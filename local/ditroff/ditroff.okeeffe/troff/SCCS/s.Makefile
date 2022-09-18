h01135
s 00005/00015/00112
d D 1.8 93/07/27 09:17:01 bostic 8 7
c checkpoint; Mike Karels left this checked out.
e
s 00012/00012/00115
d D 1.7 90/11/03 20:37:36 karels 7 6
c updates, new pathnames (still not right for man pages, no driver script
e
s 00118/00032/00009
d D 1.6 88/03/04 16:17:17 jaap 6 5
c cleaning up
e
s 00001/00001/00040
d D 1.5 86/08/14 22:58:12 jaap 5 4
c Just saving before munging
e
s 00001/00001/00040
d D 1.4 85/10/25 00:15:44 jaap 4 3
c We shouldn't forget to install grap!!!
e
s 00001/00001/00040
d D 1.3 85/10/02 17:15:30 jaap 3 2
c Added SUBDIR entry for tbl
e
s 00016/00017/00025
d D 1.2 85/07/18 16:57:41 jaap 2 1
c New makefile for V8 ditroff
e
s 00042/00000/00000
d D 1.1 85/07/18 11:15:28 jaap 1 0
c date and time created 85/07/18 11:15:28 by jaap
e
u
U
t
T
I 6
#######################################################################
E 6
I 1
D 2

E 2
#
#	%W%	(CWI)	%E%
#
D 2
CFLAGS=-O -DBSD42
E 2
I 2
D 6
CFLAGS= -DINCORE -g
E 2
DESTDIR=
BINDIR=/usr/local
D 3
SUBDIR= utilities devhar eqn pic ideal
E 3
I 3
D 4
SUBDIR= utilities devhar eqn pic ideal tbl
E 4
I 4
SUBDIR= utilities devhar eqn pic ideal grap tbl
E 4
E 3
TFILES=n1.o n2.o n3.o n4.o n5.o t6.o n7.o n8.o n9.o t10.o ni.o nii.o hytab.o suftab.o
E 6
I 6
# Makefile for ditroff and nroff
#
#######################################################################
E 6

D 6
all:	ditroff ${SUBDIR}
E 6
I 6
CFLAGS = -DINCORE -O
NFLAGS = -DNROFF -DSMALLER	# additional flags for nroff compile
E 6

D 6
ditroff:	${TFILES}
D 2
	${CC} -o ditroff ${CFLAGS} ${TFILES} 
E 2
I 2
D 5
	${CC} -o ditroff -n ${CFLAGS} ${TFILES} 
E 5
I 5
	${CC} -o ditroff  ${CFLAGS} ${TFILES} 
E 6
I 6
D 8
# other utilities maintained by this makefile
E 6
E 5
E 2

D 6
${SUBDIR}: /tmp
	cd $@; make ${MFLAGS}
E 6
I 6
UDIRS = utilities devhar eqn pic ideal grap tbl term devnver chem
E 6

E 8
D 2
n1.o:	tdef.h d.h v.h tw.h s.h ext.h ni.o
n2.o:	tdef.h d.h v.h tw.h s.h
n3.o:	tdef.h d.h v.h tw.h s.h
n4.o:	tdef.h d.h v.h tw.h s.h
n5.o:	tdef.h d.h v.h tw.h s.h
n6.o:	tdef.h d.h v.h tw.h s.h
t6.o:	tdef.h d.h v.h tw.h s.h dev.h ni.o
n7.o:	tdef.h d.h v.h tw.h s.h
n8.o:	tdef.h d.h v.h tw.h s.h
n9.o:	tdef.h d.h v.h tw.h s.h
n10.o:	tdef.h d.h v.h tw.h s.h
t10.o:	tdef.h d.h v.h tw.h s.h dev.h ni.o
ni.o:	tdef.h d.h v.h tw.h s.h
nii.o:	tdef.h d.h v.h tw.h s.h
E 2
I 2
D 6
n1.o:	tdef.h tw.h ext.h ni.o
n2.o:	tdef.h tw.h
n3.o:	tdef.h tw.h
n4.o:	tdef.h tw.h
n5.o:	tdef.h tw.h
n6.o:	tdef.h tw.h
t6.o:	tdef.h tw.h dev.h ni.o
n7.o:	tdef.h tw.h
n8.o:	tdef.h tw.h
n9.o:	tdef.h tw.h
n10.o:	tdef.h tw.h
t10.o:	tdef.h tw.h dev.h ni.o
ni.o:	tdef.h tw.h
nii.o:	tdef.h tw.h
E 6
I 6
# location to install final output
E 6
E 2

D 6
install:	all
	install -s ditroff ${DESTDIR}${BINDIR}/ditroff
	install -c -m 644 ditroff.1 ${DESTDIR}/usr/man/manl/ditroff.1
	for i in ${SUBDIR}; do \
		(cd $$i; make ${MFLAGS} DESTDIR=${DESTDIR} install); done
E 6
I 6
D 7
BINDIR = /usr/local/.code
LIBDIR = /usr/local/lib/ditroff
MANDIR = /usr/man/manl
E 7
I 7
BINDIR = /usr/local/bin
LIBDIR = /usr/local/libdata/ditroff_font
LIBXDIR = /usr/local/libexec
MANDIR = /usr/local/man/manl
E 7
E 6

D 6
clean:
	rm -f make.out *.o ditroff
	for i in ${SUBDIR}; do (cd $$i; make ${MFLAGS} clean); done
E 6
I 6
# the directories where the .o files are stored

N = nrobs
T = trobs

# the object files needed by nroff and troff

NOBS = $N/n1.o $N/n2.o $N/n3.o $N/n4.o $N/n5.o $N/n6.o $N/n7.o $N/n8.o \
       $N/n9.o $N/n10.o $N/ni.o $N/nii.o $N/hytab.o $N/suftab.o

TOBS = $T/n1.o $T/n2.o $T/n3.o $T/n4.o $T/n5.o $T/t6.o $T/n7.o $T/n8.o \
       $T/n9.o $T/t10.o $T/ni.o $T/nii.o $T/hytab.o $T/suftab.o

#######################################################################

D 7
all:	nroff ditroff $(UDIRS)
E 7
I 7
D 8
all:	troff_p $(UDIRS)
E 8
I 8
all:	troff_p
E 8
E 7

D 7
ditroff: $(T) $(TOBS)
	$(CC) $(CFLAGS) $(TOBS) -o ditroff
E 7
I 7
troff_p: $(T) $(TOBS)
	$(CC) $(CFLAGS) $(TOBS) -o troff_p -lcompat
E 7


nroff:	$(N) $(NOBS)
D 7
	$(CC) $(CFLAGS) $(NFLAGS) $(NOBS) -o nroff
E 7
I 7
	$(CC) $(CFLAGS) $(NFLAGS) $(NOBS) -o nroff -lcompat
E 7


$(T):
	mkdir $(T)

$(N):
	mkdir $(N)

$(LIBDIR):
	mkdir $(LIBDIR)
D 7
	mkdir $(LIBDIR)/font
E 7

install: all $(LIBDIR)
D 7
	install -c -s ditroff $(DESTDIR)$(BINDIR)/ditroff
	install -c -s nroff $(DESTDIR)$(BINDIR)/nroff
	install -c -m 664 ditroff.1 $(DESTDIR)$(MANDIR)/ditroff.1
E 7
I 7
D 8
	install -c -s ditroff $(DESTDIR)$(LIBXDIR)/troff_p
E 7
	for i in $(UDIRS); do (cd $$i; make $(MFLAGS) DESTDIR=${DESTDIR} install); done
I 7
#	install -c -s nroff $(DESTDIR)$(BINDIR)/nroff
E 8
I 8
	install -s ditroff $(DESTDIR)$(LIBXDIR)/troff_p
#	install -s nroff $(DESTDIR)$(BINDIR)/nroff
E 8
#	install -c -m 664 ditroff.1 $(DESTDIR)$(MANDIR)/ditroff.1
E 7

clean:  force
D 7
	rm -rf make.out ditroff nroff $N $T
E 7
I 7
	rm -rf make.out troff_p nroff $N $T
E 7
D 8
	for i in ${UDIRS}; do (cd $$i; make ${MFLAGS} clean); done
E 8

D 8
$(UDIRS): force
	cd $@; make $(MFLAGS)


E 8
# fake dependency to force a make
force:


#######################################################################
#
# The dependencies are divided into two parts: the
# first expresses the dependencies between the files
# and includes the fact that the .o files are in
# different directories than the .c files.  The 2nd
# part expresses no dependencies, but contains the
# rule for compiling the .c files into .o files.
#
# File Dependencies:
#

$T/n1.o:		n1.c  tdef.h tw.h ext.h $T/ni.o
$N/n1.o:		n1.c  tdef.h tw.h ext.h $N/ni.o

$T/n2.o  $N/n2.o:	n2.c  tdef.h tw.h
$T/n3.o  $N/n3.o:	n3.c  tdef.h tw.h
$T/n4.o  $N/n4.o:	n4.c  tdef.h tw.h
$T/n5.o  $N/n5.o:	n5.c  tdef.h tw.h

$T/t6.o:		t6.c  tdef.h tw.h dev.h $T/ni.o
$N/n6.o:		n6.c  tdef.h tw.h

$T/n7.o  $N/n7.o:	n7.c  tdef.h tw.h
$T/n8.o  $N/n8.o:	n8.c  tdef.h tw.h
$T/n9.o  $N/n9.o:	n9.c  tdef.h tw.h

$T/t10.o:		t10.c tdef.h tw.h dev.h $T/ni.o
$N/n10.o:		n10.c tdef.h tw.h

$T/ni.o  $N/ni.o:	ni.c  tdef.h tw.h
$T/nii.o $N/nii.o:	nii.c tdef.h tw.h
$T/hytab.o $N/hytab.o:	hytab.c
$T/suftab.o $N/suftab.o: suftab.c


#
# Generation Rule:
#  .oldestfile is older than everything, so
#  these rules will not be invoked unless
#  one of the above dependencies is.]
#

$(NOBS):  .oldestfile
D 8
	  $(CC) $(CFLAGS) $(NFLAGS) -c $@ `basename $@ .o`.c
E 8
I 8
	  $(CC) $(CFLAGS) $(NFLAGS) -c `basename $@ .o`.c
E 8
	mv `basename $@` nrobs

$(TOBS):  .oldestfile
D 8
	  $(CC) $(CFLAGS) -c $@ `basename $@ .o`.c
E 8
I 8
	  $(CC) $(CFLAGS) -c `basename $@ .o`.c
E 8
	mv `basename $@` trobs

.oldestfile:
	touch .oldestfile
E 6
E 1
