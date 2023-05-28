#ifndef DESERIALIZE_H
#define DESERIALIZE_H

#include "Serializer/Property.h"
#include "Serializer/Types/BaseType.h"
#include "Serializer/Types/Array.h"
#include "Serializer/Types/Boolean.h"
#include "Serializer/Types/Numeric.h"
#include "Serializer/Types/Null.h"
#include "Serializer/Types/Object.h"
#include "Serializer/Types/String.h"
#include "Serializer/static_iteration.h"
#include <string>
#include <vector>
#include <memory>

template<typename T>
std::vector<T> deserialize_ptr(const std::shared_ptr<BaseType>& serializedType);

template<typename T>
T deserialize(const std::shared_ptr<BaseType>& serializedType)
{
    std::shared_ptr<Object> serializedObject = std::static_pointer_cast<Object>(serializedType);
    T object;
    constexpr int number_of_properties = std::tuple_size_v<decltype(T::properties)>;
    for_sequence(std::make_index_sequence<number_of_properties>{}, [&](auto i) {
        constexpr auto property = std::get<i>(T::properties);
        std::shared_ptr<String> propertyName(new String);
        propertyName->value = property.name;
        object.*(property.member) = deserialize<typename decltype(property)::Type>(serializedObject->values[propertyName]);
    });
    constexpr int number_of_arr_properties = std::tuple_size_v<decltype(T::arr_properties)>;
    for_sequence(std::make_index_sequence<number_of_arr_properties>{}, [&](auto i) {
        constexpr auto arr_property = std::get<i>(T::arr_properties);
        std::shared_ptr<String> arrPropertyName(new String);
        arrPropertyName->value = arr_property.name;
        object.*(arr_property.member) = deserialize_ptr<typename decltype(arr_property)::Type>(serializedObject->values[arrPropertyName]);
    });
    return object;
}

template<typename T>
std::vector<T> deserialize_ptr(const std::shared_ptr<BaseType>& serializedType)
{
    std::shared_ptr<Array> serializedArray = std::static_pointer_cast<Array>(serializedType);
    std::vector<T> arr;
    for (const auto& i : serializedArray->values)
    {
        arr.push_back(deserialize<T>(i));
    }
    return arr;
}

template<>
double deserialize(const std::shared_ptr<BaseType>& serializedType)
{
    std::shared_ptr<Numeric> serializedNumeric = std::static_pointer_cast<Numeric>(serializedType);
    return serializedNumeric->value;
}

template<>
int deserialize(const std::shared_ptr<BaseType>& serializedType)
{
    std::shared_ptr<Numeric> serializedNumeric = std::static_pointer_cast<Numeric>(serializedType);
    return serializedNumeric->value;
}

template<>
std::string deserialize(const std::shared_ptr<BaseType>& serializedType)
{
    std::shared_ptr<String> serializedString = std::static_pointer_cast<String>(serializedType);
    return serializedString->value;
}

template<>
bool deserialize(const std::shared_ptr<BaseType>& serializedType)
{
    std::shared_ptr<Boolean> serializedBoolean = std::static_pointer_cast<Boolean>(serializedType);
    return serializedBoolean->value;
}

#endif // DESERIALIZE_H
