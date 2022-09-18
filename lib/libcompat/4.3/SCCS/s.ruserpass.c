h46134
s 00004/00003/00812
d D 5.10 92/07/03 10:17:37 torek 14 12
c declare static functions as static before defining as static (for ANSI C)
e
s 00001/00001/00814
d R 5.10 92/07/03 10:15:58 torek 13 12
c nbs8{de,en}crypt are static; say so up front
e
s 00003/00002/00812
d D 5.9 91/11/26 11:10:35 mckusick 12 11
c properly reverse strings (4.3BSD/lib/157)
e
s 00014/00009/00800
d D 5.8 91/02/24 15:35:29 bostic 11 10
c Add include files to get prototype declarations, and fix bugs found.
e
s 00001/00011/00808
d D 5.7 90/06/01 14:18:38 bostic 10 9
c new copyright notice
e
s 00003/00003/00816
d D 5.6 90/02/21 13:44:41 bostic 9 8
c rearrange the includes to be reasonable (utmp.h needs types.h)
e
s 00010/00005/00809
d D 5.5 88/06/27 17:14:36 bostic 8 7
c install approved copyright notice
e
s 00009/00003/00805
d D 5.4 88/03/07 21:17:29 bostic 7 6
c added Berkeley specific header
e
s 00002/00002/00806
d D 5.3 87/10/22 17:43:30 bostic 6 5
c ANSI C; sprintf now returns an int.
e
s 00002/00002/00806
d D 5.2 86/03/09 20:27:58 donn 5 4
c added LIBC_SCCS condition for sccs ids
e
s 00008/00002/00800
d D 5.1 85/05/30 12:08:39 dist 4 3
c Add copyright
e
s 00004/00001/00798
d D 4.2 82/10/10 16:24:19 sam 3 1
c don't perror just because the .netrc file isn't there
e
s 00003/00001/00798
d R 4.2 82/10/10 16:22:48 sam 2 1
c tired of perror just because I don't have a .netrc file
e
s 00799/00000/00000
d D 4.1 82/02/21 14:16:52 mckusick 1 0
c date and time created 82/02/21 14:16:52 by mckusick
e
u
U
t
T
I 1
D 4
/* Copyright (c) 1982 Regents of the University of California */
E 4
I 4
/*
 * Copyright (c) 1983 Regents of the University of California.
D 7
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 7
I 7
 * All rights reserved.
 *
D 10
 * Redistribution and use in source and binary forms are permitted
D 8
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 8
I 8
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
E 10
I 10
 * %sccs.include.redist.c%
E 10
E 8
E 7
 */
E 4

D 4
static char sccsid[] = "%Z%%M% %I% %G%";
E 4
I 4
D 5
#ifndef lint
E 5
I 5
#if defined(LIBC_SCCS) && !defined(lint)
E 5
static char sccsid[] = "%W% (Berkeley) %G%";
D 5
#endif not lint
E 5
I 5
D 7
#endif LIBC_SCCS and not lint
E 7
I 7
#endif /* LIBC_SCCS and not lint */
E 7
E 5
E 4

D 9
#include <stdio.h>
#include <utmp.h>
#include <ctype.h>
E 9
#include <sys/types.h>
#include <sys/stat.h>
I 3
#include <errno.h>
I 9
#include <utmp.h>
#include <ctype.h>
I 11
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
E 11
#include <stdio.h>
E 9
E 3

D 11
char	*renvlook(), *malloc(), *index(), *getenv(), *getpass(), *getlogin();
E 11
I 11
static void blkencrypt(), enblkclr(), enblknot(), nbssetkey(), rnetrc();
static int token();
static char *renvlook();
E 11
D 14
struct	utmp *getutmp();
E 14
I 14
static struct utmp *getutmp();

E 14
static	FILE *cfile;

