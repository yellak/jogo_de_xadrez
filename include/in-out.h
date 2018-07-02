#ifndef IN_OUT_H_
#define IN_OUT_H_


/* Definição do nó da lista que armazena os movimentos passados. */
/*! \struct ListNode
		\brief Estrutura do nó da lista que armazena as jogadas passadas.

		Essa estrutura armazena os elemnetos ncessários para recuperar uma jogada feita anteriormente.
*/
typedef struct node_list{
	char move[7]; /*!< String com a jogada feita na notação de xadrez. */
	struct node_list *next; /*!< Ponteiro para o próximo elemento da lista. */
}ListNode;

/* Definição da lista que armazena os movimentos passados. */
/*! \struct ListPastMoves
		\brief Estrutura da lista que armazena as jogadas passadas.

		Essa estrutura serva para recuperação de jogadas passadas e salvamentos de jogos em PGN.
*/
typedef struct list_past_move{
	ListNode *head; /*!< Ponteiro para a cabeça da lista. */
	ListNode *last; /*!< Ponteiro para o último elemento da lista. */
}ListPastMoves;


#endif