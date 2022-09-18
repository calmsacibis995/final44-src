h32027
s 00001/00001/00351
d D 8.5 95/04/29 10:22:16 bostic 49 48
c fix the prototype for ftell
c From: Chris Torek <torek@BSDI.COM>
e
s 00004/00003/00348
d D 8.4 94/01/04 14:37:48 bostic 48 47
c redefine FOPEN_MAX as the stdio min/max, not in any way related
c to the kernel; _POSIX_STREAM_MAX in limits.h makes it public
e
s 00001/00001/00350
d D 8.3 94/01/03 17:57:04 bostic 47 46
c use latest BSDI version of <sys/cdefs.h>, change to __keyword
e
s 00004/00004/00347
d D 8.2 94/01/02 14:24:46 bostic 46 45
c rename fgetline.{3,c} -> fgetln.{3,c}
e
s 00002/00002/00349
d D 8.1 93/06/06 21:58:29 bostic 45 41
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00345
d R 8.1 93/06/06 11:11:58 bostic 44 43
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00004/00347
d R 5.27 93/06/06 11:11:30 bostic 43 41
c delete extern declarations of sys_errlist, sys_nerr, sys_signame, and
c sys_siglist; they caused nothing but problems as they invariably clashed with
c declarations by the programs; delete unnecessary externs from ctype.h
e
s 00002/00002/00349
d R 8.1 93/06/02 20:06:58 bostic 42 41
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00010/00002/00341
d D 5.26 93/05/24 15:24:02 torek 41 40
c make _offset an fpos_t so we can do 64-bit seeks
e
s 00001/00001/00342
d D 5.25 93/05/07 08:47:39 torek 40 39
c make the sys_ arrays all `const char *const []' (for consistency,
c and for compatibility with GNU/Cygnus)
e
s 00001/00000/00342
d D 5.24 92/12/02 17:00:43 bostic 39 38
c add zopen(3)
e
s 00001/00001/00341
d D 5.23 92/10/09 04:57:34 torek 38 37
c sscanf first arg should be "const char *" (from John Gilmore)
e
s 00015/00001/00327
d D 5.22 92/07/09 01:22:26 torek 37 36
c under _ANSI_SOURCE or __STRICT_ANSI__, hide away off_t details
e
s 00010/00010/00318
d D 5.21 92/06/22 21:45:05 bostic 36 33
c prefix all ANSI #define's with BSD_ so don't collide with other vendors
e
s 00002/00002/00326
d R 5.22 92/06/22 21:41:38 bostic 35 34
c prefix all ANSI #define's with BSD_ so don't collide with other vendors
e
s 00003/00003/00325
d R 5.21 92/06/22 21:27:43 bostic 34 33
c prefix all ANSI #define's with BSD_ so don't collide with other vendors
e
s 00002/00001/00326
d D 5.20 92/06/19 15:18:30 bostic 33 32
c typedef fpos_t as off_t; off_t now a quad
e
s 00002/00002/00325
d D 5.19 91/09/03 08:48:36 bostic 32 31
c fread/fwrite return size_t
e
s 00001/00001/00326
d D 5.18 91/07/31 16:57:00 bostic 31 30
c workaround for "cc -ansi -c one.c two.c" GCC bug
e
s 00004/00000/00323
d D 5.17 91/06/03 17:44:47 bostic 30 29
c add sys_nerr, sys_errlist global variables to perror declaration
e
s 00002/00000/00321
d D 5.16 91/04/15 11:43:59 donn 29 28
c Add vscanf() and vsscanf() (feeping creaturism...)
e
s 00001/00001/00320
d D 5.15 91/03/09 17:56:15 bostic 28 27
c create {hp300,i386,tahoe,vax}/include/ansi.h
e
s 00010/00002/00311
d D 5.14 91/03/05 23:37:40 donn 27 26
c (1) Make __sputc() inline function invisible to gcc -traditional.
c (2) Add vfscanf() as a #define.
e
s 00005/00001/00308
d D 5.13 91/02/27 18:47:31 donn 26 25
c A bit more work to achieve C++ compatibility.
e
s 00002/00001/00307
d D 5.12 91/02/24 14:16:22 bostic 25 24
c move P_tmpdir from /usr/tmp to /var/tmp
c add prototype for tempnam(3)
e
s 00018/00016/00290
d D 5.11 91/02/22 08:24:45 donn 24 23
c Be consistent about using names for prototype parameters (they go) and
c compensate slightly by being clearer about what functions are POSIX functions.
e
s 00001/00000/00305
d D 5.10 91/02/19 15:20:08 bostic 23 22
c 1990 POSIX.1 revision moved ctermid to <stdio.h>
e
s 00077/00152/00228
d D 5.9 91/01/26 14:43:51 bostic 22 21
c stdc.h -> cdefs.h; use __P, sort functions, minor wordsmithing
e
s 00363/00053/00017
d D 5.8 91/01/20 21:39:17 bostic 21 20
c new stdio from Chris Torek
e
s 00005/00002/00065
d D 5.7 89/05/27 10:53:54 bostic 20 19
c NULL defined in unistd.h, as well
e
s 00002/00000/00065
d D 5.6 89/02/21 19:26:36 kfall 19 18
c add decls for getlogin() and cuserid()
e
s 00002/00000/00063
d D 5.5 89/02/21 19:17:42 kfall 18 17
c add definition of L_cuserid
e
s 00001/00003/00062
d D 5.4 87/10/22 17:40:05 bostic 17 16
c ANSI C; sprintf now returns an int.
e
s 00004/00000/00061
d D 5.3 86/03/15 17:53:43 donn 16 15
c Put '#ifndef lint' around getc()  and putc() to make life easier for
c lint.  Corresponding definitions were added to the lint library.
e
s 00000/00001/00061
d D 5.2 86/02/24 23:48:31 lepreau 15 14
c remove fseek: back to old version returning int
e
s 00008/00001/00054
d D 5.1 85/05/30 14:25:18 dist 14 13
c Add copyright
e
s 00009/00007/00046
d D 1.12 85/05/30 13:22:56 serge 13 12
c deleted _NFILE (use getdtablesize() instead)
e
s 00001/00001/00052
d D 1.11 85/01/08 09:34:23 ralph 12 11
c increase _NOFILE to 48 to match kernel
e
s 00007/00004/00046
d D 1.10 84/11/29 11:00:40 ralph 11 10
c fix putc(x,iop) so x is executed only once (as before).
e
s 00003/00002/00047
d D 1.9 84/11/21 12:18:13 ralph 10 9
c fix sign-extend problems in putc, getc macros
e
s 00004/00004/00045
d D 1.8 84/11/12 11:27:53 ralph 9 7
c fix lint errs, make code for putc more compact.
e
s 00004/00004/00045
d R 1.8 84/11/12 09:38:50 ralph 8 7
c fix lint errs, make code for putc more compact.
e
s 00004/00002/00045
d D 1.7 84/11/08 11:05:43 ralph 7 6
c putc(): don't call flsbuf until buffer full or '\n' if line buffering.
e
s 00001/00000/00046
d D 1.6 84/09/10 10:16:32 ralph 6 5
c added func declaration for gets
e
s 00001/00001/00045
d D 1.5 83/08/11 23:17:09 sam 5 4
c standardize sccs keyword lines
e
s 00003/00001/00043
d D 1.4 83/06/30 15:19:21 sam 4 3
c from sun
e
s 00001/00000/00043
d D 1.3 83/03/02 09:29:22 nicklin 3 2
c added char *sprintf();
e
s 00001/00000/00042
d D 1.2 82/10/05 22:44:12 mckusick 2 1
c utilize st_blksize field to optimize size of reads and writes
e
s 00042/00000/00000
d D 1.1 81/03/09 21:00:10 toy 1 0
c date and time created 81/03/09 21:00:10 by toy
e
u
U
t
T
I 1
D 5
/*	%W% (Berkeley) %G%	*/
E 5
I 5
D 14
/*	%M%	%I%	%E%	*/
E 14
I 14
D 21
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 21
I 21
/*-
D 45
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 45
I 45
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 45
E 21
 *
I 21
 * This code is derived from software contributed to Berkeley by
 * Chris Torek.
 *
 * %sccs.include.redist.c%
 *
E 21
 *	%W% (Berkeley) %G%
 */

I 21
#ifndef	_STDIO_H_
#define	_STDIO_H_

I 37
#if !defined(_ANSI_SOURCE) && !defined(__STRICT_ANSI__)
E 37
I 33
#include <sys/types.h>
I 37
#endif

E 37
E 33
D 22
/*
 * NB: to fit things in six character monocase externals, the stdio
 * code uses the prefix `__s' for stdio objects, typically followed
 * by a three-character attempt at a mnemonic.
 */
