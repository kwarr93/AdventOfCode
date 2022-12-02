#include "..\AdventOfCode.Core\IO.h"

#include <iostream>
#include <numeric>
#include <sstream>

using namespace Advent::IO;
using namespace std;

int CycleShapeIndex(int from, int offset)
{
  return (from + offset) % 3;
}

int CalculateScoreFromPredictions(const wstring& line)
{
  wchar_t opponentShape;
  wchar_t hintShape;

  // Parse
  wstringstream ss(line);
  ss >> opponentShape >> hintShape;

  // Calculate score
  auto opponentShapeIndex = opponentShape - L'A';
  auto hintShapeIndex = hintShape - L'X';
  // Score based on shape
  int score = hintShapeIndex + 1;
  if (CycleShapeIndex(hintShapeIndex, 2) == opponentShapeIndex)
  {
    // Won
    score += 6;
  }
  else if (hintShapeIndex == opponentShapeIndex)
  {
    // Draw
    score += 3;
  }

  return score;
}

int CalculateScoreFromInstructions(const wstring& line)
{
  wchar_t opponentChoice;
  wchar_t instruction;

  // Parse
  wstringstream ss(line);
  ss >> opponentChoice >> instruction;

  auto opponentChoosenShapeIndex = opponentChoice - L'A';
  auto score = 0;
  if (instruction == L'X')
  {
    // Lose
    score += CycleShapeIndex(opponentChoosenShapeIndex, 2) + 1;
  }
  else if (instruction == L'Y')
  {
    // Draw
    score += 3;
    score += opponentChoosenShapeIndex + 1;
  }
  else if (instruction == L'Z')
  {
    // Win
    score += 6;
    score += CycleShapeIndex(opponentChoosenShapeIndex, 1) + 1;
  }
  return score;
}

int main()
{
  // Part 1
  {
    auto scores = read_lines<int>(L"input.txt", CalculateScoreFromPredictions);
    auto finalScore = accumulate(begin(scores), end(scores), 0);

    wcout << format(L"Final score (part1): {}", finalScore) << endl;
  }

  // Part 2
  {
    auto scores = read_lines<int>(L"input.txt", CalculateScoreFromInstructions);
    auto finalScore = accumulate(begin(scores), end(scores), 0);

    wcout << format(L"Final score (part2): {}", finalScore) << endl;
  }

  return 0;
}