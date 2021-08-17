// NPlusKQueenProblem.cpp : Defines the entry point for the application.
//

#include "NPlusKQueenProblem.h"

using namespace std;

int main()
{
	cout << "Welcome to the N + K Queen Problem solver." << endl;
	cout << "To calculate the number of solutions for the N + K Queen Problem first enter the size of the board (N): ";
	int boardSize;

	cin >> boardSize;
	while (cin.fail() || boardSize < 1)
	{
		cout << "Invalid input for board size (N). Enter a valid number: ";
		cin.clear();
		cin.ignore(1i64, '\n');
		cin >> boardSize;
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

	return 0;
}