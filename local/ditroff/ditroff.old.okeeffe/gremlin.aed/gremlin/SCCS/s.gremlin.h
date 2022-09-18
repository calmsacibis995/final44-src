h04522
s 00001/00000/00110
d D 1.3 84/05/29 14:12:21 slatteng 3 2
c added capability of reading in and (sorta) displaying polygons
e
s 00001/00002/00109
d D 1.2 83/04/18 15:31:43 slatteng 2 1
c DLS takeover
e
s 00111/00000/00000
d D 1.1 83/04/18 13:52:13 slatteng 1 0
c date and time created 83/04/18 13:52:13 by slatteng
e
u
U
t
T
I 1
D 2

/* gremlin.h -
E 2
I 2
/* %W%	%G%
E 2
 *
 *
 * This file contains standard definitions used by the gremlin program.
 *
 * (modified from software written by John Ousterhout for the caesar
 * program)
 */

#include <stdio.h>
#include <math.h>

#define TRUE  1
#define FALSE 0

#define nullelt -1
#define nullpt  -1
#define nullun   NULL

#define rmask1 00
#define rmask2 00
#define rmask3 00

#define bordstyle   5
#define gridstyle   9
#define pointstyle 10
#define eraseany    0

#define gridmask  0200
#define pointmask 0100
#define setmask    040
#define textmask    07
#define linemask    07

#define pointchar 1
#define halfpoint 3
#define numspace  6

#define BOTLEFT 0
#define BOTRIGHT 1
#define CENTCENT 2
#define VECTOR 3
#define ARC 4
#define CURVE 5
I 3
#define POLYGON 6
E 3
#define TOPLEFT 10
#define TOPCENT 11
#define TOPRIGHT 12
#define CENTLEFT 13
#define CENTRIGHT 14
#define BOTCENT 15
#define TEXT(t) ( (t <= CENTCENT) || (t >= TOPLEFT) )
/* WARNING * WARNING * WARNING * WARNING * WARNING * WARNING * WARNING 
 *    The above (TEXT) test is dependent on the relative values of the 
 *    constants and will have to change if these values change or if new
 *    commands are added with value greater than BOTCENT
 */

#define NOADJ 0
#define HORZ  1
#define VERT  2
#define MAN   3

#define NUSER 4
#define NFONTS 4
#define NBRUSHES 6
#define NSIZES 4
#define NJUSTS 9

#define himask linemask
#define hicolor 6

#define ADD 1
#define DELETE 2
#define MOD 3

/* The following represents the maximum distance a point may be from another
 * and still be affected by gravity.  The distance is represented as the
 * square of the number of pixels (32) of the actual distance.  
 */

#define MAXGDIST 32*32

typedef struct point
        {
               float x, y;
               struct point *nextpt;
        } POINT;

typedef struct elmt
        {
               int type, brushf, size, textlength;
               char *textpt;
               POINT *ptlist;
               struct elmt *nextelt, *setnext;
        } ELT;


typedef struct unlt
        {
             int action;
             ELT *(*dbase), *oldelt, *newelt;
             struct unlt *nextun;
        } UNELT;

typedef struct {
    int tx_x;		/* First column of field */
    int tx_y;		/* Row containing field */
    int tx_size;	/* Size of field in characters */
    } TXFIELD;
 
E 1
