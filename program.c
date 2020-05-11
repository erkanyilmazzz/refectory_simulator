#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <semaphore.h>
#include <time.h>

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

/**
 **note:you add this file part later so I cant do that part properly
*/

int get_turn(int *number_of_p, int *number_of_c, int *number_of_d, int size_of_kitchen)
{
    int result;

    int x = rand() % 3;
    // printf("x is %d\n\n", x);
    if (x == 0)
    {
        if (((*number_of_p) - (*number_of_c) < 1) && ((*number_of_p) - (*number_of_d) < 1))
        {
            result = 0;
        }
        else
        {
            result = get_turn(number_of_p, number_of_c, number_of_d, size_of_kitchen);
        }
    }
    else if (x == 1)
    {
        if (((*number_of_c) - (*number_of_p) < 1) && ((*number_of_c) - (*number_of_d) < 1))
        {
            result = 1;
        }
        else
        {
            result = get_turn(number_of_p, number_of_c, number_of_d, size_of_kitchen);
        }
    }
    else if (x == 2)
    {
        if (((*number_of_d) - (*number_of_c) < 1) && ((*number_of_d) - (*number_of_c) < 1))
        {
            result = 2;
        }
        else
        {
            result = get_turn(number_of_p, number_of_c, number_of_d, size_of_kitchen);
        }
    }
    else
    {
        printf("x is %d\n\n", x);
    }

    return result;
}

