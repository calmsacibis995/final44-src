h38452
s 00002/00002/00118
d D 8.1 93/06/10 23:31:11 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00001/00115
d D 7.9 93/05/09 18:05:26 ralph 9 8
c pass the PROM entry point vector to the loaded program.
e
s 00004/00026/00112
d D 7.8 93/04/05 21:45:16 ralph 8 7
c make boot work for either 3100 or 5000 and still fit in 15 sectors.
e
s 00005/00012/00133
d D 7.7 93/03/27 16:43:57 ralph 7 6
c remove printf's so boot prog will fit into 15 sectors.
e
s 00002/00002/00143
d D 7.6 93/02/15 11:22:39 ralph 6 5
c use old DS3100 style entry point for SCSI disk I/O
e
s 00037/00029/00108
d D 7.5 92/10/24 14:26:48 ralph 5 4
c new libsa version
e
s 00004/00004/00133
d D 7.4 92/10/11 11:28:15 bostic 4 3
c make kernel includes standard
e
s 00000/00001/00137
d D 7.3 92/03/15 19:10:26 ralph 3 2
c remove debug printf
e
s 00016/00008/00122
d D 7.2 92/03/01 10:17:45 ralph 2 1
c checked in for Ralph by TK; update for 5000, not sure this works
e
s 00130/00000/00000
d D 7.1 92/01/07 20:45:18 mckusick 1 0
c contributed by Ralph Campbell
e
u
U
t
T
I 1
/*
D 10
 * Copyright (c) 1992 Regents of the University of California.
 * All rights reserved.
E 10
I 10
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 10
 *
 * This code is derived from software contributed to Berkeley by
 * Ralph Campbell.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

I 2
D 4
#include "param.h"
E 2
#include "reboot.h"
#include "exec.h"
E 4
I 4
#include <sys/param.h>
D 5
#include <sys/reboot.h>
E 5
#include <sys/exec.h>
I 9
#include <pmax/stand/dec_prom.h>
E 9
E 4

D 5
#ifndef TEST
#define DEF_MONFUNCS
D 4
#include "../include/machMon.h"
E 4
I 4
#include <machine/machMon.h>
E 4
#endif

E 5
char	line[1024];

/*
 * This gets arguments from the PROM, calls other routines to open
 * and load the program to boot, and then transfers execution to that
 * new program.
D 2
 * Argv[0] should be something like "rz(0,0,0)vmunix"
 * The argument "-a" means we were invoked by the 'auto' command from the prom.
E 2
I 2
 * Argv[0] should be something like "rz(0,0,0)vmunix" on a DECstation 3100.
 * Argv[0,1] should be something like "boot 5/rz0/vmunix" on a DECstation 5000.
 * The argument "-a" means vmunix should do an automatic reboot.
E 2
 */
void
D 5
main(argc, argv, argenv)
E 5
I 5
main(argc, argv)
E 5
	int argc;
	char **argv;
D 5
	char **argenv;
