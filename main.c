#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "thrpoolPriv.h"
#include "thrpoolPro.h"

void MsgPrint(void *msg)
{
    printf("%s\n", (char *)msg);
}

int main(int argc, char *argv[])
{
    struct ThrPoolHandle tpHdl;

    if(argc < 2){
        printf("%s | Wrong arg!\n", __func__);
        exit(1);
    }

    memset(&tpHdl, 0, sizeof(struct ThrPoolHandle));
    tpHdl.thr_nums = atoi((char *)argv[1]);
    tpHdl.thr_stkSize = 2*1024*1024;
    tpHdl.thr_stkPri = 99;
    ThrPoolHandleInit(&tpHdl);

    char *msg = "Hello world !";
    int index;
    int counts = 10;
    while(counts--){
        sleep(1);
        index = ThrPoolSched(&tpHdl);
        if(index >= 0){
            ThrPoolObjWake(&tpHdl, index, &MsgPrint, msg);
        }
        index = ThrPoolSched(&tpHdl);
        if(index >= 0){
            ThrPoolObjWake(&tpHdl, index, &MsgPrint, msg);
        }
        index = ThrPoolSched(&tpHdl);
        if(index >= 0){
            ThrPoolObjWake(&tpHdl, index, &MsgPrint, msg);
        }
        sleep(1);
    }
    ThrPoolHandleDeInit(&tpHdl);
    return 0;
}


