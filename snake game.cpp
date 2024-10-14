#include <iostream>
#include <conio.h>
#include<windows.h>
#include<time.h>
using namespace std;
bool gameover;
const int width = 20;
const int heigth = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int ntail;
enum edirection { STOP = 0, LEFT, RIGHT, UP, DOWN};
edirection dir;
void setup()
{
	gameover = false;
	dir = STOP;
	x = width / 2;
	y = heigth / 2;
	fruitX = rand() % width;
	fruitY = rand() % heigth;
	score = 0;
}
void draw()
{
	system("cls"); 
	for (int i = 0; i < width+2; i++)
	{
		cout << "~";
	}
	cout << endl;

	for (int i = 0; i < heigth; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0)
				cout << "|";
			if (i == y && j == x)
			{
				cout << "O";		
			}
			else if (i == fruitY && j == fruitX)
				cout << "@";
			else
			{	
				bool print = false;
				for (int k = 0; k < ntail; k++)
				{
					
					if (tailX[k] == j && tailY[k] == i)
					{
						cout << "+";
						print = true;
					}
					
				}
				if (!print)
						cout << " ";
			
			}
				
			
			if (j == width - 1)
				cout << "|";
		}
		cout << endl;
	
	}
	for (int i = 0; i < width+2; i++)
	{
		cout << "~";
	}
	cout << endl;
	cout << "Score:" << score << endl;
}
void input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
			case 'a':
				dir = LEFT;
				break;
			case 'd':
				dir = RIGHT;
				break;
			case 'w':
				dir = UP;
				break;
			case 's':
				dir = DOWN;
				break;
			case 'x':
				gameover = true;
				break;
		}
	}
}
void logic()
{
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < ntail; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	default:
		break;
	}
	// hit wall kills you
	//if (x > width || x < 0 || y > heigth || y <= 0) 
		//gameover = true;

	//pass through walls
	if (x >= width) x = 0; else if (x < 0) x = width - 1;
	if (y >= width) y = 0; else if (y < 0) y = width - 1;
	
	for (int i = 0; i < ntail; i++)
		if (tailX[i] == x && tailY[i] == y)
		{
			gameover = true;
		}
	if (x == fruitX && y == fruitY)
	{
		score += 10;
		fruitX = rand() % width;
		fruitY = rand() % heigth;
		ntail++;
	}

}
int main()
{ 
	srand(time(NULL));
	setup();
	while (!gameover)
	{
		draw();
		input();
		logic();
		Sleep(90);
	}
	return 0;
	if (dir == LEFT || dir == RIGHT)
	{
		Sleep(5);
	}

	Sleep(100);

	if (dir == UP || dir == DOWN)
	{
		Sleep(60);
	}
}