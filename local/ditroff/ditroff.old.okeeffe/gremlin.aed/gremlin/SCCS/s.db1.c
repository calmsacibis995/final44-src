h35715
s 00115/00011/00342
d D 1.3 84/10/21 11:01:32 opcode 3 2
c DBRead() - can now read "sungremlinfile" format
e
s 00007/00008/00346
d D 1.2 83/04/18 14:35:02 slatteng 2 1
c 
e
s 00354/00000/00000
d D 1.1 83/04/18 13:45:15 slatteng 1 0
c date and time created 83/04/18 13:45:15 by slatteng
e
u
U
t
T
I 1
D 2

/* db1.c-
E 2
I 2
/* %W%	%G%
E 2
 *
 * Copyright -C- 1982 Barry S. Roitblat
 *
 *      This file contains routines for database manipulation for the
 * gremlin picture editor.
 */

#include "gremlin.h"
#include "grem2.h"
I 3
#include <ctype.h>
E 3

/* imports from undodb */

extern UNRembAdd(), UNRembDelete();

/* imports from c */

extern char *malloc();
extern char *strcpy();
extern char *sprintf();

/* imports from point.c */

extern POINT *PTInit();
extern POINT *PTMakePoint();

/* imports from textio.c  */

extern TxPutMsg(), TxMsgOK();

/* imports from main */

extern int SEARCH;        /* Search the path for filename ?? */

ELT *DBInit()
/*
 *      This routine returns a pointer to an initialized database element
 * which would be the only element in an empty list.
 */

{
    return(NULL);
}  /* end DBInit */

ELT *DBCreateElt(type, pointlist, brush, size, text, db)
int type, brush, size;
POINT *pointlist;
char *text;
ELT *(*db) ;
/*
 *      This routine creates a new element with the specified attributes and
 * links it into database.
 */

{
    ELT *temp;

    temp = (ELT *) malloc(sizeof(ELT));
    temp->nextelt = *db;
    temp->type = type;
    temp->ptlist = pointlist;
    temp->brushf = brush;
    temp->size = size;
    temp->textpt = text;
    *db = temp;
    UNRembAdd(temp, db);
    return(temp);
} /* end CreateElt */

D 2

E 2
I 2

E 2
DBDelete(element, db)
ELT *element, *(*db);
/*
 *      This routine deletes the specified element by searching the database
 * for its predecessor and deleting the pointer to the element.
 * Flag indicates whether or not the element was in the current set
 * and is passed along for use by the undo routines.
 */

{
    ELT *(*temp);

    temp = db;
    while (*temp != element)
    {
        if (DBNullelt(*temp))
        {
            error("no such element");
            return;
        };
        temp = &(DBNextElt((*temp)));
    };
    UNRembDelete(*temp, db);
    *temp = DBNextElt(element);
}  /* end DBDelete */

D 2

E 2
I 2

E 2
#define highval 10000               /* arbitrary value greater than any 
                                     * expected distance                */

DBGravitate(x1, y1, x2, y2, point, element, db)
float x1, y1, *x2, *y2;
POINT *(*point);
ELT *(*element), *db;
/*
 *      This routine searches the database for the point closest to
 * (Euclidean distance) point1.  This point is returned as point2
 * and the element which contained the point is also returned.
 * The point must be closer than some predefined maximum distance
 * in order to be gravitated.
 */

{
    POINT *holdpt;
    ELT *temp;
    long int t, t1, t2, distance = highval;

    temp = db;
    *element = DBInit();
    *x2 = x1;
    *y2 = y1;
    while ( !DBNullelt(temp) )
    {
        holdpt = temp->ptlist;
        while ( !Nullpoint(holdpt) )
        {

                /*  Calculate the distance between the point in the data
                 * base and the specified point.  Use Euclidean distance
                 * except that, since we only need relative distance and
                 * not an absolute number, it is not necessary to take the
                 * square root.  The equation for the distance was broken up
                 * as below in order to allow integer arithmetic wherever
                 * possible to increase efficiency when it was discovered
                 * that this routine was too slow.
                 */
            t1 = holdpt->x - x1;
            t1 *= t1;           
            t2 = holdpt->y - y1; 
            t2 *= t2;
            t = t1 + t2;
            if ((t < distance) && (t < MAXGDIST))
            {
                distance = t;
                *x2 = holdpt->x;
                *y2 = holdpt->y;
    		*point = holdpt;
                *element = temp;
            }  /* end if */;
            holdpt = holdpt->nextpt;
        }  /* end while holdpt */;
        temp = temp->nextelt;
    }  /* end while temp */;
}  /* end Gravitate */

