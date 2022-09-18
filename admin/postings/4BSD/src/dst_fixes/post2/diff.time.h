*** /nbsd/usr/src/include/time.h	Wed Mar 13 16:30:32 1985
--- /usr/src/include/time.h	Wed Mar 18 16:23:54 1987
***************
*** 1,4 ****
! /*	time.h	1.1	85/03/13	*/
  
  /*
   * Structure returned by gmtime and localtime calls (see ctime(3)).
--- 1,10 ----
! /*
!  * Copyright (c) 1983, 1987 Regents of the University of California.
!  * All rights reserved.  The Berkeley software License Agreement
!  * specifies the terms and conditions for redistribution.
!  *
!  *	@(#)time.h	1.2 (Berkeley) 3/4/87
!  */
  
  /*
   * Structure returned by gmtime and localtime calls (see ctime(3)).
***************
*** 13,18 ****
--- 19,26 ----
  	int	tm_wday;
  	int	tm_yday;
  	int	tm_isdst;
+ 	long	tm_gmtoff;
+ 	char	*tm_zone;
  };
  
  extern	struct tm *gmtime(), *localtime();
