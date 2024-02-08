
https://segmentfault.com/a/1190000023441427  # C++14新特性



[[deprecated]]标记
C++14中增加了deprecated标记，修饰类、变、函数等，当程序中使用到了被其修饰的代码时，
编译时被产生警告，用户提示开发者该标记修饰的内容将来可能会被丢弃，尽量不要使用。
struct [[deprecated]] A { };
A a;
当编译时，会出现如下警告：
~/test$ g++ test.cc -std=c++14
test.cc: In function ‘int main()’:
test.cc:11:7: warning: ‘A’ is deprecated [-Wdeprecated-declarations]
     A a;
       ^
test.cc:6:23: note: declared here
 struct [[deprecated]] A {


二进制字面量与整形字面量分隔符
C++14引入了二进制字面量，也引入了分隔符
int a = 0b0001'0011'1010;
double b = 3.14'1234'1234'1234;


std::make_unique
我们都知道C++11中有std::make_shared，却没有std::make_unique，在C++14已经改善。
struct A {};
std::unique_ptr<A> ptr = std::make_unique<A>();


std::shared_timed_mutex与std::shared_lock
C++14通过std::shared_timed_mutex和std::shared_lock来实现读写锁，保证多个线程可以同时读，
但是写线程必须独立运行，写操作不可以同时和读操作一起进行。
struct ThreadSafe {
    mutable std::shared_timed_mutex mutex_;
    int value_;

    ThreadSafe() {
        value_ = 0;
    }

    int get() const {
        std::shared_lock<std::shared_timed_mutex> loc(mutex_);
        return value_;
    }

    void increase() {
        std::unique_lock<std::shared_timed_mutex> lock(mutex_);
        value_ += 1;
    }
};


std::integer_sequence
template<typename T, T... ints>
void print_sequence(std::integer_sequence<T, ints...> int_seq)
{
    std::cout << "The sequence of size " << int_seq.size() << ": ";
    ((std::cout << ints << ' '), ...);
    std::cout << '\n';
}

int main() {
    print_sequence(std::integer_sequence<int, 9, 2, 5, 1, 9, 1, 6>{});
    return 0;
}
输出：7 9 2 5 1 9 1 6

std::integer_sequence和std::tuple的配合使用
template <std::size_t... Is, typename F, typename T>
auto map_filter_tuple(F f, T& t) {
    return std::make_tuple(f(std::get<Is>(t))...);
}

template <std::size_t... Is, typename F, typename T>
auto map_filter_tuple(std::index_sequence<Is...>, F f, T& t) {
    return std::make_tuple(f(std::get<Is>(t))...);
}

template <typename S, typename F, typename T>
auto map_filter_tuple(F&& f, T& t) {
    return map_filter_tuple(S{}, std::forward<F>(f), t);
}


std::exchange
int main() {
    std::vector<int> v;
    std::exchange(v, {1,2,3,4});
    cout << v.size() << endl;
    for (int a : v) {
        cout << a << " ";
    }
    return 0;
}

和std::swap区别
template<class T, class U = T>
constexpr T exchange(T& obj, U&& new_value) {
    T old_value = std::move(obj);
    obj = std::forward<U>(new_value);
    return old_value;
}
可以看见new_value的值给了obj，而没有对new_value赋值


std::quoted
C++14引入std::quoted用于给字符串添加双引号
int main() {
    string str = "hello world";
    cout << str << endl;
    cout << std::quoted(str) << endl;
    return 0;
}
~/test$ g++ test.cc -std=c++14
~/test$ ./a.out
hello world
"hello world"


