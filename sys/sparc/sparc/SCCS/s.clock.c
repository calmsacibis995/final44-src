h45902
s 00001/00001/00465
d D 8.2 94/05/08 15:58:50 torek 6 5
c calculate hostid correctly (typo)
e
s 00002/00002/00464
d D 8.1 93/06/11 15:16:13 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00038/00012/00428
d D 7.4 93/04/20 21:30:36 torek 4 3
c from elf: more variance; short external names
e
s 00012/00012/00428
d D 7.3 92/10/11 12:57:07 bostic 3 2
c make kernel includes standard
e
s 00005/00000/00435
d D 7.2 92/07/21 16:54:21 bostic 2 1
c update the contribution notice; LBL requires acknowledgement
e
s 00435/00000/00000
d D 7.1 92/07/13 00:44:30 torek 1 0
c date and time created 92/07/13 00:44:30 by torek
e
u
U
t
T
I 1
/*
D 5
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley.
 *
I 2
 * All advertising materials mentioning features or use of this software
 * must display the following acknowledgement:
 *	This product includes software developed by the University of
D 4
 *	California, Lawrence Berkeley Laboratories.
E 4
I 4
 *	California, Lawrence Berkeley Laboratory.
E 4
 *
E 2
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *
D 4
 * from: $Header: clock.c,v 1.14 92/07/07 05:34:08 leres Exp $ (LBL)
E 4
I 4
 * from: $Header: clock.c,v 1.17 92/11/26 03:04:47 torek Exp $ (LBL)
E 4
 */

/*
 * Clock driver.  This is the id prom (``eeprom'') driver as well
 * and includes the timer register functions too.
 */

D 3
#include "sys/param.h"
#include "sys/kernel.h"
#include "sys/device.h"
#include "sys/proc.h"
#include "sys/resourcevar.h"
E 3
I 3
#include <sys/param.h>
#include <sys/kernel.h>
#include <sys/device.h>
#include <sys/proc.h>
#include <sys/resourcevar.h>
E 3
#ifdef GPROF
D 3
#include "sys/gmon.h"
E 3
I 3
#include <sys/gmon.h>
E 3
#endif

D 3
#include "vm/vm.h"
E 3
I 3
#include <vm/vm.h>
E 3

D 3
#include "machine/autoconf.h"
E 3
I 3
#include <machine/autoconf.h>
E 3
D 4
#ifdef notdef
D 3
#include "machine/psl.h"
E 3
I 3
#include <machine/psl.h>
E 3
#endif
E 4

D 3
#include "clockreg.h"
#include "intreg.h"
#include "timerreg.h"
E 3
I 3
#include <sparc/sparc/clockreg.h>
#include <sparc/sparc/intreg.h>
#include <sparc/sparc/timerreg.h>
E 3

/*
 * Statistics clock interval and variance, in usec.  Variance must be a
 * power of two.  Since this gives us an even number, not an odd number,
 * we discard one case and compensate.  That is, a variance of 1024 would
 * give us offsets in [0..1023].  Instead, we take offsets in [1..1023].
 * This is symmetric about the point 512, or statvar/2, and thus averages
 * to that value (assuming uniform random numbers).
 */
D 4
static int statvar = 1024;
static int statmin;		/* statclock interval - 1/2*variance */
E 4
I 4
/* XXX fix comment to match value */
int statvar = 8192;
int statmin;			/* statclock interval - 1/2*variance */
E 4

I 4
static int clockmatch __P((struct device *, struct cfdata *, void *));
E 4
static void clockattach __P((struct device *, struct device *, void *));
I 4

E 4
struct cfdriver clockcd =
D 4
    { NULL, "eeprom", matchbyname, clockattach,
      DV_DULL, sizeof(struct device) };
E 4
I 4
    { NULL, "clock", clockmatch, clockattach, DV_DULL, sizeof(struct device) };
E 4

I 4
static int timermatch __P((struct device *, struct cfdata *, void *));
E 4
static void timerattach __P((struct device *, struct device *, void *));
struct cfdriver timercd =
D 4
    { NULL, "counter-timer", matchbyname, timerattach, DV_DULL,
      sizeof(struct device) };
