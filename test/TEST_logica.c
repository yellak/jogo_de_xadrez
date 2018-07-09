#include "gtest/gtest.h"
#include "../include/tabuleiro.h"
#include "../include/logica.h"

/* Teste para verificar se a sintaxe de uma string fornecida pelo usuário está
   correta.
   
   Procedimentos:
   - Verificar sintaxe para notações válidas e inválidas para tipo de peça
     fornecida 
   - Verifica sintaxe para notações válidas e inválidas para o tipo de
     movimento fornecido
   - Verificar validade para casos com letras
   - Verificar validade para casos com números

   Resultados:
   - Esperamos valores true caso a notação esteja correta e false caso esteja
     errada
*/
TEST(Algebraic_verification, Named_movement)
{
	char named_test_move[7];

	/* Notação inválida para tipo de peça */
	strcpy(named_test_move, "Le2-e4");
	EXPECT_EQ(false, verify_syntax_move(named_test_move));

	/* Notação válida para tipo de peça */
	strcpy(named_test_move, "Be2-e4");
	EXPECT_EQ(true, verify_syntax_move(named_test_move));

	/* Notação inválida para tipo de movimento */
	strcpy(named_test_move, "Qa1%a5");
	EXPECT_EQ(false, verify_syntax_move(named_test_move));

	/* Notação válida para tipo de movimento */
	strcpy(named_test_move, "Ba1-a5");
	EXPECT_EQ(true, verify_syntax_move(named_test_move));

	/* Notação inválida para letras */
	strcpy(named_test_move, "RZ5-e4");
	EXPECT_EQ(false, verify_syntax_move(named_test_move));

	/* Notação inválida para letras */
	strcpy(named_test_move, "Ne5-S4");
	EXPECT_EQ(false, verify_syntax_move(named_test_move));

	/* Notação inválida para letras */
	strcpy(named_test_move, "PE5-E4");
	EXPECT_EQ(false, verify_syntax_move(named_test_move));

	/* Notação inválida para números */
	strcpy(named_test_move, "Ke9-e0");
	EXPECT_EQ(false, verify_syntax_move(named_test_move));

	/* Notação inválida para números */
	strcpy(named_test_move, "Ke4-e9");
	EXPECT_EQ(false, verify_syntax_move(named_test_move));

	/* Notação inválida para números */
	strcpy(named_test_move, "Ke9-e9");
	EXPECT_EQ(false, verify_syntax_move(named_test_move));
} /* Named_movement */

/* Teste para verificar a sintaxe da string fornecida pelo usuário no caso dele
   fornecer um roque, ou no caso de verificar quem é o vencedor

   Procedimentos:
   - Verificar sintaxe para quem é o vencedor
   - Verificar para roque pelo lado do rei

   Resultados:
   - true para quando a notação está correta e false para quando a notação está
     errada */
TEST(Algebraic_verification, Castling_or_winner)
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
} /* Castling_or_winner */


/* Teste para verificar a sintaxe dada para roque pelo lado da rainha
   Procedimentos:
   - Verificar uma sintaxe errada de roque pelo lado da rainha
   - Verificar uma sintaxe correta de roque pelo lado da rainha

   Resultados:
   - Retorno true no caso da sintaxe está correta e false caso contrário */
TEST(Algebraic_verification, Queenside_castling)
{
	char movement[6];

	/* Notação válida para roque pelo lado da rainha */
	strcpy(movement, "0-0-0");
	EXPECT_EQ(true, verify_syntax_move(movement));

	/* Notação inválida para roque pelo lado da rainha */
	strcpy(movement, "0-1-0");
	EXPECT_EQ(false, verify_syntax_move(movement));
} /* Queenside_castling */


/* Teste para verificar a sintaxe para notação de empate
   Procedimentos:
   - Verificar a sintaxe para notação de empate

   Resultados:
   - Espera-se true para quando a notação é válida e false caso contrário */
TEST(Algebraic_verification, Draw)
{
	char movement[8];

	/* Notação válida para um empate */
	strcpy(movement, "1/2-1/2");
	EXPECT_EQ(true, verify_syntax_move(movement));

	/* Notação inválida para empate */
	strcpy(movement, "1-1-1-1");
	EXPECT_EQ(false, verify_syntax_move(movement));
} /* Draw */


/* Teste para verificar a validade da função de verificar sintaxe para casos em
   que a peça não é fornecida na notação
 
   Procedimentos:
   - Verificar a validade para casos válidos e não válidos para o tipo de
     movimento
   - Verificar a validade para casos válidos e não válidos para letras na
     notação
   - Verificar a validade para casos válidos e não válidos para números na
     notação

   Resultados:
   - Espera-se resultados positivos quando a notação é válida e negativos
     quando a notação não é válida */
TEST(Algebraic_verification, Unnamed_movement)
{
	char movement[6];

	/* Notação válida para tipo de movimento */
	strcpy(movement, "b1-c3");
	EXPECT_EQ(true, verify_syntax_move(movement));

	/* Notação válida para tipo de movimento */
	strcpy(movement, "b1xc3");
	EXPECT_EQ(true, verify_syntax_move(movement));

	/* Notação inválida para tipo de movimento */
	strcpy(movement, "b1%c3");
	EXPECT_EQ(false, verify_syntax_move(movement));

	/* Notação inválida para tipo de movimento */
	strcpy(movement, "b1pc3");
	EXPECT_EQ(false, verify_syntax_move(movement));

	/* Notação válida para letras no movimento */
	strcpy(movement, "c3-e5");
	EXPECT_EQ(true, verify_syntax_move(movement));

	/* Notação inválida para letras no movimento */
	strcpy(movement, "i2-e7");
	EXPECT_EQ(false, verify_syntax_move(movement));

	/* Notação inválida para letras no movimento */
	strcpy(movement, "h3-j5");
	EXPECT_EQ(false, verify_syntax_move(movement));

	/* Notação inválida para letras no movimento */
	strcpy(movement, "i1-j4");
	EXPECT_EQ(false, verify_syntax_move(movement));

	/* Notação inválida para números no movimento */
	strcpy(movement, "d4-f9");
	EXPECT_EQ(false, verify_syntax_move(movement));

	/* Notação inválida para números no movimento */
	strcpy(movement, "a9-c4");
	EXPECT_EQ(false, verify_syntax_move(movement));

	/* Notação inválida para números no movimento */
	strcpy(movement, "a9-c9");
	EXPECT_EQ(false, verify_syntax_move(movement));
} /* Unnamed_movement */

/* Teste para verificar a validade da função de traduzir um movimento a partir
   da notação algébrica

   Procedimentos:
   - Verificar para movimentos em diagonal
   - Para movimentos de cavalo
   - Movimentos retos

   Resultados:
   - Espera-se que a tradução das linhas e colunas estejam corretas */
