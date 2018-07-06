#include "../include/ia.h"

/* Função: Create_MovesTree
		Objetivo: Criar uma árvore de decisões para ser base da IA

		Parametros:
			board - Ponteiro para a estrutura do tabuleiro.
					Não deve ser nulo
			turn  - Inteiro contendo a informação de quem é jogada(Black = 0, White = 1)
					Deve estar entre 0 e 1

		Saída: Essa função retorna um elemento do tipo árvore, contendo as jogadas possíveis para 
		uma configuração específica do tabuleiro
*/
Tree* CreateMovesTree(TBoard *board, int turn){

	/* Assertivas de entrada */
	if(board == NULL || turn > 1 || turn < 0){
		return NULL;
	}

	ListOfMoves* AllMoves, *AllMovesChild;

	/* Extraindo a lista de movimentos para a cor certa do jogador atual */
	if(turn == WHITES_TURN) AllMoves = AnalyzePossibleMovementsWhite(board);
	else if(turn == BLACKS_TURN) AllMoves = AnalyzePossibleMovementsBlack(board);
	
	/* Inicializando o movimento da raiz */
	Move play;
	play.origin[0] = 0;
	play.origin[1] = 0;
	play.destiny[0] = 0;
	play.destiny[1] = 0;

	/* Alocando a raíz da árvore */
	Tree* tree = AlocateTree();
	tree->root = AlocateNodeTree(AllMoves->howmany, board, &play);
	

	NodeList* currentnode = AllMoves->first;

	for(int I = 0; I < 8; I++){
		for(int J = 0; J < 8; J++){
			printf("%c ", board->Board[I][J]);
		}
		printf("\n");
	}
	printf("\n");

	for(int i = 0 ; i < tree->root->n_child; i++, currentnode = currentnode->next){

		/* Tabuleiro auxiliar para armazenar a nova jogada */
		TBoard boardaux = *board;

		/* Movimenta-se a peça no tabuleiro auxiliar de acordo com a jogada da lista de jogadas*/
		MovePiece(&boardaux, currentnode->play.origin[0], currentnode->play.origin[1], currentnode->play.destiny[0], currentnode->play.destiny[1]);

		/* Extraindo a lista de movimentos para a jogada seguinte */
		/* Por isso, caso a primeira jogada seja do branco a seguinte será do preto e vice-versa */
		if(turn == WHITES_TURN) AllMovesChild = AnalyzePossibleMovementsBlack(&boardaux);
		else if(turn == BLACKS_TURN) AllMovesChild = AnalyzePossibleMovementsWhite(&boardaux);	
		
		/* Alocando o nó da nova jogada */
		NodeTree* newnode = AlocateNodeTree(AllMovesChild->howmany, &boardaux, &currentnode->play);
		AddChildNode(tree->root, newnode, i);

		NodeList* currentnodechild = AllMovesChild->first;

		for(int I = 0; I < 8; I++){
			for(int J = 0; J < 8; J++){
				printf("%c ", boardaux.Board[I][J]);
			}
			printf("\n");
		}
		printf("\n");
		
		for(int j = 0; j < AllMovesChild->howmany; j++, currentnodechild = currentnodechild->next){

			/* Outro tabuleiro auxiliar para criar os filhos do newnode */
			TBoard boardauxchild = boardaux;

			/* Movimenta-se a peça no tabuleiro de arcordo com a configuração do tabuleiro de newnode */
			MovePiece(&boardauxchild, currentnodechild->play.origin[0], currentnodechild->play.origin[1], currentnodechild->play.destiny[0], currentnodechild->play.destiny[1]);
			
			/* Alocando o nó do filho de newnode */
			NodeTree* newnodechild = AlocateNodeTree(1, &boardauxchild, &currentnode->play);
			AddChildNode(newnode, newnodechild, j);			
		}

		DeleteListOfMoves(AllMovesChild);
	}

	DeleteListOfMoves(AllMoves);

	return tree;
}

/* Função: Sort_Tree
		Objetivo: Ordenar a árvore de acordo com a melhor jogada de uma cor e seus filhos de acordo com a melhor jogada da outra cor 

		Parametros:
			board - Ponteiro para a árvore que se deseja ordenar
					Não deve ser nula
			turn  - Inteiro contendo a informação de quem é jogada(Black = 0, White = 1)
					Deve estar entre 0 e 1

		Saída: Essa função retorna um inteiro indicando sucesso(0) ou fracasso(1) da operação de ordenar
*/
int SortTree(Tree* tree, int turn){
	return 1;
}

//função para extrair melhor jogada , retorna a jogad

//função para retornar as n melhores jogadas