#include "Serializer/Serializer.h"
#include <iostream>

struct ab{
    bool a = true;
    double b = 23;
    std::string c = "some";
    std::vector<int> d{1, 2, 3};

    PROPERTIES(
        PROPERTY(ab, c),
        PROPERTY(ab, b),
        PROPERTY(ab, c),
        PROPERTY(ab, d)
    );
};

struct b{
    ab a;
    std::vector<int> b{1, 2};

    PROPERTIES(
        PROPERTY(b, a),
        PROPERTY(b, b)
    );
};

int main()
{
    b obj;
    std::string str = Serializer<b>::serialize(obj)->toJsonString();
    int tmp = 0;
    b obj1 = Serializer<b>::deserialize(BaseType::fromJsonString(str, tmp));
    std::cout << Serializer<b>::serialize(obj1)->toJsonString();
}
