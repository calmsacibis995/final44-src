h07926
s 00001/00001/00292
d D 8.3 94/04/02 09:46:53 pendry 7 6
c add 1994 copyright
e
s 00070/00067/00223
d D 8.2 94/04/02 09:35:29 pendry 6 5
c prettyness police
e
s 00002/00002/00288
d D 8.1 93/06/06 15:49:14 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00001/00287
d D 5.4 91/03/01 15:18:57 bostic 4 3
c ANSI
e
s 00001/00001/00287
d D 5.3 91/02/12 22:16:25 bostic 3 2
c rework the password subsystem
e
s 00009/00007/00279
d D 5.2 91/02/03 13:52:37 bostic 2 1
c structure not &structure in call to bzero; minor lint
e
s 00286/00000/00000
d D 5.1 91/02/03 13:36:55 bostic 1 0
c date and time created 91/02/03 13:36:55 by bostic
e
u
U
t
T
I 1
/*-
D 5
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
D 7
 * Copyright (c) 1990, 1993
E 7
I 7
 * Copyright (c) 1990, 1993, 1994
E 7
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#ifdef KERBEROS

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <netinet/in.h>
#include <kerberosIV/des.h>
#include <kerberosIV/krb.h>
I 6

#include <err.h>
#include <errno.h>
E 6
#include <netdb.h>
D 6
#include <signal.h>
E 6
#include <pwd.h>
D 6
#include <errno.h>
E 6
I 6
#include <signal.h>
E 6
#include <stdio.h>
D 6
#include "kpasswd_proto.h"
I 2
#include <string.h>
E 6
#include <stdlib.h>
I 6
#include <string.h>
#include <unistd.h>
E 6
E 2

I 6
#include "kpasswd_proto.h"

#include "extern.h"

E 6
#define	PROTO	"tcp"

I 6
static void	send_update __P((int, char *, char *));
static void	recv_ack __P((int));
static void	cleanup __P((void));
static void	finish __P((void));

E 6
static struct timeval timeout = { CLIENT_KRB_TIMEOUT, 0 };
static struct kpasswd_data proto_data;
static des_cblock okey;
static Key_schedule osched;
D 6
KTEXT_ST ticket;
Key_schedule random_schedule;
long authopts;
char realm[REALM_SZ], krbhst[MAX_HSTNM];
int sock;
E 6
I 6
static KTEXT_ST ticket;
static Key_schedule random_schedule;
static long authopts;
static char realm[REALM_SZ], krbhst[MAX_HSTNM];
static int sock;
E 6

I 6
int
E 6
D 3
do_krb_passwd()
E 3
I 3
krb_passwd()
E 3
{
	struct servent *se;
	struct hostent *host;
	struct sockaddr_in sin;
	CREDENTIALS cred;
	fd_set readfds;
D 4
	int rval, finish();
E 4
I 4
	int rval;
E 4
	char pass[_PASSWORD_LEN], password[_PASSWORD_LEN];
I 4
	static void finish();
E 4

	static struct rlimit rl = { 0, 0 };

	(void)signal(SIGHUP, SIG_IGN);
	(void)signal(SIGINT, SIG_IGN);
	(void)signal(SIGTSTP, SIG_IGN);

	if (setrlimit(RLIMIT_CORE, &rl) < 0) {
D 6
		(void)fprintf(stderr,
		    "passwd: setrlimit: %s\n", strerror(errno));
		return(1);
E 6
I 6
		warn("setrlimit");
		return (1);
E 6
	}

	if ((se = getservbyname(SERVICE, PROTO)) == NULL) {
D 6
		(void)fprintf(stderr,
		    "passwd: couldn't find entry for service %s/%s\n",
E 6
I 6
		warnx("couldn't find entry for service %s/%s",
E 6
		    SERVICE, PROTO);
D 6
		return(1);
E 6
I 6
		return (1);
E 6
	}

	if ((rval = krb_get_lrealm(realm,1)) != KSUCCESS) {
D 6
		(void)fprintf(stderr,
		    "passwd: couldn't get local Kerberos realm: %s\n",
E 6
I 6
		warnx("couldn't get local Kerberos realm: %s",
E 6
		    krb_err_txt[rval]);
D 6
		return(1);
E 6
I 6
		return (1);
E 6
	}

	if ((rval = krb_get_krbhst(krbhst, realm, 1)) != KSUCCESS) {
D 6
		(void)fprintf(stderr,
		    "passwd: couldn't get Kerberos host: %s\n",
E 6
I 6
		warnx("couldn't get Kerberos host: %s",
E 6
		    krb_err_txt[rval]);
D 6
		return(1);
E 6
I 6
		return (1);
E 6
	}

	if ((host = gethostbyname(krbhst)) == NULL) {
D 6
		(void)fprintf(stderr,
		    "passwd: couldn't get host entry for krb host %s\n",
E 6
I 6
		warnx("couldn't get host entry for krb host %s",
E 6
		    krbhst);
D 6
		return(1);
E 6
I 6
		return (1);
E 6
	}

	sin.sin_family = host->h_addrtype;
D 6
	bcopy(host->h_addr, (char *) &sin.sin_addr, host->h_length);
E 6
I 6
	memmove((char *) &sin.sin_addr, host->h_addr, host->h_length);
E 6
	sin.sin_port = se->s_port;

	if ((sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
D 6
		(void)fprintf(stderr, "passwd: socket: %s\n", strerror(errno));
		return(1);
E 6
I 6
		warn("socket");
		return (1);
E 6
	}

	if (connect(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
D 6
		(void)fprintf(stderr, "passwd: connect: %s\n", strerror(errno));
E 6
I 6
		warn("connect");
E 6
		(void)close(sock);
D 6
		return(1);
E 6
I 6
		return (1);
E 6
	}

	rval = krb_sendauth(
		authopts,		/* NOT mutual */
		sock,
		&ticket,		/* (filled in) */
		SERVICE,
		krbhst,			/* instance (krbhst) */
		realm,			/* dest realm */
		(u_long) getpid(),	/* checksum */
		NULL,			/* msg data */
		NULL,			/* credentials */ 
		NULL,			/* schedule */
		NULL,			/* local addr */
		NULL,			/* foreign addr */
		"KPWDV0.1"
	);

	if (rval != KSUCCESS) {
D 6
		(void)fprintf(stderr, "passwd: Kerberos sendauth error: %s\n",
		    krb_err_txt[rval]);
		return(1);
E 6
I 6
		warnx("Kerberos sendauth error: %s", krb_err_txt[rval]);
		return (1);
E 6
	}

	krb_get_cred("krbtgt", realm, realm, &cred);

	(void)printf("Changing Kerberos password for %s.%s@%s.\n",
	    cred.pname, cred.pinst, realm);

	if (des_read_pw_string(pass,
	    sizeof(pass)-1, "Old Kerberos password:", 0)) {
D 6
		(void)fprintf(stderr,
		    "passwd: error reading old Kerberos password\n");
		return(1);
E 6
I 6
		warnx("error reading old Kerberos password");
		return (1);
E 6
	}

	(void)des_string_to_key(pass, okey);
	(void)des_key_sched(okey, osched);
	(void)des_set_key(okey, osched);

	/* wait on the verification string */

	FD_ZERO(&readfds);
	FD_SET(sock, &readfds);

	rval =
	    select(sock + 1, &readfds, (fd_set *) 0, (fd_set *) 0, &timeout);

	if ((rval < 1) || !FD_ISSET(sock, &readfds)) {
		if(rval == 0) {
D 6
			(void)fprintf(stderr, "passwd: timed out (aborted)\n");
E 6
I 6
			warnx("timed out (aborted)");
E 6
			cleanup();
D 6
			return(1);
E 6
I 6
			return (1);
E 6
		}
D 6
		(void)fprintf(stderr, "passwd: select failed (aborted)\n");
E 6
I 6
		warnx("select failed (aborted)");
E 6
		cleanup();
D 6
		return(1);
E 6
I 6
		return (1);
E 6
	}

	/* read verification string */

	if (des_read(sock, &proto_data, sizeof(proto_data)) !=
	    sizeof(proto_data)) {
D 6
		(void)fprintf(stderr,
		    "passwd: couldn't read verification string (aborted)\n");
E 6
I 6
		warnx("couldn't read verification string (aborted)");
E 6
		cleanup();
D 6
		return(1);
E 6
I 6
		return (1);
E 6
	}

	(void)signal(SIGHUP, finish);
	(void)signal(SIGINT, finish);

	if (strcmp(SECURE_STRING, proto_data.secure_msg) != 0) {
		cleanup();
		/* don't complain loud if user just hit return */
		if (pass == NULL || (!*pass))
D 6
			return(0);
E 6
I 6
			return (0);
E 6
		(void)fprintf(stderr, "Sorry\n");
D 6
		return(1);
E 6
I 6
		return (1);
E 6
	}

	(void)des_key_sched(proto_data.random_key, random_schedule);
	(void)des_set_key(proto_data.random_key, random_schedule);
