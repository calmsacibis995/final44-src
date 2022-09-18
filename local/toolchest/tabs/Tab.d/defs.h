/*

 *      Copyright (c) 1984, 1985 AT&T
 *      All Rights Reserved

 *      THIS IS UNPUBLISHED PROPRIETARY SOURCE 
 *      CODE OF AT&T.
 *      The copyright notice above does not 
 *      evidence any actual or intended
 *      publication of such source code.

 */
/*
 *	defs.h for expand.c from the 6.0 shell
 *
 *	This is not the defs.h from the 6.0 shell.  This file
 *	contains just enough of the header files to make expand.c
 *	work.  The header files from the shell are so interconnected
 *	it is difficult at best to use them.  This file also
 *	contains some trickery to get expand to work.  trapnote is
 *	normally a global variable that denotes whether or not a
 *	signal has occurred.  Here we define trapnote as zero so
 *	that all of the signal checking will not get compiled into
 *	expand.o. - CDB
 *
 */

 /* defines from Bourne */
#ifdef pdp11
typedef char BOOL;
#else
typedef short BOOL;
#endif

#define TRUE	(-1)
#define FALSE	0
#define LOBYTE	0377
#define STRIP	0177
#define QUOTE	0200

#define BYTESPERWORD	(sizeof (char *))
#define MINUS	'-'

#define SIGSET		4

 /* dummy for access only */
struct argnod
{
	struct argnod	*argnxt;
	char	argval[1];
};

 /* Our Routines to Make Expand Work */
extern char   *endstak ();
extern char   *locstak ();

 /* Fake Globals for expand - These were globals */
#define nullstr		"\0"
#define trapnote	(0)

 /* Globals for expand */
extern struct argnod	*gchain;
