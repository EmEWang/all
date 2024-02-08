



构造函数模板推导
在C++17前构造一个模板类对象需要指明类型：
pair<int, double> p(1, 2.2); // before c++17
C++17就不需要特殊指定，直接可以推导出类型，代码如下：
pair p(1, 2.2); // c++17 自动推导
vector v = {1, 2, 3}; // c++17



结构化绑定 STRUCT BINDING
C++17引入的结构化绑定进一步简化了多值返回的代码。使用auto和结构化绑定，使得代码更加直观易懂。
auto divide(int dividend, int divisor) {
  struct result {
    int quotient;
    int remainder;
  };
  return result{dividend / divisor, dividend % divisor};
}
auto [quotient, remainder] = divide(14, 3);




nodiscard
c++17引入的一种标记符，其语法一般为[[nodiscard]]或[[nodiscard("string")]](c++20引入)，含义可以理解为“不应舍弃”。
nodiscard一般用于标记函数的返回值或者某个类，当使用某个弃值表达式而不是cast to void 来调用相关函数时，编译器会发出相关warning。

1 一个被nodiscard声明的函数被调用时，比如说：
[[nodiscard]] int func(){return 1;}; // C++17
[[nodiscard("nodiscard_func_1")]] int func_1(){return 2;};  // C++20

func(); // warning    ->   warning C4834: 放弃具有 "nodiscard" 属性的函数的返回值
func_1(); // warning  ->   warning C4858: 正在放弃返回值: nodiscard_func_1

保存函数返回值，或者使用cast to void
[[nodiscard]] int func(){return 1;}; // C++17
int a = func(); // no warning
static_cast<void>(func()); // no warning

2 一个函数返回一个enum或class(这个enum或class被nodiscard声明了)，该函数被调用时(或出现在其他函数的定义中)
struct [[nodiscard]] testStruct{};
class [[nodiscard]] testClass{};
enum class [[nodiscard]] testEnum{test1, test2};

testClass funcClass() {return {};}
testEnum funcEnum() {return testEnum::test1;}

void func()
{
  funcEnum(); // warning
}

funcClass(); //warning

3 值得注意的是，当函数返回class的引用或指针时，nodiscard无效
class [[nodiscard]] testClass{};
testClass& funcClassRef() {testClass A; return A;}
testClass* funcClassPtr() {testClass A; return &A;}

funcClassRef(); // no warning
funcClassPtr(); // no warning




https://github.com/MeouSker77/Cpp17/blob/master/markdown/src/ch29.md
https://c-cpp.com/cpp/memory/polymorphic_allocator
https://en.cppreference.com/w/cpp/memory/monotonic_buffer_resource
memory_resource 内存池  maketest/profilemalloc/pmr.cpp
memory_resource 是一个抽象基类，提供了三个纯虚函数，需要被子类实现：
do_allocate(size_t bytes, size_t alignment)：根据指定的字节和对齐方式分配内存。
do_deallocate(void* p, size_t bytes, size_t alignment)：释放之前分配的内存。
do_is_equal(const memory_resource& other) const noexcept：判断两个内存资源是否等效。

要使用 memory_resource，通常需要通过它来创建一些容器。例如，我们可以用 memory_resource 创建一个 std::pmr::vector：
MyMemoryResource myMemoryResource;
std::pmr::vector<int> vec(&myMemoryResource);
这样，vec 就会使用 myMemoryResource 来进行内存的分配和回收。

C++ 提供了两种内存资源：全局内存资源和本地内存资源。
全局内存资源是通过 std::pmr::get_default_resource() 获得的，所有没有指定内存资源的 std::pmr 对象都会使用它。
本地内存资源是创建 std::pmr 对象时指定的，它会覆盖全局内存资源。
std::pmr::vector<int> vec; // 使用全局内存资源
std::pmr::vector<int> vec(&myMemoryResource); // 使用本地内存资源

除了用户自定义的内存资源，C++ 还提供了几种预定义的内存资源：
std::pmr::new_delete_resource()：用 new 和 delete 进行内存分配和回收。
std::pmr::null_memory_resource()：任何尝试分配内存的操作都会抛出 std::bad_alloc 异常。
std::pmr::unsynchronized_pool_resource 和 std::pmr::synchronized_pool_resource：内存池资源，分别为线程不安全和线程安全版本。
std::pmr::synchronized_pool_resource 使用给定的内存池








aligned_alloc  <cstdlib>
https://www.apiref.com/cpp-zh/cpp/memory/c/aligned_alloc.html
void* aligned_alloc( std::size_t alignment, std::size_t size );
分配 size 字节的未初始化存储，由 alignment 指定其对齐。 size 参数必须是 alignment 的整数倍。
参数 alignment 指定对齐。必须是实现支持的合法对齐。 size 分配的字节数。 alignment 的整数倍。
返回值 成功时，返回指向新分配内存起始的指针。为避免内存泄漏，返回的指针必须由 std::free 或 std::realloc 解分配。
失败时，返回空指针。
