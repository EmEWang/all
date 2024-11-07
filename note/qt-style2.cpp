

https://doc.qt.io/qt-5/stylesheet-examples.html                 # 官网
https://encycolorpedia.cn/                                      # 十六进制颜色码
https://blog.csdn.net/qq_42250189/article/details/105199339
https://blog.csdn.net/qq_41719595/article/details/117337855

setStyleSheet() 设置样式表
样式表语法：样式表语法基本和HTML CSS语法一致。样式表包含了样式规则序列，样式规则由一个<selector>和<declaration>组成，<selector>指定哪些窗口将会被这些规则影响，<declaration>指定哪些属性将会被设定在窗口上，例如QPushButton{color:red}。

在上面的规则中，QPushButton是<selector>，{color:red}是<declaration>，这个规则指定QPushButton和他的子类将使用红色作为前景颜色，就是字体颜色，并且对大小写没有分别，对于color，ColoR,COLOR是一样的。

几个<selector>可以同时被列出，使用逗号 , 来分开各个<selector>，例如：QPushButton, QLineEdit, QComboBox { color: red };<declaration>部分包含多对属性值 对，用{}来括起来，使用分号来分开各个属性。例如QPushButton { color: red; font-family: Arial; line-height: 26px;”}


常见的selector
https://www.jianshu.com/p/a0d07cee178b
classname 用控件类名作为selector，这种主要用在控件之间可以用类名来区别的情况下。
QPushButton{
    border-radius:2px;
    color:#FF0000;
}
QLineEdit{
  max-width:20px;
  min-width:20px;
}

classname + #objectname 类名和属性名称，这种主要用在界面上有多个相同的控件，但又需要各自控件有不同的属性，在代码中为需要设置样式的控件用setobjectname方法加以区别。
QPushButton #tabButton{
  border-bottom:2px solid #FF0000;
  font-weight:bold;
}
QPushButton #refresh{
  border:0px;
  border-radius:2px;
}

#objectname 直接当前对象的样式，如
refresh{
  border:0px;
  border-radius:2px;
}

派生选择 classname drivedclass{} 要求classname 是 drivedclass的父类，该样式只对drivedclass 这种控件有效果
basewidget QPushButton{
  color:#FF0000;
}

属性选择 classname[property=value]{} 其中property是classname 中用setproperty设置的属性，当满足这一属性条件时候显示这种样式，如果在运行的时候属性变了，需要重新加载样式，用classname->setStyle()重新加载样式。
QPushButton[state="2"]{
  border:0px;
  border-radius:0px;
}





部分declaration
样式-英文                  参数                                  样式-中文
color:                    white rgb(110,110,110) #eb7350        前景颜色，字体颜色
background:               transparent                           背景为透明（背景可以为图片等）
background-color:         white rgb(110,110,110) #eb7350        背景颜色（只能为颜色）
background-position:      left right center top bottom          设定图片的位置
background-image:         url() ./img/back.jpg                  背景图片 ，不缩放图片大小
border-image:             url() ./img/back.jpg                  背景图片，会对图片进行拉伸，平铺
border-style:             outset inset                          边框样式，按下是inset
border-width:             px                                    边框大小
border-radius:            px                                    边框弧度
border:                   3px solid red px color                边框宽度以及颜色
border-color:             rgba(255, 225, 255, 30); color        边框颜色
font-family               微软雅黑                               设定字体所属家族
font:                     bold 14px  bold px                    字体大小并加粗
font-size:                px                                    字体大小
font-style:               inset                                 字体样式
font-weight:              px                                    字体深浅
selection-color:          color                                 设定选中时候的颜色
selection-background-color:  color                              设定选中时候的背景颜色

rgba 即红色(0-255)、绿色、蓝色、透明度(0-1)(red, green, blue, alpha)

按钮中3种状态
//样例-文字：
btn1->setStyleSheet("QPushButton{color:red;background:yellow}"
                    "QPushButton::hover{background:rgb(110,115,100);}"
                    "QPushButton::pressed{background:#eb7350;}");

//样例-图片：
btn1->setStyleSheet("QPushButton{border-image:url(xxx);}"
                    "QPushButton::hover{border-image:url(xxxx);}"
                    "QPushButton::pressed{border-image:url(xxx);}");









样式表
https://blog.csdn.net/qq_32348883/article/details/122686832
1.前言
QT使用样式表通常有三种方式：
1.1. 在UI设计器---Qt Designer 内添加并设置样式；
优点：直观显示。
缺点：样式比较多时，不利于检查样式是否编写错误。同时不可以二次修改，即界面显示完毕后无法通过此方法修改界面的样式，只能靠代码去修改。

