/***************************************************************************
** 版权所有:  WeiLai Copyright (c) 2020-2030  ******************************
** 文件名称:  dlog.cpp
** 当前版本:  v1.0
** 作    者:
** 完成日期: 2021-06-24_232105
** 修改记录:
** 修改记录:
** 修改日期:
** 版本号  :
** 修改人  :
** 修改内容:
***************************************************************************/


/*****************************头文件****************************************/
#include "dlog.h"
#include "pubsw.h"

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
T_DLogMod g_tDLogMod[DLOG_MOD_MAX] = {0};

/*****************************本地变量****************************************/


/*****************************函数或类声明****************************************/


/*****************************函数或类实现****************************************/
void dLogInit()
{
    memset(&g_tDLogMod, 0, sizeof(g_tDLogMod));
    dLogInitByMod(DLOGMODNAME(DLOG_MOD_TEST1), DLOG_MOD_TEST1);
    dLogInitByMod(DLOGMODNAME(DLOG_MOD_TEST2), DLOG_MOD_TEST2);
    dLogInitByMod(DLOGMODNAME(DLOG_MOD_MSGID), DLOG_MOD_MSGID);
}

//初始化模块
P_DLogMod dLogInitByMod(const char *pModeName,unsigned char ucIndex)
{
    if(NULL == pModeName)
    {
        DLOGPRINTF("null pointer\n");
        return NULL;
    }

    P_DLogMod pMod = NULL;
    unsigned int dwLp = 0;
    for(dwLp = 0;dwLp < DLOG_MOD_MAX;dwLp++)
    {
        pMod = &g_tDLogMod[dwLp];
        if(0 == pMod->m_ucUsed)
        {
            break;
        }

        if(isSameBuf(pModeName, pMod->m_ModName, DLOG_MODNAME_MAX, NULL, NULL, 0) > 0)
        {
            return pMod;
        }
    }

    if(dwLp >= DLOG_MOD_MAX)
    {
        DLOGPRINTF("module out of range\n");
        return NULL;
    }

    memset(pMod, 0, sizeof(*pMod));
    memcpy(pMod->m_ModName, pModeName, MIN(strlen(pModeName), DLOG_MODNAME_MAX));
//    pMod->m_Mutex = PTHREAD_MUTEX_INITIALIZER;
    pMod->m_ucUsed = 1;
    pMod->m_ucIndex = ucIndex;

    return pMod;
}


//根据索引查找模块
P_DLogMod findDLogModByIndex(unsigned char ucIndex)
{
    P_DLogMod pMod = NULL;
    if(ucIndex >= DLOG_MOD_MAX)
    {
        DLOGPRINTF("module num out of range! index:%u(max:%d)\n", ucIndex, DLOG_MOD_MAX);
        return NULL;
    }

    unsigned int dwLp = 0;
    for(dwLp = 0;dwLp < DLOG_MOD_MAX;dwLp++)
    {
        pMod = &g_tDLogMod[dwLp];
        if(ucIndex == pMod->m_ucIndex)
        {
            return pMod;
        }
    }

    DLOGPRINTF("module cannot find, please check or init!! index:%u(max:%d)\n", ucIndex, DLOG_MOD_MAX);
    return NULL;
}

int dLog(unsigned char ucModIndex, const char *pTips, const unsigned char *pMsg, unsigned short wLen, const char *fmt, ...)
{
    unsigned int dwVal = 0;
    P_DLogNode pNode = findNodeByKey(ucModIndex, pTips, DLOG_KEY_MAX);
    if(NULL == pNode)
    {
        DLOGPRINTF("dLog Key out of range!! modIndex:%u\n", ucModIndex);
        if(ucModIndex < 30)
        {
            dwVal = pubGetDrvSw(INDEX_DRVSW_DLOG_OVER_RANGE);
            dwVal |= (1U << ucModIndex);
            pubSetDrvSw(INDEX_DRVSW_DLOG_OVER_RANGE, dwVal);
        }
        return 0;
    }


    va_list argptr;
    int cnt;
    char buffer[DLOG_CHAR_CONTENT_MAX] = {0};

    va_start(argptr, fmt);
    cnt = vsnprintf(buffer, sizeof(buffer), fmt, argptr);
    va_end(argptr);
    if(cnt < 0)
    {
        pNode->m_Buf[DLOG_CHAR_CONTENT_MAX - 1] = '\0';
    }

    if(pNode->m_SW > 0)
    {
        DLOGPRINTF("[%s]m_SW:%u, forced logged\n", pNode->m_Key, pNode->m_SW);
        return 0;
    }

    if(true == isSameBuf(pNode->m_Buf, buffer, DLOG_CHAR_CONTENT_MAX, pNode, pMsg, wLen))
    {
        pNode->m_SameCnt++;
        pNode->m_wLen = wLen;
        DLOGPRINTF("[%s]buffer same cnt:%u\n", pNode->m_Key, pNode->m_SameCnt);
        return 0x01;
    }

    DLOGPRINTF("[%s]buffer differ old:%s,new:%s\n", pNode->m_Key, pNode->m_Buf, buffer);
    memset(pNode->m_Buf, 0, DLOG_CHAR_CONTENT_MAX);
    memcpy(pNode->m_Buf, buffer, DLOG_CHAR_CONTENT_MAX);
    pNode->m_Buf[DLOG_CHAR_CONTENT_MAX - 1] = '\0';
    if((NULL != pMsg) && (0 != wLen))
    {
        memcpy(pNode->m_uacStream, pMsg, MIN(DLOG_UCHAR_CONTENT_MAX, wLen));
        pNode->m_wLen = wLen;
    }

    return 0x0;
}

