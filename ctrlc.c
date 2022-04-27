#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>
#include <string.h>
#include <stdbool.h>
#include <fcntl.h>

void ctrlc(int signum)
{
    pid_t pid = getpid();
    if(pid < 0)
    {
        perror("Can't get pid") ;
    }
    if(sid != pid)
    {
        return;
    }
    else
    {
        if(cid != -1)
        {
            int kid = kill(cid,signum) ;
            if(kid < 0)
            {
                perror("Can't use kill") ;
                return ;
            }
        }
        else
        {
            printf("\n") ;
            display() ;
            fflush(stdout) ;
        }
    }
}