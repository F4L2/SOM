IDIR =./include
CC=gcc
CFLAGS=-I $(IDIR) -W -Wall

ODIR=obj
SDIR=src

LIBS=-lm -std=c11

_DEPS = network.h data_format.h parameters.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o func.o learn.o load_data.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	mkdir -p $(ODIR) 
	$(CC) -c -o $@ $< $(CFLAGS) $(LIBS)

som: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f som *~
	rm -rf $(ODIR)
