


QColor
Qt中预定义颜色，如Qt::red、Qt::yellow、Qt::blue等等。
进一步的调整颜色深浅度也可以使用QColor，QColor也为我们提供很多颜色模组，有RGB、HSV、CMYK、HSL等等。
颜色模块中，所有的“1”都是255。
RGB常用于硬件显示，在基本的颜色调整方面都比较方便，.setRgb(int r,int g,int b,int a = 255)设置的前三个参数就是用于红、绿、蓝颜色调整。
HSV和RGB理解上差不多，但是HSV拥有调色功能。
HSL类似于HSV，但是HSL多了个曝光功能。
CMYK这个用于印刷机和打印机。
除了白色，其他颜色都是有深浅值的，在QColor中，深浅度由“0”-“1”，也就是0-255。0是黑色，255是设置的颜色本身，其值可以在0-255之间调整。
    QColor color;
    color.setRed(177);
    QPainter painter(this);
    painter.setBrush(QColor(0,225,225));
    painter.setBrush(QColor("red"));
    painter.setBrush(QColor("#00FFFF"));		//aqua颜色名，相当于参数(0,255,255)
    painter.setBrush(color);
    painter.drawRect(10,10,180,80);
RGB
    .setRgb(int r,int g,int b,int a = 255);   // 定义颜色 a默认是255，说明前三组组成的颜色的透明度，其深浅度为“1”。
    color.setRgb(0,255,255,255);
HSV
    HSV全称“Hue Saturation Value”意为（色调 色饱和度 值）。 和RGB大致相同，但是只是参数不同。
    色调既是其原本颜色。如果将颜色作为一个轮盘，那么0表示的是红色，120表示的是绿色，240表示的是蓝色。
    色饱和度从也是从“0”-“1”，即0-255。
    color.setHsv(0,255,255,255);	//H,S,V,a默认255，参上


QColorDialog
QColorDialog *colorDlg = new QColorDialog(this);  //显示颜色对话框并获取选中颜色
//colorDlg->exec();  //模态显示，因为后面要获取选中的颜色的。
//QColor color = colorDlg->selectedColor();  //获取当前选中的颜色

//也可以直接写下面一行即可  入参是设置默认值（颜色框弹出时的默认选中颜色值）。
QColor color = colorDlg->getColor(QColor(255,0,0));  //显示对话框并获取当前选中的颜色（显示对话框时线程阻塞，是模态显示的）
qDebug("r[%d] - g[%d] - b[%d]", color.red(), color.green(), color.blue()); //打印选中的颜色 r[114] - g[113] - b[112]
delete colorDlg;   //临时变量释放资源
colorDlg = nullptr;




QPen
color():定义了线条的颜色。使用setColor(QColor(255, 0, 0, 100))定义画笔的颜色。
width():定义了线条的宽度。使用setWidth(int width)设置线条的宽度。
setWidth(-1) / setStyle(Qt::NoPen) // 不显示线条  注意 不是 setWidth(0)
style():定义了线条的类型，使用setStyle()设置画笔线条的类型。
  Qt::SolidLine 实线  Qt::DashLine 虚线  Qt::DotLine 点线  Qt::DashDotLine 虚点线   Qt::DashDotDotLine 虚点点线  Qt::CustomDashLine
  pen.setDashPattern(QVector<qreal>() << 10 << 5 ) //实线：空线的比例为10 ：5 。每10个单位长度的实线，然后每5个单位长度的虚线。
capStyle() :设置线条两头的形状，可以是矩形，也可以是圆形的头。通过setCapStyle()设置线条端点形状。
  Qt::SquareCap 方形顶端，并且包含最后一个点  Qt::FlatCap 方形头部，但是并不包含最后一个点  Qt::RoundCap 顶端是半圆形
joinStyle() 是两条线的连接点的类型。可以通过setJoinStyle（）来设置两条线之间的连接点形状。
  Qt::MiterJoin 线的外缘延伸成一个角度，这个区域被填充。  Qt::BevelJoin 两条线之间的三角形缺口填满了。
  Qt::RoundJoin 两条线之间有弧度，就是很圆滑  Qt::SvgMiterJoin 一个斜角连接对应一个斜切的定义加入SVG 1.2小规格。