TEST(Algebraic_translation, Named_movement)
{
	char named_test_move[7];
	Move* expect_move = (Move*) malloc(sizeof(Move));
	Move* result;

	/* Cavalo da b1 para a3 */
	strcpy(named_test_move, "Nb1-a3");

	/* Sistema de coordenadas da matriz: (y,x) */
	
	/* Movimento esperado: (7,1) para (5,0) */
	expect_move->origin[0] = 7;
	expect_move->origin[1] = 1;
	expect_move->destiny[0] = 5;
	expect_move->destiny[1] = 0;

	/* Chamando a função que retornará o movimento obtido */
	result = algebraic_translate(named_test_move);
	
	/* Realizando os testes */
	EXPECT_EQ(NULL, !result);
	if(result != NULL)
		{
			EXPECT_EQ(expect_move->origin[0], result->origin[0]);
			EXPECT_EQ(expect_move->origin[1], result->origin[1]);
			EXPECT_EQ(expect_move->destiny[0], result->destiny[0]);
			EXPECT_EQ(expect_move->destiny[1], result->destiny[1]);
		}
	/* Liberando para este movimento */
	free(result);

	/*_______________________________________________________________________*/
	
	/* Torre da d7 para d3 */
	strcpy(named_test_move, "Rd7-d3");

	/* Movimento esperado: (1,3) para (5,3) */
	expect_move->origin[0] = 1;
	expect_move->origin[1] = 3;
	expect_move->destiny[0] = 5;
	expect_move->destiny[1] = 3;

	/* Chamando a função que retornará o movimento obtido */
	result = algebraic_translate(named_test_move);

	/* Realizando os testes */
	EXPECT_EQ(NULL, !result);
	if(result != NULL)
		{
			EXPECT_EQ(expect_move->origin[0], result->origin[0]);
			EXPECT_EQ(expect_move->origin[1], result->origin[1]);
			EXPECT_EQ(expect_move->destiny[0], result->destiny[0]);
			EXPECT_EQ(expect_move->destiny[1], result->destiny[1]);
		}
	/* Liberando para este movimento */
	free(result);

	/*_______________________________________________________________________*/

	/* Torre da b5 para g5 */
	strcpy(named_test_move, "Rb5-g5");

	/* Movimento esperado: (3,1) para (3,6) */
	expect_move->origin[0] = 3;
	expect_move->origin[1] = 1;
	expect_move->destiny[0] = 3;
	expect_move->destiny[1] = 6;

	/* Chamando a função que retornará o movimento obtido */
	result = algebraic_translate(named_test_move);

	/* Realizando os testes */
	EXPECT_EQ(NULL, !result);
	if(result != NULL)
		{
			EXPECT_EQ(expect_move->origin[0], result->origin[0]);
			EXPECT_EQ(expect_move->origin[1], result->origin[1]);
			EXPECT_EQ(expect_move->destiny[0], result->destiny[0]);
			EXPECT_EQ(expect_move->destiny[1], result->destiny[1]);
		}
	/* Liberando para este movimento */
	free(result);

	/*_______________________________________________________________________*/

	/* Bispo da b3 para f7 */
	strcpy(named_test_move, "Bb3-f7");

	/* Movimento esperado: (5,1) para (1,5) */
	expect_move->origin[0] = 5;
	expect_move->origin[1] = 1;
	expect_move->destiny[0] = 1;
	expect_move->destiny[1] = 5;

	/* Chamando a função que retornará o movimento obtido */
	result = algebraic_translate(named_test_move);

	/* Realizando os testes */
	EXPECT_EQ(NULL, !result);
	if(result != NULL)
		{
			EXPECT_EQ(expect_move->origin[0], result->origin[0]);
			EXPECT_EQ(expect_move->origin[1], result->origin[1]);
			EXPECT_EQ(expect_move->destiny[0], result->destiny[0]);
			EXPECT_EQ(expect_move->destiny[1], result->destiny[1]);
		}
	/* Liberando para este movimento */
	free(result);

	free(expect_move);
}

/* Teste para verificar a validade da função que traduz os movimentos a partir
   da notação algébrica, dessa vez para casos em que o nome da peça não é dado

   Os procedimentos e resultados são os mesmos que os do teste anterior */
TEST(Algebraic_translation, Unnamed_movement)
{
	char movement[6];
	Move* expect_move = (Move*) malloc(sizeof(Move));
	Move* result;
	
	/* g2 para c6 */
	strcpy(movement, "g2-c6");

	/* Movimento esperado: (2,2) para (6,6) */
	expect_move->origin[0] = 6;
	expect_move->origin[1] = 6;
	expect_move->destiny[0] = 2;
	expect_move->destiny[1] = 2;

	/* Chamando a função que retornará o movimento obtido */
	result = algebraic_translate(movement);

	/* Realizando os testes */
	EXPECT_EQ(NULL, !result);
	if(result != NULL)
		{
			EXPECT_EQ(expect_move->origin[0], result->origin[0]);
			EXPECT_EQ(expect_move->origin[1], result->origin[1]);
			EXPECT_EQ(expect_move->destiny[0], result->destiny[0]);
			EXPECT_EQ(expect_move->destiny[1], result->destiny[1]);
		}
	/* Liberando para este movimento */
	free(result);

	/*_______________________________________________________________________*/

	/* d5 para e3 */
	strcpy(movement, "e3-d5");

	/* Movimento esperado: (5,4) para (3,3) */
	expect_move->origin[0] = 5;
	expect_move->origin[1] = 4;
	expect_move->destiny[0] = 3;
	expect_move->destiny[1] = 3;

	/* Chamando a função que retornará o movimento obtido */
	result = algebraic_translate(movement);

	/* Realizando os testes */
	EXPECT_EQ(NULL, !result);
	if(result != NULL)
		{
			EXPECT_EQ(expect_move->origin[0], result->origin[0]);
			EXPECT_EQ(expect_move->origin[1], result->origin[1]);
			EXPECT_EQ(expect_move->destiny[0], result->destiny[0]);
			EXPECT_EQ(expect_move->destiny[1], result->destiny[1]);
		}
	/* Liberando para este movimento */
	free(result);

	/*_______________________________________________________________________*/

	/* f8 para f1 */
	strcpy(movement, "f8-f1");

	/* Movimento esperado: (7,5) para (0,5) */
	expect_move->origin[0] = 0;
	expect_move->origin[1] = 5;
	expect_move->destiny[0] = 7;
	expect_move->destiny[1] = 5;

	/* Chamando a função que retornará o movimento obtido */
	result = algebraic_translate(movement);

	/* Realizando os testes */
	EXPECT_EQ(NULL, !result);
	if(result != NULL)
		{
			EXPECT_EQ(expect_move->origin[0], result->origin[0]);
			EXPECT_EQ(expect_move->origin[1], result->origin[1]);
			EXPECT_EQ(expect_move->destiny[0], result->destiny[0]);
			EXPECT_EQ(expect_move->destiny[1], result->destiny[1]);
		}
	/* Liberando para este movimento */
	free(result);

	free(expect_move);
}

/* Testes para verificar o retorno da função de movimento do peão branco para parametros nulos.
   Procedimentos:
   -Criar um tabuleiro nulo e um não nulo.
   -Criar uma lista de movimentos nula e uma não nula.
   -Chamar função para tabuleiro nulo e lista não nula.
   -Chamar a função para tabuleiro não nulo e lista nula.
   Resultados:
   -É esperado que a função retorne NULL para ambos os casos.
*/
TEST(Test_WhitePawnMovements, Verify_NULL_Variables){
	TBoard* board_null = NULL;
	TBoard* board = AlocateBoard();
	ListOfMoves* list_null = NULL;
	ListOfMoves* list = CreateListOfMoves();

	/* Testa para o primeiro parametro nulo e o segundo não */
	EXPECT_EQ(NULL, WhitePawnMovements(board_null, list, 1, 2));
	/* Testa para o segundo parametro nulo e o primeiro não */
	EXPECT_EQ(NULL, WhitePawnMovements(board, list_null, 1, 2));

	DeleteListOfMoves(list);
	free(board);
}

/* Testes para verificar o retorno da função de movimento do peão preto para parametros nulos.
   Procedimentos:
   -Criar um tabuleiro nulo e um não nulo.
   -Criar uma lista de movimentos nula e uma não nula.
   -Chamar função para tabuleiro nulo e lista não nula.
   -Chamar a função para tabuleiro não nulo e lista nula.
   Resultados:
   -É esperado que a função retorne NULL para ambos os casos.
*/
TEST(Test_BlackPawnMovements, Verify_NULL_Variables){
	TBoard* board_null = NULL;
	TBoard* board = AlocateBoard();
	ListOfMoves* list_null = NULL;
	ListOfMoves* list = CreateListOfMoves();

	/* Testa para o primeiro parametro nulo e o segundo não */
	EXPECT_EQ(NULL, BlackPawnMovements(board_null, list, 1, 2));
	/* Testa para o segundo parametro nulo e o primeiro não */
	EXPECT_EQ(NULL, BlackPawnMovements(board, list_null, 1, 2));

	DeleteListOfMoves(list);
	free(board);
}

/* Testes para verificar o retorno da função de movimento do cavalo para parametros nulos.
   Procedimentos:
   -Criar um tabuleiro nulo e um não nulo.
   -Criar uma lista de movimentos nula e uma não nula.
   -Chamar função para tabuleiro nulo e lista não nula.
   -Chamar a função para tabuleiro não nulo e lista nula.
   Resultados:
   -É esperado que a função retorne NULL para ambos os casos.
*/
TEST(Test_HorseMovements, Verify_NULL_Variables){
	TBoard* board_null = NULL;
	TBoard* board = AlocateBoard();
	ListOfMoves* list_null = NULL;
	ListOfMoves* list = CreateListOfMoves();

	/* Testa para o primeiro parametro nulo e o segundo não */
	EXPECT_EQ(NULL, HorseMovements(board_null, list, 1, 2));
	/* Testa para o segundo parametro nulo e o primeiro não */
	EXPECT_EQ(NULL, HorseMovements(board, list_null, 1, 2));

	DeleteListOfMoves(list);
	free(board);
}

