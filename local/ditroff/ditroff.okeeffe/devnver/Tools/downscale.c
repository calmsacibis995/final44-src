/***************************************************************
 *
 * downscale.c
 *
 * routines to read a font in rects format, create scaled
 * bitmaps from them, and return a linked list of chardata structs
 *
 * the routine scale() must be provided, to scale from Harris
 * resulution to desired resolution (the variable `msize' is
 * set to the point size of the input font).
 *
 **************************************************************/
#include <sys/types.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <stdio.h>
#include <errno.h>
#include <math.h>
#include "../defs.h"
#include "chardata.h"


/*
 * Definitions of the data types for rects and bitmaps
 */

struct bitmapdata {
	char *cbitmap;		/* bitmap of char	*/
	int  nbytes;
	int  width, height;
};

struct Chrects {  
	struct Rect *rectp;
	int Nstructs;
	int XO;
	int YO;
	int X;
	int Y;
};


#define ABXO 	128
#define ABYO 	256

typedef unsigned int	nat;

#define Maxnat	1024
#define BYTE	8
#define MAX	(Maxnat * (Maxnat/BYTE) + 1)

#define CHARSIZE (sizeof(char))
#define Threshold .2

#define getbit(cm,i) 	(((unsigned)cm[(i)/BYTE] & (1 << ((i)%BYTE))) >> ((i)%BYTE))
#define setbit(i) 	(bmd->cbitmap[(i)/BYTE] |=  (1 << ((i)%BYTE))) 
#define clrbit(i) 	(bmd->cbitmap[(i)/BYTE] &= ~(1 << ((i)%BYTE)))
#define testbit(i) 	((bmd->cbitmap[(i)/BYTE] & (1 << ((i)%BYTE))) >> ((i)%BYTE))


extern char 		*malloc(), *calloc();
extern long 		lseek();
extern double		scale();
struct bitmapdata	*balloc(), *downscale();
struct chardata 	*loadrects(), *challoc(), *makechar();
struct Chrects   	*chralloc();
char 			*getfile();

extern int	errno;
extern int	msize;



/*
 * take a chrects struct and produce a scaled bitmap.
 *
 */

struct bitmapdata *
downscale(factor,chrect)
float factor;
struct Chrects *chrect;
{
	float vf, hf;
	register nat nv, nh;
	nat oxO, ox, oyO, oy, nxO, nx, nyO, ny;
	struct bitmapdata *bmd;
	int bwidth;
	int i, j;

	bmd = balloc();
	bmd->nbytes = 0;

	bmd->height = floor(chrect->Y/factor +.5);
	if(!bmd->height)
		bmd->height =1;
	vf = (float)chrect->Y/bmd->height;

	bmd->width = floor(chrect->X/factor + .5);
	if(!bmd->width)
		bmd->width = 1;
	hf = (float)chrect->X/bmd->width;
	bwidth = (bmd->width + 7)/BYTE;

	if((bmd->nbytes = (bmd->height + 1) * bwidth ) > MAX)
		error( "Bitmap too large");

	if((bmd->cbitmap = calloc(bmd->nbytes, 1)) == (char *) 0)
		error("downscale -- not enough space");

	for(i = 0; i < chrect->Nstructs; i++) {
		oyO = chrect->rectp->yO;
		oy = chrect->rectp->y;
		oxO = chrect->rectp->xO;
		ox = chrect->rectp->x;

		ny = floor(oy/vf + .5);
		if (!ny && oy/vf >= Threshold)
			ny = 1;
		nyO = floor(((2 * oyO + oy)/vf - ny) * .5 + .5);
		nx = floor(ox/hf + .5);
		if (!nx && ox/hf >= Threshold)
			nx = 1;
		nxO = floor(((2 * oxO + ox)/hf - nx) * .5 + .5);
		for (nv = nyO; nv < nyO + ny; nv++ ) {
			for (nh = nxO; nh < nxO + nx; nh++ ) {
				if((j = nv * bwidth * BYTE + nh) > MAX)
					error("bitmap too large");
				setbit(j);
			}
		}
		chrect->rectp++;
	}

	return(bmd);
}


/*
 *  findfont(f, size): Find and load the rects file for this font,
 *  returning a the scaled bitmaps.
 */


struct chardata *
findfont(f, size)
int f, size;
{
	char file[200], *fbuf;

	sprintf(file,"%s/%d-14.rect", RECT, f);

	if( (fbuf = getfile(file)) != 0 )
	{
		return(	loadrects( size, 14, fbuf ));
	}
	else
	{
		/* a couple of fonts are in mastersize 10 */

		sprintf(file, "%s/%d-10.rect", RECT, f);
		if( (fbuf = getfile(file)) != 0 )
		{
			return( loadrects( size, 10, fbuf ));
		}
	}
	error("Cannot get font %d\n", f);
}



/*
 * loadrects: load all the rectangles for the physical font and
 * size requested.
 */

