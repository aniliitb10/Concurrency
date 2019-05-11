#pragma once

#include "Helper.h"
#include <type_traits>

/* Checking if the container has push_back(value_type) member function */
template <typename Container>
using push_back_return_type = decltype(std::declval<Container>().push_back(Value<Container>()));

/* Following class definition will be detected only when container doesn't support push_back */
template <typename Container, typename = void >
struct has_push_back : std::false_type{};

/* Following class definition should be detected when Container does support push_back function */
template <typename Container>
struct has_push_back<Container, std::void_t<push_back_return_type<Container>>> : std::true_type{};

/* A simple helper to cleanly test for this function
 * With the help of has_push_back_v, the check is little less verbose:
 * has_push_back_v<std::vector<int>> does the job instead of has_push_back<std::vector<int>>::value */
template <typename Container>
constexpr bool has_push_back_v = has_push_back<Container>::value;

// Some tests for has_push_back_v
static_assert(has_push_back_v<std::vector<int>>);
static_assert(has_push_back_v<std::list<int>>);
static_assert(!has_push_back_v<int>);