#include <iostream>
#include <experimental/type_traits>

#include <gtest/gtest.h>

int main(int argc_, char** argv_)
{
  ::testing::InitGoogleTest(&argc_, argv_);
  return RUN_ALL_TESTS();
}