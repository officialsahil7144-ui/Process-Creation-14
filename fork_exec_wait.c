#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    }

    if (pid == 0) {
        printf("Child process created.\n");
        printf("Child PID: %d\n", getpid());

        execlp("ls", "ls", "-l", (char *)NULL);

        perror("exec failed");
        _exit(1);
    } else {
        printf("Parent process waiting for child...\n");

        int status;
        if (wait(&status) == -1) {
            perror("wait failed");
            return 1;
        }

        printf("Child process completed.\n");
    }

    return 0;
}
