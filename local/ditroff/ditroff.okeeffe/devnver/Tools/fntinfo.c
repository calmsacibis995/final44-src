#ifdef lint
static char sccsid = "%W%	(CWI)	%E%";
#endif
#include "../defs.h"

/*
 * print information from one or more fonts
 * out of the Font header Information Record
 *
 * arguments:
 *	<fontno>-<mastersize>
 *
 */

int dsk;

struct fhdentry fontdir[FHDDSZ];



main( argc, argv)
int argc; char **argv;
{
	int fontno, master;

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
		/*
		printf("index: %3d\tSelect code:\t%3d\n", i % 128, i);
		*/
		if( p->cgdentry[i]) {
			printf("\t%#4o\t%5d\t", i, p->relwidth[i % 128]);
			printf("%5d\t%4d\n",
			    cgdbno(p->cgdentry[i]), cgdseg(p->cgdentry[i%128]));
		}
	}
	if( p->cgdentry[0]) {
		printf("\t%#4o\t%5d\t", 128, p->relwidth[0]);
		printf("%5d\t%4d\n",
			cgdbno(p->cgdentry[0]), cgdseg(p->cgdentry[0]));
	}
}
