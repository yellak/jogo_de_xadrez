#include "../include/interface.h"
#include "stdlib.h"
#include "../include/logica.h"

int main(){
	/* Inicializando o tabuleiro básico */
	TBoard* board = AlocateBoard();
	StartEmptyBoard(board);
	board->Board[4][4] = W_HORSE;
	ListOfMoves* list = AnalyzePossibleMovementsWhite(board);
	for(int i = 0; i < list->howmany; i++){
		printf("%d %d\n", list->first[i].play->origin[0], list->first[i].play->origin[1]);
		printf("%d %d\n", list->first[i].play->destiny[0], list->first[i].play->destiny[1]);
		printf("\n");
	}

	return 0;
}
