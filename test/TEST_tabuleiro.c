#include "gtest/gtest.h"
#include "../include/tabuleiro.h"

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
	TBoard *null = NULL;
	RemovePiece(null, 0, 0);

	/* Testar out of range*/
	TBoard board;
	StartStandardBoard(&board);
	TBoard clone = board;
	RemovePiece(&board, 8, 8);
	RemovePiece(&board, -1, -1);
	EXPECT_EQ(clone.Weight, board.Weight);
}

/* Teste para verificar a função de inserção para entradas inválidas.
	Procedimentos:
	-Chamar a função para valores fora de alcance.
	-Chamar a função para uma peça inválida.
	-Chamar a função para tabuleiro nulo.
	Resultados:
	-É esperado que a função retorne um inteiro -1 indicando falha.
*/
TEST(Test_Insert_Piece, Verify_Invalid_Entries){
	TBoard board;
	char piece = B_KING;
	/* Testar posição invalida */
	int x = 12, y = 14;

	EXPECT_EQ(-1, InsertPiece(&board, piece, x, y));

	/* Testar peça invalida */
	x = 5;
	y = 2;
	piece = 'Z'; 
	EXPECT_EQ(-1, InsertPiece(&board, piece, x, y));

	/* Testar tabuleiro nulo */
	TBoard *null = NULL;
	piece = B_KING;
	EXPECT_EQ(-1, InsertPiece(null, piece, x, y));
}

/* Teste para verificar se a função de inserção insere uma peça corretamente.
	Procedimentos:
	-Chamar a função para peça, tabuleiro e posição válidos.
	Resultados:
	-É esperado que a função retorne um inteiro 0 indicando sucesso.
	-É esperado que a peça esteja na posição desejada no tabuleiro.
*/

TEST(Test_Insert_Piece, Verify_Correct_Insertion){
	TBoard board;
	StartEmptyBoard(&board);
	char piece = B_KING;
	int x = 2, y = 2;

	/* Testar peça inserida corretamente */
	EXPECT_EQ(0, InsertPiece(&board, piece, x, y));
	EXPECT_EQ(GetValue(B_KING), GetValue(board.Board[x][y]));
	EXPECT_EQ(-200, board.Weight);
}

/* Teste para verificar a função que verifica se um tabuleiro é válido para tabuleiros padrões.
   Procedimentos:
   -Criar um tabuleiro padrão;
   -Chamar a função para esse tabuleiro.
   Resultados:
   -É esperado que a função retorne um inteiro 1 indicando a corretude do tabuleiro. 
*/
TEST(Test_Valid_Board, Verify_Standard){
	TBoard board;
	StartStandardBoard(&board);
	
	EXPECT_EQ(1, ValidBoard(&board));
}

/* Teste para verificar a função que verifica se um tabuleiro é válido para tabuleiros vazios e só com um rei.
   Procedimentos:
   -Criar um tabuleiro vazio;
   -Chamar a função para esse tabuleiro.
   -Adicionar um rei preto e chamar a função novamente;
   -Remover o rei, adicionar um branco e chamar a função novamente.
   Resultados:
   -É esperado que a função retorne um inteiro 0, indicando a invalidez do tabuleiro.
*/
TEST(Test_Valid_Board, Verify_Empty_and_One_King){
	TBoard board;
	StartEmptyBoard(&board);
	
	EXPECT_EQ(0, ValidBoard(&board));

	InsertPiece(&board, B_KING , 0, 0);
	EXPECT_EQ(0, ValidBoard(&board));

	RemovePiece(&board, 0, 0);
	InsertPiece(&board, W_KING , 0, 0);
	EXPECT_EQ(0, ValidBoard(&board));
}

/* Teste para verificar a função que verifica se um tabuleiro é válido para tabuleiros com mais de um rei de uma cor.
   Procedimentos:
   -Criar um tabuleiro padrão;
   -Adicionar um rei branco e chamar a função;
   -Remover o rei adicionado, colocar um preto e chamar a função.
   Resultados:
   -É esperado que a função retorne um inteiro 0, indicando a invalidez do tabuleiro.
*/
TEST(Test_Valid_Board, Verify_Two_Kings){
	TBoard board;
	StartStandardBoard(&board);

	InsertPiece(&board, B_KING , 4, 4);
	EXPECT_EQ(0, ValidBoard(&board));

	RemovePiece(&board, 4, 4);
	InsertPiece(&board, W_KING , 4, 4);
	EXPECT_EQ(0, ValidBoard(&board));
}

