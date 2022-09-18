h41149
s 00000/00001/00323
d D 1.8 83/07/06 21:32:00 slatteng 9 8
c drop dopey "chrtab" sitting in main.c not used by anybody
e
s 00004/00003/00320
d D 1.7 83/06/24 14:33:25 slatteng 8 7
c make raster images smaller, if possible
e
s 00019/00014/00304
d D 1.6 83/06/17 15:32:46 slatteng 7 6
c set up for gdump stuff, and prettying up
e
s 00027/00029/00291
d D 1.5 83/05/13 17:55:11 slatteng 6 5
c restore size of varian pictures => 4 scale factor, etc.
e
s 00026/00038/00294
d D 1.4 83/03/30 13:38:04 ralph 5 4
c modified mapping and scale factors to fit in square arrays.
e
s 00038/00125/00294
d D 1.3 83/03/16 11:00:54 ralph 4 2
c fixed plots to the versatec.
e
s 00033/00123/00296
d R 1.3 83/03/15 13:46:26 ralph 3 2
c fixed plots to the versatec.
e
s 00358/00353/00061
d D 1.2 83/03/02 13:49:55 ralph 2 1
c this version uses remote line printer software.
e
s 00414/00000/00000
d D 1.1 83/03/02 13:29:38 ralph 1 0
c date and time created 83/03/02 13:29:38 by ralph
e
u
U
t
T
I 1
D 2

E 2
D 5
/* gprint.c-
E 5
I 5
D 6
/*	%M%	%I%	%E%
E 6
I 6
/* %M%	%I%	%E%
E 6
E 5
 *
 * Copyright -C- 1982 Barry S. Roitblat
 *
D 2
 *      This file contains the main and file system dependent routines
E 2
I 2
 *	This file contains the main and file system dependent routines
E 2
 * for producing hard copy from gremlin files.  It is extensively modified
 * from the vplot source.
 */

#include "gprint.h"
D 5
#include "grem2.h"
E 5
#include <signal.h>
#include <vfont.h>

I 2
#define LPR "/usr/ucb/lpr"
D 4
#define VAX
E 4
E 2

D 2
#define VDAEMON        "/usr/lib/vad"
#define WDAEMON        "/usr/lib/vpd"
E 2
I 2
D 4
#ifdef VAX
#define NB	1024		/* Number of blocks in virtual memory */
#else
#define NB	88		/* Number of blocks kept in memory */
#endif
#define BSIZ	512		/* Size of blocks */
#define LOGBSIZ	9		/* log base 2 of BSIZ */
E 2

E 4
D 2
#define NB    1024        /* Number of blocks in virtual memory */
#define BSIZ    512        /* Size of blocks */
#define    SETSTATE    (('v'<<8)+1)

E 2
extern char *mktemp();
D 2
extern char *getname(); /* get login name or user name */
E 2
I 2
extern char *malloc();
extern char *rindex();
E 2

/* imports */
extern HGtline(), HGArc(), HGPutText(), HGMove(), HGSetFont();
extern HGSetBrush(), HGInitFont(), HGPrintElt();
extern int style[], thick[];
extern char *tfont[], *tsize[];
 
/* database imports */

extern ELT *DBInit(), *DBRead();
extern POINT *PTInit(), *PTMakePoint();

D 2
int     linethickness = 0;       /* brush styles */
int    linmod    = SOLID;
char    chrtab[][16];
char    blocks    [NB][BSIZ];
int    lastx;
int    lasty;
int    angle, startx, starty, endx, endy;
double     scale = 4.0;     /* Variables used to map gremlin screen */
double    topx;             /* coordinates into output device coordinates */
double    topy;
double    botx;
double    boty;
int    centx = 0;
int    centy = 0;
double    delx;
double    dely;
double    del;
E 2
I 2
int	linethickness = 0;	/* brush styles */
D 4
int	linmod	= SOLID;
E 4
I 4
int	linmod = SOLID;
E 4
D 9
char	chrtab[][16];
E 9
D 4
char	blocks[NB][BSIZ];
E 4
I 4
D 5
char	*obuf;		/* output buffer DevRange x DevRange/8 */
int	bufsize;	/* output buffer size */
E 5
I 5
D 6
char	*obuf;			/* output buffer DevRange x DevRange/8 */
E 6
I 6
char	*obuf;			/* output buffer NumOfLin x DevRange/8 */
E 6
int	bufsize;		/* output buffer size */
E 5
E 4
int	lastx;
int	lasty;
int	angle, startx, starty, endx, endy;
D 5
double	scale = 4.0;	/* Variables used to map gremlin screen */
double	topx;		/* coordinates into output device coordinates */
double	topy;
double	botx;
double	boty;
int	centx = 0;
int	centy = 0;
double	delx;
double	dely;
double	del;
E 5
I 5
D 6
double	scale = 3.0;		/* Variables used to map gremlin screen */
E 6
I 6
double	scale = 4.0;		/* Variables used to map gremlin screen */
E 6
double	orgx = 0.0;		/* x and y origin of gremlin picture */
double	orgy = 0.0;
E 5
E 2

