// EXPECT:EXIT KILLED BY SIGNAL SIGABRT
// EXPECT:STEPS "aligned_alloc;new_handler"

#include <new>

#include "testing/test.h"
#include <stdlib.h>

void Testing::run() {
    libc.aligned_alloc.replace([](std::size_t align, std::size_t size) -> void* {
        step("aligned_alloc");
        return nullptr;
    });
    std::set_new_handler([]() {
        step("new_handler");
        ::abort();
    });

    [[maybe_unused]] const auto const_ptr = ::operator new[](256, std::align_val_t{128});
    fail("did not abort");
}