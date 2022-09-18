PRINTER= -Pdp
TBL=	dtbl ${PRINTER}
TROFF=	ditroff -t ${PRINTER}
LPR=	lpr -n ${PRINTER}

all:
	@echo "use \"make infopacket\" to print information packet docs,"
	@echo "or \"make distribution\" to print distribution box docs"
	@false

infopacket:
	${TROFF} -ms cover.info | ${LPR}
	${TROFF} -ms Checklist.info | ${LPR}
	${TROFF} -ms Checklist.info.4.2licensees | ${LPR}
	${TROFF} -ms Checklist.info.UC | ${LPR}
	${TROFF} -ms License | ${LPR}
	${TBL} License.Addendum | ${TROFF} -ms | ${LPR}
	${TROFF} -ms UC_LetterOfAuth | ${LPR}
	${TROFF} -ms UCletter | ${LPR}
	${TBL} equiplist | ${TROFF} -ms | ${LPR}
	${TBL} siteinfo.me | ${TROFF} -me | ${LPR}
	${TROFF} -ms softonvax.t | ${LPR}
	${TROFF} -ms uVAXnote.t | ${LPR}

distribution:
	${TROFF} -ms Cover.distribution | ${LPR}
	${TROFF} -ms Acknowledgements | ${LPR}
	${TROFF} -ms PackingList | ${LPR}
