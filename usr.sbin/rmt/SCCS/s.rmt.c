h21955
s 00005/00005/00213
d D 8.1 93/06/06 14:05:23 bostic 17 16
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00217
d D 5.8 93/05/19 14:56:52 bostic 16 15
c cast lseek argument
e
s 00030/00021/00188
d D 5.7 93/05/17 23:48:11 torek 15 14
c cleanup, prototype, pass -Wall (it started with lseek again)
e
s 00001/00011/00208
d D 5.6 90/06/01 18:55:04 bostic 14 13
c new copyright notice
e
s 00004/00005/00215
d D 5.5 90/05/27 10:52:36 bostic 13 12
c use strerror, not sys_errlist
e
s 00015/00004/00205
d D 5.4 88/06/29 16:31:41 bostic 12 11
c add Berkeley specific copyright
e
s 00000/00001/00209
d D 5.3 87/10/22 10:39:02 bostic 11 10
c ANSI C; sprintf now returns an int.
e
s 00001/00000/00209
d D 5.2 86/01/07 12:27:59 mckusick 10 9
c save size to avoid free/malloc continuously (from terry@randgr.arpa)
e
s 00014/00002/00195
d D 5.1 85/05/28 15:20:59 dist 9 8
c Add copyright
e
s 00003/00001/00194
d D 4.8 85/03/24 18:14:38 mckusick 8 7
c retry setsockopt until an agreeable size is found
e
s 00027/00009/00168
d D 4.7 85/03/20 18:42:37 mckusick 7 6
c dynamically allocate buffer space based on needs
e
s 00003/00001/00174
d D 4.6 85/01/23 08:28:54 ralph 6 5
c Status record packet wasn't formatted correctly.
e
s 00003/00000/00172
d D 4.5 84/12/19 11:49:43 ralph 5 4
c use setsockopt to increase buffer size.
e
s 00022/00019/00150
d D 4.4 84/11/15 19:19:04 sam 4 3
c somebody changed stdio.h; also cleanup debug code
e
s 00011/00008/00158
d D 4.3 82/05/19 00:46:22 mckusick 3 2
c fix read code
e
s 00005/00002/00161
d D 4.2 82/04/19 09:37:35 mckusick 2 1
c tef's changes to make compatible with PDP-11s
e
s 00163/00000/00000
d D 4.1 82/04/02 10:29:00 wnj 1 0
c date and time created 82/04/02 10:29:00 by wnj
e
u
U
t
T
I 9
/*
D 17
 * Copyright (c) 1983 Regents of the University of California.
D 12
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 12
I 12
 * All rights reserved.
E 17
I 17
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 17
 *
D 14
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 14
I 14
 * %sccs.include.redist.c%
E 14
E 12
 */

E 9
I 1
#ifndef lint
D 4
static char sccsid[] = "%W% %E%";
E 4
I 4
D 9
static char sccsid[] = "%W% (Berkeley) %E%";
E 4
#endif
E 9
I 9
D 17
char copyright[] =
"%Z% Copyright (c) 1983 Regents of the University of California.\n\
 All rights reserved.\n";
E 17
I 17
static char copyright[] =
"%Z% Copyright (c) 1983, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 17
D 12
#endif not lint
E 12
I 12
#endif /* not lint */
E 12

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 12
#endif not lint
E 12
I 12
#endif /* not lint */
E 12
E 9

/*
 * rmt
 */
D 15
#include <stdio.h>
#include <sgtty.h>
E 15
#include <sys/types.h>
I 5
#include <sys/socket.h>
E 5
#include <sys/mtio.h>
#include <errno.h>
I 15
#include <fcntl.h>
#include <sgtty.h>
#include <stdio.h>
#include <stdlib.h>
E 15
I 13
#include <string.h>
I 15
#include <unistd.h>
E 15
E 13

int	tape = -1;

D 2
#define	MAXRECSIZ	(60*1024)
E 2
I 2
D 7
#define	MAXRECSIZ	(10*1024)	/* small enuf for pdp-11's too */
E 2
char	record[MAXRECSIZ];
E 7
I 7
char	*record;
int	maxrecsize = -1;
D 15
char	*checkbuf();
E 15
E 7

#define	SSIZE	64
char	device[SSIZE];
char	count[SSIZE], mode[SSIZE], pos[SSIZE], op[SSIZE];

D 13
extern	errno;
char	*sys_errlist[];
E 13
char	resp[BUFSIZ];

D 11
char	*sprintf();
E 11
D 15
long	lseek();

