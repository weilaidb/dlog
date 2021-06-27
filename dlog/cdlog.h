/***************************************************************************
** 版权所有:  WeiLai Copyright (c) 2020-2030  ******************************
** 文件名称:  cdlog.h
** 当前版本:  v1.0
** 作    者:
** 完成日期: 2021-06-24_232327
** 修改记录:
** 修改记录:
** 修改日期:
** 版本号  :
** 修改人  :
** 修改内容:
***************************************************************************/
#ifndef CDLOG_H
#define CDLOG_H
/*****************************头文件****************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdarg.h>
#include <pthread.h>
#include <iostream>
#include <map>
#include <string>
#include "basetype.h"


using namespace std;

/*****************************宏定义****************************************/
#ifndef ARRAYSIZE
#define ARRAYSIZE(A) ((unsigned int)(sizeof(A)/sizeof(A[0])))
#endif

#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))


/* 存储内容最大值 */
#define DLOG_KEY_MAX (64)       /* KEY字符最大数量 */
#define DLOG_CONTENT_MAX (512)  /* 保存字符最大数量 */
#define DLOG_SETS_MAX (512)     /* 至多比较条数 */



/*****************************结构体或类型定义*******************************/

typedef struct T_DLogNode {
    char m_Key[DLOG_KEY_MAX];//key
    char m_Buf[DLOG_CONTENT_MAX];//content
    BYTE m_SW;//switch 1:forced log,0:auto judge
    BYTE m_Used;//is used,1:used,0:no use
    WORD m_SameCnt;//same cnt record
}T_DLogNode, *P_DLogNode;




/*****************************全局变量****************************************/


/*****************************本地变量****************************************/


/*****************************函数或类声明****************************************/

class CDLog
{
public:
    CDLog();
    CDLog(const char *pName);

    int dLog(const char *pTips, BYTE *pMsg, WORD wLen, const char *fmt,...);
    BYTE isSameBuf(char *pBufOrg, char *pBufNew, WORD wCmpLen);
    P_DLogNode findNodeByKey(const char *pKey, WORD wLen);
    int show(BYTE ucPrintBuf = 0);
    int setSw(const char *pKey, BYTE uacSw);
    string getStrOfData(BYTE *pData, WORD wLen);

private:
    pthread_mutex_t m_Mutex;
    T_DLogNode m_Sets[DLOG_SETS_MAX];
    char m_ModName[DLOG_KEY_MAX];

public:
    static CDLog* GetInstance();
    static CDLog* GetInstance(const char *pName);

private:
    static CDLog* m_pInstance;
};

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





#endif /* CDLOG_H */

