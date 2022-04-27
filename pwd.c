#include <stdio.h>
#include <stdlib.h>
#include <sys/utsname.h>
#include <pwd.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
void pwd(int index)
{
    char present[256];
    if (getcwd(present, sizeof(present)) == NULL)
    {
        printf("Cannot get the current working directory: ");
        perror("getcwd() error : ");
    }
    else
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
                    printf("%s\n", present);
                    if (dup2(original, 1) < 0)
                    {
                        perror("Couldn't change the STDOUT_FILENO");
                        exit(1);
                    }
                    close(fd);
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
                    int original = dup(1);
                    if(dup2(fd, 1)<0)
                    {
                        perror("Unable to duplicate file descriptor");
                        exit(1);
                    }
                    printf("%s\n", present);
                    if(dup2(original, 1)<0)
                    {
                        perror("Couldn't change the STDOUT_FILENO");
                        exit(1);
                    }
                    close(fd);
                    return;
                }
            }
        }
        printf("%s\n", present);
    }
}