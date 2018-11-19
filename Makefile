CC = gcc
CFLAGS = -std=c99 -Wall -Werror -Wextra -pedantic -g
SDIR = src
ODIR = bin
BIN = HalmaGame

_SRCS = main.c check-the-game.c error-of-game.c general-function.c in-out-shell.c init-the-game.c move-the-pawn.c run-the-game.c save-load.c
_OBJS = $(_SRCS:.c=.o)
OBJS = $(patsubst %,$(ODIR)/%,$(_OBJS))

$(ODIR)/%.o: $(SDIR)/%.c
	if [ ! -d "$(ODIR)" ]; then mkdir $(ODIR); fi
	$(CC) $(CFLAGS)  -c -o $@ $<

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN) $(OBJS)

run: $(BIN)
	./HalmaGame

.PHONY: clean

clean:
	rm -f $(BIN)
	rm -f $(ODIR)/*
