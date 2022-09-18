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
 * supfilesrv -- SUP File Server
 *
 * Usage:  supfilesrv [-l] [-P] [-N]
 *	-l	"live" -- don't fork daemon
 *	-P	"debug ports" -- use debugging network ports
 *	-N	"debug network" -- print debugging messages for network i/o
 *
 **********************************************************************
 * HISTORY
 * 20-Sep-90 Mary R. Thompson (mrt) Carnegie Mellon
 *	Added Bob's changes to always use sprintf as void and to get
 *	return value from parameter.
 *
 * $Log:	supfilesrv.c,v $
 * Revision 1.17  90/05/07  09:31:13  dlc
 * 	Sigh, some more fixes to the new "crypt" file handling code.  First,
 * 	just because the "crypt" file is in a local file system does not mean
 * 	it can be trusted.  We have to check for hard links to root owned
 * 	files whose contents could be interpretted as a crypt key.  For
 * 	checking this fact, the new routine stat_info_ok() was added.  This
 * 	routine also makes other sanity checks, such as owner only permission,
 * 	the file is a regular file, etc.  Also, even if the uid/gid of th
 * 	"crypt" file is not going to be used, still use its contents in order
 * 	to cause fewer surprises to people supping out of a shared file system
 * 	such as AFS.
 * 	[90/05/07            dlc]
 * 
 * Revision 1.16  90/04/29  04:21:08  dlc
 * 	Fixed logic bug in docrypt() which would not get the stat information
 * 	from the crypt file if the crypt key had already been set from a
 * 	"host" file.
 * 	[90/04/29            dlc]
 * 
 * Revision 1.15  90/04/18  19:51:27  dlc
 * 	Added the new routines local_file(), link_nofollow() for use in
 * 	dectecting whether a file is located in a local file system.  These
 * 	routines probably should have been in another module, but only
 * 	supfilesrv needs to do the check and none of its other modules seemed
 * 	appropriate.  Note, the implementation should be changed once we have
 * 	direct kernel support, for example the fstatfs(2) system call, for
 * 	detecting the type of file system a file resides.  Also, I changed
 * 	the routines which read the crosspatch crypt file or collection crypt
 * 	file to save the uid and gid from the stat information obtained via
 * 	the local_file() call (when the file is local) at the same time the
 * 	crypt key is read.  This change disallows non-local files for the
 * 	crypt key to plug a security hole involving the usage of the uid/gid
 * 	of the crypt file to define who the the file server should run as.  If
 * 	the saved uid/gid are both valid, then the server will set its uid/gid
 * 	to these values.
 * 	[90/04/18            dlc]
 * 
 * Revision 1.14  89/08/23  14:56:15  gm0w
 * 	Changed msgf routines to msg routines.
 * 	[89/08/23            gm0w]
 * 
 * Revision 1.13  89/08/03  19:57:33  mja
 * 	Remove setaid() call.
 * 
 * Revision 1.12  89/08/03  19:49:24  mja
 * 	Updated to use v*printf() in place of _doprnt().
 * 	[89/04/19            mja]
 * 
 * 11-Sep-88  Glenn Marcy (gm0w) at Carnegie-Mellon University
 *	Added code to record release name in logfile.
 *
 * 18-Mar-88  Glenn Marcy (gm0w) at Carnegie-Mellon University
 *	Added host=<hostfile> support to releases file. [V7.12]
 *
 * 27-Dec-87  Glenn Marcy (gm0w) at Carnegie-Mellon University
 *	Added crosspatch support.  Created docrypt() routine for crypt
 *	test message.
 *
 * 09-Sep-87  Glenn Marcy (gm0w) at Carnegie-Mellon University
 *	Removed common information logging code, the quiet switch, and
 *	moved samehost() check to after device/inode check.
 *
 * 28-Jun-87  Glenn Marcy (gm0w) at Carnegie-Mellon University
 *	Added code for "release" support. [V5.11]
 *
 * 26-May-87  Doug Philips (dwp) at Carnegie-Mellon University
 *	Added code to record final status of client in logfile. [V5.10]
 *
 * 22-May-87  Chriss Stephens (chriss) at Carnegie Mellon University
 *	Mergered divergent CS and ECE versions. [V5.9a]
 *
 * 20-May-87  Glenn Marcy (gm0w) at Carnegie-Mellon University
 *	Removed support for version 3 of SUP protocol.  Added changes
 *	to make lint happy.  Added calls to new logging routines. [V5.9]
 *
 * 31-Mar-87  Dan Nydick (dan) at Carnegie-Mellon University
 *	Fixed so no password check is done when crypts are used.
 *
 * 25-Nov-86  Rudy Nedved (ern) at Carnegie-Mellon University
 *	Set F_APPEND fcntl in logging to increase the chance
 *	that the log entry from this incarnation of the file
 *	server will not be lost by another incarnation. [V5.8]
 *
 * 20-Oct-86  Dan Nydick (dan) at Carnegie-Mellon University
 *	Changed not to call okmumbles when not compiled with CMUCS.
 *
 * 04-Aug-86  Glenn Marcy (gm0w) at Carnegie-Mellon University
 *	Added code to increment scmdebug as more -N flags are
 *	added. [V5.7]
 *
 * 25-May-86  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Renamed local variable in main program from "sigmask" to
 *	"signalmask" to avoid name conflict with 4.3BSD identifier.
 *	Conditionally compile in calls to CMU routines, "setaid" and
 *	"logaccess". [V5.6]
 *
 * 21-Jan-86  Glenn Marcy (gm0w) at Carnegie-Mellon University
 *	Changed supfilesrv to use the crypt file owner and group for
 *	access purposes, rather than the directory containing the crypt
 *	file. [V5.5]
 *
 * 07-Jan-86  Glenn Marcy (gm0w) at Carnegie-Mellon University
 *	Added code to keep logfiles in repository collection directory.
 *	Added code for locking collections. [V5.4]
 *
 * 05-Jan-86  Glenn Marcy (gm0w) at Carnegie-Mellon University
 *	Added code to support new FSETUPBUSY return.  Now accepts all
 *	connections and tells any clients after the 8th that the
 *	fileserver is busy.  New clients will retry again later. [V5.3]
 *
 * 29-Dec-85  Glenn Marcy (gm0w) at Carnegie-Mellon University
 *	Major rewrite for protocol version 4. [V4.2]
 *
 * 12-Dec-85  Glenn Marcy (gm0w) at Carnegie-Mellon University
 *	Fixed close of crypt file to use file pointer as argument
 *	instead of string pointer.
 *
 * 24-Nov-85  Glenn Marcy (gm0w) at Carnegie-Mellon University
 *	Allow "!hostname" lines and comments in collection "host" file.
 *
 * 13-Nov-85  Glenn Marcy (gm0w) at Carnegie-Mellon University
 *	Don't use access() on symbolic links since they may not point to
 *	an existing file.
 *
 * 22-Oct-85  Glenn Marcy (gm0w) at Carnegie-Mellon University
 *	Added code to restrict file server availability to when it has
 *	less than or equal to eight children.
 *
 * 22-Sep-85  Glenn Marcy (gm0w) at Carnegie-Mellon University
 *	Merged 4.1 and 4.2 versions together.
 *
 * 04-Jun-85  Steven Shafer (sas) at Carnegie-Mellon University
 *	Created for 4.2 BSD.
 *
 **********************************************************************
 */

