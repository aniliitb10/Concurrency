#pragma once

#include <type_traits>

/* Ensuring that a container is iterable */

template <typename Container, typename  = void>
struct is_iterable : std::false_type{};

template <typename Container>
struct is_iterable<Container, std::void_t<decltype(std::cbegin(std::declval<Container>()), std::cend(std::declval<Container>()))>> : std::true_type{};

template <typename Container>
constexpr bool is_iterable_v = is_iterable<Container>::value;

/* A simple helper to get the value of a Container
 * It MUST ONLY be used to get type information, eg:
 * To use this in a method call to get the method's return value */
template <typename Container>
auto Value() -> typename Container::value_type {
  return std::declval<Container::value_type>();
}

/* A simple helper to get the const_iterator of a Container
 * It MUST ONLY be used to get type information, eg:
 * To use this in a method call to get the method's return value */
template <typename Container>
auto ConstItr() -> typename Container::const_iterator {
  return std::declval<Container::value_type>();
}