#include <stdio.h>
#include <stdlib.h>
#include "tabuleiro.h"

/* Função: StartEmptyBoard
		Objetivo: Iniciar um tabuleiro vazio em todas as suas posições.

		Parametros:
			board - Ponteiro para a estrutura da árvore.
					Não deve ser nulo

		Saída: Essa função retorna, por parâmetro, um tabuleiro vazio e um inteiro para informar o funcionamento da função
			   (0 caso funcione e 1 caso contrário).
*/
int StartEmptyBoard(TBoard *board){
	/*Verificar entrada. */
	if(board == NULL){
		return 1;
	}

	int i, j; /*Variaveis auxiliares.*/

	/* Definir peso do tabuleiro como 0.*/
	board->Weight = 0;

	/* Iniciar as posições do tabuleiro como vazias. */
	for(i=0; i < 8;i++){
		for(j=0; j < 8;j++){
			board->Board[i][j] = BLANK;
		}
	}

	return 0;
}

/* Função: StartStandardBoard
		Objetivo: Iniciar um tabuleiro com as peças em posições padrões do xadrez.

		Parametros:
			board - Ponteiro para a estrutura da árvore.
					Não deve ser nulo

		Saída: Essa função retorna, por parâmetro, um tabuleiro com as peças em posições padrão e um inteiro para informar o funcionamento da função
			   (0 caso funcione e 1 caso contrário).
			   A posiçao padrao segue as regras abaixo:
			   -Peças pretas correspondem a parte "de cima" do tabuleiro (posições de (0.0) a (1,7)).
			   -Peças brancas correspondem a parte de "baixo" do tabuleiro (posiçẽos de (6,0) a (7,7)).
			   -As outras posições são vazias.
*/
int StartStandardBoard(TBoard *board){
	int i,j; /* Variaveis auxiliares. */

	/* Definir peso do tabuleiro como 0.*/
	board->Weight = 0;

	/* Posicionar Torres. */
	board->Board[0][0] = B_TOWER;
	board->Board[0][7] = B_TOWER;
	board->Board[7][0] = W_TOWER;
	board->Board[7][7] = W_TOWER;
	/* Posicionar Cavalos. */
	board->Board[0][1] = B_HORSE;
	board->Board[0][6] = B_HORSE;
	board->Board[7][1] = W_HORSE;
	board->Board[7][6] = W_HORSE;
	/* Posicionar Bispos. */
	board->Board[0][2] = B_BISHOP;
	board->Board[0][5] = B_BISHOP;
	board->Board[7][2] = W_BISHOP;
	board->Board[7][5] = W_BISHOP;
	/* Posicionar Reis. */
	board->Board[0][4] = B_KING;
	board->Board[7][4] = W_KING;
	/* Posicionar Rainhas. */
	board->Board[0][3] = B_QUEEN;
	board->Board[7][3] = W_QUEEN;
	/* Posicionar Peoes. */
	for(i=0; i < 8; i++){
		board->Board[1][i] = B_PAWN;
		board->Board[6][i] = W_PAWN;
	}
	/* Posicionar Espaços Vazios. */
	for(i=2; i < 6; i++){
		for(j=0; j < 8; j++){
			board->Board[i][j] = BLANK;
		}
	}

	return 0;
}