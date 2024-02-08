#include "cpp11_2.h"

// using namespace std;
# include <stdio.h>
# include <stdlib.h>

void thread_foo(){std::this_thread::sleep_for(std::chrono::seconds(1));}
void thread_foo2(){
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "[tid]" << std::this_thread::get_id() << std::endl;
}
void thread_foo3(std::thread *t){
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "[tid]" << t->get_id() << std::endl;
}
void ThreadFunc(int a){ std::cout << "Thread1 " << a << std::endl;}
void ThreadFunc1(int& x){x += 10;}
void ThreadFunc2(int* x){*x += 10;}
void ThreadFunc3() { std::cout << "ThreadFunc()" << std::endl; }
bool DoSomething3() { return false; }
void ThreadFunc32() { std::cout << "ThreadFunc()" << std::endl; }
void Test32() { throw 1; }
void test1_cpp11_2_thread()
{
    // 标准库线程，头文件 <thread>
    // 1 线程的启动
    // C++线程库通过构造一个线程对象来启动一个线程，该线程对象中就包含了线程运行时的上下文环境，比如：线程函数、
    //  线程栈、线程起始状态等以及线程ID等，所有操作全部封装在一起，最后在底层统一传递给_beginthreadex()
    //  创建线程函数来实现(注意：_beginthreadex是windows中创建线程的底层c函数)。windows
    // std::thread类方法简单介绍
    // thread()                    构造一个线程对象，没有关联任何线程函数，即没有启动任何线程
    // thread(fn, args1, args2, …) 构造一个线程对象，并关联线程函数fn，args1，args2，…为线程函数的参数
    // get_id()                    获取线程id
    // jionable()                  线程是否还在执行，joinable代表的是一个正在执行中的线程。
    // jion()                      该函数调用后会阻塞住线程，当该线程结束后，主线程继续执行
    // detach()                    创建线程对象后马上调用，被创建线程与主线程分离，分离的线程变为后台线程
    //
    // 线程是操作系统中的一个概念，线程对象可以关联一个线程，用来控制线程以及获取线程的状态。
    // 当创建一个线程对象后，没有提供线程函数，该对象实际没有对应任何线程。
    // 当创建一个线程对象后，给线程关联线程函数，该线程就被启动，与主线程一起运行。
    // std::thread()创建一个新的线程可以接受任意的可调用对象类型（带参数或者不带参数），
    //  包括lambda表达式（带变量捕获或者不带），函数，函数对象，以及函数指针。
    //
    // get_id()的返回值类型为thread::id类型，id类型实际为std::thread命名空间下封装的一个类，该类中包含了一个结构体：
    // typedef struct    // vs下查看
    // {   /* thread identifier for Win32 */
    //     void* _Hnd; /* Win32 HANDLE */
    //     unsigned int _Id;
    // } _Thrd_imp_t;
    //
    // thread类是防拷贝的，不允许拷贝构造以及赋值，但是可以移动构造和移动赋值，
    //  即将一个线程对象关联线程的状态转移给其他线程对象，转移期间不影响线程的执行。
    // 可以通过jionable()函数判断线程是否是有效的，如果是以下任意情况，则线程无效
    //   1 采用无参构造函数构造的线程对象
    //   2 线程对象的状态已经转移给其他线程对象
    //   3 线程已经调用jion或者detach结束
    // 并发与并行的区别？
    //   1 并行是指两个或者多个事件在同一时刻发生；而并发是指两个或多个事件在同一时间间隔发生。
    //   2 并行是在不同实体上的多个事件，并发是在同一实体上的多个事件。
    //   3 在一台处理器上“同时”（这个同时实际上市交替“”）处理多个任务，在多台处理器上同时处理多个任务
    {
        std::cout << "1 thread create" << std::endl;
        int n1 = 500;
        int n2 = 600;
        class TF {
        public:
            void operator()() {std::cout << "Thread3" << std::endl;}
        };

        std::thread t1(ThreadFunc, 10);                             // 线程函数为函数指针
        std::thread t2([] {std::cout << "Thread2" << std::endl; }); // 线程函数为lambda表达式
        std::thread t2_2([&](int addNum) {                     // 线程函数为lambda表达式2
            n1 += addNum;
            n2 += addNum;
            std::cout << "use lambda create" << std::endl;
            }, 111);
        TF tf;
        std::thread t3(tf);                                         // 线程函数为函数对象

        t1.join();
        t2.join();
        t2_2.join();
        t3.join();
        std::cout << n1 << ' ' << n2 << std::endl;  // 611 711
        std::cout << "1 thread create end" << std::endl;
    }

    // 2 线程函数参数
    // 线程函数的参数是以值拷贝的方式拷贝到线程栈空间中的，
    // 即使线程参数为引用类型，在线程中修改后也不能修改外部实参，因为其实际引用的是线程栈中的拷贝，而不是外部实参。
    // 注意：如果是类成员函数作为线程参数时，必须将this作为线程函数参数。
    {
        std::cout << "2 thread params" << std::endl;
        int a = 10;

        // 编译失败
        // std::thread t1(ThreadFunc1, a);  // 在线程函数中对a修改，不会影响外部实参，即使线程参数为引用类型
        // t1.join();
        // std::cout << a << std::endl;   // 10

        std::thread t2(ThreadFunc1, std::ref(a)); // 要通过形参改变外部实参时，必须借助std::ref()函数
        t2.join();
        std::cout << a << std::endl;   // 20

        std::thread t3(ThreadFunc2, &a);   // 地址的拷贝
        t3.join();
        std::cout << a << std::endl;   // 30
        std::cout << "2 thread params end" << std::endl;
    }


    // 3 线程的结束
    // 启动了一个线程后，当这个线程结束的时候，如何去回收线程所使用的资源呢？thread库给我们两种选择：
    // 3.1 加入式：join()
    // 主线程被阻塞，当新线程终止时，join()会清理相关的线程资源，然后返回，主线程再继续向下执行，然后销毁线程对象。
    // 由于join()清理了线程的相关资源，thread对象与已销毁的线程就没有关系了，因此一个线程对象只能使用一次join()，否则程序崩溃。
    // 当你调用的join()之后joinable()就将返回false了。
    // 因此：采用jion()方式结束线程时，jion()的调用位置非常关键。为了避免该问题，可以采用RAII的方式对线程对象进行封装
    // 3.2 分离式：deatch()
    // deatch()会从调用线程中分理出新的线程，之后不能再与新线程交互。
    // detach()被调用后，新线程与线程对象分离，不再被线程对象所表达，就不能通过线程对象控制线程了，
    //  新线程会在后台运行，其所有权和控制权将会交给c++运行库。同时，C++运行库保证，当线程退出时，其相关资源的能够正确的回收。
    // detach()函数一般在线程对象创建好之后立刻调用，因为如果不是jion()等待方式结束，
    //  那么线程对象可能会在新线程结束之前被销毁掉而导致程序崩溃。
    // 因为std::thread的析构函数中，如果线程的状态是jionable，std::terminate将会被调用，而terminate()函数直接会终止程序。
    // 因此：线程对象销毁前，要么以jion()的方式等待线程结束，要么以detach()的方式将线程与线程对象分离。
    {
        std::cout << "3 thread join/detach" << std::endl;
        std::cout << "---thread1---test joinable" << std::endl;
        std::thread t1(thread_foo);
        std::cout << "before join, joinable=" << t1.joinable() << std::endl;
        t1.join();
        std::cout << "after join, joinable=" << t1.joinable() << std::endl;
        std::cout << "---thread1" << std::endl;

        std::cout << "---thread2---test tid" << std::endl;
        std::thread t2(thread_foo2);
        std::cout << "get tid" << std::endl;
        t2.join();
        std::cout << "---thread2" << std::endl;

        std::cout << "---thread3---test tid" << std::endl;
        std::thread *t3;
        t3 = new std::thread(thread_foo3, t3);
        t3->join();
        std::cout << "---thread3" << std::endl;
        std::cout << "3 thread join/detach end" << std::endl;
    }

    // jion()的误用一
    // 如果DoSomething()函数返回false,主线程将会结束，jion()没有调用，线程资源没有回收，造成资源泄漏。
    {
        std::cout << "3.1 thread join misuse 1" << std::endl;
        std::thread t(ThreadFunc3);
        if (!DoSomething3())
            std::cout << "!DoSomething3" << std::endl;

        t.join();
        std::cout << "DoSomething3" << std::endl;
        std::cout << "3.1 thread join misuse 1 end" << std::endl;
    }

    // jion()的误用二
    {
        std::cout << "3.2 thread join misuse 2" << std::endl;
        int* p = new int[10];
        std::thread t(ThreadFunc32);
        try
        {
            Test32();
        }
        catch (...)
        {
            delete[] p;
            throw;
        }

        t.join();
        std::cout << "3.2 thread join misuse 2 end" << std::endl;
    }



    // 4 原子性操作库(atomic)
    // 库：#include <atomic>
    // 多线程最主要的问题是共享数据带来的问题(即线程安全)。如果共享数据都是只读的，那么没问题，因为只读操作不会影响到数据，
    // 更不会涉及对数据的修改，所以所有线程都会获得同样的数据。但是，当一个或多个线程要修改共享数据时，就会产生很多潜在的麻烦。
    // atomic_int: 即为int类的原子变量，其他只需要在内置类型前加上atomic_ 即可
    // 原子变量多线程安全无需加锁。为线程安全问题而生，也可以加锁解决。

    //contained type        atomic type           description
    //bool                  atomic_bool
    //char                  atomic_char           atomics for fundamental integral types.
    //signed char           atomic_schar          These are either typedefs of the corresponding full specialization of the atomic class template or a base class of such specialization.
    //unsigned char         atomic_uchar
    //short                 atomic_short
    //unsigned short        atomic_ushort
    //int                   atomic_int
    //unsigned int          atomic_uint
    //long                  atomic_long
    //unsigned long         atomic_ulong
    //long long             atomic_llong
    //unsigned long long    atomic_ullong
    //wchar_t               atomic_wchar_t
    //char16_t              atomic_char16_t
    //char32_t              atomic_char32_t
    //intmax_t              atomic_intmax_t       atomics for width - based integrals(those defined in <cinttypes>).
    //uintmax_t             atomic_uintmax_t      Each of these is either an alias of one of the above atomics for fundamental integral types or of a full specialization of the atomic class template with an extended integral type.
    //int_leastN_t          atomic_int_leastN_t   Where N is one in 8, 16, 32, 64, or any other type width supported by the library.
    //uint_leastN_t         atomic_uint_leastN_t
    //int_fastN_t           atomic_int_fastN_t
    //uint_fastN_t          atomic_uint_fastN_t
    //intptr_t              atomic_intptr_t
    //uintptr_t             atomic_uintptr_t
    //size_t                atomic_size_t
    //ptrdiff_t             atomic_ptrdiff_t

    {
        std::mutex m;
        unsigned long sum = 0L;
        auto func = [&](size_t num)
        {
            for (size_t i = 0; i < num; ++i)
            {
                m.lock();
                sum++;
                m.unlock();
            }
        };

        std::cout << "4 thread lock Before joining,sum = " << sum << std::endl;
        std::thread t1(func, 10000000);
        std::thread t2(func, 10000000);
        t1.join();
        t2.join();
        std::cout << "4 thread lock After joining,sum = " << sum << std::endl;
    }
    // 虽然加锁可以解决，但是加锁有一个缺陷就是：只要一个线程在对sum++时，其他线程就会被阻塞，会影响程序运行的效率，
    //  而且锁如果控制不好，还容易造成死锁。
    // 因此C++11中引入了原子操作。所谓原子操作：即不可被中断的一个或一系列操作，使得线程间数据的同步变得非常高效。

    {
        std::atomic_long sum{ 0 };
        // atomic_long sum{ 0 };    // vs2019

        auto func4 = [&](size_t num)
        {
            for (size_t i = 0; i < num; ++i)
                sum++;   // 原子操作
        };

        std::cout << "4.1 thread atomic Before joining, sum = " << sum << std::endl;

        std::thread t1(func4, 1000000);
        std::thread t2(func4, 1000000);
        t1.join();
        t2.join();

        std::cout << "4.1 thread atomic After joining, sum = " << sum << std::endl;
    }

    // 在C++11中，不需要对原子类型变量进行加锁解锁操作，线程能够对原子类型变量互斥的访问。
    // 更为普遍的，可以使用atomic类模板，定义出需要的任意原子类型
    // atmoic<T> t;    // 声明一个类型为T的原子类型变量t
    // 注意：原子类型通常属于"资源型"数据，多个线程只能访问单个原子类型的拷贝，因此在C++11中，原子类型只能从其模板参数中进行构造，
    // 不允许原子类型进行拷贝构造、移动构造以及operator = 等，为了防止意外，标准库已经将atmoic模板类中的拷贝构造、移动构造、赋值运算符重载默认删除掉了。
    {
        std::atomic<int> a1(0);
        //atomic<int> a2(a1);    // 编译失败
        std::atomic<int> a2(0);
        //a2 = a1;               // 编译失败
    }


    // 5 lock_guard与unique_lock
    // 在多线程环境下，如果想要保证某个变量的安全性，只要将其设置成对应的原子类型即可，即高效又不容易出现死锁问题。
    //  但是有些情况下，我们可能需要保证一段代码的安全性，那么就只能通过锁的方式来进行控制。
    //
    // 5.1 Mutex的种类
    // 在C++11中，Mutex总共包了四个互斥量的种类：
    //
    // 1. std::mutex
    // C++11提供的最基本的互斥量，该类的对象之间不能拷贝，也不能进行移动。mutex最常用的三个函数：
    //
    // 函数名       函数功能
    // lock()      上锁：锁住互斥量
    // unlock()    解锁：释放对互斥量的所有权
    // try_lock()  尝试锁住互斥量，如果互斥量被其他线程占有，则当前线程也不会被阻塞
    //
    // 注意，线程函数调用lock()时，可能会发生以下三种情况：
    //   1 如果该互斥量当前没有被锁住，则调用线程将该互斥量锁住，直到调用 unlock之前，该线程一直拥有该锁
    //   2 如果当前互斥量被其他线程锁住，则当前的调用线程被阻塞住
    //   3 如果当前互斥量被当前调用线程锁住，则会产生死锁(deadlock)
    //
    // 线程函数调用try_lock()时，可能会发生以下三种情况：
    //   1 如果当前互斥量没有被其他线程占有，则该线程锁住互斥量，直到该线程调用 unlock 释放互斥量
    //   2 如果当前互斥量被其他线程锁住，则当前调用线程返回 false，而并不会被阻塞掉
    //   3 如果当前互斥量被当前调用线程锁住，则会产生死锁(deadlock)
    //
    // 2. std::recursive_mutex
    // 其允许同一个线程对互斥量多次上锁（即递归上锁），来获得对互斥量对象的多层所有权，
    //  释放互斥量时需要调用与该锁层次深度相同次数的 unlock()，
    //  除此之外，std::recursive_mutex 的特性和std::mutex 大致相同。
    //
    // 3. std::timed_mutex
    // 比 std::mutex 多了两个成员函数，try_lock_for()，try_lock_until() 。
    //
    // try_lock_for()
    // 接受一个时间范围，表示在这一段时间范围之内线程如果没有获得锁则被阻塞住（与 std::mutex的 try_lock() 不同，
    //  try_lock 如果被调用时没有获得锁则直接返回 false），如果在此期间其他线程释放了锁，
    //  则该线程可以获得对互斥量的锁，如果超时（即在指定时间内还是没有获得锁），则返回 false。
    // try_lock_until()
    // 接受一个时间点作为参数，在指定时间点未到来之前线程如果没有获得锁则被阻塞住，如果在此期间其他线程释放了锁，
    //  则该线程可以获得对互斥量的锁，如果超时（即在指定时间内还是没有获得锁），则返回 false。
    //
    // 4. std::recursive_timed_mutex
    //
    // 5.2 lock_guard
    // std::lock_guard 是 C++11 中定义的模板类。定义如下：
    //
    // template<class _Mutex>
    // class lock_guard
    // {
    // public:
        // 在构造lock_guard时，_Mtx还没有被上锁
    //     explicit lock_guard(_Mutex& _Mtx)
    //         : _MyMutex(_Mtx)
    //     {
    //         _MyMutex.lock();
    //     }

        // 在构造lock_gard时，_Mtx已经被上锁，此处不需要再上锁
    //     lock_guard(_Mutex& _Mtx, adopt_lock_t tag)
    //         : _MyMutex(_Mtx)
    //     {}

    //     ~lock_guard() _NOEXCEPT
    //     {
    //         _MyMutex.unlock();
    //     }

    //     lock_guard(const lock_guard&) = delete;
    //     lock_guard& operator=(const lock_guard&) = delete;

    // private:
    //     _Mutex& _MyMutex;
    // };

    // lock_guard类模板主要是通过RAII的方式，对其管理的互斥量进行了封装，
    // 在需要加锁的地方，只需要用上述介绍的任意互斥体实例化一个lock_guard，调用构造函数成功上锁，
    // 出作用域前，lock_guard对象要被销毁，调用析构函数自动解锁，可以有效避免死锁问题。
    // lock_guard的缺陷：太单一，用户没有办法对该锁进行控制，因此C++11又提供了unique_lock。
    {
        std::mutex mu;
        std::lock_guard<std::mutex> lock(mu);
    }

    // 5.3 unique_lock
    // 与lock_gard类似，unique_lock类模板也是采用RAII的方式对锁进行了封装，
    // 并且也是以独占所有权的方式管理mutex对象的上锁和解锁操作，即其对象之间不能发生拷贝。
    // 在构造(或移动(move)赋值)时，unique_lock 对象需要传递一个 Mutex 对象作为它的参数，
    // 新创建的 unique_lock 对象负责传入的 Mutex对象的上锁和解锁操作。
    // 使用以上类型互斥量实例化unique_lock的对象时，自动调用构造函数上锁，
    //  unique_lock对象销毁时自动调用析构函数解锁，可以很方便的防止死锁问题。
    // 与lock_guard不同的是，unique_lock更加的灵活，提供了更多的成员函数：
    // 上锁/解锁操作：lock、try_lock、try_lock_for、try_lock_until和unlock
    // 修改操作：移动赋值、交换(swap：与另一个unique_lock对象互换所管理的互斥量所有权)、释放(release：返回它所管理的互斥量对象的指针，并释放所有权)
    // 获取属性：owns_lock(返回当前对象是否上了锁)、operator bool()(与owns_lock()的功能相同)、mutex(返回当前unique_lock所管理的互斥量的指针)。
}


