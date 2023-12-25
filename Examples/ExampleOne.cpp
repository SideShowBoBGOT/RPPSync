#include <RwLock/TRwLock.hpp>
#include <iostream>

struct A;

using PA = rwl::TRwLock<A>;

struct A {
    public:
	A(const int b) {}
    void ConstFunc() const { std::cout << "Const A" << std::endl; }
    void Func() { std::cout << "A" << std::endl; }
};

int main() {
    auto rw = rwl::TRwLock<A>(12);
    rw.Read()->ConstFunc();
    rw.Write()->Func();
    rw.TryRead().value()->ConstFunc();
    rw.TryWrite().value()->Func();
}