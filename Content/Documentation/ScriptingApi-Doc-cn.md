# Wicked Engine 脚本 API 文档

![Wicked Engine logo](../logo_small.png)

这是 Wicked Engine 中 Lua 脚本功能的参考和说明。

- [编辑器手册](WickedEditor-Manual.pdf)
- [C++ 文档](WickedEngine-Documentation.md)

完整的 API 参考在下方，按主题组织，其后是将此文档用作编辑器 IntelliSense 的说明。

## 目录

- [简介与用法](#简介与用法)
  - [阅读本文档](#阅读本文档)
- [编辑器支持（自动补全和类型检查）](#编辑器支持自动补全和类型检查)
- [编辑本文档](#编辑本文档)
- [实用工具](#实用工具)
- [引擎绑定](#引擎绑定)
  - [BackLog](#backlog)
  - [Renderer](#renderer)
    - [PaintTextureParams](#painttextureparams)
    - [PaintDecalParams](#paintdecalparams)
  - [Sprite](#sprites-and-fonts)
    - [ImageParams](#imageparams)
    - [SpriteAnim](#spriteanim)
    - [MovingTexAnim](#movingtexanim)
    - [DrawRectAnim](#drawrectanim)
  - [SpriteFont](#spritefont)
  - [Texture](#texture)
    - [texturehelper](#texturehelper)
  - [Audio](#audio)
    - [Sound](#sound)
    - [SoundInstance](#soundinstance)
    - [SoundInstance3D](#soundinstance3d)
    - [Submix 类型](#submix-类型)
    - [Reverb 类型](#reverb-类型)
  - [Video](#video)
    - [Video](#video-1)
    - [VideoInstance](#videoinstance)
  - [Vector](#math-types)
  - [Matrix](#matrix)
  - [Async](#async)
  - [场景系统（使用实体-组件系统）](#场景系统使用实体-组件系统)
    - [Entity](#entity)
    - [Scene](#scene)
    - [RayIntersectionResult](#rayintersectionresult)
    - [SphereIntersectionResult](#sphereintersectionresult)
    - [NameComponent](#namecomponent)
    - [LayerComponent](#layercomponent)
    - [TransformComponent](#transformcomponent)
    - [CameraComponent](#cameracomponent)
    - [AnimationComponent](#animationcomponent)
    - [MaterialComponent](#materialcomponent)
    - [MeshComponent](#meshcomponent)
    - [EmitterComponent](#emittercomponent)
    - [HairParticleSystem](#hairparticlesystem)
    - [LightComponent](#lightcomponent)
    - [ObjectComponent](#objectcomponent)
    - [InverseKinematicsComponent](#inversekinematicscomponent)
    - [SpringComponent](#springcomponent)
    - [ScriptComponent](#scriptcomponent)
    - [RigidBodyPhysicsComponent](#rigidbodyphysicscomponent)
    - [SoftBodyPhysicsComponent](#softbodyphysicscomponent)
    - [ForceFieldComponent](#forcefieldcomponent)
    - [WeatherComponent](#weathercomponent)
      - [OceanParameters](#oceanparameters)
      - [AtmosphereParameters](#atmosphereparameters)
      - [VolumetricCloudParameters](#volumetriccloudparameters)
    - [SoundComponent](#soundcomponent)
    - [VideoComponent](#videocomponent)
    - [ColliderComponent](#collidercomponent)
    - [ExpressionComponent](#expressioncomponent)
    - [HumanoidComponent](#humanoidcomponent)
    - [DecalComponent](#decalcomponent)
    - [MetadataComponent](#metadatacomponent)
    - [CharacterComponent](#charactercomponent)
  - [Canvas](#canvas)
  - [高层接口](#高层接口)
    - [Application](#application)
    - [RenderPath](#renderpath)
      - [RenderPath2D : RenderPath](#renderpath2d--renderpath)
      - [RenderPath3D : RenderPath2D](#renderpath3d--renderpath2d)
      - [LoadingScreen : RenderPath2D](#loadingscreen--renderpath2d)
  - [图元](#primitives)
    - [Ray](#ray)
    - [AABB](#aabb)
    - [Sphere](#sphere)
    - [Capsule](#capsule)
  - [输入](#input)
    - [ControllerFeedback](#controllerfeedback)
    - [Touch](#touch)
    - [TOUCHSTATE](#touchstate)
    - [键盘键码](#keyboard-key-codes)
    - [鼠标键码](#mouse-key-codes)
    - [游戏手柄键码](#gamepad-key-codes)
      - [通用按键码](#generic-button-codes)
      - [Xbox 按键码](#xbox-button-codes)
      - [PlayStation 按键码](#playstation-button-codes)
    - [游戏手柄模拟码](#gamepad-analog-codes)
    - [控制器偏好](#controller-preference)
    - [光标码](#cursor-codes)
  - [物理](#physics)
    - [PickDragOperation](#pickdragoperation)
  - [寻路](#path-finding)
    - [VoxelGrid](#voxelgrid)
    - [PathQuery](#pathquery)
  - [TrailRenderer](#trailrenderer)
  - [Network](#network)

## 简介与用法

Wicked Engine 的脚本功能由 Lua 驱动，意味着用户可以利用灵活而强大的 Lua 语言的语法和功能。除了常见功能外，某些引擎功能也可供使用。你可以加载 lua 脚本文件并执行它们，或者引擎脚本控制台（也称为 BackLog）也可用于执行单行脚本（你也可以在此处通过 dofile 命令执行文件脚本）。启动时，引擎将尝试在应用程序根目录中加载名为 startup.lua 的启动脚本文件。如果未找到，将抛出错误消息，随后程序正常执行。在启动文件中，你可以指定任何启动逻辑，例如加载内容或其他任何操作。

BackLog 映射到键盘上的 HOME 按钮。这将拉下一个界面，可以在其中用键盘输入 lua 命令。ENTER 键将执行输入的命令。再次按 HOME 键将退出 BackLog。

- 提示：你可以通过调用 getprops(YourObject) 来检查任何对象的功能（其中 YourObject 是要检查的对象）。结果将显示在 BackLog 上。

### 阅读本文档

每个部分中的 API 都描述为带注释的 Lua，放在 ` ```lua ` 代码块中，使用 [LuaLS](https://luals.github.io/)（EmmyLua）注释，以便编辑器可以显示类型和签名：

- 一个类及其方法：

```lua
    --- Vector 类描述。
    ---
    ---@class Vector
    ---
    ---@field X number
    local Vector = {}

    --- 返回两个向量的点积。
    ---
    ---@param v1 Vector
    ---@param v2 Vector
    ---
    ---@return number
    function Vector.Dot(v1, v2) end
```

- 构造函数是返回该类型的全局函数，例如 `function Vector(x, y, z, w) end`。
- 全局函数和值没有类前缀（例如 `function GetScene()`、`application`）。
- 可选参数用 `?` 标记（例如 `---@param layer? string`）。
- 枚举使用 `---@enum`；替代调用签名使用 `---@overload`。

## 编辑器支持（自动补全和类型检查）

因为本文档中的每个绑定都编写为带注释的 Lua，它可以被转换为 [Lua Language Server](https://luals.github.io/) 定义，这样你就可以在自己的 Lua 项目中获得整个脚本 API 的自动补全、签名和类型检查（例如使用 *sumneko.lua* VS Code 扩展）。

### 1. 生成定义

只需要 Python 3（无依赖项）：

```sh
cd Content/Documentation/scripting_api
python3 generate_stubs.py
```

这将生成一个包含整个 API 的 `wicked_engine_bindings.lua`。想要每个主题一个文件？运行 `python3 generate_stubs.py --split`，它会改为写入 `library/wicked_engine/<topic>.lua`。

### 2. 安装到你的项目中

将 `wicked_engine_bindings.lua` 复制到你的项目中，例如 `library/` 目录：

```text
your_project/
  .luarc.json
  library/
    wicked_engine_bindings.lua
  your_scripts.lua
```

文档更改后重新运行生成器并再次复制。

### 3. 配置 `.luarc.json`

在项目根目录创建一个 `.luarc.json`，将语言服务器指向定义：

```json
{
  "$schema": "https://raw.githubusercontent.com/LuaLS/vscode-lua/master/setting/schema.json",
  "workspace": {
    "library": ["library/wicked_engine_bindings.lua"],
    "checkThirdParty": false
  },
  "runtime": {
    "version": "Lua 5.4"
  }
}
```

`workspace.library` 是唯一必需的条目 — 它让语言服务器加载定义。有了它，整个引擎脚本 API 都会被识别：定义声明了引擎全局对象（`vector`、`matrix`、`application`、`main`、`audio`、`input`、`physics`、`texturehelper`）以及每个引擎全局函数、常量和枚举，因此你不需要列出其中任何一个。

如果你自己的项目使用了未在任何 `.lua` 文件中定义的全局变量，请在 `diagnostics.globals` 下添加它们，这样它们就不会被报告为未定义，例如：

```json
  "diagnostics": {
    "globals": [ "my_custom_global", "MY_CONSTANT" ]
  }
```

（你的代码在工作区文件中*赋值*的全局变量 — 例如 `scene = GetScene()` — 已经被识别，不需要列出。）

## 编辑本文档

此 Markdown 文档是真实来源；生成的定义是从它派生的。

- 将每个绑定为带注释的 Lua 记录在围栏 `lua` 块中（参见[阅读本文档](#阅读本文档)了解约定）。
- 将每个绑定放在适当的标题下；生成器按文档顺序提取每个 `lua` 块。
- 用 `---@diagnostic disable: ...` 行作为块的第一行来标记说明性*用法*代码片段（非 API 定义）；生成器会跳过这些，所以它们不会出现在定义中。
- 编辑后，重新运行 `generate_stubs.py`，理想情况下用 `lua-language-server --check wicked_engine_bindings.lua` 验证。

## 实用工具

本节描述了脚本编写中常用的工具，这些工具不一定是引擎功能。

这些是一些帮助调试的辅助工具：

用于确定当前平台的辅助工具，如果需要实现特定功能：

```lua
    --- 全局发送信号。如果有进程在等待同一信号名称，这可以唤醒它们。
    ---
    ---@param name string
    function signal(name) end

    --- 等待直到指定信号到达。
    ---
    ---@param name string
    function waitSignal(name) end

    --- 启动新进程。
    ---
    ---@param func fun()
    ---
    ---@return boolean success
    ---@return thread co
    function runProcess(func) end

    --- 停止并移除所有进程。
    function killProcesses() end

    --- 停止并移除单个进程，通过其协程标识。
    ---
    ---@param co thread
    function killProcess(co) end

    --- 停止并移除从给定脚本 PID 启动的所有进程。
    ---
    ---@param pid integer
    function killProcessPID(pid) end

    --- 停止并移除从给定脚本文件启动的所有进程。
    ---
    ---@param file string
    function killProcessFile(file) end

    --- 等待一段时间过去（从进程内部使用）。
    ---
    ---@param seconds number
    function waitSeconds(seconds) end

    --- 从对象获取反射数据。
    ---
    ---@param object table
    function getprops(object) end

    --- 获取表的长度。
    ---
    ---@param object table
    ---
    ---@return integer
    function len(object) end

    --- 将表内容发布到 backlog。
    ---
    ---@param list table
    function backlog_post_list(list) end

    --- 修改日志级别。
    ---
    ---@param level LogLevel
    function backlog_setlevel(level) end

    --- backlog/控制台日志消息的严重性级别。
    ---
    ---@enum LogLevel
    LogLevel = {
        None = 0,
        Default = 1,
        Warning = 2,
        Error = 3,
        Success = 4,
    }

    --- 等待固定更新步骤被调用（从进程内部使用）。
    function fixedupdate() end

    --- 等待可变更新步骤被调用（从进程内部使用）。
    function update() end

    --- 等待渲染步骤被调用（从进程内部使用）。
    function render() end

    --- 返回以秒为单位的增量时间（自上次 update() 以来经过的时间）。
    ---
    ---@return number
    function getDeltaTime() end

    --- 线性插值。
    ---
    ---@param a number
    ---@param b number
    ---@param t number
    ---
    ---@return number
    function math.lerp(a, b, t) end

    --- 反向线性插值。
    ---
    ---@param a number
    ---@param b number
    ---@param t number
    ---
    ---@return number
    function math.inverse_lerp(a, b, t) end

    --- 反向线性插值。
    ---
    ---@param a number
    ---@param b number
    ---@param t number
    ---
    ---@return number
    function math.inverselerp(a, b, t) end

    --- 将 x 限制在 min 和 max 之间。
    ---
    ---@param x number
    ---@param min number
    ---@param max number
    ---
    ---@return number
    function math.clamp(x, min, max) end

    --- 将 x 限制在 0 和 1 之间。
    ---
    ---@param x number
    ---
    ---@return number
    function math.saturate(x) end

    --- 将 x 四舍五入到最接近的整数。
    ---
    ---@param x number
    ---
    ---@return number
    function math.round(x) end

    --- 执行二进制 LUA 文件。
    ---
    ---@param filename string
    function dobinaryfile(filename) end

    --- 将文本 LUA 文件 (filename_src) 编译为二进制 LUA 文件
    --- (filename_dst)。
    ---
    ---@param filename_src string
    ---@param dilename_dst string
    function compilebinaryfile(filename_src, dilename_dst) end

    --- 如果当前应用程序是编辑器则返回 true，否则返回 false。
    ---
    ---@return boolean
    function IsThisEditor() end

    --- 将控制权返回给编辑器并终止正在运行的脚本。
    function ReturnToEditor() end

    --- 如果这是调试构建则返回 true，否则返回 false。
    ---
    ---@return boolean
    function IsThisDebugBuild() end

    --- 返回是否为 Windows 平台。
    ---
    ---@return boolean
    function IsPlatformWindows() end

    --- 返回是否为 Linux 平台。
    ---
    ---@return boolean
    function IsPlatformLinux() end

    --- 返回是否为 macOS 平台。
    ---
    ---@return boolean
    function IsPlatformMACOS() end

    --- 返回是否为 iOS 平台。
    ---
    ---@return boolean
    function IsPlatformIOS() end

    --- 返回是否为 PS5 平台。
    ---
    ---@return boolean
    function IsPlatformPS5() end

    --- 返回是否为 Xbox 平台。
    ---
    ---@return boolean
    function IsPlatformXBOX() end

    --- 返回给定路径是否存在文件。
    ---
    ---@param name string
    ---
    ---@return boolean
    function FileExists(name) end

    --- 返回给定路径是否存在目录。
    ---
    ---@param name string
    ---
    ---@return boolean
    function DirectoryExists(name) end

    --- 在给定路径创建目录（包括父目录）。
    ---
    ---@param name string
    function DirectoryCreate(name) end

    --- 返回一个可以在每个平台上安全保存文件的路径。这是此类路径
    --- 的基础目录；文件应保存在其中以应用程序特定命名的文件夹中。
    ---
    ---@return string
    function GetSaveDataPath() end

    --- 返回引擎主版本号。
    ---
    ---@return integer
    function GetVersionMajor() end

    --- 返回引擎次版本号。
    ---
    ---@return integer
    function GetVersionMinor() end

    --- 返回引擎修订版本号。
    ---
    ---@return integer
    function GetVersionRevision() end

    --- 返回完整的引擎版本字符串。
    ---
    ---@return string
    function GetVersionString() end

    --- 返回引擎致谢文本。
    ---
    ---@return string
    function GetCreditsString() end

    --- 返回引擎支持者文本。
    ---
    ---@return string
    function GetSupportersString() end

    --- 返回当前运行脚本的文件路径
    --- （如果不可用则为空字符串）。
    ---
    ---@return string
    function script_file() end

    --- 返回当前运行脚本的目录
    --- （如果不可用则为空字符串）。
    ---
    ---@return string
    function script_dir() end

    --- 返回当前运行脚本的进程 ID (PID)
    --- （如果不可用则为 0）。
    ---
    ---@return integer
    function script_pid() end
```

## 引擎绑定

脚本 API 提供了让开发者操作引擎行为或查询信息的函数。

### BackLog

BackLog 是引擎的脚本控制台：用键盘输入文本并用 RETURN 键运行；脚本错误也显示在此处。这些函数在全局作用域中并操作 BackLog。

```lua
    --- 清除 backlog 中的所有条目。
    function backlog_clear() end

    --- 将字符串发布到 backlog。
    ---
    ---@param params string
    function backlog_post(params) end

    --- 设置 backlog 的字体大小。
    ---
    ---@param size integer
    function backlog_fontsize(size) end

    --- 返回 backlog 当前是否活动（可见）。
    ---
    ---@return boolean
    function backlog_isactive() end

    --- 设置 backlog 文本的行间距。
    ---
    ---@param spacing integer
    function backlog_fontrowspacing(spacing) end

    --- 打开（显示）backlog 控制台。
    function backlog_open() end

    --- 禁用并锁定 backlog，使 HOME 键无法调出它。
    function backlog_lock() end

    --- 解锁 backlog，使其可以用 HOME 键切换。
    function backlog_unlock() end

    --- 禁用从 backlog 执行 Lua 代码。
    function backlog_blocklua() end

    --- 重新启用从 backlog 执行 Lua 代码。
    function backlog_unblocklua() end

    --- 立即刷新待处理的 backlog 消息。
    function backlog_flush() end

    --- 设置 backlog 自动刷新待处理消息的间隔（以毫秒为单位）。
    ---
    ---@param milliseconds integer
    function backlog_setautoflushinterval(milliseconds) end
```

### Renderer

渲染器管理渲染、场景图和调试绘制。以下所有函数都在全局作用域中（没有 `Renderer` 对象）。

```lua
    --- 返回当前游戏速度倍数。
    ---
    ---@return number
    function GetGameSpeed() end

    --- 设置游戏速度倍数（1 = 正常速度）。
    ---
    ---@param speed number
    function SetGameSpeed(speed) end

    --- 已弃用：不再支持 gamma。
    ---
    ---@deprecated
    ---
    ---@param value number
    function SetGamma(value) end

    --- 已弃用：分辨率现在由窗口事件处理。
    ---
    ---@deprecated
    function SetResolution() end

    --- 启用或禁用垂直同步。
    ---
    ---@param enabled boolean
    function SetVSyncEnabled(enabled) end

    --- 返回图形设备是否支持硬件光线追踪。
    ---
    ---@return boolean
    function IsRaytracingSupported() end

    --- 重新加载所有着色器。
    function ReloadShaders() end

    --- 清除场景和关联的渲染器资源。如果未给定场景，则清除
    --- 全局场景。
    ---
    ---@param scene? Scene
    function ClearWorld(scene) end

    --- 已弃用：改用 application.GetCanvas().GetLogicalWidth()。
    ---
    ---@deprecated
    ---
    ---@return number
    function GetScreenWidth() end

    --- 已弃用：改用 application.GetCanvas().GetLogicalHeight()。
    ---
    ---@deprecated
    ---
    ---@return number
    function GetScreenHeight() end

    --- 设置 2D（聚光灯和点光源）阴影贴图的分辨率。
    ---
    ---@param resolution integer
    function SetShadowProps2D(resolution) end

    --- 设置立方体贴图（点光源）阴影贴图的分辨率。
    ---
    ---@param resolution integer
    function SetShadowPropsCube(resolution) end

    --- 启用或禁用每对象阴影细节级别覆盖。
    ---
    ---@param value boolean
    function SetShadowLODOverrideEnabled(value) end

    --- 启用或禁用遮挡剔除。
    ---
    ---@param enabled boolean
    function SetOcclusionCullingEnabled(enabled) end

    --- 启用或禁用 meshlet 遮挡剔除。
    ---
    ---@param value boolean
    function SetMeshletOcclusionCullingEnabled(value) end

    --- 允许或不允许使用网格着色器（如果支持）。
    ---
    ---@param enabled boolean
    function SetMeshShaderAllowed(enabled) end

    --- 启用或禁用时间抗锯齿 (TAA)。
    ---
    ---@param value boolean
    function SetTemporalAAEnabled(value) end

    --- 启用或禁用光线追踪阴影（需要硬件光线追踪）。
    ---
    ---@param value boolean
    function SetRaytracedShadowsEnabled(value) end

    --- 启用或禁用 DDGI（动态漫反射全局光照）。
    ---
    ---@param value boolean
    function SetDDGIEnabled(value) end

    --- 启用或禁用胶囊阴影。
    ---
    ---@param enabled boolean
    function SetCapsuleShadowEnabled(enabled) end

    --- 设置胶囊阴影淡出距离。
    ---
    ---@param value number
    function SetCapsuleShadowFade(value) end

    --- 设置胶囊阴影锥角，以弧度为单位。
    ---
    ---@param value number
    function SetCapsuleShadowAngle(value) end

    --- 启用或禁用渲染器的所有调试绘制。
    ---
    ---@param value boolean
    function SetDebugDrawEnabled(value) end

    --- 启用或禁用对象边界框绘制。
    ---
    ---@param enabled boolean
    function SetDebugBoxesEnabled(enabled) end

    --- 启用或禁用空间分区树绘制。
    ---
    ---@param enabled boolean
    function SetDebugPartitionTreeEnabled(enabled) end

    --- 启用或禁用骨架骨骼绘制。
    ---
    ---@param enabled boolean
    function SetDebugBonesEnabled(enabled) end

    --- 启用或禁用粒子发射器绘制。
    ---
    ---@param enabled boolean
    function SetDebugEmittersEnabled(enabled) end

    --- 启用或禁用环境探针绘制。
    ---
    ---@param enabled boolean
    function SetDebugEnvProbesEnabled(enabled) end

    --- 启用或禁用力场绘制。
    ---
    ---@param enabled boolean
    function SetDebugForceFieldsEnabled(enabled) end

    --- 启用或禁用相机绘制。
    ---
    ---@param value boolean
    function SetDebugCamerasEnabled(value) end

    --- 启用或禁用碰撞器绘制。
    ---
    ---@param value boolean
    function SetDebugCollidersEnabled(value) end

    --- 启用或禁用光源剔除调试可视化。
    ---
    ---@param enabled boolean
    function SetDebugLightCulling(enabled) end

    --- 启用或禁用网格辅助器叠加层。
    ---
    ---@param value boolean
    function SetGridHelperEnabled(value) end

    --- 启用或禁用 DDGI 调试可视化。
    ---
    ---@param value boolean
    function SetDDGIDebugEnabled(value) end

    --- 排队一条从 origin 到 end_ 的调试线，在当前帧绘制。
    ---
    ---@param origin Vector
    ---@param end_ Vector
    ---@param color? Vector
    ---@param depth? boolean
    function DrawLine(origin, end_, color, depth) end

    --- 排队一个调试点，在当前帧绘制。
    ---
    ---@param origin Vector
    ---@param size? number
    ---@param color? Vector
    ---@param depth? boolean
    function DrawPoint(origin, size, color, depth) end

    --- 排队一个由 boxMatrix 变换的调试线框立方体，在当前帧绘制。
    ---
    ---@param boxMatrix Matrix
    ---@param color? Vector
    ---@param depth? boolean
    function DrawBox(boxMatrix, color, depth) end

    --- 排队一个调试线框球体，在当前帧绘制。
    ---
    ---@param sphere Sphere
    ---@param color? Vector
    ---@param depth? boolean
    function DrawSphere(sphere, color, depth) end

    --- 排队一个调试线框胶囊体，在当前帧绘制。
    ---
    ---@param capsule Capsule
    ---@param color? Vector
    ---@param depth? boolean
    function DrawCapsule(capsule, color, depth) end

    --- 在世界位置排队调试文本，在当前帧绘制。
    --- flags 是 DEBUG_TEXT_* 值的组合。
    ---
    ---@param text string
    ---@param position? Vector
    ---@param color? Vector
    ---@param scaling? number
    ---@param flags? integer
    function DrawDebugText(text, position, color, scaling, flags) end

    --- 调试文本可以被场景几何体遮挡（深度测试）。
    ---
    ---@type integer
    DEBUG_TEXT_DEPTH_TEST = 1

    --- 调试文本旋转以始终面向相机。
    ---
    ---@type integer
    DEBUG_TEXT_CAMERA_FACING = 2

    --- 调试文本无论距离如何都保持恒定的屏幕大小。
    ---
    ---@type integer
    DEBUG_TEXT_CAMERA_SCALING = 4

    --- 在调试渲染阶段绘制体素网格。在此之前 VoxelGrid 对象
    --- 不能被销毁。
    ---
    ---@param voxelgrid VoxelGrid
    function DrawVoxelGrid(voxelgrid) end

    --- 在调试渲染阶段绘制路径查询。在此之前 PathQuery 对象
    --- 不能被销毁。
    ---
    ---@param pathquery PathQuery
    function DrawPathQuery(pathquery) end

    --- 在调试渲染阶段绘制轨迹。在此之前 TrailRenderer 对象
    --- 不能被销毁。
    ---
    ---@param trail TrailRenderer
    function DrawTrail(trail) end

    --- 使用给定的 PaintTextureParams 将笔触绘制到纹理中。
    ---
    ---@param params PaintTextureParams
    function PaintIntoTexture(params) end

    --- 创建一个可用作 PaintIntoTexture 目标的纹理。
    ---
    ---@param width integer
    ---@param height integer
    ---@param mips? integer
    ---@param initialColor? Vector
    ---
    ---@return Texture
    function CreatePaintableTexture(width, height, mips, initialColor) end

    --- 使用对象的 UV 映射将纹理通过贴花矩阵投影绘制到纹理中
    --- （一种在运行时烘焙蒙皮贴花的方式）。
    ---
    ---@param params PaintDecalParams
    function PaintDecalIntoObjectSpaceTexture(params) end

    --- 使用默认嵌入资源放置水波纹。
    ---
    ---@param position Vector
    ---
    ---@overload fun(imagename: string, position: Vector)
    function PutWaterRipple(position) end
```

#### PaintTextureParams

```lua
    --- 创建一个 PaintTextureParams 对象。
    ---
    ---@return PaintTextureParams
    function PaintTextureParams() end

    --- 描述 PaintIntoTexture 笔触的参数。
    ---
    ---@class PaintTextureParams
    local PaintTextureParams = {}

    --- 设置被编辑（绘制到）的纹理。
    ---
    ---@param tex Texture
    function PaintTextureParams.SetEditTexture(tex) end

    --- 设置画笔纹理（印章形状/图案）。
    ---
    ---@param tex Texture
    function PaintTextureParams.SetBrushTexture(tex) end

    --- 设置显示纹理（用于显示型绘制）。
    ---
    ---@param tex Texture
    function PaintTextureParams.SetRevealTexture(tex) end

    --- 设置画笔颜色。
    ---
    ---@param value Vector
    function PaintTextureParams.SetBrushColor(value) end

    --- 设置画笔中心，以像素为单位。
    ---
    ---@param value Vector
    function PaintTextureParams.SetCenterPixel(value) end

    --- 设置画笔半径，以像素为单位。
    ---
    ---@param value integer
    function PaintTextureParams.SetBrushRadius(value) end

    --- 设置画笔强度（每次笔触应用的量）。
    ---
    ---@param value number
    function PaintTextureParams.SetBrushAmount(value) end

    --- 设置画笔边缘平滑度。
    ---
    ---@param value number
    function PaintTextureParams.SetBrushSmoothness(value) end

    --- 设置画笔旋转，以弧度为单位。
    ---
    ---@param value number
    function PaintTextureParams.SetBrushRotation(value) end

    --- 设置画笔形状。
    ---
    ---@param value integer
    function PaintTextureParams.SetBrushShape(value) end
```

#### PaintDecalParams

```lua
    --- 创建一个 PaintDecalParams 对象。
    ---
    ---@return PaintDecalParams
    function PaintDecalParams() end

    --- 描述用 PaintDecalIntoObjectSpaceTexture 烘焙到对象纹理中的
    --- 贴花参数。
    ---
    ---@class PaintDecalParams
    local PaintDecalParams = {}

    --- 设置源纹理（贴花图像）。
    ---
    ---@param tex Texture
    function PaintDecalParams.SetInTexture(tex) end

    --- 设置目标纹理（对象的纹理）。
    ---
    ---@param tex Texture
    function PaintDecalParams.SetOutTexture(tex) end

    --- 设置世界空间中的贴花矩阵。
    ---
    ---@param mat Matrix
    function PaintDecalParams.SetMatrix(mat) end

    --- 设置目标对象实体；位置和 UV 从中获取。
    ---
    ---@param entity Entity
    function PaintDecalParams.SetObject(entity) end

    --- 根据表面相对于贴花投影的坡度调整贴花淡出
    --- （默认 0：无坡度混合）。
    ---
    ---@param power number
    function PaintDecalParams.SetSlopeBlendPower(power) end
```

### Sprites and Fonts

#### Sprite

```lua
    --- 构造一个精灵，可选从纹理和遮罩纹理文件创建。
    ---
    ---@param texture? string
    ---@param maskTexture? string
    ---
    ---@return Sprite
    function Sprite(texture, maskTexture) end

    --- 在屏幕上渲染图像。
    ---
    ---@class Sprite
    ---
    ---@field Params ImageParams
    ---@field Anim SpriteAnim
    local Sprite = {}

    --- 设置精灵的渲染参数（位置、大小、颜色等）。
    ---
    ---@param effects ImageParams
    function Sprite.SetParams(effects) end

    --- 返回精灵的渲染参数。
    ---
    ---@return ImageParams
    function Sprite.GetParams() end

    --- 设置驱动此精灵的动画辅助器。
    ---
    ---@param anim SpriteAnim
    function Sprite.SetAnim(anim) end

    --- 返回精灵的动画辅助器。
    ---
    ---@return SpriteAnim
    function Sprite.GetAnim() end

    --- 设置基础颜色纹理。
    ---
    ---@param texture Texture
    function Sprite.SetTexture(texture) end

    --- 返回基础颜色纹理。
    ---
    ---@return Texture
    function Sprite.GetTexture() end

    --- 设置遮罩纹理（与基础颜色相乘）。
    ---
    ---@param texture Texture
    function Sprite.SetMaskTexture(texture) end

    --- 返回遮罩纹理。
    ---
    ---@return Texture
    function Sprite.GetMaskTexture() end

    --- 设置背景纹理（由背景效果使用）。
    ---
    ---@param texture Texture
    function Sprite.SetBackgroundTexture(texture) end

    --- 返回背景纹理。
    ---
    ---@return Texture
    function Sprite.GetBackgroundTexture() end

    --- 显示或隐藏精灵。
    ---
    ---@param value boolean
    function Sprite.SetHidden(value) end

    --- 返回精灵是否隐藏。
    ---
    ---@return boolean
    function Sprite.IsHidden() end
```

##### ImageParams

指定 Sprite 属性，如位置、大小、颜色和效果。

```lua
    --- 构造图像参数。用两个数字调用时它们是宽度和高度（位置为 0, 0）；
    --- 用三个或四个调用时它们是 posX、posY、宽度和高度。
    --- 默认值：位置 (0, 0)，大小 (100, 100)。
    ---
    ---@param posX number
    ---@param posY number
    ---@param width number
    ---@param height? number
    ---
    ---@return ImageParams
    ---
    ---@overload fun(width: number, height?: number): ImageParams
    function ImageParams(posX, posY, width, height) end

    ---@class ImageParams
    ---@field Pos Vector
    ---@field Size Vector
    ---@field Pivot Vector
    ---@field Color Vector
    ---@field Opacity number
    ---@field Fade number
    ---@field Rotation number
    ---@field TexOffset Vector
    ---@field TexOffset2 Vector
    local ImageParams = {}

    --- 返回位置。
    ---
    ---@return Vector
    function ImageParams.GetPos() end

    --- 返回大小。
    ---
    ---@return Vector
    function ImageParams.GetSize() end

    --- 返回轴心点（旋转/缩放原点，在大小 [0, 1] 范围内）。
    ---
    ---@return Vector
    function ImageParams.GetPivot() end

    --- 返回颜色/色调 (RGBA)。
    ---
    ---@return Vector
    function ImageParams.GetColor() end

    --- 返回不透明度（alpha 乘数）。
    ---
    ---@return number
    function ImageParams.GetOpacity() end

    --- 返回饱和度。
    ---
    ---@return number
    function ImageParams.GetSaturation() end

    --- 返回淡出量（0：可见，1：完全淡出）。
    ---
    ---@return number
    function ImageParams.GetFade() end

    --- 返回弧度为单位的旋转。
    ---
    ---@return number
    function ImageParams.GetRotation() end

    --- 返回纹理 UV 偏移。
    ---
    ---@return Vector
    function ImageParams.GetTexOffset() end

    --- 返回次纹理 UV 偏移。
    ---
    ---@return Vector
    function ImageParams.GetTexOffset2() end

    --- 返回边界柔化量。
    ---
    ---@return number
    function ImageParams.GetBorderSoften() end

    --- 返回绘制矩形 (x, y, width, height)，以纹理像素为单位。
    ---
    ---@return Vector
    function ImageParams.GetDrawRect() end

    --- 返回次绘制矩形 (x, y, width, height)。
    ---
    ---@return Vector
    function ImageParams.GetDrawRect2() end

    --- 返回绘制矩形是否启用。
    ---
    ---@return boolean
    function ImageParams.IsDrawRectEnabled() end

    --- 返回次绘制矩形是否启用。
    ---
    ---@return boolean
    function ImageParams.IsDrawRect2Enabled() end

    --- 返回水平镜像是否启用。
    ---
    ---@return boolean
    function ImageParams.IsMirrorEnabled() end

    --- 返回背景模糊是否启用。
    ---
    ---@return boolean
    function ImageParams.IsBackgroundBlurEnabled() end

    --- 返回背景是否启用。
    ---
    ---@return boolean
    function ImageParams.IsBackgroundEnabled() end

    --- 返回扭曲遮罩是否启用。
    ---
    ---@return boolean
    function ImageParams.IsDistortionMaskEnabled() end

    --- 设置位置。
    ---
    ---@param pos Vector
    function ImageParams.SetPos(pos) end

    --- 设置大小。
    ---
    ---@param size Vector
    function ImageParams.SetSize(size) end

    --- 设置轴心点（旋转/缩放原点，在大小 [0, 1] 范围内）。
    ---
    ---@param value Vector
    function ImageParams.SetPivot(value) end

    --- 设置颜色/色调 (RGBA)。
    ---
    ---@param value Vector
    function ImageParams.SetColor(value) end

    --- 设置不透明度（alpha 乘数）。
    ---
    ---@param opacity number
    function ImageParams.SetOpacity(opacity) end

    --- 设置饱和度。
    ---
    ---@param saturation number
    function ImageParams.SetSaturation(saturation) end

    --- 设置淡出量（0：可见，1：完全淡出）。
    ---
    ---@param fade number
    function ImageParams.SetFade(fade) end

    --- 设置模板测试模式和参考值。
    ---
    ---@param stencilMode integer STENCILMODE_* 常量之一
    ---@param stencilRef integer
    function ImageParams.SetStencil(stencilMode, stencilRef) end

    --- 设置模板参考值的解释方式。
    ---
    ---@param stencilRefMode integer STENCILREFMODE_* 常量之一
    function ImageParams.SetStencilRefMode(stencilRefMode) end

    --- 设置混合模式（BLENDMODE_* 常量之一）。
    ---
    ---@param blendMode integer
    function ImageParams.SetBlendMode(blendMode) end

    --- 设置采样质量（QUALITY_* 常量之一）。
    ---
    ---@param quality integer
    function ImageParams.SetQuality(quality) end

    --- 设置纹理寻址模式（SAMPLEMODE_* 常量之一）。
    ---
    ---@param sampleMode integer
    function ImageParams.SetSampleMode(sampleMode) end

    --- 设置弧度为单位的旋转。
    ---
    ---@param rotation number
    function ImageParams.SetRotation(rotation) end

    --- 设置纹理 UV 偏移。
    ---
    ---@param value Vector
    function ImageParams.SetTexOffset(value) end

    --- 设置次纹理 UV 偏移。
    ---
    ---@param value Vector
    function ImageParams.SetTexOffset2(value) end

    --- 设置边界柔化量。
    ---
    ---@param alpha number
    function ImageParams.SetBorderSoften(alpha) end

    --- 启用绘制矩形 (x, y, width, height)，以纹理像素为单位。
    ---
    ---@param value Vector
    function ImageParams.EnableDrawRect(value) end

    --- 启用次绘制矩形 (x, y, width, height)。
    ---
    ---@param value Vector
    function ImageParams.EnableDrawRect2(value) end

    --- 禁用绘制矩形。
    function ImageParams.DisableDrawRect() end

    --- 禁用次绘制矩形。
    function ImageParams.DisableDrawRect2() end

    --- 启用水平镜像。
    function ImageParams.EnableMirror() end

    --- 禁用水平镜像。
    function ImageParams.DisableMirror() end

    --- 启用背景模糊效果。
    function ImageParams.EnableBackgroundBlur() end

    --- 禁用背景模糊效果。
    function ImageParams.DisableBackgroundBlur() end

    --- 启用背景绘制。
    function ImageParams.EnableBackground() end

    --- 禁用背景绘制。
    function ImageParams.DisableBackground() end

    --- 启用将遮罩纹理用作扭曲遮罩。
    function ImageParams.EnableDistortionMask() end

    --- 禁用扭曲遮罩。
    function ImageParams.DisableDistortionMask() end

    --- 设置遮罩时使用的 alpha 范围（起始和结束阈值）。
    ---
    ---@param start number
    ---@param end_ number
    function ImageParams.SetMaskAlphaRange(start, end_) end

    --- 返回遮罩 alpha 范围作为起始、结束。
    ---
    ---@return number range_start
    ---@return number range_end
    function ImageParams.GetMaskAlphaRange() end

    --- 设置角度柔化效果的方向。
    ---
    ---@param value Vector
    function ImageParams.SetAngularSoftnessDirection(value) end

    --- 设置角度柔化效果的内角。
    ---
    ---@param value number
    function ImageParams.SetAngularSoftnessInnerAngle(value) end

    --- 设置角度柔化效果的外角。
    ---
    ---@param value number
    function ImageParams.SetAngularSoftnessOuterAngle(value) end

    --- 启用双面角度柔化。
    function ImageParams.EnableAngularSoftnessDoubleSided() end

    --- 反转角度柔化效果。
    function ImageParams.EnableAngularSoftnessInverse() end

    --- 禁用双面角度柔化。
    function ImageParams.DisableAngularSoftnessDoubleSided() end

    --- 禁用反转角度柔化。
    function ImageParams.DisableAngularSoftnessInverse() end

    --- 启用圆角。
    function ImageParams.EnableCornerRounding() end

    --- 禁用圆角。
    function ImageParams.DisableCornerRounding() end

    --- 设置一个角 (0-3) 的圆角半径和分段数。
    ---
    ---@param corner integer 角索引，在 [0, 3] 范围内
    ---@param rounding number 角半径
    ---@param segments? integer 细分数量（默认 18）
    function ImageParams.SetCornerRounding(corner, rounding, segments) end

    --- 在两个 UV 坐标之间用渐变填充图像。
    ---
    ---@param type ImageGradientType
    ---@param uv_start Vector
    ---@param uv_end Vector
    ---@param color Vector
    function ImageParams.SetGradient(type, uv_start, uv_end, color) end
```

以下常量和枚举由 ImageParams 设置器使用：

```lua
    -- 模板比较模式（与 SetStencil 一起使用）。
    STENCILMODE_DISABLED = 0
    STENCILMODE_EQUAL = 1
    STENCILMODE_LESS = 2
    STENCILMODE_LESSEQUAL = 3
    STENCILMODE_GREATER = 4
    STENCILMODE_GREATEREQUAL = 5
    STENCILMODE_NOT = 6
    STENCILMODE_ALWAYS = 7

    -- 模板参考值的解释方式（与 SetStencilRefMode 一起使用）。
    STENCILREFMODE_ENGINE = 0
    STENCILREFMODE_USER = 1
    STENCILREFMODE_ALL = 2

    -- 纹理寻址模式（与 SetSampleMode 一起使用）。
    SAMPLEMODE_CLAMP = 0
    SAMPLEMODE_WRAP = 1
    SAMPLEMODE_MIRROR = 2

    -- 采样质量（与 SetQuality 一起使用）。
    QUALITY_NEAREST = 0
    QUALITY_LINEAR = 1
    QUALITY_ANISOTROPIC = 2
    QUALITY_BICUBIC = 3

    -- 混合模式（与 SetBlendMode 一起使用）。
    BLENDMODE_OPAQUE = 0
    BLENDMODE_ALPHA = 1
    BLENDMODE_PREMULTIPLIED = 2
    BLENDMODE_ADDITIVE = 3

    ---@enum ImageGradientType
    ImageGradientType = {
        None = 0,
        Linear = 1,
        LinearReflected = 2,
        Circular = 3,
    }
```

##### SpriteAnim

```lua
    --- 构造一个精灵动画辅助器。
    ---
    ---@return SpriteAnim
    function SpriteAnim() end

    --- 用此辅助器轻松地为精灵制作动画。
    ---
    ---@class SpriteAnim
    ---
    ---@field Rot number
    ---@field Rotation number
    ---@field Opacity number
    ---@field Fade number
    ---@field Repeatable boolean
    ---@field Velocity Vector
    ---@field ScaleX number
    ---@field ScaleY number
    ---@field MovingTexAnim MovingTexAnim
    ---@field DrawRecAnim DrawRectAnim
    local SpriteAnim = {}

    --- 设置摆动效果使用的每秒旋转偏移。
    ---
    ---@param val number
    function SpriteAnim.SetRot(val) end

    --- 设置每秒旋转速度。
    ---
    ---@param val number
    function SpriteAnim.SetRotation(val) end

    --- 设置每秒不透明度变化。
    ---
    ---@param val number
    function SpriteAnim.SetOpacity(val) end

    --- 设置每秒淡出变化。
    ---
    ---@param val number
    function SpriteAnim.SetFade(val) end

    --- 设置摆动动画量。
    ---
    ---@param val number
    function SpriteAnim.SetWobbleAnimAmount(val) end

    --- 设置摆动动画速度。
    ---
    ---@param val number
    function SpriteAnim.SetWobbleAnimSpeed(val) end

    --- 设置动画是否重复。
    ---
    ---@param val boolean
    function SpriteAnim.SetRepeatable(val) end

    --- 设置每秒位置速度。
    ---
    ---@param val Vector
    function SpriteAnim.SetVelocity(val) end

    --- 设置每秒水平缩放变化。
    ---
    ---@param val number
    function SpriteAnim.SetScaleX(val) end

    --- 设置每秒垂直缩放变化。
    ---
    ---@param val number
    function SpriteAnim.SetScaleY(val) end

    --- 设置移动纹理子动画。
    ---
    ---@param val MovingTexAnim
    function SpriteAnim.SetMovingTexAnim(val) end

    --- 设置逐帧绘制矩形子动画。
    ---
    ---@param val DrawRectAnim
    function SpriteAnim.SetDrawRecAnim(val) end

    --- 返回每秒旋转偏移。
    ---
    ---@return number
    function SpriteAnim.GetRot() end

    --- 返回每秒旋转速度。
    ---
    ---@return number
    function SpriteAnim.GetRotation() end

    --- 返回每秒不透明度变化。
    ---
    ---@return number
    function SpriteAnim.GetOpacity() end

    --- 返回每秒淡出变化。
    ---
    ---@return number
    function SpriteAnim.GetFade() end

    --- 返回动画是否重复。
    ---
    ---@return boolean
    function SpriteAnim.GetRepeatable() end

    --- 返回每秒位置速度。
    ---
    ---@return Vector
    function SpriteAnim.GetVelocity() end

    --- 返回每秒水平缩放变化。
    ---
    ---@return number
    function SpriteAnim.GetScaleX() end

    --- 返回每秒垂直缩放变化。
    ---
    ---@return number
    function SpriteAnim.GetScaleY() end

    --- 返回移动纹理子动画。
    ---
    ---@return MovingTexAnim
    function SpriteAnim.GetMovingTexAnim() end

    --- 返回逐帧绘制矩形子动画。
    ---
    ---@return DrawRectAnim
    function SpriteAnim.GetDrawRecAnim() end
```

##### MovingTexAnim

```lua
    --- 构造一个移动纹理动画，可选带 X 和 Y 速度。
    ---
    ---@param speedX? number
    ---@param speedY? number
    ---
    ---@return MovingTexAnim
    function MovingTexAnim(speedX, speedY) end

    --- 连续滚动精灵的纹理。
    ---
    ---@class MovingTexAnim
    ---
    ---@field SpeedX number
    ---@field SpeedY number
    local MovingTexAnim = {}

    --- 设置水平滚动速度。
    ---
    ---@param val number
    function MovingTexAnim.SetSpeedX(val) end

    --- 设置垂直滚动速度。
    ---
    ---@param val number
    function MovingTexAnim.SetSpeedY(val) end

    --- 返回水平滚动速度。
    ---
    ---@return number
    function MovingTexAnim.GetSpeedX() end

    --- 返回垂直滚动速度。
    ---
    ---@return number
    function MovingTexAnim.GetSpeedY() end
```

##### DrawRectAnim

```lua
    --- 构造一个逐帧绘制矩形动画。
    ---
    ---@return DrawRectAnim
    function DrawRectAnim() end

    --- 从精灵图集逐帧动画化精灵。
    ---
    ---@class DrawRectAnim
    ---
    ---@field FrameRate number
    ---@field FrameCount integer
    ---@field HorizontalFrameCount integer
    local DrawRectAnim = {}

    --- 设置播放帧率（每秒帧数）。
    ---
    ---@param val number
    function DrawRectAnim.SetFrameRate(val) end

    --- 设置总帧数。
    ---
    ---@param val integer
    function DrawRectAnim.SetFrameCount(val) end

    --- 设置精灵图集中每行的帧数。
    ---
    ---@param val integer
    function DrawRectAnim.SetHorizontalFrameCount(val) end

    --- 返回播放帧率。
    ---
    ---@return number
    function DrawRectAnim.GetFrameRate() end

    --- 返回总帧数。
    ---
    ---@return integer
    function DrawRectAnim.GetFrameCount() end

    --- 返回每行帧数。
    ---
    ---@return integer
    function DrawRectAnim.GetHorizontalFrameCount() end
```

#### SpriteFont

```lua
    --- 构造一个精灵字体，可选带初始文本。
    ---
    ---@param text? string
    ---
    ---@return SpriteFont
    function SpriteFont(text) end

    --- 用自定义字体渲染文本。
    ---
    ---@class SpriteFont
    ---
    ---@field Text string
    ---@field Size integer
    ---@field Pos Vector
    ---@field Spacing Vector
    ---@field Align integer
    ---@field Color Vector
    ---@field ShadowColor Vector
    ---@field Bolden number
    ---@field Softness number
    ---@field ShadowBolden number
    ---@field ShadowSoftness number
    ---@field ShadowOffset Vector
    local SpriteFont = {}

    --- 按名称设置字体样式（字样），可选带像素大小。
    ---
    ---@param fontstyle string
    ---@param size? integer 字体大小，以像素为单位（默认 16）
    function SpriteFont.SetStyle(fontstyle, size) end

    --- 设置显示的文本（如果省略则为空字符串）。
    ---
    ---@param text? string
    function SpriteFont.SetText(text) end

    --- 设置字体大小，以像素为单位。
    ---
    ---@param size integer
    function SpriteFont.SetSize(size) end

    --- 设置在大小之上应用的额外统一缩放。
    ---
    ---@param scale number
    function SpriteFont.SetScale(scale) end

    --- 设置屏幕位置。
    ---
    ---@param pos Vector
    function SpriteFont.SetPos(pos) end

    --- 设置字符之间和行之间的水平和垂直间距。
    ---
    ---@param spacing Vector
    function SpriteFont.SetSpacing(spacing) end

    --- 设置水平和（可选）垂直对齐。
    ---
    ---@param halign integer WIFALIGN_* 常量之一
    ---@param valign? integer WIFALIGN_* 常量之一
    function SpriteFont.SetAlign(halign, valign) end

    --- 设置文本颜色，作为 Vector (RGBA) 或打包的十六进制颜色代码。
    ---
    ---@param color Vector
    ---
    ---@overload fun(colorHexCode: integer)
    function SpriteFont.SetColor(color) end

    --- 设置阴影颜色，作为 Vector (RGBA) 或打包的十六进制颜色代码。
    ---
    ---@param shadowcolor Vector
    ---
    ---@overload fun(colorHexCode: integer)
    function SpriteFont.SetShadowColor(shadowcolor) end

    --- 设置字形加粗程度。
    ---
    ---@param value number
    function SpriteFont.SetBolden(value) end

    --- 设置字形边缘柔和度。
    ---
    ---@param value number
    function SpriteFont.SetSoftness(value) end

    --- 设置阴影字形加粗程度。
    ---
    ---@param value number
    function SpriteFont.SetShadowBolden(value) end

    --- 设置阴影边缘柔和度。
    ---
    ---@param value number
    function SpriteFont.SetShadowSoftness(value) end

    --- 设置阴影偏移。
    ---
    ---@param value Vector
    function SpriteFont.SetShadowOffset(value) end

    --- 设置文本换行宽度（<= 0 禁用换行）。
    ---
    ---@param value number
    function SpriteFont.SetHorizontalWrapping(value) end

    --- 显示或隐藏文本。
    ---
    ---@param value boolean
    function SpriteFont.SetHidden(value) end

    --- 启用水平翻转字母。
    ---
    ---@param value boolean
    function SpriteFont.SetFlippedHorizontally(value) end

    --- 启用垂直翻转字母。
    ---
    ---@param value boolean
    function SpriteFont.SetFlippedVertically(value) end

    --- 返回显示的文本。
    ---
    ---@return string
    function SpriteFont.GetText() end

    --- 返回字体大小，以像素为单位。
    ---
    ---@return integer
    function SpriteFont.GetSize() end

    --- 返回额外统一缩放。
    ---
    ---@return number
    function SpriteFont.GetScale() end

    --- 返回屏幕位置。
    ---
    ---@return Vector
    function SpriteFont.GetPos() end

    --- 返回字符和行间距。
    ---
    ---@return Vector
    function SpriteFont.GetSpacing() end

    --- 返回水平和垂直对齐。
    ---
    ---@return integer halign
    ---@return integer valign
    function SpriteFont.GetAlign() end

    --- 返回文本颜色。
    ---
    ---@return Vector
    function SpriteFont.GetColor() end

    --- 返回阴影颜色。
    ---
    ---@return Vector
    function SpriteFont.GetShadowColor() end

    --- 返回字形加粗程度。
    ---
    ---@return number
    function SpriteFont.GetBolden() end

    --- 返回字形边缘柔和度。
    ---
    ---@return number
    function SpriteFont.GetSoftness() end

    --- 返回阴影字形加粗程度。
    ---
    ---@return number
    function SpriteFont.GetShadowBolden() end

    --- 返回阴影边缘柔和度。
    ---
    ---@return number
    function SpriteFont.GetShadowSoftness() end

    --- 返回阴影偏移。
    ---
    ---@return Vector
    function SpriteFont.GetShadowOffset() end

    --- 返回换行宽度。
    ---
    ---@return number
    function SpriteFont.GetHorizontalWrapping() end

    --- 返回文本是否隐藏。
    ---
    ---@return boolean
    function SpriteFont.IsHidden() end

    --- 返回字母是否水平翻转。
    ---
    ---@return boolean
    function SpriteFont.IsFlippedHorizontally() end

    --- 返回字母是否垂直翻转。
    ---
    ---@return boolean
    function SpriteFont.IsFlippedVertically() end

    --- 返回渲染文本宽度和高度在 Vector 的 X 和 Y 中。
    ---
    ---@return Vector
    function SpriteFont.TextSize() end

    --- 设置完全打字文本的时间，以秒为单位（0 禁用
    --- 打字机效果）。
    ---
    ---@param value number
    function SpriteFont.SetTypewriterTime(value) end

    --- 设置打字机动画完成时是否重新开始。
    ---
    ---@param value boolean
    function SpriteFont.SetTypewriterLooped(value) end

    --- 设置打字机动画开始的字符索引。
    ---
    ---@param value integer
    function SpriteFont.SetTypewriterCharacterStart(value) end

    --- 设置每个新字母出现时播放的音效。
    ---
    ---@param sound Sound
    ---@param soundinstance SoundInstance
    function SpriteFont.SetTypewriterSound(sound, soundinstance) end

    --- 将打字机动画重置到第一个字符。
    function SpriteFont.ResetTypewriter() end

    --- 立即完成打字机动画。
    function SpriteFont.TypewriterFinish() end

    --- 返回打字机动画是否已完成。
    ---
    ---@return boolean
    function SpriteFont.IsTypewriterFinished() end
```

SetAlign 和 GetAlign 使用的文本对齐常量：

```lua
    WIFALIGN_LEFT = 0
    WIFALIGN_CENTER = 1
    WIFALIGN_RIGHT = 2
    WIFALIGN_TOP = 3
    WIFALIGN_BOTTOM = 4
```

### Texture

```lua
    --- 创建纹理。带文件名时从文件加载图像；无参数时
    --- 返回空（无效）纹理句柄。
    ---
    ---@param filename? string
    ---
    ---@return Texture
    function Texture(filename) end

    --- 2D 纹理图像，从文件加载或程序化创建。
    ---
    ---@class Texture
    local Texture = {}

    --- 返回纹理是否包含有效数据（是否成功创建或加载）。
    ---
    ---@return boolean
    function Texture.IsValid() end

    --- 返回纹理宽度，以像素为单位。
    ---
    ---@return integer
    function Texture.GetWidth() end

    --- 返回纹理高度，以像素为单位。
    ---
    ---@return integer
    function Texture.GetHeight() end

    --- 返回纹理深度（用于 3D/体积纹理）。
    ---
    ---@return integer
    function Texture.GetDepth() end

    --- 返回纹理数组中的切片数。
    ---
    ---@return integer
    function Texture.GetArraySize() end

    --- 将纹理保存到文件。文件名中的扩展名选择
    --- 格式，必须是以下之一：.JPG、.PNG、.TGA、.BMP、.DDS。
    ---
    ---@param filename string
    function Texture.Save(filename) end

    --- 设置允许的最大纹理资源分辨率（仅影响包含 mipmap 的
    --- DDS 纹理）。
    ---
    ---@param resolution integer
    function SetTextureResolutionLimit(resolution) end

    --- 返回当前纹理分辨率限制。
    ---
    ---@return integer
    function GetTextureResolutionLimit() end
```

> 引擎还定义了这两个函数的流式内存阈值变体，但它们目前未暴露给 Lua，因此只有上面的分辨率限制形式可调用。

#### texturehelper

```lua
    --- 用于程序化创建纹理的全局实用对象。它
    --- 共享 `Texture` 类型，因此它返回的句柄公开了上面的查询
    --- 方法。
    ---
    ---@class TextureHelper
    local TextureHelper = {}

    --- 用于程序化创建纹理的全局辅助器。
    ---
    ---@type TextureHelper
    texturehelper = nil

    --- 返回内置的 Wicked Engine 标志纹理。
    ---
    ---@return Texture
    function TextureHelper.GetLogo() end

    --- 从给定参数创建渐变纹理。
    ---
    ---@param type GradientType 要生成的渐变类型
    ---@param width? integer 纹理宽度，以像素为单位（默认 256）
    ---@param height? integer 纹理高度，以像素为单位（默认 256）
    ---@param uv_start? Vector 渐变起始 UV（默认 Vector(0, 0)）
    ---@param uv_end? Vector 渐变结束 UV（默认 Vector(0, 0)）
    ---@param flags? GradientFlags 修饰标志（默认 GradientFlags.None）
    ---@param swizzle? string 每通道重排（默认 "rgba"）
    ---@param perlin_scale? number 柏林噪声缩放（默认 1）
    ---@param perlin_seed? integer 柏林噪声种子（默认 1234）
    ---@param perlin_octaves? integer 柏林噪声八度数（默认 8）
    ---@param perlin_persistence? number 柏林噪声持续性（默认 0.5）
    ---
    ---@return Texture
    function TextureHelper.CreateGradientTexture(
        type,
        width,
        height,
        uv_start,
        uv_end,
        flags,
        swizzle,
        perlin_scale,
        perlin_seed,
        perlin_octaves,
        perlin_persistence
    ) end

    --- 创建镜头畸变法线贴图（16 位精度）。
    ---
    ---@param width? integer 纹理宽度，以像素为单位（默认 256）
    ---@param height? integer 纹理高度，以像素为单位（默认 256）
    ---@param uv_start? Vector 畸变中心 UV（默认 Vector(0.5, 0.5)）
    ---@param radius? number 畸变半径（默认 0.5）
    ---@param squish? number 垂直挤压因子（默认 1）
    ---@param blend? number 混合量（默认 1）
    ---@param edge_smoothness? number 边缘平滑度（默认 0.04）
    ---
    ---@return Texture
    function TextureHelper.CreateLensDistortionNormalMap(
        width,
        height,
        uv_start,
        radius,
        squish,
        blend,
        edge_smoothness
    ) end
```

上面的渐变函数使用这些枚举：

```lua
    --- texturehelper.CreateGradientTexture 的渐变形状。
    ---
    ---@enum GradientType
    GradientType = {
        Linear = 0,
        Circular = 1,
        Angular = 2,
    }

    --- texturehelper.CreateGradientTexture 的修饰标志（用
    --- 按位或组合）。
    ---
    ---@enum GradientFlags
    GradientFlags = {
        None = 0,
        Inverse = 1 << 0,
        Smoothstep = 1 << 1,
        PerlinNoise = 1 << 2,
        R16Unorm = 1 << 3,
    }
```

纹理创建示例：

```lua
    -- 示例用法（sprite/material 是你自己的对象的占位符）。
    ---@diagnostic disable: undefined-global, param-type-mismatch
    texture = texturehelper.CreateGradientTexture(
        GradientType.Circular, -- 渐变类型
        256, 256, -- 纹理分辨率
        -- 起始和结束 UV 坐标设置渐变方向和范围：
        Vector(0.5, 0.5), Vector(0.5, 0),
        -- 修饰标志（按位组合）：
        GradientFlags.Inverse | GradientFlags.Smoothstep
            | GradientFlags.PerlinNoise,
        -- 每通道，取值之一：0, 1, r, g, b, a, x, y, z, w（小写或大写）：
        "rrr1",
        2, -- 柏林噪声缩放
        123, -- 柏林噪声种子
        6, -- 柏林噪声八度数
        0.8 -- 柏林噪声持续性
    )
    texture.Save("gradient.png") -- 保存到文件
    sprite.SetTexture(texture) -- 分配给精灵
    material.SetTexture(TextureSlot.BASECOLORMAP, texture) -- 分配给材质
```

### Audio

```lua
    --- 创建 Audio 对象。使用全局 `audio` 而不是构造一个。
    ---
    ---@return Audio
    function Audio() end

    --- 加载并播放音频文件。
    ---
    ---@class Audio
    local Audio = {}

    --- 音频设备。
    ---
    ---@type Audio
    audio = nil

    --- 创建声音文件，成功返回 true，否则返回 false。
    ---
    ---@param filename string
    ---@param sound Sound
    ---
    ---@return boolean
    function Audio.CreateSound(filename, sound) end

    --- 创建可重放的声音实例，成功返回 true，否则返回 false。
    ---
    ---@param sound Sound
    ---@param soundinstance SoundInstance
    ---
    ---@return boolean
    function Audio.CreateSoundInstance(sound, soundinstance) end

    --- 播放音频。
    ---
    ---@param soundinstance SoundInstance
    function Audio.Play(soundinstance) end

    --- 暂停音频。
    ---
    ---@param soundinstance SoundInstance
    function Audio.Pause(soundinstance) end

    --- 停止音频。
    ---
    ---@param soundinstance SoundInstance
    function Audio.Stop(soundinstance) end

    --- 返回 `soundinstance` 的音量。如果未提供 `soundinstance`，
    --- 返回主音量。
    ---
    ---@param soundinstance? SoundInstance
    ---
    ---@return number
    function Audio.GetVolume(soundinstance) end

    --- 设置 `soundinstance` 的音量。如果未提供 `soundinstance`，
    --- 设置主音量。
    ---
    ---@param volume number
    ---@param soundinstance? SoundInstance
    function Audio.SetVolume(volume, soundinstance) end

    --- 禁用循环。默认情况下，创建声音实例时会循环。
    ---
    ---@param soundinstance SoundInstance
    function Audio.ExitLoop(soundinstance) end

    --- 返回子混音组的音量。
    ---
    ---@param submixtype integer
    ---
    ---@return number
    function Audio.GetSubmixVolume(submixtype) end

    --- 设置子混音组的音量。
    ---
    ---@param submixtype integer
    ---@param volume number
    function Audio.SetSubmixVolume(submixtype, volume) end

    --- 为声音实例添加 3D 效果。
    ---
    ---@param soundinstance SoundInstance
    ---@param instance3D SoundInstance3D
    function Audio.Update3D(soundinstance, instance3D) end

    --- 全局设置混响的环境效果。可接受的输入值参见 Reverb Types
    --- 部分。
    ---
    ---@param reverbtype integer
    function Audio.SetReverb(reverbtype) end
```

#### Sound

```lua
    --- 创建声音。带文件名时从文件加载声音；无参数时
    --- 创建空声音。
    ---
    ---@param name? string
    ---
    ---@return Sound
    function Sound(name) end

    --- 音频文件。可通过 SoundInstance 实例化多次。
    ---
    ---@class Sound
    local Sound = {}

    --- 返回声音是否成功创建。
    ---
    ---@return boolean
    function Sound.IsValid() end
```

#### SoundInstance

```lua
    --- 创建声音实例。带声音时从该声音创建（可选起始偏移和长度，
    --- 以秒为单位）；无参数时创建空实例。
    ---
    ---@param sound? Sound
    ---@param begin? number
    ---@param length? number
    ---
    ---@return SoundInstance
    function SoundInstance(sound, begin, length) end

    --- 可播放的音频文件实例。注意：修改 SoundInstance 的参数后，
    --- 需要从指定声音重新创建 SoundInstance。
    ---
    ---@class SoundInstance
    local SoundInstance = {}

    --- 设置子混音类型组（默认为 SUBMIX_TYPE_SOUNDEFFECT）。
    ---
    ---@param submixtype integer
    function SoundInstance.SetSubmixType(submixtype) end

    --- 播放起始，以秒为单位，相对于它将创建自的 Sound（0 = 从开头）。
    ---
    ---@param seconds number
    function SoundInstance.SetBegin(seconds) end

    --- 长度，以秒为单位（0 = 到结尾）。
    ---
    ---@param seconds number
    function SoundInstance.SetLength(seconds) end

    --- 循环区域起始，以秒为单位，相对于实例起始时间（0 = 从开头）。
    ---
    ---@param seconds number
    function SoundInstance.SetLoopBegin(seconds) end

    --- 循环区域长度，以秒为单位（0 = 到结尾）。
    ---
    ---@param seconds number
    function SoundInstance.SetLoopLength(seconds) end

    --- 启用/禁用声音实例的混响。
    ---
    ---@param value boolean
    function SoundInstance.SetEnableReverb(value) end

    --- 启用/禁用声音实例的循环。
    ---
    ---@param value boolean
    function SoundInstance.SetLooped(value) end

    --- 返回子混音类型。
    ---
    ---@return integer
    function SoundInstance.GetSubmixType() end

    --- 返回起始。
    ---
    ---@return number
    function SoundInstance.GetBegin() end

    --- 返回长度。
    ---
    ---@return number
    function SoundInstance.GetLength() end

    --- 返回循环起始。
    ---
    ---@return number
    function SoundInstance.GetLoopBegin() end

    --- 返回循环长度。
    ---
    ---@return number
    function SoundInstance.GetLoopLength() end

    --- 返回是否启用混响。
    ---
    ---@return boolean
    function SoundInstance.IsEnableReverb() end

    --- 返回是否启用循环。
    ---
    ---@return boolean
    function SoundInstance.IsLooped() end

    --- 返回声音实例是否成功创建。
    ---
    ---@return boolean
    function SoundInstance.IsValid() end
```

#### SoundInstance3D

```lua
    --- 创建 3D 关系对象。默认情况下，监听器和发射器在
    --- 同一位置，这会禁用 3D 效果。
    ---
    ---@return SoundInstance3D
    function SoundInstance3D() end

    --- 描述 3D 世界中声音实例和监听器之间的关系。
    ---
    ---@class SoundInstance3D
    local SoundInstance3D = {}

    --- 设置监听器位置。
    ---
    ---@param value Vector
    function SoundInstance3D.SetListenerPos(value) end

    --- 设置监听器向上方向。
    ---
    ---@param value Vector
    function SoundInstance3D.SetListenerUp(value) end

    --- 设置监听器前方方向。
    ---
    ---@param value Vector
    function SoundInstance3D.SetListenerFront(value) end

    --- 设置监听器速度。
    ---
    ---@param value Vector
    function SoundInstance3D.SetListenerVelocity(value) end

    --- 设置发射器位置。
    ---
    ---@param value Vector
    function SoundInstance3D.SetEmitterPos(value) end

    --- 设置发射器向上方向。
    ---
    ---@param value Vector
    function SoundInstance3D.SetEmitterUp(value) end

    --- 设置发射器前方方向。
    ---
    ---@param value Vector
    function SoundInstance3D.SetEmitterFront(value) end

    --- 设置发射器速度。
    ---
    ---@param value Vector
    function SoundInstance3D.SetEmitterVelocity(value) end

    --- 设置发射器半径。
    ---
    ---@param radius number
    function SoundInstance3D.SetEmitterRadius(radius) end
```

#### Submix 类型

子混音类型将声音实例分组以便一起控制。

```lua
    --- 音效组。
    ---
    ---@type integer
    SUBMIX_TYPE_SOUNDEFFECT = 0

    --- 音乐组。
    ---
    ---@type integer
    SUBMIX_TYPE_MUSIC = 1

    --- 用户子混音组。
    ---
    ---@type integer
    SUBMIX_TYPE_USER0 = 2

    --- 用户子混音组。
    ---
    ---@type integer
    SUBMIX_TYPE_USER1 = 3
```

#### Reverb 类型

混响类型是内置预设，可以模拟特定类型的环境。

```lua
    --- 混响预设 DEFAULT。
    ---
    ---@type integer
    REVERB_PRESET_DEFAULT = 0

    --- 混响预设 GENERIC。
    ---
    ---@type integer
    REVERB_PRESET_GENERIC = 1

    --- 混响预设 FOREST。
    ---
    ---@type integer
    REVERB_PRESET_FOREST = 2

    --- 混响预设 PADDEDCELL。
    ---
    ---@type integer
    REVERB_PRESET_PADDEDCELL = 3

    --- 混响预设 ROOM。
    ---
    ---@type integer
    REVERB_PRESET_ROOM = 4

    --- 混响预设 BATHROOM。
    ---
    ---@type integer
    REVERB_PRESET_BATHROOM = 5

    --- 混响预设 LIVINGROOM。
    ---
    ---@type integer
    REVERB_PRESET_LIVINGROOM = 6

    --- 混响预设 STONEROOM。
    ---
    ---@type integer
    REVERB_PRESET_STONEROOM = 7

    --- 混响预设 AUDITORIUM。
    ---
    ---@type integer
    REVERB_PRESET_AUDITORIUM = 8

    --- 混响预设 CONCERTHALL。
    ---
    ---@type integer
    REVERB_PRESET_CONCERTHALL = 9

    --- 混响预设 CAVE。
    ---
    ---@type integer
    REVERB_PRESET_CAVE = 10

    --- 混响预设 ARENA。
    ---
    ---@type integer
    REVERB_PRESET_ARENA = 11

    --- 混响预设 HANGAR。
    ---
    ---@type integer
    REVERB_PRESET_HANGAR = 12

    --- 混响预设 CARPETEDHALLWAY。
    ---
    ---@type integer
    REVERB_PRESET_CARPETEDHALLWAY = 13

    --- 混响预设 HALLWAY。
    ---
    ---@type integer
    REVERB_PRESET_HALLWAY = 14

    --- 混响预设 STONECORRIDOR。
    ---
    ---@type integer
    REVERB_PRESET_STONECORRIDOR = 15

    --- 混响预设 ALLEY。
    ---
    ---@type integer
    REVERB_PRESET_ALLEY = 16

    --- 混响预设 CITY。
    ---
    ---@type integer
    REVERB_PRESET_CITY = 17

    --- 混响预设 MOUNTAINS。
    ---
    ---@type integer
    REVERB_PRESET_MOUNTAINS = 18

    --- 混响预设 QUARRY。
    ---
    ---@type integer
    REVERB_PRESET_QUARRY = 19

    --- 混响预设 PLAIN。
    ---
    ---@type integer
    REVERB_PRESET_PLAIN = 20

    --- 混响预设 PARKINGLOT。
    ---
    ---@type integer
    REVERB_PRESET_PARKINGLOT = 21

    --- 混响预设 SEWERPIPE。
    ---
    ---@type integer
    REVERB_PRESET_SEWERPIPE = 22

    --- 混响预设 UNDERWATER。
    ---
    ---@type integer
    REVERB_PRESET_UNDERWATER = 23

    --- 混响预设 SMALLROOM。
    ---
    ---@type integer
    REVERB_PRESET_SMALLROOM = 24

    --- 混响预设 MEDIUMROOM。
    ---
    ---@type integer
    REVERB_PRESET_MEDIUMROOM = 25

    --- 混响预设 LARGEROOM。
    ---
    ---@type integer
    REVERB_PRESET_LARGEROOM = 26

    --- 混响预设 MEDIUMHALL。
    ---
    ---@type integer
    REVERB_PRESET_MEDIUMHALL = 27

    --- 混响预设 LARGEHALL。
    ---
    ---@type integer
    REVERB_PRESET_LARGEHALL = 28

    --- 混响预设 PLATE。
    ---
    ---@type integer
    REVERB_PRESET_PLATE = 29
```

### Video

视频接口由两种类型的对象组成：Video 和 VideoInstance。
注意：这些是 VideoComponent 在场景中使用的底层对象，要将视频轻松设置为材质或光源，请查看可与场景的实体组件系统一起使用的 [VideoComponent](#videocomponent) 对象。

#### Video

```lua
    --- 加载 MP4 视频文件（目前仅支持 H264 内部压缩
    --- 格式）。
    ---
    ---@param filename string
    ---
    ---@return Video
    function Video(filename) end

    --- 从文件加载的视频资源。
    ---
    ---@class Video
    local Video = {}

    --- 如果视频成功创建则返回 true。
    ---
    ---@return boolean
    function Video.IsValid() end

    --- 返回持续时间，以秒为单位。
    ---
    ---@return number
    function Video.GetDurationSeconds() end
```

#### VideoInstance

VideoInstance 对象负责解码视频帧并将其输出到纹理。一个 Video 可以用多个 VideoInstance 解码，以在不同时间显示视频帧。通常你为一个视频使用一个 VideoInstance，除非你想在不同位置同时多次显示视频。

```lua
    --- 为视频数据创建解码器实例。
    ---
    ---@param video Video
    ---
    ---@return VideoInstance
    function VideoInstance(video) end

    --- Video 的播放实例，带播放控制。
    ---
    ---@class VideoInstance
    local VideoInstance = {}


    --- 如果视频实例成功创建则返回 true。
    ---
    ---@return boolean
    function VideoInstance.IsValid() end

    --- 播放。
    function VideoInstance.Play() end

    --- 暂停。
    function VideoInstance.Pause() end

    --- 停止。
    function VideoInstance.Stop() end

    --- 设置视频到达结尾时是否循环播放。
    ---
    ---@param looped boolean
    function VideoInstance.SetLooped(looped) end

    --- 跳转。
    ---
    ---@param timerSeconds number
    function VideoInstance.Seek(timerSeconds) end

    --- 返回此解码器实例的当前视频播放计时器，以
    --- 秒为单位。
    ---
    ---@return number
    function VideoInstance.GetCurrentTimer() end

    --- 如果视频播放已结束则返回 true。
    ---
    ---@return boolean
    function VideoInstance.IsEnded() end
```

### Math Types

#### Vector

```lua
    --- 构造 4 分量向量。任何缺失的分量默认为 0。
    ---
    ---@param x? number
    ---@param y? number
    ---@param z? number
    ---@param w? number
    ---
    ---@return Vector
    function Vector(x, y, z, w) end

    --- 四分量浮点向量。提供 SIMD 支持的高效计算。
    ---
    --- 全局 `vector` 对象公开相同的函数，因此可以
    --- 以静态方式调用，例如 `vector.Dot(a, b)`。
    ---
    ---@class Vector
    ---
    ---@field X number
    ---@field Y number
    ---@field Z number
    ---@field W number
    local Vector = {}

    --- 全局辅助器，公开每个 Vector 函数用于静态方式调用，
    --- 例如 vector.Lerp(a, b, t)。
    ---
    ---@type Vector
    vector = nil

    --- 返回向量的 X 分量。
    ---
    ---@return number
    function Vector.GetX() end

    --- 返回向量的 Y 分量。
    ---
    ---@return number
    function Vector.GetY() end

    --- 返回向量的 Z 分量。
    ---
    ---@return number
    function Vector.GetZ() end

    --- 返回向量的 W 分量。
    ---
    ---@return number
    function Vector.GetW() end

    --- 设置向量的 X 分量。
    ---
    ---@param value number
    function Vector.SetX(value) end

    --- 设置向量的 Y 分量。
    ---
    ---@param value number
    function Vector.SetY(value) end

    --- 设置向量的 Z 分量。
    ---
    ---@param value number
    function Vector.SetZ(value) end

    --- 设置向量的 W 分量。
    ---
    ---@param value number
    function Vector.SetW(value) end

    --- 返回向量的 3D 长度（模）。无参数调用时作用于向量自身。
    ---
    ---@param v Vector
    ---
    ---@return number
    ---
    ---@overload fun(): number
    function Vector.Length(v) end

    --- 返回向量的 3D 长度平方（比 Length 更高效）。无参数调用时
    --- 作用于向量自身。
    ---
    ---@param v Vector
    ---
    ---@return number
    ---
    ---@overload fun(): number
    function Vector.LengthSquared(v) end

    --- 返回两点之间的距离。
    ---
    ---@param v1 Vector
    ---@param v2 Vector
    ---
    ---@return number
    function Vector.Distance(v1, v2) end

    --- 返回两点之间的距离平方（比 Distance 更高效）。
    ---
    ---@param v1 Vector
    ---@param v2 Vector
    ---
    ---@return number
    function Vector.DistanceSquared(v1, v2) end

    --- 返回向量的归一化（单位长度）副本。无参数调用时作用于
    --- 向量自身。
    ---
    ---@param v Vector
    ---
    ---@return Vector
    ---
    ---@overload fun(): Vector
    function Vector.Normalize(v) end

    --- 返回四元数的归一化副本。无参数调用时作用于向量自身。
    ---
    ---@param v Vector
    ---
    ---@return Vector
    ---
    ---@overload fun(): Vector
    function Vector.QuaternionNormalize(v) end

    --- 将向量的每个分量限制在 min 和 max 之间。用两个参数调用时
    --- 作用于向量自身。
    ---
    ---@param v Vector
    ---@param min number
    ---@param max number
    ---
    ---@return Vector
    ---
    ---@overload fun(min: number, max: number): Vector
    function Vector.Clamp(v, min, max) end

    --- 用矩阵变换向量（4D，使用 w 分量）。
    ---
    ---@param vec Vector
    ---@param matrix Matrix
    ---
    ---@return Vector
    function Vector.Transform(vec, matrix) end

    --- 用矩阵变换 3D 法线（忽略平移）。
    ---
    ---@param vec Vector
    ---@param matrix Matrix
    ---
    ---@return Vector
    function Vector.TransformNormal(vec, matrix) end

    --- 用矩阵变换 3D 坐标（应用透视除法）。
    ---
    ---@param vec Vector
    ---@param matrix Matrix
    ---
    ---@return Vector
    function Vector.TransformCoord(vec, matrix) end

    --- 返回两个向量的分量和。
    ---
    ---@param v1 Vector
    ---@param v2 Vector
    ---
    ---@return Vector
    function Vector.Add(v1, v2) end

    --- 返回两个向量的分量差。
    ---
    ---@param v1 Vector
    ---@param v2 Vector
    ---
    ---@return Vector
    function Vector.Subtract(v1, v2) end

    --- 按分量相乘两个向量，或用标量缩放向量。
    ---
    ---@param v1 Vector
    ---@param v2 Vector
    ---
    ---@return Vector
    ---
    ---@overload fun(v: Vector, f: number): Vector
    ---@overload fun(f: number, v: Vector): Vector
    function Vector.Multiply(v1, v2) end

    --- 返回两个向量的点积。
    ---
    ---@param v1 Vector
    ---@param v2 Vector
    ---
    ---@return number
    function Vector.Dot(v1, v2) end

    --- 返回两个 3D 向量的叉积。
    ---
    ---@param v1 Vector
    ---@param v2 Vector
    ---
    ---@return Vector
    function Vector.Cross(v1, v2) end

    --- 按因子 t 在 [0, 1] 范围内线性插值两个向量。
    ---
    ---@param v1 Vector
    ---@param v2 Vector
    ---@param t number
    ---
    ---@return Vector
    function Vector.Lerp(v1, v2, t) end

    --- 用四元数旋转 3D 向量。
    ---
    ---@param v Vector          要旋转的向量
    ---@param quaternion Vector 旋转四元数
    ---
    ---@return Vector
    function Vector.Rotate(v, quaternion) end

    --- 返回表示恒等（无）旋转的四元数。
    ---
    ---@return Vector
    function Vector.QuaternionIdentity() end

    --- 返回四元数的逆。
    ---
    ---@param quaternion Vector
    ---
    ---@return Vector
    function Vector.QuaternionInverse(quaternion) end

    --- 相乘（串联）两个四元数。
    ---
    ---@param quaternion1 Vector
    ---@param quaternion2 Vector
    ---
    ---@return Vector
    function Vector.QuaternionMultiply(quaternion1, quaternion2) end

    --- 从欧拉角（滚转、俯仰、偏航）构建四元数。
    ---
    ---@param rotXYZ Vector
    ---
    ---@return Vector
    function Vector.QuaternionFromRollPitchYaw(rotXYZ) end

    --- 从四元数提取欧拉角（滚转、俯仰、偏航）。
    ---
    ---@param quaternion Vector
    ---
    ---@return Vector
    function Vector.QuaternionToRollPitchYaw(quaternion) end

    --- 按因子 t 球面插值两个四元数。
    ---
    ---@param quaternion1 Vector
    ---@param quaternion2 Vector
    ---@param t number
    ---
    ---@return Vector
    function Vector.QuaternionSlerp(quaternion1, quaternion2, t) end

    --- 按因子 t 球面插值两个四元数。与 QuaternionSlerp 相同。
    ---
    ---@param quaternion1 Vector
    ---@param quaternion2 Vector
    ---@param t number
    ---
    ---@return Vector
    function Vector.Slerp(quaternion1, quaternion2, t) end

    --- 从点和法线构建平面（作为系数 Vector）。
    ---
    ---@param point Vector
    ---@param normal Vector
    ---
    ---@return Vector
    function Vector.PlaneFromPointNormal(point, normal) end

    --- 从三点构建平面（作为系数 Vector）。
    ---
    ---@param a Vector
    ---@param b Vector
    ---@param c Vector
    ---
    ---@return Vector
    function Vector.PlaneFromPoints(a, b, c) end

    --- 计算围绕给定轴的两个 3D 向量之间的角度，在
    --- [0, max_angle] 范围内（默认 2*pi）。
    ---
    ---@param a Vector
    ---@param b Vector
    ---@param axis Vector
    ---@param max_angle? number
    ---
    ---@return number
    function Vector.GetAngle(a, b, axis, max_angle) end

    --- 计算围绕给定轴的两个 3D 向量之间的有符号角度。
    ---
    ---@param a Vector
    ---@param b Vector
    ---@param axis Vector
    ---
    ---@return number
    function Vector.GetAngleSigned(a, b, axis) end
```

#### Matrix

```lua
    --- 从 16 个行主序分量构造 4x4 矩阵。任何缺失的
    --- 分量默认为 0；无参数时返回单位矩阵。
    ---
    ---@param m00? number
    ---@param m01? number
    ---@param m02? number
    ---@param m03? number
    ---@param m10? number
    ---@param m11? number
    ---@param m12? number
    ---@param m13? number
    ---@param m20? number
    ---@param m21? number
    ---@param m22? number
    ---@param m23? number
    ---@param m30? number
    ---@param m31? number
    ---@param m32? number
    ---@param m33? number
    ---
    ---@return Matrix
    function Matrix(
        m00, m01, m02, m03,
        m10, m11, m12, m13,
        m20, m21, m22, m23,
        m30, m31, m32, m33
    ) end

    --- 4x4 矩阵。提供 SIMD 支持的高效计算。
    ---
    --- 全局 `matrix` 对象公开相同的函数，因此可以
    --- 以静态方式调用，例如 `matrix.Multiply(a, b)`。
    ---
    ---@class Matrix
    local Matrix = {}

    --- 全局辅助器，公开每个 Matrix 函数用于静态方式调用，
    --- 例如 matrix.Multiply(a, b)。
    ---
    ---@type Matrix
    matrix = nil

    --- 返回矩阵的给定行 (0-3) 作为 Vector。
    ---
    ---@param row? integer 行索引，在 [0, 3] 范围内（默认 0）
    ---
    ---@return Vector
    function Matrix.GetRow(row) end

    --- 从位置向量构建平移矩阵（如果省略则为单位矩阵）。
    ---
    ---@param vector? Vector
    ---
    ---@return Matrix
    function Matrix.Translation(vector) end

    --- 从欧拉角（滚转、俯仰、偏航）构建旋转矩阵。
    ---
    ---@param rollPitchYaw? Vector
    ---
    ---@return Matrix
    function Matrix.Rotation(rollPitchYaw) end

    --- 构建绕 X 轴的旋转矩阵。
    ---
    ---@param angleInRadians? number
    ---
    ---@return Matrix
    function Matrix.RotationX(angleInRadians) end

    --- 构建绕 Y 轴的旋转矩阵。
    ---
    ---@param angleInRadians? number
    ---
    ---@return Matrix
    function Matrix.RotationY(angleInRadians) end

    --- 构建绕 Z 轴的旋转矩阵。
    ---
    ---@param angleInRadians? number
    ---
    ---@return Matrix
    function Matrix.RotationZ(angleInRadians) end

    --- 从四元数构建旋转矩阵。
    ---
    ---@param quaternion? Vector
    ---
    ---@return Matrix
    function Matrix.RotationQuaternion(quaternion) end

    --- 从每轴 Vector 或统一标量构建缩放矩阵（如果省略则为
    --- 单位矩阵）。
    ---
    ---@param scaleXYZ? Vector
    ---
    ---@return Matrix
    ---
    ---@overload fun(scale: number): Matrix
    function Matrix.Scale(scaleXYZ) end

    --- 构建从 eye 朝某方向看的左手视图矩阵。
    ---
    ---@param eye Vector
    ---@param direction Vector
    ---@param up? Vector 向上方向（默认 (0, 1, 0)）
    ---
    ---@return Matrix
    function Matrix.LookTo(eye, direction, up) end

    --- 构建从 eye 朝焦点看的左手视图矩阵。
    ---
    ---@param eye Vector
    ---@param focusPos Vector
    ---@param up? Vector 向上方向（默认 (0, 1, 0)）
    ---
    ---@return Matrix
    function Matrix.LookAt(eye, focusPos, up) end

    --- 返回两个矩阵的乘积。
    ---
    ---@param m1 Matrix
    ---@param m2 Matrix
    ---
    ---@return Matrix
    function Matrix.Multiply(m1, m2) end

    --- 返回两个矩阵的分量和。
    ---
    ---@param m1 Matrix
    ---@param m2 Matrix
    ---
    ---@return Matrix
    function Matrix.Add(m1, m2) end

    --- 返回矩阵的转置。
    ---
    ---@param m Matrix
    ---
    ---@return Matrix
    function Matrix.Transpose(m) end

    --- 返回矩阵的逆及其行列式。
    ---
    ---@param m Matrix
    ---
    ---@return Matrix inverse
    ---@return number determinant
    function Matrix.Inverse(m) end

    --- 返回矩阵的前方方向。无参数调用时作用于矩阵自身。
    ---
    ---@param mat Matrix
    ---
    ---@return Vector
    ---
    ---@overload fun(): Vector
    function Matrix.GetForward(mat) end

    --- 返回矩阵的向上方向。无参数调用时作用于矩阵自身。
    ---
    ---@param mat Matrix
    ---
    ---@return Vector
    ---
    ---@overload fun(): Vector
    function Matrix.GetUp(mat) end

    --- 返回矩阵的右方向。无参数调用时作用于矩阵自身。
    ---
    ---@param mat Matrix
    ---
    ---@return Vector
    ---
    ---@overload fun(): Vector
    function Matrix.GetRight(mat) end
```

### Async

```lua
    --- 构造新的 Async 跟踪器对象。
    ---
    ---@return Async
    function Async() end

    --- Async 对象可用于跟踪或等待在后台线程上运行的函数的
    --- 完成。
    ---
    ---@class Async
    local Async = {}

    --- 等待此跟踪器上的异步任务完成。
    function Async.Wait() end

    --- 检查此跟踪器上的所有异步任务是否已完成。
    ---
    ---@return boolean
    function Async.IsCompleted() end
```

### 场景系统（使用实体-组件系统）

用这些组件操作 3D 场景。

#### Entity

实体只是一个整数值（Lua 中的 int，C++ 中的 uint32），用作检索关联组件的句柄。

```lua
    --- 实体是整数句柄。`Entity` 是 `integer` 的别名，
    --- 用于签名的可读性。
    ---
    ---@alias Entity integer

    --- 无效/无实体的哨兵值 (0)。
    ---
    ---@type integer
    INVALID_ENTITY = 0
```

#### Scene

```lua
    --- 创建自定义场景。
    ---
    ---@return Scene
    function Scene() end

    --- 场景持有组件。实体句柄可用于通过场景检索
    --- 关联的组件。
    ---
    ---@class Scene
    ---
    ---@field Weather WeatherComponent
    local Scene = {}

    --- 返回全局场景。
    ---
    ---@return Scene
    function GetScene() end

    --- 返回全局相机。
    ---
    ---@return CameraComponent
    function GetCamera() end

    --- 从文件加载模型。返回此模型中所有内容附加到的根实体。
    ---
    ---@param fileName string
    ---@param transform? Matrix
    ---
    ---@return Entity
    function LoadModel(fileName, transform) end

    --- 从文件加载模型到指定场景。返回此模型中所有内容附加到的根实体。
    ---
    ---@param scene Scene
    ---@param fileName string
    ---@param transform? Matrix
    ---
    ---@return Entity
    function LoadModel(scene, fileName, transform) end

    --- 已弃用，你可以改用 `FILTER_` 枚举。
    ---
    ---@deprecated
    ---
    ---@type integer
    PICK_OPAQUE = 1

    --- 已弃用，你可以改用 `FILTER_` 枚举。
    ---
    ---@deprecated
    ---
    ---@type integer
    PICK_TRANSPARENT = 2

    --- 已弃用，你可以改用 `FILTER_` 枚举。
    ---
    ---@deprecated
    ---
    ---@type integer
    PICK_WATER = 4

    --- 已弃用，你可以改用 `FILTER_` 枚举。
    ---
    ---@deprecated
    ---
    ---@type integer
    PICK_VOID = 0

    --- 在场景中执行射线拾取。pickType 是指定位掩码，指定要检查的
    --- 对象类型。layerMask 是位掩码，指定要检查的层。Scene 参数是
    --- 可选的，如果未指定则使用全局场景。（已弃用，你可以改用场景的
    --- Intersects() 函数）
    ---
    ---@deprecated
    ---
    ---@param ray Ray
    ---@param filterMask? integer
    ---@param layerMask? integer
    ---@param scene? Scene
    ---@param lod? integer
    ---
    ---@return Entity entity
    ---@return Vector position
    ---@return Vector normal
    ---@return number distance
    function Pick(ray, filterMask, layerMask, scene, lod) end

    --- 在场景中执行球体相交。filterMask 是指定位掩码，指定要检查的
    --- 对象类型。layerMask 是位掩码，指定要检查的层。Scene 参数是
    --- 可选的，如果未指定则使用全局场景。（已弃用，你可以改用场景的
    --- Intersects() 函数）
    ---
    ---@deprecated
    ---
    ---@param sphere Sphere
    ---@param filterMask? integer
    ---@param layerMask? integer
    ---@param scene? Scene
    ---@param lod? integer
    ---
    ---@return Entity entity
    ---@return Vector position
    ---@return Vector normal
    ---@return number distance
    function SceneIntersectSphere(sphere, filterMask, layerMask, scene, lod) end

    --- 在场景中执行胶囊相交。filterMask 是指定位掩码，指定要检查的
    --- 对象类型。layerMask 是位掩码，指定要检查的层。Scene 参数是
    --- 可选的，如果未指定则使用全局场景。（已弃用，你可以改用场景的
    --- Intersects() 函数）
    ---
    ---@deprecated
    ---
    ---@param capsule Capsule
    ---@param filterMask? integer
    ---@param layerMask? integer
    ---@param scene? Scene
    ---@param lod? integer
    ---
    ---@return Entity entity
    ---@return Vector position
    ---@return Vector normal
    ---@return number distance
    function SceneIntersectCapsule(
        capsule,
        filterMask,
        layerMask,
        scene,
        lod
    ) end

    --- 不包含任何内容。
    ---
    ---@type integer
    FILTER_NONE = 0

    --- 包含不透明网格。
    ---
    ---@type integer
    FILTER_OPAQUE = 1

    --- 包含透明网格。
    ---
    ---@type integer
    FILTER_TRANSPARENT = 2

    --- 包含水面网格。
    ---
    ---@type integer
    FILTER_WATER = 4

    --- 包含导航网格。
    ---
    ---@type integer
    FILTER_NAVIGATION_MESH = 8

    --- 包含地形。
    ---@type integer
    FILTER_TERRAIN = 16

    --- 包含所有对象、网格。
    ---
    ---@type integer
    FILTER_OBJECT_ALL = 31

    --- 包含碰撞器。
    ---
    ---@type integer
    FILTER_COLLIDER = 32

    --- 包含布娃娃身体部分。
    ---
    ---@type integer
    FILTER_RAGDOLL = 64

    --- 包含所有内容。
    ---
    ---@type integer
    FILTER_ALL = -1

    --- 将图元与场景相交并返回碰撞参数。
    --- 如果 humanoid_bone 不是 `HumanoidBone.Count`，则相交是
    --- 布娃娃，entity 指的是人形实体。
    ---
    ---@param primitive Ray|Sphere|Capsule
    ---@param filterMask? integer
    ---@param layerMask? integer
    ---@param lod? integer
    ---
    ---@return Entity entity
    ---@return Vector position
    ---@return Vector normal
    ---@return number distance
    ---@return Vector velocity
    ---@return integer subsetIndex
    ---@return Matrix orientation
    ---@return Vector uv
    ---@return HumanoidBone humanoid_bone
    function Scene.Intersects(primitive, filterMask, layerMask, lod) end

    --- 将图元与场景相交，相交时立即返回 true，如果无相交则返回
    --- false。这比搜索最近相交的常规 `Intersects` 更快地用于
    --- 遮挡检查。
    ---
    ---@param primitive Ray
    ---@param filterMask? integer
    ---@param layerMask? integer
    ---@param lod? integer
    ---
    ---@return boolean
    function Scene.IntersectsFirst(primitive, filterMask, layerMask, lod) end

    --- 将图元与场景相交并返回结果数组。对于 Ray，将返回
    --- RayIntersectionResult，对于 Sphere 和 Capsule 将返回
    --- SphereIntersectionResult。
    ---
    ---@param primitive Ray|Sphere|Capsule
    ---@param filterMask? integer
    ---@param layerMask? integer
    ---@param lod? integer
    ---
    ---@return RayIntersectionResult[]|SphereIntersectionResult[]
    function Scene.IntersectsAll(primitive, filterMask, layerMask, lod) end

    --- 更新场景及场景内的每个实体和组件。
    function Scene.Update() end

    --- 删除场景内的每个实体和组件。
    function Scene.Clear() end

    --- 将另一个场景的内容移动到此场景中。另一个场景在此
    --- 操作后将变空（内容是移动的，不是复制的）。
    ---
    ---@param other Scene
    function Scene.Merge(other) end

    --- 更新完整的场景层次结构系统。如果你修改了例如父变换并且
    --- 子级需要立即在脚本中获得最新结果，则很有用。
    function Scene.UpdateHierarchy() end

    --- 将预制场景中的所有内容复制到当前场景。如果
    --- attached 参数设为 `true`，则预制场景中的所有内容将
    --- 附加到公共根实体（带 TransformComponent 和
    --- LayerComponent），函数将返回该根实体。
    ---
    ---@param prefab Scene
    ---@param attached? boolean
    ---
    ---@return Entity
    function Scene.Instantiate(prefab, attached) end

    --- 创建空实体并返回它。
    ---
    ---@return Entity
    function CreateEntity() end

    --- 返回包含给定场景中所有实体的表。
    ---
    ---@return any
    function Scene.FindAllEntities() end

    --- 如果实体存在则返回实体 ID，否则返回 INVALID_ENTITY。你可以
    --- 指定祖先实体，如果你只想查找是祖先实体后代的实体。
    ---
    ---@param value string
    ---@param ancestor? integer
    ---
    ---@return Entity
    function Scene.Entity_FindByName(value, ancestor) end

    --- 移除实体并删除其所有组件（如果存在）。如果指定 recursive，
    --- 则所有子级也将被移除（默认启用）。如果指定 keep_sorted，则
    --- 组件顺序将保持不变（默认禁用，较慢）。
    ---
    ---@param entity Entity
    ---@param recursive? boolean
    ---@param keep_sorted? boolean
    function Scene.Entity_Remove(entity, recursive, keep_sorted) end

    --- 与 Entity_Remove 相同，但它在后台线程上运行，状态可以
    --- 由你提供的 [Async](#async) 对象跟踪。
    ---
    ---@param async Async
    ---@param entity Entity
    ---@param recursive? boolean
    ---@param keep_sorted? boolean
    function Scene.Entity_Remove_Async(
        async,
        entity,
        recursive,
        keep_sorted
    ) end

    --- 复制实体的所有组件并创建新实体。
    --- 返回克隆实体句柄。
    ---
    ---@param entity Entity
    ---
    ---@return Entity
    function Scene.Entity_Duplicate(entity) end

    --- 检查实体是否是祖先的后代。如果实体在祖先的层次结构树中
    --- 则返回 `true`，否则返回 `false`。
    ---
    ---@param entity Entity
    ---@param ancestor Entity
    ---
    ---@return boolean
    function Scene.Entity_IsDescendant(entity, ancestor) end

    --- 将名称组件附加到实体。返回的组件与实体关联并可操作。
    ---
    ---@param entity Entity
    ---
    ---@return NameComponent
    function Scene.Component_CreateName(entity) end

    --- 将层组件附加到实体。返回的组件与实体关联并可操作。
    ---
    ---@param entity Entity
    ---
    ---@return LayerComponent
    function Scene.Component_CreateLayer(entity) end

    --- 将变换组件附加到实体。返回的组件与实体关联并可操作。
    ---
    ---@param entity Entity
    ---
    ---@return TransformComponent
    function Scene.Component_CreateTransform(entity) end

    --- 将相机组件附加到实体。返回的组件与实体关联并可操作。
    ---
    ---@param entity Entity
    ---
    ---@return CameraComponent
    function Scene.Component_CreateCamera(entity) end

    --- 将光源组件附加到实体。返回的组件与实体关联并可操作。
    ---
    ---@param entity Entity
    ---
    ---@return LightComponent
    function Scene.Component_CreateLight(entity) end

    --- 将对象组件附加到实体。返回的组件与实体关联并可操作。
    ---
    ---@param entity Entity
    ---
    ---@return ObjectComponent
    function Scene.Component_CreateObject(entity) end

    --- 将 IK 组件附加到实体。返回的组件与实体关联并可操作。
    ---
    ---@param entity Entity
    ---
    ---@return InverseKinematicsComponent
    function Scene.Component_CreateInverseKinematics(entity) end

    --- 将弹簧组件附加到实体。返回的组件与实体关联并可操作。
    ---
    ---@param entity Entity
    ---
    ---@return SpringComponent
    function Scene.Component_CreateSpring(entity) end

    --- 将脚本组件附加到实体。返回的组件与实体关联并可操作。
    ---
    ---@param entity Entity
    ---
    ---@return ScriptComponent
    function Scene.Component_CreateScript(entity) end

    --- 将 RigidBodyPhysicsComponent 附加到实体。返回的组件与实体
    --- 关联并可操作。
    ---
    ---@param entity Entity
    ---
    ---@return RigidBodyPhysicsComponent
    function Scene.Component_CreateRigidBodyPhysics(entity) end

    --- 将 SoftBodyPhysicsComponent 附加到实体。返回的组件与实体
    --- 关联并可操作。
    ---
    ---@param entity Entity
    ---
    ---@return SoftBodyPhysicsComponent
    function Scene.Component_CreateSoftBodyPhysics(entity) end

    --- 将 ForceFieldComponent 附加到实体。返回的组件与实体关联并可
    --- 操作。
    ---
    ---@param entity Entity
    ---
    ---@return ForceFieldComponent
    function Scene.Component_CreateForceField(entity) end

    --- 将 WeatherComponent 附加到实体。返回的组件与实体关联并可
    --- 操作。
    ---
    ---@param entity Entity
    ---
    ---@return WeatherComponent
    function Scene.Component_CreateWeather(entity) end

    --- 将 SoundComponent 附加到实体。返回的组件与实体关联并可
    --- 操作。
    ---
    ---@param entity Entity
    ---
    ---@return SoundComponent
    function Scene.Component_CreateSound(entity) end

    --- 将 VideoComponent 附加到实体。返回的组件与实体关联并可
    --- 操作。
    ---
    ---@param entity Entity
    ---
    ---@return VideoComponent
    function Scene.Component_CreateVideo(entity) end

    --- 将 ColliderComponent 附加到实体。返回的组件与实体关联并可
    --- 操作。
    ---
    ---@param entity Entity
    ---
    ---@return ColliderComponent
    function Scene.Component_CreateCollider(entity) end

    --- 将 ExpressionComponent 附加到实体。返回的组件与实体关联并可
    --- 操作。
    ---
    ---@param entity Entity
    ---
    ---@return ExpressionComponent
    function Scene.Component_CreateExpression(entity) end

    --- 将 HumanoidComponent 附加到实体。返回的组件与实体关联并可
    --- 操作。
    ---
    ---@param entity Entity
    ---
    ---@return HumanoidComponent
    function Scene.Component_CreateHumanoid(entity) end

    --- 将 DecalComponent 附加到实体。返回的组件与实体关联并可
    --- 操作。
    ---
    ---@param entity Entity
    ---
    ---@return DecalComponent
    function Scene.Component_CreateDecal(entity) end

    --- 将 Sprite 附加到实体。返回的组件与实体关联并可操作。
    ---
    ---@param entity Entity
    ---
    ---@return Sprite
    function Scene.Component_CreateSprite(entity) end

    --- 将 SpriteFont 附加到实体。返回的组件与实体关联并可操作。
    ---
    ---@param entity Entity
    ---
    ---@return SpriteFont
    function Scene.Component_CreateFont(entity) end

    --- 将 VoxelGrid 附加到实体。返回的组件与实体关联并可操作。
    ---
    ---@param entity Entity
    ---
    ---@return VoxelGrid
    function Scene.Component_CreateVoxelGrid(entity) end

    --- 将 MetadataComponent 附加到实体。返回的组件与实体关联并可
    --- 操作。
    ---
    ---@param entity Entity
    ---
    ---@return MetadataComponent
    function Scene.Component_CreateMetadata(entity) end

    --- 查询实体的名称组件（如果存在）。
    ---
    ---@param entity Entity
    ---
    ---@return NameComponent?
    function Scene.Component_GetName(entity) end

    --- 查询实体的层组件（如果存在）。
    ---
    ---@param entity Entity
    ---
    ---@return LayerComponent?
    function Scene.Component_GetLayer(entity) end

    --- 查询实体的变换组件（如果存在）。
    ---
    ---@param entity Entity
    ---
    ---@return TransformComponent?
    function Scene.Component_GetTransform(entity) end

    --- 查询实体的相机组件（如果存在）。
    ---
    ---@param entity Entity
    ---
    ---@return CameraComponent?
    function Scene.Component_GetCamera(entity) end

    --- 查询实体的动画组件（如果存在）。
    ---
    ---@param entity Entity
    ---
    ---@return AnimationComponent?
    function Scene.Component_GetAnimation(entity) end

    --- 查询实体的材质组件（如果存在）。
    ---
    ---@param entity Entity
    ---
    ---@return MaterialComponent?
    function Scene.Component_GetMaterial(entity) end

    --- 查询实体的发射器组件（如果存在）。
    ---
    ---@param entity Entity
    ---
    ---@return EmitterComponent?
    function Scene.Component_GetEmitter(entity) end

    --- 查询实体的光源组件（如果存在）。
    ---
    ---@param entity Entity
    ---
    ---@return LightComponent?
    function Scene.Component_GetLight(entity) end

    --- 查询实体的对象组件（如果存在）。
    ---
    ---@param entity Entity
    ---
    ---@return ObjectComponent?
    function Scene.Component_GetObject(entity) end

    --- 查询实体的 IK 组件（如果存在）。
    ---
    ---@param entity Entity
    ---
    ---@return InverseKinematicsComponent?
    function Scene.Component_GetInverseKinematics(entity) end

    --- 查询实体的弹簧组件（如果存在）。
    ---
    ---@param entity Entity
    ---
    ---@return SpringComponent?
    function Scene.Component_GetSpring(entity) end

    --- 查询实体的脚本组件（如果存在）。
    ---
    ---@param entity Entity
    ---
    ---@return ScriptComponent?
    function Scene.Component_GetScript(entity) end

    --- 查询实体的 RigidBodyPhysicsComponent（如果存在）。
    ---
    ---@param entity Entity
    ---
    ---@return RigidBodyPhysicsComponent?
    function Scene.Component_GetRigidBodyPhysics(entity) end

    --- 查询实体的 SoftBodyPhysicsComponent（如果存在）。
    ---
    ---@param entity Entity
    ---
    ---@return SoftBodyPhysicsComponent?
    function Scene.Component_GetSoftBodyPhysics(entity) end

    --- 查询实体的 ForceFieldComponent（如果存在）。
    ---
    ---@param entity Entity
    ---
    ---@return ForceFieldComponent?
    function Scene.Component_GetForceField(entity) end

    --- 查询实体的 WeatherComponent（如果存在）。
    ---
    ---@param entity Entity
    ---
    ---@return WeatherComponent?
    function Scene.Component_GetWeather(entity) end

    --- 查询实体的 SoundComponent（如果存在）。
    ---
    ---@param entity Entity
    ---
    ---@return SoundComponent?
    function Scene.Component_GetSound(entity) end

    --- 查询实体的 VideoComponent（如果存在）。
    ---
    ---@param entity Entity
    ---
    ---@return VideoComponent?
    function Scene.Component_GetVideo(entity) end

    --- 查询实体的 ColliderComponent（如果存在）。
    ---
    ---@param entity Entity
    ---
    ---@return ColliderComponent?
    function Scene.Component_GetCollider(entity) end

    --- 查询实体的 ExpressionComponent（如果存在）。
    ---
    ---@param entity Entity
    ---
    ---@return ExpressionComponent?
    function Scene.Component_GetExpression(entity) end

    --- 查询实体的 HumanoidComponent（如果存在）。
    ---
    ---@param entity Entity
    ---
    ---@return HumanoidComponent?
    function Scene.Component_GetHumanoid(entity) end

    --- 查询实体的 DecalComponent（如果存在）。
    ---
    ---@param entity Entity
    ---
    ---@return DecalComponent?
    function Scene.Component_GetDecal(entity) end

    --- 查询实体的 Sprite（如果存在）。
    ---
    ---@param entity Entity
    ---
    ---@return Sprite?
    function Scene.Component_GetSprite(entity) end

    --- 查询实体的 VoxelGrid（如果存在）。
    ---
    ---@param entity Entity
    ---
    ---@return VoxelGrid?
    function Scene.Component_GetVoxelGrid(entity) end

    --- 查询实体的 MetadataComponent（如果存在）。
    ---
    ---@param entity Entity
    ---
    ---@return MetadataComponent?
    function Scene.Component_GetMetadata(entity) end

    --- 返回场景中每个 Name 组件的数组。
    ---
    ---@return NameComponent[]
    function Scene.Component_GetNameArray() end

    --- 返回场景中每个 Layer 组件的数组。
    ---
    ---@return LayerComponent[]
    function Scene.Component_GetLayerArray() end

    --- 返回场景中每个 Transform 组件的数组。
    ---
    ---@return TransformComponent[]
    function Scene.Component_GetTransformArray() end

    --- 返回场景中每个 Camera 组件的数组。
    ---
    ---@return CameraComponent[]
    function Scene.Component_GetCameraArray() end

    --- 返回场景中每个 Animation 组件的数组。
    ---
    ---@return AnimationComponent[]
    function Scene.Component_GetAnimationArray() end

    --- 返回场景中每个 Material 组件的数组。
    ---
    ---@return MaterialComponent[]
    function Scene.Component_GetMaterialArray() end

    --- 返回场景中每个 Emitter 组件的数组。
    ---
    ---@return EmitterComponent[]
    function Scene.Component_GetEmitterArray() end

    --- 返回场景中每个 Light 组件的数组。
    ---
    ---@return LightComponent[]
    function Scene.Component_GetLightArray() end

    --- 返回场景中每个 Object 组件的数组。
    ---
    ---@return ObjectComponent[]
    function Scene.Component_GetObjectArray() end

    --- 返回场景中每个 Mesh 组件的数组。
    ---
    ---@return MeshComponent[]
    function Scene.Component_GetMeshArray() end

    --- 返回场景中每个 InverseKinematics 组件的数组。
    ---
    ---@return InverseKinematicsComponent[]
    function Scene.Component_GetInverseKinematicsArray() end

    --- 返回场景中每个 Spring 组件的数组。
    ---
    ---@return SpringComponent[]
    function Scene.Component_GetSpringArray() end

    --- 返回场景中每个 Script 组件的数组。
    ---
    ---@return ScriptComponent[]
    function Scene.Component_GetScriptArray() end

    --- 返回场景中每个 RigidBodyPhysics 组件的数组。
    ---
    ---@return RigidBodyPhysicsComponent[]
    function Scene.Component_GetRigidBodyPhysicsArray() end

    --- 返回场景中每个 SoftBodyPhysics 组件的数组。
    ---
    ---@return SoftBodyPhysicsComponent[]
    function Scene.Component_GetSoftBodyPhysicsArray() end

    --- 返回场景中每个 ForceField 组件的数组。
    ---
    ---@return ForceFieldComponent[]
    function Scene.Component_GetForceFieldArray() end

    --- 返回场景中每个 Weather 组件的数组。
    ---
    ---@return WeatherComponent[]
    function Scene.Component_GetWeatherArray() end

    --- 返回场景中每个 Sound 组件的数组。
    ---
    ---@return SoundComponent[]
    function Scene.Component_GetSoundArray() end

    --- 返回场景中每个 Video 组件的数组。
    ---
    ---@return VideoComponent[]
    function Scene.Component_GetVideoArray() end

    --- 返回场景中每个 Collider 组件的数组。
    ---
    ---@return ColliderComponent[]
    function Scene.Component_GetColliderArray() end

    --- 返回场景中每个 Expression 组件的数组。
    ---
    ---@return ExpressionComponent[]
    function Scene.Component_GetExpressionArray() end

    --- 返回场景中每个 Humanoid 组件的数组。
    ---
    ---@return HumanoidComponent[]
    function Scene.Component_GetHumanoidArray() end

    --- 返回场景中每个 Decal 组件的数组。
    ---
    ---@return DecalComponent[]
    function Scene.Component_GetDecalArray() end

    --- 返回场景中每个 Sprite 组件的数组。
    ---
    ---@return Sprite[]
    function Scene.Component_GetSpriteArray() end

    --- 返回场景中每个 Font 组件的数组。
    ---
    ---@return SpriteFont[]
    function Scene.Component_GetFontArray() end

    --- 返回场景中每个 VoxelGrid 组件的数组。
    ---
    ---@return VoxelGrid[]
    function Scene.Component_GetVoxelGridArray() end

    --- 返回场景中每个 Metadata 组件的数组。
    ---
    ---@return MetadataComponent[]
    function Scene.Component_GetMetadataArray() end

    --- 返回具有 Name 组件的每个实体的数组。
    ---
    ---@return Entity[]
    function Scene.Entity_GetNameArray() end

    --- 返回具有 Layer 组件的每个实体的数组。
    ---
    ---@return Entity[]
    function Scene.Entity_GetLayerArray() end

    --- 返回具有 Transform 组件的每个实体的数组。
    ---
    ---@return Entity[]
    function Scene.Entity_GetTransformArray() end

    --- 返回具有 Camera 组件的每个实体的数组。
    ---
    ---@return Entity[]
    function Scene.Entity_GetCameraArray() end

    --- 返回具有 Animation 组件的每个实体的数组。
    ---
    ---@return Entity[]
    function Scene.Entity_GetAnimationArray() end

    --- 返回具有 AnimationData 组件的每个实体的数组。
    ---
    ---@return Entity[]
    function Scene.Entity_GetAnimationDataArray() end

    --- 返回具有 Material 组件的每个实体的数组。
    ---
    ---@return Entity[]
    function Scene.Entity_GetMaterialArray() end

    --- 返回具有 Emitter 组件的每个实体的数组。
    ---
    ---@return Entity[]
    function Scene.Entity_GetEmitterArray() end

    --- 返回具有 Light 组件的每个实体的数组。
    ---
    ---@return Entity[]
    function Scene.Entity_GetLightArray() end

    --- 返回具有 Object 组件的每个实体的数组。
    ---
    ---@return Entity[]
    function Scene.Entity_GetObjectArray() end

    --- 返回具有 Mesh 组件的每个实体的数组。
    ---
    ---@return Entity[]
    function Scene.Entity_GetMeshArray() end

    --- 返回具有 InverseKinematics 组件的每个实体的数组。
    ---
    ---@return Entity[]
    function Scene.Entity_GetInverseKinematicsArray() end

    --- 返回具有 Spring 组件的每个实体的数组。
    ---
    ---@return Entity[]
    function Scene.Entity_GetSpringArray() end

    --- 返回具有 Script 组件的每个实体的数组。
    ---
    ---@return Entity[]
    function Scene.Entity_GetScriptArray() end

    --- 返回具有 RigidBodyPhysics 组件的每个实体的数组。
    ---
    ---@return Entity[]
    function Scene.Entity_GetRigidBodyPhysicsArray() end

    --- 返回具有 SoftBodyPhysics 组件的每个实体的数组。
    ---
    ---@return Entity[]
    function Scene.Entity_GetSoftBodyPhysicsArray() end

    --- 返回具有 ForceField 组件的每个实体的数组。
    ---
    ---@return Entity[]
    function Scene.Entity_GetForceFieldArray() end

    --- 返回具有 Weather 组件的每个实体的数组。
    ---
    ---@return Entity[]
    function Scene.Entity_GetWeatherArray() end

    --- 返回具有 Sound 组件的每个实体的数组。
    ---
    ---@return Entity[]
    function Scene.Entity_GetSoundArray() end

    --- 返回具有 Video 组件的每个实体的数组。
    ---
    ---@return Entity[]
    function Scene.Entity_GetVideoArray() end

    --- 返回具有 Collider 组件的每个实体的数组。
    ---
    ---@return Entity[]
    function Scene.Entity_GetColliderArray() end

    --- 返回具有 Expression 组件的每个实体的数组。
    ---
    ---@return Entity[]
    function Scene.Entity_GetExpressionArray() end

    --- 返回具有 Humanoid 组件的每个实体的数组。
    ---
    ---@return Entity[]
    function Scene.Entity_GetHumanoidArray() end

    --- 返回具有 Decal 组件的每个实体的数组。
    ---
    ---@return Entity[]
    function Scene.Entity_GetDecalArray() end

    --- 返回具有 Sprite 组件的每个实体的数组。
    ---
    ---@return Entity[]
    function Scene.Entity_GetSpriteArray() end

    --- 返回具有 VoxelGrid 组件的每个实体的数组。
    ---
    ---@return Entity[]
    function Scene.Entity_GetVoxelGridArray() end

    --- 返回具有 Metadata 组件的每个实体的数组。
    ---
    ---@return Entity[]
    function Scene.Entity_GetMetadataArray() end

    --- 移除实体的名称组件（如果存在）。
    ---
    ---@param entity Entity
    function Scene.Component_RemoveName(entity) end

    --- 移除实体的层组件（如果存在）。
    ---
    ---@param entity Entity
    function Scene.Component_RemoveLayer(entity) end

    --- 移除实体的变换组件（如果存在）。
    ---
    ---@param entity Entity
    function Scene.Component_RemoveTransform(entity) end

    --- 移除实体的相机组件（如果存在）。
    ---
    ---@param entity Entity
    function Scene.Component_RemoveCamera(entity) end

    --- 移除实体的动画组件（如果存在）。
    ---
    ---@param entity Entity
    function Scene.Component_RemoveAnimation(entity) end

    --- 移除 Animation Data 组件。
    ---
    ---@param entity Entity
    function Scene.Component_RemoveAnimationData(entity) end

    --- 移除实体的材质组件（如果存在）。
    ---
    ---@param entity Entity
    function Scene.Component_RemoveMaterial(entity) end

    --- 移除实体的发射器组件（如果存在）。
    ---
    ---@param entity Entity
    function Scene.Component_RemoveEmitter(entity) end

    --- 移除实体的光源组件（如果存在）。
    ---
    ---@param entity Entity
    function Scene.Component_RemoveLight(entity) end

    --- 移除实体的对象组件（如果存在）。
    ---
    ---@param entity Entity
    function Scene.Component_RemoveObject(entity) end

    --- 移除实体的 IK 组件（如果存在）。
    ---
    ---@param entity Entity
    function Scene.Component_RemoveInverseKinematics(entity) end

    --- 移除实体的弹簧组件（如果存在）。
    ---
    ---@param entity Entity
    function Scene.Component_RemoveSpring(entity) end

    --- 移除实体的脚本组件（如果存在）。
    ---
    ---@param entity Entity
    function Scene.Component_RemoveScript(entity) end

    --- 移除实体的 RigidBodyPhysicsComponent（如果存在）。
    ---
    ---@param entity Entity
    function Scene.Component_RemoveRigidBodyPhysics(entity) end

    --- 移除实体的 SoftBodyPhysicsComponent（如果存在）。
    ---
    ---@param entity Entity
    function Scene.Component_RemoveSoftBodyPhysics(entity) end

    --- 移除实体的 ForceFieldComponent（如果存在）。
    ---
    ---@param entity Entity
    function Scene.Component_RemoveForceField(entity) end

    --- 移除实体的 WeatherComponent（如果存在）。
    ---
    ---@param entity Entity
    function Scene.Component_RemoveWeather(entity) end

    --- 移除实体的 SoundComponent（如果存在）。
    ---
    ---@param entity Entity
    function Scene.Component_RemoveSound(entity) end

    --- 移除实体的 VideoComponent（如果存在）。
    ---
    ---@param entity Entity
    function Scene.Component_RemoveVideo(entity) end

    --- 移除实体的 ColliderComponent（如果存在）。
    ---
    ---@param entity Entity
    function Scene.Component_RemoveCollider(entity) end

    --- 移除实体的 ExpressionComponent（如果存在）。
    ---
    ---@param entity Entity
    function Scene.Component_RemoveExpression(entity) end

    --- 移除实体的 HumanoidComponent（如果存在）。
    ---
    ---@param entity Entity
    function Scene.Component_RemoveHumanoid(entity) end

    --- 移除实体的 DecalComponent（如果存在）。
    ---
    ---@param entity Entity
    function Scene.Component_RemoveDecal(entity) end

    --- 移除实体的 Sprite（如果存在）。
    ---
    ---@param entity Entity
    function Scene.Component_RemoveSprite(entity) end

    --- 移除实体的 SpriteFont（如果存在）。
    ---
    ---@param entity Entity
    function Scene.Component_RemoveFont(entity) end

    --- 移除实体的 VoxelGrid（如果存在）。
    ---
    ---@param entity Entity
    function Scene.Component_RemoveVoxelGrid(entity) end

    --- 移除实体的 MetadataComponent（如果存在）。
    ---
    ---@param entity Entity
    function Scene.Component_RemoveMetadata(entity) end

    --- 将实体附加到父级（向实体添加层次结构组件）。从现在起，
    --- 实体将从父级继承某些属性，如变换（实体将随父级移动）或
    --- 层（实体的层将是父级层的子层）。如果 child_already_in_local_space
    --- 为 false，则子级将被转换到父级的本地空间，如果为 true，则
    --- 按原样使用。
    ---
    ---@param entity Entity
    ---@param parent Entity
    ---@param child_already_in_local_space? boolean
    function Scene.Component_Attach(
        entity,
        parent,
        child_already_in_local_space
    ) end

    --- 将实体从父级分离（如果存在 HierarchyComponent）。
    --- 恢复实体的原始层，并将当前变换应用到实体。
    ---
    ---@param entity Entity
    function Scene.Component_Detach(entity) end

    --- 从父级分离所有子级，如同对其所有子级调用 Component_Detach。
    ---
    ---@param parent Entity
    function Scene.Component_DetachChildren(parent) end

    --- 返回完全包含场景中对象的 AABB。仅在场景
    --- 更新后有效。
    ---
    ---@return AABB
    function Scene.GetBounds() end

    --- 返回天气。
    ---
    ---@return WeatherComponent
    function Scene.GetWeather() end

    --- 设置天气。
    ---
    ---@param weather WeatherComponent
    function Scene.SetWeather(weather) end

    --- 将动画从一个人形重定向到另一个人形，使新动画将在
    --- 目标人形上播放。dst：动画将适配到的目标人形
    --- src：要复制的动画，它应该已经针对人形骨骼。
    --- bake_data：如果为 true，重定向的数据将烘焙到新的动画数据中。
    --- 如果为 false，它将重用源动画数据而不创建新的，重定向将
    --- 在每次 Update 时在运行时应用。返回新动画的实体 ID，如果
    --- 重定向不成功则返回 INVALID_ENTITY
    ---
    ---@param dst Entity
    ---@param src Entity
    ---@param bake_data boolean
    ---@param src_scene? Scene  包含 src 的场景（默认为此场景）。
    ---
    ---@return Entity
    function Scene.RetargetAnimation(dst, src, bake_data, src_scene) end

    --- 将指定实体的姿态重置为绑定姿态。绑定姿态取自
    --- ArmatureComponent 的骨骼绑定矩阵。如果实体没有骨架，
    --- 则它将查找实体的子骨架。
    ---
    ---@param entity Entity
    function Scene.ResetPose(entity) end

    --- 返回从世界空间位置看到的海洋表面上的近似位置。如果当前
    --- 天气未启用海洋，返回世界位置本身。结果位置是近似的，
    --- 因为它涉及从 GPU 回读到 CPU，因此结果可能比当前 GPU 模拟
    --- 延迟。注意，此函数的输入位置将取 XZ 平面并由位移图的 XZ 值
    --- 修改，Y（垂直）位置将仅取自海洋水面高度和位移图。
    ---
    ---@param worldPosition Vector
    function Scene.GetOceanPosAt(worldPosition) end

    --- 将单个对象体素化到体素网格中。subtract 参数控制是添加
    --- （true）还是移除（false）体素。lod 参数选择对象的细节
    --- 级别。
    ---
    ---@param objectIndex integer
    ---@param voxelgrid VoxelGrid
    ---@param subtract? boolean
    ---@param lod? integer
    function Scene.VoxelizeObject(objectIndex, voxelgrid, subtract, lod) end

    --- 将场景中与体素网格体积相交且匹配 filterMask 和
    --- layerMask 的所有实体体素化。subtract 参数控制是添加
    --- （true）还是移除（false）体素。lod 参数选择对象的细节
    --- 级别。
    ---
    ---@param voxelgrid VoxelGrid
    ---@param subtract? boolean
    ---@param filterMask? integer
    ---@param layerMask? integer
    ---@param lod? integer
    function Scene.VoxelizeScene(
        voxelgrid,
        subtract,
        filterMask,
        layerMask,
        lod
    ) end

    --- 维护实用工具，帮助修复 TransformComponent 中的 NaN 问题。
    --- 包含 nan 的变换将被清除并用 `_nanfix` 后缀重命名。
    function Scene.FixupNans() end

    --- 将 EmitterComponent 附加到实体。
    ---
    ---@param entity Entity
    ---
    ---@return EmitterComponent
    function Scene.Component_CreateEmitter(entity) end

    --- 将 HairParticleSystem 附加到实体。
    ---
    ---@param entity Entity
    ---
    ---@return HairParticleSystem
    function Scene.Component_CreateHairParticleSystem(entity) end

    --- 将 MaterialComponent 附加到实体。
    ---
    ---@param entity Entity
    ---
    ---@return MaterialComponent
    function Scene.Component_CreateMaterial(entity) end

    --- 将 CharacterComponent 附加到实体。
    ---
    ---@param entity Entity
    ---
    ---@return CharacterComponent
    function Scene.Component_CreateCharacter(entity) end

    --- 返回实体的 MeshComponent（如果存在）。
    ---
    ---@param entity Entity
    ---
    ---@return MeshComponent?
    function Scene.Component_GetMesh(entity) end

    --- 返回实体的 HairParticleSystem（如果存在）。
    ---
    ---@param entity Entity
    ---
    ---@return HairParticleSystem?
    function Scene.Component_GetHairParticleSystem(entity) end

    --- 返回实体的 SpriteFont（如果存在）。
    ---
    ---@param entity Entity
    ---
    ---@return SpriteFont?
    function Scene.Component_GetFont(entity) end

    --- 返回实体的 CharacterComponent（如果存在）。
    ---
    ---@param entity Entity
    ---
    ---@return CharacterComponent?
    function Scene.Component_GetCharacter(entity) end

    --- 返回场景中每个 HairParticleSystem 组件的数组。
    ---
    ---@return HairParticleSystem[]
    function Scene.Component_GetHairParticleSystemArray() end

    --- 返回场景中每个 Character 组件的数组。
    ---
    ---@return CharacterComponent[]
    function Scene.Component_GetCharacterArray() end

    --- 返回具有 HairParticleSystem 组件的每个实体的数组。
    ---
    ---@return Entity[]
    function Scene.Entity_GetHairParticleSystemArray() end

    --- 返回具有 Character 组件的每个实体的数组。
    ---
    ---@return Entity[]
    function Scene.Entity_GetCharacterArray() end

    --- 移除实体的 MeshComponent（如果存在）。
    ---
    ---@param entity Entity
    function Scene.Component_RemoveMesh(entity) end

    --- 移除实体的 HairParticleSystem（如果存在）。
    ---
    ---@param entity Entity
    function Scene.Component_RemoveHairParticleSystem(entity) end

    --- 移除实体的 CharacterComponent（如果存在）。
    ---
    ---@param entity Entity
    function Scene.Component_RemoveCharacter(entity) end
```

#### RayIntersectionResult

```lua
    --- 创建空的 RayIntersectionResult。通常这些由
    --- `scene.IntersectsAll` 返回，而不是直接构造。
    ---
    ---@return RayIntersectionResult
    function RayIntersectionResult() end

    --- scene.IntersectsAll 中一次命中的结果。
    ---
    ---@class RayIntersectionResult
    local RayIntersectionResult = {}

    --- 返回实体。
    ---
    ---@return Entity
    function RayIntersectionResult.GetEntity() end

    --- 返回位置。
    ---
    ---@return Vector
    function RayIntersectionResult.GetPosition() end

    --- 返回法线。
    ---
    ---@return Vector
    function RayIntersectionResult.GetNormal() end

    --- 返回 UV。
    ---
    ---@return Vector
    function RayIntersectionResult.GetUV() end

    --- 返回速度。
    ---
    ---@return Vector
    function RayIntersectionResult.GetVelocity() end

    --- 返回距离。
    ---
    ---@return number
    function RayIntersectionResult.GetDistance() end

    --- 返回子集索引。
    ---
    ---@return integer
    function RayIntersectionResult.GetSubsetIndex() end

    --- 返回顶点 id0。
    ---
    ---@return integer
    function RayIntersectionResult.GetVertexID0() end

    --- 返回顶点 id1。
    ---
    ---@return integer
    function RayIntersectionResult.GetVertexID1() end

    --- 返回顶点 id2。
    ---
    ---@return integer
    function RayIntersectionResult.GetVertexID2() end

    --- 返回重心坐标。
    ---
    ---@return Vector
    function RayIntersectionResult.GetBarycentrics() end

    --- 返回方向。
    ---
    ---@return Vector
    function RayIntersectionResult.GetOrientation() end

    --- 返回人形骨骼。
    ---
    ---@return integer
    function RayIntersectionResult.GetHumanoidBone() end
```

#### SphereIntersectionResult

```lua
    --- 创建空的 SphereIntersectionResult。通常这些由
    --- `scene.IntersectsAll` 返回，而不是直接构造。
    ---
    ---@return SphereIntersectionResult
    function SphereIntersectionResult() end

    --- scene.IntersectsAll 中一次命中的结果。
    ---
    ---@class SphereIntersectionResult
    local SphereIntersectionResult = {}

    --- 返回实体。
    ---
    ---@return Entity
    function SphereIntersectionResult.GetEntity() end

    --- 返回位置。
    ---
    ---@return Vector
    function SphereIntersectionResult.GetPosition() end

    --- 返回法线。
    ---
    ---@return Vector
    function SphereIntersectionResult.GetNormal() end

    --- 返回速度。
    ---
    ---@return Vector
    function SphereIntersectionResult.GetVelocity() end

    --- 返回深度。
    ---
    ---@return number
    function SphereIntersectionResult.GetDepth() end

    --- 返回子集索引。
    ---
    ---@return integer
    function SphereIntersectionResult.GetSubsetIndex() end

    --- 返回方向。
    ---
    ---@return Vector
    function SphereIntersectionResult.GetOrientation() end

    --- 返回人形骨骼。
    ---
    ---@return integer
    function SphereIntersectionResult.GetHumanoidBone() end
```

#### NameComponent

```lua
    --- 创建新的、独立的 NameComponent，拥有自己的数据。
    ---
    ---@return NameComponent
    function NameComponent() end

    --- 持有一个字符串，能比实体 ID 更容易地用人类可读方式标识
    --- 实体。
    ---
    ---@class NameComponent
    ---
    ---@field Name string
    local NameComponent = {}

    --- 设置名称。
    ---
    ---@param value string
    function NameComponent.SetName(value) end

    --- 查询名称字符串。
    ---
    ---@return any
    function NameComponent.GetName() end
```

#### LayerComponent

```lua
    --- 创建新的、独立的 LayerComponent，拥有自己的数据。
    ---
    ---@return LayerComponent
    function LayerComponent() end

    --- 整数掩码，可用于将实体分组以进行某些操作，如拾取、
    --- 渲染等。
    ---
    ---@class LayerComponent
    ---
    ---@field LayerMask number
    local LayerComponent = {}

    --- 设置层掩码。
    ---
    ---@param value integer
    function LayerComponent.SetLayerMask(value) end

    --- 查询层掩码。
    ---
    ---@return integer
    function LayerComponent.GetLayerMask() end
```

#### TransformComponent

```lua
    --- 创建新的、独立的 TransformComponent，拥有自己的数据。
    ---
    ---@return TransformComponent
    function TransformComponent() end

    --- 描述 3D 空间中的方向。
    ---
    ---@class TransformComponent
    ---
    ---@field Translation_local Vector 查询世界空间中的位置
    ---@field Rotation_local Vector
    ---@field Scale_local Vector 查询世界空间中的缩放
    local TransformComponent = {}

    --- 应用缩放。
    ---
    ---@param vectorXYZ Vector
    function TransformComponent.Scale(vectorXYZ) end

    --- 应用统一缩放。
    ---
    ---@param value number
    function TransformComponent.Scale(value) end

    --- 应用 roll、pitch、yaw 旋转。
    ---
    ---@param vectorRollPitchYaw Vector
    function TransformComponent.Rotate(vectorRollPitchYaw) end

    --- 应用四元数旋转。
    ---
    ---@param quaternion Vector
    function TransformComponent.RotateQuaternion(quaternion) end

    --- 应用平移（位置偏移）。
    ---
    ---@param vectorXYZ Vector
    function TransformComponent.Translate(vectorXYZ) end

    --- 在两个变换组件之间线性插值。
    ---
    ---@param a TransformComponent
    ---@param b TransformComponent
    ---@param t number
    function TransformComponent.Lerp(a, b, t) end

    --- 在样条上四个变换组件之间插值。
    ---
    ---@param a TransformComponent
    ---@param b TransformComponent
    ---@param c TransformComponent
    ---@param d TransformComponent
    ---@param t number
    function TransformComponent.CatmullRom(a, b, c, d, t) end

    --- 应用变换矩阵。
    ---
    ---@param matrix Matrix
    function TransformComponent.MatrixTransform(matrix) end

    --- 检索表示变换组件当前方向的 4x4 变换矩阵。
    ---
    ---@return Matrix
    function TransformComponent.GetMatrix() end

    --- 重置到世界原点，即位置变为 Vector(0,0,0)，
    --- 旋转四元数变为 Vector(0,0,0,1)，缩放变为
    --- Vector(1,1,1)。
    function TransformComponent.ClearTransform() end

    --- 更新底层变换矩阵。
    function TransformComponent.UpdateTransform() end

    --- 查询世界空间中的位置。
    ---
    ---@return Vector
    function TransformComponent.GetPosition() end

    --- 查询世界空间中的四元数旋转。
    ---
    ---@return Vector
    function TransformComponent.GetRotation() end

    --- 查询世界空间中的缩放。
    ---
    ---@return Vector
    function TransformComponent.GetScale() end

    --- 设置本地空间缩放。
    ---
    ---@param value Vector
    function TransformComponent.SetScale(value) end

    --- 设置本地空间四元数旋转。
    ---
    ---@param quaternnion Vector
    function TransformComponent.SetRotation(quaternnion) end

    --- 设置本地空间位置。
    ---
    ---@param value Vector
    function TransformComponent.SetPosition(value) end

    --- 使其无效，这将导致变换在下次场景更新时被更新。
    ---
    ---@param value boolean
    function TransformComponent.SetDirty(value) end

    --- 检查变换自上次更新以来是否已失效。
    ---
    ---@return boolean
    function TransformComponent.IsDirty() end

    --- 返回前方方向。
    ---
    ---@return Vector
    function TransformComponent.GetForward() end

    --- 返回向上方向。
    ---
    ---@return Vector
    function TransformComponent.GetUp() end

    --- 返回右方向。
    ---
    ---@return Vector
    function TransformComponent.GetRight() end
```

#### CameraComponent

```lua
    --- 创建新的、独立的 CameraComponent，拥有自己的数据。
    ---
    ---@return CameraComponent
    function CameraComponent() end

    --- 表示相机：其位置、方向和投影，用于从视点渲染
    --- 场景。
    ---
    ---@class CameraComponent
    ---
    ---@field FOV number
    ---@field NearPlane number
    ---@field FarPlane number
    ---@field FocalLength number
    ---@field ApertureSize number
    ---@field ApertureShape number
    local CameraComponent = {}

    --- 更新相机矩阵。
    function CameraComponent.UpdateCamera() end

    --- 将变换的方向复制到相机，并设置相机位置、观察方向和向上
    --- 方向。相机矩阵不会立即更新。它们将由 Scene::Update() 更新
    --- （如果相机是场景的一部分），或通过手动调用 UpdateCamera()。
    ---
    ---@param transform TransformComponent
    function CameraComponent.TransformCamera(transform) end

    --- 变换相机。
    ---
    ---@param matrix Matrix
    function CameraComponent.TransformCamera(matrix) end

    --- 返回 FOV。
    ---
    ---@return number
    function CameraComponent.GetFOV() end

    --- 设置相机的垂直视场角（值为弧度）。
    ---
    ---@param value number
    function CameraComponent.SetFOV(value) end

    --- 返回近裁剪面。
    ---
    ---@return number
    function CameraComponent.GetNearPlane() end

    --- 设置相机的近裁剪面，指定靠近观察者的渲染截断。
    --- 必须是大于零的值。
    ---
    ---@param value number
    function CameraComponent.SetNearPlane(value) end

    --- 返回远裁剪面。
    ---
    ---@return number
    function CameraComponent.GetFarPlane() end

    --- 设置相机的远裁剪面（视距）。
    ---
    ---@param value number
    function CameraComponent.SetFarPlane(value) end

    --- 返回焦距。
    ---
    ---@return number
    function CameraComponent.GetFocalLength() end

    --- 设置相机的焦距（对焦距离）。由景深使用。
    ---
    ---@param value number
    function CameraComponent.SetFocalLength(value) end

    --- 返回光圈大小。
    ---
    ---@return number
    function CameraComponent.GetApertureSize() end

    --- 设置相机的光圈大小。较大的值将使景深效果更强。
    ---
    ---@param value number
    function CameraComponent.SetApertureSize(value) end

    --- 返回光圈形状。
    ---
    ---@return number
    function CameraComponent.GetApertureShape() end

    --- 设置相机的光圈形状，用于景深效果。值的 `.X` 元素
    --- 指定水平形状，`.Y` 元素指定垂直形状。
    ---
    ---@param value Vector
    function CameraComponent.SetApertureShape(value) end

    --- 返回视图矩阵。
    ---
    ---@return Matrix
    function CameraComponent.GetView() end

    --- 返回投影矩阵。
    ---
    ---@return Matrix
    function CameraComponent.GetProjection() end

    --- 返回视图投影矩阵。
    ---
    ---@return Matrix
    function CameraComponent.GetViewProjection() end

    --- 返回逆视图矩阵。
    ---
    ---@return Matrix
    function CameraComponent.GetInvView() end

    --- 返回逆投影矩阵。
    ---
    ---@return Matrix
    function CameraComponent.GetInvProjection() end

    --- 返回逆视图投影矩阵。
    ---
    ---@return Matrix
    function CameraComponent.GetInvViewProjection() end

    --- 返回位置。
    ---
    ---@return Vector
    function CameraComponent.GetPosition() end

    --- 返回观察方向。
    ---
    ---@return Vector
    function CameraComponent.GetLookDirection() end

    --- 返回向上方向。
    ---
    ---@return Vector
    function CameraComponent.GetUpDirection() end

    --- 返回右方向。
    ---
    ---@return Vector
    function CameraComponent.GetRightDirection() end

    --- 设置相机位置。此后应使用 `UpdateCamera()` 来应用
    --- 该值。
    ---
    ---@param value Vector
    function CameraComponent.SetPosition(value) end

    --- 设置相机的观察方向。值必须是归一化的方向 `Vector`，
    --- 相对于相机位置，且与向上方向垂直。此后应使用
    --- `UpdateCamera()` 来应用该值。如果使用 `TransformCamera()`
    --- 函数，此值也将从变换的旋转中设置。
    ---
    ---@param value Vector
    function CameraComponent.SetLookDirection(value) end

    --- 设置相机的向上方向。这必须是归一化的方向 `Vector`，
    --- 相对于相机位置，且与观察方向垂直。此后应使用
    --- `UpdateCamera()` 来应用该值。如果使用 `TransformCamera()`
    --- 函数，此值也将从变换的旋转中设置。
    ---
    ---@param value Vector
    function CameraComponent.SetUpDirection(value) end

    --- 为相机启用正交投影。
    ---
    ---@param value boolean
    function CameraComponent.SetOrtho(value) end

    --- 如果相机使用正交投影则返回 true，否则返回 false。
    ---
    ---@return boolean
    function CameraComponent.IsOrtho() end

    --- 返回正交垂直大小。
    ---
    ---@return number
    function CameraComponent.GetOrthoVerticalSize() end

    --- 设置相机在世界空间中的垂直大小，仅在正交投影模式下
    --- 使用。
    ---
    ---@param value number
    function CameraComponent.SetOrthoVerticalSize(value) end

    --- 将世界空间点投影到画布逻辑宽度和高度单位内的屏幕空间
    --- （屏幕宽度和高度）。如果 Z 坐标为正，表示在相机前方，
    --- 否则在后方（可视为被裁剪）。
    ---
    ---@param point Vector
    ---@param canvas Canvas
    function CameraComponent.ProjectToScreen(point, canvas) end
```

#### AnimationComponent

```lua
    --- 创建新的、独立的 AnimationComponent，拥有自己的数据。
    ---
    ---@return AnimationComponent
    function AnimationComponent() end

    --- 在实体上播放和控制动画（骨骼或属性动画）。
    ---
    ---@class AnimationComponent
    ---
    ---@field Timer number
    ---@field Amount number
    local AnimationComponent = {}

    --- 播放。
    function AnimationComponent.Play() end

    --- 停止。
    function AnimationComponent.Stop() end

    --- 暂停。
    function AnimationComponent.Pause() end

    --- 设置动画连续重复。
    ---
    ---@param value boolean
    function AnimationComponent.SetLooped(value) end

    --- 如果动画设置为连续重复则返回 true。
    ---
    ---@return boolean
    function AnimationComponent.IsLooped() end

    --- 返回是否正在播放。
    ---
    ---@return boolean
    function AnimationComponent.IsPlaying() end

    --- 设置计时器。
    ---
    ---@param value number
    function AnimationComponent.SetTimer(value) end

    --- 返回计时器。
    ---
    ---@return number
    function AnimationComponent.GetTimer() end

    --- 设置量。
    ---
    ---@param value number
    function AnimationComponent.SetAmount(value) end

    --- 返回量。
    ---
    ---@return number
    function AnimationComponent.GetAmount() end

    --- 返回起始。
    ---
    ---@return number
    function AnimationComponent.GetStart() end

    --- 设置起始。
    ---
    ---@param value number
    function AnimationComponent.SetStart(value) end

    --- 返回结束。
    ---
    ---@return number
    function AnimationComponent.GetEnd() end

    --- 设置结束。
    ---
    ---@param value number
    function AnimationComponent.SetEnd(value) end

    --- 设置动画向前然后向后重复播放。
    ---
    ---@param value boolean
    function AnimationComponent.SetPingPong(value) end

    --- 如果动画设置为向前然后向后重复播放则返回 true。
    ---
    ---@return boolean
    function AnimationComponent.IsPingPong() end

    --- 设置动画只播放一次。
    function AnimationComponent.SetPlayOnce() end

    --- 如果动画设置为只播放一次则返回 true。
    ---
    ---@return boolean
    function AnimationComponent.IsPlayingOnce() end

    --- 返回动画是否已到达结尾。
    ---
    ---@return boolean
    function AnimationComponent.IsEnded() end

    --- 返回是否启用根运动。
    ---
    ---@return boolean
    function AnimationComponent.IsRootMotion() end

    --- 为此动画启用根运动。
    function AnimationComponent.RootMotionOn() end

    --- 为此动画禁用根运动。
    function AnimationComponent.RootMotionOff() end

    --- 返回根运动平移。
    ---
    ---@return Vector
    function AnimationComponent.GetRootTranslation() end

    --- 返回根运动旋转作为四元数。
    ---
    ---@return Vector
    function AnimationComponent.GetRootRotation() end
```

#### MaterialComponent

```lua
    --- 创建新的、独立的 MaterialComponent，拥有自己的数据。
    ---
    ---@return MaterialComponent
    function MaterialComponent() end

    --- 对象的表面材质：颜色、纹理和 PBR 着色参数。
    ---
    ---@class MaterialComponent
    ---
    ---@field Saturation number
    ---@field _flags integer
    ---@field BaseColor Vector
    ---@field EmissiveColor Vector
    ---@field EngineStencilRef integer
    ---@field UserStencilRef integer
    ---@field ShaderType integer
    ---@field UserBlendMode integer
    ---@field SpecularColor Vector
    ---@field SubsurfaceScattering Vector
    ---@field TexMulAdd Vector
    ---@field Roughness number
    ---@field Reflectance number
    ---@field Metalness number
    ---@field NormalMapStrength number
    ---@field ParallaxOcclusionMapping number
    ---@field DisplacementMapping number
    ---@field Refraction number
    ---@field Transmission number
    ---@field Cloak number
    ---@field ChromaticAberration number
    ---@field AlphaRef number
    ---@field SheenColor Vector
    ---@field SheenRoughness number
    ---@field Clearcoat number
    ---@field ClearcoatRoughness number
    ---@field ShadingRate integer
    ---@field TexAnimDirection Vector
    ---@field TexAnimFrameRate number
    ---@field texAnimElapsedTime number
    ---@field customShaderID integer
    local MaterialComponent = {}

    --- 设置基础颜色。
    ---
    ---@param value Vector
    function MaterialComponent.SetBaseColor(value) end

    --- 设置自发光颜色。
    ---
    ---@param value Vector
    function MaterialComponent.SetEmissiveColor(value) end

    --- 设置引擎模板参考。
    ---
    ---@param value integer
    function MaterialComponent.SetEngineStencilRef(value) end

    --- 设置用户模板参考。
    ---
    ---@param value integer
    function MaterialComponent.SetUserStencilRef(value) end

    --- 返回模板参考。
    ---
    ---@return integer
    function MaterialComponent.GetStencilRef() end

    --- 设置纹理乘加。
    ---
    ---@param vector Vector
    function MaterialComponent.SetTexMulAdd(vector) end

    --- 返回纹理乘加。
    ---
    ---@return Vector
    function MaterialComponent.GetTexMulAdd() end

    --- 设置纹理。
    ---
    ---@param slot TextureSlot
    ---@param texturefile string
    function MaterialComponent.SetTexture(slot, texturefile) end

    --- 设置纹理。
    ---
    ---@param slot TextureSlot
    ---@param texture Texture
    function MaterialComponent.SetTexture(slot, texture) end

    --- 设置纹理 UV 集。
    ---
    ---@param slot TextureSlot
    ---@param uvset integer
    function MaterialComponent.SetTextureUVSet(slot, uvset) end

    --- 返回纹理。
    ---
    ---@param slot TextureSlot
    ---
    ---@return Texture
    function MaterialComponent.GetTexture(slot) end

    --- 返回纹理名称。
    ---
    ---@param slot TextureSlot
    ---
    ---@return any
    function MaterialComponent.GetTextureName(slot) end

    --- 返回纹理 UV 集。
    ---
    ---@param slot TextureSlot
    ---
    ---@return integer
    function MaterialComponent.GetTextureUVSet(slot) end

    --- 设置是否投射阴影。
    ---
    ---@param value boolean
    function MaterialComponent.SetCastShadow(value) end

    --- 返回是否投射阴影。
    ---
    ---@return boolean
    function MaterialComponent.IsCastingShadow() end

    --- 强制透明材质在不透明通道中绘制（对共面
    --- 多边形有用）
    ---
    ---@param value boolean
    function MaterialComponent.SetCoplanarBlending(value) end

    --- 返回是否共面混合。
    ---
    ---@return boolean
    function MaterialComponent.IsCoplanarBlending() end

    --- 标识 MaterialComponent 上的纹理槽（基础颜色、法线
    --- 贴图、表面贴图等）。
    ---
    ---@enum TextureSlot
    TextureSlot = {
        BASECOLORMAP = 0,
        NORMALMAP = 1,
        SURFACEMAP = 2,
        EMISSIVEMAP = 3,
        DISPLACEMENTMAP = 4,
        OCCLUSIONMAP = 5,
        TRANSMISSIONMAP = 6,
        SHEENCOLORMAP = 7,
        SHEENROUGHNESSMAP = 8,
        CLEARCOATMAP = 9,
        CLEARCOATROUGHNESSMAP = 10,
        CLEARCOATNORMALMAP = 11,
        SPECULARMAP = 12,
        ANISOTROPYMAP = 13,
        TRANSPARENCYMAP = 14,
    }

    -- 着色器类型，用于 `MaterialComponent.SetShaderType`。

    --- 标准基于物理的渲染着色器。
    ---
    ---@type integer
    SHADERTYPE_PBR = 0

    --- 带平面反射的 PBR。
    ---
    ---@type integer
    SHADERTYPE_PBR_PLANARREFLECTION = 1

    --- 带视差遮挡映射的 PBR。
    ---
    ---@type integer
    SHADERTYPE_PBR_PARALLAXOCCLUSIONMAPPING = 2

    --- 带各向异性镜面反射的 PBR。
    ---
    ---@type integer
    SHADERTYPE_PBR_ANISOTROPIC = 3

    --- 水面着色器。
    ---
    ---@type integer
    SHADERTYPE_WATER = 4

    --- 卡通着色器。
    ---
    ---@type integer
    SHADERTYPE_CARTOON = 5

    --- 无光照着色器（无光照）。
    ---
    ---@type integer
    SHADERTYPE_UNLIT = 6

    --- PBR 布料着色器。
    ---
    ---@type integer
    SHADERTYPE_PBR_CLOTH = 7

    --- 带清漆的 PBR。
    ---
    ---@type integer
    SHADERTYPE_PBR_CLEARCOAT = 8

    --- 带清漆的 PBR 布料。
    ---
    ---@type integer
    SHADERTYPE_PBR_CLOTH_CLEARCOAT = 9

    --- 引擎模板参考：空。
    ---
    ---@type integer
    STENCILREF_EMPTY = 0

    --- 引擎模板参考：默认。
    ---
    ---@type integer
    STENCILREF_DEFAULT = 1

    --- 引擎模板参考：自定义着色器。
    ---
    ---@type integer
    STENCILREF_CUSTOMSHADER = 2

    --- 引擎模板参考：轮廓。
    ---
    ---@type integer
    STENCILREF_OUTLINE = 3

    --- 引擎模板参考：自定义着色器和轮廓。
    ---
    ---@type integer
    STENCILREF_CUSTOMSHADER_OUTLINE = 4

    --- 引擎模板参考：皮肤。
    ---
    ---@type integer
    STENCILREF_SKIN = 3

    --- 引擎模板参考：雪。
    ---
    ---@type integer
    STENCILREF_SNOW = 4
```

#### MeshComponent

```lua
    --- 创建新的、独立的 MeshComponent，拥有自己的数据。
    ---
    ---@return MeshComponent
    function MeshComponent() end

    --- 几何数据（顶点、索引和子集），由对象引用和
    --- 渲染。
    ---
    ---@class MeshComponent
    ---
    ---@field _flags integer
    ---@field TessellationFactor number
    ---@field ArmatureID integer
    ---@field SubsetsPerLOD integer
    local MeshComponent = {}

    --- 设置网格子集材质 ID。
    ---
    ---@param subsetindex integer
    ---@param materialID Entity
    function MeshComponent.SetMeshSubsetMaterialID(subsetindex, materialID) end

    --- 返回网格子集材质 ID。
    ---
    ---@param subsetindex integer
    ---
    ---@return Entity
    function MeshComponent.GetMeshSubsetMaterialID(subsetindex) end

    --- 创建包含所有面的子集，返回子集索引。
    ---
    ---@return integer
    function MeshComponent.CreateSubset() end
```

#### EmitterComponent

```lua
    --- 创建新的、独立的 EmitterComponent，拥有自己的数据。
    ---
    ---@return EmitterComponent
    function EmitterComponent() end

    --- 附加到实体的 GPU 粒子发射器。
    ---
    ---@class EmitterComponent
    ---
    ---@field _flags integer
    ---@field ShaderType integer
    ---@field Mass number
    ---@field Velocity Vector
    ---@field Gravity Vector
    ---@field Drag number
    ---@field Restitution number
    ---@field EmitCount number 每秒发射的粒子数
    ---@field Size number 粒子起始大小
    ---@field Life number 粒子寿命
    ---@field NormalFactor number 调制发射速度的法线因子
    ---@field Randomness number 一般随机因子
    ---@field LifeRandomness number 寿命随机因子
    ---@field ScaleX number 沿寿命在 X 轴的缩放
    ---@field ScaleY number 沿寿命在 Y 轴的缩放
    ---@field Rotation number 旋转速度
    ---@field MotionBlurAmount number 设置运动拉长因子
    ---@field SPH_h number
    ---@field SPH_K number
    ---@field SPH_p0 number
    ---@field SPH_e number
    ---@field SpriteSheet_Frames_X integer
    ---@field SpriteSheet_Frames_Y integer
    ---@field SpriteSheet_Frame_Count integer
    ---@field SpriteSheet_Frame_Start integer
    ---@field SpriteSheet_Framerate number
    local EmitterComponent = {}

    --- 立即生成特定数量的粒子。
    ---
    ---@param value integer
    function EmitterComponent.Burst(value) end

    --- 在指定位置和颜色乘数处立即生成特定数量的粒子。
    ---
    ---@param value integer
    ---@param position Vector
    ---@param color? Vector
    function EmitterComponent.Burst(value, position, color) end

    --- 在指定位置和颜色乘数处立即生成特定数量的粒子。
    ---
    ---@param value integer
    ---@param transform Matrix
    ---@param color? Vector
    function EmitterComponent.Burst(value, transform, color) end

    --- 设置每秒发射的粒子数。
    ---
    ---@param value number
    function EmitterComponent.SetEmitCount(value) end

    --- 设置粒子起始大小。
    ---
    ---@param value number
    function EmitterComponent.SetSize(value) end

    --- 设置粒子寿命。
    ---
    ---@param value number
    function EmitterComponent.SetLife(value) end

    --- 设置调制发射速度的法线因子。
    ---
    ---@param value number
    function EmitterComponent.SetNormalFactor(value) end

    --- 设置一般随机因子。
    ---
    ---@param value number
    function EmitterComponent.SetRandomness(value) end

    --- 设置寿命随机因子。
    ---
    ---@param value number
    function EmitterComponent.SetLifeRandomness(value) end

    --- 设置沿寿命在 X 轴的缩放。
    ---
    ---@param value number
    function EmitterComponent.SetScaleX(value) end

    --- 设置沿寿命在 Y 轴的缩放。
    ---
    ---@param value number
    function EmitterComponent.SetScaleY(value) end

    --- 设置旋转速度。
    ---
    ---@param value number
    function EmitterComponent.SetRotation(value) end

    --- 设置运动拉长因子。
    ---
    ---@param value number
    function EmitterComponent.SetMotionBlurAmount(value) end

    --- 禁用 GPU 碰撞器。
    ---
    ---@param value boolean
    function EmitterComponent.SetCollidersDisabled(value) end

    --- 返回碰撞器是否禁用。
    function EmitterComponent.IsCollidersDisabled() end

    --- 返回最后已知的活动粒子计数（注意粒子在 GPU 上跟踪，
    --- 因此此值可能已过时）。
    ---
    ---@return integer
    function EmitterComponent.GetCurrentParticleCount() end
```

#### HairParticleSystem

```lua
    --- 创建新的、独立的 HairParticleSystem，拥有自己的数据。
    ---
    ---@return HairParticleSystem
    function HairParticleSystem() end

    --- 附加到实体的 GPU 毛发或草地粒子系统。
    ---
    ---@class HairParticleSystem
    ---
    ---@field _flags integer
    ---@field StrandCount integer
    ---@field SegmentCount integer
    ---@field RandomSeed integer
    ---@field Length number
    ---@field Stiffness number
    ---@field Randomness number
    ---@field ViewDistance number
    ---@field SpriteSheet_Frames_X integer
    ---@field SpriteSheet_Frames_Y integer
    ---@field SpriteSheet_Frame_Count integer
    ---@field SpriteSheet_Frame_Start integer
    local HairParticleSystem = {}
```

#### LightComponent

```lua
    --- 创建新的、独立的 LightComponent，拥有自己的数据。
    ---
    ---@return LightComponent
    function LightComponent() end

    --- 场景中的光源（方向光、点光源或聚光灯）。
    ---
    ---@class LightComponent
    ---
    ---@field Type integer
    ---@field Range number
    ---@field Intensity number
    ---@field Color Vector
    ---@field CastShadow boolean
    ---@field VolumetricsEnabled boolean
    ---@field OuterConeAngle number 聚光灯外锥角，以弧度为单位
    ---@field InnerConeAngle number 聚光灯内锥角，以弧度为单位
    local LightComponent = {}

    --- 方向光。
    ---
    ---@type integer
    DIRECTIONAL = 0

    --- 点光源。
    ---
    ---@type integer
    POINT = 1

    --- 聚光灯。
    ---
    ---@type integer
    SPOT = 2

    --- 球形区域光类型。
    ---
    ---@type integer
    SPHERE = 3

    --- 圆盘区域光类型。
    ---
    ---@type integer
    DISC = 4

    --- 矩形区域光类型。
    ---
    ---@type integer
    RECTANGLE = 5

    --- 管形区域光类型。
    ---
    ---@type integer
    TUBE = 6

    --- 设置光源类型，参见下方可接受的值（默认为点光源）。
    ---
    ---@param type integer
    function LightComponent.SetType(type) end

    --- 设置范围。
    ---
    ---@param value number
    function LightComponent.SetRange(value) end

    --- 光的亮度。单位取决于光源类型：点光源和聚光灯使用坎
    --- 德拉 (lm/sr) 表示发光强度，方向光使用勒克斯 (lm/m2) 表示
    --- 照度。参见 glTF KHR_lights_punctual 规范：
    --- https://github.com/KhronosGroup/glTF/tree/main/extensions/2.0/Khronos/KHR_lights_punctual
    ---
    ---@param value number
    function LightComponent.SetIntensity(value) end

    --- 设置颜色。
    ---
    ---@param value Vector
    function LightComponent.SetColor(value) end

    --- 设置是否投射阴影。
    ---
    ---@param value boolean
    function LightComponent.SetCastShadow(value) end

    --- 启用或禁用体积光。
    ---
    ---@param value boolean
    function LightComponent.SetVolumetricsEnabled(value) end

    --- 聚光灯外锥角，以弧度为单位。
    ---
    ---@param value number
    function LightComponent.SetOuterConeAngle(value) end

    --- 聚光灯内锥角，以弧度为单位（0 <= innerConeAngle <=
    --- outerConeAngle）。值为 0 禁用内锥角。
    ---
    ---@param value number
    function LightComponent.SetInnerConeAngle(value) end

    --- 返回类型。
    ---
    ---@return integer
    function LightComponent.GetType() end

    --- 保留与非物理光单位的向后兼容性（v0.70.0 之前）。
    ---
    ---@param value number
    function LightComponent.SetEnergy(value) end

    --- 保留与 FOV 角度的向后兼容性（v0.70.0 之前）。
    ---
    ---@param value number
    function LightComponent.SetFOV(value) end

    --- 返回光源是否投射阴影。
    ---
    ---@return boolean
    function LightComponent.IsCastShadow() end

    --- 返回是否启用体积光。
    ---
    ---@return boolean
    function LightComponent.IsVolumetricsEnabled() end
```

#### ObjectComponent

```lua
    --- 创建新的、独立的 ObjectComponent，拥有自己的数据。
    ---
    ---@return ObjectComponent
    function ObjectComponent() end

    --- 将网格作为可渲染实例放入场景中，带每实例
    --- 渲染选项。
    ---
    ---@class ObjectComponent
    ---
    ---@field MeshID integer
    ---@field CascadeMask integer
    ---@field RendertypeMask integer
    ---@field Color Vector
    ---@field EmissiveColor Vector
    ---@field UserStencilRef integer
    ---@field LodDistanceMultiplier number
    ---@field DrawDistance number
    local ObjectComponent = {}

    --- 返回网格 ID。
    ---
    ---@return Entity
    function ObjectComponent.GetMeshID() end

    --- 返回级联掩码。
    ---
    ---@return integer
    function ObjectComponent.GetCascadeMask() end

    --- 返回渲染类型掩码。
    ---
    ---@return integer
    function ObjectComponent.GetRendertypeMask() end

    --- 返回颜色。
    ---
    ---@return Vector
    function ObjectComponent.GetColor() end

    --- 返回自发光颜色。
    ---
    ---@return Vector
    function ObjectComponent.GetEmissiveColor() end

    --- 返回用户模板参考。
    ---
    ---@return integer
    function ObjectComponent.GetUserStencilRef() end

    --- 返回绘制距离。
    ---
    ---@return number
    function ObjectComponent.GetDrawDistance() end

    --- 设置网格 ID。
    ---
    ---@param entity Entity
    function ObjectComponent.SetMeshID(entity) end

    --- 设置级联掩码。
    ---
    ---@param value integer
    function ObjectComponent.SetCascadeMask(value) end

    --- 设置渲染类型掩码。
    ---
    ---@param value integer
    function ObjectComponent.SetRendertypeMask(value) end

    --- 设置颜色。
    ---
    ---@param value Vector
    function ObjectComponent.SetColor(value) end

    --- 设置轮廓高光的 RGB 颜色。
    ---
    ---@param value Vector
    function ObjectComponent.SetRimHighlightColor(value) end

    --- 设置轮廓高光颜色的强度（乘数）。
    ---
    ---@param value number
    function ObjectComponent.SetRimHighlightIntensity(value) end

    --- 设置轮廓高光的衰减幂。
    ---
    ---@param value number
    function ObjectComponent.SetRimHighlightFalloff(value) end

    --- 设置自发光颜色。
    ---
    ---@param value Vector
    function ObjectComponent.SetEmissiveColor(value) end

    --- 设置用户模板参考。
    ---
    ---@param value integer
    function ObjectComponent.SetUserStencilRef(value) end

    --- 设置绘制距离。
    ---
    ---@param value number
    function ObjectComponent.SetDrawDistance(value) end

    --- 启用/禁用前景对象渲染。前景对象将始终在常规对象之上
    --- 渲染，对 FPS 武器或手有用。
    ---
    ---@param value boolean
    function ObjectComponent.SetForeground(value) end

    --- 返回是否为前景。
    ---
    ---@return boolean
    function ObjectComponent.IsForeground() end

    --- 你可以将对象设置为在主相机中不可见，但它在反射和阴影中
    --- 仍然可见，对 FPS 角色模型有用。
    ---
    ---@param value boolean
    function ObjectComponent.SetNotVisibleInMainCamera(value) end

    --- 返回是否在主相机中不可见。
    ---
    ---@return boolean
    function ObjectComponent.IsNotVisibleInMainCamera() end

    --- 你可以将对象设置为在主相机中不可见，但它在反射和阴影中
    --- 仍然可见，对吸血鬼有用。
    ---
    ---@param value boolean
    function ObjectComponent.SetNotVisibleInReflections(value) end

    --- 返回是否在反射中不可见。
    ---
    ---@return boolean
    function ObjectComponent.IsNotVisibleInReflections() end

    --- 为对象启用湿度贴图，这将自动跟踪湿度。
    ---
    ---@param value boolean
    function ObjectComponent.SetWetmapEnabled(value) end

    --- 返回湿度贴图是否启用。
    ---
    ---@return boolean
    function ObjectComponent.IsWetmapEnabled() end

    --- 可以关闭对象的渲染。
    ---
    ---@param value boolean
    function ObjectComponent.SetRenderable(value) end

    --- 返回是否可渲染。
    ---
    ---@return boolean
    function ObjectComponent.IsRenderable() end

    --- 返回 alpha 测试参考值。
    ---
    ---@return number
    function ObjectComponent.GetAlphaRef() end

    --- 设置 alpha 测试参考值。
    ---
    ---@param value number
    function ObjectComponent.SetAlphaRef(value) end
```

#### InverseKinematicsComponent

描述反向运动学效果器。

```lua
    --- 创建新的、独立的 InverseKinematicsComponent，拥有自己的
    --- 数据。
    ---
    ---@return InverseKinematicsComponent
    function InverseKinematicsComponent() end

    --- 使用反向运动学驱动一串骨骼朝向目标实体。
    ---
    ---@class InverseKinematicsComponent
    ---
    ---@field Target integer
    ---@field ChainLength integer
    ---@field IterationCount integer
    local InverseKinematicsComponent = {}

    --- 设置目标实体（IK 实体及其父层次结构链将
    --- 尝试到达目标）。
    ---
    ---@param entity Entity
    function InverseKinematicsComponent.SetTarget(entity) end

    --- 设置链长度，换句话说，IK 系统将计算多少父级。
    ---
    ---@param value integer
    function InverseKinematicsComponent.SetChainLength(value) end

    --- 设置 IK 系统模拟的精度。
    ---
    ---@param value integer
    function InverseKinematicsComponent.SetIterationCount(value) end

    --- 禁用/启用 IK 模拟。
    ---
    ---@param value boolean
    function InverseKinematicsComponent.SetDisabled(value) end

    --- 返回目标。
    ---
    ---@return Entity
    function InverseKinematicsComponent.GetTarget() end

    --- 返回链长度。
    ---
    ---@return integer
    function InverseKinematicsComponent.GetChainLength() end

    --- 返回迭代计数。
    ---
    ---@return integer
    function InverseKinematicsComponent.GetIterationCount() end

    --- 返回是否禁用。
    ---
    ---@return boolean
    function InverseKinematicsComponent.IsDisabled() end
```

#### SpringComponent

```lua
    --- 创建新的、独立的 SpringComponent，拥有自己的数据。
    ---
    ---@return SpringComponent
    function SpringComponent() end

    --- 为变换添加弹簧/摇晃物理效果，用于柔和的次级运动
    --- 如骨骼。
    ---
    ---@class SpringComponent
    ---
    ---@field Stiffness number
    ---@field Damping number
    ---@field WindAffection number
    ---@field DragForce number
    ---@field HitRadius number
    ---@field GravityPower number
    ---@field GravityDirection Vector
    local SpringComponent = {}

    --- 设置刚度。
    ---
    ---@param value number
    function SpringComponent.SetStiffness(value) end

    --- 设置阻尼。
    ---
    ---@param value number
    function SpringComponent.SetDamping(value) end

    --- 设置风力影响。
    ---
    ---@param value number
    function SpringComponent.SetWindAffection(value) end

```

#### ScriptComponent

```lua
    --- 创建新的、独立的 ScriptComponent，拥有自己的数据。
    ---
    ---@return ScriptComponent
    function ScriptComponent() end

    --- 绑定到实体的 lua 脚本。
    ---
    ---@class ScriptComponent
    local ScriptComponent = {}

    --- 从文件创建。
    ---
    ---@param filename string
    function ScriptComponent.CreateFromFile(filename) end

    --- 播放。
    function ScriptComponent.Play() end

    --- 返回是否正在播放。
    ---
    ---@return boolean
    function ScriptComponent.IsPlaying() end

    --- 设置播放一次。
    ---
    ---@param once boolean
    function ScriptComponent.SetPlayOnce(once) end

    --- 停止。
    function ScriptComponent.Stop() end
```

#### RigidBodyPhysicsComponent

```lua
    --- 创建新的、独立的 RigidBodyPhysicsComponent，拥有自己的
    --- 数据。
    ---
    ---@return RigidBodyPhysicsComponent
    function RigidBodyPhysicsComponent() end

    --- 描述刚体物理对象。
    ---
    ---@class RigidBodyPhysicsComponent
    ---
    ---@field Shape integer
    ---@field Mass number
    ---@field Friction number
    ---@field Restitution number
    ---@field LinearDamping number
    ---@field AngularDamping number
    ---@field Buoyancy number
    ---@field BoxParams_HalfExtents Vector
    ---@field SphereParams_Radius number
    ---@field CapsuleParams_Radius number
    ---@field CapsuleParams_Height number
    ---@field TargetMeshLOD integer
    ---@field MaxSlopeAngle number 角色物理最大坡度角，以弧度为单位
    ---@field GravityFactor number 角色物理重力因子
    local RigidBodyPhysicsComponent = {}

    --- 如果这是载具则返回 true，否则返回 false。
    ---
    ---@return boolean
    function RigidBodyPhysicsComponent.IsVehicle() end

    --- 如果这是汽车载具则返回 true，否则返回 false。
    ---
    ---@return boolean
    function RigidBodyPhysicsComponent.IsCar() end

    --- 如果这是摩托车载具则返回 true，否则返回 false。
    ---
    ---@return boolean
    function RigidBodyPhysicsComponent.IsMotorcycle() end

    --- 检查刚体是否能在不活动后停用。
    ---
    ---@return boolean
    function RigidBodyPhysicsComponent.IsDisableDeactivation() end

    --- 检查刚体是可移动的还是仅静态的。
    ---
    ---@return boolean
    function RigidBodyPhysicsComponent.IsKinematic() end

    --- 检查刚体在添加到模拟时是否设置为停用。
    ---
    ---@return boolean
    function RigidBodyPhysicsComponent.IsStartDeactivated() end

    --- 设置刚体是否能在不活动后停用。
    ---
    ---@param value boolean
    function RigidBodyPhysicsComponent.SetDisableDeactivation(value) end

    --- 将刚体设置为运动学（意味着它针对由系统或用户逻辑移动
    --- 进行了优化，而非物理引擎）。
    ---
    ---@param value boolean
    function RigidBodyPhysicsComponent.SetKinematic(value) end

    --- 如果为 true，刚体在添加到模拟时将被停用（如果是动态的，
    --- 不会下落）。
    ---
    ---@param value boolean
    function RigidBodyPhysicsComponent.SetStartDeactivated(value) end

    --- 启用由物理引擎驱动的角色物理。
    ---
    ---@param value boolean
    function RigidBodyPhysicsComponent.SetCharacterPhysics(value) end

    --- 如果此刚体启用了角色物理则返回 true。
    ---
    ---@return boolean
    function RigidBodyPhysicsComponent.IsCharacterPhysics() end

    --- 将物理锁定到 2D 平面（XY 平移，Z 旋转）。
    ---
    ---@param value boolean
    function RigidBodyPhysicsComponent.SetLocked2D(value) end

    --- 如果物理锁定到 2D 平面则返回 true。
    ---
    ---@return boolean
    function RigidBodyPhysicsComponent.IsLocked2D() end

    --- RigidBodyPhysicsComponent 的碰撞形状。
    ---
    ---@enum RigidBodyShape
    RigidBodyShape = {
        Box = 0,
        Sphere = 1,
        Capsule = 2,
        ConvexHull = 3,
        TriangleMesh = 4,
    }
```

#### SoftBodyPhysicsComponent

```lua
    --- 创建新的、独立的 SoftBodyPhysicsComponent，拥有自己的
    --- 数据。
    ---
    ---@return SoftBodyPhysicsComponent
    function SoftBodyPhysicsComponent() end

    --- 描述软体物理对象。
    ---
    ---@class SoftBodyPhysicsComponent
    ---
    ---@field Mass number
    ---@field Friction number
    ---@field Restitution number
    ---@field VertexRadius number
    local SoftBodyPhysicsComponent = {}

    --- 设置软体模拟相对于图形网格的细节程度。设置此值将
    --- 重建软体，因此单独的物理顶点设置将丢失。
    ---
    ---@param value number
    function SoftBodyPhysicsComponent.SetDetail(value) end

    --- 返回细节。
    ---
    ---@return number
    function SoftBodyPhysicsComponent.GetDetail() end

    --- 设置禁用停用。
    ---
    ---@param value boolean
    function SoftBodyPhysicsComponent.SetDisableDeactivation(value) end

    --- 返回是否禁用停用。
    ---
    ---@return boolean
    function SoftBodyPhysicsComponent.IsDisableDeactivation() end

    --- 启用或禁用风。
    ---
    ---@param value boolean
    function SoftBodyPhysicsComponent.SetWindEnabled(value) end

    --- 返回风是否启用。
    ---
    ---@return boolean
    function SoftBodyPhysicsComponent.IsWindEnabled() end

    --- 从网格创建。
    ---
    ---@param mesh MeshComponent
    function SoftBodyPhysicsComponent.CreateFromMesh(mesh) end
```

#### ForceFieldComponent

```lua
    --- 创建新的、独立的 ForceFieldComponent，拥有自己的数据。
    ---
    ---@return ForceFieldComponent
    function ForceFieldComponent() end

    --- 吸引或排斥粒子和物理体的力场（点或平面类型）。
    ---
    ---@class ForceFieldComponent
    ---
    ---@field Type integer
    ---@field Gravity number
    ---@field Range number
    local ForceFieldComponent = {}
```

#### WeatherComponent

```lua
    --- 创建新的、独立的 WeatherComponent，拥有自己的数据。
    ---
    ---@return WeatherComponent
    function WeatherComponent() end

    --- 全局环境设置：天空、雾、风、星星、雨、海洋、云
    --- 和环境光照。
    ---
    ---@class WeatherComponent
    ---
    ---@field fogHeightSky number
    ---@field cloudiness number
    ---@field cloudScale number
    ---@field cloudSpeed number
    ---@field cloud_shadow_amount number
    ---@field cloud_shadow_scale number
    ---@field cloud_shadow_speed number
    ---@field rainLength number
    ---@field skyMapName string
    ---@field colorGradingMapName string
    ---@field volumetricCloudsWeatherMapFirstName string
    ---@field volumetricCloudsWeatherMapSecondName string
    ---@field OceanParameters OceanParameters
    ---@field AtmosphereParameters AtmosphereParameters
    ---@field VolumetricCloudParameters VolumetricCloudParameters
    ---@field SkyMapName string 天空纹理的资源名称
    ---@field ColorGradingMapName string 颜色分级贴图的资源名称
    ---@field sunColor Vector
    ---@field sunDirection Vector
    ---@field skyExposure number
    ---@field horizon Vector
    ---@field zenith Vector
    ---@field ambient Vector
    ---@field fogStart number
    ---@field fogDensity number
    ---@field fogHeightStart number
    ---@field fogHeightEnd number
    ---@field windDirection Vector
    ---@field windRandomness number
    ---@field windWaveSize number
    ---@field windSpeed number
    ---@field stars number
    ---@field rainAmount number
    ---@field rainLenght number
    ---@field rainSpeed number
    ---@field rainScale number
    ---@field rainColor Vector
    ---@field gravity Vector
    local WeatherComponent = {}

    --- 检查天气的海洋模拟是否启用。
    ---
    ---@return boolean
    function WeatherComponent.IsOceanEnabled() end

    --- 检查天气的天空是否以简单、非现实的方式渲染。
    ---
    ---@return boolean
    function WeatherComponent.IsSimpleSky() end

    --- 检查天气的天空是否以物理正确、现实的方式渲染。
    ---
    ---@return boolean
    function WeatherComponent.IsRealisticSky() end

    --- 检查天气是否正在渲染体积云。
    ---
    ---@return boolean
    function WeatherComponent.IsVolumetricClouds() end

    --- 检查天气是否正在渲染高度雾视觉效果。
    ---
    ---@return boolean
    function WeatherComponent.IsHeightFog() end

    --- 设置天气的海洋模拟是否启用。
    ---
    ---@param value boolean
    function WeatherComponent.SetOceanEnabled(value) end

    --- 设置天气的天空是否以简单、非现实的方式渲染。
    ---
    ---@param value boolean
    function WeatherComponent.SetSimpleSky(value) end

    --- 设置天气的天空是否以物理正确、现实的方式渲染。
    ---
    ---@param value boolean
    function WeatherComponent.SetRealisticSky(value) end

    --- 设置天气是否正在渲染体积云。
    ---
    ---@param value boolean
    function WeatherComponent.SetVolumetricClouds(value) end

    --- 设置天气是否正在渲染高度雾视觉效果。
    ---
    ---@param value boolean
    function WeatherComponent.SetHeightFog(value) end

    --- 返回是否启用体积云投射阴影。
    ---
    ---@return boolean
    function WeatherComponent.IsVolumetricCloudsCastShadow() end

    --- 返回是否启用覆盖雾颜色。
    ---
    ---@return boolean
    function WeatherComponent.IsOverrideFogColor() end

    --- 返回是否启用真实天空空中透视。
    ---
    ---@return boolean
    function WeatherComponent.IsRealisticSkyAerialPerspective() end

    --- 返回是否启用真实天空高质量。
    ---
    ---@return boolean
    function WeatherComponent.IsRealisticSkyHighQuality() end

    --- 返回是否启用真实天空接收阴影。
    ---
    ---@return boolean
    function WeatherComponent.IsRealisticSkyReceiveShadow() end

    --- 返回是否启用体积云接收阴影。
    ---
    ---@return boolean
    function WeatherComponent.IsVolumetricCloudsReceiveShadow() end

    --- 设置是否启用体积云投射阴影。
    ---
    ---@param value boolean
    function WeatherComponent.SetVolumetricCloudsCastShadow(value) end

    --- 设置是否启用覆盖雾颜色。
    ---
    ---@param value boolean
    function WeatherComponent.SetOverrideFogColor(value) end

    --- 设置是否启用真实天空空中透视。
    ---
    ---@param value boolean
    function WeatherComponent.SetRealisticSkyAerialPerspective(value) end

    --- 设置是否启用真实天空高质量。
    ---
    ---@param value boolean
    function WeatherComponent.SetRealisticSkyHighQuality(value) end

    --- 设置是否启用真实天空接收阴影。
    ---
    ---@param value boolean
    function WeatherComponent.SetRealisticSkyReceiveShadow(value) end

    --- 设置是否启用体积云接收阴影。
    ---
    ---@param value boolean
    function WeatherComponent.SetVolumetricCloudsReceiveShadow(value) end
```

##### OceanParameters

```lua
    --- 创建新的、独立的 OceanParameters，拥有自己的数据。
    ---
    ---@return OceanParameters
    function OceanParameters() end

    --- 海洋模拟的参数，通过 weather.OceanParameters 访问。
    ---
    ---@class OceanParameters
    ---
    ---@field dmap_dim integer
    ---@field patch_length number
    ---@field time_scale number
    ---@field wave_amplitude number
    ---@field wind_dir Vector
    ---@field wind_speed number
    ---@field wind_dependency number
    ---@field choppy_scale number
    ---@field waterColor Vector
    ---@field waterHeight number
    ---@field surfaceDetail integer
    ---@field surfaceDisplacementTolerance number
    local OceanParameters = {}
```

##### AtmosphereParameters

基于物理的大气和天空参数，通过 `weather.AtmosphereParameters` 访问。

```lua
    --- 创建新的、独立的 AtmosphereParameters，拥有自己的数据。
    ---
    ---@return AtmosphereParameters
    function AtmosphereParameters() end

    --- 基于物理的大气和天空参数，通过
    --- weather.AtmosphereParameters 访问。
    ---
    ---@class AtmosphereParameters
    ---
    ---@field bottomRadius number
    ---@field topRadius number
    ---@field planetCenter Vector
    ---@field rayleighDensityExpScale number
    ---@field rayleighScattering Vector
    ---@field mieDensityExpScale number
    ---@field mieScattering Vector
    ---@field mieExtinction Vector
    ---@field mieAbsorption Vector
    ---@field miePhaseG number
    ---@field absorptionDensity0LayerWidth number
    ---@field absorptionDensity0ConstantTerm number
    ---@field absorptionDensity0LinearTerm number
    ---@field absorptionDensity1ConstantTerm number
    ---@field absorptionDensity1LinearTerm number
    ---@field absorptionExtinction Vector
    ---@field groundAlbedo Vector
    local AtmosphereParameters = {}
```

##### VolumetricCloudParameters

```lua
    --- 创建新的、独立的 VolumetricCloudParameters，拥有自己的
    --- 数据。
    ---
    ---@return VolumetricCloudParameters
    function VolumetricCloudParameters() end

    --- 体积云渲染参数，通过
    --- `weather.VolumetricCloudParameters` 访问。
    ---
    ---@class VolumetricCloudParameters
    ---
    ---@field cloudAmbientGroundMultiplier number
    ---@field horizonBlendAmount number
    ---@field horizonBlendPower number
    ---@field cloudStartHeight number
    ---@field cloudThickness number
    ---@field animationMultiplier number
    ---@field albedoFirst Vector
    ---@field extinctionCoefficientFirst Vector
    ---@field skewAlongWindDirectionFirst number
    ---@field totalNoiseScaleFirst number
    ---@field curlScaleFirst number
    ---@field curlNoiseModifierFirst number
    ---@field detailScaleFirst number
    ---@field detailNoiseModifierFirst number
    ---@field skewAlongCoverageWindDirectionFirst number
    ---@field weatherScaleFirst number
    ---@field coverageAmountFirst number
    ---@field coverageMinimumFirst number
    ---@field typeAmountFirst number
    ---@field typeMinimumFirst number
    ---@field rainAmountFirst number
    ---@field rainMinimumFirst number
    ---@field gradientSmallFirst number
    ---@field gradientMediumFirst number
    ---@field gradientLargeFirst number
    ---@field anvilDeformationSmallFirst number
    ---@field anvilDeformationMediumFirst number
    ---@field anvilDeformationLargeFirst number
    ---@field windSpeedFirst number
    ---@field windAngleFirst number
    ---@field windUpAmountFirst number
    ---@field coverageWindSpeedFirst number
    ---@field coverageWindAngleFirst number
    ---@field albedoSecond Vector
    ---@field extinctionCoefficientSecond Vector
    ---@field skewAlongWindDirectionSecond number
    ---@field totalNoiseScaleSecond number
    ---@field curlScaleSecond number
    ---@field curlNoiseModifierSecond number
    ---@field detailScaleSecond number
    ---@field detailNoiseModifierSecond number
    ---@field skewAlongCoverageWindDirectionSecond number
    ---@field weatherScaleSecond number
    ---@field coverageAmountSecond number
    ---@field coverageMinimumSecond number
    ---@field typeAmountSecond number
    ---@field typeMinimumSecond number
    ---@field rainAmountSecond number
    ---@field rainMinimumSecond number
    ---@field gradientSmallSecond number
    ---@field gradientMediumSecond number
    ---@field gradientLargeSecond number
    ---@field anvilDeformationSmallSecond number
    ---@field anvilDeformationMediumSecond number
    ---@field anvilDeformationLargeSecond number
    ---@field windSpeedSecond number
    ---@field windAngleSecond number
    ---@field windUpAmountSecond number
    ---@field coverageWindSpeedSecond number
    ---@field coverageWindAngleSecond number
    local VolumetricCloudParameters = {}
```

#### SoundComponent

```lua
    --- 创建新的、独立的 SoundComponent，拥有自己的数据。
    ---
    ---@return SoundComponent
    function SoundComponent() end

    --- 描述 Sound 对象。
    ---
    ---@class SoundComponent
    ---
    ---@field Filename string
    ---@field Volume number
    local SoundComponent = {}

    --- 播放声音。
    function SoundComponent.Play() end

    --- 停止声音。
    function SoundComponent.Stop() end

    --- 设置播放时声音是否循环。
    ---
    ---@param value boolean
    function SoundComponent.SetLooped(value) end

    --- 禁用/启用 3D 声音。
    ---
    ---@param value boolean
    function SoundComponent.SetDisable3D(value) end

    --- 检查声音是否正在播放。
    ---
    ---@return boolean
    function SoundComponent.IsPlaying() end

    --- 检查声音是否循环。
    ---
    ---@return boolean
    function SoundComponent.IsLooped() end

    --- 设置声音。
    ---
    ---@param sound Sound
    function SoundComponent.SetSound(sound) end

    --- 设置声音实例。
    ---
    ---@param inst SoundInstance
    function SoundComponent.SetSoundInstance(inst) end

    --- 返回声音。
    ---
    ---@return Sound
    function SoundComponent.GetSound() end

    --- 返回声音实例。
    ---
    ---@return SoundInstance
    function SoundComponent.GetSoundInstance() end

    --- 设置声音文件路径。
    ---
    ---@param filename string
    function SoundComponent.SetFilename(filename) end

    --- 设置播放音量。
    ---
    ---@param volume number
    function SoundComponent.SetVolume(volume) end

    --- 返回声音文件路径。
    ---
    ---@return string
    function SoundComponent.GetFilename() end

    --- 返回播放音量。
    ---
    ---@return number
    function SoundComponent.GetVolume() end

    --- 返回是否禁用 3D 空间化。
    ---
    ---@return boolean
    function SoundComponent.IsDisable3D() end
```

#### VideoComponent

描述视频对象。

```lua
    --- 创建新的、独立的 VideoComponent，拥有自己的数据。
    ---
    ---@return VideoComponent
    function VideoComponent() end

    --- 在场景中播放视频文件。
    ---
    ---@class VideoComponent
    ---
    ---@field Filename string
    local VideoComponent = {}

    --- 播放。
    function VideoComponent.Play() end

    --- 停止。
    function VideoComponent.Stop() end

    --- 设置循环。
    ---
    ---@param value boolean
    function VideoComponent.SetLooped(value) end

    --- 返回是否正在播放。
    ---
    ---@return boolean
    function VideoComponent.IsPlaying() end

    --- 返回是否循环。
    ---
    ---@return boolean
    function VideoComponent.IsLooped() end

    --- 返回视频长度，以秒为单位。
    ---
    ---@return number
    function VideoComponent.GetLength() end

    --- 返回当前计时器，以秒为单位。
    ---
    ---@return number
    function VideoComponent.GetCurrentTimer() end

    --- 将解码器状态设置为从特定时间（以秒为单位）解码
    --- （大约）。
    ---
    ---@param timerSeconds number
    function VideoComponent.Seek(timerSeconds) end

    --- 设置视频。
    ---
    ---@param video Video
    function VideoComponent.SetVideo(video) end

    --- 设置视频实例。
    ---
    ---@param instance VideoInstance
    function VideoComponent.SetVideoInstance(instance) end

    --- 返回视频。
    ---
    ---@return Video
    function VideoComponent.GetVideo() end

    --- 返回视频实例。
    ---
    ---@return VideoInstance
    function VideoComponent.GetVideoInstance() end

    --- 设置视频文件路径。
    ---
    ---@param filename string
    function VideoComponent.SetFilename(filename) end

    --- 返回视频文件路径。
    ---
    ---@return string
    function VideoComponent.GetFilename() end
```

#### ColliderComponent

描述 Collider 对象。

```lua
    --- 创建新的、独立的 ColliderComponent，拥有自己的数据。
    ---
    ---@return ColliderComponent
    function ColliderComponent() end

    --- 简单的碰撞图元（球体、胶囊体或平面），用于
    --- 角色和软体碰撞。
    ---
    ---@class ColliderComponent
    ---
    ---@field Shape integer 碰撞器的形状
    ---@field Radius number
    ---@field Offset Vector
    ---@field Tail Vector
    local ColliderComponent = {}

    --- 启用或禁用 CPU。
    ---
    ---@param value boolean
    function ColliderComponent.SetCPUEnabled(value) end

    --- 启用或禁用 GPU。
    ---
    ---@param value boolean
    function ColliderComponent.SetGPUEnabled(value) end

    --- 返回胶囊体。
    ---
    ---@return Capsule
    function ColliderComponent.GetCapsule() end

    --- 返回球体。
    ---
    ---@return Sphere
    function ColliderComponent.GetSphere() end

    --- ColliderComponent 的形状。
    ---
    ---@enum ColliderShape
    ColliderShape = {
        Sphere = 0,
        Capsule = 1,
        Plane = 2,
    }
```

#### ExpressionComponent

```lua
    --- 创建新的、独立的 ExpressionComponent，拥有自己的数据。
    ---
    ---@return ExpressionComponent
    function ExpressionComponent() end

    --- 控制角色的面部表情和混合形状权重。
    ---
    ---@class ExpressionComponent
    local ExpressionComponent = {}

    --- 按名称在 ExpressionComponent 中查找表情。
    ---
    ---@param name string
    ---
    ---@return integer
    function ExpressionComponent.FindExpressionID(name) end

    --- 按 ID 设置表情权重。ID 可以是非预设表情。使用
    --- FindExpressionID() 检索非预设表情 ID。
    ---
    ---@param id integer
    ---
    ---@param weight number
    function ExpressionComponent.SetWeight(id, weight) end

    --- 返回表情的当前权重。
    ---
    ---@param id integer
    ---
    ---@return number
    function ExpressionComponent.GetWeight(id) end

    --- 设置预设表情的权重。你可以从 ExpressionPreset 表获取
    --- 预设值。
    ---
    ---@param preset ExpressionPreset
    ---@param weight number
    function ExpressionComponent.SetPresetWeight(preset, weight) end

    --- 返回预设表情的当前权重。
    ---
    ---@param preset ExpressionPreset
    ---
    ---@return number
    function ExpressionComponent.GetPresetWeight(preset) end

    --- 强制连续说话动画，即使没有声音在播放。
    ---
    ---@param value boolean
    function ExpressionComponent.SetForceTalkingEnabled(value) end

    --- 返回是否启用强制说话。
    ---
    ---@return boolean
    function ExpressionComponent.IsForceTalkingEnabled() end

    --- 设置预设覆盖嘴部。
    ---
    ---@param preset ExpressionPreset
    ---@param override ExpressionOverride
    function ExpressionComponent.SetPresetOverrideMouth(preset, override) end

    --- 设置预设覆盖眨眼。
    ---
    ---@param preset ExpressionPreset
    ---@param override ExpressionOverride
    function ExpressionComponent.SetPresetOverrideBlink(preset, override) end

    --- 设置预设覆盖视线。
    ---
    ---@param preset ExpressionPreset
    ---@param override ExpressionOverride
    function ExpressionComponent.SetPresetOverrideLook(preset, override) end

    --- 设置覆盖嘴部。
    ---
    ---@param id integer
    ---@param override ExpressionOverride
    function ExpressionComponent.SetOverrideMouth(id, override) end

    --- 设置覆盖眨眼。
    ---
    ---@param id integer
    ---@param override ExpressionOverride
    function ExpressionComponent.SetOverrideBlink(id, override) end

    --- 设置覆盖视线。
    ---
    ---@param id integer
    ---@param override ExpressionOverride
    function ExpressionComponent.SetOverrideLook(id, override) end

    --- ExpressionComponent 的标准面部表情预设（VRM 风格）。
    ---
    ---@enum ExpressionPreset
    ExpressionPreset = {
        Happy = 0,
        Angry = 1,
        Sad = 2,
        Relaxed = 3,
        Surprised = 4,
        Aa = 5,
        Ih = 6,
        Ou = 7,
        Ee = 8,
        Oh = 9,
        Blink = 10,
        BlinkLeft = 11,
        BlinkRight = 12,
        LookUp = 13,
        LookDown = 14,
        LookLeft = 15,
        LookRight = 16,
        Neutral = 17,
        None = 0,
        Block = 1,
        Blend = 2,
    }

    --- ExpressionComponent 覆盖如何与程序动画混合。
    ---@enum ExpressionOverride
    ExpressionOverride = {
        None = 0,
        Block = 1,
        Blend = 2,
    }
```

#### HumanoidComponent

```lua
    --- 创建新的、独立的 HumanoidComponent，拥有自己的数据。
    ---
    ---@return HumanoidComponent
    function HumanoidComponent() end

    --- 将实体的骨架映射到标准人形骨骼，启用
    --- 重定向和布娃娃。
    ---
    ---@class HumanoidComponent
    local HumanoidComponent = {}

    --- 获取映射到指定人形骨骼的实体。使用
    --- HumanoidBone 表获取人形骨骼值。
    ---
    ---@param bone HumanoidBone
    ---
    ---@return Entity
    function HumanoidComponent.GetBoneEntity(bone) end

    --- 启用/禁用自动 lookAt（用于头部和眼睛移动）。
    ---
    ---@param value boolean
    function HumanoidComponent.SetLookAtEnabled(value) end

    --- 设置目标 lookAt 位置（用于头部和眼睛移动）。
    ---
    ---@param value Vector
    function HumanoidComponent.SetLookAt(value) end

    --- 激活动态布娃娃物理。注意运动学布娃娃物理始终
    --- 活动（布娃娃默认是动画驱动的/运动学的）。
    ---
    ---@param value boolean
    function HumanoidComponent.SetRagdollPhysicsEnabled(value) end

    --- 返回是否启用布娃娃物理。
    ---
    ---@return boolean
    function HumanoidComponent.IsRagdollPhysicsEnabled() end

    --- 完全禁用此人形的布娃娃物理对象创建。
    ---
    ---@param value boolean
    function HumanoidComponent.SetRagdollDisabled(value) end

    --- 返回布娃娃是否禁用。
    ---
    ---@return boolean
    function HumanoidComponent.IsRagdollDisabled() end

    --- 将布娃娃锁定到 2D 平面（XY 平移，Z 旋转）。
    ---
    ---@param value boolean
    function HumanoidComponent.SetRagdoll2D(value) end

    --- 返回是否为 ragdoll2d。
    ---
    ---@return boolean
    function HumanoidComponent.IsRagdoll2D() end

    --- 关闭此布娃娃的相交测试。这仅影响直接
    --- 与 Scene::Intersects() 的相交检查。
    ---
    ---@param value boolean
    function HumanoidComponent.SetIntersectionDisabled(value) end

    --- 返回是否禁用相交。
    ---
    ---@return boolean
    function HumanoidComponent.IsIntersectionDisabled() end

    --- 控制除头部外布娃娃身体部分的整体肥胖度
    --- （默认：1）。
    ---
    ---@param value number
    function HumanoidComponent.SetRagdollFatness(value) end

    --- 控制布娃娃头部的整体大小（默认：1）。
    ---
    ---@param value number
    function HumanoidComponent.SetRagdollHeadSize(value) end

    --- 返回布娃娃肥胖度。
    ---
    ---@return number
    function HumanoidComponent.GetRagdollFatness() end

    --- 返回布娃娃头部大小。
    ---
    ---@return number
    function HumanoidComponent.GetRagdollHeadSize() end

    --- 在动画后动态修改手臂间距（负值：拉拢，
    --- 正值：分开）。
    ---
    ---@param value number
    function HumanoidComponent.SetArmSpacing(value) end

    --- 返回手臂间距。
    ---
    ---@return number
    function HumanoidComponent.GetArmSpacing() end

    --- 在动画后动态修改腿部间距（负值：拉拢，
    --- 正值：分开）。
    ---
    ---@param value number
    function HumanoidComponent.SetLegSpacing(value) end

    --- 返回腿部间距。
    ---
    ---@return number
    function HumanoidComponent.GetLegSpacing() end

    --- HumanoidComponent 使用的标准人形骨骼标识符。
    ---
    ---@enum HumanoidBone
    HumanoidBone = {
        Hips = 0,  -- 包含在布娃娃中
        Spine = 1,  -- 包含在布娃娃中
        Chest = 2,
        UpperChest = 3,
        Neck = 4,  -- 包含在布娃娃中
        Head = 5,  -- 如果 Neck 不可用则包含在布娃娃中
        LeftEye = 6,
        RightEye = 7,
        Jaw = 8,
        LeftUpperLeg = 9,  -- 包含在布娃娃中
        LeftLowerLeg = 10,  -- 包含在布娃娃中
        LeftFoot = 11,  -- 包含在布娃娃中
        LeftToes = 12,
        RightUpperLeg = 13,  -- 包含在布娃娃中
        RightLowerLeg = 14,  -- 包含在布娃娃中
        RightFoot = 15,  -- 包含在布娃娃中
        RightToes = 16,
        LeftShoulder = 17,
        LeftUpperArm = 18,  -- 包含在布娃娃中
        LeftLowerArm = 19,  -- 包含在布娃娃中
        LeftHand = 20,
        RightShoulder = 21,
        RightUpperArm = 22,  -- 包含在布娃娃中
        RightLowerArm = 23,  -- 包含在布娃娃中
        RightHand = 24,
        LeftThumbMetacarpal = 25,
        LeftThumbProximal = 26,
        LeftThumbDistal = 27,
        LeftIndexProximal = 28,
        LeftIndexIntermediate = 29,
        LeftIndexDistal = 30,
        LeftMiddleProximal = 31,
        LeftMiddleIntermediate = 32,
        LeftMiddleDistal = 33,
        LeftRingProximal = 34,
        LeftRingIntermediate = 35,
        LeftRingDistal = 36,
        LeftLittleProximal = 37,
        LeftLittleIntermediate = 38,
        LeftLittleDistal = 39,
        RightThumbMetacarpal = 40,
        RightThumbProximal = 41,
        RightThumbDistal = 42,
        RightIndexIntermediate = 43,
        RightIndexDistal = 44,
        RightIndexProximal = 45,
        RightMiddleProximal = 46,
        RightMiddleIntermediate = 47,
        RightMiddleDistal = 48,
        RightRingProximal = 49,
        RightRingIntermediate = 50,
        RightRingDistal = 51,
        RightLittleProximal = 52,
        RightLittleIntermediate = 53,
        RightLittleDistal = 54,
        Count = 55,
    }
```

#### DecalComponent

```lua
    --- 创建新的、独立的 DecalComponent，拥有自己的数据。
    ---
    ---@return DecalComponent
    function DecalComponent() end

    --- 贴花组件是可以放在网格上的带纹理贴纸。大多数属性
    --- 可以通过附加的 `TransformComponent` 和 `MaterialComponent`
    --- 控制。
    ---
    ---@class DecalComponent
    local DecalComponent = {}

    --- 设置贴花仅使用基础颜色纹理的 alpha。对混合
    --- 仅法线贴图贴花有用。
    ---
    ---@param value boolean
    function DecalComponent.SetBaseColorOnlyAlpha(value) end

    --- 返回是否仅基础颜色 alpha。
    ---
    ---@return boolean
    function DecalComponent.IsBaseColorOnlyAlpha() end

    --- 设置坡度混合幂。
    ---
    ---@param value number
    function DecalComponent.SetSlopeBlendPower(value) end

    --- 返回坡度混合幂。
    ---
    ---@return number
    function DecalComponent.GetSlopeBlendPower() end
```

#### MetadataComponent

```lua
    --- 创建新的、独立的 MetadataComponent，拥有自己的数据。
    ---
    ---@return MetadataComponent
    function MetadataComponent() end

    --- 元数据组件可以为实体存储和检索任意数量的命名用户
    --- 值。可以为多个不同的值类型使用相同的名称，但一个值
    --- 不能有多个同名的条目。
    ---
    ---@class MetadataComponent
    local MetadataComponent = {}

    --- 返回是否有 bool。
    ---
    ---@param name string
    ---
    ---@return boolean
    function MetadataComponent.HasBool(name) end

    --- 返回是否有 int。
    ---
    ---@param name string
    ---
    ---@return boolean
    function MetadataComponent.HasInt(name) end

    --- 返回是否有 float。
    ---
    ---@param name string
    ---
    ---@return boolean
    function MetadataComponent.HasFloat(name) end

    --- 返回是否有 string。
    ---
    ---@param name string
    ---
    ---@return boolean
    function MetadataComponent.HasString(name) end

    --- 返回预设。
    ---
    ---@return integer
    function MetadataComponent.GetPreset() end

    --- 返回 bool。
    ---
    ---@param name string
    ---
    ---@return boolean
    function MetadataComponent.GetBool(name) end

    --- 返回 int。
    ---
    ---@param name string
    ---
    ---@return integer
    function MetadataComponent.GetInt(name) end

    --- 返回 float。
    ---
    ---@param name string
    ---
    ---@return number
    function MetadataComponent.GetFloat(name) end

    --- 返回 string。
    ---
    ---@param name string
    ---
    ---@return any
    function MetadataComponent.GetString(name) end

    --- 设置预设。
    ---
    ---@param preset integer
    function MetadataComponent.SetPreset(preset) end

    --- 设置 bool。
    ---
    ---@param name string
    ---@param value boolean
    function MetadataComponent.SetBool(name, value) end

    --- 设置 int。
    ---
    ---@param name string
    ---@param value integer
    function MetadataComponent.SetInt(name, value) end

    --- 设置 float。
    ---
    ---@param name string
    ---@param value number
    function MetadataComponent.SetFloat(name, value) end

    --- 设置 string。
    ---
    ---@param name string
    ---@param value string
    function MetadataComponent.SetString(name, value) end

    --- 用于标记实体的内置元数据类别（玩家、敌人、
    --- 拾取物等）。
    ---
    ---@enum MetadataPreset
    MetadataPreset = {
        Custom = 0,
        Waypoint = 1,
        Player = 2,
        Enemy = 3,
        NPC = 4,
        Pickup = 5,
        Vehicle = 6,
        PointOfInterest = 7,
    }
```

#### CharacterComponent

```lua
    --- 创建新的、独立的 CharacterComponent，拥有自己的数据。
    ---
    ---@return CharacterComponent
    function CharacterComponent() end

    --- 实现基本角色控制器功能，如场景中的移动、腿部反向
    --- 运动学、游泳、水波纹等。注意 CharacterComponent 不使用物理，
    --- 而是自定义角色逻辑。角色将与其他角色、标记为
    --- Navmesh 的对象以及标记为启用 CPU 的碰撞器碰撞。
    ---
    ---@class CharacterComponent
    local CharacterComponent = {}

    --- 启用/禁用角色处理（默认启用）。
    ---
    ---@param value boolean
    function CharacterComponent.SetActive(value) end

    --- 返回角色处理是否活动。
    ---
    ---@return boolean
    function CharacterComponent.IsActive() end

    --- 持续向某方向移动角色。给定向量不需要归一化，其长度
    --- 对应移动量。角色将在下次场景更新时移动。移动将被
    --- 标记为导航网格和 CPU 碰撞器的对象阻挡。如果此实体有
    --- 层组件，该层将用于确保角色不与该层碰撞。
    ---
    ---@param value Vector
    function CharacterComponent.Move(value) end

    --- 类似于 Move，但相对于朝向方向。
    ---
    ---@param value Vector
    function CharacterComponent.Strafe(value) end

    --- 向上跳跃一定量。跳跃将在下次场景更新时执行，
    --- 带碰撞。
    ---
    ---@param amount number
    function CharacterComponent.Jump(amount) end

    --- 持续朝某方向转动。
    ---
    ---@param value Vector
    function CharacterComponent.Turn(value) end

    --- 侧向倾斜，负值表示左，正值表示右。
    ---
    ---@param value number
    function CharacterComponent.Lean(value) end

    --- 对角色应用摇晃。horizontal、vertical：方向上的移动量；
    --- frequency：移动速度；decay：减慢速度。
    ---
    ---@param horizontal number
    ---@param vertical? number
    ---@param frequency? number
    ---@param decay? number
    function CharacterComponent.Shake(
        horizontal,
        vertical,
        frequency,
        decay
    ) end

    --- 添加跟踪混合状态的动画。简单动画混合将对
    --- 除当前活动的动画外的每个动画执行混合退出。
    ---
    ---@param entity Entity
    function CharacterComponent.AddAnimation(entity) end

    --- 播放动画。这将作为主动画混合进来，其他将
    --- 混合退出。
    ---
    ---@param entity Entity
    function CharacterComponent.PlayAnimation(entity) end

    --- 停止当前动画。
    function CharacterComponent.StopAnimation() end

    --- 设置当前动画的目标混合量。
    ---
    ---@param value number
    function CharacterComponent.SetAnimationAmount(value) end

    --- 返回当前动画的目标混合量。
    ---
    ---@return number
    function CharacterComponent.GetAnimationAmount() end

    --- 返回当前动画的计时器。
    ---
    ---@return number
    function CharacterComponent.GetAnimationTimer() end

    --- 如果当前动画已结束则返回 true，否则返回 false。
    ---
    ---@return boolean
    function CharacterComponent.IsAnimationEnded() end

    --- 在地面上移动时的速度乘数，默认：0.92。
    ---
    ---@param value number
    function CharacterComponent.SetGroundFriction(value) end

    --- 在水中游泳时的速度乘数，默认：0.9。
    ---
    ---@param value number
    function CharacterComponent.SetWaterFriction(value) end

    --- 坡度检测阈值，默认：0.2。
    ---
    ---@param value number
    function CharacterComponent.SetSlopeThreshold(value) end

    --- 倾斜最小/最大钳制，默认：0.12。
    ---
    ---@param value number
    function CharacterComponent.SetLeaningLimit(value) end

    --- 使用 Turn() 时的转动平滑速度，默认：10.0。
    ---
    ---@param value number
    function CharacterComponent.SetTurningSpeed(value) end

    --- 模拟帧率，默认：120。
    ---
    ---@param value number
    function CharacterComponent.SetFixedUpdateFPS(value) end

    --- 重力值，默认：-30。
    ---
    ---@param value number
    function CharacterComponent.SetGravity(value) end

    --- 从水面保持的垂直偏移。如果角色在游泳状态下
    --- 没入太深则有用。
    ---
    ---@param value number
    function CharacterComponent.SetWaterVerticalOffset(value) end

    --- 设置角色生命值。
    ---
    ---@param value integer
    function CharacterComponent.SetHealth(value) end

    --- 设置角色胶囊的水平大小（同胶囊半径）。
    ---
    ---@param value number
    function CharacterComponent.SetWidth(value) end

    --- 设置角色胶囊的垂直大小（同胶囊高度）。
    ---
    ---@param value number
    function CharacterComponent.SetHeight(value) end

    --- 对角色应用整体缩放。
    ---
    ---@param value number
    function CharacterComponent.SetScale(value) end

    --- 立即设置当前位置（传送）。
    ---
    ---@param value Vector
    function CharacterComponent.SetPosition(value) end

    --- 立即设置当前速度。
    ---
    ---@param value Vector
    function CharacterComponent.SetVelocity(value) end

    --- 设置角色的朝向方向。
    ---
    ---@param value Vector
    function CharacterComponent.SetFacing(value) end

    --- 应用相对偏移（相对于朝向方向）。
    ---
    ---@param value Vector
    function CharacterComponent.SetRelativeOffset(value) end

    --- 启用/禁用使用反向运动学的脚部放置。
    ---
    ---@param value boolean
    function CharacterComponent.SetFootPlacementEnabled(value) end

    --- 设置此角色与其他角色的碰撞是否禁用
    --- （默认：false）。
    ---
    ---@param value boolean
    function CharacterComponent.SetCharacterToCharacterCollisionDisabled(
        value
    ) end

    --- 将角色位置锁定到 2D 平面（XY 平移，旋转
    --- 已解锁但只能侧向移动）。
    ---
    ---@param value boolean
    function CharacterComponent.SetLocked2D(value) end

    --- 如果位置锁定到 2D 平面则返回 true。
    ---
    ---@return boolean
    function CharacterComponent.IsLocked2D() end

    --- 获取当前生命值。
    ---
    ---@return integer
    function CharacterComponent.GetHealth() end

    --- 获取角色胶囊的水平大小（同胶囊半径）。
    ---
    ---@return number
    function CharacterComponent.GetWidth() end

    --- 获取角色胶囊的垂直大小（同胶囊高度）。
    ---
    ---@return number
    function CharacterComponent.GetHeight() end

    --- 获取角色的整体缩放。
    ---
    ---@return number
    function CharacterComponent.GetScale() end

    --- 检索不带插值的当前位置（这是固定时间步更新的
    --- 原始值）。
    ---
    ---@return Vector
    function CharacterComponent.GetPosition() end

    --- 检索带插值的当前位置（这是渲染的
    --- 位置）。
    ---
    ---@return Vector
    function CharacterComponent.GetPositionInterpolated() end

    --- 获取当前速度。
    ---
    ---@return Vector
    function CharacterComponent.GetVelocity() end

    --- 获取当前移动方向。
    ---
    ---@return Vector
    function CharacterComponent.GetMovement() end

    --- 返回角色当前是否站在地面上。
    ---
    ---@return boolean
    function CharacterComponent.IsGrounded() end

    --- 返回角色当前是否与墙壁相交。
    ---
    ---@return boolean
    function CharacterComponent.IsWallIntersect() end

    --- 返回角色当前是否在游泳。
    ---
    ---@return boolean
    function CharacterComponent.IsSwimming() end

    --- 返回是否当前启用使用反向运动学的脚部放置。
    ---
    ---@return boolean
    function CharacterComponent.IsFootPlacementEnabled() end

    --- 返回此角色与其他角色的碰撞是否禁用
    --- （默认：false）。
    function CharacterComponent.IsCharacterToCharacterCollisionDisabled() end

    --- 返回表示角色的胶囊体。
    ---
    ---@return Capsule
    function CharacterComponent.GetCapsule() end

    --- 返回角色的即时朝向。
    ---
    ---@return Vector
    function CharacterComponent.GetFacing() end

    --- 返回角色的平滑朝向。
    ---
    ---@return Vector
    function CharacterComponent.GetFacingSmoothed() end

    --- 返回相对偏移（相对于朝向方向）。
    ---
    ---@return Vector
    function CharacterComponent.GetRelativeOffset() end

    --- 返回即时倾斜量。
    ---
    ---@return number
    function CharacterComponent.GetLeaning() end

    --- 返回平滑倾斜量。
    ---
    ---@return number
    function CharacterComponent.GetLeaningSmoothed() end

    --- 返回考虑角色在脚部放置后位置的垂直偏移。
    ---
    ---@return number
    function CharacterComponent.GetFootOffset() end

    --- 设置寻路目标，将在下次场景更新时处理。你可以通过
    --- 使用 GetPathQuery() 访问角色的 pathquery 对象获取结果。
    ---
    ---@param goal Vector
    ---@param voxelgrid VoxelGrid
    function CharacterComponent.SetPathGoal(goal, voxelgrid) end

    --- 返回此角色的 PathQuery 对象。
    ---
    ---@return PathQuery
    function CharacterComponent.GetPathQuery() end

    --- 设置是否使用专用阴影。
    ---
    ---@param value boolean
    function CharacterComponent.SetDedicatedShadow(value) end

    --- 返回是否使用专用阴影。
    ---
    ---@return boolean
    function CharacterComponent.IsDedicatedShadow() end
```

### Canvas

```lua
    --- 创建 Canvas 对象。实际上你从应用程序获取活动画布
    --- （例如 `application:GetCanvas()`），而不是构造一个。
    ---
    ---@return Canvas
    function Canvas() end

    --- 描述可绘制区域。
    ---
    ---@class Canvas
    local Canvas = {}

    --- 获取画布每英寸像素数 (DPI)。
    ---
    ---@return number
    function Canvas.GetDPI() end

    --- 物理和逻辑大小之间的缩放因子。
    ---
    ---@return number
    function Canvas.GetDPIScaling() end

    --- DPI 缩放之上的自定义缩放因子。
    ---
    ---@return number
    function Canvas.GetCustomScaling() end

    --- 设置在 DPI 缩放之上应用的自定义缩放因子。
    ---
    ---@param value number
    function Canvas.SetCustomScaling(value) end

    --- 获取画布宽度，以像素为单位。
    ---
    ---@return integer
    function Canvas.GetPhysicalWidth() end

    --- 获取画布高度，以像素为单位。
    ---
    ---@return integer
    function Canvas.GetPhysicalHeight() end

    --- 获取画布宽度，以 DPI 缩放单位为单位。
    ---
    ---@return number
    function Canvas.GetLogicalWidth() end

    --- 获取画布高度，以 DPI 缩放单位为单位。
    ---
    ---@return number
    function Canvas.GetLogicalHeight() end
```

### 高层接口

**此部分只能从独立 lua 脚本中使用，不能从 ScriptComponent 中使用。**这是因为 ScriptComponent 始终在 scene.Update() 内运行，此时无法安全地切换路径。另一方面，独立 lua 脚本可以定义自己的更新逻辑和渲染路径并更改应用程序行为。

#### Application

```lua
    --- 切换渲染路径时使用的淡入淡出过渡样式（参见
    --- Application.SetActivePath 和 Application.Fade）。
    ---
    ---@enum FadeType
    FadeType = {
        FadeToColor = 0,
        CrossFade = 1,
    }
```

```lua
    --- 创建 Application 对象。实际上你使用全局
    --- `application` 而不是构造一个。
    ---
    ---@return Application
    function Application() end

    --- 这是主入口点，管理应用程序的
    --- 生命周期。
    ---
    ---@class Application
    local Application = {}

    --- 应用程序。
    ---
    ---@type Application
    application = nil

    --- 主程序。
    ---
    ---@deprecated
    ---
    ---@type Application
    main = nil

    --- 返回活动渲染路径。具体类型取决于当前活动的
    --- （3D 路径、加载屏幕等）。
    ---
    ---@return RenderPath3D|LoadingScreen|RenderPath2D|RenderPath|nil
    function Application.GetActivePath() end

    --- 设置活动渲染路径。
    ---
    ---@param path RenderPath
    ---@param fadeSeconds? number
    ---@param fadeColorR? integer
    ---@param fadeColorG? integer
    ---@param fadeColorB? integer
    ---@param fadetype? FadeType
    function Application.SetActivePath(
        path,
        fadeSeconds,
        fadeColorR,
        fadeColorG,
        fadeColorB,
        fadetype
    ) end

    --- 启用/禁用固定更新中的帧跳过。
    ---
    ---@param enabled boolean
    function Application.SetFrameSkip(enabled) end

    --- 切换到全屏/窗口化。
    ---
    ---@param value boolean
    function Application.SetFullScreen(value) end

    --- 设置固定更新和帧率锁定时可变速率更新的目标
    --- 帧率。
    ---
    ---@param fps number
    function Application.SetTargetFrameRate(fps) end

    --- 如果启用，可变速率更新将使用固定增量时间。
    ---
    ---@param enabled boolean
    function Application.SetFrameRateLock(enabled) end

    --- 如果启用，信息显示将显示在应用程序的左上角。
    ---
    ---@param active boolean
    function Application.SetInfoDisplay(active) end

    --- 如果启用了信息显示，切换引擎水印、版本号等
    --- 的显示。
    ---
    ---@param active boolean
    function Application.SetWatermarkDisplay(active) end

    --- 如果启用了信息显示，切换帧率显示。
    ---
    ---@param active boolean
    function Application.SetFPSDisplay(active) end

    --- 如果启用了信息显示，切换分辨率显示。
    ---
    ---@param active boolean
    function Application.SetResolutionDisplay(active) end

    --- 如果启用了信息显示，切换画布逻辑大小显示。
    ---
    ---@param active boolean
    function Application.SetLogicalSizeDisplay(active) end

    --- 如果启用了信息显示，切换输出色彩空间显示。
    ---
    ---@param active boolean
    function Application.SetColorSpaceDisplay(active) end

    --- 如果启用了信息显示，切换活动图形管线计数显示。
    ---
    ---@param active boolean
    function Application.SetPipelineCountDisplay(active) end

    --- 如果启用了信息显示，切换堆分配统计显示。
    ---
    ---@param active boolean
    function Application.SetHeapAllocationCountDisplay(active) end

    --- 如果启用了信息显示，切换显存使用显示。
    ---
    ---@param active boolean
    function Application.SetVRAMUsageDisplay(active) end

    --- 在左上角切换颜色分级辅助器显示。
    ---
    ---@param value boolean
    function Application.SetColorGradingHelper(value) end

    --- 返回当前显示器是否支持 HDR 显示输出。
    ---
    ---@return boolean
    function Application.IsHDRSupported() end

    --- 设置 HDR 显示模式（如果显示器支持）。
    ---
    ---@param bool boolean
    function Application.SetHDR(bool) end

    --- 返回应用程序当前画布的副本。
    ---
    ---@return Canvas
    function Application.GetCanvas() end

    --- 将指定画布应用到应用程序。
    ---
    ---@param canvas Canvas
    function Application.SetCanvas(canvas) end

    --- 关闭程序。
    function Application.Exit() end

    --- 淡出完成时返回 true（淡出可在用 SetActivePath() 切换路径时
    --- 设置）。
    function Application.IsFaded() end

    --- 在 fadeSeconds 时间内开始到给定 RGB 颜色（每个通道 0-255）
    --- 的淡入淡出过渡，使用给定的 FadeType。
    ---
    ---@param fadeSeconds number
    ---@param fadeColorR? integer
    ---@param fadeColorG integer
    ---@param fadeColorB integer
    ---@param fadetype FadeType
    function Application.Fade(
        fadeSeconds,
        fadeColorR,
        fadeColorG,
        fadeColorB,
        fadetype
    ) end

    --- 在给定秒数内开始交叉淡入淡出过渡，
    --- 从前一帧混合。
    ---
    ---@param fadeSeconds number
    function Application.CrossFade(fadeSeconds) end

    --- 启用/禁用屏幕上的性能分析器。
    ---
    ---@param enabled boolean
    function SetProfilerEnabled(enabled) end

    --- 切换屏幕上的性能分析器（此函数为方便更快编写
    --- 而制作）。
    function prof() end

    --- 关闭应用程序。
    function exit() end
```

#### RenderPath

```lua
    --- 创建基础 RenderPath。RenderPath 表示应用程序的高层部分
    --- （菜单、加载屏幕、游戏屏幕等）。
    ---
    ---@return RenderPath
    function RenderPath() end

    --- RenderPath 是表示整个应用程序一部分的高层系统。它负责
    --- 处理高层渲染和逻辑流程。渲染路径例如可以是加载屏幕、
    --- 菜单屏幕或主游戏屏幕等。
    ---
    ---@class RenderPath
    local RenderPath = {}

    --- 返回层掩码。
    ---
    ---@return integer
    function RenderPath.GetLayerMask() end

    --- 设置层掩码。
    ---
    ---@param mask integer
    function RenderPath.SetLayerMask(mask) end
```

##### RenderPath2D : RenderPath

```lua
    --- 创建用于绘制精灵和字体的 2D 渲染路径。
    ---
    ---@return RenderPath2D
    function RenderPath2D() end

    --- 持有 Sprites 和 SpriteFonts 的 2D 渲染路径，按层排序，
    --- 并更新和渲染它们。
    ---
    ---@class RenderPath2D : RenderPath
    local RenderPath2D = {}

    --- 添加精灵。
    ---
    ---@param sprite Sprite
    ---@param layer? string
    function RenderPath2D.AddSprite(sprite, layer) end

    --- 添加视频精灵。
    ---
    ---@param videoinstance VideoInstance
    ---@param sprite Sprite
    ---@param layer? string
    function RenderPath2D.AddVideoSprite(videoinstance, sprite, layer) end

    --- 添加字体。
    ---
    ---@param font SpriteFont
    ---@param layer? string
    function RenderPath2D.AddFont(font, layer) end

    --- 移除字体。
    ---
    ---@param font SpriteFont
    function RenderPath2D.RemoveFont(font) end

    --- 清除精灵。
    function RenderPath2D.ClearSprites() end

    --- 清除字体。
    function RenderPath2D.ClearFonts() end

    --- 返回精灵顺序。
    ---
    ---@param sprite Sprite
    ---
    ---@return integer?
    function RenderPath2D.GetSpriteOrder(sprite) end

    --- 返回字体顺序。
    ---
    ---@param font SpriteFont
    ---
    ---@return integer?
    function RenderPath2D.GetFontOrder(font) end

    --- 添加层。
    ---
    ---@param name string
    function RenderPath2D.AddLayer(name) end

    --- 返回层。
    ---
    ---@return any
    function RenderPath2D.GetLayers() end

    --- 设置层顺序。
    ---
    ---@param name string
    ---@param order integer
    function RenderPath2D.SetLayerOrder(name, order) end

    --- 设置精灵顺序。
    ---
    ---@param sprite Sprite
    ---@param order integer
    function RenderPath2D.SetSpriteOrder(sprite, order) end

    --- 设置字体顺序。
    ---
    ---@param font SpriteFont
    ---@param order integer
    function RenderPath2D.SetFontOrder(font, order) end

    --- 返回用于 SDR 到 HDR 线性输出映射转换的 HDR 缩放值
    --- （默认：9.0）。
    ---
    ---@return number
    function RenderPath2D.GetHDRScaling() end

    --- 设置用于 SDR 到 HDR 线性输出映射转换的 HDR 缩放值
    --- （默认：9.0）。
    ---
    ---@param value number
    function RenderPath2D.SetHDRScaling(value) end

    --- 从其他渲染路径复制所有内容到此。
    ---
    ---@param other RenderPath
    function RenderPath2D.CopyFrom(other) end

    --- 从渲染路径移除精灵（如果未给定则移除所有精灵）。
    ---
    ---@param sprite? Sprite
    function RenderPath2D.RemoveSprite(sprite) end
```

##### RenderPath3D : RenderPath2D

```lua
    --- 创建 3D 场景渲染路径。它继承 2D 功能，因此也可
    --- 以绘制 2D 叠加层。
    ---
    ---@return RenderPath3D
    function RenderPath3D() end

    --- 默认场景渲染路径。
    --- 它从 RenderPath2D 继承函数，因此可以渲染 2D 叠加层。
    ---
    ---@class RenderPath3D : RenderPath2D
    local RenderPath3D = {}

    --- 缩放内部渲染分辨率。当 GPU 渲染速度是瓶颈时，这可以
    --- 提供重大性能改进。
    ---
    ---@param value number
    function RenderPath3D.SetResolutionScale(value) end

    --- 设置环境光遮蔽效果（可能的值见下）。
    ---
    ---@param value integer
    function RenderPath3D.SetAO(value) end

    --- 关闭 AO 计算（在 SetAO() 函数中使用）。
    ---
    ---@type integer
    AO_DISABLED = 0

    --- 启用简单暴力屏幕空间环境光遮蔽（在 SetAO() 函数中使用）。
    ---
    ---@type integer
    AO_SSAO = 1

    --- 启用基于地平线的屏幕空间环境光遮蔽（在 SetAO() 函数中
    --- 使用）。
    ---
    ---@type integer
    AO_HBAO = 2

    --- 启用多尺度屏幕空间环境光遮蔽（在 SetAO() 函数中使用）。
    ---
    ---@type integer
    AO_MSAO = 3

    --- 在 SetAO() 中使用光线追踪环境光遮蔽（需要硬件光线
    --- 追踪）。
    ---
    ---@type integer
    AO_RTAO = 4

    --- 如果启用了任何 AO，则应用 AO 幂值。
    ---
    ---@param value number
    function RenderPath3D.SetAOPower(value) end

    --- 设置光线追踪 AO 的最大范围。
    ---
    ---@param value number
    function RenderPath3D.SetAORange(value) end

    --- 启用或禁用屏幕空间反射 (SSR)。
    ---
    ---@param value boolean
    function RenderPath3D.SetSSREnabled(value) end

    --- 启用或禁用屏幕空间全局光照 (SSGI)。
    ---
    ---@param value boolean
    function RenderPath3D.SetSSGIEnabled(value) end

    --- 启用或禁用光线追踪漫反射全局光照（需要硬件光线
    --- 追踪）。
    ---
    ---@param value boolean
    function RenderPath3D.SetRaytracedDiffuseEnabled(value) end

    --- 启用或禁用光线追踪反射（需要硬件光线追踪）。
    ---
    ---@param value boolean
    function RenderPath3D.SetRaytracedReflectionsEnabled(value) end

    --- 启用或禁用场景的阴影渲染。
    ---
    ---@param value boolean
    function RenderPath3D.SetShadowsEnabled(value) end

    --- 启用或禁用平面和环境反射。
    ---
    ---@param value boolean
    function RenderPath3D.SetReflectionsEnabled(value) end

    --- 控制平面反射渲染分辨率和多重采样抗锯齿。
    --- msaaSampleCount 必须是这些值之一：1, 2, 4, 8
    ---
    ---@param resolutionScale number
    ---@param msaaSampleCount integer
    function RenderPath3D.SetPlanarReflectionQuality(
        resolutionScale,
        msaaSampleCount
    ) end

    --- 启用或禁用 FXAA（快速近似抗锯齿）。
    ---
    ---@param value boolean
    function RenderPath3D.SetFXAAEnabled(value) end

    --- 启用或禁用泛光后处理效果。
    ---
    ---@param value boolean
    function RenderPath3D.SetBloomEnabled(value) end

    --- 设置泛光阈值。
    ---
    ---@param value number
    function RenderPath3D.SetBloomThreshold(value) end

    --- 启用或禁用颜色分级。
    ---
    ---@param value boolean
    function RenderPath3D.SetColorGradingEnabled(value) end

    --- 启用或禁用体积光。
    ---
    ---@param value boolean
    function RenderPath3D.SetVolumeLightsEnabled(value) end

    --- 启用或禁用光轴。
    ---
    ---@param value boolean
    function RenderPath3D.SetLightShaftsEnabled(value) end

    --- 启用或禁用镜头光晕。
    ---
    ---@param value boolean
    function RenderPath3D.SetLensFlareEnabled(value) end

    --- 启用或禁用运动模糊。
    ---
    ---@param value boolean
    function RenderPath3D.SetMotionBlurEnabled(value) end

    --- 设置运动模糊强度。
    ---
    ---@param value number
    function RenderPath3D.SetMotionBlurStrength(value) end

    --- 启用或禁用抖动。
    ---
    ---@param value boolean
    function RenderPath3D.SetDitherEnabled(value) end

    --- 启用或禁用景深。
    ---
    ---@param value boolean
    function RenderPath3D.SetDepthOfFieldEnabled(value) end

    --- 设置景深强度。
    ---
    ---@param value number
    function RenderPath3D.SetDepthOfFieldStrength(value) end

    --- 设置光轴强度。
    ---
    ---@param value number
    function RenderPath3D.SetLightShaftsStrength(value) end

    --- 设置 MSAA 采样计数。
    ---
    ---@param count integer
    function RenderPath3D.SetMSAASampleCount(count) end

    --- 启用或禁用 CRT 滤镜。
    ---
    ---@param value boolean
    function RenderPath3D.SetCRTFilterEnabled(value) end

    --- 启用或禁用锐化滤镜。
    ---
    ---@param value boolean
    function RenderPath3D.SetSharpenFilterEnabled(value) end

    --- 设置锐化滤镜量。
    ---
    ---@param value number
    function RenderPath3D.SetSharpenFilterAmount(value) end

    --- 启用或禁用眼睛适应。
    ---
    ---@param value boolean
    function RenderPath3D.SetEyeAdaptionEnabled(value) end

    --- 设置曝光。
    ---
    ---@param value number
    function RenderPath3D.SetExposure(value) end

    --- 设置 HDR 校准。
    ---
    ---@param value number
    function RenderPath3D.SetHDRCalibration(value) end

    --- 启用或禁用轮廓。
    ---
    ---@param value boolean
    function RenderPath3D.SetOutlineEnabled(value) end

    --- 设置轮廓阈值。
    ---
    ---@param value number
    function RenderPath3D.SetOutlineThreshold(value) end

    --- 设置轮廓粗细。
    ---
    ---@param value number
    function RenderPath3D.SetOutlineThickness(value) end

    --- 设置轮廓颜色。
    ---
    ---@param r number
    ---@param g number
    ---@param b number
    ---@param a number
    function RenderPath3D.SetOutlineColor(r, g, b, a) end

    --- FSR 1.0 开/关。
    ---
    ---@param value boolean
    function RenderPath3D.SetFSREnabled(value) end

    --- FSR 1.0 锐度 0：最锐利，2：最不锐利。
    ---
    ---@param value number
    function RenderPath3D.SetFSRSharpness(value) end

    --- FSR 2.1 开/关。
    ---
    ---@param value boolean
    function RenderPath3D.SetFSR2Enabled(value) end

    --- FSR 2.1 锐度 0：最不锐利，1：最锐利（这与 FSR 1.0
    --- 不同）。
    ---
    ---@param value number
    function RenderPath3D.SetFSR2Sharpness(value) end

    --- FSR 2.1 预设将修改分辨率缩放和采样器 LOD 偏移。
    ---
    ---@param value FSR2_Preset
    function RenderPath3D.SetFSR2Preset(value) end

    --- 设置色调映射类型。
    ---
    ---@param value Tonemap
    function RenderPath3D.SetTonemap(value) end

    --- 启用可见性渲染模式，这在计算着色器中渲染场景而不是
    --- 前向渲染。当屏幕上的三角形密度非常高时，这可以
    --- 提升性能。
    ---
    ---@param value boolean
    function RenderPath3D.SetVisibilityComputeShadingEnabled(value) end

    --- 设置从屏幕左侧裁剪，以逻辑单位为单位。
    ---
    ---@param value number
    function RenderPath3D.SetCropLeft(value) end

    --- 设置从屏幕顶部裁剪，以逻辑单位为单位。
    ---
    ---@param value number
    function RenderPath3D.SetCropTop(value) end

    --- 设置从屏幕右侧裁剪，以逻辑单位为单位。
    ---
    ---@param value number
    function RenderPath3D.SetCropRight(value) end

    --- 设置从屏幕底部裁剪，以逻辑单位为单位。
    ---
    ---@param value number
    function RenderPath3D.SetCropBottom(value) end

    --- 返回最后一个后处理渲染纹理。
    ---
    ---@return Texture
    function RenderPath3D.GetLastPostProcessRT() end

    --- 将法线贴图纹理设置为全屏扭曲遮罩。
    ---
    ---@param texture Texture
    function RenderPath3D.SetDistortionOverlay(texture) end

    --- 启用或禁用色差。
    ---
    ---@param value boolean
    function RenderPath3D.SetChromaticAberrationEnabled(value) end

    --- 设置色差量。
    ---
    ---@param value number
    function RenderPath3D.SetChromaticAberrationAmount(value) end

    --- 设置眼睛适应速率。
    ---
    ---@param value number
    function RenderPath3D.SetEyeAdaptionRate(value) end

    --- 设置眼睛适应键。
    ---
    ---@param value number
    function RenderPath3D.SetEyeAdaptionKey(value) end

    --- 设置对比度。
    ---
    ---@param value number
    function RenderPath3D.SetContrast(value) end

    --- 设置饱和度。
    ---
    ---@param value number
    function RenderPath3D.SetSaturation(value) end

    --- 设置亮度。
    ---
    ---@param value number
    function RenderPath3D.SetBrightness(value) end

    --- 设置光轴淡出速度。
    ---
    ---@param value number
    function RenderPath3D.SetLightShaftsFadeSpeed(value) end

    --- 启用或禁用网格混合。
    ---
    ---@param value boolean
    function RenderPath3D.SetMeshBlendEnabled(value) end

    --- 启用或禁用遮挡剔除。
    ---
    ---@param value boolean
    function RenderPath3D.SetOcclusionCullingEnabled(value) end

    --- 设置 SSGI 深度拒绝。
    ---
    ---@param value number
    function RenderPath3D.SetSSGIDepthRejection(value) end

    --- AMD FidelityFX Super Resolution 2 (FSR2) 时间
    --- 升级的质量预设。
    ---
    ---@enum FSR2_Preset
    FSR2_Preset = {
        Quality = 0, -- 1.5x 缩放，-1.58 采样器 LOD 偏移
        Balanced = 1, -- 1.7x 缩放，-1.76 采样器 LOD 偏移
        Performance = 2, -- 2.0x 缩放，-2.0 采样器 LOD 偏移
        Ultra_Performance = 3, -- 3.0x 缩放，-2.58 采样器 LOD 偏移
        Reinhard = 0,
        ACES = 1,
    }

    --- 用于 HDR 到 LDR 转换的色调映射算子。
    ---
    ---@enum Tonemap
    Tonemap = {
        Reinhard = 0,
        ACES = 1,
    }
```

##### LoadingScreen : RenderPath2D

```lua
    --- 创建在后台加载资源并可显示加载进度的 LoadingScreen
    --- 渲染路径。
    ---
    ---@return LoadingScreen
    function LoadingScreen() end

    --- 一个 RenderPath2D，但内部管理资源加载并可
    --- 显示有关过程的信息。它从 RenderPath2D 继承函数。
    ---
    ---@class LoadingScreen : RenderPath2D
    local LoadingScreen = {}

    --- 将场景加载任务添加到全局场景并立即返回根
    --- 实体句柄。加载任务将在 Application 激活 LoadingScreen 时
    --- 异步启动。
    ---
    ---@param fileName string
    ---@param matrix? Matrix
    ---
    ---@return integer
    function LoadingScreen.AddLoadModelTask(fileName, matrix) end

    --- 将场景加载任务添加到指定场景并立即返回根
    --- 实体句柄。加载任务将在 Application 激活 LoadingScreen 时
    --- 异步启动。
    ---
    ---@param scene Scene
    ---@param fileName string
    ---@param matrix? Matrix
    ---
    ---@return integer
    function LoadingScreen.AddLoadModelTask(scene, fileName, matrix) end

    --- 加载 RenderPath 的资源并在所有加载任务完成后
    --- 激活它。
    ---
    ---@param path RenderPath
    ---@param app Application
    ---@param fadeSeconds? number
    ---@param fadeR? integer
    ---@param fadeG? integer
    ---@param fadeB? integer
    ---@param fadetype? FadeType
    function LoadingScreen.AddRenderPathActivationTask(
        path,
        app,
        fadeSeconds,
        fadeR,
        fadeG,
        fadeB,
        fadetype
    ) end

    --- 当所有加载任务完成且加载屏幕停止时返回 true（例如
    --- 应用程序将其换出）。
    ---
    ---@return boolean
    function LoadingScreen.IsFinished() end

    --- 返回加载完成百分比（0% - 100%）。当所有加载
    --- 任务完成或没有任务时，返回 100。
    ---
    ---@return integer
    function LoadingScreen.GetProgress() end

    --- 设置在加载屏幕活动时显示的全屏背景纹理。
    ---
    ---@param tex Texture
    function LoadingScreen.SetBackgroundTexture(tex) end

    --- 返回背景纹理。
    ---
    ---@return Texture
    function LoadingScreen.GetBackgroundTexture() end

    --- 设置背景图像的对齐方式。
    ---
    ---@param mode BackgroundMode
    function LoadingScreen.SetBackgroundMode(mode) end

    --- 返回背景模式。
    ---
    ---@return integer
    function LoadingScreen.GetBackgroundMode() end

    --- 控制全屏背景图像如何适配屏幕。
    ---
    ---@enum BackgroundMode
    BackgroundMode = {
        -- 填充整个屏幕，如果纵横比不匹配将裁剪图像部分
        Fill = 0,
        -- 将图像完全放入屏幕内，如果纵横比不匹配将在屏幕上
        -- 产生黑边
        Fit = 1,
        Stretch = 2, -- 填充整个屏幕，并根据需要拉伸图像
    }
```

### Primitives

#### Ray

```lua
    --- 从原点和方向创建射线，可选带沿射线的最小和
    --- 最大距离。
    ---
    ---@param origin Vector
    ---@param direction Vector
    ---@param Tmin? number
    ---@param tmax? number
    ---
    ---@return Ray
    function Ray(origin, direction, Tmin, tmax) end

    --- 由原点 Vector 和归一化方向 Vector 定义的射线。它
    --- 可用于与其他图元或场景相交。
    ---
    ---@class Ray
    ---
    ---@field Origin Vector
    ---@field Direction Vector
    local Ray = {}

    --- 返回射线是否与给定 AABB 相交。
    ---
    ---@param aabb AABB
    ---
    ---@return boolean
    function Ray.Intersects(aabb) end

    --- 返回射线是否与给定球体相交。
    ---
    ---@param sphere Sphere
    ---
    ---@return boolean
    function Ray.Intersects(sphere) end

    --- 返回射线是否与给定胶囊体相交。
    ---
    ---@param capsule Capsule
    ---
    ---@return boolean
    function Ray.Intersects(capsule) end

    --- 返回射线与给定平面相交的点。
    ---
    ---@param plane Vector
    ---
    ---@return Vector point
    function Ray.Intersects(plane) end

    --- 返回原点。
    ---
    ---@return Vector
    function Ray.GetOrigin() end

    --- 返回方向。
    ---
    ---@return Vector
    function Ray.GetDirection() end

    --- 设置原点。
    ---
    ---@param vector Vector
    function Ray.SetOrigin(vector) end

    --- 设置方向。
    ---
    ---@param vector Vector
    function Ray.SetDirection(vector) end

    --- 从两点创建射线。点 a 将是射线原点，指向
    --- 点 b。
    ---
    ---@param a Vector
    ---@param b Vector
    function Ray.CreateFromPoints(a, b) end

    --- 在相交结果处计算放置方向矩阵。此矩阵
    --- 可用于在场景中放置面向表面的实体。
    ---
    ---@param position Vector
    ---@param normal Vector
    ---
    ---@return Matrix
    function Ray.GetPlacementOrientation(position, normal) end
```

#### AABB

```lua
    --- 如果未给定参数，它将是无限反向的，无法
    --- 相交。
    ---
    ---@param min? Vector
    ---@param max Vector
    ---
    ---@return AABB
    function AABB(min, max) end

    --- 轴对齐边界框。可与其他图元相交。
    ---
    ---@class AABB
    ---
    ---@field Min Vector
    ---@field Max Vector
    local AABB = {}


    --- 省略 z 分量进行相交检查以获得更精确的 2D
    --- 相交。
    ---
    ---@param aabb AABB
    ---
    ---@return boolean
    function AABB.Intersects2D(aabb) end

    --- 返回此 AABB 是否与给定 AABB 相交。
    ---
    ---@param aabb AABB
    ---
    ---@return boolean
    function AABB.Intersects(aabb) end

    --- 返回此 AABB 是否与给定球体相交。
    ---
    ---@param sphere Sphere
    ---
    ---@return boolean
    function AABB.Intersects(sphere) end

    --- 返回此 AABB 是否与给定射线相交。
    ---
    ---@param ray Ray
    ---
    ---@return boolean
    function AABB.Intersects(ray) end

    --- 返回给定点是否在此 AABB 内。
    ---
    ---@param point Vector
    ---
    ---@return boolean
    function AABB.Intersects(point) end

    --- 返回框的最小角。
    ---
    ---@return Vector
    function AABB.GetMin() end

    --- 返回框的最大角。
    ---
    ---@return Vector
    function AABB.GetMax() end

    --- 设置框的最小角。
    ---
    ---@param vector Vector
    function AABB.SetMin(vector) end

    --- 设置框的最大角。
    ---
    ---@param vector Vector
    function AABB.SetMax(vector) end

    --- 返回框的中心点。
    ---
    ---@return Vector
    function AABB.GetCenter() end

    --- 返回框的半范围（沿每个轴大小的一半）。
    ---
    ---@return Vector
    function AABB.GetHalfExtents() end

    --- 用矩阵变换 AABB 并返回结果的保守
    --- AABB。
    ---
    ---@param matrix Matrix
    ---
    ---@return AABB
    function AABB.Transform(matrix) end

    --- 获取将 AABB 表示为 OBB（定向边界框）的矩阵。
    ---
    ---@return Matrix
    function AABB.GetAsBoxMatrix() end

    --- 将 AABB 投影到屏幕，返回 UV 空间中的 2D 矩形作为
    --- Vector(topleftX, topleftY, bottomrightX, bottomrightY)，每个值在
    --- [0, 1] 范围内。
    ---
    ---@param ViewProjection Matrix
    ---
    ---@return Vector
    function AABB.ProjectToScreen(ViewProjection) end
```

#### Sphere

```lua
    --- 从中心点和半径创建球体。
    ---
    ---@param center Vector
    ---@param radius number
    ---
    ---@return Sphere
    function Sphere(center, radius) end

    --- 由中心 Vector 和半径定义的球体。可与其他
    --- 图元相交。
    ---
    ---@class Sphere
    ---
    ---@field Center Vector
    ---@field Radius number
    local Sphere = {}

    --- 返回此球体是否与给定 AABB 相交。
    ---
    ---@param aabb AABB
    ---
    ---@return boolean
    function Sphere.Intersects(aabb) end

    --- 返回此球体是否与给定球体相交。
    ---
    ---@param sphere Sphere
    ---
    ---@return boolean
    function Sphere.Intersects(sphere) end

    --- 返回此球体是否与给定胶囊体相交。
    ---
    ---@param capsule Capsule
    ---
    ---@return boolean
    function Sphere.Intersects(capsule) end

    --- 返回此球体是否与给定射线相交。
    ---
    ---@param ray Ray
    ---
    ---@return boolean
    function Sphere.Intersects(ray) end

    --- 返回给定点是否在此球体内。
    ---
    ---@param point Vector
    ---
    ---@return boolean
    function Sphere.Intersects(point) end

    --- 返回球体的中心。
    ---
    ---@return Vector
    function Sphere.GetCenter() end

    --- 返回球体的半径。
    ---
    ---@return number
    function Sphere.GetRadius() end

    --- 设置球体的中心。
    ---
    ---@param value Vector
    function Sphere.SetCenter(value) end

    --- 设置球体的半径。
    ---
    ---@param value number
    function Sphere.SetRadius(value) end

    --- 在相交结果处计算放置方向矩阵。此矩阵
    --- 可用于在场景中放置面向表面的实体。
    ---
    ---@param position Vector
    ---@param normal Vector
    ---
    ---@return Matrix
    function Sphere.GetPlacementOrientation(position, normal) end
```

#### Capsule

```lua
    --- 从基点、顶点和半径创建胶囊体。
    ---
    ---@param base Vector
    ---@param tip Vector
    ---@param radius number
    ---
    ---@return Capsule
    function Capsule(base, tip, radius) end

    --- 它就像两个由圆柱体连接的球体。Base 和 Tip 是两个端点，
    --- radius 是圆柱体的半径。
    ---
    ---@class Capsule
    ---
    ---@field Base Vector
    ---@field Tip Vector
    ---@field Radius number
    local Capsule = {}

    --- 返回此胶囊体是否与给定胶囊体相交。
    ---
    ---@param other Capsule
    ---
    ---@return boolean intersects
    ---@return Vector position
    ---@return Vector normal
    ---@return number depth
    function Capsule.Intersects(other) end

    --- 返回此胶囊体是否与给定球体相交。
    ---
    ---@param sphere Sphere
    ---
    ---@return boolean intersects
    ---@return number depth
    ---@return Vector normal
    function Capsule.Intersects(sphere) end

    --- 返回此胶囊体是否与给定射线相交。
    ---
    ---@param ray Ray
    ---
    ---@return boolean
    function Capsule.Intersects(ray) end

    --- 返回给定点是否在此胶囊体内。
    ---
    ---@param point Vector
    ---
    ---@return boolean
    function Capsule.Intersects(point) end

    --- 返回胶囊体的基点。
    ---
    ---@return Vector
    function Capsule.GetBase() end

    --- 返回胶囊体的顶点。
    ---
    ---@return Vector
    function Capsule.GetTip() end

    --- 返回胶囊体的半径。
    ---
    ---@return number
    function Capsule.GetRadius() end

    --- 设置胶囊体的基点。
    ---
    ---@param value Vector
    function Capsule.SetBase(value) end

    --- 设置胶囊体的顶点。
    ---
    ---@param value Vector
    function Capsule.SetTip(value) end

    --- 设置胶囊体的半径。
    ---
    ---@param value number
    function Capsule.SetRadius(value) end

    --- 在相交结果处计算放置方向矩阵。此矩阵
    --- 可用于在场景中放置面向表面的实体。
    ---
    ---@param position Vector
    ---@param normal Vector
    ---
    ---@return Matrix
    function Capsule.GetPlacementOrientation(position, normal) end

    --- 返回胶囊体的轴对齐边界框。
    ---
    ---@return AABB
    function Capsule.GetAABB() end
```

### Input

```lua
    --- 创建 Input 对象。使用全局 `input` 而不是构造一个。
    ---
    ---@return Input
    function Input() end

    --- 提供对键盘、鼠标、触摸和游戏手柄输入的访问。使用
    --- 全局 `input` 对象。
    ---
    ---@class Input
    local Input = {}

    --- 使用此全局对象访问输入函数。
    ---
    ---@type Input
    input = nil

    --- 检查按钮当前是否被按住。
    ---
    ---@param code integer
    ---@param playerindex? integer
    ---
    ---@return boolean
    function Input.Down(code, playerindex) end

    --- 检查按钮是否刚被按下（之前未按下）。
    ---
    ---@param code integer
    ---@param playerindex? integer
    ---
    ---@return boolean
    function Input.Press(code, playerindex) end

    --- 检查按钮是否刚被释放（之前被按下）。
    ---
    ---@param code integer
    ---@param playerindex? integer
    ---
    ---@return boolean
    function Input.Release(code, playerindex) end

    --- 检查按钮是否被按住特定持续时间
    --- （帧数）。如果 continuous == true，则在达到持续时间后
    --- 也将返回 true。
    ---
    ---@param code integer
    ---@param duration? integer
    ---@param continuous? boolean
    ---@param playerindex? integer
    ---
    ---@return boolean
    function Input.Hold(code, duration, continuous, playerindex) end

    --- 获取鼠标指针或主触摸位置 (x, y)。还返回鼠标
    --- 滚轮增量移动 (z) 和笔压 (w)。
    ---
    ---@return Vector
    function Input.GetPointer() end

    --- 设置鼠标位置。
    ---
    ---@param pos Vector
    function Input.SetPointer(pos) end

    --- 原生鼠标增量移动。
    ---
    ---@return Vector
    function Input.GetPointerDelta() end

    --- 隐藏指针。
    ---
    ---@param visible boolean
    function Input.HidePointer(visible) end

    --- 从游戏手柄读取模拟数据。type 参数必须来自
    --- GAMEPAD_ANALOG 值。
    ---
    ---@param type integer
    ---@param playerindex? integer
    ---
    ---@return Vector
    function Input.GetAnalog(type, playerindex) end

    --- 返回触摸。
    ---
    ---@return Touch
    function Input.GetTouches() end

    --- 设置控制器反馈，如振动或 LED 颜色。
    ---
    ---@param feedback ControllerFeedback
    ---@param playerindex? integer
    function Input.SetControllerFeedback(feedback, playerindex) end

    --- 如果没有按下任何键则返回 0 (`BUTTON_NONE`)，否则返回第一个
    --- 适当的按钮码。
    ---
    ---@param playerindex? integer
    ---
    ---@return integer
    function Input.WhatIsPressed(playerindex) end

    --- 返回该按钮码是否是游戏手柄按钮。
    ---
    ---@param button integer
    ---
    ---@return boolean
    function Input.IsGamepadButton(button) end

    --- 返回给定字符串名称的按钮码。
    ---
    ---@param str string
    ---
    ---@return integer
    function Input.StringToButton(str) end

    --- 返回给定按钮码的字符串名称。你可以设置
    --- 控制器类型偏好，它可以修改返回的字符串。
    ---
    ---@param button integer
    ---@param preference? integer
    ---
    ---@return any
    function Input.ButtonToString(button, preference) end

    --- 设置当前光标类型。值可以是光标值之一，参见
    --- 下文。
    ---
    ---@param cursor integer
    function Input.SetCursor(cursor) end

    --- 将指定光标类型设置为从光标文件加载的图像。
    ---
    ---@param cursor integer
    ---@param filename string
    function Input.SetCursorFromFile(cursor, filename) end

    --- 将指定光标重置为默认。
    ---
    ---@param cursor integer
    function Input.ResetCursor(cursor) end

    --- 将所有光标重置为默认。
    function Input.ResetCursors() end

    --- 返回当前触摸捏合手势的参数：捏合
    --- 中心位置、累积缩放和本帧的缩放变化。
    ---
    ---@return Vector position
    ---@return number scale
    ---@return number delta_scale
    function Input.GetTouchPinch() end

    --- 返回触摸平移手势增量移动。
    ---
    ---@return Vector
    function Input.GetTouchPan() end

    --- 如果平移触摸手势当前活动则返回 true。
    ---
    ---@return boolean
    function Input.IsTouchPanning() end

    --- 如果本帧开始新的平移触摸手势则返回 true。
    ---
    ---@return boolean
    function Input.IsTouchPanStarting() end
```

#### ControllerFeedback

```lua
    --- 控制器反馈。
    ---
    ---@return ControllerFeedback
    function ControllerFeedback() end

    --- 描述控制器反馈，如触摸和 LED 颜色，可在
    --- 控制器上回放。
    ---
    ---@class ControllerFeedback
    local ControllerFeedback = {}

    --- 左马达的振动量（0：无振动，1：最大振动）。
    ---
    ---@param value number
    function ControllerFeedback.SetVibrationLeft(value) end

    --- 右马达的振动量（0：无振动，1：最大振动）。
    ---
    ---@param value number
    function ControllerFeedback.SetVibrationRight(value) end

    --- 如果控制器有彩色 LED 则设置 LED 颜色。
    ---
    ---@param color Vector
    function ControllerFeedback.SetLEDColor(color) end

    --- 如果控制器有彩色 LED 则设置 LED 颜色（ABGR 十六进制颜色代码）。
    ---
    ---@param hexcolor integer
    function ControllerFeedback.SetLEDColor(hexcolor) end
```

#### Touch

```lua
    --- 创建 Touch 接触描述符。
    ---
    ---@return Touch
    function Touch() end

    --- 描述触摸接触点。
    ---
    ---@class Touch
    local Touch = {}

    --- 返回触摸状态（TOUCHSTATE_* 值之一）。
    ---
    ---@return integer
    function Touch.GetState() end

    --- 返回触摸位置。
    ---
    ---@return Vector
    function Touch.GetPos() end
```

#### TOUCHSTATE

```lua
    --- 触摸状态 PRESSED。
    ---
    ---@type integer
    TOUCHSTATE_PRESSED = 0

    --- 触摸状态 RELEASED。
    ---
    ---@type integer
    TOUCHSTATE_RELEASED = 1

    --- 触摸状态 MOVED。
    ---
    ---@type integer
    TOUCHSTATE_MOVED = 2
```

#### Keyboard Key codes

你还可以通过调用 string.byte(char uppercaseLetter) 生成键码，其中参数代表所需键盘键。

```lua
    --- 无按钮（"无输入"的哨兵值）。
    ---
    ---@type integer
    BUTTON_NONE = 0

    --- 键盘按钮 UP。
    ---
    ---@type integer
    KEYBOARD_BUTTON_UP = 518

    --- 键盘按钮 DOWN。
    ---
    ---@type integer
    KEYBOARD_BUTTON_DOWN = 519

    --- 键盘按钮 LEFT。
    ---
    ---@type integer
    KEYBOARD_BUTTON_LEFT = 520

    --- 键盘按钮 RIGHT。
    ---
    ---@type integer
    KEYBOARD_BUTTON_RIGHT = 521

    --- 键盘按钮 SPACE。
    ---
    ---@type integer
    KEYBOARD_BUTTON_SPACE = 522

    --- 键盘按钮 RSHIFT。
    ---
    ---@type integer
    KEYBOARD_BUTTON_RSHIFT = 523

    --- 键盘按钮 LSHIFT。
    ---
    ---@type integer
    KEYBOARD_BUTTON_LSHIFT = 524

    --- 键盘按钮 F1。
    ---
    ---@type integer
    KEYBOARD_BUTTON_F1 = 525

    --- 键盘按钮 F2。
    ---
    ---@type integer
    KEYBOARD_BUTTON_F2 = 526

    --- 键盘按钮 F3。
    ---
    ---@type integer
    KEYBOARD_BUTTON_F3 = 527

    --- 键盘按钮 F4。
    ---
    ---@type integer
    KEYBOARD_BUTTON_F4 = 528

    --- 键盘按钮 F5。
    ---
    ---@type integer
    KEYBOARD_BUTTON_F5 = 529

    --- 键盘按钮 F6。
    ---
    ---@type integer
    KEYBOARD_BUTTON_F6 = 530

    --- 键盘按钮 F7。
    ---
    ---@type integer
    KEYBOARD_BUTTON_F7 = 531

    --- 键盘按钮 F8。
    ---
    ---@type integer
    KEYBOARD_BUTTON_F8 = 532

    --- 键盘按钮 F9。
    ---
    ---@type integer
    KEYBOARD_BUTTON_F9 = 533

    --- 键盘按钮 F10。
    ---
    ---@type integer
    KEYBOARD_BUTTON_F10 = 534

    --- 键盘按钮 F11。
    ---
    ---@type integer
    KEYBOARD_BUTTON_F11 = 535

    --- 键盘按钮 F12。
    ---
    ---@type integer
    KEYBOARD_BUTTON_F12 = 536

    --- 键盘按钮 ENTER。
    ---
    ---@type integer
    KEYBOARD_BUTTON_ENTER = 537

    --- 键盘按钮 ESCAPE。
    ---
    ---@type integer
    KEYBOARD_BUTTON_ESCAPE = 538

    --- 键盘按钮 BACK（退格键）。
    ---
    ---@type integer
    KEYBOARD_BUTTON_BACK = 543

    --- 键盘按钮 HOME。
    ---
    ---@type integer
    KEYBOARD_BUTTON_HOME = 539

    --- 键盘按钮 RCONTROL。
    ---
    ---@type integer
    KEYBOARD_BUTTON_RCONTROL = 540

    --- 键盘按钮 LCONTROL。
    ---
    ---@type integer
    KEYBOARD_BUTTON_LCONTROL = 541

    --- 键盘按钮 DELETE。
    ---
    ---@type integer
    KEYBOARD_BUTTON_DELETE = 542

    --- 键盘按钮 BACKSPACE。
    ---
    ---@type integer
    KEYBOARD_BUTTON_BACKSPACE = 0

    --- 键盘按钮 PAGEDOWN。
    ---
    ---@type integer
    KEYBOARD_BUTTON_PAGEDOWN = 544

    --- 键盘按钮 PAGEUP。
    ---
    ---@type integer
    KEYBOARD_BUTTON_PAGEUP = 545

    --- 键盘按钮 NUMPAD0。
    ---
    ---@type integer
    KEYBOARD_BUTTON_NUMPAD0 = 546

    --- 键盘按钮 NUMPAD1。
    ---
    ---@type integer
    KEYBOARD_BUTTON_NUMPAD1 = 547

    --- 键盘按钮 NUMPAD2。
    ---
    ---@type integer
    KEYBOARD_BUTTON_NUMPAD2 = 548

    --- 键盘按钮 NUMPAD3。
    ---
    ---@type integer
    KEYBOARD_BUTTON_NUMPAD3 = 549

    --- 键盘按钮 NUMPAD4。
    ---
    ---@type integer
    KEYBOARD_BUTTON_NUMPAD4 = 550

    --- 键盘按钮 NUMPAD5。
    ---
    ---@type integer
    KEYBOARD_BUTTON_NUMPAD5 = 551

    --- 键盘按钮 NUMPAD6。
    ---
    ---@type integer
    KEYBOARD_BUTTON_NUMPAD6 = 552

    --- 键盘按钮 NUMPAD7。
    ---
    ---@type integer
    KEYBOARD_BUTTON_NUMPAD7 = 553

    --- 键盘按钮 NUMPAD8。
    ---
    ---@type integer
    KEYBOARD_BUTTON_NUMPAD8 = 554

    --- 键盘按钮 NUMPAD9。
    ---
    ---@type integer
    KEYBOARD_BUTTON_NUMPAD9 = 555

    --- 键盘按钮 MULTIPLY。
    ---
    ---@type integer
    KEYBOARD_BUTTON_MULTIPLY = 556

    --- 键盘按钮 ADD。
    ---
    ---@type integer
    KEYBOARD_BUTTON_ADD = 557

    --- 键盘按钮 SEPARATOR。
    ---
    ---@type integer
    KEYBOARD_BUTTON_SEPARATOR = 558

    --- 键盘按钮 SUBTRACT。
    ---
    ---@type integer
    KEYBOARD_BUTTON_SUBTRACT = 559

    --- 键盘按钮 DECIMAL。
    ---
    ---@type integer
    KEYBOARD_BUTTON_DECIMAL = 560

    --- 键盘按钮 DIVIDE。
    ---
    ---@type integer
    KEYBOARD_BUTTON_DIVIDE = 561

    --- 键盘按钮 TAB。
    ---
    ---@type integer
    KEYBOARD_BUTTON_TAB = 562

    --- 键盘按钮 TILDE。
    ---
    ---@type integer
    KEYBOARD_BUTTON_TILDE = 563

    --- 键盘按钮 INSERT。
    ---
    ---@type integer
    KEYBOARD_BUTTON_INSERT = 564

    --- 键盘按钮 ALT。
    ---
    ---@type integer
    KEYBOARD_BUTTON_ALT = 565

    --- 键盘按钮 ALTGR。
    ---
    ---@type integer
    KEYBOARD_BUTTON_ALTGR = 566
```

#### Mouse Key Codes

用于检查鼠标滚轮滚动的辅助工具，类似于按钮。

```lua
    --- 鼠标按钮 LEFT。
    ---
    ---@type integer
    MOUSE_BUTTON_LEFT = 513

    --- 鼠标按钮 RIGHT。
    ---
    ---@type integer
    MOUSE_BUTTON_RIGHT = 514

    --- 鼠标按钮 MIDDLE。
    ---
    ---@type integer
    MOUSE_BUTTON_MIDDLE = 515

    --- 鼠标滚轮作为按钮 UP。
    ---
    ---@type integer
    MOUSE_SCROLL_AS_BUTTON_UP = 516

    --- 鼠标滚轮作为按钮 DOWN。
    ---
    ---@type integer
    MOUSE_SCROLL_AS_BUTTON_DOWN = 517
```

#### Gamepad Key Codes

通用代码跨控制器工作；下面的 Xbox 和 PlayStation 代码是映射到通用代码的别名。

##### Generic button codes

```lua
    --- 游戏手柄方向键上。
    ---
    ---@type integer
    GAMEPAD_BUTTON_UP = 257

    --- 游戏手柄方向键下。
    ---
    ---@type integer
    GAMEPAD_BUTTON_DOWN = 259

    --- 游戏手柄方向键左。
    ---
    ---@type integer
    GAMEPAD_BUTTON_LEFT = 258

    --- 游戏手柄方向键右。
    ---
    ---@type integer
    GAMEPAD_BUTTON_RIGHT = 260

    --- 通用游戏手柄按钮 1。
    ---
    ---@type integer
    GAMEPAD_BUTTON_1 = 261

    --- 通用游戏手柄按钮 2。
    ---
    ---@type integer
    GAMEPAD_BUTTON_2 = 262

    --- 通用游戏手柄按钮 3。
    ---
    ---@type integer
    GAMEPAD_BUTTON_3 = 263

    --- 通用游戏手柄按钮 4。
    ---
    ---@type integer
    GAMEPAD_BUTTON_4 = 264

    --- 通用游戏手柄按钮 5。
    ---
    ---@type integer
    GAMEPAD_BUTTON_5 = 265

    --- 通用游戏手柄按钮 6。
    ---
    ---@type integer
    GAMEPAD_BUTTON_6 = 266

    --- 通用游戏手柄按钮 7。
    ---
    ---@type integer
    GAMEPAD_BUTTON_7 = 267

    --- 通用游戏手柄按钮 8。
    ---
    ---@type integer
    GAMEPAD_BUTTON_8 = 268

    --- 通用游戏手柄按钮 9。
    ---
    ---@type integer
    GAMEPAD_BUTTON_9 = 269

    --- 通用游戏手柄按钮 10。
    ---
    ---@type integer
    GAMEPAD_BUTTON_10 = 270

    --- 通用游戏手柄按钮 11。
    ---
    ---@type integer
    GAMEPAD_BUTTON_11 = 271

    --- 通用游戏手柄按钮 12。
    ---
    ---@type integer
    GAMEPAD_BUTTON_12 = 272

    --- 通用游戏手柄按钮 13。
    ---
    ---@type integer
    GAMEPAD_BUTTON_13 = 273

    --- 通用游戏手柄按钮 14。
    ---
    ---@type integer
    GAMEPAD_BUTTON_14 = 274

    -- 模拟摇杆和扳机作为数字按钮公开：

    --- 左摇杆上推，作为按钮。
    ---
    ---@type integer
    GAMEPAD_ANALOG_THUMBSTICK_L_AS_BUTTON_UP = 275

    --- 左摇杆下推，作为按钮。
    ---
    ---@type integer
    GAMEPAD_ANALOG_THUMBSTICK_L_AS_BUTTON_DOWN = 277

    --- 左摇杆左推，作为按钮。
    ---
    ---@type integer
    GAMEPAD_ANALOG_THUMBSTICK_L_AS_BUTTON_LEFT = 276

    --- 左摇杆右推，作为按钮。
    ---
    ---@type integer
    GAMEPAD_ANALOG_THUMBSTICK_L_AS_BUTTON_RIGHT = 278

    --- 右摇杆上推，作为按钮。
    ---
    ---@type integer
    GAMEPAD_ANALOG_THUMBSTICK_R_AS_BUTTON_UP = 279

    --- 右摇杆下推，作为按钮。
    ---
    ---@type integer
    GAMEPAD_ANALOG_THUMBSTICK_R_AS_BUTTON_DOWN = 281

    --- 右摇杆左推，作为按钮。
    ---
    ---@type integer
    GAMEPAD_ANALOG_THUMBSTICK_R_AS_BUTTON_LEFT = 280

    --- 右摇杆右推，作为按钮。
    ---
    ---@type integer
    GAMEPAD_ANALOG_THUMBSTICK_R_AS_BUTTON_RIGHT = 282

    --- 左扳机，作为按钮。
    ---
    ---@type integer
    GAMEPAD_ANALOG_TRIGGER_L_AS_BUTTON = 283

    --- 右扳机，作为按钮。
    ---
    ---@type integer
    GAMEPAD_ANALOG_TRIGGER_R_AS_BUTTON = 284
```

##### Xbox button codes

```lua
    --- Xbox X 按钮（GAMEPAD_BUTTON_1 的别名）。
    ---
    ---@type integer
    GAMEPAD_BUTTON_XBOX_X = 261

    --- Xbox A 按钮（GAMEPAD_BUTTON_2 的别名）。
    ---
    ---@type integer
    GAMEPAD_BUTTON_XBOX_A = 262

    --- Xbox B 按钮（GAMEPAD_BUTTON_3 的别名）。
    ---
    ---@type integer
    GAMEPAD_BUTTON_XBOX_B = 263

    --- Xbox Y 按钮（GAMEPAD_BUTTON_4 的别名）。
    ---
    ---@type integer
    GAMEPAD_BUTTON_XBOX_Y = 264

    --- Xbox L1 按钮（GAMEPAD_BUTTON_5 的别名）。
    ---
    ---@type integer
    GAMEPAD_BUTTON_XBOX_L1 = 265

    --- Xbox LT 按钮（GAMEPAD_ANALOG_TRIGGER_L_AS_BUTTON 的别名）。
    ---
    ---@type integer
    GAMEPAD_BUTTON_XBOX_LT = 283

    --- Xbox R1 按钮（GAMEPAD_BUTTON_6 的别名）。
    ---
    ---@type integer
    GAMEPAD_BUTTON_XBOX_R1 = 266

    --- Xbox RT 按钮（GAMEPAD_ANALOG_TRIGGER_R_AS_BUTTON 的别名）。
    ---
    ---@type integer
    GAMEPAD_BUTTON_XBOX_RT = 284

    --- Xbox L3 按钮（GAMEPAD_BUTTON_7 的别名）。
    ---
    ---@type integer
    GAMEPAD_BUTTON_XBOX_L3 = 267

    --- Xbox R3 按钮（GAMEPAD_BUTTON_8 的别名）。
    ---
    ---@type integer
    GAMEPAD_BUTTON_XBOX_R3 = 268

    --- Xbox BACK 按钮（GAMEPAD_BUTTON_9 的别名）。
    ---
    ---@type integer
    GAMEPAD_BUTTON_XBOX_BACK = 269

    --- Xbox START 按钮（GAMEPAD_BUTTON_10 的别名）。
    ---
    ---@type integer
    GAMEPAD_BUTTON_XBOX_START = 270
```

##### PlayStation button codes

```lua
    --- PlayStation SQUARE 按钮（GAMEPAD_BUTTON_1 的别名）。
    ---
    ---@type integer
    GAMEPAD_BUTTON_PLAYSTATION_SQUARE = 261

    --- PlayStation CROSS 按钮（GAMEPAD_BUTTON_2 的别名）。
    ---
    ---@type integer
    GAMEPAD_BUTTON_PLAYSTATION_CROSS = 262

    --- PlayStation CIRCLE 按钮（GAMEPAD_BUTTON_3 的别名）。
    ---
    ---@type integer
    GAMEPAD_BUTTON_PLAYSTATION_CIRCLE = 263

    --- PlayStation TRIANGLE 按钮（GAMEPAD_BUTTON_4 的别名）。
    ---
    ---@type integer
    GAMEPAD_BUTTON_PLAYSTATION_TRIANGLE = 264

    --- PlayStation L1 按钮（GAMEPAD_BUTTON_5 的别名）。
    ---
    ---@type integer
    GAMEPAD_BUTTON_PLAYSTATION_L1 = 265

    --- PlayStation L2 按钮（GAMEPAD_ANALOG_TRIGGER_L_AS_BUTTON 的别名）。
    ---
    ---@type integer
    GAMEPAD_BUTTON_PLAYSTATION_L2 = 283

    --- PlayStation R1 按钮（GAMEPAD_BUTTON_6 的别名）。
    ---
    ---@type integer
    GAMEPAD_BUTTON_PLAYSTATION_R1 = 266

    --- PlayStation R2 按钮（GAMEPAD_ANALOG_TRIGGER_R_AS_BUTTON 的别名）。
    ---
    ---@type integer
    GAMEPAD_BUTTON_PLAYSTATION_R2 = 284

    --- PlayStation L3 按钮（GAMEPAD_BUTTON_7 的别名）。
    ---
    ---@type integer
    GAMEPAD_BUTTON_PLAYSTATION_L3 = 267

    --- PlayStation R3 按钮（GAMEPAD_BUTTON_8 的别名）。
    ---
    ---@type integer
    GAMEPAD_BUTTON_PLAYSTATION_R3 = 268

    --- PlayStation SHARE 按钮（GAMEPAD_BUTTON_9 的别名）。
    ---
    ---@type integer
    GAMEPAD_BUTTON_PLAYSTATION_SHARE = 269

    --- PlayStation OPTION 按钮（GAMEPAD_BUTTON_10 的别名）。
    ---
    ---@type integer
    GAMEPAD_BUTTON_PLAYSTATION_OPTION = 270

    --- PlayStation SELECT 按钮（GAMEPAD_BUTTON_PLAYSTATION_SHARE 的别名）。
    ---
    ---@type integer
    GAMEPAD_BUTTON_PLAYSTATION_SELECT = 269

    --- PlayStation START 按钮（GAMEPAD_BUTTON_PLAYSTATION_OPTION 的别名）。
    ---
    ---@type integer
    GAMEPAD_BUTTON_PLAYSTATION_START = 270
```

#### Gamepad Analog Codes

```lua
    --- 游戏手柄模拟摇杆 L。
    ---
    ---@type integer
    GAMEPAD_ANALOG_THUMBSTICK_L = 0

    --- 游戏手柄模拟摇杆 R。
    ---
    ---@type integer
    GAMEPAD_ANALOG_THUMBSTICK_R = 1

    --- 游戏手柄模拟扳机 L。
    ---
    ---@type integer
    GAMEPAD_ANALOG_TRIGGER_L = 2

    --- 游戏手柄模拟扳机 R。
    ---
    ---@type integer
    GAMEPAD_ANALOG_TRIGGER_R = 3
```

#### Controller preference

```lua
    --- 控制器偏好 通用。
    ---
    ---@type integer
    CONTROLLER_PREFERENCE_GENERIC = 0

    --- 控制器偏好 PlayStation。
    ---
    ---@type integer
    CONTROLLER_PREFERENCE_PLAYSTATION = 1

    --- 控制器偏好 Xbox。
    ---
    ---@type integer
    CONTROLLER_PREFERENCE_XBOX = 2
```

#### Cursor codes

```lua
    --- 光标 默认。
    ---
    ---@type integer
    CURSOR_DEFAULT = 0

    --- 光标 文本输入。
    ---
    ---@type integer
    CURSOR_TEXTINPUT = 1

    --- 光标 全方向调整大小。
    ---
    ---@type integer
    CURSOR_RESIZEALL = 2

    --- 光标 南北调整大小。
    ---
    ---@type integer
    CURSOR_RESIZE_NS = 3

    --- 光标 东西调整大小。
    ---
    ---@type integer
    CURSOR_RESIZE_EW = 4

    --- 光标 东北-西南调整大小。
    ---
    ---@type integer
    CURSOR_RESIZE_NESW = 5

    --- 光标 西北-东南调整大小。
    ---
    ---@type integer
    CURSOR_RESIZE_NWSE = 6

    --- 光标 手形。
    ---
    ---@type integer
    CURSOR_HAND = 7

    --- 光标 不允许。
    ---
    ---@type integer
    CURSOR_NOTALLOWED = 8

    --- 光标 十字。
    ---
    ---@type integer
    CURSOR_CROSS = 9
```

### Physics

```lua
    --- 创建 Physics 对象。使用全局 `physics` 而不是
    --- 构造一个。
    ---
    ---@return Physics
    function Physics() end

    --- 全局物理系统。使用全局 `physics` 对象控制和
    --- 查询物理模拟。
    ---
    ---@class Physics
    local Physics = {}

    --- 使用此全局对象访问物理函数。
    ---
    ---@type Physics
    physics = nil

    --- 启用/禁用整个物理引擎。
    ---
    ---@param value boolean
    function Physics.SetEnabled(value) end

    --- 返回物理是否启用。
    ---
    ---@return boolean
    function Physics.IsEnabled() end

    --- 启用/禁用物理模拟。物理引擎状态将
    --- 更新但不模拟
    ---
    ---@param value boolean
    function Physics.SetSimulationEnabled(value) end

    --- 返回是否启用模拟。
    ---
    ---@return boolean
    function Physics.IsSimulationEnabled() end

    --- 启用/禁用物理插值。启用时，模拟的
    --- 固定帧率将被插值以匹配渲染的可变帧率
    ---
    ---@param value boolean
    function Physics.SetInterpolationEnabled(value) end

    --- 返回是否启用插值。
    ---
    ---@return boolean
    function Physics.IsInterpolationEnabled() end

    --- 启用/禁用物理对象的调试绘制。
    ---
    ---@param value boolean
    function Physics.SetDebugDrawEnabled(value) end

    --- 返回是否启用调试绘制。
    ---
    ---@return boolean
    function Physics.IsDebugDrawEnabled() end

    --- 设置模拟的精度。此值对应最大
    --- 模拟步数。较高的值会更慢但更精确。
    ---
    ---@param value integer
    function Physics.SetAccuracy(value) end

    --- 返回精度。
    ---
    ---@return integer
    function Physics.GetAccuracy() end

    --- 设置物理模拟的每秒帧率分辨率
    --- （默认 = 120 FPS）。
    ---
    ---@param value number
    function Physics.SetFrameRate(value) end

    --- 返回帧率。
    ---
    ---@return number
    function Physics.GetFrameRate() end

    --- 返回最新模拟步骤中物体的线速度。
    ---
    ---@param component RigidBodyPhysicsComponent
    ---
    ---@return Vector
    function Physics.GetVelocity(component) end

    --- 返回最新模拟步骤中物体的当前位置。
    ---
    ---@param component RigidBodyPhysicsComponent
    ---
    ---@return Vector
    function Physics.GetPosition(component) end

    --- 返回最新模拟步骤中物体的当前旋转。
    ---
    ---@param component RigidBodyPhysicsComponent
    ---
    ---@return Vector
    function Physics.GetRotation(component) end

    --- 返回刚体的地面位置（如果它启用了角色物理）。
    ---
    ---@param component RigidBodyPhysicsComponent
    ---
    ---@return Vector
    function Physics.GetCharacterGroundPosition(component) end

    --- 返回刚体的地面法线（如果它启用了角色物理）。
    ---
    ---@param component RigidBodyPhysicsComponent
    ---
    ---@return Vector
    function Physics.GetCharacterGroundNormal(component) end

    --- 返回刚体的地面速度（如果它启用了角色物理）。
    ---
    ---@param component RigidBodyPhysicsComponent
    ---
    ---@return Vector
    function Physics.GetCharacterGroundVelocity(component) end

    --- 如果角色物理由正常或陡峭地面支持则返回
    --- true。
    ---
    ---@param component RigidBodyPhysicsComponent
    ---
    ---@return boolean
    function Physics.IsCharacterGroundSupported(component) end

    --- 返回角色物理的 `CharacterGroundStates`。
    ---
    ---@param component RigidBodyPhysicsComponent
    ---
    ---@return CharacterGroundStates
    function Physics.GetCharacterGroundState(component) end

    --- 将物理角色的形状更改为具有指定
    --- 高度和半径的胶囊体。成功返回 true，否则返回 false。失败
    --- 意味着有东西阻挡了角色。
    ---
    ---@param component RigidBodyPhysicsComponent
    ---@param height number
    ---@param radius number
    ---
    ---@return boolean
    function Physics.ChangeCharacterShape(component, height, radius) end

    --- 将移动逻辑应用到物理角色。
    ---
    ---@param component RigidBodyPhysicsComponent
    ---@param movement_direction Vector
    ---@param movement_speed? number
    ---@param jump? number
    ---@param controlMovementDuringJump? boolean
    function Physics.MoveCharacter(
        component,
        movement_direction,
        movement_speed,
        jump,
        controlMovementDuringJump
    ) end

    --- 启用/禁用刚体或布娃娃的幽灵模式（所有碰撞
    --- 禁用）。
    ---
    ---@param component RigidBodyPhysicsComponent|HumanoidComponent
    ---@param value boolean
    function Physics.SetGhostMode(component, value) end

    --- 启用/禁用布娃娃的幽灵模式。在幽灵模式下，布娃娃将
    --- 不与任何东西碰撞。例如，如果人形坐在
    --- 载具内，则启用此功能。
    ---
    ---@param humanoid HumanoidComponent
    ---@param value boolean
    function Physics.SetRagdollGhostMode(humanoid, value) end

    --- 传送动态体。
    ---
    ---@param component RigidBodyPhysicsComponent
    ---@param position Vector
    function Physics.SetPosition(component, position) end

    --- 传送动态体。
    ---
    ---@param component RigidBodyPhysicsComponent
    ---@param position Vector
    ---@param rotationQuaternion Vector
    function Physics.SetPositionAndRotation(
        component,
        position,
        rotationQuaternion
    ) end

    --- 手动设置线速度。
    ---
    ---@param component RigidBodyPhysicsComponent
    ---@param velocity Vector
    function Physics.SetLinearVelocity(component, velocity) end

    --- 手动设置角速度。
    ---
    ---@param component RigidBodyPhysicsComponent
    ---@param velocity Vector
    function Physics.SetAngularVelocity(component, velocity) end

    --- 在物体中心施加力。
    ---
    ---@param component RigidBodyPhysicsComponent
    ---@param force Vector
    function Physics.ApplyForce(component, force) end

    --- 在物体本地位置施加力（at_local 控制 at 是否
    --- 在物体的本地空间中）。
    ---
    ---@param component RigidBodyPhysicsComponent
    ---@param force Vector
    ---@param at Vector
    ---@param at_local boolean
    function Physics.ApplyForceAt(component, force, at, at_local) end

    --- 在物体中心施加冲量。
    ---
    ---@param component RigidBodyPhysicsComponent
    ---@param impulse Vector
    function Physics.ApplyImpulse(component, impulse) end

    --- 在布娃娃骨骼的物体中心施加冲量。
    ---
    ---@param humanoid HumanoidComponent
    ---@param bone HumanoidBone
    ---@param impulse Vector
    function Physics.ApplyImpulse(humanoid, bone, impulse) end

    --- 在物体本地位置施加冲量（at_local 控制 `at` 是否
    --- 在物体的本地空间中）。
    ---
    ---@param component RigidBodyPhysicsComponent
    ---@param impulse Vector
    ---@param at Vector
    ---@param at_local boolean
    function Physics.ApplyImpulseAt(component, impulse, at, at_local) end

    --- 在布娃娃骨骼的物体本地位置施加冲量（at_local 控制
    --- `at` 是否在物体的本地空间中）。
    ---
    ---@param humanoid HumanoidComponent
    ---@param bone HumanoidBone
    ---@param impulse Vector
    ---@param at Vector
    ---@param at_local boolean
    function Physics.ApplyImpulseAt(humanoid, bone, impulse, at, at_local) end

    --- 在物体中心施加扭矩。
    ---
    ---@param component RigidBodyPhysicsComponent
    ---@param torque Vector
    function Physics.ApplyTorque(component, torque) end

    --- 激活场景中的所有刚体
    ---
    ---@param scene Scene
    function Physics.ActivateAllRigidBodies(scene) end

    --- 将所有刚体重置为初始方向。
    ---
    ---@param scene Scene
    function Physics.ResetPhysicsObjects(scene) end

    --- 强制设置刚体的激活状态。使用值
    --- `ACTIVATION_STATE_ACTIVE` 或 `ACTIVATION_STATE_INACTIVE`。
    ---
    ---@param component RigidBodyPhysicsComponent
    ---@param state integer
    function Physics.SetActivationState(component, state) end

    --- 强制设置软体的激活状态。使用值
    --- `ACTIVATION_STATE_ACTIVE` 或 `ACTIVATION_STATE_INACTIVE`。
    ---
    ---@param component SoftBodyPhysicsComponent
    ---@param state integer
    function Physics.SetActivationState(component, state) end

    --- 激活状态 活动。
    ---
    ---@type integer
    ACTIVATION_STATE_ACTIVE = 0

    --- 激活状态 不活动。
    ---
    ---@type integer
    ACTIVATION_STATE_INACTIVE = 1

    --- 描述角色控制器当前如何被地面支持。
    ---
    ---@enum CharacterGroundStates
    CharacterGroundStates = {
        OnGround = 0, -- 角色在地面上，可以自由移动。
        -- 角色在太陡的斜坡上，无法继续攀爬。
        -- 调用者应开始施加向下速度（如果希望从斜坡滑下）。
        OnSteepGround = 1,
        -- 角色接触物体，但不受其支持，应该下落。
        -- GetGroundXXX 函数将返回有关接触对象的信息。
        NotSupported = 2,
        InAir = 3, -- 角色在空中，不接触任何东西。
    }

    --- 用射线执行物理场景相交以获取最近命中。
    ---
    ---@param scene Scene
    ---@param ray Ray
    ---
    ---@return Entity entity
    ---@return Vector position
    ---@return Vector normal
    ---@return Entity humanoid_ragdoll_entity
    ---@return HumanoidBone humanoid_bone
    ---@return Vector position_local
    function Physics.Intersects(scene, ray) end

    --- 从驱动程序设置输入：forward 和 right 值在 -1
    --- 和 1 之间，表示后退/前进或左/右。brake 和 handbrake
    --- （handbrake = 摩托车后刹车）值在 0 和 1 之间。
    ---
    ---@param rigidbody RigidBodyPhysicsComponent
    ---@param forward? number
    ---@param right? number
    ---@param brake? number
    ---@param handbrake? number
    function Physics.DriveVehicle(
        rigidbody,
        forward,
        right,
        brake,
        handbrake
    ) end

    --- 前方方向的有符号速度量。
    ---
    ---@param rigidbody RigidBodyPhysicsComponent
    ---
    ---@return number
    function Physics.GetVehicleForwardVelocity(rigidbody) end

    --- 拾取和拖动物理对象，如布娃娃和刚体。
    ---
    ---@param scene Scene
    ---@param ray Ray
    ---@param op PickDragOperation
    ---@param constraint? ConstraintType
    ---@param break_distance? number
    function Physics.PickDrag(scene, ray, op, constraint, break_distance) end

    --- 可连接两个刚体的物理约束类型。
    ---
    ---@enum ConstraintType
    ConstraintType = {
        Fixed = 0,
        Point = 1,
    }

    --- 返回角色碰撞容差距离。
    ---
    ---@return number
    function Physics.GetCharacterCollisionTolerance() end

    --- 设置角色碰撞容差距离。
    ---
    ---@param value number
    function Physics.SetCharacterCollisionTolerance(value) end

    --- 为场景优化物理粗相位。传 force = true 以
    --- 即使未标记为脏也重建。
    ---
    ---@param scene Scene
    ---@param force? boolean
    function Physics.OptimizeBroadPhase(scene, force) end
```

#### PickDragOperation

```lua
    --- 创建 PickDragOperation，用于用光标抓取和拖动物理体。
    ---
    ---@return PickDragOperation
    function PickDragOperation() end

    --- 跟踪物理拾取拖动操作。与 `phyiscs.PickDrag()`
    --- 函数一起使用。首次使用此对象进行 PickDrag 时，操作
    --- 将启动，当你调用 Finish() 或对象被销毁时操作将结束。
    ---
    ---@class PickDragOperation
    local PickDragOperation = {}

    --- 完成操作，放下物理对象。
    function PickDragOperation.Finish() end
```

### Path finding

#### VoxelGrid

```lua
    --- 创建给定维度的体素网格，用于导航和
    --- 体素射线查询。
    ---
    ---@param dimX? integer
    ---@param dimY integer
    ---@param dimZ integer
    ---
    ---@return VoxelGrid
    function VoxelGrid(dimX, dimY, dimZ) end

    --- 寻路操作可使用体素网格和路径
    --- 查询进行。体素网格可以存储关于场景或场景一部分的空间信息，
    --- 而路径查询管理从体素网格内一点到另一点的寻路
    --- 结果。
    ---
    ---@class VoxelGrid
    local VoxelGrid = {}


    --- 为 dimX * dimY * dimZ 数量的体素分配内存并将它们
    --- 初始化为空。
    ---
    ---@param dimX integer
    ---@param dimY integer
    ---@param dimZ integer
    function VoxelGrid.Init(dimX, dimY, dimZ) end

    --- 将所有体素初始化为空。
    function VoxelGrid.ClearData() end

    --- 将体素网格体积放置以适配给定 AABB。体素数量
    --- 不变，仅中心和体素大小变化。
    ---
    ---@param aabb AABB
    function VoxelGrid.FromAABB(aabb) end

    --- 体素化三角形，要么添加到体素中（默认），要么
    --- 移除体素
    ---
    ---@param a Vector
    ---@param b Vector
    ---@param c Vector
    ---@param subtract? boolean
    function VoxelGrid.InjectTriangle(a, b, c, subtract) end

    --- 体素化轴对齐边界框，要么添加到体素中
    --- （默认），要么移除体素。
    ---
    ---@param aabb AABB
    ---@param subtract? boolean
    function VoxelGrid.InjectAABB(aabb, subtract) end

    --- 体素化球体，要么添加到体素中（默认），要么移除
    --- 体素。
    ---
    ---@param sphere Sphere
    ---@param subtract? boolean
    function VoxelGrid.InjectSphere(sphere, subtract) end

    --- 体素化胶囊体，要么添加到体素中（默认），要么
    --- 移除体素。
    ---
    ---@param capsule Capsule
    ---@param subtract? boolean
    function VoxelGrid.InjectCapsule(capsule, subtract) end

    --- 将世界空间中的位置转换为体素坐标。
    ---
    ---@param pos Vector
    ---
    ---@return integer x
    ---@return integer y
    ---@return integer z
    function VoxelGrid.WorldToCoord(pos) end

    --- 将体素坐标转换为世界空间位置。
    ---
    ---@param x integer
    ---@param y integer
    ---@param z integer
    ---
    ---@return Vector
    function VoxelGrid.CoordToWorld(x, y, z) end

    --- 如果体素为空则返回 false，如果有效则返回 true。
    ---
    ---@param pos Vector
    ---
    ---@return boolean
    function VoxelGrid.CheckVoxel(pos) end

    --- 如果体素为空则返回 false，如果有效则返回 true。
    ---
    ---@param x integer
    ---@param y integer
    ---@param z integer
    ---
    ---@return boolean
    function VoxelGrid.CheckVoxel(x, y, z) end

    --- 将单个体素设置为指定状态。
    ---
    ---@param pos Vector
    ---@param value boolean
    function VoxelGrid.SetVoxel(pos, value) end

    --- 将单个体素设置为指定状态。
    ---
    ---@param x integer
    ---@param y integer
    ---@param z integer
    ---@param value boolean
    function VoxelGrid.SetVoxel(x, y, z, value) end

    --- 返回体素网格体积的中心。
    ---
    ---@return Vector
    function VoxelGrid.GetCenter() end

    --- 设置体素网格体积的中心。
    ---
    ---@param pos Vector
    function VoxelGrid.SetCenter(pos) end

    --- 获取世界空间中一个体素的半范围。
    ---
    ---@return Vector
    function VoxelGrid.GetVoxelSize() end

    --- 设置世界空间中一个体素的半范围。
    ---
    ---@param voxelsize Vector
    function VoxelGrid.SetVoxelSize(voxelsize) end

    --- 在所有维度中统一设置世界空间中一个体素的半范围。
    ---
    ---@param voxelsize number
    function VoxelGrid.SetVoxelSize(voxelsize) end

    --- 返回体素调试可视化的颜色。
    ---
    ---@return Vector
    function VoxelGrid.GetDebugColor() end

    --- 设置体素调试可视化的颜色。
    ---
    ---@param color Vector
    function VoxelGrid.SetDebugColor(color) end

    --- 返回体素网格范围的调试可视化颜色。
    ---
    ---@return Vector
    function VoxelGrid.GetDebugColorExtent() end

    --- 设置体素网格范围的调试可视化颜色。
    ---
    ---@param color Vector
    function VoxelGrid.SetDebugColorExtent(color) end

    --- 返回体素网格的内存消耗，以字节为单位。
    ---
    ---@return integer
    function VoxelGrid.GetMemorySize() end

    --- 从观察者到目标体素坐标执行视线遮挡测试。如果
    --- 发现遮挡则返回 false，否则返回 true。
    ---
    ---@param observer_x integer
    ---@param observer_y integer
    ---@param observer_z integer
    ---@param subject_x integer
    ---@param subject_y integer
    ---@param subject_z integer
    ---
    ---@return boolean
    function VoxelGrid.IsVisible(
        observer_x,
        observer_y,
        observer_z,
        subject_x,
        subject_y,
        subject_z
    ) end

    --- 从观察者到目标世界空间点执行视线遮挡测试。如果
    --- 发现遮挡则返回 false，否则返回 true。
    ---
    ---@param observer AABB
    ---@param subject AABB
    ---
    ---@return boolean
    function VoxelGrid.IsVisible(observer, subject) end

    --- 从观察者世界空间点到目标 AABB 执行视线遮挡测试。
    --- 如果 AABB 的任何接触体素可见则返回 true，否则返回 false。
    ---
    ---@param observer AABB
    ---@param subject AABB
    ---
    ---@return boolean
    function VoxelGrid.IsVisible(observer, subject) end

    --- 将每个被包围的空体素设置为实体。
    function VoxelGrid.FloodFill() end

    --- 将另一个网格的体素添加到此网格中。
    ---
    ---@param other VoxelGrid
    function VoxelGrid.Add(other) end

    --- 从此网格中移除另一个网格的体素。
    ---
    ---@param other VoxelGrid
    function VoxelGrid.Subtract(other) end
```

#### PathQuery

```lua
    --- 创建 PathQuery 用于通过体素网格查找路径。
    ---
    ---@return PathQuery
    function PathQuery() end

    --- 计算并存储通过 VoxelGrid 的路径，用于导航和 AI
    --- 移动。
    ---
    ---@class PathQuery
    local PathQuery = {}


    --- 计算从起点到目标在体素网格上的路径并存储
    --- 结果。
    ---
    ---@param start Vector
    ---@param goal Vector
    ---@param voxelgrid VoxelGrid
    function PathQuery.Process(start, goal, voxelgrid) end

    --- 为目标位置搜索掩护以躲避观察者。搜索将在
    --- 特定方向上，在指定距离内（大约，在体素精度
    --- 范围内）。
    ---
    ---@param observer Vector
    ---@param subject Vector
    ---@param direction Vector
    ---@param max_distance number
    ---@param voxelgrid VoxelGrid
    function PathQuery.SearchCover(
        observer,
        subject,
        direction,
        max_distance,
        voxelgrid
    ) end

    --- 返回上次调用 Process() 是否成功找到
    --- 路径。
    ---
    ---@return boolean
    function PathQuery.IsSuccessful() end

    --- 获取路径上从起始位置的下一个路径点。这
    --- 需要事先调用 Process()。
    ---
    ---@return Vector
    function PathQuery.GetNextWaypoint() end

    --- 使用 DrawPathQuery() 时启用/禁用路径点调试渲染。如果
    --- 启用，体素路径点将以蓝色绘制，简化的体素
    --- 路径点将以粉色绘制。
    ---
    ---@param value boolean
    function PathQuery.SetDebugDrawWaypointsEnabled(value) end

    --- 启用/禁用飞行行为。启用飞行时，路径将
    --- 在空体素（空气）上，否则默认情况下路径将在
    --- 填充体素（地面）上。
    ---
    ---@param value boolean
    function PathQuery.SetFlying(value) end

    --- 返回是否飞行。
    ---
    ---@return boolean
    function PathQuery.IsFlying() end

    --- 以体素为单位设置导航宽度要求。这意味着查询将
    --- 在水平方向上与障碍物保持多少体素的距离。
    ---
    ---@param value integer
    function PathQuery.SetAgentWidth(value) end

    --- 返回代理宽度。
    ---
    ---@param value integer
    ---
    ---@return integer
    function PathQuery.GetAgentWidth(value) end

    --- 以体素为单位设置导航高度要求。这意味着查询将
    --- 在垂直方向上与障碍物保持多少体素的距离。
    ---
    ---@param value integer
    function PathQuery.SetAgentHeight(value) end

    --- 返回代理高度。
    ---
    ---@param value integer
    ---
    ---@return integer
    function PathQuery.GetAgentHeight(value) end

    --- 返回在 Process() 中计算的路径点数量。
    ---
    ---@return integer
    function PathQuery.GetWaypointCount() end

    --- 返回指定索引处的路径点（方向：起点 -> 目标）。
    ---
    ---@param index integer
    ---
    ---@return Vector
    function PathQuery.GetWaypoint(index) end

    --- 返回目标位置。
    ---
    ---@return Vector
    function PathQuery.GetGoal() end
```

### TrailRenderer

```lua
    --- 轨迹渲染器。
    ---
    ---@return TrailRenderer
    function TrailRenderer() end

    --- 通过一系列点渲染平滑的带状轨迹，例如用于
    --- 弹射物或武器挥动。
    ---
    ---@class TrailRenderer
    local TrailRenderer = {}

    --- 向轨迹添加新点。注意：如果未指定旋转，则
    --- 点将面向相机，否则 UP 方向将被旋转。
    ---
    ---@param pos Vector
    ---@param width? number
    ---@param color? Vector
    ---@param rotationQuaternion? Vector
    function TrailRenderer.AddPoint(pos, width, color, rotationQuaternion) end

    --- 在最后一点处切断轨迹并开始新轨迹。你可以指定
    --- 此切割将创建先前添加点的循环。
    ---
    ---@param loop? boolean
    function TrailRenderer.Cut(loop) end

    --- 对整个轨迹持续应用淡出，并移除因淡出而
    --- 可移除的段。
    ---
    ---@param amount number
    function TrailRenderer.Fade(amount) end

    --- 移除轨迹中的所有点和切割。
    ---
    function TrailRenderer.Clear() end

    --- 返回轨迹中的点数。
    ---
    ---@return integer
    function TrailRenderer.GetPointCount() end

    --- 返回给定索引处轨迹点的位置、宽度和颜色。
    ---
    ---@param index integer
    ---
    ---@return Vector position
    ---@return number width
    ---@return Vector color
    function TrailRenderer.GetPoint(index) end

    --- 在指定索引上设置点参数。
    ---
    ---@param pos Vector
    ---@param width? number
    ---@param color? Vector
    function TrailRenderer.SetPoint(pos, width, color) end

    --- 设置整个轨迹的混合模式。
    ---
    ---@param blendmode integer
    function TrailRenderer.SetBlendMode(blendmode) end

    --- 返回混合模式。
    ---
    ---@return integer
    function TrailRenderer.GetBlendMode() end

    --- 设置整个轨迹的细分数。
    ---
    ---@param subdiv integer
    function TrailRenderer.SetSubdivision(subdiv) end

    --- 返回细分。
    ---
    ---@return integer
    function TrailRenderer.GetSubdivision() end

    --- 设置整个轨迹的宽度。
    ---
    ---@param width number
    function TrailRenderer.SetWidth(width) end

    --- 返回宽度。
    ---
    ---@return number
    function TrailRenderer.GetWidth() end

    --- 设置整个轨迹的颜色。
    ---
    ---@param color Vector
    function TrailRenderer.SetColor(color) end

    --- 返回颜色。
    ---
    ---@return Vector
    function TrailRenderer.GetColor() end

    --- 设置整个轨迹的纹理。
    ---
    ---@param tex Texture
    function TrailRenderer.SetTexture(tex) end

    --- 返回纹理。
    ---
    ---@return Texture
    function TrailRenderer.GetTexture() end

    --- 设置整个轨迹的纹理 2。
    ---
    ---@param tex Texture
    function TrailRenderer.SetTexture2(tex) end

    --- 返回纹理 2。
    ---
    ---@return Texture
    function TrailRenderer.GetTexture2() end

    --- 设置整个轨迹的纹理 UV 平铺乘加值。
    ---
    ---@param tex Texture
    function TrailRenderer.SetTexMulAdd(tex) end

    --- 返回纹理乘加。
    ---
    ---@return Texture
    function TrailRenderer.GetTexMulAdd() end

    --- 设置整个轨迹的纹理 2 UV 平铺乘加值。
    ---
    ---@param tex Texture
    function TrailRenderer.SetTexMulAdd2(tex) end

    --- 返回纹理乘加 2。
    ---
    ---@return Texture
    function TrailRenderer.GetTexMulAdd2() end

    --- 设置深度柔化量（默认 = 10）。
    ---
    ---@param value number
    function TrailRenderer.SetDepthSoften(value) end
```

### Network

引擎网络系统的脚本句柄。它注册为
`Network` 类并通过全局 `network` 对象公开。

> **注意：** 底层 `wi::network` C++ API（套接字、连接、发送/
> 接收）尚未暴露给 Lua，因此此对象目前不公开任何
> 方法或属性。此处为完整性而记录；类型和
> 全局对象存在且可引用，但在引擎绑定它们之前没有可调用的成员。

```lua
    --- 创建 Network 对象。使用全局 `network` 而不是
    --- 构造一个。
    ---
    ---@return Network
    function Network() end

    --- 网络系统句柄。目前是占位符：引擎注册了
    --- 类型和全局 `network` 对象，但尚未公开可脚本化的
    --- 方法或属性。
    ---
    ---@class Network
    local Network = {}

    --- 使用此全局对象访问网络（尚未绑定方法）。
    ---
    ---@type Network
    network = nil
```
