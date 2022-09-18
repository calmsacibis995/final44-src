h19217
s 00002/00002/00711
d D 8.1 93/06/04 12:51:16 bostic 46 45
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00355/00134/00358
d D 5.37 93/06/02 17:04:53 karels 45 44
c integrate changes from bind 4.9 (most of them); continue to use address
c INADDR_ANY rather than 127.1; convert u_short to u_int16_t as appropriate
e
s 00009/00009/00483
d D 5.36 91/03/06 16:02:42 bostic 44 43
c resolver interface with named and friends defined in resolve.h
e
s 00002/00002/00490
d D 5.35 91/03/02 16:11:26 bostic 43 42
c get declarations right
e
s 00013/00013/00479
d D 5.34 91/03/02 16:01:36 bostic 42 41
c p_class, p_type, and fp_query are exported to named
e
s 00009/00004/00483
d D 5.33 91/02/24 12:40:24 bostic 41 40
c Add include files to get prototype declarations, and fix bugs found.
e
s 00010/00008/00477
d D 5.32 91/02/21 16:23:36 bostic 40 39
c make dn_skipname, fp_query, hostalias, p_cdname, p_class, p_query,
c p_rr, p_time, p_type, putlong and putshort hidden
e
s 00001/00001/00484
d D 5.31 90/12/28 16:00:53 william 39 38
c use param.h instead of types.h to pick up BYTE_ORDER transparently
e
s 00009/00012/00476
d D 5.30 90/06/27 13:29:49 bloom 38 37
c fix printing of time when ttl is 0
e
s 00001/00001/00487
d D 5.29 90/02/20 16:06:05 bostic 37 36
c type typo
e
s 00018/00009/00470
d D 5.28 90/02/04 14:19:21 bloom 36 35
c fix C_HS and T_TXT handling
e
s 00003/00001/00476
d D 5.27 89/12/27 11:40:18 bloom 35 34
c abort further processing of packet if length error detected in p_rr()
e
s 00017/00011/00460
d D 5.26 89/12/12 13:17:28 bloom 34 33
c clean up time printing a bit more; fix T_TXT format (more still
c needed); fix spelling and names
e
s 00013/00030/00458
d D 5.25 89/09/15 14:28:08 bloom 33 32
c Remove old RRs, add C_HS & T_TXT, p_time was called incorrectly
e
s 00010/00005/00478
d D 5.24 88/06/27 17:14:13 bostic 32 31
c install approved copyright notice
e
s 00051/00007/00432
d D 5.23 88/05/19 15:50:13 karels 31 30
c print times in human-readable form (from Nowicki)
e
s 00009/00003/00430
d D 5.22 88/03/07 21:17:19 bostic 30 29
c added Berkeley specific header
e
s 00004/00003/00429
d D 5.21 87/10/22 17:43:24 bostic 29 28
c ANSI C; sprintf now returns an int.
e
s 00002/00002/00430
d D 5.20 87/07/27 10:07:09 bostic 28 27
c DEBUG uses strings
e
s 00002/00004/00430
d D 5.19 87/06/30 11:22:52 karels 27 26
c nslookup uses the strings, put them in but make the names harder to hit
e
s 00024/00022/00410
d D 5.18 87/06/17 14:27:30 bostic 26 24
c opcodes/rcodes static, start with underscore; spaces to tabs
c only included on #ifdef DEBUG, #ifdef's to ANSI
e
s 00013/00013/00419
d D 5.17 87/01/31 15:25:38 kjd 24 23
c change getshort() and getlong() to _getshort() and _getlong()
e
s 00002/00000/00430
d D 5.16 86/12/03 11:33:00 kjd 23 22
c add new opcodes
e
s 00022/00002/00408
d D 5.15 86/11/10 15:36:11 kjd 22 21
c fixes for dynamic updates from Mike Schwartz@washington
e
s 00002/00000/00408
d D 5.14 86/09/16 15:27:33 kjd 21 20
c fix printing address class
e
s 00002/00002/00406
d D 5.13 86/03/09 20:35:34 donn 20 19
c added LIBC_SCCS condition for sccs ids
e
s 00001/00001/00407
d D 5.12 86/02/07 18:38:11 karels 19 18
c make up out minds: second arg to dn_expand is ptr, is beyond msg
e
s 00001/00001/00407
d D 5.11 86/02/04 09:06:12 kjd 18 16
c Pass msglen to dn_expand
e
s 00001/00001/00407
d R 5.11 86/02/02 19:39:03 kjd 17 16
c pass msglen to dn_expand
e
s 00007/00003/00401
d D 5.10 86/01/18 09:11:30 kjd 16 15
c Fix to MX records
e
s 00009/00000/00395
d D 5.9 86/01/08 11:19:14 kjd 15 14
c Add MX record
e
s 00000/00004/00395
d D 5.8 85/12/01 18:29:42 kjd 14 13
c Not all the debug code gets ifdef'ed jim
e
s 00000/00002/00399
d D 5.7 85/11/01 11:47:02 kjd 13 10
c Freeze for Novebber 1 network distribution
e
s 00000/00002/00399
d R 5.7 85/11/01 11:41:03 kjd 12 10
c Freeze for November 1 network distribution
e
s 00000/00000/00401
d R 6.1 85/10/31 15:29:35 kjd 11 10
c Freeze for November 1 network distribution
e
s 00016/00002/00385
d D 5.6 85/09/14 11:19:33 bloom 10 9
c add ifdef DEBUG around debugging code
e
s 00002/00002/00385
d D 5.5 85/09/11 16:41:17 bloom 9 8
c reverse order of bit in WKS RR
e
s 00001/00001/00386
d D 5.4 85/08/02 10:55:56 kjd 8 7
c Clean up ttl printf in p_rr()
e
s 00078/00068/00309
d D 5.3 85/08/01 11:46:12 kjd 7 6
c Add routine fp_query that will print print the querys to a file
e
s 00001/00001/00376
d D 5.2 85/07/29 17:58:50 kjd 6 5
c Move /usr/include/nameser.h /usr/include/arpa/nameser.h
e
s 00007/00006/00370
d D 5.1 85/05/30 12:05:34 dist 5 4
c Add copyright
e
s 00005/00000/00371
d D 4.4 85/04/01 15:11:02 ralph 4 3
c add copyright notice
e
s 00024/00017/00347
d D 4.3 85/03/29 16:18:54 ralph 3 2
c added MINFO to p_rr()
e
s 00014/00014/00350
d D 4.2 85/03/27 14:58:23 ralph 2 1
c make more machine independent.
e
s 00364/00000/00000
d D 4.1 85/03/01 10:42:12 ralph 1 0
c date and time created 85/03/01 10:42:12 by ralph
e
u
U
t
T
I 1
D 5
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif

