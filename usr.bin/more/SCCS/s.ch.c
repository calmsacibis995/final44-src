h23654
s 00002/00002/00426
d D 8.1 93/06/06 15:36:07 bostic 12 11
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00000/00427
d D 5.11 92/06/21 15:42:29 bostic 11 10
c off_t is a quad, now
e
s 00000/00001/00427
d D 5.10 91/03/01 15:12:02 bostic 10 9
c ANSI
e
s 00000/00001/00428
d D 5.9 91/02/05 22:09:21 bostic 9 8
c stdio defines BUFSIX
e
s 00001/00012/00428
d D 5.8 90/06/01 17:03:25 bostic 8 7
c new copyright notice
e
s 00028/00007/00412
d D 5.7 88/11/26 12:03:52 bostic 7 6
c compress CR-LF to LF by default; -u flag prints the CR as "^M"
e
s 00088/00117/00331
d D 5.6 88/11/22 16:51:14 bostic 6 5
c less -> more
e
s 00002/00004/00446
d D 5.5 88/07/25 12:04:27 bostic 5 4
c update copyright notice
e
s 00003/00003/00447
d D 5.4 88/07/22 12:03:32 bostic 4 3
c lint cleanups
e
s 00000/00063/00450
d D 5.3 88/07/21 19:21:24 bostic 3 2
c rip out LOGFILE option
e
s 00001/00001/00512
d D 5.2 88/07/21 19:02:12 bostic 2 1
c offset_t -> off_t
e
s 00513/00000/00000
d D 5.1 88/07/21 18:52:35 bostic 1 0
c distribution by Mark Nudleman
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 Mark Nudleman
D 12
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.
E 12
I 12
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 12
 *
D 5
 * This code is derived from software contributed to Berkeley by
 * Mark Nudleman.
 * 
E 5
D 8
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
D 5
 * by the University of California, Berkeley.  The name of the
E 5
I 5
 * by Mark Nudleman and the University of California, Berkeley.  The
 * name of Mark Nudleman or the
E 5
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 8
I 8
 * %sccs.include.redist.c%
E 8
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

/*
 * Low level character input from the input file.
 * We use these special purpose routines which optimize moving
 * both forward and backward from the current read pointer.
 */

D 6
#include "less.h"
E 6
I 6
#include <sys/types.h>
#include <sys/file.h>
I 11
#include <unistd.h>
E 11
#include <stdio.h>
#include <less.h>
E 6

D 6
public int file = -1;		/* File descriptor of the input file */
E 6
I 6
int file = -1;		/* File descriptor of the input file */
E 6

/*
 * Pool of buffers holding the most recently used blocks of the input file.
 */
D 6
#define BUFSIZ	1024
E 6
I 6
D 9
#define	BUFSIZ	1024
E 9
E 6
struct buf {
	struct buf *next, *prev;
	long block;
	int datasize;
	char data[BUFSIZ];
};
D 6
public int nbufs;
E 6
I 6
int nbufs;
E 6

/*
D 6
 * The buffer pool is kept as a doubly-linked circular list,
 * in order from most- to least-recently used.
 * The circular list is anchored by buf_anchor.
E 6
I 6
 * The buffer pool is kept as a doubly-linked circular list, in order from
 * most- to least-recently used.  The circular list is anchored by buf_anchor.
E 6
 */
#define	END_OF_CHAIN	((struct buf *)&buf_anchor)
#define	buf_head	buf_anchor.next
#define	buf_tail	buf_anchor.prev

static struct {
	struct buf *next, *prev;
} buf_anchor = { END_OF_CHAIN, END_OF_CHAIN };

D 6
extern int clean_data;
extern int ispipe;
extern int autobuf;
extern int cbufs;
extern int sigs;
E 6
I 6
extern int ispipe, cbufs, sigs;
E 6
D 3
#if LOGFILE
extern int logfile;
#endif
E 3

/*
 * Current position in file.
 * Stored as a block number and an offset into the block.
 */
static long ch_block;
static int ch_offset;

D 6
/* 
 * Length of file, needed if input is a pipe.
 */
static POSITION ch_fsize;
E 6
I 6
/* Length of file, needed if input is a pipe. */
static off_t ch_fsize;
E 6

