#pragma once
#include <string>
using namespace std;
class Sudoku
{
private:
	int column, row, DifficultyChoice, value;
	int start[11][11];
	//string input="hello";
	int answer[11][11];
	int user[11][11];
	int points=0;		// points that will be deducted from grade
	int maxgrade=100;
	int grade[5];
	int savegrade[5];
	int gameovercounter=1;
	int difficultycounter[5];
	int average[5];
public:
	void endgamemessage();
	void StartGame();
	void printBoard();
	void startBoard();
	void clearBoard();
	void SelectDifficulty();
	void inputs();
	void ReadFile(string);
	void Average();
	void ReadLastSave();
	void Save();
	void intro();

	void AveragePrinter(string,int);
	Sudoku();
	~Sudoku();
};

