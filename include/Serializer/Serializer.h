#ifndef JSONSERIALIZER_H
#define JSONSERIALIZER_H

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
struct Serializer
{
    static std::shared_ptr<BaseType> serialize(const T& object);
    static T deserialize(const std::shared_ptr<BaseType>& serializedType);
};

template<typename T>
struct Serializer<std::vector<T>>
{
    static std::shared_ptr<BaseType> serialize(const std::vector<T> arr);
    static std::vector<T> deserialize(const std::shared_ptr<BaseType>& serializedType);
};

template<>
struct Serializer<int>
{
    static std::shared_ptr<BaseType> serialize(const int& number);
    static int deserialize(const std::shared_ptr<BaseType>& serializedType);
};

template<>
struct Serializer<double>
{
    static std::shared_ptr<BaseType> serialize(const double& number);
    static double deserialize(const std::shared_ptr<BaseType>& serializedType);
};

template<>
struct Serializer<std::string>
{
    static std::shared_ptr<BaseType> serialize(const std::string& string);
    static std::string deserialize(const std::shared_ptr<BaseType>& serializedType);
};

template<>
struct Serializer<bool>
{
    static std::shared_ptr<BaseType> serialize(const bool& boolean);
    static bool deserialize(const std::shared_ptr<BaseType>& serializedType);
};


template<typename T>
std::shared_ptr<BaseType> Serializer<T>::serialize(const T& object)
{
    std::shared_ptr<Object> serializedObject(new Object);
    constexpr int number_of_parameters = std::tuple_size_v<decltype(T::properties)>;
    for_sequence(std::make_index_sequence<number_of_parameters>{}, [&](auto i){
        constexpr auto property = std::get<i>(T::properties);
        serializedObject->values[property.name] = Serializer<typename decltype(property)::Type>::serialize(object.*(property.member));
    });
    return serializedObject;
}

template<typename T>
std::shared_ptr<BaseType> Serializer<std::vector<T>>::serialize(const std::vector<T> arr)
{
    std::shared_ptr<Array> serializedArray(new Array);
    for (const auto& i : arr)
        serializedArray->values.push_back(Serializer<T>::serialize(i));
    return serializedArray;
}

std::shared_ptr<BaseType> Serializer<int>::serialize(const int& number)
{
    std::shared_ptr<Numeric> serializedNumeric(new Numeric);
    serializedNumeric->value = number;
    return serializedNumeric;
}

std::shared_ptr<BaseType> Serializer<double>::serialize(const double& number)
{
    std::shared_ptr<Numeric> serializedNumeric(new Numeric);
    serializedNumeric->value = number;
    return serializedNumeric;
}

std::shared_ptr<BaseType> Serializer<std::string>::serialize(const std::string& string)
{
    std::shared_ptr<String> serializedString(new String);
    serializedString->value = string;
    return serializedString;
}

std::shared_ptr<BaseType> Serializer<bool>::serialize(const bool& boolean)
{
    std::shared_ptr<Boolean> serializedBoolean(new Boolean);
    serializedBoolean->value = boolean;
    return serializedBoolean;
}


template<typename T>
T Serializer<T>::deserialize(const std::shared_ptr<BaseType>& serializedType)
{
    std::shared_ptr<Object> serializedObject = std::static_pointer_cast<Object>(serializedType);
    T object;
    constexpr int number_of_properties = std::tuple_size_v<decltype(T::properties)>;
    for_sequence(std::make_index_sequence<number_of_properties>{}, [&](auto i) {
        constexpr auto property = std::get<i>(T::properties);
        object.*(property.member) = Serializer<typename decltype(property)::Type>::deserialize(serializedObject->values[property.name]);
    });
    return object;
}

template<typename T>
std::vector<T> Serializer<std::vector<T>>::deserialize(const std::shared_ptr<BaseType>& serializedType)
{
    std::shared_ptr<Array> serializedArray = std::static_pointer_cast<Array>(serializedType);
    std::vector<T> arr;
    for (const auto& i : serializedArray->values)
        arr.push_back(Serializer<T>::deserialize(i));
    return arr;
}

int Serializer<int>::deserialize(const std::shared_ptr<BaseType>& serializedType)
{
    std::shared_ptr<Numeric> serializedNumeric = std::static_pointer_cast<Numeric>(serializedType);
    return serializedNumeric->value;
}

double Serializer<double>::deserialize(const std::shared_ptr<BaseType>& serializedType)
{
    std::shared_ptr<Numeric> serializedNumeric = std::static_pointer_cast<Numeric>(serializedType);
    return serializedNumeric->value;
}

std::string Serializer<std::string>::deserialize(const std::shared_ptr<BaseType>& serializedType)
{
    std::shared_ptr<String> serializedString = std::static_pointer_cast<String>(serializedType);
    return serializedString->value;
}

bool Serializer<bool>::deserialize(const std::shared_ptr<BaseType>& serializedType)
{
    std::shared_ptr<Boolean> serializedBoolean = std::static_pointer_cast<Boolean>(serializedType);
    return serializedBoolean->value;
}

#endif // JSONSERIALIZER_H
