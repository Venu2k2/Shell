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
void swap1(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}
void swap2(char *a, char *b)
{
    char t = *a;
    *a = *b;
    *b = t;
}
void swap3(bool *a, bool *b)
{
    bool t = *a;
    *a = *b;
    *b = t;
}
void jobs_sorting()
{
    int n = 256;
    int k = 1;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (JOB_ORDER[j] > JOB_ORDER[j + 1])
            {
                swap1(&JOB_ORDER[j], &JOB_ORDER[j + 1]);
                swap1(&PIDS[j], &PIDS[j + 1]);
                swap3(&VALUE[j],&VALUE[j+1]);
                char TRAIL_ARRAY[256];
                strcpy(TRAIL_ARRAY, NAMES[j]);
                strcpy(NAMES[j], NAMES[j + 1]);
                strcpy(NAMES[j + 1], TRAIL_ARRAY);
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        if (VALUE[i] == true)
        {
            JOB_ORDER[i] = k;
            k++;
        }
    }

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (strcmp(NAMES[j], NAMES[j + 1]) > 0)
            {
                swap1(&JOB_ORDER[j], &JOB_ORDER[j + 1]);
                swap1(&PIDS[j], &PIDS[j + 1]);
                swap3(&VALUE[j],&VALUE[j+1]);
                char TRAIL_ARRAY[256];
                strcpy(TRAIL_ARRAY, NAMES[j]);
                strcpy(NAMES[j], NAMES[j + 1]);
                strcpy(NAMES[j + 1], TRAIL_ARRAY);
            }
        }
    }
}
void job_printing(int flag)
{
    jobs_sorting();
    for (int i = 0; i < 256; i++)
    {
        if (VALUE[i] == true)
        {
            char address[256];
            sprintf(address, "/proc/%d/stat", PIDS[i]);
            FILE *fp = fopen(address, "r");
            char info[1000];
            memset(info, '\0', sizeof(info));
            fgets(info, sizeof(info), fp);
            fclose(fp);
            char status[2];
            int count = 0;
            for (int i = 0; i < sizeof(info); i++)
            {
                if (info[i] == ' ')
                {
                    count++;
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
                    break;
                }
            }
            char statusing[256];
            memset(statusing,'\0',sizeof(statusing));;
            if(status[0] == 'T')
            {
                strcpy(statusing,"Stopped");
            }
            else
            {
                strcpy(statusing,"Running");
            }
            if(flag == 0)
            {
                printf("[%d] %s %s [%d]\n",JOB_ORDER[i],statusing,NAMES[i],PIDS[i]);
            }
            if(flag == 1)
            {
                if(strcmp(statusing,"Running") == 0)
                {
                    printf("[%d] %s %s [%d]\n",JOB_ORDER[i],statusing,NAMES[i],PIDS[i]);
                }
            }
            if(flag == 2)
            {
                if(status[0] == 'T')
                {
                    printf("[%d] %s %s [%d]\n",JOB_ORDER[i],statusing,NAMES[i],PIDS[i]);
                }
            }

        }
    }
}