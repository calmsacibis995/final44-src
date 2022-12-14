/*
 * refnumtoa - return asciized refclock addresses stored in local array space
 */
#include <stdio.h>

#include "ntp_fp.h"
#include "lib_strbuf.h"
#include "ntp_stdlib.h"

char *
refnumtoa(num)
	u_long num;
{
	register u_long netnum;
	register char *buf;
	register const char *rclock;
	
	netnum = ntohl(num);
	
	LIB_GETBUF(buf);

	rclock = clockname((int)((netnum >> 8) & 0xff));

	if (rclock != NULL)
		(void)sprintf(buf, "%s(%lu)", rclock, netnum & 0xff);
	else
		(void)sprintf(buf, "REFCLK(%lu,%lu)",
		    (netnum >> 8) & 0xff, netnum&0xff);
	return buf;
}
