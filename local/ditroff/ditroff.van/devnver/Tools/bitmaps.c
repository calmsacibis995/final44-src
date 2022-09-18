/******************************************************************
 *
 * bitmaps.c
 *
 * Read the rects files and produce bitmap files.
 *
 * Usage: bitmaps <fontno>-<size> ...
 *
 ******************************************************************/
#include <stdio.h>
#include "../defs.h"
#include "chardata.h"


FILE 	*outfp;		/* where to write the output */
int	msize;		/* master size of input font; used by scale */

extern struct chardata *findfont();


main(argc,argv)
int argc;
char *argv[];
{
	char outname[50];
	int  fontnum, fontsize;
	struct chardata *f; 
	

	while( --argc )
	{
		++argv;

		sscanf(*argv, "%d-%d", &fontnum, &fontsize);

		f = findfont( fontnum, fontsize );

		sprintf(outname, "%s/%d/%d", BITS, fontnum, fontsize);
		if((outfp = fopen(outname, "w")) == 0)
			error("could not open %s\n", outname);

		writefont( f );
		fflush( outfp );
		fclose( outfp );
	}
}



/*
 * write the font in the bits format used by ndver
 *
 */

writefont( ch )
struct chardata *ch;
{
	int    len, wrtn;

	while( ch != (struct chardata *)0)
	{
		len = ch->nbytes;

		if( fwrite(ch, sizeof(*ch), 1, outfp) != 1 )
			error("could not write ch struct");

		if((wrtn = fwrite(ch->cbitmap, sizeof(char), len, outfp)) != len )
		{
			error("bad write of bitmap, char %d len %d wrtn %d", ch->charno, len, wrtn);
		}

		ch = ch->nextchar;
	}
}



/* scale from point size msize at Harris resolution to point size a at
 * versatec resolution.
 */
double
scale(a)	
int a;
{
	return( (msize * 720.0) / (200.0 * a) );
}

