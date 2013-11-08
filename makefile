all:
	gcc -g -o router router.c
	gcc -g -o tests/testNode tests/testNode_.c
	gcc -g -o tests/testLSP tests/testLSP_.c

clean:
	rm -rf router tests/testNode tests/testLSP
