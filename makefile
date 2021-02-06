IDIR =./include
CC=gcc
CFLAGS=-I $(IDIR) -W -Wall

ODIR=obj

LIBS=-lm -std=c11

_DEPS = utility.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o func.o learn.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	mkdir -p $(ODIR) 
	$(CC) -c -o $@ $< $(CFLAGS) $(LIBS)

som: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f som *~
	rm -rf $(ODIR)
