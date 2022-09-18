h20691
s 00001/00000/00215
d D 8.2 94/02/21 17:10:12 bostic 17 16
c #include <sys/time.h>; busted <unistd.h> was hiding this
e
s 00002/00002/00213
d D 8.1 93/06/04 12:06:15 bostic 16 15
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00002/00212
d D 5.13 92/10/04 12:55:19 bostic 15 14
c <sys/errno.h> -> <errno.h>
e
s 00009/00004/00205
d D 5.12 92/02/14 16:59:23 karels 14 13
c more KNF; don't bother double-checking the kernel return values
e
s 00002/00002/00207
d D 5.11 92/02/14 16:44:07 karels 13 12
c now fix the worse bug introduced in fixing the minor one
c in the previous delta
e
s 00033/00041/00176
d D 5.10 92/02/03 19:48:49 bostic 12 11
c minor cleanups to the code, KNF, one bug fix; make man pages real
e
s 00003/00001/00214
d D 5.9 91/05/20 12:07:33 bostic 11 10
c tcsetpgprp needs to take a pointer to int, not pointer to pid_t
e
s 00001/00001/00214
d D 5.8 91/05/06 14:28:55 marc 10 9
c was clearing wrong opt bits.
e
s 00002/00004/00213
d D 5.7 91/04/30 13:43:39 marc 9 8
c should be unsigned char
e
s 00093/00002/00124
d D 5.6 91/04/09 16:13:21 marc 8 7
c add the tcsendbreak, tcdrain, tcflush, and tcflow functions
e
s 00004/00004/00122
d D 5.5 91/04/02 09:53:31 bostic 7 6
c TIOCGPGRP copies an int out of the kernel
e
s 00028/00008/00098
d D 5.4 91/02/23 19:50:09 donn 6 5
c Add include files to get prototype declarations, and fix bugs found.
e
s 00009/00002/00097
d D 5.3 91/02/03 19:22:41 karels 5 4
c make cfmakeraw more raw: 8 bits, no parity, no ISTRIP
e
s 00016/00039/00083
d D 5.2 90/06/26 14:34:23 marc 4 3
c new copyright, cflag CIGNORE implements TCSASOFT
e
s 00021/00000/00101
d D 5.1 89/08/14 17:10:51 karels 3 2
c keywords, copyr and rev 5
e
s 00002/00002/00099
d D 1.2 89/08/14 17:08:24 karels 2 1
c mv iexten
e
s 00101/00000/00000
d D 1.1 88/10/07 16:35:45 marc 1 0
c date and time created 88/10/07 16:35:45 by marc
e
u
U
t
T
I 3
D 4
/*
E 4
I 4
/*-
E 4
D 16
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 16
I 16
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 16
 *
D 4
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
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 4
I 4
 * %sccs.include.redist.c%
E 4
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

E 3
I 1
#include <sys/types.h>
D 15
#include <sys/errno.h>
E 15
D 4
#include <sys/termios.h>
E 4
I 4
#include <sys/ioctl.h>
E 4
#include <sys/tty.h>
I 17
#include <sys/time.h>
E 17
I 8
D 12
#define KERNEL	/* XXX - FREAD and FWRITE was ifdef'd KERNEL*/
E 12
I 12
#define KERNEL			/* XXX - FREAD and FWRITE ifdef'd KERNEL*/
E 12
#include <sys/fcntl.h>
#undef KERNEL
E 8
I 4
D 6
#include <sys/termios.h>
E 6
I 6
D 15
#include <termios.h>
E 15
I 15

#include <errno.h>
E 15
E 6
E 4
#include <stdio.h>
I 15
#include <termios.h>
E 15
I 6
#include <unistd.h>
E 6

I 6
int
E 6
tcgetattr(fd, t)
	int fd;
	struct termios *t;
{
D 6
	extern errno;
E 6

D 12
	return(ioctl(fd, TIOCGETA, t));
E 12
I 12
	return (ioctl(fd, TIOCGETA, t));
E 12
}

I 6
int
E 6
tcsetattr(fd, opt, t)
	int fd, opt;
D 6
	struct termios *t;
E 6
I 6
	const struct termios *t;