E 15
FILE	*debug;
I 4
#define	DEBUG(f)	if (debug) fprintf(debug, f)
#define	DEBUG1(f,a)	if (debug) fprintf(debug, f, a)
#define	DEBUG2(f,a1,a2)	if (debug) fprintf(debug, f, a1, a2)
E 4

I 15
char	*checkbuf __P((char *, int));
void	 error __P((int));
void	 getstring __P((char *));

int
E 15
main(argc, argv)
	int argc;
	char **argv;
{
D 2
	long rval;
E 2
I 2
	int rval;
E 2
	char c;
	int n, i, cc;

	argc--, argv++;
	if (argc > 0) {
		debug = fopen(*argv, "w");
		if (debug == 0)
			exit(1);
D 15
		(void) setbuf(debug, (char *)0);
E 15
I 15
		(void)setbuf(debug, (char *)0);
E 15
	}
I 5
D 7
	n = MAXRECSIZ;
	(void) setsockopt(0, SOL_SOCKET, SO_RCVBUF, &n, sizeof (n));
E 7
E 5
top:
	errno = 0;
	rval = 0;
	if (read(0, &c, 1) != 1)
		exit(0);
	switch (c) {

	case 'O':
		if (tape >= 0)
			(void) close(tape);
D 4
		gets(device); gets(mode);
if (debug) fprintf(debug, "rmtd: O %s %s\n", device, mode);
E 4
I 4
D 15
		getstring(device); getstring(mode);
E 15
I 15
		getstring(device);
		getstring(mode);
E 15
		DEBUG2("rmtd: O %s %s\n", device, mode);
E 4
		tape = open(device, atoi(mode));
		if (tape < 0)
			goto ioerror;
D 3
		break;
E 3
I 3
		goto respond;
E 3

	case 'C':
D 4
if (debug) fprintf(debug, "rmtd: C\n");
		gets(device);		/* discard */
E 4
I 4
		DEBUG("rmtd: C\n");
		getstring(device);		/* discard */
E 4
		if (close(tape) < 0)
			goto ioerror;
		tape = -1;
D 3
		break;
E 3
I 3
		goto respond;
E 3

	case 'L':
D 4
		gets(count); gets(pos);
if (debug) fprintf(debug, "rmtd: L %s %s\n", count, pos);
E 4
I 4
D 15
		getstring(count); getstring(pos);
E 15
I 15
		getstring(count);
		getstring(pos);
E 15
		DEBUG2("rmtd: L %s %s\n", count, pos);
E 4
D 15
		rval = lseek(tape, (long) atoi(count), atoi(pos));
E 15
I 15
D 16
		rval = lseek(tape, atol(count), atoi(pos));
E 16
I 16
		rval = lseek(tape, (off_t)atol(count), atoi(pos));
E 16
E 15
		if (rval < 0)
			goto ioerror;
D 3
		break;
E 3
I 3
		goto respond;
E 3

	case 'W':
D 4
		gets(count);
E 4
I 4
		getstring(count);
E 4
		n = atoi(count);
D 4
if (debug) fprintf(debug, "rmtd: W %s\n", count);
E 4
I 4
		DEBUG1("rmtd: W %s\n", count);
I 7
		record = checkbuf(record, n);
E 7
E 4
		for (i = 0; i < n; i += cc) {
			cc = read(0, &record[i], n - i);
			if (cc <= 0) {
D 4
if (debug) fprintf(debug, "rmtd: premature eof\n");
E 4
I 4
				DEBUG("rmtd: premature eof\n");
E 4
D 7
				exit(1);
E 7
I 7
				exit(2);
E 7
			}
		}
		rval = write(tape, record, n);
		if (rval < 0)
			goto ioerror;
D 3
		break;
E 3
I 3
		goto respond;
E 3

	case 'R':
D 4
		gets(count);
if (debug) fprintf(debug, "rmtd: R %s\n", count);
E 4
I 4
		getstring(count);
		DEBUG1("rmtd: R %s\n", count);
E 4
		n = atoi(count);
D 7
		if (n > sizeof (record))
			n = sizeof (record);
E 7
I 7
		record = checkbuf(record, n);
E 7
		rval = read(tape, record, n);
		if (rval < 0)
			goto ioerror;
D 3
		(void) write(1, record, n);
		break;
E 3
I 3
D 15
		(void) sprintf(resp, "A%d\n", rval);
		(void) write(1, resp, strlen(resp));
		(void) write(1, record, rval);
E 15
I 15
		(void)sprintf(resp, "A%d\n", rval);
		(void)write(1, resp, strlen(resp));
		(void)write(1, record, rval);
E 15
		goto top;
E 3

	case 'I':
D 4
		gets(op); gets(count);
if (debug) fprintf(debug, "rmtd: I %s %s\n", op, count);
E 4
I 4
D 15
		getstring(op); getstring(count);
E 15
I 15
		getstring(op);
		getstring(count);
E 15
		DEBUG2("rmtd: I %s %s\n", op, count);
E 4
		{ struct mtop mtop;
		  mtop.mt_op = atoi(op);
		  mtop.mt_count = atoi(count);
		  if (ioctl(tape, MTIOCTOP, (char *)&mtop) < 0)
			goto ioerror;
		  rval = mtop.mt_count;
		}
D 3
		break;
E 3
I 3
		goto respond;
E 3

	case 'S':		/* status */
D 4
if (debug) fprintf(debug, "rmtd: S\n");
E 4
I 4
		DEBUG("rmtd: S\n");
E 4
		{ struct mtget mtget;
		  if (ioctl(tape, MTIOCGET, (char *)&mtget) < 0)
			goto ioerror;
		  rval = sizeof (mtget);
I 6
D 15
		  (void) sprintf(resp, "A%d\n", rval);
		  (void) write(1, resp, strlen(resp));
E 6
		  (void) write(1, (char *)&mtget, sizeof (mtget));
E 15
I 15
		  (void)sprintf(resp, "A%d\n", rval);
		  (void)write(1, resp, strlen(resp));
		  (void)write(1, (char *)&mtget, sizeof (mtget));
E 15
D 3
		  break;
E 3
I 3
D 6
		  goto respond;
E 6
I 6
		  goto top;
E 6
E 3
		}

	default:
D 4
if (debug) fprintf(debug, "rmtd: garbage command %c\n", c);
E 4
I 4
		DEBUG1("rmtd: garbage command %c\n", c);
E 4
D 7
		exit(1);
E 7
I 7
		exit(3);
E 7
	}
I 3
respond:
E 3
I 2
D 4
if (debug) fprintf(debug, "rmtd: A %d\n", rval);
E 4
I 4
	DEBUG1("rmtd: A %d\n", rval);
E 4
E 2
D 15
	(void) sprintf(resp, "A%d\n", rval);
	(void) write(1, resp, strlen(resp));
E 15
I 15
	(void)sprintf(resp, "A%d\n", rval);
	(void)write(1, resp, strlen(resp));
E 15
	goto top;
ioerror:
	error(errno);
	goto top;
}