E 4
I 4
    { NULL, "timer", timermatch, timerattach, DV_DULL, sizeof(struct device) };
E 4

I 4
/*
 * The OPENPROM calls the clock the "eeprom", so we have to have our
 * own special match function to call it the "clock".
 */
static int
clockmatch(parent, cf, aux)
	struct device *parent;
	struct cfdata *cf;
	void *aux;
{

	return (strcmp("eeprom", ((struct romaux *)aux)->ra_name) == 0);
}

E 4
/* ARGSUSED */
static void
clockattach(parent, self, aux)
	struct device *parent, *self;
	void *aux;
{
	register int h;
	register struct clockreg *cl;
	struct romaux *ra = aux;

D 4
	printf(": %s\n", getpropstring(ra->ra_node, "model"));
E 4
I 4
	printf(": %s (eeprom)\n", getpropstring(ra->ra_node, "model"));
E 4
	/*
	 * We ignore any existing virtual address as we need to map
	 * this read-only and make it read-write only temporarily,
	 * whenever we read or write the clock chip.  The clock also
	 * contains the ID ``PROM'', and I have already had the pleasure
	 * of reloading the cpu type, Ethernet address, etc, by hand from
	 * the console FORTH interpreter.  I intend not to enjoy it again.
	 */
	cl = (struct clockreg *)mapiodev(ra->ra_paddr, sizeof *clockreg);
	pmap_changeprot(kernel_pmap, (vm_offset_t)clockreg, VM_PROT_READ, 1);
	h = cl->cl_idprom.id_machine << 24;
	h |= cl->cl_idprom.id_hostid[0] << 16;
	h |= cl->cl_idprom.id_hostid[1] << 8;
D 6
	h |= cl->cl_idprom.id_hostid[0];
E 6
I 6
	h |= cl->cl_idprom.id_hostid[2];
E 6
	hostid = h;
	clockreg = cl;
I 4
}

/*
 * The OPENPROM calls the timer the "counter-timer".
 */
static int
timermatch(parent, cf, aux)
	struct device *parent;
	struct cfdata *cf;
	void *aux;
{

	return (strcmp("counter-timer", ((struct romaux *)aux)->ra_name) == 0);
E 4
}

/* ARGSUSED */
static void
timerattach(parent, self, aux)
	struct device *parent, *self;
	void *aux;
{
	register struct romaux *ra = aux;

	printf("\n");
	/*
	 * This time, we ignore any existing virtual address because
	 * we have a fixed virtual address for the timer, to make
	 * microtime() faster.
	 */
	(void)mapdev(ra->ra_paddr, TIMERREG_VA, sizeof(struct timerreg));
	/* should link interrupt handlers here, rather than compiled-in? */
}

/*
 * Write en/dis-able clock registers.  We coordinate so that several
 * writers can run simultaneously.
 */
void
clk_wenable(onoff)
	int onoff;
{
	register int s;
	register vm_prot_t prot;/* nonzero => change prot */
	static int writers;

	s = splhigh();
	if (onoff)
		prot = writers++ == 0 ? VM_PROT_READ|VM_PROT_WRITE : 0;
	else
		prot = --writers == 0 ? VM_PROT_READ : 0;
	splx(s);
	if (prot)
		pmap_changeprot(kernel_pmap, (vm_offset_t)clockreg, prot, 1);
}

/*
 * XXX this belongs elsewhere
 */
void
myetheraddr(cp)
	u_char *cp;
{
	register struct clockreg *cl = clockreg;

	cp[0] = cl->cl_idprom.id_ether[0];
	cp[1] = cl->cl_idprom.id_ether[1];
	cp[2] = cl->cl_idprom.id_ether[2];
	cp[3] = cl->cl_idprom.id_ether[3];
	cp[4] = cl->cl_idprom.id_ether[4];
	cp[5] = cl->cl_idprom.id_ether[5];
}

/*
 * Delay: wait for `about' n microseconds to pass.
 * This is easy to do on the SparcStation since we have
 * freerunning microsecond timers -- no need to guess at
 * cpu speed factors.  We just wait for it to change n times
 * (if we calculated a limit, we might overshoot, and precision
 * is irrelevant here---we want less object code).
 */
