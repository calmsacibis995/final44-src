/* 
 * $Id: rkinitd.c,v 1.2 1993/12/10 19:31:24 dglo Exp dglo $
 * $Source: /a/guest/dglo/nuk/rkinitd/RCS/rkinitd.c,v $
 * $Author: dglo $
 *
 * This is the main source file for rkinit
 */

#if !defined(lint) && !defined(SABER) && !defined(LOCORE) && defined(RCS_HDRS)
static char *rcsid = "$Id: rkinitd.c,v 1.2 1993/12/10 19:31:24 dglo Exp dglo $";
#endif /* lint || SABER || LOCORE || RCS_HDRS */

#include <stdio.h>
#include <ctype.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/file.h>
#include <sys/socket.h>
#ifndef GOT_NETINET_IN_H
#include <netinet/in.h>
#define GOT_NETINET_IN_H
#endif /* GOT_NETINET_IN_H */
#include <netdb.h>
#include <strings.h>
#include <signal.h>
#include <sys/time.h>
#include <pwd.h>
#include <des.h>
#include <krb.h>
#include <syslog.h>

#include <rkinit.h>
#include <rkinit_err.h>
#include <rkinit_private.h>

#include "rkinitd.h"

#include "sys_proto.h"

extern int errno;

static int inetd = TRUE;	/* True if we were started by inetd */

#ifdef __STDC__
static void usage(void) 
#else
static void usage()
#endif /* __STDC__ */
{
    syslog(LOG_ERR, "rkinitd usage: rkinitd [-notimeout]\n");
    exit(1);
}

#ifdef __STDC__
void error(void)
#else
void error()
#endif /* __STDC__ */
{
    char errbuf[BUFSIZ];
    
    strcpy(errbuf, rkinit_errmsg(0));
    if (strlen(errbuf)) {
	if (inetd)
	    syslog(LOG_ERR, "rkinitd: %s", errbuf);
	else
	    fprintf(stderr, "rkinitd: %s\n", errbuf);
    }
}

int
#ifdef __STDC__
main(int argc, char *argv[])
#else
main(argc, argv)
  int argc;
  char *argv[];
#endif /* __STDC__ */
{
    int version;		/* Version of the transaction */

    int notimeout = FALSE;	/* Should we not timeout? */

    int status = 0;		/* General error code */

    /*
     * Environment get smashed in validate_user so that it does not inherit
     * kerberos ticket variable information from the person who started
     * the process (if a person started it...).
     */
    /* Initialize com_err error table */
    init_rkin_err_tbl();

#ifdef DEBUG
    /* This only works if the library was compiled with DEBUG defined */
    rki_i_am_server();
#endif /* DEBUG */

    /* 
     * Make sure that we are running as root or can arrange to be 
     * running as root.  We need both to be able to read /etc/srvtab
     * and to be able to change uid to create tickets.
     */
    
    (void) setuid(0);
    if (getuid() != 0) {
	syslog(LOG_ERR, "rkinitd: not running as root.\n");
	exit(1);
    }

    /* Determine whether to time out */
    if (argc == 2) {
	if (strcmp(argv[1], "-notimeout"))
	    usage();
	else
	    notimeout = TRUE;
    }
    else if (argc != 1)
	usage();

    inetd = setup_rpc(notimeout);

    if ((status = choose_version(&version) != RKINIT_SUCCESS)) {
	error();
	exit(1);
    }

    if ((status = get_tickets(version) != RKINIT_SUCCESS)) {
	error();
	exit(1);
    }

    exit(0);
}

    
