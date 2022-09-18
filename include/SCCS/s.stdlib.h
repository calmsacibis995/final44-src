h50572
s 00002/00002/00140
d D 8.5 95/05/19 13:24:02 mckusick 36 35
c srandom and initstate take longs rather than ints
e
s 00000/00007/00142
d D 8.4 95/04/27 13:58:43 bostic 35 34
c move getopt information from stdlib.h to unistd.h
c as decreed by IEEE Std 1003.2-1992
e
s 00001/00000/00148
d D 8.3 94/02/16 13:39:08 bostic 34 33
c add realpath(3); From: Jan-Simon Pendry <pendry@vangogh.CS.Berkeley.EDU>
e
s 00004/00000/00144
d D 8.2 93/11/12 14:31:05 torek 33 32
c ANSI says NULL should be defined here too
e
s 00002/00002/00142
d D 8.1 93/06/02 20:07:01 bostic 32 31
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00000/00142
d D 5.29 93/06/02 18:10:27 mckusick 31 30
c devname and getbsize move in from ps and df
e
s 00002/00000/00140
d D 5.28 93/05/28 12:24:57 bostic 30 29
c don't typedef run_t if _ANSI_SOURCE defined
e
s 00004/00001/00136
d D 5.27 93/05/26 16:57:01 elan 29 27
c rune support from Paul Borman
e
s 00003/00001/00136
d R 5.27 93/05/26 14:01:18 bostic 28 27
c rune support from Paul Borman
e
s 00005/00001/00132
d D 5.26 93/04/27 18:42:51 bostic 27 26
c add daemon, group_from_gid, user_from_uid
e
s 00002/00001/00131
d D 5.25 93/04/27 10:57:52 bostic 26 25
c add getloadavg(3)
e
s 00000/00001/00132
d D 5.24 93/01/12 10:26:00 bostic 25 24
c move cfree into libcompat
e
s 00002/00000/00131
d D 5.23 92/12/02 16:37:40 bostic 24 23
c add mergesort
e
s 00007/00003/00124
d D 5.22 92/11/23 10:54:32 bostic 23 22
c ANSI says can't include <sys/types.h>, nor does ANSI permit quads
c from Chris Torek
e
s 00012/00000/00115
d D 5.21 92/08/06 18:20:41 bostic 22 21
c add getcap(3) functions
e
s 00001/00000/00114
d D 5.20 92/06/30 18:07:56 bostic 21 20
c add sradixsort
e
s 00004/00000/00110
d D 5.19 92/06/25 08:50:32 bostic 20 19
c add strtoq, strtouq
e
s 00006/00006/00104
d D 5.18 92/06/22 21:27:44 bostic 19 18
c prefix all ANSI #define's with BSD_ so don't collide with other vendors
e
s 00012/00006/00098
d D 5.17 92/03/02 20:22:49 torek 18 17
c declare dead and pure functions as such
e
s 00001/00001/00103
d D 5.16 91/12/06 14:01:11 bostic 17 15
c add optopt to the list of getopt(3) extenrs
e
s 00001/00001/00103
d R 5.16 91/11/08 21:12:00 karels 16 15
c correct putenv
e
s 00001/00001/00103
d D 5.15 91/07/23 12:37:52 bostic 15 14
c make endbyte parameter a u_int so ANSI doesn't confuse things
e
s 00015/00009/00089
d D 5.14 91/07/22 10:34:45 bostic 14 13
c add size_t, minor rearrangement
e
s 00002/00000/00096
d D 5.13 91/06/04 10:15:58 bostic 13 12
c add heapsort
e
s 00004/00000/00092
d D 5.12 91/03/16 12:36:40 donn 12 11
c Declare some external variables to go along with some prototypes.
e
s 00001/00000/00091
d D 5.11 91/02/24 14:31:13 bostic 11 10
c add prototype for getsubopt(3)
e
s 00002/00007/00089
d D 5.10 91/02/24 14:17:23 bostic 10 9
c include sys/types.h, no longer need to typedef size_t
c typo in RAND_MAX define
e
s 00001/00001/00095
d D 5.9 91/02/22 15:14:06 donn 9 8
c Fix 'const' problems with getopt()'s prototype.
e
s 00040/00031/00056
d D 5.8 91/02/22 08:03:39 donn 8 7
c Added new prototype declarations and cleaned up.
e
s 00007/00005/00080
d D 5.7 91/02/18 10:23:19 donn 7 6
c we now have stubs for the annoying ANSI multibyte character functions
e
s 00001/00001/00084
d D 5.6 91/02/13 23:34:13 donn 6 5
c G++'s parser isn't up to handling atexit()'s extended declaration...
e
s 00036/00077/00049
d D 5.5 91/02/05 17:11:06 bostic 5 4
c first pass at function prototypes with cdefs.h
c protect include files included by other include files with #ifndef _NAME_H_
e
s 00001/00001/00125
d D 5.4 90/12/18 10:52:24 bostic 4 3
c kernel reorg
e
s 00005/00005/00121
d D 5.3 90/05/29 19:26:55 bostic 3 2
c C++ wants the prototypes, too
e
s 00033/00010/00093
d D 5.2 90/05/17 16:17:44 bostic 2 1
c starting an ANSI C library
e
s 00103/00000/00000
d D 5.1 90/05/15 19:35:24 bostic 1 0
c date and time created 90/05/15 19:35:24 by bostic
e
u
U
t
T
I 1
/*-
D 32
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 32
I 32
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 32
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

#ifndef _STDLIB_H_
#define _STDLIB_H_
I 29

E 29
D 2
#include <machine/x3j11.h>
E 2
I 2
D 4
#include <machine/machtypes.h>
E 4
I 4
D 10
#include <machine/types.h>
E 10
I 10
D 23
#include <sys/types.h>
E 23
I 23
#include <machine/ansi.h>
E 23
E 10
E 4
E 2

I 14
D 19
#ifdef	_SIZE_T_
typedef	_SIZE_T_	size_t;
#undef	_SIZE_T_
E 19
I 19
#ifdef	_BSD_SIZE_T_
typedef	_BSD_SIZE_T_	size_t;
#undef	_BSD_SIZE_T_
E 19
#endif

E 14
D 10
#ifdef	_SIZE_T_
typedef	_SIZE_T_	size_t;
#undef	_SIZE_T_
#endif

E 10
D 19
#ifdef	_WCHAR_T_
typedef	_WCHAR_T_	wchar_t;
#undef	_WCHAR_T_
E 19
I 19
#ifdef	_BSD_WCHAR_T_
I 30
#ifndef _ANSI_SOURCE
E 30
I 29
typedef	_BSD_WCHAR_T_	rune_t;
I 30
#endif
E 30
E 29
typedef	_BSD_WCHAR_T_	wchar_t;
#undef	_BSD_WCHAR_T_
E 19
#endif

typedef struct {
	int quot;		/* quotient */
	int rem;		/* remainder */
} div_t;
I 14

