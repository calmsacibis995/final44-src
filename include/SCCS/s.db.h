h39800
s 00052/00049/00140
d D 8.4 94/02/21 15:06:44 bostic 30 29
c first pass at making DB use basic integral types (the Alpha port)
e
s 00002/00002/00187
d D 8.3 94/01/02 11:47:00 bostic 29 28
c make it possible to compile new versions of db that load against
c old DB users (ex: nvi with NET/2 C library getpwent.o's)
e
s 00056/00034/00133
d D 8.2 94/01/02 11:46:22 bostic 28 27
c move acceptable open(2) flag check to dbopen, no longer need #define
c add DB_{LOCK,SHMEM,TXN} flags to the open calls
c minor whitespace cleanup
e
s 00002/00002/00165
d D 8.1 93/06/02 20:05:07 bostic 27 25
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00001/00166
d R 5.26 93/05/24 09:46:50 bostic 26 25
c instead of using the sync flag, return a pointer to the btree sync
c routine -- this keeps all the ugliness in the RECNO area
c leave the sync flag in, it may be useful someday, and it's easy to add now
e
s 00001/00000/00166
d D 5.25 93/05/22 16:35:57 bostic 25 24
c add a file descriptor return interface 
e
s 00001/00000/00165
d D 5.24 93/05/16 16:09:53 bostic 24 23
c add psize to recno, passed to btree
e
s 00023/00031/00142
d D 5.23 93/05/16 15:49:31 bostic 23 22
c make sync take a flags argument (add R_RECNOSYNC flag)
c delete RECNOKEY structure and supporting #defines
c minor lint, prototyping
e
s 00001/00001/00172
d D 5.22 93/05/10 11:59:55 bostic 22 21
c delete R_CURSORLOG
e
s 00001/00001/00172
d D 5.21 93/02/14 17:28:38 bostic 21 20
c index_t -> indx_t
e
s 00003/00000/00170
d D 5.20 92/11/18 15:02:57 bostic 20 19
c add __USE_OPEN_FLAGS, it's privately used, though
e
s 00004/00004/00166
d D 5.19 92/11/11 18:47:44 bostic 19 18
c R_APPEND -> R_CURSORLOG; add R_SETCURSOR
c key variable no longer const * for the put routine, key can be set
e
s 00001/00000/00169
d D 5.18 92/04/25 20:22:10 ralph 18 17
c added sys/types.h since its needed.
e
s 00018/00019/00151
d D 5.17 91/09/26 16:57:20 bostic 17 16
c port.h has typedef's for u_'s, do it right for BSD
e
s 00011/00011/00159
d D 5.16 91/09/26 16:43:44 bostic 16 15
c minimize the dependencies on <sys/types.h
e
s 00002/00002/00168
d D 5.15 91/09/11 16:10:08 bostic 15 14
c minor rearrangements
e
s 00001/00001/00169
d D 5.14 91/09/08 12:33:18 bostic 14 13
c bump the hash version to 2; (allocate overflow pages beyond EOF)
e
s 00039/00018/00131
d D 5.13 91/09/08 11:21:05 bostic 13 12
c fold routine flags into one list; add pointer oriented swap macros;
c make get routine key argument a const.
e
s 00050/00033/00099
d D 5.12 91/09/04 12:37:04 bostic 12 11
c Rev #2; new interface, btrees, recno's.
e
s 00002/00002/00130
d D 5.11 91/08/05 19:53:58 bostic 11 10
c DBT should have a size_t as an arg, not an int
e
s 00005/00001/00127
d D 5.10 91/04/02 08:39:33 bostic 10 9
c add DB.type field to reflect type of underlying database
e
s 00001/00001/00127
d D 5.9 91/04/01 09:01:11 bostic 9 8
c data is a void *
e
s 00000/00002/00128
d D 5.8 91/03/18 18:07:36 bostic 8 7
c I got a little too enthusiastic, there...
e
s 00001/00001/00129
d D 5.7 91/03/11 16:06:17 bostic 7 6
c change hash "bytes to cache" to cachesize for consistency
e
s 00013/00009/00117
d D 5.6 91/03/03 13:59:48 bostic 6 5
c do function prototypes for db(3) internal routines
e
s 00001/00001/00125
d D 5.5 91/03/03 13:20:26 bostic 5 4
c DBT.data is unsigned
e
s 00001/00001/00125
d D 5.4 91/02/22 10:08:54 bostic 4 3
c make safe for c++
e
s 00003/00006/00123
d D 5.3 91/02/22 08:30:03 donn 3 2
c Remove prototype parameter names, both because they didn't begin with
c underscores and because they contained three of the four uses of C++ keywords.
e
s 00049/00010/00080
d D 5.2 91/02/12 20:18:18 bostic 2 1
c protect against user inclusion (included by ndbm.h)
c minor cleanup when integrated Margo Seltzer's hash package
c add big endian to/from little endian macros, both swap and copy
e
s 00090/00000/00000
d D 5.1 90/12/05 11:57:06 bostic 1 0
c date and time created 90/12/05 11:57:06 by bostic
e
u
U
t
T
I 1
/*-
D 27
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 27
I 27
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 27
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

I 2
#ifndef _DB_H_
#define	_DB_H_

I 18
#include <sys/types.h>
E 18
I 6
#include <sys/cdefs.h>

I 28
#include <limits.h>

E 28
E 6
E 2
D 12
/* flags for DB.put() call */
E 12
I 12
#define	RET_ERROR	-1		/* Return values. */
#define	RET_SUCCESS	 0
#define	RET_SPECIAL	 1

D 30
#define	MAX_PAGE_NUMBER	ULONG_MAX	/* >= # of pages in a file */
D 17
typedef unsigned long	pgno_t;
E 17
I 17
typedef u_long	pgno_t;
E 17
#define	MAX_PAGE_OFFSET	USHRT_MAX	/* >= # of bytes in a page */
D 17
typedef unsigned short	index_t;
E 17
I 17
D 21
typedef u_short	index_t;
E 21
I 21
typedef u_short	indx_t;
E 21
E 17
#define	MAX_REC_NUMBER	ULONG_MAX	/* >= # of records in a tree */
D 17
typedef unsigned long	recno_t;
E 17
I 17
typedef u_long	recno_t;
E 30
I 30
#define	MAX_PAGE_NUMBER	0xffffffff	/* >= # of pages in a file */
typedef u_int32_t	pgno_t;
#define	MAX_PAGE_OFFSET	65535		/* >= # of bytes in a page */
typedef u_int16_t	indx_t;
#define	MAX_REC_NUMBER	0xffffffff	/* >= # of records in a tree */
typedef u_int32_t	recno_t;
E 30
E 17

/* Key/data structure -- a Data-Base Thang. */
typedef struct {
	void	*data;			/* data */
	size_t	 size;			/* data length */
} DBT;

D 13
/* Flags for DB.put() call. */
E 12
#define	R_IBEFORE	1		/* RECNO */
#define	R_IAFTER	2		/* RECNO */
#define	R_NOOVERWRITE	3		/* BTREE, HASH, RECNO */
D 2
#define	R_PUT		4
E 2
I 2
#define	R_PUT		4		/* BTREE, HASH, RECNO */
E 13
I 13
/* Routine flags. */
D 19
#define	R_APPEND	1		/* put (RECNO) */
#define	R_CURSOR	2		/* del, put, seq */
E 19
I 19
#define	R_CURSOR	1		/* del, put, seq */
D 22
#define	R_CURSORLOG	2		/* put (RECNO) */
E 22
I 22
#define	__R_UNUSED	2		/* UNUSED */
E 22
E 19
#define	R_FIRST		3		/* seq */
#define	R_IAFTER	4		/* put (RECNO) */
#define	R_IBEFORE	5		/* put (RECNO) */
#define	R_LAST		6		/* seq (BTREE, RECNO) */
#define	R_NEXT		7		/* seq */
#define	R_NOOVERWRITE	8		/* put */
#define	R_PREV		9		/* seq (BTREE, RECNO) */
I 19
#define	R_SETCURSOR	10		/* put (RECNO) */
I 23
#define	R_RECNOSYNC	11		/* sync (RECNO) */
E 23
E 19
E 13
E 2

D 12
/* flags for DB.seq() call */
E 12
I 12
D 13
/* Flags for DB.seq() call. */
E 12
#define	R_CURSOR	1		/* BTREE, RECNO */
#define	R_FIRST		2		/* BTREE, HASH, RECNO */
#define	R_LAST		3		/* BTREE, RECNO */
#define	R_NEXT		4		/* BTREE, HASH, RECNO */
#define	R_PREV		5		/* BTREE, RECNO */

E 13
D 12
/* key/data structure -- a data-base thang */
typedef struct {
D 5
	char *data;
E 5
I 5
D 9
	unsigned char *data;
E 9
I 9
D 11
	void *data;
E 9
E 5
	int size;
E 11
I 11
	void	*data;			/* data */
	size_t	 size;			/* data length */
E 11
} DBT;
E 12
I 12
typedef enum { DB_BTREE, DB_HASH, DB_RECNO } DBTYPE;
E 12

I 20
D 28
#define	__USE_OPEN_FLAGS \
	(O_CREAT|O_EXCL|O_EXLOCK|O_RDONLY|O_RDWR|O_SHLOCK|O_TRUNC)
E 28
I 28
/*
 * !!!
 * The following flags are included in the dbopen(3) call as part of the
 * open(2) flags.  In order to avoid conflicts with the open flags, start
 * at the top of the 16 or 32-bit number space and work our way down.  If
 * the open flags were significantly expanded in the future, it could be
 * a problem.  Wish I'd left another flags word in the dbopen call.
 *
 * !!!
 * None of this stuff is implemented yet.  The only reason that it's here
 * is so that the access methods can skip copying the key/data pair when
 * the DB_LOCK flag isn't set.
 */
#if UINT_MAX > 65535
#define	DB_LOCK		0x20000000	/* Do locking. */
#define	DB_SHMEM	0x40000000	/* Use shared memory. */
#define	DB_TXN		0x80000000	/* Do transactions. */
#else
D 30
#define	DB_LOCK		0x00002000	/* Do locking. */
#define	DB_SHMEM	0x00004000	/* Use shared memory. */
#define	DB_TXN		0x00008000	/* Do transactions. */
E 30
I 30
#define	DB_LOCK		    0x2000	/* Do locking. */
#define	DB_SHMEM	    0x4000	/* Use shared memory. */
#define	DB_TXN		    0x8000	/* Do transactions. */
E 30
#endif
E 28

E 20
D 12
/* access method description structure */
E 12
I 12
/* Access method description structure. */
E 12
D 6
typedef struct {
	char *internal;		/* access method private; really void * */
	int (*close)();
D 4
	int (*delete)();
E 4
I 4
	int (*del)();
E 4
	int (*get)();
	int (*put)();
	int (*seq)();
	int (*sync)();
E 6
I 6
typedef struct __db {
I 12
D 15
	DBTYPE type;		/* type of underlying db */
E 12
D 10
	void *internal;		/* access method private; really void * */
E 10
I 10
	void *internal;		/* access method private */
E 15
I 15
D 28
	DBTYPE type;			/* underlying db type */
E 28
I 28
	DBTYPE type;			/* Underlying db type. */
E 28
E 15
D 12
#define	DB_BTREE	1
#define	DB_HASH		2
#define	DB_RECNO	3
	int type;		/* type of underlying db */
E 10
D 8
__BEGIN_DECLS
E 8
	int (*close) __P((const struct __db *));
	int (*del) __P((const struct __db *, const DBT *, unsigned int));
	int (*get) __P((const struct __db *, DBT *, DBT *, unsigned int));
	int (*put) __P((const struct __db *, const DBT *, const DBT *,
		unsigned int));
	int (*seq) __P((const struct __db *, DBT *, DBT *, unsigned int));
	int (*sync) __P((const struct __db *));
E 12
I 12
	int (*close)	__P((struct __db *));
D 17
	int (*del)	__P((const struct __db *, const DBT *, unsigned int));
D 13
	int (*get)	__P((const struct __db *, DBT *, DBT *, unsigned int));
E 13
I 13
	int (*get)	__P((const struct __db *, const DBT *, DBT *,
			    unsigned int));
E 17
I 17
	int (*del)	__P((const struct __db *, const DBT *, u_int));
I 25
D 29
	int (*fd)	__P((const struct __db *));
E 29
E 25
	int (*get)	__P((const struct __db *, const DBT *, DBT *, u_int));
E 17
E 13
D 19
	int (*put)	__P((const struct __db *, const DBT *, const DBT *,
D 13
			     unsigned int));
E 13
I 13
D 17
			    unsigned int));
E 13
	int (*seq)	__P((const struct __db *, DBT *, DBT *, unsigned int));
E 17
I 17
			    u_int));