ruserpass(host, aname, apass)
	char *host, **aname, **apass;
{
I 11
	static void renv();
E 11

	renv(host, aname, apass);
	if (*aname == 0 || *apass == 0)
		rnetrc(host, aname, apass);
	if (*aname == 0) {
		char *myname = getlogin();
		*aname = malloc(16);
		printf("Name (%s:%s): ", host, myname);
		fflush(stdout);
		if (read(2, *aname, 16) <= 0)
			exit(1);
		if ((*aname)[0] == '\n')
			*aname = myname;
		else
			if (index(*aname, '\n'))
				*index(*aname, '\n') = 0;
	}
	if (*aname && *apass == 0) {
		printf("Password (%s:%s): ", host, *aname);
		fflush(stdout);
		*apass = getpass("");
	}
}

D 11
static
E 11
I 11
static void
E 11
renv(host, aname, apass)
	char *host, **aname, **apass;
{
	register char *cp;
	char *stemp, fgetlogin, *comma;

	cp = renvlook(host);
	if (cp == NULL)
		return;
	if (!isalpha(cp[0]))
		return;
	comma = index(cp, ',');
	if (comma == 0)
		return;
	if (*aname == 0) {
		*aname = malloc(comma - cp + 1);
		strncpy(*aname, cp, comma - cp);
	} else
		if (strncmp(*aname, cp, comma - cp))
			return;
	comma++;
	cp = malloc(strlen(comma)+1);
	strcpy(cp, comma);
	*apass = malloc(16);
	mkpwclear(cp, host[0], *apass);
}

D 11
static
char *
E 11
I 11
static char *
E 11
renvlook(host)
	char *host;
{
	register char *cp, **env;
	extern char **environ;

	env = environ;
	for (env = environ; *env != NULL; env++)
		if (!strncmp(*env, "MACH", 4)) {
			cp = index(*env, '=');
			if (cp == 0)
				continue;
			if (strncmp(*env+4, host, cp-(*env+4)))
				continue;
			return (cp+1);
		}
	return (NULL);
}

#define	DEFAULT	1
#define	LOGIN	2
#define	PASSWD	3
#define	NOTIFY	4
#define	WRITE	5
#define	YES	6
#define	NO	7
#define	COMMAND	8
#define	FORCE	9
#define	ID	10
#define	MACHINE	11

static char tokval[100];

static struct toktab {
	char *tokstr;
	int tval;
} toktab[]= {
	"default",	DEFAULT,
	"login",	LOGIN,
	"password",	PASSWD,
	"notify",	NOTIFY,
	"write",	WRITE,
	"yes",		YES,
	"y",		YES,
	"no",		NO,
	"n",		NO,
	"command",	COMMAND,
	"force",	FORCE,
	"machine",	MACHINE,
	0,		0
};

D 11
static
E 11
I 11
static void
E 11
rnetrc(host, aname, apass)
	char *host, **aname, **apass;
{
	char *hdir, buf[BUFSIZ];
	int t;
	struct stat stb;
I 3
	extern int errno;
E 3

	hdir = getenv("HOME");
	if (hdir == NULL)
		hdir = ".";
D 6
	sprintf(buf, "%s/.netrc", hdir);
E 6
I 6
	(void)sprintf(buf, "%s/.netrc", hdir);
E 6
	cfile = fopen(buf, "r");
	if (cfile == NULL) {
D 3
		perror(buf);
E 3
I 3
		if (errno != ENOENT)
			perror(buf);
E 3
		return;
	}
next:
	while ((t = token())) switch(t) {

	case DEFAULT:
		(void) token();
		continue;

	case MACHINE:
		if (token() != ID || strcmp(host, tokval))
			continue;
		while ((t = token()) && t != MACHINE) switch(t) {

		case LOGIN:
			if (token())
				if (*aname == 0) { 
					*aname = malloc(strlen(tokval) + 1);
					strcpy(*aname, tokval);
				} else {
					if (strcmp(*aname, tokval))
						goto next;
				}
			break;
		case PASSWD:
			if (fstat(fileno(cfile), &stb) >= 0
			    && (stb.st_mode & 077) != 0) {
	fprintf(stderr, "Error - .netrc file not correct mode.\n");
	fprintf(stderr, "Remove password or correct mode.\n");
				exit(1);
			}
			if (token() && *apass == 0) {
				*apass = malloc(strlen(tokval) + 1);
				strcpy(*apass, tokval);
			}
			break;
		case COMMAND:
		case NOTIFY:
		case WRITE:
		case FORCE:
			(void) token();
			break;
		default:
	fprintf(stderr, "Unknown .netrc option %s\n", tokval);
			break;
		}
		goto done;
	}
done:
	fclose(cfile);
}

