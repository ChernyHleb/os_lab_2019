#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <signal.h>

int main(int argc, char **argv)
{
    int pid = fork();
    if(pid == 0)
    {
        execv("sequential_min_max", argv);
    }
    else 
    if(pid < 0) 
    {
        printf("Fork failed!");
        return -1;
    }

    return 0;
}