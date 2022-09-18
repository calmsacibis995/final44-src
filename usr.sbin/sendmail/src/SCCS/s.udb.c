h40446
s 00004/00004/01019
d D 8.23 95/05/28 11:50:17 eric 67 66
c lint
e
s 00021/00004/01002
d D 8.22 95/05/27 07:43:28 eric 66 65
c fix compilation when compiled with -DHESIOD=1 -DNEWDB=0
e
s 00008/00018/00998
d D 8.21 95/05/23 10:21:29 eric 65 64
c Hesiod doesn't dynamically allocate space, despite the claims in
c the documentation
e
s 00001/00001/01015
d D 8.20 95/04/23 14:03:19 eric 64 63
c updates for new DSN drafts
e
s 00001/00001/01015
d D 8.19 95/04/21 09:57:49 eric 63 62
c update copyright notice
e
s 00020/00003/00996
d D 8.18 95/04/12 08:19:37 eric 62 61
c make it so it will compile without NEWDB (but with HESIOD); better errors
e
s 00001/00002/00998
d D 8.17 95/03/31 10:52:30 eric 61 60
c pull getpwXXX and gethostbyXXX calls out into conf.c so they can
c be tweaked
e
s 00002/00001/00998
d D 8.16 95/03/27 09:25:55 eric 60 59
c more cleanup for DSN drafts
e
s 00001/00001/00998
d D 8.15 95/03/20 19:22:35 eric 59 58
c cleanup hesiod botch
e
s 00004/00003/00995
d D 8.14 95/03/15 05:45:00 eric 58 57
c fix a possible core dump where Hesiod and UDB touch
e
s 00033/00000/00965
d D 8.13 95/03/12 17:04:01 eric 57 56
c add userdb map class
e
s 00009/00011/00956
d D 8.12 94/11/22 22:25:15 eric 56 55
c clean up several small problems with file delivery, error detection,
c and return receipts
e
s 00008/00000/00959
d D 8.11 94/09/08 11:30:08 eric 55 54
c debugging output
e
s 00001/00001/00958
d D 8.10 94/06/17 17:40:16 eric 54 53
c compatibility with BIND 4.9.3 (just cleanup)
e
s 00001/00001/00958
d D 8.9 94/06/17 11:13:03 eric 53 52
c Cray fixes from Eric Wassenaar
e
s 00009/00000/00950
d D 8.8 94/04/14 09:42:50 eric 52 51
c give return-receipt on delivery to mailing lists (instead of to the
c members of that list) and suppress Return-Receipt-To: in subsequent
c deliveries to avoid denial of service attacks and generally improve
c the semantics
e
s 00239/00002/00711
d D 8.7 94/04/12 14:37:55 eric 51 50
c hesiod changes from Todd Miller
e
s 00001/00001/00712
d D 8.6 94/03/11 14:41:49 eric 50 49
c change NAMED_BIND to a 0/1 flag to allow Makefile override
e
s 00000/00001/00713
d D 8.5 94/01/22 10:29:30 eric 49 48
c avoid unnecessary <sys/time.h> inclusion
e
s 00001/00001/00713
d D 8.4 93/11/25 11:23:24 eric 48 47
c work around Ultrix problem: gethostbyname can return large h_length
e
s 00026/00011/00688
d D 8.3 93/08/25 13:19:41 eric 47 46
c generalize udbsender in anticipation of UDB map classes
e
s 00006/00004/00693
d D 8.2 93/07/27 21:35:23 eric 46 45
c improved debugging
e
s 00002/00002/00695
d D 8.1 93/06/07 10:32:33 bostic 45 44
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00010/00000/00687
d D 6.23 93/06/02 07:27:38 eric 44 43
c fix problem with multiple databases -- keybuf trashed
e
s 00002/00002/00685
d D 6.22 93/05/28 16:24:47 eric 43 42
c make SCCS id string reflect USERDB compile flag
e
s 00001/00001/00686
d D 6.21 93/05/27 11:37:51 eric 42 41
c prototype functions
e
s 00017/00000/00670
d D 6.20 93/05/03 19:02:01 eric 41 40
c first cut at :mailsender extension
e
s 00002/00002/00668
d D 6.19 93/05/01 15:18:38 eric 40 39
c don't use %e for syslog errors -- either %m or errstring
e
s 00005/00000/00665
d D 6.18 93/05/01 12:26:40 eric 39 38
c minor tweaking of syslog levels & compile fixes for SunOS & Ultrix
e
s 00001/00001/00664
d D 6.17 93/04/26 13:14:05 eric 38 37
c have getmxrr look at $=w to determine local host name
e
s 00001/00000/00664
d D 6.16 93/03/30 15:50:04 eric 37 36
c hooks for eventual better handling of SMTP recipients
e
s 00000/00001/00664
d D 6.15 93/03/23 16:38:51 eric 36 35
c eliminate use of sin_len
e
s 00002/00001/00663
d D 6.14 93/03/19 16:24:40 eric 35 34
c initial hooks for ISO networking
e
s 00000/00001/00664
d D 6.13 93/03/17 09:55:31 eric 34 33
c clean up file locking (create a lockfile() routine in conf.c)
e
s 00004/00001/00661
d D 6.12 93/02/23 09:19:10 eric 33 32
c fix botch in SMTP VRFY code (assumed all users were local)
e
s 00002/00002/00660
d D 6.11 93/02/23 06:32:02 eric 32 31
c overhaul status of SMTP reply codes
e
s 00005/00000/00657
d D 6.10 93/02/20 15:26:50 eric 31 30
c add EF_VRFYONLY support
e
s 00008/00004/00649
d D 6.9 93/02/20 13:46:56 eric 30 29
c close cached MCI connections after a fork; add p (privacy) and b
c (min blocks free) options; fix selfref code; clean up $#error format
e
s 00020/00002/00633
d D 6.8 93/02/19 10:37:15 eric 29 28
c make duplicate deletion more global
e
s 00001/00001/00634
d D 6.7 93/02/18 20:22:45 eric 28 27
c move the meta-characters from C0 into C1 space
e
s 00002/00001/00633
d D 6.6 93/02/15 16:45:03 eric 27 26
c Allow saving in ~/dead.letter; clean up VRFY output; fix bogus
c error message in udbexpand; null terminate host buffers in buildaddr
c (broken in 6.21).
e
s 00005/00000/00629
d D 6.5 93/02/14 14:41:52 eric 26 25
c HPUX and OSF/1 support; fix SMTP reply codes & multiple SMTP error
c problem; consider cache timeout non-permanent; be more graceful on OS
c failures; log forward, alias, and userdb expansions on log level 10
e
s 00000/00001/00629
d D 6.4 93/01/28 17:04:57 eric 25 24
c fix the System 5 compatilibility to be compatible with the rest
c of the world.
e
s 00000/00002/00630
d D 6.3 93/01/28 10:16:02 eric 24 23
c System 5 compatibility, misc fixes
e
s 00006/00000/00626
d D 6.2 93/01/20 13:20:43 eric 23 22
c put getmxrr on NAMED_BIND
e
s 00000/00000/00626
d D 6.1 92/12/21 16:08:55 eric 22 21
c Release 6
e
s 00004/00004/00622
d D 5.21 92/12/20 11:14:30 eric 21 20
c change random constants to be #defines
e
s 00004/00004/00622
d D 5.20 92/11/14 11:34:42 eric 20 19
c (partially) ANSI-fy it
e
s 00007/00005/00619
d D 5.19 92/07/12 14:10:13 eric 19 18
c reduce number of instances of CurEnv by passing it as a parameter
e
s 00001/00001/00623
d D 5.18 92/05/25 13:13:45 eric 18 17
c add generalized database mapping (using the K config line and
c $( ... $) syntaxes); $[ ... $] is now a special case
e
s 00001/00000/00623
d D 5.17 91/12/15 14:28:15 eric 17 16
c clear errno after trying to open the database list
e
s 00004/00004/00619
d D 5.16 91/12/15 14:10:24 eric 16 15
c drop STATIC
e
s 00194/00017/00429
d D 5.15 91/12/15 13:59:50 eric 15 14
c separate support for header vs envelope sender; if users are in the
c database, map them to a canonical name (e.g., @CS.Berkeley.EDU) in header.
e
s 00028/00015/00418
d D 5.14 91/12/14 14:35:34 eric 14 13
c allow udbexpand to return temporary failure errors
e
s 00005/00002/00428
d D 5.13 91/12/12 18:51:38 eric 13 12
c give initialization a chance
e
s 00005/00000/00425
d D 5.12 91/12/12 18:39:53 eric 12 11
c allow for default UDB spec at compile time
e
s 00001/00000/00424
d D 5.11 91/12/04 10:35:48 eric 11 10
c set udb_dbname
e
s 00006/00006/00418
d D 5.10 91/12/04 10:22:47 eric 10 9
c fix misunderstanding of seq(R_CURSOR) semantics
e
s 00001/00001/00423
d D 5.9 91/11/20 11:06:51 eric 9 8
c more null pointer fixes
e
s 00001/00001/00423
d D 5.8 91/11/20 10:25:23 eric 8 7
c fix silly indirect-through-zero bug
e
s 00002/00039/00422
d D 5.7 91/11/19 10:18:15 eric 7 6
c delete remote implementation in lieu of better protocol
e
s 00000/00001/00461
d D 5.6 91/11/13 19:31:24 eric 6 5
c sin_len is non-compatible (but not required)
e
s 00100/00040/00362
d D 5.5 91/10/13 08:31:38 eric 5 4
c beginnings of implementation of options on UDB specifications
e
s 00206/00106/00196
d D 5.4 91/10/11 17:17:33 eric 4 3
c make it work with udbd server
e
s 00233/00050/00069
d D 5.3 91/10/11 12:46:11 eric 3 2
c fixes for user database and new config files
e
s 00001/00001/00118
d D 5.2 91/09/23 15:09:25 bostic 2 1
c hash_open -> dbopen
e
s 00119/00000/00000
d D 5.1 91/07/26 19:00:38 eric 1 0
c date and time created 91/07/26 19:00:38 by eric
e
u
U
t
T
I 1
/*
D 63
 * Copyright (c) 1983 Eric P. Allman
E 63
I 63
 * Copyright (c) 1983, 1995 Eric P. Allman
E 63
D 45
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.
E 45
I 45
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 45
 *
 * %sccs.include.redist.c%
 */

