/**********************************************************************
 *
 * `High-level' font manipulation
 *
 *********************************************************************/

#include "the.h"


public struct	dev dev;
public struct	Font *fontbase[NFONTS+1];

public short	*pstab;			/* point size table pointer		*/
public int	size = 1;		/* point size (pstab index)		*/
public int	font = 1;

public int	nsizes;			/* num of sizes dev can print		*/
public int	nfonts = 1;		/* num of fonts dev can print		*/
public int	smnt;			/* index of 1st special font		*/
public int	nchtab;
public char	*chname;
public short	*chtab;
public char	*fitab[NFONTS+1];	/* font inclusion tab: ascii -> ch #	*/
public char	*widthtab[NFONTS+1];	/* width tables for each font		*/
public char	*codetab[NFONTS+1];	/* device codes				*/
public short	*fonttab[NFONTS+1];	/* font codes				*/
public struct	fontname fontname[NFONTS+1];	/* fonts and thier positions	*/


extern char	*devname;
extern char	*fontdir;
extern int	debug, dbg;



/*
 * fileinit:	read in font and code files, etc.
 *		Must open table for device, read in resolution,
 *		size info, font info, etc. and set params.
 *		Also read in font name mapping.
*/

fileinit()	/* read in font and code files, etc. */
{
	int i, fin, nw;
	char *filebase, *p, *malloc();
	char temp[60];

	/* open table for device,
	/* read in resolution, size info, font info, etc.
	/* and set params
	*/
	sprintf(temp, "%s/dev%s/DESC.out", fontdir, devname);
	if ((fin = open(temp, 0)) < 0)
		error(FATAL, "can't open tables for %s\n", temp);
	read(fin, &dev, sizeof(struct dev));
	nfonts = dev.nfonts;
	nsizes = dev.nsizes;
	nchtab = dev.nchtab;
	if((filebase = malloc(dev.filesize)) == (char *) 0)
		error(FATAL, "Malloc can't find the room!");
					/* enough room for whole file */
	read(fin, filebase, dev.filesize);	/* all at once */
	pstab = (short *) filebase;
	chtab = pstab + nsizes + 1;
	chname = (char *) (chtab + dev.nchtab);
	p = chname + dev.lchname;
	if(nfonts > NFONTS) 
		error(FATAL, "Can't have that many fonts!");
	for (i = 1; i <= nfonts; i++) {
		fontbase[i] = (struct Font *) p;
		nw = *p & BMASK;	/* 1st thing is width count */
		if (smnt == 0 && fontbase[i]->specfont == 1)
			smnt = i;	/* first special font */
		p += sizeof(struct Font);	/* that's what's on the beginning */
		widthtab[i] = p;
		codetab[i] = p + 2 * nw;
		fitab[i] = p + 3 * nw;
		p += 3 * nw + dev.nchtab + 128 - 32;
		if(fontbase[i]->fonttab == 1) {	/*MC:jna There is a fonttable */
			fonttab[i] = (short *)p;	/*MC:jna get it */
			p += nw * sizeof( short );	/* and skip it */
		}
		t_fp(i, fontbase[i]->namefont, fontbase[i]->intname);
#ifdef DEBUGABLE
		if(dbg > 5) fontprint(i);
#endif 
	}
	/*MC:jna
	 *
	 * Make space for the font cache for NCH characters
	 * also reserve space for fonttable, if any is to come
         *
	 */
	fontbase[0] = (struct Font *) malloc(3*255 + dev.nchtab + (128-32) + sizeof (struct Font) + 255 * sizeof( short));
	if (fontbase[0] ==(struct Font *) 0)
		error(FATAL, "No room for fontbase!");
	widthtab[0] = (char *) fontbase[0] + sizeof (struct Font);
	fontbase[0]->nwfont = 255;
	fontbase[0]->fonttab = 2;	/* there is room for a fonttable! */
	close(fin);
}



#ifdef DEBUGABLE

