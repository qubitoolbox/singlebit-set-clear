

bitops:bitops.o
	gcc -o bitops bitops.c

clean:
	rm -f bitops bitops.o core *~
