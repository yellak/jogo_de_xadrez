#include "gtest/gtest.h"
#include "../include/list_of_moves.h"


/* Teste para verificar a função que cria uma lista de movimentos.
	Procedimentos:
	-Criar uma lista;
	Resultados:
	-É esperado que a função retorne um ponteiro diferente de NULL;
	-É esperado que o campo howmany seja igual a 0;
	-É esperado que o campo first seja igaul a NULL.
	-É esperado que o campo current seja igual a NULL.
	-É esperado que o campo last seja igual a NULL.

*/
TEST(Test_CreateListOfMoves, Verify_Correct_Allocation){
	ListOfMoves* AllPlays = NULL;
	int allocated = 0;

	AllPlays = CreateListOfMoves();
	if(AllPlays != NULL){
		allocated = 1;
	}
	EXPECT_EQ(1, allocated);
	EXPECT_EQ(0, AllPlays->howmany);
	EXPECT_EQ(NULL, AllPlays->first);
	EXPECT_EQ(NULL, AllPlays->current);
	EXPECT_EQ(NULL, AllPlays->last);
}

/* Teste para verificar a função que insere um movimento na lista para
entradas invalidas.
	Procedimentos:
	-Tentar inserir um movimento valido em uma lista nula.
	-Tentar inserir um movimento nulo em uma lista valida.
	Resultados:
	-É esperado que a função retorne um inteiro -1 indicando falha na inserção 
	para ambos os casos.

*/

TEST(Test_InsertMove, Verify_Invalid_Entries){
	ListOfMoves* AllPlays = NULL;
	Move play;
	play.origin[0] = 0;
	play.origin[1] = 0;
	play.destiny[0] = 0;
	play.destiny[1] = 0;
	/* Testa para o primeiro parametro invalido e o segundo valido */
	EXPECT_EQ(-1, InsertMove(AllPlays, &play));

	/* Testa para o primeiro parametro valido e o segundo invalido */
	Move* play2 = NULL;
	ListOfMoves* OnePlay = CreateListOfMoves();
	EXPECT_EQ(-1, InsertMove(OnePlay, play2));
}

/* Teste para verificar a função que insere um movimento na lista para
entradas validas.
	Procedimentos:
	-Inserir um movimento.
	Resultados:
	-É esperado que a função retorne um inteiro 0 indicando sucesso na inserção.
	-É esperado que o ponteiro para o primeiro nó da lista seja diferente de NULL.

*/

TEST(Test_InsertMove, Verify_Valid_Entries){
	ListOfMoves* AllPlays = CreateListOfMoves();
	int allocated = 0;
	Move play;
	play.origin[0] = 1;
	play.origin[1] = 2;
	play.destiny[0] = 3;
	play.destiny[1] = 4;

	/* Testa o valor de retorno para operação bem sucedida */
	EXPECT_EQ(0, InsertMove(AllPlays, &play));
	/* Testa se o primeiro nó da lista foi alocado */
	if(AllPlays->first != NULL){
		allocated = 1;
	}
	EXPECT_EQ(1, allocated);
}

/* Teste para verificar se inserção foi correta da função que insere um movimento na lista.
	Procedimentos:
	-Inserir um movimento.
	-Inserir um segundo movimento.
	Resultados:
	-É esperado que o ponteiro para o movimento contido no primeiro nó da lista 
	corresponda ao endereço dado como parâmetro da função.
	-É esperado que o ponteiro para o movimento contido no ultimo nó da lista
	corresponda ao segundo movimento inserido.
	-É esperado que o campo howmany da lista de movimentos seja incrementado para cada inserção.

*/

TEST(Test_InsertMove, Verify_Correct_Insert){
	ListOfMoves* AllPlays = CreateListOfMoves();
	Move play, play2;
	play.origin[0] = 1;
	play.origin[1] = 2;
	play.destiny[0] = 3;
	play.destiny[1] = 4;
	play2.origin[0] = 1;
	play2.origin[1] = 2;
	play2.destiny[0] = 3;
	play2.destiny[1] = 4;

	InsertMove(AllPlays, &play);
	/* Testa se o indereço do movimento do primeiro nó
	corresponde ao dado como parametro */
	EXPECT_EQ(&play, AllPlays->first->play);
	/* Testa se o campo howmany foi incrementado */
	EXPECT_EQ(1, AllPlays->howmany);

	InsertMove(AllPlays, &play2);

	/* Testa se o segundo movimento foi inserido no fim da lista */
	EXPECT_EQ(&play2, AllPlays->last->play);
	/* Testa se o campo howmany foi incrementado */
	EXPECT_EQ(2, AllPlays->howmany);

}

/* Teste para verificar a função de deletar uma lista de movimentos para
uma lista nula.
	Procedimentos:
	-Chamar a função para uma lista nula.
	Resultados:
	-É esperado que retorne o inteiro -1 indicando a falha da operação.

*/

TEST(Test_DeleteListOfMoves, Verify_Invalid_Entrie){
	ListOfMoves* list = NULL;

	EXPECT_EQ(-1, DeleteListOfMoves(list));
}

/* Teste para verificar a função de deletar uma lista de movimentos para
uma lista válida.
	Procedimentos:
	-Chamar a função para uma lista válida.
	Resultados:
	-É esperado que retorne o inteiro 0 indicando o sucesso da operação.

*/

TEST(Test_DeleteListOfMoves, Verify_Valid_Entrie){
	ListOfMoves* list = CreateListOfMoves();
	Move play;
	play.origin[0] = 1;
	play.origin[1] = 2;
	play.destiny[0] = 3;
	play.destiny[1] = 4;

	InsertMove(list, &play);
	EXPECT_EQ(0, DeleteListOfMoves(list));
}

int main(int argc, char **argv){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
