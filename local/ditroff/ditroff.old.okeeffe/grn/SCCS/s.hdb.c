h18449
s 00004/00001/00230
d D 1.9 86/04/14 10:16:08 slatteng 10 9
c put in extra bounds saving for wide text
e
s 00003/00002/00228
d D 1.8 84/10/20 10:46:49 opcode 9 8
c DBRead - fixed bug with blank text strings
e
s 00142/00039/00088
d D 1.7 84/10/08 15:41:58 ralph 8 7
c update for format of new SUN gremlin files.
e
s 00005/00002/00122
d D 1.6 84/04/07 19:27:38 slatteng 7 5
c pretty-up error messages
e
s 00005/00002/00122
d R 1.6 84/04/07 19:24:11 slatteng 6 5
c pretty-up the error reporting.
e
s 00002/00002/00122
d D 1.5 84/03/15 16:38:34 slatteng 5 4
c allow ONE negative coordinate in a coordinate set (-1.00 -1.00 at end)
e
s 00001/00001/00123
d D 1.4 83/07/25 13:34:30 slatteng 4 3
c added dopey semicolon...
e
s 00018/00010/00106
d D 1.3 83/07/25 12:39:52 slatteng 3 2
c fixed bug in text elements:  extra positioning points were messing picture bounds
e
s 00001/00001/00115
d D 1.2 83/07/21 15:30:16 slatteng 2 1
c this version does the picture bounds updates for troff
e
s 00116/00000/00000
d D 1.1 83/07/21 15:27:29 slatteng 1 0
c date and time created 83/07/21 15:27:29 by slatteng
e
u
U
t
T
I 1
D 2
/*	hdb.c	1.1	(Berkeley) 83/07/09
E 2
I 2
/*	%M%	%I%	(Berkeley) %E%
E 2
 *
 * Copyright -C- 1982 Barry S. Roitblat
 *
 *      This file contains database routines for the hard copy programs of the
 * gremlin picture editor.
 */

#include "gprint.h"
I 8
#include <ctype.h>
E 8

I 8
#define MAXSTRING 128

E 8
I 7
/* imports from main.c */
I 8

E 8
extern int linenum;		/* current line number in input file */
extern char gremlinfile[];	/* name of file currently reading */
I 8
extern int SUNFILE;		/* TRUE if SUN gremlin file */
E 8
E 7

/* imports from c */

extern char *malloc();
extern char *strcpy();
extern char *sprintf();

/* imports from point.c */

extern POINT *PTInit();
extern POINT *PTMakePoint();

D 8
ELT *DBInit()
E 8
/*
D 8
 *      This routine returns a pointer to an initialized database element
E 8
I 8
 * This routine returns a pointer to an initialized database element
E 8
 * which would be the only element in an empty list.
 */
D 8

E 8
I 8
ELT *
DBInit()
E 8
{
D 8
    return(NULL);
E 8
I 8
    return((ELT *) NULL);
E 8
}  /* end DBInit */

D 8
ELT *DBCreateElt(type, pointlist, brush, size, text, db)
int type, brush, size;
POINT *pointlist;
char *text;
ELT *(*db) ;
E 8
I 8

E 8
/*
D 8
 *      This routine creates a new element with the specified attributes and
E 8
I 8
 * This routine creates a new element with the specified attributes and
E 8
 * links it into database.
 */
D 8

E 8
I 8
ELT *
DBCreateElt(type, pointlist, brush, size, text, db)
int type, brush, size;
POINT *pointlist;
char *text;
ELT *(*db);
E 8
{
    register ELT *temp;

    temp = (ELT *) malloc(sizeof(ELT));
    temp->nextelt = *db;
    temp->type = type;
    temp->ptlist = pointlist;
    temp->brushf = brush;
    temp->size = size;
    temp->textpt = text;
    *db = temp;
    return(temp);
} /* end CreateElt */

D 8
ELT *DBRead(file)
register FILE *file;
E 8
I 8

E 8
/*
D 8
 *      This routine reads the specified file into a database and 
E 8
I 8
 * This routine reads the specified file into a database and 
E 8
 * returns a pointer to that database.
 */
