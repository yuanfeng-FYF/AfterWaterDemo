# AfterWaterDemo · 洒水车 Demo

Unreal Engine **5.5.4** 的 Windows C++ 项目。完整保存 Content（含 542 个 .uasset、5 张地图）、Source、Config 和 AfterWaterDemo.uproject。资源通过 Git LFS 保存。

## 在另一台 Windows 电脑打开

1. 安装 Epic Games Launcher 和 **Unreal Engine 5.5.4**。首次恢复使用相同版本。
2. 安装 Visual Studio 2022，勾选 **使用 C++ 的游戏开发**、MSVC v143 和 Windows SDK。UE 5.5 支持 VS 2022 17.8 及以上，Epic 推荐 17.10；选择兼容 UE 5.5 的工具链。VS Code 只是编辑器，不能代替 C++ 编译工具链。
3. 安装 GitHub Desktop，登录有权访问此私有仓库的 GitHub 账号。在 **File → Clone repository → GitHub.com** 中选择 `yuanfeng-FYF/AfterWaterDemo`，克隆到短路径，例如 `D:\UnrealProjects\AfterWaterDemo`。等待 Git LFS 资源全部下载。
4. 推荐安装 Git for Windows（含 Git LFS），在项目目录的终端运行 `git lfs pull`，再运行 `git lfs fsck`。也可右键 `Verify-Backup.ps1` 使用 PowerShell 运行，核对备份清单。若系统策略阻止脚本，可直接使用前述 Git 命令，无需降低系统安全设置。
5. 右键 `AfterWaterDemo.uproject` → **Generate Visual Studio project files**，打开生成的 `.sln`，选择 **Development Editor / Win64**，编译 `AfterWaterDemo`。然后双击 `.uproject`。若提示编译缺失模块，可以在已安装工具链的前提下允许重建。
6. 在 Unreal 内容浏览器中打开 **Content/洒水车demo/洒水车Demo.umap**，对应包路径 `/Game/洒水车demo/洒水车Demo`。这是备份时最近编辑的洒水车关卡。项目原有默认地图仍为 ThirdPersonMap，所以第一次进入第三人称模板地图不代表资源缺失。
7. 等待首次着色器编译结束，再点击 Play。

命令行克隆方式（需要已完成 GitHub 登录）：

```powershell
git lfs install
git clone https://github.com/yuanfeng-FYF/AfterWaterDemo.git
cd AfterWaterDemo
git lfs pull
git lfs fsck
```

**请优先使用 Clone，不要只下载网页上的单个 .uproject 或默认 ZIP。** `.uproject` 是项目描述文件，必须与 Content、Source、Config 放在一起。GitHub ZIP 是否含真实 LFS 数据取决于仓库设置；缺少 LFS 下载时，资源可能只是很小的指针文件。

## 备份范围

- Content 下所有资源与地图（包括根目录另一张洒水车Demo地图，以及 backup01、backup02）全部保留。
- C++ 源码、编译目标、项目配置与 UE 版本描述保留；项目使用的 ModelingToolsEditorMode 为 UE 内置插件。
- Binaries、Intermediate、DerivedDataCache、Saved、IDE 缓存由本机生成，不进入 Git。自动保存草稿另保留于本次本地快照，正式地图以 Content 中已保存版本为准。
- Android File Server 的本机调试 SecurityToken 未上传；它不属于地图或桌面项目资源。原配置保存在创建备份时的本地快照中。
- 本仓库不包含 Unreal Engine、Visual Studio、外部 DCC 源工程或打包好的可执行游戏。资源导入记录中的旧电脑路径不影响已导入资源加载，重新导入外部源文件时需另行提供源素材。

## 两台电脑继续同步

开始工作前在 GitHub Desktop 点击 **Fetch origin / Pull origin**。完成修改后，先在 Unreal 中 **Save All**，再在 GitHub Desktop 写提交说明、**Commit to main**、**Push origin**。单独 Commit 只保存到当前电脑。切换电脑前确认 Push 完成；避免同时修改同一张地图或蓝图。

`BACKUP-MANIFEST.json` 记录初始备份的文件长度和 SHA-256；修改工程后旧清单会报告差异，这是正常现象。Git 提交历史和 Git LFS 才是后续版本的依据。

参考：[Epic C++ 环境要求](https://dev.epicgames.com/documentation/en-us/unreal-engine/setting-up-visual-studio-development-environment-for-cplusplus-projects-in-unreal-engine?application_version=5.5)、[GitHub LFS 与 ZIP](https://docs.github.com/en/repositories/managing-your-repositorys-settings-and-features/managing-repository-settings/managing-git-lfs-objects-in-archives-of-your-repository)。
