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
            A função não possui parâmetros.

        Retorno:
            A função retorna um nó de uma árvore alocado e  diferente de nulo
*/
NodeTree* AlocateNodeTree(void){
	return NULL;
}