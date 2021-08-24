#include <iostream>
#include <ctime>
#include <cstdlib>
#include <windows.h>
#include "sudoku.h"

#define n 9
#define N n+1

sudoku::sudoku()
{
	this->clear();
}
sudoku::sudoku(int tab[N][N])
{
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++) {
			this->Board[i][j] = tab[i][j];
		}
}
sudoku::sudoku(sudoku& s): sudoku(s.Board) {}

void sudoku::enter()
{
	for (int i = 1; i <= n; i++)	for (int j = 1; j <= n; j++) { std::cin >> this->Board[i][j]; system("cls"); this->print(); }
}
void sudoku::print()

{
	for (int i = 1; i <= n; i++) {	//wiersz
		if ((i - 1) % 3 == 0) printf("|-------|-------|-------|\n");
		printf("|");
		for (int j = 1; j <= n; j++) {	//kolumna
			if (this->Board[i][j] != 0)	printf(" %d", this->Board[i][j]);
			else printf(" .");
			if (j % 3 == 0) printf(" |");
		}
		printf("\n");
	}
	printf("|-------|-------|-------|\n");
}
void sudoku::print_solution()
{
	sudoku s = *this;
	s.solve();
	s.print();
}
bool sudoku::check()
{
	/// sprawdzenie wierszy
	for (int i = 1; i <= n; i++) { // wiersz

		for (int j = 1; j <= n; j++) { // kolumna

			for (int k = 1; k <= n; k++) { // paluszek wskazuj¹cy do porównywania

				if (this->Board[i][j] == this->Board[i][k] && j != k && this->Board[i][k] != 0) return 0;
			}
		}
	}

	/// sprawdzanie kolumn
	for (int i = 1; i <= n; i++) { // kolumna

		for (int j = 1; j <= n; j++) { // wiersz

			for (int k = 1; k <= n; k++) { //paluszek wskazuj¹cy do porównywania

				if (this->Board[j][i] == this->Board[k][i] && j != k && this->Board[k][i] != 0) return 0;
			}
		}
	}

	/// sprawdzanie kwadratów 3x3
	for (int i = 1; i <= 3; i++) { // kolumny

		for (int j = 1; j <= 3; j++) { // wiersze	
			for (int ki = 1; ki <= 3; ki++) { // komórka, na któr¹ aktualnie wskazujemy

				int x = (i - i % 3);
				int y = (j - j % 3);

				for (int kj = 1; kj <= 3; kj++) {

					for (int a = 0; a <= 2; a++)
					{
						for (int b = 0; b <= 2; b++)
						{
							if (this->Board[j + 3 * a][i + 3 * b] == this->Board[kj + 3 * a][ki + 3 * b] && j != kj && i != ki && this->Board[j + 3 * a][i + 3 * b] != 0) return 0;
						}
					}
				}
			}
		}
	}
	return 1;
}
void sudoku::clear()
{
	for (int i = 1; i <= n; i++) {

		for (int j = 0; j <= n; j++) {

			this->Board[i][j] = 0;
		}
	}
}
bool sudoku::solve(int wsp1, int wsp2)
{
	if ((wsp1 >= 1 && wsp1 <= n) && (wsp2 >= 1 && wsp2 <= n))
	{
		if (this->Board[wsp1][wsp2] == 0)
		{
			for (int i = 1; i <= n; i++)
			{
				this->Board[wsp1][wsp2] = i;
				if (this->check())
				{
					if (wsp1 < n) {
						if (this->solve(wsp1 + 1, wsp2))	return 1;
						else this->Board[wsp1][wsp2] = 0;
					}
					else if (wsp2 < n)
					{
						if (this->solve(1, wsp2 + 1))	return 1;
						else this->Board[wsp1][wsp2] = 0;
					}
					else return 1;
				}
				this->Board[wsp1][wsp2] = 0;
			}
		}
		else
		{
			if (wsp1 < n) return this->solve(wsp1 + 1, wsp2);
			else if (wsp2 < n) return this->solve(1, wsp2 + 1);
			else return 1;
		}
		return 0;
	}
	return 1;
}

void sudoku::generate(int tryb_gry)
{
	this->clear();
	//iloœæ wype³nionych pocz¹tkowych pól zale¿y od trybu gry
	//Tryb		min - max
	//Beginner	50 - 55
	//Easy		36 - 40
	//Medium	32 - 35
	//Hard		28 - 31
	//Expert	22 - 27
	srand(time(NULL));

	int min, max = 0;
	int XRand, YRand = 0;
	sudoku aux;
	switch (tryb_gry)
	{
		case 0:
		{
			min = 50; max = 55;
		}break;
		case 1:
		{
			min = 36; max = 40;
		}break;
		case 2:
		{
			min = 32; max = 35;
		}break;
		case 3:
		{
			min = 28; max = 31;
		}break;
		case 4:
		{
			min = 22; max = 27;
		}break;
	}
	int NmbOfStartCells = rand() % (max - min + 1) + min;
	int NmbOfGaps = 81 - NmbOfStartCells;
	
	for (int i = 0; i < 10; i++) // random cells
	{
		do
		{
			XRand = rand() % 9 + 1;		
			Sleep(0.01);
			YRand = rand() % 9 + 1;
		} while (this->Board[XRand][YRand] != 0);

		int k = 0;
	
		do
		{
			this->Board[XRand][YRand] = rand() % 9 + 1;
			k++;
		} while (k < 10 && !this->check());
		
		if (k == 10 || !this->check()) { this->Board[XRand][YRand] = 0; i--; }
	}
	this->solve();

	for (int i = 0; i < NmbOfGaps; i++)
	{
		do
		{
			XRand = rand() % 9 + 1;
			Sleep(0.01);
			YRand = rand() % 9 + 1;
		} while (this->Board[XRand][YRand] == 0);
		
		this->Board[XRand][YRand] = 0;
	}
}