/* Copyright (C) 1991-2019 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.
   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.
   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

#include <nautilus/nautilus.h>
#include <compat/linux/sysconf.h>
#include <nautilus/shell.h>
#define ERROR(fmt, args...) ERROR_PRINT("sysconf: " fmt, ##args)

#define INFO(fmt, args...)   INFO_PRINT("sysconf: " fmt, ##args)


#define DEBUG(fmt, args...) DEBUG_PRINT("sysconf: " fmt, ##args)

#ifdef NAUT_CONFIG_OPENMP_RT_DEBUG
#undef DEBUG
#define DEBUG(fmt, args...) DEBUG_PRINT("sysconf: " fmt, ##args)
#endif

//#define _SC_EQUIV_CLASS_MAX -1

//#define _SC_THREADS 67
//#define _SC_THREAD_THREADS_MAX 76
//#define _SC_THREAD_STACK_MIN 75
//#define _SC_NPROCESSORS_ONLN 80
static long avaiable_cores = -1;

long nk_get_avaible_cores(){
   if (avaiable_cores < 0)
    return (long) nk_get_num_cpus();
   else return  avaiable_cores;
}


static int handle_omp_num_threads(char* buf, void* priv);

static struct shell_cmd_impl omp_num_threads_impl = {
    .cmd      = "omp_num_threads",
    .help_str = "set omp number of threads",
    .handler  = handle_omp_num_threads,
};
nk_register_shell_cmd(omp_num_threads_impl);


static int handle_omp_num_threads(char* buf, void* priv){

    long cores;
    if((sscanf(buf, "omp_num_threads %d", &cores) !=1))	{
      nk_vc_printf("Don't understand %s please input single number\n", buf);
      return -1;
    }
    avaiable_cores = cores;
    return 0;

}


long int
__sysconf (int name)
{

  //DEBUG("name %d\n", name);
  switch (name)
    {
      
      /* Also add obsolete or unnecessarily added constants here.  */
    case _SC_THREADS:
 DEBUG("_SC_THREADS %d\n", name);
      return 0x31069;
    case _SC_THREAD_THREADS_MAX:
 DEBUG("_sc_thread_threads_max %d\n", name);
      return 0x1000;
    case _SC_THREAD_STACK_MIN:
   DEBUG("sc_thread_stack_min %d\n", name);    
      return 0x4000;
    case _SC_NPROCESSORS_ONLN:
   DEBUG("sc_nprocessors_onln \n");
      return (long) nk_get_avaible_cores();
//    case 84:
      //important to set default number of threads
//      DEBUG("unknown but possibly related to number of cpu %d\n", name);    
//      return (long) nk_get_num_cpus();
     case 30:
     return 4096; 
     break;
    default:
      DEBUG("name %0x\n", name);
      return 0;


