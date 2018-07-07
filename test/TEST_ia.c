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

/* Teste para verificar se a função de ordenar a árvore retorna o valor esperado quando a operação é bem sucedida
   Procedimento: 
   	-Inicia-se o tabuleiro vazio
   	-Insere-se um bispo branco e um peão preto no tabuleiro
   	-Inicializa-se a variável turno como turno do branco
   	-Cria-se a árvore com os movimentos
   Resultados:
   	-A função deve retornar 1 no caso de sucesso
 */

TEST(Test_SortTree, Verify_SortTree){
	TBoard board;
	StartEmptyBoard(&board);
	InsertPiece(&board, W_BISHOP, 4, 4);
	InsertPiece(&board, B_PAWN, 6, 6);
	int turn = WHITES_TURN;
	Tree* tree = CreateMovesTree(&board, turn);

	/* Testar a alocação */
	EXPECT_EQ(0, SortTree(tree, turn));
	EXPECT_EQ(3, tree->root->child[0]->board->Weight);
	FreeTreeNodes(tree->root);
	free(tree);
}

int main(int argc, char **argv){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

