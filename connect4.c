/* ENGGEN131 Project - C Project - 2018 */
/* Connect Four */

#include "connect4.h"

/*
name: Harpreet Singh
student ID: 819582012
upi: hsin849
*/

/*swap(helper function) --> to swap two values in an array.*/
void swap(double *val, int i, int j)
{
	double temp = val[i];
	val[i] = val[j];
	val[j] = temp;
}

/*bubble(helper function) --> to bring the smallest value at position 0
                              in an array.*/ 
void bubble(double *vals, int length)
{
	int i;
	for (i = 0; i < length - 1; i++)
	{
		if (vals[i] > vals[i + 1])
		{
			swap(vals, i, i + 1);
		}
	}
}

/*sort(helper function) --> to sort the elements of an array in 
                            increasing order*/
void sort(double *vals, int length)
{
	int i;
	for (i = 0; i < length; i++)
	{
		bubble(vals, length);
	}
}


/*SecondPlacePrize --> inputs => int prize1, int prize2, int prize3.
                       output => int a which is the second largest integer
					             out of the three inputs.*/
int SecondPlacePrize(int prize1, int prize2, int prize3)
{
	int a = 0;
	if ((prize1 <= prize2 && prize2 <= prize3) || (prize3 <= prize2 && prize2 <= prize1))
	{
		a = prize2;
	}
	if ((prize1 <= prize3 && prize3 <= prize2) || (prize2 <= prize3 && prize3 <= prize1))
	{
		a = prize3;
	}
	if ((prize3 <= prize1 && prize1 <= prize2) || (prize2 <= prize1 && prize1 <= prize3))
	{
		a = prize1;
	}
	return a;
}


/*FourInARow --> inputs => an array(values) and its integer length(length).
                 output => index position of the first element in the array 
				           that begins a four-in-arow sequence (int b).
						   If no sequence found, returns -1.*/
int FourInARow(int values[], int length)
{
	int a = 0;
	int b = 0;
	for (int i = 0; i < length; i++)
	{

		int j = i;
		a = 1;
		if (i > 0 && values[i] == values[i - 1])
		{
			while (values[j] == values[j - 1] && j < length)
			{
				j++;
				a++;
				if (a == 2)
				{
					b = j - 2;
				}
			}
			if (a >= 4)
			{
				i = length;
			}
		}
	}

	if (a >= 4)
	{
		return b;
	}

	else
	{
		return -1;
	}
}


/*BinaryToDecimal --> converts an integer array representing a binary number
                      into it's dedcimal equivalent.*/
int BinaryToDecimal(int binary)
{
	int rem = 0;
	int val = 0;
	int base = 1;
	while (binary >= 1)
	{
		rem = binary % 10;
		val = val + rem * base;
		binary = binary / 10;
		base = base * 2;
	}

	return val;
}


/*MedianAbility --> Takes a double array and its length as inputs and returns 
                    the median of all elements of that array.*/
double MedianAbility(double abilities[], int length)
{
	sort(abilities, length);
	if (length % 2 == 1)
	{
		return abilities[length / 2];
	}
	else
	{
		return ((abilities[(length / 2) - 1] + abilities[length / 2]) / 2);
	}
}


/*RemoveSpaces --> Takes a string as input.
                   Modifies the string by removing space characters such that no two
                   space characters remain in a row.*/
void RemoveSpaces(char *name)
{
	int i = 0;
	int j = 0;
	while (name[j] != '\0')
	{
		j++;
	}
	while (i <= j - 1)
	{
		int n1 = name[i];
		int n2 = name[i + 1];
		if (n1 == 32 && n2 == 32)
		{
			int k;
			for (k = i; k <= j - 1; k++)
			{
				name[k + 1] = name[k + 2];
			}
			j = j - 1;
			i = -1;
		}
		i++;
	}
}



/*InitialsiseBoard --> Creates a 10x10 2-dimensional array, and sets each 
                       element of the array to -1. Initialises the connect4
					   board so that the board has every element as 0 except
					   the center elements which it sets as 3.*/
