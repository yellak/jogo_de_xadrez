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

	/* Verificar se todas as posições estão vazias. */
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
   	-É esperado que a função retorne o valor de erro '1'.
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
	/* Verificar Bispos. */
	EXPECT_EQ(B_BISHOP, board.Board[0][2]);
	EXPECT_EQ(B_BISHOP, board.Board[0][5]);
	EXPECT_EQ(W_BISHOP, board.Board[7][2]);
	EXPECT_EQ(W_BISHOP, board.Board[7][5]);
	/*Verificar Reis e Rainhas. */
	EXPECT_EQ(B_KING, board.Board[0][4]);
	EXPECT_EQ(W_KING, board.Board[7][4]);
	EXPECT_EQ(B_QUEEN, board.Board[0][3]);
	EXPECT_EQ(W_QUEEN, board.Board[7][3]);
	/*Verificar peões. */
	for(j=0; j < 8; j++){
		EXPECT_EQ(B_PAWN, board.Board[1][j]);
		EXPECT_EQ(W_PAWN, board.Board[6][j]);
	}
	/* Verificar espaços vazios. */
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


/* Teste para verificar o funcionamento da função ColorPiece
   
   Procedimentos:
   -Chamar a função para uma peça branca;
   -Chamar a função para uma peça branca;
   -Chamar a função para um espaço em branco;
   -Chamar a função para um caractere não peça.

   Resultados:
   -Na primeira chamada, espera-se o retorno 1;
   -Na segunda chamada, espera-se o retorno 0;
   -Nas chamadas subsequentes, se espera o retorno -1.
*/
TEST(Test_Color_Piece, Verify_Correct_Color){
	/* Verificar para peças válidas. */
	EXPECT_EQ(1, ColorPiece(W_TOWER));
	EXPECT_EQ(0, ColorPiece(B_TOWER));

	/* Verificarnão peças. */
	EXPECT_EQ(-1, ColorPiece('u'));
	EXPECT_EQ(-1, ColorPiece(BLANK));
}

/* Teste para verificar a validade da função que verifica qual peça está em determinada posição para um tabuleiro vazio.
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

	/* Chamar para espaço vazoi. */
	EXPECT_EQ(BLANK, WhatPiece(&board, 2, 0));
}

/* Teste para verificar a validade da função que verifica qual peça está em determinada posição para um tabuleiro padrão.
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

	/* Verificar para posições do tabuleiro padrão. */
	EXPECT_EQ(B_TOWER, WhatPiece(&board, 0, 0));
	EXPECT_EQ(W_PAWN, WhatPiece(&board, 6, 1));
	EXPECT_EQ(W_KING, WhatPiece(&board, 7, 4));
}

/* Teste para verificar a validade da função que verifica qual peça está em determinada posição para tabuleiros nulos e para espaços fora do tabuleiro.
   Procedimentos:
   -Criar variável nula para o tabuleiro;
   -Chamar a função para a variável nula;
   -Chamar função que inicializa um tabuleiro vazio para variável não nula;
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

/* Teste para verificar a função que retorna o valor de uma peça para peças não existentes.
   Procedimentos:
   -Chamar a função para OUT_OF_RANGE;
   -Chamar a função para o caractere *;
   Resultados:
   -É esperado que a função retorne 0 em todos esses casos.
*/
TEST(Test_Get_Value_of_Piece, Verify_Non_Pieces){
	/* Testar para caracteres inválidos. */
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

	/* Remover peças e testar tabuleiro resultante. */
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
	
	/* Chamar função para tabuleiro padrão. */
	EXPECT_EQ(1, ValidBoard(&board));
}

