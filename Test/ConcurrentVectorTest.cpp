#include <thread>

#include <gtest/gtest.h>
#include "../include/ConcurrentList.h"

#include <vector>
#include <deque>
#include <string>
#include <array>
#include <random>

struct ConcurrentVectorTest : public ::testing::Test
{
};

template <typename Container, typename ValueType = typename Container::value_type>
void randomNumPushBacker(ValueType from_, ValueType to_, size_t count_, Container &list_)
{
  std::random_device device;
  std::mt19937 eng(device());
  std::uniform_int_distribution<ValueType> dis(from_, to_);

  for (int counter = 0; counter < count_; ++counter)
  {
    list_.push_back(dis(eng));
  }
}

template <typename Container, typename ValueType = typename Container::container_type::value_type>
inline void concurrentPushBackTest(ValueType min_, ValueType max_, size_t elemCount_ = 1000, size_t threadCount_ = 50)
{
  Container list;

  std::vector<std::thread> threads;
  for (int index = 0; index < threadCount_; ++index)
  {
    threads.emplace_back(randomNumPushBacker<Container>, min_, max_, elemCount_, std::ref(list));
  }

  for (auto& thread : threads)
  {
    thread.join();
  }

  EXPECT_EQ(threads.size() * elemCount_, list.size());
  std::cout << "Counter: " << 1000 << ", Threads: " << threadCount_ << ", List size: " << list.size() << std::endl;
}

TEST_F(ConcurrentVectorTest, conc_test)
{
  concurrentPushBackTest<ConcurrentList<std::vector<int>>>(1, 1'000'000);
  concurrentPushBackTest<ConcurrentList<std::deque<int>>>(1, 1'000'000);

  concurrentPushBackTest<ConcurrentList<std::vector<int>>>(1, 1'000'000, 10000, 100);
  concurrentPushBackTest<ConcurrentList<std::deque<int>>>(1, 1'000'000, 10000, 100);

  concurrentPushBackTest<ConcurrentList<std::string>>(0, 127);

  // this should break
  // concurrentPushBackTest<std::vector<int>>(1, 1'000'000);
}