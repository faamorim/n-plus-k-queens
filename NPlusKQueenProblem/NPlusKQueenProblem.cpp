// NPlusKQueenProblem.cpp : Defines the entry point for the application.
//

#include "NPlusKQueenProblem.h"
#include "NPlusKQueen.h"
#include <time.h>
#include <iomanip>

using namespace std;

int main()
{
	cout << "Welcome to the N + K Queen Problem solver." << endl;
	while (true)
	{
		cout << "To calculate the number of solutions for the N + K Queen Problem first enter the size of the board (N) then the number of pawns (K)." << endl;
		cout << "Enter the size of the board (N) (enter 0 to quit): ";
		int boardSize;

		cin >> boardSize;
		while (cin.fail())
		{
			cout << "Invalid input for board size (N). Enter a valid number: ";
			cin.clear();
			cin.ignore(1i64, '\n');
			cin >> boardSize;
		}

		if (boardSize == 0)
		{
			return 0;
		}

		cout << endl;

		cout << "Enter the number of pawns (K):";
		int pawns;
		cin >> pawns;
		while (cin.fail() || pawns < 0)
		{
			cout << "Invalid input for number of pawns (K). Enter a valid number: ";
			cin.clear();
			cin.ignore(1i64, '\n');
			cin >> pawns;
		}
		cout << endl;

		cout << "Looking for solutions to put " << (boardSize + pawns) << " queens in a " << boardSize << "x" << boardSize << " board with " << pawns << " pawns..." << endl;

		clock_t tStart = clock();
		vector<Solution> solutions = findSolutions(boardSize, pawns);
		cout << solutions.size() << " solutions found in " << setprecision(3) << ((double)(clock() - tStart)/CLOCKS_PER_SEC) << " seconds." << endl;

		int wrong = 0;

		tStart = clock();
		for (auto s : solutions)
		{
			if (!checkSolution(s, boardSize, pawns))
			{
				++wrong;
			}
		}
		cout << "All solutions checked in " << setprecision(3) << ((double)(clock() - tStart) / CLOCKS_PER_SEC) << " seconds: " <<  wrong << " wrong solutions." << endl << endl;
	}

	return 0;
}