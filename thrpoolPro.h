#ifndef __THRPOOLPRO_H_
#define	__THRPOOLPRO_H_
#ifdef __cplusplus
extern "C"{
#endif


#include <pthread.h>

struct ThrObj{
    pthread_t  thr_id;
    pthread_mutex_t thr_mutex;
    pthread_cond_t thr_cond;
    int thr_status;
    void *thr_tsk;
    void *thr_arg;
};

struct ThrPoolHandle{
    int thr_nums;
    struct ThrObj *pThrArr;
};

/*
    Create a thread pool accroding to pHdl(IN).
    pHdl : [IN], need to be clear first and vertify thr_nums > 0; or code will change thr_nums = 1.
    return value :  0 ok
                    -1 failed
*/
int ThrPoolHandleInit(struct ThrPoolHandle *pHdl);
#ifdef __cplusplus
}
#endif
#endif	//head file
