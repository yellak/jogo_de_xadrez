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

int InsertMove(ListOfMoves* list, int originx, int originy, int destinyx, int destinyy){

	if(list == NULL){
		return -1;
	}
	NodeList* novo = (NodeList*)malloc(sizeof(NodeList));
	novo->play.origin[0] = originx;
	novo->play.origin[1] = originy;
	novo->play.destiny[0] = destinyx;
	novo->play.destiny[1] = destinyy;
	novo->next = NULL;
	if(list->first == NULL){
		list->first = novo;
		list->last = list->first;
	}
	else{
		list->last->next = novo;
		list->last = novo;
	}
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

/* Função: SearchListOfMoves
		Objetivo: Buscar um movimento na lista de movimentos

		Parametros:
			list - Ponteiro para a estrutura da lista.
				   Não deve ser nulo
			move - Ponteiro para o tipo movimento a ser procurado
				   Não deve ser nulo

		Saída: Retorna um inteiro indicando a falha ou sucesso da operação.
*/
int SearchListOfMoves(ListOfMoves* list, int originx, int originy, int destinyx, int destinyy){

	if(list == NULL){
		return 1;
	}
	NodeList* aux = list->first;

	/* Percorre a lista até o último nó */
	while(aux != NULL){
		if(aux->play.origin[0] == originx && aux->play.destiny[0] == destinyx){
			if(aux->play.origin[1] == originy && aux->play.destiny[1] == destinyy){
				/* Caso encontre o movimento na lista, retorna 0 */
				return 0;
			}
		}
		aux = aux->next;
	}

	return 1;
}