/* Testes para verificar o retorno da função de movimento da torre para parametros nulos.
   Procedimentos:
   -Criar um tabuleiro nulo e um não nulo.
   -Criar uma lista de movimentos nula e uma não nula.
   -Chamar função para tabuleiro nulo e lista não nula.
   -Chamar a função para tabuleiro não nulo e lista nula.
   Resultados:
   -É esperado que a função retorne NULL para ambos os casos.
*/
TEST(Test_TowerMovements, Verify_NULL_Variables){
	TBoard* board_null = NULL;
	TBoard* board = AlocateBoard();
	ListOfMoves* list_null = NULL;
	ListOfMoves* list = CreateListOfMoves();

	/* Testa para o primeiro parametro nulo e o segundo não */
	EXPECT_EQ(NULL, TowerMovements(board_null, list, 1, 2));
	/* Testa para o segundo parametro nulo e o primeiro não */
	EXPECT_EQ(NULL, TowerMovements(board, list_null, 1, 2));

	DeleteListOfMoves(list);
	free(board);
}

/* Testes para verificar o retorno da função de movimento do bispo para parametros nulos.
   Procedimentos:
   -Criar um tabuleiro nulo e um não nulo.
   -Criar uma lista de movimentos nula e uma não nula.
   -Chamar função para tabuleiro nulo e lista não nula.
   -Chamar a função para tabuleiro não nulo e lista nula.
   Resultados:
   -É esperado que a função retorne NULL para ambos os casos.
*/
TEST(Test_BishopMovements, Verify_NULL_Variables){
	TBoard* board_null = NULL;
	TBoard* board = AlocateBoard();
	ListOfMoves* list_null = NULL;
	ListOfMoves* list = CreateListOfMoves();

	/* Testa para o primeiro parametro nulo e o segundo não */
	EXPECT_EQ(NULL, BishopMovements(board_null, list, 1, 2));
	/* Testa para o segundo parametro nulo e o primeiro não */
	EXPECT_EQ(NULL, BishopMovements(board, list_null, 1, 2));

	DeleteListOfMoves(list);
	free(board);
}

/* Testes para verificar o retorno da função de movimento da rainha para parametros nulos.
   Procedimentos:
   -Criar um tabuleiro nulo e um não nulo.
   -Criar uma lista de movimentos nula e uma não nula.
   -Chamar função para tabuleiro nulo e lista não nula.
   -Chamar a função para tabuleiro não nulo e lista nula.
   Resultados:
   -É esperado que a função retorne NULL para ambos os casos.
*/
TEST(Test_QueenMovements, Verify_NULL_Variables){
	TBoard* board_null = NULL;
	TBoard* board = AlocateBoard();
	ListOfMoves* list_null = NULL;
	ListOfMoves* list = CreateListOfMoves();

	/* Testa para o primeiro parametro nulo e o segundo não */
	EXPECT_EQ(NULL, QueenMovements(board_null, list, 1, 2));
	/* Testa para o segundo parametro nulo e o primeiro não */
	EXPECT_EQ(NULL, QueenMovements(board, list_null, 1, 2));

	DeleteListOfMoves(list);
	free(board);
}
/* Testes para verificar o retorno da função de movimento do rei para parametros nulos.
   Procedimentos:
   -Criar um tabuleiro nulo e um não nulo.
   -Criar uma lista de movimentos nula e uma não nula.
   -Chamar função para tabuleiro nulo e lista não nula.
   -Chamar a função para tabuleiro não nulo e lista nula.
   Resultados:
   -É esperado que a função retorne NULL para ambos os casos.
*/
TEST(Test_KingMovements, Verify_NULL_Variables){
	TBoard* board_null = NULL;
	TBoard* board = AlocateBoard();
	ListOfMoves* list_null = NULL;
	ListOfMoves* list = CreateListOfMoves();

	/* Testa para o primeiro parametro nulo e o segundo não */
	EXPECT_EQ(NULL, KingMovements(board_null, list, 1, 2));
	/* Testa para o segundo parametro nulo e o primeiro não */
	EXPECT_EQ(NULL, KingMovements(board, list_null, 1, 2));

	DeleteListOfMoves(list);
	free(board);
}

/* Teste para verificar a função de movimento do peão branco para um tabuleiro vazio.
   Procedimentos:
   -Criar um tabuleiro e uma lista de movimentos vazios.
   -Inserir um peão branco na posição (6,5) e em (4,4) no tabuleiro.
   -Chamar a função para essa posição.
   Resultados:
   -É esperado que a lista de movimentos retornada possua 2/1 movimentos.
*/
TEST(Test_WhitePawnMovements, Verify_Movements_EmptyBoard){
	ListOfMoves* AllPlays = CreateListOfMoves();
	ListOfMoves* AllPlays2 = CreateListOfMoves();	
	TBoard* board = AlocateBoard();
	StartEmptyBoard(board);
	board->Board[6][5] = W_PAWN;

	WhitePawnMovements(board, AllPlays, 6, 5);
	EXPECT_EQ(2, AllPlays->howmany);

	board->Board[4][4] = W_PAWN;
	WhitePawnMovements(board, AllPlays2, 4, 4);
	EXPECT_EQ(1, AllPlays2->howmany);

	DeleteListOfMoves(AllPlays);
	DeleteListOfMoves(AllPlays2);
	free(board);
}

/* Teste para verificar a função de movimento do peão preto para um tabuleiro vazio.
   Procedimentos:
   -Criar um tabuleiro e uma lista de movimentos vazios.
   -Inserir um peão branco na posição (1,5) e em (4,4) no tabuleiro.
   -Chamar a função para essa posição.
   Resultados:
   -É esperado que a lista de movimentos retornada possua 2/1 movimentos.
*/
TEST(Test_BlackPawnMovements, Verify_Movements_EmptyBoard){
	ListOfMoves* AllPlays = CreateListOfMoves();
	ListOfMoves* AllPlays2 = CreateListOfMoves();	
	TBoard* board = AlocateBoard();
	StartEmptyBoard(board);
	board->Board[1][5] = B_PAWN;

	BlackPawnMovements(board, AllPlays, 1, 5);
	EXPECT_EQ(2, AllPlays->howmany);

	board->Board[4][4] = B_PAWN;
	BlackPawnMovements(board, AllPlays2, 4, 4);
	EXPECT_EQ(1, AllPlays2->howmany);

	DeleteListOfMoves(AllPlays);
	DeleteListOfMoves(AllPlays2);
	free(board);
}

/* Teste para verificar a função de movimento do cavalo para um tabuleiro vazio.
   Procedimentos:
   -Criar um tabuleiro e uma lista de movimentos vazios.
   -Inserir um peão branco na posição (4,4) no tabuleiro.
   -Chamar a função para essa posição.
   Resultados:
   -É esperado que a lista de movimentos retornada possua 8 movimentos.
*/
TEST(Test_HorseMovements, Verify_Movements_EmptyBoard){
	ListOfMoves* AllPlays = CreateListOfMoves();
	ListOfMoves* AllPlays2 = CreateListOfMoves();	
	TBoard* board = AlocateBoard();
	StartEmptyBoard(board);
	board->Board[4][4] = W_HORSE;

	HorseMovements(board, AllPlays, 4, 4);
	EXPECT_EQ(8, AllPlays->howmany);

	board->Board[4][4] = B_HORSE;
	HorseMovements(board, AllPlays2, 4, 4);
	EXPECT_EQ(8, AllPlays2->howmany);

	DeleteListOfMoves(AllPlays);
	DeleteListOfMoves(AllPlays2);
	free(board);
}