I 43
#include "sendmail.h"

E 43
#ifndef lint
D 3
static char sccsid [] = "%W% (Berkeley) %G%";
E 3
I 3
D 66
#ifdef USERDB
E 66
I 66
#if !USERDB
E 66
static char sccsid [] = "%W% (Berkeley) %G% (with USERDB)";
#else
static char sccsid [] = "%W% (Berkeley) %G% (without USERDB)";
E 3
#endif
I 3
#endif
E 3
D 43

#include "sendmail.h"
E 43

D 66
#ifdef USERDB
E 66
I 66
#if USERDB
E 66

D 25
#include <sys/file.h>
E 25
I 3
D 49
#include <sys/time.h>
E 49
I 14
#include <errno.h>
E 14
D 34
#include <fcntl.h>
E 34
D 61
#include <netdb.h>
E 61
E 3
D 66
#include <db.h>
E 66

I 66
#ifdef NEWDB
# include <db.h>
#else
# define DBT	struct _data_base_thang_
DBT
{
	void	*data;		/* pointer to data */
	size_t	size;		/* length of data */
};
#endif

E 66
I 51
#ifdef HESIOD
D 66
#include <hesiod.h>
E 66
I 66
# include <hesiod.h>
E 66
#endif /* HESIOD */

E 51
/*
D 5
**  UDBEXPAND -- look up user in database and expand
E 5
I 5
D 18
**  UDBEXPAND.C -- interface between sendmail and Berkeley User Data Base.
E 18
I 18
**  UDB.C -- interface between sendmail and Berkeley User Data Base.
E 18
E 5
**
D 5
**	Parameters:
**		a -- address to expand.
**		sendq -- pointer to head of sendq to put the expansions in.
**
**	Returns:
**		none.
**
**	Side Effects:
**		Modifies sendq.
E 5
I 5
**	This depends on the 4.4BSD db package.
E 5
*/

I 4
D 5
int	UdbPort = 1616;
int	UdbTimeout = 10;
E 5

E 4
I 3
struct udbent
{
	char	*udb_spec;		/* string version of spec */
	int	udb_type;		/* type of entry */
I 15
	char	*udb_default;		/* default host for outgoing mail */
E 15
	union
	{
		/* type UE_REMOTE -- do remote call for lookup */
		struct
		{
D 4
			int		_udb_addrlen;	/* length of addr */
E 4
			struct sockaddr_in _udb_addr;	/* address */
			int		_udb_timeout;	/* timeout */
		} udb_remote;
D 4
#define udb_addrlen	udb_u.udb_remote._udb_addrlen
E 4
#define udb_addr	udb_u.udb_remote._udb_addr
#define udb_timeout	udb_u.udb_remote._udb_timeout

		/* type UE_FORWARD -- forward message to remote */
		struct
		{
			char	*_udb_fwdhost;	/* name of forward host */
		} udb_forward;
#define udb_fwdhost	udb_u.udb_forward._udb_fwdhost

I 66
#ifdef NEWDB
E 66
D 15
		/* type UE_LOOKUP -- lookup in local database */
E 15
I 15
		/* type UE_FETCH -- lookup in local database */
E 15
		struct
		{
			char	*_udb_dbname;	/* pathname of database */
			DB	*_udb_dbp;	/* open database ptr */
		} udb_lookup;
#define udb_dbname	udb_u.udb_lookup._udb_dbname
#define udb_dbp		udb_u.udb_lookup._udb_dbp
I 66
#endif
E 66
	} udb_u;
};

#define UDB_EOLIST	0	/* end of list */
#define UDB_SKIP	1	/* skip this entry */
#define UDB_REMOTE	2	/* look up in remote database */
D 15
#define UDB_LOOKUP	3	/* look up in local database */
E 15
I 15
#define UDB_DBFETCH	3	/* look up in local database */
E 15
#define UDB_FORWARD	4	/* forward to remote host */
I 51
#define UDB_HESIOD	5	/* look up via hesiod */
E 51

#define MAXUDBENT	10	/* maximum number of UDB entries */

I 5

struct option
{
	char	*name;
	char	*val;
};
/*
**  UDBEXPAND -- look up user in database and expand
**
**	Parameters:
**		a -- address to expand.
**		sendq -- pointer to head of sendq to put the expansions in.
I 56
**		aliaslevel -- the current alias nesting depth.
**		e -- the current envelope.
E 56
**
**	Returns:
D 14
**		none.
E 14
I 14
**		EX_TEMPFAIL -- if something "odd" happened -- probably due
**			to accessing a file on an NFS server that is down.
**		EX_OK -- otherwise.
E 14
**
**	Side Effects:
**		Modifies sendq.
*/

