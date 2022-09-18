h63177
s 00035/00010/00175
d D 1.2 91/03/07 10:57:56 karels 2 1
c if uid == 0 and USER != "root", default to $USER.root; exit 0, gets!
e
s 00185/00000/00000
d D 1.1 91/03/05 11:15:31 karels 1 0
c from rcs id 4.15
e
u
U
t
T
I 1
/*
 * $Source: /usr/src/kerberosIV/kinit/RCS/kinit.c,v $
 * $Author: kfall $ 
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
"$Header: /usr/src/kerberosIV/kinit/RCS/kinit.c,v 4.15 90/06/25 21:01:06 kfall Exp $";
#endif	lint

#include <sys/types.h>
#include <sys/param.h>
#include <mit-copyright.h>
#include <string.h>
#include <stdio.h>
#include <des.h>
#include <krb.h>
#include <pwd.h>
#include <paths.h>

#define	LEN		MAXHOSTNAMELEN
#define	LIFE		DEFAULT_TKT_LIFE /* in 5-minute units */
#define	INITIAL_TICKET	"krbtgt"

char	*progname;

char    aname[ANAME_SZ];
char    inst[INST_SZ];
char    realm[REALM_SZ];

I 2
#define	gets(buf) _gets(buf, sizeof(buf))	/* hack */

char *
_gets(p, n)
	char *p;
	int n;
{
	char *rv, *fgets();
	
	if ((rv = fgets(p, n, stdin)) == NULL)
		return (rv);
	if (p = index(p, '\n'))
		*p = '\0';
	return (rv);
}

E 2
main(argc, argv)
    char   *argv[];
{
    char    buf[LEN];
    char   *username = NULL;
    int     iflag, rflag, vflag, lflag, lifetime, k_errno;
    register char *cp;
    register i;

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
    if (username && (k_errno = kname_parse(aname, inst, realm, username)) !=
	KSUCCESS) {
	fprintf(stderr, "%s: %s\n", progname, krb_err_txt[k_errno]);
	iflag = rflag = 1;
	username = NULL;
    }
    if (k_gethostname(buf, LEN)) {
	fprintf(stderr, "%s: k_gethostname failed\n", progname);
	exit(1);
    }
D 2
    if (vflag)
    	printf("4.4 BSD/MIT Project Athena (%s)\n", buf);
E 2

    if (username) {
	printf("Kerberos Initialization for \"%s", aname);
	if (*inst)
	    printf(".%s", inst);
	if (*realm)
	    printf("@%s", realm);
	printf("\"\n");
    } else {
	if (iflag) {
		printf("Kerberos Initialization\n");
		printf("Kerberos name: ");
		gets(aname);
	} else {
D 2
		/* default to current user name */
		struct passwd	*pwd = getpwuid(geteuid());
E 2
I 2
		int uid = getuid();
		char *getenv();
		struct passwd *pwd;
E 2

D 2
		if (pwd == (struct passwd *) NULL) {
			fprintf(stderr, "Unknown Kerberos name for your uid\n");
			printf("Kerberos name: ");
			gets(aname);
		} else
			strncpy(aname, pwd->pw_name, sizeof(aname));
E 2
I 2
		/* default to current user name unless running as root */
		if (uid == 0 && (username = getenv("USER")) &&
		    strcmp(username, "root") != 0) {
			strncpy(aname, username, sizeof(aname));
			strncpy(inst, "root", sizeof(inst));
		} else {
			pwd = getpwuid(uid);

			if (pwd == (struct passwd *) NULL) {
				fprintf(stderr, "Unknown name for your uid\n");
				printf("Kerberos name: ");
				gets(aname);
			} else
				strncpy(aname, pwd->pw_name, sizeof(aname));
		}
E 2
	}
		
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
	gets(inst);
	if (!k_isinst(inst)) {
	    fprintf(stderr, "%s: bad Kerberos instance format\n",
		    progname);
	    exit(1);
	}
    }
    if (rflag) {
	printf("Kerberos realm: ");
	gets(realm);
	if (!k_isrealm(realm)) {
	    fprintf(stderr, "%s: bad Kerberos realm format\n",
		    progname);
	    exit(1);
	}
    }
    if (lflag) {
	 printf("Kerberos ticket lifetime (minutes): ");
	 gets(buf);
	 lifetime = atoi(buf);
	 if (lifetime < 5)
	      lifetime = 1;
	 else
	      lifetime /= 5;
	 /* This should be changed if the maximum ticket lifetime */
	 /* changes */
	 if (lifetime > 255)
	      lifetime = 255;
    }
    if (!*realm && krb_get_lrealm(realm, 1)) {
	fprintf(stderr, "%s: krb_get_lrealm failed\n", progname);
	exit(1);
    }

    k_errno = krb_get_pw_in_tkt(aname, inst, realm, INITIAL_TICKET,
		realm, lifetime, 0);

    if (vflag) {
	printf("Kerberos realm %s:\n", realm);
	printf("%s\n", krb_err_txt[k_errno]);
    } else if (k_errno) {
	fprintf(stderr, "%s: %s\n", progname, krb_err_txt[k_errno]);
	exit(1);
    }
I 2
    exit(0);
E 2
}

usage()
{
    fprintf(stderr, "Usage: %s [-irvl] [name]\n", progname);
    exit(1);
}
E 1