E 22
I 22
#include <sys/cdefs.h>
E 22

D 28
#include <machine/types.h>
E 28
I 28
#include <machine/ansi.h>
E 28
D 22

E 22
D 36
#ifdef	_SIZE_T_
typedef	_SIZE_T_	size_t;
#undef	_SIZE_T_
E 36
I 36
#ifdef	_BSD_SIZE_T_
typedef	_BSD_SIZE_T_	size_t;
#undef	_BSD_SIZE_T_
E 36
#endif

E 21
E 14
E 5
D 13
#define	BUFSIZ	1024
D 12
#define	_NFILE	20
E 12
I 12
#define	_NFILE	48
E 13
E 12
D 20
# ifndef FILE
E 20
I 20
#ifndef NULL
#define	NULL	0
#endif

D 21
#ifndef FILE
E 20
I 13
#define	BUFSIZ	1024
E 13
extern	struct	_iobuf {
	int	_cnt;
D 13
	char	*_ptr;
	char	*_base;
E 13
I 13
	char	*_ptr;		/* should be unsigned char */
	char	*_base;		/* ditto */
E 13
I 2
	int	_bufsiz;
E 2
	short	_flag;
D 13
	char	_file;
} _iob[_NFILE];
# endif
E 13
I 13
	char	_file;		/* should be short */
} _iob[];
E 21
I 21
D 33
typedef long fpos_t;		/* Must match off_t <sys/types.h> */
E 33
I 33
D 37
typedef off_t fpos_t;		/* Must match off_t <sys/types.h> */
E 37
I 37
/*
 * This is fairly grotesque, but pure ANSI code must not inspect the
 * innards of an fpos_t anyway.  The library internally uses off_t,
D 41
 * which we assume is exactly as big as eight chars.
E 41
I 41
 * which we assume is exactly as big as eight chars.  (When we switch
 * to gcc 2.4 we will use __attribute__ here.)
 *
 * WARNING: the alignment constraints on an off_t and the struct below
 * differ on (e.g.) the SPARC.  Hence, the placement of an fpos_t object
 * in a structure will change if fpos_t's are not aligned on 8-byte
 * boundaries.  THIS IS A CROCK, but for now there is no way around it.
E 41
 */
