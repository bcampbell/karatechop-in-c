tests: tests.c chop.c
	gcc -O3 tests.c chop.c -lcheck -o tests

test: tests
	./tests

