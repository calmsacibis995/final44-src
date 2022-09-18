h29731
s 00007/00000/00378
d D 8.17 95/05/28 11:50:24 eric 32 31
c lint
e
s 00001/00001/00377
d D 8.16 95/04/21 09:57:54 eric 31 30
c update copyright notice
e
s 00001/00001/00377
d D 8.15 94/08/17 08:08:58 eric 30 29
c make all flags be printed in hex rather than octal (except file modes)
e
s 00013/00007/00365
d D 8.14 94/05/15 07:23:40 eric 29 28
c fix malloc(0) problem if MaxMciCache <= 0
e
s 00002/00000/00370
d D 8.13 94/04/12 08:38:38 eric 28 27
c updates for Intergraph CLIX
e
s 00003/00000/00367
d D 8.12 94/02/09 07:40:14 eric 27 26
c time out cache far more frequently
e
s 00009/00000/00358
d D 8.11 94/02/06 09:35:39 eric 26 25
c fix logging of relay address on cached connections
e
s 00006/00000/00352
d D 8.10 94/01/24 08:01:51 eric 25 24
c move 7BIT information from per-mailer to per-connection so it can
c be tweaked based on the other end
e
s 00001/00001/00351
d D 8.9 93/12/01 14:01:43 eric 24 23
c syslog debug info as LOG_DEBUG instead of LOG_INFO
e
s 00003/00000/00349
d D 8.8 93/12/01 14:00:02 eric 23 22
c have mci_dump_all verify that the cache has been allocated
e
s 00002/00000/00347
d D 8.7 93/11/08 09:45:04 eric 22 21
c better checking of m->m_mno (for debugging)
e
s 00004/00002/00343
d D 8.6 93/10/23 11:56:30 eric 21 20
c avoid possible null pointer references
e
s 00018/00000/00327
d D 8.5 93/10/21 12:28:36 eric 20 19
c improved debugging/logging of mci caching
e
s 00043/00009/00284
d D 8.4 93/10/21 07:18:46 eric 19 18
c allow dumping of MCI cache to syslog for debugging
e
s 00001/00001/00292
d D 8.3 93/07/19 20:50:24 eric 18 17
c SGI IRIX & ANSI C portability
e
s 00005/00004/00288
d D 8.2 93/07/11 06:52:59 eric 17 16
c huge number of changes for 8.2, including IRIX & Solaris portability;
c improved error checking; fix -m flag and add -O flag in maps; fix long
c DNS timeouts; relax safefile restrictions; add -X command line flag; etc.
e
s 00002/00002/00290
d D 8.1 93/06/07 10:31:04 bostic 16 15
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00290
d D 6.10 93/04/26 14:42:16 eric 15 14
c print out other fields
e
s 00003/00000/00289
d D 6.9 93/04/18 10:07:27 eric 14 13
c Extended Load Average (XLA) hooks
e
s 00007/00000/00282
d D 6.8 93/04/01 08:09:35 eric 13 12
c zero CurHostAddr more vigorously to avoid bogus log entries
e
s 00001/00001/00281
d D 6.7 93/03/30 10:23:33 eric 12 11
c change connection probing to use RSET instead of NOOP
e
s 00002/00002/00280
d D 6.6 93/03/16 09:16:29 eric 11 10
c delete e_sender and e_returnpath; fix some bugs in envelope splitting
e
s 00001/00001/00281
d D 6.5 93/02/23 06:32:04 eric 10 9
c overhaul status of SMTP reply codes
e
s 00041/00010/00241
d D 6.4 93/02/20 13:46:57 eric 9 8
c close cached MCI connections after a fork; add p (privacy) and b
c (min blocks free) options; fix selfref code; clean up $#error format
e
s 00010/00004/00241
d D 6.3 93/02/14 14:41:53 eric 8 7
c HPUX and OSF/1 support; fix SMTP reply codes & multiple SMTP error
c problem; consider cache timeout non-permanent; be more graceful on OS
c failures; log forward, alias, and userdb expansions on log level 10
e
s 00034/00000/00211
d D 6.2 93/01/01 13:06:53 eric 7 6
c add debug routine to dump MCI structure
e
s 00000/00000/00211
d D 6.1 92/12/21 16:08:57 eric 6 5
c Release 6
e
s 00001/00000/00210
d D 5.5 92/09/09 06:56:48 eric 5 4
c miscellaneous bug fixes from Bryan Costales and Craig Lant
e
s 00006/00001/00204
d D 5.4 92/07/20 22:20:20 eric 4 3
c do clean connection closing on queue runs
e
s 00001/00001/00204
d D 5.3 92/07/12 14:44:09 eric 3 2
c lint
e
s 00058/00014/00147
d D 5.2 92/07/11 18:51:58 eric 2 1
c open connection caching
e
s 00161/00000/00000
d D 5.1 92/07/11 17:47:25 eric 1 0
c date and time created 92/07/11 17:47:25 by eric
e
u
U
t
T
I 1
/*
D 31
 * Copyright (c) 1983 Eric P. Allman
E 31
I 31
 * Copyright (c) 1983, 1995 Eric P. Allman
E 31
D 16
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.
E 16
I 16
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 16
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include "sendmail.h"

/*
I 2
**  Mail Connection Information (MCI) Caching Module.
**
**	There are actually two separate things cached.  The first is
**	the set of all open connections -- these are stored in a
**	(small) list.  The second is stored in the symbol table; it
**	has the overall status for all hosts, whether or not there
**	is a connection open currently.
**
**	There should never be too many connections open (since this
**	could flood the socket table), nor should a connection be
**	allowed to sit idly for too long.
**
**	MaxMciCache is the maximum number of open connections that
**	will be supported.
**
**	MciCacheTimeout is the time (in seconds) that a connection
**	is permitted to survive without activity.
**
**	We actually try any cached connections by sending a NOOP
**	before we use them; if the NOOP fails we close down the
**	connection and reopen it.  Note that this means that a
**	server SMTP that doesn't support NOOP will hose the
**	algorithm -- but that doesn't seem too likely.
*/

