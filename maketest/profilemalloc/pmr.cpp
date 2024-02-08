// pmr大概意思是“多态的内存资源
// https://blog.csdn.net/weixin_52665939/article/details/131602376
// https://www.cppstd17.com/code/lang/tracknew.hpp.html    tracknew.hpp

#include <malloc.h>
#include <chrono>
#include <string.h>
#include <vector>
#include <memory_resource>
#include <list>
#include <iostream>
#include <iomanip>
#include "tracknew.hpp"

using namespace std;
using namespace std::chrono;

int params(int argc, char**argv);
int isys = 0;
int ipmr = 0;
void testpmr();
void testpmr2();
void testpmr3();
void testpmr4();

int main(int argc, char**argv) {
    if(params(argc,argv) < 0)
        return 1;

    printf("--- pmr start ---\n");
    // ttpmr();
    // ttpmr2();
    // ttpmr3();
    // ttpmr4();
    printf("--- pmr end ---\n");
    return 0;
}
class timeuse{
public:
    chrono::time_point<steady_clock, chrono::nanoseconds> m_start;
    chrono::time_point<steady_clock, chrono::nanoseconds> m_end;

    timeuse(){m_start = steady_clock::now(); m_end = steady_clock::now();}
    void reset(){m_start = steady_clock::now();}
    void status(){
        m_end = steady_clock::now();
        //auto int_ms = duration_cast<chrono::milliseconds>(m_end - m_start);
        auto int_ms = duration_cast<chrono::microseconds>(m_end - m_start);
        printf("used time %fs\n", int_ms.count()/1000000.0);
    }
};
std::string addrrange(const void* addr, const void* start, size_t len){
    if(addr >= start && addr < ((const char*)start + len)) // pointer of type ‘void *’ used in arithmetic [-Wpointer-arith]
        return "in";
    return "out";
}
int params(int argc, char**argv){
    if (argc == 1)  return -1;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0) return -1;
        else if (strcmp(argv[i], "sys") == 0) isys = 1;
        else if (strcmp(argv[i], "pmr") == 0) ipmr = 1;
        else printf("incrrect params %s\n", argv[i]);
    }
    return 0;
}
class debug_resource : public std::pmr::memory_resource {
public:
    explicit debug_resource( std::pmr::memory_resource* up = std::pmr::get_default_resource() )
        : _upstream{ up } { }
    void* do_allocate(size_t bytes, size_t alignment) override {
        std::cout << "do_allocate(): bytes " << bytes << "alignment" << alignment << '\n';
        return _upstream->allocate(bytes, alignment);
    }
    void do_deallocate(void* ptr, size_t bytes, size_t alignment) override {
        std::cout << "do_deallocate(): bytes " << bytes << "alignment" << alignment << '\n';
        _upstream->deallocate(ptr, bytes, alignment);
    }
    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override {
        return this == &other;
    }

private:
    std::pmr::memory_resource* _upstream;
};
void testpmr() {
    // https://blog.csdn.net/audi2/article/details/118252089
    // stl容器的allocator无成员变量,即无状态 list<int>与list<int,my_allocator>是两个完全无关的类型 不能相互赋值
    // pmr容器用新分配器pmr::polymorphic_allocator,与stl分配器兼容;有一个数据成员memory_resource*,
    //  这个接口类定义了分配/回收内存的虚函数，即把内存请求/释放的功能分离出来到memory_resource的子类实现。
    {
    char buffer[32] = {};//开辟了一块位于栈上的32字节空间，
    std::fill_n(std::begin(buffer), std::size(buffer)-1, '_');//用横杠填入每个字符，除了最后一个保留'\0'
    std::cout << buffer << '\n';//_______________________________
    std::pmr::monotonic_buffer_resource pool{std::data(buffer), std::size(buffer)};//创建了一个“单增内存资源”的实例对象
      // pool有两个后盾 1是buffer数组 2是upstream 即另一个memory_resource对象，当buffer不够时，对内存的请求就会转向upstream
    std::pmr::vector<char> vec{&pool};//使用传入的指针。只有指针或者引用，才能实现多态。
    for (char ch='a'; ch <= 'z'; ++ch) vec.push_back(ch);
    std::cout << buffer << '\n';// aababcdabcdefghabcdefghijklmnop
    for (auto i : vec) std::cout << i << ' ';// a b c d e f g h i j k l m n o p q r s t u v w x y z
    std::cout << '\n';// 规律:a(1) ab(2) abcd(4) abcdefgh(8)  abcdefghijklmnop(16)  即vector扩容时，按2倍空间扩容。
    // 即 monotonic_buffer_resource 只申请不不释放
    // 那个q-z的数据哪里去了? 这就涉及到upstream，由它分配一块内存了。见下
    }
    {
    char buffer[32] = {};
    std::fill_n(std::begin(buffer), std::size(buffer)-1, '_');
    std::cout << buffer << '\n'; // _______________________________
    debug_resource dr;
    std::pmr::monotonic_buffer_resource pool{std::data(buffer), std::size(buffer), &dr};
    std::pmr::vector<char> vec{&pool};
    for (char ch='a'; ch <= 'z'; ++ch) vec.push_back(ch);
    std::cout << buffer << '\n';
// do_allocate(): bytes 64alignment16
// aababcdabcdefghabcdefghijklmnop
// do_deallocate(): bytes 64alignment16
    }
}
template <typename Func>
auto benchmark(Func test_func, int iterations) {
    const auto start = std::chrono::system_clock::now();
    while (iterations-- > 0) { test_func(); }
    const auto stop = std::chrono::system_clock::now();
    const auto secs = std::chrono::duration<double>(stop - start);
    return secs.count();
}
void testpmr2() {
    constexpr int iterations{100};
    constexpr int total_nodes{2'00'00};

    auto default_std_alloc = [total_nodes] {
        std::list<int> list;
        for (int i{}; i != total_nodes; ++i) { list.push_back(i); }
    };

    auto default_pmr_alloc = [total_nodes] {
        std::pmr::list<int> list;
        for (int i{}; i != total_nodes; ++i) { list.push_back(i); }
    };

    auto pmr_alloc_no_buf = [total_nodes] {
        std::pmr::monotonic_buffer_resource mbr;
        std::pmr::polymorphic_allocator<int> pa{&mbr};
        std::pmr::list<int> list{pa};
        for (int i{}; i != total_nodes; ++i) { list.push_back(i); }
    };

    auto pmr_alloc_and_buf = [total_nodes] {
        std::array<std::byte, total_nodes * 32 * 4> buffer; // enough to fit in all nodes
        std::pmr::monotonic_buffer_resource mbr{buffer.data(), buffer.size()};
        std::pmr::polymorphic_allocator<int> pa{&mbr};
        std::pmr::list<int> list{pa};
        for (int i{}; i != total_nodes; ++i) { list.push_back(i); }
    };

    auto pmr_alloc_and_buf2 = [total_nodes] {
        char buffer[total_nodes * 32 * 4]; // enough to fit in all nodes
        std::pmr::monotonic_buffer_resource mbr{buffer, sizeof(buffer)};
        std::pmr::polymorphic_allocator<int> pa{&mbr};
        std::pmr::list<int> list{pa};
        for (int i{}; i != total_nodes; ++i) { list.push_back(i); }
    };

    const double t1 = benchmark(default_std_alloc , iterations);
    const double t2 = benchmark(default_pmr_alloc , iterations);
    const double t3 = benchmark(pmr_alloc_no_buf  , iterations);
    const double t4 = benchmark(pmr_alloc_and_buf , iterations);
    const double t5 = benchmark(pmr_alloc_and_buf2, iterations);

    std::cout << std::fixed << std::setprecision(3)
        << "t1 (default std alloc ): " << t1 << " sec; t1/t1: " << t1/t1 << '\n'
        << "t2 (default pmr alloc ): " << t2 << " sec; t2/t1: " << t2/t1 << '\n'
        << "t3 (pmr alloc  no buf ): " << t3 << " sec; t3/t1: " << t3/t1 << '\n'
        << "t4 (pmr alloc and buf ): " << t4 << " sec; t4/t1: " << t4/t1 << '\n'
        << "t5 (pmr alloc and buf2): " << t5 << " sec; t5/t1: " << t5/t1 << '\n';
}
void testpmr3(){
    {
    int i =1;
    std::string str1("123");
    std::string str2("12345678901234");
    std::string str3("123456789012345");
    std::string str4("1234567890123456"); // string > 15 堆上分配内存
    std::vector<int> vcti;                // vector 堆上分配内存
    std::vector<std::string> vctstr;           // vector
    vcti.emplace_back(1);
    printf("i:%p str1 :%p  str2:%p str3 :%p str4 :%p\n", &i, str1.c_str(), str2.c_str(), str3.c_str(), str4.c_str());
    printf("i:%p &str1:%p &str2:%p &str3:%p &str4:%p\n", &i, &str1, &str2, &str3, &str4);
    printf("vcti:%p data():%p\n", &vcti, vcti.data());
// i:0x7ffd3689b848 str1 :0x7ffd3689b8c0  str2:0x7ffd3689b8e0 str3 :0x7ffd3689b900 str4 :0x55ce0b8932c0
// i:0x7ffd3689b848 &str1:0x7ffd3689b8b0 &str2:0x7ffd3689b8d0 &str3:0x7ffd3689b8f0 &str4:0x7ffd3689b910
// vcti:0x7ffd3689b850 data():0x55ce0b8932e0

    vctstr.emplace_back(str1);
    vctstr.emplace_back(str4);
    printf("vctstr[0] :%p vctstr[1] :%p\n", vctstr[0].c_str(), vctstr[1].c_str());
    printf("&vctstr[0]:%p &vctstr[1]:%p\n", &vctstr[0], &vctstr[1]);
// vctstr[0] :0x55ce0b893340 vctstr[1] :0x55ce0b893380
// &vctstr[0]:0x55ce0b893330 &vctstr[1]:0x55ce0b893350
    }

    {
    char arr[1000];
    std::pmr::monotonic_buffer_resource pool(arr, sizeof(arr));
    std::pmr::vector<std::string> vct1(&pool);
    std::string str1{"my string"};
    std::string str2{"my string with some value"};
    vct1.emplace_back(str1);
    vct1.emplace_back(str2);

    printf("arr:%p arr_end:%p\n", arr, arr + sizeof(arr));
    printf("1  &vct1:%p vct1[0]_d:%p [%s] vct1[1]_d:%p [%s]\n",
      &vct1, vct1[0].c_str(), addrrange(vct1[0].c_str(), arr, sizeof(arr)).c_str(),
             vct1[1].c_str(), addrrange(vct1[1].c_str(), arr, sizeof(arr)).c_str());
    printf("1  &vct1:%p  &vct1[0]:%p [%s]  &vct1[1]:%p [%s]\n",
      &vct1, &vct1[0], addrrange(&vct1[0], arr, sizeof(arr)).c_str(),
             &vct1[1], addrrange(&vct1[1], arr, sizeof(arr)).c_str());
// arr:0x7fff8179baf0 arr_end:0x7fff8179bed8
// 1  &vct1:0x7fff8179ba00 vct1[0]_d:0x7fff8179bb20 [in] vct1[1]_d:0x55626604e2f0 [out]
// 1  &vct1:0x7fff8179ba00  &vct1[0]:0x7fff8179bb10 [in]  &vct1[1]:0x7fff8179bb30 [in]
    }

    {
    char arr[5000];
    std::pmr::monotonic_buffer_resource pool(arr, sizeof(arr));
    std::pmr::vector<std::pmr::string> vct1(&pool);
    std::pmr::string str1{"my string"};
    std::pmr::string str2{"my string with some value"};
    vct1.emplace_back(str1);
    vct1.emplace_back(str2);

    printf("arr:%p arr_end:%p\n", arr, arr + sizeof(arr));
    printf("2  &vct1:%p vct1[0]_d:%p [%s] vct1[1]_d:%p [%s]\n",
      &vct1, vct1[0].c_str(), addrrange(vct1[0].c_str(), arr, sizeof(arr)).c_str(),
             vct1[1].c_str(), addrrange(vct1[1].c_str(), arr, sizeof(arr)).c_str());
    printf("2  &vct1:%p  &vct1[0]:%p [%s]  &vct1[1]:%p [%s]\n",
      &vct1, &vct1[0], addrrange(&vct1[0], arr, sizeof(arr)).c_str(),
             &vct1[1], addrrange(&vct1[1], arr, sizeof(arr)).c_str());
// arr:0x7ffd5a927970 arr_end:0x7ffd5a928cf8
// 2  &vct1:0x7ffd5a927870 vct1[0]_d:0x7ffd5a9279b0 [in] vct1[1]_d:0x7ffd5a9279e8 [in]
// 2  &vct1:0x7ffd5a927870  &vct1[0]:0x7ffd5a927998 [in]  &vct1[1]:0x7ffd5a9279c0 [in]
    }

    {
    std::string s{"my string with some value"};
    std::pmr::string ps{std::move(s), std::pmr::new_delete_resource()}; // 拷贝
    printf("str s:%p str ps:%p\n", s.c_str(), ps.c_str()); // str s:0x562ae241c3a0 str ps:0x562ae241c300
    }
}
void testpmr4(){
    int count = 10;
    int count2 = 50000;

    if(isys == 1) {
        printf("使用默认分配器\n");
        TrackNew::reset();
        timeuse tu;
        tu.reset();

        std::vector<std::string> coll;
        for (int i = 0; i < count; i++) {
            for (int i = 0; i < count2; ++i)
                coll.emplace_back("just a non-SSO string");
            coll.clear();
        }

        // for (int i = 0; i < 1; i++) {
        //     void * pp = malloc(100);
        //     free(pp);
        // }

        tu.status();
        TrackNew::status();
    }

    if(ipmr == 1){
        printf("使用内存分配器\n");
        TrackNew::reset();
        timeuse tu;
        tu.reset();

        std::array<std::byte, 8000000> buf;// 在栈上分配一些内存：
        // const static long numm = 2000000;
        // char cc[numm];
        std::pmr::monotonic_buffer_resource pool{buf.data(), buf.size()};// 将它用作vector的初始内存池：
        // std::pmr::unsynchronized_pool_resource pool;
        // std::pmr::monotonic_buffer_resource pool{cc, numm};
        std::pmr::vector<std::string> coll{&pool};
        // std::pmr::vector<std::pmr::string> coll{&pool};

        for (int i = 0; i < count; i++) {
            for (int i = 0; i < count2; ++i)
                coll.emplace_back("just a non-SSO string");
            static const char* pp = 0;
            printf("count %d coll[0] %p step %ld start %p  end %p %s\n",
            i, coll[0].c_str(), coll[0].c_str() - pp, buf.data(), buf.data() + buf.size(),
            (coll[0].c_str()>=(char*)(buf.data()) && coll[0].c_str()<=(char*)(buf.data() + buf.size()) ? "in":"out"));
            pp = coll[0].c_str();
            coll.clear();
        }

        tu.status();
        TrackNew::status();
    }

    {
        printf("比较\n");
        TrackNew::reset();
        timeuse tu;
        tu.reset();
        {
            pmr::monotonic_buffer_resource res(100000);
            // pmr::vector<vector<int>> vec1(&res);
            pmr::vector<pmr::vector<int>> vec2(&res);
            pmr::vector<int> vec1(&res);
            for (size_t i = 0; i < count; i++) {
                for (int i = 0; i < count2; ++i) {
                    vec1.push_back(123);
                }
                vec1.clear();
            }
        }
        tu.status();          // used time 0.021493s
        TrackNew::status();   // 3 allocations for 917504 bytes

        TrackNew::reset();
        tu.reset();
        {
            vector<int> vec1;
            for (size_t i = 0; i < count; i++) {
                for (int i = 0; i < count2; ++i) {
                    vec1.push_back(123);
                }
                vec1.clear();
            }
        }
        tu.status();          // used time 0.013153s
        TrackNew::status();   // 17 allocations for 524284 bytes
    }
}


