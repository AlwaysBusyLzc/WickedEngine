#include "wiRmlUi.h"
#include "wiRenderer.h"
#include "wiInput.h"
#include "wiTimer.h"
#include "wiHelper.h"
#include "wiBacklog.h"
#include "wiEventHandler.h"
#include "wiResourceManager.h"
#include "wiMath.h"

#include <RmlUi/Core.h>
#include <RmlUi/Core/ElementDocument.h>
#include <RmlUi/Core/EventListener.h>
#include <RmlUi/Core/SystemInterface.h>
#include <RmlUi/Core/FileInterface.h>
#include <RmlUi/Core/RenderInterface.h>
#include <RmlUi/Core/Vertex.h>
#include <RmlUi/Core/Texture.h>
#include <RmlUi/Core/Math.h>
#include <RmlUi/Core/Input.h>

#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <mutex>

// Lua headers for the event listener callback
extern "C" {
#include "LUA/lua.h"
#include "LUA/lauxlib.h"
}
#include "wiLua.h"

using namespace DirectX;
using namespace wi::graphics;

namespace wi::rmlui
{

// ============================================================================
// Internal state
// ============================================================================

namespace
{
	bool g_initialized = false;
	wi::Timer g_timer;

	// Default context dimensions (physical pixels)
	int g_width = 1280;
	int g_height = 720;

	// Default context name
	constexpr const char* DEFAULT_CONTEXT = "default";

	// Input tracking
	bool g_mouseButtonsPressed[5] = {};
	int g_mouseX = 0;
	int g_mouseY = 0;
	int g_mouseWheelDelta = 0;

	// Keyboard key tracking for edge detection (press/release events)
	bool g_keyPressed[wi::input::BUTTON_ENUM_SIZE] = {};

	// Text input queue: characters injected via ProcessTextInput() are consumed in Update()
	std::vector<wchar_t> g_textInputQueue;
	std::mutex g_textInputMutex;

	// Shader / pipeline resources
	static Shader g_vertexShader;
	static Shader g_pixelShader;
	static InputLayout g_inputLayout;
	static BlendState g_blendState;       // premultiplied alpha
	static RasterizerState g_rasterizerState;
	static DepthStencilState g_depthStencilState;
	static PipelineState g_pso;
	static Sampler g_sampler;
	static Texture g_whiteTexture;        // 1x1 white texture used when no texture is bound
	static bool g_shadersLoaded = false;

