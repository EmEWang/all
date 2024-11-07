

container


qWidget
void resizeEvent(QResizeEvent *rsize);     // protected:  重写这个方法处理 控件大小改变的处理

void setWindowModality(Qt::WindowModality modify)   // 设置窗口模态
  Qt::WindowModality windowModality()const;         // 返回窗口模态
  Qt::NonModal         : 0 表示该窗口不是模态窗口，不会阻止其他窗口的输入。
  Qt::WindowModal      : 1 表示该窗口是单个窗口层次结构的模态，会阻止输入到其父窗口、所有祖父窗口以及其父窗口和祖父窗口的所有同级窗口。（说人话就是这个模态窗口对象树上的输入型事件都被阻止了，除了自己，对象树的意思就是这个模态框得设置 parent，不然是阻塞不了别的窗口的）。你得设置 parent， 不然你也阻塞不了谁啊
  Qt::ApplicationModal : 2 表示该窗口是应用程序的模态窗口，会阻止本应用所有窗口的输入。（WindowModal 多个不在同一对象树的窗口还可以切换，ApplicationModal 就没有对象树的限制了，除了自己谁也不听使唤）
QDialog 模态
  QDialog 是 QWidget 的派生类，不同于 QWidget 的默认无模态，QDialog 有三种情况：
  调用 show() 显示：此时的模态属性是根据你 setWindowModality 设置的模式来决定的。或者你可以设置 QDialog::setModal(bool model) ，为 false（默认 false）则表示 Qt::NonModal ，为 true 则表示 Qt::ApplicationModal 。
  调用 exec() 显示：此时会忽略你设置的模态属性，默认以 Qt::ApplicationModal 显示，阻塞整个应用的窗口交互，并且会同步等待返回值。
  调用 open() 显示：此时会忽略你设置的模态属性，默认以 Qt::WindowModal 显示，但是是异步处理，立即返回的。

setWindowFlags(windowFlags()&~Qt::WindowCloseButtonHint&~Qt::WindowContextHelpButtonHint);  // 去掉关闭按钮，去掉帮助按钮
  Qt::FrameWindowHint          // 没有边框的窗口
  Qt::WindowStaysOnTopHint     // 总在最上面的窗口
  Qt::CustomizeWindowHint      // 自定义窗口标题栏,以下标志必须与这个标志一起使用才有效,否则窗口将有默认的标题栏
  Qt::WindowTitleHint          // 显示窗口标题栏
  Qt::WindowSystemMenuHint     // 显示系统菜单
  Qt::WindowMinimizeButtonHint // 显示最小化按钮
  Qt::WindowMaximizeButtonHint // 显示最大化按钮
  Qt::WindowMinMaxButtonsHint  // 显示最小化按钮和最大化按钮
  Qt::WindowCloseButtonHint    // 显示关闭按钮
一个控件放在另外一个控件或窗体的前面或者后面
  1 通过stackOver和stackUnder去控制
    button->stackUnder(label);   // 将button控件置于label控件的下方
    button->stackOver(label);    // 将button控件置于label控件的上方
  2 通过raise()和lower()函数实现
    label->raise();   // 将button控件置于label控件的下方
    button->lower();
  3 可以通过右键窗体放到后面或者前面，内部写代码在窗体缩放时，实现控制窗体显示的具体位置。

setStatusTip()    状态栏提示    窗口的左下角出现                                      只有MainWindow
setToolTip()      工具提示      鼠标放到控件上，浮动出一个小黄框                        MainWindow、Dialog和QWdiget都有作用
setWhatsThis()    帮助功能      标题栏上有一个?按钮，先点按钮鼠标变问号，再点控件才出现   只有QDialog起作用
setStatusTip用于MainWindow的状态栏提示；
setToolTip用于控件的提示；
setWhatsThis用于Dialog上的帮助信息。

添加工具栏
给主窗口（QMainWindow类）添加工具栏非常方便，直接使用addToolBar 即可，如下所示：
fileToolBar = addToolBar(tr("&File"));
fileToolBar->addAction(fileNewAction);
fileToolBar->addAction(fileOpenAction);

