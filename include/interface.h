#ifndef _GUI_INTERFACE_
#define _GUI_INTERFACE_

#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include "tabuleiro.h"
#include "logica.h"
#include "in-out.h"
#include "arv_decisoes.h"
#include "ia.h"
#include "list_of_moves.h"

/* Tamanho do tabuleiro */
const int XLIMIT = 8; /*!< Indica o tamanho do eixo Y do tabuleiro  */
const int YLIMIT = 8; /*!< Indica o tamanho do eixo X do tabuleiro */

/* Coordenadas para o início do tabuleiro */
const int BOARDY = 2; /*!< Indica onde começa o tabuleiro pelo eixo Y */
const int BOARDX = 3; /*!< Indica onde começa o tabuleiro pelo eixo X */

/* Variáveis usadas para diferenciar entre o tabuleiro mostrado ao usuário e o
   que está armazenado na memória */
const int YOFFSET = 2; /*!< Número de caracteres entre duas posições no tabuleiro gráfico pelo eixo Y */
const int XOFFSET = 4; /*!< Mesma coisa do YOFFSET só que para o eixo X */

/* Constantes para as mensagens */
const int INVALID_SINTAX = 0; /*!< Avisa sobre sintxe inválida */
const int ARE_YOU_SURE   = 1; /*!< Perguntar se usuário tem certeza */
const int CONTINUE_GAME  = 2; /*!< Avisar que o jogo vai continuar */
const int INVALID_MOVE   = 3; /*!< Avisar sobre movimento inválido */
const int WHITE_MOVE     = 4; /*!< Avisar que a vez das brancas */
const int BLACK_MOVE     = 5; /*!< Avisar que a vez das pretas */
const int NOTBLACKSMOVE  = 6; /*!< Avisar que não é a vez das pretas */
const int NOTWHITESMOVE  = 7; /*!< Avisar que não é a vez das brancas */
const int CONTINUE       = 8; /*!<  */
const int INSERT_PIECE   = 9; /*!<  */
const int CLICK          = 10; /*!< Avisar para clicar na posição desejada */
const int INVALID_PIECE  = 11; /*!< Avisar de peça inválida */
const int INVALID_BOARD  = 12; /*!< Avisar de tabuleiro inválido */
const int USE_MOUSE      = 13; /*!< Avisar para usar o mouse */
const int NOTPIECE       = 14; /*!< Avisar que não há uma peça naquela posição */
const int CLICK_DESTINY  = 15; /*!< Pedir para clicar no destino */
const int OUT_RANGE      = 16; /*!< Avisar que o destino está fora do tabuleiro */
const int SAVED_GAME     = 17; /*!< Avisa que o jogo foi salvo */
const int W_CHECK        = 18; /*!< Indica xeque no rei branco */
const int B_CHECK        = 19; /*!< Indica xeque no rei preto */
const int WHITE_WON      = 20; /*!< Indica que as brancas veceram */
const int BLACK_WON      = 21; /*!< Indica que as pretas venceram */
const int WANNA_SAVE     = 22; /*!< Perguntar se o usuário quer salvar o jogo */
const int GIVE_A_PIECE   = 23; /*!< Pedir para o usuário digitar uma peça */
const int YOURCOLOR      = 24; /*!< Perguntar para o usuário qual cor ele prefere */

/* Constantes para modos de jogo */
const int PVP      = 1; /*!< Player vs Player */
const int PVE      = 2;	/*!< Player vs Environment */
const int EXITGAME = 3;	/*!< Sair do jogo */

/* Constantes para opção da escolha do tabuleiro */
const int STD_BOARD   = 1; /*!< Opção de tabuleiro padrão */
const int SAVED_BOARD = 2; /*!< Opção de carregar tabuleiro salvo */
const int NEW_BOARD   = 3; /*!< Opção de criar novo tabuleiro */
const int EXIT_GAME   = 4; /*!< Opção de sair do jogo */

/* Constantes para os tipos de janelas de atalhos */
const int GAMING   = 0;	/*!< Indica menu para modo de jogo */
const int CREATING = 1;	/*!< Indica menu para mode de criação */

