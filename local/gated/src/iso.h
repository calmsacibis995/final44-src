/*
 * $Id: iso.h,v 1.14.2.1 1995/01/13 19:19:04 jch Exp $
 */

/* %(Copyright.header) */

#define	ISO_MAXADDRLEN	20
#define	SOCKADDR_ISO_LEN	(sizeof (iso_addr_default->iso) - 1 + ISO_MAXADDRLEN)

extern byte iso_default_prefix[];	/* the all zeros prefix */
extern sockaddr_un *iso_addr_default;	/* same thing as a sockaddr */

extern sockaddr_un *iso_masks[];	/* All possible contiguous masks */
extern byte iso_mask_list[SOCKADDR_ISO_LEN * (ISO_MAXADDRLEN * NBBY + 1)];
#define	iso_mask_default	iso_masks[0]

#define	ISO_LIMIT_MASKLEN	0, (size_t) (ISO_MAXADDRLEN * NBBY)

#define	iso_mask_natural(addr)	iso_masks[(socksize(addr) - (addr->iso.giso_addr - (byte *) addr)) * NBBY]

/* Locate an ISO mask given it's prefix length */
#define        iso_mask_prefix(pfx)    ((pfx < 0 || pfx > (ISO_MAXADDRLEN * NBBY)) ? (sockaddr_un *) 0 : iso_masks[pfx])

#define        iso_prefix_mask(mask) \
	((byte *) (mask) >= iso_mask_list && (byte *) (mask) < iso_mask_list + sizeof iso_mask_list) \
	? (((byte *) (mask) - iso_mask_list) / SOCKADDR_ISO_LEN) \
	: (u_int) -1

PROTOTYPE(iso_mask_locate,
	  extern sockaddr_un *,
	  (sockaddr_un *));
PROTOTYPE(iso_family_init,
	  extern void,
	  (void));
PROTOTYPE(iso_init,
	  extern void,
	  (void));


/*
 * %(Copyright)
 */
