h41644
s 00005/00005/01015
d D 8.1 93/06/06 14:24:48 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00011/00011/01009
d D 5.5 91/06/27 15:03:43 bostic 5 4
c test returns of des_setkey, des_cipher, setkey, encrypt
e
s 00015/00005/01005
d D 5.4 91/05/06 12:27:08 bostic 4 3
c use faster routines, also check for errno after setkey (Ultrix)
e
s 00050/00037/00960
d D 5.3 91/04/26 14:34:12 bostic 3 2
c changes from Matt Bishop, mostly cleanups
e
s 00265/00350/00732
d D 5.2 91/04/22 13:13:21 bostic 2 1
c change the copyright/disclaimer to the standard Berkeley one
c delete the -c option; it's the default; discard first argument of err()
c reformat the manual page somewhat to standard Berkeley
c change CNULL to NULL; rename from "des program" to "bdes"
c change key from an argument to -k option (Sun compatibility)
c change -e to -b, -i to -d (Sun compatibility), allow options to override
c minor formatting changes, add usage message
e
s 01082/00000/00000
d D 5.1 91/04/21 18:11:41 bostic 1 0
c Version from Matt Bishop
c date and time created 91/04/21 18:11:41 by bostic
e
u
U
t
T
I 2
/*-
D 6
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * This code is derived from software contributed to Berkeley by
 * Matt Bishop of Dartmouth College.
 *
 * The United States Government has rights in this work pursuant
 * to contract no. NAG 2-680 between the National Aeronautics and
 * Space Administration and Dartmouth College.
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
D 6
char copyright[] =
"%Z% Copyright (c) 1991 The Regents of the University of California.\n\
 All rights reserved.\n";
E 6
I 6
static char copyright[] =
"%Z% Copyright (c) 1991, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 6
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

E 2
I 1
/*
 * BDES -- DES encryption package for Berkeley Software Distribution 4.4
 * options:
 *	-a	key is in ASCII
D 2
 *	-c	use CBC (cipher block chaining) mode
E 2
D 3
 *	-e	use ECB (electronic code book) mode
E 3
I 3
 *	-b	use ECB (electronic code book) mode
 *	-d	invert (decrypt) input
E 3
 *	-f b	use b-bit CFB (cipher feedback) mode
 *	-F b	use b-bit CFB (cipher feedback) alternative mode
D 3
 *	-i	invert (decrypt) input
E 3
I 3
 *	-k key	use key as the cryptographic key
E 3
 *	-m b	generate a MAC of length b
 *	-o b	use b-bit OFB (output feedback) mode
 *	-p	don't reset the parity bit
 *	-v v	use v as the initialization vector (ignored for ECB)
 * note: the last character of the last block is the integer indicating
 * how many characters of that block are to be output
 *
 * Author: Matt Bishop
 *	   Department of Mathematics and Computer Science
 *	   Dartmouth College
 *	   Hanover, NH  03755
 * Email:  Matt.Bishop@dartmouth.edu
 *	   ...!decvax!dartvax!Matt.Bishop
 *
D 2
 * This is derived from a program written as part of work done for grant
 * NAG 2-680 from the National Aeronautics and Space Administration to
 * Dartmouth College.  It is freely distributable provided:
 * (1) the name and address of the author and the credit to NASA and
 *     Dartmouth are not altered or removed; and
 * (2) any changes made are noted in the leading comments, and the date
 *     and changer are also noted; and
 * (3) all bugs are promptly reported to the author at the above address.
 * Also, as stated in the manual page, "there is no warranty of merchant-
 * ability nor any warranty of fitness for a particular puurpose not any
 * other warranty, either express or implied, as to the accuracy of the
 * enclosed materials or as to their suitability for any particular pur-
 * pose.  Accordingly, the user assumes full responsibility for their 
 * use.  Further, the author assumes no obligation to furnish any assis-
 * tance of any kind whatsoever, or to furnish any additional information
 * or documentation."
 *
E 2
 * See Technical Report PCS-TR91-158, Department of Mathematics and Computer
 * Science, Dartmouth College, for a detailed description of the implemen-
 * tation and differences between it and Sun's.  The DES is described in
 * FIPS PUB 46, and the modes in FIPS PUB 81 (see either the manual page
 * or the technical report for a complete reference).
D 2
 *
 * 4/1/91 -- bug fix by Matt Bishop
 *	There was an error in the MAC computation if you asked for a
 *	MAC of length not a multiple of 8; you got the first bit from
 *	the first char, the second from the second char, and so on.
 *	Found by inspection of code; fixed.
E 2
 */
D 2
#include <ctype.h>
E 2
I 2

#include <errno.h>
#include <unistd.h>
E 2
#include <stdio.h>
D 2
#define C_NULL	((char *) NULL)
E 2
I 2
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
E 2

/*
 * BSD and System V systems offer special library calls that do
 * block moves and fills, so if possible we take advantage of them
 */
#define	MEMCPY(dest,src,len)	bcopy((src),(dest),(len))
#define	MEMZERO(dest,len)	bzero((dest),(len))

D 4
/*
 * these "hide" the calls to the primitive encryption routines
 */
E 4
I 4
/* Hide the calls to the primitive encryption routines. */
#define	FASTWAY
#ifdef	FASTWAY
D 5
#define	DES_KEY(buf)	des_setkey(buf)
#define	DES_XFORM(buf)	des_cipher(buf, buf, 0L, (inverse ? -1 : 1))
E 5
I 5
#define	DES_KEY(buf) \
	if (des_setkey(buf)) \
		err("des_setkey", 0);
#define	DES_XFORM(buf) \
	if (des_cipher(buf, buf, 0L, (inverse ? -1 : 1))) \
		err("des_cipher", 0);
E 5
#else
E 4
#define	DES_KEY(buf)	{						\
				char bits1[64];	/* bits of key */	\
				expand(buf, bits1);			\
D 5
				setkey(bits1);				\
E 5
I 5
				if (setkey(bits1))			\
					err("setkey", 0);		\
E 5
			}
D 4
#define DES_XFORM(buf)	{						\
E 4
I 4
#define	DES_XFORM(buf)	{						\
E 4
				char bits1[64];	/* bits of message */	\
				expand(buf, bits1);			\
D 5
				encrypt(bits1, inverse);		\
E 5
I 5
				if (encrypt(bits1, inverse))		\
					err("encrypt", 0);		\
E 5
				compress(bits1, buf);			\
			}
I 4
#endif
E 4

/*
 * this does an error-checking write
 */
#define	READ(buf, n)	fread(buf, sizeof(char), n, stdin)
#define WRITE(buf,n)						\
		if (fwrite(buf, sizeof(char), n, stdout) != n)	\
D 2
			err(1, bn, C_NULL);
E 2
I 2
			err(bn, NULL);
E 2

/*
 * some things to make references easier
 */
typedef char Desbuf[8];
#define	CHAR(x,i)	(x[i])
#define	UCHAR(x,i)	(x[i])
#define	BUFFER(x)	(x)
#define	UBUFFER(x)	(x)

/*
 * global variables and related macros
 */
#define KEY_DEFAULT		0	/* interpret radix of key from key */
#define KEY_ASCII		1	/* key is in ASCII characters */
D 3
int keybase = KEY_DEFAULT;	/* how to interpret the key */
E 3
I 3
int keybase = KEY_DEFAULT;		/* how to interpret the key */
E 3

