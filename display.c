#include <stdio.h>
#include <stdlib.h>
#include <sys/utsname.h>
#include <pwd.h>
#include <unistd.h>
#include <string.h>
struct utsname systemName;
void display()
{
    //dup2(original_fd,STDOUT_FILENO);
    char cwd[256];
    if (getcwd(cwd, sizeof(cwd)) == NULL)
    {
        printf("Unable to get the command!\n");
        perror("getcwd() error");
    } 
    char *user;
    //printf("<%s@",getenv("USER"));
    user = getenv("USER");
    uname(&systemName);
    int size1 = strlen(real_cwd);
    int size2 = strlen(cwd);
    if(size2 < size1)
    {
        printf("<%s@%s:%s>",user,systemName.nodename,cwd);   
    }
    else
    {
        int flag =0;
        for(int i=0;i<size1;i++)
        {
            if(real_cwd[i] == cwd[i])
            {
                continue;
            }
            else
            {
                flag = 1;
                break;
            }
        }
        if(!flag)
        {
            char printString[256];
            int count = 0;
            for(int i = size1;i<size2;i++)
            {
                printString[count++] = cwd[i];
            }
            printString[count++] = '\0';
            printf("<%s@%s:~%s>",user,systemName.nodename,printString);
        }
        else
        {
            printf("<%s@%s:%s>",user,systemName.nodename,cwd);
        }
    }
}