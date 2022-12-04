#include "..\Advent.Core\IO.h"

#include <iostream>
#include <numeric>

using namespace Advent::IO;
using namespace std;

using range = pair<unsigned, unsigned>;

bool DoesRangeFullyContainRange(const range& lhs, const range& rhs)
{
  return 
    (lhs.first <= rhs.first && rhs.first <= lhs.second) &&
    (lhs.first <= rhs.second && rhs.second <= lhs.second);
}

bool DoesRangeOverlapRange(const range& lhs, const range& rhs)
{
  return
    (lhs.first <= rhs.first && rhs.first <= lhs.second) ||
    (lhs.first <= rhs.second && rhs.second <= lhs.second);
}

bool IsAssignmentPairFullyContainsOther(const std::wstring& line)
{
  if (line.empty()) return 0;

  range firstRange;
  range secondRange;

  swscanf_s(line.c_str(), L"%d-%d,%d-%d", &firstRange.first, &firstRange.second, &secondRange.first, &secondRange.second);

  return
    DoesRangeFullyContainRange(firstRange, secondRange) ||
    DoesRangeFullyContainRange(secondRange, firstRange);
}

bool AreRangesOverlap(const std::wstring& line)
{
  if (line.empty()) return 0;

  range firstRange;
  range secondRange;

  swscanf_s(line.c_str(), L"%d-%d,%d-%d", &firstRange.first, &firstRange.second, &secondRange.first, &secondRange.second);

  return
    DoesRangeOverlapRange(firstRange, secondRange) ||
    DoesRangeOverlapRange(secondRange, firstRange);
}

int main()
{
  // Part 1
  {
    auto assignmentPairsFullyContain = read_lines<bool>(L"input.txt", IsAssignmentPairFullyContainsOther);
    auto numberOfAssignmentPairsFullyContain = reduce(begin(assignmentPairsFullyContain), end(assignmentPairsFullyContain), 0);

    wcout << format(L"Number of assignment pairs where one fully contains the other: {}", numberOfAssignmentPairsFullyContain) << endl;
  }

  // Part 2
  {
    auto overlappingRanges = read_lines<bool>(L"input.txt", AreRangesOverlap);
    auto numberOfOverlappingRanges = reduce(begin(overlappingRanges), end(overlappingRanges), 0);

    wcout << format(L"Number of assignment pairs where the ranges overlap: {}", numberOfOverlappingRanges) << endl;
  }

  return 0;
}