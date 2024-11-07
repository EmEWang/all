

在pro文件中添加
    QT += network


Qt的TCP传输数据，出现中文乱码的解决方案，通常是因为编码不一致。
可以使用QString的toUtf8()进行发送前编码转换，从socket读取后用fromUtf8()解码，同时在QTcpSocket中设置编码为UTF-8来避免问题。
QString str = "中文字符串";        # 发送
QByteArray data = str.toUtf8();

QByteArray data = socket->readAll();  # 接受
QString str = QString::fromUtf8(data);

在建立TCP连接时，设置编码方式。例如，在服务器端和客户端都设置编码为UTF-8，可以在QTcpSocket的构造函数中设置编码方式
QTcpSocket *socket = new QTcpSocket(this);  #
socket->setSocketOption(QTcpSocket::KeepAliveOption, true);
socket->setEncoding(QTextCodec::codecForName("UTF-8"));



1 QUdpSocket
Qt 框架中用于处理 UDP 网络通信的类。

1.1 bind 函数的原型：
    bool QUdpSocket::bind(quint16 port, BindMode mode = DefaultForPlatform)
    bool QUdpSocket::bind(const QHostAddress &address, quint16 port, BindMode mode = DefaultForPlatform)
参数解释
    quint16 port: 要绑定的端口号。
    const QHostAddress &address: 要绑定的 IP 地址。如果省略，则默认绑定到所有可用的网络接口（即 0.0.0.0 或 ::，取决于协议族）。
    BindMode mode: 绑定模式，可以是 QUdpSocket::ShareAddress、QUdpSocket::DontShareAddress、QUdpSocket::ReuseAddressHint 或 QUdpSocket::DefaultForPlatform（默认）。这个参数影响套接字如何与其他可能正在使用相同地址和端口的套接字共享或独占资源。
返回值
    如果绑定成功，函数返回 true；否则返回 false。
使用注意事项
    端口冲突：如果尝试绑定的端口已经被另一个进程或服务占用，bind 函数将失败。
    权限问题：在某些操作系统和配置下，绑定到低于 1024 的端口可能需要管理员权限。
    IPv4 与 IPv6：根据系统的网络配置和 Qt 的版本，你可能需要明确指定是绑定到 IPv4 还是 IPv6 地址。
    多线程环境：在多线程应用程序中使用 QUdpSocket 时，需要注意线程安全和数据同步问题。
    错误处理：如果 bind 失败，可以通过调用 QUdpSocket 的 errorString() 方法来获取详细的错误信息。
    每当有数据报到来时，QUdpSocket都会发射readyRead()信号，这样就可以在自定义的槽中读取数据了

2 writeDatagram
函数模型
    qint64 QUdpSocket::writeDatagram(const char* data, qint64 size, const QHostAddress& address,quint16 port)
    // 1、发送大小为size大小的数据报data到地址为address的port端口
    // 2、QHostAddress::Broadcast 用于广播的地址
    // 3、如果发送成功，返回发送成功的字节数；如果发送失败，则返回-1

3 readDatagram
    每当有数据报到来时，QUdpSocket都会发射readyRead()信号，这样就可以在自定义的槽中读取数据了
    receiver = new QUdpSocket(this);
    receiver->bind(45454,QUdpSocket::ShareAddress);
    connect(receiver,&QUdpSocket::readyRead,this,&Sender::sltOnReceiver);

    QByteArray datagram;      // 让datagram的大小为等待处理的数据报的大小，这样才能接收到完整的数据
    datagram.resize(receiver->pendingDatagramSize());    // 接收数据报，将其存放到datagram中
    receiver->readDatagram(datagram.data(),datagram.size());

// hasPendingDatagrams()函数用来判断是否还有等待读取的数据报
// pendingDatagramSize()函数可以用来获取当前数据报的大小
// readDatagram(datagram.data(),datagram.size())函数用来接收不大于指定大小的数据报，并将其存储到QByteArray变量中






UDP组播发送端不收回自己发出去的数据，即不回显
使用UDP组播数据，能不能做到A发送端只接收其它发送端（B、C、D……）发送的数据，而不接收自己发送去的数据？

