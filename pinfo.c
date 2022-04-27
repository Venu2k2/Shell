#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/utsname.h>
#include <fcntl.h>
void pinfo(int index)
{
    char address[256];
    memset(address, '\0', sizeof(address));
    int x = getpid();
    sprintf(address, "/proc/%d/stat", x);
    FILE *fp = fopen(address, "r");
    char info[1000];
    memset(info, '\0', sizeof(info));
    fgets(info, sizeof(info), fp);
    fclose(fp);
    int count = 0;
    char pid[10];
    char status[3];
    char memory[100];
    char path[100];
    memset(pid, '\0', sizeof(pid));
    memset(status, '\0', sizeof(status));
    memset(memory, '\0', sizeof(memory));
    memset(path, '\0', sizeof(path));
    for (int i = 0; i < sizeof(info); i++)
    {
        if (info[i] == ' ')
        {
            count++;
            continue;
        }
        if (count == 0)
        {
            int indexing = 0;
            while (info[i] != ' ')
            {
                pid[indexing++] = info[i];
                i++;
            }
            i--;
            continue;
        }
        if (count == 2)
        {
            int indexing = 0;
            while (info[i] != ' ')
            {
                status[indexing++] = info[i];
                i++;
            }
            i--;
            continue;
        }
        if (count == 22)
        {
            int indexing = 0;
            while (info[i] != ' ')
            {
                memory[indexing++] = info[i];
                i++;
            }
            i--;
            break;
        }
    }
    memset(address, '\0', sizeof(address));
    sprintf(address, "/proc/%d/exe", x);
    readlink(address, path, sizeof(path));
    int size1 = strlen(real_cwd);
    int size2 = strlen(path);
    int flag = 0;
    char printString[256];
    if (size2 >= size1)
    {
        for (int i = 0; i < size1; i++)
        {
            if (real_cwd[i] == path[i])
            {
                continue;
            }
            else
            {
                flag = 1;
                break;
            }
        }
        if (!flag)
        {
            int count = 0;
            for (int i = size1; i < size2; i++)
            {
                printString[count++] = path[i];
            }
            printString[count++] = '\0';
        }
    }
    if (status[0] == 'R' || status[0] == 'S')
    {
        status[1] = '+';
    }
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
                printf("pid -- %s\n", pid);
                printf("Process Status -- {%s}\n", status);
                printf("memory -- %s{Virtual Memory}\n", memory);
                if (!flag)
                {
                    printf("Executable Path -- ~%s\n", printString);
                }
                else
                {
                    printf("Executable Path -- %s\n", path);
                }
                if (dup2(original, 1) < 0)
                {
                    perror("Couldn't change the STDOUT_FILENO");
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
                int original = dup(1);
                int fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
                dup2(fd, 1);
                printf("pid -- %s\n", pid);
                printf("Process Status -- {%s}\n", status);
                printf("memory -- %s{Virtual Memory}\n", memory);
                if (!flag)
                {
                    printf("Executable Path -- ~%s\n", printString);
                }
                else
                {
                    printf("Executable Path -- %s\n", path);
                }
                dup2(original, 1);
                close(fd);
                return;
            }
        }
    }
    printf("pid -- %s\n", pid);
    printf("Process Status -- {%s}\n", status);
    printf("memory -- %s{Virtual Memory}\n", memory);
    if (!flag)
    {
        printf("Executable Path -- ~%s\n", printString);
    }
    else
    {
        printf("Executable Path -- %s\n", path);
    }
}
void pinfo1(int index)
{
    char address[256] = {"/proc/"};
    if (IO_flag == 1)
    {
        int count = 6, j = 6;
        while (commands[index][j] != ' ')
        {
            address[count++] = commands[index][j];
            j++;
        }
        address[count++] = '/';
        int x = count;
        address[count++] = 's';
        address[count++] = 't';
        address[count++] = 'a';
        address[count++] = 't';
        address[count++] = '\0';
        FILE *fp = fopen(address, "r");
        if (fp == NULL)
        {
            perror("Given process doesn't exit");
            exit(1);
        }
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
                int count1 = 0;
                while (k != strlen(commands[index]))
                {
                    file_name[count1++] = commands[index][k++];
                }
                int fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                int original = dup(1);
                if (dup2(fd, 1) < 0)
                {
                    perror("Unable to duplicate file descriptor");
                    exit(1);
                }
                char info[1000];
                memset(info, '\0', sizeof(info));
                fgets(info, sizeof(info), fp);
                fclose(fp);
                int count = 0;
                char pid[10];
                char status[3];
                char memory[100];
                char path[100];
                memset(pid, '\0', sizeof(pid));
                memset(status, '\0', sizeof(status));
                memset(memory, '\0', sizeof(memory));
                memset(path, '\0', sizeof(path));
                for (int i = 0; i < sizeof(info); i++)
                {
                    if (info[i] == ' ')
                    {
                        count++;
                        continue;
                    }
                    if (count == 0)
                    {
                        int indexing = 0;
                        while (info[i] != ' ')
                        {
                            pid[indexing++] = info[i];
                            i++;
                        }
                        i--;
                        continue;
                    }
                    if (count == 2)
                    {
                        int indexing = 0;
                        while (info[i] != ' ')
                        {
                            status[indexing++] = info[i];
                            i++;
                        }
                        i--;
                        continue;
                    }
                    if (count == 22)
                    {
                        int indexing = 0;
                        while (info[i] != ' ')
                        {
                            memory[indexing++] = info[i];
                            i++;
                        }
                        i--;
                        break;
                    }
                }
                address[x + 1] = '/';
                address[x + 2] = 'e';
                address[x + 3] = 'x';
                address[x + 4] = 'e';
                address[x + 5] = '\0';
                readlink(address, path, sizeof(path));
                int size1 = strlen(real_cwd);
                int size2 = strlen(path);
                int flag = 0;
                char printString[256];
                if (size2 >= size1)
                {
                    for (int i = 0; i < size1; i++)
                    {
                        if (real_cwd[i] == path[i])
                        {
                            continue;
                        }
                        else
                        {
                            flag = 1;
                            break;
                        }
                    }
                    if (!flag)
                    {
                        int count = 0;
                        for (int i = size1; i < size2; i++)
                        {
                            printString[count++] = path[i];
                        }
                        printString[count++] = '\0';
                    }
                }
                else
                {
                    flag = 1;
                }
                printf("pid -- %s\n", pid);
                printf("Process Status -- {%s}\n", status);
                printf("memory -- %s{Virtual Memory}\n", memory);
                if (flag == 0)
                {
                    printf("Executable Path -- ~%s\n", printString);
                }
                else
                {
                    printf("Executable Path -- %s\n", path);
                }
                if (dup2(original, 1) < 0)
                {
                    perror("Couldn't change the STDOUT_FILENO");
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
                int count1 = 0;
                while (k != strlen(commands[index]))
                {
                    file_name[count1++] = commands[index][k++];
                }
                int fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
                int original = dup(1);
                dup2(fd, 1);
                char info[1000];
                memset(info, '\0', sizeof(info));
                fgets(info, sizeof(info), fp);
                fclose(fp);
                int count = 0;
                char pid[10];
                char status[3];
                char memory[100];
                char path[100];
                memset(pid, '\0', sizeof(pid));
                memset(status, '\0', sizeof(status));
                memset(memory, '\0', sizeof(memory));
                memset(path, '\0', sizeof(path));
                for (int i = 0; i < sizeof(info); i++)
                {
                    if (info[i] == ' ')
                    {
                        count++;
                        continue;
                    }
                    if (count == 0)
                    {
                        int indexing = 0;
                        while (info[i] != ' ')
                        {
                            pid[indexing++] = info[i];
                            i++;
                        }
                        i--;
                        continue;
                    }
                    if (count == 2)
                    {
                        int indexing = 0;
                        while (info[i] != ' ')
                        {
                            status[indexing++] = info[i];
                            i++;
                        }
                        i--;
                        continue;
                    }
                    if (count == 22)
                    {
                        int indexing = 0;
                        while (info[i] != ' ')
                        {
                            memory[indexing++] = info[i];
                            i++;
                        }
                        i--;
                        break;
                    }
                }
                address[x + 1] = '/';
                address[x + 2] = 'e';
                address[x + 3] = 'x';
                address[x + 4] = 'e';
                address[x + 5] = '\0';
                readlink(address, path, sizeof(path));
                int size1 = strlen(real_cwd);
                int size2 = strlen(path);
                int flag = 0;
                char printString[256];
                if (size2 >= size1)
                {
                    for (int i = 0; i < size1; i++)
                    {
                        if (real_cwd[i] == path[i])
                        {
                            continue;
                        }
                        else
                        {
                            flag = 1;
                            break;
                        }
                    }
                    if (!flag)
                    {
                        int count = 0;
                        for (int i = size1; i < size2; i++)
                        {
                            printString[count++] = path[i];
                        }
                        printString[count++] = '\0';
                    }
                }
                else
                {
                    flag = 1;
                }
                printf("pid -- %s\n", pid);
                printf("Process Status -- {%s}\n", status);
                printf("memory -- %s{Virtual Memory}\n", memory);
                if (flag == 0)
                {
                    printf("Executable Path -- ~%s\n", printString);
                }
                else
                {
                    printf("Executable Path -- %s\n", path);
                }
                dup2(original, 1);
                close(fd);
                return;
            }
        }
    }
    for (int j = 6; j < strlen(commands[index]); j++)
    {
        address[j] = commands[index][j];
    }
    int x = strlen(commands[index]) - 1;
    address[x + 1] = '/';
    address[x + 2] = 's';
    address[x + 3] = 't';
    address[x + 4] = 'a';
    address[x + 5] = 't';
    address[x + 6] = '\0';
    FILE *fp = fopen(address, "r");
    char number[256];
    memset(number, '\0', sizeof(number));
    for (int j = 6;; j++)
    {
        if (commands[index][j] == ' ' || commands[index][j] == '\0')
        {
            number[j - 6] = '\0';
            break;
        }
        else
        {
            number[j - 6] = commands[index][j];
        }
    }
    if (fp == NULL)
    {
        printf("Process with PID = %s, doesn't exist\n", number);
        return;
    }
    char info[1000];
    memset(info, '\0', sizeof(info));
    fgets(info, sizeof(info), fp);
    fclose(fp);
    int count = 0;
    char pid[10];
    char status[3];
    char memory[100];
    char path[100];
    memset(pid, '\0', sizeof(pid));
    memset(status, '\0', sizeof(status));
    memset(memory, '\0', sizeof(memory));
    memset(path, '\0', sizeof(path));
    for (int i = 0; i < sizeof(info); i++)
    {
        if (info[i] == ' ')
        {
            count++;
            continue;
        }
        if (count == 0)
        {
            int indexing = 0;
            while (info[i] != ' ')
            {
                pid[indexing++] = info[i];
                i++;
            }
            i--;
            continue;
        }
        if (count == 2)
        {
            int indexing = 0;
            while (info[i] != ' ')
            {
                status[indexing++] = info[i];
                i++;
            }
            i--;
            continue;
        }
        if (count == 22)
        {
            int indexing = 0;
            while (info[i] != ' ')
            {
                memory[indexing++] = info[i];
                i++;
            }
            i--;
            break;
        }
    }
    address[x + 1] = '/';
    address[x + 2] = 'e';
    address[x + 3] = 'x';
    address[x + 4] = 'e';
    address[x + 5] = '\0';
    readlink(address, path, sizeof(path));
    int size1 = strlen(real_cwd);
    int size2 = strlen(path);
    int flag = 0;
    char printString[256];
    if (size2 >= size1)
    {
        for (int i = 0; i < size1; i++)
        {
            if (real_cwd[i] == path[i])
            {
                continue;
            }
            else
            {
                flag = 1;
                break;
            }
        }
        if (!flag)
        {
            int count = 0;
            for (int i = size1; i < size2; i++)
            {
                printString[count++] = path[i];
            }
            printString[count++] = '\0';
        }
    }
    else
    {
        flag = 1;
    }
    printf("pid -- %s\n", pid);
    printf("Process Status -- {%s}\n", status);
    printf("memory -- %s{Virtual Memory}\n", memory);
    if (flag == 0)
    {
        printf("Executable Path -- ~%s\n", printString);
    }
    else
    {
        printf("Executable Path -- %s\n", path);
    }
}
