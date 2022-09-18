h19705
s 00005/00005/00310
d D 8.1 93/06/01 23:15:56 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00004/00310
d D 5.2 93/05/16 00:36:15 torek 9 8
c ANSI C fixes for gcc2
e
s 00032/00037/00282
d D 5.1 90/11/01 10:36:14 bostic 8 7
c add CRYPT define for rlogin code (local CRYPT -> RCRYPT)
c minor cleanups, add Berkeley copyright
e
s 00003/00002/00316
d D 1.7 90/05/11 23:48:55 kfall 7 6
c now depends on des.h also
e
s 00001/00001/00317
d D 1.6 89/08/21 18:14:44 kfall 6 5
c fix syntax error
e
s 00035/00024/00283
d D 1.5 89/08/21 18:02:21 kfall 5 4
c filesystem reorg
e
s 00031/00003/00276
d D 1.4 89/05/17 22:43:05 kfall 4 3
c deal with abort
e
s 00033/00013/00246
d D 1.3 89/03/13 23:33:46 kfall 3 2
c fix buffering for send_packet, add to protocol for errors on server
e
s 00013/00000/00246
d D 1.2 88/12/12 22:57:04 kfall 2 1
c handle SIGPIPE
e
s 00246/00000/00000
d D 1.1 88/12/12 20:55:11 kfall 1 0
c date and time created 88/12/12 20:55:11 by kfall
e
u
U
t
T
I 4
D 8

/*
 * Copyright (c) 1989 The Regents of the University of California.
E 8
I 8
/*-
D 10
 * Copyright (c) 1990 The Regents of the University of California.
E 8
 * All rights reserved.
E 10
I 10
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 10
 *
D 8
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
E 8
I 8
 * %sccs.include.redist.c%
E 8
 */

#ifndef lint
I 8
D 10
char copyright[] =
"%Z% Copyright (c) 1990 The Regents of the University of California.\n\
 All rights reserved.\n";
E 10
I 10
static char copyright[] =
"%Z% Copyright (c) 1990, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 10
#endif /* not lint */

#ifndef lint
E 8
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

E 4
I 1
#include <sys/types.h>
#include <sys/time.h>
I 2
#include <sys/signal.h>
E 2
#include <sys/resource.h>
#include <sys/param.h>
#include <sys/file.h>
#include <netinet/in.h>
D 8
#include <stdio.h>
E 8
#include <syslog.h>
D 5
#include <kerberos/krb.h>
#include <kerberos/krb_db.h>
E 5
I 5
D 7
#include <krb.h>
#include <krb_db.h>
E 7
I 7
#include <kerberosIV/des.h>
#include <kerberosIV/krb.h>
#include <kerberosIV/krb_db.h>
E 7
D 8
#include "pathnames.h"
E 8
I 8
#include <stdio.h>
E 8
E 5
#include "register_proto.h"
I 8
#include "pathnames.h"
E 8

D 5
#define	SKEYFILE	"/kerberos/update.key%s"
E 5
#define	KBUFSIZ		(sizeof(struct keyfile_data))
I 3
D 8
#define	CRYPT		0x00
E 8
I 8
#define	RCRYPT		0x00
E 8
#define	CLEAR		0x01
E 3

D 8
char	*progname;
E 8
D 9
struct	sockaddr_in	sin;
E 9
I 3
D 8
char	msgbuf[BUFSIZ];
E 8
I 8
char	*progname, msgbuf[BUFSIZ];
E 8
E 3

I 2
D 8
int	die();

E 8
E 2
main(argc, argv)
D 8
char	**argv;
E 8
I 8
	int argc;
	char **argv;
