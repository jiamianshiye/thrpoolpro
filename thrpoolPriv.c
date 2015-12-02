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

    while(1){
        pthread_mutex_lock(&pObj->thr_mutex);
        pObj->thr_status = THR_STATE_FREE;
        printf("%s | Take a snap waiting for condtion !\n", __func__);
        pthread_cond_wait(&pObj->thr_cond, &pObj->thr_mutex);

        pObj->thr_tsk(pObj->thr_arg);


        pthread_mutex_unlock(&pObj->thr_mutex);
    }

}

static int ThrObjInit(struct ThrObj *pObj)
{
    int ret = 0;
    pthread_mutex_init(&pObj->thr_mutex, NULL);
    pthread_cond_init(&pObj->thr_cond, NULL);
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
    pHdl->pthr_arr = (struct ThrObj *)malloc(pHdl->thr_nums * sizeof(struct ThrObj));

    for(i = 0; i < pHdl->thr_nums; i++){
        pObj = &pHdl->pthr_arr[i];
        ThrObjInit(pObj);
    }

    return 0;
}
int ThrPoolHandleDeInit(struct ThrPoolHandle *pHdl)
{
    int i = 0;
    struct ThrObj *pObj = NULL;

    for(i = 0; i < pHdl->thr_nums; i++){
        pObj = &pHdl->pthr_arr[i];
        pthread_cancel(pObj->thr_id);
        pthread_mutex_destroy(&pObj->thr_mutex);
        pthread_cond_destroy(&pObj->thr_cond);

    }
    pHdl->thr_nums = 0;
    free(pHdl->pthr_arr);
    printf("%s | Thr Pool Deinit !\n", __func__);
    return 0;
}

/***********************************************************************/

int ThrPoolObjWake(struct ThrPoolHandle *pHdl, int index, void *Tsk, void *Arg)
{
    struct ThrObj *pObj;

    if(pHdl->thr_nums <= index || index < 0){
        printf("%s | Wrong args !\n", __func__);
        return -1;
    }

    pObj = &pHdl->pthr_arr[index];
    pthread_mutex_lock(&pObj->thr_mutex);
    pObj->thr_tsk = Tsk;
    pObj->thr_arg = Arg;
    pObj->thr_status = THR_STATE_BUSY;
    pthread_mutex_unlock(&pObj->thr_mutex);
    pthread_cond_signal(&pObj->thr_cond);

    return 0;
}
/*
    Get a free thr tsk
    return value : free tsk index
*/
int ThrPoolSched(struct ThrPoolHandle *pHdl)
{
    int i = 0;
    struct ThrObj *pObj;
    for(i = 0; i < pHdl->thr_nums; i++){
        pObj = &pHdl->pthr_arr[i];
        if(pObj->thr_status == THR_STATE_BUSY)
            continue;
        else if(pObj->thr_status == THR_STATE_FREE)
            break;
    }
    return i == pHdl->thr_nums ? -1 : i;
}
