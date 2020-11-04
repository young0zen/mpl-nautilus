/*
 * pthread_cond_init.c
 *
 * Description:
 * This translation unit implements condition variables and their primitives.
 *
 *
 * --------------------------------------------------------------------------
 *
 *      Pthreads-embedded (PTE) - POSIX Threads Library for embedded systems
 *      Copyright(C) 2008 Jason Schmidlapp
 *
 *      Contact Email: jschmidlapp@users.sourceforge.net
 *
 *
 *      Based upon Pthreads-win32 - POSIX Threads Library for Win32
 *      Copyright(C) 1998 John E. Bossom
 *      Copyright(C) 1999,2005 Pthreads-win32 contributors
 *
 *      Contact Email: rpj@callisto.canberra.edu.au
 *
 *      The original list of contributors to the Pthreads-win32 project
 *      is contained in the file CONTRIBUTORS.ptw32 included with the
 *      source code distribution. The list can also be seen at the
 *      following World Wide Web location:
 *      http://sources.redhat.com/pthreads-win32/contributors.html
 *
 *      This library is free software; you can redistribute it and/or
 *      modify it under the terms of the GNU Lesser General Public
 *      License as published by the Free Software Foundation; either
 *      version 2 of the License, or (at your option) any later version.
 *
 *      This library is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *      Lesser General Public License for more details.
 *
 *      You should have received a copy of the GNU Lesser General Public
 *      License along with this library in the file COPYING.LIB;
 *      if not, write to the Free Software Foundation, Inc.,
 *      59 Temple Place - Suite 330, Boston, MA 02111-1307, USA
 */

/* #include <stdlib.h> */
#include <nautilus/nautilus.h>
#include "pthread.h"
#include "implement.h"


int
pthread_cond_init (pthread_cond_t * cond, const pthread_condattr_t * attr)
/*
 * ------------------------------------------------------
 * DOCPUBLIC
 *      This function initializes a condition variable.
 *
 * PARAMETERS
 *      cond
 *              pointer to an instance of pthread_cond_t
 *
 *      attr
 *              specifies optional creation attributes.
 *
 *
 * DESCRIPTION
 *      This function initializes a condition variable.
 *
 * RESULTS
 *              0               successfully created condition variable,
 *              EINVAL          'attr' is invalid,
 *              EAGAIN          insufficient resources (other than
 *                              memory,
 *              ENOMEM          insufficient memory,
 *              EBUSY           'cond' is already initialized,
 *
 * ------------------------------------------------------
 */
{
  NK_PROFILE_ENTRY();
  int result;
  pthread_cond_t cv = NULL;

  if (cond == NULL)
    {
      return EINVAL;
    }

  if ((attr != NULL && *attr != NULL) &&
      ((*attr)->pshared == PTHREAD_PROCESS_SHARED))
    {
      /*
       * Creating condition variable that can be shared between
       * processes.
       */
      result = ENOSYS;
      goto DONE;
    }

  cv = (pthread_cond_t) calloc (1, sizeof (*cv));
  memset(cv,0,1*sizeof(*cv));
  if (cv == NULL)
    {
      result = ENOMEM;
      goto DONE;
    }

  cv->nWaitersBlocked = 0;
  cv->nWaitersToUnblock = 0;
  cv->nWaitersGone = 0;

  if (sem_init (&(cv->semBlockLock), 0, 1) != 0)
    {
      result = errno;
      goto FAIL0;
    }

  if (sem_init (&(cv->semBlockQueue), 0, 0) != 0)
    {
      result = errno;
      goto FAIL1;
    }

  if ((result = pthread_mutex_init (&(cv->mtxUnblockLock), 0)) != 0)
    {
      goto FAIL2;
    }

  result = 0;

  goto DONE;

  /*
   * -------------
   * Failed...
   * -------------
   */
FAIL2:
  (void) sem_destroy (&(cv->semBlockQueue));

FAIL1:
  (void) sem_destroy (&(cv->semBlockLock));

FAIL0:
  free(cv);
  //(void) free (cv);
  cv = NULL;

DONE:
  if (0 == result)
    {

      pte_osMutexLock (pte_cond_list_lock);

      cv->next = NULL;
      cv->prev = pte_cond_list_tail;

      if (pte_cond_list_tail != NULL)
        {
          pte_cond_list_tail->next = cv;
        }

      pte_cond_list_tail = cv;

      if (pte_cond_list_head == NULL)
        {
          pte_cond_list_head = cv;
        }

      pte_osMutexUnlock(pte_cond_list_lock);
    }

  *cond = cv;

  NK_PROFILE_EXIT();
  return result;

}				/* pthread_cond_init */
