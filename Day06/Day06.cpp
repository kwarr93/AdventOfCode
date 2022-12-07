#include "..\Advent.Core\Algorithms.h"
#include "..\Advent.Core\IO.h"

#include <deque>
#include <iostream>
#include <numeric>

using namespace Advent::Algorithms;
using namespace Advent::IO;
using namespace std;

pair<bool, uint64_t> FindMarkerStart(const wstring& textStream, uint64_t markerLength)
{
  deque<wchar_t> marker;
  for (auto i = 0; i < textStream.size(); ++i)
  {
    auto character = textStream[i];
    if (marker.size() == markerLength)
    {
      marker.pop_front();
    }

    marker.push_back(character);

    if (count_unique_items(marker) == markerLength)
    {
      return pair{ true, i };
    }
  }

  return pair{ false, 0 };
}

int main()
{
  // Part 1
  {
    auto lines = read_lines(L"input.txt");
    if (lines.empty()) abort();

    auto& textStream = lines[0];
    auto [found, index] = FindMarkerStart(textStream, 4);
    if (!found) abort();

    wcout << format(L"Character processed before start-of-packet marker is detected {}", index + 1) << endl;
  }

  // Part 2
  {
    auto lines = read_lines(L"input.txt");
    if (lines.empty()) abort();

    auto& textStream = lines[0];
    auto [found, index] = FindMarkerStart(textStream, 14);
    if (!found) abort();

    wcout << format(L"Character processed before start-of-message marker is detected {}", index + 1) << endl;
  }

  return 0;
}