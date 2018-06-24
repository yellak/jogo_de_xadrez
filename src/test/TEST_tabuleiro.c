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

/* Teste para verificar a validade da função que veifica qual peça está em determinda posição para um tabuleiro vazio.
   Procedimentos:
   -Criar variável para o tabuleiro;
   -Chamar função que inicializa um tabuleiro vazio;
   -Chamar a função para uma posição do tabuleiro.
   Resultados:
   -É esperado que a função retorne o indicador para espaço vazio.
*/
TEST(Test_What_Piece_in_Position, Verify_Empty_Boards){
	TBoard board;
	StartEmptyBoard(&board);
	EXPECT_EQ(BLANK, WhatPiece(&board, 2, 0));
}

/* Teste para verificar a validade da função que veifica qual peça está em determinda posição para um tabuleiro padrão.
   Procedimentos:
   -Criar variável para o tabuleiro;
   -Chamar função que inicializa um tabuleiro padrão;
   -Chamar a função para as posições (0,0), (6,1) e (7,4) do tabuleiro.
   Resultados:
   -É esperado que a função retorne os indicadores, respectivamente, de torre negra, peão branco e rei branco.
*/
TEST(Test_What_Piece_in_Position, Verify_Standard_Boards){
	TBoard board;
	StartStandardBoard(&board);
	EXPECT_EQ(B_TOWER, WhatPiece(&board, 0, 0));
	EXPECT_EQ(W_PAWN, WhatPiece(&board, 6, 1));
	EXPECT_EQ(W_KING, WhatPiece(&board, 7, 4));
}

/* Teste para verificar a validade da função que veifica qual peça está em determinda posição para tabuleiros nulos e para espaços fora do tabuleiro.
   Procedimentos:
   -Criar variável nula para o tabuleiro;
   -Chamar a função para a variável nula;
   -Chamar função que inicializa um tabuleiro vazio para variavel nao-nula;
   -Chamar a função para as coordenada (8,8) e (-1,-1).
   -É esperado que a função retorne o indicador de fora dos limites para os dois casos.
*/
TEST(Test_What_Piece_in_Position, Verify_Out_of_Range){
	/*Testar tabuleiro nulo. */
	TBoard *nul = NULL;
	EXPECT_EQ(OUT_OF_RANGE, WhatPiece(nul, 0, 0));

	/* Testar out of range*/
	TBoard board;
	StartStandardBoard(&board);
	EXPECT_EQ(OUT_OF_RANGE, WhatPiece(&board, 8, 8));
	EXPECT_EQ(OUT_OF_RANGE, WhatPiece(&board, -1, -1));
}

/* Teste para verificar a função que retorna o valor de uma peça para todas as peças possíveis.
   Procedimentos:
   -Criar variável para o tabuleiro e chamar a função de iniciar tabuleiro padrão.
   -Chamar a função para posições do tabuleiro que correspondem a peças diferentes.
   Resultados:
   -É esperado que a função retorne os valores padrões de peças de xadrez para cada peça (especificado nos comentário da tabuleiro.c e tabuleiro.h) e zero para espaços vazios.
*/
TEST(Test_Get_Value_of_Piece, Verify_Every_Piece){
	TBoard board;
	StartStandardBoard(&board);

	/* Testar Peões */
	EXPECT_EQ(1, GetValue(WhatPiece(&board, 6, 0)));
	EXPECT_EQ(-1, GetValue(WhatPiece(&board, 1, 0)));
	/* Testar Cavalos. */
	EXPECT_EQ(3, GetValue(WhatPiece(&board, 7, 1)));
	EXPECT_EQ(-3, GetValue(WhatPiece(&board, 0, 1)));
	/* Testar Bispos. */
	EXPECT_EQ(3, GetValue(WhatPiece(&board, 7, 2)));
	EXPECT_EQ(-3, GetValue(WhatPiece(&board, 0, 2)));
	/* Testar Torres. */
	EXPECT_EQ(5, GetValue(WhatPiece(&board, 7, 0)));
	EXPECT_EQ(-5, GetValue(WhatPiece(&board, 0, 0)));
	/* Testar Rainhas. */
	EXPECT_EQ(9, GetValue(WhatPiece(&board, 7, 3)));
	EXPECT_EQ(-9, GetValue(WhatPiece(&board, 0, 3)));
	/* Testar Reis. */
	EXPECT_EQ(200, GetValue(WhatPiece(&board, 7, 4)));
	EXPECT_EQ(-200, GetValue(WhatPiece(&board, 0, 4)));
	/* Testar espaço vazio. */
	EXPECT_EQ(0, GetValue(WhatPiece(&board, 5, 5)));
}

/* Teste para verificar a funçãoque retorna o valor de uma peça para peças não existentes.
   Procedimentos:
   -Chamar a função para OUT_OF_RANGE;
   -Chamar a função para o caractere *;
   Resultados:
   -É esperado que a função retorne 0 em todos esses casos.
*/
TEST(Test_Get_Value_of_Piece, Verify_Non_Pieces){
	EXPECT_EQ(0, GetValue(OUT_OF_RANGE));
	EXPECT_EQ(0, GetValue('*'));
}

/* Teste para verificar se a função de remoção remove uma peça que está no tabuleiro.
   Procedimentos:
   -Iniciar um tabuleiro padrão;
   -Remover a peça da posição (0,0);
   -Verificar se o espaço após a remoção;
   -Verificar se o peso do tabuleiro; 
   -Remover a peça da posição (7,1);
   -Verificar o espaço após a remoção;
   -Verificar o peso do tabuleiro.
   Resultados:
   -O espaços removidos devem ficar como BLANK;
   -O peso, depois da primeira remoção, deve ficar +5;
   -O peso, depois da segunda remoção, deve ficar +2;
*/
TEST(Test_Remove_Piece, Verify_Remotion){
	TBoard board;
	StartStandardBoard(&board);

	RemovePiece(&board, 0, 0);
	EXPECT_EQ(BLANK, WhatPiece(&board, 0, 0));
	EXPECT_EQ(5, board.Weight);

	RemovePiece(&board, 7, 1);
	EXPECT_EQ(BLANK, WhatPiece(&board, 7, 1));
	EXPECT_EQ(2, board.Weight);

	RemovePiece(&board, 5, 5);
	EXPECT_EQ(BLANK, WhatPiece(&board, 5, 5));
	EXPECT_EQ(2, board.Weight);
}

/* Teste para verificar se a função de remoção para entradas inválidas. 
   Procedimentos:
   -Chamar a função para um tabuleiro nulo.
   -Chamar a função para valores fora de alcance.
   Resultados:
   -É esperado que a função retorne sem falha de segmentação.
*/
TEST(Test_Remove_Piece, Verify_Invalid_Entries){
	/*Testar tabuleiro nulo. */
	TBoard *nul = NULL;
	RemovePiece(nul, 0, 0);

	/* Testar out of range*/
	TBoard board;
	StartStandardBoard(&board);
	TBoard clone = board;
	RemovePiece(&board, 8, 8);
	RemovePiece(&board, -1, -1);
	EXPECT_EQ(clone.Weight, board.Weight);
}

int main(int argc, char **argv){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}