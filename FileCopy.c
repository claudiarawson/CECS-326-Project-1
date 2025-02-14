#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define BUFFER_SIZE 25
#define STRING_SIZE 25

void read_func(const char *file) {
   FILE *stream=fopen(file,"r");
   char c;
   while((c=fgetc(stream)) != EOF) {
      putchar(c);
   }
   fclose(stream);
};

int main(int argc, char *argv[]) {
   if (argc != 3) {
      printf("Usage: ./file_name <source_file> <destination_file>\n");
      return 1;
   }
   char* sourceFile = argv[1];
   char*destinationFile = argv[2];
   printf("main\n");
   return 0;
}


