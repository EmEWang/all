


类型转换
向上转型Upcasting(子类对象转换为父类对象)是安全的。
向下转型(Downcasting)可能不安全
  qobject_cast 是 Qt 提供的安全类型转换机制，适用于 QObject 的子类(类必须直接或间接继承自QObject，并且要声明宏Q_OBJECT。)。
    运行时检查对象的实际类型，转换成功，返回子类指针；失败，返回 nullptr。如果object是0则返回0。
    if (Derived* derived = qobject_cast<Derived*>(base))  // 使用 qobject_cast 进行安全的向下转型
  dynamic_cast用于类继承层次间的指针或引用转换。执行安全的向下转型。转换失败，返回结果为0。
    Derived *der = dynamic_cast<Derived*>(base);   // 针对指针 执行完后 成功则返回指针，失败则返回空指针。
    try{Derived& der = dynamic_cast<Derived&>(base);}catch(bad_cast){cout<<"转化失败,抛出bad_cast异常"<<endl;} // 针对引用 失败抛异常



QMap
QMap<QString, int> map;
map.insert("a", 1);
map.insert("b", 2);

value()函数：返回QMap中指定key所关联的value。如果key不存在于QMap中，则该方法会返回默认构造的value。
    int value1 = map.value("a");    // value1的值为1
    int value2 = map.value("c");    // value2的值为0，因为"c"不存在于QMap中，使用默认构造的value
    int value3 = map.value("c", 3); // value3的值为3，因为"c"不存在于QMap中，使用指定的默认值3
[]操作符：根据key查找value。在QMap中，如果我们使用[]操作符访问一个不存在的key，则会自动创建一个新的key，并将其value初始化为默认值。
    int value1 = map["a"]; // value1的值为1
    int value2 = map["c"]; // value2的值为0，因为"c"不存在于QMap中，使用默认构造的value
    map["c"] = 3; // 自动创建新的key "c"，并将其value设为3
find()函数：根据key在QMap中查找value，如果找到了对应的value则返回value的迭代器；否则返回QMap::end()迭代器。
    因此，可以使用find()函数进行迭代器遍历查找，也可以使用constFind()函数查找const迭代器。
    auto iter = map.constFind("apple");
    if (iter != map.constEnd()) {
        int appleCount = iter.value();  // appleCount = 20
    }
contains()函数：返回bool，判断map中是否存在key。
    if (map.contains("key1"))
QList values(const Key &key) const // 返回map中的所有values，List存放顺序和map是一致的，即map是无序的，list也是无序的；
  qSort(list.begin(), list.end()); // 排序
QList keys(const T &value) const   // 传入一个map的value，可以返回所有这个value所应对的key值


迭代器遍历
for(QMap<QString, int>::iterator = map.begin(); itor != map.end(); ++itor){qDebug() << itor.key() << ":" << itor.value();} // 1 可读可写的遍历方式
for(QMap<QString, int>::const_iterator itor = map.constBegin(); itor != map.constEnd(); ++itor){qDebug() << itor.key() << ":" << itor.value();} // 2 只读的遍历方式。其中constBegin()返回指向QMap开头的常量迭代器，constEnd()返回指向QMap结尾的常量迭代器，itor.key()返回当前迭代器指向的键，itor.value()返回当前迭代器指向的值。
QMapIterator<QString, int> itor(map);  // 3 可读可写的遍历方式。与第一种相比，提供了更多的功能，如remove()函数删除当前迭代器指向的元素。
  while (itor.hasNext()){itor.next(); /*移动到下一个元素*/ qDebug() << itor.key() << ":" << itor.value();}
for (auto &pair : map.toStdMap()){qDebug() << pair.first << ":" << pair.second;} // 4 QMap的toStdMap()函数将QMap转换为std::map
for (const auto &key : map.keys()){qDebug() << key << ":" << map.value(key);}    // 5 QMap的keys()函数获取所有键的列表
foreach(const QString &key, map.keys()){qDebug() << key << ":" << map.value(key);} // 6 Q_FOREACH在Qt2 中被引入，Qt4 中进行了重构和改进
  foreach (auto value, map){cout << value << endl;} // 遍历所有的value
std::for_each(map.constBegin(), map.constEnd(), [](const auto &item) {qDebug() << item.key() << ":" << item.value();}); // 7 std::for_each()





QList
T QList::value(int i) const
  返回指定位置i处的值，返回值T，相当于返回了一个复制，使用value(i)改变值后，list内的原变量不变化。
  如果索引i超出界限，则函数返回一个默认的构造值。如果确定索引值在边界内，则可以使用at()，at()速度稍快。
const T &QList::at(int i)
  返回列表中索引i处的项。i必须是列表中的有效索引值（即0<=i<size（））。这个函数非常快（时间复杂度：O(1)，常数时间复杂度）。
  返回值为const T&，使用at(i)获取的项为常量引用，值不可更改。