/* Constantes que indicam de quem é a vez de jogar */
//const int BLACKS_TURN = 0;
//const int WHITES_TURN = 1;


/* Cria uma janela do tabuleiro */
/*! \fn WINDOW* MakeBoardWin(void)
        \brief Cria janela do tabuleiro

        \return boardwin Ponteiro para a janela do tabuleiro */
WINDOW* MakeBoardWin(void);

/* Cria uma janela do eixo Y */
/*! \fn WINDOW* MakeYaxisWin(void)
        \brief Cria janela do eixo Y
        
        \return yaxis Ponteiro para a janela do eixo Y */
WINDOW* MakeYaxisWin(void);

/* Cria uma janela do eixo X */
/*! \fn WINDOW* MakeXaxisWin(void)
       \brief Cria janela do eixo X

       \return xaxis Ponteiro para a janela do eixo X */
WINDOW* MakeXaxisWin(void);

/* Cria uma janela do menu de atalhos */
/*! \fn WINDOW* MakeKeyWin(void)
        \brief Cria a janela do menu de atalhos

		Este menu de atalhos é o que mostra as opções de atalhos no teclado
        para o usuário, como a tecla 'j' no menu do PVP que é usada para fazer
        jogadas usando a notação

        \return keywin Janela do menu de atalhos */
WINDOW* MakeKeyWin(void);

/* Cria uma janela de mensagens */
/*! \fn WINDOW* MakeMsgWin(void)
        \brief Cria janela de mensagens

        \return messages Janela de mensagens */
WINDOW* MakeMsgWin(void);

/* Cria uma janela de ajuda */
/*! \fn WINDOW* MakeHelpWin(void)
        \brief Cria a janela de ajuda
     
        \return helpwin Janela da ajuda */
WINDOW* MakeHelpWin(void);

/* Traduz coordenadas, da tela para tabuleiro na memória */
/*! \fn void TranslateCoord(int yscreen, int xscreen, int* yboard, int* xboard)
        \brief Traduz as coordenadas da tela para as do tabuleiro
         
        Esta função é chamada toda vez que o usuário clica na tela e traduz as
        coordenadas da posição que o usuário digitou para as coordenadas do
        tabuleiro

        \param yscreen Posição Y onde o usuário digitou
        \param xscreen Posição X onde o usuário digitou
        \param yboard  Posição Y traduzida
        \param xboard  Posição X traduzida */
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


/* Jogar PVE */
/*! \fn void play_pve(WINDOW* boardwin, WINDOW* keywin, WINDOW* messages, TBoard* board)
        \brief Faz todo o processo do modo de jogo Jogador vs Computador

         \param boardwin Janela do tabuleiro
         \param keywin   Janela onde estão dicas de atalho e região de interação com o teclado dele
         \param Janela de mensagens
         \param Tabuleiro que será utilizado */
void play_pve(WINDOW* boardwin, WINDOW* keywin, WINDOW* messages, TBoard* board);

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

/* Mostrar as dicas na tela */
/*! \fn void GiveHint(WINDOW* helpwin, TBoard* board, int turn)
        \brief Mostra as dicas na tela do jogador

        \param helpwin Janela de ajuda para o usuário
        \param board   Tabuleiro que será considerado para as dicas
        \param turn    Indica quem é o dono do turno e que vai receber as dicas */
void GiveHint(WINDOW* helpwin, TBoard* board, int turn);

/* Mostrar o turno (vez de jogar) */
/*! \fn void print_turn(WINDOW* helpwin, int turn) 
        \brief Mostra de quem é a vez de jogar na partida

        \param helpwin Janela de ajuda
        \param turn    Indica de quem é o turno (vez de jogar)*/
void print_turn(WINDOW* helpwin, int turn);

/* Verificar salvemento */
/*! \fn int wanna_save(WINDOW* messages)
        \brief Pergunta ao usuário se ele quer salvar o jogo

        \param messages Janela de mensagens

        \return true  Se o usuário quiser salvar o jogo
        \return false Se o usuário não quiser salvar */