/* Teste para verificar a função de movimento da torre para um tabuleiro vazio.
   Procedimentos:
   -Criar um tabuleiro e uma lista de movimentos vazios.
   -Inserir uma torre na posição (4,4) no tabuleiro.
   -Chamar a função para essa posição.
   Resultados:
   -É esperado que a lista de movimentos retornada possua 14 movimentos.
*/
TEST(Test_TowerMovements, Verify_Movements_EmptyBoard){
	ListOfMoves* AllPlays = CreateListOfMoves();
	ListOfMoves* AllPlays2 = CreateListOfMoves();	
	TBoard* board = AlocateBoard();
	StartEmptyBoard(board);
	board->Board[4][4] = W_TOWER;

	TowerMovements(board, AllPlays, 4, 4);
	EXPECT_EQ(14, AllPlays->howmany);

	board->Board[4][4] = B_TOWER;
	TowerMovements(board, AllPlays2, 4, 4);
	EXPECT_EQ(14, AllPlays2->howmany);

	DeleteListOfMoves(AllPlays);
	DeleteListOfMoves(AllPlays2);
	free(board);
}

/* Teste para verificar a função de movimento do bispo para um tabuleiro vazio.
   Procedimentos:
   -Criar um tabuleiro e uma lista de movimentos vazios.
   -Inserir um bispo na posição (4,4) no tabuleiro.
   -Chamar a função para essa posição.
   Resultados:
   -É esperado que a lista de movimentos retornada possua 13 movimentos.
*/

TEST(Test_BishopMovements, Verify_Movements_EmptyBoard){
	ListOfMoves* AllPlays = CreateListOfMoves();
	ListOfMoves* AllPlays2 = CreateListOfMoves();	
	TBoard* board = AlocateBoard();
	StartEmptyBoard(board);
	board->Board[4][4] = W_BISHOP;

	BishopMovements(board, AllPlays, 4, 4);
	EXPECT_EQ(13, AllPlays->howmany);

	board->Board[4][4] = B_BISHOP;
	BishopMovements(board, AllPlays2, 4, 4);
	EXPECT_EQ(13, AllPlays2->howmany);

	DeleteListOfMoves(AllPlays);
	DeleteListOfMoves(AllPlays2);
	free(board);
}

/* Teste para verificar a função de movimento da rainha para um tabuleiro vazio.
   Procedimentos:
   -Criar um tabuleiro e uma lista de movimentos vazios.
   -Inserir uma rainha na posição (4,4) no tabuleiro.
   -Chamar a função para essa posição.
   Resultados:
   -É esperado que a lista de movimentos retornada possua 27 movimentos.
*/

TEST(Test_QueenMovements, Verify_Movements_EmptyBoard){
	ListOfMoves* AllPlays = CreateListOfMoves();
	ListOfMoves* AllPlays2 = CreateListOfMoves();	
	TBoard* board = AlocateBoard();
	StartEmptyBoard(board);
	board->Board[4][4] = W_QUEEN;

	QueenMovements(board, AllPlays, 4, 4);
	EXPECT_EQ(27, AllPlays->howmany);

	board->Board[4][4] = B_QUEEN;
	QueenMovements(board, AllPlays2, 4, 4);
	EXPECT_EQ(27, AllPlays2->howmany);

	DeleteListOfMoves(AllPlays);
	DeleteListOfMoves(AllPlays2);
	free(board);
}

/* Teste para verificar a função de movimento do rei para um tabuleiro vazio.
   Procedimentos:
   -Criar um tabuleiro e uma lista de movimentos vazios.
   -Inserir um rei na posição (4,4) no tabuleiro.
   -Chamar a função para essa posição.
   Resultados:
   -É esperado que a lista de movimentos retornada possua 13 movimentos.
*/

TEST(Test_KingMovements, Verify_Movements_EmptyBoard){
	ListOfMoves* AllPlays = CreateListOfMoves();
	ListOfMoves* AllPlays2 = CreateListOfMoves();	
	TBoard* board = AlocateBoard();
	StartEmptyBoard(board);
	board->Board[4][4] = W_KING;

	KingMovements(board, AllPlays, 4, 4);
	EXPECT_EQ(8, AllPlays->howmany);

	board->Board[4][4] = B_KING;
	KingMovements(board, AllPlays2, 4, 4);
	EXPECT_EQ(8, AllPlays2->howmany);

	DeleteListOfMoves(AllPlays);
	DeleteListOfMoves(AllPlays2);
	free(board);
}

/* Teste para verificar a função de movimento do peão branco na diferenciação de peças aliadas
e oponentes.
   Procedimentos:
   -Criar um tabuleiro e uma lista de movimentos vazios.
   -Inserir um peão branco na posição (4,4) no tabuleiro.
   -Inserir peças da mesma cor nas posições para onde o pẽao poderia se mover.
   -Chamar a função para a posição do peão branco.
   -Inserir peças de cor diferente nas posições para onde o peão poderia se mover.
   -Chamar a funça para a posição do peão branco.
   Resultados:
   -É esperado que a primeira chamada da função retorne uma lista de movimentos com 0 movimentos.
   -É esperado que a segunda chamada da função retorne uma lista de movimentos com 3 movimentos.
*/
TEST(Test_WhitePawnMovements, Verify_Movements_RivalPieces){
	ListOfMoves* AllPlays = CreateListOfMoves();
	ListOfMoves* AllPlays2 = CreateListOfMoves();	
	TBoard* board = AlocateBoard();
	StartEmptyBoard(board);
	board->Board[4][4] = W_PAWN;

	
	board->Board[3][5] = W_HORSE;
	board->Board[3][3] = W_BISHOP;
	board->Board[5][5] = W_PAWN;
	board->Board[5][3] = W_TOWER;

	WhitePawnMovements(board, AllPlays, 4, 4);
	EXPECT_EQ(1, AllPlays->howmany);

	board->Board[3][5] = B_HORSE;
	board->Board[3][3] = B_BISHOP;
	board->Board[5][5] = B_PAWN;
	board->Board[5][3] = B_TOWER;

	WhitePawnMovements(board, AllPlays2, 4, 4);
	EXPECT_EQ(3, AllPlays2->howmany);

	free(board);
	DeleteListOfMoves(AllPlays2);
	DeleteListOfMoves(AllPlays);
}

/* Teste para verificar a função de movimento do peão preto na diferenciação de peças aliadas
e oponentes.
   Procedimentos:
   -Criar um tabuleiro e uma lista de movimentos vazios.
   -Inserir um peão preto na posição (4,4) no tabuleiro.
   -Inserir peças da mesma cor nas posições para onde o pẽao poderia se mover.
   -Chamar a função para a posição do peão preto.
   -Inserir peças de cor diferente nas posições para onde o peão poderia se mover.
   -Chamar a funça para a posição do peão preto.
   Resultados:
   -É esperado que a primeira chamada da função retorne uma lista de movimentos com 0 movimentos.
   -É esperado que a segunda chamada da função retorne uma lista de movimentos com 3 movimentos.
*/
TEST(Test_BlackPawnMovements, Verify_Movements_RivalPieces){
	ListOfMoves* AllPlays = CreateListOfMoves();
	ListOfMoves* AllPlays2 = CreateListOfMoves();	
	TBoard* board = AlocateBoard();
	StartEmptyBoard(board);
	board->Board[4][4] = B_PAWN;

	
	board->Board[3][5] = B_HORSE;
	board->Board[3][3] = B_BISHOP;
	board->Board[5][5] = B_PAWN;
	board->Board[5][3] = B_TOWER;

	BlackPawnMovements(board, AllPlays, 4, 4);
	EXPECT_EQ(1, AllPlays->howmany);

	board->Board[3][5] = W_HORSE;
	board->Board[3][3] = W_BISHOP;
	board->Board[5][5] = W_PAWN;
	board->Board[5][3] = W_TOWER;

	BlackPawnMovements(board, AllPlays2, 4, 4);
	EXPECT_EQ(3, AllPlays2->howmany);

	DeleteListOfMoves(AllPlays2);
	DeleteListOfMoves(AllPlays);
	free(board);
}

