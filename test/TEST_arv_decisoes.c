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
	free(tree);
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
	Move play;
	int n_child = 1;

	node = AlocateNodeTree(n_child, board, &play);

	/* Testar a alocação */
	EXPECT_EQ(1, node != NULL);
	EXPECT_EQ(1, node->board != NULL);
	EXPECT_EQ(1, node->play != NULL);
	EXPECT_EQ(n_child, node->n_child);
	FreeTreeNodes(node);
	free(board);
} 

/* Teste para verificar se a inserção de um filho foi bem sucedida
   Procedimento:
   	-Criar Variável para os nós;
   	-Alocar dois tabuleiros;
   	-Alocar duas jogadas;
   	-Inicializar variável com número de filhos
   	-Chamar função que aloca o nó para o pai e para o filho;
   	-Verificar se a adição foi bem sucedida;
   	-Verificar se o "child" é o i-ésimo filho de "father" ;
   Resultados:
   	-O nó "child" deve ser filho de "father"
 */
TEST(Test_AddChildNode, Verify_Insertion_Sucess){
	NodeTree * father, *child;
	TBoard *boardfather = AlocateBoard();
	TBoard *boardchild = AlocateBoard();
	Move playfather, playchild;
	int n_childfather = 1, n_childchild = 5, position = 0;

	/* Alocação do nó pai e do filho*/
	father = AlocateNodeTree(n_childfather, boardfather, &playfather);
	child = AlocateNodeTree(n_childchild, boardchild, &playfather);


	/* Testar se a adição do filho foi bem sucedida */
	EXPECT_EQ(1, AddChildNode(father, child, position));
	
	/* Teste se o filho "0" do pai é igual a "child" */
	EXPECT_EQ(father->child[position], child);
	
	FreeTreeNodes(father);
	free(boardfather);
	free(boardchild);
}

/* Teste para verificar a inserção de um filho foi um fracasso quando tentamos
   acessar uma posição maior que o número de filhos
   Procedimento:
   	-Criar Variável para os nós;
   	-Alocar dois tabuleiros;
   	-Alocar duas jogadas;
   	-Inicializar variável com número de filhos
   	-Inicializar variável position com um valor acima do aceitável
   	-Chamar função que aloca o nó para o pai e para o filho;
   	-Verificar se a adição fracassou (retorno 0).
   Resultados:
   	-A inserção do novo filho deve ser um fracasso
 */
TEST(Test_AddChildNode, Verify_Insertion_Failure){
	NodeTree * father, *child;
	TBoard *boardfather = AlocateBoard();
	TBoard *boardchild = AlocateBoard();
	Move playfather, playchild;
	int n_child = 1, position = 5;

	/* Alocação do nó pai e do filho*/
	father = AlocateNodeTree(n_child, boardfather, &playfather);
	child = AlocateNodeTree(n_child, boardchild, &playchild);


	/* Testar se a adição do filho foi um fracasso */
	EXPECT_EQ(0, AddChildNode(father, child, position));

	FreeTreeNodes(father);
	FreeTreeNodes(child);

	free(boardchild);
	free(boardfather);
}

/* Teste para verificar se um nó foi liberado
   Procedimento:
   	-Criar Variável para o nó;
   	-Incializar o tabuleiro e a jogada;
   	-Inicializar variável com número de filhos;
   	-Chamar função que libera um nó;
   	-Verificar se houve liberação de nó.
   Resultados:
   	-O nó deve ter sido liberado
 */
TEST(Test_FreeTreeNodes, Verify_Free_OneNode){
	NodeTree * node;
	TBoard* board = AlocateBoard();
	Move play;
	int n_child = 1;

	node = AlocateNodeTree(n_child, board, &play);

	/* Testar se a liberação deu certo */
	EXPECT_EQ(NULL, FreeTreeNodes(node));
	free(board);

}

/* Teste para verificar se a liberação de um nó com filho está funcionando
   Procedimento:
   	-Criar Variável para os nós;
   	-Incializar os tabuleiros e as jogadas;
   	-Inicializar variável com número de filhos;
   	-Alocar o nó pai e o nó filho;
   	-Verificar se o nó pai foi liberado
   Resultados:
   	-O nó e seu filho devem ter sido liberados
 */
TEST(Test_FreeTreeNodes, Verify_Free_NodewithChild){
	NodeTree * nodefather, *nodechild;
	TBoard *boardfather = AlocateBoard();
	TBoard *boardchild = AlocateBoard();
	Move playfather, playchild;
	int n_child = 1;

	/* Alocação do nó pai e do filho*/
	nodefather = AlocateNodeTree(n_child, boardfather, &playfather);
	nodechild = AlocateNodeTree(n_child, boardchild, &playchild);

	AddChildNode(nodefather, nodechild, 0);

	/* Testar se o nó pai seu filho foram liberados */
	EXPECT_EQ(NULL, FreeTreeNodes(nodefather));


	free(boardfather);
	free(boardchild);
}

int main(int argc, char **argv){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
