/*
 *  isis_timer.c,v 1.11 1993/01/07 22:40:06 jch Exp
 */

/* %(Copyright.header) */


#define	INCLUDE_TIME
#include "include.h"
#include "isis_includes.h"

#define MAXTIMER	512

struct timerEntry {
	int		ttf;		/* time to fire */
	int 	(*func)();	/* func to call */
	caddr_t	data;		/* data to pass */
} timers[MAXTIMER];

void
initTimers()
{
	int i;
	for (i=0; i<MAXTIMER; i++)
		timers[i].ttf = 0;
}

void
feepTimer()
{
	int i;

	for (i=0; i<MAXTIMER; i++) {
		if (timers[i].ttf > 0) {
			if (--timers[i].ttf == 0)
				(*(timers[i].func))(timers[i].data);
		}
	}
}

void
clearTimer(i)
int     i;
{
        timers[i].ttf = 0;
}

void
resetTimer(i, interval)
int     i;
int     interval;
{
        timers[i].ttf = interval;
}

/* 
 * Set func to be called in interval seconds; return index of timer.
 * STEVE XXX - this doesn't comply with 10589 Section 10.1, which 
 * specifies a range (with jitter) of [0.75*interval, interval].
 */
int
setTimer(interval, func, data)
int	interval;
int (*func)();
caddr_t data;
{
	int i;
	for (i=0; i<MAXTIMER; i++) {
		if (timers[i].ttf <= 0) {
			if (interval > 1) {
				if (random() & 0x01)
					interval++;
				else
					interval--;
			}
			timers[i].ttf = interval;
			timers[i].func = func;
			timers[i].data = (caddr_t) data;
			return(i);
		}
	}
	trace_log_tf(isis_trace_options,
		     0,
		     LOG_ERR,
		     ("out of timers"));
	task_quit(0);
        return(-1);
}


/*
 * %(Copyright)
 * %(Copyright.ISIS)
 */