void QWidget::showEvent(QShowEvent *event) // 执行一些需要在窗口显示时进行的操作 初始化数据、加载资源、启动定时器等。
void QWidget::hideEvent(QHideEvent *event) // 执行一些需要在窗口隐藏时进行的操作 停止定时器、保存数据等。

// widget添加toolbar
QToolBar* myToolbarMessage=new QToolBar(QString::fromLocal8Bit("信"), this);
myToolbarMessage->addAction(myMessgeAction1);
myToolbarMessage->addAction(myMessgeAction2);
myToolbarMessage->addAction(myMessgeAction3);
QVBoxLayout *mlay = new QVBoxLayout(this);
QHBoxLayout *toplay = new QHBoxLayout();
toplay->addWidget(myToolbarMessage);
toplay->addWidget(myToolbarMessage2);
toplay->addWidget(myToolbarMessage3);
toplay->addWidget(myToolbarMessage4);
toplay->addStretch();
//mlay->addWidget(myToolbarLine);
mlay->addLayout(toplay);
mlay->addWidget(sp);

T QObject::findChild(const QString & name = QString(), Qt::FindChildOptions options = Qt::FindChildrenRecursively) const
返回对象中类型可以转换为T，并且名为name的孩子。如果不满足条件，则返回0。默认执行递归搜索，除非指定选FindDirectChildrenOnly。
如果有一个以上的孩子匹配搜索，返回最直接的祖先。如果有几个直系祖先，没有定义哪一个将被返回。这种情况下，应该使用findChildren()。
Qt::FindChildOptions是一个QFlags<FindChildOption>类型定义，它存储一个或FindChildOption的组合值。
  Qt::FindDirectChildrenOnly  0x0 查找object的直接孩子
  Qt::FindChildrenRecursively 0x1 查找object的所有孩子（递归搜索）
可能情况
  返回NULL
    不能转换为类型T - 与Qt::FindChildOption取值无关。
      QPushButton *button = parentWidget->findChild<QPushButton *>(); // parentWidget所有子孙部件中没有QPushButton，无论是否递归搜索，均返回NULL。
    可以转换为类型T，但是对应的name不存在 - 与Qt::FindChildOption取值无关。
        QCheckBox *checkBox = parentWidget->findChild<QCheckBox *>("Qt"); // parentWidget上有QCheckBox，但没有名为“Qt”的，所以无论是否递归搜索，均返回NULL。
    可以转换为类型T，对应的name也存在（非直接孩子） - Qt::FindChildOption取值为Qt::FindDirectChildrenOnly。
        QCheckBox *checkBox = parentWidget->findChild<QCheckBox *>("name2", Qt::FindDirectChildrenOnly); // 查找直接孩子，而直接孩子中没有名为“name2”的QCheckBox，所以返回NULL。
  返回非NULL
    1 可以转换为类型T；2  对应的name存在（如果name为空字符串，此条件可忽略，只需要参考1）. // 条件
    理解直接与非直接孩子的区别与关系（可以想象一下血缘关系）。name是按照objectName()来查找的，并不是text()，切勿搞错。 //注意

  QPushButton *button = parentWidget->findChild<QPushButton *>("button1");  // 返回parentWidget中一个名为“button1”的QPushButton孩子，即使按钮不是父亲的直接孩子
  QListWidget *list = parentWidget->findChild<QListWidget *>(); // 返回parentWidget中的一个QListWidget孩子
  QPushButton *button = parentWidget->findChild<QPushButton *>("button1", Qt::FindDirectChildrenOnly);  // 返回parentWidget（它的直接父亲）中一个名为“button1”的QPushButton孩子
  QListWidget *list = parentWidget->findChild<QListWidget *>(QString(), Qt::FindDirectChildrenOnly);  // 返回parentWidget（它的直接父亲）中的一个QListWidget孩子





