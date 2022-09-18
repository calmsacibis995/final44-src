h00614
s 00006/00002/00101
d D 4.5 91/04/18 18:16:08 bostic 5 4
c new copyright; att/bsd/shared
e
s 00002/00001/00101
d D 4.4 91/03/01 19:08:03 bostic 4 3
c ANSI
e
s 00004/00012/00098
d D 4.3 89/05/11 10:58:26 bostic 3 2
c file reorg, pathnames.h, paths.h
e
s 00003/00001/00107
d D 4.2 83/08/11 21:13:29 sam 2 1
c standardize sccs keyword lines
e
s 00108/00000/00000
d D 4.1 83/02/12 19:06:17 shannon 1 0
c date and time created 83/02/12 19:06:17 by shannon
e
u
U
t
T
I 5
/*-
 * %sccs.include.proprietary.c%
 */

E 5
I 1
D 2
/*	%M%	%I%	%E%	*/
E 2
I 2
#ifndef lint
D 5
static char sccsid[] = "%W% %G%";
#endif
E 5
I 5
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 5
E 2

 /* t1.c: main control and input switching */
#
# include "t..c"
#include <signal.h>
I 3
#include "pathnames.h"

E 3
# ifdef gcos
/* required by GCOS because file is passed to "tbl" by troff preprocessor */
# define _f1 _f
extern FILE *_f[];
# endif

D 3
# ifdef unix
# define MACROS "/usr/lib/tmac.s"
# define PYMACS "/usr/lib/tmac.m"
# endif

# ifdef gcos
# define MACROS "cc/troff/smac"
# define PYMACS "cc/troff/mmac"
# endif

E 3
# define ever (;;)

main(argc,argv)
	char *argv[];
{
# ifdef unix
D 4
int badsig();
E 4
I 4
void badsig();
E 4
signal(SIGPIPE, badsig);
# endif
# ifdef gcos
if(!intss()) tabout = fopen("qq", "w"); /* default media code is type 5 */
# endif
exit(tbl(argc,argv));
}


tbl(argc,argv)
	char *argv[];
{
char line[BUFSIZ];
/* required by GCOS because "stdout" is set by troff preprocessor */
tabin=stdin; tabout=stdout;
setinp(argc,argv);
while (gets1(line))
	{
	fprintf(tabout, "%s\n",line);
	if (prefix(".TS", line))
		tableput();
	}
fclose(tabin);
return(0);
}
int sargc;
char **sargv;
setinp(argc,argv)
	char **argv;
{
	sargc = argc;
	sargv = argv;
	sargc--; sargv++;
	if (sargc>0)
		swapin();
}
swapin()
{
	while (sargc>0 && **sargv=='-') /* Mem fault if no test on sargc */
		{
		if (sargc<=0) return(0);
		if (match("-ms", *sargv))
			{
D 3
			*sargv = MACROS;
E 3
I 3
			*sargv = _PATH_MACROS;
E 3
			break;
			}
		if (match("-mm", *sargv))
			{
D 3
			*sargv = PYMACS;
E 3
I 3
			*sargv = _PATH_PYMACS;
E 3
			break;
			}
		if (match("-TX", *sargv))
			pr1403=1;
		sargc--; sargv++;
		}
	if (sargc<=0) return(0);
# ifdef unix
/* file closing is done by GCOS troff preprocessor */
	if (tabin!=stdin) fclose(tabin);
# endif
	tabin = fopen(ifile= *sargv, "r");
	iline=1;
# ifdef unix
/* file names are all put into f. by the GCOS troff preprocessor */
	fprintf(tabout, ".ds f. %s\n",ifile);
# endif
	if (tabin==NULL)
		error("Can't open file");
	sargc--;
	sargv++;
	return(1);
}
# ifdef unix
I 4
void
E 4
badsig()
{
signal(SIGPIPE, SIG_IGN);
 exit(0);
}
# endif
E 1
