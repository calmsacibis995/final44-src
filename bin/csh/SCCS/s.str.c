h30945
s 00002/00002/00439
d D 8.1 93/05/31 16:43:02 bostic 14 13
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00005/00436
d D 5.13 93/05/22 19:06:51 christos 13 12
c Fixed gcc -Wall warnings
e
s 00005/00002/00436
d D 5.12 92/02/05 16:30:04 christos 12 11
c Use vis(3) to print unprintable characters
e
s 00032/00000/00406
d D 5.11 91/11/06 16:09:56 christos 11 10
c Added support for displaying non-printable characters
e
s 00000/00002/00406
d D 5.10 91/11/04 18:22:39 christos 10 9
c We need strstr now...
e
s 00035/00020/00373
d D 5.9 91/10/28 21:28:12 leres 9 8
c Fix gcc "bodyless for/while" warnings.
e
s 00002/00001/00391
d D 5.8 91/07/22 11:47:54 christos 8 7
c no short strings bug fix
e
s 00045/00044/00347
d D 5.7 91/07/19 17:31:31 christos 7 6
c stdio based version; brace glob fix; builtin prototypes
e
s 00015/00014/00376
d D 5.6 91/07/02 19:22:04 christos 6 5
c strncmp was not working after last update
e
s 00001/00001/00389
d D 5.5 91/06/26 23:45:29 christos 5 4
c This one should work.
e
s 00028/00009/00362
d D 5.4 91/06/17 14:53:38 christos 4 3
c Fixed problem introduced by changing int to size_T
e
s 00039/00031/00332
d D 5.3 91/06/08 17:09:08 christos 3 2
c More prototype fixes, Removed TERMIOS define
e
s 00002/00001/00361
d D 5.2 91/06/07 11:13:47 bostic 2 1
c rename all the files (they weren't going to diff anyway)
c add function prototypes for extern functions, decls.h -> extern.h
c delete btell function, VFORK #define, lots of other minor cleanups
e
s 00362/00000/00000
d D 5.1 91/06/04 16:53:29 christos 1 0
c date and time created 91/06/04 16:53:29 by christos
e
u
U
t
T
I 1
/*-
D 14
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 14
I 14
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 14
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

I 7
#define MALLOC_INCR	128

E 7
/*
 * tc.str.c: Short string package
D 9
 * 	     This has been a lesson of how to write buggy code!
E 9
I 9
 *	     This has been a lesson of how to write buggy code!
E 9
 */
D 8
#ifdef SHORT_STRINGS
E 8

I 11
#include <sys/types.h>
E 11
I 3
#if __STDC__
# include <stdarg.h>
#else
# include <varargs.h>
#endif
I 11
#include <vis.h>
E 11

E 3
D 2
#include "sh.h"
E 2
I 2
#include "csh.h"
#include "extern.h"
I 8

#ifdef SHORT_STRINGS
E 8
E 2

Char  **
blk2short(src)
    register char **src;
{
D 3
    int     n;
E 3
I 3
    size_t     n;
E 3
    register Char **sdst, **dst;

    /*
     * Count
     */
D 3
    for (n = 0; src[n] != (char *) 0; n++);
E 3
I 3
D 9
    for (n = 0; src[n] != NULL; n++);
E 9
I 9
    for (n = 0; src[n] != NULL; n++)
	continue;
E 9
E 3
    sdst = dst = (Char **) xmalloc((size_t) ((n + 1) * sizeof(Char *)));

D 3
    for (; *src != (char *) 0; src++)
E 3
I 3
    for (; *src != NULL; src++)
E 3
	*dst++ = SAVE(*src);
    *dst = NULL;
    return (sdst);
}

char  **
short2blk(src)
    register Char **src;
{
D 3
    int     n;
E 3
I 3
    size_t     n;
E 3
    register char **sdst, **dst;

    /*
     * Count
     */
D 3
    for (n = 0; src[n] != (Char *) 0; n++);
E 3
I 3
D 9
    for (n = 0; src[n] != NULL; n++);
E 9
I 9
    for (n = 0; src[n] != NULL; n++)
	continue;
E 9
E 3
    sdst = dst = (char **) xmalloc((size_t) ((n + 1) * sizeof(char *)));

D 3
    for (; *src != (Char *) 0; src++)
E 3
I 3
    for (; *src != NULL; src++)
E 3
	*dst++ = strsave(short2str(*src));
D 3
    *dst = (char *) 0;
E 3
I 3
    *dst = NULL;
E 3
    return (sdst);
}

D 7
#define MALLOC_INCR	1024
E 7
Char   *
str2short(src)
    register char *src;
{
    static Char *sdst;
D 3
    static int dstsize = 0;
E 3
I 3
    static size_t dstsize = 0;
E 3
    register Char *dst, *edst;

D 3
    if (src == (char *) 0)
	return ((Char *) 0);
E 3
I 3
    if (src == NULL)
	return (NULL);
E 3

D 3
    if (sdst == (Char *) 0) {
E 3
I 3
    if (sdst == (NULL)) {
E 3
	dstsize = MALLOC_INCR;
	sdst = (Char *) xmalloc((size_t) dstsize * sizeof(Char));
    }

    dst = sdst;
    edst = &dst[dstsize];
    while (*src) {
	*dst++ = (Char) ((unsigned char) *src++);
	if (dst == edst) {
	    dstsize += MALLOC_INCR;
	    sdst = (Char *) xrealloc((ptr_t) sdst,
				     (size_t) dstsize * sizeof(Char));
	    edst = &sdst[dstsize];
	    dst = &edst[-MALLOC_INCR];
	}
    }
    *dst = 0;
    return (sdst);
}

char   *
D 7
short2qstr(src)
    register Char *src;
{
D 3
    static char *sdst = (char *) 0;
    static int dstsize = 0;
E 3
I 3
    static char *sdst = NULL;
    static size_t dstsize = 0;
E 3
    register char *dst, *edst;

D 3
    if (src == (Char *) 0)
	return ((char *) 0);
E 3
I 3
    if (src == NULL)
	return (NULL);
E 3

D 3
    if (sdst == (char *) 0) {
E 3
I 3
    if (sdst == NULL) {
E 3
	dstsize = MALLOC_INCR;
	sdst = (char *) xmalloc((size_t) dstsize * sizeof(char));
    }
    dst = sdst;
    edst = &dst[dstsize];
    while (*src) {
	if (*src & QUOTE) {
	    *dst++ = '\\';
	    if (dst == edst) {
		dstsize += MALLOC_INCR;
		sdst = (char *) xrealloc((ptr_t) sdst,
					 (size_t) dstsize * sizeof(char));
		edst = &sdst[dstsize];
		dst = &edst[-MALLOC_INCR];
	    }
	}
	*dst++ = (char) *src++;
	if (dst == edst) {
	    dstsize += MALLOC_INCR;
	    sdst = (char *) xrealloc((ptr_t) sdst,
				     (size_t) dstsize * sizeof(char));
	    edst = &sdst[dstsize];
	    dst = &edst[-MALLOC_INCR];
	}
    }
    *dst = 0;
    return (sdst);
}
char   *
E 7
short2str(src)
    register Char *src;
{
D 3
    static char *sdst = (char *) 0;
    static int dstsize = 0;
E 3
I 3
    static char *sdst = NULL;
    static size_t dstsize = 0;
E 3
    register char *dst, *edst;

D 3
    if (src == (Char *) 0)
	return ((char *) 0);
E 3
I 3
    if (src == NULL)
	return (NULL);
E 3

D 3
    if (sdst == (char *) 0) {
E 3
I 3
    if (sdst == NULL) {
E 3
	dstsize = MALLOC_INCR;
	sdst = (char *) xmalloc((size_t) dstsize * sizeof(char));
    }
    dst = sdst;
    edst = &dst[dstsize];
    while (*src) {
	*dst++ = (char) *src++;
	if (dst == edst) {
	    dstsize += MALLOC_INCR;
	    sdst = (char *) xrealloc((ptr_t) sdst,
				     (size_t) dstsize * sizeof(char));
	    edst = &sdst[dstsize];
	    dst = &edst[-MALLOC_INCR];
	}
    }
    *dst = 0;
    return (sdst);
}

Char   *
s_strcpy(dst, src)
    register Char *dst, *src;
{
    register Char *sdst;

    sdst = dst;
D 9
    while (*dst++ = *src++);
E 9
I 9
D 13
    while (*dst++ = *src++)
E 13
I 13
    while ((*dst++ = *src++) != '\0')
E 13
	continue;
E 9
    return (sdst);
}

Char   *
s_strncpy(dst, src, n)
    register Char *dst, *src;
D 3
    register int n;
E 3
I 3
    register size_t n;
E 3
{
    register Char *sdst;

I 4
    if (n == 0)
	return(dst);

E 4
    sdst = dst;
D 4
    while (--n >= 0 && (*dst++ = *src++));
    while (--n >= 0)
	*dst++ = '\0';
E 4
I 4
D 9
    do 
E 9
I 9
    do
E 9
	if ((*dst++ = *src++) == '\0') {
D 5
	    while (--n > 0)
E 5
I 5
	    while (--n != 0)
E 5
		*dst++ = '\0';
	    return(sdst);
	}
    while (--n != 0);
E 4
    return (sdst);
}

Char   *
s_strcat(dst, src)
    register Char *dst, *src;
{
    register short *sdst;

    sdst = dst;
D 9
    while (*dst++);
E 9
I 9
    while (*dst++)
	continue;
E 9
    --dst;
D 9
    while (*dst++ = *src++);
E 9
I 9
D 13
    while (*dst++ = *src++)
E 13
I 13
    while ((*dst++ = *src++) != '\0')
E 13
	continue;
E 9
    return (sdst);
}

#ifdef NOTUSED
Char   *
s_strncat(dst, src, n)
    register Char *dst, *src;
D 3
    register int n;
E 3
I 3
    register size_t n;
E 3
{
    register Char *sdst;

I 4
D 9
    if (n == 0) 
E 9
I 9
    if (n == 0)
E 9
	return (dst);

E 4
    sdst = dst;
I 4

E 4
D 9
    while (*dst++);
E 9
I 9
    while (*dst++)
	continue;
E 9
    --dst;
D 4
    while (*src && --n >= 0)
	*dst++ = *src++;
    *dst++ = '\0';
E 4
I 4

D 9
    do 
E 9
I 9
    do
E 9
	if ((*dst++ = *src++) == '\0')
	    return(sdst);
D 9
    while (--n != 0);
E 9
I 9
    while (--n != 0)
	continue;
E 9

    *dst = '\0';
E 4
    return (sdst);
}

#endif

Char   *
s_strchr(str, ch)
D 3
    register Char *str, ch;
E 3
I 3
    register Char *str;
    int ch;
E 3
{
    do
	if (*str == ch)
	    return (str);
    while (*str++);
D 3
    return ((Char *) 0);
E 3
I 3
    return (NULL);
E 3
}

Char   *
s_strrchr(str, ch)
D 3
    register short *str, ch;
E 3
I 3
    register Char *str;
    int ch;
E 3
{
    register Char *rstr;

D 3
    rstr = (Char *) 0;
E 3
I 3
    rstr = NULL;
E 3
    do
	if (*str == ch)
	    rstr = str;
    while (*str++);
    return (rstr);
}

D 3
int
E 3
I 3
size_t
E 3
s_strlen(str)
    register Char *str;
{
D 3
    register int n;
E 3
I 3
    register size_t n;
E 3

D 9
    for (n = 0; *str++; n++);
E 9
I 9
    for (n = 0; *str++; n++)
	continue;
E 9
    return (n);
}

int
s_strcmp(str1, str2)
    register Char *str1, *str2;
{
D 9
    for (; *str1 && *str1 == *str2; str1++, str2++);
E 9
I 9
    for (; *str1 && *str1 == *str2; str1++, str2++)
	continue;
E 9
    /*
     * The following case analysis is necessary so that characters which look
     * negative collate low against normal characters but high against the
     * end-of-string NUL.
     */
    if (*str1 == '\0' && *str2 == '\0')
	return (0);
    else if (*str1 == '\0')
	return (-1);
    else if (*str2 == '\0')
	return (1);
    else
	return (*str1 - *str2);
}

int
s_strncmp(str1, str2, n)
    register Char *str1, *str2;
D 3
    register int n;
E 3
I 3
    register size_t n;
E 3
{
D 4
    for (; --n >= 0 && *str1 == *str2; str1++, str2++);

    if (n < 0)
E 4
I 4
    if (n == 0)
E 4
	return (0);
I 4
    do {
D 6
        if (*str1 == '\0' || *str1 != *str2)
E 6
I 6
	if (*str1 != *str2) {
	    /*
D 9
	     * The following case analysis is necessary so that characters 
E 9
I 9
	     * The following case analysis is necessary so that characters
E 9
	     * which look negative collate low against normal characters
	     * but high against the end-of-string NUL.
	     */
	    if (*str1 == '\0')
		return (-1);
	    else if (*str2 == '\0')
		return (1);
	    else
		return (*str1 - *str2);
E 6
	    break;
I 6
	}
        if (*str1 == '\0')
	    return(0);
E 6
	str1++, str2++;
    } while (--n != 0);
E 4
D 6
    /*
     * The following case analysis is necessary so that characters which look
     * negative collate low against normal characters but high against the
     * end-of-string NUL.
     */
    if (*str1 == '\0' && *str2 == '\0')
	return (0);
    else if (*str1 == '\0')
	return (-1);
    else if (*str2 == '\0')
	return (1);
    else
	return (*str1 - *str2);
E 6
I 4
    return(0);
E 4
}

Char   *
s_strsave(s)
    register Char *s;
{
    Char   *n;
    register Char *p;

    if (s == 0)
	s = STRNULL;
D 9
    for (p = s; *p++;);
E 9
I 9
    for (p = s; *p++;)
	continue;
E 9
    n = p = (Char *) xmalloc((size_t) ((p - s) * sizeof(Char)));
D 9
    while (*p++ = *s++);
E 9
I 9
D 13
    while (*p++ = *s++)
E 13
I 13
    while ((*p++ = *s++) != '\0')
E 13
	continue;
E 9
    return (n);
}

Char   *
s_strspl(cp, dp)
    Char   *cp, *dp;
{
    Char   *ep;
    register Char *p, *q;

    if (!cp)
	cp = STRNULL;
    if (!dp)
	dp = STRNULL;
D 9
    for (p = cp; *p++;);
    for (q = dp; *q++;);
E 9
I 9
    for (p = cp; *p++;)
	continue;
    for (q = dp; *q++;)
	continue;
E 9
    ep = (Char *) xmalloc((size_t)
			  (((p - cp) + (q - dp) - 1) * sizeof(Char)));
D 9
    for (p = ep, q = cp; *p++ = *q++;);
    for (p--, q = dp; *p++ = *q++;);
E 9
I 9
D 13
    for (p = ep, q = cp; *p++ = *q++;)
E 13
I 13
    for (p = ep, q = cp; (*p++ = *q++) != '\0';)
E 13
	continue;
D 13
    for (p--, q = dp; *p++ = *q++;)
E 13
I 13
    for (p--, q = dp; (*p++ = *q++) != '\0';)
E 13
	continue;
E 9
    return (ep);
}

Char   *
s_strend(cp)
    register Char *cp;
{
    if (!cp)
	return (cp);
    while (*cp)
	cp++;
    return (cp);
}

D 7
#ifdef NOTUSED
E 7
I 7
D 10
# ifdef NOTUSED
E 10
E 7
Char   *
s_strstr(s, t)
    register Char *s, *t;
{
    do {
	register Char *ss = s;
	register Char *tt = t;

	do
	    if (*tt == '\0')
		return (s);
	while (*ss++ == *tt++);
    } while (*s++ != '\0');
D 3
    return ((Char *) 0);
E 3
I 3
    return (NULL);
E 3
}
D 7
#endif

E 7
I 7
D 10
# endif
E 10
E 7
#endif				/* SHORT_STRINGS */
I 7

char   *
short2qstr(src)
    register Char *src;
{
    static char *sdst = NULL;
    static size_t dstsize = 0;
    register char *dst, *edst;

    if (src == NULL)
	return (NULL);

    if (sdst == NULL) {
	dstsize = MALLOC_INCR;
	sdst = (char *) xmalloc((size_t) dstsize * sizeof(char));
    }
    dst = sdst;
    edst = &dst[dstsize];
    while (*src) {
	if (*src & QUOTE) {
	    *dst++ = '\\';
	    if (dst == edst) {
		dstsize += MALLOC_INCR;
		sdst = (char *) xrealloc((ptr_t) sdst,
					 (size_t) dstsize * sizeof(char));
		edst = &sdst[dstsize];
		dst = &edst[-MALLOC_INCR];
	    }
	}
	*dst++ = (char) *src++;
	if (dst == edst) {
	    dstsize += MALLOC_INCR;
	    sdst = (char *) xrealloc((ptr_t) sdst,
				     (size_t) dstsize * sizeof(char));
	    edst = &sdst[dstsize];
	    dst = &edst[-MALLOC_INCR];
	}
    }
    *dst = 0;
    return (sdst);
}
I 11

/*
 * XXX: Should we worry about QUOTE'd chars?
 */
char *
vis_str(cp)
    Char *cp;
{
    static char *sdst = NULL;
    static size_t dstsize = 0;
    size_t n;
    Char *dp;

    if (cp == NULL)
	return (NULL);
    
    for (dp = cp; *dp++;)
	continue;
    n = ((dp - cp) << 2) + 1; /* 4 times + NULL */
    if (dstsize < n) {
	sdst = (char *) (dstsize ? 
			    xrealloc(sdst, (size_t) n * sizeof(char)) :
			    xmalloc((size_t) n * sizeof(char)));
	dstsize = n;
    }
D 12
    (void) strvis(sdst, short2str(cp), 
		  AsciiOnly ? VIS_NOSLASH : (VIS_NLS | VIS_NOSLASH));
E 12
I 12
    /* 
     * XXX: When we are in AsciiOnly we want all characters >= 0200 to
     * be encoded, but currently there is no way in vis to do that.
     */
    (void) strvis(sdst, short2str(cp), VIS_NOSLASH);
E 12
    return (sdst);
}
    
E 11
E 7
E 1