/* Teste para verificar a função que verifica se um tabuleiro é válido para tabuleiros com só uma peça de cada (exceto peão).
   Procedimentos:
   -Criar um tabuleiro padrão;
   -Remover peças repetidas e chamar a função.
   Resultados:
   -É esperado que a função retorne um inteiro 1 indicando a corretude do tabuleiro. 
*/
TEST(Test_Valid_Board, Verify_No_Double_Pieces){
	TBoard board;
	StartStandardBoard(&board);
	
	/* Remover peças extras. */
	RemovePiece(&board, 0, 0);
	RemovePiece(&board, 0, 1);
	RemovePiece(&board, 0, 2);
	RemovePiece(&board, 7, 0);
	RemovePiece(&board, 7, 1);
	RemovePiece(&board, 7, 2);

	/* Chamar função para tabuleiro padrão. */
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
	
	/* Chamar função para tabuleiro vazio. */
	EXPECT_EQ(0, ValidBoard(&board));

	/* Chamar função para tabuleiros com só um rei. */
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

	/* Chamar funções para tabuleiros com mais de um rei. */
	InsertPiece(&board, B_KING , 4, 4);
	EXPECT_EQ(0, ValidBoard(&board));

	RemovePiece(&board, 4, 4);
	InsertPiece(&board, W_KING , 4, 4);
	EXPECT_EQ(0, ValidBoard(&board));
}

/* Teste para verificar a função que verifica se um tabuleiro é válido para tabuleiros com mais de 9 rainhas e 0 peões.
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

	/* Adicionar reis. */
	InsertPiece(&board, B_KING , 0, 0);
	InsertPiece(&board, W_KING , 7, 7);

	/* Inseir número máximo de rainhas.*/
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

	/* Adicionar novas rainhas e testar. */
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

	/* Adicionar reis. */
	InsertPiece(&board, B_KING , 0, 0);
	InsertPiece(&board, W_KING , 7, 7);

	/* Inseir número máximo de cavalos.*/
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

	/* Adicionar novos cavalos e testar. */
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

	/* Adicionar reis. */
	InsertPiece(&board, B_KING , 0, 0);
	InsertPiece(&board, W_KING , 7, 7);

	/* Inseir número máximo de bispos.*/
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

	/* Adicionar novos bispos e testar. */
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

	/* Adicionar reis. */
	InsertPiece(&board, B_KING , 0, 0);
	InsertPiece(&board, W_KING , 7, 7);

	/* Inseir número máximo de torres.*/
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

	/* Adicionar novas torres e testar. */
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

	/* Verificar função para núnmero escessivo de peões pretos. */
	InsertPiece(&board, B_PAWN , 4, 4);
	EXPECT_EQ(0, ValidBoard(&board));

	/* Verificar função para núnmero escessivo de peões brancos. */
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

	/* Testar equivalência do número de peões e outras peças. */
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

/* Teste para verificar a função que muda a peça em uma posição indo para uma posição vazia.
	Procedimentos:
	-Criar tabuleiro padrão;
	-Mover o peão na posição (6,1) para a posição (4,1);
	Resultados:
	-É esperado que a função retorne um inteiro 0 indicando o sucesso da operação;
	-É esperado que a posição (6,1) esteja vazia;
	-É esperado que a peça na posição (4,1)  seja um peão.
	-É esperado que o peso do tabuleiro não seja modificado.

*/
TEST(Test_Move_Piece, Test_Empty_Space){
	TBoard board;
	StartStandardBoard(&board);

	/* Mover peça. */
	EXPECT_EQ(0, MovePiece(&board, 6, 1, 4, 1));

	/* Verificar posições. */
	EXPECT_EQ(GetValue(BLANK), GetValue(board.Board[6][1]));
	EXPECT_EQ(GetValue(W_PAWN), GetValue(board.Board[4][1]));

	/* Verificar peso. */
	EXPECT_EQ(0, board.Weight);
}