D 8

E 8
I 8
ELT *
DBRead(file)
register FILE *file;
E 8
{
    register int i;
    register int done;		/* flag for input exhausted */
D 3
    register int orient;	/* orientation flag:  set by file */
E 3
I 3
D 8
    register int type;		/* element type */
E 8
E 3
    register float nx;		/* x holder so x is not set before orienting */
I 8
    int type;			/* element type */
E 8
    ELT *elist;			/* pointer to the file's elements */
    POINT *plist;		/* pointer for reading in points */
D 8
    char  string[100], *txt;
E 8
I 8
    char  string[MAXSTRING], *txt;
E 8
    float x, y;			/* x and y are read in point coords */
D 3
    int len, type, brush, size;
E 3
I 3
    int len, brush, size;
I 8
    int lastpoint;
E 8
E 3


I 8
    SUNFILE = FALSE;
E 8
    elist = DBInit();
D 8
    (void) fscanf(file,"%s",string);
E 8
I 8
    (void) fscanf(file,"%s\n",string);
E 8
    if (strcmp(string, "gremlinfile")) {
D 7
        fprintf(stderr, "not gremlin file\n");
E 7
I 7
D 8
        error("%s is not a gremlin file", gremlinfile);
E 7
        return(elist);
E 8
I 8
	if (strcmp(string, "sungremlinfile")) {
	    error("%s is not a gremlin file", gremlinfile);
	    return(elist);
	}
	SUNFILE = TRUE;
E 8
    }
D 8
    (void) fscanf(file, "%d%f%f", &size, &x, &y);
E 8
I 8
    (void) fscanf(file, "%d%f%f\n", &size, &x, &y);
E 8
D 3
    orient = size;
				/* ignore file positioning point */
E 3
I 3
			/* ignore orientation and file positioning point */
E 3
    done = FALSE;
    while (!done) {
D 3
        if (fscanf(file,"%d", &type) == EOF) {
E 3
I 3
D 8
        if (fscanf(file,"%d", &size) == EOF) {
E 8
I 8
        if (fscanf(file,"%s\n", string) == EOF) {
E 8
E 3
D 7
            fprintf(stderr, "error in file format\n");
E 7
I 7
            error("%s, error in file format", gremlinfile);
E 7
            return(elist);
        }
D 3
        if (type < 0) {		/* no more data */
E 3
I 3
D 8
        if ((type = size) < 0) {	/* no more data */
E 8
I 8
	type = DBGetType(string);		/* interpret element type */
        if (type < 0) {					/* no more data */
E 8
E 3
            done = TRUE;
            (void) fclose(file);
        } else {
D 8
            (void) fscanf(file, "%f%f", &x, &y);
            plist = PTInit();		/* pointlist terminated by -1,-1 */
D 3
            while ((x >= 0.0) && (y >= 0.0)) {
                nx = xorn(x,y);
E 3
I 3
	    if (TEXT(type)) {		/* only one point for text elements */
		nx = xorn(x,y);
E 3
                (void) PTMakePoint(nx, y = yorn(x,y), &plist);
E 8
I 8
            (void) fscanf(file, "%f%f\n", &x, &y);	/* always one point */
            plist = PTInit();				/* NULL point list */

	    /* Files created on the SUN have point lists terminated 
	     * by a line containing only an asterik ('*').  Files 
	     * created on the AED have point lists terminated by the
	     * coordinate pair (-1.00 -1.00).
	     */
	    if (TEXT(type)) {	/* read only first point for TEXT elements */
		nx = xorn(x, y);
		y = yorn(x, y);
                (void) PTMakePoint(nx, y, &plist);
E 8
		savebounds(nx, y);
D 3
                (void) fscanf(file, "%f%f", &x, &y);
            }
E 3
I 3
D 8
                do
D 4
		    (void) fscanf(file, "%f%f", &x, &y)
E 4
I 4
		    (void) fscanf(file, "%f%f", &x, &y);
E 4
D 5
		while ((x >= 0.0) && (y >= 0.0));
E 5
I 5
		while ((x >= 0.0) || (y >= 0.0));
E 5
	    } else {
D 5
		while ((x >= 0.0) && (y >= 0.0)) {
E 5
I 5
		while ((x >= 0.0) || (y >= 0.0)) {
E 5
		    nx = xorn(x,y);
		    (void) PTMakePoint(nx, y = yorn(x,y), &plist);
E 8
I 8

		lastpoint = FALSE;
                do {
		    fgets(string, MAXSTRING, file);
		    if (string[0] == '*') {	/* SUN gremlin file */
			lastpoint = TRUE;
		    }
		    else {
			(void) sscanf(string, "%f%f", &x, &y);
D 10
			if ((x == -1.00 && y == -1.00) && (!SUNFILE))
E 10
I 10
			if ((x == -1.00 && y == -1.00) && (!SUNFILE)) {
E 10
			    lastpoint = TRUE;
I 10
			} else {
			    savebounds(xorn(x, y), yorn(x, y));
			}
E 10
		    }
		} while (!lastpoint);
	    } 
	    else {		/* not TEXT element */
		lastpoint = FALSE;
		while (!lastpoint) {
		    nx = xorn(x, y);
		    y = yorn(x, y);
		    (void) PTMakePoint(nx, y, &plist);
E 8
		    savebounds(nx, y);
D 8
		    (void) fscanf(file, "%f%f", &x, &y);
E 8
I 8

		    fgets(string, MAXSTRING, file);
		    if (string[0] == '*') {	/* SUN gremlin file */
			lastpoint = TRUE;
		    }
		    else {
			(void) sscanf(string, "%f%f", &x, &y);
			if ((x == -1.00 && y == -1.00) && (!SUNFILE))
			    lastpoint = TRUE;
		    }
E 8
		}
	    }
E 3
D 8
            (void) fscanf(file, "%d%d", &brush, &size);
            (void) fscanf(file, "%d", &len);   
E 8
I 8
            (void) fscanf(file, "%d%d\n", &brush, &size);
D 9
            (void) fscanf(file, "%d ", &len);   
E 9
I 9
            (void) fscanf(file, "%d", &len);	/* text length */
	    (void) getc(file);			/* eat blank */
E 9
E 8
            txt = malloc((unsigned) len + 1);
D 8
            (void) getc(file);        /* throw away space character */
E 8
D 9
            for (i=0; i<len; ++i) {
E 9
I 9
            for (i=0; i<len; ++i) {		/* read text */
E 9
                txt[i] = getc(file);
	    }
            txt[len] = '\0';
            (void) DBCreateElt(type, plist, brush, size, txt, &elist);
        }  /* end else */
    }  /* end while not done */;
    return(elist);
} /* end DBRead */

I 8

/*
 * Interpret element type in string s.
 * Old file format consisted of integer element types.
 * New file format has literal names for element types.
 */
DBGetType(s)
register char *s;
{
    if (isdigit(s[0]) || (s[0] == '-'))		/* old element format or EOF */
	return(atoi(s));

    switch (s[0]) {
	case 'P':
	    return(POLYGON);
	case 'V':
	    return(VECTOR);
	case 'A':
	    return(ARC);
	case 'C':
	    if (s[1] == 'U')
		return(CURVE);
	    switch (s[4]) {
		case 'L':
		    return(CENTLEFT);
		case 'C':
		    return(CENTCENT);
		case 'R':
		    return(CENTRIGHT);
		default:
		    error("unknown element type");
		    exit(1);
	    }
	case 'B':
	    switch (s[3]) {
		case 'L':
		    return(BOTLEFT);
		case 'C':
		    return(BOTCENT);
		case 'R':
		    return(BOTRIGHT);
		default:
		    error("unknown element type");
		    exit(1);
	    }
	case 'T':
	    switch (s[3]) {
		case 'L':
		    return(TOPLEFT);
		case 'C':
		    return(TOPCENT);
		case 'R':
		    return(TOPRIGHT);
		default:
		    error("unknown element type");
		    exit(1);
	    }
	default:
	    error("unknown element type");
	    exit(1);
    }
}
E 8
E 1
