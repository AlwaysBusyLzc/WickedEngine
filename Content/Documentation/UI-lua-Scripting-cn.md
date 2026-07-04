# RmlUi Lua 脚本接口文档（中文）

本文档描述了 RmlUi 与 WickedEngine 集成后暴露给 Lua 脚本的所有 API。

RmlUi 是一个 HTML/CSS 风格的 UI 库，通过本接口可以在 WickedEngine 中使用 RML（类 HTML）和 RCSS（类 CSS）创建用户界面。

## 目录

- [启用方式](#启用方式)
- [全局函数](#全局函数)
- [RmlContext 类](#rmlcontext-类)
- [RmlDocument 类](#rmldocument-类)
- [RmlElement 类](#rmlelement-类)
- [事件系统](#事件系统)
- [完整示例](#完整示例)

---

## 启用方式

RmlUi 集成需要在构建时启用 `WICKED_RMLUI` 选项：

```powershell
cmake -B build -DWICKED_RMLUI=ON
cmake --build build
```

启用后，引擎会在初始化阶段自动完成以下工作：

1. 初始化 RmlUi 系统（创建系统接口、渲染接口、文件接口和默认上下文）
2. 注册所有 Lua 绑定
3. 在 `RenderPath2D` 的每帧更新和渲染中自动调用 RmlUi 的 `Update` 和 `Render`

因此，**Lua 脚本通常不需要手动调用 `RmlInitialize`、`RmlUpdate` 或渲染函数**，只需加载字体和文档即可。

---

## 全局函数

### RmlInitialize()

初始化 RmlUi 系统。

> 引擎启动时已自动调用，脚本中通常不需要手动调用。

```lua
RmlInitialize()
```

**参数：** 无

**返回值：** 无

---

### RmlShutdown()

关闭 RmlUi 系统，释放所有资源。

```lua
RmlShutdown()
```

**参数：** 无

**返回值：** 无

---

### RmlUpdate(dt)

手动触发 RmlUi 的一次更新（处理输入、更新上下文）。

> 引擎每帧已自动调用，通常不需要手动调用。

```lua
RmlUpdate(dt)
```

**参数：**

| 参数 | 类型 | 说明 |
|------|------|------|
| `dt` | number | 帧间隔时间（秒） |

**返回值：** 无

---

### RmlResize(w, h)

设置 RmlUi 上下文的尺寸。

> 引擎在窗口缩放时已自动调用。

```lua
RmlResize(width, height)
```

**参数：**

| 参数 | 类型 | 说明 |
|------|------|------|
| `w` | int | 宽度（像素） |
| `h` | int | 高度（像素） |

**返回值：** 无

---

### RmlLoadFontFace(path, fallback)

加载字体文件。RmlUi 需要至少一个字体才能渲染文本。

```lua
local success = RmlLoadFontFace("Content/fonts/Roboto-Medium.ttf", true)
```

**参数：**

| 参数 | 类型 | 必需 | 说明 |
|------|------|------|------|
| `path` | string | 是 | 字体文件路径（TTF/OTF） |
| `fallback` | boolean | 否 | 是否作为回退字体，默认 `false` |

**返回值：** `boolean` — 加载成功返回 `true`，失败返回 `false`

---

### RmlLoadDocument(path)

从文件加载 RML 文档到默认上下文。

```lua
local doc = RmlLoadDocument("Content/rmlui/demo.rml")
```

**参数：**

| 参数 | 类型 | 说明 |
|------|------|------|
| `path` | string | RML 文件路径 |

**返回值：** `RmlDocument | nil` — 成功返回文档对象，失败返回 `nil`

---

### RmlLoadDocumentFromMemory(rml, url)

从字符串加载 RML 文档到默认上下文。

```lua
local rml_string = [[
<rml>
<head><title>内联文档</title></head>
<body>
  <div style="position: absolute; top: 100px; left: 100px; width: 200px; height: 100px; background: blue;">
    <p>Hello!</p>
  </div>
</body>
</rml>
]]
local doc = RmlLoadDocumentFromMemory(rml_string)
```

**参数：**

| 参数 | 类型 | 必需 | 说明 |
|------|------|------|------|
| `rml` | string | 是 | RML 内容字符串 |
| `url` | string | 否 | 源 URL（用于错误提示），默认 `"[document from memory]"` |

**返回值：** `RmlDocument | nil` — 成功返回文档对象，失败返回 `nil`

---

### RmlUnloadAllDocuments()

从默认上下文卸载所有文档。

```lua
RmlUnloadAllDocuments()
```

**参数：** 无

**返回值：** 无

---

### RmlGetContext(name)

获取 RmlUi 上下文。不传参数时获取默认上下文。

```lua
local ctx = RmlGetContext()          -- 获取默认上下文
local ctx = RmlGetContext("my_ctx")  -- 获取命名上下文
```

**参数：**

| 参数 | 类型 | 必需 | 说明 |
|------|------|------|------|
| `name` | string | 否 | 上下文名称，不传则获取默认上下文 |

**返回值：** `RmlContext | nil` — 存在则返回上下文对象，不存在返回 `nil`

---

### RmlTextInput(text)

向 RmlUi 注入文本输入。用于模拟键盘字符输入或 IME 输入。

> 此函数将字符串的每个字符依次注入 RmlUi 的文本输入队列，在下一帧 `Update` 时处理。对于真实的键盘文本输入，需要在应用程序的窗口消息处理器（如 Win32 的 `WM_CHAR`）中调用 C++ 接口 `wi::rmlui::ProcessTextInput(wchar_t)`。

```lua
RmlTextInput("Hello RmlUi!")
```

**参数：**

| 参数 | 类型 | 说明 |
|------|------|------|
| `text` | string | 要输入的文本 |

**返回值：** 无

---

## RmlContext 类

RmlUi 上下文，管理文档、输入和渲染。默认上下文由引擎自动创建。

通过 `RmlGetContext()` 获取实例。

### :GetName()

获取上下文名称。

```lua
local name = ctx:GetName()  -- "default"
```

**返回值：** `string` — 上下文名称

---

### :SetDimensions(w, h)

设置上下文尺寸（像素）。

```lua
ctx:SetDimensions(1920, 1080)
```

**参数：**

| 参数 | 类型 | 说明 |
|------|------|------|
| `w` | int | 宽度 |
| `h` | int | 高度 |

---

### :GetDimensions()

获取上下文尺寸。

```lua
local w, h = ctx:GetDimensions()
```

**返回值：** `int, int` — 宽度, 高度（多返回值）

---

### :Update()

手动触发上下文更新。

> 引擎每帧已自动调用。

```lua
ctx:Update()
```

---

### :Render()

手动触发上下文渲染。

> 引擎每帧已自动调用。

```lua
ctx:Render()
```

---

### :LoadDocument(path)

从文件加载 RML 文档到此上下文。

```lua
local doc = ctx:LoadDocument("Content/rmlui/demo.rml")
```

**参数：**

| 参数 | 类型 | 说明 |
|------|------|------|
| `path` | string | RML 文件路径 |

**返回值：** `RmlDocument | nil`

---

### :LoadDocumentFromMemory(rml, url)

从字符串加载 RML 文档到此上下文。

**参数：**

| 参数 | 类型 | 必需 | 说明 |
|------|------|------|------|
| `rml` | string | 是 | RML 内容 |
| `url` | string | 否 | 源 URL |

**返回值：** `RmlDocument | nil`

---

### :UnloadDocument(doc)

卸载指定文档。

```lua
ctx:UnloadDocument(doc)
```

**参数：**

| 参数 | 类型 | 说明 |
|------|------|------|
| `doc` | RmlDocument | 要卸载的文档 |

---

### :UnloadAllDocuments()

卸载此上下文中的所有文档。

```lua
ctx:UnloadAllDocuments()
```

---

### :GetDocument(id_or_index)

获取上下文中的文档。支持按 ID（字符串）或索引（整数）获取。

```lua
local doc = ctx:GetDocument("my_doc")  -- 按 ID 获取
local doc = ctx:GetDocument(0)          -- 按索引获取
```

**参数：**

| 参数 | 类型 | 说明 |
|------|------|------|
| `id_or_index` | string \| int | 文档 ID 或索引（从 0 开始） |

**返回值：** `RmlDocument | nil`

---

### :GetNumDocuments()

获取上下文中的文档数量。

```lua
local count = ctx:GetNumDocuments()
```

**返回值：** `int` — 文档数量

---

### :GetHoverElement()

获取当前鼠标悬停的元素。

```lua
local el = ctx:GetHoverElement()
```

**返回值：** `RmlElement | nil`

---

### :GetFocusElement()

获取当前获得焦点的元素。

```lua
local el = ctx:GetFocusElement()
```

**返回值：** `RmlElement | nil`

---

### :GetRootElement()

获取上下文的根元素。

```lua
local root = ctx:GetRootElement()
```

**返回值：** `RmlElement | nil`

---

### :PullDocumentToFront(doc)

将指定文档拉到最前。

```lua
ctx:PullDocumentToFront(doc)
```

**参数：**

| 参数 | 类型 | 说明 |
|------|------|------|
| `doc` | RmlDocument | 要操作的文档 |

---

### :PushDocumentToBack(doc)

将指定文档推到最后。

```lua
ctx:PushDocumentToBack(doc)
```

---

### :AddEventListener(event, callback, capture)

为整个上下文添加事件监听器。

```lua
ctx:AddEventListener("click", function(event)
    backlog_post("上下文收到点击事件")
end)
```

**参数：**

| 参数 | 类型 | 必需 | 说明 |
|------|------|------|------|
| `event` | string | 是 | 事件类型名称（如 `"click"`、`"keydown"`） |
| `callback` | function | 是 | 事件回调函数，接收一个 event 表参数 |
| `capture` | boolean | 否 | 是否使用捕获阶段，默认 `false` |

> 回调函数的参数详见 [事件系统](#事件系统)。

---

### :EnableMouseCursor(enabled)

启用或禁用鼠标光标。

```lua
ctx:EnableMouseCursor(true)
```

**参数：**

| 参数 | 类型 | 说明 |
|------|------|------|
| `enabled` | boolean | 是否启用 |

---

### :ActivateTheme(theme_name)

激活指定主题。

```lua
ctx:ActivateTheme("dark_theme")
```

**参数：**

| 参数 | 类型 | 说明 |
|------|------|------|
| `theme_name` | string | 主题名称 |

---

### :IsThemeActive(theme_name)

检查指定主题是否激活。

```lua
if ctx:IsThemeActive("dark_theme") then
    -- ...
end
```

**返回值：** `boolean`

---

## RmlDocument 类

RML 文档，继承自 `RmlElement`，因此拥有 `RmlElement` 的所有方法。

通过 `RmlLoadDocument()`、`ctx:LoadDocument()` 或 `ctx:GetDocument()` 获取实例。

### :GetTitle()

获取文档标题。

```lua
local title = doc:GetTitle()
```

**返回值：** `string`

---

### :SetTitle(title)

设置文档标题。

```lua
doc:SetTitle("我的 UI")
```

**参数：**

| 参数 | 类型 | 说明 |
|------|------|------|
| `title` | string | 标题 |

---

### :GetSourceURL()

获取文档的源 URL。

```lua
local url = doc:GetSourceURL()
```

**返回值：** `string`

---

### :Show(modal, focus)

显示文档。

```lua
doc:Show()                      -- 普通显示
doc:Show("modal")               -- 模态显示
doc:Show("modal", "auto")       -- 模态显示，自动获取焦点
doc:Show(nil, "none")           -- 非模态，不获取焦点
```

**参数：**

| 参数 | 类型 | 必需 | 说明 |
|------|------|------|------|
| `modal` | string | 否 | 模态标志：`"modal"`（模态）、`"keep"`（保持当前模态）、不传（非模态） |
| `focus` | string | 否 | 焦点标志：`"none"`、`"document"`、`"keep"`、`"auto"`（默认） |

---

### :Hide()

隐藏文档（不销毁，可再次 Show）。

```lua
doc:Hide()
```

---

### :Close()

关闭并销毁文档。

```lua
doc:Close()
```

---

### :PullToFront()

将文档拉到最前。

```lua
doc:PullToFront()
```

---

### :PushToBack()

将文档推到最后。

```lua
doc:PushToBack()
```

---

### :IsModal()

检查文档是否为模态。

```lua
if doc:IsModal() then
    -- 文档是模态的
end
```

**返回值：** `boolean`

---

### :UpdateDocument()

手动更新文档布局。

```lua
doc:UpdateDocument()
```

---

### :ReloadStyleSheet()

重新加载文档的样式表。

```lua
doc:ReloadStyleSheet()
```

---

## RmlElement 类

DOM 元素基类，`RmlDocument` 继承自此类。所有 UI 元素（div、button、p 等）都是 `RmlElement`。

通过 `doc:GetElementById()`、`el:GetFirstChild()` 等方法获取实例。

### 样式相关

#### :SetClass(class_name, enable)

添加或移除 CSS 类。

```lua
el:SetClass("highlight", true)   -- 添加类
el:SetClass("highlight", false)  -- 移除类
```

| 参数 | 类型 | 说明 |
|------|------|------|
| `class_name` | string | CSS 类名 |
| `enable` | boolean | `true` 添加，`false` 移除 |

---

#### :IsClassSet(class_name)

检查是否设置了某个 CSS 类。

```lua
if el:IsClassSet("highlight") then ... end
```

**返回值：** `boolean`

---

#### :SetClassNames(class_names)

设置元素的 CSS 类名列表（空格分隔）。

```lua
el:SetClassNames("btn btn-primary active")
```

| 参数 | 类型 | 说明 |
|------|------|------|
| `class_names` | string | 空格分隔的类名 |

---

#### :GetClassNames()

获取元素的 CSS 类名列表。

```lua
local classes = el:GetClassNames()
```

**返回值：** `string`

---

#### :SetProperty(name, value)

设置 CSS 属性。

```lua
el:SetProperty("background-color", "#ff0000")
el:SetProperty("display", "none")
el:SetProperty("width", "200px")
```

| 参数 | 类型 | 说明 |
|------|------|------|
| `name` | string | CSS 属性名 |
| `value` | string | CSS 属性值 |

---

#### :RemoveProperty(name)

移除 CSS 属性。

```lua
el:RemoveProperty("background-color")
```

---

#### :GetPropertyName(name)

获取 CSS 属性值的字符串表示。

```lua
local value = el:GetPropertyName("color")  -- 如 "#ffffff"
```

| 参数 | 类型 | 说明 |
|------|------|------|
| `name` | string | CSS 属性名 |

**返回值：** `string | nil` — 属性值字符串，属性不存在返回 `nil`

---

#### :SetPseudoClass(name, enable)

设置伪类状态。

```lua
el:SetPseudoClass("hover", true)
```

---

#### :IsPseudoClassSet(name)

检查伪类是否设置。

```lua
if el:IsPseudoClassSet("hover") then ... end
```

**返回值：** `boolean`

---

### 属性相关

#### :SetAttribute(name, value)

设置 HTML 属性。支持字符串、整数、浮点数、布尔值。

```lua
el:SetAttribute("data-id", "123")
el:SetAttribute("max", 100)
el:SetAttribute("enabled", true)
```

| 参数 | 类型 | 说明 |
|------|------|------|
| `name` | string | 属性名 |
| `value` | string \| int \| number \| boolean | 属性值 |

---

#### :GetAttribute(name)

获取属性值。返回值类型取决于属性原始类型。

```lua
local id = el:GetAttribute("data-id")     -- 可能返回 string
local max = el:GetAttribute("max")        -- 可能返回 int
local enabled = el:GetAttribute("enabled") -- 可能返回 boolean
```

**返回值：** `string | int | number | boolean | nil` — 属性值，属性不存在返回 `nil`

---

#### :HasAttribute(name)

检查属性是否存在。

```lua
if el:HasAttribute("disabled") then ... end
```

**返回值：** `boolean`

---

#### :RemoveAttribute(name)

移除属性。

```lua
el:RemoveAttribute("disabled")
```

---

#### :GetNumAttributes()

获取属性数量。

```lua
local count = el:GetNumAttributes()
```

**返回值：** `int`

---

### DOM 属性

#### :GetTagName()

获取标签名（如 `"div"`、`"button"`、`"p"`）。

```lua
local tag = el:GetTagName()
```

**返回值：** `string`

---

#### :GetId()

获取元素 ID。

```lua
local id = el:GetId()
```

**返回值：** `string`

---

#### :SetId(id)

设置元素 ID。

```lua
el:SetId("my_element")
```

---

#### :IsVisible(include_ancestors)

检查元素是否可见。

```lua
local visible = el:IsVisible()          -- 仅检查自身
local visible = el:IsVisible(true)      -- 检查包括祖先
```

| 参数 | 类型 | 必需 | 说明 |
|------|------|------|------|
| `include_ancestors` | boolean | 否 | 是否检查祖先元素，默认 `false` |

**返回值：** `boolean`

---

#### :GetInnerRML()

获取元素内部的 RML 内容。

```lua
local rml = el:GetInnerRML()
```

**返回值：** `string`

---

#### :SetInnerRML(rml)

设置元素内部的 RML 内容。

```lua
el:SetInnerRML("<p>新内容</p>")
```

---

#### :Focus(focus_visible)

使元素获得焦点。

```lua
el:Focus()
el:Focus(true)  -- 同时显示焦点指示
```

| 参数 | 类型 | 必需 | 说明 |
|------|------|------|------|
| `focus_visible` | boolean | 否 | 是否显示焦点指示，默认 `false` |

**返回值：** `boolean`

---

#### :Blur()

使元素失去焦点。

```lua
el:Blur()
```

---

#### :Click()

模拟点击元素。

```lua
el:Click()
```

---

### DOM 层次遍历

#### :GetParentNode()

获取父元素。

```lua
local parent = el:GetParentNode()
```

**返回值：** `RmlElement | nil`

---

#### :GetNextSibling()

获取下一个兄弟元素。

```lua
local sibling = el:GetNextSibling()
```

**返回值：** `RmlElement | nil`

---

#### :GetPreviousSibling()

获取上一个兄弟元素。

```lua
local sibling = el:GetPreviousSibling()
```

**返回值：** `RmlElement | nil`

---

#### :GetFirstChild()

获取第一个子元素。

```lua
local child = el:GetFirstChild()
```

**返回值：** `RmlElement | nil`

---

#### :GetLastChild()

获取最后一个子元素。

```lua
local child = el:GetLastChild()
```

**返回值：** `RmlElement | nil`

---

#### :GetChild(index)

按索引获取子元素。

```lua
local child = el:GetChild(0)  -- 第一个子元素
```

| 参数 | 类型 | 说明 |
|------|------|------|
| `index` | int | 子元素索引（从 0 开始） |

**返回值：** `RmlElement | nil`

---

#### :GetNumChildren(include_non_dom)

获取子元素数量。

```lua
local count = el:GetNumChildren()
local count = el:GetNumChildren(true)  -- 包括非 DOM 节点
```

| 参数 | 类型 | 必需 | 说明 |
|------|------|------|------|
| `include_non_dom` | boolean | 否 | 是否包括非 DOM 节点，默认 `false` |

**返回值：** `int`

---

#### :HasChildNodes()

检查是否有子节点。

```lua
if el:HasChildNodes() then ... end
```

**返回值：** `boolean`

---

#### :GetElementById(id)

在子树中按 ID 查找元素。

```lua
local button = el:GetElementById("submit_btn")
```

**返回值：** `RmlElement | nil`

---

#### :QuerySelector(selector)

通过 CSS 选择器查找元素。

```lua
local el = root:QuerySelector("div.container > button.primary")
```

| 参数 | 类型 | 说明 |
|------|------|------|
| `selector` | string | CSS 选择器 |

**返回值：** `RmlElement | nil`

---

### 事件相关

#### :AddEventListener(event, callback, capture)

为元素添加事件监听器。

```lua
button:AddEventListener("click", function(event)
    backlog_post("按钮被点击！")
end)
```

| 参数 | 类型 | 必需 | 说明 |
|------|------|------|------|
| `event` | string | 是 | 事件类型 |
| `callback` | function | 是 | 回调函数 |
| `capture` | boolean | 否 | 是否使用捕获阶段，默认 `false` |

> 回调函数参数详见 [事件系统](#事件系统)。

---

#### :DispatchEvent(type, params)

触发自定义事件。

```lua
local result = el:DispatchEvent("custom_update", {
    value = 42,
    message = "hello"
})
```

| 参数 | 类型 | 必需 | 说明 |
|------|------|------|------|
| `type` | string | 是 | 事件类型名称 |
| `params` | table | 否 | 事件参数（键值对，值支持 string/int/number/boolean） |

**返回值：** `boolean` — 事件是否被处理

---

### 布局信息

#### :GetOffsetWidth()

获取元素偏移宽度（包含边框和滚动条）。

```lua
local w = el:GetOffsetWidth()
```

**返回值：** `int`（像素）

---

#### :GetOffsetHeight()

获取元素偏移高度。

```lua
local h = el:GetOffsetHeight()
```

**返回值：** `int`

---

#### :GetOffsetLeft()

获取元素相对偏移父元素的左边距。

```lua
local left = el:GetOffsetLeft()
```

**返回值：** `int`

---

#### :GetOffsetTop()

获取元素相对偏移父元素的上边距。

```lua
local top = el:GetOffsetTop()
```

**返回值：** `int`

---

#### :GetClientWidth()

获取元素客户区宽度（不包含边框和滚动条）。

```lua
local w = el:GetClientWidth()
```

**返回值：** `int`

---

#### :GetClientHeight()

获取元素客户区高度。

```lua
local h = el:GetClientHeight()
```

**返回值：** `int`

---

#### :GetScrollLeft()

获取水平滚动位置。

```lua
local scroll = el:GetScrollLeft()
```

**返回值：** `int`

---

#### :SetScrollLeft(value)

设置水平滚动位置。

```lua
el:SetScrollLeft(100)
```

---

#### :GetScrollTop()

获取垂直滚动位置。

```lua
local scroll = el:GetScrollTop()
```

**返回值：** `int`

---

#### :SetScrollTop(value)

设置垂直滚动位置。

```lua
el:SetScrollTop(100)
```

---

#### :GetScrollWidth()

获取滚动内容总宽度。

```lua
local w = el:GetScrollWidth()
```

**返回值：** `int`

---

#### :GetScrollHeight()

获取滚动内容总高度。

```lua
local h = el:GetScrollHeight()
```

**返回值：** `int`

---

#### :ScrollIntoView(align_top)

将元素滚动到可视区域。

```lua
el:ScrollIntoView()
el:ScrollIntoView(false)  -- 底部对齐
```

| 参数 | 类型 | 必需 | 说明 |
|------|------|------|------|
| `align_top` | boolean | 否 | `true` 顶部对齐（默认），`false` 底部对齐 |

---

### 关联获取

#### :GetOwnerDocument()

获取元素所属的文档。

```lua
local doc = el:GetOwnerDocument()
```

**返回值：** `RmlDocument | nil`

---

#### :GetContext()

获取元素所属的上下文。

```lua
local ctx = el:GetContext()
```

**返回值：** `RmlContext | nil`

---

### 动画

#### :Animate(prop, value, duration)

为属性启动动画过渡。

```lua
el:Animate("opacity", "0.0", 0.5)  -- 0.5 秒淡出
el:Animate("width", "300px", 1.0)  -- 1 秒宽度变化
```

| 参数 | 类型 | 说明 |
|------|------|------|
| `prop` | string | CSS 属性名 |
| `value` | string | 目标值 |
| `duration` | number | 动画时长（秒） |

**返回值：** `boolean` — 动画是否成功启动

---

## 事件系统

### 事件回调

通过 `AddEventListener` 注册的回调函数会接收一个事件表参数：

```lua
element:AddEventListener("click", function(event)
    -- event 是一个 Lua table，包含以下字段：
    print(event.type)        -- 事件类型字符串，如 "click"
    print(event.id)          -- 事件 ID（整数）
    print(event.target_tag)  -- 目标元素标签名，如 "button"
    print(event.target_id)   -- 目标元素 ID
end)
```

### 事件表字段

| 字段 | 类型 | 说明 |
|------|------|------|
| `type` | string | 事件类型名称 |
| `id` | int | 事件 ID（数值） |
| `target_tag` | string | 触发事件的元素标签名 |
| `target_id` | string | 触发事件的元素 ID |

### 常见事件类型

以下是 RmlUi 支持的常见事件类型（不完整列表）：

| 事件 | 说明 |
|------|------|
| `click` | 鼠标点击 |
| `mousedown` | 鼠标按下 |
| `mouseup` | 鼠标释放 |
| `mouseover` | 鼠标移入 |
| `mouseout` | 鼠标移出 |
| `mousemove` | 鼠标移动 |
| `focus` | 获得焦点 |
| `blur` | 失去焦点 |
| `keydown` | 键盘按下 |
| `keyup` | 键盘释放 |
| `textinput` | 文本输入 |
| `change` | 值改变（表单元素） |
| `submit` | 表单提交 |
| `resize` | 尺寸改变 |
| `scroll` | 滚动 |
| `load` | 文档加载完成 |
| `unload` | 文档卸载 |
| `animationend` | 动画结束 |

---

## 完整示例

### 基本示例

```lua
-- rmlui_basic.lua
-- RmlUi 基本使用示例

-- 加载字体（必须）
RmlLoadFontFace("Content/fonts/Roboto-Medium.ttf", true)

-- 从文件加载文档
local doc = RmlLoadDocument("Content/rmlui/demo.rml")
if doc then
    doc:Show()
    doc:SetTitle("RmlUi 演示")

    -- 获取按钮并添加点击事件
    local button = doc:GetElementById("test_button")
    if button then
        button:AddEventListener("click", function(event)
            backlog_post("[RmlUi] 按钮被点击！")
            backlog_post("[RmlUi] 目标元素: " .. event.target_tag .. " #" .. event.target_id)
        end)
    end

    backlog_post("[RmlUi] 文档加载成功")
else
    backlog_post("[RmlUi] 文档加载失败")
end
```

### 动态创建 UI

```lua
-- rmlui_dynamic.lua
-- 从字符串动态创建 UI

RmlLoadFontFace("Content/fonts/Roboto-Medium.ttf", true)

local rml = [[
<rml>
<head>
    <title>动态 UI</title>
    <style>
        body {
            font-family: Roboto;
            font-size: 16px;
            color: white;
        }
        #container {
            position: absolute;
            top: 50px;
            left: 50px;
            width: 300px;
            background: rgba(20, 20, 30, 0.9);
            border: 1px solid #4488ff;
            border-radius: 8px;
            padding: 20px;
        }
        button {
            display: block;
            margin: 10px 0;
            padding: 8px 16px;
            background: #4488ff;
            color: white;
            border: none;
            border-radius: 4px;
            cursor: pointer;
        }
        button:hover {
            background: #66aaff;
        }
        #output {
            color: #88ff88;
            margin-top: 10px;
        }
    </style>
</head>
<body>
    <div id="container">
        <h1>动态 UI 示例</h1>
        <button id="btn1">按钮 1</button>
        <button id="btn2">按钮 2</button>
        <button id="btn_toggle">切换可见性</button>
        <div id="output">点击按钮试试</div>
        <div id="extra" style="display: none;">
            这是额外内容，点击"切换可见性"可以显示/隐藏。
        </div>
    </div>
</body>
</rml>
]]

local doc = RmlLoadDocumentFromMemory(rml)
if doc then
    doc:Show()

    local output = doc:GetElementById("output")
    local extra = doc:GetElementById("extra")

    -- 按钮事件
    doc:GetElementById("btn1"):AddEventListener("click", function()
        output:SetInnerRML("你点击了按钮 1")
    end)

    doc:GetElementById("btn2"):AddEventListener("click", function()
        output:SetInnerRML("你点击了按钮 2")
    end)

    -- 切换可见性
    local visible = false
    doc:GetElementById("btn_toggle"):AddEventListener("click", function()
        visible = not visible
        if visible then
            extra:SetProperty("display", "block")
        else
            extra:SetProperty("display", "none")
        end
    end)

    -- 动画示例
    output:AddEventListener("click", function()
        output:Animate("opacity", "0.3", 0.5)
    end)
end
```

### 上下文事件监听

```lua
-- rmlui_events.lua
-- 上下文级事件监听示例

RmlLoadFontFace("Content/fonts/Roboto-Medium.ttf", true)

local doc = RmlLoadDocument("Content/rmlui/demo.rml")
doc:Show()

-- 获取默认上下文
local ctx = RmlGetContext()

-- 监听整个上下文的点击事件
ctx:AddEventListener("click", function(event)
    backlog_post("[RmlUi] 全局点击: " .. event.target_tag .. " #" .. event.target_id)
end)

-- 监听键盘事件
ctx:AddEventListener("keydown", function(event)
    backlog_post("[RmlUi] 键盘按下，事件类型: " .. event.type)
end)
```

### 操作文档元素

```lua
-- rmlui_elements.lua
-- 遍历和操作 DOM 元素示例

RmlLoadFontFace("Content/fonts/Roboto-Medium.ttf", true)

local doc = RmlLoadDocument("Content/rmlui/demo.rml")
doc:Show()

-- 获取根元素
local root = doc:GetElementById("root")

-- 遍历所有子元素
local count = root:GetNumChildren()
for i = 0, count - 1 do
    local child = root:GetChild(i)
    if child then
        backlog_post("子元素 " .. i .. ": " .. child:GetTagName())
    end
end

-- 使用 CSS 选择器
local button = root:QuerySelector("button")
if button then
    -- 修改样式
    button:SetProperty("background-color", "#ff4444")
    button:SetProperty("font-size", "18px")

    -- 添加 CSS 类
    button:SetClass("active", true)

    -- 设置属性
    button:SetAttribute("data-count", 0)

    -- 获取布局信息
    local w = button:GetOffsetWidth()
    local h = button:GetOffsetHeight()
    backlog_post(string.format("按钮尺寸: %dx%d", w, h))
end

-- 触发自定义事件
local result = root:DispatchEvent("custom_init", {
    timestamp = os.time(),
    source = "lua_script"
})
```

### 文档管理

```lua
-- rmlui_documents.lua
-- 多文档管理示例

RmlLoadFontFace("Content/fonts/Roboto-Medium.ttf", true)

local ctx = RmlGetContext()

-- 加载多个文档
local doc1 = ctx:LoadDocument("Content/rmlui/demo.rml")
local doc2 = ctx:LoadDocument("Content/rmlui/overlay.rml")

doc1:Show()
doc2:Show("modal")  -- 模态显示

-- 获取文档数量
backlog_post("文档数量: " .. ctx:GetNumDocuments())

-- 按索引获取文档
local firstDoc = ctx:GetDocument(0)

-- 按标题查找文档
for i = 0, ctx:GetNumDocuments() - 1 do
    local d = ctx:GetDocument(i)
    if d:GetTitle() == "RmlUi Demo" then
        d:PullToFront()
        break
    end
end

-- 关闭所有文档
-- ctx:UnloadAllDocuments()
```

---

## 注意事项

1. **字体加载**：RmlUi 需要至少加载一个字体才能渲染文本。使用 `RmlLoadFontFace()` 加载。

2. **自动更新和渲染**：引擎在 `RenderPath2D` 中自动调用 `RmlUpdate` 和 `RmlRender`，脚本无需手动调用。

3. **文本输入**：Lua 的 `RmlTextInput()` 可用于模拟文本输入。真实的键盘字符输入需要在 C++ 层从窗口消息（如 Win32 的 `WM_CHAR`）调用 `wi::rmlui::ProcessTextInput(wchar_t)`。

4. **继承关系**：`RmlDocument` 继承自 `RmlElement`，因此所有 `RmlElement` 的方法都可以在 `RmlDocument` 上调用。

5. **返回 nil 的情况**：当元素、文档或上下文不存在时，相关方法返回 `nil`。使用前应检查。

6. **事件回调**：事件回调中收到的 `event` 参数是一个 Lua table，不是 RmlEvent 对象。

7. **属性类型**：`SetAttribute` 和 `GetAttribute` 支持多种类型。`GetAttribute` 的返回值类型取决于属性设置时使用的类型。
