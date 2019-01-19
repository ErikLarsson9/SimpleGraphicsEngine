all: matrix.o graphics.o 
	gcc engine.c matrix.o graphics.o -lX11 -lm -o engine.bin
	


graphics.o: graphics.c
	gcc -c graphics.c 


matrix.o: matrix.c
	gcc -c matrix.c

clean:
	rm engine.bin matrix.o graphics.o


