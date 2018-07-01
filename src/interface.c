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

	/* Desenhando eixo Y */
	for(i = 1, j = 8; j >= 1; i += 2, j--){
		sprintf(value, "%d", j);
		wmove(yaxis, i, 1);
		waddch(yaxis, value[0]);
	}

	/* Desenhando eixo X */
	for(i = 2, j = 0; i <= 32; i += 4, j++){
		wmove(xaxis, 0, i);
		waddch(xaxis, 'a' + j);
	}
}

void HelpWinNewBoard(WINDOW* helpwin)
{
	box(helpwin, 0, 0);
	/* Mostrando o título */
	mvwprintw(helpwin, 1, 11, "Opções de peças");

	/* Mostrando as opções de peças pretas */
	mvwprintw(helpwin, 3, 1, "K - Rei preto");
	mvwprintw(helpwin, 4, 1, "Q - Rainha preta");
	mvwprintw(helpwin, 5, 1, "R - Torre preta");
	mvwprintw(helpwin, 6, 1, "B - Bispo preto");
	mvwprintw(helpwin, 7, 1, "N - Cavalo preto");
	mvwprintw(helpwin, 8, 1, "P - Peão preto");

	/* Mostrando as opções de peças brancas */
	mvwprintw(helpwin, 3, 18, "k - Rei branco");
	mvwprintw(helpwin, 4, 18, "q - Rainha branca");
	mvwprintw(helpwin, 5, 18, "r - Torre branca");
	mvwprintw(helpwin, 6, 18, "b - Bispo branco");
	mvwprintw(helpwin, 7, 18, "n - Cavalo branco");
	mvwprintw(helpwin, 8, 19, "p - Peão branco");

	/* Carregar as impressões acima */
	wrefresh(helpwin);
}

