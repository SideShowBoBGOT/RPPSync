#include <RwLock/TRwLock.hpp>
#include <iostream>

struct A {
    public:
    void func() const { std::cout << "A" << std::endl; }
};

int main() {
    auto rw = rwl::TRwLock<A>();
    rw.Read()->func();
    rw.Write()->func();
    rw.TryRead().value()->func();
    rw.TryWrite().value()->func();
}