E 19
I 19
	int (*put)	__P((const struct __db *, DBT *, const DBT *, u_int));
E 19
	int (*seq)	__P((const struct __db *, DBT *, DBT *, u_int));
E 17
D 23
	int (*sync)	__P((const struct __db *));
E 23
I 23
	int (*sync)	__P((const struct __db *, u_int));
E 23
I 15
D 29
	void *internal;			/* access method private */
E 29
I 29
	void *internal;			/* Access method private. */
	int (*fd)	__P((const struct __db *));
E 29
E 15
E 12
D 8
__END_DECLS
E 8
E 6
} DB;

#define	BTREEMAGIC	0x053162
I 2
D 12
#define	BTREEVERSION	2
E 12
I 12
#define	BTREEVERSION	3
E 12
E 2

D 12
/* structure used to pass parameters to the btree routines */
E 12
I 12
/* Structure used to pass parameters to the btree routines. */
E 12
typedef struct {
#define	R_DUP		0x01	/* duplicate keys */
D 16
	u_long flags;
E 16
I 16
D 17
	unsigned long flags;
E 17
I 17
D 23
	u_long flags;
E 17
E 16
	int cachesize;		/* bytes to cache */
I 12
	int maxkeypage;		/* maximum keys per page */
	int minkeypage;		/* minimum keys per page */
E 12
	int psize;		/* page size */
E 23
I 23
D 30
	u_long	 flags;
	int	 cachesize;	/* bytes to cache */
	int	 maxkeypage;	/* maximum keys per page */
	int	 minkeypage;	/* minimum keys per page */
	int	 psize;		/* page size */
E 23
D 12
	int (*compare)();	/* compare function */
E 12
I 12
				/* comparison, prefix functions */
D 23
	int (*compare)	__P((const DBT *, const DBT *));
	int (*prefix)	__P((const DBT *, const DBT *));
E 12
I 2
	int lorder;		/* byte order */
E 23
I 23
	int	 (*compare)	__P((const DBT *, const DBT *));
	int	 (*prefix)	__P((const DBT *, const DBT *));
	int	 lorder;	/* byte order */
E 30
I 30
	u_long	flags;
	u_int	cachesize;	/* bytes to cache */
	int	maxkeypage;	/* maximum keys per page */
	int	minkeypage;	/* minimum keys per page */
	u_int	psize;		/* page size */
	int	(*compare)	/* comparison function */
	    __P((const DBT *, const DBT *));
	size_t	(*prefix)	/* prefix function */
	    __P((const DBT *, const DBT *));
	int	lorder;		/* byte order */
E 30
E 23
E 2
} BTREEINFO;