static
token()
{
	char *cp;
	int c;
	struct toktab *t;

	if (feof(cfile))
		return (0);
	while ((c = getc(cfile)) != EOF &&
	    (c == '\n' || c == '\t' || c == ' ' || c == ','))
		continue;
	if (c == EOF)
		return (0);
	cp = tokval;
	if (c == '"') {
		while ((c = getc(cfile)) != EOF && c != '"') {
			if (c == '\\')
				c = getc(cfile);
			*cp++ = c;
		}
	} else {
		*cp++ = c;
		while ((c = getc(cfile)) != EOF
		    && c != '\n' && c != '\t' && c != ' ' && c != ',') {
			if (c == '\\')
				c = getc(cfile);
			*cp++ = c;
		}
	}
	*cp = 0;
	if (tokval[0] == 0)
		return (0);
	for (t = toktab; t->tokstr; t++)
		if (!strcmp(t->tokstr, tokval))
			return (t->tval);
	return (ID);
}
/* rest is nbs.c stolen from berknet */

D 14
char *deblknot(), *deblkclr();
char *nbs8decrypt(), *nbs8encrypt();
E 14
I 14
static char *deblknot(), *deblkclr();
static char *nbs8decrypt(), *nbs8encrypt();
E 14
static char	E[48];

/*
 * The E bit-selection table.
 */
static char	e[] = {
	32, 1, 2, 3, 4, 5,
	 4, 5, 6, 7, 8, 9,
	 8, 9,10,11,12,13,
	12,13,14,15,16,17,
	16,17,18,19,20,21,
	20,21,22,23,24,25,
	24,25,26,27,28,29,
	28,29,30,31,32, 1,
};
static
char *nbsencrypt(str,key,result)
  char *result;
  char *str, *key; {
	static char buf[20],oldbuf[20];
	register int j;
	result[0] = 0;
	strcpy(oldbuf,key);
	while(*str){
		for(j=0;j<10;j++)buf[j] = 0;
		for(j=0;j<8 && *str;j++)buf[j] = *str++;
		strcat(result,nbs8encrypt(buf,oldbuf));
		strcat(result,"$");
		strcpy(oldbuf,buf);
		}
	return(result);
	}
static
char *nbsdecrypt(cpt,key,result)
  char *result;
  char *cpt,*key; {
	char *s;
	char c,oldbuf[20];
	result[0] = 0;
	strcpy(oldbuf,key);
	while(*cpt){
		for(s = cpt;*s && *s != '$';s++);
		c = *s;
		*s = 0;
		strcpy(oldbuf,nbs8decrypt(cpt,oldbuf));
		strcat(result,oldbuf);
		if(c == 0)break;
		cpt = s + 1;
		}
	return(result);
	}

static
char *nbs8encrypt(str,key)
char *str, *key; {
	static char keyblk[100], blk[100];
	register int i;

	enblkclr(keyblk,key);
	nbssetkey(keyblk);

	for(i=0;i<48;i++) E[i] = e[i];
	enblkclr(blk,str);
	blkencrypt(blk,0);			/* forward dir */

	return(deblknot(blk));
}

