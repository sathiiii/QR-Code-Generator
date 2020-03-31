#include "stdio.h"
#include "stdlib.h"

#define BLACK 0
#define RED 1
#define GREEN 2
#define YELLOW 3
#define BLUE 4
#define MAGENTA 5
#define CYAN 6
#define WHITE 7

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

void printBlock(int foregroundColor)
{
	printf("%c[%dm%c%c%c[0m", 0x1B, foregroundColor + 30, 219, 219, 0x1B);
}

/* void printHorizontalBar(int length, int foregroundColor)
{
	for (int i = 0; i < length; i++)
	{
		printBlock(foregroundColor);
	}
} */

/* void printPositionIndicator(int foregroundColor)
{
	printHorizontalBar(6, BLACK);
	printf("\n");
	printBlock(BLACK);
	printHorizontalBar(4, foregroundColor);
	printBlock(BLACK);
	printf("\n");
	printBlock(BLACK);
	printBlock(WHITE);
	printHorizontalBar(2, BLACK);
	printBlock(foregroundColor);
	printBlock(BLACK);
	printf("\n");
	printBlock(BLACK);
	printBlock(WHITE);
	printHorizontalBar(2, BLACK);
	printBlock(foregroundColor);
	printBlock(BLACK);
	printf("\n");
	printBlock(BLACK);
	printHorizontalBar(4, foregroundColor);
	printBlock(BLACK);
	printf("\n");
	printHorizontalBar(6, BLACK);
} */

void clearScreen()
{
	printf("\e[1;1H\e[2J");
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

int main(int argc, char *argv[])
{
	char url[120];
	clearScreen();
	printf("Enter the URL: ");
	scanf("%s", url);
	clearScreen();
	char *hashedStr = hash(url);
	int qrGridSize = (strlen(hashedStr) == 24) ? 18 : 36;
	/*
	This space is kept for the QR generation using the hashed string.
	*/
	return 0;
}
