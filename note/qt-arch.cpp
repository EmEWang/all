

http://download.qt.io/archive/                          #
https://download.qt.io/static/mirrorlist/               # 镜像列表  点击Mirroe列的HTTP进去
https://mirror.bjtu.edu.cn/qt/development_releases/qt/  # 提供部分老本版的下载
https://blog.csdn.net/u014252478/article/details/80755456  # QT之qt4.8.6安装(详细教程)


vsaddin是VisualStudio集成插件，qtcreator是Qt官方的集成开发环境，qt就是各种新老版本下载位置，online_installers就是在线安装工具。
Qt4开发环境包括3个基本部分：Qt Framework(Qt库)、QtCreator(IDE)和MinGW(编译调试)，都要分别下载安装并配置，比较麻烦。
进入Qt5之后，Qt公司将三者打包成一个安装文件
Qt库需要MinGW，qtcreator需要配置前面二者，所以先安装MinGW，再安装qt-opensource-windows-x86-mingw482-4.8.6-1，最后装QtCreator。


ubuntu16
wjg@ubuntu:~/qt/Qt5.12.12/Tools/QtCreator/bin$ ./qtcreator
qt.qpa.plugin: Could not load the Qt platform plugin "xcb" in "" even though it was found.
This application failed to start because no Qt platform plugin could be initialized. Reinstalling the application may fix this problem.
Available platform plugins are: eglfs, linuxfb, minimal, minimalegl, offscreen, vnc, xcb.
Aborted (core dumped)

sudo apt-get install libxcb-xinerama0      #   安装完qt5.12  运行qtcreator    出现以上错误



ubuntu16编译qt 出现 cannot find -lgl 错误
sudo apt-get install build-essential libgl1-mesa-dev     # qt5依赖库



解决 At least one valid and enabled repository required for this action to succeed 问题的办法
https://blog.csdn.net/weixin_44916154/article/details/124839272
使用 MaintenanceTool 工具对已安装的 Qt 进行卸载、修复等其他操作时，会遇到所示的问题，导致无法继续
单击窗口左下角的图标
在新的窗口中，选中 Repositories 一栏
在 Repositories 一栏中，选中 Temporary respositories，然后单击左下角的 Add
接下来把下面的网址粘贴到 Repository 一栏，记得不要粘贴到 Username 或 Password 处，最后单击 OK，回到初始窗口，便可以继续进行操作了
  如 https://mirrors.tuna.tsinghua.edu.cn/qt/online/qtsdkrepository/windows_x86/root/qt/



Qt 规定：任何对于 GUI 上内容的操作必须在主线程中完成。像 Widget 构造函数，以及 connect 连接的 slot 函数，都是在主线程中调用的。
  而我们自己创建的线程则不是，当我们自己的线程中尝试对界面元素进行修改时，Qt 程序往往会直接崩溃。



QObject是以对象树的形式组织起来的：创建 QObject 对象时，提供一个其父对象，则创建的这个 QObject 对象会自动添加到其父对象的 children()列表。
  当父对象析构的时候，这个列表中的所有对象也会被析构。(注：这里的父对象并不是继承意义上的父类)

所谓信号槽，类似观察者模式：当发生了感兴趣的事件，某一个操作就会被自动触发。
  如按钮检测到自己被点击了一下，它就会发出一个信号(signal)。这种发出是没有目的的，类似广播。
  如有对象对这个信号感兴趣，它就会使用连接(connect)函数，将想要处理的信号和自己的一个函数(称为槽slot)绑定来处理这个信号。
  也就是说，当信号发出时，被连接的槽函数会自动被回调。

Q_OBJECT宏的作用
  只有加入了Q_OBJECT，才能使用QT中的signal和slot机制，而且Q_OBJECT要放在类的最前面
  元对象编译器 moc对 C++ 文件中的类声明进行分析并产生用于初始化元对象的 C++ 代码，元对象包含全部信号和槽的名字以及指向这些函数的指针。
