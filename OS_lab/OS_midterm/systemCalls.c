










/*
// passing message using pipes

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main()
{
    int pipe_fd[2];
    pid_t pid;

    char buffer[100];

    if (pipe(pipe_fd) == -1)
    {
        perror("pipe failed");
        return 1;
    }

    pid = fork();

    if (pid < 0)
    {
        perror("flok failed");
        return 1;
    }
    if (pid == 0)
    {
        close(pipe_fd[1]);
        read(pipe_fd[0], buffer, sizeof(buffer));
        printf("child received : %s\n", buffer);
        close(pipe_fd[0]);
    }
    else
    {
        close(pipe_fd[0]);
        const char *message = "Hello from parent!";
        write(pipe_fd[1], message, strlen(message) + 1);
        close(pipe_fd[1]);
    }

    return 0;
}

// Orphan process
/*

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    pid_t pid = fork();

    if(pid < 0){
        perror("fork failed");
        return 1;
    }
    if(pid == 0){
        printf("Child process PID : %d,Parent PID : %d\n", getpid(), getppid());
        sleep(10);
        printf("Child process after parent termination PID : %d, Parent PID : %d\n", getpid(), getppid());
    }
    else{
        printf("Parent PID : %d", getpid());
        sleep(2);
        exit(0);
    }

    return 0;
}



















// Zombie process

/*
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork failed");
        return 1;
    }
    if (pid == 0)
    {
        printf("child process PID : %d\n", getpid());
        exit(0);
    }
    else
    {
        printf("Parent process PID : %d\n", getpid());
        printf("Parent sleeping for 10 seconds ...\n");
        sleep(10);
        printf("Parent waking up should see zombie child process if checked with ps\n");
    }

    return 0;
}

// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>

// int main()
// {
//     pid_t pid = fork();

//     if (pid < 0)
//     {
//         perror("fork failed");
//         return 1;
//     }

//     if (pid == 0)
//     {
//         printf("Child process PID : %d, Parent PID : %d", getpid(), getppid());
//     }
//     else
//     {
//         printf("Parent process PID : %d, child process PID : %d", getpid(), pid);
//     }

//     return 0;
// }