#include <RwLock/TRwLock.hpp>
#include <iostream>

struct A;

using PA = rwl::TRwLock<A>;

struct A {
    public:
    void ConstFunc() const { std::cout << "Const A" << std::endl; }
    void Func() { std::cout << "A" << std::endl; }
};

int main() {
    auto rw = rwl::TRwLock<A>();
    rw.Read()->ConstFunc();
    rw.Write()->Func();
    rw.TryRead().value()->ConstFunc();
    rw.TryWrite().value()->Func();
}