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

/* Teste para verificar a validade da função que aloca um nó de uma árvore
   Procedimento:
   	-Criar Variável para o nó;
   	-Alocar um tabuleiro;
   	-Alocar uma jogada;
   	-Inicializar variável com número de filhos
   	-Chamar função que aloca o nó;
   	-Verificar se o nó retornado pela função é não nulo;
   	-Verificar se o componente "board" do nó é não nulo;
   	-Verificar se o componente "play" do nó é não nulo;
   	-Verificar se o componente "n_child" do nó é igual ao esperado;
   Resultados:
   	-Todas as variáveis devem estar alocadas corretamente
 */
TEST(Test_AlocateNodeTree, Verify_Alocation_Node){
	NodeTree * node;
	TBoard* board = AlocateBoard();
	Move* play = (Move*) malloc (sizeof(play));
	int n_child = 1;

	node = AlocateNodeTree(n_child, board, play);

	/* Testar a alocação */
	EXPECT_EQ(1, node != NULL);
	EXPECT_EQ(1, node->board != NULL);
	EXPECT_EQ(1, node->play != NULL);
	EXPECT_EQ(n_child, node->n_child);
} 

int main(int argc, char **argv){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
