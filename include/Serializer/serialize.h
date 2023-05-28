#ifndef SERIALIZE_H
#define SERIALIZE_H

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
#include <memory>
#include <vector>

template<typename T>
std::shared_ptr<BaseType> serialize_arr(const std::vector<T>& arr);

template<typename T>
std::shared_ptr<BaseType> serialize(const T& object)
{
    std::shared_ptr<Object> serializedObject;
    constexpr int number_of_parameters = std::tuple_size_v<decltype(T::properties)>;
    for_sequence(std::make_index_sequence<number_of_parameters>{}, [&](auto i){
        constexpr auto property = std::get<i>(T::properties);
        std::shared_ptr<String> propertyName(new String);
        propertyName->value = property.name;
        serializedObject->values[propertyName] = serialize<typename decltype(property)::Type>(object.*(property.member));
    });
    constexpr int number_of_arr_properties = std::tuple_size_v<decltype(T::arr_properties)>;
    for_sequence(std::make_index_sequence<number_of_arr_properties>{}, [&](auto i) {
        constexpr auto arr_property = std::get<i>(T::arr_properties);
        std::shared_ptr<String> arrPropertyName(new String);
        arrPropertyName->value = arr_property.name;
        serializedObject->values[arrPropertyName] = serialize_arr<typename decltype(arr_property)::Type>(object.*(arr_property.member));
    });
    return serializedObject;
}

template<typename T, std::vector<T>>
std::shared_ptr<BaseType> serialize_arr(const std::vector<T>& arr)
{
    std::shared_ptr<Array> serializedArray;
    for (const auto& i : arr)
    {
        serializedArray->values.push_back(serialize<T>(i));
    }
    return serializedArray;
}

template<>
std::shared_ptr<BaseType> serialize(const int& number)
{
    std::shared_ptr<Numeric> serializedNumeric;
    serializedNumeric->value = number;
    return serializedNumeric;
}

template<>
std::shared_ptr<BaseType> serialize(const double& number)
{
    std::shared_ptr<Numeric> serializedNumeric;
    serializedNumeric->value = number;
    return serializedNumeric;
}

template<>
std::shared_ptr<BaseType> serialize(const bool& boolean)
{
    std::shared_ptr<Boolean> serializedBoolean;
    serializedBoolean->value = boolean;
    return serializedBoolean;
}

template<>
std::shared_ptr<BaseType> serialize(const std::string& string)
{
    std::shared_ptr<String> serializedString;
    serializedString->value = string;
    return serializedString;
}

#endif // SERIALIZE_H
