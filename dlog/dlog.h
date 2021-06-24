/***************************************************************************
** 版权所有:  WeiLai Copyright (c) 2020-2030  ******************************
** 文件名称:  dlog.h
** 当前版本:  v1.0
** 作    者:
** 完成日期: 2021-06-24_232007
** 修改记录:
** 修改记录:
** 修改日期:
** 版本号  :
** 修改人  :
** 修改内容:
***************************************************************************/
#ifndef __DLOG_H__
#define __DLOG_H__

/*****************************头文件****************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdarg.h>
#include <pthread.h>

using namespace std;

/* 存储内容最大值 */
#define DLOG_CONTENT_MAX (256)


typedef struct T_DLogNode {
    char m_buf[DLOG_CONTENT_MAX];//store buffer
    unsigned char m_sw;//switch
    unsigned short m_same_cnt;//switch
}T_DLogNode, *P_DLogNode;



/*****************************宏定义****************************************/

/*****************************结构体或类型定义*******************************/


/*****************************全局变量****************************************/


/*****************************本地变量****************************************/


/*****************************函数或类声明****************************************/


/*****************************函数或类实现****************************************/








/*****************************by extern "C"****************************************/
/*****************************头文件****************************************/


/*****************************宏定义****************************************/


#ifdef __cplusplus
extern "C" {
#endif

/*****************************结构体或类型定义*******************************/


/*****************************全局变量****************************************/


/*****************************本地变量****************************************/


/*****************************函数或类声明****************************************/


/*****************************函数或类实现****************************************/


#ifdef __cplusplus
}
#endif





#endif /* dlog.h */