static
char *nbs8decrypt(crp,key)
char *crp, *key; {
	static char keyblk[100], blk[100];
	register int i;

	enblkclr(keyblk,key);
	nbssetkey(keyblk);

	for(i=0;i<48;i++) E[i] = e[i];
	enblknot(blk,crp);
	blkencrypt(blk,1);			/* backward dir */

	return(deblkclr(blk));
}

D 11
static
E 11
I 11
static void
E 11
enblkclr(blk,str)		/* ignores top bit of chars in string str */
char *blk,*str; {
	register int i,j;
	char c;
	for(i=0;i<70;i++)blk[i] = 0;
	for(i=0; (c= *str) && i<64; str++){
		for(j=0; j<7; j++, i++)
			blk[i] = (c>>(6-j)) & 01;
		i++;
		}
	}

static
char *deblkclr(blk)
char *blk; {
	register int i,j;
	char c;
	static char iobuf[30];
	for(i=0; i<10; i++){
		c = 0;
		for(j=0; j<7; j++){
			c <<= 1;
			c |= blk[8*i+j];
			}
		iobuf[i] = c;
	}
	iobuf[i] = 0;
	return(iobuf);
	}

D 11
static
E 11
I 11
static void
E 11
enblknot(blk,crp)
char *blk;
char *crp; {
	register int i,j;
	char c;
	for(i=0;i<70;i++)blk[i] = 0;
	for(i=0; (c= *crp) && i<64; crp++){
		if(c>'Z') c -= 6;
		if(c>'9') c -= 7;
		c -= '.';
		for(j=0; j<6; j++, i++)
			blk[i] = (c>>(5-j)) & 01;
		}
	}

static
char *deblknot(blk)
char *blk; {
	register int i,j;
	char c;
	static char iobuf[30];
	for(i=0; i<11; i++){
		c = 0;
		for(j=0; j<6; j++){
			c <<= 1;
			c |= blk[6*i+j];
			}
		c += '.';
		if(c > '9')c += 7;
		if(c > 'Z')c += 6;
		iobuf[i] = c;
	}
	iobuf[i] = 0;
	return(iobuf);
}

/*
 * This program implements the
 * Proposed Federal Information Processing
 *  Data Encryption Standard.
 * See Federal Register, March 17, 1975 (40FR12134)
 */

/*
 * Initial permutation,
 */
static	char	IP[] = {
	58,50,42,34,26,18,10, 2,
	60,52,44,36,28,20,12, 4,
	62,54,46,38,30,22,14, 6,
	64,56,48,40,32,24,16, 8,
	57,49,41,33,25,17, 9, 1,
	59,51,43,35,27,19,11, 3,
	61,53,45,37,29,21,13, 5,
	63,55,47,39,31,23,15, 7,
};

/*
 * Final permutation, FP = IP^(-1)
 */
static	char	FP[] = {
	40, 8,48,16,56,24,64,32,
	39, 7,47,15,55,23,63,31,
	38, 6,46,14,54,22,62,30,
	37, 5,45,13,53,21,61,29,
	36, 4,44,12,52,20,60,28,
	35, 3,43,11,51,19,59,27,
	34, 2,42,10,50,18,58,26,
	33, 1,41, 9,49,17,57,25,
};

/*
 * Permuted-choice 1 from the key bits
 * to yield C and D.
 * Note that bits 8,16... are left out:
 * They are intended for a parity check.
 */
static	char	PC1_C[] = {
	57,49,41,33,25,17, 9,
	 1,58,50,42,34,26,18,
	10, 2,59,51,43,35,27,
	19,11, 3,60,52,44,36,
};

static	char	PC1_D[] = {
	63,55,47,39,31,23,15,
	 7,62,54,46,38,30,22,
	14, 6,61,53,45,37,29,
	21,13, 5,28,20,12, 4,
};

/*
 * Sequence of shifts used for the key schedule.
*/
static	char	shifts[] = {
	1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1,
};

/*
 * Permuted-choice 2, to pick out the bits from
 * the CD array that generate the key schedule.
 */
