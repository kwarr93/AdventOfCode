#pragma once

#include "pch.h"

namespace Advent::IO
{
  auto default_line_mapper = [](const std::wstring& str) { return str; };

  template<typename T = std::wstring>
  std::vector<T> read_lines(const std::filesystem::path& path, const std::function<T(const std::wstring&)>& mapper = default_line_mapper)
  {
    std::wifstream infile(path.c_str());
    std::wstring line;
    std::vector<T> lines;
    while (std::getline(infile, line))
    {
      lines.push_back(mapper(line));
    }
    return lines;
  }
}