1.2. 在代码内直接使用样式；
优点：此种方法很方便，也很快捷。可以随时设置样式，改变样式，根据不同条件设置不同的样式，而不像第一、第三种方法直接设置固定样式。
缺点：当样式内容较复杂时，不利于查看，同时可能为了编码风格美观需要将样式内容换行等，这样可能会导致样式错误，根本没有效果，导致需要多次调试，浪费不必要的时间。

1.3. 将样式添加在文件内，以读取文件的方式来设置样式；
优点：
这种方法在界面样式较复杂时，我们在文件中编写样式，内容比较清晰，样式编写格式错误更加明显。同时也便于修改，同时一些文件编辑器能够自动给出样式输入提示，提供高编码效率。
缺点：
一般样式表文件都会加载到程序资源文件中，所以这里需要单独加载一个文件。同时跟第一种方法一样，不可以二次修改，当界面显示完毕后，只能靠调用setStyleSheet方法再次修改。


2.QPushButton和QToolButton 鼠标普通态、停留态、按下态  以QPushButton为例：
QPushButton{                                                           // 按钮普通态
  color: rgb(255, 255, 255);
  color: white;                    /* 文字颜色为白色 */
  background-color: rgb(0, 150, 0);
  background-color: #473C8B;       /* 背景色 */
  border-style: outset;            /* 边框风格 */
  border-width: 2px;               /* 边框宽度 */
  border-radius: 5px;              /* 边框圆角 半径为5像素 */
  border-color: #8B7355;           /* 边框颜色 */
  font: bold 14px;                 /* 字体 */
  min-width: 2em;                  /* 控件最小宽度 */
  min-height: 2px;                 /* 控件最小高度 */
  font-family: 华文新魏;            /* 字库  Microsoft Yahei; 微软雅黑 */
  font-size:20pt;                  /*字体大小为20点*/
  padding: 5px;                    /* 内边距 */
  padding-left:6px;                /* 文字横向偏移 */
  padding-top:6px;                 /* 文字纵向偏移 */
}
QPushButton:hover{ background-color:rgb(44 , 137 , 255);/*背景颜色*/ }  // 按钮停留态
QPushButton:!enabled { background-color: rgb(100, 100, 100); }         // 按钮禁用样式
QPushButton:pressed{                                                   // 按钮按下态
  background-color:rgb(14 , 135 , 228);/*背景颜色*/
  padding-left:3px;/*左内边距为3像素，让按下时字向右移动3像素*/
  padding-top:3px;/*上内边距为3像素，让按下时字向下移动3像素*/
}

// 调整边框风格时，需要先设置border-width >= 1
  border-style属性值    含义
  none                  定义无边框。
  hidden                与 “none” 相同。不过应用于表时除外，对于表，hidden 用于解决边框冲突。
  dotted                定义点状边框。在大多数浏览器中呈现为实线。
  dashed                定义虚线。在大多数浏览器中呈现为实线。
  solid                 定义实线。
  double                定义双线。双线的宽度等于 border-width 的值。
  groove                定义 3D 凹槽边框。其效果取决于 border-color 的值。
  ridge                 定义 3D 垄状边框。其效果取决于 border-color 的值。
  inset                 定义 3D inset 边框。其效果取决于 border-color 的值。
  outset                定义 3D outset 边框。其效果取决于 border-color 的值。
  inherit               规定应该从父元素继承边框样式。


3.QLabel设置前景色、背景色、字体大小、字体类型
QLabel {
    font-family: "Microsoft YaHei";
    font-size: 14px;
    color: #BDC8E2;
    background-color: #2E3648;
}


4.QLineEdit边框、背景颜色设置
QLineEdit
{
    border: 1px solid gray; /* 边框 */
    border-radius: 4px;     /* 边框圆角 */
    padding: 0 8px;         /* 内容与边框距离 */
    background: white;      /* 背景颜色 */
    selection-background-color: darkgray; /*所选内容的背景颜色*/
}


5.QComboBox边框、标识设置
//下面设置针对下拉框整体设置
QComboBox {
     border:1px solid gray ;          #设置边框
     border-radius: 3px ;             #设置圆角
     padding : 1px  2px  1px  2px ;  # 针对于组合框中的文本内容
}

//下面设置针对下拉框下拉标识（箭头）
QComboBox::drop-down {
     subcontrol-origin: padding;           #针对标识图标的位置设置
     subcontrol- position :  top  right ;
     width : 20px ;

     border-left-width :  1px ;            #针对标识图标四周属性
     border-left-color : darkgray;
     border-left-style :  solid ;  /* just a single line */
     border-top-right-radius:  3px ;  /* same radius as the QComboBox */
     border-bottom-right-radius:  3px ;
}

