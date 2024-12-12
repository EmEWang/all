


input


QLineEdit
void cursorPositionChanged( int old, int new );  // 当鼠标移动时发出此信号，old为先前的位置，new为新位置。在文本框中输入一个字符，光标移动一格，触发槽函数
void editingFinished(); //当 按返回或者回车键时，或者行编辑失去焦点时，发出此信号。当QLineEdit设置了validator() orinputMask()函数，验证器or输入掩码，并按了返回或回车键，信号只有在 输入内容符合输入掩码 或验证器返回 QValidator::Acceptable时 发出。
void returnPressed();  // 当 返回或回车键按下时发出此信号;当QLineEdit设置了validator() orinputMask()函数，验证器or输入掩码，并按了返回或回车键，信号只有在 输入内容符合输入掩码 或验证器返回 QValidator::Acceptable时 发出。
void selectionChanged(); // 当选文本改变时，发出此信号。
void textChanged( const QString &text );  // 当QLineEdit中的文本改变时，发出此信号，text是新的文本。当通过程序改变文本时，也会触发此信号
void textEdited( const QString &text );   // 当QLineEdit中的文本改变时，发出此信号，text是新的文本。当通过程序改变文本时，不会触发此信号。

ui.lonEdit->setFocus();           // 设置焦点
ui.lonEdit->selectAll();          // 全选文字  只有设置焦点之后才能全选


QTextEdit
void setPlainText ( const QString & text )       // 设置纯文本内容
void insertPlainText ( const QString & text )    // 插入内容  \n 换行
void setText ( const QString & text )            // 设置为纯文本之外，还可以设置为一些简单的html格式的字符串
void append( const QString & text )              // 在末尾添加新的一行。自动添加换行符
QString toPlainText () const                     // 获取文本内容
textEdit->document()->setMaximumBlockCount(100); // 显示的最大行数。之后apend追加到达最大行数时,会自动删除第一一行。
textEdit->setReadOnly(true);                     // 只读

QPalette pal = textEdit->palette();
pal.setBrush(QPalette::Base, QColor("#B4EEB4"));  // 设置画刷，填充背景颜色
pal.setBrush(QPalette::Base, QPixmap("C:/1.jpg").scaled(textEdit->size()));  // 设置画刷，填充背景图片，且调整了图片大小
textEdit->setAutoFillBackground(true);            // 取消继承父类的背景样式
textEdit->setPalette(pal);                        // 设置调色板，即填充了背景图片


连接信号textChanged()每当有新数据，将自动滚动到底部
    QTextEdit *textEdit = new  QTextEdit();
    connect(textEdit,SIGNAL(textChanged()),SLOT(slotTextTcpChanged()));
    textEdit->moveCursor(QTextCursor::End);    // 槽函数里的内容
		QTextCursor::Start        移动到文档的开头
		QTextCursor::StartOfLine  移动到当前行的开头
		QTextCursor::End          移动到文档末尾
		QTextCursor::EndOfLine    移动到当前行的末尾(内容够多的话，效果和end的一样)

QTextEdit实现自定义关键字着色(代码块着色)
https://cloud.tencent.com/developer/article/1933019

#ifndef HIGHLIGHTER_H
#define HIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QTextCharFormat>

QT_BEGIN_NAMESPACE
class QTextDocument;
QT_END_NAMESPACE

//Highlighter.h
#include <QSyntaxHighlighter>
#include <QTextCharFormat>

QT_BEGIN_NAMESPACE
class QTextDocument;
QT_END_NAMESPACE

#include <QMap>

class Highlighter : public QSyntaxHighlighter
{
	Q_OBJECT

public:
	Highlighter(QTextDocument *parent = 0);
	void SetText(const QString& text);
	void SetText(const QString& text, enum Qt::GlobalColor clr);
protected:
	void highlightBlock(const QString &text);

	QString word_text;

	QMap<QString, enum Qt::GlobalColor> myKeyHigh;
};


//Highlighter.cpp
#include "highlighter.h"

Highlighter::Highlighter(QTextDocument *parent)
	: QSyntaxHighlighter(parent)
{
}

