h09445
s 00009/00009/00057
d D 1.4 93/07/27 09:16:20 bostic 4 3
c checkpoint; Mike Karels left this checked out.
e
s 00001/00000/00065
d D 1.3 86/11/13 15:42:55 jaap 3 2
c Fixed lf again (Table too wide gave wrong name)
e
s 00002/00000/00063
d D 1.2 85/10/02 14:40:16 jaap 2 1
c Removed a lot of commented out debug code, takes now -d argument
c for debug output. some tidy up.
e
s 00063/00000/00000
d D 1.1 85/10/01 18:09:38 jaap 1 0
c date and time created 85/10/01 18:09:38 by jaap
e
u
U
t
T
I 1
D 4
/*	%W% (CWI) %E%	*/
E 4
I 4
/*	%W% (Berkeley) %G%	*/
E 4
#define max(a,b)	((a) > (b) ? (a) : (b))
#define min(a,b)	((a) < (b) ? (a) : (b))
D 4
#define MAXLIN 200
E 4
I 4
#define MAXLIN 1024
E 4
/*
 * Maximum columns to be output
 */
D 4
#define MAXCOL 30
E 4
I 4
#define MAXCOL 64
E 4

/*
 * MAXCOL is amount of columns to be specified per column
 *
 *  for relation of MAXCOL and MAXHEAD, see next example:
 *	.TS
	l l l		)
	a s s		) Maximum MAXHEAD
	r r n.		)
	-----
	  |
	  Maximum MAXCOL
 *
 * Every table can be MAXCOL, with in each column MAXHEAD
 * specification (lines)
 *
 * Don't make MAXCOL bigger width adjusting nregs in globals.c (bwk)
 */

D 4
#define MAXHEAD	44
#define MAXCHS		2000
#define MAXRPT		100
#define CLLEN		10
E 4
I 4
#define MAXHEAD	64
#define MAXCHS		8192
#define MAXRPT		256
#define CLLEN		128
E 4
#define SHORTLINE	4
#define	ZEROW		001
#define HALFUP		002
#define	CTOP		004
#define CDOWN		010
#define CLEFT		000
#define CMID		001
#define CRIGHT		002
#define S1		31
#define S2		32
#define TMP		38
#define SF		35
#define SL		34
#define LSIZE		33
#define SIND		37
#define SVS		36
#define LEFT 1
#define RIGHT 2
#define THRU 3
#define TOP 1
#define BOT 2
D 4
#define MACROS "/usr/lib/tmac.s"
#define PYMACS "/usr/lib/tmac.m"
E 4
I 4
#define MACROS "/usr/share/tmac/tmac.s"
#define PYMACS "/usr/share/tmac/tmac.m"
E 4

/* devices supported */
I 3
#define DEVPSC	3
E 3
#define DEVVER	2
#define HARRIS	1
#define CAT	0

struct colstr {
	char *col, *rcol;
	};
I 2

#define dprint	if(dbg)printf
E 2
E 1
