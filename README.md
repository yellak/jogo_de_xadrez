# jogo_de_xadrez
Um jogo de xadrez escrito em C.

Instruções:

Primeiramente, abre-se a pasta src, que está dentro do diretório jogo_de_xadrez, no terminal. Em seguida, compila-se o programa escrevendo make. Para iniciar a execução do programa, digita-se no terminal, dentro da pasta src, a seguinte instrução: ./main.

Em seguida, Aparecerá uma interface com 4 opções, uma para iniciar um jogo com um tabuleiro na posição de peças padrão do xadrez, a segunda que permite recuperar um jogo salvo por meio de um arquivo contendo um tabuleiro salvo, a terceira que permite criar um tabuleiro do zero e a última que permite sair do jogo.

Ao selecionar a primeira opção e a segunda, abrirá outra janela de opções que dispõem de 3 opções, a primeira em que se joga jogadorXjogador, a segunda que é jogadorxComputador e a opção de sair do jogo.

Ao selecionar a terceira opção, primeiro abre-se uma interface para que se crie a sua própria disposição em um tabuleiro de xadrez, usando a linha de comando própria da interface para adicionar as peças, começando pelos reis, e clicando na posição desejada. Ao finalizar esse processo, aparecem as 2 opções de modo de jogo.

Como jogar:

. Modo Jogador x Jogador:

Aparece a interface com o tabuleiro selecionado, começando pelas peças brancas. O jogador deve escrever na linha de comando usando o padrão pré estabelecido para determinar a peça em sua posição inicial e a posição final do movimento. Em seguida, é a vez das peça pretas jogarem, seguindo o mesmo procedimento. O jogo termina ao se chegar em uma condição de checkmate ou empate.

. Modo Jogador x Computador:
 
Aparece a interface com o tabuleiro selecionado, começando pelas peças brancas. O jogador recebe escrito naa tela as melhores jogadas possíveis para o momento, podendo escolhê-las ou não. Em seguida, a maquina joga baseada em sua IA para tentar ganhar do jogador. O jogo termina quando se chega em uma posição de checkmate ou empate.
