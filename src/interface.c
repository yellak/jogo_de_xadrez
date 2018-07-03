#include "../include/interface.h"

WINDOW* MakeBoardWin(void)
{
	WINDOW* boardwin = newwin(YLIMIT*2 + 1, XLIMIT*4 + 1, BOARDY, BOARDX);
	return boardwin;
}

WINDOW* MakeYaxisWin(void)
{
	WINDOW* yaxis = newwin(YLIMIT*2 + 1, 2, BOARDY, 0);
	return yaxis;
}

WINDOW* MakeXaxisWin(void)
{
	WINDOW* xaxis = newwin(1, XLIMIT*4 + 1, BOARDY + YLIMIT*2 + 1, BOARDX);
	return xaxis;
}

WINDOW* MakeKeyWin(void)
{
	WINDOW* keywin = newwin(4, 78, BOARDY + 2*YLIMIT + 2, 1);
	return keywin;
}

WINDOW* MakeMsgWin(void)
{
	WINDOW* messages = newwin(3, 42, BOARDY + 2*YLIMIT - 2, BOARDX + 4*XLIMIT + 3);
	return messages;
}

WINDOW* MakeHelpWin(void)
{
	WINDOW* helpwin = newwin(YLIMIT*2 - 3, 42, BOARDY, BOARDX + 4*XLIMIT + 3);
	return helpwin;
}

void TranslateCoord(int yscreen, int xscreen, int* yboard, int* xboard)
{
	int line, column; /* Contadores */
	int yaux, xaux;	/* Auxiliares para tradução */
	int minyaux = 5000, minxaux = 5000;

	/* Retirando o excesso causado pelas bordas */
	yscreen -= BOARDY;
	xscreen -= BOARDX;

	for(line = 0; line < 8; line++)
		{
			yaux = abs((line*YOFFSET) + 1 - yscreen);
			if(yaux < minyaux){
				minyaux = yaux;
				*yboard = line;
			}
		}

	for(column = 0; column < 8; column++)
		{
			xaux = abs((column*XOFFSET) + 2 - xscreen);
			if(xaux < minxaux){
				minxaux = xaux;
				*xboard = column;
			}
		}
} /* TranslateCoord() */

/*
 Função: Verificar o turno (verify_turn)
       Objetivo:
           Verificar se o turno atual do jogo é o turno da peça que deverá ser
           movimentada

       Parâmetros:
           board    - Tabuleiro atual do jogo, deverá já está alocado
           movement - Movimento a ser feito pelo jogador, já alocado
           turn     - Turno atual do jogo

      Saída:
           true  - Se o turno é o da cor da peça a ser movimentada
           false - Se não é o turn da cor da peça a ser movimentada
*/
int verify_turn(TBoard* board, Move* movement, int turn){
	if(movement != NULL)
		{
			int y_pos = movement->origin[0];
			int x_pos = movement->origin[1];
			char piece = board->Board[y_pos][x_pos];

			if(turn == WHITES_TURN) /* Vez das brancas */
				{
					if(piece > '\\'){	/* A peça é branca */
						return true;
					}
					else{
						return false;
					}
				}
			else  /* Se for a vez das pretas */
				{
					if(piece < '\\'){	/* A peça é preta */
						return true;
					}
					else{
						return false;
					}
				}
		}
	else
		{
			return false;
		}
} /* verify_turn() */

/*
 Função: Mudar a/o vez/turno (change_turn)
       Objetivo:
           Mudar de quem é o turno atual do jogo, por exemplo, se as pretas
           acabaram de jogar agora o turno é das brancas

       Parâmetros:
           turn - Turno atual

       Saída:
          new_turn - O novo turno do jogo*/
int change_turn(int turn){
	if(turn == BLACKS_TURN){
		return WHITES_TURN;
	}
	else{
		return BLACKS_TURN;
	}
}

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

	wrefresh(boardwin);
	
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

	wrefresh(yaxis);
	wrefresh(xaxis);

} /* DrawAxis() */

/*
 Função: Inicializar a janela de ajuda
       Objetivo:
           Inicializar a janela de ajuda para o ambiente de criação de um novo
           Tabuleiro. A função não possui retorno

       Parâmetros:
           helpwin - Janela onde será inicilizada a ajuda*/
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

	mvwprintw(helpwin, 11, 1, "Começe adicionando os reis");

	/* Carregar as impressões acima */
	wrefresh(helpwin);
} /* HelpWinNewBoard() */

