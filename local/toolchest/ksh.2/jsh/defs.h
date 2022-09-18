/*

 *      Copyright (c) 1984, 1985, 1986 AT&T
 *      All Rights Reserved

 *      THIS IS UNPUBLISHED PROPRIETARY SOURCE 
 *      CODE OF AT&T.
 *      The copyright notice above does not 
 *      evidence any actual or intended
 *      publication of such source code.

 */
/* %W% */
#include	<sys/types.h>
#include	<sys/tty.h>
#include	<sys/errno.h>
#include	<signal.h>
#include	<sys/termio.h>
#include	<sys/sxt.h>
#include	<fcntl.h>
#include	<stdio.h>

#define		SYSERROR	-1
#define		MAX_LAYERS	MAXPCHAN
#define		set_dev(x)	sprintf(&cntlf[9], "%03d", conv(x))


extern int	 	chan;
extern int 		max_index;

extern char 		cntlf[];
extern int  		cntl_chan_fd;

extern int		errno;
extern int		sys_nerr;
extern char		*sys_errlist[];

extern struct termio	ttysave;

extern int		uid;
extern int		gid;

char 			*strcpy();
int			hangup();
int			child_death();



