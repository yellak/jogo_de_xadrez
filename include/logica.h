#ifndef LOGICA_H_
#define LOGICA_H_

#include "../include/tabuleiro.h"

/* Definição da estrutura que irá armazenar uma jogada possível a partir de um tabuleiro */
/*! \struct Move
		\brief Estrutura que irá caracterizar a jogada.

		Estrutura que armazena uma maneira de interpretar uma jogada.
*/
typedef struct Move{
	int origin[2]; /*!< Array que armazena as coordenadas de origem do movimento. */
	int destiny[2]; /*!< Array que armazena as coordenadas de destino do movimento. */
}Move;

/* Definição da estrutura que irá armazenar as jogadas possíveis a partir de um tabuleiro. */
/*! \struct ListOfMoves
		\brief Estrutura representará todas as possíveis jogadas de um tabuleiro.

		Array do tipo Move que é importante para a análise das jogadas.
*/
typedef struct ListOfMoves{
	int howmany; /*!< Inteiro que guarda quantas jogadas são possíveis de serem feitas. */
	Move *Plays; /*!< Array que armazena todas as jogadas possíveis com base em um tabuleiro. */
}ListOfMoves;

/* Funções para manipulação da lógica do xadrez: */

/*Analisa os movimentos possíveis em um tabuleiro em relação as peças pretas.*/
/*! \fn ListOfMoves AnalyzePossibleMovementsBlack(TBoard *board)
		\brief Armazena movimentos possíveis para cada peça preta.

		\param board Ponteiro para um tabuleiro.
		\return Retorna uma lista com os movimentos possíveis de acordo com as peças pretas.
*/
ListOfMoves* AnalyzePossibleMovementsBlack(TBoard *board);

/*Analisa os movimentos possíveis em um tabuleiro em relação as peças brancas.*/
/*! \fn ListOfMoves AnalyzePossibleMovementsWhite(TBoard *board)
		\brief Armazena movimentos possíveis para cada peça branca.

		\param board Ponteiro para um tabuleiro.
		\return Retorna uma lista com os movimentos possíveis de acordo com as peças brancas.
*/
ListOfMoves* AnalyzePossibleMovementsWhite(TBoard *board);

/*Libera memória dedicada a lista dos movimentos possíveis.*/
/*! \fn int DeleteMoveList(ListOfMoves* list)
		\brief Libera memória utilizada por uma lista.

		\param list uma lista de movimentos.
		\return Retorna um inteiro indicando a falha ou sucesso da operação.
*/
int DeleteMoveList(ListOfMoves* list);

/* \fn int verify_syntax_move(char chess_move[])
       \brief Verifica a validade da sintaxe da notação algébrica de um
              movimento de xadrez

       \param chess_move Strig com a notação

       \return True caso a sintaxe esteja correta ou false caso não esteja */
int verify_syntax_move(char chess_move[]);

/*! \fn Move* algebraic_translate(char chess_move[])
        \brief Traduz uma notação algébrica de um movimento de xadrez para um
               movimento normal na matriz do tabuleiro

         \param chess_move String com a notação algébrica do movimento

         \return Um elemento de movimento com a origem e o destino do movimento */
Move* algebraic_translate(char chess_move[]);

#endif
