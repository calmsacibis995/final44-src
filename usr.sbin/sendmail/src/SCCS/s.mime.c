h50091
s 00003/00001/00821
d D 8.26 95/06/18 11:53:16 eric 27 26
c add class `m' to include message subtypes that can be treated
c as though rfc822
e
s 00002/00000/00820
d D 8.25 95/06/17 10:36:17 eric 26 25
c message/rfc822 MIME fixes
e
s 00001/00002/00819
d D 8.24 95/05/28 11:50:25 eric 25 24
c lint
e
s 00009/00008/00812
d D 8.23 95/05/22 08:29:28 eric 24 23
c fixes from JGM
e
s 00003/00000/00817
d D 8.22 95/05/15 19:00:40 eric 23 22
c put MIME 8->7 bit conversions on a compile flag (default on for now)
e
s 00018/00013/00799
d D 8.21 95/05/15 09:15:47 eric 22 21
c MIME glitches
e
s 00004/00000/00808
d D 8.20 95/05/05 08:21:10 eric 21 19
c fix MIME problem: did header munging on interior headers
e
s 00570/00008/00800
d D 8.19.1.1 95/04/29 16:35:59 eric 20 19
c bogus attempt to do 7->8 bit conversion
e
s 00102/00075/00706
d D 8.19 95/04/24 20:30:34 eric 19 18
c more bug fixes from JGM
e
s 00007/00007/00774
d D 8.18 95/04/23 08:50:16 eric 18 17
c better solution to MIME sign extension problem
e
s 00014/00001/00767
d D 8.17 95/04/23 07:59:55 eric 17 16
c add F=3 flag to extend Q-P encoding to non-EBCDIC characters
e
s 00010/00005/00758
d D 8.16 95/04/23 07:18:59 eric 16 15
c don't do NL=>CRLF mapping on C-T-E: binary files; always encode
c binaries as Base64 (because Q-P munges newlines)
e
s 00104/00021/00659
d D 8.15 95/04/22 10:53:01 eric 15 14
c fixes to MIME code
e
s 00093/00038/00587
d D 8.14 95/04/03 09:31:25 eric 14 13
c clean up problems with MIME 8 to 7 bit conversions
e
s 00006/00005/00619
d D 8.13 95/04/02 09:28:46 eric 13 12
c MIME cleanup to get header line parsing right
e
s 00002/00002/00622
d D 8.12 95/03/21 15:28:42 eric 12 11
c eliminate `D' line in qf file
e
s 00136/00035/00488
d D 8.11 95/03/11 18:02:29 eric 11 10
c more MIME cleanup
e
s 00086/00051/00437
d D 8.10 95/03/11 13:42:51 eric 10 9
c fix several MIME boundary-condition problems
e
s 00001/00001/00487
d D 8.9 94/11/19 16:57:53 eric 9 8
c remove Content-Type: header from returned messages if and only if
c no body is to be returned -- this could confuse mail readers
e
s 00027/00000/00461
d D 8.8 94/11/08 11:49:08 eric 8 7
c allow per-mailer default character set (applies to INCOMING mailer)
e
s 00019/00002/00442
d D 8.7 94/10/23 14:18:00 eric 7 6
c output trailing white space on lines as (e.g., =20) instead of
c using an escaped newline -- people seem to like that better
e
s 00006/00006/00438
d D 8.6 94/09/08 09:32:30 eric 6 5
c fix problem that could cause bogus unhidden "." if long lines
c were folded on quoted-printable encoding
e
s 00006/00000/00438
d D 8.5 94/08/17 08:18:33 eric 5 4
c output original Content-Transfer-Encoding header if we aren't
c going to do our own encoding
e
s 00000/00001/00438
d D 8.4 94/08/15 10:15:52 eric 4 3
c move hvalue extern declaration into sendmail.h
e
s 00026/00019/00413
d D 8.3 94/07/23 11:16:24 eric 3 2
c move hidden dot algorithm; allow no encoding at all
e
s 00025/00004/00407
d D 8.2 94/07/23 10:12:39 eric 2 1
c tweaks & bug fixes to MIME algorithm
e
s 00411/00000/00000
d D 8.1 94/07/23 07:53:46 eric 1 0
c date and time created 94/07/23 07:53:46 by eric
e
u
U
t
T
I 1
/*
 * Copyright (c) 1994 Eric P. Allman
 * Copyright (c) 1994
 *	The Regents of the University of California.  All rights reserved.
 *
 * %sccs.include.redist.c%
 */

# include "sendmail.h"
# include <string.h>

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

/*
**  MIME support.
**
**	I am indebted to John Beck of Hewlett-Packard, who contributed
**	his code to me for inclusion.  As it turns out, I did not use
**	his code since he used a "minimum change" approach that used
**	several temp files, and I wanted a "minimum impact" approach
**	that would avoid copying.  However, looking over his code
**	helped me cement my understanding of the problem.
**
**	I also looked at, but did not directly use, Nathaniel
**	Borenstein's "code.c" module.  Again, it functioned as
**	a file-to-file translator, which did not fit within my
**	design bounds, but it was a useful base for understanding
**	the problem.
I 20
**
**	Also, I looked at John G. Meyer's "part.[ch]" code.  Some
**	ideas have been loosely borrowed.
E 20
*/

I 23
#if MIME8TO7
E 23

/* character set for hex and base64 encoding */
char	Base16Code[] =	"0123456789ABCDEF";
char	Base64Code[] =	"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

/* types of MIME boundaries */
#define MBT_SYNTAX	0	/* syntax error */
#define MBT_NOTSEP	1	/* not a boundary */
#define MBT_INTERMED	2	/* intermediate boundary (no trailing --) */
#define MBT_FINAL	3	/* final boundary (trailing -- included) */
I 2

D 14
static int	MimeBoundaryType;	/* internal linkage */
E 14
I 14
static char	*MimeBoundaryNames[] =
{
	"SYNTAX",	"NOTSEP",	"INTERMED",	"FINAL"
};
I 20

/*
**  Pseudo-file structure for reading up to MIME boundaries.
*/

#define MFILE	struct _mfile

MFILE
{
	FILE	*mf_fp;		/* underlying file */
	u_char	*mf_buf;	/* a cache buffer */
	u_char	*mf_bp;		/* current pointer into mf_buf */
	int	mf_cnt;		/* number of characters left in mf_buf */
	int	mf_bsize;	/* size of mf_buf */
	int	(*mf_fill)();	/* buffer fill routine */
	char	mf_boundaries[MAXMIMENESTING + 1];
				/* current boundaries */
};

#define mime_getc(mf)	((mf)->mf_cnt-- > 0 : *(mf)->mf_ptr++ : mf->mf_fill(mf))
E 20
E 14
E 2
/*
**  MIME8TO7 -- output 8 bit body in 7 bit format
**
**	The header has already been output -- this has to do the
**	8 to 7 bit conversion.  It would be easy if we didn't have
**	to deal with nested formats (multipart/xxx and message/rfc822).
**
**	We won't be called if we don't have to do a conversion, and
**	appropriate MIME-Version: and Content-Type: fields have been
**	output.  Any Content-Transfer-Encoding: field has not been
**	output, and we can add it here.
**
**	Parameters:
**		mci -- mailer connection information.
**		header -- the header for this body part.
**		e -- envelope.
D 11
**		boundary -- the message boundary -- NULL if we are
**			processing the outer portion.
E 11
I 11
D 20
**		boundaries -- the currently pending message boundaries.
**			NULL if we are processing the outer portion.
E 20
**		flags -- to tweak processing.
E 11
**
**	Returns:
I 20
**		none.
*/

int
mime8to7(mci, header, e, flags)
	register MCI *mci;
	HDR *header;
	register ENVELOPE *e;
	int flags;
{
	MFILE mfile;

	mfile.mf_fp = e->e_dfp;
	mfile.mf_cnt = mfile.mf_size = 0;

	(void) mime8to7x(mci, header, e, &mfile, flags);
	if (mfile.mf_buf != NULL)
		free(mfile.mf_buf);
}
/*
**  MIME8TO7X -- internal interface for mime8to7.
**
**	Parameters:
**		mci -- mailer connection information.
**		header -- the header for this body part.
**		e -- envelope.
**		mf -- the file from which to read.
**		flags -- to tweak processing.
**
**	Returns:
E 20
**		An indicator of what terminated the message part:
**		  MBT_FINAL -- the final boundary
**		  MBT_INTERMED -- an intermediate boundary
**		  MBT_NOTSEP -- an end of file
*/

