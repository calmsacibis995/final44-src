h42225
s 00005/00005/00402
d D 8.1 93/06/06 14:11:57 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00000/00401
d D 6.9 92/01/28 14:01:58 bostic 9 8
c don't let users create their own symbol table for the running kernel
e
s 00056/00018/00345
d D 6.8 91/03/02 18:07:14 bostic 8 7
c ANSI
e
s 00001/00011/00362
d D 6.7 90/06/01 19:04:33 bostic 7 6
c new copyright notice
e
s 00002/00002/00371
d D 6.6 90/03/05 12:28:41 bostic 6 5
c make work with ANSI C preprocessor
e
s 00001/00001/00372
d D 6.5 89/05/11 14:32:02 bostic 5 4
c file reorg, pathnames.h, paths.h
e
s 00005/00001/00368
d D 6.4 89/04/02 15:46:38 bostic 4 3
c add pathnames.h
e
s 00004/00002/00365
d D 6.3 88/09/20 16:22:14 bostic 3 2
c checked in for Keith Sklower; bring up to date
e
s 00016/00005/00351
d D 6.2 88/07/01 08:36:08 bostic 2 1
c add Berkeley specific copyright
e
s 00356/00000/00000
d D 6.1 85/10/08 22:42:43 sklower 1 0
c date and time created 85/10/08 22:42:43 by sklower
e
u
U
t
This manual page documents a tool used for debugging failures in
the Xerox NS Sequenced packet protocol layer.  It is adapted from
the Internet equivalent trpt(8c).
T
I 1
/*
D 10
 * Copyright (c) 1985 Regents of the University of California.
D 2
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 2
I 2
 * All rights reserved.
E 10
I 10
 * Copyright (c) 1985, 1993
 *	The Regents of the University of California.  All rights reserved.
E 10
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
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 7
I 7
 * %sccs.include.redist.c%
E 7
E 2
 */

#ifndef lint
D 10
char copyright[] =
D 2
"%Z% Copyright (c) 1980 Regents of the University of California.\n\
E 2
I 2
"%Z% Copyright (c) 1985 Regents of the University of California.\n\
E 2
 All rights reserved.\n";
E 10
I 10
static char copyright[] =
"%Z% Copyright (c) 1985, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 10
D 2
#endif not lint
E 2
I 2
#endif /* not lint */
E 2

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 2
#endif not lint
E 2
I 2
#endif /* not lint */
E 2

I 8
#include <sys/cdefs.h>
E 8
#include <sys/param.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
#define PRUREQUESTS
#include <sys/protosw.h>

#include <net/route.h>
#include <net/if.h>

#define TCPSTATES
#include <netinet/tcp_fsm.h>
#define	TCPTIMERS
#include <netinet/tcp_timer.h>

#include <netns/ns.h>
D 8
#include <netns/ns_pcb.h>
#include <netns/idp.h>
#include <netns/idp_var.h>
E 8
#include <netns/sp.h>
I 8
#include <netns/idp.h>
E 8
#include <netns/spidp.h>
I 3
#include <netns/spp_timer.h>
E 3
#include <netns/spp_var.h>
I 8
#include <netns/ns_pcb.h>
#include <netns/idp_var.h>
E 8
#define SANAMES
#include <netns/spp_debug.h>

#include <stdio.h>
#include <errno.h>
#include <nlist.h>
I 4
D 5
#include "pathnames.h"
E 5
I 5
#include <paths.h>
E 5
E 4

unsigned long	ntime;
int	sflag;
int	tflag;
int	jflag;
int	aflag;
int	zflag;
int	numeric();
struct	nlist nl[] = {
	{ "_spp_debug" },
	{ "_spp_debx" },
	0
};
struct	spp_debug spp_debug[SPP_NDEBUG];
caddr_t	spp_pcbs[SPP_NDEBUG];
int	spp_debx;

