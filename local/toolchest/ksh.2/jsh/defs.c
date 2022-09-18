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

#include	"defs.h"


int max_index = 0;
int chan = 000;
	
char cntlf[]	= "/dev/sxt/000";
int	cntl_chan_fd;
	
struct termio ttysave;

int uid;
int gid;

