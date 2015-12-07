#ifndef __THRPOOLPRIV_H_
#define	__THRPOOLPRIV_H_
#ifdef __cplusplus
extern "C"{
#endif
//Max threads in pool
#define     MAX_THR_POOL_OBJS   (32)

#define     THR_STATE_FAIL      (-1) // thr create failed
#define     THR_STATE_FREE      (0) // free
#define     THR_STATE_BUSY      (1) // occupied

#ifdef __cplusplus
}
#endif
#endif	//head file