#define	HASHMAGIC	0x061561
I 2
D 14
#define	HASHVERSION	1
E 14
I 14
#define	HASHVERSION	2
E 14
E 2

D 12
/* structure used to pass parameters to the hashing routines */
E 12
I 12
/* Structure used to pass parameters to the hashing routines. */
E 12
typedef struct {
D 23
	int bsize;		/* bucket size */
	int ffactor;		/* fill factor */
	int nelem;		/* number of elements */
D 7
	int ncached;		/* bytes to cache */
E 7
I 7
	int cachesize;		/* bytes to cache */
E 7
	int (*hash)();		/* hash function */
I 2
	int lorder;		/* byte order */
E 23
I 23
D 30
	int	 bsize;		/* bucket size */
	int	 ffactor;	/* fill factor */
	int	 nelem;		/* number of elements */
	int	 cachesize;	/* bytes to cache */
				/* hash function */
	int	 (*hash) __P((const void *, size_t));
	int	 lorder;	/* byte order */
E 30
I 30
	u_int	bsize;		/* bucket size */
	u_int	ffactor;	/* fill factor */
	u_int	nelem;		/* number of elements */
	u_int	cachesize;	/* bytes to cache */
	u_int32_t		/* hash function */
		(*hash) __P((const void *, size_t));
	int	lorder;		/* byte order */
E 30
E 23
E 2
} HASHINFO;

