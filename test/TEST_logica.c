#include "gtest/gtest.h"
#include "../include/tabuleiro.h"
#include "../include/logica.h"

/* Teste para verificar se a função de criação da lista de movimentos funciona corretamente com um tabuleiro nulo.
	Procedimentos:
	-Chamar a função de criação da lista com um tabuleiro nulo.
	Resultados:
	-É esperado que a função retorne um ponteiro NULL indicando sucesso.
*/
TEST(Test_CreateListOfMoves, Verify_Correct_CreationNullBoard){
	TBoard* null = NULL;
	ListOfMoves* list = AnalyzePossibleMovementsBlack(null);
	EXPECT_EQ(NULL, list);
}

/* Teste para verificar se a função de criação da lista de movimentos funciona corretamente com um tabuleiro não nulo.
	Procedimentos:
	-Chamar a função de criação da lista com um tabuleiro não nulo.
	Resultados:
	-É esperado que a função retorne um ponteiro não nulo indicando sucesso.
*/
TEST(Test_CreateListOfMoves, Verify_Correct_CreationNonNullBoard){
	TBoard board;
	StartEmptyBoard(&board);
	ListOfMoves* list = AnalyzePossibleMovementsBlack(&board);
	EXPECT_EQ(NULL, !list);
	EXPECT_EQ(NULL, !list->Plays);
}

/* Teste para verificar se a função de deleção da lista de movimentos funciona corretamente com um tabuleiro nulo.
	Procedimentos:
	-Chamar a função de deleao da lista com um tabuleiro nulo.
	Resultados:
	-É esperado que a função retorne um inteiro que indica sucesso.
*/
TEST(Test_ListDeletion, Verify_Correct_FreesWithNullList){
	TBoard* null = NULL;
	ListOfMoves* list = AnalyzePossibleMovementsBlack(null);
	EXPECT_EQ(-1, DeleteMoveList(list));
}

/* Teste para verificar se a função de deleção da lista de movimentos funciona corretamente com um tabuleiro não nulo.
	Procedimentos:
	-Chamar a função de deleao da lista com um tabuleiro não nulo.
	Resultados:
	-É esperado que a função retorne um inteiro que indica sucesso.
*/
TEST(Test_ListDeletion, Verify_Correct_FreesWithNonNullList){
	TBoard board;
	StartEmptyBoard(&board);
	ListOfMoves* list = AnalyzePossibleMovementsBlack(&board);
	EXPECT_EQ(0, DeleteMoveList(list));
}

int main(int argc, char **argv){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}