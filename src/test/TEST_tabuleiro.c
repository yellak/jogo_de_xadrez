#include "gtest/gtest.h"
#include "tabuleiro.h"

/* Teste para verificar a validade da função que inicia um tabuleiro vazio
   Procedimento:
   	-Criar Variável para o tabuleiro;
   	-Chamar função que inicia o tabuleiro vazio;
   	-Verificar se todas as peças estão vazias;
   	-Verificar o peso ponderado do tabuleiro.
   Resultados:
   	-Todas as posições devem estar vazias para passar no teste;
   	-O peso ponderado do tabuleiro deve ser 0.
 */
TEST(Test_Verify_Empty_Board, Verify_If_Empty){
	TBoard board;
	ASSERT_EQ(0, StartEmptyBoard(&board));

	int i, j;
	for(i=0; i < 8; i++){
		for(j=0; j < 8; j++){
			EXPECT_EQ(BLANK, board.Board[i][j]);
		}
	}
	EXPECT_EQ(0, board.Weight);
}

/* Teste para verificar a validade da função para casos em que o ponteiro é nulo.
   Procedimento:
   	-Chamar função para uma variável nula.
   Resultados:
   	-É esperado que a função retorne o valor de eroo '1'.
*/
TEST(Test_Verify_Empty_Board, Verify_NULL_Variables){
	TBoard *board = NULL;
	ASSERT_EQ(1, StartEmptyBoard(board));
}

/* Teste para verificar a validade da função que inicia um tabuleiro padrão de xadrez
   Procedimento:
   	-Criar Variável para o tabuleiro;
   	-Chamar função que inicia o tabuleiro padrão;
   	-Verificar se todas as peças correspondem a um tabuleiro padrão inicial de xadrez;
   	-Verificar o peso ponderado do tabuleiro.
   Resultados:
   	-Todas as posições devem estar corretas para passar no teste;
   	-O peso ponderado do tabuleiro deve ser 0.
 */
TEST(Test_Verify_Standard_Board, Verify_If_Correct_Positions){
	TBoard board;
	ASSERT_EQ(0, StartStandardBoard(&board));

	int i, j;

	/* Verificar Torres. */
	EXPECT_EQ(B_TOWER, board.Board[0][0]);
	EXPECT_EQ(B_TOWER, board.Board[0][7]);
	EXPECT_EQ(W_TOWER, board.Board[7][0]);
	EXPECT_EQ(W_TOWER, board.Board[7][7]);
	/* Verificar Cavalos. */
	EXPECT_EQ(B_HORSE, board.Board[0][1]);
	EXPECT_EQ(B_HORSE, board.Board[0][6]);
	EXPECT_EQ(W_HORSE, board.Board[7][1]);
	EXPECT_EQ(W_HORSE, board.Board[7][6]);
	/* Vericar Bispos. */
	EXPECT_EQ(B_BISHOP, board.Board[0][2]);
	EXPECT_EQ(B_BISHOP, board.Board[0][5]);
	EXPECT_EQ(W_BISHOP, board.Board[7][2]);
	EXPECT_EQ(W_BISHOP, board.Board[7][5]);
	/*Verificar Reis e Rainhas. */
	EXPECT_EQ(B_KING, board.Board[0][4]);
	EXPECT_EQ(W_KING, board.Board[7][4]);
	EXPECT_EQ(B_QUEEN, board.Board[0][3]);
	EXPECT_EQ(W_QUEEN, board.Board[7][3]);
	/*Verificar peoes. */
	for(j=0; j < 8; j++){
		EXPECT_EQ(B_PAWN, board.Board[1][j]);
		EXPECT_EQ(W_PAWN, board.Board[6][j]);
	}
	/* VErificar espaços vazios. */
	for(i=2; i < 6; i++){
		for(j=0; j < 8; j++){
			EXPECT_EQ(BLANK, board.Board[i][j]);
		}
	}

	EXPECT_EQ(0, board.Weight);
}

/* Teste para verificar a validade da função para casos em que o ponteiro é nulo.
   Procedimento:
   	-Chamar função para uma variável nula.
   Resultados:
   	-É esperado que a função retorne o valor de erro '1'.
*/
TEST(Test_Verify_Standard_Board, Verify_NULL_Variables){
	TBoard *board = NULL;
	ASSERT_EQ(1, StartStandardBoard(board));
}


int main(int argc, char **argv){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
