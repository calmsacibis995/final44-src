h36330
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
/*
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
 *
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
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

E 5
I 1
#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <kerberos/krb.h>
#include <sys/param.h>
#include <sys/file.h>
I 3
#include <sys/signal.h>
E 3
#include "register_proto.h"

#define	SERVICE	"krbupdate"
#define	PROTO	"tcp"
#define	KFILE	"/.update.key%s"
D 4
#define	KPASSWD	"/usr/local/kpasswd"
E 4
I 4
#define	KPASSWD	"/usr/athena/kpasswd"
E 4

char	realm[REALM_SZ];
char	krbhst[MAX_HSTNM];

static	char	pname[ANAME_SZ];
static	char	iname[INST_SZ];
static	char	password[255];

extern char	*sys_errlist;
I 2
int	die();
E 2

main(argc, argv)
int	argc;
char	**argv;
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
	if ((rval = krb_get_lrealm(realm,1)) != KSUCCESS) {
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
	bcopy(host->h_addr, (char *) &sin.sin_addr, host->h_length);
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
		close(sock);
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
		close(sock);
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
	if(des_write(sock, &code, 1) != 1) {
		perror("write 1");
		cleanup();
		exit(1);
	}

	if(des_write(sock, pname, ANAME_SZ) != ANAME_SZ) {
		perror("write principal name");
		cleanup();
		exit(1);
	}

	if(des_write(sock, iname, INST_SZ) != INST_SZ) {
		perror("write instance name");
		cleanup();
		exit(1);
	}

	if(des_write(sock, password, 255) != 255) {
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
		if(cc <= 0) {
			fprintf(stderr, "protocol error during read\n");
			cleanup();
			exit(1);
		} else {
			printf("%s: %s", krbhst, msgbuf);
		}
	}

	cleanup();
	close(sock);
}

cleanup()
{
	bzero(password, 255);
}

#include <pwd.h>

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

	if((pw = getpwuid(uid)) == NULL) {
		fprintf(stderr, "Who are you?\n");
D 5
		exit(1);
E 5
I 5
		return(0);
E 5
	}
I 4
	seteuid(uid);
E 4
	strcpy(pname, pw->pw_name);	/* principal name */
	for(i = 1; i < 3; i++) {
		pas = getpass("login password:");
		namep = crypt(pas, pw->pw_passwd);
		if(strcmp(namep, pw->pw_passwd)) {
			fprintf(stderr, "Password incorrect\n");
			continue;
		} else {
			valid = 1;
			break;
		}
	}
	if(!valid)
D 5
		exit(1);
E 5
I 5
		return(0);
E 5
	pas = getpass("Kerberos password (may be the same):");
I 4
	while(*pas == NULL) {
		printf("<NULL> password not allowed\n");
		pas = getpass("Kerberos password (may be the same):");
	}
E 4
	strcpy(password, pas);		/* password */
	pas = getpass("Retype Kerberos password:");
	if(strcmp(password, pas)) {
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

setup_key(local)
	struct	sockaddr_in	local;
{
	static	struct	keyfile_data	kdata;
	static  Key_schedule		schedule;
	int	fd;
	char	namebuf[MAXPATHLEN];
	extern int errno;

	sprintf(namebuf, KFILE, inet_ntoa(local.sin_addr));
	fd = open(namebuf, O_RDONLY);
	if(fd < 0) {
		fprintf(stderr, "couldn't open key file for local host %s\n",
			inet_ntoa(local.sin_addr));
		perror("open");
		exit(1);
	}

	if(read(fd, (char *)&kdata, sizeof(kdata)) != sizeof(kdata)) {
		fprintf(stderr,"size error reading key file for local host %s\n",
			inet_ntoa(local.sin_addr));
		exit(1);
	}
	key_sched(kdata.kf_key, schedule);
	des_set_key(kdata.kf_key, schedule);
}

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
	printf("the %s program from now on to change your Kerberos password.\n\n", KPASSWD);
}

die()
{
	fprintf(stderr, "\nServer no longer listeninga\n");
	fflush(stderr);
	cleanup();
	exit(1);
E 2
}
E 1
