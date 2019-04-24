#include <iostream>
#include <string>
#include <cstdlib>
//#include <time.h>
//#include <stdlib.h>
#include "Sudoku.h"
#include <string>
//#include <windows.h>
//#include <tchar.h>
//#include <conio.h>
//#include <process.h>
//#include <dos.h>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

void Sudoku::startBoard()
{
	//Creates 9x9 board.
	std::cout << "Game Start!" << endl;
	
	for (int row = 1; row < 10; row++)			//Creates board
	{
		for (int col = 1; col < 10; col++)
		{
			start[row][col] = col;
		}
	}
}

void Sudoku::clearBoard()
{
	//Clear Board
	for (int row = 1; row < 10; row++)				//erases the board, set all values to 0
	{
		for (int col = 1; col < 10; col++)
		{
			start[row][col] = 0;
			user[row][col] = 0;
		}
	}
}

void Sudoku::printBoard()
{
	gameovercounter = 0;
	//Prints Board Layout and Print blank space if 0
	for (int row = 1; row < 10; row++)
	{
		for (int col = 1; col < 10; col++)
		{
				if (start[row][col] == 0 && user[row][col] ==0)	//Blanks
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);			// if any value is zero, prints a blank space
					std::cout << "  ";
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
						std::cout << " |";
				}
				else if (start[row][col] == answer[row][col] )	//Preset
				{
					gameovercounter++;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);		//prints values at the start
					std::cout << " " << start[row][col];
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
					std::cout << " |";
				}
				 else if (user[row][col] != answer[row][col])		//Wrong
				 {	 
					 points = points + 5;		//Points +5 everytime input is wrong
					 

					 std::cout << " ";
					 for (int i = 1; i < 10; i++)													// A problem with this is that, the board stops to blink at the error spot, failing to print the rest of the board until blinking is over...
					 {
						 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);			//blinks when value is wrong in red
						 std::cout << " ";
						 Sleep(250);
						 std::cout << "\b";
						 std::cout << user[row][col];
						 Sleep(250);
						 std::cout << "\b";
					 }
					 user[row][col] = 0;
					 start[row][col] = 0;
					 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
					 std::cout << " ";
					 std::cout << " |";
				}
				
			//What if you dont assign start array, and only use user array until the end?
				 else if (user[row][col]==answer[row][col] )			//Correct
				{ 
					gameovercounter++;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);			//Use color 10 to print the user input
					std::cout << " " << user[row][col];
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
					std::cout << " |";	
				}
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		std::cout << endl << "------------------------------------" << endl;
	}
}

void Sudoku::endgamemessage()
{

	cout << "You have scored " << grade[DifficultyChoice] << " points!" << endl;			//End game stats, 

	if (grade[DifficultyChoice] == 100)
	{
		std::cout << "Excellent Player, try the next level" << endl;
	}
	else if (grade[DifficultyChoice] >= 80 && grade[DifficultyChoice] < 100)
	{
		std::cout << "Good player, keep practicing on this level" << endl;
	}
	else if (grade[DifficultyChoice] >= 60 && grade[DifficultyChoice] < 80)
	{
		std::cout << "Ok player.. keep practicing on this level if you dare" << endl;
	}
	else if (grade[DifficultyChoice] >= 40 && grade[DifficultyChoice] < 60)
	{
		std::cout << "Well.. suggest trying an easir level" << endl;
	}
	else if (grade[DifficultyChoice] < 40)
	{
		std::cout << "Watch this video how to play" << endl;
	}
}


void Sudoku::Average()
{
	AveragePrinter("VeryEasy", 1);		// runs a helper function to easily detect whether the difficulty, name of difficulty, average value at the difficulty, and if there is no saves at the difficulty
	AveragePrinter("Easy", 2);
	AveragePrinter("Medium", 3);
	AveragePrinter("Hard", 4);
}

