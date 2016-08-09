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

int main(int argc, char **argv ) {


   int sz = 1 << 30;
   int *array = malloc(sz * sizeof(int));
   if (array == NULL) crash();

   srand48(123);

   generate_one_cycle_perm(sz, array);

   FILE *f = fopen("array.dat", "w");
   if (f == NULL) exit(EXIT_FAILURE);
   
   fwrite(array, sizeof(int), sz, f);

   return 0;

}
