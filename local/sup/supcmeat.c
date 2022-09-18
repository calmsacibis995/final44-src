/*
 * Copyright (c) 1991 Carnegie Mellon University
 * All Rights Reserved.
 * 
 * Permission to use, copy, modify and distribute this software and its
 * documentation is hereby granted, provided that both the copyright
 * notice and this permission notice appear in all copies of the
 * software, derivative works or modified versions, and any portions
 * thereof, and that both notices appear in supporting documentation.
 *
 * CARNEGIE MELLON ALLOWS FREE USE OF THIS SOFTWARE IN ITS "AS IS"
 * CONDITION.  CARNEGIE MELLON DISCLAIMS ANY LIABILITY OF ANY KIND FOR
 * ANY DAMAGES WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE.
 *
 * Carnegie Mellon requests users of this software to return to
 *
 *  Software Distribution Coordinator   or   Software.Distribution@CS.CMU.EDU
 *  School of Computer Science
 *  Carnegie Mellon University
 *  Pittsburgh PA 15213-3890
 *
 * any improvements or extensions that they make and grant Carnegie the rights
 * to redistribute these changes.
 */
/*
 * sup "meat" routines
 **********************************************************************
 * HISTORY
 * 13-Mar-90  Mary Thompson (mrt) at Carnegie-Mellon University
 *	Added release to name of last and when files.
 *
 * $Log:	supcmeat.c,v $
 * Revision 1.12  89/08/23  14:55:44  gm0w
 * 	Changed msgf routines to msg routines.
 * 	[89/08/23            gm0w]
 * 
 * Revision 1.11  89/08/03  19:49:10  mja
 * 	Updated to use v*printf() in place of _doprnt().
 * 	[89/04/19            mja]
 * 
 * Revision 1.10  89/06/18  14:41:27  gm0w
 * 	Fixed up some notify messages of errors to use "SUP:" prefix.
 * 	[89/06/18            gm0w]
 * 
 * Revision 1.9  89/06/10  15:12:17  gm0w
 * 	Changed to always use rename to install targets.  This breaks hard
 * 	links and recreates those known to sup, other links will be orphaned.
 * 	[89/06/10            gm0w]
 * 
 * Revision 1.8  89/05/24  15:04:23  gm0w
 * 	Added code to check for EINVAL from FSPARAM ioctl for disk
 * 	space check failures when the ioctl is not implemented.
 * 	[89/05/24            gm0w]
 * 
 * Revision 1.7  89/01/16  18:22:28  gm0w
 * 	Changed needone() to check that mode of files match before
 * 	setting update if times also match.
 * 	[89/01/16            gm0w]
 * 
 * 10-Feb-88  Glenn Marcy (gm0w) at Carnegie-Mellon University
 *	Added timeout to backoff.
 *
 * 27-Dec-87  Glenn Marcy (gm0w) at Carnegie-Mellon University
 *	Added crosspatch support.
 *
 * 09-Sep-87  Glenn Marcy (gm0w) at Carnegie-Mellon University
 *	Added code to be less verbose when updating files that have
 *	already been successfully upgraded.
 *
 * 28-Jun-87  Glenn Marcy (gm0w) at Carnegie-Mellon University
 *	Added code for "release" support.
 *
 * 26-May-87  Doug Philips (dwp) at Carnegie-Mellon University
 *	Converted to end connection with more information.
 *	Added done routine.  Modified goaway routine to free old
 *	goawayreason.
 *
 * 26-May-87  Doug Philips (dwp) at Carnegie-Mellon University
 *	Use computeBackoff from scm instead of doing it ourselves.
 *
 * 25-May-87  Doug Philips (dwp) at Carnegie-Mellon University
 *	Split off from sup.c and reindented goaway calls.
 *
 **********************************************************************
 */

#include "supcdefs.h"
#include <sys/wait.h>
#include <varargs.h>

TREE *lastT;				/* last filenames in collection */
jmp_buf sjbuf;				/* jump location for network errors */
int dontjump;				/* flag to void sjbuf */

extern COLLECTION *thisC;		/* collection list pointer */
extern int rpauseflag;			/* don't disable resource pausing */
extern int portdebug;			/* network debugging ports */

/*************************************************
 ***    U P G R A D E   C O L L E C T I O N    ***
 *************************************************/

/* The next two routines define the fsm to support multiple fileservers
 * per collection.
 */
getonehost (t,state)
register TREE *t;
int *state;
{
	if (t->Tflags != *state)
		return (SCMOK);
	if (*state != 0 && t->Tmode == SCMEOF) {
		t->Tflags = 0;
		return (SCMOK);
	}
	if (*state == 2)
		t->Tflags--;
	else
		t->Tflags++;
	thisC->Chost = t;
	return (SCMEOF);
}

TREE *getcollhost (tout,backoff,state,nhostsp)
int *tout,*backoff,*state,*nhostsp;
{
	static int laststate = 0;
	static int nhosts = 0;

	if (*state != laststate) {
		*nhostsp = nhosts;
		laststate = *state;
		nhosts = 0;
	}
	if (Tprocess (thisC->Chtree,getonehost,*state) == SCMEOF) {
		if (*state != 0 && nhosts == 0 && !dobackoff (tout,backoff))
			return (NULL);
		nhosts++;
		return (thisC->Chost);
	}
	if (nhosts == 0)
		return (NULL);
	if (*state == 2)
		(*state)--;
	else
		(*state)++;
	return (getcollhost (tout,backoff,state,nhostsp));
}

/*  Upgrade a collection from the file server on the appropriate
 *  host machine.
 */

