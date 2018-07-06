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

TEST(Test_CreateTree, Verify_Creation_Tree){
	Tree * tree;
	TBoard board;
	StartStandardBoard(&board);
	int turn = WHITES_TURN;
	tree = Create_BestTree(&board, turn);

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

TEST(Test_CreateTree, Verify_Alocation_Tree){
	Tree * tree;
	TBoard* board = NULL;
	int turn = WHITES_TURN;
	tree = Create_BestTree(board, turn);

	/* Testar a alocação */
	EXPECT_EQ(NULL, tree);
}

int main(int argc, char **argv){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}