h47877
s 00000/00047/00000
d R 5.3 91/05/23 19:12:22 sellgren 3 2
c no longer need anything in here, all moved to correct places.
e
s 00024/00035/00023
d D 5.2 90/05/02 14:24:01 bostic 2 1
c move scores/data files into /var, /usr/share
c remove time checks, dm does that, minor general cleanup
e
s 00058/00000/00000
d D 5.1 89/03/05 18:59:14 bostic 1 0
c date and time created 89/03/05 18:59:14 by bostic
e
u
U
t
T
I 1
/*
 *	config.c	--	This defines the installation dependent variables.
 *                  Some strings are modified later.  ANSI C would
 *                  allow compile time string concatenation, we must
 *                  do runtime concatenation, in main.
 *
 *		Larn is copyrighted 1986 by Noah Morgan.
 */
#include "header.h"
I 2
#include "pathnames.h"
E 2

D 2
#ifndef LARNHOME
#define LARNHOME "/usr/games/lib/larn/"		/* normally supplied by a Makefile */
#endif

#ifndef WIZID
#define WIZID	0
#endif

E 2
/*
 *	All these strings will be appended to in main() to be complete filenames
 */

D 2
		/* the game save filename   */
char savefilename[SAVEFILENAMESIZE] = 					LARNHOME;
E 2
I 2
/* the game save filename */
char savefilename[1024];
E 2

D 2
		/* the score file	    	*/
char scorefile[sizeof(LARNHOME)+sizeof(SCORENAME)] =	LARNHOME;
E 2
I 2
/* the logging file */
char logfile[] = _PATH_LOG;
E 2

D 2
		/* the logging file     	*/
char logfile[sizeof(LARNHOME)+sizeof(LOGFNAME)]  =		LARNHOME;
E 2
I 2
/* the help text file */
char helpfile[] = _PATH_HELP;
E 2

D 2
		/* the help text file		*/
char helpfile[sizeof(LARNHOME)+sizeof(HELPNAME)] = 		LARNHOME;
E 2
I 2
/* the score file */
char scorefile[] = _PATH_SCORE;
E 2

D 2
		/* the maze data file		*/
char larnlevels[sizeof(LARNHOME)+sizeof(LEVELSNAME)] = 	LARNHOME;
E 2
I 2
/* the maze data file */
char larnlevels[] = _PATH_LEVELS;
E 2

D 2
		/* the fortune data file	*/
char fortfile[sizeof(LARNHOME)+sizeof(FORTSNAME)] =		LARNHOME;
E 2
I 2
/* the fortune data file */
char fortfile[] = _PATH_FORTS;
E 2

D 2
		/* the .larnopts filename */
char optsfile[128] ="/.larnopts";				/* the option file			*/
E 2
I 2
/* the .larnopts filename */
char optsfile[1024] ="/.larnopts";
E 2

D 2
		/* the player id datafile name */
char playerids[sizeof(LARNHOME)+sizeof(PLAYERIDS)] =	LARNHOME;
E 2
I 2
/* the player id datafile name */
char playerids[] = _PATH_PLAYERIDS;
E 2

D 2
		/* the holiday datafile */
char holifile[sizeof(LARNHOME)+sizeof(HOLIFILE)] =		LARNHOME;
E 2
I 2
char diagfile[] ="Diagfile";		/* the diagnostic filename */
char ckpfile[] ="Larn12.0.ckp";		/* the checkpoint filename */
char *password ="pvnert(x)";		/* the wizards password <=32 */
char psname[PSNAMESIZE]="larn";		/* the process name */
E 2

D 2
char diagfile[] ="Diagfile";					/* the diagnostic filename	*/
char ckpfile[] ="Larn12.0.ckp";					/* the checkpoint filename	*/
char *password ="pvnert(x)";					/* the wizards password <=32*/
#if WIZID == -1
int wisid=0;			/* the user id of the only person who can be wizard */
#else
int wisid=WIZID;		/* the user id of the only person who can be wizard */
#endif
char psname[PSNAMESIZE]="larn";						/* the process name		*/
E 2
I 2
#define	WIZID	1
int wisid=0;		/* the user id of the only person who can be wizard */

E 2
E 1