void InitialiseBoard(int board[MAX_SIZE][MAX_SIZE], int size)
{
	int i, j;
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			board[i][j] = 0;
		}
	}

	/*checks if size is even and sets the single center element as 3
	  if size is not even, sets the center 4 elements to 3.*/
	if (size % 2 == 1)
	{
		board[(size - 1) / 2][(size - 1) / 2] = 3;
	}
	else
	{
		board[(size - 2) / 2][(size - 2) / 2] = 3;
		board[(size - 2) / 2][(size) / 2] = 3;
		board[(size) / 2][(size - 2) / 2] = 3;
		board[(size) / 2][(size) / 2] = 3;
	}
}


/*AddMoveToBoard --> Adds the required player move to the board with repect to
                     the game rules.*/
void AddMoveToBoard(int board[MAX_SIZE][MAX_SIZE], int size, char side, int move, int player, int *lastRow, int *lastCol)
{
	int i;
	
	/*drops an element respective to the side and move and pleces it before the next non 
	zero element.*/
	if (side == 'N' && board[0][move] == 0)
	{
		i = 0;
		while (board[i + 1][move] == 0 && i < size - 1)
		{
			i++;
		}

		board[i][move] = player;
		*lastRow = i;
		*lastCol = move;
	}
	if (side == 'S' && board[size - 1][move] == 0)
	{
		i = size - 1;
		while (board[i - 1][move] == 0 && i > 0)
		{
			i--;
		}

		board[i][move] = player;
		*lastRow = i;
		*lastCol = move;
	}
	if (side == 'E' && board[move][size - 1] == 0)
	{
		i = size - 1;
		while (board[move][i - 1] == 0 && i > 0)
		{
			i--;
		}

		board[move][i] = player;
		*lastRow = move;
		*lastCol = i;
	}
	if (side == 'W' && board[move][0] == 0)
	{
		i = 0;
		while (board[move][i + 1] == 0 && i < size - 1)
		{
			i++;
		}

		board[move][i] = player;
		*lastRow = move;
		*lastCol = i;
	}
	
	/*if no move was possible, returns -1.*/
	if ((side == 'N' && board[0][move] != 0) || (side == 'S' && board[size - 1][move] != 0) || (side == 'E' && board[move][size - 1] != 0) || (side == 'W' && board[move][0] != 0))
	{
		*lastRow = -1;
		*lastCol = -1;
	}
}



/*CheckGameOver --> Checks if a palyer has won the game and returns the player number.*/
int CheckGameOver(int board[MAX_SIZE][MAX_SIZE], int size, int player, int row, int col)
{
	int i, j, b, m;
	int a = 0;
	row = row + 1 - 1;
	col = col + 1 - 1;
	
	/*checking whether there are any four same elements together, either horizontal,
	 vertical, or diagonal.*/
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			m = 0;
			if (board[i][j] == board[i + 1][j + 1] && board[i][j] != 0 && board[i][j] != 3 && i <= size - 4 && j <= size - 4)
			{

				for (b = 0; b < 4; b++)
				{
					if (board[i][j] == board[i + b][j + b] && board[i][j] != 0)
					{
						m++;
					}
					if (m >= 4)
					{
						return board[i][j];
					}
				}
			}

			m = 0;
			if (board[i][j] == board[i + 1][j - 1] && board[i][j] != 0 && board[i][j] != 3 && i <= size - 4 && j >= 3)
			{

				for (b = 0; b < 4; b++)
				{
					if (board[i][j] == board[i + b][j - b] && board[i][j] != 0)
					{
						m++;
					}
					if (m >= 4)
					{
						return board[i][j];
					}
				}
			}

			m = 0;
			if (board[i][j] == board[i + 1][j] && board[i][j] != 0 && board[i][j] != 3 && i <= size - 4)
			{

				for (b = 0; b < 4; b++)
				{
					if (board[i][j] == board[i + b][j])
					{
						m++;
					}
					if (m >= 4)
					{
						return board[i][j];
					}
				}
			}

			m = 0;
			if (board[i][j] == board[i][j + 1] && board[i][j] != 0 && board[i][j] != 3 && j <= size - 4)
			{

				for (b = 0; b < 4; b++)
				{
					if (board[i][j] == board[i][j + b])
					{
						m++;
					}
					if (m >= 4)
					{
						return board[i][j];
					}
				}
			}

			if (board[i][j] == 0)
			{
				a++;
			}
		}
	}

	/*returning player of last move if there is no space to add a valid move.*/
	if (a == 0)
	{
		return player;
	}
	
	else
	{
		return 0;
	}
}


