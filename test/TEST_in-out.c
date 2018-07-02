#include "gtest/gtest.h"
#include "../include/in-out.h"

/* Teste para verificar a alocação de uma lista de movimentos passados
   Procedimento:
   	-Chamar função de alocar nova lista.
   Resultados:
   	-É esperado que a função retorne um ponteiro não-nulo;
   	-É esperado que a cabeça não seja nula;
   	-É esperado que a cabeça aponte para nulo;
   	-É esperado que o último elemento aponte para a cabeça.
 */
TEST(Test_Verify_Start_List, Verify_Funcionality){
	ListPastMoves *list = StartListPM();
	EXPECT_TRUE(list != NULL);

	EXPECT_TRUE(list->head != NULL);
	EXPECT_EQ(NULL, list->head->next);
	EXPECT_EQ(list->head, list->last);
}

/* Teste para verificar a função de adicionar um item para entradas inválidas.
   Procedimento:
   	-Chamar função para uma lista nula;
   	-Chamar função para uma string nula.
   Resultados:
   	-É esperado que em ambos os testes a função retorne 1.
 */
TEST(Test_Verify_Add_Move, Verify_Invalid_Entries){
	char move[] = "Nb1-c3";
	EXPECT_EQ(1, AddListPM(NULL, move));

	ListPastMoves *list = StartListPM();
	EXPECT_EQ(1, AddListPM(list, NULL));

	free(list->head);
	free(list);
}

/* Teste para verificar a função de adicionar um item
   Procedimento:
   	-Chamar a função duas vezes para uma lista criada.
   Resultados:
   	-Função deve retornar 0;
   	-Segundo elemento deve conter a string mandada para ela;
   	-Último elemento da lista deve conter a string mandada para ela;
   	-Último elemento da lista deve apontar para NULL;
   	-Segundo elemento deve apontar para o último.
 */
TEST(Test_Verify_Add_Move, Verify_Function){
	char move1[] = "Nb1-c3";
	char move2[] = "Pb1-c4";
	ListPastMoves *list = StartListPM();

	EXPECT_EQ(0, AddListPM(list, move1));
	EXPECT_EQ(0, AddListPM(list, move2));

	EXPECT_TRUE(!strcmp(list->head->next->move, move1));
	EXPECT_TRUE(!strcmp(list->last->move, move2));
	EXPECT_TRUE(list->last->next == NULL);
	EXPECT_EQ(list->head->next->next, list->last);

	free(list->last);
	free(list->head->next);
	free(list->head);
	free(list);
}

/* Teste para verificar a função de remover o último item para entradas inválidas.
   Procedimento:
   	-Chamar função para uma lista nula;
   Resultados:
   	-É esperado que a função retorne 1.
 */
TEST(Test_Verify_Remove_Last, Verify_Invalid_Entries){
	EXPECT_EQ(1, RemoveLastListPM(NULL));
}

int main(int argc, char **argv){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}