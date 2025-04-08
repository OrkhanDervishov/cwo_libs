run: test
	./test

build: test.c
	gcc -o test test.c