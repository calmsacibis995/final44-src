/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	getidprom.s,v $
 * Revision 2.2  89/07/12  00:22:06  jjc
 * 	Picked up from SunOS 4.0.
 * 	[89/07/03            jjc]
 * 
 */
|
| 	@(#)getidprom.s 1.2 88/02/08 Copyright (c) 1985 by Sun Microsystems, Inc.
|
#ifdef sun2
#define	FC_MAP		3
#define	BYTESPERPG	0x800
#define	IDPROMOFF	8
#endif
#ifdef sun3
#define	FC_MAP		3
#define	BYTESPERPG	0x2000
#define	IDPROMOFF	0
#endif


|
| getidprom(addr, size)
|
| Read back <size> bytes of the ID prom and store them at <addr>.
| Typical use:  getidprom(&idprom_struct, sizeof(idprom_struct));
|
	.globl	_getidprom
_getidprom:
	movl	sp@(4),a0	| address to move ID prom bytes to
	movl	sp@(8),d1	| How many bytes to move
	movl	d2,sp@-		| save a reg
	movc	sfc,d0		| save source func code
	movl	#FC_MAP,d2
	movc	d2,sfc		| set space 3
	lea	IDPROMOFF,a1	| select id prom
	jra	2$		| Enter loop at bottom as usual for dbra
1$:	movsb	a1@+,d2		| get a byte
	movb	d2,a0@+		| save it
#ifdef sun2
	addw	#BYTESPERPG-1,a1 | address next byte (in next page)
#endif sun2
2$:	dbra	d1,1$		| and loop
	movc	d0,sfc		| restore sfc
	movl	sp@+,d2		| restore d2
	rts
