h37559
s 00001/00001/00064
d D 8.2 95/04/28 16:04:07 bostic 15 14
c externs.h -> extern.h
e
s 00002/00002/00063
d D 8.1 93/05/31 17:50:23 bostic 14 13
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00064
d D 5.7 91/02/28 14:47:53 bostic 13 12
c ANSI
e
s 00001/00011/00064
d D 5.6 90/06/01 13:20:16 bostic 12 11
c new copyright notice
e
s 00004/00003/00071
d D 5.5 90/05/03 10:44:50 bostic 11 10
c move log file to /var/games
e
s 00001/00000/00073
d D 5.4 89/03/05 21:10:53 bostic 10 9
c pwd.h needs types.h
e
s 00010/00005/00063
d D 5.3 88/06/18 19:55:34 bostic 9 8
c install approved copyright notice
e
s 00009/00003/00059
d D 5.2 88/03/09 12:30:23 bostic 8 7
c written by David Riggle and Edward Wang; add Berkeley specific copyright
e
s 00005/00005/00057
d D 5.1 85/05/29 16:03:32 dist 7 6
c Add copyright
e
s 00006/00000/00056
d D 2.3 85/04/23 21:53:18 edward 6 5
c copyright message
e
s 00006/00020/00050
d D 2.2 85/03/04 18:06:23 edward 5 4
c more cleanup; sail, driver, sail.log merged into single program
e
s 00000/00000/00070
d D 2.1 83/10/31 13:45:32 edward 4 3
c new version
e
s 00046/00039/00024
d D 1.3 83/07/20 17:27:50 edward 3 2
c 
e
s 00000/00000/00063
d D 1.2 83/05/20 17:45:21 root 2 1
c merge
e
s 00063/00000/00000
d D 1.1 83/03/17 21:12:02 leres 1 0
c date and time created 83/03/17 21:12:02 by leres
e
u
U
t
T
I 6
/*
D 7
 * Copyright (c) 1983 Regents of the University of California,
 * All rights reserved.  Redistribution permitted subject to
 * the terms of the Berkeley Software License Agreement.
E 7
I 7
D 14
 * Copyright (c) 1983 Regents of the University of California.
D 8
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 8
I 8
 * All rights reserved.
E 14
I 14
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 14
 *
D 12
 * Redistribution and use in source and binary forms are permitted
D 9
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 9
I 9
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
E 12
I 12
 * %sccs.include.redist.c%
E 12
E 9
E 8
E 7
 */

E 6
I 1
#ifndef lint
D 7
static	char *sccsid = "%W% %E%";
#endif
E 7
I 7
static char sccsid[] = "%W% (Berkeley) %G%";
D 8
#endif not lint
E 8
I 8
#endif /* not lint */
E 8
E 7
I 3

E 3
/*
 * Print out the top ten SAILors
 *
D 5
 * sail.log [-s/l]
 *
 *  -s force a short listing (without real usernames)
 *  -l force a long listing (print out real usernames)
E 5
I 5
 * -l force a long listing (print out real usernames)
E 5
 */
I 10
#include <sys/types.h>
E 10
#include <pwd.h>
D 15
#include "externs.h"
E 15
I 15
#include "extern.h"
E 15
I 11
#include "pathnames.h"
E 11

char *title[] = {
D 3
    "Admiral", "Commodore", "Captain", "Captain",
    "Captain", "Captain", "Captain", "Commander",
    "Commander", "Lieutenant"
E 3
I 3
	"Admiral", "Commodore", "Captain", "Captain",
	"Captain", "Captain", "Captain", "Commander",
	"Commander", "Lieutenant"
E 3
};

