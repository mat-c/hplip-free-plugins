lj.so: libj.o
	$(CC) $(LDLAFS) -shared libj.o -ljbig -o lj.so

libj.o: libj.c
test_lj.o: test_lj.c


test_lj: test_lj.o
	$(CC) $(LDLAFS) test_lj.o -L. -l:lj.so -o test_lj

clean:
	rm libj.o test_lj.o test_lj lj.so
