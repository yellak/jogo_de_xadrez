#include "../include/interface.h"
#include "stdlib.h"
#include "../include/logica.h"

int main(){
	/* Inicializando o tabuleiro básico */
	TBoard* board = AlocateBoard();
	StartEmptyBoard(board);
	board->Board[4][4] = W_TOWER;
//	ListOfMoves* list = CreateListOfMoves();
//	list = TowerMovements(board, list, 4, 4);
//	printf("%d\n", list->howmany);

	return 0;
}

/*
char peace;
	int k;
	if(board == NULL || AllMoves == NULL){
		return NULL;
	}

	peace = WhatPiece(board, originx, originy);
	for(k = 1; k<8; k++){
		if(peace < BLANK){
			if(originx + k <= 7 && board->Board[originx + k][originy] >= BLANK){
				InsertMove(AllMoves, originx, originy, originx + k, originy);
			}
			if(originx - k >= 0 && board->Board[originx - k][originy] >= BLANK){
				InsertMove(AllMoves, originx, originy, originx - k, originy);
			}
			if(originy + k <= 7 && board->Board[originx][originy + k] >= BLANK){
				InsertMove(AllMoves, originx, originy, originx, originy + k);
			}
			if(originy - k >= 0 && board->Board[originx][originy - k] >= BLANK){
				InsertMove(AllMoves, originx, originy, originx, originy - k);				
			}
		}
		else if(peace > BLANK){
			if(originx + k <= 7 && board->Board[originx + k][originy] <= BLANK){
				InsertMove(AllMoves, originx, originy, originx + k, originy);
			}
			if(originx - k >= 0 && board->Board[originx - k][originy] <= BLANK){
				InsertMove(AllMoves, originx, originy, originx - k, originy);
			}
			if(originy + k <= 7 && board->Board[originx][originy + k] <= BLANK){
				InsertMove(AllMoves, originx, originy, originx, originy + k);
			}
			if(originy - k >= 0 && board->Board[originx][originy - k] <= BLANK){
				InsertMove(AllMoves, originx, originy, originx, originy - k);			
			}
		}
	}
	return AllMoves;
*/