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
#ifndef DLOG_H
#define DLOG_H

/*****************************头文件****************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdarg.h>
#include <pthread.h>

using namespace std;

/* 存储内容最大值 */
#define DLOG_MODNAME_MAX       (64)  /* MOD字符最大数量 */
#define DLOG_KEY_MAX           (64)  /* KEY字符最大数量 */
#define DLOG_CHAR_CONTENT_MAX  (256) /* 保存字符最大数量 */
#define DLOG_UCHAR_CONTENT_MAX (256) /* 保存BYTE流最大数量 */
#define DLOG_SETS_MAX          (512) /* 至多比较条数 */


/**
  模块名称及索引
*/
enum{
    DLOG_MOD_TEST1,
    DLOG_MOD_TEST2,
    DLOG_MOD_MSGID,

    DLOG_MOD_MAX, /* MOD模块最大数量 */
};

#define DLOGMODNAME(A) #A

#ifndef DLOGPRINTF
#define DLOGPRINTF(fmt,...) \
do{ \
    if(1)\
    {\
        printf("[%-40s:%-3d]" fmt , __FUNCTION__ , __LINE__  ,##__VA_ARGS__);\
    }\
}while(0)
#endif



/*****************************宏定义****************************************/
#ifndef ARRAYSIZE
#define ARRAYSIZE(A) ((unsigned int)(sizeof(A)/sizeof(A[0])))
#endif

#ifndef MAX
#define MAX(a,b) ((a)>(b)?(a):(b))
#endif

#ifndef MIN
#define MIN(a,b) ((a)<(b)?(a):(b))
#endif

/*****************************结构体或类型定义*******************************/
typedef struct T_DLogNode {
    char m_Key[DLOG_KEY_MAX];//key
    char m_Buf[DLOG_CHAR_CONTENT_MAX];//content
    unsigned char m_uacStream[DLOG_UCHAR_CONTENT_MAX];//stream data
    unsigned char m_SW;//switch 1:forced log, 0:auto judge
    unsigned char m_Used;//is used, 1:used,0:no use
    unsigned char m_Pad;//
    unsigned short m_SameCnt;//same cnt record
    unsigned short m_wLen;//buffer length
}T_DLogNode, *P_DLogNode;


typedef struct T_DLogMod{
    unsigned char m_ucIndex;  /* 模块索引 */
    unsigned char m_ucUsed;   /* 是否被使用 */
    T_DLogNode m_Sets[DLOG_SETS_MAX]; /* 支持数量 */
    char m_ModName[DLOG_MODNAME_MAX]; /* 模块名 */
    pthread_mutex_t m_Mutex; /* 锁 */
}T_DLogMod, *P_DLogMod ;


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
void dLogInit();
P_DLogMod dLogInitByMod(const char *pModeName,unsigned char ucIndex);
P_DLogMod findDLogModByIndex(unsigned char ucIndex);
int dLog(unsigned char ucModIndex, const char *pTips, const unsigned char *pMsg, unsigned short wLen, const char *fmt, ...);
int dLogFormatKey(char *acBuf, unsigned char uacLen, const char *fmt, ...);
unsigned char isSameBuf(const char *pBufOrg, char *pBufNew, unsigned short wCmpLen
                        , P_DLogNode pNode, const unsigned char *pMsg, unsigned short wLen);
P_DLogNode findNodeByKey(unsigned char ucModIndex, const char *pKey, unsigned short wLen);
int diagDLogSetSw(unsigned char ucModIndex, const char *pKey, unsigned char ucSw);
int diagDLogShow(unsigned char ucModIndex, unsigned char ucFlag);
/*****************************函数或类实现****************************************/


#ifdef __cplusplus
}
#endif





#endif /* DLOG_H */