	// WickedEngine keyboard button -> RmlUi KeyIdentifier mapping table
	struct KeyMapEntry { wi::input::BUTTON wickedKey; Rml::Input::KeyIdentifier rmlKey; };
	static const KeyMapEntry g_keyMap[] = {
		{ wi::input::KEYBOARD_BUTTON_UP,         Rml::Input::KI_UP },
		{ wi::input::KEYBOARD_BUTTON_DOWN,       Rml::Input::KI_DOWN },
		{ wi::input::KEYBOARD_BUTTON_LEFT,       Rml::Input::KI_LEFT },
		{ wi::input::KEYBOARD_BUTTON_RIGHT,      Rml::Input::KI_RIGHT },
		{ wi::input::KEYBOARD_BUTTON_SPACE,      Rml::Input::KI_SPACE },
		{ wi::input::KEYBOARD_BUTTON_RSHIFT,     Rml::Input::KI_RSHIFT },
		{ wi::input::KEYBOARD_BUTTON_LSHIFT,     Rml::Input::KI_LSHIFT },
		{ wi::input::KEYBOARD_BUTTON_LCONTROL,   Rml::Input::KI_LCONTROL },
		{ wi::input::KEYBOARD_BUTTON_RCONTROL,   Rml::Input::KI_RCONTROL },
		{ wi::input::KEYBOARD_BUTTON_ALT,        Rml::Input::KI_LMENU },
		{ wi::input::KEYBOARD_BUTTON_ALTGR,      Rml::Input::KI_RMENU },
		{ wi::input::KEYBOARD_BUTTON_ENTER,      Rml::Input::KI_RETURN },
		{ wi::input::KEYBOARD_BUTTON_ESCAPE,     Rml::Input::KI_ESCAPE },
		{ wi::input::KEYBOARD_BUTTON_HOME,       Rml::Input::KI_HOME },
		{ wi::input::KEYBOARD_BUTTON_END,        Rml::Input::KI_END },
		{ wi::input::KEYBOARD_BUTTON_DELETE,     Rml::Input::KI_DELETE },
		{ wi::input::KEYBOARD_BUTTON_BACKSPACE,  Rml::Input::KI_BACK },
		{ wi::input::KEYBOARD_BUTTON_PAGEDOWN,   Rml::Input::KI_NEXT },
		{ wi::input::KEYBOARD_BUTTON_PAGEUP,     Rml::Input::KI_PRIOR },
		{ wi::input::KEYBOARD_BUTTON_TAB,        Rml::Input::KI_TAB },
		{ wi::input::KEYBOARD_BUTTON_TILDE,      Rml::Input::KI_OEM_3 },
		{ wi::input::KEYBOARD_BUTTON_INSERT,     Rml::Input::KI_INSERT },
		{ wi::input::KEYBOARD_BUTTON_F1,         Rml::Input::KI_F1 },
		{ wi::input::KEYBOARD_BUTTON_F2,         Rml::Input::KI_F2 },
		{ wi::input::KEYBOARD_BUTTON_F3,         Rml::Input::KI_F3 },
		{ wi::input::KEYBOARD_BUTTON_F4,         Rml::Input::KI_F4 },
		{ wi::input::KEYBOARD_BUTTON_F5,         Rml::Input::KI_F5 },
		{ wi::input::KEYBOARD_BUTTON_F6,         Rml::Input::KI_F6 },
		{ wi::input::KEYBOARD_BUTTON_F7,         Rml::Input::KI_F7 },
		{ wi::input::KEYBOARD_BUTTON_F8,         Rml::Input::KI_F8 },
		{ wi::input::KEYBOARD_BUTTON_F9,         Rml::Input::KI_F9 },
		{ wi::input::KEYBOARD_BUTTON_F10,        Rml::Input::KI_F10 },
		{ wi::input::KEYBOARD_BUTTON_F11,        Rml::Input::KI_F11 },
		{ wi::input::KEYBOARD_BUTTON_F12,        Rml::Input::KI_F12 },
		{ wi::input::KEYBOARD_BUTTON_NUMPAD0,    Rml::Input::KI_NUMPAD0 },
		{ wi::input::KEYBOARD_BUTTON_NUMPAD1,    Rml::Input::KI_NUMPAD1 },
		{ wi::input::KEYBOARD_BUTTON_NUMPAD2,    Rml::Input::KI_NUMPAD2 },
		{ wi::input::KEYBOARD_BUTTON_NUMPAD3,    Rml::Input::KI_NUMPAD3 },
		{ wi::input::KEYBOARD_BUTTON_NUMPAD4,    Rml::Input::KI_NUMPAD4 },
		{ wi::input::KEYBOARD_BUTTON_NUMPAD5,    Rml::Input::KI_NUMPAD5 },
		{ wi::input::KEYBOARD_BUTTON_NUMPAD6,    Rml::Input::KI_NUMPAD6 },
		{ wi::input::KEYBOARD_BUTTON_NUMPAD7,    Rml::Input::KI_NUMPAD7 },
		{ wi::input::KEYBOARD_BUTTON_NUMPAD8,    Rml::Input::KI_NUMPAD8 },
		{ wi::input::KEYBOARD_BUTTON_NUMPAD9,    Rml::Input::KI_NUMPAD9 },
		{ wi::input::KEYBOARD_BUTTON_MULTIPLY,   Rml::Input::KI_MULTIPLY },
		{ wi::input::KEYBOARD_BUTTON_ADD,        Rml::Input::KI_ADD },
		{ wi::input::KEYBOARD_BUTTON_SUBTRACT,   Rml::Input::KI_SUBTRACT },
		{ wi::input::KEYBOARD_BUTTON_DECIMAL,    Rml::Input::KI_DECIMAL },
		{ wi::input::KEYBOARD_BUTTON_DIVIDE,     Rml::Input::KI_DIVIDE },
	};
}

// ============================================================================
// System Interface
// ============================================================================

class WickedSystemInterface : public Rml::SystemInterface
{
public:
	double GetElapsedTime() override
	{
		return g_timer.elapsed() / 1000.0;
	}