char *file_path;
void handler(int s)
{
    if (file_path != NULL)
    {
        free(file_path);
    }
    return;
}
int main(int argc, char **argv)
{
    struct sigaction sa;
    sa.sa_handler = handler;
    sigaction(SIGINT, &sa, NULL);
    ///////////////////////////////////////////////////////////////////////////////////////////
    int n;
    int m;
    int t; //= mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0);
    int s; //= mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0);
    int k; // = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0);
    int l;
    ///////////////////////////////////////////////////////////////////////////////////////////
    file_path = malloc(sizeof(char) * 100);
    ////////////////////////////////////////////////////////////////////////////////////////////
    argHandler(argc, argv, &n, &m, &t, &s, &l, &k, file_path);
    printf("N:%d M:%d T:%d S:%d L:%d K:%d F:%s\n", n, m, t, s, l, k, file_path);
    ////////////////////////////////////////////////////////////////////////////////////////////
    int *P_in_kithen = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0);
    int *C_in_kithen = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0);
    int *D_in_kithen = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0);
    int *total_item_in_kithen = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0);
    ////////////////////////////////////////////////////////////////////////////////////////////
    int *P_in_counter = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0);
    int *C_in_counter = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0);
    int *D_in_counter = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0);
    int *total_item_in_counter = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0);
    /////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////
    sem_t *kitchen_full = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0);
    sem_t *kitchen_empty = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0);
    sem_init(kitchen_full, 1, 0);
    sem_init(kitchen_empty, 1, k);
    /////////////////////////////////////////////////////////////////////////////////////////////

    sem_t *counter_full = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0);
    sem_t *counter_empty = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0);
    sem_init(counter_full, 1, 0);
    sem_init(counter_empty, 1, s);
    /////////////////////////////////////////////////////////////////////////////////////////////
    sem_t *mutex = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0);
    sem_init(mutex, 1, 1);
    sem_t *mutex_r = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0);
    sem_init(mutex_r, 1, 1);
    ////////////////////////////////////////////////////////////////////////////////////////////
    sem_t *agent = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0);
    sem_t *p = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0);
    sem_t *c = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0);
    sem_t *d = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0);

    int *is_p = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0);
    int *is_c = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0);
    int *is_d = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0);
    *is_p = 0;
    *is_p = 0;
    *is_p = 0;
    //sem_init(agent, 1, 1);
    sem_init(p, 1, 0);
    sem_init(c, 1, 0);
    sem_init(d, 1, 0);
    ////////////////////////////////////////////////////////////////////////////////////////////

    sem_t *empty1 = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0);
    sem_init(empty1, 1, 3);
    ///////////////////////////////////////////////////////////////////////////////////////////////
    int process;

    process = fork();
    if (process == 0)
    { //supliyer
        for (size_t i = 0; i < l * m * 3; i++)
        {
            //sem_wait(counter_empty);

            sem_wait(kitchen_empty);

            sem_wait(mutex_r);
            srand(time(NULL));
            int x = get_turn(P_in_kithen, C_in_kithen, D_in_kithen, k);
            if (x == 0)
            {

                sem_wait(mutex);
                printf("The supplier is P:%d,C:%d,D:%d=%d going to the kitchen to deliver soup:kitchen items\n\n",
                       *P_in_kithen, *C_in_kithen, *D_in_kithen, *P_in_kithen + *C_in_kithen + *D_in_kithen);
                (*P_in_kithen)++;
                printf("The suplyer delivered the soup P:%d,C:%d,D:%d=%d\n\n",
                       *P_in_kithen, *C_in_kithen, *D_in_kithen, *P_in_kithen + *C_in_kithen + *D_in_kithen);
                sem_post(mutex);
            }
            else if (x == 1)
            {

                sem_wait(mutex);
                printf("The supplier is P:%d,C:%d,D:%d=%d going to the kitchen to deliver main course:kitchen items\n\n",
                       *P_in_kithen, *C_in_kithen, *D_in_kithen, *P_in_kithen + *C_in_kithen + *D_in_kithen);
                (*C_in_kithen)++;
                printf("The suplyer delivered the main course P:%d,C:%d,D:%d=%d\n\n",
                       *P_in_kithen, *C_in_kithen, *D_in_kithen, *P_in_kithen + *C_in_kithen + *D_in_kithen);
                sem_post(mutex);
            }
            else if (x == 2)
            {

                sem_wait(mutex);
                printf("The supplier is P:%d,C:%d,D:%d=%d going to the kitchen to deliver desrt:kitchen items\n\n",
                       *P_in_kithen,
                       *C_in_kithen, *D_in_kithen, *P_in_kithen + *C_in_kithen + *D_in_kithen);
                (*D_in_kithen)++;
                printf("The suplyer delivered the desert P:%d,C:%d,D:%d=%d\n\n",
                       *P_in_kithen, *C_in_kithen, *D_in_kithen, *P_in_kithen + *C_in_kithen + *D_in_kithen);
                sem_post(mutex);
            }
            else
            {

                printf("someting wrong hapennnnn-------------------%d\n\n\n", x);
            }
            sem_post(mutex_r);

            sem_post(kitchen_full);
            //sem_post(counter_full);
        }

        exit(0);
    }
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    for (size_t i = 0; i < n; i++)
    {
        int *cook_id = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0);
        *cook_id = i;
        process = fork();
        if (process == 0)
        {
            for (size_t i = 0; i < (3 * l * m / n); i++)
            {

                sem_wait(kitchen_full);
                //cook process
                sem_wait(mutex_r);
                sem_wait(mutex);
                int x;
                if (i == 0)
                {
                    x = 0;
                }
                else
                {
                    x = get_turn(P_in_counter, C_in_counter, D_in_counter, s);
                }
                sem_post(mutex);
                if (x == 0)
                {
                    sem_wait(mutex);
                    printf("\nit is cook pid is:%d ", *cook_id);
                    printf("The enter kitchen for soup P:%d,C:%d,D:%d=%d\n\n",
                           *P_in_kithen, *C_in_kithen, *D_in_kithen, *P_in_kithen + *C_in_kithen + *D_in_kithen);
                    (*P_in_counter)++;
                    (*P_in_kithen)--;
                    printf("The out the kithen kitchen P:%d,C:%d,D:%d=%d\n\n",
                           *P_in_kithen, *C_in_kithen, *D_in_kithen, *P_in_kithen + *C_in_kithen + *D_in_kithen);
                    sem_post(mutex);
                }
                else if (x == 1)
                {
                    sem_wait(mutex);

                    printf("\nit is cook pid is:%d ", *cook_id);
                    printf("The enter kitchen for main course P:%d,C:%d,D:%d=%d\n\n",
                           *P_in_kithen, *C_in_kithen, *D_in_kithen, *P_in_kithen + *C_in_kithen + *D_in_kithen);
                    (*C_in_counter)++;
                    (*C_in_kithen)--;
                    printf("The out the kithen kitchen P:%d,C:%d,D:%d=%d\n\n",
                           *P_in_kithen, *C_in_kithen, *D_in_kithen, *P_in_kithen + *C_in_kithen + *D_in_kithen);

                    sem_post(mutex);
                }
                else if (x == 2)
                {
                    sem_wait(mutex);

                    printf("\nit is cook pid is:%d ", *cook_id);
                    printf("The enter kitchen desert P:%d,C:%d,D:%d=%d\n\n",
                           *P_in_kithen, *C_in_kithen, *D_in_kithen, *P_in_kithen + *C_in_kithen + *D_in_kithen);
                    (*D_in_counter)++;
                    (*D_in_kithen)--;
                    printf("The out the kithen kitchen P:%d,C:%d,D:%d=%d\n\n",
                           *P_in_kithen, *C_in_kithen, *D_in_kithen, *P_in_kithen + *C_in_kithen + *D_in_kithen);

                    sem_post(mutex);
                }

                sem_post(mutex_r);
                sem_post(kitchen_empty);
            }
            exit(0);
        }
        munmap(cook_id, sizeof(int));
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    for (size_t i = 0; i < (m); i++)
    {
        wait(NULL);
    }
    for (size_t i = 0; i < m; i++)
    {
        int *student_id = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0);
        *student_id = i;
        process = fork();
        if (process == 0)
        {

            for (size_t i = l; i > 0; i--)
            {
                //sem_wait(counter_full);
                sem_wait(mutex);
                //student prpocess
                printf("Student %d is going to the counter (round %d) - # of students at counter: 1 and counter items P:%d,C:%d,D:%d=%d\n",
                       *student_id, l, *P_in_counter, *C_in_counter, *D_in_counter, *P_in_counter + *C_in_counter + *D_in_counter);
                //printf("it is student pid is:%d and l is %d\n", );
                (*P_in_counter)--;
                (*C_in_counter)--;
                (*D_in_counter)--;
                //printf("P:%d C:%d D:%d", *P_in_counter, *C_in_counter, *D_in_counter);
                printf("Student %d left table  to eat again (round %d)\n", *student_id, l);

                l--;
                if (i == 1)
                {
                    printf("Student %d is done eating L=%d times - going home – GOODBYE!!!\n", *student_id, l);
                }
                sem_post(mutex);

                //sem_post(counter_empty);
            }
            exit(0);
        }
        munmap(student_id, sizeof(int));
    }
    //////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////////////////////////

    for (size_t i = 0; i < (n); i++)
    {
        wait(NULL);
    }
    wait(NULL);
    free(file_path);
    return 0;
}