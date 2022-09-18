h26571
s 00005/00005/00080
d D 8.1 93/06/11 16:01:06 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00085/00000/00000
d D 7.1 93/06/11 14:35:15 mckusick 1 0
c date and time created 93/06/11 14:35:15 by mckusick
e
u
U
t
T
I 1
/*-
D 2
 * Copyright (c) 1993 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
D 2
char copyright[] =
"%Z% Copyright (c) 1993 The Regents of the University of California.\n\
 All rights reserved.\n";
E 2
I 2
static char copyright[] =
"%Z% Copyright (c) 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 2
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/param.h>
#include <ufs/ufs/dir.h>
#include <sys/ttychars.h>
#include <stand/stand.h>

main()
{
	struct dinode *ip;
	int fd;

	for (;;) {
		if ((fd = getfile("ls", 0)) == -1)
			exit();
		ip = &iob[fd - 3].i_ino;
		if ((ip->di_mode & IFMT) != IFDIR) {
			printf("ls: not a directory\n");
			continue;
		}
		if (ip->di_size == 0) {
			printf("ls: zero length directory\n");
			continue;
		}
		ls(fd);
	}
}

#define CTRL(x)	(x&037)

getfile(prompt, mode)
	char *prompt;
	int mode;
{
	int fd;
	char buf[100];

	do {
		printf("%s: ", prompt);
		gets(buf);
		if (buf[0] == CTRL('d') && buf[1] == 0)
			return (-1);
	} while ((fd = open(buf, mode)) < 0);
	return(fd);
}

typedef struct direct	DP;
static
ls(fd)
	register int fd;
{
	register int size;
	register char *dp;
	char dirbuf[DIRBLKSIZ];

	printf("\ninode\tname\n");
	while ((size = read(fd, dirbuf, DIRBLKSIZ)) == DIRBLKSIZ)
		for (dp = dirbuf; (dp < (dirbuf + size)) &&
		    (dp + ((DP *)dp)->d_reclen) < (dirbuf + size);
		    dp += ((DP *)dp)->d_reclen) {
			if (((DP *)dp)->d_ino == 0)
				continue;
			if (((DP *)dp)->d_namlen > MAXNAMLEN+1) {
				printf("Corrupt file name length!  Run fsck soon!\n");
				return;
			}
			printf("%d\t%s\n", ((DP *)dp)->d_ino,
			    ((DP *)dp)->d_name);
		}
}
E 1