/* 
 Função: Criar um novo tabuleiro (CreateNewBoard)
       Objetivo:
           Criar um novo Tabuleiro a partir de um ambiente de criação onde o
           usuário poderá criar um novo Tabuleiro de sua preferência

       Saída:
           board - Tabuleiro criado pelo usuário
*/
TBoard* CreateNewBoard(void)
{
	/* Tabuleiro que será retornado */
	TBoard* board = AlocateBoard();

	/* Janelas do tabuleiro */
	WINDOW* boardwin = MakeBoardWin();
	WINDOW* yaxis = MakeYaxisWin();
	WINDOW* xaxis = MakeXaxisWin();

	/* Janela de ajuda */
	WINDOW* helpwin = MakeHelpWin();

	/* Janela onde serão impressas as mensagens para o usuário */
	WINDOW* messages = MakeMsgWin();

	/* Janela interação com o teclado do usuário */
	WINDOW* keywin = MakeKeyWin();

	int finished = false; /* Indica processo finalizado ou não */
	int choice;	/* É a tecla que o usuário apertou */
	char piece;	/* Peça a ser adicionada ou removida */

	int b_line, b_column;

	/* Habilitando o reconhecimento do mouse */
	mousemask(BUTTON1_PRESSED, NULL);
	keypad(stdscr, TRUE);

	MEVENT event; /* Guarda as coordenadas do clique do mouse */


	/* Carregando as janelas */
	refresh();

	/* Colocando a janela com atalhos */
	write_keys_help(keywin, CREATING);

	/* Desenhando um tabuleiro */
	DrawBoard(boardwin);
	DrawAxis(yaxis, xaxis);

	/* Mostrando as ajudas */
	HelpWinNewBoard(helpwin);
	init_msg_win(messages);	/* Menu de mensagens */

	/* Inicializando um tabuleiro vazio */
	StartEmptyBoard(board);

	while(!finished)
		{
			choice = getch();
			clear_keywin(keywin);

			switch(choice)
				{
				case 'a': /* Usuário escolheu adicionar uma peça */
					{
						print_message(messages, INSERT_PIECE);

						/* Adiquirindo a peça do usuário */
						curs_set(1);
						echo();
						wmove(keywin, 2, 1);
						piece = wgetch(keywin); /* Aquirindo a peça do usuário */
						noecho();
						curs_set(0);

						/* Verificando se a peça realmente é uma peça de xadrez */
						if(valid_piece(piece) == true)
							{
								print_message(messages, CLICK); /* Avisar o usuário de clicar na tela */
						
								choice = getch(); /* Pegando o clique do mouse */

								if(choice == KEY_MOUSE) /* Usuário apertou o botão esquerdo do mouse */
									{
										if(getmouse(&event) == OK)
											{
												/* Traduzindo das coordenadas da tela para as do tabuleiro */
												TranslateCoord(event.y, event.x, &b_line, &b_column);
												/* Inserindo a peça no tabuleiro */
												InsertPiece(board, piece, b_line, b_column);

												if(ValidBoard(board) || DontHaveMinimun(board))
													{
														InitBoard(boardwin, board);
														wrefresh(boardwin);
													}
												else /* O tabuleiro não é válido */
													{
														RemovePiece(board, b_line, b_column);
														print_message(messages, INVALID_BOARD);
													}
											} /* getmouse() OK */
									} /* if(choice == KEY_MOUSE) */

								else  /* Usuário não utilizou o mouse */
									{
										print_message(messages, USE_MOUSE);
									}
										
							}
						else
							{
								/* O usuário tentou adicionar uma peça que não devia */
								print_message(messages, INVALID_PIECE);
							}
					
						break;
					}  /* case 'a' */

				case 'r': /* Usuário escolheu remover uma peça */
					{
						print_message(messages, CLICK);
						choice = getch(); /* Pegando o teclado */

						if(choice == KEY_MOUSE)
							{
								if(getmouse(&event) == OK)
									{
										/* Traduzindo das coordenadas da tela para as do tabuleiro */
										TranslateCoord(event.y, event.x, &b_line, &b_column);

										/* Fazendo backup da peça na posição */
										piece = WhatPiece(board, b_line, b_column);
										/* Removendo a peça */
										RemovePiece(board, b_line, b_column);

										if(ValidBoard(board) || DontHaveMinimun(board))
											{
												InitBoard(boardwin, board);
												wrefresh(boardwin);
											}
										else /* Tabuleiro não é válido */
											{
												InsertPiece(board, piece, b_line, b_column);
												print_message(messages, INVALID_BOARD);
											}
									} /* getmouse( ... ) == OK */
							} /* choice == KEY_MOUSE */
						else
							{
								print_message(messages, USE_MOUSE);
							}
					} /* case 'r' */
					break;
					
				case 'q': /* Usuário escolheu sair do jogo */
					print_message(messages, ARE_YOU_SURE);
					choice = 'a';
					while((choice != 's') && (choice != 'n'))
						{
							choice = getch();
							if(choice == 's'){
								free(board);
								board = NULL;
								finished = true;
							}
							else if(choice == 'n'){
								print_message(messages, CONTINUE);
							}
						} /* while(choice != ... ) */
					break;
					
				case 'f':
					finished = true;
					break;
				}
		}

	delwin(messages);
	delwin(boardwin);
	delwin(yaxis);
	delwin(xaxis);
	delwin(keywin);
	delwin(helpwin);

	return board;
} /* CreateNewBoard() */

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
TBoard* MenuGetBoard(void)
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
					/* Atualizando as opções */
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

	switch(highlight)
		{
		case STD_BOARD:
			board = AlocateBoard();
			StartEmptyBoard(board);
			StartStandardBoard(board);
			break;

		case SAVED_BOARD:
			break;
			
		case NEW_BOARD:
			clear();
			board = CreateNewBoard();
			break;

		case EXIT_GAME:
			board = NULL;
			break;
		}

	delwin(menu);
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
	if(wintype == GAMING) /* Jogando normalmente */
		{
			mvwprintw(keywin, 1, 1, "q-Sair");
			mvwprintw(keywin, 1, 11, "j-Jogada pela notação");
			mvwprintw(keywin, 1, 37, "h-Ajuda");
			mvwprintw(keywin, 1, 48, "d-deletar jogada");
		}
	else if(wintype == CREATING) /* Menu de criação de tabuleiro */
		{
			mvwprintw(keywin, 1, 1, "q-Sair");
			mvwprintw(keywin, 1, 9, "a-Adicionar");
			mvwprintw(keywin, 1, 24, "r-Remover");
			mvwprintw(keywin, 1, 36, "f-Finalizar");
		}
	
	/* Carregando a janela no terminal */
	wrefresh(keywin);
} /* write_keys_help() */

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
	clear_message(messages);
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
		case WHITE_MOVE:
			wprintw(messages, "Vez das brancas");
			break;
		case BLACK_MOVE:
			wprintw(messages, "Vez das pretas");
			break;
		case NOTBLACKSMOVE:
			wprintw(messages, "Não é a vez das pretas");
			break;
		case NOTWHITESMOVE:
			wprintw(messages, "Não é a vez das brancas");
			break;
		case CONTINUE:
			wprintw(messages, "Continuando...");
			break;
		case INSERT_PIECE:
			wprintw(messages, "Qual a peça a ser adicionada?");
			break;
		case CLICK:
			wprintw(messages, "Clique na posição desejada");
			break;
		case INVALID_PIECE:
			wprintw(messages, "Peça inválida");
			break;
		case INVALID_BOARD:
			wprintw(messages, "Tabuleiro inválido");
			break;
		case USE_MOUSE:
			wprintw(messages, "Por favor, utilize o mouse");
			break;
		}
	
	wrefresh(messages);
} /* print_message() */

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
	/* Inteiro que indicará de quem é a vez de jogar */
	int turn = WHITES_TURN;
	/* Variáveis para movimento, elas não são intuitivas para que
       haja uma economia de espaço mais a frente, elas também são melhor
       apresentadas mais a frente */
	int ol, oc, dl, dc;
	/* Indica qual era o tabuleiro antigo */
	TBoard* old_board = AlocateBoard();

	copy_boards(old_board, board);


	keypad(stdscr, TRUE);

	while(!finished)
		{
			/* Pegar a tecla que o usuário digitar */
			choice = getch();

			/* Mostrando de quem é a vez de jogar */
			if(turn == WHITES_TURN){
				print_message(messages, WHITE_MOVE);
			}
			else{
				print_message(messages, BLACK_MOVE);
			}

			if(choice == 'j') /* Tecla j */
				{
					/* Salvando tabuleiro anterior */
					copy_boards(old_board, board);
					
					echo();	/* Deixar as teclas aparecerem na tela */
					curs_set(1); /* Fazer o cursor aparecer */
					wmove(keywin, 2, 1);
					/* Obter a notação de movimento do usuário */
					wgetstr(keywin, chess_move); /* Pegar a jogada */
					clear_keywin(keywin);
					curs_set(0); /* Tirar o cursor */
					noecho(); /* Desabilitar teclas aparecerem na tela */

					/* Traduzindo o notação para elemento de movimento */
					movement = algebraic_translate(chess_move);

					if(verify_turn(board, movement, turn) == true)
						{
							/* Agora é a vez do próximo jogador */
							turn = change_turn(turn);
					
							ol = movement->origin[0]; /* origin line */
							oc = movement->origin[1]; /* origin column */
							dl = movement->destiny[0]; /* destiny line */
							dc = movement->destiny[1]; /* destiny column */
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
									
							free(movement);
						} /* if(verify_turn( ... )) */
					else  /* Não é a vez da peça que o usuário tentou mexer */
						{
							if(movement == NULL){
								print_message(messages, INVALID_SINTAX);
							}
							else if(turn == WHITES_TURN){
								print_message(messages, NOTBLACKSMOVE);
							}
							else{
								print_message(messages, NOTWHITESMOVE);
							}
						} /* Não é a vez da peça que o jogador escolheu */
						
				} /* Choide == j */
			
			else if(choice == 'q') /* Sair do jogo */
				{
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
								print_message(messages, CONTINUE_GAME);
							}
						}
				} /* choice == 'q' */

			else if(choice == 'd') /* Escolheu deletar última jogada */
				{
					/* Copiando o tabuleiro antigo no novo */
					copy_boards(board, old_board);
					/* Mudando a vez de quem joga */
					turn = change_turn(turn);
					/* Refazendo o tabuleiro na interface */
					InitBoard(boardwin, board);
					wrefresh(boardwin);
				}
		}  /* while(!finished) */
} /* Modo PVP */
