


一.按钮类
QPushButton 普通按钮  继承 QAbstractButton 类，被 QCommandLinkButton 继承。
QToolButton 工具按钮  继承 QAbstractButton 类。用于命令或选项可以快速访问的按钮，通常在 ToolBar 里面。通常显示的是图标而不是文本。支持自动浮起。在自动浮起模式中，按钮只有在鼠标指向它的时候才绘制三维的框架。
QRadioButton 单选按钮  继承 QAbstractButton 类。通常成组出现，用于提供多选一。默认在同一个父对象下，初始化后点击它们是互斥状态。
QCheckButton 复选按钮  承 QAbstractButton。提供多选多。
QCommandLinkButton 命令连接按钮  继承 QPushButton。和 RadioButton 相似，都是多选一。默认携带一个箭头图标，表明按下按钮将打开另一个窗口或页面。
QDialogButtonBox 对话框按钮  继承 QWidget。常用于对话框里自定义按钮，比如“确定”和“取消” 按钮。

二.输出类
Qlabel 普通文本
QTextBrower 文本浏览器
QCalendarWidget 日历窗口
QLCDNumber 七段LCD数码管
QProgressBar 进度条

三.输入类
QComboBox 组合框             继承 QWidget ，被 QFontComboBox 继承。显示选项列表。
QFontComBox 字体下拉选择框   继承 QComboBox。常用于工具栏，选择字体的组合框。与 ComboBox 一起控制字体大小，与两个 ToolButtons 控制粗体和斜体。
QLineEdit 单行文本编辑框     继承 QWidget。echoMode()，用作“只写”字段，用于输入如密码等。
QTextEdit 多行文本编辑框     继承 QAbstractScrollArea，被 QTextBrowser 继承。高级所见即所得查看器/编辑器，支持 html 样式的 rich text 格式化。它经过优化以处理大型文档并快速响应用户输入。默认情况下，一个换行表示一个段落。一份文件由零个或多个段落组成。段落中的文字与段落的对齐方式一致。段落之间用硬换行符隔开。段落中的每个字符都有自己的属性，例如字体和颜色。 QTextEdit 可以显示图像，列表和表格。如果文本太大而无法在文本编辑的视图中查看，视图中则会出现滚动条。
QPlainTextEdit            是一个支持纯文本的高级查看器/编辑器。它被优化为处理大型文档和快速响应用户输入。
QSpinBox 自旋框            继承 QAbstractSpinBox。用于处理整数和离散值(如月份名称)，单击上下按钮或键盘上下键来选择当前显示的值或手动输入。
QDoubleSpinBox            继承 QAbstractSpinBox。 用于处理浮点值。单击上下按钮或键盘上下键来选择当前显示的值或手动输入。
QTimeEdit 编辑时间         继承 QDateTimeEdit。
QDateEdit 编辑日期         继承 QDateTimeEdit。
QDateTimeEdit 编辑日期和时间件。 键盘或箭头键编辑日期，以增加或减少日期和时间值。箭头键可用于在 QDateTimeEdit 框中从一个区域移动到另一个区域。
QDial 旋钮                继承 QAbstractSlider。拨号的行为与滑块类似。圆形范围控制(如速度计或电位器)。用于范围内控制一个值，并且该范围要么是环绕的(如，从 0 到 359 度测量的角度)。 当 wrapping()为 false(默认设置)时，滑块和刻度盘之间没有真正的区别。它们共享相同的信号，插槽和成员功能。使用哪一个取决于您的用户期望和应用程序类型。
QScrollBar 滚动条          继承 QAbstractSlider。提供垂直或水平滚动条，允许用户访问比用于显示文档的小部件大的文档部分。它提供了用户在文档中的当前位置和可见文档数量的可视化指示。滚动条通常配有其他控件，可以实现更精确的导航。
QSlider 滑动杆             继承 QAbstractSlider。提供垂直或水平滑动条小部件， 滑动条是用于控制有界值的典型小部件。它允许用户沿着水平或垂直凹槽移动滑块手柄，并将手柄的位置转换为合法范围内的整数值。
QKeySequenceEdit         继承 QWidget。允许用户选择 QKeySequence, QKeySequence通常用作快捷方式。当小部件接收到焦点并在用户释放最后一个键后一秒结束时，将启动记录，通常用作记录快捷键。


四.容器类
QGroupBox 分组框
QWidget 窗体
QFrame 窗口框架
QToolBox 工具栏
QScrollArea 滚动窗口容器
QTableWidget 制表容器
QStackedWidget 栈容器
QListWidget 列表窗口容器
QTreeWidget 树形窗口容器




固定窗口大小
1 设置最大窗口值和最小窗口值，并且使最大值和最小值相等。如固定为(370,150)
  setMinimumSize(370, 150);
  setMaximumSize(370, 150);
2 使用setFixedSize()  窗口的最大化按钮将变得不可用。
  setFixedSize(365,240);


创建窗口
1 使用代码创建一个新窗口，优点是灵活，缺点是麻烦，其中控件和布局都需要代码来创建。
2 在ui设计界面使用tab widget控件来达到多个窗口的效果，不过这种方法只能做切换窗口。
3 再创建一个ui设计界面，优点是可以很方便的使用ui设计工具。这里介绍第三种方法的使用。
    新建一个文件，文件类型选QT，再选QT设计师界面类  生成3个文件 xx.ui xx.h xx.cpp
    xx.h中将原本为private的 Ui::xx *ui; 改为public。
    #include "xx.h"和#include "ui_xx.h"，调用文件中添加头文件，前者是为了能够调用新的ui类对象，后者是为了能够调用新ui当中的控件。
    xx *px = new xx; xx.show();要调用的文件中创建新的ui界面类对象，就可以使用新的ui界面了。