在组播时，设置不允许再返回到自身就可以了。而广播是没有该属性的。
int loop=0;                 # Off
setsockopt(sock,IPPROTO_IP,IP_MULTICAST_LOOP,&loop,sizeof(loop));  # 设置不允许再返回到自身

谢谢，我没有使用你的方法，但你的方法给了我启示，我最后的方法是：
bFlag = 0;
WSAIoctl(s_SocketCAN_Local, SIO_MULTIPOINT_LOOPBACK, &bFlag, sizeof(bFlag), NULL, 0, &len, NULL, NULL);



QT加入组播，却收不到本机自己给自己发的数据
QUdpSocket udp_socket;
udp_socket.bind.......//绑定IP的语句略
QHostAddress mcast_addr("224.0.0.17");
udp_socket.setSocketOption(QAbstractSocket::MulticastLoopbackOption, 0);  // 0禁止本机回环接收 1可以接收
udp_socket.joinMulticastGroup(mcast_addr);




UDP 广播 组播 的区别







TCP
https://www.cnblogs.com/ybqjymy/p/13683658.html
#include <QTcpSocket>
#include <QHostAddress>
#include <QTcpServer>       // 服务器
#include <QNetworkInterface>

1客户端编程
1.1 初始化QTcpSocket
    //初始化TCP客户端
    tcpClient = new QTcpSocket(this);   //实例化tcpClient
    tcpClient->abort();                 //取消原有连接
    connect(tcpClient, SIGNAL(readyRead()), this, SLOT(ReadData()));
    connect(tcpClient, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(ReadError(QAbstractSocket::SocketError)));
1.2 建立连接 和 断开连接
    tcpClient->connectToHost(ui->edtIP->text(), ui->edtPort->text().toInt());
    if (tcpClient->waitForConnected(1000))  // 连接成功
    {
        ui->btnConnect->setText("断开");
        ui->btnSend->setEnabled(true);
    }
    a）建立TCP连接的函数：void connectToHost(const QHostAddress &address, quint16 port, OpenMode openMode = ReadWrite)是从QAbstractSocket继承下来的public function，同时它又是一个virtual function。作用为：Attempts to make a connection to address on port port。
    b）等待TCP连接成功的函数：bool waitForConnected(int msecs = 30000)同样是从QAbstractSocket继承下来的public function，同时它又是一个virtual function。作用为：Waits until the socket is connected, up to msecs milliseconds. If the connection has been established, this function returns true; otherwise it returns false. In the case where it returns false, you can call error() to determine the cause of the error.

    tcpClient->disconnectFromHost();
    if (tcpClient->state() == QAbstractSocket::UnconnectedState || tcpClient->waitForDisconnected(1000))  //已断开连接
    {
            ui->btnConnect->setText("连接");
            ui->btnSend->setEnabled(false);
    }
    a）断开TCP连接的函数：void disconnectFromHost()是从QAbstractSocket继承的public function，同时它又是一个virtual function。作用为：Attempts to close the socket. If there is pending data waiting to be written, QAbstractSocket will enter ClosingState and wait until all data has been written. Eventually, it will enter UnconnectedState and emit the disconnected() signal.
    b）等待TCP断开连接函数：bool waitForDisconnected(int msecs = 30000)，同样是从QAbstractSocket继承下来的public function，同时它又是一个virtual function。作用为：Waits until the socket has disconnected, up to msecs milliseconds. If the connection has been disconnected, this function returns true; otherwise it returns false. In the case where it returns false, you can call error() to determine the cause of the error.
1.3 读取服务器发送过来的数据
    readyRead()是QTcpSocket从父类QIODevice中继承下来的信号：This signal is emitted once every time new data is available for reading from the device’s current read channel。
    readyRead()对应的槽函数为：
    void MyTcpClient::ReadData()
    {
        QByteArray buffer = tcpClient->readAll();
        if(!buffer.isEmpty())
        {
            ui->edtRecv->append(buffer);
        }
    }
    readAll()是QTcpSocket从QIODevice继承的public function，直接调用就可以读取从服务器发过来的数据了。
    error(QAbstractSocket::SocketError)是QTcpSocket从QAbstractSocket继承的signal， This signal is emitted after an error occurred. The socketError parameter describes the type of error that occurred.连接到的槽函数定义为：
    void MyTcpClient::ReadError(QAbstractSocket::SocketError)
    {
        tcpClient->disconnectFromHost();
        ui->btnConnect->setText(tr("连接"));
        QMessageBox msgBox;
        msgBox.setText(tr("failed to connect server because %1").arg(tcpClient->errorString()));
    }
    作用是：当错误发生时，首先断开TCP连接，再用QMessageBox提示出errorString，即错误原因。
