h04658
s 00002/00001/00156
d D 8.2 95/05/03 18:53:03 mckusick 27 26
c lint
e
s 00002/00002/00155
d D 8.1 93/06/04 12:01:19 bostic 26 25
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00003/00153
d D 5.23 92/10/04 12:53:09 bostic 25 24
c <sys/errno.h> -> <errno.h>
e
s 00006/00002/00150
d D 5.22 92/10/03 16:29:25 ralph 24 23
c the field p_frag is a character and cgetnum takes apointer to a long.
c This causes an unaligned exception in some CPUs.
e
s 00004/00030/00148
d D 5.21 92/09/14 16:23:24 elan 23 22
c Added SCCS keywords.
e
s 00057/00287/00121
d D 5.20 92/09/01 11:20:20 elan 22 21
c Rewrote to use new getcap(3) library.
e
s 00004/00002/00404
d D 5.19 92/03/19 08:59:22 bostic 21 20
c put ": " after file name in error message
c don't call error just because reach the end of the disktab file
c from Craig Leres
e
s 00001/00001/00405
d D 5.18 91/11/04 21:40:23 bostic 20 19
c break FFS into UFS/FFS/LFS
e
s 00009/00001/00397
d D 5.17 91/02/23 19:49:37 donn 19 18
c Add include files to get prototype declarations, and fix bugs found.
e
s 00000/00013/00398
d D 5.16 91/02/21 13:34:29 bostic 18 17
c move dkcksum() to sbin/disklabel/dkcksum.c
e
s 00001/00001/00410
d D 5.15 90/11/28 17:02:44 bostic 17 16
c EBADFORMAT -> EFTYPE
e
s 00020/00003/00391
d D 5.14 90/11/28 00:13:13 bostic 16 15
c make error messages a little better, use constants in unistd.h
e
s 00001/00011/00393
d D 5.13 90/06/01 14:09:46 bostic 15 14
c new copyright notice
e
s 00001/00001/00403
d D 5.12 90/05/15 19:45:19 bostic 14 13
c string.h is ANSI C include file
e
s 00001/00001/00403
d D 5.11 89/07/30 09:02:07 bostic 13 12
c vnodes
e
s 00015/00004/00389
d D 5.10 88/07/19 14:31:42 bostic 12 11
c add Berkeley specific copyright
e
s 00018/00006/00375
d D 5.9 88/01/27 03:02:46 marc 11 10
c add b0 and b1 capabilities: primary and secondary boot files
e
s 00001/00018/00380
d D 5.8 88/01/03 19:38:11 mckusick 10 9
c use strcasecmp in place of ustrcmp (4.3BSD/lib/101 torek)
e
s 00002/00002/00396
d D 5.7 87/03/28 11:22:18 bostic 9 8
c linted
e
s 00000/00029/00398
d D 5.6 87/02/02 22:26:48 karels 8 7
c toss byte swapping
e
s 00151/00025/00276
d D 5.5 87/01/19 15:27:19 karels 7 6
c convert to disklabels
e
s 00002/00002/00299
d D 5.4 86/10/15 21:16:47 sam 6 5
c check for 0 sector size and/or rpm's
e
s 00002/00002/00299
d D 5.3 86/03/09 21:12:03 donn 5 4
c added LIBC_SCCS condition for sccs ids
e
s 00002/00000/00299
d D 5.2 85/10/02 00:20:57 mckusick 4 3
c add :sf: (bad144 sector forwarding) and 
c :so: (sector rather than cylinder offsets)
e
s 00009/00001/00290
d D 5.1 85/05/30 15:06:27 dist 3 2
c Add copyright
e
s 00011/00004/00280
d D 4.2 83/02/08 12:50:01 sam 2 1
c add partition tables (don't belong here, but for now...)
e
s 00284/00000/00000
d D 4.1 83/02/06 16:34:13 sam 1 0
c date and time created 83/02/06 16:34:13 by sam
e
u
U
t
T
I 1
D 3
/*	%W% (Berkeley) %G%	*/
E 3
I 3
/*
D 7
 * Copyright (c) 1983 Regents of the University of California.
E 7
I 7
D 12
 * Copyright (c) 1983,1987 Regents of the University of California.
E 7
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 12
I 12
D 26
 * Copyright (c) 1983, 1987 Regents of the University of California.
 * All rights reserved.
E 26
I 26
 * Copyright (c) 1983, 1987, 1993
 *	The Regents of the University of California.  All rights reserved.
E 26
 *
D 15
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
E 15
I 15
D 22
 * %sccs.include.redist.c%
E 22
I 22
D 23
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
E 23
I 23
 * %sccs.include.redist.c%
E 23
E 22
E 15
E 12
 */

D 5
#ifndef lint
E 5
I 5
D 23
#if defined(LIBC_SCCS) && !defined(lint)
E 5
D 22
static char sccsid[] = "%W% (Berkeley) %G%";
E 22
I 22
static char sccsid[] = "@(#)disklabel.c	5.19 (Berkeley) 3/19/92";
E 22
D 5
#endif not lint
E 5
I 5
D 12
#endif LIBC_SCCS and not lint
E 12
I 12
#endif /* LIBC_SCCS and not lint */
E 23
I 23
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 23
E 12
E 5
E 3

D 7
#include <disktab.h>
E 7
I 7
#include <sys/param.h>
I 16
D 25
#include <sys/errno.h>
E 16
D 13
#include <sys/fs.h>
E 13
I 13
D 20
#include <ufs/fs.h>
E 20
E 13
#include <sys/file.h>
E 25
#define DKTYPENAMES
#include <sys/disklabel.h>
I 27
#include <ufs/ufs/dinode.h>
E 27
I 20
#include <ufs/ffs/fs.h>
I 25

#include <errno.h>
#include <fcntl.h>
E 25
E 20
E 7
#include <stdio.h>
I 9
D 14
#include <strings.h>
E 14
I 14
D 25
#include <string.h>
E 25
I 19
#include <stdlib.h>
I 25
#include <string.h>
E 25
#include <unistd.h>
E 19
E 14
E 9

D 22
static	char *dgetstr();
I 19
static	dgetent();
static	dnamatch();
static	dgetnum();
static	dgetflag();
static	gettype();
static	error();
E 22
I 22
static int	error __P((int));
static int	gettype __P((char *, char **));
E 22
E 19

D 7
struct disktab *
E 7
I 7
struct disklabel *
E 7
getdiskbyname(name)
D 19
	char *name;
E 19
I 19
	const char *name;
E 19
{
D 7
	static struct disktab disk;
	static char localbuf[100], *cp = localbuf;
	register struct	disktab *dp = &disk;
E 7
I 7
D 11
	static struct disklabel disk;
	static char localbuf[100];
	char *cp, *cq;
E 11
I 11
	static struct	disklabel disk;
D 21
	static char 	boot[BUFSIZ];
E 21
I 21
D 22
	static char	boot[BUFSIZ];
E 21
	char	localbuf[BUFSIZ];
	char	buf[BUFSIZ];
	char	*cp, *cq;	/* can't be register */
E 22
E 11
	register struct	disklabel *dp = &disk;
E 7
D 2
	char p, part[3], buf[BUFSIZ];
E 2
I 2
	register struct partition *pp;
I 22
	char	*buf;
	char  	*db_array[2] = { _PATH_DISKTAB, 0 };
	char	*cp, *cq;	/* can't be register */
E 22
D 7
	char p, psize[3], pbsize[3], pfsize[3];
E 7
I 7
D 11
	char p, max, psize[3], pbsize[3], pfsize[3], poffset[3], ptype[3];
E 7
	char buf[BUFSIZ];
I 7
D 9
	int i;
E 9
	u_long *dx;
E 11
I 11
	char	p, max, psize[3], pbsize[3],
		pfsize[3], poffset[3], ptype[3];
D 27
	u_long	*dx;
E 27
I 27
	u_int32_t *dx;
E 27
E 11
E 7
E 2

D 22
	if (dgetent(buf, name) <= 0)
D 7
		return ((struct disktab *)0);
	dp->d_name = cp;
	strcpy(cp, name);
	cp += strlen(name) + 1;
	dp->d_type = dgetstr("ty", &cp);
	dp->d_secsize = dgetnum("se");
D 6
	if (dp->d_secsize < 0)
E 6
I 6
	if (dp->d_secsize <= 0)
E 6
		dp->d_secsize = 512;
E 7
I 7
		return ((struct disklabel *)0);
E 22
I 22
	if (cgetent(&buf, db_array, (char *) name) < 0)
		return NULL;

E 22
	bzero((char *)&disk, sizeof(disk));
I 11
	/*
	 * typename
	 */
E 11
	cq = dp->d_typename;
	cp = buf;
	while (cq < dp->d_typename + sizeof(dp->d_typename) - 1 &&
	    (*cq = *cp) && *cq != '|' && *cq != ':')
		cq++, cp++;
	*cq = '\0';
I 11
	/*
	 * boot name (optional)  xxboot, bootxx
	 */
D 22
	cp = boot;
	dp->d_boot0 = dgetstr("b0", &cp);
	dp->d_boot1 = dgetstr("b1", &cp);
E 11
	cp = localbuf;
	cq = dgetstr("ty", &cp);
	if (cq && strcmp(cq, "removable") == 0)
E 22
I 22
	cgetstr(buf, "b0", &dp->d_boot0);
	cgetstr(buf, "b1", &dp->d_boot1);

	if (cgetstr(buf, "ty", &cq) > 0 && strcmp(cq, "removable") == 0)
E 22
		dp->d_flags |= D_REMOVABLE;
	else  if (cq && strcmp(cq, "simulated") == 0)
		dp->d_flags |= D_RAMDISK;
D 22
	if (dgetflag("sf"))
E 22
I 22
	if (cgetcap(buf, "sf", ':') != NULL)
E 22
		dp->d_flags |= D_BADSECT;
I 11

E 11
#define getnumdflt(field, dname, dflt) \
D 22
	{ int f = dgetnum(dname); \
	(field) = f == -1 ? (dflt) : f; }
E 22
I 22
        { long f; (field) = (cgetnum(buf, dname, &f) == -1) ? (dflt) : f; }
E 22

	getnumdflt(dp->d_secsize, "se", DEV_BSIZE);
E 7
D 22
	dp->d_ntracks = dgetnum("nt");
	dp->d_nsectors = dgetnum("ns");
	dp->d_ncylinders = dgetnum("nc");
D 7
	dp->d_rpm = dgetnum("rm");
D 6
	if (dp->d_rpm < 0)
E 6
I 6
	if (dp->d_rpm <= 0)
E 6
		dp->d_rpm = 3600;
I 4
	dp->d_badsectforw = dgetflag("sf");
	dp->d_sectoffset = dgetflag("so");
E 7
I 7
	cq = dgetstr("dt", &cp);
	if (cq)
E 22
I 22
	cgetnum(buf, "nt",(long *) &dp->d_ntracks);
	cgetnum(buf, "ns",(long *) &dp->d_nsectors);
	cgetnum(buf, "nc",(long *) &dp->d_ncylinders);

	if (cgetstr(buf, "dt", &cq) > 0)
E 22
		dp->d_type = gettype(cq, dktypenames);
	else
		getnumdflt(dp->d_type, "dt", 0);
	getnumdflt(dp->d_secpercyl, "sc", dp->d_nsectors * dp->d_ntracks);
	getnumdflt(dp->d_secperunit, "su", dp->d_secpercyl * dp->d_ncylinders);
	getnumdflt(dp->d_rpm, "rm", 3600);
	getnumdflt(dp->d_interleave, "il", 1);
	getnumdflt(dp->d_trackskew, "sk", 0);
	getnumdflt(dp->d_cylskew, "cs", 0);
	getnumdflt(dp->d_headswitch, "hs", 0);
	getnumdflt(dp->d_trkseek, "ts", 0);
	getnumdflt(dp->d_bbsize, "bs", BBSIZE);
	getnumdflt(dp->d_sbsize, "sb", SBSIZE);
E 7
E 4
D 2
	strcpy(part, "px");
E 2
I 2
	strcpy(psize, "px");
	strcpy(pbsize, "bx");
	strcpy(pfsize, "fx");
E 2
D 7
	for (p = 'a'; p < 'i'; p++) {
D 2
		part[1] = p;
		dp->d_partitions[p - 'a'] = dgetnum(part);
E 2
I 2
		psize[1] = pbsize[1] = pfsize[1] = p;
		pp = &dp->d_partitions[p - 'a'];
E 7
I 7
	strcpy(poffset, "ox");
	strcpy(ptype, "tx");
	max = 'a' - 1;
	pp = &dp->d_partitions[0];
	for (p = 'a'; p < 'a' + MAXPARTITIONS; p++, pp++) {
		psize[1] = pbsize[1] = pfsize[1] = poffset[1] = ptype[1] = p;
E 7
D 22
		pp->p_size = dgetnum(psize);
D 7
		pp->p_bsize = dgetnum(pbsize);
		pp->p_fsize = dgetnum(pfsize);
E 7
I 7
		if (pp->p_size == -1)
E 22
I 22
		if (cgetnum(buf, psize,(long *) &pp->p_size) == -1)
E 22
			pp->p_size = 0;
		else {
D 22
			pp->p_offset = dgetnum(poffset);
E 22
I 22
			cgetnum(buf, poffset, (long *) &pp->p_offset);
E 22
			getnumdflt(pp->p_fsize, pfsize, 0);
D 22
			if (pp->p_fsize)
				pp->p_frag = dgetnum(pbsize) / pp->p_fsize;
E 22
I 22
			if (pp->p_fsize) {
D 24
			        cgetnum(buf, pbsize, (long *) &pp->p_frag);
				pp->p_frag /= pp->p_fsize;
E 24
I 24
				long bsize;

				if (cgetnum(buf, pbsize, &bsize) == 0)
					pp->p_frag = bsize / pp->p_fsize;
				else
					pp->p_frag = 8;
E 24
			}
E 22
			getnumdflt(pp->p_fstype, ptype, 0);
D 22
			if (pp->p_fstype == 0 && (cq = dgetstr(ptype, &cp)))
E 22
I 22
			if (pp->p_fstype == 0 && cgetstr(buf, ptype, &cq) > 0)
E 22
				pp->p_fstype = gettype(cq, fstypenames);
			max = p;
		}
E 7
E 2
	}
I 7
	dp->d_npartitions = max + 1 - 'a';
D 9
	strcpy(psize, "dx");
E 9
I 9
	(void)strcpy(psize, "dx");
E 9
	dx = dp->d_drivedata;
	for (p = '0'; p < '0' + NDDATA; p++, dx++) {
		psize[1] = p;
		getnumdflt(*dx, psize, 0);
	}
	dp->d_magic = DISKMAGIC;
	dp->d_magic2 = DISKMAGIC;
I 22
	free(buf);
E 22
E 7
	return (dp);
}

D 22
#include <ctype.h>

static	char *tbuf;
static	char *dskip();
static	char *ddecode();

/*
 * Get an entry for disk name in buffer bp,
 * from the diskcap file.  Parse is very rudimentary;
 * we just notice escaped newlines.
 */
static
dgetent(bp, name)
	char *bp, *name;
{
	register char *cp;
	register int c;
	register int i = 0, cnt = 0;
	char ibuf[BUFSIZ];
	int tf;

	tbuf = bp;
D 16
	tf = open(DISKTAB, 0);
	if (tf < 0)
E 16
I 16
	tf = open(_PATH_DISKTAB, 0);
	if (tf < 0) {
		error(errno);
E 16
		return (-1);
I 16
	}
E 16
	for (;;) {
		cp = bp;
		for (;;) {
			if (i == cnt) {
				cnt = read(tf, ibuf, BUFSIZ);
				if (cnt <= 0) {
I 16
D 21
					error(errno);
E 21
I 21
					if (cnt < 0)
						error(errno);
E 21
E 16
					close(tf);
					return (0);
				}
				i = 0;
			}
			c = ibuf[i++];
			if (c == '\n') {
				if (cp > bp && cp[-1] == '\\'){
					cp--;
					continue;
				}
				break;
			}
			if (cp >= bp+BUFSIZ) {
D 16
				write(2,"Disktab entry too long\n", 23);
E 16
I 16
D 17
				error(EBADFORMAT);
E 17
I 17
				error(EFTYPE);
E 17
E 16
				break;
			} else
				*cp++ = c;
		}
		*cp = 0;

		/*
		 * The real work for the match.
		 */
		if (dnamatch(name)) {
			close(tf);
			return (1);
		}
	}
}

/*
 * Dnamatch deals with name matching.  The first field of the disktab
 * entry is a sequence of names separated by |'s, so we compare
 * against each such name.  The normal : terminator after the last
 * name (before the first field) stops us.
 */
static
dnamatch(np)
	char *np;
{
	register char *Np, *Bp;

	Bp = tbuf;
	if (*Bp == '#')
		return (0);
	for (;;) {
		for (Np = np; *Np && *Bp == *Np; Bp++, Np++)
			continue;
		if (*Np == 0 && (*Bp == '|' || *Bp == ':' || *Bp == 0))
			return (1);
		while (*Bp && *Bp != ':' && *Bp != '|')
			Bp++;
		if (*Bp == 0 || *Bp == ':')
			return (0);
		Bp++;
	}
}

/*
 * Skip to the next field.  Notice that this is very dumb, not
 * knowing about \: escapes or any such.  If necessary, :'s can be put
 * into the diskcap file in octal.
 */
static char *
dskip(bp)
	register char *bp;
{

	while (*bp && *bp != ':')
		bp++;
	if (*bp == ':')
		bp++;
	return (bp);
}

/*
 * Return the (numeric) option id.
 * Numeric options look like
 *	li#80
 * i.e. the option string is separated from the numeric value by
 * a # character.  If the option is not found we return -1.
 * Note that we handle octal numbers beginning with 0.
 */
static
dgetnum(id)
	char *id;
{
	register int i, base;
	register char *bp = tbuf;

	for (;;) {
		bp = dskip(bp);
		if (*bp == 0)
			return (-1);
		if (*bp++ != id[0] || *bp == 0 || *bp++ != id[1])
			continue;
		if (*bp == '@')
			return (-1);
		if (*bp != '#')
			continue;
		bp++;
		base = 10;
		if (*bp == '0')
			base = 8;
		i = 0;
		while (isdigit(*bp))
			i *= base, i += *bp++ - '0';
		return (i);
	}
}

/*
 * Handle a flag option.
 * Flag options are given "naked", i.e. followed by a : or the end
 * of the buffer.  Return 1 if we find the option, or 0 if it is
 * not given.
 */
static
dgetflag(id)
	char *id;
{
	register char *bp = tbuf;

	for (;;) {
		bp = dskip(bp);
		if (!*bp)
			return (0);
		if (*bp++ == id[0] && *bp != 0 && *bp++ == id[1]) {
			if (!*bp || *bp == ':')
				return (1);
			else if (*bp == '@')
				return (0);
		}
	}
}

/*
 * Get a string valued option.
 * These are given as
 *	cl=^Z
 * Much decoding is done on the strings, and the strings are
 * placed in area, which is a ref parameter which is updated.
 * No checking on area overflow.
 */
static char *
dgetstr(id, area)
	char *id, **area;
{
	register char *bp = tbuf;

	for (;;) {
		bp = dskip(bp);
		if (!*bp)
			return (0);
		if (*bp++ != id[0] || *bp == 0 || *bp++ != id[1])
			continue;
		if (*bp == '@')
			return (0);
		if (*bp != '=')
			continue;
		bp++;
		return (ddecode(bp, area));
	}
}

/*
 * Tdecode does the grung work to decode the
 * string capability escapes.
 */
static char *
ddecode(str, area)
	register char *str;
	char **area;
{
	register char *cp;
	register int c;
	register char *dp;
	int i;

	cp = *area;
	while ((c = *str++) && c != ':') {
		switch (c) {

		case '^':
			c = *str++ & 037;
			break;

		case '\\':
			dp = "E\033^^\\\\::n\nr\rt\tb\bf\f";
			c = *str++;
nextc:
			if (*dp++ == c) {
				c = *dp++;
				break;
			}
			dp++;
			if (*dp)
				goto nextc;
			if (isdigit(c)) {
				c -= '0', i = 2;
				do
					c <<= 3, c |= *str++ - '0';
				while (--i && isdigit(*str));
			}
			break;
		}
		*cp++ = c;
	}
	*cp++ = 0;
	str = *area;
	*area = cp;
	return (str);
I 7
}

static
E 22
I 22
static int
E 22
gettype(t, names)
	char *t;
	char **names;
{
	register char **nm;

	for (nm = names; *nm; nm++)
D 10
		if (ustrcmp(t, *nm) == 0)
E 10
I 10
		if (strcasecmp(t, *nm) == 0)
E 10
			return (nm - names);
	if (isdigit(*t))
		return (atoi(t));
D 10
	return (0);
}

static
ustrcmp(s1, s2)
	register char *s1, *s2;
{
#define	lower(c)	(islower(c) ? (c) : tolower(c))

	for (; *s1; s1++, s2++) {
		if (*s1 == *s2)
			continue;
		if (isalpha(*s1) && isalpha(*s2) &&
		    lower(*s1) == lower(*s2))
			continue;
		return (*s2 - *s1);
	}
E 10
	return (0);
}

D 8
/*
 * Swab disk label if needed.
 */
#if ENDIAN != BIG
/* ARGSUSED */
#endif
swablabel(lp)
	register struct disklabel *lp;
{
#if ENDIAN != BIG
	register u_long *p;
	register struct partition *pp;
	int npart;

	lp->d_magic = ntohl(lp->d_magic);
	lp->d_type = ntohs(lp->d_type);
	lp->d_subtype = ntohs(lp->d_subtype);
	for (p = &lp->d_swabfirst; p <= &lp->d_swablast; p++)
		*p = ntohl(*p);
	npart = lp->d_npartitions;
	for (pp = lp->d_partitions; pp < &lp->d_partitions[npart]; pp++) {
		pp->p_size = ntohl(pp->p_size);
		pp->p_offset = ntohl(pp->p_offset);
		pp->p_fsize = ntohl(pp->p_fsize);
		pp->p_cpg = ntohs(pp->p_cpg);
	}
#endif
}

E 8
D 18
dkcksum(lp)
	register struct disklabel *lp;
{
	register u_short *start, *end;
	register u_short sum = 0;

	start = (u_short *)lp;
	end = (u_short *)&lp->d_partitions[lp->d_npartitions];
	while (start < end)
		sum ^= *start++;
	return (sum);
I 16
}

E 18
D 22
static
E 22
I 22
static int
E 22
error(err)
	int err;
{
	char *p;

	(void)write(STDERR_FILENO, "disktab: ", 9);
	(void)write(STDERR_FILENO, _PATH_DISKTAB, sizeof(_PATH_DISKTAB) - 1);
I 21
	(void)write(STDERR_FILENO, ": ", 2);
E 21
	p = strerror(err);
	(void)write(STDERR_FILENO, p, strlen(p));
	(void)write(STDERR_FILENO, "\n", 1);
E 16
E 7
}
E 1
