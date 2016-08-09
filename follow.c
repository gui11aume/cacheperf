#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifndef EXTRA
#define EXTRA 0;
#endif

void crash (void) {
   fprintf(stderr, "memory error\n");
   exit(EXIT_FAILURE);
}


int *
generate_one_cycle_perm
(
   int   nelem,
   int * array
)
// Use the cycle notation to easily generate a
// permutation with a single cycle. This uses the
// Durstenfeld version of the Fisher-Yates algorithm.
{

   int *new = malloc(nelem * sizeof(int));
   if (new == NULL) crash();

   // Initialize with integers.
   for (int i = 0 ; i < nelem ; i++) new[i] = i;

   for (int i = nelem-1 ; i > 0 ; i-- ) {
      // Take an element between 0 and i at random,
      // and swap it with element at position i.
      int j = lrand48() % (i+1);
      int tmp = new[i];
      new[i] = new[j];
      new[j] = tmp;
   }

   // Now write the permutation in regular form.
   int j = new[0];

   for (int i = 1 ; i < nelem ; i++) {
      j = array[j] = new[i];
   }
   array[j] = new[0];

   free(new);

   return array;

}


int
follow
(
   int   pos,
   int * array
)
{


   for (int i = 0 ; i < 100000000 ; i++) {
      pos = array[pos];
   }

   return pos;

}

int main(int argc, char **argv ) {


//   for (int j = 7 ; j < 31 ; j++) {
   for (int j = 30 ; j < 31 ; j++) {

//      int sz = 1 << j;
      int sz = 15728640/4;
      int *array = malloc(sz * sizeof(int));
      if (array == NULL) crash();

      srand48(123);
      generate_one_cycle_perm(sz, array);
      
      // Read from file.
//      FILE *f = fopen("array.dat", "r");
//      if (f == NULL) exit(EXIT_FAILURE);
//      fread(array, sizeof(int), sz, f);

      clock_t start = clock();
      int a = follow(lrand48() % sz, array);
      clock_t end = clock();

      free(array);

      fprintf(stdout, "%f\n", (double)(end-start) / CLOCKS_PER_SEC);

   }

   return 0;

}