/* Teste para verificar a função que muda a peça em uma posição indo para uma posição cheia.
	Procedimentos:
	-Criar tabuleiro padrão;
	-Mover o peão na posição (6,1) para a posição (1,1);
	Resultados:
	-É esperado que a função retorne um inteiro 0 indicando o sucesso da operação;
	-É esperado que a posição (6,1) esteja vazia;
	-É esperado que a peça na posição (4,1)  seja um peão branco.
	-É esperado que o peso do tabuleiro seja modificado para 1.

*/
TEST(Test_Move_Piece, Test_Full_Space){
	TBoard board;
	StartStandardBoard(&board);

	/* Mover peça. */
	EXPECT_EQ(0, MovePiece(&board, 6, 1, 1, 1));

	/* Verificar posições. */
	EXPECT_EQ(GetValue(BLANK), GetValue(board.Board[6][1]));
	EXPECT_EQ(GetValue(W_PAWN), GetValue(board.Board[1][1]));

	/* Verificar peso. */
	EXPECT_EQ(1, board.Weight);
}

/* Teste para verificar o movimento de roque.
	Procedimentos:
	-Criar 2 tabuleiros padrões;
	-Remover rainhas, bispos e cavalos;
	-Chamar roques pequenos para um tabuleiro e grandes para o outro.
	Resultados:
	-É esperado que a função retorne um inteiro 0 indicando o sucesso da operação;
	-É esperado que as peças estejam na mesma posição;
	-É esperado que o peso do tabuleiro continue 0.

*/
TEST(Test_Move_Piece, Test_Roque){
	TBoard board1, board2;
	StartStandardBoard(&board1);

	/* Remover bispos, cavalos e rainhas. */
	RemovePiece(&board1, 0, 1);
	RemovePiece(&board1, 0, 2);
	RemovePiece(&board1, 0, 3);
	RemovePiece(&board1, 0, 5);
	RemovePiece(&board1, 0, 6);
	RemovePiece(&board1, 7, 1);
	RemovePiece(&board1, 7, 2);
	RemovePiece(&board1, 7, 3);
	RemovePiece(&board1, 7, 5);
	RemovePiece(&board1, 7, 6);
	board2 = board1;

	/* Chamar e testar movimentos do roque. */
	EXPECT_EQ(0, MovePiece(&board1, 0, 4, 0, 6));
	EXPECT_EQ(0, MovePiece(&board1, 7, 4, 7, 6));
	EXPECT_EQ(0, MovePiece(&board2, 0, 4, 0, 2));
	EXPECT_EQ(0, MovePiece(&board2, 7, 4, 7, 2));

	/* Verificar posições nos tabuleiros. */
	EXPECT_EQ(GetValue(BLANK), GetValue(board1.Board[0][4]));
	EXPECT_EQ(GetValue(BLANK), GetValue(board1.Board[0][7]));
	EXPECT_EQ(GetValue(BLANK), GetValue(board1.Board[7][4]));
	EXPECT_EQ(GetValue(BLANK), GetValue(board1.Board[7][7]));
	EXPECT_EQ(GetValue(B_KING), GetValue(board1.Board[0][6]));
	EXPECT_EQ(GetValue(B_TOWER), GetValue(board1.Board[0][5]));
	EXPECT_EQ(GetValue(W_KING), GetValue(board1.Board[7][6]));
	EXPECT_EQ(GetValue(W_TOWER), GetValue(board1.Board[7][5]));

	EXPECT_EQ(GetValue(BLANK), GetValue(board2.Board[0][4]));
	EXPECT_EQ(GetValue(BLANK), GetValue(board2.Board[0][0]));
	EXPECT_EQ(GetValue(BLANK), GetValue(board2.Board[7][4]));
	EXPECT_EQ(GetValue(BLANK), GetValue(board2.Board[7][0]));
	EXPECT_EQ(GetValue(B_KING), GetValue(board2.Board[0][2]));
	EXPECT_EQ(GetValue(B_TOWER), GetValue(board2.Board[0][3]));
	EXPECT_EQ(GetValue(W_KING), GetValue(board2.Board[7][2]));
	EXPECT_EQ(GetValue(W_TOWER), GetValue(board2.Board[7][3]));

	/* Verificar pesos dos tabuleiros. */
	EXPECT_EQ(0, board1.Weight);
	EXPECT_EQ(0, board2.Weight);
}