int	UdbPort = 1616;
int	UdbTimeout = 10;

E 5
I 4
D 15
struct udbent	UdbEnts[MAXUDBENT + 1];
int		UdbSock = -1;
E 15
I 15
D 16
STATIC struct udbent	UdbEnts[MAXUDBENT + 1];
STATIC int		UdbSock = -1;
STATIC bool		UdbInitialized = FALSE;
E 16
I 16
struct udbent	UdbEnts[MAXUDBENT + 1];
int		UdbSock = -1;
bool		UdbInitialized = FALSE;
E 16
E 15
E 4

E 3
D 14
void
E 14
I 14
int
E 14
D 19
udbexpand(a, sendq)
E 19
I 19
D 56
udbexpand(a, sendq, e)
E 56
I 56
udbexpand(a, sendq, aliaslevel, e)
E 56
E 19
	register ADDRESS *a;
	ADDRESS **sendq;
I 56
	int aliaslevel;
E 56
I 19
	register ENVELOPE *e;
E 19
{
	int i;
D 67
	register char *p;
E 67
D 4
	auto char *class;
	auto char *list;
E 4
	DBT key;
	DBT info;
D 3
	static DB *dbp = NULL;
E 3
D 4
	register char *bp;
E 4
I 3
D 15
	static bool firstcall = TRUE;
E 15
D 4
	static int udbsock = -1;
E 4
	bool breakout;
	register struct udbent *up;
D 4
	struct udbent udbents[MAXUDBENT + 1];
E 4
I 4
	int keylen;
I 30
	int naddrs;
E 30
D 21
	char keybuf[128];
E 4
E 3
	char buf[8192];
E 21
I 21
	char keybuf[MAXKEY];
	char buf[BUFSIZ];
E 21

	if (tTd(28, 1))
D 29
		printf("expand(%s)\n", a->q_paddr);
E 29
I 29
		printf("udbexpand(%s)\n", a->q_paddr);
E 29

	/* make certain we are supposed to send to this address */
D 3
	if (bitset(QDONTSEND, a->q_flags))
E 3
I 3
D 13
	if (bitset(QDONTSEND, a->q_flags) ||
	    UdbSpec == NULL || UdbSpec[0] == '\0')
E 13
I 13
D 33
	if (bitset(QDONTSEND, a->q_flags))
E 33
I 33
	if (bitset(QDONTSEND|QVERIFIED, a->q_flags))
E 33
E 13
E 3
D 14
		return;
E 14
I 14
		return EX_OK;
E 14
D 19
	CurEnv->e_to = a->q_paddr;
E 19
I 19
	e->e_to = a->q_paddr;
E 19

D 3
	/* if necessary, open the database */
	if (dbp == NULL)
E 3
I 3
	/* on first call, locate the database */
D 15
	if (firstcall)
E 15
I 15
	if (!UdbInitialized)
E 15
E 3
	{
I 4
D 14
		extern void _udbx_init();
E 14
I 14
		extern int _udbx_init();
E 14

D 14
		_udbx_init();
E 14
I 14
		if (_udbx_init() == EX_TEMPFAIL)
			return EX_TEMPFAIL;
E 14
E 4
D 3
		if (UdbFileName == NULL || UdbFileName[0] == '\0')
E 3
I 3
D 15
		firstcall = FALSE;
E 15
D 4
		p = UdbSpec;
		up = udbents;
		for (;;)
E 3
		{
D 3
			if (tTd(28, 4))
				printf("no userdb specified\n");
			return;
		}
D 2
		dbp = hash_open(UdbFileName, O_RDONLY, 0644, NULL);
E 2
I 2
		dbp = dbopen(UdbFileName, O_RDONLY, 0644, DB_HASH, NULL);
E 2
		if (dbp == NULL)
		{
			extern int errno;
E 3
I 3
			char *spec;
			auto int rcode;
			int nmx;
			char *mxhosts[MAXMXHOSTS + 1];
E 4
I 4
	}
I 13

	/* short circuit the process if no chance of a match */
	if (UdbSpec == NULL || UdbSpec[0] == '\0')
D 14
		return;
E 14
I 14
		return EX_OK;
E 14
E 13
E 4
E 3

I 51
	/* short circuit name begins with '\\' since it can't possibly match */
	if (a->q_user[0] == '\\')
		return EX_OK;

E 51
D 3
			if (tTd(28, 2))
				printf("cannot open %s: %d\n", UdbFileName, errno);
			return;
E 3
I 3
D 4
			while (*p == ' ' || *p == '\t' || *p == ',')
				p++;
			if (*p == '\0')
				break;
			spec = p;
			p = index(p, ',');
			if (*p != '\0')
				*p++ = '\0';
			switch (*spec)
			{
			  case '*':	/* search remote database */
				expand("\001j", buf, &buf[sizeof(buf) - 1], CurEnv);
				nmx = getmxrr(spec + 1, mxhosts, buf, &rcode);
				for (i = 0; i < nmx; i++)
				{
					register struct hostent *h;
E 4
I 4
	/* if name is too long, assume it won't match */
	if (strlen(a->q_user) > sizeof keybuf - 12)
D 14
		return;
E 14
I 14
		return EX_OK;
E 14
E 4

D 4
					h = gethostbyname(mxhosts[i]);
					if (h == NULL)
						continue;
					up->udb_type = UDB_REMOTE;
					up->udb_addr.sin_family = h->h_addrtype;
					up->udb_addrlen = h->h_length;
					bcopy(h->h_addr_list[0],
					      (char *) &up->udb_addr.sin_addr,
					      h->h_length);
					up++;
				}
E 4
I 4
	/* if name begins with a colon, it indicates our metadata */
	if (a->q_user[0] == ':')
D 14
		return;
E 14
I 14
		return EX_OK;
E 14
E 4

D 4
				/* set up a datagram socket */
				if (udbsock < 0)
				{
					udbsock = socket(AF_INET, SOCK_DGRAM, 0);
					(void) fcntl(udbsock, F_SETFD, 1);
				}
				break;
E 4
I 4
	/* build actual database key */
	(void) strcpy(keybuf, a->q_user);
	(void) strcat(keybuf, ":maildrop");
	keylen = strlen(keybuf);
E 4

D 4
			  case '@':	/* forward to remote host */
				up->udb_type = UDB_FORWARD;
				up->udb_fwdhost = spec + 1;
				up++;
				break;

			  case '/':	/* look up remote name */
				up->udb_dbp = dbopen(spec, O_RDONLY, 0644, DB_BTREE, NULL);
				if (up->udb_dbp == NULL)
					break;
				up->udb_type = UDB_LOOKUP;
				up++;
				break;
			}
E 3
		}
I 3
		up->udb_type = UDB_EOLIST;
E 3
	}

E 4
D 3
	key.data = a->q_user;
	key.size = strlen(key.data);
	i = dbp->get(dbp, &key, &info, R_NOOVERWRITE);
	if (i != 0 || info.size <= 0)
E 3
I 3
	breakout = FALSE;
D 4
	for (up = udbents; !breakout; up++)
E 4
I 4
	for (up = UdbEnts; !breakout; up++)
