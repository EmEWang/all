

item





QListWidget
itemChanged(QListWidgetItem *)                // 信号 条目改变时触发
listWidget->count()                           // 条目数量
listWidget->clear()                           // 清除所有条目
listWidget->addItem(QListWidgetItem *);       // 添加条目
listWidget->addItems( );                      // 添加条目s
listWidget->setItemWidget(QListWidgetItem *, QWidget);  // 设置该item对应的widget
listWidget->setCurrentItem(item);             // 当前条目选中
listWidget->setSelectionMode(QAbstractItemView::MultiSelection) // 设置选择模式 ExtendedSelection 按住ctrl多选, SingleSelection 单选 MultiSelection 点击多选 ContiguousSelection 鼠标拖拉多选
listWidget->selectedItems();                  // 选中的item对象 的list 对象
listWidget->setDragEnabled(True)              // 设置拖拉
listWidget->sortItems()                       // 排序
listWidget->selectAll()                       // 全选
listWidget->setSortingEnabled(bool)           // 设置自动排序
listWidget->setCurrentRow(0)                  // 设置当前选择行默认为-1
listWidget->count()                           // 得到子项总数
listWidget->item(row).text()                  // 得到第 row 行的内容 listWidget.item(row) 返回一个item 对象
listWidget->takeItem(row)                     // 返回row 行的所在的item 对象 可以用在 insertItem（）中
listWidget->insertItem(2,item)                // 在第二行插入一项 item 可谓为一个listviewitem对象 或者string
listWidget->setCurrentItem('dd')              // 设置'dd'为当前项
listWidget->setText('dsds')                   // 设置item的内容为dsds item为对象 可从 listWidget.item(row) takeItem(row) 得到

connect(musicList,SIGNAL(currentRowChanged(int)),this,SLOT(musicListRowNum(int)));  //信号 与槽函数的链接  获取listWidget 的当前行行号

listWidget->removeItemWidget(QListWidgetItem *item);   // 删除该item对应的widget  (测试不是括号这样的而是会删除4.8  不删除该item,若item有Qstring，该qstring会保留下来)
listWidget->setFocusPolicy(Qt::NoFocus);      // 去掉item选中的虚线框 或  QListWidget{outline:0px;}
listWidget->setAlternatingRowColors(true);    // item颜色交替
    QListWidget {background:gray; alternate-background-color: black;} // 设置颜色 算上背景色有两种颜色
    QListWidget {background:gray;}                                    // 算上背景色有三种颜色 下3行
    QListWidget::item:alternate /*偶数行*/{background:pink;}
    QListWidget::item:!alternate /*奇数行*/{background:black;}
QListWidget{outline:0px;}     // 部分样式
    QListWidget {border: none; background:gray; /*alternate-background-color: black;*/ color: green;}
    QListWidget QLineEdit{background: gray;color:white;border:none;} // 编辑框 同QLineEdit
    QListWidget::item:alternate{background:pink;}
    QListWidget::item:!alternate{background:black;}
    QListWidget::item{color: yellow;border-bottom: 1px solid blue;}
    QListWidget::item:hover{background: red;color: white;}
    QListWidget::item:selected{background: red;color:white;}

https://blog.csdn.net/kongcheng253/article/details/128615807
QListWidgetItem 是一个纯数据类，不是控件，没有基类，也就没有信号和槽函数。QListWidgetItem 可以直接用数据流 QDataStream 读写。
QListWidgetItem 不单单有字符串，还可以有自己的图标、复选框等特性，列表控件会根据条目对象的丰富特性来呈现数据并进行交互操作。
构造函数
    QListWidgetItem(QListWidget * parent = 0, int type = Type)    //
    QListWidgetItem(const QString & text, QListWidget * parent = 0, int type = Type)
    QListWidgetItem(const QIcon & icon, const QString & text, QListWidget * parent = 0, int type = Type)
    icon 是条目显示的图标，text 是条目文本，parent 是条目隶属的列表控件，type 是条目的自定义类型。
    如果在构造函数指定了条目隶属的列表控件，那么这个条目会自动添加到列表控件末尾，而不需要调用列表控件的 add*() 和 insert*()函数
    如：new QListWidgetItem(tr("Hazel"), listWidget); 只要指定所隶属的列表控件,"Hazel" 条目就自动添加在 listWidget 末尾。
