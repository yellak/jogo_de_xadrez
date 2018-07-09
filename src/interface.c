#include "../include/interface.h"

/*
 Função: Criar janela do tabuleiro (MakeBoardWin)
       Objetivo:
           Inicializar a janela onde estará o Tabueleiro

       Saída:
           boardwin - Ponteiro para a janela do tabuleiro alocada
*/
WINDOW* MakeBoardWin(void)
{
	WINDOW* boardwin = newwin(YLIMIT*2 + 1, XLIMIT*4 + 1, BOARDY, BOARDX);
	return boardwin;
}


/*
 Função: Criar janela do eixo Y (MakeYaxisWin)
       Objetivo:
           Inicializar a janela onde estará o eixo X

       Saída:
           yaxis - Ponteiro para a janela alocada
*/
WINDOW* MakeYaxisWin(void)
{
	WINDOW* yaxis = newwin(YLIMIT*2 + 1, 2, BOARDY, 0);
	return yaxis;
}


/*
 Função: Criar janela do eixo X (MakeXaxisWin)
       Objetivo:
           Inicializar a janela do eixo X

       Saída:
           xaxis - Ponteiro para a janela do eixo X
*/
WINDOW* MakeXaxisWin(void)
{
	WINDOW* xaxis = newwin(1, XLIMIT*4 + 1, BOARDY + YLIMIT*2 + 1, BOARDX);
	return xaxis;
}


/* 
 Função: Criar janela do menu de atalhos (MakeKeyWin)
       Objetivo:
           Inicilizar a janela do menu de atalhos. Este é o menu onde o usuário
           digita os comandos quando ele vai mover uma peça pela notação

       Saída:
           keywin - Ponteiro para a janela alocada
*/
WINDOW* MakeKeyWin(void)
{
	WINDOW* keywin = newwin(4, 79, BOARDY + 2*YLIMIT + 2, 1);
	return keywin;
}


/*
 Função: Criar a janela de mensagens (MakeMsgWin)
       Objetivo:
           Inicializar a janela de mensagens para o usuário

       Saída:
           messages - Ponteiro para a janela de mensagens
*/
WINDOW* MakeMsgWin(void)
{
	WINDOW* messages = newwin(3, 42, BOARDY + 2*YLIMIT - 2, BOARDX + 4*XLIMIT + 3);
	return messages;
}


/* 
 Função: Criar janela de ajuda (MakeHelpWin)
       Objetivo:
           Inicializar a janela de ajuda para o usuário

       Saída:
           helpwin - Ponteiro para a janela de ajuda
*/
WINDOW* MakeHelpWin(void)
{
	WINDOW* helpwin = newwin(YLIMIT*2 - 3, 42, BOARDY, BOARDX + 4*XLIMIT + 3);
	return helpwin;
}


