/*************************************************************************
 * File Name: debug.h
 * Author: 
 * Mail: 
 * Created Time: Thu 06 Feb 2020 09:06:18 AM PST
 ************************************************************************/
#include <sys/time.h>
#include <time.h>
#include <stdio.h>
#include <assert.h>

#ifndef PROJECT_PATH_DEBUG_H
#define PROJECT_PATH_DEBUG_H

#define print_func_name() {                                                 \
    printf("\n\n%s%d%s: %s%s%s():                                           \
        \n\r----------------------------------------------\n",              \
        "\e[1;33m", __LINE__, "\033[0m", "\e[1;34m", __func__, "\033[0m");  \
}

#define MEAS_RUNTIME(funcs, NUM)                        \
{                                                       \
    double ss, ee, timediff;                            \
    ss = (double)clock()/CLOCKS_PER_SEC;                \
    funcs(NUM);                                         \
    ee = (double)clock()/CLOCKS_PER_SEC;                \
    timediff = ee - ss;                                 \
    printf("\t \e[1;34mRuntime: %.6f sec\033[0m\n", timediff); \
}

#endif
