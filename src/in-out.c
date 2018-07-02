#include "../include/in-out.h"

/* Função: StartListPM
		Objetivo: Iniciar uma lista de movimentos passados.

		Parametros:
			board - Não há parâmetros de entrada

		Saída: Essa função retorna uma lista de movimentos passados vazia com a cabeça.
*/
ListPastMoves* StartListPM(void){
	/* Alocar espaço para a lista. */
	ListPastMoves *list = (ListPastMoves*) malloc(sizeof(ListPastMoves));

	/* Alocar cabeça. */
	list->head = (ListNode*) malloc(sizeof(ListNode));

	/* Definir movimento da cabeca como '\\'. */
	list->head->move[0] = '\\';
	list->head->move[1] = '\0';

	/* Organizar ponterios. */
	list->head->next = NULL;
	list->last = list->head;

	return list;
}