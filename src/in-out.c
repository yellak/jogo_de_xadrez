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
				   Não pode ser nulo
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

/* Função: RemoveLastListPM
		Objetivo: Remover o último elemento da lista.

		Parametros:
			list - Ponteiro para a lista onde será removido o último movimento.
				   Não pode ser nulo

		Saída: Por parâmetro, retorna a lista sem o último elemento e um inteiro indicando o funcionamento (0 funciona, 1 não funciona)
*/
int RemoveLastListPM(ListPastMoves* list){
	/* Verificar entradas. */
	if(list == NULL)
		return 1;
	if(list->head == list->last)
		return 1;

	/* Achar elemento anterior. */
	ListNode *anterior, *aux;
	anterior = list->head;
	for(aux = list->head->next; aux != list->last; aux = aux->next)
		anterior = aux;

	/* Organizar ponteiros e liberar no. */
	free(list->last);
	anterior->next = NULL;
	list->last = anterior;

	return 0;
}

/* Função: FreeListPM
		Objetivo: Liberar a lista.

		Parametros:
			list - Ponteiro para a lista que será liberada.
				   Não pode ser nulo

		Saída: Inteiro indicando o funcionamento (0 funciona, 1 não funciona)
*/
int FreeListPM(ListPastMoves* list){
	/* Verificar entrada. */
	if(list == NULL)
		return 1;

	ListNode* aux = list->head;
	ListNode* temp;

	/* Liberar nós. */
	while(aux != NULL){
		temp = aux->next;
		free(aux);
		aux = temp;
	}

	/* Liberar lista. */
	free(list);

	return 0;
}
/* Função: SaveBoardFile
		Objetivo: Salvar a configuração de um tabuleiro em um arquivo

		Parametros:
			board    - Ponteiro para o tabuleiro que será salvo
					   Não pode ser nulo
			arq_name - Ponteiro para a string com o nome do arquivo
					   Não pode ser nula

		Saída: Inteiro indicando o funcionamento (0 funciona, 1 não funciona)
*/
int SaveBoardFile(TBoard* board, char* arq_name){
	return 1;
}