复制
    QListWidgetItem(const QListWidgetItem & other)  //复制构造函数
    QListWidgetItem & operator=(const QListWidgetItem & other) // = 赋值函数
    virtual QListWidgetItem *  clone() const  //克隆函数
    复制构造函数和  "=" 函数 原理是一样的，它们除了 type() 和 listWidget() 函数指定的两个数据不复制，其他的数据都复制。type() 是条目的自定义类型，listWidget() 是该条目所隶属的列表控件。
    而克隆函数 clone() 会精确复制所有数据，如果原条目隶属某个列表控件，克隆出来的也会自动隶属该列表控件，自定义条目类型也一样。
virtual bool operator<(const QListWidgetItem & other) const
    只有一个小于号函数，是比较列表条目文本的字典序先后关系，没有等于号函数和大于号函数，如果确实用到条目文本比较，建议直接用 QString 变量进行比较。
QListWidgetItem 内部的数据大致分为两类：第一类是以数据角色形式管理的通用数据，这些数据自动参与 QDataStream 数据流的读写；第二类是非通用数据，不参与数据流读写，与 QListWidgetItem 和 QListWidget 自身特性有关。
第一类：QListWidgetItem 的通用数据
    通用数据是以数据角色与数据变量一一对应的形式存储管理，比如设置文本 setText()、设置图标 setIcon() 等函数，其本质都是根据各自的角色调用通用设置数据的函数：
    virtual void setData(int role, const QVariant & value)
    virtual QVariant data(int role) const    根据角色来获取各个数据变量
第二类：QListWidgetItem 的非通用数据
int QListWidgetItem::​type() const   条目自定义类型 这个条目类型只能在构造函数指定，指定之后不能修改，默认值为 QListWidgetItem::Type （数值 0），如果程序员希望自己区分列表控件条目的类型，那么可以自己定义大于 QListWidgetItem::UserType （数值 1000）的类型值，一般用在 QListWidgetItem 派生类里面。
QListWidget * QListWidgetItem::​listWidget() const   条目所隶属的列表控件
    条目自身不能修改所隶属的列表控件，要通过列表控件的删除函数 QListWidget::​takeItem(int row) 才能解除隶属关系。
void QListWidgetItem::setSelected(bool select)      列表条目本身的选中状态（与复选框无关，是用户在列表控件点击条目的高亮选中状态）
bool QListWidgetItem::isSelected() const
    item->setSelected(true);  // 选中
    一般是用户在列表控件图形界面点击哪个条目，哪个条目就处于高亮选中状态，这里可以用条目自身的函数设置高亮选中状态。
void QListWidgetItem::setHidden(bool hide)    // 条目在列表控件里面显示或者隐藏
bool QListWidgetItem::isHidden() const