/* Teste para verificar a validez da função que aloca um novo tabuleiro
    Procedimentos:
    - Verificar se foi alocado um espaço de memória para o tabuleiro
    - Verificar se o tabuleiro alocado possui peso zero

    Resultados:
    - Espera-se que a função responda corretamente para os procedimentos
      acima
 */
TEST(Test_alocate, Alocate_new_board){
	TBoard* test_board = NULL;
	test_board = AlocateBoard();

	EXPECT_EQ(NULL, !test_board);
	EXPECT_EQ(0, test_board->Weight);

	free(test_board);
}

/* Teste para a função de copiar dois tabuleiros
    Procedimentos:
    - Fazer comparações entre o esperado e o recebido para um tabuleiro vazio

    Resultados:
    - Espera-se que todas as peças dos tabuleiros tenham sido copiadas de
      maneira correta
*/
TEST(Copy_boards, CopyEmptyBoards){
	int i, j;
	TBoard* test_board = AlocateBoard();
	TBoard* expect_board = AlocateBoard();

	/* Inicializando um tabuleiro esperado vazio */
	StartEmptyBoard(expect_board);

	/* Copiando o tabuleiro criado */
	copy_boards(test_board, expect_board);

	/* Fazendo a comparação para cada peça no tabuleiro */
	for(i = 0; i < 8; i++){
		for(j = 0; j < 8; j++){
			EXPECT_EQ(test_board->Board[i][j], expect_board->Board[i][j]);
		}
	}

	/* Verificando a cópia dos pesos */
	EXPECT_EQ(test_board->Weight, expect_board->Weight);

	free(test_board);
	free(expect_board);
}

/* Teste para a função de copiar um tabuleiro em outro
   Procedimentos:
   - São os mesmos do último teste para esta função, mas desta vez faremos as
     verificações para um tabuleiro de base padrão

   Resultados:
   - Espera-se que a cópia tenha todas as peças nas mesmas posições que o
     copiado
 */
TEST(Copy_boards, CopySTDBoard){
	int i, j;
	TBoard* test_board = AlocateBoard();
	TBoard* expect_board = AlocateBoard();

	/* Inicializando tabuleiro esperado */
	StartEmptyBoard(expect_board);
	StartStandardBoard(expect_board);

	/* Chamando a função que será testada */
	copy_boards(test_board, expect_board);
	
	/* Fazendo a comparação para cada peça no tabuleiro */
	for(i = 0; i < 8; i++){
		for(j = 0; j < 8; j++){
			EXPECT_EQ(test_board->Board[i][j], expect_board->Board[i][j]);
		}
	}

	EXPECT_EQ(test_board->Weight, expect_board->Weight);

	free(test_board);
	free(expect_board);
}

/* Teste para a função de copiar um tabuleiro em outro para tabuleiros nulos
   Procedimentos:
   -Chamar a função para tabuleiros nulos.

   Resultados:
   -Espera-se que a função retorne 1.
 */
TEST(Copy_boards, NULL_Board){
	TBoard board;

	/* Testar a função para cada tabuleiro sendo nulo. */
	EXPECT_EQ(1, copy_boards(&board, NULL));
	EXPECT_EQ(1, copy_boards(NULL, &board));
	EXPECT_EQ(1, copy_boards(NULL, NULL));
}

/* Teste para a função de verificar se uma peça é válida ou não
   Procedimentos:
   - Chamar a função para cada uma das letras do alfabeto, maiúsculas e
     minúsculas

   Resultados:
   - Espera-se que a função retorne false para cada letra que não é válida e
     true para cada letra válida */
