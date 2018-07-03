#ifndef _GUI_INTERFACE_
#define _GUI_INTERFACE_

#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include "tabuleiro.h"
#include "logica.h"

/* Tamanho do tabuleiro */
const int XLIMIT = 8;
const int YLIMIT = 8;

/* Coordenadas para o início do tabuleiro */
const int BOARDY = 2;
const int BOARDX = 3;

/* Variáveis usadas para diferenciar entre o tabuleiro mostrado ao usuário e o
   que está armazenado na memória */
const int YOFFSET = 2;
const int XOFFSET = 4;

/* Constantes para as mensagens */
const int INVALID_SINTAX = 0;
const int ARE_YOU_SURE   = 1;
const int CONTINUE_GAME  = 2;
const int INVALID_MOVE   = 3;
const int WHITE_MOVE     = 4;
const int BLACK_MOVE     = 5;
const int NOTBLACKSMOVE  = 6;
const int NOTWHITESMOVE  = 7;
const int CONTINUE       = 8;
const int INSERT_PIECE   = 9;
const int CLICK          = 10;
const int INVALID_PIECE  = 11;
const int INVALID_BOARD  = 12;
const int USE_MOUSE      = 13;

/* Constantes para modos de jogo */
const int PVP      = 1; /* Player vs Player */
const int PVE      = 2;
const int EXITGAME = 3;

/* Constantes para opção da escolha do tabuleiro */
const int STD_BOARD   = 1;
const int SAVED_BOARD = 2;
const int NEW_BOARD   = 3;
const int EXIT_GAME   = 4;

/* Constantes para os tipos de janelas de atalhos */
const int GAMING   = 0;
const int CREATING = 1;

/* Constantes que indicam de quem é a vez de jogar */
const int BLACKS_TURN = 0;
const int WHITES_TURN = 1;


WINDOW* MakeBoardWin(void);

WINDOW* MakeYaxisWin(void);

WINDOW* MakeXaxisWin(void);

WINDOW* MakeKeyWin(void);

WINDOW* MakeMsgWin(void);

WINDOW* MakeHelpWin(void);

void TranslateCoord(int yscreen, int xscreen, int* yboard, int* xboard);


/* Inicia um tabuleiro graficamente */
/*! \fn void InitBoard(WINDOW* boardwin, TBoard* board)
		\brief Inicializa graficamente um tabuleiro na base inicial

		\param boardwin Janela onde está o tabuleiro
		\param board    Tabuleiro que será incializado na parte gráfica
		\return Não tem retorno
*/
void InitBoard(WINDOW* boardwin, TBoard* board);

/* Desenha um tabeuleiro vazio */
/*! \fn void DrawBoard(WINDOW* boardwin)
        \brief Desenha um tabuleiro vazio no terminal

		\param boardwin Janela onde será colocado o tabuleiro
		\return Não há retorno, ela apenas desenha o quadro na janela dada
 */
void DrawBoard(WINDOW* boardwin);

/* Desenha os eixos coordenados */
/*! \fn void DrawAxis(WINDOW* yaxis, WINDOW* xaxis)
        \brief Desenha os eixos coordenados que servem para indicar ajudar a
               identificar a posição de uma peça

		\param yaxis Eixo das coordenadas dadas por números
		\param xaxis Eixo das coordenadas dadas pelas letras
		\return Sem retorno
*/
void DrawAxis(WINDOW* yaxis, WINDOW* xaxis);

/* Cria um menu para escolha de tipo de jogo */
/*! \fn int CreateMenu(WINDOW* menuwin)
        \brief Desenha o menu de escolha do tipo de jogo e faz o usuário
               escolher entre uma das opções disponíveis

        \param menuwin Janela onde será mostrado o menu

		\return 1 Se o usuário escolher "Jogador VS Jogador"
                2 Se ele escolher "Jogador VS Máquina"
                3 Se escolher Sair
*/
int CreateMenu(WINDOW* menuwin);

/* Escreve os atalhos disponíveis na janela de atalhos */
/*! \fn void write_keys_help(WINDOW* keywin)
        \brief Esta função irá escrever na interface os atalhos disponíveis
               para uso na janela de teclas e atalhos

		\param keywin A janela onde seram impressos os atalhos
		\return Sem retorno
*/
void write_keys_help(WINDOW* keywin, int wintype);