	bool LogMessage(Rml::Log::Type type, const Rml::String& message) override
	{
		switch (type)
		{
		case Rml::Log::LT_ERROR:
			wilog_error("[RmlUi] %s", message.c_str());
			break;
		case Rml::Log::LT_WARNING:
			wilog_warning("[RmlUi] %s", message.c_str());
			break;
		case Rml::Log::LT_INFO:
			wilog("[RmlUi] %s", message.c_str());
			break;
		default:
			wilog("[RmlUi] %s", message.c_str());
			break;
		}
		return true;
	}

	void SetMouseCursor(const Rml::String& cursor_name) override
	{
		// Could forward to wi::input if desired
	}

	void SetClipboardText(const Rml::String& text) override
	{
		// wi::helper::SetClipboardText expects std::wstring
		std::wstring wtext(text.begin(), text.end());
		wi::helper::SetClipboardText(wtext);
	}

	void GetClipboardText(Rml::String& text) override
	{
		// wi::helper::GetClipboardText returns std::wstring
		std::wstring wtext = wi::helper::GetClipboardText();
		text.assign(wtext.begin(), wtext.end());
	}
};

// ============================================================================
// File Interface
// ============================================================================

class WickedFileInterface : public Rml::FileInterface
{
public:
	Rml::FileHandle Open(const Rml::String& path) override
	{
		auto* file = new std::ifstream(path, std::ios::binary);
		if (!file->is_open())
		{
			delete file;
			return (Rml::FileHandle)0;
		}
		return (Rml::FileHandle)file;
	}

	void Close(Rml::FileHandle file) override
	{
		auto* stream = reinterpret_cast<std::ifstream*>(file);
		if (stream)
		{
			stream->close();
			delete stream;
		}
	}

	size_t Read(void* buffer, size_t size, Rml::FileHandle file) override
	{
		auto* stream = reinterpret_cast<std::ifstream*>(file);
		if (!stream) return 0;
		stream->read(static_cast<char*>(buffer), size);
		return (size_t)stream->gcount();
	}

	bool Seek(Rml::FileHandle file, long offset, int origin) override
	{
		auto* stream = reinterpret_cast<std::ifstream*>(file);
		if (!stream) return false;
		std::ios_base::seekdir dir = std::ios_base::beg;
		switch (origin)
		{
		case SEEK_SET: dir = std::ios_base::beg; break;
		case SEEK_CUR: dir = std::ios_base::cur; break;
		case SEEK_END: dir = std::ios_base::end; break;
		}
		stream->seekg(offset, dir);
		return stream->good();
	}

	size_t Tell(Rml::FileHandle file) override
	{
		auto* stream = reinterpret_cast<std::ifstream*>(file);
		if (!stream) return 0;
		return (size_t)stream->tellg();
	}
};

// ============================================================================
// Render Interface - bridges RmlUi rendering to WickedEngine GraphicsDevice
// ============================================================================

class WickedRenderInterface : public Rml::RenderInterface
{
public:
	struct CompiledGeometry
	{
		GPUBuffer vertexBuffer;
		GPUBuffer indexBuffer;
		int indexCount = 0;
	};

	struct TextureEntry
	{
		Texture texture;
		// For textures loaded via resource manager, keep the resource alive:
		wi::Resource resource;
	};

	// We store compiled geometries and textures in maps keyed by their handles.
	std::unordered_map<Rml::CompiledGeometryHandle, std::unique_ptr<CompiledGeometry>> geometries;
	std::unordered_map<Rml::TextureHandle, std::unique_ptr<TextureEntry>> textures;
	Rml::CompiledGeometryHandle nextGeometryHandle = 1;
	Rml::TextureHandle nextTextureHandle = 1;

	CommandList currentCmd;
	bool scissorEnabled = false;
	Rml::Rectanglei scissorRegion;

	// Special handle for the internal 1x1 white texture (used when RmlUi passes texture == 0)
	Rml::TextureHandle whiteTextureHandle = 0;

