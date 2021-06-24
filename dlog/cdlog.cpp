/***************************************************************************
** 版权所有:  WeiLai Copyright (c) 2020-2030  ******************************
** 文件名称:  cdlog.cpp
** 当前版本:  v1.0
** 作    者:
** 完成日期: 2021-06-24_232425
** 修改记录:
** 修改记录:
** 修改日期:
** 版本号  :
** 修改人  :
** 修改内容:
***************************************************************************/


/*****************************头文件****************************************/
#include "cdlog.h"

/*****************************宏定义****************************************/

/*****************************结构体或类型定义*******************************/


/*****************************全局变量****************************************/

/*****************************本地变量****************************************/
CDLog* CDLog::m_pInstance = NULL;


/*****************************函数或类声明****************************************/


/*****************************函数或类实现****************************************/

CDLog::CDLog()
{
    m_Mutex = PTHREAD_MUTEX_INITIALIZER;
    memset(&m_Sets,0,sizeof (m_Sets));
}

CDLog* CDLog::GetInstance()
{
    if ( m_pInstance == NULL )
    {
        m_pInstance = new CDLog;
    }

    return m_pInstance;
}


int CDLog::dLog(const char *pTips, unsigned char *pMsg, unsigned short wLen, const char *fmt,...)
{
    P_DLogNode pNode = findNodeByKey(pTips, DLOG_KEY_MAX);
    if(NULL == pNode)
    {
        printf("dLog Key out of range!!\n");
        return 0xFE;
    }


    char buffer[DLOG_CONTENT_MAX] = {0};
    va_list argptr;
    int cnt;

    va_start(argptr, fmt);
    cnt = vsnprintf(buffer,sizeof(buffer) ,fmt, argptr);
    va_end(argptr);
    if(cnt < 0)
    {
        //TODO
//        printf("error:snprintf invalid len/M:%d(%u),buf:%s\n",iLen, sizeof(buffer), buffer);
        return -1;
    }

    if(true == isSameCont(pNode->m_Buf, buffer, DLOG_CONTENT_MAX))
    {
        pNode->m_SameCnt++;
        printf("[%s]buffer same cnt:%u\n", pNode->m_Key, pNode->m_SameCnt);
        return 0x1;
    }

    printf("[%s]buffer differ old:%s, new:%s\n", pNode->m_Key, pNode->m_Buf, buffer);
    memcpy(pNode->m_Buf, buffer, DLOG_CONTENT_MAX);

    return 0x0;

    return(cnt);
}


unsigned char CDLog::isSameCont(char *pBufOrg, char *pBufNew, unsigned short wCmpLen)
{
    if((NULL == pBufOrg) || (NULL == pBufNew))
    {
        printf("null ponter\n");
        return false;
    }

    return (0 == memcmp(pBufOrg, pBufNew, wCmpLen));
}


P_DLogNode CDLog::findNodeByKey(const char *pKey, unsigned short wLen)
{
    unsigned int dwLp =  0;
    for(dwLp = 0;dwLp < ARRAYSIZE(m_Sets);dwLp++)
    {
        //printf("No:%-03u -- %-03u\n", dwLp+1, m_Sets[dwLp]);
        P_DLogNode pNode = &m_Sets[dwLp];
        if(0 == pNode->m_Used)
        {
            memcpy(pNode->m_Key, pKey, wLen);
            pNode->m_Used = 1;
            return pNode;
        }

        if(0 == memcmp(pKey, pNode->m_Key, ARRAYSIZE(pNode->m_Key)))
        {
            return pNode;
        }
    }

    return NULL;
}






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

