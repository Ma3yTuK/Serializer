#ifndef NULL_H
#define NULL_H

struct Null;

#include "Serializer/Types/BaseType.h"
#include <memory>

struct Null : BaseType
{
    virtual std::string toJsonString(int depth = 0) override;
    virtual bool operator==(const BaseType& other) const override;
    static std::shared_ptr<Null> fromJsonString(std::string string, int& index);
};

#endif // NULL_H