QPen pen(Qt::green, 5, Qt::DotLine, Qt::RoundCap, Qt::RoundJoin);  //参数为：画刷，线宽，画笔风格，画笔端点，画笔连接风格



QBrush
QBrush brush(QColor(0,0,255), Qt::Dense4Pattern);   // 画刷可以设置颜色和填充模式



QPainterPath path;  // 绘制路径
path.addEllipse(-4, -4, 8, 8); // 添加一个圆
path.addRect(-5, -5, 10, 10);  // 添加一个矩形
painter.drawPath(path);
path.setFillRule(Qt::OddEventFil); // 奇偶填充规则  判断一个点是否在图形中，从该点向图形外引一条水平线，该水平线与图形的交点人个数为奇数，则该点在在图形中。
path.setFillRule(Qt::WindingFill); // 非零弯曲规则  判断一个点是否在图形中，从该点向图形外引一条水平线，该水平线与图形的边线相交，这个边线是顺时针绘制的，就记为1，是逆时针绘制的就记为-1，然后将所有数值相加，结果不为0，那么该点就在图形中。



QPainter
QPainter painter(this); // 会立即开始在设备上绘制，自动调用begin()函数，然后析构函数中调用end()函数结束绘制。
QPainter painter;       // 不带参数时，可以在后面调用QPainter::begin(QPaintDevice *device)来指定绘制设置，然后用完再调用end()函数。
painter.translate(this->width() / 2 + X, this->height() /2 + Y);  // 平移  X,Y ; x y 轴平移的距离
painter.scale(ZoomValue , ZoomValue);                             // 缩放 qreal ZoomValue ；鼠标缩放位置
painter.setPen(pen);    // 设置画笔
painter.setBrush(brush); // 设置画刷
painter.fillRect(QRect(10,100,150,20), QBrush(Qt::darkYellow));  //使用画刷填充一个矩形区域
painter.eraserRect(QRect(50,0,50,120));   //擦除一个矩形区域的内容
painter.setCompositionMode(QPainter::CompositionMode_SourceIn); // 源图像和目标图像合成显示 https://blog.csdn.net/danshiming/article/details/123321515


QPainter painter(this);
QPixmap pix;
pix.load(“D:/1.jpg”);
painter.drawPixmap(0,0,50,50,pix); // 在（0，0）点起始的宽高均为50的矩形中显示图片
painter.translate(50,50);          // 将起始点改为（50，50）

qreal wid = pix.width();           // 获取图像的宽高
qreal hei = pix.height();
pix = pix.scaled(wid*2,hei*2,Qt::KeepAspectRatio); // 将图片宽高扩大两倍，且在矩形内保持宽高比值
  Qt::KeepAspectRatio            图片缩放的方式，其含义在给定矩形中保持图片长宽比；
  Qt::IgnoreAspectRatio          不保持图片长宽比；
  Qt::KeepAspectRatioByExpanding 保持图片长宽比，但可能超出给定的矩形

painter.translate(50,50); //将旋转中心改为（50，50）   必须先改变旋转中心，然后再旋转，然后再将原点复原，才能达到想要的效果。
painter.rotate(90); //顺时针旋转90度
painter.translate(-50,-50);
painter.drawPixmap(0,0,50,50,pix);

painter.drawPixmap(0,0,50,50,pix);
painter.shear(0.5,0) ;//横向扭曲    shear(qreal sh，qreal sv) 实现图片的扭曲。参数1横行变形，参数2纵向变形。当值为0时，表示不扭曲。
painter.drawPixmap(50,0,50,50,pix);
painter.shear(0,0.5);//纵向扭曲
painter.drawPixmap(0,50,50,50,pix);
painter.shear(0.5,0.5);//同时横纵扭曲
painter.drawPixmap(50,50,50,50,pix);

