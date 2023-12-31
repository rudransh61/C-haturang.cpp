#include <iostream>
#include <bits/stdc++.h>

// game variables
#define BOARD_SIZE 8

// score of pieces
#define PAWN 100
#define KNIGHT 320
#define BISHOP 330
#define ROOK 500
#define QUEEN 900
#define KING 20000

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
	{5, 10, 10, -20, -20, 10, 10, 5},
	{5, -5, -10, 0, 0, -10, -5, 5},
	{0, 0, 0, 20, 20, 0, 0, 0},
	{5, 5, 10, 25, 25, 10, 5, 5},
	{10, 10, 20, 30, 30, 20, 10, 10},
	{50, 50, 50, 50, 50, 50, 50, 50},
	{0, 0, 0, 0, 0, 0, 0, 0}};

float blackPawnTable[8][8] = {
	{0, 0, 0, 0, 0, 0, 0, 0},
	{50, 50, 50, 50, 50, 50, 50, 50},
	{10, 10, 20, 30, 30, 20, 10, 10},
	{5, 5, 10, 25, 25, 10, 5, 5},
	{0, 0, 0, 20, 20, 0, 0, 0},
	{-5, -5, -10, 0, 0, -10, -5, 5},
	{5, 10, 10, -20, -20, 10, 10, 5},
	{0, 0, 0, 0, 0, 0, 0, 0}};

float knightTable[8][8] = {
	{-50, -40, -30, -30, -30, -30, -40, -50},
	{-40, -20, 0, 5, 5, 0, -20, -40},
	{-30, 5, 10, 15, 15, 10, 5, -30},
	{-30, 0, 15, 20, 20, 15, 0, -30},
	{-30, 5, 15, 20, 20, 15, 5, -30},
	{-30, 0, 10, 15, 15, 10, 0, -30},
	{-40, -20, 0, 0, 0, 0, -20, -40},
	{-50, -40, -30, -30, -30, -30, -40, -50}};

float blackKnightTable[8][8] = {
	{-50, -40, -30, -30, -30, -30, -40, -50},
	{-40, -20, 0, 0, 0, 0, -20, -40},
	{-30, 0, 10, 15, 15, 10, 0, -30},
	{-30, 5, 15, 20, 20, 15, 5, -30},
	{-30, 0, 15, 20, 20, 15, 0, -30},
	{-30, 5, 10, 15, 15, 10, 5, -30},
	{-40, -20, 0, 5, 5, 0, -20, -40},
	{-50, -40, -30, -30, -30, -30, -40, -50}};

float bishopTable[8][8] = {
	{-20, -10, -10, -10, -10, -10, -10, -20},
	{-10, 5, 0, 0, 0, 0, 5, -10},
	{-10, 10, 10, 10, 10, 10, 10, -10},
	{-10, 0, 10, 10, 10, 10, 0, -10},
	{-10, 5, 5, 10, 10, 5, 5, -10},
	{-10, 0, 5, 10, 10, 5, 0, -10},
	{-10, 0, 0, 0, 0, 0, 0, -10},
	{-20, -10, -10, -10, -10, -10, -10, -20}};

float blackBishopTable[8][8] = {
	{-20, -10, -10, -10, -10, -10, -10, -20},
	{-10, 0, 0, 0, 0, 0, 0, -10},
	{-10, 0, 5, 10, 10, 5, 0, -10},
	{-10, 5, 5, 10, 10, 5, 5, -10},
	{-10, 0, 10, 10, 10, 10, 0, -10},
	{-10, 10, 10, 10, 10, 10, 10, -10},
	{-10, 5, 0, 0, 0, 0, 5, -10},
	{-20, -10, -10, -10, -10, -10, -10, -20}};

float rookTable[8][8] = {
	{0, 0, 0, 5, 5, 0, 0, 0},
	{-5, 0, 0, 0, 0, 0, 0, -5},
	{-5, 0, 0, 0, 0, 0, 0, -5},
	{-5, 0, 0, 0, 0, 0, 0, -5},
	{-5, 0, 0, 0, 0, 0, 0, -5},
	{-5, 0, 0, 0, 0, 0, 0, -5},
	{5, 10, 10, 10, 10, 10, 10, 5},
	{0, 0, 0, 0, 0, 0, 0, 0}};

float blackRookTable[8][8] = {
	{0, 0, 0, 0, 0, 0, 0, 0},
	{5, 10, 10, 10, 10, 10, 10, 5},
	{-5, 0, 0, 0, 0, 0, 0, -5},
	{-5, 0, 0, 0, 0, 0, 0, -5},
	{-5, 0, 0, 0, 0, 0, 0, -5},
	{-5, 0, 0, 0, 0, 0, 0, -5},
	{-5, 0, 0, 0, 0, 0, 0, -5},
	{0, 0, 0, 5, 5, 0, 0, 0}};

float queenTable[8][8] = {
	{-20, -10, -10, -5, -5, -10, -10, -20},
	{-10, 0, 5, 0, 0, 0, 0, -10},
	{-10, 5, 5, 5, 5, 5, 0, -10},
	{0, 0, 5, 5, 5, 5, 0, -5},
	{-5, 0, 5, 5, 5, 5, 0, -5},
	{-10, 0, 5, 5, 5, 5, 0, -10},
	{-10, 0, 0, 0, 0, 0, 0, -10},
	{-20, -10, -10, -5, -5, -10, -10, -20}};