I 11
struct args
{
	char	*field;		/* name of field */
	char	*value;		/* value of that field */
};

E 11
int
D 11
mime8to7(mci, header, e, boundary)
E 11
I 11
D 20
mime8to7(mci, header, e, boundaries, flags)
E 20
I 20
mime8to7x(mci, header, e, boundaries, flags)
E 20
E 11
	register MCI *mci;
D 10
	HDR *header;
	register ENVELOPE *e;
E 10
I 10
D 14
	HDR *header; register ENVELOPE *e;
E 14
I 14
	HDR *header;
	register ENVELOPE *e;
E 14
E 10
D 11
	char *boundary;
E 11
I 11
	char **boundaries;
	int flags;
E 11
{
	register char *p;
	int linelen;
	int bt;
	off_t offset;
	size_t sectionsize, sectionhighbits;
I 11
	int i;
	char *type;
	char *subtype;
I 15
	char *cte;
E 15
	char **pvp;
	int argc = 0;
I 19
	char *bp;
E 19
	struct args argv[MAXMIMEARGS];
E 11
	char bbuf[128];
	char buf[MAXLINE];
I 11
	char pvpbuf[MAXLINE];
I 13
D 25
	extern char MimeTokenTab[256];
E 25
I 25
	extern u_char MimeTokenTab[256];
E 25
E 13
E 11
D 4
	extern char *hvalue();
E 4

	if (tTd(43, 1))
	{
D 14
		printf("mime8to7: boundary=%s\n",
D 11
			boundary == NULL ? "<none>" : boundary);
E 11
I 11
			boundaries[0] == NULL ? "<none>" : boundaries[0]);
		for (i = 1; boundaries[i] != NULL; i++)
D 13
			printf("\tboundaries[i]\n");
E 13
I 13
			printf("\t%s\n", boundaries[i]);
E 14
I 14
		printf("mime8to7: flags = %x, boundaries =", flags);
		if (boundaries[0] == NULL)
			printf(" <none>");
		else
		{
			for (i = 0; boundaries[i] != NULL; i++)
				printf(" %s", boundaries[i]);
		}
		printf("\n");
E 14
E 13
E 11
	}
I 19
	p = hvalue("Content-Transfer-Encoding", header);
	if (p == NULL ||
	    (pvp = prescan(p, '\0', pvpbuf, sizeof pvpbuf, NULL,
			   MimeTokenTab)) == NULL ||
	    pvp[0] == NULL)
	{
		cte = NULL;
	}
	else
	{
		cataddr(pvp, NULL, buf, sizeof buf, '\0');
		cte = newstr(buf);
	}

E 19
I 11
D 15
	type = subtype = "-none-";
E 15
I 15
	type = subtype = NULL;
E 15
E 11
	p = hvalue("Content-Type", header);
I 15
	if (p == NULL)
	{
		if (bitset(M87F_DIGEST, flags))
			p = "message/rfc822";
		else
			p = "text/plain";
	}
E 15
D 11
	if (p != NULL && strncasecmp(p, "multipart/", 10) == 0)
E 11
I 11
	if (p != NULL &&
D 13
	    (pvp = prescan(p, '\0', pvpbuf, sizeof pvpbuf, NULL)) != NULL &&
E 13
I 13
	    (pvp = prescan(p, '\0', pvpbuf, sizeof pvpbuf, NULL,
			   MimeTokenTab)) != NULL &&
E 13
	    pvp[0] != NULL)
E 11
	{
I 14
		if (tTd(43, 40))
		{
			for (i = 0; pvp[i] != NULL; i++)
				printf("pvp[%d] = \"%s\"\n", i, pvp[i]);
		}
E 14
I 11
		type = *pvp++;
		if (*pvp != NULL && strcmp(*pvp, "/") == 0 &&
		    *++pvp != NULL)
		{
			subtype = *pvp++;
		}

		/* break out parameters */
		while (*pvp != NULL && argc < MAXMIMEARGS)
		{
			/* skip to semicolon separator */
			while (*pvp != NULL && strcmp(*pvp, ";") != 0)
				pvp++;
			if (*pvp++ == NULL || *pvp == NULL)
				break;

			/* extract field name */
			argv[argc].field = *pvp++;

			/* see if there is a value */
			if (*pvp != NULL && strcmp(*pvp, "=") == 0 &&
			    (*++pvp == NULL || strcmp(*pvp, ";") != 0))
			{
				argv[argc].value = *pvp;
				argc++;
			}
		}
	}
I 14

D 15
	/* handle types that cannot have 8-bit data internally */
E 15
I 15
	/* check for disaster cases */
	if (type == NULL)
		type = "-none-";
	if (subtype == NULL)
		subtype = "-none-";

I 19
	/* don't propogate some flags more than one level into the message */
	flags &= ~M87F_DIGEST;

E 19
	/*
	**  Check for cases that can not be encoded.
	**
	**	For example, you can't encode certain kinds of types
	**	or already-encoded messages.  If we find this case,
	**	just copy it through.
	*/

D 19
	cte = hvalue("content-transfer-encoding", header);
E 19
E 15
	sprintf(buf, "%s/%s", type, subtype);
D 15
	if (wordinclass(buf, 'n'))
E 15
I 15
	if (wordinclass(buf, 'n') || (cte != NULL && !wordinclass(cte, 'e')))
E 15
		flags |= M87F_NO8BIT;

	/*
	**  Multipart requires special processing.
	**
	**	Do a recursive descent into the message.
	*/

E 14
D 19
	if (strcasecmp(type, "multipart") == 0)
E 19
I 19
	if (strcasecmp(type, "multipart") == 0 && !bitset(M87F_NO8BIT, flags))
