ROFF	= troff
ROFFPR	= lpr -n
LPR	= lpr

MAKE    = make

DEFS	= "ROFF=$(ROFF)" "ROFFPR=$(ROFFPR)" "LPR=$(LPR)"

SUBDIRS	= Xansi Xim Xlc nls

all:

print:
	for i in $(SUBDIRS); \
	do \
		(cd $$i ; echo "making" all "in $$i"; \
		 $(MAKE) $(DEFS) print); \
	done
