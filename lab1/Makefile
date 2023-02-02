.PHONY: all clean format
CFLAGS = -O3

all: reverse_test

clean:
	rm -f reverse test_reverse reverse.o test_reverse.o

format:
	clang-format -style=Google -i reverse.c test_reverse.c 

reverse_test: reverse test_reverse
	gcc $(CFLAGS) $^ -o $@

%: %.c
	gcc {{{html}}}lt; -o $@