D 2
char *vspoolr = "/usr/spool/vad/dfxXXXXXX";
char *wspoolr = "/usr/spool/vpd/dfxXXXXXX";
char *vfilen = "/usr/spool/vad/tmpXXXXXX";
char *wfilen = "/usr/spool/vad/tmpXXXXXX";
E 2
I 2
D 4
#ifdef VAX
char	dirty[NB];		/* marks if a block has been written into */
#else
struct	buf {
	int	bno;
	char	*block;
} bufs[NB];
#endif
E 2

D 2
int DevRange = 1536;        /* Bits per line for output device */
E 2
I 2
int	fd;			/* file descriptor of current picture */
E 4
I 4
FILE	*pfp = stdout;		/* file descriptor of current picture */
E 4
char	picture[] = "/usr/tmp/rastAXXXXXX";
int	run = 13;		/* index of 'a' in picture[] */
D 4
int	DevRange = 1536;	/* Bits per line for output device */
E 4
I 4
D 5
int	DevRange = 1536;	/* Bits per line for output array */
int	DevRange8 = 1536/8;	/* Bytes per line for output array */
E 5
I 5
D 6
int	DevRange = 1536;	/* plot dimensions in pixels */
int	DevRange8 = 1536/8;
E 5
E 4
int	BytesPerLine = 264;	/* Bytes per raster line (different from range
				   due to non-square paper). */
D 5
char	device = 'V';		/* default device */
E 5
int	lparg = 6;		/* index into lpargs */
E 6
I 6
int	DevRange = Vxlen;	/* plot dimensions in pixels */
int	DevRange8 = Vxlen/8;
int	BytPrLin = Vbytperlin;	/* Bytes per raster line. (not DevRange8) */
int	NumOfLin = Vylen;
E 6
E 2

I 6
int	lparg = 6;		/* index into lpargs */
E 6
D 2
struct    buf 
{
    int    bno;
    char    *block;
};
struct    buf    bufs;
E 2
I 2
char	*lpargs[50] = { "lpr", "-Pvarian", "-v", "-s", "-r", "-J", };
E 2

D 2
int dirty[NB];         /* marks if a block has been written into */
int    in, out;
char picture[64];
char *run = "a";     /* gives uniqueness for multiple pictures */
char device = 'V';
char *banner = "gremlin";

E 2
D 6
/* variables used to print from font file */
D 2
int Orientation;
int cfont = 0;
int csize = 0;
struct header header;
struct dispatch dispatch[256];
char *bits = NULL;
char *fontdir = "/usr/lib/vfont/";
E 2
I 2
int	Orientation;
E 6
I 6
int	Orientation;		/* variables used to print from font file */
E 6
int	cfont = 0;
int	csize = 0;
struct	header header;
struct	dispatch dispatch[256];
char	*bits = NULL;
char	*fontdir = "/usr/lib/vfont/";
E 2

