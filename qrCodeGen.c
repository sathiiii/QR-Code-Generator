#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLACK 0
#define RED 1
#define GREEN 2
#define YELLOW 3
#define BLUE 4
#define MAGENTA 5
#define CYAN 6
#define WHITE 7

const int SMALL[6][6] = {{-1, -1, 16, 17, -1, -1},
						 {-1, -1, 18, 19, -1, -1},
						 {20, 21, 0, 1, 2, 3},
						 {22, 23, 4, 5, 6, 7},
						 {-1, -1, 8, 9, 10, 11},
						 {-1, -1, 12, 13, 14, 15}};

const int BIG[12][12] = {{-1, -1, 100, 101, 102, 103, 104, 105, 106, 107, -1, -1},
						 {-1, -1, 108, 109, 110, 111, 112, 113, 114, 115, -1, -1},
						 {116, 117, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
						 {118, 119, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19},
						 {120, 121, 20, 21, 22, 23, 1, 1, 1, 1, 1, 2},
						 {122, 123, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3},
						 {124, 125, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5},
						 {126, 127, 5, 5, 5, 5, 5, 5, 5, 5, 5, 6},
						 {128, 129, 6, 6, 6, 6, 6, 6, 6, 6, 6, 7},
						 {130, 131, 7, 7, 7, 7, 7, 7, 7, 7, 7, 8},
						 {-1, -1, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9},
						 {-1, -1, 10, 10, 10, 10, 10, 10, 10, 10, 10, 99}};

void strip(char arr[], int length)
{
	if (strlen(arr) > length)
	{
		for (int i = length; i < strlen(arr); i++)
		{
			arr[i] = '\0';
		}
	}
}

void reverse(char arr[], int start, int end)
{
	for (int low = start, high = end; low < high; low++, high--)
	{
		char temp = arr[low];
		arr[low] = arr[high];
		arr[high] = temp;
	}
}

void clearScreen()
{
	printf("\e[1;1H\e[2J");
}

void printBlock(int foregroundColor)
{
	printf("%c[%dm%c%c%c[0m", 0x1B, foregroundColor + 30, 219, 219, 0x1B);
}

char *hash(char str[])
{
	int n = strlen(str);
	int hashLength = (n <= 20) ? 24 : 132;
	char *hashed = (char *)calloc(hashLength, sizeof(char));
	hashed[0] = n + 50;
	for (int i = 1; i < hashLength; i++)
	{
		hashed[i] = str[(i - 1) % n] + (i - 1) / n;
	}
	reverse(hashed, n + 1, hashLength - 1);
	strip(hashed, hashLength);
	return hashed;
}

void applyPadding(unsigned long long grid[38], int gridSize)
{
	grid[0] = 1;
	for (int i = 1; i < gridSize; i++)
	{
		grid[0] = (grid[0] << 1) | 1;
	}
	grid[gridSize - 1] = grid[0];
	for (int i = 1; i < gridSize - 1; i++)
	{
		grid[i] = (1 << (gridSize - 1)) | 1;
	}
}

void maskPositionIndicators(unsigned long long grid[38], int gridSize)
{
	grid[2] |= 15 << (gridSize - 6);
	grid[3] |= 9 << (gridSize - 6);
	grid[4] = grid[3];
	grid[5] |= grid[2];
	grid[gridSize - 3] = grid[2];
	grid[gridSize - 4] = grid[3];
	grid[gridSize - 5] = grid[3];
	grid[gridSize - 6] = grid[2];
	grid[2] |= 15 << 2;
	grid[3] |= 9 << 2;
	grid[4] = grid[3];
	grid[5] = grid[2];
}

int main(int argc, char *argv[])
{
	/* char url[120];
	clearScreen();
	printf("Enter the URL: ");
	scanf("%s", url);
	clearScreen();
	char *hashedStr = hash(url);
	int qrGridSize = (strlen(hashedStr) == 24) ? 18 + 2 : 36 + 2;
	unsigned long long grid[38];
	applyPadding(grid, qrGridSize);
	maskPositionIndicators(grid, qrGridSize); */

	for (int i = 0; i < 100; i++)
	{
		printf("%c[%d;%dm", 0x1B, 30, 47);
		printf(" ");
		printf("%c[0m", 0x1B);
	}

	return 0;
}
