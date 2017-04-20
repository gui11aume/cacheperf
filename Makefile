go: follow.o mt.o cacheperf.c
	gcc -std=gnu99 -O0 -g cacheperf.c follow.o mt.o -o go

follow.o: follow.c mt.o
	gcc -std=gnu99 -O2 -g -c follow.c

mt.o: mt.c mt.h
	gcc -std=gnu99 -O2 -g -c mt.c

clean:
	rm go