#if !defined(_ANSI_SOURCE) && !defined(__STRICT_ANSI__)
typedef off_t fpos_t;
#else
typedef struct __sfpos {
	char	_pos[8];
} fpos_t;
#endif
E 37
E 33
E 21
E 13

D 21
#define	_IOREAD	01
#define	_IOWRT	02
#define	_IONBF	04
#define	_IOMYBUF	010
#define	_IOEOF	020
#define	_IOERR	040
#define	_IOSTRG	0100
#define	_IOLBF	0200
#define	_IORW	0400
D 20
#define	NULL	0
E 20
#define	FILE	struct _iobuf
E 21
I 21
#define	_FSTDIO			/* Define for new stdio with functions. */

I 22
/*
 * NB: to fit things in six character monocase externals, the stdio
 * code uses the prefix `__s' for stdio objects, typically followed
 * by a three-character attempt at a mnemonic.
 */

E 22
/* stdio buffers */
struct __sbuf {
	unsigned char *_base;
	int	_size;
};

/*
 * stdio state variables.
 *
 * The following always hold:
 *
 *	if (_flags&(__SLBF|__SWR)) == (__SLBF|__SWR),
 *		_lbfsize is -_bf._size, else _lbfsize is 0
 *	if _flags&__SRD, _w is 0
 *	if _flags&__SWR, _r is 0
 *
 * This ensures that the getc and putc macros (or inline functions) never
 * try to write or read from a file that is in `read' or `write' mode.
 * (Moreover, they can, and do, automatically switch from read mode to
 * write mode, and back, on "r+" and "w+" files.)
 *
 * _lbfsize is used only to make the inline line-buffered output stream
 * code as compact as possible.
 *
 * _ub, _up, and _ur are used when ungetc() pushes back more characters
 * than fit in the current _bf, or when ungetc() pushes back a character
 * that does not match the previous one in _bf.  When this happens,
 * _ub._base becomes non-nil (i.e., a stream has ungetc() data iff
 * _ub._base!=NULL) and _up and _ur save the current values of _p and _r.
I 41
 *
 * NB: see WARNING above before changing the layout of this structure!
E 41
 */