/* 
 Função: Traduzir coordenadas para coordenadas do tabuleiro em memória
       Objetivo:
           Esta função irá receber as coordenadas em que o usuário tenha
           digitado na tela e irá traduzí-las para as coordenadas do tabuleiro
           armazenado em memória

       Saída:
           yboard - Coordenada Y traduzida
           xboard - Coordenada X traduzida

       Assertivas de entrada:
           0 <= yscreen < 5000
           0 <= xscreen < 5000

		   * A função depende de muito de como foi desenhado o tabuleiro, dessa
             forma, mudanças no design do tabuleiro implicam numa análise desta
             função para saber se ela precisa ser adapatada ao novo design

      Assertivas de saída:
           0 <= yboard <= 7
           0 <= xboard <= 7
*/
void TranslateCoord(int yscreen, int xscreen, int* yboard, int* xboard)
{
	int line, column; /* Contadores */
	int yaux, xaux;	/* Auxiliares para tradução */
	/* Coordenadas válidas mais próximas até a posição que o usuário digitou */
	int minyaux = 5000, minxaux = 5000;

	/* Retirando o excesso causado pelas bordas */
	yscreen -= BOARDY;
	xscreen -= BOARDX;

	/* Loop para encontrar qual a coodernada y válida mais próxima de onde o
       usuário digitou */
	for(line = 0; line < 8; line++)
		{
			yaux = abs((line*YOFFSET) + 1 - yscreen);
			if(yaux < minyaux){
				minyaux = yaux;
				*yboard = line;
			}
		}

	/* Mesmo objetivo do loop anterior mas para a coordenada x */
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
 Função: Mostrar as dicas (GiveHint)
       Objetivo:
           Mostrar na tela as 5 melhores dicas de movimento para o Usuário

       Parâmetros:
          helpwin - Janela de ajuda
          board   - Tabuleiro que será considerado para as dicas
          turn    - Indica quem é o dono do turno e que vai receber as dicas */
void GiveHint(WINDOW* helpwin, TBoard* board, int turn)
{
	int ol, oc, dl, dc;
	Tree* decisions; /* Árvore decisões */
	ListOfMoves* possiblemoves;	/* Lista com os melhores movimentos para o jogador */
	NodeList* aux;
	char chess_move[6];
	int i; /* Contador */

	/* Criando a lista de movimentos recomendados */
	decisions = CreateMovesTree(board, turn);
	SortTree(decisions, turn);
	possiblemoves = Best_Plays(decisions, decisions->root->n_child);
	aux = possiblemoves->first;

	/* Limpando a área */
	for(i = 1; i <=5; i++){
		mvwprintw(helpwin, i + 2, 1, "         ");
	}
	wrefresh(helpwin);

	/* Colocando as dicas */
	for(i = 1; i <= 5; i++, aux = aux->next)
		{
			if(aux == NULL){
				break;
			}
			Move2Algebraic(&aux->play, chess_move);
			mvwprintw(helpwin, i + 2, 1, "%d. %s", i, chess_move);
		}

	FreeTreeNodes(decisions->root);
	free(decisions);
	DeleteListOfMoves(possiblemoves);
	wrefresh(helpwin);
}


/*
 Função: Mostrar legenda das peças na janela de ajuda (HelpWinPVP)
       Objetivo:
           Mostrar legenda das peças do tabuleiro na janela de ajuda

       Parâmetros:
          helpwin - Janela de ajuda onde seram colocadas as legendas */
void HelpWinPVP(WINDOW* helpwin)
{
	/* Destacando a janela */
	box(helpwin, 0, 0);

	/* Mostrando o título */
	mvwprintw(helpwin, 1, 11, "Legenda das peças");

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
	
	wrefresh(helpwin);
}


/* 
   Função: Inicializar a janela de ajuda do PVE
         Objetivo:
             Inicializar a janela de ajuda do PVE com o básico

         Parâmetros:
             helpwin - Janela de ajuda */
void HelpWinPVE(WINDOW* helpwin)
{
	/* Destacando a janela */
	box(helpwin, 0, 0);

	mvwprintw(helpwin, 1, 1, "Dicas de movimento:");

	wrefresh(helpwin);
}


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

	int b_line, b_column; /* Posições traduzidas da posição onde o usuário clicou */

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

												if(ValidBoard(board) || HaveMinimun(board))
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

										if(ValidBoard(board) || HaveMinimun(board))
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
					if(ValidBoard(board)){
						finished = true;
					}
					else{
						print_message(messages, INVALID_BOARD);
					}
					break;
				}
		}

	delwin(messages);
	delwin(boardwin);
	delwin(yaxis);
	delwin(xaxis);
	delwin(keywin);
	delwin(helpwin);

	board = VerifyCheck(board, WHITE);
	board = VerifyCheck(board, BLACK);

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
           Mostra o menu em o usuário escolhe que tipo de tabuleiro ele vai querer usar
       
       Saída:
           board - Tabuleiro pronto que o usuário esolheu
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
	char saved_board[] = "save/board.txt";

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
			board = AlocateBoard();
			RecoverBoardFromFile(board, saved_board);
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
			mvwprintw(keywin, 1, 37, "s-Salvar");
			mvwprintw(keywin, 1, 48, "d-Deletar jogada");
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
			wprintw(messages, "Vez das brancas (Minúsculas)");
			break;
		case BLACK_MOVE:
			wprintw(messages, "Vez das pretas (maiúsculas)");
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
		case NOTPIECE:
			wprintw(messages, "Posição vazia");
			break;
		case CLICK_DESTINY:
			wprintw(messages, "Clique no destino da peça");
			break;
		case OUT_RANGE:
			wprintw(messages, "Posição fora do tabuleiro");
			break;
		case SAVED_GAME:
			wprintw(messages, "Jogo salvo");
			break;
		case W_CHECK:
			wprintw(messages, "Xeque no rei branco");
			break;
		case B_CHECK:
			wprintw(messages, "Xeque no rei preto");
			break;
		case WHITE_WON:
			wprintw(messages, "As brancas venceram");
			break;
		case BLACK_WON:
			wprintw(messages, "As pretas venceram");
			break;
		case WANNA_SAVE:
			wprintw(messages, "Você deseja salvar? (s/n)");
			break;
		case GIVE_A_PIECE:
			wprintw(messages, "A qual peça evoluir o peão?");
			break;
		case YOURCOLOR:
			wprintw(messages, "Qual cor você escolhe? (p/b)");
			break;
		}
	
	wrefresh(messages);
} /* print_message() */