getcoll ()
{
	register TREE *t;
	register int x;
	int tout,backoff,state,nhosts;

	collname = thisC->Cname;
	tout = thisC->Ctimeout;
	lastT = NULL;
	backoff = 2;
	state = 0;
	nhosts = 0;
	for (;;) {
		t = getcollhost (&tout,&backoff,&state,&nhosts);
		if (t == NULL) {
			finishup (SCMEOF);
			notify ((char *)NULL);
			return;
		}
		t->Tmode = SCMEOF;
		dontjump = FALSE;
		if (!setjmp (sjbuf) && !signon (t,nhosts,&tout) && !setup (t))
			break;
		(void) requestend ();
	}
	dontjump = FALSE;
	if (setjmp (sjbuf))
		x = SCMERR;
	else {
		login ();
		listfiles ();
		recvfiles ();
		x = SCMOK;
	}
	if (thisC->Clockfd >= 0) {
		(void) close (thisC->Clockfd);
		thisC->Clockfd = -1;
	}
	finishup (x);
	notify ((char *)NULL);
}

/***  Sign on to file server ***/

int signon (t,nhosts,tout)
register TREE *t;
int nhosts;
int *tout;
{
	register int x;
	int timeout;

	if ((thisC->Cflags&CFLOCAL) == 0 && thishost (thisC->Chost->Tname)) {
		vnotify ("SUP: Skipping local collection %s\n",collname);
		t->Tmode = SCMEOF;
		return (TRUE);
	}
	if (nhosts == 1)
		timeout = *tout;
	else
		timeout = 0;
	x = request (portdebug?DEBUGFPORT:FILEPORT,
			thisC->Chost->Tname,&timeout);
	if (nhosts == 1)
		*tout = timeout;
	if (x != SCMOK) {
		if (nhosts) {
			notify ("SUP: Can't connect to host %s\n",
				thisC->Chost->Tname);
			t->Tmode = SCMEOF;
		} else
			t->Tmode = SCMOK;
		return (TRUE);
	}
	xpatch = FALSE;
	x = msgsignon ();	/* signon to fileserver */
	if (x != SCMOK)
		goaway ("Error sending signon request to fileserver");
	x = msgsignonack ();	/* receive signon ack from fileserver */
	if (x != SCMOK)
		goaway ("Error reading signon reply from fileserver");
	vnotify ("SUP Fileserver %d.%d (%s) %d on %s\n",
		protver,pgmver,scmver,fspid,remotehost());
	free (scmver);
	scmver = NULL;
	if (protver < 4) {
		dontjump = TRUE;
		goaway ("Fileserver sup protocol version is obsolete.");
		notify ("SUP: This version of sup can only communicate with a fileserver using at least\n");
		notify ("SUP: version 4 of the sup network protocol.  You should either run a newer\n");
		notify ("SUP: version of the sup fileserver or find an older version of sup.\n");
		t->Tmode = SCMEOF;
		return (TRUE);
	}
	return (FALSE);
}

/***  Tell file server what to connect to ***/

setup (t)
register TREE *t;
{
	char buf[STRINGLENGTH];
	char relsufix[STRINGLENGTH];
	register int f,x;
	struct stat sbuf;

	if (chdir (thisC->Cbase) < 0)
		goaway ("Can't change to base directory %s",thisC->Cbase);
	if (stat ("sup",&sbuf) < 0) {
		(void) mkdir ("sup",0755);
		if (stat("sup",&sbuf) < 0)
			goaway ("Can't create directory %s/sup",thisC->Cbase);
		vnotify ("SUP Created directory %s/sup\n",thisC->Cbase);
	}
	if (thisC->Cprefix && chdir (thisC->Cprefix) < 0)
		goaway ("Can't change to %s from base directory %s",
			thisC->Cprefix,thisC->Cbase);
	if (stat (".",&sbuf) < 0)
		goaway ("Can't stat %s directory %s",
			thisC->Cprefix?"prefix":"base",
			thisC->Cprefix?thisC->Cprefix:thisC->Cbase);
	if (thisC->Cprefix)  (void) chdir (thisC->Cbase);
	/* read time of last upgrade from when file */
	if (thisC->Crelease)
		(void) sprintf (relsufix,".%s",thisC->Crelease);
	else relsufix[0] = '\0';
	(void) sprintf (buf,FILEWHEN,collname,relsufix);
	f = open (buf,O_RDONLY,0);
	if (f >= 0) {
		if (read(f,(char *)&lasttime,sizeof(long)) != sizeof(long))
			lasttime = 0;
		(void) close (f);
	} else
		lasttime = 0;
	/* setup for msgsetup */
	basedir = thisC->Chbase;
	basedev = sbuf.st_dev;
	baseino = sbuf.st_ino;
	listonly = (thisC->Cflags&CFLIST);
	newonly = ((thisC->Cflags&(CFALL|CFDELETE|CFOLD)) == 0);
	release = thisC->Crelease;
	x = msgsetup ();
	if (x != SCMOK)
		goaway ("Error sending setup request to file server");
	x = msgsetupack ();
	if (x != SCMOK)
		goaway ("Error reading setup reply from file server");
	if (setupack == FSETUPOK) {
		/* Test encryption */
		(void) netcrypt (thisC->Ccrypt);
		crypttest = CRYPTTEST;
		x = msgcrypt ();
		if (x != SCMOK)
			goaway ("Error sending encryption test request");
		x = msgcryptok ();
		if (x == SCMEOF)
			goaway ("Data encryption test failed");
		if (x != SCMOK)
			goaway ("Error reading encryption test reply");
		return (FALSE);
	}
	switch (setupack) {
	case FSETUPSAME:
		notify ("SUP: Attempt to upgrade from same host to same directory\n");
		done (FDONESRVERROR,"Overwrite error");
	case FSETUPHOST:
		notify ("SUP: This host has no permission to access %s\n",
			collname);
		done (FDONESRVERROR,"Permission denied");
	case FSETUPOLD:
		notify ("SUP: This version of SUP is too old for the fileserver\n");
		done (FDONESRVERROR,"Obsolete client");
	case FSETUPRELEASE:
		notify ("SUP: Invalid release %s for collection %s\n",
			release == NULL ? DEFRELEASE : release,collname);
		done (FDONESRVERROR,"Invalid release");
	case FSETUPBUSY:
		vnotify ("SUP Fileserver is currently busy\n");
		t->Tmode = SCMOK;
		doneack = FDONESRVERROR;
		donereason = "Fileserver is busy";
		(void) netcrypt ((char *)NULL);
		(void) msgdone ();
		return (TRUE);
	default:
		goaway ("Unrecognized file server setup status %d",setupack);
	}
	/* NOTREACHED */
}

