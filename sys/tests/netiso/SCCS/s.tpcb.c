h57761
s 00043/00005/00200
d D 7.2 92/07/23 16:56:26 sklower 2 1
c check in for alpha distribution
e
s 00205/00000/00000
d D 7.1 92/05/04 17:52:47 sklower 1 0
c date and time created 92/05/04 17:52:47 by sklower
e
u
U
t
T
I 1
/*-
 * Copyright (c) 1988, 1990 The Regents of the University of California.
 * All rights reserved.
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
char copyright[] =
"%Z% Copyright (c) 1988, 1990 The Regents of the University of California.\n\
 All rights reserved.\n";
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/param.h>
#include <sys/mbuf.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
#include <sys/ioctl.h>
#include <net/route.h>
#include <net/if.h>
#define  TCPT_NTIMERS 4
#include <netiso/iso.h>
#include <netiso/tp_param.h>
#include <netiso/tp_user.h>
#include <netiso/tp_pcb.h>
#include <netiso/tp_events.h>
I 2
#include <netiso/tp_states.h>
E 2

#include <errno.h>
#include <netdb.h>
#include <nlist.h>
#include <kvm.h>
#include <paths.h>
#include <stdio.h>
/*
 * This is a kernel debugging aid.
 * dumps out a tp_pcb.
 */
#define mem(e) (((struct tp_pcb *)0)->e)
#define Offsetof(e) ((int)&mem(e))
#define Sizeof(e) sizeof mem(e)
#if defined(__STDC__) || defined(__cplusplus)
#define Entry(n, e) { #n , Offsetof(e), Sizeof(e), }
#else
#define Entry(n, e) { "n" , Offsetof(e), Sizeof(e), }
#endif
struct tpcb_info {
	char	*name;
	int	offset;
	int	size;
} tpcb_info[];

int tflag = 0;
int Iflag = 0;
int Aflag = 0;
I 2
int Sflag = 1;
E 2

char *vmunix = _PATH_UNIX;
char *kmemf = 0;
struct nlist nl[] = {
I 2
#define TP_REFINFO 0
E 2
{"_tp_refinfo"},
0
};
struct tp_pcb tp_pcb;

#define kget(p, d) \
	(kvm_read((void *)(p), &(d), sizeof (d)))
