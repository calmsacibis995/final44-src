#
#	%M%	(CWI)	%I%	%E%
#
# BINDIR is the place where ideal will be installed
BINDIR = /usr/local
# DESTDIR is the destination where we want to move the thing (temporarily)
DESTDIR =
# LIBDIR is the place where we expect the the things we need and is
# is therefore hardwired in. Since it is all local, we use BINDIR as well
LIBDIR = ${BINDIR}/lib/ideal/lib
FILES = ARC Arc CIRCLE a arc arrow bar c circle dash dashed hole rect wavy

all: ${FILES}

install: all
	for i in ${FILES}; do\
	install -c -m 644 $$i ${DESTDIR}/${LIBDIR}/$$i; done

clean:

