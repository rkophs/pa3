all:
	gcc -g -o router router.c
	gcc -g -o tests/testNode tests/testNode_.c
	gcc -g -o tests/testLSP tests/testLSP_.c
	gcc -g -o tests/testLspPool tests/testLspPool_.c
	gcc -g -o tests/testLspPoolCtrl tests/testLspPoolCtrl_.c
	
clean:
	rm -rf router tests/testNode tests/testLSP tests/testLspPool tests/testLspPoolCtrl