E 19
	{
E 11
D 19
		register char *q;
E 19
I 19
		int blen;
E 19

I 15
		if (strcasecmp(subtype, "digest") == 0)
			flags |= M87F_DIGEST;

E 15
D 11
		/* oh dear -- this part is hard */
		p = strstr(p, "boundary=");		/*XXX*/
		if (p == NULL)
E 11
I 11
		for (i = 0; i < argc; i++)
E 11
		{
I 11
			if (strcasecmp(argv[i].field, "boundary") == 0)
				break;
		}
		if (i >= argc)
		{
E 11
			syserr("mime8to7: Content-Type: %s missing boundary", p);
			p = "---";
		}
		else
I 19
		{
E 19
D 11
			p += 9;
E 11
I 11
			p = argv[i].value;
E 11
D 19
		if (*p == '"')
D 13
			q = strchr(p, '"');
E 13
I 13
			q = strchr(++p, '"');
E 13
		else
D 11
			q = strchr(p, ',');
		if (q == NULL)
E 11
			q = p + strlen(p);
		if (q - p > sizeof bbuf - 1)
E 19
I 19
			stripquotes(p);
		}
		blen = strlen(p);
		if (blen > sizeof bbuf - 1)
E 19
		{
D 19
			syserr("mime8to7: multipart boundary \"%.*s\" too long",
				q - p, p);
			q = p + sizeof bbuf - 1;
E 19
I 19
			syserr("mime8to7: multipart boundary \"%s\" too long",
				p);
			blen = sizeof bbuf - 1;
E 19
		}
D 19
		strncpy(bbuf, p, q - p);
		bbuf[q - p] = '\0';
E 19
I 19
		strncpy(bbuf, p, blen);
		bbuf[blen] = '\0';
E 19
		if (tTd(43, 1))
D 14
		{
E 14
			printf("mime8to7: multipart boundary \"%s\"\n", bbuf);
D 14
		}
E 14
I 11
		for (i = 0; i < MAXMIMENESTING; i++)
			if (boundaries[i] == NULL)
				break;
		if (i >= MAXMIMENESTING)
			syserr("mime8to7: multipart nesting boundary too deep");
		else
		{
			boundaries[i] = bbuf;
			boundaries[i + 1] = NULL;
		}
I 21
		mci->mci_flags |= MCIF_INMIME;
E 21
E 11

I 11
D 14
		/* flag subtypes that can't have any 8-bit data */
		if (strcasecmp(subtype, "signed") == 0)
			flags |= M87F_NO8BIT;

E 14
E 11
		/* skip the early "comment" prologue */
D 14
		bt = MBT_FINAL;
E 14
I 14
		putline("", mci);
E 14
		while (fgets(buf, sizeof buf, e->e_dfp) != NULL)
		{
D 11
			bt = mimeboundary(buf, bbuf);
E 11
I 11
			bt = mimeboundary(buf, boundaries);
E 11
			if (bt != MBT_NOTSEP)
				break;
D 15
			putline(buf, mci);
E 15
I 15
			putxline(buf, mci, PXLF_MAPFROM|PXLF_STRIP8BIT);
E 15
I 14
			if (tTd(43, 99))
				printf("  ...%s", buf);
E 14
		}
I 14
		if (feof(e->e_dfp))
			bt = MBT_FINAL;
E 14
		while (bt != MBT_FINAL)
		{
			auto HDR *hdr = NULL;

			sprintf(buf, "--%s", bbuf);
			putline(buf, mci);
I 14
			if (tTd(43, 35))
				printf("  ...%s\n", buf);
E 14
			collect(e->e_dfp, FALSE, FALSE, &hdr, e);
I 14
			if (tTd(43, 101))
				putline("+++after collect", mci);
E 14
D 9
			putheader(mci, hdr, e);
E 9
I 9
D 19
			putheader(mci, hdr, e, 0);
E 19
I 19
			putheader(mci, hdr, e);
E 19
I 14
			if (tTd(43, 101))
				putline("+++after putheader", mci);
E 14
E 9
D 11
			bt = mime8to7(mci, hdr, e, bbuf);
E 11
I 11
D 20
			bt = mime8to7(mci, hdr, e, boundaries, flags);
E 20
I 20
			bt = mime8to7x(mci, hdr, e, boundaries, flags);
E 20
E 11
		}
		sprintf(buf, "--%s--", bbuf);
		putline(buf, mci);
I 14
		if (tTd(43, 35))
			printf("  ...%s\n", buf);
		boundaries[i] = NULL;
I 21
		mci->mci_flags &= ~MCIF_INMIME;
E 21
E 14

		/* skip the late "comment" epilogue */
		while (fgets(buf, sizeof buf, e->e_dfp) != NULL)
		{
D 14
			putline(buf, mci);
E 14
D 11
			bt = mimeboundary(buf, boundary);
E 11
I 11
			bt = mimeboundary(buf, boundaries);
E 11
			if (bt != MBT_NOTSEP)
				break;
I 14
D 15
			putline(buf, mci);
E 15
I 15
			putxline(buf, mci, PXLF_MAPFROM|PXLF_STRIP8BIT);
E 15
			if (tTd(43, 99))
				printf("  ...%s", buf);
E 14
		}
I 11
D 14
		boundaries[i] = NULL;
E 14
I 14
		if (feof(e->e_dfp))
			bt = MBT_FINAL;
		if (tTd(43, 3))
			printf("\t\t\tmime8to7=>%s (multipart)\n",
				MimeBoundaryNames[bt]);
E 14
E 11
		return bt;
	}

	/*
I 15
	**  Message/* types -- recurse exactly once.
I 27
	**
	**	Class 'm' is predefined to have "rfc822" only.
E 27
	*/

	if (strcasecmp(type, "message") == 0)
	{
D 19
		register char *q;
		auto HDR *hdr = NULL;
E 19
I 19
D 27
		if (strcasecmp(subtype, "rfc822") != 0)
E 27
I 27
		if (!wordinclass(subtype, 'm'))
E 27
		{
			flags |= M87F_NO8BIT;
		}
		else
		{
D 25
			register char *q;
E 25
			auto HDR *hdr = NULL;
E 19

D 19
		putline("", mci);
E 19
I 19
			putline("", mci);
E 19

I 21
			mci->mci_flags |= MCIF_INMIME;
E 21
D 19
		collect(e->e_dfp, FALSE, FALSE, &hdr, e);
		if (tTd(43, 101))
			putline("+++after collect", mci);
		putheader(mci, hdr, e, 0);
		if (tTd(43, 101))
			putline("+++after putheader", mci);
		bt = mime8to7(mci, hdr, e, boundaries, flags);
		return bt;
E 19
I 19
			collect(e->e_dfp, FALSE, FALSE, &hdr, e);
			if (tTd(43, 101))
				putline("+++after collect", mci);
			putheader(mci, hdr, e);
			if (tTd(43, 101))
				putline("+++after putheader", mci);
I 26
			if (hvalue("MIME-Version", hdr) == NULL)
				putline("MIME-Version: 1.0", mci);
E 26
			bt = mime8to7(mci, hdr, e, boundaries, flags);
I 21
			mci->mci_flags &= ~MCIF_INMIME;
E 21
			return bt;
		}
E 19
	}

	/*
E 15
	**  Non-compound body type
	**
	**	Compute the ratio of seven to eight bit characters;
	**	use that as a heuristic to decide how to do the
	**	encoding.
	*/

I 11
D 14
	/* handle types that cannot have 8-bit data internally */
	sprintf(buf, "%s/%s", type, subtype);
	if (wordinclass(buf, 'n'))
		flags |= M87F_NO8BIT;

E 14
E 11
D 10
	/* remember where we were */
	offset = ftell(e->e_dfp);
	if (offset == -1)
		syserr("mime8to7: cannot ftell on %s", e->e_df);

	/* do a scan of this body type to count character types */
E 10
	sectionsize = sectionhighbits = 0;
D 10
	while (fgets(buf, sizeof buf, e->e_dfp) != NULL)
E 10
I 10
D 11
	if (p == NULL || strcasecmp(p, "message/rfc822") != 0)
E 11
I 11
	if (!bitset(M87F_NO8BIT, flags))
E 11
E 10
	{
D 10
		bt = mimeboundary(buf, boundary);
		if (bt != MBT_NOTSEP)
			break;
		for (p = buf; *p != '\0'; p++)
E 10
I 10
		/* remember where we were */
		offset = ftell(e->e_dfp);
		if (offset == -1)
D 12
			syserr("mime8to7: cannot ftell on %s", e->e_df);
E 12
I 12
			syserr("mime8to7: cannot ftell on df%s", e->e_id);
E 12

		/* do a scan of this body type to count character types */
		while (fgets(buf, sizeof buf, e->e_dfp) != NULL)
E 10
		{
I 2
D 10
			/* count bytes with the high bit set */
D 3
			/* XXX should this count any character that will */
			/* XXX have to be encoded in quoted-printable? */
E 3
E 2
			sectionsize++;
			if (bitset(0200, *p))
				sectionhighbits++;
		}
E 10
I 10
D 11
			bt = mimeboundary(buf, boundary);
E 11
I 11
D 14
			bt = mimeboundary(buf, boundaries);
E 11
			if (bt != MBT_NOTSEP)
E 14
I 14
			if (mimeboundary(buf, boundaries) != MBT_NOTSEP)
E 14
				break;
			for (p = buf; *p != '\0'; p++)
			{
				/* count bytes with the high bit set */
				sectionsize++;
				if (bitset(0200, *p))
					sectionhighbits++;
			}
E 10
I 2

D 10
		/*
		**  Heuristic: if 1/4 of the first 4K bytes are 8-bit,
		**  assume base64.  This heuristic avoids double-reading
		**  large graphics or video files.
		*/
E 10
I 10
			/*
			**  Heuristic: if 1/4 of the first 4K bytes are 8-bit,
			**  assume base64.  This heuristic avoids double-reading
			**  large graphics or video files.
			*/
E 10

D 10
		if (sectionsize >= 4096 && sectionhighbits > sectionsize / 4)
			break;
E 10
I 10
			if (sectionsize >= 4096 &&
			    sectionhighbits > sectionsize / 4)
				break;
		}
D 14
		if (feof(e->e_dfp))
			bt = MBT_FINAL;
E 14

		/* return to the original offset for processing */
		/* XXX use relative seeks to handle >31 bit file sizes? */
		if (fseek(e->e_dfp, offset, SEEK_SET) < 0)
D 12
			syserr("mime8to7: cannot fseek on %s", e->e_df);
E 12
I 12
			syserr("mime8to7: cannot fseek on df%s", e->e_id);
I 14
		else
			clearerr(e->e_dfp);
E 14
E 12
E 10
E 2
	}
D 10
	if (feof(e->e_dfp))
		bt = MBT_FINAL;
E 10

D 10
	/* return to the original offset for processing */
I 2
	/* XXX use relative seeks to handle >31 bit file sizes? */
E 2
	if (fseek(e->e_dfp, offset, SEEK_SET) < 0)
		syserr("mime8to7: cannot fseek on %s", e->e_df);

E 10
D 2
	/* heuristically determine encoding method */
