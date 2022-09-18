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
#include	<utmp.h>

static char	rl_ttynm[14];
static char	base_ttynm[10];
static int 	real_tty_fd;
static struct termio	ttystart;

char		*ttyname();
char		*getenv();



main(argc, argv, envp)
int argc;
char *argv[];
char *envp[];
{
	int i;
	int temp_fd;
	

	uid = getuid();
	gid = getgid();

	if ((cntl_chan_fd = open_cntl_chan()) == SYSERROR)
	{
		execsh(argv,envp);
		exit(1);
	}


	if(get_ttynm()==0)
	{
		execsh(argv,envp);
		exit(2);
	}
	if ((real_tty_fd = open(rl_ttynm, O_RDWR)) == SYSERROR)
	{
		fprintf(stderr, "real tty open failed (errno = %d)\n", errno);
		execsh(argv,envp);
		exit(3);
	}

	if (real_tty_fd < 3)	/* check if 0, 1, or 2 closed when invoked */
	{
		temp_fd = fcntl(real_tty_fd, F_DUPFD, 3);
		close(real_tty_fd);
		real_tty_fd = temp_fd;
	}
	
	ioctl(real_tty_fd, TCGETA, &ttystart);		/* save real tty settings */
	ttysave = ttystart;

	if (ttysave.c_cc[VSWTCH] == CNSWTCH)
	{
		ttysave.c_cc[VSWTCH] = CSWTCH;
		ioctl(real_tty_fd, TCSETA, &ttysave);
	}


	if (multiplex())
	{
		for (i = 0; i < 3; ++i)
		{
			close(i);
			dup(cntl_chan_fd);
		}

		if (ioctl(cntl_chan_fd, TCSETA, &ttysave) == SYSERROR)
		{
			fprintf(stderr, "virtual tty ioctl failed (errno = %d)\n", errno);
			reset();
		}
		

	}
	else
	{
		ioctl(real_tty_fd, TCSETA, &ttystart);	/* restore real tty */
	}

	execsh(argv,envp);
	
	exit(4);
}


execsh(argv,arge)
char *argv[];
char *arge[];
{
 register char *shell = getenv("SHELL");
 if(shell==NULL)
	 shell = "/bin/sh";
 close(real_tty_fd);
 setuid(getuid());
 setgid(getgid());
 execve(shell,argv,arge);
}

reset()
{
	int i;

	close(cntl_chan_fd);
	for (i = 0; i < 3; ++i)
	{
		close(i);
		dup(real_tty_fd);
	}


	ioctl(real_tty_fd, TCSETA, &ttystart);		/* restore real tty */

}


get_ttynm()
{
	char *ttynm;

	if (isatty(0)				&&
	    (ttynm = ttyname(0)) != NULL	&&
		strcmp(ttynm, ttyname(1)) == 0	&&
		strcmp(ttynm, ttyname(2)) == 0)
	{
		strcpy(rl_ttynm, ttynm);
		strcpy(base_ttynm, (strrchr(ttynm, '/') + (char *)1));

	}
	else
	{
		fprintf(stderr, "can't determine your login terminal\n");
		exit(9);
	}
}

