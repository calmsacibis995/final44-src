*** kern_time.c	Wed Mar 25 18:01:40 1987
--- /sys/sys/kern_time.c	Mon Mar 23 17:46:20 1987
***************
*** 3,13 ****
   * All rights reserved.  The Berkeley software License Agreement
   * specifies the terms and conditions for redistribution.
   *
!  *	@(#)kern_time.c	7.1 (Berkeley) 6/5/86
   */
  
- #include "../machine/reg.h"
- 
  #include "param.h"
  #include "dir.h"		/* XXX */
  #include "user.h"
--- 3,11 ----
   * All rights reserved.  The Berkeley software License Agreement
   * specifies the terms and conditions for redistribution.
   *
!  *	@(#)kern_time.c	7.4 (Berkeley) 3/23/87
   */
  
  #include "param.h"
  #include "dir.h"		/* XXX */
  #include "user.h"
***************
*** 15,20 ****
--- 13,21 ----
  #include "inode.h"
  #include "proc.h"
  
+ #include "../machine/reg.h"
+ #include "../machine/cpu.h"
+ 
  /* 
   * Time of day and interval timer support.
   *
***************
*** 33,46 ****
  	} *uap = (struct a *)u.u_ap;
  	struct timeval atv;
  
! 	microtime(&atv);
! 	u.u_error = copyout((caddr_t)&atv, (caddr_t)uap->tp, sizeof (atv));
! 	if (u.u_error)
! 		return;
! 	if (uap->tzp == 0)
! 		return;
! 	/* SHOULD HAVE PER-PROCESS TIMEZONE */
! 	u.u_error = copyout((caddr_t)&tz, (caddr_t)uap->tzp, sizeof (tz));
  }
  
  settimeofday()
--- 34,49 ----
  	} *uap = (struct a *)u.u_ap;
  	struct timeval atv;
  
! 	if (uap->tp) {
! 		microtime(&atv);
! 		u.u_error = copyout((caddr_t)&atv, (caddr_t)uap->tp,
! 			sizeof (atv));
! 		if (u.u_error)
! 			return;
! 	}
! 	if (uap->tzp)
! 		u.u_error = copyout((caddr_t)&tz, (caddr_t)uap->tzp,
! 			sizeof (tz));
  }
  
  settimeofday()
***************
*** 52,62 ****
  	struct timeval atv;
  	struct timezone atz;
  
! 	u.u_error = copyin((caddr_t)uap->tv, (caddr_t)&atv,
! 		sizeof (struct timeval));
! 	if (u.u_error)
! 		return;
! 	setthetime(&atv);
  	if (uap->tzp && suser()) {
  		u.u_error = copyin((caddr_t)uap->tzp, (caddr_t)&atz,
  			sizeof (atz));
--- 55,67 ----
  	struct timeval atv;
  	struct timezone atz;
  
! 	if (uap->tv) {
! 		u.u_error = copyin((caddr_t)uap->tv, (caddr_t)&atv,
! 			sizeof (struct timeval));
! 		if (u.u_error)
! 			return;
! 		setthetime(&atv);
! 	}
  	if (uap->tzp && suser()) {
  		u.u_error = copyin((caddr_t)uap->tzp, (caddr_t)&atz,
  			sizeof (atz));
***************
*** 174,180 ****
  	splx(s);
  	u.u_error = copyout((caddr_t)&aitv, (caddr_t)uap->itv,
  	    sizeof (struct itimerval));
- 	splx(s);
  }
  
  setitimer()
--- 179,184 ----