void Sudoku::ReadFile(string file)
{
	string holder;					//holder to carry the value from the file

	ifstream read;				//output file
	read.open(file);		//open file

	for (int row = 1; row < 10; row++)
	{
		for (int col = 1; col < 10; col++)	
		{
			getline(read, holder, ' ');						//delimitizer is space
			stringstream StringtoInt(holder);				// changes holder string to int
			StringtoInt >> start[row][col];					//	Assigns values to start array, everytime it reads a space, it moves to the next array spot 
		}
	}

	for (int row = 1; row < 10; row++)
	{
		for (int col = 1; col < 10; col++)
		{
			getline(read, holder, ' ');
			stringstream StringtoInt(holder);			//Same as above, excepts reads the second values into the array which are the answers
			StringtoInt >> answer[row][col];
		}
	}
	//Prints preset sudoku and answer sudoku chart, used to help create program at the start

	/*for (int row = 1; row < 10; row++)		
	{ 
		for (int col = 1; col < 10; col++)
		{
			cout << start[row][col] << " ";
		}
		cout << endl;
	}

	cout << endl;

	for (int row = 1; row < 10; row++)
	{
		for (int col = 1; col < 10; col++)
		{
			cout << answer[row][col] << " ";
		}
		cout << endl;
	}*/
}

void Sudoku::intro()		//game intro
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);			//Function to change colors of next lines, 15 for white to reset it to normal color
	std::cout << endl;
	std::cout << "If your answer is correct, the number will be ";			
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	std::cout << "green" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	std::cout << "If the cell is the part of the problem then the number will be ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	std::cout << "blue" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	std::cout << "If your answer is wrong, the number will blink ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	std::cout << "red" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	Sleep(1000);
}

void Sudoku::SelectDifficulty()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);		
	//Select Difficulty
	std::cout << "Select one of the following difficulties: " << endl;
	std::cout << "(1) for very easy" << endl;
	std::cout << "(2) for easy" << endl;
	std::cout << "(3) for medium" << endl;
	std::cout << "(4) for hard" << endl;
	cin >> DifficultyChoice;
	//Create random integer from 1-10
	srand(time(NULL));
	int random = rand() % 10 + 1;
	// Changes int datatype to string datatype
	stringstream ss;
	ss << random;
	string str = ss.str();

	// Print Difficulty Chosen, and use 1-4 to assign difficulties to a value, 
	if (DifficultyChoice == 1) {
		std::cout << "You have selected very easy" << endl;		
		string randomfile = "VeryEasy" + str+".txt";		//uses the same random variable in string form to access the corresponding .txt
		std::cout << randomfile << endl;
		ReadFile(randomfile);
		difficultycounter[1]++;				//counts how mnay times the difficulty runs 
	}
	else if (DifficultyChoice == 2) 
	{
		std::cout << "You have selected easy" << endl;
		string randomfile = "Easy" + str + ".txt";
		std::cout << randomfile << endl;
		ReadFile(randomfile);
		difficultycounter[2]++;
	}
	else if (DifficultyChoice == 3)
	{
		std::cout << "You have selected Medium" << endl;
		string randomfile = "Medium" + str + ".txt";
		std::cout << randomfile << endl;
		ReadFile(randomfile);
		difficultycounter[3]++;
	}
	else if (DifficultyChoice = 4)
	{
		std::cout << "You have selected Hard" << endl;
		string randomfile = "Hard" + str + ".txt";
		std::cout << randomfile << endl;
		ReadFile(randomfile);
		difficultycounter[4]++;
	}
	std::cout << "To quit, type -1, For a new game, type -2" << endl;		//part two if the intro, these options are located in the input section, which runs after the select difficulty
	cout << " To see average for all levels, enter -3" << endl;
}

void Sudoku::AveragePrinter(string difficulty,int i)			//help function to print the averages of each difficulty, as well as detect when the average has no saves, so no average yet
{
	
		if (difficultycounter[i] != 0)
		{
			cout << difficulty << " average is " << average[i] << endl;
		}
		else if (difficultycounter[i] < 1)
		{
			cout << difficulty << " average is not set" << endl;
		}
	
}

