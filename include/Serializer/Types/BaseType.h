#ifndef JSONBASE_H
#define JSONBASE_H

class BaseType;

#include <string>
#include <memory>

struct BaseType
{
    virtual std::string toJsonString(int depth = 0) = 0;
    virtual bool operator==(const BaseType& other) const = 0;
    bool operator!=(const BaseType& other) const { return !(*this == other); }
    static std::shared_ptr<BaseType> fromJsonString(std::string string, int& index);
};

#endif // JSONBASE_H