E 5
I 4
D 38
/*
E 38
I 38
/*-
E 38
D 5
 * Copyright (c) 1985 Regents of the University of California
 *	All Rights Reserved
E 5
I 5
D 36
 * Copyright (c) 1985 Regents of the University of California.
E 36
I 36
D 46
 * Copyright (c) 1985, 1990 Regents of the University of California.
E 36
D 30
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 30
I 30
 * All rights reserved.
E 46
I 46
 * Copyright (c) 1985, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 46
 *
D 38
 * Redistribution and use in source and binary forms are permitted
D 32
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 32
I 32
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
E 38
I 38
 * %sccs.include.redist.c%
D 45
 *
 *	%W% (Berkeley) %G%
E 45
I 45
 * -
 * Portions Copyright (c) 1993 by Digital Equipment Corporation.
 * 
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies, and that
 * the name of Digital Equipment Corporation not be used in advertising or
 * publicity pertaining to distribution of the document or software without
 * specific, written prior permission.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS" AND DIGITAL EQUIPMENT CORP. DISCLAIMS ALL
 * WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING ALL IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS.   IN NO EVENT SHALL DIGITAL EQUIPMENT
 * CORPORATION BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 * DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 * PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS
 * ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
 * SOFTWARE.
 * -
 * --Copyright--
E 45
E 38
E 32
E 30
E 5
 */
I 5

D 20
#ifndef lint
E 20
I 20
#if defined(LIBC_SCCS) && !defined(lint)
E 20
static char sccsid[] = "%W% (Berkeley) %G%";
D 20
#endif not lint
E 20
I 20
D 30
#endif LIBC_SCCS and not lint
E 30
I 30
#endif /* LIBC_SCCS and not lint */
E 30
E 20
E 5

I 10
D 33
#if defined(lint) && !defined(DEBUG)
#define DEBUG
#endif

E 33
E 10
E 4
D 39
#include <sys/types.h>
E 39
I 39
#include <sys/param.h>
E 39
#include <netinet/in.h>
D 41
#include <stdio.h>
E 41
I 41
#include <arpa/inet.h>
E 41
D 6
#include <nameser.h>
E 6
I 6
#include <arpa/nameser.h>
I 41
#include <resolv.h>
#include <stdio.h>
#include <string.h>
E 41
E 6

I 43
void __fp_query();
D 44
char *__p_class(), *__p_type();
E 43
D 31
extern char *p_cdname(), *p_rr(), *p_type(), *p_class();
E 31
I 31
D 40
extern char *p_cdname(), *p_rr(), *p_type(), *p_class(), *p_time();
E 40
E 31
D 41
extern char *inet_ntoa();
E 41
I 40
D 42
static char *p_cdname(), *p_class(), *p_rr(), *p_time(), *p_type();
E 42
I 42
static char *p_cdname(), *p_rr(), *p_time();
E 44
I 44
char *__p_class(), *__p_time(), *__p_type();
D 45
static char *p_cdname(), *p_rr();
E 45
I 45
char *p_cdname(), *p_fqname(), *p_rr();
static char *p_option __P((u_int32_t));
E 45
E 44
E 42
E 40

