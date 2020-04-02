/* 	Copyright (C) 2020 Sathira Silva
	Programming Methodology (CO222) - Project01 

	This program generates a QR Code for a given string (URL). */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* The possibilities for the text foreground color */
#define BLACK 	0
#define RED 	1
#define GREEN 	2
#define YELLOW 	3
#define BLUE 	4
#define MAGENTA 5
#define CYAN 	6
#define WHITE 	7

/* The possibilities of displaying help */
#define BASIC	0
#define FULL	1

int indexOf(char *string, char **array);
int contains(char *string, char **array);
void strip(char arr[], int length);
void reverse(char arr[], int start, int end);
void clearScreen();
void changeTextColor(int foregroundColor);
void resetColor();
void printBlock(int foregroundColor);
char *hash(char str[]);
void applyPadding(int grid[38][38], int gridSize);
void maskPositionIndicators(int grid[38][38], int gridSize);
void fillHashData(char *hashedStr, int grid[38][38], int gridSize);
void printHelp(char *programName, int type);


char *colors[7] = {"black", "red", "green", "yellow", "blue", "magenta", "cyan"};

const int SMALL[6][6] = {{-1, -1, 16, 17, -1, -1},
						 {-1, -1, 18, 19, -1, -1},
						 {20, 21,  0,  1,  2,  3},
						 {22, 23,  4,  5,  6,  7},
						 {-1, -1,  8,  9, 10, 11},
						 {-1, -1, 12, 13, 14, 15}};

const int BIG[12][12] = {{-1,   -1, 100, 101, 102, 103, 104, 105, 106, 107, -1, -1},
						 {-1,   -1, 108, 109, 110, 111, 112, 113, 114, 115, -1, -1},
						 {116, 117,   0,   1,   2,   3,   4,   5,   6,   7,  8,  9},
						 {118, 119,  10,  11,  12,  13,  14,  15,  16,  17, 18, 19},
						 {120, 121,  20,  21,  22,  23,  24,  25,  26,  27, 28, 29},
						 {122, 123,  30,  31,  32,  33,  34,  35,  36,  37, 38, 39},
						 {124, 125,  40,  41,  42,  43,  44,  45,  46,  47, 48, 49},
						 {126, 127,  50,  51,  52,  53,  54,  55,  56,  57, 58, 59},
						 {128, 129,  60,  61,  62,  63,  64,  65,  66,  67, 68, 69},
						 {130, 131,  70,  71,  72,  73,  74,  75,  76,  77, 78, 79},
						 { -1,  -1,  80,  81,  82,  83,  84,  85,  86,  87, 88, 89},
						 { -1,  -1,  90,  91,  92,  93,  94,  95,  96,  97, 98, 99}};

int indexOf(char *string, char **array)
{
	for (int i = 0; i < 7; i++)
	{
		if (!strcmp(array[i], string))
		{
			return i;
		}
	}
	return -1;
}

int contains(char *string, char **array)
{
	if (indexOf(string, array) != -1)
		return 1;
	return 0;
}

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

void changeTextColor(int foregroundColor)
{
	printf("%c[%dm", 0x1B, foregroundColor + 30);
}

void resetColor()
{
	printf("%c[0m", 0x1B);
}

