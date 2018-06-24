#include <stdio.h>
#include <stdlib.h>
#include "tabuleiro.h"

/* Função: StartEmptyBoard
		Objetivo: Iniciar um tabuleiro vazio em todas as suas posições.

		Parametros:
			board - Ponteiro para a estrutura da árvore.

		Saída: Essa função retorna, por parâmetro, um tabuleiro vazio.
*/
void StartEmptyBoard(TBoard *board){
	int i, j; /*Variaveis auxiliare.*/

	/* Definir peso do tabuleiro como 0.*/
	board->Weight = 0;

	/* Iniciar as posições do tabuleiro como vazias. */
	for(i=0; i < 8;i++){
		for(j=0; j < 8;j++){
			board->Board[i][j] = BLANK;
		}
	}
}