h38283
s 00005/00005/00280
d D 8.1 93/06/01 23:15:06 bostic 14 13
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00010/00014/00275
d D 5.1 91/02/25 15:46:11 bostic 13 12
c ANSI fixes, yank to rev 5.1, fix the copyright notices
e
s 00001/00001/00288
d D 1.12 90/09/06 01:25:59 kfall 12 11
c call get_lrealm with 0 2nd arg to not use KRB_REALM define
e
s 00028/00020/00261
d D 1.11 90/06/22 18:54:19 kfall 11 10
c cleanup
e
s 00003/00003/00278
d D 1.10 90/05/11 23:48:26 kfall 10 9
c clean up error message when unable to open keyfile
e
s 00000/00000/00281
d D 1.9 90/05/11 23:29:07 kfall 9 8
c no change
e
s 00002/00001/00279
d D 1.8 90/05/11 23:25:31 kfall 8 7
c new Makefile (for new make), now includes kerberosIV/des.h, 
c broke out make_keypair and registerd to other directories
e
s 00001/00001/00279
d D 1.7 89/08/21 18:14:35 kfall 7 6
c fix syntax error
e
s 00019/00017/00261
d D 1.6 89/08/21 18:02:18 kfall 6 5
c filesystem reorg
e
s 00043/00014/00235
d D 1.5 89/05/17 22:42:28 kfall 5 4
c account for aborting registration
e
s 00021/00009/00228
d D 1.4 89/03/13 23:32:32 kfall 4 3
c remote errors handled correctly, no null pw's, use new library calls
e
s 00001/00000/00236
d D 1.3 88/12/12 22:54:55 kfall 3 2
c include signal.h
e
s 00012/00001/00224
d D 1.2 88/12/12 22:53:57 kfall 2 1
c add SIGPIPE stuff
e
s 00225/00000/00000
d D 1.1 88/12/12 20:54:57 kfall 1 0
c date and time created 88/12/12 20:54:57 by kfall
e
u
U
t
T
I 5
D 13
/*
E 13
I 13
/*-
E 13
D 14
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 14
I 14
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 14
 *
D 13
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 13
I 13
 * %sccs.include.redist.c%
E 13
 */

#ifndef lint
I 13
D 14
char copyright[] =
"%Z% Copyright (c) 1989 The Regents of the University of California.\n\
 All rights reserved.\n";
E 14
I 14
static char copyright[] =
"%Z% Copyright (c) 1989, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 14
#endif /* not lint */

#ifndef lint
E 13
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

E 5
I 1
#include <sys/types.h>
I 11
#include <sys/param.h>
E 11
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/socket.h>
I 11
#include <sys/file.h>
#include <sys/signal.h>
#include <netinet/in.h>
#include <pwd.h>
E 11
#include <stdio.h>
#include <netdb.h>
D 11
#include <netinet/in.h>
E 11
D 6
#include <kerberos/krb.h>
E 6
I 6
D 8
#include <krb.h>
E 8
I 8
#include <kerberosIV/des.h>
#include <kerberosIV/krb.h>
E 8
E 6
D 11
#include <sys/param.h>
#include <sys/file.h>
I 3
#include <sys/signal.h>
E 11
I 6
#include "pathnames.h"
E 6
E 3
#include "register_proto.h"

D 11
#define	SERVICE	"krbupdate"
E 11
I 11
#define	SERVICE	"krbupdate"	/* service to add to KDC's database */
E 11
#define	PROTO	"tcp"
D 6
#define	KFILE	"/.update.key%s"
D 4
#define	KPASSWD	"/usr/local/kpasswd"
E 4
I 4
#define	KPASSWD	"/usr/athena/kpasswd"
E 6
E 4

char	realm[REALM_SZ];
char	krbhst[MAX_HSTNM];

static	char	pname[ANAME_SZ];
static	char	iname[INST_SZ];
D 11
static	char	password[255];
E 11
I 11
static	char	password[_PASSWORD_LEN];
E 11

D 11
extern char	*sys_errlist;
E 11
I 11
/* extern char	*sys_errlist; */
E 11
I 2
D 13
int	die();
E 13
I 13
void	die();
E 13
I 11
void	setup_key(), type_info(), cleanup();
E 11
E 2

main(argc, argv)
D 11
int	argc;
char	**argv;
E 11
I 11
	int	argc;
	char	**argv;
