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
            board - Tabuleiro atual 
            play - Movimento que originou a configuração atual do tabuleiro

        Retorno:
            A função retorna um nó de uma árvore alocado e  diferente de nulo
*/
NodeTree* AlocateNodeTree(int n_child, TBoard* board, Move* play){
	NodeTree* node = (NodeTree*)malloc(sizeof(NodeTree));

	/* Alocação das componentes de um nó de árvore */
	node->board = board;
	node->play = play;
	node->n_child = n_child;

	/* Alocação de "n_child" filhos para o nó */
	node->child = (NodeTree**)malloc(n_child*sizeof(NodeTree*));
	return node;	

}

/*
  Função: Inserir um nó como o i-ésimo filho de outro nó
        Objetivo:
            Inserir um nó como filho de outro

        Parâmetros:
            father - Nó que receberá o novo filho
            child - Nó que se tornará filho de "father"
            position - Posição do filho no vetor de filhos do pai

        Retorno:
            1 caso a inserção seja um sucesso e 0 caso seja um fracasso
*/
int AddChildNode(NodeTree* father, NodeTree* child, int position){
	return 0;
}