/* Teste para verificar a função que verifica se um tabuleiro é válido para tabuleiros com mais de 9 rainhas e 0 peoes.
   Procedimentos:
   -Criar um tabuleiro vazio;
   -Adicionar os dois reis de cada cor;
   -Adicionar 9 rainhas de cada cor;
   -Chamar a função;
   -Adicionar uma rainha branca e chamar a função;
   -Remover a última rainha adicionada, adicionar uma preta e chamar a função.
   Resultados:
   -É esperado que a função retorne 1, para a primeira chamada e 0 para as outras duas.
*/
TEST(Test_Valid_Board, Verify_Queens){
	TBoard board;
	StartEmptyBoard(&board);

	InsertPiece(&board, B_KING , 0, 0);
	InsertPiece(&board, W_KING , 7, 7);

	InsertPiece(&board, W_QUEEN , 7, 6);
	InsertPiece(&board, W_QUEEN , 7, 5);
	InsertPiece(&board, W_QUEEN , 7, 4);
	InsertPiece(&board, W_QUEEN , 7, 3);
	InsertPiece(&board, W_QUEEN , 7, 2);
	InsertPiece(&board, W_QUEEN , 7, 1);
	InsertPiece(&board, W_QUEEN , 7, 0);
	InsertPiece(&board, W_QUEEN , 6, 7);
	InsertPiece(&board, W_QUEEN , 6, 6);

	InsertPiece(&board, B_QUEEN , 5, 5);
	InsertPiece(&board, B_QUEEN , 5, 6);
	InsertPiece(&board, B_QUEEN , 5, 7);
	InsertPiece(&board, B_QUEEN , 6, 0);
	InsertPiece(&board, B_QUEEN , 6, 1);
	InsertPiece(&board, B_QUEEN , 6, 2);
	InsertPiece(&board, B_QUEEN , 6, 3);
	InsertPiece(&board, B_QUEEN , 6, 4);
	InsertPiece(&board, B_QUEEN , 6, 5);

	EXPECT_EQ(1, ValidBoard(&board));

	InsertPiece(&board, W_QUEEN , 4, 4);
	EXPECT_EQ(0, ValidBoard(&board));

	RemovePiece(&board, 4, 4);
	InsertPiece(&board, B_QUEEN , 4, 4);
	EXPECT_EQ(0, ValidBoard(&board));
}

/* Teste para verificar a função que verifica se um tabuleiro é válido para tabuleiros com mais de 10 cavalos e nenhum peão.
   Procedimentos:
   -Criar um tabuleiro vazio;
   -Adicionar os dois reis de cada cor;
   -Adicionar 10 cavalos de cada cor;
   -Chamar a função;
   -Adicionar um cavalo branco e chamar a função;
   -Remover o último cavalo adicionado, adicionar um preto e chamar a função.
   Resultados:
   -É esperado que a função retorne 1, para a primeira chamada e 0 para as outras duas.
*/
TEST(Test_Valid_Board, Verify_Horses){
	TBoard board;
	StartEmptyBoard(&board);

	InsertPiece(&board, B_KING , 0, 0);
	InsertPiece(&board, W_KING , 7, 7);

	InsertPiece(&board, W_HORSE , 7, 6);
	InsertPiece(&board, W_HORSE , 7, 5);
	InsertPiece(&board, W_HORSE , 7, 4);
	InsertPiece(&board, W_HORSE , 7, 3);
	InsertPiece(&board, W_HORSE , 7, 2);
	InsertPiece(&board, W_HORSE , 7, 1);
	InsertPiece(&board, W_HORSE , 7, 0);
	InsertPiece(&board, W_HORSE , 6, 7);
	InsertPiece(&board, W_HORSE , 6, 6);
	InsertPiece(&board, W_HORSE , 5, 3);

	InsertPiece(&board, B_HORSE , 5, 4);
	InsertPiece(&board, B_HORSE , 5, 5);
	InsertPiece(&board, B_HORSE , 5, 6);
	InsertPiece(&board, B_HORSE , 5, 7);
	InsertPiece(&board, B_HORSE , 6, 0);
	InsertPiece(&board, B_HORSE , 6, 1);
	InsertPiece(&board, B_HORSE , 6, 2);
	InsertPiece(&board, B_HORSE , 6, 3);
	InsertPiece(&board, B_HORSE , 6, 4);
	InsertPiece(&board, B_HORSE , 6, 5);

	EXPECT_EQ(1, ValidBoard(&board));

	InsertPiece(&board, W_HORSE , 4, 4);
	EXPECT_EQ(0, ValidBoard(&board));

	RemovePiece(&board, 4, 4);
	InsertPiece(&board, B_HORSE , 4, 4);
	EXPECT_EQ(0, ValidBoard(&board));
}

