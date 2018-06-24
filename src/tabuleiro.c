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