E 4
E 3
	{
D 3
		if (i < 0)
			syserr("udbexpand: db-get stat %s");
		if (tTd(28, 2))
			printf("expand: no match on %s\n", key.data);
		return;
	}
E 3
I 3
		char *user;
D 24
		struct timeval timeout;
		fd_set fdset;
E 24
E 3

D 3
	/* extract the class (first string) and data (second string) */
	i = strlen((char *) info.data) + 1;
	p = (char *) info.data + i;
	i = info.size - i;
E 3
I 3
		/*
		**  Select action based on entry type.
		**
		**	On dropping out of this switch, "class" should
		**	explain the type of the data, and "user" should
		**	contain the user information.
		*/
E 3

D 3
	/* use internal buffer if it will fit; otherwise malloc */
	if (i < sizeof buf)
		bp = buf;
	else
		bp = xalloc(i + 1);
	bcopy(p, bp, i);
	bp[i] = '\0';
E 3
I 3
		switch (up->udb_type)
		{
I 62
#ifdef NEWDB
E 62
D 15
		  case UDB_LOOKUP:
E 15
I 15
		  case UDB_DBFETCH:
E 15
D 4
			key.data = a->q_user;
			key.size = strlen(key.data);
			i = (*up->udb_dbp->get)(up->udb_dbp, &key, &info, 0);
E 4
I 4
			key.data = keybuf;
			key.size = keylen;
I 44
			if (tTd(28, 80))
D 46
				printf("udbexpand: trying %s\n", keybuf);
E 46
I 46
D 51
				printf("udbexpand: trying %s (%d)\n",
E 51
I 51
				printf("udbexpand: trying %s (%d) via db\n",
E 51
					keybuf, keylen);
E 46
E 44
			i = (*up->udb_dbp->seq)(up->udb_dbp, &key, &info, R_CURSOR);
E 4
D 14
			if (i != 0 || info.size <= 0)
E 14
I 14
			if (i > 0 || info.size <= 0)
E 14
			{
D 14
				if (i < 0)
					syserr("udbexpand: db-get stat %s");
E 14
				if (tTd(28, 2))
D 4
					printf("expand: no match on %s\n", key.data);
E 4
I 4
D 29
					printf("expand: no match on %s\n", keybuf);
E 29
I 29
D 46
					printf("udbexpand: no match on %s\n", keybuf);
E 46
I 46
					printf("udbexpand: no match on %s (%d)\n",
						keybuf, keylen);
E 46
E 29
E 4
				continue;
			}
I 44
			if (tTd(28, 80))
				printf("udbexpand: match %.*s: %.*s\n",
					key.size, key.data, info.size, info.data);
E 44
E 3

I 30
			naddrs = 0;
			a->q_flags &= ~QSELFREF;
E 30
D 3
	if (tTd(28, 1))
		printf("Class %s: %s\n", info.data, bp);
E 3
I 3
D 4
			/* extract the class (first string) and data (second string) */
			class = info.data;
			i = strlen((char *) info.data) + 1;
			p = (char *) info.data + i;
			i = info.size - i;
E 4
I 4
D 10
			/* there is at least one match -- start processing */
			breakout = TRUE;
			do
E 10
I 10
			while (i == 0 && key.size == keylen &&
					bcmp(key.data, keybuf, keylen) == 0)
E 10
			{
I 31
				if (bitset(EF_VRFYONLY, e->e_flags))
I 33
				{
					a->q_flags |= QVERIFIED;
I 37
					e->e_nrcpts++;
E 37
E 33
					return EX_OK;
I 33
				}
E 33

E 31
I 10
				breakout = TRUE;
E 10
				if (info.size < sizeof buf)
					user = buf;
				else
					user = xalloc(info.size + 1);
				bcopy(info.data, user, info.size);
				user[info.size] = '\0';
E 4
E 3

D 3
	/* do special processing based on class */
	if (strcmp((char *) info.data, "user") == 0)
	{
		message(Arpa_Info, "expanded to (%s) %s", info.data, bp);
		AliasLevel++;
		sendtolist(bp, a, sendq);
		AliasLevel--;
E 3
I 3
D 4
			/* use internal buffer if it will fit; otherwise malloc */
			if (i < sizeof buf)
				user = buf;
			else
				user = xalloc(i + 1);
			bcopy(p, user, i);
			user[i] = '\0';
E 4
I 4
D 32
				message(Arpa_Info, "expanded to %s", user);
E 32
I 32
				message("expanded to %s", user);
E 32
I 26
#ifdef LOG
				if (LogLevel >= 10)
					syslog(LOG_INFO, "%s: expand %s => %s",
						e->e_id, e->e_to, user);
#endif
E 26
D 56
				AliasLevel++;
D 19
				sendtolist(user, a, sendq);
E 19
I 19
D 30
				sendtolist(user, a, sendq, e);
E 30
I 30
				naddrs += sendtolist(user, a, sendq, e);
E 30
E 19
				AliasLevel--;
E 56
I 56
				naddrs += sendtolist(user, a, sendq, aliaslevel + 1, e);
E 56

				if (user != buf)
					free(user);

				/* get the next record */
				i = (*up->udb_dbp->seq)(up->udb_dbp, &key, &info, R_NEXT);
D 10
			} while (i == 0 && key.size == keylen &&
					bcmp(key.data, keybuf, keylen) == 0);
E 10
I 10
			}
I 44

			/* if nothing ever matched, try next database */
			if (!breakout)
				continue;

E 44
I 29
D 30
			if (!bitset(QSELFREF, a->q_flags))
E 30
I 30
			if (naddrs > 0 && !bitset(QSELFREF, a->q_flags))
E 30
			{
				if (tTd(28, 5))
				{
					printf("udbexpand: QDONTSEND ");
					printaddr(a, FALSE);
				}
				a->q_flags |= QDONTSEND;
			}
E 29
I 14
			if (i < 0)
			{
D 27
				syserr("udbexpand: db-get stat %s");
E 27
I 27
				syserr("udbexpand: db-get %.*s stat %d",
					key.size, key.data, i);
E 27
				return EX_TEMPFAIL;
			}
I 41

			/*
			**  If this address has a -request address, reflect
			**  it into the envelope.
			*/

			(void) strcpy(keybuf, a->q_user);
			(void) strcat(keybuf, ":mailsender");
			keylen = strlen(keybuf);
			key.data = keybuf;
			key.size = keylen;
			i = (*up->udb_dbp->get)(up->udb_dbp, &key, &info, 0);
			if (i != 0 || info.size <= 0)
				break;
			a->q_owner = xalloc(info.size + 1);
			bcopy(info.data, a->q_owner, info.size);
			a->q_owner[info.size] = '\0';
I 52

			/* announce delivery; NORECEIPT bit set later */
			if (e->e_xfp != NULL)
			{
				fprintf(e->e_xfp,
					"Message delivered to mailing list %s\n",
					a->q_paddr);
D 60
				e->e_flags |= EF_SENDRECEIPT;
E 60
			}
I 60
			e->e_flags |= EF_SENDRECEIPT;
D 64
			a->q_flags |= QREPORT|QEXPLODED;
E 64
I 64
			a->q_flags |= QDELIVERED|QEXPANDED;
E 64
E 60
E 52
E 41
E 14
E 10
E 4
			break;
I 62
#endif
E 62

I 51
#ifdef HESIOD
		  case UDB_HESIOD:
			key.data = keybuf;
			key.size = keylen;
			if (tTd(28, 80))
				printf("udbexpand: trying %s (%d) via hesiod\n",
					keybuf, keylen);
			/* look up the key via hesiod */
			i = hes_udb_get(&key, &info);
D 65
			if (i > 0 || info.size <= 0)
E 65
I 65
			if (i < 0)
E 65
			{
I 65
				syserr("udbexpand: hesiod-get %.*s stat %d",
					key.size, key.data, i);
				return EX_TEMPFAIL;
			}
			else if (i > 0 || info.size <= 0)
			{
E 65
				if (tTd(28, 2))
				printf("udbexpand: no match on %s (%d)\n",
					keybuf, keylen);
				continue;
			}
			if (tTd(28, 80))
				printf("udbexpand: match %.*s: %.*s\n",
					key.size, key.data, info.size, info.data);
			a->q_flags &= ~QSELFREF;

			if (bitset(EF_VRFYONLY, e->e_flags))
			{
				a->q_flags |= QVERIFIED;
				e->e_nrcpts++;
D 65
				free(info.data);
E 65
				return EX_OK;
			}

			breakout = TRUE;
			if (info.size < sizeof buf)
				user = buf;
			else
				user = xalloc(info.size + 1);
			bcopy(info.data, user, info.size);
			user[info.size] = '\0';
D 65
			free(info.data);
E 65

			message("hesioded to %s", user);
#ifdef LOG
			if (LogLevel >= 10)
				syslog(LOG_INFO, "%s: hesiod %s => %s",
					e->e_id, e->e_to, user);
#endif
D 56
			AliasLevel++;
			naddrs = sendtolist(user, a, sendq, e);
			AliasLevel--;
E 56
I 56
			naddrs = sendtolist(user, a, sendq, aliaslevel + 1, e);
E 56

			if (user != buf)
				free(user);

			if (naddrs > 0 && !bitset(QSELFREF, a->q_flags))
			{
				if (tTd(28, 5))
				{
					printf("udbexpand: QDONTSEND ");
					printaddr(a, FALSE);
				}
				a->q_flags |= QDONTSEND;
			}
D 65
			if (i < 0)
			{
				syserr("udbexpand: hesiod-get %.*s stat %d",
					key.size, key.data, i);
				return EX_TEMPFAIL;
			}
E 65

			/*
			**  If this address has a -request address, reflect
			**  it into the envelope.
			*/

			(void) strcpy(keybuf, a->q_user);
			(void) strcat(keybuf, ":mailsender");
			keylen = strlen(keybuf);
			key.data = keybuf;
			key.size = keylen;
			i = hes_udb_get(&key, &info);
			if (i != 0 || info.size <= 0)
				break;
			a->q_owner = xalloc(info.size + 1);
			bcopy(info.data, a->q_owner, info.size);
			a->q_owner[info.size] = '\0';
D 65
			free(info.data);
E 65
			break;
#endif /* HESIOD */

E 51
		  case UDB_REMOTE:
D 4
			if (sendto(udbsock, a->q_user, strlen(a->q_user), 0,
E 4
I 4
D 7
			if (sendto(UdbSock, keybuf, keylen, 0,
E 4
				   (struct sockaddr *) &up->udb_addr,
D 4
				   up->udb_addrlen) < 0)
E 4
I 4
				   sizeof up->udb_addr) < 0)
E 4
			{
				continue;
			}
			timeout.tv_sec = up->udb_timeout / 10;
			timeout.tv_usec = (up->udb_timeout % 10) * 100000;
			do
			{
				FD_ZERO(&fdset);
D 4
				FD_SET(udbsock, &fdset);
E 4
I 4
				FD_SET(UdbSock, &fdset);
E 4
				i = select(FD_SETSIZE, &fdset, NULL, NULL, &timeout);
D 4
			} while (i > 0 && !FD_ISSET(udbsock, &fdset));
E 4
I 4
			} while (i > 0 && !FD_ISSET(UdbSock, &fdset));
E 4
			if (i <= 0)
				continue;
D 4
			i = recvfrom(udbsock, buf, sizeof buf - 1, 0, NULL, NULL);
E 4
I 4
			i = recvfrom(UdbSock, buf, sizeof buf - 1, 0, NULL, NULL);
E 4
			if (i < 0)
				continue;
D 4
			class = buf;
			user = &buf[strlen(buf)];
			buf[i] = '\0';
E 4
I 4
			if (buf[0] != ' ' && buf[0] != '-')
				continue;
			breakout = TRUE;
			while (buf[0] == ' ' || buf[0] == '-')
			{
				user = &buf[1];
				buf[i] = '\0';
				message(Arpa_Info, "expanded to %s", user);
				AliasLevel++;
				sendtolist(user, a, sendq);
				AliasLevel--;

				/* try for next record */
				if (buf[0] == ' ')
					break;
				i = recvfrom(UdbSock, buf, sizeof buf - 1, 0, NULL, NULL);
				if (i < 0)
					break;
			}
E 4
			break;
E 7
I 7
			/* not yet implemented */
			continue;
E 7

		  case UDB_FORWARD:
I 31
			if (bitset(EF_VRFYONLY, e->e_flags))
				return EX_OK;
E 31
D 4
			class = "forward";
E 4
			i = strlen(up->udb_fwdhost) + strlen(a->q_user) + 1;
			if (i < sizeof buf)
				user = buf;
			else
				user = xalloc(i + 1);
			(void) sprintf(user, "%s@%s", a->q_user, up->udb_fwdhost);
I 4
D 32
			message(Arpa_Info, "expanded to %s", user);
E 32
I 32
			message("expanded to %s", user);
E 32
I 30
			a->q_flags &= ~QSELFREF;
E 30
D 56
			AliasLevel++;
D 19
			sendtolist(user, a, sendq);
E 19
I 19
D 30
			sendtolist(user, a, sendq, e);
E 30
I 30
			naddrs = sendtolist(user, a, sendq, e);
E 30
E 19
			AliasLevel--;
E 56
I 56
			naddrs = sendtolist(user, a, sendq, aliaslevel + 1, e);
E 56
I 29
D 30
			if (!bitset(QSELFREF, a->q_flags))
E 30
I 30
			if (naddrs > 0 && !bitset(QSELFREF, a->q_flags))
E 30
			{
				if (tTd(28, 5))
				{
					printf("udbexpand: QDONTSEND ");
					printaddr(a, FALSE);
				}
				a->q_flags |= QDONTSEND;
			}
E 29
			if (user != buf)
				free(user);
			breakout = TRUE;
E 4
			break;

		  case UDB_EOLIST:
			breakout = TRUE;
			continue;

		  default:
			/* unknown entry type */
			continue;
		}