E 11
{
	struct servent	*se;
	struct hostent	*host;
	struct sockaddr_in	sin, local;
	int		rval;
	int		sock, llen;
	u_char		code;
	static struct rlimit rl = { 0, 0 };

D 4
	if(geteuid()) {
		fprintf(stderr, "must run set-uid root to access keyfile\n");
		exit(1);
	}

E 4
I 2
	signal(SIGPIPE, die);

E 2
D 5
	if(setrlimit(RLIMIT_CORE, &rl) < 0) {
E 5
I 5
	if (setrlimit(RLIMIT_CORE, &rl) < 0) {
E 5
		perror("rlimit");
		exit(1);
	}

D 5
	if((se = getservbyname(SERVICE, PROTO)) == NULL) {
E 5
I 5
	if ((se = getservbyname(SERVICE, PROTO)) == NULL) {
E 5
		fprintf(stderr, "couldn't find entry for service %s\n",
			SERVICE);
		exit(1);
	}
D 4
	if((rval = get_krbrlm(realm,1)) != KSUCCESS) {
E 4
I 4
D 5
	if((rval = krb_get_lrealm(realm,1)) != KSUCCESS) {
E 5
I 5
D 12
	if ((rval = krb_get_lrealm(realm,1)) != KSUCCESS) {
E 12
I 12
	if ((rval = krb_get_lrealm(realm,0)) != KSUCCESS) {
E 12
E 5
E 4
		fprintf(stderr, "couldn't get local Kerberos realm: %s\n",
			krb_err_txt[rval]);
		exit(1);
	}

D 4
	if((rval = get_krbhst(krbhst, realm, 1)) != KSUCCESS) {
E 4
I 4
D 5
	if((rval = krb_get_krbhst(krbhst, realm, 1)) != KSUCCESS) {
E 5
I 5
	if ((rval = krb_get_krbhst(krbhst, realm, 1)) != KSUCCESS) {
E 5
E 4
		fprintf(stderr, "couldn't get Kerberos host: %s\n",
			krb_err_txt[rval]);
		exit(1);
	}

D 5
	if((host = gethostbyname(krbhst)) == NULL) {
E 5
I 5
	if ((host = gethostbyname(krbhst)) == NULL) {
E 5
		fprintf(stderr, "couldn't get host entry for host %s\n",
			krbhst);
		exit(1);
	}

	sin.sin_family = host->h_addrtype;
D 11
	bcopy(host->h_addr, (char *) &sin.sin_addr, host->h_length);
E 11
I 11
	(void)bcopy(host->h_addr, (char *) &sin.sin_addr, host->h_length);
E 11
	sin.sin_port = se->s_port;

D 5
	if((sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
E 5
I 5
	if ((sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
E 5
		perror("socket");
		exit(1);
	}

D 5
	if(connect(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
E 5
I 5
	if (connect(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
E 5
		perror("connect");
D 11
		close(sock);
E 11
I 11
		(void)close(sock);
E 11
		exit(1);
	}

	llen = sizeof(local);
D 5
	if(getsockname(sock, (struct sockaddr *) &local, &llen) < 0) {
E 5
I 5
	if (getsockname(sock, (struct sockaddr *) &local, &llen) < 0) {
E 5
		perror("getsockname");
D 11
		close(sock);
E 11
I 11
		(void)close(sock);
E 11
		exit(1);
	}

	setup_key(local);

	type_info();
D 5
	get_user_info();
E 5

I 5
	if (!get_user_info()) {
		code = ABORT;
		(void)des_write(sock, &code, 1);
		cleanup();
		exit(1);
	}

E 5
	code = APPEND_DB;
D 6
	if(des_write(sock, &code, 1) != 1) {
E 6
I 6
	if (des_write(sock, &code, 1) != 1) {
E 6
		perror("write 1");
		cleanup();
		exit(1);
	}

D 6
	if(des_write(sock, pname, ANAME_SZ) != ANAME_SZ) {
E 6
I 6
	if (des_write(sock, pname, ANAME_SZ) != ANAME_SZ) {
E 6
		perror("write principal name");
		cleanup();
		exit(1);
	}

D 6
	if(des_write(sock, iname, INST_SZ) != INST_SZ) {
E 6
I 6
	if (des_write(sock, iname, INST_SZ) != INST_SZ) {
E 6
		perror("write instance name");
		cleanup();
		exit(1);
	}

D 6
	if(des_write(sock, password, 255) != 255) {
E 6
I 6
	if (des_write(sock, password, 255) != 255) {
E 6
		perror("write password");
		cleanup();
		exit(1);
	}

	/* get return message */

	{
		int	cc;
		char	msgbuf[BUFSIZ];

I 4
		cc = read(sock, msgbuf, BUFSIZ);
		if (cc <= 0) {
			fprintf(stderr, "protocol error during key verification\n");
			cleanup();
			exit(1);
		}
D 5
		if (strncmp(msgbuf, "GOTKEY", 6) != 0) {
E 5
I 5
		if (strncmp(msgbuf, GOTKEY_MSG, 6) != 0) {
E 5
			fprintf(stderr, "%s: %s", krbhst, msgbuf);
			cleanup();
			exit(1);
		}

E 4
		cc = des_read(sock, msgbuf, BUFSIZ);
D 6
		if(cc <= 0) {
E 6
I 6
		if (cc <= 0) {
E 6
			fprintf(stderr, "protocol error during read\n");
			cleanup();
			exit(1);
		} else {
			printf("%s: %s", krbhst, msgbuf);
		}
	}

	cleanup();
D 11
	close(sock);
E 11
I 11
	(void)close(sock);
E 11
}

I 11
void
E 11
cleanup()
{
	bzero(password, 255);
}

D 11
#include <pwd.h>

E 11
extern	char	*crypt();
extern	char	*getpass();
I 5

int
E 5
get_user_info()
{
	int	uid = getuid();
	int	valid = 0, i;
	struct	passwd	*pw;
	char	*pas, *namep;

I 11
	/* NB: we must run setuid-root to get at the real pw file */

E 11
D 6
	if((pw = getpwuid(uid)) == NULL) {
E 6
I 6
	if ((pw = getpwuid(uid)) == NULL) {
E 6
		fprintf(stderr, "Who are you?\n");
D 5
		exit(1);
E 5
I 5
		return(0);
E 5
	}
I 4
D 11
	seteuid(uid);
E 4
	strcpy(pname, pw->pw_name);	/* principal name */
	for(i = 1; i < 3; i++) {
E 11
I 11
	(void)seteuid(uid);
	(void)strcpy(pname, pw->pw_name);	/* principal name */

	for (i = 1; i < 3; i++) {
E 11
		pas = getpass("login password:");
		namep = crypt(pas, pw->pw_passwd);
D 6
		if(strcmp(namep, pw->pw_passwd)) {
E 6
I 6
		if (strcmp(namep, pw->pw_passwd)) {
E 6
			fprintf(stderr, "Password incorrect\n");
			continue;
		} else {
			valid = 1;
			break;
		}
	}
D 6
	if(!valid)
E 6
I 6
	if (!valid)
E 6
D 5
		exit(1);
E 5
I 5
		return(0);
E 5
	pas = getpass("Kerberos password (may be the same):");
I 4
D 11
	while(*pas == NULL) {
E 11
I 11
	while (*pas == NULL) {
E 11
		printf("<NULL> password not allowed\n");
		pas = getpass("Kerberos password (may be the same):");
	}
E 4
D 11
	strcpy(password, pas);		/* password */
E 11
I 11
	(void)strcpy(password, pas);		/* password */
E 11
	pas = getpass("Retype Kerberos password:");
D 6
	if(strcmp(password, pas)) {
E 6
I 6
	if (strcmp(password, pas)) {
E 6
		fprintf(stderr, "Password mismatch -- aborted\n");
D 5
		cleanup();
		exit(1);
E 5
I 5
		return(0);
E 5
	}

	iname[0] = NULL;	/* null instance name */
I 5
	return(1);
E 5
}

I 11
void
E 11
setup_key(local)
	struct	sockaddr_in	local;
{
	static	struct	keyfile_data	kdata;
	static  Key_schedule		schedule;
	int	fd;
	char	namebuf[MAXPATHLEN];
	extern int errno;

D 6
	sprintf(namebuf, KFILE, inet_ntoa(local.sin_addr));
E 6
I 6
D 7
	(void) sprintf(namebuf, "%s%s"
E 7
I 7
	(void) sprintf(namebuf, "%s%s",
E 7
		CLIENT_KEYFILE,
		inet_ntoa(local.sin_addr));

E 6
	fd = open(namebuf, O_RDONLY);
D 6
	if(fd < 0) {
E 6
I 6
	if (fd < 0) {
E 6
D 10
		fprintf(stderr, "couldn't open key file for local host %s\n",
			inet_ntoa(local.sin_addr));
		perror("open");
E 10
I 10
		fprintf(stderr, "couldn't open key file %s for local host: ",
			namebuf);
		perror("");
E 10
		exit(1);
	}

D 6
	if(read(fd, (char *)&kdata, sizeof(kdata)) != sizeof(kdata)) {
E 6
I 6
	if (read(fd, (char *)&kdata, sizeof(kdata)) != sizeof(kdata)) {
E 6
		fprintf(stderr,"size error reading key file for local host %s\n",
			inet_ntoa(local.sin_addr));
		exit(1);
	}
	key_sched(kdata.kf_key, schedule);
	des_set_key(kdata.kf_key, schedule);
I 11
	return;
E 11
}

I 11
void
E 11
type_info()
{
	printf("Kerberos user registration (realm %s)\n\n", realm);
	printf("Please enter your login password followed by your new Kerberos password.\n");
	printf("The Kerberos password you enter now will be used in the future\n");
D 4
	printf("as your login password for all machines in the %s realm.\n", realm);
E 4
I 4
	printf("as your Kerberos password for all machines in the %s realm.\n", realm);
E 4
	printf("You will only be allowed to perform this operation once, although you may run\n");
D 2
	printf("the %s program to change your Kerberos password\n\n", KPASSWD);
E 2
I 2
D 6
	printf("the %s program from now on to change your Kerberos password.\n\n", KPASSWD);
E 6
I 6
	printf("the %s program from now on to change your Kerberos password.\n\n", _PATH_KPASSWD);
E 6
}

I 11
D 13
int
E 13
I 13
void
E 13
E 11
die()
{
D 6
	fprintf(stderr, "\nServer no longer listeninga\n");
E 6
I 6
	fprintf(stderr, "\nServer no longer listening\n");
E 6
	fflush(stderr);
	cleanup();
	exit(1);
E 2
}
E 1
