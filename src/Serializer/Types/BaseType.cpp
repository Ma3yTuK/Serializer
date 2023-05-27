#include "Serializer/CONSTANTS.h"
#include "Serializer/Types/BaseType.h"
#include "Serializer/Types/Array.h"
#include "Serializer/Types/Boolean.h"
#include "Serializer/Types/Null.h"
#include "Serializer/Types/Numeric.h"
#include "Serializer/Types/Object.h"
#include "Serializer/Types/String.h"

std::shared_ptr<BaseType> BaseType::fromJsonString(std::string string, int& index)
{
    index = string.find_first_not_of(BLANK, index);
    if (string.substr(index, JSON_ARRAY_OPEN.size()) == JSON_ARRAY_OPEN)
        return Array::fromJsonString(string, index);
    if (string.substr(index, JSON_OBJECT_OPEN.size()) == JSON_OBJECT_OPEN)
        return Object::fromJsonString(string, index);
    if (string.substr(index, JSON_STRING_OPEN.size()) == JSON_STRING_OPEN)
        return String::fromJsonString(string, index);
    if (string.substr(index, JSON_NULL.size()) == JSON_NULL)
        return Null::fromJsonString(string, index);
    if (string.substr(index, JSON_BOOLEAN_TRUE.size()) == JSON_BOOLEAN_TRUE)
        return Boolean::fromJsonString(string, index);
    if (string.substr(index, JSON_BOOLEAN_FALSE.size()) == JSON_BOOLEAN_FALSE)
        return Boolean::fromJsonString(string, index);
    return Numeric::fromJsonString(string, index);
}
