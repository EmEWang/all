


layout  spacer



QLayout 作为布局相关类的基类
                     | QFromLayout
QObject -> QLayout ->| QBoxLayout   ->| QHBoxLayout
                     | QGridLayout    | QVBoxLayout
void QBoxLayout::addStretch(int stretch = 0) // 在布局器中增加一个伸缩量
void QLayout::setContentsMargins(int left, int top, int right, int bottom) // S设置左侧、顶部、右侧和底部边距，以便在布局周围使用。
setSpacing(int) // 设置 layout 中各部件的相邻距离，如果不设置，这个距离默认是 10。
addSpacing(int) // 在 setSpacing(int) 的基础之上再插入间距。这个距离可以是负值，表示后一个部件会覆盖在前一个部件上面。



1 QVBoxLayout 垂直布局
    void addWidget(); 向布局管理器中添加控件
    void addStretch(); 添加空白行
    addSpacing(); 添加一个固定间距
    setMargin(); 设置外边距
    setDirection(); 设置布局方向
    setStretchFactor(); 设置拉伸系数

2 QHBoxLayout 水平布局
    同上

3 QGridLayout 栅格布局
    rowCount(); 获取网格的行数
    columnCOunt(); 获取网格的列数
    addWidget(); 布局管理器中添加控件
    addLayout(); 向网格布局中再添加布局管理器
    setColumnStrech(); 给指定列设置伸缩系数
    setRowStrech(); 给指定行设置伸缩系数
    setColumnMinimunWidth(); 设置指定列的最小宽度
    setRowMinimunWidth(); 设置指定行的最小宽度

4 QFormLayout 表单布局
    addRow(); 将指定控件和存储标签添加到表单控件的末尾
    insertRow(); 将指定的控件和标签插入到表单的指定位置
    removeRow(); 删除表单控件的指定行
    setRowWrapPolicy(); 设置标签的显示格式
    setSpacing(); 设置行列间距

5 QStackedLayout 分组布局
    addWidget(); 添加控件到布局器内
    insertWidget(); 插入控件到布局器指定位置
    currentChanged(); 切换此布局控件时发射信号
    widgetRemove(); 移除某控件时触发此信号
    setCurrentIndex(); 设置指定控件为要显示的控件
    setCurrentWidget(); 设置指定控件为当前控件



splitter->setOrientation(Qt::Horizontal);  // 设置为水平分隔器
splitter->setOpaqueResize(true); // 设置为不透明分隔器
splitter->addWidget(textEdit);   // 将一个控件添加到分隔器中
splitter->setSizes(QList<int>() << 200 << 300); // 设置两个子控件的初始大小
QList<int> sizes = splitter->sizes(); // 获取当前子控件的大小
int width = QSplitter::handleWidth(); // 获取分隔器的宽度
splitter->refresh(); // 重新布局和绘制分隔器
splitter->setCollapsible(0, true); // 允许第一个子控件折叠



QGridLayout
如果QGridLayout不是顶级布局，必须在创建它时将它添加到其父布局中，但在你对它做任何事情之前。添加布局的通常方法是在父布局上调用addLayout()。
一旦添加了布局，就可以开始使用addWidget()、addItem()和addLayout()将小部件和其他布局放入网格布局的单元格中。

void setColumnMinimumWidth(int column, int minSize)    // 设置最小列宽
void setRowMinimumHeight(int row, int minSize)         // 设置最小行高
void setColumnStretch(int column, int stretch)         // 设置每一列的列宽比例
void setRowStretch(int row, int stretch)               // 设置每一行的行高比例
void setHorizontalSpacing(int spacing)                 // 设置水平方向各控件的间隔
void setSpacing(int spacing)                           // 同时设置设置水平方向和垂直方向上各控件的间隔
void setVerticalSpacing(int spacing)                   // 设置垂直方向各控件的间隔
void setSizeConstraint(SizeConstraint)                 // 设置尺寸控制模式
    Constant                       Value  Description     // 参数可选值
    QLayout::SetDefaultConstraint    0    主小部件的最小尺寸被设置为minimumSize()，除非小部件已经有了最小尺寸。
    QLayout::SetFixedSize            3    主部件的尺寸被设置为sizeHint();它根本无法调整尺寸。
    QLayout::SetMinimumSize          2    主部件的最小尺寸设置为minimumSize();不能再小了。
    QLayout::SetMaximumSize          4    主部件的最大尺寸设置为maximumSize();不能再大了。
    QLayout::SetMinAndMaxSize        5    主小部件的最小尺寸设置为minimumSize()，最大尺寸设置为maximumSize()。
    QLayout::SetNoConstraint         1    小部件不受约束。
void setOriginCorner(Qt::Corner corner)                // 设置表格坐标原点
    Constant                   Value      Description      // 参数可选值
    Qt::TopLeftCorner          0x00000    以矩形的左上角为原点。
    Qt::TopRightCorner         0x00001    以矩形的右上角为原点。
    Qt::BottomLeftCorner       0x00002    以矩形的左下角为原点。
    Qt::BottomRightCorner      0x00003    以矩形的右下角为原点。

QPushButton* button = new QPushButton("Button");// 占领gridlayout两行两列。变成一个大按钮。
button->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding); //Set SizePolicy of "Button" to Expanding for Both Directions
gridlayout->addWidget(button,1,1,2,2); //2个1，表示第1行，第1列；第1行，合并2行，第1列，合并2列  set Row and Col Span of "Button" to 2