E 14
typedef struct {
	long quot;		/* quotient */
	long rem;		/* remainder */
} ldiv_t;

I 33
#ifndef NULL
#define	NULL	0
#endif

E 33
#define	EXIT_FAILURE	1
#define	EXIT_SUCCESS	0

D 10
#define	RAND_MAX	0x7ffffffff
E 10
I 10
#define	RAND_MAX	0x7fffffff
E 10

D 29
#define	MB_CUR_MAX	1	/* XXX */
E 29
I 29
extern int __mb_cur_max;
#define	MB_CUR_MAX	__mb_cur_max
E 29

D 3
#ifdef __STDC__
E 3
I 3
D 5
#if __STDC__ || c_plusplus
E 5
I 5
#include <sys/cdefs.h>
E 5
E 3

D 5
void	 abort(void);
int	 abs(int);
int	 atexit(void (*_func)(void));
double	 atof(const char *_nptr);
int	 atoi(const char *_nptr);
long	 atol(const char *_nptr);
void	*bsearch(const void *_key, const void *_base, size_t _nmemb,
	    size_t _size, int (*_compar)(const void *, const void *));
void	*calloc(size_t _nmemb, size_t _size);
div_t	 div(int _numer, int _denom);
void	 exit(int _status);
void	 free(void *_ptr);
char	*getenv(const char *_string);
long	 labs(long);
ldiv_t	 ldiv(long _numer, long _denom);
void	*malloc(size_t _size);
void	 qsort(void *_base, size_t _nmemb, size_t _size,
	    int (*_compar)(const void *, const void *));
