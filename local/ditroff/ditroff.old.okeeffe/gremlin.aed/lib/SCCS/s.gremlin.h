h02295
s 00048/00000/00000
d D 1.1 84/12/14 13:24:39 opcode 1 0
c date and time created 84/12/14 13:24:39 by opcode
e
u
U
t
T
I 1
/*
 * %W%	%G%
 *
 * Gremlin library routines header file - 
 * for use with /usr/local/lib/libgremlin.a
 *
 * Mark Opperman (opcode@monet.BERKELEY)
 *
 */

extern FILE *gr_open();
extern gr_close();
extern gr_vector();
extern gr_curve();
extern gr_arc();
extern gr_circle();
extern gr_polygon();
extern gr_text();

#define GR_ERROR -1
#define GR_OK 0

#define SUN_GREMLIN 0
#define AED_GREMLIN 1

#define HORZ_ORIENT 0
#define VERT_ORIENT 1

#define BOTLEFT 0
#define BOTRIGHT 1
#define CENTCENT 2
#define VECTOR 3
#define ARC 4
#define CURVE 5
#define POLYGON 6
#define TOPLEFT 10
#define TOPCENT 11
#define TOPRIGHT 12
#define CENTLEFT 13
#define CENTRIGHT 14
#define BOTCENT 15

#define DOTTED 1
#define DOTDASHED 2
#define THICK 3
#define DASHED 4
#define NARROW 5
#define MEDIUM 6
E 1