D 6
	(void)bzero(pass, sizeof(pass));
E 6
I 6
	(void)memset(pass, 0, sizeof(pass));
E 6

	if (des_read_pw_string(pass,
	    sizeof(pass)-1, "New Kerberos password:", 0)) {
D 6
		(void)fprintf(stderr,
		    "passwd: error reading new Kerberos password (aborted)\n");
E 6
I 6
		warnx("error reading new Kerberos password (aborted)");
E 6
		cleanup();
D 6
		return(1);
E 6
I 6
		return (1);
E 6
	}

	if (des_read_pw_string(password,
	    sizeof(password)-1, "Retype new Kerberos password:", 0)) {
D 6
		(void)fprintf(stderr,
		    "passwd: error reading new Kerberos password (aborted)\n");
E 6
I 6
		warnx("error reading new Kerberos password (aborted)");
E 6
		cleanup();
D 6
		return(1);
E 6
I 6
		return (1);
E 6
	}

	if (strcmp(password, pass) != 0) {
D 6
		(void)fprintf(stderr,
		    "passwd: password mismatch (aborted)\n");
E 6
I 6
		warnx("password mismatch (aborted)");
E 6
		cleanup();
D 6
		return(1);
E 6
I 6
		return (1);
E 6
	}

	if (strlen(pass) == 0)
		(void)printf("using NULL password\n");

	send_update(sock, password, SECURE_STRING);

	/* wait for ACK */

	FD_ZERO(&readfds);
	FD_SET(sock, &readfds);

	rval =
	    select(sock + 1, &readfds, (fd_set *) 0, (fd_set *) 0, &timeout);
	if ((rval < 1) || !FD_ISSET(sock, &readfds)) {
		if(rval == 0) {
D 6
			(void)fprintf(stderr,
			    "passwd: timed out reading ACK (aborted)\n");
E 6
I 6
			warnx("timed out reading ACK (aborted)");
E 6
			cleanup();
			exit(1);
		}
D 6
		(void)fprintf(stderr, "passwd: select failed (aborted)\n");
E 6
I 6
		warnx("select failed (aborted)");
E 6
		cleanup();
		exit(1);
	}
	recv_ack(sock);
	cleanup();