E 5
{
	register char *cp;
D 5
	int howto, entry;
E 5
I 5
	int ask, entry;
E 5
I 2
D 7
	char *boot = "boot";
E 7
E 2

D 2
	for (entry = 0; entry < argc; entry++)
		printf("%d: '%s'\n", entry, argv[entry]);
E 2
#ifdef JUSTASK
D 2
	howto = RB_ASKNAME | RB_SINGLE;
E 2
I 2
D 5
	howto = RB_ASKNAME;
E 5
I 5
	ask = 1;
E 5
E 2
#else
D 2
	howto = (argc > 1 && strcmp(argv[1], "-a") == 0) ?
		0 : RB_SINGLE;
E 2
I 2
D 5
	if (argc > 0 && strcmp(argv[0], boot) == 0) {
		argc--;
		argv++;
		argv[0] = getenv(boot);
D 3
		printf("boot '%s'\n", argv[0]); /* XXX */
E 3
	}
	howto = 0;
E 5
I 5
D 8
	ask = 0;
#ifdef DS3100
E 5
E 2
	for (cp = argv[0]; *cp; cp++) {
		if (*cp == ')' && cp[1]) {
			cp = argv[0];
			goto fnd;
		}
	}
D 5
	howto |= RB_ASKNAME;
E 5
I 5
#endif
#ifdef DS5000
	if (argc > 1) {
E 8
I 8
	/* check for DS5000 boot */
	if (strcmp(argv[0], "boot") == 0) {
E 8
		argc--;
		argv++;
D 8
		/* look for second '/' as in '5/rz0/vmunix' */
		for (cp = argv[0]; *cp; cp++) {
			if (*cp == '/') {
				while (*++cp) {
					if (*cp == '/' && cp[1]) {
						cp = argv[0];
						goto fnd;
					}
				}
			}
		}
E 8
	}
D 8
#endif
	ask = 1;
E 5
fnd:
	;
E 8
I 8
	cp = *argv;
	ask = 0;
E 8
D 5
#endif
E 5
I 5
#endif /* JUSTASK */
E 5
	for (;;) {
D 5
		if (howto & RB_ASKNAME) {
E 5
I 5
		if (ask) {
E 5
			printf("Boot: ");
			gets(line);
			if (line[0] == '\0')
				continue;
			cp = line;
I 2
			argv[0] = cp;
			argc = 1;
E 2
		} else
			printf("Boot: %s\n", cp);
		entry = loadfile(cp);
		if (entry != -1)
			break;
D 2
		howto = RB_ASKNAME | RB_SINGLE;
E 2
I 2
D 5
		howto = RB_ASKNAME;
E 5
I 5
		ask = 1;
E 5
E 2
	}
D 5
#ifndef TEST
	Boot_Transfer(argc, argv, argenv, entry);
#endif
E 5
I 5
	printf("Starting at 0x%x\n\n", entry);
D 9
	((void (*)())entry)(argc, argv);
E 9
I 9
	if (callv == &callvec)
		((void (*)())entry)(argc, argv, 0, 0);
	else
		((void (*)())entry)(argc, argv, DEC_PROM_MAGIC, callv);
E 9
E 5
}

/*
 * Open 'filename', read in program and return the entry point or -1 if error.
 */
loadfile(fname)
	register char *fname;
{
	register struct devices *dp;
	register int fd, i, n;
	struct exec aout;

D 5
	if ((fd = Open(fname, 0)) < 0)
E 5
I 5
	if ((fd = open(fname, 0)) < 0) {
D 7
		printf("Can't open '%s'\n", fname);
E 7
E 5
		goto err;
I 5
	}
E 5

D 6
	/* read the COFF header */
E 6
I 6
	/* read the exec header */
E 6
D 5
	i = Read(fd, (char *)&aout, sizeof(aout));
E 5
I 5
	i = read(fd, (char *)&aout, sizeof(aout));
E 5
	if (i != sizeof(aout)) {
D 7
		printf("No a.out header\n");
E 7
		goto cerr;
	} else if (aout.a_magic != OMAGIC) {
D 7
		printf("A.out? magic 0%o size %d+%d+%d\n", aout.a_magic,
			aout.a_text, aout.a_data, aout.a_bss);
E 7
		goto cerr;
	}

	/* read the code and initialized data */
	printf("Size: %d+%d", aout.a_text, aout.a_data);
D 5
	if (Lseek(fd, N_TXTOFF(aout), 0) < 0) {
E 5
I 5
	if (lseek(fd, (off_t)N_TXTOFF(aout), 0) < 0) {
E 5
D 7
		printf("\nSeek error\n");
E 7
		goto cerr;
	}
	i = aout.a_text + aout.a_data;
D 7
#ifndef TEST
E 7
D 5
	n = Read(fd, (char *)aout.ex_aout.codeStart, i);
E 5
I 5
D 6
	n = read(fd, (char *)aout.ex_aout.codeStart, i);
E 6
I 6
	n = read(fd, (char *)aout.a_entry, i);
E 6
E 5
D 7
#else
	n = i;
#endif
E 7
I 7
#ifndef SMALL
E 7
D 5
	(void) Close(fd);
E 5
I 5
	(void) close(fd);
I 7
#endif
E 7
E 5
	if (n < 0) {
D 7
		printf("\nRead error\n");
E 7
		goto err;
	} else if (n != i) {
D 7
		printf("\nShort read (%d)\n", n);
E 7
		goto err;
	}

	/* kernel will zero out its own bss */
	n = aout.a_bss;
	printf("+%d\n", n);

	return ((int)aout.a_entry);

cerr:
I 7
#ifndef SMALL
E 7
D 5
	(void) Close(fd);
E 5
I 5
	(void) close(fd);
I 7
#endif
E 7
E 5
err:
I 7
	printf("Can't boot '%s'\n", fname);
E 7
	return (-1);
}
E 1
