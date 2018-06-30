#ifndef _GUI_INTERFACE_
#define _GUI_INTERFACE_

#include <ncurses.h>
#include "../include/tabuleiro.h"

/* Tamanho do tabuleiro */
const int XLIMIT = 8;
const int YLIMIT = 8;

/* Coordenadas para o início do tabuleiro */
const int BOARDY = 2;
const int BOARDX = 2;

/* Variáveis usadas para diferenciar entre o tabuleiro mostrado ao usuário e o
   que está armazenado na memória */
const int YOFFSET = 2;
const int XOFFSET = 4;


/* Inicia um tabuleiro graficamente */
/*! \fn void InitBoard(WINDOW* boardwin, TBoard* board)
		\brief Inicializa graficamente um tabuleiro na base inicial

		\param boardwin Janela onde está o tabuleiro
		\param board    Tabuleiro que será incializado na parte gráfica
		\return Não tem retorno
*/
void InitBoard(WINDOW* boardwin, TBoard* board);

/* Desenha um tabeuleiro vazio */
/*! \fn void DrawBoard(WINDOW* boardwin)
        \brief Desenha um tabuleiro vazio no terminal

		\param boardwin Janela onde será colocado o tabuleiro
		\return Não há retorno, ela apenas desenha o quadro na janela dada
 */
void DrawBoard(WINDOW* boardwin);

/* Desenha os eixos coordenados */
/*! \fn void DrawAxis(WINDOW* yaxis, WINDOW* xaxis)
        \brief Desenha os eixos coordenados que servem para indicar ajudar a
               identificar a posição de uma peça

		\param yaxis Eixo das coordenadas dadas por números
		\param xaxis Eixo das coordenadas dadas pelas letras
		\return Sem retorno
*/
void DrawAxis(WINDOW* yaxis, WINDOW* xaxis);

/* Cria um menu para escolha de tipo de jogo */
/*! \fn int CreateMenu(WINDOW* menuwin)
        \brief Desenha o menu de escolha do tipo de jogo e faz o usuário
               escolher entre uma das opções disponíveis

        \param menuwin Janela onde será mostrado o menu

		\return 1 Se o usuário escolher "Jogador VS Jogador"
                2 Se ele escolher "Jogador VS Máquina"
                3 Se escolher Sair
*/
int CreateMenu(WINDOW* menuwin);

#endif