#include <libc.h>
#include <sys/param.h>
#include <c.h>
#include <signal.h>
#include <errno.h>
#include <setjmp.h>
#include <pwd.h>
#include <grp.h>
#include <varargs.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <sys/dir.h>
#if	CMUCS
#include <acc.h>
#include <sys/ttyloc.h>
#include <access.h>
#include <sys/table.h>
#include <sys/viceioctl.h>
#else	CMUCS
#define ACCESS_CODE_OK		0
#define ACCESS_CODE_BADPASSWORD (-2)
#endif  CMUCS
#include "sup.h"
#define MSGFILE
#include "supmsg.h"

extern int errno;
long time ();
#if	CMUCS
uid_t getuid ();
#endif	CMUCS

/*
 * These are used to save the stat information from the crosspatch crypt
 * file or collection crypt file at the time it is opened for the crypt
 * key and it is verified to be a local file.
 */
int runas_uid = -1;
int runas_gid = -1;

#define PGMVERSION 12

/*************************
 ***    M A C R O S    ***
 *************************/

#define HASHBITS 8
#define HASHSIZE (1<<HASHBITS)
#define HASHMASK (HASHSIZE-1)
#define HASHFUNC(x,y) ((x)&HASHMASK)

/*******************************************
 ***    D A T A   S T R U C T U R E S    ***
 *******************************************/

struct hashstruct {			/* hash table for number lists */
	int Hnum1;			/* numeric keys */
	int Hnum2;
	char *Hname;			/* string value */
	TREE *Htree;			/* TREE value */
	struct hashstruct *Hnext;
};
typedef struct hashstruct HASH;

/*********************************************
 ***    G L O B A L   V A R I A B L E S    ***
 *********************************************/

char program[] = "supfilesrv";		/* program name for SCM messages */
int progpid = -1;			/* and process id */

jmp_buf sjbuf;				/* jump location for network errors */
TREELIST *listTL;			/* list of trees to upgrade */

int live;				/* -l flag */
int dbgportsq;				/* -P flag */
extern int scmdebug;			/* -N flag */
extern int netfile;

char *clienthost;			/* host name of client */
int nchildren;				/* number of children that exist */
char *prefix;				/* collection pathname prefix */
char *release;				/* collection release name */
char *cryptkey;				/* encryption key if non-null */
int lockfd;				/* descriptor of lock file */

/* global variables for scan functions */
int trace = FALSE;			/* directory scan trace */

HASH *uidH[HASHSIZE];			/* for uid and gid lookup */
HASH *gidH[HASHSIZE];
HASH *inodeH[HASHSIZE];			/* for inode lookup for linked file check */

char *fmttime ();			/* time format routine */

/*************************************
 ***    M A I N   R O U T I N E    ***
 *************************************/

main (argc,argv)
int argc;
char **argv;
{
	register int x,pid,signalmask;
	struct sigvec chldvec,ignvec,oldvec;
	int chldsig ();
	long tloc;

	/* initialize global variables */
	pgmversion = PGMVERSION;	/* export version number */
	server = TRUE;			/* export that we're not a server */
	collname = NULL;		/* no current collection yet */

	init (argc,argv);		/* process arguments */
	logopen ("supfile");
	tloc = time ((long *)NULL);
	loginfo ("SUP File Server Version %d.%d (%s) starting at %s",
		PROTOVERSION,PGMVERSION,scmversion,fmttime (tloc));
	if (live) {
		x = service ();
		if (x != SCMOK)
			logquit (1,"Can't connect to network");
		answer ();
		(void) serviceend ();
		exit (0);
	}
	ignvec.sv_handler = SIG_IGN;
	ignvec.sv_onstack = 0;
	ignvec.sv_mask = 0;
	(void) sigvec (SIGHUP,&ignvec,&oldvec);
	(void) sigvec (SIGINT,&ignvec,&oldvec);
	(void) sigvec (SIGPIPE,&ignvec,&oldvec);
	chldvec.sv_handler = chldsig;
	chldvec.sv_mask = 0;
	chldvec.sv_onstack = 0;
	(void) sigvec (SIGCHLD,&chldvec,&oldvec);
	nchildren = 0;
	for (;;) {
		x = service ();
		if (x != SCMOK)
			logquit (1,"Error in establishing network connection");
		signalmask = sigblock(sigmask(SIGCHLD));
		if ((pid = fork()) == 0) { /* server process */
			(void) serviceprep ();
			answer ();
			(void) serviceend ();
			exit (0);
		}
		(void) servicekill ();	/* parent */
		if (pid > 0) nchildren++;
		(void) sigsetmask(signalmask);
	}
}

/*
 * Child status signal handler
 */

chldsig()
{
	union wait w;

	while (wait3(&w, WNOHANG, (struct rusage *)0) > 0) {
		if (nchildren) nchildren--;
	}
}

/*****************************************
 ***    I N I T I A L I Z A T I O N    ***
 *****************************************/

usage ()
{
	quit (1,"Usage: supfilesrv [ -l | -P | -N | -H <host> <user> <cryptfile> <supargs> ]\n");
}