D 12
/* structure used to pass parameters to the record routines */
E 12
I 12
/* Structure used to pass parameters to the record routines. */
E 12
typedef struct {
#define	R_FIXEDLEN	0x01	/* fixed-length records */
I 12
#define	R_NOKEY		0x02	/* key not required */
#define	R_SNAPSHOT	0x04	/* snapshot the input */
E 12
D 16
	u_long flags;
E 16
I 16
D 17
	unsigned long flags;
E 17
I 17
D 23
	u_long flags;
E 17
E 16
	int cachesize;		/* bytes to cache */
I 12
	int lorder;		/* byte order */
E 12
	size_t reclen;		/* record length (fixed-length records) */
D 16
	u_char bval;		/* delimiting byte (variable-length records */
E 16
I 16
D 17
	unsigned char bval;	/* delimiting byte (variable-length records */
E 17
I 17
	u_char bval;		/* delimiting byte (variable-length records */
E 23
I 23
D 30
	u_long	 flags;
	int	 cachesize;	/* bytes to cache */
I 24
	int	 psize;		/* page size */
E 24
	int	 lorder;	/* byte order */
	size_t	 reclen;	/* record length (fixed-length records) */
	u_char	 bval;		/* delimiting byte (variable-length records */
E 30
I 30
	u_long	flags;
	u_int	cachesize;	/* bytes to cache */
	u_int	psize;		/* page size */
	int	lorder;		/* byte order */
	size_t	reclen;		/* record length (fixed-length records) */
	u_char	bval;		/* delimiting byte (variable-length records */
E 30
	char	*bfname;	/* btree file name */ 
E 23
E 17
E 16
} RECNOINFO;
D 23

