# RmlUi 集成说明

本文档描述了 RmlUi 与 WickedEngine 的集成方式。

## 构建启用

在 CMake 配置时启用 `WICKED_RMLUI` 选项：

```powershell
cmake -B build -DWICKED_RMLUI=ON
cmake --build build
```

该选项会：
- 编译 RmlUi 库（启用 C++ 异常和 RTTI）
- 编译 `wiRmlUi.cpp`（引擎集成模块）
- 单独编译 `wiRmlUi_BindLua.cpp`（启用异常，sol2 要求）
- 链接 sol2（header-only，位于 `WickedEngine/third_party/sol2/`）

## 架构

### 文件结构

| 文件 | 说明 |
|------|------|
| `WickedEngine/wiRmlUi.h` | 引擎模块公共接口 |
| `WickedEngine/wiRmlUi.cpp` | 引擎集成实现（渲染管线、输入、纹理） |
| `WickedEngine/wiRmlUi_BindLua.h` | Lua 绑定声明 |
| `WickedEngine/wiRmlUi_BindLua.cpp` | sol2 Lua 绑定实现 |
| `WickedEngine/shaders/RmlUiVS.hlsl` | RmlUi 顶点着色器 |
| `WickedEngine/shaders/RmlUiPS.hlsl` | RmlUi 像素着色器 |
| `Content/rmlui/demo.rml` | 示例 RML 文档 |
| `Content/rmlui/demo.rcss` | 示例 RCSS 样式表 |
| `Content/scripts/rmlui_test.lua` | Lua 测试脚本 |
| `Content/fonts/Roboto-Medium.ttf` | 示例字体 |

### 引擎集成点

- **初始化**：`wiInitializer.cpp` — 在 Lua 初始化后调用 `wi::rmlui::Initialize()`
- **Lua 绑定**：`wiLua.cpp` — 在 `Initialize()` 中调用 `wi::lua::rmlui::Bind()`
- **每帧更新**：`wiRenderPath2D.cpp::Update()` — 调用 `wi::rmlui::Update(dt)`
- **渲染**：`wiRenderPath2D.cpp::Compose()` — 调用 `wi::rmlui::Render(cmd)`
- **窗口缩放**：`wiRenderPath2D.cpp::Update()` — 调用 `wi::rmlui::Resize(w, h)`

## 渲染实现

### 顶点格式

RmlUi 的 `Rml::Vertex` 结构（20 字节）：
```
offset 0:  Vector2f position      (R32G32_FLOAT)
offset 8:  ColourbPremultiplied   (R8G8B8A8_UNORM)
offset 12: Vector2f tex_coord     (R32G32_FLOAT)
```

### 着色器

- **RmlUiVS.hlsl**：正交投影 × 平移变换，`row_major` 矩阵
- **RmlUiPS.hlsl**：纹理采样 × 顶点颜色（预乘 alpha）

### 混合状态

预乘 alpha 混合：
- `SRC_BLEND = ONE`
- `DEST_BLEND = INV_SRC_ALPHA`

## 输入处理

### 鼠标
自动从 `wi::input::GetMouseState()` 转发：
- 鼠标移动 → `ProcessMouseMove`
- 三键点击 → `ProcessMouseButtonDown/Up`
- 滚轮 → `ProcessMouseWheel`

### 键盘
自动从 `wi::input::Down()` 转发（49 个按键映射）：
- 边沿检测触发 `ProcessKeyDown/Up`
- 修饰键状态（Ctrl/Shift/Alt）

### 文本输入
需要从平台窗口消息处理器注入：

**Windows (WndProc)**：
```cpp
case WM_CHAR:
    wi::rmlui::ProcessTextInput((wchar_t)wParam);
    break;
```

**Lua 脚本**：
```lua
RmlTextInput("Hello RmlUi!")
```

## Lua API