init (argc,argv)
int argc;
char **argv;
{
	register int i;
	register int x;
	char *clienthost,*clientuser;
	char *p,*q;
	char buf[STRINGLENGTH];
	register FILE *f;

	live = FALSE;
	dbgportsq = FALSE;
	scmdebug = 0;
	clienthost = NULL;
	clientuser = NULL;
	if (--argc < 0)
		usage ();
	argv++;
	while (clienthost == NULL && argc > 0 && argv[0][0] == '-') {
		switch (argv[0][1]) {
		case 'l':
			live = TRUE;
			break;
		case 'P':
			dbgportsq = TRUE;
			break;
		case 'N':
			scmdebug++;
			break;
		case 'H':
			if (--argc < 3)
				quit (1,"Missing args to -H\n");
			argv++;
			clienthost = argv[0];
			clientuser = argv[1];
			cryptkey = argv[2];
			argc -= 2;
			argv += 2;
			break;
		default:
			fprintf (stderr,"Unknown flag %s ignored\n",argv[0]);
			break;
		}
		--argc;
		argv++;
	}
	if (clienthost == NULL) {
		if (argc != 0)
			usage ();
		x = servicesetup (dbgportsq ? DEBUGFPORT : FILEPORT);
		if (x != SCMOK)
			quit (1,"Error in network setup");
		for (i = 0; i < HASHSIZE; i++)
			uidH[i] = gidH[i] = inodeH[i] = NULL;
		return;
	}
	server = FALSE;
	if (argc < 1)
		usage ();
	f = fopen (cryptkey,"r");
	if (f == NULL)
		quit (1,"Unable to open cryptfile %s\n",cryptkey);
	if (p = fgets (buf,STRINGLENGTH,f)) {
		if (q = index (p,'\n'))  *q = '\0';
		if (*p == '\0')
			quit (1,"No cryptkey found in %s\n",cryptkey);
		cryptkey = salloc (buf);
	}
	(void) fclose (f);
	x = request (dbgportsq ? DEBUGFPORT : FILEPORT,clienthost,TRUE);
	if (x != SCMOK)
		quit (1,"Unable to connect to host %s\n",clienthost);
	x = msgsignon ();
	if (x != SCMOK)
		quit (1,"Error sending signon request to fileserver\n");
	x = msgsignonack ();
	if (x != SCMOK)
		quit (1,"Error reading signon reply from fileserver\n");
	printf ("SUP Fileserver %d.%d (%s) %d on %s\n",
		protver,pgmver,scmver,fspid,remotehost());
	free (scmver);
	scmver = NULL;
	if (protver < 7)
		quit (1,"Remote fileserver does not implement reverse sup\n");
	xpatch = TRUE;
	xuser = clientuser;
	x = msgsetup ();
	if (x != SCMOK)
		quit (1,"Error sending setup request to fileserver\n");
	x = msgsetupack ();
	if (x != SCMOK)
		quit (1,"Error reading setup reply from fileserver\n");
	switch (setupack) {
	case FSETUPOK:
		break;
	case FSETUPSAME:
		quit (1,"User %s not found on remote client\n",xuser);
	case FSETUPHOST:
		quit (1,"This host has no permission to reverse sup\n");
	default:
		quit (1,"Unrecognized file server setup status %d\n",setupack);
	}
	(void) netcrypt (cryptkey);
	crypttest = CRYPTTEST;
	x = msgcrypt ();
	if (x != SCMOK)
		quit (1,"Error sending encryption test request\n");
	x = msgcryptok ();
	if (x == SCMEOF)
		quit (1,"Data encryption test failed\n");
	if (x != SCMOK)
		quit (1,"Error reading encryption test reply\n");
	logcrypt = CRYPTTEST;
	loguser = NULL;
	logpswd = NULL;
	(void) netcrypt (PSWDCRYPT);	/* encrypt password data */
	x = msglogin ();
	(void) netcrypt ((char *)NULL);	/* turn off encryption */
	if (x != SCMOK)
		quit (1,"Error sending login request to file server\n");
	x = msglogack ();
	if (x != SCMOK)
		quit (1,"Error reading login reply from file server\n");
	if (logack == FLOGNG)
		quit (1,"%s\nImproper login to %s account\n",logerror,xuser);
	xargc = argc;
	xargv = argv;
	x = msgxpatch ();
	if (x != SCMOK)
		quit (1,"Error sending crosspatch request\n");
    	crosspatch ();
	exit (0);
}

/*****************************************
 ***    A N S W E R   R E Q U E S T    ***
 *****************************************/

answer ()
{
	long starttime;
	register int x;

	progpid = fspid = getpid ();
	collname = NULL;
	basedir = NULL;
	prefix = NULL;
	release = NULL;
	goawayreason = NULL;
	donereason = NULL;
	lockfd = -1;
	starttime = time ((long *)NULL);
	if (!setjmp (sjbuf)) {
		signon ();
		setup ();
		docrypt ();
		login ();
		if (xpatch) {
			int fd;

			x = msgxpatch ();
			if (x != SCMOK)
				exit (0);
			xargv[0] = "/usr/mach/bin/sup";
			xargv[1] = "-X";
			xargv[xargc] = (char *)NULL;
			dup2 (netfile,0);
			dup2 (netfile,1);
			dup2 (netfile,2);
			fd = getdtablesize ();
			while (--fd > 2)
				close (fd);
			execv (xargv[0],xargv);
			exit (0);
		}
		listfiles ();
		sendfiles ();
	}
	finishup (starttime);
	if (collname)  free (collname);
	if (basedir)  free (basedir);
	if (prefix)  free (prefix);
	if (release)  free (release);
	if (goawayreason) {
		if (donereason == goawayreason)
			donereason = NULL;
		free (goawayreason);
	}
	if (donereason)  free (donereason);
	if (lockfd >= 0)  (void) close (lockfd);
	endpwent ();
	(void) endgrent ();
#if	CMUCS
	endacent ();
#endif	CMUCS
	Hfree (uidH);
	Hfree (gidH);
	Hfree (inodeH);
}

/*****************************************
 ***    S I G N   O N   C L I E N T    ***
 *****************************************/

signon ()
{
	register int x;

	xpatch = FALSE;
	x = msgsignon ();
	if (x != SCMOK)  goaway ("Error reading signon request from client");
	x = msgsignonack ();
	if (x != SCMOK)  goaway ("Error sending signon reply to client");
	free (scmver);
	scmver = NULL;
}

/*****************************************************************
 ***    E X C H A N G E   S E T U P   I N F O R M A T I O N    ***
 *****************************************************************/

