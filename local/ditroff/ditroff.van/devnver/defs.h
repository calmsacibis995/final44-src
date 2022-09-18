/*
 *  Home of the data files
 */
#define BITS	"/hfonts/bits"
#define DISK	"/hfonts/harris.disk"
#define RECT	"/hfonts/rects"
#define RLES	"/hfonts/rle"


#define SECSIZE	512		/* sector contains 512 bytes */
#define WORD	2		/* two bytes */

#define PTS	01		/* PAPER TAPE SLAVE */
#define PTC	02		/* PAPER TAPE COMPOSITION */
#define PTX	03		/* PAPER TAPE UNDEFINED */
#define FHD	04		/* FONT HEADER DIRECTORY */
#define FHS	05		/* FONT HEADERS */
#define FMT	07		/* FORMAT STORAGE */
#define STX	010		/* STATISTICS RECORD */
#define EWD	012		/* EXCEPTION WORD DICTIONARY */
#define OVL	013		/* OVERLAYS */
#define DF1	014		/* COMPOSITION DEFAULTS - 1 */
#define DF2	015		/* COMPOSITION DEFAULTS - 2 */
#define DF3	016		/* COMPOSITION DEFAULTS - 3 */
#define CGD	017		/* CHARACTER GENERATION DATA */
#define FTD	031		/* Font/Table Directory */
#define DT	032		/* Density Table */

typedef unsigned short	Word;
typedef unsigned char	Byte;

/*
 * an entry in Volume Table Of Contents
 */

struct fentry {
	Byte tag;		/* file or program number */
	Byte unit;		/* disk unit number */
	Word sector;		/* Starting sector on disk */
	Word fsize;		/* File size in words */
	Word empty;		/* empty word */
};

#define VTOCSZ	128		/* Vtoc size (== SECSIZE / sizeof(struct fentry) */

/*
 * entry in Font Header Directory
 */

struct fhdentry {
	Word fno;		/* font number */
	unsigned msize:3;	/* Master size code */
	unsigned fhno:10;	/* Font header block number */
	unsigned dsk:3;		/* Disk where the fonts lives */
};

#define FHDDSZ	256		/* chvtoc reports 256 words for
					Font Haeder directory size */

/*
 * Master size codes (MSCx) run from 0 to 5, they correspont with
 * the next pointsizes
 */
#define MSC0	5
#define MSC1	7
#define MSC2	10
#define MSC3	14
#define MSC4	28
#define MSC5	56

/*
 * struct pointing to Character Generation Data
 */

struct cgdentry {
	unsigned segno:3;
	unsigned blockno:13;
};

/*
 * Font Information Record structure
 *
 */

struct finfo {
	/* first info to character generation data */
	Word cgdentry[128];
	Byte relwidth[128];	/* relative widths */
	Byte emspace;
	Byte enspace;
	Byte thinspace;
	Byte figspace;
	Byte maxwordspace;
	Byte minwordspace;
	Byte normwordspace;
	Byte kernfact;
	Word fntno;
	Byte mastszcode;
	Byte notused;
	Word pt5;
	Word pt7;
	Word pt10;
	Word pt14;
	Word pt28;
	Word pt56;
	Word norm;
	Word bold;
	Word italic;
	Word faceident;
	Word rest[48];
};

/*
 *  structures to hold the data
 */

#define MAGIC ('C' << 8 | 'O')

struct Header {
	int magic;
	char name[10];
} ;

struct Chars {
	long offset;
	int Nstructs;
	int XO;
	int YO;
	int X;
	int Y;
	int Relwidth;
	int Lmax;
} ;

struct Rect {
	short yO;
	short y;
	short xO;
	short x;
} ;

#define CGDSEG	07		/* segment part in ccgdentry */
#define CGDBLCK 0177770		/* blockno part in cgdentry */
#define CGDBMSK	017777
#define CGDSHFT	3

#define cgdseg(i)	((i) & CGDSEG)
#define cgdbno(i)	(((i) >> CGDSHFT) & CGDBMSK)
