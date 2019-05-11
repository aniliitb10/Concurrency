#pragma once

#include <type_traits>

// Detecting size_t size() function

template <typename Container>
using size_type = decltype(std::declval<Container>().size());

template <typename Container, typename  = void>
struct has_size : std::false_type{};

template <typename Container>
struct has_size<Container, std::void_t<size_type<Container>>> : std::true_type{};

template <typename Container>
constexpr bool has_size_v = has_size<Container>::value;
