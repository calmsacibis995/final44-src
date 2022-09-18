h37202
s 00001/00001/00163
d D 8.3 94/04/02 10:07:46 pendry 14 13
c add 1994 copyright
e
s 00014/00011/00150
d D 8.2 94/04/02 08:38:44 pendry 13 12
c prettyness police
e
s 00002/00002/00159
d D 8.1 93/06/09 22:43:45 bostic 12 11
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00000/00160
d D 5.11 92/07/12 16:02:28 bostic 11 10
c fake out gcc 
e
s 00004/00001/00156
d D 5.10 92/06/29 12:51:50 bostic 10 9
c ANSI C prototypes
e
s 00016/00001/00141
d D 5.9 91/06/02 17:40:02 karels 9 8
c use same tkt file as su for "user.root", letting login.c set the env
c (too early here); avoid in_tkt botch with uids
e
s 00018/00019/00124
d D 5.8 91/06/01 15:13:06 karels 8 7
c various cleanups: allow any instance to be attempted; no syslog
c if there is no Kerberos realm; fix up error msgs; allow user.root login
c via Kerberos on any tty
e
s 00002/00001/00141
d D 5.7 91/05/09 13:35:56 bostic 7 6
c ignore "generic errors"
e
s 00002/00001/00140
d D 5.6 91/03/29 17:57:26 kfall 6 5
c update to use "person.root" login for kerberos
e
s 00003/00003/00138
d D 5.5 91/03/29 14:30:54 kfall 5 4
c fix problem where bad login would kill valid ticket cache
e
s 00003/00001/00138
d D 5.4 90/09/05 16:57:26 kfall 4 3
c call get_lrealm() with 0; -> don't use KRB_REALM define
e
s 00000/00002/00139
d D 5.3 90/06/21 16:15:09 kfall 3 2
c remove extraneous debug code
e
s 00035/00027/00106
d D 5.2 90/06/21 16:03:41 kfall 2 1
c use default ticket location, remove tty argument to klogin
e
s 00133/00000/00000
d D 5.1 90/06/19 19:22:39 kfall 1 0
c date and time created 90/06/19 19:22:39 by kfall
e
u
U
t
T
I 1
/*-
D 12
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 12
I 12
D 14
 * Copyright (c) 1990, 1993
E 14
I 14
 * Copyright (c) 1990, 1993, 1994
E 14
 *	The Regents of the University of California.  All rights reserved.
E 12
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#ifdef KERBEROS
#include <sys/param.h>
#include <sys/syslog.h>
#include <kerberosIV/des.h>
#include <kerberosIV/krb.h>
D 13
#include <pwd.h>
E 13
I 13

#include <err.h>
E 13
#include <netdb.h>
I 13
#include <pwd.h>
E 13
I 10
#include <stdio.h>
I 13
#include <stdlib.h>
E 13
#include <string.h>
#include <unistd.h>
E 10

D 8
#define	PRINCIPAL_NAME	pw->pw_name
D 6
#define	PRINCIPAL_INST	""
E 6
I 6
#define	PRINCIPAL_INST	(rootlogin ? "root" : "")
E 8
E 6
#define	INITIAL_TICKET	"krbtgt"
#define	VERIFY_SERVICE	"rcmd"

extern int notickets;
I 9
extern char *krbtkfile_env;
E 9
I 6
D 8
extern int rootlogin;
E 8
E 6

/*
D 2
 * return 0 on success
 *	  1 if Kerberos not around (try local)
 *	  2 on failure
E 2
I 2
 * Attempt to log the user in using Kerberos authentication
 *
 * return 0 on success (will be logged in)
 *	  1 if Kerberos failed (try local password in login)
E 2
 */
D 10

E 10
I 10
int
E 10
D 2
klogin(pw, localhost, name, tty)
E 2
I 2
D 8
klogin(pw, localhost, password)
E 8
I 8
klogin(pw, instance, localhost, password)
E 8
E 2
	struct passwd *pw;
D 2
	char *localhost, *name, *tty;
E 2
I 2
D 8
	char *localhost, *password;
E 8
I 8
	char *instance, *localhost, *password;
