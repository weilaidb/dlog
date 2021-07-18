#include <iostream>
//#include "cdlog.h"
#include "dlog.h"

using namespace std;

void test1()
{
//    unsigned int dwLp =  0;
//    for(dwLp = 0;dwLp < 10;dwLp++)
//    {
//        char buf[DLOG_KEY_MAX] = {0};
//        int iLen = 0;

//        iLen = snprintf(buf, sizeof(buf),"%s-%u", "ABC", dwLp);
//        if(iLen < 0)
//        {
//            //TODO
//            printf("error:snprintf invalid len/M:%d(%u),buf:%s\n",iLen, sizeof(buf), buf);
//            return -1;
//        }

//        CDLog::GetInstance("CLK")->dLog(buf, NULL, 0, "niceto meet you!!!,aaaaaaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbbbbbbbbbbbvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvveeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee");
//    }

//    CDLog::GetInstance()->setSw("ABC-0",1);


//    for(dwLp = 0;dwLp < 9;dwLp++)
//    {
//        char buf[DLOG_KEY_MAX] = {0};
//        int iLen = 0;

//        iLen = snprintf(buf, sizeof(buf),"%s-%u", "ABC", dwLp);
//        if(iLen < 0)
//        {
//            //TODO
//            printf("error:snprintf invalid len/M:%d(%u),buf:%s\n",iLen, sizeof(buf), buf);
//            return -1;
//        }

//        CDLog::GetInstance()->dLog(buf, NULL, 0, "niceto meet you!!!,aaaaaaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbbbbbbbbbbbvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvveeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee");
//    }


//    CDLog::GetInstance()->show(1);

////    CDLog::GetInstance()->dLog("abc", NULL, 0, "niceto meet you!!!");
////    CDLog::GetInstance()->dLog("abc", NULL, 0, "niceto meet you!!!");
////    CDLog::GetInstance()->dLog("abc", NULL, 0, "niceto meet you!!!");
////    CDLog::GetInstance()->dLog("abc", NULL, 0, "niceto meet you!!!");
////    CDLog::GetInstance()->dLog("abc12", NULL, 0, "niceto meet you!!!");
////    CDLog::GetInstance()->dLog("abc12", NULL, 0, "niceto meet you!!!");
////    CDLog::GetInstance()->dLog("abc12", NULL, 0, "niceto meet you!!!");
////    CDLog::GetInstance()->dLog("abc12", NULL, 0, "niceto meet you!!!");
////    CDLog::GetInstance()->dLog("abc12", NULL, 0, "niceto meet you!!!");
////    CDLog::GetInstance()->dLog("abc12", NULL, 0, "niceto meet you!!!");
////    CDLog::GetInstance()->dLog("abc12", NULL, 0, "niceto meet you!!!");
////    CDLog::GetInstance()->dLog("abc12", NULL, 0, "niceto meet you!!!");
////    CDLog::dLog("nihaoma");
}

int testDLog(const char *pKey)
{
    unsigned int dwLp =  0;
    for(dwLp = 0;dwLp < 10;dwLp++)
    {
        char buf[DLOG_KEY_MAX] = {0};
        int iLen = 0;

        iLen = snprintf(buf, sizeof(buf),"%s-%u", pKey, dwLp);
        if(iLen < 0)
        {
            //TODO
            printf("error:snprintf invalid len/M:%d(%u),buf:%s\n",iLen, sizeof(buf), buf);
            return -1;
        }

        dLog(0, buf, NULL, 0, "niceto meet you!!!,");
    }
    return 0;
}


int main()
{
//    diagDLogSetSw(0,1);
    dLogInit();

    cout << "Hello World!" << endl;
    testDLog("ABC");
    testDLog("ABC");

    dLog(0,"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaee", NULL, 0,"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxyyyyxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxzz");
    dLog(0,"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaee", NULL, 0,"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxyyyyxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxzz");
//    dLog(0,"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaee", NULL, 0,"yyy");

//    diagDLogShow(0,0);
//    diagDLogShow(0,1);
//    diagDLogShow(0,3);
    diagDLogShow(0,7);

    return 0;
}
