#include <iostream>
#include "cdlog.h"

using namespace std;

int main()
{
    cout << "Hello World!" << endl;
    unsigned int dwLp =  0;
    for(dwLp = 0;dwLp < 10;dwLp++)
    {
        char buf[DLOG_KEY_MAX] = {0};
        int iLen = 0;

        iLen = snprintf(buf, sizeof(buf),"%s-%u", "ABC", dwLp);
        if(iLen < 0)
        {
            //TODO
            printf("error:snprintf invalid len/M:%d(%u),buf:%s\n",iLen, sizeof(buf), buf);
            return -1;
        }

        CDLog::GetInstance()->dLog(buf, NULL, 0, "niceto meet you!!!,aaaaaaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbbbbbbbbbbbvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvveeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee");
    }

    CDLog::GetInstance()->setSw("ABC-0",1);


    for(dwLp = 0;dwLp < 9;dwLp++)
    {
        char buf[DLOG_KEY_MAX] = {0};
        int iLen = 0;

        iLen = snprintf(buf, sizeof(buf),"%s-%u", "ABC", dwLp);
        if(iLen < 0)
        {
            //TODO
            printf("error:snprintf invalid len/M:%d(%u),buf:%s\n",iLen, sizeof(buf), buf);
            return -1;
        }

        CDLog::GetInstance()->dLog(buf, NULL, 0, "niceto meet you!!!,aaaaaaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbbbbbbbbbbbvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvveeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee");
    }


    CDLog::GetInstance()->show();

//    CDLog::GetInstance()->dLog("abc", NULL, 0, "niceto meet you!!!");
//    CDLog::GetInstance()->dLog("abc", NULL, 0, "niceto meet you!!!");
//    CDLog::GetInstance()->dLog("abc", NULL, 0, "niceto meet you!!!");
//    CDLog::GetInstance()->dLog("abc", NULL, 0, "niceto meet you!!!");
//    CDLog::GetInstance()->dLog("abc12", NULL, 0, "niceto meet you!!!");
//    CDLog::GetInstance()->dLog("abc12", NULL, 0, "niceto meet you!!!");
//    CDLog::GetInstance()->dLog("abc12", NULL, 0, "niceto meet you!!!");
//    CDLog::GetInstance()->dLog("abc12", NULL, 0, "niceto meet you!!!");
//    CDLog::GetInstance()->dLog("abc12", NULL, 0, "niceto meet you!!!");
//    CDLog::GetInstance()->dLog("abc12", NULL, 0, "niceto meet you!!!");
//    CDLog::GetInstance()->dLog("abc12", NULL, 0, "niceto meet you!!!");
//    CDLog::GetInstance()->dLog("abc12", NULL, 0, "niceto meet you!!!");
//    CDLog::dLog("nihaoma");
    return 0;
}