/* Teste para verificar a função que verifica se um tabuleiro é válido para tabuleiros com mais de 10 bispos e nenhum peão.
   Procedimentos:
   -Criar um tabuleiro vazio;
   -Adicionar os dois reis de cada cor;
   -Adicionar 10 bispos de cada cor;
   -Chamar a função;
   -Adicionar um bispo branco e chamar a função;
   -Remover o último bispo adicionado, adicionar um preto e chamar a função.
   Resultados:
   -É esperado que a função retorne 1, para a primeira chamada e 0 para as outras duas.
*/
TEST(Test_Valid_Board, Verify_Bishops){
	TBoard board;
	StartEmptyBoard(&board);

	InsertPiece(&board, B_KING , 0, 0);
	InsertPiece(&board, W_KING , 7, 7);

	InsertPiece(&board, W_BISHOP , 7, 6);
	InsertPiece(&board, W_BISHOP , 7, 5);
	InsertPiece(&board, W_BISHOP , 7, 4);
	InsertPiece(&board, W_BISHOP , 7, 3);
	InsertPiece(&board, W_BISHOP , 7, 2);
	InsertPiece(&board, W_BISHOP , 7, 1);
	InsertPiece(&board, W_BISHOP , 7, 0);
	InsertPiece(&board, W_BISHOP , 6, 7);
	InsertPiece(&board, W_BISHOP , 6, 6);
	InsertPiece(&board, W_BISHOP , 5, 3);

	InsertPiece(&board, B_BISHOP , 5, 4);
	InsertPiece(&board, B_BISHOP , 5, 5);
	InsertPiece(&board, B_BISHOP , 5, 6);
	InsertPiece(&board, B_BISHOP , 5, 7);
	InsertPiece(&board, B_BISHOP , 6, 0);
	InsertPiece(&board, B_BISHOP , 6, 1);
	InsertPiece(&board, B_BISHOP , 6, 2);
	InsertPiece(&board, B_BISHOP , 6, 3);
	InsertPiece(&board, B_BISHOP , 6, 4);
	InsertPiece(&board, B_BISHOP , 6, 5);

	EXPECT_EQ(1, ValidBoard(&board));

	InsertPiece(&board, W_BISHOP , 4, 4);
	EXPECT_EQ(0, ValidBoard(&board));

	RemovePiece(&board, 4, 4);
	InsertPiece(&board, B_BISHOP , 4, 4);
	EXPECT_EQ(0, ValidBoard(&board));
}

