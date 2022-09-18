h15948
s 00001/00001/00078
d D 8.3 94/04/02 10:03:38 pendry 12 11
c add 1994 copyright
e
s 00005/00007/00074
d D 8.2 94/04/01 04:59:40 pendry 11 10
c prettyness police
e
s 00002/00002/00079
d D 8.1 93/06/06 14:19:12 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00003/00078
d D 5.9 92/06/19 15:15:06 bostic 9 8
c st_size is now a quad, st_mtime is now a timespec
e
s 00003/00001/00078
d D 5.8 91/04/12 14:29:11 bostic 8 7
c lost the redist include line somewhere
e
s 00002/00002/00077
d D 5.7 91/03/21 12:16:02 bostic 7 6
c rename -s option to -T (Sys V. compatibility)
e
s 00004/00004/00075
d D 5.6 91/03/12 09:07:38 bostic 6 5
c make archive routine naming consistent
e
s 00013/00013/00066
d D 5.5 91/03/11 21:16:09 bostic 5 4
c make ORPHANS a function; add externals, minor cleanups
e
s 00003/00003/00076
d D 5.4 91/03/11 10:27:47 bostic 4 3
c get truncated names right -- it's 15 chars, not 16
e
s 00009/00005/00070
d D 5.3 91/03/10 16:26:03 bostic 3 2
c add -s option which inserts/matches truncated member names
e
s 00003/00008/00072
d D 5.2 91/03/10 15:36:19 bostic 2 1
c cleanup, get padding and archive creation right, delete SKIP macro
e
s 00080/00000/00000
d D 5.1 91/01/21 09:11:26 bostic 1 0
c date and time created 91/01/21 09:11:26 by bostic
e
u
U
t
T
I 1
/*-
D 8
 * Copyright (c) 1990 The Regents of the University of California.
E 8
I 8
D 10
 * Copyright (c) 1991 The Regents of the University of California.
E 8
 * All rights reserved.
E 10
I 10
D 12
 * Copyright (c) 1991, 1993
E 12
I 12
 * Copyright (c) 1991, 1993, 1994
E 12
 *	The Regents of the University of California.  All rights reserved.
E 10
 *
 * This code is derived from software contributed to Berkeley by
 * Hugh Smith at The University of Guelph.
I 8
 *
 * %sccs.include.redist.c%
E 8
 *
 *	%W% (Berkeley) %G%
 */

/* Ar(1) options. */
#define	AR_A	0x0001
#define	AR_B	0x0002
#define	AR_C	0x0004
#define	AR_D	0x0008
#define	AR_M	0x0010
#define	AR_O	0x0020
#define	AR_P	0x0040
#define	AR_Q	0x0080
#define	AR_R	0x0100
D 3
#define	AR_T	0x0200
#define	AR_U	0x0400
#define	AR_V	0x0800
#define	AR_X	0x1000
E 3
I 3
D 7
#define	AR_S	0x0200
#define	AR_T	0x0400
E 7
I 7
#define	AR_T	0x0200
#define	AR_TR	0x0400
E 7
#define	AR_U	0x0800
#define	AR_V	0x1000
#define	AR_X	0x2000
E 3
extern u_int options;

/* Set up file copy. */
#define	SETCF(from, fromname, to, toname, pad) { \
	cf.rfd = from; \
	cf.rname = fromname; \
	cf.wfd = to; \
	cf.wname = toname; \
	cf.flags = pad; \
}

/* File copy structure. */
typedef struct {
	int rfd;			/* read file descriptor */
	char *rname;			/* read name */
	int wfd;			/* write file descriptor */
	char *wname;			/* write name */
I 2
#define	NOPAD	0x00			/* don't pad */
E 2
#define	RPAD	0x01			/* pad on reads */
#define	WPAD	0x02			/* pad on writes */
	u_int flags;			/* pad flags */
} CF;

/* Header structure internal format. */
typedef struct {
I 2
	off_t size;			/* size of the object in bytes */
E 2
	long date;			/* date */
D 2
	long size;			/* size in bytes */
E 2
I 2
	int lname;			/* size of the long name in bytes */
E 2
	int gid;			/* group */
D 2
	int lname;			/* if long name */
E 2
	int uid;			/* owner */
	u_short mode;			/* permissions */
	char name[MAXNAMLEN + 1];	/* name */
} CHDR;

D 2
/* Seek over the module contents; always rounds. */
#define	SKIP(fd, size, name) { \
	if (lseek((fd), ((size) + ((size) & 1)), SEEK_CUR) == (off_t)-1) \
		error(name); \
}
	
E 2
D 5
/* Print out any files that weren't in the archive. */
#define	ORPHANS { \
	if (*argv) { \
		eval = 1; \
		do { \
			(void)fprintf(stderr, \
			    "ar: %s: not found in archive.\n", *argv); \
		} while (*++argv); \
	} \
}

E 5
I 3
D 4
/* Old archive format name limit. */
#define	ARNAMEMAX	16

E 4
E 3
/* Header format strings. */
D 9
#define	HDR1	"%s%-13d%-12ld%-6u%-6u%-8o%-10ld%2s"
D 3
#define	HDR2	"%-16s%-12ld%-6u%-6u%-8o%-10ld%2s"
E 3
I 3
#define	HDR2	"%-16.16s%-12ld%-6u%-6u%-8o%-10ld%2s"
E 9
I 9
#define	HDR1	"%s%-13d%-12ld%-6u%-6u%-8o%-10qd%2s"
#define	HDR2	"%-16.16s%-12ld%-6u%-6u%-8o%-10qd%2s"
E 9
I 4

#define	OLDARMAXNAME	15
D 9
#define	HDR3	"%-16.15s%-12ld%-6u%-6u%-8o%-10ld%2s"
E 9
I 9
#define	HDR3	"%-16.15s%-12ld%-6u%-6u%-8o%-10qd%2s"
E 9
E 4
E 3

D 5
#include <stdlib.h>
#include <string.h>
E 5
I 5

#include <sys/cdefs.h>

D 11
__BEGIN_DECLS
E 11
I 11
struct stat;

E 11
void	close_archive __P((int));
D 6
void	skipobj __P((int));
int	copyfile __P((CF *, off_t));
int	get_header __P((int));
E 6
I 6
D 11
void	skip_arobj __P((int));
int	copy_ar __P((CF *, off_t));
E 11
I 11
void	copy_ar __P((CF *, off_t));
E 11
int	get_arobj __P((int));
E 6
int	open_archive __P((int));
D 11
struct stat;
D 6
int	put_object __P((CF *, struct stat *));
E 6
I 6
int	put_arobj __P((CF *, struct stat *));
E 6
__END_DECLS

E 11
I 11
void	put_arobj __P((CF *, struct stat *));
void	skip_arobj __P((int));
E 11
E 5
E 1