static	char	PC2_C[] = {
	14,17,11,24, 1, 5,
	 3,28,15, 6,21,10,
	23,19,12, 4,26, 8,
	16, 7,27,20,13, 2,
};

static	char	PC2_D[] = {
	41,52,31,37,47,55,
	30,40,51,45,33,48,
	44,49,39,56,34,53,
	46,42,50,36,29,32,
};

/*
 * The C and D arrays used to calculate the key schedule.
 */

static	char	C[28];
static	char	D[28];
/*
 * The key schedule.
 * Generated from the key.
 */
static	char	KS[16][48];

/*
 * Set up the key schedule from the key.
 */

D 11
static
E 11
I 11
static void
E 11
nbssetkey(key)
char *key;
{
	register i, j, k;
	int t;

	/*
	 * First, generate C and D by permuting
	 * the key.  The low order bit of each
	 * 8-bit char is not used, so C and D are only 28
	 * bits apiece.
	 */
	for (i=0; i<28; i++) {
		C[i] = key[PC1_C[i]-1];
		D[i] = key[PC1_D[i]-1];
	}
	/*
	 * To generate Ki, rotate C and D according
	 * to schedule and pick up a permutation
	 * using PC2.
	 */
	for (i=0; i<16; i++) {
		/*
		 * rotate.
		 */
		for (k=0; k<shifts[i]; k++) {
			t = C[0];
			for (j=0; j<28-1; j++)
				C[j] = C[j+1];
			C[27] = t;
			t = D[0];
			for (j=0; j<28-1; j++)
				D[j] = D[j+1];
			D[27] = t;
		}
		/*
		 * get Ki. Note C and D are concatenated.
		 */
		for (j=0; j<24; j++) {
			KS[i][j] = C[PC2_C[j]-1];
			KS[i][j+24] = D[PC2_D[j]-28-1];
		}
	}
}


/*
 * The 8 selection functions.
 * For some reason, they give a 0-origin
 * index, unlike everything else.
 */
static	char	S[8][64] = {
	14, 4,13, 1, 2,15,11, 8, 3,10, 6,12, 5, 9, 0, 7,
	 0,15, 7, 4,14, 2,13, 1,10, 6,12,11, 9, 5, 3, 8,
	 4, 1,14, 8,13, 6, 2,11,15,12, 9, 7, 3,10, 5, 0,
	15,12, 8, 2, 4, 9, 1, 7, 5,11, 3,14,10, 0, 6,13,

	15, 1, 8,14, 6,11, 3, 4, 9, 7, 2,13,12, 0, 5,10,
	 3,13, 4, 7,15, 2, 8,14,12, 0, 1,10, 6, 9,11, 5,
	 0,14, 7,11,10, 4,13, 1, 5, 8,12, 6, 9, 3, 2,15,
	13, 8,10, 1, 3,15, 4, 2,11, 6, 7,12, 0, 5,14, 9,

	10, 0, 9,14, 6, 3,15, 5, 1,13,12, 7,11, 4, 2, 8,
	13, 7, 0, 9, 3, 4, 6,10, 2, 8, 5,14,12,11,15, 1,
	13, 6, 4, 9, 8,15, 3, 0,11, 1, 2,12, 5,10,14, 7,
	 1,10,13, 0, 6, 9, 8, 7, 4,15,14, 3,11, 5, 2,12,

	 7,13,14, 3, 0, 6, 9,10, 1, 2, 8, 5,11,12, 4,15,
	13, 8,11, 5, 6,15, 0, 3, 4, 7, 2,12, 1,10,14, 9,
	10, 6, 9, 0,12,11, 7,13,15, 1, 3,14, 5, 2, 8, 4,
	 3,15, 0, 6,10, 1,13, 8, 9, 4, 5,11,12, 7, 2,14,

	 2,12, 4, 1, 7,10,11, 6, 8, 5, 3,15,13, 0,14, 9,
	14,11, 2,12, 4, 7,13, 1, 5, 0,15,10, 3, 9, 8, 6,
	 4, 2, 1,11,10,13, 7, 8,15, 9,12, 5, 6, 3, 0,14,
	11, 8,12, 7, 1,14, 2,13, 6,15, 0, 9,10, 4, 5, 3,

	12, 1,10,15, 9, 2, 6, 8, 0,13, 3, 4,14, 7, 5,11,
	10,15, 4, 2, 7,12, 9, 5, 6, 1,13,14, 0,11, 3, 8,
	 9,14,15, 5, 2, 8,12, 3, 7, 0, 4,10, 1,13,11, 6,
	 4, 3, 2,12, 9, 5,15,10,11,14, 1, 7, 6, 0, 8,13,

	 4,11, 2,14,15, 0, 8,13, 3,12, 9, 7, 5,10, 6, 1,
	13, 0,11, 7, 4, 9, 1,10,14, 3, 5,12, 2,15, 8, 6,
	 1, 4,11,13,12, 3, 7,14,10,15, 6, 8, 0, 5, 9, 2,
	 6,11,13, 8, 1, 4,10, 7, 9, 5, 0,15,14, 2, 3,12,

	13, 2, 8, 4, 6,15,11, 1,10, 9, 3,14, 5, 0,12, 7,
	 1,15,13, 8,10, 3, 7, 4,12, 5, 6,11, 0,14, 9, 2,
	 7,11, 4, 1, 9,12,14, 2, 0, 6,10,13,15, 3, 5, 8,
	 2, 1,14, 7, 4,10, 8,13,15,12, 9, 0, 3, 5, 6,11,
};

