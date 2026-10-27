#include <errno.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <sys/types.h> 
#include <sys/wait.h> 
#include <unistd.h> 
int main(void) { 
    pid_t pid = fork(); 
    if (pid < 0) { perror("fork"); return EXIT_FAILURE; } 
    if (pid == 0) { 
        puts("Child: executing /bin/echo"); 
        execl("/bin/echo", "echo", "Hello from exec", (char *)NULL); 
        perror("execl"); 
        _exit(127); 
    } 
    int status; 
    if (waitpid(pid, &status, 0) < 0) { perror("waitpid"); return EXIT_FAILURE; } 
    if (WIFEXITED(status)) 
        printf("Parent: child exit status = %d\n", WEXITSTATUS(status)); 
    return EXIT_SUCCESS; 
} 