/* Função para jogo PVP */
/*! \fn void play_pvp(WINDOW* boardwin, WINDOW* keywin, WINDOW* messages, TBoard* board)
        \brief Função responsável por todo o modo de jogo de humano vs humano

        \param boardwin Janela onde está o tabuleiro gráfico do programa
        \param keywin   Janela das teclas e atalhos disponíveis
        \param messages Janela onde serão impressas as mensagens
        \param board    Tabueleiro guaradado na memória de forma não gráfica
*/
void play_pvp(WINDOW* boardwin, WINDOW* keywin, WINDOW* messages, TBoard* board);

/* Função para limpar a janelas de ajuda com atalhos */
/*! \fn void clear_keywin(WINDOW* keywin)
        \brief Limpa a área de comandos da janela de ajuda com atalhos

         A área de comando desta janela é onde o usuário irá digitar o
         movimento desejado, que é logo abaixo das informações de atalhos

         \param keywin Janela de ajuda com atalhos */
void clear_keywin(WINDOW* keywin);

/* Função de inicializar a janela de mensagens */
/*! \fn void init_msg_win(WINDOW* messages)
        \brief Inicializa a janela de mensagens

        \param messages Janela de mensagens já alocada */
void init_msg_win(WINDOW* messages);

/* Função de limpar janela de mensagens */
/*! \fn void clear_message(WINDOW* messages)

        \brief Limpa janela de mensagens

		Ela irá limpar a janela de mensagens mas não limpará o efeito box

        \param messages Janela de mensagens */
void clear_message(WINDOW* messages);

/* Função que irá printar mensagens */
/*! \fn void print_message(WINDOW* messages, int msg)
        \brief Imprime mensagens na janela de mensagens

        \param messages Janela de mensagens
        \param msg      Inteiro que indica qual mensagem deverá aparecer na
                        janela */
void print_message(WINDOW* messages, int msg);

/* Função de obter um tabuleiro */
/*! \fn TBoard* MenuGetBoard(void)
        \brief Abre o menu de escolha do tabuleiro

		Esta função irá fazer outras chamadas internas de funções que poderão
        inicilizar um novo ambiente de interação com o usuário

        \return board Tabuleiro que poderá ter sido carregado de um arquivo,
                criado pelo usuário ou inicializado de forma padrão
*/
TBoard* MenuGetBoard(void);

/* Função de criar um novo tabuleiro */
/*! \fn TBoard* CreateNewBoard(void)
        \brief Função de criar um novo tabuleiro

        Esta função irá abrir um novo ambiente de interação com o usuário onde
        ele poderá criar um tabuleiro de sua preferência.

        \return board Tabuleiro criado pelo usuário */
TBoard* CreateNewBoard(void);

/* Função de criar a janela de ajuda para criação de tabuleiro */
/*! \fn void HelpWinNewBoard(WINDOW* helpwin)

        \brief Inicializa a janela de ajuda para o menu de criação

		Observe que esta função é chamada apenas para o menu de criação de
        uma nova imagem.
        Esta função irá colocar na janela de ajuda alguns resumos sobre as
        peças que o usuário poderá colocar e a explicação de como colocar
        uma nova peça.
		Não possui retorno

        \param helpwin Janela de ajuda */
void HelpWinNewBoard(WINDOW* helpwin);

/* Função de mudar a vez */
/*! \fn int change_turn(int turn)
        \brief Muda a vez da jogada

         Ela vai mudar o turno da jogada, por exemplo se foi as pretas que
         jogaram por último ela muda o turno para as brancas

        \param turn Indica de quem era a última jogada

        \return new_turn Indica de quem é a nova vez de jogar */
int change_turn(int turn);

/* Função de verificar a vez */
/*! \fn int verify_turn(TBoard* board, Move* movement, int turn)
        \brief Verifica se o jogador vai mexer a peça correta

        Ela verifica se realmente é o turno da cor da peça que o usuário está
        querendo movimentar

        \param board    Tabuleiro atual do jogo
        \param movement Movimento que o jogador quer fazer
        \param turn     De quem é o turno atual do jogo

        \return true  Se é o turno da cor da peça a ser mexida
        \return false Se não é o turno da cor da peça a ser mexida */
int verify_turn(TBoard* board, Move* movement, int turn);
	
#endif
