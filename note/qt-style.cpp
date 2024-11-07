

样式表——url路径
    绝对路径  setStyleSheet("background:url(c:/xxx/theme/img.jpg)");
    相对路径  setStyleSheet("background:url(/theme/img.jpg)");或setStyleSheet("background:url(./theme/img.jpg)");
    从QRC中加载 setStyleSheet("background:url(:/theme/img.jpg)"); 可手动编辑xx.qrc文件或通过vs操作。



设置背景图已知有三种方法
  background:url();       //平铺
  background-image:url(); //平铺
  border-image：url();    //拉伸填充

第一种方法可以直接在尾部添加no-repeat阻止图片平铺；第二种则需要添加background-repeat语句：
  background:url() no-repeat;  //阻止平铺
  background-position:center;  //居中
  background-image:url();
  background-repeat:no-repeat; //阻止平铺
在repeat中可以设置repeat-xy来限定横纵方向的平铺。
background-position:center;
background中可以通过top bottom left right center五个关键字设置背景图的位置，也可以通过margin-left和margin-top设定像素位置。
  background-position:top right;//设定在右上方
  margin-left：34；
  margin-top:34px;              //设定背景图左上角坐标在（34，34）位置
暂未找到background-image调整大小的方法，这点存疑。

border-image。它是对图像进行缩放填充，有些细节要记录一下：
border-image最多有5个参数分别是url 上右下左的距离（边框大小）。参数可以省略或部分省略。
  border:40;//等同于下4行
  border-top:40;
  border-right:40;
  border-bottom:40;
  border-left:40;
以上效果是锁定边框的大小。




设置widget背景图片，不影响widget内其他控件背景的方法
https://blog.csdn.net/weixin_55735677/article/details/129612500
在给widget或者frame或者其他任何类型的控件添加背景图时，在样式表中加入如下代码，指定某个控件，设置其背景。
如果单纯改变样式表，没有指定控件的话，内部的其他控件背景也会改变。
特别提醒：类名 # 控件名，其中控件名要准确，假如你把widget的名字改成了其他，那么这里的控件名要一致。
    类名 # 控件名
    {
    填充方式：图片路径
    }

    例如：
    QWidget#Widget
    {
        border-image: url(:/resource/bg2.png);
    }
    或者
    QFrmae#frame
    {
        border-image: url(:/resource/bg2.png);
    }



qt5版本以上的左上角的图标
1 首选可以将需要的图片的格式通过扣扣截图的方式保存成png格式
2 在qt中添加资源，右键-添加新文件-Qt-QtResource File-写上名称 ，如：image
3 添加-添加前缀，去掉/new,然后点击添加-添加文件-选择要添加进去的图片-保存一下，这样就将图片添加进来了。
4 记得在widget.cpp的构造函数中添加一句代码：
    this->setWindowIcon(QIcon(":/prefix1/image/***.png"));//放的是相对路径，注意一下
最后就编译，执行一下就会发现，原本的左上角的图标这时已经发生了改变，变成了你刚刚加载进去的那个图片。



QWidget样式表或背景图片在Qt Designer 中能显示但运行时不显示的解决方法
https://blog.csdn.net/danshiming/article/details/134324523
1. 现象
    在QWidget中贴一张png图片作为背景图或者通过QSS设置背景颜色，在Qt Designer 能显示，但运行时，死活不显示背景图片或背景颜色。样式表设置如下：
    QWidget
    {
        border-image:url(:/untitled2/image/operpanel.png);
    }
    或
    QWidget
    {
        background-color:#FF0000;
    }

2. 解决方法
Qt Designer 中能显示证明图片的路径是正确的，不显示肯定其它问题导致的。
    2.1. 第1种解决方法
    经过排查，在QWidget所在类重写paintEvent函数，如下：
        void Widget::paintEvent(QPaintEvent* event)
        {
            QStyleOption opt;
            opt.init(this);
            QPainter p(this);
            style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
        }
    其中Widget为QWidget的子类，重新编译运行后就可以显示图片了。
    2.2. 第2种解决方法
    如果不是需要直接在Widget（Widget为QWidget的子类）窗体上贴图，可以在Widget的上面套一个QFrame，然后将图片贴到QFrame对象上，
    此frame的样式表如下：
        QFrame
        {
            border-image:url(:/QtWidgetsApplication1/image/back.png);
        }
    此时不需要重写QWidget的paintEvent函数。