void QListWidgetItem::setFlags(Qt::ItemFlags flags)   // 条目的特性标志
Qt::ItemFlags QListWidgetItem::flags() const
    item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsEditable | Qt::ItemIsSelectable);   //条目 可编辑、可选中
    flags 会决定条目的工作特性，比如是否有三态复选框，是否在用户双击该条目时开启文本编辑器等等，Qt::ItemFlags 枚举值见下面表格
    Qt::​ItemFlags 枚举常量    数值    描述
    Qt::NoItemFlags    0    不设置任何特性，条目会处于完全的不可用状态。
    Qt::ItemIsSelectable    1    条目本身可以被高亮选中。
    Qt::ItemIsEditable    2    条目可以被编辑，比如用户双击条目时自动启用文本编辑器。
    Qt::ItemIsDragEnabled    4    条目可以被拖拽出去。
    Qt::ItemIsDropEnabled    8    条目可以作为拖拽的目的地。
    Qt::ItemIsUserCheckable    16    条目可以有复选框，用户能勾选复选框。
    Qt::ItemIsEnabled    32    条目处于可用状态。
    Qt::ItemIsTristate    64    条目的复选框可以有三种勾选状态：选中、非选中、部分选中。
    Qt::ItemNeverHasChildren    128    条目不能有子条目（指树形控件）。
    上表中的 Qt::ItemFlags 也适用于后面 8.2 节的表格控件条目和 8.3 节的树形控件条目，表格条目和树形条目也都有一样的条目标志位设置函数，功能与本节列表条目一样，参数也一样。
    Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsDragEnabled   列表控件条目默认的特性标志为同时启用四个
    item->setFlags( (item->flags()) | Qt::ItemIsEditable ); //双击条目会自动 开启文本编辑器

QListWidgetItem *item = new QListWidgetItem("test", listWidget);    // 新建条目
QListWidgetItem *item = listWidget->takeItem(listWidget->count() - 1 );  // 获取最后一条item  delete item;// 删除
ui->treeWidget->setCurrentItem(item);                              // item为当前条目 并跳转到此条目





QTreeWidget
https://blog.csdn.net/wzz953200463/article/details/109996501
QTreeWidgetItem *topItem1 = new QTreeWidgetItem(ui->treeWidget);
topItem1->setText(0,"baidu");                   // setFlags()
topItem1->setIcon(0,QIcon(":/new/prefix1/picture/Down.png")); // 图标
topItem1->setFont(0,font);                      // 字体  QFont font("黑体",16);
topItem1->setTextColor(0,Qt::white);            // 字体  QFont font("黑体",16);
topItem1->setTextAlignment(0,Qt::AlignLeft | Qt::AlignVCenter);           // 设置对齐方式
topItem1->setSelected(false);                   //
topItem1->setSizeHint(0,QSize(C_WIDTH,C_HEIGHT));                //
topItem1->setData(0,Qt::ToolTipRole,"Tooltip"); // 设置提示信息栏
  topItem1->setData(0,Qt::UserRole,100);        // 设置数据,节点可以带多种数据
  topItem1->data(0,Qt::UserRole).toInt();       // 获得数据
topItem1->setCheckState(0,Qt::Checked);         // 设置带checkBox     checkState() 获取
ui->treeWidget->addTopLevelItem(topItem1);      // 添加顶层节点
QTreeWidgetItem *item11 = new QTreeWidgetItem(topItem1); // 顶层节点下添加子节点
ui->treeWidget->setHeaderHidden(true);// 隐藏表头
ui->treeWidget->expandAll();          // 设置展开
ui->treeWidget->setColumnCount(1);    // 一列
ui->treeWidget->setRootIsDecorated(false);   // 关掉默认的展开图标
ui->treeWidget->header()->setVisible(false); // 关闭头部信息
ui->treeWidget->setFixedSize(T_WIDTH,T_HEIGHT); // 初始qtree的宽高
ui->treeWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // 禁用滑动块   setHorizontalScrollBarPolicy

ui->treeWidget->setContextMenuPolicy(Qt::CustomContextMenu);                                 // 打开右键菜单属性
  m_menu = new QMenu(ui->treeWidget);  m_menu->addAction("添加");  m_menu->addAction("删除"); // 右键菜单
  connect(ui->treeWidget,&QTreeWidget::customContextMenuRequested,this,&Form::slotMenuPopup);// 响应右键菜单信号槽
  void Form::slotMenuPopup(const QPoint &pos) { m_menu->exec(ui->treeWidget->mapToGlobal(pos));}

