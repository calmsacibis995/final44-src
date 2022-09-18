h23682
s 00004/00005/00111
d D 6.2 86/02/20 14:57:52 sklower 2 1
c Fix defective copyright notices.
e
s 00116/00000/00000
d D 6.1 86/02/14 20:13:17 sklower 1 0
c Program to retrieve core image from board
e
u
U
t
T
I 1
/*
D 2
 * Copyright (c) 1986 MICOM-Interlan, Inc., Foxborough Mass.
E 2
I 2
 * Copyright (c) 1986 MICOM-Interlan, Inc., Boxborough Mass.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 2
 *
D 2
 * This software is furnished under a license and may only be used
 * or copied in accordance with the terms of that license.
 *
E 2
 */
#ifndef lint
char copyright[] =
D 2
"%Z% Copyright (c) 1986 MICOM-Interlan, Inc., Foxborough Mass.\n\
E 2
I 2
"%Z% Copyright (c) 1986 MICOM-Interlan, Inc., Boxborough Mass.\n\
E 2
 All rights reserved.\n";
#endif not lint

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif not lint

#include <stdio.h>
#include <fcntl.h>
#include "npcmd.h"
#include <sys/ioctl.h>

extern int errno;

main(argc,argv)
int argc;
char **argv;
{

	int	ret;
	int	ed;
	int	fd;
	int	nbyte;
	char	*fname;
	char	ibuf[1024];
	char	obuf[1024];
	long	stadd = 0x400;
	char	*devname = "/dev/np00";

	switch (argc) {
	case 3:
		/* Pathname for device to be loaded */
		devname = argv[2];
	case 2:
		/* Name of the image file to be loaded */
		fname = argv[1];
		break;
	default:
		printf("usage: npload imagefile [device]\n");
		exit(1);
	}
	/* Open the device to be loaded */

	if((ed = open(devname,O_RDWR)) == -1) {
		char fullpath[50];
		(void) sprintf(fullpath, "/dev/%s", devname);
		if((ed = open(devname,O_RDWR)) == -1) {
			fprintf(stderr,
				"%s unable to open device %s errno = %d\n",
				argv[0], devname, errno);
			exit(2);
		}
	}
	
	/* Open the image file */

	if((fd = open(fname,O_RDONLY)) == -1) {
		fprintf(stderr,"%s: unable to open file %s errno = %d\n",
		    argv[0],fname,errno);
		exit(3);
	}

	/* Reset the specified device */

	if(ioctl(ed,NPRESET | IOC_VOID,&stadd) == -1) {
		fprintf(stderr,"unable to reset %s errno = %d\n",devname,errno);
		exit(4);
	}

	/* Seek to address 400 on the device */

	if(lseek(ed,(long)0x400,0) == -1) {
		fprintf(stderr,"seek failed on %s errno = %d.\n",devname,errno);
		exit(5);	
	}

	/* Seek to address 400 on the image file */

	if(lseek(fd,(long)0x400,0) == -1) {
		fprintf(stderr,"seek failed on %s errno = %d.\n",fname,errno);
		exit(6);	
	}

	/* Read from the image file and write to the device */
	
	while((nbyte = read(fd,ibuf,1024)) > 0) { 
		
		if((ret = write(ed,ibuf,nbyte)) == -1) {
			fprintf(stderr,"Bad write to %s errno = %d\n",
			    argv[0],errno);
			exit(7);
		}
	}

	/* Issue a begin execution command to the device */

	if(ioctl(ed,NPSTART | IOC_VOID,&stadd) == -1) {
		fprintf(stderr,"Start error on %s errno = %d.\n",devname,errno);
		exit(8);
	}

	close(fd);
	close(ed);

	exit(0);
}
E 1
