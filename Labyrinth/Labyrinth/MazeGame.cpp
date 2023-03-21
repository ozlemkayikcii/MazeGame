#include <iostream>
#include <ctime>
#include <Windows.h>
#include <conio.h>
#include <fstream>

using namespace std;

char button_;
int coin = 0;
int n = 8, m = 3;
int GRID_WIDTH;
int GRID_HEIGHT;
ofstream outfile("output.txt");

struct objects
{
	int symbol;
	bool active;
	int x;
	int y;
};

#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

int grid[100 * 100];

void ResetGrid();
int XYToIndex(int x, int y);
int IsInBounds(int x, int y);
void Visit(int x, int y);
void PrintGrid();
void player();
void gotoXY(int, int);
void HideTheArrow();
void move();
void PlayAgain();
void ObjectPlace();

int main()
{
	cout << "___________________________RULES____________________________" << endl;
	cout << "| Size of maze must be greater than 9 and smaller than 101. |"<< endl;
	cout << "| Please press w ,a,s or d to move.                         |" << endl;
	cout << "| If the monster are reached, the game will start again.    |" << endl;
	cout << "|___________________________________________________________|" << endl<<endl;

	cout << "Monsters=   " <<char(021)<< "   Golds=  ©  and Exit=   "<<char(206)<< endl<<endl<<endl;
	
	cout << "Please enter the size of maze:" << endl;
	cin >> GRID_HEIGHT;
	if (GRID_HEIGHT < 10 || GRID_HEIGHT>100)
	{
		cout << "size must be greater than 9 and smaller than 101." << endl;
		return -1;
	}

	GRID_WIDTH = GRID_HEIGHT;
	system("cls");
	srand(time(0));
	ResetGrid();
	Visit(1, 1);
	ObjectPlace();

	for (int i = 0; i <= GRID_WIDTH + 2; i++)
	{
		for (int j = 0; j <= GRID_HEIGHT + 2; j++)
		{
			grid[XYToIndex(i, GRID_HEIGHT + 1)] = 1;
			
		}
	}
	grid[XYToIndex(GRID_WIDTH - 1, GRID_HEIGHT - 1)] = 2;
	grid[XYToIndex(GRID_WIDTH - 2, GRID_HEIGHT - 1)] = 2;
	grid[XYToIndex(0, GRID_HEIGHT)] = 1;
	grid[XYToIndex(GRID_WIDTH, 0)] = 1;

	PrintGrid();
	move();
	outfile.close();
	return 0;
	system("pause");
}
void ResetGrid()
{
	for (int i = 0; i < GRID_WIDTH*GRID_HEIGHT; ++i)
	{
		grid[i] = 1;
	}
}
int XYToIndex(int x, int y)
{
	
	return y * GRID_WIDTH + x;
}
int IsInBounds(int x, int y)
{
	
	if (x < 0 || x >= GRID_WIDTH) return false;
	if (y < 0 || y >= GRID_HEIGHT) return false;
	return true;
}
void Visit(int x, int y)
{

	grid[XYToIndex(x, y)] = 0;

	int dirs[4];
	dirs[0] = NORTH;
	dirs[1] = EAST;
	dirs[2] = SOUTH;
	dirs[3] = WEST;
	for (int i = 0; i < 4; ++i)
	{
		int r = rand() & 3;
		int temp = dirs[r];
		dirs[r] = dirs[i];
		dirs[i] = temp;
	}

	for (int i = 0; i < 4; ++i)
	{

		int dx = 0, dy = 0;
		switch (dirs[i])
		{
		case NORTH: dy = -1; break;
		case SOUTH: dy = 1; break;
		case EAST: dx = 1; break;
		case WEST: dx = -1; break;
		}
		int x2 = x + (dx << 1);
		int y2 = y + (dy << 1);
		if (IsInBounds(x2, y2))
		{
			if (grid[XYToIndex(x2, y2)] == 1)
			{

				grid[XYToIndex(x2 - dx, y2 - dy)] = 0;
				Visit(x2, y2);
			}
		}
	}
}
void PrintGrid()
{

	for (int i = 0; i < GRID_HEIGHT + 3; ++i)
	{
		for (int j = 0; j < GRID_WIDTH + 3; ++j)
		{
			switch (grid[XYToIndex(j, i)])
			{
			case 0:
				cout << " ";
				break;

			case 1:
				cout << char(176);
				break;
			case 2:
				cout << char(206);
				break;
			case 3:
				cout << char(021);
				break;
			case 4:
				cout << "©";
				break;
			
			}
		}
		cout << " " << endl;
	}
}