T &QList::operator[](int i)
  返回列表中索引i处的项。i必须是列表中的有效索引值（即0<=i<size（））。时间复杂度：O(1)，常数时间复杂度。
  返回值为T&，即list项的引用，值可更改，并且改变的是list中的值，可以保存。
所以访问元素不改变值最好用at()，获取元素并且要改变值就用operator[]。at() 比 operator 更快，因为它不会发生深拷贝。





文件系统
QFileDialog::getOpenFileName()       // 获取指定文件路径名返回QString
QFileDialog::getExistingDirectory()  // 获取指定路径返回QString
QFileDialog::getSaveFileName()       // 获取指定保存路径名返回QString

QFileInfo fileinfo = QFileInfo(QFileDialog::getOpenFileName(this,.....)); // fileinfo("./Resources/Config/Version.ini");
fileinfo.fileName();           // Version.ini  文件名
fileinfo.filePath();           // ./Resources/Config/Version.in  文件名
fileinfo.path();               // ./Resources/Config
fileinfo.suffix()              // ini  文件后缀
fileinfo.completeSuffix()      // ini  完整的后缀由文件中第一个“.”之后(但不包括)的所有字符组成
fileinfo.baseName()            // Version 文件名
fileinfo.completeBaseName()    // Version 完整的基名由文件中的所有字符组成，直到(但不包括)最后一个“.”字符
fileinfo.absolutePath();       // E:/App/Resources/Config  绝对路径 不包含文件名
fileinfo.dir().path();         // ./Resources/Config
fileinfo.absoluteDir().path(); // E:/App/Resources/Config
fileinfo.absoluteFilePath();   // E:/App/Resources/Config/Version.ini  绝对路径 包含文件名
fileinfo.canonicalPath();      // E:/App/Resources/Config  文件的路径规范路径(不包括文件名)，即没有符号链接或冗余“.”或“..”元素的绝对路径
fileinfo.canonicalFilePath();  // E:/App/Resources/Config/Version.ini  文件的路径规范路径(包括文件名)，即没有符号链接或冗余“.”或“..”元素的绝对路径

QString path = QDir::currentPath(); // 获取当前工程目录
QDir dir(path);
QStringList filename ;
filename << "*.png" << "*.jpg";     // 可叠加，可使用通配符筛选
QStringList results = dir.entryList(filename,QDir::Files | QDir::Readable,QDir::Name);  // 获取的所有文件名
    entryList 参数说明：第一个参数：筛选的条件  第二个参数：匹配条件  第三个参数：排序方式
    QDir::Files         列出文件
    QDir::Dirs          列出与筛选器匹配的目录
    QDir::AllDirs       列出所有目录；即不将过滤器应用于目录名
    QDir::Readable      列出应用程序具有读取访问权限的文件
    QDir::Writable      列出应用程序具有写访问权限的文件

    QDir::Name          按名称排序
    QDir::Time          按时间排序(修改时间)
    QDir::Size          按文件大小排序
    QDir::Type          按文件类型(扩展名)排序
    QDir::DirsFirst     首先放目录，然后放文件


QFile
QFile file(path);   //参数就是文件的路径
file.open(QIODevice::ReadOnly);   // 设置打开方式 取值可以组合，如 QIODevice::ReadOnly | QIODevice::Text 表示以只读和文本方式打开文件。
    QIODevice::ReadOnly           // 以只读方式打开文件，用于载入文件。
    QIODevice::WriteOnly          // 以只写方式打开文件，用于保存文件。
    QIODevice::ReadWrite          // 以读写方式打开。
    QIODevice::Append             // 以添加模式打开，新写入文件的数据添加到文件尾部。
    QIODevice::Truncate           // 以截取方式打开文件，文件原有的内容全部被删除。
    QIODevice::Text               // 以文本方式打开文件，读取时“\n”被自动翻译为换行符，写入时字符串结束符会自动翻译为系统平台的编码，如 Windows 平台下是“\r\n”。
file.close();                     // 关闭文件对象
QByteArray array = file.readAll();  // 用QByteArray类去接收读取的信息
QByteArray array; while(!file.atEnd()){ array+=file.readLine(); } // readLine一次读取一行  +=叠加读过的行
file.write(QByteArray);           // 对文件进行写操作


QTextStream
QFile file(path);
QTextStream QS(&file);        // 用QTextStream类去读取文本信息
QString array=QS.readAll();   // 用QString类去接收读取的信息
QS << QString("xxx");         // 对操作符进行了重载，<< 操作符将字符串流入文本文件



