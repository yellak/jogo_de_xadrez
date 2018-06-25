CC          = g++
IDIR        = ../include
TDIR		= ../test
ODIR        = obj
LDIR        = ../lib
CURSESFLAGS = -lncurses
GTESTFLAGS = -lgtest -lpthread

# Dependências do módulo principal
_MAINOBJ = interface.o main.o
MAINOBJ = $(patsubst %, $(ODIR)/%, $(_MAINOBJ))

_MAINDEPS = interface.h
MAINDEPS = $(patsubst %, $(IDIR)/%, $(_MAINDEPS))

# Dependências do módulo tabuleiro e seu módulo de testes
_TABOBJ = tabuleiro.o TEST_tabuleiro.o
TABOBJ = $(patsubst %, $(ODIR)/%, $(_TABOBJ))

_TABDEPS = tabuleiro.h
TABDEPS = $(patsubst %, $(IDIR)/%, $(_TABDEPS))

all: main test_tabuleiro

# Compila os módulos principais
$(ODIR)/%.o: %.c
	$(CC) -g -c -o $@ $<

# Compila os módulos de testes
$(ODIR)/%.o: $(TDIR)/%.c
	$(CC) -g -c -o $@ $<

main: $(MAINOBJ) $(MAINDEPS)
	$(CC) -g -o $@ $^ $(CURSESFLAGS)

test_tabuleiro: $(TABOBJ) $(TABDEPS)
	$(CC) -g -o $@ $^ $(GTESTFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ $(IDIR)/*~ main *.o