D 26
char *opcodes[] = {
E 26
I 26
D 27
#ifdef DEBUG
static char *_opcodes[] = {
E 27
I 27
char *_res_opcodes[] = {
E 27
E 26
	"QUERY",
	"IQUERY",
	"CQUERYM",
	"CQUERYU",
	"4",
	"5",
	"6",
	"7",
	"8",
D 22
	"9",
	"10",
E 22
	"UPDATEA",
	"UPDATED",
I 23
	"UPDATEDA",
E 23
	"UPDATEM",
I 23
	"UPDATEMA",
E 23
	"ZONEINIT",
	"ZONEREF",
};

D 26
char *rcodes[] = {
E 26
I 26
D 27
static char *_rcodes[] = {
E 27
I 27
char *_res_resultcodes[] = {
E 27
E 26
	"NOERROR",
	"FORMERR",
	"SERVFAIL",
	"NXDOMAIN",
	"NOTIMP",
	"REFUSED",
	"6",
	"7",
	"8",
	"9",
	"10",
	"11",
	"12",
	"13",
	"14",
	"NOCHANGE",
};
I 26
D 27
#endif
E 27
E 26

I 45
static char retbuf[16];

static char *
dewks(wks)
	int wks;
{
	switch (wks) {
	case 5: return("rje");
	case 7: return("echo");
	case 9: return("discard");
	case 11: return("systat");
	case 13: return("daytime");
	case 15: return("netstat");
	case 17: return("qotd");
	case 19: return("chargen");
	case 20: return("ftp-data");
	case 21: return("ftp");
	case 23: return("telnet");
	case 25: return("smtp");
	case 37: return("time");
	case 39: return("rlp");
	case 42: return("name");
	case 43: return("whois");
	case 53: return("domain");
	case 57: return("apts");
	case 59: return("apfs");
	case 67: return("bootps");
	case 68: return("bootpc");
	case 69: return("tftp");
	case 77: return("rje");
	case 79: return("finger");
	case 87: return("link");
	case 95: return("supdup");
	case 100: return("newacct");
	case 101: return("hostnames");
	case 102: return("iso-tsap");
	case 103: return("x400");
	case 104: return("x400-snd");
	case 105: return("csnet-ns");
	case 109: return("pop-2");
	case 111: return("sunrpc");
	case 113: return("auth");
	case 115: return("sftp");
	case 117: return("uucp-path");
	case 119: return("nntp");
	case 121: return("erpc");
	case 123: return("ntp");
	case 133: return("statsrv");
	case 136: return("profile");
	case 144: return("NeWS");
	case 161: return("snmp");
	case 162: return("snmp-trap");
	case 170: return("print-srv");
	default: (void) sprintf(retbuf, "%d", wks); return(retbuf);
	}
}

static char *
deproto(protonum)
	int protonum;
{
	switch (protonum) {
	case 1: return("icmp");
	case 2: return("igmp");
	case 3: return("ggp");
	case 5: return("st");
	case 6: return("tcp");
	case 7: return("ucl");
	case 8: return("egp");
	case 9: return("igp");
	case 11: return("nvp-II");
	case 12: return("pup");
	case 16: return("chaos");
	case 17: return("udp");
	default: (void) sprintf(retbuf, "%d", protonum); return(retbuf);
	}
}

static char *
do_rrset(msg, cp, cnt, pflag, file, hs)
	int cnt, pflag;
	char *cp,*msg, *hs;
	FILE *file;
{
	int n;
	int sflag;
	/*
	 * Print  answer records
	 */
	sflag = (_res.pfcode & pflag);
	if (n = ntohs(cnt)) {
		if ((!_res.pfcode) || ((sflag) && (_res.pfcode & RES_PRF_HEAD1)))
			fprintf(file, hs);
		while (--n >= 0) {
			cp = p_rr(cp, msg, file);
			if ((cp-msg) > PACKETSZ)
				return (NULL);
		}
		if ((!_res.pfcode) || ((sflag) && (_res.pfcode & RES_PRF_HEAD1)))
			putc('\n', file);
	}
	return(cp);
}

E 45
I 7
D 40
p_query(msg)
E 40
I 40
__p_query(msg)
E 40
	char *msg;
{
I 41
D 42
	static void fp_query();
E 42
I 42
D 43
	void __fp_query();
E 42

E 43
E 41
I 10
D 33
#ifdef DEBUG
E 33
E 10
D 42
	fp_query(msg,stdout);
E 42
I 42
D 45
	__fp_query(msg,stdout);
E 45
I 45
	__fp_query(msg, stdout);
E 45
E 42
I 10
D 33
#endif
E 33
E 10
}

E 7
/*
I 45
 * Print the current options.
 * This is intended to be primarily a debugging routine.
 */
void
__fp_resstat(statp, file)
	struct __res_state *statp;
	FILE *file;
{
	int bit;

	fprintf(file, ";; res options:");
	if (!statp)
		statp = &_res;
	for (bit = 0;  bit < 32;  bit++) {	/* XXX 32 - bad assumption! */
		if (statp->options & (1<<bit))
			fprintf(file, " %s", p_option(1<<bit));
	}
	putc('\n', file);
}

/*
E 45
 * Print the contents of a query.
 * This is intended to be primarily a debugging routine.
 */
I 40
D 41
static
E 41
I 41
D 42
static void
E 41
E 40
D 3
p_query(buf)
	char *buf;
E 3
I 3
D 7
p_query(msg)
E 7
I 7
fp_query(msg,file)
E 42
I 42
void
__fp_query(msg,file)
E 42
E 7
	char *msg;
I 7
	FILE *file;
E 7
E 3
{
I 10
D 33
#ifdef DEBUG
E 33
E 10
	register char *cp;
	register HEADER *hp;
	register int n;

	/*
	 * Print header fields.
	 */
D 3
	hp = (HEADER *)buf;
	cp = buf + sizeof(HEADER);
E 3
I 3
	hp = (HEADER *)msg;
	cp = msg + sizeof(HEADER);
E 3
D 7
	printf("HEADER:\n");
	printf("\topcode = %s", opcodes[hp->opcode]);
	printf(", id = %d", ntohs(hp->id));
	printf(", rcode = %s\n", rcodes[hp->rcode]);
	printf("\theader flags: ");
E 7
I 7
D 45
	fprintf(file,"HEADER:\n");
D 26
	fprintf(file,"\topcode = %s", opcodes[hp->opcode]);
E 26
I 26
D 28
	fprintf(file,"\topcode = %s", _opcodes[hp->opcode]);
E 28
I 28
	fprintf(file,"\topcode = %s", _res_opcodes[hp->opcode]);
E 28
E 26
	fprintf(file,", id = %d", ntohs(hp->id));
D 26
	fprintf(file,", rcode = %s\n", rcodes[hp->rcode]);
E 26
I 26
D 28
	fprintf(file,", rcode = %s\n", _rcodes[hp->rcode]);
E 28
I 28
	fprintf(file,", rcode = %s\n", _res_resultcodes[hp->rcode]);
E 28
E 26
	fprintf(file,"\theader flags: ");
E 7
	if (hp->qr)
D 7
		printf(" qr");
E 7
I 7
		fprintf(file," qr");
E 7
	if (hp->aa)
D 7
		printf(" aa");
E 7
I 7
		fprintf(file," aa");
E 7
	if (hp->tc)
D 7
		printf(" tc");
E 7
I 7
		fprintf(file," tc");
E 7
	if (hp->rd)
D 7
		printf(" rd");
E 7
I 7
		fprintf(file," rd");
E 7
	if (hp->ra)
D 7
		printf(" ra");
E 7
I 7
		fprintf(file," ra");
E 7
	if (hp->pr)
D 7
		printf(" pr");
	printf("\n\tqdcount = %d", ntohs(hp->qdcount));
	printf(", ancount = %d", ntohs(hp->ancount));
	printf(", nscount = %d", ntohs(hp->nscount));
	printf(", arcount = %d\n\n", ntohs(hp->arcount));
E 7
I 7
		fprintf(file," pr");
	fprintf(file,"\n\tqdcount = %d", ntohs(hp->qdcount));
	fprintf(file,", ancount = %d", ntohs(hp->ancount));
	fprintf(file,", nscount = %d", ntohs(hp->nscount));
	fprintf(file,", arcount = %d\n\n", ntohs(hp->arcount));
E 45
I 45
	if ((!_res.pfcode) || (_res.pfcode & RES_PRF_HEADX) || hp->rcode) {
		fprintf(file,";; ->>HEADER<<- opcode: %s, status: %s, id: %d",
			_res_opcodes[hp->opcode],
			_res_resultcodes[hp->rcode],
			ntohs(hp->id));
		putc('\n', file);
	}
	putc(';', file);
	if ((!_res.pfcode) || (_res.pfcode & RES_PRF_HEAD2)) {
		fprintf(file,"; flags:");
		if (hp->qr)
			fprintf(file," qr");
		if (hp->aa)
			fprintf(file," aa");
		if (hp->tc)
			fprintf(file," tc");
		if (hp->rd)
			fprintf(file," rd");
		if (hp->ra)
			fprintf(file," ra");
		if (hp->pr)
			fprintf(file," pr");
	}
	if ((!_res.pfcode) || (_res.pfcode & RES_PRF_HEAD1)) {
		fprintf(file,"; Ques: %d", ntohs(hp->qdcount));
		fprintf(file,", Ans: %d", ntohs(hp->ancount));
		fprintf(file,", Auth: %d", ntohs(hp->nscount));
		fprintf(file,", Addit: %d\n", ntohs(hp->arcount));
	}
#if 0
	if (_res.pfcode & (RES_PRF_HEADX | RES_PRF_HEAD2 | RES_PRF_HEAD1)) {
		putc('\n',file);
	}
#endif
E 45
E 7
	/*
	 * Print question records.
	 */
	if (n = ntohs(hp->qdcount)) {
D 7
		printf("QUESTIONS:\n");
E 7
I 7
D 45
		fprintf(file,"QUESTIONS:\n");
E 45
I 45
		if ((!_res.pfcode) || (_res.pfcode & RES_PRF_QUES))
			fprintf(file,";; QUESTIONS:\n");
E 45
E 7
		while (--n >= 0) {
D 7
			printf("\t");
D 3
			cp = p_cdname(cp, buf);
E 3
I 3
			cp = p_cdname(cp, msg);
E 7
I 7
D 45
			fprintf(file,"\t");
E 45
I 45
			fprintf(file,";;\t");
E 45
			cp = p_cdname(cp, msg, file);
E 7
E 3
			if (cp == NULL)
				return;
D 2
			printf(", type = %s", p_type(ntohs(*(u_short *)cp)));
E 2
I 2
D 7
			printf(", type = %s", p_type(getshort(cp)));
E 7
I 7
D 24
			fprintf(file,", type = %s", p_type(getshort(cp)));
E 24
I 24
D 42
			fprintf(file,", type = %s", p_type(_getshort(cp)));
E 42
I 42
D 45
			fprintf(file,", type = %s", __p_type(_getshort(cp)));
E 42
E 24
E 7
E 2
			cp += sizeof(u_short);
D 2
			printf(", class = %s\n\n", p_class(ntohs(*(u_short *)cp)));
E 2
I 2
D 7
			printf(", class = %s\n\n", p_class(getshort(cp)));
E 7
I 7
D 24
			fprintf(file,", class = %s\n\n", p_class(getshort(cp)));
E 24
I 24
D 40
			fprintf(file,", class = %s\n\n", p_class(_getshort(cp)));
E 40
I 40
			fprintf(file,
D 42
			    ", class = %s\n\n", p_class(_getshort(cp)));
E 42
I 42
			    ", class = %s\n\n", __p_class(_getshort(cp)));
E 42
E 40
E 24
E 7
E 2
			cp += sizeof(u_short);
E 45
I 45
			if ((!_res.pfcode) || (_res.pfcode & RES_PRF_QUES))
				fprintf(file, ", type = %s",
					__p_type(_getshort(cp)));
			cp += sizeof(u_int16_t);
			if ((!_res.pfcode) || (_res.pfcode & RES_PRF_QUES))
				fprintf(file, ", class = %s\n\n",
					__p_class(_getshort(cp)));
			cp += sizeof(u_int16_t);
E 45
		}
	}
	/*
	 * Print authoritative answer records
	 */
D 45
	if (n = ntohs(hp->ancount)) {
D 7
		printf("ANSWERS:\n");
E 7
I 7
		fprintf(file,"ANSWERS:\n");
E 7
		while (--n >= 0) {
D 7
			printf("\t");
D 3
			cp = p_rr(cp, buf);
E 3
I 3
			cp = p_rr(cp, msg);
E 7
I 7
			fprintf(file,"\t");
			cp = p_rr(cp, msg, file);
E 7
E 3
			if (cp == NULL)
				return;
		}
	}
E 45
I 45
	cp = do_rrset(msg, cp, hp->ancount, RES_PRF_ANS, file,
		      ";; ANSWERS:\n");
	if (cp == NULL)
		return;

E 45
	/*
	 * print name server records
	 */
D 45
	if (n = ntohs(hp->nscount)) {
D 7
		printf("NAME SERVERS:\n");
E 7
I 7
		fprintf(file,"NAME SERVERS:\n");
E 7
		while (--n >= 0) {
D 7
			printf("\t");
D 3
			cp = p_rr(cp, buf);
E 3
I 3
			cp = p_rr(cp, msg);
E 7
I 7
			fprintf(file,"\t");
			cp = p_rr(cp, msg, file);
E 7
E 3
			if (cp == NULL)
				return;
		}
	}
E 45
I 45
	cp = do_rrset(msg, cp, hp->nscount, RES_PRF_AUTH, file,
		      ";; AUTHORITY RECORDS:\n");
	if (!cp)
		return;

E 45
	/*
	 * print additional records
	 */
D 45
	if (n = ntohs(hp->arcount)) {
D 7
		printf("ADDITIONAL RECORDS:\n");
E 7
I 7
		fprintf(file,"ADDITIONAL RECORDS:\n");
E 7
		while (--n >= 0) {
D 7
			printf("\t");
D 3
			cp = p_rr(cp, buf);
E 3
I 3
			cp = p_rr(cp, msg);
E 7
I 7
			fprintf(file,"\t");
			cp = p_rr(cp, msg, file);
E 7
E 3
			if (cp == NULL)
				return;
		}
	}
E 45
I 45
	cp = do_rrset(msg, cp, hp->arcount, RES_PRF_ADD, file,
		      ";; ADDITIONAL RECORDS:\n");
	if (!cp)
		return;
E 45
I 10
D 33
#endif
E 33
E 10
}

D 40
char *
E 40
I 40
D 45
static char *
E 45
I 45
char *
E 45
E 40
D 3
p_cdname(cp, buf)
	char *cp, *buf;
E 3
I 3
D 7
p_cdname(cp, msg)
E 7
I 7
p_cdname(cp, msg, file)
E 7
	char *cp, *msg;
I 7
	FILE *file;
E 7
E 3
{
I 10
D 33
#ifdef DEBUG
E 33
E 10
	char name[MAXDNAME];
	int n;

D 3
	if ((n = dn_expand(buf, cp, name, sizeof(name))) < 0)
E 3
I 3
D 18
	if ((n = dn_expand(msg, cp, name, sizeof(name))) < 0)
E 18
I 18
D 19
	if ((n = dn_expand(msg, 512, cp, name, sizeof(name))) < 0)
E 19
I 19
D 41
	if ((n = dn_expand(msg, msg + 512, cp, name, sizeof(name))) < 0)
E 41
I 41
D 45
	if ((n = dn_expand((u_char *)msg, (u_char *)msg + 512, (u_char *)cp,
	    (u_char *)name, sizeof(name))) < 0)
E 45
I 45
	if ((n = dn_expand((u_char *)msg, (u_char *)msg + MAXCDNAME,
	    (u_char *)cp, (u_char *)name, sizeof(name))) < 0)
E 45
E 41
E 19
E 18
E 3
		return (NULL);
I 45
	if (name[0] == '\0')
		putc('.', file);
	else
		fputs(name, file);
	return (cp + n);
}

char *
p_fqname(cp, msg, file)
	char *cp, *msg;
	FILE *file;
{
	char name[MAXDNAME];
	int n, len;

	if ((n = dn_expand((u_char *)msg, (u_char *)msg + MAXCDNAME,
	    (u_char *)cp, (u_char *)name, sizeof(name))) < 0)
		return (NULL);
E 45
	if (name[0] == '\0') {
D 45
		name[0] = '.';
		name[1] = '\0';
E 45
I 45
		putc('.', file);
	} else {
		fputs(name, file);
		if (name[strlen(name) - 1] != '.')
			putc('.', file);
E 45
	}
D 7
	fputs(name, stdout);
E 7
I 7
D 45
	fputs(name, file);
E 45
E 7
	return (cp + n);
I 10
D 33
#endif
E 33
E 10
}

/*
 * Print resource record fields in human readable form.
 */
D 40
char *
E 40
I 40
D 45
static char *
E 45
I 45
char *
E 45
E 40
D 3
p_rr(cp, buf)
	char *cp, *buf;
E 3
I 3
D 7
p_rr(cp, msg)
E 7
I 7
p_rr(cp, msg, file)
E 7
	char *cp, *msg;
I 7
	FILE *file;
E 7
E 3
{
I 10
D 33
#ifdef DEBUG
E 33
E 10
	int type, class, dlen, n, c;
	struct in_addr inaddr;
D 36
	char *cp1;
E 36
I 36
D 37
	char *cp1, cp2;
E 37
I 37
	char *cp1, *cp2;
I 45
	u_int32_t tmpttl, t;
	int lcnt;
E 45
E 37
E 36

D 3
	if ((cp = p_cdname(cp, buf)) == NULL)
E 3
I 3
D 7
	if ((cp = p_cdname(cp, msg)) == NULL)
E 7
I 7
D 45
	if ((cp = p_cdname(cp, msg, file)) == NULL)
E 45
I 45
	if ((cp = p_fqname(cp, msg, file)) == NULL)
E 45
E 7
E 3
		return (NULL);			/* compression error */
D 2
	printf("\n\ttype = %s", p_type(type = ntohs(*(u_short *)cp)));
E 2
I 2
D 7
	printf("\n\ttype = %s", p_type(type = getshort(cp)));
E 7
I 7
D 24
	fprintf(file,"\n\ttype = %s", p_type(type = getshort(cp)));
E 24
I 24
D 42
	fprintf(file,"\n\ttype = %s", p_type(type = _getshort(cp)));
E 42
I 42
D 45
	fprintf(file,"\n\ttype = %s", __p_type(type = _getshort(cp)));
E 42
E 24
E 7
E 2
	cp += sizeof(u_short);
D 2
	printf(", class = %s", p_class(class = ntohs(*(u_short *)cp)));
E 2
I 2
D 7
	printf(", class = %s", p_class(class = getshort(cp)));
E 7
I 7
D 24
	fprintf(file,", class = %s", p_class(class = getshort(cp)));
E 24
I 24
D 42
	fprintf(file,", class = %s", p_class(class = _getshort(cp)));
E 42
I 42
	fprintf(file,", class = %s", __p_class(class = _getshort(cp)));
E 42
E 24
E 7
E 2
	cp += sizeof(u_short);
D 2
	printf(", ttl = %d", ntohl(*(u_int *)cp));
E 2
I 2
D 7
	printf(", ttl = %ld", getlong(cp));
E 7
I 7
D 8
	fprintf(file,", ttl = %ld", getlong(cp));
E 8
I 8
D 24
	fprintf(file,", ttl = %u", getlong(cp));
E 24
I 24
D 31
	fprintf(file,", ttl = %u", _getlong(cp));
E 31
I 31
D 33
	fprintf(file,", ttl = %s", p_time(cp));
E 33
I 33
D 44
	fprintf(file,", ttl = %s", p_time(_getlong(cp)));
E 44
I 44
	fprintf(file,", ttl = %s", __p_time(_getlong(cp)));
E 44
E 33
E 31
E 24
E 8
E 7
E 2
	cp += sizeof(u_long);
D 2
	printf(", dlen = %d\n", dlen = ntohs(*(u_short *)cp));
E 2
I 2
D 7
	printf(", dlen = %d\n", dlen = getshort(cp));
E 7
I 7
D 24
	fprintf(file,", dlen = %d\n", dlen = getshort(cp));
E 24
I 24
	fprintf(file,", dlen = %d\n", dlen = _getshort(cp));
E 24
E 7
E 2
	cp += sizeof(u_short);
E 45
I 45
	type = _getshort(cp);
	cp += sizeof(u_int16_t);
	class = _getshort(cp);
	cp += sizeof(u_int16_t);
	tmpttl = _getlong(cp);
	cp += sizeof(u_int32_t);
	dlen = _getshort(cp);
	cp += sizeof(u_int16_t);
E 45
	cp1 = cp;
I 45
	if ((!_res.pfcode) || (_res.pfcode & RES_PRF_TTLID))
		fprintf(file, "\t%lu", tmpttl);
	if ((!_res.pfcode) || (_res.pfcode & RES_PRF_CLASS))
		fprintf(file, "\t%s", __p_class(class));
	fprintf(file, "\t%s", __p_type(type));
E 45
	/*
	 * Print type specific data, if appropriate
	 */
	switch (type) {
	case T_A:
		switch (class) {
		case C_IN:
I 36
		case C_HS:
E 36
D 2
			inaddr.s_addr = *(u_long *)cp;
E 2
I 2
			bcopy(cp, (char *)&inaddr, sizeof(inaddr));
E 2
			if (dlen == 4) {
D 7
				printf("\tinternet address = %s\n",
E 7
I 7
D 45
				fprintf(file,"\tinternet address = %s\n",
E 7
					inet_ntoa(inaddr));
E 45
I 45
				fprintf(file,"\t%s", inet_ntoa(inaddr));
E 45
				cp += dlen;
			} else if (dlen == 7) {
D 7
				printf("\tinternet address = %s",
E 7
I 7
D 45
				fprintf(file,"\tinternet address = %s",
E 7
					inet_ntoa(inaddr));
D 7
				printf(", protocol = %d", cp[4]);
				printf(", port = %d\n",
E 7
I 7
				fprintf(file,", protocol = %d", cp[4]);
				fprintf(file,", port = %d\n",
E 7
					(cp[5] << 8) + cp[6]);
				cp += dlen;
E 45
I 45
				char *address;
				u_char protocol;
				u_short port;

				address = inet_ntoa(inaddr);
				cp += sizeof(inaddr);
				protocol = *(u_char*)cp;
				cp += sizeof(u_char);
				port = _getshort(cp);
				cp += sizeof(u_int16_t);
				fprintf(file, "\t%s\t; proto %d, port %d",
					address, protocol, port);
E 45
			}
			break;
I 21
		default:
			cp += dlen;
E 21
		}
		break;
	case T_CNAME:
	case T_MB:
I 16
D 33
#ifdef OLDRR
E 16
	case T_MD:
	case T_MF:
I 16
#endif /* OLDRR */
E 33
E 16
	case T_MG:
	case T_MR:
	case T_NS:
	case T_PTR:
D 7
		printf("\tdomain name = ");
D 3
		cp = p_cdname(cp, buf);
E 3
I 3
		cp = p_cdname(cp, msg);
E 3
		printf("\n");
E 7
I 7
D 45
		fprintf(file,"\tdomain name = ");
		cp = p_cdname(cp, msg, file);
		fprintf(file,"\n");
E 45
I 45
		putc('\t', file);
		cp = p_fqname(cp, msg, file);
E 45
E 7
		break;

	case T_HINFO:
		if (n = *cp++) {
D 7
			printf("\tCPU=%.*s\n", n, cp);
E 7
I 7
D 45
			fprintf(file,"\tCPU=%.*s\n", n, cp);
E 45
I 45
			fprintf(file,"\t%.*s", n, cp);
E 45
E 7
			cp += n;
		}
		if (n = *cp++) {
D 7
			printf("\tOS=%.*s\n", n, cp);
E 7
I 7
D 45
			fprintf(file,"\tOS=%.*s\n", n, cp);
E 45
I 45
			fprintf(file,"\t%.*s", n, cp);
E 45
E 7
			cp += n;
		}
		break;

	case T_SOA:
D 7
		printf("\torigin = ");
D 3
		cp = p_cdname(cp, buf);
E 3
I 3
		cp = p_cdname(cp, msg);
E 3
		printf("\n\tmail addr = ");
D 3
		cp = p_cdname(cp, buf);
E 3
I 3
		cp = p_cdname(cp, msg);
E 3
D 2
		printf("\n\tserial=%d", ntohl(*(u_long *)cp));
E 2
I 2
		printf("\n\tserial=%ld", getlong(cp));
E 7
I 7
D 45
		fprintf(file,"\torigin = ");
		cp = p_cdname(cp, msg, file);
		fprintf(file,"\n\tmail addr = ");
		cp = p_cdname(cp, msg, file);
D 24
		fprintf(file,"\n\tserial=%ld", getlong(cp));
E 24
I 24
D 33
		fprintf(file,"\n\tserial=%ld", _getlong(cp));
E 33
I 33
		fprintf(file,"\n\tserial = %ld", _getlong(cp));
E 33
E 24
E 7
E 2
		cp += sizeof(u_long);
D 2
		printf(", refresh=%d", ntohl(*(u_long *)cp));
E 2
I 2
D 7
		printf(", refresh=%ld", getlong(cp));
E 7
I 7
D 24
		fprintf(file,", refresh=%ld", getlong(cp));
E 24
I 24
D 31
		fprintf(file,", refresh=%ld", _getlong(cp));
E 31
I 31
D 33
		fprintf(file,", refresh=%s", p_time(cp));
E 33
I 33
D 44
		fprintf(file,"\n\trefresh = %s", p_time(_getlong(cp)));
E 44
I 44
		fprintf(file,"\n\trefresh = %s", __p_time(_getlong(cp)));
E 44
E 33
E 31
E 24
E 7
E 2
		cp += sizeof(u_long);
D 2
		printf(", retry=%d", ntohl(*(u_long *)cp));
E 2
I 2
D 7
		printf(", retry=%ld", getlong(cp));
E 7
I 7
D 24
		fprintf(file,", retry=%ld", getlong(cp));
E 24
I 24
D 31
		fprintf(file,", retry=%ld", _getlong(cp));
E 31
I 31
D 33
		fprintf(file,", retry=%s", p_time(cp));
E 33
I 33
D 44
		fprintf(file,"\n\tretry = %s", p_time(_getlong(cp)));
E 44
I 44
		fprintf(file,"\n\tretry = %s", __p_time(_getlong(cp)));
E 44
E 33
E 31
E 24
E 7
E 2
		cp += sizeof(u_long);
D 2
		printf(", expire=%d", ntohl(*(u_long *)cp));
E 2
I 2
D 7
		printf(", expire=%ld", getlong(cp));
E 7
I 7
D 24
		fprintf(file,", expire=%ld", getlong(cp));
E 24
I 24
D 31
		fprintf(file,", expire=%ld", _getlong(cp));
E 31
I 31
D 33
		fprintf(file,", expire=%s", p_time(cp));
E 33
I 33
D 44
		fprintf(file,"\n\texpire = %s", p_time(_getlong(cp)));
E 44
I 44
		fprintf(file,"\n\texpire = %s", __p_time(_getlong(cp)));
E 44
E 33
E 31
E 24
E 7
E 2
		cp += sizeof(u_long);
D 2
		printf(", min=%d\n", ntohl(*(u_long *)cp));
E 2
I 2
D 7
		printf(", min=%ld\n", getlong(cp));
E 7
I 7
D 24
		fprintf(file,", min=%ld\n", getlong(cp));
E 24
I 24
D 31
		fprintf(file,", min=%ld\n", _getlong(cp));
E 31
I 31
D 33
		fprintf(file,", min=%s\n", p_time(cp));
E 33
I 33
D 44
		fprintf(file,"\n\tmin = %s\n", p_time(_getlong(cp)));
E 44
I 44
		fprintf(file,"\n\tmin = %s\n", __p_time(_getlong(cp)));
E 44
E 33
E 31
E 24
E 7
E 2
		cp += sizeof(u_long);
E 45
I 45
		putc('\t', file);
		cp = p_fqname(cp, msg, file);	/* origin */
		putc(' ', file);
		cp = p_fqname(cp, msg, file);	/* mail addr */
		fputs(" (\n", file);
		t = _getlong(cp);  cp += sizeof(u_int32_t);
		fprintf(file,"\t\t\t%lu\t; serial\n", t);
		t = _getlong(cp);  cp += sizeof(u_int32_t);
		fprintf(file,"\t\t\t%lu\t; refresh (%s)\n", t, __p_time(t));
		t = _getlong(cp);  cp += sizeof(u_int32_t);
		fprintf(file,"\t\t\t%lu\t; retry (%s)\n", t, __p_time(t));
		t = _getlong(cp);  cp += sizeof(u_int32_t);
		fprintf(file,"\t\t\t%lu\t; expire (%s)\n", t, __p_time(t));
		t = _getlong(cp);  cp += sizeof(u_int32_t);
		fprintf(file,"\t\t\t%lu )\t; minimum (%s)", t, __p_time(t));
E 45
I 3
		break;

I 15
	case T_MX:
D 16
		fprintf(file,"\tname = ");
E 16
I 16
D 24
		fprintf(file,"\tpreference = %ld,",getshort(cp));
E 24
I 24
D 45
		fprintf(file,"\tpreference = %ld,",_getshort(cp));
E 24
		cp += sizeof(u_short);
		fprintf(file," name = ");
E 16
		cp = p_cdname(cp, msg, file);
E 45
I 45
		fprintf(file,"\t%d ", _getshort(cp));
		cp += sizeof(u_int16_t);
		cp = p_fqname(cp, msg, file);
E 45
D 16
		fprintf(file,", preference = %ld",getlong(cp));
		cp += sizeof(u_long);
E 16
		break;

I 34
D 36
	case T_TXT:
		if (n = *cp++) {
			fprintf(file, "\tTEXT=%.*s\n", n, cp);
			cp += n;
		} else
			fprintf(file, "\tTEXT=\"\"\n");
		break;
E 36
I 36
  	case T_TXT:
		(void) fputs("\t\"", file);
		cp2 = cp1 + dlen;
		while (cp < cp2) {
			if (n = (unsigned char) *cp++) {
				for (c = n; c > 0 && cp < cp2; c--)
					if (*cp == '\n') {
					    (void) putc('\\', file);
					    (void) putc(*cp++, file);
					} else
					    (void) putc(*cp++, file);
			}
		}
D 45
		(void) fputs("\"\n", file);
E 45
I 45
		putc('"', file);
E 45
  		break;
E 36

E 34
E 15
	case T_MINFO:
D 7
		printf("\trequests = ");
		cp = p_cdname(cp, msg);
		printf("\n\terrors = ");
		cp = p_cdname(cp, msg);
E 7
I 7
D 45
		fprintf(file,"\trequests = ");
		cp = p_cdname(cp, msg, file);
		fprintf(file,"\n\terrors = ");
		cp = p_cdname(cp, msg, file);
E 45
I 45
	case T_RP:
		putc('\t', file);
		cp = p_fqname(cp, msg, file);
		putc(' ', file);
		cp = p_fqname(cp, msg, file);
E 45
E 7
E 3
		break;

	case T_UINFO:
I 33
D 34
	case T_TXT:
E 34
E 33
D 7
		printf("\t%s\n", cp);
E 7
I 7
D 45
		fprintf(file,"\t%s\n", cp);
E 45
I 45
		putc('\t', file);
		fputs(cp, file);
E 45
E 7
		cp += dlen;
		break;

	case T_UID:
	case T_GID:
		if (dlen == 4) {
D 2
			printf("\t%d\n", ntohl(*(int *)cp));
E 2
I 2
D 7
			printf("\t%ld\n", getlong(cp));
E 7
I 7
D 24
			fprintf(file,"\t%ld\n", getlong(cp));
E 24
I 24
D 45
			fprintf(file,"\t%ld\n", _getlong(cp));
E 24
E 7
E 2
			cp += sizeof(int);
E 45
I 45
			fprintf(file,"\t%u", _getlong(cp));
			cp += sizeof(int32_t);
E 45
		}
		break;

	case T_WKS:
D 45
		if (dlen < sizeof(u_long) + 1)
E 45
I 45
		if (dlen < sizeof(u_int32_t) + 1)
E 45
			break;
D 2
		inaddr.s_addr = *(u_long *)cp;
E 2
I 2
		bcopy(cp, (char *)&inaddr, sizeof(inaddr));
E 2
D 45
		cp += sizeof(u_long);
D 7
		printf("\tinternet address = %s, protocol = %d\n\t",
E 7
I 7
		fprintf(file,"\tinternet address = %s, protocol = %d\n\t",
E 7
			inet_ntoa(inaddr), *cp++);
E 45
I 45
		cp += sizeof(u_int32_t);
		fprintf(file, "\t%s %s ( ",
			inet_ntoa(inaddr),
			deproto((int) *cp));
		cp += sizeof(u_char);
E 45
		n = 0;
I 45
		lcnt = 0;
E 45
		while (cp < cp1 + dlen) {
			c = *cp++;
			do {
D 9
				if (c & 1)
E 9
I 9
D 45
 				if (c & 0200)
E 9
D 7
					printf(" %d", n);
E 7
I 7
					fprintf(file," %d", n);
E 45
I 45
 				if (c & 0200) {
					if (lcnt == 0) {
						fputs("\n\t\t\t", file);
						lcnt = 5;
					}
					fputs(dewks(n), file);
					putc(' ', file);
					lcnt--;
				}
E 45
E 7
D 9
				c >>= 1;
E 9
I 9
 				c <<= 1;
E 9
			} while (++n & 07);
		}
D 7
		putchar('\n');
E 7
I 7
D 45
		putc('\n',file);
E 45
I 45
		putc(')', file);
E 45
E 7
		break;

I 22
#ifdef ALLOW_T_UNSPEC
D 26
        case T_UNSPEC:
                {
                        int NumBytes = 8;
                        char *DataPtr;
                        int i;
E 26
I 26
	case T_UNSPEC:
		{
			int NumBytes = 8;
			char *DataPtr;
			int i;
E 26

D 26
                        if (dlen < NumBytes) NumBytes = dlen;
                        fprintf(file, "\tFirst %d bytes of hex data:",
                                NumBytes);
                        for (i = 0, DataPtr = cp; i < NumBytes; i++, DataPtr++)
                                fprintf(file, " %x", *DataPtr);
                        fputs("\n", file);
                        cp += dlen;
                }
                break;
#endif ALLOW_T_UNSPEC
E 26
I 26
			if (dlen < NumBytes) NumBytes = dlen;
			fprintf(file, "\tFirst %d bytes of hex data:",
				NumBytes);
			for (i = 0, DataPtr = cp; i < NumBytes; i++, DataPtr++)
				fprintf(file, " %x", *DataPtr);
D 45
			fputs("\n", file);
E 45
			cp += dlen;
		}
		break;
#endif /* ALLOW_T_UNSPEC */
E 26

E 22
	default:
D 7
		printf("\t???\n");
E 7
I 7
D 45
		fprintf(file,"\t???\n");
E 45
I 45
		fprintf(file,"\t?%d?", type);
E 45
E 7
		cp += dlen;
	}
D 35
	if (cp != cp1 + dlen)
E 35
I 35
D 45
	if (cp != cp1 + dlen) {
E 35
D 7
		printf("packet size error (%#x != %#x)\n", cp, cp1+dlen);
	printf("\n");
E 7
I 7
		fprintf(file,"packet size error (%#x != %#x)\n", cp, cp1+dlen);
E 45
I 45
#if 0
	fprintf(file, "\t; dlen=%d, ttl %s\n", dlen, __p_time(tmpttl));
#else
	putc('\n', file);
#endif
	if (cp - cp1 != dlen) {
		fprintf(file,";; packet size error (found %d, dlen was %d)\n",
			cp - cp1, dlen);
E 45
I 35
		cp = NULL;
	}
E 35
D 45
	fprintf(file,"\n");
E 45
E 7
	return (cp);
I 10
D 33
#endif
E 33
E 10
}

D 31
static	char nbuf[20];
E 31
I 31
static	char nbuf[40];
E 31
D 29
extern	char *sprintf();
E 29

/*
 * Return a string for the type
 */
D 40
char *
E 40
I 40
D 42
static char *
E 40
p_type(type)
E 42
I 42
char *
__p_type(type)
E 42
	int type;
{
D 10

E 10
I 10
D 14
#ifdef DEBUG
E 14
E 10
	switch (type) {
	case T_A:
		return("A");
	case T_NS:		/* authoritative server */
		return("NS");
I 16
D 33
#ifdef OLDRR
E 16
	case T_MD:		/* mail destination */
		return("MD");
	case T_MF:		/* mail forwarder */
		return("MF");
I 16
#endif /* OLDRR */
E 33
E 16
D 34
	case T_CNAME:		/* connonical name */
E 34
I 34
	case T_CNAME:		/* canonical name */
E 34
		return("CNAME");
	case T_SOA:		/* start of authority zone */
		return("SOA");
	case T_MB:		/* mailbox domain name */
		return("MB");
	case T_MG:		/* mail group member */
		return("MG");
I 15
D 33
	case T_MX:		/* mail routing info */
		return("MX");
E 33
E 15
	case T_MR:		/* mail rename name */
		return("MR");
	case T_NULL:		/* null resource record */
		return("NULL");
	case T_WKS:		/* well known service */
		return("WKS");
	case T_PTR:		/* domain name pointer */
		return("PTR");
	case T_HINFO:		/* host information */
		return("HINFO");
	case T_MINFO:		/* mailbox information */
		return("MINFO");
I 33
	case T_MX:		/* mail routing info */
		return("MX");
	case T_TXT:		/* text */
		return("TXT");
I 45
	case T_RP:		/* responsible person */
		return("RP");
E 45
E 33
	case T_AXFR:		/* zone transfer */
		return("AXFR");
	case T_MAILB:		/* mail box */
		return("MAILB");
	case T_MAILA:		/* mail address */
		return("MAILA");
	case T_ANY:		/* matches any type */
		return("ANY");
	case T_UINFO:
		return("UINFO");
	case T_UID:
		return("UID");
	case T_GID:
		return("GID");
I 22
#ifdef ALLOW_T_UNSPEC
D 26
        case T_UNSPEC:
                return("UNSPEC");
#endif ALLOW_T_UNSPEC
E 26
I 26
	case T_UNSPEC:
		return("UNSPEC");
#endif /* ALLOW_T_UNSPEC */
E 26
E 22
	default:
D 29
		return (sprintf(nbuf, "%d", type));
E 29
I 29
		(void)sprintf(nbuf, "%d", type);
		return(nbuf);
E 29
	}
I 10
D 14
#endif
E 14
E 10
}

/*
 * Return a mnemonic for class
 */
D 40
char *
E 40
I 40
D 42
static char *
E 40
p_class(class)
E 42
I 42
char *
__p_class(class)
E 42
	int class;
{
I 10
D 14
#ifdef DEBUG
E 14
E 10

	switch (class) {
	case C_IN:		/* internet class */
		return("IN");
I 33
D 34
	case C_HS:		/* internet class */
		return("HESIOD");
E 34
I 34
	case C_HS:		/* hesiod class */
		return("HS");
E 34
E 33
D 13
	case C_CS:		/* csnet class */
		return("CS");
E 13
	case C_ANY:		/* matches any class */
		return("ANY");
	default:
D 29
		return (sprintf(nbuf, "%d", class));
E 29
I 29
		(void)sprintf(nbuf, "%d", class);
		return(nbuf);
E 29
	}
I 31
}

/*
I 45
 * Return a mnemonic for an option
 */
static char *
p_option(option)
	u_int32_t option;
{
	switch (option) {
	case RES_INIT:		return "init";
	case RES_DEBUG:		return "debug";
	case RES_AAONLY:	return "aaonly";
	case RES_USEVC:		return "usevc";
	case RES_PRIMARY:	return "primry";
	case RES_IGNTC:		return "igntc";
	case RES_RECURSE:	return "recurs";
	case RES_DEFNAMES:	return "defnam";
	case RES_STAYOPEN:	return "styopn";
	case RES_DNSRCH:	return "dnsrch";
	default:		sprintf(nbuf, "?0x%x?", option); return nbuf;
	}
}

/*
E 45
 * Return a mnemonic for a time to live
 */
D 34
char
*p_time(value)
E 34
I 34
D 40
char *
E 40
I 40
D 44
static char *
E 40
p_time(value)
E 44
I 44
char *
__p_time(value)
E 44
E 34
D 45
	u_long value;
E 45
I 45
	u_int32_t value;
E 45
{
D 45
	int secs, mins, hours;
E 45
I 45
	int secs, mins, hours, days;
E 45
	register char *p;
I 38

	if (value == 0) {
		strcpy(nbuf, "0 secs");
		return(nbuf);
	}
E 38

	secs = value % 60;
	value /= 60;
	mins = value % 60;
	value /= 60;
	hours = value % 24;
	value /= 24;
I 45
	days = value;
	value = 0;
E 45

#define	PLURALIZE(x)	x, (x == 1) ? "" : "s"
	p = nbuf;
D 45
	if (value) {
		(void)sprintf(p, "%d day%s", PLURALIZE(value));
E 45
I 45
	if (days) {
		(void)sprintf(p, "%d day%s", PLURALIZE(days));
E 45
		while (*++p);
	}
	if (hours) {
D 34
		if (p != nbuf)
E 34
I 34
D 45
		if (value)
E 45
I 45
		if (days)
E 45
E 34
			*p++ = ' ';
		(void)sprintf(p, "%d hour%s", PLURALIZE(hours));
		while (*++p);
	}
	if (mins) {
D 34
		if (p != nbuf)
E 34
I 34
D 45
		if (value || hours)
E 45
I 45
		if (days || hours)
E 45
E 34
			*p++ = ' ';
		(void)sprintf(p, "%d min%s", PLURALIZE(mins));
		while (*++p);
	}
D 34
	if (secs) {
		if (p != nbuf)
E 34
I 34
D 45
	if (secs || ! (value || hours || mins)) {
		if (value || hours || mins)
E 45
I 45
	if (secs || ! (days || hours || mins)) {
		if (days || hours || mins)
E 45
E 34
			*p++ = ' ';
		(void)sprintf(p, "%d sec%s", PLURALIZE(secs));
D 34
		while (*++p);
E 34
	}
	return(nbuf);
E 31
I 10
D 14
#endif
E 14
E 10
}
I 7
D 10

E 10
E 7
E 1