D 12
/* key structure for the record routines */
E 12
I 12
/* Key structure for the record routines. */
E 12
typedef struct {
D 16
	u_long number;
	u_long offset;
	u_long length;
E 16
I 16
D 17
	unsigned long number;
	unsigned long offset;
	unsigned long length;
E 17
I 17
	u_long number;
	u_long offset;
	u_long length;
E 17
E 16
#define	R_LENGTH	0x01	/* length is valid */
#define	R_NUMBER	0x02	/* record number is valid */
#define	R_OFFSET	0x04	/* offset is valid */
D 16
	u_char valid;
E 16
I 16
D 17
	unsigned char valid;
E 17
I 17
	u_char valid;
E 17
E 16
} RECNOKEY;
E 23

I 30
#ifdef __DBINTERFACE_PRIVATE
E 30
D 2
#if __STDC__ || c_plusplus
DB *btree_open(const char *file, int flags, int mode, const BTREEINFO *private);
DB *hash_open(const char *file, int flags, int mode, const HASHINFO *private);
DB *recno_open(const char *file, int flags, int mode, const RECNOINFO *private);
#else
DB *btree_open();
DB *hash_open();
DB *recno_open();
#endif
E 2
I 2
D 13
/* Little endian <--> big endian long swap macros. */
E 13
I 13
/*
D 30
 * Little endian <==> big endian long swap macros.
 *	BLSWAP		swap a memory location
 *	BLPSWAP		swap a referenced memory location
 *	BLSWAP_COPY	swap from one location to another
E 30
I 30
 * Little endian <==> big endian 32-bit swap macros.
 *	M_32_SWAP	swap a memory location
 *	P_32_SWAP	swap a referenced memory location
 *	P_32_COPY	swap from one location to another
E 30
 */
