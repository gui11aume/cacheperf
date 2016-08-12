int follow
(
   int   pos,
   int * array
)
{

   for (int i = 0 ; i < 1000000000 ; i++) {
      pos = array[pos];
   }

   return pos;

}
