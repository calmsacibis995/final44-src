/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	omerge.c,v $
 * Revision 2.4  89/03/09  21:13:18  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  19:26:47  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.2  88/07/20  22:50:51  rpd
 * Eliminated mysterious TRACEF macro calls.
 * 
 */
/*
 * File:	omerge.c
 * Purpose:
 *	Merge rdb binary & symbol table into the kernel binary.
 */

#ifndef	lint
static char rcsid[] = "$Header: omerge.c,v 2.4 89/03/09 21:13:18 rpd Exp $";
#endif
/* $Source: /afs/cs.cmu.edu/source_mach/rcs/kernel/src/omerge.c,v $ */
#include <stdio.h>
#include <ctype.h>

#define PAGESIZE page_size

#include <sys/types.h>
#include <netinet/in.h>
#include <a.out.h>

int debug;
long old_pos;

#define LSEEK(fd,pos,how) old_pos = lseek(fd,pos,how)


/*
 * Program to merge an input a.out format file into another
 * a.out format file that (presumably) has space set aside for the
 * contents.
 * the input file is placed at the start of the output file unless
 * this is overridden with a -n switch. "n" is the hex offset
 * to place it at. 
 * the current host system's pagesize is used for ZMAGIC files, 
 * unless PAGESIZE is set into the environment.
 */

int infile, outfile;
char *inname, *outname;
int page_size;		/* the page size */
int flip_header;	/* header must be flipped to be read */
int tflg, dflg;
long offset;		/* default offset */
long maxlength;		/* a maximum length */
int lflg;		/* if maxlength specified */

main(argc,argv) char **argv;
{
struct exec inheader;
struct exec outheader;
int insize, outsize;
char *getenv();
register char *p = getenv("PAGESIZE");
char *pgname = argv[0];
register char *argp;

page_size = p ? atoi(p) : getpagesize();	/* get page size */

while (argc > 1 && * (argp = argv[1]) == '-')
	{
	--argc;
	++argv;
	switch(argp[1])
		{
	case 'D':	/* debug flag */
		++debug;
		break;
	case 'e':	/* provide end address */
		++lflg;
		maxlength = aton(argp+2) - offset;
		break;
	case 'l':	/* provide maximum length to output */
		++lflg;		/* length specified */
		maxlength = aton(argp+2);
		break;
	case 'p':
		page_size = atoi(argp+2);	/* set the page size */
		break;
	case 'o':			/* set offset */
		offset = aton(argp+2);
		break;
	default:
		if (isxdigit(argp[1]) || argp[1] == '+' || argp[1] == '-')
			offset = aton(argp+1);
		else
			err("switch %s not recognized",argp);
		break;
		}
	}
if (argc < 3)
	err("usage: %s infile outfile",pgname);
inname = argv[1]; outname = argv[2];

if ((infile = open(inname,0)) < 0)
	err("cannot open %s for input",inname);
if ((outfile = open(outname,2)) < 0)
	err("cannot open %s for input/output",outname);
if (read(infile,&inheader,sizeof inheader) != sizeof inheader)
	err("%s: header too short",inname);

if (N_BADMAG(inheader))
	err("%s: bad header type",inname);

if (read(outfile,&outheader,sizeof outheader) != sizeof outheader)
	err("%s: header too short",outname);

if (N_BADMAG(outheader))
	err("%s: bad header type",outname);
if (inheader.a_trsize || inheader.a_drsize)
	printf("warning: %s has relocation information\n",inname);
if (outheader.a_trsize || outheader.a_drsize)
	printf("warning: %s has relocation information\n",outname);
if (!lflg)
	maxlength = outheader.a_text + outheader.a_data;
LSEEK(infile,(long) N_TXTOFF(inheader),0);
LSEEK(outfile,(long) offset + N_TXTOFF(outheader),0);
copy_file(inheader.a_text);	/* copy the text */
LSEEK(infile,(long) N_TXTOFF(inheader) + inheader.a_text,0);
/*
 * put the data of the input file right after the text of the input
 * file in the output file. (essentially we treat the input text+data
 * as text for the output file.
 */
LSEEK(outfile,(long) offset + N_TXTOFF(outheader) + inheader.a_text,0);
copy_file(inheader.a_data);	/* copy the data */
if (maxlength < 0)
	err("input file exceeds available space by %d bytes",-maxlength);
exit(0);			/* we did it! */
}

copy_file(length) register int length;
{
char buff[BUFSIZ];
register int l, n;

while (length > 0)
	{
	l = length;
	if (l > BUFSIZ)
		l = BUFSIZ;
	if ((n = read(infile,buff,l)) != l)
		{
		if (n < 0)
			err("%s: read error",inname);
		else
			err("%s: file too short",inname);
		}
	if ((l = write(outfile,buff,n)) != n)
		err("%s: write error",outname);
	length -= n;
	maxlength -= n;		/* adjust max length */
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


/*
 * convert string in hex to binary
 */
int atox(ptr)
	register char *ptr;
{
	register int n = 0;
	register int c;

	for (; c = *ptr++;) {
		if (isdigit(c))
			c -= '0';
		else if ('a' <= c && c <= 'f')
			c -= 'a' - 10;
		else if ('A' <= c && c <= 'F')
			c -= 'A' - 10;
		else
			break;
		n = (n << 4) + c;
	}
	return (n);
}

aton(ptr)
	register char *ptr;
{
	if (*ptr == '+' || *ptr == '-')
		return (atoi(ptr));
	if (*ptr == '0' && (ptr[1] == 'x' || ptr[1] == 'X'))
		return (atox(ptr + 2));
	return (atox(ptr));
}

