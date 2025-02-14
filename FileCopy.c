#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#define BUFFER_SIZE 25
#define STRING_SIZE 25

// Function that reads a input file
void read_func(int fd, const char *destinationFile) {
   FILE *stream = fdopen(fd,"r");
   FILE *destination = fopen(destinationFile, "w");
   char buffer[BUFFER_SIZE];
   while((fgets(buffer, BUFFER_SIZE, stream)) != NULL) {
      fputs(buffer, destination);
   }
   fclose(stream);
};

// Function that writes to an output file
void write_func(int fd, const char *sourceFile) {
   FILE *src = fopen(sourceFile, "r");
   FILE *stream = fdopen(fd, "w");
   char buffer[BUFFER_SIZE];
   while (fgets(buffer, BUFFER_SIZE, src) != NULL) {
      fputs(buffer, stream);
   }
   fclose(src);
   fclose(stream);
}

// Main function
int main(int argc, char *argv[]) {
   // Identify command line usage if argument count is not 3
   if (argc != 3) {
      printf("Usage: ./file_name <source_file> <destination_file>\n");
      return 1;
   }

   char *sourceFile = argv[1];
   char *destinationFile = argv[2];
   int arr[2];
   
   // Create a pipe
   if (pipe(arr) != 0) {
      fprintf(stderr, "Condition for Pipe Failed");
      return EXIT_FAILURE;
   }
   
   pid_t pid = fork();

   // Child process
   if (pid == 0) {
      close(arr[1]);
      read_func(arr[0], destinationFile);
      close(arr[0]);
      printf("child process");
      return EXIT_SUCCESS;
   }

   // Parent process
   if (pid >= 0) {
      close(arr[0]);
      write_func(arr[1], sourceFile);
      close(arr[1]);
      printf("parent process");
      wait(NULL);
      return EXIT_SUCCESS;
   }

   // Error process
   else {
      fprintf(stderr, "The Fork Failed");
      return EXIT_FAILURE;
   }
   return 0;
}


