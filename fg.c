#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/utsname.h>
#include <signal.h>
#include <string.h>
#include <stdbool.h>
#include <fcntl.h>

void fg1(int x)
{
    int pid,indexesing;
    pid_t original_pid = getpid();
    for (int i = 0; i < 256; i++)
    {
        if (JOB_ORDER[i] == x && VALUE[i] == true)
        {
            pid = PIDS[i];
            indexesing = i;
            break;
        }
    }
    signal(SIGTTOU, SIG_IGN);
    signal(SIGTTOU, SIG_IGN);
    tcsetpgrp(0, getpgid(pid));
    kill(pid, SIGCONT);
    int q;
    waitpid(pid, &q, WUNTRACED);
    tcsetpgrp(0, original_pid);
    signal(SIGTTOU, SIG_DFL);
    signal(SIGTTIN, SIG_DFL);
    VALUE[indexesing] = false;
    if (WIFSTOPPED(q))
    {
        VALUE[indexesing] = true;
    }
}
void fg2(int x)
{
    int pid,indexesing;
    for (int i = 0; i < 256; i++)
    {
        if (JOB_ORDER[i] == x && VALUE[i] == true)
        {
            pid = PIDS[i];
            indexesing = i;
            break;
        }
    }
    kill(pid,SIGCONT);
    VALUE[indexesing] = 1;
}