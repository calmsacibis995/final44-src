h09193
s 00038/00035/01743
d D 8.3 94/10/09 21:16:43 mckusick 5 4
c err => errf to avoid conflict with function of the same name (from ralph)
e
s 00000/00003/01778
d D 8.2 94/04/16 12:50:24 bostic 4 3
c historically, pr permitted -w without a column specification
c POSIX.2 only requires that it be ignored for single-column, not that
c it be disallowed.
c From: "John F. Woods" <jfw@jfwhome.funhouse.com>
e
s 00004/00004/01777
d D 8.1 93/06/06 15:57:06 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00013/00102/01768
d D 5.2 93/04/30 16:58:52 bostic 2 1
c minor integration in 4BSD source tree
e
s 01870/00000/00000
d D 5.1 93/04/30 13:30:05 muller 1 0
c date and time created 93/04/30 13:30:05 by muller
e
u
U
t
T
I 1
D 2

E 2
/*-
 * Copyright (c) 1991 Keith Muller.
D 2
 * Copyright (c) 1991 The Regents of the University of California.
E 2
I 2
D 3
 * Copyright (c) 1993 The Regents of the University of California.
E 2
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * This code is derived from software contributed to Berkeley by
 * Keith Muller of the University of California, San Diego.
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char copyright[] =
D 2
"%Z% Copyright (c) 1991 The Regents of the University of California.\n\
E 2
I 2
D 3
"%Z% Copyright (c) 1993 The Regents of the University of California.\n\
E 2
 All rights reserved.\n";
E 3
I 3
"%Z% Copyright (c) 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 3
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/types.h>
#include <sys/time.h>
#include <sys/stat.h>
D 2
#include <stdio.h>
#include <signal.h>
E 2
I 2

E 2
#include <ctype.h>
D 2
#include <stdlib.h>
E 2
#include <errno.h>
I 2
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
E 2
#include <string.h>
#include <unistd.h>
I 2

E 2
#include "pr.h"
#include "extern.h"

/*
 * pr:	a printing and pagination filter. If multiple input files
 *	are specified, each is read, formatted, and written to standard
 *	output. By default, input is seperated into 66-line pages, each
 *	with a header that includes the page number, date, time and the
 *	files pathname.
 *
 *	Complies with posix P1003.2/D11
 */

/*
 * parameter variables
 */
int	pgnm;			/* starting page number */
int	clcnt;			/* number of columns */
int	colwd;			/* column data width - multiple columns */
int	across;			/* mult col flag; write across page */
int	dspace;			/* double space flag */
char	inchar;			/* expand input char */
int	ingap;			/* expand input gap */
int	formfeed;		/* use formfeed as trailer */
char	*header;		/* header name instead of file name */
char	ochar;			/* contract output char */
int	ogap;			/* contract output gap */
int	lines;			/* number of lines per page */
int	merge;			/* merge multiple files in output */
char	nmchar;			/* line numbering append char */
int	nmwd;			/* width of line number field */
int	offst;			/* number of page offset spaces */
int	nodiag;			/* do not report file open errors */
char	schar;			/* text column separation character */
int	sflag;			/* -s option for multiple columns */
int	nohead;			/* do not write head and trailer */
int	pgwd;			/* page width with multiple col output */
char	*timefrmt;		/* time conversion string */

/*
 * misc globals
 */
D 5
FILE	*err;			/* error message file pointer */
E 5
I 5
FILE	*errf;			/* error message file pointer */
E 5
int	addone;			/* page length is odd with double space */
int	errcnt;			/* error count on file processing */
char	digs[] = "0123456789";	/* page number translation map */

D 2
#if __STDC__
E 2
int
D 2
main(int argc, char **argv)
#else
int
E 2
main(argc, argv)
        int argc;
D 2
        char **argv;
#endif
E 2
I 2
        char *argv[];
E 2
{
	int ret_val;

	if (signal(SIGINT, SIG_IGN) != SIG_IGN)
		(void)signal(SIGINT, terminate);
	ret_val = setup(argc, argv);
	if (!ret_val) {
		/*
		 * select the output format based on options
		 */
		if (merge)
			ret_val = mulfile(argc, argv);
		else if (clcnt == 1)
			ret_val = onecol(argc, argv);
		else if (across)
			ret_val = horzcol(argc, argv);
		else
			ret_val = vertcol(argc, argv);
	} else
		usage();
	flsh_errs();
	if (errcnt || ret_val)
		exit(1);
	return(0);
}

/*
 * onecol:	print files with only one column of output.
 *		Line length is unlimited.
 */
D 2
#if __STDC__
E 2
int
D 2
onecol(int argc, char **argv)
#else
int
E 2
onecol(argc, argv)
        int argc;
D 2
        char **argv;
#endif
E 2
I 2
        char *argv[];