E 2
I 2
	/*
	**  Heuristically determine encoding method.
	**	If more than 1/8 of the total characters have the
	**	eighth bit set, use base64; else use quoted-printable.
I 16
	**	However, only encode binary encoded data as base64,
	**	since otherwise the NL=>CRLF mapping will be a problem.
E 16
	*/

E 2
	if (tTd(43, 8))
	{
D 14
		printf("mime8to7: %ld high bits in %ld bytes\n",
E 14
I 14
D 16
		printf("mime8to7: %ld high bit(s) in %ld byte(s)\n",
E 14
			sectionhighbits, sectionsize);
E 16
I 16
		printf("mime8to7: %ld high bit(s) in %ld byte(s), cte=%s\n",
			sectionhighbits, sectionsize,
			cte == NULL ? "[none]" : cte);
E 16
	}
I 16
	if (cte != NULL && strcasecmp(cte, "binary") == 0)
		sectionsize = sectionhighbits;
E 16
I 14
	linelen = 0;
I 19
	bp = buf;
E 19
E 14
D 3
	if (sectionsize / 8 < sectionhighbits)
E 3
I 3
	if (sectionhighbits == 0)
E 3
	{
I 3
		/* no encoding necessary */
I 5
D 15
		p = hvalue("content-transfer-encoding", header);
		if (p != NULL)
E 15
I 15
		if (cte != NULL)
E 15
		{
D 15
			sprintf(buf, "Content-Transfer-Encoding: %s", p);
E 15
I 15
			sprintf(buf, "Content-Transfer-Encoding: %s", cte);
E 15
			putline(buf, mci);
I 14
			if (tTd(43, 36))
				printf("  ...%s\n", buf);
E 14
		}
E 5
		putline("", mci);
		mci->mci_flags &= ~MCIF_INHEADER;
		while (fgets(buf, sizeof buf, e->e_dfp) != NULL)
		{
D 11
			bt = mimeboundary(buf, boundary);
E 11
I 11
			bt = mimeboundary(buf, boundaries);
E 11
			if (bt != MBT_NOTSEP)
				break;
D 15
			if (buf[0] == 'F' &&
			    bitnset(M_ESCFROM, mci->mci_mailer->m_flags) &&
			    strncmp(buf, "From ", 5) == 0)
				(void) putc('>', mci->mci_out);
E 15
			putline(buf, mci);
		}
I 14
		if (feof(e->e_dfp))
			bt = MBT_FINAL;
E 14
	}
	else if (sectionsize / 8 < sectionhighbits)
	{
E 3
		/* use base64 encoding */
		int c1, c2;
I 15
D 19
		int (*getcharf) __P((FILE *, char **, int *));
		extern int mime_getchar __P((FILE *, char **, int *));
		extern int mime_getchar_crlf __P((FILE *, char **, int *));
E 19
E 15

I 15
D 16
		if (strcasecmp(type, "text") == 0)
			getcharf = mime_getchar_crlf;
		else
E 16
I 16
D 19
		if (cte != NULL && strcasecmp(cte, "binary") == 0)
E 16
			getcharf = mime_getchar;
I 16
		else
			getcharf = mime_getchar_crlf;
E 19
E 16
E 15
		putline("Content-Transfer-Encoding: base64", mci);
I 14
		if (tTd(43, 36))
			printf("  ...Content-Transfer-Encoding: base64\n");
E 14
		putline("", mci);
		mci->mci_flags &= ~MCIF_INHEADER;
D 14
		linelen = 0;
D 11
		while ((c1 = mime_getchar(e->e_dfp, boundary)) != EOF)
E 11
I 11
		while ((c1 = mime_getchar(e->e_dfp, boundaries)) != EOF)
E 14
I 14
D 15
		while ((c1 = mime_getchar(e->e_dfp, boundaries, &bt)) != EOF)
E 15
I 15
D 19
		while ((c1 = (*getcharf)(e->e_dfp, boundaries, &bt)) != EOF)
E 19
I 19
D 20
		while ((c1 = mime_getchar_crlf(e->e_dfp, boundaries, &bt)) != EOF)
E 20
I 20
		mf->mf_fill = mime_fill_crlf;
		while ((c1 = mime_getc(mf)) != EOF)
E 20
E 19
E 15
E 14
E 11
		{
			if (linelen > 71)
			{
D 19
				fputs(mci->mci_mailer->m_eol, mci->mci_out);
E 19
I 19
				*bp = '\0';
				putline(buf, mci);
E 19
				linelen = 0;
I 19
				bp = buf;
E 19
			}
			linelen += 4;
D 15
			fputc(Base64Code[c1 >> 2], mci->mci_out);
E 15
I 15
D 18
			fputc(Base64Code[(c1 >> 2) & 0x3f], mci->mci_out);
E 18
I 18
D 19
			fputc(Base64Code[(c1 >> 2)], mci->mci_out);
E 19
I 19
			*bp++ = Base64Code[(c1 >> 2)];
E 19
E 18
E 15
			c1 = (c1 & 0x03) << 4;
D 11
			c2 = mime_getchar(e->e_dfp, boundary);
E 11
I 11
D 14
			c2 = mime_getchar(e->e_dfp, boundaries);
E 14
I 14
D 15
			c2 = mime_getchar(e->e_dfp, boundaries, &bt);
E 15
I 15
D 19
			c2 = (*getcharf)(e->e_dfp, boundaries, &bt);
E 19
I 19
D 20
			c2 = mime_getchar_crlf(e->e_dfp, boundaries, &bt);
E 20
I 20
			c2 = mime_getc(mf);
E 20
E 19
E 15
E 14
E 11
			if (c2 == EOF)
			{
D 15
				fputc(Base64Code[c1], mci->mci_out);
E 15
I 15
D 18
				fputc(Base64Code[c1 & 0x3f], mci->mci_out);
E 18
I 18
D 19
				fputc(Base64Code[c1], mci->mci_out);
E 18
E 15
				fputc('=', mci->mci_out);
				fputc('=', mci->mci_out);
E 19
I 19
				*bp++ = Base64Code[c1];
				*bp++ = '=';
				*bp++ = '=';
E 19
				break;
			}
			c1 |= (c2 >> 4) & 0x0f;
D 15
			fputc(Base64Code[c1], mci->mci_out);
E 15
I 15
D 18
			fputc(Base64Code[c1 & 0x3f], mci->mci_out);
E 18
I 18
D 19
			fputc(Base64Code[c1], mci->mci_out);
E 19
I 19
			*bp++ = Base64Code[c1];
E 19
E 18
E 15
			c1 = (c2 & 0x0f) << 2;
D 11
			c2 = mime_getchar(e->e_dfp, boundary);
E 11
I 11
D 14
			c2 = mime_getchar(e->e_dfp, boundaries);
E 14
I 14
D 15
			c2 = mime_getchar(e->e_dfp, boundaries, &bt);
E 15
I 15
D 19
			c2 = (*getcharf)(e->e_dfp, boundaries, &bt);
E 19
I 19
D 20
			c2 = mime_getchar_crlf(e->e_dfp, boundaries, &bt);
E 20
I 20
			c2 = mime_getc(mf);
E 20
E 19
E 15
E 14
E 11
			if (c2 == EOF)
			{
D 15
				fputc(Base64Code[c1], mci->mci_out);
E 15
I 15
D 18
				fputc(Base64Code[c1 & 0x3f], mci->mci_out);
E 18
I 18
D 19
				fputc(Base64Code[c1], mci->mci_out);
E 18
E 15
				fputc('=', mci->mci_out);
E 19
I 19
				*bp++ = Base64Code[c1];
				*bp++ = '=';
E 19
				break;
			}
			c1 |= (c2 >> 6) & 0x03;
D 15
			fputc(Base64Code[c1], mci->mci_out);
E 15
I 15
D 18
			fputc(Base64Code[c1 & 0x3f], mci->mci_out);
E 18
I 18
D 19
			fputc(Base64Code[c1], mci->mci_out);
E 18
E 15
			fputc(Base64Code[c2 & 0x3f], mci->mci_out);
E 19
I 19
			*bp++ = Base64Code[c1];
			*bp++ = Base64Code[c2 & 0x3f];
E 19
		}
I 24
		*bp = '\0';
		putline(buf, mci);
E 24
	}
	else
	{
		/* use quoted-printable encoding */
		int c1, c2;
I 10
		int fromstate;
I 17
		BITMAP badchars;
E 17
E 10

I 17
		/* set up map of characters that must be mapped */
		clrbitmap(badchars);
		for (c1 = 0x00; c1 < 0x20; c1++)
			setbitn(c1, badchars);
		clrbitn('\t', badchars);
		for (c1 = 0x7f; c1 < 0x100; c1++)
			setbitn(c1, badchars);
		setbitn('=', badchars);
		if (bitnset(M_EBCDIC, mci->mci_mailer->m_flags))
			for (p = "!\"#$@[\\]^`{|}~"; *p != '\0'; p++)
				setbitn(*p, badchars);

E 17
		putline("Content-Transfer-Encoding: quoted-printable", mci);
I 14
		if (tTd(43, 36))
			printf("  ...Content-Transfer-Encoding: quoted-printable\n");
E 14
		putline("", mci);
		mci->mci_flags &= ~MCIF_INHEADER;
D 10
		linelen = 0;
E 10
I 10
D 14
		linelen = fromstate = 0;
E 14
I 14
		fromstate = 0;
E 14
E 10
D 3
		c2 = EOF;
E 3
I 3
		c2 = '\n';
E 3
D 11
		while ((c1 = mime_getchar(e->e_dfp, boundary)) != EOF)
E 11
I 11
D 14
		while ((c1 = mime_getchar(e->e_dfp, boundaries)) != EOF)
E 14
I 14
D 20
		while ((c1 = mime_getchar(e->e_dfp, boundaries, &bt)) != EOF)
E 20
I 20
		mf->mf_fill = mime_fill_nl;
		while ((c1 = mime_getc(mf)) != EOF)
E 20
E 14
E 11
		{
			if (c1 == '\n')
			{
				if (c2 == ' ' || c2 == '\t')
				{
D 19
					fputc('=', mci->mci_out);
D 7
					fputs(mci->mci_mailer->m_eol, mci->mci_out);
E 7
I 7
					fputc(Base16Code[(c2 >> 4) & 0x0f],
								mci->mci_out);
					fputc(Base16Code[c2 & 0x0f],
								mci->mci_out);
					fputs(mci->mci_mailer->m_eol,
								mci->mci_out);
E 19
I 19
					*bp++ = '=';
					*bp++ = Base16Code[(c2 >> 4) & 0x0f];
					*bp++ = Base16Code[c2 & 0x0f];
D 24
					*bp = '\0';
					putline(buf, mci);
					bp = buf;
E 24
E 19
E 7
				}
D 19
				fputs(mci->mci_mailer->m_eol, mci->mci_out);
E 19
I 19
				*bp = '\0';
				putline(buf, mci);
E 19
D 10
				linelen = 0;
E 10
I 10
				linelen = fromstate = 0;
I 19
				bp = buf;
E 19
E 10
				c2 = c1;
				continue;
			}
I 7
D 10
			if (c2 == ' ' || c2 == '\t')
E 10
I 10
			if (c2 == ' ' && linelen == 4 && fromstate == 4 &&
			    bitnset(M_ESCFROM, mci->mci_mailer->m_flags))
E 10
			{
I 10
D 19
				fputs("=20", mci->mci_out);
E 19
I 19
				*bp++ = '=';
				*bp++ = '2';
				*bp++ = '0';
E 19
				linelen += 3;
			}
			else if (c2 == ' ' || c2 == '\t')
			{
E 10
D 19
				fputc(c2, mci->mci_out);
E 19
I 19
				*bp++ = c2;
E 19
				linelen++;
			}
E 7
I 3
D 6
			else if (c2 == '\n' && c1 == '.' &&
				 bitnset(M_XDOT, mci->mci_mailer->m_flags))
			{
				fputc('.', mci->mci_out);
				linelen++;
			}
E 6
E 3
			if (linelen > 72)
			{
D 19
				fputc('=', mci->mci_out);
				fputs(mci->mci_mailer->m_eol, mci->mci_out);
E 19
I 19
				*bp++ = '=';
				*bp = '\0';
				putline(buf, mci);
E 19
D 10
				linelen = 0;
E 10
I 10
				linelen = fromstate = 0;
I 19
				bp = buf;
E 19
E 10
I 3
				c2 = '\n';
I 6
			}
D 19
			if (c2 == '\n' && c1 == '.' &&
				 bitnset(M_XDOT, mci->mci_mailer->m_flags))
			{
				fputc('.', mci->mci_out);
				linelen++;
E 6
E 3
			}
E 19
D 2
			if ((c1 < 0x20 && c1 != '\t') || c2 >= 0xff || c2 == '=')
E 2
I 2
D 17
			if ((c1 < 0x20 && c1 != '\t') || c1 >= 0x7f || c1 == '=')
E 17
I 17
			if (bitnset(c1 & 0xff, badchars))
E 17
E 2
			{
D 19
				fputc('=', mci->mci_out);
				fputc(Base16Code[(c1 >> 4) & 0x0f], mci->mci_out);
				fputc(Base16Code[c1 & 0x0f], mci->mci_out);
E 19
I 19
				*bp++ = '=';
				*bp++ = Base16Code[(c1 >> 4) & 0x0f];
				*bp++ = Base16Code[c1 & 0x0f];
E 19
				linelen += 3;
			}
D 7
			else
E 7
I 7
			else if (c1 != ' ' && c1 != '\t')
E 7
			{
I 10
				if (linelen < 4 && c1 == "From"[linelen])
					fromstate++;
E 10
D 19
				fputc(c1, mci->mci_out);
E 19
I 19
				*bp++ = c1;
E 19
				linelen++;
			}
			c2 = c1;
I 7
		}

		/* output any saved character */
		if (c2 == ' ' || c2 == '\t')
		{
D 10
			fputc(c2, mci->mci_out);
			linelen++;
E 10
I 10
D 19
			fputc('=', mci->mci_out);
			fputc(Base16Code[(c2 >> 4) & 0x0f], mci->mci_out);
			fputc(Base16Code[c2 & 0x0f], mci->mci_out);
E 19
I 19
			*bp++ = '=';
			*bp++ = Base16Code[(c2 >> 4) & 0x0f];
			*bp++ = Base16Code[c2 & 0x0f];
E 19
			linelen += 3;
E 10
E 7
		}
D 24
	}
	if (linelen > 0)
D 19
		fputs(mci->mci_mailer->m_eol, mci->mci_out);
E 19
I 19
	{
		*bp = '\0';
		putline(buf, mci);
E 24
I 24

		if (linelen > 0 || boundaries[0] != NULL)
		{
			*bp = '\0';
			putline(buf, mci);
		}

E 24
	}
E 19
D 2
	return bt;
E 2
I 2
D 14
	return MimeBoundaryType;
E 14
I 14
	if (tTd(43, 3))
		printf("\t\t\tmime8to7=>%s (basic)\n", MimeBoundaryNames[bt]);
	return bt;
E 14
E 2
}
I 10
/*
**  MIME_GETCHAR -- get a character for MIME processing
**
**	Treats boundaries as EOF.
**
**	Parameters:
**		fp -- the input file.
D 11
**		boundary -- the current MIME boundary.
E 11
I 11
**		boundaries -- the current MIME boundaries.
I 14
**		btp -- if the return value is EOF, *btp is set to
**			the type of the boundary.
E 14
E 11
**
**	Returns:
**		The next character in the input stream.
*/
E 10