#include <mutex>
#include <condition_variable>
#include <functional>
#include <queue>
#include <thread>
#include <iostream>
//固定线程数的线程池。
class FixedThreadPool
{
public:
    explicit FixedThreadPool(size_t threadCount) : _data(std::make_shared<data>())
    {
        for (size_t i = 0; i < threadCount; ++i)
        {
            std::thread([data = _data]
                {
                    std::unique_lock<std::mutex> guard(data->_mutex);
                    for (;;)
                    {
                        if (!data->_tasks.empty())
                        {
                            std::function<void()> currentTask = std::move(data->_tasks.front());
                            data->_tasks.pop();
                            guard.unlock();
                            currentTask();
                            guard.lock();
                        }
                        else if (data->_isShutdown)
                        {
                            break;
                        }
                        else
                        {
                            data->_condition.wait(guard);
                        }
                    }
                }).detach();
        }
    }

    FixedThreadPool() = default;
    FixedThreadPool(FixedThreadPool&&) = default;

    ~FixedThreadPool()
    {
        if ((bool)_data)
        {
            {
                std::lock_guard<std::mutex> guard(_data->_mutex);
                _data->_isShutdown = true;
            }
            _data->_condition.notify_all();
        }
    }

    template <class F>
    void execute(F&& task)
    {
        {
            std::lock_guard<std::mutex> guard(_data->_mutex);
            _data->_tasks.emplace(std::forward<F>(task));
        }
        _data->_condition.notify_one();
    }

private:
    struct data
    {
        std::mutex _mutex;
        std::condition_variable _condition;
        bool _isShutdown = false;
        std::queue<std::function<void()>> _tasks;
    };
    std::shared_ptr<data> _data;
};
void printTest(){std::cout << "Thread start id = " << std::this_thread::get_id() << std::endl;}
void test1_cpp11_2_threadpool()
{
    FixedThreadPool p(4);         //有4个线程的线程池
    for (int i = 0; i < 10; i++)  //初始化10个任务
    {
        p.execute(printTest);    //打印执行任务的线程的id
    }
    getchar();
}

void test1_cpp11_2_atomic()
{
    // #include <atomic>
    // https://zhuanlan.zhihu.com/p/672623300
    // 内存顺序
    // 顺序一致性（Sequential Consistency）：这是最直观的内存顺序，保证了所有操作按照程序的顺序执行。
    // 松散顺序（Relaxed Ordering）：允许操作重排序，但仍保证原子性。适用于某些性能敏感的场景。
    // memory_order_relaxed：最弱的内存顺序，只保证了操作的原子性，不保证操作间的顺序。
    // memory_order_acquire 和 memory_order_release：用于控制操作之间的重排序。
    //   acquire 防止之后的读写操作被重排序到它之前，而 release 防止之前的读写操作被重排序到它之后。
    // memory_order_acq_rel 和 memory_order_seq_cst：更严格的顺序保证。特别是 cst 提供了类似于单线程的执行顺序，默认。

    // 无锁编程
    std::atomic<int> counter = 0;
    int value;
    int value_new = 10;
    counter.store(10, std::memory_order_relaxed);    // 原子赋值
    value = counter.load(std::memory_order_relaxed); // 原子读取
    counter.fetch_add(1, std::memory_order_relaxed); // 原子加法
    counter.fetch_sub(1, std::memory_order_relaxed); // 原子减法
    counter++;                                       // 原子自增
    counter.compare_exchange_strong(value_new, 20);  // 原子比较并交换 允许在值未被其他线程更改的情况下更新一个原子变量
                                                     // 若 counter 的当前值等于 value_new，它被设置为 20。否则，操作失败

    // 举例
    // 1 is_ready.load确保了当 is_ready 变为真时，数据处理相关的操作能够安全地执行。
    std::atomic<bool> is_ready = true;
    while (!is_ready.load(std::memory_order_acquire)) {
        // 等待数据准备好
    }
    // 处理数据

    // 2 无锁队列 可改为模板 template<typename T> 需要外面定义
    class LockFreeQueue {
    private:
        struct Node {
            std::shared_ptr<int> data;
            std::atomic<Node*> next;
            Node(int newData) : data(std::make_shared<int>(newData)), next(nullptr) {}
        };
        std::atomic<Node*> head;
        std::atomic<Node*> tail;

    public:
        void enqueue(int newData) { // 入队操作
            Node* newNode = new Node(newData);
            Node* oldTail = tail.load();
            while (!tail.compare_exchange_weak(oldTail, newNode)) {
                // 循环直到尾部指针更新成功
            }
            oldTail->next = newNode;
        }
        std::shared_ptr<int> dequeue() { // 出队操作
            Node* oldHead = head.load();
            while (oldHead && !head.compare_exchange_weak(oldHead, oldHead->next)) {
                // 循环直到头部指针更新成功
            }
            return oldHead ? oldHead->data : std::shared_ptr<int>();
        }
    };

    // ABA问题
    // 是无锁编程中一个著名的问题，线程1读取一个值 A，然后在它能够执行更新之前，线程2将该值改变为 B，再改回 A。
    // 导致线程1错误地认为自己可以安全地继续执行操作。ABA 问题的存在不仅是技术挑战，也是对我们理解和处理复杂系统中变化的挑战。

}