I 4
	}
I 14
	return EX_OK;
E 14
}
I 15
/*
**  UDBSENDER -- return canonical external name of sender, given local name
**
**	Parameters:
**		sender -- the name of the sender on the local machine.
**
**	Returns:
**		The external name for this sender, if derivable from the
**			database.
**		NULL -- if nothing is changed from the database.
**
**	Side Effects:
**		none.
*/
E 15
E 4

I 15
char *
udbsender(sender)
	char *sender;
{
I 47
	extern char *udbmatch();

	return udbmatch(sender, "mailname");
}


char *
udbmatch(user, field)
	char *user;
	char *field;
{
E 47
	register char *p;
	register struct udbent *up;
	int i;
	int keylen;
	DBT key, info;
D 21
	char keybuf[128];
E 21
I 21
	char keybuf[MAXKEY];
E 21

	if (tTd(28, 1))
D 47
		printf("udbsender(%s)\n", sender);
E 47
I 47
		printf("udbmatch(%s, %s)\n", user, field);
E 47

	if (!UdbInitialized)
	{
		if (_udbx_init() == EX_TEMPFAIL)
			return NULL;
	}

	/* short circuit if no spec */
	if (UdbSpec == NULL || UdbSpec[0] == '\0')
		return NULL;

I 51
	/* short circuit name begins with '\\' since it can't possibly match */
	if (user[0] == '\\')
		return NULL;

E 51
	/* long names can never match and are a pain to deal with */
D 47
	if (strlen(sender) > sizeof keybuf - 12)
E 47
I 47
	if ((strlen(user) + strlen(field)) > sizeof keybuf - 4)
E 47
		return NULL;

	/* names beginning with colons indicate metadata */
D 47
	if (sender[0] == ':')
E 47
I 47
	if (user[0] == ':')
E 47
		return NULL;

	/* build database key */
D 47
	(void) strcpy(keybuf, sender);
	(void) strcat(keybuf, ":mailname");
E 47
I 47
	(void) strcpy(keybuf, user);
	(void) strcat(keybuf, ":");
	(void) strcat(keybuf, field);
E 47
	keylen = strlen(keybuf);

	for (up = UdbEnts; up->udb_type != UDB_EOLIST; up++)
	{
		/*
		**  Select action based on entry type.
		*/

		switch (up->udb_type)
		{
I 62
#ifdef NEWDB
E 62
		  case UDB_DBFETCH:
			key.data = keybuf;
			key.size = keylen;
			i = (*up->udb_dbp->get)(up->udb_dbp, &key, &info, 0);
			if (i != 0 || info.size <= 0)
			{
				if (tTd(28, 2))
D 46
					printf("udbsender: no match on %s\n",
							keybuf);
E 46
I 46
D 47
					printf("udbsender: no match on %s (%d)\n",
E 47
I 47
D 51
					printf("udbmatch: no match on %s (%d)\n",
E 51
I 51
					printf("udbmatch: no match on %s (%d) via db\n",
E 51
E 47
							keybuf, keylen);
E 46
				continue;
			}

			p = xalloc(info.size + 1);
			bcopy(info.data, p, info.size);
			p[info.size] = '\0';
			if (tTd(28, 1))
D 47
				printf("udbsender ==> %s\n", p);
E 47
I 47
				printf("udbmatch ==> %s\n", p);
E 47
			return p;
I 51
			break;
I 62
#endif
E 62

#ifdef HESIOD
		  case UDB_HESIOD:
			key.data = keybuf;
			key.size = keylen;
			i = hes_udb_get(&key, &info); 
			if (i != 0 || info.size <= 0)
			{
				if (tTd(28, 2))
					printf("udbmatch: no match on %s (%d) via hesiod\n",
							keybuf, keylen);
				continue;
			}

			p = xalloc(info.size + 1);
			bcopy(info.data, p, info.size);
			p[info.size] = '\0';
D 65
			free(info.data);
E 65
			if (tTd(28, 1))
				printf("udbmatch ==> %s\n", p);
			return p;
D 65
			break;
E 65
#endif /* HESIOD */
E 51
		}
	}

I 47
	if (strcmp(field, "mailname") != 0)
		return NULL;

E 47
	/*
	**  Nothing yet.  Search again for a default case.  But only
	**  use it if we also have a forward (:maildrop) pointer already
	**  in the database.
	*/

	/* build database key */
D 47
	(void) strcpy(keybuf, sender);
E 47
I 47
	(void) strcpy(keybuf, user);
E 47
	(void) strcat(keybuf, ":maildrop");
	keylen = strlen(keybuf);

	for (up = UdbEnts; up->udb_type != UDB_EOLIST; up++)
	{
		switch (up->udb_type)
		{
I 62
#ifdef NEWDB
E 62
		  case UDB_DBFETCH:
			/* get the default case for this database */
			if (up->udb_default == NULL)
			{
				key.data = ":default:mailname";
				key.size = strlen(key.data);
				i = (*up->udb_dbp->get)(up->udb_dbp, &key, &info, 0);
				if (i != 0 || info.size <= 0)
				{
					/* no default case */
					up->udb_default = "";
					continue;
				}

				/* save the default case */
				up->udb_default = xalloc(info.size + 1);
				bcopy(info.data, up->udb_default, info.size);
				up->udb_default[info.size] = '\0';
			}
			else if (up->udb_default[0] == '\0')
				continue;

			/* we have a default case -- verify user:maildrop */
			key.data = keybuf;
			key.size = keylen;
			i = (*up->udb_dbp->get)(up->udb_dbp, &key, &info, 0);
			if (i != 0 || info.size <= 0)
			{
				/* nope -- no aliasing for this user */
				continue;
			}

			/* they exist -- build the actual address */
D 47
			p = xalloc(strlen(sender) + strlen(up->udb_default) + 2);
			(void) strcpy(p, sender);
E 47
I 47
			p = xalloc(strlen(user) + strlen(up->udb_default) + 2);
			(void) strcpy(p, user);
E 47
			(void) strcat(p, "@");
			(void) strcat(p, up->udb_default);
			if (tTd(28, 1))
D 47
				printf("udbsender ==> %s\n", p);
E 47
I 47
				printf("udbmatch ==> %s\n", p);
E 47
			return p;
I 51
			break;
I 62
#endif
E 62

#ifdef HESIOD
		  case UDB_HESIOD:
			/* get the default case for this database */
			if (up->udb_default == NULL)
			{
				key.data = ":default:mailname";
				key.size = strlen(key.data);
				i = hes_udb_get(&key, &info); 

				if (i != 0 || info.size <= 0)
				{
					/* no default case */
					up->udb_default = "";
					continue;
				}

				/* save the default case */
				up->udb_default = xalloc(info.size + 1);
				bcopy(info.data, up->udb_default, info.size);
				up->udb_default[info.size] = '\0';
D 65
				free(info.data);
E 65
			}
			else if (up->udb_default[0] == '\0')
				continue;

			/* we have a default case -- verify user:maildrop */
			key.data = keybuf;
			key.size = keylen;
			i = hes_udb_get(&key, &info);
			if (i != 0 || info.size <= 0)
			{
				/* nope -- no aliasing for this user */
				continue;
			}

D 65
			free(info.data);
E 65
			/* they exist -- build the actual address */
			p = xalloc(strlen(user) + strlen(up->udb_default) + 2);
			(void) strcpy(p, user);
			(void) strcat(p, "@");
			(void) strcat(p, up->udb_default);
			if (tTd(28, 1))
				printf("udbmatch ==> %s\n", p);
			return p;
			break;
#endif /* HESIOD */
E 51
		}
	}

	/* still nothing....  too bad */
	return NULL;
}
/*
I 57
**  UDB_MAP_LOOKUP -- look up arbitrary entry in user database map
**
**	Parameters:
**		map -- the map being queried.
**		name -- the name to look up.
**		av -- arguments to the map lookup.
**		statp -- to get any error status.
**
**	Returns:
**		NULL if name not found in map.
**		The rewritten name otherwise.
*/

char *
udb_map_lookup(map, name, av, statp)
	MAP *map;
	char *name;
	char **av;
	int *statp;
{
	char *val;

	if (tTd(38, 20))
		printf("udb_map_lookup(%s, %s)\n", map->map_mname, name);
	val = udbmatch(name, map->map_file);
	if (val == NULL)
		return NULL;
	if (bitset(MF_MATCHONLY, map->map_mflags))
		return map_rewrite(map, name, strlen(name), NULL);
	else
		return map_rewrite(map, val, strlen(val), av);
}
/*
E 57
**  _UDBX_INIT -- parse the UDB specification, opening any valid entries.
**
**	Parameters:
**		none.
**
**	Returns:
**		EX_TEMPFAIL -- if it appeared it couldn't get hold of a
**			database due to a host being down or some similar
**			(recoverable) situation.
**		EX_OK -- otherwise.
**
**	Side Effects:
**		Fills in the UdbEnts structure from UdbSpec.
*/

E 15
I 5
#define MAXUDBOPTS	27

E 5
D 4
		if (tTd(28, 1))
			printf("Class %s: %s\n", class, user);
E 4
I 4
D 14
void
E 14
I 14
D 15
int
E 15
I 15
D 16
STATIC int
E 16
I 16
int
E 16
E 15
E 14
_udbx_init()
{
	register char *p;
D 67
	int i;
E 67
	register struct udbent *up;
D 21
	char buf[8192];
E 21
I 21
D 67
	char buf[BUFSIZ];
E 67
E 21
E 4

I 15
	if (UdbInitialized)
		return EX_OK;

E 15
I 12
# ifdef UDB_DEFAULT_SPEC
	if (UdbSpec == NULL)
		UdbSpec = UDB_DEFAULT_SPEC;
# endif

E 12
D 4
		/* do special processing based on class */
		if (strcmp(class, "user") == 0 || strcmp(class, "forward") == 0)
E 4
I 4
	p = UdbSpec;
	up = UdbEnts;
D 9
	for (;;)
E 9
I 9
	while (p != NULL)
E 9
	{
		char *spec;
D 67
		auto int rcode;
E 67
I 5
		int nopts;
I 67
# if 0
		auto int rcode;
E 67
E 5
		int nmx;
I 67
		int i;
E 67
		register struct hostent *h;
		char *mxhosts[MAXMXHOSTS + 1];
I 67
# endif
E 67
I 5
		struct option opts[MAXUDBOPTS + 1];
E 5

		while (*p == ' ' || *p == '\t' || *p == ',')
			p++;
		if (*p == '\0')
			break;
		spec = p;
D 20
		p = index(p, ',');
E 20
I 20
		p = strchr(p, ',');
E 20
D 8
		if (*p != '\0')
E 8
I 8
		if (p != NULL)
E 8
			*p++ = '\0';
I 5

		/* extract options */
		nopts = _udb_parsespec(spec, opts, MAXUDBOPTS);

		/*
		**  Decode database specification.
		**
		**	In the sendmail tradition, the leading character
		**	defines the semantics of the rest of the entry.
		**
		**	+hostname --	send a datagram to the udb server
		**			on host "hostname" asking for the
		**			home mail server for this user.
		**	*hostname --	similar to +hostname, except that the
		**			hostname is searched as an MX record;
		**			resulting hosts are searched as for
		**			+mxhostname.  If no MX host is found,
		**			this is the same as +hostname.
		**	@hostname --	forward email to the indicated host.
		**			This should be the last in the list,
		**			since it always matches the input.
		**	/dbname	 --	search the named database on the local
		**			host using the Berkeley db package.
		*/

E 5
		switch (*spec)
E 4
		{
I 62
#if 0
E 62
D 4
			message(Arpa_Info, "expanded to (%s) %s", class, user);
			AliasLevel++;
			sendtolist(user, a, sendq);
			AliasLevel--;
			breakout = TRUE;
E 4
I 4
		  case '+':	/* search remote database */
D 5
			h = gethostbyname(spec + 1);
			if (h == NULL)
				continue;
			up->udb_type = UDB_REMOTE;
			up->udb_addr.sin_family = h->h_addrtype;
			up->udb_addr.sin_len = h->h_length;
			bcopy(h->h_addr_list[0],
			      (char *) &up->udb_addr.sin_addr,
			      h->h_length);
			up->udb_addr.sin_port = UdbPort;
			up->udb_timeout = UdbTimeout;
			up++;

			/* set up a datagram socket */
			if (UdbSock < 0)
			{
				UdbSock = socket(AF_INET, SOCK_DGRAM, 0);
				(void) fcntl(UdbSock, F_SETFD, 1);
			}
			break;

E 5
		  case '*':	/* search remote database (expand MX) */
D 5
			nmx = getmxrr(spec + 1, mxhosts, "", &rcode);
			if (tTd(28, 16))
E 5
I 5
			if (*spec == '*')
E 5
			{
I 23
D 50
#ifdef NAMED_BIND
E 50
I 50
#if NAMED_BIND
E 50
E 23
D 5
				int i;
E 5
I 5
D 38
				nmx = getmxrr(spec + 1, mxhosts, "", &rcode);
E 38
I 38
				nmx = getmxrr(spec + 1, mxhosts, FALSE, &rcode);
E 38
I 23
#else
				mxhosts[0] = spec + 1;
				nmx = 1;
				rcode = 0;
#endif
E 23
				if (tTd(28, 16))
				{
					int i;
E 5

D 5
				printf("getmxrr(%s): %d", spec + 1, nmx);
				for (i = 0; i <= nmx; i++)
					printf(" %s", mxhosts[i]);
				printf("\n");
E 5
I 5
					printf("getmxrr(%s): %d", spec + 1, nmx);
					for (i = 0; i <= nmx; i++)
						printf(" %s", mxhosts[i]);
					printf("\n");
				}
E 5
			}
I 5
			else
			{
				nmx = 1;
				mxhosts[0] = spec + 1;
			}

E 5
			for (i = 0; i < nmx; i++)
			{
D 61
				h = gethostbyname(mxhosts[i]);
E 61
I 61
				h = sm_gethostbyname(mxhosts[i]);
E 61
				if (h == NULL)
					continue;
				up->udb_type = UDB_REMOTE;
				up->udb_addr.sin_family = h->h_addrtype;
I 35
D 36
				up->udb_addr.sin_len = h->h_length;
E 36
E 35
D 6
				up->udb_addr.sin_len = h->h_length;
E 6
				bcopy(h->h_addr_list[0],
				      (char *) &up->udb_addr.sin_addr,
D 48
				      h->h_length);
E 48
I 48
D 53
				      sizeof up->udb_addr.sin_addr);
E 53
I 53
D 54
				      IPADDRSIZE);
E 54
I 54
				      INADDRSZ);
E 54
E 53
E 48
				up->udb_addr.sin_port = UdbPort;
				up->udb_timeout = UdbTimeout;
				up++;
			}

			/* set up a datagram socket */
			if (UdbSock < 0)
			{
				UdbSock = socket(AF_INET, SOCK_DGRAM, 0);
				(void) fcntl(UdbSock, F_SETFD, 1);
			}
			break;
I 62
#endif
E 62

		  case '@':	/* forward to remote host */
			up->udb_type = UDB_FORWARD;
			up->udb_fwdhost = spec + 1;
			up++;
			break;

I 62
#ifdef HESIOD
E 62
I 51
		  case 'h':	/* use hesiod */
		  case 'H':
D 62
#ifdef HESIOD
E 62
			if (strcasecmp(spec, "hesiod") != 0)
D 62
				break;
E 62
I 62
				goto badspec;
E 62
			up->udb_type = UDB_HESIOD;
			up++;
D 62
#endif /* HESIOD */
E 62
			break;
I 62
#endif /* HESIOD */
E 62

I 62
#ifdef NEWDB
E 62
E 51
		  case '/':	/* look up remote name */
I 11
			up->udb_dbname = spec;
I 14
			errno = 0;
E 14
E 11
			up->udb_dbp = dbopen(spec, O_RDONLY, 0644, DB_BTREE, NULL);
			if (up->udb_dbp == NULL)
I 14
			{
I 55
				if (tTd(28, 1))
				{
					int saveerrno = errno;

					printf("dbopen(%s): %s",
						spec, errstring(errno));
					errno = saveerrno;
				}
E 55
				if (errno != ENOENT && errno != EACCES)
D 15
					return EX_TEMPFAIL;
E 15
I 15
				{
I 39
#ifdef LOG
					if (LogLevel > 2)
D 40
						syslog(LOG_ERR, "dbopen(%s): %e",
							spec);
E 40
I 40
						syslog(LOG_ERR, "dbopen(%s): %s",
							spec, errstring(errno));
E 40
#endif
E 39
					up->udb_type = UDB_EOLIST;
					goto tempfail;
				}
E 15
E 14
				break;
I 14
			}
E 14
D 15
			up->udb_type = UDB_LOOKUP;
E 15
I 15
			up->udb_type = UDB_DBFETCH;
E 15
			up++;
			break;
I 62
#endif

		  default:
badspec:
			syserr("Unknown UDB spec %s", spec);
			break;
E 62
E 4
		}
I 4
	}
	up->udb_type = UDB_EOLIST;
