follow: follow.c
	gcc -std=gnu99 -O0 -g bissect.c -o follow
	valgrind --tool=cachegrind
	cg_annotate --auto=yes cachegrind.*

bissect: bissect.c
	gcc -std=gnu99 -O0 -g bissect.c -o bis
