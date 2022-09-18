h22228
s 00010/00012/00069
d D 1.2 89/02/03 22:19:21 kfall 2 1
c prepend kerberos to includes, cleanup
e
s 00081/00000/00000
d D 1.1 89/02/03 22:03:45 kfall 1 0
c date and time created 89/02/03 22:03:45 by kfall
e
u
U
t
T
I 1
/*
 * $Source: /mit/kerberos/src/kuser/RCS/kdestroy.c,v $
 * $Author: steiner $ 
 *
 * Copyright 1987, 1988 by the Massachusetts Institute of Technology. 
 *
 * For copying and distribution information, please see the file
 * <mit-copyright.h>. 
 *
 * This program causes Kerberos tickets to be destroyed.
 * Options are: 
 *
 *   -q[uiet]	- no bell even if tickets not destroyed
 *   -f[orce]	- no message printed at all 
 */

D 2
#include <mit-copyright.h>
E 2
I 2
#include <kerberos/mit-copyright.h>
E 2

#ifndef	lint
static char rcsid_kdestroy_c[] =
"$Header: kdestroy.c,v 4.5 88/03/18 15:16:02 steiner Exp $";
#endif	lint

#include <stdio.h>
D 2
#include <krb.h>
#ifdef BSD42
E 2
I 2
#include <kerberos/krb.h>
E 2
#include <strings.h>
D 2
#endif BSD42
E 2

D 2

E 2
static char *pname;

D 2
static usage()
{
    fprintf(stderr, "Usage: %s [-f] [-q]\n", pname);
    exit(1);
}
E 2

main(argc, argv)
    char   *argv[];
{
    int     fflag=0, qflag=0, k_errno;
    register char *cp;

    cp = rindex (argv[0], '/');
    if (cp == NULL)
	pname = argv[0];
    else
	pname = cp+1;

    if (argc > 2)
	usage();
    else if (argc == 2) {
	if (!strcmp(argv[1], "-f"))
	    ++fflag;
	else if (!strcmp(argv[1], "-q"))
	    ++qflag;
	else usage();
    }

    k_errno = dest_tkt();

    if (fflag) {
D 2
	if (k_errno != 0 && k_errno != RET_TKFIL)
E 2
I 2
	if (k_errno != KSUCCESS && k_errno != RET_TKFIL)
E 2
	    exit(1);
	else
	    exit(0);
    } else {
D 2
	if (k_errno == 0)
E 2
I 2
	if (k_errno == KSUCCESS)
E 2
	    printf("Tickets destroyed.\n");
	else if (k_errno == RET_TKFIL)
	    fprintf(stderr, "No tickets to destroy.\n");
	else {
	    fprintf(stderr, "Tickets NOT destroyed.\n");
	    if (!qflag)
		fprintf(stderr, "\007");
	    exit(1);
	}
    }
    exit(0);
I 2
}

static usage()
{
    fprintf(stderr, "Usage: %s [-f] [-q]\n", pname);
    exit(1);
E 2
}
E 1
