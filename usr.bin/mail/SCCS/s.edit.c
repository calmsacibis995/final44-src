h03038
s 00002/00002/00192
d D 8.1 93/06/06 15:07:36 bostic 25 24
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00007/00185
d D 5.16 92/06/26 12:03:10 bostic 24 23
c quad's broke it -- prototyped it rather than figure out the problem
e
s 00011/00004/00181
d D 5.15 90/06/25 00:01:16 edward 23 22
c remove call of _fwalk
e
s 00001/00011/00184
d D 5.14 90/06/01 16:58:14 bostic 22 21
c new copyright notice
e
s 00001/00001/00194
d D 5.13 89/11/24 23:07:07 edward 21 20
c sig_t
e
s 00002/00002/00193
d D 5.12 89/05/11 09:44:09 bostic 20 19
c file reorg, pathnames.h, paths.h
e
s 00000/00002/00195
d D 5.11 89/04/22 15:27:39 edward 19 18
c no more SIGCONT
e
s 00004/00005/00193
d D 5.10 88/07/08 19:41:41 edward 18 17
c removed some functions in the C library
e
s 00000/00002/00198
d D 5.9 88/07/07 04:16:11 edward 17 16
c don't include wait.h
e
s 00125/00121/00075
d D 5.8 88/07/07 02:48:09 edward 16 15
c rationalized calling of editors and starting processes in general
e
s 00012/00007/00184
d D 5.7 88/06/29 21:01:37 bostic 15 14
c install approved copyright notice
e
s 00036/00062/00155
d D 5.6 88/06/29 19:09:01 edward 14 13
c cleaned up edit1, use a file in /tmp, not in current directory, and more
e
s 00011/00005/00206
d D 5.5 88/02/18 17:03:48 bostic 13 12
c written by Kurt Shoens; added Berkeley specific header
e
s 00022/00022/00189
d D 5.4 87/05/18 12:51:54 edward 12 11
c lint
e
s 00019/00030/00192
d D 5.3 87/05/18 12:28:56 edward 11 10
c major rework: made faster, cleaned up, obsolete code removed,
c the whole thing should be chucked and written from scratch
e
s 00001/00001/00221
d D 5.2 85/06/21 17:09:42 mckusick 10 9
c botched copyright
e
s 00007/00001/00215
d D 5.1 85/06/06 10:29:35 dist 9 8
c Add copyright
e
s 00003/00003/00213
d D 2.5 83/08/11 22:15:13 sam 8 7
c standardize sccs keyword lines
e
s 00002/00002/00214
d D 2.4 82/10/21 05:36:37 carl 7 6
c Changes to support long mail sizes (long m_size).
e
s 00001/00001/00215
d D 2.3 82/07/28 23:13:26 kurt 6 5
c changed arguments to send to include the new doignore argument 
c 
e
s 00001/00000/00215
d D 2.2 82/07/26 17:08:33 kurt 5 4
c added call on sigchild() after fork to fix retrofit signals 
c 
e
s 00000/00000/00215
d D 2.1 81/07/01 11:08:33 kurt 4 3
c Release to Heidi Stettner
e
s 00006/00006/00209
d D 1.3 81/04/01 12:46:34 kurt 3 2
c changed calls on signal to sigset/sigsys
e
s 00018/00000/00197
d D 1.2 80/10/16 17:27:09 kas 2 1
c now makes the temporary editing file mode 0400 if in readonly
c mode so that you can't easily change it.  also, will not read back in the
c new version in read only mode.
e
s 00197/00000/00000
d D 1.1 80/10/08 09:49:39 kas 1 0
c date and time created 80/10/08 09:49:39 by kas
e
u
U
f b 
t
T
I 9
/*
D 25
 * Copyright (c) 1980 Regents of the University of California.
D 13
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 13
I 13
 * All rights reserved.
E 25
I 25
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 25
 *
D 22
 * Redistribution and use in source and binary forms are permitted
D 15
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 15
I 15
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
E 22
I 22
 * %sccs.include.redist.c%
E 22
E 15
E 13
 */

