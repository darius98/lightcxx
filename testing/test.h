#ifndef _LIGHTCXX_GUARD_TESTING_TEST_H
#define _LIGHTCXX_GUARD_TESTING_TEST_H

#include "testing/meta.h"

namespace Testing {

void expect(bool condition, const char* message = "") noexcept;

#define STATIC_EXPECT(...)                                                                         \
    ::Testing::expect(__VA_ARGS__);                                                                \
    static_assert(__VA_ARGS__)

template<class T, class U>
constexpr void expectType(U&& val) noexcept {
    static_assert(IsSameType<T, decltype(val)>::value, "Invalid type.");
}

template<class T, class U, class V>
void expectTypeAndValue(U&& val, V&& expected, const char* message = "") noexcept {
    static_assert(IsSameType<T, decltype(val)>::value, "Invalid type.");
    expect(val == expected, message);
}

void run();

}  // namespace Testing

#endif