/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/* 
 * HISTORY
 * $Log:	mc68020pats.c,v $
 * Revision 2.3  89/02/25  19:34:41  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.2  89/01/15  16:33:02  rpd
 * 	#ifdef'd out the bogus lock patterns, added comment.
 * 	[89/01/15  15:12:40  rpd]
 * 
 * 18-Dec-87  Robert Baron (rvb) at Carnegie-Mellon University
 *	Created
 *
 */

/*
 * TODO:	If usage ever warrants:
 *
 */

#include <inline/inline.h>

struct pats tst[] = {

	{0, "_splhigh\n",
"	movw	sr, d0\n\
	movw	high, sr\n"},

	{1, "_splx\n",
"	movl	sp@+, d1\n\
	movw	sr, d0\n\
	movw	d1, sr\n"},

	{ 0, "", ""}
};
struct pats mc68020_ptab[] = {

	{ 0, "", ""}
};

#define spl(y) \
"	movw	sr, d0\n\
	movw	#y, sr\n"

#define rspl(y) \
"	movw	sr,d0\n\
	andw	#0x2700,d0\n\
	cmpw	#y,d0\n\
	jge	1f\n\
	movw	#y,sr\n\
1:"

#define splx() \
"	movl	sp@+, d1\n\
	movw	sr, d0\n\
	movw	d1, sr\n"

#define splr() \
"	movl	sp@+, d1\n\
	movw	sr, d0\n\
	andw	#0x2700, d0\n\
	andw	#0x2700, d1\n\
	cmpw	d1, d0\n\
	jge	1f\n\
	movw	d1, sr\n\
1:"

struct pats sun_ptab[] = {

	{0, "_splimp\n",	rspl(0x2300)},
	{0, "_splnet\n",	rspl(0x2100)},
	{0, "_splie\n",		rspl(0x2300)},
	{0, "_splclock\n",	rspl(0x2500)},
	{0, "_splzs\n",		 spl(0x2600)},
	{0, "_spl7\n",		 spl(0x2700)},
	{0, "_spl6\n",		 spl(0x2500)},
	{0, "_spl5\n",		 spl(0x2500)},
	{0, "_spl4\n",		 spl(0x2400)},
	{0, "_spl3\n",		 spl(0x2300)},
	{0, "_spl2\n",		 spl(0x2200)},
	{0, "_spl1\n",		 spl(0x2100)},
	{0, "_spl0\n",		 spl(0x2000)},

	{1, "_splx\n",		splx()},
	{1, "_splr\n",		splr()},

	{0, "_np_splhigh\n",	spl(0x2700)},
	{1, "_np_splx\n",	splx()},

	{ 0, "", ""}
};

struct pats unix_ptab[] = {

	{ 0, "", ""}
};

struct pats mach_schnell_ptab[] = {

	{ 0, "", ""},

#ifdef	notdef
/*
 *	This code is wrong, given the current lock layout.
 */

	{1, "_lock_write\n",
"	movl	sp@+, a0\n\
	movl	a0@, d0\n\
	andl	#0x3ffff, d0		| if (no readers, no upgrade, no writer)\n\
	beqs	1f			| success\n\
	pea	a0@\n\
	jbsr	_lock_write\n\
	bras	2f\n\
1:	bset	#1, a0@(2)		| bit 17\n\
2:\n"},

	{1, "_lock_read\n",
"	movl	sp@+, a0\n\
	movl	a0@, d0\n\
	andl	#0x30000, d0		| if (no upgrade, no writer)\n\
	beqs	1f			| success\n\
	pea	a0@			| else call C\n\
	jbsr	_lock_read\n\
	bras	2f\n\
1:	addqw	a0@			| increment reader count\n\
2:\n" },

	{1, "_lock_done\n", 
"	movl	sp@+, a0\n\
	tstw	a0@			| if (any readers)\n\
	beqs	0f\n\
	subql	a0@			| ... decrement count\n\
	beqs	1f\n\
0:	tstl	a0@(12)			| recursive lock?\n\
	beqs	0f\n\
	subql	a0@(12)			| decrement recursion depth\n\
	bras	2f			| don't wake up waiters yet\n\
0:	bclr	#0,a0@(2)		| clear bit 16\n\
	bnes	1f			| if (upgrade) release it\n\
	bclr	#1,a0@(2)		| clear 17,release writer\n\
1:	bclr	#2,a0@(2)		| clear bit 18\n\
	beqs	2f			| if anyone waiting:\n\
	pea	a0@			| clear bit,\n\
	jbsr	_thread_wakeup		| call wakeup\n\
2:\n" },

	{ 0, "", ""}
#endif	notdef
};