E 9
I 1
D 8
#
E 8
I 8
D 13
#ifndef lint
D 10
static char sccsid[] = "%W% (Berkeley) %G%";
E 10
I 10
static char *sccsid = "%W% (Berkeley) %G%";
E 10
D 9
#endif
E 9
I 9
#endif not lint
E 13
I 13
D 15
#ifdef notdef
E 15
I 15
#ifndef lint
E 15
static char sccsid[] = "%W% (Berkeley) %G%";
D 15
#endif /* notdef */
E 15
I 15
#endif /* not lint */
E 15
E 13
E 9
E 8

#include "rcv.h"
D 17
#include <stdio.h>
E 17
D 24
#include <sys/stat.h>
E 24
I 24
#include <fcntl.h>
#include "extern.h"
E 24
I 11
D 17
#include <sys/wait.h>
E 17
E 11

/*
 * Mail -- a mail program
 *
 * Perform message editing functions.
 */
D 8

static char *SccsId = "%W% %G%";
E 8

/*
 * Edit a message list.
 */
D 24

E 24
I 24
int
E 24
editor(msgvec)
	int *msgvec;
{
D 16
	char *edname;
E 16

D 16
	if ((edname = value("EDITOR")) == NOSTR)
		edname = EDITOR;
	return(edit1(msgvec, edname));
E 16
I 16
	return edit1(msgvec, 'e');
E 16
}

/*
 * Invoke the visual editor on a message list.
 */
D 24

E 24
I 24
int
E 24
visual(msgvec)
	int *msgvec;
{
D 16
	char *edname;
E 16

D 16
	if ((edname = value("VISUAL")) == NOSTR)
		edname = VISUAL;
	return(edit1(msgvec, edname));
E 16
I 16
	return edit1(msgvec, 'v');
E 16
}

/*
 * Edit a message by writing the message into a funnily-named file
 * (which should not exist) and forking an editor on it.
 * We get the editor from the stuff above.
 */
I 24
int
E 24
D 14

E 14
D 16
edit1(msgvec, ed)
E 16
I 16
edit1(msgvec, type)
E 16
	int *msgvec;
D 16
	char *ed;
E 16
I 16
D 24
	char type;
E 24
I 24
	int type;