/***  Tell file server what account to use ***/

int login ()
{
	char buf[STRINGLENGTH];
	register int f,x;

	/* lock collection if desired */
	(void) sprintf (buf,FILELOCK,collname);
	f = open (buf,O_RDONLY,0);
	if (f >= 0) {
		if (flock (f,(LOCK_EX|LOCK_NB)) < 0) {
			if (errno != EWOULDBLOCK)
				goaway ("Can't lock collection %s",collname);
			if (flock (f,(LOCK_SH|LOCK_NB)) < 0) {
				(void) close (f);
				if (errno == EWOULDBLOCK)
					goaway ("Collection %s is locked by another sup",collname);
				goaway ("Can't lock collection %s",collname);
			}
			vnotify ("SUP Waiting for exclusive access lock\n");
			if (flock (f,LOCK_EX) < 0) {
				(void) close (f);
				goaway ("Can't lock collection %s",collname);
			}
		}
		thisC->Clockfd = f;
		vnotify ("SUP Locked collection %s for exclusive access\n",collname);
	}
	logcrypt = CRYPTTEST;
	loguser = thisC->Clogin;
	logpswd = thisC->Cpswd;
	(void) netcrypt (PSWDCRYPT);	/* encrypt password data */
	x = msglogin ();
	(void) netcrypt ((char *)NULL);	/* turn off encryption */
	if (x != SCMOK)
		goaway ("Error sending login request to file server");
	x = msglogack ();
	if (x != SCMOK)
		goaway ("Error reading login reply from file server");
	if (logack == FLOGNG) {
		notify ("SUP: %s\n",logerror);
		free (logerror);
		logerror = NULL;
		notify ("SUP: Improper login to %s account",
			thisC->Clogin ? thisC->Clogin : "default");
		done (FDONESRVERROR,"Improper login");
	}
	(void) netcrypt (thisC->Ccrypt);	/* restore encryption */
}

/*
 *  send list of files that we are not interested in.  receive list of
 *  files that are on the repository that could be upgraded.  Find the
 *  ones that we need.  Receive the list of files that the server could
 *  not access.  Delete any files that have been upgraded in the past
 *  which are no longer on the repository.
 */

int listfiles ()
{
	int needone(), denyone(), deleteone();
	char buf[STRINGLENGTH];
	char relsufix[STRINGLENGTH];
	register char *p,*q;
	register FILE *f;
	register int x;

	if (release)
		(void) sprintf (relsufix,".%s",release);
	else relsufix[0] = '\0';
	(void) sprintf (buf,FILELAST,collname,relsufix);
	f = fopen (buf,"r");
	if (f) {
		while (p = fgets (buf,STRINGLENGTH,f)) {
			if (q = index (p,'\n'))  *q = '\0';
			if (index ("#;:",*p))  continue;
			(void) Tinsert (&lastT,p,FALSE);
		}
		(void) fclose (f);
	}
	refuseT = NULL;
	(void) sprintf (buf,FILEREFUSE,collname);
	f = fopen (buf,"r");
	if (f) {
		while (p = fgets (buf,STRINGLENGTH,f)) {
			if (q = index (p,'\n'))  *q = '\0';
			if (index ("#;:",*p))  continue;
			(void) Tinsert (&refuseT,p,FALSE);
		}
		(void) fclose (f);
	}
	vnotify ("SUP Requesting changes since %s",ctime (&lasttime));
	x = msgrefuse ();
	if (x != SCMOK)
		goaway ("Error sending refuse list to file server");
	listT = NULL;
	x = msglist ();
	if (x != SCMOK)
		goaway ("Error reading file list from file server");
	if (thisC->Cprefix)  (void) chdir (thisC->Cprefix);
	needT = NULL;
	(void) Tprocess (listT,needone);
	Tfree (&listT);
	x = msgneed ();
	if (x != SCMOK)
		goaway ("Error sending needed files list to file server");
	Tfree (&needT);
	denyT = NULL;
	x = msgdeny ();
	if (x != SCMOK)
		goaway ("Error reading denied files list from file server");
	if (thisC->Cflags&CFVERBOSE)
		(void) Tprocess (denyT,denyone);
	Tfree (&denyT);
	if (thisC->Cflags&(CFALL|CFDELETE|CFOLD))
		(void) Trprocess (lastT,deleteone);
	Tfree (&refuseT);
}

