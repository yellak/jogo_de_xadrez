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
            		- Não pode ter um valor menor que 0 pois gera problemas na alocação
            board - Tabuleiro atual 
            play - Movimento que originou a configuração atual do tabuleiro

        Retorno:
            A função retorna um nó de uma árvore alocado e  diferente de nulo
*/
NodeTree* AlocateNodeTree(int n_child, TBoard* board, Move* play){

	/* Uma árvore não pode ter menos que um filho */
	if(n_child < 0){
		return NULL;
	}

	NodeTree* node = (NodeTree*)malloc(sizeof(NodeTree));

	/* Alocação das componentes de um nó de árvore */
	node->board = board;
	node->play = play;
	node->n_child = n_child;

	/* Alocação de "n_child" filhos para o nó */

	if(n_child > 0){
		node->child = (NodeTree**)malloc(n_child*sizeof(NodeTree*));
		for(int i = 0; i < n_child; i++){
			node->child[i] = NULL;
		}
	}
	return node;	

}

/*
  Função: Inserir um nó como o i-ésimo filho de outro nó
        Objetivo:
            Inserir um nó como filho de outro

        Parâmetros:
            father - Nó que receberá o novo filho
            	   - Não pode ser nulo
            child - Nó que se tornará filho de "father"
            position - Posição do filho no vetor de filhos do pai
            		 - Não pode ser maior que o número de filhos de pai

        Retorno:
            1 caso a inserção seja um sucesso
            0 caso seja um fracasso
*/
int AddChildNode(NodeTree* father, NodeTree* child, int position){

	/* Assertiva para assegurar a validade de "father" */
	if(father == NULL){
		return 0;
	}

	/* Assertiva para assegurar que não seja possível acessar um filho maior que o número de filhos */
	if(position > father->n_child - 1){
		return 0;
	}
	
	father->child[position] = child;
	return 1;
}

/*
  Função: Liberar um nó e todos os seus filhos
        Objetivo:
            Liberar um nó e todos os seus filhos

        Parâmetros:
            node - Nó que será liberado
            
        Retorno:
            Ponteiro nulo do tipo NodeTree
*/
NodeTree* FreeTreeNodes(NodeTree* node){
	
	/* Caso o nó enviado seja nulo, retorna-se nulo */
	if(node == NULL){
		return NULL;
	}

	/* Libera-se cada um dos filhos do nó */
	for(int i = 0; i < node->n_child; i++){
		node->child[i] = FreeTreeNodes(node->child[i]);
	}

	if(node->n_child != 0){
		free(node->child);
	}
	free(node);
	return NULL;
}