E 2
{
	register int cnt = -1;
	register int off;
	register int lrgln;
	register int linecnt;
	register int num;
	int lncnt;
	int pagecnt;
	int ips;
	int ops;
	int cps;
	char *obuf;
	char *lbuf;
	char *nbuf;
	char *hbuf;
	char *ohbuf;
	FILE *inf;
	char *fname;
	int mor;

	if (nmwd)
		num = nmwd + 1;
	else
		num = 0;
	off = num + offst;

	/*
	 * allocate line buffer
	 */
	if ((obuf = malloc((unsigned)(LBUF + off)*sizeof(char))) == NULL) {
		mfail();
		return(1);
	}
	/*
	 * allocate header buffer
	 */
	if ((hbuf = malloc((unsigned)(HDBUF + offst)*sizeof(char))) == NULL) {
		mfail();
		return(1);
	}

	ohbuf = hbuf + offst;
	nbuf = obuf + offst;
	lbuf = nbuf + num;
	if (num)
		nbuf[--num] = nmchar;
	if (offst) {
		(void)memset(obuf, (int)' ', offst);
		(void)memset(hbuf, (int)' ', offst);
	}

	/*
	 * loop by file
	 */
	while ((inf = nxtfile(argc, argv, &fname, ohbuf, 0)) != NULL) {
		if (pgnm) {
			/*
			 * skip to specified page
			 */
			if (inskip(inf, pgnm, lines))
				continue;
			pagecnt = pgnm;
		} else
			pagecnt = 1;
		lncnt = 0;

		/*
		 * loop by page
		 */
		for(;;) {
			linecnt = 0;
			lrgln = 0;
			ops = 0;
			ips = 0;
			cps = 0;

			/*
			 * loop by line
			 */
			while (linecnt < lines) {
				/*
				 * input next line
				 */
				if ((cnt = inln(inf,lbuf,LBUF,&cps,0,&mor)) < 0)
					break;
				if (!linecnt && !nohead &&
					prhead(hbuf, fname, pagecnt))
					return(1);

				/*
				 * start of new line.
				 */
				if (!lrgln) {
					if (num)
						addnum(nbuf, num, ++lncnt);
					if (otln(obuf,cnt+off, &ips, &ops, mor))
						return(1);
				} else if (otln(lbuf, cnt, &ips, &ops, mor))
					return(1);

				/*
				 * if line bigger than buffer, get more
				 */
				if (mor) {
					lrgln = 1;
					continue;
				}

				/*
				 * whole line rcvd. reset tab proc. state
				 */
				++linecnt;
				lrgln = 0;
				ops = 0;
				ips = 0;
			}

			/*
			 * fill to end of page
			 */
			if (linecnt && prtail(lines-linecnt-lrgln, lrgln))
				return(1);

			/*
			 * On EOF go to next file
			 */
			if (cnt < 0)
				break;
			++pagecnt;
		}
		if (inf != stdin)
			(void)fclose(inf);
	}
	if (eoptind < argc)
		return(1);
	return(0);
}

/*
 * vertcol:	print files with more than one column of output down a page
 */
D 2
#if __STDC__
E 2
int
D 2
vertcol(int argc, char **argv)
#else
int
E 2
vertcol(argc, argv)
        int argc;
D 2
        char **argv;
#endif
E 2
I 2
        char *argv[];
E 2
{
	register char *ptbf;
	register char **lstdat;
	register int i;
	register int j;
	register int cnt = -1;
	register int pln;
	register int *indy;
	int cvc;
	int *lindy;
	int lncnt;
	int stp;
	int pagecnt;
	int col = colwd + 1;
	int mxlen = pgwd + offst + 1;
	int mclcnt = clcnt - 1;
	struct vcol *vc;
	int mvc;
	int tvc;
	int cw = nmwd + 1;
	int fullcol;
	char *buf;
	char *hbuf;
	char *ohbuf;
	char *fname;
	FILE *inf;
	int ips = 0;
	int cps = 0;
	int ops = 0;
	int mor = 0;

	/*
	 * allocate page buffer
	 */
	if ((buf = malloc((unsigned)lines*mxlen*sizeof(char))) == NULL) {
		mfail();
		return(1);
	}

	/*
	 * allocate page header
	 */
	if ((hbuf = malloc((unsigned)(HDBUF + offst)*sizeof(char))) == NULL) {
		mfail();
		return(1);
	}
	ohbuf = hbuf + offst;
	if (offst)
		(void)memset(hbuf, (int)' ', offst);

	/*
	 * col pointers when no headers
	 */
	mvc = lines * clcnt;
	if ((vc =
	    (struct vcol *)malloc((unsigned)mvc*sizeof(struct vcol))) == NULL) {
		mfail();
		return(1);
	}

	/*
	 * pointer into page where last data per line is located
	 */
	if ((lstdat = (char **)malloc((unsigned)lines*sizeof(char *))) == NULL){
		mfail();
		return(1);
	}

	/*
	 * fast index lookups to locate start of lines
	 */
	if ((indy = (int *)malloc((unsigned)lines*sizeof(int))) == NULL) {
		mfail();
		return(1);
	}
	if ((lindy = (int *)malloc((unsigned)lines*sizeof(int))) == NULL) {
		mfail();
		return(1);
	}

	if (nmwd)
		fullcol = col + cw;
	else
		fullcol = col;

	/*
	 * initialize buffer lookup indexes and offset area
	 */
	for (j = 0; j < lines; ++j) {
		lindy[j] = j * mxlen;
		indy[j] = lindy[j] + offst;
		if (offst) {
			ptbf = buf + lindy[j];
			(void)memset(ptbf, (int)' ', offst);
			ptbf += offst;
		} else
			ptbf = buf + indy[j];
		lstdat[j] = ptbf;
	}

	/*
	 * loop by file
	 */
	while ((inf = nxtfile(argc, argv, &fname, ohbuf, 0)) != NULL) {
		if (pgnm) {
			/*
			 * skip to requested page
			 */
			if (inskip(inf, pgnm, lines))
				continue;
			pagecnt = pgnm;
		} else
			pagecnt = 1;
		lncnt = 0;

		/*
		 * loop by page
		 */
		for(;;) {
			/*
			 * loop by column
			 */
			cvc = 0;
			for (i = 0; i < clcnt; ++i) {
				j = 0;
				/*
				 * if last column, do not pad
				 */
				if (i == mclcnt)
					stp = 1;
				else
					stp = 0;
				/*
				 * loop by line
				 */
				for(;;) {
					/*
					 * is this first column
					 */
					if (!i) {
						ptbf = buf + indy[j];
						lstdat[j] = ptbf;
					} else 
						ptbf = lstdat[j];
					vc[cvc].pt = ptbf;

					/*
					 * add number
					 */
					if (nmwd) {
						addnum(ptbf, nmwd, ++lncnt);
						ptbf += nmwd;
						*ptbf++ = nmchar;
					}

					/*
					 * input next line
					 */
					cnt = inln(inf,ptbf,colwd,&cps,1,&mor);
					vc[cvc++].cnt = cnt;
					if (cnt < 0)
						break;
					ptbf += cnt;

					/*
					 * pad all but last column on page
					 */
					if (!stp) {
						/*
						 * pad to end of column
						 */
						if (sflag)
							*ptbf++ = schar;
						else if ((pln = col-cnt) > 0) {
							(void)memset(ptbf,
								(int)' ',pln);
							ptbf += pln;
						}
					}
					/*
					 * remember last char in line
					 */
					lstdat[j] = ptbf;
					if (++j >= lines)
						break;
				}
				if (cnt < 0)
					break;
			}

			/*
			 * when -t (no header) is specified the spec requires
			 * the min number of lines. The last page may not have
			 * balanced length columns. To fix this we must reorder
			 * the columns. This is a very slow technique so it is
			 * only used under limited conditions. Without -t, the
			 * balancing of text columns is unspecified. To NOT
			 * balance the last page, add the global variable
			 * nohead to the if statement below e.g.
			 *
			 * if ((cnt < 0) && nohead && cvc ......
			 */
			--cvc;

			/*
			 * check to see if last page needs to be reordered
			 */
			if ((cnt < 0) && cvc && ((mvc-cvc) >= clcnt)){
				pln = cvc/clcnt;
				if (cvc % clcnt)
					++pln;

				/*
				 * print header
				 */
				if (!nohead && prhead(hbuf, fname, pagecnt))
					return(1);
				for (i = 0; i < pln; ++i) {
					ips = 0;
					ops = 0;
					if (offst&& otln(buf,offst,&ips,&ops,1))
						return(1);
					tvc = i;

					for (j = 0; j < clcnt; ++j) {
						/*
						 * determine column length
						 */
						if (j == mclcnt) {
							/*
							 * last column
							 */
							cnt = vc[tvc].cnt;
							if (nmwd)
								cnt += cw;
						} else if (sflag) {
							/*
							 * single ch between
							 */
							cnt = vc[tvc].cnt + 1;
							if (nmwd)
								cnt += cw;
						} else
							cnt = fullcol;
						if (otln(vc[tvc].pt, cnt, &ips,
								&ops, 1))
							return(1);
						tvc += pln;
						if (tvc >= cvc)
							break;
					}
					/*
					 * terminate line
					 */
					if (otln(buf, 0, &ips, &ops, 0))
						return(1);
				}
				/*
				 * pad to end of page
				 */
				if (prtail((lines - pln), 0))
					return(1);
				/*
				 * done with output, go to next file
				 */
				break;
			}

			/*
			 * determine how many lines to output
			 */
			if (i > 0)
				pln = lines;
			else
				pln = j;

			/*
			 * print header
			 */
			if (pln && !nohead && prhead(hbuf, fname, pagecnt))
				return(1);

			/*
			 * output each line
			 */
			for (i = 0; i < pln; ++i) {
				ptbf = buf + lindy[i];
				if ((j = lstdat[i] - ptbf) <= offst)
					break;
				if (otln(ptbf, j, &ips, &ops, 0))
					return(1);
			}

			/*
			 * pad to end of page
			 */
			if (pln && prtail((lines - pln), 0))
				return(1);

			/*
			 * if EOF go to next file
			 */
			if (cnt < 0)
				break;
			++pagecnt;
		}
		if (inf != stdin)
			(void)fclose(inf);
	}
	if (eoptind < argc)
		return(1);
	return(0);
}

