h51343
s 00005/00001/00018
d D 4.3 91/04/18 16:34:52 bostic 3 2
c new copyright; att/bsd/shared
e
s 00002/00000/00017
d D 4.2 83/08/11 21:04:53 sam 2 1
c standardize sccs keyword lines
e
s 00017/00000/00000
d D 4.1 83/05/06 23:50:12 tut 1 0
c date and time created 83/05/06 23:50:12 by tut
e
u
U
t
T
I 2
D 3
/*	%M%	%I%	%E%	*/
E 3
I 3
/*-
 * %sccs.include.proprietary.c%
 *
 *	%W% (Berkeley) %G%
 */
E 3

E 2
I 1
#include <stdio.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <assert.h>
#define NFILES 100
#define NAMES 2000
#define NFEED 5
extern exch(), comp();
struct filans {
	char *nm;
	long fdate;
	long size;
	int uid;
	};
extern struct filans files[NFILES];
extern char fnames[NAMES];
E 1