E 13
D 28
#define BLSWAP(a) { \
D 16
	u_long _tmp = a; \
E 16
I 16
D 17
	unsigned long _tmp = a; \
E 17
I 17
	u_long _tmp = a; \
E 17
E 16
	((char *)&a)[0] = ((char *)&_tmp)[3]; \
	((char *)&a)[1] = ((char *)&_tmp)[2]; \
	((char *)&a)[2] = ((char *)&_tmp)[1]; \
	((char *)&a)[3] = ((char *)&_tmp)[0]; \
E 28
I 28
D 30
#define BLSWAP(a) {							\
	u_long _tmp = a;						\
E 30
I 30
#define	M_32_SWAP(a) {							\
	u_int32_t _tmp = a;						\
E 30
	((char *)&a)[0] = ((char *)&_tmp)[3];				\
	((char *)&a)[1] = ((char *)&_tmp)[2];				\
	((char *)&a)[2] = ((char *)&_tmp)[1];				\
	((char *)&a)[3] = ((char *)&_tmp)[0];				\
E 28
}
D 13
#define	BLSWAP_COPY(a,b) { \
E 13
I 13
D 28
#define	BLPSWAP(a) { \
D 16
	u_long _tmp = *(u_long *)a; \
E 16
I 16
D 17
	unsigned long _tmp = *(unsigned long *)a; \
E 17
I 17
	u_long _tmp = *(u_long *)a; \
E 17
E 16
	((char *)a)[0] = ((char *)&_tmp)[3]; \
	((char *)a)[1] = ((char *)&_tmp)[2]; \
	((char *)a)[2] = ((char *)&_tmp)[1]; \
	((char *)a)[3] = ((char *)&_tmp)[0]; \
E 28
I 28
D 30
#define	BLPSWAP(a) {							\
	u_long _tmp = *(u_long *)a;					\
E 30
I 30
#define	P_32_SWAP(a) {							\
	u_int32_t _tmp = *(u_int32_t *)a;				\
E 30
	((char *)a)[0] = ((char *)&_tmp)[3];				\
	((char *)a)[1] = ((char *)&_tmp)[2];				\
	((char *)a)[2] = ((char *)&_tmp)[1];				\
	((char *)a)[3] = ((char *)&_tmp)[0];				\
E 28
}
D 28
#define	BLSWAP_COPY(a, b) { \
E 13
	((char *)&(b))[0] = ((char *)&(a))[3]; \
	((char *)&(b))[1] = ((char *)&(a))[2]; \
	((char *)&(b))[2] = ((char *)&(a))[1]; \
	((char *)&(b))[3] = ((char *)&(a))[0]; \
E 28
I 28
D 30
#define	BLSWAP_COPY(a, b) {						\
E 30
I 30
#define	P_32_COPY(a, b) {						\
E 30
	((char *)&(b))[0] = ((char *)&(a))[3];				\
	((char *)&(b))[1] = ((char *)&(a))[2];				\
	((char *)&(b))[2] = ((char *)&(a))[1];				\
	((char *)&(b))[3] = ((char *)&(a))[0];				\
E 28
}

D 12

E 12
D 13
/* Little endian <--> big endian short swap macros. */
E 13
I 13
/*
D 30
 * Little endian <==> big endian short swap macros.
 *	BSSWAP		swap a memory location
 *	BSPSWAP		swap a referenced memory location
 *	BSSWAP_COPY	swap from one location to another
E 30
I 30
 * Little endian <==> big endian 16-bit swap macros.
 *	M_16_SWAP	swap a memory location
 *	P_16_SWAP	swap a referenced memory location
 *	P_16_COPY	swap from one location to another
E 30
 */
