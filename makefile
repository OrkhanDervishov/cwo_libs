run: test
	./test

gauss: gauss.c
	gcc -Wall -Wextra -o test gauss.c -lm


test: test.c
	gcc -Wall -Wextra -o test test.c -lm