setup ()
{
	register int x;
	char *p,*q;
	char buf[STRINGLENGTH];
	register FILE *f;
	struct stat sbuf;
	register TREELIST *tl;

	x = msgsetup ();
	if (x != SCMOK)  goaway ("Error reading setup request from client");
	if (protver < 4) {
		setupack = FSETUPOLD;
		(void) msgsetupack ();
		if (protver >= 6)  longjmp (sjbuf,TRUE);
		goaway ("Sup client using obsolete version of protocol");
	}
	if (xpatch) {
		register struct passwd *pw;
		struct stat fsbuf;
		extern int link_nofollow(), local_file();

		if ((pw = getpwnam (xuser)) == NULL) {
			setupack = FSETUPSAME;
			(void) msgsetupack ();
			if (protver >= 6)  longjmp (sjbuf,TRUE);
			goaway ("User not found");
		}
		(void) free (xuser);
		xuser = salloc (pw->pw_dir);

		/* check crosspatch host access file */
		cryptkey = NULL;
		(void) sprintf (buf,FILEXPATCH,xuser);

		/* Turn off link following */
		if (link_nofollow(1) >= 0) {
			/* Get the stat info before open */
			if (stat(buf, &sbuf) < 0)
				(void) bzero((char *)&sbuf, sizeof(sbuf));
			f = fopen (buf,"r");
		} else {
			(void) bzero((char *)&sbuf, sizeof(sbuf));
			f = NULL;
		}

		if (f) {
			int hostok = FALSE;
			int local = local_file(fileno(f), &fsbuf);
			int statok = stat_info_ok(&sbuf, &fsbuf);

			/* Use the file contents, regardless whether the
			   file can be trusted for setting the uid/gid */
			while (p = fgets (buf,STRINGLENGTH,f)) {
				q = index (p,'\n');
				if (q)  *q = 0;
				if (index ("#;:",*p))  continue;
				q = nxtarg (&p," \t");
				if (*p == '\0')  continue;
				if (matchhost(q)) {
					cryptkey = salloc (p);
					hostok = TRUE;
					if (local > 0 && statok) {
						runas_uid = (short)sbuf.st_uid;
						runas_gid = (short)sbuf.st_gid;
					}
					break;
				}
			}

			(void) fclose (f);

			/* Restore link following */
			if (link_nofollow(0) < 0)
				goaway ("Restore link following");
			if (!hostok) {
				setupack = FSETUPHOST;
				(void) msgsetupack ();
				if (protver >= 6)  longjmp (sjbuf,TRUE);
				goaway ("Host not on access list");
			}
		}

		/* Restore link following */
		if (link_nofollow(0) < 0)
			goaway ("Restore link following");
		setupack = FSETUPOK;
		x = msgsetupack ();
		if (x != SCMOK)
			goaway ("Error sending setup reply to client");
		return;
	}
	if (release == NULL)
		release = salloc (DEFRELEASE);
	if (basedir == NULL || *basedir == '\0') {
		basedir = NULL;
		(void) sprintf (buf,FILEDIRS,DEFDIR);
		f = fopen (buf,"r");
		if (f) {
			while (p = fgets (buf,STRINGLENGTH,f)) {
				q = index (p,'\n');
				if (q)  *q = 0;
				if (index ("#;:",*p))  continue;
				q = nxtarg (&p," \t=");
				if (strcmp(q,collname) == 0) {
					basedir = skipover(p," \t=");
					basedir = salloc (basedir);
					break;
				}
			}
			(void) fclose (f);
		}
		if (basedir == NULL) {
			(void) sprintf (buf,FILEBASEDEFAULT,collname);
			basedir = salloc(buf);
		}
	}
	if (chdir (basedir) < 0)
		goaway ("Can't chdir to base directory %s",basedir);
	(void) sprintf (buf,FILEPREFIX,collname);
	f = fopen (buf,"r");
	if (f) {
		while (p = fgets (buf,STRINGLENGTH,f)) {
			q = index (p,'\n');
			if (q)  *q = 0;
			if (index ("#;:",*p))  continue;
			prefix = salloc(p);
			if (chdir (prefix) < 0)
				goaway ("Can't chdir to %s from base directory %s",
					prefix,basedir);
			break;
		}
		(void) fclose (f);
	}
	x = stat (".",&sbuf);
	if (prefix)  (void) chdir (basedir);
	if (x < 0)
		goaway ("Can't stat base/prefix directory");
	if (nchildren >= MAXCHILDREN) {
		setupack = FSETUPBUSY;
		(void) msgsetupack ();
		if (protver >= 6)  longjmp (sjbuf,TRUE);
		goaway ("Sup client told to try again later");
	}
	if (sbuf.st_dev == basedev && sbuf.st_ino == baseino && samehost()) {
		setupack = FSETUPSAME;
		(void) msgsetupack ();
		if (protver >= 6)  longjmp (sjbuf,TRUE);
		goaway ("Attempt to upgrade to same directory on same host");
	}
	/* obtain release information */
	if (!getrelease (release)) {
		setupack = FSETUPRELEASE;
		(void) msgsetupack ();
		if (protver >= 6)  longjmp (sjbuf,TRUE);
		goaway ("Invalid release information");
	}
	/* check host access file */
	cryptkey = NULL;
	for (tl = listTL; tl != NULL; tl = tl->TLnext) {
		char *h;
		if ((h = tl->TLhost) == NULL)
			h = FILEHOSTDEF;
		(void) sprintf (buf,FILEHOST,collname,h);
		f = fopen (buf,"r");
		if (f) {
			int hostok = FALSE;
			while (p = fgets (buf,STRINGLENGTH,f)) {
				int not;
				q = index (p,'\n');
				if (q)  *q = 0;
				if (index ("#;:",*p))  continue;
				q = nxtarg (&p," \t");
				if ((not = (*q == '!')) && *++q == '\0')
					q = nxtarg (&p," \t");
				hostok = (not == (matchhost(q) == 0));
				if (hostok) {
					if (*p)  cryptkey = salloc (p);
					break;
				}
			}
			(void) fclose (f);
			if (!hostok) {
				setupack = FSETUPHOST;
				(void) msgsetupack ();
				if (protver >= 6)  longjmp (sjbuf,TRUE);
				goaway ("Host not on access list for %s",
					collname);
			}
		}
	}
	/* try to lock collection */
	(void) sprintf (buf,FILELOCK,collname);
	x = open (buf,O_RDONLY,0);
	if (x >= 0) {
		if (flock (x,(LOCK_SH|LOCK_NB)) < 0) {
			(void) close (x);
			if (errno != EWOULDBLOCK)
				goaway ("Can't lock collection %s",collname);
			setupack = FSETUPBUSY;
			(void) msgsetupack ();
			if (protver >= 6)  longjmp (sjbuf,TRUE);
			goaway ("Sup client told to wait for lock");
		}
		lockfd = x;
	}
	setupack = FSETUPOK;
	x = msgsetupack ();
	if (x != SCMOK)  goaway ("Error sending setup reply to client");
}

/** Test data encryption **/
docrypt ()
{
	register int x;
	char *p,*q;
	char buf[STRINGLENGTH];
	register FILE *f;
	struct stat sbuf, fsbuf;
	extern int  link_nofollow(), local_file();

	if (!xpatch) {
		(void) sprintf (buf,FILECRYPT,collname);

		/* Turn off link following */
		if (link_nofollow(1) >= 0) {
			/* Get stat info before open */
			if (stat(buf, &sbuf) < 0)
				(void)bzero((char *)&sbuf, sizeof(sbuf));
			f = fopen (buf,"r");
		} else {
			(void)bzero((char *)&sbuf, sizeof(sbuf));
			f = NULL;
		}

		if (f) {
			int statok;

			x = local_file(fileno(f), &fsbuf);
			statok = stat_info_ok(&sbuf, &fsbuf);
			
			/* Use the file contents regardless whether the file
			   can be trusted for setting uid/gid. */
			if (cryptkey == NULL &&
			    (p = fgets (buf,STRINGLENGTH,f))) {
				if (q = index (p,'\n'))  *q = '\0';
				if (*p)  cryptkey = salloc (buf);
			}
			if (x > 0 && statok) {
				runas_uid = (short)sbuf.st_uid;
				runas_gid = (short)sbuf.st_gid;
			}
			(void) fclose (f);
		}
		/* Restore link following */
		if (link_nofollow(0) < 0)
			goaway ("Restore link following");
	}
	(void) netcrypt (cryptkey);
	x = msgcrypt ();
	if (x != SCMOK)
		goaway ("Error reading encryption test request from client");
	(void) netcrypt ((char *)NULL);
	if (strcmp(crypttest,CRYPTTEST) != 0)
		goaway ("Client not encrypting data properly", crypttest);
	free (crypttest);
	crypttest = NULL;
	x = msgcryptok ();
	if (x != SCMOK)
		goaway ("Error sending encryption test reply to client");
}

