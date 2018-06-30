#include "gtest/gtest.h"
#include "../include/arv_decisoes.h"

/* Teste para verificar a validade da função que aloca uma árvore
   Procedimento:
   	-Criar Variável para a árvore;
   	-Chamar função que aloca a árvore;
   	-Verificar se a árvore retornada pela função é não nula;
   Resultados:
   	-A árvore alocada deve ser diferente de nula
 */

TEST(Test_AlocateTree, Verify_Alocation_Tree){
	Tree * tree;
	tree = AlocateTree();

	/* Testar a alocação */
	EXPECT_EQ(1, tree != NULL);
} 


TEST(Test_AlocateNodeTree, Verify_Alocation_Node){
	NodeTree * node;
	node = AlocateNodeTree(4);

	/* Testar a alocação */
	EXPECT_EQ(1, node != NULL);
} 

int main(int argc, char **argv){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