TBoard* CreateNewBoard(void)
{
	/* Tabuleiro que será retornado */
	TBoard* board = AlocateBoard();

	/* Janelas do tabuleiro */
	WINDOW* boardwin = newwin(YLIMIT*2 + 1, XLIMIT*4 + 1, BOARDY, BOARDX);
	WINDOW* yaxis = newwin(YLIMIT*2 + 1, 2, BOARDY, 0);
	WINDOW* xaxis = newwin(1, XLIMIT*4 + 1, BOARDY + YLIMIT*2 + 1, BOARDX);

	/* Janela de ajuda */
	WINDOW* helpwin = newwin(YLIMIT*2 - 3, 42, BOARDY, BOARDX + 4*XLIMIT + 3);

	/* Janela onde serão impressas as mensagens para o usuário */
	WINDOW* messages = newwin(3, 42, BOARDY + 2*YLIMIT - 2, BOARDX + 4*XLIMIT + 3);

	WINDOW* keywin = newwin(4, 78, BOARDY + 2*YLIMIT + 2, 1);

	/* Carregando as janelas */
	refresh();

	/* Colocando a janela com atalhos */
	write_keys_help(keywin, CREATING);

	/* Desenhando um tabuleiro */
	DrawBoard(boardwin);
	DrawAxis(yaxis, xaxis);
	HelpWinNewBoard(helpwin);
	init_msg_win(messages);
	
	/* Carregando o tabuleiro desenhado */
	wrefresh(boardwin);
	wrefresh(yaxis);
	wrefresh(xaxis);

	getch();

	delwin(boardwin);
	delwin(yaxis);
	delwin(xaxis);

	return board;
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

	int yMax, xMax;

	/* Pegando o tamanho do terminal */
	getmaxyx(stdscr, yMax, xMax);

	/* Inicializando a janela */
	menuwin = newwin(6, xMax - 12, yMax-8, 5);
	box(menuwin, 0, 0);
	refresh();
	wrefresh(menuwin);

	/* Função para ativar os comandos das setinhas */
	keypad(menuwin, true);

	char modos[4][xMax - 12];
	strcpy(modos[0], "Escolha o Modo de Jogo:                                     ");
	strcpy(modos[1], "Jogador vs Jogador                                          ");
	strcpy(modos[2], "Jogador vs Computador                                       ");
	strcpy(modos[3], "Sair do jogo                                                ");

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
 Função: Criar menu de escolha de tabuleiro
       Objetivo:
           Blah
       
       Saída:
*/
TBoard* MenuGetBoard()
{
	/* Indicarão o tamanho da tela */
	int yMax, xMax;
	/* Indicarão a escolha do usuário */
	int choice = 0, highlight = 1;
	/* Contador */
	int i;
	/* Janela onde será mostrado o menu de escolha do tabuleiro */
	WINDOW* menu;
	/* Tabuleiro que será retornado para o módulo principal */
	TBoard* board;

	/* Pegando o tamanho do terminal */
	getmaxyx(stdscr, yMax, xMax);

	/* Inicializando a janela */
	menu = newwin(7, xMax - 12, yMax - 9, 5);
	box(menu, 0, 0); /* Desenhando um quadro em volta da janela */
	refresh();
	wrefresh(menu);	/* Carregando a janela na tela */

	/* Ativando teclas do teclados como setinhas por exemplo */
	keypad(menu, true);

	/* Variável com as opções do menu */
	char opcoes[5][xMax - 12];
	strcpy(opcoes[0], "Com qual tabuleiro você prefere jogar?");
	strcpy(opcoes[1], "Tabuleiro padrão                                           ");
	strcpy(opcoes[2], "Carregar tabuleiro salvo                                   ");
	strcpy(opcoes[3], "Criar um tabuleiro do zero                                 ");
	strcpy(opcoes[4], "Sair do jogo                                               ");

	while(choice != 10)	/* Tecla ENTER */
		{
			for(i = 0; i < 5; i++)
				{
					if(i == highlight)
						{
							/* Ativando o highlight na opção atual */
							wattron(menu, A_REVERSE);
						}
					/* Atulizando as opções */
					mvwprintw(menu, i + 1, 1, opcoes[i]);
					wattroff(menu, A_REVERSE);
					wrefresh(menu);
				}

			/* Obtendo a tecla que o usuário apertou */
			choice = wgetch(menu);
			switch(choice)
				{
				case KEY_UP:	/* Seta para cima */
					highlight--;
					if(highlight == 0) /* Não é para destacar o título do menu */
						{
							highlight = 1;
						}
					break;

				case KEY_DOWN:	/* Seta para baixo */
					highlight++;
					if(highlight == 5) /* Não é para passar o limite inferior */
						{
							highlight = 4;
						}
					break;

				default:
					break;
				} /* switch(choice) */
		} /* while(choice != 10 */

	delwin(menu);

	switch(highlight)
		{
		case STD_BOARD:
			board = AlocateBoard();
			StartEmptyBoard(board);
			StartStandardBoard(board);
			break;

		case SAVED_BOARD:
			mvprintw(1, 1, "Ainda em processo de desenvolvimento");
			refresh();
			break;
			
		case NEW_BOARD:
			clear();
			board = CreateNewBoard();
			break;

		case EXIT_GAME:
			free(board);
			board = NULL;
			break;
		}
	
	return board;
} /* MenuGetBoard() */

/* 
   Função: Inicializar janela de ajuda com as teclas (write_keys_help)
         Objetivo:
             Imprimir na janela de ajuda as teclas que o usuário poderá usar

         Parâmetros:
             keywin - Janela responsável por mostrar o menu das chaves 
*/
void write_keys_help(WINDOW* keywin, int wintype)
{
	int Y_position = BOARDY + 2*YLIMIT + 3;
	int X_position = BOARDX;
	
	/* Criando uma caixa em volta da janela */
	box(keywin, 0, 0);
	
	/* Escrevendo as ajudas de teclas */
	if(wintype == GAMING)
		{
			mvwprintw(keywin, 1, 1, "q-Sair");
			mvwprintw(keywin, 1, 9, "j-Jogada pela notação");
			mvwprintw(keywin, 1, 37, "h-Ajuda");
		}
	else if(wintype == CREATING)
		{
			mvwprintw(keywin, 1, 1, "q-Sair");
			mvwprintw(keywin, 1, 9, "a-Adicionar");
			mvwprintw(keywin, 1, 24, "r-Remover");
		}
	
	/* Carregando a janela no terminal */
	wrefresh(keywin);
}

/*
 Função: Limpar a janela de interação com o usuário (clear_keywin)
       Objetivo:
           Limpar a parte onde o usuário digita coisas na janela de teclas 
           e atalhos

       Parâmetros:
           keywin - a própria janela de teclas e atalhos que deverá ser
		            diferente de nula
*/
void clear_keywin(WINDOW* keywin){
	int i;
	wmove(keywin, 2, 1);
	for(i = 0; i < 76; i++){
		wprintw(keywin, " ");
	}
	wrefresh(keywin);
}

/*
  Função: Inicializa janela de mensagens (init_msg_win)
        Objetivo:
            Criar a borda para a janela de mensagens

        Parâmetros:
            messages - a própria janela de mensagens
*/
void init_msg_win(WINDOW* messages){
	box(messages, 0, 0);
	wrefresh(messages);
}

/*
 Função: Limpar janela de mensagens (clear_message)
       Objetivo:
           Manter a janela de mensagens sempre de boa aparência

       Parâmetros:
           messages - janela onde serão colocadas as mensagens, precisa ser
                      diferente de nula
*/
void clear_message(WINDOW* messages){
	int i;
	wmove(messages, 1, 1);
	for(i = 0; i < 40; i++){
		wprintw(messages, " ");
	}
	wrefresh(messages);
}

/*
 Função: Imprimir mensagens (print_message)
       Objetivo:
           Manter o usuário atualizado quanto a situação atual do jogo

       Parâmetros:
           messages - janela onde serão mostradas as mensagens, precisa ser
                      diferente de nula
           msg      - inteiro que indica que mensagem deverá ser impressa na
                      janela
*/
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

/*
  Função: Jogar modo PVP (play_pvp)
        Objetivo:
            É umas das funções mais importantes de todo o projeto, nela o
            usuário poderá jogar contra outro jogador.
            Seu principal objetivo é manter a relação entre usuário e o
            programa

        Parâmetros:
           boardwin - janela onde está o Tabuleiro, de forma gráfica, precisa
                      ser diferente de nulo
           keywin   - janela onde estão as dicas de teclas e atalhos e onde é
                      digitada a notação algébrica
           messages - janela com as mensagens ao usuário
           board    - tabuleiro guardado na memória (não gráfico)
*/
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
									/* Recria o tabuleiro com as novas posições */
									InitBoard(boardwin, board);
									wrefresh(boardwin); /* Recarrega o tabuleiro */
								}
							else
								{
									print_message(messages, INVALID_MOVE);
								}
						}
						
				} /* Choide == j */
			else if(choice == 'q')
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
							else if(choice == 'n'){ /* Ele escolheu continuar */
								clear_message(messages);
								print_message(messages, CONTINUE_GAME);
							}
						}
				} /* choice == 's' */
		}  /* while(!finished) */
} /* Modo PVP */