/***************************************************************
 ***    C O N N E C T   T O   P R O P E R   A C C O U N T    ***
 ***************************************************************/

login ()
{
	char *changeuid ();
	register int x,fileuid,filegid;
	char buf[STRINGLENGTH];

	(void) netcrypt (PSWDCRYPT);	/* encrypt acct name and password */
	x = msglogin ();
	(void) netcrypt ((char *)NULL); /* turn off encryption */
	if (x != SCMOK)  goaway ("Error reading login request from client");
	if (strcmp(logcrypt,CRYPTTEST) != 0) {
		logack = FLOGNG;
		logerror = "Improper login encryption";
		(void) msglogack ();
		goaway ("Client not encrypting login information properly");
	}
	free (logcrypt);
	logcrypt = NULL;
	if (loguser == NULL) {
		if (cryptkey) {
			if (runas_uid >= 0 && runas_gid >= 0) {
				fileuid = runas_uid;
				filegid = runas_gid;
				loguser = NULL;
			} else
				loguser = salloc (DEFUSER);
		} else
			loguser = salloc (DEFUSER);
	}
	if ((logerror = changeuid (loguser,logpswd,fileuid,filegid)) != NULL) {
		logack = FLOGNG;
		(void) msglogack ();
		if (protver >= 6)  longjmp (sjbuf,TRUE);
		goaway ("Client denied login access");
	}
	if (loguser)  free (loguser);
	if (logpswd)  free (logpswd);
	logack = FLOGOK;
	x = msglogack ();
	if (x != SCMOK)  goaway ("Error sending login reply to client");
	if (!xpatch)
		(void) netcrypt (cryptkey); /* restore desired encryption */
	free (cryptkey);
	cryptkey = NULL;
}

/*****************************************
 ***    M A K E   N A M E   L I S T    ***
 *****************************************/

listfiles ()
{
	int denyone();
	register int x;

	refuseT = NULL;
	x = msgrefuse ();
	if (x != SCMOK)  goaway ("Error reading refuse list from client");
	getscanlists ();
	Tfree (&refuseT);
	x = msglist ();
	if (x != SCMOK)  goaway ("Error sending file list to client");
	Tfree (&listT);
	listT = NULL;
	needT = NULL;
	x = msgneed ();
	if (x != SCMOK)
		goaway ("Error reading needed files list from client");
	denyT = NULL;
	(void) Tprocess (needT,denyone);
	Tfree (&needT);
	x = msgdeny ();
	if (x != SCMOK)  goaway ("Error sending denied files list to client");
	Tfree (&denyT);
}

denyone (t)
register TREE *t;
{
	register TREELIST *tl;
	register char *name = t->Tname;
	register int update = (t->Tflags&FUPDATE) != 0;
	struct stat sbuf;
	register TREE *tlink;
	TREE *linkcheck ();
	char slinkname[STRINGLENGTH];
	register int x;

	for (tl = listTL; tl != NULL; tl = tl->TLnext)
		if ((t = Tsearch (tl->TLtree,name)) != NULL)
			break;
	if (t == NULL) {
		(void) Tinsert (&denyT,name,FALSE);
		return (SCMOK);
	}
	cdprefix (tl->TLprefix);
	if ((t->Tmode&S_IFMT) == S_IFLNK)
		x = lstat(name,&sbuf);
	else
		x = stat(name,&sbuf);
	if (x < 0 || (sbuf.st_mode&S_IFMT) != (t->Tmode&S_IFMT)) {
		(void) Tinsert (&denyT,name,FALSE);
		return (SCMOK);
	}
	switch (t->Tmode&S_IFMT) {
	case S_IFLNK:
		if ((x = readlink (name,slinkname,STRINGLENGTH)) <= 0) {
			(void) Tinsert (&denyT,name,FALSE);
			return (SCMOK);
		}
		slinkname[x] = '\0';
		(void) Tinsert (&t->Tlink,slinkname,FALSE);
		break;
	case S_IFREG:
		if (sbuf.st_nlink > 1 &&
		    (tlink = linkcheck (t,(int)sbuf.st_dev,(int)sbuf.st_ino)))
		{
			(void) Tinsert (&tlink->Tlink,name,FALSE);
			return (SCMOK);
		}
		if (update)  t->Tflags |= FUPDATE;
	case S_IFDIR:
		t->Tuid = sbuf.st_uid;
		t->Tgid = sbuf.st_gid;
		break;
	default:
		(void) Tinsert (&denyT,name,FALSE);
		return (SCMOK);
	}
	t->Tflags |= FNEEDED;
	return (SCMOK);
}

/*********************************
 ***    S E N D   F I L E S    ***
 *********************************/

sendfiles ()
{
	int sendone(),senddir(),sendfile();
	register TREELIST *tl;
	register int x;

	/* send all files */
	for (tl = listTL; tl != NULL; tl = tl->TLnext) {
		cdprefix (tl->TLprefix);
		(void) Tprocess (tl->TLtree,sendone);
	}
	/* send directories in reverse order */
	for (tl = listTL; tl != NULL; tl = tl->TLnext) {
		cdprefix (tl->TLprefix);
		(void) Trprocess (tl->TLtree,senddir);
	}
	x = msgsend ();
	if (x != SCMOK)
		goaway ("Error reading receive file request from client");
	upgradeT = NULL;
	x = msgrecv (sendfile,0);
	if (x != SCMOK)
		goaway ("Error sending file to client");
}

