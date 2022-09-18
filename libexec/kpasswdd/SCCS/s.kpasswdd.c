h58136
s 00005/00005/00240
d D 8.1 93/06/04 18:50:22 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00013/00236
d D 5.1 91/04/12 14:21:20 bostic 7 6
c new copyright; att/bsd/shared
e
s 00004/00004/00245
d D 1.6 91/03/07 16:02:20 karels 6 5
c not so noisy when someone interrupts or mistypes something
e
s 00006/00005/00243
d D 1.5 90/06/22 15:39:26 kfall 5 4
c re-arrange include files
e
s 00032/00013/00216
d D 1.4 90/05/14 14:39:05 kfall 4 3
c new get_principal args, better error handling
e
s 00013/00013/00216
d D 1.3 89/08/21 18:27:01 kfall 3 2
c new location for include files; pretty up
e
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
D 7
/*
 * Copyright (c) 1989 The Regents of the University of California.
E 7
I 7
/*-
D 8
 * Copyright (c) 1990 The Regents of the University of California.
E 7
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
 *
D 7
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
E 7
I 7
 * %sccs.include.redist.c%
E 7
 */
I 7

#ifndef lint
D 8
char copyright[] =
"%Z% Copyright (c) 1990 The Regents of the University of California.\n\
 All rights reserved.\n";
E 8
I 8
static char copyright[] =
"%Z% Copyright (c) 1990, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 8
#endif /* not lint */
E 7

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

D 5
#include <stdio.h>
E 5
#include <sys/types.h>
#include <sys/time.h>
I 5
#include <sys/resource.h>
#include <sys/signal.h>
#include <netinet/in.h>
#include <pwd.h>
E 5
#include <syslog.h>
D 3
#include <kerberos/krb.h>
#include <kerberos/krb_db.h>
E 3
I 3
D 4
#include <krb.h>
#include <krb_db.h>
E 4
I 4
#include <kerberosIV/des.h>
#include <kerberosIV/krb.h>
#include <kerberosIV/krb_db.h>
E 4
E 3
D 5
#include <sys/resource.h>
#include <sys/signal.h>
#include <netinet/in.h>
E 5
I 5
#include <stdio.h>
E 5
#include "kpasswd_proto.h"

static	struct kpasswd_data	kpwd_data;
D 5
static	C_Block			master_key, key;
E 5
I 5
static	des_cblock		master_key, key;
E 5
static	Key_schedule		master_key_schedule,
				key_schedule, random_sched;