void Highlighter::highlightBlock(const QString &text)
{
	//if(word_text.isEmpty())return;

	//QTextCharFormat myClassFormat;
	//QBrush br_blue;
	//br_blue.setColor(QColor("#D9919"));
	//myClassFormat.setFontWeight(QFont::Bold);
	//myClassFormat.setForeground(Qt::red);
	////myClassFormat.setForeground(br_blue);
	//QString pattern = word_text;

	//QRegExp expression(pattern);
	//int index = text.indexOf(expression);
	//while (index >= 0) {
	//	int length = expression.matchedLength();
	//	setFormat(index, length, myClassFormat);
	//	index = text.indexOf(expression, index + length);
	//}


	if(myKeyHigh.isEmpty())return;

	for (QMap<QString, enum Qt::GlobalColor>::Iterator it = myKeyHigh.begin(); it != myKeyHigh.end(); it++)
	{
		QTextCharFormat myClassFormat;
		myClassFormat.setFontWeight(QFont::Bold);
		myClassFormat.setForeground(QBrush(it.value()));
		QString pattern = it.key();

		QRegExp expression(pattern);
		int index = text.indexOf(expression);
		while (index >= 0) {
			int length = expression.matchedLength();
			setFormat(index, length, myClassFormat);
			index = text.indexOf(expression, index + length);
		}
	}
}


void Highlighter::SetText(const QString& text)
{
	word_text=text;
}

void Highlighter::SetText(const QString& text, enum Qt::GlobalColor clr)
{
	myKeyHigh[text] = clr;
}



// 使用着色的控件  声明
class itemForm : public QWidget
{
    Q_OBJECT

public:
    explicit itemForm(QWidget *parent = nullptr);
    ~itemForm();

	void setMyItem(const QString& time, const QString& msg, const QString& type = "", const QString& seg = "");
	void setLabelSeg (const QString& seg = "");
    void setLabelSeg2 (const QString& seg = "");
	QString myset(){return myseg;};
	QString getImage(const QString& text = "");

protected:
	bool eventFilter(QObject *target, QEvent *event);


private:
    Ui::itemForm *ui;
	QString mytype;
	QString myseg;
	Highlighter *highlighter;                                            // ****
};



// 使用着色的控件  构造函数设置
itemForm::itemForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::itemForm)
{
    ui->setupUi(this);
	myseg = "*";
	ui->textEdit->installEventFilter(this);

	highlighter = new Highlighter(ui->textEdit->document());              // ****

	//highlighter->SetText(QString::fromLocal8Bit("sg"));
	highlighter->SetText(QString::fromLocal8Bit("发射武器"), Qt::yellow);  // ****
	highlighter->SetText(QString::fromLocal8Bit("发现目标"), Qt::red);
	highlighter->SetText(QString::fromLocal8Bit("丢失目标"), Qt::blue);
	highlighter->SetText(QString::fromLocal8Bit("发送指令"), Qt::green);
}




QComboBox
ui.comboBox->setCurrentIndex(ui.comboBox->findText("xxx")); // 根据字符定位当前选项
除了显示可见下拉列表外，每个项（item，或称列表项）还可以关联一个 QVariant 类型的变量，用于存储一些不可见数据。
void addItem(const QIcon &icon, const QString &text, const QVariant &userData = QVariant())
void insertItem(int index, const QIcon &icon, const QString &text, const QVariant &userData = QVariant())
  ui->comboBox->insertItem(ui->comboBox->count(),"测试项目5");  //指定位置插入单个item(在最后插入)
  ui->comboBox->addItem(icon,"test1");  // QIcon icon;icon.addFile(":/images/icon.jpg");
  ui->comboBox->addItems(strList);      // QStringList strList;strList<<"test1"<<"test2"<<"test3";
  ui->comboBox->addItem(str,str2);

  struct Student{QString name;int age;}; Q_DECLARE_METATYPE(Student);//声明自定义类型,使得Qt能找到此类型的定义
  QVariant useVar;Student s1 = {"小明",20};useVar.setValue(s1);ui->comboBox->addItem("小明",useVar); // addItem时直接指定自定义数据
  QVariant useVar = ui->comboBox->itemData(index);if(useVar != QVariant::Invalid){qDebug() << useVar.value<Student>().name} // 使用