/*
 * horzcol:	print files with more than one column of output across a page
 */
D 2
#if __STDC__
E 2
int
D 2
horzcol(int argc, char **argv)
#else
int
E 2
horzcol(argc, argv)
        int argc;
D 2
        char **argv;
#endif
E 2
I 2
        char *argv[];
E 2
{
	register char *ptbf;
	register int pln;
	register int cnt = -1;
	register char *lstdat;
	register int col = colwd + 1;
	register int j;
	register int i;
	int lncnt;
	int pagecnt;
	char *buf;
	char *hbuf;
	char *ohbuf;
	char *fname;
	FILE *inf;
	int ips = 0;
	int cps = 0;
	int ops = 0;
	int mor = 0;

	if ((buf = malloc((unsigned)(pgwd+offst+1)*sizeof(char))) == NULL) {
		mfail();
		return(1);
	}

	/*
	 * page header
	 */
	if ((hbuf = malloc((unsigned)(HDBUF + offst)*sizeof(char))) == NULL) {
		mfail();
		return(1);
	}
	ohbuf = hbuf + offst;
	if (offst) {
		(void)memset(buf, (int)' ', offst);
		(void)memset(hbuf, (int)' ', offst);
	}

	/*
	 * loop by file
	 */
	while ((inf = nxtfile(argc, argv, &fname, ohbuf, 0)) != NULL) {
		if (pgnm) {
			if (inskip(inf, pgnm, lines))
				continue;
			pagecnt = pgnm;
		} else
			pagecnt = 1;
		lncnt = 0;

		/*
		 * loop by page
		 */
		for(;;) {
			/*
			 * loop by line
			 */
			for (i = 0; i < lines; ++i) {
				ptbf = buf + offst;
				lstdat = ptbf;
				j = 0;
				/*
				 * loop by col
				 */
				for(;;) {
					if (nmwd) {
						/*
						 * add number to column
						 */
						addnum(ptbf, nmwd, ++lncnt);
						ptbf += nmwd;
						*ptbf++ = nmchar;
					}
					/*
					 * input line
					 */
					if ((cnt = inln(inf,ptbf,colwd,&cps,1,
							&mor)) < 0)
						break;
					ptbf += cnt;
					lstdat = ptbf;

					/*
					 * if last line skip padding
					 */
					if (++j >= clcnt)
						break;

					/*
					 * pad to end of column
					 */
					if (sflag)
						*ptbf++ = schar;
					else if ((pln = col - cnt) > 0) {
						(void)memset(ptbf,(int)' ',pln);
						ptbf += pln;
					}
				}

				/*
				 * determine line length
				 */
				if ((j = lstdat - buf) <= offst)
					break;
				if (!i && !nohead &&
					prhead(hbuf, fname, pagecnt))
					return(1);
				/*
				 * output line
				 */
				if (otln(buf, j, &ips, &ops, 0))
					return(1);
			}

			/*
			 * pad to end of page
			 */
			if (i && prtail(lines-i, 0))
				return(1);

			/*
			 * if EOF go to next file
			 */
			if (cnt < 0)
				break;
			++pagecnt;
		}
		if (inf != stdin)
			(void)fclose(inf);
	}
	if (eoptind < argc)
		return(1);
	return(0);
}

