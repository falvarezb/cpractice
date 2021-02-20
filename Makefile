GCC = gcc
CFLAGS = -g -Wall -Wshadow
VALGRIND = valgrind --tool=memcheck --leak-check=full 
VALGRIND += --verbose --log-file=
BUILD_DIR = out


run: strlibrary
	./bin/strlibrary

# strlibrary: strlibrary.o
# 	$(GCC) $(CFLAGS) strlibrary.o -o $@ -lm

strtest: strlibrarytest
	./${BUILD_DIR}/strlibrarytest

mathtest: mathlibrarytest
	./${BUILD_DIR}/mathlibrarytest

biginttest: bigint_test
	./${BUILD_DIR}/bigint_test
	

strlibrarytest: strlibrary.o strlibrarytest.o
	$(GCC) $(CFLAGS) strlibrary.o strlibrarytest.o -o $@ -lm

mathlibrarytest: mathlibrary1.o mathlibrarytest.o
	$(GCC) $(CFLAGS) mathlibrary1.o mathlibrarytest.o -o $@ -lm

bigint_test: ${BUILD_DIR}/bigint.o ${BUILD_DIR}/biginttest.o
	$(GCC) $(CFLAGS) ${BUILD_DIR}/bigint.o ${BUILD_DIR}/biginttest.o -o ${BUILD_DIR}/$@ -lm


# if an object ﬁle is needed, compile the corresponding .c ﬁle
${BUILD_DIR}/%.o: %.c
	$(GCC) $(CFLAGS) -c $< -o $@

clean:
	rm -f outputs/* logs/* *.o ${BUILD_DIR}/*