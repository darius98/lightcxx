// EXPECT:STEPS "new"

#include <new>

#include "testing.h"

void* operator new[](std::size_t, std::align_val_t) {
    Testing::step("new");
    throw std::bad_alloc();
}

TEST() {
    std::set_new_handler([]() {
        fail();
        ::abort();
    });

    const auto const_ptr = ::operator new[](256, std::align_val_t{128}, std::nothrow);
    expect(const_ptr == nullptr);
}