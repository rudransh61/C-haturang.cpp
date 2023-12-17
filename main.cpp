#include<iostream>
#include<bits/stdc++.h>

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

// all possible squares for pieces
std::vector<std::vector<int>> whitePawnsMoves;
std::vector<std::vector<int>> whiteKnightsMoves;
std::vector<std::vector<int>> whiteBishopsMoves;
std::vector<std::vector<int>> whiteRooksMoves;
std::vector<std::vector<int>> whiteQueensMoves;
std::vector<std::vector<int>> whiteKingMoves;

void allCoveredSquareWhitePawns(char board[8][8]){
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			// check whether it is a pawn or not	
			if(board[i][j]=='1'){
				// check for up and up+up square is covered or not
				if(board[i-1][j]=='0'){
					whitePawnsMoves.push_back({i-1,j});
				}
				if(board[i-2][j]=='0'){
					whitePawnsMoves.push_back({i-2,j});
				}
			}
		}
	}
}

void allCoveredSquareWhiteKnight(char board[8][8]){
	
	// for knight moves
	int X[8] = {2 , 1 , -1 , -2 , -2 , -1 , 1 , 2};
	int Y[8] = { 1, 2 , 2 , 1,-1,-2,-2,-1 };

	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			// check whether it is a knight or not
			if(board[i][j]=='2'){
				
				// check for every move
				for(int k=0;k<8;k++){
					int x = i + X[k];
					int y = j + Y[k];

					// count moves
					if( x>=0 && y>=0 && x<8 && y<8 && board[x][y]=='0'){
						whiteKnightsMoves.push_back({x,y});	
					}
				}

			}
		}
	}
}


bool isBlackMated(char board[8][8]){


	return 0;

}

bool isWhiteMated(char board[8][8]){
	return 0;
}


float evaluation(char board[8][8]){

	if(isWhiteMated(board)){
		return 1000;
	}
	if(isBlackMated(board)){
		return -1000;
	}

	float score = 0.0;

	//calculate score
	





	// return 
	return score;


}


void printboard(char board[8][8]){
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			std::cout<<board[i][j]<<" ";
		}
		std::cout<<std::endl;
	}
}


int main(){
	char board[8][8]={
		{-4,-2,-3,-5,-6,-3,-2,-4},
		{-1,-1,-1,-1,-1,-1,-1,-1},
		{ 0, 0, 0, 0, 0, 0, 0, 0},
		{ 0, 0, 0, 0, 0, 0, 0, 0},
		{ 0, 0, 0, 0, 0, 0, 0, 0},
		{ 0, 0, 0, 0, 0, 0, 0, 0},
		{ 1, 1, 1, 1, 1, 1, 1, 1},
		{ 4, 2 ,3, 5, 6, 3, 2, 4}	
	};

	printboard(board);


	// all white pawn moves
	allCoveredSquareWhitePawns(board);
	for(any : whitePawnsMoves){
		for(squares : any){
			std::cout<<squares[0]<<","squares[1]<<std::endl;
		}
	}
	
	// evaluation of board
	float eval = evaluation(board);
	
	std::cout<<eval<<std::endl;
}