E 4

D 4
		/* free memory if we allocated it */
		if (up->udb_type == UDB_FORWARD || up->udb_type == UDB_LOOKUP)
E 4
I 4
	if (tTd(28, 4))
	{
D 15
		for (up = UdbEnts; ; up++)
E 15
I 15
		for (up = UdbEnts; up->udb_type != UDB_EOLIST; up++)
E 15
E 4
		{
D 4
			if (user != buf)
				free(user);
E 4
I 4
			switch (up->udb_type)
			{
D 15
			  case UDB_EOLIST:
D 14
				return;
E 14
I 14
				return EX_OK;
E 14

E 15
			  case UDB_REMOTE:
				printf("REMOTE: addr %s, timeo %d\n",
D 35
					inet_ntoa(up->udb_addr.sin_addr),
E 35
I 35
D 42
					anynet_ntoa(&up->udb_addr),
E 42
I 42
					anynet_ntoa((SOCKADDR *) &up->udb_addr),
E 42
E 35
					up->udb_timeout);
				break;

D 15
			  case UDB_LOOKUP:
D 10
				printf("LOOKUP\n");
E 10
I 10
				printf("LOOKUP: file %s\n",
E 15
I 15
			  case UDB_DBFETCH:
I 66
#ifdef NEWDB
E 66
				printf("FETCH: file %s\n",
E 15
					up->udb_dbname);
I 66
#else
				printf("FETCH\n");
#endif
E 66
E 10
				break;

			  case UDB_FORWARD:
				printf("FORWARD: host %s\n",
					up->udb_fwdhost);
				break;

I 51
			  case UDB_HESIOD:
				printf("HESIOD\n");
				break;

E 51
			  default:
				printf("UNKNOWN\n");
				break;
			}
E 4
		}
E 3
	}
I 15

	UdbInitialized = TRUE;
I 17
	errno = 0;
E 17
	return EX_OK;

	/*
	**  On temporary failure, back out anything we've already done
	*/

  tempfail:
I 62
#ifdef NEWDB
E 62
	for (up = UdbEnts; up->udb_type != UDB_EOLIST; up++)
	{
		if (up->udb_type == UDB_DBFETCH)
		{
			(*up->udb_dbp->close)(up->udb_dbp);
		}
	}
I 62
#endif
E 62
	return EX_TEMPFAIL;
E 15
I 5
}

