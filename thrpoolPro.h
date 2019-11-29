#ifndef __THRPOOLPRO_H_
#define	__THRPOOLPRO_H_
#ifdef __cplusplus
extern "C"{
#endif


#include <pthread.h>

typedef void (*Func)(void *);
struct ThrObj{
    pthread_t  thr_id;
    pthread_mutex_t thr_mutex;
    pthread_cond_t thr_cond;
    int thr_status;
    Func thr_tsk;
    void *thr_arg;
};

struct ThrPoolHandle{
    int thr_nums;
/*
minsize = 16*1024 Bytes.
If this value is 0, then this thread will be set default size 8192KBytes. Or other size checked by : ulimit -s.
*/
    int thr_stkSize;
/*
    Thread priority, 0-99; default value is 98
*/
    int thr_stkPri;

    struct ThrObj *pthr_arr;
    pthread_mutex_t sched_mutex;
};

/*
    Create a thread pool accroding to pHdl(IN).
    pHdl : [IN], need to be clear first and vertify thr_nums > 0; or code will change thr_nums = 1.
    return value :  0 ok
                    -1 failed
*/
int ThrPoolHandleInit(struct ThrPoolHandle *pHdl);
int ThrPoolHandleDeInit(struct ThrPoolHandle *pHdl);

/*
    Wake up the index threads in pHdl, run by tsk and arg.
*/
int ThrPoolObjWake(struct ThrPoolHandle *pHdl, int index, void *Tsk, void *Arg);

/*
    Get a free thr tsk
    return value : the index of free tsk, used by ThrPoolObjWake
*/
int ThrPoolSched(struct ThrPoolHandle *pHdl);
int ThrPoolPushWait(struct ThrPoolHandle *pHdl, void *Tsk, void *Arg);
#ifdef __cplusplus
}
#endif
#endif	//head file
