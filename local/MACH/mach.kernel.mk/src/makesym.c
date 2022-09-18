/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	makesym.c,v $
 * Revision 2.3  89/02/25  19:26:24  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.2  88/07/20  22:52:42  rpd
 * Moved definitions of MAXSYMLEN and struct symtab here from standca/debug.h.
 * 
 */
/*
 * File:	makesym.c
 * Purpose:
 *	Make a symbol table for rdb, to be merged into the kernel binary.
 */

#include <stdio.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <a.out.h>

/* from standca/debug.h in acis kernel source */
#define MAXSYMLEN 20

struct symtab {
	char symbol[MAXSYMLEN];	       /* the symbol */
	unsigned int value;	       /* it's value */
};

/*
 * make a symbol table suitable for the debugger from the output
 * of 'nm'.
 * input is of the form: address letter symbol 
 */

#define MAXSYMSIZE 100
FILE *infile = NULL;
int outsize = 0;		/* output file size */
struct exec header = { OMAGIC };
char symbol[MAXSYMSIZE];
int addr;
char letter[10];
struct symtab sym;
int hflg;			/* -h (header) specified */
int nflg;			/* -n (no byte swapping) specified */
FILE *outfile = stdout;		/* output file */

main(argc,argv) char **argv;
{
register int i;
register char *argp;

for (i=1; i<argc; ++i)
	{
	argp = argv[i];
	if (*argp == '-')
		switch(argp[1])
			{
		case 'n':
			++nflg;
			break;
		case 'h':	/* produce an a.out header */
			++hflg;
			if (outsize)
				err("-h must be first");
			fwrite(&header,sizeof header,1,outfile);
			break;
		case 'o':	/* -o output-file */
			if (hflg)
				err("-o must appear before -h ");
			if ((outfile = fopen(argv[++i],"w")) == NULL)
				err("could not open %s for output",argv[i]);
			break;
		default:
			err("bad option %s",argp);
			break;
			}
	else
		{
		if ((infile = fopen(argp,"r")) == NULL)
			err("can't open %s",argp);
		dofile(infile);
		fclose(infile);
		}
	}
if (infile == NULL)
	dofile(stdin);
if (hflg)
	{
	header.a_text = outsize;
	if (fseek(outfile,(long) 0, 0) < 0)	/* point to start of file again */
		err("could not reposition outfile (pipe?)");
	fwrite(&header,sizeof header,1,outfile);
	}
exit(0);
}

dofile(file) register FILE *file;
{
while (fscanf(file,"%x %1s %100s\n",&addr,letter,symbol) == 3)
	{
	if (symbol[0] != '_')
		continue;
	if (nflg)
		sym.value = (addr);
	else
		sym.value = htonl(addr);
	strncpy(sym.symbol,symbol+1,sizeof sym.symbol);
	fwrite(&sym,sizeof sym,1,outfile);
	outsize += sizeof sym;
	}
}


err(s,d1,d2,d3,d4)
char *s;
{
warn(s,d1,d2,d3,d4);
exit(1);
}

warn(s,d1,d2,d3,d4)
char *s;
{
extern errno;

fflush(stdout);
fprintf(stderr,s,d1,d2,d3,d4);
if(errno > 0)
	{
	fprintf(stderr," - ");
	perror("");
	}
else
	fprintf(stderr,"\n");
}
