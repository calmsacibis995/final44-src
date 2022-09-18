h20984
s 00000/00000/00007
d D 8.1 93/08/14 10:08:48 mckusick 5 4
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00002/00005
d D 5.3 93/08/13 15:13:47 elan 4 2
c Don't need tmac.ansp.
e
s 00000/00000/00007
d R 8.1 93/06/08 18:21:43 bostic 3 2
c 4.4BSD snapshot (revision 8.1)
e
s 00005/00023/00002
d D 5.2 93/06/08 18:21:40 bostic 2 1
c update, integrate
e
s 00025/00000/00000
d D 5.1 92/07/22 12:26:21 bostic 1 0
c date and time created 92/07/22 12:26:21 by bostic
e
u
U
t
T
I 1
D 2
#
LOCALS		= tutorial.ms tutorial.psc \
                  pmake.mansp pmake.psc \
		  Lst.mansp Lst.psc Makefile makefile tmac.ansp \
                  cctrl.8 customs.8 importquota.8 reginfo.1
E 2
I 2
#	%W% (Berkeley) %G%
E 2

D 2
SUBDIRS		= index ex1 ex2 customs
E 2
I 2
DIR=	psd/12.make
D 4
SRCS=	tmac.ansp tutorial.ms
MACROS=	-msU
E 4
I 4
SRCS=	tutorial.ms
MACROS=	-ms
E 4
E 2

D 2

tutorial.t	: index/tmac.index tutorial.ms 
	ditroff -Plw -ms -t $(.ALLSRC) > tut.temp
	index/index -Plw -t tut.temp > $(.TARGET)
	rm -f tut.temp

print 		: tutorial.t
	lpr -Plw -h -n tutorial.t

package		::
	if [ ! -d $(PKGDIR) ]; then
		mkdir $(PKGDIR)
	fi
	cp $(LOCALS) $(PKGDIR)
	for i in $(SUBDIRS); do
		(cd $i; $(MAKE) "PKGDIR=$(PKGDIR)/$i" package)
	done
E 2
I 2
.include <bsd.doc.mk>
E 2
E 1
