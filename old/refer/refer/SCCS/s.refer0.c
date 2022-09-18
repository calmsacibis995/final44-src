h09434
s 00006/00002/00033
d D 4.2 91/04/18 16:44:09 bostic 2 1
c new copyright; att/bsd/shared
e
s 00035/00000/00000
d D 4.1 83/05/06 23:33:58 tut 1 0
c date and time created 83/05/06 23:33:58 by tut
e
u
U
t
T
I 2
/*-
 * %sccs.include.proprietary.c%
 */

E 2
I 1
#ifndef lint
D 2
static char *sccsid = "%W% (Berkeley) %G%";
#endif
E 2
I 2
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 2

#include "refer..c"

FILE *in = stdin;
FILE *fo = stdout;
FILE *ftemp = stdout;
int endpush = 0;
int sort = 0;
int labels = 0;
int keywant = 0;
int bare = 0;
int biblio = 0;
int science = 0;
int postpunct = 0;
int authrev = 0;
char *smallcaps = "";
char *keystr = "AD";
char *convert = "X.AP";
int nmlen = 0, dtlen = 0;
char *rdata[NSERCH];
char **search = rdata;
int refnum = 0;
char reftext[NRFTXT];
char *reftable[NRFTBL];
char *rtp = reftext;
int sep = '\n';
char tfile[NTFILE];
char ofile[NTFILE];
char gfile[NTFILE];
char hidenam[NTFILE];
char *Ifile = "standard input";
int Iline = 0;
E 1
