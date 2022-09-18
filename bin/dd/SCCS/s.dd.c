h19591
s 00002/00002/00367
d D 8.5 94/04/02 09:55:15 pendry 33 32
c add 1994 copyright
e
s 00016/00015/00353
d D 8.4 94/04/02 07:46:04 bostic 32 31
c prototype getfdtype
e
s 00040/00037/00328
d D 8.3 94/04/02 07:39:16 pendry 31 30
c prettyness police
e
s 00005/00001/00360
d D 8.2 94/01/13 12:10:29 bostic 30 29
c Mike Karels at BSDI's changes for osync, to make output padding work
c correctly (this is not POSIX.2, but POSIX.2 is wrong)
e
s 00005/00005/00356
d D 8.1 93/05/31 14:22:21 bostic 29 28
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00002/00353
d D 5.17 93/05/24 15:17:58 bostic 28 27
c when reach "end-of-device" write returns 0 forever
e
s 00009/00007/00346
d D 5.16 93/04/28 16:36:27 bostic 27 26
c bcopy -> memmove, bzero -> memset
e
s 00001/00001/00352
d D 5.15 92/09/22 21:37:12 ralph 26 25
c dumb typo
e
s 00006/00005/00347
d D 5.14 92/09/21 20:19:39 ralph 25 24
c check for write errors before incrementing output counts.
e
s 00004/00003/00348
d D 5.13 92/09/02 15:07:14 bostic 24 23
c fix seek calls for quad's
e
s 00004/00001/00347
d D 5.12 92/06/02 16:31:44 marc 23 22
c add byte count to stats
e
s 00010/00009/00338
d D 5.11 91/08/23 11:57:18 bostic 22 21
c fix of/seek/truncate stuff
e
s 00001/00007/00346
d D 5.10 91/08/14 13:55:56 bostic 21 20
c fix worst-case buffer sizes for non-blocking I/O
e
s 00010/00010/00343
d D 5.9 91/07/29 14:11:31 bostic 20 19
c swab turns off special semantics of bs
e
s 00021/00023/00332
d D 5.8 91/07/29 13:30:45 bostic 19 18
c fix block/unblock, ascii/ebcdic, cbs relationships (extensive)
c check for read/write/seek overflow; move stats into separate structure
c treat odd-length swab errors like truncate errors
e
s 00003/00004/00352
d D 5.7 91/07/27 13:40:29 bostic 18 17
c don't bzero/memset twice, already done before the read
e
s 00010/00010/00346
d D 5.6 91/07/27 13:27:28 bostic 17 16
c allow bs= and C_SWAB to have special bs semantics
e
s 00002/00001/00354
d D 5.5 91/07/27 10:55:17 bostic 16 15
c add Lance Visser to contrib list
e
s 00279/00624/00076
d D 5.4 91/07/26 15:43:26 bostic 15 14
c new version from Keith Muller
e
s 00015/00002/00685
d D 5.3 91/04/04 18:20:34 bostic 14 13
c new copyright; att/bsd/shared
e
s 00007/00002/00680
d D 5.2 91/02/25 07:30:32 bostic 13 12
c ANSI fixes
e
s 00011/00010/00671
d D 5.1 91/02/19 12:01:47 bostic 12 11
c pipe is a libc routine, fix for ANSI C
e
s 00002/00000/00679
d D 4.9 90/08/24 17:47:13 karels 11 10
c print position on ^T
e
s 00001/00001/00678
d D 4.8 90/06/25 10:29:18 karels 10 9
c can't do single-buffering (fflag) with conversions
e
s 00084/00012/00595
d D 4.7 89/12/12 11:13:07 karels 9 7
c fix noerror, sync
e
s 00005/00004/00603
d R 4.7 89/12/10 21:11:28 karels 8 7
c fix conv=noerror (don't treat error as EOF)
e
s 00001/00001/00606
d D 4.6 88/06/01 18:22:10 bostic 7 6
c new _doprnt doesn't support %[A-Z]
e
s 00002/00004/00605
d D 4.5 87/04/07 17:56:31 bostic 6 4
c don't truncate output files; bug report 4.2BSD/bin/43
e
s 00002/00001/00608
d R 4.5 85/04/23 13:48:06 serge 5 4
c don't truncate output file if it exists
e
s 00008/00005/00601
d D 4.4 85/01/22 14:38:51 ralph 4 3
c fix return code
e
s 00001/00001/00605
d D 4.3 83/04/29 01:20:21 mckusick 3 2
c added perror
e
s 00001/00001/00605
d D 4.2 82/07/14 18:26:27 kre 2 1
c fix bug that prevented 'conv=swab' operating on the last
c word in a file that contained an odd number of words.
e
s 00606/00000/00000
d D 4.1 80/10/01 17:26:09 bill 1 0
c date and time created 80/10/01 17:26:09 by bill
e
u
U
t
T
I 14
/*-
D 29
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 29
I 29
D 33
 * Copyright (c) 1991, 1993
E 33
I 33
 * Copyright (c) 1991, 1993, 1994
E 33
 *	The Regents of the University of California.  All rights reserved.
E 29
 *
D 15
 * %sccs.include.proprietary.c%
E 15
I 15
 * This code is derived from software contributed to Berkeley by
D 16
 * Keith Muller of the University of California, San Diego.
E 16
I 16
 * Keith Muller of the University of California, San Diego and Lance
 * Visser of Convex Computer Corporation.
E 16
 *
 * %sccs.include.redist.c%
E 15
 */

E 14
I 4
#ifndef lint
E 4
I 1
D 14
static char *sccsid = "%W% (Berkeley) %G%";
I 4
#endif
E 14
I 14
D 29
char copyright[] =
"%Z% Copyright (c) 1991 The Regents of the University of California.\n\
 All rights reserved.\n";
E 29
I 29
static char copyright[] =
D 33
"%Z% Copyright (c) 1991, 1993\n\
E 33
I 33
"%Z% Copyright (c) 1991, 1993, 1994\n\
E 33
	The Regents of the University of California.  All rights reserved.\n";
E 29
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 14

I 9
D 15
#include <sys/types.h>
E 15
I 15
#include <sys/param.h>
#include <sys/stat.h>
E 15
E 9
I 6
D 12
#include <sys/file.h>
E 12
I 9
#include <sys/ioctl.h>
#include <sys/mtio.h>
D 15
#include <sys/stat.h>
E 15
E 9
E 6
E 4
D 12
#include <stdio.h>
E 12
D 27
#include <signal.h>
I 12
#include <fcntl.h>
#include <unistd.h>
E 27
I 27

#include <ctype.h>
I 31
#include <err.h>
E 31
E 27
I 15
#include <errno.h>
I 27
#include <fcntl.h>
#include <signal.h>
E 27
E 15
#include <stdio.h>
I 15
D 27
#include <ctype.h>
E 27
E 15
I 13
#include <stdlib.h>
#include <string.h>
I 27
#include <unistd.h>

E 27
I 15
#include "dd.h"
#include "extern.h"
E 15
E 13
E 12

D 15
#define	BIG	2147483647
#define	LCASE	01
#define	UCASE	02
#define	SWAB	04
#define NERR	010
#define SYNC	020
int	cflag;
int	fflag;
int	skip;
int	seekn;
int	count;
int	files	= 1;
char	*string;
char	*ifile;
char	*ofile;
char	*ibuf;
char	*obuf;
char	*sbrk();
int	ibs	= 512;
int	obs	= 512;
int	bs;
int	cbs;
int	ibc;
int	obc;
int	cbc;
int	nifr;
int	nipr;
int	nofr;
int	nopr;
int	ntrunc;
int	ibf;
int	obf;
char	*op;
int	nspace;
char	etoa[] = {
	0000,0001,0002,0003,0234,0011,0206,0177,
	0227,0215,0216,0013,0014,0015,0016,0017,
	0020,0021,0022,0023,0235,0205,0010,0207,
	0030,0031,0222,0217,0034,0035,0036,0037,
	0200,0201,0202,0203,0204,0012,0027,0033,
	0210,0211,0212,0213,0214,0005,0006,0007,
	0220,0221,0026,0223,0224,0225,0226,0004,
	0230,0231,0232,0233,0024,0025,0236,0032,
	0040,0240,0241,0242,0243,0244,0245,0246,
	0247,0250,0133,0056,0074,0050,0053,0041,
	0046,0251,0252,0253,0254,0255,0256,0257,
	0260,0261,0135,0044,0052,0051,0073,0136,
	0055,0057,0262,0263,0264,0265,0266,0267,
	0270,0271,0174,0054,0045,0137,0076,0077,
	0272,0273,0274,0275,0276,0277,0300,0301,
	0302,0140,0072,0043,0100,0047,0075,0042,
	0303,0141,0142,0143,0144,0145,0146,0147,
	0150,0151,0304,0305,0306,0307,0310,0311,
	0312,0152,0153,0154,0155,0156,0157,0160,
	0161,0162,0313,0314,0315,0316,0317,0320,
	0321,0176,0163,0164,0165,0166,0167,0170,
	0171,0172,0322,0323,0324,0325,0326,0327,
	0330,0331,0332,0333,0334,0335,0336,0337,
	0340,0341,0342,0343,0344,0345,0346,0347,
	0173,0101,0102,0103,0104,0105,0106,0107,
	0110,0111,0350,0351,0352,0353,0354,0355,
	0175,0112,0113,0114,0115,0116,0117,0120,
	0121,0122,0356,0357,0360,0361,0362,0363,
	0134,0237,0123,0124,0125,0126,0127,0130,
	0131,0132,0364,0365,0366,0367,0370,0371,
	0060,0061,0062,0063,0064,0065,0066,0067,
	0070,0071,0372,0373,0374,0375,0376,0377,
};
char	atoe[] = {
	0000,0001,0002,0003,0067,0055,0056,0057,
	0026,0005,0045,0013,0014,0015,0016,0017,
	0020,0021,0022,0023,0074,0075,0062,0046,
	0030,0031,0077,0047,0034,0035,0036,0037,
	0100,0117,0177,0173,0133,0154,0120,0175,
	0115,0135,0134,0116,0153,0140,0113,0141,
	0360,0361,0362,0363,0364,0365,0366,0367,
	0370,0371,0172,0136,0114,0176,0156,0157,
	0174,0301,0302,0303,0304,0305,0306,0307,
	0310,0311,0321,0322,0323,0324,0325,0326,
	0327,0330,0331,0342,0343,0344,0345,0346,
	0347,0350,0351,0112,0340,0132,0137,0155,
	0171,0201,0202,0203,0204,0205,0206,0207,
	0210,0211,0221,0222,0223,0224,0225,0226,
	0227,0230,0231,0242,0243,0244,0245,0246,
	0247,0250,0251,0300,0152,0320,0241,0007,
	0040,0041,0042,0043,0044,0025,0006,0027,
	0050,0051,0052,0053,0054,0011,0012,0033,
	0060,0061,0032,0063,0064,0065,0066,0010,
	0070,0071,0072,0073,0004,0024,0076,0341,
	0101,0102,0103,0104,0105,0106,0107,0110,
	0111,0121,0122,0123,0124,0125,0126,0127,
	0130,0131,0142,0143,0144,0145,0146,0147,
	0150,0151,0160,0161,0162,0163,0164,0165,
	0166,0167,0170,0200,0212,0213,0214,0215,
	0216,0217,0220,0232,0233,0234,0235,0236,
	0237,0240,0252,0253,0254,0255,0256,0257,
	0260,0261,0262,0263,0264,0265,0266,0267,
	0270,0271,0272,0273,0274,0275,0276,0277,
	0312,0313,0314,0315,0316,0317,0332,0333,
	0334,0335,0336,0337,0352,0353,0354,0355,
	0356,0357,0372,0373,0374,0375,0376,0377,
};
char	atoibm[] =
{
	0000,0001,0002,0003,0067,0055,0056,0057,
	0026,0005,0045,0013,0014,0015,0016,0017,
	0020,0021,0022,0023,0074,0075,0062,0046,
	0030,0031,0077,0047,0034,0035,0036,0037,
	0100,0132,0177,0173,0133,0154,0120,0175,
	0115,0135,0134,0116,0153,0140,0113,0141,
	0360,0361,0362,0363,0364,0365,0366,0367,
	0370,0371,0172,0136,0114,0176,0156,0157,
	0174,0301,0302,0303,0304,0305,0306,0307,
	0310,0311,0321,0322,0323,0324,0325,0326,
	0327,0330,0331,0342,0343,0344,0345,0346,
	0347,0350,0351,0255,0340,0275,0137,0155,
	0171,0201,0202,0203,0204,0205,0206,0207,
	0210,0211,0221,0222,0223,0224,0225,0226,
	0227,0230,0231,0242,0243,0244,0245,0246,
	0247,0250,0251,0300,0117,0320,0241,0007,
	0040,0041,0042,0043,0044,0025,0006,0027,
	0050,0051,0052,0053,0054,0011,0012,0033,
	0060,0061,0032,0063,0064,0065,0066,0010,
	0070,0071,0072,0073,0004,0024,0076,0341,
	0101,0102,0103,0104,0105,0106,0107,0110,
	0111,0121,0122,0123,0124,0125,0126,0127,
	0130,0131,0142,0143,0144,0145,0146,0147,
	0150,0151,0160,0161,0162,0163,0164,0165,
	0166,0167,0170,0200,0212,0213,0214,0215,
	0216,0217,0220,0232,0233,0234,0235,0236,
	0237,0240,0252,0253,0254,0255,0256,0257,
	0260,0261,0262,0263,0264,0265,0266,0267,
	0270,0271,0272,0273,0274,0275,0276,0277,
	0312,0313,0314,0315,0316,0317,0332,0333,
	0334,0335,0336,0337,0352,0353,0354,0355,
	0356,0357,0372,0373,0374,0375,0376,0377,
};
E 15
I 15
static void dd_close __P((void));
static void dd_in __P((void));
I 32
static void getfdtype __P((IO *));
E 32
static void setup __P((void));
E 15

I 9
D 12
enum ftype { unknown, reg, chr, tape, pipe } iftype;
E 12
I 12
D 15
enum ftype { unknown, reg, chr, tape, ispipe } iftype;
E 12
enum ftype checktype();
E 15
I 15
D 19
struct	io_desc in, out;	/* input/output state */
E 19
I 19
IO	in, out;		/* input/output state */
STAT	st;			/* statistics */
E 19
D 27
void	(*cfunc)();		/* conversion function */
E 27
I 27
void	(*cfunc) __P((void));	/* conversion function */
E 27
u_long	cpy_cnt;		/* # of blocks to copy */
u_int	ddflags;		/* conversion options */
u_int	cbsz;			/* conversion block size */
u_int	files_cnt = 1;		/* # of files to copy */
I 23
D 31
int	errstats;		/* show statistics on error */
E 31
E 23
u_char	*ctab;			/* conversion table */
E 15
E 9

I 24
int
E 24
I 13
D 15
void stats(), term();

E 15
E 13
main(argc, argv)
D 15
int	argc;
char	**argv;
E 15
I 15
	int argc;
D 24
	char **argv;
E 24
I 24
	char *argv[];
E 24
E 15
{
D 15
	int (*conv)();
	register char *ip;
	register c;
D 13
	int ebcdic(), ibm(), ascii(), null(), cnull(), term(), block(), unblock();
I 11
	int stats();
E 13
I 13
	int ebcdic(), ibm(), ascii(), null(), cnull(), block(), unblock();
E 13
E 11
	int a;
E 15
I 15
	jcl(argv);
	setup();
E 15

D 15
	conv = null;
	for(c=1; c<argc; c++) {
		string = argv[c];
		if(match("ibs=")) {
			ibs = number(BIG);
			continue;
		}
		if(match("obs=")) {
			obs = number(BIG);
			continue;
		}
		if(match("cbs=")) {
			cbs = number(BIG);
			continue;
		}
		if (match("bs=")) {
			bs = number(BIG);
			continue;
		}
		if(match("if=")) {
			ifile = string;
			continue;
		}
		if(match("of=")) {
			ofile = string;
			continue;
		}
		if(match("skip=")) {
			skip = number(BIG);
			continue;
		}
		if(match("seek=")) {
			seekn = number(BIG);
			continue;
		}
		if(match("count=")) {
			count = number(BIG);
			continue;
		}
		if(match("files=")) {
			files = number(BIG);
			continue;
		}
		if(match("conv=")) {
		cloop:
			if(match(","))
				goto cloop;
			if(*string == '\0')
				continue;
			if(match("ebcdic")) {
				conv = ebcdic;
				goto cloop;
			}
			if(match("ibm")) {
				conv = ibm;
				goto cloop;
			}
			if(match("ascii")) {
				conv = ascii;
				goto cloop;
			}
			if(match("block")) {
				conv = block;
				goto cloop;
			}
			if(match("unblock")) {
				conv = unblock;
				goto cloop;
			}
			if(match("lcase")) {
				cflag |= LCASE;
				goto cloop;
			}
			if(match("ucase")) {
				cflag |= UCASE;
				goto cloop;
			}
			if(match("swab")) {
				cflag |= SWAB;
				goto cloop;
			}
			if(match("noerror")) {
				cflag |= NERR;
				goto cloop;
			}
			if(match("sync")) {
				cflag |= SYNC;
				goto cloop;
			}
		}
		fprintf(stderr,"bad arg: %s\n", string);
D 4
		exit(0);
E 4
I 4
		exit(1);
E 4
	}
	if(conv == null && cflag&(LCASE|UCASE))
		conv = cnull;
	if (ifile)
		ibf = open(ifile, 0);
	else
		ibf = dup(0);
	if(ibf < 0) {
D 3
		fprintf(stderr,"cannot open: %s\n", ifile);
E 3
I 3
		perror(ifile);
E 3
D 4
		exit(0);
E 4
I 4
		exit(1);
E 4
	}
I 9
	iftype = checktype(ibf);
E 9
D 6
	if (ofile)
		obf = creat(ofile, 0666);
	else
		obf = dup(1);
E 6
I 6
	obf = ofile ? open(ofile, O_WRONLY|O_CREAT, 0666) : dup(1);
E 6
	if(obf < 0) {
		fprintf(stderr,"cannot create: %s\n", ofile);
D 4
		exit(0);
E 4
I 4
		exit(1);
E 4
	}
	if (bs) {
		ibs = obs = bs;
D 10
		if (conv == null)
E 10
I 10
		if (conv == null && (cflag &~ (SYNC|NERR)) == 0)
E 10
			fflag++;
	}
	if(ibs == 0 || obs == 0) {
		fprintf(stderr,"counts: cannot be zero\n");
D 4
		exit(0);
E 4
I 4
		exit(1);
E 4
	}
	ibuf = sbrk(ibs);
	if (fflag)
		obuf = ibuf;
	else
		obuf = sbrk(obs);
	sbrk(64);	/* For good measure */
	if(ibuf == (char *)-1 || obuf == (char *)-1) {
		fprintf(stderr, "not enough memory\n");
D 4
		exit(0);
E 4
I 4
		exit(1);
E 4
	}
	ibc = 0;
	obc = 0;
	cbc = 0;
	op = obuf;
E 15
I 15
D 31
	(void)signal(SIGINFO, summary);
E 31
I 31
	(void)signal(SIGINFO, summaryx);
E 31
	(void)signal(SIGINT, terminate);
E 15

D 15
	if (signal(SIGINT, SIG_IGN) != SIG_IGN)
		signal(SIGINT, term);
I 11
	signal(SIGINFO, stats);
E 11
D 9
	while(skip) {
		read(ibf, ibuf, ibs);
		skip--;
E 9
I 9
	if (skip)
	    switch (iftype) {
		case tape: {
			struct mtop op;
E 15
I 15
D 23
	while (files_cnt--)
E 23
I 23
D 31
	for (errstats = 1; files_cnt--;)
E 31
I 31
	atexit(summary);

	while (files_cnt--)
E 31
E 23
		dd_in();
E 15

D 15
			op.mt_op = MTFSR;
			op.mt_count = skip;
			if (ioctl(ibf, MTIOCTOP, (char *)&op) < 0)
				perror("dd: skip: tape forward-space-record");
			}
			break;
		case reg:
D 12
			lseek(ibf, skip*ibs, L_INCR);
E 12
I 12
			lseek(ibf, skip*ibs, SEEK_CUR);
E 12
			break;
		default:
			while (skip--)
				read(ibf, ibuf, ibs);
			break;
E 9
	}
D 9
	while(seekn) {
		lseek(obf, (long)obs, 1);
		seekn--;
E 9
I 9
	if (seekn)
	    switch (checktype(obf)) {
		case reg:
D 12
			lseek(obf, (long)obs*seekn, L_INCR);
E 12
I 12
			lseek(obf, (long)obs*seekn, SEEK_CUR);
E 12
			break;
D 12
		case pipe:
E 12
I 12
		case ispipe:
E 12
			fprintf(stderr, "dd: can't seek on pipe\n");
			break;
		default:
			while (seekn--)
D 12
				lseek(obf, (long)obs, L_INCR);
E 12
I 12
				lseek(obf, (long)obs, SEEK_CUR);
E 12
			break;
E 9
	}

loop:
	if(ibc-- == 0) {
		ibc = 0;
		if(count==0 || nifr+nipr!=count) {
D 9
			if(cflag&(NERR|SYNC))
			for(ip=ibuf+ibs; ip>ibuf;)
				*--ip = 0;
E 9
I 9
			if (cflag&NERR)
				bzero((char *)ibuf, ibs);
E 9
			ibc = read(ibf, ibuf, ibs);
		}
		if(ibc == -1) {
			perror("read");
			if((cflag&NERR) == 0) {
				flsh();
				term();
			}
D 9
			ibc = 0;
E 9
I 9
			/* guess actual read size; default still -1 */
E 9
			for(c=0; c<ibs; c++)
				if(ibuf[c] != 0)
D 9
					ibc = c;
E 9
I 9
					ibc = c + 1;
E 9
			stats();
I 9
			advance(ibf, iftype, ibs);
E 9
		}
		if(ibc == 0 && --files<=0) {
			flsh();
			term();
		}
		if(ibc != ibs) {
I 9
			if (ibc == -1)
				ibc = 0;
E 9
			nipr++;
D 9
			if(cflag&SYNC)
E 9
I 9
			if (cflag&SYNC) {
				bzero(ibuf + ibc, ibs - ibc);
E 9
				ibc = ibs;
I 9
			}
E 9
		} else
			nifr++;
		ip = ibuf;
D 2
		c = (ibc>>1) & ~1;
E 2
I 2
		c = ibc >> 1;
E 2
		if(cflag&SWAB && c)
		do {
			a = *ip++;
			ip[-1] = *ip;
			*ip++ = a;
		} while(--c);
		ip = ibuf;
		if (fflag) {
			obc = ibc;
			flsh();
			ibc = 0;
		}
		goto loop;
	}
	c = 0;
	c |= *ip++;
	c &= 0377;
	(*conv)(c);
	goto loop;
E 15
I 15
	dd_close();
D 31
	summary(0);
E 31
	exit(0);
E 15
}

D 15
flsh()
E 15
I 15
static void
D 31
setup()
E 31
I 31
D 32
getfdtype(io)
	IO *io;
E 31
E 15
{
D 15
	register c;
E 15
I 15
D 31
	register u_int cnt;
	struct stat sb;
E 31
	struct mtget mt;
I 31
	struct stat sb;
E 31
E 15

I 31
	if (fstat(io->fd, &sb))
		err(1, "%s", io->name);
	if (S_ISCHR(sb.st_mode))
		io->flags |= ioctl(io->fd, MTIOCGET, &mt) ? ISCHR : ISTAPE;
	else if (lseek(io->fd, (off_t)0, SEEK_CUR) == -1 && errno == ESPIPE)
		io->flags |= ISPIPE;		/* XXX fixed in 4.4BSD */
}

static void
E 32
setup()
{
	u_int cnt;

E 31
D 15
	if(obc) {
		if(obc == obs)
			nofr++; else
			nopr++;
		c = write(obf, obuf, obc);
		if(c != obc) {
			perror("write");
			term();
		}
		obc = 0;
E 15
I 15
	if (in.name == NULL) {
		in.name = "stdin";
		in.fd = STDIN_FILENO;
	} else {
		in.fd = open(in.name, O_RDONLY, 0);
		if (in.fd < 0)
D 31
			err("%s: %s", in.name, strerror(errno));
E 31
I 31
			err(1, "%s", in.name);
E 31
E 15
	}
D 15
}
E 15

D 15
match(s)
char *s;
{
	register char *cs;
E 15
I 15
D 31
	if (fstat(in.fd, &sb))
		err("%s: %s", in.name, strerror(errno));
	if (S_ISCHR(sb.st_mode))
		in.flags |= ioctl(in.fd, MTIOCGET, &mt) ? ISCHR : ISTAPE;
D 24
	else if (lseek(in.fd, 0L, SEEK_CUR) == -1 && errno == ESPIPE)
E 24
I 24
	else if (lseek(in.fd, (off_t)0, SEEK_CUR) == -1 && errno == ESPIPE)
E 24
		in.flags |= ISPIPE;		/* XXX fixed in 4.4BSD */
E 31
I 31
	getfdtype(&in);
E 31
E 15

D 15
	cs = string;
	while(*cs++ == *s)
		if(*s++ == '\0')
			goto true;
	if(*s != '\0')
		return(0);
E 15
I 15
	if (files_cnt > 1 && !(in.flags & ISTAPE))
D 31
		err("files is not supported for non-tape devices");
E 31
I 31
		errx(1, "files is not supported for non-tape devices");
E 31
E 15

D 15
true:
	cs--;
	string = cs;
	return(1);
}
E 15
I 15
	if (out.name == NULL) {
		/* No way to check for read access here. */
		out.fd = STDOUT_FILENO;
		out.name = "stdout";
	} else {
D 22
		out.fd = open(out.name, O_RDWR|O_CREAT, DEFFILEMODE);
E 22
I 22
#define	OFLAGS \
    (O_CREAT | (ddflags & (C_SEEK | C_NOTRUNC) ? 0 : O_TRUNC))
		out.fd = open(out.name, O_RDWR | OFLAGS, DEFFILEMODE);
E 22
		/*
		 * May not have read access, so try again with write only.
		 * Without read we may have a problem if output also does
		 * not support seeks.
		 */
		if (out.fd < 0) {
D 22
			out.fd = open(out.name, O_WRONLY|O_CREAT, DEFFILEMODE);
E 22
I 22
			out.fd = open(out.name, O_WRONLY | OFLAGS, DEFFILEMODE);
E 22
			out.flags |= NOREAD;
		}
		if (out.fd < 0)
D 31
			err("%s: %s", out.name, strerror(errno));
E 31
I 31
			err(1, "%s", out.name);
E 31
	}
E 15

D 15
number(big)
{
	register char *cs;
	long n;
E 15
I 15
D 31
	if (fstat(out.fd, &sb))
		err("%s: %s", out.name, strerror(errno));
	if (S_ISCHR(sb.st_mode))
		out.flags |= ioctl(out.fd, MTIOCGET, &mt) ? ISCHR : ISTAPE;
D 24
	else if (lseek(out.fd, 0L, SEEK_CUR) == -1 && errno == ESPIPE)
E 24
I 24
	else if (lseek(out.fd, (off_t)0, SEEK_CUR) == -1 && errno == ESPIPE)
E 24
		out.flags |= ISPIPE;		/* XXX fixed in 4.4BSD */
E 31
I 31
	getfdtype(&out);
E 31
E 15

D 15
	cs = string;
	n = 0;
	while(*cs >= '0' && *cs <= '9')
		n = n*10 + *cs++ - '0';
	for(;;)
	switch(*cs++) {
E 15
I 15
	/*
	 * Allocate space for the input and output buffers.  If not doing
	 * record oriented I/O, only need a single buffer.
	 */
	if (!(ddflags & (C_BLOCK|C_UNBLOCK))) {
D 21
		if (in.dbsz > out.dbsz)
			cnt = in.dbsz - 1 - in.dbsz / 2 + in.dbsz;
		else if (in.dbsz < out.dbsz)
			cnt = out.dbsz + in.dbsz - 1;
		else
			cnt = in.dbsz;
		if ((in.db = malloc(cnt)) == NULL)
E 21
I 21
		if ((in.db = malloc(out.dbsz + in.dbsz - 1)) == NULL)
E 21
D 31
			err("%s", strerror(errno));
E 31
I 31
			err(1, NULL);
E 31
		out.db = in.db;
	} else if ((in.db =
	    malloc((u_int)(MAX(in.dbsz, cbsz) + cbsz))) == NULL ||
	    (out.db = malloc((u_int)(out.dbsz + cbsz))) == NULL)
D 31
		err("%s", strerror(errno));
E 31
I 31
		err(1, NULL);
E 31
	in.dbp = in.db;
	out.dbp = out.db;
E 15

D 15
	case 'k':
		n *= 1024;
		continue;
E 15
I 15
	/* Position the input/output streams. */
	if (in.offset)
		pos_in();
	if (out.offset)
		pos_out();
E 15

D 15
	case 'w':
		n *= sizeof(int);
		continue;
E 15
I 15
D 22
	/* Truncate the output file. */
	if (ddflags & C_NOTRUNC) {
		if (out.flags & ISTAPE)
			err("notrunc is not supported for tape devices");
	} else if (S_ISREG(sb.st_mode) && ftruncate(out.fd,
	    (off_t)out.offset * out.dbsz))
		err("%s: truncate: %s", out.name, strerror(errno));
E 22
I 22
	/*
	 * Truncate the output file; ignore errors because it fails on some
	 * kinds of output files, tapes, for example.
	 */
	if (ddflags & (C_OF | C_SEEK | C_NOTRUNC) == (C_OF | C_SEEK))
		(void)ftruncate(out.fd, (off_t)out.offset * out.dbsz);
E 22
E 15

D 15
	case 'b':
		n *= 512;
		continue;
E 15
I 15
	/*
	 * If converting case at the same time as another conversion, build a
	 * table that does both at once.  If just converting case, use the
	 * built-in tables.
	 */
	if (ddflags & (C_LCASE|C_UCASE))
D 19
		if (ddflags & C_BLOCK)
E 19
I 19
		if (ddflags & C_ASCII)
E 19
			if (ddflags & C_LCASE) {
				for (cnt = 0; cnt < 0377; ++cnt)
D 19
					if (isupper(cnt))
						ctab[cnt] = ctab[tolower(cnt)];
E 19
I 19
					if (isupper(ctab[cnt]))
						ctab[cnt] = tolower(ctab[cnt]);
E 19
			} else {
				for (cnt = 0; cnt < 0377; ++cnt)
D 19
					if (islower(cnt))
						ctab[cnt] = ctab[toupper(cnt)];
E 19
I 19
					if (islower(ctab[cnt]))
						ctab[cnt] = toupper(ctab[cnt]);
E 19
			}
D 19
		else if (ddflags & C_UNBLOCK)
E 19
I 19
		else if (ddflags & C_EBCDIC)
E 19
			if (ddflags & C_LCASE) {
				for (cnt = 0; cnt < 0377; ++cnt)
D 19
					if (isupper(ctab[cnt]))
						ctab[cnt] = tolower(ctab[cnt]);
E 19
I 19
					if (isupper(cnt))
						ctab[cnt] = ctab[tolower(cnt)];
E 19
			} else {
				for (cnt = 0; cnt < 0377; ++cnt)
D 19
					if (islower(ctab[cnt]))
						ctab[cnt] = toupper(ctab[cnt]);
E 19
I 19
					if (islower(cnt))
						ctab[cnt] = ctab[toupper(cnt)];
E 19
			}
D 19
		else {
			extern u_char l2u[], u2l[];
E 15

E 19
I 19
		else
E 19
D 15
	case '*':
	case 'x':
		string = cs;
		n *= number(BIG);

	case '\0':
		if (n>=big || n<0) {
D 7
			fprintf(stderr, "dd: argument %D out of range\n", n);
E 7
I 7
			fprintf(stderr, "dd: argument %ld out of range\n", n);
E 7
			exit(1);
E 15
I 15
			ctab = ddflags & C_LCASE ? u2l : l2u;
I 23
	(void)time(&st.start);			/* Statistics timestamp. */
I 32
}

static void
getfdtype(io)
	IO *io;
{
	struct mtget mt;
	struct stat sb;

	if (fstat(io->fd, &sb))
		err(1, "%s", io->name);
	if (S_ISCHR(sb.st_mode))
		io->flags |= ioctl(io->fd, MTIOCGET, &mt) ? ISCHR : ISTAPE;
	else if (lseek(io->fd, (off_t)0, SEEK_CUR) == -1 && errno == ESPIPE)
		io->flags |= ISPIPE;		/* XXX fixed in 4.4BSD */
E 32
E 23
E 15
D 19
		}
E 19
D 15
		return(n);
	}
	/* never gets here */
E 15
}

D 15
cnull(cc)
E 15
I 15
static void
dd_in()
E 15
{
D 15
	register c;
E 15
I 15
D 31
	register int flags, n;
E 31
I 31
	int flags, n;
E 31
E 15

D 15
	c = cc;
	if(cflag&UCASE && c>='a' && c<='z')
		c += 'A'-'a';
	if(cflag&LCASE && c>='A' && c<='Z')
		c += 'a'-'A';
	null(c);
}
E 15
I 15
D 25
	for(flags = ddflags;;) {
E 25
I 25
	for (flags = ddflags;;) {
E 25
D 19
		if (cpy_cnt && (in.f_stats + in.p_stats) >= cpy_cnt)
E 19
I 19
		if (cpy_cnt && (st.in_full + st.in_part) >= cpy_cnt)
E 19
			return;
E 15

D 15
null(c)
{
E 15
I 15
		/*
		 * Zero the buffer first if trying to recover from errors so
		 * lose the minimum amount of data.  If doing block operations
		 * use spaces.
		 */
D 30
		if (flags & (C_NOERROR|C_SYNC))
E 30
I 30
		if ((flags & (C_NOERROR|C_SYNC)) == (C_NOERROR|C_SYNC))
E 30
			if (flags & (C_BLOCK|C_UNBLOCK))
				memset(in.dbp, ' ', in.dbsz);
			else
D 27
				bzero(in.dbp, in.dbsz);
E 27
I 27
				memset(in.dbp, 0, in.dbsz);
E 27
E 15

D 15
	*op = c;
	op++;
	if(++obc >= obs) {
		flsh();
		op = obuf;
	}
}
E 15
I 15
		n = read(in.fd, in.dbp, in.dbsz);
		if (n == 0) {
			in.dbrcnt = 0;
			return;
		}
E 15

D 15
ascii(cc)
{
	register c;
E 15
I 15
		/* Read error. */
		if (n < 0) {
			/*
			 * If noerror not specified, die.  POSIX requires that
			 * the warning message be followed by an I/O display.
			 */
			if (!(flags & C_NOERROR))
D 31
				err("%s: %s", in.name, strerror(errno));
			warn("%s: %s", in.name, strerror(errno));
			summary(0);
E 31
I 31
				err(1, "%s", in.name);
			warn("%s", in.name);
			summary();
E 31
E 15

D 15
	c = etoa[cc] & 0377;
	if(cbs == 0) {
		cnull(c);
		return;
	}
	if(c == ' ') {
		nspace++;
		goto out;
	}
	while(nspace > 0) {
		null(' ');
		nspace--;
	}
	cnull(c);
E 15
I 15
			/*
			 * If it's not a tape drive or a pipe, seek past the
			 * error.  If your OS doesn't do the right thing for
			 * raw disks this section should be modified to re-read
			 * in sector size chunks.
			 */
			if (!(in.flags & (ISPIPE|ISTAPE)) &&
			    lseek(in.fd, (off_t)in.dbsz, SEEK_CUR))
D 31
				warn("%s: %s", in.name, strerror(errno));
E 31
I 31
				warn("%s", in.name);
E 31
E 15

D 15
out:
	if(++cbc >= cbs) {
		null('\n');
		cbc = 0;
		nspace = 0;
	}
}
E 15
I 15
			/* If sync not specified, omit block and continue. */
			if (!(ddflags & C_SYNC))
				continue;
E 15

D 15
unblock(cc)
{
	register c;
E 15
I 15
			/* Read errors count as full blocks. */
			in.dbcnt += in.dbrcnt = in.dbsz;
D 19
			++in.f_stats;
E 19
I 19
			++st.in_full;
E 19
E 15

D 15
	c = cc & 0377;
	if(cbs == 0) {
		cnull(c);
		return;
	}
	if(c == ' ') {
		nspace++;
		goto out;
	}
	while(nspace > 0) {
		null(' ');
		nspace--;
	}
	cnull(c);
E 15
I 15
		/* Handle full input blocks. */
		} else if (n == in.dbsz) {
			in.dbcnt += in.dbrcnt = n;
D 19
			++in.f_stats;
E 19
I 19
			++st.in_full;
E 19
E 15

D 15
out:
	if(++cbc >= cbs) {
		null('\n');
		cbc = 0;
		nspace = 0;
	}
}
E 15
I 15
		/* Handle partial input blocks. */
D 25
		} else if (n != in.dbsz) {
E 25
I 25
		} else {
E 25
D 18
			/* If sync, fill the block with NULs. */
			if (ddflags & C_SYNC) {
				bzero(in.dbp + n, in.dbsz - n);
E 18
I 18
			/* If sync, use the entire block. */
			if (ddflags & C_SYNC)
E 18
				in.dbcnt += in.dbrcnt = in.dbsz;
D 18
			} else
E 18
I 18
			else
E 18
				in.dbcnt += in.dbrcnt = n;
D 19
			++in.p_stats;
E 19
I 19
			++st.in_part;
E 19
		}
E 15

I 17
D 20
		if (ddflags & C_SWAB) {
			if ((n = in.dbcnt) & 1) {
D 19
				warn("%s: odd swab count", in.name);
E 19
I 19
				++st.swab;
E 19
				--n;
			}
			swab(in.dbp, in.dbp, n);
		}

E 20
E 17
D 15
ebcdic(cc)
{
	register c;

	c = cc;
	if(cflag&UCASE && c>='a' && c<='z')
		c += 'A'-'a';
	if(cflag&LCASE && c>='A' && c<='Z')
		c += 'a'-'A';
	c = atoe[c] & 0377;
	if(cbs == 0) {
		null(c);
		return;
	}
	if(cc == '\n') {
		while(cbc < cbs) {
			null(atoe[' ']);
			cbc++;
E 15
I 15
		/*
		 * POSIX states that if bs is set and no other conversions
D 17
		 * are specified, the block is output as it is read, without
		 * buffering.
E 17
I 17
D 20
		 * are specified, the block is output without buffering as
		 * it is read.
E 20
I 20
		 * than noerror, notrunc or sync are specified, the block
		 * is output without buffering as it is read.
E 20
E 17
		 */
		if (ddflags & C_BS) {
			out.dbcnt = in.dbcnt;
			dd_out(1);
			in.dbcnt = 0;
			continue;
I 20
		}

		if (ddflags & C_SWAB) {
			if ((n = in.dbcnt) & 1) {
				++st.swab;
				--n;
			}
			swab(in.dbp, in.dbp, n);
E 20
E 15
D 17
		}
D 15
		cbc = 0;
		return;
	}
	if(cbc == cbs)
		ntrunc++;
	cbc++;
	if(cbc <= cbs)
		null(c);
}
E 15

D 15
ibm(cc)
{
	register c;

	c = cc;
	if(cflag&UCASE && c>='a' && c<='z')
		c += 'A'-'a';
	if(cflag&LCASE && c>='A' && c<='Z')
		c += 'a'-'A';
	c = atoibm[c] & 0377;
	if(cbs == 0) {
		null(c);
		return;
	}
	if(cc == '\n') {
		while(cbc < cbs) {
			null(atoibm[' ']);
			cbc++;
E 15
I 15
		if (ddflags & C_SWAB) {
			if ((n = in.dbcnt) & 1) {
				warn("%s: odd swab count", in.name);
				--n;
			}
			swab(in.dbp, in.dbp, n);
E 17
E 15
		}
D 15
		cbc = 0;
		return;
	}
	if(cbc == cbs)
		ntrunc++;
	cbc++;
	if(cbc <= cbs)
		null(c);
}
E 15

D 15
block(cc)
{
	register c;

	c = cc;
	if(cflag&UCASE && c>='a' && c<='z')
		c += 'A'-'a';
	if(cflag&LCASE && c>='A' && c<='Z')
		c += 'a'-'A';
	c &= 0377;
	if(cbs == 0) {
		null(c);
		return;
E 15
I 15
		in.dbp += in.dbrcnt;
		(*cfunc)();
E 15
	}
D 15
	if(cc == '\n') {
		while(cbc < cbs) {
			null(' ');
			cbc++;
		}
		cbc = 0;
		return;
	}
	if(cbc == cbs)
		ntrunc++;
	cbc++;
	if(cbc <= cbs)
		null(c);
E 15
}

I 13
D 15
void
E 13
term()
E 15
I 15
/*
 * Cleanup any remaining I/O and flush output.  If necesssary, output file
 * is truncated.
 */
static void
dd_close()
E 15
{
D 15

	stats();
	exit(0);
E 15
I 15
	if (cfunc == def)
		def_close();
	else if (cfunc == block)
		block_close();
	else if (cfunc == unblock)
		unblock_close();
I 30
	if (ddflags & C_OSYNC && out.dbcnt < out.dbsz) {
D 31
		bzero(out.dbp, out.dbsz - out.dbcnt);
E 31
I 31
		memset(out.dbp, 0, out.dbsz - out.dbcnt);
E 31
		out.dbcnt = out.dbsz;
	}
E 30
	if (out.dbcnt)
		dd_out(1);
E 15
}

I 13
void
E 13
D 15
stats()
E 15
I 15
dd_out(force)
	int force;
E 15
{
I 15
	static int warned;
D 31
	register int cnt, n, nw;
	register u_char *outp;
E 31
I 31
	int cnt, n, nw;
	u_char *outp;
E 31
E 15

D 15
	fprintf(stderr,"%u+%u records in\n", nifr, nipr);
	fprintf(stderr,"%u+%u records out\n", nofr, nopr);
	if(ntrunc)
		fprintf(stderr,"%u truncated records\n", ntrunc);
}
I 9

enum ftype
checktype(fd)
	int fd;
{
	struct stat st;
	struct mtget mt;

	if (fstat(fd, &st) == -1)
		return (unknown);
	if (S_ISFIFO(st.st_mode))
D 12
		return (pipe);
E 12
I 12
		return (ispipe);
E 12
	if (S_ISCHR(st.st_mode)) {
		if (ioctl(fd, MTIOCGET, (char *)&mt) != -1)
			return (tape);
		return (chr);
E 15
I 15
	/*
	 * Write one or more blocks out.  The common case is writing a full
	 * output block in a single write; increment the full block stats.
	 * Otherwise, we're into partial block writes.  If a partial write,
	 * and it's a character device, just warn.  If a tape device, quit.
	 *
	 * The partial writes represent two cases.  1: Where the input block
	 * was less than expected so the output block was less than expected.
	 * 2: Where the input block was the right size but we were forced to
	 * write the block in multiple chunks.  The original versions of dd(1)
	 * never wrote a block in more than a single write, so the latter case
	 * never happened.
	 *
	 * One special case is if we're forced to do the write -- in that case
	 * we play games with the buffer size, and it's usually a partial write.
	 */
	outp = out.db;
	for (n = force ? out.dbcnt : out.dbsz;; n = out.dbsz) {
		for (cnt = n;; cnt -= nw) {
D 25
			outp += nw = write(out.fd, outp, cnt);
E 25
I 25
			nw = write(out.fd, outp, cnt);
D 28
			if (nw < 0)
				err("%s: %s", out.name, strerror(errno));
E 28
I 28
			if (nw <= 0) {
				if (nw == 0)
D 31
					err("%s: end of device", out.name);
E 31
I 31
					errx(1, "%s: end of device", out.name);
E 31
				if (errno != EINTR)
D 31
					err("%s: %s",
					    out.name, strerror(errno));
E 31
I 31
					err(1, "%s", out.name);
E 31
				nw = 0;
			}
E 28
D 26
			outp += rw;
E 26
I 26
			outp += nw;
E 26
E 25
I 23
			st.bytes += nw;
E 23
			if (nw == n) {
				if (n != out.dbsz)
D 19
					++out.p_stats;
E 19
I 19
					++st.out_part;
E 19
				else
D 19
					++out.f_stats;
E 19
I 19
					++st.out_full;
E 19
				break;
			}
D 25
			if (nw < 0)
				err("%s: %s", out.name, strerror(errno));
E 25
D 19
			++out.p_stats;
E 19
I 19
			++st.out_part;
E 19
			if (nw == cnt)
				break;
			if (out.flags & ISCHR && !warned) {
				warned = 1;
D 31
				warn("%s: short write on character device",
E 31
I 31
				warnx("%s: short write on character device",
E 31
				    out.name);
			}
			if (out.flags & ISTAPE)
D 31
				err("%s: short write on tape device", out.name);
E 31
I 31
				errx(1, "%s: short write on tape device", out.name);
E 31
		}
		if ((out.dbcnt -= n) < out.dbsz)
			break;
E 15
	}
D 15
	return (reg);	/* or dir, symlink, blk, or ??? */
}
E 15

D 15
advance(fd, fdtype, count)
{

	switch (fdtype) {
	case reg:
	case chr:
D 12
		lseek(fd, count, L_INCR);
E 12
I 12
		lseek(fd, count, SEEK_CUR);
E 12
		break;
D 12
	case pipe:
E 12
I 12
	case ispipe:
E 12
	case tape:
		break;
	default:
		fprintf(stderr, "dd: unknown input type, can't resynchronize\n");
		exit(99);
	}
E 15
I 15
	/* Reassemble the output block. */
	if (out.dbcnt)
D 27
		bcopy(out.dbp - out.dbcnt, out.db, out.dbcnt);
E 27
I 27
		memmove(out.db, out.dbp - out.dbcnt, out.dbcnt);
E 27
	out.dbp = out.db + out.dbcnt;
E 15
}
D 15

E 15
E 9
E 1
