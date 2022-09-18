h26616
s 00001/00001/00464
d D 8.2 95/04/28 12:47:14 bostic 35 34
c flush before trunc when opened for append
c From: Chris Torek <torek@BSDI.COM>
e
s 00002/00002/00463
d D 8.1 93/06/06 15:08:32 bostic 34 33
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00005/00457
d D 5.18 92/06/26 12:03:23 bostic 33 32
c quad's broke it -- prototyped it rather than figure out the problem
e
s 00002/00001/00460
d D 5.17 92/03/11 16:46:37 bostic 32 31
c make mail understand TMPDIR
e
s 00007/00007/00454
d D 5.16 91/02/09 23:01:53 edward 31 30
c for bostic: ANSI C change: remove -> rm
e
s 00054/00054/00407
d D 5.15 90/06/25 00:01:28 edward 30 29
c remove call of _fwalk
e
s 00001/00011/00460
d D 5.14 90/06/01 17:00:02 bostic 29 28
c new copyright notice
e
s 00001/00001/00470
d D 5.13 89/08/21 17:34:27 bostic 28 27
c don't have double slashes, for emacs
e
s 00002/00001/00469
d D 5.12 89/05/11 09:44:20 bostic 27 26
c file reorg, pathnames.h, paths.h
e
s 00140/00008/00330
d D 5.11 89/01/16 01:34:20 edward 26 25
c don't catch SIGCONT, catch the stop signals instead,
c cleaned up quitting of mail and signal catch in general,
c could use more work
e
s 00002/00002/00336
d D 5.10 88/07/07 09:34:41 edward 25 24
c merged even more functionality into send()
e
s 00012/00007/00326
d D 5.9 88/06/29 21:02:02 bostic 24 23
c install approved copyright notice
e
s 00005/00007/00328
d D 5.8 88/06/17 15:38:51 edward 23 22
c some general cleanup
e
s 00002/00000/00333
d D 5.7 88/06/17 15:05:05 edward 22 21
c cleaned up file handling code, now allows "mbox" variable
e
s 00000/00010/00333
d D 5.6 88/06/16 17:40:57 edward 21 20
c prehistoric (e.g., pre-sendmail) code removed
e
s 00001/00001/00342
d D 5.5 88/06/09 22:24:26 edward 20 19
c new commands saveignore, saveretain, and savediscard
e
s 00011/00005/00332
d D 5.4 88/02/18 17:04:17 bostic 19 18
c written by Kurt Shoens; added Berkeley specific header
e
s 00003/00001/00334
d D 5.3 86/03/06 13:07:48 mckusick 18 16
c fix security/privacy problem (from ks@ef.purdue.edu (Kirk Smith))
e
s 00001/00000/00335
d R 5.3 86/03/03 14:48:32 mckusick 17 16
c fix security/privacy problem (from ks@ef.purdue.edu (Kirk Smith))
e
s 00001/00001/00334
d D 5.2 85/06/21 17:13:45 mckusick 16 15
c botched copyright
e
s 00008/00002/00327
d D 5.1 85/06/06 10:41:47 dist 15 14
c Add copyright
e
s 00003/00002/00326
d D 2.9 85/05/27 15:04:01 serge 14 13
c Fixed indirect through NULL bug
e
s 00029/00027/00299
d D 2.8 84/07/19 15:43:05 ralph 13 12
c use flock for mailbox locking
e
s 00003/00003/00323
d D 2.7 83/08/11 22:19:13 sam 12 11
c standardize sccs keyword lines
e
s 00003/00000/00323
d D 2.6 83/05/28 22:35:48 leres 11 10
c Modified to truncate read/write files before closing.
e
s 00003/00003/00320
d D 2.5 83/05/24 16:30:16 leres 10 9
c Changed various fopens to open read/write to avoid trashing files
c when the file system gets full, etc.
e
s 00002/00003/00321
d D 2.4 82/07/28 23:18:13 kurt 9 8
c added extra doignore argument to send() calls 
c 
e
s 00005/00002/00319
d D 2.3 81/09/09 10:00:57 kurt 8 7
c changed quit processing to NOT delete MSAVED messages if you
c have set "keepsave"
e
s 00013/00001/00308
d D 2.2 81/07/20 17:07:51 kurt 7 6
c added code to handle accounting for the -T flag:
c writes into the chosen file name the article id's of messages read or
c deleted
e
s 00000/00000/00309
d D 2.1 81/07/01 11:10:16 kurt 6 5
c Release to Heidi Stettner
e
s 00009/00010/00300
d D 1.5 81/03/20 15:28:50 kas 5 4
c simplified interpretation of where to send each message with added mbox bit
e
s 00014/00002/00296
d D 1.4 80/10/17 00:34:18 kas 4 3
c now quit clears the MNEW bit on all messages and writes back
c all the messages into the mail file if any of the message status fields
c have changed
e
s 00004/00001/00294
d D 1.3 80/10/10 13:47:03 kas 3 2
c Implemented transparent version of autoholding messages
c which doesn't set MPRESERVE until we are just about to quit.
e
s 00007/00000/00288
d D 1.2 80/10/09 13:41:18 kas 2 1
c quit() does nothing if in read only mode
e
s 00288/00000/00000
d D 1.1 80/10/08 09:51:11 kas 1 0
c date and time created 80/10/08 09:51:11 by kas
e
u
U
f b 
t
T
I 15
/*
D 34
 * Copyright (c) 1980 Regents of the University of California.
D 19
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 19
I 19
 * All rights reserved.
E 34
I 34
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 34
 *
D 29
 * Redistribution and use in source and binary forms are permitted
D 24
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 24
I 24
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 29
I 29
 * %sccs.include.redist.c%
E 29
E 24
E 19
 */