D 4
int				mkeyversion;
E 4
I 4
long				mkeyversion;
E 4
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
D 3
	if(setrlimit(RLIMIT_CORE, &rl) < 0) {
E 3
I 3
	if (setrlimit(RLIMIT_CORE, &rl) < 0) {
E 3
		syslog(LOG_ERR, "setrlimit: %m");
		exit(1);
	}

D 3
	if(getpeername(0, &foreign, &foreign_len) < 0) {
E 3
I 3
	if (getpeername(0, &foreign, &foreign_len) < 0) {
E 3
		syslog(LOG_ERR,"getpeername: %m");
		exit(1);
	}

	strcpy(inst, "*");
	rval = krb_recvauth(
D 4
		0L,				/* !MUTUAL */
E 4
I 4
		0L,				/* options--!MUTUAL */
E 4
		0,				/* file desc */
		&ticket,			/* client's ticket */
		SERVICE,			/* expected service */
		inst,				/* expected instance */
		&foreign,			/* foreign addr */
D 4
		(struct sockaddr_in *) 0,	
		&kdata,
		"",
		(bit_64 *) NULL,		/* key schedule */
E 4
I 4
		(struct sockaddr_in *) 0,	/* local addr */
		&kdata,				/* returned krb data */
		"",				/* service keys file */
		(bit_64 *) NULL,		/* returned key schedule */
E 4
		version
	);


D 3
	if(rval != KSUCCESS) {
E 3
I 3
	if (rval != KSUCCESS) {
E 3
D 6
		syslog(LOG_ERR, "krb_recvauth: %s", krb_err_txt[rval]);
E 6
I 6
		syslog(LOG_NOTICE, "krb_recvauth: %s", krb_err_txt[rval]);
E 6
		cleanup();
		exit(1);
	}

I 4
	if (*version == '\0') {
		/* indicates error on client's side (no tickets, etc.) */
		cleanup();
		exit(0);
	} else if (strcmp(version, "KPWDV0.1") != 0) {
		syslog(LOG_NOTICE,
			"kpasswdd version conflict (recv'd %s)",
			version);
		cleanup();
		exit(1);
	}
E 4

I 4

E 4
	/* get master key */
D 3
	if(kdb_get_master_key(0, master_key, master_key_schedule) != 0) {
E 3
I 3
	if (kdb_get_master_key(0, master_key, master_key_schedule) != 0) {
E 3
		syslog(LOG_ERR, "couldn't get master key");
		cleanup();
		exit(1);
	}

D 4
	mkeyversion = 
	   kdb_get_master_key(master_key, master_key_schedule, NULL);
E 4
I 4
	mkeyversion = kdb_get_master_key(NULL, master_key, master_key_schedule);
E 4

D 4

E 4
D 3
	if(mkeyversion < 0) {
E 3
I 3
	if (mkeyversion < 0) {
E 3
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

I 4
	if (rval < 0) {
		syslog(LOG_NOTICE,
			"error retrieving principal record for %s.%s",
			kdata.pname, kdata.pinst);
		cleanup();
		exit(1);
	}

E 4
D 3
	if(rval != 1 || (more != 0)) {
E 3
I 3
	if (rval != 1 || (more != 0)) {
E 3
D 4
		syslog(LOG_NOTICE, "more than 1 entry for %s.%s",
E 4
I 4
		syslog(LOG_NOTICE, "more than 1 dbase entry for %s.%s",
E 4
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
D 3
	if(des_write(0, &kpwd_data, sizeof(kpwd_data)) != sizeof(kpwd_data)) {
E 3
I 3
	if (des_write(0, &kpwd_data, sizeof(kpwd_data)) != sizeof(kpwd_data)) {
E 3
D 6
		syslog(LOG_ERR, "error writing initial data");
E 6
I 6
		syslog(LOG_NOTICE, "error writing initial data");
E 6
		cleanup();
		exit(1);
	}

	bzero(key, sizeof(key));
	bzero(key_schedule, sizeof(key_schedule));

	/* now read update info: { info }Krandom */

	key_sched(kpwd_data.random_key, random_sched);
	des_set_key(kpwd_data.random_key, random_sched);
D 3
	if(des_read(0, &ud_data, sizeof(ud_data)) != sizeof(ud_data)) {
E 3
I 3
	if (des_read(0, &ud_data, sizeof(ud_data)) != sizeof(ud_data)) {
E 3
D 6
		syslog(LOG_ERR, "update aborted");
E 6
I 6
		syslog(LOG_NOTICE, "update aborted");
E 6
		cleanup();
		exit(1);
	}

	/* validate info string by looking at the embedded string */

D 3
	if(strcmp(ud_data.secure_msg, SECURE_STRING)) {
E 3
I 3
D 4
	if (strcmp(ud_data.secure_msg, SECURE_STRING)) {
E 4
I 4
	if (strcmp(ud_data.secure_msg, SECURE_STRING) != 0) {
E 4
E 3
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
D 3
	if(kerb_put_principal(&principal_data, 1)) {
E 3
I 3
	if (kerb_put_principal(&principal_data, 1)) {
E 3
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
D 3
	if(cc <= 0) {
E 3
I 3
	if (cc <= 0) {
E 3
D 6
		syslog(LOG_ERR, "error writing ack");
E 6
I 6
		syslog(LOG_NOTICE, "error writing ack");
E 6
		cleanup();
		exit(1);
	}
}
E 1
