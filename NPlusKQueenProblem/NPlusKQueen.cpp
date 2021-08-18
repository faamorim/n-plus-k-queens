#include "NPlusKQueen.h"
#include <set>

using namespace std;

vector<vector<char>> Solution::getBoard()
{
  vector<vector<char>> _solution;
  for (int i = 0; i < boardSize; ++i)
  {
    vector<char> line(boardSize, '.');
    _solution.push_back(line);
  }

  for (const auto &q : queens)
  {
    _solution[q.first][q.second] = 'Q';
  }
  
  for (const auto& p : pawns)
  {
    _solution[p.first][p.second] = 'p';
  }

  return _solution;
}

bool checkSolution(Solution& solution, int boardSize, int pawns)
{
  if (solution.boardSize != boardSize)
  {
    return false;
  }
  if (solution.pawns.size() != pawns)
  {
    return false;
  }
  if (solution.queens.size() != boardSize + pawns)
  {
    return false;
  }

  //Add real solution check

  return true;
}

#define nsDiagIndex(x, y, b) (x + b - y - 1)
#define psDiagIndex(x, y, b) (x + y)

void findSolutions(vector<Solution>& solution, int boardSize, int pawnCount, vector<pair<int, int>>& queens, vector<pair<int, int>>& pawns, int x, int y, vector<bool>& columns, vector<bool>& psDiag, vector<bool>& nsDiag);

void findSolutions(vector<Solution>& solution, int boardSize, int pawnCount, vector<pair<int, int>>& queens, vector<pair<int, int>>& pawns, int x, int y, vector<bool>& columns, vector<bool>& psDiag, vector<bool>& nsDiag)
{
  for (int i = x; i < boardSize; ++i)
  {
    int nsi = nsDiagIndex(i, y, boardSize);
    int psi = psDiagIndex(i, y, boardSize);
    if (columns[i] && nsDiag[nsi] && psDiag[psi])
    {
      columns[i] = false;
      nsDiag[nsi] = false;
      psDiag[psi] = false;
      pair<int, int> pos(y, i);
      queens.push_back(pos);
      if (queens.size() == boardSize + pawnCount)
      {
        vector<pair<int, int>> q(queens);
        vector<pair<int, int>> p(pawns);
        Solution s;
        s.boardSize = boardSize;
        s.queens = q;
        s.pawns = p;
        solution.push_back(s);
      }
      findSolutions(solution, boardSize, pawnCount, queens, pawns, 0, y + 1, columns, psDiag, nsDiag);
      columns[i] = true;
      nsDiag[nsi] = true;
      psDiag[psi] = true;
      queens.pop_back();
    }
  }
}

#undef nsDiagIndex
#undef psDiagIndex

vector<Solution> findSolutions(int boardSize, int pawns)
{
  vector<Solution> _solution;

  set<int> columns, psDiag, nsDiag;
  vector<pair<int, int>> q(0);
  vector<pair<int, int>> p(0);
  vector<bool> c(boardSize, true);
  vector<bool> psd(2 * boardSize - 1, true);
  vector<bool> nsd(2 * boardSize - 1, true);
  vector<bool> test2(boardSize, true);
  findSolutions(_solution, boardSize, pawns, q, p, 0, 0, c, psd, nsd);

  return _solution;
}