TEST(Valid_piece, Letters)
{
	/* Testando as letras do alfabeto */
	EXPECT_EQ(false, valid_piece('A'));
	EXPECT_EQ(false, valid_piece('a'));

	EXPECT_EQ(true, valid_piece('B'));
	EXPECT_EQ(true, valid_piece('b'));

	EXPECT_EQ(false, valid_piece('C'));
	EXPECT_EQ(false, valid_piece('c'));

	EXPECT_EQ(false, valid_piece('D'));
	EXPECT_EQ(false, valid_piece('d'));

	EXPECT_EQ(false, valid_piece('E'));
	EXPECT_EQ(false, valid_piece('e'));

	EXPECT_EQ(false, valid_piece('F'));
	EXPECT_EQ(false, valid_piece('f'));

	EXPECT_EQ(false, valid_piece('G'));
	EXPECT_EQ(false, valid_piece('g'));

	EXPECT_EQ(false, valid_piece('H'));
	EXPECT_EQ(false, valid_piece('h'));

	EXPECT_EQ(false, valid_piece('I'));
	EXPECT_EQ(false, valid_piece('i'));

	EXPECT_EQ(false, valid_piece('J'));
	EXPECT_EQ(false, valid_piece('j'));

	EXPECT_EQ(true, valid_piece('K'));
	EXPECT_EQ(true, valid_piece('k'));

	EXPECT_EQ(false, valid_piece('L'));
	EXPECT_EQ(false, valid_piece('l'));

	EXPECT_EQ(false, valid_piece('M'));
	EXPECT_EQ(false, valid_piece('m'));

	EXPECT_EQ(true, valid_piece('N'));
	EXPECT_EQ(true, valid_piece('n'));

	EXPECT_EQ(false, valid_piece('O'));
	EXPECT_EQ(false, valid_piece('o'));

	EXPECT_EQ(true, valid_piece('P'));
	EXPECT_EQ(true, valid_piece('p'));

	EXPECT_EQ(true, valid_piece('Q'));
	EXPECT_EQ(true, valid_piece('q'));

	EXPECT_EQ(true, valid_piece('R'));
	EXPECT_EQ(true, valid_piece('r'));

	EXPECT_EQ(false, valid_piece('S'));
	EXPECT_EQ(false, valid_piece('s'));

	EXPECT_EQ(false, valid_piece('T'));
	EXPECT_EQ(false, valid_piece('t'));

	EXPECT_EQ(false, valid_piece('U'));
	EXPECT_EQ(false, valid_piece('u'));

	EXPECT_EQ(false, valid_piece('V'));
	EXPECT_EQ(false, valid_piece('v'));

	EXPECT_EQ(false, valid_piece('W'));
	EXPECT_EQ(false, valid_piece('w'));

	EXPECT_EQ(false, valid_piece('X'));
	EXPECT_EQ(false, valid_piece('x'));

	EXPECT_EQ(false, valid_piece('Y'));
	EXPECT_EQ(false, valid_piece('y'));

	EXPECT_EQ(false, valid_piece('Z'));
	EXPECT_EQ(false, valid_piece('z'));
}

/* Teste para a função de verificar se uma peça é válida
   Procedimentos:
   - Chamar a função para cada um dos números de 0 a 9

   Resultados:
   - Espera-se que a função retorne false para qualquer um desses números uma
     vez que números não são peças de xadrez */
TEST(Valid_piece, Numbers)
{
	/* Testando para números de 0 a 9 */
	EXPECT_EQ(false, valid_piece('0'));
	EXPECT_EQ(false, valid_piece('1'));
	EXPECT_EQ(false, valid_piece('2'));
	EXPECT_EQ(false, valid_piece('3'));
	EXPECT_EQ(false, valid_piece('4'));
	EXPECT_EQ(false, valid_piece('5'));
	EXPECT_EQ(false, valid_piece('6'));
	EXPECT_EQ(false, valid_piece('7'));
	EXPECT_EQ(false, valid_piece('8'));
	EXPECT_EQ(false, valid_piece('9'));
}

