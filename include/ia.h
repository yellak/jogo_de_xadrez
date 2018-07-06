#ifndef IA_H_
#define IA_H_

#include <stdio.h>
#include <stdlib.h>
#include "../include/logica.h"
#include "../include/arv_decisoes.h"

/* Constantes que indicam de quem é a vez de jogar */
const int BLACKS_TURN = 0;
const int WHITES_TURN = 1;

/* Criar a árvore com todas as jogadas. */
/*! \fn Tree* Create_BestTree(TBoard *board)
		\brief Criar a ávore com todas as jogadas

		\param board Ponteiro para o tabuleiro o qual se deseja encontrar as possíveis jogadas
		\param turn Inteiro contendo a informação de quem é jogada(Black = 0, White = 1)

		\return Ponteiro para a árvore com todos os filhos alocados
*/
Tree* Create_BestTree(TBoard *board, int turn);

#endif