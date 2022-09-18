h03446
s 00000/00000/00152
d D 8.1 93/06/06 22:31:14 bostic 9 8
c 4.4BSD snapshot (revision 8.1)
e
s 00006/00002/00146
d D 4.8 91/04/18 19:01:36 bostic 8 7
c new copyright; att/bsd/shared
e
s 00001/00001/00147
d D 4.7 91/03/02 13:39:26 bostic 7 6
c ANSI (real bug fix!)
e
s 00009/00007/00139
d D 4.6 89/05/11 13:35:34 bostic 6 5
c file reorg, pathnames.h, paths.h
e
s 00011/00012/00135
d D 4.5 84/02/14 20:36:54 rrh 5 4
c use popen, not /tmp files, dummy
e
s 00022/00002/00125
d D 4.4 84/01/20 13:22:31 rrh 4 3
c use /bin/mail; create a rationale Subject line; no longer need
c /usr/spool/secretmail/notice file, since /tmp is now used to create
c the body of the notice message
e
s 00001/00001/00126
d D 4.3 83/06/30 14:28:27 sam 3 2
c fix includes
e
s 00012/00011/00115
d D 4.2 83/05/18 18:36:13 mckusick 2 1
c update to use new directory access routines
e
s 00126/00000/00000
d D 4.1 83/03/30 12:08:48 sam 1 0
c date and time created 83/03/30 12:08:48 by sam
e
u
U
t
T
I 8
/*-
 * %sccs.include.proprietary.c%
 */

E 8
I 1
#ifndef lint
D 8
static char sccsid[] = "%W% %G%";
#endif
E 8
I 8
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 8

D 6
#include "xmail.h"
D 2
#include "sys/types.h"
#include "pwd.h"
#include "sys/stat.h"
#include "sys/dir.h"
E 2
I 2
#include <sys/types.h>
#include <pwd.h>
E 6
I 6
#include <sys/param.h>
E 6
#include <sys/stat.h>
D 3
#include <dir.h>
E 3
I 3
#include <sys/dir.h>
I 6
#include <pwd.h>
#include "xmail.h"
#include "pathnames.h"

E 6
E 3
E 2
extern int errno;
struct stat stbuf;
int uid, destuid;
D 7
char *myname, *dest, *keyfile[128], line[128];
E 7
I 7
char *myname, *dest, keyfile[128], line[128];
E 7
D 2
struct direct dbuf;
E 2
I 2
struct direct *dbuf;
E 2
D 6
char *maildir = "/usr/spool/secretmail/";
E 6
I 6
char *maildir = _PATH_SECRETMAIL;
E 6
D 2
FILE *kf, *mf, *df;
E 2
I 2
FILE *kf, *mf;
DIR *df;
E 2
MINT *a[42], *cd[6][128];
MINT *msg;
char buf[256], eof;
int dbg;
I 2
extern char *malloc(), *getlogin();

