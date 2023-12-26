#include <iostream>
#include <bits/stdc++.h>

// game variables
#define BOARD_SIZE 8
// state of board
long whitePawns;
long whiteKnights;
long whiteBishops;
long whiteRooks;
long whiteQueens;
long whiteKing;

long blackPawns;
long blackKnights;
long blackBishops;
long blackRooks;
long blackQueens;
long blackKing;

bool whitetomove;
int castlingRight;
int enpassantsquare;

// piece square table

float pawnTable[8][8] = {
	{0, 0, 0, 0, 0, 0, 0, 0},
	{1, 1, 1, 1, 1, 1, 1, 1},
	{0.5, 0.5, 1, 2, 2, 1, 0.5, 0.5},
	{0.2, 0.2, 0.4, 1, 1, 0.4, 0.2, 0.2},
	{0, 0, 0, 1, 1, 0, 0, 0},
	{0.2, -0.2, -0.4, 0, 0, -0.4, -0.2, 0.2},
	{0.2, 0.2, 0.4, -0.5, -0.5, 0.4, 0.2, 0.2},
	{0, 0, 0, 0, 0, 0, 0, 0}};

float blackPawnTable[8][8] = {
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0.2, 0.2, 0.4, -0.5, -0.5, 0.4, 0.2, 0.2},
	{0.2, -0.2, -0.4, 0, 0, -0.4, -0.2, 0.2},
	{0, 0, 0, 1, 1, 0, 0, 0},
	{0.2, 0.2, 0.4, 1, 1, 0.4, 0.2, 0.2},
	{0.5, 0.5, 1, 2, 2, 1, 0.5, 0.5},
	{1, 1, 1, 1, 1, 1, 1, 1},
	{0, 0, 0, 0, 0, 0, 0, 0}};

float knightTable[8][8] = {
	{-5, -4, -3, -3, -3, -3, -4, -5},
	{-4, -2, 0, 0.5, 0.5, 0, -2, -4},
	{-3, 0, 1, 1.5, 1.5, 1, 0, -3},
	{-3, 0.5, 1.5, 2, 2, 1.5, 0.5, -3},
	{-3, 0, 1.5, 2, 2, 1.5, 0, -3},
	{-3, 0.5, 1, 1.5, 1.5, 1, 0.5, -3},
	{-4, -2, 0, 0.5, 0.5, 0, -2, -4},
	{-5, -4, -3, -3, -3, -3, -4, -5}};

float bishopTable[8][8] = {
	{-2, -1, -1, -1, -1, -1, -1, -2},
	{-1, 0, 0, 0.5, 0.5, 0, 0, -1},
	{-1, 0, 0.5, 1, 1, 0.5, 0, -1},
	{-1, 0.5, 1, 1, 1, 1, 0.5, -1},
	{-1, 0, 1, 1, 1, 1, 0, -1},
	{-1, 1, 1, 1, 1, 1, 1, -1},
	{-1, 0.5, 0, 0, 0, 0, 0.5, -1},
	{-2, -1, -1, -1, -1, -1, -1, -2}};

float rookTable[8][8] = {
	{0, 0, 0, 1, 1, 0, 0, 0},
	{0, 0, 0, 1, 1, 0, 0, 0},
	{0, 0, 0, 1, 1, 0, 0, 0},
	{0, 0, 0, 1, 1, 0, 0, 0},
	{0, 0, 0, 1, 1, 0, 0, 0},
	{0, 0, 0, 1, 1, 0, 0, 0},
	{0, 0, 0, 1, 1, 0, 0, 0},
	{0, 0, 0, 1, 1, 0, 0, 0}};

float queenTable[8][8] = {
	{-2, -1, -1, -0.5, -0.5, -1, -1, -2},
	{-1, 0, 0, 0, 0, 0, 0, -1},
	{-1, 0, 0.5, 0.5, 0.5, 0.5, 0, -1},
	{-0.5, 0, 0.5, 0.5, 0.5, 0.5, 0, -0.5},
	{0, 0, 0.5, 0.5, 0.5, 0.5, 0, -0.5},
	{-1, 0.5, 0.5, 0.5, 0.5, 0.5, 0, -1},
	{-1, 0, 0.5, 0, 0, 0, 0, -1},
	{-2, -1, -1, -0.5, -0.5, -1, -1, -2}};

float kingTable[8][8] = {
	{-3, -4, -4, -5, -5, -4, -4, -3},
	{-3, -4, -4, -5, -5, -4, -4, -3},
	{-3, -4, -4, -5, -5, -4, -4, -3},
	{-3, -4, -4, -5, -5, -4, -4, -3},
	{-2, -3, -3, -4, -4, -3, -3, -2},
	{-1, -2, -2, -2, -2, -2, -2, -1},
	{2, 2, 0, 0, 0, 0, 2, 2},
	{2, 3, 1, 0, 0, 1, 3, 2}};

// all possible squares for pieces
std::vector<std::vector<int>> whiteBishopsMoves;
std::vector<std::vector<int>> whiteRooksMoves;
std::vector<std::vector<int>> whiteQueensMoves;
std::vector<std::vector<int>> whiteKingMoves;

