#include "common.h"

template <typename TNum>
constexpr TNum fib(S64 x) {
    TNum f_m1 = 0;
    TNum f    = 1;
    if (x < 1) { return f_m1; }
    while (x-- >= 2) {
        const TNum t = f + f_m1;
        f_m1 = f;
        f    = t;
    }
    return f;
}
static_assert(fib<S32>(0)  == 0);
static_assert(fib<S32>(1)  == 1);
static_assert(fib<S32>(2)  == 1);
static_assert(fib<S32>(3)  == 2);
static_assert(fib<S32>(4)  == 3);
static_assert(fib<S32>(5)  == 5);
static_assert(fib<S32>(6)  == 8);
static_assert(fib<S32>(7)  == 13);
static_assert(fib<S64>(50) == 12586269025);

struct Foo {

    explicit Foo(int i) : m_i{i} {}
    
    bool operator==(const Foo& o) const { return m_i == o.m_i; }

    int i() const { return m_i; }

    struct Hash {
        size_t operator()(const Foo& foo) const { return foo.m_i; }
    };

private:

    int m_i;

};

int main() {
    HashSet<Foo, Foo::Hash> s;
    s.insert(Foo(2));
    s.insert(Foo(3));
    s.insert(Foo(1));
    s.insert(Foo(3));
    s.insert(Foo(2));
    s.insert(Foo(3));
    
    for (const auto& foo : s) {
        println(foo.i());
    }
}