MCI	**MciCache;		/* the open connection cache */
I 32

extern void	mci_uncache __P((MCI **, bool));
E 32
/*
E 2
**  MCI_CACHE -- enter a connection structure into the open connection cache
**
**	This may cause something else to be flushed.
**
**	Parameters:
**		mci -- the connection to cache.
**
**	Returns:
**		none.
*/

I 32
void
E 32
mci_cache(mci)
D 2
	register MCONINFO *mci;
E 2
I 2
	register MCI *mci;
E 2
{
D 2
	register MCONINFO **mcislot;
	extern MCONINFO **mci_scan();
E 2
I 2
	register MCI **mcislot;
	extern MCI **mci_scan();
E 2

D 29
	if (MaxMciCache <= 0)
	{
		/* we don't support caching */
		return;
	}

E 29
	/*
	**  Find the best slot.  This may cause expired connections
	**  to be closed.
	*/

	mcislot = mci_scan(mci);
I 29
	if (mcislot == NULL)
	{
		/* we don't support caching */
		return;
	}
E 29

	/* if this is already cached, we are done */
	if (bitset(MCIF_CACHED, mci->mci_flags))
		return;

	/* otherwise we may have to clear the slot */
	if (*mcislot != NULL)
D 9
		mci_uncache(mcislot);
E 9
I 9
		mci_uncache(mcislot, TRUE);
E 9

I 20
	if (tTd(42, 5))
		printf("mci_cache: caching %x (%s) in slot %d\n",
			mci, mci->mci_host, mcislot - MciCache);
#ifdef LOG
	if (tTd(91, 100))
		syslog(LOG_DEBUG, "%s: mci_cache: caching %x (%s) in slot %d",
D 21
			CurEnv->e_id, mci, mci->mci_host, mcislot - MciCache);
E 21
I 21
			CurEnv->e_id ? CurEnv->e_id : "NOQUEUE",
			mci, mci->mci_host, mcislot - MciCache);
E 21
#endif

E 20
	*mcislot = mci;
	mci->mci_flags |= MCIF_CACHED;
}
/*
**  MCI_SCAN -- scan the cache, flush junk, and return best slot
**
**	Parameters:
**		savemci -- never flush this one.  Can be null.
**
**	Returns:
**		The LRU (or empty) slot.
*/

D 2
MCONINFO	**MciCache;