QSettings
QSettings *ini = new QSettings("hahaya.ini", QSettings::IniFormat);  // 参数1是ini文件的路径 参数2表示是ini文件 参数3可以缺省
ini->setValue("/ip/first", "192.168.0.1");// setValue两个参数是键值对  向ini文件的第一个节写入内容,ip节下的第一个参数
ini->setValue("ip/second", "127.0.0.1");  // 向ini文件的第一个节写入内容,ip节下的第二个参数
ini->setValue("port/open", "2222");       // 向ini文件的第二个节写入内容,port节下的第一个参数
delete ini;                               // 写入完成后删除指针
QString ip = ini->value("/ip/second").toString(); // 读取ini文件，先取值，toString()转换成QString
QString  title = QString::fromLocal8Bit(ini.value("Title").toByteArray().data());  // 读取标题  带汉字
QColor color = s.value("Color","")==""?QColor():QColor(s.value("Color").toString().toUInt(nullptr,16)); // 读取颜色
ini.setValue("title" title);              // 存储标题
ini.setValue("EarthLogColor",_QEarthLogColor.isValid()?QString::number(_QEarthLogColor.rgb(),16):"");   // 存储颜色
ini.beginGroup("SEC1");       // 开始一个节点
ini.endGroup();               // 结束一个节点



QByteArray <--> char* <--> std::string <--> QString
QByteArray类同样不以'\0'为结尾
1. QByteArray <--> QString
    1.1 QByteArray文本形式的转化
    QString str = QString(byte);         // QByteArray -> QString   直接使用QString构造
    QString str = bytes;                 // QByteArray - > QString
    str.prepend(bytes);                  // QByteArray - > QString

    QString str = "aaa";                 // QByteArray <- QString
    QByteArray byte = "ccc";
    QByteArray byte = str.toLatin1();    // ISO-8859-1编码是单字节编码，向下兼容ASCII，其编码范围是0x00-0xFF
    QByteArray byte = str.toLocal8Bit(); // gb18030字符集兼容了gbk字符集，以两个字节表示一个文字。windows系统可能使用的就是这两种的一种
    QByteArray byte = str.toUtf8();      // utf8字符集以2个或以上的字节表示一个汉字。实际上具体的数值和unicode有很大的相关

    1.2 QByteArray非文本形式的转化(二进制、十六进制)
    QString只有在数据是文本的时候才能构造，对于非文本形式(二进制或十六进制)的数据不能直接构造，可使用如下六种方法任意之一
    QString str1 = QString::fromLatin1(byte.toHex());    // QByteArray -> QString
    QString str2 = QString::fromLatin1(byte.toBase64()); // 先toHex() / toBase64() 再fromLatin1 / fromLocal8Bit / fromUtf8 转化为QString
    QString str3 = QString::fromLocal8Bit(byte.toHex());
    QString str4 = QString::fromLocal8Bit(byte.toBase64());
    QString str5 = QString::fromUtf8(byte.toHex());
    QString str6 = QString::fromUtf8(byte.toBase64());

    QByteArray byte1 = QByteArray::fromHex(str1.toLatin1);    // QByteArray <- QString
    QByteArray byte2 = QByteArray::fromBase64(str2.toLatin1); // 针对上面6个QString的str1,str2,str3,str4,str5,str6 转化为 QByteArray
    QByteArray byte3= QByteArray::fromHex(str3.toLocal8Bit);
    QByteArray byte4 = QByteArray::fromBase64(str4.toLocal8Bit);
    QByteArray byte5 = QByteArray::fromHex(str5.toUtf8);
    QByteArray byte6 = QByteArray::fromBase64(str6.toUtf8);

2  QByteArray  <--> std::string
    QByteArray byteArray(stdString.c_str(), stdString.length());      // std::string -> QByteArray
    std::string stdString(byteArray.constData(), byteArray.length()); // QByteArray  -> std::string
    inline std::string QByteArray::toStdString() const { return std::string(constData(), length()); } // Qt 5.4开始
    inline QByteArray QByteArray::fromStdString(const std::string &s) { return QByteArray(s.data(), int(s.size())); } //Qt 5.4开始

3 QByteArray <--> char *
    char *QByteArray::data()       // 指向存储在字节数组中的数据。可访问/修改组。数据以“\0”结束，返回字符串中的字节数为size() + 1。
    QByteArray ba("Hello world");  // QByteArray -> char *
    char *ch = ba.data();          // ch是指针
    qDebug() << *ch;               // *ch指向字符'H'，输出：H
    qDebug() << ch;                // 输出：Hello world

    char *ch = "Hello world";
    QByteArray ba = QByteArray(ch);  //  QByteArray <- char * 直接使用QByteArray()构造
    qDebug() << ba;                  // 输出："Hello world"
    qDebug().noquote() << ba;        // 去除字符串的双引号打印，输出：Hello world