D 2

E 2
I 2

E 2
DBSetGravitate(x1, y1, x2, y2, point, element, db)
float x1, y1, *x2, *y2;
POINT *(*point);
ELT *(*element), *db;
/*
 *      This routine searches the database for the point closest to
 * (Euclidean distance) point1.  This point is returned as point2
 * and the element which contained the point is also returned.
 * The point must be closer than some predefined maximum distance
 * in order to be gravitated.
 */

{
    POINT *holdpt;
    ELT *temp;
    long int t, t1, t2, distance = highval;

    temp = db;
    *element = DBInit();
    *x2 = x1;
    *y2 = y1;
    while ( !DBNullelt(temp) )
    {
        holdpt = temp->ptlist;
        while ( !Nullpoint(holdpt) )
        {

                /*  Calculate the distance between the point in the data
                 * base and the specified point.  Use Euclidean distance
                 * except that, since we only need relative distance and
                 * not an absolute number, it is not necessary to take the
                 * square root.  The equation for the distance was broken up
                 * as below in order to allow integer arithmetic wherever
                 * possible to increase efficiency when it was discovered
                 * that this routine was too slow.
                 */
            t1 = holdpt->x - x1;
            t1 *= t1;           
            t2 = holdpt->y - y1; 
            t2 *= t2;
            t = t1 + t2;
            if ((t < distance) && (t < MAXGDIST))
            {
                distance = t;
                *x2 = holdpt->x;
                *y2 = holdpt->y;
    		*point = holdpt;
                *element = temp;
            }  /* end if */;
            holdpt = holdpt->nextpt;
        }  /* end while holdpt */;
        temp = temp->setnext;
    }  /* end while temp */;
}  /* end Gravitate */


D 2

E 2
I 2

E 2
DBClearElt(elt)
ELT *elt;
/*
 *      This routine returns all storage associated with the element to
 * free storage
 */

{
    POINT *pt, *pt2;

    pt = elt->ptlist;
    while ( !Nullpoint(pt) )
    {
        pt2 = PTNextPoint(pt);
        free ((char *) pt);
        pt = pt2;
    }  /* end while */;
    free(elt->textpt);
    free((char *) elt);
}  /* end DBClearElt */

D 2

E 2
I 2

E 2
ELT *DBRead(filename, orient, pos)
char *filename;
int *orient;
POINT *pos;
/*
 *      This routine reads the specified file into a database and 
 * returns a pointer to that database.  Orient and pos are also set
 * from the file.
 *
 * The format of a file written by gremlin is:
 * the string: "gremlinfile" followed by a carriage return.
 * the orientation (integer) and the x and y coordinates of a positioning
 * point (float) followed by another carriage return.
 * The output of 0 or more elements (see below).
 * a -1 (integer) indicating end of data.
 *
 * The format of each element is:
 * The element type (integer) followed by a carriage return.
 * a list of 0 or more pairs of point coordinates (float) each on separate
 * lines and terminated by the coordinates -1.0 -1.0.
 * the brush (font) and size (integer) the element was defined with then <cr>
 * the length (integer) of the string followed by the string terminated with
 * a carriage return.
 *
 * All numbers are printed using standard c output conversion (ascii).
I 3
 *
 * +++ NEW FORMAT FOR SUN +++
 *
 * Installed 10/21/84 by Mark Opperman
 * This modification allows reading of either SUN or AED formats
 *
 * "sungremlinfile" is keyword in place of "gremlinfile"
 *
 * Point lists are terminated by a line containing a single asterik ('*')
 * to allow the legal point (-1.00 -1.00) in the point list.  All negative
 * coordinates are now legal.  Element types are indicated by ascii text,
 * eg, POLYGON, VECTOR, ARC, BOTLEFT, TOPCENT, etc.
E 3
 */