main(argc, argv)
	int argc;
	char **argv;
{
	int loc, n;
	char *end;
	argc--; argv++;
D 2
	if (strcmp("-k", argv[0]) == 0) {
E 2
I 2
	if ((argc > 0) && strcmp("-k", argv[0]) == 0) {
E 2
		vmunix = argv[1];
		kmemf = argv[2];
		argc -= 3;
		argv += 3;
	}
	if (kvm_openfiles(vmunix, kmemf, NULL) == -1) {
		fprintf(stderr, "tpcb: kvm_openfiles: %s\n", kvm_geterr());
		exit(1);
	}
	if (kvm_nlist(nl) < 0 || nl[0].n_type == 0) {
		fprintf(stderr, "%s: no namelist\n", vmunix);
		exit(1);
	}
	if (argc < 1) {
D 2
		fprintf(stderr, "tpcb: no args");
		exit(1);
E 2
I 2
		doall(nl[TP_REFINFO].n_value);
		exit(0);
E 2
	}
	sscanf(argv[0], "%x", &loc);
	n = kget(loc, tp_pcb);
	parse(--argc, ++argv);
}
I 2
int column;
E 2

#define kdata(t) (data = *(t *)(ti->offset + (char *)&tp_pcb))

I 2
doall(refinfo_off)
off_t refinfo_off;
{
	struct tp_refinfo tp_refinfo;
	register struct tp_pcb **tpp, **tpplim;
	char *tpr_base, *malloc();
	int n;

	kget(refinfo_off, tp_refinfo);
	n = tp_refinfo.tpr_size * sizeof(struct tp_pcb *);
	if (tp_refinfo.tpr_base && (tpr_base = malloc(n))) {
		tpp = (struct tp_pcb **)tpr_base; 
		tpplim = tpp + tp_refinfo.tpr_maxopen;
		bzero(tpr_base, n);
		kvm_read(tp_refinfo.tpr_base, tpr_base, n);
		for (n = 0; tpp <= tpplim; tpp++)
			if (*tpp) {
				n++;
				kget(*tpp, tp_pcb);
				if (Sflag == 0 || tp_pcb.tp_state == TP_OPEN) {
					printf("\n\npcb at 0x%x:\n", *tpp);
					parse(0, (char **)"");
				}
			}
		if (n != tp_refinfo.tpr_numopen)
			printf("\nFound %d of %d expected tpcb's\n",
				n, tp_refinfo.tpr_numopen);
	}
}
E 2
printone(ti)
register struct tpcb_info  *ti;
{
D 2
	static int column = 0; int data = -1;
E 2
I 2
	int data = -1;
E 2
	switch (ti->size) {
	case 1: kdata(u_char); break;
	case 2: kdata(u_short); break;
	case 4: kdata(u_long); break;
	}
	column += printf("%s 0x%x, ", ti->name, data);
D 2
	if (column > 65) {
E 2
I 2
	if (column > 65 || Sflag) {
E 2
		column = 0;
		putchar('\n');
	}
}

parse(argc, argv)
	register int argc;
	register char **argv;
{
	register struct tpcb_info *ti;
I 2
	column = 0;
E 2
	if (argc > 0) {
	    for (; argc-- > 0; argv++)
		for (ti = tpcb_info; ti->name; ti++)
		    if (strcmp(ti->name, *argv) == 0) {
			    printone(ti);
			    break;
		    }
	} else
	    for (ti = tpcb_info; ti->name; ti++)
		printone(ti);
}

struct tpcb_info tpcb_info[] = {
Entry(next, tp_next),
Entry(prev, tp_prev),
Entry(nextlisten, tp_nextlisten),
Entry(state, tp_state),
Entry(retrans, tp_retrans),
Entry(npcb, tp_npcb),
Entry(nlproto, tp_nlproto),
Entry(sock, tp_sock),
Entry(lref, tp_lref),
Entry(fref, tp_fref),
Entry(seqmask, tp_seqmask),
Entry(seqbit, tp_seqbit),
Entry(seqhalf, tp_seqhalf),
Entry(ucddata, tp_ucddata),
I 2
Entry(cebit_off, tp_cebit_off),
Entry(oktonagle, tp_oktonagle),
Entry(flags, tp_flags),
E 2
Entry(fcredit, tp_fcredit),
Entry(maxfcredit, tp_maxfcredit),
Entry(dupacks, tp_dupacks),
Entry(cong_win, tp_cong_win),
Entry(ssthresh, tp_ssthresh),
Entry(snduna, tp_snduna),
Entry(sndnew, tp_sndnew),
Entry(sndnum, tp_sndnum),
Entry(sndnxt, tp_sndnxt),
Entry(sndnxt_m, tp_sndnxt_m),
Entry(Nwindow, tp_Nwindow),
Entry(rcvnxt, tp_rcvnxt),
Entry(sent_lcdt, tp_sent_lcdt),
Entry(sent_uwe, tp_sent_uwe),
Entry(sent_rcvnxt, tp_sent_rcvnxt),
Entry(lcredit, tp_lcredit),
Entry(maxlcredit, tp_maxlcredit),
I 2
Entry(rhiwat, tp_rhiwat),
E 2
Entry(rsyq, tp_rsyq),
Entry(rsycnt, tp_rsycnt),
Entry(win_recv, tp_win_recv),
Entry(l_tpdusize, tp_l_tpdusize),
Entry(rtv, tp_rtv),
Entry(rtt, tp_rtt),
Entry(rttseq, tp_rttseq),
Entry(rttemit, tp_rttemit),
Entry(idle, tp_idle),
Entry(rxtcur, tp_rxtcur),
Entry(rxtshift, tp_rxtshift),
Entry(domain, tp_domain),
Entry(fsuffixlen, tp_fsuffixlen),
Entry(fsuffix, tp_fsuffix[0]),
Entry(lsuffixlen, tp_lsuffixlen),
Entry(lsuffix, tp_lsuffix[0]),
{ "fport", Offsetof(tp_fsuffix[0]), sizeof(short), },
{ "lport", Offsetof(tp_lsuffix[0]), sizeof(short), },
Entry(vers, tp_vers),
Entry(peer_acktime, tp_peer_acktime),
Entry(refstate, tp_refstate),
Entry(fasttimeo, tp_fasttimeo),
Entry(inact, tp_timer[TM_inact]),
Entry(retrans, tp_timer[TM_retrans]),
Entry(sendack, tp_timer[TM_sendack]),
Entry(data_retrans, tp_timer[TM_data_retrans]),
Entry(reference, tp_timer[TM_reference]),
Entry(Xsnd, tp_Xsnd),
Entry(Xsndnxt, tp_Xsndnxt),
Entry(Xuna, tp_Xuna),
Entry(Xrcvnxt, tp_Xrcvnxt),
Entry(s_subseq, tp_s_subseq),
Entry(r_subseq, tp_r_subseq),
Entry(dt_ticks, tp_dt_ticks),
Entry(inact_ticks, tp_inact_ticks),
Entry(keepalive_ticks, tp_keepalive_ticks),
Entry(cr_ticks, tp_cr_ticks),
Entry(xpd_ticks, tp_xpd_ticks),
0};
E 1