1.4 向服务器发送数据
    QString data = ui->edtSend->toPlainText();
    if(data != "")
    {
        tcpClient->write(data.toLatin1()); //qt5去除了.toAscii()
    }

2 服务器端编程
遇到的问题：每个新加入的客户端，服务器给其分配一个SocketDescriptor后，就会emit newConnection()信号，但分配好的SocketDecriptor并没有通过newConnection()信号传递，所以用户得不到这个客户端标识　　SocketDescriptor。同样的，每当服务器收到新的消息时，客户端会emit readReady()信号，然而readReady()信号也没有传递SocketDescriptor， 这样的话，服务器端即使接收到消息，也不知道这个消息是从哪个客户端发出的。
解决的方法：
　　1. 通过重写[virtual protected] void QTcpServer::incomingConnection(qintptr socketDescriptor)，获取soketDescriptor。自定义TcpClient类继承QTcpSocket，并将获得的soketDescriptor作为类成员。 这个方法的优点是：可以获取到soketDescriptor，灵活性高。缺点是：需要重写函数、自定义类。
　　2. 在newConnection()信号对应的槽函数中，通过QTcpSocket *QTcpServer::nextPendingConnection()函数获取 新连接的客户端：Returns the next pending connection as a connected QTcpSocket object. 虽然仍然得不到soketDescriptor，但可以通过QTcpSocket类的peerAddress()和peerPort()成员函数获取客户端的IP和端口号，同样是唯一标识。 优点：无需重写函数和自定义类，代码简洁。缺点：无法获得SocketDecriptor，灵活性差。
本文介绍第二种方法
2.1 初始化QTcpServer
    tcpServer = new QTcpServer(this);
    ui->edtIP->setText(QNetworkInterface().allAddresses().at(1).toString());   //获取本地IP
    ui->btnConnect->setEnabled(true);
    ui->btnSend->setEnabled(false);
    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(NewConnectionSlot()));
    通过QNetworkInterface().allAddresses().at(1)获取到本机IP显示在lineEditor上（edtIP）。
    [static] QList<QHostAddress> QNetworkInterface::allAddresses() This convenience function returns all IP addresses found on the host machine. It is equivalent to calling addressEntries() on all the objects returned by allInterfaces() to obtain lists of QHostAddress objects then calling QHostAddress::ip() on each of these.： 每当新的客户端连接到服务器时，newConncetion()信号触发，NewConnectionSlot()是用户的槽函数，定义如下
    void MyTcpServer::NewConnectionSlot()
    {
        currentClient = tcpServer->nextPendingConnection();
        tcpClient.append(currentClient);
        ui->cbxConnection->addItem(tr("%1:%2").arg(currentClient->peerAddress().toString().split("::ffff:")[1])\
                                            .arg(currentClient->peerPort()));
        connect(currentClient, SIGNAL(readyRead()), this, SLOT(ReadData()));
        connect(currentClient, SIGNAL(disconnected()), this, SLOT(disconnectedSlot()));
    }
    通过nextPendingConnection()获得连接过来的客户端信息，取到peerAddress和peerPort后显示在comboBox(cbxConnection)上，并将客户端的readyRead()信号连接到服务器端自定义的读数据槽函数ReadData()上。将客户端的disconnected()信号连接到服务器端自定义的槽函数disconnectedSlot()上。
