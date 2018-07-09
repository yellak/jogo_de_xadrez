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
	NodeTree* newnode, *newnodechild;

	/* Extraindo a lista de movimentos para a cor certa do jogador atual */
	if(turn == WHITES_TURN){
	 	AllMoves = AnalyzePossibleMovementsWhite(board);
	}
	else if(turn == BLACKS_TURN){
		AllMoves = AnalyzePossibleMovementsBlack(board);
	}

	/* Inicializando o movimento da raiz como zero */
	Move play;
	play.origin[0] = 0;
	play.origin[1] = 0;
	play.destiny[0] = 0;
	play.destiny[1] = 0;

	/* Alocando a raíz da árvore */
	Tree* tree = AlocateTree();
	tree->root = AlocateNodeTree(AllMoves->howmany, board, &play);
	
	/* Vetor de tabuleiros auxiliares */
	TBoard** boardaux = (TBoard**) malloc(AllMoves->howmany*sizeof(TBoard*)); 
	NodeList* currentnode = AllMoves->first;

	/* Loop para cada um dos filhos da raiz contendo as jogadas possíveis a partir do tabuleiro inicial */
	for(int i = 0 ; i < tree->root->n_child; i++, currentnode = currentnode->next){

		/* Tabuleiro auxiliar para armazenar a nova jogada */
		boardaux[i] = AlocateBoard();
		copy_boards(boardaux[i], board);

		/* Movimenta-se a peça no tabuleiro auxiliar de acordo com a jogada da lista de jogadas caso ele seja válido */
		if(VerifyValidMovement(boardaux[i], currentnode->play.origin[0], currentnode->play.origin[1], currentnode->play.destiny[0], currentnode->play.destiny[1])){
			MovePiece(boardaux[i], currentnode->play.origin[0], currentnode->play.origin[1], currentnode->play.destiny[0], currentnode->play.destiny[1]);
		}
		
		/* Caso o seu rei entre em xeque, se torna prioridade sair do cheque */
		else{
			if(turn == WHITES_TURN){
				boardaux[i]->Weight = -999;
			}
			else{
				boardaux[i]->Weight = 999;
			}
		}


		/* Extraindo a lista de movimentos para a jogada seguinte */
		/* Por isso, caso a primeira jogada seja do branco a seguinte será do preto e vice-versa */
		/* Verifica-se também se houve cheque depois do movimento */
		if(turn == WHITES_TURN){
			AllMovesChild = AnalyzePossibleMovementsBlack(boardaux[i]);	
			boardaux[i] = VerifyCheck(boardaux[i], BLACK);
		} 
		else if(turn == BLACKS_TURN){
			AllMovesChild = AnalyzePossibleMovementsWhite(boardaux[i]);
			boardaux[i] = VerifyCheck(boardaux[i], WHITE);		
		} 
		
		/* Alocando o nó da nova jogada */

		/* Caso não haja uma próxima jogada depois do nó atual, apenas copiamos o seu tabuleiro  */
		/* e o seu movimento para o seu filho para facilitar na hora de ordenar a árvore        */
		if(AllMovesChild->howmany == 0){
			newnode = AlocateNodeTree(1, boardaux[i], &currentnode->play);
			AddChildNode(tree->root, newnode, i);	
			newnodechild = AlocateNodeTree(0, newnode->board, newnode->play);
			AddChildNode(newnode, newnodechild, 0);			
		}

		/* Caso exista uma próxima jogada, apenas aloca-se o espaço para ela */
		else{
			newnode = AlocateNodeTree(AllMovesChild->howmany, boardaux[i], &currentnode->play);
			AddChildNode(tree->root, newnode, i);
		}


		NodeList* currentnodechild = AllMovesChild->first;
		TBoard** boardauxchild = (TBoard**) malloc(AllMovesChild->howmany*sizeof(TBoard*)); 

		/* Loop para percorrer cada um dos filhos dos filhos para inserir as jogadas seguintes */
		for(int j = 0; j < AllMovesChild->howmany; j++, currentnodechild = currentnodechild->next){

			/* Outro tabuleiro auxiliar para criar os filhos do newnode */
			boardauxchild[j] = AlocateBoard();
			copy_boards(boardauxchild[j], boardaux[i]);

			/* Movimenta-se a peça no tabuleiro de acordo com a configuração do tabuleiro de newnode */
			/* Apenas no caso do movimento ser válido */
			if(VerifyValidMovement(boardauxchild[j], currentnodechild->play.origin[0], currentnodechild->play.origin[1], currentnodechild->play.destiny[0], currentnodechild->play.destiny[1])){
				MovePiece(boardauxchild[j], currentnodechild->play.origin[0], currentnodechild->play.origin[1], currentnodechild->play.destiny[0], currentnodechild->play.destiny[1]);
			}


			/* Verifica se depois do movimento, o rei continua em cheque */
			if(turn == WHITES_TURN){
				boardauxchild[j] = VerifyCheck(boardauxchild[j], BLACK);
			} 
			else if(turn == BLACKS_TURN){
				boardauxchild[j] = VerifyCheck(boardauxchild[j], WHITE);		
			}

			/* Alocando o nó do filho de newnode */
			NodeTree* newnodechild = AlocateNodeTree(1, boardauxchild[j], &currentnodechild->play);
			AddChildNode(newnode, newnodechild, j);			
		}
	}

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

		/* Assertivas de entrada */
	if(tree == NULL || turn > 1 || turn < 0){
		return 1;
	}

	int n_child = tree->root->n_child;
	int i, j, k, check1, check2, check3, check4	;

	/* Caso seja turno dos brancos, ordena-se o primeiro sub-nível para que o primeiro filho seja a 
		melhor jogada do branco e o segundo sub-nível a melhor jogada do preto */
	if(turn == WHITES_TURN){

		/* Loop para ordenar o segundo sub-nível de cada nó do primeiro sub-nível*/
		for (k = 0; k < n_child; k++){
			int n = tree->root->child[k]->n_child;

			for (i = 0; i < n; i++){     
		   		for (j = 0; j < n-i-1; j++){
		   			check1 = tree->root->child[k]->child[j]->board->BlackCheck;
		   			check2 = tree->root->child[k]->child[j + 1]->board->BlackCheck;
		   			check3 = tree->root->child[k]->child[j]->board->WhiteCheck;
		   			check4 = tree->root->child[k]->child[j + 1]->board->WhiteCheck;


		   			/* O fato de ter ou não xeque é levado em consideração para ordenar a árvore */
		      		if(tree->root->child[k]->child[j]->board->Weight + CHECK_WEIGHT*check1 - CHECK_WEIGHT*check3 > tree->root->child[k]->child[j+1]->board->Weight + CHECK_WEIGHT*check2 - CHECK_WEIGHT*check4){
		      			NodeTree* nodeaux = tree->root->child[k]->child[j];
		      			tree->root->child[k]->child[j] = tree->root->child[k]->child[j + 1];
		      			tree->root->child[k]->child[j + 1] = nodeaux;
		      		}
		    	}
		  	}
		}

		/* Loop para ordenar o primeiro sub-nível em função do primeiro filho ordenado anteriormente*/
		for (i = 0; i < n_child; i++){     
		   	for (j = 0; j < n_child-i-1; j++){
		   		check1 = tree->root->child[j]->child[0]->board->BlackCheck;
		   		check2 = tree->root->child[j + 1]->child[0]->board->BlackCheck;
		   		check3 = tree->root->child[j]->child[0]->board->WhiteCheck;
		   		check4 = tree->root->child[j + 1]->child[0]->board->WhiteCheck;

		      	if(tree->root->child[j]->child[0]->board->Weight + CHECK_WEIGHT*check1 - CHECK_WEIGHT*check3 < tree->root->child[j + 1]->child[0]->board->Weight + CHECK_WEIGHT*check2 - CHECK_WEIGHT*check4){
		      		NodeTree* nodeaux = tree->root->child[j];
		      		tree->root->child[j] = tree->root->child[j + 1];
		      		tree->root->child[j + 1] = nodeaux;
		      	}
		    }
		}
	}

	/* Caso seja turno dos pretos, ordena-se o primeiro sub-nível para que o primeiro filho seja a 
		melhor jogada do preto e o segundo sub-nível a melhor jogada do branco */
	else if(turn == BLACKS_TURN){

		/* Loop para ordenar o segundo sub-nível de cada nó do primeiro sub-nível*/
		for (k = 0; k < n_child; k++){
			int n = tree->root->child[k]->n_child;

			for (i = 0; i < n; i++){     
		   		for (j = 0; j < n-i-1; j++){
		   			check1 = tree->root->child[k]->child[j]->board->WhiteCheck;
		   			check2 = tree->root->child[k]->child[j + 1]->board->WhiteCheck;
		   			check3 = tree->root->child[k]->child[j]->board->BlackCheck;
		   			check4 = tree->root->child[k]->child[j + 1]->board->BlackCheck;	

		   			/* O fato de ter ou não xeque é levado em consideração para ordenar a árvore */
		      		if(tree->root->child[k]->child[j]->board->Weight - CHECK_WEIGHT*check1 + CHECK_WEIGHT*check3 < tree->root->child[k]->child[j+1]->board->Weight - CHECK_WEIGHT*check2 + CHECK_WEIGHT*check4){
		      			NodeTree* nodeaux = tree->root->child[k]->child[j];
		      			tree->root->child[k]->child[j] = tree->root->child[k]->child[j + 1];
		      			tree->root->child[k]->child[j + 1] = nodeaux;
		      		}
		    	}
		  	}
		}

		/* Loop para ordenar o primeiro sub-nível em função do primeiro filho ordenado anteriormente*/
		for (i = 0; i < n_child; i++){     
		   	for (j = 0; j < n_child-i-1; j++){
		   		check1 = tree->root->child[j]->child[0]->board->WhiteCheck;
		   		check2 = tree->root->child[j + 1]->child[0]->board->WhiteCheck;
		   		check3 = tree->root->child[j]->child[0]->board->BlackCheck;
		   		check4 = tree->root->child[j + 1]->child[0]->board->BlackCheck;

		      	if(tree->root->child[j]->child[0]->board->Weight - CHECK_WEIGHT*check1 + CHECK_WEIGHT*check3 > tree->root->child[j + 1]->child[0]->board->Weight - CHECK_WEIGHT*check2 + CHECK_WEIGHT*check4){
		      		NodeTree* nodeaux = tree->root->child[j];
		      		tree->root->child[j] = tree->root->child[j + 1];
		      		tree->root->child[j + 1] = nodeaux;
		      	}
		    }
		}	
	}
	return 0;
}

/* Função: Best_Plays
		Objetivo: Extrair uma lista de movimentos dos nós de uma árvore

		Parametros:
			tree  	 - Ponteiro para a árvore que se deseja extrair a lista de movimentos
					   Não deve ser nula
			n_child  - Inteiro contendo o número de filhos que a raiz da árvore tem

		Saída: Retorna uma lista com todas as jogadas de uma árvore
*/
ListOfMoves* Best_Plays(Tree* tree, int n_child) {

	if(tree == NULL){
		return NULL;
	}

	ListOfMoves* Lista = CreateListOfMoves();

	/* Insere todas as jogadas possíveis da árvore na lista de movimentos */
	for(int j=0; j< n_child; j++){
		InsertMove(Lista,tree->root->child[j]->play->origin[0],tree->root->child[j]->play->origin[1],tree->root->child[j]->play->destiny[0], tree->root->child[j]->play->destiny[1]);
	}
	
	return Lista;
}
