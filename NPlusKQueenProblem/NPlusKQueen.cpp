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

#define nsDiagIndex(x, y, b) (x + b - y - 1)
#define psDiagIndex(x, y, b) (x + y)

bool isBetween(pair<int, int>& p, pair<int, int>& q1, pair<int, int>& q2)
{
  return ((p.first >= q1.first && p.first <= q2.first) || (p.first <= q1.first && p.first >= q2.first)) && ((p.second >= q1.second && p.second <= q2.second) || (p.second <= q1.second && p.second >= q2.second));
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

  for (int i = 0; i < boardSize + pawns; ++i)
  {
    auto q1 = solution.queens[i];
    for (int j = i + 1; j < boardSize + pawns; ++j)
    {
      auto q2 = solution.queens[j];
      if (q1.first == q2.first && q1.second == q2.second)
      {
        return false;
      }
    }
    for (int k = 0; k < pawns; ++k)
    {
      auto p = solution.pawns[k];
      if (q1.first == p.first && q1.second == p.second)
      {
        return false;
      }
    }
  }

  for (int i = 0; i < boardSize + pawns; ++i)
  {
    auto q1 = solution.queens[i];
    auto q1nsi = nsDiagIndex(q1.second, q1.first, boardSize);
    auto q1psi = psDiagIndex(q1.second, q1.first, boardSize);

    for (int j = i + 1; j < boardSize + pawns; ++j)
    {
      auto q2 = solution.queens[j];
      auto q2nsi = nsDiagIndex(q2.second, q2.first, boardSize);
      auto q2psi = psDiagIndex(q2.second, q2.first, boardSize);
      if (q1.first == q2.first)
      {
        bool safe = false;
        for (auto p : solution.pawns)
        {
          if (p.first == q1.first)
          {
            if (isBetween(p, q1, q2))
            {
              safe = true;
              break;
            }
          }
        }
        if (!safe)
        {
          return false;
        }
      }
      if (q1.second == q2.second)
      {
        bool safe = false;
        for (auto p : solution.pawns)
        {
          if (p.second == q1.second)
          {
            if (isBetween(p, q1, q2))
            {
              safe = true;
              break;
            }
          }
        }
        if (!safe)
        {
          return false;
        }
      }
      if (q1nsi == q2nsi)
      {
        bool safe = false;
        for (auto p : solution.pawns)
        {
          if (nsDiagIndex(p.second, p.first, boardSize) == q1nsi)
          {
            if (isBetween(p, q1, q2))
            {
              safe = true;
              break;
            }
          }
        }
        if (!safe)
        {
          return false;
        }
      }
      if (q1psi == q2psi)
      {
        bool safe = false;
        for (auto p : solution.pawns)
        {
          if (psDiagIndex(p.second, p.first, boardSize) == q1psi)
          {
            if (isBetween(p, q1, q2))
            {
              safe = true;
              break;
            }
          }
        }
        if (!safe)
        {
          return false;
        }
      }
    }
  }

  return true;
}

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
      if (y > 0 && y < boardSize - 1 && pawns.size() < pawnCount)
      {
        for (int pi = i + 1; pi < boardSize - 1; ++pi)
        {
          if (!columns[pi])
          {
            int nspi = nsDiagIndex(pi, y, boardSize);
            int pspi = psDiagIndex(pi, y, boardSize);
            bool oldNspd = nsDiag[nspi];
            bool oldPspd = psDiag[pspi];
            columns[pi] = true;
            nsDiag[nspi] = true;
            psDiag[pspi] = true;
            pair<int, int> pPos(y, pi);
            pawns.push_back(pPos);
            findSolutions(solution, boardSize, pawnCount, queens, pawns, pi + 1, y, columns, psDiag, nsDiag);
            columns[pi] = false;
            nsDiag[nspi] = oldNspd;
            psDiag[pspi] = oldPspd;
            pawns.pop_back();
          }
        }
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