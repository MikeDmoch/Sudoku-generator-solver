#pragma once
#define n 9
#define N n+1
class sudoku
{
	int Board[N][N];

public:
	sudoku();
	sudoku(int tab[N][N]);
	sudoku(sudoku& s);

	void print();
	void print_solution();
	void enter();
	bool check();
	void clear();

	bool solve(int wsp1 = 1, int wsp2 = 1);
	void generate(int tryb_gry);
};