/* Teste para a função de verificar se uma peça é válida
   Procedimentos:
   - Chamar a função para diferentes caracteres da tabela ASCII
 
   Resultados:
   - Espera-se que a função retorne false para todos estes caracteres uma vez
     que eles não são peças de xadrez válidas */
TEST(Valid_piece, Other_chars)
{
	/* Testando para caracteres diversos */
	EXPECT_EQ(false, valid_piece('*'));
	EXPECT_EQ(false, valid_piece('\\'));
	EXPECT_EQ(false, valid_piece('.'));
	EXPECT_EQ(false, valid_piece(','));
	EXPECT_EQ(false, valid_piece(')'));
	EXPECT_EQ(false, valid_piece('?'));
	EXPECT_EQ(false, valid_piece(';'));
	EXPECT_EQ(false, valid_piece(','));
}

/* Teste para a função de verificar um tabuleiro mínimo para um tabuleiro nulo
   Procedimentos:
   - Chamar a função para um tabuleiro nulo

   Resultados:
   - Espera-se que a função retorne o valor -1 */
TEST(MinimumChessBoard, NULL_Board)
{
	/* Testando para tabuleiro nulo */
	EXPECT_EQ(-1, HaveMinimun(NULL));
}

/* Teste para a função de verificar um tabuleiro mínimo 
   Procedimentos:
   - Chamar a função para um tabuleiro vazio

   Resultados:
   - Espera-se que a função retorne true para um tabuleiro vazio */
TEST(MinimumChessBoard, EmptyBoard)
{
	TBoard* board = AlocateBoard();

	/* Testando para tabuleiro vazio */
	StartEmptyBoard(board);
	EXPECT_EQ(true, HaveMinimun(board));

	free(board);
}

/* Teste para a função de verificar um tabuleiro mínimo
   Procedimentos:
   - Chamar a função para um tabuleiro com um único rei
   - Chamar a função para um tabuleiro com dois reis

   Resultados:
   - Espera-se que a função retorne que os dois tabuleiros são aceitos */
TEST(MinimumChessBoard, BoardWithKings)
{
	TBoard* board = AlocateBoard();

	StartEmptyBoard(board);	/* Iniciando tabuleiro vazio */

	/* Colocando um rei no tabuleiro */
	board->Board[1][5] = B_KING;

	EXPECT_EQ(true, HaveMinimun(board));

	board->Board[6][6] = W_KING; /* Outro rei no tabuleiro */

	EXPECT_EQ(true, HaveMinimun(board));

	free(board);
}

/* Teste para a função de verificar um tabuleiro mínimo
   Procedimentos:
   - Chamar a função para um tabuleiro com uma única peça que não é rei
   - Chamar a função para um tabuleiro com dois reis e um não rei
   - Chamar a função para um tabuleiro com dois reis da mesma cor

   Resultados:
   - Espera-se que a função retorne false para todos os casos listados acima */
TEST(MinimumChessBoard, BoardWithOtherPieces)
{
	TBoard* board = AlocateBoard();

	StartEmptyBoard(board);	/* Tabuleiro vazio */

	board->Board[2][2] = B_QUEEN; /* Uma peça que não é rei */
	EXPECT_EQ(false, HaveMinimun(board));

	/* Mais dois reis de cores diferentes */
	board->Board[1][4] = B_KING;
	board->Board[5][4] = W_KING;
	EXPECT_EQ(false, HaveMinimun(board));

	/* Dois reis da mesma cor */
	board->Board[5][4] = B_KING;
	board->Board[2][2] = BLANK;
	EXPECT_EQ(false, HaveMinimun(board));

	board->Board[5][4] = W_KING;
	board->Board[1][4] = W_KING;
	board->Board[2][2] = BLANK;
	EXPECT_EQ(false, HaveMinimun(board));

	free(board);
}

int main(int argc, char **argv){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
