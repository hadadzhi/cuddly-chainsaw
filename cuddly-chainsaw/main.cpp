#include <boost/multiprecision/cpp_int.hpp>

#include "common.h"

template <typename TNum>
constexpr
TNum fib(S64 x) {
    TNum f_m1 = 0;
    TNum f    = 1;
    if (x < 1) { return f_m1; }
    while (x-- >= 2) {
        //const TNum t = f + f_m1;
        //f_m1 = std::move(f);
        //f    = std::move(t);
        // swap and += is much faster for boost::multiprecision::cpp_int
        swap(f_m1, f);
        f += f_m1;
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

void frobnicate() {
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

template <typename TFunc, typename TArg>
constexpr
TArg iterate(TFunc&& f, TArg&& x0, U64 n, bool print = false) {
    if (print) {
        println(x0);
    }
    if (n > 0) {
        return iterate(f, f(std::forward<TArg>(x0)), n - 1, print);
    }
    return x0;
}

using cpp_int = boost::multiprecision::cpp_int;

void TestFibonacci() {
    S64 ns = time([&]() {
        const cpp_int f = fib<cpp_int>(1'000'000);
        println(f); // boost cheats with template expressions, so must time the output too, to force evaluation
    });

    println(ns / 1'000'000, " ms");
}

void TestIterate() {
    S64 ns = time([]() {
        iterate(
            [](const cpp_int& x) { return 2*x + 1; },
            cpp_int(0),
            1000,
            true
        );
    });

    println(ns / 1'000'000, " ms");
}

int main() {
    //TestFibonacci();
    TestIterate();
}
