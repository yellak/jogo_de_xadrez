CC          = g++
IDIR        = ../include
TDIR		= ../test
ODIR        = obj
LDIR        = ../lib
CURSESFLAGS = -lncurses
GTESTFLAGS = -lgtest -lpthread

# Dependências do módulo principal
_MAINOBJ = interface.o main.o tabuleiro.o logica.o
MAINOBJ = $(patsubst %, $(ODIR)/%, $(_MAINOBJ))

_MAINDEPS = interface.h tabuleiro.h logica.h
MAINDEPS = $(patsubst %, $(IDIR)/%, $(_MAINDEPS))

# Dependências do módulo tabuleiro e seu módulo de testes
_TABOBJ = tabuleiro.o TEST_tabuleiro.o
TABOBJ = $(patsubst %, $(ODIR)/%, $(_TABOBJ))

_TABDEPS = tabuleiro.h
TABDEPS = $(patsubst %, $(IDIR)/%, $(_TABDEPS))

# Dependências do módulo lógica e seu módulo de testes
_LOGOBJ = logica.o TEST_logica.o tabuleiro.o
LOGOBJ = $(patsubst %, $(ODIR)/%, $(_LOGOBJ))

_LOGDEPS = tabuleiro.h logica.h
LOGDEPS = $(patsubst %, $(IDIR)/%, $(_LOGDEPS))

all: main test_tabuleiro test_logica

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

test_logica: $(LOGOBJ) $(LOGDEPS)
	$(CC) -g -o $@ $^ $(GTESTFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ $(IDIR)/*~ main *.o

