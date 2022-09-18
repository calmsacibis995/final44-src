/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/* 
 * HISTORY
 * $Log:	pit.c,v $
 * Revision 2.2.1.5  90/11/27  13:40:21  rvb
 * 	We don't want to see clock interrupts till clkstart(),
 * 	where we enable them.
 * 	[90/11/05            rvb]
 * 
 * Revision 2.2.1.4  90/07/27  11:24:44  rvb
 * 	Fix Intel Copyright as per B. Davies authorization.
 * 	[90/07/27            rvb]
 * 
 * Revision 2.2.1.3  90/07/10  11:42:39  rvb
 * 	Flush EXL references
 * 	[90/06/15            rvb]
 * 
 * Revision 2.2.1.2  90/01/08  13:29:03  rvb
 * 	Add Intel copyright.
 * 	[90/01/08            rvb]
 * 
 * Revision 2.2.1.1  89/10/22  11:31:28  rvb
 * 	splall/backall -> splon/sploff
 * 	[89/10/20            rvb]
 * 
 * Revision 2.2  89/09/25  12:32:40  rvb
 * 	File was provided by Intel 9/18/89.
 * 	[89/09/23            rvb]
 * 
 */

/*
  Copyright 1988, 1989 by Intel Corporation, Santa Clara, California.

		All Rights Reserved

Permission to use, copy, modify, and distribute this software and
its documentation for any purpose and without fee is hereby
granted, provided that the above copyright notice appears in all
copies and that both the copyright notice and this permission notice
appear in supporting documentation, and that the name of Intel
not be used in advertising or publicity pertaining to distribution
of the software without specific, written prior permission.

INTEL DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE
INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS,
IN NO EVENT SHALL INTEL BE LIABLE FOR ANY SPECIAL, INDIRECT, OR
CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
LOSS OF USE, DATA OR PROFITS, WHETHER IN ACTION OF CONTRACT,
NEGLIGENCE, OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION
WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

#include <cputypes.h>
#include <sys/param.h>
#include <sys/time.h>
#include <sys/kernel.h>
#include <i386/ipl.h>
#include <i386/pit.h>

int pitctl_port  = PITCTL_PORT;		/* For 386/20 Board */
int pitctr0_port = PITCTR0_PORT;	/* For 386/20 Board */
int pitctr1_port = PITCTR1_PORT;	/* For 386/20 Board */
int pitctr2_port = PITCTR2_PORT;	/* For 386/20 Board */

/* We want PIT 0 in square wave mode */

int pit0_mode = PIT_C0|PIT_SQUAREMODE|PIT_READMODE ;

unsigned int delaycount;		/* loop count in trying to delay for
					 * 1 millisecond
					 */
unsigned long microdata=50;		/* loop count for 10 microsecond wait.
					   MUST be initialized for those who
					   insist on calling "tenmicrosec"
					   it before the clock has been
					   initialized.
					 */
unsigned int clknumb = CLKNUM;		/* interrupt interval for timer 0 */
clkstart()
{
	unsigned int	flags;
	unsigned char	byte;
	int		s;

	intpri[0] = SPLHI;		/* clock is pic slot 0 */
	form_pic_mask();

	findspeed();
	microfind();
	s = sploff();         /* disable interrupts */
	/* Since we use only timer 0, we program that.
	 * 8254 Manual specifically says you do not need to program
	 * timers you do not use
	 */
	outb(pitctl_port, pit0_mode);
	clknumb = CLKNUM/hz;
	byte = clknumb;
	outb(pitctr0_port, byte);
	byte = clknumb>>8;
	outb(pitctr0_port, byte); 
	splon(s);         /* restore interrupt state */
}

#define COUNT	0x2000

findspeed()
{
	unsigned int flags;
	unsigned char byte;
	unsigned int leftover;
	int i;
	int j;
	int s;

	s = sploff();                 /* disable interrupts */
	/* Put counter in count down mode */
#define PIT_COUNTDOWN PIT_READMODE|PIT_NDIVMODE
	outb(pitctl_port, PIT_COUNTDOWN);
	/* output a count of -1 to counter 0 */
	outb(pitctr0_port, 0xff);
	outb(pitctr0_port, 0xff);
	delaycount = COUNT;
	spinwait(1);
	/* Read the value left in the counter */
	byte = inb(pitctr0_port);	/* least siginifcant */
	leftover = inb(pitctr0_port);	/* most significant */
	leftover = (leftover<<8) + byte ;
	/* Formula for delaycount is :
	 *  (loopcount * timer clock speed)/ (counter ticks * 1000)
	 * 1000 is for figuring out milliseconds 
	 */
	delaycount = (((COUNT * CLKNUM)/1000) * hz) / (0xffff-leftover);
	splon(s);         /* restore interrupt state */
}

spinwait(millis)
	int millis;		/* number of milliseconds to delay */
{
	int i, j;

	for (i=0;i<millis;i++)
		for (j=0;j<delaycount;j++)
			;
}

#define MICROCOUNT	0x2000

microfind()
{
	unsigned int flags;
	unsigned char byte;
	unsigned short leftover;
	int s;


	s = sploff();                 /* disable interrupts */

	/* Put counter in count down mode */
	outb(pitctl_port, PIT_COUNTDOWN);
	/* output a count of -1 to counter 0 */
	outb(pitctr0_port, 0xff);
	outb(pitctr0_port, 0xff);
	microdata=MICROCOUNT;
	tenmicrosec();
	/* Read the value left in the counter */
	byte = inb(pitctr0_port);	/* least siginifcant */
	leftover = inb(pitctr0_port);	/* most significant */
	leftover = (leftover<<8) + byte ;
	/* Formula for delaycount is :
	 *  (loopcount * timer clock speed)/ (counter ticks * 1000)
	 *  Note also that 1000 is for figuring out milliseconds
	 */
	microdata = (MICROCOUNT * CLKNUM) / ((0xffff-leftover)*(100000/hz));
	if (!microdata)
		microdata++;
	splon(s);         /* restore interrupt state */
}