sendone (t)
TREE *t;
{
	register int x,fd;
	char *uconvert(),*gconvert();
	int sendfile ();

	if ((t->Tflags&FNEEDED) == 0)	/* only send needed files */
		return (SCMOK);
	if ((t->Tmode&S_IFMT) == S_IFDIR) /* send no directories this pass */
		return (SCMOK);
	x = msgsend ();
	if (x != SCMOK)  goaway ("Error reading receive file request from client");
	upgradeT = t;			/* upgrade file pointer */
	fd = -1;			/* no open file */
	if ((t->Tmode&S_IFMT) == S_IFREG) {
		if (!listonly && (t->Tflags&FUPDATE) == 0) {
			fd = open (t->Tname,O_RDONLY,0);
			if (fd < 0)  t->Tmode = 0;
		}
		if (t->Tmode) {
			t->Tuser = salloc (uconvert (t->Tuid));
			t->Tgroup = salloc (gconvert (t->Tgid));
		}
	}
	x = msgrecv (sendfile,fd);
	if (x != SCMOK)  goaway ("Error sending file to client");
	return (SCMOK);
}

senddir (t)
TREE *t;
{
	register int x;
	char *uconvert(),*gconvert();
	int sendfile ();

	if ((t->Tflags&FNEEDED) == 0)	/* only send needed files */
		return (SCMOK);
	if ((t->Tmode&S_IFMT) != S_IFDIR) /* send only directories this pass */
		return (SCMOK);
	x = msgsend ();
	if (x != SCMOK)  goaway ("Error reading receive file request from client");
	upgradeT = t;			/* upgrade file pointer */
	t->Tuser = salloc (uconvert (t->Tuid));
	t->Tgroup = salloc (gconvert (t->Tgid));
	x = msgrecv (sendfile,0);
	if (x != SCMOK)  goaway ("Error sending file to client");
	return (SCMOK);
}

sendfile (t,fd)
register TREE *t;
int *fd;
{
	register int x;
	if ((t->Tmode&S_IFMT) != S_IFREG || listonly || (t->Tflags&FUPDATE))
		return (SCMOK);
	x = writefile (*fd);
	if (x != SCMOK)  goaway ("Error sending file to client");
	(void) close (*fd);
	return (SCMOK);
}

/*****************************************
 ***    E N D   C O N N E C T I O N    ***
 *****************************************/

finishup (starttime)
long starttime;
{
	register int x = SCMOK;
	char buf[STRINGLENGTH];
	register FILE *f;
	struct stat sbuf;
	long finishtime;
	int flags;
	char *releasename;

	(void) netcrypt ((char *)NULL);
	if (protver < 6) {
		if (goawayreason != NULL)
			free (goawayreason);
		goawayreason = (char *)NULL;
		x = msggoaway();
		doneack = FDONESUCCESS;
		donereason = salloc ("Unknown");
	} else if (goawayreason == (char *)NULL)
		x = msgdone ();
	else {
		doneack = FDONEGOAWAY;
		donereason = goawayreason;
	}
	if (x == SCMEOF || x == SCMERR) {
		doneack = FDONEUSRERROR;
		donereason = salloc ("Premature EOF on network");
	} else if (x != SCMOK) {
		doneack = FDONESRVERROR;
		donereason = salloc ("Unknown SCM code");
	}
	if (doneack == FDONEDONTLOG)
		return;
	if (donereason == NULL)
		donereason = salloc ("No reason");
	if (doneack == FDONESRVERROR || doneack == FDONEUSRERROR)
		logerr ("%s", donereason);
	else if (doneack == FDONEGOAWAY)
		logerr ("GOAWAY: %s",donereason);
	else if (doneack != FDONESUCCESS)
		logerr ("Reason %d:  %s",doneack,donereason);
	goawayreason = donereason;
	cdprefix ((char *)NULL);
	(void) sprintf (buf,FILELOGFILE,collname);
	if (stat (buf,&sbuf) < 0 || (f = fopen (buf,"a")) == NULL)
		return;
	finishtime = time ((long *)NULL);
	if ((flags = fcntl (fileno (f),F_GETFL,0)) != -1) {
		flags |= FAPPEND;
		(void) fcntl (fileno (f),F_SETFL,flags);
	}
	(void) sprintf (buf,"%s ",fmttime (lasttime));
	(void) sprintf (buf,"%s%s ",buf,fmttime (starttime));
	(void) sprintf (buf,"%s%s ",buf,fmttime (finishtime));
	if ((releasename = release) == NULL)
		releasename = "UNKNOWN";
	fprintf (f,"%s%s %s %d %s\n",buf,remotehost (),releasename,
		FDONESUCCESS-doneack,donereason);
	(void) fclose (f);
}

/***************************************************
 ***    H A S H   T A B L E   R O U T I N E S    ***
 ***************************************************/

Hfree (table)
HASH **table;
{
	register HASH *h;
	register int i;
	for (i = 0; i < HASHSIZE; i++)
		while (h = table[i]) {
			table[i] = h->Hnext;
			if (h->Hname)  free (h->Hname);
			free ((char *)h);
		}
}

HASH *Hlookup (table,num1,num2)
HASH **table;
int num1,num2;
{
	register HASH *h;
	register int hno;
	hno = HASHFUNC(num1,num2);
	for (h = table[hno]; h && (h->Hnum1 != num1 || h->Hnum2 != num2); h = h->Hnext);
	return (h);
}

Hinsert (table,num1,num2,name,tree)
HASH **table;
int num1,num2;
char *name;
TREE *tree;
{
	register HASH *h;
	register int hno;
	hno = HASHFUNC(num1,num2);
	h = (HASH *) malloc (sizeof(HASH));
	h->Hnum1 = num1;
	h->Hnum2 = num2;
	h->Hname = name;
	h->Htree = tree;
	h->Hnext = table[hno];
	table[hno] = h;
}

/*********************************************
 ***    U T I L I T Y   R O U T I N E S    ***
 *********************************************/

TREE *linkcheck (t,d,i)
TREE *t;
int d,i;			/* inode # and device # */
{
	register HASH *h;
	h = Hlookup (inodeH,i,d);
	if (h)  return (h->Htree);
	Hinsert (inodeH,i,d,(char *)NULL,t);
	return ((TREE *)NULL);
}

char *uconvert (uid)
int uid;
{
	register struct passwd *pw;
	register char *p;
	register HASH *u;
	u = Hlookup (uidH,uid,0);
	if (u)  return (u->Hname);
	pw = getpwuid (uid);
	if (pw == NULL)  return ("");
	p = salloc (pw->pw_name);
	Hinsert (uidH,uid,0,p,(TREE*)NULL);
	return (p);
}

char *gconvert (gid)
int gid;
{
	register struct group *gr;
	register char *p;
	register HASH *g;
	g = Hlookup (gidH,gid,0);
	if (g)  return (g->Hname);
	gr = getgrgid (gid);
	if (gr == NULL)  return ("");
	p = salloc (gr->gr_name);
	Hinsert (gidH,gid,0,p,(TREE *)NULL);
	return (p);
}