/*
 * mulfile:	print files with more than one column of output and
 *		more than one file concurrently
 */
D 2
#if __STDC__
E 2
int
D 2
mulfile(int argc, char **argv)
#else
int
E 2
mulfile(argc, argv)
        int argc;
D 2
        char **argv;
#endif
E 2
I 2
        char *argv[];
E 2
{
	register char *ptbf;
	register int j;
	register int pln;
	register int cnt;
	register char *lstdat;
	register int i;
	FILE **fbuf;
	int actf;
	int lncnt;
	int col;
	int pagecnt;
	int fproc;
	char *buf;
	char *hbuf;
	char *ohbuf;
	char *fname;
	int ips = 0;
	int cps = 0;
	int ops = 0;
	int mor = 0;

	/*
	 * array of FILE *, one for each operand
	 */
	if ((fbuf = (FILE **)malloc((unsigned)clcnt*sizeof(FILE *))) == NULL) {
		mfail();
		return(1);
	}

	/*
	 * page header
	 */
	if ((hbuf = malloc((unsigned)(HDBUF + offst)*sizeof(char))) == NULL) {
		mfail();
		return(1);
	}
	ohbuf = hbuf + offst;

	/*
	 * do not know how many columns yet. The number of operands provide an
	 * upper bound on the number of columns. We use the number of files
	 * we can open successfully to set the number of columns. The operation
	 * of the merge operation (-m) in relation to unsuccesful file opens
	 * is unspecified by posix.
	 */
	j = 0;
	while (j < clcnt) {
		if ((fbuf[j] = nxtfile(argc, argv, &fname, ohbuf, 1)) == NULL)
			break;
		if (pgnm && (inskip(fbuf[j], pgnm, lines)))
			fbuf[j] = NULL;
		++j;
	}

	/*
	 * if no files, exit
	 */
	if (!j)
		return(1);

	/*
	 * calculate page boundries based on open file count
	 */
	clcnt = j;
	if (nmwd) {
		colwd = (pgwd - clcnt - nmwd)/clcnt;
		pgwd = ((colwd + 1) * clcnt) - nmwd - 2;
	} else {
		colwd = (pgwd + 1 - clcnt)/clcnt;
		pgwd = ((colwd + 1) * clcnt) - 1;
	}
	if (colwd < 1) {
D 5
		(void)fprintf(err,
E 5
I 5
		(void)fprintf(errf,
E 5
		  "pr: page width too small for %d columns\n", clcnt);
		return(1);
	}
	actf = clcnt;
	col = colwd + 1;

	/*
	 * line buffer
	 */
	if ((buf = malloc((unsigned)(pgwd+offst+1)*sizeof(char))) == NULL) {
		mfail();
		return(1);
	}
	if (offst) {
		(void)memset(buf, (int)' ', offst);
		(void)memset(hbuf, (int)' ', offst);
	}
	if (pgnm)
		pagecnt = pgnm;
	else
		pagecnt = 1;
	lncnt = 0;

	/*
	 * continue to loop while any file still has data
	 */
	while (actf > 0) {
		/*
		 * loop by line
		 */
		for (i = 0; i < lines; ++i) {
			ptbf = buf + offst;
			lstdat = ptbf;
			if (nmwd) {
				/*
				 * add line number to line
				 */
				addnum(ptbf, nmwd, ++lncnt);
				ptbf += nmwd;
				*ptbf++ = nmchar;
			}
			j = 0;
			fproc = 0;

			/*
			 * loop by column
			 */
			for (j = 0; j < clcnt; ++j) {
				if (fbuf[j] == NULL) {
					/*
					 * empty column; EOF
					 */
					cnt = 0;
				} else if ((cnt = inln(fbuf[j], ptbf, colwd,
							&cps, 1, &mor)) < 0) {
					/*
					 * EOF hit; no data
					 */
					if (fbuf[j] != stdin)
						(void)fclose(fbuf[j]);
					fbuf[j] = NULL;
					--actf;
					cnt = 0;
				} else {
					/*
					 * process file data
					 */
					ptbf += cnt;
					lstdat = ptbf;
					fproc++;
				}

				/*
				 * if last ACTIVE column, done with line
				 */
				if (fproc >= actf)
					break;

				/*
				 * pad to end of column
				 */
				if (sflag) {
					*ptbf++ = schar;
				} else if ((pln = col - cnt) > 0) {
					(void)memset(ptbf, (int)' ', pln);
					ptbf += pln;
				}
			}

			/*
			 * calculate data in line
			 */
			if ((j = lstdat - buf) <= offst)
				break;

			if (!i && !nohead && prhead(hbuf, fname, pagecnt))
				return(1);

			/*
			 * output line
			 */
			if (otln(buf, j, &ips, &ops, 0))
				return(1);

			/*
			 * if no more active files, done
			 */
			if (actf <= 0) {
				++i;
				break;
			}
		}

		/*
		 * pad to end of page
		 */
		if (i && prtail(lines-i, 0))
			return(1);
		++pagecnt;
	}
	if (eoptind < argc)
		return(1);
	return(0);
}

/*
 * inln():	input a line of data (unlimited length lines supported)
 *		Input is optionally expanded to spaces
 *
 *	inf:	file
 *	buf:	buffer
 *	lim:	buffer length
 *	cps:	column positon 1st char in buffer (large line support)
 *	trnc:	throw away data more than lim up to \n 
 *	mor:	set if more data in line (not truncated)
 */
D 2
#if __STDC__
E 2
int
D 2
inln(FILE *inf, char *buf, register int lim, int *cps, int trnc, int *mor)
#else
int
E 2
inln(inf, buf, lim, cps, trnc, mor)
	FILE *inf;
	char *buf;
	register int lim;
	int *cps;
	int trnc;
	int *mor;
D 2
#endif
E 2
{
	register int col;
	register int gap = ingap;
	register int ch = EOF;
	register char *ptbuf;
	register int chk = (int)inchar;

	ptbuf = buf;

	if (gap) {
		/*
		 * expanding input option
		 */
		while ((--lim >= 0) && ((ch = getc(inf)) != EOF)) {
			/*
			 * is this the input "tab" char
			 */
			if (ch == chk) {
				/*
				 * expand to number of spaces
				 */
				col = (ptbuf - buf) + *cps;
				col = gap - (col % gap);

				/*
				 * if more than this line, push back
				 */
				if ((col > lim) && (ungetc(ch, inf) == EOF))
					return(1);

				/*
				 * expand to spaces
				 */
				while ((--col >= 0) && (--lim >= 0))
					*ptbuf++ = ' ';
				continue;
			}
			if (ch == '\n')
				break;
			*ptbuf++ = ch;
		}
	} else {
		/*
		 * no expansion
		 */
		while ((--lim >= 0) && ((ch = getc(inf)) != EOF)) {
			if (ch == '\n')
				break;
			*ptbuf++ = ch;
		}
	}
	col = ptbuf - buf;
	if (ch == EOF) {
		*mor = 0;
		*cps = 0;
		if (!col)
			return(-1);
		return(col);
	}
	if (ch == '\n') {
		/*
		 * entire line processed
		 */
		*mor = 0;
		*cps = 0;
		return(col);
	}

	/*
	 * line was larger than limit
	 */
	if (trnc) {
		/*
		 * throw away rest of line
		 */
		while ((ch = getc(inf)) != EOF) {
			if (ch == '\n')
				break;
		}
		*cps = 0;
		*mor = 0;
	} else {
		/*
		 * save column offset if not truncated
		 */
		*cps += col;
		*mor = 1;
	}

	return(col);
}

/*
 * otln():	output a line of data. (Supports unlimited length lines)
 *		output is optionally contracted to tabs
 *
 *	buf:	output buffer with data
 *	cnt:	number of chars of valid data in buf
 *	svips:	buffer input column position (for large lines)
 *	svops:	buffer output column position (for large lines)
 *	mor:	output line not complete in this buf; more data to come.	
 *		1 is more, 0 is complete, -1 is no \n's
 */
D 2
#if __STDC__
E 2
int
D 2
otln(register char *buf, int cnt, int *svops, int *svips, int mor)
#else
int
E 2
otln(buf, cnt, svips, svops, mor)
	register char *buf;
	int cnt;
	int *svops;
	int *svips;
	int mor;
D 2
#endif
E 2
{
	register int ops;		/* last col output */
	register int ips;		/* last col in buf examined */
	register int gap = ogap;
	register int tbps;
	register char *endbuf;

	if (ogap) {
		/*
		 * contracting on output
		 */
		endbuf = buf + cnt;
		ops = *svops;
		ips = *svips;
		while (buf < endbuf) {
			/*
			 * count number of spaces and ochar in buffer
			 */
			if (*buf == ' ') {
				++ips;
				++buf;
				continue;
			}

			/*
			 * simulate ochar processing
			 */
			if (*buf == ochar) {
				ips += gap - (ips % gap);
				++buf;
				continue;
			}

			/*
			 * got a non space char; contract out spaces
			 */
			while (ops < ips) {
				/*
				 * use as many ochar as will fit
				 */
				if ((tbps = ops + gap - (ops % gap)) > ips)
					break;
				if (putchar(ochar) == EOF) {
					pfail();
					return(1);
				}
				ops = tbps;
			}

			while (ops < ips) {
				/*
				 * finish off with spaces
				 */
				if (putchar(' ') == EOF) {
					pfail();
					return(1);
				}
				++ops;
			}

			/*
			 * output non space char
			 */
			if (putchar(*buf++) == EOF) {
				pfail();
				return(1);
			}
			++ips;
			++ops;
		}

		if (mor > 0) {
			/*
			 * if incomplete line, save position counts
			 */
			*svops = ops;
			*svips = ips;
			return(0);
		}

		if (mor < 0) {
			while (ops < ips) {
				/*
				 * use as many ochar as will fit
				 */
				if ((tbps = ops + gap - (ops % gap)) > ips)
					break;
				if (putchar(ochar) == EOF) {
					pfail();
					return(1);
				}
				ops = tbps;
			}
			while (ops < ips) {
				/*
				 * finish off with spaces
				 */
				if (putchar(' ') == EOF) {
					pfail();
					return(1);
				}
				++ops;
			}
			return(0);
		}
	} else {
		/*
		 * output is not contracted
		 */
		if (cnt && (fwrite(buf, sizeof(char), cnt, stdout) <= 0)) {
			pfail();
			return(1);
		}
		if (mor != 0)
			return(0);
	}

	/*
	 * process line end and double space as required
	 */
	if ((putchar('\n') == EOF) || (dspace && (putchar('\n') == EOF))) {
		pfail();
		return(1);
	}
	return(0);
}

/*
 * inskip():	skip over pgcnt pages with lncnt lines per page
 *		file is closed at EOF (if not stdin).
 *
 *	inf	FILE * to read from
 *	pgcnt	number of pages to skip
 *	lncnt	number of lines per page
 */
D 2
#if __STDC__
E 2
int
D 2
inskip(FILE *inf, register int pgcnt, register int lncnt)
#else
int
E 2
inskip(inf, pgcnt, lncnt)
	FILE *inf;
	register int pgcnt;
	register int lncnt;
D 2
#endif
E 2
{
	register int c;
	register int cnt;

	while(--pgcnt > 0) {
		cnt = lncnt;
		while ((c = getc(inf)) != EOF) {
			if ((c == '\n') && (--cnt == 0))
				break;
		}
		if (c == EOF) {
			if (inf != stdin)
				(void)fclose(inf);
			return(1);
		}
	}
	return(0);
}

/*
 * nxtfile:	returns a FILE * to next file in arg list and sets the
 *		time field for this file (or current date).
 *
 *	buf	array to store proper date for the header.
 *	dt	if set skips the date processing (used with -m)
 */
D 2
#if __STDC__
E 2
FILE *
D 2
nxtfile(int argc, char **argv, char **fname, char *buf, int dt)
#else
FILE *
E 2
nxtfile(argc, argv, fname, buf, dt)
	int argc;
	char **argv;
	char **fname;
	char *buf;
	int dt;
D 2
#endif
E 2
{
	FILE *inf = NULL;
	struct timeval tv;
	struct timezone tz;
	struct tm *timeptr = NULL;
	struct stat statbuf;
	static int twice = -1;

	++twice;
	if (eoptind >= argc) {
		/*
		 * no file listed; default, use standard input
		 */
		if (twice)
			return(NULL);
		clearerr(stdin);
		inf = stdin;
		if (header != NULL)
			*fname = header;
		else
			*fname = FNAME;
		if (nohead)
			return(inf);
		if (gettimeofday(&tv, &tz) < 0) {
			++errcnt;
D 5
			(void)fprintf(err, "pr: cannot get time of day, %s\n",
E 5
I 5
			(void)fprintf(errf, "pr: cannot get time of day, %s\n",
E 5
				strerror(errno));
			eoptind = argc - 1;
			return(NULL);
		}
		timeptr = localtime(&(tv.tv_sec));
	}
	for (; eoptind < argc; ++eoptind) {
		if (strcmp(argv[eoptind], "-") == 0) {
			/*
			 * process a "-" for filename
			 */
			clearerr(stdin);
			inf = stdin;
			if (header != NULL)
				*fname = header;
			else
				*fname = FNAME;
			++eoptind;
			if (nohead || (dt && twice))
				return(inf);
			if (gettimeofday(&tv, &tz) < 0) {
				++errcnt;
D 5
				(void)fprintf(err,
E 5
I 5
				(void)fprintf(errf,
E 5
					"pr: cannot get time of day, %s\n",
					strerror(errno));
				return(NULL);
			}
			timeptr = localtime(&(tv.tv_sec));
		} else {
			/*
			 * normal file processing
			 */
			if ((inf = fopen(argv[eoptind], "r")) == NULL) {
				++errcnt;
				if (nodiag)
					continue;
D 5
				(void)fprintf(err, "pr: Cannot open %s, %s\n",
E 5
I 5
				(void)fprintf(errf, "pr: Cannot open %s, %s\n",
E 5
					argv[eoptind], strerror(errno));
				continue;
			}
			if (header != NULL)
				*fname = header;
			else if (dt)
				*fname = FNAME;
			else
				*fname = argv[eoptind];
			++eoptind;
			if (nohead || (dt && twice))
				return(inf);

			if (dt) {
				if (gettimeofday(&tv, &tz) < 0) {
					++errcnt;
D 5
					(void)fprintf(err,
E 5
I 5
					(void)fprintf(errf,
E 5
					     "pr: cannot get time of day, %s\n",
					     strerror(errno));
					return(NULL);
				}
				timeptr = localtime(&(tv.tv_sec));
			} else {
				if (fstat(fileno(inf), &statbuf) < 0) {
					++errcnt;
					(void)fclose(inf);
D 5
					(void)fprintf(err, 
E 5
I 5
					(void)fprintf(errf, 
E 5
						"pr: Cannot stat %s, %s\n",
						argv[eoptind], strerror(errno));
					return(NULL);
				}
				timeptr = localtime(&(statbuf.st_mtime));
			}
		}
		break;
	}
	if (inf == NULL)
		return(NULL);

	/*
	 * set up time field used in header
	 */
	if (strftime(buf, HDBUF, timefrmt, timeptr) <= 0) {
		++errcnt;
		if (inf != stdin)
			(void)fclose(inf);
D 5
		(void)fputs("pr: time conversion failed\n", err);
E 5
I 5
		(void)fputs("pr: time conversion failed\n", errf);
E 5
		return(NULL);
	}
	return(inf);
}

/*
 * addnum():	adds the line number to the column
 *		Truncates from the front or pads with spaces as required.
 *		Numbers are right justified.
 *
 *	buf	buffer to store the number
 *	wdth	width of buffer to fill
 *	line	line number
 *
 *		NOTE: numbers occupy part of the column. The posix
 *		spec does not specify if -i processing should or should not
 *		occur on number padding. The spec does say it occupies
 *		part of the column. The usage of addnum	currently treats
 *		numbers as part of the column so spaces may be replaced.
 */
D 2
#if __STDC__
E 2
void
D 2
addnum(register char *buf, register int wdth, register int line)
#else
void
E 2
addnum(buf, wdth, line)
	register char *buf;
	register int wdth;
	register int line;
D 2
#endif
E 2
{
	register char *pt = buf + wdth;

	do {
		*--pt = digs[line % 10];
		line /= 10;
	} while (line && (pt > buf));

	/*
	 * pad with space as required
	 */
	while (pt > buf)
		*--pt = ' ';
}

/*
 * prhead():	prints the top of page header
 *
 *	buf	buffer with time field (and offset)
 *	cnt	number of chars in buf
 *	fname	fname field for header
 *	pagcnt	page number
 */
D 2
#if __STDC__
E 2
int
D 2
prhead(char *buf, char *fname, int pagcnt)
#else
int
E 2
prhead(buf, fname, pagcnt)
	char *buf;
	char *fname;
	int pagcnt;
D 2
#endif
E 2
{
	int ips = 0;
	int ops = 0;

	if ((putchar('\n') == EOF) || (putchar('\n') == EOF)) {
		pfail();
		return(1);
	}
	/*
	 * posix is not clear if the header is subject to line length
	 * restrictions. The specification for header line format
	 * in the spec clearly does not limit length. No pr currently
	 * restricts header length. However if we need to truncate in
	 * an reasonable way, adjust the length of the printf by
	 * changing HDFMT to allow a length max as an arguement printf.
	 * buf (which contains the offset spaces and time field could
	 * also be trimmed
	 *
	 * note only the offset (if any) is processed for tab expansion
	 */
	if (offst && otln(buf, offst, &ips, &ops, -1))
		return(1);
	(void)printf(HDFMT,buf+offst, fname, pagcnt);
	return(0);
}

/*
 * prtail():	pad page with empty lines (if required) and print page trailer
 *		if requested
 *
 *	cnt	number of lines of padding needed
 *	incomp	was a '\n' missing from last line output
 */
D 2
#if __STDC__
E 2
int
D 2
prtail(register int cnt, int incomp)
#else
int
E 2
prtail(cnt, incomp)
	register int cnt;
	int incomp;
D 2
#endif
E 2
{
	if (nohead) {
		/*
		 * only pad with no headers when incomplete last line
		 */
		if (!incomp)
			return(0);
		if ((dspace && (putchar('\n') == EOF)) ||
		    (putchar('\n') == EOF)) {
			pfail();
			return(1);
		}
		return(0);
	}

	/*
	 * if double space output two \n
	 */
	if (dspace)
		cnt *= 2;

	/*
	 * if an odd number of lines per page, add an extra \n
	 */
	if (addone)
		++cnt;

	/*
	 * pad page
	 */
	if (formfeed) {
		if ((incomp && (putchar('\n') == EOF)) || 
		    (putchar('\f') == EOF)) {
			pfail();
			return(1);
		}
		return(0);
	} 
	cnt += TAILLEN;
	while (--cnt >= 0) {
		if (putchar('\n') == EOF) {
			pfail();
			return(1);
		}
	}
	return(0);
}

/*
 * terminate():	when a SIGINT is recvd
 */
D 2
#if __STDC__
E 2
void
D 2
terminate(int which_sig)
#else
void
E 2
terminate(which_sig)
D 2
int which_sig;
#endif
E 2
I 2
	int which_sig;
E 2
{
	flsh_errs();
	exit(1);
}


/*
 * flsh_errs():	output saved up diagnostic messages after all normal
 *		processing has completed
 */
D 2
#if __STDC__
E 2
void
D 2
flsh_errs(void)
#else
void
E 2
flsh_errs()
D 2
#endif
E 2
{
	char buf[BUFSIZ];

	(void)fflush(stdout);
D 5
	(void)fflush(err);
	if (err == stderr)
E 5
I 5
	(void)fflush(errf);
	if (errf == stderr)
E 5
		return;
D 5
	rewind(err);
	while (fgets(buf, BUFSIZ, err) != NULL)
E 5
I 5
	rewind(errf);
	while (fgets(buf, BUFSIZ, errf) != NULL)
E 5
		(void)fputs(buf, stderr);
}

D 2
#if __STDC__
E 2
void
D 2
mfail(void)
#else
void
E 2
mfail()
D 2
#endif
E 2
{
D 5
	(void)fputs("pr: memory allocation failed\n", err);
E 5
I 5
	(void)fputs("pr: memory allocation failed\n", errf);
E 5
}

D 2
#if __STDC__
E 2
void
D 2
pfail(void)
#else
void
E 2
pfail()
D 2
#endif
E 2
{
D 5
	(void)fprintf(err, "pr: write failure, %s\n", strerror(errno));
E 5
I 5
	(void)fprintf(errf, "pr: write failure, %s\n", strerror(errno));
E 5
}

D 2
#if __STDC__
E 2
void
D 2
usage(void)
#else
void
E 2
usage()
D 2
#endif
E 2
{
	(void)fputs(
D 5
	 "usage: pr [+page] [-col] [-adFmrt] [-e[ch][gap]] [-h header]\n",err);
E 5
I 5
	 "usage: pr [+page] [-col] [-adFmrt] [-e[ch][gap]] [-h header]\n",
	 errf);
E 5
	(void)fputs(
D 5
	 "          [-i[ch][gap]] [-l line] [-n[ch][width]] [-o offset]\n",err);
E 5
I 5
	 "          [-i[ch][gap]] [-l line] [-n[ch][width]] [-o offset]\n",
	 errf);
E 5
	(void)fputs(
D 5
	 "          [-s[ch]] [-w width] [-] [file ...]\n", err);
E 5
I 5
	 "          [-s[ch]] [-w width] [-] [file ...]\n", errf);
E 5
}

/*
 * setup:	Validate command args, initialize and perform sanity 
 *		checks on options
 */
D 2
#if __STDC__
E 2
int
D 2
setup(register int argc, register char **argv)
#else
int
E 2
setup(argc, argv)
	register int argc;
	register char **argv;
D 2
#endif
E 2
{
	register int c;
	int eflag = 0;
	int iflag = 0;
	int wflag = 0;
	int cflag = 0;

	if (isatty(fileno(stdout))) {
		/*
		 * defer diagnostics until processing is done
		 */
D 5
		if ((err = tmpfile()) == NULL) {
E 5
I 5
		if ((errf = tmpfile()) == NULL) {
E 5
		       (void)fputs("Cannot defer diagnostic messages\n",stderr);
		       return(1);
		}
	} else
D 5
		err = stderr;
E 5
I 5
		errf = stderr;
E 5
	while ((c = egetopt(argc, argv, "#adFmrte?h:i?l:n?o:s?w:")) != EOF) {
		switch (c) {
		case '+':
			if ((pgnm = atoi(eoptarg)) < 1) {
			    (void)fputs("pr: +page number must be 1 or more\n",
D 5
				err);
E 5
I 5
				errf);
E 5
			    return(1);
			}
			break;
		case '-':
			if ((clcnt = atoi(eoptarg)) < 1) {
D 5
			    (void)fputs("pr: -columns must be 1 or more\n",err);
E 5
I 5
			    (void)fputs("pr: -columns must be 1 or more\n",
			    	errf);
E 5
			    return(1);
			}
			if (clcnt > 1)
				++cflag;
			break;
		case 'a':
			++across;
			break;
		case 'd':
			++dspace;
			break;
		case 'e':
			++eflag;
			if ((eoptarg != NULL) && !isdigit(*eoptarg))
				inchar = *eoptarg++;
			else
				inchar = INCHAR;
			if ((eoptarg != NULL) && isdigit(*eoptarg)) {
				if ((ingap = atoi(eoptarg)) < 0) {
					(void)fputs(
D 5
					"pr: -e gap must be 0 or more\n", err);
E 5
I 5
					"pr: -e gap must be 0 or more\n", errf);
E 5
					return(1);
				}
				if (ingap == 0)
					ingap = INGAP;
			} else if ((eoptarg != NULL) && (*eoptarg != '\0')) {
D 5
				(void)fprintf(err,
E 5
I 5
				(void)fprintf(errf,
E 5
				      "pr: invalid value for -e %s\n", eoptarg);
				return(1);
			} else
				ingap = INGAP;
			break;
		case 'F':
			++formfeed;
			break;
		case 'h':
			header = eoptarg;
			break;
		case 'i':
			++iflag;
			if ((eoptarg != NULL) && !isdigit(*eoptarg))
				ochar = *eoptarg++;
			else
				ochar = OCHAR;
			if ((eoptarg != NULL) && isdigit(*eoptarg)) {
				if ((ogap = atoi(eoptarg)) < 0) {
					(void)fputs(
D 5
					"pr: -i gap must be 0 or more\n", err);
E 5
I 5
					"pr: -i gap must be 0 or more\n", errf);
E 5
					return(1);
				}
				if (ogap == 0)
					ogap = OGAP;
			} else if ((eoptarg != NULL) && (*eoptarg != '\0')) {
D 5
				(void)fprintf(err,
E 5
I 5
				(void)fprintf(errf,
E 5
				      "pr: invalid value for -i %s\n", eoptarg);
				return(1);
			} else
				ogap = OGAP;
			break;
		case 'l':
			if (!isdigit(*eoptarg) || ((lines=atoi(eoptarg)) < 1)) {
				(void)fputs(
D 5
				 "pr: Number of lines must be 1 or more\n",err);
E 5
I 5
				 "pr: Number of lines must be 1 or more\n",errf);
E 5
				return(1);
			}
			break;
		case 'm':
			++merge;
			break;
		case 'n':
			if ((eoptarg != NULL) && !isdigit(*eoptarg))
				nmchar = *eoptarg++;
			else
				nmchar = NMCHAR;
			if ((eoptarg != NULL) && isdigit(*eoptarg)) {
				if ((nmwd = atoi(eoptarg)) < 1) {
					(void)fputs(
D 5
					"pr: -n width must be 1 or more\n",err);
E 5
I 5
					"pr: -n width must be 1 or more\n",errf);
E 5
					return(1);
				}
			} else if ((eoptarg != NULL) && (*eoptarg != '\0')) {
D 5
				(void)fprintf(err,
E 5
I 5
				(void)fprintf(errf,
E 5
				      "pr: invalid value for -n %s\n", eoptarg);
				return(1);
			} else
				nmwd = NMWD;
			break;
		case 'o':
			if (!isdigit(*eoptarg) || ((offst = atoi(eoptarg))< 1)){
				(void)fputs("pr: -o offset must be 1 or more\n",
D 5
					err);
E 5
I 5
					errf);
E 5
				return(1);
			}
			break;
		case 'r':
			++nodiag;
			break;
		case 's':
			++sflag;
			if (eoptarg == NULL)
				schar = SCHAR;
			else
				schar = *eoptarg++;
			if (*eoptarg != '\0') {
D 5
				(void)fprintf(err,
E 5
I 5
				(void)fprintf(errf,
E 5
				      "pr: invalid value for -s %s\n", eoptarg);
				return(1);
			}
			break;
		case 't':
			++nohead;
			break;
		case 'w':
			++wflag;
			if (!isdigit(*eoptarg) || ((pgwd = atoi(eoptarg)) < 1)){
				(void)fputs(
D 5
				   "pr: -w width must be 1 or more \n",err);
E 5
I 5
				   "pr: -w width must be 1 or more \n",errf);
E 5
				return(1);
			}
			break;
		case '?':
		default:
			return(1);
		}
	}

	/*
	 * default and sanity checks
	 */
	if (!clcnt) {
		if (merge) {
			if ((clcnt = argc - eoptind) <= 1) {
				clcnt = CLCNT;
				merge = 0;
			}
		} else
			clcnt = CLCNT;
	}
	if (across) {
		if (clcnt == 1) {
			(void)fputs("pr: -a flag requires multiple columns\n",
D 5
				err);
E 5
I 5
				errf);
E 5
			return(1);
		}
		if (merge) {
D 5
			(void)fputs("pr: -m cannot be used with -a\n", err);
E 5
I 5
			(void)fputs("pr: -m cannot be used with -a\n", errf);
E 5
			return(1);
		}
	}
	if (!wflag) {
		if (sflag)
			pgwd = SPGWD;
		else
			pgwd = PGWD;
D 4
	} else if (clcnt == 1) {
		(void)fputs("pr: -w requires multiple columns\n", err);
		return(1);
E 4
	}
	if (cflag || merge) {
		if (!eflag) {
			inchar = INCHAR;
			ingap = INGAP;
		}
		if (!iflag) {
			ochar = OCHAR;
			ogap = OGAP;
		}
	}
	if (cflag) {
		if (merge) {
			(void)fputs(
D 5
			  "pr: -m cannot be used with multiple columns\n", err);
E 5
I 5
			  "pr: -m cannot be used with multiple columns\n", errf);
E 5
			return(1);
		}
		if (nmwd) {
			colwd = (pgwd + 1 - (clcnt * (nmwd + 2)))/clcnt;
			pgwd = ((colwd + nmwd + 2) * clcnt) - 1;
		} else {
			colwd = (pgwd + 1 - clcnt)/clcnt;
			pgwd = ((colwd + 1) * clcnt) - 1;
		}
		if (colwd < 1) {
D 5
			(void)fprintf(err,
E 5
I 5
			(void)fprintf(errf,
E 5
			  "pr: page width is too small for %d columns\n",clcnt);
			return(1);
		}
	}
	if (!lines)
		lines = LINES;

	/*
	 * make sure long enough for headers. if not disable
	 */
	if (lines <= HEADLEN + TAILLEN)
		++nohead;	
	else if (!nohead)
		lines -= HEADLEN + TAILLEN;

	/*
	 * adjust for double space on odd length pages
	 */
	if (dspace) {
		if (lines == 1)
			dspace = 0;
		else {
			if (lines & 1)
				++addone;
			lines /= 2;
		}
	}

	if ((timefrmt = getenv("LC_TIME")) == NULL)
		timefrmt = TIMEFMT;
	return(0);
}
E 1
