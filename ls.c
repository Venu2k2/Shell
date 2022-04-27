#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/utsname.h>
#include <pwd.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <time.h>
#include <grp.h>
#include <stdbool.h>
void ls()
{
    DIR *d;
    struct dirent *dir;
    d = opendir(".");
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            if (*dir->d_name == '.')
            {
                continue;
            }
            printf("%s\n", dir->d_name);
        }
        closedir(d);
    }
}
void lsa()
{
    DIR *d;
    struct dirent *dir;
    d = opendir(".");
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            printf("%s\n", dir->d_name);
        }
        closedir(d);
    }
}
void ls1()
{
    chdir("..");
    DIR *d;
    struct dirent *dir;
    d = opendir(".");
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            if (*dir->d_name == '.')
            {
                continue;
            }
            printf("%s\n", dir->d_name);
        }
        closedir(d);
    }
}
void lsl()
{
    char files[256][256];
    DIR *d;
    struct dirent *dir;
    d = opendir(".");
    int count = 0;
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            if (*dir->d_name == '.')
            {
                continue;
            }
            //printf("%s ", dir->d_name);
            strcpy(files[count], dir->d_name);
            count++;
        }
        closedir(d);
    }
    int total = 0;
    char months[13][4] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Aug", "Sep", "Oct", "Nov", "Dec"};
    char output[count][11];
    long long int nlink[count];
    char user[count][256];
    char group[count][256];
    long long int size[count];
    long long int max_size = -1;
    int digits = 0;
    int month[count];
    int day[count];
    int hour[count];
    int min[count];
    int year[count];
    bool what[count];
    memset(what, false, sizeof(what));
    for (int i = 0; i < count; i++)
    {
        int output1 = 0;
        struct stat st;
        int in = stat(files[i], &st);
        total += st.st_blocks;
        if (in == -1)
        {
            perror(files[i]);
        }
        else
        {
            if (S_ISDIR(st.st_mode))
            {
                output[i][output1] = 'd';
                output1++;
            }
            else
            {
                output[i][output1] = '-';
                output1++;
            }
            if (st.st_mode & S_IRUSR)
            {
                output[i][output1] = 'r';
                output1++;
            }
            else
            {
                output[i][output1] = '-';
                output1++;
            }
            if (st.st_mode & S_IWUSR)
            {
                output[i][output1] = 'w';
                output1++;
            }
            else
            {
                output[i][output1] = '-';
                output1++;
            }
            if (st.st_mode & S_IXUSR)
            {
                output[i][output1] = 'x';
                output1++;
            }
            else
            {
                output[i][output1] = '-';
                output1++;
            }
            if (st.st_mode & S_IRGRP)
            {
                output[i][output1] = 'r';
                output1++;
            }
            else
            {
                output[i][output1] = '-';
                output1++;
            }
            if (st.st_mode & S_IWGRP)
            {
                output[i][output1] = 'w';
                output1++;
            }
            else
            {
                output[i][output1] = '-';
                output1++;
            }
            if (st.st_mode & S_IXGRP)
            {
                output[i][output1] = 'x';
                output1++;
            }
            else
            {
                output[i][output1] = '-';
                output1++;
            }
            if (st.st_mode & S_IROTH)
            {
                output[i][output1] = 'r';
                output1++;
            }
            else
            {
                output[i][output1] = '-';
                output1++;
            }
            if (st.st_mode & S_IWOTH)
            {
                output[i][output1] = 'w';
                output1++;
            }
            else
            {
                output[i][output1] = '-';
                output1++;
            }
            if (st.st_mode & S_IXOTH)
            {
                output[i][output1] = 'x';
                output1++;
            }
            else
            {
                output[i][output1] = '-';
                output1++;
            }
            output[i][output1] = '\0';
            nlink[i] = st.st_nlink;
            struct passwd *pw = getpwuid(st.st_uid);
            struct group *gr = getgrgid(st.st_uid);
            strcpy(user[i], pw->pw_name);
            strcpy(group[i], gr->gr_name);
            size[i] = st.st_size;
            if (max_size < size[i])
            {
                max_size = size[i];
            }
            time_t t;
            struct tm *tmp = localtime(&st.st_mtime);
            int mins = tmp->tm_min;
            int hours = tmp->tm_hour;
            int days = tmp->tm_mday;
            int month1 = tmp->tm_mon;
            int years = tmp->tm_year + 1900;
            int p = 0;
            month[i] = month1;
            day[i] = days;
            hour[i] = hours;
            min[i] = mins;
            year[i] = years;
            time_t now;
            time(&now);
            struct tm *local = localtime(&now);
            if (year[i] != local->tm_year + 1900 || month1 < local->tm_mon - 6)
            {
                what[i] = true;
            }
        }
    }
    while (max_size != 0)
    {
        max_size = max_size / 10;
        digits++;
    }
    printf("total %d\n", total / 2);
    for (int i = 0; i < count; i++)
    {
        if (what[i] == false)
        {
            printf("%s %lld %s %s %*lld %s %.2d %.2d:%.2d %s\n", output[i], nlink[i], user[i], group[i], digits, size[i], months[month[i] - 1], day[i], hour[i], min[i], files[i]);
        }
        else
        {
            printf("%s %lld %s %s %*lld %s %.2d %.4d %s\n", output[i], nlink[i], user[i], group[i], digits, size[i], months[month[i] - 1], day[i], year[i], files[i]);
        }
    }
}
void lsal()
{
    char files[256][256];
    DIR *d;
    struct dirent *dir;
    d = opendir(".");
    int count = 0;
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            //printf("%s ", dir->d_name);
            strcpy(files[count], dir->d_name);
            count++;
        }
        closedir(d);
    }
    int total = 0;
    char months[13][4] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Aug", "Sep", "Oct", "Nov", "Dec"};
    char output[count][11];
    long long int nlink[count];
    char user[count][256];
    char group[count][256];
    long long int size[count];
    long long int max_size = -1;
    int digits = 0;
    int month[count];
    int day[count];
    int hour[count];
    int min[count];
    for (int i = 0; i < count; i++)
    {
        int output1 = 0;
        struct stat st;
        int in = stat(files[i], &st);
        total += st.st_blocks;
        if (in == -1)
        {
            perror(files[i]);
        }
        else
        {
            if (S_ISDIR(st.st_mode))
            {
                output[i][output1] = 'd';
                output1++;
            }
            else
            {
                output[i][output1] = '-';
                output1++;
            }
            if (st.st_mode & S_IRUSR)
            {
                output[i][output1] = 'r';
                output1++;
            }
            else
            {
                output[i][output1] = '-';
                output1++;
            }
            if (st.st_mode & S_IWUSR)
            {
                output[i][output1] = 'w';
                output1++;
            }
            else
            {
                output[i][output1] = '-';
                output1++;
            }
            if (st.st_mode & S_IXUSR)
            {
                output[i][output1] = 'x';
                output1++;
            }
            else
            {
                output[i][output1] = '-';
                output1++;
            }
            if (st.st_mode & S_IRGRP)
            {
                output[i][output1] = 'r';
                output1++;
            }
            else
            {
                output[i][output1] = '-';
                output1++;
            }
            if (st.st_mode & S_IWGRP)
            {
                output[i][output1] = 'w';
                output1++;
            }
            else
            {
                output[i][output1] = '-';
                output1++;
            }
            if (st.st_mode & S_IXGRP)
            {
                output[i][output1] = 'x';
                output1++;
            }
            else
            {
                output[i][output1] = '-';
                output1++;
            }
            if (st.st_mode & S_IROTH)
            {
                output[i][output1] = 'r';
                output1++;
            }
            else
            {
                output[i][output1] = '-';
                output1++;
            }
            if (st.st_mode & S_IWOTH)
            {
                output[i][output1] = 'w';
                output1++;
            }
            else
            {
                output[i][output1] = '-';
                output1++;
            }
            if (st.st_mode & S_IXOTH)
            {
                output[i][output1] = 'x';
                output1++;
            }
            else
            {
                output[i][output1] = '-';
                output1++;
            }
            output[i][output1] = '\0';
            nlink[i] = st.st_nlink;
            struct passwd *pw = getpwuid(st.st_uid);
            struct group *gr = getgrgid(st.st_uid);
            strcpy(user[i], pw->pw_name);
            strcpy(group[i], gr->gr_name);
            size[i] = st.st_size;
            if (max_size < size[i])
            {
                max_size = size[i];
            }
            time_t t;
            struct tm *tmp = localtime(&st.st_mtime);
            int mins = tmp->tm_min;
            int hours = tmp->tm_hour;
            int days = tmp->tm_mday;
            int month1 = tmp->tm_mon;
            int p = 0;
            //printf("%s %.2d %.2d:%.2d ",months[month-1],day,hour,min);
            month[i] = month1;
            day[i] = days;
            hour[i] = hours;
            min[i] = mins;
            //printf("%s\n",files[i]);
        }
    }
    while (max_size != 0)
    {
        max_size = max_size / 10;
        digits++;
    }
    printf("total %d\n", total / 2);
    for (int i = 0; i < count; i++)
    {
        printf("%s %lld %s %s %*lld %s %.2d %.2d:%.2d %s\n", output[i], nlink[i], user[i], group[i], digits, size[i], months[month[i] - 1], day[i], hour[i], min[i], files[i]);
    }
}
void lsactual(int i, int directories,int flag1,int flag2,int flag,char Directories[256][256])
{
    if (commands[i][0] == 'l' && commands[i][1] == 's')
    {
        if (commands[i][3] == '.')
        {
            if (commands[i][4] == '.')
            {
                char current[256];
                if (getcwd(current, sizeof(current)) == NULL)
                {
                    printf("Unable to open directory\n");
                    perror("getcwd() error: ");
                    return;
                }
                int original;
                if (IO_flag == 1)
                {
                    original = dup(1);
                    int j = 0;
                    while (commands[i][j] != '>')
                    {
                        j++;
                    }
                    int breakage = j;
                    commands[i][j] = '\0';
                    commands[i][j - 1] = '\0';
                    j += 2;
                    if (greater_than == 2)
                    {
                        j += 1;
                        commands[i][j] = '\0';
                        j++;
                    }
                    char output_file[256];
                    memset(output_file, '\0', sizeof(output_file));
                    int count = 0;
                    while (commands[i][j] != '\0')
                    {
                        output_file[count++] = commands[i][j];
                        commands[i][j] = '\0';
                        j++;
                    }
                    original = dup(1);
                    int fd;
                    if (greater_than == 1)
                    {
                        fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                    }
                    if (greater_than == 2)
                    {
                        fd = open(output_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
                    }
                    dup2(fd, 1);
                }
                ls1();
                chdir(current);
                if (IO_flag == 1)
                {
                    dup2(original, 1);
                }
                return;
            }
            int original;
            if (IO_flag == 1)
            {
                original = dup(1);
                int j = 0;
                while (commands[i][j] != '>')
                {
                    j++;
                }
                int breakage = j;
                commands[i][j] = '\0';
                commands[i][j - 1] = '\0';
                j += 2;
                char output_file[256];
                memset(output_file, '\0', sizeof(output_file));
                int count = 0;
                while (commands[i][j] != '\0')
                {
                    output_file[count++] = commands[i][j];
                    commands[i][j] = '\0';
                    j++;
                }
                original = dup(1);
                int fd;
                if (greater_than == 1)
                {
                    fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                }
                if (greater_than == 2)
                {
                    fd = open(output_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
                }
                dup2(fd, 1);
            }
            ls();
            if (IO_flag == 1)
            {
                dup2(original, 1);
            }
            return;
        }
        if (commands[i][3] == '~' && (commands[i][4] == '\0' || IO_flag == 1))
        {
            char current[256];
            if (getcwd(current, sizeof(current)) == NULL)
            {
                printf("Unable to open directory\n");
                perror("getcwd() error: ");
                return;
            }
            chdir(real_cwd);
            int original;
            if (IO_flag == 1)
            {
                original = dup(1);
                char file_name[256];
                memset(file_name, '\0', sizeof(file_name));
                int j = 0;
                while (commands[i][j] != '>')
                {
                    j++;
                }
                commands[i][j] = '\0';
                commands[i][j + 1] = '\0';
                j += 2;
                if (greater_than == 2)
                {
                    commands[i][j] = '\0';
                    j++;
                }
                int count = 0;
                while (commands[i][j] != '\0')
                {
                    file_name[count++] = commands[i][j];
                    j++;
                }
                if (greater_than == 1)
                {
                    int fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                    dup2(fd, 1);
                }
                if (greater_than == 2)
                {
                    int fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
                    dup2(fd, 1);
                }
            }
            ls();
            chdir(current);
            dup2(original, 1);
            return;
        }
        if (commands[i][3] == '-' && commands[i][4] == 'a' && (directories == 0 || (directories == 2 && IO_flag == 1)))
        {
            if (commands[i][5] == 'l')
            {
                int original;
                if (IO_flag == 1)
                {
                    original = dup(1);
                    char file_name[256];
                    memset(file_name, '\0', sizeof(file_name));
                    int j = 0;
                    while (commands[i][j] != '>')
                    {
                        j++;
                    }
                    commands[i][j] = '\0';
                    commands[i][j + 1] = '\0';
                    j += 2;
                    if (greater_than == 2)
                    {
                        commands[i][j] = '\0';
                        j++;
                    }
                    int count = 0;
                    while (commands[i][j] != '\0')
                    {
                        file_name[count++] = commands[i][j];
                        j++;
                    }
                    if (greater_than == 1)
                    {
                        int fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                        dup2(fd, 1);
                    }
                    if (greater_than == 2)
                    {
                        int fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
                        dup2(fd, 1);
                    }
                }
                lsal();
                dup2(original, 1);
                return;
            }
            if (commands[i][6] == '-' && commands[i][7] == 'l')
            {
                int original;
                if (IO_flag == 1)
                {
                    original = dup(1);
                    char file_name[256];
                    memset(file_name, '\0', sizeof(file_name));
                    int j = 0;
                    while (commands[i][j] != '>')
                    {
                        j++;
                    }
                    commands[i][j] = '\0';
                    commands[i][j + 1] = '\0';
                    j += 2;
                    if (greater_than == 2)
                    {
                        commands[i][j] = '\0';
                        j++;
                    }
                    int count = 0;
                    while (commands[i][j] != '\0')
                    {
                        file_name[count++] = commands[i][j];
                        j++;
                    }
                    if (greater_than == 1)
                    {
                        int fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                        dup2(fd, 1);
                    }
                    if (greater_than == 2)
                    {
                        int fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
                        dup2(fd, 1);
                    }
                }
                lsal();
                dup2(original, 1);
                return;
            }
            int original;
            if (IO_flag == 1)
            {
                original = dup(1);
                char file_name[256];
                memset(file_name, '\0', sizeof(file_name));
                int j = 0;
                while (commands[i][j] != '>')
                {
                    j++;
                }
                commands[i][j] = '\0';
                commands[i][j + 1] = '\0';
                j += 2;
                if (greater_than == 2)
                {
                    commands[i][j] = '\0';
                    j++;
                }
                int count = 0;
                while (commands[i][j] != '\0')
                {
                    file_name[count++] = commands[i][j];
                    j++;
                }
                if (greater_than == 1)
                {
                    int fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                    dup2(fd, 1);
                }
                if (greater_than == 2)
                {
                    int fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
                    dup2(fd, 1);
                }
            }
            lsa();
            dup2(original, 1);
            return;
        }
        if (commands[i][3] == '-' && commands[i][4] == 'l' && (directories == 0 || (directories == 2 && IO_flag == 1)))
        {
            int flagx = 0;
            for (int j = 5; j < sizeof(commands[i]); j++)
            {
                if (commands[i][j] == '-' && commands[i][j + 1] == 'a')
                {
                    flagx = 1;
                    break;
                }
            }
            if (commands[i][5] == 'a' || flagx == 1)
            {
                int original;
                if (IO_flag == 1)
                {
                    original = dup(1);
                    char file_name[256];
                    memset(file_name, '\0', sizeof(file_name));
                    int j = 0;
                    while (commands[i][j] != '>')
                    {
                        j++;
                    }
                    commands[i][j] = '\0';
                    commands[i][j + 1] = '\0';
                    j += 2;
                    if (greater_than == 2)
                    {
                        commands[i][j] = '\0';
                        j++;
                    }
                    int count = 0;
                    while (commands[i][j] != '\0')
                    {
                        file_name[count++] = commands[i][j];
                        j++;
                    }
                    if (greater_than == 1)
                    {
                        int fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                        dup2(fd, 1);
                    }
                    if (greater_than == 2)
                    {
                        int fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
                        dup2(fd, 1);
                    }
                }
                lsal();
                dup2(original, 1);
                return;
            }
            int original;
            if (IO_flag == 1)
            {
                original = dup(1);
                char file_name[256];
                memset(file_name, '\0', sizeof(file_name));
                int j = 0;
                while (commands[i][j] != '>')
                {
                    j++;
                }
                commands[i][j] = '\0';
                commands[i][j + 1] = '\0';
                j += 2;
                if (greater_than == 2)
                {
                    commands[i][j] = '\0';
                    j++;
                }
                int count = 0;
                while (commands[i][j] != '\0')
                {
                    file_name[count++] = commands[i][j];
                    j++;
                }
                if (greater_than == 1)
                {
                    int fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                    dup2(fd, 1);
                }
                if (greater_than == 2)
                {
                    int fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
                    dup2(fd, 1);
                }
            }
            lsl();
            return;
        }
        if ((directories == 0 && flag == 0) || (directories == 2 && flag == 0 && IO_flag == 1))
        {
            int original;
            if (IO_flag == 1)
            {
                original = dup(1);
                char file_name[256];
                memset(file_name, '\0', sizeof(file_name));
                int j = 0;
                while (commands[i][j] != '>')
                {
                    j++;
                }
                commands[i][j] = '\0';
                commands[i][j + 1] = '\0';
                j += 2;
                if (greater_than == 2)
                {
                    commands[i][j] = '\0';
                    j++;
                }
                int count = 0;
                while (commands[i][j] != '\0')
                {
                    file_name[count++] = commands[i][j];
                    j++;
                }
                if (greater_than == 1)
                {
                    int fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                    dup2(fd, 1);
                }
                if (greater_than == 2)
                {
                    int fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
                    dup2(fd, 1);
                }
            }
            ls();
            dup2(original, 1);
            return;
        }
        char presentdir[256];
        if (getcwd(presentdir, sizeof(presentdir)) == NULL)
        {
            printf("Unable to get the command!\n");
            perror("getcwd() error");
            return;
        }
        if (IO_flag == 1)
        {
            directories -= 2;
        }
        int original;
        char file_name[256];
        memset(file_name, '\0', sizeof(file_name));
        int fd, orignal = 1;
        if (IO_flag == 1)
        {
            int j = 0;
            while (commands[i][j] != '>')
            {
                j++;
            }
            commands[i][j] = '\0';
            commands[i][j + 1] = '\0';
            j += 2;
            if (greater_than == 2)
            {
                commands[i][j] = '\0';
                j++;
            }
            int count = 0;
            while (commands[i][j] != '\0')
            {
                file_name[count++] = commands[i][j];
                j++;
            }
            if (greater_than == 1)
            {
                fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                dup2(fd, 1);
            }
            if (greater_than == 2)
            {
                fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
                dup2(fd, 1);
            }
        }
        for (int p = 0; p < directories; p++)
        {
            if (Directories[p][0] == '~')
            {
                strcpy(Directories[p], real_cwd);
            }
            int x = chdir(Directories[p]);
            if (x == -1)
            {
                perror(Directories[p]);
                return;
            }
            if (flag == 0)
            {
                ls();
            }
            else
            {
                if (flag1 >= 1 && flag2 >= 1)
                {
                    printf("%s:\n", Directories[p]);
                    lsal();
                    return;
                }
                if (flag1 >= 1 && flag2 == 0)
                {
                    printf("%s:\n", Directories[p]);
                    lsa();
                    return;
                }
                if (flag1 == 0 && flag2 >= 1)
                {
                    printf("%s:\n", Directories[p]);
                    lsl();
                    return;
                }
            }
        }
        chdir(presentdir);
        close(fd);
        if (IO_flag == 1)
        {
            dup2(original, 1);
        }
        return;
    }
}
