#include <iostream>
#include <fstream>
#include <conio.h>
#include <Windows.h>
#include <time.h>
using namespace std;

char map[16][24]; //2D array for the map 
void gotoxy(int column, int line) // function that I think gets coordinates of the screen ?
{
	COORD coord;
	coord.Y = column;
	coord.X = line;
	SetConsoleCursorPosition(
		GetStdHandle(STD_OUTPUT_HANDLE), coord
	);
}

void hidecursor()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;   info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}

void timer(int t)
{
	for (int x = 0; x < t; x++)
	{
		gotoxy(20, 60);
	}
}

void getobject(char c, int x, int y)
{
	gotoxy(x, y);
	cout << c;
	map[x][y] = c;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
	bool game = true;
	bool gamestart = false;

	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

	srand(time(0));
	int yrand = 0;

	bool pause = true;
	bool win = false;

	int oldscore = 0;
	int pscore = 0;

	char choice; //variable that holds key input

	int rowcount[55];
	for (int x = 0; x < 55; x++)
	{
		rowcount[x] = 0;
	}
	bool down = true;

	int edeaths = 0;

	char e = 'S';
	bool ealive[55];
	int ex[55]; int ey[55];

	/////ROW 1//////////////////
	ex[0] = 3, ey[0] = 6;
	for (int x = 1; x < 11; x++)
	{
		ex[x] = 3;
		ey[x] = 6 + x;
	}

	/////ROW 2//////////////////
	ex[11] = 4, ey[11] = 6;
	for (int x = 12; x < 22; x++)
	{
		ex[x] = 4;
		ey[x] = 6 + (x - 11);
	}

	/////ROW 3//////////////////
	ex[22] = 5, ey[22] = 6;
	for (int x = 23; x < 33; x++)
	{
		ex[x] = 5;
		ey[x] = 6 + (x - 22);
	}

	/////ROW 4//////////////////
	ex[33] = 6, ey[33] = 6;
	for (int x = 34; x < 44; x++)
	{
		ex[x] = 6;
		ey[x] = 6 + (x - 33);
	}

	for (int x = 0; x < 55; x++)
	{
		ealive[x] = true;
	}

	/////ROW 5//////////////////
	ex[44] = 7, ey[44] = 6;
	for (int x = 45; x < 55; x++)
	{
		ex[x] = 7;
		ey[x] = 6 + (x - 44);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	for (int x = 0; x < 55; x++)
	{
		ealive[x] = true;
	}

	bool scroll = true;

	bool right[55];
	int R[55]; int L[55];
	for (int x = 0; x < 55; x++)
	{
		R[x] = 6;
		L[x] = 7;
	}
	for (int x = 0; x < 55; x++)
	{
		right[x] = true;
	}

	char p = 'A';
	int px = 13, py = 11;
	bool palive = true;

	char bp = '^';
	int bpx = 2, bpy = 0;
	bool bpalive = false;

	char be = 'v';
	int bex = 2, bey = 1;
	bool bealive = false;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	ifstream inFile;
	inFile.open("map.txt"); //opens the map file
	for (int x = 0; x < 16; x++) //loop for x coordinates on the map ROW
	{
		for (int y = 0; y < 24; y++) //loop for y coordinates on the map COLUMN
		{
			inFile >> map[x][y]; //grabs every chracter on the map x&y
		}
	}
	inFile.close();

	ifstream inFile2;
	inFile2.open("highscore.txt");
	inFile2 >> oldscore;
	inFile2.close();

	for (int x = 0; x < 55; x++)
	{
		getobject(e, ex[x], ey[x]);
	}

	getobject(p, px, py);

	system("cls"); //cleares the screen from my understanding ?

	for (int x = 0; x < 16; x++) //loop for x coordinates on the map ROW
	{
		for (int y = 0; y < 24; y++) //loop for y coordinates on the map COLUMN
		{
			if (map[x][y] == '.') //if the coordinate is a period
				map[x][y] = ' '; //convertst the period into a blank space
			cout << map[x][y]; //displays the map
		}
		cout << endl; //breaks the map rows after the rows characters have printed
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	do //infinite while loop for the game
	{
		yrand = rand() % 18 + 1;

		if (_kbhit()) //checks if the keyboard is pressed
		{
			choice = _getch(); //gets the pressed key and assigns it to variable choice

			if (palive && choice == ',' && py - 1 != 0 && pause == false)
			{
				getobject(' ', px, py);
				py--;
				SetConsoleTextAttribute(h, 0x0001 | 0x0008); //MAKES PLAYER CYAN
				getobject(p, px, py);
			}
			if (palive && choice == '.' && py + 1 != 23 && pause == false)
			{
				getobject(' ', px, py);
				py++;
				SetConsoleTextAttribute(h, 0x0001 | 0x0008); //MAKES PLAYER CYAN
				getobject(p, px, py);
			}
			if (palive && choice == 'x' && bpalive == false && pause == false)
			{
				bpalive = true;
				bpx = px, bpy = py;
			}
			if (choice == 'e')
			{
				game = false;
			}
			if (choice == 's' && gamestart == false)
			{
				gamestart = true;
				pause = false;
				gotoxy(8, 5);
				cout << "              ";
				gotoxy(10, 4);
				cout << "                ";
			}
			if (choice == 'p' && pause == false && gamestart == true && palive == true && edeaths < 55)
			{
				pause = true;
				gotoxy(8, 8);
				SetConsoleTextAttribute(h, 0x0003 | 0x0008);
				cout << "PAUSED";
			}
			else if (choice == 'p' && pause == true && gamestart == true && palive == true && edeaths < 55)
			{
				pause = false;
				gotoxy(8, 8);
				cout << "      ";
			}
			if (choice == 'r' && win == true)
			{
				edeaths = 0;
				win = false;
				gotoxy(6, 8);
				cout << "        ";
				gotoxy(8, 2);
				cout << "                    ";

				for (int x = 0; x < 55; x++)
				{
					rowcount[x] = 0;
				}
				down = true;

				/////ROW 1//////////////////
				ex[0] = 3, ey[0] = 6;
				for (int x = 1; x < 11; x++)
				{
					ex[x] = 3;
					ey[x] = 6 + x;
				}

				/////ROW 2//////////////////
				ex[11] = 4, ey[11] = 6;
				for (int x = 12; x < 22; x++)
				{
					ex[x] = 4;
					ey[x] = 6 + (x - 11);
				}

				/////ROW 3//////////////////
				ex[22] = 5, ey[22] = 6;
				for (int x = 23; x < 33; x++)
				{
					ex[x] = 5;
					ey[x] = 6 + (x - 22);
				}

				/////ROW 4//////////////////
				ex[33] = 6, ey[33] = 6;
				for (int x = 34; x < 44; x++)
				{
					ex[x] = 6;
					ey[x] = 6 + (x - 33);
				}

				for (int x = 0; x < 55; x++)
				{
					ealive[x] = true;
				}

				/////ROW 5//////////////////
				ex[44] = 7, ey[44] = 6;
				for (int x = 45; x < 55; x++)
				{
					ex[x] = 7;
					ey[x] = 6 + (x - 44);
				}

				for (int x = 0; x < 55; x++)
				{
					ealive[x] = true;
				}

				scroll = true;

				for (int x = 0; x < 55; x++)
				{
					R[x] = 6;
					L[x] = 7;
				}
				for (int x = 0; x < 55; x++)
				{
					right[x] = true;
				}
			}
			if (choice == 'r' && palive == false)
			{
				gotoxy(6, 6);
				cout << "             ";
				gotoxy(8, 1);
				cout << "                      ";

				yrand = 0;

				pause = false;
				win = false;

				pscore = 0;

				for (int x = 0; x < 55; x++)
				{
					rowcount[x] = 0;
				}
				down = true;

				edeaths = 0;

				/////ROW 1//////////////////
				ex[0] = 3, ey[0] = 6;
				for (int x = 1; x < 11; x++)
				{
					ex[x] = 3;
					ey[x] = 6 + x;
				}

				/////ROW 2//////////////////
				ex[11] = 4, ey[11] = 6;
				for (int x = 12; x < 22; x++)
				{
					ex[x] = 4;
					ey[x] = 6 + (x - 11);
				}

				/////ROW 3//////////////////
				ex[22] = 5, ey[22] = 6;
				for (int x = 23; x < 33; x++)
				{
					ex[x] = 5;
					ey[x] = 6 + (x - 22);
				}

				/////ROW 4//////////////////
				ex[33] = 6, ey[33] = 6;
				for (int x = 34; x < 44; x++)
				{
					ex[x] = 6;
					ey[x] = 6 + (x - 33);
				}

				for (int x = 0; x < 55; x++)
				{
					ealive[x] = true;
				}

				/////ROW 5//////////////////
				ex[44] = 7, ey[44] = 6;
				for (int x = 45; x < 55; x++)
				{
					ex[x] = 7;
					ey[x] = 6 + (x - 44);
				}

				////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				for (int x = 0; x < 55; x++)
				{
					ealive[x] = true;
				}

				scroll = true;

				for (int x = 0; x < 55; x++)
				{
					R[x] = 6;
					L[x] = 7;
				}
				for (int x = 0; x < 55; x++)
				{
					right[x] = true;
				}

				px = 13, py = 11;
				palive = true;

				bpx = 2, bpy = 0;
				bpalive = false;

				bex = 2, bey = 1;
				bealive = false;


				for (int x = 0; x < 55; x++)
				{
					getobject(e, ex[x], ey[x]);
				}

				getobject(p, px, py);
				gotoxy(2, 4);
				cout << "        ";
				cout << pscore;
			}
		}

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		else //while the keyboard isnt pressed
		{
			hidecursor();
			if (gamestart == false)
			{
				timer(7000);
				SetConsoleTextAttribute(h, 0x0002 | 0x0008);
				gotoxy(8, 5);
				cout << "SPACE INVADERS";
				SetConsoleTextAttribute(h, 0x0004 | 0x0004);
				gotoxy(10, 4);
				cout << "PRESS S TO START";
			}
			if (pause == false)
			{
				timer(6000);

				SetConsoleTextAttribute(h, 0x0002 | 0x0008);
				gotoxy(0, 0);
				cout << "~~~~~SPACE INVADERS~~~~~";

				SetConsoleTextAttribute(h, 0x0008 | 0x0006);
				gotoxy(1, 4);
				cout << "SCORE";
				gotoxy(2, 4);
				cout << pscore;

				gotoxy(1, 12);
				cout << "Hi-SCORE";
				gotoxy(2, 12);
				cout << oldscore;

				SetConsoleTextAttribute(h, 0x0003 | 0x0008);
				gotoxy(6, 25);
				cout << "PRESS < TO MOVE LEFT";
				gotoxy(7, 25);
				cout << "PRESS > TO MOVE RIGHT";
				gotoxy(8, 25);
				cout << "PRESS X TO SHOOT";
				gotoxy(9, 25);
				cout << "PRESS P TO PAUSE";
				gotoxy(10, 25);
				cout << "PRESS E TO EXIT";

				SetConsoleTextAttribute(h, 0x0004 | 0x0008); //DISPLAYS ENEMIES AS RED

				yrand = rand() % 50 + 1;

				if (pscore > oldscore)
				{
					ofstream outFile;
					outFile.open("highscore.txt");
					outFile << pscore;
					outFile.close();
					oldscore = pscore;
				}
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				////////////////////////////////////////ROW 1/////////////////////////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

				////////////////////////////////////////ENEMY 1///////////////////////////////////////////////////////////////////////////////
				if (scroll && ealive[0] && right[0] == false && ey[0] + 1 != (ey[0] + L[0]) && ey[0] + L[0] == (ey[0] + L[0]))
				{
					R[0]++;
					L[0]--;
					getobject(' ', ex[0], ey[0]);
					ey[0]++;
					getobject(e, ex[0], ey[0]);
				}
				if (scroll && ealive[0] && right[0] && ey[0] - 1 != (ey[0] - R[0]) && ey[0] - R[0] == (ey[0] - R[0]))
				{
					R[0]--;
					L[0]++;
					getobject(' ', ex[0], ey[0]);
					ey[0]--;
					getobject(e, ex[0], ey[0]);
				}
				if (scroll && ealive[0] && R[0] == 1)
				{
					right[0] = false;
				}
				else if (scroll && ealive[0] && L[0] == 1)
				{
					right[0] = true;
					rowcount[0]++;
				}
				if (ealive[0] && bpalive && bpx == ex[0] && bpy == ey[0])
				{
					scroll = false;
					bpalive = false;
					getobject(' ', bpx, bpy);
					bpx = 2, bpy = 0;
					getobject('X', ex[0], ey[0]);
					timer(3000);
					getobject(' ', ex[0], ey[0]);
					getobject(' ', ex[0], ey[0]);
					ealive[0] = false;
					pscore = pscore + (ey[0] * 8);
					scroll = true;
					edeaths++;
				}

				////////////////////////////////////////ENEMY 2 - 11//////////////////////////////////////////////////////////////////////////
				for (int x = 1; x < 11; x++)
				{
					if (ealive[x - 1])
					{
						if (scroll && ealive[x] && right[x] == false && ey[x] + 1 != (ey[x] + L[x]) && ey[x] + L[x] == (ey[x] + L[x]))
						{
							R[x]++;
							L[x]--;
							ey[x]++;
							getobject(e, ex[x], ey[x]);
						}
					}
					else
					{
						if (scroll && ealive[x] && right[x] == false && ey[x] + 1 != (ey[x] + L[x]) && ey[x] + L[x] == (ey[x] + L[x]))
						{
							R[x]++;
							L[x]--;
							getobject(' ', ex[x], ey[x]);
							ey[x]++;
							getobject(e, ex[x], ey[x]);
						}
					}
					if (scroll && ealive[x] && right[x] && ey[x] - 1 != (ey[x] - R[x]) && ey[x] - R[x] == (ey[x] - R[x]))
					{
						R[x]--;
						L[x]++;
						getobject(' ', ex[x], ey[x]);
						ey[x]--;
						getobject(e, ex[x], ey[x]);
					}
					if (scroll && ealive[x] && R[x] == 1)
					{
						right[x] = false;
					}
					else if (scroll && ealive[x] && L[x] == 1)
					{
						right[x] = true;
						rowcount[x]++;
					}
					if (ealive[x] && bpalive && bpx == ex[x] && bpy == ey[x])
					{
						scroll = false;
						bpalive = false;
						getobject(' ', bpx, bpy);
						bpx = 2, bpy = 0;
						getobject('X', ex[x], ey[x]);
						timer(3000);
						getobject(' ', ex[x], ey[x]);
						getobject(' ', ex[x], ey[x]);
						ealive[x] = false;
						pscore = pscore + (ey[x] * 8);
						scroll = true;
						edeaths++;
					}
				}

				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				////////////////////////////////////////ROW 2/////////////////////////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

				////////////////////////////////////////ENEMY 12//////////////////////////////////////////////////////////////////////////////
				if (scroll && ealive[11] && right[11] == false && ey[11] + 1 != (ey[11] + L[11]) && ey[11] + L[11] == (ey[11] + L[11]))
				{
					R[11]++;
					L[11]--;
					getobject(' ', ex[11], ey[11]);
					ey[11]++;
					getobject(e, ex[11], ey[11]);
				}
				if (scroll && ealive[11] && right[11] && ey[11] - 1 != (ey[11] - R[11]) && ey[11] - R[11] == (ey[11] - R[11]))
				{
					R[11]--;
					L[11]++;
					getobject(' ', ex[11], ey[11]);
					ey[11]--;
					getobject(e, ex[11], ey[11]);
				}
				if (scroll && ealive[11] && R[11] == 1)
				{
					right[11] = false;
				}
				else if (scroll && ealive[11] && L[11] == 1)
				{
					right[11] = true;
					rowcount[11]++;
				}
				if (ealive[11] && bpalive && bpx == ex[11] && bpy == ey[11])
				{
					scroll = false;
					bpalive = false;
					getobject(' ', bpx, bpy);
					bpx = 2, bpy = 0;
					getobject('X', ex[11], ey[11]);
					timer(3000);
					getobject(' ', ex[11], ey[11]);
					getobject(' ', ex[11], ey[11]);
					ealive[11] = false;
					pscore = pscore + (ey[11] * 8);
					scroll = true;
					edeaths++;
				}

				////////////////////////////////////////ENEMY 13 - 22//////////////////////////////////////////////////////////////////////////
				for (int x = 12; x < 22; x++)
				{
					if (ealive[x - 1])
					{
						if (scroll && ealive[x] && right[x] == false && ey[x] + 1 != (ey[x] + L[x]) && ey[x] + L[x] == (ey[x] + L[x]))
						{
							R[x]++;
							L[x]--;
							ey[x]++;
							getobject(e, ex[x], ey[x]);
						}
					}
					else
					{
						if (scroll && ealive[x] && right[x] == false && ey[x] + 1 != (ey[x] + L[x]) && ey[x] + L[x] == (ey[x] + L[x]))
						{
							R[x]++;
							L[x]--;
							getobject(' ', ex[x], ey[x]);
							ey[x]++;
							getobject(e, ex[x], ey[x]);
						}
					}
					if (scroll && ealive[x] && right[x] && ey[x] - 1 != (ey[x] - R[x]) && ey[x] - R[x] == (ey[x] - R[x]))
					{
						R[x]--;
						L[x]++;
						getobject(' ', ex[x], ey[x]);
						ey[x]--;
						getobject(e, ex[x], ey[x]);
					}
					if (scroll && ealive[x] && R[x] == 1)
					{
						right[x] = false;
					}
					else if (scroll && ealive[x] && L[x] == 1)
					{
						right[x] = true;
						rowcount[x]++;
					}
					if (ealive[x] && bpalive && bpx == ex[x] && bpy == ey[x])
					{
						scroll = false;
						bpalive = false;
						getobject(' ', bpx, bpy);
						bpx = 2, bpy = 0;
						getobject('X', ex[x], ey[x]);
						timer(3000);
						getobject(' ', ex[x], ey[x]);
						getobject(' ', ex[x], ey[x]);
						ealive[x] = false;
						pscore = pscore + (ey[x] * 8);
						scroll = true;
						edeaths++;
					}
				}

				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				////////////////////////////////////////ROW 3/////////////////////////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

				////////////////////////////////////////ENEMY 23//////////////////////////////////////////////////////////////////////////////
				if (scroll && ealive[22] && right[22] == false && ey[22] + 1 != (ey[22] + L[22]) && ey[22] + L[22] == (ey[22] + L[22]))
				{
					R[22]++;
					L[22]--;
					getobject(' ', ex[22], ey[22]);
					ey[22]++;
					getobject(e, ex[22], ey[22]);
				}
				if (scroll && ealive[22] && right[22] && ey[22] - 1 != (ey[22] - R[22]) && ey[22] - R[22] == (ey[22] - R[22]))
				{
					R[22]--;
					L[22]++;
					getobject(' ', ex[22], ey[22]);
					ey[22]--;
					getobject(e, ex[22], ey[22]);
				}
				if (scroll && ealive[22] && R[22] == 1)
				{
					right[22] = false;
				}
				else if (scroll && ealive[22] && L[22] == 1)
				{
					right[22] = true;
					rowcount[22]++;
				}
				if (ealive[22] && bpalive && bpx == ex[22] && bpy == ey[22])
				{
					scroll = false;
					bpalive = false;
					getobject(' ', bpx, bpy);
					bpx = 2, bpy = 0;
					getobject('X', ex[22], ey[22]);
					timer(3000);
					getobject(' ', ex[22], ey[22]);
					getobject(' ', ex[22], ey[22]);
					ealive[22] = false;
					pscore = pscore + (ey[22] * 8);
					scroll = true;
					edeaths++;
				}

				////////////////////////////////////////ENEMY 24 - 33//////////////////////////////////////////////////////////////////////////
				for (int x = 23; x < 33; x++)
				{
					if (ealive[x - 1])
					{
						if (scroll && ealive[x] && right[x] == false && ey[x] + 1 != (ey[x] + L[x]) && ey[x] + L[x] == (ey[x] + L[x]))
						{
							R[x]++;
							L[x]--;
							ey[x]++;
							getobject(e, ex[x], ey[x]);
						}
					}
					else
					{
						if (scroll && ealive[x] && right[x] == false && ey[x] + 1 != (ey[x] + L[x]) && ey[x] + L[x] == (ey[x] + L[x]))
						{
							R[x]++;
							L[x]--;
							getobject(' ', ex[x], ey[x]);
							ey[x]++;
							getobject(e, ex[x], ey[x]);
						}
					}
					if (scroll && ealive[x] && right[x] && ey[x] - 1 != (ey[x] - R[x]) && ey[x] - R[x] == (ey[x] - R[x]))
					{
						R[x]--;
						L[x]++;
						getobject(' ', ex[x], ey[x]);
						ey[x]--;
						getobject(e, ex[x], ey[x]);
					}
					if (scroll && ealive[x] && R[x] == 1)
					{
						right[x] = false;
					}
					else if (scroll && ealive[x] && L[x] == 1)
					{
						right[x] = true;
						rowcount[x]++;
					}
					if (ealive[x] && bpalive && bpx == ex[x] && bpy == ey[x])
					{
						scroll = false;
						bpalive = false;
						getobject(' ', bpx, bpy);
						bpx = 2, bpy = 0;
						getobject('X', ex[x], ey[x]);
						timer(3000);
						getobject(' ', ex[x], ey[x]);
						getobject(' ', ex[x], ey[x]);
						ealive[x] = false;
						pscore = pscore + (ey[x] * 8);
						scroll = true;
						edeaths++;
					}
				}

				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				////////////////////////////////////////ROW 4/////////////////////////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

				////////////////////////////////////////ENEMY 34//////////////////////////////////////////////////////////////////////////////
				if (scroll && ealive[33] && right[33] == false && ey[33] + 1 != (ey[33] + L[33]) && ey[33] + L[33] == (ey[33] + L[33]))
				{
					R[33]++;
					L[33]--;
					getobject(' ', ex[33], ey[33]);
					ey[33]++;
					getobject(e, ex[33], ey[33]);
				}
				if (scroll && ealive[33] && right[33] && ey[33] - 1 != (ey[33] - R[33]) && ey[33] - R[33] == (ey[33] - R[33]))
				{
					R[33]--;
					L[33]++;
					getobject(' ', ex[33], ey[33]);
					ey[33]--;
					getobject(e, ex[33], ey[33]);
				}
				if (scroll && ealive[33] && R[33] == 1)
				{
					right[33] = false;
				}
				else if (scroll && ealive[33] && L[33] == 1)
				{
					right[33] = true;
					rowcount[33]++;
				}
				if (ealive[33] && bpalive && bpx == ex[33] && bpy == ey[33])
				{
					scroll = false;
					bpalive = false;
					getobject(' ', bpx, bpy);
					bpx = 2, bpy = 0;
					getobject('X', ex[33], ey[33]);
					timer(3000);
					getobject(' ', ex[33], ey[33]);
					getobject(' ', ex[33], ey[33]);
					ealive[33] = false;
					pscore = pscore + (ey[33] * 8);
					scroll = true;
					edeaths++;
				}

				////////////////////////////////////////ENEMY 35 - 44//////////////////////////////////////////////////////////////////////////
				for (int x = 34; x < 44; x++)
				{
					if (ealive[x - 1])
					{
						if (scroll && ealive[x] && right[x] == false && ey[x] + 1 != (ey[x] + L[x]) && ey[x] + L[x] == (ey[x] + L[x]))
						{
							R[x]++;
							L[x]--;
							ey[x]++;
							getobject(e, ex[x], ey[x]);
						}
					}
					else
					{
						if (scroll && ealive[x] && right[x] == false && ey[x] + 1 != (ey[x] + L[x]) && ey[x] + L[x] == (ey[x] + L[x]))
						{
							R[x]++;
							L[x]--;
							getobject(' ', ex[x], ey[x]);
							ey[x]++;
							getobject(e, ex[x], ey[x]);
						}
					}
					if (scroll && ealive[x] && right[x] && ey[x] - 1 != (ey[x] - R[x]) && ey[x] - R[x] == (ey[x] - R[x]))
					{
						R[x]--;
						L[x]++;
						getobject(' ', ex[x], ey[x]);
						ey[x]--;
						getobject(e, ex[x], ey[x]);
					}
					if (scroll && ealive[x] && R[x] == 1)
					{
						right[x] = false;
					}
					else if (scroll && ealive[x] && L[x] == 1)
					{
						right[x] = true;
						rowcount[x]++;
					}
					if (ealive[x] && bpalive && bpx == ex[x] && bpy == ey[x])
					{
						scroll = false;
						bpalive = false;
						getobject(' ', bpx, bpy);
						bpx = 2, bpy = 0;

						getobject('X', ex[x], ey[x]);
						timer(3000);
						getobject(' ', ex[x], ey[x]);
						getobject(' ', ex[x], ey[x]);
						ealive[x] = false;
						pscore = pscore + (ey[x] * 8);
						scroll = true;
						edeaths++;
					}
				}

				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				////////////////////////////////////////ROW 5/////////////////////////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

				////////////////////////////////////////ENEMY 45//////////////////////////////////////////////////////////////////////////////
				if (scroll && ealive[44] && right[44] == false && ey[44] + 1 != (ey[44] + L[44]) && ey[44] + L[44] == (ey[44] + L[44]))
				{
					R[44]++;
					L[44]--;
					getobject(' ', ex[44], ey[44]);
					ey[44]++;
					getobject(e, ex[44], ey[44]);
				}
				if (scroll && ealive[44] && right[44] && ey[44] - 1 != (ey[44] - R[44]) && ey[44] - R[44] == (ey[44] - R[44]))
				{
					R[44]--;
					L[44]++;
					getobject(' ', ex[44], ey[44]);
					ey[44]--;
					getobject(e, ex[44], ey[44]);
				}
				if (scroll && ealive[44] && R[44] == 1)
				{
					right[44] = false;
				}
				else if (scroll && ealive[44] && L[44] == 1)
				{
					right[44] = true;
					rowcount[44]++;
				}
				if (ealive[44] && bpalive && bpx == ex[44] && bpy == ey[44])
				{
					scroll = false;
					bpalive = false;
					getobject(' ', bpx, bpy);
					bpx = 2, bpy = 0;
					getobject('X', ex[44], ey[44]);
					timer(3000);
					getobject(' ', ex[44], ey[44]);
					getobject(' ', ex[44], ey[44]);
					ealive[44] = false;
					pscore = pscore + (ey[44] * 8);
					scroll = true;
					edeaths++;
				}

				////////////////////////////////////////ENEMY 46 - 55//////////////////////////////////////////////////////////////////////////
				for (int x = 45; x < 55; x++)
				{
					if (ealive[x - 1])
					{
						if (scroll && ealive[x] && right[x] == false && ey[x] + 1 != (ey[x] + L[x]) && ey[x] + L[x] == (ey[x] + L[x]))
						{
							R[x]++;
							L[x]--;
							ey[x]++;
							getobject(e, ex[x], ey[x]);
						}
					}
					else
					{
						if (scroll && ealive[x] && right[x] == false && ey[x] + 1 != (ey[x] + L[x]) && ey[x] + L[x] == (ey[x] + L[x]))
						{
							R[x]++;
							L[x]--;
							getobject(' ', ex[x], ey[x]);
							ey[x]++;
							getobject(e, ex[x], ey[x]);
						}
					}
					if (scroll && ealive[x] && right[x] && ey[x] - 1 != (ey[x] - R[x]) && ey[x] - R[x] == (ey[x] - R[x]))
					{
						R[x]--;
						L[x]++;
						getobject(' ', ex[x], ey[x]);
						ey[x]--;
						getobject(e, ex[x], ey[x]);
					}
					if (scroll && ealive[x] && R[x] == 1)
					{
						right[x] = false;
					}
					else if (scroll && ealive[x] && L[x] == 1)
					{
						right[x] = true;
						rowcount[x]++;
					}
					if (ealive[x] && bpalive && bpx == ex[x] && bpy == ey[x])
					{
						scroll = false;
						bpalive = false;
						getobject(' ', bpx, bpy);
						bpx = 2, bpy = 0;
						getobject('X', ex[x], ey[x]);
						timer(3000);
						getobject(' ', ex[x], ey[x]);
						getobject(' ', ex[x], ey[x]);
						ealive[x] = false;
						pscore = pscore + (ey[x] * 8);
						scroll = true;
						edeaths++;
					}
				}
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				if (down)
				{
					for (int x = 0; x < 55; x++)
					{
						if (ealive[x] && rowcount[x] == 4)
						{
							scroll = false;
							rowcount[x] = 0;
							getobject(' ', ex[x], ey[x]);
							ex[x]++;
							scroll = true;
							getobject(e, ex[x], ey[x]);
						}
						if (ealive[x] && ex[x] + 1 == 13)
						{
							down = false;
						}
					}
				}

				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				if (bpalive && bpx - 1 != 2)
				{
					SetConsoleTextAttribute(h, 0x0001 | 0x0008); //MAKES PLAYER BULLET CYAN
					getobject(' ', bpx, bpy);
					getobject(p, px, py);
					bpx--;
					getobject(bp, bpx, bpy);
				}

				if (bpx == 3 && bpalive)
				{
					bpalive = false;

					getobject('X', bpx, bpy);
					timer(6000);
					getobject(' ', bpx, bpy);
					bpx = 2, bpy = 0;
				}

				for (int x = 0; x < 55; x++)
				{
					if (ealive[x] && bpalive && bpx == ex[x] && bpy == ey[x])
					{
						scroll = false;
						bpalive = false;
						getobject(' ', bpx, bpy);
						bpx = 2, bpy = 0;
						getobject('X', ex[x], ey[x]);
						timer(3000);
						getobject(' ', ex[x], ey[x]);
						getobject(' ', ex[x], ey[x]);
						ealive[x] = false;
						pscore = pscore + (ey[x] * 8);
						scroll = true;
						edeaths++;
					}
					if (bealive == false && ealive[x] && map[ex[x] + 1][ey[x]] == ' ' && ey[x] == yrand || bealive == false && ealive[x] && map[ex[x] + 1][ey[x]] == p && ey[x] == yrand)
					{
						bealive = true;
						bex = ex[x], bey = ey[x];
					}
				}
				if (bealive && bex + 1 != 14)
				{
					getobject(' ', bex, bey);
					bex++;
					SetConsoleTextAttribute(h, 0x0004 | 0x0008); //DISPLAYS ENEMY BULLETS AS RED
					getobject(be, bex, bey);
				}
				if (bealive && palive && bex == px && bey == py)
				{
					palive = false;
					bealive = false;
					bpalive = false;
					getobject('X', bex, bey);
					timer(6000);
					getobject(' ', bex, bey);
					getobject(' ', bpx, bpy);
					getobject(' ', px, py);
					bex = 2, bey = 1;
				}
				if (bex == 13 && bealive)
				{
					bealive = false;

					getobject('X', bex, bey);
					timer(6000);
					getobject(' ', bex, bey);
					bex = 2, bey = 1;
				}

				if (edeaths == 55)
				{
					Sleep(500);

					win = true;
					gotoxy(6, 8);
					SetConsoleTextAttribute(h, 0x0002 | 0x0008);
					cout << "YOU WIN!";
					gotoxy(8, 2);
					cout << "PRESS R TO CONTINUE!";
				}

				if (palive == false)
				{
					Sleep(500);

					for (int x = 0; x < 55; x++)
					{
						ealive[x] = false;
						getobject(' ', ex[x], ey[x]);
					}
					scroll = false;
					gotoxy(6, 6);
					SetConsoleTextAttribute(h, 0x0004 | 0x0009);
					cout << "  YOU LOSE!  ";
					gotoxy(8, 1);
					cout << "  PRESS R TO RESTART! ";
				}
			}
		}
	} while (game == true);
	return 0;
}