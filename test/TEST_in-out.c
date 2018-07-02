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
	ASSERT_NE(NULL, list);

	ASSERT_NE(NULL, list->head);
	EXPECT_EQ(NULL, list->head->next);
	EXPECT_EQ(list->head, list->last);
}