E 15
I 1
D 12
#
E 12
I 12
D 19
#ifndef lint
D 14
static char sccsid[] = "%W% (Berkeley) %G%";
E 14
I 14
D 15
static char *sccsid = "%W% (Berkeley) %G%";
E 14
#endif
E 15
I 15
D 16
static char sccsid[] = "%W% (Berkeley) %G%";
E 16
I 16
static char *sccsid = "%W% (Berkeley) %G%";
E 16
#endif not lint
E 19
I 19
D 24
#ifdef notdef
E 24
I 24
#ifndef lint
E 24
static char sccsid[] = "%W% (Berkeley) %G%";
D 24
#endif /* notdef */
E 24
I 24
#endif /* not lint */
E 24
E 19
E 15
E 12

#include "rcv.h"
D 33
#include <sys/stat.h>
I 13
#include <sys/file.h>
E 33
I 33
#include <fcntl.h>
#include "extern.h"
E 33
E 13

/*
 * Rcv -- receive mail rationally.
 *
 * Termination processing.
 */
D 12

static char *SccsId = "%W% %G%";
E 12

/*
I 26
 * The "quit" command.
 */
I 33
int
E 33
quitcmd()
{
	/*
	 * If we are sourcing, then return 1 so execute() can handle it.
	 * Otherwise, return -1 to abort command loop.
	 */
	if (sourcing)
		return 1;
	return -1;
}

/*
E 26
 * Save all of the undetermined messages at the top of "mbox"
 * Save all untouched messages back in the system mailbox.
 * Remove the system mailbox, if none saved there.
 */
D 33

