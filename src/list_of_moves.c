#include "../include/list_of_moves.h"
#include <stdio.h>
#include <stdlib.h>


/*
  Função: CreateListOfMoves
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
/*
	Função: InsertMove
		Objetivo:
			Alocar um nó e inserir um movimento na lista.
		Parametros:
			list - Ponteiro para uma lista de movimentos.
				   Não deve ser nulo.
			play - Ponteiro para um movimento.
				   Não deve ser nulo.
		Retorno:
			Um inteiro indicando a falha ou sucesso da inserção.

*/

int InsertMove(ListOfMoves* list, Move* play){

	if(list == NULL || play == NULL){
		return -1;
	}
	list->first = (NodeList*)malloc(sizeof(NodeList));
	list->first->play = play;
	list->first->next = NULL;
	list->last = list->first;
	list->howmany ++;
	return 0;
}

/* Função: DeleteListOfMoves
		Objetivo: Liberar toda a memória da lista de movimentos.

		Parametros:
			list - Ponteiro para a estrutura da lista.
					Não deve ser nulo

		Saída: Retorna um inteiro indicando a falha ou sucesso da operação.
*/

int DeleteListOfMoves(ListOfMoves* list){
	NodeList* temp;
	if(list == NULL){
		return -1;
	}
	list->current = list->first;
	while(list->current != NULL){
		temp = list->current->next;
		free(list->current);
		list->current = temp;
	}
	free(list);

	return 0;
}
