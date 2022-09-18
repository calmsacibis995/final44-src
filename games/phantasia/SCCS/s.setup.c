h09734
s 00001/00000/00261
d D 5.9 95/05/14 16:36:36 mkm 9 8
c unistd.h for optarg
e
s 00030/00011/00231
d D 5.8 92/08/28 15:52:41 bostic 8 7
c hack to take an argument (and I mean hack)
e
s 00001/00033/00241
d D 5.7 90/05/02 21:48:17 bostic 7 6
c more cleanup, this is pretty pitiful.  *sigh*
e
s 00021/00023/00253
d D 5.6 90/03/05 12:26:51 bostic 6 5
c make it work with ANSI C preprocessor
e
s 00002/00002/00274
d D 5.5 89/03/06 10:29:56 bostic 5 4
c nor does make want to hear your pithy little comments
e
s 00000/00006/00276
d D 5.4 89/03/06 08:42:53 bostic 4 3
c OK_TO_PLAY no longer necessary, we have dm(8)
e
s 00001/00001/00281
d D 5.3 88/06/01 19:20:09 bostic 3 2
c we no longer support %[A-Z]; besides, it messes up SCCS
e
s 00002/00000/00280
d D 5.2 87/07/27 16:15:10 bostic 2 1
c make doesn't answer questions
e
s 00280/00000/00000
d D 5.1 87/06/05 14:37:01 bostic 1 0
c date and time created 87/06/05 14:37:01 by bostic
e
u
U
t
T
I 1
/*
 * setup.c - set up all files for Phantasia
 */
#include "include.h"
#include <sys/types.h>
#include <sys/stat.h>
I 8
#include <stdlib.h>
I 9
#include <unistd.h>
E 9
E 8
/**/
/************************************************************************
/
/ FUNCTION NAME: main()
/
/ FUNCTION: setup files for Phantasia 3.3.2
/
/ AUTHOR: E. A. Estes, 12/4/85
/
/ ARGUMENTS: none
/
/ RETURN VALUE: none
/
/ MODULES CALLED: time(), exit(), stat(), Error(), creat(), close(), fopen(), 
/	fgets(), floor(), srandom(), umask(), drandom(), strcpy(), getuid(), 
/	unlink(), fwrite(), fclose(), sscanf(), printf(), strlen(), fprintf()
/
D 6
/ GLOBAL INPUTS: Peoplefile[], Curmonster, _iob[], Databuf[], *Monstfp, 
/	Lastdead[], Goldfile[], Voidfile[], Motdfile[], Messfile[], Scorefile[], 
/	Enemyfile[], Monstfile[], Enrgyvoid
E 6
I 6
/ GLOBAL INPUTS: Curmonster, _iob[], Databuf[], *Monstfp, Enrgyvoid
E 6
/
/ GLOBAL OUTPUTS: Curmonster, Databuf[], *Monstfp, Enrgyvoid
/
/ DESCRIPTION: 
/
/	This program tries to verify the parameters specified in
/	the Makefile.
/
/	Create all necessary files.  Note that nothing needs to be
/	put in these files.
/	Also, the monster binary data base is created here.
/
/************************************************************************/