QStringList strList<<"名称"<<"年龄"<<"性别";                  // 多列树
    ui->treeWidget->setHeaderLabels(strList);
    ui->treeWidget->header()->setStyleSheet(sstyle);
    QTreeWidgetItem *item1 = new QTreeWidgetItem(QStringList()<<"七年级");
    ui->treeWidget->addTopLevelItem(item1);
    QTreeWidgetItem *item11 = new QTreeWidgetItem(QStringList()<<"小涨"<<"13"<<"男");item1->addChild(item11);
    QTreeWidgetItem *item12 = new QTreeWidgetItem(QStringList()<<"小红"<<"14"<<"女");item1->addChild(item12);
    QTreeWidgetItem *item13 = new QTreeWidgetItem(QStringList()<<"小丽"<<"13"<<"女");item1->addChild(item13);

void currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous) // 当前项发生变化时触发，使用后不会触发 itemClicked、itemDoubleClicked这两个信号，支持鼠标和键盘触发
void itemCollapsed(QTreeWidgetItem *item)                 // 伸展子项和收缩子项信号
void itemExpanded(QTreeWidgetItem *item)
void itemActivated(QTreeWidgetItem *item, int column)     // 激活项时触发信号
void itemChanged(QTreeWidgetItem *item, int column)
void itemClicked(QTreeWidgetItem *item, int column)       // 鼠标单击触发信号
void itemDoubleClicked(QTreeWidgetItem *item, int column) // 鼠标双击触发信号
void itemEntered(QTreeWidgetItem *item, int column)       // 鼠标光标的移动到项上时触发，前提打开鼠标跟踪
void itemPressed(QTreeWidgetItem *item, int column)       // 鼠标按下时触发
void itemSelectionChanged()                               // 当项发生变化时，可以通过键盘上下键触发

//遍历treeWidget
QTreeWidgetItemIterator it(ui.treeWidget);
while (*it) {
    //do something like
    (*it)->text(0);
    ++it;
}

// 1 删除节点及子节点
void removeItem(QTreeWidgetItem *item){              // 递归删除节点
    int count = item->childCount();
    if(count==0){                                    // 没有子节点，直接删除
        delete item;
        return;
    }

    for(int i=0; i<count; i++){
        QTreeWidgetItem *childItem = item->child(0); // 删除子节点
        removeItem(childItem);
    }
    delete item;                                     // 最后将自己删除
}

void  removeSelectedItems(QTreeWidget*treeWidget){   // 删除选中的节点及子节点
    QList<QTreeWidgetItem*> items = treeWidget->selectedItems();
    for (int i = 0; i < items.size(); ++i) {
        removeItem(items[i]);
    }
}

void on_pushButton_clicked(){removeSelectedItems(ui->treeWidget);} //点击按钮，删除已经删除的节点及其子节点


// 2 双击编辑QTreeWidget中Item的内容
private slots:                                                               //.h 文件
    void slotDoubleClickItem(QTreeWidgetItem *item, int col);
    void slotFinishEdit();         // 双击编辑完成

void ElemTree::slotDoubleClickItem(QTreeWidgetItem *item, int col) {         // .cpp 实现
    doubleClickItem = nullptr;
    if (col == 0) {
        doubleClickItem = item;
        QLineEdit* lineEdit = new QLineEdit(this);
        lineEdit->setText(0, QString::fromLocal8Bit("新建要素"));
        connect(lineEdit, SIGNAL(editingFinished()), this, SLOT(slotFinishEdit()));
        item->setSelected(true);
        this->setItemWidget(doubleClickItem, 0, lineEdit);
    }
}

void ElemTree::slotFinishEdit() {  // 槽函数 编辑完成
    if (doubleClickItem != nullptr) {
        QLineEdit *edit = qobject_cast<QLineEdit*>(this->itemWidget(doubleClickItem, 0));
        if (!edit) {
            return;
        }
        QString text = edit->text();
        this->removeItemWidget(doubleClickItem, 0);
        doubleClickItem->setText(0, text);
    }
}


