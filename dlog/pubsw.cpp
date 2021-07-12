#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "pubsw.h"



//declare variables
T_DrvSw g_DrvSw = {0};



#ifdef __cplusplus
extern "C" {
#endif

unsigned int pubGetDrvSw (unsigned int dwIndex)
{
    if(dwIndex > INDEX_MAX - 1)
    {
        return 0;
    }

    return g_DrvSw.m_Data[dwIndex] ;
}

unsigned int pubSetDrvSw (unsigned int dwIndex, unsigned int _val)
{
    if(dwIndex > INDEX_MAX - 1)
    {
        return 0;
    }

    g_DrvSw.m_Data[dwIndex]  = _val;
    return g_DrvSw.m_Data[dwIndex] ;
}

int pubShowDrvSw()
{
#ifndef ARRAYSIZE
#define ARRAYSIZE(A) ((unsigned int)(sizeof(A)/sizeof(A[0])))
#endif


    unsigned int  dwLp =  0;
    for(dwLp = 0;dwLp < ARRAYSIZE(g_DrvSw.m_Data);dwLp++)
    {
        printf("No:%-3u -- %-3u\n", dwLp+1, g_DrvSw.m_Data[dwLp]);

    }

    return 0;
}


#ifdef __cplusplus
}
#endif
