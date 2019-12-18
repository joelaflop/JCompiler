jc : jc.c writer.c writer.h token.c token.h stack.c stack.h
	clang -Wall -o jc jc.c token.c writer.c stack.c
clean : 
	rm jc *.o