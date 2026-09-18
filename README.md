# 项目名称

> 一句话描述项目，例：C++练习，熟悉VS Code

## 📖 项目介绍

基于 CLion 开发的控制台程序。

- 开发IDE：CLion
- 编程语言：C / C++ / C#
- 项目类型：控制台应用

## ⚙️ 环境依赖

### C / C++

1. CMake
2. C/C++编译器：MinGW-w64 / GCC / Clang
3. CLion自动读取`CMakeLists.txt`构建项目

### C#

1. .NET SDK
2. CLion自带.NET插件支持C#项目

## 🚀 编译与运行

### C / C++

1. 将仓库克隆到本地，使用CLion打开项目文件夹
2. CLion自动加载CMake配置，等待项目索引完成
3. 右上角选择构建目标（Debug / Release）
4. 点击运行按钮 ▶️ 或者快捷键 `Shift+F10` 运行程序
5. `Shift+F9` 启动调试

> 手动CMake命令（终端）

```bash
mkdir build && cd build
cmake ..
make
./程序名
```

# VSCode 开发 C++ 完整.vscode配置

> 环境：Windows + MinGW‑w64 (gcc/g++) + VSCode，C++17，外部控制台
> 
> 需要插件：C/C++（微软官方）、Code Runner（可选）、clang‑format格式化
> 
> ，支持编译+调试。
> 
> 前提：已经安装 MinGW‑w64，把 `mingw64/bin` 添加到系统环境变量 PATH；
> 
> 产出：完整可运行 C++ 项目，包含 `tasks.json`(编译)、`launch.json`(调试)、`c_cpp_properties.json`(智能提示)
> 
> 使用方式：在你的项目根目录新建文件夹 `.vscode`，把下面4个文件复制进去。
> 
> **VSCode必须打开文件夹，不能只打开单个cpp文件**，项目路径不要中文。

## 一、准备工具

1. **安装 MinGW‑w64**
- 下载解压，把 `mingw64/bin` 添加到系统环境变量 PATH
- 打开 cmd 验证：

```
g++ --version
gdb --version
```

输出版本号代表安装成功。

2. VSCode 安装插件
- **C/C++ Extension Pack**（微软官方，必装，包含调试、智能提示）
- Code Runner（可选，一键运行小代码）

## 二、项目目录结构

新建项目文件夹，用 VSCode 打开该文件夹（**必须打开文件夹，不要只打开单个文件**）

```plaintext
cpp_demo/
├─ main.cpp            # 源代码
└─ .vscode/            # 配置文件夹，下面4个json自动/手动创建
 ├─ settings.json      # 工作区配置（覆盖用户settings）
 ├─ tasks.json         # 编译任务（带C++、中文乱码参数）
 ├─ launch.json        # F5调试
 └─ c_cpp_properties.json # 智能提示、头文件路径
```

## 三、.vscode 四个配置文件完整内容

### .vscode/tasks.json （编译，Ctrl+Shift+B 执行生成）

> 1.按`Ctrl+Shift+P`→输入`Task:Configure Task`（配置任务）→创建`task.json`→选择Others，生成 `.vscode/tasks.json`
> 
> 2.`Ctrl+Shift+P` → 输入 `Tasks: Configure Default Build Task`（配置默认生成任务） →选择 `C/C++: gcc build active file`（C/C++: gcc.exe生成活动文件）

g++编译，内置中文乱码修复参数

```json
{
    // See https://go.microsoft.com/fwlink/?LinkId=733558
    // for the documentation about the tasks.json format
     "version": "2.0.0",
     "tasks": [
         {
             "label": "g++ build active file",
             "type": "cppbuild",  // shell
             "command": "g++",
             "args": [
                 "-fdiagnostics-color=always",
                 "-finput-charset=UTF-8",
                 "-fexec-charset=GBK",
                 "-std=c++17",   // C++标准，可以改成 c++11 / c++20
                 "-Wall",
                 "-g",           // 必须加-g，生成调试信息                
                 "${file}",
                 "-o",                 
                 "${fileDirname}\\${fileBasenameNoExtension}.exe"
             ],
             "options": {
                "cwd": "E:/mingw64/bin"
             },                
             "group": {
                 "kind": "build",
                 "isDefault": true
             },
             "problemMatcher": ["$gcc"],
             "detail": "调试器生成的任务。"
         }
    ]
}
```

