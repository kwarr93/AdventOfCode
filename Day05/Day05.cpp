#include "..\Advent.Core\Algorithms.h"
#include "..\Advent.Core\IO.h"

#include <iostream>
#include <numeric>
#include <stack>

using namespace Advent::Algorithms;
using namespace Advent::IO;
using namespace std;

struct Rearrangment
{
  unsigned Count;
  unsigned FromIndex;
  unsigned ToIndex;
};

using const_lines_iterator = vector<wstring>::const_iterator;
using stack_vector = vector<stack<wchar_t>>;
using rearrangment_vector = vector<Rearrangment>;

stack_vector BuildStacks(const const_lines_iterator& start, const const_lines_iterator& end)
{
  auto indexLine = end - 1;
  auto stackCount = indexLine->size() / 4 + 1;

  stack_vector results;
  results.resize(stackCount);

  auto it = end - 2;
  while (true)
  {
    auto crateLine = *it;
    for (auto i = 0; i < stackCount; ++i)
    {
      auto crateSign = crateLine[i * 4 + 1];
      if (crateSign == ' ') continue;

      results[i].push(crateSign);
    }

    if (it != start)
    {
      --it;
    }
    else
    {
      break;
    }
  }  

  return results;
}

rearrangment_vector ParseRearrangements(const const_lines_iterator& start, const const_lines_iterator& end)
{
  rearrangment_vector results;
  results.reserve(distance(start, end));

  for (auto it = start; it != end; ++it)
  {
    Rearrangment rearrangment;
    swscanf_s(it->c_str(), L"move %d from %d to %d", &rearrangment.Count, &rearrangment.FromIndex, &rearrangment.ToIndex);
    --rearrangment.FromIndex;
    --rearrangment.ToIndex;

    results.push_back(rearrangment);
  }

  return results;
}

wstring GetTopCrates(const stack_vector& stacks)
{
  wstring result;
  for (auto& stack : stacks)
  {
    result += stack.top();
  }
  return result;
}

int main()
{
  // Part 1
  {
    auto lines = read_lines(L"input.txt");

    auto separatorLineIt = find_if(lines.begin(), lines.end(), [](const auto& line) { return line.empty(); });
    if (lines.end() == separatorLineIt || separatorLineIt - lines.begin() < 2) abort();

    auto stacks = BuildStacks(lines.begin(), separatorLineIt);
    auto rearrangements = ParseRearrangements(separatorLineIt + 1, lines.end());

    //Make rearrangements
    for (auto& rearrangement : rearrangements)
    {
      auto& fromStack = stacks[rearrangement.FromIndex];
      auto& toStack = stacks[rearrangement.ToIndex];

      for (auto i = 0; i < rearrangement.Count; ++i)
      {
        toStack.push(fromStack.top());
        fromStack.pop();
      }
    }

    //Collect top crates
    auto topCrates = GetTopCrates(stacks);

    wcout << format(L"Top crates (part1): {}", topCrates);
  }

  // Part 2
  {
    auto lines = read_lines(L"input.txt");

    auto separatorLineIt = find_if(lines.begin(), lines.end(), [](const auto& line) { return line.empty(); });
    if (lines.end() == separatorLineIt || separatorLineIt - lines.begin() < 2) abort();

    auto stacks = BuildStacks(lines.begin(), separatorLineIt);
    auto rearrangements = ParseRearrangements(separatorLineIt + 1, lines.end());

    //Make rearrangements
    for (auto& rearrangement : rearrangements)
    {
      auto& fromStack = stacks[rearrangement.FromIndex];
      auto& toStack = stacks[rearrangement.ToIndex];

      stack<wchar_t> movedCrates;
      for (auto i = 0; i < rearrangement.Count; ++i)
      {
        movedCrates.push(fromStack.top());
        fromStack.pop();
      }

      for (auto i = 0; i < rearrangement.Count; ++i)
      {
        toStack.push(movedCrates.top());
        movedCrates.pop();
      }
    }

    //Collect top crates
    auto topCrates = GetTopCrates(stacks);

    wcout << format(L"Top crates (part2): {}", topCrates);
  }

  return 0;
}