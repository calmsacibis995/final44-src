##
# $XConsortium: Makefile,v 5.3 91/08/20 20:03:11 hersh Exp $
##
## 
## Copyright (c) 1990, 1991 by Sun Microsystems, Inc. and the X Consortium.
## 
##			 All Rights Reserved
## 
## Permission to use, copy, modify, and distribute this software and its 
## documentation for any purpose and without fee is hereby granted, 
## provided that the above copyright notice appear in all copies and that
## both that copyright notice and this permission notice appear in 
## supporting documentation, and that the names of Sun Microsystems,
## the X Consortium, and MIT not be used in advertising or publicity 
## pertaining to distribution of the software without specific, written 
## prior permission.  
## 
## SUN MICROSYSTEMS DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, 
## INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO
## EVENT SHALL SUN MICROSYSTEMS BE LIABLE FOR ANY SPECIAL, INDIRECT OR
## CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF
## USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
## OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
## PERFORMANCE OF THIS SOFTWARE.

DOCBIN=..

XREF=$(DOCBIN)/xref

RECODE=$(DOCBIN)/recode

INDEXER=$(DOCBIN)/indexer

PEXMACROS=$(DOCBIN)/pex.macros

all: draft/cover.PS draft/doc.PS draft/index.PS 

PHIGSMAN = phigs.macros
INDEX_MACROS_STD = index.macros
NAMES = names.make

include $(NAMES)

TROFF=psroff
TBL=tbl
EQN=eqn

draft/doc.PS: $(NAMES)
	(cat $(PHIGSMAN) $(INDEX_MACROS_STD) $(NAMES) ; \
		echo .tm section 1: \\n% ) | \
 	$(TBL) | $(EQN) | \
	$(TROFF) -rC1 -rD1 -rF1 -rj$$FORTRAN > $@ 2> draft/book.temp

draft/cover.PS: cover.phigs $(PHIGSMAN)
	$(TROFF) -rj$$FORTRAN -ms cover.phigs > $@ 2>/dev/null

draft/index.PS: $(INDEX_MACROS_STD) draft/doc.PS
	grep 'section 1:' draft/book.temp | \
		awk '{print $$3}' > draft/book.maxpage
	awk '{ if ($$1 % 2) { \
		printf (".TH \"BLANK\" \"\" \"16 August 1991\"\n"); \
		printf ("\\&\n"); \
		printf (".TH INDEX \"\" \"16 August 1991\"\n"); \
		printf (".bp\n"); \
 	     } else { \
 	      	printf (".TH INDEX \"\" \"16 August 1991\"");  \
	     } }' draft/book.maxpage > draft/book.file
	$(RECODE) < draft/book.temp | grep '^\.IE' | \
		$(INDEXER) >> draft/book.file
	$(TROFF) -rC1 -rD1 -rF1 -rj$$FORTRAN \
		 -rP`awk '{printf("%s", $$1 + 1)}' draft/book.maxpage` \
		 $(PHIGSMAN) draft/book.file > $@ 2>/dev/null

clean:
	rm -f draft/book* draft/*.PS