/*
 * P is a permutation on the selected combination
 * of the current L and key.
 */
static	char	P[] = {
	16, 7,20,21,
	29,12,28,17,
	 1,15,23,26,
	 5,18,31,10,
	 2, 8,24,14,
	32,27, 3, 9,
	19,13,30, 6,
	22,11, 4,25,
};

/*
 * The current block, divided into 2 halves.
 */
static	char	L[32], R[32];
static	char	tempL[32];
static	char	f[32];

/*
 * The combination of the key and the input, before selection.
 */
static	char	preS[48];

/*
 * The payoff: encrypt a block.
 */

D 11
static
E 11
I 11
static void
E 11
blkencrypt(block, edflag)
char *block;
{
	int i, ii;
	register t, j, k;

	/*
	 * First, permute the bits in the input
	 */
	for (j=0; j<64; j++)
		L[j] = block[IP[j]-1];
	/*
	 * Perform an encryption operation 16 times.
	 */
	for (ii=0; ii<16; ii++) {
		/*
		 * Set direction
		 */
		if (edflag)
			i = 15-ii;
		else
			i = ii;
		/*
		 * Save the R array,
		 * which will be the new L.
		 */
		for (j=0; j<32; j++)
			tempL[j] = R[j];
		/*
		 * Expand R to 48 bits using the E selector;
		 * exclusive-or with the current key bits.
		 */
		for (j=0; j<48; j++)
			preS[j] = R[E[j]-1] ^ KS[i][j];
		/*
		 * The pre-select bits are now considered
		 * in 8 groups of 6 bits each.
		 * The 8 selection functions map these
		 * 6-bit quantities into 4-bit quantities
		 * and the results permuted
		 * to make an f(R, K).
		 * The indexing into the selection functions
		 * is peculiar; it could be simplified by
		 * rewriting the tables.
		 */
		for (j=0; j<8; j++) {
			t = 6*j;
			k = S[j][(preS[t+0]<<5)+
				(preS[t+1]<<3)+
				(preS[t+2]<<2)+
				(preS[t+3]<<1)+
				(preS[t+4]<<0)+
				(preS[t+5]<<4)];
			t = 4*j;
			f[t+0] = (k>>3)&01;
			f[t+1] = (k>>2)&01;
			f[t+2] = (k>>1)&01;
			f[t+3] = (k>>0)&01;
		}
		/*
		 * The new R is L ^ f(R, K).
		 * The f here has to be permuted first, though.
		 */
		for (j=0; j<32; j++)
			R[j] = L[j] ^ f[P[j]-1];
		/*
		 * Finally, the new L (the original R)
		 * is copied back.
		 */
		for (j=0; j<32; j++)
			L[j] = tempL[j];
	}
	/*
	 * The output L and R are reversed.
	 */
	for (j=0; j<32; j++) {
		t = L[j];
		L[j] = R[j];
		R[j] = t;
	}
	/*
	 * The final output
	 * gets the inverse permutation of the very original.
	 */
	for (j=0; j<64; j++)
		block[j] = L[FP[j]-1];
}
/*
	getutmp()
	return a pointer to the system utmp structure associated with
	terminal sttyname, e.g. "/dev/tty3"
	Is version independent-- will work on v6 systems
	return NULL if error
*/
static
struct utmp *getutmp(sttyname)
char *sttyname;
{
	static struct utmp utmpstr;
	FILE *fdutmp;

	if(sttyname == NULL || sttyname[0] == 0)return(NULL);

	fdutmp = fopen("/etc/utmp","r");
	if(fdutmp == NULL)return(NULL);

	while(fread(&utmpstr,1,sizeof utmpstr,fdutmp) == sizeof utmpstr)
		if(strcmp(utmpstr.ut_line,sttyname+5) == 0){
			fclose(fdutmp);
			return(&utmpstr);
		}
	fclose(fdutmp);
	return(NULL);
}

