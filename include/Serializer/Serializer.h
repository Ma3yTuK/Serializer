#ifndef JSONSERIALIZER_H
#define JSONSERIALIZER_H

#include "Serializer/Property.h"
#include "Serializer/Types/BaseType.h"
#include "Serializer/Types/Array.h"
#include "Serializer/Types/Boolean.h"
#include "Serializer/Types/Numeric.h"
#include "Serializer/Types/Object.h"
#include "Serializer/Types/String.h"
#include <string>
#include <memory>

std::string jsonToString(std::shared_ptr<BaseType>)
{

}

#endif // JSONSERIALIZER_H
