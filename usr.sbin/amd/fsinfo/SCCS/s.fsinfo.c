h34513
s 00005/00005/00244
d D 8.1 93/06/06 12:04:26 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00000/00243
d D 5.5 93/06/06 12:04:20 bostic 6 4
c it's a main(), throw in the copyright string
e
s 00002/00002/00241
d R 8.1 93/06/06 11:57:04 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00242
d D 5.4 92/02/09 08:44:00 pendry 4 3
c merge in new release
e
s 00003/00002/00240
d D 5.3 91/05/12 15:59:48 pendry 3 2
c checkpoint for network tape
e
s 00001/00013/00241
d D 5.2 91/03/17 13:43:52 pendry 2 1
c from amd5.3 alpha11
e
s 00254/00000/00000
d D 5.1 91/03/17 11:02:47 pendry 1 0
c date and time created 91/03/17 11:02:47 by pendry
e
u
U
t
T
I 1
/*
D 3
 * $Id: fsinfo.c,v 5.2.1.2 90/12/21 16:46:47 jsp Alpha $
 *
E 3
 * Copyright (c) 1989 Jan-Simon Pendry
 * Copyright (c) 1989 Imperial College of Science, Technology & Medicine
D 7
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
 * This code is derived from software contributed to Berkeley by
 * Jan-Simon Pendry at Imperial College, London.
 *
D 2
 * Redistribution and use in source and binary forms are permitted provided
 * that: (1) source distributions retain this entire copyright notice and
 * comment, and (2) distributions including binaries display the following
 * acknowledgement:  ``This product includes software developed by the
 * University of California, Berkeley and its contributors'' in the
 * documentation or other materials provided with the distribution and in
 * all advertising materials mentioning features or use of this software.
 * Neither the name of the University nor the names of its contributors may
 * be used to endorse or promote products derived from this software without
 * specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 2
I 2
 * %sccs.include.redist.c%
E 2
 *
 *	%W% (Berkeley) %G%
I 3
 *
D 4
 * $Id: fsinfo.c,v 5.2.1.3 91/05/07 22:19:01 jsp Alpha $
E 4
I 4
 * $Id: fsinfo.c,v 5.2.2.1 1992/02/09 15:09:33 jsp beta $
E 4
 *
E 3
 */

I 6
#ifndef lint
D 7
char copyright[] =
"%Z% Copyright (c) 1993 The Regents of the University of California.\n\
 All rights reserved.\n";
E 7
I 7
static char copyright[] =
"%Z% Copyright (c) 1989, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 7
#endif /* not lint */

E 6
/*
 * fsinfo
 */

#include "../fsinfo/fsinfo.h"
#include "fsi_gram.h"
#include <pwd.h>

qelem *list_of_hosts;
qelem *list_of_automounts;
dict *dict_of_volnames;
dict *dict_of_hosts;
char *autodir = "/a";
char hostname[MAXHOSTNAMELEN+1];
char *username;
int file_io_errors;
int parse_errors;
int errors;
int verbose;
char idvbuf[1024];

char **g_argv;
char *progname;

/*
 * Output file prefixes
 */
char *exportfs_pref;
char *fstab_pref;
char *dumpset_pref;
char *mount_pref;
char *bootparams_pref;

/*
 * Argument cracking...
 */
static void get_args(c, v)
int c;
char *v[];
{
	extern char *optarg;
	extern int optind;
	int ch;
	int usage = 0;
	char *iptr = idvbuf;

	/*
	 * Determine program name
	 */
	if (v[0]) {
		progname = strrchr(v[0], '/');
		if (progname && progname[1])
			progname++;
		else
			progname = v[0];
	}
	if (!progname)
		progname = "fsinfo";

	while ((ch = getopt(c, v, "a:b:d:e:f:h:m:D:U:I:qv")) != EOF)
	switch (ch) {
	case 'a':
		autodir = optarg;
		break;
	case 'b':
		if (bootparams_pref)
			fatal("-b option specified twice");
		bootparams_pref = optarg;
		break;
	case 'd':
		if (dumpset_pref)
			fatal("-d option specified twice");
		dumpset_pref = optarg;
		break;
	case 'h':
		strncpy(hostname, optarg, sizeof(hostname)-1);
		break;
	case 'e':
		if (exportfs_pref)
			fatal("-e option specified twice");
		exportfs_pref = optarg;
		break;
	case 'f':
		if (fstab_pref)
			fatal("-f option specified twice");
		fstab_pref = optarg;
		break;
	case 'm':
		if (mount_pref)
			fatal("-m option specified twice");
		mount_pref = optarg;
		break;
	case 'q':
		verbose = -1;
		break;
	case 'v':
		verbose = 1;
		break;
	case 'I': case 'D': case 'U':
		sprintf(iptr, "-%c%s ", ch, optarg);
		iptr += strlen(iptr);
		break;
	default:
		usage++;
		break;
	}

	if (c != optind) {
		g_argv = v + optind - 1;
		if (yywrap())
			fatal("Cannot read any input files");
	} else {
		usage++;
	}

	if (usage) {
		fprintf(stderr,
"\
Usage: %s [-v] [-a autodir] [-h hostname] [-b bootparams] [-d dumpsets]\n\
\t[-e exports] [-f fstabs] [-m automounts]\n\
\t[-I dir] [-D|-U string[=string]] config ...\n", progname);
		exit(1);
	}


	if (g_argv[0])
		log("g_argv[0] = %s", g_argv[0]);
	else
		log("g_argv[0] = (nil)");
}

/*
 * Determine username of caller
 */
static char *find_username()
{
	extern char *getlogin();
	extern char *getenv();
	char *u = getlogin();
	if (!u) {
		struct passwd *pw = getpwuid(getuid());
		if (pw)
			u = pw->pw_name;
	}
	if (!u)
		u = getenv("USER");
	if (!u)
		u = getenv("LOGNAME");
	if (!u)
		u = "root";

	return strdup(u);
}

/*
 * MAIN
 */
main(argc, argv)
int argc;
char *argv[];
{
	/*
	 * Process arguments
	 */
	get_args(argc, argv);

	/*
	 * If no hostname given then use the local name
	 */
	if (!*hostname && gethostname(hostname, sizeof(hostname)) < 0) {
		perror("gethostname");
		exit(1);
	}

	/*
	 * Get the username
	 */
	username = find_username();

	/*
	 * New hosts and automounts
	 */
	list_of_hosts = new_que();
	list_of_automounts = new_que();

	/*
	 * New dictionaries
	 */
	dict_of_volnames = new_dict();
	dict_of_hosts = new_dict();

	/*
	 * Parse input
	 */
	show_area_being_processed("read config", 11);
	if (yyparse())
		errors = 1;
	errors += file_io_errors + parse_errors;

	if (errors == 0) {
		/*
		 * Do semantic analysis of input
		 */
		analyze_hosts(list_of_hosts);
		analyze_automounts(list_of_automounts);
	}

	/*
	 * Give up if errors
	 */
	if (errors == 0) {
		/*
		 * Output data files
		 */

		write_atab(list_of_automounts);
		write_bootparams(list_of_hosts);
		write_dumpset(list_of_hosts);
		write_exportfs(list_of_hosts);
		write_fstab(list_of_hosts);
	}

	col_cleanup(1);

	exit(errors);
}
E 1