4 QString <--> char *
    QString str("Hello world");        // QString -> char *
    char* ch = str.toLatin1().data();  // 1 先转化为QByteArray，再转化为char *    toLocal8Bit()/toUtf8()同
    qDebug() << ch;                    // 输出：Hello world

    QString str("Hello world");
    std::string s = str.toStdString().c_str();  // 2 先转为标准库中的 string 类型，再转化为 char *   注意：c_str()返回的是const
    const char* ch = s.c_str();
    qDebug() << ch;                    // 输出：Hello world

    char *ch = "Hello world";          // QString <- char *
    QString str(ch);                   // 直接使用QString()构造
    qDebug() << str;                   // 输出："Hello world"



QString
存储字符串数据。它存储16位Unicode字符，可以轻松地在应用程序中存储非ASCII /非拉丁字符。
QString str = "Hello, world!";
bool starts = str.startsWith("Hello");  // 返回 true 检查字符串是否以特定的子串开始/结束
bool ends = str.endsWith("world!");     // 返回 true
str = "apple,banana,cherry";QStringList fruits = str.split(",");// 返回 {"apple", "banana", "cherry"}  按分隔符分割为子串列表。
str = "42"; int value = str.toInt();    // 返回 42
str = "a";  int value = str.toUInt(nullptr,16); // 返回 10
str = QString::number(color.rgb(),16)   // QColor color; 16进制字符串
str = "Hello, World!"; QString upperStr = str.toUpper();        // 返回 "HELLO, WORLD!"   toLower()返回 "hello, world!"
QString QString::trimmed() const
  返回值为去除了开头和结尾的空白字符串，这里的空白指QChar::isSpace()返回值为true，比如'\t','\n','\v','\f','\r'和' ';
  str = "  Hello, world!  "; QString trimmedStr = str.trimmed();  // 返回 "Hello, world!"
QString QString::simplified() const
  返回字符串开头和结尾除去空白的字符串，并且内部的空白字符也去掉，这里的空白字符和上面的一样。
QString QString::arg(int a, int fieldWidth = 0, int base = 10, QChar fillChar = QLatin1Char(' ')) const // 格式化
QString QString::arg(long a, int fieldWidth = 0, int base = 10, QChar fillChar = QLatin1Char(' ')) const
QString QString::arg(double a, int fieldWidth = 0, char format = 'g', int precision = -1, QChar fillChar = QLatin1Char(' ')) const
QString str2=QString::number(num2,'f',2);   // 数字转QString，并保留小数点位数
QString::asprintf("%d", xx);                // 数字转QString，使用asprintf
QString::asprintf("%.3f",yy);



QStringList
字符串链表，里面存放的是QString类型的元素
QStringList weekList;
weekList<<"星期一"<<"星期二"<<"星期三";     // 添加元素.
weekList.append("星期天");                 // 在链表尾部添加
weekList.prepend("星期零");                // 在链表头部插入元素
weekList.insert(0,"星期零");               // 链表中插入元素 0则表示头部插入  参数:1插入链表的位置,2插入的QString字符串
weekList.removeFirst();                   // 删除头元素
weekList.removeLast();                    // 删除尾元素
weekList.removeOne("星期一");             // 删除某个元素
weekList.removeAt(0);                     // 删除指定位置的元素
weekList.clear();                         // 清空整个链表
weekList.contains("星期八");              // 链表中是否存在某个元素.
for(int i=0;i<weekList.size();i++){qDebug()<<weekList.at(i);} // 遍历 函数at(),传入的参数就是元素的位置.下表需要从0数起.
foreach(QString s,weekList){qDebug()<<s;} // foreach遍历,用QString类型的变量 s 临时存放里面的元素.
for(QStringList::iterator it = weekList.begin();it!= weekList.end();++it){qDebug()<<*it;}  // STL风格迭代器访 for循环
QListIterator<QString> itr(weekList);     // QListIterator:字符串链表的迭代器,元素是QString类型.  java风格迭代器访问
    while(itr.hasNext()){                 // .hasNext():当前位置的下一个位置是否存在元素;
        qDebug()<<itr.next();             // next()原因:初始位置不是第一个元素.是第一个元素的前面.
    }
weekList = weekList.toSet().toList();     // 去除重复项


