#include <stdio.h>
#include <stdlib.h>
#include "../include/tabuleiro.h"


/*
  Função: Alocar novo tabuleiro
        Objetivo:
            Alocar espaço na memória para um tabuleiro.

        Parâmetros:
            A função não possui parâmetros.

        Retorno:
            A função retorna um elemento tabuleiro inicializado com peso zerado
            e diferente de nulo.
*/
TBoard* AlocateBoard(void){
	TBoard* new_board = (TBoard*) malloc(sizeof(TBoard));
	new_board->Weight = 0;
	return new_board;
}

/* Função: StartEmptyBoard
		Objetivo: Iniciar um tabuleiro vazio em todas as suas posições.

		Parametros:
			board - Ponteiro para a estrutura do tabuleiro.
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
			board - Ponteiro para a estrutura do tabuleiro.
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

int ColorPiece(char piece){

}
/* Função: WhatPiece
		Objetivo: Verificar qual peça se encontra na posição (x,y) do tabuleiro.

		Parametros:
			board - Ponteiro para a estrutura do tabuleiro.
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
			board - Ponteiro para a estrutura do tabuleiro.
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

/* Função: InsertPiece
		Objetivo: inserir uma peça na coordenada (x,y) do tabuleiro.

		Parametros:
			board - Ponteiro para a estrutura do tabuleiro.
					Não deve ser nulo
			line - Inteiro representando a linha x da posição (x,y) da peça a ser inserida.
				   Deve ser um valor entre 0 e 7.
			column - Inteiro representando a coluna y da posição (x,y) da peça a ser inserida.
				     Deve ser um valor entre 0 e 7.
			piece - Peça a ser inserida.
					Deve ser uma das peças existentes.

		Saída: Essa função retorna, por parâmetro, o tabuleiro coma a nova peça e com seu peso modificado.
		       Retorna também um inteiro indicando seu funcionamento, sendo -1 para falhas e 0 para correto funcionamento.
*/
int InsertPiece(TBoard *board, char piece, int line, int column){
	/* Verificar x e y. */
	if(line<0 || line>7 || column<0 || column>7){
		return -1;
	}
	/* Verificar se a peça é válida */
	if(GetValue(piece) == 0){
		return -1;
	}
	/* Verifcar tabuleiro */
	if(board == NULL){
		return -1;
	}
	
	board->Board[line][column] = piece;
	board->Weight = board->Weight + GetValue(piece);

	return 0;
}

/* Função: ValidBoard
		Objetivo: Verificar se um tabuleiro é válido ou não para jogar.

		Parametros:
			board - Ponteiro para a estrutura do tabuleiro.
					Não deve ser nulo

		Saída: Essa função retorna 1, cao o tabuleiro seja válido, 0, caso seja inválido ou -1, caso o ponteiro do tabuleiro seja nulo.
*/
int ValidBoard(TBoard *board){
	/* Veriificar tabuleiro. */
	if(board == NULL){
		return -1;
	}

	int i, j;

	/* Iniciar Contadores. */
	int W_King = 0;
	int B_King = 0;
	int W_Pawn = 0;
	int B_Pawn = 0;
	int W_Queen = 0;
	int B_Queen = 0;
	int W_Horse = 0;
	int B_Horse = 0;
	int W_Bishop = 0;
	int B_Bishop = 0;
	int W_Tower = 0;
	int B_Tower = 0;

	/* Contar quantidades de cada tipo de peças no tabuleiro. */
	for(i=0; i < 8; i++){
		for(j=0; j < 8; j++){
			if(board->Board[i][j] == W_KING)
				W_King++;
			else if(board->Board[i][j] == B_KING)
				B_King++;
			else if(board->Board[i][j] == W_QUEEN)
				W_Queen++;
			else if(board->Board[i][j] == B_QUEEN)
				B_Queen++;
			else if(board->Board[i][j] == W_HORSE)
				W_Horse++;
			else if(board->Board[i][j] == B_HORSE)
				B_Horse++;
			else if(board->Board[i][j] == W_BISHOP)
				W_Bishop++;
			else if(board->Board[i][j] == B_BISHOP)
				B_Bishop++;
			else if(board->Board[i][j] == W_TOWER)
				W_Tower++;
			else if(board->Board[i][j] == B_TOWER)
				B_Tower++;
			else if(board->Board[i][j] == W_PAWN)
				W_Pawn++;
			else if(board->Board[i][j] == B_PAWN)
				B_Pawn++;
		}
	}

	int sum_white = 0;
	int sum_black = 0;

	/* Somar quantidades de peças brancas extras. */
	if(W_Queen != 0){
		sum_white = sum_white + W_Queen-1;
	}
	if(W_Horse != 0){
		if(W_Horse == 1)
			sum_white = sum_white + W_Horse-1;
		else
			sum_white = sum_white + W_Horse-2;
	}
	if(W_Bishop != 0){
		if(W_Bishop == 1)
			sum_white = sum_white + W_Bishop-1;
		else
			sum_white = sum_white + W_Bishop-2;
	}
	if(W_Tower != 0){
		if(W_Tower == 1)
			sum_white = sum_white + W_Tower-1;
		else
			sum_white = sum_white + W_Tower-2;
	}

	/* Somar quantidades de peças pretas extras. */
	if(B_Queen != 0){
		sum_black = sum_black + B_Queen-1;
	}
	if(B_Horse != 0){
		if(B_Horse == 1)
			sum_black = sum_black + B_Horse-1;
		else
			sum_black = sum_black + B_Horse-2;
	}
	if(B_Bishop != 0){
		if(B_Bishop == 1)
			sum_black = sum_black + B_Bishop-1;
		else
			sum_black = sum_black + B_Bishop-2;
	}
	if(B_Tower != 0){
		if(B_Tower == 1)
			sum_black = sum_black + B_Tower-1;
		else
			sum_black = sum_black + B_Tower-2;
	}

	/* Retornar 0 caso quantidade de cada rei for diferente de 1. */
	if(W_King != 1 || B_King != 1)
		return 0;
	
	/* Retornar 0 caso tenha mais de 8 peões de cada cor. */
	if(W_Pawn > 8 || B_Pawn > 8)
		return 0;

	/* Retornar 0 caso quantidade de peças extras de cada cor superar 8 menos peões. */
	if(sum_white > 8-W_Pawn || sum_black > 8-B_Pawn)
		return 0;

	return 1;
}

