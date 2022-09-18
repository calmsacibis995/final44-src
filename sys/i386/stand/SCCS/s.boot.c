h29295
s 00005/00005/00130
d D 8.1 93/06/11 15:57:41 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00003/00131
d D 7.5 92/10/11 10:22:53 bostic 5 4
c make kernel includes standard
e
s 00001/00001/00133
d D 7.4 92/02/05 10:40:44 bostic 4 3
c mask out relocation bits 0xfe000000; only worked because the linker
c was broken, and -T 0xfe000000 started at 0.  From Christos Zoulas
e
s 00001/00003/00133
d D 7.3 91/05/04 15:43:15 bostic 3 2
c UNIX is defined by saio.h, jmp_buf was moved into stand/dev.c
e
s 00055/00030/00081
d D 7.2 91/04/28 16:48:28 william 2 1
c cleaned code, rewrote bootdev handoff, added opt arg for flag
e
s 00111/00000/00000
d D 7.1 90/04/24 19:56:19 william 1 0
c date and time created 90/04/24 19:56:19 by william
e
u
U
t
T
I 1
/*-
D 6
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * This code is derived from software contributed to Berkeley by
 * William Jolitz.
 *
D 2
 * %sccs.include.noredist.c%
E 2
I 2
 * %sccs.include.redist.c%
E 2
 */

#ifndef lint
D 6
char copyright[] =
"%Z% Copyright (c) 1990 The Regents of the University of California.\n\
 All rights reserved.\n";
E 6
I 6
static char copyright[] =
"%Z% Copyright (c) 1990, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 6
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

D 2
#include "../h/param.h"
#include "../h/inode.h"
#include "../h/fs.h"
#include "../h/dir.h"
#include "../h/reboot.h"
#include "../h/disk.h"
E 2
I 2
D 5
#include "param.h"
#include "reboot.h"
E 5
I 5
#include <sys/param.h>
#include <sys/reboot.h>

E 5
E 2
#include <a.out.h>
I 2
#include <setjmp.h>
E 2
D 5
#include "saio.h"
E 5
I 5
#include <stand/saio.h>
E 5

/*
D 2
 * Boot program... arguments passed in r6 and r7 determine
E 2
I 2
 * Boot program... arguments from lower-level bootstrap determine
E 2
 * whether boot stops to ask for system name and which device
 * boot comes from.
 */

D 3
#define	UNIX	"/vmunix"

E 3
char line[100] = UNIX;
D 2
char line2[100] = "/stand/";
extern	int howto, bootdev, unit, cyloffset, boottype;
extern	int opendev, openfirst;
E 2
I 2
extern	int opendev, bootdev, cyloffset;
E 2
int	retry = 0;
I 2
D 3
jmp_buf  exception;
E 3
I 3
extern jmp_buf  exception;
E 3
E 2

D 2
main()
E 2
I 2
main(howto, dev, off)
E 2
{
	int io;

D 2
howto = RB_SINGLE|RB_ASKNAME;
E 2
I 2
	if((dev&B_MAGICMASK) == B_DEVMAGIC) {
		bootdev = dev;
		cyloffset = off;
	} else	goto again;

	if(_setjmp(exception)) {
		close(io);
		printf("- load aborted\n");
again:
		howto = RB_SINGLE|RB_ASKNAME;
		cyloffset = 0; 
	}
		
E 2
	for (;;) {
		if (howto & RB_ASKNAME) {
I 2
			char *cp;

E 2
			printf("Boot: ");
			gets(line);
I 2

			/* process additional flags if any */
			if(cp = (char *)index(line, ' ')) {
				howto = strtol (cp, 0, 0);
				*cp = '\0';
			}
			cyloffset = 0;
E 2
		} else
			printf("Boot: %s\n", line);
I 2

E 2
		if (line[0] == 0) {
			strcpy(line, UNIX);
			printf("Boot: %s\n", line);
		}

		io = open(line, 0);
D 2
		/*if (io < 0) {
			strcat(line2,line) ;
			io = open(line2, 0);
		}*/
E 2
		if (io >= 0) {
D 2
			bootdev = opendev;
			copyunix(io);
		}
		openfirst = 1;
		if (++retry > 2)
			howto = RB_SINGLE|RB_ASKNAME;
E 2
I 2
			copyunix(io, howto);
			goto again;
		} else if (++retry > 2)
			goto again;
E 2
	}
}

/*ARGSUSED*/
D 2
copyunix(io)
E 2
I 2
copyunix(io, howto)
E 2
	register io;
{
	struct exec x;
	int i;
D 2
	char *addr;
E 2
I 2
	char *addr,c;
E 2

	i = read(io, (char *)&x, sizeof x);
	if (i != sizeof x ||
D 2
	    (x.a_magic != 0407 && x.a_magic != 0413 && x.a_magic != 0410))
		_stop("Bad format\n");
E 2
I 2
	    (x.a_magic != 0407 && x.a_magic != 0413 && x.a_magic != 0410)) {
		printf("Bad format\n");
		return;
	}

E 2
	printf("%d", x.a_text);
	if (x.a_magic == 0413 && lseek(io, 0x400, 0) == -1)
		goto shread;
	if (read(io, (char *)0, x.a_text) != x.a_text)
		goto shread;
I 2

E 2
	addr = (char *)x.a_text;
	if (x.a_magic == 0413 || x.a_magic == 0410)
		while ((int)addr & CLOFSET)
			*addr++ = 0;
	printf("+%d", x.a_data);
	if (read(io, addr, x.a_data) != x.a_data)
		goto shread;
I 2

E 2
	addr += x.a_data;
	printf("+%d", x.a_bss);
	x.a_bss += 128*512;	/* slop */
	for (i = 0; i < x.a_bss; i++)
		*addr++ = 0;
I 2

	/* mask high order bits corresponding to relocated system base */
D 4
	x.a_entry &= 0xfff00000;
E 4
I 4
	x.a_entry &= 0x000fffff;
E 4
E 2
	printf(" start 0x%x\n", x.a_entry);
D 2
	setregs() ;
	i = (*((int (*)()) x.a_entry))();
E 2
I 2

	if(c=scankbd())
		_longjmp(&exception,1);

	i = (*((int (*)()) x.a_entry))(howto, opendev, 0, cyloffset);

E 2
	if (i) printf("exit %d\n", i) ; 
	return;
shread:
D 2
	_stop("Short read\n");
E 2
I 2
	printf("Short read\n");
	return;
E 2
}
E 1
