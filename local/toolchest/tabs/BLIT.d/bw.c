/*

 *      Copyright (c) 1984, 1985 AT&T
 *      All Rights Reserved

 *      THIS IS UNPUBLISHED PROPRIETARY SOURCE 
 *      CODE OF AT&T.
 *      The copyright notice above does not 
 *      evidence any actual or intended
 *      publication of such source code.

 */
/*
 * discover Blit window size for vi
 */
#include <sys/ioctl.h>
#include "/usr/jerq/include/jioctl.h"
struct winsize j;

main()
{
	if (ioctl(0, JWINSIZE, &j) == -1)
		printf("?\n");
	else
		printf("COLUMNS=%d\nLINES=%d\n", j.bytesx, j.bytesy);
}
