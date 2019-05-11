#pragma once

#include "Helper.h"
#include <type_traits>

/* Detecting insert (const_iterator, value_type) method */
template <typename Container>
using insert_return_type = decltype(std::declval<Container>().insert(ConstItr<Container>(), Value<Container>()));

template <typename Container, typename = void>
struct has_insert : std::false_type{};

template <typename Container>
struct has_insert<Container, std::void_t<insert_return_type<Container>>> : std::true_type{};

template <typename Container>
constexpr bool has_insert_v = has_insert<Container>::value;

static_assert(has_insert_v<std::vector<int>>);
static_assert(has_insert_v<std::list<int>>);