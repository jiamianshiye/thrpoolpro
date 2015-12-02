#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "thrpoolPriv.h"
#include "thrpoolPro.h"

int main(int argc, char *argv[])
{
    struct ThrPoolHandle tpHdl;

    if(argc < 2)
        printf("%s | Wrong arg!\n", __func__);

    memset(&tpHdl, 0, sizeof(struct ThrPoolHandle));
    tpHdl.thr_nums = atoi((char *)argv[1]);
    ThrPoolHandleInit(&tpHdl);

    while(1)
        sleep(10);
    return 0;
}