/* Teste para verificar a função de movimento do cavalo na diferenciação de peças aliadas
e oponentes.
   Procedimentos:
   -Criar um tabuleiro e uma lista de movimentos vazios.
   -Inserir uma cavalo na posição (4,4) no tabuleiro.
   -Inserir peças da mesma cor nas posições para onde a cavalo poderia se mover.
   -Chamar a função para a posição do cavalo.
   -Inserir peças de cor diferente nas posições para onde a torre poderia se mover.
   -Chamar a funça para a posição do cavalo.
   Resultados:
   -É esperado que a primeira chamada da função retorne uma lista de movimentos com 0 movimentos.
   -É esperado que a segunda chamada da função retorne uma lista de movimentos com 8 movimentos.
*/
TEST(Test_HorseMovements, Verify_Movements_RivalPieces){
	ListOfMoves* AllPlays = CreateListOfMoves();
	ListOfMoves* AllPlays2 = CreateListOfMoves();	
	TBoard* board = AlocateBoard();
	StartEmptyBoard(board);
	board->Board[4][4] = W_HORSE;

	
	board->Board[3][2] = W_HORSE;
	board->Board[2][3] = W_PAWN;
	board->Board[2][5] = W_BISHOP;
	board->Board[5][2] = W_PAWN;
	board->Board[3][6] = W_TOWER;
	board->Board[6][3] = W_PAWN;
	board->Board[6][5] = W_PAWN;
	board->Board[5][6] = W_PAWN;

	HorseMovements(board, AllPlays, 4, 4);
	EXPECT_EQ(0, AllPlays->howmany);

	board->Board[4][4] = B_HORSE;

	HorseMovements(board, AllPlays2, 4, 4);
	EXPECT_EQ(8, AllPlays2->howmany);

	DeleteListOfMoves(AllPlays2);
	DeleteListOfMoves(AllPlays);
	free(board);
}

/* Teste para verificar a função de movimento da torre na diferenciação de peças aliadas
e oponentes.
   Procedimentos:
   -Criar um tabuleiro e uma lista de movimentos vazios.
   -Inserir uma torre na posição (4,4) no tabuleiro.
   -Inserir peças da mesma cor nas posições para onde a torre poderia se mover.
   -Chamar a função para a posição da torre.
   -Inserir peças de cor diferente nas posições para onde a torre poderia se mover.
   -Chamar a funça para a posição da torre.
   Resultados:
   -É esperado que a primeira chamada da função retorne uma lista de movimentos com 0 movimentos.
   -É esperado que a segunda chamada da função retorne uma lista de movimentos com 4 movimentos.
*/

TEST(Test_TowerMovements, Verify_Movements_RivalPieces){
	ListOfMoves* AllPlays = CreateListOfMoves();
	ListOfMoves* AllPlays2 = CreateListOfMoves();	
	TBoard* board = AlocateBoard();
	StartEmptyBoard(board);
	board->Board[4][4] = W_TOWER;

	
	board->Board[5][4] = W_HORSE;
	board->Board[3][4] = W_PAWN;
	board->Board[4][5] = W_BISHOP;
	board->Board[4][3] = W_TOWER;

	TowerMovements(board, AllPlays, 4, 4);
	EXPECT_EQ(0, AllPlays->howmany);

	board->Board[5][4] = B_HORSE;
	board->Board[3][4] = B_PAWN;
	board->Board[4][5] = B_BISHOP;
	board->Board[4][3] = B_TOWER;
	TowerMovements(board, AllPlays2, 4, 4);
	EXPECT_EQ(4, AllPlays2->howmany);

	DeleteListOfMoves(AllPlays2);
	DeleteListOfMoves(AllPlays);
	free(board);
}


/* Teste para verificar a função de movimento do bispo na diferenciação de peças aliadas
e oponentes.
   Procedimentos:
   -Criar um tabuleiro e uma lista de movimentos vazios.
   -Inserir um bispo na posição (4,4) no tabuleiro.
   -Inserir peças da mesma cor nas posições para onde o bispo poderia se mover.
   -Chamar a função para a posição do bispo.
   -Inserir peças de cor diferente nas posições para onde o bispo poderia se mover.
   -Chamar a funça para a posição do bispo.
   Resultados:
   -É esperado que a primeira chamada da função retorne uma lista de movimentos com 0 movimentos.
   -É esperado que a segunda chamada da função retorne uma lista de movimentos com 4 movimentos.
*/
TEST(Test_BishopMovements, Verify_Movements_RivalPieces){
	ListOfMoves* AllPlays = CreateListOfMoves();
	ListOfMoves* AllPlays2 = CreateListOfMoves();	
	TBoard* board = AlocateBoard();
	StartEmptyBoard(board);
	board->Board[4][4] = W_BISHOP;
	
	board->Board[3][3] = W_HORSE;
	board->Board[3][5] = W_PAWN;
	board->Board[5][3] = W_PAWN;
	board->Board[5][5] = W_TOWER;

	BishopMovements(board, AllPlays, 4, 4);
	EXPECT_EQ(0, AllPlays->howmany);

	board->Board[3][3] = B_HORSE;
	board->Board[3][5] = B_PAWN;
	board->Board[5][3] = B_BISHOP;
	board->Board[5][5] = B_TOWER;
	BishopMovements(board, AllPlays2, 4, 4);
	EXPECT_EQ(4, AllPlays2->howmany);

	DeleteListOfMoves(AllPlays2);
	DeleteListOfMoves(AllPlays);
	free(board);
}


/* Teste para verificar a função de movimento da rainha na diferenciação de peças aliadas
e oponentes.
   Procedimentos:
   -Criar um tabuleiro e uma lista de movimentos vazios.
   -Inserir uma rainha na posição (4,4) no tabuleiro.
   -Inserir peças da mesma cor nas posições para onde a rainha poderia se mover.
   -Chamar a função para a posição da rainha.
   -Inserir peças de cor diferente nas posições para onde a rainha poderia se mover.
   -Chamar a funça para a posição da rainha.
   Resultados:
   -É esperado que a primeira chamada da função retorne uma lista de movimentos com 0 movimentos.
   -É esperado que a segunda chamada da função retorne uma lista de movimentos com 8 movimentos.
*/
TEST(Test_QueenMovements, Verify_Movements_RivalPieces){
	ListOfMoves* AllPlays = CreateListOfMoves();
	ListOfMoves* AllPlays2 = CreateListOfMoves();	
	TBoard* board = AlocateBoard();
	StartEmptyBoard(board);
	board->Board[4][4] = W_QUEEN;
	
	board->Board[3][3] = W_HORSE;
	board->Board[3][5] = W_PAWN;
	board->Board[5][3] = W_PAWN;
	board->Board[5][5] = W_TOWER;
	board->Board[5][4] = W_HORSE;
	board->Board[3][4] = W_PAWN;
	board->Board[4][5] = W_BISHOP;
	board->Board[4][3] = W_TOWER;

	QueenMovements(board, AllPlays, 4, 4);
	EXPECT_EQ(0, AllPlays->howmany);

	board->Board[3][3] = B_HORSE;
	board->Board[3][5] = B_PAWN;
	board->Board[5][3] = B_BISHOP;
	board->Board[5][5] = B_TOWER;
	board->Board[5][4] = B_HORSE;
	board->Board[3][4] = B_PAWN;
	board->Board[4][5] = B_BISHOP;
	board->Board[4][3] = B_TOWER;
	QueenMovements(board, AllPlays2, 4, 4);
	EXPECT_EQ(8, AllPlays2->howmany);

	free(board);
	DeleteListOfMoves(AllPlays2);
	DeleteListOfMoves(AllPlays);
}

/* Teste para verificar a função de movimento do rei na diferenciação de peças aliadas
e oponentes.
   Procedimentos:
   -Criar um tabuleiro e uma lista de movimentos vazios.
   -Inserir um rei na posição (4,4) no tabuleiro.
   -Inserir peças da mesma cor nas posições para onde o rei poderia se mover.
   -Chamar a função para a posição do rei.
   -Inserir peças de cor diferente nas posições para onde o rei poderia se mover.
   -Chamar a funça para a posição do rei.
   Resultados:
   -É esperado que a primeira chamada da função retorne uma lista de movimentos com 0 movimentos.
   -É esperado que a segunda chamada da função retorne uma lista de movimentos com 8 movimentos.
*/

