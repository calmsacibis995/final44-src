h32360
s 00027/00021/00249
d D 8.2 95/04/28 17:08:04 christos 3 2
c Updated to the latest version from the NetBSD source
e
s 00002/00002/00268
d D 8.1 93/06/06 15:15:02 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00270/00000/00000
d D 5.1 93/05/24 14:47:30 bostic 1 0
c date and time created 93/05/24 14:47:30 by bostic
e
u
U
t
T
I 1
/*
D 2
 * Copyright (c) 1993 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * This code is derived from software contributed to Berkeley by
 * Christos Zoulas.
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

/*-
 * for.c --
 *	Functions to handle loops in a makefile.
 *
 * Interface:
 *	For_Eval 	Evaluate the loop in the passed line.
 *	For_Run		Run accumulated loop
 *
 */

#include    <ctype.h>
#include    "make.h"
#include    "hash.h"
#include    "dir.h"
#include    "buf.h"

/*
 * For statements are of the form:
 *
 * .for <variable> in <varlist>
 * ...
 * .endfor
 *
 * The trick is to look for the matching end inside for for loop
 * To do that, we count the current nesting level of the for loops.
 * and the .endfor statements, accumulating all the statements between
 * the initial .for loop and the matching .endfor; 
 * then we evaluate the for loop for each variable in the varlist.
 */

static int  	  forLevel = 0;  	/* Nesting level	*/
static char	 *forVar;		/* Iteration variable	*/
static Buffer	  forBuf;		/* Commands in loop	*/
static Lst	  forLst;		/* List of items	*/

/*
 * State of a for loop.
 */
D 3
struct For {
E 3
I 3
typedef struct _For {
E 3
    Buffer	  buf;			/* Unexpanded buffer	*/
    char*	  var;			/* Index name		*/
    Lst  	  lst;			/* List of variables	*/
D 3
};
E 3
I 3
} For;
E 3

D 3
static int ForExec	__P((char *, struct For *));
E 3
I 3
static int ForExec	__P((ClientData, ClientData));
E 3




/*-
 *-----------------------------------------------------------------------
 * For_Eval --
 *	Evaluate the for loop in the passed line. The line
 *	looks like this:
 *	    .for <variable> in <varlist>
 *
 * Results:
 *	TRUE: We found a for loop, or we are inside a for loop
 *	FALSE: We did not find a for loop, or we found the end of the for
 *	       for loop.
 *
 * Side Effects:
 *	None.
 *
 *-----------------------------------------------------------------------
 */