moc(meta object compiler) 读 C++ 源文件，如果发现有 Q_OBJECT 宏声明的类，它就会生成另外一个 C++ 源文件，这个新生成的文件中包含有该类的元对象代码。如有一个头文件 mysignal.h，在这个文件中包含有信号或槽的声明，那么在编译之前 moc 工具就会根据该文件自动生成一个名为 mysignal.moc.h 的 C++ 源文件并将其提交给编译器；同样 mysignal.cpp 文件 moc 工具将自动生成一个名为 mysignal.moc.cpp 文件提交给编译器。
元对象代码是 signal/slot 机制所必须的。用 moc 产生的 C++ 源文件必须与类实现一起进行编译和连接，或者用 #include 语句将其包含到类的源文件中。moc 并不扩展 #include 或者 #define 宏定义 , 它只是简单的跳过所遇到的任何预处理指令。



Qt Creator以工程项目的方式对源码进行管理
一个Qt Craetor工程包含不同类型的文件
  .pro项目描述文件 实质上是Makefile文件
  .pro.user用户配置描述文件
  .h头文件
  .cpp源文件
  .ui界面描述文件
  .qrc资源文件；使用 : 开头，表示从 qrc 中读取资源  / 是上面配置的前缀；qrc 中导入的资源会被转成这个 qrc_resource.cpp(自动生成)这个 c++ 代码，通过 unsigned char 数组，把资源中的每个字节都记录下来。这些代码会被编译到 exe 中，后续无论 exe 被复制到哪个目录下都确保能够访问到该图片资源。缺点：不适合管理体积大的资源。
注意：
  1、Qt Creator在打开项目文件的同时会生成.pro.user文件
  2、.pro.user文件包含一些与Qt相关的本地配置信息
  3、当需要在不同计算机之间移动项目源码时，建议删除.pro.user文件



QT       += core gui              # 模块声明 core模块 gui模块
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets    # 如果使用QT版本大于4，那么需要告诉QT，还需要widgets模块
TARGET = test1                    # 可执行文件名
TEMPLATE = app                    # test1是一个app，可执行程序
SOURCES += main.cpp\              # 源文件
        mainwindow.cpp
HEADERS  += mainwindow.h          # 头文件
FORMS    += mainwindow.ui         # 界面描述文件.ui
RESOURCES += image.qrc            # 资源文件
CONFIG += c++11                   # 设定项目的配置信息和编译选项，这里是添加了c++11标准



qtcreator编译过程的原理：
xx.pro(里面会包含xx.qrc项)通过qmake.exe，得到 debug同级目录的 Makefile, Makefile.Debug, Makefile.Release，
然后make.exe再读取Makefile文件进行源码的编译，得到 debug目录里面的各种 xx.o文件(这里就包含了qrc_xx.o)，然后链接成最后的 xx.exe可执行文件。
因此，要想更新这个资源文件 qrc_xx.o ，那么就要让qmake重新生成这几个Makefile。但qtcreator有时候也不知道咋的，就是不能重新生成这些Makefile，
所以需要去这个目录，手动删除它们(为了解决资源文件问题，还可以xx_resource.rc文件也给删除了)，然后构建项目，就可以了。
如果连 qrc_xx.o 文件都生成不了，那么就去资源文件里看看是不是有些文件路径不存在，或者文件无效的，因为这样也会导致qt生成不了qrc_xx.o 从而报错。

creator ui界面修改后运行不产生作用(本质分析)
https://biao2488890051.blog.csdn.net/article/details/127344329?spm=1001.2014.3001.5502
解决方法：删除Makefile文件即可。原因应该是ui_xx.h文件没有被gcc编译到。
本质分析
1. 界面可视化设计原理
编辑可视化界面，如对应的是 mainwindow.ui 文件(xml格式)，用这个格式来对界面进行描述。
qtcreator编译过程中，把这个xml文件转换为 ui_mainwindow.h文件(用的qt自己的uic工具)，这个就是纯c++语法文件了。
里面定义了一个Ui命名空间，Ui里定义了两个类，Ui_MainWindow和MainWindow，MainWindow继承Ui_MainWindow，代码如下：
namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui
注意：这里面的MainWindow类跟我们自定义的MainWindow类，不是同一个类，因为它们不在一个命名空间中。
所以引用Ui里面的这个类，需要这样 Ui::MainWindow
然后这个Ui::MainWindow类作为我们自己的MainWindow类(比如)的一个成员存在。结构图如下：
MainWindow ----| Ui::MainWindow    ←--------- MainWindow
    |         -| mVariable1                       |
    |         -| mVariable2                       |
    ▽                                            ▽
