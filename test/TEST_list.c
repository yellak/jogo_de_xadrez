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
	DeleteListOfMoves(AllPlays);
}

/* Teste para verificar a função que insere um movimento na lista para
entradas invalidas.
	Procedimentos:
	-Tentar inserir um movimento valido em uma lista nula.
	Resultados:
	-É esperado que a função retorne um inteiro -1 indicando falha na inserção.

*/

TEST(Test_InsertMove, Verify_Invalid_Entries){
	ListOfMoves* AllPlays = NULL;

	/* Testa para o primeiro parametro invalido */
	EXPECT_EQ(-1, InsertMove(AllPlays, 1, 2, 3, 4));
	DeleteListOfMoves(AllPlays);
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

	/* Testa o valor de retorno para operação bem sucedida */
	EXPECT_EQ(0, InsertMove(AllPlays, 1, 2, 3, 4));
	/* Testa se o primeiro nó da lista foi alocado */
	if(AllPlays->first != NULL){
		allocated = 1;
	}
	EXPECT_EQ(1, allocated);

	DeleteListOfMoves(AllPlays);
}

/* Teste para verificar se inserção foi correta da função que insere um movimento na lista.
	Procedimentos:
	-Inserir um movimento.
	-Inserir um segundo movimento.
	Resultados:
	-É esperado que os valores contidos no campo play correspondam ao os valores dados
	como parâmetro.
	-É esperado que os valores contidos no campo play do último nó correspondam aos
	parâmetros da segunda inserção.
	-É esperado que o campo howmany da lista de movimentos seja incrementado para cada inserção.
	-E esperado que o campo last da lista tenha sido atualizado após a segunda inserção.

*/

TEST(Test_InsertMove, Verify_Correct_Insert){
	ListOfMoves* AllPlays = CreateListOfMoves();

	InsertMove(AllPlays, 1, 2, 3, 4);
	/* Testa se o primeiro nó contém os valores dados como parâmetro */
	EXPECT_EQ(1, AllPlays->first->play.origin[0]);
	EXPECT_EQ(2, AllPlays->first->play.origin[1]);
	EXPECT_EQ(3, AllPlays->first->play.destiny[0]);
	EXPECT_EQ(4, AllPlays->first->play.destiny[1]);
	/* Testa se o campo howmany foi incrementado */
	EXPECT_EQ(1, AllPlays->howmany);

	InsertMove(AllPlays, 5, 6, 7, 8);

	/* Testa se o segundo movimento foi inserido no fim da lista */
	int different = 0;
	if(AllPlays->first != AllPlays->last){
		different = 1;
	}
	EXPECT_EQ(1, different);
	EXPECT_EQ(5, AllPlays->last->play.origin[0]);
	EXPECT_EQ(6, AllPlays->last->play.origin[1]);
	EXPECT_EQ(7, AllPlays->last->play.destiny[0]);
	EXPECT_EQ(8, AllPlays->last->play.destiny[1]);
	/* Testa se o campo howmany foi incrementado */
	EXPECT_EQ(2, AllPlays->howmany);

	DeleteListOfMoves(AllPlays);
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

	InsertMove(list, 1, 2, 3, 4);
	EXPECT_EQ(0, DeleteListOfMoves(list));
}

/* Teste para verificar a se a função realiza uma busca corretamente
	Procedimentos:
	-Chamar a função para criar uma lista
	-Inserir nós na lista
	-Buscar movimento na lista
	Resultados:
	-A função deve retornar 0
*/
TEST(Test_SearchListOfMoves, Verify_Succesfull_Search){
	ListOfMoves* list = CreateListOfMoves();

	InsertMove(list, 0, 0, 0, 0);
	InsertMove(list, 1, 2, 3, 4);

	EXPECT_EQ(0, SearchListOfMoves(list, 1, 2, 3, 4));

	DeleteListOfMoves(list);
}

/* Teste para verificar a se ao buscar um movimento que não está na lista retorna 1
	Procedimentos:
	-Chamar a função para criar a lista.
	-Inserir nós na lista
	-Buscar movimento que não existe na lista
	Resultados:
	-A função deve retornar 1

*/

TEST(Test_SearchListOfMoves, Verify_Failure_Search){
	ListOfMoves* list = CreateListOfMoves();

	InsertMove(list, 0, 0, 0, 0);
	InsertMove(list, 1, 1, 2, 3);

	EXPECT_EQ(1, SearchListOfMoves(list, 1, 2, 3, 4));

	DeleteListOfMoves(list);
}

int main(int argc, char **argv){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