void Sudoku::inputs()
{	
	//Gives time for user to read
	bool x = 0;							//bool for new game
	bool z = 0;							//bool for averages
	printBoard();				//prints the board everytime input function is used
	grade[DifficultyChoice] = maxgrade - points;			// a way to find the current grade after every time input function is used
	cout << "Current score is : " << grade[DifficultyChoice] << endl;

	if (gameovercounter >= 81)				// when there 81 gameover counter, game is over. the counter is found in the printboard function, where it detects the type of number on the board
	{
		std::cout << "Game is over, no more open spots" << endl;
		Sleep(1000);
		std::cout << "Game will now end" << endl;
		std::cout << "Checking stats" << endl;
		endgamemessage();				//game is now over, prints stats and ending messages
	}

	else
	{

		for (int row = 1; row < 10; row++)
		{
			for (int col = 1; col < 10; col++)						//cycles through every col and row
			{
				if (start[row][col] == 0)

				{
					// Asks for row and column, then uses that to assign new value to array[row][column]
					std::cout << "Input row then column seperated by a space respectively to change the value at that spot (1-9)" << endl;
					cin >> row >> col;
					if (row == -1 || column == -1)		//if row or col = -1, then exit program 
					{
						exit(0);
					}
					else if (row == -2 || column == -2)			//i if row or col = -2, changes bool to false, breaks out of first  loop
					{
						x = 1;
						break;
					}
					else if (row > 9 || column > 9)			//ensures row and column is within 1-9
					{
						cout << "This is not an allowed value" << endl;

					}
					else if (row == -3 || column == -3)			//option to check for average, breaks out first loop
					{
						z = 1;
						break;
					}
					std::cout << "Now enter the new value you want to change to (1-9)" << endl;		// now that row and column is selected, will ask for value in this row and column
					cin >> value;
					if (value == -1)						// if value == -1, then exit program
					{
						exit(0);
					}
					else if (value == -2)				//if value == -2, then changes bool to false, breaks out first loop
					{
						x = 1;
						break;
					}
					else if (value == -3)			//option to check for average, breaks out first loop
					{
						z = 1;
						break;
					}
					else if (value > 9)		//ensures value is 1-9
					{
						cout << "This is not an allowed value" << endl;
						value = 0;			//assigns value to 0, so it could assign user array to zero, allowing to print blank space in printboard again
					}
					
					else if (user[row][col] != 0 || start[row][col] != 0)		//a way to check if the spot has been taken
					{
						cout << "This spot has already been used,please try again" << endl;
						
					}

					user[row][col] = value;			// final value of the row and col that the user selected
					break;
								//breaks second loop when it cycles through all col
				}

			}
			if (x == 1)				//if bool was set to false, break out final loop for new game 
			{
				break;
			}
			else if (z == 1)	//break out final loop for average
			{
				break;
			}
			else   //break out final loop, to rerun inputs for more values
			{
				break;
			}
		}
		if (x == 1)
		{			//if bool was set to false, new game

			clearBoard();
			SelectDifficulty();
			inputs();
		}
		else if (z == 1) // if bool was set to false, check average, then run inputs again
		{
			Average();
			inputs();
		}
		else   //after all is run, rerun for inputs for more values
		{
			inputs();
		}
	}
}

void Sudoku::StartGame()
{
	ReadLastSave();  //Reads last save data, to find previous game datas
	intro();  // start of the game.. introduction 
	startBoard(); //starts a 9x9 board
	clearBoard();//clears board for values
	SelectDifficulty(); //select difficulty through user, randomly finds a game, and assigns the values to the board
	inputs(); //Where you enter the values, and much more complex logic
	Save();  //Save final data of this program run for the future
}

void Sudoku::Save()		//Opens last Save
{
	ofstream write;				//file write
	write.open("Saves.txt");

	for (int i = 1; i < 5; i++)				//int to string 
	{
		stringstream s;						//Assigns updated variables to txt
		s << difficultycounter[i];
		string difficultycounter = s.str();
		write << difficultycounter << " ";
		
	}
	write << endl;
	

	for (int i = 1; i < 5; i++)
	{
		stringstream s;
		s << savegrade[i];
		string grade = s.str();
		write << grade << " ";
		
	}
	write << endl;
	

	for (int i = 1; i < 5; i++)
	{
		stringstream s;
		s << average[i];
		string average = s.str();
		write << average << " ";
		
	}
	write << endl;
	
}


void Sudoku::ReadLastSave()
{
	

	string holder;
								
	ifstream read;				// file read
	read.open("Saves.txt");
	for (int i = 1; i < 5; i++)	
	{
		getline(read, holder, ' ');
		stringstream StringtoInt(holder);		//string to int
		StringtoInt >> difficultycounter[i];		// Assigns last save variables to class variables
		
	}

	for (int i = 1; i < 5; i++)
	{
		getline(read, holder, ' ');
		stringstream StringtoInt(holder);		
		StringtoInt >> savegrade[i];		
		
	}

	for (int i = 1; i < 5; i++)
	{
		getline(read, holder, ' ');
		stringstream StringtoInt(holder);
		StringtoInt >> average[i];
		
	}
	

}

Sudoku::Sudoku()
{
}


Sudoku::~Sudoku()
{
}
