#ifndef lint
#ifndef NOID
static char	elsieid[] = "@(#)difftime.c	1.1";
#endif /* !defined NOID */
#endif /* !defined lint */

/*LINTLIBRARY*/

#include "time.h"
#include "nonstd.h"

double
difftime(time1, time0)
const time_t	time1;
const time_t	time0;
{
	return time1 - time0;
}
