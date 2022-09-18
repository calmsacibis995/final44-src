h50088
s 00008/00007/00960
d D 8.7 94/02/21 17:43:38 bostic 45 44
c cast alloc's to shut SunOS up
e
s 00038/00038/00929
d D 8.6 94/02/21 15:09:07 bostic 44 43
c first pass at making DB use basic integral types (the Alpha port)
e
s 00002/00000/00965
d D 8.5 94/01/13 12:12:48 bostic 43 42
c Fixes a small memory leak (476 bytes) in libc's database subsystem.
c From: Christopher Jon Kane <kane@kidd.vet.purdue.edu>
e
s 00003/00001/00962
d D 8.4 93/10/12 15:17:11 bostic 42 41
c hash can actually read version 1 as well as version 2, the on-disk
c format didn't change
e
s 00007/00006/00956
d D 8.3 93/09/07 11:53:50 bostic 41 40
c add DB_ flags to __hash_open()
c USE_OPEN_FLAGS work done in dbopen(), no longer needed here
e
s 00001/00001/00961
d D 8.2 93/07/09 17:59:34 bostic 40 39
c don't increment/change a void *, cast to char * (thanks GCC!)
e
s 00002/00002/00960
d D 8.1 93/06/06 23:04:17 bostic 39 38
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00961
d D 5.36 93/06/06 22:57:01 bostic 38 36
c hash_realloc should zero out the newly allocated memory,
c not beyond the end of the old memory.
e
s 00002/00002/00960
d R 8.1 93/06/04 15:21:42 bostic 37 36
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00032/00003/00930
d D 5.35 93/05/23 13:09:07 bostic 36 35
c Add fd interface routine to return file descriptor.  Pass file name 
c to init_htab so that if no page size is specified, the page size will default 
c to the block size of the file system.  Initialize fill factor so that it will 
c dynamically be set during operation.
e
s 00008/00002/00925
d D 5.34 93/05/16 15:58:27 bostic 35 34
c add a flags argument to the sync call
e
s 00001/00001/00926
d D 5.33 93/02/21 13:49:08 ralph 34 33
c fix prototype declaration for swap_header().
e
s 00005/00005/00922
d D 5.32 93/02/16 12:33:28 bostic 33 32
c bcmp/bcopy/bzero -> memcmp/memmove/memset
e
s 00001/00001/00926
d D 5.31 93/02/11 11:39:45 bostic 32 31
c move db.h to the end of the includes, make compat.h work better
e
s 00120/00099/00807
d D 5.30 93/01/17 16:20:19 bostic 31 30
c can't have a global "hashp", pass it around as an argument
c change default_hash to __default_hash for the same reason
e
s 00004/00004/00902
d D 5.29 92/11/18 15:06:26 bostic 30 29
c hash_put can now set the key, so key not a const *
c use __USE_OPEN_FLAGS macro from db.h
e
s 00001/00001/00905
d D 5.28 92/11/02 17:21:46 bostic 29 28
c just in case, lseek lint
e
s 00001/00001/00905
d D 5.27 92/11/02 09:16:45 bostic 28 27
c use O_ACCMODE to extract O_WRONLY bit
e
s 00007/00012/00899
d D 5.26 92/10/04 16:56:46 margo 27 26
c Disallow O_WRONLY permission on hash files.
e
s 00004/00002/00907
d D 5.25 92/08/07 13:52:48 bostic 26 25
c Don't increment bucket number when breaking out of hash_seq loop.
e
s 00033/00026/00876
d D 5.24 92/07/20 16:16:23 bostic 25 24
c handle sequential access when overflow pages have no keys
e
s 00002/00002/00900
d D 5.23 92/05/15 16:18:01 bostic 24 23
c add O_EXLOCK, O_SHLOCK to open falgs
e
s 00003/00004/00899
d D 5.22 91/12/18 18:13:10 bostic 23 22
c Make sure that the overflow points get initialized correctly when the
c table is created empty.  Also, make overflow point calculation a function of
c (max_bucket + 1), not just max_bucket.
e
s 00004/00001/00899
d D 5.21 91/11/26 16:21:34 marc 22 21
c don't need whdr unless LITTLE_ENDIAN
e
s 00001/00001/00899
d D 5.20 91/11/13 12:51:50 bostic 21 19
c undeclared structure
e
s 00000/00001/00899
d R 5.20 91/11/12 10:34:52 bostic 20 19
c unnecessary assignment in BYTEORDER code
e
s 00002/00001/00898
d D 5.19 91/09/26 15:27:32 bostic 19 18
c check hashp before closing the file descriptor on error
e
s 00004/00004/00895
d D 5.18 91/09/11 16:01:07 bostic 18 17
c hash_open -> __hash_open; flush_meta checked wrong return value for
c __put_page; formatting typo
e
s 00020/00006/00879
d D 5.17 91/09/08 13:45:15 bostic 17 16
c bump the hash version to 2; (allocate overflow pages beyond EOF)
e
s 00017/00014/00868
d D 5.16 91/09/08 12:29:13 bostic 16 15
c check return values, delete unused arguments, get now takes const *key
e
s 00609/00714/00273
d D 5.15 91/09/04 12:56:18 bostic 15 14
c Rev #2.  ANSI/POSIX and reformatting, a few bug fixes thrown in
e
s 00001/00000/00986
d D 5.14 91/04/02 08:43:24 bostic 14 13
c add DB.type field to reflect type of underlying database
e
s 00018/00035/00968
d D 5.13 91/03/12 09:36:11 bostic 13 12
c Make all bucket and overflow addresses unsigned
c add flag to hash_get for consistency with documentation
c Make bitmaps demand loaded rather than load ahead on open
c Fix RDONLY behaviour so meta data is not written out
e
s 00004/00004/00999
d D 5.12 91/03/03 14:32:56 bostic 12 11
c DBT data changed to be unsigned, fix routines that take flags
e
s 00014/00006/00989
d D 5.11 91/02/23 09:24:02 bostic 11 10
c make flags arguments right
e
s 00004/00006/00991
d D 5.10 91/02/22 17:23:36 bostic 10 9
c ANSI prototypes
e
s 00003/00003/00994
d D 5.9 91/02/22 10:21:49 bostic 9 8
c ANSI and c++ stuff
e
s 00001/00000/00996
d D 5.8 91/02/22 08:18:55 bostic 8 7
c need stdio for DEBUG and HASH_STATISTICS
e
s 00018/00000/00978
d D 5.7 91/02/21 18:57:20 bostic 7 6
c clear errno on open/create after stat; count bitmaps so can be free'd
e
s 00002/00001/00976
d D 5.6 91/02/21 17:19:58 bostic 6 5
c L_SET -> SEEK_SET
e
s 00000/00005/00977
d D 5.5 91/02/21 17:12:46 bostic 5 4
c move O_ACCMODE into ../dist/sysv.h
e
s 00005/00003/00977
d D 5.4 91/02/20 08:59:45 bostic 4 3
c don't do the fcntl unless the file was openeed
e
s 00034/00012/00946
d D 5.3 91/02/19 10:30:40 bostic 3 2
c make -1 mean no open fd instead of 0
c don't save the file if it's read-only
c make sure db structure gets destroyed
c always close the file
c add "pinning" to the buffer pool
e
s 00001/00000/00957
d D 5.2 91/02/14 18:25:37 bostic 2 1
c set file descriptors to be close-on-exec; block signals while
c unlinking the temporary file so we don't get caught
e
s 00957/00000/00000
d D 5.1 91/02/12 20:27:58 bostic 1 0
c date and time created 91/02/12 20:27:58 by bostic
e
u
U
t
T
I 1
/*-
D 39
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 39
I 39
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 39
 *
 * This code is derived from software contributed to Berkeley by
 * Margo Seltzer.
 *
 * %sccs.include.redist.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

#include <sys/param.h>
D 10
#include <sys/file.h>
E 10
#include <sys/stat.h>
I 25

E 25
I 10
D 31
#include <fcntl.h>
E 10
#include <errno.h>
I 15
#ifdef DEBUG
E 15
#include <assert.h>
I 15
#endif
E 31
E 15
D 32
#include <db.h>
E 32
I 31
#include <errno.h>
#include <fcntl.h>
E 31
I 6
D 10
#include <unistd.h>
E 10
I 8
#include <stdio.h>
E 8
E 6
D 10
#include "hash.h"
E 10
I 10
#include <stdlib.h>
D 31
#include <unistd.h>
E 31
E 10
#include <string.h>
I 31
#include <unistd.h>
#ifdef DEBUG
#include <assert.h>
#endif

I 32
#include <db.h>
E 32
E 31
I 10
#include "hash.h"
I 15
#include "page.h"
#include "extern.h"
E 15
E 10

I 15
D 31
static int   alloc_segs __P((int));
static int   flush_meta __P((void));
static int   hash_access __P((ACTION, DBT *, DBT *));
E 31
I 31
static int   alloc_segs __P((HTAB *, int));
static int   flush_meta __P((HTAB *));
static int   hash_access __P((HTAB *, ACTION, DBT *, DBT *));
E 31
static int   hash_close __P((DB *));
static int   hash_delete __P((const DB *, const DBT *, u_int));
I 36
static int   hash_fd __P((const DB *));
E 36
D 16
static int   hash_get __P((const DB *, DBT *, DBT *, u_int));
E 16
I 16
static int   hash_get __P((const DB *, const DBT *, DBT *, u_int));
E 16
D 30
static int   hash_put __P((const DB *, const DBT *, const DBT *, u_int));
E 30
I 30
static int   hash_put __P((const DB *, DBT *, const DBT *, u_int));
E 30
static void *hash_realloc __P((SEGMENT **, int, int));
static int   hash_seq __P((const DB *, DBT *, DBT *, u_int));
D 35
static int   hash_sync __P((const DB *));
E 35
I 35
static int   hash_sync __P((const DB *, u_int));
E 35
D 31
static int   hdestroy __P((void));
static HTAB *init_hash __P((HASHINFO *));
static int   init_htab __P((int));
E 31
I 31
static int   hdestroy __P((HTAB *));
D 36
static HTAB *init_hash __P((HTAB *, HASHINFO *));
E 36
I 36
static HTAB *init_hash __P((HTAB *, const char *, HASHINFO *));
E 36
static int   init_htab __P((HTAB *, int));
E 31
#if BYTE_ORDER == LITTLE_ENDIAN
D 31
static void  swap_header __P((void));
E 31
I 31
D 34
static void  swap_header __P((HTAB *, void));
E 34
I 34
static void  swap_header __P((HTAB *));
E 34
E 31
static void  swap_header_copy __P((HASHHDR *, HASHHDR *));
#endif

E 15
D 5
/* For systems that do not have O_ACCMODE */
#ifndef O_ACCMODE
#define O_ACCMODE       (O_RDONLY|O_WRONLY|O_RDWR)
#endif

E 5
/* Fast arithmetic, relying on powers of 2, */
I 15
#define MOD(x, y)		((x) & ((y) - 1))
E 15

D 15
#define MOD(x,y)		((x) & ((y)-1))
#define RETURN_ERROR(ERR,LOC)	{ save_errno = ERR; goto LOC; }
E 15
I 15
#define RETURN_ERROR(ERR, LOC)	{ save_errno = ERR; goto LOC; }
E 15

/* Return values */
I 15
#define	SUCCESS	 (0)
#define	ERROR	(-1)
#define	ABNORMAL (1)
E 15

