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

void pipes(int i, int PIPE_FLAGS, int I_FLAGS[256])
{
    int O_original = dup(1);
    int I_original = dup(0);
    int TRAIL_INDEX = 0;
    int fd[PIPE_FLAGS + 1][2];
    char STORE_STRING[256], TRAIL_STRING[256];
    memset(STORE_STRING, '\0', sizeof(STORE_STRING));
    memset(TRAIL_STRING, '\0', sizeof(TRAIL_STRING));
    strcpy(STORE_STRING, commands[i]);
    for (int j = 0; j < PIPE_FLAGS + 1; j++)
    {
        pipe(fd[j]);
        int x = fork();
        if (x == 0)
        {
            close(fd[j][0]);
            if (j == PIPE_FLAGS)
            {
                dup2(O_original, 1);
            }
            else
            {
                dup2(fd[j][1],1);
            }
            memset(commands[i], '\0', sizeof(commands[i]));
            if(j != 0)
            {
                TRAIL_INDEX = I_FLAGS[j - 1] + 2;
            }
            else
            {
                TRAIL_INDEX = 0;
            }
            int k = 0;
            int xx = strlen(STORE_STRING);
            while (STORE_STRING[TRAIL_INDEX] != '\0' && STORE_STRING[TRAIL_INDEX+1] != '|')
            {
                commands[i][k] = STORE_STRING[TRAIL_INDEX];
                k++;
                TRAIL_INDEX++;
            }            int flag = 0;
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
            close(fd[j][1]);
            exit(0);
        }
        else
        {
            close(fd[j][1]);
            wait(NULL);
            dup2(fd[j][0],0);
            close(fd[j][0]);
        }

    }
    dup2(O_original,1);
    dup2(I_original,0);
}
