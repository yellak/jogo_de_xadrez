#ifndef LOGICA_H_
#define LOGICA_H_

#include "../include/list_of_moves.h"
#include "../include/tabuleiro.h"

/* Funções para manipulação da lógica do xadrez: */

/*Analisa os movimentos possíveis em um tabuleiro em relação as peças pretas.*/
/*! \fn ListOfMoves AnalyzePossibleMovementsBlack(TBoard *board)
		\brief Armazena movimentos possíveis para cada peça preta.

		\param board Ponteiro para um tabuleiro.
		\return Retorna uma lista com os movimentos possíveis de acordo com as peças pretas.
*/
ListOfMoves* AnalyzePossibleMovementsBlack(TBoard *board);

/*Analisa os movimentos possíveis em um tabuleiro em relação as peças brancas.*/
/*! \fn ListOfMoves AnalyzePossibleMovementsWhite(TBoard *board)
		\brief Armazena movimentos possíveis para cada peça branca.

		\param board Ponteiro para um tabuleiro.
		\return Retorna uma lista com os movimentos possíveis de acordo com as peças brancas.
*/
ListOfMoves* AnalyzePossibleMovementsWhite(TBoard *board);

/* \fn int verify_syntax_move(char chess_move[])
       \brief Verifica a validade da sintaxe da notação algébrica de um
              movimento de xadrez

       \param chess_move Strig com a notação

       \return True caso a sintaxe esteja correta ou false caso não esteja */
int verify_syntax_move(char chess_move[]);

/*! \fn Move* algebraic_translate(char chess_move[])
        \brief Traduz uma notação algébrica de um movimento de xadrez para um
               movimento normal na matriz do tabuleiro

         \param chess_move String com a notação algébrica do movimento

         \return Um elemento de movimento com a origem e o destino do movimento */
Move* algebraic_translate(char chess_move[]);

/* Função para calcular os movimentos de um peão preto. */
/*! \fn ListOfMoves* BlackPawnMovements(TBoard* board, ListOfMoves* AllMoves, int originx, int originy)
    \brief Adiciona os movimentos possíveis de um peão preto,
     dada uma configuração de tabuleiro, em uma lista de movimentos.

    \param board Ponteiro para um tabuleiro.
    \param AllMoves Ponteiro para uma lista de movimentos.
    \param originx Inteiro referente a coordenada x da peça no tabuleiro.
    \param originy Inteiro referente a coordenada y da peça no tabuleiro.
    \return Retorna uma lista de movimentos e em caso de parâmetros inválidos retorna NULL.
*/
ListOfMoves* BlackPawnMovements(TBoard* board, ListOfMoves* AllMoves, int originx, int originy);

/* Função para calcular os movimentos de um peão branco. */
/*! \fn ListOfMoves* WhitePawnMovements(TBoard* board, ListOfMoves* AllMoves, int originx, int originy)
    \brief Adiciona os movimentos possíveis de um peão branco,
     dada uma configuração de tabuleiro, em uma lista de movimentos.

    \param board Ponteiro para um tabuleiro.
    \param AllMoves Ponteiro para uma lista de movimentos.
    \param originx Inteiro referente a coordenada x da peça no tabuleiro.
    \param originy Inteiro referente a coordenada y da peça no tabuleiro.
    \return Retorna uma lista de movimentos e em caso de parâmetros inválidos retorna NULL.
*/
ListOfMoves* WhitePawnMovements(TBoard* board, ListOfMoves* AllMoves, int originx, int originy);

/* Função para calcular os movimentos de uma torre. */
/*! \fn ListOfMoves* TowerMovements(TBoard* board, ListOfMoves* AllMoves, int originx, int originy)
    \brief Adiciona os movimentos possíveis de uma torre,
     dada uma configuração de tabuleiro, em uma lista de movimentos.

    \param board Ponteiro para um tabuleiro.
    \param AllMoves Ponteiro para uma lista de movimentos.
    \param originx Inteiro referente a coordenada x da peça no tabuleiro.
    \param originy Inteiro referente a coordenada y da peça no tabuleiro.
    \return Retorna uma lista de movimentos e em caso de parâmetros inválidos retorna NULL.
*/
ListOfMoves* TowerMovements(TBoard* board, ListOfMoves* AllMoves, int originx, int originy);

/* Função para calcular os movimentos de um bispo. */
/*! \fn ListOfMoves* BishopMovements(TBoard* board, ListOfMoves* AllMoves, int originx, int originy)
    \brief Adiciona os movimentos possíveis de um bispo,
     dada uma configuração de tabuleiro, em uma lista de movimentos.

    \param board Ponteiro para um tabuleiro.
    \param AllMoves Ponteiro para uma lista de movimentos.
    \param originx Inteiro referente a coordenada x da peça no tabuleiro.
    \param originy Inteiro referente a coordenada y da peça no tabuleiro.
    \return Retorna uma lista de movimentos e em caso de parâmetros inválidos retorna NULL.
*/
ListOfMoves* BishopMovements(TBoard* board, ListOfMoves* AllMoves, int originx, int originy);