D 15
#define	SUCCESS	0
#define	ERROR	-1
#define	ABNORMAL 1
D 10

/* external routines */
extern char *calloc();
E 10

/* page.c */
extern int __get_page();
extern int __split_page();
extern int __addel();
extern int __delpair();
extern u_long *__init_bitmap();

/* big.c */
D 13
extern void __big_return();
E 13
I 13
extern int __big_return();
E 13
extern int __big_keydata();
extern u_short __find_last_page();

/* buf.c */
extern BUFHEAD	*__get_buf();
extern void __buf_init();
extern int __buf_free();

/* hash function */
extern int (*default_hash)();

/* My externals */
extern int __expand_table();
D 13
extern int __call_hash();
E 13
I 13
extern u_int __call_hash();
E 13

/* Internal routines */
static HTAB *init_hash();
static int hash_access();
static int flush_meta();
static int alloc_segs();
static int init_htab();
static char *hash_realloc();
static int hdestroy();
static int hash_put();
static int hash_delete();
static int hash_get();
static int hash_sync();
static int hash_close();
static int hash_seq();
static void swap_header_copy();
static void swap_header();

E 15
D 31
/* Local data */
D 15

E 15
HTAB *hashp = NULL;

E 31
#ifdef HASH_STATISTICS
long hash_accesses, hash_collisions, hash_expansions, hash_overflows;
#endif

D 15
/************************** INTERFACE ROUTINES **********************/
E 15
I 15
/************************** INTERFACE ROUTINES ***************************/
E 15
/* OPEN/CLOSE */

D 15
extern	DB *
hash_open ( file, flags, mode, info )
D 9
char	*file;
E 9
I 9
const char	*file;
E 9
int	flags;
int	mode;
D 9
HASHINFO	*info;		/* Special directives for create */
E 9
I 9
const HASHINFO	*info;		/* Special directives for create */
E 15
I 15
extern DB *
D 18
hash_open(file, flags, mode, info)
E 18
I 18
D 41
__hash_open(file, flags, mode, info)
E 41
I 41
__hash_open(file, flags, mode, info, dflags)
E 41
E 18
	const char *file;
D 41
	int flags, mode;
E 41
I 41
	int flags, mode, dflags;
E 41
	const HASHINFO *info;	/* Special directives for create */