QByteArray
可用于存储原始字节(包括“\ 0” )和传统的8位 “\ 0” 端接字符串 . 使用QByteArray比使用const char *更方便.
除了从原始数据创建QByteArray之外，还保证数据以”\ 0”字节结尾。这个’\ 0’字节由QByteArray自动提供，并不会在size()中计算。
QByteArray ba("Hello");    # 初始化  创建一个大小为5的字节数组，虽然size()为5，但是字节数组在最后还会保留一个额外的’\ 0’字符，以便如果使用一个函数来请求指向底层数据的指针(例如调用data())，那么指出的数据保证被’\ 0’终止。
ba.resize();               # 设置数组的大小，并初始化每个字节.resize()后，新分配的字节具有未定义的值。要将所有字节设置为特定值，请调用fill()。
QByteArray &QByteArray::fill(char ch, int size = -1)
    QByteArray ba("Istambul");  将字节数组中的每个字节设置为字符ch。如果size与-1(默认值)不同，则字节数组将预先调整为大小。
    ba.fill('o');        // ba == "oooooooo"
    ba.fill('X', 2);     // ba == "XX"
ba[0] = 0x3c;              # operator[] ()在非常量字节数组上，返回一个特定索引位置的字节引用。
if (ba.at(i) >= 'a')       # at()可以比operator []()更快，因为它不会导致深层拷贝发生。
left() right() mid()       # 一次提取多个字节
    QByteArray QByteArray::left(int len) const  返回一个包含该字节数组最左侧len个字节的字节数组,如果len大于size()，则返回整个字节数组.
        QByteArray x("Pineapple");
        QByteArray y = x.left(4); // y == "Pine"
QByteArray QByteArray::number(int n, int base = 10)
    返回一个字节数组，其中包含等价于数字n到基数的字符串(默认为10)。基数可以是2到36之间的任何值。可以理解为 int 类型到QByteArray类型的转化。
    int n = 63;
    QByteArray::number(n);                // returns "63"
    QByteArray::number(n, 16);            // returns "3f"
    QByteArray::number(n, 16).toUpper();  // returns "3F"
QByteArray &QByteArray::setNum(int n, int base = 10)
    将字节数组设置为基数为n的打印值(默认为10)并返回对字节数组的引用。基数可以是介于2和36之间的任何值。对于非10以外的其他值，n被视为无符号整数。
    QByteArray ba;
    int n = 63;
    ba.setNum(n);           // ba == "63"
    ba.setNum(n, 16);       // ba == "3f"
int QByteArray::size() const   # 返回此字节数组中的字节数。
    QByteArray可以嵌入“\0” 字节,size()函数总是返回整个数组的大小，包括嵌入的’\ 0’字节，但不包括QByteArray添加的终止’\ 0’.
    QByteArray ba("Hello");
    int n = ba.size();          // n == 5
    ba.data()[0];               // returns 'H'  操作某一位的方法
    ba.data()[4];               // returns 'o'
    ba.data()[5];               // returns '\0'
    ba.data() / const data()    // 返回一个指向数据开头的指针。要获取指向实际字符数据的指针 char  *QByteArray::data()
double QByteArray::toDouble(bool *ok = Q_NULLPTR) const
    float QByteArray::toFloat(bool *ok = Q_NULLPTR) const
    int QByteArray::toInt(bool *ok = Q_NULLPTR, int base = 10) const
    QByteArray string("1234.56");
    double a = string.toDouble();   // a == 1234.56
QByteArray QByteArray::toHex() const
    返回字节数组的十六进制编码副本。十六进制编码使用数字 0 - 9 和字母 a - f。See also fromHex().
std::string QByteArray::toStdString() const
    返回std :: string对象,带有QByteArray中包含的数据的.
QByteArray x("and");            // 修改字节数据的基本功能：append()，prepend() ，insert()，replace()和remove()。
    x.prepend("rock ");         // x == "rock and"  前置
    x.append(" roll");          // x == "rock and roll" 附加
    x.replace(5, 3, "&");       // x == "rock & roll" 替代
    这个 replace() 和remove()函数，前两个参数是从其开始擦除的位置和应该被擦除的字节数。
从QByteArray两端删除空格，用trimmed()。从两端移除空格并用字符数组中的单个空格替换多个连续的空格，请使用simplified()。
查找QByteArray中特定字符或子字符串的所有出现，请使用indexOf()或lastIndexOf()。
    int QByteArray::indexOf(const QByteArray &ba, int from = 0) const
        返回该字节数组中第一次出现字节数组ba的索引位置，从索引位置向前搜索。如果找不到ba，则返回-1 。
        QByteArray x("sticky question");
        QByteArray y("sti");
        x.indexOf(y);               // returns 0
        x.indexOf(y, 1);            // returns 10
        x.indexOf(y, 10);           // returns 10
        x.indexOf(y, 11);           // returns -1
    indexOf()从给定的索引位置开始搜索，lastIndexOf()向后搜索。两者返回字符或子字符串的索引位置，如果它们找到它; 否则返回-1。
    QByteArray ba("We must be <b>bold</b>, very <b>bold</b>");
    int j = 0;
    while ((j = ba.indexOf("<b>", j)) != -1){    // 查找特定子字符串的所有出现
        cout << "Found <b> tag at index position " << j << endl;
        ++j;
    }
