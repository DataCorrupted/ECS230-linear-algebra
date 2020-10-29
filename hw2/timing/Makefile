all: timing1 timing2

timing1: src/timing1.c
	gcc -o bin/timing1 $< -lm

timing2: src/timing2.c
	gcc -o bin/timing2 $< -lm

test: timing1 timing2
	./script/test.sh