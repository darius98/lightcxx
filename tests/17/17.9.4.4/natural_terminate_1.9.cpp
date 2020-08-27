// EXPECT:STEPS "before_ctor;after_ctor;terminate"
// EXPECT:EXIT KILLED BY SIGNAL SIGABRT

// This is based on clause [except.terminate], situation 1.9 from the note.

#include <exception>

#include "testing/test.h"

void Testing::run() {
    std::set_terminate([]() {
      Testing::step("terminate");
      ::abort();
    });

    step("before_ctor");
    std::nested_exception exc;
    step("after_ctor");
    exc.rethrow_nested();
}