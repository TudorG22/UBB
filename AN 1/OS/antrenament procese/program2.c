#include <stdio.h>
#include <stdlib.h>

#define MAX_DEPTH 10

void create_process(int depth) {
    pid_t pid;

    if (depth > 0) {
        printf("Parent: Creating process with depth %d\n", depth);
        pid = fork();

        if (pid == -1) {
            perror("fork() failed");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // This is the child process
            create_process(depth - 1);
            printf("Child: Exited with depth %d\n", depth);
            exit(EXIT_SUCCESS);
        } else {
            // This is the parent process
            printf("Parent: Waiting for child to exit with depth %d\n", 
depth);
            wait(NULL);
            printf("Parent: Child exited with depth %d\n", depth);
        }
    } else {
        printf("Final child reached the maximum depth\n");
    }
}

int main(int argc, char *argv[]) {
    int depth;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <depth>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    depth = atoi(argv[1]);

    create_process(depth);

    printf("Main process exiting\n");
    return 0;
}

