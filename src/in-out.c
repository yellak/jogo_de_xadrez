#include "../include/in-out.h"

/* Função: StartListPM
		Objetivo: Iniciar uma lista de movimentos passados.

		Parametros:
			Não há parâmetros de entrada.

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

/* Função: AddListPM
		Objetivo: Adicionar um novo movimento na lista.

		Parametros:
			list - Ponteiro para a lista onde será adiiconado o movimento.
				   Não pode se nulo
			move - String com o movimento na notação do xadrez.
				   Deve ser não-nulo e ter seu sétimo elemento com '\0'

		Saída: Por parâmetro, retorna a lista com o novo elemento e um inteiro indicando o funcionamento (0 funciona, 1 não funciona)
*/
int AddListPM(ListPastMoves* list, char move[]){
	/* Verificar entradas. */
	if(list == NULL || move == NULL)
		return 1;

	if(move[6] != '\0')
		move[6] = '\0';

	/* Alocar nó e copiar string. */
	ListNode* Novo = (ListNode*) malloc(sizeof(ListNode));
	strcpy(Novo->move, move);

	/* Organizar ponteiros. */
	list->last->next = Novo;
	list->last = Novo;
	list->last->next = NULL;

	return 0;
}