/* Função: ChangePiece
		Objetivo: Modificar uma peça na coordenada (x,y) do tabuleiro.

		Parametros:
			board - Ponteiro para a estrutura do tabuleiro.
					Não deve ser nulo
			line - Inteiro representando a linha x da posição (x,y) da peça a ser modificada.
				   Deve ser um valor entre 0 e 7.
			column - Inteiro representando a coluna y da posição (x,y) da peça a ser modificada.
				     Deve ser um valor entre 0 e 7.
			piece - Peça a ser inserida.
					Deve ser uma das peças existentes.

		Saída: Essa função retorna, por parâmetro, o tabuleiro coma a nova peça e com seu peso modificado.
		       Retorna também um inteiro indicando seu funcionamento, sendo -1 para falhas e 0 para correto funcionamento.
*/
int ChangePiece(TBoard *board, char piece, int line, int column){
	/* Verificar x e y. */
	if(line<0 || line>7 || column<0 || column>7){
		return -1;
	}
	/* Verificar se a peça é válida */
	if(GetValue(piece) == 0){
		return -1;
	}
	/* Verifcar tabuleiro */
	if(board == NULL){
		return -1;
	}

	/* Remover peça atual na posição. */
	RemovePiece(board, line, column);
	/* Inserir nova peça. */
	InsertPiece(board, piece, line, column);

	return 0;
}

/* Função: MovePiece
		Objetivo: Mover uma peça da coordenada (xo,yo) do tabuleiro para a (x,y).

		Parametros:
			board - Ponteiro para a estrutura do tabuleiro.
					Não deve ser nulo
			origin_line - Inteiro representando a linha xo da posição (xo,yo) da peça a ser movida.
				   Deve ser um valor entre 0 e 7.
			origin_column - Inteiro representando a coluna yo da posição (xo,yo) da peça a ser movida.
				     Deve ser um valor entre 0 e 7.
			dest_line - Inteiro representando a linha x da posição (x,y) da peça a ser movida.
				   Deve ser um valor entre 0 e 7.
			dest_column - Inteiro representando a coluna y da posição (x,y) da peça a ser movida.
				     Deve ser um valor entre 0 e 7.

		Saída: Essa função retorna, por parâmetro, o tabuleiro com a peça movida de lugar.
		       Retorna também um inteiro indicando seu funcionamento, sendo -1 para falhas e 0 para correto funcionamento.
*/
int MovePiece(TBoard *board, int origin_line, int origin_column, int dest_line, int dest_column){
	/* Verificar x, y, xo e yo. */
	if(origin_line<0 || origin_line>7 || origin_column<0 || origin_column>7){
		return -1;
	}
	if(dest_line<0 || dest_line>7 || dest_column<0 || dest_column>7){
		return -1;
	}

	/* Verifcar tabuleiro */
	if(board == NULL){
		return -1;
	}

	/* Salvar peça na posição de origem. */
	char piece = board->Board[origin_line][origin_column];

	/* Remover peça atual na posição de origem. */
	RemovePiece(board, origin_line, origin_column);

	/* Mudar peça na posição final. */
	ChangePiece(board, piece, dest_line, dest_column);

	return 0;
}

void copy_boards(TBoard* copy, TBoard* board){
	/* Contadores */
	int i, j;

	/* Copiando as peças dos dois tabuleiros */
	for(i = 0; i < 8; i++){
		for(j = 0; j < 8; j++){
			copy->Board[i][j] = board->Board[i][j];
		}
	}

	copy->Weight = board->Weight;
}
