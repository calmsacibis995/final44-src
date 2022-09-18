h32002
s 00046/00008/00105
d D 1.3 83/06/24 14:34:19 slatteng 3 2
c use smaller raster images, and fix read/giveup bug
e
s 00004/00004/00109
d D 1.2 83/06/22 13:45:15 slatteng 2 1
c fix newline on error message...
e
s 00113/00000/00000
d D 1.1 83/06/17 17:03:53 slatteng 1 0
c date and time created 83/06/17 17:03:53 by slatteng
e
u
U
t
T
I 1
/* %M%	%I%	%E% 	by David Slattengren
 *
 *      This file contains a program for printing gprint raster files.
 *   Gprint puts out a generic file, and gdump changes the size to fit
 *   the proper device that's being used.
 */

#include <stdio.h>
#include <signal.h>
#include "gprint.h"

#define LPR	"/usr/ucb/lpr"

extern char *mktemp();

char *picture	= "/usr/tmp/rastAXXXXXX";	/* output file name */
int  temp;					/* output file number */
char *lpargs[9]	= { "lpr", "-Pvarian", "-v",
		   "-s", "-r", "-J", "gdump" };
int  outwidth	= Vbytperlin;		/* number of chars per line to output*/
int  outlength	= Vylen;		/* number of lines to output */

int  infile	= 0;		/* input file (default = stdin) */
I 3
int  inwidth	= Vxlen/8;	/* input file raster line length */
E 3
int  FileFound	= 0;		/* flag for filename on input */
char *arg;			/* intermediary command line argument */
char *file;			/* input file name */
char buf [Wbytperlin];		/* intermediary raster line buffer */


cleanup()		/* Called if program stopped, or ... */
{
    unlink (picture);
    exit (1);
}


I 3
			/* read in one line of the raster file */
readline()		/* returns 1 (true) if successful, 0 if not */
{
    register i = inwidth;
    register j;

    do {
    	if ((j = read (infile, buf, inwidth)) < 1) {
	    if (i == inwidth)
		return (0);
	    else {			/* fill in incomplete last line */
		while (i != inwidth)
		    buf [i++] = '\0';
		return (1);
	    }
	}
	i -= j;
    } while (i);
    return (1);
}


E 3
main (argc, argv)
int argc;
char *argv[];
{
I 3
    register int i;		/* multipurpose index */


E 3
    lpargs [7] = picture;	/* set file for lpr to read */
    lpargs [8] = 0;
D 3

E 3
    while (--argc > 0)		/* Parse the command line. */
    {
        arg = *++argv;
        if (arg[0] != '-') {
	    if (FileFound) {
		fprintf (stderr, "gdump: Only one file may be printed\n");
		exit(1);
	    }
            lpargs [6] = file = arg;	/* set filename (and to lpr) */
            FileFound = 1;
        } else {
            switch (*++arg) {
		case 'W':		/* Print to wide (versatec) device */
			outwidth = Wbytperlin;
			outlength = Wylen;
			lpargs[1] = "-Pversatec";
			break;
		case 'V':		/* Print to narrow (varian) device */
			outwidth = Vbytperlin;
			outlength = Vylen;
			lpargs[1] = "-Pvarian";
			break;
		default:
D 2
			printf ("unknown switch %c", *arg);
E 2
I 2
			printf ("unknown switch %c\n", *arg);
E 2
			exit (1);
			break;
            }
D 2
        }
E 2
I 2
        } 
E 2
    }

    if (FileFound) {		/* open input file, if one exists */
	fclose (stdin);
	infile = open (file, 0);
	if (infile == -1) {
            fprintf (stderr, "can't open %s", file);
	    exit(1);
	}
    }
					/* clear out line buffer */
D 3
    for (FileFound = 0; FileFound < Wbytperlin; buf [FileFound++] = 0)
E 3
I 3
    for (i = 0; i < Wbytperlin; buf [i++] = 0)
E 3
	;

    mktemp (picture);			/* make up file name */

    signal (SIGTERM, cleanup);			/* prepare to be killed */
    if (signal (SIGINT, SIG_IGN) != SIG_IGN)	/*    or interrupted */
	signal (SIGINT, cleanup);

    if ((temp = creat (picture, 0666)) == -1) {
	fprintf (stderr, "gdump: can't create %s\n", picture);
	cleanup ();
    }

D 3
/****** transfer the raster file from input to output, fixing line
	lengths, if necessary, and truncating to one page length *********/
E 3
I 3
/*
 * transfer the raster file from input to output,
 * fixing line lengths, if necessary,
 * and truncating to one page length
 */
E 3

D 3
    while ((read (infile, buf, Vbytperlin) == Vbytperlin) && outlength--) {
E 3
I 3
    while (readline () && outlength--) {
E 3
	if (write (temp, buf, outwidth) != outwidth) {
D 3
	    fprintf (stderr, "gdump: error writing file %s\n", picture);
E 3
I 3
	    sprintf (buf, "gdump - error writing %s\n", picture);
	    perror (buf);
E 3
	    cleanup();
	}
D 2
    }
    close (infile);				/* eat the rest of input */
E 2
I 2
    }						/* eat the rest of input */
E 2
D 3
    while (read (infile, buf, Vbytperlin) > 0)	/* if there is any */
E 3
I 3
    while (read (infile, buf, inwidth) > 0)	/* if there is any */
E 3
	;
I 2
D 3
    close (infile);
E 3
I 3
    close (infile);				/* clear out line buffer */
    for (i = 0; i < Wbytperlin; buf [i++] = 0)
	;
    while (outlength-- > 0) {			/* and fill out the picture */
	if (write (temp, buf, outwidth) != outwidth) {
	    sprintf (buf, "gdump - error writing %s\n", picture);
	    perror (buf);
	    cleanup();
	}
    }
E 3
E 2

    execv (LPR, lpargs);
    fprintf (stderr, "gdump: can't exec %s\n", LPR);
    cleanup();
}
E 1