/*GetDisplayBoardString --> takes boardstring as an input and converts it into a string
                            which represents the board.
							
							Calculation process: every new line starts at an integer multiple
							of (size + 5) as every element at an integer multiple of (size + 4)
							is '\n'. The last element is '\0'.*/
void GetDisplayBoardString(int board[MAX_SIZE][MAX_SIZE], int size, char *boardString)
{
	for (int m = 0; m < 220; m++)
	{
		boardString[m] = -1;
	}
	int i, j, k;
	
	for (i = 0; i < size + 5; i++)
	{
		/*adding '-' at corners.*/
		if (i == 0 || i == 1 || i == size + 3 || i == size + 2)
		{
			boardString[i] = '-';
			boardString[i + size + 5] = '-';
			boardString[i + (size + 5) * (size + 2)] = '-';
			boardString[i + (size + 5) * (size + 3)] = '-';
		}

		
		/*adding all sides(N,S,E,W) , move numbers , and '\n'.*/
		else if (i >= 2 && i <= size + 1)
		{
			boardString[i] = 'N';
			boardString[i + (size + 5) * (size + 3)] = 'S';
		}

		else if (i == size + 4)
		{
			for (k = 0; k <= (size + 3); k++)
			{
				boardString[i + (size + 5) * k] = '\n';
			}
		}
	}

	for (j = 2; j <= (size + 1); j++)
	{
		boardString[(size + 5) * j] = 'W';
		boardString[(size + 5) * j + 1] = (char)(46 + j);
	}

	for (j = 2; j <= (size + 1); j++)
	{
		boardString[(size + 5) * j + size + 3] = 'E';
		boardString[(size + 5) * j + size + 2] = (char)(46 + j);
	}
	int num = 2;
	for (int n = 0; n < size; n++)
	{
		boardString[num + size + 5] = (char)(48 + n);
		boardString[num + (size + 5) * (size + 2)] = (char)(48 + n);
		num++;
	}

	for (int p = 0; p < size; p++)
	{
		for (int q = 0; q < size; q++)
		{
			if (board[p][q] == 0)
			{
				boardString[(size + 5) * (p + 2) + 2 + q] = '.';
			}
			if (board[p][q] == 1)
			{
				boardString[(size + 5) * (p + 2) + 2 + q] = 'X';
			}
			if (board[p][q] == 2)
			{
				boardString[(size + 5) * (p + 2) + 2 + q] = 'O';
			}
			if (board[p][q] == 3)
			{
				boardString[(size + 5) * (p + 2) + 2 + q] = '#';
			}
		}
	}

	boardString[(size + 5) * (size + 3) + size + 5] = '\0';
}