char *changeuid (namep,passwordp,fileuid,filegid)
char *namep,*passwordp;
int fileuid,filegid;
{
	char *okpassword ();
	char *group,*account,*pswdp;
	struct passwd *pwd;
	struct group *grp;
#if	CMUCS
	struct account *acc;
	struct ttyloc tlc;
#endif	CMUCS
	register int status = ACCESS_CODE_OK;
	char nbuf[STRINGLENGTH];
	static char errbuf[STRINGLENGTH];
	int *grps;
	char *p;

	if (namep == NULL) {
		pwd = getpwuid (fileuid);
		if (pwd == NULL) {
			(void) sprintf (errbuf,"Reason:  Unknown user id %d",
				fileuid);
			return(errbuf);
		}
		grp = getgrgid (filegid);
		if (grp)  group = strcpy (nbuf,grp->gr_name);
		else  group = NULL;
		account = NULL;
		pswdp = NULL;
	} else {
		(void) strcpy (nbuf,namep);
		account = group = index (nbuf,',');
		if (group != NULL) {
			*group++ = '\0';
			account = index (group,',');
			if (account != NULL) {
				*account++ = '\0';
				if (*account == '\0')  account = NULL;
			}
			if (*group == '\0')  group = NULL;
		}
		pwd = getpwnam (nbuf);
		if (pwd == NULL){
			(void) sprintf (errbuf,"Reason:  Unknown user %s",
				nbuf);
			return (errbuf);
		}
		if (strcmp (nbuf,DEFUSER) == 0)
			pswdp = NULL;
		else
			pswdp = passwordp ? passwordp : "";
	}
	if (getuid () != 0) {
		if (getuid () == pwd->pw_uid)
			return (NULL);
		if (strcmp (pwd->pw_name,DEFUSER) == 0)
			return (NULL);
		logerr ("Fileserver not superuser");
		return ("Reason:  fileserver is not running privileged");
	}
#if	CMUCS
	tlc.tlc_hostid = TLC_UNKHOST;
	tlc.tlc_ttyid = TLC_UNKTTY;
	if (okaccess(pwd->pw_name,ACCESS_TYPE_SU,0,-1,tlc) != 1)
		status = ACCESS_CODE_DENIED;
	else {
		grp = NULL;
		acc = NULL;
		status = oklogin(pwd->pw_name,group,&account,pswdp,&pwd,&grp,&acc,&grps);
		if (status == ACCESS_CODE_OK) {
			if ((p = okpassword(pswdp,pwd->pw_name,pwd->pw_gecos)) != NULL)
				status = ACCESS_CODE_INSECUREPWD;
		}
	}
#else	CMUCS
	status = ACCESS_CODE_OK;
	if (namep && strcmp(pwd->pw_name, DEFUSER) != 0)
		if (strcmp(pwd->pw_passwd,crypt(pswdp,pwd->pw_passwd)))
			status = ACCESS_CODE_BADPASSWORD;
#endif	CMUCS
	switch (status) {
	case ACCESS_CODE_OK:
		break;
	case ACCESS_CODE_BADPASSWORD:
		p = "Reason:  Invalid password";
		break;
#if	CMUCS
	case ACCESS_CODE_INSECUREPWD:
		(void) sprintf (errbuf,"Reason:  %s",p);
		p = errbuf;
		break;
	case ACCESS_CODE_DENIED:
		p = "Reason:  Access denied";
		break;
	case ACCESS_CODE_NOUSER:
		p = errbuf;
		break;
	case ACCESS_CODE_ACCEXPIRED:
		p = "Reason:  Account expired";
		break;
	case ACCESS_CODE_GRPEXPIRED:
		p = "Reason:  Group expired";
		break;
	case ACCESS_CODE_ACCNOTVALID:
		p = "Reason:  Invalid account";
		break;
	case ACCESS_CODE_MANYDEFACC:
		p = "Reason:  User has more than one default account";
		break;
	case ACCESS_CODE_NOACCFORGRP:
		p = "Reason:  No account for group";
		break;
	case ACCESS_CODE_NOGRPFORACC:
		p = "Reason:  No group for account";
		break;
	case ACCESS_CODE_NOGRPDEFACC:
		p = "Reason:  No group for default account";
		break;
	case ACCESS_CODE_NOTGRPMEMB:
		p = "Reason:  Not member of group";
		break;
	case ACCESS_CODE_NOTDEFMEMB:
		p = "Reason:  Not member of default group";
		break;
	case ACCESS_CODE_OOPS:
		p = "Reason:  Internal error";
		break;
#endif	CMUCS
	default:
		(void) sprintf (errbuf,"Reason:  Status %d",status);
		p = errbuf;
		break;
	}
	if (pwd == NULL)
		return (p);
	if (status != ACCESS_CODE_OK) {
		logerr ("Login failure for %s",pwd->pw_name);
		logerr ("%s",p);
#if	CMUCS
		logaccess (pwd->pw_name,ACCESS_TYPE_SUP,status,0,-1,tlc);
#endif	CMUCS
		return (p);
	}
#if	CMUCS
	if (setgroups (grps[0], &grps[1]) < 0)
		logerr ("setgroups: %%m");
	if (setgid ((gid_t)grp->gr_gid) < 0)
		logerr ("setgid: %%m");
	if (setuid ((uid_t)pwd->pw_uid) < 0)
		logerr ("setuid: %%m");
#else   CMUCS
	if (initgroups (pwd->pw_name,pwd->pw_gid) < 0)
		return("Error setting group list");
	if (setgid (pwd->pw_gid) < 0)
		logerr ("setgid: %%m");
	if (setuid (pwd->pw_uid) < 0)
		logerr ("setuid: %%m");
#endif	CMUCS
	return (NULL);
}

/* VARARGS1 */
goaway (fmt,va_alist)
register char *fmt;
va_dcl
{
	char buf[STRINGLENGTH];
	va_list ap;

	(void) netcrypt ((char *)NULL);
	va_start(ap);
	vsnprintf(buf, sizeof(buf), fmt, ap);
	va_end(ap);
	goawayreason = salloc (buf);
	(void) msggoaway ();
	logerr ("%s",buf);
	longjmp (sjbuf,TRUE);
}

char *fmttime (time)
long time;
{
	static char buf[STRINGLENGTH];
	int len;

	(void) strcpy (buf,ctime (&time));
	len = strlen(buf+4)-6;
	(void) strncpy (buf,buf+4,len);
	buf[len] = '\0';
	return (buf);
}
#if	CMUCS
/*
 * Companion routine for ensuring that a local file can be trusted.  Compare
 * various pieces of the stat information to make sure that the file can be
 * trusted.  Returns true for stat information which meets the criteria
 * for being trustworthy.  The main paranoia is to prevent a hard link to
 * a root owned file.  Since the link could be removed after the file is
 * opened, a simply fstat() can not be relied upon.  The two stat buffers
 * for comparison should come from a stat() on the file name and a following
 * fstat() on the open file.  Some of the following checks are also an
 * additional level of paranoia.  Also, this test will fail (correctly) if
 * either or both of the stat structures have all fields zeroed; typically
 * due to a stat() failure.
 */
