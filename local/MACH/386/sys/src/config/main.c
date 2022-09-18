/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	main.c,v $
 * Revision 2.7.1.1  90/02/01  13:37:58  rvb
 * 	Cast all sprintf's (void).
 * 	[90/01/22            rvb]
 * 
 * Revision 2.7  89/03/09  21:12:18  rpd
 * 	More cleanup.
 * 
 * Revision 2.6  89/02/25  19:21:48  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.5  89/02/07  22:56:02  mwyoung
 * Code cleanup cataclysm.
 * 
 * Revision 2.4  89/01/23  22:22:36  af
 * 	Changes for MIPS and I386.
 * 	Add get_rest() for "|" processing.
 * 	[89/01/09            rvb]
 * 
 * 17-Mar-88  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Allow source directory to be specified.
 *
 * 03-Mar-88  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Made changes for Sun 4.
 *
 * 08-Jan-87  Robert Beck (beck) at Sequent Computer Systems, Inc.
 *	main() now handles MACHINE_SQT specific configuration stuff.
 *
 * 16-Nov-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Don't create a symbolic link for "sys" in the build directory.
 *
 * 27-Oct-86  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Merged in David Black's changes for the Multimax.
 *
 * 22-Oct-86  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Merged in changes for Sun 2 and 3.
 *
 *  4-Oct-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Changed references of CMUCS to CMU.
 *
 *  18-Apr-86  Robert V. Baron (rvb) at Carnegie-Mellon University
 *	No more make depend warning.
 *
 */
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 */

#ifndef	lint
char copyright[] =
"@(#) Copyright (c) 1980 Regents of the University of California.\n\
 All rights reserved.\n";
#endif	not lint

#ifndef	lint
static char sccsid[] = "@(#)main.c	5.2 (Berkeley) 1/11/86";
#endif	not lint

#include <stdio.h>
#include <ctype.h>
#include "y.tab.h"
#include "config.h"

/*
 * Config builds a set of files for building a UNIX
 * system given a description of the desired system.
 */
main(argc, argv)
	int argc;
	char **argv;
{

	source_directory = "..";	/* default */
	object_directory = "..";
	config_directory = (char *) 0;
	while ((argc > 1) && (argv[1][0] == '-')) {
		char		*c;

		argv++; argc--;
		for (c = &argv[0][1]; *c ; c++) {
			switch (*c) {
				case 'd':
					source_directory = argv[1];
					goto check_arg;

				case 'o':
					object_directory = argv[1];
					goto check_arg;

				case 'c':
					config_directory = argv[1];

				 check_arg:
				 	if (argv[1] == (char *) 0)
						goto usage_error;
					argv++; argc--;
					break;

				case 'p':
					profiling++;
					break;
				default:
					goto usage_error;
			}
		}
	}
	if (config_directory == (char *) 0) {
		config_directory =
			malloc((unsigned) strlen(source_directory) + 6);
		(void) sprintf(config_directory, "%s/conf", source_directory);
	}
	if (argc != 2) {
		usage_error: ;
		fprintf(stderr, "usage: config [ -dco dir ] [ -p ] sysname\n");
	}
	PREFIX = argv[1];
	if (freopen(argv[1], "r", stdin) == NULL) {
		perror(argv[1]);
		exit(2);
	}
	dtab = NULL;
	confp = &conf_list;
	opt = 0;
	if (yyparse())
		exit(3);
	switch (machine) {

	case MACHINE_VAX:
		vax_ioconf();		/* Print ioconf.c */
		ubglue();		/* Create ubglue.s */
		break;

	case MACHINE_SUN:
		sun_ioconf();
		break;

	case MACHINE_SUN2:
	case MACHINE_SUN3:
	case MACHINE_SUN4:
		sun_ioconf();           /* Print ioconf.c */
		mbglue();               /* Create mbglue.s */
		break;
	case MACHINE_ROMP:
		romp_ioconf();
		break;

	case MACHINE_MMAX:
		mmax_ioconf();
		break;

	case MACHINE_SQT:
		sqt_ioconf();
		break;
	case MACHINE_I386:
	case MACHINE_IX:
		/* i386_ioconf(); */
		break;
	case MACHINE_MIPSY:
	case MACHINE_MIPS:
		mips_ioconf();
		break;
	default:
		printf("Specify machine type, e.g. ``machine vax''\n");
		exit(1);
	}
	makefile();			/* build Makefile */
	headers();			/* make a lot of .h files */
	swapconf();			/* swap config files */
}

/*
 * get_word
 *	returns EOF on end of file
 *	NULL on end of line
 *	pointer to the word otherwise
 */
char *
get_word(fp)
	register FILE *fp;
{
	static char line[80];
	register int ch;
	register char *cp;

	while ((ch = getc(fp)) != EOF)
		if (ch != ' ' && ch != '\t')
			break;
	if (ch == EOF)
		return ((char *)EOF);
	if (ch == '\n')
		return (NULL);
	if (ch == '|')
		return( "|");
	cp = line;
	*cp++ = ch;
	while ((ch = getc(fp)) != EOF) {
		if (isspace(ch))
			break;
		*cp++ = ch;
	}
	*cp = 0;
	if (ch == EOF)
		return ((char *)EOF);
	(void) ungetc(ch, fp);
	return (line);
}

/*
 * get_rest
 *	returns EOF on end of file
 *	NULL on end of line
 *	pointer to the word otherwise
 */
char *
get_rest(fp)
	register FILE *fp;
{
	static char line[80];
	register int ch;
	register char *cp;

	cp = line;
	while ((ch = getc(fp)) != EOF) {
		if (ch == '\n')
			break;
		*cp++ = ch;
	}
	*cp = 0;
	if (ch == EOF)
		return ((char *)EOF);
	return (line);
}

/*
 * prepend the path to a filename
 */
char *
path(file)
	char *file;
{
	register char *cp;

	cp = malloc((unsigned)(strlen(PREFIX)+strlen(file)+strlen(object_directory)+3));
	(void) sprintf(cp, "%s/%s/%s", object_directory, PREFIX, file);
	return (cp);
}
