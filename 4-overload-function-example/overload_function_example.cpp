#include <emscripten/bind.h>
using namespace emscripten;

struct HasOverloadedMethods {
    void foo();
    void foo(int i);
    void foo(float f) const;
};

EMSCRIPTEN_BINDINGS(overloads) {
    class_<HasOverloadedMethods>("HasOverloadedMethods")
        .function("foo", select_overload<void()>(&HasOverloadedMethods::foo))
        .function("foo_int", select_overload<void(int)>(&HasOverloadedMethods::foo))
        .function("foo_float", select_overload<void(float)const>(&HasOverloadedMethods::foo))
        ;
}