D 6
/*
 * Number of bytes read, if input is standard input (a pipe).
 */
static POSITION last_piped_pos;
E 6
I 6
/* Number of bytes read, if input is standard input (a pipe). */
static off_t last_piped_pos;
E 6

/*
D 6
 * Get the character pointed to by the read pointer.
 * ch_get() is a macro which is more efficient to call
 * than fch_get (the function), in the usual case 
 * that the block desired is at the head of the chain.
E 6
I 6
 * Get the character pointed to by the read pointer.  ch_get() is a macro
 * which is more efficient to call than fch_get (the function), in the usual
 * case that the block desired is at the head of the chain.
E 6
 */
D 6
#define	ch_get()   ((buf_head->block == ch_block && \
		     ch_offset < buf_head->datasize) ? \
			buf_head->data[ch_offset] : fch_get())
	static int
E 6
I 6
#define	ch_get() \
	((buf_head->block == ch_block && \
	    ch_offset < buf_head->datasize) ? \
	    buf_head->data[ch_offset] : fch_get())

static
E 6
fch_get()
{
I 7
	extern int bs_mode;
E 7
	register struct buf *bp;
D 7
	register int n;
	register char *p;
E 7
I 7
	register int n, ch;
	register char *p, *t;
E 7
D 6
	POSITION pos;
E 6
I 6
	off_t pos, lseek();
E 6

D 6
	/*
	 * Look for a buffer holding the desired block.
	 */
E 6
I 6
	/* look for a buffer holding the desired block. */
E 6
	for (bp = buf_head;  bp != END_OF_CHAIN;  bp = bp->next)
D 6
		if (bp->block == ch_block)
		{
E 6
I 6
		if (bp->block == ch_block) {
E 6
			if (ch_offset >= bp->datasize)
				/*
				 * Need more data in this buffer.
				 */
				goto read_more;
			/*
			 * On a pipe, we don't sort the buffers LRU
			 * because this can cause gaps in the buffers.
			 * For example, suppose we've got 12 1K buffers,
			 * and a 15K input stream.  If we read the first 12K
			 * sequentially, then jump to line 1, then jump to
			 * the end, the buffers have blocks 0,4,5,6,..,14.
			 * If we then jump to line 1 again and try to
			 * read sequentially, we're out of luck when we
			 * get to block 1 (we'd get the "pipe error" below).
			 * To avoid this, we only sort buffers on a pipe
			 * when we actually READ the data, not when we
			 * find it already buffered.
			 */
			if (ispipe)
D 6
				return (bp->data[ch_offset]);
E 6
I 6
				return(bp->data[ch_offset]);
E 6
			goto found;
		}
	/*
D 6
	 * Block is not in a buffer.  
	 * Take the least recently used buffer 
	 * and read the desired block into it.
	 * If the LRU buffer has data in it, 
	 * and autobuf is true, and input is a pipe, 
	 * then try to allocate a new buffer first.
E 6
I 6
	 * Block is not in a buffer.  Take the least recently used buffer
	 * and read the desired block into it.  If the LRU buffer has data
	 * in it, and input is a pipe, then try to allocate a new buffer first.
E 6
	 */
D 6
	if (autobuf && ispipe && buf_tail->block != (long)(-1))
		(void) ch_addbuf(1);
E 6
I 6
	if (ispipe && buf_tail->block != (long)(-1))
		(void)ch_addbuf(1);
E 6
	bp = buf_tail;
	bp->block = ch_block;
	bp->datasize = 0;

D 6
    read_more:
E 6
I 6
read_more:
E 6
	pos = (ch_block * BUFSIZ) + bp->datasize;
D 6
	if (ispipe)
	{
E 6
I 6
	if (ispipe) {
E 6
		/*
		 * The data requested should be immediately after
		 * the last data read from the pipe.
		 */
D 6
		if (pos != last_piped_pos)
		{
E 6
I 6
		if (pos != last_piped_pos) {
E 6
			error("pipe error");
			quit();
		}
	} else
D 4
		lseek(file, pos, 0);
E 4
I 4
		(void)lseek(file, pos, L_SET);
E 4

	/*
	 * Read the block.
	 * If we read less than a full block, we just return the
	 * partial block and pick up the rest next time.
	 */
	n = iread(file, &bp->data[bp->datasize], BUFSIZ - bp->datasize);
	if (n == READ_INTR)
		return (EOI);
D 6
	if (n < 0)
	{
E 6
I 6
	if (n < 0) {
E 6
		error("read error");
		quit();
	}
	if (ispipe)
		last_piped_pos += n;

I 7
	p = &bp->data[bp->datasize];
E 7
D 3
#if LOGFILE
	/*
	 * If we have a log file, write the new data to it.
	 */
	if (logfile >= 0 && n > 0)
		write(logfile, &bp->data[bp->datasize], n);
#endif

E 3
	bp->datasize += n;

	/*
D 6
	 * Set an EOI marker in the buffered data itself.
	 * Then ensure the data is "clean": there are no 
	 * extra EOI chars in the data and that the "meta"
	 * bit (the 0200 bit) is reset in each char.
E 6
I 6
	 * Set an EOI marker in the buffered data itself.  Then ensure the
	 * data is "clean": there are no extra EOI chars in the data and
D 7
	 * that the "meta" bit (the 0200 bit) is reset in each char.
E 7
I 7
	 * that the "meta" bit (the 0200 bit) is reset in each char;
	 * also translate \r\n sequences to \n if -u flag not set.
E 7
E 6
	 */
D 6
	if (n == 0)
	{
E 6
I 6
	if (n == 0) {
E 6
		ch_fsize = pos;
		bp->data[bp->datasize++] = EOI;
	}

D 6
	if (!clean_data)
	{
		p = &bp->data[bp->datasize];
		while (--n >= 0)
		{
			*--p &= 0177;
			if (*p == EOI)
				*p = '@';
		}
E 6
I 6
D 7
	for (p = &bp->data[bp->datasize]; --n >= 0;) {
		*--p &= 0177;
		if (*p == EOI)
			*p = 0200;
E 7
I 7
	if (bs_mode) {
		for (p = &bp->data[bp->datasize]; --n >= 0;) {
			*--p &= 0177;
			if (*p == EOI)
				*p = 0200;
		}
	}
	else {
		for (t = p; --n >= 0; ++p) {
			ch = *p & 0177;
			if (ch == '\r' && n && (p[1] & 0177) == '\n') {
				++p;
				*t++ = '\n';
			}
			else
				*t++ = (ch == EOI) ? 0200 : ch;
		}
		if (p != t) {
			bp->datasize -= p - t;
			if (ispipe)
				last_piped_pos -= p - t;
		}
E 7
E 6
	}

D 6
    found:
	if (buf_head != bp)
	{
E 6
I 6
found:
	if (buf_head != bp) {
E 6
		/*
		 * Move the buffer to the head of the buffer chain.
		 * This orders the buffer chain, most- to least-recently used.
		 */
		bp->next->prev = bp->prev;
		bp->prev->next = bp->next;

		bp->next = buf_head;
		bp->prev = END_OF_CHAIN;
		buf_head->prev = bp;
		buf_head = bp;
	}

	if (ch_offset >= bp->datasize)
		/*
		 * After all that, we still don't have enough data.
		 * Go back and try again.
		 */
		goto read_more;

D 6
	return (bp->data[ch_offset]);
E 6
I 6
	return(bp->data[ch_offset]);
E 6
}
D 3

#if LOGFILE
/*
 * Close the logfile.
 * If we haven't read all of standard input into it, do that now.
 */
	public void
end_logfile()
{
	static int tried = 0;

	if (logfile < 0)
		return;
	if (!tried && ch_fsize == NULL_POSITION)
	{
		tried = 1;
		ierror("finishing logfile");
		while (ch_forw_get() != EOI)
			if (sigs)
				break;
	}
	close(logfile);
	logfile = -1;
}

/*
 * Start a log file AFTER less has already been running.
 * Invoked from the - command; see toggle_option().
 * Write all the existing buffered data to the log file.
 */
	public void
sync_logfile()
{
	register struct buf *bp;
	register int n;
	long block;
	long last_block;

	last_block = (last_piped_pos + BUFSIZ - 1) / BUFSIZ;
	for (block = 0;  block <= last_block;  block++)
		for (bp = buf_head;  bp != END_OF_CHAIN;  bp = bp->next)
			if (bp->block == block)
			{
				n = bp->datasize;
				if (bp->data[n-1] == EOI)
					n--;
				write(logfile, bp->data, n);
				break;
			}
}

#endif
E 3

/*
 * Determine if a specific block is currently in one of the buffers.
 */
D 6
	static int
E 6
I 6
static
E 6
buffered(block)
	long block;
{
	register struct buf *bp;

D 6
	for (bp = buf_head;  bp != END_OF_CHAIN;  bp = bp->next)
E 6
I 6
	for (bp = buf_head; bp != END_OF_CHAIN; bp = bp->next)
E 6
		if (bp->block == block)
D 6
			return (1);
	return (0);
E 6
I 6
			return(1);
	return(0);
E 6
}

/*
 * Seek to a specified position in the file.
 * Return 0 if successful, non-zero if can't seek there.
 */
D 6
	public int
E 6
ch_seek(pos)
D 6
	register POSITION pos;
E 6
I 6
	register off_t pos;
E 6
{
	long new_block;

	new_block = pos / BUFSIZ;
D 6
	if (!ispipe || pos == last_piped_pos || buffered(new_block))
	{
E 6
I 6
	if (!ispipe || pos == last_piped_pos || buffered(new_block)) {
E 6
		/*
		 * Set read pointer.
		 */
		ch_block = new_block;
		ch_offset = pos % BUFSIZ;
D 6
		return (0);
E 6
I 6
		return(0);
E 6
	}
D 6
	return (1);
E 6
I 6
	return(1);
E 6
}

/*
 * Seek to the end of the file.
 */
D 6
	public int
E 6
ch_end_seek()
{
I 6
	off_t ch_length();

E 6
	if (!ispipe)
D 6
		return (ch_seek(ch_length()));
E 6
I 6
		return(ch_seek(ch_length()));
E 6

	/*
	 * Do it the slow way: read till end of data.
	 */
	while (ch_forw_get() != EOI)
		if (sigs)
D 6
			return (1);
	return (0);
E 6
I 6
			return(1);
	return(0);
E 6
}

/*
 * Seek to the beginning of the file, or as close to it as we can get.
 * We may not be able to seek there if input is a pipe and the
 * beginning of the pipe is no longer buffered.
 */
D 6
	public int
E 6
ch_beg_seek()
{
	register struct buf *bp, *firstbp;

	/*
	 * Try a plain ch_seek first.
	 */
D 6
	if (ch_seek((POSITION)0) == 0)
		return (0);
E 6
I 6
	if (ch_seek((off_t)0) == 0)
		return(0);
E 6

	/*
	 * Can't get to position 0.
	 * Look thru the buffers for the one closest to position 0.
	 */
	firstbp = bp = buf_head;
	if (bp == END_OF_CHAIN)
D 6
		return (1);
E 6
I 6
		return(1);
E 6
	while ((bp = bp->next) != END_OF_CHAIN)
		if (bp->block < firstbp->block)
			firstbp = bp;
	ch_block = firstbp->block;
	ch_offset = 0;
D 6
	return (0);
E 6
I 6
	return(0);
E 6
}

/*
 * Return the length of the file, if known.
 */
D 6
	public POSITION
E 6
I 6
off_t
E 6
ch_length()
{
I 6
	off_t lseek();

E 6
	if (ispipe)
D 6
		return (ch_fsize);
D 2
	return ((POSITION)(lseek(file, (offset_t)0, 2)));
E 2
I 2
	return ((POSITION)(lseek(file, (off_t)0, L_XTND)));
E 6
I 6
		return(ch_fsize);
	return((off_t)(lseek(file, (off_t)0, L_XTND)));
E 6
E 2
}

/*
 * Return the current position in the file.
 */
D 6
	public POSITION
E 6
I 6
off_t
E 6
ch_tell()
{
D 6
	return (ch_block * BUFSIZ + ch_offset);
E 6
I 6
	return(ch_block * BUFSIZ + ch_offset);
E 6
}

/*
 * Get the current char and post-increment the read pointer.
 */
D 6
	public int
E 6
ch_forw_get()
{
	register int c;

	c = ch_get();
D 6
	if (c != EOI && ++ch_offset >= BUFSIZ)
	{
E 6
I 6
	if (c != EOI && ++ch_offset >= BUFSIZ) {
E 6
		ch_offset = 0;
D 6
		ch_block ++;
E 6
I 6
		++ch_block;
E 6
	}
D 6
	return (c);
E 6
I 6
	return(c);
E 6
}

/*
 * Pre-decrement the read pointer and get the new current char.
 */
D 6
	public int
E 6
ch_back_get()
{
D 6
	if (--ch_offset < 0)
	{
		if (ch_block <= 0 || (ispipe && !buffered(ch_block-1)))
		{
E 6
I 6
	if (--ch_offset < 0) {
		if (ch_block <= 0 || (ispipe && !buffered(ch_block-1))) {
E 6
			ch_offset = 0;
D 6
			return (EOI);
E 6
I 6
			return(EOI);
E 6
		}
		ch_offset = BUFSIZ - 1;
		ch_block--;
	}
D 6
	return (ch_get());
E 6
I 6
	return(ch_get());
E 6
}

/*
 * Allocate buffers.
 * Caller wants us to have a total of at least want_nbufs buffers.
 * keep==1 means keep the data in the current buffers;
 * otherwise discard the old data.
 */
D 6
	public void
E 6
ch_init(want_nbufs, keep)
	int want_nbufs;
	int keep;
{
	register struct buf *bp;
	char message[80];

	cbufs = nbufs;
D 6
	if (nbufs < want_nbufs && ch_addbuf(want_nbufs - nbufs))
	{
E 6
I 6
	if (nbufs < want_nbufs && ch_addbuf(want_nbufs - nbufs)) {
E 6
		/*
		 * Cannot allocate enough buffers.
		 * If we don't have ANY, then quit.
		 * Otherwise, just report the error and return.
		 */
D 4
		sprintf(message, "cannot allocate %d buffers",
E 4
I 4
		(void)sprintf(message, "cannot allocate %d buffers",
E 4
D 6
			want_nbufs - nbufs);
E 6
I 6
		    want_nbufs - nbufs);
E 6
		error(message);
		if (nbufs == 0)
			quit();
		return;
	}

	if (keep)
		return;

	/*
	 * We don't want to keep the old data,
	 * so initialize all the buffers now.
	 */
	for (bp = buf_head;  bp != END_OF_CHAIN;  bp = bp->next)
		bp->block = (long)(-1);
D 6
	last_piped_pos = (POSITION)0;
E 6
I 6
	last_piped_pos = (off_t)0;
E 6
	ch_fsize = NULL_POSITION;
D 6
	(void) ch_seek((POSITION)0);
E 6
I 6
	(void)ch_seek((off_t)0);
E 6
}

/*
 * Allocate some new buffers.
 * The buffers are added to the tail of the buffer chain.
 */
D 6
	static int
E 6
I 6
D 10
static
E 10
E 6
ch_addbuf(nnew)
	int nnew;
{
	register struct buf *bp;
	register struct buf *newbufs;
I 6
	char *calloc();
E 6

	/*
	 * We don't have enough buffers.  
	 * Allocate some new ones.
	 */
D 4
	newbufs = (struct buf *) calloc(nnew, sizeof(struct buf));
E 4
I 4
D 6
	newbufs = (struct buf *) calloc((u_int)nnew, sizeof(struct buf));
E 6
I 6
	newbufs = (struct buf *)calloc((u_int)nnew, sizeof(struct buf));
E 6
E 4
	if (newbufs == NULL)
D 6
		return (1);
E 6
I 6
		return(1);
E 6

	/*
	 * Initialize the new buffers and link them together.
	 * Link them all onto the tail of the buffer list.
	 */
	nbufs += nnew;
	cbufs = nbufs;
D 6
	for (bp = &newbufs[0];  bp < &newbufs[nnew];  bp++)
	{
E 6
I 6
	for (bp = &newbufs[0];  bp < &newbufs[nnew];  bp++) {
E 6
		bp->next = bp + 1;
		bp->prev = bp - 1;
		bp->block = (long)(-1);
	}
	newbufs[nnew-1].next = END_OF_CHAIN;
	newbufs[0].prev = buf_tail;
	buf_tail->next = &newbufs[0];
	buf_tail = &newbufs[nnew-1];
D 6
	return (0);
E 6
I 6
	return(0);
E 6
}
E 1