QMainWindow                                  Ui_MainWindow

2. 项目文件编译原理
主要分为3步，看下面图就清楚了
MainWindow.ui   --- 2) Qt的uic工具 -->  ui_mainwindow.h  -|
                                        mainwindow.h     -| ------ 3) gcc编译器 ------> mainwindow.exe
                                        mainwindow.cpp   -|          ↗
                                                                   /
mainwindow.pro  --- 1) Qt的qmake工具  ----->   makefile文件 -------

3. 解决问题步骤如下
因此，修改了xx.ui文件，运行不奏效，查问题步骤如下：
3.1 因此首先看看.pro文件里是否包含这个xx.ui文件，因为这个能告诉creator将它编译成ui_xx.h文件。如果没有，那么问题就在这里了，加上即可。
3.2 打开ui_xx.h文件查看，如果该文件里确实是我们修改了控件的代码，说明creator将xx.ui文件转换(用的自己的uic工具)成功了的。否则，问题就在这里了，那么删除这个文件即可(直接在菜单栏的菜单项： 构建->清除 选项，可以快捷删除所有这些上次编译产生的文件，但是也要去这个文件夹里看看，防止没有删干净，因为qtcreator还是有点bug的)，因为qt creator再编译时候会自动生成这个文件。
3.3 既然ui_xx.h文件本身没有问题，那么就是说明creator在正式编译(gcc)时候没有编译到ui_xx.h文件，而这个过程是由makefile文件提供的编译信息，来对编译过程进行控制的。所以我们需要对这个makefile重新生成，该文件是由.pro文件用qmake工具生成的(所以可以用菜单栏的菜单项： 构建->执行qmake 选项)，也就是上面的图中的第1步。
注意：这里也有点奇怪的地方，即使执行qmake了，但是仍然可能不能真的更新这个makefile文件，那么直接去构建结果目录，把Makefile，Makefile.Debug，Makefile.Release这3个文件手动删除即可，此时qmake就会全新的生成它们了。
经过上面的步骤，再点击重新构建，或者直接构建，一般都能解决了。
此外，还有一个要注意：如果debug目录下的文件都删了，还是不行，注意看看项目源码根目录下(因为曾经采用过影子编译目录啥的，历史遗留)是不是也有大量的 .o文件，以及UI_XX.h文件，Makefile文件，这些文件被用作编译了，全部给删除，就好了。




QT5.12.12 HTTPS请求 TLS initialization failed
D:\tool\qt\Qt5.12.12\5.12.12\mingw73_32\bin  # 直接运行时 缺少
D:\tool\qt\Qt5.12.12\Tools\mingw730_32\bin   # creator下运行 缺少
libcrypto-1_1.dll libeay32.dll libssl-1_1.dll ssleay32.dll




qt中添加多个UI界面，并在其他文件中调用该UI界面
1 ui界面的创建 右键项目->Add new->Qt->Qt设计师界面类->...  分别会创建 xx.h xx.cpp xx.ui
2 将xx.h 的ui对象由private更改为public
3 在需要调用的文件中添加头文件，xx.h和ui_xx.h,前者是为了能够调用新的ui类对象，后者是为了能够调用新ui当中的控件。 (本人使用只需要第一个)
4 在要调用的文件中创建新的ui界面类对象，就可以使用新的ui界面了。xx l = new xx;...



资源文件错误：No rule to make target ‘../??.png‘, needed by ‘debug/qrc_icon.cpp‘. Stop.   QT版本：5.12
原因：资源文件中包含中文命名的图片文件。
解决办法：
  方法1：在资源文件中重命名含有中文名的图片文件，执行qmake，重新构建；
  方法2：将含有中文命名的图片文件从资源文件中移除，执行qmake，在重新添加有中文图片的文件，再重新编译就不会出错了。


