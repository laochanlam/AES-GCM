CC ?= gcc
CFLAGS_common ?= -mpclmul

EXEC = main calculate

main: main.c
	$(CC) $(CFLAGS_common) -o $@ $@.c

Function.txt: main
	./main

Instrinics.txt: main
	./main

calculate: calculate.c Function.txt Instrinics.txt
	$(CC) -o $@ $@.c

repeat: $(EXEC)
	perf stat --repeat 100 \
		-e cache-misses,cache-references,instructions,cycles \
		./main

plot: output.txt
	gnuplot runtime.gp

output.txt: calculate
	./calculate


.PHONY: clean
clean:
	$(RM) $(EXEC) *.out *.txt