/* Função para calcular os movimentos de uma rainha. */
/*! \fn ListOfMoves* QueenMovements(TBoard* board, ListOfMoves* AllMoves, int originx, int originy)
    \brief Adiciona os movimentos possíveis de uma rainha,
     dada uma configuração de tabuleiro, em uma lista de movimentos.

    \param board Ponteiro para um tabuleiro.
    \param AllMoves Ponteiro para uma lista de movimentos.
    \param originx Inteiro referente a coordenada x da peça no tabuleiro.
    \param originy Inteiro referente a coordenada y da peça no tabuleiro.
    \return Retorna uma lista de movimentos e em caso de parâmetros inválidos retorna NULL.
*/
ListOfMoves* QueenMovements(TBoard* board, ListOfMoves* AllMoves, int originx, int originy);

/* Função para calcular os movimentos de um rei. */
/*! \fn ListOfMoves* KingMovements(TBoard* board, ListOfMoves* AllMoves, int originx, int originy)
    \brief Adiciona os movimentos possíveis de um rei,
     dada uma configuração de tabuleiro, em uma lista de movimentos.

    \param board Ponteiro para um tabuleiro.
    \param AllMoves Ponteiro para uma lista de movimentos.
    \param originx Inteiro referente a coordenada x da peça no tabuleiro.
    \param originy Inteiro referente a coordenada y da peça no tabuleiro.
    \return Retorna uma lista de movimentos e em caso de parâmetros inválidos retorna NULL.
*/
ListOfMoves* KingMovements(TBoard* board, ListOfMoves* AllMoves, int originx, int originy);

/* Função para calcular os movimentos de um Cavalo. */
/*! \fn ListOfMoves* HorseMovements(TBoard* board, ListOfMoves* AllMoves, int originx, int originy)
    \brief Adiciona os movimentos possíveis de um Cavalo,
     dada uma configuração de tabuleiro, em uma lista de movimentos.

    \param board Ponteiro para um tabuleiro.
    \param AllMoves Ponteiro para uma lista de movimentos.
    \param originx Inteiro referente a coordenada x da peça no tabuleiro.
    \param originy Inteiro referente a coordenada y da peça no tabuleiro.
    \return Retorna uma lista de movimentos e em caso de parâmetros inválidos retorna NULL.
*/
ListOfMoves* HorseMovements(TBoard* board, ListOfMoves* AllMoves, int originx, int originy);

/* Função para verificar se um movimento é válido */
/*! \fn int VerifyValidMovement(TBoard* board, int originx, int originy, int destinyx, int destinyy)
    \brief Verifica com base nas coordenadas de origem e destino do movimento, se ele
    é válido.
    \param board Ponteiro para um tabuleiro.
    \param originx Inteiro representando a coordenada x da posição (x,y) a ser verificada.
    \param originy Inteiro representando a coordenada y da posição (x,y) a ser verificada.
    \param destinyx Inteiro representando a coordenada x da posição de destino (x,y) a ser verificada.
    \param destinyy Inteiro representando a coordenada y da posição de destubi (x,y) a ser verificada.
    \return Retorna um inteiro 0 ou 1 indicando movimento inválido ou válido respectivamente.
*/
int VerifyValidMovement(TBoard* board, int originx, int originy, int destinyx, int destinyy);

/* Função para verificar se é xeque */
/*! \fn TBoard* VerifyCheck(TBoard* board, int color)
    \brief Verifica com base em um tabuleiro e uma cor se o rei dessa cor está em xeque.
    \param board Ponteiro para um tabuleiro.
    \param color Inteiro indicando a cor do rei.
    \return Retorna um ponteiro para um tabuleiro com o campo check da cor analisada, atualizado.
*/
TBoard* VerifyCheck(TBoard* board, int color);

/* Função para verificar se é xeque mate */
/*! \fn TBoard* VerifyCheck(TBoard* board, int color)
    \brief Verifica com base em um tabuleiro e uma cor se o rei dessa cor está em xeque mate.
    \param board Ponteiro para um tabuleiro.
    \param color Inteiro indicando a cor do rei.
    \return Retorna um ponteiro para uma lista de movimentos contendo os movimentos possíveis para sair do 
    xeque ou NULL em caso de xeque mate.
*/
ListOfMoves* VerifyCheckMate(TBoard* board, int color);

/* Função de traduzir movimento para notação algébrica */
/*! \fn void Move2Algebraic(Move* movement, char chess_move[])
        \brief Traduz para notação algébrica a partir do movimento 

        A partir do elemento de movimento a ele irá traduzí-lo para notação
		algébrica

        \param movement   Elemento de movimento a ser traduzido
        \param chess_move String que será substituída pela nova notação */
void Move2Algebraic(Move* movement, char chess_move[]);

#endif