错误：No rule to make target ‘../‘, needed by ‘debug/qrc_res (资源文件没有更新)的原理和解决方法
问题分析：资源文件  resource.qrc 已经编译生成，在resource资源目录下进行删除不能改变已经编译生成的 resource.qrc 所以会出现此类错误。
解决方法：项目右键执行qmake即可，然后重新构建，解决。



QObject::connect(const QObject *sender, const char *signal,const QObject *receiver,const char *method, Qt::ConnectionType type = Qt::AutoConnection)
// 信号与槽的连接方式决定槽函数调用时候的相关行为！
  信号(Signal):是在特定情况下被发射的事件，如PushButton的clicked()信号，ComboBox的CurrentIndexChanged()信号。
  槽(Slot):是对信号响应的函数。与一般的C++函数是一样的，可以定义在类的任何部分(public/private/protected)，可以具有任何参数，也可以被直接调用。
    槽函数与一般的函数不同的是：槽函数可以与一个信号关联，当信号被发射时，关联的槽函数被自动执行。
  一个信号可以连接到多个槽，多个信号可以连接到一个槽，多个信号可以连接到多个槽
  槽函数的参数不能多于信号的参数。信号的参数可以多于槽的参数，且槽函数的参数必须是信号参数的一个子集。
    1 信号和槽函数具有相同数量和类型的参数。这时可以直接连接且无需出现函数参数：connect(lineEdit, &QLineEdit::textChanged, this, &Widget::do_textChanged);
    2 信号的参数多于槽函数的参数。槽函数将忽略信号的多余参数，这个特性允许在信号和槽参数不完全匹配的情况下，仍然能够正常工作。正常情况下，不推荐把槽函数设计为overload型。
    3 某些信号的参数有默认值。也就是说同一信号的参数分为有参数和无参数，如QCheckBox的clicked()信号和clicked(bool)信号。这时connect()函数有两种写法：
      3.1 设置不同名字的槽函数
        //槽函数
        void do_checked(bool checked);
        void do_checked_NoParam();
        //connect()函数
        connect(checkBox, &QCheckBox::clicked, this, &Widget::do_checked);
        connect(checkBox, &QCheckBox::clicked, this, &Widget::do_checked_NoParam);
      3.2 使用模板函数qOverload()来明确参数类型：
        connect(checkBox, &QCheckBox::clicked, this, qOverload<bool>(&Widget::do_checked));
        connect(checkBox, &QCheckBox::clicked, this, qOverload<>(&Widget::do_checked));
    4 自动连接(无需使用connect()函数)
        在构建项目时，若勾选了“Generate form”字段，则会生成一个后缀为“.ui”的文件。
        在ui设计界面种可以选中一个对象，右键选择“Go to slot”或者“转到槽”，在弹出的对话框中再选择信号，那么就会自动生成一个槽函数。
        如果槽函数的名称符合相应的格式，Qt 会在运行时通过setupUi(this)自动生成connect()函数完成连接。
        当然在设计一些复杂功能时，自动连接方法就不太适用了。
    5 Lambda表达式(Qt5.4)
        基本格式 connect(sender, &SenderClass::signalName, [lambda expression]);

  1  QT4.0最为传统的方法
    connect(ui->pushButton_1,SIGNAL(clicked()),this,SLOT(on_pushButton_11_clicked()));
  2  QT5.0之后推出来的绑定方法，去掉了之前的宏
    connect(ui->pushButton_2,&QPushButton::clicked,this,&::MainWindow::on_pushButton_21_clicked);
  3  C++11出来之后，新的特性就出来，static_cast 用法
    //connect(ui->pushButton_3,static_cast<void (QPushButton::*)(bool)>(&QPushButton::clicked), this, SLOT(on_pushButton_31_clicked())); 注意这样不行
    connect(ui->pushButton_3,static_cast<void (QPushButton::*)(bool)>(&QPushButton::clicked), this, &::MainWindow::on_pushButton_31_clicked);
      //第2参数转换其实是一个函数指针，等价下面的代码
      //void (QPushButton::*ff)(bool)=&QPushButton::clicked;
      //connect(ui->pushButton_3, ff, this, &::MainWindow::on_pushButton_31_clicked);
  4 使用模板函数qOverload()
    connect(ui->pushButton_4, QOverload<bool>::of(&QPushButton::clicked),this,&::MainWindow::pushButon4_clicked);
  5  lamda表达式 不需要去定义槽函数
    connect(ui->pushButton_5, QOverload<bool>::of(&QPushButton::clicked),[=](){ui->textEdit->setText("按钮5");});
    //connect(ui->pushButton_5, static_cast<void (QPushButton::*)(bool)>(&QPushButton::clicked), this, [=](bool check){ui->textEdit->setText("按钮5");});

  第5个参数，只是一般使用默认值
  每一个线程都有自己的事件队列 ，线程通过事件队列接收信号 ，信号在事件循环中被处理
    Qt::AutoConnection：默认值，使用这个值则连接类型会在信号发送时决定。
      如果接收者和发送者在同一个线程，则自动使用Qt::DirectConnection类型。如果接收者和发送者不在一个线程，则自动使用Qt::QueuedConnection类型。
    Qt::DirectConnection：立即调用，槽函数在信号发送的时候直接被调用，槽函数运行于信号发送者所在线程。效果就像是直接在信号发送位置调用了槽函数。
      直接在发送信号的线程中调用槽函数，等价于槽函数的实时调用
      这个在多线程环境下比较危险，可能会造成奔溃。不在同一个线程用这个，也可能导致另一个线程槽函数始终不响应。
    Qt::QueuedConnection：异步调用，槽函数在控制回到接收者所在线程的事件循环时被调用，槽函数运行于信号接收者所在线程。
      信号发送至目标线程的事件队列，由目标线程处理；当前线程继续向下执行。
      发送信号之后，槽函数不会立刻被调用，等到接收者的当前函数执行完，进入事件循环之后，槽函数才会被调用。多线程环境下一般用这个。
    Qt::BlockingQueuedConnection：槽函数的调用时机与Qt::QueuedConnection一致，不过发送完信号后发送者所在线程会阻塞，直到槽函数运行完。
      信号发送至目标线程的事件队列，由目标线程处理； 当前线程等待槽函数返回，之后继续向下执行。
      接收者和发送者绝对不能在一个线程，否则程序会死锁。在多线程间需要同步的场合可能需要这个。
    Qt::UniqueConnection：这个flag可以通过按位或(|)与以上四个结合在一起使用。
      功能与AutoConnection相同，自动确定连接类型。当这个flag设置时，当某个信号和槽已经连接时，再进行重复的连接就会失败。也就是避免重复连接。
      同一个信号与同一个槽函数之间只有一个连接 (默认，同一个信号可以多次连接到同一个槽函数，多次连接意味着同一个槽函数的多次调用 )


