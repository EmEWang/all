

display


Qlabel
QLabel *label = new QLabel;
label->setWordWrap(true);            // 设置自动换行
label->setFrameShape (QFrame::Box);  // 设置边框  默认是NoFrame，不显示边框。
label->setStyleSheet("border-width: 1px;border-style: solid;border-color: rgb(255, 170, 0);"); // 边框宽度默认是0。必须更改一下边框宽度，才能显示出边框颜色。

QPalette pe; pe.setColor(QPalette::WindowText,Qt::white); label->setPalette(pe); // 1 使用setPalette设置字体的颜色
setStyleSheet("color:red;");  	//setStyleSheet("color:#ff6600;");                  2 使用样式表 或者使用 QStyle
QLabel *label = new QLabel("<h2><i>Hello</i><font color=red>Qt!</font></h2>");  //  3 使用一些简单的HTML格式

label.setMinimumWidth(200)     // 设置QLabel的最小宽度
label.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Fixed)    // 设置QLabel的自适应大小策略：这里设置宽度可以自适应，高度固定不变。
label.setScaledContents(true); //  设置label内容填充整个label空间
label.adjustSize();            // 设置label大小随内容自动变化

QPixmap pixmap("path_to_your_image.jpg"); // 替换为你的图片路径
label->setPixmap(pixmap);
pixmap->scaled(ui->label->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation); // 图片适应控件大小  按比例缩放
ui->label->setScaledContents(true);

QImage image;                  // 控件适应图片大小 这样的载入方式，能加载的图片类型是很少的
image.load("F:\\timg.jfif");
ui->label->setPixmap(QPixmap::fromImage(image));  // 图像显示在label上
ui->label->adjustSize();       // 控件适应图像(注意必须放到上一句代码之后)
ui->label->resize(QSize(image.width(),image.height()));

QScrollArea *scrollArea = new QScrollArea;   // 创建一个QScrollArea，并设置其为垂直滚动
scrollArea->setWidget(ui->label);            // 设置label为scrollArea的窗帘
scrollArea->setWidgetResizable(true);        // 允许滚动区域内的控件可调整大小
scrollArea->show();                          // 显示滚动区域


// 实现超链接
QLabel *linkLabel1 = new QLabel(this);     // 方法一
linkLabel1->setOpenExternalLinks(true);    // 设置为true才能打开网页
linkLabel1->setText("<a style='color: green; text-decoration: none' href = https://baidu.com>点我");
linkLabel1->setAlignment(Qt::AlignCenter); // 文字居中   color: red 为设置字体颜色，text-decoration: none 为设置字体没有下划线。

QLabel *linkLabel2 = new QLabel(this);     // 方法二
linkLabel2->setText("<a style='color: red; text-decoration: none' href = https://blog.csdn.net/wmcy123?type=lately>点我试试");
linkLabel2->setAlignment(Qt::AlignCenter);//文字居中
connect(linkLabel2, &QLabel::linkActivated, [=](QString url){QDesktopServices::openUrl(QUrl(url));}); //连接信号槽

QVBoxLayout *layout = new QVBoxLayout(this); // 使用垂直布局
layout->addWidget(linkLabel1);
layout->addWidget(linkLabel2);



实现拖动QLabel
使用QLabel派生一个自己的类,在派生类中重新定义以下几个鼠标事件相关的处理函数.
// mylabel.h
#ifndef MYLABEL_H
#define MYLABEL_H

#include <QObject>
#include <QLabel>

class MyLabel : public QLabel{
    Q_OBJECT
public:
    explicit MyLabel(QWidget *parent = nullptr);

protected:
    void mouseMoveEvent(QMouseEvent *event);         // 鼠标移动
    void mousePressEvent(QMouseEvent *event);        // 鼠标按下
    void mouseReleaseEvent(QMouseEvent *event);      // 鼠标弹起
    void contextMenuEvent(QContextMenuEvent *event); // 右键菜单
    void wheelEvent(QWheelEvent *event);             // 鼠标滚轮
    void paintEvent(QPaintEvent *event);             // QPaint 画图
signals:

private:
    bool m_bDrag{false};    // 是否可以拖动
    QPoint prePos;          // 鼠标的位置