typedef	struct __sFILE {
	unsigned char *_p;	/* current position in (some) buffer */
	int	_r;		/* read space left for getc() */
	int	_w;		/* write space left for putc() */
	short	_flags;		/* flags, below; this FILE is free if 0 */
	short	_file;		/* fileno, if Unix descriptor, else -1 */
	struct	__sbuf _bf;	/* the buffer (at least 1 byte, if !NULL) */
	int	_lbfsize;	/* 0 or -_bf._size, for inline putc */

	/* operations */
	void	*_cookie;	/* cookie passed to io functions */
D 22
#if __STDC__ || c_plusplus
	int	(*_read)(void *_cookie, char *_buf, int _n);
	int	(*_write)(void *_cookie, const char *_buf, int _n);
	fpos_t	(*_seek)(void *_cookie, fpos_t _offset, int _whence);
	int	(*_close)(void *_cookie);
#else
	int	(*_read)();
	int	(*_write)();
	fpos_t	(*_seek)();
	int	(*_close)();
#endif
E 22
I 22
D 24
	int	(*_close) __P((void *_cookie));
	int	(*_read)  __P((void *_cookie, char *_buf, int _n));
	fpos_t	(*_seek)  __P((void *_cookie, fpos_t _offset, int _whence));
	int	(*_write) __P((void *_cookie, const char *_buf, int _n));
E 24
I 24
	int	(*_close) __P((void *));
	int	(*_read)  __P((void *, char *, int));
	fpos_t	(*_seek)  __P((void *, fpos_t, int));
	int	(*_write) __P((void *, const char *, int));
E 24
E 22

	/* separate buffer for long sequences of ungetc() */
	struct	__sbuf _ub;	/* ungetc buffer */
	unsigned char *_up;	/* saved _p when _p is doing ungetc data */
	int	_ur;		/* saved _r when _r is counting ungetc data */

	/* tricks to meet minimum requirements even when malloc() fails */
	unsigned char _ubuf[3];	/* guarantee an ungetc() buffer */
	unsigned char _nbuf[1];	/* guarantee a getc() buffer */

D 46
	/* separate buffer for fgetline() when line crosses buffer boundary */
	struct	__sbuf _lb;	/* buffer for fgetline() */
E 46
I 46
	/* separate buffer for fgetln() when line crosses buffer boundary */
	struct	__sbuf _lb;	/* buffer for fgetln() */
E 46

	/* Unix stdio files get aligned to block boundaries on fseek() */
	int	_blksize;	/* stat.st_blksize (may be != _bf._size) */
D 41
	int	_offset;	/* current lseek offset */
E 41
I 41
	fpos_t	_offset;	/* current lseek offset (see WARNING) */
E 41
} FILE;

I 26
__BEGIN_DECLS
E 26
extern FILE __sF[];
I 26
__END_DECLS
E 26

#define	__SLBF	0x0001		/* line buffered */
#define	__SNBF	0x0002		/* unbuffered */
#define	__SRD	0x0004		/* OK to read */
#define	__SWR	0x0008		/* OK to write */
	/* RD and WR are never simultaneously asserted */
#define	__SRW	0x0010		/* open for reading & writing */
#define	__SEOF	0x0020		/* found EOF */
#define	__SERR	0x0040		/* found error */
#define	__SMBF	0x0080		/* _buf is from malloc */
#define	__SAPP	0x0100		/* fdopen()ed in append mode */
#define	__SSTR	0x0200		/* this is an sprintf/snprintf string */
#define	__SOPT	0x0400		/* do fseek() optimisation */
#define	__SNPT	0x0800		/* do not do fseek() optimisation */
#define	__SOFF	0x1000		/* set iff _offset is in fact correct */
D 46
#define	__SMOD	0x2000		/* true => fgetline modified _p text */
E 46
I 46
#define	__SMOD	0x2000		/* true => fgetln modified _p text */
E 46

/*
 * The following three definitions are for ANSI C, which took them
 * from System V, which brilliantly took internal interface macros and
 * made them official arguments to setvbuf(), without renaming them.
 * Hence, these ugly _IOxxx names are *supposed* to appear in user code.
 *
 * Although numbered as their counterparts above, the implementation
 * does not rely on this.
 */
#define	_IOFBF	0		/* setvbuf should set fully buffered */
#define	_IOLBF	1		/* setvbuf should set line buffered */
#define	_IONBF	2		/* setvbuf should set unbuffered */

#define	BUFSIZ	1024		/* size of buffer used by setbuf */
E 21
#define	EOF	(-1)

D 21
#define	stdin	(&_iob[0])
#define	stdout	(&_iob[1])
#define	stderr	(&_iob[2])
I 16
#ifndef lint
E 16
D 7
#define	getc(p)		(--(p)->_cnt>=0? *(p)->_ptr++&0377:_filbuf(p))
E 7
I 7
D 9
#define	getc(p)	(--(p)->_cnt >= 0 ? *(unsigned char *)(p)->_ptr++ : _filbuf(p))
E 9
I 9
D 10
#define	getc(p)		(--(p)->_cnt>=0? *(p)->_ptr++&0377:_filbuf(p))
E 10
I 10
#define	getc(p)		(--(p)->_cnt>=0? (int)(*(unsigned char *)(p)->_ptr++):_filbuf(p))
I 16
#endif not lint
E 16
E 10
E 9
E 7
#define	getchar()	getc(stdin)
I 16
#ifndef lint
E 16
D 7
#define putc(x,p) (--(p)->_cnt>=0? ((int)(*(p)->_ptr++=(unsigned)(x))):_flsbuf((unsigned)(x),p))
E 7
I 7
D 9
#define putc(x, p)	(--(p)->_cnt >= 0 ? (*(p)->_ptr++ = (x)) :\
	((p)->_flag&_IOLBF && -(p)->_cnt <= (p)->_bufsiz && (x)!='\n' ?\
		*(p)->_ptr++ = (x) : _flsbuf(x, p)))