std::vector<std::vector<int>> allCoveredSquareWhitePawns(int board[8][8])
{

	std::vector<std::vector<int>> whitePawnsMoves;
	for (int i = 1; i < 7; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			// check whether it is a pawn or not
			if (board[i][j] == 1)
			{
				// check for up and up+up square is covered or not
				if (board[i - 1][j] == 0)
				{
					whitePawnsMoves.push_back({i - 1, j});
				}
				if (board[i - 2][j] == 0)
				{
					whitePawnsMoves.push_back({i - 2, j});
				}
				// check for captures
				if (j >= 1 && board[i - 1][j - 1] == 0)
				{
					whitePawnsMoves.push_back({i - 1, j - 1});
				}
				if (j <= 6 && board[i - 1][j + 1] == 0)
				{
					whitePawnsMoves.push_back({i - 1, j + 1});
				}
			}
		}
	}

	return whitePawnsMoves;
}

std::vector<std::vector<int>> allCoveredSquareWhiteKnights(int board[8][8])
{

	std::vector<std::vector<int>> whiteKnightsMoves;

	// for knight moves
	int X[8] = {2, 1, -1, -2, -2, -1, 1, 2};
	int Y[8] = {1, 2, 2, 1, -1, -2, -2, -1};

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			// check whether it is a knight or not
			if (board[i][j] == 2)
			{

				// check for every move
				for (int k = 0; k < 8; k++)
				{
					int x = i + X[k];
					int y = j + Y[k];

					// count moves
					if (x >= 0 && y >= 0 && x < 8 && y < 8 && board[x][y] == '0')
					{
						whiteKnightsMoves.push_back({x, y});
					}
				}
			}
		}
	}
	return whiteKnightsMoves;
}

bool isBlackMated(int board[8][8])
{

	return 0;
}

bool isWhiteMated(int board[8][8])
{
	return 0;
}

float WhiteMaterial(int board[8][8])
{
	float totalwhite = 0;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (board[i][j] > 0)
			{
				totalwhite += board[i][j];
			}
		}
	}

	return totalwhite;
}

float BlackMaterial(int board[8][8])
{
	float totalblack = 0;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (board[i][j] < 0)
			{
				totalblack += board[i][j];
			}
		}
	}

	return totalblack;
}

float WhiteMaterialAdjusted(int board[8][8])
{
	float totalwhite = 0;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (board[i][j] > 0)
			{
				if (board[i][j] == 4)
				{
					totalwhite += rookTable[i][j] * board[i][j];
				}
				else if (board[i][j] == 2)
				{
					totalwhite += knightTable[i][j] * board[i][j];
				}
				else if (board[i][j] == 3)
				{
					totalwhite += bishopTable[i][j] * board[i][j];
				}
				else if (board[i][j] == 5)
				{
					totalwhite += queenTable[i][j] * board[i][j];
				}
				else if (board[i][j] == 6)
				{
					totalwhite += kingTable[i][j] * board[i][j];
				}
				else if (board[i][j] == 1)
				{
					totalwhite += pawnTable[i][j] * board[i][j];
				}
			}
		}
	}

	return totalwhite;
}

float BlackMaterialAdjusted(int board[8][8])
{
	float totalblack = 0;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (board[i][j] < 0)
			{
				if (board[i][j] == 4)
				{
					totalblack += rookTable[i][j] * board[i][j];
				}
				else if (board[i][j] == 2)
				{
					totalblack += knightTable[i][j] * board[i][j];
				}
				else if (board[i][j] == 3)
				{
					totalblack += bishopTable[i][j] * board[i][j];
				}
				else if (board[i][j] == 5)
				{
					totalblack += queenTable[i][j] * board[i][j];
				}
				else if (board[i][j] == 6)
				{
					totalblack += kingTable[i][j] * board[i][j];
				}
				else if (board[i][j] == 1)
				{
					totalblack += blackPawnTable[i][j] * board[i][j];
				}
			}
		}
	}

	return totalblack;
}

float evaluation(int board[8][8])
{

	if (isWhiteMated(board))
	{
		return 100;
	}
	if (isBlackMated(board))
	{
		return -100;
	}

	// calculate score
	float score = 0.0;
	score = WhiteMaterial(board);
	score += BlackMaterial(board);

	score += WhiteMaterialAdjusted(board);
	score += BlackMaterialAdjusted(board);

	// return
	return score;
}

void printboard(int board[8][8])
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			std::cout << board[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

int main()
{
	int board[8][8] = {
		{-4, -2, -3, -5, -6, -3, -2, -4},
		{-1, -1, -1, -1, -1, -1, -1, -1},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{1, 1, 1, 1, 1, 1, 1, 1},
		{4, 2, 3, 5, 6, 3, 2, 4}};

	// print the board
	printboard(board);

	// all white pawn moves
	std::vector<std::vector<int>> whitePawnsMoves = allCoveredSquareWhitePawns(board);
	for (const auto &any : whitePawnsMoves)
	{
		//	std::cout<<"Pawn : "<<any[0]<<","<<any[1]<<std::endl;
	}
	// std::cout<<"Total Pawns : "<<whitePawnsMoves.size()<<std::endl;

	std::vector<std::vector<int>> whiteKnightsMoves = allCoveredSquareWhiteKnights(board);
	for (const auto &any : whiteKnightsMoves)
	{
		//	std::cout<<"Knight : "<<any[0]<<","<<any[1]<<std::endl;
	}
	// std::cout<<"Total Knights : "<<whiteKnightsMoves.size()<<std::endl;

	// evaluation of board
	int eval = evaluation(board);

	std::cout << eval << std::endl;
}
