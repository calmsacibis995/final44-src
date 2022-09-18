h36718
s 00002/00002/00245
d D 8.1 93/06/06 16:32:51 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00022/00014/00225
d D 5.7 93/05/16 16:10:01 torek 7 6
c prototypes, ANSI, pass -Wall; still could stand more work
e
s 00001/00001/00238
d D 5.6 91/02/28 16:46:53 bostic 6 5
c ANSI
e
s 00001/00011/00238
d D 5.5 90/06/01 17:44:58 bostic 5 4
c new copyright notice
e
s 00010/00005/00239
d D 5.4 88/06/29 20:49:29 bostic 4 3
c install approved copyright notice
e
s 00010/00004/00234
d D 5.3 88/03/28 13:51:47 bostic 3 2
c add Berkeley specific header
e
s 00033/00000/00205
d D 5.2 86/02/07 21:35:54 minshall 2 1
c Centralize re-synchronization routine.  Only do re-synchronization
e
s 00205/00000/00000
d D 5.1 86/02/06 15:00:07 minshall 1 0
c date and time created 86/02/06 15:00:07 by minshall
e
u
U
t
T
I 1
/*
D 3
 * Copyright (c) 1985 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 3
I 3
D 8
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
 *
D 5
 * Redistribution and use in source and binary forms are permitted
D 4
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 4
I 4
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 5
I 5
 * %sccs.include.redist.c%
E 5
E 4
E 3
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 3
#endif not lint
E 3
I 3
#endif /* not lint */
E 3

/* Simple minded read-ahead/write-behind subroutines for tftp user and
   server.  Written originally with multiple buffers in mind, but current
   implementation has two buffer logic wired in.

   Todo:  add some sort of final error check so when the write-buffer
   is finally flushed, the caller can detect if the disk filled up
   (or had an i/o error) and return a nak to the other side.

			Jim Guyton 10/85
 */

#include <sys/types.h>
#include <sys/socket.h>
I 2
#include <sys/ioctl.h>
E 2
#include <netinet/in.h>
#include <arpa/tftp.h>
I 7

E 7
#include <stdio.h>
I 7
#include <unistd.h>
E 7

I 7
#include "tftpsubs.h"

E 7
#define PKTSIZE SEGSIZE+4       /* should be moved to tftp.h */

struct bf {
	int counter;            /* size of data in buffer, or flag */
	char buf[PKTSIZE];      /* room for data packet */
} bfs[2];

				/* Values for bf.counter  */
#define BF_ALLOC -3             /* alloc'd but not yet filled */
#define BF_FREE  -2             /* free */
/* [-1 .. SEGSIZE] = size of data in the data buffer */

D 7
static int nextone;     /* index of next buffer to use */
static int current;     /* index of buffer in use */
E 7
I 7
static int nextone;		/* index of next buffer to use */
static int current;		/* index of buffer in use */
E 7

D 7
			/* control flags for crlf conversions */
int newline = 0;        /* fillbuf: in middle of newline expansion */
int prevchar = -1;      /* putbuf: previous char (cr check) */
E 7
I 7
				/* control flags for crlf conversions */
int newline = 0;		/* fillbuf: in middle of newline expansion */
int prevchar = -1;		/* putbuf: previous char (cr check) */
E 7

D 7
struct tftphdr *rw_init();
E 7
I 7
static struct tftphdr *rw_init();
E 7

struct tftphdr *w_init() { return rw_init(0); }         /* write-behind */
struct tftphdr *r_init() { return rw_init(1); }         /* read-ahead */

D 7
struct tftphdr *
rw_init(x)              /* init for either read-ahead or write-behind */
int x;                  /* zero for write-behind, one for read-head */
E 7
I 7
static struct tftphdr *
rw_init(x)			/* init for either read-ahead or write-behind */
	int x;			/* zero for write-behind, one for read-head */
E 7
{
D 7
	newline = 0;            /* init crlf flag */
E 7
I 7
	newline = 0;		/* init crlf flag */
E 7
	prevchar = -1;
	bfs[0].counter =  BF_ALLOC;     /* pass out the first buffer */
	current = 0;
	bfs[1].counter = BF_FREE;
	nextone = x;                    /* ahead or behind? */
	return (struct tftphdr *)bfs[0].buf;
}


/* Have emptied current buffer by sending to net and getting ack.
   Free it and return next buffer filled with data.
 */
I 7
int
E 7
readit(file, dpp, convert)
	FILE *file;                     /* file opened for read */
	struct tftphdr **dpp;
	int convert;                    /* if true, convert to ascii */
{
	struct bf *b;

	bfs[current].counter = BF_FREE; /* free old one */
	current = !current;             /* "incr" current */

	b = &bfs[current];              /* look at new buffer */
	if (b->counter == BF_FREE)      /* if it's empty */
		read_ahead(file, convert);      /* fill it */
D 7
/*      assert(b->counter != BF_FREE);  /* check */
E 7
I 7
/*      assert(b->counter != BF_FREE);*//* check */
E 7
	*dpp = (struct tftphdr *)b->buf;        /* set caller's ptr */
	return b->counter;
}

