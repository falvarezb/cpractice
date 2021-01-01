GCC = gcc
CFLAGS = -g -Wall -Wshadow
VALGRIND = valgrind --tool=memcheck --leak-check=full 
VALGRIND += --verbose --log-file=


run: strlibrary
	./strlibrary

# strlibrary: strlibrary.o
# 	$(GCC) $(CFLAGS) strlibrary.o -o $@ -lm

# mathlibrary: strlibrary.o
# 	$(GCC) $(CFLAGS) mathlibrary.o -o $@ -lm

strtest: strlibrarytest
	./strlibrarytest

mathtest: mathlibrarytest
	./mathlibrarytest
	

# $@ means the symbol before the :
strlibrarytest: strlibrary.o strlibrarytest.o
	$(GCC) $(CFLAGS) strlibrary.o strlibrarytest.o -o $@ -lm

mathlibrarytest: mathlibrary1.o mathlibrarytest.o
	$(GCC) $(CFLAGS) mathlibrary1.o mathlibrarytest.o -o $@ -lm


# if an object ﬁle is needed, compile the corresponding .c ﬁle
.c.o:
	$(GCC) $(CFLAGS) -c $*.c	

clean:
	rm -f outputs/* logs/* *.o strlibrarytest