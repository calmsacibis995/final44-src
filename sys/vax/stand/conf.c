/*
 * Copyright (c) 1982, 1986, 1988 Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)conf.c	7.9 (Berkeley) 12/16/90
 */

#include "sys/param.h"
#include "stand/saio.h"

extern int	nullsys(), nodev(), noioctl();

#if defined(VAX780) || defined(VAX750) || defined(VAX8600)
#define	HP		"hp"
int	hpstrategy(), hpopen();
#ifdef SMALL
#define	hpioctl		noioctl
#else
int	hpioctl();
#endif
#else
#define	HP		0
#define	hpstrategy	nodev
#define	hpopen		nodev
#define	hpioctl		noioctl
#endif

int	upstrategy(), upopen();
#ifdef SMALL
#define	upioctl		noioctl
#else
int	upioctl();
#endif

int	rkstrategy(), rkopen();
int	rastrategy(), raopen();

#if defined(VAX730)
#define	RB		"rb"
int	idcstrategy(), idcopen();
#else
#define	RB		0
#define	idcstrategy	nodev
#define	idcopen		nodev
#endif

int	rlstrategy(), rlopen();

#ifdef BOOT
#define	TM		0
#define	tmstrategy	nodev
#define	tmopen		nodev
#define	tmclose		nodev
#define	TS		0
#define	tsstrategy	nodev
#define	tsopen		nodev
#define	tsclose		nodev
#define	HT		0
#define	htstrategy	nodev
#define	htopen		nodev
#define	htclose		nodev
#define	MT		0
#define	mtstrategy	nodev
#define	mtopen		nodev
#define	mtclose		nodev
#define	UT		0
#define	utstrategy	nodev
#define	utopen		nodev
#define	utclose		nodev
#define	TMSCP		0
#define	tmscpstrategy	nodev
#define	tmscpopen	nodev
#define	tmscpclose	nodev
#else /* !BOOT */
#define	TM		"tm"
int	tmstrategy(), tmopen(), tmclose();
#define	TS		"ts"
int	tsstrategy(), tsopen(), tsclose();

#if defined(VAX780) || defined(VAX750) || defined(VAX8600)
#define	HT		"ht"
int	htstrategy(), htopen(), htclose();
#define	MT		"mt"
int	mtstrategy(), mtopen(), mtclose();
#else /* massbus vax */
#define	HT		0
#define	htstrategy	nodev
#define	htopen		nodev
#define	htclose		nodev
#define	MT		0
#define	mtstrategy	nodev
#define	mtopen		nodev
#define	mtclose		nodev
#endif /* massbus vax */

#define	UT		"ut"
int	utstrategy(), utopen(), utclose();
#define	TMSCP		"tms"
int	tmscpstrategy(), tmscpopen(), tmscpclose();
#endif /* BOOT */

#ifdef VAX8200
#define	KRA		"kra"
int	krastrategy(), kraopen();
#else
#define	KRA		0
#define	krastrategy	nodev
#define	kraopen		nodev
#endif

struct devsw devsw[] = {
	{ HP,	hpstrategy,	hpopen,	nullsys, hpioctl },  /*  0 = hp */
	{ HT,	htstrategy,	htopen,	htclose, noioctl },  /*  1 = ht */
	{ "up",	upstrategy,	upopen,	nullsys, upioctl },  /*  2 = up */
	{ "hk",	rkstrategy,	rkopen,	nullsys, noioctl },  /*  3 = hk */
	{ 0,	nodev,		nodev,	nullsys, noioctl },  /*  4 = sw */
	{ TM,	tmstrategy,	tmopen,	tmclose, noioctl },  /*  5 = tm */
	{ TS,	tsstrategy,	tsopen,	tsclose, noioctl },  /*  6 = ts */
	{ MT,	mtstrategy,	mtopen,	mtclose, noioctl },  /*  7 = mt */
	{ 0,	nodev,		nodev,	nullsys, noioctl },  /*  8 = tu */
	{ "ra",	rastrategy,	raopen,	nullsys, noioctl },  /*  9 = ra */
	{ UT,	utstrategy,	utopen,	utclose, noioctl },  /* 10 = ut */
	{ RB,	idcstrategy,	idcopen,nullsys, noioctl },  /* 11 = rb */
	{ 0,	nodev,		nodev,	nullsys, noioctl },  /* 12 = uu */
	{ 0,	nodev,		nodev,	nullsys, noioctl },  /* 13 = rx */
	{ "rl",	rlstrategy,	rlopen,	nullsys, noioctl },  /* 14 = rl */
	{ TMSCP,tmscpstrategy,tmscpopen,tmscpclose,noioctl}, /* 15 = tmscp */
	{ KRA,	krastrategy,	kraopen,nullsys, noioctl},   /* 16 = kra */
};

int	ndevs = (sizeof(devsw)/sizeof(devsw[0]));
