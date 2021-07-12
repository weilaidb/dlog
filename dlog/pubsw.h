#ifndef PUBSW_H
#define PUBSW_H

enum{
    INDEX_DRVSW_DLOG_OVER_RANGE,
    INDEX_MAX,
};


//
typedef struct T_DrvSw
{
    unsigned int m_Data[INDEX_MAX];
}T_DrvSw, *P_DrvSw;


#ifdef __cplusplus
extern "C" {
#endif

unsigned int pubGetDrvSw (unsigned int dwIndex);
unsigned int pubSetDrvSw (unsigned int dwIndex, unsigned int _val);
int pubShowDrvSw();

#ifdef __cplusplus
}
#endif




#endif // PUBSW_H
