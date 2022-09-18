h13096
s 00002/00002/00096
d D 8.1 93/05/31 16:41:13 bostic 20 19
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00097
d D 5.14 93/05/22 19:06:14 christos 19 18
c Fixed gcc -Wall warnings
e
s 00016/00434/00082
d D 5.13 92/02/12 20:07:57 christos 18 17
c Use the system's version of malloc
e
s 00017/00016/00499
d D 5.12 92/02/05 16:31:01 christos 17 16
c fixed bug in realloc: copy the min size of the new and old block.
e
s 00001/00002/00514
d D 5.11 91/10/27 15:59:26 christos 16 15
c Minor fixes
e
s 00000/00004/00516
d D 5.10 91/07/28 14:13:07 christos 15 14
c Removed sun ifdef in free()
e
s 00017/00013/00503
d D 5.9 91/07/19 17:30:17 christos 14 13
c stdio based version; brace glob fix; builtin prototypes
e
s 00024/00029/00492
d D 5.8 91/06/08 17:08:31 christos 13 12
c More prototype fixes, Removed TERMIOS define
e
s 00001/00001/00520
d D 5.7 91/06/07 11:13:44 bostic 12 11
c rename all the files (they weren't going to diff anyway)
c add function prototypes for extern functions, decls.h -> extern.h
c delete btell function, VFORK #define, lots of other minor cleanups
e
s 00407/00272/00114
d D 5.6 91/06/04 13:32:04 bostic 11 10
c new version from Christos -- 8-bit clean, lots of bug fixes
c massive changes, including a pass of indent.
e
s 00008/00006/00378
d D 5.5 91/04/04 18:17:28 bostic 10 9
c new copyright; att/bsd/shared
e
s 00001/00000/00383
d D 5.4 91/02/25 08:11:48 bostic 9 8
c ANSI fixes
e
s 00162/00101/00221
d D 5.3 86/03/29 07:21:16 lepreau 8 7
c make csh-specific hacks to libc malloc.c, sid 5.5.
e
s 00003/00003/00319
d D 5.2 85/06/06 13:11:57 edward 7 5
c cleaning up after bozos
e
s 00002/00002/00320
d R 5.2 85/06/06 12:50:55 edward 6 5
c clean up after bozos
e
s 00008/00002/00314
d D 5.1 85/06/04 11:13:08 dist 5 4
c Add copyright
e
s 00023/00031/00293
d D 4.4 84/12/13 14:43:32 edward 4 3
c performance
e
s 00289/00181/00035
d D 4.3 83/11/13 23:35:36 layer 3 2
c new malloc from Caltech.   Better for alloc'ing small chunks of space.
e
s 00001/00001/00215
d D 4.2 83/02/09 14:16:58 sam 2 1
c cleanups from sun
e
s 00216/00000/00000
d D 4.1 80/10/09 12:39:55 bill 1 0
c date and time created 80/10/09 12:39:55 by bill
e
u
U
t
T
I 5
D 10
/*
D 8
 * Copyright (c) 1980 Regents of the University of California.
D 7
 * All rights reserved.  The Berkeley software License Agreement
E 7
I 7
 * All rights reserved.  The Berkeley Software License Agreement
E 8
I 8
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
E 8
E 7
 * specifies the terms and conditions for redistribution.
E 10
I 10
/*-
D 20
 * Copyright (c) 1983, 1991 The Regents of the University of California.
 * All rights reserved.
E 20
I 20
 * Copyright (c) 1983, 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 20
 *
 * %sccs.include.redist.c%
E 10
 */

E 5
I 1
D 3
static	char *sccsid = "%Z%%M% %I% %G%";
E 3
I 3
#ifndef lint
I 10
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

E 10
I 8
D 11
/* From "@(#)malloc.c	5.5 (Berkeley) 2/25/86"; */
E 8
D 5
static	char *sccsid = "%Z%%M% %I% (Berkeley from Caltech) %G%";
#endif
E 5
I 5
D 7
static char sccsid[] = "%W% (Berkeley) %G%";
#endif not lint
E 7
I 7
D 10
static char *sccsid = "%W% (Berkeley) %G%";
D 8
#endif
E 8
I 8
#endif not lint
E 10
E 8
E 7
E 5
E 3

E 11
D 3
#include "sh.local.h"
E 3
I 3
D 18
/*
D 11
 * malloc.c (Caltech) 2/21/82
E 11
I 11
 * tc.alloc.c from malloc.c (Caltech) 2/21/82
E 11
 * Chris Kingsley, kingsley@cit-20.
 *
D 11
 * This is a very fast storage allocator.  It allocates blocks of a small 
E 11
I 11
 * This is a very fast storage allocator.  It allocates blocks of a small
E 11
 * number of different sizes, and keeps free lists of each size.  Blocks that
D 11
 * don't exactly fit are passed up to the next larger size.  In this 
D 8
 * implementation, the available sizes are 2^n-4 (or 2^n-12) bytes long.
 * This is designed for use in a program that uses vast quantities of memory,
 * but bombs when it runs out. 
E 8
I 8
 * implementation, the available sizes are 2^n-4 (or 2^n-10) bytes long.
 * This is designed for use in a virtual memory environment.
E 11
I 11
 * don't exactly fit are passed up to the next larger size.  In this
 * implementation, the available sizes are 2^n-4 (or 2^n-12) bytes long.
 * This is designed for use in a program that uses vast quantities of memory,
 * but bombs when it runs out.
E 11
E 8
 */

E 18
I 13
#include <sys/types.h>
#include <unistd.h>
D 18
#include <string.h>
E 18
I 18
#include <stdlib.h>
E 18
#if __STDC__
# include <stdarg.h>
#else
# include <varargs.h>
#endif

E 13
D 11
#include <sys/types.h>
E 11
I 11
D 12
#include "sh.h"
E 12
I 12
#include "csh.h"
I 13
#include "extern.h"
E 13
E 12
E 11

I 11
char   *memtop = NULL;		/* PWP: top of current memory */
char   *membot = NULL;		/* PWP: bottom of allocatable memory */

D 18
#ifndef SYSMALLOC

#undef RCHECK
#undef DEBUG


#ifndef NULL
E 11
#define	NULL 0
I 11
#endif
E 11

I 11
D 13
typedef unsigned char U_char;	/* we don't really have signed chars */
typedef unsigned int U_int;
typedef unsigned short U_short;
static int findbucket();
static void morecore();
E 13

E 11
/*
 * The overhead on a block is at least 4 bytes.  When free, this space
 * contains a pointer to the next free block, and the bottom two bits must
 * be zero.  When in use, the first byte is set to MAGIC, and the second
 * byte is the size index.  The remaining bytes are for alignment.
D 8
 * If range checking is enabled and the size of the block fits
 * in two bytes, then the top two bytes hold the size of the requested block
 * plus the range checking words, and the header word MINUS ONE.
E 8
I 8
D 11
 * If range checking is enabled then a second word holds the size of the
 * requested block, less 1, rounded up to a multiple of sizeof(RMAGIC).
 * The order of elements is critical: ov_magic must overlay the low order
 * bits of ov_next, and ov_magic can not be a valid ov_next bit pattern.
E 11
I 11
 * If range checking is enabled and the size of the block fits
 * in two bytes, then the top two bytes hold the size of the requested block
 * plus the range checking words, and the header word MINUS ONE.
E 11
E 8
 */
D 11
union	overhead {
	union	overhead *ov_next;	/* when free */
	struct {
		u_char	ovu_magic;	/* magic number */
		u_char	ovu_index;	/* bucket # */
E 11
I 11

D 13
#ifdef SUNOS4
/*
 * SunOS localtime() overwrites the 9th byte on an 8 byte malloc()....
 * So we align to 16 bytes...
 */
#define ROUNDUP	15
#else
E 13
#define ROUNDUP	7
D 13
#endif
E 13

D 17
#define ALIGN(a) (((a) + ROUNDUP) & ~ROUNDUP)
E 17
I 17
#define MEMALIGN(a) (((a) + ROUNDUP) & ~ROUNDUP)
E 17

union overhead {
    union overhead *ov_next;	/* when free */
    struct {
D 13
	U_char  ovu_magic;	/* magic number */
	U_char  ovu_index;	/* bucket # */
E 13
I 13
	u_char  ovu_magic;	/* magic number */
	u_char  ovu_index;	/* bucket # */
E 13
E 11
#ifdef RCHECK
D 8
		u_short	ovu_size;	/* actual block size */
		u_int	ovu_rmagic;	/* range magic number */
E 8
I 8
D 11
		u_short	ovu_rmagic;	/* range magic number */
		u_int	ovu_size;	/* actual block size */
E 11
I 11
D 13
	U_short ovu_size;	/* actual block size */
	U_int   ovu_rmagic;	/* range magic number */
E 13
I 13
	u_short ovu_size;	/* actual block size */
	u_int   ovu_rmagic;	/* range magic number */
E 13
E 11
E 8
#endif
D 11
	} ovu;
E 11
I 11
    }       ovu;
E 11
#define	ov_magic	ovu.ovu_magic
#define	ov_index	ovu.ovu_index
D 8
#define	ov_size		ovu.ovu_size
E 8
D 11
#define	ov_rmagic	ovu.ovu_rmagic
E 11
I 8
#define	ov_size		ovu.ovu_size
I 11
#define	ov_rmagic	ovu.ovu_rmagic
E 11
E 8
};

D 8
#define	MAGIC		0xff		/* magic # on accounting info */
#define RMAGIC		0x55555555	/* magic # on range info */
E 8
I 8
D 11
#define	MAGIC		0xef		/* magic # on accounting info */
#define RMAGIC		0x5555		/* magic # on range info */

E 11
I 11
#define	MAGIC		0xfd	/* magic # on accounting info */
#define RMAGIC		0x55555555	/* magic # on range info */
E 11
E 8
#ifdef RCHECK
D 8
#define	RSLOP		sizeof (u_int)
E 8
I 8
D 11
#define	RSLOP		sizeof (u_short)
E 11
I 11
D 13
#define	RSLOP		sizeof (U_int)
E 13
I 13
#define	RSLOP		sizeof (u_int)
E 13
E 11
E 8
#else
#define	RSLOP		0
#endif

/*
 * nextf[i] is the pointer to the next free block of size 2^(i+3).  The
 * smallest allocatable block is 8 bytes.  The overhead information
 * precedes the data area returned to the user.
 */
#define	NBUCKETS 30
D 11
static	union overhead *nextf[NBUCKETS];
extern	char *sbrk();
E 11
I 11
static union overhead *nextf[NBUCKETS];
E 11

I 8
D 11
static	int pagesz;			/* page size */
static	int pagebucket;			/* page size bucket */
E 11
I 11
D 13
#ifdef notdef
extern char *sbrk();
E 13
I 13
static int	findbucket __P((union overhead *, int));
static void	morecore __P((int));
E 13
E 11

I 11
D 13
#endif

E 13
E 11
E 8
E 3
D 4
#ifdef debug
E 4
D 3
#define ASSERT(p) if(!(p))botch("p");else
E 3
I 3
/*
 * nmalloc[i] is the difference between the number of mallocs and frees
 * for a given block size.
 */
D 11
static	u_int nmalloc[NBUCKETS];
E 11
I 11
D 13
static U_int nmalloc[NBUCKETS];
E 13
I 13
static u_int nmalloc[NBUCKETS];
E 13
E 11
D 4
#endif
E 4

D 8
#ifdef debug
#define	ASSERT(p)   if (!(p)) botch("p"); else
E 8
I 8
D 11
#if defined(DEBUG) || defined(RCHECK)
#define	ASSERT(p)   if (!(p)) botch("p")
E 8
static
E 3
botch(s)
D 8
char *s;
E 8
I 8
	char *s;
E 8
{
D 8
	printf("assertion botched: %s\n",s);
E 8
I 8
	printf("\r\nassertion botched: %s\r\n", s);
E 8
	abort();
}
E 11
I 11

#ifdef DEBUG
#define CHECK(a, str, p) \
    if (a) { \
D 14
	xprintf(str, p);	\
	xprintf("memtop = %lx membot = %lx.\n", memtop, membot);	\
E 14
I 14
	(void) fprintfcsherr, (str, p);	\
	(void) fprintf(csherr, "memtop = %lx membot = %lx.\n", memtop, membot);\
E 14
	abort(); \
    }	\
    else
E 11
#else
D 3
#define ASSERT(p)
E 3
I 3
D 11
#define	ASSERT(p)
E 11
I 11
#define CHECK(a, str, p) \
    if (a) { \
D 14
	xprintf(str, p);	\
	xprintf("memtop = %lx membot = %lx.\n", memtop, membot);	\
E 14
I 14
	(void) fprintf(csherr, str, p);	\
	(void) fprintf(csherr, "memtop = %lx membot = %lx.\n", memtop, membot);\
E 14
	return; \
    }	\
    else
E 11
E 3
#endif

E 18
D 3
/*	avoid break bug */
#ifdef pdp11
#define GRANULE 64
#else
#define GRANULE 0
#endif
/*	C storage allocator
 *	circular first-fit strategy
 *	works with noncontiguous, but monotonically linked, arena
 *	each block is preceded by a ptr to the (pointer of) 
 *	the next following block
 *	blocks are exact number of words long 
 *	aligned to the data type requirements of ALIGN
 *	pointers to blocks must have BUSY bit 0
 *	bit in ptr is 1 for busy, 0 for idle
 *	gaps in arena are merely noted as busy blocks
 *	last block of arena (pointed to by alloct) is empty and
 *	has a pointer to first
 *	idle blocks are coalesced during space search
 *
 *	a different implementation may need to redefine
 *	ALIGN, NALIGN, BLOCK, BUSY, INT
 *	where INT is integer type to which a pointer can be cast
*/
#define INT int
#define ALIGN int
#define NALIGN 1
#define WORD sizeof(union store)
#define BLOCK 1024	/* a multiple of WORD*/
#define BUSY 1
#define NULL 0
#define testbusy(p) ((INT)(p)&BUSY)
#define setbusy(p) (union store *)((INT)(p)|BUSY)
#define clearbusy(p) (union store *)((INT)(p)&~BUSY)

union store { union store *ptr;
	      ALIGN dummy[NALIGN];
	      int calloc;	/*calloc clears an array of integers*/
};

static	union store allocs[2];	/*initial arena*/
static	union store *allocp;	/*search ptr*/
static	union store *alloct;	/*arena top*/
static	union store *allocx;	/*for benefit of realloc*/
char	*sbrk();

E 3
D 11
char *
E 11
I 11
ptr_t
E 11
D 18
malloc(nbytes)
D 3
unsigned nbytes;
E 3
I 3
D 8
	register unsigned nbytes;
E 8
I 8
D 11
	unsigned nbytes;
E 11
I 11
    register size_t nbytes;
E 11
E 8
E 3
{
D 3
	register union store *p, *q;
	register nw;
	static temp;	/*coroutines assume no auto*/
E 3
I 3
D 8
  	register union overhead *p;
  	register int bucket = 0;
  	register unsigned shiftr;
E 8
I 8
D 11
  	register union overhead *op;
  	register int bucket;
	register unsigned amt, n;
E 11
I 11
#ifndef lint
    register union overhead *p;
    register int bucket = 0;
    register unsigned shiftr;
E 11
E 8
E 3

D 3
	if(allocs[0].ptr==0) {	/*first time*/
		allocs[0].ptr = setbusy(&allocs[1]);
		allocs[1].ptr = setbusy(&allocs[0]);
		alloct = &allocs[1];
		allocp = &allocs[0];
	}
	nw = (nbytes+WORD+WORD-1)/WORD;
	ASSERT(allocp>=allocs && allocp<=alloct);
	ASSERT(allock());
	for(p=allocp; ; ) {
		for(temp=0; ; ) {
			if(!testbusy(p->ptr)) {
				while(!testbusy((q=p->ptr)->ptr)) {
					ASSERT(q>p&&q<alloct);
					p->ptr = q->ptr;
				}
				if(q>=p+nw && p+nw>=p)
					goto found;
			}
			q = p;
			p = clearbusy(p->ptr);
			if(p>q)
				ASSERT(p<=alloct);
			else if(q!=alloct || p!=allocs) {
				ASSERT(q==alloct&&p==allocs);
				return(NULL);
			} else if(++temp>1)
				break;
		}
		temp = ((nw+BLOCK/WORD)/(BLOCK/WORD))*(BLOCK/WORD);
		q = (union store *)sbrk(0);
		if(q+temp+GRANULE < q) {
			return(NULL);
		}
		q = (union store *)sbrk(temp*WORD);
		if((INT)q == -1) {
			return(NULL);
		}
		ASSERT(q>alloct);
		alloct->ptr = q;
		if(q!=alloct+1)
			alloct->ptr = setbusy(alloct->ptr);
		alloct = q->ptr = q+temp-1;
		alloct->ptr = setbusy(allocs);
	}
found:
	allocp = p + nw;
	ASSERT(allocp<=alloct);
	if(q>allocp) {
		allocx = allocp->ptr;
		allocp->ptr = p->ptr;
	}
	p->ptr = setbusy(allocp);
	return((char *)(p+1));
E 3
I 3
D 11
	/*
D 8
	 * Convert amount of memory requested into
	 * closest block size stored in hash buckets
	 * which satisfies request.  Account for
	 * space used per block for accounting.
E 8
I 8
	 * First time malloc is called, setup page size and
	 * align break pointer so all data will be page aligned.
E 8
	 */
D 8
  	nbytes += sizeof (union overhead) + RSLOP;
  	nbytes = (nbytes + 3) &~ 3; 
  	shiftr = (nbytes - 1) >> 2;
	/* apart from this loop, this is O(1) */
  	while (shiftr >>= 1)
  		bucket++;
E 8
I 8
	if (pagesz == 0) {
		pagesz = n = getpagesize();
		op = (union overhead *)sbrk(0);
  		n = n - sizeof (*op) - ((int)op & (n - 1));
		if (n < 0)
			n += pagesz;
  		if (n) {
  			if (sbrk(n) == (char *)-1)
				return (NULL);
		}
		bucket = 0;
		amt = 8;
		while (pagesz > amt) {
			amt <<= 1;
			bucket++;
		}
		pagebucket = bucket;
	}
E 8
	/*
I 8
	 * Convert amount of memory requested into closest block size
	 * stored in hash buckets which satisfies request.
	 * Account for space used per block for accounting.
	 */
	if (nbytes <= (n = pagesz - sizeof (*op) - RSLOP)) {
#ifndef RCHECK
		amt = 8;	/* size of first bucket */
		bucket = 0;
E 11
I 11
    /*
     * Convert amount of memory requested into closest block size stored in
     * hash buckets which satisfies request.  Account for space used per block
     * for accounting.
     */
D 17
    nbytes = ALIGN(ALIGN(sizeof(union overhead)) + nbytes + RSLOP);
E 17
I 17
    nbytes = MEMALIGN(MEMALIGN(sizeof(union overhead)) + nbytes + RSLOP);
E 17
    shiftr = (nbytes - 1) >> 2;

    /* apart from this loop, this is O(1) */
    while (shiftr >>= 1)
	bucket++;
    /*
     * If nothing in hash bucket right now, request more memory from the
     * system.
     */
    if (nextf[bucket] == NULL)
	morecore(bucket);
    if ((p = (union overhead *) nextf[bucket]) == NULL) {
	child++;
#ifndef DEBUG
	stderror(ERR_NOMEM);
E 11
#else
D 11
		amt = 16;	/* size of first bucket */
		bucket = 1;
E 11
I 11
	showall();
D 14
	xprintf("nbytes=%d: Out of memory\n", nbytes);
E 14
I 14
	(void) fprintf(csherr, "nbytes=%d: Out of memory\n", nbytes);
E 14
	abort();
E 11
#endif
D 11
		n = -(sizeof (*op) + RSLOP);
	} else {
		amt = pagesz;
		bucket = pagebucket;
	}
	while (nbytes > amt + n) {
		amt <<= 1;
		if (amt == 0)
			return (NULL);
		bucket++;
	}
	/*
E 8
	 * If nothing in hash bucket right now,
	 * request more memory from the system.
	 */
D 8
  	if (nextf[bucket] == NULL)    
E 8
I 8
  	if ((op = nextf[bucket]) == NULL) {
E 8
  		morecore(bucket);
D 8
  	if ((p = (union overhead *)nextf[bucket]) == NULL)
  		return (NULL);
E 8
I 8
  		if ((op = nextf[bucket]) == NULL)
  			return (NULL);
	}
E 8
	/* remove from linked list */
D 8
  	nextf[bucket] = nextf[bucket]->ov_next;
	p->ov_magic = MAGIC;
	p->ov_index= bucket;
E 8
I 8
  	nextf[bucket] = op->ov_next;
	op->ov_magic = MAGIC;
	op->ov_index = bucket;
E 8
D 4
#ifdef debug
E 4
  	nmalloc[bucket]++;
E 11
I 11
	/* fool lint */
	return ((ptr_t) 0);
    }
    /* remove from linked list */
    nextf[bucket] = nextf[bucket]->ov_next;
    p->ov_magic = MAGIC;
    p->ov_index = bucket;
    nmalloc[bucket]++;
E 11
D 4
#endif
E 4
#ifdef RCHECK
D 11
	/*
	 * Record allocated size of block and
	 * bound space with magic numbers.
	 */
D 8
  	if (nbytes <= 0x10000)
		p->ov_size = nbytes - 1;
	p->ov_rmagic = RMAGIC;
  	*((u_int *)((caddr_t)p + nbytes - RSLOP)) = RMAGIC;
E 8
I 8
	op->ov_size = (nbytes + RSLOP - 1) & ~(RSLOP - 1);
	op->ov_rmagic = RMAGIC;
  	*(u_short *)((caddr_t)(op + 1) + op->ov_size) = RMAGIC;
E 11
I 11
    /*
     * Record allocated size of block and bound space with magic numbers.
     */
    if (nbytes <= 0x10000)
	p->ov_size = nbytes - 1;
    p->ov_rmagic = RMAGIC;
D 13
    *((U_int *) (((caddr_t) p) + nbytes - RSLOP)) = RMAGIC;
E 13
I 13
    *((u_int *) (((caddr_t) p) + nbytes - RSLOP)) = RMAGIC;
E 13
E 11
E 8
#endif
D 8
  	return ((char *)(p + 1));
E 8
I 8
D 11
  	return ((char *)(op + 1));
E 11
I 11
D 17
    return ((ptr_t) (((caddr_t) p) + ALIGN(sizeof(union overhead))));
E 17
I 17
    return ((ptr_t) (((caddr_t) p) + MEMALIGN(sizeof(union overhead))));
E 17
#else
    if (nbytes)
	return ((ptr_t) 0);
    else
	return ((ptr_t) 0);
#endif				/* !lint */
E 11
E 8
E 3
}

I 11
#ifndef lint
E 11
D 3
/*	freeing strategy tuned for LIFO allocation
*/
free(ap)
register char *ap;
E 3
I 3
/*
 * Allocate more memory to the indicated bucket.
 */
I 11
static void
E 11
D 8
static
E 8
morecore(bucket)
D 8
	register bucket;
E 8
I 8
D 11
	int bucket;
E 11
I 11
D 13
    register bucket;
E 13
I 13
    register int bucket;
E 13
E 11
E 8
E 3
{
D 3
	register union store *p = (union store *)ap;
E 3
I 3
D 11
  	register union overhead *op;
D 8
  	register int rnu;       /* 2^rnu bytes will be requested */
  	register int nblks;     /* become nblks blocks of the desired size */
	register int siz;
E 8
I 8
	register int sz;		/* size of desired block */
  	int amt;			/* amount to allocate */
  	int nblks;			/* how many blocks we get */
E 11
I 11
    register union overhead *op;
    register int rnu;		/* 2^rnu bytes will be requested */
    register int nblks;		/* become nblks blocks of the desired size */
    register int siz;
E 11
E 8
E 3

D 3
	ASSERT(p>clearbusy(allocs[1].ptr)&&p<=alloct);
	ASSERT(allock());
	allocp = --p;
/* 	ASSERT(testbusy(p->ptr)); */
	p->ptr = clearbusy(p->ptr);
	ASSERT(p->ptr > allocp && p->ptr <= alloct);
E 3
I 3
D 8
  	if (nextf[bucket])
  		return;
E 8
D 11
	/*
D 8
	 * Insure memory is allocated
	 * on a page boundary.  Should
	 * make getpageize call?
E 8
I 8
	 * sbrk_size <= 0 only for big, FLUFFY, requests (about
	 * 2^30 bytes on a VAX, I think) or for a negative arg.
E 8
	 */
D 8
  	op = (union overhead *)sbrk(0);
  	if ((int)op & 0x3ff)
D 4
  		sbrk(1024 - ((int)op & 0x3ff));
E 4
I 4
  		(void) sbrk(1024 - ((int)op & 0x3ff));
E 4
	/* take 2k unless the block is bigger than that */
  	rnu = (bucket <= 8) ? 11 : bucket + 3;
  	nblks = 1 << (rnu - (bucket + 3));  /* how many blocks to get */
  	if (rnu < bucket)
		rnu = bucket;
	op = (union overhead *)sbrk(1 << rnu);
E 8
I 8
	sz = 1 << (bucket + 3);
#ifdef DEBUG
	ASSERT(sz > 0);
#else
	if (sz <= 0)
		return;
#endif
	if (sz < pagesz) {
		amt = pagesz;
  		nblks = amt / sz;
	} else {
		amt = sz + pagesz;
		nblks = 1;
	}
	op = (union overhead *)sbrk(amt);
E 8
	/* no more room! */
  	if ((int)op == -1)
  		return;
	/*
D 8
	 * Round up to minimum allocation size boundary
	 * and deduct from block count to reflect.
	 */
  	if ((int)op & 7) {
  		op = (union overhead *)(((int)op + 8) &~ 7);
  		nblks--;
  	}
	/*
E 8
	 * Add new memory allocated to that on
	 * free list for this hash bucket.
	 */
  	nextf[bucket] = op;
D 8
  	siz = 1 << (bucket + 3);
E 8
  	while (--nblks > 0) {
D 8
		op->ov_next = (union overhead *)((caddr_t)op + siz);
		op = (union overhead *)((caddr_t)op + siz);
E 8
I 8
		op->ov_next = (union overhead *)((caddr_t)op + sz);
		op = (union overhead *)((caddr_t)op + sz);
E 8
  	}
E 11
I 11
    if (nextf[bucket])
	return;
    /*
     * Insure memory is allocated on a page boundary.  Should make getpageize
     * call?
     */
    op = (union overhead *) sbrk(0);
    memtop = (char *) op;
    if (membot == NULL)
	membot = memtop;
    if ((int) op & 0x3ff) {
	memtop = (char *) sbrk(1024 - ((int) op & 0x3ff));
	memtop += 1024 - ((int) op & 0x3ff);
    }

    /* take 2k unless the block is bigger than that */
    rnu = (bucket <= 8) ? 11 : bucket + 3;
    nblks = 1 << (rnu - (bucket + 3));	/* how many blocks to get */
D 16
    if (rnu < bucket)
	rnu = bucket;
E 16
    memtop = (char *) sbrk(1 << rnu);	/* PWP */
    op = (union overhead *) memtop;
    memtop += 1 << rnu;
    /* no more room! */
    if ((int) op == -1)
	return;
    /*
     * Round up to minimum allocation size boundary and deduct from block count
     * to reflect.
     */
D 13
    if (((U_int) op) & ROUNDUP) {
	op = (union overhead *) (((U_int) op + (ROUNDUP + 1)) & ~ROUNDUP);
E 13
I 13
    if (((u_int) op) & ROUNDUP) {
	op = (union overhead *) (((u_int) op + (ROUNDUP + 1)) & ~ROUNDUP);
E 13
	nblks--;
    }
    /*
     * Add new memory allocated to that on free list for this hash bucket.
     */
    nextf[bucket] = op;
    siz = 1 << (bucket + 3);
    while (--nblks > 0) {
	op->ov_next = (union overhead *) (((caddr_t) op) + siz);
	op = (union overhead *) (((caddr_t) op) + siz);
    }
I 16
    op->ov_next = NULL;
E 16
E 11
E 3
}

D 3
/*	realloc(p, nbytes) reallocates a block obtained from malloc()
 *	and freed since last call of malloc()
 *	to have new size nbytes, and old content
 *	returns new location, or 0 on failure
*/
E 3
I 3
D 11
free(cp)
	char *cp;
{   
  	register int size;
	register union overhead *op;
E 11
I 11
#endif
E 11
E 3

D 3
char *
realloc(p, nbytes)
register union store *p;
unsigned nbytes;
{
	register union store *q;
	union store *s, *t;
	register unsigned nw;
	unsigned onw;
E 3
I 3
D 11
  	if (cp == NULL)
  		return;
	op = (union overhead *)((caddr_t)cp - sizeof (union overhead));
E 3
D 8

E 8
D 3
	if(testbusy(p[-1].ptr))
		free((char *)p);
	onw = p[-1].ptr - p;
	q = (union store *)malloc(nbytes);
	if(q==NULL || q==p)
		return((char *)q);
	s = p;
	t = q;
	nw = (nbytes+WORD-1)/WORD;
	if(nw<onw)
		onw = nw;
	while(onw--!=0)
#ifdef	V6
		copy(t++, s++, sizeof (*t));
E 3
I 3
	/* 
D 8
	** The following botch is because csh tries to free a free block
	** when processing the =~ or !~ operators. -- layer@ucbmonet
E 8
I 8
	 * The following botch is because csh tries to free a free block
	 * when processing the =~ or !~ operators. -- layer@ucbmonet
E 8
	*/
D 8
#ifdef CSHbotch /* was debug */
E 8
I 8
#ifdef CSHbotch /* was DEBUG */
E 8
  	ASSERT(op->ov_magic == MAGIC);		/* make sure it was in use */
E 11
I 11
D 15
#ifdef sun
int
E 11
E 3
#else
E 15
D 3
		*t++ = *s++;
E 3
I 3
D 11
	if (op->ov_magic != MAGIC)
		return;				/* sanity */
E 11
I 11
void
E 11
E 3
D 15
#endif
E 15
I 11
free(cp)
    ptr_t   cp;
{
#ifndef lint
    register int size;
    register union overhead *op;

    if (cp == NULL)
	return;
    CHECK(!memtop || !membot, "free(%lx) called before any allocations.", cp);
    CHECK(cp > (ptr_t) memtop, "free(%lx) above top of memory.", cp);
    CHECK(cp < (ptr_t) membot, "free(%lx) above top of memory.", cp);
D 17
    op = (union overhead *) (((caddr_t) cp) - ALIGN(sizeof(union overhead)));
E 17
I 17
    op = (union overhead *) (((caddr_t) cp) - MEMALIGN(sizeof(union overhead)));
E 17
    CHECK(op->ov_magic != MAGIC, "free(%lx) bad block.", cp);

E 11
D 3
	if(q<p && q+nw>=p)
		(q+(q+nw-p))->ptr = allocx;
	return((char *)q);
}
E 3
D 8

E 8
I 3
#ifdef RCHECK
D 11
  	ASSERT(op->ov_rmagic == RMAGIC);
D 8
	if (op->ov_index <= 13)
		ASSERT(*(u_int *)((caddr_t)op + op->ov_size + 1 - RSLOP) == RMAGIC);
E 8
I 8
	ASSERT(*(u_short *)((caddr_t)(op + 1) + op->ov_size) == RMAGIC);
E 11
I 11
    if (op->ov_index <= 13)
D 13
	CHECK(*(U_int *) ((caddr_t) op + op->ov_size + 1 - RSLOP) != RMAGIC,
E 13
I 13
	CHECK(*(u_int *) ((caddr_t) op + op->ov_size + 1 - RSLOP) != RMAGIC,
E 13
	      "free(%lx) bad range check.", cp);
E 11
E 8
#endif
D 8
  	ASSERT(op->ov_index < NBUCKETS);
E 8
D 11
  	size = op->ov_index;
D 8
	op->ov_next = nextf[size];
E 8
I 8
  	ASSERT(size < NBUCKETS);
	op->ov_next = nextf[size];	/* also clobbers ov_magic */
E 8
  	nextf[size] = op;
E 3
D 4
#ifdef debug
E 4
D 3
allock()
{
#ifdef longdebug
	register union store *p;
	int x;
	x = 0;
	for(p= &allocs[0]; clearbusy(p->ptr) > p; p=clearbusy(p->ptr)) {
		if(p==allocp)
			x++;
	}
	ASSERT(p==alloct);
	return(x==1|p==allocp);
#else
	return(1);
E 3
I 3
  	nmalloc[size]--;
E 11
I 11
    CHECK(op->ov_index >= NBUCKETS, "free(%lx) bad block index.", cp);
    size = op->ov_index;
    op->ov_next = nextf[size];
    nextf[size] = op;

    nmalloc[size]--;

#else
    if (cp == NULL)
	return;
#endif
E 11
E 3
D 4
#endif
E 4
}
D 3
#endif
E 3

I 11
ptr_t
calloc(i, j)
    size_t  i, j;
{
#ifndef lint
    register char *cp, *scp;

    i *= j;
    scp = cp = (char *) xmalloc((size_t) i);
    if (i != 0)
	do
	    *cp++ = 0;
	while (--i);

    return (scp);
#else
    if (i && j)
	return ((ptr_t) 0);
    else
	return ((ptr_t) 0);
#endif
}

E 11
I 3
/*
 * When a program attempts "storage compaction" as mentioned in the
 * old malloc man page, it realloc's an already freed block.  Usually
 * this is the last block it freed; occasionally it might be farther
 * back.  We have to search all the free lists for the block in order
 * to determine its bucket: 1st we make one pass thru the lists
 * checking only the first block in each; if that fails we search
 * ``realloc_srchlen'' blocks in each list for a match (the variable
 * is extern so the caller can modify it).  If that fails we just copy
 * however many bytes was given to realloc() and hope it's not huge.
 */
D 8
int realloc_srchlen = 4;	/* 4 should be plenty.  -1 means whole list */
E 8
I 8
D 11
int realloc_srchlen = 4;	/* 4 should be plenty, -1 =>'s whole list */
E 11
I 11
#ifndef lint
int     realloc_srchlen = 4;	/* 4 should be plenty, -1 =>'s whole list */
I 17
#endif /* lint */
E 17
E 11
E 8

D 11
char *
E 11
I 11
D 17
#endif				/* lint */

E 17
ptr_t
E 11
realloc(cp, nbytes)
D 11
	char *cp; 
	unsigned nbytes;
{   
D 8
  	register u_int onb;
E 8
I 8
  	register u_int onb, i;
E 8
	union overhead *op;
  	char *res;
D 8
	register int i;
E 8
	int was_alloced = 0;
I 9
	static int findbucket();
E 11
I 11
    ptr_t   cp;
    size_t  nbytes;
{
#ifndef lint
D 13
    register U_int onb;
E 13
I 13
    register u_int onb;
E 13
    union overhead *op;
    char   *res;
    register int i;
    int     was_alloced = 0;
E 11
E 9

D 11
  	if (cp == NULL)
  		return (malloc(nbytes));
	op = (union overhead *)((caddr_t)cp - sizeof (union overhead));
	if (op->ov_magic == MAGIC) {
		was_alloced++;
		i = op->ov_index;
D 8
	}
	else {		/* already free: he is doing "compaction" (tee hee) */
E 8
I 8
	} else {
		/*
		 * Already free, doing "compaction".
		 *
		 * Search for the old block of memory on the
		 * free list.  First, check the most common
		 * case (last element free'd), then (this failing)
		 * the last ``realloc_srchlen'' items free'd.
		 * If all lookups fail, then assume the size of
		 * the memory block being realloc'd is the
		 * largest possible (so that all "nbytes" of new
		 * memory are copied into).  Note that this could cause
		 * a memory fault if the old area was tiny, and the moon
		 * is gibbous.  However, that is very unlikely.
		 */
E 8
		if ((i = findbucket(op, 1)) < 0 &&
		    (i = findbucket(op, realloc_srchlen)) < 0)
D 8
			i = 0;		/* assume smallest possible */
E 8
I 8
			i = NBUCKETS;
E 8
	}
D 8
	onb = (1 << (i + 3)) - sizeof (*op) - RSLOP;
	if (was_alloced &&		/* avoid the copy if same size block */
	    nbytes <= onb && nbytes > (onb >> 1) - sizeof(*op) - RSLOP)
		return(cp);
E 8
I 8
	onb = 1 << (i + 3);
	if (onb < pagesz)
		onb -= sizeof (*op) + RSLOP;
	else
		onb += pagesz - sizeof (*op) - RSLOP;
	/* avoid the copy if same size block */
	if (was_alloced) {
		if (i) {
			i = 1 << (i + 2);
			if (i < pagesz)
				i -= sizeof (*op) + RSLOP;
			else
				i += pagesz - sizeof (*op) - RSLOP;
		}
		if (nbytes <= onb && nbytes > i) {
#ifdef RCHECK
			op->ov_size = (nbytes + RSLOP - 1) & ~(RSLOP - 1);
			*(u_short *)((caddr_t)(op + 1) + op->ov_size) = RMAGIC;
#endif
			return(cp);
		} else
			free(cp);
	}
E 8
  	if ((res = malloc(nbytes)) == NULL)
  		return (NULL);
D 8
  	if (cp != res)			/* common optimization */
E 8
I 8
  	if (cp != res)		/* common optimization if "compacting" */
E 8
		bcopy(cp, res, (nbytes < onb) ? nbytes : onb);
D 8
  	if (was_alloced)
		free(cp);
E 8
  	return (res);
E 11
I 11
    if (cp == NULL)
	return (malloc(nbytes));
D 17
    op = (union overhead *) (((caddr_t) cp) - ALIGN(sizeof(union overhead)));
E 17
I 17
    op = (union overhead *) (((caddr_t) cp) - MEMALIGN(sizeof(union overhead)));
E 17
    if (op->ov_magic == MAGIC) {
	was_alloced++;
	i = op->ov_index;
    }
    else
	/*
	 * Already free, doing "compaction".
	 * 
D 17
	 * Search for the old block of memory on the free list.  First, check the
	 * most common case (last element free'd), then (this failing) the last
	 * ``realloc_srchlen'' items free'd. If all lookups fail, then assume
	 * the size of the memory block being realloc'd is the smallest
	 * possible.
E 17
I 17
	 * Search for the old block of memory on the free list.  First, check 
	 * the most common case (last element free'd), then (this failing) 
	 * the last ``realloc_srchlen'' items free'd. If all lookups fail, 
	 * then assume the size of the memory block being realloc'd is the 
	 * smallest possible.
E 17
	 */
	if ((i = findbucket(op, 1)) < 0 &&
	    (i = findbucket(op, realloc_srchlen)) < 0)
	i = 0;

D 17
    onb = ALIGN(nbytes + ALIGN(sizeof(union overhead)) + RSLOP);
E 17
I 17
    onb = MEMALIGN(nbytes + MEMALIGN(sizeof(union overhead)) + RSLOP);
E 17

    /* avoid the copy if same size block */
    if (was_alloced && (onb < (1 << (i + 3))) && (onb >= (1 << (i + 2))))
	return ((ptr_t) cp);
    if ((res = malloc(nbytes)) == NULL)
	return ((ptr_t) 0);
D 17
    if (cp != res)		/* common optimization */
	bcopy(cp, res, nbytes);
E 17
I 17
    if (cp != res) {		/* common optimization */
	onb = (1 << (i + 3)) - MEMALIGN(sizeof(union overhead)) - RSLOP;
	bcopy(cp, res, onb < nbytes ? onb : nbytes);
    }
E 17
    if (was_alloced)
	free(cp);
    return (res);
#else
    if (cp && nbytes)
	return ((ptr_t) 0);
    else
	return ((ptr_t) 0);
D 17
#endif				/* !lint */
E 17
I 17
#endif /* !lint */
E 17
E 11
}

I 11


#ifndef lint
E 11
/*
 * Search ``srchlen'' elements of each free list for a block whose
 * header starts at ``freep''.  If srchlen is -1 search the whole list.
 * Return bucket number, or -1 if not found.
 */
D 11
static
E 11
I 11
static int
E 11
findbucket(freep, srchlen)
D 8
union overhead *freep;
int srchlen;
E 8
I 8
D 11
	union overhead *freep;
	int srchlen;
E 11
I 11
    union overhead *freep;
    int     srchlen;
E 11
E 8
{
D 11
	register union overhead *p;
	register int i, j;
E 11
I 11
    register union overhead *p;
    register int i, j;
E 11

D 8
	for (i = 0; i < NBUCKETS; i++)
		for (j = 0, p = nextf[i]; p && j != srchlen; j++, p = p->ov_next)
E 8
I 8
D 11
	for (i = 0; i < NBUCKETS; i++) {
		j = 0;
		for (p = nextf[i]; p && j != srchlen; p = p->ov_next) {
E 8
			if (p == freep)
				return (i);
I 8
			j++;
		}
E 11
I 11
    for (i = 0; i < NBUCKETS; i++) {
	j = 0;
	for (p = nextf[i]; p && j != srchlen; p = p->ov_next) {
	    if (p == freep)
		return (i);
	    j++;
E 11
	}
E 8
D 11
	return (-1);
E 11
I 11
    }
    return (-1);
E 11
}

I 11
#endif


#else				/* SYSMALLOC */

/**
 ** ``Protected versions'' of malloc, realloc, calloc, and free
 **
 ** On many systems:
 **
 ** 1. malloc(0) is bad
 ** 2. free(0) is bad
 ** 3. realloc(0, n) is bad
 ** 4. realloc(n, 0) is bad
 **
 ** Also we call our error routine if we run out of memory.
 **/
char   *
E 18
Malloc(n)
    size_t  n;
{
    ptr_t   ptr;

D 18
    n = n ? n : 1;

E 18
I 18
    if (membot == NULL)
	memtop = membot = sbrk(0);
E 18
    if ((ptr = malloc(n)) == (ptr_t) 0) {
	child++;
	stderror(ERR_NOMEM);
    }
D 18
    return ((char *) ptr);
E 18
I 18
    return (ptr);
E 18
}

D 18
char   *
E 18
I 18
ptr_t
E 18
Realloc(p, n)
    ptr_t   p;
    size_t  n;
{
    ptr_t   ptr;

D 18
    n = n ? n : 1;
    if ((ptr = (p ? realloc(p, n) : malloc(n))) == (ptr_t) 0) {
E 18
I 18
    if (membot == NULL)
	memtop = membot = sbrk(0);
    if ((ptr = realloc(p, n)) == (ptr_t) 0) {
E 18
	child++;
	stderror(ERR_NOMEM);
    }
D 18
    return ((char *) ptr);
E 18
I 18
    return (ptr);
E 18
}

D 18
char   *
E 18
I 18
ptr_t
E 18
Calloc(s, n)
    size_t  s, n;
{
D 18
    char   *sptr;
E 18
    ptr_t   ptr;

D 18
    n *= s;
    n = n ? n : 1;
    if ((ptr = malloc(n)) == (ptr_t) 0) {
E 18
I 18
    if (membot == NULL)
	memtop = membot = sbrk(0);
    if ((ptr = calloc(s, n)) == (ptr_t) 0) {
E 18
	child++;
	stderror(ERR_NOMEM);
    }

D 18
    sptr = (char *) ptr;
    if (n != 0)
	do
	    *sptr++ = 0;
	while (--n);

    return ((char *) ptr);
E 18
I 18
    return (ptr);
E 18
}

void
Free(p)
    ptr_t   p;
{
    if (p)
	free(p);
}

D 18
#endif				/* SYSMALLOC */

E 18
E 11
E 3
D 4
#ifdef debug
E 4
D 3
showall(v)
	char **v;
E 3
I 3
/*
 * mstats - print out statistics about malloc
D 11
 * 
E 11
I 11
 *
E 11
 * Prints two lines of numbers, one showing the length of the free list
 * for each size category, the second showing the number of mallocs -
 * frees for each size category.
 */
D 11
showall(s)
D 4
	char **s;
E 4
I 4
char **s;
E 11
I 11
void
D 14
showall()
E 14
I 14
/*ARGSUSED*/
showall(v, t)
    Char **v;
    struct command *t;
E 14
E 11
E 4
E 3
{
D 3
	register union store *p, *q;
	int used = 0, free = 0, i;
E 3
I 3
D 4
  	register int i, j;
  	register union overhead *p;
  	int totfree = 0,
  	totused = 0;
E 4
I 4
D 11
	register int i, j;
	register union overhead *p;
	int totfree = 0,
	totused = 0;
E 11
I 11
D 18
#ifndef SYSMALLOC
    register int i, j;
    register union overhead *p;
    int     totfree = 0, totused = 0;
E 11
E 4
E 3

D 3
	for (p = clearbusy(allocs[1].ptr); p != alloct; p = q) {
		q = clearbusy(p->ptr);
		if (v[1])
		printf("%6o %5d %s\n", p,
		    ((unsigned) q - (unsigned) p),
		    testbusy(p->ptr) ? "BUSY" : "FREE");
		i = ((unsigned) q - (unsigned) p);
		if (testbusy(p->ptr)) used += i; else free += i;
	}
D 2
	printf("%d used, %d free, %l end\n", used, free, clearbusy(alloct));
E 2
I 2
	printf("%d used, %d free, %ld end\n", used, free, clearbusy(alloct));
E 3
I 3
D 11
	if (s[1])
D 4
	    printf("Memory allocation statistics %s\nfree:\t", s[1]);
  	for (i = 0; i < NBUCKETS; i++) {
  		for (j = 0, p = nextf[i]; p; p = p->ov_next, j++)
  			;
	
  		if (s[1])
		    printf(" %d", j);
  		totfree += j * (1 << (i + 3));
  	}
E 4
I 4
		printf("Memory allocation statistics %s\nfree:", s[1]);
	for (i = 0; i < NBUCKETS; i++) {
		for (j = 0, p = nextf[i]; p; p = p->ov_next, j++)
			;
D 8

E 8
		if (s[1])
			printf(" %d", j);
		totfree += j * (1 << (i + 3));
	}
E 4
	if (s[1])
D 4
  	    printf("\nused:\t");
  	for (i = 0; i < NBUCKETS; i++) {
  		if (s[1])
		    printf(" %d", nmalloc[i]);
  		totused += nmalloc[i] * (1 << (i + 3));
  	}
E 4
I 4
		printf("\nused:");
	for (i = 0; i < NBUCKETS; i++) {
		if (s[1])
			printf(" %d", nmalloc[i]);
		totused += nmalloc[i] * (1 << (i + 3));
	}
E 4
	if (s[1])
D 4
	    printf("\n\t");
  	printf("Total in use: %d, total free: %d\n", totused, totfree);
E 4
I 4
		printf("\n");
	printf("Total in use: %d, total free: %d\n", totused, totfree);
E 11
I 11
D 14
    xprintf("csh current memory allocation:\nfree:\t");
E 14
I 14
    (void) fprintf(cshout, "csh current memory allocation:\nfree:\t");
E 14
    for (i = 0; i < NBUCKETS; i++) {
	for (j = 0, p = nextf[i]; p; p = p->ov_next, j++);
D 14
	xprintf(" %4d", j);
E 14
I 14
	(void) fprintf(cshout, " %4d", j);
E 14
	totfree += j * (1 << (i + 3));
    }
D 14
    xprintf("\nused:\t");
E 14
I 14
    (void) fprintf(cshout, "\nused:\t");
E 14
    for (i = 0; i < NBUCKETS; i++) {
D 14
	xprintf(" %4d", nmalloc[i]);
E 14
I 14
	(void) fprintf(cshout, "%4d", nmalloc[i]);
E 14
	totused += nmalloc[i] * (1 << (i + 3));
    }
D 14
    xprintf("\n\tTotal in use: %d, total free: %d\n",
E 14
I 14
    (void) fprintf(cshout, "\n\tTotal in use: %d, total free: %d\n",
E 14
	    totused, totfree);
D 14
    xprintf("\tAllocated memory from 0x%lx to 0x%lx.  Real top at 0x%lx\n",
E 14
I 14
    (void) fprintf(cshout, 
	    "\tAllocated memory from 0x%lx to 0x%lx.  Real top at 0x%lx\n",
E 14
	    membot, memtop, (char *) sbrk(0));
#else
E 18
I 18
    memtop = (char *) sbrk(0);
E 18
D 14
    xprintf("Allocated memory from 0x%lx to 0x%lx (%ld).\n",
E 14
I 14
    (void) fprintf(cshout, "Allocated memory from 0x%lx to 0x%lx (%ld).\n",
E 14
D 18
	    membot, memtop = (char *) sbrk(0), memtop - membot);
#endif				/* SYSMALLOC */
E 18
I 18
D 19
	    membot, memtop, memtop - membot);
E 19
I 19
	    (unsigned long) membot, (unsigned long) memtop, memtop - membot);
E 19
E 18
E 11
E 4
E 3
E 2
}
D 4
#endif
E 4
E 1
