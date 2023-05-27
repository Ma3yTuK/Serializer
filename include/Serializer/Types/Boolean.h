#ifndef BOOLEAN_H
#define BOOLEAN_H

struct Boolean;

#include "Serializer/Types/BaseType.h"
#include <memory>

struct Boolean : BaseType
{
    bool value;
    virtual std::string toJsonString(int depth = 0) override;
    virtual bool operator==(const BaseType& other) const override;
    static std::shared_ptr<Boolean> fromJsonString(std::string string, int& index);
};

#endif // BOOLEAN_H
