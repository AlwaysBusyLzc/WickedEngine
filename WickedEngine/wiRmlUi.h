#pragma once

// RmlUi integration for WickedEngine.
// Provides a HTML/CSS-based UI system that can be rendered on top of the engine's render paths.
// Lua bindings are available through wiRmlUi_BindLua (using sol2).

#include "CommonInclude.h"
#include "wiGraphicsDevice.h"

#include <string>
#include <unordered_map>
#include <memory>

// Forward declarations for RmlUi types to avoid including RmlUi headers here.
namespace Rml {
	class Context;
	class ElementDocument;
	class Element;
	class EventListener;
}

namespace wi::rmlui
{
	// Initialize the RmlUi system. Must be called after the graphics device is created.
	// Creates the system interface, render interface, file interface and default context.
	void Initialize();

	// Shut down RmlUi and release all resources.
	void Shutdown();

	// Returns true if RmlUi has been initialized.
	bool IsInitialized();

	// Per-frame update. Must be called every frame before Render().
	// Processes input events and updates all contexts.
	// dt: delta time in seconds.
	void Update(float dt);

	// Render all RmlUi contexts onto the given command list.
	// This should be called during the Compose phase of a RenderPath.
	void Render(wi::graphics::CommandList cmd);

	// Called when the window/canvas is resized.
	// w, h: new dimensions in physical pixels.
	void Resize(int w, int h);

	// --- Context management ---

	// Get the default context (created during Initialize).
	Rml::Context* GetContext();

	// Get a context by name.
	Rml::Context* GetContext(const std::string& name);

	// Create a new context with the given name and dimensions.
	Rml::Context* CreateContext(const std::string& name, int width, int height);

	// Remove a context by name. Returns true if the context was found and removed.
	bool RemoveContext(const std::string& name);

	// --- Document management (convenience wrappers around the default context) ---

	// Load an RML document from file into the default context.
	Rml::ElementDocument* LoadDocument(const std::string& path);

	// Load an RML document from a string into the default context.
	Rml::ElementDocument* LoadDocumentFromMemory(const std::string& rml, const std::string& source_url = "[document from memory]");

	// Unload all documents from the default context.
	void UnloadAllDocuments();

	// --- Font management ---

	// Load a font face from a file path.
	bool LoadFontFace(const std::string& path, bool fallback = false);

	// --- Text input ---
	// Forward a character (from WM_CHAR or equivalent) to the RmlUi context.
	// Call this from your platform's character input handler (e.g. WndProc WM_CHAR).
	// Characters are queued and processed in the next Update() call.
	void ProcessTextInput(wchar_t character);

	// --- Event listener factory ---
	// Creates an EventListener that calls back into a Lua function.
	// The Lua function reference is managed internally.
	// This is used by the Lua bindings; C++ users should create their own EventListener subclasses.
	Rml::EventListener* CreateLuaEventListener(int lua_function_ref);
	void DestroyLuaEventListener(Rml::EventListener* listener);
}
