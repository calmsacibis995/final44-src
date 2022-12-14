h08910
s 00020/00000/00209
d D 1.2 89/05/17 22:50:02 kfall 2 1
c add Berkeley headers
e
s 00209/00000/00000
d D 1.1 88/12/12 20:26:19 kfall 1 0
c date and time created 88/12/12 20:26:19 by kfall
e
u
U
t
T
I 2
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
E 2
I 1

/*
 * kpasswdd - update a principal's passwd field in the Kerberos
 * 	      database.  Called from inetd.
 * K. Fall
 * 12-Dec-88
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/time.h>
#include <syslog.h>
#include <kerberos/krb.h>
#include <kerberos/krb_db.h>
#include <sys/resource.h>
#include <sys/signal.h>
#include <netinet/in.h>
#include "kpasswd_proto.h"

static	struct kpasswd_data	kpwd_data;
static	C_Block			master_key, key;
static	Key_schedule		master_key_schedule,
				key_schedule, random_sched;
int				mkeyversion;
AUTH_DAT			kdata;
static	Principal		principal_data;
static	struct update_data	ud_data;

char				inst[INST_SZ];
char				version[9];
KTEXT_ST			ticket;

char	*progname;		/* for the library */

main()
{
	struct	sockaddr_in	foreign;
	int			foreign_len = sizeof(foreign);
	int			rval, more;
	static  char	name[] = "kpasswdd";

	static	struct rlimit	rl = { 0, 0 };

	progname = name;
	openlog("kpasswdd", LOG_CONS | LOG_PID, LOG_AUTH);

	signal(SIGHUP, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	if(setrlimit(RLIMIT_CORE, &rl) < 0) {
		syslog(LOG_ERR, "setrlimit: %m");
		exit(1);
	}

	if(getpeername(0, &foreign, &foreign_len) < 0) {
		syslog(LOG_ERR,"getpeername: %m");
		exit(1);
	}

	strcpy(inst, "*");
	rval = krb_recvauth(
		0L,				/* !MUTUAL */
		0,				/* file desc */
		&ticket,			/* client's ticket */
		SERVICE,			/* expected service */
		inst,				/* expected instance */
		&foreign,			/* foreign addr */
		(struct sockaddr_in *) 0,	
		&kdata,
		"",
		(bit_64 *) NULL,		/* key schedule */
		version
	);


	if(rval != KSUCCESS) {
		syslog(LOG_ERR, "krb_recvauth: %s", krb_err_txt[rval]);
		cleanup();
		exit(1);
	}


	/* get master key */
	if(kdb_get_master_key(0, master_key, master_key_schedule) != 0) {
		syslog(LOG_ERR, "couldn't get master key");
		cleanup();
		exit(1);
	}

	mkeyversion = 
	   kdb_get_master_key(master_key, master_key_schedule, NULL);


	if(mkeyversion < 0) {
		syslog(LOG_NOTICE, "couldn't verify master key");
		cleanup();
		exit(1);
	}

	/* get principal info */
	rval = kerb_get_principal(
		kdata.pname,
		kdata.pinst,
		&principal_data,
		1,
		&more
	);

	if(rval != 1 || (more != 0)) {
		syslog(LOG_NOTICE, "more than 1 entry for %s.%s",
			kdata.pname, kdata.pinst);
		cleanup();
		exit(1);
	}

	/* get the user's key */

	bcopy(&principal_data.key_low, key, 4);
	bcopy(&principal_data.key_high, ((long *) key) + 1, 4);
	kdb_encrypt_key(key, key, master_key, master_key_schedule,
		DECRYPT);
	key_sched(key, key_schedule);
	des_set_key(key, key_schedule);


	/* get random key and send it over {random} Kperson */

	random_key(kpwd_data.random_key);
	strcpy(kpwd_data.secure_msg, SECURE_STRING);
	if(des_write(0, &kpwd_data, sizeof(kpwd_data)) != sizeof(kpwd_data)) {
		syslog(LOG_ERR, "error writing initial data");
		cleanup();
		exit(1);
	}

	bzero(key, sizeof(key));
	bzero(key_schedule, sizeof(key_schedule));

	/* now read update info: { info }Krandom */

	key_sched(kpwd_data.random_key, random_sched);
	des_set_key(kpwd_data.random_key, random_sched);
	if(des_read(0, &ud_data, sizeof(ud_data)) != sizeof(ud_data)) {
		syslog(LOG_ERR, "update aborted");
		cleanup();
		exit(1);
	}

	/* validate info string by looking at the embedded string */

	if(strcmp(ud_data.secure_msg, SECURE_STRING)) {
		syslog(LOG_NOTICE, "invalid update from %s",
			inet_ntoa(foreign.sin_addr));
		cleanup();
		exit(1);
	}

	/* produce the new key entry in the database { key }Kmaster */
	string_to_key(ud_data.pw, key);
	kdb_encrypt_key(key, key,
		master_key, master_key_schedule,
		ENCRYPT);
	bcopy(key, &principal_data.key_low, 4);
	bcopy(((long *) key) + 1,
		&principal_data.key_high, 4);
	bzero(key, sizeof(key));
	principal_data.key_version++;
	if(kerb_put_principal(&principal_data, 1)) {
		syslog(LOG_ERR, "couldn't write new record for %s.%s",
			principal_data.name, principal_data.instance);
		cleanup();
		exit(1);
	}

	syslog(LOG_NOTICE,"wrote new password field for %s.%s from %s",
		principal_data.name,
		principal_data.instance,
		inet_ntoa(foreign.sin_addr)
	);

	send_ack(0, "Update complete.\n");
	cleanup();
	exit(0);
}

cleanup()
{
	bzero(&kpwd_data, sizeof(kpwd_data));
	bzero(master_key, sizeof(master_key));
	bzero(master_key_schedule, sizeof(master_key_schedule));
	bzero(key, sizeof(key));
	bzero(key_schedule, sizeof(key_schedule));
	bzero(random_sched, sizeof(random_sched));
	bzero(&principal_data, sizeof(principal_data));
	bzero(&ud_data, sizeof(ud_data));
}

send_ack(remote, msg)
	int	remote;
	char	*msg;
{
	int	cc;
	cc = des_write(remote, msg, strlen(msg) + 1);
	if(cc <= 0) {
		syslog(LOG_ERR, "error writing ack");
		cleanup();
		exit(1);
	}
}
E 1
