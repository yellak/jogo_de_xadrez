#ifndef _GUI_INTERFACE_
#define _GUI_INTERFACE_

#include <ncurses.h>
#include <stdlib.h>
#include "tabuleiro.h"
#include "logica.h"

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

/* Constante que indicará que o usuário escolheu terminar o jogo */
const int EXITGAME = 3;

/* Constantes para as mensagens */
const int INVALID_SINTAX = 0;
const int ARE_YOU_SURE   = 1;
const int CONTINUE_GAME  = 2;
const int INVALID_MOVE   = 3;

/* Constantes para modos de jogo */
const int PVP = 1;
const int PVE = 2;

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
void write_keys_help(WINDOW* keywin);

/* Função para jogo PVP */
/*! \fn void play_pvp(WINDOW* boardwin, WINDOW* keywin, WINDOW* messages, TBoard* board)
        \brief Função responsável por todo o modo de jogo de humano vs humano

        \param boardwin Janela onde está o tabuleiro gráfico do programa
        \param keywin   Janela das teclas e atalhos disponíveis
        \param messages Janela onde serão impressas as mensagens
        \param board    Tabueleiro guaradado na memória de forma não gráfica
*/
void play_pvp(WINDOW* boardwin, WINDOW* keywin, WINDOW* messages, TBoard* board);

void clear_keywin(WINDOW* keywin);

void init_msg_win(WINDOW* messages);

void clear_message(WINDOW* messages);

void print_message(WINDOW* messages, int msg);
	
#endif
