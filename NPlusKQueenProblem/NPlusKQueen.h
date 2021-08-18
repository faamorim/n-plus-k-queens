#pragma once

#include <vector>

struct Solution
{
  int boardSize;
  std::vector<std::pair<int, int>> queens;
  std::vector<std::pair<int, int>> pawns;

  std::vector<std::vector<char>> getBoard();
};

std::vector<Solution> findSolutions(int boardSize, int pawns);

bool checkSolution(Solution &solution, int boardSize, int pawns);

