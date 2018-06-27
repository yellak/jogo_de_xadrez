#include "../include/interface.h"

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

/* 
   Função: Inicializar o tabuleiro
         Objetivo:
             Inicializar graficamente um tabuleiro já pronto

         Parâmetros:
            boardwin - Ponteiro para a janela onde está o tabuleiro

            board    - Struct do tabuleiro onde está o tabuleiro em si que será
                       mostrado na interface
*/
void InitBoard(WINDOW* boardwin, TBoard* board){
	int line, column;
	for(line = 0; line < YLIMIT; line++){
		for(column = 0; column < XLIMIT; column++){
			wmove(boardwin, (line * YOFFSET) + 1, (XOFFSET * column) + 2);
			
			if(board->Board[line][column] != '\\'){
				waddch(boardwin, board->Board[line][column]);
			}
		}
	}
} /* InitBoard */

/*
  Função: Desenhar o tabuleiro
        Objetivo:
            Desenhar o tabuleiro no terminal

        Parâmetros:
            boardwin - janela do tabuleiro, observe que ela já deverá ter sido
                       alocada antes de ser passada como parâmetro desta função
*/
void DrawBoard(WINDOW* boardwin){
	int y, x;
	mvaddstr(0, 20, "Um jogo de xadrez");

	move(BOARDY, BOARDX); /* Movendo para a posição onde deve começar o quadro */
	waddch(boardwin, ACS_ULCORNER); /* Colocando o canto superior esquerdo */

	for(y = 0; y < YLIMIT - 1; y++) /* Percorrendo a primeira linha */
		{
			/* Linhas horizontais superiores */
			waddch(boardwin, ACS_HLINE);
			waddch(boardwin, ACS_HLINE);
			waddch(boardwin, ACS_HLINE);
			waddch(boardwin, ACS_TTEE);
		}
	/* Últimas linhas horizontais e canto superior direito */
	waddch(boardwin, ACS_HLINE);
	waddch(boardwin, ACS_HLINE);
	waddch(boardwin, ACS_HLINE);
	waddch(boardwin, ACS_URCORNER);

	for (x = 1; x < YLIMIT; x++) /* Percorrendo cada linha */
		{
			move(BOARDY + x * 2 - 1, BOARDX);
			waddch(boardwin, ACS_VLINE); /* Paredes verticais */
			for (y = 0; y < XLIMIT; y++)
				{
					/* Partes em branco no meio */
					waddch(boardwin, ' ');
					waddch(boardwin, ' ');
					waddch(boardwin, ' ');
					waddch(boardwin, ACS_VLINE);
				}
			move(BOARDY + x * 2, BOARDX);
			waddch(boardwin, ACS_LTEE);
			for (y = 0; y < XLIMIT - 1; y++)
				{
					waddch(boardwin, ACS_HLINE);
					waddch(boardwin, ACS_HLINE);
					waddch(boardwin, ACS_HLINE);
					waddch(boardwin, ACS_PLUS);
				}
			waddch(boardwin, ACS_HLINE);
			waddch(boardwin, ACS_HLINE);
			waddch(boardwin, ACS_HLINE);
			waddch(boardwin, ACS_RTEE);
		}

	move(BOARDY + x * 2 - 1, BOARDX);
	waddch(boardwin, ACS_VLINE);
	for (y = 0; y < XLIMIT; y++)
		{
			waddch(boardwin, ' ');
			waddch(boardwin, ' ');
			waddch(boardwin, ' ');
			waddch(boardwin, ACS_VLINE);
		}

	move(BOARDY + x * 2, BOARDX);
	waddch(boardwin, ACS_LLCORNER);
	for (y = 0; y < XLIMIT - 1; y++)
		{
			waddch(boardwin, ACS_HLINE);
			waddch(boardwin, ACS_HLINE);
			waddch(boardwin, ACS_HLINE);
			waddch(boardwin, ACS_BTEE);
		}
	waddch(boardwin, ACS_HLINE);
	waddch(boardwin, ACS_HLINE);
	waddch(boardwin, ACS_HLINE);
	waddch(boardwin, ACS_LRCORNER);
} /* DrawBoard */

/* 
   Função: Desenhar eixos coordernados (DrawAxis)
         Objetivo:
             Desenhar os eixos coordenados em volta do tabuleiro.

         Parâmetros:
             yaxis - Janela responsável pelo desenho do eixo y, já deverá ter
                     sido alocada antes da chamada desta função

             xaxis - Janela do eixo x embaixo do tabuleiro

*/
void DrawAxis(WINDOW* yaxis, WINDOW* xaxis){
	int i, j;
	char value[2];
  
	for(i = 1, j = 8; j >= 1; i += 2, j--){
		sprintf(value, "%d", j);
		wmove(yaxis, i, 0);
		waddch(yaxis, value[0]);
	}

	for(i = 2, j = 0; i <= 32; i += 4, j++){
		wmove(xaxis, 0, i);
		waddch(xaxis, 'a' + j);
	}
}

/* 
   Função: CreateMenu
         Objetivo:
             Desenhar o menu e apresentar as opções de jogo ao usuário

         Parâmetros:
             menuwin -  Janela responsável pela criação do menu 
		 
		 Saída: Essa função retorna a opção do jogo que o usuário deseja jogar
		 		1 = PVP
		 		2 = PVE
		 		3 = SAIR

*/
int CreateMenu(WINDOW* menuwin){

	int yMax,xMax;

	//Pegando o tamanho do terminal
	getmaxyx(stdscr, yMax, xMax);

	//Inicializando a janela
	menuwin = newwin(6, xMax - 12, yMax-8, 5);
	box(menuwin, 0, 0);
	refresh();
	wrefresh(menuwin);

	//Função para ativas os comandos das setinhas
	keypad(menuwin, true);

	char* modos[4] = {"Escolha o Modo de Jogo:","JogadorXJogador","JogadorXComputador","Sair"};

	int choice = 0;
	int highlight = 1;

	//Não avança até o usuário apertar "enter"
	while(choice != 10){
		for(int i = 0; i < 4; i++){

			/* Destacando a string que o usuário está em cima */
			if(i == highlight){
				wattron(menuwin, A_REVERSE);
			}

			mvwprintw(menuwin, i + 1, 1, modos[i]);
			wattroff(menuwin, A_REVERSE);
			wrefresh(menuwin);
			
		}
		choice = wgetch(menuwin);
		switch(choice){

			case KEY_UP: //Seta pra cima
				highlight--;
				if (highlight == 0) highlight = 1; /* Condição para não passar do topo */
			break;

			case KEY_DOWN: //Seta pra cima
				highlight++;
				if (highlight == 4) highlight = 3; /* Condição para não passar do fundo */
			break;

			default:
			break;
		}
	}
	
	delwin(menuwin);

	return highlight;
}