void printBlock(int foregroundColor)
{
	printf("%c[%d;%dm%*c%c[0m", 0x1B, 30, 40 + foregroundColor, 2, ' ', 0x1B);
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

void applyPadding(int grid[38][38], int gridSize)
{
	for (int i = 0; i < gridSize; i++)
	{
		for (int j = 0; j < gridSize; j++)
		{
			grid[i][j] = 0;
		}
	}
}

void maskPositionIndicators(int grid[38][38], int gridSize)
{
	for (int j = 1; j < 7; j++)
	{
 		grid[1][j] = 1;
		grid[6][j] = 1;
		grid[1][gridSize - j - 1] = 1;
		grid[6][gridSize - j - 1] = 1;
		grid[gridSize - 7][j] = 1;
		grid[gridSize - 2][j] = 1;
	}
	for (int i = 2; i < 6; i++)
	{
		grid[i][1] = 1;
		grid[i][6] = 1;
		grid[i][gridSize - 7] = 1;
		grid[i][gridSize - 2] = 1;
		grid[gridSize - i - 1][1] = 1;
		grid[gridSize - i - 1][6] = 1;
	}
	grid[3][3] = 1;
	grid[3][4] = 1;
	grid[3][gridSize - 5] = 1;
	grid[3][gridSize - 4] = 1;
	grid[4][3] = 1;
	grid[4][4] = 1;
	grid[4][gridSize - 5] = 1;
	grid[4][gridSize - 4] = 1;
	grid[gridSize - 5][3] = 1;
	grid[gridSize - 5][4] = 1;
	grid[gridSize - 4][3] = 1;
	grid[gridSize - 4][4] = 1;
	
}

void fillHashData(char *hashedStr, int grid[38][38], int gridSize)
{
	if (gridSize == 20)
	{
		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 6; j++)
			{
				if (SMALL[i][j] != -1)
				{
					int val = (int)hashedStr[SMALL[i][j]];
					for (int k = 0; k < 3; k ++)
					{
						for (int l = 0; l < 3; l++)
						{
							grid[1 + 3 * i + k][1 + 3 * j + l] = (val >> (8 - (3 * k + l))) & 1;
						}
					}
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < 12; i++)
		{
			for (int j = 0; j < 12; j++)
			{
				if (BIG[i][j] != -1)
				{
					int val = (int)hashedStr[BIG[i][j]];
					for (int k = 0; k < 3; k ++)
					{
						for (int l = 0; l < 3; l++)
						{
							grid[1 + 3 * i + k][1 + 3 * j + l] = (val >> (8 - (3 * k + l))) & 1;
						}
					}
				}
			}
		}
	}
}

void printHelp(char *programName, int type)
{
	if (type == BASIC || type == FULL)
	{
		printf("Usage:\n");
		printf("  %s\n", programName);
		printf("  %s -c [black | red | green | yellow | blue | magenta | cyan]\n", programName);
		printf("  %s -h\n", programName);
	}
	if (type == FULL)
	{
		printf("\nOptions:\n");
		printf("  -c\tSpecify the foreground color for the QR.\n");
		printf("  -h\tShow this help screen.\n");
		printf("\nInput:\n");
		printf("  The length of the URL must be atleast 5 characters.\n\n");
	}
}

int main(int argc, char *argv[])
{
	int foregroundColor = BLACK;
	if (argc == 2)
	{
		if (!strcmp(argv[1], "-h"))
		{
			printf("\n");
			printHelp(argv[0], FULL);
			return 0;
		}
		else if (!strcmp(argv[1], "-c"))
		{
			changeTextColor(RED);
			printf("Missing 1 argument:\n");
			resetColor();
			printf("  Color must be specified just after the -c flag.\n\n");
			printHelp(argv[0], BASIC);
			return 0;
		}
		else
		{
			changeTextColor(RED);
			printf("Incorrect usage of arguments:\n");
			resetColor();
			printf("  View help for more details.\n\n");
			printHelp(argv[0], BASIC);
			return 0;
		}
	}
	else if (argc == 3)
	{
		if (!strcmp(argv[1], "-c") && contains(argv[2], colors))
		{
			foregroundColor = indexOf(argv[2], colors);
		}
		else if (!strcmp(argv[1], "-c") && !contains(argv[2], colors))
		{
			changeTextColor(RED);
			printf("Color undefined:\n");
			resetColor();
			printf("  View help for more details.\n\n");
			printHelp(argv[0], BASIC);
			return 0;
		}
		else
		{
			changeTextColor(RED);
			printf("Incorrect usage of arguments:\n");
			resetColor();
			printf("  View help for more details.\n\n");
			printHelp(argv[0], BASIC);
			return 0;
		}
	}
	else if (argc > 3)
	{
		changeTextColor(RED);
		printf("The arguments list is too long.\n\n");
		resetColor();
		printHelp(argv[0], BASIC);
		return 0;
	}
	char url[300];
	clearScreen();
	printf("Enter the URL: ");
	scanf("%s", url);
	if (strlen(url) < 5)
	{
		changeTextColor(RED);
		printf("URL too short:\n");
		resetColor();
		printf("  The minimum length of the URL is 5 characters.\n");
		return 0;
	}
	clearScreen();
	char *hashedStr = hash(url);
	int qrGridSize = (strlen(hashedStr) == 24) ? 20 : 38;
	int grid[38][38] = {{-1}};
	applyPadding(grid, qrGridSize);
	maskPositionIndicators(grid, qrGridSize);
	fillHashData(hashedStr, grid, qrGridSize);
	for (int i = 0; i < qrGridSize; i++)
	{
		for (int j = 0; j < qrGridSize; j++)
		{
			if (grid[i][j] == 0)
			{
				printBlock(WHITE);
			}
			else if (grid[i][j] == 1)
			{
				printBlock(foregroundColor);
			}
		}
		printf("\n");
	}
	printf("\n");
	return 0;
}
