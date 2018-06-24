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
TEST(Test_Verify_Empty_Board, Verify_Funcionality){
	TBoard board;
	StartEmptyBoard(&board);

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

int main(int argc, char **argv){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
