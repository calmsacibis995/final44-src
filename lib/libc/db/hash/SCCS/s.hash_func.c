h04297
s 00057/00036/00129
d D 8.2 94/02/21 15:09:09 bostic 6 5
c first pass at making DB use basic integral types (the Alpha port)
e
s 00002/00002/00163
d D 8.1 93/06/04 15:22:01 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00001/00165
d D 5.4 93/02/11 11:39:50 bostic 4 3
c move db.h to the end of the includes, make compat.h work better
e
s 00003/00001/00163
d D 5.3 93/01/17 16:20:23 bostic 3 2
c can't have a global "hashp", pass it around as an argument
c change default_hash to __default_hash for the same reason
e
s 00105/00094/00059
d D 5.2 91/09/04 12:56:31 bostic 2 1
c Rev #2.  ANSI/POSIX and reformatting, a few bug fixes thrown in
e
s 00153/00000/00000
d D 5.1 91/02/12 20:28:02 bostic 1 0
c date and time created 91/02/12 20:28:02 by bostic
e
u
U
t
T
I 1
/*-
D 5
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * This code is derived from software contributed to Berkeley by
 * Margo Seltzer.
 *
 * %sccs.include.redist.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

D 2
/* Global default hash function */
static	int	hash1();
static	int	hash2();
static	int	hash3();
static	int	hash4();
E 2
I 2
#include <sys/types.h>
I 3

E 3
#include <db.h>
I 3
D 4

E 4
E 3
#include "hash.h"
#include "page.h"
#include "extern.h"
E 2

D 2
int	(*default_hash)() = hash4;
E 2
I 2
D 6
static int hash1 __P((u_char *, int));
static int hash2 __P((u_char *, int));
static int hash3 __P((u_char *, int));
static int hash4 __P((u_char *, int));
E 6
I 6
static u_int32_t hash1 __P((const void *, size_t));
static u_int32_t hash2 __P((const void *, size_t));
static u_int32_t hash3 __P((const void *, size_t));
static u_int32_t hash4 __P((const void *, size_t));
E 6
E 2

I 2
/* Global default hash function */
D 3
int (*default_hash) __P((u_char *, int)) = hash4;
E 3
I 3
D 6
int (*__default_hash) __P((u_char *, int)) = hash4;
E 6
I 6
u_int32_t (*__default_hash) __P((const void *, size_t)) = hash4;
E 6
E 3

E 2
D 6
/******************************* HASH FUNCTIONS **************************/
E 6
/*
I 6
 * HASH FUNCTIONS
 *
E 6
D 2
	Assume that we've already split the bucket to which this
	key hashes, calculate that bucket, and check that in fact
	we did already split it.
E 2
I 2
 * Assume that we've already split the bucket to which this key hashes,
 * calculate that bucket, and check that in fact we did already split it.
 *
 * This came from ejb's hsearch.
 */
E 2

D 2
	This came from ejb's hsearch.
*/
E 2
I 2
#define PRIME1		37
#define PRIME2		1048583
E 2

D 2
# define PRIME1			37
# define PRIME2			1048583

E 2
D 6
static int
D 2
hash1(key,len)
char *key;
int len;
E 2
I 2
hash1(key, len)
	register u_char *key;
	register int len;
E 6
I 6
static u_int32_t
hash1(keyarg, len)
	const void *keyarg;
	register size_t len;
E 6
E 2
{
D 6
	register int h;
E 6
I 6
	register const u_char *key;
	register u_int32_t h;
E 6
D 2
	register int l = len;
	register unsigned char *k = (unsigned char *) key;
E 2

D 6
	h = 0;
E 6
D 2
	/*
	 * Convert string to integer
	 */
	while (l--) h = h * PRIME1 ^ (*k++ - ' ');
E 2
I 2
	/* Convert string to integer */
D 6
	while (len--)
E 6
I 6
	for (key = keyarg, h = 0; len--;)
E 6
		h = h * PRIME1 ^ (*key++ - ' ');
E 2
	h %= PRIME2;
D 2

E 2
	return (h);
}

/*
D 2
    Phong's linear congruential hash
*/
E 2
I 2
 * Phong's linear congruential hash
 */
E 2
#define dcharhash(h, c)	((h) = 0x63c63cd9*(h) + 0x9c39c33d + (c))

D 6
static int
D 2
hash2(str, n)
	register unsigned char *str;
	int n;
E 2
I 2
hash2(key, len)
	register u_char *key;
	int len;
E 6
I 6
static u_int32_t
hash2(keyarg, len)
	const void *keyarg;
	size_t len;