	Rml::CompiledGeometryHandle CompileGeometry(Rml::Span<const Rml::Vertex> vertices, Rml::Span<const int> indices) override
	{
		auto* device = GetDevice();
		if (!device) return 0;

		auto geom = std::make_unique<CompiledGeometry>();
		geom->indexCount = (int)indices.size();

		// Rml::Vertex layout: Vector2f position, ColourbPremultiplied colour, Vector2f tex_coord
		// This must match the InputLayout declared in LoadShaders().
		GPUBufferDesc vbDesc;
		vbDesc.usage = Usage::DEFAULT;
		vbDesc.stride = sizeof(Rml::Vertex);
		vbDesc.size = uint32_t(vertices.size() * sizeof(Rml::Vertex));
		vbDesc.bind_flags = BindFlag::VERTEX_BUFFER;

		device->CreateBuffer(&vbDesc, vertices.data(), &geom->vertexBuffer);

		// Create index buffer (RmlUi uses 32-bit indices)
		GPUBufferDesc ibDesc;
		ibDesc.usage = Usage::DEFAULT;
		ibDesc.stride = sizeof(int);
		ibDesc.size = uint32_t(indices.size() * sizeof(int));
		ibDesc.bind_flags = BindFlag::INDEX_BUFFER;

		device->CreateBuffer(&ibDesc, indices.data(), &geom->indexBuffer);

		Rml::CompiledGeometryHandle handle = nextGeometryHandle++;
		geometries[handle] = std::move(geom);
		return handle;
	}

	void RenderGeometry(Rml::CompiledGeometryHandle geometry, Rml::Vector2f translation, Rml::TextureHandle texture) override
	{
		auto* device = GetDevice();
		if (!device || !currentCmd.IsValid()) return;

		auto geomIt = geometries.find(geometry);
		if (geomIt == geometries.end()) return;
		CompiledGeometry* geom = geomIt->second.get();

		// Build the transform: orthographic projection (origin top-left, y down) * translation
		// X: [0, g_width]  -> [-1, 1]
		// Y: [0, g_height] -> [ 1,-1]  (flipped)
		struct RmlUiCB
		{
			XMFLOAT4X4 Transform;
		};
		RmlUiCB cb;
		// XMMatrixOrthographicOffCenterLH(left, right, bottom, top, znear, zfar)
		// We want bottom=g_height, top=0 so that screen y (downward) maps to NDC y (upward) inverted.
		XMMATRIX proj = XMMatrixOrthographicOffCenterLH(0.0f, (float)g_width, (float)g_height, 0.0f, 0.0f, 1.0f);
		XMMATRIX trans = XMMatrixTranslation(translation.x, translation.y, 0.0f);
		XMStoreFloat4x4(&cb.Transform, proj * trans);

		device->BindDynamicConstantBuffer(cb, 0, currentCmd);

		// Bind pipeline state
		device->BindPipelineState(&g_pso, currentCmd);

		// Bind sampler at slot 0
		device->BindSampler(&g_sampler, 0, currentCmd);

		// Bind texture: RmlUi passes texture == 0 when no texture is set; use the white texture then.
		const Texture* texToBind = &g_whiteTexture;
		if (texture != 0)
		{
			auto texIt = textures.find(texture);
			if (texIt != textures.end())
			{
				texToBind = &texIt->second->texture;
			}
		}
		device->BindResource(texToBind, 0, currentCmd);

		// Bind vertex buffer
		const GPUBuffer* vbs[] = { &geom->vertexBuffer };
		const uint32_t strides[] = { sizeof(Rml::Vertex) };
		const uint64_t offsets[] = { 0 };
		device->BindVertexBuffers(vbs, 0, arraysize(vbs), strides, offsets, currentCmd);

		// Bind index buffer (32-bit indices)
		device->BindIndexBuffer(&geom->indexBuffer, IndexBufferFormat::UINT32, 0, currentCmd);

		// Draw
		device->DrawIndexed(geom->indexCount, 0, 0, currentCmd);
	}

	void ReleaseGeometry(Rml::CompiledGeometryHandle geometry) override
	{
		geometries.erase(geometry);
	}

