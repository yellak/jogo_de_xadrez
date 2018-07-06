#include "gtest/gtest.h"
#include "../include/ia.h"

/* Teste para verificar a validade da função que cria a árvore a partir de um tabuleiro
   Procedimento:
   	-Criar Variável para a árvore;
   	-Inicializar um tabuleiro
   	-Chamar a função que cria a árvore
   Resultados:
   	-A árvore alocada deve ser diferente de nula
 */

TEST(Test_CreateMovesTree, Verify_Creation_Tree){
	Tree * tree;
	TBoard board;
	StartStandardBoard(&board);
	int turn = WHITES_TURN;
	tree = CreateMovesTree(&board, turn);

	/* Testar a alocação */
	EXPECT_EQ(1, tree != NULL);
	FreeTreeNodes(tree->root);
	free(tree);
}

/* Teste para verificar se a função retorna os valores certos no caso de entrada inválida 
   Procedimento:
   	-Criar Variável para a árvore;
   	-Inicializar um tabuleiro nulo (entrada inválida)
   	-Chamar a função que cria a árvore
   Resultados:
   	-A árvore alocada deve ser nula
 */

TEST(Test_CreateMovesTree, Verify_Alocation_Tree){
	Tree * tree;
	TBoard* board = NULL;
	int turn = WHITES_TURN;
	tree = CreateMovesTree(board, turn);

	/* Testar a alocação */
	EXPECT_EQ(NULL, tree);
}

/* Teste para verificar a validade da função que cria a árvore a partir de um tabuleiro
   Procedimento:
   	-Criar Variável para a árvore;
   	-Inicializar um tabuleiro
   	-Chamar a função que cria a árvore
   Resultados:
   	-A árvore alocada deve ser diferente de nula
   	-A raiz deve ter 20 filhos(número de possibilidades de movimentos)
   	-Os tabuleiros de todos os nós devem ter peso 0
 */

TEST(Test_CreateMovesTree, Verify_Root_Information){
	Tree * tree;
	TBoard board;
	StartStandardBoard(&board);
	int turn = WHITES_TURN;
	tree = CreateMovesTree(&board, turn);

	/* Testar a alocação */
	EXPECT_EQ(1, tree != NULL);

	/* Testar se a raiz tem 20 filhos */
	EXPECT_EQ(20, tree->root->n_child);

	/* Testar se o peso do tabuleiro e de todos os filhos desse nó tem peso 0 */
	/* pois não há chances de uma peça ser capturada nessa rodada */
	EXPECT_EQ(0, tree->root->board->Weight);

	for(int i = 0; i < tree->root->n_child; i++){
		EXPECT_EQ(0, tree->root->child[i]->board->Weight);
	}
	
	FreeTreeNodes(tree->root);
	free(tree);
}

/* Teste para 
   Procedimento:
   	-
   	-
   	-
   Resultados:
   	-
 */

TEST(Test_SortTree, Verify_Creation_Tree){
	TBoard board;
	StartEmptyBoard(&board);
	board.Board[4][4] = W_BISHOP;
	board.Board[5][5] = B_PAWN;
	int turn = WHITES_TURN;
	Tree* tree = CreateMovesTree(&board, turn);

	/* Testar a alocação */
	EXPECT_EQ(0, SortTree(tree, turn));
	FreeTreeNodes(tree->root);
	free(tree);
}

int main(int argc, char **argv){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}