//下面设置针对下拉框下拉标识图片设置
QComboBox::down-arrow {
     image: url (:/misc/down_arrow.png);
}


6.QTableWidget 边框线和间隔线样式
//如下代码设置横向表格头的间隔线，有四个方向的间隔线,不需要间隔线的可以设置为0px
ui.myTableWidget->horizontalHeader()->setStyleSheet(
"QHeaderView::section{"
            "border-top:0px solid #E5E5E5;"
            "border-left:0px solid #E5E5E5;"
            "border-right:0.5px solid #E5E5E5;"
            "border-bottom: 0.5px solid #E5E5E5;"
            "background-color:white;"
            "padding:4px;"
        "}"
)

//如下代码设置纵向表格头的间隔线，有四个方向的间隔线,不需要间隔线的可以设置为0px
ui.myTableWidget->verticalHeader()->setStyleSheet(
"QHeaderView::section{"
            "border-top:0px solid #E5E5E5;"
            "border-left:0px solid #E5E5E5;"
            "border-right:0.5px solid #E5E5E5;"
            "border-bottom: 0.5px solid #E5E5E5;"
            "background-color:white;"
            "padding:4px;"
        "}"
)

//如下代码设置列表左上角第0行第0列的那个格子的边框线
ui.myTableWidget->verticalHeader()->setStyleSheet(
"QTableCornerButton::section{"
            "border-top:0px solid #E5E5E5;"
            "border-left:0px solid #E5E5E5;"
            "border-right:0.5px solid #E5E5E5;"
            "border-bottom: 0.5px solid #E5E5E5;"
            "background-color:white;"
        "}"
)


7. 窗体背景图片设置
设置主窗体背景图片为 new_back.png
QWidget#MainWindow
{
    image: url(:/new/prefix/resource/new_back.png);
}


8. 控件背景图片自适应
8.1 使用background-image
来设置背景图片，但是当背景图尺寸与控件尺寸不同时，就会出现，控件背景图显示的是多个要设置的图片，或者是没有显示完整。
#testButton {
        background-image:url(":/images/cancel_normal.png");
}
8.2 使用border-image 如
#testButton2 {
        border-image:url(":/images/cancel_normal.png");
}
来设置图片背景，因为border-image会自动适应控件大小，并且设置为背景图
如果同时指定了两个属性，那么将会使用border-image 绘制覆盖掉background-image。
简单使用例子如下：
QString styleSheet = QString(
"QPushButton {border-image:url(":/images/cancel_normal.png");background-color:transparent;border:none;}" //Normal
"QPushButton:hover {border-image:url(":/images/cancel_hover.png");background-color:transparent;}"
)
QBtn->setStyleSheet(styleSheet);


9.字体样式
//假设窗体中有子控件，默认字体12px，父类类型是QWidget，父类类名是Widget

//下面几种方法只会设置主窗体的字体，子控件不会应用，需要按个调用setFont
QFont font;
font.setPixelSize(20);
this->setFont(font);
this->setStyleSheet("{font:26px;}");
this->setStyleSheet("QWidget{font:26px;}");
this->setStyleSheet("Widget{font:26px;}");

//下面才是通过样式表设置整个控件+子控件的字体
this->setStyleSheet("font:26px;");
this->setStyleSheet("*{font:26px;}");
this->setStyleSheet("QWidget>*{font:26px;}");
this->setStyleSheet("Widget>*{font:26px;}");

//下面设置全局字体
qApp->setFont(font);


附注
1 在不改变原有的样式下，添加附加新样式的方式：
void setNewStyleSheet(QString styleSheet)
{
    //获取到原来的样式
     QString oldStyleSheet = this->styleSheet();
     styleSheet += oldStyleSheet;
     this->setStyleSheet(styleSheet);
}

2 QPushbutton或者QToolButton 的背景图片自动缩放，自适应按键大小
QPushButton *button = new QPushButton(this);
button->setGeometry(50, 50, 100, 50);
button->setStyleSheet("border-image:url(:/timg.jpg)");
connect(button, &QPushButton::pressed, [=](){
    button->setStyleSheet("border-image:url(:/myico.ico)");}
);
connect(button, &QPushButton::released, [=](){
    button->setStyleSheet("border-image:url(:/timg.jpg)"); }
);

3 QT工程加载一个样式表
QFile file(":/qss/stylesheet/mysheet.qss");
file.open(QFile::ReadOnly);
QString styleSh = tr(file.readAll());
setStyleSheet(styleSh);
file.close();










