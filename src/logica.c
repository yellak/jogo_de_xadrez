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

/* 
   Função: Traduzir para movimento a partir da notação
         Objetivo:
             A partir da notação algébrica de uma jogada, obter o movimento
             correspondente

         Parâmetros:
             chess_move - string que contém a notação algébrica

         Saída:
             result - Elemento de movimento resultante */
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


/* 
 Função: Traduzir para notação algébrica a partir do movimento
       Objetivo:
           A partir do elemento de movimento a ele irá traduzí-lo para notação
           algébrica

       Parâmetros:
           movement   - Elemento de movimento a ser traduzido
           chess_move - String que será substituída pela nova notação */
void Move2Algebraic(Move* movement, char chess_move[])
{
	int ol, oc, dl, dc;	/* Coordenadas do movimento */
	ol = movement->origin[0]; /* origin line */
	oc = movement->origin[1]; /* origin column */
	dl = movement->destiny[0]; /* destiny line */
	dc = movement->destiny[1]; /* destiny column */

	chess_move[0] = 'a' + oc;
	chess_move[1] = '8' - ol;
	chess_move[2] = '-';
	chess_move[3] = 'a' + dc;
	chess_move[4] = '8' - dl;
	chess_move[5] = '\0';
}

/* Função: WhitePawnMovements
		Objetivo: Calcular todos os movimentos possíveis para um peão branco dada uma
		determinada configuração de tabuleiro.

		Parametros:
			board - Ponteiro para um tabuleiro.
					Não deve ser nulo
			AllMoves - Ponteiro para uma lista de movimentos.
					Não deve ser nulo
			originx - Inteiro representando a coordenada x da posição (x,y) a ser verificada.
				   Deve ser um valor entre 0 e 7.
			originy - Inteiro representando a coordenada y da posição (x,y) a ser verificada.
				     Deve ser um valor entre 0 e 7.

		Saída: Essa função retorna a lista de movimentos com os movimentos possíveis do peão
		branco adicionados.
*/

ListOfMoves* WhitePawnMovements(TBoard* board, ListOfMoves* AllMoves, int originx, int originy){
	int COLOR_POSITION;

	if(board == NULL || AllMoves == NULL){
		return NULL;
	}

	/* Caso andar 2 estando na posição inicial. */
	if(WhatPiece(board, originx-2, originy) != OUT_OF_RANGE){
		COLOR_POSITION = ColorPiece(board->Board[originx - 2][originy]);
		int COLOR_POSITION2 = ColorPiece(board->Board[originx - 1][originy]);
		if(originx == 6 && COLOR_POSITION == -1 && originx - 2 >= 0 && COLOR_POSITION2 == -1){
			InsertMove(AllMoves, originx, originy, originx - 2, originy);
		}
	}
	/* Caso andar 1 estando na posição inicial/ andar normalmente. */
	if(WhatPiece(board, originx-1, originy) != OUT_OF_RANGE){
		COLOR_POSITION = ColorPiece(board->Board[originx - 1][originy]);
		if(((originx == 6 && COLOR_POSITION == -1) || COLOR_POSITION == -1) && originx - 1 >= 0){
			InsertMove(AllMoves, originx, originy, originx - 1, originy);
		}
	}
	/* Caso de eliminar peça sendo um peão na diagonal superior direita. */
	if(WhatPiece(board, originx-1, originy+1) != OUT_OF_RANGE){
		COLOR_POSITION = ColorPiece(board->Board[originx - 1][originy + 1]);
		if(originx - 1 >= 0 && originy + 1 <= 7 && COLOR_POSITION == BLACK){
			InsertMove(AllMoves, originx, originy, originx - 1, originy + 1);
		}
	}
	/* Caso de eliminar peça sendo um peão na diagonal superior esquerda. */
	if(WhatPiece(board, originx-1, originy-1) != OUT_OF_RANGE){
		COLOR_POSITION = ColorPiece(board->Board[originx - 1][originy - 1]);
		if(originx - 1 >= 0 && originy - 1 >= 0 && COLOR_POSITION == BLACK){
			InsertMove(AllMoves, originx, originy, originx - 1, originy - 1);
		}
	}

	return AllMoves;
}

/* Função: BlackPawnMovements
		Objetivo: Calcular todos os movimentos possíveis para um peão preto dada uma
		determinada configuração de tabuleiro.

		Parametros:
			board - Ponteiro para um tabuleiro.
					Não deve ser nulo
			AllMoves - Ponteiro para uma lista de movimentos.
					Não deve ser nulo
			originx - Inteiro representando a coordenada x da posição (x,y) a ser verificada.
				   Deve ser um valor entre 0 e 7.
			originy - Inteiro representando a coordenada y da posição (x,y) a ser verificada.
				     Deve ser um valor entre 0 e 7.

		Saída: Essa função retorna a lista de movimentos com os movimentos possíveis do peão
		preto adicionados.
*/