needone (t)
register TREE *t;
{
	register TREE *newt;
	register int exists,update;
	struct stat sbuf;

	newt = Tinsert (&lastT,t->Tname,TRUE);
	newt->Tflags |= FUPDATE;
	update = FALSE;
	if ((thisC->Cflags&CFALL) == 0) {
		if ((t->Tflags&FNEW) == 0 && (thisC->Cflags&CFOLD) == 0)
			return (SCMOK);
		if ((t->Tmode&S_IFMT) == S_IFLNK)
			exists = (lstat (t->Tname,&sbuf) == 0);
		else
			exists = (stat (t->Tname,&sbuf) == 0);
		update = (exists &&
			  (sbuf.st_mode&S_IFMT) == (t->Tmode&S_IFMT) &&
			  ((t->Tmode&S_IFMT) != S_IFREG ||
			   sbuf.st_mtime == t->Tmtime));
		if ((t->Tflags&FNEW) == 0 && update)
			return (SCMOK);
	}
	newt = Tinsert (&needT,t->Tname,TRUE);
	if (update && (t->Tmode&S_IFMT) == S_IFREG)
		newt->Tflags |= FUPDATE;
	return (SCMOK);
}

denyone (t)
register TREE *t;
{
	vnotify ("SUP: Access denied to %s\n",t->Tname);
	return (SCMOK);
}

deleteone (t)
TREE *t;
{
	struct stat sbuf;
	register int x;
	register char *name = t->Tname;

	if (t->Tflags&FUPDATE)		/* in current upgrade list */
		return (SCMOK);
	if (lstat(name,&sbuf) < 0)	/* doesn't exist */
		return (SCMOK);
	/* is it a symbolic link ? */
	if ((sbuf.st_mode & S_IFMT) == S_IFLNK) {
		if (Tlookup (refuseT,name)) {
			vnotify ("SUP Would not delete symbolic link %s\n",
				name);
			return (SCMOK);
		}
		if (thisC->Cflags&CFLIST) {
			vnotify ("SUP Would delete symbolic link %s\n",name);
			return (SCMOK);
		}
		if ((thisC->Cflags&CFDELETE) == 0) {
			notify ("SUP Please delete symbolic link %s\n",name);
			t->Tflags |= FUPDATE;
			return (SCMOK);
		}
		x = unlink (name);
		if (x < 0) {
			notify ("SUP: Unable to delete symbolic link %s\n",
				name);
			t->Tflags |= FUPDATE;
			return (SCMOK);
		}
		vnotify ("SUP Deleted symbolic link %s\n",name);
		return (SCMOK);
	}
	/* is it a directory ? */
	if ((sbuf.st_mode & S_IFMT) == S_IFDIR) {
		if (Tlookup (refuseT,name)) {
			vnotify ("SUP Would not delete directory %s\n",name);
			return (SCMOK);
		}
		if (thisC->Cflags&CFLIST) {
			vnotify ("SUP Would delete directory %s\n",name);
			return (SCMOK);
		}
		if ((thisC->Cflags&CFDELETE) == 0) {
			notify ("SUP Please delete directory %s\n",name);
			t->Tflags |= FUPDATE;
			return (SCMOK);
		}
		(void) rmdir (name);
		if (lstat(name,&sbuf) == 0) {
			notify ("SUP: Unable to delete directory %s\n",name);
			t->Tflags |= FUPDATE;
			return (SCMOK);
		}
		vnotify ("SUP Deleted directory %s\n",name);
		return (SCMOK);
	}
	/* it is a file */
	if (Tlookup (refuseT,name)) {
		vnotify ("SUP Would not delete file %s\n",name);
		return (SCMOK);
	}
	if (thisC->Cflags&CFLIST) {
		vnotify ("SUP Would delete file %s\n",name);
		return (SCMOK);
	}
	if ((thisC->Cflags&CFDELETE) == 0) {
		notify ("SUP Please delete file %s\n",name);
		t->Tflags |= FUPDATE;
		return (SCMOK);
	}
	x = unlink (name);
	if (x < 0) {
		notify ("SUP: Unable to delete file %s\n",name);
		t->Tflags |= FUPDATE;
		return (SCMOK);
	}
	vnotify ("SUP Deleted file %s\n",name);
	return (SCMOK);
}

/***************************************
 ***    R E C E I V E   F I L E S    ***
 ***************************************/

/* Note for these routines, return code SCMOK generally means
 * NETWORK communication is OK; it does not mean that the current
 * file was correctly received and stored.  If a file gets messed
 * up, too bad, just print a message and go on to the next one;
 * but if the network gets messed up, the whole sup program loses
 * badly and best just stop the program as soon as possible.
 */

recvfiles ()
{
	register int x;
	int recvone ();
	int recvmore;

	recvmore = TRUE;
	upgradeT = NULL;
	do {
		x = msgsend ();
		if (x != SCMOK)
			goaway ("Error sending receive file request to file server");
		(void) Tinsert (&upgradeT,(char *)NULL,FALSE);
		x = msgrecv (recvone,&recvmore);
		if (x != SCMOK)
			goaway ("Error receiving file from file server");
		Tfree (&upgradeT);
	} while (recvmore);
}

/* prepare the target, if necessary */
prepare (name,mode,newp,statp)
char *name;
int mode,*newp;
struct stat *statp;
{
	register char *type;

	if (mode == S_IFLNK)
		*newp = (lstat (name,statp) < 0);
	else
		*newp = (stat (name,statp) < 0);
	if (*newp) {
		if (thisC->Cflags&CFLIST)
			return (FALSE);
		if (establishdir (name))
			return (TRUE);
		return (FALSE);
	}
	if (mode == (statp->st_mode&S_IFMT))
		return (FALSE);
	*newp = TRUE;
	switch (statp->st_mode&S_IFMT) {
	case S_IFDIR:
		type = "directory";
		break;
	case S_IFLNK:
		type = "symbolic link";
		break;
	case S_IFREG:
		type = "regular file";
		break;
	default:
		type = "unknown file";
		break;
	}
	if (thisC->Cflags&CFLIST) {
		vnotify ("SUP Would remove %s %s\n",type,name);
		return (FALSE);
	}
	if ((statp->st_mode&S_IFMT) == S_IFDIR) {
		if (rmdir (name) < 0)
			runp ("rm","rm","-rf",name,0);
	} else
		(void) unlink (name);
	if (stat (name,statp) < 0) {
		vnotify ("SUP Removed %s %s\n",type,name);
		return (FALSE);
	}
	notify ("SUP: Couldn't remove %s %s\n",type,name);
	return (TRUE);
}

