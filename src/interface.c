#include "../include/interface.h"


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
			else{
				waddch(boardwin, ' ');
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
	
	mvaddstr(0, 10, "Um jogo de xadrez");
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

/* 
   Função: Inicializar janela de ajuda com as teclas (write_keys_help)
         Objetivo:
             Imprimir na janela de ajuda as teclas que o usuário poderá usar

         Parâmetros:
             keywin - Janela responsável por mostrar o menu das chaves 
*/
void write_keys_help(WINDOW* keywin)
{
	int Y_position = BOARDY + 2*YLIMIT + 3;
	int X_position = BOARDX;
	/* Criando uma caixa em volta da janela */
	box(keywin, 0, 0);
	/* Escrevvendo as ajudas de teclas */
	mvwprintw(keywin, 1, 1, "s-Sair");
	mvwprintw(keywin, 1, 9, "j-Jogada pela notação");
	mvwprintw(keywin, 1, 37, "h-Ajuda");
	/* Carregando a janela no terminal */
	wrefresh(keywin);
}

void clear_keywin(WINDOW* keywin){
	int i;
	wmove(keywin, 2, 1);
	for(i = 0; i < 76; i++){
		wprintw(keywin, " ");
	}
	wrefresh(keywin);
}

void init_msg_win(WINDOW* messages){
	box(messages, 0, 0);
	wrefresh(messages);
}

void clear_message(WINDOW* messages){
	int i;
	wmove(messages, 1, 1);
	for(i = 0; i < 40; i++){
		wprintw(messages, " ");
	}
	wrefresh(messages);
}

void print_message(WINDOW* messages, int msg)
{
	wmove(messages, 1, 1);
	switch(msg)
		{
		case INVALID_SINTAX:
			wprintw(messages, "Sintaxe inválida");
			break;
		case ARE_YOU_SURE:
			wprintw(messages, "Você tem certeza? s/n");
			break;
		case CONTINUE_GAME:
			wprintw(messages, "Continuando... faça sua jogada");
			break;
		case INVALID_MOVE:
			wprintw(messages, "Movimento inválido");
			break;
		}
	
	wrefresh(messages);
}

void play_pvp(WINDOW* boardwin, WINDOW* keywin, WINDOW* messages, TBoard* board)
{
	/* Indica a escolha tomada pelo usuário */
	int choice;
	/* Indica se o jogo acabou ou não */
	int finished = false;
	/* String com a jogada escolhida pelo usuário */
	char chess_move[8];
	/* Booleano para fins diversos */
	int boolean;
	/* Movimento do jogador */
	Move* movement = (Move*) malloc(sizeof(Move));

	/* Variáveis para movimento
       ol - origin line
       oc - orig column
       dl - destiny line
       dc - destiny column */
	int ol, oc, dl, dc;


	keypad(stdscr, TRUE);

	while(!finished)
		{
			choice = getch();

			if(choice == 'j') /* Tecla j */
				{
					echo();	/* Deixar as teclas aparecerem na tela */
					curs_set(1); /* Fazer o cursor aparecer */
					wmove(keywin, 2, 1);
					/* Obter a notação de movimento do usuário */
					wgetstr(keywin, chess_move);
					clear_keywin(keywin);
					curs_set(0); /* Tirar o cursor */
					noecho(); /* Desabilitar teclas aparecerem na tela */

					/* Traduzindo o notação para elemento de movimento */
					movement = algebraic_translate(chess_move);
					clear_message(messages);
					/* Assertiva para o caso da sintaxe não ser válida */
					if(movement == NULL)
						{
							print_message(messages, INVALID_SINTAX);
						}
					else  /* Movimento válido pela sintaxe */
						{
							ol = movement->origin[0];
							oc = movement->origin[1];
							dl = movement->destiny[0];
							dc = movement->destiny[1];
							/* Realizando a jogada */
							boolean = MovePiece(board, ol, oc, dl, dc);

							if(boolean == 0) /* Jogada válida */
								{
									InitBoard(boardwin, board);
									wrefresh(boardwin);
								}
							else
								{
									print_message(messages, INVALID_MOVE);
								}
						}
						
				} /* Choide == j */
			else if(choice == 's')
				{
					clear_message(messages);
					/* Colocando a mensagem de incerteza para o usuário */
					print_message(messages, ARE_YOU_SURE);
					choice = 'a';
					while((choice != 's') && (choice != 'n'))
						{
							choice = getchar(); /* Verificando se o usuário realmente quer sair */
							if(choice == 's'){
								finished = true; /* Fim de jogo */
							}
							else if(choice == 'n'){
								clear_message(messages);
								print_message(messages, CONTINUE_GAME);
							}
						}
				} /* choice == 's' */
		}  /* while(!finished) */
}