TEST(Test_KingMovements, Verify_Movements_RivalPieces){
	ListOfMoves* AllPlays = CreateListOfMoves();
	ListOfMoves* AllPlays2 = CreateListOfMoves();	
	TBoard* board = AlocateBoard();
	StartEmptyBoard(board);
	board->Board[4][4] = W_KING;
	
	board->Board[3][3] = W_HORSE;
	board->Board[3][5] = W_PAWN;
	board->Board[5][3] = W_PAWN;
	board->Board[5][5] = W_TOWER;
	board->Board[5][4] = W_HORSE;
	board->Board[3][4] = W_PAWN;
	board->Board[4][5] = W_BISHOP;
	board->Board[4][3] = W_TOWER;

	KingMovements(board, AllPlays, 4, 4);
	EXPECT_EQ(0, AllPlays->howmany);

	board->Board[3][3] = B_HORSE;
	board->Board[3][5] = B_PAWN;
	board->Board[5][3] = B_BISHOP;
	board->Board[5][5] = B_TOWER;
	board->Board[5][4] = B_HORSE;
	board->Board[3][4] = B_PAWN;
	board->Board[4][5] = B_BISHOP;
	board->Board[4][3] = B_TOWER;

	KingMovements(board, AllPlays2, 4, 4);
	EXPECT_EQ(8, AllPlays2->howmany);

	DeleteListOfMoves(AllPlays2);
	DeleteListOfMoves(AllPlays);
	free(board);
}

 /* Testa o adição do movimento de roque */
/* Teste para verificar a adição dos movimentos de roque na função de movimentos do rei..
   Procedimentos:
   -Criar um tabuleiro e uma lista de movimentos vazios.
   -Inserir um rei no tabuleiro na sua posição inicial de um jogo de xadrez.
   -Inserir torres da mesma cor do rei em um tabuleiro nas suas posições iniciais de um jogo de xadrez.
   -Chamar a funça para a posição do rei.
   Resultados:
   -É esperado que a função retorne uma lista de movimentos com 7 movimentos.
*/

TEST(Test_KingMovements, Verify_Addict_Roque_Movement){
 	ListOfMoves* AllPlays = CreateListOfMoves();
 	ListOfMoves* AllPlays2 = CreateListOfMoves();	
 	TBoard* board = AlocateBoard();
 	TBoard* board2 = AlocateBoard();
 	StartEmptyBoard(board);
 	StartEmptyBoard(board2);
 	board->Board[0][4] = B_KING;
 	board->Board[0][0] = B_TOWER;
 	board->Board[0][7] = B_TOWER;

 	KingMovements(board, AllPlays, 0, 4);
 	EXPECT_EQ(7, AllPlays->howmany);

 	board2->Board[7][4] = W_KING;
 	board2->Board[7][0] = W_TOWER;
 	board2->Board[7][7] = W_TOWER;

 	KingMovements(board2, AllPlays2, 7, 4);
 	EXPECT_EQ(7, AllPlays2->howmany);

 	DeleteListOfMoves(AllPlays2);
 	DeleteListOfMoves(AllPlays);
 	free(board);
 	free(board2);
}

/* Teste para verificar a função que calcula todos os movimentos possíveis funciona corretamente com um
tabuleiro nulo.
   Procedimentos:
   -Criar um tabuleiro do tipo nulo.
   Resultados:
   -É esperado que o retorno da função seja um ponteiro NULL indicando sucesso.
*/
TEST(Test_AllMovements, Verify_NULL_Board){
	TBoard* board_null = NULL;

	/* Testa para os movimentos referentes as peças brancas */
	EXPECT_EQ(NULL, AnalyzePossibleMovementsWhite(board_null));
	/* Testa para os movimentos referentes as peças pretas */
	EXPECT_EQ(NULL, AnalyzePossibleMovementsBlack(board_null));
}

/* Teste para verificar a função que calcula todos os movimentos possíveis funciona corretamente com um
tabuleiro vazio.
   Procedimentos:
   -Criar um tabuleiro vazio.
   Resultados:
   -É esperado que o retorno da função seja um inteiro indicando sucesso.
*/
TEST(Test_AllMovements, Verify_Movements_EmptyBoard){
	TBoard* board = AlocateBoard();
	StartEmptyBoard(board);
	ListOfMoves* AllPlays = AnalyzePossibleMovementsWhite(board);

	/* Testa para os movimentos referentes as peças brancas */
	EXPECT_EQ(0, AllPlays->howmany);
	DeleteListOfMoves(AllPlays);
	AllPlays = AnalyzePossibleMovementsBlack(board);

	/* Testa para os movimentos referentes as peças pretas */
	EXPECT_EQ(0, AllPlays->howmany);

	DeleteListOfMoves(AllPlays);
	free(board);
}

/* Teste para verificar a função que calcula todos os movimentos possíveis funciona corretamente com um
tabuleiro padrão.
   Procedimentos:
   -Criar um tabuleiro do tipo padrão.
   Resultados:
   -É esperado que o retorno da função seja um inteiro indicando sucesso.
*/
TEST(Test_AllMovements, Verify_Movements_StandardBoard){
	TBoard* board = AlocateBoard();
	StartStandardBoard(board);
	ListOfMoves* AllPlays = AnalyzePossibleMovementsWhite(board);

	/* Testa para os movimentos referentes as peças brancas */
	EXPECT_EQ(20, AllPlays->howmany);
	DeleteListOfMoves(AllPlays);
	AllPlays = AnalyzePossibleMovementsBlack(board);

	/* Testa para os movimentos referentes as peças pretas */
	EXPECT_EQ(20, AllPlays->howmany);

	DeleteListOfMoves(AllPlays);
	free(board);
}
/* Teste para verificar a função de verificar movimento para entradas inválidas
   Procedimento:
   	-Criar um tabuleiro vazio.
   	-Chamar função que inicia o tabuleiro vazio;
    -Chamar a função de verificar se um movimento é válido para um tabuleiro nulo.
    -Chamar a função de verificar se um movimento é valido para um tabuleiro alocado,
    mas para coordenadas em que não exista uma peça.
   Resultados:
	-É esperado quem em ambos os casos retorne -1.
 */
TEST(Test_VerifyValidMovement,  Veirfy_Invalid_Entries){
	TBoard* board1 = NULL;
	TBoard* board2 = AlocateBoard();
	StartStandardBoard(board2);

	/* Testa para tabuleiro nulo */
	EXPECT_EQ(-1, VerifyValidMovement(board1, 4, 4, 5, 4));
	/* Testa para tabuleiro válido e coordenadas inválidas (sem peça) */
	EXPECT_EQ(-1, VerifyValidMovement(board2, 4, 4, 5, 4));
	free(board2);
	
}

/* Teste para verificar a função de verificar movimento para movimentos válidos
   Procedimento:
   	-Criar um tabuleiro vazio.
   	-Preencher com uma peça de cada tipo.
    -Chamar a função de verificar movimento para movimentos válidos para cada peça.
   Resultados:
	-É esperado quem em todos os casos, para brancas e pretas, retorne 1.
 */

TEST(Test_VerifyValidMovement, Verify_Valid_Movements){
	TBoard* board = AlocateBoard();
	StartEmptyBoard(board);
	board->Board[0][0] = B_PAWN;
	board->Board[0][1] = B_TOWER;
	board->Board[0][2] = B_BISHOP;
	board->Board[0][4] = B_KING;
	board->Board[0][5] = B_QUEEN;
	board->Board[0][6] = B_HORSE;

	EXPECT_EQ(1, VerifyValidMovement(board, 0, 0, 1, 0));
	EXPECT_EQ(1, VerifyValidMovement(board, 0, 1, 1, 1));
	EXPECT_EQ(1, VerifyValidMovement(board, 0, 2, 1, 3));
	EXPECT_EQ(1, VerifyValidMovement(board, 0, 4, 1, 4));
	EXPECT_EQ(1, VerifyValidMovement(board, 0, 5, 1, 5));
	EXPECT_EQ(1, VerifyValidMovement(board, 0, 6, 2, 7));


	board->Board[7][0] = W_PAWN;
	board->Board[7][1] = W_TOWER;
	board->Board[7][2] = W_BISHOP;
	board->Board[7][4] = W_KING;
	board->Board[7][5] = W_QUEEN;
	board->Board[7][6] = W_HORSE;

	EXPECT_EQ(1, VerifyValidMovement(board, 7, 0, 6, 0));
	EXPECT_EQ(1, VerifyValidMovement(board, 7, 1, 6, 1));
	EXPECT_EQ(1, VerifyValidMovement(board, 7, 2, 6, 3));
	EXPECT_EQ(1, VerifyValidMovement(board, 7, 4, 6, 4));
	EXPECT_EQ(1, VerifyValidMovement(board, 7, 5, 6, 5));
	EXPECT_EQ(1, VerifyValidMovement(board, 7, 6, 5, 7));

	free(board);
}