recvone (t,recvmore)
register TREE *t;
int **recvmore;
{
	register int x;
	int new;
	struct stat sbuf;
	int linkone (),execone ();

	/* check for end of file list */
	if (t == NULL) {
		*(*recvmore) = FALSE;
		return (SCMOK);
	}
	/* check for failed access at fileserver */
	if (t->Tmode == 0) {
		notify ("SUP: File server unable to transfer file %s\n",
			t->Tname);
		thisC->Cnogood = TRUE;
		return (SCMOK);
	}
	if (prepare (t->Tname,t->Tmode&S_IFMT,&new,&sbuf)) {
		notify ("SUP: Can't prepare path for %s\n",t->Tname);
		if ((t->Tmode&S_IFMT) == S_IFREG) {
			x = readskip ();	/* skip over file */
			if (x != SCMOK)
				goaway ("Can't skip file transfer");
		}
		thisC->Cnogood = TRUE;
		return (SCMOK);
	}
	/* make file mode specific changes */
	switch (t->Tmode&S_IFMT) {
	case S_IFDIR:
		x = recvdir (t,new,&sbuf);
		break;
	case S_IFLNK:
		x = recvsym (t,new,&sbuf);
		break;
	case S_IFREG:
		x = recvreg (t,new,&sbuf);
		break;
	default:
		goaway ("Unknown file type %o\n",t->Tmode&S_IFMT);
	}
	if (x) {
		thisC->Cnogood = TRUE;
		return (SCMOK);
	}
	if ((t->Tmode&S_IFMT) == S_IFREG)
		(void) Tprocess (t->Tlink,linkone,t->Tname);
	(void) Tprocess (t->Texec,execone);
	return (SCMOK);
}

int recvdir (t,new,statp)		/* receive directory from network */
register TREE *t;
register int new;
register struct stat *statp;
{
	struct timeval tbuf[2];

	if (new) {
		if (thisC->Cflags&CFLIST) {
			vnotify ("SUP Would create directory %s\n",t->Tname);
			return (FALSE);
		}
		(void) mkdir (t->Tname,0755);
		if (stat (t->Tname,statp) < 0) {
			notify ("SUP: Can't create directory %s\n",t->Tname);
			return (TRUE);
		}
	}
	if ((t->Tflags&FNOACCT) == 0) {
		/* convert user and group names to local ids */
		ugconvert (t->Tuser,t->Tgroup,&t->Tuid,&t->Tgid,&t->Tmode);
	}
	if (!new && (t->Tflags&FNEW) == 0 && statp->st_mtime == t->Tmtime) {
		if (t->Tflags&FNOACCT)
			return (FALSE);
		if (statp->st_uid == t->Tuid && statp->st_gid == t->Tgid)
			return (FALSE);
	}
	if (thisC->Cflags&CFLIST) {
		vnotify ("SUP Would update directory %s\n",t->Tname);
		return (FALSE);
	}
	if ((t->Tflags&FNOACCT) == 0) {
		(void) chown (t->Tname,t->Tuid,t->Tgid);
		(void) chmod (t->Tname,t->Tmode&S_IMODE);
	}
	tbuf[0].tv_sec = time((long *)NULL);  tbuf[0].tv_usec = 0;
	tbuf[1].tv_sec = t->Tmtime;  tbuf[1].tv_usec = 0;
	(void) utimes (t->Tname,tbuf);
	vnotify ("SUP %s directory %s\n",new?"Created":"Updated",t->Tname);
	return (FALSE);
}

int recvsym (t,new,statp)			/* receive symbolic link */
register TREE *t;
register int new;
register struct stat *statp;
{
	char buf[STRINGLENGTH];
	int n;
	register char *linkname;

	if (t->Tlink == NULL || t->Tlink->Tname == NULL) {
		notify ("SUP: Missing linkname for symbolic link %s\n",
			t->Tname);
		return (TRUE);
	}
	linkname = t->Tlink->Tname;
	if (!new && (t->Tflags&FNEW) == 0 &&
	    (n = readlink (t->Tname,buf,sizeof(buf))) >= 0 &&
	    (n == strlen (linkname)) && (strncmp (linkname,buf,n) == 0))
		return (FALSE);
	if (thisC->Cflags&CFLIST) {
		vnotify ("SUP Would %s symbolic link %s to %s\n",
			new?"create":"update",t->Tname,linkname);
		return (FALSE);
	}
	if (!new)
		(void) unlink (t->Tname);
	if (symlink (linkname,t->Tname) < 0 || lstat(t->Tname,statp) < 0) {
		notify ("SUP: Unable to create symbolic link %s\n",t->Tname);
		return (TRUE);
	}
	vnotify ("SUP Created symbolic link %s to %s\n",t->Tname,linkname);
	return (FALSE);
}