E 6
{
D 4
	long code;
	int ret;
	extern errno;
E 4
I 4
	struct termios localterm;
E 4

D 4
	switch (opt) {
	case TCSANOW:
		code = TIOCSETA; 
		break;
	case TCSADRAIN: 
		code = TIOCSETAW; 
		break;
	case TCSADFLUSH: 
		code = TIOCSETAF; 
		break;
	case TCSANOW | TCSASOFT:
		code = TIOCSETAS; 
		break;
	case TCSADRAIN | TCSASOFT:
		code = TIOCSETAWS;
		break;
	case TCSADFLUSH | TCSASOFT:
		code = TIOCSETAFS;
		break;
	default:
		errno = EINVAL;
		return(-1);
E 4
I 4
	if (opt & TCSASOFT) {
		localterm = *t;
		localterm.c_cflag |= CIGNORE;
		t = &localterm;
D 10
		opt &= TCSASOFT;
E 10
I 10
D 12
		opt &= ~TCSASOFT;
E 12
E 10
E 4
	}
D 4
	return(ioctl(fd, code, t));
E 4
I 4
D 12
	if (opt == TCSANOW)
E 12
I 12
D 13
	switch(opt & ~TCSASOFT) {
E 13
I 13
	switch (opt & ~TCSASOFT) {
E 13
	case TCSANOW:
E 12
		return (ioctl(fd, TIOCSETA, t));
D 12
	else if (opt == TCSADRAIN)
E 12
I 12
	case TCSADRAIN:
E 12
		return (ioctl(fd, TIOCSETAW, t));
D 6
	else
		return (ioctl(fd, TIOCSETAF, t));
E 6
I 6
D 12
	return (ioctl(fd, TIOCSETAF, t));
E 12
I 12
D 13
	case TIOCSETAF:
E 13
I 13
	case TCSAFLUSH:
E 13
		return (ioctl(fd, TIOCSETAF, t));
	default:
		errno = EINVAL;
		return (-1);
	}
E 12
E 6
E 4
}

I 6
int
#if __STDC__
tcsetpgrp(int fd, pid_t pgrp)
#else
E 6
tcsetpgrp(fd, pgrp)
I 6
	int fd;
	pid_t pgrp;
#endif
E 6
{
I 11
	int s;
E 11
I 8

E 8
D 11
	return(ioctl(fd, TIOCSPGRP, &pgrp));
E 11
I 11
	s = pgrp;
D 12
	return(ioctl(fd, TIOCSPGRP, &s));
E 12
I 12
	return (ioctl(fd, TIOCSPGRP, &s));
E 12
E 11
}

I 6
pid_t
E 6
tcgetpgrp(fd)
{
D 6
	int pgrp;
E 6
I 6
D 7
	pid_t pgrp;
E 7
I 7
	int s;
E 7
E 6

D 7
	if (ioctl(fd, TIOCGPGRP, &pgrp) < 0)
		return(-1);
	return(pgrp);
E 7
I 7
	if (ioctl(fd, TIOCGPGRP, &s) < 0)
D 12
		return((pid_t)-1);
E 12
I 12
		return ((pid_t)-1);
E 12
I 8

E 8
D 12
	return((pid_t)s);
E 12
I 12
	return ((pid_t)s);
E 12
E 7
}

I 6
speed_t
E 6
cfgetospeed(t)
D 6
	struct termios *t;
E 6
I 6
	const struct termios *t;
E 6
{
I 8

E 8
D 12
	return(t->c_ospeed);
E 12
I 12
	return (t->c_ospeed);
E 12
}

I 6
speed_t
E 6
cfgetispeed(t)
D 6
	struct termios *t;
E 6
I 6
	const struct termios *t;
E 6
{
I 8

E 8
D 12
	return(t->c_ispeed);
E 12
I 12
	return (t->c_ispeed);
E 12
}

I 6
int
E 6
cfsetospeed(t, speed)
	struct termios *t;
I 6
	speed_t speed;
E 6
{
I 14

E 14
	t->c_ospeed = speed;
I 6
D 8
	return 0;
E 8
I 8
D 12

E 12
	return (0);
E 8
E 6
}

I 6
int
E 6
cfsetispeed(t, speed)
	struct termios *t;
I 6
	speed_t speed;
E 6
{
I 14

E 14
	t->c_ispeed = speed;
I 6
D 8
	return 0;
E 8
I 8
D 12

E 12
	return (0);
E 8
E 6
}

I 6
D 12
void
E 12
I 12
int
E 12
E 6
cfsetspeed(t, speed)
	struct termios *t;
I 6
	speed_t speed;
E 6
{
I 14

E 14
	t->c_ispeed = t->c_ospeed = speed;
I 12
	return (0);
E 12
I 8
D 9

	return (0)
E 9
E 8
}

I 5
/*
D 12
 * Make a pre-existing termios structure into "raw" mode:
 * character-at-a-time mode with no characters interpreted,
 * 8-bit data path.
E 12
I 12
 * Make a pre-existing termios structure into "raw" mode: character-at-a-time
 * mode with no characters interpreted, 8-bit data path.
E 12
 */
I 6
void
E 6
E 5
cfmakeraw(t)
	struct termios *t;
{
I 14

E 14
D 2
	t->c_iflag &= ~(IGNBRK|BRKINT|PARMRK|INLCR|IGNCR|ICRNL|IXON|IEXTEN);
E 2
I 2
D 5
	t->c_iflag &= ~(IGNBRK|BRKINT|PARMRK|INLCR|IGNCR|ICRNL|IXON);
E 2
	t->c_oflag &= ~(ONLCR|OXTABS);
E 5
I 5
	t->c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL|IXON);
	t->c_oflag &= ~OPOST;
E 5
D 2
	t->c_lflag &= ~(ECHO|ECHONL|ICANON|ISIG);
E 2
I 2
	t->c_lflag &= ~(ECHO|ECHONL|ICANON|ISIG|IEXTEN);
I 5
	t->c_cflag &= ~(CSIZE|PARENB);
	t->c_cflag |= CS8;
E 5
E 2
D 12
	/* set MIN/TIME */
E 12
I 12
	/* XXX set MIN/TIME */
E 12
I 8
}

tcsendbreak(fd, len)
	int fd, len;
{
	struct timeval sleepytime;

	sleepytime.tv_sec = 0;
	sleepytime.tv_usec = 400000;
	if (ioctl(fd, TIOCSBRK, 0) == -1)
		return (-1);
D 12
	select(0, 0, 0, 0, &sleepytime);
E 12
I 12
	(void)select(0, 0, 0, 0, &sleepytime);
E 12
	if (ioctl(fd, TIOCCBRK, 0) == -1)
		return (-1);
D 12

E 12
	return (0);
}

tcdrain(fd)
	int fd;
{
D 12
	if (ioctl(fd, TIOCDRAIN, 0) == -1)
		return (-1);

	return (0);
E 12
I 12
D 14
	return (ioctl(fd, TIOCDRAIN, 0) == -1 ? -1 : 0);
E 14
I 14

	return (ioctl(fd, TIOCDRAIN, 0));
E 14
E 12
}

tcflush(fd, which)
	int fd, which;
{
	int com;

	switch (which) {
	case TCIFLUSH:
		com = FREAD;
		break;
	case TCOFLUSH:
		com = FWRITE;
		break;
	case TCIOFLUSH:
		com = FREAD | FWRITE;
		break;
	default:
		errno = EINVAL;
		return (-1);
	}
D 12
	if (ioctl(fd, TIOCFLUSH, &com) == -1)
		return (-1);

	return (0);
E 12
I 12
D 14
	return (ioctl(fd, TIOCFLUSH, &com) == -1 ? -1 : 0);
E 14
I 14
	return (ioctl(fd, TIOCFLUSH, &com));
E 14
E 12
}

tcflow(fd, action)
	int fd, action;
{
I 12
	struct termios term;
	u_char c;

E 12
	switch (action) {
	case TCOOFF:
D 12
		return (ioctl(fd, TIOCSTOP, 0));
		break;
E 12
I 12
D 14
		return (ioctl(fd, TIOCSTOP, 0) == -1 ? -1 : 0);
E 14
I 14
		return (ioctl(fd, TIOCSTOP, 0));
E 14
E 12
	case TCOON:
D 12
		return (ioctl(fd, TIOCSTART, 0));
		break;
E 12
I 12
D 14
		return (ioctl(fd, TIOCSTART, 0) == -1 ? -1 : 0);
E 14
I 14
		return (ioctl(fd, TIOCSTART, 0));
E 14
	case TCION:
E 12
	case TCIOFF:
D 12
	case TCION: {		/* these posix functions are STUPID */
		struct termios term;
D 9
		char c;
E 9
I 9
		unsigned char c;
E 9

E 12
D 9
		if (tcgetattr(fd, &term) == -1);
E 9
I 9
		if (tcgetattr(fd, &term) == -1)
E 9
			return (-1);
		c = term.c_cc[action == TCIOFF ? VSTOP : VSTART];
D 12
		if (c != _POSIX_VDISABLE && write(fd, &c, 1) == -1)
E 12
I 12
		if (c != _POSIX_VDISABLE && write(fd, &c, sizeof(c)) == -1)
E 12
			return (-1);
D 12
		break;
	}
E 12
I 12
		return (0);
E 12
	default:
		errno = EINVAL;
		return (-1);
	}
D 12

	return (0);
E 12
I 12
	/* NOTREACHED */
E 12
E 8
}
E 1
