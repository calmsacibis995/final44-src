/*
 * tvtoa - return an asciized representation of a struct timeval
 */
#include <stdio.h>
#include <sys/time.h>

#include "lib_strbuf.h"
#include "ntp_stdlib.h"

char *
tvtoa(tv)
	struct timeval *tv;
{
	register char *buf;
	register u_long sec;
	register u_long usec;
	register int isneg;

	if (tv->tv_sec < 0 || tv->tv_usec < 0) {
		sec = -tv->tv_sec;
		usec = -tv->tv_usec;
		isneg = 1;
	} else {
		sec = tv->tv_sec;
		usec = tv->tv_usec;
		isneg = 0;
	}

	LIB_GETBUF(buf);

	(void) sprintf(buf, "%s%lu.%06lu", (isneg?"-":""), sec, usec);
	return buf;
}