ListOfMoves* BlackPawnMovements(TBoard* board, ListOfMoves* AllMoves, int originx, int originy){
	int COLOR_POSITION;

	if(board == NULL || AllMoves == NULL){
		return NULL;
	}

	/* Caso andar 2 estando na posição inicial. */
	if(WhatPiece(board, originx+2, originy) != OUT_OF_RANGE){
		COLOR_POSITION = ColorPiece(board->Board[originx + 2][originy]);
		int COLOR_POSITION2 = ColorPiece(board->Board[originx + 1][originy]);
		if(originx == 1 && COLOR_POSITION == -1 && originx + 2 <= 7 && COLOR_POSITION2 == -1){
			InsertMove(AllMoves, originx, originy, originx + 2, originy);
		}
	}
	/* Caso andar 1 estando na posição inicial/ andar normalmente. */
	if(WhatPiece(board, originx+1, originy) != OUT_OF_RANGE){
		COLOR_POSITION = ColorPiece(board->Board[originx + 1][originy]);
		if(((originx == 1 && COLOR_POSITION == -1) || COLOR_POSITION == -1) && originx + 1 <= 7){
			InsertMove(AllMoves, originx, originy, originx + 1, originy);
		}
	}
	/* Caso de eliminar peça sendo um peão na diagonal inferior direita. */
	if(WhatPiece(board, originx+1, originy+1) != OUT_OF_RANGE){
		COLOR_POSITION = ColorPiece(board->Board[originx + 1][originy + 1]);
		if(originx + 1 <= 7 && originy + 1 <= 7 && COLOR_POSITION == WHITE){
			InsertMove(AllMoves, originx, originy, originx + 1, originy + 1);
		}
	}
	/* Caso de eliminar peça sendo um peão na diagonal inferior esquerda. */
	if(WhatPiece(board, originx+1, originy-1) != OUT_OF_RANGE){
		COLOR_POSITION = ColorPiece(board->Board[originx + 1][originy - 1]);
		if(originx + 1 <= 7 && originy - 1 >= 0 && COLOR_POSITION == WHITE){
			InsertMove(AllMoves, originx, originy, originx + 1, originy - 1);
		}
	}

	return AllMoves;
}

/* Função: HorseMovements
		Objetivo: Calcular todos os movimentos possíveis para um cavalo dada uma
		determinada configuração de tabuleiro.

		Parametros:
			board - Ponteiro para um tabuleiro.
					Não deve ser nulo
			AllMoves - Ponteiro para uma lista de movimentos.
					Não deve ser nulo
			originx - Inteiro representando a coordenada x da posição (x,y) a ser verificada.
				   Deve ser um valor entre 0 e 7.
			originy - Inteiro representando a coordenada y da posição (x,y) a ser verificada.
				     Deve ser um valor entre 0 e 7.

		Saída: Essa função retorna a lista de movimentos com os movimentos possíveis do cavalo
		adicionados.
*/

ListOfMoves* HorseMovements(TBoard* board, ListOfMoves* AllMoves, int originx, int originy){
	char piece;
	int COLOR_PIECE, COLOR_POSITION;

	if(board == NULL || AllMoves == NULL){
		return NULL;
	}

	/* Determina a cor da peça */
	piece = WhatPiece(board, originx, originy);
	COLOR_PIECE = ColorPiece(piece);

	/* Casos para o cavalo black. Todos os Ls possíveis foram representados. */
	if(WhatPiece(board, originx-1, originy-2) != OUT_OF_RANGE){
		COLOR_POSITION = ColorPiece(board->Board[originx - 1][originy - 2]);
		if(originx - 1 >= 0 && originy - 2 >= 0 && COLOR_POSITION != COLOR_PIECE){
			InsertMove(AllMoves, originx, originy, originx - 1, originy - 2);
		}
	}
	if(WhatPiece(board, originx-2, originy-1) != OUT_OF_RANGE){
		COLOR_POSITION = ColorPiece(board->Board[originx - 2][originy - 1]);
		if(originx - 2 >= 0 && originy - 1 >= 0 && COLOR_POSITION != COLOR_PIECE){
			InsertMove(AllMoves, originx, originy, originx - 2, originy - 1);
		}
	}
	if(WhatPiece(board, originx-2, originy+1) != OUT_OF_RANGE){
		COLOR_POSITION = ColorPiece(board->Board[originx - 2][originy + 1]);
		if(originx - 2 >= 0 && originy + 1 <= 7 &&  COLOR_POSITION != COLOR_PIECE){
			InsertMove(AllMoves, originx, originy, originx - 2, originy + 1);
		}
	}
	if(WhatPiece(board, originx-1, originy+2) != OUT_OF_RANGE){
		COLOR_POSITION = ColorPiece(board->Board[originx - 1][originy + 2]);
		if(originx - 1 >= 0 && originy + 2 <= 7 && COLOR_POSITION != COLOR_PIECE){
			InsertMove(AllMoves, originx, originy, originx - 1, originy + 2);
		}
	}
	if(WhatPiece(board, originx+1, originy-2) != OUT_OF_RANGE){
		COLOR_POSITION = ColorPiece(board->Board[originx + 1][originy - 2]);
		if(originx + 1 <= 7 && originy - 2 >= 0 && COLOR_POSITION != COLOR_PIECE){
			InsertMove(AllMoves, originx, originy, originx + 1, originy - 2);
		}
	}
	if(WhatPiece(board, originx+2, originy-1) != OUT_OF_RANGE){
		COLOR_POSITION = ColorPiece(board->Board[originx + 2][originy - 1]);
		if(originx + 2 <= 7 && originy - 1 >= 0 && COLOR_POSITION != COLOR_PIECE){
			InsertMove(AllMoves, originx, originy, originx + 2, originy - 1);
		}
	}
	if(WhatPiece(board, originx+2, originy+1) != OUT_OF_RANGE){
		COLOR_POSITION = ColorPiece(board->Board[originx + 2][originy + 1]);
		if(originx + 2 <= 7 && originy + 1 <= 7 && COLOR_POSITION != COLOR_PIECE){
			InsertMove(AllMoves, originx, originy, originx + 2, originy + 1);
		}
	}
	if(WhatPiece(board, originx+1, originy+2) != OUT_OF_RANGE){
		COLOR_POSITION = ColorPiece(board->Board[originx + 1][originy + 2]);
		if(originx + 1 <= 7 && originy + 2 <= 7 && COLOR_POSITION != COLOR_PIECE){
			InsertMove(AllMoves, originx, originy, originx + 1, originy + 2);
		}
	}

	return AllMoves;
}


