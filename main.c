#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "thrpoolPriv.h"
#include "thrpoolPro.h"

void MsgPrint(void *msg)
{
    printf("%s\n", (char *)msg);
	usleep(100*1000);
}

int main(int argc, char *argv[])
{
	int ret =  -1;
    struct ThrPoolHandle tpHdl;

    if(argc < 2){
        printf("%s | Wrong arg!\n", __func__);
		return -1;
    }

    memset(&tpHdl, 0, sizeof(struct ThrPoolHandle));
    tpHdl.thr_nums = atoi((char *)argv[1]);
    tpHdl.thr_stkSize = 2*1024*1024;
    tpHdl.thr_stkPri = 99;
    ret = ThrPoolHandleInit(&tpHdl);
	if(ret < 0)
	{
		return -1;	
	}
	

    char *msg = "Hello , The suck world !";
    int index;
    int counts = 5;
    while(0){
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
	counts = 5;
	while(counts--)
	{
		ThrPoolPushWait(&tpHdl, &MsgPrint, msg);	
		ThrPoolPushWait(&tpHdl, &MsgPrint, msg);	
		ThrPoolPushWait(&tpHdl, &MsgPrint, msg);	
		ThrPoolPushWait(&tpHdl, &MsgPrint, msg);	
	}
    ThrPoolHandleDeInit(&tpHdl);
    return 0;
}


