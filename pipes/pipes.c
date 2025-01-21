#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h> 

#define PIPE_READ_END 0
#define PIPE_WRITE_END 1

int main(void) {

    pid_t pid;
    int parent_to_child[2];  
    int child_to_parent[2];
    char byte;

    if (pipe(parent_to_child) == -1 || pipe(child_to_parent) == -1) {
        fprintf(stderr, "failed to create pipes\n");
        return EXIT_FAILURE; 
    }

    pid = fork();
    if (pid == -1) {
        fprintf(stderr, "failed to fork\n");
        return EXIT_FAILURE;
    }

    if (pid > 0) {
        close(parent_to_child[PIPE_READ_END]);
        close(child_to_parent[PIPE_WRITE_END]);

        while (read(STDIN_FILENO, &byte, 1) > 0) {
            if (write(parent_to_child[PIPE_WRITE_END], &byte, 1) != 1) {
                return EXIT_FAILURE;
            }

            if (read(child_to_parent[PIPE_READ_END], &byte, 1) != 1) {
                return EXIT_FAILURE;
            }

            printf("%c", byte);
        }

        close(parent_to_child[PIPE_WRITE_END]);
        close(child_to_parent[PIPE_READ_END]);

        wait(NULL);
    }
    else {  
        close(parent_to_child[PIPE_WRITE_END]);
        close(child_to_parent[PIPE_READ_END]);

        while (read(parent_to_child[PIPE_READ_END], &byte, 1) > 0) {
            byte = toupper(byte);

            if (write(child_to_parent[PIPE_WRITE_END], &byte, 1) != 1) {
                return EXIT_FAILURE;
            }
        }

        close(parent_to_child[PIPE_READ_END]);
        close(child_to_parent[PIPE_WRITE_END]);
    }

    return EXIT_SUCCESS; 
}