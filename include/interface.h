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

void InitBoard(WINDOW* boardwin, TBoard* board);

void DrawBoard(WINDOW* boardwin);

void DrawAxis(WINDOW* yaxis, WINDOW* xaxis);

int CreateMenu(WINDOW* menuwin);

#endif