- `-std=c++17`：指定C++17标准，可以改成`c++11`

- `-g`：生成调试信息（F5断点调试必须）

- `-Wall`：开启警告·

- `-finput‑charset=UTF‑8 -fexec‑charset=GBK`：解决Windows控制台cout中文乱码

### .vscode/launch.json （F5调试）

> 左侧【运行和调试】→创建`launch.json`，选择`C++(GDB/LLDB)`，自动生成`launch.json`
> 
> 修改 `miDebuggerPath` 为你本机 `gdb.exe` 真实路径
> 
> 注意：如果你用 mingw gdb，type为 `cppdbg`；微软 msvc 用 `cppvsdbg`。mingw推荐`"type":"cppdbg"`

```json
{
    // 使用 IntelliSense 了解相关属性。 
    // 悬停以查看现有属性的描述。
    // 欲了解更多信息，请访问: https://go.microsoft.com/fwlink/?linkid=830387
    "version": "0.2.0",
    "configurations": [
        {
            "name": "C++ Debug",
            "type": "cppdbg",
            "request": "launch",
            "program": "${fileDirname}\\${fileBasenameNoExtension}.exe",
            "args": [],
            "stopAtEntry": false,
            "cwd": "${fileDirname}",
            "environment": [],
            "externalConsole": false,
            "MIMode": "gdb",
            "miDebuggerPath": "E:\\mingw64\\bin\\gdb.exe",
            "setupCommands": [
                {
                    "description": "启用gdb整齐打印",
                    "text": "-enable-pretty-printing",
                    "ignoreFailures": true
                }
            ],
            "preLaunchTask": "g++ build active file"
        }
    ]
}
```

### .vscode/c_cpp_properties.json（IntelliSense智能提示、头文件路径）

> `Ctrl+Shift+P` → `C/C++: Edit Configurations (UI)` 生成，用于头文件路径、编译器路径。

修改 `compilerPath` 为你本机 mingw64 的 g++.exe 真实路径，否则头文件飘红。

```json
{
    "configurations": [
        {
            "name": "Win32",
            "includePath": [
                "${workspaceFolder}/**"
            ],
            "defines": [
                "_DEBUG",
                "UNICODE",
                "_UNICODE"
            ],
            "compilerPath": "E:/mingw64/bin/g++.exe",
            "cStandard": "c11",
            "cppStandard": "c++17",
            "intelliSenseMode": "windows-gcc-x64"
        }
    ],
    "version": 4
}
```

### .vscode/settings.json 用户配置

> 文件打开方式：`Ctrl+Shift+P` → 输入 `Preferences: Open User Settings (JSON)`
> 
> 适用：MinGW‑w64 / MSVC，集成 C/C++ 扩展(microsoft C/C++ Extension Pack)，包含格式化、编码、提示、文件关联等常用配置。

