/*
.pp
.nf
  devundo:
	read binary info about a particular device (DESC.out)
	(e.g., cat, 202, aps5) from file, convert
	it into asciiform suitable for
	fast reading by humans and devconfig.

	Usage:

	devconfig DESC [ F ... ]
		uses DESC to create a description file
		using the information therein.
		It creates the file DESC.out.

	devconfig F ...
		makes the font tables for fonts F only,
		creates files F.out.

	DESC.out contains:
	dev structure with fundamental sizes
	list of sizes (nsizes+1) terminated by 0, as short's
	indices of char names (nchtab * sizeof(short))
	char names as hy\0em\0... (lchname)
	nfonts occurrences of
		widths (nwidth)
		kerning (nwidth) [ascender+descender only so far]
		codes (nwidth) to drive actual typesetter
		fitab (nchtab+128-32)
	each of these is an array of char.

	dev.filesize contains the number of bytes
	in the file, excluding the dev part itself.

	F.out contains the font header, width, kern, codes, and fitab.
	Width, kern and codes are parallel arrays.
	(Which suggests that they ought to be together?)
	Later, we might allow for codes which are actually
	sequences of formatting info so characters can be drawn.
*/

#include "stdio.h"
#include "dev.h"

#define	BMASK	0377
#define	skipline(f)	while(getc(f) != '\n')
#define	NSIZE	100		/* maximum number of sizes */
#define	NCH	256		/* max number of characters with funny names */
#define	NFITAB	(NCH + 128-32)	/* includes ascii chars, but not non-graphics */
#define	FSIZE	200	/* size of a physical font (e.g., 102 for cat) */
#define	NFONT	60	/* max number of default fonts */

struct	dev	dev;
struct	font	font;

short	size[NSIZE];
char	chname[5*NCH];	/* character names, including \0 for each */
short	chtab[NCH];	/* index of character in chname */
unsigned char	fitab[NFITAB];	/* font table: position of char i;  0 if not there */
char	width[FSIZE];	/* width table for a physical font */
char	kern[FSIZE];	/* ascender+descender info */
char	code[FSIZE];	/* actual device codes for a physical font */
char	fname[NFONT][10];	/* temp space to hold default font names */
char	sname[NFONT][10];	/* temp space to hold default stipple names */

int	fflag	= 0;	/* on if font table to be written */
int	fdout;		/* output file descriptor */

main(argc, argv)
char *argv[];
{
	FILE *fout;
	int fin;
	char cmd[100], *p;
	int i, totfont, v;

	if ((fin = open(argv[1], 0)) == NULL) {
		fprintf(stderr, "devconfig: can't open %s\n", argv[1]);
		exit(1);
	}
	if ((fout = fopen("DESC", "w")) == NULL) {
		fprintf(stderr, "devconfig: can't open %s\n", argv[1]);
		exit(1);
	}
	read(fin, &dev, sizeof(struct dev));
	read(fin, size, (dev.nsizes+1) * sizeof(size[0]));	/* we need a 0 on the end */
	read(fin, chtab, dev.nchtab * sizeof(chtab[0]));
	read(fin, chname, dev.lchname);
	undesc1(fout);
	totfont = dev.filesize - (
		(dev.nsizes+1) * sizeof(size[0])
		+ dev.nchtab * sizeof(chtab[0])
		+ dev.lchname * sizeof(char));
	for (i = 0; i < dev.nfonts; i++) {
		read(fin, &font, sizeof(struct font));
		read(fin, width, font.nwfont & BMASK);
		read(fin, kern, font.nwfont & BMASK);
		read(fin, code, font.nwfont & BMASK);
		read(fin, fitab, dev.nchtab+128-32);
		totfont -= undofont(fname[i]);
	}
	read(fin, sname, totfont);
	undesc2(fout);
}
#define LINE(x) {if(dev.x) fprintf(descf, "%s %d\n", "x", dev.x);} 
undesc1(descf)
FILE *descf;
{
	register int i;
	LINE(res);
	LINE(hor);
	LINE(vert);
	LINE(unitwidth);
	LINE(sizescale);   
	LINE(paperwidth);    
	LINE(paperlength);
	LINE(spare1);
	if(dev.nsizes) {
		fprintf(descf,"sizes ");
		for (i = 0; i < dev.nsizes; i++)
			fprintf(descf,"%d ",size[i]);
		fprintf(descf,"0\n");
	}
	fflush(descf);
}

