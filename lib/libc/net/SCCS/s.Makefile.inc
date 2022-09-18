h51632
s 00002/00002/00037
d D 8.2 93/09/05 21:34:40 mckusick 13 12
c link_addr should be linkaddr
e
s 00000/00000/00039
d D 8.1 93/06/04 12:49:21 bostic 12 10
c 4.4BSD snapshot (revision 8.1)
e
s 00000/00000/00039
d R 8.1 93/06/02 17:25:32 bostic 11 10
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00038
d D 5.9 93/03/09 01:58:28 torek 10 9
c fix oops in MLINKS for link_addr.3
e
s 00002/00001/00037
d D 5.8 93/03/02 17:50:56 bostic 9 8
c BSDI just gave us a link_addr man page
e
s 00003/00012/00035
d D 5.7 92/06/25 09:14:33 bostic 8 7
c break up machine dependent stuff
e
s 00001/00001/00046
d D 5.6 92/06/04 15:07:12 mckusick 7 5
c add support for luna68k from Omron
e
s 00001/00001/00046
d R 5.6 92/06/04 15:06:33 mckusick 6 5
c add support for luna68k from Omron
e
s 00001/00001/00046
d D 5.5 91/11/27 11:16:17 bostic 5 4
c link inet_aton to inet
e
s 00002/00000/00045
d D 5.4 91/09/06 18:04:02 ralph 4 3
c add mips
e
s 00003/00000/00042
d D 5.3 91/02/21 16:23:33 bostic 3 2
c make dn_skipname, fp_query, hostalias, p_cdname, p_class, p_query,
c p_rr, p_time, p_type, putlong and putshort hidden
e
s 00002/00002/00040
d D 5.2 91/02/21 14:10:25 bostic 2 1
c delete sethostfile(3)
e
s 00042/00000/00000
d D 5.1 90/06/23 16:23:22 bostic 1 0
c date and time created 90/06/23 16:23:22 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

D 8
# net sources
E 8
I 8
# machine-independent net sources
E 8
.PATH: ${.CURDIR}/${MACHINE}/net ${.CURDIR}/net

SRCS+=	gethostnamadr.c getnetbyaddr.c getnetbyname.c getnetent.c \
	getproto.c getprotoent.c getprotoname.c getservbyname.c \
	getservbyport.c getservent.c herror.c inet_addr.c inet_lnaof.c \
	inet_makeaddr.c inet_netof.c inet_network.c inet_ntoa.c \
	iso_addr.c linkaddr.c ns_addr.c ns_ntoa.c rcmd.c recv.c res_comp.c \
	res_debug.c res_init.c res_mkquery.c res_query.c res_send.c \
	send.c sethostent.c

D 7
.if   (${MACHINE} == "hp300")
E 7
I 7
D 8
.if   (${MACHINE} == "hp300" || ${MACHINE} == "luna68k")
E 7
SRCS+=	htonl.s htons.s ntohl.s ntohs.s
.elif (${MACHINE} == "i386")
SRCS+=	htonl.s htons.s ntohl.s ntohs.s
I 4
.elif (${MACHINE} == "mips")
SRCS+=	htonl.s htons.s
E 4
.elif (${MACHINE} == "tahoe")
SRCS+=	htonl.s htons.s ntohl.s ntohs.s
.elif (${MACHINE} == "vax")
SRCS+=	htonl.s htons.s ntohl.s ntohs.s
.endif
E 8
I 8
# machine-dependent net sources
.include "${.CURDIR}/${MACHINE}/net/Makefile.inc"
E 8

MAN3+=	byteorder.0 gethostbyname.0 getnetent.0 getprotoent.0 getservent.0 \
D 9
	inet.0 ns.0 rcmd.0 resolver.0 \
E 9
I 9
D 13
	inet.0 link_addr.0 ns.0 rcmd.0 resolver.0 \
E 13
I 13
	inet.0 linkaddr.0 ns.0 rcmd.0 resolver.0 \
E 13
E 9

MLINKS+=byteorder.3 htonl.3 byteorder.3 htons.3 byteorder.3 ntohl.3 \
	byteorder.3 ntohs.3
MLINKS+=gethostbyname.3 endhostent.3 gethostbyname.3 gethostbyaddr.3 \
D 2
	gethostbyname.3 sethostent.3 gethostbyname.3 sethostfile.3 \
	gethostbyname.3 gethostent.3 gethostbyname.3 herror.3
E 2
I 2
	gethostbyname.3 sethostent.3 gethostbyname.3 gethostent.3 \
	gethostbyname.3 herror.3
E 2
MLINKS+=getnetent.3 endnetent.3 getnetent.3 getnetbyaddr.3 \
	getnetent.3 getnetbyname.3 getnetent.3 setnetent.3
MLINKS+=getprotoent.3 endprotoent.3 getprotoent.3 getprotobyname.3 \
	getprotoent.3 getprotobynumber.3 getprotoent.3 setprotoent.3
MLINKS+=getservent.3 endservent.3 getservent.3 getservbyname.3 \
	getservent.3 getservbyport.3 getservent.3 setservent.3
MLINKS+=inet.3 addr.3 inet.3 inet_addr.3 inet.3 inet_lnaof.3 \
	inet.3 inet_makeaddr.3 inet.3 inet_netof.3 inet.3 inet_network.3 \
D 5
	inet.3 inet_ntoa.3 inet.3 network.3 inet.3 ntoa.3
E 5
I 5
	inet.3 inet_ntoa.3 inet.3 network.3 inet.3 ntoa.3 inet.3 inet_aton.3
I 9
D 10
MLINKS+=link_addr.0 link_ntoa.0
E 10
I 10
D 13
MLINKS+=link_addr.3 link_ntoa.3
E 13
I 13
MLINKS+=linkaddr.3 linkntoa.3
E 13
E 10
E 9
E 5
MLINKS+=ns.3 ns_addr.3 ns.3 ns_ntoa.3
MLINKS+=rcmd.3 rresvport.3 rcmd.3 ruserok.3
I 3
MLINKS+=resolver.3 dn_comp.3 resolver.3 dn_expand.3 resolver.3 res_init.3 \
	resolver.3 res_mkquery.3 resolver.3 res_send.3 resolver.3 res_query.3 \
	resolver.3 res_search.3
E 3
E 1
