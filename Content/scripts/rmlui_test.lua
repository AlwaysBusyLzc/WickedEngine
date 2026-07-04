-- rmlui_test.lua
-- Example script demonstrating RmlUi integration with WickedEngine
-- This script loads an RML document and sets up event listeners.

-- Initialize RmlUi (normally done automatically by the engine, but safe to call again)
RmlInitialize()

-- Load a font face (required for text rendering)
-- Adjust the path to point to a TTF font file in your content
RmlLoadFontFace("Content/fonts/Roboto-Medium.ttf", true)

-- Resize to current canvas dimensions
local canvas = application.GetCanvas()
RmlResize(canvas.GetPhysicalWidth(), canvas.GetPhysicalHeight())

-- Load the demo RML document
local doc = RmlLoadDocument("Content/rmlui/demo.rml")
if doc then
    -- Show the document
    doc:Show()
    
    -- Set the title
    doc:SetTitle("RmlUi Demo")
    
    -- Find a button element and add a click listener
    local button = doc:GetElementById("test_button")
    if button then
        button:AddEventListener("click", function(event)
            backlog_post("[RmlUi] Button clicked! Event type: ", event.type)
        end)
    end
    
    -- Find the root element and add a general click listener
    local root = doc:GetElementById("root")
    if root then
        root:AddEventListener("click", function(event)
            backlog_post("[RmlUi] Root clicked, target: ", event.target_tag, " id: ", event.target_id)
        end)
    end
    
    backlog_post("[RmlUi] Demo document loaded successfully!")
else
    backlog_post("[RmlUi] Failed to load demo.rml - make sure the file exists at Content/rmlui/demo.rml")
end

-- You can also create documents from memory:
-- local doc2 = RmlLoadDocumentFromMemory([[
-- <rml>
-- <head><title>Inline Document</title></head>
-- <body>
--   <div style="position: absolute; top: 100px; left: 100px; width: 200px; height: 100px; background: blue;">
--     <p>Hello from inline RML!</p>
--   </div>
-- </body>
-- </rml>
-- ]])
-- if doc2 then doc2:Show() end

-- The RmlUi update and render are called automatically by the engine's RenderPath2D.
-- You don't need to call RmlUpdate() or render manually in the normal case.

-- Text input: To enable text entry in RmlUi input fields, add the following
-- to your application's WndProc (or equivalent platform character handler):
--
--   case WM_CHAR:
--       wi::rmlui::ProcessTextInput((wchar_t)wParam);
--       break;
--
-- From Lua, you can simulate text input with RmlTextInput(string):
-- RmlTextInput("Hello RmlUi!")

backlog_post("[RmlUi] Test script loaded. Press HOME to open the backlog console.")
