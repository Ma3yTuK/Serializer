#include "Serializer/Types/Object.h"
#include "Serializer/Types/String.h"
#include "Serializer/CONSTANTS.h"

std::shared_ptr<Object> Object::fromJsonString(std::string string, int& index)
{
    std::shared_ptr<Object> result(new Object);
    index = string.find_first_not_of(BLANK, index + 1);
    while (string.substr(index, JSON_OBJECT_CLOSE.size()) != JSON_OBJECT_CLOSE)
    {
        std::shared_ptr<BaseType> key(BaseType::fromJsonString(string, index));
        index = string.find(JSON_OBJECT_SEPARATOR, index);
        index = string.find_first_not_of(BLANK, index + JSON_OBJECT_SEPARATOR.size());
        result->values[std::static_pointer_cast<String>(key)->value] = BaseType::fromJsonString(string, index);
        index = string.find_first_not_of(std::string(BLANK).append(COMMA), index);
    }
    index++;
    return result;
}

std::string Object::toJsonString(int depth)
{
    std::string result(JSON_OBJECT_OPEN);
    for (auto& i : values)
    {
        result.append(NEW_LINE);
        for (int i = 0; i <= depth; i++)
            result.append(JSON_SEP);
        std::shared_ptr<String> first(new String);
        first->value = i.first;
        result.append(first->toJsonString(depth + 1)).append(JSON_OBJECT_SEPARATOR).append(i.second->toJsonString(depth + 1));
        result.append(COMMA);
    }
    if (result.substr(result.size()-COMMA.size()) == COMMA)
        result.erase(result.size()-COMMA.size());
    for (int i = 0; i < depth; i++)
        result.append(JSON_SEP);
    return result.append(JSON_OBJECT_CLOSE);
}

bool Object::operator==(const BaseType& other) const
{
    const Object* otherCast = dynamic_cast<const Object*>(&other);
    if (!otherCast)
        return false;
    if (values.size() != otherCast->values.size())
        return false;
    for (auto i = values.begin(), j = otherCast->values.begin(); i != values.end(); i++, j++)
        if (i->first != j->first || *(i->second) != *(j->second))
            return false;
    return true;
}
