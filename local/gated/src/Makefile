#
#	Mini - makefile
#
#	$Id: Makefile,v 1.13.4.2 1994/07/25 00:24:10 jch Exp $
#
# %(Copyright.header)
#

MAKE=make
MAKEFILE=Makefile
ARCHTYPE=`util/archtype`
CONFIG=util/config
SHELL=/bin/sh
TAGS=etags
TFLAGS=
OBJDIRS=obj.`hostname | sed -e 's/\..*//'` obj.${ARCHTYPE} obj

doall:	all

true:;

all build_depend depend gated gdc ripquery ospf_monitor \
install install-man man clean cleanall clean-man lint links version Makefile:
	-@case "${.CURDIR}" in \
		""|"."|"${PWD}") \
			for arch in ${OBJDIRS}; do \
				if [ -d $${arch} ]; then \
					test -f $${arch}/${MAKEFILE} || ${MAKE} config ; \
					echo "cd $${arch}" ; \
					cd $${arch} ; \
					echo "$(MAKE) $(MFLAGS) $@" ; \
					$(MAKE) $(MFLAGS) $@ 2>&1 | tee make.log ; \
					exit 0; \
				fi; \
			done; \
			echo "Can not find any of { ${OBJDIRS} }." ; \
			exit 1 ; \
			;; \
		*) \
			cd ${.CURDIR} ; \
			$(MAKE) config ; \
			$(MAKE) $(MFLAGS) $@ ; \
			;; \
	esac

config:
	-@case "${.CURDIR}" in \
		""|"."|"${PWD}") \
			for dir in ${OBJDIRS} .; do \
				if [ -r $${dir}/Config ]; then \
					echo "${CONFIG} $${dir}/Config" ; \
					${CONFIG} $${dir}/Config ; \
					exit 0; \
				fi; \
			done; \
			echo "Can not find Config in { ${OBJDIRS} . } ." ; \
			exit 1 ; \
			;; \
		*) \
			cd ${.CURDIR} ; \
			echo "${CONFIG} $${MAKEOBJDIR-obj}/Config" ; \
			CURDIR=${.CURDIR} ${CONFIG} $${MAKEOBJDIR-obj}/Config ; \
			;; \
	esac

tags:	*.[chly]
	@echo "Building:	TAGS"
	@${TAGS} ${TFLAGS} *.[chly]

checkout:
	cvs checkout -d .. gated

#
# %(Copyright)
#