	Rml::TextureHandle LoadTexture(Rml::Vector2i& texture_dimensions, const Rml::String& source) override
	{
		auto* device = GetDevice();
		if (!device) return 0;

		// Use WickedEngine's resource manager to load the texture from file.
		wi::Resource res = wi::resourcemanager::Load(source);
		if (!res.IsValid())
		{
			wilog_warning("[wi::rmlui] LoadTexture: failed to load '%s'", source.c_str());
			return 0;
		}

		const Texture& tex = res.GetTexture();
		const TextureDesc& desc = tex.GetDesc();
		texture_dimensions = { (int)desc.width, (int)desc.height };

		auto entry = std::make_unique<TextureEntry>();
		entry->texture = tex;
		entry->resource = res;

		Rml::TextureHandle handle = nextTextureHandle++;
		textures[handle] = std::move(entry);
		return handle;
	}

	Rml::TextureHandle GenerateTexture(Rml::Span<const Rml::byte> source, Rml::Vector2i source_dimensions) override
	{
		auto* device = GetDevice();
		if (!device) return 0;

		auto tex = std::make_unique<TextureEntry>();

		TextureDesc desc;
		desc.width = source_dimensions.x;
		desc.height = source_dimensions.y;
		desc.format = Format::R8G8B8A8_UNORM;
		desc.bind_flags = BindFlag::SHADER_RESOURCE;

		SubresourceData init_data;
		init_data.data_ptr = source.data();
		init_data.row_pitch = source_dimensions.x * 4;

		if (!device->CreateTexture(&desc, &init_data, &tex->texture))
			return 0;

		Rml::TextureHandle handle = nextTextureHandle++;
		textures[handle] = std::move(tex);
		return handle;
	}

	void ReleaseTexture(Rml::TextureHandle texture) override
	{
		// Never release the internal white texture handle here
		if (texture == whiteTextureHandle) return;
		textures.erase(texture);
	}

	void EnableScissorRegion(bool enable) override
	{
		scissorEnabled = enable;
		auto* device = GetDevice();
		if (device && currentCmd.IsValid())
		{
			if (!enable)
			{
				// Disable scissor by setting the full-screen rect
				Rect full;
				full.left = 0;
				full.top = 0;
				full.right = g_width;
				full.bottom = g_height;
				device->BindScissorRects(1, &full, currentCmd);
			}
		}
	}

	void SetScissorRegion(Rml::Rectanglei region) override
	{
		scissorRegion = region;
		auto* device = GetDevice();
		if (device && currentCmd.IsValid())
		{
			Rect rect;
			rect.left = region.Left();
			rect.top = region.Top();
			rect.right = region.Right();
			rect.bottom = region.Bottom();
			device->BindScissorRects(1, &rect, currentCmd);
		}
	}

	void SetCommandList(CommandList cmd)
	{
		currentCmd = cmd;
	}
};

// ============================================================================
// Lua Event Listener
// ============================================================================

class LuaEventListener : public Rml::EventListener
{
public:
	int luaRef = LUA_NOREF;
	lua_State* L = nullptr;

	LuaEventListener(int ref, lua_State* state) : luaRef(ref), L(state) {}

	~LuaEventListener() override
	{
		if (L && luaRef != LUA_NOREF)
		{
			luaL_unref(L, LUA_REGISTRYINDEX, luaRef);
		}
	}

	void ProcessEvent(Rml::Event& event) override
	{
		if (!L || luaRef == LUA_NOREF) return;

		// Push the Lua function onto the stack
		lua_rawgeti(L, LUA_REGISTRYINDEX, luaRef);

		// Create a Lua table representing the event
		lua_newtable(L);
		lua_pushstring(L, event.GetType().c_str());
		lua_setfield(L, -2, "type");

		// Push the event type string as the single argument
		// A more complete implementation would expose more event properties
		if (lua_pcall(L, 1, 0, 0) != LUA_OK)
		{
			const char* err = lua_tostring(L, -1);
			wilog_error("[RmlUi] Lua event listener error: %s", err ? err : "unknown");
			lua_pop(L, 1);
		}
	}