D 2
#define MODE_ENCRYPT		0x01	/* encrypt */
#define MODE_DECRYPT		0x02	/* decrypt */
#define MODE_AUTHENTICATE	0x04	/* authenticate */
#define GET_DIRECTION		((mode)&0xf)
#define ISSET_MODE_DIRECTION	(GET_DIRECTION != 0)
#define MODE_ECB		0x10	/* ECB mode */
#define MODE_CBC		0x20	/* CBC mode */
#define	MODE_CFB		0x30	/* cipher feedback mode */
#define MODE_OFB		0x40	/* output feedback mode */
#define	MODE_CFBA		0x50	/* alternative cipher feedback mode */
#define GET_ALGORITHM		((mode)&0xf0)
#define ISSET_MODE_ALGORITHM	(GET_ALGORITHM != 0)
int mode = 0;			/* how to run */
E 2
I 2
D 3
enum { MODE_ENCRYPT, MODE_DECRYPT, MODE_AUTHENTICATE } mode = MODE_ENCRYPT;
enum { ALG_ECB, ALG_CBC, ALG_CFB, ALG_OFB, ALG_CFBA } alg = ALG_CBC;
E 3
I 3
enum { 					/* encrypt, decrypt, authenticate */
	MODE_ENCRYPT, MODE_DECRYPT, MODE_AUTHENTICATE
} mode = MODE_ENCRYPT;
enum {					/* ecb, cbc, cfb, cfba, ofb? */
	ALG_ECB, ALG_CBC, ALG_CFB, ALG_OFB, ALG_CFBA
} alg = ALG_CBC;
E 3
E 2

D 2
char *keyrep = "*********";	/* replaces command-line key */
E 2
D 3
Desbuf ivec;			/* initialization vector */
D 2
char bits[] = { '\200', '\100',	/* used to extract bits from a char */
		'\040', '\020', '\010', '\004', '\002', '\001' };
