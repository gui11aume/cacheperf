#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXCACHENB 8


int follow (int, int *);


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
   // For this, place each number at the position
   // indicated by the previous one.
   int j = new[0];

   for (int i = 1 ; i < nelem ; i++) {
      j = array[j] = new[i];
   }
   // We finally know where to place the first number.
   array[j] = new[0];

   // Free the temporary array and return.
   free(new);

   return array;

}


void
get_cache_sizes (
   size_t * cache_sizes
)
{

   int level = 0;
   for (int i = 0; i < MAXCACHENB ; i++) {

      // Variables to hold the contents of the 4 i386 legacy registers
      uint32_t eax, ebx, ecx, edx; 

      eax = 4; // get cache info
      ecx = i; // cache id

      // Generates output in 4 registers eax, ebx, ecx and edx.
      __asm__ (
         "cpuid"      // Call i386 'cpuid()' instruction.
         : "+a" (eax) // Contains cpuid command code, 4 for cache query.
         , "=b" (ebx)
         , "+c" (ecx) // Contains the cache id.
         , "=d" (edx)
      );

      int cache_type = eax & 0x1F; 

      if (cache_type == 0) // End of valid cache identifiers
         return;

//     char * cache_type_string;
//     switch (cache_type) {
//         case 1: cache_type_string = "Data Cache"; break;
//         case 2: cache_type_string = "Instruction Cache"; break;
//         case 3: cache_type_string = "Unified Cache"; break;
//         default: cache_type_string = "Unknown Type Cache"; break;
//     }
//
      if (cache_type == 2) // Not interested in L1i.
         continue;

      int cache_level = (eax >>= 5) & 0x7;

      int cache_is_self_initializing = (eax >>= 3) & 0x1; // does not need SW initialization
      int cache_is_fully_associative = (eax >>= 1) & 0x1;

      // ebx contains 3 integers of 10, 10 and 12 bits respectively
      unsigned int cache_sets = ecx + 1;
      unsigned int cache_coherency_line_size = (ebx & 0xFFF) + 1;
      unsigned int cache_physical_line_partitions = ((ebx >>= 12) & 0x3FF) + 1;
      unsigned int cache_ways_of_associativity = ((ebx >>= 10) & 0x3FF) + 1;

      size_t cache_total_size =
         cache_ways_of_associativity *
         cache_physical_line_partitions *
         cache_coherency_line_size *
         cache_sets;
      cache_sizes[level++] = cache_total_size; 

   }

   return;

}

int main(int argc, char **argv ) {


   // Timing estimates.
   double time[MAXCACHENB+1] = {0};
   size_t cache_sizes[MAXCACHENB+2] = {0};

   get_cache_sizes(cache_sizes);
   
   if (cache_sizes[0] == 0) {
      fprintf(stderr, "cannot find cache information\n");
      exit(EXIT_FAILURE);
   }

   for (int j = 0 ; cache_sizes[j] > 0 ; j++) {
      fprintf(stdout, "L%d cache size: %ld\n",
            j+1, cache_sizes[j]);
   }

   // Add an entry that is 5 times larger than
   // the last level cache.
   for (int i = MAXCACHENB+1 ; i > 1 ; i--) {
      if (cache_sizes[i] == 0) cache_sizes[i] = 5*cache_sizes[i-1];
   }

   for (int j = 0 ; cache_sizes[j] > 0 ; j++) {

      int sz = cache_sizes[j] / sizeof(int);
      int *array = malloc(sz * sizeof(int));
      if (array == NULL) crash();

      srand48(123);
      generate_one_cycle_perm(sz, array);
      
      clock_t start = clock();
      int a = follow(lrand48() % sz, array);
      clock_t end = clock();

      free(array);

      time[j] = (double)(end-start) / CLOCKS_PER_SEC;
      if (a < 0) { fprintf(stdout, "err\n"); }

   }

   double p; // Proportion of cache hits at the lower level.
   int j;

   double latency = time[0];
   printf("L1 hit:  ~ %.2f ns\n", latency);

   for (j = 1 ; cache_sizes[j+1] > 0 ; j++) {
      p = (double) cache_sizes[j-1] / (double) cache_sizes[j];
      latency = (time[j] - (latency * p)) / (1-p);
      printf("L%d hit:  ~ %.2f ns\n", j+1, latency);
   }

   p = (double) cache_sizes[j-1] / (double) cache_sizes[j];
   latency = (time[j] - (latency * p)) / (1-p);
   printf("L%d miss: ~ %.2f ns\n", j, latency);

   return 0;

}
