#ifndef _ARV_DECISOES_
#define _ARV_DECISOES_

#include "../include/tabuleiro.h"
#include "../include/logica.h"

/* Definição da estrutura de um nó da árvore de decisões */
/*! \struct NodeTree
		\brief Estrutura de um nó da árvore.

		Estrutura que armazena os componentes básicos de um nó da árvore de decisões
*/
typedef struct NodeTree{
	TBoard* board;	/*!< Ponteiro para uma variável do tipo Tboard que representa a organização do tabuleiro depois de alguma jogada */
	Move* play;	/*!< Ponteiro para uma variável do tipo Move que representa a jogada que originou a configuração do tabuleiro */
	int n_child; /*!< Inteiro que armazena o número de filhos que o nó da árvore tem */
	NodeTree ** child; /*!< Vetor de ponteiros para os filhos do nó */
}NodeTree;

/* Definição da estrutura da árvore de decisões */
/*! \struct Tree
		\brief Estrutura da árvore.

		Estrutura que armazena uma referência para a raíz da árvore de decisões
*/
typedef struct Tree{
	NodeTree* root; /*!< Ponteiro para uma variável do tipo ponteiro que representa a raiz da árvore */
}Tree;

/* Alocar espaço para a árvore */
/*! \fn Tree* AlocateTree(void)
        \brief Aloca espaço em memória para uma árvore

        \return Uma árvore inicializada e diferente de nulo
*/
Tree* AlocateTree(void);

/* Alocar espaço para o nó de uma árvore */
/*! \fn NodeTree* AlocateNodeTree(void)
        \brief Aloca espaço em memória para o nó de uma árvore

		\param n_child Inteiro contendo o número de filhos do nó
		\param board Ponteiro para o tipo Tboard que armazena a configuração do tabuleiro
		\param pay Ponteiro para o tipo Move que armazena a jogada que originou a configuração do tabuleiro

        \return Um nó inicializado e diferente de nulo
*/
NodeTree* AlocateNodeTree(int n_child, TBoard* board, Move* play);

#endif