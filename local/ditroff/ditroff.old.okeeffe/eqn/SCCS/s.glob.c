h46376
s 00001/00000/00030
d D 1.4 84/07/23 18:02:35 slatteng 4 3
c made minimum granularity of vertical movement a parameter read from DESC file
e
s 00001/00001/00029
d D 1.3 83/10/07 21:29:38 slatteng 3 2
c set default printer to 'va' not 'var'
e
s 00003/00009/00027
d D 1.2 83/08/15 16:28:16 slatteng 2 1
c removed all device-dependent code.  That means anything that was
c optimized for a particular typesetter is gone, and eqn now looks up the
c output device in a device file, like everybody else.
e
s 00036/00000/00000
d D 1.1 83/08/15 10:12:14 slatteng 1 0
c date and time created 83/08/15 10:12:14 by slatteng
e
u
U
t
T
I 1
#include "e.h"

int	dbg;	/* debugging print if non-zero */
int	lp[80];	/* stack for things like piles and matrices */
int	ct;	/* pointer to lp */
int	used[100];	/* available registers */
int	ps;	/* default init point size */
int	deltaps	= 3;	/* default change in ps */
int	gsize	= 10;	/* default initial point size */
int	gfont	= ITAL;	/* italic */
int	ft;	/* default font */
D 2
#ifdef	APS
	int	ttype	= DEVAPS;	/* type of typesetter today */
	int	res	= 723;	/* resolution of typesetter; dflt = 202 */
	int	minsize	= 5;	/* min size it can handle; ditto */
#else
	int	ttype	= DEVCAT;	/* type of typesetter today */
	int	res	= 200;	/* resolution of typesetter; dflt = 202 */
	int	minsize	= 6;	/* min size it can handle; ditto */
#endif
E 2
I 2
D 3
char	*device ="var";	/* device for "res" and "minsize" (default = varian) */
E 3
I 3
char	*device ="va";	/* device for "res" and "minsize" (default = varian) */
E 3
int	res	= 0;	/* resolution of typesetter; no default */
int	minsize	= 0;	/* min size it can handle; no default */
I 4
int	minvert	= 1;	/* min size it can move vertically; no default */
E 4
E 2
FILE	*curfile;	/* current input file */
int	ifile;
int	linect;	/* line number in file */
int	eqline;	/* line where eqn started */
int	svargc;
char	**svargv;
int	eht[100];
int	ebase[100];
int	lfont[100];
int	rfont[100];
int	eqnreg;	/* register where final string appears */
int	eqnht;	/* inal height of equation */
int	lefteq	= '\0';	/* left in-line delimiter */
int	righteq	= '\0';	/* right in-line delimiter */
int	lastchar;	/* last character read by lex */
int	markline	= 0;	/* 1 if this EQ/EN contains mark; 2 if lineup */
E 1