MCONINFO **
E 2
I 2
MCI **
E 2
mci_scan(savemci)
D 2
	MCONINFO *savemci;
E 2
I 2
	MCI *savemci;
E 2
{
	time_t now;
D 2
	register MCONINFO **bestmci;
	register MCONINFO *mci;
E 2
I 2
	register MCI **bestmci;
	register MCI *mci;
E 2
	register int i;

I 29
	if (MaxMciCache <= 0)
	{
		/* we don't support caching */
		return NULL;
	}

E 29
	if (MciCache == NULL)
	{
		/* first call */
D 2
		MciCache = (MCONINFO **) xalloc(MaxMciCache * sizeof *MciCache);
E 2
I 2
		MciCache = (MCI **) xalloc(MaxMciCache * sizeof *MciCache);
I 5
		bzero((char *) MciCache, MaxMciCache * sizeof *MciCache);
E 5
E 2
		return (&MciCache[0]);
	}

	now = curtime();
	bestmci = &MciCache[0];
	for (i = 0; i < MaxMciCache; i++)
	{
		mci = MciCache[i];
		if (mci == NULL || mci->mci_state == MCIS_CLOSED)
		{
			bestmci = &MciCache[i];
			continue;
		}
		if (mci->mci_lastuse + MciCacheTimeout < now && mci != savemci)
		{
			/* connection idle too long -- close it */
			bestmci = &MciCache[i];
D 9
			mci_uncache(bestmci);
E 9
I 9
			mci_uncache(bestmci, TRUE);
E 9
			continue;
		}
		if (*bestmci == NULL)
			continue;
		if (mci->mci_lastuse < (*bestmci)->mci_lastuse)
			bestmci = &MciCache[i];
	}
	return bestmci;
}
/*
**  MCI_UNCACHE -- remove a connection from a slot.
**
**	May close a connection.
**
**	Parameters:
**		mcislot -- the slot to empty.
I 9
**		doquit -- if TRUE, send QUIT protocol on this connection.
**			  if FALSE, we are assumed to be in a forked child;
**				all we want to do is close the file(s).
E 9
**
**	Returns:
**		none.
*/

I 32
void
E 32
D 9
mci_uncache(mcislot)
E 9
I 9
mci_uncache(mcislot, doquit)
E 9
D 2
	register MCONINFO **mcislot;
E 2
I 2
	register MCI **mcislot;
I 9
	bool doquit;
E 9
E 2
{
D 2
	register MCONINFO *mci;
E 2
I 2
	register MCI *mci;
E 2
D 3
	extern ENVELOPE *BlankEnvelope;
E 3
I 3
	extern ENVELOPE BlankEnvelope;
E 3

	mci = *mcislot;
	if (mci == NULL)
		return;
	*mcislot = NULL;
I 20

	if (tTd(42, 5))
		printf("mci_uncache: uncaching %x (%s) from slot %d (%d)\n",
			mci, mci->mci_host, mcislot - MciCache, doquit);
#ifdef LOG
	if (tTd(91, 100))
		syslog(LOG_DEBUG, "%s: mci_uncache: uncaching %x (%s) from slot %d (%d)",
D 21
			CurEnv->e_id, mci, mci->mci_host, mcislot - MciCache, doquit);
E 21
I 21
			CurEnv->e_id ? CurEnv->e_id : "NOQUEUE",
			mci, mci->mci_host, mcislot - MciCache, doquit);
E 21
#endif
E 20
D 9
	mci->mci_flags &= ~MCIF_CACHED;
E 9

I 4
D 9
	message(Arpa_Info, "Closing connection to %s", mci->mci_host);
