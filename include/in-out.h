#ifndef IN_OUT_H_
#define IN_OUT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/tabuleiro.h"

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

/* Alocar espaço para lista de movimentos passados */
/*! \fn ListPastMoves* StartListPM(void)
        \brief Aloca o espaço para a lista de movimentos passados e sua cabeça.

        \return Lista com espaço e sua cabeca alocados e o elemento seguinte da cabeça como nulo. 
*/
ListPastMoves* StartListPM(void);

/* Adicionar movimento na lista. */
/*! \fn int AddListPM(ListPastMoves* list, char move[])
		\brief Adiciona um movimento na lista de movimentos passados.

		\param list Ponteiro para a lista.
		\param move String com o movimeto na notação de xadrez.
		\return Por parâmetro, retorna a lista com o novo elemento e um inteiro indicando o funcionamento da função (0, caso funcione e 1 caso contrário).
*/
int AddListPM(ListPastMoves* list, char move[]);

/* Remover último movimento na lista. */
/*! \fn int RemoveLastListPM(ListPastMoves* list)
		\brief Remove o último elemento da lista.

		\param list Ponteiro para a lista.
		\return Por parâmetro, retorna a lista sem o último elemento e um inteiro indicando o funcionamento da função (0, caso funcione e 1 caso contrário).
*/
int RemoveLastListPM(ListPastMoves* list);

/* Liberar lista. */
/*! \fn int FreeListPM(ListPastMoves* list)
		\brief Libera a lista, desalocando seus elementos.

		\param list Ponteiro para a lista.
		\return Inteiro indicando o funcionamento da função (0, caso funcione e 1 caso contrário).
*/
int FreeListPM(ListPastMoves* list);

/* Salvar arquivo do tabuleiro. */
/*! \fn int SaveBoardFile(Tboard* board, char* arq_name)
		\brief Salva o tabuleiro em um arquivo

		\param board Tabuleiro que será salvo em um arquivo
		\param file_name Nome do arquivo
		\return Inteiro indicando o funcionamento da função (0, caso funcione e 1 caso contrário).
*/
int SaveBoardFile(TBoard* board, char* file_name);

/* Recuperar um tabuleiro a partir de um arquivo. */
/*! \fn int RecoverBoardFromFile(Tboard* board, char* arq_name)
		\brief Cria um tabuleiro a partir de um arquivo

		\param board Tabuleiro que será recuperado
		\param file_name Nome do arquivo contendo o tabuleiro salvo
		\return Inteiro indicando o funcionamento da função (0, caso funcione e 1 caso contrário).
*/
int RecoverBoardFromFile(TBoard* board, char* file_name);

/* Salvar arquivo PGN. */
/*! \fn int SavePGNFile(ListPastMoves* listmoves, char* file_name)
		\brief Salva o tabuleiro em um arquivo

		\param listmoves Ponteiro para uma lista de movimentos
		\param file_name Nome do arquivo
		\return Inteiro indicando o funcionamento da função (0, caso funcione e 1 caso contrário).
*/
int SavePGNFile(ListPastMoves* listmoves, char* file_name);

/* Recuperar uma lista de movimentos a partir de um arquivo. */
/*! \fn int RecoverMoveListFromFile(ListPastMoves* listmoves, char* file_name)
		\brief Recupera a lista de movimentos armazenada em um arquivo

		\param listmoves Lista de movimentos que será recuperada
		\param file_name Nome do arquivo contendo o tabuleiro salvo
		\return Inteiro indicando o funcionamento da função (0, caso funcione e 1 caso contrário).
*/
int RecoverMoveListFromFile(ListPastMoves* listmoves, char* file_name);
#endif