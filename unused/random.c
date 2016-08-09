#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifndef EXTRA
#define EXTRA 100000
#endif


void crash (void) {
   fprintf(stderr, "memory error\n");
   exit(EXIT_FAILURE);
}


int
jump
(
   int   nelem,
   int * array
)
{

   int j = 0;
   for (int i = 0 ; i < 1000 ; i++) {
      j += array[lrand48() % nelem];
   }

   return j;

}

int
jump_ctrl
(
   int   nelem,
   int * array
)
{

   int j = 0;
   for (int i = 0 ; i < 1000 ; i++) {
      j += lrand48() % nelem;
   }

   return j;

}

int main(int argc, char **argv ) {

   unsigned int sz = 1000000000;

   int * array = malloc(sz * sizeof(int));
   if (array == NULL) crash();

   srand48(123);


   volatile uintmax_t time = 0;

   clock_t start = clock();
   for (int i = 0 ; i < 100000 ; i++) {
      int a = jump(sz, array);
   }
   clock_t end = clock();

   free(array);

   fprintf(stdout, "%f\n", (double) (end-start) / CLOCKS_PER_SEC);

   start = clock();
   for (int i = 0 ; i < 100000 ; i++) {
      int a = jump_ctrl(sz, array);
   }
   end = clock();

   fprintf(stdout, "%f\n", (double) (end-start) / CLOCKS_PER_SEC);

   return 0;

}
