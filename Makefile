GCC = gcc
CFLAGS = -g -Wall -Wextra -Wshadow -std=c11 -Wpedantic
VALGRIND = valgrind --tool=memcheck --leak-check=full 
VALGRIND += --verbose --log-file=
BUILD_DIR = out
BIGINT_OBJS = ${BUILD_DIR}/bigint_calculator.o ${BUILD_DIR}/bigint_parser.o ${BUILD_DIR}/bigint_arithmetic.o ${BUILD_DIR}/bigint_calculator_test.o


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

bigintcalculator: bigint_calculator
	./${BUILD_DIR}/bigint_calculator

bigintparser: bigint_parser
	./${BUILD_DIR}/$^

bigintarithmetic: bigint_arithmetic
	./${BUILD_DIR}/$^
	

strlibrarytest: strlibrary.o strlibrarytest.o
	$(GCC) $(CFLAGS) strlibrary.o strlibrarytest.o -o $@ -lm

mathlibrarytest: mathlibrary1.o mathlibrarytest.o
	$(GCC) $(CFLAGS) mathlibrary1.o mathlibrarytest.o -o $@ -lm

bigint_calculator: $(BIGINT_OBJS)
	$(GCC) $(CFLAGS) $^ -o ${BUILD_DIR}/$@ -lm

bigint_parser: ${BUILD_DIR}/bigint_parser.o ${BUILD_DIR}/bigint_parser_test.o
	$(GCC) $(CFLAGS) $^ -o ${BUILD_DIR}/$@ -lm

bigint_arithmetic: ${BUILD_DIR}/bigint_arithmetic.o ${BUILD_DIR}/bigint_arithmetic_test_cmocka.o
	$(GCC) $(CFLAGS) $^ -o ${BUILD_DIR}/$@ -lm -lcmocka


# if an object ﬁle is needed, compile the corresponding .c ﬁle
${BUILD_DIR}/%.o: %.c
	$(GCC) $(CFLAGS) -c $< -o $@

clean:
	rm -f outputs/* logs/* *.o ${BUILD_DIR}/*