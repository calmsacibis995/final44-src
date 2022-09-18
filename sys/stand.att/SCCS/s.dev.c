h46258
s 00002/00002/00130
d D 8.1 93/06/11 16:01:38 bostic 17 16
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00131
d D 7.16 93/05/24 22:44:03 mckusick 16 15
c new include location
e
s 00001/00001/00131
d D 7.15 92/10/11 10:01:02 bostic 15 14
c make kernel includes standard
e
s 00008/00000/00124
d D 7.14 91/05/05 16:20:46 bostic 14 13
c SMALL changes for the 386
e
s 00003/00002/00121
d D 7.13 91/05/05 14:28:37 bostic 13 12
c fix includes, nodev() should not return 0
e
s 00002/00002/00121
d D 7.12 91/05/04 16:46:24 bostic 12 11
c typo...
e
s 00014/00007/00109
d D 7.11 91/05/04 15:41:09 bostic 11 10
c WRITE -> F_WRITE, add kbd interrupt code
e
s 00001/00001/00115
d D 7.10 91/05/03 12:10:25 bostic 10 9
c remove READ #define
e
s 00001/00001/00115
d D 7.9 90/12/16 16:40:31 bostic 9 8
c kernel reorg
e
s 00001/00011/00115
d D 7.8 90/06/28 21:56:13 bostic 8 7
c new copyright notice
e
s 00000/00002/00126
d D 7.7 90/04/04 16:13:39 mckusick 7 6
c do not need includes
e
s 00007/00009/00121
d D 7.6 90/03/15 20:06:42 mckusick 6 5
c update to use dinode.h instead of inode.h
e
s 00005/00003/00125
d D 7.5 90/03/15 19:54:18 root 5 4
c update location of include files
e
s 00010/00005/00118
d D 7.4 88/06/29 18:19:11 bostic 4 3
c install approved copyright notice
e
s 00009/00004/00114
d D 7.3 88/05/27 15:27:23 karels 3 2
c additions to error repertoire
e
s 00036/00001/00082
d D 7.2 88/03/04 17:24:18 bostic 2 1
c print out open errors here, not in the drivers
e
s 00083/00000/00000
d D 7.1 88/02/20 13:49:32 bostic 1 0
c split out machine independent stuff from vaxstand/conf.c
e
u
U
t
T
I 1
/*
D 17
 * Copyright (c) 1982, 1986, 1988 Regents of the University of California.
 * All rights reserved.
E 17
I 17
 * Copyright (c) 1982, 1986, 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 17
 *
D 8
 * Redistribution and use in source and binary forms are permitted
D 4
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 4
I 4
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
E 8
I 8
 * %sccs.include.redist.c%
E 8
E 4
 *
 *	%W% (Berkeley) %G%
 */

D 5
#include "param.h"
#include "inode.h"
#include "fs.h"
E 5
I 5
D 13
#include "sys/param.h"
D 6
#include "sys/time.h"
#include "sys/vnode.h"
E 6
D 7
#include "ufs/inode.h"
#include "ufs/fs.h"
E 7
E 5
D 9
#include "saio.h"
E 9
I 9
#include "stand/saio.h"			/* used from machine/stand dir */
E 13
I 13
#include <sys/param.h>
E 13
I 11
#include <setjmp.h>
I 13
D 15
#include "saio.h"
E 15
I 15
D 16
#include <stand/saio.h>
E 16
I 16
#include <stand.att/saio.h>
E 16
E 15
E 13
E 11
E 9

I 2
/*
D 6
 * NB: the value "io->i_ino.i_dev", used to offset the devsw[] array
E 6
I 6
D 11
 * NB: the value "io->i_dev", used to offset the devsw[] array
E 6
 * in the routines below, is munged by the vaxstand Makefile to work
 * for certain boots.
E 11
I 11
 * NB: the value "io->i_dev", used to offset the devsw[] array in the
 * routines below, is munged by the machine specific stand Makefiles
 * to work for certain boots.
E 11
 */

I 11
jmp_buf exception;