delay(n)
	register int n;
{
	register int c, t;

	if (timercd.cd_ndevs == 0)
		panic("delay");
	c = TIMERREG->t_c10.t_counter;
	while (--n >= 0) {
		while ((t = TIMERREG->t_c10.t_counter) == c)
			continue;
		c = t;
	}
}

/*
 * Set up the real-time and statistics clocks.  Leave stathz 0 only if
 * no alternative timer is available.
 *
 * The frequencies of these clocks must be an even number of microseconds.
 */
cpu_initclocks()
{
	register int statint, minint;

	if (1000000 % hz) {
		printf("cannot get %d Hz clock; using 100 Hz\n", hz);
		hz = 100;
		tick = 1000000 / hz;
	}
	if (stathz == 0)
		stathz = hz;
	if (1000000 % stathz) {
		printf("cannot get %d Hz statclock; using 100 Hz\n", stathz);
		stathz = 100;
	}
	profhz = stathz;		/* always */

	statint = 1000000 / stathz;
	minint = statint / 2 + 100;
	while (statvar > minint)
		statvar >>= 1;
	TIMERREG->t_c10.t_limit = tmr_ustolim(tick);
	TIMERREG->t_c14.t_limit = tmr_ustolim(statint);
	statmin = statint - (statvar >> 1);
	ienab_bis(IE_L14 | IE_L10);
}

/*
 * Dummy setstatclockrate(), since we know profhz==hz.
 */
/* ARGSUSED */
void
setstatclockrate(newhz)
	int newhz;
{
	/* nothing */
}

/*
 * Level 10 (clock) interrupts.  If we are using the FORTH PROM for
 * console input, we need to check for that here as well, and generate
 * a software interrupt to read it.
 */
int
clockintr(cap)
	void *cap;
{
	register int discard;
	extern int rom_console_input;

	/* read the limit register to clear the interrupt */
	discard = TIMERREG->t_c10.t_limit;
	hardclock((struct clockframe *)cap);
	if (rom_console_input && cnrom())
		setsoftint();

	return (1);
}

/*
 * Level 14 (stat clock) interrupt handler.
 */
int
statintr(cap)
	void *cap;
{
	register int discard;
	register u_long newint, r, var;

	/* read the limit register to clear the interrupt */
	discard = TIMERREG->t_c14.t_limit;
	statclock((struct clockframe *)cap);

	/*
	 * Compute new randomized interval.  The intervals are uniformly
	 * distributed on [statint - statvar / 2, statint + statvar / 2],
	 * and therefore have mean statint, giving a stathz frequency clock.
	 */
	var = statvar;
	do {
		r = random() & (var - 1);
	} while (r == 0);
	newint = statmin + r;

	TIMERREG->t_c14.t_limit = tmr_ustolim(newint);
	return (1);
}

/*
 * BCD to decimal and decimal to BCD.
 */
#define	FROMBCD(x)	(((x) >> 4) * 10 + ((x) & 0xf))
#define	TOBCD(x)	(((x) / 10 * 16) + ((x) % 10))

#define	SECDAY		(24 * 60 * 60)
#define	SECYR		(SECDAY * 365)
#define	LEAPYEAR(y)	(((y) & 3) == 0)

/*
 * This code is defunct after 2068.
 * Will Unix still be here then??
 */
const short dayyr[12] =
    { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334 };

chiptotime(sec, min, hour, day, mon, year)
	register int sec, min, hour, day, mon, year;
{
	register int days, yr;

	sec = FROMBCD(sec);
	min = FROMBCD(min);
	hour = FROMBCD(hour);
	day = FROMBCD(day);
	mon = FROMBCD(mon);
	year = FROMBCD(year) + YEAR0;

	/* simple sanity checks */
	if (year < 70 || mon < 1 || mon > 12 || day < 1 || day > 31)
		return (0);
	days = 0;
	for (yr = 70; yr < year; yr++)
		days += LEAPYEAR(yr) ? 366 : 365;
	days += dayyr[mon - 1] + day - 1;
	if (LEAPYEAR(yr) && mon > 2)
		days++;
	/* now have days since Jan 1, 1970; the rest is easy... */
	return (days * SECDAY + hour * 3600 + min * 60 + sec);
}

