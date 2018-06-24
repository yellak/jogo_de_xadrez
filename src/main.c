#include "../include/interface.h"

/* Tamanho do tabuleiro */
const int YLIMIT = 8;
const int XLIMIT = 8;

/* Incício do tabuleiro */
const int BOARDX = 2;
const int BOARDY = 2;

int main()
{
	WINDOW* boardwin;
	WINDOW* yaxis;
	WINDOW* xaxis;
  
	initscr();
	raw();
	noecho();

	boardwin = newwin(YLIMIT*2 + 1, XLIMIT*4 + 1, BOARDY, BOARDX);
	yaxis = newwin(YLIMIT*2 + 1, 2, BOARDY, 0);
	xaxis = newwin(2, XLIMIT*4 + 1, BOARDX + YLIMIT*2 + 1, BOARDX);
	refresh();
  
	DrawBoard(boardwin);
	DrawAxis(yaxis, xaxis);
	wrefresh(boardwin);
	wrefresh(yaxis);
	wrefresh(xaxis);
  
	getch();
	delwin(boardwin);
	endwin();

	return 0;
}