int wanna_save(WINDOW* messages);

/* Mostra o vencedor */
/*! \fn void print_winner(WINDOW* helpwin, int who)
        \brief Mostra na tela quem é o jogador vencedor da partida

        \param helpwin Janela de ajuda
        \param who     Indica quem foi o vencedor do jogo */
void print_winner(WINDOW* helpwin, int who);

/* Destaca uma peça na tela */
/*! \fn int reverse_color_in_board(WINDOW* boardwin, TBoard* board, int line, int column)
        \brief Destaca na interface a posição dada no tabuleiro 

        \param boardwin Janela do tabuleiro
        \param board    Tabuleiro referência
        \param line     Posição Y a ser destacada (referente a board e não a tela)
        \param column   Posição X a ser destacada

        \return true  Se havia uma peça na posição dada 
        \return false Se não tiha uma peça na posição dada*/
int reverse_color_in_board(WINDOW* boardwin, TBoard* board, int line, int column);

/* Verificar promoção do peão */
/*! \fn int verify_evolve_pawn(WINDOW* messages, TBoard* board)
        \brief Verifica se existe algum peão para ser promovido

               Ela também irá promover o peão de acordo com a escolha do jogador

        \param messages Janela de mensagens
        \param board    Tabuleiro atual do jogo

        \return true  Se tinha um peão para promover
        \return false Se não tinha um peão para promover */
int verify_evolve_pawn(WINDOW* messages, TBoard* board);

/* Mover peça graficamente */
/*! \fn int UI_MOVE_PIECE(WINDOW* boardwin, WINDOW* messages, TBoard* board, int turn, Move* movement)
        \brief Move a peça e faz todas as verificações pela própria interface

        \param boardwin Janela do tabuleiro
        \param messages Janela de mensagens
        \param board    Tabuleiro a ser modificado
        \param turn     Indica de quem é a vez de jogar
        \param movement Movimento a ser feito

        \return turn Indicando de quem é a vez de jogar */
int UI_MOVE_PIECE(WINDOW* boardwin, WINDOW* messages, TBoard* board, int turn, Move* movement);

/* Mover peça pelo mouse */
/*! \fn int UI_MOUSE_MOVE(WINDOW* boardwin, WINDOW* messages, TBoard* board, int turn, MEVENT event, ListPastMoves* pastmoves) 
        \brief Move a peça através do mouse do usuário

        \param boadwin   Janela do tabuleiro
        \param messages  Janela de mensagens
        \param board     Tabuleiro a ser modificado
        \param turn      Indica de quem é a vez de jogar agora
        \param event     Evento de mouse 
        \param pastmoves Lista de movimentos passados para o arquivo PGN

        \return turn Indicando de quem é a vez de jogar agora*/
int UI_MOUSE_MOVE(WINDOW* boardwin, WINDOW* messages, TBoard* board, int turn, MEVENT event, ListPastMoves* pastmoves);

/* Obter movimento do usuário */
/*! \fn Move* GetMovement(WINDOW* keywin, char chess_move[])
        \brief Obtém do usuário um movimento através da notação

        \param keywin     Janela onde está os atalhos
        \param chess_move String onde será colocada a jodada do jogador

        \return movement Movimento traduzido do jogador para o tipo Move* */
Move* GetMovement(WINDOW* keywin, char chess_move[]);

/* Iniciar janela de ajuda do PVE */
/*! \fn void HelpWinPVE(WINDOW* helpwin)
        \brief Inicializa a janela de ajuda do PVE com o básico 

        \param helpwin Janela de ajuda */
void HelpWinPVE(WINDOW* helpwin);

/* Mostrar legenda na tela de ajuda */
/*! \fn void HelpWinPVP(WINDOW* helpwin) 
        \brief Mostra legenda das peças na tela de ajuda no PVP

        \param helpwin Janela de ajuda onde seram colocadas as legendas*/
void HelpWinPVP(WINDOW* helpwin);
	
#endif
