#include "../include/arv_decisoes.h"
#include <stdio.h>
#include <stdlib.h>

/*
  Função: Alocar nova árvore
        Objetivo:
            Alocar dinâmicamente a árvore

        Parâmetros:
            A função não possui parâmetros.

        Retorno:
            A função retorna uma árvore alocada diferente de nulo
*/
Tree* AlocateTree(void){
	Tree* tree = (Tree*)malloc(sizeof(Tree));
	return tree;
}


/*
  Função: Alocar um nó de uma árvore
        Objetivo:
            Alocar dinâmicamente um nó de uma árvore

        Parâmetros:
            n_child - número de filhos que o nó terá

        Retorno:
            A função retorna um nó de uma árvore alocado e  diferente de nulo
*/
NodeTree* AlocateNodeTree(int n_child){
	NodeTree* node = (NodeTree*)malloc(sizeof(NodeTree));

	/* Alocação das componentes de um nó de árvore */
	node->board = AlocateBoard();
	node->play = (Move*)malloc(sizeof(Move));
	node->n_child = n_child;

	/* Alocação de "n_child" filhos para o nó */
	node->child = (NodeTree**)malloc(n_child*sizeof(NodeTree*));
	return node;	

}