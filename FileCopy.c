#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#define BUFFER_SIZE 25
#define STRING_SIZE 25

// Function that reads an input file
void read_func(int fd, const char *destinationFile) {
    // Open Output File and File Stream (for pipe file descriptor)
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

    // Read from pipe and write to destination file
    char buffer[BUFFER_SIZE];
    while((fgets(buffer, BUFFER_SIZE, stream)) != NULL) {
        fputs(buffer, destination);
    }

    // Close files
    fclose(stream);
    fclose(destination);
};

// Function that writes to an output file
void write_func(int fd, const char *sourceFile) {
    // Open Input File and File Stream (for pipe file descriptor)
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

    // Read the input File into the Pipe
    char buffer[BUFFER_SIZE];
    while (fgets(buffer, BUFFER_SIZE, src) != NULL) {
        fputs(buffer, stream);
    }

    // Close Files
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
    
    // Create pipe
    int arr[2]; // arr[0] = readEnd | arr[1] = writeEnd

    //Error Handling
    if (pipe(arr) != 0) {
        fprintf(stderr, "Condition for Pipe Failed\n");
        return EXIT_FAILURE;
    }
    
    // Fork Child Process -- Everything past this point is run by two processes (Parent > 0 & Child 0)
    pid_t pid = fork(); // Outputs: 0 = Child | > 0 Parent | -1 = Error

    // Child process
    if (pid == 0) {
        close(arr[1]); // Close writeEnd (only used for parent)
        read_func(arr[0], destinationFile); // Reads pipeWriteEnd into destinationFile
        close(arr[0]); // Close readEnd 
        printf("Child Process Completed -- Written to Destination\n");
        return EXIT_SUCCESS;
    }

    // Parent process
    if (pid > 0) {
        close(arr[0]); // Close readEnd (only used for child)
        write_func(arr[1], sourceFile); // Read sourceFile content and write to Pipe
        close(arr[1]); // Close writeEnd
        printf("Parent Process Completed -- Read From Source\n");
        wait(NULL); // Lets child process finish before return
        printf("File successfully copied from %s to %s.\n", sourceFile, destinationFile);
        return EXIT_SUCCESS;
    }

    // Fork Error Handling  
    else {
        fprintf(stderr, "Fork Failed\n");
        return EXIT_FAILURE;
    }
    return 0;
}