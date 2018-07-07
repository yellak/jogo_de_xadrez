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
/*! \fn Tree* CreateBestTree(TBoard *board)
		\brief Criar a ávore com todas as jogadas

		\param board Ponteiro para o tabuleiro o qual se deseja encontrar as possíveis jogadas
		\param turn Inteiro contendo a informação de quem é jogada(Black = 0, White = 1)

		\return Ponteiro para a árvore com todos os filhos alocados
*/
Tree* CreateMovesTree(TBoard *board, int turn);

/* Ordena a árvore de acordo com a melhor jogada de uma cor e seus filhos de acordo com a melhor jogada da outra cor */
/*! \fn int SortTree(Tree* tree, int turn)
		\brief Ordena a árvore para achar a melhor jogada

		\param board Ponteiro para o tabuleiro o qual se deseja encontrar as melhores possíveis jogadas
		\param turn Inteiro contendo a informação de quem é jogada(Black = 0, White = 1)

		\return Inteiro indicando sucesso(0) ou fracasso(1) da operação
*/
int SortTree(Tree* tree, int turn);

NodeList* Best_Plays(Tree* tree, int n_child);

#endif