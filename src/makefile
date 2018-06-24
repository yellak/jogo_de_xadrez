CC          = g++
IDIR        = ../include
ODIR        = obj
LDIR        = ../lib
CURSESFLAGS = -lncurses

# Dependências do módulo principal
_MAINOBJ = interface.o main.o
MAINOBJ = $(patsubst %, $(ODIR)/%, $(_MAINOBJ))

_MAINDEPS = interface.h
MAINDEPS = $(patsubst %, $(IDIR)/%, $(_MAINDEPS))

all: main

$(ODIR)/%.o: %.c
	$(CC) -g -c -o $@ $<

main: $(MAINOBJ) $(MAINDEPS)
	$(CC) -g -o $@ $^ $(CURSESFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ $(IDIR)/*~ main *.o