重写窗口关闭按钮事件
#include <QCloseEvent>
void closeEvent(QCloseEvent *e);              // .h 中
void XXX::closeEvent(QCloseEvent *e){ /*想要实现的操作*/ this->close();}       // .cpp 中


QWidget *childWidget = new QWidget(parentWidget);
childWidget->show()                                 // 显示子窗口
childWidget->raise()                               // 将子窗口置于堆栈顶部 使其成为活动窗口
childWidget->lower()                                // 将子窗口置于堆栈底部 使其不在父窗口前面显示
childWidget->setWindowFlags(this->windowFlags() | Qt::Dialog);    // 子窗口作为模态对话框显示在父窗口上面
setAttribute(Qt::WA_DeleteOnClose);  子窗体的构造函数中添加 解决子窗体关闭时，不执行析构函数的问题
    子窗体构造函数中初始化了父窗体的parent，当关闭子窗体时不会调用析构函数，只有关闭父窗体时，才会调用子窗体的析构函数。



模态对话框的使用示例及accept()和reject()槽函数的使用
使用exec()函数实现的模态对话框执行accept()槽，会隐藏这个模态对话框，对应的返回值dialog.exec()==QDialog::Accepted---->宏值为1
使用exec()函数实现的模态对话框执行reject()槽，会隐藏这个模态对话框, 对应的返回值dialog.exec()==QDialog::Rejected---->宏值为0
小结：accept()和reject()都可以使对话框隐藏，但是dialog.exec()对应不同的返回值，我们可以通过返回判断是哪个按钮按下的。

示例1，点击一个按钮QDiaog隐藏，主窗口显示，点击另一个按钮，程序直接退出的功能。
int main() {
    QApplication a(argc,argv)
    myWidget w;
    myDialog dialog;
    if(dialog.exec()==QDialog::Accepted()){
        w.show;
        return  a.exec();  // a.exec()使程序在事件循环中，不会退出，而return0则直接退出程序了。(return a.exec()和return0的区别)
    }else
        return 0;//否则退出程序
}
示例2：警告窗口的使用
void MainWindow::ResponseFunc() {
    if(flag) {
        MyDialog  dialog;    //自定义的继承QDialog的类
        dialog.showInfo("未保存");//自定义的函数
        dialog.exec();  //使主窗口阻塞在这里
        return ;        //return必须要加上,如果不加return,dialog关闭后还是会执行后面的代码。
    }
    qDebug()<<"suceed";
    return;
}
示例3：自定义的对话框窗口
myDialog::myDialog() { connect(ui->okButton,SIGNAL(click()),this,SLOT(accept()));}
myDialog::showInfo(QString str) { ui->myLabel->setText(str); }



QDialog 之屏蔽 Esc 键
Qt中Esc键会在一些控件中默认的进行一些事件的触发，比如：QDialog，按下Esc键窗口消失。
通过查看QDialog的源码，很容易会发现keyPressEvent事件中，当按下Esc键时，会默认执行reject()。

1 事件重写  重写QDialog的键盘事件keyPressEvent。
void myBoxDialog::keyPressEvent(QKeyEvent *event){
    switch (event->key()) {
    case Qt::Key_Escape:
        close();
        break;
    default:
        QDialog::keyPressEvent(event);
    }
}

2 事件过滤器  对QDialog使用事件过滤器，过滤Esc键。
installEventFilter(new EventFilter(this));

bool EventFilter::eventFilter(QObject *obj, QEvent *event) {
    QDialog *pDialog = qobject_cast<QDialog *>(obj);
    if (pDialog != NULL) {
        switch (event->type()) {
        case QEvent::KeyPress: {
            QKeyEvent *pKeyEvent = static_cast<QKeyEvent*>(event);
            if (pKeyEvent->key() == Qt::Key_Escape) {
                return true;
            }
        }
        }
    }
    return QObject::eventFilter(obj, event);
}

3 重写reject m_bClosed为关闭的条件，为true时，窗口才会关闭。
void Dialog::reject() {
    if (m_bClosed)
        QDialog::reject();
}



QAction
对按钮的一次点击、对下拉菜单的一次选择抽象理解成对QAction的一次操作。使用QAction时，不需要关心绘制出来的UI是button还是menu还是啥。
void triggered(bool checked = false);      // 信号 只能由trigger()函数或者用户点击触发。
void toggled(bool);                        // 信号 扣第一次触发信号toggled(true)，扣第二次触发信号toggled(false)。
void setCheckable(bool);                   // 函数 QAction默认不是checkable的。可以触发toggled，但不能触发triggered。
  checkable的存在，toggled信号终于能被触发了。toggled 优先 于triggered触发。triggered的参数会根据 action当前的 checked状态传true或false。
isChecked状态与信号是什么关系? 先改变状态，再触发信号。信号的bool checked参数表示的是改变后的状态。

QActionGroup
  默认是IsExclusive() == true，排他的，单选的。
    QActionGroup* group = new QActionGroup(widget);
    group->addAction(act1);
    group->addAction(act2);
    运行，先点击按钮1，然后点击按钮2，再次点击按钮2：triggered的参数永远地变成true了。
    因为QActionGroup的作用，每次只能启用一把枪。当act2被扣下时，act1就会被自动停用。对于已经启用的枪，我们再次点击，并不会使它停用；
    虽然状态上没有任何改变，但triggered信号会被发送第二次。
  group->setExclusive(false);  // 效果和QActionGroup不存在时是一样的



QMessageBox头文件时，编译器报错无此头文件。
Qt5将MessageBox移到 widgets 下。因此可采用两个解决方案：
1 在.pro中添加 QT += widgets.    // 考虑到Qt4和Qt5代码的通用，最好使用这种。
2 在引用头文件时 #include <QtWidgets/QMessageBox>















