*** /nbsd/usr/src/usr.lib/sendmail/src/arpadate.c	Thu Jan  9 15:19:40 1986
--- /usr/src/usr.lib/sendmail/src/arpadate.c	Sun Mar 22 13:12:41 1987
***************
*** 9,15 ****
  */
  
  #ifndef lint
! static char	SccsId[] = "@(#)arpadate.c	5.4 (Berkeley) 1/9/86";
  #endif not lint
  
  # include "conf.h"
--- 9,15 ----
  */
  
  #ifndef lint
! static char	SccsId[] = "@(#)arpadate.c	5.5 (Berkeley) 3/18/87";
  #endif not lint
  
  # include "conf.h"
***************
*** 74,80 ****
  # else OLDTIME
  	struct timeb t;
  	extern struct timeb *ftime();
- 	extern char *timezone();
  # endif OLDTIME
  # ifdef V6
  	extern char *StdTimezone, *DstTimezone;
--- 74,79 ----
***************
*** 148,154 ****
  	else
  		p = tzname[0];
  # else
! 	p = timezone(t.timezone, localtime(&t.time)->tm_isdst);
  # endif USG
  # endif V6
  	if ((strncmp(p, "GMT", 3) == 0 || strncmp(p, "gmt", 3) == 0) &&
--- 147,153 ----
  	else
  		p = tzname[0];
  # else
! 	p = localtime(&t.time)->tm_zone;
  # endif USG
  # endif V6
  	if ((strncmp(p, "GMT", 3) == 0 || strncmp(p, "gmt", 3) == 0) &&