E 9
I 9
D 11
#define putc(x, p)	(--(p)->_cnt >= 0 || ((p)->_flag & _IOLBF) &&\
		-(p)->_cnt <= (p)->_bufsiz && (x) != '\n' ?\
D 10
		(int)(*(p)->_ptr++ = (unsigned)(x)) : _flsbuf((unsigned)(x), p))
E 10
I 10
		(int)(*(unsigned char *)(p)->_ptr++ = (x)) :\
		_flsbuf((unsigned char)(x), p))
E 11
I 11
#define putc(x, p)	(--(p)->_cnt >= 0 ?\
	(int)(*(unsigned char *)(p)->_ptr++ = (x)) :\
	(((p)->_flag & _IOLBF) && -(p)->_cnt < (p)->_bufsiz ?\
		((*(p)->_ptr = (x)) != '\n' ?\
			(int)(*(unsigned char *)(p)->_ptr++) :\
			_flsbuf(*(unsigned char *)(p)->_ptr, p)) :\
		_flsbuf((unsigned char)(x), p)))
I 16
#endif not lint
E 16
E 11
E 10
E 9
E 7
#define	putchar(x)	putc(x,stdout)
#define	feof(p)		(((p)->_flag&_IOEOF)!=0)
#define	ferror(p)	(((p)->_flag&_IOERR)!=0)
#define	fileno(p)	((p)->_file)
I 13
#define	clearerr(p)	((p)->_flag &= ~(_IOERR|_IOEOF))
E 21
I 21
/*
D 48
 * FOPEN_MAX is a minimum maximum, and should be the number of descriptors
 * that the kernel can provide without allocation of a resource that can
 * fail without the process sleeping.  Do not use this for anything.
E 48
I 48
 * FOPEN_MAX is a minimum maximum, and is the number of streams that
 * stdio can provide without attempting to allocate further resources
 * (which could fail).  Do not use this for anything.
E 48
 */
I 48
				/* must be == _POSIX_STREAM_MAX <limits.h> */
E 48
#define	FOPEN_MAX	20	/* must be <= OPEN_MAX <sys/syslimits.h> */
#define	FILENAME_MAX	1024	/* must be <= PATH_MAX <sys/syslimits.h> */
E 21
E 13

I 21
/* System V/ANSI C; this is the wrong way to do this, do *not* use these. */
#ifndef _ANSI_SOURCE
D 25
#define	P_tmpdir	"/usr/tmp/"
E 25
I 25
#define	P_tmpdir	"/var/tmp/"
E 25
#endif
#define	L_tmpnam	1024	/* XXX must be == PATH_MAX */
#define	TMP_MAX		308915776

#ifndef SEEK_SET
#define	SEEK_SET	0	/* set file offset to offset */
#endif
#ifndef SEEK_CUR
#define	SEEK_CUR	1	/* set file offset to current plus offset */
#endif
#ifndef SEEK_END
#define	SEEK_END	2	/* set file offset to EOF plus offset */
#endif

#define	stdin	(&__sF[0])
#define	stdout	(&__sF[1])
#define	stderr	(&__sF[2])

/*
 * Functions defined in ANSI C standard.
 */
