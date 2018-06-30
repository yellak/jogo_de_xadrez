#include <stdio.h>
#include <stdlib.h>
#include "../include/logica.h"

/* Função: DeleteMoveList
		Objetivo: Liberar toda a memória da lista de movimentos.

		Parametros:
			list - Ponteiro para a estrutura da lista.
					Não deve ser nulo

		Saída: Retorna um inteiro indicando a falha ou sucesso da operação.
*/
int DeleteMoveList(ListOfMoves* list){
	if(list == NULL){
		return -1;
	}else{
		free(list->Plays);
		list->Plays = NULL;
		if(list->Plays == NULL){
			free(list);
			list = NULL;
			if(list == NULL){
				return 0;
			}else{
				return -1;
			}
		}else{
			return -1;
		}
	}
}

/* Função: AnalyzePossibleMovementsBlack
		Objetivo: Conseguir armazenar todas as possíveis jogadas para as peças brancas a partir de um tabuleiro.

		Parametros:
			board - Ponteiro para a estrutura da tabuleiro.
					Não deve ser nulo nem vazio

		Saída: Essa função retorna um arrays que contém os movimentos possíveis para com as peças brancas.
*/
ListOfMoves* AnalyzePossibleMovementsWhite(TBoard *board){

	/* Verificando se o tabuleiro é nulo */
	if(board == NULL){
		return NULL;
	}

	int i, j, size = 1;
	ListOfMoves* AllMoves = (ListOfMoves*) malloc(sizeof(ListOfMoves));
	AllMoves->Plays = (Move*) malloc(size*sizeof(Move));
	AllMoves->howmany = 0;

	/* Percorrendo o tabuleiro. */
	for(i=0; i < 8;i++){
		for(j=0; j < 8;j++){
			/* Casos para o peão black. */
			if(board->Board[i][j] == W_PAWN){
				/* Caso andar 2 estando na posição inicial. */
				if((i == 6 && board->Board[i - 2][j] == BLANK) && i - 2 >= 0){
					AllMoves->howmany = AllMoves->howmany + 1;
					size++;
					AllMoves->Plays = (Move*)realloc(AllMoves->Plays, size*sizeof(Move));
					AllMoves->Plays[size - 1].origin[0] = i;
					AllMoves->Plays[size - 1].origin[1] = j;
					AllMoves->Plays[size - 1].destiny[0] = i - 2;
					AllMoves->Plays[size - 1].destiny[1] = j;
				}
				/* Caso andar 1 estando na posição inicial/ andar normalmente. */
				if(((i == 6 && board->Board[i - 1][j] == BLANK) || board->Board[i - 1][j] == BLANK) && i - 1 >= 0){
					AllMoves->howmany = AllMoves->howmany + 1;
					size++;
					AllMoves->Plays = (Move*)realloc(AllMoves->Plays, size*sizeof(Move));
					AllMoves->Plays[size - 1].origin[0] = i;
					AllMoves->Plays[size - 1].origin[1] = j;
					AllMoves->Plays[size - 1].destiny[0] = i - 1;
					AllMoves->Plays[size - 1].destiny[1] = j;
				}
				/* Caso de eliminar peça sendo um peão na diagonal superior direita. */
				if(board->Board[i - 1][j + 1] < BLANK && i - 1 >=0 && j + 1 <= 7){
					AllMoves->howmany = AllMoves->howmany + 1;
					size++;
					AllMoves->Plays = (Move*)realloc(AllMoves->Plays, size*sizeof(Move));
					AllMoves->Plays[size - 1].origin[0] = i;
					AllMoves->Plays[size - 1].origin[1] = j;
					AllMoves->Plays[size - 1].destiny[0] = i - 1;
					AllMoves->Plays[size - 1].destiny[1] = j + 1;
				}
				/* Caso de eliminar peça sendo um peão na diagonal superior esquerda. */
				if(board->Board[i - 1][j - 1] < BLANK && i - 1 >= 0 && j - 1 >= 0){
					AllMoves->howmany = AllMoves->howmany + 1;
					size++;
					AllMoves->Plays = (Move*)realloc(AllMoves->Plays, size*sizeof(Move));
					AllMoves->Plays[size - 1].origin[0] = i;
					AllMoves->Plays[size - 1].origin[1] = j;
					AllMoves->Plays[size - 1].destiny[0] = i - 1;
					AllMoves->Plays[size - 1].destiny[1] = j - 1;
				}
				/* Caso de eliminar peça sendo um peão na diagonal inferior esquerda. */
				if(board->Board[i + 1][j - 1] < BLANK && i + 1 <= 7 && j - 1 >= 0){
					AllMoves->howmany = AllMoves->howmany + 1;
					size++;
					AllMoves->Plays = (Move*)realloc(AllMoves->Plays, size*sizeof(Move));
					AllMoves->Plays[size - 1].origin[0] = i;
					AllMoves->Plays[size - 1].origin[1] = j;
					AllMoves->Plays[size - 1].destiny[0] = i + 1;
					AllMoves->Plays[size - 1].destiny[1] = j - 1;
				}
				/* Caso de eliminar peça sendo um peão na diagonal inferior direita. */
				if(board->Board[i + 1][j + 1] < BLANK && i + 1 <= 7 && j + 1 <= 7){
					AllMoves->howmany = AllMoves->howmany + 1;
					size++;
					AllMoves->Plays = (Move*)realloc(AllMoves->Plays, size*sizeof(Move));
					AllMoves->Plays[size - 1].origin[0] = i;
					AllMoves->Plays[size - 1].origin[1] = j;
					AllMoves->Plays[size - 1].destiny[0] = i + 1;
					AllMoves->Plays[size - 1].destiny[1] = j + 1;
				}
				/* Caso de eliminar peça sendo um peão de frente. */
				if(board->Board[i - 1][j] < BLANK && i - 1 >= 0){
					AllMoves->howmany = AllMoves->howmany + 1;
					size++;
					AllMoves->Plays = (Move*)realloc(AllMoves->Plays, size*sizeof(Move));
					AllMoves->Plays[size - 1].origin[0] = i;
					AllMoves->Plays[size - 1].origin[1] = j;
					AllMoves->Plays[size - 1].destiny[0] = i - 1;
					AllMoves->Plays[size - 1].destiny[1] = j;
				}
			}
			/* Casos para o cavalo black. Todos os Ls possíveis foram representados. */
			else if(board->Board[i][j] == W_HORSE){
				if(i - 1 >= 0 && j - 2 >= 0 && board->Board[i - 1][j - 2] <= BLANK){
					AllMoves->howmany = AllMoves->howmany + 1;
					size++;
					AllMoves->Plays = (Move*)realloc(AllMoves->Plays, size*sizeof(Move));
					AllMoves->Plays[size - 1].origin[0] = i;
					AllMoves->Plays[size - 1].origin[1] = j;
					AllMoves->Plays[size - 1].destiny[0] = i - 1;
					AllMoves->Plays[size - 1].destiny[1] = j - 2;
				}
				if(i - 2 >= 0 && j - 1 >= 0 && board->Board[i - 2][j - 1] <= BLANK){
					AllMoves->howmany = AllMoves->howmany + 1;
					size++;
					AllMoves->Plays = (Move*)realloc(AllMoves->Plays, size*sizeof(Move));
					AllMoves->Plays[size - 1].origin[0] = i;
					AllMoves->Plays[size - 1].origin[1] = j;
					AllMoves->Plays[size - 1].destiny[0] = i - 2;
					AllMoves->Plays[size - 1].destiny[1] = j - 1;
				}
				if(i - 2 >= 0 && j + 1 <= 7 && board->Board[i - 2][j + 1] <= BLANK){
					AllMoves->howmany = AllMoves->howmany + 1;
					size++;
					AllMoves->Plays = (Move*)realloc(AllMoves->Plays, size*sizeof(Move));
					AllMoves->Plays[size - 1].origin[0] = i;
					AllMoves->Plays[size - 1].origin[1] = j;
					AllMoves->Plays[size - 1].destiny[0] = i - 2;
					AllMoves->Plays[size - 1].destiny[1] = j + 1;
				}
				if(i - 1 >= 0 && j + 2 <= 7 && board->Board[i - 1][j + 2] <= BLANK){
					AllMoves->howmany = AllMoves->howmany + 1;
					size++;
					AllMoves->Plays = (Move*)realloc(AllMoves->Plays, size*sizeof(Move));
					AllMoves->Plays[size - 1].origin[0] = i;
					AllMoves->Plays[size - 1].origin[1] = j;
					AllMoves->Plays[size - 1].destiny[0] = i - 1;
					AllMoves->Plays[size - 1].destiny[1] = j + 2;
				}
				if(i + 1 <= 7 && j - 2 >= 0 && board->Board[i + 1][j - 2] <= BLANK){
					AllMoves->howmany = AllMoves->howmany + 1;
					size++;
					AllMoves->Plays = (Move*)realloc(AllMoves->Plays, size*sizeof(Move));
					AllMoves->Plays[size - 1].origin[0] = i;
					AllMoves->Plays[size - 1].origin[1] = j;
					AllMoves->Plays[size - 1].destiny[0] = i + 1;
					AllMoves->Plays[size - 1].destiny[1] = j - 2;
				}
				if(i + 2 <= 7 && j - 1 >= 0 && board->Board[i + 2][j - 1] <= BLANK){
					AllMoves->howmany = AllMoves->howmany + 1;
					size++;
					AllMoves->Plays = (Move*)realloc(AllMoves->Plays, size*sizeof(Move));
					AllMoves->Plays[size - 1].origin[0] = i;
					AllMoves->Plays[size - 1].origin[1] = j;
					AllMoves->Plays[size - 1].destiny[0] = i + 2;
					AllMoves->Plays[size - 1].destiny[1] = j - 1;
				}
				if(i + 2 <= 7 && j + 1 <= 7 && board->Board[i + 2][j + 1] <= BLANK){
					AllMoves->howmany = AllMoves->howmany + 1;
					size++;
					AllMoves->Plays = (Move*)realloc(AllMoves->Plays, size*sizeof(Move));
					AllMoves->Plays[size - 1].origin[0] = i;
					AllMoves->Plays[size - 1].origin[1] = j;
					AllMoves->Plays[size - 1].destiny[0] = i + 2;
					AllMoves->Plays[size - 1].destiny[1] = j + 1;
				}
				if(i + 1 <= 7 && j + 2 <= 7 && board->Board[i + 1][j + 2] <= BLANK){
					AllMoves->howmany = AllMoves->howmany + 1;
					size++;
					AllMoves->Plays = (Move*)realloc(AllMoves->Plays, size*sizeof(Move));
					AllMoves->Plays[size - 1].origin[0] = i;
					AllMoves->Plays[size - 1].origin[1] = j;
					AllMoves->Plays[size - 1].destiny[0] = i + 1;
					AllMoves->Plays[size - 1].destiny[1] = j + 2;
				}
			}
		}
	}
	return AllMoves;
}

