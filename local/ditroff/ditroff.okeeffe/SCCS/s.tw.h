h22923
s 00001/00000/00034
d D 2.2 86/08/15 12:07:43 jaap 3 2
c Page feeder assist added (eject)
e
s 00034/00030/00000
d D 2.1 85/07/18 14:31:22 jaap 2 1
c Edition 8 Version of troff (May 1985), (Dennis did the caching). 
c Local hacks from jaap.
e
s 00030/00000/00000
d D 1.1 85/07/17 17:55:14 jaap 1 0
c date and time created 85/07/17 17:55:14 by jaap
e
u
U
t
T
I 1
D 2
/* typewriter driving table structure*/
struct {
	int bset;
	int breset;
	int Hor;
	int Vert;
	int Newline;
	int Char;
	int Em;
	int Halfline;
	int Adj;
	char *twinit;
	char *twrest;
	char *twnl;
	char *hlr;
	char *hlf;
	char *flr;
	char *bdon;
	char *bdoff;
	char *iton;
	char *itoff;
	char *ploton;
	char *plotoff;
	char *up;
	char *down;
	char *right;
	char *left;
	char *codetab[256-32];
	char *zzz;
	} t;
E 2
I 2
/* typewriter driving table structure */

#define	NROFFCHARS	350	/* ought to be dynamic */

extern struct t {
	int	bset;		/* these bits have to be on */
	int	breset;		/* these bits have to be off */
	int	Hor;		/* #units in minimum horiz motion */
	int	Vert;		/* #units in minimum vert motion */
	int	Newline;	/* #units in single line space */
	int	Char;		/* #units in character width */
	int	Em;		/* ditto */
	int	Halfline;	/* half line units */
	int	Adj;		/* minimum units for horizontal adjustment */
	char	*twinit;	/* initialize terminal */
	char	*twrest;	/* reinitialize terminal */
	char	*twnl;		/* terminal sequence for newline */
	char	*hlr;		/* half-line reverse */
	char	*hlf;		/* half-line forward */
	char	*flr;		/* full-line reverse */
	char	*bdon;		/* turn bold mode on */
	char	*bdoff;		/* turn bold mode off */
	char	*iton;		/* turn italic mode on */
	char	*itoff;		/* turn italic mode off */
	char	*ploton;	/* turn plot mode on */
	char	*plotoff;	/* turn plot mode off */
	char	*up;		/* sequence to move up in plot mode */
	char	*down;		/* ditto */
	char	*right;		/* ditto */
	char	*left;		/* ditto */
I 3
	char	*eject;		/* sequence to eject page */
E 3

	char	*codetab[NROFFCHARS-128];
	char	width[NROFFCHARS];
} t;
E 2
E 1