E 8
E 2
{
	int kerror;
	AUTH_DAT authdata;
	KTEXT_ST ticket;
	struct hostent *hp;
	unsigned long faddr;
D 2
	char tkfile[MAXPATHLEN], realm[REALM_SZ], savehost[MAXHOSTNAMELEN];
E 2
I 2
	char realm[REALM_SZ], savehost[MAXHOSTNAMELEN];
	char tkt_location[MAXPATHLEN];
I 11
	char *krb_get_phost();
E 11
E 2

	/*
D 8
	 * If we aren't Kerberos-authenticated, try the normal pw file
	 * for a password.  If that's ok, log the user in without issueing
	 * any tickets.
E 8
I 8
	 * Root logins don't use Kerberos.
	 * If we have a realm, try getting a ticket-granting ticket
	 * and using it to authenticate.  Otherwise, return
	 * failure so that we can try the normal passwd file
	 * for a password.  If that's ok, log the user in
	 * without issuing any tickets.
E 8
	 */
D 4
	if (krb_get_lrealm(realm, 1) != KSUCCESS)
E 4
I 4
D 8
	if (krb_get_lrealm(realm, 0) != KSUCCESS) {
		syslog(LOG_ERR, "couldn't get local Kerberos realm");
E 4
		return(1);
I 4
	}
E 8
I 8
	if (strcmp(pw->pw_name, "root") == 0 ||
	    krb_get_lrealm(realm, 0) != KSUCCESS)
		return (1);
E 8
E 4

	/*
D 2
	 * get TGT for local realm; by convention, store tickets in file
	 * associated with tty name, which should be available.
E 2
I 2
	 * get TGT for local realm
D 8
	 * tickets are stored in a file determined by calling tkt_string()
E 8
I 8
	 * tickets are stored in a file named TKT_ROOT plus uid
I 9
	 * except for user.root tickets.
E 9
E 8
E 2
	 */
D 2
	(void)sprintf(tkfile, "%s_%s", TKT_ROOT, tty);
E 2

D 2
	if (setenv("KRBTKFILE", tkfile, 1) < 0) {
		kerror = INTK_ERR;
		syslog(LOG_ERR, "couldn't set tkfile environ");
	} else {
		(void)unlink(tkfile);
		kerror = krb_get_pw_in_tkt(PRINCIPAL_NAME, PRINCIPAL_INST,
		    realm, INITIAL_TICKET, realm, DEFAULT_TKT_LIFE, name);
	}
E 2
I 2
D 9
	(void)sprintf(tkt_location, "%s%d", TKT_ROOT, pw->pw_uid);
E 9
I 9
	if (strcmp(instance, "root") != 0)
		(void)sprintf(tkt_location, "%s%d", TKT_ROOT, pw->pw_uid);
	else {
		(void)sprintf(tkt_location, "%s_root_%d", TKT_ROOT, pw->pw_uid);
		krbtkfile_env = tkt_location;
	}
E 9
	(void)krb_set_tkt_string(tkt_location);
D 5
	(void)dest_tkt();
E 5
E 2

I 9
	/*
	 * Set real as well as effective ID to 0 for the moment,
	 * to make the kerberos library do the right thing.
	 */
	if (setuid(0) < 0) {
D 13
		perror("login: setuid");
E 13
I 13
		warnx("setuid");
E 13
		return (1);
	}
E 9
I 2
D 8
	kerror = krb_get_pw_in_tkt(PRINCIPAL_NAME, PRINCIPAL_INST,
E 8
I 8
	kerror = krb_get_pw_in_tkt(pw->pw_name, instance,
E 8
		    realm, INITIAL_TICKET, realm, DEFAULT_TKT_LIFE, password);
D 3
syslog(LOG_ERR, "retval of get_pw_in_tkt: %s", krb_err_txt[kerror]);

E 3
E 2
	/*
	 * If we got a TGT, get a local "rcmd" ticket and check it so as to
	 * ensure that we are not talking to a bogus Kerberos server.
	 *
	 * There are 2 cases where we still allow a login:
	 *	1: the VERIFY_SERVICE doesn't exist in the KDC
	 *	2: local host has no srvtab, as (hopefully) indicated by a
	 *	   return value of RD_AP_UNDEC from krb_rd_req().
	 */
	if (kerror != INTK_OK) {
D 2
		(void)unlink(tkfile);
E 2
I 2
D 5
		dest_tkt();
E 2
		if (kerror != INTK_BADPW && kerror != KDC_PR_UNKNOWN)
E 5
I 5
D 7
		if (kerror != INTK_BADPW && kerror != KDC_PR_UNKNOWN) {
E 7
I 7
D 8
		if (kerror != INTK_BADPW && kerror != KDC_PR_UNKNOWN &&
		    kerror != KFAILURE) {
E 8
I 8
		if (kerror != INTK_BADPW && kerror != KDC_PR_UNKNOWN) {
E 8
E 7
E 5
			syslog(LOG_ERR, "Kerberos intkt error: %s",
			    krb_err_txt[kerror]);
I 5
			dest_tkt();
		}
E 5
D 2
		return(2);
E 2
I 2
D 8
		return(1);
E 8
I 8
		return (1);
E 8
E 2
	}

D 2
	if (chown(tkfile, pw->pw_uid, pw->pw_gid) < 0)
		syslog(LOG_ERR, "chown tkfile: %m");
E 2
I 2
	if (chown(TKT_FILE, pw->pw_uid, pw->pw_gid) < 0)
		syslog(LOG_ERR, "chown tkfile (%s): %m", TKT_FILE);
E 2

	(void)strncpy(savehost, krb_get_phost(localhost), sizeof(savehost));
	savehost[sizeof(savehost)-1] = NULL;
D 2
	kerror = krb_mk_req(&ticket, VERIFY_SERVICE, savehost, realm, 33);
E 2

	/*
	 * if the "VERIFY_SERVICE" doesn't exist in the KDC for this host,
	 * still allow login with tickets, but log the error condition.
	 */
I 2

	kerror = krb_mk_req(&ticket, VERIFY_SERVICE, savehost, realm, 33);
E 2
	if (kerror == KDC_PR_UNKNOWN) {
D 8
		syslog(LOG_NOTICE, "warning: TGT not verified (%s)",
		    krb_err_txt[kerror]);
E 8
I 8
		syslog(LOG_NOTICE,
    		    "warning: TGT not verified (%s); %s.%s not registered, or srvtab is wrong?",
		    krb_err_txt[kerror], VERIFY_SERVICE, savehost);
E 8
		notickets = 0;
D 13
		return(0);
E 13
I 13
		return (0);
E 13
	}

	if (kerror != KSUCCESS) {
D 13
		(void)printf("unable to use TGT: (%s)\n", krb_err_txt[kerror]);
E 13
I 13
		warnx("unable to use TGT: (%s)", krb_err_txt[kerror]);
E 13
		syslog(LOG_NOTICE, "unable to use TGT: (%s)",
		    krb_err_txt[kerror]);
		dest_tkt();
D 2
		return(2);
E 2
I 2
D 13
		return(1);
E 13
I 13
		return (1);
E 13
E 2
	}

	if (!(hp = gethostbyname(localhost))) {
		syslog(LOG_ERR, "couldn't get local host address");
D 2
		return(2);
E 2
I 2
		dest_tkt();
D 13
		return(1);
E 13
I 13
		return (1);
E 13
E 2
	}
I 2

E 2
D 13
	bcopy((void *)hp->h_addr, (void *)&faddr, sizeof(faddr));
E 13
I 13
	memmove((void *)&faddr, (void *)hp->h_addr, sizeof(faddr));
E 13

	kerror = krb_rd_req(&ticket, VERIFY_SERVICE, savehost, faddr,
	    &authdata, "");
I 2

E 2
	if (kerror == KSUCCESS) {
		notickets = 0;
D 13
		return(0);
E 13
I 13
		return (0);
E 13
	}
I 2

	/* undecipherable: probably didn't have a srvtab on the local host */
E 2
	if (kerror = RD_AP_UNDEC) {
		syslog(LOG_NOTICE, "krb_rd_req: (%s)\n", krb_err_txt[kerror]);
D 2
		notickets = 0;
		return(0);
E 2
I 2
		dest_tkt();
D 13
		return(1);
E 13
I 13
		return (1);
E 13
E 2
	}
I 2
	/* failed for some other reason */
E 2
D 13
	(void)printf("unable to verify %s ticket: (%s)\n", VERIFY_SERVICE,
E 13
I 13
	warnx("unable to verify %s ticket: (%s)", VERIFY_SERVICE,
E 13
	    krb_err_txt[kerror]);
	syslog(LOG_NOTICE, "couldn't verify %s ticket: %s", VERIFY_SERVICE,
	    krb_err_txt[kerror]);
D 2
	return(2);
E 2
I 2
	dest_tkt();
D 13
	return(1);
E 13
I 13
	return (1);
E 13
E 2
}
#endif
E 1