2.2 监听端口 与 取消监听
    bool ok = tcpServer->listen(QHostAddress::Any, ui->edtPort->text().toInt());
     if(ok)
     {
         ui->btnConnect->setText("断开");
         ui->btnSend->setEnabled(true);
     }
    a）监听端口的函数：bool QTcpServer::listen(const QHostAddress &*address* = QHostAddress::Any, quint16 *port* = 0),该函数的作用为：Tells the server to listen for incoming connections on address *address* and port *port*. If port is 0, a port is chosen automatically. If address is QHostAddress::Any, the server will listen on all network interfaces. Returns true on success; otherwise returns false.
    for(int i=0; i<tcpClient.length(); i++)//断开所有连接
     {
         tcpClient[i]->disconnectFromHost();
         bool ok = tcpClient[i]->waitForDisconnected(1000);
         if(!ok)
         {
             // 处理异常
         }
         tcpClient.removeAt(i);  //从保存的客户端列表中取去除
     }
     tcpServer->close();     //不再监听端口
     b）断开客户端与服务器连接的函数：disconnectFromHost()和waitForDisconnected()上文已述。断开连接之后，要将其从QList tcpClient中移除。服务器取消监听的函数：tcpServer->close()。
     //由于disconnected信号并未提供SocketDescriptor，所以需要遍历寻找
    for(int i=0; i<tcpClient.length(); i++)
    {
        if(tcpClient[i]->state() == QAbstractSocket::UnconnectedState)
        {
            // 删除存储在combox中的客户端信息
            ui->cbxConnection->removeItem(ui->cbxConnection->findText(tr("%1:%2")\
                                  .arg(tcpClient[i]->peerAddress().toString().split("::ffff:")[1])\
                                  .arg(tcpClient[i]->peerPort())));
            // 删除存储在tcpClient列表中的客户端信息
             tcpClient[i]->destroyed();
             tcpClient.removeAt(i);
        }
    }
    c）若某个客户端断开了其与服务器的连接，disconnected()信号被触发，但并未传递参数。所以用户需要遍历tcpClient list来查询每个tcpClient的state()，若是未连接状态（UnconnectedState），则删除combox中的该客户端，删除tcpClient列表中的该客户端，并destroy()。
2.3 读取客户端发送过来的数据
    // 客户端数据可读信号，对应的读数据槽函数
    void MyTcpServer::ReadData()
    {
        // 由于readyRead信号并未提供SocketDecriptor，所以需要遍历所有客户端
        for(int i=0; i<tcpClient.length(); i++)
        {
            QByteArray buffer = tcpClient[i]->readAll();
            if(buffer.isEmpty())    continue;

            static QString IP_Port, IP_Port_Pre;
            IP_Port = tr("[%1:%2]:").arg(tcpClient[i]->peerAddress().toString().split("::ffff:")[1])\
                                         .arg(tcpClient[i]->peerPort());

            // 若此次消息的地址与上次不同，则需显示此次消息的客户端地址
            if(IP_Port != IP_Port_Pre)
                ui->edtRecv->append(IP_Port);

            ui->edtRecv->append(buffer);

            //更新ip_port
            IP_Port_Pre = IP_Port;
        }
    }
    这里需要注意的是，虽然tcpClient产生了readReady()信号，但readReady()信号并没有传递任何参数，当面向多连接客户端时，tcpServer并不知道是哪一个tcpClient是数据源，所以这里遍历tcpClient列表来读取数据（略耗时，上述的解决方法1则不必如此）。 读操作由tcpClient变量处理：tcpClient[i]->readAll();
2.4 向客户端发送数据
    //全部连接
    if(ui->cbxConnection->currentIndex() == 0)
    {
        for(int i=0; i<tcpClient.length(); i++)
            tcpClient[i]->write(data.toLatin1()); //qt5除去了.toAscii()
    }
    a）向当前连接的所有客户端发数据，遍历即可。
    //指定连接
    QString clientIP = ui->cbxConnection->currentText().split(":")[0];
    int clientPort = ui->cbxConnection->currentText().split(":")[1].toInt();
    for(int i=0; i<tcpClient.length(); i++)
    {
        if(tcpClient[i]->peerAddress().toString().split("::ffff:")[1]==clientIP\
                        && tcpClient[i]->peerPort()==clientPort)
        {
            tcpClient[i]->write(data.toLatin1());
            return; //ip:port唯一，无需继续检索
        }
    }
    b）在comboBox(cbxConnction)中选择指定连接发送数据：通过peerAddress和peerPort匹配客户端，并发送。写操作由tcpClient变量处理：tcpClient[i]->write()。
至此，通过4步，我们就完成了TCP Server的程序开发







sokect断开的几种情况
1 显式断开连接：您可以在代码中显式地调用QAbstractSocket类的disconnectFromHost()或close()方法来断开连接。
    socket->disconnectFromHost();  或者 socket->close();