```plaintext
{
    // ========== 编辑器基础 ==========
    "editor.fontSize": 16,
    "editor.tabSize": 4,
    "editor.insertSpaces": true,
    "editor.detectIndentation": false,
    "editor.formatOnSave": true,
    "editor.formatOnType": false,
    "editor.wordWrap": "on",
    "editor.rulers": [80, 120],
    "editor.suggest.snippetsPreventQuickSuggestions": false,

    // ========== 文件编码 解决中文乱码 ==========
    "files.encoding": "gbk",
    "files.autoGuessEncoding": true,
    "files.eol": "\r\n",

    // ========== C/C++ 扩展配置 ==========
    "C_Cpp.default.cppStandard": "c++17",
    "C_Cpp.default.cStandard": "c17",
    "C_Cpp.default.intelliSenseMode": "windows-gcc-x64",
    "C_Cpp.autocomplete": "default",
    "C_Cpp.suggestSnippets": true,
    "C_Cpp.errorSquiggles": "enabled",
    "C_Cpp.formatting": "clangFormat",

    // ========== Clang‑Format 格式化规则 ==========
    "C_Cpp.clang_format_style": "{ BasedOnStyle: LLVM, IndentWidth: 4, TabWidth:4, UseTab: Never, ColumnLimit: 120, AccessModifierOffset: -4, BreakBeforeBraces: Attach }",

    // ========== 文件关联，把 .h 识别为 C++头文件 ==========
    "files.associations": {
        "*.h": "cpp",
        "*.hpp": "cpp",
        "*.ipp": "cpp"
    },

    // ========== 排除搜索/索引目录，加快VSCode速度 ==========
    "files.exclude": {
        "**/.git": true,
        "**/.svn": true,
        "**/build": true,
        "**/cmake‑build*": true,
        "**/*.o": true,
        "**/*.exe": true
    },
    "search.exclude": {
        "**/build": true,
        "**/cmake‑build*": true
    },

    // ========== 终端配置 Windows 默认 cmd，避免乱码 ==========
    "terminal.integrated.defaultProfile.windows": "Command Prompt",
    "terminal.integrated.profiles.windows": {
        "Command Prompt": {
            "path": "cmd.exe",
            "args": [],
            "icon": "terminal-cmd"
        }
    },
    "terminal.integrated.allowChords": false,

    // ========== 保存时自动去除行尾空格 ==========
    "files.trimTrailingWhitespace": true,
    "files.trimFinalNewlines": true
}
```

### 扩展：多文件C++项目

比如项目有 `main.cpp`、`func.cpp`、`func.h`
tasks.json的args不能只写 `${file}`（只编译当前打开文件）
args改为：

```json
"args": [
"-finput-charset=UTF-8",
"-fexec-charset=GBK",
"-g",
"-std=c++17",
"${workspaceFolder}/*.cpp",
"-o",
"${workspaceFolder}\\main.exe"
],
```

> `${workspaceFolder}/*.cpp` 编译项目下全部cpp文件，输出main.exe。

### 配套说明

1. **settings.json是**全局用户配置**；c_cpp_properties.json、tasks.json、launch.json放在项目 `.vscode` 文件夹，属于**项目工作区配置**。**

2. 切换编译器：
- MinGW‑w64(gcc/g++)：`intelliSenseMode: windows‑gcc‑x64`
- MSVC(VS cl.exe)：`intelliSenseMode: windows‑msvc‑x64`
3. 中文乱码：
- MinGW编译输出乱码：终端GBK；源码如果是UTF‑8，编译加参数 `-fexec‑charset=gbk`
- MSVC 推荐源码保存 UTF‑8 with BOM。

## 测试代码 main.cpp

```cpp
#include <iostream>
#include <vector>
using namespace std;
int main()
{
cout << "VSCode C++测试：你好！" << endl;
vector<int> arr = {10,20,30,40};
for(auto num : arr)
{
cout << num << " ";
}
cout << endl;
return 0;
}
```

### 操作流程

1. 打开项目文件夹
2. 写 `main.cpp`
3. `Ctrl+Shift+B` → 执行编译，生成 `main.exe`
4. **F5**：启动调试，支持断点、监视变量
5. 运行exe：终端输入 `./main.exe`

## 📌常用操作

1.`Ctrl+Shift+B`：执行编译任务，生成exe

2.`F5`：编译+断点调试，弹出黑窗口运行

3.`Ctrl+` `：调出终端，手动运行：`.\main.exe`

## 常见坑

1.❗只打开单个cpp文件 → `.vscode`配置不生效，**一定要Open Folder打开项目文件夹**

2.项目路径、文件夹名字**不能带中文、空格**

3.头文件红色波浪线：检查 `c_cpp_properties.json` 的 `compilerPath`

4.`miDebuggerPath` / `compilerPath` 路径写错，调试报错找不到gdb/g++

5.没有 `-g` 参数：断点无效，不能调试

6.中文乱码：tasks.json务必带上那两个charset参数

7.调试报错找不到exe：确认编译任务label和launch里面`preLaunchTask`名字完全一致。