static
sreverse(sto, sfrom)
	register char *sto, *sfrom;
{
	register int i;

	i = strlen(sfrom);
D 12
	while (i >= 0)
		*sto++ = sfrom[i--];
E 12
I 12
	while (i > 0)
		*sto++ = sfrom[--i];
	*sto = '\0';
E 12
}

static
char *mkenvkey(mch)
	char mch;
{
	static char skey[40];
	register struct utmp *putmp;
	char stemp[40], stemp1[40], sttyname[30];
	register char *sk,*p;

	if (isatty(2))
		strcpy(sttyname,ttyname(2));
	else if (isatty(0))
		strcpy(sttyname,ttyname(0));
	else if (isatty(1))
		strcpy(sttyname,ttyname(1));
	else
		return (NULL);
	putmp = getutmp(sttyname);
	if (putmp == NULL)
		return (NULL);
	sk = skey;
	p = putmp->ut_line;
	while (*p)
		*sk++ = *p++;
	*sk++ = mch;
D 6
	sprintf(stemp, "%ld", putmp->ut_time);
E 6
I 6
	(void)sprintf(stemp, "%ld", putmp->ut_time);
E 6
	sreverse(stemp1, stemp);
	p = stemp1;
	while (*p)
		*sk++ = *p++;
	*sk = 0;
	return (skey);
}

mkpwunclear(spasswd,mch,sencpasswd)
	char mch, *spasswd, *sencpasswd;
{
	register char *skey;

	if (spasswd[0] == 0) {
		sencpasswd[0] = 0;
		return;
	}
	skey = mkenvkey(mch);
	if (skey == NULL) {
		fprintf(stderr, "Can't make key\n");
		exit(1);
	}
	nbsencrypt(spasswd, skey, sencpasswd);
}

mkpwclear(sencpasswd,mch,spasswd)
	char mch, *spasswd, *sencpasswd;
{
	register char *skey;

	if (sencpasswd[0] == 0) {
		spasswd[0] = 0;
		return;
	}
	skey = mkenvkey(mch);
	if (skey == NULL) {
		fprintf(stderr, "Can't make key\n");
		exit(1);
	}
	nbsdecrypt(sencpasswd, skey, spasswd);
}
E 1
