#ifndef TABULEIRO_H_
#define TABULEIRO_H_

const char W_KING = 'k';
const char W_QUEEN = 'q';
const char W_TOWER = 't';
const char W_BISHOP = 'b';
const char W_HORSE = 'h';
const char W_PAWN = 'p';
const char BLANK = '\\';
const char B_KING = 'K';
const char B_QUEEN = 'Q';
const char B_TOWER = 'T';
const char B_BISHOP = 'B';
const char B_HORSE = 'H';
const char B_PAWN = 'P';
const char OUT_OF_RANGE = '~';

/* Definição da estrutura do tabuleiro. */
/*! \struct TBoard
		\brief Estrutura do tabuleiro.

		Estrutura que armazena os elementos necessário para definir um tabuleiro.
*/
typedef struct board{
	char Board[8][8]; /*!< Matriz de caracteres que representa o tabuleiro. */
	int Weight; /*!< Inteiro que armazena o peso ponderado do tabuleiro. */
}TBoard;

/* Funções para manipulação do tabuleiro: */

/* Alocar espaço para tabuleiro */
/*! \fn TBoard* AlocateBoard(void)
        \brief Aloca espaço em memória para um elemento de tabuleiro

        \return Um elemento de tabuleiro diferente de nulo alocado dinamicamente
                inicializado com peso igual a zero
*/
TBoard* AlocateBoard(void);

/* Inicializar tabuleiro vazio. */
/*! \fn int StartEmptyBoard(TBoard *board)
		\brief Inicializa um tabuleiro sem nenhuma peça em todas as posições.

		\param board Ponteiro para um tabuleiro.
		\return Por parâmetro, retorna o tabuleiro vazio e um inteiro indicando o funcionamento da função (0, caso funcione e 1 caso contrário).
*/
int StartEmptyBoard(TBoard *board);

/* Inicializar tabuleiro padrão. */
/*! \fn void StartStandardBoard(TBoard *board)
		\brief Inicializa um tabuleiro com as peças na posição padrão de um jogo de xadrez.
			   
	    Peças pretas correspondem a parte "de cima" do tabuleiro (posições de (0.0) a (1,7)).
		Peças brancas correspondem a parte de "baixo" do tabuleiro (posiçẽos de (6,0) a (7,7)).
		As outras posições são vazias.

		\param board Ponteiro para um tabuleiro.
		\return Por parâmetro, retorna o tabuleiro com as peças em posições padrões e um inteiro indicando o funcionamento da função (0, caso funcione e 1 caso contrário).
*/
int StartStandardBoard(TBoard *board);


/* Verificar qual peça se encontra na posição (x,y) do tabuleiro. */
/*! \fn char WhatPiece(TBoard *board, int line, int column)
		\brief Verifica qual peça se encontra na posição dada.
		
		\param board Ponteiro para um tabuleiro.
		\param line Inteiro indicando a linha x da posição (x,y) a ser verificada. Deve ser um número de 0 a 7.
		\param column Inteiro indicando a coluna y da posição (x,y) a ser verificada. Deve ser um número de 0 a 7.
		\return Retorna o caractere correspondente da peça na posição (x,y) ou OUT_OF_RANGE para posições não existentes.
*/
char WhatPiece(TBoard *board, int line, int column);

/* Verificar o valor de uma peça dada. */
/*! \fn int GetValue(char piece)
		\brief Verifica o valor de uma peça dada ou espaço vazio.
		 
		Os valores, em módulo, para as peças são:
		Peões - 1;
		Cavalos e Bispos - 3;
		Torres - 5;
		Rainhas - 9;
		Reis - 200;
		Espaço em branco - 0;
		Sendo que as peças pretas assumem valores negativos e as brancas, positivos.
		
		\param piece É um caractere representado por alguma das constantes de peças definidas.
		\return Retorna o valor da peça requisitada ou 0 para peças inválidas.
*/
int GetValue(char piece);

/* Remover do tabuleiro uma peça dada. */
/*! \fn void RemovePiece(TBoard *board, int line, int column)
		\brief Remove uma peça de uma posição e modifica o peso do tabuleiro.
		
		\param board Ponteiro para um tabuleiro.
		\param line Inteiro indicando a linha x da posição (x,y) da peça a ser removida. Deve ser um número de 0 a 7.
		\param column Inteiro indicando a coluna y da posição (x,y) da peça a ser removida. Deve ser um número de 0 a 7.
		\return Retorna, por parâmetro, o tabuleiro sem a peça e com seu peso modificado.
*/
void RemovePiece(TBoard *board, int line, int column);

/*Insere uma nova peça no tabuleiro.*/
/*! \fn void RemovePiece(TBoard *board, int line, int column)
		\brief Insere uma peça válida no tabuleiro.

		\param board Pontereiro para um tabuleiro.
		\param piece É um caractere representado por alguma das constantes de peças definidas.
		\param line Inteiro indicando a linha x da posição (x,y) da peça a ser removida. Deve ser um número de 0 a 7.
		\param column Inteiro indicando a coluna y da posição (x,y) da peça a ser removida. Deve ser um número de 0 a 7.
		\return Retorna, um inteiro indicando a falha ou sucesso da operação.
*/
int InsertPiece(TBoard *board, char piece, int line, int column);

#endif