float blackQueenTable[8][8] = {
	{-20, -10, -10, -5, -5, -10, -10, -20},
	{-10, 0, 0, 0, 0, 0, 0, -10},
	{-10, 0, 5, 5, 5, 5, 0, -10},
	{-5, 0, 5, 5, 5, 5, 0, -5},
	{0, 0, 5, 5, 5, 5, 0, -5},
	{-10, 5, 5, 5, 5, 5, 0, -10},
	{-10, 0, 5, 0, 0, 0, 0, -10},
	{-20, -10, -10, -5, -5, -10, -10, -20}};

float blackKingTable[8][8] = {
	{-30, -40, -40, -50, -50, -40, -40, -30},
	{-30, -40, -40, -50, -50, -40, -40, -30},
	{-30, -40, -40, -50, -50, -40, -40, -30},
	{-30, -40, -40, -50, -50, -40, -40, -30},
	{-20, -30, -30, -40, -40, -30, -30, -20},
	{-10, -20, -20, -20, -20, -20, -20, -10},
	{20, 20, 0, 0, 0, 0, 20, 20},
	{20, 30, 10, 0, 0, 10, 30, 20}};

float kingTable[8][8] = {
	{20, 30, 10, 0, 0, 10, 30, 20},
	{20, 20, 0, 0, 0, 0, 20, 20},
	{-10, -20, -20, -20, -20, -20, -20, -10},
	{-20, -30, -30, -40, -40, -30, -30, -20},
	{-30, -40, -40, -50, -50, -40, -40, -30},
	{-30, -40, -40, -50, -50, -40, -40, -30},
	{-30, -40, -40, -50, -50, -40, -40, -30},
	{-30, -40, -40, -50, -50, -40, -40, -30}};

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
			if (board[i][j] == 4)
				{
					totalwhite +=  ROOK;
				}
				else if (board[i][j] == 2)
				{
					totalwhite += KNIGHT;
				}
				else if (board[i][j] == 3)
				{
					totalwhite +=  BISHOP;
				}
				else if (board[i][j] == 5)
				{
					totalwhite +=  QUEEN;
				}
				else if (board[i][j] == 6)
				{
					totalwhite +=  KING;
				}
				else if (board[i][j] == 1)
				{
					totalwhite +=  PAWN;
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
			if (board[i][j] == -4)
				{
					totalblack +=  ROOK;
				}
				else if (board[i][j] == -2)
				{
					totalblack += KNIGHT;
				}
				else if (board[i][j] == -3)
				{
					totalblack +=  BISHOP;
				}
				else if (board[i][j] == -5)
				{
					totalblack +=  QUEEN;
				}
				else if (board[i][j] == -6)
				{
					totalblack +=  KING;
				}
				else if (board[i][j] == -1)
				{
					totalblack +=  PAWN;
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
					totalwhite += rookTable[i][j] * ROOK;
				}
				else if (board[i][j] == 2)
				{
					totalwhite += knightTable[i][j] * KNIGHT;
				}
				else if (board[i][j] == 3)
				{
					totalwhite += bishopTable[i][j] * BISHOP;
				}
				else if (board[i][j] == 5)
				{
					totalwhite += queenTable[i][j] * QUEEN;
				}
				else if (board[i][j] == 6)
				{
					totalwhite += kingTable[i][j] * KING;
				}
				else if (board[i][j] == 1)
				{
					totalwhite += pawnTable[i][j] * PAWN;
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
				if (board[i][j] == -4)
				{
					totalblack += blackRookTable[i][j] * ROOK;
				}
				else if (board[i][j] == -2)
				{
					totalblack += blackKnightTable[i][j] * KNIGHT;
				}
				else if (board[i][j] == -3)
				{
					totalblack += blackBishopTable[i][j] * BISHOP;
				}
				else if (board[i][j] == -5)
				{
					totalblack += blackQueenTable[i][j] * QUEEN;
				}
				else if (board[i][j] == -6)
				{
					totalblack += blackKingTable[i][j] * KING;
				}
				else if (board[i][j] == -1)
				{
					totalblack += blackPawnTable[i][j] * PAWN;
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
	score -= BlackMaterial(board);

	score += WhiteMaterialAdjusted(board);
	score -= BlackMaterialAdjusted(board);

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
		{-4, -2, -3, -6, -5, -3, -2, -4},
		{-1, -1, -1, -1, -1, -1, -1, -1},
		{0, 0, 0, 0,0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{1, 1, 1, 1, 1, 1, 1, 1},
		{4, 2, 3, 6, 5, 3, 2, 4}};
	int board2[8][8]={
		{0,2,0,0,-3,0,0,0},
		{0,0,0,0,0,0,-3,0},
		{0,0,0,-6,0,0,0,-1},
		{-4,0,4,1,0,1,0,0},
		{0,0,1,0,3,0,0,-1},
		{-5,0,0,1,6,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,-2,0,0,0,0,0}
	};
	// print the board
	std::cout<<"BOARD 1"<<std::endl;
	printboard(board);
	std::cout<<"BOARD 2"<<std::endl;
	printboard(board2);

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
	int eval2 = evaluation(board2);
	std::cout << "Evaluation of this position : " << eval << std::endl;
	std::cout << "Evaluation 2nd of this position : " << eval2 << std::endl;
	
}