contains()    // 只想检查QByteArray是否包含特定字符或子字符串
count()       // 要查找字节数组中特定字符或子字符串的次数
要将特定值的所有出现替换为另一个，请使用两个参数replace()重载之一。
<() <=() ==() >=()  // 等运算符来比较QByteArray。比较完全基于字符的数值，非常快，但不是我们期望的。QString::localeAwareCompare()是排序用户界面字符串的更好选择。
bool QByteArray::isEmpty() const    // 如果字节数组的大小为0，返回true; 否则返回false。
    由于历史原因，QByteArray区分了一个Null byte 和 empty byte. 我们建议您始终使用isEmpty().



Qt生成随机数-qrand及QRandomGenerator
//老方法 利用qrand和qsrand生成随机数 位于QtGlobal中 例，生成一个0和10之间的随机数
qsrand(QTime::currentTime().msec());        //设置种子，该种子作为qrand生成随机数的起始值，RAND_MAX为32767，即随机数在种子值到32767之间
qrand()%10;

//新方法 利用QRandomGenerator类  Qt5.10之后新增该类 例
qDebug()<<QRandomGenerator::global()->bounded(10);                //生成一个0和10之间的整数
qDebug()<<QRandomGenerator::global()->bounded(10.123);        //生成一个0和10.123之间的浮点数
qDebug()<<QRandomGenerator::global()->bounded(10, 15);        //生成一个10和15之间的整数



QProcess
QProcess::execute()              // 阻塞主进程的方式打开（静态成员）
void start(const QString& program, const QStringList& arguments, OpenMode mode = ReadWrite) // 以主进程的子进程的方式打开(父子) 将随主程序的退出而退出。
void startDetached(const QString& program, const QStringList& arguments, const QString& workingDirectory = QString(), qint64 * pid = 0) // 分离式 外部程序启动后，当主程序退出时并不退出。而是继续执行。
    QProcess::execute("C:\\Environment\\influxDB_1_5_2\\influxd.exe");
    process->start("F:/AppInst/115/115com/115com.exe");    //1-不带空格。能够启动
    process->start("C:/Program Files/HaoZip/HaoZip.exe");  //2-带空格，无法启动
    process->start("C:/Program Files/HaoZip/HaoZip.exe", QStringList("C:/Program Files/HaoZip/HaoZip.exe"));  //3-带空格，使用带參模式。能够启动
    QProcess::startDetached("C:\\Environment\\influxDB_1_5_2\\influxd.exe");
waitForFinished();      // 等待 程序结束
readAllStandardError()  // 从标准错误中获取所有数据
readAllStandardOutput() // 从标准输出中获取所有数据
write()                 // 继承于QIODevice
close()                 // 继承于QIODevice
setWorkingDirectory(QString); // 工作目录
Q_PID pid()             // windows下是个指针 linux下是个数值  注意startDetached方式获取的pid无效 请使用tart方式
execute(QString)        // 静态成员函数 启动一个进程，然后等待该进程结束。 阻塞式运行,一直占用cpu,成功返回0，失败返回1
startDetached()         // 静态成员函数 启动一个进程，然后使其和当前进程脱离进程的父子关系。
QStringList environment =  QProcess::systemEnvironment();    // 获取环境变量
执行cmd命令
    QProcess p(0);
    p.start("cmd", QStringList()<<"/c"<<"ping www.baidu.com");
    p.waitForStarted();
    p.waitForFinished();
    QString strTemp=QString::fromLocal8Bit(p.readAllStandardOutput());
    QMessageBox testMassage;
    testMassage.setText(strTemp);
    testMassage.exec();
终止外部进程
    QProcess::startDetached("taskkill -t  -f /pid " + QString::number(proc.processId())); // 通过进程ID结束进程（该进程由proc对象打开前提是通过 proc）   qt4下用proc.pid();
    QProcess::startDetached("taskkill -t  -f /IM " + QString("influxd.exe"));  // 通过进程名字结束进程

process = new QProcess();     // 处理started和finished信号
connect(process, SIGNAL(started()), this, SLOT(started()));
connect(process, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(finished()));
connect(process, &QProcess::errorOccurred,[&process](QProcess::ProcessError error){});  // 当有错误发生时，会发出errorOccurred信号。

