#include <stdio.h>
#include <stdlib.h>
#include "../include/tabuleiro.h"

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
	/* Testar entrada. */
	if(board == NULL){
		return 1;
	}

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

/* Função: WhatPiece
		Objetivo: Verificar qual peça se encontra na posição (x,y) do tabuleiro.

		Parametros:
			board - Ponteiro para a estrutura da árvore.
					Não deve ser nulo
			line - Inteiro representando a linha x da posição (x,y) a ser verificada.
				   Deve ser um valor entre 0 e 7.
			column - Inteiro representando a coluna y da posição (x,y) a ser verificada.
				     Deve ser um valor entre 0 e 7.

		Saída: Essa função retorna o caractere correspondente da posição analisada.
*/
char WhatPiece(TBoard *board, int line, int column){
	/* Veriificar tabuleiro. */
	if(board == NULL){
		return OUT_OF_RANGE;
	}

	/* Verificar x e y. */
	if(line<0 || line>7 || column<0 || column>7){
		return OUT_OF_RANGE;
	}

	return board->Board[line][column];
}

/* Função: GetValue
		Objetivo: Verificar o valor de uma determinada peça.

		Parametros:
			piece - Peça a ser verificada, seguindo as constantes definidas.

		Saída: Essa função retorna um valor inteiro correspondente da peça, verificados a seguir:
				Os valores, em módulo, para as peças são:
				Peões - 1;
				Cavalos e Bispos - 3;
				Torres - 5;
				Rainhas - 9;
				Reis - 200;
				Espaço em branco - 0;
				Sendo que as peças pretas assumem valores negativos e as brancas, positivos.
*/
int GetValue(char piece){
	if(piece == W_PAWN){
		return 1;
	}

	else if(piece == B_PAWN){
		return -1;
	}

	else if(piece == W_BISHOP || piece == W_HORSE){
		return 3;
	}

	else if(piece == B_BISHOP || piece == B_HORSE){
		return -3;
	}

	else if(piece == W_TOWER){
		return 5;
	}

	else if(piece == B_TOWER){
		return -5;
	}

	else if(piece == W_QUEEN){
		return 9;
	}

	else if(piece == B_QUEEN){
		return -9;
	}

	else if(piece == W_KING){
		return 200;
	}

	else if(piece == B_KING){
		return -200;
	}

	else{
		return 0;
	}
}

/* Função: RemovePiece
		Objetivo: Remover uma peça da coordenada (x,y) do tabuleiro.

		Parametros:
			board - Ponteiro para a estrutura da árvore.
					Não deve ser nulo
			line - Inteiro representando a linha x da posição (x,y) da peça a ser removida.
				   Deve ser um valor entre 0 e 7.
			column - Inteiro representando a coluna y da posição (x,y) da peça a ser removida.
				     Deve ser um valor entre 0 e 7.

		Saída: Essa função retorna, por parâmetro, o tabuleiro sem a peça e com seu peso modificado.
*/
void RemovePiece(TBoard *board, int line, int column){
	/* Get the piece in the position */
	char piece = WhatPiece(board, line, column);

	/* Return if out pf range. */
	if(piece == OUT_OF_RANGE){
		return;
	}

	/* Get value of the piece in the position. */
	int value = GetValue(piece);

	/* Subtrair o peso atual pelo valor obtido. */
	board->Weight = board->Weight - value;

	/* Definir posição como vazia. */
	board->Board[line][column] = BLANK;
}

int InsertPiece(TBoard *board, char peace, int line, int column){
	/* Verificar x e y. */
	if(line<0 || line>7 || column<0 || column>7){
		return -1;
	}
	/* Verificar se a peça é válida */
	if(GetValue(peace) == 0){
		return -1;
	}
}