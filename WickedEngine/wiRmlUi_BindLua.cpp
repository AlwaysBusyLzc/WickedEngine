// ============================================================================
// wiRmlUi_BindLua.cpp - Lua bindings for RmlUi using sol2
// ============================================================================
// This file must be compiled with C++ exceptions enabled (/EHsc or -fexceptions)
// because sol2 requires exception support. The CMake configuration handles
// this by setting per-file compile options.
//
// The bindings expose the following Lua classes:
//   - RmlContext      : wrapper for Rml::Context
//   - RmlDocument     : wrapper for Rml::ElementDocument
//   - RmlElement      : wrapper for Rml::Element
//   - RmlEvent        : wrapper for Rml::Event (passed to event callbacks)
//
// Global functions:
//   - RmlInitialize()
//   - RmlShutdown()
//   - RmlGetContext(name?) -> RmlContext
//   - RmlLoadDocument(path) -> RmlDocument
//   - RmlLoadDocumentFromMemory(rml, url?) -> RmlDocument
//   - RmlUnloadAllDocuments()
//   - RmlLoadFontFace(path, fallback?) -> boolean
//   - RmlResize(w, h)
//   - RmlUpdate(dt)
// ============================================================================

#include "wiRmlUi_BindLua.h"
#include "wiLua.h"
#include "wiBacklog.h"

#include <RmlUi/Core.h>
#include <RmlUi/Core/ElementDocument.h>
#include <RmlUi/Core/Element.h>
#include <RmlUi/Core/Event.h>
#include <RmlUi/Core/EventListener.h>
#include <RmlUi/Core/Context.h>
#include <RmlUi/Core/Types.h>
#include <RmlUi/Core/Variant.h>
#include <RmlUi/Core/Dictionary.h>

#include <sol/sol.hpp>

namespace wi::lua::rmlui
{

// ============================================================================
// Helper: Convert Rml::Variant to sol::object
// ============================================================================
static sol::object VariantToLua(sol::state_view& lua, const Rml::Variant& variant)
{
	switch (variant.GetType())
	{
	case Rml::Variant::Type::STRING:
		return sol::make_object(lua, variant.Get<Rml::String>());
	case Rml::Variant::Type::INT:
		return sol::make_object(lua, variant.Get<int>());
	case Rml::Variant::Type::FLOAT:
		return sol::make_object(lua, variant.Get<float>());
	case Rml::Variant::Type::BOOL:
		return sol::make_object(lua, variant.Get<bool>());
	case Rml::Variant::Type::VECTOR2:
	{
		auto v = variant.Get<Rml::Vector2f>();
		lua_newtable(lua.lua_state());
		lua_pushnumber(lua.lua_state(), v.x);
		lua_setfield(lua.lua_state(), -2, "x");
		lua_pushnumber(lua.lua_state(), v.y);
		lua_setfield(lua.lua_state(), -2, "y");
		return sol::object(lua.lua_state(), -1);
	}
	default:
		return sol::make_object(lua, sol::nil);
	}
}

// ============================================================================
// LuaEventListener - bridges RmlUi events to Lua callbacks
// ============================================================================
class LuaEventListener : public Rml::EventListener
{
public:
	sol::function callback;

	LuaEventListener(sol::function fn) : callback(std::move(fn)) {}

	void ProcessEvent(Rml::Event& event) override
	{
		if (!callback.valid())
			return;

		try
		{
			// Build a Lua table with event properties
			sol::table evt = callback.lua_state().create_table();
			evt["type"] = event.GetType();
			evt["id"] = (int)event.GetId();

			Rml::Element* target = event.GetTargetElement();
			if (target)
			{
				evt["target_tag"] = target->GetTagName();
				evt["target_id"] = target->GetId();
			}

			// Call the Lua function
			callback(evt);
		}
		catch (const std::exception& e)
		{
			wilog_error("[RmlUi] Lua event callback error: %s", e.what());
		}
		catch (...)
		{
			wilog_error("[RmlUi] Unknown Lua event callback error");
		}
	}

