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

TEST(Test_AlocateTree, Verify_Alocation_Tree){
	Tree * tree;
	TBoard board;
	StartStandardBoard(&board);
	int turn = WHITES_TURN;
	tree = Create_BestTree(&board, turn);

	/* Testar a alocação */
	EXPECT_EQ(1, tree != NULL);
	free(tree);
}

int main(int argc, char **argv){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}