QScrollArea
容器本身套了两层，ui拖动产出时，QScrollArea(本身widget)->scrllAreaWidgetContents(内部容器widget)，所有子控件位于内部容器中。
QScrollArea::setWidget(QWidget *)    // 更换掉 内层的这个scrllAreaWidgetContents本身
setWidget应在“把想加的控件都加到内部容器”之后再调用，否则会无法显示(测试发现，即使在setWidget之前没有给内部容器设置布局也不要紧，
  只要在setWidget之后，内部容器调用一下adjustSize，就可以把内部容器的控件显示出来，为了保险或后续程序兼容性，还是按照帮助文档来做)。
只要QScrollArea的尺寸 < 内部容器的尺寸，就会自动出现滚动条。
内部QWidget与QScrollArea的关系，就像是给QScrollArea设置了网格布局，然后把小QWidget放进了这个布局中，
  如果小QWidget最大宽高 < QScrollArea的实时大小，QScrollArea会显示出空白，而空白部分是无法放置/显示拖入的控件。
若不给内部容器设置宽高最大值，则其值为内部容器和QScrollArea最大值。


总结一下滚动区的标准编程步骤：
  1 new QscrollArea
  2 new 内部容器
  3 new 布局,例如网格布局QGridLayout（前3步不分先后顺序）
  4 向布局中添加你想要的控件（这一步必须位于步骤3之后）
  5 关联"内部容器"和"布局"（如果在创建布局时，就把布局构造在了内部容器中，那么这一步就省了）
  6 关联"内部容器"和"滚动区"，也即调用QScrollArea::setWidget(QWidget *)，这一步必须位于步骤4、5之后。

QScrollArea *scrollArea = new QScrollArea;
QScrollBar *vScrollBar = scrollArea->verticalScrollBar();  // 获取垂直滚动条对象
scrollArea->setHorizontalScrollBarRange(0, 100);        //设置水平滚动范围
scrollArea->setVerticalScrollBarRange(0, 100);          //设置垂直滚动范围
scrollArea->horizontalScrollBar()->setSingleStep(10);   //设置水平滚动步长为10
scrollArea->verticalScrollBar()->setValue(20);          //设置垂直滚动条当前值为20
scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);   // 设置滚动条的策略 如显示属性 范围 步长 当前值
scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);// Qt::ScrollBarAsNeeded
scrollArea->setWidgetResizable(true); // 让内部小部件自适应大小

QWidget *innerWidget = new QWidget(scrollArea);                   // 创建一个内部小部件
innerWidget->setFixedSize(600,800);                               // 设置内部小部件的大小
scrollArea->setWidget(innerWidget);                               // 将内部小部件设置为滚动区的小部件
vScrollBar->setRange(0, innerWidget->height() - scrollArea->height()); // 设置滚动条范围

QScrollArea *scrollArea = new QScrollArea;
QScrollBar *vScrollBar = new QScrollBar(scrollArea);              // 创建一个自定义滚动条对象
scrollArea->setVerticalScrollBar(vScrollBar);                     // 将自定义滚动条对象设置为垂直滚动条
scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // 不显示水平滚动条
vScrollBar->setStyleSheet("QScrollBar:vertical {background-color: #E9E9E9; width: 20px; margin: 0px 0px 0px 0px;} \
        QScrollBar::handle:vertical {background-color: #A0A0A0; min-height: 20px;}"); // 自定义滚动条的外观





QGroupBox
QGroupBox *box = new QGroupBox("hello");
box->setStyleSheet("background-color:rgba(0,0,0,0); border-image: url(:/picture/Frame.png);color:rgb(81,192,223);");  设置背景为图片
box->setStyleSheet("QGroupBox{background:red}");   改变背景颜色
box->setStyleSheet("QGroupBox{ margin-top:0px;} QGroupBox:title {margin-top: 0px;}");  除去标题和边框
box->setStyleSheet("QGroupBox { border-radius: 5px; }");  设置 QGroupBox边框为圆角 指定半径为5像素






