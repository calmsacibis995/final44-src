
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
static char sccsid[] = "@(#)registerd.c	1.4 (Berkeley) 5/17/89";
#endif /* not lint */

#include <sys/types.h>
#include <sys/time.h>
#include <sys/signal.h>
#include <sys/resource.h>
#include <sys/param.h>
#include <sys/file.h>
#include <netinet/in.h>
#include <stdio.h>
#include <syslog.h>
#include <kerberos/krb.h>
#include <kerberos/krb_db.h>
#include "register_proto.h"

#define	SKEYFILE	"/kerberos/update.key%s"
#define	KBUFSIZ		(sizeof(struct keyfile_data))
#define	CRYPT		0x00
#define	CLEAR		0x01

char	*progname;
struct	sockaddr_in	sin;
char	msgbuf[BUFSIZ];

int	die();

main(argc, argv)
char	**argv;
{
	int	kf;
	char	keyfile[MAXPATHLEN];
	static	Key_schedule	schedule;
	u_char	code;
	char	keybuf[KBUFSIZ];
	int	retval, sval;
	struct	keyfile_data	*kfile;
	static struct rlimit rl = { 0, 0 };

	openlog("registerd", LOG_PID, LOG_AUTH);

	progname = argv[0];

	signal(SIGHUP, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGPIPE, die);
	if(setrlimit(RLIMIT_CORE, &rl) < 0) {
		syslog(LOG_ERR, "setrlimit: %m");
		exit(1);
	}


	/* figure out who we are talking to */

	sval = sizeof(sin);
	if(getpeername(0, (struct sockaddr *) &sin, &sval) < 0) {
		syslog(LOG_ERR, "getpeername: %m");
		exit(1);
	}

	/* get encryption key */

	(void) sprintf(keyfile, SKEYFILE, inet_ntoa(sin.sin_addr));
	if((kf = open(keyfile, O_RDONLY)) < 0) {
		syslog(LOG_ERR, "error opening Kerberos update keyfile (%s): %m", keyfile);
		(void) sprintf(msgbuf, "couldn't open session keyfile for your host");
		send_packet(msgbuf, CLEAR);
		exit(1);
	}

	if(read(kf, keybuf, KBUFSIZ) != KBUFSIZ) {
		syslog(LOG_ERR, "wrong read size of Kerberos update keyfile");
		(void) sprintf(msgbuf,
			"couldn't read session key from your host's keyfile");
		send_packet(msgbuf, CLEAR);
		exit(1);
	}
	(void) sprintf(msgbuf, GOTKEY_MSG);
	send_packet(msgbuf, CLEAR);
	kfile = (struct keyfile_data *) keybuf;
	key_sched(kfile->kf_key, schedule);
	des_set_key(kfile->kf_key, schedule);

	/* read the command code byte */

	if(des_read(0, &code, 1) == 1) {

		switch(code) {
		case	APPEND_DB:
			retval = do_append();
			break;
		case	ABORT:
			cleanup();
			close(0);
			exit(0);
		default:
			retval = KFAILURE;
			syslog(LOG_NOTICE,
				"invalid command code on db update (0x%x)", code);
		}

	} else {
		retval = KFAILURE;
		syslog(LOG_ERR, "couldn't read command code on Kerberos update");
	}

	code = (u_char) retval; 
	if(code != KSUCCESS) {
		(void) sprintf(msgbuf, "%s", krb_err_txt[code]);
		send_packet(msgbuf,CRYPT);
	} else {
		(void) sprintf(msgbuf, "Update complete.");
		send_packet(msgbuf, CRYPT);
	}
	cleanup();
	close(0);
	exit(0);
}

#define	MAX_PRINCIPAL	10
static	Principal	principal_data[MAX_PRINCIPAL];
static	C_Block		key, master_key;
static Key_schedule	master_key_schedule;
int
do_append()
{
	Principal	default_princ;
	char		input_name[ANAME_SZ];
	char		input_instance[INST_SZ];
	int		j,n, more;
	long		mkeyversion;



	/* get master key from MKEYFILE */
	if(kdb_get_master_key(0, master_key, master_key_schedule) != 0) {
		syslog(LOG_ERR, "couldn't get master key");
		return(KFAILURE);
	}

	mkeyversion = kdb_verify_master_key(master_key, master_key_schedule, NULL);
	if(mkeyversion < 0) {
		syslog(LOG_ERR, "couldn't validate master key");
		return(KFAILURE);
	}

	n = kerb_get_principal(KERB_DEFAULT_NAME, KERB_DEFAULT_INST,
		&default_princ, 1, &more);

	if(n != 1) {
		syslog(LOG_ERR, "couldn't get default principal");
		return(KFAILURE);
	}

	/*
	 * get principal name, instance, and password from network.
	 * convert password to key and store it
	 */

	if(net_get_principal(input_name, input_instance, key) != 0) {
		return(KFAILURE);
	}


	j = kerb_get_principal(
		input_name,
		input_instance,
		principal_data,
		MAX_PRINCIPAL,
		&more
	);

	if(j != 0) {
		/* already in database, no update */
		syslog(LOG_NOTICE, "attempt to add duplicate entry for principal %s.%s",
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
	if(kerb_put_principal(&principal_data[0], 1)) {
		syslog(LOG_INFO, "Kerberos update failure: put_principal failed");
		return(KFAILURE);
	}

	syslog(LOG_NOTICE, "Kerberos update: wrote new record for %s.%s from %s",
		principal_data[0].name,
		principal_data[0].instance,
		inet_ntoa(sin.sin_addr)
	);

	return(KSUCCESS);

}

send_packet(msg,flag)
	char	*msg;
	int	flag;
{
	int	len = strlen(msg);
	msg[len++] = '\n';
	msg[len] = '\0';
	if (len > sizeof(msgbuf)) {
		syslog(LOG_ERR, "send_packet: invalid msg size");
		return;
	}
	if (flag == CRYPT) {
		if (des_write(0, msg, len) != len)
			syslog(LOG_ERR, "couldn't write reply message");
	} else if (flag == CLEAR) {
		if (write(0, msg, len) != len)
			syslog(LOG_ERR, "couldn't write reply message");
	} else
			syslog(LOG_ERR, "send_packet: invalid flag (%d)", flag);

}

net_get_principal(pname, iname, keyp)
	char	*pname, *iname;
	C_Block	*keyp;
{
	int	cc;
	static	char	password[255];

	cc = des_read(0, pname, ANAME_SZ);
	if(cc != ANAME_SZ) {
		syslog(LOG_ERR, "couldn't get principal name");
		return(-1);
	}

	cc = des_read(0, iname, INST_SZ);
	if(cc != INST_SZ) {
		syslog(LOG_ERR, "couldn't get instance name");
		return(-1);
	}

	cc = des_read(0, password, 255);
	if(cc != 255) {
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
}

die()
{
	syslog(LOG_ERR, "remote end died (SIGPIPE)");
	cleanup();
	exit(1);
}
