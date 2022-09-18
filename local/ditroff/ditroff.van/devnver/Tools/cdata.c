#ifndef lint
static char sccsid[] = "%W% (CWI) %E%";
#endif lint

#include <stdio.h>
#include "../defs.h"

/*
 * get the runlength from one font.
 * store it in a file in the directory called <fontname>
 * and the file <characterscode>
 *
 * arguments:
 *	<fontno>-<mastersize>
 *
 */

int dsk;

struct fhdentry fontdir[FHDDSZ];


int fontno, master;

main( argc, argv)
int argc; char **argv;
{

	if(!--argc) 
		error("No font specified");

	while(argc--) {
		argv++;
		sscanf(*argv, "%d-%d", &fontno, &master);
		/*
		printf("%d-%d\n", fontno, master);
		*/
		prfir(fontno, master);

	}
}

/*
 * print font header info record
 */
prfir(font, master)
int font, master;
{
	static int init;
	struct finfo *p;
	register int i;
	extern struct finfo *getfinfo();


	p = getfinfo(font, master);

	printf("Font information record font %d, master size %d\n", font, master);
	printf("\tFont number:\t%d", p->fntno);
	printf("\tMastercode:\t%d\n", p->mastszcode);
	printf("\tFontname:\t");
	printf("%o %o\n", p->faceident & 0377, (p->faceident >> 8) & 0377);
	printf("\tEm space:\t%d\tEn space:\t%d\n", p->emspace, p->enspace);
	printf("\tThin space:\t%d\tFigure space:\t%d\n", p->thinspace, p->figspace);
	printf("\tMaximum word space:\t%d\tMinimum word space:\t%d\n",
					p->minwordspace, p->maxwordspace);
	printf("\tNormal word space:\t%d\n", p->normwordspace);
	printf("\tKerning Factor:\t%d\n", p->kernfact);
	printf("\tPointsize 5:\t\%d\t", p->pt5);
	printf("\tPointsize 7:\t\%d\n", p->pt7);
	printf("\tPointsize 10:\t\%d\t", p->pt10);
	printf("\tPointsize 14:\t\%d\n", p->pt14);
	printf("\tPointsize 28:\t\%d\t", p->pt28);
	printf("\tPointsize 56:\t\%d\n", p->pt56);
	printf("\tNormal:\t%d\t", p->norm);
	printf("\tbold:\t%d\t", p->bold);
	printf("\tItalic:\t%d\n", p->italic);

	printf("\tAvailable characters:\n");
	printf("\tCode\tWidth\t");
	printf("Block\tSegment\n");
	for( i = 1; i <= 127; i++) {
		if( p->cgdentry[i]) {
			printf("\t%#4o\t%5d\t", i, p->relwidth[i % 128]);
			printf("%5d\t%4d\n",
			    cgdbno(p->cgdentry[i]), cgdseg(p->cgdentry[i%128]));
			getcgd(i, p->cgdentry[i%128]);
		}
	}
	if( p->cgdentry[0]) {
		printf("\t%#4o\t%5d\t", 128, p->relwidth[0]);
		printf("%5d\t%4d\n",
			cgdbno(p->cgdentry[0]), cgdseg(p->cgdentry[0]));
		getcgd(128, p->cgdentry[0]);
	}
}

/*
 * get runlengths of character i, store in on file <i.rle>
 */
#define CGDSIZE	32

getcgd(code, p)
int code;
Word p;
{
	int fd, i, j, k;
	char buf[BUFSIZ];
	Word seg[CGDSIZE];
	Word cnt;

	sprintf(buf, "%d-%d/%#o.rle", fontno, master, code);
	if(( fd = creat(buf, 0644)) < 0)
		error("Cannot create %s", buf);
	
	cnt = cgdseg(p);
	/*
	 * seek to the first Character Generation Segment
	 */
	seekchar( cgdbno(p), cnt);
	if(( j = read(dsk, seg, CGDSIZE * 2)) != CGDSIZE * 2)
		error("Read error character %#o (segment)", code);
	/*
	 * last word contains number of segments
	 */
	cnt = seg[CGDSIZE-1];

	if((j = write(fd, seg, ( CGDSIZE - 1) *2)) != (CGDSIZE -1) * 2)
		error("Write error character %#o (segment)", j);

	for( k = cnt -1; k > 0; --k) {
		if(( j = read(dsk, seg, CGDSIZE * 2)) != CGDSIZE * 2)
			error("Read error character %#o (segment)", code);
/*
for( i = 0; i< CGDSIZE; i++) {
printf("seg[%d] %#o\n", i, seg[i]);
}
printf("	Count %o (seg[%d])\n", seg[CGDSIZE-1], CGDSIZE-1);
*/
		if((j = write(fd, seg, (CGDSIZE - 1) *2)) != (CGDSIZE -1) * 2)
			error("Write error character %#o (segment)", code);

	}
	(void) close(fd);
}

/*
 * seek to char data
 */
seekchar( block, segment)
Word block, segment;
{
	seekblock(block);
	seekseg(segment);
}

/*
 * seek over the length of a segment
 */
#define	L_INCR	1
seekseg( n)
int n;
{
	long to;

	if((to = lseek(dsk, (long)(n * CGDSIZE * 2), L_INCR)) < 0)
		error("seek error");
}
