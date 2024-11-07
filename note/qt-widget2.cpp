

button


QPushButton
按钮实现无边框效果  打开属性里面的 flag 开关

clicked()  // 信号在按钮被点击(并且释放)后发出，不论按钮的状态是否发生改变。无论按钮是从按下状态到抬起状态，还是从抬起状态到按下状态，只要点击了按钮，clicked() 信号就会被发出。
toggled(bool checked) // 信号在按钮的状态发生改变时发出。这个信号不仅会在按钮被点击后发出，还会在按钮的状态由按下变为抬起或者由抬起变为按下时发出。这个信号的参数 checked 表示按钮的新状态，如果按钮被按下，checked 为 true；如果按钮被抬起，checked 为 false。
简单来说，clicked() 信号只关心按钮是否被点击，而 toggled(bool checked) 信号则更关心按钮的状态是否发生了改变。

setCheckable(bool checkable = false) // 设置按钮是否可被选中(默认不可选中)，即是否具有选中状态。true按钮可被选中；false，按钮不可被选中。
setChecked(bool checked = true)      // 设置按钮的选中状态。true按钮被选中；false按钮未被选中。

text  保存按钮上要显示的文字  该属性的值可以通过text()方法获取，也可以通过setText(const QString &text)方法修改
icon  保存按钮左侧要显示的图标  该属性的值可以通过icon方法获取，也可以通过setIcon(const QIcon &icon)方法修改
iconsize  保存按钮左侧图标的尺寸  该属性的值可以通过iconSize()方法获取，也可以通过setIconSize(const QSize &size)方法修改
size  保存按钮尺寸  该属性的值可以通过size()方法获取，也可以通过resize(int w,int h)或者resize(const QSize &)方法修改
font  保存按钮上文字的字体和大小  该属性的值可以通过font（）方法获取，也可以通过setFont(const QFont &)方法修改
flat  初始状态下，按钮是否显示边框。flat属性的默认值为flase，表示按钮带有边框  该属性的值可以通过isFlat()方法获取，也可以通过setFlat(bool)方法修改
enabled  按钮是否可以被按下  默认为true，表示按钮可以被按下；false，按钮将不能被点击，按钮处于禁用状态  通过isEnabled()方法获取，也可以通过setEnabled(bool)方法进行修改
autoDefault  按下Enter时，是否触发点击按钮的事件  当按钮的父窗口为QDialog窗口时，该属性的值为true；其他情况下均为默认值false  该属性的值可以通过autoFault()方法获取，也可以通过setAutoFault(bool)方法修改

move(int x,int y)                          手动指定按钮位于父窗口中的位置
setStyleSheet(const QString &styleSheet)   自定义按钮的样式，包括按钮上文字或图片的显示效果，按钮的形状等等
setGeometry(int x,int y,int w, int h)      同时指定按钮的尺寸和位置
adjustSize()                               根据按钮上要显示的内容，自动调整按钮的大小
setDisabled(bool disable)                  指定按钮是否可以被按下，当disable值为true时，表示按钮不能被按下

clicked() / clicked(bool checked = false)  用户点击按钮并释放后，触发此信号
pressed()                                  用户按下按钮时会触发此信号
released()                                 用户松开按钮时会触发此信号

click()                                   槽函数 单击指定的按钮
setIconSize()                             槽函数 重新设置按钮上图片的尺寸
hide()                                    槽函数 隐藏按钮控件
setMenu(QMenu *menu)                      槽函数 弹出与按钮关联的菜单

// 设置颜色
1 CSS风格
  button->setStyleSheet("background-color:yellow");  // 最简单的一种，但不常用，因为当按钮设置如下属性颜色就看不见了
  button->setFlat(true);                             // 这种情况下，只有按钮按钮下的状态才能显示出颜色。
2 QPalette类
  使用QPalette类也分两种情况，使用QPalette有前提：我们要把按钮放在QFrame框里，同时按钮窗体进行两项设置
    //放到QFrame里
    buttonFrame = new QFrame;
    QVBoxLayout *buttonLayout = new QVBoxLayout(buttonFrame);
    buttonLayout->addWidget(button);
    //进行两项设置
    button->setAutoFillBackground(true);
    button->setFlat(true);
  2.1 使用QColor类
    QColor color(255,0,255);
    QPalette p = buttonFrame->palette();
    p.setColor(QPalette::Button,color);
    button->setPalette(p);
  2.2 不使用QColor类
    QPalette p = buttonFrame->palette();
    p.setColor(QPalette::Button,Qt::green);
    button->setPalette(p);
3 调用Qt的预定义颜色,用选取的预定义颜色给控件赋值，常常和QComboBox下拉框配合使用，将获取到的预定义颜色填入下拉框以供选择。
  // 定义下拉框comboBoxOne  获取Qt预定义颜色，填到下拉框里
    void Widget::fillColorList(QComboBox *comboBox){
        QStringList colorList = QColor::colorNames();
        QString color;
        foreach (color, colorList)    {
            QPixmap pix(QSize(70,20));
            pix.fill(QColor(color));
            comboBox->addItem(QIcon(pix),NULL);
            comboBox->setIconSize(QSize(70,20));
            comboBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);
        }
    }
  // 定义响应下拉框改变信号的槽函数(改变按钮颜色)
    void Widget::changeColor(){
        QStringList colorList = QColor::colorNames();
        QColor colors = QColor(colorList[comboBoxOne->currentIndex()]);
        QPalette pOne = buttonFrame->palette();
        pOne.setColor(QPalette::Button,colors);
        button->setPalette(pOne);
        buttonFrame->update();
    }
  // 信号和槽函数的连接
    connect(comboBoxOne,SIGNAL(activated(int)),this,SLOT(changeColor()));

// 设置按钮颜色方法
void setPushButtonColor(QPushButton* button, QColor color){
    if (!button )
        return;

    if(!color.isValid())    {
        //button->setStyleSheet("QPushButton{background-color: initial}");
        button->setStyleSheet("QPushButton{background-color: palette().window();}"); // 颜色无效则恢复默认颜色
        return;
    }

    button->setAutoFillBackground(true);
    button->setFlat(true);
    QPalette p = button->palette();
    p.setColor(QPalette::Button,color);
    button->setPalette(p);
}






QRadioButton
QRadioButton *radioButton = new QRadioButton(this);
radioButton->setGeometry(300, 200, 100, 50);  // 位置和显示大小
radioButton->setText("下·");               // 显示文本
radioButton->setChecked(false);              // 设置初始状态

QRadioButton{                    // 样式
    spacing: 2px;
    color: white;
}
QRadioButton::indicator {
    width: 45px;
    height: 30px;
}
QRadioButton::indicator:unchecked {     // 未选中图标
    image: url(:/images/switch_off.png);
}
QRadioButton::indicator:checked {       // 选中图标
    image: url(:/images/switch_on.png);
}




QCheckBox
stateChanged(int state) // 信号在状态改变时发出 Qt::Unchecked(0):未被选中；Qt::PartiallyChecked(1):部分选中状态；Qt::Checked(2):完全选中。
clicked()               // 信号在复选框被点击时发出，不论状态如何改变。
clicked(bool checked)   // 信号在复选框被点击时发出，选中状态为 true；未选中为 false。