### 全局函数
- `RmlInitialize()` — 初始化 RmlUi
- `RmlShutdown()` — 关闭 RmlUi
- `RmlUpdate(dt)` — 手动更新（通常自动调用）
- `RmlResize(w, h)` — 设置上下文尺寸
- `RmlLoadFontFace(path, fallback?)` — 加载字体
- `RmlLoadDocument(path)` → `RmlDocument` — 加载 RML 文档
- `RmlLoadDocumentFromMemory(rml, url?)` → `RmlDocument` — 从字符串加载
- `RmlUnloadAllDocuments()` — 卸载所有文档
- `RmlGetContext(name?)` → `RmlContext` — 获取上下文
- `RmlTextInput(text)` — 注入文本输入

### 类层次
```
RmlContext  → RmlDocument : RmlElement
RmlElement  → RmlDocument (继承)
```

### RmlContext 方法
`GetName`, `SetDimensions`, `GetDimensions`, `Update`, `Render`,
`LoadDocument`, `LoadDocumentFromMemory`, `UnloadDocument`,
`UnloadAllDocuments`, `GetDocument`, `GetNumDocuments`,
`GetHoverElement`, `GetFocusElement`, `GetRootElement`,
`PullDocumentToFront`, `PushDocumentToBack`,
`AddEventListener`, `EnableMouseCursor`, `ActivateTheme`, `IsThemeActive`

### RmlElement 方法
- **样式**：`SetClass`, `IsClassSet`, `SetClassNames`, `GetClassNames`,
  `SetProperty`, `RemoveProperty`, `GetPropertyName`, `SetPseudoClass`, `IsPseudoClassSet`
- **属性**：`SetAttribute`, `GetAttribute`, `HasAttribute`, `RemoveAttribute`, `GetNumAttributes`
- **DOM**：`GetTagName`, `GetId`, `SetId`, `IsVisible`, `GetInnerRML`, `SetInnerRML`,
  `Focus`, `Blur`, `Click`
- **层次**：`GetParentNode`, `GetNextSibling`, `GetPreviousSibling`,
  `GetFirstChild`, `GetLastChild`, `GetChild`, `GetNumChildren`, `HasChildNodes`,
  `GetElementById`, `QuerySelector`
- **事件**：`AddEventListener`, `DispatchEvent`
- **布局**：`GetOffsetWidth/Height/Left/Top`, `GetClientWidth/Height`,
  `GetScrollLeft/Top`, `SetScrollLeft/Top`, `GetScrollWidth/Height`, `ScrollIntoView`
- **动画**：`Animate`

### RmlDocument 方法（继承 RmlElement）
`GetTitle`, `SetTitle`, `GetSourceURL`, `Show`, `Hide`, `Close`,
`PullToFront`, `PushToBack`, `IsModal`, `UpdateDocument`, `ReloadStyleSheet`

## 示例

```lua
-- 初始化（引擎已自动初始化，此调用安全）
RmlInitialize()

-- 加载字体
RmlLoadFontFace("Content/fonts/Roboto-Medium.ttf", true)

-- 加载并显示文档
local doc = RmlLoadDocument("Content/rmlui/demo.rml")
if doc then
    doc:Show()
    doc:SetTitle("My UI")

    -- 事件监听
    local button = doc:GetElementById("test_button")
    if button then
        button:AddEventListener("click", function(event)
            backlog_post("Button clicked: " .. event.type)
        end)
    end
end
```

## 注意事项

1. **异常隔离**：WickedEngine 全局禁用异常和 RTTI。RmlUi 和 `wiRmlUi_BindLua.cpp`
   单独编译时启用 `/EHsc`（异常）和 `/GR`（RTTI），不影响引擎其他代码。

2. **着色器编译**：RmlUi 着色器（`.hlsl`）会在首次运行时由引擎的着色器编译器
   自动编译为 `.cso`。无需手动编译。

3. **高级功能**：以下 RmlUi 高级功能使用基类默认空实现，不影响基本 UI：
   - CSS `transform` 属性
   - 图层混合（`PushLayer`/`PopLayer`）
   - CSS 滤镜
   - 自定义着色器装饰器
   - 裁剪遮罩

4. **字体**：RmlUi 使用内置的 FreeType 字体引擎。字体通过 `RmlLoadFontFace()` 加载。
