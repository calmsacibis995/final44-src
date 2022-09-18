h08229
s 00002/00000/00177
d D 1.4 92/07/19 15:43:14 bostic 4 3
c This file was not locked, but had been modified.
c Figured I'd put it on a delta, sure hope it works.  ;-}
e
s 00001/00001/00176
d D 1.3 89/05/17 22:09:04 kfall 3 2
c use getstr instead of fgets
e
s 00023/00021/00154
d D 1.2 89/02/03 23:20:24 kfall 2 1
c avoid gets(), show what ticket we're trying for, 
c also, this led to changes in kname_parse.c in the library to allow 
c for instance names containing periods., some general cleanup as well
e
s 00175/00000/00000
d D 1.1 89/02/03 22:03:47 kfall 1 0
c date and time created 89/02/03 22:03:47 by kfall
e
u
U
t
T
I 1
/*
 * $Source: /mit/kerberos/src/kuser/RCS/kinit.c,v $
 * $Author: jtkohl $ 
 *
 * Copyright 1987, 1988 by the Massachusetts Institute of Technology. 
 *
 * For copying and distribution information, please see the file
 * <mit-copyright.h>. 
 *
 * Routine to initialize user to Kerberos.  Prompts optionally for
 * user, instance and realm.  Authenticates user and gets a ticket
 * for the Kerberos ticket-granting service for future use. 
 *
 * Options are: 
 *
 *   -i[instance]
 *   -r[realm]
 *   -v[erbose]
 *   -l[ifetime]
 */

#ifndef	lint
static char rcsid_kinit_c[] =
"$Header: kinit.c,v 4.11 89/01/23 09:34:49 jtkohl Exp $";
#endif	lint

D 2
#include <mit-copyright.h>
E 2
I 2
#include <kerberos/mit-copyright.h>
E 2
#include <stdio.h>
#include <pwd.h>
D 2
#include <krb.h>
E 2
I 2
#include <kerberos/krb.h>
E 2

D 2
#ifdef	PC
#define	LEN	64		/* just guessing */
#endif	PC

#ifdef	BSD42
E 2
#include <strings.h>
#include <sys/param.h>
D 2
#if 	defined(ultrix) || defined(sun)
#define LEN	64
#else
#define	LEN	MAXHOSTNAMELEN
#endif	/* defined(ultrix) || defined(sun) */
#endif	/* BSD42 */
E 2

D 2
#define	LIFE	96	/* lifetime of ticket in 5-minute units */
E 2
I 2
#define	LEN		MAXHOSTNAMELEN
#define	LIFE		96 	/* tick lifetime in 5-min units<8hrs> */
#define	MAX_LIFE	255	/* maximum life in 5-min units */
E 2

char   *progname;

main(argc, argv)
    char   *argv[];
{
    char    aname[ANAME_SZ];
    char    inst[INST_SZ];
    char    realm[REALM_SZ];
    char    buf[LEN];
    char   *username = NULL;
    int     iflag, rflag, vflag, lflag, lifetime, k_errno;
    register char *cp;
    register i;
I 4
    extern int krb_debug;
    krb_debug = 1;
E 4

    *inst = *realm = '\0';
    iflag = rflag = vflag = lflag = 0;
    lifetime = LIFE;
    progname = (cp = rindex(*argv, '/')) ? cp + 1 : *argv;

    while (--argc) {
	if ((*++argv)[0] != '-') {
	    if (username)
		usage();
	    username = *argv;
	    continue;
	}
	for (i = 1; (*argv)[i] != '\0'; i++)
	    switch ((*argv)[i]) {
	    case 'i':		/* Instance */
		++iflag;
		continue;
	    case 'r':		/* Realm */
		++rflag;
		continue;
	    case 'v':		/* Verbose */
		++vflag;
		continue;
	    case 'l':
		++lflag;
		continue;
	    default:
		usage();
		exit(1);
	    }
    }
    if (username &&
	(k_errno = kname_parse(aname, inst, realm, username))
	!= KSUCCESS) {
	fprintf(stderr, "%s: %s\n", progname, krb_err_txt[k_errno]);
	iflag = rflag = 1;
	username = NULL;
    }
    if (k_gethostname(buf, LEN)) {
	fprintf(stderr, "%s: k_gethostname failed\n", progname);
	exit(1);
    }
D 2
    printf("MIT Project Athena (%s)\n", buf);
E 2
I 2
    printf("MIT Project Athena/UC Berkeley (%s)\n", buf);
E 2
    if (username) {
	printf("Kerberos Initialization for \"%s", aname);
	if (*inst)
	    printf(".%s", inst);
	if (*realm)
	    printf("@%s", realm);
	printf("\"\n");
    } else {
	printf("Kerberos Initialization\n");
	printf("Kerberos name: ");
D 2
	gets(aname);
E 2
I 2
	getstr(aname, ANAME_SZ);
E 2
	if (!*aname)
	    exit(0);
	if (!k_isname(aname)) {
	    fprintf(stderr, "%s: bad Kerberos name format\n",
		    progname);
	    exit(1);
	}
    }
    /* optional instance */
    if (iflag) {
	printf("Kerberos instance: ");
D 2
	gets(inst);
E 2
I 2
	getstr(inst, INST_SZ);
E 2
	if (!k_isinst(inst)) {
	    fprintf(stderr, "%s: bad Kerberos instance format\n",
		    progname);
	    exit(1);
	}
    }
    if (rflag) {
	printf("Kerberos realm: ");
D 2
	gets(realm);
E 2
I 2
D 3
	fgets(realm, REALM_SZ);
E 3
I 3
	getstr(realm, REALM_SZ);
E 3
E 2
	if (!k_isrealm(realm)) {
	    fprintf(stderr, "%s: bad Kerberos realm format\n",
		    progname);
	    exit(1);
	}
    }
    if (lflag) {
	 printf("Kerberos ticket lifetime (minutes): ");
D 2
	 gets(buf);
E 2
I 2
	 getstr(buf, LEN);
E 2
	 lifetime = atoi(buf);
	 if (lifetime < 5)
	      lifetime = 1;
	 else
	      lifetime /= 5;
	 /* This should be changed if the maximum ticket lifetime */
	 /* changes */
D 2
	 if (lifetime > 255)
	      lifetime = 255;
E 2
I 2
	 if (lifetime > MAX_LIFE)
	      lifetime = MAX_LIFE;
E 2
    }
    if (!*realm && krb_get_lrealm(realm, 1)) {
	fprintf(stderr, "%s: krb_get_lrealm failed\n", progname);
	exit(1);
    }
I 2
    printf("Getting initial ticket for %s.%s@%s\n",
	aname, inst, realm);
E 2
    k_errno = krb_get_pw_in_tkt(aname, inst, realm, "krbtgt", realm,
				lifetime, 0);
    if (vflag) {
	printf("Kerberos realm %s:\n", realm);
	printf("%s\n", krb_err_txt[k_errno]);
    } else if (k_errno) {
	fprintf(stderr, "%s: %s\n", progname, krb_err_txt[k_errno]);
	exit(1);
    }
}

usage()
{
    fprintf(stderr, "Usage: %s [-irvl] [name]\n", progname);
    exit(1);
I 2
}

getstr(p, len)
	register char	*p;
	int		len;
{
	while(((*p++ = getchar()) != '\n') && --len)
		;
	*--p = '\0';
E 2
}
E 1
