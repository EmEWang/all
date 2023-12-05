



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



