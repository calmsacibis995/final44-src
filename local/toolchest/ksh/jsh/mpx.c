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

open_cntl_chan()
{
	register int fd;
	register char p;

	while ((fd = open(cntlf, O_RDWR | O_EXCL)) == SYSERROR)
	{
#ifdef xxx
		if (errno == EBUSY)
#endif
		{
			chan += MAX_LAYERS;
			set_dev(chan);
		}
#ifdef xxx
		else
		{
			fprintf(stderr, "no control channels available (errno=%d)\n", errno);
			return(SYSERROR);
		}
#endif
	}


	{	register int j;

		for (j=0; j < MAX_LAYERS; ++j)
		{
			set_dev(chan + j);
			if (chown(cntlf, uid, gid) != SYSERROR)
			{
				chmod(cntlf, 0622);
			}
			else
			{
				fprintf(stderr, "chown on %s failed (errno = %d)\n", cntlf, errno);
				close(fd);
				return(SYSERROR);
			}
		}

	}

	return(fd);
}

multiplex()
{

	if (ioctl(cntl_chan_fd, SXTIOCLINK, MAX_LAYERS) == SYSERROR)
	{
		switch (errno)
		{
			case ENXIO:
				fprintf(stderr, "sxt driver not configured\n");
				break;

			case ENOMEM:
				fprintf(stderr, "no memory for kernel configuration");
				break;

			default:
				fprintf(stderr, "multiplex failed (errno = %d)\n", errno);
fprintf(stderr, " sxt=%s\n",cntlf);
		}

		return(0);
	}

	return(1);
}

conv(n)
int n;
{
	int i;
	int j;

	i = n / MAX_LAYERS;
	j = n % MAX_LAYERS;

	return((i * 10) + j);
}