关于start和startDetached
start()和startDetached()函数提供了两种不同的启动进程的方式。他们在大部分情况下能达到相同的效果，但在某些方面有着重要的不同。具体如下：
生命周期：start()函数创建的进程的生命周期与创建它的QProcess对象的生命周期相绑定。也就是说，当QProcess对象被销毁时，由它启动的进程也会被销毁。相比之下，startDetached()函数则会创建一个独立的进程，即使创建它的QProcess对象被销毁，启动的进程也会继续运行。
输入/输出：只有start()启动的进程可以使用QProcess类的一些重要功能。例如，使用setStandardInputFile()设置进程的标准输入，或者用readAllStandardOutput()和readAllStandardError()来获取进程的标准输出和标准错误。而startDetached()启动的进程则没有这样的功能，它的输入/输出不能由创建它的QProcess对象所控制。
进程间通信：start()启动的进程可以利用QProcess的信号/槽机制进行通信，例如用readyReadStandardOutput()和readyReadStandardError()信号获取到输出信息，并进行处理。而startDetached()则无法实现此类通信。
所以说，从上面的说明中，如果你需要对创建的进程进行控制的话，推荐使用start()函数。而如果你只是需要创建一个独立的进程，那么startDetached()可能会是更好的选择。

bool IsProcessExist(const QString &processName){// 返回 true/false    判断进程是否在运行
    QProcess proc;
    proc.start("tasklist");
    proc.waitForFinished();// 等待 tasklist 启动

    QByteArray result = proc.readAllStandardOutput();
    QString str = result;
    if(str.contains(processName)){
        qDebug() << processName <<"is Running";
        return true;
    }
    else{
        qDebug() << "Can't find " << processName;
        return false;
    }
}

bool IsProcessExist(const QString &processName){// 返回 true/false
    QString strInfo = QString::number(QProcess::execute("tasklist", QStringList()<<"-fi"<<"imagename eq influxd.exe"));
    if(strInfo .contains(processName)){
        qDebug() << processName <<"is Running";
        return true;
    }
    else{
        qDebug() << "Can't find " << processName;
        return false;
    }
}




XML
QDomDocument doc;                                // 写
QDomElement root =doc.createElement("wjgtree");
doc.appendChild(root);
QDomElement element = doc.createElement("top");
element.setAttribute("name", item->text(0));
element.setAttribute("type", item->type());
root.appendChild(element);
QFile file("./assembletree.xml");
file.open(QIODevice::WriteOnly);
QTextStream out(&file);
out.setCodec(QTextCodec::codecForName("UTF-8"));    // *** qt4.8.6 默认不使用utf8 需要显示说明 否则乱码
out << doc.toString();
//doc.save(out, QTextCodec::codecForName("UTF-8")); // QDomNode::EncodingFromDocument
file.close();

doc.appendChild(doc.createProcessingInstruction("xml","version=\"1.0\" encoding=\"UTF-8\""));  // *** 若设置了doc的编码属性
doc.save(out,2);     // 写入时按照上一行指定的编码   out.setCodec(QTextCodec::codecForName("UTF-8"));写与不写都不起作用



QDomDocument doc;                                // 读
QFile file("./assembletree.xml");
if (!file.open(QIODevice::ReadOnly)) break;
bool ok=doc.setContent(&file);
file.close();
if (!ok||doc.isNull()) break;
QDomElement root = doc.documentElement();
QDomNodeList items=doc.elementsByTagName("top");
for (int i=0;i!=items.size();++i){
    QDomElement item=items.item(i).toElement();
    if (item.isNull()) continue;

    QTreeWidgetItem* itemtop = new QTreeWidgetItem(ui.treeWidget, item.attribute("type").toInt());
    itemtop->setText(0, item.attribute("name"));
    //ui.treeWidget->addTopLevelItem(itemtop);     // 可省 构造中已指定

    fromSubItem(itemtop, item, doc, assembles, curAssembles);  // sub 迭代
}



QPropertyAnimation
QPropertyAnimation* animation = new QPropertyAnimation(targetObject, propertyName)
  targetObject 是要进行动画的对象  propertyName 是要进行动画的属性名
connect(animation, SIGNAL(finished()), this, SLOT(on_animation_finished))   //



QVariant
QTreeWidgetItem * item = objTree->topLevelItem(i);
item->setData(0,Qt::UserRole,QVariant::fromValue<ByyEntityObject*>(entObj));   // 存数据
ByyEntityObject *ent2=item->data(0,Qt::UserRole).value<ByyEntityObject*>();    // 取数据  value<T>()取值

variant.isValid();     // 判断是否存储有一个有效值  有效赋值之后位true 否则false
variant.type();        // 获取当前保存的数据类型
variant.value<QString>(); // 获取保存到指定类型的值
variant.canConvert<QString>();  // 判断能否将存储的类型转换为指定类型
variant.convert(QVariant::Int); // 将存储到类型转换为指定类型
variant.setValue(QString("Hello"));  // 重新存储字符

