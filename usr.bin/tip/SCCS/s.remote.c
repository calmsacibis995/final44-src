h22908
s 00004/00004/00196
d D 8.1 93/06/06 16:34:41 bostic 18 17
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00000/00194
d D 5.10 92/10/17 13:50:21 bostic 17 16
c it's considered tacky to remove the include files
e
s 00001/00001/00193
d D 5.9 92/09/16 10:56:17 elan 16 15
c copyright[] -> static.
e
s 00008/00032/00186
d D 5.8 92/09/15 11:02:09 elan 15 14
c Added SCCS keywords.
e
s 00000/00001/00218
d D 5.7 92/08/31 15:35:19 elan 14 13
c getcap.h = stdlib.h
e
s 00083/00032/00136
d D 5.6 92/08/31 15:32:54 elan 13 12
c Changed to use new getcap(3) routines.
e
s 00001/00011/00167
d D 5.5 90/06/01 17:47:43 bostic 12 11
c new copyright notice
e
s 00015/00004/00163
d D 5.4 88/09/02 12:04:45 bostic 11 10
c add Berkeley specific copyright
e
s 00002/00002/00165
d D 5.3 86/04/30 14:41:50 mckusick 10 9
c avoid dereference of null pointer (from kirk@oz)
e
s 00011/00000/00156
d D 5.2 85/12/09 21:36:40 karels 9 8
c behave sensibly if using cu -l and /etc/remote has nothing to say
c about it
e
s 00007/00001/00149
d D 5.1 85/04/30 12:34:34 dist 8 7
c Add copyright
e
s 00046/00024/00104
d D 4.7 83/06/25 01:14:24 sam 7 6
c so much...clean up after ralph's merge of wendel and mo code;
c purge VMUNIX include since changes for signals make it no longer portable 
c to systems other than 4.2; fix ventel for no echo strapping; do setjmps 
c instead of assuming interrupted system calls; purge lcmd, if people use 
e
s 00033/00002/00095
d D 4.6 83/06/15 13:52:49 ralph 6 5
c changes for local info, parity, vadic auto dialers
e
s 00009/00006/00088
d D 4.5 81/11/29 22:50:41 sam 5 4
c reformatting
e
s 00000/00000/00094
d D 4.4 81/11/20 10:44:52 sam 4 3
c cosmetics
e
s 00006/00000/00088
d D 4.3 81/07/13 09:43:08 sam 3 2
c guard against missing "hw" attributes
e
s 00001/00000/00087
d D 4.2 81/06/16 16:43:33 sam 2 1
c lots of patches to satisfy the DN-11's wants
e
s 00087/00000/00000
d D 4.1 81/05/09 16:45:21 root 1 0
c date and time created 81/05/09 16:45:21 by root
e
u
U
t
T
I 8
/*
D 11
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 11
I 11
D 15
 * Copyright (c) 1983 The Regents of the University of California.
E 15
I 15
D 18
 * Copyright (c) 1992 The Regents of the University of California.
E 15
 * All rights reserved.
E 18
I 18
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 18
 *
D 12
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
E 12
I 12
D 13
 * %sccs.include.redist.c%
E 13
I 13
D 15
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
E 15
 *
D 15
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
E 15
I 15
 * %sccs.include.redist.c%
E 15
E 13
E 12
E 11
 */

E 8
I 1
D 7
/*	%M%	%I%	%E%	*/
E 7
I 7
#ifndef lint
D 13
static char sccsid[] = "%W% (Berkeley) %G%";
E 13
I 13
D 15
static char sccsid[] = "@(#)remote.c	5.6 (Berkeley) 8/6/92";
E 15
I 15
D 16
char copyright[] =
E 16
I 16
static char copyright[] =
E 16
D 18
"%Z% Copyright (c) 1992 The Regents of the University of California.\n\
 All rights reserved.\n";
E 18
I 18
"%Z% Copyright (c) 1992, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 18
E 15
E 13
D 8
#endif
E 8
I 8
D 11
#endif not lint
E 11
I 11
#endif /* not lint */
E 11
E 8

E 7
D 13
# include "tip.h"
E 13
I 13
D 15
#include <stdlib.h>
#include <stdio.h>
D 14
#include <getcap.h>
E 14
#include "pathnames.h"
#include "tip.h"
E 15
I 15
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 15
E 13

I 17
#include <stdio.h>
#include <stdlib.h>

#include "pathnames.h"
#include "tip.h"

E 17
I 6
D 7
static char *sccsid = "%W% %G%";

E 7
E 6
/*
 * Attributes to be gleened from remote host description
 *   data base.
 */
