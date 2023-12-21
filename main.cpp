#include<iostream>
#include<bits/stdc++.h>

// game variables
#define BOARD_SIZE 8

#define PAWN   0
#define KNIGHT 1
#define BISHOP 2
#define ROOK   3
#define QUEEN  4
#define KING   5

/* board representation */
#define WHITE  0
#define BLACK  1

#define WHITE_PAWN      (2*PAWN   + WHITE)
#define BLACK_PAWN      (2*PAWN   + BLACK)
#define WHITE_KNIGHT    (2*KNIGHT + WHITE)
#define BLACK_KNIGHT    (2*KNIGHT + BLACK)
#define WHITE_BISHOP    (2*BISHOP + WHITE)
#define BLACK_BISHOP    (2*BISHOP + BLACK)
#define WHITE_ROOK      (2*ROOK   + WHITE)
#define BLACK_ROOK      (2*ROOK   + BLACK)
#define WHITE_QUEEN     (2*QUEEN  + WHITE)
#define BLACK_QUEEN     (2*QUEEN  + BLACK)
#define WHITE_KING      (2*KING   + WHITE)
#define BLACK_KING      (2*KING   + BLACK)
#define EMPTY           (BLACK_KING  +  1)

#define PCOLOR(p) ((p)&1)

int side2move;
int board[64];

#define FLIP(sq) ((sq)^56)
#define OTHER(side) ((side)^ 1)

int mg_value[6] = { 82, 337, 365, 477, 1025,  0 };
int eg_value[6] = { 94, 281, 297, 512,  936,  0 };

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


void init_tables()
{
	int pc, p, sq;
	for (p = PAWN, pc = WHITE_PAWN; p <= KING; pc += 2, p++) {
		for (sq = 0; sq < 64; sq++) {
			mg_table[pc]  [sq] = mg_value[p] + mg_pesto_table[p][sq];
			eg_table[pc]  [sq] = eg_value[p] + eg_pesto_table[p][sq];
			mg_table[pc+1][sq] = mg_value[p] + mg_pesto_table[p][FLIP(sq)];
			eg_table[pc+1][sq] = eg_value[p] + eg_pesto_table[p][FLIP(sq)];
																        
		}
			    
	}
		
}

// all possible squares for pieces
std::vector<std::vector<int>> whiteBishopsMoves;
std::vector<std::vector<int>> whiteRooksMoves;
std::vector<std::vector<int>> whiteQueensMoves;
std::vector<std::vector<int>> whiteKingMoves;

std::vector<std::vector<int>> allCoveredSquareWhitePawns(int board[8][8]){
	
	std::vector<std::vector<int>> whitePawnsMoves;	
	for(int i=1;i<7;i++){
		for(int j=0;j<8;j++){
			// check whether it is a pawn or not	
			if(board[i][j]==1){
				// check for up and up+up square is covered or not
				if(board[i-1][j]==0){
					whitePawnsMoves.push_back({i-1,j});
				}
				if(board[i-2][j]==0){
					whitePawnsMoves.push_back({i-2,j});
				}
				//check for captures
				if(j>=1 && board[i-1][j-1]==0){
					whitePawnsMoves.push_back({i-1,j-1});
				}
				if(j<=6 && board[i-1][j+1]==0){
					whitePawnsMoves.push_back({i-1,j+1});
				}
				
			}

		}
	}

	return whitePawnsMoves;
}

std::vector<std::vector<int>> allCoveredSquareWhiteKnights(int board[8][8]){
	
	std::vector<std::vector<int>> whiteKnightsMoves;
		
	// for knight moves
	int X[8] = {2 , 1 , -1 , -2 , -2 , -1 , 1 , 2};
	int Y[8] = { 1, 2 , 2 , 1,-1,-2,-2,-1 };

	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			// check whether it is a knight or not
			if(board[i][j]==2){
				
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
	return whiteKnightsMoves;

}


bool isBlackMated(int board[8][8]){


	return 0;

}

bool isWhiteMated(int board[8][8]){
	return 0;
}


float evaluation(int board[8][8]){

	//calculate score
	
int mg[2];
    int eg[2];
	    int gamePhase = 0;

		    mg[WHITE] = 0;
			    mg[BLACK] = 0;
				    eg[WHITE] = 0;
					    eg[BLACK] = 0;

						    /* evaluate each piece */
						for (int sq = 0; sq < 64; ++sq) {
							        int pc = board[sq];
									if (pc != EMPTY) {
										            mg[PCOLOR(pc)] += mg_table[pc][sq];
													            eg[PCOLOR(pc)] += eg_table[pc][sq];
																            gamePhase += gamephaseInc[pc];
																			        
									}
									    
						}

						    /* tapered eval */
						    int mgScore = mg[side2move] - mg[OTHER(side2move)];
							    int egScore = eg[side2move] - eg[OTHER(side2move)];
								    int mgPhase = gamePhase;
									    if (mgPhase > 24) mgPhase = 24; /* in case of early promotion */
										    int egPhase = 24 - mgPhase;
											    return (mgScore * mgPhase + egScore * egPhase) / 24;




	// return 
	return score;


}


void printboard(int board[8][8]){
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			std::cout<<board[i][j]<<" ";
		}
		std::cout<<std::endl;
	}
}


int main(){
	int board[8][8]={
		{-4,-2,-3,-5,-6,-3,-2,-4},
		{-1,-1,-1,-1,-1,-1,-1,-1},
		{ 0, 0, 0, 0, 0, 0, 0, 0},
		{ 0, 0, 0, 0, 0, 0, 0, 0},
		{ 0, 0, 0, 0, 0, 0, 0, 0},
		{ 0, 0, 0, 0, 0, 0, 0, 0},
		{ 1, 1, 1, 1, 1, 1, 1, 1},
		{ 4, 2 ,3, 5, 6, 3, 2, 4}	
	};
	
	//print the board
	printboard(board);


	// all white pawn moves
	std::vector<std::vector<int>> whitePawnsMoves = allCoveredSquareWhitePawns(board);
	for(const auto& any : whitePawnsMoves){
		std::cout<<"Pawn : "<<any[0]<<","<<any[1]<<std::endl;
	}
	std::cout<<"Total Pawns : "<<whitePawnsMoves.size()<<std::endl;
	
	std::vector<std::vector<int>> whiteKnightsMoves = allCoveredSquareWhiteKnights(board);
	for(const auto& any : whiteKnightsMoves){
		std::cout<<"Knight : "<<any[0]<<","<<any[1]<<std::endl;
	}
	std::cout<<"Total Knights : "<<whiteKnightsMoves.size()<<std::endl;
		
	// evaluation of board
	int eval = evaluation(board);
	
	std::cout<<eval<<std::endl;
}