// 基本数据类型读取
QVariant intVar(10);               // 存储整数
QVariant doubleVar(3.14);          // 存储浮点数
QVariant stringVar("Qt QVariant"); // 存储字符串
QVariant stringListVar(QStringList{"apple", "banana", "cherry"});
qDebug() << "intVar type:" << intVar.typeName() << "value:" << intVar.toInt(); // 输出类型和值
if (v.type() == QVariant::Int) int value = v.toInt();  // 常用转换函数 toInt() toDouble() toString() toBool() toList()
if (v.type() == QVariant::String) QString str = v.toString(); // 自定义类型 需要用 v.value<XXX>()

// 自定义数据类型读取 由于Qt都是基于元对象系统，故要在头文件里面要注册此类属于元类型。
QVariant QVariant::fromValue(const T &value) 或 void QVariant::setValue(const T &value)。 // 存储
T QVariant::value() const                          // 获取
bool QVariant::canConvert(int targetTypeId) const  // 判断是否可以转换
variant.convert(QVariant::Int);                    // 将存储到类型转换为指定类型

struct MyStruct{    // .h文件声明
    int id;
    QString name;

    MyStruct() = default;
    MyStruct(const QVariant & variant){*this = variant.value<MyStruct>();} // 2 自定义类型转换
    operator QVariant() const{return QVariant::fromValue(*this);  }
};
Q_DECLARE_METATYPE(MyStruct)  // 1 注册为元类型
// QVariant支持自定义的数据类型。被QVariant存储的数据类型需要有一个默认的构造函数和一个拷贝构造函数。
// 为了实现这个功能，首先必须使用Q_DECLARE_METATYPE()宏。通常会将这个宏放在类的声明所在头文件的下面。

MyStruct ms;                       // .cpp文件定义
ms.id = 0;
ms.name = QString("hello");
variant.setValue<MyStruct>(ms);    // 1 存储数据
variant = QVariant::fromValue(ms);
variant = ms;                      // 2 自定义类型转换之后何用
MyStruct ms = variant;             //   自定义类型转换之后何用
if(variant.canConvert<MyStruct>()){MyStruct ms = variant.value<MyStruct>();}  // 获取
QVariant variant = QVariant::fromValue(static_cast<void*>(&ms));    // 3 指针类型存取
MyStruct* pms = static_cast<MyStruct*>(variant.value<void*>());
QObject* obj=new QObject;
QVariant var=QVariant(QMetaType::QObjectStar,&obj);   // 保存 4 用QVariant的构造函数QVariant(int typeId, const void *copy)
QObject* myobj=qvariant_cast<QObject*>(var);          // 提取
obj->deleteLater();


// 动态调用方法
class MyObject : public QObject {
    Q_OBJECT
public slots:
    void mySlot(int value) {qDebug() << "Value received:" << value;}
};
MyObject obj;
QVariant arg(42);
QMetaObject::invokeMethod(&obj, "mySlot", Q_ARG(QVariant, arg));



QDateTime
QDateTime dateTime;
QDateTime dateTime2 = QDateTime::currentDateTime();
QString dateTime_str = dateTime.currentDateTime().toString("yyyy-MM-dd hh:mm:ss");  // 获取系统时间
qint64 startTime = QDateTime::currentMSecsSinceEpoch();       //
dateTime.msecsTo(dateTime2);    // 时间差 结果为ms
QDateTime::fromMSecsSinceEpoch(QDateTime::currentDateTime().toMSecsSinceEpoch() - dateTime2.toMSecsSinceEpoch()).toUTC().toString("hh:mm:ss");
QDataTime time1 = QDateTime(QDate(1970,1,1));
QDateTime time2 = QDateTime(QDate(2020,1,1));
qint64 diffs = time1.secsTo(time2);//time1到time2的秒数
qint64 diffs = time1.daysTo(time2);//time1到time2的天数
datetime.fromString("2011-09-10 12:07:50:541", "yyyy-MM-dd hh:mm:ss:zzz").toMSecsSinceEpoch();// 从字符串转换为毫秒（需完整的年月日时分秒）
datetime.fromString("2011-09-10 12:07:50:541", "yyyy-MM-dd hh:mm:ss:zzz").toTime_t();// 从字符串转换为秒（需完整的年月日时分秒）
datetime.fromMSecsSinceEpoch(1315193829218).toString("yyyy-MM-dd hh:mm:ss:zzz");// 从毫秒转换到年月日时分秒
datetime.fromTime_t(1315193829).toString("yyyy-MM-dd hh:mm:ss[:zzz]");// 从秒转换到年月日时分秒（若有zzz，则为000）
QDateTime::toMSecsSinceEpoch() const;// 将QDateTime转换成毫秒
QDateTime::toSecsSinceEpoch() const;// 将QDateTime转换成秒
QDateTime::fromMSecsSinceEpoch(qint64 msecs);// 将毫秒值转换成QDateTime
QDateTime::fromSecsSinceEpoch(qint64 msecs);// 将秒转换成QDateTime