	void OnAttach(Rml::Element* element) override {}
	void OnDetach(Rml::Element* element) override {}
};

// ============================================================================
// Static instances
// ============================================================================

namespace
{
	WickedSystemInterface g_systemInterface;
	WickedFileInterface g_fileInterface;
	WickedRenderInterface g_renderInterface;
}

// ============================================================================
// Shader / pipeline initialization
// ============================================================================

static void LoadShaders()
{
	GraphicsDevice* device = GetDevice();
	if (!device) return;

	// Load the RmlUi-specific vertex and pixel shaders.
	// The engine's shader compiler will compile the .hlsl sources in the
	// shaders/ directory into .cso binaries on demand (when outdated).
	bool vs_ok = wi::renderer::LoadShader(ShaderStage::VS, g_vertexShader, "RmlUiVS.cso");
	bool ps_ok = wi::renderer::LoadShader(ShaderStage::PS, g_pixelShader, "RmlUiPS.cso");

	if (!vs_ok || !ps_ok)
	{
		wilog_error("[wi::rmlui] Failed to load RmlUi shaders (VS=%d PS=%d)", vs_ok, ps_ok);
		return;
	}

	// Input layout matching Rml::Vertex:
	//   Vector2f position          -> POSITION   (R32G32_FLOAT, 8 bytes, offset 0)
	//   ColourbPremultiplied colour-> COLOR0     (R8G8B8A8_UNORM, 4 bytes, offset 8)
	//   Vector2f tex_coord         -> TEXCOORD0  (R32G32_FLOAT, 8 bytes, offset 12)
	g_inputLayout.elements =
	{
		{ "POSITION",  0, Format::R32G32_FLOAT,    0, 0,  InputClassification::PER_VERTEX_DATA },
		{ "COLOR",     0, Format::R8G8B8A8_UNORM,  0, 8,  InputClassification::PER_VERTEX_DATA },
		{ "TEXCOORD",  0, Format::R32G32_FLOAT,    0, 12, InputClassification::PER_VERTEX_DATA },
	};

	// Premultiplied alpha blend: src * ONE + dest * INV_SRC_ALPHA
	g_blendState.independent_blend_enable = false;
	g_blendState.alpha_to_coverage_enable = false;
	g_blendState.render_target[0].blend_enable = true;
	g_blendState.render_target[0].src_blend = Blend::ONE;
	g_blendState.render_target[0].dest_blend = Blend::INV_SRC_ALPHA;
	g_blendState.render_target[0].blend_op = BlendOp::ADD;
	g_blendState.render_target[0].src_blend_alpha = Blend::ONE;
	g_blendState.render_target[0].dest_blend_alpha = Blend::INV_SRC_ALPHA;
	g_blendState.render_target[0].blend_op_alpha = BlendOp::ADD;
	g_blendState.render_target[0].render_target_write_mask = ColorWrite::ENABLE_ALL;

	// No depth testing, no culling (UI is double-sided)
	g_depthStencilState.depth_enable = false;
	g_depthStencilState.depth_write_mask = DepthWriteMask::ZERO;
	g_rasterizerState.cull_mode = CullMode::NONE;
	g_rasterizerState.fill_mode = FillMode::SOLID;
	g_rasterizerState.depth_clip_enable = false;

	PipelineStateDesc desc;
	desc.vs = &g_vertexShader;
	desc.ps = &g_pixelShader;
	desc.il = &g_inputLayout;
	desc.bs = &g_blendState;
	desc.dss = &g_depthStencilState;
	desc.rs = &g_rasterizerState;
	desc.pt = PrimitiveTopology::TRIANGLELIST;

	device->CreatePipelineState(&desc, &g_pso);

	// Linear clamp sampler for UI textures
	SamplerDesc samplerDesc;
	samplerDesc.filter = Filter::MIN_MAG_MIP_LINEAR;
	samplerDesc.address_u = TextureAddressMode::CLAMP;
	samplerDesc.address_v = TextureAddressMode::CLAMP;
	samplerDesc.address_w = TextureAddressMode::CLAMP;
	device->CreateSampler(&samplerDesc, &g_sampler);

	// Create the 1x1 white texture used as a fallback when RmlUi renders without a texture
	if (!g_whiteTexture.IsValid())
	{
		TextureDesc texDesc;
		texDesc.width = 1;
		texDesc.height = 1;
		texDesc.format = Format::R8G8B8A8_UNORM;
		texDesc.bind_flags = BindFlag::SHADER_RESOURCE;

		uint8_t white[4] = { 255, 255, 255, 255 };
		SubresourceData initData;
		initData.data_ptr = white;
		initData.row_pitch = 4;

		device->CreateTexture(&texDesc, &initData, &g_whiteTexture);
	}

	g_shadersLoaded = true;
	wilog("[wi::rmlui] Shaders and pipeline state loaded.");
}

// ============================================================================
// Public API implementation
// ============================================================================

void Initialize()
{
	if (g_initialized) return;

	wilog("[wi::rmlui] Initializing RmlUi...");

	Rml::SetSystemInterface(&g_systemInterface);
	Rml::SetFileInterface(&g_fileInterface);
	Rml::SetRenderInterface(&g_renderInterface);

	if (!Rml::Initialise())
	{
		wilog_error("[wi::rmlui] Failed to initialize RmlUi!");
		return;
	}

	// Create the default context
	Rml::Context* ctx = Rml::CreateContext(DEFAULT_CONTEXT, Rml::Vector2i(g_width, g_height));
	if (!ctx)
	{
		wilog_error("[wi::rmlui] Failed to create default context!");
		Rml::Shutdown();
		return;
	}

	// Load shaders & create pipeline state (subscribe to shader reload events)
	static wi::eventhandler::Handle handle = wi::eventhandler::Subscribe(wi::eventhandler::EVENT_RELOAD_SHADERS, [](uint64_t userdata) { LoadShaders(); });
	LoadShaders();

	g_timer.record();
	g_initialized = true;
	wilog("[wi::rmlui] RmlUi initialized successfully.");
}

void Shutdown()
{
	if (!g_initialized) return;

	Rml::Shutdown();
	g_initialized = false;
	wilog("[wi::rmlui] RmlUi shut down.");
}

bool IsInitialized()
{
	return g_initialized;
}

void Update(float dt)
{
	if (!g_initialized) return;

	// Process input: forward mouse/keyboard state to the RmlUi context
	Rml::Context* ctx = GetContext();
	if (!ctx) return;

	// Get current mouse position from WickedEngine input
	wi::input::MouseState mouseState = wi::input::GetMouseState();

	// Mouse movement
	int newMouseX = (int)mouseState.position.x;
	int newMouseY = (int)mouseState.position.y;
	if (newMouseX != g_mouseX || newMouseY != g_mouseY)
	{
		ctx->ProcessMouseMove(newMouseX, newMouseY, 0);
		g_mouseX = newMouseX;
		g_mouseY = newMouseY;
	}

	// Mouse button states (0 = left, 1 = right, 2 = middle)
	static const int rmlButtons[] = { 0, 1, 2 };
	for (int i = 0; i < 3; i++)
	{
		bool pressed = wi::input::Down(wi::input::MOUSE_BUTTON_LEFT + i);
		if (pressed && !g_mouseButtonsPressed[i])
		{
			ctx->ProcessMouseButtonDown(rmlButtons[i], 0);
		}
		else if (!pressed && g_mouseButtonsPressed[i])
		{
			ctx->ProcessMouseButtonUp(rmlButtons[i], 0);
		}
		g_mouseButtonsPressed[i] = pressed;
	}

	// Mouse wheel
	if (mouseState.delta_wheel != 0)
	{
		ctx->ProcessMouseWheel(static_cast<float>(mouseState.delta_wheel), 0);
	}

	// Keyboard input: forward key press/release events to RmlUi
	// Compute the key modifier bitmask from the current modifier key states.
	int keyModifier = 0;
	if (wi::input::Down(wi::input::KEYBOARD_BUTTON_LSHIFT) || wi::input::Down(wi::input::KEYBOARD_BUTTON_RSHIFT))
		keyModifier |= Rml::Input::KM_SHIFT;
	if (wi::input::Down(wi::input::KEYBOARD_BUTTON_LCONTROL) || wi::input::Down(wi::input::KEYBOARD_BUTTON_RCONTROL))
		keyModifier |= Rml::Input::KM_CTRL;
	if (wi::input::Down(wi::input::KEYBOARD_BUTTON_ALT) || wi::input::Down(wi::input::KEYBOARD_BUTTON_ALTGR))
		keyModifier |= Rml::Input::KM_ALT;

	for (const auto& entry : g_keyMap)
	{
		bool down = wi::input::Down(entry.wickedKey);
		bool wasDown = g_keyPressed[entry.wickedKey];
		if (down && !wasDown)
		{
			ctx->ProcessKeyDown(entry.rmlKey, keyModifier);
		}
		else if (!down && wasDown)
		{
			ctx->ProcessKeyUp(entry.rmlKey, keyModifier);
		}
		g_keyPressed[entry.wickedKey] = down;
	}
	// Note: Text input (ProcessTextInput) requires platform-level character
	// messages. Use wi::rmlui::ProcessTextInput(wchar_t) from your WndProc's
	// WM_CHAR handler to inject characters. They are consumed here.

	// Consume any queued text input characters
	{
		std::vector<wchar_t> chars;
		{
			std::lock_guard<std::mutex> lock(g_textInputMutex);
			chars.swap(g_textInputQueue);
		}
		for (wchar_t ch : chars)
		{
			ctx->ProcessTextInput(static_cast<Rml::Character>(ch));
		}
	}

	// Update all contexts
	ctx->Update();
}

void Render(wi::graphics::CommandList cmd)
{
	if (!g_initialized) return;
	if (!g_shadersLoaded) return;

	g_renderInterface.SetCommandList(cmd);

	// Ensure the viewport matches the RmlUi context dimensions so that
	// the orthographic projection in RenderGeometry maps correctly.
	auto* device = GetDevice();
	if (device)
	{
		Viewport vp;
		vp.width = (float)g_width;
		vp.height = (float)g_height;
		vp.top_left_x = 0;
		vp.top_left_y = 0;
		vp.min_depth = 0;
		vp.max_depth = 1;
		device->BindViewports(1, &vp, cmd);
	}

	Rml::Context* ctx = GetContext();
	if (ctx)
	{
		ctx->Render();
	}

	// Restore scissor to full screen after RmlUi is done rendering
	if (device)
	{
		Rect full;
		full.left = 0;
		full.top = 0;
		full.right = g_width;
		full.bottom = g_height;
		device->BindScissorRects(1, &full, cmd);
	}
}

void Resize(int w, int h)
{
	g_width = w;
	g_height = h;

	if (!g_initialized) return;

	Rml::Context* ctx = GetContext();
	if (ctx)
	{
		ctx->SetDimensions(Rml::Vector2i(w, h));
	}
}

Rml::Context* GetContext()
{
	return Rml::GetContext(DEFAULT_CONTEXT);
}

Rml::Context* GetContext(const std::string& name)
{
	return Rml::GetContext(name);
}

Rml::Context* CreateContext(const std::string& name, int width, int height)
{
	if (!g_initialized) return nullptr;
	return Rml::CreateContext(name, Rml::Vector2i(width, height));
}

bool RemoveContext(const std::string& name)
{
	if (!g_initialized) return false;
	if (name == DEFAULT_CONTEXT) return false; // Don't allow removing default context
	return Rml::RemoveContext(name);
}

Rml::ElementDocument* LoadDocument(const std::string& path)
{
	if (!g_initialized) return nullptr;
	Rml::Context* ctx = GetContext();
	if (!ctx) return nullptr;
	return ctx->LoadDocument(path);
}

Rml::ElementDocument* LoadDocumentFromMemory(const std::string& rml, const std::string& source_url)
{
	if (!g_initialized) return nullptr;
	Rml::Context* ctx = GetContext();
	if (!ctx) return nullptr;
	return ctx->LoadDocumentFromMemory(rml, source_url);
}

void UnloadAllDocuments()
{
	if (!g_initialized) return;
	Rml::Context* ctx = GetContext();
	if (ctx) ctx->UnloadAllDocuments();
}

bool LoadFontFace(const std::string& path, bool fallback)
{
	if (!g_initialized) return false;
	return Rml::LoadFontFace(path, fallback);
}

Rml::EventListener* CreateLuaEventListener(int lua_function_ref)
{
	lua_State* L = wi::lua::GetLuaState();
	if (!L) return nullptr;
	return new LuaEventListener(lua_function_ref, L);
}

void DestroyLuaEventListener(Rml::EventListener* listener)
{
	delete listener;
}

void ProcessTextInput(wchar_t character)
{
	if (!g_initialized) return;
	std::lock_guard<std::mutex> lock(g_textInputMutex);
	g_textInputQueue.push_back(character);
}

} // namespace wi::rmlui