disconnect 断开连接
  1 解除与一个发射者所有信号的连接
    disconnect(myObject, nullptr, nullptr, nullptr);
    myObject->disconnect();
  2 解除与一个特定信号的所有连接
    disconnect(myObject, SIGNAL(mySignal), nullptr, nullptr);
    myObject->disconnect(SIGNAL(mySignal));
  3 解除与一个特定接收者的所有连接
    disconnect(myObject, nullptr, myReceiver, nullptr);
    myObject->disconnect( myReceiver);
  4 解除特定的一个信号与槽的连接
    disconnect(lineEdit, &QLineEdit::textChanged, label, &QLabel::setText);




QEvent
1 事件(event)是由系统或者Qt本身在不同的时刻发出的。当用户按下鼠标、敲下键盘，或者是窗口需要重新绘制的时候，都会发出一个相应的事件。
  一些事件在对用户操作做出响应时发出，如键盘事件等;另一些事件则是由系统自动发出，如计时器事件。
Qt中所有事件类都继承于QEvent，event()函数并不直接处理事件，而是按照事件对象的类型分派给特定的事件处理函数。
EventLabel::mouseMoveEvent(QMouseEvent *event){
    this->setText(QString("<center><h1>Move: (%1, %2)</h1></center>").arg(QString::number(event->x()),QString::number(event->y())));}