D 6
	exit(0);
E 6
I 6
	return (0);
E 6
}

I 6
static void
E 6
send_update(dest, pwd, str)
	int dest;
	char *pwd, *str;
{
	static struct update_data ud;

D 2
	strncpy(ud.secure_msg, str, _PASSWORD_LEN);
	strncpy(ud.pw, pwd, sizeof(ud.pw));
E 2
I 2
	(void)strncpy(ud.secure_msg, str, _PASSWORD_LEN);
	(void)strncpy(ud.pw, pwd, sizeof(ud.pw));
E 2
	if (des_write(dest, &ud, sizeof(ud)) != sizeof(ud)) {
D 6
		(void)fprintf(stderr,
		    "passwd: couldn't write pw update (abort)\n");
D 2
		bzero(ud, sizeof(ud));
E 2
I 2
		bzero((char *)&ud, sizeof(ud));
E 6
I 6
		warnx("couldn't write pw update (abort)");
		memset((char *)&ud, 0, sizeof(ud));
E 6
E 2
		cleanup();
		exit(1);
	}
}

I 6
static void
E 6
recv_ack(remote)
	int remote;
{
	int cc;
	char buf[BUFSIZ];

	cc = des_read(remote, buf, sizeof(buf));
	if (cc <= 0) {
D 6
		(void)fprintf(stderr,
		    "passwd: error reading acknowledgement (aborted)\n");
E 6
I 6
		warnx("error reading acknowledgement (aborted)");
E 6
		cleanup();
		exit(1);
	}
	(void)printf("%s", buf);
}

I 6
static void
E 6
cleanup()
{
D 2
	(void)bzero(&proto_data, sizeof(proto_data));
	(void)bzero(okey, sizeof(okey));
	(void)bzero(osched, sizeof(osched));
	(void)bzero(random_schedule, sizeof(random_schedule));
E 2
I 2
D 6
	(void)bzero((char *)&proto_data, sizeof(proto_data));
	(void)bzero((char *)okey, sizeof(okey));
	(void)bzero((char *)osched, sizeof(osched));
	(void)bzero((char *)random_schedule, sizeof(random_schedule));
E 6
I 6

	(void)memset((char *)&proto_data, 0, sizeof(proto_data));
	(void)memset((char *)okey, 0, sizeof(okey));
	(void)memset((char *)osched, 0, sizeof(osched));
	(void)memset((char *)random_schedule, 0, sizeof(random_schedule));
E 6
E 2
}

I 4
static void
E 4
finish()
{
I 6

E 6
	(void)close(sock);
	exit(1);
}

#endif /* KERBEROS */
E 1
