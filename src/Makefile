all: pa5test

clean:
	rm -f pa5test

pa5test: pa5test.c
	gcc -Wall -Werror -g pa5test.c -o pa5test

test: pa5test
	python3 ../test_pa5.py