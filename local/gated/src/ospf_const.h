/*
 * $Id: ospf_const.h,v 1.11.2.1 1994/09/20 15:48:50 jch Exp $
 */

/* %(Copyright.header) */


/* Values are on second boundarys */
#ifndef CONST_H
#define CONST_H
#define	SECONDS	1
#define	MINUTES	60
#define HOURS	(60 * MINUTES)

#define	IfChkAlrmTime	(30)
#define DbAgeTime	(900)
#define	AseAgeTime	(61)
#define LSRefreshTime	(1800)
#define	MinLSInterval	(5)
#define MaxAgeDiff	((u_int) 900)
#define MaxAge		((u_int) 3600)
#define	CheckAge	(300)

/*
 * Every AseAgeTime age ASE_AGE_NDX_ADD hash buckets so we don't
 * cause massive flooding
 * This may be adjusted - change with AseAgeTime
 */
#define ASE_AGE_NDX_ADD       2

/* a few offsets so events occur at the same time very infrequently */
#define OFF1	(37)
#define OFF2	(131)
#define OFF3	(199)
#define OFF4	(263)
#define OFF5	(327)
#define OFF6	(391)

#define BaseSeq		htonl(0x80000000)
#define HBaseSeq	0x80000000	/* host order */
#define FirstSeq	htonl((HBaseSeq) + 1)
#define HFirstSeq	((HBaseSeq) + 1)
#define MaxSeqNum	0x7FFFFFFF

#define	ODIFF(A, B)	((A) > (B) ? (A) - (B) : (B) - (A))

/* for these macros, the version that is held in the lsdb should be B */
#define MORE_RECENT(A, B, Elapse) \
	((s_int32) ntohl((A)->ls_seq) > (s_int32) ntohl((B)->ls_seq) \
	 || ((A)->ls_seq == (B)->ls_seq \
	     && (((A)->ls_chksum != (B)->ls_chksum \
		  && (u_int) ntohs((A)->ls_chksum) > (u_int) ntohs((B)->ls_chksum)) \
		 || ((A)->ls_age == MaxAge \
		     && (B)->ls_age + (u_int) Elapse < MaxAge) \
		 || ((A)->ls_age != MaxAge \
		     && (B)->ls_age + (u_int) Elapse < MaxAge \
		     && ODIFF((A)->ls_age, (B)->ls_age + (u_int) Elapse) > MaxAgeDiff \
		     && (A)->ls_age < ((B)->ls_age + (u_int) Elapse)))))

#define SAME_INSTANCE(A,B,Elapse) \
	((A)->ls_seq == (B)->ls_seq \
	 && (A)->ls_chksum == (B)->ls_chksum \
	 && ((A)->ls_age == MaxAge) == ((B)->ls_age + (u_int) Elapse >= MaxAge) \
	 && ODIFF((A)->ls_age, MIN((B)->ls_age + (u_int) Elapse, MaxAge)) <= MaxAgeDiff)

#define NEXTSEQ(S) ((((S) + 1) == HBaseSeq) ? HFirstSeq : ((S) + 1))

#define NEXTNSEQ(S) (htonl(NEXTSEQ(ntohl(S))))	/* from net to host and back */


#define RTRLSInfinity	0xFFFF
#define SUMLSInfinity	0xFFFFFF
#define ASELSInfinity	0xFFFFFF

#define	OSPF_ADDR_ALLSPF	0xe0000005	/* 224.0.0.5 */
#define	OSPF_ADDR_ALLDR		0xe0000006	/* 224.0.0.6 */

/*
 * Default configuration defines
 */
#define OSPF_BC_DFT_HELLO	10
#define OSPF_NBMA_DFT_HELLO	30
#define OSPF_PTP_DFT_HELLO	30
#define OSPF_VIRT_DFT_HELLO	30

#define OSPF_DFT_RETRANS	5
#define OSPF_VIRT_DFT_RETRANS	30
#define OSPF_DFLT_POLL_INT	120
#define	OSPF_DFLT_TRANSDLY	1
#define	OSPF_VIRT_DFLT_TRANSDLY	4
#define OSPF_DFLT_COST		1

#define	OSPF_T_ACK		1

/* Ls_ase are originated every MinASEInterval over a period of LSRefreshTime
 *    - Just do ASEGenLimit at a time
 * This may be adjusted
*/

#define	ASEGenLimit	100	/* # of LS_ASE generated tq_AseLsa period */
#define	MinASEInterval	(1)	/* Can send ASEGenLimit over this value */

#define OSPF_MAXVPKT  	512	/* Maxmimum tx pkt size less ip hdr stuff */

#endif	/* CONST_H */


/*
 * %(Copyright)
 * %(Copyright.OSPF)
 */