2 event()函数主要用于事件的分发。如果希望在事件分发之前做一些操作，就可以重写这个 event()函数。
如果传入事件分发器的事件已被识别并且处理，则需要返回 true，否则返回false。
  返回值是 true，Qt 会认为这个事件已经处理完毕，不会再将这个事件发送给其它对象，而是会继续处理事件队列中的下一事件。
在event()函数中，调用事件对象的accept()和ignore()函数是没有作用的，不会影响到事件的传播。

在一个QWidget组件中监听 tab 键的按下，那么就可以继承QWidget，并重写它的event()函数，来达到这个目的：
bool CustomWidget::event(QEvent *e){
    if (e->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(e);
        if (keyEvent->key() == Qt::Key_Tab) {
            qDebug() << "You press tab.";
            return true;
        }
    }
    return QWidget::event(e);
}


事件过滤器
  virtual bool QObject::eventFilter ( QObject * watched, QEvent * event );
  事件过滤器会检查接收到的事件。如果这个事件是我们感兴趣的类型，就进行我们自己的处理；如果不是，就继续转发。
  这个函数返回一个 bool 类型，不想让它继续转发，就返回 true，否则返回 false。
  事件过滤器和被安装过滤器的组件必须在同一线程创建，否则，过滤器将不起作用。
  另外，如果在安装过滤器之后，这两个组件到了不同的线程，那么，只有等到二者重新回到同一线程的时候过滤器才会有效。

事件过滤器例子 textEdit 只处理按键操作
class MainWindow : public QMainWindow{
public:
    MainWindow();
protected:
    bool eventFilter(QObject *obj, QEvent *event);    //重载事件过滤
private:
    QTextEdit *textEdit;
};
MainWindow::MainWindow(){
    textEdit = new QTextEdit;
    setCentralWidget(textEdit);
    textEdit->installEventFilter(this);              // 安装过滤器
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event){
    if (obj == textEdit) {
        if (event->type() == QEvent::KeyPress) {
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
            qDebug() << "Ate key press" << keyEvent->key();
            return true;
        } else {
            return false;
        }
    } else {
        // pass the event on to the parent class
        return QMainWindow::eventFilter(obj, event);
    }
}

消息事件机制和信号和槽机制的关系
  1.两者都是Qt中的通讯机制
  2.信号和槽被用于程序内对象之间的通信，也是一种程序回调机制(框架在适当时机调用)。
  3.事件不仅有程序内部产生的，也有程序外部、系统产生的，如：鼠标、键盘、定时器事件
  4.信号和槽都是函数，当某个信号发生了就调用相关联的槽函数。
  5.事件是对象，代表着一条消息。其他对象接收到这个事件要对这个事件做相应的处理，也可以不做任何处理。
  6.消息事件比信号槽更底层，一般Qt中的标准信号会是某些消息事件处理的结果，如：鼠标移动到按钮上，按钮一直收到鼠标移动的事件，可是按钮没有做任何处理，但是只要当鼠标点击按钮，按钮就会收到一个鼠标点击的事件，他会处理这个事件并且主动去发送一个被点击的信号clicked，这时候相关联的槽函数就会被调用。
Qt 程序需要在main()函数创建一个QApplication对象，然后调用它的exec()函数。这个函数就是开始 Qt 的消息事件循环，不断地处理收到的消息事件。当事件发生时，Qt框架将创建一个事件对象。Qt中所有事件类都继承于QEvent。在事件对象创建完毕后，Qt 将这个事件对象传递给QObject的event()函数。event()函数并不直接处理事件，而是按照事件对象的类型分派给特定的事件处理函数(event handler)。



总结
event()函数会有两个问题：
  1.event()函数是一个 protected 的函数，这意味着我们要想重写event()，必须继承一个已有的类。试想，我的程序根本不想要鼠标事件，程序中所有组件都不允许处理鼠标事件，是不是我得继承所有组件，一一重写其event()函数？protected 函数带来的另外一个问题是，如果我基于第三方库进行开发，而对方没有提供源代码，只有一个链接库，其它都是封装好的。我怎么去继承这种库中的组件呢？
  2.event()函数的确有一定的控制，不过有时候我的需求更严格一些：我希望那些组件根本看不到这种事件。event()函数虽然可以拦截，但其实也是接收到了QMouseEvent对象。我连让它收都收不到。这样做的好处是，模拟一种系统根本没有那个事件的效果，所以其它组件根本不会收到这个事件，也就无需修改自己的事件处理函数。这种需求怎么办呢？
