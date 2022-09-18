#include <stdio.h>
#include <ctype.h>
#include "dev.h"
#include <strings.h>
#include <math.h>

/* #define DEBUGABLE 		/* NO */

/*
 *  This is gross and ugly, but it makes the code _look_ cleaner...
 *  call like  DBGPRINT(1,("format string with %d and %c\n", intfoo, charfoo));
 */

#ifdef DEBUGABLE
#define DBGPRINT(level, s)	if(dbg>level) eprintf s
#else
#define DBGPRINT(level, s)
#endif

#define DRIVER			/* Yes, we're driving directly */
#define	NFONTS	65		/* total number of fonts useable */
#define	MAXSTATE 6		/* number of environments rememberable */
#define RESTART	1		/* upon exit, return either RESTART */
#define ABORT	2		/*     or ABORT */
#define	FATAL	1		/* type of error */
#define NONFATAL 0

#define	BMASK	0377		/* byte grabber */
#define NMASK	077

#define DISPATCHSIZE	256			/* must be a power of two	*/
#define CHARMASK	(DISPATCHSIZE-1)
#define OUTFILE		fileno (stdout)

#define	RES	200				/* dots per inch of device	*/
#define RASTER_LENGTH	2112			/* device line length		*/
#define BYTES_PER_LINE	(RASTER_LENGTH/8)

#define BAND		2.2 			/* length of a band in inches	*/
#define NLINES		(int)	(BAND*RES)	/* BAND" long band needs..	*/
#define BUFFER_SIZE	(NLINES*BYTES_PER_LINE)

#define BUFTOP		(&buffer[0])
#define BUFBOTTOM	(&buffer[BUFFER_SIZE] - 1)
#define buf0p		BUFTOP			/* vorigin in circular buffer	*/
#define PAGEEND		1			/* flags to `outband'		*/
#define OVERBAND	0


/* 
 * used in dev.c and put.c
 */

struct fontname {
	char *name;
	int number;
};



/* note: unlike previous versions of dver,
 * these motions are in units of the input resolution,
 * not the units of the versatec resolution.
 * Translation occurs in putcode() and point().
 */

#define  hmot(n)	(hpos += (n))
#define  hgoto(n)	(hpos = (n))
#define  vmot(n)	vgoto(vpos + (n))

/* scale from the virtual (input) resolution to
 * the physical versatec resolution
 */
#define	PHYS(x)	(int)( (double)((RES*(x)) + virtRES/2) / virtRES )


#define  public			/* used for public globals */
#define  private	static  /* used for private globs  */