D 22
#if __STDC__ || c_plusplus
int	remove(const char *);
int	rename(const char *_old, const char *_new);
FILE	*tmpfile(void);
char	*tmpnam(char *);
int	fclose(FILE *);
int	fflush(FILE *);
FILE	*fopen(const char *_name, const char *_type);
FILE	*freopen(const char *_name, const char *_type, FILE *_stream);
void	setbuf(FILE *, char *);
int	setvbuf(FILE *, char *, int, size_t);
int	fprintf(FILE *, const char *, ...);
int	fscanf(FILE *, const char *, ...);
int	printf(const char *, ...);
int	scanf(const char *, ...);
int	sprintf(char *, const char *, ...);
int	sscanf(char *, const char *, ...);
int	vfprintf(FILE *, const char *, _VA_LIST_);
int	vprintf(const char *, _VA_LIST_);
int	vsprintf(char *, const char *, _VA_LIST_);
int	fgetc(FILE *);
char	*fgets(char *, size_t, FILE *);
int	fputc(int, FILE *);
int	fputs(const char *, FILE *);
int	getc(FILE *);
int	getchar(void);
char	*gets(char *);
int	putc(int, FILE *);
int	putchar(int);
int	puts(const char *);
int	ungetc(int, FILE *);
int	fread(void *, size_t _size, size_t _n, FILE *);
int	fwrite(const void *, size_t _size, size_t _n, FILE *);
int	fgetpos(FILE *, fpos_t *);
int	fseek(FILE *, long, int);
int	fsetpos(FILE *, const fpos_t *);
long	ftell(const FILE *);
void	rewind(FILE *);
void	clearerr(FILE *);
int	feof(FILE *);
int	ferror(FILE *);
void	perror(const char *);
#else
int	remove();
int	rename();
FILE	*tmpfile();
char	*tmpnam();
int	fclose();
int	fflush();
E 21
FILE	*fopen();
D 21
FILE	*fdopen();
E 21
FILE	*freopen();
I 13
D 21
FILE	*popen();
E 13
long	ftell();
E 21
I 21
void	setbuf();
int	setvbuf();
int	fprintf();
int	fscanf();
int	printf();
int	scanf();
int	sprintf();
int	sscanf();
int	vfprintf();
int	vprintf();
int	vsprintf();
int	fgetc();
E 21
I 13
D 15
long	fseek();
E 15
E 13
char	*fgets();
I 21
int	fputc();
int	fputs();
int	getc();
int	getchar();
E 21
I 6
char	*gets();
E 6
I 3
D 4
char	*sprintf();
E 4
I 4
D 17
#ifdef vax
char	*sprintf();		/* too painful to do right */
#endif
E 17
I 17
D 21
int	sprintf();	/* here until everyone does it right */
E 17
I 13
# endif
E 21
I 21
int	putc();
int	putchar();
int	puts();
int	ungetc();
int	fread();
int	fwrite();
int	fgetpos();
int	fseek();
int	fsetpos();
long	ftell();
void	rewind();
void	clearerr();
int	feof();
int	ferror();
void	perror();
#endif
E 22
I 22
__BEGIN_DECLS
void	 clearerr __P((FILE *));
int	 fclose __P((FILE *));
int	 feof __P((FILE *));
int	 ferror __P((FILE *));
int	 fflush __P((FILE *));
int	 fgetc __P((FILE *));
int	 fgetpos __P((FILE *, fpos_t *));
char	*fgets __P((char *, size_t, FILE *));
D 24
FILE	*fopen __P((const char *_name, const char *_type));
E 24
I 24
FILE	*fopen __P((const char *, const char *));
E 24
int	 fprintf __P((FILE *, const char *, ...));
int	 fputc __P((int, FILE *));
int	 fputs __P((const char *, FILE *));
D 24
int	 fread __P((void *, size_t _size, size_t _n, FILE *));
FILE	*freopen __P((const char *_name, const char *_type, FILE *_stream));
E 24
I 24
D 32
int	 fread __P((void *, size_t, size_t, FILE *));
E 32
I 32
size_t	 fread __P((void *, size_t, size_t, FILE *));
E 32
FILE	*freopen __P((const char *, const char *, FILE *));
E 24
int	 fscanf __P((FILE *, const char *, ...));
int	 fseek __P((FILE *, long, int));
int	 fsetpos __P((FILE *, const fpos_t *));
D 49
long	 ftell __P((const FILE *));
E 49
I 49
long	 ftell __P((FILE *));
E 49
D 24
int	 fwrite __P((const void *, size_t _size, size_t _n, FILE *));
E 24
I 24
D 32
int	 fwrite __P((const void *, size_t, size_t, FILE *));
E 32
I 32
size_t	 fwrite __P((const void *, size_t, size_t, FILE *));
E 32
E 24
int	 getc __P((FILE *));
int	 getchar __P((void));
char	*gets __P((char *));
I 30
#if !defined(_ANSI_SOURCE) && !defined(_POSIX_SOURCE)
extern int sys_nerr;			/* perror(3) external variables */
D 40
extern char *sys_errlist[];
E 40
I 40
D 47
extern const char *const sys_errlist[];
E 47
I 47
extern __const char *__const sys_errlist[];
E 47
E 40
#endif
E 30
void	 perror __P((const char *));
int	 printf __P((const char *, ...));
int	 putc __P((int, FILE *));
int	 putchar __P((int));
int	 puts __P((const char *));
int	 remove __P((const char *));
D 24
int	 rename  __P((const char *_old, const char *_new));
E 24
I 24
int	 rename  __P((const char *, const char *));
E 24
void	 rewind __P((FILE *));
int	 scanf __P((const char *, ...));
void	 setbuf __P((FILE *, char *));
int	 setvbuf __P((FILE *, char *, int, size_t));
int	 sprintf __P((char *, const char *, ...));
D 38
int	 sscanf __P((char *, const char *, ...));
E 38
I 38
int	 sscanf __P((const char *, const char *, ...));
E 38
FILE	*tmpfile __P((void));
char	*tmpnam __P((char *));
int	 ungetc __P((int, FILE *));
D 36
int	 vfprintf __P((FILE *, const char *, _VA_LIST_));
int	 vprintf __P((const char *, _VA_LIST_));
int	 vsprintf __P((char *, const char *, _VA_LIST_));
E 36
I 36
int	 vfprintf __P((FILE *, const char *, _BSD_VA_LIST_));
int	 vprintf __P((const char *, _BSD_VA_LIST_));
int	 vsprintf __P((char *, const char *, _BSD_VA_LIST_));
E 36
__END_DECLS
E 22
E 21
I 18

