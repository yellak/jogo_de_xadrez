#ifndef LOGICA_H_
#define LOGICA_H_

#include "../include/list_of_moves.h"
#include "../include/tabuleiro.h"

/* Funções para manipulação da lógica do xadrez: */

/*Analisa os movimentos possíveis em um tabuleiro em relação as peças pretas.*/
/*! \fn ListOfMoves AnalyzePossibleMovementsBlack(TBoard *board)
		\brief Armazena movimentos possíveis para cada peça preta.

		\param board Ponteiro para um tabuleiro.
		\return Retorna uma lista com os movimentos possíveis de acordo com as peças pretas.
*/
//ListOfMoves* AnalyzePossibleMovementsBlack(TBoard *board);

/*Analisa os movimentos possíveis em um tabuleiro em relação as peças brancas.*/
/*! \fn ListOfMoves AnalyzePossibleMovementsWhite(TBoard *board)
		\brief Armazena movimentos possíveis para cada peça branca.

		\param board Ponteiro para um tabuleiro.
		\return Retorna uma lista com os movimentos possíveis de acordo com as peças brancas.
*/
ListOfMoves* AnalyzePossibleMovementsWhite(TBoard *board);

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
