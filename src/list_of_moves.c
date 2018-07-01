#include "../include/list_of_moves.h"
#include <stdio.h>
#include <stdlib.h>


/*
  Função: Criar uma lista de movimentos vazia
        Objetivo:
            Alocar espaço na memória para uma lista de movimentos.

        Parâmetros:
            A função não possui parâmetros.

        Retorno:
        	A  função retorna uma lista de movimentos vazia.
*/

ListOfMoves* CreateListOfMoves(void){
	ListOfMoves* List = (ListOfMoves*)malloc(sizeof(ListOfMoves));

	List->howmany = 0;
	List->first = NULL;
	List->current = NULL;
	List->last = NULL;
	
	return List;
}

int InsertMove(ListOfMoves* list, Move* play){

	if(list == NULL || play == NULL){
		return -1;
	}
	else{
		list->first = (NodeList*)malloc(sizeof(NodeList));
		list->first->play = play;
		list->first->next = NULL;
		list->last = list->first;
	}
	return 0;
}
