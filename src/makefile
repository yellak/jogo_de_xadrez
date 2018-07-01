CC          = g++
IDIR        = ../include
TDIR		= ../test
ODIR        = obj
LDIR        = ../lib
CURSESFLAGS = -lncurses
GTESTFLAGS = -lgtest -lpthread

# Dependências do módulo principal
_MAINOBJ = interface.o main.o tabuleiro.o logica.o list_of_moves.o
MAINOBJ = $(patsubst %, $(ODIR)/%, $(_MAINOBJ))

_MAINDEPS = interface.h tabuleiro.h logica.h list_of_moves.h
MAINDEPS = $(patsubst %, $(IDIR)/%, $(_MAINDEPS))

# Dependências do módulo tabuleiro e seu módulo de testes
_TABOBJ = tabuleiro.o TEST_tabuleiro.o
TABOBJ = $(patsubst %, $(ODIR)/%, $(_TABOBJ))

_TABDEPS = tabuleiro.h
TABDEPS = $(patsubst %, $(IDIR)/%, $(_TABDEPS))

# Dependências do módulo lógica e seu módulo de testes
_LOGOBJ = logica.o TEST_logica.o tabuleiro.o list_of_moves.o
LOGOBJ = $(patsubst %, $(ODIR)/%, $(_LOGOBJ))

_LOGDEPS = tabuleiro.h list_of_moves.h logica.h 
LOGDEPS = $(patsubst %, $(IDIR)/%, $(_LOGDEPS))

# Dependências do módulo arv_decisoes e seu módulo de testes
_ARVOBJ = arv_decisoes.o list_of_moves.o TEST_arv_decisoes.o tabuleiro.o
ARVOBJ = $(patsubst %, $(ODIR)/%, $(_ARVOBJ))

_ARVDEPS = tabuleiro.h list_of_moves.h arv_decisoes.h
ARVDEPS = $(patsubst %, $(IDIR)/%, $(_ARVDEPS))

# Dependências do módulo list_of_moves e seu módulo de testes

# _LSTOBJ = list_of_moves.o #TEST_list.o
# LSTOBJ = $(patsubst %, $(ODIR)/%, $(_LSTOBJ))

# _LSTDEPS = list_of_moves.h
# LSTDEPS = $(patsubst %, $(IDIR)/%, $(_LSTDEPS))

all: main test_tabuleiro test_logica test_arvore 
#test_list

# Compila os módulos principais
$(ODIR)/%.o: %.c
	$(CC) -g -c -o $@ $<

# Compila os módulos de testes
$(ODIR)/%.o: $(TDIR)/%.c
	$(CC) -g -c -o $@ $<

main: $(MAINOBJ) $(MAINDEPS)
	$(CC) -g -o $@ $^ $(CURSESFLAGS)

test_list: $(LSTOBJ) $(LSTDEPS)
	$(CC) -g -o $@ $^ $(GTESTFLAGS)
	
test_tabuleiro: $(TABOBJ) $(TABDEPS)
	$(CC) -g -o $@ $^ $(GTESTFLAGS)

test_logica: $(LOGOBJ) $(LOGDEPS)
	$(CC) -g -o $@ $^ $(GTESTFLAGS)

test_arvore: $(ARVOBJ) $(ARVDEPS)
	$(CC) -g -o $@ $^ $(GTESTFLAGS)


.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ $(IDIR)/*~ main *.o

