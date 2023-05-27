#ifndef ARRAY_H
#define ARRAY_H

struct Array;

#include "Serializer/Types/BaseType.h"
#include <memory>
#include <vector>

struct Array : BaseType
{
    std::vector<std::shared_ptr<BaseType>> values;
    virtual std::string toJsonString(int depth = 0) override;
    virtual bool operator==(const BaseType& other) const override;
    static std::shared_ptr<Array> fromJsonString(std::string string, int& index);
};

#endif // ARRAY_H
