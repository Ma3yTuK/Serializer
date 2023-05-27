#include "Serializer/Types/String.h"
#include "Serializer/CONSTANTS.h"

std::shared_ptr<String> String::fromJsonString(std::string string, int& index)
{
    std::shared_ptr<String> result(new String);
    int stringStart = index + 1;
    index = string.find(JSON_STRING_CLOSE, index) + 1;
    result->value = string.substr(stringStart, index - stringStart - 1);
    return result;
}

std::string String::toJsonString(int depth)
{
    return std::string(JSON_STRING_OPEN).append(value).append(JSON_STRING_CLOSE);
}

bool String::operator==(const BaseType& other) const
{
    const String* otherCast = dynamic_cast<const String*>(&other);
    if (!otherCast)
        return false;
    return value == otherCast->value;
}