// 3 拖放操作
class TreeWidget : public QTreeWidget{                   // 要继承 重写如下
    Q_OBJECT

public:
    explicit TreeWidget(QWidget *parent = nullptr);
    void init();                                          // 创建树形

protected:
    void mousePressEvent(QMouseEvent* event) override;    // 鼠标压下事件,启动拖拽事件
    void dragMoveEvent(QDragMoveEvent* event) override;   // drag操作在窗体移动事件
    void dragEnterEvent(QDragEnterEvent* event) override; // drag操作进入窗体
    void dropEvent(QDropEvent* event) override;           // drop释放事件

private:
    QLabel* label;                                        // 拖放显示控件
    QTreeWidgetItem* _selectItem;                         // 选中拖动节点
};


TreeWidget::TreeWidget(QWidget *parent){
    setDragDropMode(QAbstractItemView::InternalMove);     // 设置拖放模式为移动项目，否则为复制项目
    setAcceptDrops(true);                                 // 允许接受drop操作 设置拖放
    setDragEnabled(true);                                 // 允许拖动 启用拖放
    setSelectionMode(QAbstractItemView::SingleSelection); // 单选
    setDropIndicatorShown(true);                          // 设置显示将要被放置的位置
    setIndentation(20);
    //setRootIsDecorated(false);
    this->header()->hide();//隐藏头
}







QTableWidget
常用信号
    itemPressed(QTableWidgetItem *item)：当某个项目被按下时发出信号。
    itemClicked(QTableWidgetItem *item)：当某个项目被单击时发出信号。
    itemDoubleClicked(QTableWidgetItem *item)：当某个项目被双击时发出信号。
    itemActivated(QTableWidgetItem *item)：当某个项目被激活（例如通过键盘上的Enter键）时发出信号。
    itemEntered(QTableWidgetItem *item)：当鼠标进入某个项目时发出信号。
    itemChanged(QTableWidgetItem *item)：当某个项目的内容发生变化时发出信号。
    currentItemChanged(QTableWidgetItem *current, QTableWidgetItem *previous)：当当前选中的项目发生变化时发出信号。
    itemSelectionChanged()：当项目的选中状态发生变化时发出信号。
    cellPressed(int row, int column)：当某个单元格被按下时发出信号。
    cellClicked(int row, int column)：当某个单元格被单击时发出信号。
    cellDoubleClicked(int row, int column)：当某个单元格被双击时发出信号。
    cellActivated(int row, int column)：当某个单元格被激活时发出信号。
    cellEntered(int row, int column)：当鼠标进入某个单元格时发出信号。
    cellChanged(int row, int column)：当某个单元格的内容发生变化时发出信号。
    currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)：当当前选中的单元格发生变化时发出信号。

QTableWidget类中的常用方法
    rowCount()                                 获得QTableWidget表格控件的行数
    setROwCount(int row)                       设置QTableWidget表格控件的行数
    columnCount()                              获得QTableWidget表格控件的列数
    setColumnCount(int col)                    设置QTableWidget表格控件的列数
    clearContents()                            清空tablewidger中的内容，不包括表头
    clear()                                    清楚所有包括表头
    setHorizontalHeaderLabels()                设置QTableWidget表格控件的水平标签
    setVerticalHeaderLabels()                  设置QTableWidget表格控件的垂直标签
    item(int row,int col)                      获取单元格item
    setItem(int ,int ,QTableWidgetItem)        在QTableWidget表格控件的每个选项的单元控件内添加控件
    horizontalHeader()                         获得QTableWidget表格控件的表格头，以便执行隐藏
    setEditTriggers(EditTriggers)              设置表格是否可以编辑，设置表格的枚举值
    setSelectionBehavior()                     设置表格的选择行为
    setSelectionMode()                         设置表格的选择模式
    setTextAlignment()                         设置单元格内文本的对齐方式
    setSpan(int row,int column,int rowSpanCount,int columnSpanCount)  合并单元格，要改变单元格的第row行，column列，要合并rowSpancount行数和columnSpanCount列数
        row：要改变的行数  column：要改变的列数  rowSpanCount：需要合并的行数  columnSpanCount：需要合并的列数
    setShowGrid(bool)                          在默认情况下表格的显示是有网格的，可以设置True或False用于是否显示，默认True
    setColumnWidth(int column,int width)       设置单元格行的宽度
    setRowHeight(int row,int height)           设置单元格列的高度

