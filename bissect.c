#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int    * ARRAY;
int    * COUNT;
double * TIME;

void crash (void) {
   fprintf(stderr, "memory error\n");
   exit(EXIT_FAILURE);
}


void
bissect
(
   int       lo,
   int       hi,
   double    x,
   int     * array
)
{
   int mid;
   // Cycle 1.
   mid = (lo+hi) / 2;
   if (x < array[mid]) hi = mid-1;
   else                lo = mid+1;
   if (hi < lo) return;
   // Cycle 2.
   mid = (lo+hi) / 2;
   if (x < array[mid]) hi = mid-1;
   else                lo = mid+1;
   if (hi < lo) return;
   // Cycle 3.
   mid = (lo+hi) / 2;
   if (x < array[mid]) hi = mid-1;
   else                lo = mid+1;
   if (hi < lo) return;
   // Cycle 4.
   mid = (lo+hi) / 2;
   if (x < array[mid]) hi = mid-1;
   else                lo = mid+1;
   if (hi < lo) return;
   // Cycle 5.
   mid = (lo+hi) / 2;
   if (x < array[mid]) hi = mid-1;
   else                lo = mid+1;
   if (hi < lo) return;
   // Cycle 6.
   mid = (lo+hi) / 2;
   if (x < array[mid]) hi = mid-1;
   else                lo = mid+1;
   if (hi < lo) return;
   // Cycle 7.
   mid = (lo+hi) / 2;
   if (x < array[mid]) hi = mid-1;
   else                lo = mid+1;
   if (hi < lo) return;
   // Cycle 8.
   mid = (lo+hi) / 2;
   if (x < array[mid]) hi = mid-1;
   else                lo = mid+1;
   if (hi < lo) return;
   // Cycle 9.
   mid = (lo+hi) / 2;
   if (x < array[mid]) hi = mid-1;
   else                lo = mid+1;
   if (hi < lo) return;
   // Cycle 10.
   mid = (lo+hi) / 2;
   if (x < array[mid]) hi = mid-1;
   else                lo = mid+1;
   if (hi < lo) return;
   // Cycle 11.
   mid = (lo+hi) / 2;
   if (x < array[mid]) hi = mid-1;
   else                lo = mid+1;
   if (hi < lo) return;
   // Cycle 12.
   mid = (lo+hi) / 2;
   if (x < array[mid]) hi = mid-1;
   else                lo = mid+1;
   if (hi < lo) return;
   // Cycle 13.
   mid = (lo+hi) / 2;
   if (x < array[mid]) hi = mid-1;
   else                lo = mid+1;
   if (hi < lo) return;
   // Cycle 14.
   mid = (lo+hi) / 2;
   if (x < array[mid]) hi = mid-1;
   else                lo = mid+1;
   if (hi < lo) return;
   // Cycle 15.
   mid = (lo+hi) / 2;
   if (x < array[mid]) hi = mid-1;
   else                lo = mid+1;
   if (hi < lo) return;
   // Cycle 16.
   mid = (lo+hi) / 2;
   if (x < array[mid]) hi = mid-1;
   else                lo = mid+1;
   if (hi < lo) return;
   // Cycle 17.
   mid = (lo+hi) / 2;
   if (x < array[mid]) hi = mid-1;
   else                lo = mid+1;
   if (hi < lo) return;
   // Cycle 18.
   mid = (lo+hi) / 2;
   if (x < array[mid]) hi = mid-1;
   else                lo = mid+1;
   if (hi < lo) return;
   // Cycle 19.
   mid = (lo+hi) / 2;
   if (x < array[mid]) hi = mid-1;
   else                lo = mid+1;
   if (hi < lo) return;
   // Cycle 20.
   mid = (lo+hi) / 2;
   if (x < array[mid]) hi = mid-1;
   else                lo = mid+1;
   if (hi < lo) return;
   // Cycle 21.
   mid = (lo+hi) / 2;
   if (x < array[mid]) hi = mid-1;
   else                lo = mid+1;
   if (hi < lo) return;
   // Cycle 22.
   mid = (lo+hi) / 2;
   if (x < array[mid]) hi = mid-1;
   else                lo = mid+1;
   if (hi < lo) return;
   // Cycle 23.
   mid = (lo+hi) / 2;
   if (x < array[mid]) hi = mid-1;
   else                lo = mid+1;
   if (hi < lo) return;
   // Cycle 24.
   mid = (lo+hi) / 2;
   if (x < array[mid]) hi = mid-1;
   else                lo = mid+1;
   if (hi < lo) return;
   // Cycle 25.
   mid = (lo+hi) / 2;
   if (x < array[mid]) hi = mid-1;
   else                lo = mid+1;
   if (hi < lo) return;
   // Cycle 26.
   mid = (lo+hi) / 2;
   if (x < array[mid]) hi = mid-1;
   else                lo = mid+1;
   if (hi < lo) return;
   // Cycle 27.
   mid = (lo+hi) / 2;
   if (x < array[mid]) hi = mid-1;
   else                lo = mid+1;
   if (hi < lo) return;
   // Cycle 28.
   mid = (lo+hi) / 2;
   if (x < array[mid]) hi = mid-1;
   else                lo = mid+1;
   if (hi < lo) return;
   // Cycle 29.
   mid = (lo+hi) / 2;
   if (x < array[mid]) hi = mid-1;
   else                lo = mid+1;
   if (hi < lo) return;
   // Cycle 30.
   mid = (lo+hi) / 2;
   if (x < array[mid]) hi = mid-1;
   else                lo = mid+1;
   if (hi < lo) return;
   // Cycle 31.
   mid = (lo+hi) / 2;
   if (x < array[mid]) hi = mid-1;
   else                lo = mid+1;
   if (hi < lo) return;
   // Cycle 32.
   mid = (lo+hi) / 2;
   if (x < array[mid]) hi = mid-1;
   else                lo = mid+1;
   if (hi < lo) return;
   return;
}


int main(int argc, char **argv ) {

#define M (1 << 30)

   // Allocate ~ 4 GB array.
   ARRAY = malloc(M * sizeof(int));
   if (ARRAY == NULL) crash();

   // Initialize array.
   for (int i = 0 ; i < M ; i++) ARRAY[i] = i;

   srand48(123);

   for (int i = 0 ; i < 1000000 ; i++) {
      bissect(0, M, drand48() * M, ARRAY);
   }

   return 0;

}
