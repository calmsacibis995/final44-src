h03495
s 00001/00001/00148
d D 8.2 93/08/15 13:17:03 mckusick 8 7
c final update from Akito Fujita
e
s 00002/00002/00147
d D 8.1 93/06/10 22:29:25 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00148
d D 7.6 93/02/10 15:50:53 akito 6 5
c local version update
e
s 00001/00001/00148
d D 7.5 93/02/09 18:16:57 akito 5 4
c local verison update
e
s 00018/00010/00131
d D 7.4 93/01/20 09:15:05 akito 4 3
c added restoring number of planes
e
s 00002/00003/00139
d D 7.3 93/01/18 19:13:06 akito 3 2
c save DIPSW setup
e
s 00001/00001/00141
d D 7.2 93/01/12 10:57:59 akito 2 1
c local version update
e
s 00142/00000/00000
d D 7.1 92/12/13 03:50:14 akito 1 0
c date and time created 92/12/13 03:50:14 by akito
e
u
U
t
T
I 1
/*
 * Copyright (c) 1992 OMRON Corporation.
D 7
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
 * This code is derived from software contributed to Berkeley by
 * OMRON Corporation.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

#include <sys/param.h>
#include <sys/systm.h>
#include <machine/cpu.h>
#include <machine/stinger.h>
#include <luna68k/stand/romvec.h>
#include <luna68k/stand/status.h>

extern int cpuspeed;
extern int dipsw1, dipsw2;

extern char default_file[];

D 2
#define	VERS_LOCAL	"Phase-25"
E 2
I 2
D 3
#define	VERS_LOCAL	"Phase-26"
E 3
I 3
D 4
#define	VERS_LOCAL	"Phase-27"
E 4
I 4
D 5
#define	VERS_LOCAL	"Phase-28"
E 5
I 5
D 6
#define	VERS_LOCAL	"Phase-29"
E 6
I 6
D 8
#define	VERS_LOCAL	"Phase-30"
E 8
I 8
#define	VERS_LOCAL	"Phase-31"
E 8
E 6
E 5
E 4
E 3
E 2

extern int howto;
extern int devtype;
I 4
       int nplane;
E 4

/* KIFF */

D 4

E 4
struct KernInter  KIFF;
struct KernInter *kiff = &KIFF;

/* for command parser */

#define BUFFSIZE 100
#define MAXARGS  30

char buffer[BUFFSIZE];

int   argc;
char *argv[MAXARGS];

char  prompt[16];

main()
{
	int i, status;
	int *p;

	/*
	 * Initialize the console before we print anything out.
	 */
	cpuspeed = MHZ_25;				/* for DELAY() macro */

I 4
	nplane   = get_plane_numbers();

E 4
	cninit();

	printf("\n\nStinger ver 0.0 [%s]\n\n", VERS_LOCAL);

	kiff->maxaddr = (caddr_t) (ROM_memsize -1);
D 3
	kiff->argc = 0;
	kiff->argv = (char **) 0;
E 3
I 3
	kiff->dipsw   = ~((dipsw2 << 8) | dipsw1) & 0xFFFF;
I 4
	kiff->plane   = nplane;
E 4
E 3

	i = (int) kiff->maxaddr + 1;
	printf("Physical Memory = 0x%x  ", i);
	i >>= 20;
	printf("(%d MB)\n", i);
	printf("\n");

	bcopy(VERS_LOCAL, prompt, sizeof(VERS_LOCAL));
	prompt[sizeof(VERS_LOCAL) - 1]	= '>';
	prompt[sizeof(VERS_LOCAL)]	= ' ';
	prompt[sizeof(VERS_LOCAL) + 1]	= 0;

	/*
	 * IO configuration
	 */

	find_devs();
	configure();
	printf("\n");

	howto = reorder_dipsw(dipsw2);

	if ((howto & 0xFE) == 0) {
		printf("auto-boot %s\n", default_file);
		
		i = open(default_file, 0);
		if (i >= 0) {
			bootunix(howto, devtype, i);
			close(i);
		}
	}

	/*
	 * Main Loop
	 */

	do {
		bzero(buffer, BUFFSIZE);
		if (getline(prompt, buffer) > 0) {
			argc = getargs(buffer, argv, sizeof(argv)/sizeof(char *));

			status = parse(argc, argv);
			if (status == ST_NOTFOUND)
				printf("Command \"%s\" is not found !!\n", argv[0]);
		}
	} while(status != ST_EXIT);

	exit();
}

int
I 4
get_plane_numbers()
{
	register int r = ROM_plane;
	register int n = 0;

	for (; r ; r >>= 1)
		if (r & 0x1)
			n++;

	return(n);
}

int
E 4
reorder_dipsw(dipsw)
	int dipsw;
{
	int i, sw = 0;

	for (i = 0; i < 8; i++) {
		if ((dipsw & 0x01) == 0)
			sw += 1;

		if (i == 7)
			break;

		sw <<= 1;
		dipsw >>= 1;
	}

	return(sw);
}
D 4

/*
int
exit()
{
	ROM_abort();
}
*/
E 4
E 1