/* Função: AnalyzePossibleMovementsWhite
		Objetivo: Conseguir armazenar todas as possíveis jogadas para as peças pretas a partir de um tabuleiro.

		Parametros:
			board - Ponteiro para a estrutura da tabuleiro.
					Não deve ser nulo nem vazio

		Saída: Essa função retorna um arrays que contém os movimentos possíveis para com as peças pretas.
*/
ListOfMoves* AnalyzePossibleMovementsBlack(TBoard *board){

	/* Verificando se o tabuleiro é nulo */
	if(board == NULL){
		return NULL;
	}

	int i, j, size = 1;
	ListOfMoves* AllMoves = (ListOfMoves*) malloc(sizeof(ListOfMoves));
	AllMoves->Plays = (Move*) malloc(size*sizeof(Move));
	AllMoves->howmany = 0;

	/* Percorrendo o tabuleiro. */
	for(i=0; i < 8;i++){
		for(j=0; j < 8;j++){
			/* Casos para o peão white. */
			if(board->Board[i][j] == B_PAWN){
				/* Caso andar 2 estando na posição inicial. */
				if((i == 1 && board->Board[i + 2][j] == BLANK) && i + 2 <= 7){
					AllMoves->howmany = AllMoves->howmany + 1;
					size++;
					AllMoves->Plays = (Move*)realloc(AllMoves->Plays, size*sizeof(Move));
					AllMoves->Plays[size - 1].origin[0] = i;
					AllMoves->Plays[size - 1].origin[1] = j;
					AllMoves->Plays[size - 1].destiny[0] = i + 2;
					AllMoves->Plays[size - 1].destiny[1] = j;
				}
				/* Caso andar 1 estando na posição inicial/ andar normalmente. */
				if(((i == 1 && board->Board[i + 1][j] == BLANK) || board->Board[i + 1][j] == BLANK) && i + 1 <= 7){
					AllMoves->howmany = AllMoves->howmany + 1;
					size++;
					AllMoves->Plays = (Move*)realloc(AllMoves->Plays, size*sizeof(Move));
					AllMoves->Plays[size - 1].origin[0] = i;
					AllMoves->Plays[size - 1].origin[1] = j;
					AllMoves->Plays[size - 1].destiny[0] = i + 1;
					AllMoves->Plays[size - 1].destiny[1] = j;
				}
				/* Caso de eliminar peça sendo um peão na diagonal superior direita. */
				if(board->Board[i - 1][j + 1] > BLANK && i - 1 >= 0 && j + 1 <= 7){
					AllMoves->howmany = AllMoves->howmany + 1;
					size++;
					AllMoves->Plays = (Move*)realloc(AllMoves->Plays, size*sizeof(Move));
					AllMoves->Plays[size - 1].origin[0] = i;
					AllMoves->Plays[size - 1].origin[1] = j;
					AllMoves->Plays[size - 1].destiny[0] = i - 1;
					AllMoves->Plays[size - 1].destiny[1] = j + 1;
				}
				/* Caso de eliminar peça sendo um peão na diagonal superior esquerda. */
				if(board->Board[i - 1][j - 1] > BLANK && i - 1 >= 0 && j - 1 >= 0){
					AllMoves->howmany = AllMoves->howmany + 1;
					size++;
					AllMoves->Plays = (Move*)realloc(AllMoves->Plays, size*sizeof(Move));
					AllMoves->Plays[size - 1].origin[0] = i;
					AllMoves->Plays[size - 1].origin[1] = j;
					AllMoves->Plays[size - 1].destiny[0] = i - 1;
					AllMoves->Plays[size - 1].destiny[1] = j - 1;
				}
				/* Caso de eliminar peça sendo um peão na diagonal inferior esquerda. */
				if(board->Board[i + 1][j - 1] > BLANK && i + 1 <= 7 && j - 1 >= 0){
					AllMoves->howmany = AllMoves->howmany + 1;
					size++;
					AllMoves->Plays = (Move*)realloc(AllMoves->Plays, size*sizeof(Move));
					AllMoves->Plays[size - 1].origin[0] = i;
					AllMoves->Plays[size - 1].origin[1] = j;
					AllMoves->Plays[size - 1].destiny[0] = i + 1;
					AllMoves->Plays[size - 1].destiny[1] = j - 1;
				}
				/* Caso de eliminar peça sendo um peão na diagonal inferior direita. */
				if(board->Board[i + 1][j + 1] > BLANK && i + 1 <= 7 && j + 1 <= 7){
					AllMoves->howmany = AllMoves->howmany + 1;
					size++;
					AllMoves->Plays = (Move*)realloc(AllMoves->Plays, size*sizeof(Move));
					AllMoves->Plays[size - 1].origin[0] = i;
					AllMoves->Plays[size - 1].origin[1] = j;
					AllMoves->Plays[size - 1].destiny[0] = i + 1;
					AllMoves->Plays[size - 1].destiny[1] = j + 1;
				}
				/* Caso de eliminar peça sendo um peão de frente. */
				if(board->Board[i + 1][j] > BLANK && i + 1 <= 7){
					AllMoves->howmany = AllMoves->howmany + 1;
					size++;
					AllMoves->Plays = (Move*)realloc(AllMoves->Plays, size*sizeof(Move));
					AllMoves->Plays[size - 1].origin[0] = i;
					AllMoves->Plays[size - 1].origin[1] = j;
					AllMoves->Plays[size - 1].destiny[0] = i + 1;
					AllMoves->Plays[size - 1].destiny[1] = j;
				}
			}
			/* Casos para o cavalo branco. Todos os Ls possíveis foram representados. */
			else if(board->Board[i][j] == B_HORSE){
				if(i - 1 >= 0 && j - 2 >= 0 && board->Board[i - 1][j - 2] >= BLANK){
					AllMoves->howmany = AllMoves->howmany + 1;
					size++;
					AllMoves->Plays = (Move*)realloc(AllMoves->Plays, size*sizeof(Move));
					AllMoves->Plays[size - 1].origin[0] = i;
					AllMoves->Plays[size - 1].origin[1] = j;
					AllMoves->Plays[size - 1].destiny[0] = i - 1;
					AllMoves->Plays[size - 1].destiny[1] = j - 2;
				}
				if(i - 2 >= 0 && j - 1 >= 0 && board->Board[i - 2][j - 1] >= BLANK){
					AllMoves->howmany = AllMoves->howmany + 1;
					size++;
					AllMoves->Plays = (Move*)realloc(AllMoves->Plays, size*sizeof(Move));
					AllMoves->Plays[size - 1].origin[0] = i;
					AllMoves->Plays[size - 1].origin[1] = j;
					AllMoves->Plays[size - 1].destiny[0] = i - 2;
					AllMoves->Plays[size - 1].destiny[1] = j - 1;
				}
				if(i - 2 >= 0 && j + 1 <= 7 && board->Board[i - 2][j + 1] >= BLANK){
					AllMoves->howmany = AllMoves->howmany + 1;
					size++;
					AllMoves->Plays = (Move*)realloc(AllMoves->Plays, size*sizeof(Move));
					AllMoves->Plays[size - 1].origin[0] = i;
					AllMoves->Plays[size - 1].origin[1] = j;
					AllMoves->Plays[size - 1].destiny[0] = i - 2;
					AllMoves->Plays[size - 1].destiny[1] = j + 1;
				}
				if(i - 1 >= 0 && j + 2 <= 7 && board->Board[i - 1][j + 2] >= BLANK){
					AllMoves->howmany = AllMoves->howmany + 1;
					size++;
					AllMoves->Plays = (Move*)realloc(AllMoves->Plays, size*sizeof(Move));
					AllMoves->Plays[size - 1].origin[0] = i;
					AllMoves->Plays[size - 1].origin[1] = j;
					AllMoves->Plays[size - 1].destiny[0] = i - 1;
					AllMoves->Plays[size - 1].destiny[1] = j + 2;
				}
				if(i + 1 <= 7 && j - 2 >= 0 && board->Board[i + 1][j - 2] >= BLANK){
					AllMoves->howmany = AllMoves->howmany + 1;
					size++;
					AllMoves->Plays = (Move*)realloc(AllMoves->Plays, size*sizeof(Move));
					AllMoves->Plays[size - 1].origin[0] = i;
					AllMoves->Plays[size - 1].origin[1] = j;
					AllMoves->Plays[size - 1].destiny[0] = i + 1;
					AllMoves->Plays[size - 1].destiny[1] = j - 2;
				}
				if(i + 2 <= 7 && j - 1 >= 0 && board->Board[i + 2][j - 1] >= BLANK){
					AllMoves->howmany = AllMoves->howmany + 1;
					size++;
					AllMoves->Plays = (Move*)realloc(AllMoves->Plays, size*sizeof(Move));
					AllMoves->Plays[size - 1].origin[0] = i;
					AllMoves->Plays[size - 1].origin[1] = j;
					AllMoves->Plays[size - 1].destiny[0] = i + 2;
					AllMoves->Plays[size - 1].destiny[1] = j - 1;
				}
				if(i + 2 <= 7 && j + 1 <= 7 && board->Board[i + 2][j + 1] >= BLANK){
					AllMoves->howmany = AllMoves->howmany + 1;
					size++;
					AllMoves->Plays = (Move*)realloc(AllMoves->Plays, size*sizeof(Move));
					AllMoves->Plays[size - 1].origin[0] = i;
					AllMoves->Plays[size - 1].origin[1] = j;
					AllMoves->Plays[size - 1].destiny[0] = i + 2;
					AllMoves->Plays[size - 1].destiny[1] = j + 1;
				}
				if(i + 1 <= 7 && j + 2 <= 7 && board->Board[i + 1][j + 2] >= BLANK){
					AllMoves->howmany = AllMoves->howmany + 1;
					size++;
					AllMoves->Plays = (Move*)realloc(AllMoves->Plays, size*sizeof(Move));
					AllMoves->Plays[size - 1].origin[0] = i;
					AllMoves->Plays[size - 1].origin[1] = j;
					AllMoves->Plays[size - 1].destiny[0] = i + 1;
					AllMoves->Plays[size - 1].destiny[1] = j + 2;
				}
			}
		}
	}
	return AllMoves;
}