/* Função: TowerMovements
		Objetivo: Calcular todos os movimentos possíveis para uma torre dada uma
		determinada configuração de tabuleiro.

		Parametros:
			board - Ponteiro para um tabuleiro.
					Não deve ser nulo
			AllMoves - Ponteiro para uma lista de movimentos.
					Não deve ser nulo
			originx - Inteiro representando a coordenada x da posição (x,y) a ser verificada.
				   Deve ser um valor entre 0 e 7.
			originy - Inteiro representando a coordenada y da posição (x,y) a ser verificada.
				     Deve ser um valor entre 0 e 7.

		Saída: Essa função retorna a lista de movimentos com os movimentos possíveis da torre
		adicionados.
*/

ListOfMoves* TowerMovements(TBoard *board, ListOfMoves* AllMoves, int originx, int originy){
	char piece;
	int k, COLOR_PIECE, COLOR_POSITION, OPPOSITE_COLOR;

	if(board == NULL || AllMoves == NULL){
		return NULL;
	}
	/* Determina a cor da peça e a oposta*/
	piece = WhatPiece(board, originx, originy);
	COLOR_PIECE = ColorPiece(piece);
	if(COLOR_PIECE == BLACK){
		OPPOSITE_COLOR = WHITE;
	}
	else{
		OPPOSITE_COLOR = BLACK;
	}

	k = 1;
	/* Verifica a cor da peça que está na posição */
	if(WhatPiece(board, originx+k, originy) != OUT_OF_RANGE){
		COLOR_POSITION = ColorPiece(board->Board[originx + k][originy]);
		while(originx + k <= 7 && COLOR_POSITION != COLOR_PIECE){
			COLOR_POSITION = ColorPiece(board->Board[originx + k][originy]);
			if(COLOR_PIECE == COLOR_POSITION){
				break;
			}
			InsertMove(AllMoves, originx, originy, originx + k, originy);
			/* Para o loop caso tenha chegado na posição de uma peça adversária */
			if(COLOR_POSITION == OPPOSITE_COLOR){
				break;
			}
			k++;
		}
	}
	k = 1;
	if(WhatPiece(board, originx-k, originy) != OUT_OF_RANGE){
		COLOR_POSITION = ColorPiece(board->Board[originx - k][originy]);
		while(originx - k >= 0 && COLOR_POSITION != COLOR_PIECE){
			COLOR_POSITION = ColorPiece(board->Board[originx - k][originy]);
			if(COLOR_PIECE == COLOR_POSITION){
				break;
			}
			InsertMove(AllMoves, originx, originy, originx - k, originy);
			if(COLOR_POSITION == OPPOSITE_COLOR){
				break;
			}			
			k++;
		}
	}
	k = 1;
	if(WhatPiece(board, originx, originy+k) != OUT_OF_RANGE){
		COLOR_POSITION = ColorPiece(board->Board[originx][originy + k]);
		while(originy + k <= 7 && COLOR_POSITION != COLOR_PIECE){
			COLOR_POSITION = ColorPiece(board->Board[originx][originy + k]);
			if(COLOR_PIECE == COLOR_POSITION){
				break;
			}
			InsertMove(AllMoves, originx, originy, originx, originy + k);
			if(COLOR_POSITION == OPPOSITE_COLOR){
				break;
			}			
			k++;
		}
	}
	k = 1;
	if(WhatPiece(board, originx, originy-k) != OUT_OF_RANGE){
		COLOR_POSITION = ColorPiece(board->Board[originx][originy - k]);
		while(originy - k >= 0 && COLOR_POSITION != COLOR_PIECE){
			COLOR_POSITION = ColorPiece(board->Board[originx][originy - k]);
			if(COLOR_PIECE == COLOR_POSITION){
				break;
			}
			InsertMove(AllMoves, originx, originy, originx, originy - k);				
			if(COLOR_POSITION == OPPOSITE_COLOR){
				break;
			}			
			k++;
		}
	}

	return AllMoves;	
}

/* Função: TowerMovements
		Objetivo: Calcular todos os movimentos possíveis para um bispo dada uma
		determinada configuração de tabuleiro.

		Parametros:
			board - Ponteiro para um tabuleiro.
					Não deve ser nulo
			AllMoves - Ponteiro para uma lista de movimentos.
					Não deve ser nulo
			originx - Inteiro representando a coordenada x da posição (x,y) a ser verificada.
				   Deve ser um valor entre 0 e 7.
			originy - Inteiro representando a coordenada y da posição (x,y) a ser verificada.
				     Deve ser um valor entre 0 e 7.

		Saída: Essa função retorna a lista de movimentos com os movimentos possíveis do bispo
		adicionados.
*/

