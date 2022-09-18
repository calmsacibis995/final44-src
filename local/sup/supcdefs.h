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
 *	supcdefs.h -- Declarations shared by the collection of files
 *			that build the sup client.
 *
 **********************************************************************
 * HISTORY
 * 10-Feb-88  Glenn Marcy (gm0w) at Carnegie-Mellon University
 *	Added timeout for backoff.
 *
 * 28-Jun-87  Glenn Marcy (gm0w) at Carnegie-Mellon University
 *	Added Crelease for "release" support.
 *
 * 25-May-87  Doug Philips (dwp) at Carnegie-Mellon University
 *	Created.
 *
 **********************************************************************
 */

#include <libc.h>
#include <netdb.h>
#include <signal.h>
#include <setjmp.h>
#include <pwd.h>
#include <grp.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/file.h>
#include <sys/errno.h>
#if	CMUCS			/* used by resource pausing code only */
#include <sys/ioctl.h>
#include <sys/resource.h>
#endif	CMUCS
#include <c.h>
#include "sup.h"
#include "supmsg.h"

extern int errno;
extern uid_t getuid();
extern gid_t getgid();
extern long time();

extern int PGMVERSION;

/*******************************************
 ***    D A T A   S T R U C T U R E S    ***
 *******************************************/

struct collstruct {			/* one per collection to be upgraded */
	char *Cname;			/* collection name */
	TREE *Chost;			/* attempted host for collection */
	TREE *Chtree;			/* possible hosts for collection */
	char *Cbase;			/* local base directory */
	char *Chbase;			/* remote base directory */
	char *Cprefix;			/* local collection pathname prefix */
	char *Crelease;			/* release name */
	char *Cnotify;			/* user to notify of status */
	char *Clogin;			/* remote login name */
	char *Cpswd;			/* remote password */
	char *Ccrypt;			/* data encryption key */
	int Ctimeout;			/* timeout for backoff */
	int Cflags;			/* collection flags */
	int Cnogood;			/* upgrade no good, "when" unchanged */
	int Clockfd;			/* >= 0 if collection is locked */
	struct collstruct *Cnext;	/* next collection */
};
typedef struct collstruct COLLECTION;

#define CFALL		00001
#define CFBACKUP	00002
#define CFDELETE	00004
#define CFEXECUTE	00010
#define CFLIST		00020
#define CFLOCAL		00040
#define CFMAIL		00100
#define CFOLD		00200
#define CFVERBOSE	00400

/*************************
 ***	M A C R O S    ***
 *************************/

#define vnotify	if (thisC->Cflags&CFVERBOSE)  notify
