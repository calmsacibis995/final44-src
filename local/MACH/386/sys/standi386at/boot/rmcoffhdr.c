/* 
 * Mach Operating System
 * Copyright (c) 1990 Carnegie-Mellon University
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	rmcoffhdr.c,v $
 * Revision 2.1.1.1  90/02/09  17:27:25  rvb
 * 	Add Intel copyright
 * 	[90/02/09            rvb]
 * 
 */
/*
 * 			INTEL CORPORATION PROPRIETARY INFORMATION
 *
 *	This software is supplied under the terms of a license  agreement or 
 *	nondisclosure agreement with Intel Corporation and may not be copied 
 *	nor disclosed except in accordance with the terms of that agreement.
 *
 *	Copyright 1988 Intel Corporation
 * Copyright 1988, 1989 by Intel Corporation
 */

#include "coff.h"

struct headers {
	struct filehdr mainhdr ;
	struct aouthdr secondhdr ;
	} head ;

char buf[1024] ;

main(argc, argv)
char **argv ;
{
	int ifd, ofd, count;
	long offset;

	if ((ifd = open(argv[1], 0)) == -1) {
		printf ("rmcoffhdr: can't open %s\n", argv[1]);
		exit(1) ;
	}

	if ((ofd = open(argv[2], 01002, 0777)) == -1) {
		printf ("rmcoffhdr: can't create %s\n", argv[2]);
		exit(2) ;
	}

	read(ifd, &head, sizeof(struct headers));

	offset = head.mainhdr.f_nscns * sizeof(struct scnhdr);

	lseek (ifd, offset, 1) ;

	while ((count = read(ifd, buf, 1024)) != 0)
		write(ofd, buf, count);

	close(ifd);

	close(ofd);
	 
}