E 11
E 2
devread(io)
	register struct iob *io;
{
	int cc;

	io->i_flgs |= F_RDDATA;
	io->i_error = 0;
D 6
	cc = (*devsw[io->i_ino.i_dev].dv_strategy)(io, READ);
E 6
I 6
D 10
	cc = (*devsw[io->i_dev].dv_strategy)(io, READ);
E 10
I 10
	cc = (*devsw[io->i_dev].dv_strategy)(io, F_READ);
E 10
E 6
	io->i_flgs &= ~F_TYPEMASK;
I 14
#ifndef SMALL
E 14
I 11
	if (scankbd())
D 12
		_longjmp(&exception, 1);
E 12
I 12
		_longjmp(exception, 1);
I 14
#endif
E 14
E 12
E 11
	return (cc);
}

devwrite(io)
	register struct iob *io;
{
	int cc;

	io->i_flgs |= F_WRDATA;
	io->i_error = 0;
D 6
	cc = (*devsw[io->i_ino.i_dev].dv_strategy)(io, WRITE);
E 6
I 6
D 11
	cc = (*devsw[io->i_dev].dv_strategy)(io, WRITE);
E 11
I 11
	cc = (*devsw[io->i_dev].dv_strategy)(io, F_WRITE);
E 11
E 6
	io->i_flgs &= ~F_TYPEMASK;
I 14
#ifndef SMALL
E 14
I 11
	if (scankbd())
D 12
		_longjmp(&exception, 1);
E 12
I 12
		_longjmp(exception, 1);
I 14
#endif
E 14
E 12
E 11
	return (cc);
}

devopen(io)
	register struct iob *io;
{
D 2
	return (*devsw[io->i_ino.i_dev].dv_open)(io);
E 2
I 2
	int ret;

D 6
	if (!(ret = (*devsw[io->i_ino.i_dev].dv_open)(io)))
E 6
I 6
	if (!(ret = (*devsw[io->i_dev].dv_open)(io)))
E 6
		return (0);
I 14
#ifdef SMALL
	printf("open error\n");
#else
E 14
D 6
	printf("%s(%d,%d,%d,%d): ", devsw[io->i_ino.i_dev].dv_name,
E 6
I 6
	printf("%s(%d,%d,%d,%d): ", devsw[io->i_dev].dv_name,
E 6
		io->i_adapt, io->i_ctlr, io->i_unit, io->i_part);
	switch(ret) {
I 3
	case EIO:
		break;		/* already reported */
E 3
	case EADAPT:
D 3
		printf("bad adaptor\n");
E 3
I 3
		printf("bad adaptor number\n");
E 3
		break;
	case ECTLR:
D 3
		printf("bad controller\n");
E 3
I 3
		printf("bad controller number\n");
E 3
		break;
	case EUNIT:
D 3
		printf("bad drive\n");
E 3
I 3
		printf("bad drive number\n");
E 3
		break;
	case EPART:
		printf("bad partition\n");
		break;
	case ERDLAB:
		printf("can't read disk label\n");
		break;
	case EUNLAB:
		printf("unlabeled\n");
		break;
	case ENXIO:
D 3
	default:
E 3
		printf("bad device specification\n");
I 3
		break;
	default:
		printf("unknown open error\n");
		break;
E 3
	}
I 14
#endif
E 14
	return (ret);
E 2
}

devclose(io)
	register struct iob *io;
{
D 6
	(*devsw[io->i_ino.i_dev].dv_close)(io);
E 6
I 6
	(*devsw[io->i_dev].dv_close)(io);
E 6
}

devioctl(io, cmd, arg)
	register struct iob *io;
	int cmd;
	caddr_t arg;
{
D 6
	return ((*devsw[io->i_ino.i_dev].dv_ioctl)(io, cmd, arg));
E 6
I 6
	return ((*devsw[io->i_dev].dv_ioctl)(io, cmd, arg));
E 6
}

D 11
/*ARGSUSED*/
E 11
I 11
/* ARGSUSED */
E 11
nullsys(io)
	struct iob *io;
{}

D 11
/*ARGSUSED*/
E 11
I 11
/* ARGSUSED */
E 11
nodev(io)
	struct iob *io;
{
	errno = EBADF;
I 13
	return(-1);
E 13
}

D 11
/*ARGSUSED*/
E 11
I 11
/* ARGSUSED */
E 11
noioctl(io, cmd, arg)
	struct iob *io;
	int cmd;
	caddr_t arg;
{
	return (ECMD);
}
E 1
