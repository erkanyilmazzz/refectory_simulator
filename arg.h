#ifndef _ARGH
#define _ARGH

#define USAGE_ERROR -1
#define ARG_NOT_IN_RANGE_ERROR -2
#define INVALID_PATH_ERROR -3

//K = 3(L-1)M+1
/*
*   N is number of cooks 
*   M is number of students
*   T is number of tables
*   S is counter of size
*   K is kicthen of size  
*--------------------------------------------
*   M > N > 2
*   S > 3
*   M > T >= 1
*   L >= 3
*   K = 3(L-1)M+1
*/
int argHandler(int __argc, char **__argv, int *n, int *m, int *t, int *s, int *l, int *k);

#endif