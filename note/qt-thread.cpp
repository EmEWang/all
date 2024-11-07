

锁机制
QMutex(互斥锁)            // 最常见的锁类型，用于实现简单的互斥访问。通过lock()和unlock()手动控制锁的加锁和解锁。
QMutexLocker              // 一个RAII类，简化对QMutex的加锁和解锁过程。创建QMutexLocker对象时自动加锁，离开作用域时会自动解锁。
QReadWriteLock(读写锁)     // 允许多个线程同时读，但只有一个线程写。通过lockForRead()和lockForWrite()手动控制读取锁和写入锁。
QReadLocker和QWriteLocker // 是QReadWriteLock的RAII类，在创建对象时自动加读锁或写锁，离开作用域时会自动解锁。
QSemaphore(信号量)        // 允许控制对共享资源的并发访问数量。可以通过acquire()和release()手动控制资源的获取和释放。
QWaitCondition(条件变量)  // 用于线程间的等待和唤醒，允许一个线程等待特定条件的发生，并在其他线程满足条件时发出信号

QMutex mutex;              // QMutex（互斥锁）
for (int i = 0; i < 1000; ++i) {
    mutex.lock();
    xxx;
    mutex.unlock();
}

QMutex mutex;              // QMutexLocker的例子
for (int i = 0; i < 1000; ++i) {
    QMutexLocker locker(&mutex);
    xxx;
}

QReadWriteLock rwLock;     // QReadWriteLock（读写锁）
int data = 0;
for (int i = 0; i < 100; ++i) {  // 读取操作
    QReadLocker locker(&rwLock);
    qDebug() << "Read data:" << data;
}
for (int i = 0; i < 10; ++i) {   // 写入操作
    QWriteLocker locker(&rwLock);
    data += 10;
    qDebug() << "Write data:" << data;
}

QSemaphore semaphore(1); // 初始信号量计数为1   QSemaphore（信号量）
QThread thread1, thread2;// 创建两个线程，模拟同时访问共享资源
QObject::connect(&thread1, &QThread::started, [&]() {
    semaphore.acquire();
    qDebug() << "Thread 1: Accessing shared resource...";
    QThread::sleep(2); // 模拟资源访问
    semaphore.release();
    qDebug() << "Thread 1: Done!";
});
QObject::connect(&thread2, &QThread::started, [&]() {
    semaphore.acquire();
    qDebug() << "Thread 2: Accessing shared resource...";
    QThread::sleep(2); // 模拟资源访问
    semaphore.release();
    qDebug() << "Thread 2: Done!";
});
thread1.start();
thread2.start();
thread1.wait();
thread2.wait();

QMutex mutex;             // QWaitCondition（条件变量）
QWaitCondition condition;
bool isReady = false;
QThread waitThread; // 等待线程
QObject::connect(&waitThread, &QThread::started, [&]() {
    QMutexLocker locker(&mutex);
    qDebug() << "Waiting thread: Waiting for condition...";
    condition.wait(&mutex);
    qDebug() << "Waiting thread: Condition signaled!";
});
QThread signalThread;// 发送信号线程
QObject::connect(&signalThread, &QThread::started, [&]() {
    QThread::sleep(2);
    QMutexLocker locker(&mutex);
    isReady = true;
    qDebug() << "Signaling thread: Condition is ready!";
    condition.wakeOne();
});
waitThread.start();
signalThread.start();
waitThread.wait();
signalThread.wait();