D 8
main()
{
FILE	*fp;			/* for opening files */
struct stat	fbuf;		/* for getting files statistics */
register char	**filename;	/* for pointing to file names */
register int	fd;		/* file descriptor */
static char *files[] =		/* all files to create */
	{
E 8
I 8
static char *files[] = {		/* all files to create */
E 8
D 6
	Monstfile,
	Peoplefile,
	Messfile,
	Lastdead,
	Motdfile,
	Goldfile,
	Voidfile,
	Scorefile,
E 6
I 6
	_PATH_MONST,
	_PATH_PEOPLE,
	_PATH_MESS,
	_PATH_LASTDEAD,
	_PATH_MOTD,
	_PATH_GOLD,
	_PATH_VOID,
	_PATH_SCORE,
E 6
D 7
#ifdef ENEMY
D 6
	Enemyfile,
E 6
I 6
	_PATH_ENEMY,
E 6
#endif
E 7
D 8
	(char *) NULL
	};
E 8
I 8
	NULL,
};
E 8

I 8
char *monsterfile="monsters.asc";

int
main(argc, argv)
	int argc;
	char *argv[];
{
	register char	**filename;	/* for pointing to file names */
	register int	fd;		/* file descriptor */
	FILE	*fp;			/* for opening files */
	struct stat	fbuf;		/* for getting files statistics */
	int ch;

	while ((ch = getopt(argc, argv, "m:")) != EOF)
		switch(ch) {
		case 'm':
			monsterfile = optarg;
			break;
		case '?':
		default:
			break;
		}
	argc -= optind;
	argv += optind;

E 8
    srandom((unsigned) time((long *) NULL));	/* prime random numbers */

    umask(0117);		/* only owner can read/write created files */

D 7
    if (getuid() != UID)
	fprintf(stderr, "Warning: UID (%d) is not equal to current uid.\n", UID);

    /* check Phantasia destination directory */
D 6
    if (stat(DEST", &fbuf) < 0)
E 6
I 6
    if (stat(_PATH_PHANTDIR, &fbuf) < 0)
E 6
	/* not found */
	{
D 6
	Error("Cannot stat %s.\n", DEST");
E 6
I 6
	Error("Cannot stat %s.\n", _PATH_PHANTDIR);
E 6
	exit(1);
	/*NOTREACHED*/
	}

    if ((fbuf.st_mode & S_IFDIR) == 0)
	/* not a directory */
D 6
	Error("%s is not a directory.\n", DEST");
E 6
I 6
	Error("%s is not a directory.\n", _PATH_PHANTDIR);
E 6
	/*NOTREACHED*/

E 7
    /* try to create data files */
    filename = &files[0];
    while (*filename != NULL)
	/* create each file */
	{
	if (stat(*filename, &fbuf) == 0)
	    /* file exists; remove it */
	    {
D 6
	    if (*filename == Peoplefile)
E 6
I 6
	    if (!strcmp(*filename, _PATH_PEOPLE))
E 6
		/* do not reset character file if it already exists */
		{
		++filename;
		continue;
		}

	    if (unlink(*filename) < 0)
		Error("Cannot unlink %s.\n", *filename);
		/*NOTREACHED*/
	    }

	if ((fd = creat(*filename, 0660)) < 0)
	    Error("Cannot create %s.\n", *filename);
	    /*NOTREACHED*/

	close(fd);			/* close newly created file */

	++filename;			/* process next file */
	}

    /* put holy grail info into energy void file */
    Enrgyvoid.ev_active = TRUE;
    Enrgyvoid.ev_x = ROLL(-1.0e6, 2.0e6);
    Enrgyvoid.ev_y = ROLL(-1.0e6, 2.0e6);
D 6
    if ((fp = fopen(Voidfile, "w")) == NULL)
	Error("Cannot update %s.\n", Voidfile);
E 6
I 6
    if ((fp = fopen(_PATH_VOID, "w")) == NULL)
	Error("Cannot update %s.\n", _PATH_VOID);
E 6
    else
	{
	fwrite(&Enrgyvoid, SZ_VOIDSTRUCT, 1, fp);
	fclose(fp);
	}

    /* create binary monster data base */
D 6
    if ((Monstfp = fopen(Monstfile, "w")) == NULL)
	Error("Cannot update %s.\n", Monstfile);
E 6
I 6
    if ((Monstfp = fopen(_PATH_MONST, "w")) == NULL)
	Error("Cannot update %s.\n", _PATH_MONST);
E 6
    else
	{
D 8
	if ((fp = fopen("monsters.asc", "r")) == NULL)
E 8
I 8
	if ((fp = fopen(monsterfile, "r")) == NULL)
E 8
	    {
	    fclose(Monstfp);
	    Error("cannot open %s to create monster database.\n", "monsters.asc");
	    }
	else
	    {
	    Curmonster.m_o_strength =
	    Curmonster.m_o_speed =
	    Curmonster.m_maxspeed =
	    Curmonster.m_o_energy =
	    Curmonster.m_melee =
	    Curmonster.m_skirmish = 0.0;

	    while (fgets(Databuf, SZ_DATABUF, fp) != NULL)
		/* read in text file, convert to binary */
		{
D 3
		sscanf(&Databuf[24], "%F%F%F%F%F%d%d%F",
E 3
I 3
		sscanf(&Databuf[24], "%lf%lf%lf%lf%lf%d%d%lf",
E 3
		    &Curmonster.m_strength, &Curmonster.m_brains,
		    &Curmonster.m_speed, &Curmonster.m_energy,
		    &Curmonster.m_experience, &Curmonster.m_treasuretype,
		    &Curmonster.m_type, &Curmonster.m_flock);
		Databuf[24] = '\0';
		strcpy(Curmonster.m_name, Databuf);
		fwrite((char *) &Curmonster, SZ_MONSTERSTRUCT, 1, Monstfp);
		}
	    fclose(fp);
	    fclose(Monstfp);
	    }
	}

I 2
D 5
#ifdef MAKE_INSTALLS_THIS_AND_DOESNT_ANSWER_QUESTIONS
E 5
I 5
#ifdef MAKE_INSTALLS_THIS_AND_DOESNT_WANT_TO_HEAR_ABOUT_IT
E 5
E 2
    /* write to motd file */
    printf("One line 'motd' ? ");
    if (fgets(Databuf, SZ_DATABUF, stdin) == NULL)
	Databuf[0] = '\0';
D 6
    if ((fp = fopen(Motdfile, "w")) == NULL)
	Error("Cannot update %s.\n", Motdfile);
E 6
I 6
    if ((fp = fopen(_PATH_MOTD, "w")) == NULL)
	Error("Cannot update %s.\n", _PATH_MOTD);
E 6
    else
	{
	fwrite(Databuf, sizeof(char), strlen(Databuf), fp);
	fclose(fp);
	}
I 2
D 5
#endif
E 5
E 2

    /* report compile-time options */
    printf("Compiled options:\n\n");
D 6
    printf("Phantasia destination directory:  %s\n", DEST");
E 6
I 6
    printf("Phantasia destination directory:  %s\n", _PATH_PHANTDIR);
E 6
D 7
    printf("Wizard:  %s   UID:  %d\n", WIZARD, UID);

D 4
#ifdef OK_TO_PLAY
    printf("Restricted playing enabled.\n");
#else
    printf("Playing unrestricted.\n");
#endif

E 4
#ifdef ENEMY
    printf("Enemy list enabled.\n");
#else
    printf("Enemy list disabled.\n");
#endif

#ifdef SHELL
    printf("Shell escapes enabled.  Default shell:  %s\n", SHELL);
#else
    printf("Shell escapes disabled.\n");
#endif
E 7
I 7
    printf("Wizard: root UID: 0\n");
E 7

#ifdef BSD41
    printf("Compiled for BSD 4.1\n");
#endif

#ifdef BSD42
    printf("Compiled for BSD 4.2\n");
#endif

#ifdef SYS3
    printf("Compiled for System III\n");
#endif

#ifdef SYS5
    printf("Compiled for System V\n");
I 5
#endif
E 5
#endif

    exit(0);
    /*NOTREACHED*/
}
/**/
/************************************************************************
/
/ FUNCTION NAME: Error()
/
/ FUNCTION: print an error message, and exit
/
/ AUTHOR: E. A. Estes, 12/4/85
/
/ ARGUMENTS:
/	char *str - format string for printf()
/	char *file - file which caused error
/
/ RETURN VALUE: none
/
/ MODULES CALLED: exit(), perror(), fprintf()
/
/ GLOBAL INPUTS: _iob[]
/
/ GLOBAL OUTPUTS: none
/
/ DESCRIPTION:
/	Print an error message, then exit.
/
/************************************************************************/

Error(str, file)
char	*str, *file;
{
    fprintf(stderr, "Error: ");
    fprintf(stderr, str, file);
    perror(file);
    exit(1);
    /*NOTREACHED*/
}
/**/
/************************************************************************
/
/ FUNCTION NAME: drandom()
/
/ FUNCTION: return a random number
/
/ AUTHOR: E. A. Estes, 2/7/86
/
/ ARGUMENTS: none
/
/ RETURN VALUE: none
/
/ MODULES CALLED: random()
/
/ GLOBAL INPUTS: none
/
/ GLOBAL OUTPUTS: none
/
/ DESCRIPTION: 
/
/************************************************************************/

double
drandom()
{
    if (sizeof(int) != 2)
	return((double) (random() & 0x7fff) / 32768.0);
    else
	return((double) random() / 32768.0);
}
E 1
