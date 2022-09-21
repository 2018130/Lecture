#include <stdio.h>
#include <windows.h>

void gotoxy(int x, int y);

int main(void)
{
	//int dan = 0;
	//printf("Dan Input : ");
	//scanf("%d", &dan);
	
	for(int i=1;i<=9;i++)
	{
		for(int j = 1; j < 10; j++){
			gotoxy(10 * i, j);
			printf("%d*%d=%2d",i,j,i*j);
		}
	}
	
	printf("\n");
	
	return 0;
}

void gotoxy(int x, int y)
{
	COORD Pos = {x - 1, y - 1};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}


//3´Ü Ãâ·Â

