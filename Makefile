CC			:= gcc
CFLAGS 		:= -g -lm

ALL_CFLAGS 	:= -Wall -Wextra -pedantic-errors -O2

BIN			:= sieve

# ================================================================ #

$(BIN): main.c
	$(CC) $(CFLAGS) $(ALL_CFLAGS) -o $@.out $^

# ================================ #

.PHONY: clean

clean:
	rm -rf $(OBJDIR) *.out