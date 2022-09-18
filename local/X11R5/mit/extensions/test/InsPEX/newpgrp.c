/* $XConsortium: newpgrp.c,v 5.1 91/02/16 10:04:51 rws Exp $ */

/*****************************************************************
Copyright (c) 1989,1990, 1991 by Sun Microsystems, Inc. and the X Consortium.

                        All Rights Reserved

Permission to use, copy, modify, and distribute this software and its 
documentation for any purpose and without fee is hereby granted, 
provided that the above copyright notice appear in all copies and that
both that copyright notice and this permission notice appear in 
supporting documentation, and that the names of Sun Microsystems,
the X Consortium, and MIT not be used in advertising or publicity 
pertaining to distribution of the software without specific, written 
prior permission.  

SUN MICROSYSTEMS DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, 
INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT 
SHALL SUN MICROSYSTEMS BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL 
DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
SOFTWARE.

******************************************************************/

/*
 * newprgp:  disassociate current process from process group and 
 *	     control terminal; execute the rest of the command line 
 * 	     as a command
 */

#include "signal.h"

#ifdef SIGTSTP /* BSD */
#include "sys/file.h"
#include "sys/ioctl.h"
#endif

main(argc,argv)
	int argc;
	char **argv;
{
	int i;
	char command[1024];
	char *charptr;
	int fd;

	/* ignore terminal stop signals (BSD) */
#ifdef SIGTOU
	signal(SIGTOU, SIG_IGN);
#endif 
#ifdef SIGTTIN
	signal(SIGTTIN, SIG_IGN);
#endif 
#ifdef SIGTSTP
	signal(SIGTSTP, SIG_IGN);
#endif 

	/* to make sure the first child is not the process group leader */
	if (fork() != 0)
		exit(0);  /* parent */

#ifdef SIGTSTP /* BSD */
	/* disassociate from process group */
	setpgrp(0,getpid());

	/* disassociate from control terminal */
	fd = open("/dev/tty",O_RDWR);
        if (fd >=0) {
                ioctl(fd, TIOCNOTTY, (char*)0);
                close(fd);
        }

#else 	       /* SYS 5 */
	/* disassociate from process group and */
 	/* control terminal (as a side effect) */
	setpgrp();
	/* to immune from pgrp leader death */
	signal(SIGHUP, SIG_IGN);
	/* first child exit so that the living process will not be a */
 	/* process group leader */
	if (fork() != 0)
		exit(0);
#endif

	/* assemble command line */
	for (charptr=command, i=1;
			i<argc;
			++i, charptr+=strlen(argv[i-1])+1)
		sprintf(charptr," %s",argv[i]);

	/* execute command line */
	system(command);
}