/*     case _SC_ARG_MAX: */
/* #ifdef        ARG_MAX */
/*       return ARG_MAX; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_CHILD_MAX: */
/* #ifdef        CHILD_MAX */
/*       return CHILD_MAX; */
/* #else */
/*       return __get_child_max (); */
/* #endif */
/*     case _SC_CLK_TCK: */
/*       return __getclktck (); */
/*     case _SC_NGROUPS_MAX: */
/* #ifdef        NGROUPS_MAX */
/*       return NGROUPS_MAX; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_OPEN_MAX: */
/*       return __getdtablesize (); */
/*     case _SC_STREAM_MAX: */
/* #ifdef        STREAM_MAX */
/*       return STREAM_MAX; */
/* #else */
/*       return FOPEN_MAX; */
/* #endif */
/*     case _SC_TZNAME_MAX: */
/*       return -1; */
/*     case _SC_JOB_CONTROL: */
/* #if CONF_IS_DEFINED_SET (_POSIX_JOB_CONTROL) */
/*       return _POSIX_JOB_CONTROL; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_SAVED_IDS: */
/* #if CONF_IS_DEFINED_SET (_POSIX_SAVED_IDS) */
/*       return 1; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_REALTIME_SIGNALS: */
/* #if CONF_IS_DEFINED_SET (_POSIX_REALTIME_SIGNALS) */
/*       return _POSIX_REALTIME_SIGNALS; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_PRIORITY_SCHEDULING: */
/* #if CONF_IS_DEFINED_SET (_POSIX_PRIORITY_SCHEDULING) */
/*       return _POSIX_PRIORITY_SCHEDULING; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_TIMERS: */
/* #if CONF_IS_DEFINED_SET (_POSIX_TIMERS) */
/*       return _POSIX_TIMERS; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_ASYNCHRONOUS_IO: */
/* #if CONF_IS_DEFINED_SET (_POSIX_ASYNCHRONOUS_IO) */
/*       return _POSIX_ASYNCHRONOUS_IO; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_PRIORITIZED_IO: */
/* #if CONF_IS_DEFINED_SET (_POSIX_PRIORITIZED_IO) */
/*       return _POSIX_PRIORITIZED_IO; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_SYNCHRONIZED_IO: */
/* #if CONF_IS_DEFINED_SET (_POSIX_SYNCHRONIZED_IO) */
/*       return _POSIX_SYNCHRONIZED_IO; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_FSYNC: */
/* #if CONF_IS_DEFINED_SET (_POSIX_FSYNC) */
/*       return _POSIX_FSYNC; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_MAPPED_FILES: */
/* #if CONF_IS_DEFINED_SET (_POSIX_MAPPED_FILES) */
/*       return _POSIX_MAPPED_FILES; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_MEMLOCK: */
/* #if CONF_IS_DEFINED_SET (_POSIX_MEMLOCK) */
/*       return _POSIX_MEMLOCK; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_MEMLOCK_RANGE: */
/* #if CONF_IS_DEFINED_SET (_POSIX_MEMLOCK_RANGE) */
/*       return _POSIX_MEMLOCK_RANGE; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_MEMORY_PROTECTION: */
/* #if CONF_IS_DEFINED_SET (_POSIX_MEMORY_PROTECTION) */
/*       return _POSIX_MEMORY_PROTECTION; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_MESSAGE_PASSING: */
/* #if CONF_IS_DEFINED_SET (_POSIX_MESSAGE_PASSING) */
/*       return _POSIX_MESSAGE_PASSING; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_SEMAPHORES: */
/* #if CONF_IS_DEFINED_SET (_POSIX_SEMAPHORES) */
/*       return _POSIX_SEMAPHORES; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_SHARED_MEMORY_OBJECTS: */
/* #if CONF_IS_DEFINED_SET (_POSIX_SHARED_MEMORY_OBJECTS) */
/*       return _POSIX_SHARED_MEMORY_OBJECTS; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_VERSION: */
/*       return _POSIX_VERSION; */
/*     case _SC_PAGESIZE: */
/*       return __getpagesize (); */
/*     case _SC_AIO_LISTIO_MAX: */
/* #ifdef        AIO_LISTIO_MAX */
/*       return AIO_LISTIO_MAX; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_AIO_MAX: */
/* #ifdef        AIO_MAX */
/*       return AIO_MAX; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_AIO_PRIO_DELTA_MAX: */
/* #ifdef        AIO_PRIO_DELTA_MAX */
/*       return AIO_PRIO_DELTA_MAX; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_DELAYTIMER_MAX: */
/* #ifdef        DELAYTIMER_MAX */
/*       return DELAYTIMER_MAX; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_MQ_OPEN_MAX: */
/* #ifdef        MQ_OPEN_MAX */
/*       return MQ_OPEN_MAX; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_MQ_PRIO_MAX: */
/* #ifdef        MQ_PRIO_MAX */
/*       return MQ_PRIO_MAX; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_RTSIG_MAX: */
/* #ifdef        RTSIG_MAX */
/*       return RTSIG_MAX; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_SEM_NSEMS_MAX: */
/* #ifdef        SEM_NSEMS_MAX */
/*       return SEM_NSEMS_MAX; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_SEM_VALUE_MAX: */
/* #ifdef        SEM_VALUE_MAX */
/*       return SEM_VALUE_MAX; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_SIGQUEUE_MAX: */
/* #ifdef        SIGQUEUE_MAX */
/*       return SIGQUEUE_MAX; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_TIMER_MAX: */
/* #ifdef        TIMER_MAX */
/*       return TIMER_MAX; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_BC_BASE_MAX: */
/* #ifdef        BC_BASE_MAX */
/*       return BC_BASE_MAX; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_BC_DIM_MAX: */
/* #ifdef        BC_DIM_MAX */
/*       return BC_DIM_MAX; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_BC_SCALE_MAX: */
/* #ifdef        BC_SCALE_MAX */
/*       return BC_SCALE_MAX; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_BC_STRING_MAX: */
/* #ifdef        BC_STRING_MAX */
/*       return BC_STRING_MAX; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_COLL_WEIGHTS_MAX: */
/* #ifdef        COLL_WEIGHTS_MAX */
/*       return COLL_WEIGHTS_MAX; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_EXPR_NEST_MAX: */
/* #ifdef        EXPR_NEST_MAX */
/*       return EXPR_NEST_MAX; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_LINE_MAX: */
/* #ifdef        LINE_MAX */
/*       return LINE_MAX; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_RE_DUP_MAX: */
/* #ifdef        RE_DUP_MAX */
/*       return RE_DUP_MAX; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_CHARCLASS_NAME_MAX: */
/* #ifdef        CHARCLASS_NAME_MAX */
/*       return CHARCLASS_NAME_MAX; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_PII: */
/* #if CONF_IS_DEFINED_SET (_POSIX_PII) */
/*       return 1; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_PII_XTI: */
/* #if CONF_IS_DEFINED_SET (_POSIX_PII_XTI) */
/*       return 1; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_PII_SOCKET: */
/* #if CONF_IS_DEFINED_SET (_POSIX_PII_SOCKET) */
/*       return 1; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_PII_INTERNET: */
/* #if CONF_IS_DEFINED_SET (_POSIX_PII_INTERNET) */
/*       return 1; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_PII_OSI: */
/* #if CONF_IS_DEFINED_SET (_POSIX_PII_OSI) */
/*       return 1; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_POLL: */
/* #if CONF_IS_DEFINED_SET (_POSIX_POLL) */
/*       return 1; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_SELECT: */
/* #if CONF_IS_DEFINED_SET (_POSIX_SELECT) */
/*       return 1; */
/* #else */
/*       return -1; */
/* #endif */
/*       /\* The same as _SC_IOV_MAX.  *\/ */
/*     case _SC_UIO_MAXIOV: */
/* #ifdef        UIO_MAXIOV */
/*       return UIO_MAXIOV; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_PII_INTERNET_STREAM: */
/* #if CONF_IS_DEFINED_SET (_POSIX_PII_INTERNET_STREAM) */
/*       return 1; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_PII_INTERNET_DGRAM: */
/* #if CONF_IS_DEFINED_SET (_POSIX_PII_INTERNET_DGRAM) */
/*       return 1; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_PII_OSI_COTS: */
/* #if CONF_IS_DEFINED_SET (_POSIX_PII_OSI_COTS) */
/*       return 1; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_PII_OSI_CLTS: */
/* #if CONF_IS_DEFINED_SET (_POSIX_PII_OSI_CLTS) */
/*       return 1; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_PII_OSI_M: */
/* #if CONF_IS_DEFINED_SET (_POSIX_PII_OSI_M) */
/*       return 1; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_T_IOV_MAX: */
/* #ifdef        _T_IOV_MAX */
/*       return _T_IOV_MAX; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_2_VERSION: */
/*       return _POSIX2_VERSION; */
/*     case _SC_2_C_BIND: */
/* #ifdef        _POSIX2_C_BIND */
/*       return _POSIX2_C_BIND; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_2_C_DEV: */
/* #ifdef        _POSIX2_C_DEV */
/*       return _POSIX2_C_DEV; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_2_C_VERSION: */
/* #ifdef        _POSIX2_C_VERSION */
/*       return _POSIX2_C_VERSION; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_2_FORT_DEV: */
/* #ifdef        _POSIX2_FORT_DEV */
/*       return _POSIX2_FORT_DEV; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_2_FORT_RUN: */
/* #ifdef        _POSIX2_FORT_RUN */
/*       return _POSIX2_FORT_RUN; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_2_LOCALEDEF: */
/* #ifdef        _POSIX2_LOCALEDEF */
/*       return _POSIX2_LOCALEDEF; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_2_SW_DEV: */
/* #ifdef        _POSIX2_SW_DEV */
/*       return _POSIX2_SW_DEV; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_2_CHAR_TERM: */
/* #ifdef        _POSIX2_CHAR_TERM */
/*       return _POSIX2_CHAR_TERM; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_2_UPE: */
/* #ifdef        _POSIX2_UPE */
/*       return _POSIX2_UPE; */
/* #else */
/*       return -1; */
/* #endif */
/*       /\* POSIX 1003.1c (POSIX Threads).  *\/ */
/*     case _SC_THREADS: */
/* #if CONF_IS_DEFINED_SET (_POSIX_THREADS) */
/*       return _POSIX_THREADS; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_THREAD_SAFE_FUNCTIONS: */
/* #if CONF_IS_DEFINED_SET (_POSIX_THREAD_SAFE_FUNCTIONS) */
/*       return _POSIX_THREAD_SAFE_FUNCTIONS; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_GETGR_R_SIZE_MAX: */
/*       return NSS_BUFLEN_GROUP; */
/*     case _SC_GETPW_R_SIZE_MAX: */
/*       return NSS_BUFLEN_PASSWD; */
/*     case _SC_LOGIN_NAME_MAX: */
/* #ifdef        LOGIN_NAME_MAX */
/*       return LOGIN_NAME_MAX; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_TTY_NAME_MAX: */
/* #ifdef        TTY_NAME_MAX */
/*       return TTY_NAME_MAX; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_THREAD_DESTRUCTOR_ITERATIONS: */
/* #if CONF_IS_DEFINED_SET (_POSIX_THREAD_DESTRUCTOR_ITERATIONS) */
/*       return _POSIX_THREAD_DESTRUCTOR_ITERATIONS; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_THREAD_KEYS_MAX: */
/* #ifdef        PTHREAD_KEYS_MAX */
/*       return PTHREAD_KEYS_MAX; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_THREAD_STACK_MIN: */
/* #ifdef        PTHREAD_STACK_MIN */
/*       return PTHREAD_STACK_MIN; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_THREAD_THREADS_MAX: */
/* #ifdef        PTHREAD_THREADS_MAX */
/*       return PTHREAD_THREADS_MAX; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_THREAD_ATTR_STACKADDR: */
/* #if CONF_IS_DEFINED_SET (_POSIX_THREAD_ATTR_STACKADDR) */
/*       return _POSIX_THREAD_ATTR_STACKADDR; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_THREAD_ATTR_STACKSIZE: */
/* #if CONF_IS_DEFINED_SET (_POSIX_THREAD_ATTR_STACKSIZE) */
/*       return _POSIX_THREAD_ATTR_STACKSIZE; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_THREAD_PRIORITY_SCHEDULING: */
/* #if CONF_IS_DEFINED_SET (_POSIX_THREAD_PRIORITY_SCHEDULING) */
/*       return _POSIX_THREAD_PRIORITY_SCHEDULING; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_THREAD_PRIO_INHERIT: */
/* #if CONF_IS_DEFINED_SET (_POSIX_THREAD_PRIO_INHERIT) */
/*       return _POSIX_THREAD_PRIO_INHERIT; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_THREAD_PRIO_PROTECT: */
/* #if CONF_IS_DEFINED_SET (_POSIX_THREAD_PRIO_PROTECT) */
/*       return _POSIX_THREAD_PRIO_PROTECT; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_THREAD_PROCESS_SHARED: */
/* #if CONF_IS_DEFINED_SET (_POSIX_THREAD_PROCESS_SHARED) */
/*       return _POSIX_THREAD_PROCESS_SHARED; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_NPROCESSORS_CONF: */
/*       return __get_nprocs_conf (); */
/*     case _SC_NPROCESSORS_ONLN: */
/*       return __get_nprocs (); */
/*     case _SC_PHYS_PAGES: */
/*       return __get_phys_pages (); */
/*     case _SC_AVPHYS_PAGES: */
/*       return __get_avphys_pages (); */
/*     case _SC_ATEXIT_MAX: */
/*       /\* We have no limit since we use lists.  *\/ */
/*       return INT_MAX; */
/*     case _SC_PASS_MAX: */
/*       /\* We have no limit but since the return value might be used to */
/*          allocate a buffer we restrict the value.  *\/ */
/*       return BUFSIZ; */
/*     case _SC_XOPEN_VERSION: */
/*       return _XOPEN_VERSION; */
/*     case _SC_XOPEN_XCU_VERSION: */
/*       return _XOPEN_XCU_VERSION; */
/*     case _SC_XOPEN_UNIX: */
/*       return _XOPEN_UNIX; */
/*     case _SC_XOPEN_CRYPT: */
/* #ifdef        _XOPEN_CRYPT */
/*       return _XOPEN_CRYPT; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_XOPEN_ENH_I18N: */
/* #ifdef        _XOPEN_ENH_I18N */
/*       return _XOPEN_ENH_I18N; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_XOPEN_SHM: */
/* #ifdef        _XOPEN_SHM */
/*       return _XOPEN_SHM; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_XOPEN_XPG2: */
/* #ifdef        _XOPEN_XPG2 */
/*       return _XOPEN_XPG2; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_XOPEN_XPG3: */
/* #ifdef        _XOPEN_XPG3 */
/*       return _XOPEN_XPG3; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_XOPEN_XPG4: */
/* #ifdef        _XOPEN_XPG4 */
/*       return _XOPEN_XPG4; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_CHAR_BIT: */
/*       return CHAR_BIT; */
/*     case _SC_CHAR_MAX: */
/*       return CHAR_MAX; */
/*     case _SC_CHAR_MIN: */
/*       return CHAR_MIN; */
/*     case _SC_INT_MAX: */
/*       return INT_MAX; */
/*     case _SC_INT_MIN: */
/*       return INT_MIN; */
/*     case _SC_LONG_BIT: */
/*       return sizeof (long int) * CHAR_BIT; */
/*     case _SC_WORD_BIT: */
/*       return sizeof (int) * CHAR_BIT; */
/*     case _SC_MB_LEN_MAX: */
/*       return MB_LEN_MAX; */
/*     case _SC_NZERO: */
/*       return NZERO; */
/*     case _SC_SSIZE_MAX: */
/*       return _POSIX_SSIZE_MAX; */
/*     case _SC_SCHAR_MAX: */
/*       return SCHAR_MAX; */
/*     case _SC_SCHAR_MIN: */
/*       return SCHAR_MIN; */
/*     case _SC_SHRT_MAX: */
/*       return SHRT_MAX; */
/*     case _SC_SHRT_MIN: */
/*       return SHRT_MIN; */
/*     case _SC_UCHAR_MAX: */
/*       return UCHAR_MAX; */
/*     case _SC_UINT_MAX: */
/*       return UINT_MAX; */
/*     case _SC_ULONG_MAX: */
/*       return ULONG_MAX; */
/*     case _SC_USHRT_MAX: */
/*       return USHRT_MAX; */
/*     case _SC_NL_ARGMAX: */
/* #ifdef        NL_ARGMAX */
/*       return NL_ARGMAX; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_NL_LANGMAX: */
/* #ifdef        NL_LANGMAX */
/*       return NL_LANGMAX; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_NL_MSGMAX: */
/* #ifdef        NL_MSGMAX */
/*       return NL_MSGMAX; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_NL_NMAX: */
/* #ifdef        NL_NMAX */
/*       return NL_NMAX; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_NL_SETMAX: */
/* #ifdef        NL_SETMAX */
/*       return NL_SETMAX; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_NL_TEXTMAX: */
/* #ifdef        NL_TEXTMAX */
/*       return NL_TEXTMAX; */
/* #else */
/*       return -1; */
/* #endif */
/* #define START_ENV_GROUP(VERSION)                \ */
/*       /\* Empty.  *\/ */
/* #define END_ENV_GROUP(VERSION)                        \ */
/*       /\* Empty.  *\/ */
/* #define KNOWN_ABSENT_ENVIRONMENT(SC_PREFIX, ENV_PREFIX, SUFFIX)        \ */
/*     case _SC_##SC_PREFIX##_##SUFFIX:                                \ */
/*       return _##ENV_PREFIX##_##SUFFIX; */
/* #define KNOWN_PRESENT_ENVIRONMENT(SC_PREFIX, ENV_PREFIX, SUFFIX)        \ */
/*     case _SC_##SC_PREFIX##_##SUFFIX:                                        \ */
/*       return _##ENV_PREFIX##_##SUFFIX; */
/* #define UNKNOWN_ENVIRONMENT(SC_PREFIX, ENV_PREFIX, SUFFIX)        \ */
/*     case _SC_##SC_PREFIX##_##SUFFIX:                                \ */
/*       return __sysconf_check_spec (#SUFFIX); */
/* #include <posix/posix-envs.def> */
/* #undef START_ENV_GROUP */
/* #undef END_ENV_GROUP */
/* #undef KNOWN_ABSENT_ENVIRONMENT */
/* #undef KNOWN_PRESENT_ENVIRONMENT */
/* #undef UNKNOWN_ENVIRONMENT */
/*     case _SC_XOPEN_LEGACY: */
/*       return _XOPEN_LEGACY; */
/*     case _SC_XOPEN_REALTIME: */
/* #ifdef _XOPEN_REALTIME */
/*       return _XOPEN_REALTIME; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_XOPEN_REALTIME_THREADS: */
/* #ifdef _XOPEN_REALTIME_THREADS */
/*       return _XOPEN_REALTIME_THREADS; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_ADVISORY_INFO: */
/* #if CONF_IS_DEFINED_SET (_POSIX_ADVISORY_INFO) */
/*       return _POSIX_ADVISORY_INFO; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_BARRIERS: */
/* #if CONF_IS_DEFINED_SET (_POSIX_BARRIERS) */
/*       return _POSIX_BARRIERS; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_BASE: */
/* #if CONF_IS_DEFINED_SET (_POSIX_BASE) */
/*       return _POSIX_BASE; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_C_LANG_SUPPORT: */
/* #if CONF_IS_DEFINED_SET (_POSIX_C_LANG_SUPPORT) */
/*       return _POSIX_C_LANG_SUPPORT; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_C_LANG_SUPPORT_R: */
/* #if CONF_IS_DEFINED_SET (_POSIX_C_LANG_SUPPORT_R) */
/*       return _POSIX_C_LANG_SUPPORT_R; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_CLOCK_SELECTION: */
/* #if CONF_IS_DEFINED_SET (_POSIX_CLOCK_SELECTION) */
/*       return _POSIX_CLOCK_SELECTION; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_CPUTIME: */
/* #if CONF_IS_DEFINED_SET (_POSIX_CPUTIME) */
/*       return _POSIX_CPUTIME; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_DEVICE_IO: */
/* #if CONF_IS_DEFINED_SET (_POSIX_DEVICE_IO) */
/*       return _POSIX_DEVICE_IO; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_DEVICE_SPECIFIC: */
/* #if CONF_IS_DEFINED_SET (_POSIX_DEVICE_SPECIFIC) */
/*       return _POSIX_DEVICE_SPECIFIC; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_DEVICE_SPECIFIC_R: */
/* #if CONF_IS_DEFINED_SET (_POSIX_DEVICE_SPECIFIC_R) */
/*       return _POSIX_DEVICE_SPECIFIC_R; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_FD_MGMT: */
/* #if CONF_IS_DEFINED_SET (_POSIX_FD_MGMT) */
/*       return _POSIX_FD_MGMT; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_FIFO: */
/* #if CONF_IS_DEFINED_SET (_POSIX_FIFO) */
/*       return _POSIX_FIFO; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_PIPE: */
/* #if CONF_IS_DEFINED_SET (_POSIX_PIPE) */
/*       return _POSIX_PIPE; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_FILE_ATTRIBUTES: */
/* #if CONF_IS_DEFINED_SET (_POSIX_FILE_ATTRIBUTES) */
/*       return _POSIX_FILE_ATTRIBUTES; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_FILE_LOCKING: */
/* #if CONF_IS_DEFINED_SET (_POSIX_FILE_LOCKING) */
/*       return _POSIX_FILE_LOCKING; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_FILE_SYSTEM: */
/* #if CONF_IS_DEFINED_SET (_POSIX_FILE_SYSTEM) */
/*       return _POSIX_FILE_SYSTEM; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_MONOTONIC_CLOCK: */
/* #if CONF_IS_DEFINED_SET (_POSIX_MONOTONIC_CLOCK) */
/*       return _POSIX_MONOTONIC_CLOCK; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_MULTI_PROCESS: */
/* #if CONF_IS_DEFINED_SET (_POSIX_MULTI_PROCESS) */
/*       return _POSIX_MULTI_PROCESS; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_SINGLE_PROCESS: */
/* #if CONF_IS_DEFINED_SET (_POSIX_SINGLE_PROCESS) */
/*       return _POSIX_SINGLE_PROCESS; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_NETWORKING: */
/* #if CONF_IS_DEFINED_SET (_POSIX_NETWORKING) */
/*       return _POSIX_NETWORKING; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_READER_WRITER_LOCKS: */
/* #if CONF_IS_DEFINED_SET (_POSIX_READER_WRITER_LOCKS) */
/*       return _POSIX_READER_WRITER_LOCKS; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_SPIN_LOCKS: */
/* #if CONF_IS_DEFINED_SET (_POSIX_SPIN_LOCKS) */
/*       return _POSIX_SPIN_LOCKS; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_REGEXP: */
/* #if CONF_IS_DEFINED_SET (_POSIX_REGEXP) */
/*       return _POSIX_REGEXP; */
/* #else */
/*       return -1; */
/* #endif */
/*     /\* _REGEX_VERSION has been removed with IEEE Std 1003.1-2001/Cor 2-2004, */
/*        item XSH/TC2/D6/137.  *\/ */
/*     case _SC_REGEX_VERSION: */
/*       return -1; */
/*     case _SC_SHELL: */
/* #if CONF_IS_DEFINED_SET (_POSIX_SHELL) */
/*       return _POSIX_SHELL; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_SIGNALS: */
/* #if CONF_IS_DEFINED (_POSIX_SIGNALS) */
/*       return _POSIX_SIGNALS; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_SPAWN: */
/* #if CONF_IS_DEFINED_SET (_POSIX_SPAWN) */
/*       return _POSIX_SPAWN; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_SPORADIC_SERVER: */
/* #if CONF_IS_DEFINED_SET (_POSIX_SPORADIC_SERVER) */
/*       return _POSIX_SPORADIC_SERVER; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_THREAD_SPORADIC_SERVER: */
/* #if CONF_IS_DEFINED_SET (_POSIX_THREAD_SPORADIC_SERVER) */
/*       return _POSIX_THREAD_SPORADIC_SERVER; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_SYSTEM_DATABASE: */
/* #if CONF_IS_DEFINED_SET (_POSIX_SYSTEM_DATABASE) */
/*       return _POSIX_SYSTEM_DATABASE; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_SYSTEM_DATABASE_R: */
/* #if CONF_IS_DEFINED_SET (_POSIX_SYSTEM_DATABASE_R) */
/*       return _POSIX_SYSTEM_DATABASE_R; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_THREAD_CPUTIME: */
/* #if CONF_IS_DEFINED_SET (_POSIX_THREAD_CPUTIME) */
/*       return _POSIX_THREAD_CPUTIME; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_TIMEOUTS: */
/* #if CONF_IS_DEFINED_SET (_POSIX_TIMEOUTS) */
/*       return _POSIX_TIMEOUTS; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_TYPED_MEMORY_OBJECTS: */
/* #if CONF_IS_DEFINED_SET (_POSIX_TYPED_MEMORY_OBJECTS) */
/*       return _POSIX_TYPED_MEMORY_OBJECTS; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_USER_GROUPS: */
/* #if CONF_IS_DEFINED_SET (_POSIX_USER_GROUPS) */
/*       return _POSIX_USER_GROUPS; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_USER_GROUPS_R: */
/* #if CONF_IS_DEFINED_SET (_POSIX_USER_GROUPS_R) */
/*       return _POSIX_USER_GROUPS_R; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_2_PBS: */
/* #ifdef _POSIX2_PBS */
/*       return _POSIX2_PBS; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_2_PBS_ACCOUNTING: */
/* #ifdef _POSIX2_PBS_ACCOUNTING */
/*       return _POSIX2_PBS_ACCOUNTING; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_2_PBS_CHECKPOINT: */
/* #ifdef _POSIX2_PBS_CHECKPOINT */
/*       return _POSIX2_PBS_CHECKPOINT; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_2_PBS_LOCATE: */
/* #ifdef _POSIX2_PBS_LOCATE */
/*       return _POSIX2_PBS_LOCATE; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_2_PBS_MESSAGE: */
/* #ifdef _POSIX2_PBS_MESSAGE */
/*       return _POSIX2_PBS_MESSAGE; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_2_PBS_TRACK: */
/* #ifdef _POSIX2_PBS_TRACK */
/*       return _POSIX2_PBS_TRACK; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_SYMLOOP_MAX: */
/* #ifdef SYMLOOP_MAX */
/*       return SYMLOOP_MAX; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_STREAMS: */
/*       return -1; */
/*     case _SC_HOST_NAME_MAX: */
/* #ifdef HOST_NAME_MAX */
/*       return HOST_NAME_MAX; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_TRACE: */
/* #if CONF_IS_DEFINED_SET (_POSIX_TRACE) */
/*       return _POSIX_TRACE; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_TRACE_EVENT_FILTER: */
/* #if CONF_IS_DEFINED_SET (_POSIX_TRACE_EVENT_FILTER) */
/*       return _POSIX_TRACE_EVENT_FILTER; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_TRACE_INHERIT: */
/* #if CONF_IS_DEFINED_SET (_POSIX_TRACE_INHERIT) */
/*       return _POSIX_TRACE_INHERIT; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_TRACE_LOG: */
/* #if CONF_IS_DEFINED_SET (_POSIX_TRACE_LOG) */
/*       return _POSIX_TRACE_LOG; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_TRACE_EVENT_NAME_MAX: */
/*     case _SC_TRACE_NAME_MAX: */
/*     case _SC_TRACE_SYS_MAX: */
/*     case _SC_TRACE_USER_EVENT_MAX: */
/*       /\* No support for tracing.  *\/ */
/*     case _SC_XOPEN_STREAMS: */
/*       /\* No support for STREAMS.  *\/ */
/*       return -1; */
/*     case _SC_LEVEL1_ICACHE_SIZE: */
/*     case _SC_LEVEL1_ICACHE_ASSOC: */
/*     case _SC_LEVEL1_ICACHE_LINESIZE: */
/*     case _SC_LEVEL1_DCACHE_SIZE: */
/*     case _SC_LEVEL1_DCACHE_ASSOC: */
/*     case _SC_LEVEL1_DCACHE_LINESIZE: */
/*     case _SC_LEVEL2_CACHE_SIZE: */
/*     case _SC_LEVEL2_CACHE_ASSOC: */
/*     case _SC_LEVEL2_CACHE_LINESIZE: */
/*     case _SC_LEVEL3_CACHE_SIZE: */
/*     case _SC_LEVEL3_CACHE_ASSOC: */
/*     case _SC_LEVEL3_CACHE_LINESIZE: */
/*     case _SC_LEVEL4_CACHE_SIZE: */
/*     case _SC_LEVEL4_CACHE_ASSOC: */
/*     case _SC_LEVEL4_CACHE_LINESIZE: */
/*       /\* In general we cannot determine these values.  Therefore we */
/*          return zero which indicates that no information is */
/*          available.  *\/ */
/*       return 0; */
/*     case _SC_IPV6: */
/* #if CONF_IS_DEFINED_SET (_POSIX_IPV6) */
/*       return _POSIX_IPV6; */
/* #else */
/*       return -1; */
/* #endif */
/*     case _SC_RAW_SOCKETS: */
/* #if CONF_IS_DEFINED_SET (_POSIX_RAW_SOCKETS) */
/*       return _POSIX_RAW_SOCKETS; */
/* #else */
/*       return -1; */
/* #endif */
    }
}
//#undef __sysconf
//weak_alias (__sysconf, sysconf)
//libc_hidden_def (__sysconf)
/* #if NEED_CHECK_SPEC */

/* static long int */
/* __sysconf_check_spec (const char *spec) */
/* { */
/*   int save_errno = errno; */
/*   const char *getconf_dir = __libc_secure_getenv ("GETCONF_DIR") ?: GETCONF_DIR; */
/*   size_t getconf_dirlen = strlen (getconf_dir); */
/*   size_t speclen = strlen (spec); */
/*   char name[getconf_dirlen + sizeof ("/POSIX_V6_") + speclen]; */
/*   memcpy (mempcpy (mempcpy (name, getconf_dir, getconf_dirlen), */
/*                    "/POSIX_V6_", sizeof ("/POSIX_V6_") - 1), */
/*           spec, speclen + 1); */
/*   struct stat64 st; */
/*   long int ret = __xstat64 (_STAT_VER, name, &st) >= 0 ? 1 : -1; */
/*   __set_errno (save_errno); */
/*   return ret; */
/* } */
/* #endif */


long sysconf(int name){
  //DEBUG("sysconf, %d",name);
  long conf = __sysconf(name);
  return conf;
}