QTableWidgetItem 常用方法
    setFlags(Qt.ItemIsSelectable | Qt.ItemIsEnabled)   设置为item不可被编辑

ui->tableWidget->rsetTabsClosable(true);                                 // Enable close buttons on tabs
ui->tableWidget->rtabBar()->setTabButton(0,QTabBar::RightSide,nullptr);  //第一个tab取消关闭按钮
ui->tableWidget->rowCount()                    // 行数   columnCount列
ui->tableWidget->insertRow(RowCont);           // 增加一行
    ui->tableWidget->setItem(RowCont,0,new QTableWidgetItem(PaperName)); //插入元素
    ui->tableWidget->setItem(RowCont,1,new QTableWidgetItem(KeyWord));
ui->tableWidget->removeRow(0);                 // 删除某行   removeColumn()列
ui->tableWidget->setRowCount(3);               // 设置表格的行数    setColumnCount()列
ui->tableWidget->setColumnCount(2);            // 设置表格的列数
int curRow = ui->tableWidget->currentRow();    // 返回当前选定的行号    currentColumn()列
int width = ui->tableWidget->width()           // 表的宽度
QStandardItem * pItem = new QStandardItem("AAA");  // QTableView设置单元格字体颜色及背景色
    pItem->setBackground(QBrush(Qt::blue));        // 设置背景色
    pItem->setForeground(QBrush(Qt::red));         // 设置字体颜色
QTableWidgetItem* pItem = new QTableWidgetItem("AAA");  // QTableWidget设置单元格字体颜色及背景色
    pItem->setBackground(QBrush(Qt::blue));        // 设置背景色
    pItem->setForeground(QBrush(Qt::red));         // 设置字体颜色
    pItem->setTextColor(QColor(Qt::red));          // 设置字体颜色
QTableView::item{        // 如果界面用QSS文件设置了皮肤，则需在QSS文件中把QTableView/QTableWidget 设置单元格颜色的代码去掉
    border: none;        /*去除分割线*/
    color: #2f2f2f;      /*设置字体颜色, 这里设置之后，代码里设置某个单元格的颜色不起作用*/
}
ui->tableWidget->setFocusPolicy(Qt::NoFocus);  // 去除选中虚线框
ui->tableWidget->setAlternatingRowColors(true)   // 隔行交替背景色
ui->tableWidget->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);  // 设置非单元滚动
    ui->tableWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
