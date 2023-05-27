#ifndef PROPERTY_H
#define PROPERTY_H

template<typename Class, typename T>
struct Property;

#include <tuple>

template<typename Class, typename T>
struct Property
{
    using Type = T;
    T Class:: *const member;
    const char *const name;
    constexpr Property(T Class:: *const &member, const char *const &name) : member(member), name(name) {}
};

#define PROPERTIES constexpr static auto properties = std::tuple
#define PROPERTY(CLASS, MEMBER) Property(&CLASS::MEMBER, #MEMBER)

#endif // PROPERTY_H