D 10

E 10
int
D 11
mime_getchar(fp, boundary)
E 11
I 11
D 14
mime_getchar(fp, boundaries)
E 14
I 14
mime_getchar(fp, boundaries, btp)
E 14
E 11
	register FILE *fp;
D 11
	char *boundary;
E 11
I 11
	char **boundaries;
I 14
	int *btp;
E 14
E 11
{
	int c;
D 18
	static char *bp = NULL;
E 18
I 18
	static u_char *bp = NULL;
E 18
	static int buflen = 0;
	static bool atbol = TRUE;	/* at beginning of line */
I 14
	static int bt = MBT_SYNTAX;	/* boundary type of next EOF */
E 14
D 18
	static char buf[128];		/* need not be a full line */
E 18
I 18
	static u_char buf[128];		/* need not be a full line */
E 18

	if (buflen > 0)
	{
		buflen--;
		return *bp++;
	}
I 10
	bp = buf;
	buflen = 0;
E 10
D 19
	c = fgetc(fp);
E 19
I 19
	c = getc(fp);
E 19
I 10
	if (c == '\n')
	{
		/* might be part of a MIME boundary */
		*bp++ = c;
		atbol = TRUE;
D 19
		c = fgetc(fp);
E 19
I 19
		c = getc(fp);
		if (c == '\n')
		{
			ungetc(c, fp);
			return c;
		}
E 19
	}
	if (c != EOF)
		*bp++ = c;
I 14
	else
		bt = MBT_FINAL;
E 14
E 10
D 11
	if (atbol && c == '-' && boundary != NULL)
E 11
I 11
	if (atbol && c == '-')
E 11
	{
		/* check for a message boundary */
D 10
		bp = buf;
E 10
D 19
		c = fgetc(fp);
E 19
I 19
		c = getc(fp);
E 19
		if (c != '-')
		{
			if (c != EOF)
D 10
			{
				*bp = c;
				buflen++;
			}
			return '-';
E 10
I 10
				*bp++ = c;
I 14
			else
				bt = MBT_FINAL;
E 14
			buflen = bp - buf - 1;
			bp = buf;
			return *bp++;
E 10
		}

		/* got "--", now check for rest of separator */
		*bp++ = '-';
D 10
		*bp++ = '-';
E 10
D 15
		while (bp < &buf[sizeof buf - 1] &&
E 15
I 15
		while (bp < &buf[sizeof buf - 2] &&
E 15
D 19
		       (c = fgetc(fp)) != EOF && c != '\n')
E 19
I 19
		       (c = getc(fp)) != EOF && c != '\n')
E 19
		{
			*bp++ = c;
		}
		*bp = '\0';
D 2
		switch (mimeboundary(buf, boundary))
E 2
I 2
D 11
		MimeBoundaryType = mimeboundary(buf, boundary);
E 11
I 11
D 14
		MimeBoundaryType = mimeboundary(buf, boundaries);
E 11
		switch (MimeBoundaryType)
E 14
I 14
		bt = mimeboundary(&buf[1], boundaries);
		switch (bt)
E 14
E 2
		{
		  case MBT_FINAL:
		  case MBT_INTERMED:
			/* we have a message boundary */
			buflen = 0;
I 14
			*btp = bt;
E 14
			return EOF;
		}

		atbol = c == '\n';
		if (c != EOF)
			*bp++ = c;
D 10
		buflen = bp - buf - 1;
		bp = buf;
		return *bp++;
E 10
D 3
	}
	else if (atbol && c == '.')
	{
		/* implement hidden dot algorithm */
		bp = buf;
		*bp = c;
		buflen = 1;
		c = fgetc(fp);
		if (c != '\n')
			return '.';
		atbol = TRUE;
		buf[0] = '.';
		buf[1] = '\n';
		buflen = 2;
		return '.';
E 3
	}

D 10
	atbol = c == '\n';
	return c;
E 10
I 10
	buflen = bp - buf - 1;
	if (buflen < 0)
I 14
	{
		*btp = bt;
E 14
		return EOF;
I 14
	}
E 14
	bp = buf;
	return *bp++;
I 15
}
/*
**  MIME_GETCHAR_CRLF -- do mime_getchar, but translate NL => CRLF
**
**	Parameters:
**		fp -- the input file.
**		boundaries -- the current MIME boundaries.
**		btp -- if the return value is EOF, *btp is set to
**			the type of the boundary.
**
**	Returns:
**		The next character in the input stream.
*/