/*
 * fill the input buffer, doing ascii conversions if requested
 * conversions are  lf -> cr,lf  and cr -> cr, nul
 */
I 7
void
E 7
read_ahead(file, convert)
	FILE *file;                     /* file opened for read */
	int convert;                    /* if true, convert to ascii */
{
	register int i;
	register char *p;
	register int c;
	struct bf *b;
	struct tftphdr *dp;

	b = &bfs[nextone];              /* look at "next" buffer */
	if (b->counter != BF_FREE)      /* nop if not free */
		return;
	nextone = !nextone;             /* "incr" next buffer ptr */

	dp = (struct tftphdr *)b->buf;

	if (convert == 0) {
		b->counter = read(fileno(file), dp->th_data, SEGSIZE);
		return;
	}

	p = dp->th_data;
	for (i = 0 ; i < SEGSIZE; i++) {
		if (newline) {
			if (prevchar == '\n')
				c = '\n';       /* lf to cr,lf */
			else    c = '\0';       /* cr to cr,nul */
			newline = 0;
		}
		else {
			c = getc(file);
			if (c == EOF) break;
			if (c == '\n' || c == '\r') {
				prevchar = c;
				c = '\r';
				newline = 1;
			}
		}
	       *p++ = c;
	}
	b->counter = (int)(p - dp->th_data);
}

/* Update count associated with the buffer, get new buffer
   from the queue.  Calls write_behind only if next buffer not
   available.
 */
I 7
int
E 7
writeit(file, dpp, ct, convert)
	FILE *file;
	struct tftphdr **dpp;
D 7
	int convert;
E 7
I 7
	int ct, convert;
E 7
{
	bfs[current].counter = ct;      /* set size of data to write */
	current = !current;             /* switch to other buffer */
	if (bfs[current].counter != BF_FREE)     /* if not free */
D 7
		write_behind(file, convert);     /* flush it */
E 7
I 7
		(void)write_behind(file, convert); /* flush it */
E 7
	bfs[current].counter = BF_ALLOC;        /* mark as alloc'd */
	*dpp =  (struct tftphdr *)bfs[current].buf;
	return ct;                      /* this is a lie of course */
}

/*
 * Output a buffer to a file, converting from netascii if requested.
 * CR,NUL -> CR  and CR,LF => LF.
 * Note spec is undefined if we get CR as last byte of file or a
 * CR followed by anything else.  In this case we leave it alone.
 */
I 7
int
E 7
write_behind(file, convert)
	FILE *file;
	int convert;
{
	char *buf;
	int count;
	register int ct;
	register char *p;
	register int c;                 /* current character */
	struct bf *b;
	struct tftphdr *dp;

	b = &bfs[nextone];
	if (b->counter < -1)            /* anything to flush? */
		return 0;               /* just nop if nothing to do */

	count = b->counter;             /* remember byte count */
	b->counter = BF_FREE;           /* reset flag */
	dp = (struct tftphdr *)b->buf;
	nextone = !nextone;             /* incr for next time */
	buf = dp->th_data;

	if (count <= 0) return -1;      /* nak logic? */

	if (convert == 0)
		return write(fileno(file), buf, count);

	p = buf;
	ct = count;
	while (ct--) {                  /* loop over the buffer */
	    c = *p++;                   /* pick up a character */
	    if (prevchar == '\r') {     /* if prev char was cr */
		if (c == '\n')          /* if have cr,lf then just */
		   fseek(file, -1, 1);  /* smash lf on top of the cr */
		else
		   if (c == '\0')       /* if have cr,nul then */
			goto skipit;    /* just skip over the putc */
		/* else just fall through and allow it */
	    }
	    putc(c, file);
skipit:
	    prevchar = c;
	}
	return count;
}


I 2
/* When an error has occurred, it is possible that the two sides
 * are out of synch.  Ie: that what I think is the other side's
 * response to packet N is really their response to packet N-1.
 *
 * So, to try to prevent that, we flush all the input queued up
 * for us on the network connection on our host.
 *
 * We return the number of packets we flushed (mostly for reporting
 * when trace is active).
 */

int
synchnet(f)
D 7
int	f;		/* socket to flush */
E 7
I 7
	int	f;		/* socket to flush */
E 7
{
	int i, j = 0;
	char rbuf[PKTSIZE];
	struct sockaddr_in from;
	int fromlen;

	while (1) {
		(void) ioctl(f, FIONREAD, &i);
		if (i) {
			j++;
			fromlen = sizeof from;
			(void) recvfrom(f, rbuf, sizeof (rbuf), 0,
D 6
				(caddr_t)&from, &fromlen);
E 6
I 6
				(struct sockaddr *)&from, &fromlen);
E 6
		} else {
			return(j);
		}
	}
}
E 2
E 1
