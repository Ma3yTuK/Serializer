#ifndef STRING_H
#define STRING_H

struct String;

#include "Serializer/Types/BaseType.h"
#include <memory>
#include <string>

struct String : BaseType
{
    std::string value;
    virtual std::string toJsonString(int depth = 0) override;
    virtual bool operator==(const BaseType& other) const override;
    static std::shared_ptr<String> fromJsonString(std::string string, int& index);
};

#endif // STRING_H
