h42461
s 00006/00002/00085
d D 4.3 91/04/18 16:34:54 bostic 3 2
c new copyright; att/bsd/shared
e
s 00005/00004/00082
d D 4.2 89/05/11 10:05:05 bostic 2 1
c file reorg, pathnames.h, paths.h
e
s 00086/00000/00000
d D 4.1 83/05/06 23:50:17 tut 1 0
c date and time created 83/05/06 23:50:17 by tut
e
u
U
t
T
I 3
/*-
 * %sccs.include.proprietary.c%
 */

E 3
I 1
#ifndef lint
D 3
static char *sccsid = "%W% (Berkeley) %G%";
#endif
E 3
I 3
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 3

#include "what..c"
I 2
#include "pathnames.h"
E 2

doclook(argc, argv, colevel)
char *argv[];
{
	int fpa[2], fpb[2], fpc[2], pid1, pid2, st;
	int iarg;
	char *s;
	FILE *ansf;
	struct filans *af;
	struct stat statbuf;
# define RD 0
# define WR 1
# define fmv(x,y) close(y); dup(x); close(x);
	/* we want to run chkbib and then lhunt and pipe in & out */
	pipe (fpa); /* from this program to chkbib */
	pipe (fpb); /* from chkbib to lhunt */
	pipe (fpc); /* from lhunt to us */
	if (  (pid1 = fork())  ==0)
	{
		fmv(fpa[RD], 0);
		fmv(fpb[WR], 1);
		close(fpa[WR]); 
		close(fpb[RD]); 
		close(fpc[RD]); 
		close(fpc[WR]); 
D 2
		execl("/usr/lib/refer/mkey", "mkey", "-s", 0);
E 2
I 2
		execl(_PATH_MKEY, "mkey", "-s", 0);
E 2
		_assert(0);
	}
	if (  (pid2 = fork()) == 0)
	{
		char coarg[20];
		sprintf(coarg, "-C%d", colevel);
		fmv(fpb[RD], 0);
		fmv(fpc[WR], 1);
		close(fpa[RD]); 
		close(fpa[WR]); 
		close(fpb[WR]); 
		close(fpc[RD]);
D 2
		execl("/usr/lib/refer/hunt", "hunt",
E 2
I 2
		execl(_PATH_HUNT, "hunt",
E 2
		/* "-P", */
D 2
		coarg, "-Ty", "-Fn", "/usr/dict/lookall/All", 0);
E 2
I 2
		coarg, "-Ty", "-Fn", _PATH_ALL, 0);
E 2
		_assert(0);
	}
	_assert (pid1 != -1); 
	_assert(pid2 != -1);
	close(fpb[RD]); 
	close(fpb[WR]); 
	close(fpa[RD]); 
	close(fpc[WR]);
D 2
	ansf = fopen("/dev/null", "r");
E 2
I 2
	ansf = fopen(_PATH_DEVNULL, "r");
E 2
	fmv (fpc[RD], ansf->_file);
	for(iarg=1; iarg<argc; iarg++)
		prod(fpa[WR], argv[iarg]);
	close(fpa[WR]);
	s=fnames;
	af=files;
	while (af < files+NFILES)
	{
		if (fgets(af->nm=s, NAMES, ansf)==0)
			break;
		trimnl(s);
		if (*s==0) continue;
		while (*s++);
		_assert(s<fnames+NAMES);
		st = stat(af->nm, &statbuf);
		if (st<0) continue;
		af->uid = statbuf.st_uid;
		af->fdate = statbuf.st_mtime;
		af->size = statbuf.st_size;
		af++;
	}
	fclose(ansf);
	return(af-files);
}

prod(f,s)
char *s;
{
	write (f, s, strlen(s));
	write (f, "\n", 1);
}
E 1
