#include <shared_mutex>
#include "STLReflection.h"

template <typename ContainerType>
class ConcurrentList
{
public:
  using const_itr  = typename ContainerType::const_iterator;
  using value_type = typename ContainerType::value_type;
  using WriteLock  = std::unique_lock<std::shared_mutex>;
  using ReadLock   = std::shared_lock<std::shared_mutex>;
  using container_type  = ContainerType;

  auto push_back(const value_type& value)
  ->std::enable_if_t<has_push_back_v<ContainerType>, push_back_return_type<ContainerType>>
  {
    WriteLock lock{_sharedMutex};
    return _container.push_back(value);
  }

  auto operator[] (size_t pos) const
  -> std::enable_if_t <has_index_oper_v<ContainerType>, const index_oper_return_type <ContainerType>& >
  {
    ReadLock lock{_sharedMutex};
    return _container[pos];
  }

  auto size() const
  -> std::enable_if_t<has_size_v<ContainerType>, size_type<ContainerType>>
  {
    ReadLock lock {_sharedMutex};
    return _container.size();
  }


  /* These (std::cbegin() and std::cend()) should not be supported in concurrent containers as it would be tricky to:
   * 1. ensure that the iterators are still valid
   * 2. take a ReadLock on the underlying container while data is being read using iterators */

  /*auto cbegin() const
  -> std::enable_if_t<is_iterable_v<ContainerType>, typename ContainerType::const_iterator>
  {
    return std::cbegin(_container);
  }

  auto cend() const
  -> std::enable_if_t<is_iterable_v<ContainerType>, typename ContainerType::const_iterator>
  {
    return std::cend(_container);
  }*/

private:
  ContainerType _container;
  mutable std::shared_mutex _sharedMutex;
};