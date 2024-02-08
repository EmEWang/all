// test.cpp
// g++ test.cpp -o test -lprofiler
#include <iostream>

constexpr uint64_t kLoopCount = 200000000;

void FuncA() {
  uint64_t add_num = 0;
  for (int i = 0; i < kLoopCount; ++i) {
    add_num += 1;
  }
}

void FuncB() {
  uint64_t res = 0;
  for (int i = 0; i < kLoopCount; ++i) {
    if (i % 2 == 0) {
      res += 2;
    } else {
      res -= 1;
    }
  }
}
void FuncC() {
    FuncA();
}
void FuncD() {
    FuncC();
}

int main() {
  FuncA();
  FuncB();
  FuncD();

  return 0;
}