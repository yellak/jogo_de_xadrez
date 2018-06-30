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

/* Teste para verificar se a sintaxe de uma string fornecida pelo usuário está
   correta.
   
   Procedimentos:
   - Verificar sintaxe para notações válidas e inválidas para tipo de peça
     fornecida 
   - Verifica sintaxe para notações válidadas e inválidas para o tipo de
     movimento fornecido 

   Resultados:
   - Esperamos valores true caso a notação esteja correta e false caso esteja
     errada
*/
TEST(Algebric_verification, Named_movement)
{
	char named_test_move[7];

	/* Notação inválida para tipo de peça */
	strcpy(named_test_move, "Le2-e4");
	EXPECT_EQ(false, verify_syntax_move(named_test_move));

	/* Notação válida para tipo de peça */
	strcpy(named_test_move, "Re2-e4");
	EXPECT_EQ(true, verify_syntax_move(named_test_move));

	/* Notação inválida para tipo de movimento */
	strcpy(named_test_move, "Ra1%a5");
	EXPECT_EQ(false, verify_syntax_move(named_test_move));

	/* Notação válida para tipo de movimento */
	strcpy(named_test_move, "Ra1-a5");
	EXPECT_EQ(true, verify_syntax_move(named_test_move));
}

/* Teste para verificar a sintaxe da string fornecida pelo usuário no caso dele
   fornecer um roque, ou no caso de verificar quem é o vencedor

   Procedimentos:
   - Verificar sintaxe para quem é o vencedor
   - Verificar para roque pelo lado do rei

   Resultados:
   - true para quando a notação está correta e false para quando a notação está
     errada */
TEST(Algebric_verification, Castling_or_winner)
{
	char cas_or_winner[4];
	
	/* Notação válida para branca venceu */
	strcpy(cas_or_winner, "1-0");
	EXPECT_EQ(true, verify_syntax_move(cas_or_winner));

	/* Notação válida para preto venceu */
	strcpy(cas_or_winner, "0-1");
	EXPECT_EQ(true, verify_syntax_move(cas_or_winner));

	/* Notação válida para roque pelo lado do rei */
	strcpy(cas_or_winner, "0-0");
	EXPECT_EQ(true, verify_syntax_move(cas_or_winner));

	/* Notação inválida para roque ou vencedor */
	strcpy(cas_or_winner, "1-1");
	EXPECT_EQ(false, verify_syntax_move(cas_or_winner));
}

/* Teste para verificar a sintaxe dada para roque pelo lado da rainha */
TEST(Algebric_verification, Queenside_castling)
{
	char movement[6];

	/* Notação válida para roque pelo lado da rainha */
	strcpy(movement, "0-0-0");
	EXPECT_EQ(true, verify_syntax_move(movement));

	/* Notação inválida para roque pelo lado da rainha */
	strcpy(movement, "0-1-0");
	EXPECT_EQ(false, verify_syntax_move(movement));
}

/* 
 * TEST(ChessMove_translation, Normal_movement)
 * {
 * 	char named_test_move[7];
 * 	char test_move[6];
 * 	Move* expect_move = (Move*) malloc(sizeof(Move));
 * 	Move* result;
 * 
 * 	/\* Cavalo da b1 para a3 *\/
 * 	strcpy(named_test_move, "Nb1-a3");
 * 	
 * 	/\* Movimento esperado *\/
 * 	expect_move->origin[0] = 7;
 * 	expect_move->origin[1] = 1;
 * 	expect_move->destiny[0] = 5;
 * 	expect_move->destiny[1] = 0;
 * 
 * 	/\* Chamando a função que retornará o movimento obtido *\/
 * 	result = algebric_translate(named_test_move);
 * 	
 * 	/\* Realizando os testes *\/
 * 	EXPECT_EQ(NULL, !result);
 * 	if(result != NULL)
 * 		{
 * 			EXPECT_EQ(expect_move->origin[0], result->origin[0]);
 * 			EXPECT_EQ(expect_move->origin[1], result->origin[1]);
 * 			EXPECT_EQ(expect_move->destiny[0], result->destiny[0]);
 * 			EXPECT_EQ(expect_move->destiny[1], result->destiny[1]);
 * 		}
 * 
 * 	free(expect_move);
 * 	free(result);
 * }
 */

int main(int argc, char **argv){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
