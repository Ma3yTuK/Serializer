#ifndef OBJECT_H
#define OBJECT_H

struct Object;

#include "Serializer/Types/BaseType.h"
#include <memory>
#include <map>

struct Object : BaseType
{
    std::map<std::string, std::shared_ptr<BaseType>> values;
    virtual std::string toJsonString(int depth = 0) override;
    virtual bool operator==(const BaseType& other) const override;
    static std::shared_ptr<Object> fromJsonString(std::string string, int& index);
};

#endif // OBJECT_H
