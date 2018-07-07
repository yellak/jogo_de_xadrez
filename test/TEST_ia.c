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
	TBoard* board = AlocateBoard();
	StartStandardBoard(board);
	int turn = WHITES_TURN;
	tree = CreateMovesTree(board, turn);

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
	TBoard* board = AlocateBoard();
	StartStandardBoard(board);

	int turn = WHITES_TURN;
	tree = CreateMovesTree(board, turn);

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
	TBoard* board = AlocateBoard();
	StartEmptyBoard(board);
	InsertPiece(board, W_BISHOP, 4, 4);
	InsertPiece(board, B_PAWN, 6, 6);
	int turn = WHITES_TURN;
	Tree* tree = CreateMovesTree(board, turn);

	/* Testar a alocação */
	EXPECT_EQ(0, SortTree(tree, turn));
	EXPECT_EQ(3, tree->root->child[0]->board->Weight);
	FreeTreeNodes(tree->root);
	free(tree);
}

/* Teste para verificar se a função de ordenar a árvore retorna o valor esperado quando a entrada é inválida
   Procedimento: 
   	-Inicia-se o tabuleiro como nulo e o turno como maior que 1 (entradas inválidas)
   	-Cria-se a árvore com os movimentos
   Resultados:
   	-A função deve retornar 0 no caso de fracasso
 */

TEST(Test_SortTree, Verify_InvalidValues_SortTree){

	/* Entradas inválidas */
	TBoard* board = NULL;
	int turn = 5;
	Tree* tree = CreateMovesTree(board, turn);

	/* Testar a alocação */
	EXPECT_EQ(1, SortTree(tree, turn));
}

/* Teste para verificar se a lista contendo todas as jogada ordenadas está sendo criada de maneira adequada
- Inicia-se a árvore com jogadas, usando apenas um peão no tabuleiro;
- Inicia-se a lista para criação;
- Cria-se variáveis com os resultados esperados pela função
- Resultados:
- A função deve retornar o mesmo dado que as variáveis fixadas
*/

TEST(TEST_Best_Plays, VerifyListCreation){
	TBoard* board = AlocateBoard();
	ListOfMoves* Lista;
	StartEmptyBoard(board);
	InsertPiece(board, B_PAWN, 1, 1);
	int turn = BLACKS_TURN;
	Tree* tree = CreateMovesTree(board, turn);
	int plays = tree->root->n_child;
	Lista = Best_Plays(tree, plays);
	
	EXPECT_EQ(1, Lista->first->play.origin[0]);
	EXPECT_EQ(1, Lista->first->play.origin[1]);
	EXPECT_EQ(3, Lista->first->play.destiny[0]);
	EXPECT_EQ(1, Lista->first->play.destiny[1]);
	EXPECT_EQ(1, Lista->first->next->play.origin[0]);
	EXPECT_EQ(1, Lista->first->next->play.origin[1]);
	EXPECT_EQ(2, Lista->first->next->play.destiny[0]);
	EXPECT_EQ(1, Lista->first->next->play.destiny[1]);

	DeleteListOfMoves(Lista);
	FreeTreeNodes(tree->root);
	free(tree);

}
int main(int argc, char **argv){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