E 9
I 9
	if (doquit)
	{
D 10
		message(Arpa_Info, "Closing connection to %s", mci->mci_host);
E 10
I 10
		message("Closing connection to %s", mci->mci_host);
E 10
E 9

E 4
D 9
	/* only uses the envelope to flush the transcript file */
	if (mci->mci_state != MCIS_CLOSED)
		smtpquit(mci->mci_mailer, mci, &BlankEnvelope);
E 9
I 9
		mci->mci_flags &= ~MCIF_CACHED;

		/* only uses the envelope to flush the transcript file */
		if (mci->mci_state != MCIS_CLOSED)
			smtpquit(mci->mci_mailer, mci, &BlankEnvelope);
I 14
#ifdef XLA
		xla_host_end(mci->mci_host);
#endif
E 14
	}
	else
	{
		if (mci->mci_in != NULL)
D 11
			fclose(mci->mci_in);
E 11
I 11
			xfclose(mci->mci_in, "mci_uncache", "mci_in");
E 11
		if (mci->mci_out != NULL)
D 11
			fclose(mci->mci_out);
E 11
I 11
			xfclose(mci->mci_out, "mci_uncache", "mci_out");
E 11
		mci->mci_in = mci->mci_out = NULL;
		mci->mci_state = MCIS_CLOSED;
		mci->mci_exitstat = EX_OK;
		mci->mci_errno = 0;
		mci->mci_flags = 0;
	}
E 9
}
/*
**  MCI_FLUSH -- flush the entire cache
I 9
**
**	Parameters:
**		doquit -- if TRUE, send QUIT protocol.
**			  if FALSE, just close the connection.
**		allbut -- but leave this one open.
**
**	Returns:
**		none.
E 9
*/

I 32
void
E 32
D 9
mci_flush()
E 9
I 9
mci_flush(doquit, allbut)
	bool doquit;
	MCI *allbut;
E 9
{
	register int i;

	if (MciCache == NULL)
		return;

	for (i = 0; i < MaxMciCache; i++)
D 9
		mci_uncache(&MciCache[i]);
E 9
I 9
		if (allbut != MciCache[i])
			mci_uncache(&MciCache[i], doquit);
E 9
}
/*
**  MCI_GET -- get information about a particular host
*/

D 2
MCONINFO *
E 2
I 2
MCI *
E 2
mci_get(host, m)
	char *host;
	MAILER *m;
{
D 2
	return &(stab(host, ST_MCONINFO + m->m_mno, ST_ENTER))->s_mci;
E 2
I 2
	register MCI *mci;
I 4
	register STAB *s;
I 29
	extern MCI **mci_scan();
E 29
E 4

I 13
#ifdef DAEMON
	extern SOCKADDR CurHostAddr;

	/* clear CurHostAddr so we don't get a bogus address with this name */
	bzero(&CurHostAddr, sizeof CurHostAddr);
D 18
#endif DAEMON
E 18
I 18
#endif
E 18

I 27
	/* clear out any expired connections */
D 29
	mci_scan(NULL);
E 29
I 29
	(void) mci_scan(NULL);
E 29

E 27
I 22
	if (m->m_mno < 0)
		syserr("negative mno %d (%s)", m->m_mno, m->m_name);
E 22
E 13
D 4
	mci = &(stab(host, ST_MCI + m->m_mno, ST_ENTER))->s_mci;
E 4
I 4
	s = stab(host, ST_MCI + m->m_mno, ST_ENTER);
	mci = &s->s_mci;
	mci->mci_host = s->s_name;
E 4

	if (tTd(42, 2))
	{
		printf("mci_get(%s %s): mci_state=%d, _flags=%x, _exitstat=%d, _errno=%d\n",
			host, m->m_name, mci->mci_state, mci->mci_flags,
			mci->mci_exitstat, mci->mci_errno);
	}

D 8
	/* try poking this to see if it is still usable */
	switch (mci->mci_state)
E 8
I 8
	if (mci->mci_state == MCIS_OPEN)
E 8
	{
D 8
	  case MCIS_OPEN:
E 8
I 8
		/* poke the connection to see if it's still alive */
E 8
D 12
		smtpnoop(mci);
E 12
I 12
		smtpprobe(mci);
E 12
D 8
		break;
E 8
I 8

		/* reset the stored state in the event of a timeout */
		if (mci->mci_state != MCIS_OPEN)
		{
			mci->mci_errno = 0;
			mci->mci_exitstat = EX_OK;
			mci->mci_state = MCIS_CLOSED;
		}
I 26
		else
		{
			/* get peer host address for logging reasons only */
			/* (this should really be in the mci struct) */
			int socksize = sizeof CurHostAddr;

			(void) getpeername(fileno(mci->mci_in),
				(struct sockaddr *) &CurHostAddr, &socksize);
		}
E 26
E 8
	}
I 25
	if (mci->mci_state == MCIS_CLOSED)
	{
		/* copy out any mailer flags needed in connection state */
		if (bitnset(M_7BITS, m->m_flags))
			mci->mci_flags |= MCIF_7BIT;
	}
E 25

	return mci;
E 2
}
I 7
/*
**  MCI_DUMP -- dump the contents of an MCI structure.
**
**	Parameters:
**		mci -- the MCI structure to dump.
**
**	Returns:
**		none.
**
**	Side Effects:
**		none.
*/