int
mime_getchar_crlf(fp, boundaries, btp)
	register FILE *fp;
	char **boundaries;
	int *btp;
{
	static bool sendlf = FALSE;
	int c;

	if (sendlf)
	{
		sendlf = FALSE;
		return '\n';
	}
	c = mime_getchar(fp, boundaries, btp);
	if (c == '\n')
	{
		sendlf = TRUE;
		return '\r';
	}
	return c;
I 20
}
/*
**  MIME7TO8 -- convert 7 bit MIME message to 8 bit
*/

char	QPdecoder[256] =
{
    /*	nul soh stx etx eot enq ack bel  bs  ht  nl  vt  np  cr  so  si   */
	-1, -1, -1, -1, -1, -1, -1, -1,  -1, -1, 16, -1, -1, 16, -1, -1,
    /*	dle dc1 dc2 dc3 dc4 nak syn etb  can em  sub esc fs  gs  rs  us   */
	-1, -1, -1, -1, -1, -1, -1, -1,  -1, -1, -1, -1, -1, -1, -1, -1,
    /*  sp  !   "   #   $   %   &   '    (   )   *   +   ,   -   .   /    */
	-1, -1, -1, -1, -1, -1, -1, -1,  -1, -1, -1, -1, -1, -1, -1, -1,
    /*	0   1   2   3   4   5   6   7    8   9   :   ;   <   =   >   ?    */
	0,  1,  2,  3,  4,  5,  6,  7,   8,  9,  -1, -1, -1, -1, -1, -1,
    /*	@   A   B   C   D   E   F   G    H   I   J   K   L   M   N   O    */
	-1, 10, 11, 12, 13, 14, 15, -1,  -1, -1, -1, -1, -1, -1, -1, -1,
    /*  P   Q   R   S   T   U   V   W    X   Y   Z   [   \   ]   ^   _    */
	-1, -1, -1, -1, -1, -1, -1, -1,  -1, -1, -1, -1, -1, -1, -1, -1,
    /*	`   a   b   c   d   e   f   g    h   i   j   k   l   m   n   o    */
	-1, 10, 11, 12, 13, 14, 15, -1,  -1, -1, -1, -1, -1, -1, -1, -1,
    /*  p   q   r   s   t   u   v   w    x   y   z   {   |   }   ~   del  */
	-1, -1, -1, -1, -1, -1, -1, -1,  -1, -1, -1, -1, -1, -1, -1, -1,

    /*	nul soh stx etx eot enq ack bel  bs  ht  nl  vt  np  cr  so  si   */
	-1, -1, -1, -1, -1, -1, -1, -1,  -1, -1, -1, -1, -1, -1, -1, -1,
    /*	dle dc1 dc2 dc3 dc4 nak syn etb  can em  sub esc fs  gs  rs  us   */
	-1, -1, -1, -1, -1, -1, -1, -1,  -1, -1, -1, -1, -1, -1, -1, -1,
    /*  sp  !   "   #   $   %   &   '    (   )   *   +   ,   -   .   /    */
	-1, -1, -1, -1, -1, -1, -1, -1,  -1, -1, -1, -1, -1, -1, -1, -1,
    /*	0   1   2   3   4   5   6   7    8   9   :   ;   <   =   >   ?    */
	-1, -1, -1, -1, -1, -1, -1, -1,  -1, -1, -1, -1, -1, -1, -1, -1,
    /*	@   A   B   C   D   E   F   G    H   I   J   K   L   M   N   O    */
	-1, -1, -1, -1, -1, -1, -1, -1,  -1, -1, -1, -1, -1, -1, -1, -1,
    /*  P   Q   R   S   T   U   V   W    X   Y   Z   [   \   ]   ^   _    */
	-1, -1, -1, -1, -1, -1, -1, -1,  -1, -1, -1, -1, -1, -1, -1, -1,
    /*	`   a   b   c   d   e   f   g    h   i   j   k   l   m   n   o    */
	-1, -1, -1, -1, -1, -1, -1, -1,  -1, -1, -1, -1, -1, -1, -1, -1,
    /*  p   q   r   s   t   u   v   w    x   y   z   {   |   }   ~   del  */
	-1, -1, -1, -1, -1, -1, -1, -1,  -1, -1, -1, -1, -1, -1, -1, -1,
};


