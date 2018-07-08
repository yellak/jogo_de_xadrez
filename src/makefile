CC          = g++
IDIR        = ../include
TDIR		= ../test
ODIR        = obj
LDIR        = ../lib
CURSESFLAGS = -lncurses
GTESTFLAGS = -lgtest -lpthread
GCOVFLAGS = -fprofile-arcs -ftest-coverage -lgcov --coverage

# Dependências do módulo principal
_MAINOBJ = interface.o main.o tabuleiro.o logica.o list_of_moves.o in-out.o arv_decisoes.o ia.o
MAINOBJ = $(patsubst %, $(ODIR)/%, $(_MAINOBJ))

_MAINDEPS = interface.h tabuleiro.h logica.h list_of_moves.h in-out.h arv_decisoes.h ia.h
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

_LSTOBJ = list_of_moves.o TEST_list.o
LSTOBJ = $(patsubst %, $(ODIR)/%, $(_LSTOBJ))

_LSTDEPS = list_of_moves.h
LSTDEPS = $(patsubst %, $(IDIR)/%, $(_LSTDEPS))

# Dependências do módulo in-out e seu módulo de testes

_IOOBJ = in-out.o TEST_in-out.o tabuleiro.o
IOOBJ = $(patsubst %, $(ODIR)/%, $(_IOOBJ))

_IODEPS = in-out.h tabuleiro.h
IODEPS = $(patsubst %, $(IDIR)/%, $(_IODEPS))

# Dependências do módulo IA e seu módulo de testes

_IAOBJ = ia.o TEST_ia.o logica.o arv_decisoes.o tabuleiro.o list_of_moves.o
IAOBJ = $(patsubst %, $(ODIR)/%, $(_IAOBJ))

_IADEPS = ia.h logica.h arv_decisoes.h tabuleiro.h list_of_moves.h
IADEPS = $(patsubst %, $(IDIR)/%, $(_IADEPS))

all: main test_tabuleiro test_logica test_arvore test_list test_io test_ia

# Compila os módulos principais
$(ODIR)/%.o: %.c
	$(CC) -g -c -o $@ $< $(GCOVFLAGS)

# Compila os módulos de testes
$(ODIR)/%.o: $(TDIR)/%.c
	$(CC) -g -c -o $@ $<

main: $(MAINOBJ) $(MAINDEPS)
	$(CC) -g -o $@ $^ $(CURSESFLAGS) $(GCOVFLAGS)

test_list: $(LSTOBJ) $(LSTDEPS)
	$(CC) -g -o $@ $^ $(GTESTFLAGS) $(GCOVFLAGS)

test_tabuleiro: $(TABOBJ) $(TABDEPS)
	$(CC) -g -o $@ $^ $(GTESTFLAGS) $(GCOVFLAGS)

test_logica: $(LOGOBJ) $(LOGDEPS)
	$(CC) -g -o $@ $^ $(GTESTFLAGS) $(GCOVFLAGS)

test_arvore: $(ARVOBJ) $(ARVDEPS)
	$(CC) -g -o $@ $^ $(GTESTFLAGS) $(GCOVFLAGS)

test_io: $(IOOBJ) $(IODEPS)
	$(CC) -g -o $@ $^ $(GTESTFLAGS) $(GCOVFLAGS)

test_ia: $(IAOBJ) $(IADEPS)
	$(CC) -g -o $@ $^ $(GTESTFLAGS) $(GCOVFLAGS)


.PHONY: clean

clean:
	rm -f  $(ODIR)/*.o $(ODIR)/*.gcno $(ODIR)/*.gcda *~ $(IDIR)/*~ main *.o


.PHONY: gcov

gcov: gcov_board gcov_list gcov_logica gcov_arvore gcov_io gcov_ia

gcov_board:
	./test_tabuleiro
	gcov -abcfu tabuleiro.c -o obj > gcov_tabuleiro.txt

gcov_list:
	./test_list
	gcov -abcfu list_of_moves.c -o obj > gcov_list.txt

gcov_arvore:
	./test_arvore
	gcov -abcfu arv_decisoes.c -o obj > gcov_arvore.txt

gcov_logica:
	./test_logica
	gcov -abcfu logica.c -o obj > gcov_logica.txt

gcov_io:
	./test_io
	gcov -abcfu in-out.c -o obj > gcov_io.txt

gcov_ia:
	./test_ia
	gcov -abcfu ia.c -o obj > gcov_ia.txt


.PHONY: clean_gcov

clean_gcov:
	rm -f *.gcno *.gcov