ui->tableWidget->resizeColumnsToContens()      // 根据内容自动调整列宽  resizeRowsToContens() 行高
ui->tableWidget->setColumnWidth(0,100)         // 手动指定第一列列宽为100  setRowHight(int,int) 行高
ui->tableWidget->horizontalHeader().setSectionResizeMode(QHeaderView.ResizeToContents)    // 设置所有列的宽度自适应内容
ui->tableWidget->horizontalHeader().setSectionResizeMode(0, QHeaderView.ResizeToContents) // 设置第一列的宽度自适应内容
ui->tableWidget->horizontalHeader()->setFont(font);       // 设置字体 QFont font("song", 12, QFont::Bold);
ui->tableWidget->horizontalHeader()->setHidden(true);     // 隐藏行标题
ui->tableWidget->horizontalHeader()->setVisible(false);   // 隐藏行标题
ui->tableWidget->horizontalHeader()->hide();              // 隐藏行标题
ui->tableWidget->setHorizontalHeaderLabels(headTable);    // 表格标题 QStringList headTable = {"编号","起点","终点","时刻","载重"};
ui->tableWidget->horizontalHeader()->setStretchLastSection(true) // 水平方向标签拓展剩下的窗口部分，填满表格
    horizontalHeader 返回表格的行标题，即第一行标题栏。这是个特殊的QHeaderView类。对标题栏进行调整。
    verticalHeader   返回表格的列标题，即第一列标题栏。
    setSectionResizeMode 函数是上述类的一个函数，设置标题如何调整为给定模式所描述的大小。
    QHeaderView::ResizeMode就是模式的枚举量，主要就是调整标题栏大小，即列宽。存在以下的取值：
    QHeaderView::Interactive       用户可以手动调节列宽，也可以通过调用resizeSection函数调整。
    QHeaderView::Fixed             用户无法手动调整列宽，只能调用resizeSection函数调整。
    QHeaderView::Stretch           列宽会自动调节以填充可用空间。大小不能由用户更改或以编程的方式更改。
    QHeaderView::ResizeToContents  列宽会自动根据内容调整为最佳大小。大小不能由用户更改或以编程的方式更改。
ui.tableWidget->setCurrentItem(nullptr);                     // 不选中任何项
ui.tableWidget->setCurrentItem(ui.tableWidget->item(1, 0));  // 只选中指定项
ui.tableWidget->setCurrentCell(1, 0);                        // 只选中指定项
ui.tableWidget->item(1, 0)->setSelected(true);               // 选中指定项 同时其他选定的项保留
QTableWidgetItem* item1 = new QTableWidgetItem("Row 1");
    ui->tableWidget->setItem(0, 0, item1);           // 在指定行和列中添加 QTableWidgetItem
QTableWidgetItem* selectedItem = ui->tableWidget->item(rowToSelect, 0);  // rowToSelect 为要选中的行的索引
    ui->tableWidget->setCurrentItem(selectedItem);   // 选中行1  行列索引都从 0 开始
ui->tableWidget->setCurrentCell(rowIndex,colIndex);  // 选中行2 若要选中整行 列索引置为0
ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows)  // 设置表格的选择模式 如行模式表示只选中整行
    ui->tableWidget->selectRow(rowNum)               // 选中行3 此时currentItem不能获取当前选定项，selectItems可以获取选中的某一列信息
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection)  // 单机某一行 整行单元格都被选中
ui->tableWidget->setRangeSelected(QTableWidgetSelectionRange(1,0,3,ui->tableWidget->columnCount()-1), true);  // 选中 2-4行
    QTableWidgetSelectionRange表示选中的区域，12参数为左上角单元格行列索引，34参数为右下角，5参数为bool，表是否选中该区域。
编辑规则的枚举值类型
    选项                                        值    描述
    QAbstractItemView::NoEditTriggers           0    不能对表格内容进行修改
    QAbstractItemView::CurrentChanged           1    任何时候都能对单元格进行修改
    QAbstractItemView::DoubleClicked            2    双击单元格
    QAbstractItemView::SelectedClicked          4    单击已经选中的内容
    QAbstractItemView::EditKeyPressed           8    当修改键按下时修改单元格
    QAbstractItemView::AnyKeyPressed            16   按任意键修改单元格
    QAbstractItemView::AllEditTriggers          31   包括以上所有条件
表格选择行为的枚举值
    QAbstractItemView::SelectItems              0    选中单个单元格
    QAbstractItemView::SelectRows               1    选中一行
    QAbstractItemView::SelectColumns            2    选中一列
单元格文本水平对齐方式
    Qt::AlignLeft                                    将单元格内的内容沿单元格的左边缘对齐
    Qt::AlignRight                                   将单元格内的内容沿单元格的右边缘对齐
    Qt::AlignHCenter                                 在可用空间中，居中显示在水平方向上
    Qt::AlignJustify                                 将文本在可用空间内对齐，默认从左到右