	void OnAttach(Rml::Element*) override {}
	void OnDetach(Rml::Element*) override {}
};

// ============================================================================
// Bind all RmlUi types and functions to Lua
// ============================================================================
void Bind()
{
	lua_State* L = wi::lua::GetLuaState();
	if (!L) return;

	sol::state_view lua(L);

	// ------------------------------------------------------------------
	// Global functions
	// ------------------------------------------------------------------
	lua.set_function("RmlInitialize", []() {
		wi::rmlui::Initialize();
	});

	lua.set_function("RmlShutdown", []() {
		wi::rmlui::Shutdown();
	});

	lua.set_function("RmlUpdate", [](float dt) {
		wi::rmlui::Update(dt);
	});

	lua.set_function("RmlResize", [](int w, int h) {
		wi::rmlui::Resize(w, h);
	});

	lua.set_function("RmlLoadFontFace", [](const std::string& path, sol::optional<bool> fallback) -> bool {
		return wi::rmlui::LoadFontFace(path, fallback.value_or(false));
	});

	lua.set_function("RmlUnloadAllDocuments", []() {
		wi::rmlui::UnloadAllDocuments();
	});

	lua.set_function("RmlTextInput", [](const std::string& text) {
		// Forward each character of the string to the RmlUi text input queue.
		// This allows Lua scripts to simulate text input for testing or IME.
		for (unsigned char ch : text)
		{
			wi::rmlui::ProcessTextInput(static_cast<wchar_t>(ch));
		}
	});

	lua.set_function("RmlGetContext", [](sol::optional<std::string> name) -> sol::object {
		sol::state_view lua(wi::lua::GetLuaState());
		Rml::Context* ctx = name.has_value()
			? wi::rmlui::GetContext(name.value())
			: wi::rmlui::GetContext();
		if (!ctx)
			return sol::make_object(lua, sol::nil);
		return sol::make_object(lua, ctx);
	});

	lua.set_function("RmlLoadDocument", [](const std::string& path) -> sol::object {
		sol::state_view lua(wi::lua::GetLuaState());
		Rml::ElementDocument* doc = wi::rmlui::LoadDocument(path);
		if (!doc)
			return sol::make_object(lua, sol::nil);
		return sol::make_object(lua, doc);
	});

	lua.set_function("RmlLoadDocumentFromMemory", [](const std::string& rml, sol::optional<std::string> url) -> sol::object {
		sol::state_view lua(wi::lua::GetLuaState());
		Rml::ElementDocument* doc = wi::rmlui::LoadDocumentFromMemory(rml, url.value_or("[document from memory]"));
		if (!doc)
			return sol::make_object(lua, sol::nil);
		return sol::make_object(lua, doc);
	});

	// ------------------------------------------------------------------
	// Rml::Context bindings
	// ------------------------------------------------------------------
	auto rml_context = lua.new_usertype<Rml::Context>("RmlContext",
		sol::no_constructor
	);

	rml_context.set_function("GetName", &Rml::Context::GetName);
	rml_context.set_function("SetDimensions", [](Rml::Context& ctx, int w, int h) {
		ctx.SetDimensions(Rml::Vector2i(w, h));
	});
	rml_context.set_function("GetDimensions", [](Rml::Context& ctx) {
		auto d = ctx.GetDimensions();
		return std::make_pair(d.x, d.y);
	});
	rml_context.set_function("Update", &Rml::Context::Update);
	rml_context.set_function("Render", &Rml::Context::Render);
	rml_context.set_function("LoadDocument", [](Rml::Context& ctx, const std::string& path) -> sol::object {
		sol::state_view lua(wi::lua::GetLuaState());
		Rml::ElementDocument* doc = ctx.LoadDocument(path);
		if (!doc) return sol::make_object(lua, sol::nil);
		return sol::make_object(lua, doc);
	});
	rml_context.set_function("LoadDocumentFromMemory", [](Rml::Context& ctx, const std::string& rml, sol::optional<std::string> url) -> sol::object {
		sol::state_view lua(wi::lua::GetLuaState());
		Rml::ElementDocument* doc = ctx.LoadDocumentFromMemory(rml, url.value_or("[document from memory]"));
		if (!doc) return sol::make_object(lua, sol::nil);
		return sol::make_object(lua, doc);
	});
	rml_context.set_function("UnloadDocument", &Rml::Context::UnloadDocument);
	rml_context.set_function("UnloadAllDocuments", &Rml::Context::UnloadAllDocuments);
	rml_context.set_function("GetDocument", sol::overload(
		[](Rml::Context& ctx, const std::string& id) -> sol::object {
			sol::state_view lua(wi::lua::GetLuaState());
			Rml::ElementDocument* doc = ctx.GetDocument(id);
			if (!doc) return sol::make_object(lua, sol::nil);
			return sol::make_object(lua, doc);
		},
		[](Rml::Context& ctx, int index) -> sol::object {
			sol::state_view lua(wi::lua::GetLuaState());
			Rml::ElementDocument* doc = ctx.GetDocument(index);
			if (!doc) return sol::make_object(lua, sol::nil);
			return sol::make_object(lua, doc);
		}
	));
	rml_context.set_function("GetNumDocuments", &Rml::Context::GetNumDocuments);
	rml_context.set_function("GetHoverElement", [](Rml::Context& ctx) -> sol::object {
		sol::state_view lua(wi::lua::GetLuaState());
		Rml::Element* el = ctx.GetHoverElement();
		if (!el) return sol::make_object(lua, sol::nil);
		return sol::make_object(lua, el);
	});
	rml_context.set_function("GetFocusElement", [](Rml::Context& ctx) -> sol::object {
		sol::state_view lua(wi::lua::GetLuaState());
		Rml::Element* el = ctx.GetFocusElement();
		if (!el) return sol::make_object(lua, sol::nil);
		return sol::make_object(lua, el);
	});
	rml_context.set_function("GetRootElement", [](Rml::Context& ctx) -> sol::object {
		sol::state_view lua(wi::lua::GetLuaState());
		Rml::Element* el = ctx.GetRootElement();
		if (!el) return sol::make_object(lua, sol::nil);
		return sol::make_object(lua, el);
	});
	rml_context.set_function("PullDocumentToFront", &Rml::Context::PullDocumentToFront);
	rml_context.set_function("PushDocumentToBack", &Rml::Context::PushDocumentToBack);
	rml_context.set_function("AddEventListener", [](Rml::Context& ctx, const std::string& event, sol::function callback, sol::optional<bool> capture) {
		auto* listener = new LuaEventListener(std::move(callback));
		ctx.AddEventListener(event, listener, capture.value_or(false));
	});
	rml_context.set_function("EnableMouseCursor", &Rml::Context::EnableMouseCursor);
	rml_context.set_function("ActivateTheme", &Rml::Context::ActivateTheme);
	rml_context.set_function("IsThemeActive", &Rml::Context::IsThemeActive);

	// ------------------------------------------------------------------
	// Rml::Element bindings (base class for all DOM elements)
	// ------------------------------------------------------------------
	auto rml_element = lua.new_usertype<Rml::Element>("RmlElement",
		sol::no_constructor
	);

	// Class methods
	rml_element.set_function("SetClass", &Rml::Element::SetClass);
	rml_element.set_function("IsClassSet", &Rml::Element::IsClassSet);
	rml_element.set_function("SetClassNames", &Rml::Element::SetClassNames);
	rml_element.set_function("GetClassNames", &Rml::Element::GetClassNames);
	rml_element.set_function("SetProperty", &Rml::Element::SetProperty);
	rml_element.set_function("RemoveProperty", static_cast<void (Rml::Element::*)(const Rml::String&)>(&Rml::Element::RemoveProperty));
	rml_element.set_function("GetPropertyName", [](Rml::Element& el, const std::string& name) -> sol::object {
		sol::state_view lua(wi::lua::GetLuaState());
		const Rml::Property* prop = el.GetProperty(name);
		if (!prop) return sol::make_object(lua, sol::nil);
		return sol::make_object(lua, prop->ToString());
	});
	rml_element.set_function("SetPseudoClass", &Rml::Element::SetPseudoClass);
	rml_element.set_function("IsPseudoClassSet", &Rml::Element::IsPseudoClassSet);

	// Attributes
	rml_element.set_function("SetAttribute", [](Rml::Element& el, const std::string& name, sol::object value) {
		if (value.is<std::string>())
			el.SetAttribute(name, value.as<std::string>());
		else if (value.is<int>())
			el.SetAttribute(name, value.as<int>());
		else if (value.is<double>())
			el.SetAttribute(name, value.as<float>());
		else if (value.is<bool>())
			el.SetAttribute(name, value.as<bool>());
	});
	rml_element.set_function("GetAttribute", [](Rml::Element& el, const std::string& name) -> sol::object {
		sol::state_view lua(wi::lua::GetLuaState());
		const Rml::Variant* attr = el.GetAttribute(name);
		if (!attr) return sol::make_object(lua, sol::nil);
		return VariantToLua(lua, *attr);
	});
	rml_element.set_function("HasAttribute", &Rml::Element::HasAttribute);
	rml_element.set_function("RemoveAttribute", &Rml::Element::RemoveAttribute);
	rml_element.set_function("GetNumAttributes", &Rml::Element::GetNumAttributes);

	// DOM properties
	rml_element.set_function("GetTagName", &Rml::Element::GetTagName);
	rml_element.set_function("GetId", &Rml::Element::GetId);
	rml_element.set_function("SetId", &Rml::Element::SetId);
	rml_element.set_function("IsVisible", [](Rml::Element& el, sol::optional<bool> include_ancestors) {
		return el.IsVisible(include_ancestors.value_or(false));
	});
	rml_element.set_function("GetInnerRML", &Rml::Element::GetInnerRML);
	rml_element.set_function("SetInnerRML", &Rml::Element::SetInnerRML);
	rml_element.set_function("Focus", [](Rml::Element& el, sol::optional<bool> focus_visible) {
		return el.Focus(focus_visible.value_or(false));
	});
	rml_element.set_function("Blur", &Rml::Element::Blur);
	rml_element.set_function("Click", &Rml::Element::Click);

	// DOM hierarchy
	rml_element.set_function("GetParentNode", [](Rml::Element& el) -> sol::object {
		sol::state_view lua(wi::lua::GetLuaState());
		Rml::Element* p = el.GetParentNode();
		if (!p) return sol::make_object(lua, sol::nil);
		return sol::make_object(lua, p);
	});
	rml_element.set_function("GetNextSibling", [](Rml::Element& el) -> sol::object {
		sol::state_view lua(wi::lua::GetLuaState());
		Rml::Element* s = el.GetNextSibling();
		if (!s) return sol::make_object(lua, sol::nil);
		return sol::make_object(lua, s);
	});
	rml_element.set_function("GetPreviousSibling", [](Rml::Element& el) -> sol::object {
		sol::state_view lua(wi::lua::GetLuaState());
		Rml::Element* s = el.GetPreviousSibling();
		if (!s) return sol::make_object(lua, sol::nil);
		return sol::make_object(lua, s);
	});
	rml_element.set_function("GetFirstChild", [](Rml::Element& el) -> sol::object {
		sol::state_view lua(wi::lua::GetLuaState());
		Rml::Element* c = el.GetFirstChild();
		if (!c) return sol::make_object(lua, sol::nil);
		return sol::make_object(lua, c);
	});
	rml_element.set_function("GetLastChild", [](Rml::Element& el) -> sol::object {
		sol::state_view lua(wi::lua::GetLuaState());
		Rml::Element* c = el.GetLastChild();
		if (!c) return sol::make_object(lua, sol::nil);
		return sol::make_object(lua, c);
	});
	rml_element.set_function("GetChild", [](Rml::Element& el, int index) -> sol::object {
		sol::state_view lua(wi::lua::GetLuaState());
		Rml::Element* c = el.GetChild(index);
		if (!c) return sol::make_object(lua, sol::nil);
		return sol::make_object(lua, c);
	});
	rml_element.set_function("GetNumChildren", [](Rml::Element& el, sol::optional<bool> include_non_dom) {
		return el.GetNumChildren(include_non_dom.value_or(false));
	});
	rml_element.set_function("HasChildNodes", &Rml::Element::HasChildNodes);
	rml_element.set_function("GetElementById", [](Rml::Element& el, const std::string& id) -> sol::object {
		sol::state_view lua(wi::lua::GetLuaState());
		Rml::Element* c = el.GetElementById(id);
		if (!c) return sol::make_object(lua, sol::nil);
		return sol::make_object(lua, c);
	});
	rml_element.set_function("QuerySelector", [](Rml::Element& el, const std::string& selector) -> sol::object {
		sol::state_view lua(wi::lua::GetLuaState());
		Rml::Element* c = el.QuerySelector(selector);
		if (!c) return sol::make_object(lua, sol::nil);
		return sol::make_object(lua, c);
	});

	// Events
	rml_element.set_function("AddEventListener", [](Rml::Element& el, const std::string& event, sol::function callback, sol::optional<bool> capture) {
		auto* listener = new LuaEventListener(std::move(callback));
		el.AddEventListener(event, listener, capture.value_or(false));
	});
	rml_element.set_function("DispatchEvent", [](Rml::Element& el, const std::string& type, sol::optional<sol::table> params) -> bool {
		Rml::Dictionary dict;
		if (params)
		{
			for (auto& kv : *params)
			{
				std::string key = kv.first.as<std::string>();
				sol::object val = kv.second;
				if (val.is<std::string>())
					dict[key] = val.as<std::string>();
				else if (val.is<int>())
					dict[key] = val.as<int>();
				else if (val.is<double>())
					dict[key] = val.as<float>();
				else if (val.is<bool>())
					dict[key] = val.as<bool>();
			}
		}
		return el.DispatchEvent(type, dict);
	});

	// Layout info
	rml_element.set_function("GetOffsetWidth", &Rml::Element::GetOffsetWidth);
	rml_element.set_function("GetOffsetHeight", &Rml::Element::GetOffsetHeight);
	rml_element.set_function("GetOffsetLeft", &Rml::Element::GetOffsetLeft);
	rml_element.set_function("GetOffsetTop", &Rml::Element::GetOffsetTop);
	rml_element.set_function("GetClientWidth", &Rml::Element::GetClientWidth);
	rml_element.set_function("GetClientHeight", &Rml::Element::GetClientHeight);
	rml_element.set_function("GetScrollLeft", &Rml::Element::GetScrollLeft);
	rml_element.set_function("SetScrollLeft", &Rml::Element::SetScrollLeft);
	rml_element.set_function("GetScrollTop", &Rml::Element::GetScrollTop);
	rml_element.set_function("SetScrollTop", &Rml::Element::SetScrollTop);
	rml_element.set_function("GetScrollWidth", &Rml::Element::GetScrollWidth);
	rml_element.set_function("GetScrollHeight", &Rml::Element::GetScrollHeight);
	rml_element.set_function("ScrollIntoView", [](Rml::Element& el, sol::optional<bool> align_top) {
		el.ScrollIntoView(align_top.value_or(true));
	});

	rml_element.set_function("GetOwnerDocument", [](Rml::Element& el) -> sol::object {
		sol::state_view lua(wi::lua::GetLuaState());
		Rml::ElementDocument* doc = el.GetOwnerDocument();
		if (!doc) return sol::make_object(lua, sol::nil);
		return sol::make_object(lua, doc);
	});
	rml_element.set_function("GetContext", [](Rml::Element& el) -> sol::object {
		sol::state_view lua(wi::lua::GetLuaState());
		Rml::Context* ctx = el.GetContext();
		if (!ctx) return sol::make_object(lua, sol::nil);
		return sol::make_object(lua, ctx);
	});

	// Animation
	rml_element.set_function("Animate", [](Rml::Element& el, const std::string& prop, const std::string& value, float duration) -> bool {
		return el.Animate(prop, Rml::Property(value, Rml::Unit::STRING), duration);
	});

	// ------------------------------------------------------------------
	// Rml::ElementDocument bindings (inherits from Element)
	// ------------------------------------------------------------------
	auto rml_document = lua.new_usertype<Rml::ElementDocument>("RmlDocument",
		sol::base_classes, sol::bases<Rml::Element>(),
		sol::no_constructor
	);

	rml_document.set_function("GetTitle", &Rml::ElementDocument::GetTitle);
	rml_document.set_function("SetTitle", &Rml::ElementDocument::SetTitle);
	rml_document.set_function("GetSourceURL", &Rml::ElementDocument::GetSourceURL);
	rml_document.set_function("Show", [](Rml::ElementDocument& doc, sol::optional<std::string> modal, sol::optional<std::string> focus) {
		Rml::ModalFlag mf = Rml::ModalFlag::None;
		Rml::FocusFlag ff = Rml::FocusFlag::Auto;
		if (modal)
		{
			if (*modal == "modal") mf = Rml::ModalFlag::Modal;
			else if (*modal == "keep") mf = Rml::ModalFlag::Keep;
		}
		if (focus)
		{
			if (*focus == "none") ff = Rml::FocusFlag::None;
			else if (*focus == "document") ff = Rml::FocusFlag::Document;
			else if (*focus == "keep") ff = Rml::FocusFlag::Keep;
			else if (*focus == "auto") ff = Rml::FocusFlag::Auto;
		}
		doc.Show(mf, ff);
	});
	rml_document.set_function("Hide", &Rml::ElementDocument::Hide);
	rml_document.set_function("Close", &Rml::ElementDocument::Close);
	rml_document.set_function("PullToFront", &Rml::ElementDocument::PullToFront);
	rml_document.set_function("PushToBack", &Rml::ElementDocument::PushToBack);
	rml_document.set_function("IsModal", &Rml::ElementDocument::IsModal);
	rml_document.set_function("UpdateDocument", &Rml::ElementDocument::UpdateDocument);
	rml_document.set_function("ReloadStyleSheet", &Rml::ElementDocument::ReloadStyleSheet);

	wilog("[wi::lua::rmlui] RmlUi Lua bindings registered (using sol2).");
}

} // namespace wi::lua::rmlui
