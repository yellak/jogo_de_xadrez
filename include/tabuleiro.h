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

/* Inicializar tabuleiro vazio. */
/*! \fn void StartEmptyBoard(TBoard *board)
		\brief Inicializa um tabuleiro sem nenhuma peça em todas as posições.

		\param board Ponteiro para um tabuleiro
		\return Por parâmetro, retorna o tabuleiro vazio e um inteiro indicando o funcionamento da função (0, caso funcione e 1 caso contrário).
*/
int StartEmptyBoard(TBoard *board);

/* Inicializar tabuleiro padrão. */
/*! \fn void StartStandardBoard(TBoard *board)
		\brief Inicializa um tabuleiro com as peças na posição padrão de um jogo de xadrez.
			   Peças pretas correspondem a parte "de cima" do tabuleiro (posições de (0.0) a (1,7)).
			   Peças brancas correspondem a parte de "baixo" do tabuleiro (posiçẽos de (6,0) a (7,7)).
			   As outras posições são vazias.

		\param board Ponteiro para um tabuleiro
		\return Por parâmetro, retorna o tabuleiro com as peças em posições padrões e um inteiro indicando o funcionamento da função (0, caso funcione e 1 caso contrário).
*/
int StartStandardBoard(TBoard *board);

#endif