ListOfMoves* BishopMovements(TBoard* board, ListOfMoves* AllMoves, int originx, int originy){
	char piece;
	int k, COLOR_PIECE, COLOR_POSITION, OPPOSITE_COLOR;

	if(board == NULL || AllMoves == NULL){
		return NULL;
	}
	/* Determina a cor da peça e a oposta*/
	piece = WhatPiece(board, originx, originy);
	COLOR_PIECE = ColorPiece(piece);
	if(COLOR_PIECE == BLACK){
		OPPOSITE_COLOR = WHITE;
	}
	else{
		OPPOSITE_COLOR = BLACK;
	}

	k = 1;
	/* Verifica a cor da peça que está na posição */
	if(WhatPiece(board, originx+k, originy+k) != OUT_OF_RANGE){
		COLOR_POSITION = ColorPiece(board->Board[originx + k][originy + k]);
		while(originx + k <= 7 && originy + k <= 7 && COLOR_POSITION != COLOR_PIECE){
			COLOR_POSITION = ColorPiece(board->Board[originx + k][originy + k]);
			if(COLOR_PIECE == COLOR_POSITION){
				break;
			}
			InsertMove(AllMoves, originx, originy, originx + k, originy + k);
			/* Para o loop caso tenha chegado na posição de uma peça adversária */
			if(COLOR_POSITION == OPPOSITE_COLOR){
				break;
			}
			k++;
		}
	}
	k = 1;
	/* Verifica a cor da peça que está na posição */
	if(WhatPiece(board, originx-k, originy-k) != OUT_OF_RANGE){
		COLOR_POSITION = ColorPiece(board->Board[originx - k][originy - k]);
		while(originx - k >= 0 && originy - k >= 0 && COLOR_POSITION != COLOR_PIECE){
			COLOR_POSITION = ColorPiece(board->Board[originx - k][originy - k]);
			if(COLOR_PIECE == COLOR_POSITION){
				break;
			}
			InsertMove(AllMoves, originx, originy, originx - k, originy - k);
			/* Para o loop caso tenha chegado na posição de uma peça adversária */
			if(COLOR_POSITION == OPPOSITE_COLOR){
				break;
			}
			k++;
		}
	}
	k = 1;
	/* Verifica a cor da peça que está na posição */
	if(WhatPiece(board, originx+k, originy-k) != OUT_OF_RANGE){
		COLOR_POSITION = ColorPiece(board->Board[originx + k][originy - k]);
		while(originx + k <= 7 && originy - k >= 0 && COLOR_POSITION != COLOR_PIECE){
			COLOR_POSITION = ColorPiece(board->Board[originx + k][originy - k]);
			if(COLOR_PIECE == COLOR_POSITION){
				break;
			}
			InsertMove(AllMoves, originx, originy, originx + k, originy - k);
			/* Para o loop caso tenha chegado na posição de uma peça adversária */
			if(COLOR_POSITION == OPPOSITE_COLOR){
				break;
			}
			k++;
		}
	}
	k = 1;
	/* Verifica a cor da peça que está na posição */
	if(WhatPiece(board, originx-k, originy+k) != OUT_OF_RANGE){
		COLOR_POSITION = ColorPiece(board->Board[originx - k][originy + k]);
		while(originx - k >= 0 && originy + k <= 7 && COLOR_POSITION != COLOR_PIECE){
			COLOR_POSITION = ColorPiece(board->Board[originx - k][originy + k]);
			if(COLOR_PIECE == COLOR_POSITION){
				break;
			}
			InsertMove(AllMoves, originx, originy, originx - k, originy + k);
			/* Para o loop caso tenha chegado na posição de uma peça adversária */
			if(COLOR_POSITION == OPPOSITE_COLOR){
				break;
			}
			k++;
		}
	}

	return AllMoves;
}

/* Função: QueenMovements
		Objetivo: Calcular todos os movimentos possíveis para uma rainha dada uma
		determinada configuração de tabuleiro.

		Parametros:
			board - Ponteiro para um tabuleiro.
					Não deve ser nulo
			AllMoves - Ponteiro para uma lista de movimentos.
					Não deve ser nulo
			originx - Inteiro representando a coordenada x da posição (x,y) a ser verificada.
				   Deve ser um valor entre 0 e 7.
			originy - Inteiro representando a coordenada y da posição (x,y) a ser verificada.
				     Deve ser um valor entre 0 e 7.

		Saída: Essa função retorna a lista de movimentos com os movimentos possíveis da rainha
		adicionados.
*/