2 连接错误：当Socket遇到连接错误时，连接会自动断开。可以通过监听error()信号来处理连接错误。
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(handleError(QAbstractSocket::SocketError)));
3 连接超时：如果在指定的时间内无法建立连接，Socket会自动断开。可以使用QAbstractSocket类的connectToHost()方法的重载版本来设置连接超时时间。
    socket->connectToHost(host, port);
    socket->waitForConnected(timeout); // 设置连接超时时间
4 远程主机关闭连接：当远程主机关闭连接时，Socket会自动检测到并断开连接。可以通过监听disconnected()信号来处理连接断开事件。
connect(socket, SIGNAL(disconnected()), this, SLOT(handleDisconnected()));
请注意，Socket的断开连接可能是异步的，因此建议在适当的时候检查连接状态，例如使用state()方法来获取当前连接状态。

if (socket->state() == QAbstractSocket::ConnectedState) { // Socket已连接 }
else { // Socket未连接 }
总之，在Qt中，Socket的连接可以在多个时刻被断开，具体取决于您的代码逻辑以及网络条件。
5 在Qt中，Socket的连接在长时间没有通信时可能会自动断开。这是由操作系统和网络协议栈的设置决定的，而不是Qt库本身的行为。具体的断开时间取决于操作系统和网络环境的配置。
在TCP协议中，通常会使用"keep-alive"机制来检测长时间没有通信的连接，并在一定时间内没有收到数据时自动断开连接。这个时间通常被称为"keep-alive timeout"或"TCP keep-alive timeout"。不同的操作系统和网络设备可能有不同的默认超时时间，通常在几分钟到几个小时之间。
在Qt中，可以通过设置QAbstractSocket类的setSocketOption()方法来调整keep-alive参数。例如，可以使用QAbstractSocket::KeepAliveOption选项来启用或禁用keep-alive机制：
    socket->setSocketOption(QAbstractSocket::KeepAliveOption, true);
请注意，即使启用了keep-alive机制，具体的超时时间仍然取决于操作系统和网络环境的配置。如果您需要更精确地控制连接的断开时间，可以考虑在应用程序中定期发送心跳消息来保持连接活跃，而不依赖于操作系统的超时机制。





QTcpSocket碰到的ConnectToHost失败问题
尝试Qt的QTcpSocket，发现ConnectToHost失败，waitForConnected一直返回false。
是QNetworkProxy::HttpProxy 原因。
关掉了全局SSR，发现成功了。原来开了这玩意儿会走httpproxy。如果想要在翻墙情况下连接，可以使用setProxy(QNetworkProxy::NoProxy)。
Qt6的TCP在Connect的时候，此时若你处于翻墙状态，连接是直接成功的。但此时端到端的通信是不通的（报文无法正常收发），需要关闭翻墙，然后重新connect才能正常使用。



QTcpSocket的连续发送数据和连续接收数据
用QTcpSocket的write（）一数据，然后接收方只要emit一个readyread（）信号然后就用QTcpSocket的read（）去读。本以为只要发送方write一次，接收方就会响应readyRead信号。其实根本就不是这样的，readyRead不会知道发送方调用了几个write，它只负责在有数据到达时触发，等你真正接收时，或许已经能够收到所有的数据了。这要看你发送的信息量了，如果很少的话，比如发送几个字节的数据当然没有问题，一次readyRead就能读到所有数据但切记，这不是必然的！另外readRead到底能读多少数据是不确定的，这要看你的网速情况，还有你的电脑的性能了。

举个例子，我在编程时用发送方while（）连续向网络上传输数据，这个文件的数据量很大，就要使用waitForBytesWritten做一下等待，这就是每次等上一个write（）完毕后才继续下一个write（）这样数据就不会漏或者乱。还有一个问题是要传输数据时一定要先告诉接收方发的数据量是多大，也就是在发真正的数据时的头部用2个字节（quint16）或四个字节（quint32）去存放传送数据的大小。接收方就是根据这个传输数据的大小和每次bytesAvailable()的大小做对比若小就不断的触发emit的信号，在去接收，知道最终接收的总数据跟发送方的数据大小是一致的就说明接收完毕。这就解决了大数据量连续发送与接收的问题。






