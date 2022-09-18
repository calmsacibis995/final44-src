h35151
s 00035/00021/00025
d D 1.2 89/02/03 23:49:49 kfall 2 1
c many cleanups; don't assume ATHENA.MIT.EDU is realm; 
c don't assume srvtab is in /etc
e
s 00046/00000/00000
d D 1.1 89/02/03 22:03:50 kfall 1 0
c date and time created 89/02/03 22:03:50 by kfall
e
u
U
t
T
I 1
/*
 * $Source: /mit/kerberos/src/kuser/RCS/ksrvtgt.c,v $
 * $Author: steiner $
 *
 * Copyright 1988 by the Massachusetts Institute of Technology. 
 *
 * For copying and distribution information, please see the file
 * <mit-copyright.h>. 
 *
 * Get a ticket-granting-ticket given a service key file (srvtab)
 * The lifetime is the shortest allowed [1 five-minute interval]
 *
 */

#include <stdio.h>
D 2
#include <krb.h>
#include <conf.h>
E 2
I 2
#include <kerberos/krb.h>
#include <kerberos/conf.h>
E 2

const char rcsid[] =
    "$Header: ksrvtgt.c,v 4.2 89/01/13 18:05:19 steiner Exp $";

D 2
char *realm = "ATHENA.MIT.EDU";
char *srvtab = "/etc/srvtab";
E 2
I 2
char	realmbuf[REALM_SZ];
static	char *realm = NULL;
static	char *srvtab = NULL;
static	char srvtabfile[] = KEYFILE;
E 2

main(argc,argv)
D 2
    int argc;
    char **argv;
E 2
I 2
	int argc;
	char **argv;
E 2
{
D 2
    register int code;
    if (argc < 3 || argc > 5) {
	fprintf(stderr, "Usage: %s name instance [[realm] srvtab]\n",
E 2
I 2
	register int code;
	if (argc < 3 || argc > 5) {
		fprintf(stderr, "Usage: %s name instance [[realm] srvtab]\n",
E 2
		argv[0]);
D 2
	exit(1);
    }
    if (argc == 5) {
	realm = argv[3];
	srvtab = argv[4];
    }
    else if (argc == 4)
	srvtab = argv[3];
    code = krb_get_svc_in_tkt(argv[1], argv[2], realm,
E 2
I 2
		exit(1);
	}
	if (argc == 5) {
		realm = argv[3];
		srvtab = argv[4];
	}
	else if (argc == 4)
		srvtab = argv[3];

	if(realm == NULL) {
		if(krb_get_lrealm(realmbuf, 1) != KSUCCESS) {
			fprintf(stderr, "Couldn't get local relm info.\n");
			exit(1);
		}
		realm = realmbuf;
	}

	if(srvtab == NULL)
		srvtab = srvtabfile;

	code = krb_get_svc_in_tkt(argv[1], argv[2], realm,
E 2
			      "krbtgt", realm, 1, srvtab);
D 2
    if (code)
	fprintf(stderr, "%s\n", krb_err_txt[code]);
    exit(code);
E 2
I 2
	if (code != KSUCCESS)
		fprintf(stderr, "%s\n", krb_err_txt[code]);
	exit(code);
E 2
}
E 1
