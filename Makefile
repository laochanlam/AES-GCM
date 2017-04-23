CC ?= gcc
CFLAGS_common ?= -mpclmul

EXEC = main

main: main.c
	$(CC) $(CFLAGS_common) -o $@ $@.c

.PHONY: clean
clean:
	$(RM) $(EXEC) *.out