I 15
void
E 15
D 4
gets(bp)
E 4
I 4
getstring(bp)
E 4
	char *bp;
{
	int i;
	char *cp = bp;

	for (i = 0; i < SSIZE; i++) {
		if (read(0, cp+i, 1) != 1)
			exit(0);
		if (cp[i] == '\n')
			break;
	}
	cp[i] = '\0';
}

I 7
char *
checkbuf(record, size)
	char *record;
	int size;
{
D 15
	extern char *malloc();
E 15

	if (size <= maxrecsize)
		return (record);
	if (record != 0)
		free(record);
	record = malloc(size);
	if (record == 0) {
		DEBUG("rmtd: cannot allocate buffer space\n");
		exit(4);
	}
I 10
	maxrecsize = size;
E 10
D 8
	(void) setsockopt(0, SOL_SOCKET, SO_RCVBUF, &size, sizeof (size));
E 8
I 8
	while (size > 1024 &&
	       setsockopt(0, SOL_SOCKET, SO_RCVBUF, &size, sizeof (size)) < 0)
		size -= 1024;
E 8
	return (record);
}

I 15
void
E 15
E 7
error(num)
	int num;
{

I 2
D 4
if (debug) fprintf(debug, "rmtd: E %d (%s)\n", num, sys_errlist[num]);
E 4
I 4
D 13
	DEBUG2("rmtd: E %d (%s)\n", num, sys_errlist[num]);
E 4
E 2
	(void) sprintf(resp, "E%d\n%s\n", num, sys_errlist[num]);
	(void) write(1, resp, strlen (resp));
E 13
I 13
	DEBUG2("rmtd: E %d (%s)\n", num, strerror(num));
D 15
	(void) sprintf(resp, "E%d\n%s\n", num, strerror(num));
	(void) write(1, resp, strlen(resp));
E 15
I 15
	(void)sprintf(resp, "E%d\n%s\n", num, strerror(num));
	(void)write(1, resp, strlen(resp));
E 15
E 13
}
I 2
D 7

E 7
E 2
E 1
