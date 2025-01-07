/* cfg1_out.c */
#define TOPPERS_CFG1_OUT  1
#include "kernel/kernel_int.h"


#ifdef INT64_MAX
  typedef int64_t signed_t;
  typedef uint64_t unsigned_t;
#else
  typedef int32_t signed_t;
  typedef uint32_t unsigned_t;
#endif

#include <target_cfg1_out.h>

const uint32_t TOPPERS_cfg_magic_number = 0x12345678;
const uint32_t TOPPERS_cfg_sizeof_signed_t = sizeof(signed_t);
const unsigned_t TOPPERS_cfg_CHAR_BIT = CHAR_BIT;
const unsigned_t TOPPERS_cfg_CHAR_MAX = CHAR_MAX;
const unsigned_t TOPPERS_cfg_CHAR_MIN = CHAR_MIN;
const unsigned_t TOPPERS_cfg_SCHAR_MAX = SCHAR_MAX;
const unsigned_t TOPPERS_cfg_SHRT_MAX = SHRT_MAX;
const unsigned_t TOPPERS_cfg_INT_MAX = INT_MAX;
const unsigned_t TOPPERS_cfg_LONG_MAX = LONG_MAX;

const unsigned_t TOPPERS_cfg_TA_NULL = TA_NULL;
const unsigned_t TOPPERS_cfg_TA_ACT = TA_ACT;
const unsigned_t TOPPERS_cfg_TA_TPRI = TA_TPRI;
const unsigned_t TOPPERS_cfg_TA_MPRI = TA_MPRI;
const unsigned_t TOPPERS_cfg_TA_WMUL = TA_WMUL;
const unsigned_t TOPPERS_cfg_TA_CLR = TA_CLR;
const unsigned_t TOPPERS_cfg_TA_STA = TA_STA;
const unsigned_t TOPPERS_cfg_TA_NONKERNEL = TA_NONKERNEL;
const unsigned_t TOPPERS_cfg_TA_ENAINT = TA_ENAINT;
const unsigned_t TOPPERS_cfg_TA_EDGE = TA_EDGE;
const signed_t TOPPERS_cfg_TMIN_TPRI = TMIN_TPRI;
const signed_t TOPPERS_cfg_TMAX_TPRI = TMAX_TPRI;
const signed_t TOPPERS_cfg_TMIN_DPRI = TMIN_DPRI;
const signed_t TOPPERS_cfg_TMAX_DPRI = TMAX_DPRI;
const signed_t TOPPERS_cfg_TMIN_MPRI = TMIN_MPRI;
const signed_t TOPPERS_cfg_TMAX_MPRI = TMAX_MPRI;
const signed_t TOPPERS_cfg_TMIN_ISRPRI = TMIN_ISRPRI;
const signed_t TOPPERS_cfg_TMAX_ISRPRI = TMAX_ISRPRI;
const unsigned_t TOPPERS_cfg_TMAX_MAXSEM = TMAX_MAXSEM;
const unsigned_t TOPPERS_cfg_TMAX_RELTIM = TMAX_RELTIM;
const signed_t TOPPERS_cfg_TMIN_INTPRI = TMIN_INTPRI;
const unsigned_t TOPPERS_cfg_OMIT_INITIALIZE_INTERRUPT = 
#if defined(OMIT_INITIALIZE_INTERRUPT)
(1);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_OMIT_INITIALIZE_EXCEPTION = 
#if defined(OMIT_INITIALIZE_EXCEPTION)
(1);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_USE_TSKINICTXB = 
#if defined(USE_TSKINICTXB)
(1);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_sizeof_ID = sizeof(ID);
const unsigned_t TOPPERS_cfg_sizeof_uint_t = sizeof(uint_t);
const unsigned_t TOPPERS_cfg_sizeof_SIZE = sizeof(SIZE);
const unsigned_t TOPPERS_cfg_sizeof_ATR = sizeof(ATR);
const unsigned_t TOPPERS_cfg_sizeof_PRI = sizeof(PRI);
const unsigned_t TOPPERS_cfg_sizeof_void_ptr = sizeof(void*);
const unsigned_t TOPPERS_cfg_sizeof_VP = sizeof(void*);
const unsigned_t TOPPERS_cfg_sizeof_intptr_t = sizeof(intptr_t);
const unsigned_t TOPPERS_cfg_sizeof_FP = sizeof(FP);
const unsigned_t TOPPERS_cfg_sizeof_TINIB = sizeof(TINIB);
const unsigned_t TOPPERS_cfg_offsetof_TINIB_tskatr = offsetof(TINIB,tskatr);
const unsigned_t TOPPERS_cfg_offsetof_TINIB_exinf = offsetof(TINIB,exinf);
const unsigned_t TOPPERS_cfg_offsetof_TINIB_task = offsetof(TINIB,task);
const unsigned_t TOPPERS_cfg_offsetof_TINIB_ipriority = offsetof(TINIB,ipriority);
const unsigned_t TOPPERS_cfg_offsetof_TINIB_stksz = 
#if !defined(USE_TSKINICTXB)
(offsetof(TINIB,stksz));
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_offsetof_TINIB_stk = 
#if !defined(USE_TSKINICTXB)
(offsetof(TINIB,stk));
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_offsetof_TINIB_texatr = offsetof(TINIB,texatr);
const unsigned_t TOPPERS_cfg_offsetof_TINIB_texrtn = offsetof(TINIB,texrtn);
const unsigned_t TOPPERS_cfg_sizeof_SEMINIB = sizeof(SEMINIB);
const unsigned_t TOPPERS_cfg_offsetof_SEMINIB_sematr = offsetof(SEMINIB,sematr);
const unsigned_t TOPPERS_cfg_offsetof_SEMINIB_isemcnt = offsetof(SEMINIB,isemcnt);
const unsigned_t TOPPERS_cfg_offsetof_SEMINIB_maxsem = offsetof(SEMINIB,maxsem);
const unsigned_t TOPPERS_cfg_sizeof_FLGPTN = sizeof(FLGPTN);
const unsigned_t TOPPERS_cfg_sizeof_FLGINIB = sizeof(FLGINIB);
const unsigned_t TOPPERS_cfg_offsetof_FLGINIB_flgatr = offsetof(FLGINIB,flgatr);
const unsigned_t TOPPERS_cfg_offsetof_FLGINIB_iflgptn = offsetof(FLGINIB,iflgptn);
const unsigned_t TOPPERS_cfg_sizeof_DTQINIB = sizeof(DTQINIB);
const unsigned_t TOPPERS_cfg_offsetof_DTQINIB_dtqatr = offsetof(DTQINIB,dtqatr);
const unsigned_t TOPPERS_cfg_offsetof_DTQINIB_dtqcnt = offsetof(DTQINIB,dtqcnt);
const unsigned_t TOPPERS_cfg_offsetof_DTQINIB_p_dtqmb = offsetof(DTQINIB,p_dtqmb);
const unsigned_t TOPPERS_cfg_sizeof_PDQINIB = sizeof(PDQINIB);
const unsigned_t TOPPERS_cfg_offsetof_PDQINIB_pdqatr = offsetof(PDQINIB,pdqatr);
const unsigned_t TOPPERS_cfg_offsetof_PDQINIB_pdqcnt = offsetof(PDQINIB,pdqcnt);
const unsigned_t TOPPERS_cfg_offsetof_PDQINIB_maxdpri = offsetof(PDQINIB,maxdpri);
const unsigned_t TOPPERS_cfg_offsetof_PDQINIB_p_pdqmb = offsetof(PDQINIB,p_pdqmb);
const unsigned_t TOPPERS_cfg_sizeof_MBXINIB = sizeof(MBXINIB);
const unsigned_t TOPPERS_cfg_offsetof_MBXINIB_mbxatr = offsetof(MBXINIB,mbxatr);
const unsigned_t TOPPERS_cfg_offsetof_MBXINIB_maxmpri = offsetof(MBXINIB,maxmpri);
const unsigned_t TOPPERS_cfg_sizeof_MPFINIB = sizeof(MPFINIB);
const unsigned_t TOPPERS_cfg_offsetof_MPFINIB_mpfatr = offsetof(MPFINIB,mpfatr);
const unsigned_t TOPPERS_cfg_offsetof_MPFINIB_blkcnt = offsetof(MPFINIB,blkcnt);
const unsigned_t TOPPERS_cfg_offsetof_MPFINIB_blksz = offsetof(MPFINIB,blksz);
const unsigned_t TOPPERS_cfg_offsetof_MPFINIB_mpf = offsetof(MPFINIB,mpf);
const unsigned_t TOPPERS_cfg_offsetof_MPFINIB_p_mpfmb = offsetof(MPFINIB,p_mpfmb);
const unsigned_t TOPPERS_cfg_sizeof_CYCINIB = sizeof(CYCINIB);
const unsigned_t TOPPERS_cfg_offsetof_CYCINIB_cycatr = offsetof(CYCINIB,cycatr);
const unsigned_t TOPPERS_cfg_offsetof_CYCINIB_exinf = offsetof(CYCINIB,exinf);
const unsigned_t TOPPERS_cfg_offsetof_CYCINIB_cychdr = offsetof(CYCINIB,cychdr);
const unsigned_t TOPPERS_cfg_offsetof_CYCINIB_cyctim = offsetof(CYCINIB,cyctim);
const unsigned_t TOPPERS_cfg_offsetof_CYCINIB_cycphs = offsetof(CYCINIB,cycphs);
const unsigned_t TOPPERS_cfg_sizeof_ALMINIB = sizeof(ALMINIB);
const unsigned_t TOPPERS_cfg_offsetof_ALMINIB_almatr = offsetof(ALMINIB,almatr);
const unsigned_t TOPPERS_cfg_offsetof_ALMINIB_exinf = offsetof(ALMINIB,exinf);
const unsigned_t TOPPERS_cfg_offsetof_ALMINIB_almhdr = offsetof(ALMINIB,almhdr);
const unsigned_t TOPPERS_cfg_sizeof_INHNO = sizeof(INHNO);
const unsigned_t TOPPERS_cfg_sizeof_INTNO = sizeof(INTNO);
const unsigned_t TOPPERS_cfg_sizeof_EXCNO = sizeof(EXCNO);
const unsigned_t TOPPERS_cfg_TA_LOWLEVEL = TA_LOWLEVEL;
const unsigned_t TOPPERS_cfg_TA_BOTHEDGE = TA_BOTHEDGE;
const unsigned_t TOPPERS_cfg_TA_NEGEDGE = TA_NEGEDGE;
const signed_t TOPPERS_cfg_TIPM_LOCK = TIPM_LOCK;
const unsigned_t TOPPERS_cfg_IPL_LOCK = IPL_LOCK;
const unsigned_t TOPPERS_cfg_PSW_I_MASK = PSW_I_MASK;
const unsigned_t TOPPERS_cfg_PSW_IPL_MASK = PSW_IPL_MASK;
const unsigned_t TOPPERS_cfg_EXC_GET_PSW_OFFSET = EXC_GET_PSW_OFFSET;
const unsigned_t TOPPERS_cfg_LOG_DSP_ENTER = LOG_DSP_ENTER;
const unsigned_t TOPPERS_cfg_LOG_DSP_LEAVE = LOG_DSP_LEAVE;
const unsigned_t TOPPERS_cfg_LOG_INH_ENTER = LOG_INH_ENTER;
const unsigned_t TOPPERS_cfg_LOG_INH_LEAVE = LOG_INH_LEAVE;
const unsigned_t TOPPERS_cfg_LOG_EXC_ENTER = LOG_EXC_ENTER;
const unsigned_t TOPPERS_cfg_LOG_EXC_LEAVE = LOG_EXC_LEAVE;
const unsigned_t TOPPERS_cfg_SIL_DLY_TIM1 = SIL_DLY_TIM1;
const unsigned_t TOPPERS_cfg_SIL_DLY_TIM2 = SIL_DLY_TIM2;