int	 rand(void);
void	*realloc(void *_ptr, size_t _size);
void	 srand(unsigned _seed);
long	 strtol(const char *_nptr, char **_endptr, int _base);
E 5
I 5
__BEGIN_DECLS
D 18
void	 abort __P((void));
int	 abs __P((int));
E 18
I 18
__dead void
	 abort __P((void));
__pure int
	 abs __P((int));
E 18
D 6
int	 atexit __P((void (*_func)(void)));
E 6
I 6
int	 atexit __P((void (*)(void)));
E 6
D 8
double	 atof __P((const char *_nptr));
int	 atoi __P((const char *_nptr));
long	 atol __P((const char *_nptr));
void	*bsearch __P((const void *_key, const void *_base, size_t _nmemb,
	    size_t _size, int (*_compar)(const void *, const void *)));
void	*calloc __P((size_t _nmemb, size_t _size));
div_t	 div __P((int _numer, int _denom));
void	 exit __P((int _status));
void	 free __P((void *_ptr));
char	*getenv __P((const char *_string));
E 8
I 8
double	 atof __P((const char *));
int	 atoi __P((const char *));
long	 atol __P((const char *));
void	*bsearch __P((const void *, const void *, size_t,
	    size_t, int (*)(const void *, const void *)));
void	*calloc __P((size_t, size_t));
D 18
div_t	 div __P((int, int));
void	 exit __P((int));
E 18
I 18
__pure div_t
	 div __P((int, int));
__dead void
	 exit __P((int));
E 18
void	 free __P((void *));
char	*getenv __P((const char *));
E 8
D 18
long	 labs __P((long));
D 8
ldiv_t	 ldiv __P((long _numer, long _denom));
void	*malloc __P((size_t _size));
void	 qsort __P((void *_base, size_t _nmemb, size_t _size,
	    int (*_compar)(const void *, const void *)));
E 8
I 8
ldiv_t	 ldiv __P((long, long));
E 18
I 18
__pure long
	 labs __P((long));
__pure ldiv_t
	 ldiv __P((long, long));
E 18
void	*malloc __P((size_t));
void	 qsort __P((void *, size_t, size_t,
	    int (*)(const void *, const void *)));
E 8
int	 rand __P((void));
D 8
void	*realloc __P((void *_ptr, size_t _size));
void	 srand __P((unsigned _seed));
long	 strtol __P((const char *_nptr, char **_endptr, int _base));
E 8
I 8
void	*realloc __P((void *, size_t));
void	 srand __P((unsigned));
double	 strtod __P((const char *, char **));
long	 strtol __P((const char *, char **, int));
E 8
E 5
D 2
u_long	 strtoul(const char *_nptr, char **_endptr, int _base);
E 2
I 2
unsigned long
D 5
	 strtoul(const char *_nptr, char **_endptr, int _base);
E 2
int	 system(const char *_string);
E 5
I 5
D 8
	 strtoul __P((const char *_nptr, char **_endptr, int _base));
int	 system __P((const char *_string));
E 8
I 8
	 strtoul __P((const char *, char **, int));
int	 system __P((const char *));
E 8
E 5

