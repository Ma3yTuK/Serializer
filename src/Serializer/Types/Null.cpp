#include "Serializer/Types/Null.h"
#include "Serializer/CONSTANTS.h"

std::shared_ptr<Null> Null::fromJsonString(std::string string, int& index)
{
    index += JSON_NULL.size();
    return std::shared_ptr<Null>(new Null);
}

std::string Null::toJsonString(int depth)
{
    return JSON_NULL;
}

bool Null::operator==(const BaseType& other) const
{
    return dynamic_cast<const Null*>(&other);
}