int
For_Eval (line)
    char    	    *line;    /* Line to parse */
{
    char	    *ptr = line, *sub, *wrd;
    int	    	    level;  	/* Level at which to report errors. */

    level = PARSE_FATAL;


    if (forLevel == 0) {
	Buffer	    buf;
	int	    varlen;

D 3
	for (ptr++; *ptr && isspace(*ptr); ptr++)
E 3
I 3
	for (ptr++; *ptr && isspace((unsigned char) *ptr); ptr++)
E 3
	    continue;
	/*
	 * If we are not in a for loop quickly determine if the statement is
	 * a for.
	 */
D 3
	if (ptr[0] != 'f' || ptr[1] != 'o' || ptr[2] != 'r' || !isspace(ptr[3]))
E 3
I 3
	if (ptr[0] != 'f' || ptr[1] != 'o' || ptr[2] != 'r' ||
	    !isspace((unsigned char) ptr[3]))
E 3
	    return FALSE;
	ptr += 3;
	
	/*
	 * we found a for loop, and now we are going to parse it.
	 */
D 3
	while (*ptr && isspace(*ptr))
E 3
I 3
	while (*ptr && isspace((unsigned char) *ptr))
E 3
	    ptr++;
	
	/*
	 * Grab the variable
	 */
	buf = Buf_Init(0);
D 3
	for (wrd = ptr; *ptr && !isspace(*ptr); ptr++) 
E 3
I 3
	for (wrd = ptr; *ptr && !isspace((unsigned char) *ptr); ptr++) 
E 3
	    continue;
	Buf_AddBytes(buf, ptr - wrd, (Byte *) wrd);

	forVar = (char *) Buf_GetAll(buf, &varlen);
	if (varlen == 0) {
	    Parse_Error (level, "missing variable in for");
	    return 0;
	}
	Buf_Destroy(buf, FALSE);

D 3
	while (*ptr && isspace(*ptr))
E 3
I 3
	while (*ptr && isspace((unsigned char) *ptr))
E 3
	    ptr++;

	/*
	 * Grab the `in'
	 */
D 3
	if (ptr[0] != 'i' || ptr[1] != 'n' || !isspace(ptr[2])) {
E 3
I 3
	if (ptr[0] != 'i' || ptr[1] != 'n' ||
	    !isspace((unsigned char) ptr[2])) {
E 3
	    Parse_Error (level, "missing `in' in for");
	    printf("%s\n", ptr);
	    return 0;
	}
	ptr += 3;

D 3
	while (*ptr && isspace(*ptr))
E 3
I 3
	while (*ptr && isspace((unsigned char) *ptr))
E 3
	    ptr++;

	/*
	 * Make a list with the remaining words
	 */
	forLst = Lst_Init(FALSE);
	buf = Buf_Init(0);
	sub = Var_Subst(NULL, ptr, VAR_GLOBAL, FALSE); 

#define ADDWORD() \
	Buf_AddBytes(buf, ptr - wrd, (Byte *) wrd), \
	Buf_AddByte(buf, (Byte) '\0'), \
	Lst_AtEnd(forLst, (ClientData) Buf_GetAll(buf, &varlen)), \
	Buf_Destroy(buf, FALSE)

D 3
	for (ptr = sub; *ptr && isspace(*ptr); ptr++)
E 3
I 3
	for (ptr = sub; *ptr && isspace((unsigned char) *ptr); ptr++)
E 3
	    continue;

	for (wrd = ptr; *ptr; ptr++)
D 3
	    if (isspace(*ptr)) {
E 3
I 3
	    if (isspace((unsigned char) *ptr)) {
E 3
		ADDWORD();
		buf = Buf_Init(0);
D 3
		while (*ptr && isspace(*ptr))
E 3
I 3
		while (*ptr && isspace((unsigned char) *ptr))
E 3
		    ptr++;
		wrd = ptr--;
	    }
	if (DEBUG(FOR))
	    (void) fprintf(stderr, "For: Iterator %s List %s\n", forVar, sub);
	if (ptr - wrd > 0) 
	    ADDWORD();
	else
	    Buf_Destroy(buf, TRUE);
	free((Address) sub);
	    
	forBuf = Buf_Init(0);
	forLevel++;
	return 1;
    }
    else if (*ptr == '.') {

D 3
	for (ptr++; *ptr && isspace(*ptr); ptr++)
E 3
I 3
	for (ptr++; *ptr && isspace((unsigned char) *ptr); ptr++)
E 3
	    continue;

D 3
	if (strncmp(ptr, "endfor", 6) == 0 && (isspace(ptr[6]) || !ptr[6])) {
E 3
I 3
	if (strncmp(ptr, "endfor", 6) == 0 &&
	    (isspace((unsigned char) ptr[6]) || !ptr[6])) {
E 3
	    if (DEBUG(FOR))
		(void) fprintf(stderr, "For: end for %d\n", forLevel);
	    if (--forLevel < 0) {
		Parse_Error (level, "for-less endfor");
		return 0;
	    }
	}
D 3
	else if (strncmp(ptr, "for", 3) == 0 && isspace(ptr[3])) {
E 3
I 3
	else if (strncmp(ptr, "for", 3) == 0 &&
		 isspace((unsigned char) ptr[3])) {
E 3
	    forLevel++;
	    if (DEBUG(FOR))
		(void) fprintf(stderr, "For: new loop %d\n", forLevel);
	}
    }

    if (forLevel != 0) {
	Buf_AddBytes(forBuf, strlen(line), (Byte *) line);
	Buf_AddByte(forBuf, (Byte) '\n');
	return 1;
    }
    else {
	return 0;
    }
}

/*-
 *-----------------------------------------------------------------------
 * ForExec --
 *	Expand the for loop for this index and push it in the Makefile
 *
 * Results:
 *	None.
 *
 * Side Effects:
 *	None.
 *
 *-----------------------------------------------------------------------
 */
static int
D 3
ForExec(name, arg)
    char *name;
    struct For *arg;
E 3
I 3
ForExec(namep, argp)
    ClientData namep;
    ClientData argp;
E 3
{
I 3
    char *name = (char *) namep;
    For *arg = (For *) argp;
E 3
    int len;
    Var_Set(arg->var, name, VAR_GLOBAL);
    if (DEBUG(FOR))
	(void) fprintf(stderr, "--- %s = %s\n", arg->var, name);
    Parse_FromString(Var_Subst(arg->var, (char *) Buf_GetAll(arg->buf, &len), 
			       VAR_GLOBAL, FALSE));
    Var_Delete(arg->var, VAR_GLOBAL);

    return 0;
}


/*-
 *-----------------------------------------------------------------------
 * For_Run --
 *	Run the for loop, immitating the actions of an include file
 *
 * Results:
 *	None.
 *
 * Side Effects:
 *	None.
 *
 *-----------------------------------------------------------------------
 */
void
For_Run()
{
D 3
    struct For arg;
E 3
I 3
    For arg;
E 3

    if (forVar == NULL || forBuf == NULL || forLst == NULL)
	return;
    arg.var = forVar;
    arg.buf = forBuf;
    arg.lst = forLst;
    forVar = NULL;
    forBuf = NULL;
    forLst = NULL;

    Lst_ForEach(arg.lst, ForExec, (ClientData) &arg);

    free((Address)arg.var);
D 3
    Lst_Destroy(arg.lst, free);
E 3
I 3
    Lst_Destroy(arg.lst, (void (*) __P((ClientData))) free);
E 3
    Buf_Destroy(arg.buf, TRUE);
}
E 1
