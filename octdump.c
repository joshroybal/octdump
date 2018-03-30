#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char *argv[])
{
   int i, n, noblanks, address = 0;
   unsigned char word[8];
   FILE *fp;
   
   if (argc < 2) {
      fprintf(stderr, "Usage: %s filename\n", argv[0]);
      return(1);
   }

   if ( ( fp = fopen(argv[1], "rb") ) == NULL ) {
      fprintf(stderr, "ERROR - opening file %s failed.\n", argv[1]);
      return(1);
   }

   memset(word, 0, sizeof(word));
   n = fread(word, sizeof(unsigned char), sizeof(word), fp);
   while (n == sizeof(word)) {
      printf(" %#012o ", address);
      for (i = 0; i < 8; ++i)
         printf(" %#04o", word[i]);
      printf("  |");
      for (i = 0; i < 8; ++i)
         if (isprint(word[i]))
            putchar(word[i]);
         else
            putchar('.');
      printf("|\n");
      address += 8;
      memset(word, 0, sizeof(word));
      n = fread(word, sizeof(unsigned char), sizeof(word), fp);
   }
   
   fclose(fp);

   if (n > 0) {   /* dump any trailing bytes */
      printf(" %#012o ", address);
      for (i = 0; i < n; ++i)
         printf(" %#04o", word[i]);
      noblanks = 5*(8-n);
      for (i = 0; i < noblanks; ++i)
         putchar(' ');
      printf("  |");
      for (i = 0; i < n; ++i)
         if (isprint(word[i]))
            putchar(word[i]);
         else
            putchar('.');
      printf("|\n");
   }

   return(0);
}