/* Teste para verificar a função que verifica se um tabuleiro é válido para tabuleiros com mais de 10 torres e nenhum peão.
   Procedimentos:
   -Criar um tabuleiro vazio;
   -Adicionar os dois reis de cada cor;
   -Adicionar 10 torres de cada cor;
   -Chamar a função;
   -Adicionar uma torre branca e chamar a função;
   -Remover a última torre adicionada, adicionar uma preta e chamar a função.
   Resultados:
   -É esperado que a função retorne 1, para a primeira chamada e 0 para as outras duas.
*/
TEST(Test_Valid_Board, Verify_Towers){
	TBoard board;
	StartEmptyBoard(&board);

	InsertPiece(&board, B_KING , 0, 0);
	InsertPiece(&board, W_KING , 7, 7);

	InsertPiece(&board, W_TOWER , 7, 6);
	InsertPiece(&board, W_TOWER , 7, 5);
	InsertPiece(&board, W_TOWER , 7, 4);
	InsertPiece(&board, W_TOWER , 7, 3);
	InsertPiece(&board, W_TOWER , 7, 2);
	InsertPiece(&board, W_TOWER , 7, 1);
	InsertPiece(&board, W_TOWER , 7, 0);
	InsertPiece(&board, W_TOWER , 6, 7);
	InsertPiece(&board, W_TOWER , 6, 6);
	InsertPiece(&board, W_TOWER , 5, 3);

	InsertPiece(&board, B_TOWER , 5, 4);
	InsertPiece(&board, B_TOWER , 5, 5);
	InsertPiece(&board, B_TOWER , 5, 6);
	InsertPiece(&board, B_TOWER , 5, 7);
	InsertPiece(&board, B_TOWER , 6, 0);
	InsertPiece(&board, B_TOWER , 6, 1);
	InsertPiece(&board, B_TOWER , 6, 2);
	InsertPiece(&board, B_TOWER , 6, 3);
	InsertPiece(&board, B_TOWER , 6, 4);
	InsertPiece(&board, B_TOWER , 6, 5);

	EXPECT_EQ(1, ValidBoard(&board));

	InsertPiece(&board, W_TOWER , 4, 4);
	EXPECT_EQ(0, ValidBoard(&board));

	RemovePiece(&board, 4, 4);
	InsertPiece(&board, B_TOWER , 4, 4);
	EXPECT_EQ(0, ValidBoard(&board));
}

/* Teste para verificar a função que verifica se um tabuleiro é válido para tabuleiros com mais 8 peões.
   Procedimentos:
   -Criar um tabuleiro padrão;
   -Adicionar um peão branco e chamar a função;
   -Remover o peão adicionado, colocar um preto e chamar a função.
   Resultados:
   -É esperado que a função retorne um inteiro 0 para as duas chamadas, indicando a invalidez do tabuleiro.
*/
TEST(Test_Valid_Board, Verify_Pawns){
	TBoard board;
	StartStandardBoard(&board);

	InsertPiece(&board, B_PAWN , 4, 4);
	EXPECT_EQ(0, ValidBoard(&board));

	RemovePiece(&board, 4, 4);
	InsertPiece(&board, W_PAWN , 4, 4);
	EXPECT_EQ(0, ValidBoard(&board));
}

/* Teste para verificar a função que verifica se um tabuleiro é válido para tabuleiros nulos.
   Procedimentos:
   -Chamar a função para um tabuleiro nulo.
   Resultados:
   -Espera-se que a função retorne o valor -1.
*/
TEST(Test_Valid_Board, Verify_NULL){
	EXPECT_EQ(-1, ValidBoard(NULL));
}

/* Teste para verificar a relação entre o número de peões e outras peças na função que verifica se um tabuleiro é válido.
   Procedimentos:
   -Criar um tabuleiro padrão;
   -Adicionar uma rainha e chamar a função;
   -Remover um peão e chamar a função;
   -Adicionar uma torre e chamar a função;
   -Remover um peão e chamar a função;
   -Adicionar um cavalo e chamar a função;
   -Remover um peão e chamar a função;
   -Adicionar um bispo e chamar a função;
   -Remover um peão e chamar a função.

   Resultados:
   -Espera-se que, os procedimentos (2, 4, 6, 8) retornem 0 e o restante, 1.
*/
TEST(Test_Valid_Board, Verify_Equivalance){
	TBoard board;
	StartStandardBoard(&board);

	InsertPiece(&board, W_QUEEN , 4, 0);
	EXPECT_EQ(0, ValidBoard(&board));
	RemovePiece(&board, 6, 0);
	EXPECT_EQ(1, ValidBoard(&board));

	InsertPiece(&board, B_QUEEN , 5, 0);
	EXPECT_EQ(0, ValidBoard(&board));
	RemovePiece(&board, 1, 0);
	EXPECT_EQ(1, ValidBoard(&board));

	InsertPiece(&board, W_TOWER , 4, 1);
	EXPECT_EQ(0, ValidBoard(&board));
	RemovePiece(&board, 6, 1);
	EXPECT_EQ(1, ValidBoard(&board));

	InsertPiece(&board, B_TOWER , 5, 1);
	EXPECT_EQ(0, ValidBoard(&board));
	RemovePiece(&board, 1, 1);
	EXPECT_EQ(1, ValidBoard(&board));

	InsertPiece(&board, W_HORSE , 4, 2);
	EXPECT_EQ(0, ValidBoard(&board));
	RemovePiece(&board, 6, 2);
	EXPECT_EQ(1, ValidBoard(&board));

	InsertPiece(&board, B_HORSE , 5, 2);
	EXPECT_EQ(0, ValidBoard(&board));
	RemovePiece(&board, 1, 2);
	EXPECT_EQ(1, ValidBoard(&board));

	InsertPiece(&board, W_BISHOP , 4, 3);
	EXPECT_EQ(0, ValidBoard(&board));
	RemovePiece(&board, 6, 3);
	EXPECT_EQ(1, ValidBoard(&board));

	InsertPiece(&board, B_BISHOP , 5, 3);
	EXPECT_EQ(0, ValidBoard(&board));
	RemovePiece(&board, 1, 3);
	EXPECT_EQ(1, ValidBoard(&board));
}