{
    FILE *fp, *POpen();
    ELT *elist;
    POINT *plist;
D 3
    char string[100], *txt;
E 3
I 3
    char string[128], *txt;
E 3
    float x, y;
D 3
    int len, type, i, brush, size, done;
E 3
I 3
    int len, type, i, brush, size, done, lastpoint, sunfile;
E 3

I 3
    sunfile = FALSE;
E 3
    elist = DBInit();
    fp = POpen(filename,(char **) NULL,SEARCH);
    if (fp == NULL)
    {
        (void) sprintf(string, "can't open %s",filename);
        error(string);
        return(elist);
    }
    TxPutMsg("reading file...");
D 3
    (void) fscanf(fp,"%s",string);
E 3
I 3
    (void) fscanf(fp,"%s\n",string);
E 3
    if ( strcmp(string, "gremlinfile") )
    {
D 3
        error("not gremlin file");
        return(elist);
E 3
I 3
	if ( strcmp(string, "sungremlinfile") )
	{
	    error("not gremlin file");
	    return(elist);
	}
	sunfile = TRUE;
E 3
    }
D 3
    (void) fscanf(fp, "%d%f%f", orient, &x, &y);
E 3
I 3
    (void) fscanf(fp, "%d%f%f\n", orient, &x, &y);
E 3
    pos->x = x;
    pos->y = y;

    done = FALSE;
    while (!done)
    {
D 3
        if ( fscanf(fp,"%d", &type) == EOF )
E 3
I 3
        if ( fscanf(fp,"%s\n", string) == EOF )		/* element type */
E 3
        {
            error("error in file format");
I 3
	    fclose(fp);
E 3
            return(elist);
        }
D 3
        if (type < 0)         /* no more data */
E 3
I 3
        if ( (type = DBGetType(string))  < 0)         /* no more data */
E 3
        {
            done = TRUE;
D 3
            (void) fclose(fp);
E 3
        }
        else
        {
D 3
            (void) fscanf(fp, "%f%f", &x, &y);
E 3
I 3
            (void) fscanf(fp, "%f%f\n", &x, &y);	/* read first point */
E 3
            plist = PTInit();
I 3

	    /* Files created on the SUN have point lists terminated
	     * by a line containing only an asterik ('*').  Files
	     * created on the AED have point lists terminated by the
	     * coordinate pair (-1.00 -1.00).
	     */
	    lastpoint = FALSE;
	    do {
		(void) PTMakePoint(x, y, &plist);
		fgets(string, 127, fp);
		if (string[0] == '*') {     /* SUN gremlin file */
		    lastpoint = TRUE;
		}
		else {
		    (void) sscanf(string, "%f%f", &x, &y);
		    if ((x == -1.00 && y == -1.00) && (!sunfile))
			lastpoint = TRUE;
		}
	    } while (!lastpoint);

#ifdef oldway
E 3
            while ((x != -1) && (y != -1)) /* pointlist terminated by -1, -1 */
            {
                (void) PTMakePoint(x, y, &plist);
                (void) fscanf(fp, "%f%f", &x, &y);
            }
D 3
            (void) fscanf(fp, "%d%d", &brush, &size);
E 3
I 3
#endif
            (void) fscanf(fp, "%d%d\n", &brush, &size);
E 3
            (void) fscanf(fp, "%d", &len);   
            txt = malloc((unsigned) len + 1);
            (void) getc(fp);        /* throw away space character */
            for (i=0; i<len; ++i)
                txt[i] = getc(fp);
            txt[len] = '\0';
            (void) DBCreateElt(type, plist, brush, size, txt, &elist);
        }  /* end else */
    }  /* end while not done */;
    TxMsgOK();
I 3
    fclose(fp);
E 3
    return(elist);
} /* end DBRead */
I 3


/*               
 * Interpret element type in string s.
 * Old file format consisted of integer element types.
 * New file format has literal names for element types.
 */                           
DBGetType(s)     
register char *s;
{        
    if (isdigit(s[0]) || (s[0] == '-'))         /* old element format or EOF */
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
                    return(-1);
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
                    return(-1);
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
                    return(-1);
            }          
        default:       
            error("unknown element type");
            return(-1);
    }                  
}  /* end DBGetType */ 
E 3

D 2

E 2
I 2

E 2
DBBounded(elt, x1, y1, x2, y2)
ELT *elt;
float x1, y1, x2, y2;
/*
 *      This routine returns true if all points in elt are bounded by
 * the rectangle who diagonal is formed by (x1, y1) and (x2, y2).
 */

{
	POINT *p1;
	float lox, loy, hix, hiy;

	lox = (x1 < x2) ? x1 : x2;
	loy = (y1 < y2) ? y1 : y2;
	hix = (x1 > x2) ? x1 : x2;
	hiy = (y1 > y2) ? y1 : y2;
	p1 = elt->ptlist;
	while ( !Nullpoint(p1) )
	{
		if (p1->x < lox) return(FALSE);
		if (p1->x > hix) return(FALSE);
		if (p1->y < loy) return(FALSE);
		if (p1->y > hiy) return(FALSE);
		p1 = PTNextPoint(p1);
	}  /* end while */;
	return(TRUE);
}  /* end DBBounded */
E 1
