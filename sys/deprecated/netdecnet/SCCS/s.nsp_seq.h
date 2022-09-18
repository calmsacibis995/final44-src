h54305
s 00000/00000/00017
d D 1.3 82/10/09 05:49:19 wnj 3 2
c fix header files
e
s 00001/00000/00016
d D 1.2 82/05/15 21:53:00 sam 2 1
c add keywords
e
s 00016/00000/00000
d D 1.1 82/05/15 21:46:22 sam 1 0
c date and time created 82/05/15 21:46:22 by sam
e
u
U
t
T
I 2
/*	%M%	%I%	%E%	*/
E 2
I 1

/*
 * NSP sequence numbers are 12 bit integers operated
 * on with modular arithmetic.  These macros can be
 * used to compare and perform arithmetic on such integers.
 */
#define	MAXSEQ	(1<<12)
#define	SEQMASK	(MAXSEQ-1)

#define	SEQ_LSS(a, b)	(nsp_seqcmp(a, b) < 0)
#define	SEQ_LEQ(a, b)	(nsp_seqcmp(a, b) <= 0)
#define	SEQ_GTR(a, b)	(nsp_seqcmp(a, b) > 0)
#define	SEQ_GEQ(a, b)	(nsp_seqcmp(a, b) >= 0)

#define	SEQ_ADD(a, b)	(((a) + (b)) & SEQMASK)
#define	SEQ_SUB(a, b)	(((a) - (b)) & SEQMASK)
E 1