int recvreg (t,new,statp)			/* receive file from network */
register TREE *t;
register int new;
register struct stat *statp;
{
	register FILE *fin,*fout;
	char dirpart[STRINGLENGTH],filepart[STRINGLENGTH];
	char filename[STRINGLENGTH],buf[STRINGLENGTH];
	struct timeval tbuf[2];
	register int x;
	register char *p;

	if (t->Tflags&FUPDATE) {
		if ((t->Tflags&FNOACCT) == 0) {
			/* convert user and group names to local ids */
			ugconvert (t->Tuser,t->Tgroup,&t->Tuid,&t->Tgid,
				&t->Tmode);
		}
		if (!new && (t->Tflags&FNEW) == 0 &&
		    statp->st_mtime == t->Tmtime) {
			if (t->Tflags&FNOACCT)
				return (FALSE);
			if (statp->st_uid == t->Tuid &&
			    statp->st_gid == t->Tgid)
				return (FALSE);
		}
		if (thisC->Cflags&CFLIST) {
			vnotify ("SUP Would update file %s\n",t->Tname);
			return (FALSE);
		}
		vnotify ("SUP Updating file %s\n",t->Tname);
		if ((t->Tflags&FNOACCT) == 0) {
			(void) chown (t->Tname,t->Tuid,t->Tgid);
			(void) chmod (t->Tname,t->Tmode&S_IMODE);
		}
		tbuf[0].tv_sec = time((long *)NULL);  tbuf[0].tv_usec = 0;
		tbuf[1].tv_sec = t->Tmtime;  tbuf[1].tv_usec = 0;
		(void) utimes (t->Tname,tbuf);
		return (FALSE);
	}
	if (thisC->Cflags&CFLIST) {
		if (new)
			p = "create";
		else if (statp->st_mtime < t->Tmtime)
			p = "receive new";
		else if (statp->st_mtime > t->Tmtime)
			p = "receive old";
		else
			p = "receive";
		vnotify ("SUP Would %s file %s\n",p,t->Tname);
		return (FALSE);
	}
	vnotify ("SUP Receiving file %s\n",t->Tname);
	if (!new && (t->Tmode&S_IFMT) == S_IFREG &&
	    (t->Tflags&FBACKUP) && (thisC->Cflags&CFBACKUP)) {
		fin = fopen (t->Tname,"r");	/* create backup */
		if (fin == NULL) {
			x = readskip ();	/* skip over file */
			if (x != SCMOK)
				goaway ("Can't skip file transfer");
			notify ("SUP: Can't open %s to create backup\n",
				t->Tname);
			return (TRUE);		/* mark upgrade as nogood */
		}
		path (t->Tname,dirpart,filepart);
		(void) sprintf (filename,FILEBACKUP,dirpart,filepart);
		fout = fopen (filename,"w");
		if (fout == NULL) {
			(void) sprintf (buf,FILEBKDIR,dirpart);
			(void) mkdir (buf,0755);
			fout = fopen (filename,"w");
		}
		if (fout == NULL) {
			x = readskip ();	/* skip over file */
			if (x != SCMOK)
				goaway ("Can't skip file transfer");
			notify ("SUP: Can't create %s for backup\n",filename);
			(void) fclose (fin);
			return (TRUE);
		}
		ffilecopy (fin,fout);
		(void) fclose (fin);
		(void) fclose (fout);
		vnotify ("SUP Backup of %s created\n", t->Tname);
	}
	x = copyfile (t->Tname,(char *)NULL);
	if (x)
		return (TRUE);
	if ((t->Tflags&FNOACCT) == 0) {
		/* convert user and group names to local ids */
		ugconvert (t->Tuser,t->Tgroup,&t->Tuid,&t->Tgid,&t->Tmode);
		(void) chown (t->Tname,t->Tuid,t->Tgid);
		(void) chmod (t->Tname,t->Tmode&S_IMODE);
	}
	tbuf[0].tv_sec = time((long *)NULL);  tbuf[0].tv_usec = 0;
	tbuf[1].tv_sec = t->Tmtime;  tbuf[1].tv_usec = 0;
	(void) utimes (t->Tname,tbuf);
	return (FALSE);
}

linkone (t,fname)			/* link to file already received */
register TREE *t;
register char **fname;
{
	struct stat fbuf,sbuf;
	register char *name = t->Tname;
	int new,x;
	char *type;

	if (stat(*fname,&fbuf) < 0) {	/* source file */
		if (thisC->Cflags&CFLIST) {
			vnotify ("SUP Would link %s to %s\n",name,*fname);
			return (SCMOK);
		}
		notify ("SUP: Can't link %s to missing file %s\n",name,*fname);
		thisC->Cnogood = TRUE;
		return (SCMOK);
	}
	if (prepare (name,S_IFREG,&new,&sbuf)) {
		notify ("SUP: Can't prepare path for link %s\n",name);
		thisC->Cnogood = TRUE;
		return (SCMOK);
	}
	if (!new && (t->Tflags&FNEW) == 0 &&
	    fbuf.st_dev == sbuf.st_dev && fbuf.st_ino == sbuf.st_ino)
		return (SCMOK);
	if (thisC->Cflags&CFLIST) {
		vnotify ("SUP Would link %s to %s\n",name,*fname);
		return (SCMOK);
	}
	(void) unlink (name);
	type = "";
	if ((x = link (*fname,name)) < 0) {
		type = "symbolic ";
		x = symlink (*fname,name);
	}
	if (x < 0 || lstat(name,&sbuf) < 0) {
		notify ("SUP: Unable to create %slink %s\n",type,name);
		return (TRUE);
	}
	vnotify ("SUP Created %slink %s to %s\n",type,name,*fname);
	return (SCMOK);
}

execone (t)			/* execute command for file */
register TREE *t;
{
	union wait w;

	if (thisC->Cflags&CFLIST) {
		vnotify ("SUP Would execute %s\n",t->Tname);
		return (SCMOK);
	}
	if ((thisC->Cflags&CFEXECUTE) == 0) {
		notify ("SUP Please execute %s\n",t->Tname);
		return (SCMOK);
	}
	vnotify ("SUP Executing %s\n",t->Tname);

	w.w_status = system (t->Tname);
	if (WIFEXITED(w) && w.w_retcode != 0) {
		notify ("SUP: Execute command returned failure status %#o\n",
			w.w_retcode);
		thisC->Cnogood = TRUE;
	} else if (WIFSIGNALED(w)) {
		notify ("SUP: Execute command killed by signal %d\n",
			w.w_termsig);
		thisC->Cnogood = TRUE;
	} else if (WIFSTOPPED(w)) {
		notify ("SUP: Execute command stopped by signal %d\n",
			w.w_stopsig);
		thisC->Cnogood = TRUE;
	}
	return (SCMOK);
}