/*GetMoveBot1 --> it is passed the current board configuration as input, as
well as the size of the board, and which player the bot is controlling (this could be 1 or 2). Once
the bot has chosen where to place their token, this is indicated by writing the chosen move into
the pointers side and move (which are provided as input to the function).*/
void GetMoveBot1(int board[MAX_SIZE][MAX_SIZE], int size, int player, char *side, int *move)
{
	int i = 0, j = 0, cg, lr, lc, var = 0, ii, jj;
	char side2 = 'n';
	int arr[MAX_SIZE][MAX_SIZE];
	for (ii = 0; ii < size; ii++)
	{
		for (jj = 0; jj < size; jj++)
		{
			arr[ii][jj] = board[ii][jj];
		}
	}
	for (i = 0; i < 4; i++)
	{
		if (i == 0)
		{
			side2 = 'N';
		}
		if (i == 1)
		{
			side2 = 'S';
		}
		if (i == 2)
		{
			side2 = 'E';
		}
		if (i == 3)
		{
			side2 = 'W';
		}

		for (j = 0; j < size; j++)
		{
			AddMoveToBoard(arr, size, side2, j, player, &lr, &lc);
			cg = CheckGameOver(arr, size, player, lr, lc);
			if (lr >= 0 && lc >= 0)
			{

				if (cg == player)
				{
					*move = j;
					*side = side2;
					j = size;
					i = 4;
					var = 0;
					break;
				}
				else
				{
					var = 44;
				}
			}
			for (ii = 0; ii < size; ii++)
			{
				for (jj = 0; jj < size; jj++)
				{
					arr[ii][jj] = board[ii][jj];
				}
			}
		}
	}
	int mm = 0, aaa;
	if (var == 44)
	{
		for (aaa = 0; aaa < size; aaa++)
		{
			if (board[0][aaa] == 0)
			{
				*side = 'N';
				*move = aaa;
				mm = 44;
				break;
			}
		}
		if (mm != 44)
		{
			for (aaa = 0; aaa < size; aaa++)
			{
				if (board[size - 1][aaa] == 0)
				{
					*side = 'S';
					*move = aaa;
					mm = 44;
					break;
				}
			}
		}
		if (mm != 44)
		{
			for (aaa = 0; aaa < size; aaa++)
			{
				if (board[aaa][0] == 0)
				{
					*side = 'W';
					*move = aaa;
					mm = 44;
					break;
				}
			}
		}
		if (mm != 44)
		{
			for (aaa = 0; aaa < size; aaa++)
			{
				if (board[aaa][size - 1] == 0)
				{
					*side = 'E';
					*move = aaa;
					mm = 44;
					break;
				}
			}
		}
	}
}


/*GetMoveBot2 --> it is passed the current board configuration as input, as
well as the size of the board, and which player the bot is controlling (this could be 1 or 2). Once
the bot has chosen where to place their token, this is indicated by writing the chosen move into
the pointers side and move (which are provided as input to the function).*/
void GetMoveBot2(int board[MAX_SIZE][MAX_SIZE], int size, int player, char *side, int *move)
{
    int i = 0, j = 0, cg, lr, lc, var = 0, ii, jj;
	char side2 = 'n';
	int arr[MAX_SIZE][MAX_SIZE];
	for (ii = 0; ii < size; ii++)
	{
		for (jj = 0; jj < size; jj++)
		{
			arr[ii][jj] = board[ii][jj];
		}
	}
	for (i = 0; i < 4; i++)
	{
		if (i == 0)
		{
			side2 = 'N';
		}
		if (i == 1)
		{
			side2 = 'S';
		}
		if (i == 2)
		{
			side2 = 'E';
		}
		if (i == 3)
		{
			side2 = 'W';
		}

		for (j = 0; j < size; j++)
		{
			AddMoveToBoard(arr, size, side2, j, player, &lr, &lc);
			cg = CheckGameOver(arr, size, player, lr, lc);
			if (lr >= 0 && lc >= 0)
			{

				if (cg == player)
				{
					*move = j;
					*side = side2;
					j = size;
					i = 4;
					var = 0;
					break;
				}
				else
				{
					var = 44;
				}
			}
			for (ii = 0; ii < size; ii++)
			{
				for (jj = 0; jj < size; jj++)
				{
					arr[ii][jj] = board[ii][jj];
				}
			}
		}
	}
	int mm = 0, aaa;
	if (var == 44)
	{
		for (aaa = 0; aaa < size; aaa++)
		{
			if (board[0][aaa] == 0)
			{
				*side = 'N';
				*move = aaa;
				mm = 44;
				break;
			}
		}
		if (mm != 44)
		{
			for (aaa = 0; aaa < size; aaa++)
			{
				if (board[size - 1][aaa] == 0)
				{
					*side = 'S';
					*move = aaa;
					mm = 44;
					break;
				}
			}
		}
		if (mm != 44)
		{
			for (aaa = 0; aaa < size; aaa++)
			{
				if (board[aaa][0] == 0)
				{
					*side = 'W';
					*move = aaa;
					mm = 44;
					break;
				}
			}
		}
		if (mm != 44)
		{
			for (aaa = 0; aaa < size; aaa++)
			{
				if (board[aaa][size - 1] == 0)
				{
					*side = 'E';
					*move = aaa;
					mm = 44;
					break;
				}
			}
		}
	}
}