I 7
D 14
/* these are currently just stubs */
E 14
I 14
/* These are currently just stubs. */
E 14
D 8
int	mblen __P((const char *_s, size_t _n));
size_t	mbstowcs __P((wchar_t *_pwcs, const char *_s, size_t _n));
int	wctomb __P((char *_s, wchar_t _wchar));
int	mbtowc __P((wchar_t *_pwc, const char *_s, size_t _n));
size_t	wcstombs __P((char *_s, const wchar_t *_pwcs, size_t _n));
E 8
I 8
int	 mblen __P((const char *, size_t));
size_t	 mbstowcs __P((wchar_t *, const char *, size_t));
int	 wctomb __P((char *, wchar_t));
int	 mbtowc __P((wchar_t *, const char *, size_t));
size_t	 wcstombs __P((char *, const wchar_t *, size_t));
E 8

E 7
I 2
D 3
#ifndef __STDC__
E 3
I 3
#ifndef _ANSI_SOURCE
E 3
D 5
void	 cfree(void *_ptr);
int	putenv(const char *_string);
int	setenv(const char *_string, const char *_value, int _overwrite);
E 5
I 5
D 8
void	 cfree __P((void *_ptr));
int	putenv __P((const char *_string));
int	setenv __P((const char *_string, const char *_value, int _overwrite));
E 5
#endif
E 8
I 8
D 25
void	 cfree __P((void *));
E 25
int	 putenv __P((const char *));
int	 setenv __P((const char *, const char *, int));
D 14
#endif /* not ANSI */
E 14
I 14
#endif
E 14
E 8

D 8
#ifdef NOT_YET_IMPLEMENTED
D 5
int	mblen(const char *_s, size_t _n);
size_t	mbstowcs(wchar_t *_pwcs, const char *_s, size_t _n);
int	wctomb(char *_s, wchar_t _wchar);
int	mbtowc(wchar_t *_pwc, const char *_s, size_t _n);
double	strtod(const char *_nptr, char **_endptr);
size_t	wcstombs(char *_s, const wchar_t *_pwcs, size_t _n);
E 5
I 5
D 7
int	mblen __P((const char *_s, size_t _n));
size_t	mbstowcs __P((wchar_t *_pwcs, const char *_s, size_t _n));
int	wctomb __P((char *_s, wchar_t _wchar));
int	mbtowc __P((wchar_t *_pwc, const char *_s, size_t _n));
E 7
double	strtod __P((const char *_nptr, char **_endptr));
D 7
size_t	wcstombs __P((char *_s, const wchar_t *_pwcs, size_t _n));
E 7
E 5
#endif
E 8
I 8
#if !defined(_ANSI_SOURCE) && !defined(_POSIX_SOURCE)
I 27
void	*alloca __P((size_t));		/* built-in for gcc */
E 27
I 22
					/* getcap(3) functions */
I 31
char	*getbsize __P((int *, long *));
E 31
char	*cgetcap __P((char *, char *, int));
int	 cgetclose __P((void));
int	 cgetent __P((char **, char **, char *));
int	 cgetfirst __P((char **, char **));
int	 cgetmatch __P((char *, char *));
int	 cgetnext __P((char **, char **));
int	 cgetnum __P((char *, char *, long *));
int	 cgetset __P((char *));
int	 cgetstr __P((char *, char *, char **));
int	 cgetustr __P((char *, char *, char **));

I 27
int	 daemon __P((int, int));
I 31
char	*devname __P((int, int));
E 31
E 27
I 26
int	 getloadavg __P((double [], int));
I 27

E 27
E 26
E 22
D 14
void	*alloca __P((size_t));	/* built-in for gcc */
I 12
extern	 char *optarg;			/* getopt(3) external variables */
extern	 int optind;
extern	 int opterr;
E 14
I 14
D 35
extern char *optarg;			/* getopt(3) external variables */
D 17
extern int opterr, optind;
E 17
I 17
extern int opterr, optind, optopt;
E 17
E 14
E 12
D 9
int	 getopt __P((int, const char * const *, const char *));
E 9
I 9
int	 getopt __P((int, char * const *, const char *));
I 12
D 14
extern	 char *suboptarg;		/* getsubopt(3) external variable */
E 14
I 14

