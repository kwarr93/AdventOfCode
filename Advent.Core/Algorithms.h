#pragma once

#include "pch.h"

namespace Advent::Algorithms
{
  template<typename T, typename TInput>
  std::vector<T> map_group_n(size_t n, const TInput& input, const std::function<T(typename TInput::const_iterator&, typename TInput::const_iterator&)> mapper)
  {
    if (input.empty()) return {};

    std::vector<T> result;
    result.reserve(input.size() / 3 + 1);

    auto groupStart = cbegin(input);
    auto groupEnd = groupStart;
    while (groupEnd != cend(input))
    {
      ++groupEnd;
      if (groupEnd == cend(input) || groupEnd - groupStart == 3)
      {
        result.push_back(mapper(groupStart, groupEnd));
        groupStart = groupEnd;
      }
    }

    return result;
  }

  template<typename TCollection>
  void remove_all(TCollection& collection, const typename TCollection::value_type& value)
  {
    collection.erase(std::remove(collection.begin(), collection.end(), value), collection.end());
  }

  template<typename TCollection, class TPredicate>
  void remove_all_if(TCollection& collection, TPredicate predicate)
  {
    collection.erase(std::remove_if(collection.begin(), collection.end(), predicate), collection.end());
  }
}