int copyfile (to,from)
char *to;
char *from;		/* 0 if reading from network */
{
	register int fromf,tof,istemp,x;
	char dpart[STRINGLENGTH],fpart[STRINGLENGTH];
	char tname[STRINGLENGTH];
	struct stat sbuf;
#if	CMUCS
	int fsize;
	struct fsparam fsp;
#endif	CMUCS
	static int thispid = 0;		/* process id # */

	if (from) {			/* reading file */
		fromf = open (from,O_RDONLY,0);
		if (fromf < 0) {
			notify ("SUP: Can't open %s to copy to %s: %s\n",
				from,to,errmsg (-1));
			return (TRUE);
		}
	} else				/* reading network */
		fromf = -1;
	istemp = TRUE;			/* try to create temp file */
	lockout (TRUE);			/* block interrupts */
	if (thispid == 0)  thispid = getpid ();
	/* Now try hard to find a temp file name.  Try VERY hard. */
	for (;;) {
	/* try destination directory */
		path (to,dpart,fpart);
		(void) sprintf (tname,"%s/#%d.sup",dpart,thispid);
		tof = open (tname,(O_WRONLY|O_CREAT|O_TRUNC),0600);
		if (tof >= 0)  break;
	/* try sup directory */
		if (thisC->Cprefix)  (void) chdir (thisC->Cbase);
		(void) sprintf (tname,"sup/#%d.sup",thispid);
		tof = open (tname,(O_WRONLY|O_CREAT|O_TRUNC),0600);
		if (tof >= 0) {
			if (thisC->Cprefix)  (void) chdir (thisC->Cprefix);
			break;
		}
	/* try base directory */
		(void) sprintf (tname,"#%d.sup",thispid);
		tof = open (tname,(O_WRONLY|O_CREAT|O_TRUNC),0600);
		if (thisC->Cprefix)  (void) chdir (thisC->Cprefix);
		if (tof >= 0)  break;
	/* try /usr/tmp */
		(void) sprintf (tname,"/usr/tmp/#%d.sup",thispid);
		tof = open (tname,(O_WRONLY|O_CREAT|O_TRUNC),0600);
		if (tof >= 0)  break;
	/* try /tmp */
		(void) sprintf (tname,"/tmp/#%d.sup",thispid);
		tof = open (tname,(O_WRONLY|O_CREAT|O_TRUNC),0600);
		if (tof >= 0)  break;
		istemp = FALSE;
	/* give up: try to create output file */
		tof = open (to,(O_WRONLY|O_CREAT|O_TRUNC),0600);
		if (tof >= 0)  break;
	/* no luck */
		notify ("SUP: Can't create %s or temp file for it\n",to);
		lockout (FALSE);
		if (fromf >= 0)
			(void) close (fromf);
		else {
			x = readskip ();
			if (x != SCMOK)
				goaway ("Can't skip file transfer");
		}
		return (TRUE);
	}
	if (fromf >= 0) {		/* read file */
		x = filecopy (fromf,tof);
		(void) close (fromf);
		(void) close (tof);
		if (x < 0) {
			notify ("SUP: Error in copying %s to %s\n",from,to);
			if (istemp)  (void) unlink (tname);
			lockout (FALSE);
			return (TRUE);
		}
	} else {			/* read network */
#if	CMUCS
		if (!rpauseflag) {
			x = prereadcount (&fsize);
			if (x != SCMOK) {
				if (istemp)  (void) unlink (tname);
				lockout (FALSE);
				x = readskip ();
				if (x != SCMOK)
					goaway ("Can't skip file transfer");
				goaway ("Error in server space check");
				logquit (1,"Error in server space check");
			}
			errno = 0;
			if (ioctl (tof,FIOCFSPARAM,(char *)&fsp) < 0 &&
			    errno != EINVAL) {
				if (istemp)  (void) unlink (tname);
				lockout (FALSE);
				x = readskip ();
				if (x != SCMOK)
					goaway ("Can't skip file transfer");
				goaway ("Error in disk space check");
				logquit (1,"Error in disk space check");
			}
			if (errno == 0) {
				fsize = (fsize + 1023) / 1024;
				x = fsp.fsp_size * MAX (fsp.fsp_minfree,1) / 100;
				fsp.fsp_free -= x;
				if (fsize > MAX (fsp.fsp_free,0)) {
					if (istemp)  (void) unlink (tname);
					lockout (FALSE);
					x = readskip ();
					if (x != SCMOK)
						goaway ("Can't skip file transfer");
					goaway ("No disk space for file %s", to);
					logquit (1,"No disk space for file %s",to);
				}
			}
		}
#endif	CMUCS
		x = readfile (tof);
		(void) close (tof);
		if (x != SCMOK) {
			if (istemp)  (void) unlink (tname);
			lockout (FALSE);
			goaway ("Error in receiving %s\n",to);
		}
	}
	if (!istemp) {			/* no temp file used */
		lockout (FALSE);
		return (FALSE);
	}
	/* move to destination */
	if (rename (tname,to) == 0) {
		(void) unlink (tname);
		lockout (FALSE);
		return (FALSE);
	}
	fromf = open (tname,O_RDONLY,0);
	if (fromf < 0) {
		notify ("SUP: Error in moving temp file to %s: %s\n",
			to,errmsg (-1));
		(void) unlink (tname);
		lockout (FALSE);
		return (TRUE);
	}
	tof = open (to,(O_WRONLY|O_CREAT|O_TRUNC),0600);
	if (tof < 0) {
		(void) close (fromf);
		notify ("SUP: Can't create %s from temp file: %s\n",
			to,errmsg (-1));
		(void) unlink (tname);
		lockout (FALSE);
		return (TRUE);
	}
	x = filecopy (fromf,tof);
	(void) close (fromf);
	(void) close (tof);
	(void) unlink (tname);
	lockout (FALSE);
	if (x < 0) {
		notify ("SUP: Error in storing data in %s\n",to);
		return (TRUE);
	}
	return (FALSE);
}

