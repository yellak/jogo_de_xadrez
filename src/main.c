#include "../include/interface.h"
#include "stdlib.h"

/* Tamanho do tabuleiro */
const int YLIMIT = 8;
const int XLIMIT = 8;

/* Início do tabuleiro */
const int BOARDX = 2;
const int BOARDY = 2;

int main(){
	WINDOW* menuwin;
	WINDOW* boardwin;
	WINDOW* yaxis;
	WINDOW* xaxis;
	TBoard* board = AlocateBoard();
 
	initscr();
	raw();
	noecho();
	curs_set(0);

	if(has_colors() == FALSE)
		{
			endwin();
			printf("Your terminal does not support color\n");
			exit(1);
		}

	start_color();

	/* Criando a janela do menu e oferecendo as opções ao usuário*/
	/* Retorna o modo de jogo(1 = PVP, 2 = PVE, 3 = SAIR) */
	int gamemode = CreateMenu(menuwin);

	clear();

	if(gamemode < 3){
		/* Criando janelas necessárias para o jogo */
		boardwin = newwin(YLIMIT*2 + 1, XLIMIT*4 + 1, BOARDY, BOARDX);
		yaxis = newwin(YLIMIT*2 + 1, 2, BOARDY, 0);
		xaxis = newwin(2, XLIMIT*4 + 1, BOARDX + YLIMIT*2 + 1, BOARDX);
		refresh();

		/* Inicializando as janelas criadas a pouco */
		DrawBoard(boardwin);
		DrawAxis(yaxis, xaxis);
		wrefresh(boardwin);
		wrefresh(yaxis);
		wrefresh(xaxis);

		/* Inicializando o tabuleiro básico */
		StartEmptyBoard(board);
		StartStandardBoard(board);

		/* Mostrando o tabuleiro básico na interface gráfica */
		InitBoard(boardwin, board);
		wrefresh(boardwin);
		
		getch();
		delwin(boardwin);
	}
	endwin();

	return 0;
}
