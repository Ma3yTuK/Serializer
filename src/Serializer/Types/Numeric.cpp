#include "Serializer/Types/Numeric.h"
#include "Serializer/CONSTANTS.h"

static const double MAX_NUMBER_SIZE = 100;

std::shared_ptr<Numeric> Numeric::fromJsonString(std::string string, int& index)
{
    std::shared_ptr<Numeric> result(new Numeric);
    size_t numSize;
    result->value = std::stod(string.substr(index, MAX_NUMBER_SIZE), &numSize);
    index += numSize;
    return result;
}

std::string Numeric::toJsonString(int depth)
{
    return std::to_string(value);
}

bool Numeric::operator==(const BaseType& other) const
{
    const Numeric* otherCast = dynamic_cast<const Numeric*>(&other);
    if (!otherCast)
        return false;
    return value == otherCast->value;
}