/* 
 Função: Destacar peça (reverse_color_in_board)
       Objetivo:
           Destaca na interface a posição dada no tabuleiro 
       
       Parâmetros:
           boardwin - Janela do tabuleiro
           board    - Tabuleiro referência
           line     - Posição Y a ser destacada (referente a board e não a tela)
           column   - Posição X a ser destacada

       Saída:
          true  - Se tinha uma peça na posição dada
          false - Se não tiha uma peça na posição dada
*/
int reverse_color_in_board(WINDOW* boardwin, TBoard* board, int line, int column)
{
	wmove(boardwin, (line * YOFFSET) + 1, (XOFFSET * column) + 2);
	if(board->Board[line][column] != BLANK)
		{
			wattron(boardwin, A_REVERSE);
			wprintw(boardwin, "%c", board->Board[line][column]);
			wattroff(boardwin, A_REVERSE);
			wrefresh(boardwin);

			return true;
		}

	return false;
}


/* 
 Função: Obter o movimento do usuário (GetMovement)
       Objetivo:
           Obtém do usuário um movimento através da notação

       Parâmetros:
           keywin     - Janela onde está os atalhos
           chess_move - String onde será colocada a jodada do jogador

       Saída:
           movement - Movimento traduzido do jogador para o tipo Move*
*/
Move* GetMovement(WINDOW* keywin, char chess_move[])
{
	Move* movement;
	
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

	return movement;
}

/* 
 Função: Mostrar vencedor do jogo (print_winner)
       Objetivo:
           Mostra na tela quem é o jogador vencedor da partida
       
       Parâmetros:
           helpwin - Janela de ajuda
           who     - Indica quem foi o vencedor do jogo */
void print_winner(WINDOW* helpwin, int who)
{
	/* Limpando a janela */
	wmove(helpwin, 11, 12);
	wprintw(helpwin, "                   ");
	wrefresh(helpwin);

	wmove(helpwin, 11, 12);
	if(who == WHITE){
		wprintw(helpwin, "Brancas Venceram!");
	}
	else{
		wprintw(helpwin, "Pretas Venceram!");
	}

	wrefresh(helpwin);
}


/* 
 Função: Mostrar a vez
       Objetivo:
           Mostra de quem é a vez de jogar na partida
 
       Parâmetros:
           helpwin - Janela de ajuda
           turn    - Indica de quem é o turno (vez de jogar) */
void print_turn(WINDOW* helpwin, int turn)
{
	/* Limpando a janela */
	wmove(helpwin, 11, 12);
	wprintw(helpwin, "                   ");
	wrefresh(helpwin);

	/* Escrevendo de quem é a vez */
	wmove(helpwin, 11, 12);
	if(turn == WHITES_TURN){
		wprintw(helpwin, "Vez das brancas");
	}
	else{
		wprintw(helpwin, "Vez das pretas");
	}

	wrefresh(helpwin);
}


/* 
 Função: Verifar salvamento
       Objetivo:
           Pergunta ao usuário se ele quer salvar o jogo

       Parâmetros:
           messages - Janela de mensagens

       Saída:
           true  - Se o usuário quiser salvar o jogo
           false - Se o usuário não quiser salvar */
int wanna_save(WINDOW* messages)
{
	int choice;
	print_message(messages, WANNA_SAVE);

	do{
		choice = getch();
	} while(choice != 's' && choice != 'n');

	if(choice == 's'){
		return true;
	}
	else{
		return false;
	}
}