int
mime7to8(mci, header, e, boundaries, flags)
	register MCI *mci;
	HDR *header;
	register ENVELOPE *e;
	char **boundaries;
	int flags;
{
	register char *p;
	int linelen;
	int bt;
	off_t offset;
	int i;
	char *type;
	char *subtype;
	char *cte;
	char **pvp;
	int argc = 0;
	char *bp;
	struct args argv[MAXMIMEARGS];
	char bbuf[128];
	char buf[MAXLINE];
	char pvpbuf[MAXLINE];
	extern char MimeTokenTab[256];

	if (tTd(43, 1))
	{
		printf("mime7to8: flags = %x, boundaries =", flags);
		if (boundaries[0] == NULL)
			printf(" <none>");
		else
		{
			for (i = 0; boundaries[i] != NULL; i++)
				printf(" %s", boundaries[i]);
		}
		printf("\n");
	}
	p = hvalue("Content-Transfer-Encoding", header);
	if (p == NULL ||
	    (pvp = prescan(p, '\0', pvpbuf, sizeof pvpbuf, NULL,
			   MimeTokenTab)) == NULL ||
	    pvp[0] == NULL)
	{
		cte = NULL;
	}
	else
	{
		cataddr(pvp, NULL, buf, sizeof buf, '\0');
		cte = newstr(buf);
	}

	type = subtype = NULL;
	p = hvalue("Content-Type", header);
	if (p == NULL)
	{
		if (bitset(M87F_DIGEST, flags))
			p = "message/rfc822";
		else
			p = "text/plain";
	}
	if (p != NULL &&
	    (pvp = prescan(p, '\0', pvpbuf, sizeof pvpbuf, NULL,
			   MimeTokenTab)) != NULL &&
	    pvp[0] != NULL)
	{
		if (tTd(43, 40))
		{
			for (i = 0; pvp[i] != NULL; i++)
				printf("pvp[%d] = \"%s\"\n", i, pvp[i]);
		}
		type = *pvp++;
		if (*pvp != NULL && strcmp(*pvp, "/") == 0 &&
		    *++pvp != NULL)
		{
			subtype = *pvp++;
		}

		/* break out parameters */
		while (*pvp != NULL && argc < MAXMIMEARGS)
		{
			/* skip to semicolon separator */
			while (*pvp != NULL && strcmp(*pvp, ";") != 0)
				pvp++;
			if (*pvp++ == NULL || *pvp == NULL)
				break;

			/* extract field name */
			argv[argc].field = *pvp++;

			/* see if there is a value */
			if (*pvp != NULL && strcmp(*pvp, "=") == 0 &&
			    (*++pvp == NULL || strcmp(*pvp, ";") != 0))
			{
				argv[argc].value = *pvp;
				argc++;
			}
		}
	}

	/* check for disaster cases */
	if (type == NULL)
		type = "-none-";
	if (subtype == NULL)
		subtype = "-none-";

	/* don't propogate some flags more than one level into the message */
	flags &= ~M87F_DIGEST;

	/*
	**  Check for cases that can not be encoded.
	**
	**	For example, you can't encode certain kinds of types
	**	or already-encoded messages.  If we find this case,
	**	just copy it through.
	*/

	sprintf(buf, "%s/%s", type, subtype);
	if (wordinclass(buf, 'n') || (cte != NULL && !wordinclass(cte, 'e')))
		flags |= M87F_NO8BIT;

	/*
	**  Multipart requires special processing.
	**
	**	Do a recursive descent into the message.
	*/

	if (strcasecmp(type, "multipart") == 0 && !bitset(M87F_NO8BIT, flags))
	{
		int blen;

		if (strcasecmp(subtype, "digest") == 0)
			flags |= M87F_DIGEST;

		for (i = 0; i < argc; i++)
		{
			if (strcasecmp(argv[i].field, "boundary") == 0)
				break;
		}
		if (i >= argc)
		{
			syserr("mime7to8: Content-Type: %s missing boundary", p);
			p = "---";
		}
		else
		{
			p = argv[i].value;
			stripquotes(p);
		}
		blen = strlen(p);
		if (blen > sizeof bbuf - 1)
		{
			syserr("mime7to8: multipart boundary \"%s\" too long",
				p);
			blen = sizeof bbuf - 1;
		}
		strncpy(bbuf, p, blen);
		bbuf[blen] = '\0';
		if (tTd(43, 1))
			printf("mime7to8: multipart boundary \"%s\"\n", bbuf);
		for (i = 0; i < MAXMIMENESTING; i++)
			if (boundaries[i] == NULL)
				break;
		if (i >= MAXMIMENESTING)
			syserr("mime7to8: multipart nesting boundary too deep");
		else
		{
			boundaries[i] = bbuf;
			boundaries[i + 1] = NULL;
		}

		/* skip the early "comment" prologue */
		putline("", mci);
		while (fgets(buf, sizeof buf, e->e_dfp) != NULL)
		{
			bt = mimeboundary(buf, boundaries);
			if (bt != MBT_NOTSEP)
				break;
			putxline(buf, mci, PXLF_MAPFROM|PXLF_STRIP8BIT);
			if (tTd(43, 99))
				printf("  ...%s", buf);
		}
		if (feof(e->e_dfp))
			bt = MBT_FINAL;
		while (bt != MBT_FINAL)
		{
			auto HDR *hdr = NULL;

			sprintf(buf, "--%s", bbuf);
			putline(buf, mci);
			if (tTd(43, 35))
				printf("  ...%s\n", buf);
			collect(e->e_dfp, FALSE, FALSE, &hdr, e);
			if (tTd(43, 101))
				putline("+++after collect", mci);
			putheader(mci, hdr, e);
			if (tTd(43, 101))
				putline("+++after putheader", mci);
			bt = mime7to8(mci, hdr, e, boundaries, flags);
		}
		sprintf(buf, "--%s--", bbuf);
		putline(buf, mci);
		if (tTd(43, 35))
			printf("  ...%s\n", buf);
		boundaries[i] = NULL;

		/* skip the late "comment" epilogue */
		while (fgets(buf, sizeof buf, e->e_dfp) != NULL)
		{
			bt = mimeboundary(buf, boundaries);
			if (bt != MBT_NOTSEP)
				break;
			putxline(buf, mci, PXLF_MAPFROM|PXLF_STRIP8BIT);
			if (tTd(43, 99))
				printf("  ...%s", buf);
		}
		if (feof(e->e_dfp))
			bt = MBT_FINAL;
		if (tTd(43, 3))
			printf("\t\t\tmime7to8=>%s (multipart)\n",
				MimeBoundaryNames[bt]);
		return bt;
	}

	/*
	**  Message/* types -- recurse exactly once.
	*/

	if (strcasecmp(type, "message") == 0)
	{
		if (strcasecmp(subtype, "rfc822") != 0)
		{
			flags |= M87F_NO8BIT;
		}
		else
		{
			register char *q;
			auto HDR *hdr = NULL;

			putline("", mci);

			collect(e->e_dfp, FALSE, FALSE, &hdr, e);
			if (tTd(43, 101))
				putline("+++after collect", mci);
			putheader(mci, hdr, e);
			if (tTd(43, 101))
				putline("+++after putheader", mci);
			bt = mime7to8(mci, hdr, e, boundaries, flags);
			return bt;
		}
	}

	/*
	**  Non-compound body type.
	**
	**	First scan to see if it is legally translatable.  This
	**	means:
	**
	**	  * No long lines.
	**	  * No bare CR or NL bytes.
	**
	**	We'll also check to see if there are any 8-bit characters
	**	so we can make a good choice of final encoding method.
	*/

	nodecode = FALSE;
	has8bit = FALSE;
	if (cte != NULL && strcasecmp(cte, "base64") == 0)
		mf->mf_fill = mime_fill_base64;
	else if (cte != NULL && strcasecmp(cte, "quoted-printable") != 0)
		mf->mf_fill = mime_fill_qp;
	else
		nodecode = TRUE;

	maxlinelen = 0;
	if (!nodecode)
	{
		offset = mime_tell(mfp);
		if (offset == -1)
			syserr("mime7to8: cannot ftell on df%s", e->e_id);

		linelen = 0;
		while (!nodecode && (c = mime_getc(mfp)) != EOF)
		{
			if (bitset(0x80, c))
				has8bit = TRUE;
			else if (c == '\n' || c == '\0')
				nodecode = TRUE;
			else if (c == '\r')
			{
				c = mime_getc(mfp);
				if (c == '\n')
				{
					if (linelen > maxlinelen)
						maxlinelen = linelen;
					linelen = 0;
					continue;
				}
				nodecode = TRUE;
			}
			else
				linelen++;
		}
		if (linelen != 0 || maxlinelen > mci->mci_mailer->m_maxline)
			nodecode = TRUE;
		if (mime_seek(mfp, offset, SEEK_SET) < 0)
			syserr("mime7to8: cannot fseek on df%s", e->e_id)
		else
			mime_clearerr(mfp);
		mime_flush(mfp);
	}

	if (tTd(43, 8))
	{
		printf("mime7to8: cte=%s, maxlinelen=%d, nodecode=%d, has8bit=%d\n",
			cte == NULL ? "[none]" : cte,
			maxlinelen, nodecode, has8bit);
	}

	if (!nodecode)
	{
		/*
		**  Convert to 8-bit.  We know it will be well-behaved.
		*/

		if (has8bit)
			p = "8bit";
		else
			p = "7bit";
	}
	else
	{
		p = cte;
		mfp->mf_fill = mime_fill;
	}
	if (p != NULL)
	{
		sprintf(buf, "Content-Transfer-Encoding: %s", p);
		putline(buf, mci);
	}
	putline("", mci);
	mci->mci_flags &= ~MCIF_INHEADER;

	p = buf;
	linelen = 0;
	while ((c = mime_getc(mfp)) != EOF)
	{
		while (c == '\r')
		{
			c = mime_getc(mfp);
			if (c == '\n')
			{
				*p = '\0';
				putline(buf, mci);
				linelen = fromstate = 0;
				p = buf;
				continue;
			}
			*p++ = '\r';
		}
		if (mci->mci_mailer->m_linelimit > 0 &&
		    linelen > mci->mci_mailer->m_linelimit - 1)
		{
			/* line wrap */
			putc('!', mci->mci_out);
			fputs(mci->mci_mailer->m_eol, mci->mci_out);
			linelen = 0;
		}
		if (linelen == 0 && c == '.' &&
		    bitnset(M_XDOT, mci->mci_mailer->m_flags))
		{
			putc('.', mci->mci_out);
			linelen++;
		}
		if (linelen == fromstate && c == "From "[fromstate])
		{
			if (fromstate == 4)
			{
				/* hide From_? */
				if (bitnset(M_ESCFROM, mci->mci_mailer->m_flags))
				{
					putc('>', mci->mci_out);
					linelen++;
				}
				fputs("From ", mci->mci_out);
				fromstate = -1;
			}
			fromstate++;
			linelen++;
			continue;
		}
		if (fromstate != 0)
		{
			p = "From ";
			while (--fromstate >= 0)
				putc(*p++, mci->mci_out);
		}
		putc(c, mci->mci_out);
		linelen++;
	}
	if (tTd(43, 3))
		printf("\t\t\tmime7to8=>%s (basic)\n", MimeBoundaryNames[bt]);
	return bt;
}
/*
**  MIME_FILL_QP -- fill buffer doing Quoted-Printable decoding
**
**	Parameters:
**		mfp -- MIME file pointer.
**
**	Returns:
**		The next character in the input stream.
*/

