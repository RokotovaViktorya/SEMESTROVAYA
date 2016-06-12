#include <iostream> 
#include <cstdlib> 
#include <conio.h> 
#include <windows.h> 
#include <ctime>

using namespace std;
enum Direction { UP, DOWN, LEFT, RIGHT };
int Field[4][4];


void CreateField()
{
	bool NumIsFree[15];  
	int Nums[15]; 
	for (int i = 0; i < 15; i++) 
		NumIsFree[i] = true;
	bool Ok; 
	int RandNum; 
	srand(time(NULL));
	for (int i = 0; i < 15; i++) 
	{
		Ok = false;  
		while (!Ok) 
		{
			RandNum = rand() % 15 + 1;  
			if (NumIsFree[RandNum - 1]) 
				Ok = true; 
		}
		Nums[i] = RandNum;  
		NumIsFree[RandNum - 1] = false;  
	}
	int Chaos = 0;  
	int CurrNum; 
	for (int i = 0; i < 14; i++)
	{
		CurrNum = Nums[i];
		for (int j = i + 1; j < 15; j++)
			if (CurrNum > Nums[j])
				Chaos++;
	}
	if (Chaos % 2 == 1)  
	{ 
		int temp = Nums[13];
		Nums[13] = Nums[14];
		Nums[14] = temp;
	}
	for (int i = 0; i < 15; i++) 
		Field[i % 4][i / 4] = Nums[i]; 
	    Field[3][3] = 0;
}


void DrawField(void)
{
	
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD cPos;
	unsigned char BL = 219;
	SetConsoleTextAttribute(hCon, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
	SetConsoleTextAttribute(hCon, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_BLUE);
	int i, j;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			cPos.X = j * 3;
			cPos.Y = i * 2 + 1;

			SetConsoleCursorPosition(hCon, cPos);
			printf("%c%c%c%c", BL, BL, BL, BL);
			cPos.Y = i * 2 + 2;
			cPos.X = j * 3;
			SetConsoleCursorPosition(hCon, cPos);
			if (Field[i][j])
				printf("%c%2i%c", BL, Field[i][j], BL);
			else
				printf("%c %c", BL, BL);
			cPos.Y = i * 2 + 3;
			cPos.X = j * 3;
			SetConsoleCursorPosition(hCon, cPos);
			printf("%c%c%c%c", BL, BL, BL, BL);
		}
	}
	SetConsoleTextAttribute(hCon, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
}


void Move(int direction)
{
	int dy[] = { 1, -1, 0, 0 };
	int dx[] = { 0, 0, 1, -1 };
	int i, j;
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			if (Field[i][j] == 0)
			{
				int newy = i + dy[direction];
				int newx = j + dx[direction];
				if (newy >= 0 && newy < 4 &&
					newx >= 0 && newx < 4)
				{
					Field[i][j] = Field[newy][newx];
					Field[newy][newx] = 0;
				}
				return;
			}
}


bool EndOfGame()
{
	int i;
	for (i = 0; i < 15; i++)
		if (Field[i / 4][i % 4] != i + 1)
			return false;
	return true;
}
int main()
{
	CreateField();  
	DrawField(); 
	char c; 
	while (!EndOfGame())  
	{
		c = _getch();
		switch (c)  
		{
		case 75: Move(LEFT); 
		break;  
		case 72: Move(UP); 
		break; 
		case 77: Move(RIGHT); 
		break; 
		case 80: Move(DOWN); 
		break; 
		case 27: return 0; 
		}
		DrawField(); 
	}
	cout << "\n\nCongratulations! Press Enter to exit!";  
	cin.get();
}