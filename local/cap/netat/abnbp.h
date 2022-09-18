/*
 *  Author: cck    Date: 88/04/30 09:00:50  
 *  Header: abnbp.h,v 1.4 88/04/30 09:00:50 cck Rel  
 *  Revision: 1.4  
*/

/*
 * abnbp.h - Name Binding Protocol definitions
 *
 * AppleTalk package for UNIX (4.2 BSD).
 *
 * Copyright (c) 1986, 1987 by The Trustees of Columbia University in the
 * City of New York.
 *
 * Edit History:
 *
 *  April 1, 1976 CCKIM Created
 *
*/

/* NBP Information Socket - for NBP server */
#define	nbpNIS		2

#define	nbpBrRq		1
#define	nbpLkUp		2
#define	nbpLkUpReply	3
#define nbpRegister    0x7	/* register a name */
#define nbpDelete      0x8	/* delete a name */
#define nbpTickle      0x9	/* let them know socket is alive and well */
#define nbpStatusReply 0xa	/* status on register/delete */
#define nbpLookAside   0xb	/* Lookup via NIS */
/* maximum is 0xf */


/* status reply codes - all max out at 0xf - zero is reserved for noErr */

#define nbpSR_noErr 0x0

/* status reply codes for register */
#define nbpSR_access	0x1	/* permission denied */
#define nbpSR_overflow	0x2	/* name server overflow */

/* status reply codes for delete */
/* - uses nbpSR_access  */
#define nbpSR_nsn	0x2	/* no such name */


#define	nbpTupleMax	15
/* 3 for field lengths + 3*32  for the three names */
#define MAX_TUPLE_SIZE 99

/* control + id + Addrblock + enumerator */
#define nbpBaseSize (1+1+1+sizeof(AddrBlock))
/* nbpBaseSize + 3 for the three object lengths */
#define nbpMinSize (nbpBaseSize + 3)

typedef struct {
  AddrBlock addr;		/* address */
  byte enume;			/* enumerator */
  byte name[MAX_TUPLE_SIZE];	/* the entity name */
} NBPTuple;

/* following would be really simple if we could use #if, but vms */
/* c doesn't like and hopefully someday... */
#ifndef BYTESWAPPED
# ifdef vax
#  define BYTESWAPPED
# endif
#endif
#ifndef BYTESWAPPED
# ifdef ns16000
#  define BYTESWAPPED
# endif
#endif
#ifndef BYTESWAPPED
# ifdef ns32000
#  define BYTESWAPPED
# endif
#endif
/* add this in case sequent doesn't define nsxxxxx */
#ifndef BYTESWAPPED
# ifdef sequent
#  define BYTESWAPPED
# endif
#endif


typedef struct {
#ifdef BYTESWAPPED
  /* then these structure elements need to be reversed */
  /* because the machines are byteswapped */
  byte tcnt : 4,		/* tuple count */
       control : 4;		/* control */
#else
  byte control : 4,		/* control */
       tcnt : 4;		/* tuple count */
#endif
  byte id;			/* NBP identifier */
  NBPTuple tuple[nbpTupleMax]; /* start of first tuple, */
} NBP;				/* space for rest */

typedef struct {
  byte lapddp[lapSize+ddpSize];
  NBP nbp;
} NBPpkt;