D 5
main(argc, argv)
int argc;
char **argv;
E 5
I 5
lo_main()
E 5
{
D 3
    FILE *fp;
    char sbuf[32];
    int n = 0, people;
    int usrnam = SAILLOGDEF;
    struct passwd *getpwuid(), *pass;
    struct logs flog;
E 3
I 3
	FILE *fp;
	char sbuf[32];
	int n = 0, people;
D 5
	int usrnam = 0;
E 5
D 13
	struct passwd *getpwuid(), *pass;
E 13
I 13
	struct passwd *pass;
E 13
	struct logs log;
	struct ship *ship;
E 3

D 3
    if (argc > 1)
	if (argc == 2)
	    if (!strcmp(argv[1], "-s"))
		usrnam = 0;
	    else if (!strcmp(argv[1], "-l"))
		usrnam = 1;
	else {
	    fprintf(stderr, "usage: %s: [-s/l]\n", argv[0]);
	    exit(1);
E 3
I 3
D 5
	if (argc > 1 && argc == 2)
		if (strcmp(argv[1], "-s") == 0)
			usrnam = 0;
		else if (strcmp(argv[1], "-l") == 0)
			usrnam = 1;
		else {
			fprintf(stderr, "usage: %s: [-s/l]\n", argv[0]);
			exit(1);
		}
E 5
D 11
	if ((fp = fopen(LOGFILE, "r")) == 0) {
		perror(LOGFILE);
E 11
I 11
	if ((fp = fopen(_PATH_LOGFILE, "r")) == 0) {
		perror(_PATH_LOGFILE);
E 11
		exit(1);
E 3
	}
D 3
    if((fp = fopen(LOGFILE, "r")) == 0) {
	printf("%s: Error opening logfile - %s\n", argv[0], LOGFILE);
	exit(1);
    }
    if (fread(&people, sizeof(people), 1, fp) == 0) {
	printf("%s: Error reading logfile.\n", argv[0]);
	exit(1);
    }
    while ((fread(&flog, sizeof(flog), 1, fp) != 0) && (flog.fname[0] != '\0')) {
	if (usrnam && ((pass = getpwuid(flog.uid)) != NULL))
	    sprintf(sbuf, "%10.10s (%s)", flog.fname, pass->pw_name);
	else
	    sprintf(sbuf, "%10.10s", flog.fname);
	printf("%-10s %21s of the %15s %3d points, %5.2f equiv\n",
	  title[n++], sbuf,
	  scene[flog.fgamenum].ship[flog.fshipnum].shipname,
	  flog.netpoints,
	  (float) flog.netpoints /
	  specs[scene[flog.fgamenum].ship[flog.fshipnum].shipnum].pts);
    }
    printf("\n%d people have played.\n", people);
E 3
I 3
	switch (fread((char *)&people, sizeof people, 1, fp)) {
	case 0:
		printf("Nobody has sailed yet.\n");
		exit(0);
	case 1:
		break;
	default:
D 11
		perror(LOGFILE);
E 11
I 11
		perror(_PATH_LOGFILE);
E 11
		exit(1);
	}
D 5
	while (fread((char *)&log, sizeof log, 1, fp) == 1
	       && log.l_name[0] != '\0') {
		if (usrnam && (pass = getpwuid(log.l_uid)) != NULL)
E 5
I 5
	while (fread((char *)&log, sizeof log, 1, fp) == 1 &&
	       log.l_name[0] != '\0') {
		if (longfmt && (pass = getpwuid(log.l_uid)) != NULL)
E 5
			(void) sprintf(sbuf, "%10.10s (%s)",
				log.l_name, pass->pw_name);
		else
			(void) sprintf(sbuf, "%20.20s", log.l_name);
		ship = &scene[log.l_gamenum].ship[log.l_shipnum];
		printf("%-10s %21s of the %15s %3d points, %5.2f equiv\n",
			title[n++], sbuf, ship->shipname, log.l_netpoints,
			(float) log.l_netpoints / ship->specs->pts);
	}
	printf("\n%d people have played.\n", people);
I 5
	return 0;
E 5
E 3
}
E 1
