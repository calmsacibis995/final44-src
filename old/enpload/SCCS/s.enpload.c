h04740
s 00003/00004/00132
d D 5.4 91/01/14 17:20:09 bostic 6 5
c kernel reorg
e
s 00001/00011/00135
d D 5.3 90/06/01 16:15:46 bostic 5 4
c new copyright notice
e
s 00028/00002/00118
d D 5.2 88/09/18 12:26:22 bostic 4 1
c appropriate copyright
e
s 00003/00001/00133
d R 5.3 87/06/03 00:22:48 bostic 3 2
c tahoe specific chagnes
e
s 00014/00000/00120
d R 5.2 87/05/30 16:15:36 bostic 2 1
c enpload is a tahoe specific program
e
s 00120/00000/00000
d D 5.1 87/04/29 20:37:26 sam 1 0
c date and time created 87/04/29 20:37:26 by sam
e
u
U
t
T
I 4
/*
 * Copyright (c) 1988 The Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Computer Consoles Inc.
 *
D 5
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
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 5
I 5
 * %sccs.include.redist.c%
E 5
 */

E 4
I 1
#ifndef lint
D 4
static char sccsid[] = "%W% (Berkeley from CCI) %G%";
#endif
E 4
I 4
char copyright[] =
"%Z% Copyright (c) 1988 The Regents of the University of California.\n\
 All rights reserved.\n";
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 4

/*
 * CMC Ethernet ``Microcode'' Loader.
 */
D 6
#include <stdio.h>
#include <a.out.h>

E 6
#include <sys/types.h>
#include <sys/file.h>
#include <sys/ioctl.h>
D 6
#include <tahoeif/if_enpreg.h>
E 6
I 6
#include <tahoe/if/if_enpreg.h>
#include <stdio.h>
#include <a.out.h>
E 6

char	*dev;

main(argc, argv)
	int argc;
	char *argv[];
{
	int enp = -1, fd, first = 1, nostart = 0;

	argc--, argv++;
	if (argc > 0) {
		enp = open(dev = argv[0], O_RDWR);
		if (enp < 0) {
			fprintf(stderr, "enpload: ");
			perror(dev);
			exit(-1);
		}
		argc--, argv++;
	}
	for (; argc > 0; argc--, argv++) {
		if (strcmp(argv[0], "-s") == 0 || strcmp(argv[0], "-S") == 0) {
			nostart++;
			continue;
		}
		if (first) {
			/*
			 * Reset device before first file is loaded.
			 */
			if (ioctl(enp, ENPIORESET) < 0) {
				fprintf(stderr, "enpload: %s: ", dev);
				perror("ioctl (ENPIORESET)");
				exit(-1);
			}
			first = !first;
		}
		if ((fd = open(argv[0], O_RDONLY)) < 0) {
			fprintf(stderr, "enpload: "), perror(argv[0]);
			exit(1);
		}
		enpload(enp, fd, argv[0]);
		close(fd);
	}
	if (enp != -1 && !nostart && ioctl(enp, ENPIOGO) < 0) {
		fprintf(stderr, "enpload: ");
		perror("ioctl (ENPIOGO)");
		exit(-1);
	}
	exit(0);
}

#define	RELO		0x03FFFF	/* relocation offset */
#define	ENPMSTART	0x0		/* start of memory */
#define	BSIZE		512		/* buffer size */
char	buff[BSIZE];
char	zbuf[BSIZE];

enpload(enp, fd, filename)
	int enp, fd;
	char *filename;
{
	int cnt, size, lstart;
	struct exec hdr;

	if (read(fd, &hdr, sizeof (hdr)) != sizeof (hdr)) {
		fprintf(stderr, "enpload: %s: Read short (header).\n",
		   filename);
		exit(1);
	}
	if (N_BADMAG(hdr)) {
		fprintf(stderr, "enpload: %s: Bad magic number.\n", filename);
		exit(1);
	}
	size = hdr.a_text + hdr.a_data;
	lstart = (ENPMSTART + (hdr.a_entry & RELO)) - 0x1000;

	printf("%s: Loading %s...", dev, filename);
	(void) lseek(enp, lstart + size, L_SET);
	while (hdr.a_bss >= BSIZE) {
		if (write(enp, zbuf, BSIZE) != BSIZE) {
			fprintf(stderr, "enpload: Bss write error.\n");
			exit(-1);
		}
		hdr.a_bss -= BSIZE;
	}
	if (hdr.a_bss > 0 && write(enp, zbuf, hdr.a_bss) != hdr.a_bss) {
		fprintf(stderr, "enpload: Bss write error.\n");
		exit(-1);
	}
	(void) lseek(enp, lstart, L_SET);
	while (size > BSIZE) {
		cnt = read(fd, buff, BSIZE);
		size -= cnt;
		if (write(enp, buff, cnt) != cnt) {
			fprintf(stderr, "enpload: Write error.\n");
			exit(-1);
		}
	}
	if (size > 0) {
		cnt = read(fd, buff, size);
		if (write(enp, buff, cnt) != cnt) {
			fprintf(stderr, "enpload: Write error.\n");
			exit(-1);
		}
	}
	printf("done.\n");
}
E 1
