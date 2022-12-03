#pragma once

#include "pch.h"

namespace Advent::Algorithms
{
  template<typename T, typename TInput>
  std::vector<T> group_n(size_t n, const TInput& input, const std::function<T(typename TInput::const_iterator&, typename TInput::const_iterator&)> groupper)
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
        result.push_back(groupper(groupStart, groupEnd));
        groupStart = groupEnd;
      }
    }

    return result;
  }
}