h62140
s 00000/00000/00175
d D 2.1 81/07/01 11:09:15 kurt 2 1
c Release to Heidi Stettner
e
s 00175/00000/00000
d D 1.1 80/10/08 09:50:20 kas 1 0
c date and time created 80/10/08 09:50:20 by kas
e
u
U
f b 
t
T
I 1
#

/*
 * Mail -- a mail program
 *
 * Ingres 11/70.  Unix version 6.0
 *
 * Local routines that are installation dependent.
 * All fiddlers please note:  if you make careful note of
 * what you change here, I will incorporate your changes and
 * you won't have to remake them each release.
 */

static char *SccsId = "%W% %G%";

#include "rcv.h"
#include	<errno.h>

/*
 * Locate the user's mailbox file (ie, the place where new, unread
 * mail is queued).  At Ingres, it's in /usr/spool/mail/loginname.
 */

findmail()
{
	register char *cp;

	cp = copy("/usr/spool/mail/", mailname);
	copy(myname, cp);
}

/*
 * Get rid of the queued mail.
 */

demail()
{
	if (unlink(mailname) >= 0)
		return;
	close(creat(mailname, 0666));
	alter(mailname);
}

/*
 * Get an environment variable.  At present, we only support
 * "SHELL" and "HOME".  This routine makes use of the getpw
 * routine in the neighboring getname.c stuff.
 */

char *
getenv(name)
	char name[];
{
	char pwline[LINESIZE];
	static char val[30];
	register char *cp, *dp;
	register int cc;

	if (equal(name, "SHELL"))
		cc = 6;
	else if (equal(name, "HOME"))
		cc = 5;
	else
		return(NOSTR);
	if (getpwnam(myname, pwline) < 0)
		return(NOSTR);
	for (cp = pwline; *cp && cc > 0;)
		if (*cp++ == ':')
			cc--;
	dp = cp;
	while (*cp != ':' && *cp != '\0' && *cp != '\n')
		cp++;
	*cp = '\0';
	if (*dp == '\0')
		return(NOSTR);
	copy(dp, val);
	return(val);
}

/*
 * Discover user name.  On Ingres, user names are rarely 1-1 with uids,
 * so we look for this guy in the utmp file first, then try finding
 * him in the passwd file on basis of uid if that fails.
 */

struct utmp {
	char	u_name[8];		/* User login name. */
	char	u_tty;			/* typewriter character */
	char	u_cfill;		/* Unused for now. */
	long	u_time;			/* Login time */
	short	u_wfill;		/* Unused also */
};

username(uid, namebuf)
	char namebuf[];
{
	struct utmp ubuf;
	register char *cp;
	register int tty;
	register FILE *fwho;

	tty = ttyn(0);
	if (tty == 'x')
		goto useuid;
	
	/*
	 * Dammit, I really do have to search the utmp file!
	 */

	if ((fwho = fopen("/etc/utmp", "r")) == NULL)
		goto useuid;
	while (fread(&ubuf, 1, sizeof ubuf, fwho) > 0)
		if (ubuf.u_tty == tty) {
			strncpy(namebuf, ubuf.u_name, 8);
			namebuf[8] = 0;
			cp = index(namebuf, ' ');
			if (cp != NOSTR)
				*cp = 0;
			return(0);
		}
	fclose(fwho);

useuid:
	return(getname(uid, namebuf));
}

/*
 * Unix routine to do an "fopen" on file descriptor
 * The mode has to be repeated because you can't query its
 * status
 */

FILE *
fdopen(fd, mode)
register char *mode;
{
	extern int errno;
	register FILE *iop;
	extern FILE *_lastbuf;

	for (iop = _iob; iop->_flag&(_IOREAD|_IOWRT); iop++)
		if (iop >= _lastbuf)
			return(NULL);
	iop->_cnt = 0;
	iop->_file = fd;
	if (*mode != 'r') {
		iop->_flag |= _IOWRT;
		if (*mode == 'a')
			lseek(fd, 0L, 2);
	} else
		iop->_flag |= _IOREAD;
	return(iop);
}

/*
 * Copy s2 to s1, truncating or null-padding to always copy n bytes
 * return s1
 */

char *
strncpy(s1, s2, n)
register char *s1, *s2;
{
	register i;
	register char *os1;

	os1 = s1;
	for (i = 0; i < n; i++)
		if ((*s1++ = *s2++) == '\0') {
			while (++i < n)
				*s1++ = '\0';
			return(os1);
		}
	return(os1);
}
E 1