E 2
main(argc, argv) char **argv;
{	int i, nmax, len;
	char *p;
	long now;
	if(argc != 2)
		xfatal("mail to exactly one person");
	uid = getuid();
	p =getlogin();
	if(p == NULL)
		p = getpwuid(uid)->pw_name;
	myname = malloc(strlen(p)+1);
	strcpy(myname, p);
	dest = argv[1];
	strcpy(keyfile, maildir);
	strcat(keyfile, dest);
	strcat(keyfile, ".key");
	if(stat(keyfile, &stbuf) <0)
		xfatal("addressee not enrolled");
	destuid = getpwnam(dest)->pw_uid;
	if(destuid != stbuf.st_uid)
		fprintf(stderr, "warning: addressee's key file may be subverted\n");
	errno = 0;
	kf = fopen(keyfile, "r");
	if(kf == NULL)
		xfatal("addressee's key weird");
D 2
	df = fopen(maildir, "r");
E 2
I 2
	df = opendir(maildir);
E 2
	if(df == NULL)
	{	perror(maildir);
		exit(1);
	}
	strcpy(line, dest);
	strcat(line, ".%d");
	nmax = -1;
D 2
	for(; !feof(df);)
	{	fread(&dbuf, sizeof(dbuf), 1, df);
		if(dbuf.d_ino == 0) continue;
		if(sscanf(dbuf.d_name, line, &i) != 1)
E 2
I 2
	while ((dbuf=readdir(df))!=NULL)
	{	if(sscanf(dbuf->d_name, line, &i) != 1)
E 2
			continue;
		if(i>nmax) nmax = i;
	}
	nmax ++;
	for(i=0; i<10; i++)
	{	sprintf(line, "%s%s.%d", maildir, dest, nmax+i);
		if(creat(line, 0666) >= 0) break;
	}
	if(i==10) xfatal("cannot create mail file");
	mf = fopen(line, "w");
	init();
	time(&now);
	sprintf(buf, "From %s %s", myname, ctime(&now) );
#ifdef DBG
	dbg = 1;
#endif
	run();
D 4
	sprintf(buf, "mail %s <%snotice", dest, maildir);
	system(buf);
E 4
I 4
	{
D 5
		char	*tmpname = "/tmp/xsend.XXXXXX";
E 5
D 6
		char	hostname[32];
E 6
I 6
		char	hostname[MAXHOSTNAMELEN];
E 6
D 5
		FILE	*nf;
E 5
I 5
		FILE	*nf, *popen();
E 5
		struct	passwd	*passp;

D 5
		mktemp(tmpname);
		if ((nf = fopen(tmpname, "w")) == NULL)
			xfatal("cannot create notice file");
E 5
I 5
D 6
		sprintf(buf, "/bin/mail %s", dest);
E 6
I 6
		sprintf(buf, "%s %s", _PATH_MAIL, dest);
E 6
		if ((nf = popen(buf, "w")) == NULL)
D 6
			xfatal("cannot pipe to /bin/mail");
E 6
I 6
			xfatal("cannot pipe to %s", _PATH_MAIL);
E 6
E 5
		passp = getpwuid(getuid());
D 5
		if (passp == 0)
E 5
I 5
		if (passp == 0){
			pclose(nf);
E 5
			xfatal("Who are you?");
I 5
		}
E 5
		gethostname(hostname, sizeof(hostname));
D 5
		fprintf(nf, "Subject: %s@%s sent secret mail\n",
E 5
I 5
		fprintf(nf, "Subject: %s@%s sent you secret mail\n",
E 5
			passp->pw_name, hostname);
D 5
		fprintf(nf, "Your secret mail can be read on %s using ``xget''.\n",
E 5
I 5
		fprintf(nf,
		 "Your secret mail can be read on host %s using ``xget''.\n",
E 5
			hostname);
D 5
		fclose(nf);
		sprintf(buf, "/bin/mail %s < %s", dest, tmpname);
		system(buf);
		unlink(tmpname);
E 5
I 5
		pclose(nf);
E 5
	}
E 4
	exit(0);
}
mkcd()
{	int i, j, k, n;
	for(i=0; i<42; i++)
		nin(a[i], kf);
	fclose(kf);
	for(i=0; i<6; i++)
	for(j=0; j<128; j++)
		for(k=j, n=0; k>0 && n<7; n++, k>>=1)
			if(k&01) madd(cd[i][j], a[7*i+n], cd[i][j]);
}
encipher(s) char s[6];
{	int i;
	msub(msg, msg, msg);
	for(i=0; i<6; i++)
		madd(msg, cd[i][s[i]&0177], msg);
}
init()
{	int i, j;
	msg = itom(0);
	for(i=0; i<42; i++)
		a[i] = itom(0);
	for(i=0; i<6; i++)
	for(j=0; j<128; j++)
		cd[i][j] = itom(0);
	mkcd();
}
run()
{	char *p;
	int i, len, eof = 0;
	for(;;)
	{	len = strlen(buf);
		for(i=0; i<len/6; i++)
		{
			encipher(buf+6*i);
			nout(msg, mf);
		}
		p = buf;
		for(i *= 6; i<len; i++)
			*p++ = buf[i];
		if(eof) return;
		fgets(p, sizeof(buf)-6, stdin);
		if(strcmp(p, ".\n") == 0 || feof(stdin))
		{	for(i=0; i<6; i++) *p++ = ' ';
			*p = 0;
			eof = 1;
		}
	}
}
E 1
