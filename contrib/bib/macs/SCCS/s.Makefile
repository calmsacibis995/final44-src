h39739
s 00003/00001/00071
d D 1.10 94/06/18 14:52:18 mckusick 11 9
c needs to install bibinc.publishers
e
s 00001/00000/00072
d R 1.10 94/06/18 11:41:15 mckusick 10 9
c add missing tibinc.publishers
e
s 00002/00002/00070
d D 1.9 93/06/07 23:36:15 bostic 9 8
c use the library passed from the parent Makefile
e
s 00036/00009/00036
d D 1.8 93/05/27 14:23:38 bostic 8 7
c new version from Dain Samples; checked in by TK
e
s 00001/00000/00044
d D 1.7 87/11/16 17:00:38 garrison 7 6
c added bib.compsurv
e
s 00001/00001/00043
d D 1.6 85/09/10 12:35:35 mckusick 6 5
c bmac moves to /usr/new/lib
e
s 00005/00001/00039
d D 1.5 85/06/25 20:12:50 kre 5 4
c make /usr/lib/bmac if it doesn't exist
e
s 00001/00001/00039
d D 1.4 85/06/11 12:48:37 garrison 4 3
c put keywords back in
e
s 00002/00002/00038
d D 1.3 85/06/11 12:46:54 garrison 3 2
c Changed install command to reduce problems with access rights.
e
s 00004/00000/00036
d D 1.2 84/01/21 09:36:05 rrh 2 1
c add stdafull
e
s 00036/00000/00000
d D 1.1 84/01/21 09:33:51 rrh 1 0
c date and time created 84/01/21 09:33:51 by rrh
e
u
U
t
T
I 2
#
D 3
#	%W%	(Berkeley)	%E%
E 3
I 3
D 4
#	@(#)Makefile	1.2	(Berkeley)	84/01/21
E 4
I 4
#	%W%	%E%
E 4
E 3
#
E 2
I 1
D 6
DEST	      = $(DESTDIR)/usr/lib/bmac
E 6
I 6
D 8
DEST	      = $(DESTDIR)/usr/new/lib/bmac
E 8
I 8
D 9
DEST	      = $(DESTDIR)/lib/bmac
E 9
I 9
DEST	      = $(DEST_LIB)/bmac
E 9
E 8
E 6

MAKEFILE      = Makefile

PRINT	      = vtroff

D 8
SRCS	      = bib.astro \
E 8
I 8
BIBSRCS	      = bib.astro \
E 8
I 7
		bib.compsurv \
E 7
		bib.foot \
		bib.hnf \
I 8
		bib.jrnl \
		bib.lib \
E 8
		bib.list \
I 8
		bib.llist \
E 8
		bib.opena \
		bib.openn \
		bib.spe \
		bib.spe2 \
		bib.stda \
I 2
		bib.stdafull \
E 2
		bib.stdn \
		bib.stdsn \
		bib.supn \
D 8
		bibinc.fullnames \
		bibinc.publishers \
		bibinc.shortnames \
E 8
I 8
		bibinc.names \
E 8
		bibmac.me \
		bmac.open \
		bmac.std \
D 8
		common
E 8
I 8
		common \
		macros.me \
		Makefile.e.g.
E 8

I 8
BIBINCS	      = bibinc.fullnames \
		bibinc.shortnames \
I 11
		bibinc.publishers \
E 11
		tibinc.fullnames \
		tibinc.shortnames

.PHONY: depend install clean all

E 8
all:;

clean:;

depend:;	@mkmf -f $(MAKEFILE)

D 5
install:;	@echo Installing $(SRCS) in $(DEST)
E 5
I 5
D 8
install:	$(DEST)
		@echo Installing $(SRCS) in $(DEST)
E 5
D 3
		@for i in $(SRCS); do cp $$i $(DEST)/$$i; done
E 3
I 3
		-for i in $(SRCS); do rm -f $(DEST)/$$i; cp $$i $(DEST)/$$i; done
E 8
I 8
D 11
install:	bibinc.fullnames bibinc.shortnames tibinc.fullnames tibinc.shortnames
E 11
I 11
install:	${BIBINCS}
E 11
		-mkdir $(DEST)
		-mkdir $(DEST)/bibmacs
		-mkdir $(DEST)/tibmacs
		cp bibinc.fullnames $(DEST)/bibmacs
		cp bibinc.shortnames $(DEST)/bibmacs
I 11
		cp bibinc.publishers $(DEST)/bibmacs
E 11
		cp tibinc.fullnames $(DEST)/tibmacs/bibinc.fullnames
		cp tibinc.shortnames $(DEST)/tibmacs/bibinc.shortnames
		cp bibinc.fulllocal $(DEST)/bibmacs
		cp bibinc.shortlocal $(DEST)/bibmacs
		cp bibinc.fulllocal $(DEST)/tibmacs
		cp bibinc.shortlocal $(DEST)/tibmacs
		@echo Installing in $(DEST)
D 9
		./Install $(DEST) $(BIBSRCS) ;
E 9
I 9
		csh -f ./Install $(DEST) $(BIBSRCS) ;
E 9
E 8
I 5

$(DEST):
		mkdir $(DEST)
E 5
E 3

I 8
bibinc.shortnames bibinc.fullnames: bibinc.names
	bibinc <bibinc.names

tibinc.fullnames tibinc.shortnames: bibinc.names
	bibinc -Tib -Tex <bibinc.names
	
E 8
update:;
E 1
