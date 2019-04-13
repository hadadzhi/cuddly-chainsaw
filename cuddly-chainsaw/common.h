#ifndef CC_COMMON_H
#define CC_COMMON_H

#include <climits>
#include <cstdint>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <vector>
#include <list>
#include <iostream>
#include <utility>
#include <chrono>

static_assert(CHAR_BIT == 8);

using S8  = int8_t;
using S16 = int16_t;
using S32 = int32_t;
using S64 = int64_t;

using S8F  = int_fast8_t;
using S16F = int_fast16_t;
using S32F = int_fast32_t;
using S64F = int_fast64_t;

using U8  = uint8_t;
using U16 = uint16_t;
using U32 = uint32_t;
using U64 = uint64_t;

using U8F  = uint_fast8_t;
using U16F = uint_fast16_t;
using U32F = uint_fast32_t;
using U64F = uint_fast64_t;

using SP = float;
using DP = double;
using EP = long double;

// ascii char[]
using Str = ::std::string;

template <typename... P> using SortedMap = ::std::map<P...>;
template <typename... P> using SortedSet = ::std::set<P...>;
template <typename... P> using HashMap   = ::std::unordered_map<P...>;
template <typename... P> using HashSet   = ::std::unordered_set<P...>;
template <typename... P> using Vector    = ::std::vector<P...>;
template <typename... P> using List      = ::std::list<P...>;

template <typename T>
void println(const T& t) { ::std::cout << t << "\n"; }

// Prints arguments side-by-side, followed by endline
template <typename Head, typename... Tail>
void println(const Head& arg1, const Tail& ... args) {
    ::std::cout << arg1;
    println(args...);
}

// flushes output
void println() { ::std::cout << std::endl; }

// Times an action
// Action is a no-arg callable (return value is ignored)
// Returns nanoseconds
template<typename Action>
S64 time(const Action& action) {
    auto start = std::chrono::high_resolution_clock::now();

    action();

    auto end = std::chrono::high_resolution_clock::now();

    return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
}

// constexpr swap not standard until C++20
template <typename T>
constexpr
void swap(T& a, T& b) noexcept {
    T t = std::move(a);
    a = std::move(b);
    b = std::move(t);
}

#endif // CC_COMMON_H