#ifndef _ARV_DECISOES_
#define _ARV_DECISOES_

#include "../include/tabuleiro.h"

/* Definição da estrutura da árvore de decisões */
/*! \struct Tree
		\brief Estrutura da árvore.

		Estrutura que armazena uma referência para a raíz da árvore de decisões
*/
typedef struct Tree{
	NodeTree* root; /*!< Ponteiro para uma variável do tipo ponteiro que representa a raiz da árvore */
}Tree;

/* Definição da estrutura de um nó da árvore de decisões */
/*! \struct NodeTree
		\brief Estrutura de um nó da árvore.

		Estrutura que armazena os componentes básicos de um nó da árvore de decisões
*/
typedef struct NodeTree{
	TBoard* board;	/*!< Ponteiro para uma variável do tipo Tboard que representa a organização do tabuleiro depois de alguma jogada */
	Move* play;	/*!< Ponteiro para uma variável do tipo Move que representa a jogada que originou a configuração do tabuleiro */
	int n_child; /*!< Inteiro que armazena o número de filhos que o nó da árvore tem */
	NoArv ** child; /*!< Vetor de ponteiros para os filhos do nó */
}NodeTree;


#endif