static char **caps[] = {
D 6
	&AT, &DV, &CM, &CU, &EL, &IE, &OE, &PN
E 6
I 6
	&AT, &DV, &CM, &CU, &EL, &IE, &OE, &PN, &PR, &DI,
	&ES, &EX, &FO, &RC, &RE, &PA
E 6
};

static char *capstrings[] = {
D 6
	"at", "dv", "cm", "cu", "el", "ie", "oe", "pn", 0
E 6
I 6
	"at", "dv", "cm", "cu", "el", "ie", "oe", "pn", "pr",
	"di", "es", "ex", "fo", "rc", "re", "pa", 0
E 6
};

D 13
char *rgetstr();
E 13
I 13
static char	*db_array[3] = { _PATH_REMOTE, 0, 0 };
E 13

I 13
#define cgetflag(f)	(cgetcap(bp, f, ':') != NULL)

E 13
static
getremcap(host)
	register char *host;
{
D 13
	int stat;
	char tbuf[BUFSIZ];
	static char buf[BUFSIZ/2];
	char *bp = buf;
E 13
	register char **p, ***q;
I 13
	char *bp;
	char *rempath;
	int   stat;
E 13

D 13
	if ((stat = rgetent(tbuf, host)) <= 0) {
E 13
I 13
	rempath = getenv("REMOTE");
	if (rempath != NULL)
		if (*rempath != '/')
			/* we have an entry */
			cgetset(rempath);
		else {	/* we have a path */
			db_array[1] = rempath;
			db_array[2] = _PATH_REMOTE;
		}

	if ((stat = cgetent(&bp, db_array, host)) < 0) {
E 13
I 9
		if (DV ||
		    host[0] == '/' && access(DV = host, R_OK | W_OK) == 0) {
			CU = DV;
			HO = host;
			HW = 1;
			DU = 0;
			if (!BR)
				BR = DEFBR;
			FS = DEFFS;
			return;
		}
E 9
D 13
		fprintf(stderr, stat == 0 ?
			"tip: unknown host %s\n" :
			"tip: can't open host description file\n", host);
E 13
I 13
		switch(stat) {
		case -1:
			fprintf(stderr, "tip: unknown host %s\n", host);
			break;
		case -2:
			fprintf(stderr, 
			    "tip: can't open host description file\n");
			break;
		case -3:
			fprintf(stderr, 
			    "tip: possible reference loop in host description file\n");
			break;
		}
E 13
		exit(3);
	}

	for (p = capstrings, q = caps; *p != NULL; p++, q++)
D 5
		**q = rgetstr(*p, &bp);
	if ((BR = rgetnum("br")) < 0)
E 5
I 5
		if (**q == NULL)
D 13
			**q = rgetstr(*p, &bp);
	if (!BR && (BR = rgetnum("br")) < 0)
E 13
I 13
			cgetstr(bp, *p, *q);
	if (!BR && (cgetnum(bp, "br", &BR) == -1))
E 13
E 5
		BR = DEFBR;
D 13
	if ((FS = rgetnum("fs")) < 0)
E 13
I 13
	if (cgetnum(bp, "fs", &FS) == -1)
E 13
		FS = DEFFS;
D 5
	DU = rgetflag("du");
I 2
	HW = rgetflag("hw");
E 5
I 5
	if (DU < 0)
		DU = 0;
	else
D 13
		DU = rgetflag("du");
E 13
I 13
		DU = cgetflag("du");
E 13
E 5
E 2
	if (DV == NOSTR) {
		fprintf(stderr, "%s: missing device spec\n", host);
		exit(3);
	}
	if (DU && CU == NOSTR)
		CU = DV;
	if (DU && PN == NOSTR) {
		fprintf(stderr, "%s: missing phone number\n", host);
		exit(3);
	}
I 6

D 13
	HD = rgetflag("hd");
E 13
I 13
	HD = cgetflag("hd");
E 13

E 6
I 3
	/*
	 * This effectively eliminates the "hw" attribute
	 *   from the description file
	 */
	if (!HW)
		HW = (CU == NOSTR) || (DU && equal(DV, CU));
E 3
	HO = host;
I 6
	/*
	 * see if uppercase mode should be turned on initially
	 */
D 7
	if (rgetflag("ra")) boolean(value(RAISE)) = 1;
	if (rgetflag("ec")) boolean(value(ECHOCHECK)) = 1;
	if (rgetflag("be")) boolean(value(BEAUTIFY)) = 1;
	if (rgetflag("nb")) boolean(value(BEAUTIFY)) = 0;
	if (rgetflag("sc")) boolean(value(SCRIPT)) = 1;
	if (rgetflag("tb")) boolean(value(TABEXPAND)) = 1;
	if (rgetflag("vb")) boolean(value(VERBOSE)) = 1;
	if (rgetflag("nv")) boolean(value(VERBOSE)) = 0;
	if (rgetflag("ta")) boolean(value(TAND)) = 1;
	if (rgetflag("nt")) boolean(value(TAND)) = 0;
	if (rgetflag("rw")) boolean(value(RAWFTP)) = 1;
	if (rgetflag("hd")) boolean(value(HALFDUPLEX)) = 1;
	if (*RE == NULL) RE = (char *)"tip.record";
	if (*EX == NULL) EX = (char *)"\t\n\b\f";
	if (ES != NOSTR) vstring("es",ES);
	if (FO != NOSTR) vstring("fo",FO);
	if (PR != NOSTR) vstring("pr",PR);
	if (RC != NOSTR) vstring("rc",RC);
	if ((DL = rgetnum("dl")) < 0) DL = 0;
	if ((CL = rgetnum("cl")) < 0) CL = 0;
	if ((ET = rgetnum("et")) < 0) ET = 10;
E 7
I 7
D 13
	if (rgetflag("ra"))
E 13
I 13
	if (cgetflag("ra"))
E 13
		boolean(value(RAISE)) = 1;
D 13
	if (rgetflag("ec"))
E 13
I 13
	if (cgetflag("ec"))
E 13
		boolean(value(ECHOCHECK)) = 1;
D 13
	if (rgetflag("be"))
E 13
I 13
	if (cgetflag("be"))
E 13
		boolean(value(BEAUTIFY)) = 1;
D 13
	if (rgetflag("nb"))
E 13
I 13
	if (cgetflag("nb"))
E 13
		boolean(value(BEAUTIFY)) = 0;
D 13
	if (rgetflag("sc"))
E 13
I 13
	if (cgetflag("sc"))
E 13
		boolean(value(SCRIPT)) = 1;
D 13
	if (rgetflag("tb"))
E 13
I 13
	if (cgetflag("tb"))
E 13
		boolean(value(TABEXPAND)) = 1;
D 13
	if (rgetflag("vb"))
E 13
I 13
	if (cgetflag("vb"))
E 13
		boolean(value(VERBOSE)) = 1;
D 13
	if (rgetflag("nv"))
E 13
I 13
	if (cgetflag("nv"))
E 13
		boolean(value(VERBOSE)) = 0;
D 13
	if (rgetflag("ta"))
E 13
I 13
	if (cgetflag("ta"))
E 13
		boolean(value(TAND)) = 1;
D 13
	if (rgetflag("nt"))
E 13
I 13
	if (cgetflag("nt"))
E 13
		boolean(value(TAND)) = 0;
D 13
	if (rgetflag("rw"))
E 13
I 13
	if (cgetflag("rw"))
E 13
		boolean(value(RAWFTP)) = 1;
D 13
	if (rgetflag("hd"))
E 13
I 13
	if (cgetflag("hd"))
E 13
		boolean(value(HALFDUPLEX)) = 1;
D 10
	if (*RE == NULL)
E 10
I 10
	if (RE == NOSTR)
E 10
		RE = (char *)"tip.record";
D 10
	if (*EX == NULL)
E 10
I 10
	if (EX == NOSTR)
E 10
		EX = (char *)"\t\n\b\f";
	if (ES != NOSTR)
		vstring("es", ES);
	if (FO != NOSTR)
		vstring("fo", FO);
	if (PR != NOSTR)
		vstring("pr", PR);
	if (RC != NOSTR)
		vstring("rc", RC);
D 13
	if ((DL = rgetnum("dl")) < 0)
E 13
I 13
	if (cgetnum(bp, "dl", &DL) == -1)
E 13
		DL = 0;
D 13
	if ((CL = rgetnum("cl")) < 0)
E 13
I 13
	if (cgetnum(bp, "cl", &CL) == -1)
E 13
		CL = 0;
D 13
	if ((ET = rgetnum("et")) < 0)
E 13
I 13
	if (cgetnum(bp, "et", &ET) == -1)
E 13
		ET = 10;
E 7
E 6
}

char *
getremote(host)
	char *host;
{
	register char *cp;
	static char *next;
	static int lookedup = 0;

	if (!lookedup) {
		if (host == NOSTR && (host = getenv("HOST")) == NOSTR) {
			fprintf(stderr, "tip: no host specified\n");
			exit(3);
		}
		getremcap(host);
		next = DV;
		lookedup++;
	}
	/*
	 * We return a new device each time we're called (to allow
	 *   a rotary action to be simulated)
	 */
	if (next == NOSTR)
D 5
		return(NOSTR);
E 5
I 5
		return (NOSTR);
E 5
	if ((cp = index(next, ',')) == NULL) {
		DV = next;
		next = NOSTR;
	} else {
		*cp++ = '\0';
		DV = next;
		next = cp;
	}
D 5
	return(DV);
E 5
I 5
	return (DV);
E 5
}
E 1