3. 总结
如果想直接在QWidget上贴图且能在运行时显示，必须为QWidget窗体设置好样式表，且按2.1节那样重写paintEvent函数。
如果需求不是直接在QWidget上贴图，则可以在QWidget上套个QFrame，让这个QFrame完全铺满盖住QWidget，然后对QFrame设置好背景图的样式表，此时不需要重写QWidget的paintEvent函数。

4. 附录
图片不显示只对整个窗体的背景图时不显示，当图片贴在窗体上的某个部件如：作为按钮贴图，则不会存在这个问题。



Shadow build具体作用
https://blog.csdn.net/cathy18c/article/details/128130618
1 什么是影子构建
就是将源码路径和构建路径分开（也就是生成的makefile文件和其他产物都不放到源码路径），以此来保证源码路径的清洁。
在项目文件夹的同级出现一个带有debug字眼或带有release字眼的文件夹来保存变异的中间和结果文件。

在Build界面上，有一个“Shadow build”复选框。
如勾选，编译后将在项目的同级目录下建立一个编译后的文件目录，目录名称包含编译器信息，这个目录的位置和名字由Build directory指定。
这种方式一般用于使用不同编译器创建不同版本的可执行文件。
如不勾选，生成的debug和release默认将在项目的源代码文件夹内。

2 如何取消影子构建
一般创建项目都是默认就勾选了shadow build，如果不要默认勾选shadow build，以后每次新建项目将不再默认选中影子构建则设置如下
工具->选项->构建与运行->default build properties->default build directory中改为.  (表示当前目录)->确定。




按钮添加图片
1 代码实现，放在构造函数中进行实现

    QIcon icon1;
    icon1.addFile(":/image/Max.png");//添加图形，将加载进来的资源进行保存
    ui->pushButton_4->setMinimumSize(33,33);
    ui->pushButton_4->setMaximumSize(33,33);
    ui->pushButton_4->setIcon(icon1);
    ui->pushButton_4->setIconSize(QSize(28,28));

2 ui->label->setPixmap(QPixmap(":/image/Max.png"));   // 好像是label 添加图片

3 通过ui控件的布局来给界面添加图片
    选中按钮，找到icon，如normal off，选择你想要加载的图片直接点击ok，就可以看到界面上的按钮上已经被直接填充成你的图片。
    注意：这边出现的加载资源和加载文件出现的一个bug，添加资源一定还是要区分是选择资源而不是选择文件
      这种是添加文件，这种添加编译的时候会出现图片，但是打包成release的时候，会发现加载的图片并没有加载进去。


按钮设置成透明
1 选中按钮，样式设计中添加
    border-style:none;
    padding:11px;
    border-radius:3px;
    background:transparent;
2 取消掉flat属性的对勾，此时按钮已经变成透明的，但是在实际运行时点击会出现按钮的形状；
    若要点击时也透明，则需在stylesheet中输入：background:transparent;

3 直接在styleSheet中设置，如：
    QToolButton{
    background-color:rgba(0,0,0,0);
    }
    这样QToolButton就是透明的了，这是在QToolButton的父窗口设置的，这样在这个父窗口下的QToolButton都是透明的。



QLabel颜色的设置（文字、背景）
1 使用调色板QPalettet
    QLabel *label = new QLabel(tr("Hello Qt!"));
    QPalette pe;
    //设置黑底红字
    pe.setColor(QPalette::Background,Qt::black);
    pe.setColor(QPalette::WindowText,Qt::red);
    label->setPalette(pe);

2 使用QT样式表(QSS)直接设置
    ui->label->setText("");
    //ui->label->setStyleSheet("color:red;");
    //设置指定背景色
    ui->label->setStyleSheet("QLabel{background-color:rgb(200,101,102);}");



QLineEdit边框属性
    border-style: outset;
    border-width: 2px;
    border-color: green;
    外框 2像素宽 绿色