/* 
 Função: Verificar promoção do Peão 
       Objetivo:
         Verifica se existe algum peão para ser promovido
         Ela também irá promover o peão de acordo com a escolha do jogador

	   Parâmetros:
         messages - Janela de mensagens
         board    - Tabuleiro atual do jogo

       Saída:
         true  - Se tinha um peão para promover
         false - Se não tinha um peão para promover
        */
int verify_evolve_pawn(WINDOW* messages, TBoard* board)
{
	int y_pos, x_pos, i;
	int whos;
	int found = false; /* Indica se tem um peão para ser evoluido */
	char piece;

	/* Loop para procurar o peão */
	for(i = 0; i < 8; i++)
		{
			piece = board->Board[0][i];
			if(piece == W_PAWN)
				{
					found = true;
					x_pos = i;
					y_pos = 0;
					whos = WHITE;
					break;
				}
			else
				{
					piece = board->Board[7][i];
					if(piece == B_PAWN)
						{
							found = true;
							x_pos = i;
							y_pos = 7;
							whos  = BLACK;
							break;
						}
				}
		} /* for(i = 0; i < 8; i++) */

	if(found == true)
		{
			piece = 'a';
			print_message(messages, GIVE_A_PIECE);

			if(whos == WHITE)
				{
					while(!valid_piece(piece) || piece == B_KING || piece == W_KING || piece < BLANK)
						{
							piece = getch();
							if(!valid_piece(piece) || piece == B_KING || piece == W_KING || piece < BLANK)
								{
									print_message(messages, INVALID_PIECE);
								}
						}
				} /* if(whos == WHITE) */
			else /* Peão preto */
				{
					while(!valid_piece(piece) || piece == B_KING || piece == W_KING || piece > BLANK)
						{
							piece = getch();
							if(!valid_piece(piece) || piece == B_KING || piece == W_KING || piece > BLANK)
								{
									print_message(messages, INVALID_PIECE);
								}
						}
				} /* Peão preto */
				
			board->Board[y_pos][x_pos] = piece;
			board->Weight += GetValue(piece);
			if(ColorPiece(piece) == WHITE){
				board->Weight -= GetValue(piece);
			}
			else{
				board->Weight -= GetValue(piece);
			}
		}

	return found;
}


