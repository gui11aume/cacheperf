#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void crash (void) {
   fprintf(stderr, "memory error\n");
   exit(EXIT_FAILURE);
}


int main(int argc, char **argv ) {

   int sz[19] = {14,15,16,17,18,19,
      20,21,22,23,24,25,26,27,28,29,30,31,32};

   for (int j = 0 ; j < 19 ; j++) {

      uint8_t *array = malloc(1 << j);
      if (array == NULL) crash();

      const int steps = 256 * 1024 * 1024; // Arbitrary number of steps
      int lengthMod = (1 << j) - 1;
      clock_t start = clock();
      for (int i = 0; i < steps; i++) {
          array[i & lengthMod]++; // (x & lengthMod) is equal to (x % arr.Length)
      }
      clock_t end = clock();

      fprintf(stdout, "%ld\n", (uintmax_t) end - (uintmax_t) start);

      free(array);

   }

   return 0;

}
