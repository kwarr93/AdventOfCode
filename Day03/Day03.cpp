#include "..\AdventOfCode.Core\Algorithms.h"
#include "..\AdventOfCode.Core\IO.h"

#include <iostream>
#include <numeric>
#include <set>

using namespace Advent::Algorithms;
using namespace Advent::IO;
using namespace std;

int CalculatePriority(wchar_t item)
{
  return islower(item) ? item - L'a' + 1 : item - L'A' + 27;
}

int CalculateCommonItemPriority(const std::wstring& line)
{
  if (line.empty()) return 0;

  auto halfLineLength = line.size() / 2;
  auto firstRucksackItems = line.substr(0, halfLineLength);
  auto secondRucksackItems = line.substr(halfLineLength);

  auto commonItem = L' ';
  for (auto item : secondRucksackItems)
  {
    if (firstRucksackItems.find(item) != wstring::npos)
    {
      commonItem = item;
      break;
    }
  }

  return CalculatePriority(commonItem);
}

int CalculateGroupBadgePriority(const vector<wstring>::const_iterator& startIt, const vector<wstring>::const_iterator& endIt)
{
  using wchar_set = set<wchar_t>;

  wchar_set previousIntersectingItems(begin(*startIt), end(*startIt));
  wchar_set intersectingItems;
  for (auto it(startIt + 1); it != endIt; ++it)
  {
    intersectingItems.clear();

    wchar_set currentItems(begin(*it), end(*it));
    set_intersection(begin(previousIntersectingItems), end(previousIntersectingItems), begin(currentItems), end(currentItems), inserter(intersectingItems, intersectingItems.end()));
    previousIntersectingItems = intersectingItems;
  }

  if (intersectingItems.size() != 1) return 0;

  return CalculatePriority(*intersectingItems.begin());
}

int main()
{
  // Part 1
  {
    auto commonItemPriorities = read_lines<int>(L"input.txt", CalculateCommonItemPriority);
    auto commonItemPrioritySum = accumulate(begin(commonItemPriorities), end(commonItemPriorities), 0);

    wcout << format(L"CommonItemPrioritySum: {}", commonItemPrioritySum) << endl;
  }

  // Part 2
  {
    auto lines = read_lines(L"input.txt");
    auto badgePriorities = map_group_n<int>(3, lines, CalculateGroupBadgePriority);
    auto badgePrioritySum = accumulate(begin(badgePriorities), end(badgePriorities), 0);

    wcout << format(L"GroupBadgePrioritySum: {}", badgePrioritySum) << endl;
  }

  return 0;
}