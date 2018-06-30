#include "gtest/gtest.h"
#include <string.h>
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

TEST(Test_ChessMove_translation, Normal_movement)
{
	char named_test_move[7];
	char test_move[6];
	Move* expect_move = (Move*) malloc(sizeof(Move));
	Move* result = (Move*) malloc(sizeof(Move));

	/* Cavalo da b1 para a3 */
	strcpy(named_test_move, "Nb1-a3");
	
	/* Movimento esperado */
	expect_move->origin[0] = 7;
	expect_move->origin[1] = 1;
	expect_move->destiny[0] = 5;
	expect_move->destiny[1] = 0;

	/* Chamando a função que retornará o movimento obtido */
	result = algebric_translate(named_test_move);
	
	/* Realizando os testes */
	EXPECT_EQ(NULL, !result);
	if(result != NULL)
		{
			EXPECT_EQ(expect_move->origin[0], result->origin[0]);
			EXPECT_EQ(expect_move->origin[1], result->origin[1]);
			EXPECT_EQ(expect_move->destiny[0], result->destiny[0]);
			EXPECT_EQ(expect_move->destiny[1], result->destiny[1]);
		}
}

int main(int argc, char **argv){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