main(argc, argv)
int argc;
char *argv[];
{
D 2
    FILE *fp, *fopen();
    ELT *PICTURE, *e;
    POINT *p1, pos;
    char *file[50], sw, string[10], *arg;
    char c, string1[50], string2[50], string3[50], string4[50], 
            string5[50], string6[50], string7[50], string8[50]; 
    extern int onintr();
    float mult;
    int WriteRaster = FALSE;
    int i, j, gfil = 0;
    int b, brsh;
    int k;
E 2
I 2
	FILE *fp, *fopen();
	ELT *PICTURE, *e;
	POINT *p1, pos;
	char *file[50], string[10], *arg;
	char c, string1[50], string2[50], string3[50], string4[50], 
		string5[50], string6[50], string7[50], string8[50]; 
	extern int cleanup();
	float mult;
	int WriteRaster = FALSE;
D 4
	register int i, j, k;
E 4
I 4
	register char *cp1, *cp2;
	register int i, k;
E 4
	int brsh, gfil = 0;
E 2

D 2
    /* Parse the command line. */
E 2
I 2
	/* Parse the command line. */
E 2

D 2
    argc -= 1;  argv++;                /* Skip program name. */
    while (argc > 0)
    {
        argc -= 1;
        arg = *argv++;
        if (arg[0] != '-') file[gfil++] = arg;
        else
        {
            sw = *++arg;
            switch (sw)
            {
            case 'W':       /* Print to wide (versatec) device */
                  device = 'W';
                  DevRange = 2047;
                  break;
            case 'V':       /* Print to narrow (varian) device */
                  device = 'V';
                  DevRange = 1536;
                  break;
            case '1':      /* select size 1 */
                  if (*++arg == '\0')
                  if (argc-- > 0) arg = *argv++;
                  tsize[0] = arg;
                  break;
            case '2':      /* select size 2 */
                  if (*++arg == '\0')
                  if (argc-- > 0) arg = *argv++;
                  tsize[1] = arg;
                  break;
            case '3':      /* select size 3 */
                  if (*++arg == '\0')
                  if (argc-- > 0) arg = *argv++;
                  tsize[2] = arg;
                  break;
            case '4':      /* select size 4 */
                  if (*++arg == '\0')
                  if (argc-- > 0) arg = *argv++;
                  tsize[3] = arg;
                  break;
            case 'R':      /* select Roman font */
                  if (*++arg == '\0')
                  if (argc-- > 0) arg = *argv++;
                  tfont[0] = arg;
                  break;
            case 'I':     /* select italics font */
                  if (*++arg == '\0')
                  if (argc-- > 0) arg = *argv++;
                  tfont[1] = arg;
                  break;
            case 'B':     /* select bold font */
                  if (*++arg == '\0')
                  if (argc-- > 0) arg = *argv++;
                  tfont[2] = arg;
                  break;
            case 'S':     /* select special font */
                  if (*++arg == '\0')
                  if (argc-- > 0) arg = *argv++;
                  tfont[3] = arg;
                  break;
            case 'N':     /* select narrow brush width */
                  if (*++arg == '\0')
                  if (argc-- > 0) arg = *argv++;
                  (void) sscanf(arg, "%d", &brsh);
                  thick[0] = thick[1] = thick[3] = thick[4] = brsh;
                  break;
            case 'T':     /* select thick brush width */
                  if (*++arg == '\0')
                  if (argc-- > 0) arg = *argv++;
                  (void) sscanf(arg, "%d", &brsh);
                  thick[2] = brsh;
                  break;
            case 'M':     /* select medium brush width */
                  if (*++arg == '\0')
                  if (argc-- > 0) arg = *argv++;
                  (void) sscanf(arg, "%d", &brsh);
                  thick[5] = brsh;
                  break;
            case 't':     /* send raster to standard output */
                  WriteRaster = TRUE;
                  break;
            case 'x':     /* select scale */
                  if (*++arg == '\0')
                  if (argc-- > 0) arg = *argv++;
                  sscanf(arg,"%f",&mult);
                  scale *= mult;
                  break;
            case 'p':     /* prompt for font and size parameters */
                  printf("Roman font name? (%s): ", tfont[0]);
                  gets(string1);
                  if (*string1 != '\0') tfont[0] = string1;
                  printf("Italic font name? (%s): ", tfont[1]);
                  gets(string2);
                  if (*string2 != '\0') tfont[1] = string2;
                  printf("Bold font name? (%s): ", tfont[2]);
                  gets(string3);
                  if (*string3 != '\0') tfont[2] = string3;
                  printf("Special font name? (%s): ", tfont[3]);
                  gets(string4);
                  if (*string4 != '\0') tfont[3] = string4;
                  printf("font size 1? (%s): ", tsize[0]);
                  gets(string5);
                  if (*string5 != '\0') tsize[0] = string5;
                  printf("font size 2? (%s): ", tsize[1]);
                  gets(string6);
                  if (*string6 != '\0') tsize[1] = string6;
                  printf("font size 3? (%s): ", tsize[2]);
                  gets(string7);
                  if (*string7 != '\0') tsize[2] = string7;
                  printf("font size 4? (%s): ", tsize[3]);
                  gets(string8);
                  if (*string8 != '\0') tsize[3] = string8;
                  printf("narrow brush size? (%d): ", thick[0]);
                  gets(string);
                  if (*string != '\0') 
                  {
                       sscanf(string, "%d", &brsh);
                       thick[0] = thick[1] = thick[3] = thick[4] = brsh;
                  }
                  printf("medium brush size? (%d): ", thick[5]);
                  gets(string);
                  if (*string != '\0') 
                  {
                       sscanf(string, "%d", &brsh);
                       thick[5] = brsh;
                  }
                  printf("thick brush size? (%d): ", thick[2]);
                  gets(string);
                  if (*string != '\0') 
                  {
                       sscanf(string, "%d", &brsh);
                       thick[2] = brsh;
                  }
                  break;
            default:
                  (void) printf("unknown switch: %c", sw);
            }
        }
    }
E 2
I 2
	argc--;
	argv++;
	while (argc--) {
		if (*(arg = *argv++) != '-')
			file[gfil++] = arg;
		else switch (*++arg) {
		case 'W':	/* Print to wide (versatec) device */
D 5
			device = 'W';
E 5
I 5
D 6
			scale = 4.0;
E 5
D 4
			DevRange = 2047;
E 4
I 4
			DevRange = 2048;
			DevRange8 = 2048/8;
E 4
			BytesPerLine = 880;
E 6
I 6
D 7
			BytPrLin = Wbytperlin;
E 7
			DevRange = Wxlen;
			DevRange8 = Wxlen/8;
			BytPrLin = Wbytperlin;
			NumOfLin = Wylen;
E 6
			lpargs[1] = "-Pversatec";
			break;
		case 'V':	/* Print to narrow (varian) device */
D 5
			device = 'V';
E 5
I 5
D 6
			scale = 3.0;
E 5
			DevRange = 1536;
I 4
			DevRange8 = 1536/8;
E 4
			BytesPerLine = 264;
E 6
I 6
D 7
			BytPrLin = Vbytperlin;
E 7
			DevRange = Vxlen;
			DevRange8 = Vxlen/8;
			BytPrLin = Vbytperlin;
			NumOfLin = Vylen;
E 6
			lpargs[1] = "-Pvarian";
			break;
		case '1':	/* select size 1 */
			if (*++arg == '\0' && argc--)
				arg = *argv++;
			tsize[0] = arg;
			break;
		case '2':	/* select size 2 */
			if (*++arg == '\0' && argc--)
				arg = *argv++;
			tsize[1] = arg;
			break;
		case '3':	/* select size 3 */
			if (*++arg == '\0' && argc--)
				arg = *argv++;
			tsize[2] = arg;
			break;
		case '4':	/* select size 4 */
			if (*++arg == '\0' && argc--)
				arg = *argv++;
			tsize[3] = arg;
			break;
		case 'R':	/* select Roman font */
			if (*++arg == '\0' && argc--)
				arg = *argv++;
			tfont[0] = arg;
			break;
		case 'I':	/* select italics font */
			if (*++arg == '\0' && argc--)
				arg = *argv++;
			tfont[1] = arg;
			break;
		case 'B':	/* select bold font */
			if (*++arg == '\0' && argc--)
				arg = *argv++;
			tfont[2] = arg;
			break;
		case 'S':	/* select special font */
			if (*++arg == '\0' && argc--)
				arg = *argv++;
			tfont[3] = arg;
			break;
		case 'N':	/* select narrow brush width */
			if (*++arg == '\0' && argc--)
				arg = *argv++;
			(void) sscanf(arg, "%d", &brsh);
			thick[0] = thick[1] = thick[3] = thick[4] = brsh;
			break;
		case 'T':	/* select thick brush width */
			if (*++arg == '\0' && argc--)
				arg = *argv++;
			(void) sscanf(arg, "%d", &brsh);
			thick[2] = brsh;
			break;
		case 'M':	/* select medium brush width */
			if (*++arg == '\0' && argc--)
				arg = *argv++;
			(void) sscanf(arg, "%d", &brsh);
			thick[5] = brsh;
			break;
		case 't':	/* send raster to standard output */
			WriteRaster = TRUE;
			break;
		case 'x':	/* select scale */
			if (*++arg == '\0' && argc--)
				arg = *argv++;
			sscanf(arg,"%f", &mult);
			scale *= mult;
			break;
		case 'p':	/* prompt for font and size parameters */
			printf("Roman font name? (%s): ", tfont[0]);
			gets(string1);
			if (*string1 != '\0') tfont[0] = string1;
			printf("Italic font name? (%s): ", tfont[1]);
			gets(string2);
			if (*string2 != '\0') tfont[1] = string2;
			printf("Bold font name? (%s): ", tfont[2]);
			gets(string3);
			if (*string3 != '\0') tfont[2] = string3;
			printf("Special font name? (%s): ", tfont[3]);
			gets(string4);
			if (*string4 != '\0') tfont[3] = string4;
			printf("font size 1? (%s): ", tsize[0]);
			gets(string5);
			if (*string5 != '\0') tsize[0] = string5;
			printf("font size 2? (%s): ", tsize[1]);
			gets(string6);
			if (*string6 != '\0') tsize[1] = string6;
			printf("font size 3? (%s): ", tsize[2]);
			gets(string7);
			if (*string7 != '\0') tsize[2] = string7;
			printf("font size 4? (%s): ", tsize[3]);
			gets(string8);
			if (*string8 != '\0') tsize[3] = string8;
			printf("narrow brush size? (%d): ", thick[0]);
			gets(string);
			if (*string != '\0') {
D 7
				sscanf(string, "%d", &brsh);
				thick[0] = thick[1] = thick[3] = thick[4] = brsh;
E 7
I 7
			    sscanf(string, "%d", &brsh);
			    thick[0] = thick[1] = thick[3] = thick[4] = brsh;
E 7
			}
			printf("medium brush size? (%d): ", thick[5]);
			gets(string);
			if (*string != '\0') {
D 7
				sscanf(string, "%d", &brsh);
				thick[5] = brsh;
E 7
I 7
			    sscanf(string, "%d", &brsh);
			    thick[5] = brsh;
E 7
			}
			printf("thick brush size? (%d): ", thick[2]);
			gets(string);
			if (*string != '\0') {
D 7
				sscanf(string, "%d", &brsh);
				thick[2] = brsh;
E 7
I 7
			    sscanf(string, "%d", &brsh);
			    thick[2] = brsh;
E 7
			}
			break;
		default:
D 4
			(void) printf("unknown switch: %c", *arg);
E 4
I 4
D 6
			fprintf(stderr, "unknown switch: %c", *arg);
E 6
I 6
			fprintf(stderr, "unknown switch: %c\n", *arg);
E 6
E 4
		}
	}
E 2

I 7
	if (WriteRaster) {		/* over-ride dimension settings */
		DevRange = Vxlen;	/* if printing to file to be gdumped */
		DevRange8 = Vxlen/8;
D 8
		BytPrLin = Vbytperlin;
		NumOfLin = Wylen;
E 8
I 8
		BytPrLin = DevRange8;
E 8
	}

E 7
D 2
    /* init constants for scaling */
    topx = topy = DevRange;
    botx = boty = 0;
    delx = dely = del = DevRange;
    centx = (DevRange - mapx(topx/scale))/2;
    centy = mapy(topy/scale)/2;
    signal(SIGTERM, onintr);
    if (signal(SIGINT, SIG_IGN) != SIG_IGN)
        signal(SIGINT, onintr);
    if (gfil == 0)   /* no filename, use standard input */
    {
        file[0] = "stdin";
        ++gfil;
    }
    for (j=0; j<gfil; ++j)
    {
        if (strcmp(file[j], "stdin") != 0) fp = fopen(file[j],"r");
        else  fp = stdin;
        if (fp == NULL)
        {
            fprintf(stderr, "can't open %s",file[j]);
            continue;
        }
        PICTURE = DBRead(fp,&Orientation, &pos);    /* read picture file */
        if (DBNullelt(PICTURE)) continue;
E 2
I 2
D 5
	/* init constants for scaling */
	topx = topy = DevRange;
	botx = boty = 0;
	delx = dely = del = DevRange;
	centx = (DevRange - mapx(topx/scale))/2;
	centy = mapy(topy/scale)/2;
E 5
	signal(SIGTERM, cleanup);
	if (signal(SIGINT, SIG_IGN) != SIG_IGN)
		signal(SIGINT, cleanup);
	mktemp(picture);
I 4
D 6
	if ((obuf = malloc(bufsize = DevRange * DevRange8)) == NULL) {
E 6
I 6
	if ((obuf = malloc(bufsize = NumOfLin * DevRange8)) == NULL) {
E 6
D 7
		fprintf(stderr, "gprint: ran out of memory for output buffer\n");
E 7
I 7
		fprintf(stderr,"gprint: ran out of memory for output buffer\n");
E 7
		exit(1);
	}
E 4
	if (gfil == 0) {	/* no filename, use standard input */
		file[0] = NULL;
		gfil++;
	}
	for (k=0; k<gfil; k++) {
		if (file[k] != NULL) {
			if ((fp = fopen(file[k], "r")) == NULL) {
D 6
				fprintf(stderr, "gprint: can't open %s", file[k]);
E 6
I 6
D 7
				fprintf(stderr, "gprint: can't open %s\n", file[k]);
E 6
				continue;
E 7
I 7
			    fprintf(stderr, "gprint: can't open %s\n", file[k]);
			    continue;
E 7
			}
			if (k == 0) {
				if ((arg = rindex(file[k], '/')) == NULL)
					arg = file[k];
				else
					arg++;
				lpargs[lparg++] = arg;
			}
		} else {
			fp = stdin;
			lpargs[lparg++] = "gremlin";
		}
		/* read picture file */
		PICTURE = DBRead(fp, &Orientation, &pos);
I 4
		fclose(fp);
E 4
		if (DBNullelt(PICTURE))
			continue;
E 2

D 2
        banner = file[j];
        picture[0] = '\0';    /* picture equals null string */
        strcat(picture,mktemp("/usr/tmp/#rastXXXXX"));
        strcat(picture, run);
        (*run)++;
        bufs.bno = -1;      /* no current block */
        for (i=0; i<NB; i++) 
        {
            dirty[i] = FALSE;     /* no blocks written yet */
            for (k=0; k<BSIZ; ++k)     /* Zero out memory area for picture */
                  blocks[i][k] = 0;
        }
        out = creat(picture, 0666);
        in = open(picture, 0);
        zseek(out, NB);               /* seek to end of file and write */
        write(out, blocks[0], BSIZ);  /* intervening hole will be 0-filled */
E 2
I 2
D 4
		if ((fd = creat(picture, 0666)) < 0) {
			fprintf(stderr, "gprint: can't create %s\n", picture);
			cleanup();
E 4
I 4
		if (!WriteRaster) {
D 5
			umask(0);
E 5
I 5
			umask(022);
E 5
			if ((pfp = fopen(picture, "w")) == NULL) {
D 7
				fprintf(stderr, "gprint: can't create %s\n", picture);
				cleanup();
E 7
I 7
			    fprintf(stderr,"gprint: can't create %s\n",picture);
			    cleanup();
E 7
			}
E 4
		}
D 4
#ifndef VAX
		close(fd);
		if ((fd = open(picture, 2)) < 0) {
			fprintf(stderr, "gprint: can't reopen %s\n", picture);
			cleanup();
		}
#endif
E 4
		i = strlen(picture) + 1;
		if ((arg = malloc(i)) == NULL) {
			fprintf(stderr, "gprint: ran out of memory\n");
			cleanup();
		}
		strcpy(arg, picture);
		lpargs[lparg++] = arg;
		picture[run]++;
D 4
		for (i=0; i<NB; i++) {
#ifdef VAX
			dirty[i] = FALSE;
			for (j=0; j<BSIZ; ++j)
				blocks[i][j] = 0;
#else
			bufs[i].bno = -1;
			bufs[i].block = blocks[i];
#endif
		}
#ifdef NOHOLES
		/* clear the entire file */
		for (i=0; i<BSIZ; i++)
			blocks[0][i] = '\0';
		for (i=0; i<1024; i++)
			write(fd, blocks[0], BSIZ);
#endif
E 2

E 4
I 4
		cp2 = &obuf[bufsize];
		for (cp1 = obuf; cp1 < cp2; )
			*cp1++ = 0;
E 4
D 2
        e = PICTURE;
        while (!DBNullelt(e))
        {
               HGPrintElt(e);     /* traverse picture, printing elements */
               e = DBNextElt(e);
        }
E 2
I 2
		e = PICTURE;
		while (!DBNullelt(e)) {
D 7
			HGPrintElt(e);	/* traverse picture, printing elements */
E 7
I 7
			HGPrintElt(e);	/* traverse picture;  print elements */
E 7
			e = DBNextElt(e);
		}
E 2
D 4

D 2
        for (i=0; i<NB; i++) 
        {
            if (WriteRaster == TRUE)   /* put picture to standard output */
            {
                for (j=0; j<BSIZ; ++j)
                    putchar(blocks[i][j]);
            }
            if (dirty[i] == TRUE)      /* write out only those blocks which */
            {                          /* which have been written into, the */
                zseek(out,i);          /* rest will default to be zeroes    */
                write(out, blocks[i], BSIZ);
            }
        }
        fclose(fp);
        close(out);
        if (WriteRaster == FALSE) 
            putpict(picture);
        close(in);
        close(out);
    }  /* end for j */
    exit(0);
}  /* end main */

putpict(picture)
char *picture;
{
    FILE *temp;
    char *fileName,*spoolerName;

    if((temp = fopen(picture,"r")) == NULL)   /* picture image doesnt exist */
    {
        perror(picture);
        exit(1);
    }
    fclose(temp);
    if(device == 'V')     /* writing to varian */
    {
        fileName = (char *) malloc(strlen(vfilen) + 1);
        strcpy(fileName,vfilen);
        fileName = mktemp(fileName);
        spoolerName = (char *) malloc(strlen(vspoolr) + 1);
        strcpy(spoolerName,vspoolr);
        spoolerName = mktemp(spoolerName);
    }
    else                 /* writing to versatec */
    {
        fileName = (char *) malloc(strlen(wfilen) + 1);
        strcpy(fileName,wfilen);
        fileName = mktemp(fileName);
        spoolerName = (char *) malloc(strlen(wspoolr) + 1);
        strcpy(spoolerName,wspoolr);
        spoolerName = mktemp(spoolerName);
    }
    if((temp = fopen(fileName,"w")) == NULL) 
    {
        fprintf(stderr,"Can't make temporary spooling file\n");
        exit(1);
    }
 
           /* write file and command information to printer daemon */

    fprintf(temp,"L%s\n",getname());  /* login name (for banner) */
    fprintf(temp,"B%s\n",banner);      /* gremlin file name (for banner) */
    fprintf(temp,"V%s\n",picture);     /* raster image file name  */
    fprintf(temp,"U%s\n",picture);     /* unlink file when through */
    fclose(temp);
    if(link(fileName,spoolerName) != 0) 
    {
        perror(spoolerName);
        exit(2);
    }
    unlink(fileName);

            /* Spawn daemon process */

    if(vfork() == 0) 
    {
        if(device == 'V')
            execl(VDAEMON,VDAEMON);
        else
            execl(WDAEMON,WDAEMON);
    }
E 2
I 2
		for (i=0; i<NB; i++) {
			if (WriteRaster) {
				fwrite(blocks[i], sizeof(char), BSIZ, stdout);
				continue;
			}
#ifdef VAX
			if (dirty[i]) {	/* write out non-zero blocks */
				zseek(fd, i);
				write(fd, blocks[i], BSIZ);
			}
#else
			if (bufs[i].bno != -1) {
				zseek(fd, bufs[i].bno);
				write(fd, bufs[i].blocks[i], BSIZ);
			}
#endif
E 4
I 4
D 5
		for (cp1 = obuf; cp1 < cp2; cp1 += DevRange8) {
			fwrite(cp1, sizeof(char), DevRange8, pfp);
			if (fseek(pfp, (long) BytesPerLine - DevRange8, 1) < 0)
				for (i = BytesPerLine - DevRange8; i--; )
					putc('\0', pfp);
E 5
I 5
D 8
		for (cp1 = obuf; cp1 < cp2; ) {
E 8
I 8
		if (WriteRaster)	/* if -t then cut image length */
		    while (!*--cp2);
		for (cp1 = obuf; cp1 < cp2; ) {			/* write file */
E 8
			for (i = DevRange8; i--; cp1++)
				putc(*cp1, pfp);
D 6
			for (i = BytesPerLine - DevRange8; i--; )
E 6
I 6
			for (i = BytPrLin - DevRange8; i--; )
E 6
				putc('\0', pfp);
E 5
E 4
		}
D 4
		fclose(fp);
		close(fd);
E 4
I 4
		if (!WriteRaster)
			fclose(pfp);
E 4
	}
I 5
D 6
/*
E 6
E 5
	if (!WriteRaster) {
		lpargs[lparg] = 0;
		execv(LPR, lpargs);
		fprintf(stderr, "gprint: can't exec %s\n", LPR);
		cleanup();
	}
I 5
D 6
*/
E 6
E 5
	exit(0);
E 2
}

I 2
D 4
#ifndef VAX
E 2
getblk(b)
D 2
int b;
E 2
I 2
register b;
E 2
{
D 2
    if(b < 0 || NB <= b)   /* bad block number */
    {
        fprintf(stderr,"vplot: internal error, b out of range in getblk\n");
        abort();
    }
    dirty[b] = TRUE;    /* assume that present block has been written into */
    bufs.bno = b;
    bufs.block = blocks[b];  /* get new block to write */
E 2
I 2
	register struct buf *bp1;
	register char *tp;

	if (b < 0 || b >= NB) {		/* bad block number */
		fprintf(stderr, "gprint: internal error, b out of range in getblk\n");
		cleanup();
	}
loop:
	for (bp1 = bufs; bp1 < &bufs[NB]; bp1++) {
		if (bp1->bno == b || bp1->bno == -1) {
			tp = bp1->block;
			while (bp1 > bufs) {
				bp1->bno = (bp1-1)->bno;
				bp1->block = (bp1-1)->block;
				bp1--;
			}
			bp1->bno = b;
			bp1->block = tp;
			return;
		}
	}
	zseek(fd, bufs[NB-1].bno);
	write(fd, bufs[NB-1].block, BSIZ);
	zseek(fd, b);
	read(fd, bufs[NB-1].block, BSIZ);
	bufs[NB-1].bno = b;
	goto loop;
E 2
}
I 2
#endif
E 2

E 4
D 2
onintr()
E 2
I 2
cleanup()
E 2
{
D 2
    exit(1);
E 2
I 2
D 5
	while (picture[run] != 'a') {
E 5
I 5
	do
E 5
		unlink(picture);
D 5
		picture[run]--;
	}
E 5
I 5
	while (picture[run]-- != 'A');
E 5
	exit(1);
E 2
}

I 2
/*
D 5
 * Points should be in the range 0 <= x (or y) <= DevRange.
E 5
I 5
D 6
 * Points should be in the range 0 <= x < DevRange, 0 <= y < DevRange.
E 6
I 6
 * Points should be in the range 0 <= x < DevRange, 0 <= y < NumOfLin.
E 6
E 5
 * The origin is the top left-hand corner with increasing x towards the
 * right and increasing y going down.
I 4
D 5
 * The output array is DevRange x DevRange pixels.
E 5
I 5
D 6
 * The output array is DevRange x DevRange/8 pixels.
E 6
I 6
 * The output array is NumOfLin x DevRange/8 pixels.
E 6
E 5
E 4
 */
E 2
point(x, y)
D 2
int x, y;
E 2
I 2
register int x, y;
E 2
{
D 2
    int bno;
E 2
I 2
D 4
	register unsigned bno, byte;
E 4
I 4
	register unsigned byte;
E 4
E 2

D 2
    bno = ((x&03700)>>6) + ((y&03700)>>1);  /* calculate block number */
    if (bno != bufs.bno)     /* get appropriate block if necessary */
    {
        if (bno < 0 || bno >= 1024)
            return;
        getblk(bno);
    }
    bufs.block[((y&077)<<3)+((x>>3)&07)] |= 1 << (7-(x&07));  /* set bit */
E 2
I 2
D 4
	byte = y * BytesPerLine + (x >> 3);
	bno = byte >> LOGBSIZ;
	byte &= BSIZ - 1;
	if (bno >= 1024)
		return;
#ifndef VAX
	if (bno != bufs[0].bno)
		getblk(bno);
	bufs[0].block[byte] |= 1 << (7 - (x & 07));
#else
	blocks[bno][byte] |= 1 << (7 - (x & 07));
	dirty[bno] = TRUE;
#endif
E 2
}

zseek(a, b)
{
D 2
    return(lseek(a, (long)b*512, 0));
E 2
I 2
	return(lseek(a, (long)b*BSIZ, 0));
E 4
I 4
D 5
	byte = y * DevRange8 + (x >> 3);
	if (byte < bufsize)
E 5
I 5
D 6
	if ((unsigned) x < DevRange && (unsigned) y < DevRange) {
E 6
I 6
	if ((unsigned) x < DevRange && (unsigned) y < NumOfLin) {
E 6
		byte = y * DevRange8 + (x >> 3);
E 5
		obuf[byte] |= 1 << (7 - (x & 07));
I 5
D 6
	} else
		printf("(%d, %d) out of range\n", x, y);
E 6
I 6
	}
E 6
E 5
E 4
E 2
}
E 1
