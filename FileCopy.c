/*
 * FileCopy.c
 * 
 * This program opens a file and writes its contents to a pipe 
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define BUFFER_SIZE 25
#define STRING_SIZE 25

void read_func(const char *file) {
   FILE *stream=fopen(file,"r");
   char c;
   while((c=fgetc(stream)) != EOF) {
      putchar(c);
   }
   fclose(stream);
   printf("hello world");
}

int main(int argc, char *argv[]) {
   char* sourceFile = argv[0];
   char*destinationFile = argv[1];
   
}