E 15
E 9
{
I 31
	HTAB *hashp;
E 31
D 15
    int		buckets;
    int		bpages;
    int		hdrsize;
    int		i;
    int		new_table = 0;
    int		nkey;
    int		nsegs;
    int		save_errno;
    struct	stat statbuf;
    DB		*dbp;
E 15
I 15
	struct stat statbuf;
	DB *dbp;
	int bpages, hdrsize, new_table, nsegs, save_errno;
E 15

I 27
D 28
	if (flags & O_WRONLY) {
E 28
I 28
	if ((flags & O_ACCMODE) == O_WRONLY) {
E 28
		errno = EINVAL;
		return (NULL);
	}

E 27
I 15
D 45
	if (!(hashp = calloc(1, sizeof(HTAB))))
E 45
I 45
	if (!(hashp = (HTAB *)calloc(1, sizeof(HTAB))))
E 45
		return (NULL);
	hashp->fp = -1;
I 41

E 41
	/*
D 41
	 * Select flags relevant to us. Even if user wants write only, we need
	 * to be able to read the actual file, so we need to open it read/write.
	 * But, the field in the hashp structure needs to be accurate so that
E 41
I 41
	 * Even if user wants write only, we need to be able to read
	 * the actual file, so we need to open it read/write. But, the
	 * field in the hashp structure needs to be accurate so that
E 41
	 * we can check accesses.
	 */
D 24
	hashp->flags = flags =
	    flags & (O_CREAT | O_EXCL | O_RDONLY | O_RDWR | O_TRUNC | O_WRONLY);
E 24
I 24
D 30
	hashp->flags = flags = flags & (O_CREAT | O_EXCL | O_EXLOCK | 
D 27
	    O_RDONLY | O_RDWR | O_SHLOCK | O_TRUNC | O_WRONLY);
E 24
	if (flags & O_WRONLY)
		flags = (flags & ~O_WRONLY) | O_RDWR;
E 27
I 27
	    O_RDONLY | O_RDWR | O_SHLOCK | O_TRUNC);
E 30
I 30
D 41
	hashp->flags = flags = flags & __USE_OPEN_FLAGS;
E 41
I 41
	hashp->flags = flags;
E 41
E 30
E 27
E 15

D 15
    if ( !(hashp = (HTAB *) calloc( 1, sizeof(HTAB) ))) {
	/* calloc should set errno */
	return(0);
    }
I 3
    hashp->fp = -1;
E 3
    /* 
	Select flags relevant to us.
	Even if user wants write only, we need to be able to read 
	the actual file, so we need to open it read/write.  But, the
	field in the hashp structure needs to be accurate so that
	we can check accesses.
    */
    flags = flags & (O_CREAT | O_EXCL | O_RDONLY | O_RDWR | O_TRUNC | O_WRONLY);
    hashp->flags = flags;
    if ( flags & O_WRONLY )  flags = (flags & ~O_WRONLY) | O_RDWR;

    if ( !file || 
	 (flags & O_TRUNC) || 
	 (stat ( file, &statbuf ) && (errno == ENOENT)) ) {
I 7
	 if ( errno == ENOENT ) {
	    errno = 0;		/* Just in case someone looks at errno */
	 }
E 7
	 new_table = 1;
    }

D 4
    if ( file && ((hashp->fp = open ( file, flags, mode )) == -1)) {
	RETURN_ERROR (errno, error0);
E 4
I 4
    if ( file ) {
	if ((hashp->fp = open ( file, flags, mode )) == -1) {
	    RETURN_ERROR (errno, error0);
E 15
I 15
	new_table = 0;
	if (!file || (flags & O_TRUNC) ||
	    (stat(file, &statbuf) && (errno == ENOENT))) {
		if (errno == ENOENT)
			errno = 0; /* Just in case someone looks at errno */
		new_table = 1;
E 15
	}
D 15
	(void)fcntl(hashp->fp, F_SETFD, 1);
E 4
    }
I 2
D 4
    (void)fcntl(hashp->fp, F_SETFD, 1);
E 4
E 2

    if ( new_table ) {
	if ( !(hashp = init_hash( info )) ) {
	    RETURN_ERROR(errno,error1);
E 15
I 15
	if (file) {
		if ((hashp->fp = open(file, flags, mode)) == -1)
			RETURN_ERROR(errno, error0);
		(void)fcntl(hashp->fp, F_SETFD, 1);
E 15
	}
D 15
    } else {
	/* Table already exists */
	if ( info && info->hash ) hashp->hash = info->hash;
	else hashp->hash = default_hash;
E 15
I 15
	if (new_table) {
D 31
		if (!(hashp = init_hash((HASHINFO *)info)))
E 31
I 31
D 36
		if (!(hashp = init_hash(hashp, (HASHINFO *)info)))
E 36
I 36
		if (!(hashp = init_hash(hashp, file, (HASHINFO *)info)))
E 36
E 31
			RETURN_ERROR(errno, error1);
	} else {
		/* Table already exists */
		if (info && info->hash)
			hashp->hash = info->hash;
		else
D 31
			hashp->hash = default_hash;
E 31
I 31
			hashp->hash = __default_hash;
E 31
E 15

D 15
	hdrsize = read ( hashp->fp, &hashp->hdr, sizeof(HASHHDR) );
E 15
I 15
		hdrsize = read(hashp->fp, &hashp->hdr, sizeof(HASHHDR));
E 15
#if BYTE_ORDER == LITTLE_ENDIAN
D 15
	swap_header ( );
E 15
I 15
D 31
		swap_header();
E 31
I 31
		swap_header(hashp);
E 31
E 15
#endif
D 15
	if ( hdrsize == -1 ) {
	    RETURN_ERROR(errno, error1);
	}
	if ( hdrsize != sizeof(HASHHDR) ) {
	    RETURN_ERROR(EFTYPE, error1);
	}
E 15
I 15
		if (hdrsize == -1)
			RETURN_ERROR(errno, error1);
		if (hdrsize != sizeof(HASHHDR))
			RETURN_ERROR(EFTYPE, error1);
		/* Verify file type, versions and hash function */
		if (hashp->MAGIC != HASHMAGIC)
			RETURN_ERROR(EFTYPE, error1);
D 17
		if (hashp->VERSION != VERSION_NO)
E 17
I 17
D 42
		if (hashp->VERSION != HASHVERSION)
E 42
I 42
#define	OLDHASHVERSION	1
		if (hashp->VERSION != HASHVERSION &&
		    hashp->VERSION != OLDHASHVERSION)
E 42
E 17
			RETURN_ERROR(EFTYPE, error1);
		if (hashp->hash(CHARKEY, sizeof(CHARKEY)) != hashp->H_CHARKEY)
			RETURN_ERROR(EFTYPE, error1);
D 16
		/* 
			Figure out how many segments we need. 
			Max_Bucket it the maximum bucket number, so the
			number of buckets is max_bucket+1.
		*/
		nsegs = (hashp->MAX_BUCKET + 1 + hashp->SGSIZE - 1) / 
E 16
I 16
		/*
		 * Figure out how many segments we need.  Max_Bucket is the
		 * maximum bucket number, so the number of buckets is
		 * max_bucket + 1.
		 */
		nsegs = (hashp->MAX_BUCKET + 1 + hashp->SGSIZE - 1) /
E 16
			 hashp->SGSIZE;
		hashp->nsegs = 0;
D 31
		if (alloc_segs(nsegs))
E 31
I 31
		if (alloc_segs(hashp, nsegs))
E 31
			/*
			 * If alloc_segs fails, table will have been destroyed
			 * and errno will have been set.
			 */
			return (NULL);
		/* Read in bitmaps */
D 17
		bpages = (hashp->SPARES[__log2(hashp->MAX_BUCKET)] +
E 17
I 17
		bpages = (hashp->SPARES[hashp->OVFL_POINT] +
E 17
		    (hashp->BSIZE << BYTE_SHIFT) - 1) >>
		    (hashp->BSHIFT + BYTE_SHIFT);
E 15

D 15
	/* Verify file type, versions and hash function */
	if ( hashp->MAGIC != HASHMAGIC ) 
	    RETURN_ERROR ( EFTYPE, error1 );
	if ( hashp->VERSION != VERSION_NO ) 
	    RETURN_ERROR ( EFTYPE, error1 );
	if (hashp->hash ( CHARKEY, sizeof(CHARKEY) ) != hashp->H_CHARKEY ) {
	    RETURN_ERROR ( EFTYPE, error1 );
E 15
I 15
		hashp->nmaps = bpages;
D 16
		memset(&hashp->mapp[0], 0, bpages * sizeof(u_long *));
E 16
I 16
		(void)memset(&hashp->mapp[0], 0, bpages * sizeof(u_long *));
E 16
E 15
	}

D 15
	/* 
	    Figure out how many segments we need.
	*/
	nsegs = (hashp->MAX_BUCKET + hashp->SGSIZE -1)/ hashp->SGSIZE;
	hashp->nsegs = 0;
	if (alloc_segs( nsegs )) {	
	    /* 
		If alloc_segs fails, table will have been destroyed 
		and errno will have been set.
	    */
	    return( (DB *) NULL );
E 15
I 15
	/* Initialize Buffer Manager */
	if (info && info->cachesize)
D 31
		__buf_init(info->cachesize);
E 31
I 31
		__buf_init(hashp, info->cachesize);
E 31
	else
D 31
		__buf_init(DEF_BUFSIZE);
E 31
I 31
		__buf_init(hashp, DEF_BUFSIZE);
E 31

	hashp->new_file = new_table;
D 27
	hashp->save_file = file && (hashp->flags & (O_WRONLY | O_RDWR));
E 27
I 27
	hashp->save_file = file && (hashp->flags & O_RDWR);
E 27
	hashp->cbucket = -1;
D 45
	if (!(dbp = malloc(sizeof(DB)))) {
E 45
I 45
	if (!(dbp = (DB *)malloc(sizeof(DB)))) {
E 45
		save_errno = errno;
D 31
		hdestroy();
E 31
I 31
		hdestroy(hashp);
E 31
		errno = save_errno;
		return (NULL);
E 15
	}
I 15
D 31
	dbp->internal = (char *)hashp;
E 31
I 31
	dbp->internal = hashp;
E 31
	dbp->close = hash_close;
	dbp->del = hash_delete;
I 36
	dbp->fd = hash_fd;
E 36
	dbp->get = hash_get;
	dbp->put = hash_put;
	dbp->seq = hash_seq;
	dbp->sync = hash_sync;
	dbp->type = DB_HASH;
E 15

D 15
	/* Read in bitmaps */
	bpages = (hashp->SPARES[__log2(hashp->MAX_BUCKET)] + 
		  (hashp->BSIZE << BYTE_SHIFT) - 1) >> 
		  (hashp->BSHIFT + BYTE_SHIFT);

I 7
	hashp->nmaps = bpages;
E 7
D 13
	hashp->mapp[0] = (u_long *)malloc(bpages<<hashp->BSHIFT);
	if ( !hashp->mapp[0] ) {
	    RETURN_ERROR(errno, error2);
	}
	for ( i = 0; i < bpages; i++ ) {
	    hashp->mapp[i] = &hashp->mapp[0][i<<hashp->BSHIFT];
	    if (__get_page ((char *)hashp->mapp[i],
		hashp->BITMAPS[i], 0, 1, 1)) {
		    RETURN_ERROR(errno, error2);
	    }
	}

E 13
I 13
	memset ( &hashp->mapp[0], 0, bpages * sizeof ( u_long *) );
E 13
    }

    /* Initialize Buffer Manager */
D 13
    if ( info && info->ncached ) {
	__buf_init (info->ncached);
E 13
I 13
    if ( info && info->cachesize ) {
	__buf_init (info->cachesize);
E 13
    } else {
	__buf_init (DEF_BUFSIZE);
    }

    hashp->new_file = new_table;
D 3
    hashp->save_file = (file != NULL);
E 3
I 3
D 13
    hashp->save_file = file && !(hashp->flags&O_RDONLY);
E 13
I 13
    hashp->save_file = file && (hashp->flags & (O_WRONLY|O_RDWR));
E 13
E 3
    hashp->cbucket = -1;
    if ( !(dbp = (DB *)malloc ( sizeof (DB) )) ) {
	save_errno = errno;
	hdestroy();
	errno = save_errno;
	return ( NULL );
    }
    dbp->internal = (char *)hashp;
    dbp->close = hash_close;
D 9
    dbp->delete = hash_delete;
E 9
I 9
    dbp->del = hash_delete;
E 9
    dbp->get = hash_get;
    dbp->put = hash_put;
    dbp->seq = hash_seq;
    dbp->sync = hash_sync;
I 14
    dbp->type = DB_HASH;
E 14

E 15
#ifdef DEBUG
D 15
	(void)fprintf(stderr, "%s\n%s%x\n%s%d\n%s%d\n%s%d\n%s%d\n%s%d\n%s%d\n%s%d\n%s%x\n%s%x\n%s%d\n%s%d\n",
		"init_htab:",
		"TABLE POINTER   ", hashp,
		"BUCKET SIZE     ", hashp->BSIZE,
		"BUCKET SHIFT    ", hashp->BSHIFT,
		"DIRECTORY SIZE  ", hashp->DSIZE,
		"SEGMENT SIZE    ", hashp->SGSIZE,
		"SEGMENT SHIFT   ", hashp->SSHIFT,
		"FILL FACTOR     ", hashp->FFACTOR,
		"MAX BUCKET      ", hashp->MAX_BUCKET,
		"HIGH MASK       ", hashp->HIGH_MASK,
		"LOW  MASK       ", hashp->LOW_MASK,
		"NSEGS           ", hashp->nsegs,
		"NKEYS           ", hashp->NKEYS );
E 15
I 15
	(void)fprintf(stderr,
D 17
"%s\n%s%x\n%s%d\n%s%d\n%s%d\n%s%d\n%s%d\n%s%d\n%s%d\n%s%x\n%s%x\n%s%d\n%s%d\n",
E 17
I 17
"%s\n%s%x\n%s%d\n%s%d\n%s%d\n%s%d\n%s%d\n%s%d\n%s%d\n%s%d\n%s%d\n%s%x\n%s%x\n%s%d\n%s%d\n",
E 17
	    "init_htab:",
	    "TABLE POINTER   ", hashp,
	    "BUCKET SIZE     ", hashp->BSIZE,
	    "BUCKET SHIFT    ", hashp->BSHIFT,
	    "DIRECTORY SIZE  ", hashp->DSIZE,
	    "SEGMENT SIZE    ", hashp->SGSIZE,
	    "SEGMENT SHIFT   ", hashp->SSHIFT,
	    "FILL FACTOR     ", hashp->FFACTOR,
	    "MAX BUCKET      ", hashp->MAX_BUCKET,
I 17
	    "OVFL POINT	     ", hashp->OVFL_POINT,
	    "LAST FREED      ", hashp->LAST_FREED,
E 17
	    "HIGH MASK       ", hashp->HIGH_MASK,
	    "LOW  MASK       ", hashp->LOW_MASK,
	    "NSEGS           ", hashp->nsegs,
	    "NKEYS           ", hashp->NKEYS);
E 15
#endif
#ifdef HASH_STATISTICS
	hash_overflows = hash_accesses = hash_collisions = hash_expansions = 0;
#endif
D 15
    return (dbp);
E 15
I 15
	return (dbp);
E 15

D 15
error2:
    (void)hdestroy();
    errno = save_errno;
D 3
    hashp->errno = errno;
E 3
    return ( (DB *)NULL );

E 15
error1:
D 15
    (void) close ( hashp->fp );
E 15
I 15
D 19
	(void)close(hashp->fp);
E 19
I 19
	if (hashp != NULL)
		(void)close(hashp->fp);
E 19
E 15

error0:
D 15
    free ( hashp );
    errno = save_errno;
D 3
    hashp->errno = errno;
E 3
    return ( (DB *) NULL );
E 15
I 15
	free(hashp);
	errno = save_errno;
	return (NULL);
E 15
}

static int
D 15
hash_close (dbp)
DB	*dbp;
E 15
I 15
hash_close(dbp)
	DB *dbp;
E 15
{
I 31
	HTAB *hashp;
E 31
I 3
D 15
	int	retval;
E 15
I 15
	int retval;
E 15

E 3
D 15
	if ( !dbp ) {
	    return(ERROR);
	}
E 15
I 15
	if (!dbp)
		return (ERROR);
I 31

E 31
E 15
	hashp = (HTAB *)dbp->internal;
D 3
	return (hdestroy());
E 3
I 3
D 31
	retval = hdestroy();
E 31
I 31
	retval = hdestroy(hashp);
E 31
D 15
	(void)free ( dbp );
	return ( retval );
E 15
I 15
	free(dbp);
	return (retval);
E 15
E 3
}

I 36
static int
hash_fd(dbp)
	const DB *dbp;
{
	HTAB *hashp;

	if (!dbp)
		return (ERROR);

	hashp = (HTAB *)dbp->internal;
	if (hashp->fp == -1) {
		errno = ENOENT;
		return (-1);
	}
	return (hashp->fp);
}

E 36
D 15

E 15
/************************** LOCAL CREATION ROUTINES **********************/
D 15
static HTAB * 
init_hash( info )
HASHINFO *info;
E 15
I 15
static HTAB *
D 31
init_hash(info)
E 31
I 31
D 36
init_hash(hashp, info)
E 36
I 36
init_hash(hashp, file, info)
E 36
	HTAB *hashp;
I 36
	const char *file;
E 36
E 31
	HASHINFO *info;
E 15
{
I 36
	struct stat statbuf;
E 36
D 15
	int	nelem;
E 15
I 15
	int nelem;
E 15

	nelem = 1;
I 17
	hashp->NKEYS = 0;
E 17
I 15
	hashp->LORDER = BYTE_ORDER;
	hashp->BSIZE = DEF_BUCKET_SIZE;
	hashp->BSHIFT = DEF_BUCKET_SHIFT;
	hashp->SGSIZE = DEF_SEGSIZE;
	hashp->SSHIFT = DEF_SEGSIZE_SHIFT;
	hashp->DSIZE = DEF_DIRSIZE;
	hashp->FFACTOR = DEF_FFACTOR;
D 31
	hashp->hash = default_hash;
E 31
I 31
	hashp->hash = __default_hash;
E 31
D 33
	bzero(hashp->SPARES, sizeof(hashp->SPARES));
I 17
	bzero (hashp->BITMAPS, sizeof (hashp->BITMAPS));
E 33
I 33
	memset(hashp->SPARES, 0, sizeof(hashp->SPARES));
	memset(hashp->BITMAPS, 0, sizeof (hashp->BITMAPS));
I 36

	/* Fix bucket size to be optimal for file system */
	if (file != NULL) {
		if (stat(file, &statbuf))
			return (NULL);
		hashp->BSIZE = statbuf.st_blksize;
		hashp->BSHIFT = __log2(hashp->BSIZE);
	}
E 36
E 33
E 17
E 15

D 15
	hashp->LORDER	= BYTE_ORDER;
	hashp->BSIZE    = DEF_BUCKET_SIZE;
	hashp->BSHIFT   = DEF_BUCKET_SHIFT;
	hashp->SGSIZE   = DEF_SEGSIZE;
	hashp->SSHIFT   = DEF_SEGSIZE_SHIFT;
	hashp->DSIZE    = DEF_DIRSIZE;
	hashp->FFACTOR  = DEF_FFACTOR;
	hashp->hash     = default_hash;
	bzero (hashp->SPARES, sizeof (hashp->SPARES));

	if ( info ) {
	    if ( info->bsize )   {
		/* Round pagesize up to power of 2 */
		hashp->BSHIFT  = __log2(info->bsize);
		hashp->BSIZE   = 1 << hashp->BSHIFT;
		if ( hashp->BSIZE > MAX_BSIZE ) {
		    errno = EINVAL;
		    return(0);
E 15
I 15
	if (info) {
		if (info->bsize) {
			/* Round pagesize up to power of 2 */
			hashp->BSHIFT = __log2(info->bsize);
			hashp->BSIZE = 1 << hashp->BSHIFT;
			if (hashp->BSIZE > MAX_BSIZE) {
				errno = EINVAL;
				return (NULL);
			}
E 15
		}
D 15
	    }
	    if ( info->ffactor )  hashp->FFACTOR = info->ffactor;
	    if ( info->hash ) hashp->hash    = info->hash;
	    if ( info->nelem ) nelem = info->nelem;
	    if ( info->lorder ) {
		if ( info->lorder != BIG_ENDIAN && 
		     info->lorder != LITTLE_ENDIAN) {
		    errno = EINVAL;
		    return(0);
E 15
I 15
		if (info->ffactor)
			hashp->FFACTOR = info->ffactor;
		if (info->hash)
			hashp->hash = info->hash;
		if (info->nelem)
			nelem = info->nelem;
		if (info->lorder) {
			if (info->lorder != BIG_ENDIAN &&
			    info->lorder != LITTLE_ENDIAN) {
				errno = EINVAL;
				return (NULL);
			}
			hashp->LORDER = info->lorder;
E 15
		}
D 15
		hashp->LORDER = info->lorder;
	    }
E 15
	}
D 15

E 15
	/* init_htab should destroy the table and set errno if it fails */
D 15
	if ( init_htab ( nelem ) ) {
	    return(0);
	} else {
	    return(hashp);
	}
E 15
I 15
D 31
	if (init_htab(nelem))
E 31
I 31
	if (init_htab(hashp, nelem))
E 31
		return (NULL);
	else
		return (hashp);
E 15
}
D 15

E 15
/*
D 15
    This calls alloc_segs which may run out of memory.
    Alloc_segs will destroy the table and set errno,
    so we just pass the error information along.

    Returns 0 on No Error

*/
E 15
I 15
 * This calls alloc_segs which may run out of memory.  Alloc_segs will destroy
 * the table and set errno, so we just pass the error information along.
 *
 * Returns 0 on No Error
 */
E 15
static int
D 15
init_htab ( nelem )
int	nelem;
E 15
I 15
D 31
init_htab(nelem)
E 31
I 31
init_htab(hashp, nelem)
	HTAB *hashp;
E 31
	int nelem;
E 15
{
D 15
	register SEGMENT	*segp;
	register int nbuckets;
	register int nsegs;
	int	l2;
E 15
I 15
	register int nbuckets, nsegs;
	int l2;
E 15

D 15
 /*
  * Divide number of elements by the fill factor and determine a desired
  * number of buckets.  Allocate space for the next greater power of
  * two number of buckets
  */
E 15
I 15
	/*
	 * Divide number of elements by the fill factor and determine a
	 * desired number of buckets.  Allocate space for the next greater
	 * power of two number of buckets.
	 */
E 15
	nelem = (nelem - 1) / hashp->FFACTOR + 1;

D 23
	l2 = __log2(nelem);
E 23
I 23
	l2 = __log2(MAX(nelem, 2));
E 23
	nbuckets = 1 << l2;
D 15
	nbuckets = MAX ( nbuckets, 2 );
E 15
I 15
D 23
	nbuckets = MAX(nbuckets, 2);
E 23
E 15

	hashp->SPARES[l2] = l2 + 1;
D 15
	hashp->SPARES[l2+1] = l2 + 1;
	/* 
	    First bitmap page is at:
		splitpoint l2
		page offset 1
	*/
	__init_bitmap ( OADDR_OF(l2,1), l2+1, 0 );
E 15
I 15
	hashp->SPARES[l2 + 1] = l2 + 1;
I 17
	hashp->OVFL_POINT = l2;
	hashp->LAST_FREED = 2;

E 17
	/* First bitmap page is at: splitpoint l2 page offset 1 */
D 16
	__init_bitmap(OADDR_OF(l2, 1), l2 + 1, 0);
E 16
I 16
D 31
	if (__init_bitmap(OADDR_OF(l2, 1), l2 + 1, 0))
E 31
I 31
	if (__init_bitmap(hashp, OADDR_OF(l2, 1), l2 + 1, 0))
E 31
		return (-1);
E 16
E 15

	hashp->MAX_BUCKET = hashp->LOW_MASK = nbuckets - 1;
	hashp->HIGH_MASK = (nbuckets << 1) - 1;
D 15
	hashp->HDRPAGES = ((MAX(sizeof(HASHHDR),MINHDRSIZE) - 1) >> 
			  hashp->BSHIFT) + 1;
E 15
I 15
	hashp->HDRPAGES = ((MAX(sizeof(HASHHDR), MINHDRSIZE) - 1) >>
	    hashp->BSHIFT) + 1;
E 15

	nsegs = (nbuckets - 1) / hashp->SGSIZE + 1;
	nsegs = 1 << __log2(nsegs);

D 15
	if ( nsegs > hashp->DSIZE ) {
	    hashp->DSIZE  = nsegs;
	}

	return (alloc_segs ( nsegs ) );
E 15
I 15
	if (nsegs > hashp->DSIZE)
		hashp->DSIZE = nsegs;
D 31
	return (alloc_segs(nsegs));
E 31
I 31
	return (alloc_segs(hashp, nsegs));
E 31
E 15
}

/********************** DESTROY/CLOSE ROUTINES ************************/

/*
D 15
    Flushes any changes to the file if necessary and
    destroys the hashp structure, freeing all allocated
    space.
*/
E 15
I 15
 * Flushes any changes to the file if necessary and destroys the hashp
 * structure, freeing all allocated space.
 */
E 15
static int
D 31
hdestroy()
E 31
I 31
hdestroy(hashp)
	HTAB *hashp;
E 31
{
D 15
	int	save_errno;
	int	i;
E 15
I 15
	int i, save_errno;
E 15
I 7
D 13
	u_long	**mapp;
E 13
E 7

	save_errno = 0;

D 31
	if (hashp != NULL) {
E 31
#ifdef HASH_STATISTICS
D 15
	 (void)	fprintf(stderr,	"hdestroy: accesses %ld collisions %ld\n",
			hash_accesses, hash_collisions);
	 (void)	fprintf(stderr, "hdestroy: expansions %ld\n",
			hash_expansions);
	 (void)	fprintf(stderr, "hdestroy: overflows %ld\n",
			hash_overflows);
	 (void)	fprintf(stderr,	"keys %ld maxp %d segmentcount %d\n",
			hashp->NKEYS, hashp->MAX_BUCKET, hashp->nsegs);
E 15
I 15
D 31
		(void)fprintf(stderr, "hdestroy: accesses %ld collisions %ld\n",
		    hash_accesses, hash_collisions);
		(void)fprintf(stderr, "hdestroy: expansions %ld\n",
		    hash_expansions);
		(void)fprintf(stderr, "hdestroy: overflows %ld\n",
		    hash_overflows);
		(void)fprintf(stderr, "keys %ld maxp %d segmentcount %d\n",
		    hashp->NKEYS, hashp->MAX_BUCKET, hashp->nsegs);
E 31
I 31
	(void)fprintf(stderr, "hdestroy: accesses %ld collisions %ld\n",
	    hash_accesses, hash_collisions);
	(void)fprintf(stderr, "hdestroy: expansions %ld\n",
	    hash_expansions);
	(void)fprintf(stderr, "hdestroy: overflows %ld\n",
	    hash_overflows);
	(void)fprintf(stderr, "keys %ld maxp %d segmentcount %d\n",
	    hashp->NKEYS, hashp->MAX_BUCKET, hashp->nsegs);
E 31
E 15

D 15
	for ( i = 0; i < NCACHED; i++ ) {
	    (void) fprintf ( stderr, "spares[%d] = %d\n", i, hashp->SPARES[i] );
	}
E 15
I 15
D 31
		for (i = 0; i < NCACHED; i++)
			(void)fprintf(stderr,
			    "spares[%d] = %d\n", i, hashp->SPARES[i]);
E 31
I 31
	for (i = 0; i < NCACHED; i++)
		(void)fprintf(stderr,
		    "spares[%d] = %d\n", i, hashp->SPARES[i]);
E 31
E 15
#endif
D 15

		/* 
		    Call on buffer manager to free buffers, and if
		    required, write them to disk
		*/
		if (__buf_free(1, hashp->save_file)) {
		    save_errno = errno;
E 15
I 15
D 31
		/*
		 * Call on buffer manager to free buffers, and if required,
		 * write them to disk.
		 */
		if (__buf_free(1, hashp->save_file))
			save_errno = errno;
		if (hashp->dir) {
			free(*hashp->dir);	/* Free initial segments */
			/* Free extra segments */
			while (hashp->exsegs--)
				free(hashp->dir[--hashp->nsegs]);
			free(hashp->dir);
E 15
		}
D 15
		if ( hashp->dir ) {
		    (void)free(*hashp->dir);	/* Free initial segments */
		    /* Free extra segments */
		    while ( hashp->exsegs-- ) {
			(void)free ( hashp->dir[--hashp->nsegs] );
		    }
		    (void)free(hashp->dir);
		}
		if (flush_meta() && !save_errno) {
		    save_errno = errno;
		}
I 7

E 15
I 15
		if (flush_meta() && !save_errno)
			save_errno = errno;
E 15
D 13
		/* Free Initial Bigmaps */
		if ( hashp->nmaps ) {
		    (void)free(hashp->mapp[0]);	
E 13
I 13
		/* Free Bigmaps */
D 15
		for ( i = 0; i < hashp->nmaps; i++ ) {
		    if ( hashp->mapp[i] ) {
			(void) free ( hashp->mapp[i] );
		    }
E 13
		}
E 15
I 15
		for (i = 0; i < hashp->nmaps; i++)
			if (hashp->mapp[i])
				free(hashp->mapp[i]);
E 15

D 13
		/* Free extra bitmaps */
		for ( mapp = &hashp->mapp[hashp->nmaps]; 
		      hashp->exmaps--; 
		      mapp++ ) {
		      (void) free ( *mapp );
		}

E 13
E 7
D 3
		if ( hashp->save_file ) (void)close (hashp->fp);
E 3
I 3
D 15
		if ( hashp->fp != -1 ) {
			(void)close (hashp->fp);
		}
E 3
		(void)free(hashp);
E 15
I 15
		if (hashp->fp != -1)
			(void)close(hashp->fp);
		free(hashp);
E 15
		hashp = NULL;
E 31
I 31
	/*
	 * Call on buffer manager to free buffers, and if required,
	 * write them to disk.
	 */
	if (__buf_free(hashp, 1, hashp->save_file))
		save_errno = errno;
	if (hashp->dir) {
		free(*hashp->dir);	/* Free initial segments */
		/* Free extra segments */
		while (hashp->exsegs--)
			free(hashp->dir[--hashp->nsegs]);
		free(hashp->dir);
E 31
	}
I 31
	if (flush_meta(hashp) && !save_errno)
		save_errno = errno;
	/* Free Bigmaps */
	for (i = 0; i < hashp->nmaps; i++)
		if (hashp->mapp[i])
			free(hashp->mapp[i]);

	if (hashp->fp != -1)
		(void)close(hashp->fp);

I 43
	free(hashp);

E 43
E 31
D 15
	if ( save_errno ) {
	    errno = save_errno;
	    return(ERROR);
	} else {
	    return(SUCCESS);
E 15
I 15
	if (save_errno) {
		errno = save_errno;
		return (ERROR);
E 15
	}
I 15
	return (SUCCESS);
E 15
}
D 15

/* 
    Write modified pages to disk 
    0 == OK
    -1 ERROR
*/
E 15
I 15
/*
 * Write modified pages to disk
 *
 * Returns:
 *	 0 == OK
 *	-1 ERROR
 */
E 15
static int
D 35
hash_sync(dbp)
E 35
I 35
hash_sync(dbp, flags)
E 35
D 15
DB	*dbp;
E 15
I 15
	const DB *dbp;
I 35
	u_int flags;
E 35
E 15
{
I 31
	HTAB *hashp;
I 35

	if (flags != 0) {
		errno = EINVAL;
		return (ERROR);
	}
E 35

E 31
D 15
	if ( !dbp ) {
	    return (ERROR);
	}

E 15
I 15
	if (!dbp)
		return (ERROR);
E 15
D 31
	hashp = (HTAB *)dbp->internal;
E 31

I 31
	hashp = (HTAB *)dbp->internal;
E 31
D 15
	if (!hashp->save_file) return(0);
	if ( __buf_free ( 0, 1 )  || flush_meta()) {
	    return(ERROR);
	}
E 15
I 15
	if (!hashp->save_file)
		return (0);
D 31
	if (__buf_free(0, 1) || flush_meta())
E 31
I 31
	if (__buf_free(hashp, 0, 1) || flush_meta(hashp))
E 31
		return (ERROR);
E 15
	hashp->new_file = 0;
D 15
	return(0);
E 15
I 15
	return (0);
E 15
}

/*
D 15
0 == OK
-1 indicates that errno should be set
*/
E 15
I 15
 * Returns:
 *	 0 == OK
 *	-1 indicates that errno should be set
 */
E 15
static int
D 31
flush_meta()
E 31
I 31
flush_meta(hashp)
	HTAB *hashp;
E 31
{
D 15
    	int	fp;
	int	hdrsize;
	int	i;
	int	wsize;
	HASHHDR	*whdrp;
	HASHHDR	whdr;
E 15
I 15
D 21
	HASHHDR *whdrp;
E 21
I 21
D 22
	HASHHDR *whdrp, whdr;
E 22
I 22
	HASHHDR *whdrp;
#if BYTE_ORDER == LITTLE_ENDIAN
	HASHHDR whdr;
#endif
E 22
E 21
	int fp, i, wsize;
E 15

D 15
	if (!hashp->save_file) return(0);
E 15
I 15
	if (!hashp->save_file)
		return (0);
E 15
	hashp->MAGIC = HASHMAGIC;
D 17
	hashp->VERSION = VERSION_NO;
E 17
I 17
	hashp->VERSION = HASHVERSION;
E 17
D 15
	hashp->H_CHARKEY = hashp->hash ( CHARKEY, sizeof(CHARKEY));
E 15
I 15
	hashp->H_CHARKEY = hashp->hash(CHARKEY, sizeof(CHARKEY));
E 15

	fp = hashp->fp;
	whdrp = &hashp->hdr;
#if BYTE_ORDER == LITTLE_ENDIAN
	whdrp = &whdr;
D 15
	swap_header_copy( &hashp->hdr, whdrp );
E 15
I 15
	swap_header_copy(&hashp->hdr, whdrp);
E 15
#endif
D 6
	if ( (lseek (fp, 0, L_SET) == -1 ) ||
E 6
I 6
D 15
	if ( (lseek (fp, 0, SEEK_SET) == -1 ) ||
E 6
	     ((wsize = write ( fp, whdrp, sizeof(HASHHDR))) == -1)) {
	    return(-1);
	} else if ( wsize != sizeof(HASHHDR) ) {
	    errno = EFTYPE;
	    hashp->errno = errno;
	    return(-1);
	}
	for ( i = 0; i < NCACHED; i++ ) {
	    if ( hashp->mapp[i] ) {
		if (!__put_page((char *)hashp->mapp[i],
		    hashp->BITMAPS[i], 0, 1)){
		    return(-1);
E 15
I 15
D 29
	if ((lseek(fp, 0, SEEK_SET) == -1) ||
E 29
I 29
	if ((lseek(fp, (off_t)0, SEEK_SET) == -1) ||
E 29
	    ((wsize = write(fp, whdrp, sizeof(HASHHDR))) == -1))
		return (-1);
	else
		if (wsize != sizeof(HASHHDR)) {
			errno = EFTYPE;
			hashp->errno = errno;
			return (-1);
E 15
		}
D 15
	    }
	}
	return(0);
E 15
I 15
	for (i = 0; i < NCACHED; i++)
		if (hashp->mapp[i])
D 18
			if (!__put_page((char *)hashp->mapp[i],
E 18
I 18
D 31
			if (__put_page((char *)hashp->mapp[i],
E 31
I 31
			if (__put_page(hashp, (char *)hashp->mapp[i],
E 31
E 18
				hashp->BITMAPS[i], 0, 1))
				return (-1);
	return (0);
E 15
}
I 15

E 15
/*******************************SEARCH ROUTINES *****************************/
/*
D 15
    All the access routines return 
	0 on SUCCESS
	1 to indicate an external ERROR (i.e. key not found, etc)
	-1 to indicate an internal ERROR (i.e. out of memory, etc)
*/
E 15
I 15
 * All the access routines return
 *
 * Returns:
 *	 0 on SUCCESS
 *	 1 to indicate an external ERROR (i.e. key not found, etc)
 *	-1 to indicate an internal ERROR (i.e. out of memory, etc)
 */
E 15
static int
D 11
hash_get ( dbp, key, data )
E 11
I 11
D 15
hash_get ( dbp, key, data, flag )
E 11
DB	*dbp;
D 11
DBT *key, *data;
E 11
I 11
DBT	*key, *data;
D 13
u_long	flag;
E 13
I 13
u_int	flag;
E 15
I 15
hash_get(dbp, key, data, flag)
	const DB *dbp;
D 16
	DBT *key, *data;
E 16
I 16
	const DBT *key;
	DBT *data;
E 16
	u_int flag;
E 15
E 13
E 11
{
I 31
	HTAB *hashp;

	hashp = (HTAB *)dbp->internal;
E 31
I 11
D 15
#ifdef lint
    flag = flag;
#endif

E 11
    if ( !dbp ) {
	return (ERROR);
    }
    hashp = (HTAB *)dbp->internal;
    if ( hashp->flags & O_WRONLY ) {
	errno = EBADF;
	hashp->errno = errno;
	return ( ERROR );
    }
    return ( hash_access ( HASH_GET, key, data ) );
E 15
I 15
	if (flag) {
		hashp->errno = errno = EINVAL;
		return (ERROR);
	}
D 31
	hashp = (HTAB *)dbp->internal;
D 27
	if (hashp->flags & O_WRONLY) {
		hashp->errno = errno = EPERM;
		return (ERROR);
	}
E 27
D 16
	return (hash_access(HASH_GET, key, data));
E 16
I 16
	return (hash_access(HASH_GET, (DBT *)key, data));
E 31
I 31
	return (hash_access(hashp, HASH_GET, (DBT *)key, data));
E 31
E 16
E 15
}

static int
D 15
hash_put ( dbp, key, data, flag )
DB	*dbp;
DBT 	*key, *data;
D 11
int	flag;
E 11
I 11
D 13
u_long	flag;
E 13
I 13
u_int	flag;
E 15
I 15
hash_put(dbp, key, data, flag)
	const DB *dbp;
D 30
	const DBT *key, *data;
E 30
I 30
	DBT *key;
	const DBT *data;
E 30
	u_int flag;
E 15
E 13
E 11
{
I 31
	HTAB *hashp;

	hashp = (HTAB *)dbp->internal;
E 31
D 15
    if ( !dbp ) {
	return (ERROR);
    }
    hashp = (HTAB *)dbp->internal;
    if ( (hashp->flags & O_ACCMODE) == O_RDONLY ) {
	errno = EBADF;
	hashp->errno = errno;
	return ( ERROR );
    }
    if ( flag == R_NOOVERWRITE ) {
	return ( hash_access ( HASH_PUTNEW, key, data ) );
    } else {
	return ( hash_access ( HASH_PUT, key, data ) );
    }
E 15
I 15
	if (flag && flag != R_NOOVERWRITE) {
		hashp->errno = errno = EINVAL;
		return (ERROR);
	}
D 31
	hashp = (HTAB *)dbp->internal;
E 31
	if ((hashp->flags & O_ACCMODE) == O_RDONLY) {
		hashp->errno = errno = EPERM;
		return (ERROR);
	}
D 16
	return (hash_access(flag == R_NOOVERWRITE ? 
E 16
I 16
D 31
	return (hash_access(flag == R_NOOVERWRITE ?
E 31
I 31
	return (hash_access(hashp, flag == R_NOOVERWRITE ?
E 31
E 16
	    HASH_PUTNEW : HASH_PUT, (DBT *)key, (DBT *)data));
E 15
}

static int
D 11
hash_delete ( dbp, key, flags )
E 11
I 11
D 15
hash_delete ( dbp, key, flag )
E 11
DB	*dbp;
DBT 	*key;
D 11
int	flags;		/* Ignored */
E 11
I 11
D 13
u_long	flag;		/* Ignored */
E 13
I 13
u_int	flag;		/* Ignored */
E 15
I 15
hash_delete(dbp, key, flag)
	const DB *dbp;
	const DBT *key;
	u_int flag;		/* Ignored */
E 15
E 13
E 11
{
I 31
	HTAB *hashp;

	hashp = (HTAB *)dbp->internal;
E 31
I 11
D 15
#ifdef lint
    flag = flag;
#endif
E 11
    if ( !dbp ) {
	return (ERROR);
    }
    hashp = (HTAB *)dbp->internal;
    if ( (hashp->flags & O_ACCMODE) == O_RDONLY ) {
	errno = EBADF;
	hashp->errno = errno;
	return ( ERROR );
    }
    return ( hash_access ( HASH_DELETE, key, NULL ) );
E 15
I 15
	if (flag && flag != R_CURSOR) {
		hashp->errno = errno = EINVAL;
		return (ERROR);
	}
D 31
	hashp = (HTAB *)dbp->internal;
E 31
	if ((hashp->flags & O_ACCMODE) == O_RDONLY) {
		hashp->errno = errno = EPERM;
		return (ERROR);
	}
D 31
	return (hash_access(HASH_DELETE, (DBT *)key, NULL));
E 31
I 31
	return (hash_access(hashp, HASH_DELETE, (DBT *)key, NULL));
E 31
E 15
}

/*
D 15
    Assume that hashp has been set in wrapper routine
*/
E 15
I 15
 * Assume that hashp has been set in wrapper routine.
 */
E 15
static int
D 31
hash_access(action, key, val)
E 31
I 31
hash_access(hashp, action, key, val)
	HTAB *hashp;
E 31
D 15
ACTION action;
DBT *key, *val;
E 15
I 15
	ACTION action;
	DBT *key, *val;
E 15
{
D 15
	register	BUFHEAD	*rbufp;
	register	u_short	*bp;
	register	int	ndx;
	register 	int n;
	register 	int off = hashp->BSIZE;
	register	int		size;
	register	char	*kp;
	BUFHEAD	*bufp;
I 3
	BUFHEAD	*save_bufp;
E 3
	u_short	pageno;
E 15
I 15
	register BUFHEAD *rbufp;
	BUFHEAD *bufp, *save_bufp;
	register u_short *bp;
	register int n, ndx, off, size;
	register char *kp;
	u_short pageno;
E 15

#ifdef HASH_STATISTICS
	hash_accesses++;
#endif

I 15
	off = hashp->BSIZE;
E 15
	size = key->size;
D 12
	kp = key->data;
E 12
I 12
	kp = (char *)key->data;
E 12
D 3
	rbufp = __get_buf ( __call_hash(key->data, size), NULL, 0 );
E 3
I 3
D 15
	rbufp = __get_buf ( __call_hash(kp, size), NULL, 0 );
E 3
	if ( !rbufp ) return(ERROR);
E 15
I 15
D 31
	rbufp = __get_buf(__call_hash(kp, size), NULL, 0);
E 31
I 31
	rbufp = __get_buf(hashp, __call_hash(hashp, kp, size), NULL, 0);
E 31
	if (!rbufp)
		return (ERROR);
E 15
I 3
	save_bufp = rbufp;
E 3

I 3
	/* Pin the bucket chain */
	rbufp->flags |= BUF_PIN;
E 3
D 15
	for ( bp = (u_short *)rbufp->page, n = *bp++, ndx = 1; ndx < n;  ) {
	    if ( bp[1] >= REAL_KEY ) {
		/* Real key/data pair */
		if (size == off - *bp && 
		    bcmp(kp, rbufp->page + *bp, size) == 0) {
		    goto found;
		}
		off = bp[1];
E 15
I 15
	for (bp = (u_short *)rbufp->page, n = *bp++, ndx = 1; ndx < n;)
		if (bp[1] >= REAL_KEY) {
			/* Real key/data pair */
			if (size == off - *bp &&
D 33
			    bcmp(kp, rbufp->page + *bp, size) == 0)
E 33
I 33
			    memcmp(kp, rbufp->page + *bp, size) == 0)
E 33
				goto found;
			off = bp[1];
E 15
#ifdef HASH_STATISTICS
D 15
		hash_collisions++;
E 15
I 15
			hash_collisions++;
E 15
#endif
D 15
	        bp += 2; 
	        ndx += 2;
	    } else if ( bp[1] == OVFLPAGE ) {
		rbufp = __get_buf ( *bp, rbufp, 0 );
D 3
		if ( !rbufp ) return (ERROR);
E 3
I 3
		if ( !rbufp ) {
		    save_bufp->flags &= ~BUF_PIN;
		    return (ERROR);
E 15
I 15
			bp += 2;
			ndx += 2;
		} else if (bp[1] == OVFLPAGE) {
D 31
			rbufp = __get_buf(*bp, rbufp, 0);
E 31
I 31
			rbufp = __get_buf(hashp, *bp, rbufp, 0);
E 31
			if (!rbufp) {
				save_bufp->flags &= ~BUF_PIN;
				return (ERROR);
			}
			/* FOR LOOP INIT */
			bp = (u_short *)rbufp->page;
			n = *bp++;
			ndx = 1;
			off = hashp->BSIZE;
		} else if (bp[1] < REAL_KEY) {
D 31
			if ((ndx = __find_bigpair(rbufp, ndx, kp, size)) > 0)
E 31
I 31
			if ((ndx =
			    __find_bigpair(hashp, rbufp, ndx, kp, size)) > 0)
E 31
				goto found;
			if (ndx == -2) {
				bufp = rbufp;
D 31
				if (!(pageno = __find_last_page(&bufp))) {
E 31
I 31
				if (!(pageno =
				    __find_last_page(hashp, &bufp))) {
E 31
					ndx = 0;
					rbufp = bufp;
					break;	/* FOR */
				}
D 31
				rbufp = __get_buf(pageno, bufp, 0);
E 31
I 31
				rbufp = __get_buf(hashp, pageno, bufp, 0);
E 31
				if (!rbufp) {
					save_bufp->flags &= ~BUF_PIN;
					return (ERROR);
				}
				/* FOR LOOP INIT */
				bp = (u_short *)rbufp->page;
				n = *bp++;
				ndx = 1;
				off = hashp->BSIZE;
			} else {
				save_bufp->flags &= ~BUF_PIN;
				return (ERROR);
			}
E 15
		}
E 3
D 15
		/* FOR LOOP INIT */
		bp = (u_short *)rbufp->page;
		n = *bp++;
		ndx = 1;
		off = hashp->BSIZE;
	    } else if ( bp[1] < REAL_KEY ) {
		if ( (ndx = __find_bigpair(rbufp, ndx, kp, size )) > 0 ) {
		    goto found;
		} else if ( ndx == -2 ) {
		    bufp = rbufp;
		    if ( !(pageno = __find_last_page ( &bufp )) ) {
			ndx = 0;
			rbufp = bufp;
			break;	/* FOR */
		    }
		    rbufp = __get_buf ( pageno, bufp, 0 );
D 3
		    if ( !rbufp ) return (ERROR);
E 3
I 3
		    if ( !rbufp ) {
			save_bufp->flags &= ~BUF_PIN;
			return (ERROR);
		    }
E 3
		    /* FOR LOOP INIT */
		    bp = (u_short *)rbufp->page;
		    n = *bp++;
		    ndx = 1;
		    off = hashp->BSIZE;
		} else  {
I 3
		    save_bufp->flags &= ~BUF_PIN;
E 3
		    return(ERROR);
		}
	    } 
	}
E 15

	/* Not found */
D 15
	switch ( action ) {
	    case HASH_PUT:
	    case HASH_PUTNEW:
E 15
I 15
	switch (action) {
	case HASH_PUT:
	case HASH_PUTNEW:
E 15
D 31
		if (__addel(rbufp, key, val)) {
E 31
I 31
		if (__addel(hashp, rbufp, key, val)) {
E 31
I 3
D 15
		    save_bufp->flags &= ~BUF_PIN;
E 3
		    return(ERROR);
E 15
I 15
			save_bufp->flags &= ~BUF_PIN;
			return (ERROR);
E 15
		} else {
I 3
D 15
		    save_bufp->flags &= ~BUF_PIN;
E 3
		    return(SUCCESS);
E 15
I 15
			save_bufp->flags &= ~BUF_PIN;
			return (SUCCESS);
E 15
		}
D 15
	    case HASH_GET:
D 3
		return ( ABNORMAL );
E 3
	    case HASH_DELETE:
D 3
		return ( ABNORMAL );
E 3
	    default:
E 15
I 15
	case HASH_GET:
	case HASH_DELETE:
	default:
E 15
I 3
		save_bufp->flags &= ~BUF_PIN;
E 3
D 15
		return(ABNORMAL);
E 15
I 15
		return (ABNORMAL);
E 15
	}

found:
	switch (action) {
D 15
	    case HASH_PUTNEW:
E 15
I 15
	case HASH_PUTNEW:
E 15
I 3
		save_bufp->flags &= ~BUF_PIN;
E 3
D 15
		return(ABNORMAL);
	    case HASH_GET:
E 15
I 15
		return (ABNORMAL);
	case HASH_GET:
E 15
		bp = (u_short *)rbufp->page;
D 15
		if (bp[ndx+1] < REAL_KEY) __big_return(rbufp, ndx, val, 0);
E 15
I 15
D 18
		if (bp[ndx + 1] < REAL_KEY)
E 18
I 18
		if (bp[ndx + 1] < REAL_KEY) {
E 18
D 16
			__big_return(rbufp, ndx, val, 0);
E 16
I 16
D 31
			if (__big_return(rbufp, ndx, val, 0))
E 31
I 31
			if (__big_return(hashp, rbufp, ndx, val, 0))
E 31
				return (ERROR);
E 16
E 15
D 18
		else {
E 18
I 18
		} else {
E 18
D 12
		    val->data = rbufp->page + (int) bp[ndx + 1];
E 12
I 12
D 15
		    val->data = (u_char *)rbufp->page + (int) bp[ndx + 1];
E 12
		    val->size = bp[ndx] - bp[ndx + 1];
E 15
I 15
			val->data = (u_char *)rbufp->page + (int)bp[ndx + 1];
			val->size = bp[ndx] - bp[ndx + 1];
E 15
		}
		break;
D 15
	    case HASH_PUT:
D 3
		if (__delpair (rbufp, ndx))return(ERROR);
		if (__addel (rbufp, key, val)) return(ERROR);
E 3
I 3
		if ((__delpair (rbufp, ndx)) || (__addel (rbufp, key, val)) ) {
		    save_bufp->flags &= ~BUF_PIN;
		    return(ERROR);
E 15
I 15
	case HASH_PUT:
D 31
		if ((__delpair(rbufp, ndx)) || (__addel(rbufp, key, val))) {
E 31
I 31
		if ((__delpair(hashp, rbufp, ndx)) ||
		    (__addel(hashp, rbufp, key, val))) {
E 31
			save_bufp->flags &= ~BUF_PIN;
			return (ERROR);
E 15
		}
E 3
		break;
D 15
	    case HASH_DELETE:
		if (__delpair (rbufp, ndx))return(ERROR);
E 15
I 15
	case HASH_DELETE:
D 31
		if (__delpair(rbufp, ndx))
E 31
I 31
		if (__delpair(hashp, rbufp, ndx))
E 31
			return (ERROR);
E 15
		break;
I 31
	default:
		abort();
E 31
	}
I 3
	save_bufp->flags &= ~BUF_PIN;
E 3
	return (SUCCESS);
}

static int
hash_seq(dbp, key, data, flag)
D 15
DB	*dbp;
DBT 	*key, *data;
D 11
int flag;
E 11
I 11
D 13
u_long	flag;
E 13
I 13
u_int	flag;
E 15
I 15
	const DB *dbp;
	DBT *key, *data;
	u_int flag;
E 15
E 13
E 11
{
D 13
	register	int bucket;
E 13
I 13
D 15
	register	u_int bucket;
E 13
	register	BUFHEAD	*bufp;
I 3
	BUFHEAD	*save_bufp;
E 3
	u_short	*bp;
	u_short	ndx;
	u_short	pageno;
E 15
I 15
	register u_int bucket;
	register BUFHEAD *bufp;
I 31
	HTAB *hashp;
E 31
	u_short *bp, ndx;
E 15

I 31
	hashp = (HTAB *)dbp->internal;
E 31
D 15
	if ( !dbp ) {
	    return (ERROR);
E 15
I 15
	if (flag && flag != R_FIRST && flag != R_NEXT) {
		hashp->errno = errno = EINVAL;
		return (ERROR);
E 15
	}
D 15

E 15
D 31
	hashp = (HTAB *)dbp->internal;
E 31
D 15
	if ( hashp->flags & O_WRONLY ) {
	    errno = EBADF;
	    hashp->errno = errno;
	    return ( ERROR );
E 15
I 15
D 27
	if (hashp->flags & O_WRONLY) {
		hashp->errno = errno = EPERM;
		return (ERROR);
E 15
	}
E 27
#ifdef HASH_STATISTICS
	hash_accesses++;
#endif
D 15

	if ( (hashp->cbucket < 0) || (flag == R_FIRST) ) {
	    hashp->cbucket = 0;
	    hashp->cndx = 1;
	    hashp->cpage = NULL;
E 15
I 15
	if ((hashp->cbucket < 0) || (flag == R_FIRST)) {
		hashp->cbucket = 0;
		hashp->cndx = 1;
		hashp->cpage = NULL;
E 15
	}
I 15
D 25
	if (!(bufp = hashp->cpage)) {
		for (bucket = hashp->cbucket; bucket <= hashp->MAX_BUCKET;
		    bucket++, hashp->cndx = 1) {
E 25
E 15

D 15
	if ( !(bufp = hashp->cpage) ) {
	    for (bucket = hashp->cbucket; 
		 bucket <= hashp->MAX_BUCKET; 
		 bucket++, hashp->cndx = 1 ) {
E 15
I 15
D 25
			bufp = __get_buf(bucket, NULL, 0);
			if (!bufp)
				return (ERROR);
			hashp->cpage = bufp;
			bp = (u_short *)bufp->page;
			if (bp[0])
				break;
		}
		hashp->cbucket = bucket;
		if (hashp->cbucket > hashp->MAX_BUCKET) {
			hashp->cbucket = -1;
			return (ABNORMAL);
		}
	} else
		bp = (u_short *)hashp->cpage->page;
E 25
I 25
D 26
	for (bp = NULL; !bp || !bp[0]; ++hashp->cbucket) {
E 26
I 26
	for (bp = NULL; !bp || !bp[0]; ) {
E 26
		if (!(bufp = hashp->cpage)) {
			for (bucket = hashp->cbucket;
			    bucket <= hashp->MAX_BUCKET;
			    bucket++, hashp->cndx = 1) {
D 31
				bufp = __get_buf(bucket, NULL, 0);
E 31
I 31
				bufp = __get_buf(hashp, bucket, NULL, 0);
E 31
				if (!bufp)
					return (ERROR);
				hashp->cpage = bufp;
				bp = (u_short *)bufp->page;
				if (bp[0])
					break;
			}
			hashp->cbucket = bucket;
			if (hashp->cbucket > hashp->MAX_BUCKET) {
				hashp->cbucket = -1;
				return (ABNORMAL);
			}
		} else
			bp = (u_short *)hashp->cpage->page;
E 25
E 15

D 15
		bufp = __get_buf ( bucket, NULL, 0 );
		if (!bufp) return(ERROR);
		hashp->cpage = bufp;
		bp = (u_short *)bufp->page;
		if (bp[0]) break;
	    }
	    hashp->cbucket = bucket;
	    if ( hashp->cbucket > hashp->MAX_BUCKET ) {
		hashp->cbucket = -1;
		return ( ABNORMAL );
	    } 
	} else {
	    bp  = (u_short *)hashp->cpage->page;
	}
	
E 15
#ifdef DEBUG
D 15
	assert (bp);
	assert (bufp);
E 15
I 15
D 25
	assert(bp);
	assert(bufp);
E 25
I 25
		assert(bp);
		assert(bufp);
E 25
E 15
#endif
D 15
	while ( bp[hashp->cndx+1] == OVFLPAGE ) {
	    bufp = hashp->cpage = __get_buf ( bp[hashp->cndx], bufp, 0 );
	    if (!bufp) return(ERROR);
	    bp = (u_short *)(bufp->page);
	    hashp->cndx = 1;
E 15
I 15
D 25
	while (bp[hashp->cndx + 1] == OVFLPAGE) {
		bufp = hashp->cpage = __get_buf(bp[hashp->cndx], bufp, 0);
		if (!bufp)
			return (ERROR);
		bp = (u_short *)(bufp->page);
		hashp->cndx = 1;
E 25
I 25
		while (bp[hashp->cndx + 1] == OVFLPAGE) {
			bufp = hashp->cpage =
D 31
			    __get_buf(bp[hashp->cndx], bufp, 0);
E 31
I 31
			    __get_buf(hashp, bp[hashp->cndx], bufp, 0);
E 31
			if (!bufp)
				return (ERROR);
			bp = (u_short *)(bufp->page);
			hashp->cndx = 1;
		}
D 26
		if (!bp[0])
E 26
I 26
		if (!bp[0]) {
E 26
			hashp->cpage = NULL;
I 26
			++hashp->cbucket;
		}
E 26
E 25
E 15
	}
	ndx = hashp->cndx;
D 15
	if (bp[ndx+1] < REAL_KEY) {
	    if (__big_keydata(bufp, ndx, key, data, 1)) {
		return(ERROR);
	    }
E 15
I 15
	if (bp[ndx + 1] < REAL_KEY) {
D 16
		if (__big_keydata(bufp, ndx, key, data, 1))
E 16
I 16
D 31
		if (__big_keydata(bufp, key, data, 1))
E 31
I 31
		if (__big_keydata(hashp, bufp, key, data, 1))
E 31
E 16
			return (ERROR);
E 15
	} else {
D 12
	    key->data = hashp->cpage->page + bp[ndx];
E 12
I 12
D 15
	    key->data = (u_char *)hashp->cpage->page + bp[ndx];
E 12
	    key->size = (ndx > 1 ? bp[ndx-1] : hashp->BSIZE) - bp[ndx];
D 12
	    data->data = hashp->cpage->page + bp[ndx + 1];
E 12
I 12
	    data->data = (u_char *)hashp->cpage->page + bp[ndx + 1];
E 12
	    data->size = bp[ndx] - bp[ndx + 1];
	    ndx += 2;
	    if ( ndx > bp[0] ) {
		hashp->cpage = NULL;
		hashp->cbucket++;
		hashp->cndx=1;
	    } else hashp->cndx = ndx;
E 15
I 15
		key->data = (u_char *)hashp->cpage->page + bp[ndx];
		key->size = (ndx > 1 ? bp[ndx - 1] : hashp->BSIZE) - bp[ndx];
		data->data = (u_char *)hashp->cpage->page + bp[ndx + 1];
		data->size = bp[ndx] - bp[ndx + 1];
		ndx += 2;
		if (ndx > bp[0]) {
			hashp->cpage = NULL;
			hashp->cbucket++;
			hashp->cndx = 1;
		} else
			hashp->cndx = ndx;
E 15
	}
	return (SUCCESS);
}

/********************************* UTILITIES ************************/
I 15

E 15
/*
D 15
    0 ==> OK
    -1 ==> Error
*/
E 15
I 15
 * Returns:
 *	 0 ==> OK
 *	-1 ==> Error
 */
E 15
extern int
D 31
__expand_table()
E 31
I 31
__expand_table(hashp)
	HTAB *hashp;
E 31
{
D 13
	int	old_bucket, new_bucket;
E 13
I 13
D 15
	u_int	old_bucket, new_bucket;
E 13
	int	new_segnum;
	int	dirsize;
	int	spare_ndx;
	register	char **old, **new;
E 15
I 15
	u_int old_bucket, new_bucket;
	int dirsize, new_segnum, spare_ndx;

E 15
#ifdef HASH_STATISTICS
	hash_expansions++;
#endif
D 15

E 15
	new_bucket = ++hashp->MAX_BUCKET;
	old_bucket = (hashp->MAX_BUCKET & hashp->LOW_MASK);

	new_segnum = new_bucket >> hashp->SSHIFT;

	/* Check if we need a new segment */
D 15
	if ( new_segnum >= hashp->nsegs ) {

	    /* Check if we need to expand directory */
	    if ( new_segnum >= hashp->DSIZE ) {

		/* Reallocate directory */
		dirsize = hashp->DSIZE * sizeof ( SEGMENT * );
		if (!hash_realloc ( &hashp->dir, dirsize, (dirsize << 1 ) )) {
		    return(-1);
E 15
I 15
	if (new_segnum >= hashp->nsegs) {
		/* Check if we need to expand directory */
		if (new_segnum >= hashp->DSIZE) {
			/* Reallocate directory */
			dirsize = hashp->DSIZE * sizeof(SEGMENT *);
			if (!hash_realloc(&hashp->dir, dirsize, dirsize << 1))
				return (-1);
			hashp->DSIZE = dirsize << 1;
E 15
		}
D 15
		hashp->DSIZE = dirsize << 1;
	    }
	    if (!(hashp->dir[new_segnum] = 
		    (SEGMENT)calloc ( hashp->SGSIZE, sizeof(SEGMENT)))) {
		    return(-1);
	    }
	    hashp->exsegs++;
	    hashp->nsegs++;
E 15
I 15
D 45
		if (!(hashp->dir[new_segnum] =
			calloc(hashp->SGSIZE, sizeof(SEGMENT))))
E 45
I 45
		if ((hashp->dir[new_segnum] =
		    (SEGMENT)calloc(hashp->SGSIZE, sizeof(SEGMENT))) == NULL)
E 45
			return (-1);
		hashp->exsegs++;
		hashp->nsegs++;
E 15
	}
D 15

E 15
	/*
D 15
	    If the split point is increasing (MAX_BUCKET's log
	    base 2 increases), we need to copy the current contents
	    of the spare split bucket to the next bucket
	*/
E 15
I 15
	 * If the split point is increasing (MAX_BUCKET's log base 2
	 * * increases), we need to copy the current contents of the spare
	 * split bucket to the next bucket.
	 */
E 15
D 23
	spare_ndx = __log2(hashp->MAX_BUCKET);
D 15
	if ( spare_ndx != (__log2(hashp->MAX_BUCKET - 1))) {
	    hashp->SPARES[spare_ndx] = hashp->SPARES[spare_ndx-1];
E 15
I 15
D 17
	if (spare_ndx != (__log2(hashp->MAX_BUCKET - 1)))
		hashp->SPARES[spare_ndx] = hashp->SPARES[spare_ndx - 1];
E 17
I 17
	if ( spare_ndx > hashp->OVFL_POINT ) {
E 23
I 23
	spare_ndx = __log2(hashp->MAX_BUCKET + 1);
	if (spare_ndx > hashp->OVFL_POINT) {
E 23
		hashp->SPARES[spare_ndx] = hashp->SPARES[hashp->OVFL_POINT];
		hashp->OVFL_POINT = spare_ndx;
	}

E 17
	if (new_bucket > hashp->HIGH_MASK) {
		/* Starting a new doubling */
		hashp->LOW_MASK = hashp->HIGH_MASK;
		hashp->HIGH_MASK = new_bucket | hashp->LOW_MASK;
E 15
	}
D 15

	if ( new_bucket > hashp->HIGH_MASK ) {
	    /* Starting a new doubling */
	    hashp->LOW_MASK = hashp->HIGH_MASK;
	    hashp->HIGH_MASK = new_bucket | hashp->LOW_MASK;
	}

	/*
	 * Relocate records to the new bucket
	 */
	return(__split_page ( old_bucket, new_bucket ));
E 15
I 15
	/* Relocate records to the new bucket */
D 31
	return (__split_page(old_bucket, new_bucket));
E 31
I 31
	return (__split_page(hashp, old_bucket, new_bucket));
E 31
E 15
}
I 15

E 15
/*
D 15
    If realloc guarantees that the pointer is not destroyed
    if the realloc fails, then this routine can go away
*/
static char * 
hash_realloc ( p_ptr, oldsize, newsize )
char	**p_ptr;
int	oldsize;
int	newsize;
E 15
I 15
 * If realloc guarantees that the pointer is not destroyed if the realloc
 * fails, then this routine can go away.
 */
static void *
hash_realloc(p_ptr, oldsize, newsize)
	SEGMENT **p_ptr;
	int oldsize, newsize;
E 15
{
D 15
	register char	*p;
E 15
I 15
	register void *p;
E 15

D 15
	if (p = (char *)malloc ( newsize ) ) {
		bcopy ( *p_ptr, p, oldsize );
		bzero ( *p_ptr + oldsize, newsize-oldsize );
E 15
I 15
	if (p = malloc(newsize)) {
D 33
		bcopy(*p_ptr, p, oldsize);
		bzero(*p_ptr + oldsize, newsize - oldsize);
E 33
I 33
		memmove(p, *p_ptr, oldsize);
D 38
		memset(*p_ptr + oldsize, 0, newsize - oldsize);
E 38
I 38
D 40
		memset(p + oldsize, 0, newsize - oldsize);
E 40
I 40
		memset((char *)p + oldsize, 0, newsize - oldsize);
E 40
E 38
E 33
E 15
		free(*p_ptr);
		*p_ptr = p;
	}
	return (p);
}

D 13
extern int
E 13
I 13
extern u_int
E 13
D 15
__call_hash ( k, len )
char	*k;
int	len;
E 15
I 15
D 31
__call_hash(k, len)
E 31
I 31
__call_hash(hashp, k, len)
	HTAB *hashp;
E 31
	char *k;
	int len;
E 15
{
D 15
	int	n, bucket;
	n = hashp->hash(k, len);
E 15
I 15
	int n, bucket;
E 15

I 15
	n = hashp->hash(k, len);
E 15
	bucket = n & hashp->HIGH_MASK;
D 15
	if ( bucket > hashp->MAX_BUCKET ) {
	    bucket = bucket & hashp->LOW_MASK;
	}

	return(bucket);
E 15
I 15
	if (bucket > hashp->MAX_BUCKET)
		bucket = bucket & hashp->LOW_MASK;
	return (bucket);
E 15
}

/*
D 15
    Allocate segment table.  On error, destroy the table
    and set errno.

    Returns 0 on success
*/
E 15
I 15
 * Allocate segment table.  On error, destroy the table and set errno.
 *
 * Returns 0 on success
 */
E 15
static int
D 15
alloc_segs ( nsegs )
int	nsegs;
E 15
I 15
D 31
alloc_segs(nsegs)
E 31
I 31
alloc_segs(hashp, nsegs)
	HTAB *hashp;
E 31
	int nsegs;
E 15
{
D 15
    register int	i;
    register SEGMENT	store;
E 15
I 15
	register int i;
	register SEGMENT store;
E 15

D 15
    int	save_errno;
E 15
I 15
	int save_errno;
E 15

D 15
    if (!(hashp->dir = (SEGMENT *)calloc(hashp->DSIZE, sizeof(SEGMENT *)))) {
	save_errno = errno;
	(void)hdestroy();
	errno = save_errno;
	return(-1);
    }

    /* Allocate segments */
    store = (SEGMENT)calloc ( nsegs << hashp->SSHIFT, sizeof (SEGMENT) );
    if ( !store ) {
	save_errno = errno;
	(void)hdestroy();
	errno = save_errno;
	return(-1);
    }

    for ( i=0; i < nsegs; i++, hashp->nsegs++ ) {
	hashp->dir[i] = &store[i<<hashp->SSHIFT];
    }
    return(0);
E 15
I 15
D 45
	if (!(hashp->dir = calloc(hashp->DSIZE, sizeof(SEGMENT *)))) {
E 45
I 45
	if ((hashp->dir =
	    (SEGMENT *)calloc(hashp->DSIZE, sizeof(SEGMENT *))) == NULL) {
E 45
		save_errno = errno;
D 31
		(void)hdestroy();
E 31
I 31
		(void)hdestroy(hashp);
E 31
		errno = save_errno;
		return (-1);
	}
	/* Allocate segments */
D 45
	store = calloc(nsegs << hashp->SSHIFT, sizeof(SEGMENT));
	if (!store) {
E 45
I 45
	if ((store =
	    (SEGMENT)calloc(nsegs << hashp->SSHIFT, sizeof(SEGMENT))) == NULL) {
E 45
		save_errno = errno;
D 31
		(void)hdestroy();
E 31
I 31
		(void)hdestroy(hashp);
E 31
		errno = save_errno;
		return (-1);
	}
	for (i = 0; i < nsegs; i++, hashp->nsegs++)
		hashp->dir[i] = &store[i << hashp->SSHIFT];
	return (0);
E 15
}

I 15
#if BYTE_ORDER == LITTLE_ENDIAN
E 15
/*
D 15
    Hashp->hdr needs to be byteswapped.
*/
E 15
I 15
 * Hashp->hdr needs to be byteswapped.
 */
E 15
static void
D 15
swap_header_copy ( srcp, destp )
HASHHDR	*srcp;
HASHHDR	*destp;
E 15
I 15
swap_header_copy(srcp, destp)
	HASHHDR *srcp, *destp;
E 15
{
D 15
    int i;
E 15
I 15
	int i;
E 15

D 15
    BLSWAP_COPY(srcp->magic, destp->magic);
    BLSWAP_COPY(srcp->version, destp->version);
    BLSWAP_COPY(srcp->lorder, destp->lorder);
    BLSWAP_COPY(srcp->bsize, destp->bsize);
    BLSWAP_COPY(srcp->bshift, destp->bshift);
    BLSWAP_COPY(srcp->dsize, destp->dsize);
    BLSWAP_COPY(srcp->ssize, destp->ssize);
    BLSWAP_COPY(srcp->sshift, destp->sshift);
    BLSWAP_COPY(srcp->max_bucket, destp->max_bucket);
    BLSWAP_COPY(srcp->high_mask, destp->high_mask);
    BLSWAP_COPY(srcp->low_mask, destp->low_mask);
    BLSWAP_COPY(srcp->ffactor, destp->ffactor);
    BLSWAP_COPY(srcp->nkeys, destp->nkeys);
    BLSWAP_COPY(srcp->hdrpages, destp->hdrpages);
    BLSWAP_COPY(srcp->h_charkey, destp->h_charkey);
    for ( i=0; i < NCACHED; i++ ) {
	BLSWAP_COPY ( srcp->spares[i] , destp->spares[i]);
	BSSWAP_COPY ( srcp->bitmaps[i] , destp->bitmaps[i]);
    }
    return;
E 15
I 15
D 44
	BLSWAP_COPY(srcp->magic, destp->magic);
	BLSWAP_COPY(srcp->version, destp->version);
	BLSWAP_COPY(srcp->lorder, destp->lorder);
	BLSWAP_COPY(srcp->bsize, destp->bsize);
	BLSWAP_COPY(srcp->bshift, destp->bshift);
	BLSWAP_COPY(srcp->dsize, destp->dsize);
	BLSWAP_COPY(srcp->ssize, destp->ssize);
	BLSWAP_COPY(srcp->sshift, destp->sshift);
I 17
	BLSWAP_COPY(srcp->ovfl_point, destp->ovfl_point);
	BLSWAP_COPY(srcp->last_freed, destp->last_freed);
E 17
	BLSWAP_COPY(srcp->max_bucket, destp->max_bucket);
	BLSWAP_COPY(srcp->high_mask, destp->high_mask);
	BLSWAP_COPY(srcp->low_mask, destp->low_mask);
	BLSWAP_COPY(srcp->ffactor, destp->ffactor);
	BLSWAP_COPY(srcp->nkeys, destp->nkeys);
	BLSWAP_COPY(srcp->hdrpages, destp->hdrpages);
	BLSWAP_COPY(srcp->h_charkey, destp->h_charkey);
E 44
I 44
	P_32_COPY(srcp->magic, destp->magic);
	P_32_COPY(srcp->version, destp->version);
	P_32_COPY(srcp->lorder, destp->lorder);
	P_32_COPY(srcp->bsize, destp->bsize);
	P_32_COPY(srcp->bshift, destp->bshift);
	P_32_COPY(srcp->dsize, destp->dsize);
	P_32_COPY(srcp->ssize, destp->ssize);
	P_32_COPY(srcp->sshift, destp->sshift);
	P_32_COPY(srcp->ovfl_point, destp->ovfl_point);
	P_32_COPY(srcp->last_freed, destp->last_freed);
	P_32_COPY(srcp->max_bucket, destp->max_bucket);
	P_32_COPY(srcp->high_mask, destp->high_mask);
	P_32_COPY(srcp->low_mask, destp->low_mask);
	P_32_COPY(srcp->ffactor, destp->ffactor);
	P_32_COPY(srcp->nkeys, destp->nkeys);
	P_32_COPY(srcp->hdrpages, destp->hdrpages);
	P_32_COPY(srcp->h_charkey, destp->h_charkey);
E 44
	for (i = 0; i < NCACHED; i++) {
D 44
		BLSWAP_COPY(srcp->spares[i], destp->spares[i]);
		BSSWAP_COPY(srcp->bitmaps[i], destp->bitmaps[i]);
E 44
I 44
		P_32_COPY(srcp->spares[i], destp->spares[i]);
		P_16_COPY(srcp->bitmaps[i], destp->bitmaps[i]);
E 44
	}
E 15
}

static void
D 15
swap_header ( )
E 15
I 15
D 31
swap_header()
E 31
I 31
swap_header(hashp)
	HTAB *hashp;
E 31
E 15
{
D 15
    HASHHDR	*hdrp;
    int	i;
E 15
I 15
	HASHHDR *hdrp;
	int i;
E 15

D 15
    hdrp = &hashp->hdr;
E 15
I 15
	hdrp = &hashp->hdr;
E 15

D 15
    BLSWAP(hdrp->magic);
    BLSWAP(hdrp->version);
    BLSWAP(hdrp->lorder);
    BLSWAP(hdrp->bsize);
    BLSWAP(hdrp->bshift);
    BLSWAP(hdrp->dsize);
    BLSWAP(hdrp->ssize);
    BLSWAP(hdrp->sshift);
    BLSWAP(hdrp->max_bucket);
    BLSWAP(hdrp->high_mask);
    BLSWAP(hdrp->low_mask);
    BLSWAP(hdrp->ffactor);
    BLSWAP(hdrp->nkeys);
    BLSWAP(hdrp->hdrpages);
    BLSWAP(hdrp->h_charkey);
    for ( i=0; i < NCACHED; i++ ) {
	BLSWAP ( hdrp->spares[i] );
	BSSWAP ( hdrp->bitmaps[i] );
    }
    return;
E 15
I 15
D 44
	BLSWAP(hdrp->magic);
	BLSWAP(hdrp->version);
	BLSWAP(hdrp->lorder);
	BLSWAP(hdrp->bsize);
	BLSWAP(hdrp->bshift);
	BLSWAP(hdrp->dsize);
	BLSWAP(hdrp->ssize);
	BLSWAP(hdrp->sshift);
I 17
	BLSWAP(hdrp->ovfl_point);
	BLSWAP(hdrp->last_freed);
E 17
	BLSWAP(hdrp->max_bucket);
	BLSWAP(hdrp->high_mask);
	BLSWAP(hdrp->low_mask);
	BLSWAP(hdrp->ffactor);
	BLSWAP(hdrp->nkeys);
	BLSWAP(hdrp->hdrpages);
	BLSWAP(hdrp->h_charkey);
E 44
I 44
	M_32_SWAP(hdrp->magic);
	M_32_SWAP(hdrp->version);
	M_32_SWAP(hdrp->lorder);
	M_32_SWAP(hdrp->bsize);
	M_32_SWAP(hdrp->bshift);
	M_32_SWAP(hdrp->dsize);
	M_32_SWAP(hdrp->ssize);
	M_32_SWAP(hdrp->sshift);
	M_32_SWAP(hdrp->ovfl_point);
	M_32_SWAP(hdrp->last_freed);
	M_32_SWAP(hdrp->max_bucket);
	M_32_SWAP(hdrp->high_mask);
	M_32_SWAP(hdrp->low_mask);
	M_32_SWAP(hdrp->ffactor);
	M_32_SWAP(hdrp->nkeys);
	M_32_SWAP(hdrp->hdrpages);
	M_32_SWAP(hdrp->h_charkey);
E 44
	for (i = 0; i < NCACHED; i++) {
D 44
		BLSWAP(hdrp->spares[i]);
		BSSWAP(hdrp->bitmaps[i]);
E 44
I 44
		M_32_SWAP(hdrp->spares[i]);
		M_16_SWAP(hdrp->bitmaps[i]);
E 44
	}
E 15
}
I 15
#endif
E 15
E 1
