// logika wysoka
#include <iostream>
#include "sudoku.h"

#define n 9
#define N n+1

using namespace std;

int main()
{
	system("chcp 1250");
	system("cls");

	int opcja = 0;
	int opcja2 = 0;
	int tryb_gry = 0;

	int plansza[N][N] = {
			{0,0,0,0,0,0,0,0,0},
		{0,  0, 0, 0,  0, 1, 0,  6, 0, 0},
		{0,  9, 0, 0,  0, 0, 7,  0, 3, 0},
		{0,  0, 8, 0,  2, 0, 0,  0, 1, 0},

		{0,  0, 0, 1,  0, 4, 0,  0, 9, 0},
		{0,  0, 0, 0,  0, 0, 0,  0, 8, 0},
		{0,  0, 0, 0,  8, 9, 0,  7, 0, 3},

		{0,  0, 3, 0,  0, 0, 0,  0, 0, 5},
		{0,  0, 6, 0,  0, 2, 0,  0, 0, 0},
		{0,  7, 0, 0,  5, 0, 8,  0, 0, 0}
	};

	sudoku s;

	cout << "Proszê wybraæ opcjê [0-1]:\n0. Generowanie sudoku\n1. Rozwi¹zanie sudoku\n";
	cin >> opcja;
	system("cls");

	switch (opcja)
	{
	case 0:
		cout << "Proszê podaæ tryb gry [0-4]:\n0. Pocz¹tkuj¹cy\n1. £atwy\n2. Œredni\n3. Trudny\n4. Bardzo trudny\n";
		cin >> tryb_gry;
		system("cls");

		s.generate(tryb_gry);
		s.print(); puts("");

		break;
	case 1:
		cout << "Proszê wybraæ opcjê [0-1]\n0. Plansza domyœlna\n1. Wczytanie planszy\n";
		cin >> opcja2;
		system("cls");

		switch (opcja2)
		{
		case 0:
			
			s = sudoku::sudoku(plansza);
			s.print(); puts("");
			s.print_solution();
			break;
		case 1:
			cout << "Proszê podaæ wartoœci";			
			s.enter();
			s.print_solution();
			break;
		}
		break;
	}


	puts("");
	system("pause");
	return 0;
}