ListOfMoves* QueenMovements(TBoard* board, ListOfMoves* AllMoves, int originx, int originy){
	char piece;
	int k, COLOR_PIECE, COLOR_POSITION, OPPOSITE_COLOR;

	if(board == NULL || AllMoves == NULL){
		return NULL;
	}
	/* Determina a cor da peça e a oposta*/
	piece = WhatPiece(board, originx, originy);
	COLOR_PIECE = ColorPiece(piece);
	if(COLOR_PIECE == BLACK){
		OPPOSITE_COLOR = WHITE;
	}
	else{
		OPPOSITE_COLOR = BLACK;
	}
	/* Movimentos na horizontal e na vertical */
	k = 1;
	/* Verifica a cor da peça que está na posição */
	if(WhatPiece(board, originx+k, originy) != OUT_OF_RANGE){
		COLOR_POSITION = ColorPiece(board->Board[originx + k][originy]);
		while(originx + k <= 7 && COLOR_POSITION != COLOR_PIECE){
			COLOR_POSITION = ColorPiece(board->Board[originx + k][originy]);
			if(COLOR_PIECE == COLOR_POSITION){
				break;
			}
			InsertMove(AllMoves, originx, originy, originx + k, originy);
			/* Para o loop caso tenha chegado na posição de uma peça adversária */
			if(COLOR_POSITION == OPPOSITE_COLOR){
				break;
			}
			k++;
		}
	}
	k = 1;
	if(WhatPiece(board, originx-k, originy) != OUT_OF_RANGE){
		COLOR_POSITION = ColorPiece(board->Board[originx - k][originy]);
		while(originx - k >= 0 && COLOR_POSITION != COLOR_PIECE){
			COLOR_POSITION = ColorPiece(board->Board[originx - k][originy]);
			if(COLOR_PIECE == COLOR_POSITION){
				break;
			}
			InsertMove(AllMoves, originx, originy, originx - k, originy);
			if(COLOR_POSITION == OPPOSITE_COLOR){
				break;
			}			
			k++;
		}
	}
	k = 1;
	if(WhatPiece(board, originx, originy+k) != OUT_OF_RANGE){
		COLOR_POSITION = ColorPiece(board->Board[originx][originy + k]);
		while(originy + k <= 7 && COLOR_POSITION != COLOR_PIECE){
			COLOR_POSITION = ColorPiece(board->Board[originx][originy + k]);
			if(COLOR_PIECE == COLOR_POSITION){
				break;
			}
			InsertMove(AllMoves, originx, originy, originx, originy + k);
			if(COLOR_POSITION == OPPOSITE_COLOR){
				break;
			}			
			k++;
		}
	}
	k = 1;
	if(WhatPiece(board, originx, originy-k) != OUT_OF_RANGE){
		COLOR_POSITION = ColorPiece(board->Board[originx][originy - k]);
		while(originy - k >= 0 && COLOR_POSITION != COLOR_PIECE){
			COLOR_POSITION = ColorPiece(board->Board[originx][originy - k]);
			if(COLOR_PIECE == COLOR_POSITION){
				break;
			}
			InsertMove(AllMoves, originx, originy, originx, originy - k);				
			if(COLOR_POSITION == OPPOSITE_COLOR){
				break;
			}			
			k++;
		}
	}
	/* Movimentos na diagonal */
	/* Verifica a cor da peça que está na posição */
	k = 1;
	if(WhatPiece(board, originx+k, originy+k) != OUT_OF_RANGE){
		COLOR_POSITION = ColorPiece(board->Board[originx + k][originy + k]);
		while(originx + k <= 7 && originy + k <= 7 && COLOR_POSITION != COLOR_PIECE){
			COLOR_POSITION = ColorPiece(board->Board[originx + k][originy + k]);
			if(COLOR_PIECE == COLOR_POSITION){
				break;
			}
			InsertMove(AllMoves, originx, originy, originx + k, originy + k);
			/* Para o loop caso tenha chegado na posição de uma peça adversária */
			if(COLOR_POSITION == OPPOSITE_COLOR){
				break;
			}
			k++;
		}
	}
	k = 1;
	/* Verifica a cor da peça que está na posição */
	if(WhatPiece(board, originx-k, originy-k) != OUT_OF_RANGE){
		COLOR_POSITION = ColorPiece(board->Board[originx - k][originy - k]);
		while(originx - k >= 0 && originy - k >= 0 && COLOR_POSITION != COLOR_PIECE){
			COLOR_POSITION = ColorPiece(board->Board[originx - k][originy - k]);
			if(COLOR_PIECE == COLOR_POSITION){
				break;
			}
			InsertMove(AllMoves, originx, originy, originx - k, originy - k);
			/* Para o loop caso tenha chegado na posição de uma peça adversária */
			if(COLOR_POSITION == OPPOSITE_COLOR){
				break;
			}
			k++;
		}
	}
	k = 1;
	/* Verifica a cor da peça que está na posição */
	if(WhatPiece(board, originx+k, originy-k) != OUT_OF_RANGE){
		COLOR_POSITION = ColorPiece(board->Board[originx + k][originy - k]);
		while(originx + k <= 7 && originy - k >= 0 && COLOR_POSITION != COLOR_PIECE){
			COLOR_POSITION = ColorPiece(board->Board[originx + k][originy - k]);
			if(COLOR_PIECE == COLOR_POSITION){
				break;
			}
			InsertMove(AllMoves, originx, originy, originx + k, originy - k);
			/* Para o loop caso tenha chegado na posição de uma peça adversária */
			if(COLOR_POSITION == OPPOSITE_COLOR){
				break;
			}
			k++;
		}
	}
	k = 1;
	/* Verifica a cor da peça que está na posição */
	if(WhatPiece(board, originx-k, originy+k) != OUT_OF_RANGE){
		COLOR_POSITION = ColorPiece(board->Board[originx - k][originy + k]);
		while(originx - k >= 0 && originy + k <= 7 && COLOR_POSITION != COLOR_PIECE){
			COLOR_POSITION = ColorPiece(board->Board[originx - k][originy + k]);
			if(COLOR_PIECE == COLOR_POSITION){
				break;
			}
			InsertMove(AllMoves, originx, originy, originx - k, originy + k);
			/* Para o loop caso tenha chegado na posição de uma peça adversária */
			if(COLOR_POSITION == OPPOSITE_COLOR){
				break;
			}
			k++;
		}
	}

	return AllMoves;
}

/* Função: TowerMovements
		Objetivo: Calcular todos os movimentos possíveis para um rei dada uma
		determinada configuração de tabuleiro.

		Parametros:
			board - Ponteiro para um tabuleiro.
					Não deve ser nulo
			AllMoves - Ponteiro para uma lista de movimentos.
					Não deve ser nulo
			originx - Inteiro representando a coordenada x da posição (x,y) a ser verificada.
				   Deve ser um valor entre 0 e 7.
			originy - Inteiro representando a coordenada y da posição (x,y) a ser verificada.
				     Deve ser um valor entre 0 e 7.

		Saída: Essa função retorna a lista de movimentos com os movimentos possíveis do rei
		adicionados.
*/