D 21
#define	L_cuserid	9	/* posix says it goes in stdio.h :( */
I 19
char	*getlogin();
char	*cuserid();
E 21
I 21
/*
 * Functions defined in POSIX 1003.1.
 */
#ifndef _ANSI_SOURCE
#define	L_cuserid	9	/* size for cuserid(); UT_NAMESIZE + 1 */
#define	L_ctermid	1024	/* size for ctermid(); PATH_MAX */

D 22
#if __STDC__ || c_plusplus
FILE	*fdopen(int, const char *);
int	fileno(FILE *);
#else
FILE	*fdopen();
int	fileno();
#endif
#endif
E 22
I 22
__BEGIN_DECLS
I 23
char	*ctermid __P((char *));
E 23
FILE	*fdopen __P((int, const char *));
int	 fileno __P((FILE *));
__END_DECLS
I 24
#endif /* not ANSI */
E 24
E 22

/*
 * Routines that are purely local.
 */
I 24
#if !defined (_ANSI_SOURCE) && !defined(_POSIX_SOURCE)
E 24
D 22
#if __STDC__ || c_plusplus
char	*fgetline(FILE *, size_t *);
int	fpurge(FILE *);
int	getw(FILE *);
int	pclose(FILE *);
FILE	*popen(const char *_name, const char *_type);
int	putw(int, FILE *);
void	setbuffer(FILE *, char *, int);
int	setlinebuf(FILE *);
int	snprintf(char *, size_t, const char *, ...);
int	vsnprintf(char *, size_t, const char *, _VA_LIST_);
#else
char	*fgetline();
int	fpurge();
int	getw();
int	pclose();
FILE	*popen();
int	putw();
void	setbuffer();
int	setlinebuf();
int	snprintf();
int	vsnprintf();
#endif
#endif /* _ANSI_SOURCE */
E 22
I 22
__BEGIN_DECLS
D 46
char	*fgetline __P((FILE *, size_t *));
E 46
I 46
char	*fgetln __P((FILE *, size_t *));
E 46
int	 fpurge __P((FILE *));
int	 getw __P((FILE *));
int	 pclose __P((FILE *));
D 24
FILE	*popen __P((const char *_name, const char *_type));
E 24
I 24
FILE	*popen __P((const char *, const char *));
E 24
int	 putw __P((int, FILE *));
void	 setbuffer __P((FILE *, char *, int));
int	 setlinebuf __P((FILE *));
I 25
char	*tempnam __P((const char *, const char *));
E 25
int	 snprintf __P((char *, size_t, const char *, ...));
D 36
int	 vsnprintf __P((char *, size_t, const char *, _VA_LIST_));
I 29
int	 vscanf __P((const char *, _VA_LIST_));
int	 vsscanf __P((const char *, const char *, _VA_LIST_));
E 36
I 36
int	 vsnprintf __P((char *, size_t, const char *, _BSD_VA_LIST_));
int	 vscanf __P((const char *, _BSD_VA_LIST_));
int	 vsscanf __P((const char *, const char *, _BSD_VA_LIST_));
I 39
FILE	*zopen __P((const char *, const char *, int));
E 39
E 36
E 29
__END_DECLS
E 22

D 22
#ifndef _ANSI_SOURCE
E 22
/*
I 27
 * This is a #define because the function is used internally and
 * (unlike vfscanf) the name __svfscanf is guaranteed not to collide
 * with a user function when _ANSI_SOURCE or _POSIX_SOURCE is defined.
 */
