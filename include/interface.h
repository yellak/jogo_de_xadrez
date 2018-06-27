#ifndef _GUI_INTERFACE_
#define _GUI_INTERFACE_

#include <ncurses.h>
#include "../include/tabuleiro.h"

void InitBoard(WINDOW* boardwin, TBoard* board);

void DrawBoard(WINDOW* boardwin);

void DrawAxis(WINDOW* yaxis, WINDOW* xaxis);

int CreateMenu(WINDOW* menuwin);

#endif
