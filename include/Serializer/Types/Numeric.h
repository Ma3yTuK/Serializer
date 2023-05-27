#ifndef NUMERIC_H
#define NUMERIC_H

struct Numeric;

#include "Serializer/Types/BaseType.h"
#include <memory>

struct Numeric : BaseType
{
    double value;
    virtual std::string toJsonString(int depth = 0) override;
    virtual bool operator==(const BaseType& other) const override;
    static std::shared_ptr<Numeric> fromJsonString(std::string string, int& index);
};

#endif // NUMERIC_H