/* Teste para verificar a função que muda a peça em uma posição para entradas inválidas.
	Procedimentos:
	-Chamar a função para valores fora de alcance.
	-Chamar a função para uma peça inválida.
	-Chamar a função para tabuleiro nulo.
	Resultados:
	-É esperado que a função retorne um inteiro -1 indicando falha.
*/
TEST(Test_Change_Piece, Verify_Invalid_Entries){
	TBoard board;
	char piece = B_KING;
	/* Testar posição invalida */
	int x = 12, y = 14;

	EXPECT_EQ(-1, ChangePiece(&board, piece, x, y));

	/* Testar peça invalida */
	x = 5;
	y = 2;
	piece = 'Z'; 
	EXPECT_EQ(-1, ChangePiece(&board, piece, x, y));

	/* Testar tabuleiro nulo */
	TBoard *null = NULL;
	piece = B_KING;
	EXPECT_EQ(-1, ChangePiece(null, piece, x, y));
}

/* Teste para verificar a função que muda a peça em uma posição.
	Procedimentos:
	-Criar tabuleiro padrão;
	-Mudar o peão na posição (1,1) por um cavalo preto.
	Resultados:
	-É esperado que a função retorne um inteiro 0 indicando o sucesso da operação;
	-É esperado que a peça na posição (1,1) corresponda a um cavalo;
	-É esperado que o peso do tabuleiro seja modificado para -4.
*/
TEST(Test_Change_Piece, Verify_Valid_Entries){
	TBoard board;
	StartStandardBoard(&board);
	char piece = B_HORSE;
	int x = 6, y = 1;

	/* Testar peça inserida corretamente */
	EXPECT_EQ(0, ChangePiece(&board, piece, x, y));
	EXPECT_EQ(GetValue(piece), GetValue(board.Board[x][y]));
	EXPECT_EQ(-4, board.Weight);
}

/* Teste para verificar a função que muda a peça em uma posição para entradas inválidas.
	Procedimentos:
	-Chamar a função para valores fora de alcance.
	-Chamar a função para tabuleiro nulo.
	Resultados:
	-É esperado que a função retorne um inteiro -1 indicando falha.
*/
TEST(Test_Move_Piece, Verify_Invalid_Entries){
	TBoard board;
	char piece = B_KING;
	/* Testar posição invalida */

	EXPECT_EQ(-1, MovePiece(&board, 12, 13, 0, 0));
	EXPECT_EQ(-1, MovePiece(&board, 0, 0, 9, 14));

	/* Testar tabuleiro nulo */
	TBoard *null = NULL;
	EXPECT_EQ(-1, MovePiece(null, 0, 0, 1, 1));
}

int main(int argc, char **argv){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

TEST(Test_alocate, Alocate_new_board){
	TBoard* test_board = NULL;
	test_board = AlocateBoard();

	EXPECT_EQ(NULL, !test_board);
	EXPECT_EQ(0, test_board->Weight);
}