I 32
void
E 32
D 19
mci_dump(mci)
E 19
I 19
mci_dump(mci, logit)
E 19
	register MCI *mci;
I 19
	bool logit;
E 19
{
I 19
	register char *p;
	char *sep;
	char buf[1000];
E 19
	extern char *ctime();

D 19
	printf("MCI@%x: ", mci);
E 19
I 19
	sep = logit ? " " : "\n\t";
	p = buf;
	sprintf(p, "MCI@%x: ", mci);
	p += strlen(p);
E 19
	if (mci == NULL)
	{
D 19
		printf("NULL\n");
		return;
E 19
I 19
		sprintf(p, "NULL");
		goto printit;
E 19
	}
D 15
	printf("flags=%o, errno=%d, exitstat=%d, state=%d, pid=%d,\n",
E 15
I 15
D 17
	printf("flags=%o, errno=%d, exitstat=%d, state=%d, pid=%d, maxsize=%ld\n",
E 15
		mci->mci_flags, mci->mci_errno, mci->mci_exitstat,
D 15
		mci->mci_state, mci->mci_pid);
E 15
I 15
		mci->mci_state, mci->mci_pid, mci->mci_maxsize);
E 15
	printf("\tphase=%s, mailer=%s,\n",
E 17
I 17
D 19
	printf("flags=%o, errno=%d, herrno=%d, exitstat=%d, state=%d, pid=%d,\n",
E 19
I 19
D 30
	sprintf(p, "flags=%o, errno=%d, herrno=%d, exitstat=%d, state=%d, pid=%d,%s",
E 30
I 30
	sprintf(p, "flags=%x, errno=%d, herrno=%d, exitstat=%d, state=%d, pid=%d,%s",
E 30
E 19
		mci->mci_flags, mci->mci_errno, mci->mci_herrno,
D 19
		mci->mci_exitstat, mci->mci_state, mci->mci_pid);
	printf("\tmaxsize=%ld, phase=%s, mailer=%s,\n",
E 19
I 19
		mci->mci_exitstat, mci->mci_state, mci->mci_pid, sep);
	p += strlen(p);
	sprintf(p, "maxsize=%ld, phase=%s, mailer=%s,%s",
E 19
		mci->mci_maxsize,
E 17
		mci->mci_phase == NULL ? "NULL" : mci->mci_phase,
D 19
		mci->mci_mailer == NULL ? "NULL" : mci->mci_mailer->m_name);
	printf("\thost=%s, lastuse=%s\n",
E 19
I 19
		mci->mci_mailer == NULL ? "NULL" : mci->mci_mailer->m_name,
		sep);
	p += strlen(p);
	sprintf(p, "host=%s, lastuse=%s",
E 19
		mci->mci_host == NULL ? "NULL" : mci->mci_host,
		ctime(&mci->mci_lastuse));
I 19
printit:
I 28
#ifdef LOG
E 28
	if (logit)
D 24
		syslog(LOG_INFO, "%s", buf);
E 24
I 24
		syslog(LOG_DEBUG, "%s", buf);
E 24
	else
I 28
#endif
E 28
		printf("%s\n", buf);
}
/*
**  MCI_DUMP_ALL -- print the entire MCI cache
**
**	Parameters:
**		logit -- if set, log the result instead of printing
**			to stdout.
**
**	Returns:
**		none.
*/

I 32
void
E 32
mci_dump_all(logit)
	bool logit;
{
	register int i;

I 23
	if (MciCache == NULL)
		return;

E 23
	for (i = 0; i < MaxMciCache; i++)
		mci_dump(MciCache[i], logit);
E 19
}
E 7
E 1
