h30221
s 00014/00000/00000
d D 1.1 85/10/14 18:14:46 karels 1 0
c from BBN
e
u
U
t
T
I 1
#define SWS_QFF_MAX    100
#define SWS_QFF_MIN	 5	/* a guess */
#define SWS_QFF_DEC	20	/* applied to connection on ICMP quench */

/*
 * The following were determined by measurement.
 */
#define SWS_IMP		75
#define SWS_ETHER	65

/*
 * Should be for network most likely to be redirected toward.
 */
#define SWS_QFF_DEF	SWS_IMP
E 1