int
_udb_parsespec(udbspec, opt, maxopts)
	char *udbspec;
	struct option opt[];
	int maxopts;
{
	register char *spec;
	register char *spec_end;
	register int optnum;

D 20
	spec_end = index(udbspec, ':');
E 20
I 20
	spec_end = strchr(udbspec, ':');
E 20
	for (optnum = 0; optnum < maxopts && (spec = spec_end) != NULL; optnum++)
	{
		register char *p;

D 28
		while (isspace(*spec))
E 28
I 28
		while (isascii(*spec) && isspace(*spec))
E 28
			spec++;
D 20
		spec_end = index(spec, ':');
E 20
I 20
		spec_end = strchr(spec, ':');
E 20
		if (spec_end != NULL)
			*spec_end++ = '\0';

		opt[optnum].name = spec;
		opt[optnum].val = NULL;
D 20
		p = index(spec, '=');
E 20
I 20
		p = strchr(spec, '=');
E 20
		if (p != NULL)
			opt[optnum].val = ++p;
	}
	return optnum;
E 5
I 3
}
I 51

#ifdef HESIOD

int
hes_udb_get(key, info)
	DBT *key;
	DBT *info;
{
	char *name, *type;
	char *p, **hp;
I 58
	char kbuf[MAXKEY + 1];
E 58

D 58
	name = key->data;
E 58
I 58
	strcpy(kbuf, key->data);
	name = kbuf;
E 58
	type = strchr(name, ':');
D 58
	if (type == NULL)
E 58
I 58
D 59
	if (type == NULL || type == name)
E 59
I 59
	if (type == NULL)
E 59
E 58
		return 1;
D 58

E 58
	*type++ = '\0';

	if (tTd(28, 1))
		printf("hes_udb_get(%s, %s)\n", name, type);

	/* make the hesiod query */
	hp = hes_resolve(name, type);
I 66
	*--type = ':';
E 66
	if (hp == NULL)
	{
		/* network problem or timeout */
		if (hes_error() == HES_ER_NET)
			return -1;

		return 1;
	}
	else
	{
		/*
		**  If there are multiple matches, just return the
D 65
		**  first one and free the others.
E 65
I 65
		**  first one.
E 65
		**
		**  XXX These should really be returned; for example,
		**  XXX it is legal for :maildrop to be multi-valued.
		*/
D 65

		for (p = hp[1]; p; p++)
			free(p);
E 65

		info->data = hp[0];
		info->size = (size_t) strlen(info->data);
	}

	return 0;
}
#endif /* HESIOD */
E 51
E 3

D 3
	/* free memory if we allocated it */
	if (bp != buf)
		free(bp);
E 3
I 3
#else /* not USERDB */

D 14
void
E 14
I 14
int
E 14
D 19
udbexpand(a, sendq)
E 19
I 19
D 56
udbexpand(a, sendq, e)
E 56
I 56
udbexpand(a, sendq, aliaslevel, e)
E 56
E 19
	ADDRESS *a;
	ADDRESS **sendq;
I 56
	int aliaslevel;
E 56
I 19
	ENVELOPE *e;
E 19
{
D 14
	return;
E 14
I 14
	return EX_OK;
E 14
E 3
}

#endif /* USERDB */
E 1