int stat_info_ok(sb1, sb2)
struct stat *sb1, *sb2;
{
    return (sb1->st_ino == sb2->st_ino &&	/* Still the same file */
	    sb1->st_dev == sb2->st_dev &&	/* On the same device */
	    sb1->st_mode == sb2->st_mode &&     /* Perms (and type) same */
	    (sb1->st_mode & S_IFMT) == S_IFREG && /* Only allow reg files */
	    !(sb1->st_mode & 077) &&		/* Owner only perms */
	    sb1->st_nlink == sb2->st_nlink &&	/* # hard links same... */
	    sb1->st_nlink == 1 &&		/* and only 1 */
	    sb1->st_uid == sb2->st_uid &&	/* owner and ... */
	    sb1->st_gid == sb2->st_gid &&	/* group unchanged */
	    sb1->st_mtime == sb2->st_mtime &&	/* Unmodified between stats */
	    sb1->st_ctime == sb2->st_ctime);	/* Inode unchanged.  Hopefully
						   a catch-all paranoid test */
}

/*
 * For detecting RFS links which are opened as regular files.
 */
#define	ROOT_USER	0
#define	SYMLINK_GRP	64
#else 	/* CMUCS */
int stat_info_ok(sb1, sb2)
{    return (1);
}
#endif	/* CMUCS */

#ifndef	VICEIOCTL
#if	AFS_ENV
/*
 * Put the necessary AFS definitions here in case the system supports AFS,
 * but lacks sys/viceioctl.h.
 */
struct ViceIoctl {
	caddr_t in, out;	/* Data to be transferred in, or out */
	short in_size;		/* Size of input buffer <= 2K */
        short out_size;		/* Maximum size of output buffer, <= 2K */
};

#define _VICEIOCTL(id)  ((unsigned int ) _IOW(V, id, struct ViceIoctl))
#endif	/* AFS_ENV */
#endif	/* VICEIOCTL */

/*
 * Determine whether the file referenced by the file descriptor 'handle' can
 * be trusted, namely is it a file resident in the local file system.
 *
 * The main method of operation is to perform operations on the file
 * descriptor so that an attempt to spoof the checks should fail, for
 * example renamimg the file from underneath us and/or changing where the
 * file lives from underneath us.
 *
 * returns: -1 for error, indicating that we can not tell
 *	     0 for file is definately not local, or it is an RFS link
 *	     1 for file is local and can be trusted
 *
 * Side effect: copies the stat information into the supplied buffer,
 * regardless of the type of file system the file resides.
 *
 * Currently, the cases that we try to distinguish are RFS, AFS, NFS and
 * UFS, where the latter is considered a trusted file.  We assume that the
 * caller has disabled link following and will detect an attempt to access
 * a file through an RFS link, except in the case the the last component is
 * an RFS link.  With link following disabled, the last component itself is
 * interpretted as a regular file if it is really an RFS link, so we
 * disallow the RFS link owner,group "root,symlink".  An AFS file is
 * detected by trying the VIOCIGETCELL ioctl, which is one of the few AFS
 * ioctls which operate on a file descriptor.  Note, this AFS ioctl is
 * implemented in the cache manager, so the decision does not involve a
 * query with the AFS file server.  An NFS file is detected by looking at
 * the major device number and seeing if it matches the known values for
 * MACH NSF/Sun OS 3.x or Sun OS 4.x.
 *
 * Having the fstatfs() system call would make this routine easier and
 * more reliable.
 *
 * Note, in order to make the checks simpler, the file referenced by the
 * file descriptor can not be a BSD style symlink.  Even with symlink
 * following of the last path component disabled, the attempt to open a
 * file which is a symlink will succeed, so we check for the BSD symlink
 * file type here.  Also, the link following on/off and RFS file types
 * are only relevant in a CMUCS/MACH environment. 
 */
local_file(handle, sinfo)
int handle;
struct stat *sinfo;
{
	struct stat sb;
#if	CMUCS || AFS_ENV
	/*
	 * dummies for the AFS ioctl
	 */
	struct ViceIoctl vdata;
	char cellname[512];
#endif	/* CMUCS || AFS_ENV */

	if (sinfo != NULL)
		(void) bzero((char *)sinfo, sizeof(*sinfo));

	if (fstat(handle, &sb) < 0)
		return(-1);

	if (sinfo != NULL)
		*sinfo = sb;

#if	CMUCS
	/*
	 * If the following test succeeds, then the file referenced by 'handle'
	 * is actually an RFS link, so we will not trust it.
	 */
	if (sb.st_uid == ROOT_USER && sb.st_gid == SYMLINK_GRP)
		return(0);
#endif	/* CMUCS */

	/*
	 * Do not trust BSD style symlinks either.
	 */
	if ((sb.st_mode & S_IFMT) == S_IFLNK)
		return(0);

#if	CMUCS || AFS_ENV
	/*
	 * This is the VIOCIGETCELL (vice ioctl 3) ioctl, which takes an fd,
	 * not a path name.  If it succeeds, then file is in /afs.
	 *
	 * On failure, ENOTTY indicates that the file was not in AFS; all other
	 * errors are pessimistically assumed to be a temporary AFS error.
	 */
	vdata.in_size = 0;
	vdata.out_size = sizeof(cellname);
	vdata.out = cellname;
	if (ioctl(handle, _VICEIOCTL(3), (char *)&vdata) >= 0)
		return(0);
	else if (errno != ENOTTY)
		return(-1);
#endif	/* CMUCS || AFS_ENV */

	/*
	 * Verify the file is not in NFS.  Our current NFS implemention and
	 * Sun OS 3.x uses major device 255 for NFS files; Sun OS 4.x seems
	 * to use 130 (I have only determined this empirically -- DLC).
	 * Without a fstatfs() system call, this will have to do for now.
	 */
	if (major(sb.st_dev) == 255 || major(sb.st_dev) == 130)
		return(0);

	return(1);
}

/*
 * Twiddle symbolic/RFS link following on/off.  This is a no-op in a non
 * CMUCS/MACH environment.  Also, the setmodes/getmodes interface is used
 * mainly because it is simpler than using table(2) directly.
 */
int link_nofollow(on)
int on;
{
#if	CMUCS
	int modes;

	if ((modes = getmodes()) < 0) {
	return(-1);
	}

	if (on)
		return(setmodes(modes | UMODE_NOFOLLOW));
	else
		return(setmodes(modes & (~UMODE_NOFOLLOW)));
#else	/* CMUCS */
	return(0);
#endif	/* CMUCS */
}