E 8
{
D 8
	int	kf;
	char	keyfile[MAXPATHLEN];
E 8
	static	Key_schedule	schedule;
D 8
	u_char	code;
	char	keybuf[KBUFSIZ];
	int	retval, sval;
	struct	keyfile_data	*kfile;
E 8
	static struct rlimit rl = { 0, 0 };
I 8
	struct	keyfile_data	*kfile;
	u_char	code;
	int	kf, retval, sval;
I 9
	struct	sockaddr_in	sin;
E 9
	char	keyfile[MAXPATHLEN], keybuf[KBUFSIZ];
	void die();
E 8

I 8
	progname = argv[0];		/* for the library routines */

E 8
D 3
	openlog("krbupdated", LOG_CONS | LOG_PID, LOG_AUTH);
E 3
I 3
	openlog("registerd", LOG_PID, LOG_AUTH);
E 3

D 8
	progname = argv[0];
E 8
I 8
	(void)signal(SIGHUP, SIG_IGN);
	(void)signal(SIGINT, SIG_IGN);
	(void)signal(SIGTSTP, SIG_IGN);
	(void)signal(SIGPIPE, die);
E 8

D 8
	signal(SIGHUP, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
I 2
	signal(SIGPIPE, die);
E 8
E 2
D 5
	if(setrlimit(RLIMIT_CORE, &rl) < 0) {
E 5
I 5
	if (setrlimit(RLIMIT_CORE, &rl) < 0) {
E 5
		syslog(LOG_ERR, "setrlimit: %m");
		exit(1);
	}


	/* figure out who we are talking to */

	sval = sizeof(sin);
D 5
	if(getpeername(0, (struct sockaddr *) &sin, &sval) < 0) {
E 5
I 5
	if (getpeername(0, (struct sockaddr *) &sin, &sval) < 0) {
E 5
		syslog(LOG_ERR, "getpeername: %m");
		exit(1);
	}

	/* get encryption key */

D 5
	(void) sprintf(keyfile, SKEYFILE, inet_ntoa(sin.sin_addr));
	if((kf = open(keyfile, O_RDONLY)) < 0) {
		syslog(LOG_ERR, "error opening Kerberos update keyfile (%s): %m", keyfile);
D 3
		send_packet("couldn't open session key file for your host");
E 3
I 3
		(void) sprintf(msgbuf, "couldn't open session keyfile for your host");
E 5
I 5
D 6
	(void) sprintf(keyfile, "%s%s%s"
E 6
I 6
	(void) sprintf(keyfile, "%s%s%s",
E 6
		SERVER_KEYDIR,
		CLIENT_KEYFILE,
		inet_ntoa(sin.sin_addr));

	if ((kf = open(keyfile, O_RDONLY)) < 0) {
		syslog(LOG_ERR,
		    "error opening Kerberos update keyfile (%s): %m", keyfile);
		(void) sprintf(msgbuf,
		    "couldn't open session keyfile for your host");
E 5
		send_packet(msgbuf, CLEAR);
E 3
		exit(1);
	}

D 5
	if(read(kf, keybuf, KBUFSIZ) != KBUFSIZ) {
E 5
I 5
	if (read(kf, keybuf, KBUFSIZ) != KBUFSIZ) {
E 5
		syslog(LOG_ERR, "wrong read size of Kerberos update keyfile");
D 3
		send_packet("couldn't read session key file for your host");
E 3
I 3
D 4
		(void) sprintf(msgbuf, "couldn't read session key from your host's keyfile");
E 4
I 4
		(void) sprintf(msgbuf,
			"couldn't read session key from your host's keyfile");
E 4
		send_packet(msgbuf, CLEAR);
E 3
		exit(1);
	}
I 3
D 4
	(void) sprintf(msgbuf, "GOTKEY");
E 4
I 4
	(void) sprintf(msgbuf, GOTKEY_MSG);
E 4
	send_packet(msgbuf, CLEAR);
E 3
	kfile = (struct keyfile_data *) keybuf;
	key_sched(kfile->kf_key, schedule);
	des_set_key(kfile->kf_key, schedule);

	/* read the command code byte */

D 5
	if(des_read(0, &code, 1) == 1) {
E 5
I 5
	if (des_read(0, &code, 1) == 1) {
E 5

		switch(code) {
		case	APPEND_DB:
D 9
			retval = do_append();
E 9
I 9
			retval = do_append(&sin);
E 9
			break;
I 4
		case	ABORT:
			cleanup();
			close(0);
			exit(0);
E 4
		default:
			retval = KFAILURE;
D 4
			syslog(LOG_NOTICE, "invalid command code on Kerberos update (0x%x)", code);
E 4
I 4
			syslog(LOG_NOTICE,
D 5
				"invalid command code on db update (0x%x)", code);
E 5
I 5
				"invalid command code on db update (0x%x)",
				code);
E 5
E 4
		}

	} else {
		retval = KFAILURE;
D 8
		syslog(LOG_ERR, "couldn't read command code on Kerberos update");
E 8
I 8
		syslog(LOG_ERR,
		    "couldn't read command code on Kerberos update");
E 8
	}

I 2
D 3
syslog(LOG_DEBUG,"read comm code and did append (%d)", retval);

E 2
	code = (u_char) retval;
	if(code != KSUCCESS)
		send_packet(krb_err_txt[code]);
	else
		send_packet("Update complete.");
E 3
I 3
	code = (u_char) retval; 
D 5
	if(code != KSUCCESS) {
E 5
I 5
	if (code != KSUCCESS) {
E 5
		(void) sprintf(msgbuf, "%s", krb_err_txt[code]);
D 5
		send_packet(msgbuf,CRYPT);
E 5
I 5
D 8
		send_packet(msgbuf, CRYPT);
E 8
I 8
		send_packet(msgbuf, RCRYPT);
E 8
E 5
	} else {
		(void) sprintf(msgbuf, "Update complete.");
D 8
		send_packet(msgbuf, CRYPT);
E 8
I 8
		send_packet(msgbuf, RCRYPT);
E 8
	}
E 3
	cleanup();
	close(0);
	exit(0);
}

#define	MAX_PRINCIPAL	10
static	Principal	principal_data[MAX_PRINCIPAL];
static	C_Block		key, master_key;
static Key_schedule	master_key_schedule;
int
D 9
do_append()
E 9
I 9
do_append(sinp)
	struct sockaddr_in *sinp;
E 9
{
	Principal	default_princ;
	char		input_name[ANAME_SZ];
	char		input_instance[INST_SZ];
	int		j,n, more;
	long		mkeyversion;



	/* get master key from MKEYFILE */
D 5
	if(kdb_get_master_key(0, master_key, master_key_schedule) != 0) {
E 5
I 5
	if (kdb_get_master_key(0, master_key, master_key_schedule) != 0) {
E 5
		syslog(LOG_ERR, "couldn't get master key");
		return(KFAILURE);
	}

	mkeyversion = kdb_verify_master_key(master_key, master_key_schedule, NULL);
D 5
	if(mkeyversion < 0) {
E 5
I 5
	if (mkeyversion < 0) {
E 5
		syslog(LOG_ERR, "couldn't validate master key");
		return(KFAILURE);
	}

	n = kerb_get_principal(KERB_DEFAULT_NAME, KERB_DEFAULT_INST,
		&default_princ, 1, &more);

D 5
	if(n != 1) {
E 5
I 5
	if (n != 1) {
E 5
		syslog(LOG_ERR, "couldn't get default principal");
		return(KFAILURE);
	}

	/*
	 * get principal name, instance, and password from network.
	 * convert password to key and store it
	 */

D 5
	if(net_get_principal(input_name, input_instance, key) != 0) {
E 5
I 5
	if (net_get_principal(input_name, input_instance, key) != 0) {
E 5
		return(KFAILURE);
	}


	j = kerb_get_principal(
		input_name,
		input_instance,
		principal_data,
		MAX_PRINCIPAL,
		&more
	);

D 5
	if(j != 0) {
E 5
I 5
	if (j != 0) {
E 5
		/* already in database, no update */
D 5
		syslog(LOG_NOTICE, "attempt to add duplicate entry for principal %s.%s",
E 5
I 5
		syslog(LOG_NOTICE,
			"attempt to add duplicate entry for principal %s.%s",
E 5
			input_name, input_instance);
		return(KDC_PR_N_UNIQUE);
	}

	/*
	 * set up principal's name, instance
	 */

	strcpy(principal_data[0].name, input_name);
	strcpy(principal_data[0].instance, input_instance);
	principal_data[0].old = NULL;


	/* and the expiration date and version #s */

	principal_data[0].exp_date = default_princ.exp_date;
	strcpy(principal_data[0].exp_date_txt, default_princ.exp_date_txt);
	principal_data[0].max_life = default_princ.max_life;
	principal_data[0].attributes = default_princ.attributes;
	principal_data[0].kdc_key_ver = default_princ.kdc_key_ver;


	/* and the key */

	kdb_encrypt_key(key, key, master_key, master_key_schedule,
			ENCRYPT);
	bcopy(key, &principal_data[0].key_low, 4);
	bcopy(((long *) key) + 1, &principal_data[0].key_high,4);
	bzero(key, sizeof(key));

	principal_data[0].key_version = 1;	/* 1st entry */
D 5
	if(kerb_put_principal(&principal_data[0], 1)) {
E 5
I 5

	/* and write it to the database */

	if (kerb_put_principal(&principal_data[0], 1)) {
E 5
		syslog(LOG_INFO, "Kerberos update failure: put_principal failed");
		return(KFAILURE);
	}

	syslog(LOG_NOTICE, "Kerberos update: wrote new record for %s.%s from %s",
		principal_data[0].name,
		principal_data[0].instance,
D 9
		inet_ntoa(sin.sin_addr)
E 9
I 9
		inet_ntoa(sinp->sin_addr)
E 9
	);

	return(KSUCCESS);

}

D 3
send_packet(msg)
E 3
I 3
send_packet(msg,flag)
E 3
	char	*msg;
I 3
	int	flag;
E 3
{
	int	len = strlen(msg);
	msg[len++] = '\n';
	msg[len] = '\0';
D 3
	if(des_write(0, msg, len) != len)
		syslog(LOG_ERR, "couldn't write reply message");
E 3
I 3
	if (len > sizeof(msgbuf)) {
		syslog(LOG_ERR, "send_packet: invalid msg size");
		return;
	}
D 8
	if (flag == CRYPT) {
E 8
I 8
	if (flag == RCRYPT) {
E 8
		if (des_write(0, msg, len) != len)
			syslog(LOG_ERR, "couldn't write reply message");
	} else if (flag == CLEAR) {
		if (write(0, msg, len) != len)
			syslog(LOG_ERR, "couldn't write reply message");
	} else
			syslog(LOG_ERR, "send_packet: invalid flag (%d)", flag);

E 3
}

net_get_principal(pname, iname, keyp)
	char	*pname, *iname;
	C_Block	*keyp;
{
	int	cc;
	static	char	password[255];

	cc = des_read(0, pname, ANAME_SZ);
D 5
	if(cc != ANAME_SZ) {
E 5
I 5
	if (cc != ANAME_SZ) {
E 5
		syslog(LOG_ERR, "couldn't get principal name");
		return(-1);
	}

	cc = des_read(0, iname, INST_SZ);
D 5
	if(cc != INST_SZ) {
E 5
I 5
	if (cc != INST_SZ) {
E 5
		syslog(LOG_ERR, "couldn't get instance name");
		return(-1);
	}

	cc = des_read(0, password, 255);
D 5
	if(cc != 255) {
E 5
I 5
	if (cc != 255) {
E 5
		syslog(LOG_ERR, "couldn't get password");
		bzero(password, 255);
		return(-1);
	}

	string_to_key(password, *keyp);
	bzero(password, 255);
	return(0);
}

cleanup()
{
	bzero(master_key, sizeof(master_key));
	bzero(key, sizeof(key));
	bzero(master_key_schedule, sizeof(master_key_schedule));
I 2
}

I 8
void
E 8
die()
{
	syslog(LOG_ERR, "remote end died (SIGPIPE)");
	cleanup();
	exit(1);
E 2
}
E 1
