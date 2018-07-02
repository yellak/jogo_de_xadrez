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

/* Teste para verificar a alocação de uma lista de movimentos passados
   Procedimento:
   	-Chamar função de alocar nova lista.
   Resultados:
   	-É esperado que a função retorne um ponteiro não-nulo;
   	-É esperado que a cabeça não seja nula;
   	-É esperado que a cabeça aponte para nulo;
   	-É esperado que o último elemento aponte para a cabeça.
 */
TEST(Test_Verify_Add_Move, Verify_Invalid_Entries){
	char move[] = "Nb1-c3";
	EXPECT_EQ(1, AddListPM(NULL, move));

	ListPastMoves *list = StartListPM();
	EXPECT_EQ(1, AddListPM(list, NULL));

	free(list->head);
	free(list);
}

int main(int argc, char **argv){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}