int
mime_fill_qp(mfp)
	register MFILE;
{
	int c;

	/* first do the raw buffer fill */
	if (mime_fill_nl(mfp) == EOF)
		return EOF;

	/* now scan the buffer converting =XX */
	ip = op = mfp->mf_buf;
	il = mfp->mf_cnt;
	while (--il >= 0)
	{
		if (*ip != '=')
		{
			*op++ = *ip++;
			continue;
		}

		/* special handling for "=" sign */
		if (il >= 2 && !bitset(0x80, ip[1] | ip[2]) &&
		    isxdigit(ip[1]) && isxdigit(ip[2]))
		{
			/* this is an escape sequence */
			/* ASCII dependence ahead.... */
			if (isdigit(*++ip))
				c = *ip - '0';
			else
				c = (*ip & 07) + 9;
			c <<= 4;
			if (isdigit(*++ip))
				c |= *ip - '0';
			else
				c |= (*ip & 07) + 9;
			*op++ = c;
		}
		else if ((il == 2 && ip[1] == '\r' && ip[2] == '\n') ||
			 (il == 1 && ip[1] == '\n'))
		{
			/* this is a hidden newline */
			break;
		}

		/* bogus `=' -- what to do?  treat it as normal */
		*op++ = *ip++;
	}

	/* adjust buffer count to match reality */
	if ((mfp->mf_cnt = op - mfp->mf_buf - 1) <= 0)
		return EOF;
	return *mfp->mf_bp++;
E 20
E 15
E 10
}
/*
**  MIMEBOUNDARY -- determine if this line is a MIME boundary & its type
**
**	Parameters:
**		line -- the input line.
D 11
**		boundary -- the expected boundary.
E 11
I 11
**		boundaries -- the set of currently pending boundaries.
E 11
**
**	Returns:
**		MBT_NOTSEP -- if this is not a separator line
**		MBT_INTERMED -- if this is an intermediate separator
**		MBT_FINAL -- if this is a final boundary
**		MBT_SYNTAX -- if this is a boundary for the wrong
**			enclosure -- i.e., a syntax error.
*/

int
D 11
mimeboundary(line, boundary)
E 11
I 11
mimeboundary(line, boundaries)
E 11
	register char *line;
D 11
	char *boundary;
E 11
I 11
	char **boundaries;
E 11
{
D 22
	int type;
E 22
I 22
	int type = MBT_NOTSEP;
E 22
	int i;
I 11
	int savec;
E 11

D 11
	if (line[0] != '-' || line[1] != '-' || boundary == NULL)
E 11
I 11
	if (line[0] != '-' || line[1] != '-' || boundaries == NULL)
E 11
		return MBT_NOTSEP;
D 14
	if (tTd(43, 5))
D 11
		printf("mimeboundary: bound=\"%s\", line=\"%s\"... ",
			boundary, line);
E 11
I 11
		printf("mimeboundary: line=\"%s\"... ", line);
E 14
E 11
	i = strlen(line);
	if (line[i - 1] == '\n')
I 10
		i--;
I 14
D 22
	if (tTd(43, 5))
		printf("mimeboundary: line=\"%.*s\"... ", i, line);
E 22
I 22

	/* strip off trailing whitespace */
E 22
E 14
	while (line[i - 1] == ' ' || line[i - 1] == '\t')
E 10
		i--;
D 22
	if (i > 2 && strncmp(&line[i - 2], "--", 2) == 0)
E 22
I 22
	savec = line[i];
	line[i] = '\0';

	if (tTd(43, 5))
		printf("mimeboundary: line=\"%s\"... ", line);

	/* check for this as an intermediate boundary */
	if (isboundary(&line[2], boundaries) >= 0)
		type = MBT_INTERMED;
	else if (i > 2 && strncmp(&line[i - 2], "--", 2) == 0)
E 22
	{
D 22
		type = MBT_FINAL;
		i -= 2;
E 22
I 22
		/* check for a final boundary */
		line[i - 2] = '\0';
		if (isboundary(&line[2], boundaries) >= 0)
			type = MBT_FINAL;
		line[i - 2] = '-';
E 22
	}
D 22
	else
		type = MBT_INTERMED;
E 22

I 11
D 22
	savec = line[i];
	line[i] = '\0';
E 11
	/* XXX should check for improper nesting here */
D 11
	if (strncmp(boundary, &line[2], i - 2) != 0 ||
	    strlen(boundary) != i - 2)
E 11
I 11
	if (isboundary(&line[2], boundaries) < 0)
E 11
		type = MBT_NOTSEP;
E 22
I 11
	line[i] = savec;
E 11
	if (tTd(43, 5))
D 14
		printf("%d\n", type);
E 14
I 14
		printf("%s\n", MimeBoundaryNames[type]);
E 14
	return type;
}
I 8
/*
**  DEFCHARSET -- return default character set for message
**
**	The first choice for character set is for the mailer
**	corresponding to the envelope sender.  If neither that
**	nor the global configuration file has a default character
**	set defined, return "unknown-8bit" as recommended by
**	RFC 1428 section 3.
**
**	Parameters:
**		e -- the envelope for this message.
**
**	Returns:
**		The default character set for that mailer.
*/

char *
defcharset(e)
	register ENVELOPE *e;
{
	if (e != NULL && e->e_from.q_mailer != NULL &&
	    e->e_from.q_mailer->m_defcharset != NULL)
		return e->e_from.q_mailer->m_defcharset;
	if (DefaultCharSet != NULL)
		return DefaultCharSet;
	return "unknown-8bit";
I 11
}
/*
**  ISBOUNDARY -- is a given string a currently valid boundary?
**
**	Parameters:
**		line -- the current input line.
**		boundaries -- the list of valid boundaries.
**
**	Returns:
**		The index number in boundaries if the line is found.
**		-1 -- otherwise.
**
*/

int
isboundary(line, boundaries)
	char *line;
	char **boundaries;
{
	register int i;

D 13
	i = 0;
	while (boundaries[i] != NULL)
E 13
I 13
	for (i = 0; boundaries[i] != NULL; i++)
E 13
	{
		if (strcmp(line, boundaries[i]) == 0)
			return i;
	}
	return -1;
E 11
}
I 23

#endif /* MIME */
E 23
E 8
E 1
