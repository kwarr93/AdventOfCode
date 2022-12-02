#include "..\AdventOfCode.Core\IO.h"

#include <iostream>
#include <set>

using namespace Advent::IO;
using namespace std;

int main()
{
  auto lines = read_lines(L"input.txt");

  // Collect calories
  vector<unsigned long> calories;
  auto current = 0ul;
  for (auto& line : lines)
  {
    if (line.empty())
    {
      calories.push_back(current);
      current = {};
      continue;
    }
    else
    {
      current += stoul(line);
    }
  }

  if (calories.size() < 3) return 0;

  // Sort
  sort(calories.rbegin(), calories.rend());
  
  // Print
  wcout << format(L"Top: {}", calories[0]) << endl;
  wcout << format(L"Top three sum: {}", calories[0] + calories[1] + calories[2]) << endl;
}