main(argc, argv)
	int argc;
	char **argv;
{
	int i, mask = 0, npcbs = 0;
D 4
	char *system = "/vmunix", *core = "/dev/kmem";
E 4
I 4
	char *system, *core;

	system = _PATH_UNIX;
	core = _PATH_KMEM;
E 4

	argc--, argv++;
again:
	if (argc > 0 && !strcmp(*argv, "-a")) {
		aflag++, argc--, argv++;
		goto again;
	}
	if (argc > 0 && !strcmp(*argv, "-z")) {
		zflag++, argc--, argv++;
		goto again;
	}
	if (argc > 0 && !strcmp(*argv, "-s")) {
		sflag++, argc--, argv++;
		goto again;
	}
	if (argc > 0 && !strcmp(*argv, "-t")) {
		tflag++, argc--, argv++;
		goto again;
	}
	if (argc > 0 && !strcmp(*argv, "-j")) {
		jflag++, argc--, argv++;
		goto again;
	}
	if (argc > 0 && !strcmp(*argv, "-p")) {
		argc--, argv++;
		if (argc < 1) {
			fprintf(stderr, "-p: missing sppcb address\n");
			exit(1);
		}
		if (npcbs >= SPP_NDEBUG) {
			fprintf(stderr, "-p: too many pcb's specified\n");
			exit(1);
		}
		sscanf(*argv, "%x", &spp_pcbs[npcbs++]);
		argc--, argv++;
		goto again;
	}
	if (argc > 0) {
		system = *argv;
		argc--, argv++;
		mask++;
I 9
		/*
		 * Discard setgid privileges if not the running kernel so that
		 * bad guys can't print interesting stuff from kernel memory.
		 */
		setgid(getgid());
E 9
	}
	if (argc > 0) {
		core = *argv;
		argc--, argv++;
		mask++;
I 9
		setgid(getgid());
E 9
	}
	(void) nlist(system, nl);
	if (nl[0].n_value == 0) {
		fprintf(stderr, "trsp: %s: no namelist\n", system);
		exit(1);
	}
	(void) close(0);
	if (open(core, 0) < 0) {
		fprintf(stderr, "trsp: "); perror(core);
		exit(2);
	}
	if (mask) {
		nl[0].n_value &= 0x7fffffff;
		nl[1].n_value &= 0x7fffffff;
	}
	(void) lseek(0, nl[1].n_value, 0);
	if (read(0, &spp_debx, sizeof (spp_debx)) != sizeof (spp_debx)) {
		fprintf(stderr, "trsp: "); perror("spp_debx");
		exit(3);
	}
	printf("spp_debx=%d\n", spp_debx);
	(void) lseek(0, nl[0].n_value, 0);
	if (read(0, spp_debug, sizeof (spp_debug)) != sizeof (spp_debug)) {
		fprintf(stderr, "trsp: "); perror("spp_debug");
		exit(3);
	}
	/*
	 * Here, we just want to clear out the old trace data and start over.
	 */
	if (zflag) {
		char *cp = (char *) spp_debug,
		     *cplim = cp + sizeof(spp_debug);
		(void) close(0);
		if (open(core, 2) < 0) {
			fprintf(stderr, "trsp: "); perror(core);
			exit(2);
		}
		while(cp < cplim) *cp++ = 0;
		(void) lseek(0, nl[0].n_value, 0);
		if (write(0, spp_debug, sizeof (spp_debug)) != sizeof (spp_debug)) {
			fprintf(stderr, "trsp: "); perror("spp_debug");
			exit(3);
		}
		(void) lseek(0, nl[1].n_value, 0);
		spp_debx = 0;
		if (write(0, &spp_debx, sizeof (spp_debx)) != sizeof (spp_debx)) {
			fprintf(stderr, "trsp: "); perror("spp_debx");
			exit(3);
		}
		exit(0);
	}
	/*
	 * If no control blocks have been specified, figure
	 * out how many distinct one we have and summarize
	 * them in spp_pcbs for sorting the trace records
	 * below.
	 */
	if (npcbs == 0) {
		for (i = 0; i < SPP_NDEBUG; i++) {
			register int j;
			register struct spp_debug *sd = &spp_debug[i];

			if (sd->sd_cb == 0)
				continue;
			for (j = 0; j < npcbs; j++)
				if (spp_pcbs[j] == sd->sd_cb)
					break;
			if (j >= npcbs)
				spp_pcbs[npcbs++] = sd->sd_cb;
		}
	}
	qsort(spp_pcbs, npcbs, sizeof (caddr_t), numeric);
	if (jflag) {
		char *cp = "";

		for (i = 0; i < npcbs; i++) {
			printf("%s%x", cp, spp_pcbs[i]);
			cp = ", ";
		}
		if (*cp)
			putchar('\n');
		exit(0);
	}
	for (i = 0; i < npcbs; i++) {
		printf("\n%x:\n", spp_pcbs[i]);
		dotrace(spp_pcbs[i]);
	}
	exit(0);
}