    QImage Image;           // 图片
    qreal ZoomValue;        // 鼠标缩放位置
    int X_move;             // 平移x轴的位置
    int Y_move;             // 平移y轴的位置
    QPoint old_pos;         // 旧鼠标位置
    bool Pressed=false;     // 鼠标是否按下
    QString ImageFile="xx"; // 图片路径
};

#endif // MYLABEL_H



// mylabel.cpp
#include "mylabel.h"
#include <QMouseEvent>
#include <QDebug>

MyLabel::MyLabel(QWidget *parent): QLabel{parent}{}

void MyLabel::mouseMoveEvent(QMouseEvent *event){
    if(false == m_bDrag){return;}
    auto point = event->globalPos();  // 鼠标的当前位置
    auto newPos = this->pos() + (point - prePos); // 标签的新位置是鼠标较上次变化的量
    this->move(newPos);               // 将标签移动到新的位置
    prePos = point;                   // 更新鼠标位置
}

void MyLabel::mousePressEvent(QMouseEvent *event){
    if(event->button() != Qt::LeftButton){return;}  // 要求使用鼠标左键移动,如果不是鼠标左键直接return
    prePos = event->globalPos();      // 更新鼠标位置
    m_bDrag = true;
}

void MyLabel::mouseReleaseEvent(QMouseEvent *event){
    if(event->button() != Qt::LeftButton){return;}
    m_bDrag = false;
}

void MyLabel::contextMenuEvent(QContextMenuEvent *event){
    QPoint pos = event->pos();       // 获取鼠标坐标pos;
    pos = this->mapToGlobal(pos);    // 坐标转换为全局屏幕坐标 以上两步确认鼠标右键生成的menu跟随鼠标的当前位置

    QMenu* menu = new QMenu(this);   // 生成右键事件
    //menu->addSeparator();          // 添加动作到菜单中

    QAction* zoomInAction = new QAction(this);      // 放大动作
    zoomInAction->setText(QString::fromLocal8Bit("放大"));
    connect(zoomInAction , &QAction::triggered , this , &MyLabel::OnZoomInImage);   // OnZoomInImage 槽函数
    menu->addAction(zoomInAction);

    QAction* zoomOutAction = new QAction(this);     // 缩小动作
    zoomOutAction->setText(QString::fromLocal8Bit("缩小"));
    connect(zoomOutAction , &QAction::triggered , this , &MyLabel::OnZoomOutImage); // OnZoomOutImage 槽函数
    menu->addAction(zoomOutAction);

    QAction* presetAction = new QAction(this);      // 还原动作
    presetAction->setText(QString::fromLocal8Bit("还原"));
    connect(presetAction , &QAction::triggered , this , &MyLabel::OnPresetImage);   // OnPresetImage 槽函数
    menu->addAction(presetAction);

    menu->exec(pos);                                // 在鼠标位置出 执行
}

void MyLabel::OnZoomInImage(){ZoomValue += 0.05;update();}
void MyLabel::OnZoomOutImage(){if(ZoomValue > 0.05){ZoomValue = 0.05; update();}}
void MyLabel::OnPresetImage(){ZoomValue = 1.0;X_move= 0;Y_move= 0;update();}

void MyLabel::wheelEvent(QWheelEvent *event){                // 鼠标滚轮事件
    int value = event->delta();
    if(value > 0) OnZoomInImage();  // 放大
    else OnZoomOutImage();          // 缩小
    update();
}

void MyLabel::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    Image.load(ImageFile);                                           // 根据窗口计算应该显示的图片的大小
    int width = qMin(Image.width(), this->width());                  // 返回较小值
    int height = (width * 1.0)/(Image.width()*1.0 / Image.height()); // 图像跟label会根据宽对齐。height / width则根据长对齐
    height = qMin(height , this->height());
    width = height * 1.0 *(Image.width() *1.0 / Image.height());
    painter.translate(this->width() / 2 + X_move, this->height() /2 + Y_move);  // 平移int X_move , Y_move ; x y 轴平移的距离
    painter.scale(ZoomValue , ZoomValue);                                       // 缩放 qreal ZoomValue ；鼠标缩放位置
    QRect pecRect(-width / 2 , -height /2 , width , height);         // 绘制图像 前两个参数是坐标原地(0，0 在label 中心) 后两个天参数是长宽
    painter.drawImage(pecRect , Image);

    QWidget::paintEvent(event);
}