E 24
E 16
{
I 16
D 19
	int (*sigcont)() = signal(SIGCONT, SIG_DFL);
E 19
E 16
D 11
	register char *cp, *cp2;
E 11
	register int c;
D 11
	int *ip, pid, mesg, lines;
D 7
	unsigned int ms;
E 7
I 7
	long ms;
E 11
I 11
D 14
	int *ip, pid, mesg;
E 14
I 14
D 16
	int i, pid;
E 14
E 11
E 7
	int (*sigint)(), (*sigquit)();
E 16
I 16
	int i;
E 16
D 14
	FILE *ibuf, *obuf;
D 12
	char edname[15], nbuf[10];
E 12
I 12
	char edname[15];
E 12
D 11
	struct message *mp;
E 11
I 11
	register struct message *mp;
E 14
I 14
	FILE *fp;
E 14
E 11
D 16
	extern char tempEdit[];
I 14
	char *edname = tempEdit;
E 16
	register struct message *mp;
E 14
D 16
	off_t fsize(), size;
	struct stat statb;
D 14
	long modtime;
E 14
I 14
	time_t modtime;
E 14
I 11
	union wait status;
E 16
I 16
	off_t size;
E 16
E 11

	/*
D 16
	 * Set signals; locate editor.
	 */
D 14

E 14
D 3
	sigint = signal(SIGINT, SIG_IGN);
	sigquit = signal(SIGQUIT, SIG_IGN);
E 3
I 3
D 11
	sigint = sigset(SIGINT, SIG_IGN);
	sigquit = sigset(SIGQUIT, SIG_IGN);
E 11
I 11
	sigint = signal(SIGINT, SIG_IGN);
	sigquit = signal(SIGQUIT, SIG_IGN);
E 11
E 3
D 14

E 14
	/*
E 16
	 * Deal with each message to be edited . . .
	 */
D 14

	for (ip = msgvec; *ip && ip-msgvec < msgCount; ip++) {
		mesg = *ip;
		mp = &message[mesg-1];
E 14
I 14
	for (i = 0; msgvec[i] && i < msgCount; i++) {
D 16
		mp = &message[msgvec[i] - 1];
E 14
		mp->m_flag |= MODIFY;
I 11
D 14
		touch(mesg);
E 14
I 14
		touch(msgvec[i]);
E 14
		dot = mp;
E 11
D 14

E 14
		/*
D 14
		 * Make up a name for the edit file of the
		 * form "Message%d" and make sure it doesn't
		 * already exist.
E 14
I 14
		 * Copy the message into the edit file.
		 * If we are in read only mode, make the
		 * temporary message file readonly as well.
E 14
		 */
D 11

		cp = &nbuf[10];
		*--cp = 0;
		while (mesg) {
			*--cp = mesg % 10 + '0';
			mesg /= 10;
		}
		cp2 = copy("Message", edname);
		while (*cp2++ = *cp++)
			;
E 11
I 11
D 12
		sprintf(edname, "Message%d", mesg);
E 12
I 12
D 14
		(void) sprintf(edname, "Message%d", mesg);
E 12
E 11
		if (!access(edname, 2)) {
			printf("%s: file exists\n", edname);
E 14
I 14
		if ((c = creat(edname, readonly ? 0400 : 0600)) < 0) {
			perror(edname);
E 14
			goto out;
E 16
I 16
D 21
		int (*sigint)();
E 21
I 21
		sig_t sigint;
E 21
D 18
		int m = msgvec[i];
E 18

		if (i > 0) {
			char buf[100];
			char *p;

D 18
			printf("Edit message %d [ynq]? ", m);
E 18
I 18
			printf("Edit message %d [ynq]? ", msgvec[i]);
E 18
			if (fgets(buf, sizeof buf, stdin) == 0)
				break;
D 18
			for (p = buf; any(*p, " \t"); p++)
E 18
I 18
			for (p = buf; *p == ' ' || *p == '\t'; p++)
E 18
				;
			if (*p == 'q')
				break;
			if (*p == 'n')
				continue;
E 16
		}
D 14

		/*
		 * Copy the message into the edit file.
		 */
D 11

E 11
D 12
		close(creat(edname, 0600));
E 12
I 12
		(void) close(creat(edname, 0600));
E 12
		if ((obuf = fopen(edname, "w")) == NULL) {
E 14
I 14
D 16
		if ((fp = fdopen(c, "w")) == NULL) {
E 14
			perror(edname);
I 14
			(void) unlink(edname);
E 14
			goto out;
		}
D 6
		if (send(mp, obuf) < 0) {
E 6
I 6
D 14
		if (send(mp, obuf, 0) < 0) {
E 14
I 14
		if (send(mp, fp, 0) < 0) {
E 14
E 6
			perror(edname);
E 16
I 16
D 18
		dot = mp = &message[m - 1];
		touch(m);
E 18
I 18
		dot = mp = &message[msgvec[i] - 1];
		touch(mp);
E 18
		sigint = signal(SIGINT, SIG_IGN);
		fp = run_editor(setinput(mp), mp->m_size, type, readonly);
		if (fp != NULL) {
D 24
			(void) fseek(otf, (long) 0, 2);
E 24
I 24
			(void) fseek(otf, 0L, 2);
E 24
			size = ftell(otf);
			mp->m_block = blockof(size);
			mp->m_offset = offsetof(size);
			mp->m_size = fsize(fp);
			mp->m_lines = 0;
			mp->m_flag |= MODIFY;
			rewind(fp);
			while ((c = getc(fp)) != EOF) {
				if (c == '\n')
					mp->m_lines++;
				if (putc(c, otf) == EOF)
					break;
			}
			if (ferror(otf))
				perror("/tmp");
E 16
D 12
			fclose(obuf);
			remove(edname);
E 12
I 12
D 14
			(void) fclose(obuf);
			(void) remove(edname);
E 14
I 14
D 23
			(void) fclose(fp);
E 23
I 23
			(void) Fclose(fp);
E 23
D 16
			(void) unlink(edname);
E 14
E 12
			goto out;
E 16
		}
D 12
		fflush(obuf);
E 12
I 12
D 14
		(void) fflush(obuf);
E 12
		if (ferror(obuf)) {
D 12
			remove(edname);
			fclose(obuf);
E 12
I 12
			(void) remove(edname);
			(void) fclose(obuf);
E 14
I 14
D 16
		(void) fflush(fp);
		if (ferror(fp)) {
			(void) unlink(edname);
			(void) fclose(fp);
E 14
E 12
			goto out;
		}
D 12
		fclose(obuf);
E 12
I 12
D 14
		(void) fclose(obuf);
E 12

E 14
I 14
		if (fstat(fileno(fp), &statb) < 0)
			modtime = 0;
		else
			modtime = statb.st_mtime;
		(void) fclose(fp);
E 14
		/*
I 2
D 14
		 * If we are in read only mode, make the
		 * temporary message file readonly as well.
		 */

		if (readonly)
D 12
			chmod(edname, 0400);
E 12
I 12
			(void) chmod(edname, 0400);
E 12

		/*
E 14
E 2
		 * Fork/execl the editor on the edit file.
		 */
D 14

		if (stat(edname, &statb) < 0)
			modtime = 0;
		modtime = statb.st_mtime;
E 14
		pid = vfork();
		if (pid == -1) {
			perror("fork");
D 12
			remove(edname);
E 12
I 12
D 14
			(void) remove(edname);
E 14
I 14
			(void) unlink(edname);
E 14
E 12
			goto out;
		}
		if (pid == 0) {
I 5
D 11
			sigchild();
E 11
E 5
			if (sigint != SIG_IGN)
D 3
				signal(SIGINT, SIG_DFL);
E 3
I 3
D 11
				sigsys(SIGINT, SIG_DFL);
E 11
I 11
D 12
				signal(SIGINT, SIG_DFL);
E 12
I 12
				(void) signal(SIGINT, SIG_DFL);
E 12
E 11
E 3
			if (sigquit != SIG_IGN)
D 3
				signal(SIGQUIT, SIG_DFL);
E 3
I 3
D 11
				sigsys(SIGQUIT, SIG_DFL);
E 11
I 11
D 12
				signal(SIGQUIT, SIG_DFL);
E 12
I 12
				(void) signal(SIGQUIT, SIG_DFL);
E 12
E 11
E 3
			execl(ed, ed, edname, 0);
			perror(ed);
			_exit(1);
		}
D 11
		while (wait(&mesg) != pid)
E 11
I 11
		while (wait(&status) != pid)
E 11
			;
I 2
D 14

E 14
		/*
		 * If in read only mode, just remove the editor
		 * temporary and return.
		 */
D 14

E 14
		if (readonly) {
D 12
			remove(edname);
E 12
I 12
D 14
			(void) remove(edname);
E 14
I 14
			(void) unlink(edname);
E 14
E 12
			continue;
		}
E 2
D 14

E 14
		/*
		 * Now copy the message to the end of the
		 * temp file.
		 */
D 14

E 14
		if (stat(edname, &statb) < 0) {
			perror(edname);
			goto out;
		}
		if (modtime == statb.st_mtime) {
D 12
			remove(edname);
E 12
I 12
D 14
			(void) remove(edname);
E 14
I 14
			(void) unlink(edname);
E 14
E 12
			goto out;
		}
D 14
		if ((ibuf = fopen(edname, "r")) == NULL) {
E 14
I 14
		if ((fp = fopen(edname, "r")) == NULL) {
E 14
			perror(edname);
D 12
			remove(edname);
E 12
I 12
D 14
			(void) remove(edname);
E 14
I 14
			(void) unlink(edname);
E 14
E 12
			goto out;
		}
D 12
		remove(edname);
		fseek(otf, (long) 0, 2);
E 12
I 12
D 14
		(void) remove(edname);
E 14
I 14
		(void) unlink(edname);
E 14
		(void) fseek(otf, (long) 0, 2);
E 12
D 11
		size = fsize(otf);
E 11
I 11
		size = ftell(otf);
E 11
		mp->m_block = blockof(size);
		mp->m_offset = offsetof(size);
D 7
		ms = 0;
E 7
I 7
D 11
		ms = 0L;
E 7
		lines = 0;
E 11
I 11
D 14
		mp->m_size = fsize(ibuf);
E 14
I 14
		mp->m_size = fsize(fp);
E 14
		mp->m_lines = 0;
E 11
D 14
		while ((c = getc(ibuf)) != EOF) {
E 14
I 14
		while ((c = getc(fp)) != EOF) {
E 14
			if (c == '\n')
D 11
				lines++;
E 11
I 11
				mp->m_lines++;
E 11
D 12
			putc(c, otf);
E 12
I 12
			(void) putc(c, otf);
E 12
			if (ferror(otf))
				break;
D 11
			ms++;
E 11
		}
D 11
		mp->m_size = ms;
		mp->m_lines = lines;
E 11
		if (ferror(otf))
			perror("/tmp");
D 12
		fclose(ibuf);
E 12
I 12
D 14
		(void) fclose(ibuf);
E 14
I 14
		(void) fclose(fp);
E 16
I 16
		(void) signal(SIGINT, sigint);
	}
D 19
	(void) signal(SIGCONT, sigcont);
E 19
	return 0;
}

/*
 * Run an editor on the file at "fpp" of "size" bytes,
 * and return a new file pointer.
 * Signals must be handled by the caller.
D 20
 * "Type" is 'e' for EDITOR, 'v' for VISUAL.
E 20
I 20
 * "Type" is 'e' for _PATH_EX, 'v' for _PATH_VI.
E 20
 */
FILE *
run_editor(fp, size, type, readonly)
	register FILE *fp;
	off_t size;
D 24
	char type;
E 24
I 24
	int type, readonly;
E 24
{
	register FILE *nf = NULL;
	register int t;
	time_t modtime;
	char *edit;
	struct stat statb;
	extern char tempEdit[];

	if ((t = creat(tempEdit, readonly ? 0400 : 0600)) < 0) {
		perror(tempEdit);
		goto out;
E 16
E 14
E 12
	}
I 16
D 23
	if ((nf = fdopen(t, "w")) == NULL) {
E 23
I 23
	if ((nf = Fdopen(t, "w")) == NULL) {
E 23
		perror(tempEdit);
		(void) unlink(tempEdit);
		goto out;
	}
	if (size >= 0)
		while (--size >= 0 && (t = getc(fp)) != EOF)
			(void) putc(t, nf);
	else
		while ((t = getc(fp)) != EOF)
			(void) putc(t, nf);
	(void) fflush(nf);
	if (fstat(fileno(nf), &statb) < 0)
		modtime = 0;
	else
		modtime = statb.st_mtime;
D 23
	if (ferror(nf) || fclose(nf) < 0) {
E 23
I 23
	if (ferror(nf)) {
		(void) Fclose(nf);
E 23
		perror(tempEdit);
		(void) unlink(tempEdit);
		nf = NULL;
		goto out;
	}
I 23
	if (Fclose(nf) < 0) {
		perror(tempEdit);
		(void) unlink(tempEdit);
		nf = NULL;
		goto out;
	}
E 23
	nf = NULL;
	if ((edit = value(type == 'e' ? "EDITOR" : "VISUAL")) == NOSTR)
D 20
		edit = type == 'e' ? EDITOR : VISUAL;
E 20
I 20
		edit = type == 'e' ? _PATH_EX : _PATH_VI;
E 20
D 24
	if (run_command(edit, 0, -1, -1, tempEdit, NOSTR) < 0) {
E 24
I 24
	if (run_command(edit, 0, -1, -1, tempEdit, NOSTR, NOSTR) < 0) {
E 24
		(void) unlink(tempEdit);
		goto out;
	}
E 16
D 14

E 14
	/*
D 16
	 * Restore signals and return.
E 16
I 16
	 * If in read only mode or file unchanged, just remove the editor
	 * temporary and return.
E 16
	 */
I 16
	if (readonly) {
		(void) unlink(tempEdit);
		goto out;
	}
	if (stat(tempEdit, &statb) < 0) {
		perror(tempEdit);
		goto out;
	}
	if (modtime == statb.st_mtime) {
		(void) unlink(tempEdit);
		goto out;
	}
	/*
	 * Now switch to new file.
	 */
D 23
	if ((nf = fopen(tempEdit, "a+")) == NULL) {
E 23
I 23
	if ((nf = Fopen(tempEdit, "a+")) == NULL) {
E 23
		perror(tempEdit);
		(void) unlink(tempEdit);
		goto out;
	}
	(void) unlink(tempEdit);
E 16
D 14

E 14
out:
D 3
	signal(SIGINT, sigint);
	signal(SIGQUIT, sigquit);
E 3
I 3
D 11
	sigset(SIGINT, sigint);
	sigset(SIGQUIT, sigquit);
E 11
I 11
D 12
	signal(SIGINT, sigint);
	signal(SIGQUIT, sigquit);
E 12
I 12
D 16
	(void) signal(SIGINT, sigint);
	(void) signal(SIGQUIT, sigquit);
E 12
	return 0;
E 16
I 16
	return nf;
E 16
E 11
E 3
}
E 1