dotrace(sppcb)
	register caddr_t sppcb;
{
	register int i;
	register struct spp_debug *sd;

	for (i = spp_debx % SPP_NDEBUG; i < SPP_NDEBUG; i++) {
		sd = &spp_debug[i];
		if (sppcb && sd->sd_cb != sppcb)
			continue;
		ntime = ntohl(sd->sd_time);
		spp_trace(sd->sd_act, sd->sd_ostate, sd->sd_cb, &sd->sd_sp,
		    &sd->sd_si, sd->sd_req);
	}
	for (i = 0; i < spp_debx % SPP_NDEBUG; i++) {
		sd = &spp_debug[i];
		if (sppcb && sd->sd_cb != sppcb)
			continue;
		ntime = ntohl(sd->sd_time);
		spp_trace(sd->sd_act, sd->sd_ostate, sd->sd_cb, &sd->sd_sp,
		    &sd->sd_si, sd->sd_req);
	}
}

ptime(ms)
	int ms;
{

	printf("%03d ", (ms/10) % 1000);
}

numeric(c1, c2)
	caddr_t *c1, *c2;
{
	
	return (*c1 - *c2);
}

spp_trace(act, ostate, asp, sp, si, req)
	short act, ostate;
	struct sppcb *asp, *sp;
	struct spidp *si;
	int req;
{
	u_short seq, ack, len, alo;
	int flags, timer;
	char *cp;

	if(ostate >= TCP_NSTATES) ostate = 0;
	if(act > SA_DROP) act = SA_DROP;
	printf("\n");
	ptime(ntime);
	printf("%s:%s", tcpstates[ostate], sanames[act]);

	if (si != 0) {
		seq = si->si_seq;
		ack = si->si_ack;
		alo = si->si_alo;
		len = si->si_len;
		switch (act) {
		case SA_RESPOND:
		case SA_OUTPUT:
				seq = ntohs(seq);
				ack = ntohs(ack);
				alo = ntohs(alo);
				len = ntohs(len);
		case SA_INPUT:
		case SA_DROP:
			if (aflag) {
				printf("\n\tsna=");
				ns_printhost(&si->si_sna);
				printf("\tdna=");
				ns_printhost(&si->si_dna);
			}
			printf("\n\t");
D 8
#define p1(f)  { printf("%s = %x, ", "f", f); }
			p1(seq); p1(ack); p1(alo); p1(len);
E 8
I 8
#define p1(name, f) { \
	printf("%s = %x, ", name, f); \
 }
			p1("seq", seq);
			p1("ack", ack);
			p1("alo", alo);
			p1("len", len);
E 8
			flags = si->si_cc;
			printf("flags=%x", flags);
I 8
#define pf(name, f) { \
	if (flags & f) { \
		printf("%s%s", cp, name); \
		cp = ","; \
	} \
}
E 8
			if (flags) {
				char *cp = "<";
D 6
#define pf(f) { if (flags&SP_/**/f) { printf("%s%s", cp, "f"); cp = ","; } }
				pf(SP); pf(SA); pf(OB); pf(EM);
E 6
I 6
D 8
#define pf(f) { if (flags&f) { printf("%s%s", cp, "f"); cp = ","; } }
				pf(SP_SP); pf(SP_SA); pf(SP_OB); pf(SP_EM);
E 8
I 8
				pf("SP_SP", SP_SP);
				pf("SP_SA", SP_SA);
				pf("SP_OB", SP_OB);
				pf("SP_EM", SP_EM);
E 8
E 6
				printf(">");
			}
			printf(", ");
D 8
#define p2(f)  { printf("%s = %x, ", "f", si->si_/**/f); }
			p2(sid);p2(did);p2(dt);
E 8
I 8
#define p2(name, f) { \
	printf("%s = %x, ", name, f); \
}
			p2("sid", si->si_sid);
			p2("did", si->si_did);
			p2("dt", si->si_dt);