/* 
 Função: Mover a peça na interface gráfica
       Objetivo:
           Move a peça e faz todas as verificações pela própria interface

       Parâmetros:
           boardwin - Janela do tabuleiro
           messages - Janela de mensagens
           board    - Tabuleiro a ser modificado
           turn     - Indica de quem é a vez de jogar
           movement - Movimento a ser feito

      Saída:
          turn - Indicando de quem é a vez de jogar
*/
int UI_MOVE_PIECE(WINDOW* boardwin, WINDOW* messages, TBoard* board, int turn, Move* movement)
{
	int ol, oc, dl, dc; /* Indicam as posições de origem e destino */
	int boolean;
	
	if(verify_turn(board, movement, turn) == true)
		{			
			ol = movement->origin[0]; /* origin line */
			oc = movement->origin[1]; /* origin column */
			dl = movement->destiny[0]; /* destiny line */
			dc = movement->destiny[1]; /* destiny column */

			board = VerifyCheck(board, BLACK);
			board = VerifyCheck(board, WHITE);

			if(VerifyValidMovement(board, ol, oc, dl, dc) == 1)
				{
					/* Agora é a vez do próximo jogador */
					turn = change_turn(turn);
			
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
							print_message(messages, OUT_RANGE);
						}
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

	return turn;
} /* UI_MOVE_PIECE */


/* 
 Função: Mover peça pelo mouse
       Objetivo:
           Move a peça através do mouse do usuário
       
       Parâmetros:
           boardwin  - Janela do tabuleiro
           messages  - Janela de mensagens
           board     - Tabuleiro a ser modificado
           turn      - Indica de quem é a vez de jogar agora
           event     - Evento de mouse 
           pastmoves - Lista de movimentos passados para o arquivo PGN

       Saída:
           turn - Indicando de quem é a vez de jogar agora */
int UI_MOUSE_MOVE(WINDOW* boardwin, WINDOW* messages, TBoard* board, int turn, MEVENT event, ListPastMoves* pastmoves)
{
	/* Movimento do jogador */
	Move* movement = (Move*) malloc(sizeof(Move));
	/* Coordenadas traduzidas da posição onde o mouse clicou */
	int b_line, b_column;
	/* Coordenadas de origem e destino quando o usuário usar o mouse */
	int ol, oc, dl, dc;
	/* Boleano para fins diversos */
	int boolean;
	/* Tecla que o usuário apertou */
	int choice;
	char chess_move[6];
	
	/* Traduzindo as coordenadas de onde o usuário digitou */
	TranslateCoord(event.y, event.x, &b_line, &b_column);
							
	/* Marcando a posição no tabuleiro onde o usuário apertou */
	if(reverse_color_in_board(boardwin, board, b_line, b_column) == true)
		{
			/* Passando as coordenadas de origem */
			movement->origin[0] = b_line;
			movement->origin[1] = b_column;

			if(verify_turn(board, movement, turn) == true)
				{
					/* Avisar para o usuário clicar no destino */
					print_message(messages, CLICK_DESTINY);

					/* Pegar a posição destino */
					do{
						choice = getch();
					} while(choice != KEY_MOUSE);

					if(getmouse(&event) == OK)
						{
							TranslateCoord(event.y, event.x, &b_line, &b_column);

							/* Passando as coordenadas de destino */
							movement->destiny[0] = b_line;
							movement->destiny[1] = b_column;
						}

					ol = movement->origin[0]; /* origin line */
					oc = movement->origin[1]; /* origin column */
					dl = movement->destiny[0]; /* destiny line */
					dc = movement->destiny[1]; /* destiny column */

					board = VerifyCheck(board, BLACK);
					board = VerifyCheck(board, WHITE);

					if(VerifyValidMovement(board, ol, oc, dl, dc) == 1)
						{
									
							boolean = MovePiece(board, ol, oc, dl, dc);

							if(boolean == 0) /* Jogada válida */
								{
									/* Recria o tabuleiro com as novas posições */
									InitBoard(boardwin, board);
									wrefresh(boardwin); /* Recarrega o tabuleiro */

									/* Colocando o movimento na lista para salvar o PGN */
									Move2Algebraic(movement, chess_move);
									AddListPM(pastmoves, chess_move);

									/* Mudando a vez do jogador */
									turn = change_turn(turn);
								}
							else
								{
									print_message(messages, OUT_RANGE);
								}
						}
					else /* Movimento não é válido */
						{
							print_message(messages, INVALID_MOVE);
							/* Recarregando o tabuleiro para limpar a sujeira */
							InitBoard(boardwin, board);
							wrefresh(boardwin);
						}
				}
			else /* Não é a vez da peça que o usuário tentou mexer */
				{
					/* Recarregando o tabuleiro na tela */
					InitBoard(boardwin, board);
					wrefresh(boardwin);
					
					if(turn == WHITES_TURN){
						print_message(messages, NOTBLACKSMOVE);
					}
					else{
						print_message(messages, NOTWHITESMOVE);
					}
				} /* Não é a vez da peça que o usuário tentou mexer */
		} /* if(reverse_color_in_board...) */
	else{
		print_message(messages, NOTPIECE);
	}

	return turn;
} /* UI_MOUSE_MOVE */

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
	/* Movimento do jogador */
	Move* movement;
	/* Inteiro que indicará de quem é a vez de jogar */
	int turn = WHITES_TURN, old_turn = BLACKS_TURN;
	/* Indica qual era o tabuleiro antigo */
	TBoard* old_board = AlocateBoard();
	/* Evento de clicar numa tecla do mouse */
	MEVENT event;
	/* janela de ajuda */
	WINDOW* helpwin = MakeHelpWin();

	/* Inicializando variáveis necessárias para salvar o jogo */
	char txtboard[] = "save/board.txt";
	char pgnboard[] = "save/board.pgn";
	ListPastMoves* pastmoves = StartListPM();

	/* Iniciando janela de ajuda */
	HelpWinPVP(helpwin);

	/* Guardando o tabuleiro para o caso do usuário querer deletar último movimento */
	copy_boards(old_board, board);

	/* Reconhecimento do mouse */
	mousemask(BUTTON1_PRESSED, NULL);
	keypad(stdscr, TRUE);

	/* Verificando se o tabuleiro inicial já está com cheque */
	board = VerifyCheck(board, BLACK);
	if(board->BlackCheck == CHECK){
		turn = BLACKS_TURN;
	}

	while(!finished)
		{
			/* Mostrando de quem é a vez de jogar */
			print_turn(helpwin, turn);

			/* Verificando se tem xeque no jogo */
			if(turn == WHITES_TURN)
				{
					board = VerifyCheck(board, WHITE);
					if(board->WhiteCheck == CHECK){
						/* Mostrando que as brancas fizeram xeque */
						print_message(messages, W_CHECK);
						if(VerifyCheckMate(board, WHITE) == NULL)
							{
								print_winner(helpwin, BLACK);
								if(wanna_save(messages)){
									SaveBoardFile(board, txtboard); /* Arquivo txt */
									SavePGNFile(pastmoves, pgnboard); /* Arquivo pgn */
									print_message(messages, SAVED_GAME);
								}
								break;
							} /* if(VerifyCheckMate...) */
					} /* if(board->whi..) */
				}
			else /* Vez das pretas */
				{
					board = VerifyCheck(board, BLACK);
					if(board->BlackCheck == 1){
						/* Mostrando que as pretas fizeram xeque */
						print_message(messages, B_CHECK);

						if(VerifyCheckMate(board, BLACK) == NULL)
							{
								print_winner(helpwin, WHITE);
								if(wanna_save(messages)){
									SaveBoardFile(board, txtboard);
									SavePGNFile(pastmoves, pgnboard);
									print_message(messages, SAVED_GAME);
								}
								break;
							}
					} /* if(board->Blac...) */
				}
			
			/* Pegar a tecla que o usuário digitar */
			choice = getch();

			clear_message(messages);

			if(choice == 'j') /* Tecla j - jogada pela notação */
				{
					/* Salvando tabuleiro anterior */
					copy_boards(old_board, board);

					/* Obtendo o movimento do jogador pela notação */
					movement = GetMovement(keywin, chess_move);
					
					old_turn = turn;

					/* Movendo a peça */
					turn = UI_MOVE_PIECE(boardwin, messages, board, turn, movement);

					if(turn != old_turn)
						{
							AddListPM(pastmoves, chess_move);
						}
						
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
								FreeListPM(pastmoves);
								finished = true; /* Fim de jogo */
							}
							else if(choice == 'n'){ /* Ele escolheu continuar */
								print_message(messages, CONTINUE_GAME);
							}
						}
				} /* choice == 'q' */

			else if(choice == KEY_MOUSE) /* Usuário apertou o botão esquerdo do mouse */
				{
					/* Salvando tabuleiro anterior */
					copy_boards(old_board, board);

					/* Salvando o movimento anterior */
					old_turn = turn;
					
					if(getmouse(&event) == OK)
						{
							/* Fazendo o movimento para o mouse */
							turn = UI_MOUSE_MOVE(boardwin, messages, board, turn, event, pastmoves);
						}
				} /* else if(choice == KEY_MOUSE) */

			else if(choice == 'd') /* Escolheu deletar última jogada */
				{
					/* Removendo a jogada da lista de jogadas já feitas */
					RemoveLastListPM(pastmoves);
					/* Copiando o tabuleiro antigo no novo */
					copy_boards(board, old_board);
					/* Mudando a vez de quem joga */
					turn = change_turn(turn);
					/* Refazendo o tabuleiro na interface */
					InitBoard(boardwin, board);
					wrefresh(boardwin);
				}

			else if(choice == 's')
				{
					SaveBoardFile(board, txtboard); /* Arquivo txt */
					SavePGNFile(pastmoves, pgnboard); /* Arquivo pgn */
					print_message(messages, SAVED_GAME);
				}

			if(verify_evolve_pawn(messages, board))
				{
					InitBoard(boardwin, board);
					wrefresh(boardwin);
				}
		}  /* while(!finished) */
} /* Modo PVP */


