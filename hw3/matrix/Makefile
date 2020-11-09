SRC=src
TARGET=target

.PHONY: all

all: mul mul_loop_O0 mul_loop_O2 mul_loop_O3 mul_BLAS

mul: $(SRC)/mul.c
	gcc $^ -o $(TARGET)/$@

mul_loop_%: $(SRC)/mul_loop.c
	gcc $^ -$* -o $(TARGET)/$@

mul_BLAS: $(SRC)/mul_BLAS.c
	gcc $^ -o $(TARGET)/$@ -lblas

clean: 
	rm $(TARGET)/mul*