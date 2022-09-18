#ifndef lint
static char sccsid[] = "%W% (CWI) %E%";
#endif lint

#include "../defs.h"
#include <sys/file.h>

extern int dsk;

struct fentry vtoc[SECSIZE];

/*
 * read the table of contents
 */

initvtoc()
{
	int  i;
	static int init;

	if(!init) {
		if((dsk = open( DISK, O_RDONLY)) < 0)
			error("Cannot open disk");
		init++;
	}

	seekblock(0);
	if((i = read(dsk, vtoc, SECSIZE)) != SECSIZE)
		error("read error reading VTOC");
}


/*
 * seek to a disk block
 */

seekblock( block )
Word block;
{
	long to, i;
	i = block * SECSIZE;

	if((to = lseek(dsk, (long) (i), 0)) != i) {
		error("seek error");
	}
}


/*
 * seek to a file
 */

tofile(nr)
Word nr;
{
	struct fentry *p = vtoc;

	for( p = vtoc; p->tag != nr; p++) {
		if (p->tag == 0)
			error("Cannot find font %d", nr);
	}
	seekblock(p->sector);
}


/*
 * open the font header directory
 */

openfdir()
{

	initvtoc();		/* read the contents */
	tofile(FHD);
}


/*
 * return a pointer to the font dir
 */

struct fhdentry *
readfdir()
{
	static int init;
	static struct fhdentry fontdir[FHDDSZ];
	register int i;

	if(!init) {
		openfdir();
		if((i = read(dsk, fontdir, SECSIZE)) != SECSIZE)
			error("Cannot read Font Header Directory");
		init++;
	}
	return(fontdir);
}

/*
 * return a pointer to the font information record
 */

static int trtab[] = {
	MSC0,
	MSC1,
	MSC2,
	MSC3,
	MSC4,
	MSC5
};

struct finfo *
getfinfo(font, master)
int font, master;
{
	static struct finfo finforec;
	struct finfo *f = &finforec;
	static int init;
	register struct fhdentry *p;
	register int i, j;
	int mcode;
	extern int dsk;
	extern struct fhdentry *readfdir();

	for( i = 0; i <= 6 ; i++) {
		if(master == trtab[mcode = i])
			break;
	}

	if(i > 5)
		error("Unknown Mastersize");

	p = readfdir();

	for( i = 0; i < FHDDSZ; i++, p++) {
		if(p->fno == font && p->msize == mcode) {	/* font found */
			seekblock(p->fhno);
			if((j = read(dsk, f, SECSIZE)) != SECSIZE)
				error("Read error FIR %d-%d\n", font, master);
			return(f);
		}
	}

	error("Connot find FIR %d-%d\n", font, master);
}
