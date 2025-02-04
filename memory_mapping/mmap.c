#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void) {
    int *addr;

    addr = mmap(NULL, sizeof(*addr), PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANON, -1, 0);
    if (addr == MAP_FAILED) {
        fprintf(stderr, "mmap failed\n");
        exit(EXIT_FAILURE);
    }

    *addr = 1;

    switch(fork()) {
        case -1:
            fprintf(stderr, "fork failed\n");
            munmap(addr, sizeof(*addr));
            exit(EXIT_FAILURE);
        
        case 0:
            printf("Child: value = %d\n", *addr);
            (*addr)++;
            munmap(addr, sizeof(*addr));
            exit(EXIT_SUCCESS);

        default:
            wait(NULL);
            printf("Parent: value = %d\n", *addr);
            munmap(addr, sizeof(*addr));
            exit(EXIT_SUCCESS);
    }
}