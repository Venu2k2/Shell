#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include <string.h>
#include <sys/utsname.h>
#include <stdlib.h>
#include <stdbool.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <sys/types.h>
#include <limits.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>
#include <time.h>
void echo(int index, int value)
{
    if (IO_flag == 1)
    {
        if (greater_than == 1)
        {
            if (less_than == 0)
            {
                int k = 0;
                while (commands[index][k] != '>')
                {
                    k++;
                }
                k += 2;
                char file_name[256];
                memset(file_name, '\0', sizeof(file_name));
                int count = 0;
                while (k != strlen(commands[index]))
                {
                    file_name[count++] = commands[index][k++];
                }
                int fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                int original = dup(1);
                if (dup2(fd, 1) < 0)
                {
                    perror("Unable to duplicate file descriptor");
                    exit(1);
                }
                char printstring[256];
                memset(printstring, '\0', sizeof(printstring));
                k = 5;
                count = 0;
                while (commands[index][k] != '>')
                {
                    printstring[count++] = commands[index][k++];
                }
                printf("%s\n", printstring);
                close(fd);
                if (dup2(original, 1) < 0)
                {
                    perror("Couldn't change the STDOUT_FILENO");
                }
                return;
            }
        }
        if (greater_than == 2)
        {
            if (less_than == 0)
            {
                int k = 0;
                while (commands[index][k] != '>')
                {
                    k++;
                }
                k += 3;
                char file_name[256];
                memset(file_name, '\0', sizeof(file_name));
                int count = 0;
                while (k != strlen(commands[index]))
                {
                    file_name[count++] = commands[index][k++];
                }
                int fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
                int original;
                dup2(STDOUT_FILENO, original);
                if(dup2(fd, STDOUT_FILENO) < 0)
                {
                    perror("Unable to duplicate file descriptor");
                    exit(1);
                }
                char printstring[256];
                memset(printstring, '\0', sizeof(printstring));
                k = 5;
                count = 0;
                while (commands[index][k] != '>')
                {
                    printstring[count++] = commands[index][k++];
                }
                printf("%s\n", printstring);
                if(dup2(original, 1) < 0)
                {
                    perror("Couldn't change the STDOUT_FILENO");
                }
                close(fd);
                return;
            }
        }
    }
    printf("%s\n", &commands[index][value]);
}
