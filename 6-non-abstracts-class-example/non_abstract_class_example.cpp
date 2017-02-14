#include <emscripten/bind.h>
using namespace emscripten;

struct Base {
    virtual void invoke(const std::string& str) {
        // default implementation
    }
};

struct BaseWrapper : public wrapper<Base> {
    EMSCRIPTEN_WRAPPER(BaseWrapper);
    void invoke(const std::string& str) {
        return call<void>("invoke", str);
    }
};

EMSCRIPTEN_BINDINGS(interface) {
    class_<Base>("Base")
        .allow_subclass<BaseWrapper>("BaseWrapper")
        .function("invoke", optional_override([](Base& self, const std::string& str) {
            return self.Base::invoke(str);
        }))
        ;
}