/* 
 Função: Jogar modo PVE
       Objetivo:
           Faz todo o processo do modo de jogo Jogador vs Computador
           
       Parâmetros:
           boardwin - Janela do tabuleiro
           keywin   - Janela onde estão dicas de atalho e região de interação com o teclado dele
           messages - Janela de mensagens
           board    - Tabuleiro que será utilizado */
void play_pve(WINDOW* boardwin, WINDOW* keywin, WINDOW* messages, TBoard* board)
{
	int choice;	/* Escolha do usuário */
	WINDOW* helpwin = MakeHelpWin();
	int player, machine, turn, old_turn; /* Turno do jogador, da máquina e atual do jogo */
	int finished = false; /* Indica o fim do jogo */
	TBoard* old_board = AlocateBoard(); /* Armazena a forma anterior do tabuleiro */
	char chess_move[8];	/* String do movimento que o jogador fez */
	Move* movement;	/* Movimento do jogador */
	MEVENT event; /* evento de mouse */
	Tree* decisions;
	ListOfMoves* possiblemoves;
	ListOfMoves* auxilary;
	int ol, oc, dl, dc; /* Para indicar para onde o pc vai mexer */
	int aux_color, mate = false;
	int player_moved = false;

	/* Variáveis para salvar o jogo */
	char txtboard[] = "save/board.txt";
	char pgnboard[] = "save/board.pgn";
	ListPastMoves* pastmoves = StartListPM();

	HelpWinPVE(helpwin);

	/* Adquirindo a cor que o usuário deseja ser */
	print_message(messages, YOURCOLOR);
	do{
		choice = getch();
	} while(choice != 'p' && choice != 'b');

	/* Limpando a janela de mensagens */
	clear_message(messages);

	/* Habilitando as variáveis dos movimentos */
	if(choice == 'p'){
		player = BLACKS_TURN;
		machine = WHITES_TURN;
		turn = machine;
	}
	else{
		player = WHITES_TURN;
		machine = BLACKS_TURN;
		turn = player;
	}

	/* Verificando se o tabuleiro inicial já está com cheque */
	board = VerifyCheck(board, BLACK);
	if(board->BlackCheck == CHECK){
		turn = BLACKS_TURN;
	}

	/* Armazenando o tabuleiro anterior */
	copy_boards(old_board, board);

	/* Reconhecimento do mouse */
	mousemask(BUTTON1_PRESSED, NULL);
	keypad(stdscr, TRUE);

	choice = 'a';

	while(!finished)
		{
			/* Mostrando de quem é a vez de jogar */
			print_turn(helpwin, turn);

			/* Verificando se tem xeque no jogo */
			if(turn == WHITES_TURN)
				{
					board = VerifyCheck(board, WHITE);
					if(board->WhiteCheck == CHECK){
						/* Mostrando que as brancas fizeram xeque */
						print_message(messages, W_CHECK);
						auxilary = VerifyCheckMate(board, WHITE);
						if(auxilary == NULL)
							{
								print_winner(helpwin, BLACK);
								if(wanna_save(messages)){
									SaveBoardFile(board, txtboard); /* Arquivo txt */
									SavePGNFile(pastmoves, pgnboard); /* Arquivo pgn */
									print_message(messages, SAVED_GAME);
								}
								break;
							} /* if(VerifyCheckMate...) */
						else
							{
								DeleteListOfMoves(auxilary);
							}
					} /* if(board->whi..) */
				}
			else /* Vez das pretas */
				{
					board = VerifyCheck(board, BLACK);
					if(board->BlackCheck == CHECK){
						/* Mostrando que as pretas fizeram xeque */
						print_message(messages, B_CHECK);
						auxilary = VerifyCheckMate(board, BLACK);
						if(auxilary == NULL)
							{
								print_winner(helpwin, WHITE);
								if(wanna_save(messages)){
									SaveBoardFile(board, txtboard);
									SavePGNFile(pastmoves, pgnboard);
									print_message(messages, SAVED_GAME);
								}
								break;
							}
						else
							{
								DeleteListOfMoves(auxilary);
							}
					} /* if(board->Blac...) */
				}

			if(turn == player)
				{
					/* Atualizando as dicas para o jogador */
					GiveHint(helpwin, board, turn);
					
					/* Adquirindo tecla ou mouse do usuário */
					choice = getch();
				}

			if(choice == 'j')
				{
					/* Guardando ponteiro para o tabuleiro anterior */
					copy_boards(old_board, board);

					/* Adquirindo o movimento do usuário pela notação */
					movement = GetMovement(keywin, chess_move);

					old_turn = turn; /* Para verificação se precisa guardar o movimento na lista */

					/* Movendo a peça para a nova posição */
					turn = UI_MOVE_PIECE(boardwin, messages, board, turn, movement);

					if(turn != old_turn)
						{
							AddListPM(pastmoves, chess_move);
						}
				} /* choice == j */

			else if(choice == KEY_MOUSE)
				{	
					/* Guardando o tabuleiro anterior */
					copy_boards(old_board, board);

					if(getmouse(&event) == OK)
						{
							/* Fazendo o movimento para o mouse */
							turn = UI_MOUSE_MOVE(boardwin, messages, board, turn, event, pastmoves);
						}
				} /* KEY_MOUSE */

			else if(choice == 'd')
				{
					/* Removendo a jogada da lista de jogadas já feitas */
					RemoveLastListPM(pastmoves);
					/* Pegando o tabuleiro antigo */
					copy_boards(board, old_board);
					/* Refazendo tabuleiro na interface */
					InitBoard(boardwin, board);
					wrefresh(boardwin);
				} /* choice == 'd' */

			else if(choice == 'q')
				{
					print_message(messages, ARE_YOU_SURE);
					choice = 'a';

					while((choice != 's') && (choice != 'n'))
						{
							choice = getch();
							if(choice == 's'){
								FreeListPM(pastmoves);
								finished = true;
							}
							else if(choice == 'n'){
								print_message(messages, CONTINUE_GAME);
							}
						} /* while((choice != 's') ... */
				} /* else if(choice == 'q') */

			else if(choice == 's') /* Usuário escolheu salvar o jogo */
				{
					SaveBoardFile(board, txtboard); /* Arquivo txt */
					SavePGNFile(pastmoves, pgnboard); /* Arquivo pgn */
					print_message(messages, SAVED_GAME);
				}

			/* Mostrando de quem é a vez de jogar */
			print_turn(helpwin, turn);

			if(machine == WHITES_TURN){
				aux_color = WHITE;
			}
			else{
				aux_color = BLACK;
			}


			/* Verificando se o player não já deu mate */
			board = VerifyCheck(board, aux_color);
			if(aux_color == WHITE)
				{
					if(board->WhiteCheck == CHECK)
						{
							auxilary = VerifyCheckMate(board, aux_color);
							if(auxilary == NULL)
								{
									mate = true; /* deu mate */
								}
							else
								{
									DeleteListOfMoves(auxilary);
								}
						}
				}
			else
				{
					if(board->BlackCheck == CHECK)
						{
							auxilary = VerifyCheckMate(board, aux_color);
							if(auxilary == NULL)
								{
									mate = true; /* deu mate */
								}
							else
								{
									DeleteListOfMoves(auxilary);
								}
						}
				}
			
			if((turn == machine) && (mate == false))
				{
					/* Fazendo o movimento do computador */
					decisions = CreateMovesTree(board, turn);
					SortTree(decisions, turn);
					possiblemoves = Best_Plays(decisions, decisions->root->n_child);
					ol = possiblemoves->first->play.origin[0]; /* Origin line */
					oc = possiblemoves->first->play.origin[1]; /* origin column */
					dl = possiblemoves->first->play.destiny[0]; /* destiny line */
					dc = possiblemoves->first->play.destiny[1]; /* destiny column */
					MovePiece(board, ol, oc, dl, dc);

					if((dl == 0) && (board->Board[dl][dc] == W_PAWN)){
							board->Board[dl][dc] = W_QUEEN;
							board->Weight -= GetValue(W_PAWN);
							board->Weight += GetValue(W_QUEEN);
						}
					else if((dl == 7) && (board->Board[dl][dc] == B_PAWN)){
						board->Board[dl][dc] = B_QUEEN;
						board->Weight -= GetValue(B_PAWN);
						board->Weight += GetValue(B_QUEEN);
					}

					InitBoard(boardwin, board);
					wrefresh(boardwin);

					turn = change_turn(turn);

					FreeTreeNodes(decisions->root);
					free(decisions);
					DeleteListOfMoves(possiblemoves);
				}
		} /* while(!finished) */
} /* play_pve() */
