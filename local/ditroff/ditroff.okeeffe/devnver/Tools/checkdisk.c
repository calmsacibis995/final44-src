#ifndef lint
static char sccsid[] = "%W% (CWI) %E%";
#endif lint
/*****************************************************************
 *
 * checkdisk
 *
 * Print out header info from the vtoc, and a list of the fonts
 * contained, in the form <fontno>-<mastersize>.  With -a more
 * info about the fonts is printed.
 *
 ****************************************************************/
#include "../defs.h"
#include <sys/file.h>

#define SECSIZE	512		/* sector contains 512 bytes */
#define WORD	2		/* two bytes */

/*
 * This is what we expect the VTOC to contain:
	
	FILE	PTS,100,0		; PAPER TAPE SLAVE
	FILE	PTC,100,0		; PAPER TAPE COMPOSITION
	FILE	PTX,100,0		; PAPER TAPE UNDEFINED
	FILE	FHD,1,0			; FONT HEADER DIRECTORY
	FILE	FHS,200,0		; FONT HEADERS
	FILE	FMT,113,0		; FORMAT STORAGE
	FILE	STX,1,0			; STATISTICS RECORD
	FILE	EWD,100,0		; EXCEPTION WORD DICTIONARY
	FILE	OVL,20,0		; OVERLAYS
	FILE	DF1,1,0			; COMPOSITION DEFAULTS - 1
	FILE	DF2,1,0			; COMPOSITION DEFAULTS - 2
	FILE	DF3,1,0			; COMPOSITION DEFAULTS - 3
	FILE	CGD,1,0			; CHARACTER GENERATION DATA
*/

struct filelist {
	struct fentry entry;
	char *fname;
} list[] = {
     /* tag,	unit,	sector,	fsize,	empty,	filename??? */
	PTS,	0,	1,	0100,	0,	"Paper Tape Slave",
	PTC,	0,	0101,	0100,	0,	"Paper Tape composition",
	PTX,	0,	0201,	0100,	0,	"Paper Tape Undefined",
	FHD,	0,	0301,	01,	0,	"Font Header Directory",
	FHS,	0,	0302,	0200,	0,	"Font Headers",
	FMT,	0,	0502,	0113,	0,	"Format Storage",
	STX,	0,	0615,	01,	0,	"Statistics Record",
	EWD,	0,	0616,	0100,	0,	"Exception Dictionary",
	OVL,	0,	0716,	020,	0,	"Overlays",
	DF1,	0,	0736,	1,	0,	"Composition Defaults - 1",
	DF2,	0,	0737,	1,	0,	"Composition Defaults - 2",
	DF3,	0,	0740,	1,	0,	"Composition Defaults - 3",
	CGD,	0,	0741,	1,	0,	"Character Generation Data",
	FTD,	0,	201,	3,	0,	"Font/Table Directory",
	DT,	0,	204,	10,	0,	"Density or exposure Tables",
	0
};

struct fentry vtoc[VTOCSZ];


int dsk;
int allflag;

struct fhdentry fontdir[FHDDSZ];


main(argc, argv)
int argc; char *argv[];
{
	int i;
	struct fentry *p;
	struct filelist *q;

	/*
	 * parse args
	 */

	argv++;
	while( --argc && *argv[0] == '-') {
		
		switch(argv[0][1]) {
			case 'a':
				allflag++;
				break;
			default:
				error("Unknown option %s", *argv);
		}
		argv++;
	}

	if((dsk = open( DISK, O_RDONLY)) < 0)
		error("Cannot open disk");

	if((i = read(dsk, vtoc, SECSIZE)) != SECSIZE)
		error("read error on disk");
	
	/*
	 *  first show the vtoc info
	 */

	for( p = vtoc; p->tag != 0; p++) {
next:
		if( p->tag) {
			for( q = list; q->entry.tag != 0; q++) {
				if ( q->entry.tag == p->tag ) {
					printf("fileno %d unit %d ",p->tag,p->unit);
					if(p->unit != q->entry.unit)
						printf("(%d) ", q->entry.unit);
					printf("sector %d ", p->sector);
					if(p->sector != q->entry.sector)
						printf("(%d) ", q->entry.sector);
					printf("size %d ", p->fsize);
					i = q->entry.fsize * SECSIZE / WORD;
					if(p->fsize != i)
						printf("(%d) ", i);
					if(p->empty)
						printf("Load address %d ", p->empty);
					printf("(%s)\n", q->fname);
					p++; goto next;
				}
			}
			printf("fileno %d unit %d ", p->tag, p->unit);
			if(p->empty)
				printf("Load address %d ", p->empty);
			printf("sector %d size %d\n", p->sector, p->fsize);
		}
	}

	/*
	 * now print out the font info
	 */

	openfdir();

	if((i = read(dsk, fontdir, SECSIZE)) != SECSIZE)
		error("Cannot read Font Header Directory");

	prfinfo(fontdir);
}



/*
 * printfont header information
 */
int trtab[] = {
	MSC0,
	MSC1,
	MSC2,
	MSC3,
	MSC4,
	MSC5
};

prfinfo(head)
struct fhdentry head[];
{
	register struct fhdentry *p;

	for( p = head; p->fno != 0; p++) {
		if(allflag) {
			printf("Fontnumber: %4d ", p->fno);
			printf("has Mastersize %2d, ", trtab[p->msize]);
			printf("disk %d, ", p->dsk);
			printf("Font Information Record at block %d", p->fhno);
			putchar('\n');
		} else
			printf("%d-%d\n", p->fno, trtab[p->msize]);
	}
	
}