ListOfMoves* KingMovements(TBoard* board, ListOfMoves* AllMoves, int originx, int originy){
	char piece;
	int COLOR_PIECE, COLOR_POSITION;
	if(board == NULL || AllMoves == NULL){
		return NULL;
	}
	/* Determina a cor da peça */
	piece = WhatPiece(board, originx, originy);
	COLOR_PIECE = ColorPiece(piece);

	/* Movimentos na horizontal e na vertical */
	if(WhatPiece(board, originx+1, originy) != OUT_OF_RANGE){
		COLOR_POSITION = ColorPiece(board->Board[originx + 1][originy]);
		if(originx + 1 <= 7 && COLOR_POSITION != COLOR_PIECE){
			InsertMove(AllMoves, originx, originy, originx + 1, originy);
		}
	}
	if(WhatPiece(board, originx, originy+1) != OUT_OF_RANGE){
		COLOR_POSITION = ColorPiece(board->Board[originx][originy + 1]);
		if(originy + 1 <= 7 && COLOR_POSITION != COLOR_PIECE){
			InsertMove(AllMoves, originx, originy, originx, originy + 1);
		}
	}
	if(WhatPiece(board, originx-1, originy) != OUT_OF_RANGE){
		COLOR_POSITION = ColorPiece(board->Board[originx - 1][originy]);
		if(originx - 1 >= 0 && COLOR_POSITION != COLOR_PIECE){
			InsertMove(AllMoves, originx, originy, originx - 1, originy);
		}
	}
	if(WhatPiece(board, originx, originy-1) != OUT_OF_RANGE){
		COLOR_POSITION = ColorPiece(board->Board[originx][originy - 1]);
		if(originy - 1 >= 0 && COLOR_POSITION != COLOR_PIECE){
			InsertMove(AllMoves, originx, originy, originx, originy - 1);
		}
	}
	
	/* Movimentos na diagonal */
	if(WhatPiece(board, originx+1, originy+1) != OUT_OF_RANGE){
		COLOR_POSITION = ColorPiece(board->Board[originx + 1][originy + 1]);
		if(originx + 1 <= 7 && originy + 1 <= 7&& COLOR_POSITION != COLOR_PIECE){
			InsertMove(AllMoves, originx, originy, originx + 1, originy + 1);
		}
	}
	if(WhatPiece(board, originx-1, originy-1) != OUT_OF_RANGE){
		COLOR_POSITION = ColorPiece(board->Board[originx - 1][originy - 1]);
		if(originx - 1 >= 0 && originy - 1 >= 0 && COLOR_POSITION != COLOR_PIECE){
			InsertMove(AllMoves, originx, originy, originx - 1, originy - 1);
		}
	}
	if(WhatPiece(board, originx+1, originy-1) != OUT_OF_RANGE){
		COLOR_POSITION = ColorPiece(board->Board[originx + 1][originy - 1]);
		if(originx + 1 <= 7 && originy - 1 >= 0 && COLOR_POSITION != COLOR_PIECE){
			InsertMove(AllMoves, originx, originy, originx + 1, originy - 1);
		}
	}
	if(WhatPiece(board, originx-1, originy+1) != OUT_OF_RANGE){
		COLOR_POSITION = ColorPiece(board->Board[originx - 1][originy + 1]);
		if(originx - 1 >= 0 && originy + 1 <= 7 && COLOR_POSITION != COLOR_PIECE){
			InsertMove(AllMoves, originx, originy, originx - 1, originy + 1);
		}
	}
	/* Roque */
	if( piece == B_KING && originx == 0 && originy == 4){
		/* Roque pequeno */
		if(WhatPiece(board, 0, 7) == B_TOWER && board->Board[0][5] == BLANK && board->Board[0][6] == BLANK){
			InsertMove(AllMoves, 0, 4, 0, 6);
		}
		/* Roque grande */
		if(WhatPiece(board, 0, 0) == B_TOWER && board->Board[0][1] == BLANK && board->Board[0][2] == BLANK && board->Board[0][3] == BLANK){
			InsertMove(AllMoves, 0, 4, 0, 2);
		}
	}
	if(piece == W_KING && originx == 7 && originy == 4){
		/* Roque pequeno */
		if(WhatPiece(board, 7, 7) == W_TOWER && board->Board[7][5] == BLANK && board->Board[7][6] == BLANK){
			InsertMove(AllMoves, 7, 4, 7, 6);
		}
		/* Roque grande */
		if(WhatPiece(board, 7, 0) == W_TOWER && board->Board[7][1] == BLANK && board->Board[7][2] == BLANK && board->Board[7][3] == BLANK){
			InsertMove(AllMoves, 7, 4, 7, 2);
		}
	}
/*
	if((AllMoves->howmany - old_howmany) == 0 && COLOR_PIECE == WHITE && board->WhiteCheck == CHEQUE){
		board->WhiteCheck = CHEQUE_MATE;
	}
	else if((AllMoves->howmany - old_howmany) == 0 && COLOR_PIECE == BLACK && board->BlackCheck == CHEQUE){
		board->BlackCheck = CHEQUE_MATE;
	}*/

	return AllMoves;
}


