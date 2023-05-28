#include "Serializer/Types/Array.h"
#include "Serializer/CONSTANTS.h"

std::shared_ptr<Array> Array::fromJsonString(std::string string, int& index)
{
    std::shared_ptr<Array> result(new Array);
    index = string.find_first_not_of(BLANK, index + 1);
    while (string.substr(index, JSON_ARRAY_CLOSE.size()) != JSON_ARRAY_CLOSE)
    {
        result->values.push_back(BaseType::fromJsonString(string, index));
        index = string.find_first_not_of(std::string(BLANK).append(COMMA), index);
    }
    index++;
    return result;
}

std::string Array::toJsonString(int depth)
{
    std::string result(JSON_ARRAY_OPEN);
    result.append(NEW_LINE);
    for (auto& i : values)
    {
        for (int i = 0; i <= depth; i++)
            result.append(JSON_SEP);
        result.append(i->toJsonString(depth + 1));
        result.append(COMMA).append(NEW_LINE);
    }
    for (int i = 0; i < depth; i++)
        result.append(JSON_SEP);
    return result.append(JSON_ARRAY_CLOSE);
}

bool Array::operator==(const BaseType& other) const
{
    const Array* otherCast = dynamic_cast<const Array*>(&other);
    if (!otherCast)
        return false;
    if (values.size() != otherCast->values.size())
        return false;
    for (auto i = values.begin(), j = otherCast->values.begin(); i != values.end(); i++, j++)
        if (**i != **j)
            return false;
    return true;
}