int inverse = 0;		/* 0 ti encrypt, 1 to decrypt */
char *progname = "des program";	/* program name */
E 2
I 2
char bits[] = {			/* used to extract bits from a char */
E 3
I 3
Desbuf ivec;				/* initialization vector */
char bits[] = {				/* used to extract bits from a char */
E 3
	'\200', '\100', '\040', '\020', '\010', '\004', '\002', '\001'
};
D 3
int inverse;			/* 0 to encrypt, 1 to decrypt */
E 2
int macbits = -1;		/* number of bits in authentication */
int fbbits = -1;		/* number of feedback bits */
D 2
int pflag = 0;			/* 1 to preserve parity bits */
char *dummyargs[] = { "*****", NULL };	/* argument list to be printed */
E 2
I 2
int pflag;			/* 1 to preserve parity bits */
E 3
I 3
int inverse;				/* 0 to encrypt, 1 to decrypt */
int macbits = -1;			/* number of bits in authentication */
int fbbits = -1;			/* number of feedback bits */
int pflag;				/* 1 to preserve parity bits */
E 3
E 2

D 2
/*
 * library hooks
 */
				/* see getopt(3) */
extern int optind;		/* option (argument) number */
extern char *optarg;		/* argument to option if any */

/*
 * library functions
 */
#ifdef notdef
char *sprintf();		/* in core formatted print */
#endif
char *getpass();		/* get a password from a terminal */

main(argc, argv)
int argc;
char **argv;
E 2
I 2
main(ac, av)
D 3
	int ac;
	char **av;
E 3
I 3
	int ac;				/* arg count */
	char **av;			/* arg vector */
E 3
E 2
{
I 2
D 3
	extern int optind;	/* option (argument) number */
	extern char *optarg;	/* argument to option if any */
E 2
	register int i;		/* counter in a for loop */
	register char *p;	/* used to obtain the key */
D 2
	int n;			/* number of command-line errors */
E 2
	Desbuf msgbuf;		/* I/O buffer */
D 2
	int nargs;		/* internal number of arguments */
	char **arglist;		/* internal argument list */
E 2
I 2
	int argc, kflag;
	char **argv;
E 3
I 3
	extern int optind;		/* option (argument) number */
	extern char *optarg;		/* argument to option if any */
	register int i;			/* counter in a for loop */
	register char *p;		/* used to obtain the key */
	Desbuf msgbuf;			/* I/O buffer */
	int kflag;			/* command-line encryptiooon key */
	int argc;			/* the real arg count */
	char **argv;			/* the real argument vector */
E 3
E 2

D 2
	/*
	 * hide the arguments
	 */
	nargs = argc;
	argc = 1;
	arglist = argv;
	argv = dummyargs;
E 2
I 2
D 3
	/* hide the arguments from ps(1) */
E 3
I 3
	/*
	 * Hide the arguments from ps(1) by making private copies of them
	 * and clobbering the global (visible to ps(1)) ones.
	 */
E 3
	argc = ac;
	ac = 1;
	argv = malloc((argc + 1) * sizeof(char *));
	for (i = 0; i < argc; ++i) {
		argv[i] = strdup(av[i]);
		MEMZERO(av[i], strlen(av[i]));
	}
	argv[argc] = NULL;
E 2

D 2
	/*
	 * initialize the initialization vctor
	 */
	for(i = 0; i < 8; i++)
		UCHAR(ivec, i) = 0x00;
E 2
I 2
	/* initialize the initialization vctor */
	MEMZERO(ivec, 8);
E 2

D 2
	/*
	 * process the argument list
	 */
	progname = arglist[0];
	n = 0;
	while ((i = getopt(nargs, arglist, "aceF:f:im:o:pv:")) != EOF)
		switch(i){
E 2
I 2
	/* process the argument list */
	kflag = 0;
	while ((i = getopt(argc, argv, "abdF:f:k:m:o:pv:")) != EOF)
		switch(i) {
E 2
		case 'a':		/* key is ASCII */
			keybase = KEY_ASCII;
			break;
D 2
		case 'c':		/* use CBC mode */
			if (ISSET_MODE_ALGORITHM)
				err(1, -1, "two modes of operation specified");
			mode |= MODE_CBC;
E 2
I 2
		case 'b':		/* use ECB mode */
			alg = ALG_ECB;
E 2
			break;
D 2
		case 'e':		/* use ECB mode */
			if (ISSET_MODE_ALGORITHM)
				err(1, -1, "two modes of operation specified");
			mode |= MODE_ECB;
E 2
I 2
		case 'd':		/* decrypt */
			mode = MODE_DECRYPT;
E 2
			break;
		case 'F':		/* use alternative CFB mode */
D 2
			if (ISSET_MODE_ALGORITHM)
				err(1, -1, "two modes of operation specified");
			mode |= MODE_CFBA;
E 2
I 2
			alg = ALG_CFBA;
E 2
			if ((fbbits = setbits(optarg, 7)) > 56 || fbbits == 0)
D 2
			err(1, -1, "-F: number must be 1-56 inclusive");
E 2
I 2
				err(-1, "-F: number must be 1-56 inclusive");
E 2
			else if (fbbits == -1)
D 2
			err(1, -1, "-F: number must be a multiple of 7");
E 2
I 2
				err(-1, "-F: number must be a multiple of 7");
E 2
			break;
		case 'f':		/* use CFB mode */
D 2
			if (ISSET_MODE_ALGORITHM)
				err(1, -1, "two modes of operation specified");
			mode |= MODE_CFB;
E 2
I 2
			alg = ALG_CFB;
E 2
			if ((fbbits = setbits(optarg, 8)) > 64 || fbbits == 0)
D 2
			err(1, -1, "-f: number must be 1-64 inclusive");
E 2
I 2
				err(-1, "-f: number must be 1-64 inclusive");
E 2
			else if (fbbits == -1)
D 2
			err(1, -1, "-f: number must be a multiple of 8");
E 2
I 2
				err(-1, "-f: number must be a multiple of 8");
E 2
			break;
D 2
		case 'i':		/* decrypt */
			if (ISSET_MODE_DIRECTION)
				err(1, -1, "only one of -i and -m allowed");
			mode |= MODE_DECRYPT;
E 2
I 2
		case 'k':		/* encryption key */
			kflag = 1;
			cvtkey(BUFFER(msgbuf), optarg);
E 2
			break;
		case 'm':		/* number of bits for MACing */
D 2
			if (ISSET_MODE_DIRECTION)
				err(1, -1, "only one of -i and -m allowed");
			mode |= MODE_AUTHENTICATE;
E 2
I 2
			mode = MODE_AUTHENTICATE;
E 2
			if ((macbits = setbits(optarg, 1)) > 64)
D 2
			err(1, -1, "-m: number must be 0-64 inclusive");
E 2
I 2
				err(-1, "-m: number must be 0-64 inclusive");
E 2
			break;
		case 'o':		/* use OFB mode */
D 2
			if (ISSET_MODE_ALGORITHM)
				err(1, -1, "two modes of operation specified");
			mode |= MODE_OFB;
E 2
I 2
			alg = ALG_OFB;
E 2
			if ((fbbits = setbits(optarg, 8)) > 64 || fbbits == 0)
D 2
			err(1, -1, "-o: number must be 1-64 inclusive");
E 2
I 2
				err(-1, "-o: number must be 1-64 inclusive");
E 2
			else if (fbbits == -1)
D 2
			err(1, -1, "-o: number must be a multiple of 8");
E 2
I 2
				err(-1, "-o: number must be a multiple of 8");
E 2
			break;
D 2
			break;
E 2
		case 'p':		/* preserve parity bits */
D 2
			pflag++;
E 2
I 2
			pflag = 1;
E 2
			break;
		case 'v':		/* set initialization vector */
			cvtkey(BUFFER(ivec), optarg);
			break;
		default:		/* error */
D 2
			n++;
			break;
E 2
I 2
			usage();
E 2
		}
D 2
	/*
	 * on error, quit
	 */
	if (n > 0)
		exit(1);
	/*
	 * if no direction set, default to encryption
	 */
	if (!ISSET_MODE_DIRECTION)
		mode |= MODE_ENCRYPT;
	if (!ISSET_MODE_ALGORITHM)
		mode |= MODE_CBC;
E 2

D 2
	/*
	 * pick up the key
	 * -- if there are no more arguments, prompt for it
	 * -- if there is 1 more argument, use it as the key
	 * -- if there are 2 or more arguments, error
	 */
	if (optind == nargs){
E 2
I 2
	if (!kflag) {
E 2
		/*
		 * if the key's not ASCII, assume it is
		 */
		keybase = KEY_ASCII;
		/*
		 * get the key
		 */
D 2
		if ((p = getpass("Enter key: ")) == NULL)
			err(1, -1, "no key given");
E 2
I 2
		p = getpass("Enter key: ");
E 2
		/*
		 * copy it, nul-padded, into the key area
		 */
D 3
		strncpy(BUFFER(msgbuf), p, 8);
E 3
I 3
		cvtkey(BUFFER(msgbuf), p);
E 3
	}
D 2
	else if (optind + 1 == nargs){
		/*
		 * obtain the bit form of the key
		 * and hide it from a "ps"
		 */
		cvtkey(BUFFER(msgbuf), arglist[optind]);
		arglist[optind] = keyrep;
	}
	else{
		/*
		 * extra arguments -- bomb
		 */
		err(1, -1, "extraneous arguments");
	}
E 2

I 2
	makekey(msgbuf);
	inverse = (alg == ALG_CBC || alg == ALG_ECB) && mode == MODE_DECRYPT;
E 2

D 2
	/*
	 * main loop
	 */
	switch(mode){
	case MODE_ECB|MODE_ENCRYPT:		/* encrypt using ECB mode */
				inverse = 0;
				makekey(msgbuf);
				ecbenc();
				break;
	case MODE_ECB|MODE_DECRYPT:		/* decrypt using ECB mode */
				inverse = 1;
				makekey(msgbuf);
				ecbdec();
				break;
	case MODE_ECB|MODE_AUTHENTICATE:	/* authenticate using ECB */
				err(1, -1, "can't authenticate with ECB mode");
				break;
	case MODE_CBC|MODE_ENCRYPT:		/* encrypt using CBC mode */
				inverse = 0;
				makekey(msgbuf);
				cbcenc();
				break;
	case MODE_CBC|MODE_DECRYPT:		/* decrypt using CBC mode */
				inverse = 1;
				makekey(msgbuf);
				cbcdec();
				break;
	case MODE_CBC|MODE_AUTHENTICATE:	/* authenticate using CBC */
				inverse = 0;
				makekey(msgbuf);
				cbcauth();
				break;
	case MODE_CFB|MODE_ENCRYPT:		/* encrypt using CFB mode */
				inverse = 0;
				makekey(msgbuf);
				cfbenc();
				break;
	case MODE_CFB|MODE_DECRYPT:		/* decrypt using CFB mode */
				inverse = 0;
				makekey(msgbuf);
				cfbdec();
				break;
	case MODE_CFB|MODE_AUTHENTICATE:	/* authenticate using CFB */
				inverse = 0;
				makekey(msgbuf);
				cfbauth();
				break;
	case MODE_CFBA|MODE_ENCRYPT:		/* alternative CFB mode */
				inverse = 0;
				makekey(msgbuf);
				cfbaenc();
				break;
	case MODE_CFBA|MODE_DECRYPT:		/* alternative CFB mode */
				inverse = 0;
				makekey(msgbuf);
				cfbadec();
				break;
	case MODE_OFB|MODE_ENCRYPT:		/* encrypt using OFB mode */
				inverse = 0;
				makekey(msgbuf);
				ofbenc();
				break;
	case MODE_OFB|MODE_DECRYPT:		/* decrypt using OFB mode */
				inverse = 0;
				makekey(msgbuf);
				ofbdec();
				break;
	default:			/* unimplemented */
				err(1, -1, "can't handle that yet");
				break;
E 2
I 2
	switch(alg) {
	case ALG_CBC:
		switch(mode) {
		case MODE_AUTHENTICATE:	/* authenticate using CBC mode */
			cbcauth();
			break;
		case MODE_DECRYPT:	/* decrypt using CBC mode */
			cbcdec();
			break;
		case MODE_ENCRYPT:	/* encrypt using CBC mode */
			cbcenc();
			break;
		}
		break;
	case ALG_CFB:
		switch(mode) {
		case MODE_AUTHENTICATE:	/* authenticate using CFB mode */
			cfbauth();
			break;
		case MODE_DECRYPT:	/* decrypt using CFB mode */
			cfbdec();
			break;
		case MODE_ENCRYPT:	/* encrypt using CFB mode */
			cfbenc();
			break;
		}
		break;
	case ALG_CFBA:
		switch(mode) {
		case MODE_AUTHENTICATE:	/* authenticate using CFBA mode */
			err(-1, "can't authenticate with CFBA mode");
			break;
		case MODE_DECRYPT:	/* decrypt using CFBA mode */
			cfbadec();
			break;
		case MODE_ENCRYPT:	/* encrypt using CFBA mode */
			cfbaenc();
			break;
		}
		break;
	case ALG_ECB:
		switch(mode) {
		case MODE_AUTHENTICATE:	/* authenticate using ECB mode */
			err(-1, "can't authenticate with ECB mode");
			break;
		case MODE_DECRYPT:	/* decrypt using ECB mode */
			ecbdec();
			break;
		case MODE_ENCRYPT:	/* encrypt using ECB mode */
			ecbenc();
			break;
		}
		break;
	case ALG_OFB:
		switch(mode) {
		case MODE_AUTHENTICATE:	/* authenticate using OFB mode */
			err(-1, "can't authenticate with OFB mode");
			break;
		case MODE_DECRYPT:	/* decrypt using OFB mode */
			ofbdec();
			break;
		case MODE_ENCRYPT:	/* encrypt using OFB mode */
			ofbenc();
			break;
		}
		break;
E 2
	}
	exit(0);
D 2

E 2
}

/*
 * print a warning message and, possibly, terminate
 */
D 2
err(f, n, s)
int f;			/* >0 if fatal (status code), 0 if not */
int n;			/* offending block number */
char *s;		/* the message */
E 2
I 2
err(n, s)
	int n;			/* offending block number */
	char *s;		/* the message */
E 2
{
D 2
	char tbuf[BUFSIZ];

E 2
	if (n > 0)
D 2
		(void) sprintf(tbuf, "%s (block %d)", progname, n);
E 2
I 2
		(void)fprintf(stderr, "bdes (block %d): ", n);
E 2
	else
D 2
		(void) sprintf(tbuf, "%s", progname);
	if (s == C_NULL)
		perror(tbuf);
	else
		fprintf(stderr, "%s: %s\n", tbuf, s);
	if (f > 0)
		exit(f);
E 2
I 2
		(void)fprintf(stderr, "bdes: ");
	(void)fprintf(stderr, "%s\n", s ? s : strerror(errno));
	exit(1);
E 2
}

/*
 * map a hex character to an integer
 */
D 2
int tobinhex(c, radix)
char c;
int radix;
E 2
I 2
tobinhex(c, radix)
D 3
	char c;
	int radix;
E 3
I 3
	char c;			/* char to be converted */
	int radix;		/* base (2 to 16) */
E 3
E 2
{
D 2
	switch(c){
E 2
I 2
	switch(c) {
E 2
	case '0':		return(0x0);
	case '1':		return(0x1);
	case '2':		return(radix > 2 ? 0x2 : -1);
	case '3':		return(radix > 3 ? 0x3 : -1);
	case '4':		return(radix > 4 ? 0x4 : -1);
	case '5':		return(radix > 5 ? 0x5 : -1);
	case '6':		return(radix > 6 ? 0x6 : -1);
	case '7':		return(radix > 7 ? 0x7 : -1);
	case '8':		return(radix > 8 ? 0x8 : -1);
	case '9':		return(radix > 9 ? 0x9 : -1);
	case 'A': case 'a':	return(radix > 10 ? 0xa : -1);
	case 'B': case 'b':	return(radix > 11 ? 0xb : -1);
	case 'C': case 'c':	return(radix > 12 ? 0xc : -1);
	case 'D': case 'd':	return(radix > 13 ? 0xd : -1);
	case 'E': case 'e':	return(radix > 14 ? 0xe : -1);
	case 'F': case 'f':	return(radix > 15 ? 0xf : -1);
	}
	/*
	 * invalid character
	 */
	return(-1);
}

/*
 * convert the key to a bit pattern
 */
cvtkey(obuf, ibuf)
D 2
char *obuf;
char *ibuf;
E 2
I 2
D 3
	char *obuf, *ibuf;
E 3
I 3
	char *obuf;			/* bit pattern */
	char *ibuf;			/* the key itself */
E 3
E 2
{
D 2
	register int i, j;			/* counter in a for loop */
E 2
I 2
	register int i, j;		/* counter in a for loop */
E 2
	int nbuf[64];			/* used for hex/key translation */

	/*
	 * just switch on the key base
	 */
D 2
	switch(keybase){
E 2
I 2
	switch(keybase) {
E 2
	case KEY_ASCII:			/* ascii to integer */
D 2
		(void) strncpy(obuf, ibuf, 8);
E 2
I 2
		(void)strncpy(obuf, ibuf, 8);
E 2
		return;
	case KEY_DEFAULT:		/* tell from context */
		/*
		 * leading '0x' or '0X' == hex key
		 */
D 2
		if (ibuf[0] == '0' && (ibuf[1] == 'x' || ibuf[1] == 'X')){
E 2
I 2
		if (ibuf[0] == '0' && (ibuf[1] == 'x' || ibuf[1] == 'X')) {
E 2
			ibuf = &ibuf[2];
			/*
			 * now translate it, bombing on any illegal hex digit
			 */
D 2
			for(i = 0; ibuf[i] && i < 16; i++)
E 2
I 2
			for (i = 0; ibuf[i] && i < 16; i++)
E 2
				if ((nbuf[i] = tobinhex(ibuf[i], 16)) == -1)
D 2
					err(1, -1, "bad hex digit in key");
			while(i < 16)
E 2
I 2
					err(-1, "bad hex digit in key");
			while (i < 16)
E 2
				nbuf[i++] = 0;
D 2
			for(i = 0; i < 8; i++)
				obuf[i] = ((nbuf[2*i]&0xf)<<4)|
							(nbuf[2*i+1]&0xf);
E 2
I 2
			for (i = 0; i < 8; i++)
				obuf[i] =
				    ((nbuf[2*i]&0xf)<<4) | (nbuf[2*i+1]&0xf);
E 2
			/* preserve parity bits */
			pflag = 1;
			return;
		}
		/*
		 * leading '0b' or '0B' == binary key
		 */
D 2
		if (ibuf[0] == '0' && (ibuf[1] == 'b' || ibuf[1] == 'B')){
E 2
I 2
		if (ibuf[0] == '0' && (ibuf[1] == 'b' || ibuf[1] == 'B')) {
E 2
			ibuf = &ibuf[2];
			/*
			 * now translate it, bombing on any illegal binary digit
			 */
D 2
			for(i = 0; ibuf[i] && i < 16; i++)
E 2
I 2
			for (i = 0; ibuf[i] && i < 16; i++)
E 2
				if ((nbuf[i] = tobinhex(ibuf[i], 2)) == -1)
D 2
					err(1, -1, "bad binary digit in key");
			while(i < 64)
E 2
I 2
					err(-1, "bad binary digit in key");
			while (i < 64)
E 2
				nbuf[i++] = 0;
D 2
			for(i = 0; i < 8; i++)
				for(j = 0; j < 8; j++)
E 2
I 2
			for (i = 0; i < 8; i++)
				for (j = 0; j < 8; j++)
E 2
					obuf[i] = (obuf[i]<<1)|nbuf[8*i+j];
			/* preserve parity bits */
			pflag = 1;
			return;
		}
		/*
		 * no special leader -- ASCII
		 */
D 2
		(void) strncpy(obuf, ibuf, 8);
E 2
I 2
		(void)strncpy(obuf, ibuf, 8);
E 2
	}
}

/*
 * convert an ASCII string into a decimal number:
 * 1. must be between 0 and 64 inclusive
 * 2. must be a valid decimal number
 * 3. must be a multiple of mult
 */
setbits(s, mult)
D 2
char *s;
int mult;
E 2
I 2
D 3
	char *s;
	int mult;
E 3
I 3
	char *s;			/* the ASCII string */
	int mult;			/* what it must be a multiple of */
E 3
E 2
{
D 3
	register char *p;
	register int n = 0;
E 3
I 3
	register char *p;		/* pointer in a for loop */
	register int n = 0;		/* the integer collected */
E 3

	/*
	 * skip white space
	 */
	while (isspace(*s))
		s++;
	/*
	 * get the integer
	 */
D 2
	for(p = s; *p; p++){
E 2
I 2
	for (p = s; *p; p++) {
E 2
		if (isdigit(*p))
			n = n * 10 + *p - '0';
D 2
		else{
			err(1, -1, "bad decimal digit in MAC length");
E 2
I 2
		else {
			err(-1, "bad decimal digit in MAC length");
E 2
		}
	}
	/*
	 * be sure it's a multiple of mult
	 */
	return((n % mult != 0) ? -1 : n);
}

/*****************
 * DES FUNCTIONS *
 *****************/
/*
 * This sets the DES key and (if you're using the deszip version)
 * the direction of the transformation.  This uses the Sun
 * to map the 64-bit key onto the 56 bits that the key schedule
 * generation routines use: the old way, which just uses the user-
 * supplied 64 bits as is, and the new way, which resets the parity
 * bit to be the same as the low-order bit in each character.  The
 * new way generates a greater variety of key schedules, since many
 * systems set the parity (high) bit of each character to 0, and the
 * DES ignores the low order bit of each character.
 */
makekey(buf)
D 2
Desbuf buf;			/* key block */
E 2
I 2
	Desbuf buf;				/* key block */
E 2
{
	register int i, j;			/* counter in a for loop */
	register int par;			/* parity counter */

	/*
	 * if the parity is not preserved, flip it
	 */
D 2
	if (!pflag){
		for(i = 0; i < 8; i++){
E 2
I 2
	if (!pflag) {
		for (i = 0; i < 8; i++) {
E 2
			par = 0;
D 2
			for(j = 1; j < 8; j++)
E 2
I 2
			for (j = 1; j < 8; j++)
E 2
				if ((bits[j]&UCHAR(buf, i)) != 0)
					par++;
			if ((par&01) == 01)
				UCHAR(buf, i) = UCHAR(buf, i)&0177;
			else
				UCHAR(buf, i) = (UCHAR(buf, i)&0177)|0200;
		}
	}
D 5
	/*
D 4
	 * Make the key schedule
E 4
I 4
	 * Make the key schedule.  If an error, the system probably does
	 * not have the encryption routines available.
E 4
	 */
I 4
	errno = 0;
E 5
I 5

E 5
E 4
	DES_KEY(UBUFFER(buf));
I 4
D 5
	if (errno)
		err(0, NULL);
E 5
E 4
}

/*
 * This encrypts using the Electronic Code Book mode of DES
 */
ecbenc()
{
	register int n;		/* number of bytes actually read */
	register int bn;	/* block number */
	Desbuf msgbuf;		/* I/O buffer */

D 2
	for(bn = 0; (n = READ(BUFFER(msgbuf),  8)) == 8; bn++){
E 2
I 2
	for (bn = 0; (n = READ(BUFFER(msgbuf),  8)) == 8; bn++) {
E 2
		/*
		 * do the transformation
		 */
		DES_XFORM(UBUFFER(msgbuf));
		WRITE(BUFFER(msgbuf), 8);
	}
	/*
	 * at EOF or last block -- in either ase, the last byte contains
	 * the character representation of the number of bytes in it
	 */
	bn++;
	MEMZERO(&CHAR(msgbuf, n), 8 - n);
	CHAR(msgbuf, 7) = n;
	DES_XFORM(UBUFFER(msgbuf));
	WRITE(BUFFER(msgbuf), 8);

}

/*
 * This decrypts using the Electronic Code Book mode of DES
 */
ecbdec()
{
	register int n;		/* number of bytes actually read */
	register int c;		/* used to test for EOF */
	register int bn;	/* block number */
	Desbuf msgbuf;		/* I/O buffer */

D 2
	for(bn = 1; (n = READ(BUFFER(msgbuf), 8)) == 8; bn++){
E 2
I 2
	for (bn = 1; (n = READ(BUFFER(msgbuf), 8)) == 8; bn++) {
E 2
		/*
		 * do the transformation
		 */
		DES_XFORM(UBUFFER(msgbuf));
		/*
		 * if the last one, handle it specially
		 */
D 2
		if ((c = getchar()) == EOF){
E 2
I 2
		if ((c = getchar()) == EOF) {
E 2
			n = CHAR(msgbuf, 7);
			if (n < 0 || n > 7)
D 2
				err(1, bn,
					"decryption failed (block corrupted)");
E 2
I 2
				err(bn, "decryption failed (block corrupted)");
E 2
		}
		else
D 2
			(void) ungetc(c, stdin);
E 2
I 2
			(void)ungetc(c, stdin);
E 2
		WRITE(BUFFER(msgbuf), n);
	}
	if (n > 0)
D 2
		err(1, bn, "decryption failed (incomplete block)");
E 2
I 2
		err(bn, "decryption failed (incomplete block)");
E 2
}

/*
 * This encrypts using the Cipher Block Chaining mode of DES
 */
cbcenc()
{
	register int n;		/* number of bytes actually read */
	register int bn;	/* block number */
	Desbuf msgbuf;		/* I/O buffer */

	/*
	 * do the transformation
	 */
D 2
	for(bn = 1; (n = READ(BUFFER(msgbuf), 8)) == 8; bn++){
		for(n = 0; n < 8; n++)
E 2
I 2
	for (bn = 1; (n = READ(BUFFER(msgbuf), 8)) == 8; bn++) {
		for (n = 0; n < 8; n++)
E 2
			CHAR(msgbuf, n) ^= CHAR(ivec, n);
		DES_XFORM(UBUFFER(msgbuf));
		MEMCPY(BUFFER(ivec), BUFFER(msgbuf), 8);
		WRITE(BUFFER(msgbuf), 8);
	}
	/*
	 * at EOF or last block -- in either case, the last byte contains
	 * the character representation of the number of bytes in it
	 */
	bn++;
	MEMZERO(&CHAR(msgbuf, n), 8 - n);
	CHAR(msgbuf, 7) = n;
D 2
	for(n = 0; n < 8; n++)
E 2
I 2
	for (n = 0; n < 8; n++)
E 2
		CHAR(msgbuf, n) ^= CHAR(ivec, n);
	DES_XFORM(UBUFFER(msgbuf));
	WRITE(BUFFER(msgbuf), 8);

}

/*
 * This decrypts using the Cipher Block Chaining mode of DES
 */
cbcdec()
{
	register int n;		/* number of bytes actually read */
	Desbuf msgbuf;		/* I/O buffer */
	Desbuf ibuf;		/* temp buffer for initialization vector */
	register int c;		/* used to test for EOF */
	register int bn;	/* block number */

D 2
	for(bn = 0; (n = READ(BUFFER(msgbuf), 8)) == 8; bn++){
E 2
I 2
	for (bn = 0; (n = READ(BUFFER(msgbuf), 8)) == 8; bn++) {
E 2
		/*
		 * do the transformation
		 */
		MEMCPY(BUFFER(ibuf), BUFFER(msgbuf), 8);
		DES_XFORM(UBUFFER(msgbuf));
D 2
		for(c = 0; c < 8; c++)
E 2
I 2
		for (c = 0; c < 8; c++)
E 2
			UCHAR(msgbuf, c) ^= UCHAR(ivec, c);
		MEMCPY(BUFFER(ivec), BUFFER(ibuf), 8);
		/*
		 * if the last one, handle it specially
		 */
D 2
		if ((c = getchar()) == EOF){
E 2
I 2
		if ((c = getchar()) == EOF) {
E 2
			n = CHAR(msgbuf, 7);
			if (n < 0 || n > 7)
D 2
				err(1, bn,
					"decryption failed (block corrupted)");
E 2
I 2
				err(bn, "decryption failed (block corrupted)");
E 2
		}
		else
D 2
			(void) ungetc(c, stdin);
E 2
I 2
			(void)ungetc(c, stdin);
E 2
		WRITE(BUFFER(msgbuf), n);
	}
	if (n > 0)
D 2
		err(1, bn, "decryption failed (incomplete block)");
E 2
I 2
		err(bn, "decryption failed (incomplete block)");
E 2
}

/*
 * This authenticates using the Cipher Block Chaining mode of DES
 */
cbcauth()
{
	register int n, j;		/* number of bytes actually read */
	Desbuf msgbuf;		/* I/O buffer */
	Desbuf encbuf;		/* encryption buffer */

	/*
	 * do the transformation
	 * note we DISCARD the encrypted block;
	 * we only care about the last one
	 */
D 2
	while ((n = READ(BUFFER(msgbuf), 8)) == 8){
		for(n = 0; n < 8; n++)
E 2
I 2
	while ((n = READ(BUFFER(msgbuf), 8)) == 8) {
		for (n = 0; n < 8; n++)
E 2
			CHAR(encbuf, n) = CHAR(msgbuf, n) ^ CHAR(ivec, n);
		DES_XFORM(UBUFFER(encbuf));
		MEMCPY(BUFFER(ivec), BUFFER(encbuf), 8);
	}
	/*
	 * now compute the last one, right padding with '\0' if need be
	 */
D 2
	if (n > 0){
E 2
I 2
	if (n > 0) {
E 2
		MEMZERO(&CHAR(msgbuf, n), 8 - n);
D 2
		for(n = 0; n < 8; n++)
E 2
I 2
		for (n = 0; n < 8; n++)
E 2
			CHAR(encbuf, n) = CHAR(msgbuf, n) ^ CHAR(ivec, n);
		DES_XFORM(UBUFFER(encbuf));
	}
	/*
	 * drop the bits
	 * we write chars until fewer than 7 bits,
	 * and then pad the last one with 0 bits
	 */
D 2
	for(n = 0; macbits > 7; n++, macbits -= 8)
		putchar(CHAR(encbuf, n));
	if (macbits > 0){
E 2
I 2
	for (n = 0; macbits > 7; n++, macbits -= 8)
		(void)putchar(CHAR(encbuf, n));
	if (macbits > 0) {
E 2
		CHAR(msgbuf, 0) = 0x00;
D 2
		for(j = 0; j < macbits; j++)
E 2
I 2
		for (j = 0; j < macbits; j++)
E 2
			CHAR(msgbuf, 0) |= (CHAR(encbuf, n)&bits[j]);
D 2
		putchar(CHAR(msgbuf, 0));
E 2
I 2
		(void)putchar(CHAR(msgbuf, 0));
E 2
	}
}

/*
 * This encrypts using the Cipher FeedBack mode of DES
 */
cfbenc()
{
	register int n;		/* number of bytes actually read */
	register int nbytes;	/* number of bytes to read */
	register int bn;	/* block number */
	char ibuf[8];		/* input buffer */
	Desbuf msgbuf;		/* encryption buffer */

	/*
	 * do things in bytes, not bits
	 */
	nbytes = fbbits / 8;
	/*
	 * do the transformation
	 */
D 2
	for(bn = 1; (n = READ(ibuf, nbytes)) == nbytes; bn++){
E 2
I 2
	for (bn = 1; (n = READ(ibuf, nbytes)) == nbytes; bn++) {
E 2
		MEMCPY(BUFFER(msgbuf), BUFFER(ivec), 8);
		DES_XFORM(UBUFFER(msgbuf));
D 2
		for(n = 0; n < 8 - nbytes; n++)
E 2
I 2
		for (n = 0; n < 8 - nbytes; n++)
E 2
			UCHAR(ivec, n) = UCHAR(ivec, n+nbytes);
D 2
		for(n = 0; n < nbytes; n++)
E 2
I 2
		for (n = 0; n < nbytes; n++)
E 2
			UCHAR(ivec, 8-nbytes+n) = ibuf[n] ^ UCHAR(msgbuf, n);
		WRITE(&CHAR(ivec, 8-nbytes), nbytes);
	}
	/*
	 * at EOF or last block -- in either case, the last byte contains
	 * the character representation of the number of bytes in it
	 */
	bn++;
	MEMZERO(&ibuf[n], nbytes - n);
	ibuf[nbytes - 1] = n;
	MEMCPY(BUFFER(msgbuf), BUFFER(ivec), 8);
	DES_XFORM(UBUFFER(msgbuf));
D 2
	for(n = 0; n < nbytes; n++)
E 2
I 2
	for (n = 0; n < nbytes; n++)
E 2
		ibuf[n] ^= UCHAR(msgbuf, n);
	WRITE(ibuf, nbytes);
}

/*
 * This decrypts using the Cipher Block Chaining mode of DES
 */
cfbdec()
{
	register int n;		/* number of bytes actually read */
	register int c;		/* used to test for EOF */
	register int nbytes;	/* number of bytes to read */
	register int bn;	/* block number */
	char ibuf[8];		/* input buffer */
	char obuf[8];		/* output buffer */
	Desbuf msgbuf;		/* encryption buffer */

	/*
	 * do things in bytes, not bits
	 */
	nbytes = fbbits / 8;
	/*
	 * do the transformation
	 */
D 2
	for(bn = 1; (n = READ(ibuf, nbytes)) == nbytes; bn++){
E 2
I 2
	for (bn = 1; (n = READ(ibuf, nbytes)) == nbytes; bn++) {
E 2
		MEMCPY(BUFFER(msgbuf), BUFFER(ivec), 8);
		DES_XFORM(UBUFFER(msgbuf));
D 2
		for(c = 0; c < 8 - nbytes; c++)
E 2
I 2
		for (c = 0; c < 8 - nbytes; c++)
E 2
			CHAR(ivec, c) = CHAR(ivec, c+nbytes);
D 2
		for(c = 0; c < nbytes; c++){
E 2
I 2
		for (c = 0; c < nbytes; c++) {
E 2
			CHAR(ivec, 8-nbytes+c) = ibuf[c];
			obuf[c] = ibuf[c] ^ UCHAR(msgbuf, c);
		}
		/*
		 * if the last one, handle it specially
		 */
D 2
		if ((c = getchar()) == EOF){
E 2
I 2
		if ((c = getchar()) == EOF) {
E 2
			n = obuf[nbytes-1];
			if (n < 0 || n > nbytes-1)
D 2
				err(1, bn,
					"decryption failed (block corrupted)");
E 2
I 2
				err(bn, "decryption failed (block corrupted)");
E 2
		}
		else
D 2
			(void) ungetc(c, stdin);
E 2
I 2
			(void)ungetc(c, stdin);
E 2
		WRITE(obuf, n);
	}
	if (n > 0)
D 2
		err(1, bn, "decryption failed (incomplete block)");
E 2
I 2
		err(bn, "decryption failed (incomplete block)");
E 2
}

/*
 * This encrypts using the alternative Cipher FeedBack mode of DES
 */
cfbaenc()
{
	register int n;		/* number of bytes actually read */
	register int nbytes;	/* number of bytes to read */
	register int bn;	/* block number */
	char ibuf[8];		/* input buffer */
	char obuf[8];		/* output buffer */
	Desbuf msgbuf;		/* encryption buffer */

	/*
	 * do things in bytes, not bits
	 */
	nbytes = fbbits / 7;
	/*
	 * do the transformation
	 */
D 2
	for(bn = 1; (n = READ(ibuf, nbytes)) == nbytes; bn++){
E 2
I 2
	for (bn = 1; (n = READ(ibuf, nbytes)) == nbytes; bn++) {
E 2
		MEMCPY(BUFFER(msgbuf), BUFFER(ivec), 8);
		DES_XFORM(UBUFFER(msgbuf));
D 2
		for(n = 0; n < 8 - nbytes; n++)
E 2
I 2
		for (n = 0; n < 8 - nbytes; n++)
E 2
			UCHAR(ivec, n) = UCHAR(ivec, n+nbytes);
D 2
		for(n = 0; n < nbytes; n++)
E 2
I 2
		for (n = 0; n < nbytes; n++)
E 2
			UCHAR(ivec, 8-nbytes+n) = (ibuf[n] ^ UCHAR(msgbuf, n))
							|0200;
D 2
		for(n = 0; n < nbytes; n++)
E 2
I 2
		for (n = 0; n < nbytes; n++)
E 2
			obuf[n] = CHAR(ivec, 8-nbytes+n)&0177;
		WRITE(obuf, nbytes);
	}
	/*
	 * at EOF or last block -- in either case, the last byte contains
	 * the character representation of the number of bytes in it
	 */
	bn++;
	MEMZERO(&ibuf[n], nbytes - n);
	ibuf[nbytes - 1] = ('0' + n)|0200;
	MEMCPY(BUFFER(msgbuf), BUFFER(ivec), 8);
	DES_XFORM(UBUFFER(msgbuf));
D 2
	for(n = 0; n < nbytes; n++)
E 2
I 2
	for (n = 0; n < nbytes; n++)
E 2
		ibuf[n] ^= UCHAR(msgbuf, n);
	WRITE(ibuf, nbytes);
}

/*
 * This decrypts using the alternative Cipher Block Chaining mode of DES
 */
cfbadec()
{
	register int n;		/* number of bytes actually read */
	register int c;		/* used to test for EOF */
	register int nbytes;	/* number of bytes to read */
	register int bn;	/* block number */
	char ibuf[8];		/* input buffer */
	char obuf[8];		/* output buffer */
	Desbuf msgbuf;		/* encryption buffer */

	/*
	 * do things in bytes, not bits
	 */
	nbytes = fbbits / 7;
	/*
	 * do the transformation
	 */
D 2
	for(bn = 1; (n = READ(ibuf, nbytes)) == nbytes; bn++){
E 2
I 2
	for (bn = 1; (n = READ(ibuf, nbytes)) == nbytes; bn++) {
E 2
		MEMCPY(BUFFER(msgbuf), BUFFER(ivec), 8);
		DES_XFORM(UBUFFER(msgbuf));
D 2
		for(c = 0; c < 8 - nbytes; c++)
E 2
I 2
		for (c = 0; c < 8 - nbytes; c++)
E 2
			CHAR(ivec, c) = CHAR(ivec, c+nbytes);
D 2
		for(c = 0; c < nbytes; c++){
E 2
I 2
		for (c = 0; c < nbytes; c++) {
E 2
			CHAR(ivec, 8-nbytes+c) = ibuf[c]|0200;
			obuf[c] = (ibuf[c] ^ UCHAR(msgbuf, c))&0177;
		}
		/*
		 * if the last one, handle it specially
		 */
D 2
		if ((c = getchar()) == EOF){
E 2
I 2
		if ((c = getchar()) == EOF) {
E 2
			if ((n = (obuf[nbytes-1] - '0')) < 0
						|| n > nbytes-1)
D 2
				err(1, bn, 
					"decryption failed (block corrupted)");
E 2
I 2
				err(bn, "decryption failed (block corrupted)");
E 2
		}
		else
D 2
			(void) ungetc(c, stdin);
E 2
I 2
			(void)ungetc(c, stdin);
E 2
		WRITE(obuf, n);
	}
	if (n > 0)
D 2
		err(1, bn, "decryption failed (incomplete block)");
E 2
I 2
		err(bn, "decryption failed (incomplete block)");
E 2
}


/*
 * This encrypts using the Output FeedBack mode of DES
 */
ofbenc()
{
	register int n;		/* number of bytes actually read */
	register int c;		/* used to test for EOF */
	register int nbytes;	/* number of bytes to read */
	register int bn;	/* block number */
	char ibuf[8];		/* input buffer */
	char obuf[8];		/* output buffer */
	Desbuf msgbuf;		/* encryption buffer */

	/*
	 * do things in bytes, not bits
	 */
	nbytes = fbbits / 8;
	/*
	 * do the transformation
	 */
D 2
	for(bn = 1; (n = READ(ibuf, nbytes)) == nbytes; bn++){
E 2
I 2
	for (bn = 1; (n = READ(ibuf, nbytes)) == nbytes; bn++) {
E 2
		MEMCPY(BUFFER(msgbuf), BUFFER(ivec), 8);
		DES_XFORM(UBUFFER(msgbuf));
D 2
		for(n = 0; n < 8 - nbytes; n++)
E 2
I 2
		for (n = 0; n < 8 - nbytes; n++)
E 2
			UCHAR(ivec, n) = UCHAR(ivec, n+nbytes);
D 2
		for(n = 0; n < nbytes; n++){
E 2
I 2
		for (n = 0; n < nbytes; n++) {
E 2
			UCHAR(ivec, 8-nbytes+n) = UCHAR(msgbuf, n);
			obuf[n] = ibuf[n] ^ UCHAR(msgbuf, n);
		}
		WRITE(obuf, nbytes);
	}
	/*
	 * at EOF or last block -- in either case, the last byte contains
	 * the character representation of the number of bytes in it
	 */
	bn++;
	MEMZERO(&ibuf[n], nbytes - n);
	ibuf[nbytes - 1] = n;
	MEMCPY(BUFFER(msgbuf), BUFFER(ivec), 8);
	DES_XFORM(UBUFFER(msgbuf));
D 2
	for(c = 0; c < nbytes; c++)
E 2
I 2
	for (c = 0; c < nbytes; c++)
E 2
		ibuf[c] ^= UCHAR(msgbuf, c);
	WRITE(ibuf, nbytes);
}

/*
 * This decrypts using the Output Block Chaining mode of DES
 */
ofbdec()
{
	register int n;		/* number of bytes actually read */
	register int c;		/* used to test for EOF */
	register int nbytes;	/* number of bytes to read */
	register int bn;	/* block number */
	char ibuf[8];		/* input buffer */
	char obuf[8];		/* output buffer */
	Desbuf msgbuf;		/* encryption buffer */

	/*
	 * do things in bytes, not bits
	 */
	nbytes = fbbits / 8;
	/*
	 * do the transformation
	 */
D 2
	for(bn = 1; (n = READ(ibuf, nbytes)) == nbytes; bn++){
E 2
I 2
	for (bn = 1; (n = READ(ibuf, nbytes)) == nbytes; bn++) {
E 2
		MEMCPY(BUFFER(msgbuf), BUFFER(ivec), 8);
		DES_XFORM(UBUFFER(msgbuf));
D 2
		for(c = 0; c < 8 - nbytes; c++)
E 2
I 2
		for (c = 0; c < 8 - nbytes; c++)
E 2
			CHAR(ivec, c) = CHAR(ivec, c+nbytes);
D 2
		for(c = 0; c < nbytes; c++){
E 2
I 2
		for (c = 0; c < nbytes; c++) {
E 2
			CHAR(ivec, 8-nbytes+c) = UCHAR(msgbuf, c);
			obuf[c] = ibuf[c] ^ UCHAR(msgbuf, c);
		}
		/*
		 * if the last one, handle it specially
		 */
D 2
		if ((c = getchar()) == EOF){
E 2
I 2
		if ((c = getchar()) == EOF) {
E 2
			n = obuf[nbytes-1];
			if (n < 0 || n > nbytes-1)
D 2
				err(1, bn,
					"decryption failed (block corrupted)");
E 2
I 2
				err(bn, "decryption failed (block corrupted)");
E 2
		}
		else
D 2
			(void) ungetc(c, stdin);
E 2
I 2
			(void)ungetc(c, stdin);
E 2
		/*
		 * dump it
		 */
		WRITE(obuf, n);
	}
	if (n > 0)
D 2
		err(1, bn, "decryption failed (incomplete block)");
E 2
I 2
		err(bn, "decryption failed (incomplete block)");
E 2
}

/*
 * This authenticates using the Cipher FeedBack mode of DES
 */
cfbauth()
{
	register int n, j;	/* number of bytes actually read */
	register int nbytes;	/* number of bytes to read */
	char ibuf[8];		/* input buffer */
	Desbuf msgbuf;		/* encryption buffer */

	/*
	 * do things in bytes, not bits
	 */
	nbytes = fbbits / 8;
	/*
	 * do the transformation
	 */
D 2
	while((n = READ(ibuf, nbytes)) == nbytes){
E 2
I 2
	while ((n = READ(ibuf, nbytes)) == nbytes) {
E 2
		MEMCPY(BUFFER(msgbuf), BUFFER(ivec), 8);
		DES_XFORM(UBUFFER(msgbuf));
D 2
		for(n = 0; n < 8 - nbytes; n++)
E 2
I 2
		for (n = 0; n < 8 - nbytes; n++)
E 2
			UCHAR(ivec, n) = UCHAR(ivec, n+nbytes);
D 2
		for(n = 0; n < nbytes; n++)
E 2
I 2
		for (n = 0; n < nbytes; n++)
E 2
			UCHAR(ivec, 8-nbytes+n) = ibuf[n] ^ UCHAR(msgbuf, n);
	}
	/*
	 * at EOF or last block -- in either case, the last byte contains
	 * the character representation of the number of bytes in it
	 */
	MEMZERO(&ibuf[n], nbytes - n);
	ibuf[nbytes - 1] = '0' + n;
	MEMCPY(BUFFER(msgbuf), BUFFER(ivec), 8);
	DES_XFORM(UBUFFER(msgbuf));
D 2
	for(n = 0; n < nbytes; n++)
E 2
I 2
	for (n = 0; n < nbytes; n++)
E 2
		ibuf[n] ^= UCHAR(msgbuf, n);
	/*
	 * drop the bits
	 * we write chars until fewer than 7 bits,
	 * and then pad the last one with 0 bits
	 */
D 2
	for(n = 0; macbits > 7; n++, macbits -= 8)
		putchar(CHAR(msgbuf, n));
	if (macbits > 0){
E 2
I 2
	for (n = 0; macbits > 7; n++, macbits -= 8)
		(void)putchar(CHAR(msgbuf, n));
	if (macbits > 0) {
E 2
		CHAR(msgbuf, 0) = 0x00;
D 2
		for(j = 0; j < macbits; j++)
E 2
I 2
		for (j = 0; j < macbits; j++)
E 2
			CHAR(msgbuf, 0) |= (CHAR(msgbuf, n)&bits[j]);
D 2
		putchar(CHAR(msgbuf, 0));
E 2
I 2
		(void)putchar(CHAR(msgbuf, 0));
E 2
	}
}

I 4
#ifndef FASTWAY
E 4
/*
 * change from 8 bits/Uchar to 1 bit/Uchar
 */
expand(from, to)
D 3
Desbuf from;			/* 8bit/unsigned char string */
char to[64];			/* 1bit/char string */
E 3
I 3
	Desbuf from;			/* 8bit/unsigned char string */
	char *to;			/* 1bit/char string */
E 3
{
	register int i, j;		/* counters in for loop */

D 2
	for(i = 0; i < 8; i++)
		for(j = 0; j < 8; j++)
E 2
I 2
	for (i = 0; i < 8; i++)
		for (j = 0; j < 8; j++)
E 2
D 3
			to[i*8+j] = (CHAR(from, i)>>(7-j))&01;
E 3
I 3
			*to++ = (CHAR(from, i)>>(7-j))&01;
E 3
}

/*
 * change from 1 bit/char to 8 bits/Uchar
 */
compress(from, to)
D 3
char from[64];			/* 1bit/char string */
Desbuf to;			/* 8bit/unsigned char string */
E 3
I 3
	char *from;			/* 1bit/char string */
	Desbuf to;			/* 8bit/unsigned char string */
E 3
{
	register int i, j;		/* counters in for loop */

D 2
	for(i = 0; i < 8; i++){
E 2
I 2
	for (i = 0; i < 8; i++) {
E 2
	 	CHAR(to, i) = 0;
D 2
		for(j = 0; j < 8; j++)
E 2
I 2
		for (j = 0; j < 8; j++)
E 2
D 3
			CHAR(to, i) = (from[i*8+j]<<(7-j))|CHAR(to, i);
E 3
I 3
			CHAR(to, i) = ((*from++)<<(7-j))|CHAR(to, i);
E 3
	}
}
I 4
#endif
E 4

I 3
/*
 * message about usage
 */
E 3
I 2
usage()
{
D 3
	(void)fprintf(stderr,
"usage: bdes [-aceip] [-F bit] [-f bit] [-m bit] [-o bit] [-v vector] [key]\n");
E 3
I 3
	(void)fprintf(stderr, "%s\n", 
"usage: bdes [-abdp] [-F bit] [-f bit] [-k key] [-m bit] [-o bit] [-v vector]");
E 3
	exit(1);
}
E 2
E 1