/* Função: AnalyzePossibleMovementsWhite
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

	int i, j;
	ListOfMoves* AllMoves = CreateListOfMoves();
	AllMoves->howmany = 0;

	/* Percorrendo o tabuleiro. */
	for(i = 0; i < 8; i++){
		for(j = 0; j < 8; j++){
			if(board->Board[i][j] == W_PAWN){
				AllMoves = WhitePawnMovements(board, AllMoves, i, j);
			}
			else if(board->Board[i][j] == W_HORSE){
				AllMoves = HorseMovements(board, AllMoves, i, j);
			}
			else if(board->Board[i][j] == W_KING){
				AllMoves = KingMovements(board, AllMoves, i, j);
			}
			else if(board->Board[i][j] == W_QUEEN){
				AllMoves = QueenMovements(board, AllMoves, i, j);
			}
			else if(board->Board[i][j] == W_TOWER){
				AllMoves = TowerMovements(board, AllMoves, i, j);
			}
			else if(board->Board[i][j] == W_BISHOP){
				AllMoves = BishopMovements(board, AllMoves, i, j);
			}
		}
	}
	return AllMoves;
}

/* Função: AnalyzePossibleMovementsBlack
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

	int i, j;
	ListOfMoves* AllMoves = CreateListOfMoves();
	AllMoves->howmany = 0;

	/* Percorrendo o tabuleiro. */
	for(i = 0; i < 8; i++){
		for(j = 0; j < 8; j++){
			if(board->Board[i][j] == B_PAWN){
				AllMoves = BlackPawnMovements(board, AllMoves, i, j);
			}
			else if(board->Board[i][j] == B_HORSE){
				AllMoves = HorseMovements(board, AllMoves, i, j);
			}
			else if(board->Board[i][j] == B_KING){
				AllMoves = KingMovements(board, AllMoves, i, j);
			}
			else if(board->Board[i][j] == B_QUEEN){
				AllMoves = QueenMovements(board, AllMoves, i, j);
			}
			else if(board->Board[i][j] == B_TOWER){
				AllMoves = TowerMovements(board, AllMoves, i, j);
			}
			else if(board->Board[i][j] == B_BISHOP){
				AllMoves = BishopMovements(board, AllMoves, i, j);
			}
		}
	}
	return AllMoves;
}

/* Função: VerifyValidMovent 
	Objetivo: Verifica se um movimento é valido para uma determinada configuração de tabuleiro.

		board - Ponteiro para um tabuleiro.
			Não deve ser nulo
		AllMoves - Ponteiro para uma lista de movimentos.
			Não deve ser nulo
		originx - Inteiro representando a coordenada x da posição (x,y) a ser verificada.
			Deve ser um valor entre 0 e 7.
		originy - Inteiro representando a coordenada y da posição (x,y) a ser verificada.
			Deve ser um valor entre 0 e 7.
		destinyx - Inteiro representando a coordenada x da posição de destino (x,y) a ser verificada.
			Deve ser um valor entre 0 e 7.
		destinyy - Inteiro representando a coordenada y da posição de destubi (x,y) a ser verificada.
			Deve ser um valor entre 0 e 7.			

		Saída: Essa 
*/
int VerifyValidMovement(TBoard* board, int originx, int originy, int destinyx, int destinyy){
	char piece;

	piece = WhatPiece(board, originx, originy);
	if(board == NULL){
		return -1;	
	}

	ListOfMoves* AllMoves = CreateListOfMoves();
	
	/* Calcula os movimentos possíveis de acordo com a peça e em caso de xeque 
	calcula os movimentos que possam tirar o rei do xeque */
	if(board->WhiteCheck == CHECK && ColorPiece(piece) == WHITE){
		AllMoves = VerifyCheckMate(board, WHITE);
	}
	else if(board->BlackCheck == CHECK && ColorPiece(piece == BLACK)){
		AllMoves = VerifyCheckMate(board, BLACK);
	}
	else if(piece == W_PAWN){
		AllMoves = WhitePawnMovements(board, AllMoves, originx, originy);
	}
	else if(piece == B_PAWN){
		AllMoves = BlackPawnMovements(board, AllMoves, originx, originy);
	}
	else if(piece == W_HORSE || piece == B_HORSE){
		AllMoves = HorseMovements(board, AllMoves, originx, originy);
	}
	else if(piece == W_TOWER || piece == B_TOWER){
		AllMoves = TowerMovements(board, AllMoves, originx, originy);
	}
	else if(piece == W_BISHOP || piece == B_BISHOP){
		AllMoves = BishopMovements(board, AllMoves, originx, originy);
	}
	else if(piece == W_QUEEN || piece == B_QUEEN){
		AllMoves = QueenMovements(board, AllMoves, originx, originy);
	}
	else if(piece == W_KING || piece == B_KING){
		AllMoves = KingMovements(board, AllMoves, originx, originy);
	}
	else{
		DeleteListOfMoves(AllMoves);
		return -1;
	}
	/* Busca o movimento na lista de movimentos possíveis */
	if(!SearchListOfMoves(AllMoves, originx, originy, destinyx, destinyy)){
		DeleteListOfMoves(AllMoves);
		/* Caso o rei da mesma cor estivesse em xeque e o movimento foi encontrado 
		na lista de movimentos capazes de tira-lo do xeque, o movimento é válido */
		if((board->WhiteCheck == CHECK && ColorPiece(piece) == WHITE) || (board->BlackCheck == CHECK && ColorPiece(piece) == BLACK)){
			return 1;
		}
		/* Caso o rei de mesma cor não estivesse em xeque e o movimento foi encontrado
		na lista de movimentos possíveis para aquela peça, é testado se o movimento causa
		xeque em seu rei. */
		else{
			TBoard *temp = AlocateBoard();
			copy_boards(temp, board);
			MovePiece(temp, originx, originy, destinyx, destinyy);
			temp = VerifyCheck(temp, ColorPiece(piece));
			/* Caso ponha o seu rei em xeque o movimento é inválido */
			if((ColorPiece(piece) == WHITE && temp->WhiteCheck == CHECK) || (ColorPiece(piece) == BLACK && temp->BlackCheck == CHECK)){
				free(temp);
				return 0;
			}
			/* Caso contrário é válido */
			else{
				free(temp);
				return 1;
			}
		}	
	}
	else{
		DeleteListOfMoves(AllMoves);
		return 0;
	}
}