E 6
E 2
{
D 2
	register unsigned char *e, c;
E 2
I 2
D 6
	register u_char *e, c;
E 2
	register int h;
E 6
I 6
	register const u_char *e, *key;
	register u_int32_t h;
	register u_char c;
E 6

I 6
	key = keyarg;
E 6
D 2
	e = str + n;
	for (h = 0; str != e;) {
		c = *str++;
		if (!c && str > e)
E 2
I 2
	e = key + len;
	for (h = 0; key != e;) {
		c = *key++;
		if (!c && key > e)
E 2
			break;
D 2
		dcharhash(h,c);
E 2
I 2
		dcharhash(h, c);
E 2
	}
D 2
	return(h);
E 2
I 2
	return (h);
E 2
}

/*
D 2
 * This is INCREDIBLY ugly, but fast.
 * We break the string up into 8 byte units.  On the first time
 * through the loop we get the "leftover bytes" (strlen % 8).
 * On every other iteration, we perform 8 HASHC's so we handle
 * all 8 bytes.  Essentially, this saves us 7 cmp & branch
 * instructions.  If this routine is heavily used enough, it's
 * worth the ugly coding
 * 
E 2
I 2
 * This is INCREDIBLY ugly, but fast.  We break the string up into 8 byte
 * units.  On the first time through the loop we get the "leftover bytes"
 * (strlen % 8).  On every other iteration, we perform 8 HASHC's so we handle
 * all 8 bytes.  Essentially, this saves us 7 cmp & branch instructions.  If
 * this routine is heavily used enough, it's worth the ugly coding.
 *
E 2
 * OZ's original sdbm hash
 */
D 6
static int
D 2
hash3(key,nbytes)
char *key;
int nbytes;
E 2
I 2
hash3(key, len)
	register u_char *key;
	register int len;
E 6
I 6
static u_int32_t
hash3(keyarg, len)
	const void *keyarg;
	register size_t len;
E 6
E 2
{
D 2
        register int n = 0;
	register char *str = key;
	register int loop;
	register int len = nbytes;
E 2
I 2
D 6
	register int n, loop;
E 6
I 6
	register const u_char *key;
	register size_t loop;
	register u_int32_t h;
E 6
E 2

D 2
#define HASHC   n = *str++ + 65599 * n
E 2
I 2
D 6
#define HASHC   n = *key++ + 65599 * n
E 6
I 6
#define HASHC   h = *key++ + 65599 * h
E 6
E 2

D 2
        if (len > 0) {
                loop = (len + 8 - 1) >> 3;
E 2
I 2
D 6
	n = 0;
E 6
I 6
	h = 0;
	key = keyarg;
E 6
	if (len > 0) {
		loop = (len + 8 - 1) >> 3;
E 2

D 2
                switch(len & (8 - 1)) {
			case 0: do {		/* All fall throughs */
					HASHC;  
				case 7: HASHC;
				case 6: HASHC;  
				case 5: HASHC;
				case 4: HASHC;  
				case 3: HASHC;
				case 2: HASHC;  
				case 1: HASHC;
                        } while (--loop);
                }
E 2
I 2
		switch (len & (8 - 1)) {
		case 0:
D 6
			do {	/* All fall throughs */
E 6
I 6
			do {
E 6
				HASHC;
I 6
				/* FALLTHROUGH */
E 6
		case 7:
				HASHC;
I 6
				/* FALLTHROUGH */
E 6
		case 6:
				HASHC;
I 6
				/* FALLTHROUGH */
E 6
		case 5:
				HASHC;
I 6
				/* FALLTHROUGH */
E 6
		case 4:
				HASHC;
I 6
				/* FALLTHROUGH */
E 6
		case 3:
				HASHC;
I 6
				/* FALLTHROUGH */
E 6
		case 2:
				HASHC;
I 6
				/* FALLTHROUGH */
E 6
		case 1:
				HASHC;
			} while (--loop);
		}
E 2
D 6

E 6
D 2
        }
	return(n);
E 2
I 2
	}
D 6
	return (n);
E 6
I 6
	return (h);
E 6
E 2
}

D 2
/* Hash function from Chris Torek */
E 2
I 2
/* Hash function from Chris Torek. */
E 2
D 6
static int
D 2
hash4(key,nbytes)
char	*key;
int	nbytes;
E 2
I 2
hash4(key, len)
	register u_char *key;
	register int len;
E 6
I 6
static u_int32_t
hash4(keyarg, len)
	const void *keyarg;
	register size_t len;
E 6
E 2
{
D 2
        register int h = 0;
	register char *p = key;
	register int loop;
	register int len = nbytes;
E 2
I 2
D 6
	register int h, loop;
E 6
I 6
	register const u_char *key;
	register size_t loop;
	register u_int32_t h;
E 6
E 2

D 2
#define HASH4a   h = (h << 5) - h + *p++;
#define HASH4b   h = (h << 5) + h + *p++;
E 2
I 2
#define HASH4a   h = (h << 5) - h + *key++;
#define HASH4b   h = (h << 5) + h + *key++;
E 2
#define HASH4 HASH4b

D 2
        if (len > 0) {
                loop = (len + 8 - 1) >> 3;
E 2
I 2
	h = 0;
I 6
	key = keyarg;
E 6
	if (len > 0) {
		loop = (len + 8 - 1) >> 3;
E 2

D 2
                switch(len & (8 - 1)) {
			case 0: do {		/* All fall throughs */
					HASH4;  
				case 7: HASH4;
				case 6: HASH4;  
				case 5: HASH4;
				case 4: HASH4;  
				case 3: HASH4;
				case 2: HASH4;  
				case 1: HASH4;
                        } while (--loop);
                }
E 2
I 2
		switch (len & (8 - 1)) {
		case 0:
D 6
			do {	/* All fall throughs */
E 6
I 6
			do {
E 6
				HASH4;
I 6
				/* FALLTHROUGH */
E 6
		case 7:
				HASH4;
I 6
				/* FALLTHROUGH */
E 6
		case 6:
				HASH4;
I 6
				/* FALLTHROUGH */
E 6
		case 5:
				HASH4;
I 6
				/* FALLTHROUGH */
E 6
		case 4:
				HASH4;
I 6
				/* FALLTHROUGH */
E 6
		case 3:
				HASH4;
I 6
				/* FALLTHROUGH */
E 6
		case 2:
				HASH4;
I 6
				/* FALLTHROUGH */
E 6
		case 1:
				HASH4;
			} while (--loop);
		}
E 2
D 6

E 6
D 2
        }
	return(h);
E 2
I 2
	}
	return (h);
E 2
}
E 1
