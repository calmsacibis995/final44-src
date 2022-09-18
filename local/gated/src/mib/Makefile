#
#	$Id: Makefile,v 1.12 1994/02/09 22:45:39 jch Exp $
#
# %(Copyright.header)
#

ISODE_DIR	=	/vol/src/isode-7.0
RFC		=	/vol/rfc
ID		=	/home/jch/lib/script/net/IETF

MYS		=	smi.my mib.my rt.my ospf.my rip.my bgp.my gated.my isisext.myp slsp.my
DEFS		=	smi.defs mib.defs rt.defs ospf.defs rip.defs bgp.defs gated.defs isisext.defs slsp.defs
TXTS		=	gated.txt
CHECK		=	smi.chk mib.chk rt.chk ospf.chk rip.chk bgp.chk gated.chk isisext.chk slsp.chk

.SUFFIXES:	.txt .my .defs .chk .rf

.rf.txt:
	rf2txt.sh $< > $@ || rm $@

.txt.my:
	rfc2my.sh $< > $@ || rm $@

.my.defs:
	mosy -s -o - $< > $@ || rm $@

.defs.chk:
	@echo "snmpi -f " $< " quit" ;
	@cat $? > $*.tmp ; snmpi -f $*.tmp quit ; rm $*.tmp ;

all:	${DEFS}

check:	${CHECK}

clean:
	rm -f ${DEFS} ${CHECK} ${TXTS}

smi.defs:	/usr/include/isode/snmp/smi.defs
	cp -p /usr/include/isode/snmp/smi.defs $@

smi.my:		${ISODE_DIR}/snmp/smi.my
	cp -p $? $@

mib.my:		${ISODE_DIR}/snmp/mib.my
	cp -p $? $@

ospf.my:	${ISODE_DIR}/snmp/ospf.my
	cp -p $? $@

rip.my:		${RFC}/rfc1389.txt
	rfc2my.sh $? > $@

rt.my:		${RFC}/rfc1354.txt
	rfc2my.sh $? > $@

bgp.my:		${RFC}/rfc1269.txt
	rfc2my.sh $? > $@

slsp.my:	slsp.txt
	rfc2my.sh slsp.txt > $@

mib.chk:	smi.defs
ospf.chk:	smi.defs mib.defs
rip.chk:	smi.defs mib.defs
bgp.chk:	smi.defs mib.defs
rt.chk:		smi.defs mib.defs
gated.chk:	smi.defs mib.defs
isisext.chk:	smi.defs mib.defs
slsp.chk:	smi.defs mib.defs

gated.txt:	gated.rf gatedAgents.rf gatedGeneral.rf gatedConfig.rf gatedInet.rf
gated.my:	gated.txt
gated.defs:	gated.my

#
# %(Copyright)
#