void setItemIcon(int index, const QIcon &icon)   // 修改或设置已有item的图标
setIconSize(QSize(32,32));                       // 设置图标大小为32*32(默认为16*16)
int currentlndex()       //返回当前项的序号，第一个项的序号为0。
QString currentText()    //返回当前项的文字。
QVariant currentData(int role = Qt::UserRole)  //返回当前项的关联数据
QString itemText(int index)                    //返回指定索引号的项的文字。
QVariant itemData(int index, int role = Qt::UserRole)  //返回指定索引号的项的关联数据。
int count()              //返回项的个数。
void setView(QAbstractItemView *itemView)   // 设置QComboBox下拉框的样式，可以是列表、树、表格等格式
setEditable(true)        // 打开可编辑属性 可以通过setValidator接口限定其输入格式，通过setCompleter接口设置输入自动补全
  // 默认，编辑模式不会删除或改变已有的item，按下回车后，在最顶端添加刚刚编辑的内容。若要改变默认属性，可以通过setInsertPolicy接口进行修改。
  //关于setInsertPolicy的参数列表的解释，在这里直接贴上官方帮助文档里的内容:
    QComboBox::NoInsert                 The string will not be inserted into the combobox.
    QComboBox::InsertAtTop              The string will be inserted as the first item in the combobox.
    QComboBox::InsertAtCurrent          The current item will be replaced by the string.
    QComboBox::InsertAtBottom           The string will be inserted after the last item in the combobox.
    QComboBox::InsertAfterCurrent       The string is inserted after the current item in the combobox.
    QComboBox::InsertBeforeCurrent      The string is inserted before the current item in the combobox.
    QComboBox::InsertAlphabetically     The string is inserted in the alphabetic order in the combobox.

void activated(int index)                       // 当有列表项被点击时，会发出activated信号，不管选项是够改变都会产生该消息。
void activated(const QString &text)
void currentIndexChanged(int index)             // 当选择项发生变化时，如果ComboBox为空或重置当前ComboBox，产生的消息值返回-1。
void currentIndexChanged(const QString &text)
void currentTextChanged(const QString &text)
void editTextChanged(const QString &text)       // 当列表文本改变时(需要打开可编辑属性)，则会触发editTextChanged信号
void highlighted(int index)                     // 当某个列表项高亮时(如将鼠标放在列表项上面)，会发出highlighted信号
void highlighted(const QString &text)
  connect(comboBox, SIGNAL(activated(int)), this, SLOT(ActiveSignal()));
  connect(comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(IndexChangedSignal()));
  connect(pushButton, SIGNAL(clicked()), this, SLOT(SelectedPlus()));
  void SelectedPlus(){comboBox->setCurrentIndex(comboBox->currentIndex()+1);} //点击按钮，改变currentIndex，又会触发currentIndexChanged信号
  void ActiveSignal(){int a = 0;}       //通过鼠标切换选项会进入该函数，通过按钮改变currentIndex不会进入该函数
  void IndexChangedSignal(){int a = 0;} //通过鼠标切换选项会进入该函数，通过按钮改变currentIndex会进入该函数
  //同时注意到有个小的细节，Connect的信号总是会先发currentIndexChanged，后发activated



QSpinBox/QDoubleSpinBox
前者处理整数和离散值集(如月份名称)；后者处理浮点值。
上/下按钮或键盘上/下键，增加/减少当前显示的值，以singleStep()为步长，更改此行为，则重写stepBy()。也可以手动输入值。
旋转框支持整数值，但可以扩展为使用带有validate()，textFromValue()和valueFromText()的不同字符串。
值更改时，发出两个valueChanged()信号，一个提供整数，一个供QString(带有数值及其前后缀)。value()获取当前值，setValue()进行设置。
setWrapping(true)        // 循环行为  用作圆形旋转框，如范围为0-9，当前值为9，则单击“上”将给出0。
setPrefix()/setSuffix()  // 在显示的值之前/后附加任意字符串，例如货币或度量单位。
旋转框中的文本使用text()（包括任何prefix()和suffix()）或cleanText()（没有prefix()，suffix()且没有前导或尾随空格）检索。
setSpecialValueText()  // 提供特殊的选择（通常是默认设置）










