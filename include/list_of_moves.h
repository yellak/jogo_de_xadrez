#ifndef _LIST_OF_MOVES_
#define _LIST_OF_MOVES_


/* Definição da estrutura que irá armazenar uma jogada possível a partir de um tabuleiro */
/*! \struct Move
		\brief Estrutura que irá caracterizar a jogada.

		Estrutura que armazena uma maneira de interpretar uma jogada.
*/
typedef struct Move{
	int origin[2]; /*!< Array que armazena as coordenadas de origem do movimento. */
	int destiny[2]; /*!< Array que armazena as coordenadas de destino do movimento. */
}Move;

typedef struct NodeList{
	Move play;
	struct NodeList *next;
}NodeList;

/* Definição da estrutura que irá armazenar as jogadas possíveis a partir de um tabuleiro. */
/*! \struct ListOfMoves
		\brief Estrutura representará todas as possíveis jogadas de um tabuleiro.

		Lista do tipo Move que é importante para a análise das jogadas.
*/
typedef struct ListOfMoves{
	int howmany; /*!< Inteiro que guarda quantas jogadas são possíveis de serem feitas. */
	NodeList *first;
	NodeList *current;
	NodeList *last;
}ListOfMoves;

/* Criar uma lista de movimentos vazia. */
/*! \fn ListOfMoves* CreateListOfMoves(void)
		\brief Cria uma lista de movimentos.
		
		\param void.
		\return Retorna uma lista de movimentos vazia.
*/
ListOfMoves* CreateListOfMoves(void);

/* Inserir um movimento na lista. */
/*! \fn int InsertMove(ListOfMoves* list, int originx, int originy, int destinyx, int destinyy)
		\brief Insere um movimento na lista.
		
		\param list Ponteiro para uma lista de movimentos.
		\param originx Inteiro com a coordenada x de origem.
		\param originy Inteiro com a coordenada y de origem.
		\param destinyx Inteiro com a coordenada x de destino.
		\param destinyy Inteiro com a coordenada y de destino.
		\return Retorna um inteiro indicando a falha ou sucesso da inserção.
*/
int InsertMove(ListOfMoves* list, int originx, int originy, int destinyx, int destinyy);


/*Libera memória dedicada a lista dos movimentos possíveis.*/
/*! \fn int DeleteListOfMoves(ListOfMoves* list)
		\brief Libera memória utilizada por uma lista.

		\param list uma lista de movimentos.
		\return Retorna um inteiro indicando a falha ou sucesso da operação.
*/
int DeleteListOfMoves(ListOfMoves* list);

/* Busca um movimento na lista de movimentos *de forma sequencial */
/*! \fn int SearchListOfMoves(ListOfMoves* list, int originx, int originy, int destinyx, int destinyy)
		\brief Busca um movimento na lista de movimentos

		\param list uma lista de movimentos.
		\param originx Inteiro com a coordenada x de origem.
		\param originy Inteiro com a coordenada y de origem.
		\param destinyx Inteiro com a coordenada x de destino.
		\param destinyy Inteiro com a coordenada y de destino.
		\return Retorna um inteiro indicando a falha ou sucesso da operação.
*/
int SearchListOfMoves(ListOfMoves* list, int originx, int originy, int destinyx, int destinyy);


#endif