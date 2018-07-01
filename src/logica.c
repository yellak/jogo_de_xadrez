#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/logica.h"

/* Função: Verificar sintaxe do movimento (verify_syntax_move)
        Objetivo:
            Verificar se a sintaxe de uma jogada está correta
        
        Parâmetros:
            chess_move - string fornecida pelo usuário na hora do movimento
     
        Retorno:
            true  - caso a sintaxe esteja correta
            false - caso a sintaxe esteja errada
*/
int verify_syntax_move(char chess_move[])
{
	int i;
	char piece;
	char movement[6]; /* Parte onde está a origem e o destino */
	if(strlen(chess_move) == 6)	/* A peça foi especificada */
		{
			/* Peça que está sendo movimentada */
			piece = chess_move[0];
			/* Verificando se não foi colocada nenhuma peça não permitida */
			if(piece != 'K'){	/* rei */
				if(piece != 'Q'){ /* rainha */
					if(piece != 'R'){ /* torre */
						if(piece != 'B'){ /* bispo */
							if(piece != 'N'){ /* cavalo */
								if(piece != 'P'){ /* peão */
									return false;
								} /* P */
							} /* N */
						} /* B */
					} /* R */
				} /* Q */
			} /* K */

			/* Copiando a parte da origem-destino da notação */
			for(i = 1; i < 6; i++){
				movement[i - 1] = chess_move[i];
			}
		} /* if( ... == 6) */
	
	else if(strlen(chess_move) == 5) /* A peça não foi especificada */
		{
			if(strcmp(chess_move, "0-0-0") == 0){ /* Roque pelo lado da rainha */
				return true;
			}
			else{
				/* Copiando a string diretamante já que a peça não é especificada */
				strcpy(movement, chess_move);
			}
		} /* else if( ... == 5) */
	
	else if(strlen(chess_move) == 3)
		{
			if(strcmp(chess_move, "0-0") != 0){ /* Roque pelo lado do rei */
				if(strcmp(chess_move, "1-0") != 0){ /* Branca venceu */
					if(strcmp(chess_move, "0-1") != 0){ /* Preto venceu */
						return false;
					}
					else{
						return true; /* Preto venceu */
					}
				}
				else{
					return true; /* Branca venceu */
				}
			}
			else{
				return true; /* Roque pelo lado do rei */
			}
		} /* else if( ... == 3) */

	else if(strlen(chess_move) == 7)
		{
			if(strcmp(chess_move, "1/2-1/2") == 0){ /* Jogo deu empate */
				return true;
			}
			else{
				return false;
			}
		} /* else if( ... == 7) */

	/* Verificando a notação da ação */
	if(movement[2] != '-'){ /* Movimento padrão */
		if(movement[2] != 'x'){	/* Captura */
			if(movement[2] != '='){ /* Promoção de um peão */
				if(movement[2] != '+'){ /* Rei em cheque */
					if(movement[2] != '#'){ /* Cheque-mate */
						return false;
					} /* # */
				}	  /* + */
			} /* = */
		} /* x */
	} /* - */

	/* Primeiro caractere não é uma letra válida */
	if((movement[0] < 'a') || (movement[0] > 'h')){
		return false;
	}

	/* Segundo caractere não é um número válido */
	if((movement[1] < '1') || (movement[1] > '8')){
		return false;
	}

	/* Quarto caractere não é uma letra válida */
	if((movement[3] < 'a') || (movement[3] > 'h')){
		return false;
	}

	/* Quinto caractere não é um número válido */
	if((movement[4] < '1') || (movement[4] > '8')){
		return false;
	}

	return true;
}

Move* algebraic_translate(char chess_move[]){
	Move* result = (Move*) malloc(sizeof(Move));
	char movement[6];
	int i;

	/* Verificando se a sintaxe é válida */
	if(verify_syntax_move(chess_move) == true)
		{
			/* Verficando se a peça foi especificada */
			if(strlen(chess_move) == 6){
				for(i = 1; i < 6; i++)
					{
						movement[i - 1] = chess_move[i];
					}
			}
			/* Verificando se a peça não foi especificada */
			else if(strlen(chess_move) == 5){
				strcpy(movement, chess_move);
			}
			/* A notação é inválida */
			else{
				free(result);
				return NULL;
			}

			/* Traduzindo para as letras */
			result->origin[1] = movement[0] - 'a';
			result->destiny[1] = movement[3] - 'a';

			/* Traduzindo para os números */
			result->origin[0] = '8' - movement[1];
			result->destiny[0] = '8' - movement[4];
		}
	else
		{
			free(result);
			return NULL;
		}
	
	return result;
}

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