undesc2(descf)
FILE *descf;
{
	register int i; register char *p;
	fprintf(descf, "fonts %d ", dev.nfonts);
	for (i = 0; i < dev.nfonts; i++) {
		fprintf(descf, "%s ", fname[i]);
		if((i&0x7)==7) fprintf(descf,"\n	");
	}
	putc('\n',descf);
	if (dev.nstips) {
		p = (char *)sname;
		fprintf(descf, "stipples %d ", dev.nstips);
		for (i = 0; i < dev.nstips; i++) {
			fprintf(descf, "%s ", p);
			while(*p++); /* advance to next one */
		}
		putc('\n',descf);
	}
	fprintf(descf, "charset ");
	for (i = 0; i < dev.nchtab - 1; i++)
	{
		if((i % 23)==0)
		putc('\n',descf);
		fprintf(descf,"%s ",&chname[chtab[i]]);
	}

}



undofont(name)	/* create fitab and width tab for font */
char *name;
{
	FILE *fout;
	int fdout;
	int i, nw, spacewidth, n, v, o_w, o_k, o_n;
	char buf[100], ch[10], s1[10], s2[10], s3[10], cmd[30];
	short xnw[NFITAB], xfitab[NFITAB];

	if ((fout = fopen(font.namefont, "w")) == NULL) {
		fprintf(stderr, "devconfig: can't open font %s\n", name);
		exit(2);
	}
	strncpy(name,font.namefont,10);
	fprintf(fout, "name %s\n", name);
	if (font.intname[0]) fprintf(fout,"internalname %s\n",font.intname);
	if (font.specfont) fprintf(fout,"special\n");
	if (font.spare1) fprintf(fout,"spare1 %1.1s\n",&font.spare1);
	if (font.ligfont) {
		fprintf(fout,"ligatures ");
		if (font.ligfont & LFF) fprintf(fout,"ff ");
		if (font.ligfont & LFL) fprintf(fout,"fl ");
		if (font.ligfont & LFI) fprintf(fout,"fi ");
		if (font.ligfont & LFFL) fprintf(fout,"ffl ");
		if (font.ligfont & LFFI) fprintf(fout,"ffi ");
		fprintf(fout,"0\n");
	}
	n = dev.res * dev.unitwidth / 72 / 3;
	if (width[0]!=n) fprintf(fout, "spacewidth %d\n", width[0]);
	/* print out elements by widths */
	fprintf(fout,"# char	width	u/d	octal\ncharset\n");
	for(i = dev.nchtab + 128-32 - 1; i >= 0; i--) xnw[i] = xfitab[i] = -1;
	for(i = dev.nchtab + 128-32 - 1; i >= 0; i--) {
		if(nw = fitab[i]) {
			xfitab[i] = xnw[nw];
			xnw[nw] = i;
		}
	}
	for (nw = 1; nw <= (font.nwfont & BMASK); nw++) {
		if ((i = xnw[nw]) < 0) continue; /* unlikely! */
		if (i < 128 - 32) {
			putc(i + 32,fout); putc('\t',fout);
		} else
			fprintf(fout, "%s	", &chname[chtab[i - (128 - 32)]]);
		fprintf(fout, "%4d	%2d	0%o\n", BMASK & width[nw], kern[nw], BMASK & code[nw]);
		while ( (i = xfitab[i]) >  0) {
			if (i < 128 - 32) {
				putc(i + 32,fout); putc('\t',fout);
			} else
				fprintf(fout, "%s\t",
					&chname[chtab[i - (128 - 32)]]);
			fprintf(fout,"\"\n");
		}
	}
	/* the above is supposed to be a faster version of the
	    following grunt exercise:

	for (nw = 1; nw < (font.nwfont & BMASK); nw++) {
		int firstone = 1;
		for (i = 32; i < dev.nchtab + 128; i++) {
			if (fitab[i-32]==nw) {
				if (i < 128) {
					putc(i + 32,fout);
					putc(' ',fout);
				} else
					fprintf(fout, "%s ",
						&chname[chtab[i - 128]]);
				if (firstone) {
					firstone = 0;
					fprintf(fout, "%d %d 0%o\n",
						width[nw], kern[nw], code[nw]);
				} else
					fprintf(fout, "\"\n");
			}
		}
	} */
	fclose(fout);
	v = sizeof(struct font) + 3 * (font.nwfont & BMASK) + dev.nchtab + 128-32;
	fprintf(stderr, "%3s: %3d chars, width %3d, size %3d\n",
		font.namefont, nw, width[0], v);
	return v;
}