/***  Finish connection with file server ***/

finishup (x)
int x;
{
	char tname[STRINGLENGTH],fname[STRINGLENGTH];
	char relsufix[STRINGLENGTH];
	long tloc;
	FILE *finishfile;		/* record of all filenames */
	int f,finishone();

	if (release)
		(void) sprintf (relsufix,".%s",release);
	else relsufix[0] = '\0';

	dontjump = TRUE;		/* once here, no more longjmp */
	(void) netcrypt ((char *)NULL);
	if (protver < 6) {
		/* done with server */
		if (x == SCMOK)
			goaway ((char *)NULL);
		(void) requestend ();
	}
	tloc = time ((long *)NULL);
	if (x != SCMOK) {
		notify ("SUP: Upgrade of %s aborted at %s",
			collname,ctime (&tloc));
		Tfree (&lastT);
		if (protver < 6)  return;
		/* if we've not been blown off, make sure he is! */
		if (x != SCMEOF)
			goaway ("Aborted");
		(void) requestend ();
		return;
	}
	if (thisC->Cnogood) {
		notify ("SUP: Upgrade of %s completed with errors at %s",
			collname,ctime (&tloc));
		notify ("SUP: Upgrade time will not be updated\n");
		Tfree (&lastT);
		if (protver < 6)  return;
		done (FDONEUSRERROR,"Completed with errors");
		(void) requestend ();
		return;
	}
	if (thisC->Cprefix)  (void) chdir (thisC->Cbase);
	vnotify ("SUP Upgrade of %s completed at %s",collname,ctime (&tloc));
	if (thisC->Cflags&CFLIST) {
		Tfree (&lastT);
		if (protver < 6)  return;
		done (FDONEDONTLOG,"List only");
		(void) requestend ();
		return;
	}

	(void) sprintf (fname,FILEWHEN,collname,relsufix);
	if (establishdir (fname)) {
		notify ("SUP: Can't create directory for upgrade timestamp\n");
		Tfree (&lastT);
		if (protver < 6)  return;
		done (FDONEUSRERROR,"Couldn't timestamp");
		(void) requestend ();
		return;
	}
	f = open (fname,(O_WRONLY|O_CREAT|O_TRUNC),0644);
	if (f < 0) {
		notify ("SUP: Can't record current time in %s: %s\n",
			fname,errmsg (-1));
		Tfree (&lastT);
		if (protver < 6)  return;
		done (FDONEUSRERROR,"Couldn't timestamp");
		(void) requestend ();
		return;
	}
	(void) write (f,(char *)&scantime,sizeof(int));
	(void) close (f);
	if (protver >= 6) {
		/* At this point we have let the server go */
		/* "I'm sorry, we've had to let you go" */
		done (FDONESUCCESS,"Success");
		(void) requestend ();
	}
	(void) sprintf (tname,FILELASTTEMP,collname);
	finishfile = fopen (tname,"w");
	if (finishfile == NULL) {
		notify ("SUP: Can't record list of all files in %s\n",tname);
		Tfree (&lastT);
		return;
	}
	(void) Tprocess (lastT,finishone,finishfile);
	(void) fclose (finishfile);
	(void) sprintf (fname,FILELAST,collname,relsufix);
	if (rename (tname,fname) < 0)
		notify ("SUP: Can't change %s to %s\n",tname,fname);
	(void) unlink (tname);
	Tfree (&lastT);
}

finishone (t,finishfile)
TREE *t;
FILE **finishfile;
{
	if ((thisC->Cflags&CFDELETE) == 0 || (t->Tflags&FUPDATE))
		fprintf (*finishfile,"%s\n",t->Tname);
	return (SCMOK);
}

/* VARARGS2 */
done (value,fmt,va_alist)
int value;
char *fmt;
va_dcl
{
	char buf[STRINGLENGTH];

	(void) netcrypt ((char *)NULL);
	if (fmt) {
		va_list ap;

		va_start(ap);
		vsnprintf(buf, sizeof(buf), fmt, ap);
		va_end(ap);
	}
	if (protver < 6) {
		if (goawayreason)
			free (goawayreason);
		goawayreason = (fmt) ? salloc (buf) : (char *)NULL;
		(void) msggoaway ();
	}
	else {
		doneack = value;
		donereason = (fmt) ? buf : (char *)NULL;
		(void) msgdone ();
	}
	if (!dontjump)
		longjmp (sjbuf,TRUE);
}

/* VARARGS1 */
goaway (fmt,va_alist)
register char *fmt;
va_dcl
{
	char buf[STRINGLENGTH];

	(void) netcrypt ((char *)NULL);
	if (fmt) {
		va_list ap;

		va_start(ap);
		vsnprintf(buf, sizeof(buf), fmt, ap);
		va_end(ap);
		goawayreason = buf;
	} else
		goawayreason = NULL;
	(void) msggoaway ();
	if (fmt)
		if (thisC)
			notify ("SUP: %s\n",buf);
		else
			printf ("SUP: %s\n",buf);
	if (!dontjump)
		longjmp (sjbuf,TRUE);
}
