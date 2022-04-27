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
int VARIABLE = 0;
char real_cwd[256];
char command[256];
char commands[256][256];
int indexes = 0;
struct passwd *USER;
int PIDS[256];
char NAMES[256][256];
bool VALUE[256];
int JOB_ORDER[256];
int PIDS_VALUES = 0;
char cdhistory[2][256];
int cd_index = 0;
int IO_flag = 0;
int greater_than = 0;
int less_than = 0;
int original_fd;
int sid;
int cid;
#include "pinfo.c"
#include "display.c"
#include "cd.c"
#include "echo.c"
#include "pwd.c"
#include "ls.c"
#include "bg.c"
#include "ctrlc.c"
#include "pipe.c"
#include "jobs.c"
#include "fg.c"
void func()
{
    int q;
    int pid = waitpid(-1, &q, WNOHANG | WUNTRACED);
    for (int i = 0; i < 256; i++)
    {
        if (PIDS[i] == pid && VALUE[i] == true && WIFEXITED(q) > 0)
        {
            VALUE[i] = false;
            printf("%s with pid %d exited normally\n", NAMES[i], PIDS[i]);
            break;
        }
        if (PIDS[i] == pid && VALUE[i] == true && WIFSIGNALED(q) == 1)
        {
            VALUE[i] = false;
            printf("%s with pid %d exited abnormally\n", NAMES[i], PIDS[i]);
            break;
        }
    }
}
void ctrlz()
{
    if(cid != sid)
    {
        kill(cid,SIGSTOP);
    }
    else
    {
        display();
    }
}
int main()
{
    cid = -1;
    dup2(STDOUT_FILENO, original_fd);
    memset(PIDS, 0, sizeof(PIDS));
    memset(NAMES, '\0', sizeof(NAMES));
    memset(VALUE, false, sizeof(VALUE));
    memset(cdhistory, '\0', sizeof(cdhistory));
    signal(SIGTSTP,SIG_DFL);
    signal(SIGCHLD, func);
    signal(SIGINT, ctrlc);
    signal(SIGTSTP, ctrlz);
    pid_t p_id;
    p_id = getpid();
    sid = p_id;
    if (getcwd(real_cwd, sizeof(real_cwd)) == NULL)
    {
        printf("Unable to get the scommand!\n");
        perror("getcwd() error");
    }
    strcpy(cdhistory[0], real_cwd);
    while (1)
    {
        cid = -1;
        memset(commands, '\0', sizeof(commands));
        memset(command, '\0', sizeof(command));
        display();
        gets(command);
        if (feof(stdin))
        {
            exit(0);
        }
        if (command[0] == '\0')
        {
            continue;
        }
        char *token;
        char dummy[256];
        memset(dummy, '\0', sizeof(dummy));
        char x = ' ';
        char y = '\t';
        int count = 0;
        token = strtok(command, " "
                                "\t");
        while (token != NULL)
        {
            for (int i = 0; i < strlen(token); i++)
            {
                dummy[count] = token[i];
                count++;
            }
            if (dummy[count - 1] != ';' && dummy[count] != ';')
            {
                dummy[count] = ' ';
                count++;
            }
            token = strtok(NULL, " "
                                 "\t");
        }
        dummy[count - 1] = '\0';
        count--;
        //printf("%s\n\n\n",dummy);
        int j = 0;
        for (int i = 0; i < strlen(dummy); i++)
        {
            if (dummy[i] == ';')
            {
                commands[indexes][j - 1] = '\0';
                indexes++;
                j = 0;
            }
            else
            {
                commands[indexes][j] = dummy[i];
                j++;
            }
        }
        for (int i = 0; i <= indexes; i++)
        {
            int I_FLAGS[256];
            int I_FLAGS_INDEX = 0;
            int PIPE_FLAG = 0;
            IO_flag = 0;
            greater_than = 0;
            less_than = 0;
            for (int j = 0; j < strlen(commands[i]); j++)
            {
                if (commands[i][j] == '>')
                {
                    IO_flag = 1;
                    greater_than = 1;
                }
                if (commands[i][j] == '<')
                {
                    IO_flag = 1;
                    less_than = 1;
                }
                if (j != strlen(commands[i]) - 1 && commands[i][j] == '>' && commands[i][j + 1] == '>')
                {
                    IO_flag = 1;
                    greater_than = 2;
                    break;
                }
                if (commands[i][j] == '|')
                {
                    PIPE_FLAG++;
                    I_FLAGS[I_FLAGS_INDEX++] = j;
                }
            }
            int flag = 0;
            int flag1 = 0;
            int flag2 = 0;
            int flag_index = 0;
            int directories = 0;
            char Directories[256][256];
            memset(Directories, '\0', sizeof(Directories));
            int directory_index = 0;
            int x = 1;
            if (strcmp(commands[i], "quit") == 0)
            {
                exit(0);
            }
            if (commands[i][0] == 'r' && commands[i][1] == 'e')
            {
                char number[100];
                int count = 0;
                memset(number, '\0', sizeof(number));
                int j = 7;
                for (j = 7;; j++)
                {
                    if (commands[i][j] == ' ')
                    {
                        break;
                    }
                    else
                    {
                        number[count++] = commands[i][j];
                        continue;
                    }
                }
                x = atoi(number);
                char trail[256];
                memset(trail, '\0', sizeof(trail));
                strcpy(trail, &commands[i][j + 1]);
                strcpy(commands[i], trail);
            }
            for (int k = 0; k < x; k++)
            {
                for (int j = 3; j < strlen(commands[i]); j++)
                {
                    if (commands[i][j] == ' ')
                    {
                        continue;
                    }
                    if (commands[i][j] == '-')
                    {
                        flag++;
                        if (commands[i][j + 1] == 'a')
                        {
                            flag1++;
                        }
                        if (commands[i][j + 1] == 'l')
                        {
                            flag2++;
                        }
                        if (commands[i][j + 2] == 'a')
                        {
                            flag1++;
                            j++;
                        }
                        if (commands[i][j + 2] == 'l')
                        {
                            flag2++;
                            j++;
                        }
                        j++;
                    }
                    else
                    {
                        while (commands[i][j] != ' ' && commands[i][j] != '\0')
                        {
                            Directories[directories][directory_index++] = commands[i][j];
                            j++;
                        }
                        directory_index = 0;
                        directories++;
                    }
                }
                if (commands[i][0] == 'j' && commands[i][1] == 'o')
                {
                    int flagging = 0;
                    if (commands[i][6] == 'r')
                    {
                        flagging = 1;
                    }
                    if (commands[i][6] == 's')
                    {
                        flagging = 2;
                    }
                    job_printing(flagging);
                    continue;
                }
                if (PIPE_FLAG != 0)
                {
                    pipes(i, PIPE_FLAG, I_FLAGS);
                    continue;
                }
                if (commands[i][0] == 's' && commands[i][1] == 'i')
                {
                    char number1[256];
                    char number2[256];
                    memset(number1, '\0', sizeof(number1));
                    memset(number2, '\0', sizeof(number2));
                    int k = 4, countings = 0;
                    while (commands[i][k] != ' ')
                    {
                        number1[countings] = commands[i][k];
                        countings++;
                        k++;
                    }
                    k++;
                    countings = 0;
                    while (commands[i][k] != '\0')
                    {
                        number2[countings] = commands[i][k];
                        countings++;
                        k++;
                    }
                    int job_number = atoi(number1);
                    int sig_number = atoi(number2);
                    jobs_sorting();
                    int required_pid;
                    for (int i = 0; i < 256; i++)
                    {
                        if (JOB_ORDER[i] == job_number && VALUE[i] == true)
                        {
                            required_pid = PIDS[i];
                            break;
                        }
                    }
                    if (kill(required_pid, sig_number) < 0)
                    {
                        perror("kill()");
                    }
                    continue;
                    ;
                }
                if (commands[i][0] == 'f' && commands[i][1] == 'g')
                {
                    jobs_sorting();
                    int x;
                    char number[256];
                    memset(number, '\0', sizeof(number));
                    int k = 3, counting = 0;
                    while (commands[i][k] != '\0')
                    {
                        number[counting] = commands[i][k];
                        k++;
                        counting++;
                    }
                    x = atoi(number);
                    fg1(x);
                    continue;
                }
                if (commands[i][0] == 'b' && commands[i][1] == 'g')
                {
                    jobs_sorting();
                    int x;
                    char number[256];
                    memset(number, '\0', sizeof(number));
                    int k = 3, counting = 0;
                    while (commands[i][k] != '\0')
                    {
                        number[counting] = commands[i][k];
                        k++;
                        counting++;
                    }
                    x = atoi(number);
                    fg2(x);
                    continue;
                }
                if (commands[i][0] == 'c' && commands[i][1] == 'd')
                {
                    cdactual(i, Directories);
                    continue;
                }
                if (commands[i][0] == 'e' && commands[i][1] == 'c')
                {
                    echo(i, 5);
                    continue;
                }
                if (commands[i][0] == 'p' && commands[i][1] == 'w')
                {
                    pwd(i);
                    continue;
                }
                if (commands[i][0] == 'l' && commands[i][1] == 's')
                {
                    lsactual(i, directories, flag1, flag2, flag, Directories);
                    continue;
                }
                if (commands[i][0] == 'p' && commands[i][1] == 'i')
                {
                    if (commands[i][5] == '\0' || commands[i][6] == '>')
                    {
                        pinfo(i);
                        continue;
                    }
                    else
                    {
                        pinfo1(i);
                        continue;
                    }
                }
                bg(i);
                continue;
            }
        }
    }
}