/* Teste para verificar a função de verificar movimento para movimentos inválidos
   Procedimento:
   	-Criar um tabuleiro vazio.
   	-Preencher com uma peça de cada tipo.
    -Chamar a função de verificar movimento para movimentos inválidos para cada peça.
   Resultados:
	-É esperado quem em todos os casos, para brancas e pretas, retorne 0.
 */

TEST(Test_VerifyValidMovement, Verify_Invalid_Movements){
	TBoard* board = AlocateBoard();
	StartEmptyBoard(board);
	board->Board[0][0] = B_PAWN;
	board->Board[0][1] = B_TOWER;
	board->Board[0][2] = B_BISHOP;
	board->Board[0][4] = B_KING;
	board->Board[0][5] = B_QUEEN;
	board->Board[0][6] = B_HORSE;

	/* Posições fora do tabuleiro */
	EXPECT_EQ(0, VerifyValidMovement(board, 0, 0, 22, 15));
	EXPECT_EQ(0, VerifyValidMovement(board, 0, 1, 14, 13));
	EXPECT_EQ(0, VerifyValidMovement(board, 0, 2, 12, 33));
	EXPECT_EQ(0, VerifyValidMovement(board, 0, 4, 11, 44));
	EXPECT_EQ(0, VerifyValidMovement(board, 0, 5, 13, 54));
	EXPECT_EQ(0, VerifyValidMovement(board, 0, 6, 23, 74));

	/* Posições contendo peças de mesma cor */
	board->Board[1][0] = B_PAWN;
	board->Board[1][1] = B_PAWN;
	board->Board[1][3] = B_PAWN;
	board->Board[1][4] = B_PAWN;
	board->Board[1][5] = B_PAWN;
	board->Board[2][7] = B_PAWN;
	EXPECT_EQ(0, VerifyValidMovement(board, 0, 0, 1, 0));
	EXPECT_EQ(0, VerifyValidMovement(board, 0, 1, 1, 1));
	EXPECT_EQ(0, VerifyValidMovement(board, 0, 2, 1, 3));
	EXPECT_EQ(0, VerifyValidMovement(board, 0, 4, 1, 4));
	EXPECT_EQ(0, VerifyValidMovement(board, 0, 5, 1, 5));
	EXPECT_EQ(0, VerifyValidMovement(board, 0, 6, 2, 7));
	free(board);
}

/* Teste para verificar a função de verificação de xeque funciona corretamente com um
tabuleiro nulo.
   Procedimentos:
   -Criar um tabuleiro do tipo nulo.
   -Chamar a função de atualização da variável de xeque no tabuleiro.
   Resultados:
   -É esperado que o retorno da função seja um ponteiro NULL.
*/
TEST(Test_VerifyCheck, Verify_NULL_Variables){
	TBoard* board1 = NULL;
	TBoard* board2 = NULL;
	board1 = VerifyCheck(board1, BLACK);
	board2 = VerifyCheck(board2, WHITE);
	EXPECT_EQ(NULL, board1);
	EXPECT_EQ(NULL, board2);
}

/* Teste para verificar a função de verificação de xeque funciona corretamente com um
tabuleiro em que está acontecendo um xeque real com o rei preto.
   Procedimentos:
   -Criar um tabuleiro vazio.
   -Inserir peças para uma simulação de xeque.
   -Chamar a função de atualização da variável de xeque no tabuleiro.
   Resultados:
   -É esperado que o retorno da função seja um tabuleiro com a variável dedicada ao xeque do rei preto atualizada.
*/
TEST(Test_VerifyCheck, Verify_RealBlackCheck){
	TBoard* board = AlocateBoard();
	StartEmptyBoard(board);
	board->Board[0][0] = B_KING;
	board->Board[1][1] = W_PAWN;
	board = VerifyCheck(board, BLACK);
	EXPECT_EQ(1, board->BlackCheck);
	EXPECT_EQ(0, board->WhiteCheck);
	free(board);
}

/* Teste para verificar a função de verificação de xeque funciona corretamente com um
tabuleiro em que está acontecendo um xeque real com o rei branco.
   Procedimentos:
   -Criar um tabuleiro vazio.
   -Inserir peças para uma simulação de xeque.
   -Chamar a função de atualização da variável de xeque no tabuleiro.
   Resultados:
   -É esperado que o retorno da função seja um tabuleiro com a variável dedicada ao xeque do rei branco atualizada.
*/
TEST(Test_VerifyCheck, Verify_RealWhiteCheck){
	TBoard* board = AlocateBoard();
	StartEmptyBoard(board);
	board->Board[0][0] = W_KING;
	board->Board[1][1] = B_BISHOP;
	board = VerifyCheck(board, WHITE);
	EXPECT_EQ(0, board->BlackCheck);
	EXPECT_EQ(1, board->WhiteCheck);
	free(board);
}

/* Teste para verificar a função de verificação de xeque funciona corretamente com um
tabuleiro em que está acontecendo um xeque falso com o rei preto.
   Procedimentos:
   -Criar um tabuleiro vazio.
   -Inserir peças para uma simulação de xeque.
   -Chamar a função de atualização da variável de xeque no tabuleiro.
   Resultados:
   -É esperado que o retorno da função seja um tabuleiro com a variável dedicada ao xeque do rei preto não modificada.
*/
TEST(Test_VerifyCheck, Verify_FakeBlackCheck){
	TBoard* board = AlocateBoard();
	StartEmptyBoard(board);
	board->Board[0][0] = B_KING;
	board->Board[2][2] = W_PAWN;
	board = VerifyCheck(board, BLACK);
	EXPECT_EQ(0, board->BlackCheck);
	EXPECT_EQ(0, board->WhiteCheck);
	free(board);
}

/* Teste para verificar a função de verificação de xeque funciona corretamente com um
tabuleiro em que está acontecendo um xeque falso com o rei branco.
   Procedimentos:
   -Criar um tabuleiro vazio.
   -Inserir peças para uma simulação de xeque.
   -Chamar a função de atualização da variável de xeque no tabuleiro.
   Resultados:
   -É esperado que o retorno da função seja um tabuleiro com a variável dedicada ao xeque do rei branco não modificada.
*/
TEST(Test_VerifyCheck, Verify_FakeWhiteCheck){
	TBoard* board = AlocateBoard();
	StartEmptyBoard(board);
	board->Board[0][0] = W_KING;
	board->Board[2][2] = B_PAWN;
	board = VerifyCheck(board, WHITE);
	EXPECT_EQ(0, board->BlackCheck);
	EXPECT_EQ(0, board->WhiteCheck);
	free(board);
}

/* Teste para verificar a função de mudança de estado de xeque funciona corretamente com um
tabuleiro em que está deixando de acontecer um xeque com o rei preto.
   Procedimentos:
   -Criar um tabuleiro vazio.
   -Inserir peças para uma simulação de entrada e saida de xeque.
   -Chamar a função de atualização da variável de xeque no tabuleiro.
   Resultados:
   -É esperado que o retorno da função seja um tabuleiro com a variável
    dedicada ao xeque do rei preto modificada para a mudança de estado de xeque.
*/
TEST(Test_VerifyCheck, Verify_ChangeBlackCheck){
	TBoard* board = AlocateBoard();
	StartEmptyBoard(board);

	board->Board[0][0] = B_KING;
	board->Board[1][1] = W_BISHOP;

	board = VerifyCheck(board, BLACK);

	EXPECT_EQ(1, board->BlackCheck);
	EXPECT_EQ(0, board->WhiteCheck);

	board->Board[1][1] = B_BISHOP;
	board = VerifyCheck(board, BLACK);

	EXPECT_EQ(0, board->BlackCheck);
	EXPECT_EQ(0, board->WhiteCheck);
	free(board);
}

