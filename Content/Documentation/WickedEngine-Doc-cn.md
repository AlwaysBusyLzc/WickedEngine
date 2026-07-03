<img src="../logo_small.png" width="128px"/>

# WickedEngine 文档
这是 Wicked Engine 的 C++ 功能文档
- [编辑器手册](WickedEditor-Manual.pdf)<br/>
- [Lua 文档](ScriptingAPI-Documentation.md)<br/>

## 目录
0. [构建与链接](#构建与链接)
0. [基本运行流程](#基本运行流程)
1. [高层接口](#高层接口)
	1. [Application](#application)
	2. [RenderPath](#renderpath)
	3. [RenderPath2D](#renderpath2d)
	4. [RenderPath3D](#renderpath3d)
	9. [RenderPath3D_Pathtracing](#renderpath3d_pathtracing)
		1. [降噪器](#降噪器)
	10. [LoadingScreen](#loadingscreen)
2. [系统](#系统)
	1. [实体-组件系统](#实体-组件系统)
	2. [场景系统](#场景系统)
		1. [NameComponent](#namecomponent)
		2. [LayerComponent](#layercomponent)
		3. [TransformComponent](#transformcomponent)
		4. [PreviousFrameTransformComponent](#previousframetransformcomponent)
		5. [HierarchyComponent](#hierarchycomponent)
		6. [MaterialComponent](#materialcomponent)
		7. [MeshComponent](#meshcomponent)
		8. [ImpostorComponent](#impostorcomponent)
		9. [ObjectComponent](#objectcomponent)
		10. [RigidBodyPhysicsComponent](#rigidbodyphysicscomponent)
		11. [SoftBodyPhysicsComponent](#softbodyphysicscomponent)
		12. [ArmatureComponent](#armaturecomponent)
		13. [LightComponent](#lightcomponent)
		14. [CameraComponent](#cameracomponent)
		15. [EnvironmentProbeComponent](#environmentprobecomponent)
		16. [ForceFieldComponent](#forcefieldcomponent)
		17. [DecalComponent](#decalcomponent)
		18. [AnimationDataComponent](#animationdatacomponent)
		18. [AnimationComponent](#animationcomponent)
		19. [WeatherComponent](#weathercomponent)
		20. [SoundComponent](#soundcomponent)
		21. [InverseKinematicsComponent](#inversekinematicscomponent)
		22. [SpringComponent](#springcomponent)
		22. [ColliderComponent](#collidercomponent)
		22. [ScriptComponent](#scriptcomponent)
		23. [Scene](#scene)
	3. [作业系统](#作业系统)
	4. [初始化器](#初始化器)
	5. [平台](#平台)
	6. [事件处理器](#事件处理器)
	7. [画布](#画布)
3. [图形](#图形)
	1. [图形 API](#图形-api)
		1. [GraphicsDevice](#graphicsdevice)
			1. [调试设备](#调试设备)
			2. [创建资源](#创建资源)
			3. [销毁资源](#销毁资源)
			4. [工作提交](#工作提交)
				1. [异步计算](#异步计算)
			5. [呈现到屏幕](#呈现到屏幕)
				1. [HDR 显示](#hdr-显示)
			6. [资源绑定](#资源绑定)
			6. [无绑定资源](#无绑定资源)
			7. [子资源](#子资源)
			8. [管线状态和着色器](#管线状态和着色器)
			9. [渲染通道](#渲染通道)
			10. [GPU 屏障](#gpu-屏障)
			11. [纹理](#纹理)
			12. [GPU 缓冲区](#gpu-缓冲区)
			13. [更新 GPU 缓冲区](#更新-gpu-缓冲区)
			14. [GPU 查询](#gpu-查询)
			15. [RayTracingAccelerationStructure](#raytracingaccelerationstructure)
			16. [RayTracingPipelineState](#raytracingpipelinestate)
			17. [可变速率着色](#可变速率着色)
			17. [视频解码](#视频解码)
		2. [GraphicsDevice_DX11](#graphicsdevice_dx11)
		3. [GraphicsDevice_DX12](#graphicsdevice_dx12)
		4. [GraphicsDevice_Vulkan](#graphicsdevice_vulkan)
	2. [渲染器](#渲染器)
		1. [DrawScene](#drawscene)
		3. [曲面细分](#曲面细分)
		4. [遮挡剔除](#遮挡剔除)
		5. [阴影贴图](#阴影贴图)
		6. [UpdatePerFrameData](#updateperframedata)
		7. [UpdateRenderData](#updaterenderdata)
		8. [光线追踪（硬件加速）](#光线追踪硬件加速)
		8. [光线追踪（计算）](#光线追踪计算)
		9. [路径追踪](#路径追踪)
		10. [光照贴图烘焙](#光照贴图烘焙)
		11. [场景 BVH](#场景-bvh)
		12. [贴花](#贴花)
		13. [环境探针](#环境探针)
		14. [后处理](#后处理)
		15. [实例化](#实例化)
		16. [模板](#模板)
		17. [加载着色器](#加载着色器)
		18. [调试绘制](#调试绘制)
		19. [动画蒙皮](#动画蒙皮)
		20. [自定义着色器](#自定义着色器)
	3. [枚举](#枚举)
	4. [图像渲染器](#图像渲染器)
	5. [字体渲染器](#字体渲染器)
	6. [发射粒子系统](#发射粒子系统)
	7. [毛发粒子系统](#毛发粒子系统)
	8. [海洋](#海洋)
	9. [精灵](#精灵)
	10. [SpriteFont](#spritefont)
	11. [GPUSortLib](#gpusortlib)
	12. [GPUBVH](#gpubvh)
4. [GUI](#gui)
	1. [GUI](#gui)
	2. [Widget](#widget)
	3. [Button](#button)
	4. [Label](#label)
	5. [TextInputField](#textinputfield)
	6. [Slider](#slider)
	7. [CheckBox](#checkbox)
	8. [ComboBox](#combobox)
	9. [Window](#window)
	10. [ColorPicker](#colorpicker)
	11. [TreeList](#treelist)
5. [辅助工具](#辅助工具)
	1. [Archive](#archive)
	2. [Color](#color)
	3. [FadeManager](#fademanager)
	4. [Helper](#helper)
	5. [Primitive](#primitive)
		1. [AABB](#aabb)
		2. [Sphere](#sphere)
		2. [Capsule](#capsule)
		3. [Ray](#ray)
		4. [Frustum](#frustum)
		5. [Hitbox2D](#hitbox2d)
	6. [wiMath](#wimath)
	7. [wiRandom](#wirandom)
	8. [wiRectPacker](#wirectpacker)
	9. [wiResourceManager](#wiresourcemanager)
	10. [wiSpinLock](#wispinlock)
	11. [wiArguments](#wiarguments)
	12. [wiTimer](#witimer)
	13. [wiVoxelGrid](#wivoxelgrid)
	14. [wiPathQuery](#wipathquery)
6. [输入](#输入)
7. [音频](#音频)
	1. [Sound](#sound)
	2. [SoundInstance](#soundinstance)
	3. [SoundInstance3D](#soundinstance3d)
	4. [SUBMIX_TYPE](#submix_type)
	5. [REVERB_PRESET](#reverb_preset)
8. [物理](#物理)
	1. [刚体物理](#刚体物理)
	2. [软体物理](#软体物理)
9. [网络](#网络)
	1. [Socket](#socket)
	2. [Connection](#connection)
10. [脚本](#脚本)
	1. [Lua](#lua)
	2. [Lua_Globals](#lua_globals)
	3. [Luna](#luna)
11. [工具](#工具)
	1. [Backlog](#backlog)
	2. [Profiler](#profiler)
12. [着色器](#着色器)
	1. [互操作](#互操作)
	2. [着色器编译器](#着色器编译器)

## 构建与链接
Wicked Engine 是一个静态库，可以被包含并链接到标准的 C++ 应用程序中。当你尝试为不同平台构建它时，会带来一些差异，因为它们有不同的编译器和设置。静态库的基础知识适用于所有平台：

1. 你必须构建 WickedEngine 本身
	- Windows：使用 Visual Studio 打开 WickedEngine.sln，并构建 WickedEngine_Windows 项目
	- Linux：在 Linux 上使用以下命令构建解决方案：

确保在 Linux 上已安装依赖项：
```bash
sudo apt update
sudo apt install libsdl2-dev
sudo apt install build-essential
```
要在 Linux 上构建引擎，请使用 `cmake` 然后 `make`：
```bash
mkdir build
cd build
cmake ..
make
```

2. 在应用程序的构建系统中，将 `$(SolutionDir)WickedEngine` 文件夹设置为"附加包含目录"（例如，对我来说它解析为：`C:\PROJECTS\WickedEngine\WickedEngine`）
3. 在应用程序的构建系统中，将 `$(SolutionDir)BUILD/$(Platform)/$(Configuration)` 设置为"附加库目录"（例如，对我来说它在 Debug x64 配置下解析为：`C:\PROJECTS\WickedEngine\BUILD\x64\Debug`）
4. 在你的 C++ 应用程序代码中使用 `#include "WickedEngine.h`
5. 验证你的应用程序能正确编译并链接到 Wicked Engine。
6. 如果成功，请继续阅读本指南的 [Application 初始化](#application) 部分

如果你遇到问题，请查看 Samples/Template 项目，它们设置了使用 Wicked Engine 的简单应用程序及其配置方式。

Xbox、PlayStation：WickedEngine.sln 必须像 Windows 一样使用 Visual Studio，但需要控制台扩展文件和目前保密的额外说明，未来可能会提供。

## 基本运行流程
Wicked Engine 操作的一般流程如下：

- main.cpp：你的入口点，包含所有平台特定功能
	- `wi::Application::SetWindow()` 被调用一次，传入操作系统特定的窗口句柄
	- `wi::Application.Run()` 在无限循环中被调用，每次调用是一"帧"
		- `wi::Application::Initialize()` 如果之前未被调用过，则调用一次
			- `wi::initializer::InitializeComponentsAsync()` 将被调用以在后台初始化所有引擎系统
		- `wi::Application::Update()` 每帧被调用
			- `wi::input::Update()` 被调用以读取输入
			- 等待 `update()` 的 lua 脚本协程被恢复
			- 如果 Application 上激活了任何 RenderPath，则每帧调用 `wi::RenderPath::Update()`
				- 如果 RenderPath 是 RenderPath3D，则每帧调用 wi::scene::Scene::Update()
		- `wi::Application::Render()` 每帧被调用
			- 等待 `render()` 的 lua 脚本协程被恢复
			- 如果 Application 上激活了任何 RenderPath，则每帧调用 wi::RenderPath::Render()
				- 使用多个 CPU 线程执行复杂的离屏渲染逻辑（主要使用 `wi::renderer` 命名空间中的函数）
		- `wi::Application::Compose()` 每帧被调用
			- 如果 Application 上激活了任何 RenderPath，则每帧调用 `wi::RenderPath::Compose()`
				- 在主线程上直接向显示（交换链）执行简单渲染逻辑
			- 如果启用（infoDisplay），Application 会在最顶部渲染一些信息文本，如版本、FPS 等
		- 在主线程上提交所有 GPU 工作（`GraphicsDevice::SubmitCommandLists()`）

## 高层接口
高层接口由构成 Wicked Engine 一般流程的类组成，允许通过自定义功能扩展引擎。这通常通过重写类来完成。使用 C++ 编码时不一定要使用高层接口，但它们提供了由 Wicked Engine 维护的完整简单运行时逻辑。

### Application
[[头文件]](../../WickedEngine/wiApplication.h) [[源文件]](../../WickedEngine/wiApplication.cpp)
这是主要的运行时组件，具有每帧调用的 `Run()` 函数。它应该被包含在应用程序入口点中，同时在无限循环中调用 Run()。Application 设计用于处理简单的游戏功能，可以切换到带有淡入淡出效果的不同游戏屏幕，并渲染到单个显示器。

要使用应用程序，用户至少应通过 `SetWindow()` 设置要渲染到的操作系统窗口，为其提供操作系统特定的窗口句柄。这将是应用程序绘制其内容的主窗口。

如果你在 RenderPath 之外使用引擎功能（例如在主函数中），还建议调用应用程序的 `Initialize()`。这将立即启动引擎初始化，而不是在第一次调用 `Run()` 时启动。在调用 `application.Initialize()` 之前使用引擎功能可能是未定义行为。如果你只在应用程序的 Update() 和其他可重写函数内使用引擎功能，则可确保在有效时运行。

最小应用程序初始化示例：

```cpp
Application app;
app.SetWindow(hWnd); // 提供操作系统相关的窗口句柄
while(true)
{
	app.Run(); // app.Initialize() 将在此处被调用，在此之前不要使用引擎功能。
}
```

上面的示例足以依赖在 startup.lua 文件中执行操作，如果该文件存在，将在适当的时间被执行。

使用扩展 C++ 类的最小应用程序初始化示例：

```cpp
class Game : public Application
{
	virtual ~Game() = default; // 在 C++ 中，建议始终将用于继承的类析构函数设为虚函数

	void Update(float deltatime) override // 重写 Application 的 Update 函数
	{
		Application::Update(deltatime);
		// 你的每应用程序更新逻辑可以放在这里
	}
}
Game game;
game.SetWindow(hWnd);
while(true)
{
	game.Run();
}
```

应用程序初始化并立即使用某些引擎功能的示例：

```cpp
Application app;
app.SetWindow(hWnd);
app.Initialize(); // 在使用引擎功能 LoadModel 之前，application.Initialize() 将确保所有引擎系统初始化都已启动。大多数功能在后台初始化运行时可以安全使用...
LoadModel("something.wiscene");
while(true)
{
	app.Run();
}
```

初始化应用程序并阻塞直到整个引擎初始化完成的示例：

```cpp
Application app;
app.SetWindow(hWnd);
app.Initialize(); // 这会立即返回，但引擎子系统开始在后台初始化...
wi::initializer::WaitForInitializationsToFinish(); // 阻塞直到所有引擎子系统就绪。如果在 Run() 之前调用，则不会显示初始化屏幕。
while(true)
{
	app.Run();
}
```

`Application` 有许多用户不一定感兴趣的用途。最重要的部分是它管理 `RenderPath`。一次只能有一个活动的 `RenderPath`，它将每帧被更新并渲染到屏幕。然而，由于 RenderPath 是高度可定制的类，在 RenderPath 内可以做什么没有限制，例如如果需要可以支持多个并发 RenderPath。RenderPath 可以通过淡出屏幕轻松切换。加载屏幕可以作为活动的 Renderpath 激活，如果需要，它将加载并切换到另一个 RenderPath。RenderPath 可以通过 `Application::ActivatePath()` 函数简单地激活，当使用 `fadeSeconds` 和 `fadeColor` 参数时，也会执行淡出。<br/>
`Application` 在运行时每帧执行以下操作：<br/>
1. FixedUpdate() <br/>
为活动的 RenderPath 调用 FixedUpdate，并唤醒等待 fixedupdate() 的脚本。调用频率由 `Application::setTargetFrameRate(float framespersecond)` 决定。默认情况下（参数 = 60），FixedUpdate 每秒将被调用 60 次。
2. Update(float deltatime) <br/>
为活动的 RenderPath 调用 Update，并唤醒等待 update() 的脚本
3. Render() <br/>
为活动的 RenderPath 调用 Render，并唤醒等待 render() 的脚本
4. Compose()
为活动的 RenderPath 调用 Compose

注意：应用程序的 splash_screen 纹理可以在应用程序初始化之前创建，在这种情况下，在引擎初始化尚未完成时，此纹理将作为全屏图像显示（如有必要会裁剪）。如果在工作目录中找到 splash_screen.png 文件，也会自动创建 splash_screen 纹理。如果不使用启动画面，则在启动时将显示初始化日志屏幕。
警告：如果你自己用资源管理器加载启动画面，请注意在引擎尚未初始化时不会生成 mipmap。你可以使用 `Application::splash_screen_subresource` 通过 `GraphicsDevice::CreateSubresource()` 方法指定要用于图像的 mipmap。如果你使用默认的 splash_screen.png 文件，这将自动处理。

### RenderPath
[[头文件]](../../WickedEngine/wiRenderPath.h)
这是一个空基类，可以通过 `Application` 激活。它会根据需要调用其 Start()、Update()、FixedUpdate()、Render()、Compose()、Stop() 等函数。重写此类以执行自定义游戏玩法或渲染逻辑。RenderPath 继承自 [wiCanvas](#wicanvas)，当 RenderPath 被激活时以及处于活动状态时，画布属性将由 [Application](#application) 设置。<br/>
每帧执行函数的顺序：<br/>
1. PreUpdate() <br/>
这将在每帧中调用 Update() 的任何脚本之前被调用一次。
2. FixedUpdate() <br/>
这将以确定性的方式被调用，因此逻辑将在 `Application::setTargetFrameRate(float framespersecond)` 指定的频率上运行
3. Update(float deltatime) <br/>
这将在每帧中调用一次，并以秒为单位提供自上次 Update() 以来的经过时间作为参数
4. PostUpdate() <br/>
这将在每帧中调用 Update() 的任何脚本之后被调用一次。
5. Render() const <br/>
这将在每帧中调用一次。它是 const 的，所以不应修改状态。运行此函数时，未定义它在哪个线程上运行。这之中可以使用多个线程和作业系统。主要目的是在多个线程和命令列表中记录大量渲染命令。此时可以安全地从图形设备获取命令列表。
6. Compose(CommandList cmd) const <br/>
它在每帧中调用一次。它运行在作为参数接收的单个命令列表上。这些渲染命令将直接记录到该帧中最后提交的命令列表上。此时渲染目标是后缓冲区，因此渲染将发生在屏幕上。

除了每帧运行的函数外，RenderPath 还有以下函数：
1. Load() <br/> 
用于在 RenderPath 首次使用之前加载资源。它将由 [LoadingScreen](#loadingscreen) 调用以在后台加载资源。
2. Start() <br/>
当 RenderPath 被 `Application` 激活时，Start 将始终被调用
3. Stop() <br/>
当当前 RenderPath 是 `Application` 中的活动 RenderPath，但另一个被激活时，Stop 将始终被调用。

### RenderPath2D
[[头文件]](../../WickedEngine/wiRenderPath2D.h) [[源文件]](../../WickedEngine/wiRenderPath2D.cpp)
能够在 Render() 函数中处理到离屏缓冲区的 2D 渲染，或仅在 Compose() 函数中处理到屏幕的渲染。它具有一些功能，可以将 wiSprite 和 wiSpriteFont 渲染到渲染层，并与 3D 渲染场景进行模板化。它有一个 [GUI](#gui)，如果添加了任何元素，会自动更新和渲染。

### RenderPath3D
[[头文件]](../../WickedEngine/wiRenderPath3D.h) [[源文件]](../../WickedEngine/wiRenderPath3D.cpp)
用于实现 3D 渲染路径的基类。它还支持 Renderpath2D 的所有功能。

后处理链也在这里实现。这意味着后处理的顺序和它们使用的资源在此定义，但较低级别的单个后处理渲染作为核心引擎功能在 `wi::renderer` 中实现。在 [wi::renderer 部分](#后处理) 中阅读更多关于后处理实现的信息。

后处理链在 `RenderPath3D::RenderPostprocessChain()` 函数中实现，分为多个部分：
- HDR<br/>
这些使用 HDR 场景渲染目标，它们发生在色调映射之前。例如：时间抗锯齿、运动模糊、景深
- LDR<br/>
这些在色调映射之后运行。例如：颜色分级、FXAA、色差。最后一个 LDR 后处理结果将在 `Compose()` 函数中输出到后缓冲区。
- 其他<br/>
这些根据渲染路径在更具体的位置运行。例如：SSR、SSAO、卡通描边

HDR 和 LDR 后处理链使用"乒乓"技术，这意味着当第一个后处理消耗 texture1 并生成 texture2 时，下一个后处理将消耗 texture2 并生成 texture1，直到所有后处理都渲染完成。

### RenderPath3D_PathTracing
[[头文件]](../../WickedEngine/wiRenderPath3D_PathTracing.h) [[源文件]](../../WickedEngine/wiRenderPath3D_PathTracing.cpp)
实现基于计算着色器的路径追踪解决方案。在静态场景中，渲染将收敛到真实值。当场景中某些内容发生变化（某物移动，或材质改变等），收敛将从头开始。光线追踪在 [wi::renderer](#wi::renderer) 和多个[着色器](#着色器)中实现。光线追踪可在支持计算着色器的任何 GPU 上使用。

#### 降噪器
要为路径追踪图像启用降噪，你可以使用 [Open Image Denoise 库](https://github.com/OpenImageDenoise/oidn)。要启用此功能，引擎将尝试包含 "WickedEngine/OpenImageDenoise/oidn.hpp" 文件。如果能包含此文件，它将尝试与 OpenImageDenoise.lib 和 tbb.lib 以及 OpenImageDenoise 发行版中提供的任何其他库链接。这些库应位于 `$(SolutionDir)BUILD\$(Platform)\$(Configuration)` 路径中，例如：`C:/PROJECTS/WickedEngine/BUILD/x64/Release`。还需要在 exe 附近提供 OpenImageDenoise.dll 和 tbb.dll 以及任何其他 dll 才能正确启动应用程序，例如：`C:\PROJECTS\WickedEngine\BUILD\x64\Release\Editor_Windows`。如果你满足这些步骤，在重新构建引擎后，当路径追踪器达到目标样本数或光照贴图烘焙停止时，降噪器将自动工作。

### LoadingScreen
[[头文件]](../../WickedEngine/wiLoadingScreen.h) [[源文件]](../../WickedEngine/wiLoadingScreen.cpp)
LoadingScreen 是一个示例 RenderPath，可用作应用程序的即插即用加载屏幕。它被设计为在资源加载期间显示的简单 2D 屏幕。你可以使用 `addLoadingFunction()` 添加通用任务，或使用 `addLoadingComponent()` 加载另一个 `RenderPath`。你可以通过 `onFinished()` 添加任务来指定加载完成后将调用的内容。你可以使用 `getProgress()` 函数查询加载进度，该函数以 0-100 范围内的整数形式返回加载百分比。例如，你可以使用它来显示加载进度条。加载将在调用加载屏幕的 `Start()` 时开始，但通常你不需要自己调用此函数。当你使用 `Application` 类激活加载屏幕时，它会在适当时切换到加载屏幕并自动启动。这样你可以轻松实现加载屏幕的淡入淡出，因为 `Application` 的 `ActivatePath()` 只有一个用于淡入淡出持续时间的参数。

因为 `LoadingScreen` 是 `RenderPath2D`，所以直接将 `Scene` 加载到主场景中（使用 `LoadModel()`）是安全的，因为 `RenderPath2D` 完全不利用场景进行渲染。如果你使用自定义加载屏幕也执行带有场景的 3D 渲染，则应改为使用 `LoadModel()` 加载到单独的场景中，并在 `LoadingScreen::onFinished()` 回调中合并到主场景。

此 LoadingScreen 类的一个简单辅助功能是 `BackgroundMode` 设置。你可以轻松地为 LoadingScreen 设置背景纹理，该纹理将在加载期间作为全屏图像显示。为此，你至少应指定 `LoadingScreen::bacgroundTexture` 资源，你可以使用 `wi::resourcemanager::Load()` 从资源文件中加载它。你可以通过 `LoadingScreen::background_mode` 设置此图像的 `BackgroundMode`，模式如下：
- Fill：填充整个屏幕，如果纵横比不匹配，将裁剪图像的部分（默认）
- Fit：将图像完全放入屏幕内，如果纵横比不匹配，将在屏幕上产生黑边
- Stretch：填充整个屏幕，并根据需要拉伸图像

如果你想在 LoadingScreen 上渲染其他内容，你也可以重写 RenderPath2D 方法，如 Render() 或 Compose()，并为自己实现自定义渲染。

## 系统
你可以在解决方案的 ENGINE/System 筛选器下找到更多关于实体-组件系统和其他引擎级系统的信息。
### 实体-组件系统
[[头文件]](../../WickedEngine/wiECS.h)

#### ComponentManager
组件管理器负责将数据（组件）绑定到实体（标识符）。组件可以是包含实体数据的 C++ 结构体。它支持此数据的序列化，如果使用此功能，则组件结构体必须具有 Serialize() 函数。否则，组件可以是任何可移动的 C++ 结构体。

#### Entity
实体是一个标识符（数字），可以通过 ComponentManager 容器引用组件。如果实体存在，则它始终有效。实体不一定需要有任何组件。如果有一个 ComponentManager 具有与同一实体关联的组件，则实体具有该组件。

#### 使用实体-组件系统
要使用实体-组件系统，你必须使用 ComponentManager<T> 来存储 T 类型的组件，其中 T 是某种 C++ 结构体类型。要将组件绑定到实体，应遵循此过程：

```cpp
struct MyComponent
{
	float3 position;
	float speed;
};
ComponentManager<MyComponent> components; // 创建组件管理器
Entity entity = CreateEntity(); // 创建新实体 ID
MyComponent& component = components.Create(entity); // 创建组件并将其绑定到实体
```

当你创建新组件时，它将被添加到数组的末尾，在连续的内存分配中。ComponentManager 可以高效地索引和迭代：

```cpp
for(size_t i = 0; i < components.GetCount(); ++i)
{
	MyComponent& component = components[i];
	Entity entity = components.GetEntity(i);
}
```

你可以看到，通过相同的索引，我们可以同时遍历组件和实体。当你想逐一遍历所有内容时，这很有用。但当你想为实体查询组件但不知道其索引时，这并不有用。当组件被移除时，索引可能会改变，因此你通常不能依赖自己记住实体的索引。然而，组件管理器确实在内部管理此信息。要为给定实体查询组件，请使用 GetComponent() 函数：

```cpp
MyComponent* component = components.GetComponent(entity);
if(component != nullptr) // 检查是否为 null，如果实体不存在组件则可能返回 null
{
	// 使用组件
}
```

你还可以获取实体在组件管理器中的索引：

```cpp
size_t index = components.GetIndex(entity);
if(index != INVALID_INDEX) // 检查是否有效。如果无效，则返回的索引将是 64 位 uint 的最大值
{
	MyComponent& component = components[index];
}
```

使用实体 ID 作为数组操作符是无效的：

```cpp
// 无效！结果将是未定义的（可能是有效组件，或越界崩溃）
MyComponent& component = components[entity];
```

一个有用的模式是将大型组件管理器的迭代卸载到作业系统，以并行化工作：

```cpp
wi::jobsystem::context ctx;
wi::jobsystem::Dispatch(ctx, (uint32_t)components.GetCount(), 64, [&](wi::jobsystem::JobArgs args){
	MyComponent& component = components[args.jobIndex];
	Entity entity = components.GetEntity(args.jobIndex);
	// 执行操作...
});
// 可选地，在此处执行不相关的操作...
wi::jobsystem::Wait(ctx); // 等待 Dispatch 完成
```
在此示例中，每个实体/组件将由一个作业迭代，64 批作业将作为一组在一个线程上执行。在迭代大型组件管理器时，这可以大大提高性能。

你必须注意的一件事是组件管理器的指针失效。任何时候使用实体 ID 都是安全的，但使用指针或索引更快。然而，随着组件的添加或移除，这些可能会改变。当移除组件时，你必须注意索引和指针失效，因为组件的顺序可能会在那里改变（组件管理器始终保持密集，没有空洞）。添加/创建组件时，指针可能会偶尔失效，就像例如 std::vector 一样，因为可能会发生内存重新分配以保持一切连续。这可能导致意外后果：

```cpp
MyComponent& component1 = components[0];
MyComponent& component2 = components.Create(CreateEntity()); // 这里 component1 引用/指针可能失效
component1.speed = 10; // 指针失效风险！
```
在上面的示例中，在仍然要使用对第一个元素的引用时创建了新组件，如果在创建 component2 时内存被重新分配，这可能导致崩溃。正确的解决方案是先创建所有组件，然后在所有创建完成后使用它们。或者在创建发生后使用 GetComponent(entity) 重新查询组件指针。

引擎的 Scene 结构本质上是 ComponentManager 的集合，让你以相同的方式访问场景中的所有内容。

### 场景系统
[[头文件]](../../WickedEngine/wiScene.h) [[源文件]](../../WickedEngine/wiScene.cpp)
使用实体-组件系统的逻辑场景表示
- GetScene <br/>
返回全局场景实例。这是需要单一场景的简单应用程序的便利功能。RenderPath3D 默认将使用全局场景，但如果需要可以设置为自定义场景。
- LoadModel() <br/>
这有两种形式。一种是立即加载到全局场景。另一种加载到自定义场景，这对于单独管理内容很有用。此函数将返回表示场景根变换的 Entity - 如果 attached 参数为 true，否则它将返回 INVALID_ENTITY 并且不会创建根变换。
- LoadModel2() <br/>
这是 LoadModel 的替代用法，它允许你将根实体 ID 作为参数给出。除此之外，它的工作方式与 LoadModel() 相同，只是附件将附加到你指定的根实体。
- Intersects(Ray/Capsule/Sphere, filterMask, layerMask, lod) <br/>
与场景实体和图元的相交函数。你可以指定各种设置来筛选相交。filterMask 允许你指定引擎定义的类型枚举位掩码组合，因此你可以选择与对象和/或碰撞器以及各种规范相交。layerMask 允许你使用层位筛选相交，其中参数和实体层的二进制 OR 将决定活动实体。lod 参数允许你强制网格使用特定 lod 级别。
- Pick <br/>
允许使用 RAY 拾取最近的对象（最近射线相交点到射线原点的命中）。用户可以提供自定义场景或 layermask 来筛选要检查的对象。
- SceneIntersectSphere <br/>
与所有对象执行球体相交，并立即返回第一个发生的相交。结果包含入射法线、穿透深度 和接触对象实体 ID。
- SceneIntersectCapsule <br/>
与所有对象执行胶囊相交，并立即返回第一个发生的相交。结果包含入射法线、穿透深度 和接触对象实体 ID。

下面你将找到构成场景的结构。这些旨在成为简单的结构，将保存在 [ComponentManager](#componentmanager) 中。保持这些结构体大小最小，以便在迭代大量组件时高效使用缓存。

<b>关于 bool 的说明：</b> 在 C++ 结构体中使用 bool 是低效的，因为它们在内存中占用比所需更多的空间。相反，将在每个组件中使用位掩码，可以在每个位中存储最多 32 个 bool 值。这也使添加 bool 标志变得更容易，不必担心序列化它们，因为位域本身已经序列化（但标志的顺序绝不能更改，否则需要通过序列化版本控制处理可能的副作用！）。C++ 枚举在代码中用于管理这些 bool 标志，存储这些的位掩码始终称为 `uint32_t _flags;` 例如：

```cpp
enum FLAGS
{
	EMPTY = 0, // 始终将 empty 作为第一个标志（值为零）
	RENDERABLE = 1 << 0,
	DOUBLE_SIDED = 1 << 1,
	DYNAMIC = 1 << 2,
};
uint32_t _flags = EMPTY; // 默认值通常为 EMPTY，表示未设置任何标志

// 如何查询"双面"标志：
bool IsDoubleSided() const { return _flags & DOUBLE_SIDED; }

// 如何设置"双面"标志
void SetDoubleSided(bool value) { if (value) { _flags |= DOUBLE_SIDED; } else { _flags &= ~DOUBLE_SIDED; } }
```

不为组件实现构造函数和析构函数是良好的做法。在可能的情况下，应优先在声明中初始化值。如果定义了析构函数，则还需要为与 [ComponentManager](#componentmanager) 的兼容性定义移动构造函数等，因此应优先使用默认构造函数和析构函数。成员对象应能隐式析构自身。如果需要在组件中存储管理对象生命周期的指针，可以使用 std::unique_ptr 或 wi::allocator::shared_ptr，它们将被隐式析构。

#### NameComponent
[[头文件]](../../WickedEngine/wiScene.h) [[源文件]](../../WickedEngine/wiScene.cpp)
用于以人类可读的名称标识实体的字符串。

#### LayerComponent
[[头文件]](../../WickedEngine/wiScene.h) [[源文件]](../../WickedEngine/wiScene.cpp)
可用于筛选实体的位掩码。根据实体具有的其他组件，层将被不同系统使用，例如用于确定可见性、筛选碰撞或拾取。
位掩码为 0 将使实体在大多数系统中处于非活动状态。
低 8 位将被光线追踪用作实例的实例包含掩码（ObjectComponent、EmittedParticle、HairParticle..）

#### TransformComponent
[[头文件]](../../WickedEngine/wiScene_Components.h) [[源文件]](../../WickedEngine/wiScene_Components.cpp)
3D 空间中的方向，支持对其自身进行各种常见操作。

#### PreviousFrameTransformComponent
[[头文件]](../../WickedEngine/wiScene_Components.h) [[源文件]](../../WickedEngine/wiScene_Components.cpp)
上一帧的绝对方向（矩阵）。

#### HierarchyComponent
[[头文件]](../../WickedEngine/wiScene_Components.h) [[源文件]](../../WickedEngine/wiScene_Components.cpp)
实体可以通过具有此组件成为变换层次结构的一部分。某些其他属性也可以继承，例如层位掩码。如果实体有父级，则它具有 HierarchyComponent，否则它不是层次结构的一部分。

#### MaterialComponent
[[头文件]](../../WickedEngine/wiScene_Components.h) [[源文件]](../../WickedEngine/wiScene_Components.cpp)
定义材质的几个属性，如颜色、纹理等...

#### MeshComponent
[[头文件]](../../WickedEngine/wiScene_Components.h) [[源文件]](../../WickedEngine/wiScene_Components.cpp)
网格是三角形的数组。网格可以有多个部分，称为 MeshSubset。每个 MeshSubset 都有一个材质，并使用网格的三角形范围。这也可以有用于渲染的 GPU 常驻数据。

#### ImpostorComponent
[[头文件]](../../WickedEngine/wiScene_Components.h) [[源文件]](../../WickedEngine/wiScene_Components.cpp)
支持高效地多次渲染同一网格（但作为近似，如公告板剪裁）。例如，当网格不重要但有大量副本时，可以将其渲染为 impostor。

#### ObjectComponent
[[头文件]](../../WickedEngine/wiScene_Components.h) [[源文件]](../../WickedEngine/wiScene_Components.cpp)
ObjectComponent 是在 3D 世界中具有物理位置的网格实例。多个 ObjectComponent 可以具有相同的网格，在这种情况下，网格将被高效地多次渲染。预期具有 ObjectComponent 的实体也具有 TransformComponent 和 [AABB](#aabb)（轴对齐边界框）组件。

#### RigidBodyPhysicsComponent
[[头文件]](../../WickedEngine/wiScene_Components.h) [[源文件]](../../WickedEngine/wiScene_Components.cpp)
存储刚体物理模拟所需的属性和物理引擎内部使用的句柄。

#### SoftBodyPhysicsComponent
[[头文件]](../../WickedEngine/wiScene_Components.h) [[源文件]](../../WickedEngine/wiScene_Components.cpp)
存储软体物理模拟所需的属性和物理引擎内部使用的句柄。

#### ArmatureComponent
[[头文件]](../../WickedEngine/wiScene_Components.h) [[源文件]](../../WickedEngine/wiScene_Components.cpp)
用于网格蒙皮变形的骨架。

#### LightComponent
[[头文件]](../../WickedEngine/wiScene_Components.h) [[源文件]](../../WickedEngine/wiScene_Components.cpp)
场景中可以在黑暗中发光的光。预期具有 LightComponent 的实体也具有 TransformComponent 和 [AABB](#aabb)（轴对齐边界框）组件。

#### CameraComponent
[[头文件]](../../WickedEngine/wiScene_Components.h) [[源文件]](../../WickedEngine/wiScene_Components.cpp)

#### EnvironmentProbeComponent
[[头文件]](../../WickedEngine/wiScene_Components.h) [[源文件]](../../WickedEngine/wiScene_Components.cpp)
预期具有 EnvironmentProbeComponent 的实体也具有 TransformComponent 和 [AABB](#aabb)（轴对齐边界框）组件。

#### ForceFieldComponent
[[头文件]](../../WickedEngine/wiScene_Components.h) [[源文件]](../../WickedEngine/wiScene_Components.cpp)

#### DecalComponent
[[头文件]](../../WickedEngine/wiScene_Components.h) [[源文件]](../../WickedEngine/wiScene_Components.cpp)
预期具有 DecalComponent 的实体也具有 TransformComponent 和 [AABB](#aabb)（轴对齐边界框）组件。

#### AnimationDataComponent
[[头文件]](../../WickedEngine/wiScene_Components.h) [[源文件]](../../WickedEngine/wiScene_Components.cpp)

#### AnimationComponent
[[头文件]](../../WickedEngine/wiScene_Components.h) [[源文件]](../../WickedEngine/wiScene_Components.cpp)

#### WeatherComponent
[[头文件]](../../WickedEngine/wiScene_Components.h) [[源文件]](../../WickedEngine/wiScene_Components.cpp)

#### SoundComponent
[[头文件]](../../WickedEngine/wiScene_Components.h) [[源文件]](../../WickedEngine/wiScene_Components.cpp)
持有 Sound 和 SoundInstance，可以通过 TransformComponent 放置到场景中。如果它具有 TransformComponent，则可以有 3D 音频效果。

#### InverseKinematicsComponent
[[头文件]](../../WickedEngine/wiScene_Components.h) [[源文件]](../../WickedEngine/wiScene_Components.cpp)
如果实体具有 `InverseKinematicComponent`（IK），并且是变换层次结构的一部分（同时具有 [TransformComponent](#transformcomponent) 和 [HierarchyComponent](#hierarchycomponent)），则它可以被定位到另一个 [TransformComponent](#transformcomponent)。父变换将按顺序计算，以使 IK 在可能的情况下到达目标。父变换将仅旋转。例如，如果手试图触及物体，手和肩膀将相应移动以让手到达。
可以指定 `chain_length` 让 IK 系统知道应计算多少父级。它可以大于实际链长度，在这种情况下，模拟步数不会超过层次结构链的长度。
可以指定 `iteration_count` 以提高计算的精度。
如果在受影响的实体上也播放动画，IK 系统将覆盖动画。

#### SpringComponent
[[头文件]](../../WickedEngine/wiScene_Components.h) [[源文件]](../../WickedEngine/wiScene_Components.cpp)
实体可以具有 `SpringComponent` 以编程方式实现"摇晃"或"柔软"动画效果。如果变换由动画系统更改或以任何其他方式更改，效果将自动工作。参数 `stiffness` 指定变换尝试返回其初始位置的速度。参数 `damping` 指定变换回到静止位置的速度。`wind_affection` 参数指定全局风对弹簧的影响程度。

#### ColiderComponent
[[头文件]](../../WickedEngine/wiScene_Components.h) [[源文件]](../../WickedEngine/wiScene_Components.cpp)
碰撞器组件将指定用于简单假物理模拟的碰撞器形状。它将影响弹簧和 GPU 粒子效果。

#### ScriptComponent
[[头文件]](../../WickedEngine/wiScene_Components.h) [[源文件]](../../WickedEngine/wiScene_Components.cpp)
ScriptComponent 可以引用 lua 脚本并每帧运行它，同时还向脚本提供一些附加数据，如本地 GetEntity() 函数。脚本可以编写为使用其唯一的 GetEntity() 函数引用附加组件数据。ScriptComponent 还可以调用其他脚本，这可用于在一个实体上实现多个脚本。

#### Scene
[[头文件]](../../WickedEngine/wiScene.h) [[源文件]](../../WickedEngine/wiScene.cpp)
场景是组件数组的集合。场景使用[作业系统](#作业系统)以高效的方式更新所有组件。它可以被序列化并高效地从磁盘保存/加载。
- Update(float deltatime) <br/>
此函数运行所有必需的系统来更新场景中包含的所有组件。

### 作业系统
[[头文件]](../../WickedEngine/wiJobSystem.h) [[源文件]](../../WickedEngine/wiJobSystem.cpp)
管理并发任务的执行
- context <br/>
定义可以同步的单一工作负载。它用于从作业中发布作业并正确等待完成。context 可以简单地在栈上创建，因为它是一个简单的原子计数器。
- Execute <br/>
这将为给定工作负载安排在单独线程上执行任务
- Dispatch <br/>
这将为给定工作负载安排在多个并行线程上执行任务
- Wait <br/>
此函数将阻塞，直到给定工作负载的所有作业都已完成。当前线程开始处理任何剩余待完成的工作。

### 初始化器
[[头文件]](../../WickedEngine/wiInitializer.h) [[源文件]](../../WickedEngine/wiInitializer.cpp)
以阻塞或异步方式初始化所有引擎系统。

### 平台
[[头文件]](../../WickedEngine/wiPlatform.h)
你可以获取原生平台特定功能。

### 事件处理器
[[头文件]](../../WickedEngine/wiEventHandler.h)
事件系统可用于执行系统范围的任务。任何系统都可以"订阅"事件，任何系统都可以"触发"事件。
- Subscribe <br/>
第一个参数是事件 ID。核心系统事件是负数。用户可以选择任何正数来创建自定义事件。
第二个参数是要执行的函数，带有 userdata 参数。userdata 参数可以保存用户希望的任何自定义数据。
返回值是 `wi::eventhandler::Handle` 类型。当此对象被销毁时，函数的事件订阅将被移除。
多个函数可以订阅单个事件 ID。
- FireEvent <br/>
第一个参数是事件 id，表示要调用哪些事件。
第二个参数将传递给订阅事件的 userdata 参数。
所有订阅指定事件 id 的事件将在调用 FireEvent 时立即运行。事件之间的执行顺序是它们被订阅的顺序。

### 画布
[[头文件]](../../WickedEngine/wiCanvas.h)
画布指定一个 DPI 感知的绘制区域。使用 GetLogical... 函数获取应用了 DPI 感知缩放因子的参数。使用 GetPhysical... 函数获取真实像素计数。


## 图形
下面将讨论与渲染图形相关的所有内容

### 图形 API
[[头文件]](../../WickedEngine/wiGraphics.h)
图形 API 包装器

#### GraphicsDevice
[[头文件]](../../WickedEngine/wiGraphicsDevice.h) [[源文件]](../../WickedEngine/wiGraphicsDevice.cpp)
这是图形 API 抽象的接口。它比图形 API 更高级，但这是引擎提供的最低级别的渲染命令。

##### 调试设备
创建图形设备时，可以以特殊调试模式创建以辅助开发。为此，用户可以在应用程序的命令行参数中指定 `debugdevice`，或在创建设备时将图形设备构造函数的 `debuglayer` 参数设置为 `true`。错误将发布到开发环境中的控制台输出窗口。

##### 创建资源
可以使用 `CreateTexture()`、`CreateBuffer()` 等函数创建相应的 GPU 资源。使用这些函数是线程安全的。资源不一定立即创建，而是在 GPU 想要使用它们时创建。如果出现任何错误（如传递给描述参数的错误参数），这些函数将立即返回 `false`，如果一切正确则返回 `true`。如果有错误，请使用[调试设备](#调试设备)功能获取附加信息。当将已创建的资源传递给这些函数时，它将被销毁，然后使用新提供的参数重新创建。

##### 销毁资源
资源在不再使用时将由图形设备自动销毁。

##### 工作提交
期望 `CommandList` 作为参数的渲染命令不会立即执行。它们将被记录到命令列表中，并在调用 `SubmitCommandLists()` 函数时提交给 GPU 执行。`CommandList` 是一个简单的句柄，将渲染命令关联到 CPU 执行时间线。`CommandList` 不是线程安全的，因此每个 `CommandList` 一次只能由一个 CPU 线程使用来记录命令。在多线程场景中，每个 CPU 线程应有自己的 `CommandList`。可以通过调用 `GraphicsDevice::BeginCommandList()` 从 [GraphicsDevice](#graphicsdevice) 检索 `CommandList`，它将返回一个从那时起可由调用线程自由使用的 `CommandList` 句柄。所有此类句柄将一直使用，直到调用 `SubmitCommandLists()` 或 `PresentEnd()`，其中发生 GPU 提交。命令列表将按使用 `GraphicsDevice::BeginCommandList()` 检索的顺序提交。提交顺序与实际 GPU 执行顺序相关。例如：

```cpp
CommandList cmd1 = device->BeginCommandList();
CommandList cmd2 = device->BeginCommandList();

Read_Shadowmaps(cmd2); // CPU 首先执行这些命令
Render_Shadowmaps(cmd1); // CPU 其次执行这些命令

//...

CommandList cmd_present = device->BeginCommandList();

device->SubmitCommandLists(cmd_present); // CPU 为 GPU 提交工作
// GPU 将首先执行 Render_Shadowmaps() 命令，然后执行 Read_Shadowmaps() 命令
```

当使用 `SubmitCommandLists()` 提交命令列表时，如果已提交但尚未完成的 GPU 工作过多，CPU 线程可能会被阻塞。在 `SubmitCommandLists()` 完成之前开始记录新命令列表是不合适的。

此外，`BeginCommandList()` 是线程安全的，因此如果命令列表之间的顺序不是要求（例如当它们产生相互独立的工作负载时），用户可以从工作线程调用它。

###### 异步计算
可以在计算队列上以 `CommandList` 粒度执行异步工作负载。`BeginCommandList()` 函数有一个可选的 `QUEUE_TYPE` 参数，可以指定在指定队列上执行命令列表。默认情况下，如果未指定此参数，工作将在主图形队列（`QUEUE_GRAPHICS`）上执行，与其他此类图形工作串行。如果图形设备或 API 不支持异步计算（如 DX11），则将假定使用 `QUEUE_GRAPHICS`。主图形队列可以执行图形和计算工作，但 `QUEUE_COMPUTE` 只能执行计算工作。两个队列也可以以 `CommandList` 粒度同步，使用 `WaitCommandList()` 函数。此函数在第一个参数命令列表之前插入依赖屏障，与第二个参数命令列表同步。例如：

```cpp
CommandList cmd0 = device->BeginCommandList(QUEUE_GRAPHICS);
CommandList cmd1 = device->BeginCommandList(QUEUE_COMPUTE);
device->WaitCommandList(cmd1, cmd0); // cmd1 等待 cmd0 完成
CommandList cmd2 = device->BeginCommandList(QUEUE_GRAPHICS); // cmd2 不等待，它与 cmd1 异步运行
CommandList cmd3 = device->BeginCommandList(QUEUE_GRAPHICS);
device->WaitCommandList(cmd3, cmd1); // cmd3 等待 cmd1 完成

device->SubmitCommandLists(); // 执行上述所有操作
```

`WaitCommandList()` 函数是 GPU 等待操作，因此不会阻塞 CPU 执行。此外，在同一队列上的两个 `CommandList` 之间不需要使用此函数，因为它们之间的同步是隐式的。

重要提示：`SHADER_RESOURCE` 状态不能在计算队列上使用。设备可以在发出 `Barrier()` 命令时将这些转换为 `SHADER_RESOURCE_COMPUTE`。但是，起始资源状态必须正确指定，因为那些无法转换。如果资源将在计算队列中使用，请考虑始终选择 `SHADER_RESOURCE_COMPUTE` 起始资源状态，并仅在资源将用于像素着色器之前将它们转换为常规 `SHADER_RESOURCE`。但是，带有计算命令的图形队列没有此限制。

##### 呈现到屏幕
要呈现到屏幕（操作系统窗口），首先使用 `CreateSwapChain()` 函数创建与窗口关联的 `SwapChain`。SwapChain 充当特殊类型的 [RenderPass](#渲染通道)，因此有一个 `BeginRenderPass()` 函数的重载，接受 SwapChain 参数而不是 RenderPass。只需使用此 `BeginRenderPass()` 和 `EndRenderPass()` 绘制到 SwapChain。最终呈现将在调用 `SubmitCommandLists()` 时发生。

###### HDR 显示
要向 HDR 显示器呈现内容，在创建 `SwapChain` 时将 `SwapChainDesc::allow_hdr` 设置为 `true`。同时，为 swapChain 选择可用于 HDR 内容的纹理格式。能够 HDR 的格式有：
- `R10G10B10A2_UNORM`，支持 `SRGB`（即 SDR）和 `HDR10_ST2084`（HDR10）色彩空间。
- `R16G16B16A16_FLOAT`，支持 `HDR_LINEAR` 色彩空间。

如果与 `SwapChain` 关联的显示器不支持 HDR 输出，将禁用 HDR，`SwapChain` 可以回退到支持的适当格式。要检查 `SwapChain` 的最终色彩空间，请调用 `GraphicsDevice::GetSwapChainColorSpace()` 函数，提供有效的 `SwapChain` 作为参数。该函数返回 `SwapChain` 的实际 `COLOR_SPACE`。
要检查与 `SwapChain` 关联的显示器是否支持 HDR，请调用 `GraphicsDevice::IsSwapChainSupportsHDR()` 函数，提供有效的 `SwapChain` 作为参数。这将返回显示器是否支持 HDR，而不管 `SwapChain` 的当前格式。

仅设置 HDR `SwapChain` 不足以渲染正确的 HDR 内容，因为必须非常小心地在线性色彩空间中混合元素，并在呈现之前正确转换到显示器的色彩空间。这是着色器的责任。

##### 资源绑定
资源绑定模型基于 DirectX 11。这意味着资源绑定到作为简单整数的槽号。

使用 HLSL 语法声明资源绑定点：
```cpp
Texture2D<float4> myTexture : register(t5);
```
必须指定槽号 `t5`，以避免 HLSL 编译器为其分配任意槽，并且可以从 CPU 访问。

用户可以从 CPU 端绑定纹理资源：
```cpp
Texture myTexture;
// 在纹理创建之后等：
device->BindResource(&myTexture, 5, cmd);
```

除此之外，像 `Texture` 这样的资源可以有不同的子资源，因此可以为 `BindResources()` 函数指定一个名为 `subresource` 的额外参数：
```cpp
Texture myTexture;
// 在纹理创建之后等：
device->BindResource(&myTexture, 5, cmd, 42);
```
默认情况下，`subresource` 参数为 `-1`，表示将绑定整个资源。有关子资源的更多信息，请参见[子资源](#子资源)部分。

关于如何绑定资源有不同的资源类型。这些槽具有彼此独立的绑定点，因此它们之间不会相互干扰。
- 着色器资源<br/>
这些是只读资源。如果 `GPUBuffer` 和 `Texture` 的描述中的 `BindFlags` 设置了 `SHADER_RESOURCE` 位，则可以将它们绑定为着色器资源。使用 `GraphicsDevice::BindResource()` 函数绑定单个着色器资源，或使用 `GraphicsDevice::BindResources()` 绑定一组着色器资源，从绑定槽开始占用多个槽。使用 `GraphicsDevice::UnbindResources()` 函数手动取消绑定多个着色器资源槽，这对于消除调试设备警告很有用。
- UAV<br/>
无序访问视图，即具有读写访问权限的资源。如果 `GPUBuffer` 和 `Texture` 的描述中的 `BindFlags` 设置了 `UNORDERED_ACCESS` 位，则可以将它们绑定为着色器资源。使用 `GraphicsDevice::BindUAV()` 函数绑定单个 UAV 资源，或使用 `GraphicsDevice::BindUAVs()` 绑定一组 UAV 资源，从绑定槽开始占用多个槽。使用 `GraphicsDevice::UnbindUAVs()` 函数手动取消绑定多个 UAV 槽，这对于消除调试设备警告很有用。
- 常量缓冲区<br/>
只有 `GPUBuffer` 可以设置为常量缓冲区，如果其描述中的 `BindFlags` 设置了 `CONSTANT_BUFFER` 位。当资源同时也是着色器资源或 UAV 或顶点缓冲区或索引缓冲区时，它不能同时是常量缓冲区。使用 `GraphicsDevice::BindConstantBuffer()` 函数绑定常量缓冲区。
- 采样器<br/>
只有 `Sampler` 可以绑定为采样器。使用 `GraphicsDevice::BindSampler()` 函数绑定采样器。

槽的最大值有一些限制，这些在 [Graphics device SharedInternals](../WickedEngine/wiGraphicsDevice_SharedInternals.h) 中定义为编译时常量。如果预定义槽不足，用户可以修改这些并重新编译引擎。这可能会略微影响性能。

备注：
- Vulkan 和 DX12 设备努力跨着色器阶段组合描述符，因此在某种程度上这些 API 不支持重叠描述符。例如，在顶点着色器中槽 0 (b0) 有常量缓冲区而在像素着色器中槽 0 (t0) 有 Texture2D 是可以的。但是，在顶点着色器槽 0 (t0) 有 StructuredBuffer 而在像素着色器槽 0 (t0) 有 Texture2D 将无法正常工作，因为它们中只有一个将绑定到管线状态。这是出于性能原因。
- 这种基于槽的绑定模型有 CPU 开销，必须牢记。避免绑定大量资源。应使用的最大槽号为：`BindConstantBuffer()` 为 14，`BindResource()` 为 16，`BindUAV()` 为 16，`BindSampler()` 为 8。当需要绑定多个资源时，考虑使用[无绑定模型](#无绑定资源)。

##### 无绑定资源

Wicked Engine 支持无绑定资源管理，这可以大大提高性能并消除资源绑定约束以提供极大的灵活性。

与此功能相关的函数：
- `GetDescriptorIndex()`：返回一个 `int`，用于在无绑定空间中标识资源。查询的资源可以是 `Sampler` 或 `GPUResource`。如果资源不可用（例如如果它未被创建），则函数返回 `-1`。**在这种情况下，着色器绝不能使用该资源，而是依赖动态分支来避免它，因为这将是未定义行为并可能导致 GPU 挂起**。否则，索引可以由着色器用于索引描述符堆。
- `PushConstants()`：这是一种在 GPU 上设置少量 32 位值的简单方法，可由声明了 `PUSHCONSTANT(name, type)` 块的着色器使用。每个管线（图形、计算或光线追踪）可以有一个推送常量块。推送常量将绑定到上次设置的管线，因此仅在绑定图形管线状态或计算着色器之后使用此函数。

着色器可以使用以下语法示例使用无绑定描述符：

```hlsl
Texture2D<float4> bindless_textures[] : register(t0, space5);
struct PushConstants
{
	uint materialIndex;
	int textureindex;
};
PUSHCONSTANT(push, PushConstants);
// ...
float4 color = bindless_textures[push.textureindex].Sample(sam, uv);
```

相应的数据可以从 CPU 这样提供：

```cpp
struct PushConstants
{
	uint materialIndex;
	int textureindex;
};
PushConstants push;
push.materialIndex = device->GetDescriptorIndex(materialCB, SRV);
push.textureindex = device->GetDescriptorIndex(texture, SRV);
device->PushConstants(&push, sizeof(push), cmd);
```

*注意：即使支持无绑定描述符，ConstantBuffer<T> 的描述符数组也可能被某些硬件/API（例如 Vulkan）以有限形式支持，因此不要过度依赖它。*

常规基于槽的绑定模型将与无绑定模型无缝配合工作。基于槽的绑定将始终隐式使用 `space0`，`space1` 及更大值应用于无绑定模型。目标是将空间号保持得尽可能低。

##### 子资源
像纹理这样的资源可以有不同的视图。例如，如果纹理包含多个 mip 级别，则每个 mip 级别可以视为具有一个 mip 级别的单独纹理，或者整个纹理可以视为具有多个 mip 级别的纹理。创建资源时，将创建查看整个资源的子资源。期望子资源参数的函数可以提供值 `-1`，表示整个资源。通常，此参数是可选的。

可以使用 `GraphicsDevice::CreateSubresource()` 函数创建其他子资源。该函数将返回一个 `int` 值，可用于引用创建的子资源视图。如果函数返回 `-1`，则子资源创建由于参数不正确而失败。请使用[调试设备](#调试设备)功能检查此情况下的错误。`CreateSubresource()` 函数的使用在设备上是线程安全的，但在资源上不是，因此一次只能有 1 个线程修改给定资源。

子资源索引在其创建所用的资源有效时有效。

##### 管线状态和着色器
`PipelineState` 用于定义图形管线状态，包括使用哪些着色器、哪种混合模式、光栅化器状态、输入布局、深度模板状态和图元拓扑，以及采样掩码。这些状态只能在单个 `GraphicsDevice::SetPipelineState()` 调用中原子地绑定。这不包括计算着色器，它们不参与图形管线状态，可以使用 `GraphicsDevice::BindComputeShader()` 方法单独绑定。

管线状态受着色器编译的影响。当管线状态首次在渲染通道内绑定时，将发生着色器编译。这是必需的，因为渲染目标格式是编译的必要信息，但它们不是管线状态描述的一部分。这样做是为了增加定义管线状态的灵活性。但是，与可以单独绑定状态子集（如 RasterizerDesc 或 BlendStateDesc）的 API 不同，状态分组在 CPU 时间方面更优，因为状态哈希仅在创建时为整个管线状态计算一次，而不是在每个单独状态的绑定时间。当开发人员可能忘记设置任何状态子集并且先前渲染通道的剩余状态不正确时，这种方法也不太容易出现用户错误。

着色器仍然需要以与 CreateTexture() 等类似的方式使用 `GraphicsDevice::CreateShader()` 创建。CreateShader() 函数需要一个 `wiGraphics::ShaderStage` 枚举值，该值将定义着色器类型：

- `MS`：网格着色器
- `AS`：放大着色器或任务着色器
- `VS`：顶点着色器
- `HS`：外壳着色器或曲面细分控制着色器
- `DS`：域着色器或曲面细分评估着色器
- `GS`：几何着色器
- `PS`：像素着色器
- `CS`：计算着色器
- `LIB`：库着色器

根据图形设备实现，着色器代码必须是不同格式。例如，DirectX 期望 DXIL 着色器，Vulkan 期望 SPIR-V 着色器。引擎可以使用[着色器编译器](#着色器编译器)将 HLSL 着色器源代码编译为 DXIL 或 SPIRV 格式。

注意：作为可选参数，`CreatePipelineState()` 函数还接受 `RenderPassInfo` 指针。如果提供此参数，则所有信息都将可用于管线创建立即发生。这意味着管线将在函数返回后立即处于最终可用状态，但这可能需要更长时间才能完成。如果未提供参数，则管线可以在稍后首次使用时渲染通道信息可用时创建。这可能具有更长的管线编译在意外时间发生的效果。但在这种情况下，如果在不同位置使用，管线也将与更多渲染通道类型兼容。

##### 渲染通道
渲染通道定义了 GPU 执行中的区域，其中一些渲染目标或深度缓冲区将被用于渲染。渲染目标和深度缓冲区定义为 `RenderPassImage`。`RenderPassImage` 具有指向纹理的指针，说明资源类型（`RENDERTARGET`、`DEPTH_STENCIL` 或 `RESOLVE`），说明[子资源](#子资源)索引、加载和存储操作，以及纹理的布局转换。

- `RENDERTARGET`：图像将用作（颜色）渲染目标。这些图像的顺序定义着色器颜色输出顺序。
- `DEPTH_STENCIL`：图像将用作深度（和/或模板）缓冲区。
- `RESOLVE`：图像将用作 MSAA 解析目标。解析源在同一渲染通道中的 `RENDERTARGET` 图像中选择，按它们声明的顺序。`RENDERTARGET` 和 `RESOLVE` 图像的声明顺序必须匹配，以正确推断解析操作的源和目标。
- `RESOLVE_DEPTH` 与 `RESOLVE` 相同，但用于深度模板。你还可以使用 `RenderPassImage::DepthResolveMode` 枚举指定 Min 或 Max 解析操作。此功能必须由 GPU 支持并由 `GraphicsDeviceCapability::DEPTH_RESOLVE_MIN_MAX` 和 `GraphicsDeviceCapability::STENCIL_RESOLVE_MIN_MAX`（如果图像也有模板）指示。

- 加载操作：<br/>
定义渲染通道开始时纹理内容的初始化方式。`LoadOp::LOAD` 表示将保留先前纹理内容。`LoadOp::CLEAR` 表示纹理的先前内容将丢失，而是使用纹理清除颜色填充纹理。`LoadOp::DONTCARE` 表示纹理内容未定义，因此仅当开发人员可以确保整个纹理将被渲染到并且不留任何区域为空（在这种情况下，纹理中将出现未定义结果）时才应使用此选项。
- 存储操作：<br/>
定义渲染通道结束后纹理内容的处理方式。`StoreOp::STORE` 表示内容将被保留。`StoreOp::DONTCARE` 表示内容不一定会被保留，它们仅在渲染通道持续时间内暂时有效，这可以在某些平台（特别是基于分块的渲染架构，如移动 GPU）上节省一些内存带宽。
- 布局转换：<br/>
定义 `layout_before`、`layout`（仅用于 `DEPTH_STENCIL`）和 `layout_after` 成员以执行作为渲染通道一部分的隐式转换，其工作方式类似于 [IMAGE_BARRIER](#gpu-屏障)，但可以更优。`layout_before` 说明资源的起始状态。资源将在渲染通道内从 `layout_before` 转换为 `layout`。`layout` 说明资源在渲染通道内如何被访问。对于 `DEPTH_STENCIL` 类型，它必须是 `DEPTHSTENCIL` 或 `DEPTHSTENCIL_READONLY`。对于 `RESOLVE` 类型，subpass_layout 没有意义，它是隐式定义的。在渲染通道结束时，资源将从 `layout` 转换为 `layout_after`。

注意：
- 当调用 `RenderPassBegin()` 时，必须在同一命令列表上调用 `RenderPassEnd()`，之后才能[提交](#工作提交)命令列表。
- 不允许在渲染通道内调用 `RenderPassBegin()`。
- 不允许在渲染通道内调用 `CopyResource()`、`CopyTexture()`、`CopyBuffer()`。
- 不允许在渲染通道内调用 `Dispatch()`、`DispatchIndirect()`、`DispatchMesh()`、`DispatchMeshIndirect()`、`DispatchRays()`。
- 不允许在渲染通道内调用 `UpdateBuffer()`。
- 不允许在渲染通道内调用 `Barrier()`。
- 不允许在渲染通道内调用 `ClearUAV()`。

##### GPU 屏障
`GPUBarrier` 可用于说明 GPU 工作负载之间的依赖关系。有不同类型的屏障：

- MEMORY_BARRIER <br/>
内存屏障用于等待 UAV 写入完成，换句话说，等待正在写入 UNORDERED_ACCESS 资源的着色器完成。`GPUBarrier::memory.resource` 成员是指向要等待的 GPUResource 的指针。如果为 nullptr，则屏障意味着"等待每个正在进行的 UAV 写入完成"。
- IMAGE_BARRIER <br/>
图像屏障说明[纹理](#纹理)的资源状态转换。最常见的用例例如是从 `RENDERTARGET` 转换为 `SHADER_RESOURCE`，这意味着将纹理作为渲染目标写入的 [RenderPass](#渲染通道) 必须在屏障之前完成，并且纹理可以在屏障之后用作只读着色器资源。还有其他情况可以使用 `GPUBarrier::image.layout_before` 和 `GPUBarrier::image.layout_after` 状态指示。`GPUBarrier::image.resource` 是指向将更改其状态的资源的指针。如果纹理的 `layout`（作为 TextureDesc 的一部分）不是 `SHADER_RESOURCE`，则在绑定为着色器资源之前必须将布局转换为 `SHADER_RESOURCE`。图像布局也可以使用 [RenderPass](#渲染通道) 转换，应优先于 `GPUBarrier` 使用。
- BUFFER_BARRIER <br/>
类似于 `IMAGE_BARRIER`，但用于 [GPU 缓冲区](#gpu-缓冲区)状态转换。

将屏障放在正确的位置非常重要；缺少屏障可能导致渲染结果损坏、崩溃和一般未定义行为。[调试层](#调试设备)将帮助检测错误和缺少的屏障。

##### 纹理
`Texture` 类型资源用于存储将由 GPU 高效采样或写入的图像。有许多纹理类型，如 `Texture1D`、`Texture2D`、`TextureCube`、`Texture3D` 等在[着色器](#着色器)中使用，对应于 CPU 上的简单 `Texture` 类型。使用 `GraphicsDevice::CreateTexture(const TextureDesc*, const SubresourceData*, Texture*)` 函数创建资源时将确定纹理类型。第一个参数是 `TextureDesc`，确定纹理资源的尺寸、大小、格式和其他属性。`SubresourceData` 用于初始化纹理内容，当不需要初始化纹理内容时（例如对于将渲染到的纹理），可以将其留为 `nullptr`。`Texture` 是将被初始化的纹理。

`SubresourceData` 用法：
- `SubresourceData` 参数指向 `SubresourceData` 结构体数组。数组大小由 `TextureDesc::ArraySize` * `TextureDesc::MipLevels` 确定，因此每个子资源一个结构体。
- `SubresourceData::pData` 指针应指向 CPU 上将上传到 GPU 的纹理内容。
- `SubresourceData::rowPitch` 成员表示从纹理的一行开头到下一行的距离（以字节为单位）。
系统内存间距仅用于 2D 和 3D 纹理数据，因为对于其他资源类型没有意义。在 `slicePitch` 成员中指定从 3D 纹理的一个 2D 切片的第一个像素到该纹理的下一个 2D 切片的第一个像素的距离。
- `SubresourcData::slicePitch` 成员表示从一个深度级别开头到下一个深度级别的距离（以字节为单位）。
系统内存切片间距仅用于 3D 纹理数据，因为对于其他资源类型没有意义。
- 有关更完整的信息，请参阅有关此主题的 [DirectX 11 文档](https://docs.microsoft.com/en-us/windows/win32/api/d3d11/ns-d3d11-d3d11_subresource_data)，应与之紧密匹配。

相关主题：[创建资源](#创建资源)、[销毁资源](#销毁资源)、[绑定资源](#资源绑定)、[子资源](#子资源)

##### GPU 缓冲区
`GPUBuffer` 类型资源用于存储将由 GPU 读取或写入的线性数据。有许多缓冲区类型，如结构化缓冲区、原始缓冲区、顶点缓冲区、索引缓冲区、类型化缓冲区等在[着色器](#着色器)中使用，对应于 CPU 上的简单 `GPUBuffer` 类型。使用 `GraphicsDevice::CreateBuffer(const GPUBufferDesc*, const void*, GPUBuffer*)` 函数创建缓冲区时将确定缓冲区类型。第一个参数是 `GPUBufferDesc`，确定纹理资源的尺寸、大小、格式和其他属性。`pInitialData` 用于初始化缓冲区内容，可以留为 `nullptr`。`GPUBuffer` 是将被初始化的缓冲区。

相关主题：[创建资源](#创建资源)、[销毁资源](#销毁资源)、[绑定资源](#资源绑定)、[子资源](#子资源)、[更新 GPU 缓冲区](#更新-gpu-缓冲区)

##### 更新 GPU 缓冲区
`GPUBuffer` 的 `Usage` 参数指定如何访问缓冲区内存。
- `DEFAULT`：缓冲区内存对 GPU 可见但对 CPU 不可见。这意味着它将获得最大的 GPU 性能，但需要特别注意写入缓冲区内容。GPU 可以从着色器或复制操作写入内存。你也可以使用 `UpdateBuffer()` 函数从 CPU 更新此类缓冲区（使用 GPU 复制）。
- `UPLOAD`：缓冲区可以由 CPU 写入并由 GPU 读取。一旦创建了这样的 `GPUBuffer`，其内存将持久映射以供 CPU 访问，可以通过 `GPUResource::mapped_data` 指针访问。它非常适合从 CPU 填充 `UPLOAD` 缓冲区，然后让 GPU 通过着色器或复制操作将其内容复制到 `DEFAULT` 缓冲区来更新 `DEFAULT` 缓冲区。
- `READBACK`：缓冲区可以由 GPU 写入并由 CPU 读取内容。创建后缓冲区内存将持久映射，并可通过 `GPUResource::mapped_data` 指针访问。

##### GPU 查询
`GPUQueryHeap` 可用于从 GPU 检索信息到 CPU。有不同的查询类型（`GpuQueryType` 枚举）：
- `TIMESTAMP` 用于向堆中指定的查询写入时间戳值。使用 `GraphicsDevice::QueryEnd()` 记录此类型。
- `OCCLUSION` 用于检索 `GraphicsDevice::QueryBegin()` 和 `GraphicsDevice::QueryEnd()` 之间绘制命令的深度测试通过的样本计数。
- `OCCLUSION_BINARY` 与 `OCCLUSION` 相同，但仅返回是否有任何样本通过深度测试。它可以比 `OCCLUSION` 更优。

`GPUQueryHeap` 设计为批量检索查询结果，而不是逐个检索，这可以更优地实现。但是，如果需要，仍然可以逐个检索查询。`GraphicsDevice::QueryResolve()` 函数将发出 GPU 操作，将查询结果写入 CPU 可见的堆。可以在 CPU 时间线上调用 `GraphicsDevice::QueryRead()` 函数批量读取已解析的查询数据。必须在 GPU 完成执行 `GraphicsDevice::QueryResolve()` 后读取查询，这通常在几帧延迟之后。

##### RayTracingAccelerationStructure
加速结构可以是底层或顶层，由描述结构的 `type` 字段决定。根据 `type`，在创建加速结构之前必须填写 `toplevel` 或 `bottomlevel` 成员。使用图形设备（`GraphicsDevice::CreateRaytracingAccelerationStructure()`）创建加速结构时，将分配足够的后备内存，但加速结构不会被构建。在 GPU 时间线上通过 `GraphicsDevice::BuildRaytracingAccelerationStructure()` 执行构建加速结构。要从头构建，将此函数的 `src` 参数留为 `nullptr`。要在不进行完全重建的情况下更新加速结构，请指定 `src` 参数。`src` 可以是同一加速结构，在这种情况下，更新将就地执行。要能够更新加速结构，它必须使用 `RaytracingAccelerationStructureDesc::FLAG_ALLOW_UPDATE` 标志创建。

##### RayTracingPipelineState
绑定光线追踪管线状态是分发光线追踪着色器所必需的。光线追踪管线状态持有着色器库和 hitgroup 定义的集合。它还声明有关管线最大资源使用的信息。

##### 可变速率着色
可变速率着色可用于降低着色质量，同时保持深度测试精度。着色率可以通过不同方式设置：

- `BindShadingRate()`：为以下绘制调用设置着色率。第一个参数是着色率，默认为 `RATE_1X1`（最佳质量）。增加的枚举值代表降低的着色率。
- 着色率图像：通过平铺纹理为屏幕设置着色率。纹理必须设置为 `RATE_SOURCE` 类型的 RenderPassAttachment。纹理必须使用 `R8_UINT` 格式。在每个像素中，纹理包含一个像素块（8x8、16x16 或 32x32）的着色率值。可以通过 `GetVariableRateShadingTileSize()` 查询块大小。纹理包含的着色率值不是来自 `ShadingRate` 枚举的原始值，但必须使用 `WriteShadingRateValue()` 函数将它们转换为所使用图形 API 的原生值。着色率纹理必须用计算着色器写入，并使用 [GPUBarrier](#gpu-屏障) 转换为 `RATE_SOURCE`，然后再使用 `BindShadingRateImage()` 设置。可以将 `nullptr` 设置为纹理，表示着色率不由纹理指定是有效的。
- 或者使用 `SV_ShadingRate` 系统值语义从顶点或几何着色器设置着色率。

最终着色率将从上述方法中使用适用于屏幕块的最大着色率（最不详细）确定。未来可能会考虑公开运算符以定义此值。

要阅读有关可变速率着色的更多信息，请参阅 [DirectX 规范。](https://microsoft.github.io/DirectX-Specs/d3d/VariableRateShading)


##### 视频解码
视频解码可用于在 GPU 上实时解码压缩视频比特流。目前仅支持 H264 格式。要解码视频，需要执行以下步骤：
- 在 `GPUBuffer` 中提供 H264 切片数据。切片数据偏移需要使用 `GraphcisDevice::GetVideoDecodeBitstreamAlignment()` 在缓冲区内对齐。比特流缓冲区目前需要是 `UPLOAD` 缓冲区。
- 创建 `VideoDecoder` 对象，同时提供从 H264 解析的适当参数，如分辨率、图片参数、序列参数。解码格式必须是 `Format::NV12`，这是一种多平面 YUV420 格式。
- 创建"解码图片缓冲区"（DPB），它是一个纹理数组，以原生视频格式存储参考和解码图像（目前仅支持 `Format::NV12`）。在 `misc_flags` 中指示它将用作 `ResourceMiscFlags::VIDEO_DECODE`。
- 运行 `GraphicsDevice::VideoDecode` 操作，提供正确的参数来解码单个视频帧。你有责任提供正确的 H264 参数和 DPB 图片索引。
- 你需要手动从 DPB 纹理读取（例如在着色器中），并根据需要将 YUV 格式解析为 RGB。

所有这些都在 [wi::video](../../WickedEngine/wiVideo.cpp) 实现中演示。


#### GraphicsDevice_DX11
DirectX11 接口已在 0.56 版本后移除

#### GraphicsDevice_DX12
[[头文件]](../../WickedEngine/wiGraphicsDevice_DX12.h) [[源文件]](../../WickedEngine/wiGraphicsDevice_DX12.cpp)
用于渲染接口的 DirectX12 实现

#### GraphicsDevice_Vulkan
[[头文件]](../../WickedEngine/wiGraphicsDevice_Vulkan.h) [[源文件]](../../WickedEngine/wiGraphicsDevice_Vulkan.cpp)
用于渲染接口的 Vulkan 实现


### 渲染器
[[头文件]](../../WickedEngine/wiRenderer.h) [[源文件]](../../WickedEngine/wiRenderer.cpp)
这是图形技术实现和绘制场景、阴影、后处理等功能的集合。它也是 GraphicsDevice 实例的管理器，并提供其他辅助函数从磁盘上的文件加载着色器。

除了大多数彼此独立的图形辅助函数外，渲染器还提供渲染场景的工具。这可以通过高级 DrawScene、DrawSky 等函数完成。这些函数本身不设置渲染通道或视口，但期望从外部设置它们。大多数其他渲染状态将在内部处理，如常量缓冲区、模板、混合状态等。请查看高级接口 RenderPath3D 实现中如何使用场景渲染函数（例如 [RenderPath3D_TiledForward.cpp](../WickedEngine/RenderPath3D_TiledForward.cpp)）

这里其他感兴趣的地方是实用图形函数，如 CopyTexture2D、GenerateMipChain 等，它们提供可定制的操作，如边框扩展模式、高斯 mipchain 生成以及图形 API 不支持的功能。

渲染器还托管后处理实现。这些函数是独立的，具有清晰的输入/输出参数。它们不应依赖外部的任何其他额外设置。

在下面更详细地阅读渲染器的不同功能：

#### DrawScene
从作为参数指定的相机视角渲染场景。仅渲染相机[视锥体](#frustum)内的对象。对象将从前到后排序。这是一种减少过度绘色的优化，因为对于不透明对象，只有最接近相机的像素将贡献到渲染图像。最前面像素后面的像素将被 GPU 使用深度缓冲区剔除，不进行渲染。排序通过 RenderQueue 在内部实现。RenderQueue 负责按距离和网格索引对对象进行排序，因此实例化渲染（将多个可绘制对象批量为一个绘制调用）和从前到后排序都可以协同工作。

`renderPass` 参数将指定我们使用哪种渲染通道，并指定着色器复杂度和渲染技术。
`cmd` 参数引用有效的 [CommandList](#工作提交)。
`flags` 参数可以包含各种修饰符，用于确定要渲染哪种对象或考虑哪种其他属性：

- `DRAWSCENE_OPAQUE`：将渲染不透明对象
- `DRAWSCENE_TRANSPARENT`：将渲染透明对象。对象将按从后到前排序，用于混合目的
- `DRAWSCENE_OCCLUSIONCULLING`：被遮挡的对象将不被渲染。可以使用 `wi::renderer::SetOcclusionCullingEnabled()` 全局开关[遮挡剔除](#遮挡剔除)
- `DRAWSCENE_TESSELLATION`：启用[曲面细分](#曲面细分)（如果硬件支持）。可以使用 `wi::renderer::SetTessellationEnabled()` 全局开关[曲面细分](#曲面细分)
- `DRAWSCENE_HAIRPARTICLE`：允许绘制毛发粒子
- `DRAWSCENE_IMPOSTOR`：允许绘制 impostor
- `DRAWSCENE_OCEAN`：允许绘制海洋
- `DRAWSCENE_SKIP_PLANAR_REFLECTION_OBJECTS`：不绘制渲染平面反射的对象。这是为了避免将反射器对象本身渲染到平面反射中，这可能产生完全被遮挡的反射。

#### 曲面细分
渲染对象时可以使用曲面细分。曲面细分需要 GPU 硬件功能，可以在渲染对象时动态启用顶点上的位移映射或平滑网格轮廓。当 [DrawScene](#drawscene) 的 `tessellation` 参数设置为 `true` 且 GPU 支持曲面细分功能时，将使用曲面细分。可以按 [MeshComponent](#meshcomponent) 的 `tessellationFactor` 参数指定曲面细分级别。曲面细分级别将根据距相机的距离进行调制，以便曲面细分因子将在更远的对象上淡出。更大的曲面细分因子意味着将生成更详细的几何体。

#### 遮挡剔除
遮挡剔除是一种确定哪些对象在相机内但完全在其他对象后面的技术，因此它们不会被渲染。深度缓冲区已经在 GPU 上执行遮挡剔除，但是，我们希望在将网格提交到 GPU 进行绘制之前执行此操作，因此本质上在 CPU 上执行遮挡剔除。这里使用混合方法，它使用先前渲染帧（由 GPU 渲染）的结果来确定对象在当前帧中是否可见。为此，我们首先将对象渲染到前一帧的深度缓冲区，并使用前一帧的相机矩阵，但是，使用对象的当前位置。实际上，出于性能原因，我们只渲染边界框而不是对象。渲染时使用遮挡查询，CPU 可以在稍后的帧中读取查询结果。我们跟踪对象不可见多少帧，如果它不可见一定数量，我们将从渲染中省略它。如果它稍后突然变为可见，我们立即再次启用渲染它。此技术意味着结果将滞后几帧（CPU 和 GPU 之间的延迟以及使用前一帧深度缓冲区的延迟）。这些在 `wi::renderer::OcclusionCulling_Render()` 和 `wi::renderer::OcclusionCulling_Read()` 函数中实现。

#### 阴影贴图
`DrawShadowmaps()` 函数将为相机[视锥体](#frustum)内每个活动的动态光渲染阴影贴图。有两种类型的阴影贴图，2D 和 Cube 阴影贴图。可使用的最大阴影贴图数通过调用 `SetShadowProps2D()` 或 `SetShadowPropsCube()` 函数设置，其中参数将指定最大阴影贴图数和分辨率。必须已为每个光分配阴影槽，因为这是渲染函数，不允许修改 [Scene](#scene) 和[光](#lightcomponent)的状态。阴影槽将在 `RenderPath3D` 每帧调用的 [UpdatePerFrameData()](#updateperframedata) 函数中设置。

#### UpdatePerFrameData
此函数为渲染准备场景。它必须每帧调用一次。它将修改 [Scene](#scene) 和其他与渲染相关的资源。它在 [Scene](#scene) 更新之后调用。它执行视锥体剔除和其他管理任务，例如将贴花矩形打包到图集中以及其他几件事。

#### UpdateRenderData
在 GPU 上开始渲染帧。这意味着启动 GPU 计算作业，如粒子模拟、纹理打包、排队的 mipmap 生成任务、更新每帧 GPU 缓冲区数据、动画顶点蒙皮等。

#### 光线追踪（硬件加速）
硬件加速光线追踪 API 可用，因此使用它的各种渲染器功能可用。如果硬件支持可用，`Scene` 将分配顶层加速结构，如果某些效果请求，网格将为自己分配底层加速结构。可以通过使用 `wi::scene::Scene::SetAccelerationStructureUpdateRequested(true)` 来请求。通过调用 `wi::renderer::UpdateRaytracingAccelerationStructures(cmd)` 来更新加速结构，可以在异步计算或图形队列上调用。更新将在 GPU 时间线上发生，因此提供 [CommandList](#工作提交) 作为参数。顶层加速结构将从头重建。底层加速结构将从头重建一次，然后将被更新（重新拟合）。

加速结构更新后，光线追踪着色器可以在绑定到着色器资源槽后使用它。

#### 光线追踪（计算）
如果硬件加速光线追踪不可用，某些效果将回退到使用计算资源的软件光线追踪实现。以下效果支持软件光线追踪实现：
- 路径追踪
- 光照贴图烘焙
- DDGI
- Surfel GI
由于实际原因（因为实时使用会太慢），以下目前不支持软件光线追踪：
- 光线追踪阴影
- 光线追踪环境光遮蔽
- 光线追踪反射
- 光线追踪漫反射

#### 路径追踪
`wi::renderer::RayTraceScene()` 函数将使用路径追踪从使用 `wi::renderer::BindCameraCB()` 为当前 `CommandList` 绑定的相机视角渲染场景。结果将写入作为参数提供的纹理。你还提供样本索引参数，因为路径追踪将在此调用中仅渲染 1 个样本，但对于大于 0 的样本索引，它将结果混合到先前结果纹理中。纹理必须使用 `UNORDERED_ACCESS` 绑定标志创建，因为它将在计算着色器中写入。使用此功能之前必须已构建场景 BVH 结构，可以通过调用 `wi::renderer::UpdateRaytracingAccelerationStructures()` 来完成。[RenderPath3D_Pathracing](#renderpath3d_pathtracing) 使用此光线追踪功能来渲染路径追踪场景。
`RayTraceScene()` 还有可选的纹理参数，可以在使用降噪器或与光栅化效果合成时填充以辅助。有关更多详细信息，请查看 [RenderPath3D_Pathtracing](#renderpath3d_pathtracing) 实现。

除了路径追踪外，还可以使用 `RayTraceSceneBVH` 函数渲染场景 BVH。这会将边界框层次结构作为热图渲染到屏幕。蓝色表示每个像素命中的框很少，而更多的边界框命中使颜色变为绿色、黄色、红色，最后是白色。这对于确定场景在光线追踪性能方面的昂贵程度很有用。

#### 光照贴图烘焙
光照贴图烘焙也使用 GPU 上的光线追踪来预计算场景中对象的静态光照。包含光照贴图图集纹理坐标集的[对象](#objectcomponent)可以通过设置 `ObjectComponent::SetLightmapRenderRequest(true)` 来启动光照贴图渲染。每个设置了此标志的对象每帧将通过 [wi::renderer](#wi::renderer) 内部执行光线追踪渲染来更新其光照贴图。每帧仅渲染 1 个样本，因此结果将实时更新，你将看到结果如何随时间累积。你可以在感觉到收敛足够时停止累积。光照贴图纹理坐标可以通过单独的工具生成，例如 Wicked Engine 编辑器应用程序。光照贴图可以选择以 BC6H 格式压缩以节省内存并提高性能。压缩仅在光照贴图渲染停止后执行，因此压缩不会干扰光照贴图累积。如果你使用降噪器，它将在光照贴图烘焙停止后执行。要对光照贴图降噪，请按照[降噪器](#降噪器)部分中描述的路径追踪降噪器设置相同步骤操作。

#### 场景 BVH
可以使用 `wi::renderer::UpdateRaytracingAccelerationStructures()` 函数从头重建场景 BVH。[光线追踪](#光线追踪硬件加速)功能要求在使用它们之前构建场景 BVH。当硬件光线追踪不可用时，这使用 [wiGPUBVH](#wigpubvh) 设施在 GPU 上运行的计算着色器构建 BVH。否则它使用光线追踪加速结构 API 对象。

#### 贴花
场景中的 [DecalComponent](#decalcomponent) 可以根据所使用的渲染技术进行不同渲染。两种主要渲染技术是前向渲染和延迟渲染。

<b>前向渲染</b>旨在降低带宽消耗，因此场景光照在一次渲染通道中计算，就在将场景对象渲染到屏幕时。在这种情况下，所有贴花也将在对象渲染着色器中自动处理。在这种情况下，需要生成贴花图集，因为所有贴花纹理必须可在单个着色器中采样，但这在 [UpdateRenderData](#updaterenderdata) 函数内自动处理。

<b>延迟渲染</b>技术输出 G 缓冲区，并在与对象渲染通道分离的单独通道中计算光照。贴花使用 `wi::renderer::DrawDeferredDecals()` 函数一个接一个地渲染在反照率缓冲区之上。所有光照将在贴花渲染到反照率后，在单独的渲染通道中在其之上计算，以完成最终场景。

#### 环境探针
[EnvironmentProbeComponent](#environmentprobecomponent) 可以放置到场景中，如果使用 `EnvironmentProbeComponent::SetDirty(true)` 标志标记为无效，它们将被渲染到所有着色器中可访问的立方体贴图数组。如果设置了 `EnvironmentProbeComponent::SetRealTime(true)` 标志，它们还将每帧实时渲染。这些立方体贴图包含来自点光源的间接镜面反射信息，可用作附近对象的近似反射。

探针还必须具有与同一实体关联的 [TransformComponent](#transformcomponent)。这将用于在场景中定位探针，还用于缩放和旋转它们。缩放/位置/旋转定义了一个定向边界框（OBB），将用于执行视差校正环境映射。这意味着体积内的反射不会显得无限远，而是限制在体积内，以实现更可信的错觉。

#### 后处理
`wi::renderer` 中实现了多种后处理效果。它们都在以 Postprocess_ 开头的单个函数中实现，例如：`wi::renderer::Postprocess_SSAO()`。它们旨在成为无状态函数，其函数签名清楚地指示输入/输出参数和资源。

后处理的链/顺序不在这里实现，仅实现单个效果本身。后处理的顺序更多是用户责任，因此应在[高层接口](#高层接口)中实现。作为参考，在 [RenderPath3D::RenderPostProcessChain()](#renderpath3d) 函数中实现了默认后处理链。

#### 实例化
渲染对象时将始终自动使用实例化渲染。这意味着共享同一[网格](#meshcomponent)的 [ObjectComponent](#objectcomponent) 将被批量为一个绘制调用，即使它们具有不同的变换、颜色或抖动参数。当大量对象被复制（例如树木、岩石、道具）时，这可以大大减少 CPU 开销。

[ObjectComponent](#objectcomponent) 可以覆盖[材质](#materialcomponent)的[模板](#模板)设置。如果多个 [ObjectComponent](#objectcomponent) 共享同一网格，但某些使用不同的模板覆盖，则可以从实例化批次中移除它们，因此为对象修改模板覆盖有一些开销。

<i>提示：要了解有关实例化如何用于批量对象的更多信息，请查看 [wi::renderer.cpp](../WickedEngine/wi::renderer.cpp) 中的 `RenderMeshes()` 函数</i>

#### 模板
如果使用 [DrawScene()](#drawscene) 时绑定了深度模板缓冲区，将写入模板缓冲区。模板是一个 8 位掩码，可用于为不同对象实现不同类型的屏幕空间效果。[MaterialComponent](#materialcomponent) 和 [ObjectComponent](#objectcomponent) 可以设置将渲染的模板值。8 位模板值分为两部分：
- 前 4 位保留用于引擎特定值，例如将皮肤、天空、常见材质彼此分离。这些值包含在 [wiEnums](#wienums) 的 `STENCILREF` 枚举中。
- 最后 4 位保留用于用户模板值。应用程序可以决定将其用于什么。

请使用 `wi::renderer::CombineStencilrefs()` 函数以面向未来的方式指定模板掩码。

[管线状态](#管线状态)有一个 `DepthStencilState` 类型成员，它将控制模板掩码如何用于任何自定义渲染效果的图形管线。该功能应该等同于 DirectX 11 提供的功能并与之紧密匹配，因此有关更多信息，请参阅 [DirectX 11 深度模板状态文档](https://docs.microsoft.com/en-us/windows/win32/direct3d11/d3d10-graphics-programming-guide-depth-stencil)。

#### 加载着色器
虽然 [GraphicsDevice 负责创建着色器和管线状态](#管线状态和着色器)，但加载着色器文件本身不由图形设备处理。`wi::renderer::LoadShader(ShaderStage::)` 是提供此功能的辅助函数。它在内部从公共着色器路径加载着色器，默认情况下是 "../WickedEngine/shaders" 目录（相对于应用程序工作目录），因此提供给此函数的文件名必须相对于该路径。引擎中加载着色器的每个系统都使用此函数从同一文件夹加载着色器，这使得使用 `wi::renderer::ReloadShaders()` 函数按需重新加载着色器非常容易。这对于开发人员修改着色器并重新编译它时很有用，引擎可以在应用程序运行时重新加载它。开发人员可以使用 `wi::renderer::SetShaderPath()` 将公共着色器路径修改为任何首选路径。开发人员可以自由使用自定义加载器从任何路径加载着色器，但在这种情况下，`wi::renderer::ReloadShaders()` 功能可能不适用于这些着色器。

#### 调试绘制
可以通过调用 `wi::renderer::DrawDebugWorld()` 函数并设置调试几何体或启用调试功能来渲染调试几何体。`DrawDebugWorld()` 已由 [RenderPath3D](#renderpath3d) 调用，因此开发人员只需担心配置调试绘制功能并添加调试几何体，绘制将在正确的位置发生（如果开发人员决定在其应用程序中使用 [RenderPath3D](#renderpath3d)）。

当前用户提供的调试几何体功能有：
- `DrawBox()`：提供变换矩阵和颜色，以所需变换和颜色渲染线框立方体网格。立方体将仅渲染单帧。
- `DrawLine()`：提供线段起点、终点位置和颜色值。线将仅渲染单帧。
- `DrawPoint()`：提供位置、大小和颜色，将点渲染为始终面向相机的"X"线几何体。点将仅渲染单帧。
- `DrawTriangle()`：提供 3 个位置和颜色，表示彩色三角形。有一个选项可以以线框模式而不是实体模式绘制三角形。三角形将仅渲染单帧。
- `DrawSphere()`：提供球体和颜色，其边界将作为线几何体绘制。球体将仅渲染单帧。
- `DrawCapsule()`：提供胶囊和颜色，其边界将作为线几何体绘制。胶囊将仅渲染单帧。

配置其他调试渲染功能：
- `SetToDrawDebugBoneLines()`：骨骼将作为线渲染
- `SetToDrawDebugPartitionTree()`：场景对象边界框将被渲染。
- `SetToDrawDebugEnvProbes()`：环境探针将作为反射球渲染，其影响范围作为定向边界框。
- `SetToDrawDebugEmitters()`：发射器网格几何体将作为线框网格渲染。
- `SetToDrawDebugForceFields()`：力场体积将被渲染。
- `SetToDrawDebugCameras()`：相机将作为定向框渲染。

#### 动画蒙皮
`armatureID` 与 [ArmatureComponent](#armaturecomponent) 关联的 [MeshComponent](#meshcomponent) 将在 `wi::renderer::UpdateRenderData()` 函数内进行蒙皮。这意味着它们的顶点缓冲区将使用计算着色器进行动画处理，动画顶点缓冲区将在帧的其余部分使用。


#### 自定义着色器
除了内置材质着色器外，开发人员还可以从应用程序端创建自定义着色器库并将其分配给材质。`wi::renderer::RegisterCustomShader()` 函数用于从应用程序注册自定义着色器。该函数返回自定义着色器的 ID，可以输入到 `MaterialComponent::SetCustomShaderID()` 函数。

`CustomShader` 本质上是每个 `RENDERPASS` 的[管线状态对象](#管线状态和着色器)的组合，指定它是在 `RENDERPASS` 内的透明还是不透明或其他类型通道中绘制。开发人员负责创建完全有效的管线状态来渲染网格。如果管线状态对于 `RENDERPASS` 的组合留空，则材质将仅在该通道中被跳过而不渲染。`CustomShader` 的另一部分是名称，可用作用户的简单标识符，以及 `filterMask`，将用于向多个系统指示这是哪种材质。你可以将 `filterMask` 设置为任何 `wi::enums::FILTER` 组合以满足你的目的，但你必须包含 `FILTER_OPAQUE` 或 `FILTER_TRANSPARENT` 以指示这将在不透明还是透明通道中渲染（或两者兼有）。

`MaterialComponent::userdata` 还可用于提供少量自定义材质数据，这些数据将对着色器可用。你可以从 `ShaderMaterial::userdata` 在着色器中访问它。如果内置用户数据不足以满足你的目的，你可以创建额外的 `GPUBuffer` 对象并在用户数据中发送描述符索引以间接访问扩展用户数据。

要查看示例，请查看内置的 Hologram 自定义着色器，并了解如何创建有效的管线状态、着色器等。


### 枚举
[[头文件]](../../WickedEngine/wiEnums.h)
这是 wi::renderer 用于标识图形资源的枚举值集合。通常声明相同资源类型的数组，XYZENUM_COUNT 值告诉数组的长度。其他 XYZENUM_VALUE 表示该数组中的单个元素。这使代码易于管理，例如：

```cpp
enum CBTYPE
{
	CBTYPE_MESH, // = 0
	CBTYPE_SOMETHING_ELSE, // = 1
	CBTYPE_AN_OTHER_THING, // = 2
	CBTYPE_COUNT // = 3
};
GPUBuffer buffers[CBTYPE_COUNT]; // 此示例数组包含 3 个元素
//...
device->BindConstantBuffer(&buffers[CBTYPE_MESH], 0, cmd); // 使引用元素变得容易
```

这被广泛使用以使代码直接且易于添加新对象，而无需创建额外的声明，除了枚举值。

### 图像渲染器
[[头文件]](../../WickedEngine/wiImage.h) [[源文件]](../../WickedEngine/wiImage.cpp)
这可以以简单的方式将图像渲染到屏幕。你可以这样绘制图像：
```cpp
wi::image::SetCanvas(canvas); // 设置画布区域是设置绘制区域和执行 DPI 缩放所必需的（这仅适用于当前线程）
wi::image::Draw(myTexture, wiImageParams(10, 20, 256, 128), cmd);
```
示例将把 2D 纹理图像绘制到位置 (10, 20)，大小为 256 x 128 像素，到当前渲染通道。还有许多其他参数可自定义渲染图像，有关更多信息，请参见 wiImageParams 结构。
- wi::image::Params <br/>
描述如何在屏幕上绘制图像以及在哪里绘制的所有参数。

### 字体渲染器
[[头文件]](../../WickedEngine/wiFont.h) [[源文件]](../../WickedEngine/wiFont.cpp)
这可以以简单的方式将字体渲染到屏幕。你可以像这样简单地渲染字体：
```cpp
wi::font::SetCanvas(canvas); // 设置画布区域是设置绘制区域和执行 DPI 缩放所必需的（这仅适用于当前线程）
wi::font::Draw("write this!", wiFontParams(10, 20), cmd);
```
这会将文本 <i>write this!</i> 写入屏幕上的 10, 20 像素位置。还有许多其他参数描述字体的位置、大小、颜色等。有关更多详细信息，请参见 wiFontParams 结构。
- wiFontParams <br/>
描述如何在屏幕上绘制字体以及在哪里绘制的所有参数。

wiFont 可以加载和渲染 .ttf（TrueType）字体。默认的"Liberation Sans"（Arial 兼容）字体样式嵌入到引擎中（[[liberation_sans.h]](../WickedEngine/Utility/liberation_sans.h) 文件）。开发人员可以使用 `wiFont::AddFontStyle()` 函数从文件加载其他字体。这些可以从文件加载，或获取提供的字体字节数据。`AddFontStyle()` 将返回一个 `int`，指示已加载字体库中的字体 ID。可以将 `wiFontParams::style` 设置为字体 ID 以使用先前加载的特定字体。如果开发人员在调用 wiFont::Initialize 之前添加了字体，则该字体将是默认字体，并且不会创建"Liberation Sans"字体。

### 发射粒子系统
[[头文件]](../../WickedEngine/wiEmittedParticle.h) [[源文件]](../../WickedEngine/wiEmittedParticle.cpp)
GPU 驱动的发射粒子系统，用于绘制大量面向相机的四边形公告板。支持力场模拟和基于光滑粒子流体动力学计算的流体模拟。

### 毛发粒子系统
[[头文件]](../../WickedEngine/wiHairParticle.h) [[源文件]](../../WickedEngine/wiHairParticle.cpp)
GPU 驱动的附加到网格表面的粒子。可用于渲染植被。它参与力场模拟。

### 海洋
[[头文件]](../../WickedEngine/wiOcean.h) [[源文件]](../../WickedEngine/wiOcean.cpp)
使用快速傅里叶变换模拟的海洋渲染器。海洋表面始终相对于相机渲染，就像无限大的水体一样。

### 精灵
[[头文件]](../../WickedEngine/wiSprite.h) [[源文件]](../../WickedEngine/wiSprite.cpp)
用于渲染和动画图像的辅助设施。它在内部使用 [wiImage](#wiimage) 渲染器
- Anim <br/>
几种不同的简单动画实用工具，如动画纹理、摆动、旋转、淡出等...

### SpriteFont
[[头文件]](../../WickedEngine/wiSprite.h) [[源文件]](../../WickedEngine/wiSprite.cpp)
用于渲染字体的辅助设施。它在内部使用 [wiFont](#wifont) 渲染器。它执行字符串转换

### TextureHelper
[[头文件]](../../WickedEngine/wiTextureHelper.h) [[源文件]](../../WickedEngine/wiTextureHelper.cpp)
用于生成程序纹理，如均匀颜色、噪声等...

### GPUSortLib
[[头文件]](../../WickedEngine/wiGPUSortLib.h) [[源文件]](../../WickedEngine/wiGPUSortLib.cpp)
这是使用 Bitonic Sort 算法的 GPU 排序设施。它可以完全在 GPU 上根据浮点列表作为比较键对索引列表进行排序。

### GPUBVH
[[头文件]](../../WickedEngine/wiGPUBVH.h) [[源文件]](../../WickedEngine/wiGPUBVH.cpp)
此设施可以在 GPU 上为 [Scene](#scene) 生成 BVH（边界体积层次结构）。BVH 结构可用于在 GPU 上执行高效的 RAY-三角形相交，例如在光线追踪中。这不使用光线追踪 API 硬件加速，而是在计算中实现，因此具有广泛的硬件支持。


## GUI
使用引擎功能实现的自定义 GUI

### GUI
[[头文件]](../../WickedEngine/wiGUI.h) [[源文件]](../../WickedEngine/wiGUI.cpp)
wiGUI 负责运行 GUI 界面并管理小部件。

<b>GUI 缩放：</b> 为确保正确的 GUI 缩放，GUI 元素应为当前窗口大小设计。如果将它们放置在 `RenderPath2D::ResizeLayout()` 函数内根据当前屏幕大小，将确保 GUI 在分辨率或 DPI 更改事件时缩放，这是推荐的。

### EventArgs
这将发送到小部件回调以提供不同格式的事件参数

### wiWidget
基本小部件接口可以通过特定功能扩展。GUI 将通过此接口存储和处理小部件。

#### Button
简单的可点击按钮。支持 OnClick 事件回调。

#### Label
简单的静态文本字段。

#### TextInputField
激活时支持文本输入。按 Enter 将接受输入并触发 OnInputAccepted 回调。激活时按 Escape 键将取消文本输入并恢复先前状态。一次只能有一个活动的文本输入字段。

#### Slider
滑块，可以表示浮点或整数值。滑块还接受文本输入以输入数字值。如果数字输入超出滑块的范围，它将扩展其范围以支持新分配的值。更改滑块值时（无论是通过文本输入还是滑动），将触发 OnSlide 事件回调。

#### CheckBox
复选框是一个两种状态的项目，可以表示真/假状态。更改值时（通过单击它）将触发 OnClick 事件回调

#### ComboBox
支持从文本列表中选择项目。可以设置最大可见项目数。如果项目列表大于最大允许的可见项目数，则将显示垂直滚动条以允许显示隐藏的项目。选择时，将触发 OnSelect 事件回调。

#### Window
窗口小部件能够容纳任意数量的其他小部件。它可以由用户在屏幕上移动、最小化和调整大小。自 0.49.0 起，窗口不管理附加小部件的生命周期！

#### ColorPicker
支持选择 HSV（或 HSL）颜色，显示其 RGB 值。选择时，将触发 OnColorChanged 事件回调，用户可以从事件参数中读取新的 RGB 值。


## 辅助工具
引擎级辅助类的集合

### Archive
[[头文件]](../../WickedEngine/wiArchive.h) [[源文件]](../../WickedEngine/wiArchive.cpp)
用于将二进制数据序列化到磁盘或内存。归档文件始终以序列化的 64 位版本号开头。版本号大于引擎当前归档版本的归档无法安全打开，因此如果发生这种情况将显示错误消息。如果当前归档版本屏障号大于归档自身的版本号，则某个归档版本将与当前引擎版本不向前兼容。

### Color
[[头文件]](../../WickedEngine/wiColor.h)
用于将浮点颜色数据转换为/从 32 位 RGBA 数据（存储在 uint32_t 中作为 RGBA，其中每个通道为 8 位）的实用工具

### FadeManager
[[头文件]](../../WickedEngine/wiFadeManager.h) [[源文件]](../../WickedEngine/wiFadeManager.cpp)
用于管理淡出屏幕的简单辅助工具。淡出从透明开始，然后平滑地淡入到不透明颜色（在大多数情况下为黑色），然后发生回调，用户可以用自己的事件处理它。之后，颜色将淡回透明。这被 [Application](#application) 用于从一个 RenderPath 淡入到另一个。

### Helper
[[头文件]](../../WickedEngine/wiHelper.h) [[源文件]](../../WickedEngine/wiHelper.cpp)
许多辅助实用函数，如截图、读取文件、消息框、拆分路径、睡眠等...

### Primitive
[[头文件]](../../WickedEngine/wiPrimitive.h) [[源文件]](../../WickedEngine/wiPrimitive.cpp)
可以相互相交的图元

#### AABB
[[头文件]](../../WickedEngine/wiPrimitive.h) [[源文件]](../../WickedEngine/wiPrimitive.cpp)
轴对齐边界框。有多种构造方法，例如从最小-最大角或中心和半范围。

#### Sphere
[[头文件]](../../WickedEngine/wiPrimitive.h) [[源文件]](../../WickedEngine/wiPrimitive.cpp)
具有中心和半径的球体。

#### Capsule
[[头文件]](../../WickedEngine/wiPrimitive.h) [[源文件]](../../WickedEngine/wiPrimitive.cpp)
它就像两个由圆柱体连接的球体。Base 和 Tip 是两个端点，radius 是圆柱体的半径。

#### Ray
[[头文件]](../../WickedEngine/wiPrimitive.h) [[源文件]](../../WickedEngine/wiPrimitive.cpp)
具有起点（原点）和方向的线。方向的倒数是预先计算的，以执行许多图元与一条射线的快速相交。

#### Frustum
[[头文件]](../../WickedEngine/wiPrimitive.h) [[源文件]](../../WickedEngine/wiPrimitive.cpp)
六个平面，最常用于检查可相交图元是否在相机内。

#### Hitbox2D
[[头文件]](../../WickedEngine/wiPrimitive.h) [[源文件]](../../WickedEngine/wiPrimitive.cpp)
一个矩形，本质上是 2D AABB。

### Math
[[头文件]](../../WickedEngine/wiMath.h) [[源文件]](../../WickedEngine/wiMath.cpp)
数学相关的辅助函数，如 lerp、triangleArea、HueToRGB 等...

### Random
[[头文件]](../../WickedEngine/wiRandom.h) [[源文件]](../../WickedEngine/wiRandom.cpp)
具有良好分布的均匀随机数生成器。

### RectPacker
[[头文件]](../../WickedEngine/wiRectPacker.h) [[源文件]](../../WickedEngine/wiRectPacker.cpp)
提供将多个矩形打包到更大矩形中的能力，同时从包含矩形中占用最少的空间。

### ResourceManager
[[头文件]](../../WickedEngine/wiResourceManager.h) [[源文件]](../../WickedEngine/wiResourceManager.cpp)
这可以加载图像和声音。它将保留资源直到至少有某个东西引用它们，否则删除它们。一个资源也可以有多个所有者。这是线程安全的。

- `Load()`：加载资源，或如果已存在则返回资源句柄。资源由文件名标识。用户可以指定导入标志（可选）。用户可以提供外部加载的文件数据缓冲区（可选）。此函数将返回资源句柄。如果未成功加载，资源句柄等于 `nullptr`，否则返回有效句柄。
- `Contains()`：检查资源是否存在。
- `Clear()`：清除所有资源。这将清除资源库，但仍在某处使用的资源将保持可用。

资源管理器可以支持不同的模式，可以通过 `SetMode(MODE param)` 函数设置：
- `DISCARD_FILEDATA_AFTER_LOAD`：这是默认行为。资源将不保留文件数据，即使用户在加载资源时指定了 `IMPORT_RETAIN_FILEDATA` 标志。这将导致资源管理器无法序列化（保存）自身。
- `ALLOW_RETAIN_FILEDATA`：此模式可用于保持资源内的文件数据缓冲区存活。这样资源管理器可以被序列化（保存）。只有仍保留其文件数据的资源才会被序列化（保存）。加载资源时，用户可以指定 `IMPORT_RETAIN_FILEDATA` 标志以保留特定资源的文件数据而不是丢弃它。
- `ALLOW_RETAIN_FILEDATA_BUT_DISABLE_EMBEDDING`：保留所有文件数据，但在序列化时不写入它们。这对于临时禁用资源嵌入而不销毁文件数据缓冲区很有用。

资源管理器始终可以在读取模式下序列化。文件数据保留将基于现有文件导入标志和全局资源管理器模式。

### SpinLock
[[头文件]](../../WickedEngine/wiSpinLock.h) [[源文件]](../../WickedEngine/wiSpinLock.cpp)
这可用于在多线程竞争条件场景中保证对块的独占访问，而不是互斥锁。与互斥锁的区别在于，这不允许线程让出，而是在原子标志上自旋直到可以锁定自旋锁。

### Arguments
[[头文件]](../../WickedEngine/wiArguments.h) [[源文件]](../../WickedEngine/wiArguments.cpp)
用于存储从操作系统"命令行"传递给应用程序的启动参数。用户可以按名称查询这些参数。

### Timer
[[头文件]](../../WickedEngine/wiTimer.h) [[源文件]](../../WickedEngine/wiTimer.cpp)
高分辨率秒表计时器

### wiVoxelGrid
[[头文件]](../../WickedEngine/wiVoxelGrid.h) [[源文件]](../../WickedEngine/wiVoxelGrid.cpp)
包含体素 3D 网格的轴对齐边界框体积。它可用于体素化场景，并由 [PathQuery](#wipathquery) 用于路径查找。

体素网格使用 `init()` 函数创建，提供 3D 网格的尺寸。此函数将分配存储网格所需的内存，并将每个体素填充为空。要简单地清除网格，请使用 `cleardata()` 函数，它不会分配内存，只会将所有体素清除为空。

网格的体积由 `center` 和 `voxelSize` 成员指定。要设置 `voxelSize`，请使用 `set_voxelsize()` 函数而不是直接修改 `voxelSize`。你还可以使用 `from_aabb()` 函数轻松将其与现有 AABB 对齐。设置这些不会修改体素数据，因此修改后可能需要重新体素化。

主要功能是可以将图元注入体素网格，这是体素化过程。你可以分别使用 `inject_triangle()`、`inject_aabb()`、`inject_sphere()` 和 `inject_capsule()` 函数注入三角形、AABB、球体和胶囊体图元。所有图元都是世界空间输入到这些函数中的，它们将根据网格中心、voxelSize 和分辨率在内部由这些函数映射到体素网格中。这些函数还可以接受一个名为 `subtract` 的 bool 选项，如果设置为 `true`，将修改体素化过程以移除而不是添加体素。体素化过程对性能敏感，但可以从不同线程完成，因为它是线程安全的，使用原子操作修改体素数据。

要访问单个体素，你可以使用 `check_voxel()` 函数检查体素是空还是有效，使用 `set_voxel()` 函数将体素设置为空或有效。这些操作不是线程安全的！这些函数还都将接受世界位置或体素坐标。你还可以使用 `world_to_coord()` 函数将世界位置转换为体素坐标，或使用 `coord_to_world()` 函数进行反向转换。

注意：有辅助函数可以体素化整个对象或整个场景，可从 [Scene](#scene) 对象访问。这些函数称为 `VoxelizeObject()` 和 `VoxelizeScene()`。

### wiPathQuery
[[头文件]](../../WickedEngine/wiPathQuery.h) [[源文件]](../../WickedEngine/wiPathQuery.cpp)
路径查询可以在体素网格内找到从起点到目标位置的路径。要运行路径查找查询，首先用场景数据准备一个[体素网格](#wivoxelgrid)，然后用路径查询处理它。

路径查询的最少用法是调用 `process()` 函数，提供起点和目标位置以及[体素网格](#wivoxelgrid)。当函数返回时，你可以使用 `is_successful()` 函数检查路径查找是否成功，使用 `get_next_waypoint()` 函数找到从起点到目标的路径中的下一个路径点。

路径查询还可以用 `flying` bool 参数配置。如果将 `flying` 设置为 `true`，则路径查找将在空体素（空中）中搜索路径，否则默认情况下它将尝试找到在地面上行进的路径。

遍历实体可以具有逻辑大小，由 `agent_height` 和 `agent_width` 参数配置，指定遍历实体以体素为单位的近似大小。`agent_height` 将指定遍历路径上任何路径点上方必须有多少空体素。`agent_width` 指定水平方向必须有多少空体素。使用这些你可以指定路径应与墙壁和障碍物保持多远，也不允许进入逻辑大小不允许的紧密开口之间。

注意：处理路径查询可能需要很长时间，具体取决于目标距起点有多远。考虑在多个线程上执行多个路径查询，或在帧之间异步执行它们，可以使用[作业系统](#作业系统)来跟踪此类异步任务的完成。


## 输入
[[头文件]](../../WickedEngine/wiInput.h) [[源文件]](../../WickedEngine/wiInput.cpp)
这是高级输入接口。使用它以平台无关的方式读取输入设备。
- Initialize <br/>
创建所有必需的资源，引擎初始化已通过 [wiInitializer](#初始化器) 完成此操作，因此用户可能不必担心此操作。
- Update <br/>
这每帧调用一次，是处理输入所必需的。这在 [Application](#application) 中自动调用，因此用户不必担心它，除非他们为自己重新实现高层接口。
- Down <br/>
检查按钮当前是否被按住。
- Press <br/>
检查按钮在当前帧中是否被按下。
- Hold <br/>
检查按钮是否被按住指定时间。可以检查它是否被精确按住设定的时间，或至少按住那么长时间。
- GetPointer <br/>
返回鼠标位置。返回向量的前两个值是窗口空间中的鼠标指针坐标。第三个值是自上一帧以来的相对滚动按钮差异。
- SetPointer <br/>
在窗口相对坐标中设置鼠标指针位置。
- HidePointer <br/>
隐藏或显示鼠标指针。
- GetAnalog <br/>
返回游戏手柄的模拟位置。
- SetControllerFeedback <br/>
利用游戏手柄的各种功能，如振动或 LED 颜色。

### BUTTON
此枚举集合包含所有可用的数字按钮，无论是键盘上的还是控制器上的。如果你想指定键盘上的字母键，你可以使用普通字符值并转换为此枚举，如：

```cpp
bool is_P_key_pressed = wiInput::Press((wiInput::BUTTON)'P');
```

### KeyboardState
键盘的完整状态，其中每个按钮的状态存储为按下或释放。可以通过 [wiRawInput](#wirawinput) 查询

### MouseState
鼠标指针的绝对和相对位置。可以通过 [wiRawInput](#wirawinput) 查询

### ControllerState
控制器的按钮和模拟状态。可以通过 [wiRawInput](#wirawinput) 或 [wiXInput](#wixinput) 查询

### ControllerFeedback
可能支持的控制器的力反馈功能。可以提供给 [wiRawInput](#wirawinput) 或 [wiXInput](#wixinput)

### Touch
触摸接触点。目前在 UWP（通用 Windows 平台）应用程序中受支持。
- GetTouches <br/>
获取包含当前 Touch 接触点的向量

### XInput
[[头文件]](../../WickedEngine/wiXInput.h) [[源文件]](../../WickedEngine/wiXInput.cpp)
XInput API 的低级包装器（能够处理 Xbox 控制器）。此功能由更通用的 wiInput 接口使用，因此用户可能不需要使用它。

### RawInput
[[头文件]](../../WickedEngine/wiRawInput.h) [[源文件]](../../WickedEngine/wiRawInput.cpp)
RAWInput API 的低级包装器（能够处理人机接口设备，如鼠标、键盘、控制器）。此功能由更通用的 wiInput 接口使用，因此用户可能不需要使用它。



## 音频
[[头文件]](../../WickedEngine/wiAudio.h) [[源文件]](../../WickedEngine/wiAudio.cpp)
音频相关功能的集合命名空间。
- CreateSound
- CreateSoundInstance
- Play
- Pause
- Stop
- SetVolume
- GetVolume
- ExitLoop
- SetSubmixVolume
- GetSubmixVolume
- Update3D
- SetReverb
### Sound
表示内存中的声音文件。通过 wiAudio 接口加载声音文件。
### SoundInstance
声音文件的实例，可以通过 wiAudio 接口以各种方式播放和控制。（要确保其 `Sound` 的循环播放，必须在 `audio::CreateSoundInstance` _之前_ 调用 `SoundInstance::SetLooped(true)`，即使发生在调用 `Play` 之前，后续的 SetLooped 调用也无效。）
### SoundInstance3D
此结构描述 3D 空间中侦听器和声音发射器之间的关系。与 wiAudio::Update3D() 函数中的 SoundInstance 一起使用
### SUBMIX_TYPE
将声音分组，以便可以为整个组设置不同的属性，例如音量
### REVERB_PRESET
可以全局产生不同的 3D 混响效果
- REVERB_PRESET_DEFAULT
- REVERB_PRESET_GENERIC
- REVERB_PRESET_FOREST
- REVERB_PRESET_PADDEDCELL
- REVERB_PRESET_ROOM
- REVERB_PRESET_BATHROOM
- REVERB_PRESET_LIVINGROOM
- REVERB_PRESET_STONEROOM
- REVERB_PRESET_AUDITORIUM
- REVERB_PRESET_CONCERTHALL
- REVERB_PRESET_CAVE
- REVERB_PRESET_ARENA
- REVERB_PRESET_HANGAR
- REVERB_PRESET_CARPETEDHALLWAY
- REVERB_PRESET_HALLWAY
- REVERB_PRESET_STONECORRIDOR
- REVERB_PRESET_ALLEY
- REVERB_PRESET_CITY
- REVERB_PRESET_MOUNTAINS
- REVERB_PRESET_QUARRY
- REVERB_PRESET_PLAIN
- REVERB_PRESET_PARKINGLOT
- REVERB_PRESET_SEWERPIPE
- REVERB_PRESET_UNDERWATER
- REVERB_PRESET_SMALLROOM
- REVERB_PRESET_MEDIUMROOM
- REVERB_PRESET_LARGEROOM
- REVERB_PRESET_MEDIUMHALL
- REVERB_PRESET_LARGEHALL
- REVERB_PRESET_PLATE


## 物理
[[头文件]](../../WickedEngine/wiPhysics.h) [[源文件]](../../WickedEngine/wiPhysics_Bullet.cpp)
你可以在解决方案的 ENGINE/Physics 筛选器下找到物理系统相关功能。
它使用实体-组件系统来执行更新世界中的所有物理组件。
- Initialize<br/>
这必须在使用物理系统之前调用，但 [wiInitializer](#初始化器) 会自动完成
- IsEnabled<br/>
物理系统是否正在运行？
- SetEnabled<br/>
启用或禁用物理系统
- RunPhysicsUpdateSystem<br/>
对输入组件运行物理模拟。

#### 刚体物理
刚体模拟需要实体的 [RigidBodyPhysicsComponent](#rigidbodyphysicscomponent) 和 [TransformComponent](#transformcomponent)。它将用物理模拟数据修改 TransformComponent，因此模拟后，TransformComponent 将包含绝对世界矩阵。

<b>运动学</b>刚体是不由物理系统模拟的刚体，但它们将影响其余模拟。例如，动画运动学刚体将严格遵循动画，但影响它接触的任何其他刚体。通过在 `RigidBodyPhysicsComponent::_flags` 位掩码中具有 `RigidBodyPhysicsComponent::KINEMATIC` 标志将刚体设置为运动学。

<b>停用</b>在参与模拟一段时间的刚体之后发生，这意味着之后它们将不再参与模拟。可以使用 `RigidBodyPhysicsComponent::DISABLE_DEACTIVATION` 标志禁用此行为。

有多个可用于刚体的<b>碰撞形状</b>：
- `BOX`：简单的定向边界框，快速。
- `SPHERE`：简单的球体，快速。
- `CAPSULE`：两个球体之间有圆柱体。
- `CONVEX_HULL`：简化的网格。
- `TRIANGLE_MESH`：原始网格。它始终是运动学的。

#### 软体物理
软体模拟需要实体的 [SoftBodyPhysicsComponent](#softbodyphysicscomponent) 以及 [MeshComponent](#meshcomponent)。创建软体时，模拟网格将从 MeshComponent 顶点和从物理到图形索引的映射表计算，将图形顶点与物理顶点关联。物理顶点将在世界空间中模拟并复制到 `SoftBodyPhysicsComponent::vertex_positions_simulation` 数组作为图形顶点。此数组可以原样上传为顶点缓冲区。

如果 ObjectComponent 的网格有关联的软体，[ObjectComponent](#objectcomponent) 的变换矩阵用作软体的操作矩阵。操作矩阵意味着固定的软体物理顶点将接收该变换矩阵。模拟的顶点将跟随那些被操作的顶点。

<b>固定</b>软体顶点意味着这些物理顶点权重为零，因此它们不被模拟，而是驱动模拟，因为其他顶点将跟随它们，有点像运动学刚体如何操作模拟刚体。

固定的顶点也可以通过<b>蒙皮动画</b>操作。如果软体网格被蒙皮并且正在播放动画，则固定的顶点将跟随动画。




## 网络
[[头文件]](../../WickedEngine/wiNetwork.h) [[源文件]](../../WickedEngine/wiNetwork.cpp)
提供 UDP 网络功能的简单接口。
- Initialize
- CreateSocket
- Send
- ListenPort
- CanReceive
- Receive
#### Socket
这是为了发送或接收数据必须创建的句柄。它标识发送者/接收者。
#### Connection
标识通信目标的 IP 地址和端口号


## 脚本
这是 Lua 脚本接口的位置。有关 Lua 脚本接口的完整参考，请参见 [ScriptingAPI-Documentation](ScriptingAPI-Documentation.md)
### LuaBindings
绑定到 Lua 的系统以系统名称作为文件名，后缀为 _BindLua。
### Lua
[[头文件]](../../WickedEngine/wiLua.h) [[源文件]](../../WickedEngine/wiLua.cpp)
C++ 端的 Lua 脚本接口。这允许从 C++ 端执行 lua 命令并操作 lua 栈，例如向 lua 推送值和从 lua 获取值等。
### Lua_Globals
[[头文件]](../../WickedEngine/wiLua_Globals.h)
以文本格式硬编码的 lua 脚本。这将始终被执行，并为 lua 脚本提供一些常用的辅助功能。
### Luna
[[头文件]](../../WickedEngine/wiLuna.h)
允许从 C++ 向 Lua 绑定引擎类的辅助工具


## 工具
这是使用引擎级系统的工具的位置
### Backlog
[[头文件]](../../WickedEngine/wiBacklog.h) [[源文件]](../../WickedEngine/wiBacklog.cpp)
用于任何系统、从任何线程记录任何消息。它可以将自己绘制到屏幕。它可以执行 Lua 脚本。
如果发布了 `wii:backlog::LogLevel::Error` 或更高严重性的消息到 backlog，日志内容将保存到临时用户目录中的 wiBacklog.txt。
### Profiler
[[头文件]](../../WickedEngine/wiProfiler.h) [[源文件]](../../WickedEngine/wiProfiler.cpp)
用于计时执行中的特定范围。支持 CPU 和 GPU 计时。目前可以将结果作为简单文本写入屏幕。


## 着色器
着色器以 HLSL 着色语言编写，并[编译](#着色器编译器)为原生着色器二进制格式，该格式可能因平台和图形设备要求而异。

有一些宏用于声明具有绑定槽的资源，可以通过代码共享从 C++ 应用程序读取。这些宏用于声明资源：

- CBUFFER(name, slot)<br/>
声明常量缓冲区
```cpp
CBUFFER(myCbuffer, 0);
{
	float4 values0;
	uint4 values2;
};

// 像读取全局值一样加载
float loaded_value = values0.y;
```

注意：创建常量缓冲区时，结构必须根据 HLSL 规则严格填充到 16 字节边界。除此之外，Vulkan 兼容性有以下限制生效：

不正确的 16 字节填充：
```cpp
CBUFFER(cbuf, 0)
{
	float padding;
	float3 value; // <- 较大的类型可以开始新的 16 字节槽，因此 C++ 和着色器端结构可能不匹配
	float4 value2;
};
```

正确的填充：
```cpp
CBUFFER(cbuf, 0)
{
	float3 value; // <- 较大的类型必须放在填充之前
	float padding;
	float4 value2;
};
```

### 互操作
着色器和 C++ 代码之间的互操作由共享头文件（.h）处理。修改共享头文件需要重新编译引擎和着色器，否则将发生未定义行为。对于仅着色器需要可见性的情况，请考虑使用着色器头文件（.hlsli），这些不应与引擎 C++ 代码共享。

[[头文件]](../../WickedEngine/shaders/ShaderInterop.h)
Shader Interop 用于在 C++ 引擎代码和着色器代码之间声明共享结构或值。有几个 ShaderInterop 文件，以它们所用于的子系统为后缀，以保持它们最小且更可读：<br/>
[ShaderInterop_BVH.h](../../WickedEngine/shaders/ShaderInterop_BVH.h) <br/>
[ShaderInterop_DDGI.h](../../WickedEngine/shaders/ShaderInterop_DDGI.h) <br/>
[ShaderInterop_EmittedParticle.h](../../WickedEngine/shaders/ShaderInterop_EmittedParticle.h) <br/>
[ShaderInterop_FFTGenerator.h](../../WickedEngine/shaders/ShaderInterop_FFTGenerator.h) <br/>
[ShaderInterop_Font.h](../../WickedEngine/shaders/ShaderInterop_Font.h) <br/>
[ShaderInterop_FSR2.h](../../WickedEngine/shaders/ShaderInterop_FSR2.h) <br/>
[ShaderInterop_GPUSortLib.h](../../WickedEngine/shaders/ShaderInterop_GPUSortLib.h) <br/>
[ShaderInterop_HairParticle.h](../../WickedEngine/shaders/ShaderInterop_HairParticle.h) <br/>
[ShaderInterop_Image.h](../../WickedEngine/shaders/ShaderInterop_Image.h) <br/>
[ShaderInterop_Ocean.h](../../WickedEngine/shaders/ShaderInterop_Ocean.h) <br/>
[ShaderInterop_Postprocess.h](../../WickedEngine/shaders/ShaderInterop_Postprocess.h) <br/>
[ShaderInterop_Raytracing.h](../../WickedEngine/shaders/ShaderInterop_Raytracing.h) <br/>
[ShaderInterop_Renderer.h](../../WickedEngine/shaders/ShaderInterop_Renderer.h) <br/>
[ShaderInterop_SurfelGI.h](../../WickedEngine/shaders/ShaderInterop_SurfelGI.h) <br/>
[ShaderInterop_Terrain.h](../../WickedEngine/shaders/ShaderInterop_Terrain.h) <br/>
[ShaderInterop_VoxelGrid.h](../../WickedEngine/shaders/ShaderInterop_VoxelGrid.h) <br/>
[ShaderInterop_VXGI.h](../../WickedEngine/shaders/ShaderInterop_VXGI.h) <br/>
[ShaderInterop_Weather.h](../../WickedEngine/shaders/ShaderInterop_Weather.h) <br/>

ShaderInterop 还包含资源宏，以帮助在 C++ 和 HLSL 之间共享代码，以及在着色器编译器之间可移植。在[着色器部分](#着色器)中阅读有关宏的更多信息

### 着色器编译器
内置的 Visual Studio 着色器编译器可以使用通常的 Visual Studio 构建过程编译 HLSL 着色器。这在某种程度上可以使用，但推荐的方法是使用 [[Wicked Engine 着色器编译器接口 (wiShaderCompiler)]](../WickedEngine/wiShaderCompiler.h)。这支持各种工具将着色器编译为不同的着色器格式（hlsl5、hlsl6、spirv），并可在运行时使用，例如轻松编译着色器排列，还使用引擎功能如[作业系统](#作业系统)来并行化编译任务，比通用构建系统有更多控制。

离线着色器编译：
OfflineShaderCompiler 工具可以构建并用于在命令行过程中编译着色器。它还可用于生成着色器转储，这是一个可以包含到 C++ 代码中并编译的头文件，因此所有着色器都将嵌入到可执行文件中，这样应用程序就不会将它们作为单独的文件加载。但是，在这种情况下，对于嵌入的着色器，着色器重新加载功能将不起作用。当使用 `shaderdump` 命令行参数由离线着色器编译器生成时，着色器转储将包含在 `wiShaderDump.h` 文件中。如果引擎编译时检测到此文件，着色器将嵌入到编译的可执行文件中。离线着色器编译器还可用于将着色器正常编译为单独的 .cso 文件，带有 .wishadermeta 元数据文件，用于检测何时需要自动重建每个着色器。
