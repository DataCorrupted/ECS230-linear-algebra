SRC=src
TARGET=target
CC=gcc

.PHONY: all

all: mul mul_loop_O0 mul_loop_O2 mul_loop_O3 mul_BLAS

mul: $(SRC)/mul.c
	${CC} $^ -o $(TARGET)/$@

mul_loop_%: $(SRC)/mul_loop.c
	${CC} $^ -$* -DOPT_LEVEL=\"-$*\" -o $(TARGET)/$@

mul_BLAS: $(SRC)/mul_BLAS.c
	${CC} $^ -o $(TARGET)/$@ -lblas

clean: 
	rm $(TARGET)/mul*