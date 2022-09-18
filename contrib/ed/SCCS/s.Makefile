h08052
s 00000/00000/00013
d D 8.1 93/05/31 15:02:40 bostic 4 3
c 4.4BSD snapshot (revision 8.1)
e
s 00000/00002/00013
d D 5.3 93/03/01 16:50:22 bostic 3 2
c NOTERMCAP is stupid
e
s 00001/00001/00014
d D 5.2 93/02/28 15:28:24 bostic 2 1
c some lint, some bug fixes, ^C handling improvements
c multiple access methods back in (yeeech!)
c new version from Rodney Ruddock (rodney@snowhite.cis.uoguelph.ca)
e
s 00015/00000/00000
d D 5.1 93/02/10 20:56:45 bostic 1 0
c date and time created 93/02/10 20:56:45 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

PROG=	ed
SRCS=	a.c add_line.c address.c bang.c c.c d.c e.c edhup.c equal.c f.c \
 	filename.c g.c get_line.c get_pattern.c i.c input_lines.c j.c k.c \
	l.c line_number.c m.c main.c p.c q.c r.c re.c rol.c sub.c search.c \
	t.c u.c w.c z.c

D 3
# -DNOTERMCAP and be added or substracted without harm
# see README for details and more flags.
E 3
D 2
CFLAGS+=-DBSD
E 2
I 2
CFLAGS+=-DBSD -DDBI
E 2
LDADD=	-ltermcap
DPADD=	${TERMLIB}

.include <bsd.prog.mk>
E 1
