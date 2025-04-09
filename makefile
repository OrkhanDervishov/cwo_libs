run: test
	clear
	./test

gauss: gauss.c
	gcc -W -Wextra -o test gauss.c


test: test.c
	gcc -W -Wextra -o test test.c