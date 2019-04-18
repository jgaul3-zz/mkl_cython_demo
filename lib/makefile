CC := icc

default: libmm.a

mm: mm.o
	$(CC) $^ -mkl -static-intel -o $@

libmm.a: mm.o
	ar rcs $@ $^

mm.o: mm.c
	$(CC) -c mm.c

clean:
	rm *.o *.a
