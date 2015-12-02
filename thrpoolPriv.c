#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

#include "thrpoolPriv.h"
#include "thrpoolPro.h"

/***********************************************************************/
static void ThrObjExec(void *pArg)
{
    struct ThrObj *pObj = pArg;
    pthread_mutex_lock(&pObj->thr_mutex);
    while(1){
        printf("%s | Take a snap waiting for condtion !\n", __func__);
        pthread_cond_wait(&pObj->thr_cond, &pObj->thr_mutex);
    }
    pthread_mutex_unlock(&pObj->thr_mutex);
}

static int ThrObjInit(struct ThrObj *pObj)
{
    int ret = 0;
    pthread_mutex_init(&pObj->thr_mutex, NULL);
    pthread_condattr_init(&pObj->thr_cond);
    pObj->thr_status = THR_STATE_FREE;
    pObj->thr_tsk = NULL;
    pObj->thr_arg = NULL;
    if((ret = pthread_create(&pObj->thr_id, NULL, (void *)ThrObjExec, (void *)pObj)) < 0){
        printf("%s | Create thread Obj failed!\n", __func__);
        return -1;
    }else{
        pthread_detach(pObj->thr_id);
    }

    return 0;
}

int ThrPoolHandleInit(struct ThrPoolHandle *pHdl)
{
    struct ThrObj *pObj = NULL;
    int i = 0;

    if(pHdl == NULL){
        printf("Wrong arg !\n");
        return -1;
    }
    if(pHdl->thr_nums > MAX_THR_POOL_OBJS){
        printf("%s | Wrong thread numbers !\n", __func__);
        return -1;
    }
    if(pHdl->thr_nums <= 0){
        pHdl->thr_nums = 1;
    }
    pHdl->pThrArr = (struct ThrObj *)malloc(pHdl->thr_nums * sizeof(struct ThrObj));

    for(i = 0; i < pHdl->thr_nums; i++){
        pObj = &pHdl->pThrArr[i];
        ThrObjInit(pObj);
    }

    return 0;
}
/***********************************************************************/

int ThrPoolObjWake()
{

}
/*
    Get a free thr tsk
*/
struct ThrPoolHandle *ThrPoolSched(struct ThrPoolHandle *pHdl)
{
    int i = 0;
    struct ThrObj pObj;
    for(i = 0; i < pHdl->thr_nums; i++){

    }
}
