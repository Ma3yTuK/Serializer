#include "Serializer/Types/Boolean.h"
#include "Serializer/CONSTANTS.h"

std::shared_ptr<Boolean> Boolean::fromJsonString(std::string string, int& index)
{
    std::shared_ptr<Boolean> result(new Boolean);
    if (string.substr(index, JSON_BOOLEAN_TRUE.size()) == JSON_BOOLEAN_TRUE)
    {
        result->value = true;
        index += JSON_BOOLEAN_TRUE.size();
    }
    else
    {
        result->value = false;
        index += JSON_BOOLEAN_FALSE.size();
    }
    return result;
}

std::string Boolean::toJsonString(int depth)
{
    if (value)
        return JSON_BOOLEAN_TRUE;
    else
        return JSON_BOOLEAN_FALSE;
}

bool Boolean::operator==(const BaseType& other) const
{
    const Boolean* otherCast = dynamic_cast<const Boolean*>(&other);
    if (!otherCast)
        return false;
    return value == otherCast->value;
}
