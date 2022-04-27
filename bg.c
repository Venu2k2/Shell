#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/utsname.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>
void bg(int index)
{
    int original_O;
    int original_I;
    if (IO_flag == 1)
    {
        if (greater_than == 1 && less_than == 0)
        {
            int j = 0;
            char execute[256];
            memset(execute, '\0', sizeof(execute));
            while (commands[index][j] != '>')
            {
                execute[j] = commands[index][j];
                j++;
            }
            j--;
            execute[j] = '\0';
            char output[256];
            memset(output, '\0', sizeof(output));
            commands[index][j] = '\0';
            commands[index][j + 1] = '\0';
            j += 2;
            int count = 0;
            while (commands[index][j] != '\0')
            {
                output[count++] = commands[index][j];
                commands[index][j] = '\0';
                j++;
            }
            int fd = open(output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            original_O = dup(1);
            if (dup2(fd, 1) < 0)
            {
                perror("Unable to duplicate file descriptor");
                exit(1);
            }
        }
        else
        {
            if (greater_than == 2 && less_than == 0)
            {
                int j = 0;
                char execute[256];
                memset(execute, '\0', sizeof(execute));
                while (commands[index][j] != '>')
                {
                    execute[j] = commands[index][j];
                    j++;
                }
                j--;
                execute[j] = '\0';
                char output[256];
                memset(output, '\0', sizeof(output));
                commands[index][j] = '\0';
                commands[index][j + 1] = '\0';
                commands[index][j + 2] = '\0';
                j += 3;
                int count = 0;
                while (commands[index][j] != '\0')
                {
                    output[count++] = commands[index][j];
                    commands[index][j] = '\0';
                    j++;
                }
                int fd = open(output, O_WRONLY | O_CREAT | O_APPEND, 0644);
                original_O = dup(1);
                if (dup2(fd, 1) < 0)
                {
                    perror("Unable to duplicate file descriptor");
                    exit(1);
                }
            }
            if (greater_than == 0 && less_than == 1)
            {
                int j = 0;
                char input_file[256];
                memset(input_file, '\0', sizeof(input_file));
                while (commands[index][j] != '<')
                {
                    j++;
                }
                commands[index][j - 1] = '\0';
                commands[index][j] = '\0';
                j += 2;
                int count = 0;
                while (commands[index][j] != '\0')
                {
                    input_file[count++] = commands[index][j];
                    j++;
                }
                original_I = dup(0);
                int fd = open(input_file, O_RDONLY);
                if (fd == -1)
                {
                    perror("Given input file doesn't exist");
                    return;
                }
                if (dup2(fd, 0) < 0)
                {
                    perror("Unable to duplicate file descriptor");
                    return;
                }
            }
            else
            {
                if (greater_than == 1 && less_than == 1)
                {
                    int j = 0;
                    char input_file[256];
                    memset(input_file, '\0', sizeof(input_file));
                    while (commands[index][j] != '<')
                    {
                        j++;
                    }
                    j += 2;
                    int count = 0;
                    while (commands[index][j] != '>')
                    {
                        input_file[count++] = commands[index][j];
                        j++;
                    }
                    input_file[count - 1] = '\0';
                    original_I = dup(0);
                    int fd = open(input_file, O_RDONLY);
                    if (fd == -1)
                    {
                        perror("Given input file doesn't exist");
                        return;
                    }
                    if (dup2(fd, 0) < 0)
                    {
                        perror("Unable to duplicate file descriptor");
                        return;
                    }
                    j = 0;
                    char execute[256];
                    memset(execute, '\0', sizeof(execute));
                    while (commands[index][j] != '>')
                    {
                        execute[j] = commands[index][j];
                        j++;
                    }
                    j--;
                    execute[j] = '\0';
                    char output[256];
                    memset(output, '\0', sizeof(output));
                    j += 2;
                    count = 0;
                    while (commands[index][j] != '\0')
                    {
                        output[count++] = commands[index][j];
                        commands[index][j] = '\0';
                        j++;
                    }
                    int fd1 = open(output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                    original_O = dup(1);
                    if (dup2(fd1, 1) < 0)
                    {
                        perror("Unable to duplicate file descriptor");
                        exit(1);
                    }
                    j = 0;
                    while (commands[index][j] != '<')
                    {
                        j++;
                    }
                    commands[index][j - 1] = '\0';
                    while (commands[index][j] != '\0')
                    {
                        commands[index][j] = '\0';
                        j++;
                    }
                }
                if (greater_than == 2 && less_than == 1)
                {
                    int j = 0;
                    char input_file[256];
                    memset(input_file, '\0', sizeof(input_file));
                    while (commands[index][j] != '<')
                    {
                        j++;
                    }
                    j += 2;
                    int count = 0;
                    while (commands[index][j] != '>')
                    {
                        input_file[count++] = commands[index][j];
                        j++;
                    }
                    input_file[count - 1] = '\0';
                    original_I = dup(0);
                    int fd = open(input_file, O_RDONLY);
                    if (fd == -1)
                    {
                        perror("Given input file doesn't exist");
                        return;
                    }
                    if (dup2(fd, 0) < 0)
                    {
                        perror("Unable to duplicate file descriptor");
                        return;
                    }
                    j = 0;
                    char execute[256];
                    memset(execute, '\0', sizeof(execute));
                    while (commands[index][j] != '>')
                    {
                        execute[j] = commands[index][j];
                        j++;
                    }
                    j--;
                    execute[j] = '\0';
                    char output[256];
                    memset(output, '\0', sizeof(output));
                    j += 3;
                    count = 0;
                    while (commands[index][j] != '\0')
                    {
                        output[count++] = commands[index][j];
                        commands[index][j] = '\0';
                        j++;
                    }
                    int fd1 = open(output, O_WRONLY | O_CREAT | O_APPEND, 0644);
                    original_O = dup(1);
                    if (dup2(fd1, 1) < 0)
                    {
                        perror("Unable to duplicate file descriptor");
                        exit(1);
                    }
                    j = 0;
                    while (commands[index][j] != '<')
                    {
                        j++;
                    }
                    commands[index][j - 1] = '\0';
                    while (commands[index][j] != '\0')
                    {
                        commands[index][j] = '\0';
                        j++;
                    }
                }
            }
        }
    }
    int count = 1;
    for (int i = 0; i < strlen(commands[index]); i++)
    {
        if (commands[index][i] == ' ' || commands[index][i] == '\0')
        {
            count++;
        }
    }
    int flag = 0;
    if (commands[index][strlen(commands[index]) - 1] == '&')
    {
        flag = 1;
    }
    int indexes1 = 0;
    char args[count][256];
    memset(args, '\0', sizeof(args));
    int count1 = 0;
    for (int i = 0; i < strlen(commands[index]); i++)
    {
        if (commands[index][i] == ' ')
        {
            args[indexes1][count1] = '\0';
            indexes1++;
            count1 = 0;
        }
        else
        {
            args[indexes1][count1] = commands[index][i];
            count1++;
        }
    }
    if (flag == 0)
    {
        char *arg[count + 1];
        for (int i = 0; i < count; i++)
        {
            arg[i] = args[i];
        }
        arg[count] = NULL;
        int x = fork();
        if (PIDS_VALUES >= 256)
        {
            PIDS_VALUES = 0;
            while (VALUE[PIDS_VALUES] == true)
            {
                PIDS_VALUES++;
                continue;
            }
        }
        PIDS[PIDS_VALUES] = x;
        VALUE[PIDS_VALUES] = true;
        JOB_ORDER[PIDS_VALUES] = VARIABLE + 1;
        VARIABLE++;
        for (int i = 0; i < strlen(commands[index]) - 2; i++)
        {
            NAMES[PIDS_VALUES][i] = commands[index][i];
        }
        NAMES[PIDS_VALUES][strlen(commands[index]) - 2] = '\0';
        if (x == -1)
        {
            perror("Child couldn't be created");
        }
        if (x == 0)
        {
            int y = execvp(arg[0], arg);
            if (y != 0)
            {
                perror("Cannot run foreground process");
            }
        }
        else
        {
            printf("%d\n", x);
            cid = x;
            int status;
            waitpid(cid, &status, WUNTRACED);
            if (WIFSTOPPED(status) == 1)
            {
              return;
            }
        }
    }
    else
    {
        char *arg[count];
        for (int i = 0; i < count - 1; i++)
        {
            arg[i] = args[i];
        }
        arg[count - 1] = NULL;
        int x = fork();
        if (PIDS_VALUES >= 256)
        {
            PIDS_VALUES = 0;
            while (VALUE[PIDS_VALUES] == true)
            {
                PIDS_VALUES++;
                continue;
            }
        }
        PIDS[PIDS_VALUES] = x;
        VALUE[PIDS_VALUES] = true;
        JOB_ORDER[PIDS_VALUES] = VARIABLE + 1;
        VARIABLE++;
        for (int i = 0; i < strlen(commands[index]) - 2; i++)
        {
            NAMES[PIDS_VALUES][i] = commands[index][i];
        }
        NAMES[PIDS_VALUES][strlen(commands[index]) - 2] = '\0';
        if (x == 0)
        {
            int y = execvp(arg[0], arg);
            if (y != 0)
            {
                perror("Cannot run background process");
            }
        }
        else
        {
            printf("%d\n", x);
        }
    }
    if (IO_flag == 1)
    {
        if (greater_than == 1 && less_than == 0)
        {
            dup2(original_O, 1);
        }
        if (greater_than == 2 && less_than == 0)
        {
            dup2(original_O, 1);
        }
        if (greater_than == 0 && less_than == 1)
        {
            dup2(original_I, 0);
        }
        if (greater_than == 1 && less_than == 1)
        {
            dup2(original_I, 0);
            dup2(original_O, 1);
        }
        if (greater_than == 2 && less_than == 1)
        {
            dup2(original_I, 0);
            dup2(original_O, 1);
        }
    }
}
