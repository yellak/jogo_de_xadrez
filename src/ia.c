#include "../include/ia.h"

/* Função: Create_BestTree
		Objetivo: Criar uma árvore de decisões para ser base da IA

		Parametros:
			board - Ponteiro para a estrutura do tabuleiro.
					Não deve ser nulo
			turn  - Inteiro contendo a informação de quem é jogada(Black = 0, White = 1)
					Deve estar entre 0 e 1

		Saída: Essa função retorna um elemento do tipo árvore, contendo as jogadas possíveis para 
		uma configuração específica do tabuleiro
*/
Tree* Create_BestTree(TBoard *board, int turn){

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

		for(int j = 0; j < AllMovesChild->howmany; j++, currentnodechild = currentnodechild->next){

			/* Outro tabuleiro auxiliar para criar os filhos do newnode */
			TBoard boardauxchild = boardaux;

			/* Movimenta-se a peça no tabuleiro de arcordo com a configuração do tabuleiro de newnode */
			MovePiece(&boardauxchild, currentnodechild->play.origin[0], currentnodechild->play.origin[1], currentnodechild->play.destiny[0], currentnodechild->play.destiny[1]);
			
			/* Alocando o nó do filho de newnode */
			NodeTree* newnodechild = AlocateNodeTree(1, &boardauxchild, &currentnode->play);
			AddChildNode(newnode, newnodechild, j);			
		}
	}



	return tree;
}
//função que ordena jogadas, baseadas no peso do tabuleiro
int Sort_Tree(Tree* tree) {}

//função para extrair melhor jogada , retorna a jogad

//função para retornar as n melhores jogadas