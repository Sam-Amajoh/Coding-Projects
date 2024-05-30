CC=gcc
CFLAGS=-Wall

dcooke_analyzer: P1.o front.h
	$(CC) P1.o -o dcooke_analyzer

P1.o: P1.c front.h
	$(CC) -c P1.c -o P1.o $(CFLAGS)

clean:
	rm -f P1.o dcooke_analyzer 
	
