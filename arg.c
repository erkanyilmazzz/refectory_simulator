/**
 *  Author :Erkan Yılmaz 
 *  NO:161044044
 *  Date:19/04/2020
*/
#include "arg.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <getopt.h>
void print_err()
{
    printf("M > N > 2\nS > 3\nM > T >= 1\nL >= 3\n");
}

int argHandler(int __argc, char **__argv, int *_n, int *_m, int *_t, int *_s, int *_l, int *_k)
{
    int option;
    int iflag = 0, oflag = 0, tflag = 0;
    int outputlen;
    int inputlen;

    int n_flag = 0, m_flag = 0, t_flag = 0, s_flag = 0, l_flag = 0;
    while ((option = getopt(__argc, __argv, "N: M: T: S: L:")) != -1)
    {

        //printf("option is %d\n",option);
        switch (option)
        {
        case 'N':
            *_n = atoi(optarg);
            n_flag++;
            break;
        case 'M':
            *_m = atoi(optarg);
            m_flag++;
            break;
        case 'T':
            *_t = atoi(optarg);
            t_flag++;
            break;
        case 'S':
            *_s = atoi(optarg);
            s_flag++;
            break;
        case 'L':
            *_l = atoi(optarg);
            l_flag++;
            break;
        default:
            break;
        }
    }

    if (n_flag != 1 | m_flag != 1 | t_flag != 1 | s_flag != 1 | l_flag != 1)
    {
        printf("usage is <./program -N param -M param -T param -S param -L param>\n");
        exit(-1);
    }
    if (!(*_m > *_n) | !(*_n > 2))
    {
        print_err();
        exit(-1);
    }
    if (!(*_s > 3))
    {
        print_err();
        exit(-1);
    }
    if (!(*_m > *_t) | !(*_t >= 1))
    {
        print_err();
        exit(-1);
    }
    if (!(*_l >= 3))
    {
        print_err();
        exit(-1);
    }

    *_k = 3 * (*_l - 1) * (*_m) + 1;

    return 0;
}
