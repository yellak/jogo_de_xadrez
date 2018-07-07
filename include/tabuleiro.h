#ifndef TABULEIRO_H_
#define TABULEIRO_H_

const int WHITE = 1;
const int BLACK = 0;
const int CHECK = 1;

/* Constantes para as peças do jogo */
const char W_KING       = 'k';
const char W_QUEEN      = 'q';
const char W_TOWER      = 'r';
const char W_BISHOP     = 'b';
const char W_HORSE      = 'n';
const char W_PAWN       = 'p';
const char BLANK        = '\\';
const char B_KING       = 'K';
const char B_QUEEN      = 'Q';
const char B_TOWER      = 'R';
const char B_BISHOP     = 'B';
const char B_HORSE      = 'N';
const char B_PAWN       = 'P';
const char OUT_OF_RANGE = '~';

/* Definição da estrutura do tabuleiro. */
/*! \struct TBoard
		\brief Estrutura do tabuleiro.

		Estrutura que armazena os elementos necessário para definir um tabuleiro.
*/
typedef struct board{
	char Board[8][8]; /*!< Matriz de caracteres que representa o tabuleiro. */
	int Weight; /*!< Inteiro que armazena o peso ponderado do tabuleiro. */
	int WhiteCheck; /*!< Inteiro que armazena a condição de xeque do rei branco. */
	int BlackCheck; /*!< Inteiro que armazena a condição de xeque do rei preto. */
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
		\return Por parâmetro, retorna o tabuleiro vazio e um inteiro indicando
                o funcionamento da função (0, caso funcione e 1 caso contrário).
*/
int StartEmptyBoard(TBoard *board);

/* Inicializar tabuleiro padrão. */
/*! \fn void StartStandardBoard(TBoard *board)
		\brief Inicializa um tabuleiro com as peças na posição padrão de um
               jogo de xadrez.
			   
	    Peças pretas correspondem a parte "de cima" do tabuleiro (posições de
        (0.0) a (1,7)). Peças brancas correspondem a parte de "baixo" do
        tabuleiro (posiçẽos de (6,0) a (7,7)). As outras posições são vazias.

		\param board Ponteiro para um tabuleiro.

		\return Por parâmetro, retorna o tabuleiro com as peças em posições
                padrões e um inteiro indicando o funcionamento da função
                (0, caso funcione e 1 caso contrário).
*/
int StartStandardBoard(TBoard *board);

/* Verificar qual a cor da peça requisitada. */
/*! \fn int ColorPiece(char piece)
		\brief Dada uma determinada peça, verifica qual a cor dela.
		
		\param board Ponteiro para um tabuleiro.
		\param line Inteiro indicando a linha x da posição (x,y) a ser verificada. Deve ser um número de 0 a 7.
		\param column Inteiro indicando a coluna y da posição (x,y) a ser verificada. Deve ser um número de 0 a 7.
		\return Retorna o caractere correspondente da peça na posição (x,y) ou OUT_OF_RANGE para posições não existentes.
*/
int ColorPiece(char piece);

/* Verificar qual peça se encontra na posição (x,y) do tabuleiro. */
/*! \fn char WhatPiece(TBoard *board, int line, int column)
		\brief Verifica qual peça se encontra na posição dada.
		
		\param piece É um caractere representado por alguma das constantes de peças definidas.
		\return Retorna a constante definida BLACK ou WHITE para a cor da peça passada ou -1 se não for uma peça.
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
		\return Retorna, por parâmetro, o tabuleiro sem a peça e com seu peso modificado e um inteiro indicando seu funcionamento.
*/
void RemovePiece(TBoard *board, int line, int column);

/*Insere uma nova peça no tabuleiro.*/
/*! \fn void RemovePiece(TBoard *board, int line, int column)
		\brief Insere uma peça válida no tabuleiro.

		\param board Pontereiro para um tabuleiro.
		\param piece É um caractere representado por alguma das constantes de peças definidas.
		\param line Inteiro indicando a linha x da posição (x,y) da peça a ser inserida. Deve ser um número de 0 a 7.
		\param column Inteiro indicando a coluna y da posição (x,y) da peça a ser inserida. Deve ser um número de 0 a 7.
		\return Retorna um inteiro indicando a falha ou sucesso da operação.
*/
int InsertPiece(TBoard *board, char piece, int line, int column);

/* Verificar se um tabuleiro é válido. */
/*! \fn int ValidBoard(TBoard *board)
		\brief Verifica se um tabuleiro é válido para ser jogado ou não.
		
		\param board Ponteiro para um tabuleiro.
		\return Retorna 1 para caso seja válido ou 0, caso contrário.
*/
int ValidBoard(TBoard *board);

/* Mudar a peça em uma posição. */
/*! \fn int ChangePiece(TBoard *board, char piece, int line, int column)
		\brief Muda a peça em uma posição por outra.
		
		\param board Ponteiro para um tabuleiro.
		\param piece É um caractere representado por alguma das constantes de peças definidas.
		\param line Inteiro indicando a linha x da posição (x,y) da peça a ser modificada. Deve ser um número de 0 a 7.
		\param column Inteiro indicando a coluna y da posição (x,y) da peça a ser modificada. Deve ser um número de 0 a 7.
		\return Retorna 0 para caso seja válido ou -1, caso contrário. Por parâmetro, retorna o tabuleiro modificado.
*/
int ChangePiece(TBoard *board, char piece, int line, int column);

/* Mover a peça para outra posição. */
/*! \fn int MovePiece(TBoard *board, int origin_line, int origin_column, int dest_line, int dest_column)
		\brief Move a peça na posição (xo,yo) para a posição (x,y).
		
		\param board Ponteiro para um tabuleiro.
		\param origin_line Inteiro indicando a linha xo da posição (xo,yo) da peça a ser movida. Deve ser um número de 0 a 7.
		\param origin_column Inteiro indicando a coluna yo da posição (xo,yo) da peça a ser movida. Deve ser um número de 0 a 7.
		\param dest_line Inteiro indicando a linha x da posição (x,y) da peça a ser movida. Deve ser um número de 0 a 7.
		\param dest_column Inteiro indicando a coluna y da posição (x,y) da peça a ser movida. Deve ser um número de 0 a 7.
		\return Retorna 0 para caso seja válido ou -1, caso contrário. Por parâmetro, retorna o tabuleiro modificado.
*/
int MovePiece(TBoard *board, int origin_line, int origin_column, int dest_line, int dest_column);

/* Copiar dois tabuleiros */
/*! \fn void copy_boards(TBoard* copy, TBoard* board)
        \brief Copia todas as peças de um tabuleiro para outro e também os
               pesos.

        A função não possui retorno

        \param copy  Tabuleiro que será a cópia. Não deve ser nulo.
        \param board Tabuleiro que será copiado. Não deve ser nulo.

        \return 0, caso funcione adequadamente ou 1, caso contrário
*/
int copy_boards(TBoard* copy, TBoard* board);

/* Verificar se uma peça é válida */
/*! \fn int valid_piece(char piece)
        \brief Verifica se uma peça dada é uma peça de xadrez ou não

        \param piece Peça a ser verificada

        \return true  Se a peça é uma peça de xadrez
        \return false Se ela não for uma peça de xadrez */
int valid_piece(char piece);

/* Verificar tabuleiro mínino */
/*! \fn int HaveMinimun(TBoard* board)
        \brief Verifica se um tabuleiro é no máximo o mínimo para ser válido

        Por exemplo, o tabuleiro mínimo é um rei de cada cor, se tiver
		qualquer outra peça que não seja um rei ela retorna false, mas ela
		também retorna true para um tabuleiro com menos que o mínimo para ser
		válido como um tabuleiro vazio 

        \param board Tabuleiro que será verificado

        \return true  Se o tabuleiro obedece as condições estabelecidas
        \return false Se o tabuleiro não obedece as condições estabelecidas */
int HaveMinimun(TBoard* board);

#endif
