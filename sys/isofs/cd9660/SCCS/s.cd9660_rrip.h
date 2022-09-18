h12304
s 00013/00019/00101
d D 8.2 94/12/05 21:51:49 mckusick 2 1
c update from mycroft
e
s 00120/00000/00000
d D 8.1 94/01/21 18:28:59 mckusick 1 0
c from Mike Hibler
e
u
U
t
T
I 1
/*-
 * Copyright (c) 1993, 1994
 *	The Regents of the University of California.  All rights reserved.
 *
 * This code is derived from software contributed to Berkeley
 * by Pace Willisson (pace@blitz.com).  The Rock Ridge Extension
 * Support code is derived from software contributed to Berkeley
 * by Atsushi Murai (amurai@spec.co.jp).
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

typedef struct {
D 2
	char 	      type		[ISODCL (  0,    1)];
	unsigned char length		[ISODCL (  2,    2)]; /* 711 */
	unsigned char version		[ISODCL (  3,    3)];
E 2
I 2
	char   type			[ISODCL (  0,    1)];
	u_char length			[ISODCL (  2,    2)]; /* 711 */
	u_char version			[ISODCL (  3,    3)];
E 2
} ISO_SUSP_HEADER;

typedef struct {
	ISO_SUSP_HEADER			h;
D 2
	char mode_l			[ISODCL (  4,    7)]; /* 731 */
	char mode_m			[ISODCL (  8,   11)]; /* 732 */
	char links_l			[ISODCL ( 12,   15)]; /* 731 */
	char links_m			[ISODCL ( 16,   19)]; /* 732 */
	char uid_l			[ISODCL ( 20,   23)]; /* 731 */
	char uid_m			[ISODCL ( 24,   27)]; /* 732 */
	char gid_l			[ISODCL ( 28,   31)]; /* 731 */
	char gid_m			[ISODCL ( 32,   35)]; /* 732 */
E 2
I 2
	char mode			[ISODCL (  4,   11)]; /* 733 */
	char links			[ISODCL ( 12,   19)]; /* 733 */
	char uid			[ISODCL ( 20,   27)]; /* 733 */
	char gid			[ISODCL ( 28,   35)]; /* 733 */
E 2
} ISO_RRIP_ATTR;

typedef struct {
	ISO_SUSP_HEADER			h;
D 2
	char dev_t_high_l		[ISODCL (  4,    7)]; /* 731 */
	char dev_t_high_m		[ISODCL (  8,   11)]; /* 732 */
	char dev_t_low_l		[ISODCL ( 12,   15)]; /* 731 */
	char dev_t_low_m		[ISODCL ( 16,   19)]; /* 732 */
E 2
I 2
	char dev_t_high			[ISODCL (  4,   11)]; /* 733 */
	char dev_t_low			[ISODCL ( 12,   19)]; /* 733 */
E 2
} ISO_RRIP_DEVICE;

#define	ISO_SUSP_CFLAG_CONTINUE	0x01
#define	ISO_SUSP_CFLAG_CURRENT	0x02
#define	ISO_SUSP_CFLAG_PARENT	0x04
#define	ISO_SUSP_CFLAG_ROOT	0x08
#define	ISO_SUSP_CFLAG_VOLROOT	0x10
#define	ISO_SUSP_CFLAG_HOST	0x20

typedef struct {
	u_char cflag			[ISODCL (  1,    1)];
	u_char clen			[ISODCL (  2,    2)];
D 2
	u_char name			[0];
E 2
I 2
	u_char name			[1];			/* XXX */
E 2
} ISO_RRIP_SLINK_COMPONENT;
#define	ISO_RRIP_SLSIZ	2

typedef struct {
	ISO_SUSP_HEADER			h;
	u_char flags			[ISODCL (  4,    4)];
	u_char component		[ISODCL (  5,    5)];
} ISO_RRIP_SLINK;

typedef struct {
	ISO_SUSP_HEADER			h;
	char flags			[ISODCL (  4,    4)];
} ISO_RRIP_ALTNAME;

typedef struct {
	ISO_SUSP_HEADER			h;
	char dir_loc			[ISODCL (  4,    11)]; /* 733 */
} ISO_RRIP_CLINK;

typedef struct {
	ISO_SUSP_HEADER			h;
	char dir_loc			[ISODCL (  4,    11)]; /* 733 */
} ISO_RRIP_PLINK;

typedef struct {
	ISO_SUSP_HEADER			h;
} ISO_RRIP_RELDIR;

#define	ISO_SUSP_TSTAMP_FORM17	0x80
#define	ISO_SUSP_TSTAMP_FORM7	0x00
#define	ISO_SUSP_TSTAMP_CREAT	0x01
#define	ISO_SUSP_TSTAMP_MODIFY	0x02
#define	ISO_SUSP_TSTAMP_ACCESS	0x04
#define	ISO_SUSP_TSTAMP_ATTR	0x08
#define	ISO_SUSP_TSTAMP_BACKUP	0x10
#define	ISO_SUSP_TSTAMP_EXPIRE	0x20
#define	ISO_SUSP_TSTAMP_EFFECT	0x40

typedef struct {
	ISO_SUSP_HEADER			h;
D 2
	unsigned char flags		[ISODCL (  4,    4)];
	unsigned char time		[ISODCL (  5,    5)];
E 2
I 2
	u_char flags			[ISODCL (  4,    4)];
	u_char time			[ISODCL (  5,    5)];
E 2
} ISO_RRIP_TSTAMP;

typedef struct {
	ISO_SUSP_HEADER			h;
D 2
	unsigned char flags		[ISODCL (  4,    4)];
E 2
I 2
	u_char flags			[ISODCL (  4,    4)];
E 2
} ISO_RRIP_IDFLAG;

typedef struct {
	ISO_SUSP_HEADER			h;
	char len_id			[ISODCL (  4,    4)];
	char len_des			[ISODCL (  5,	 5)];
	char len_src			[ISODCL (  6,	 6)];
	char version			[ISODCL (  7,	 7)];
} ISO_RRIP_EXTREF;

typedef struct {
	ISO_SUSP_HEADER			h;
	char check			[ISODCL (  4,	 5)];
	char skip			[ISODCL (  6,	 6)];
} ISO_RRIP_OFFSET;

typedef struct {
	ISO_SUSP_HEADER			h;
	char location			[ISODCL (  4,	11)];
	char offset			[ISODCL ( 12,	19)];
	char length			[ISODCL ( 20,	27)];
} ISO_RRIP_CONT;
E 1