#define	 vfscanf	__svfscanf

/*
E 27
 * Stdio function-access interface.
 */
D 22
#if __STDC__ || c_plusplus
FILE	*funopen(const void *_cookie,
E 22
I 22
__BEGIN_DECLS
D 24
FILE	*funopen __P((const void *_cookie,
E 22
		int (*readfn)(void *_cookie, char *_buf, int _n),
		int (*writefn)(void *_cookie, const char *_buf, int _n),
		fpos_t (*seekfn)(void *_cookie, fpos_t _off, int _whence),
D 22
		int (*closefn)(void *_cookie));
E 22
I 22
		int (*closefn)(void *_cookie)));
E 24
I 24
FILE	*funopen __P((const void *,
		int (*)(void *, char *, int),
		int (*)(void *, const char *, int),
		fpos_t (*)(void *, fpos_t, int),
		int (*)(void *)));
E 24
__END_DECLS
E 22
#define	fropen(cookie, fn) funopen(cookie, fn, 0, 0, 0)
#define	fwopen(cookie, fn) funopen(cookie, 0, fn, 0, 0)
D 22
#else
FILE	*funopen();
#define	fropen(cookie, fn) \
	funopen(cookie, fn, (int (*)())0, (fpos_t (*)())0, (int (*)())0)
#define	fwopen(cookie, fn) \
	funopen(cookie, (int (*)())0, fn, (fpos_t (*)())0, (int (*)())0)
#endif
E 22
I 22
D 24
#endif /* !ANSI_SOURCE */
E 24
I 24
D 26
#endif /* neither ANSI nor POSIX */
E 26
I 26
#endif /* !_ANSI_SOURCE && !_POSIX_SOURCE */
E 26
E 24
E 22

/*
 * Functions internal to the implementation.
 */
I 26
__BEGIN_DECLS
E 26
D 22
#if __STDC__ || c_plusplus
int	__srget(FILE *);
int	__swbuf(int, FILE *);
#else
int	__srget();
int	__swbuf();
#endif
E 22
I 22
int	__srget __P((FILE *));
I 27
D 36
int	__svfscanf __P((FILE *, const char *, _VA_LIST_));
E 36
I 36
int	__svfscanf __P((FILE *, const char *, _BSD_VA_LIST_));
E 36
E 27
int	__swbuf __P((int, FILE *));
I 26
__END_DECLS
E 26
E 22

/*
 * The __sfoo macros are here so that we can 
 * define function versions in the C library.
 */
#define	__sgetc(p) (--(p)->_r < 0 ? __srget(p) : (int)(*(p)->_p++))
D 27
#ifdef __GNUC__
static __inline int __sputc(int _c, FILE *_p) {
E 27
I 27
#if defined(__GNUC__) && defined(__STDC__)
D 31
static inline int __sputc(int _c, FILE *_p) {
E 31
I 31
static __inline int __sputc(int _c, FILE *_p) {
E 31
E 27
	if (--_p->_w >= 0 || (_p->_w >= _p->_lbfsize && (char)_c != '\n'))
		return (*_p->_p++ = _c);
	else
		return (__swbuf(_c, _p));
}
#else
/*
 * This has been tuned to generate reasonable code on the vax using pcc.
 */
#define	__sputc(c, p) \
	(--(p)->_w < 0 ? \
		(p)->_w >= (p)->_lbfsize ? \
			(*(p)->_p = (c)), *(p)->_p != '\n' ? \
				(int)*(p)->_p++ : \
				__swbuf('\n', p) : \
			__swbuf((int)(c), p) : \
		(*(p)->_p = (c), (int)*(p)->_p++))
#endif

#define	__sfeof(p)	(((p)->_flags & __SEOF) != 0)
#define	__sferror(p)	(((p)->_flags & __SERR) != 0)
#define	__sclearerr(p)	((void)((p)->_flags &= ~(__SERR|__SEOF)))
#define	__sfileno(p)	((p)->_file)

#define	feof(p)		__sfeof(p)
#define	ferror(p)	__sferror(p)
#define	clearerr(p)	__sclearerr(p)

#ifndef _ANSI_SOURCE
#define	fileno(p)	__sfileno(p)
#endif

#ifndef lint
#define	getc(fp)	__sgetc(fp)
#define putc(x, fp)	__sputc(x, fp)
#endif /* lint */

#define	getchar()	getc(stdin)
#define	putchar(x)	putc(x, stdout)
#endif /* _STDIO_H_ */
E 21
E 19
E 18
E 13
E 4
E 3
E 1