E 33
I 33
void
E 33
quit()
{
D 3
	int mcount, p, modify;
E 3
I 3
D 4
	int mcount, p, modify, autohold;
E 4
I 4
D 5
	int mcount, p, modify, autohold, anystat;
E 5
I 5
D 8
	int mcount, p, modify, autohold, anystat, holdbit;
E 8
I 8
	int mcount, p, modify, autohold, anystat, holdbit, nohold;
E 8
E 5
E 4
E 3
D 7
	FILE *ibuf, *obuf, *fbuf, *rbuf;
E 7
I 7
D 13
	FILE *ibuf, *obuf, *fbuf, *rbuf, *readstat;
E 13
I 13
	FILE *ibuf, *obuf, *fbuf, *rbuf, *readstat, *abuf;
E 13
E 7
	register struct message *mp;
	register int c;
	extern char tempQuit[], tempResid[];
	struct stat minfo;
I 7
D 23
	char *id;
E 23
I 22
	char *mbox;
E 22
E 7

	/*
I 2
	 * If we are read only, we can't do anything,
	 * so just return quickly.
	 */
D 26

E 26
	if (readonly)
		return;
	/*
I 26
	 * If editing (not reading system mail box), then do the work
	 * in edstop()
	 */
	if (edit) {
		edstop();
		return;
	}

	/*
E 26
E 2
	 * See if there any messages to save in mbox.  If no, we
	 * can save copying mbox to /tmp and back.
	 *
	 * Check also to see if any files need to be preserved.
	 * Delete all untouched messages to keep them out of mbox.
	 * If all the messages are to be preserved, just exit with
	 * a message.
D 21
	 *
	 * If the luser has sent mail to himself, refuse to do
	 * anything with the mailbox, unless mail locking works.
E 21
	 */

D 13
	lock(mailname);
E 13
I 13
D 30
	fbuf = fopen(mailname, "r");
E 30
I 30
	fbuf = Fopen(mailname, "r");
E 30
	if (fbuf == NULL)
		goto newmail;
	flock(fileno(fbuf), LOCK_EX);
E 13
D 21
#ifndef CANLOCK
	if (selfsent) {
		printf("You have new mail.\n");
D 13
		unlock();
E 13
I 13
		fclose(fbuf);
E 13
		return;
	}
#endif
E 21
	rbuf = NULL;
D 13
	if (stat(mailname, &minfo) >= 0 && minfo.st_size > mailsize) {
E 13
I 13
	if (fstat(fileno(fbuf), &minfo) >= 0 && minfo.st_size > mailsize) {
E 13
		printf("New mail has arrived.\n");
D 30
		rbuf = fopen(tempResid, "w");
E 30
I 30
		rbuf = Fopen(tempResid, "w");
E 30
D 13
		fbuf = fopen(mailname, "r");
E 13
		if (rbuf == NULL || fbuf == NULL)
			goto newmail;
#ifdef APPEND
D 33
		fseek(fbuf, mailsize, 0);
E 33
I 33
		fseek(fbuf, (long)mailsize, 0);
E 33
		while ((c = getc(fbuf)) != EOF)
D 26
			putc(c, rbuf);
E 26
I 26
			(void) putc(c, rbuf);
E 26
#else
		p = minfo.st_size - mailsize;
		while (p-- > 0) {
			c = getc(fbuf);
			if (c == EOF)
				goto newmail;
D 26
			putc(c, rbuf);
E 26
I 26
			(void) putc(c, rbuf);
E 26
		}
#endif
D 13
		fclose(fbuf);
E 13
D 30
		fclose(rbuf);
		if ((rbuf = fopen(tempResid, "r")) == NULL)
E 30
I 30
		Fclose(rbuf);
		if ((rbuf = Fopen(tempResid, "r")) == NULL)
E 30
			goto newmail;
D 31
		remove(tempResid);
E 31
I 31
		rm(tempResid);
E 31
	}
I 4

	/*
	 * Adjust the message flags in each message.
	 */

	anystat = 0;
I 5
	autohold = value("hold") != NOSTR;
	holdbit = autohold ? MPRESERVE : MBOX;
I 8
	nohold = MBOX|MSAVED|MDELETED|MPRESERVE;
	if (value("keepsave") != NOSTR)
		nohold &= ~MSAVED;
E 8
E 5
E 4
	for (mp = &message[0]; mp < &message[msgCount]; mp++) {
I 4
		if (mp->m_flag & MNEW) {
			mp->m_flag &= ~MNEW;
			mp->m_flag |= MSTATUS;
		}
		if (mp->m_flag & MSTATUS)
			anystat++;
E 4
D 5
		if (mp->m_flag & MDELETED)
			mp->m_flag = MDELETED|MTOUCH;
E 5
		if ((mp->m_flag & MTOUCH) == 0)
D 5
			mp->m_flag |= MDELETED;
E 5
I 5
			mp->m_flag |= MPRESERVE;
D 8
		if ((mp->m_flag & (MBOX|MSAVED|MDELETED|MPRESERVE)) == 0)
E 8
I 8
		if ((mp->m_flag & nohold) == 0)
E 8
			mp->m_flag |= holdbit;
E 5
	}
I 3
D 5
	autohold = value("hold") != NOSTR;
E 5
E 3
	modify = 0;
I 7
	if (Tflag != NOSTR) {
D 30
		if ((readstat = fopen(Tflag, "w")) == NULL)
E 30
I 30
		if ((readstat = Fopen(Tflag, "w")) == NULL)
E 30
			Tflag = NOSTR;
	}
E 7
	for (c = 0, p = 0, mp = &message[0]; mp < &message[msgCount]; mp++) {
I 3
D 5
		if ((mp->m_flag & (MSAVED|MDELETED)) == 0 && autohold)
			mp->m_flag |= MPRESERVE;
E 3
		if ((mp->m_flag & (MSAVED|MDELETED|MPRESERVE)) == 0)
E 5
I 5
		if (mp->m_flag & MBOX)
E 5
			c++;
D 5
		if ((mp->m_flag & MPRESERVE) || (mp->m_flag & MTOUCH) == 0)
E 5
I 5
		if (mp->m_flag & MPRESERVE)
E 5
			p++;
		if (mp->m_flag & MODIFY)
			modify++;
I 7
		if (Tflag != NOSTR && (mp->m_flag & (MREAD|MDELETED)) != 0) {
D 23
			id = hfield("article-id", mp);
			if (id != NOSTR)
E 23
I 23
			char *id;

			if ((id = hfield("article-id", mp)) != NOSTR)
E 23
				fprintf(readstat, "%s\n", id);
		}
E 7
	}
I 7
	if (Tflag != NOSTR)
D 30
		fclose(readstat);
E 30
I 30
		Fclose(readstat);
E 30
E 7
D 4
	if (p == msgCount && !modify) {
E 4
I 4
	if (p == msgCount && !modify && !anystat) {
E 4
D 23
		if (p == 1)
			printf("Held 1 message in %s\n", mailname);
		else
			printf("Held %2d messages in %s\n", p, mailname);
E 23
I 23
		printf("Held %d message%s in %s\n",
			p, p == 1 ? "" : "s", mailname);
E 23
D 13
		unlock();
E 13
I 13
D 30
		fclose(fbuf);
E 30
I 30
		Fclose(fbuf);
E 30
E 13
		return;
	}
	if (c == 0) {
		if (p != 0) {
			writeback(rbuf);
D 13
			unlock();
E 13
I 13
D 30
			fclose(fbuf);
E 30
I 30
			Fclose(fbuf);
E 30
E 13
			return;
		}
		goto cream;
	}

	/*
	 * Create another temporary file and copy user's mbox file
	 * darin.  If there is no mbox, copy nothing.
	 * If he has specified "append" don't copy his mailbox,
	 * just copy saveable entries at the end.
	 */

I 22
	mbox = expand("&");
E 22
	mcount = c;
	if (value("append") == NOSTR) {
D 30
		if ((obuf = fopen(tempQuit, "w")) == NULL) {
E 30
I 30
		if ((obuf = Fopen(tempQuit, "w")) == NULL) {
E 30
			perror(tempQuit);
D 13
			unlock();
E 13
I 13
D 30
			fclose(fbuf);
E 30
I 30
			Fclose(fbuf);
E 30
E 13
			return;
		}
D 30
		if ((ibuf = fopen(tempQuit, "r")) == NULL) {
E 30
I 30
		if ((ibuf = Fopen(tempQuit, "r")) == NULL) {
E 30
			perror(tempQuit);
D 31
			remove(tempQuit);
E 31
I 31
			rm(tempQuit);
E 31
D 30
			fclose(obuf);
D 13
			unlock();
E 13
I 13
			fclose(fbuf);
E 30
I 30
			Fclose(obuf);
			Fclose(fbuf);
E 30
E 13
			return;
		}
D 31
		remove(tempQuit);
E 31
I 31
		rm(tempQuit);
E 31
D 13
		if ((fbuf = fopen(mbox, "r")) != NULL) {
			while ((c = getc(fbuf)) != EOF)
E 13
I 13
D 30
		if ((abuf = fopen(mbox, "r")) != NULL) {
E 30
I 30
		if ((abuf = Fopen(mbox, "r")) != NULL) {
E 30
			while ((c = getc(abuf)) != EOF)
E 13
D 26
				putc(c, obuf);
E 26
I 26
				(void) putc(c, obuf);
E 26
D 13
			fclose(fbuf);
E 13
I 13
D 30
			fclose(abuf);
E 30
I 30
			Fclose(abuf);
E 30
E 13
		}
		if (ferror(obuf)) {
			perror(tempQuit);
D 30
			fclose(ibuf);
			fclose(obuf);
D 13
			unlock();
E 13
I 13
			fclose(fbuf);
E 30
I 30
			Fclose(ibuf);
			Fclose(obuf);
			Fclose(fbuf);
E 30
E 13
			return;
		}
D 30
		fclose(obuf);
E 30
I 30
		Fclose(obuf);
E 30
		close(creat(mbox, 0600));
D 10
		if ((obuf = fopen(mbox, "w")) == NULL) {
E 10
I 10
D 30
		if ((obuf = fopen(mbox, "r+")) == NULL) {
E 30
I 30
		if ((obuf = Fopen(mbox, "r+")) == NULL) {
E 30
E 10
			perror(mbox);
D 30
			fclose(ibuf);
D 13
			unlock();
E 13
I 13
			fclose(fbuf);
E 30
I 30
			Fclose(ibuf);
			Fclose(fbuf);
E 30
E 13
			return;
		}
	}
D 18
	if (value("append") != NOSTR)
E 18
I 18
	if (value("append") != NOSTR) {
E 18
D 30
		if ((obuf = fopen(mbox, "a")) == NULL) {
E 30
I 30
		if ((obuf = Fopen(mbox, "a")) == NULL) {
E 30
			perror(mbox);
D 13
			unlock();
E 13
I 13
D 30
			fclose(fbuf);
E 30
I 30
			Fclose(fbuf);
E 30
E 13
			return;
		}
I 18
		fchmod(fileno(obuf), 0600);
	}
E 18
	for (mp = &message[0]; mp < &message[msgCount]; mp++)
D 5
		if ((mp->m_flag & (MDELETED|MSAVED|MPRESERVE)) == 0)
E 5
I 5
		if (mp->m_flag & MBOX)
E 5
D 9
			if (send(mp, obuf) < 0) {
E 9
I 9
D 20
			if (send(mp, obuf, 0) < 0) {
E 20
I 20
D 25
			if (send(mp, obuf, saveignore) < 0) {
E 25
I 25
			if (send(mp, obuf, saveignore, NOSTR) < 0) {
E 25
E 20
E 9
				perror(mbox);
D 30
				fclose(ibuf);
				fclose(obuf);
D 13
				unlock();
E 13
I 13
				fclose(fbuf);
E 30
I 30
				Fclose(ibuf);
				Fclose(obuf);
				Fclose(fbuf);
E 30
E 13
				return;
			}

	/*
	 * Copy the user's old mbox contents back
	 * to the end of the stuff we just saved.
	 * If we are appending, this is unnecessary.
	 */

	if (value("append") == NOSTR) {
		rewind(ibuf);
		c = getc(ibuf);
		while (c != EOF) {
D 26
			putc(c, obuf);
E 26
I 26
			(void) putc(c, obuf);
E 26
			if (ferror(obuf))
				break;
			c = getc(ibuf);
		}
D 30
		fclose(ibuf);
E 30
I 30
		Fclose(ibuf);
E 30
D 35
		fflush(obuf);
E 35
	}
I 35
	fflush(obuf);
E 35
I 11
	trunc(obuf);
E 11
	if (ferror(obuf)) {
		perror(mbox);
D 30
		fclose(obuf);
D 13
		unlock();
E 13
I 13
		fclose(fbuf);
E 30
I 30
		Fclose(obuf);
		Fclose(fbuf);
E 30
E 13
		return;
	}
D 30
	fclose(obuf);
E 30
I 30
	Fclose(obuf);
E 30
	if (mcount == 1)
		printf("Saved 1 message in mbox\n");
	else
		printf("Saved %d messages in mbox\n", mcount);

	/*
	 * Now we are ready to copy back preserved files to
	 * the system mailbox, if any were requested.
	 */

	if (p != 0) {
		writeback(rbuf);
D 13
		unlock();
E 13
I 13
D 30
		fclose(fbuf);
E 30
I 30
		Fclose(fbuf);
E 30
E 13
		return;
	}

	/*
	 * Finally, remove his /usr/mail file.
	 * If new mail has arrived, copy it back.
	 */

cream:
	if (rbuf != NULL) {
D 10
		fbuf = fopen(mailname, "w");
E 10
I 10
D 13
		fbuf = fopen(mailname, "r+");
E 10
		if (fbuf == NULL)
E 13
I 13
D 30
		abuf = fopen(mailname, "r+");
E 30
I 30
		abuf = Fopen(mailname, "r+");
E 30
		if (abuf == NULL)
E 13
			goto newmail;
		while ((c = getc(rbuf)) != EOF)
D 13
			putc(c, fbuf);
E 13
I 13
D 26
			putc(c, abuf);
E 26
I 26
			(void) putc(c, abuf);
E 26
E 13
D 30
		fclose(rbuf);
E 30
I 30
		Fclose(rbuf);
E 30
I 11
D 13
		trunc(fbuf);
E 11
		fclose(fbuf);
E 13
I 13
		trunc(abuf);
D 30
		fclose(abuf);
E 30
I 30
		Fclose(abuf);
E 30
E 13
		alter(mailname);
D 13
		unlock();
E 13
I 13
D 30
		fclose(fbuf);
E 30
I 30
		Fclose(fbuf);
E 30
E 13
		return;
	}
	demail();
D 13
	unlock();
E 13
I 13
D 30
	fclose(fbuf);
E 30
I 30
	Fclose(fbuf);
E 30
E 13
	return;

newmail:
	printf("Thou hast new mail.\n");
D 13
	unlock();
E 13
I 13
D 14
	fclose(fbuf);
E 14
I 14
	if (fbuf != NULL)
D 30
		fclose(fbuf);
E 30
I 30
		Fclose(fbuf);
E 30
E 14
E 13
}

/*
 * Preserve all the appropriate messages back in the system
 * mailbox, and print a nice message indicated how many were
 * saved.  On any error, just return -1.  Else return 0.
 * Incorporate the any new mail that we found.
 */
I 33
int
E 33
D 9

E 9
writeback(res)
	register FILE *res;
{
	register struct message *mp;
	register int p, c;
	FILE *obuf;

	p = 0;
D 10
	if ((obuf = fopen(mailname, "w")) == NULL) {
E 10
I 10
D 30
	if ((obuf = fopen(mailname, "r+")) == NULL) {
E 30
I 30
	if ((obuf = Fopen(mailname, "r+")) == NULL) {
E 30
E 10
		perror(mailname);
		return(-1);
	}
#ifndef APPEND
	if (res != NULL)
		while ((c = getc(res)) != EOF)
D 26
			putc(c, obuf);
E 26
I 26
			(void) putc(c, obuf);
E 26
#endif
	for (mp = &message[0]; mp < &message[msgCount]; mp++)
		if ((mp->m_flag&MPRESERVE)||(mp->m_flag&MTOUCH)==0) {
			p++;
D 9
			if (send(mp, obuf) < 0) {
E 9
I 9
D 25
			if (send(mp, obuf, 0) < 0) {
E 25
I 25
			if (send(mp, obuf, (struct ignoretab *)0, NOSTR) < 0) {
E 25
E 9
				perror(mailname);
D 30
				fclose(obuf);
E 30
I 30
				Fclose(obuf);
E 30
				return(-1);
			}
		}
#ifdef APPEND
	if (res != NULL)
		while ((c = getc(res)) != EOF)
D 26
			putc(c, obuf);
E 26
I 26
			(void) putc(c, obuf);
E 26
#endif
	fflush(obuf);
I 11
	trunc(obuf);
E 11
	if (ferror(obuf)) {
		perror(mailname);
D 30
		fclose(obuf);
E 30
I 30
		Fclose(obuf);
E 30
		return(-1);
	}
	if (res != NULL)
D 30
		fclose(res);
	fclose(obuf);
E 30
I 30
		Fclose(res);
	Fclose(obuf);
E 30
	alter(mailname);
	if (p == 1)
		printf("Held 1 message in %s\n", mailname);
	else
		printf("Held %d messages in %s\n", p, mailname);
	return(0);
I 26
}

/*
 * Terminate an editing session by attempting to write out the user's
 * file from the temporary.  Save any new stuff appended to the file.
 */
I 33
void
E 33
edstop()
{
I 32
	extern char *tmpdir;
E 32
	register int gotcha, c;
	register struct message *mp;
	FILE *obuf, *ibuf, *readstat;
	struct stat statb;
	char tempname[30];
	char *mktemp();

	if (readonly)
		return;
	holdsigs();
	if (Tflag != NOSTR) {
D 30
		if ((readstat = fopen(Tflag, "w")) == NULL)
E 30
I 30
		if ((readstat = Fopen(Tflag, "w")) == NULL)
E 30
			Tflag = NOSTR;
	}
	for (mp = &message[0], gotcha = 0; mp < &message[msgCount]; mp++) {
		if (mp->m_flag & MNEW) {
			mp->m_flag &= ~MNEW;
			mp->m_flag |= MSTATUS;
		}
		if (mp->m_flag & (MODIFY|MDELETED|MSTATUS))
			gotcha++;
		if (Tflag != NOSTR && (mp->m_flag & (MREAD|MDELETED)) != 0) {
			char *id;

			if ((id = hfield("article-id", mp)) != NOSTR)
				fprintf(readstat, "%s\n", id);
		}
	}
	if (Tflag != NOSTR)
D 30
		fclose(readstat);
E 30
I 30
		Fclose(readstat);
E 30
	if (!gotcha || Tflag != NOSTR)
		goto done;
	ibuf = NULL;
	if (stat(mailname, &statb) >= 0 && statb.st_size > mailsize) {
D 27
		strcpy(tempname, "/tmp/mboxXXXXXX");
E 27
I 27
D 32
		strcpy(tempname, _PATH_TMP);
E 32
I 32
		strcpy(tempname, tmpdir);
E 32
D 28
		strcat(tempname, "/mboxXXXXXX");
E 28
I 28
		strcat(tempname, "mboxXXXXXX");
E 28
E 27
		mktemp(tempname);
D 30
		if ((obuf = fopen(tempname, "w")) == NULL) {
E 30
I 30
		if ((obuf = Fopen(tempname, "w")) == NULL) {
E 30
			perror(tempname);
			relsesigs();
			reset(0);
		}
D 30
		if ((ibuf = fopen(mailname, "r")) == NULL) {
E 30
I 30
		if ((ibuf = Fopen(mailname, "r")) == NULL) {
E 30
			perror(mailname);
D 30
			fclose(obuf);
E 30
I 30
			Fclose(obuf);
E 30
D 31
			remove(tempname);
E 31
I 31
			rm(tempname);
E 31
			relsesigs();
			reset(0);
		}
D 33
		fseek(ibuf, mailsize, 0);
E 33
I 33
		fseek(ibuf, (long)mailsize, 0);
E 33
		while ((c = getc(ibuf)) != EOF)
			(void) putc(c, obuf);
D 30
		fclose(ibuf);
		fclose(obuf);
		if ((ibuf = fopen(tempname, "r")) == NULL) {
E 30
I 30
		Fclose(ibuf);
		Fclose(obuf);
		if ((ibuf = Fopen(tempname, "r")) == NULL) {
E 30
			perror(tempname);
D 31
			remove(tempname);
E 31
I 31
			rm(tempname);
E 31
			relsesigs();
			reset(0);
		}
D 31
		remove(tempname);
E 31
I 31
		rm(tempname);
E 31
	}
	printf("\"%s\" ", mailname);
	fflush(stdout);
D 30
	if ((obuf = fopen(mailname, "r+")) == NULL) {
E 30
I 30
	if ((obuf = Fopen(mailname, "r+")) == NULL) {
E 30
		perror(mailname);
		relsesigs();
		reset(0);
	}
	trunc(obuf);
	c = 0;
	for (mp = &message[0]; mp < &message[msgCount]; mp++) {
		if ((mp->m_flag & MDELETED) != 0)
			continue;
		c++;
		if (send(mp, obuf, (struct ignoretab *) NULL, NOSTR) < 0) {
			perror(mailname);
			relsesigs();
			reset(0);
		}
	}
	gotcha = (c == 0 && ibuf == NULL);
	if (ibuf != NULL) {
		while ((c = getc(ibuf)) != EOF)
			(void) putc(c, obuf);
D 30
		fclose(ibuf);
E 30
I 30
		Fclose(ibuf);
E 30
	}
	fflush(obuf);
	if (ferror(obuf)) {
		perror(mailname);
		relsesigs();
		reset(0);
	}
D 30
	fclose(obuf);
E 30
I 30
	Fclose(obuf);
E 30
	if (gotcha) {
D 31
		remove(mailname);
E 31
I 31
		rm(mailname);
E 31
		printf("removed\n");
	} else
		printf("complete\n");
	fflush(stdout);

done:
	relsesigs();
E 26
}
E 1
