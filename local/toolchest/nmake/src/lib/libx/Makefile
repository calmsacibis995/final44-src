/*
 * libx make
 */

.SOURCE.h : $(INCLUDEDIR)

HERSHEYDIR = "$(LIBDIR)/hershey"

.SOURCE : dir expr hash hershey misc

LIBX = expry.y exprl.l hash.3 hash.c hershey.c record.c stack.c strmatch.c

LIBXO = chash.c chash2.c

#if identifiers(/lib/libc.a,memcpy,memset) != 2 && identifiers(/lib/libc.a,bcopy,bzero) != 2
LIBX += memcpy.c memset.c
#endif

#if identifiers(/lib/libc.a,closedir,opendir,readdir,seekdir,telldir) != 5
LIBX += opendir.c readdir.c seekdir.c telldir.c
#endif

#if identifiers(/lib/libc.a,sgetl,sputl) != 2
LIBX += sgetl.c sputl.c
#endif

#if exists(/lib/libjobs.a) || exists(/usr/lib/libjobs.a)
JOBS = killpg.o setpgrp.o signal.o sigset.o
LIBX += $(JOBS)
$(JOBS) : libjobs.a
	$(AR) x $(*) $(<)
#endif

#if machine(balance8000)
LIBX += rindex.c
#endif

$(LIBDIR)/libx.a :: $(LIBX) $(LIBXO)

#if architecture(vax)
$(LIBXO:BS=.o) : .IMPLICIT
	$(CC) $(CCFLAGS:/-O//) -c $(>)
#endif

exprl.o expry.o : .READONLY

hash.o : (HASH_INFO)

hershey.o : (HERSHEYDIR)

FONTS = english.hf german.hf gothic.hf greek.hf greek_s.hf math.hf \
	roman.hf roman_b.hf roman_bi.hf roman_bs.hf roman_i.hf \
	roman_s.hf russian.hf script.hf script_b.hf stroke.hf

.FILES. += $(FONTS)

.INSTALL : fonts

fonts : $(FONTS:D=$(HERSHEYDIR):BS)

$(FONTS:D=$(HERSHEYDIR):BS) : $$(<:BS)
	$(CP) $(>) $(<)
