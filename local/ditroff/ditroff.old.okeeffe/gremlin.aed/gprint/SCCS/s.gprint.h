h10562
s 00001/00001/00105
d D 1.5 83/05/22 19:06:38 slatteng 5 4
c change #-of-lines to 1600, from 1536
e
s 00025/00007/00081
d D 1.4 83/05/13 17:55:49 slatteng 4 3
c restore size of varian pictures => 4 scale factor, etc.
e
s 00010/00005/00078
d D 1.3 83/03/30 13:36:46 ralph 3 2
c modified mapping and scale factors to fit in square arrays.
e
s 00031/00038/00052
d D 1.2 83/03/02 13:46:03 ralph 2 1
c this version uses remote line printer software.
e
s 00090/00000/00000
d D 1.1 83/03/02 13:27:48 ralph 1 0
c date and time created 83/03/02 13:27:48 by ralph
e
u
U
t
T
I 1
D 2
/* gprint.h -
E 2
I 2
D 4
/*	%M%	%I%	%E%
E 4
I 4
/* %M%	%I%	%E%
E 4
E 2
 *
D 2
 *
E 2
 * This file contains standard definitions used by the gprint program.
 */

D 3
#define poffset ( (device == 'V') ? 10 : 117 )
#define Ymax 483
E 3
D 4
#define Xmax 511
I 3
#define Ymax 483
E 3
#define xorn(x,y) Orientation ? (y) : (x) 
D 3
#define yorn(x,y) Orientation ? (Ymax - ((x) - poffset)) : (y) 
D 2
#define    mapx(x)    ((DevRange*(((x) * scale)-botx)/del)+centx)
#define    mapy(y)    ((DevRange*(del-((y) * scale)+boty)/del)-centy)
E 2
I 2
#define mapx(x) ((DevRange*(((x) * scale)-botx)/del)+centx)
#define mapy(y) ((DevRange*(del-((y) * scale)+boty)/del)-centy)
E 3
I 3
#define yorn(x,y) Orientation ? (x) : (y) 
#define mapx(x) (((x) * scale)-orgx)
#define mapy(y) (((y) * scale)-orgy)
E 4
I 4
#define Vxlen		2048		/* varian dimensions */
D 5
#define Vylen		1536
E 5
I 5
#define Vylen		1600
E 5
#define Vbytperlin	264

#define Wxlen		2048		/* versatec dimensions */
#define Wylen		2048
#define Wbytperlin	880

#define	MenuSize	116		/* screen dimensions */
#define HXmin		0
#define HXmax		511
#define HYmin		0
#define HYmax		(511 - MenuSize)
#define VXmin		MenuSize
#define VXmax		511
#define VYmin		0
#define VYmax		511

						/* translation stuff */
#define xorn(x,y)	Orientation ? ((y) - VYmin) : ((x) - HXmin)
#define yorn(x,y)	Orientation ? ((x) - VXmin) : (HYmax - (y))
#define mapx(x)		(((x) * scale)-orgx)
#define mapy(y)		(((y) * scale)-orgy)

E 4
E 3
E 2
#define STYLES 6
#define SIZES 4
#define FONTS 4
#define SOLID -1
D 2
#define DOTTED 004   /* 014 */
#define DASHED 020   /* 034 */
#define DOTDASHED 024 /* 054 */
E 2
I 2
#define DOTTED 004	/* 014 */
#define DASHED 020	/* 034 */
#define DOTDASHED 024	/* 054 */
E 2
#define LONGDASHED 074
D 2
#define    SETSTATE    (('v'<<8)+1)
E 2

#include <stdio.h>
#include <math.h>

D 2
#define TRUE  1
#define FALSE 0
E 2
I 2
#define TRUE	1
#define FALSE	0
E 2

D 2
#define nullelt -1
#define nullpt  -1
#define nullun   NULL
E 2
I 2
#define nullelt	-1
#define nullpt	-1
#define nullun	NULL
E 2

D 2
#define BOTLEFT 0
E 2
I 2
#define BOTLEFT	0
E 2
#define BOTRIGHT 1
#define CENTCENT 2
#define VECTOR 3
#define ARC 4
#define CURVE 5
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

#define NUSER 4
#define NFONTS 4
#define NBRUSHES 6
#define NSIZES 4
#define NJUSTS 9

#define ADD 1
#define DELETE 2
#define MOD 3

D 2
typedef struct point
        {
               float x, y;
               struct point *nextpt;
        } POINT;
E 2
I 2
typedef struct point {
	float x, y;
	struct point *nextpt;
} POINT;
E 2

D 2
typedef struct elmt
        {
               int type, brushf, size, textlength;
               char *textpt;
               POINT *ptlist;
               struct elmt *nextelt, *setnext;
        } ELT;
E 2
I 2
typedef struct elmt {
	int type, brushf, size, textlength;
	char *textpt;
	POINT *ptlist;
	struct elmt *nextelt, *setnext;
} ELT;
E 2

I 2
typedef struct unlt {
	int action;
	ELT *(*dbase), *oldelt, *newelt;
	struct unlt *nextun;
} UNELT;
E 2

D 2
typedef struct unlt
        {
             int action;
             ELT *(*dbase), *oldelt, *newelt;
             struct unlt *nextun;
        } UNELT;

E 2
typedef struct {
D 2
    int tx_x;		/* First column of field */
    int tx_y;		/* Row containing field */
    int tx_size;	/* Size of field in characters */
    } TXFIELD;
 
E 2
I 2
	int tx_x;	/* First column of field */
	int tx_y;	/* Row containing field */
	int tx_size;	/* Size of field in characters */
} TXFIELD;
I 3

#define DBNextElt(elt) elt->nextelt
#define DBNextofSet(elt) elt->setnext
#define DBNullelt(elt) (elt == NULL)
#define Nullpoint(pt)  (pt->x == nullpt)
#define PTNextPoint(pt) pt->nextpt
E 3
E 2
E 1
