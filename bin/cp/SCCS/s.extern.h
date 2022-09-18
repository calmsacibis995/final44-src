h61661
s 00008/00011/00021
d D 8.2 94/04/01 10:17:40 bostic 7 6
c POSIX 1003.2B/D9 symbolic links
c make cp use err/warn, and pass errors back to the calling routine
c clean up fts_read() usage, fix errno calls
c make file-copy failed error clean up after itself immediately
e
s 00002/00002/00030
d D 8.1 93/05/31 14:18:55 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00003/00031
d D 5.5 92/06/08 16:19:42 bostic 5 4
c whitespace cleanups, no real changes
e
s 00013/00004/00021
d D 5.4 92/06/01 10:58:31 elan 4 3
c Modified to work with new version.
e
s 00001/00000/00024
d D 5.3 91/10/27 08:56:00 bostic 3 2
c add err prototype
e
s 00004/00004/00020
d D 5.2 91/04/03 12:48:52 bostic 2 1
c messed up the prototypes
e
s 00024/00000/00000
d D 5.1 91/04/03 11:22:39 bostic 1 0
c date and time created 91/04/03 11:22:39 by bostic
e
u
U
t
T
I 1
/*-
D 6
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
D 7
 * Copyright (c) 1991, 1993
E 7
I 7
 * Copyright (c) 1991, 1993, 1994
E 7
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

typedef struct {
	char *p_end;			/* pointer to NULL at end of path */
I 4
	char *target_end;               /* pointer to end of target base */
E 4
	char p_path[MAXPATHLEN + 1];	/* pointer to the start of a path */
} PATH_T;

D 7
extern char *progname;			/* program name */
E 7
I 4
extern PATH_T to;
D 7
extern int iflag, pflag;
E 7
extern uid_t myuid;
D 7
extern int exit_val, myumask;
E 7
I 7
extern int iflag, pflag, myumask;
E 7
E 4

#include <sys/cdefs.h>

__BEGIN_DECLS
I 3
D 5
void	 err __P((const char *fmt, ...));
E 3
D 2
int	 path_set(PATH_T *, char *);
char	*path_append(PATH_T *, char *, int);
char	*path_basename(PATH_T *);
void	 path_restore(PATH_T *, char *);
E 2
I 2
D 4
int	 path_set __P((PATH_T *, char *));
char	*path_append __P((PATH_T *, char *, int));
char	*path_basename __P((PATH_T *));
void	 path_restore __P((PATH_T *, char *));
E 4
I 4

E 5
D 7
void copy_fifo __P((struct stat *, int));
void copy_file __P((FTSENT *, int));
void copy_link __P((FTSENT *, int));
void copy_special __P((struct stat *, int));
I 5
void err __P((const char *fmt, ...));
E 5
void setfile __P((struct stat *, int));
void usage __P((void));
E 7
I 7
int	copy_fifo __P((struct stat *, int));
int	copy_file __P((FTSENT *, int));
int	copy_link __P((FTSENT *, int));
int	copy_special __P((struct stat *, int));
int	setfile __P((struct stat *, int));
void	usage __P((void));
E 7
D 5

E 5
E 4
E 2
__END_DECLS
E 1
