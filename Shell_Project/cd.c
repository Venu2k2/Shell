#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/utsname.h>
#include <pwd.h>
#include <unistd.h>
#include <string.h>

void cdactual(int i,char Directories[256][256])
{
    if (commands[i][3] == '.' && commands[i][4] == '.')
    {
        chdir("..");
        cd_index = cd_index ^ 1;
        char current[256];
        memset(current, '\0', sizeof(current));
        getcwd(current, sizeof(current));
        strcpy(cdhistory[cd_index], current);
        return;
    }
    if (commands[i][3] == '-')
    {
        if (cdhistory[1][0] == '\0')
        {
            printf("-bash: cd: OLDPWD not set\n");
            return;
        }
        char current[256];
        if (getcwd(current, sizeof(current)) == NULL)
        {
            printf("Unable to get the command!\n");
            perror("getcwd() error");
            return;
        }
        else
        {
            cd_index = cd_index ^ 1;
            printf("%s\n", cdhistory[cd_index]);
            chdir(cdhistory[cd_index]);
            return;
        }
    }
    if (commands[i][3] == '~' || commands[i][3] == '\0')
    {

        chdir(real_cwd);
        cd_index = cd_index ^ 1;
        strcpy(cdhistory[cd_index], real_cwd);
        return;
    }
    if (chdir(Directories[0]) == -1)
    {
        perror(Directories[0]);
        return;
    }
    else
    {
        cd_index = cd_index ^ 1;
        strcpy(cdhistory[cd_index], Directories[0]);
    }
    return;
}