struct chardata *
loadrects( psize, ms, filebuf )
int psize, ms;
char *filebuf;
{
	struct chardata *c;
	struct chardata *firstc;
	struct chardata *prev;
	struct Header *head;
	int charno;

	head = (struct Header *) filebuf;
	if(head->magic != MAGIC)
		error("This is not a rectangular character file!\n");

	msize = ms;		/* used for scaling by downscale */

	firstc = (struct chardata *)0;
	for(charno = 1; charno <=128; charno++)
	{
		c = makechar(charno, psize, filebuf);
		if( c != (struct chardata *)0 )
		{
			if( firstc == (struct chardata *)0 )
				firstc = c;
			else
				prev->nextchar = c;
			prev = c;
		}
	}

	free( filebuf );
	return(firstc);
}
	

	
/*
 * makechar( charno, size, filebuf )
 *
 * take the rects data for char charno (currently in filebuf), and
 * scale it to create the bitmap and associated data.
 * Also transpose the bits in each byte of the bitmap.
 */

#include "flip.h"	/* the constant flip array */

struct chardata *
makechar(charno, size, filebuf)
int charno, size;
char *filebuf;
{
	float  factor;
	struct bitmapdata *bmd;
	struct Chrects *chrect; 
	struct chardata *c;
	struct Chars *p;
	int    xo, yo;
	int    cnt;
	unsigned char   *pt;

	/* 
	 * get the rects data, we hope
	 */
	p = (struct Chars *)(filebuf + sizeof(struct Header) +  
				          (charno-1) * sizeof(struct Chars));

	if(!p->offset) {	/* then there wasn't really anything there */
		return((struct chardata *) 0);
	}

	/* 
	 * make a Chrects structure for downscale
	 */
	chrect = chralloc(); 
	chrect->rectp = (struct Rect *)(filebuf + p->offset);	

	chrect->Nstructs = p->Nstructs;
	chrect->XO       = p->XO;
	chrect->YO       = p->YO;
	chrect->X        = p->X;
	chrect->Y        = p->Y;

	/*
	 *  create a bitmap in the appropriate size;
	 */
	factor = scale( size );
	bmd = downscale(factor, chrect);
	free( chrect );				/* we're done with it */

	/*
	 * bit-wise transpose every byte in the
	 * bitmap, so bit order = byte order
	 */
	cnt = bmd->nbytes;
	pt  = (unsigned char *)bmd->cbitmap;
	for( ; cnt > 0 ; cnt--, pt++ )
	{
		*pt = flip[ *pt ];
	}

	/*
 	 *  and now init the chardata structure
	 */

	c = challoc();
	xo = chrect->XO - ABXO;  
	yo = ABYO - chrect->YO;

	c->XO       = floor((double)xo/factor);
	c->YO       = floor((double)yo/factor);
	c->height   = bmd->height;	
	c->width    = bmd->width;
	c->charno   = charno;
	c->nbytes   = bmd->nbytes;
	c->cbitmap  = bmd->cbitmap;
	c->nextchar = (struct chardata *) 0;

	return(c);
}



/*
 *  get the contents of the file, and return a pointer to them.
 *  If the file does not exist, 0 is returned.  All other errors
 *  result in death.
 *
 */


char *
getfile(file)
char *file;
{
	struct	stat statbuf; 
	char	*filebuf;
	int	fdi;

	if( stat(file, &statbuf) == -1 )
	{
		if( errno == ENOENT )
			return( (char *)0 );
		else
			error( "Can't get file status: %s", file);
	}

	if((statbuf.st_mode & S_IFMT) != S_IFREG)
		error( "File %s not a regular file", file);

	if((fdi = open(file, O_RDONLY)) < 0 )
		error( "Can not open %s", file );

	if((filebuf = malloc( (unsigned int)statbuf.st_size )) == (char *)0 )
		error( "Not enough room for file %s!", file);

	if(read(fdi, filebuf, (int)statbuf.st_size) != statbuf.st_size)
		error( "Read error on %s", file);

	(void) close( fdi );
	return( filebuf );
}



struct Chrects *
chralloc()
{

	register char *p;

	if((p = calloc(1, sizeof(struct Chrects))) == (char *)0)
		error( "Can't find enough room in chralloc.");
	return((struct Chrects *)p);
}




struct bitmapdata *
balloc()
{
	register char *p;

	if((p = malloc(sizeof(struct bitmapdata))) == (char *)0)
		error( "Can't find enough room in balloc.");
	return((struct bitmapdata *)p);
}



/*
 * print the bitmap of the character on the terminal screen
 */


printchar(c)
struct bitmapdata *c;
{
	nat v, h;
	int i, bytewidth, bitwidth;
	unsigned char *cm;	/* character map */

	if(c == (struct bitmapdata *) 0) 
		fprintf(stderr,"no char here\n");
	else 
	{
		cm = (unsigned char *)c->cbitmap;
		bytewidth = (c->width + 7)/BYTE;
		bitwidth = bytewidth*BYTE;

		fputc('\n', stderr);
		for (v = 0; v < c->height; v++) 
		{
			i = v * bytewidth * BYTE;
			for(h = 0;  h < bitwidth;  i++, h++) 
				fputc((getbit(cm,i) ? 'x' : ' '), stderr);

			fputc('\n', stderr);
		}
		fprintf(stderr,"@ End of character data\n");
	}
}



struct chardata *
challoc()
{
	register char *p;

	if(( p = malloc(sizeof(struct chardata))) == (char *)0)
		error( "challoc");
	return((struct chardata *)p);
}