E 8
			printf("\n\tsna=");
			ns_printhost(&si->si_sna);
			printf("\tdna=");
			ns_printhost(&si->si_dna);
		}
	}
	if(act == SA_USER) {
		printf("\treq=%s", prurequests[req&0xff]);
		if ((req & 0xff) == PRU_SLOWTIMO)
			printf("<%s>", tcptimers[req>>8]);
	}
	printf(" -> %s", tcpstates[sp->s_state]);

	/* print out internal state of sp !?! */
	printf("\n");
	if (sp == 0)
		return;
D 8
#define p3(f)  { printf("%s = %x, ", "f", sp->s_/**/f); }
	if(sflag) {
D 3
		printf("\t"); p3(rack); p3(ralo); p3(snt); p3(flags);
E 3
I 3
		printf("\t"); p3(rack); p3(ralo); p3(smax); p3(snxt); p3(flags);
E 8
I 8
#define p3(name, f)  { \
	printf("%s = %x, ", name, f); \
}
	if (sflag) {
		printf("\t");
		p3("rack", sp->s_rack);
		p3("ralo", sp->s_ralo);
		p3("smax", sp->s_smax);
		p3("snxt", sp->s_snxt);
		p3("flags", sp->s_flags);
E 8
E 3
#undef pf
D 8
#define pf(f) { if (flags&SF_/**/f) { printf("%s%s", cp, "f"); cp = ","; } }
E 8
I 8
#define pf(name, f) { \
	if (flags & f) { \
		printf("%s%s", cp, name); \
		cp = ","; \
	} \
}
E 8
		flags = sp->s_flags;
		if (flags || sp->s_oobflags) {
			char *cp = "<";
D 3
			pf(AK); pf(DELACK); pf(HI); pf(HO);
E 3
I 3
D 8
			pf(ACKNOW); pf(DELACK); pf(HI); pf(HO);
			pf(PI); pf(WIN); pf(RXT); pf(RVD);
E 8
I 8
			pf("ACKNOW", SF_ACKNOW);
			pf("DELACK", SF_DELACK);
			pf("HI", SF_HI);
			pf("HO", SF_HO);
			pf("PI", SF_PI);
			pf("WIN", SF_WIN);
			pf("RXT", SF_RXT);
			pf("RVD", SF_RVD);
E 8
E 3
			flags = sp->s_oobflags;
D 8
			pf(SOOB); pf(IOOB);
E 8
I 8
			pf("SOOB", SF_SOOB);
			pf("IOOB", SF_IOOB);
E 8
			printf(">");
		}
D 8

E 8
	}
	/* print out timers? */
	if (tflag) {
		char *cp = "\t";
		register int i;

		printf("\n\tTIMERS: ");
D 8
		p3(idle); p3(force); p3(rtseq);
E 8
I 8
		p3("idle", sp->s_idle);
		p3("force", sp->s_force);
		p3("rtseq", sp->s_rtseq);
E 8
		for (i = 0; i < TCPT_NTIMERS; i++) {
			if (sp->s_timer[i] == 0)
				continue;
			printf("%s%s=%d", cp, tcptimers[i], sp->s_timer[i]);
			if (i == TCPT_REXMT)
				printf(" (s_rxtshft=%d)", sp->s_rxtshift);
			cp = ", ";
		}
		if (*cp != '\t')
			putchar('\n');
	}
}

ns_printhost(p)
register struct ns_addr *p;
{

	printf("<net:%x%x,host:%4.4x%4.4x%4.4x,port:%x>",
			p->x_net.s_net[0],
			p->x_net.s_net[1],
			p->x_host.s_host[0],
			p->x_host.s_host[1],
			p->x_host.s_host[2],
			p->x_port);

}

E 1
