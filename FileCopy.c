#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#define BUFFER_SIZE 25
#define STRING_SIZE 25

// Function that reads an input file
void read_func(int fd, const char *destinationFile) {
    FILE *stream = fdopen(fd,"r");
    FILE *destination = fopen(destinationFile, "w");
    // Error Handling
    if (stream == NULL) {
        perror("read_func -- stream fdopen");
        exit(EXIT_FAILURE);
    }
    if (destination == NULL) {
        perror("read_func -- destination fopen");
        exit(EXIT_FAILURE);
    }

    // Copy Data
    char buffer[BUFFER_SIZE];
    while((fgets(buffer, BUFFER_SIZE, stream)) != NULL) {
        fputs(buffer, destination);
    }
    fclose(stream);
    fclose(destination);
};

// Function that writes to an output file
void write_func(int fd, const char *sourceFile) {
    FILE *src = fopen(sourceFile, "r");
    FILE *stream = fdopen(fd, "w");
    // Error Handling
    if (src == NULL) {
        perror("write_func -- src fopen");
        exit(EXIT_FAILURE);
    }
    if (stream == NULL) {
        perror("write_func -- stream fdopen");
        exit(EXIT_FAILURE);
    }

    // Paste Data
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

    // Store command line arguments
    char *sourceFile = argv[1];
    char *destinationFile = argv[2];
    int arr[2];
    
    // Create a pipe
    if (pipe(arr) != 0) {
        fprintf(stderr, "Condition for Pipe Failed\n");
        return EXIT_FAILURE;
    }
    
    pid_t pid = fork();

    // Child process
    if (pid == 0) {
        close(arr[1]);
        read_func(arr[0], destinationFile);
        close(arr[0]);
        printf("Child Process\n");
        return EXIT_SUCCESS;
    }

    // Parent process
    if (pid >= 0) {
        close(arr[0]);
        write_func(arr[1], sourceFile);
        close(arr[1]);
        printf("Parent Process\n");
        wait(NULL);
        return EXIT_SUCCESS;
    }

    // Error process
    else {
        fprintf(stderr, "Fork Failed\n");
        return EXIT_FAILURE;
    }

    return 0;
}