#include <future>
template <typename RandomIt>
int parallel_sum(RandomIt beg, RandomIt end)
{
    // std::cout << "thread_id:" << std::this_thread::get_id() << std::endl;
    auto len = end - beg;
    if (len < 1000)
        return std::accumulate(beg, end, 0);

    RandomIt mid = beg + len / 2;
    auto handle = std::async(std::launch::async, parallel_sum<RandomIt>, mid, end);
    int sum = parallel_sum(beg, mid);
    return sum + handle.get();
}
std::mutex m_async;
void test1_cpp11_2_async()
{
    // https://blog.csdn.net/fengbingchun/article/details/104133494
    // std::async异步调用函数，在某个时候以Args作为参数(可变长参数)调用Fn，不等待Fn执行完就返回，结果是std::future对象。
    //  Fn返回的值可通过std::future对象的get成员函数获取。一旦完成Fn的执行，共享状态将包含Fn返回的值并ready。
    // template <class Fn, class... Args> future<typename result_of<Fn(Args...)>::type> async (Fn&& fn, Args&&... args);
    // template <class Fn, class... Args> future<typename result_of<Fn(Args...)>::type> async (launch policy, Fn&& fn, Args&&... args);
    // 参数Fn：可以为函数指针、成员指针、任何类型的可移动构造的函数对象(即类定义了operator()的对象)。
    //  Fn的返回值或异常存储在共享状态中以供异步的std::future对象检索。
    // 参数Args：传递给Fn调用的参数，它们的类型应是可移动构造的。
    // 返回值：当Fn执行结束时，共享状态的std::future对象准备就绪。std::future的成员函数get检索的值是Fn返回的值。
    //  当启动策略采用std::launch::async时，即使从不访问其共享状态，返回的std::future也会链接到被创建线程的末尾。
    //  在这种情况下，std::future的析构函数与Fn的返回同步。

    // http://www.cplusplus.com/reference/future/async/
    {
        std::cout << "test async -- 1 --\n";
        auto is_prime = [](int x) {
            std::cout << "Calculating. Please, wait...\n";
            for (int i = 2; i < x; ++i) if (x%i == 0) return false;
            return true;
        };

        std::future<bool> fut = std::async(is_prime, 313222313);
        std::cout << "Checking whether 313222313 is prime.\n";

        bool ret = fut.get(); // waits for is_prime to return
        if (ret) std::cout << "It is prime!\n";
        else std::cout << "It is not prime.\n";
// test async -- 1 --
// Checking whether 313222313 is prime.
// Calculating. Please, wait...
// It is prime!
    }

    // std::async的启动策略类型是个枚举类enum class launch，包括：
    //   std::launch::async：异步，启动一个新的线程调用Fn，该函数由新线程异步调用，并且将其返回值与共享状态的访问点同步。
    //   std::launch::deferred：延迟，在访问共享状态时该函数才被调用。
    //    对Fn的调用将推迟到返回的std::future的共享状态被访问时(使用std::future的wait或get函数)。
    // reference: http://www.cplusplus.com/reference/future/launch/
    {
        auto print_ten = [](char c, int ms) {
            for (int i = 0; i < 10; ++i) {
                std::this_thread::sleep_for(std::chrono::milliseconds(ms));
                std::cout << c;
            }
        };

        std::cout << "test async -- 2 -- with launch::async\n";
        std::future<void> foo = std::async(std::launch::async, print_ten, '*', 100);
        std::future<void> bar = std::async(std::launch::async, print_ten, '@', 200);
        // async "get" (wait for foo and bar to be ready):
        foo.get(); // 注：注释掉此句，也会输出'*'
        bar.get();
        std::cout << "\n\n";
// test async -- 2 -- with launch::async
// *@**@**@**@**@*@@@@@

        std::cout << "test async -- 2 -- with launch::deferred\n";
        foo = std::async(std::launch::deferred, print_ten, '*', 100);
        bar = std::async(std::launch::deferred, print_ten, '@', 200);
        // deferred "get" (perform the actual calls):
        foo.get(); // 注：注释掉此句，则不会输出'**********'
        bar.get();
        std::cout << '\n';
// test async -- 2 -- with launch::deferred
// **********@@@@@@@@@@
    }

    // https://en.cppreference.com/w/cpp/thread/async
    {
        // std::mutex m_async; // ! reference to local variable of enclosing function is not allowedC/C++(394)
        struct X {
            void foo(int i, const std::string& str) {
                std::lock_guard<std::mutex> lk(m_async);
                std::cout << str << ' ' << i << '\n';
            }
            void bar(const std::string& str) {
                std::lock_guard<std::mutex> lk(m_async);
                std::cout << str << '\n';
            }
            int operator()(int i) {
                std::lock_guard<std::mutex> lk(m_async);
                std::cout << i << '\n';
                return i + 10;
            }
        };

        std::cout << "test async -- 3 --\n";
        std::vector<int> v(10000, 1);
        std::cout << "The sum is " << parallel_sum(v.begin(), v.end()) << '\n';

        X x;
        // Calls (&x)->foo(42, "Hello") with default policy:
        // may print "Hello 42" concurrently or defer execution
        auto a1 = std::async(&X::foo, &x, 42, "Hello");
        // Calls x.bar("world!") with deferred policy
        // prints "world!" when a2.get() or a2.wait() is called
        auto a2 = std::async(std::launch::deferred, &X::bar, x, "world!");
        // Calls X()(43); with async policy
        // prints "43" concurrently
        auto a3 = std::async(std::launch::async, X(), 43);
        a2.wait();                     // prints "world!"
        std::cout << a3.get() << '\n'; // prints "53"
// The sum is 10000
// Hello 42
// world!
// 43
// 53
    }// if a1 is not done at this point, destructor of a1 prints "Hello 42" here

    // https://thispointer.com/c11-multithreading-part-9-stdasync-tutorial-example/
    {
        using namespace std::chrono;

        auto fetchDataFromDB = [](std::string recvdData) {
            // Make sure that function takes 5 seconds to complete
            std::this_thread::sleep_for(seconds(2));
            //Do stuff like creating DB Connection and fetching Data
            return "DB_" + recvdData;
        };

        auto fetchDataFromFile = [](std::string recvdData) {
            // Make sure that function takes 5 seconds to complete
            std::this_thread::sleep_for(seconds(2));
            //Do stuff like fetching Data File
            return "File_" + recvdData;
        };

        std::cout << "test async -- 4 --\n";
        // Get Start Time
        system_clock::time_point start = system_clock::now();

        std::future<std::string> resultFromDB = std::async(std::launch::async, fetchDataFromDB, "Data");

        //Fetch Data from File
        std::string fileData = fetchDataFromFile("Data");

        //Fetch Data from DB
        // Will block till data is available in future<std::string> object.
        std::string dbData = resultFromDB.get();

        // Get End Time
        auto end = system_clock::now();
        auto diff = duration_cast <std::chrono::seconds> (end - start).count();
        std::cout << "Total Time Taken = " << diff << " Seconds" << std::endl;

        //Combine The Data
        std::string data = dbData + " :: " + fileData;
        //Printing the combined Data
        std::cout << "Data = " << data << std::endl;
// test async -- 4 --
// Total Time Taken = 2 Seconds
// Data = DB_Data :: File_Data
    }
}
void test1_cpp11_2_future()
{
    // https://blog.csdn.net/fengbingchun/article/details/104115489
    // std::future提供了一种用于访问异步操作结果的机制。std::future所引用的共享状态不能与任何其它异步返回的对象共享
    // 有效的future是与共享状态(shared state)关联的future对象，可以通过调用以下函数(provider)来构造future对象：
    //  std::async、std::promise::get_future、std::packaged_task::get_future。future对象仅在它们是有效时才有用。
    // 模板类std::future成员函数包括：
    // 1. 构造函数：(1).不带参数的默认构造函数，此对象没有共享状态，因此它是无效的，但是可以通过移动赋值的方式将一个有效的future值赋值给它；(2).禁用拷贝构造；(3).支持移动构造。
    // 2. 析构函数：销毁future对象，它是异常安全的。
    // 3. get函数：(1).当共享状态就绪时，返回存储在共享状态中的值(或抛出异常)。(2).如果共享状态尚未就绪(即提供者尚未设置其值或异常)，则该函数将阻塞调用的线程直到就绪。(3).当共享状态就绪后，则该函数将取消阻塞并返回(或抛出)释放其共享状态，这使得future对象不再有效，因此对于每一个future共享状态，该函数最多应被调用一次。(4).std::future<void>::get()不返回任何值，但仍等待共享状态就绪并释放它。(5).共享状态是作为原子操作(atomic operation)被访问。
    // 4. operator=：(1).禁用拷贝赋值。(2).支持移动赋值：如果在调用之前，此对象是有效的(即它已经访问共享状态)，则将其与先前已关联的共享状态解除关联。如果它是与先前共享状态关联的唯一对象，则先前的共享状态也会被销毁。
    // 5. share函数：获取共享的future，返回一个std::shared_future对象，该对象获取future对象的共享状态。future对象将不再有效。
    // 6. valid函数：检查共享状态的有效性，返回当前的future对象是否与共享状态关联。一旦调用了std::future::get()函数，再调用此函数将返回false。
    // 7. wait函数：(1).等待共享状态就绪。(2).如果共享状态尚未就绪(即提供者尚未设置其值或异常)，则该函数将阻塞调用的线程直到就绪。(3).当共享状态就绪后，则该函数将取消阻塞并void返回。
    // 8. wait_for函数：(1).等待共享状态在指定的时间内(time span)准备就绪。(2). 如果共享状态尚未就绪(即提供者尚未设置其值或异常)，则该函数将阻塞调用的线程直到就绪或已达到设置的时间。(3).此函数的返回值类型为枚举类future_status。此枚举类有三种label：ready：共享状态已就绪；timeout：在指定的时间内未就绪；deferred：共享状态包含了一个延迟函数(deferred function)。
    // 9. wait_until函数：(1). 等待共享状态在指定的时间点(time point)准备就绪。(2). 如果共享状态尚未就绪(即提供者尚未设置其值或异常)，则该函数将阻塞调用的线程直到就绪或已达到指定的时间点。(3).此函数的返回值类型为枚举类future_status。

    // http://www.cplusplus.com/reference/future/future/
    { // constructor/get/operator=
        std::cout << "test future -- 1 -- constructor/get/operator=\n";
        auto get_value = []() { return 10; };
        std::future<int> foo; // default-constructed
        std::future<int> bar = std::async(get_value); // move-constructed

        int x = bar.get();
        std::cout << "value: " << x << '\n'; // 10

        //int x2 = bar.get(); // crash, 对于每个future的共享状态，get函数最多仅被调用一次
        //std::cout << "value: " << x2 << '\n';

        std::future<int> foo2(std::async(get_value));
        std::cout << "value: " << foo2.get() << '\n'; // 10
    }

    { // share
        std::cout << "test future -- 1 -- share\n";
        std::future<int> fut = std::async([]() { return 10; });
        std::shared_future<int> shfut = fut.share();

        //std::cout << "value: " << fut.get() << '\n'; // crash, 执行完fut.share()后，fut对象将变得无效
        std::cout << "fut valid: " << fut.valid() << '\n';// 0

        // shared futures can be accessed multiple times:
        std::cout << "value: " << shfut.get() << '\n'; // 10
        std::cout << "its double: " << shfut.get() * 2 << '\n'; // 20, 对于std::shared_future对象，get函数可以被多次访问
    }

    { // valid
        std::cout << "test future -- 1 -- valid\n";
        std::future<int> foo, bar;
        foo = std::async([]() { return 10; });
        bar = std::move(foo);

        if (foo.valid()) std::cout << "foo's value: " << foo.get() << '\n';
        else std::cout << "foo is not valid\n"; // foo is not valid

        if (bar.valid()) std::cout << "bar's value: " << bar.get() << '\n'; // 10
        else std::cout << "bar is not valid\n";
    }

    { // wait
        std::cout << "test future -- 1 -- wait\n";
        auto is_prime = [](int x) {
            for (int i = 2; i < x; ++i) if (x%i == 0) return false;
            return true;
        };

        // call function asynchronously:
        std::future<bool> fut = std::async(is_prime, 194232491);

        std::cout << "checking...\n";
        fut.wait();

        std::cout << "\n194232491 ";
        if (fut.get()) // guaranteed to be ready (and not block) after wait returns
            std::cout << "is prime.\n";
        else
            std::cout << "is not prime.\n";
    }

    { // wait_for
        std::cout << "test future -- 1 -- wait_for\n";
        auto is_prime = [](int x) {
            for (int i = 2; i < x; ++i) if (x%i == 0) return false;
            return true;
        };

        // call function asynchronously:
        std::future<bool> fut = std::async(is_prime, 700020007);

        // do something while waiting for function to set future:
        std::cout << "checking, please wait";
        std::chrono::milliseconds span(100);
        while (fut.wait_for(span) == std::future_status::timeout) // 可能多次调用std::future::wait_for函数
            std::cout << '.';

        bool x = fut.get(); // retrieve return value
        std::cout << "\n700020007 " << (x ? "is" : "is not") << " prime.\n";
    }

    // https://en.cppreference.com/w/cpp/thread/future
    {
        std::cout << "test future -- 2 --\n";
        // future from a packaged_task
        std::packaged_task<int()> task([] { return 7; }); // wrap the function
        std::future<int> f1 = task.get_future();  // get a future
        std::thread t(std::move(task)); // launch on a thread

        // future from an async()
        std::future<int> f2 = std::async(std::launch::async, [] { return 8; });

    #ifdef _MSC_VER
        // future from a promise
        std::promise<int> p;
        std::future<int> f3 = p.get_future();
        std::thread([&p] { p.set_value_at_thread_exit(9); }).detach(); // gcc 4.9 don't support this function
    #endif

        std::cout << "Waiting..." << std::flush;
        f1.wait();
        f2.wait();
    #ifdef _MSC_VER
        f3.wait();
    #endif
        std::cout << "Done!\nResults are: " << f1.get() << ' ' << f2.get() << ' '
    #ifdef _MSC_VER
            << f3.get()
    #endif
            << '\n';
        t.join();
// test future -- 2 --
// Waiting...Done!
// Results are: 7 8
    }

    // https://thispointer.com/c11-multithreading-part-8-stdfuture-stdpromise-and-returning-values-from-thread/
    {
        auto initiazer = [](std::promise<int> * promObj){
            std::cout << "Inside Thread" << std::endl;
            promObj->set_value(35);
        };

        std::cout << "test future -- 3 --\n";
        std::promise<int> promiseObj;
        std::future<int> futureObj = promiseObj.get_future();
        std::thread th(initiazer, &promiseObj);
        std::cout << "value: " << futureObj.get() << std::endl;
        th.join();

        // If std::promise object is destroyed before setting the value the calling get() function on associated std::future object will throw exception.
        // A part from this, if you want your thread to return multiple values at different point of time then
        // just pass multiple std::promise objects in thread and fetch multiple return values from thier associated multiple std::future objects.
// test future -- 3 --
// value: Inside Thread
// 35
    }
}
void test1_cpp11_2_promise()
{
    // https://blog.csdn.net/fengbingchun/article/details/104124174
    // C++11中的std::promise是个模板类。一个std::promise对象可以存储由future对象(可能在另一个线程中)检索的T类型的值或派生自std::exception的异常，并提供一个同步点。
    // 在构造std::promise对象时，该对象与新的共享状态(shared state)关联。通过调用std::promise的get_future函数，可以将该共享状态与std::future对象关联。调用之后，两个对象共享相同的共享状态：(1).std::promise对象是异步提供程序(asynchronous provider)，应 在某个时刻为共享状态设置一个值。(2).std::future对象是个异步返回对象，可以检索共享状态的值，并在必要时等待其准备就绪。
    // std::promise used to communicate objects between thread. The class template std::promise provides a facility to store a value or an exception that is later acquired asynchronously via a std::future object created by the std::promise object. Note that the std::promise object is meant to be used only once.
    // 共享状态的生存期至少要持续到与之关联的最后一个对象释放或销毁为止。
    // std::future介绍参考：https://blog.csdn.net/fengbingchun/article/details/104115489
    // 模板类std::promise成员函数包括：
    // 1. 构造函数：(1).默认构造函数：通过访问新的空共享状态来初始化对象(The object is initialized with access to a new empty shared state)。(2).带allocator的构造函数。(3).禁用拷贝构造。(4).支持移动构造。
    // 2. 析构函数：(1).放弃(abandon)共享状态并销毁promise对象。(2).如果有其它future对象关联到同一共享状态，则共享状态本身不会被销毁。(3).如果promise对象在共享状态准备就绪前被销毁，则共享状态自动准备就绪并包含一个std::future_error类型的异常。
    // 3. get_future函数：(1).返回一个与promise对象的共享状态关联的std::future对象。(2).一旦准备就绪，返回的std::future对象就可以访问promise对象在共享状态上设置的值或异常。(3).每个promise共享状态只能被一个std::future对象检索(Only one future object can be retrieved for each promise shared state)。(4).调用此函数后，promise应在某个时候使其共享状态准备就绪(通过设置值或异常)，否则将在销毁时自动准备就绪并包含一个std::future_error类型的异常。
    // 4. operator=：(1).禁用拷贝赋值。(2).支持移动赋值。
    // 5. set_exception：将异常指针存储进共享状态即设置共享状态的异常指针，准备就绪。
    // 6. set_exception_at_thread_exit：设置共享状态的异常指针，但并不将该共享状态的标志设置为ready，当线程退出时，该promise对象会自动设置为ready (Stores the exception pointer p in the shared state without making it ready immediately. Instead, it will be made ready automatically at thread exit, once all objects of thread storage duration have been destroyed)。
    // 7. set_value：(1).将值存储进共享状态即设置共享状态的值，准备就绪。(2).set_value(void)只是简单使共享状态就绪而无须设置任何值。
    // 8. set_value_at_thread_exit：设置共享状态的值，但并不将该共享状态的标志设置为ready，当线程退出时，该promise对象会自动设置为ready(Stores val as the value in the shared state without making it ready immediately. Instead, it will be made ready automatically at thread exit, once all objects of thread storage duration have been destroyed)。
    // 9. swap/非成员模板函数swap：交换共享状态。

    { // constructor/get_future/set_value
        std::cout << "test promise -- 1 -- constructor/get_future/set_value\n";
        std::promise<int> foo; // create promise
        std::promise<int> bar = std::promise<int>(std::allocator_arg, std::allocator<int>());
        std::future<int> fut = bar.get_future(); // engagement with future
        //std::future<int> fut2 = bar.get_future(); // crash, 每个promise共享状态只能被一个std::future对象检索或关联
        std::future<int> fut3 = foo.get_future();
        auto print_int = [&fut]() { int x = fut.get(); fprintf(stdout, "value: %d\n", x); };
        std::thread th1(print_int); // send future to new thread
        bar.set_value(10); // fulfill promise(synchronizes with getting the future)
        //bar.set_value(10); // crash, 每个promise的set_value仅能被调用一次
        foo.set_value(10);
        th1.join();
// test promise -- 1 -- constructor/get_future/set_value
// value: 10
    }

    { // operator =
        std::cout << "test promise -- 1 -- operator =\n";
        std::promise<int> prom;
        auto print_promise = [&prom]() {
            std::future<int> fut = prom.get_future();
            int x = fut.get();
            std::cout << "value: " << x << '\n';
        };

        std::thread th1(print_promise);
        prom.set_value(10);
        th1.join();

        prom = std::promise<int>(); // reset, by move-assigning a new promise
        std::thread th2(print_promise);
        prom.set_value(20);
        th2.join();
// test promise -- 1 -- operator =
// value: 10
// value: 20
    }

    { // set_exception
        std::cout << "test promise -- 1 -- set_exception\n";
        std::promise<int> prom;
        std::future<int> fut = prom.get_future();

        auto get_int = [&prom]() {
            int x;
            std::cout << "Please, enter an integer value: ";
            std::cin.exceptions(std::ios::failbit); // throw on failbit
            try {
                std::cin >> x; // sets failbit if input is not int
                prom.set_value(x);
            } catch (std::exception&) {
                prom.set_exception(std::current_exception());
            }
        };

        auto print_int = [&fut]() {
            try {
                int x = fut.get();
                std::cout << "value: " << x << '\n';
            } catch (std::exception& e) {
                std::cout << "[exception caught: " << e.what() << "]\n";
            }
        };

        std::thread th1(print_int);
        std::thread th2(get_int);

        th1.join();
        th2.join();
// test promise -- 1 -- set_exception    输入1
// Please, enter an integer value: 1
// value: 1

// test promise -- 1 -- set_exception    输入x
// Please, enter an integer value: x
// [exception caught: basic_ios::clear: iostream error]
    }

    // reference: https://en.cppreference.com/w/cpp/thread/promise
    {
        auto accumulate = [](std::vector<int>::iterator first, std::vector<int>::iterator last, std::promise<int> accumulate_promise){
            std::cout << "start accumulate\n";
            int sum = std::accumulate(first, last, 0);
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            accumulate_promise.set_value(sum);  // Notify future
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            std::cout << "end accumulate\n";
        };
        auto do_work = [](std::promise<void> barrier){
            std::this_thread::sleep_for(std::chrono::seconds(1));
            barrier.set_value();
        };

        std::cout << "test promise -- 2 --\n";
        // Demonstrate using promise<int> to transmit a result between threads.
        std::vector<int> numbers = { 1, 2, 3, 4, 5, 6 };
        std::promise<int> accumulate_promise;
        std::future<int> accumulate_future = accumulate_promise.get_future();
        std::thread work_thread(accumulate, numbers.begin(), numbers.end(), std::move(accumulate_promise));

        // future::get() will wait until the future has a valid result and retrieves it.
        // Calling wait() before get() is not needed
        //accumulate_future.wait();  // wait for result
        std::cout << "result=" << accumulate_future.get() << '\n';
        std::cout << "after1" << '\n';
        work_thread.join();  // wait for thread completion
        std::cout << "after2" << '\n';

        // Demonstrate using promise<void> to signal state between threads.
        std::promise<void> barrier;
        std::future<void> barrier_future = barrier.get_future();
        std::thread new_work_thread(do_work, std::move(barrier));
        barrier_future.wait();
        new_work_thread.join();
        std::cout << "after3" << '\n';
// test promise -- 2 --
// result=start accumulate
// 21
// after1
// end accumulate
// after2
// after3
    }

    // https://en.cppreference.com/w/cpp/thread/promise/set_value_at_thread_exit
    {
        std::cout << "test promise -- 3 --\n";
    #ifdef _MSC_VER
        // set_value_at_thread_exit
        using namespace std::chrono_literals;
        std::promise<int> p;
        std::future<int> f = p.get_future();
        std::thread([&p] {
            std::this_thread::sleep_for(1s);
            p.set_value_at_thread_exit(9); // gcc 4.9 don't support this function
        }).detach();

        std::cout << "Waiting..." << std::flush;
        f.wait();
        std::cout << "Done!\nResult is: " << f.get() << '\n';
    #endif
    }
}
#include <cmath>
void test1_cpp11_2_packaged_task()
{
    // https://blog.csdn.net/fengbingchun/article/details/104127352
    // C++11中的std::packaged_task是个模板类。std::packaged_task包装任何可调用目标(函数、lambda表达式、bind表达式、函数对象)以便它可以被异步调用。它的返回值或抛出的异常被存储于能通过std::future对象访问的共享状态中。
    // std::packaged_task类似于std::function，但是会自动将其结果传递给std::future对象。
    // std::packaged_task对象内部包含两个元素：(1).存储的任务(stored task)是一些可调用的对象(例如函数指针、成员或函数对象的指针)( A stored task, which is some callable object (such as a function pointer, pointer to member or function object))。(2).共享状态，它可以存储调用存储的任务(stored task)的结果，并可以通过std::future进行异步访问(A shared state, which is able to store the results of calling the stored task and be accessed asynchronously through a future)。
    // 通过调用std::packaged_task的get_future成员将共享状态与std::future对象关联。调用之后，两个对象共享相同的共享状态：(1).std::packaged_task对象是异步提供程序(asynchronous provider)，应通过调用存储的任务(stored task)在某个时刻将共享状态设置为就绪。(2).std::future对象是一个异步返回对象，可以检索共享状态的值，并在必要时等待其准备就绪。
    // 共享状态的生存期至少要持续到与之关联的最后一个对象释放或销毁为止。
    // std::packaged_task不会自己启动，你必须调用它(A packaged_task won't start on it's own, you have to invoke it)。
    // std::future介绍参考：https://blog.csdn.net/fengbingchun/article/details/104115489
    // 模板类std::packaged_task成员函数包括：
    // 1. 构造函数：(1).默认构造函数：无共享状态无存储任务(no shared state and no stored task)情况下初始化对象。(2). initialization constructor：该对象具有共享状态，且其存储的任务由fn初始化。(3). initialization constructor with allocator。(4).禁用拷贝构造。(5).支持移动构造。
    // 2. 析构函数：(1).放弃(abandon)共享状态并销毁packaged_task对象。(2). 如果有其它future对象关联到同一共享状态，则共享状态本身不会被销毁。(3). 如果packaged_task对象在共享状态准备就绪前被销毁，则共享状态自动准备就绪并包含一个std::future_error类型的异常。
    // 3. get_future函数：(1).返回一个与packaged_task对象的共享状态关联的std::future对象。(2).一旦存储的任务被调用，返回的std::future对象就可以访问packaged_task对象在共享状态上设置的值或异常。(3).每个packaged_task共享状态只能被一个std::future对象检索(Only one future object can be retrieved for each packaged_task shared state)。(4).调用此函数后，packaged_task应在某个时候使其共享状态准备就绪(通过调用其存储的任务)，否则将在销毁后自动准备就绪并包含一个std::future_error类型的异常。
    // 4. make_ready_at_thread_exit函数：在线程退出时才使共享状态ready而不是在调用完成后就立即ready。
    // 5. operator=：(1).禁用拷贝赋值。(2).支持移动赋值。
    // 6. operator()：(1).call stored task。(2).如果对存储任务的调用成功完成或抛出异常，则返回的值或捕获的异常存储在共享状态，共享状态准备就绪(解除阻塞当前等待它的所有线程)。
    // 7. reset函数：(1).在保持相同存储的任务的同时，以新的共享状态重置对象。(2).允许再次调用存储的任务。(3).与对象关联的之前的共享状态被放弃(就像packaged_task被销毁了一样)。(4).在内部，该函数的行为就像是移动赋值了一个新构造的packaged_task一样(Internally, the function behaves as if move-assigned a newly constructed packaged_task (with its stored task as argument))。
    // 8. swap函数/非成员模板函数swap：交换共享状态和存储的任务(stored task)。
    // 9. valid函数：检查packaged_task对象是否具有共享状态。

    // reference: http://www.cplusplus.com/reference/future/packaged_task/
    { // constructor/get_future/operator=/valid
        std::cout << "test promise -- 1 -- constructor/get_future/operator=/valid\n";
        std::packaged_task<int(int)> foo; // default-constructed
        std::packaged_task<int(int)> bar([](int x) { return x * 2; }); // initialized

        foo = std::move(bar); // move-assignment
        std::cout << "valid: " << foo.valid() << "\n";
        std::future<int> ret = foo.get_future(); // get future
        std::thread(std::move(foo), 10).detach(); // spawn thread and call task

        int value = ret.get(); // wait for the task to finish and get result
        std::cout << "The double of 10 is " << value << ".\n";
// test promise -- 1 -- constructor/get_future/operator=/valid
// valid: 1
// The double of 10 is 20.
    }

    { // reset/operator()
        std::cout << "test promise -- 1 -- reset/operator()\n";
        std::packaged_task<int(int)> tsk([](int x) { return x * 3; }); // package task

        std::future<int> fut = tsk.get_future();
        tsk(33);
        std::cout << "The triple of 33 is " << fut.get() << ".\n";

        // re-use same task object:
        tsk.reset();
        fut = tsk.get_future();
        std::thread(std::move(tsk), 99).detach();
        std::cout << "Thre triple of 99 is " << fut.get() << ".\n";
// test promise -- 1 -- reset/operator()
// The triple of 33 is 99.
// Thre triple of 99 is 297.

    }

    { // constructor/get_future
        std::cout << "test promise -- 1 -- constructor/get_future\n";
        auto countdown = [](int from, int to) {
            for (int i = from; i != to; --i) {
                std::cout << i << '\n';
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
            std::cout << "Lift off!\n";
            return from - to;
        };

        std::packaged_task<int(int, int)> tsk(countdown); // set up packaged_task
        std::future<int> ret = tsk.get_future(); // get future

        std::thread th(std::move(tsk), 5, 0); // spawn thread to count down from 5 to 0

        int value = ret.get(); // wait for the task to finish and get result
        std::cout << "The countdown lasted for " << value << " seconds.\n";

        th.join();
// test promise -- 1 -- constructor/get_future
// 5
// 4
// 3
// 2
// 1
// Lift off!
// The countdown lasted for 5 seconds.
    }

    // reference: https://en.cppreference.com/w/cpp/thread/packaged_task
    { // lambda
        std::cout << "test promise -- 2 -- lambda\n";
        std::packaged_task<int(int, int)> task([](int a, int b) { return std::pow(a, b);});
        std::future<int> result = task.get_future();

        task(2, 9);
        std::cout << "task_lambda:\t" << result.get() << '\n';
// test promise -- 2 -- lambda
// task_lambda:    512
    }
    { // bind
        std::cout << "test promise -- 2 -- bind\n";
        std::packaged_task<int()> task(std::bind([](int x, int y) { return std::pow(x, y); }, 2, 11));
        std::future<int> result = task.get_future();

        task();
        std::cout << "task_bind:\t" << result.get() << '\n';
// test promise -- 2 -- bind
// task_bind:      2048
    }

    { // thread
        std::cout << "test promise -- 2 -- thread\n";
        std::packaged_task<int(int, int)> task([](int x, int y) { return std::pow(x, y); });
        std::future<int> result = task.get_future();

        std::thread task_td(std::move(task), 2, 10);
        task_td.join();
        std::cout << "task_thread:\t" << result.get() << '\n';
// test promise -- 2 -- thread
// task_thread:    1024
    }

    // reference: https://thispointer.com/c11-multithreading-part-10-packaged_task-example-and-tutorial/
    struct DBDataFetcher {
        std::string operator()(std::string token)
        {
            // Do some stuff to fetch the data
            std::string data = "Data From " + token;
            return data;
        }
    };
    {
        std::cout << "test promise -- 3 --\n";
        // Create a packaged_task<> that encapsulated a Function Object
        std::packaged_task<std::string(std::string)> task(std::move(DBDataFetcher()));

        // Fetch the associated future<> from packaged_task<>
        std::future<std::string> result = task.get_future();

        // Pass the packaged_task to thread to run asynchronously
        std::thread th(std::move(task), "Arg");

        // Join the thread. Its blocking and returns when thread is finished.
        th.join();

        // Fetch the result of packaged_task<> i.e. value returned by getDataFromDB()
        std::string data = result.get();
        std::cout << data << std::endl;
// test promise -- 3 --
// Data From Arg
    }

    // reference: https://stackoverflow.com/questions/18143661/what-is-the-difference-between-packaged-task-and-async
    // sleeps for one second and returns 1
    auto sleep = []() {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        return 1;
    };
    { // std::packaged_task
        std::cout << "test promise -- 4 -- packaged_task\n";
        // >>>>> A packaged_task won't start on it's own, you have to invoke it
        std::packaged_task<int()> task(sleep);

        auto f = task.get_future();
        task(); // invoke the function

        // You have to wait until task returns. Since task calls sleep
        // you will have to wait at least 1 second.
        std::cout << "You can see this after 1 second\n";

        // However, f.get() will be available, since task has already finished.
        std::cout << f.get() << std::endl;
// test promise -- 4 -- packaged_task
// You can see this after 1 second
// 1
    }

    { // std::async
        std::cout << "test promise -- 4 -- async\n";
        // >>>>> On the other hand, std::async with launch::async will try to run the task in a different thread :
        auto f = std::async(std::launch::async, sleep);
        std::cout << "You can see this immediately!\n";

        // However, the value of the future will be available after sleep has finished
        // so f.get() can block up to 1 second.
        std::cout << f.get() << "This will be shown after a second!\n";
// test promise -- 4 -- async
// You can see this immediately!
// 1This will be shown after a second!
    }
}


void test1_cpp11_2_memory()
{
    std::shared_ptr<int> sp1,sp2;
    std::weak_ptr<int> wp;
    sp1 = std::make_shared<int> (20);    // sp1
    wp = sp1;                            // sp1, wp
    std::cout << "num: " << wp.use_count() << '\n';    // 1
    sp2 = sp1;
    std::cout << "num: " << wp.use_count() << '\n';    // 2
    sp1.reset();
    //sp2 = wp.lock();                     // sp1, wp, sp2
    std::cout << "num: " << wp.use_count() << '\n';    // 1
    sp1 = wp.lock();                     // sp1, wp, sp2
    std::cout << "num: " << wp.use_count() << '\n';    // 2
}

std::unique_ptr<int> get_unique_ptr(){return std::unique_ptr<int>(new int(520));}
void delete_unique_ptr(int*p){delete p;}
void test1_cpp11_2_unique_ptr()
{
    using namespace std;
    {
        // 创建
        // 有两种版本：一普通版本，管理一个动态分配的资源对象；二数组版本，是一个偏特化版本，用于管理一个动态分配的数组。
        unique_ptr<int> ptra1(new int(10));         // 通过构造函数初始化
        unique_ptr<int> ptra2 = move(ptra1);        // 通过转移所有权的方式初始化
        // unique_ptr<int> ptra3 = ptr1;            // 编译报错 是 move-only 的
        unique_ptr<int> ptra4 = get_unique_ptr();   // 通过函数返回初始化
        unique_ptr<int> ptra5;                      // 使用缺省构造函数创建的是不拥有任何资源的空对象
        unique_ptr<int[]> ptra6;
        // std::unique_ptr<int> ptra7 = new int(4); // error 不能直接把裸指针赋值给unique_ptr对象，没有提供这样的隐式转换
        std::unique_ptr<int> ptra8(nullptr);        // 可以使用nullptr直接构造
        std::unique_ptr<int> ptra9 = nullptr;       // 可以使用nullptr直接赋值
        ptra9.reset(nullptr);
        int *pi = new int(1);
        unique_ptr<int> ptra10(pi);                 // 可以 但是不建议这样做

        // std::make_shared是c++11的一部分，但std::make_unique不是。它是在c++14里加入标准库的。
        // 使用new的版本重复了被创建对象的键入，但是make_unique函数则没有。
        unique_ptr<int> ptrb1(std::make_unique<int>()); // with make func 需要设置c++14
        unique_ptr<int> ptrb2(new int); // without make func

        unique_ptr<int[]> ptrc1 = std::make_unique<int[]>(10);  // 指向一个数组
        for (int i = 0; i < 10; i++)  ptrc1[i] = i * i;
        unique_ptr<int[]> ptrc2(new int[10]);                   //
        ptrc2[9] = 9;
        // unique_ptr<int[10]> ptrc3(new int[10]); // 无法编译
        // unique_ptr<int> ptrc4(new int[10]);     // 可以编译，运行会出错  因为销毁时，使用delete，不是delete[]。
    }
    {
        // 指定删除器 是可调用对象，类型可以是函数指针、函数对象、lambda表达式、function对象等。
        // 如果没有指定删除器，会使用缺省删除器，缺省使用delete和delete[]来销毁对象，分别用于普通版本和数组版本。
        struct FileCloser {void operator()(FILE* fp) const {if (fp != nullptr)  fclose(fp);}};
        unique_ptr<FILE, FileCloser> ptra1(fopen("1.txt", "w"));  // 使用 函数对象
        unique_ptr<FILE, function<void(FILE*)>> ptra2(fopen("1.txt", "w"), [](FILE* fp) {fclose(fp);}); // 使用 function
        unique_ptr<FILE, void(*)(FILE*)> ptra3(fopen("1.txt", "w"), [](FILE* fp) {fclose(fp);}); // 使用 函数指针
        struct MyDelete{void operator()(int *p){cout << "delete" << endl;delete p;}};
        unique_ptr<int,MyDelete> ptra4(new int(1));

        // 删除器是模板类型的一部分，必须先声明，不能像 shared_ptr 那样直接指定删除器。
        shared_ptr<int> ptrb1(new int(10), [](int* p) {delete p; });           // ok
        // unique_ptr<int> ptrb2(new int(10), [](int* p) {delete p; });        // error
        using func_ptr = void(*)(int*); // func_ptr 的类型和 lambda表达式的类型是一致的
        unique_ptr<int, func_ptr> ptrb3(new int(10), [](int* p) {delete p; }); // ok
        unique_ptr<int, func_ptr> ptrb4(new int(10), delete_unique_ptr);       // ok

        // lambda 不捕获变量时是正确的；捕获了变量，则编译报错。
        // lambda 不捕获变量时，可直接转换为函数指针，一旦捕获了就无法转换了，
        // 如果想要让编译器成功通过编译，那么需要使用可调用对象包装器来处理声明的函数指针：
        unique_ptr<int, void(*)(int*)> ptrc1(new int(10), [](int* p) {delete p; }); // ok
        // unique_ptr<int, func_ptr> ptrc2(new int(10), [&](int* p) {delete p; }); // 编译报错
        unique_ptr<int, function<void(int*)>> ptrc3(new int(10), [&](int* p) {delete p; }); // ok

        // 移动操作要求两个对象的类型必须完全一样，即删除器的类型也必须一样。
        unique_ptr<int, function<void(int*)>> ptrd1(new int(4), [](int *ptr){delete ptr;});
        // unique_ptr<int> ptrd2(move(ptrd1));  // 无法编译
    }
    {
        // 使用
        // std::shared_ptr 和 std::unique_ptr共有操作
        // p.get()              返回p中保存的指针，不会影响p的引用计数。
        // p.reset()            释放p指向的对象，将p置为空。
        // p.reset(q)           释放p指向的对象，令p指向q。
        // p.reset(new T)       释放p指向的对象，令p指向一个新的对象。
        // p.swap(q)            交换p和q中的指针。
        // swap(p, q)           交换p和q中的指针。
        // p.operator*()        解引用p。
        // p.operator->()       成员访问运算符，等价于(*p).member。
        // p.operator bool()    检查p是否为空指针。

        unique_ptr<int> ptra1(new int(1));
        unique_ptr<int> ptra2(new int(1));
        unique_ptr<int[]> ptrb1(new int[10]);
        int i = 0;

        int *p1 = ptra1.get();     // 返回裸指针，如果unique_ptr对象是个空对象，则返回nullptr。
        int *p2 = ptra2.release(); // ! 返回裸指针，放弃控制权，并将ptra1置空  注意这个p2 必须手动释放 否则内存泄露

        i = *ptra1;    // 重载了操作符*，->可以象使用指针那样使用它们
        *ptra1 = 2;
        i = ptrb1[0];  // 对于数组版本，还重载了数组操作符[]，可以通过它访问指定位置的数组元素
        // i = ptrb1[10];  // ! 同裸指针访问数组一样，不进行越界检查
        ptrb1[0] = 1;  // 操作符[]返回的是引用，可以作为左值使用
        unique_ptr<int> ptrb2(new int[10]);   // 不是一个指向数组的智能指针，而是普通版本的智能指针，没有提供[]操作符重载
        // ptrb2[0] = 1;  // 编译失败
        *ptrb2 = 1;            //  ok 访问的是位置0处的元素

        // 没有重载+，-，++，–，+=，-=等算术运算操作符，如果访问其它位置的元素，只能通过裸指针
        std::cout << *(ptra1.get()+0) << std::endl; // 2
        std::cout << (ptra1.get)()[0] << std::endl; // 2

        // 可以直接判断是否为nullptr，有两种方式，和使用裸指针的形式完全一样。
        assert(ptra1 != nullptr);
        if(!ptra1)          std::cout<<"up is nullptr"<<std::endl;
        if(ptra1== nullptr) std::cout<<"up is nullptr"<<std::endl;

        // 也可象普通指针那样，当指向一个类继承体系的基类对象时，也具有多态性质，如同使用裸指针管理基类对象和派生类对象那样。
        // unique_ptr<base> up_base(new base); // up_base指向基类
        // up_base->foo(); // 调用基类的成员函数
        // up_base->bar(); // 调用基类的成员函数
        // unique_ptr<derive> up_derive(new derive);
        // up_base = move(up_derive); // unique_ptr可以进行隐式转换，基类指针指向派生类对象
        // up_base->foo(); // 不是多态，调用基类对象的成员函数
        // up_base->bar(); // 由多态机制调用派生类对象的成员函数
        // up_base.reset(); // 调用派生类的析构函数

        ptra1.reset();                       // 释放ptra1对象指向的资源对象，显式释放 解除对原始内存的管理
        ptra1.reset(new int(222));           // 释放ptra1指向的资源对象，同时指向新的对象，隐式释放
        ptra1.reset(nullptr);                // 释放ptra1对象指向的资源对象，显式释放
    }
    {
        // 注意
    }
}

void delete_shared_ptr(int *p) {delete p;}
void delete_shared_ptr2(int *p) {delete []p;}
void test1_cpp11_2_shared_ptr()
{
    using namespace std;
    {
// operator=()       重载赋值号，使得同一类型的 shared_ptr 智能指针可以相互赋值。
// operator*()       重载 * 号，获取当前 shared_ptr 智能指针对象指向的数据。
// operator->()      重载 -> 号，当智能指针指向的数据类型为自定义的结构体时，通过 -> 运算符可以获取其内部的指定成员。
// swap()            交换 2 个相同类型 shared_ptr 智能指针的内容。
// reset()           当函数没有实参时，该函数会使当前 shared_ptr 所指堆内存的引用计数减 1，同时将当前对象重置为一个空指针；当为函数传递一个新申请的堆内存时，则调用该函数的 shared_ptr 对象会获得该存储空间的所有权，并且引用计数的初始值为 1。
// get()             获得 shared_ptr 对象内部包含的普通指针。
// use_count()       返回同当前 shared_ptr 对象（包括它）指向相同的所有 shared_ptr 对象的数量。
// unique()          判断当前 shared_ptr 对象指向的堆内存，是否不再有其它 shared_ptr 对象再指向它。
// operator bool()   判断当前 shared_ptr 对象是否为空智能指针，如果是空指针，返回 false；反之，返回 true。

    // 创建
    // 对资源做引用计数——当引用计数为 0 的时候，自动释放资源。
    // 实现包含了两部分，指向堆上创建的对象的裸指针:raw_ptr，指向内部隐藏的、共享的管理对象:share_count_object

    // 通过构造函数、std::shared_ptr辅助函数和reset方法来初始化
    shared_ptr<int> ptra1(new int(1));
    shared_ptr<int> ptra2 = make_shared<int>(1);  // 优先这种，更高效。相当于shared_ptr<int> ptra4(new int(1));
    // shared_ptr<int> ptra3 = new int(1);        // ! 错误  不能将一个原始指针直接赋值给一个智能指针
    shared_ptr<int> ptra4(ptra1);                 // 拷贝构造 引用计数+1
    shared_ptr<int> ptra41 = ptra1;               // 同上
    shared_ptr<int> ptr42(move(ptra1));           // 移动构造 ptr42替代ptr1  ptr1转让了所有权 变为空
    int* pi1 = new int(2);
    shared_ptr<int> ptra5(pi1);                   // 可以 不建议这样
    // shared_ptr<int> ptra51(pi1);               // 不可以 运行会出错
    shared_ptr<int> ptra6;                        // 不管理任何内存 空 引用计数为 0
    shared_ptr<int> ptra7(nullptr);               // 同上

    shared_ptr<int[]> ptrb1(new int[10]);    // 指向数组
    shared_ptr<int[]> ptrb2 = make_shared<int[]>(10);  // C++20 才支持 std::make_shared<int[]>
    ptrb2[1] = 1;
    shared_ptr<int[]> ptrb3 = ptrb2;
    cout << "ptrb3[1]:" << ptrb3[1]  << " ptrb3.use_count():" << ptrb3.use_count() << endl; // 1 2

    shared_ptr<int[]> ptrc1(new int(0), [](int* p){delete p;}); // 指定删除器
    shared_ptr<int[]> ptrc2(new int(0), delete_shared_ptr);     // 引用计数为0时，自动调用删除器来释放对象的内存。
    shared_ptr<int[]> ptrc3(new int[10], delete_shared_ptr2);   // 默认的释放规则是不支持释放数组，要自定义对应的释放规则
    shared_ptr<int[]> ptrc4(new int[10], std::default_delete<int[]>()); // C++11提供 default_delete 模板类释放数组

    shared_ptr<int> ptrd1;
    ptrd1.reset();           // 没有参数就是释放资源
    ptrd1.reset(new int(1)); // 有参数就是重新分配资源   原引用计数减1
    if(ptrd1) cout << "ptrd1 is not null";              // 判断是否空指针
    if(ptrd1 != nullptr) cout << "ptrd1 is not null";   // 判断是否空指针
    int* pi = ptrd1.get();   // 返回裸指针  和使用普通指针一样
    shared_ptr<char> ptrd2(new char[32]);
    char* add = ptrd2.get();memset(add, 0, 32);strcpy(add, "sss");cout << "string: " << add << endl; // sss

    shared_ptr<int> ptre1; cout << "ptre1:" << ptre1.use_count() << endl;             // 0   引用计数
    shared_ptr<int> ptre2(new int(1)); cout << "ptre2:" << ptre2.use_count() << endl; // 1
    shared_ptr<int> ptre3 = ptre2; cout << "ptre2:" << ptre2.use_count() << endl;     // 2
    ptre3.reset();cout << "ptre2:" << ptre2.use_count() << endl;                      // 1
    }
    {
        // 使用
        //std::make_shared() 是模板函数。
        //template< class T, class... Args >
        //shared_ptr<T> make_shared(Args&&... args);
        //T：模板参数的数据类型
        //Args&&... args ：要初始化的数据，如果是通过 make_shared 创建对象，需按照构造函数的参数列表指定
        class Test{
        public:
            Test(){cout << "construct Test..." << endl;}
            Test(int x){cout << "construct Test, x = " << x << endl;}
            Test(string str){cout << "construct Test, str = " << str << endl;}
            ~Test(){cout << "destruct Test ..." << endl;}
        };

        shared_ptr<int>  ptr1 = make_shared<int>(520);   cout << "ptr1:"<< ptr1.use_count() << endl; // 1
        shared_ptr<Test> ptr2 = make_shared<Test>();     cout << "ptr2:"<< ptr2.use_count() << endl; // 1
        shared_ptr<Test> ptr3 = make_shared<Test>(520);  cout << "ptr3:"<< ptr3.use_count() << endl; // 1
        shared_ptr<Test> ptr4 = make_shared<Test>("xxx");cout << "ptr4:"<< ptr4.use_count() << endl; // 1
    }
    {
        // 注意
        // 1 不要用一个原始指针初始化多个shared_ptr
        int *ptr = new int;
        shared_ptr<int> ptr1(ptr);
        // shared_ptr<int> ptr2(ptr); // ! 逻辑错误

        // 2 不要在函数实参中创建shared_ptr
        // myfunc(shared_ptr<int>(new int), myfunc2()); //有缺陷  函数参数顺序不同编译器可能是不一样的
        // 可能的过程是先new int，然后调用g()，如果恰好g()发生异常，而shared_ptr还 没有创建， 则int内存泄漏了
        // shared_ptr<int> p(new int); myfunc(p, g());  // 正确的写法


        // 3 通过shared_from_this()返回this指针。
        // 不要将this指针作为shared_ptr返回，因为this指针本质上是一个裸指针，会导致重复析构。
        class A {
        public:
            shared_ptr<A>GetSelf(){return shared_ptr<A>(this);} // ! 不要这么做
            ~A(){cout << "Deconstruction A" << endl;}
        };
        shared_ptr<A> ptra1(new A);
        cout << "ptra1~~~:" << ptra1.use_count() << endl;  // 1
        // shared_ptr<A> ptra2 = ptra1->GetSelf();   // 导致析构2次  this构造了两个智能指针，这二者之间是没有任何关系的
        // cout << "ptra2:" << ptra2.use_count() << endl; // 1

        // 这个问题可以通过 weak_ptr 来解决，通过 wek_ptr 返回管理 this 资源的共享智能指针对象 shared_ptr。
        // C++11 模板类 std::enable_shared_from_this<T>，这个类中有一个方法叫做 shared_from_this()，
        // 这个方法返回shared_ptr，内部使用 weak_ptr 来监测 this 对象，调用 weak_ptr 的 lock() 返回 shared_ptr 对象。
        // 强调一个细节：调用 enable_shared_from_this 类的 shared_from_this() 方法前，必须先初始化函数内部 weak_ptr 对象，
        // 否则该函数无法返回一个有效的 shared_ptr 对象。
        // shared_ptr构造时(因为是友元)，其底层调用enable_shared_from_this的_M_weak_assign给其初始化
        class B:public std::enable_shared_from_this<B>{
        public:
            shared_ptr<B>GetSelf(){return shared_from_this();} // ! 这么做
            ~B(){cout << "Deconstruction B" << endl;}
        };
        shared_ptr<B> ptrb1(new B);
        cout << "ptrb1:" << ptrb1.use_count() << endl;  // 1
        shared_ptr<B> ptrb2 = ptrb1->GetSelf();
        cout << "ptrb2:" << ptrb2.use_count() << endl;  // 2   析构一次


        // 避免循环引用。循环引用会导致内存泄漏
        class D;
        class C {
        public:
            std::shared_ptr<D> m_ptr;
            ~C(){cout << "Deconstruction C" << endl;}
        };
        class D {
        public:
            std::shared_ptr<C> m_ptr;
            ~D(){cout << "Deconstruction D" << endl;}
        };
        std::shared_ptr<C> ptrc1(new C);
        std::shared_ptr<D> ptrd1(new D);
        cout << "ptrc1:" << ptrc1.use_count() << endl;  // 1
        cout << "ptrd1:" << ptrd1.use_count() << endl;  // 1
        ptrc1->m_ptr = ptrd1;
        ptrd1->m_ptr = ptrc1;
        cout << "ptrc1:" << ptrc1.use_count() << endl;  // 2  离开作用域 引用计数变为1 不能释放
        cout << "ptrd1:" << ptrd1.use_count() << endl;  // 2
        ptrc1->m_ptr.reset();                           // 手动释放成员变量才行
        ptrd1->m_ptr.reset();
        ptrc1.reset();      // 只这样写不起作用 因为离开作用域ptrc1会自动释放 但ptrc1->m_ptr不会
        // ptrc1,ptrd1 对 C,D 实例对象的引用计数为 2，离开作用域之后引用计数-1，不会去删除智能指针管理的内存，
        // 导致 C,D 的实例对象不能被析构，最终造成内存泄露。
        // 使用 weak_ptr 可以解决这个问题，只要将类 C 或 D 的任意一个成员改为 weak_ptr：

        {
        class D;
        class C {
        public:
            std::weak_ptr<D> m_ptr; // ! 修改为weak_ptr
            ~C(){cout << "Deconstruction C x" << endl;}
        };
        class D {
        public:
            std::shared_ptr<C> m_ptr;
            ~D(){cout << "Deconstruction D x" << endl;}
        };
        std::shared_ptr<C> ptrc1(new C);
        std::shared_ptr<D> ptrd1(new D);
        cout << "ptrc1 x:" << ptrc1.use_count() << endl;  // 1
        cout << "ptrd1 x:" << ptrd1.use_count() << endl;  // 1
        ptrc1->m_ptr = ptrd1; // 由于 m_ptr 是 weak_ptr，这个赋值操作并不会增加引用计数，ptrd1 的引用计数仍然为 1
        ptrd1->m_ptr = ptrc1;
        cout << "ptrc1 x:" << ptrc1.use_count() << endl;  // 2
        cout << "ptrd1 x:" << ptrd1.use_count() << endl;  // 1  离开作用域后 ptrd1 的引用计数为 0，类 D 实例对象被析构
        // 在类 D 的实例对象被析构时，内部的 m_ptr 也被析构，其对 C 对象的管理解除，内存的引用计数减为 1，
        // 当 ptrc1 离开作用域之后，对 C 对象的管理也解除了，内存的引用计数减为 0，类 C 的实例对象被析构。
        }
    }
    {
        // 实现细节
        // https://zhuanlan.zhihu.com/p/150555165
        std::cout << sizeof(int*) << std::endl;  // 8
        std::cout << sizeof(std::unique_ptr<int>) << std::endl;  // 8
        std::cout << sizeof(std::unique_ptr<FILE, std::function<void(FILE*)>>) << std::endl;  // 40
        std::cout << sizeof(std::shared_ptr<int>) << std::endl;  // 16
        std::shared_ptr<FILE> ptra1(fopen("test_file.txt", "w"), [](FILE* fp) {
            std::cout << "close " << fp << std::endl;
            fclose(fp);
        });
        std::cout << sizeof(ptra1) << std::endl;  // 16

        // 内部有2个指针实现，分别指向共享资源和控制信息
        // (std::shared_ptr<T> sptr1(new T))栈内存                          堆内存
        //          ptr to T       ------------------------------------------------------> T-共享资源
        //          ptr to control ------------------------------>|ref count(1)       |-------^
        //                                                        |weak ref count(1)  |
        //                                                        |deleter            |
        //                                                        |ptr   --------------
        // std::shared_ptr<T> sptr2 = sptr1;
        //          栈内存                                                   堆内存
        //          ptr to T       ------------------------------------------------------> T-共享资源
        //          ptr to control ------------------------------>|ref count(1)       |-------^   ^
        //                                                        |weak ref count(1)  |           |
        //      --- ptr to T                                      |deleter            |           |
        //      |   ptr to control ------------------------------>|ptr   --------------           |
        //      |----------------------------------------------------------------------------------

        // 控制信息和每个 shared_ptr 对象都需要保存指向共享资源的指针
        // 因为 shared_ptr 对象中的指针指向的对象不一定和控制块中的指针指向的对象一样。
        struct Fruit {int juice;};
        struct Vegetable {int fiber;};
        struct Tomato : public Fruit, Vegetable {int sauce;};
        // 由于继承的存在，shared_ptr 可能指向基类对象
        std::shared_ptr<Tomato> tomato = std::make_shared<Tomato>();
        std::shared_ptr<Fruit> fruit = tomato;
        std::shared_ptr<Vegetable> vegetable = tomato;
        std::cout << tomato << " " << fruit << " " << vegetable << std::endl;  // 0x55fc0a4dcf60 0x55fc0a4dcf60 0x55fc0a4dcf64

        // template< class Y > shared_ptr( const shared_ptr<Y>& r, element_type* ptr ) noexcept; // aliasing constructor
        // shared_ptr 对象和参数 r 指向同一个控制块（会影响 r 指向的资源的生命周期），但是指向共享资源的指针是参数 ptr。
        auto elts = {0, 1, 2, 3, 4}; // initializer_list类型 一块内存+size
        std::shared_ptr<vector<int>> pvec = std::make_shared<vector<int>>(elts);
        std::shared_ptr<int>ptrb1(pvec, &(*pvec)[2]);
        for (int i = -2; i < 3; ++i)  printf("%d\n", ptrb1.get()[i]); // 0 1 2 3 4 5
        //          栈内存                                         堆内存
        //          int*       ------------------------------------------------------> 0 1 2 3 4
        //          ptr to control ------------------------------>|ref count(1)             ^
        //                                                        |weak ref count(1)        |
        //                                                        |deleter                  |
        //                                                        |ptr   -->vector<int> (内部数据)
        // 看上面的例子，使用 std::shared_ptr 时，会涉及两次内存分配：一次分配共享资源对象；一次分配控制块。
        // C++ 标准库提供了 std::make_shared 函数来创建一个 shared_ptr 对象，只需要一次内存分配。
    }
}
#include <array>
void test1_cpp11_2_weak_ptr()
{
    using namespace std;
    // 是弱引用智能指针 可以看做是 shared_ptr 的助手，它不管理 shared_ptr 内部的指针。
    // 没有重载操作符* 和->，因为它不共享指针，不能操作资源，所以它的构造/析构不会增加/减少引用计数，
    // 主要作用就是作为一个旁观者监视 shared_ptr 中管理的资源是否存在。还可以返回this指针和解决循环引用的问题。
    {
        // 创建
        // constexpr weak_ptr() noexcept;         // 默认构造函数
        // weak_ptr(const weak_ptr & x) noexcept; // 拷贝构造
        // template <class U> weak_ptr(const weak_ptr<U>&x) noexcept;
        // template <class U> weak_ptr(const shared_ptr<U>&x) noexcept; // 通过shared_ptr对象构造

        shared_ptr<int> sp(new int);
        weak_ptr<int> wp1;         // 空 weak_ptr 对象
        // shared_ptr<int> sp2(wp1);  // ! throw std::bad_weak_ptr  用空weak_ptr构造shared_ptr
        weak_ptr<int> wp2(wp1);    // 空 weak_ptr 对象构造了另一个空 weak_ptr 对象
        weak_ptr<int> wp3(sp);     // shared_ptr 对象构造了一个可用的 weak_ptr 实例对象
        weak_ptr<int> wp4;
        wp4 = sp;                  // shared_ptr 对象构造了一个可用的 weak_ptr 实例对象（这是一个隐式类型转换）
        weak_ptr<int> wp5;
        wp5 = wp3;                 // weak_ptr 对象构造了一个可用的 weak_ptr 实例对象
    }

    {
        // 使用
        // std::weak_ptr 一些内置方法
        // use_count()       返回与之共享对象的shared_ptr的数量
        // expired()         检查所指对象是否已经被释放
        // lock()            返回一个指向共享对象的shared_ptr，若对象不存在则返回空shared_ptr
        // owner_before()    提供所有者基于的弱指针的排序
        // reset()           释放所指对象
        // swap()            交换两个weak_ptr对象

        shared_ptr<int> sp1, sp2,sp3;
        weak_ptr<int> wp,wp2,wp3;
        sp1 = std::make_shared<int>(520);
        wp = sp1;

        cout << "use_count: " << wp.use_count() << endl; // 1 获得当前所观测资源的引用计数
        cout << "expired: " << wp.expired() << endl;     // 0 判断观测的资源是否已经被释放  true/false资源已/没释放
        sp2 = wp.lock();                                 // 获取所监测资源的 shared_ptr 对象
        cout << "use_count: " << wp.use_count() << endl; // 2
        cout << "*sp1: " << *sp1 << endl;                // 520   sp1 和 sp2 管理的是同一块内存
        cout << "*sp2: " << *sp2 << endl;                // 520
        sp1.reset();                                     // sp1重置 引用计数减 1
        cout << "use_count: " << wp.use_count() << endl; // 1
        wp.reset();                                      // 释放所指对象
        cout << "use_count: " << wp.use_count() << endl; // 0
        sp1.reset(new int(2));
        wp2=sp2;
        wp.swap(wp2);                                    // 交换两个weak_ptr对象
        cout << "wp2: " << *(wp.lock()) << endl;         // 520
        wp2=sp1;
        cout << wp.lock() << " " << wp2.lock() << endl;  // 0x563ad73f9f00 0x563ad73fa4f0
        cout << "owner_before: " << wp.owner_before(wp2) << endl;  // 1  提供所有者基于的弱指针的排序
        // C++中的弱序：ptr和ptr1是不是同类型指针；ptr指针指向的地址小于ptr1指针指向的地址；满足这两条，就可以称“ptr<ptr1”。
        // https://blog.csdn.net/weixin_45590473/article/details/113040456
    }
    {
        // 注意
        // weak_ptr在使用前需要检查合法性 expired()
        weak_ptr<int> wp;
        {
            shared_ptr<int> sp(new int(1)); //sp.use_count()==1
            wp = sp; //wp不会改变引用计数，所以sp.use_count()==1
            shared_ptr<int> sp_ok = wp.lock(); //wp没有重载->操作符。只能这样取所指向的对象
        }
        shared_ptr<int> sp_null = wp.lock(); //sp_null .use_count()==0;
    }
}



void test1_cpp11_2_chrono()
{
    std::chrono::time_point<std::chrono::steady_clock> start = std::chrono::steady_clock::now();
    std::chrono::time_point<std::chrono::steady_clock> end = std::chrono::steady_clock::now();
    std::vector<std::string> vctstr;
    {
        for(int i = 0; i < 1; ++i)
        {
            for (int j = 0; j < 10000; j++)
            {
                vctstr.push_back("aaa");
            }

            end = std::chrono::steady_clock::now();
            printf("push_back time:%ld\n", std::chrono::duration_cast<std::chrono::microseconds>(end-start).count());
            vctstr.clear();

            start = std::chrono::steady_clock::now();
            for (int j = 0; j < 10000; j++)
            {
                vctstr.emplace_back("aaa");
            }
            end = std::chrono::steady_clock::now();
            printf("emplace_back time:%ld\n", std::chrono::duration_cast<std::chrono::microseconds>(end-start).count());
            vctstr.clear();
        }
    }

// push_back time:1217
// emplace_back time:623

// push_back time:2995
// emplace_back time:824
}



// Durations
// #include <ratio>
// #include <chrono>
void test1_cpp11_2_chrono_duration()
{
    // chrono 是一个time library, 源于boost，现在已经是C++标准。
    // 要使用chrono库，需要#include<chrono>，其所有实现均在std::chrono namespace下。
    // 注意标准库里面的每个命名空间代表了一个独立的概念。所以下文中的概念均以命名空间的名字表示！
    // chrono是一个模版库，使用简单，功能强大，只需要理解三个概念：duration、time_point、clock
    //
    //    1.Durations
    //    std::chrono::duration 表示一段时间，比如两个小时，12.88秒，半个时辰，一炷香的时间等等，只要能换算成秒即可。
    //    template <class Rep, class Period = ratio<1> > class duration;
    // 其中
    //    Rep表示一种数值类型，用来表示Period的数量，比如int float double
    //    Period是ratio类型，用来表示【用秒表示的时间单位】比如second milisecond
    //    常用的duration<Rep, Period>已经定义好了，在std::chrono::duration下：
    //    ratio<3600, 1>                  hours
    //    ratio<60, 1>                    minutes
    //    ratio<1, 1>                     seconds
    //    ratio<1, 1000>                  milisecond
    //    ratio<1, 1000000>               microsecond
    //    ratio<1, 1000000000>            nanosecon
    //
    //    这里需要说明一下ratio这个类模版的原型：
    //    template <intmax_t N, intmax_t D = 1> class ratio;
    //    N代表分子，D代表分母，所以ratio表示一个分数值。
    //    注意，我们自己可以定义Period，比如ratio<1, -2>表示单位时间是 - 0.5秒。
    //
    //    由于各种duration表示不同，chrono库提供了duration_cast类型转换函数。
    //    template < class ToDuration, class Rep, class Period>
    //    constexpr ToDuration duration_cast(const duration<Rep, Period>&dtn);
    //
    // 典型的用法是表示一段时间：
    typedef std::chrono::duration<int> seconds_type;
    typedef std::chrono::duration<int, std::milli> milliseconds_type;
    typedef std::chrono::duration<int, std::ratio<60 * 60>> hours_type;

    {
        hours_type h_oneday(24);                      // 24h
        seconds_type s_oneday(60 * 60 * 24);          // 86400s
        milliseconds_type ms_oneday(s_oneday);        // 86400000ms
        std::cout << h_oneday.count() << " h_oneday " << std::endl;
        std::cout << s_oneday.count() << " s_oneday " << std::endl;
        std::cout << ms_oneday.count() << " ms_oneday " << std::endl;
    }

    {
        seconds_type s_onehour(60 * 60);              // 3600s
        //hours_type h_onehour(s_onehour);             // NOT VALID (type truncates)   格式错误 应用下面方式
        hours_type h_onehour(std::chrono::duration_cast<hours_type>(s_onehour));
        milliseconds_type ms_onehour(s_onehour);      // 3600000ms (ok, no type truncation)
        std::cout << s_onehour.count() << " s_onehour" << std::endl;
        std::cout << h_onehour.count() << " h_onehour" << std::endl;
        std::cout << ms_onehour.count() << " ms_onehour" << std::endl;
    }

    // duration还有一个成员函数count()返回Rep类型的Period数量
    {
        using namespace std::chrono;
        // std::chrono::milliseconds is an instatiation of std::chrono::duration:
        milliseconds foo(1000); // 1 second
        foo *= 60;
        std::cout << "duration (in periods): " << foo.count() << " milliseconds" << std::endl;
        std::cout << "duration (in seconds): " << foo.count() * milliseconds::period::num / milliseconds::period::den << " seconds"
            << "[milliseconds::period::num]" << milliseconds::period::num << "[milliseconds::period::den]" << milliseconds::period::den << std::endl;

        // 自定义时间
        using myratio = std::ratio<3,7>;
        using mysec = duration<long long, myratio>;
        mysec ms(100);
        std::cout << "[mysec]" << ms.count() << std::endl;
        std::cout << "[seconds]" << ms.count() * mysec::period::num / mysec::period::den
            <<"[mysec::period::num]" << mysec::period::num << "[mysec::period::den]" << mysec::period::den << std::endl;
    }
}

// Time points
// #include <chrono>
// #include <ctime>
void test1_cpp11_2_chrono_timepoint()
{
    // Time points
    // std::chrono::time_point 表示一个具体时间，如上个世纪80年代、你的生日、今天下午、火车出发时间等，只要它能用计算机时钟表示。
    // 鉴于我们使用时间的情景不同，这个time point 具体到什么程度，由选用的单位决定。
    // 一个time point 必须有一个clock计时。参见clock的说明。
    //
    //  template <class Clock, class Duration = typename Clock::duration>  class time_point;
    using namespace std::chrono;
    system_clock::time_point tp_epoch;    // epoch value
    std::cout << "1 second since tp_epoch = " << tp_epoch.time_since_epoch().count() << " system_clock periods" << std::endl;

    time_point <system_clock, duration<int>> tp_seconds(duration<int>(1));
    system_clock::time_point tp(tp_seconds);
    std::cout << "1 second since system_clock epoch = " << tp.time_since_epoch().count() << " system_clock periods" << std::endl;

    // display time_point:
    time_t tt = system_clock::to_time_t(tp);
    std::cout << "time_point tp is: " << ctime(&tt);


    // time_point有一个函数time_from_eproch()用来获得1970年1月1日到time_point时间经过的duration。
    // 举个例子，如果timepoint以天为单位，函数返回的duration就以天为单位。
    //
    // 由于各种time_point表示方式不同，chrono也提供了相应的转换函数 time_point_cast。
    // template < class ToDuration, class Clock, class Duration>
    // time_point<Clock, ToDuration> time_point_cast(const time_point<Clock, Duration>&tp);
    {
        using namespace std::chrono;
        typedef duration<int, std::ratio<60 * 60 * 24>> days_type;
        time_point<system_clock, days_type> today = time_point_cast<days_type>(system_clock::now());
        std::cout << today.time_since_epoch().count() << " days since epoch" << std::endl;
    }

    {
        // 自定义
        time_point <system_clock, duration<int>> tp_seconds(duration<int>(1));
        system_clock::time_point tp1;
        system_clock::time_point tp2;
        tp1 = system_clock::from_time_t(111);
        tp2 = system_clock::from_time_t(222);

        //class std::chrono::duration<__int64,struct std::ratio<1,10000000> >
        using mydur = std::chrono::duration<long long, struct std::ratio<1, 10000000> >;
        // using mydur = std::chrono::duration<__int64, struct std::ratio<1, 10000000> >; // vs2019
        auto itt = tp2 - tp1;
        //typename ttt = typeid(itt);
        mydur myd;
        //using period = typename itt; itt.
        std::cout << "[tp2-tp1]" << std::endl
            << "         [default]" <<(tp2 - tp1).count() << std::endl
            << "         [double]" << duration_cast<duration<double>>(tp2 - tp1).count() << std::endl
            << "         [int]" << duration_cast<duration<int>>(tp2 - tp1).count() << std::endl
            << "         [typeid]" << typeid(itt).name() << std::endl
            << "         [den]" << mydur::period::den << std::endl;
        std::cout << "[tp2-tp1]" << (tp2 - tp1).count() << "[itt_mat]" << itt.max().count() << "[itt_min]" << itt.min().count() << std::endl;
        //cout << "[tp2-tp1]" << (tp2 - tp1).count() << "[itt]" << typeid(itt).name() << "[itt]" << itt.period::den << endl;
        //cout << "[tp2-tp1]" << (tp2 - tp1).count() << "[itt]" << typeid(itt).name() << "[itt]" << myd.period::den << endl;
    }
}

// Clocks
// #include <ctime>
// #include <ratio>
// #include <chrono>
void test1_cpp11_2_chrono_clock()
{
    // 3.Clocks
    //
    // 3.1 std::chrono::system_clock 它表示当前的系统时钟，系统中运行的所有进程使用now()得到的时间是一致的。
    // 每一个clock类中都有确定的time_point, duration, Rep, Period 类型。
    // 操作有：
    // now() 当前时间time_point
    // to_time_t() time_point转换成time_t秒
    // from_time_t() 从time_t转换成time_point
    // 典型的应用是计算时间日期：
    using std::chrono::system_clock;
    std::chrono::duration<int, std::ratio<60 * 60 * 24> > one_day(1);
    system_clock::time_point today = system_clock::now();
    system_clock::time_point tomorrow = today + one_day;
    std::time_t tt;
    tt = system_clock::to_time_t(today);
    std::cout << "today is: " << ctime(&tt);
    tt = system_clock::to_time_t(tomorrow);
    std::cout << "tomorrow will be: " << ctime(&tt);


    // 具体来说，时钟类 system_clock 是一个系统范围的实时时钟。
    //  system_clock 提供了对当前时间点 time_point 的访问，将得到时间点转换为 time_t 类型的时间对象，
    //  就可以基于这个时间对象获取到当前的时间信息了。
    // struct system_clock { // wraps GetSystemTimePreciseAsFileTime/GetSystemTimeAsFileTime
    //    using rep = long long;
    //    using period = ratio<1, 10'000'000>; // 100 nanoseconds
    //    using duration = chrono::duration<rep, period>;
    //    using time_point = chrono::time_point<system_clock>;
    //    static constexpr bool is_steady = false;

    //    _NODISCARD static time_point now() noexcept
    //    { // get current time
    //        return time_point(duration(_Xtime_get_ticks()));
    //    }

    //    _NODISCARD static __time64_t to_time_t(const time_point& _Time) noexcept
    //    { // convert to __time64_t
    //        return duration_cast<seconds>(_Time.time_since_epoch()).count();
    //    }

    //    _NODISCARD static time_point from_time_t(__time64_t _Tm) noexcept
    //    { // convert from __time64_t
    //        return time_point{ seconds{_Tm} };
    //    }
    //};
    //
    //通过以上源码可以了解到在 system_clock 类中的一些细节信息：
    //    rep：时钟周期次数是通过整形来记录的 long long
    //    period：一个时钟周期是 100 纳秒 ratio<1, 10'000'000>
    //    duration：时间间隔为 rep * period 纳秒 chrono::duration<rep, period>
    //    time_point：时间点通过系统时钟做了初始化 chrono::time_p - oint<system_clock>，里面记录了新纪元时间点
    //
    //提供了三个静态成员函数：
    // 返回表示当前时间的时间点。
    //    static std::chrono::time_point<std::chrono::system_clock> now() noexcept;
       // 将 time_point 时间点类型转换为 std::time_t 类型
    //    static std::time_t to_time_t(const time_point & t) noexcept;
       // 将 std::time_t 类型转换为 time_point 时间点类型
    //    static std::chrono::system_clock::time_point from_time_t(std::time_t t) noexcept;
    {
        using namespace std::chrono;
        system_clock::time_point epoch;// 新纪元1970.1.1时间
        duration<int, std::ratio<60 * 60 * 24>> day(1);
        system_clock::time_point ppt(day);// 新纪元1970.1.1时间 + 1天
        using dday = duration<int, std::ratio<60 * 60 * 24>>;
        time_point<system_clock, dday> t(dday(10));// 新纪元1970.1.1时间 + 10天

        system_clock::time_point today = system_clock::now();// 系统当前时间
        time_t tm = system_clock::to_time_t(today);// 转换为time_t时间类型
        std::cout << "今天的日期是:    " << ctime(&tm);

        time_t tm1 = system_clock::to_time_t(today + day);
        std::cout << "明天的日期是:    " << ctime(&tm1);

        time_t tm2 = system_clock::to_time_t(epoch);
        std::cout << "新纪元时间:      " << ctime(&tm2);

        time_t tm3 = system_clock::to_time_t(ppt);
        std::cout << "新纪元时间+1天:  " << ctime(&tm3);

        time_t tm4 = system_clock::to_time_t(t);
        std::cout << "新纪元时间+10天: " << ctime(&tm4);
    }


    // 3.2 std::chrono::steady_clock 为了表示稳定的时间间隔，后一次调用now()得到的时间总是比前一次的值大
    //  （这句话的意思其实是，如果中途修改了系统时间，也不影响now()的结果），每次tick都保证过了稳定的时间间隔。
    // 操作有：
    // now() 获取当前时钟
    // 典型的应用是给算法计时：
    {
        using namespace std::chrono;
        steady_clock::time_point t1 = steady_clock::now();
        std::cout << "printing out 1000 stars...\n";
        for (int i = 0; i < 1000; ++i) std::cout << "*";
        std::cout << std::endl;

        steady_clock::time_point t2 = steady_clock::now();
        duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
        std::cout << "It took me " << time_span.count() << " seconds.";
        std::cout << std::endl;
    }


    //如果我们通过时钟不是为了获取当前的系统时间，而是进行程序耗时的时长，
    // 此时使用 syetem_clock 就不合适了，因为这个时间可以跟随系统的设置发生变化。
    // 在 C++11 中提供的时钟类 steady_clock 相当于秒表，只要启动就会进行时间的累加，
    // 并且不能被修改，非常适合于进行耗时的统计。
    //
    //struct steady_clock { // wraps QueryPerformanceCounter
    //    using rep = long long;
    //    using period = nano;
    //    using duration = nanoseconds;
    //    using time_point = chrono::time_point<steady_clock>;
    //    static constexpr bool is_steady = true;
    //
       // get current time
    //    _NODISCARD static time_point now() noexcept
    //    {
           // doesn't change after system boot
    //        const long long _Freq = _Query_perf_frequency();
    //        const long long _Ctr = _Query_perf_counter();
    //        static_assert(period::num == 1, "This assumes period::num == 1.");
    //        const long long _Whole = (_Ctr / _Freq) * period::den;
    //        const long long _Part = (_Ctr % _Freq) * period::den / _Freq;
    //        return time_point(duration(_Whole + _Part));
    //    }
    //};
    //通过以上源码可以了解到在 steady_clock 类中的一些细节信息：
    //
    //rep：时钟周期次数是通过整形来记录的 long long
    //period：一个时钟周期是 1 纳秒 nano
    //duration：时间间隔为 1 纳秒 nanoseconds
    //time_point：时间点通过系统时钟做了初始化 chrono::time_point<steady_clock>
    //另外，在这个类中也提供了一个静态的 now() 方法，用于得到当前的时间点，函数原型如下：
    //
    //static std::chrono::time_point<std::chrono::steady_clock> now() noexcept;

    //假设要测试某一段程序的执行效率，可以计算它执行期间消耗的总时长
    {
        using namespace std::chrono;
        steady_clock::time_point start = steady_clock::now();   // 获取开始时间点
        std::cout << "print 1000 stars ...." << std::endl;   // 执行业务流程
        for (int i = 0; i < 1000; ++i)
        {
            std::cout << "*";
        }
        std::cout << std::endl;
        steady_clock::time_point last = steady_clock::now();     // 获取结束时间点
        auto dt = last - start;                                  // 计算差值
        std::cout << "总共耗时: " << dt.count() << "纳秒" << std::endl;
    }


    // 3.3 最后一个时钟，std::chrono::high_resolution_clock 顾名思义，这是系统可用的最高精度的时钟。
    // 实际上high_resolution_clock只不过是system_clock或者steady_clock的typedef。
    // 操作有：
    // now() 获取当前时钟。
}

#include <ctime>
#include <iomanip>
#include <sstream>
void f4()
{
    std::cout << "print 1000 stars ...." << std::endl;
    for (int i = 0; i < 1000; ++i)
    {
        std::cout << "*";
    }
    std::cout << std::endl;
}

using Clock = std::chrono::high_resolution_clock;
using Ms = std::chrono::milliseconds;
using Sec = std::chrono::seconds;
template<class Duration>
using TimePoint = std::chrono::time_point<Clock, Duration>;

void print_ms(const TimePoint<Ms>& time_point)
{
    std::cout << time_point.time_since_epoch().count() << " ms\n";
}
void test1_cpp11_2_chrono_cast()
{
    using namespace std::chrono;

    // duration_cast
    // duration_cast 是 chrono 库提供的一个模板函数，这个函数不属于 duration 类。
    //  通过这个函数可以对 duration 类对象内部的时钟周期 Period，和周期次数的类型 Rep 进行修改，该函数原型如下：
    //
    //     template <class ToDuration, class Rep, class Period>
    // constexpr ToDuration duration_cast(const duration<Rep, Period>&dtn);
    // 在源周期能准确地为目标周期所整除的场合（例如小时到分钟），
    // 浮点时长和整数时长间转型能隐式进行无需使用 duration_cast ，其他情况下都需要通过函数进行转换。
    //
    //    我们可以修改一下上面测试程序执行时间的代码，在代码中修改 duration 对象的属性：
    {
        auto t1 = steady_clock::now();
        f4();
        auto t2 = steady_clock::now();

        // 整数时长：要求 duration_cast
        auto int_ms = duration_cast<std::chrono::milliseconds>(t2 - t1);

        // 小数时长：不要求 duration_cast
        duration<double, std::ratio<1, 1000>> fp_ms = t2 - t1;

        std::cout << "f4() took " << fp_ms.count() << " ms, "
            << "or " << int_ms.count() << " whole milliseconds\n";

        //print 1000 stars ....
        //    * ***************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************
        //    f() took 40.2547 ms, or 40 whole milliseconds
    }

    //time_point_cast
    //time_point_cast 也是 chrono 库提供的一个模板函数，这个函数不属于 time_point 类。
    // 函数的作用是对时间点进行转换，因为不同的时间点对象内部的时钟周期 Period，和周期次数的类型 Rep 可能也是不同的，
    // 一般情况下它们之间可以进行隐式类型转换，也可以通过该函数显示的进行转换，函数原型如下：
    //
    //    template <class ToDuration, class Clock, class Duration>
    //time_point<Clock, ToDuration> time_point_cast(const time_point<Clock, Duration> &t);
    //关于函数的使用，示例代码如下：
    {
        TimePoint<Sec> time_point_sec(Sec(6));
        // 无精度损失, 可以进行隐式类型转换
        TimePoint<Ms> time_point_ms(time_point_sec);
        print_ms(time_point_ms);    // 6000 ms

        time_point_ms = TimePoint<Ms>(Ms(6789));
        // error，会损失精度，不允许进行隐式的类型转换
        //TimePoint<Sec> sec(time_point_ms);

        // 显示类型转换,会损失精度。6789 truncated to 6000
        time_point_sec = std::chrono::time_point_cast<Sec>(time_point_ms);
        print_ms(time_point_sec); // 6000 ms

        //注意事项：关于时间点的转换如果没有没有精度的损失可以直接进行隐式类型转换，
        //如果会损失精度只能通过显示类型转换，也就是调用 time_point_cast 函数来完成该操作。
    }


    //微软的实现是这样的：
    //    namespace std
    //{
    //    namespace chrono
    //    {
    //        struct system_clock
    //        {
    //            static time_point now() __NOEXCEPT
    //            {
    //                return (time_point(duration(_Xtime_get_ticks())));
    //            }
    //            _Xtime_get_ticks（）使用GetSystemTimeAsFileTime（） 。 该功能的精度为1毫秒。

    //需要高精度时间戳（绝对时间点），而不是计算相对时间，那么可以考虑这个API:

    //GetSystemTimeAsFileTime()
    //    该函数返回自1601年1月1日起，到现在的时间（以 100ns 为单位）。
    //    其实，Windows上的 std::clock() 函数就是通过 GetSystemTimeAsFileTime() 来实现的，
    //  只不过 std::clock() 返回的是从程序启动到当前的时间（毫秒数），如下：
    //
    //    clock_t __cdecl clock(
    //        void
    //    )
    //{
    //    unsigned __int64 current_tics;
    //    FILETIME ct;
    //    GetSystemTimeAsFileTime(&ct);
    //    current_tics = (unsigned __int64)ct.dwLowDateTime +
    //        (((unsigned __int64)ct.dwHighDateTime) << 32);
    //    /* calculate the elapsed number of 100 nanosecond units */
    //    current_tics -= start_tics;  // start_tics 在程序启动时初始化
    //    /* return number of elapsed milliseconds */
    //    return (clock_t)(current_tics / 10000);
    //}
    //
    //想要获得从1601年1月1日以来，到目前为止所经历过的 微秒(micro seconds)数，可以这样做：
    //FILETIME fileTime;
    //long long now_long;
    //GetSystemTimeAsFileTime(&fileTime);
    //now_long = (long long(fileTime.dwHighDateTime) << 32) + fileTime.dwLowDateTime;
    //std::cout << "micro time from 1601.1.1:00:00:00 is: " << (now_long / 10) << std::endl;


    // default_value
    time_point<system_clock> startTime;// 1970-1-1 8:0:0;
    std::time_t tmStartTime = system_clock::to_time_t(startTime);
    std::cout << "startTime_time_t " << tmStartTime <<  " startTime_put_time " << std::put_time(std::localtime(&tmStartTime), "%F %T") << std::endl;
    //startTime_time_t 0 startTime_put_time 1970-01-01 08:00:00


    // get current time
    time_point<system_clock> nowTime = system_clock::now();
    std::time_t tmNowTime = system_clock::to_time_t(nowTime);
    std::cout << "nowTime_time_t " << tmNowTime << " nowTime_str " << std::put_time(std::localtime(&tmNowTime), "%F %T") << std::endl;
    //nowTime_time_t 1661218579 nowTime_str 2022 - 08 - 23 09:36 : 19


    // use timestamp
    // 2020-01-08 15:05:50(1578466970)
    time_point<system_clock> stampTime(seconds(1578466970));
    std::time_t tmStampTime = system_clock::to_time_t(stampTime);
    std::cout << "stampTime_time_t " << tmStampTime << " stampTime_str " << std::put_time(std::localtime(&tmStampTime), "%F %T") << std::endl;
    //stampTime_time_t 1578466970 stampTime_str 2020 - 01 - 08 15:02 : 50


    // some hours ago
    std::time_t tmSomeTimeAgo = system_clock::to_time_t(nowTime - hours(22) - minutes(30));
    std::cout << "22 hours 30 minutes ago time_t" << tmSomeTimeAgo << "22 hours 30 minutes ago " << std::put_time(std::localtime(&tmSomeTimeAgo), "%F %T") << std::endl;
    //22 hours 30 minutes ago time_t166113757922 hours 30 minutes ago 2022 - 08 - 22 11:06 : 19


    // get time from string
    // use "std::get_time()"
    std::tm aTime;
    std::string strTime("2008-08-08 10:0:0");
    std::stringstream ssTime(strTime);
    ssTime.imbue(std::locale("de_DE.utf-8"));
    ssTime >> std::get_time(&aTime, "%Y-%m-%d %H:%M:%S");
    time_point<system_clock> tp = system_clock::from_time_t(std::mktime(&aTime));
    std::time_t aTestTime = system_clock::to_time_t(tp);
    std::cout << "aTime_time_t " << aTestTime << " aTime_str " << std::put_time(std::localtime(&aTestTime), "%F %T") << std::endl;
    std::cout << "compare: nowTime >= aTime ? " << (nowTime >= tp ? "true" : "false") << std::endl;
    //aTime_time_t 1218160800 aTime_str 2008 - 08 - 08 10:00 : 00
    //compare: nowTime >= aTime ? true


    // end time
    time_point<system_clock> endTime = system_clock::now();
    std::time_t tmEndTime = system_clock::to_time_t(endTime);
    std::cout << "endTime_time_t " << tmEndTime << " endTime_str " << std::put_time(std::localtime(&tmEndTime), "%F %T") << std::endl;
    std::cout << "the program used\t" << duration_cast<microseconds>(endTime - nowTime).count() << "us.\n";
    //endTime_time_t 1661218579 endTime_str 2022 - 08 - 23 09:36 : 19
    //the program used        16584us.


    // used time
    time_point<system_clock> p1 = system_clock::now();   // 默认时间间隔为 100纳秒 也就是1后7个0
    std::time_t tmNowTime1 = system_clock::to_time_t(p1);
    std::cout << "1  " << p1.time_since_epoch().count() << " time_t " << tmNowTime1 << std::endl;
    time_point<steady_clock> p3 = steady_clock::now();     // 默认时间间隔为 1纳秒 也就是1后9个0
    std::cout << "3  " << p3.time_since_epoch().count() << std::endl;
    std::this_thread::sleep_for(milliseconds(1234));
    std::this_thread::sleep_for(seconds(1));
    time_point<system_clock> p2 = system_clock::now();
    std::time_t tmNowTime2 = system_clock::to_time_t(p2);
    std::cout << "2  " << p2.time_since_epoch().count() << " time_t " << tmNowTime2 << std::endl;

    time_point<steady_clock> p4 = steady_clock::now();
    std::cout << "4  " << p4.time_since_epoch().count() << " used " << p4.time_since_epoch().count() - p3.time_since_epoch().count() << std::endl;

    std::cout << "[timeuse_defalut]" << (p2 - p1).count()
        << "[timeuse_s]" << duration_cast<duration<int, std::ratio<1, 1>>>(p2 - p1).count()
        << "[timeuse_milis]" << duration_cast<duration<int, std::ratio<1, 1000>>>(p2 - p1).count()
        << "[timeuse_s]" << duration_cast<seconds>(p2 - p1).count()
        << "[timeuse_milis]" << duration_cast<milliseconds>(p2 - p1).count()
        << "[xxx]" << duration_cast<duration<int, std::ratio<1, 1000000>>>(p2 - p1).count() << std::endl;
    //    1  16612193642482445 time_t 1661219364
    //    3  523153593620700
    //    2  16612193664887254 time_t 1661219366
    //    4  523155835130400 used 2241509700
    //    [timeuse_defalut]22363088[timeuse_s]2[timeuse_milis]2236[timeuse_s]2[timeuse_milis]2236[xxx]2236308
}


void test1_cpp11_2_chrono_put_time()
{
    // std::put_time()函数
    // 此函数首先通过构造一个类型为basic_ostream::sentry的对象来访问输出序列。
    // 然后（如果评估计算 sentry 对象为 true），它调用 time_put::put（使用流的选定区域设置）来执行格式化和插入操作，
    // 相应地调整流的内部状态标志。 最后，它在返回之前销毁 sentry 对象。
    // 它用于插入由tmb指向的时间和日期信息的表示，根据参数fmt指定来格式化。
    // 声明
    // 以下是 std::put_time 函数的声明。
    // template <class charT>
    // /*unspecified*/ put_time(const struct tm* tmb, const charT * fmt);
    // 参数
    // tmb − 指向类型struct tm的对象的指针，具有格式化的日期和时间信息。 struct tm是<ctime>头中定义的类。
    // fmt − time_put::put 使用C字符串作为格式字符串。它包含常规字符和特殊格式说明符的任意组合。这些格式说明符被函数替换为相应的值，以表示在tmb中指定的时间。
    //
    // 格式都以百分比（％）符号开头，如下所示 -

    // 格式都以百分比（％）符号开头，如下所示
    //    说明符   替换                                          示例
    //    % a       工作日名称的缩写* Thu
    //    % A       完整工作日名称* Thursday
    //    % b       月份名称缩写* Aug
    //    % B       完整月份名称* August
    //    % c       日期和时间表示                                Thu Aug 23 14:55 : 02 2019
    //    % C       年份除以100，并截断为整数（00 - 99）            20
    //    % d       月份中的某一天，用零填充（01 - 31）             23
    //    % D       MM / DD / YY日期的简写，相当于％m / ％d / ％y         08 / 23 / 19
    //    % e       月份中的某日，空格填充（1 - 31）                23
    //    % F       YYYY - MM - DD日期的简写，相当于％Y - ％m - ％d
    //    % g       基于周的年份，后两位数字（00 - 99）             01
    //    % G       一年中周                                      2001
    //    % h       月份名称的缩写（与％b相同）                   Aug
    //    % H       24小时格式（00 - 23）                           14
    //    % I       12小时格式（01 - 12）                           02
    //    % j       一年中的某日（001 - 366）                       235
    //    % m       月份的十进制数（01 - 12）                       08
    //    % M       分钟（00 - 59）                                 56
    //    % n       新行字符（'/n'）
    //    % p       指定AM或PM                                    PM
    //    % r       12小时时钟时间                                02:55 : 02 pm
    //    % R       24小时HH : MM时间，相当于％H : ％M                14 : 51
    //    % S       秒（00 - 61）                                   02
    //    % t       水平制表符（’ / t’）
    //    % T       ISO 8601时间格式(HH : MM : SS)，相当于 % H : % M : % S
    //    % u       ISO 8601工作日，星期一的数字为1（1 - 7）        4
    //    % U       周数，以第一个星期日为第一周的第一天（00 - 53） 33
    //    % V       ISO 8601周编号（00 - 53）                       34
    //    % w       工作日，使用十进制数，星期日为0（0 - 6）        4
    //    % W       周数，第一个星期一作为第一周的第一天（00 - 53）
    //    % x       日期的表示                                    08 / 23 / 01
    //    % X       时间的表示                                    14:55 : 02
    //    % y       年份，最后两位数字（00 - 99）                   01
    //    % Y       年份，四位数字                                2001
    //    % z       ISO 8601偏离UTC在时区（1分钟 = 1，1小时 = 100） + 100
    //    % Z       时区名称或缩写                                CDT
    //    % %％符号%


//#include <iostream>
//#include <iomanip>
//#include <ctime>
//#include <chrono>
    using std::chrono::system_clock;
    std::time_t tt = system_clock::to_time_t(system_clock::now());
    struct std::tm* ptm = std::localtime(&tt);
    std::cout << "Now (local time): " << std::put_time(ptm, "%c") << '\n';

}




// regex_match
void test1_cpp11_2_regex_match()
{
    // regex 库中涉及到的主要类型有：
    // 以std::string为代表的处理字符串的类型（我们知道还有存储wchar_t的wstring类、原生c式字符串const char* 等等，
    //   为了简化处理仅介绍std::string类型相关的操作，当你把握住了regex的主脉络之后，想使用其他的版本只要类比就可以）
    // std::regex类，该类型需要一个代表正则表达式的字符串和一个文法选项作为输入，当文法选项不提供时默认为ECMAScript。
    // std::match_results类，该类用来记录匹配的结果，这是一个模板类，该类的模板参数是一个迭代器类型，
    //   对于std::string来说我们定义了smatch作为match_results<string::const_iterator>作为别名。
    // std::sub_match类，该类其实封装了两个迭代器，第一个代表开始部分，第二个代表结束部分，就像你用两个下表索引去表达一个字符串的某一个子串一样。
    //  这个类就是通过这样的方式提供原字符串的某一个子串作为结果。实际上match_results中就封装了一些std::sub_match类型的对象。
    //  （为什么是一些而不是一个，因为一次匹配可能会产生多个结果返回，regex认为每个括号对构成一个子匹配项，regex匹配的结果可以显式每个子匹配项匹配到的内容。）
    // 现在我们有了表达字符串的类，表达正则匹配的类，表达匹配结果的类，接下来regex提供三个匹配函数：
    //  bool std::regex_match(...)
    //  bool std::regex_search(...)
    //  string std::regex_replace(...)//实际上返回类型是根据你输入的数据类型对应的basic_string类。
    // 首先说明三个函数功能上的不同，std::regex_match是全文匹配，即它希望你输入的字符串要和正则表达式全部匹配，才认为匹配成功，否则匹配失败，
    //  而std::regex_search是在你输入的字符串中不断搜索符合正则表达式描述的子字符串，然后将第一个匹配到的子字符串返回。
    //  std::regex_replace是在std::regex_search的基础上更进一步，可以将匹配的子字符串替换为你提供的字符串。


    // 使用正则表达式，你就必须包含所需的头文件regex, 里面包含了所需的函数，一般的第一步需要确定要匹配的模式pattern,
    // 使用regex类型进行定义regex pattern("要匹配的正则表达式模式")，
    // 其次一般的常用操作就是灵活的运用regex_match, regex_search, regex_replace这三个函数，
    // 后面还有几个用的不太多的函数regex_iterator后续会介绍：

    // regex_match的相关及举例
    // 原型大致为：
    // bool regex_match(const basic_string<charT, ST, SA>&s,
    //    const basic_regex<charT, traits>&rgx,
    //    regex_constants::match_flag_type flags = regex_constants::match_default);
    //
    //  第一个参数s为：需要用正则表达式去匹配的字符串，简言之就是要处理的字符串。
    //  第二个参数rgx为：为一个basic_regex的一个对象，也就是你要进行匹配的模式，用正则字符串表示，其声明为:
    //    (1)typedef basic_regex<char>    regex;//正常字符处理（常用）
    //    (2)typedef basic_regex<wchar_t> wregex;//宽字符处理
    //  第三个参数flags是控制第二个参数如何去匹配，第三个参数处可以设置一个或多个常量去控制，一般设置有默认值
    //  返回值为：如果匹配成功，返回True,否则返回False
    //


    std::cout << "testregex1------------------" << std::endl;
    //此为匹配字符串"wdw9078798asadada"，是否满足匹配正则表达式所要求的条件，
    //regex{ "[A-Z]{1,3}.*"}:目的是匹配由1个到三个字母开头的字符串，匹配成功时返回true,否则返回false
    bool status = false;
    std::string str1 = "wdw9078798asadada";
    status = std::regex_match(str1, std::regex{ "[a-z]{1,3}.*" }); //第三个参数为忽略大小写
    if (status == true) {
        printf("匹配成功！\n");
    }
    else {
        printf("匹配失败！\n");
    }
    // 结果为匹配成功！

    // 当然在regex定义时，可以指定第二个参数类型flag_type为控制regex的属性，构造函数声明如下：
    // explicit basic_regex(
    //    const basic_string<_Elem, _STtraits, _STalloc>&_Str,
    //    flag_type _Flags = regex_constants::ECMAScript)
    //
    // 第一个参数不用说，就是指定一个字符串，为要匹配的正则式，
    // 第二个参数为指定属性，之前已经用到的一个为regex_constants::icase, 表示忽略大小写进行匹配，也可以写成regex::icase,
    // 但源码中为regex_constants::？这种形式，所以采用这种写法，其中的声明还有：

    // 来自regex中的声明
    // static constexpr flag_type icase = regex_constants::icase;//忽略大小写
    // static constexpr flag_type nosubs = regex_constants::nosubs;//子无表达式，
    // static constexpr flag_type optimize = regex_constants::optimize;//优化匹配，匹配效率优于构造regex对象的效率。
    // static constexpr flag_type collate = regex_constants::collate;//区域敏感性
    // static constexpr flag_type ECMAScript = regex_constants::ECMAScript;//默认的语法
    // static constexpr flag_type basic = regex_constants::basic;//基础的posix语法
    // static constexpr flag_type extended = regex_constants::extended;//扩展posix语法
    // static constexpr flag_type awk = regex_constants::awk;
    // static constexpr flag_type grep = regex_constants::grep;
    // static constexpr flag_type egrep = regex_constants::egrep;

    status = std::regex_match(str1, std::regex{ "[A-Z]{1,3}.*"}); // 默认不忽略大小写
    if (status == true) {
        printf("匹配成功！\n");
    }
    else {
        printf("匹配失败！\n");
    }

    status = std::regex_match(str1, std::regex("[A-Z]{1,3}.*")); // 注意 { （ 效果一样
    if (status == true) {
        printf("匹配成功！\n");
    }
    else {
        printf("匹配失败！\n");
    }

    status = std::regex_match(str1, std::regex{ "[A-Z]{1,3}.*",std::regex_constants::icase }); //第三个参数为忽略大小写
    if (status == true) {
        printf("匹配成功！\n");
    }
    else {
        printf("匹配失败！\n");
    }
}


// regex_search
void test1_cpp11_2_regex_search()
{
    // bool regex_search(const basic_string<charT, ST, SA>&s,
    //    const basic_regex<charT, traits>&rgx,
    //    regex_constants::match_flag_type flags = regex_constants::match_default);
    //  参数含义与regex_match一致，此方法不返回匹配成功的字符串，只是确定里面是否有满足正则式的字句

    // bool regex_search(const basic_string<charT, ST, SA>&s,
    //    match_results<typename basic_string<charT, ST, SA>::const_iterator, Alloc>&m,
    //    const basic_regex<charT, traits>&rgx,
    //    regex_constants::match_flag_type flags = regex_constants::match_default);
    // 其他参数含义一样，多了一个m参数，其含义为此处为一个match_results的类型，其作用是存储匹配的结果或者满足子表达式匹配的结果，返回结果为一个迭代器

    std::cout << "testregex2------------------" << std::endl;
    {
        // 此程序的regex为regex("[0-9]{2}[a-z]{1,4}[0-9]{2}")
        std::smatch result;
        std::string str1("i89love78you,mrsLu");
        bool sta = regex_search(str1, result, std::regex("[0-9]{2}[a-z]{1,4}[0-9]{2}"));
        for (const auto &it : result)
        {
            std::cout << it.str() << std::endl;
        }
        /*结果：
            89love78
        */
    }

    {
        //此程程序中的regex为regex("([0-9]{2})([a-z]{1,4})([0-9]{2})")注意中间有括号和没有括号的区别
        std::smatch result;
        std::string str1("i89love78you,mrsLu");
        bool sta = std::regex_search(str1, result, std::regex("([0-9]{2})([a-z]{1,4})([0-9]{2})"));
        for (const auto& it : result) {
            std::cout << it.str() << std::endl;
        }
        /*当有子表达式匹配时，访问匹配结果中的存储为：
        第一个存储的结果为满足整个正则匹配式的字符串，从第二个开始，依次存储从左向右的每个圆括号中的匹配式的结果，所以可以进行以下访问：
        cout << result[0] << endl; //输出89love78
        cout << result.str(0) << endl; //输出89love78
        二者等效，
        cout << result.str(1) << endl; //输出89
        cout << result.str(2) << endl; //输出love
        cout << result.str(3) << endl; //输出78
        */
        /*结果：
            89love78
            89
            love
            78
        */
    }

    {
        //从以上两个程序结果可以看出，smatch存储的结果为以()为子匹配式进行匹配，在某些时候这种方式可以起到非常大的作用。
        //当然regex_results对象有两个方法suffix()和prefix()分别显示的为匹配结果的后缀和前缀，上述的匹配结果进行调用有如下信息：

        std::smatch result;
        std::string str1("i89love78you,mrsLu");
        bool sta = regex_search(str1, result, std::regex("[0-9]{2}[a-z]{1,4}[0-9]{2}"));
        std::cout << "后缀为：" << result.suffix().str() << std::endl << "前缀为：" << result.prefix().str() << std::endl;
        /*结果：
            后缀为：you,mrsLu
            前缀为：i
        */
    }
}


//regex_replace
void test1_cpp11_2_regex_replace()
{
    //regex_replace可以查找匹配正则表达式的字符串并使用其它格式来替换，可以是自己想要替换的普通字符串，也可以是$指定
    //原型声明：
    //template <class traits, class charT, class ST, class SA>
    //    basic_string<charT, ST, SA> regex_replace(const basic_string<charT, ST, SA>&s,
    //    const basic_regex<charT, traits>&rgx,
    //    const charT * fmt,
    //    regex_constants::match_flag_type flags = regex_constants::match_default);
    //第一个参数s表示要被操作的字符串对象
    //第二个参数rgx为匹配正则表达式
    //第三个参数fmt为以何种方式进行替换
    //第四个参数flags为一种方式，代表怎样去替换
    //返回值为：如果匹配成功返回已经替换成功的字符串，否则匹配失败，返回原字符串

    //第三个参数的设置如下表（来自c++ reference）其中（第三个为$`,第四个为$’）：
    //characters    replacement
    //    $n    n - th backreference(i.e., a copy of the n - th matched group specified with parentheses in the regex pattern).
    //    n must be an integer value designating a valid backreference, greater than 0, and of two digits at most.
    //    $& A copy of the entire match
    //    $`    The prefix(i.e., the part of the target sequence that precedes the match).
    //    $´    The suffix(i.e., the part of the target sequence that follows the match).
    //    $$    A single $ character.

    //第四个参数的设置常量如下表（来自c++ reference）这些常量全都在regex_contants命名空间中有声明:
    //flag* effects    notes
    //    match_default    Default    Default matching behavior.
    //    This constant has a value of zero** .
    //    match_not_bol    Not Beginning - Of - Line    The first character is not considered a beginning of line("^" does not match).
    //    match_not_eol    Not End - Of - Line    The last character is not considered an end of line("$" does not match).
    //    match_not_bow    Not Beginning - Of - Word    The escape sequence "\b" does not match as a beginning - of - word.
    //    match_not_eow    Not End - Of - Word    The escape sequence "\b" does not match as an end - of - word.
    //    match_any    Any match    Any match is acceptable if more than one match is possible.
    //    match_not_null    Not null    Empty sequences do not match.
    //    match_continuous    Continuous    The expression must match a sub - sequence that begins at the first character.
    //    Sub - sequences must begin at the first character to match.
    //    match_prev_avail    Previous Available    One or more characters exist before the first one. (match_not_bol and match_not_bow are ignored)
    //    format_default    Default formatting    Uses the standard formatting rules to replace matches(those used by ECMAScript's replace method).
    //        This constant has a value of zero * *.
    //        format_sed    sed formatting    Uses the same rules as the sed utility in POSIX to replace matches.
    //        format_no_copy    No copy    The sections in the target sequence that do not match the regular expression are not copied when replacing matches.
    //        format_first_only    First only    Only the first occurrence of a regular expression is replaced.

    std::regex pattern("([0-9]{4})-([0-9]{2})-([0-9]{2})");
    std::regex r(pattern);
    std::string date = "日期为：2020-08-04 2020-05-30";
    std::cout << std::regex_replace(date, r, "$1.$2.$3") << std::endl;
    /*结果：
        日期为:2020.08.04 2020.05.30
    */

    //当然，也可以设置regex_replace第四那个参数，设置将字符串中没有被匹配的部分不输出
    std::cout << std::regex_replace(date, r, "$1.$2.$3", std::regex_constants::format_no_copy) << std::endl;
    //输出为2020.08.042020.05.30

    //最常使用的为进行普通字符串的替代
    //将字符串中的大写字母换为_
    std::regex patt("[A-Z]");
    std::string s = "www.asxWscnsj.com";
    std::cout << regex_replace(s, patt, "_") << std::endl;
    //执行结果www.asx_scnsj.com
}


//match_results
//regex_error
//regex_iterator
void test1_cpp11_2_regex_other()
{
    //match_results
        //typedef match_results<const char*> cmatch;
        //typedef match_results<const wchar_t*> wcmatch;
        //typedef match_results<string::const_iterator> smatch;  //(常用)
        //typedef match_results<wstring::const_iterator> wsmatch;
        //上面为regex头文件中的宏声明，常用的为smatch，例子见regex_search栏

    //regex_error
        //class regex_error : public runtime_error { /* ... */ };
        //由此可见，该异常类继承自runtime_error类。
        //异常描述：
        //此异常类型的对象由正则表达式库的元素引发。
        //它继承了标准异常runtime_error，并有一个特殊的公共成员函数, 它根据引发它的错误的类型返回regex_constants:：error_type的特定代码：
    //flag    error
    //    error_collate    The expression contained an invalid collating element name.
    //    error_ctype    The expression contained an invalid character class name.
    //    error_escape    The expression contained an invalid escaped character, or a trailing escape.
    //    error_backref    The expression contained an invalid back reference.
    //    error_brack    The expression contained mismatched brackets([and]).
    //    error_paren    The expression contained mismatched parentheses((and)).
    //    error_brace    The expression contained mismatched braces({ and }).
    //    error_badbrace    The expression contained an invalid range between braces({ and }).
    //    error_range    The expression contained an invalid character range.
    //    error_space    There was insufficient memory to convert the expression into a finite state machine.
    //    error_badrepeat    The expression contained a repeat specifier(one of * ? +{) that was not preceded by a valid regular expression.
    //    error_complexity    The complexity of an attempted match against a regular expression exceeded a pre - set level.
    //    error_stack    There was insufficient memory to determine whether the regular expression could match the specified character sequence.


    try
    {
        std::regex myregex("*");
    }
    catch (std::regex_error& e)
    {
        std::cerr << "error code:" << e.code() << ":" << e.what() << std::endl;
    }
    /*
        error code:10:regex_error(error_badrepeat): One of *?+{ was not preceded by a valid regular expression.
    */

    //regex_iterator
    //构造方法：
    //无参构造函数：regex_iterator();
    //拷贝构造函数：regex_iterator(const regex_iterator & rit)
    //初始化构造函数：regex_iterator(BidirectionalIterator first,
    //        BidirectionalIterator last,
    //        const regex_type & rgx,
    //        regex_constants::match_flag_type flags = regex_constants::match_default);
    //初始化构造函数的第四个参数与regex_replace的第四个参数的含义一样，复制选项也一样，可参考上述文章

    //                    tab
    std::string s("this sub    123 subject has a submarine as a subsequence");
    std::regex e("\\b(sub)([^ ]*)");   // matches words beginning by "sub"，后跟非空白字符，遇到空格会终止

    std::regex_iterator<std::string::iterator> rit(s.begin(), s.end(), e);
    std::regex_iterator<std::string::iterator> rend;

    while (rit != rend)
    {
        std::cout << rit->str();
        std::cout << std::endl;
        ++rit;
    }
    /*
      输出为：
      sub    123
      subject
      submarine
      subsequence
  */

}



void test1_cpp11_2_array()
{
    // 增加容器—静态数组array、forward_list以及unordered系列
    // array 是一个类似vector的容器，但是是保存在栈区的，因此性能更好，不能够隐式转换为指针
    //   编译时创建固定大小数组，只需要指定类型和大小即可
    std::array<int, 5>  arr = { 1, 2, 3, 4, 5 }; // 长度必须是常量或者常量表达式
    int* parr = &arr[0];
    parr = arr.data();
    parr = nullptr; // 转换为指针的操作
    // forward_list<int> flist;
    //   区别于list双向链表的单向链表，空间利用率和速率都更高
    // 新增两组无序容器：
    // unordered_map
    // unordered_multimap
    // unordered_set
    // unordered_multiset
    // 不同于set和map内部通过红黑树实现，而是hash表实现
}

void test1_cpp11_2_tuple_pair()
{
    // 就像一个可以容纳不同类型的结构体
    std::tuple<int, double, std::string> tps(12, 17.58, "pixel");
    auto tp = std::make_tuple(5, 12.125, "hello");// 构造元组，类型推断为tuple<int,double,string>
    std::cout << std::get<2>(tp) << std::endl;    // 获取元素，无法使用变量下标    // hello
    int id;
    double bim;
    std::string item;
    std::tie(id, bim, item) = tp;                 // 元组拆包
    std::cout << id << " " << bim << " " << item << std::endl;         // 5 12.125 hello
    auto ntp = tuple_cat(tps, tp);                // 元组的连接
    auto p1 = std::make_pair(12, 'c');            // pair，一个两个成员的结构体
    std::pair<double, int> p2(12.125, 17);
    std::cout << p2.first << " " << p2.second << std::endl;            // 12.125 17
    p2 = std::make_pair(1, 1.2);
    p2 = p1;                                      // 一个含有成员函数的结构体
    //pair可以使用typedef进行简化声明


    // std::tie 将 tuple 解包为独立对象，或 能用于引入字典序比较到结构体。
    // std::tie 返回含左值引用的 std::tuple 对象。
    // std::tie 可用于解包 std::pair ，因为 std::tuple 拥有从 pair 的转换赋值
    // std::ignore 任何值均可赋给而无效果的未指定类型的对象。目的是令 std::tie 在解包 std::tuple 时作为不使用的参数的占位符使用。
    struct S {int n;std::string s;float d;
    bool operator<(const S& rhs) const {
        return std::tie(n, s, d) < std::tie(rhs.n, rhs.s, rhs.d);// 比较 n 与 rhs.n,然后为 s 与 rhs.s,然后为 d 与 rhs.d
    }
    };
    S value{42, "Test", 3.14};
    std::set<S> set_of_s;  // S 为可比较小于 (LessThanComparable)
    std::set<S>::iterator iter;
    bool inserted;
    std::tie(iter, inserted) = set_of_s.insert(value);  // 解包 insert 的返回值为 iter 与 inserted
    if (inserted) std::cout << "Value was inserted successfully\n";  // Value was inserted successfully
    std::set<std::string> set_of_str;
    inserted = false;
    std::tie(std::ignore, inserted) = set_of_str.insert("Test");
    if (inserted) std::cout << "Value was inserted successfully\n";  // Value was inserted successfully
}



#include <cstring>
#include <cassert>
void test1_cpp11_2_data()
{
    // 1 std:data
    // https://en.cppreference.com/w/cpp/iterator/data
    // 参数   含有data()的容器 或 an array of arbitrary type 或 an initializer list
    // 返回值 一段内存   Returns c.data(). Returns array. Returns il.begin().
    // 如下4个版本 C++17
    // template<class C>  constexpr auto data(C& c) -> decltype(c.data()){return c.data();}
    // template<class C>  constexpr auto data(const C& c) -> decltype(c.data()){return c.data();}
    // template<class T, std::size_t N> constexpr T* data(T (&array)[N]) noexcept {return array;}
    // template<class E> constexpr const E* data(std::initializer_list<E> il) noexcept {return il.begin();}
    {
    std::string s{"Hello world!\n"};
    char a[20]; // storage for a C-style string
    std::strcpy(a, std::data(s));  // #include <cstring>
//  [s.data(), s.data() + s.size()] is guaranteed to be an NTBS since C++11
    std::cout << a;  // Hello world!
    }
}

void test1_cpp11_2_size()
{
    // 2 std::size
    // https://en.cppreference.com/w/cpp/iterator/size
    // 参数   含有size()的容器 或 an array of arbitrary type
    // 返回值 Returns c.size() 或 Returns N.
    // 如下4个版本 C++17 C++20
    // template<class C> constexpr auto size(const C& c) -> decltype(c.size()){return c.size();}
    // template<class C> constexpr auto ssize(const C& c) -> std::common_type_t<std::ptrdiff_t,std::make_signed_t<decltype(c.size())>>
    //  { using R = std::common_type_t<std::ptrdiff_t,std::make_signed_t<decltype(c.size())>>;return static_cast<R>(c.size());}
    // template<class T, std::size_t N> constexpr std::size_t size(const T (&array)[N]) noexcept {return N;}
    // template<class T, std::ptrdiff_t N> constexpr std::ptrdiff_t ssize(const T (&array)[N]) noexcept {return N;}

    {
    // Works with containers
    std::vector<int> v{3, 1, 4};
    assert(std::size(v) == 3); // #include <cassert>

    // And works with built-in arrays too
    int a[]{-5, 10, 15};
    // Returns the number of elements (not bytes) as opposed to sizeof
    assert(std::size(a) == 3);
    std::cout << "size of a[]: " << sizeof a << '\n'; // 12, if sizeof(int) == 4

    // Provides a safe way (compared to sizeof) of getting string buffer size
    const char str[] = "12345";
    // These are fine and give the correct result
    assert(std::size(str) == 6);
    assert(sizeof(str) == 6);

    // But use of sizeof here is a common source of bugs
    const char* str_decayed = "12345";
    // std::cout << std::size(str_decayed) << '\n'; // Usefully fails to compile
    std::cout << sizeof(str_decayed) << '\n'; // 8   Prints the size of the pointer!

    // Since C++20 the signed size (std::ssize) is available
    // auto i = std::ssize(v);
    // for (--i; i != -1; --i)
    //     std::cout << v[i] << (i ? ' ' : '\n');
    // assert(i == -1);
    }
}

void isnull(void *c){std::cout << "void*c" << std::endl;}
void isnull(int n){  std::cout << "int n" << std::endl;}
void test1_cpp11_2_null_ptr()
{
    // std::nullptr
    // 三种方法来获取一个 空指针
    int *pa1 = NULL; // 需要引入cstdlib头文件
    int *pa2 = 0;
    int *pa3 = nullptr;

    // #define NULL ((void *)0)  在C中的定义 实质上是一个void *指针
    // #define NULL 0            在C++中的定义 被明确定义为整数0  之所以不同于C，根本原因和C++的函数重载机制有关。
    // void Func(char *);
    // void Func(int);
    // Func(NULL);               如果C++让NULL也支持void *的隐式类型转换，这样编译器就不知道应该调用哪一个函数。
    // 但是又引入了另一个问题 从程员的角度，Func(NULL)应该调用的是Func(char *)但实际上NULL的值是0，所以调用了Func(int)。
    // nullptr关键字真是为了解决这个问题而引入的，是std::nullptr_t类型的(constexpr)变量。
    // 它可以转换成任何指针类型和bool布尔类型，主要是为了兼容普通指针可以作为条件判断语句的写法，但是不能被转换为整数。
    char *pb1 = nullptr;  // 正确   编译器分别将 nullptr 隐式转换成 char*
    int  *pb2 = nullptr;  // 正确   编译器分别将 nullptr 隐式转换成 int*
    // bool b = nullptr;  // converting to ‘bool’ from ‘std::nullptr_t’ requires direct-initialization [-fpermissive]
    if(nullptr) ;     // 正确
    // int a = nullptr;     // error   cannot convert ‘std::nullptr_t’ to ‘int’

    // isnull(NULL);    // int n     //  error: call of overloaded ‘isnull(NULL)’ is ambiguous
    isnull(nullptr); // void*c
}