这两个问题是event()函数无法处理的。于是，Qt 提供了另外一种解决方案：事件过滤器。

事件过滤器可以解决刚刚我们提出的event()函数的两点不足：
  1.首先，事件过滤器不是 protected 的，因此我们可以向任何QObject子类安装事件过滤器；
  2.其次，事件过滤器在目标对象接收到事件之前进行处理，如果我们将事件过滤掉，目标对象根本不会见到这个事件。

事实上，Qt 事件的调用最终都会追溯到QCoreApplication::notify()函数，因此，最大的控制权实际上是重写QCoreApplication::notify()。
virtual bool QCoreApplication::notify ( QObject * receiver, QEvent * event );
该函数会将event发送给receiver，也就是调用receiver->event(event)，其返回值就是来自receiver的事件处理器。
注意，这个函数为任意线程的任意对象的任意事件调用，它不存在事件过滤器的线程的问题。不推荐这么做，因为notify()函数只有一个，而事件过滤器要灵活得多。


总结一下 Qt 的事件处理，实际上是有五个层次：
  1.重写paintEvent()、mousePressEvent()等事件处理函数。这是最普通、最简单的形式，同时功能也最简单。
  2.重写event()函数。event()函数是所有对象的事件入口，QObject和QWidget中的实现，默认是把事件传递给特定的事件处理函数。
  3.在特定对象上面安装事件过滤器。该过滤器仅过滤该对象接收到的事件。
  4.在QCoreApplication::instance()上安装事件过滤器。该过滤器将过滤所有对象的所有事件，因此和notify()函数一样强大，但是它更灵活，因为可以安装多个过滤器。全局的事件过滤器可以看到 disabled 组件上面发出的鼠标事件。
  5.重写QCoreApplication::notify()函数。这是最强大的，和全局事件过滤器一样提供完全控制，并且不受线程的限制。但是全局范围内只能有一个被使用(因为QCoreApplication是单例的)。




重写QWidget方法  监听鼠标滚轮+ctrl
void XXXX::wheelEvent(QWheelEvent * Event){
    if ((Event->modifiers() == Qt::ControlModifier) && (Event->delta() > 0)){xx;}
    else if ((Event->modifiers() == Qt::ControlModifier) && (Event->delta() < 0)){xx;}
}


过滤事件  监听鼠标滚轮+ctrl
this->installEventFilter(this);             // 注册监视对象

bool eventFilter(QObject *obj, QEvent *ev){
    if (ev->type() == QEvent::Wheel ){      //滚轮事件
        if (QApplication::keyboardModifiers () == Qt::ControlModifier){  // 判断 Ctrl 是否按下
            return true;
        }
    }
    return __super::eventFilter(obj,ev);
}

bool XX::eventFilter(QObject *obj, QEvent *e){
    if (e->type() == QEvent::Wheel){                         // 滚轮事件
        QWheelEvent *wheelEvent = static_cast<QWheelEvent *>(e);
        if (wheelEvent->modifiers() == Qt::ControlModifier){ // 判断修饰键 Ctrl 是否按下
            QSize size = page->size();
            if(wheelEvent->delta() > 0)                      // delta为负向上滚动 delta为正向上滚动
                xx;
            else
                xx;
            return true;
        }
        else{
            if(wheelEvent->orientation() == Qt::Vertical){   // 垂直滚动
                return scrollWidget->verticalScrollBar()->event(wheelEvent);
            }
            else if (wheelEvent->orientation() == Qt::Horizontal){ // 水平滚动
                return scrollWidget->horizontalScrollBar()->event(wheelEvent);
            }
        }
        else if (obj == this){
            return obj->event(e);
        }
    }
    else if (e->type() == QEvent::KeyPress){                 // 键按下
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(e);
        if ((keyEvent->key() == Qt::Key_0) && (keyEvent->modifiers() == Qt::ControlModifier)){
            reshow(this->size());
            return true;
        }
    }

    return obj->event(e);
}






