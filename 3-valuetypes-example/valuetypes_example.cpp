#include <emscripten/bind.h>
using namespace emscripten;

struct Point2f {
    float x;
    float y;
};

struct PersonRecord {
    std::string name;
    int age;
};

PersonRecord findPersonAtLocation(Point2f);

EMSCRIPTEN_BINDINGS(my_value_example) {
    value_array<Point2f>("Point2f")
        .element(&Point2f::x)
        .element(&Point2f::y)
        ;

    value_object<PersonRecord>("PersonRecord")
        .field("name", &PersonRecord::name)
        .field("age", &PersonRecord::age)
        ;
    function("findPersonAtLocation", &findPersonAtLocation);
}