/* Teste para verificar a função de mudança de estado de xeque funciona corretamente com um
tabuleiro em que está deixando de acontecer um xeque com o rei branco.
   Procedimentos:
   -Criar um tabuleiro vazio.
   -Inserir peças para uma simulação de entrada e saida de xeque.
   -Chamar a função de atualização da variável de xeque no tabuleiro.
   Resultados:
   -É esperado que o retorno da função seja um tabuleiro com a variável
    dedicada ao xeque do rei branco modificada para a mudança de estado de xeque.
*/
TEST(Test_VerifyCheck, Verify_ChangeWhiteCheck){
	TBoard* board = AlocateBoard();
	StartEmptyBoard(board);

	board->Board[0][0] = W_KING;
	board->Board[1][1] = B_BISHOP;

	board = VerifyCheck(board, WHITE);

	EXPECT_EQ(0, board->BlackCheck);
	EXPECT_EQ(1, board->WhiteCheck);

	board->Board[1][1] = W_BISHOP;
	board = VerifyCheck(board, WHITE);

	EXPECT_EQ(0, board->BlackCheck);
	EXPECT_EQ(0, board->WhiteCheck);
	free(board);
}

/* Teste para verificar a função de verificar xeque mate para entradas inválidas
   Procedimento:
   	-Criar um tabuleiro vazio.
   	-Chamar função que inicia o tabuleiro vazio;
    -Chamar a função de verificar xeque para um tabuleiro nulo.
    -Chamar a função de verificar xeque para um tabuleiro alocado,
    mas cor inválida.
   Resultados:
	-É esperado quem em ambos os casos retorne NULL.
 */

TEST(Test_VerifyCheckMate, Verify_Invalid_Entries){
	TBoard* board = NULL;
	TBoard* board2 = AlocateBoard();
	StartEmptyBoard(board2);

	/* Testa para tabuleiro nulo e cor válida */
	EXPECT_EQ(NULL, VerifyCheckMate(board, WHITE));
	/* Testa para tabuleiro válido e cor inválida */
	EXPECT_EQ(NULL, VerifyCheckMate(board2, 25));

	free(board2);
}


/* Teste para verificar a função de verificar xeque mate para entradas inválidas
   Procedimento:
   	-Criar um tabuleiro vazio.
   	-Chamar função que inicia o tabuleiro vazio.
   	-Inserir algumas peças em uma configuração de xeque mate.
    -Chamar a função de verificar xeque mate.
   Resultados:
	-É esperado que retorne NULL para peças brancas ou pretas.
 */

TEST(Test_VerifyCheckMate, Verify_Correct_CheckMate){
	TBoard* board = AlocateBoard();
	StartEmptyBoard(board);

	/* Testa xeque mate no rei preto */
	board->BlackCheck = 1;
	board->Board[4][4] = B_KING;
	board->Board[6][5] = W_PAWN;
	board->Board[6][6] = W_BISHOP;
	board->Board[7][3] = W_QUEEN;
	board->Board[2][5] = W_TOWER;
	board->Board[2][6] = W_HORSE;

	EXPECT_EQ(NULL, VerifyCheckMate(board, BLACK));
	free(board);

	/* Testa xeque mate no rei branco */
	board = AlocateBoard();
	StartEmptyBoard(board);
	board->WhiteCheck = 1;
	board->WhiteCheck = 1;
	board->Board[7][0] = W_KING;
	board->Board[4][1] = B_HORSE;
	board->Board[5][0] = B_PAWN;
	board->Board[5][2] = B_BISHOP;
	board->Board[5][1] = B_TOWER;

	EXPECT_EQ(NULL, VerifyCheckMate(board, WHITE));
	free(board);

}

/* Teste para verificar a função de verificar xeque mate para entradas inválidas
   Procedimento:
   	-Criar um tabuleiro vazio.
   	-Chamar função que inicia o tabuleiro vazio.
   	-Inserir algumas peças em uma configuração de xeque mate com apenas um movimento
   	possível para sair do xeque.
    -Chamar a função de verificar xeque mate.
   Resultados:
	-É esperado que para peças brancas e pretas retorne uma lista de movimentos com howmany igual a 1.
 */

TEST(Test_VerifyCheckMate, Verify_Not_CheckMate){
	TBoard* board = AlocateBoard();
	ListOfMoves* LeaveCheck;
	StartEmptyBoard(board);
	/* Testa não xeque mate paro rei preto */
	board->BlackCheck = 1;
	board->Board[4][4] = B_KING;
	board->Board[5][2] = B_TOWER;
	board->Board[6][5] = W_PAWN;
	board->Board[6][6] = W_BISHOP;
	board->Board[7][3] = W_QUEEN;
	board->Board[2][5] = W_TOWER;
	board->Board[2][6] = W_HORSE;
	LeaveCheck = VerifyCheckMate(board, BLACK);
	EXPECT_EQ(1, LeaveCheck->howmany);
	DeleteListOfMoves(LeaveCheck);
	free(board);

	board = AlocateBoard();
	StartEmptyBoard(board);
	/* Testa não xeque mate para o rei branco */
	board->WhiteCheck = 1;
	board->Board[7][0] = W_KING;
	board->Board[7][2] = W_BISHOP;
	board->Board[4][1] = B_HORSE;
	board->Board[5][0] = B_PAWN;
	board->Board[5][2] = B_BISHOP;
	board->Board[5][1] = B_TOWER;
	LeaveCheck = VerifyCheckMate(board, WHITE);
	EXPECT_EQ(1, LeaveCheck->howmany);
	DeleteListOfMoves(LeaveCheck);
	free(board);

}

/* Teste para verificar a validade da função de traduzir um movimento para
   notação algébrica

   Procedimentos:
   - Testar para movimentos em diagonal
   - Testar para movimentos na mesma coluna
   - Testar para movimentos de cavalo 

   Resultados:
   - Para cada caso de teste, espera-se que o resultado da função esteja de
     acordo a notação algébrica */
TEST(MovementTranslation, VariusMovements)
{
	char chess_move[6];
	Move* movement = (Move*) malloc(sizeof(Move));

	/* Movimento: (0,0) para (1,1) */
	movement->origin[0] = 0;
	movement->origin[1] = 0;
	movement->destiny[0] = 1;
	movement->destiny[1] = 1;
	/* Chamando ao função teste */
	Move2Algebraic(movement, chess_move);

	EXPECT_STREQ(chess_move, "a8-b7");

	/* Movimento: (7,1) para (5,0) */
	movement->origin[0] = 7;
	movement->origin[1] = 1;
	movement->destiny[0] = 5;
	movement->destiny[1] = 0;
	/* Chamando ao função teste */
	Move2Algebraic(movement, chess_move);

	EXPECT_STREQ(chess_move, "b1-a3");

	/* Movimento: (7,7) para (0,0) */
	movement->origin[0] = 7;
	movement->origin[1] = 7;
	movement->destiny[0] = 0;
	movement->destiny[1] = 0;
	/* Chamando ao função teste */
	Move2Algebraic(movement, chess_move);

	EXPECT_STREQ(chess_move, "h1-a8");

	/* Movimento: (0,0) para (7,7) */
	movement->origin[0] = 0;
	movement->origin[1] = 0;
	movement->destiny[0] = 7;
	movement->destiny[1] = 7;
	/* Chamando ao função teste */
	Move2Algebraic(movement, chess_move);

	EXPECT_STREQ(chess_move, "a8-h1");

	/* Movimento: (6,2) para (3,5) */
	movement->origin[0] = 6;
	movement->origin[1] = 2;
	movement->destiny[0] = 3;
	movement->destiny[1] = 5;
	/* Chamando ao função teste */
	Move2Algebraic(movement, chess_move);

	EXPECT_STREQ(chess_move, "c2-f5");

	/* Movimento: (0,3) para (7,3) */
	movement->origin[0] = 0;
	movement->origin[1] = 3;
	movement->destiny[0] = 7;
	movement->destiny[1] = 3;
	/* Chamando ao função teste */
	Move2Algebraic(movement, chess_move);

	EXPECT_STREQ(chess_move, "d8-d1");

	free(movement);
}

int main(int argc, char **argv){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
