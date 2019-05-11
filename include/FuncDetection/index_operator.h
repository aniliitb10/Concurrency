#pragma once

#include "Helper.h"
#include <type_traits>

/* Detecting operator[](size_t) const */
template <typename Container>
using index_oper_return_type = decltype(std::declval<Container>().operator[](std::declval<size_t>()));

template <typename Container, typename  = void>
struct has_index_oper : std::false_type{};

template <typename Container>
struct has_index_oper<Container, std::void_t<index_oper_return_type<Container>>> : std::true_type{};

template <typename Container>
constexpr bool has_index_oper_v = has_index_oper<Container>::value;

static_assert(has_index_oper_v<std::vector<int>>);
static_assert(has_index_oper_v<std::string>);
static_assert(!has_index_oper_v<std::list<int>>);