void player()
{
	cout << char(002);
}

void gotoXY(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

}

void HideTheArrow()
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(out, &cursorInfo);
}

void move()
{

	int x = 1;
	int y = 1;
	int xCln = 1;
	int yCln = 1;

	while (true)
	{

		HideTheArrow();

		gotoXY(xCln, yCln);
		cout << " ";

		gotoXY(x, y);
		player();
		button_ = _getch();
		xCln = x;
		yCln = y;

		if (button_ == 'w' || button_=='W')
		{
			y -= 1;
			cout << endl;
			outfile << "x=" << x << ", y=" << y << endl;
		}

		else if (button_ == 's' || button_ == 'S')
		{
			y += 1;
			cout << endl;
			outfile << "x=" << x << ", y=" << y << endl;
		}
		else if (button_ == 'a' || button_ == 'A')
		{
			x -= 1;
			cout << endl;
			outfile << "x=" << x << ", y=" << y << endl;
		}
		else if (button_ == 'd' || button_ == 'D')
		{
			x += 1;
			cout << endl;
			outfile << "x=" << x << ", y=" << y << endl;

		}

		if (grid[XYToIndex(x, y)] == 1)
		{
			x = xCln;
			y = yCln;
		}
		else if (grid[XYToIndex(x, y)] == 2)
		{
			cout << endl;
			cout << endl << endl;
			cout << "____________________________________________" << endl;

			system("COLOR B");
			cout << "success! " << endl;
			cout << "you collected " << coin << " gold  ^-^     " << endl;
			cin.get();
			exit(0);

		}
		else if (grid[XYToIndex(x, y)] == 4)
		{
			coin++;
			grid[XYToIndex(x, y)] = 0;
		}
		else if (grid[XYToIndex(x, y)] == 3)
		{

			cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
			outfile << endl << "Monster!! The game started again... " << endl;
			
			PlayAgain();

			break;
		}
	}
}
void PlayAgain()
{
	system("cls");
	for (int i = 0; i < GRID_WIDTH; i++)
	{
		for (int j = 0; j < GRID_HEIGHT; j++)
		{
			if (grid[XYToIndex(i, j)] == 3 || grid[XYToIndex(i, j)] == 4)
				grid[XYToIndex(i, j)] = 0;
		}
	}
	
	system("cls");
	coin = 0;
	ObjectPlace();
	PrintGrid();
	move();
}

void ObjectPlace()
{
	for (int i = 0; i < m; i++)
	{
		objects enemy1;
		enemy1.symbol = 3;
		enemy1.active = true;
		enemy1.x = rand() % ((GRID_WIDTH - 5) - 0 + 1);
		enemy1.y = rand() % ((GRID_HEIGHT - 5) - 0 + 1);
		grid[XYToIndex(enemy1.x, enemy1.y)] = 3;
	}
	for (int i = 0; i < n; i++)
	{
		objects golds;
		golds.symbol = 4;
		golds.active = true;
		golds.x = rand() % ((GRID_WIDTH - 5) - 0 + 1);
		golds.y = rand() % ((GRID_HEIGHT - 5) - 0 + 1);
		if (grid[XYToIndex(golds.x, golds.y)] != 1)
			grid[XYToIndex(golds.x, golds.y)] = 4;
		else
			n++;
	}
	n = 8;
}
