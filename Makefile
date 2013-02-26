CC=gcc
CFLAGS=-Wall -Iinc -std=c99
LFLAGS=-lncurses

ODIR=obj

_OBJ = mousing.o functions.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

mousing: $(OBJ)
	$(CC) -o $@ $^ $(LFLAGS)

$(ODIR)/%.o: src/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o mousing