fontprint(i)	/* debugging print of font i (0,...) */
{
	int j, n;
	char *p;

	fprintf(stderr,"font %d:\n", i);
	p = (char *) fontbase[i];
	n = fontbase[i]->nwfont & BMASK;
	fprintf(stderr,
	    "base=0%o, nchars=%d, spec=%d, name=%s, widthtab=0%o, fitab=0%o\n",p,
	    n,fontbase[i]->specfont,fontbase[i]->namefont,widthtab[i],fitab[i]);
	fprintf(stderr,"widths:\n");
	for (j=0; j <= n; j++) {
		fprintf(stderr," %2d", widthtab[i][j] & BMASK);
		if (j % 20 == 19) fprintf(stderr,"\n");
	}
	fprintf(stderr,"\ncodetab:\n");
	for (j=0; j <= n; j++) {
		fprintf(stderr," %2d", codetab[i][j] & BMASK);
		if (j % 20 == 19) fprintf(stderr,"\n");
	}
	fprintf(stderr,"\nfitab:\n");
	for (j=0; j <= dev.nchtab + 128-32; j++) {
		fprintf(stderr," %2d", fitab[i][j] & BMASK);
		if (j % 20 == 19) fprintf(stderr,"\n");
	}
	if(fontbase[i]->fonttab == 1) {
		fprintf(stderr,"\nfonttab:\n");
		for (j=0; j <= n; j++) {
			fprintf(stderr," %4d", fonttab[i][j] );
		if (j % 20 == 19) fprintf(stderr,"\n");
		}
	}
	fprintf(stderr,"\n");
}
#endif



/* 
 * load font info for font s on position n (0...)
 */


loadfont(n, s, s1)	
int n;
char *s, *s1;
{
	char temp[60];
	int fin, nw, norig, forig;

	if (n < 0 || n > NFONTS)
		error(FATAL, "illegal fp command %d %s", n, s);
	if (strcmp(s, fontbase[n]->namefont) == 0)
		return;
	if (s1 == NULL || s1[0] == '\0')
		sprintf(temp, "%s/dev%s/%s.out", fontdir, devname, s);
	else
		sprintf(temp, "%s/%s.out", s1, s);
	if ((fin = open(temp, 0)) < 0)
		error(FATAL, "can't open font table %s", temp);
	norig = fontbase[n]->nwfont & BMASK;
	forig = fontbase[n]->fonttab;

	DBGPRINT(3,("nworig, %d, fonttaborig %d\n", norig, forig)); 
	/*
	 *MC:jna norig is the original amount of chars in
	 * the (premounted) font)
	 *
	 * first geuss there is no fonttab
	 */
	read(fin, fontbase[n], 3*norig + nchtab+128-32 + sizeof(struct Font));
	if ((fontbase[n]->nwfont & BMASK) > norig || (forig == 0 && fontbase[n]->fonttab == 1))
		error(FATAL, "Font %s too big for position %d\n", s, n);
		/*
		 *MC:jna This means it is wise to make the default mounted
		 * fonts larger then any other mounttable fonts.
		 * And because of the kludge with the fonttable,
		 * Make sure that they all contain fonttables!
		 * It will make your life easier.
		 */
	nw = fontbase[n]->nwfont & BMASK;

	DBGPRINT(3,("nw %d\n", nw));

	if(fontbase[n]->fonttab == 1) {
		lseek(fin, 0L, 0);
		read(fin, fontbase[n], 3*norig + nchtab+128-32 + nw*sizeof(short) + sizeof(struct Font));
		/*
		 * There turned out to be a fonttab, so we have to read it in
		 *MC:jna a bit stupid, but the laziest way (for me)
		 */
	}
	close(fin);
	widthtab[n] = (char *) fontbase[n] + sizeof(struct Font);
	codetab[n] = (char *) widthtab[n] + 2 * nw;
	fitab[n] = (char *) widthtab[n] + 3 * nw;
	if(fontbase[n]->fonttab == 1)
		fonttab[n] = (short *) (widthtab[n] + 3*nw + nchtab+128-32);
	t_fp(n, fontbase[n]->namefont, fontbase[n]->intname);
	fontbase[n]->nwfont = norig;	/* so can later use full original size */
	if(fontbase[n]->fonttab == 0 && forig != 0)
		fontbase[n]->fonttab = 2;
					/* so we signal that there is place
					 * for a fonttab! */
}
