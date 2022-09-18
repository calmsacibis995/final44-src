/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	kdbdefine.h,v $
 * Revision 1.4  89/03/09  20:01:03  rpd
 * 	More cleanup.
 * 
 * Revision 1.3  89/02/27  21:33:12  mrt
 * 	We will minimally sanitize this kdb till something better comes
 * 	along.
 * 	[89/02/27            rvb]
 * 
 */

#define access	kdbaccess
#define bchkget	kdbbchkget
#define bignumprint	kdbbignumprint
#define bpwait	kdbbpwait
#define bsbrk	kdbbsbrk
#define casebody	kdbcasebody
#define charpos	kdbcharpos
#define chkerr	kdbchkerr
#define chkget	kdbchkget
#define chkloc	kdbchkloc
#define chkmap	kdbchkmap
#define command	kdbcommand
#define convdig	kdbconvdig
#define convert	kdbconvert
#define delbp	kdbdelbp
#define digit	kdbdigit
#define dispaddress	kdbdispaddress
#define done	kdbdone
#define editchar	kdbeditchar
#define endline	kdbendline
#define endpcs	kdbendpcs
#define eol	kdbeol
#define eqstr	kdbeqstr
#define eqsym	kdbeqsym
#define error	kdberror
#define execbkpt	kdbexecbkpt
#define execbkptf	kdbexecbkptf
#define exform	kdbexform
#define expr	kdbexpr
#define findsym	kdbfindsym
#define flushbuf	kdbflushbuf
#define get	kdbget
#define getformat	kdbgetformat
#define getnum	kdbgetnum
#define getreg	kdbgetreg
#define getsig	kdbgetsig
#define iclose	kdbiclose
#define inkdot	kdbinkdot
#define insregname	kdbinsregname
#define item	kdbitem
#define length	kdblength
#define localsym	kdblocalsym
#define lookup	kdblookup
#define mapescbyte	kdbmapescbyte
#define mkioptab	kdbmkioptab
#define newline	kdbnewline
#define nextchar	kdbnextchar
#define nextpcs	kdbnextpcs
#define oclose	kdboclose
#define operandout	kdboperandout
#define pcimmediate	kdbpcimmediate
#define physrw	kdbphysrw
#define printc	kdbprintc
#define printdate	kdbprintdate
#define printdbl	kdbprintdbl
#define printesc	kdbprintesc
#define printf	kdbprintf
#define printins	kdbprintins
#define printmap	kdbprintmap
#define printnum	kdbprintnum
#define printoct	kdbprintoct
#define printpc	kdbprintpc
#define printregs	kdbprintregs
#define prints	kdbprints
#define printtrace	kdbprinttrace
#define psymoff	kdbpsymoff
#define put	kdbput
#define putchar	cnputc
#define quotchar	kdbquotchar
#define rdc	kdbrdc
#define rdfp	kdbrdfp
#define read	kdbread
#define readchar	kdbreadchar
#define readregs	kdbreadregs
#define readsym	kdbreadsym
#define rintr	kdbrintr
#define round	kdbround
#define runpcs	kdbrunpcs
#define rwerr	kdbrwerr
#define sbrk	kdbsbrk
#define scanbkpt	kdbscanbkpt
#define scanform	kdbscanform
#define setbp	kdbsetbp
#define setcor	kdbsetcor
#define setsym	kdbsetsym
#define setup	kdbsetup
#define setvar	kdbsetvar
#define shell	kdbshell
#define shortliteral	kdbshortliteral
#define sigprint	kdbsigprint
#define snarf	kdbsnarf
#define snarfreloc	kdbsnarfreloc
#define snarfuchar	kdbsnarfuchar
#define subpcs	kdbsubpcs
#define symchar	kdbsymchar
#define term	kdbterm
#define valpr	kdbvalpr
#define varchk	kdbvarchk
#define within	kdbwithin
#define write	kdbwrite

#define adrflg	kdbadrflg
#define adrval	kdbadrval
#define bkpthead	kdbbkpthead
#define bpstate	kdbbpstate
#define callpc	kdbcallpc
#define cntflg	kdbcntflg
#define cntval	kdbcntval
#define corfil	kdbcorfil
#define cursym	kdbcursym
#define datbas	kdbdatbas
#define datmap	kdbdatmap
#define digitptr	kdbdigitptr
#define ditto	kdbditto
#define dot	kdbdot
#define dotinc	kdbdotinc
#define entrypt	kdbentrypt
#define eof	kdbeof
#define eqformat	kdbeqformat
#define erasec	kdberasec
#define errflg	kdberrflg
#define errno	kdberrno
#define esymtab	kdbesymtab
#define executing	kdbexecuting
#define exitflg	kdbexitflg
#define expv	kdbexpv
#define fcor	kdbfcor
#define filhdr	kdbfilhdr
#define fltimm	kdbfltimm
#define fpenames	kdbfpenames
#define fphack	kdbfphack
#define fsym	kdbfsym
#define ifiledepth	kdbifiledepth
#define illinames	kdbillinames
#define incp	kdbincp
#define infile	kdbinfile
#define insoutvar	kdbinsoutvar
#define insttab	kdbinsttab
#define ioptab	kdbioptab
#define istack	kdbistack
#define isymbol	kdbisymbol
#define itolws	kdbitolws
#define kcore	kdbkcore
#define kernel	kdbkernel
#define lastc	kdblastc
#define lastcom	kdblastcom
#define lastframe	kdblastframe
#define line	kdbline
#define localval	kdblocalval
#define locmsk	kdblocmsk
#define locval	kdblocval
#define loopcnt	kdbloopcnt
#define lp	kdblp
#define masterpcbb	kdbmasterpcbb
#define maxfile	kdbmaxfile
#define maxoff	kdbmaxoff
#define maxpos	kdbmaxpos
#define maxstor	kdbmaxstor
#define mkfault	kdbmkfault
#define outfile	kdboutfile
#define pcb	kdbpcb
#define peekc	kdbpeekc
#define pid	kdbpid
#define printbuf	kdbprintbuf
#define printptr	kdbprintptr
#define radix	kdbradix
#define reglist	kdbreglist
#define regname	kdbregname
#define savframe	kdbsavframe
#define savlastf	kdbsavlastf
#define savpc	kdbsavpc
#define sbr	kdbsbr
#define sigint	kdbsigint
#define signals	kdbsignals
#define signo	kdbsigno
#define sigqit	kdbsigqit
#define slr	kdbslr
#define space	kdbspace
#define stformat	kdbstformat
#define stksiz	kdbstksiz
#define symfil	kdbsymfil
#define symtab	kdbsymtab
#define systab	kdbsystab
#define txtmap	kdbtxtmap
#define ty_NORELOC	kdbty_NORELOC
#define ty_nbyte	kdbty_nbyte
#define type	kdbtype
#define udot	kdbudot
#define userpc	kdbuserpc
#define var	kdbvar
#define wtflag	kdbwtflag
#define wtflg	kdbwtflg
#define xargc	kdbxargc

#define curmap	kdbcurmap
#define curpcb	kdbcurpcb
#define curpid	kdbcurpid
