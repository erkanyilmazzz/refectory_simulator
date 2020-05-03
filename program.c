#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <semaphore.h>

#include "arg.h"
/*
*--------------------------------------------
*   N is number of cooks 
*   M is number of students
*   T is number of tables
*   S is counter of size
*   K is kicthen of size  
*   L is times//
*   I number of items in the kitchen 
*--------------------------------------------
*   P is soup
*   C is main course
*   D is desert
*/

int main(int argc, char **argv)
{
    int *n = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0);
    int *m = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0);
    int *t = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0);
    int *s = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0);
    int *k = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0);
    ////////////////////////////////////////////////////////////////////////////////////////////
    sem_t *mutex = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0);
    sem_init(mutex, 1, 1);
    ////////////////////////////////////////////////////////////////////////////////////////////
    int l;
    argHandler(argc, argv, n, m, t, s, &l, k);
    printf("N:%d M:%d T:%d S:%d L:%d K:%d\n", *n, *m, *t, *s, l, *k);
    ////////////////////////////////////////////////////////////////////////////////////////////
    int process;
    for (size_t i = 0; i < (*m); i++)
    {
        int *student_id = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0);
        *student_id = i;
        process = fork();
        if (process == 0)
        {
            for (size_t i = l; i > 0; i--)
            {

                sem_wait(mutex);
                //student prpocess
                printf("it is student pid is:%d and l is %d\n", *student_id, l);
                l--;

                sem_post(mutex);
            }
            exit(0);
        }
        munmap(student_id, sizeof(int));
    }
    //////////////////////////////////////////////////////////////////////////////////////////////
    for (size_t i = 0; i < *n; i++)
    {
        int *cook_id = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0);
        *cook_id = i;
        process = fork();
        if (process == 0)
        {

            //cook process
            printf("it is cook pid is:%d\n", *cook_id);
            exit(0);
        }
        munmap(cook_id, sizeof(int));
    }
    ///////////////////////////////////////////////////////////////////////////////////////////////
    for (size_t i = 0; i < (*m); i++)
    {
        wait(NULL);
    }
    for (size_t i = 0; i < (*n); i++)
    {
        wait(NULL);
    }

    return 0;
}