struct chiptime {
	int	sec;
	int	min;
	int	hour;
	int	wday;
	int	day;
	int	mon;
	int	year;
};

timetochip(c)
	register struct chiptime *c;
{
	register int t, t2, t3, now = time.tv_sec;

	/* compute the year */
	t2 = now / SECDAY;
	t3 = (t2 + 2) % 7;	/* day of week */
	c->wday = TOBCD(t3 + 1);

	t = 69;
	while (t2 >= 0) {	/* whittle off years */
		t3 = t2;
		t++;
		t2 -= LEAPYEAR(t) ? 366 : 365;
	}
	c->year = t;

	/* t3 = month + day; separate */
	t = LEAPYEAR(t);
	for (t2 = 1; t2 < 12; t2++)
		if (t3 < dayyr[t2] + (t && t2 > 1))
			break;

	/* t2 is month */
	c->mon = t2;
	c->day = t3 - dayyr[t2 - 1] + 1;
	if (t && t2 > 2)
		c->day--;

	/* the rest is easy */
	t = now % SECDAY;
	c->hour = t / 3600;
	t %= 3600;
	c->min = t / 60;
	c->sec = t % 60;

	c->sec = TOBCD(c->sec);
	c->min = TOBCD(c->min);
	c->hour = TOBCD(c->hour);
	c->day = TOBCD(c->day);
	c->mon = TOBCD(c->mon);
	c->year = TOBCD(c->year - YEAR0);
}

/*
 * Set up the system's time, given a `reasonable' time value.
 */
inittodr(base)
	time_t base;
{
	register struct clockreg *cl = clockreg;
	int sec, min, hour, day, mon, year;
	int badbase = 0;

	if (base < 5 * SECYR) {
		printf("WARNING: preposterous time in file system\n");
		/* not going to use it anyway, if the chip is readable */
		base = 21*SECYR + 186*SECDAY + SECDAY/2;
		badbase = 1;
	}
	clk_wenable(1);
	cl->cl_csr |= CLK_READ;		/* enable read (stop time) */
	sec = cl->cl_sec;
	min = cl->cl_min;
	hour = cl->cl_hour;
	day = cl->cl_mday;
	mon = cl->cl_month;
	year = cl->cl_year;
	cl->cl_csr &= ~CLK_READ;	/* time wears on */
	clk_wenable(0);
	if ((time.tv_sec = chiptotime(sec, min, hour, day, mon, year)) == 0) {
		printf("WARNING: bad date in battery clock");
		/*
		 * Believe the time in the file system for lack of
		 * anything better, resetting the clock.
		 */
		time.tv_sec = base;
		if (!badbase)
			resettodr();
	} else {
		int deltat = time.tv_sec - base;

		if (deltat < 0)
			deltat = -deltat;
		if (deltat < 2 * SECDAY)
			return;
		printf("WARNING: clock %s %d days",
		    time.tv_sec < base ? "lost" : "gained", deltat / SECDAY);
	}
	printf(" -- CHECK AND RESET THE DATE!\n");
}

/*
 * Reset the clock based on the current time.
 * Used when the current clock is preposterous, when the time is changed,
 * and when rebooting.  Do nothing if the time is not yet known, e.g.,
 * when crashing during autoconfig.
 */
resettodr()
{
	register struct clockreg *cl;
	struct chiptime c;

	if (!time.tv_sec || (cl = clockreg) == NULL)
		return;
	timetochip(&c);
	clk_wenable(1);
	cl->cl_csr |= CLK_WRITE;	/* enable write */
	cl->cl_sec = c.sec;
	cl->cl_min = c.min;
	cl->cl_hour = c.hour;
	cl->cl_wday = c.wday;
	cl->cl_mday = c.day;
	cl->cl_month = c.mon;
	cl->cl_year = c.year;
	cl->cl_csr &= ~CLK_WRITE;	/* load them up */
	clk_wenable(0);
}
E 1
