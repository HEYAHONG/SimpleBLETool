# ***仅供测试***

# 说明

这是一个利用[SimpleBLE](https://github.com/OpenBluetoothToolbox/SimpleBLE) 获取BLE设备信息的测试工具。

## 使用条件

具体使用条件见SimpleBLE的说明,通常情况下使用条件如下:

- Windows 10+
- ubuntu20.04+

## 源代码下载

由于本源代码包含第三方源代码,故直接下载可能有部分源代码缺失，需要通过以下方法解决:

- 在进行git clone 使用--recurse-submodules参数。

- 若已通过git clone下载,则在源代码目录中执行以下命令下载子模块:

  ```bash
   git submodule update --init --recursive
  ```
# 编译

本工程主要依赖[wxWidgets](https://www.wxwidgets.org/)库。

需要提前安装好的工具(所有平台都需要提前安装)：

- git:用于源代码下载及cmake脚本中的调用。
- CMake：生成工程文件。

主要测试的操作系统平台为Windows 10+与Ubuntu 20.04+。

## Windows 10+

注意:各个架构的系统只能用各个架构的可执行文件,如x86_64架构的系统只能用x86_64版exe,不能用x86版exe(可执行但不能正常工作)。

- 安装好visual studio最新版,安装好C++开发环境及最新的windows sdk。进入visual studio开发者命令提示符（开始菜单中,下列所有命令均应当在此提示符窗口中运行）。
- 下载wxWidgets并编译安装。
- 使用CMake生成工程文件。(可能需要使用CMake-gui修改wxWidgets库安装路径)
- 编译

## ubuntu 20.04+

安装好编译环境及wxWidgets库、DBus1库即可正常编译。

若CMake版本过低,可能需要下载最新的CMake源代码进行编译安装。

