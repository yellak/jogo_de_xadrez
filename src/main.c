#include "../include/interface.h"
#include "stdlib.h"

int main()
{
	/* Janelas que serão utilizadas durante o uso do programa */
	WINDOW* menuwin;
	WINDOW* boardwin;
	WINDOW* yaxis;
	WINDOW* xaxis;
	WINDOW* keywin;
	WINDOW* messages;
	/* Tabuleiro */
	TBoard* board;
   
	initscr(); /* Incializando o Ncurses */
	raw(); /* Para pegar teclas no mesmo momento em que são digitadas */
	curs_set(0); /* Ocultar cursor */
	noecho(); /* Não mostrar na tela o que o usuário digitar */

	/* Verificando se o terminal possui suporte para cores */
	if(has_colors() == FALSE)
		{
			endwin();
			printf("Seu terminal não suporta cores\n");
			exit(1);
		}

	/* Inicializando modo de cores do Ncurses */
	start_color();

	/* 
	 * init_pair(1, COLOR_WHITE, COLOR_CYAN);
	 * 
	 * attron(COLOR_PAIR(1));
	 * bkgd(COLOR_PAIR(1));
	 */

	/* Abrindo menu para escolha do tabuleiro desejado */
	board = MenuGetBoard();
	erase(); /* Limpando o terminal */

	/* Condição do usuário ter escolhido para sair do jogo */
	if(board == NULL)
		{
			endwin();
			return 0;
		}

	/* Criando a janela do menu e oferecendo as opções ao usuário*/
	/* Retorna o modo de jogo(1 = PVP, 2 = PVE, 3 = SAIR) */
	int gamemode = CreateMenu(menuwin);
	erase();

	/* Usuário escolheu sair do jogo */
	if(gamemode == 3)
		{
			endwin();
			return 0;
		}

	/* Janela do tabuleiro */
	boardwin = MakeBoardWin();
	/* Janelas dos eixos coordenados */
	yaxis = MakeYaxisWin();
	xaxis = MakeXaxisWin();
	/* Janela da interface com o teclado do usuário */
	keywin = MakeKeyWin();
	/* Janela onde serão impressas as mensagens para o usuário */
	messages = MakeMsgWin();
	refresh();

	/* Inicializando as janelas criadas a pouco */
	DrawBoard(boardwin);
	DrawAxis(yaxis, xaxis);
	init_msg_win(messages);
	
	/* Colocando as ajudas com as teclas */
	write_keys_help(keywin, GAMING);

	/* Mostrando o tabuleiro básico na interface gráfica */
	InitBoard(boardwin, board);
	wrefresh(boardwin);

	if(gamemode == PVP)
		{
			play_pvp(boardwin, keywin, messages, board);
		}
	else if(gamemode == PVE)
		{
			play_pve(boardwin, keywin, messages, board);
		}
		
	delwin(boardwin);
	delwin(yaxis);
	delwin(xaxis);
	delwin(keywin);

	free(board);
	endwin();

	return 0;
}
