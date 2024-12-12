

https://download.qt.io/                                    # 官方下载


编译qt4.8.6 64位
http://clatfd.cn/a/208    qt 4.8.6 64 bit compilation note   Posted on 2016-07-16 by admin 1161 0
Cited from http://www.tuicool.com/articles/JFF3Ar
QT4 has no pre-compiled 64 bit VS version. When compiling projects with qt4 in 64 bit mode, there will be a linking error for the incompatible library, such as Qtgui4.lib. As there is nowhere to download such outdated qt4 precompiled version for VS (Qt 5 is supported in 64 bit), so the only way is to build by myself.
qt-everywhere-opensource-src-4.8.6.tar.gz   Download from https://download.qt.io/archive/qt/4.8/4.8.6/
1 Decompress
2 Open VS 64 bit command tool in software installation tools
3 Enter the Qt directory
  configure -platform win32-msvc2010 -opensource -fast -qt-style-windowsxp -qt-style-windowsvista -no-qt3support -qt-sql-odbc -no-phonon -no-phonon-backend -no-script -no-scripttools -no-multimedia -nomake examples -nomake demos
  nmake
  nmake install
The compilation takes up to hours


Qt 4.8.5 Windows/Ubuntu下x64编译
https://blog.csdn.net/lonelysky/article/details/53144820
Windows
环境准备：
1.Visual Studio 2010（Visual Studio 2008需要在安装的时候勾选x64工具包，安装上的x64工具包是beta版本的，不知道会不会有BUG，我只是编译了一下）；
2.Windows机器上一定要有Perl，否则编出来的东西不能用，assistant之内的全都没法打开；我安装的是ActivePerl 5.24 x64；
3.QT安装包解压在C:\Qt\4.8.5。保证存在C:\Qt\4.8.5\configure.exe
步骤：
1.修改源码C:\Qt\4.8.5\src\3rdparty\webkit\Source\WebCore\platform\DefaultLocalizationStrategy.cpp，在325行和327行有个BUG，把里面中文的引号改成\"；      "
2.从开始菜单打开Visual Studio x64 Win64 Command Prompt (2010)；
3.cd C:\Qt\4.8.5
4.set PATH=C:\Qt\4.8.5\bin;%PATH%
5.执行configure.exe，后面的参数根据需要增加；完成之后会生成C:\Qt\4.8.5\bin\qmake.exe
6.然后运行nmake就行了
7.编译完成后C:\Qt\4.8.5\bin\中会有很多动态库，以及designer.exe、assistant.exe等程序
8.运行nmake clean把其中的中间文件清一清，剩下的就可以和产品发布了

Ubuntu
Ubuntu比较麻烦，下面的方法在16.04和16.10测试通过
1.首先需要通过apt-get安装一堆依赖项，如果不是上面的两个版本，那么你要先查询下面的软件包在不在，16.0x直接安装就ok
sudo apt-get install build-essential libx11-dev libxau-dev libxaw7-dev libxcb1-dev libxcomposite-dev libxcursor-dev libxdamage-dev libxdmcp-dev libxext-dev libxfixes-dev libxfont-dev libxft-dev libxi-dev libxinerama-dev libxkbfile-dev libxmu-dev libxmuu-dev libxpm-dev libxrandr-dev libxrender-dev libxres-dev libxss-dev libxt-dev libxtst-dev libxv-dev libxvmc-dev libglib2.0-dev  libglib2.0-dev libgtk2.0-dev libcups2-dev libgl1-mesa-dev libglu1-mesa-dev libgstreamer1.0-dev libgstreamer-plugins-base1.0-dev
2.解压代码到$HOME下面
tar zxvf qt-everywhere-opensource-src-4.8.5.tar.gz
如果g++版本太高的话（比如16.04和16.10自带的版本，都TM的6.2了），会在编译中途报错，包std::tr1中的部分内容找不到。修改qt目录下的mkspec/linux-g++/qmake.conf，在QMAKE_CFLAG = -m64下面增加一行QMAKE_CXXFLAGS += -std=gnu++98
3.到qt目录下运行configure，注意把安装路径带上
cd $HOME/qt-everywhere-opensource-src-4.8.5
./configure -prefix /usr/local/Qt-4.8.5
4.然后执行make
5.然后执行sudo make install
6.环境变量什么的这里就不说了，按需配置