extern char *suboptarg;			/* getsubopt(3) external variable */
E 14
E 12
I 11
int	 getsubopt __P((char **, char * const *, char **));
I 14

E 35
D 26
void	*alloca __P((size_t));	/* built-in for gcc */
E 26
I 26
D 27
void	*alloca __P((size_t));		/* built-in for gcc */
E 27
I 27
char	*group_from_gid __P((unsigned long, int));
E 27
E 26
E 14
I 13
int	 heapsort __P((void *, size_t, size_t,
	    int (*)(const void *, const void *)));
E 13
E 11
E 9
D 36
char	*initstate __P((unsigned, char *, int));
E 36
I 36
char	*initstate __P((unsigned long, char *, long));
E 36
I 24
int	 mergesort __P((void *, size_t, size_t,
	    int (*)(const void *, const void *)));
E 24
D 15
int	 radixsort __P((const u_char **, int, const u_char *, u_char));
E 15
I 15
D 23
int	 radixsort __P((const u_char **, int, const u_char *, u_int));
I 21
int	 sradixsort __P((const u_char **, int, const u_char *, u_int));
E 23
I 23
int	 radixsort __P((const unsigned char **, int, const unsigned char *,
	    unsigned));
int	 sradixsort __P((const unsigned char **, int, const unsigned char *,
	    unsigned));
E 23
E 21
E 15
long	 random __P((void));
I 34
char	*realpath __P((const char *, char resolved_path[]));
E 34
char	*setstate __P((char *));
D 36
void	 srandom __P((unsigned));
E 36
I 36
void	 srandom __P((unsigned long));
E 36
I 27
char	*user_from_uid __P((unsigned long, int));
E 27
I 23
#ifndef __STRICT_ANSI__
E 23
I 20
long long
	 strtoq __P((const char *, char **, int));
unsigned long long
	 strtouq __P((const char *, char **, int));
I 23
#endif
E 23
E 20
void	 unsetenv __P((const char *));
D 14
#endif /* neither ANSI nor POSIX */

E 14
I 14
#endif
E 14
E 8
D 5

E 2
D 3
#else /* !__STDC__ */
E 3
I 3
#else
E 3

void	 abort();
int	 abs();
int	 atexit();
double	 atof();
int	 atoi();
long	 atol();
void	*bsearch();
void	*calloc();
div_t	 div();
void	 exit();
void	 free();
char	*getenv();
long	 labs();
ldiv_t	 ldiv();
void	*malloc();
void	 qsort();
int	 rand();
void	*realloc();
void	 srand();
long	 strtol();
D 2
u_long	 strtoul();
E 2
I 2
unsigned long
	 strtoul();
E 2
int	 system();

D 2
#endif /* __STDC__ */
E 2
I 2
D 3
#ifndef __STDC__
E 3
I 3
#ifndef _ANSI_SOURCE
E 3
void	 cfree();
int	putenv();
int	setenv();
#endif
E 2

#ifdef NOT_YET_IMPLEMENTED
D 2
int	mblen(const char *_s, size_t _n);
size_t	mbstowcs(wchar_t *_pwcs, const char *_s, size_t _n);
int	wctomb(char *_s, wchar_t _wchar);
int	mbtowc(wchar_t *_pwc, const char *_s, size_t _n);
double	strtod(const char *_nptr, char **_endptr);
size_t	wcstombs(char *_s, const wchar_t *_pwcs, size_t _n);
E 2
I 2
int	mblen();
size_t	mbstowcs();
int	wctomb();
int	mbtowc();
double	strtod();
size_t	wcstombs();
E 2
#endif
I 2

D 3
#endif /* __STDC__ */
E 3
I 3
#endif
E 5
I 5
__END_DECLS
E 5
E 3
E 2

#endif /* _STDLIB_H_ */
E 1