单元格文本垂直对齐方式
    Qt::AlignTop                                     与顶部对齐
    Qt::AlignBottom                                  与底部对齐
    Qt::AlignVCenter                                 在可用空间中，居中显示在垂直方向上
    Qt::AlignBaseline                                与基线对齐
    如果要设置水平和垂直方向对齐方式，比如在表格空间内上下，左右居中对齐，那么只要使用Qt,AlignHCenter和Qt,AlignVCenter即可

样式设置
#tab_1.QWidget{background-color: rgb(108, 117, 125, 65);} // 设置TabWidget中tab_1的样式 在样式表中用“#”指定对象

QTabBar::tab{                     // 设置TabWidget中QTabBar的样式  QTabWidget的选项卡栏
    background-color: #0B0E11;
    font-family:Consolas;         // 设置tab中的文本的字体
    font-size:8pt;
    color:#ced4da;                // 设置tab中的文本的颜色
    border-top-left-radius: 5px;  // 设置tab的边框的圆角（左上圆角）
    border-top-right-radius: 5px; // 设置tab的边框的圆角（右上圆角）
    min-width: 8px;
    padding: 5px;
}

QTabBar::tab:selected{background-color: rgb(108, 117, 125, 65);} // 设置TabWidget中QTabBar的tab被选中时的样式
QTabBar::tab:hover:!selected {background-color: rgb(108, 117, 125, 45);} // 设置TabWidget中鼠标悬浮在QTabBar的tab上，但未选中该Tab的样式
QTabWidget::pane {border: 1px solid rgb(108, 117, 125, 65);} // 设置TabWidget的边框的样式
QTabBar QToolButton {   // 当打开多个tab，右侧出现，点击后，可以向前向后的按钮的样式
    border: none;
    color: rgb(255, 206, 6);
    background-color: #0b0e11;
}
QTabBar QToolButton:hover {background-color: #161a1e;}

// 平滑滚动
ui->tableWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel); //设置为像素移动
QScrollBar * a = ui->tableWidget->verticalScrollBar(); //获取到tablewidget的滚动条
a->setSingleStep(5); //设置单步，值越小，下滑越慢

auto nLastRowIndex = ui->tableLogWnd->rowCount() - 1; // 最后一行的索引
auto lastModelIndex = ui->tableLogWnd->model()->index(lastRowIndex, 0);
ui->tableLogWnd->scrollTo(lastModelIndex); // 滚动到最后一行

ui->tableWidget->scrollToBottom();  //让滚动条滚动到最底部
ui->tableWidget->scrollToTop();     //让滚动条滚动到最顶部

setEditTriggers(QAbstractItemView::NoEditTriggers);  设置所有单元格都不可编辑

设置某行或者某列不可编辑，其他行列可编辑
1 继承类QStyledItemDelegate，重写函数createEditor，让其返回空，（单元格较多时推荐使用）
QWidget* ReadOnlyItemDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
{return nullptr;}

//限制某行某列不可编辑
ui->tableView->setItemDelegateForRow(row, new TableItemDelegate());
ui->tableView->setItemDelegateForColumn(column, new TableItemDelegate());

ui->tableWidget->setItemDelegateForRow(row, new TableItemDelegate());
ui->tableWidget->setItemDelegateForColumn(column, new TableItemDelegate());

2 使用QTableWidgetItem的setFlags函数（单元格较少时候推荐使用）
QTableWidgetItem* item = new QTableWidgetItem(optionsName);
item->setFlags(item->flags() & ~Qt::ItemIsEditable);


tableWidget->setMouseTracking(true);//开启捕获鼠标功能   鼠标悬停显示提示内容(Tooltip)
connect(ui->tableWidget,SIGNAL(entered(QModelIndex)),this,SLOT(ShowTooltip(QModelIndex))); // 接收和处理信号
void xxxx::ShowTooltip(QModelIndex index){QToolTip::showText(QCursor::pos(),index.data().toString());}