/* Função: VerifyCheck
		Objetivo: Verificar se uma determinada configuração do tabuleiro deixa algum rei em xeque.

		Parametros:
			board - Ponteiro para um tabuleiro.
					Não deve ser nulo
			color - Cor do rei em questão.

		Saída: Essa função retorna um tabuleiro com sua variavél dedicada a xeque atualizada.
*/
TBoard* VerifyCheck(TBoard* board, int color){

	if(board == NULL){
		return NULL;	
	}

	if(color == BLACK){
		ListOfMoves* AllMoves = AnalyzePossibleMovementsWhite(board);
		AllMoves->current = AllMoves->first;
		while(AllMoves->current != NULL){
			char whichis = WhatPiece(board, AllMoves->current->play.destiny[0], AllMoves->current->play.destiny[1]);
			if(whichis == B_KING){
				board->BlackCheck = 1;
				DeleteListOfMoves(AllMoves);
				return board;	
			}
		AllMoves->current = AllMoves->current->next;
		}
		board->BlackCheck = 0;
		DeleteListOfMoves(AllMoves);
		return board;
	}
	if(color == WHITE){
		ListOfMoves* AllMoves = AnalyzePossibleMovementsBlack(board);
		AllMoves->current = AllMoves->first;
		while(AllMoves->current != NULL){
			char whichis = WhatPiece(board, AllMoves->current->play.destiny[0], AllMoves->current->play.destiny[1]);
			if(whichis == W_KING){
				board->WhiteCheck = 1;
				DeleteListOfMoves(AllMoves);
				return board;
			}
		AllMoves->current = AllMoves->current->next;
		}
		board->WhiteCheck = 0;
		DeleteListOfMoves(AllMoves);
		return board;
	}
	return NULL;
}

/* Função: VerifyCheckMate
		Objetivo: Verificar se caso o rei esteja em xeque, se é xeque mate.

		Parametros:
			board - Ponteiro para um tabuleiro.
					Não deve ser nulo
			color - Cor do rei em questão.
					Deve ser 1 ou 0.
		Saída: Essa função retorna NULL em caso de xeque mate e uma lista de móvimentos para sair
		do xeque em caso contrário.
*/
ListOfMoves* VerifyCheckMate(TBoard* board, int color){
	int originx, originy, destinyx, destinyy;
	if(board == NULL || (color != WHITE && color != BLACK)){
		return NULL;
	}
	TBoard* temp = AlocateBoard();
	ListOfMoves* AllMoves = NULL;
	ListOfMoves *LeaveCheck = CreateListOfMoves();
	if(color == WHITE && board->WhiteCheck == CHECK){
		AllMoves = AnalyzePossibleMovementsWhite(board);
		AllMoves->current = AllMoves->first;
		/* Verifica se existe algum movimento que possa tirar o rei do xeque */
		while(AllMoves->current != NULL){
			originx = AllMoves->current->play.origin[0];
			originy = AllMoves->current->play.origin[1];
			destinyx = AllMoves->current->play.destiny[0];
			destinyy = AllMoves->current->play.destiny[1];
			copy_boards(temp, board);
			MovePiece(temp, originx, originy, destinyx, destinyy);
			temp = VerifyCheck(temp, WHITE);
			if(temp->WhiteCheck != CHECK){
				InsertMove(LeaveCheck, originx, originy, destinyx, destinyy);
			}	
			AllMoves->current = AllMoves->current->next;
		}
		if(LeaveCheck->howmany != 0){
			free(temp);
			DeleteListOfMoves(AllMoves);
			return LeaveCheck;
		}
	}
	else if(color == BLACK && board->BlackCheck == CHECK){
		AllMoves = AnalyzePossibleMovementsBlack(board);
		AllMoves->current = AllMoves->first;
		/* Verifica se existe algum movimento que possa tirar o rei do xeque */		
		while(AllMoves->current != NULL){
			originx = AllMoves->current->play.origin[0];
			originy = AllMoves->current->play.origin[1];
			destinyx = AllMoves->current->play.destiny[0];
			destinyy = AllMoves->current->play.destiny[1];
			copy_boards(temp, board);
			MovePiece(temp, originx, originy, destinyx, destinyy);
			temp = VerifyCheck(temp, BLACK);
			if(temp->BlackCheck != CHECK){
				InsertMove(LeaveCheck, originx, originy, destinyx, destinyy);
			}	
			AllMoves->current = AllMoves->current->next;
		}
		if(LeaveCheck->howmany != 0){
			free(temp);
			DeleteListOfMoves(AllMoves);
			return LeaveCheck;			
		}
	}

	free(temp);
	DeleteListOfMoves(AllMoves);
	DeleteListOfMoves(LeaveCheck);
	return NULL;
}
