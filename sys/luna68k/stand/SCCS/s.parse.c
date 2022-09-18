h42439
s 00002/00002/00135
d D 8.1 93/06/10 22:29:44 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00137/00000/00000
d D 7.1 92/12/13 03:50:20 akito 1 0
c date and time created 92/12/13 03:50:20 by akito
e
u
U
t
T
I 1
/*
 * Copyright (c) 1992 OMRON Corporation.
D 2
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * This code is derived from software contributed to Berkeley by
 * OMRON Corporation.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/*
 * parse.c -- command parser
 * by A.Fujita, JAN-30-1992
 */

#include <luna68k/stand/status.h>

/* for scsi.c */

int scsi();

/* for disklabel.c */

int disklabel();

/* for boot.c */

int boot();

int load();

int how_to_boot();

/* for tape.c */

int tape();

/* for fsdump.c */

int fsdump();
int fsrestore();

/* for screen.c */

int screen();

int
check_args(argc, argv)
	int   argc;
	char *argv[];
{
	register int i;

	for ( i = 0; i < argc; i++)
		printf("argv[%d] = \"%s\"\n", i, argv[i]);

	return(ST_NORMAL);
}

int
exit_program(argc, argv)
	int   argc;
	char *argv[];
{
	return(ST_EXIT);
}

struct command_entry {
	char *name;
	int (*func)();
};

struct command_entry entries[] = {
{ "b",		boot         },
{ "boot",	boot         },
{ "chkargs",	check_args   },
{ "disklabel",	disklabel    },
{ "exit",	exit_program },
{ "fsdump",	fsdump       },
{ "fsrestore",	fsrestore    },
{ "howto",	how_to_boot  },
{ "load",       load         },
{ "screen",	screen	     },
{ "tape",	tape	     },
{ "tp",		tape	     },
{ "scsi",	scsi         },
{ "quit",	exit_program },
{ 0, 0 }
};


int 
parse(argc, argv)
	int   argc;
	char *argv[];
{
	register int i, status = ST_NOTFOUND;

	for (i = 0; entries[i].name != (char *) 0; i++) {
		if (!strcmp(argv[0], entries[i].name)) {
			status = (*entries[i].func)(argc, argv);
			break;
		}
	}

	return(status);
}



/*
 * getargs -- make argument arrays
 */

getargs(buffer, argv, maxargs)
	char buffer[], *argv[];
	int  maxargs;
{
	register int   n = 0;
	register char *p = buffer;

	argv[n++] = p;
	while (*p != '\0') {
		if ( *p == ' ' ) {
			*p = '\0';
		} else if (p != buffer && *(p-1) == '\0') {
			if ( n < maxargs )
				argv[n++] = p;
		}
		p++;
	}

	return(n);
}
E 1
