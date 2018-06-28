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
	
	mvaddstr(0, 20, "Um jogo de xadrez");
	wborder(boardwin, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);
		
	//Colocando linhas verticais e horizontias
	for(int i = 0; i < 7; i++){
		mvwvline(boardwin, 1, 4*i + 4, 0, 2*YLIMIT - 1);
		mvwhline(boardwin, i*2 + 2, 1, 0, 4*XLIMIT - 1);
	}
	
	//Coloca as cruzes na intersecção entre linhas verticais e horizontais
	for(int i = 0; i < 7; i++){
		for(int j = 0; j< 7; j++){
			mvwaddch(boardwin, 2*i + 2, 4*j + 4, ACS_PLUS);
		}
	}

	//Inserindo dentes para a direita e para a esquerda nas extremidades do tabuleiro
	for(int i = 0; i < 7; i++){
		//direita
		mvwaddch(boardwin, 2*i + 2, 0, ACS_LTEE);

		//esquerda
		mvwaddch(boardwin, 2*i + 2, 32, ACS_RTEE);			
	}

	//Inserindo dentes para a cima e para baixo nas extremidades do tabuleiro
	for(int i = 0; i < 7; i++){
		//cima
		mvwaddch(boardwin, 16, 4*i + 4, ACS_BTEE);

		//baixo
		mvwaddch(boardwin, 0, 4*i + 4, ACS_TTEE);
	}
	
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
} /* CreateMenu */