int dLogFormatKey(char *acBuf, unsigned char uacLen, const char *fmt, ...)
{
    if(NULL == acBuf)
    {
        DLOGPRINTF("null pointer\n");
        return -1;
    }

    memset(acBuf,0,uacLen);
    va_list argptr;
    int cnt;

    va_start(argptr, fmt);
    cnt = vsnprintf(acBuf, uacLen, fmt, argptr);
    va_end(argptr);
    if((cnt < 0) && (uacLen > 0))
    {
        acBuf[uacLen - 1] = '\0';
    }

    return 0x0;
}

unsigned char isSameBuf(const char *pBufOrg, char *pBufNew, unsigned short wCmpLen
                        , P_DLogNode pNode, const unsigned char *pMsg, unsigned short wLen)
{
    unsigned char bRet = false;
    if((NULL == pBufOrg) || (NULL == pBufNew) || (NULL == pNode))
    {
        DLOGPRINTF("null pointer\n");
        return false;
    }

    if((NULL != pMsg) && (0 != wLen))
    {
        bRet = (0 == memcmp(pBufOrg, pBufNew, wCmpLen))
                && (0 == memcmp(pNode->m_uacStream, pMsg, MIN(DLOG_UCHAR_CONTENT_MAX, wLen)))
                && (pNode->m_wLen == wLen);
        return bRet;
    }
    else
    {
        bRet = (0 == memcmp(pBufOrg, pBufNew, wCmpLen));
    }

    return bRet;
}

P_DLogNode findNodeByKey(unsigned char ucModIndex, const char *pKey, unsigned short wLen)
{
    P_DLogMod pMod = NULL;
    pMod = findDLogModByIndex(ucModIndex);
    if(NULL == pMod)
    {
        DLOGPRINTF("null pointer\n");
        return 0;
    }

    unsigned int dwLp = 0;
    for(dwLp = 0;dwLp < DLOG_SETS_MAX;dwLp++)
    {
        P_DLogNode pNode = &pMod->m_Sets[dwLp];
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

int diagDLogSetSw(unsigned char ucModIndex, const char *pKey, unsigned char ucSw)
{
    P_DLogMod pMod = NULL;
    pMod = findDLogModByIndex(ucModIndex);
    if(NULL == pMod)
    {
        DLOGPRINTF("null pointer\n");
        return 0;
    }

    unsigned int dwLp = 0;
    char buf[DLOG_KEY_MAX] = {0};
    memcpy(buf, pKey, MIN(strlen(pKey), DLOG_KEY_MAX));

    for(dwLp = 0;dwLp < DLOG_SETS_MAX;dwLp++)
    {
        P_DLogNode pNode = &pMod->m_Sets[dwLp];
        if(0 == pNode->m_Used)
        {
            break;
        }

        if(0 == memcmp(buf, pNode->m_Key, DLOG_KEY_MAX))
        {
            pNode->m_SW = ucSw;
            break;
        }
    }

    return 0;
}


int diagDLogShow(unsigned char ucModIndex, unsigned char ucFlag)
{
    P_DLogMod pMod = NULL;
    pMod = findDLogModByIndex(ucModIndex);
    if(NULL == pMod)
    {
        DLOGPRINTF("null pointer\n");
        return -1;
    }

    unsigned int dwLp = 0;
    unsigned int dwLp2 = 0;

    printf("Module:%s[Idx:%u], out of range Flag:%u[1>>Idx is 1, out of range]\n", pMod->m_ModName, pMod->m_ucIndex, pubGetDrvSw(INDEX_DRVSW_DLOG_OVER_RANGE));
    printf("%-4s%-61s%-8s%-3s\n", "No", "Key", "SameCnt", "Sw");
    for(dwLp = 0;dwLp < DLOG_SETS_MAX;dwLp++)
    {
        P_DLogNode pNode = &pMod->m_Sets[dwLp];
        if(0 == pNode->m_Used)
        {
            break;
        }

        printf("%-4u%-61s%-8u%-3u\n", dwLp+1, pNode->m_Key, pNode->m_SameCnt, pNode->m_SW);
        //print buf
        if(ucFlag & 0x1)
        {
            if(strlen(pNode->m_Buf) >= DLOG_CHAR_CONTENT_MAX - 1)
            {
                printf("  buf[F]|-- %s\n",pNode->m_Buf);
            }
            else
            {
                printf("  buf   |-- %s\n",pNode->m_Buf);
            }
        }

        if(ucFlag & 0x2)
        {
            if(pNode->m_wLen >= DLOG_UCHAR_CONTENT_MAX)
            {
                printf("  msg[%u out of range:%d]\n",pNode->m_wLen, DLOG_UCHAR_CONTENT_MAX);
            }
            else
            {
                printf("  msg[%u]\n", pNode->m_wLen);
            }
        }
        //print unsigned buf
        if((ucFlag & 0x4) && (pNode->m_wLen > 0))
        {
            if(pNode->m_wLen >= DLOG_UCHAR_CONTENT_MAX)
            {
                printf("  msg[F]\n");
            }
            else
            {
                printf("  msg[%u]\n", pNode->m_wLen);
            }

            for(dwLp2 = 0;dwLp2 < pNode->m_wLen; dwLp2++)
            {
                printf("%02x\n", pNode->m_uacStream[dwLp2]);
            }
            printf("\n");
            printf("\n");
        }
    }

    return 0;
}

#ifdef __cplusplus
}
#endif







