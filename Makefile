go: follow.o cacheperf.c
	gcc -std=gnu99 -O0 -g cacheperf.c follow.o -o go

follow.o: follow.c 
	gcc -std=gnu99 -O2 -g -c follow.c

clean:
	rm go