E 13
D 28
#define BSSWAP(a) { \
D 16
	u_short _tmp = a; \
E 16
I 16
D 17
	unsigned short _tmp = a; \
E 17
I 17
	u_short _tmp = a; \
E 17
E 16
	((char *)&a)[0] = ((char *)&_tmp)[1]; \
	((char *)&a)[1] = ((char *)&_tmp)[0]; \
E 28
I 28
D 30
#define BSSWAP(a) {							\
	u_short _tmp = a;						\
E 30
I 30
#define	M_16_SWAP(a) {							\
	u_int16_t _tmp = a;						\
E 30
	((char *)&a)[0] = ((char *)&_tmp)[1];				\
	((char *)&a)[1] = ((char *)&_tmp)[0];				\
E 28
}
D 13
#define BSSWAP_COPY(a,b) { \
E 13
I 13
D 28
#define BSPSWAP(a) { \
D 16
	u_short _tmp = *(u_short *)a; \
E 16
I 16
D 17
	unsigned short _tmp = *(unsigned short *)a; \
E 17
I 17
	u_short _tmp = *(u_short *)a; \
E 17
E 16
	((char *)a)[0] = ((char *)&_tmp)[1]; \
	((char *)a)[1] = ((char *)&_tmp)[0]; \
E 28
I 28
D 30
#define BSPSWAP(a) {							\
	u_short _tmp = *(u_short *)a;					\
E 30
I 30
#define	P_16_SWAP(a) {							\
	u_int16_t _tmp = *(u_int16_t *)a;				\
E 30
	((char *)a)[0] = ((char *)&_tmp)[1];				\
	((char *)a)[1] = ((char *)&_tmp)[0];				\
E 28
}
D 28
#define BSSWAP_COPY(a, b) { \
E 13
	((char *)&(b))[0] = ((char *)&(a))[1]; \
	((char *)&(b))[1] = ((char *)&(a))[0]; \
E 28
I 28
D 30
#define BSSWAP_COPY(a, b) {						\
E 30
I 30
#define	P_16_COPY(a, b) {						\
E 30
	((char *)&(b))[0] = ((char *)&(a))[1];				\
	((char *)&(b))[1] = ((char *)&(a))[0];				\
E 28
}
I 30
#endif
E 30

D 6
#include <sys/cdefs.h>
E 6
__BEGIN_DECLS
D 12
DB	*btree_open
D 3
	    __P((const char *file, int flags, int mode,
	    const BTREEINFO *private));
E 3
I 3
	    __P((const char *, int, int, const BTREEINFO *));
E 3
DB	*hash_open
D 3
	    __P((const char *file, int flags, int mode,
	    const HASHINFO *private));
E 3
I 3
	    __P((const char *, int, int, const HASHINFO *));
E 3
DB	*recno_open
D 3
	    __P((const char *file, int flags, int mode,
	    const RECNOINFO *private));
E 3
I 3
	    __P((const char *, int, int, const RECNOINFO *));
E 3
__END_DECLS
E 12
I 12
DB *dbopen __P((const char *, int, int, DBTYPE, const void *));
E 12

I 12
#ifdef __DBINTERFACE_PRIVATE
D 28
DB	*__bt_open __P((const char *, int, int, const BTREEINFO *));
DB	*__hash_open __P((const char *, int, int, const HASHINFO *));
DB	*__rec_open __P((const char *, int, int, const RECNOINFO *));
E 28
I 28
DB	*__bt_open __P((const char *, int, int, const BTREEINFO *, int));
DB	*__hash_open __P((const char *, int, int, const HASHINFO *, int));
DB	*__rec_open __P((const char *, int, int, const RECNOINFO *, int));
E 28
void	 __dbpanic __P((DB *dbp));
#endif
__END_DECLS
E 12
#endif /* !_DB_H_ */
E 2
E 1
