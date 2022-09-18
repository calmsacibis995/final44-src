/* 
 * Mach Operating System
 * Copyright (c) 1994-1991 Carnegie Mellon University
 * Copyright (c) 1991 IBM Corporation 
 * All Rights Reserved.
 * 
 * Permission to use, copy, modify and distribute this software and its
 * documentation is hereby granted, provided that both the copyright
 * notice and this permission notice appear in all copies of the
 * software, derivative works or modified versions, and any portions
 * thereof, and that both notices appear in supporting documentation,
 * and that the name IBM not be used in advertising or publicity 
 * pertaining to distribution of the software without specific, written
 * prior permission.
 * 
 * CARNEGIE MELLON AND IBM ALLOW FREE USE OF THIS SOFTWARE IN ITS "AS IS"
 * CONDITION.  CARNEGIE MELLON AND IBM DISCLAIM ANY LIABILITY OF ANY KIND FOR
 * ANY DAMAGES WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE.
 * 
 * Carnegie Mellon requests users of this software to return to
 * 
 *  Software Distribution Coordinator  or  Software.Distribution@CS.CMU.EDU
 *  School of Computer Science
 *  Carnegie Mellon University
 *  Pittsburgh PA 15213-3890
 * 
 * any improvements or extensions that they make and grant Carnegie Mellon
 * the rights to redistribute these changes.
 */

/* 
 * HISTORY
 * $Log:	pos.h,v $
 * Revision 2.2  94/12/15  15:49:26  dbg
 * 	Removed everything but POS registers, since we now use standard
 * 	autoconfiguration structures.  Moved to i386ps2/pos.h.
 * 	[94/06/17            dbg]
 * 
 * Revision 2.3  93/03/11  14:08:48  danner
 * 	u_long -> u_int
 * 	[93/03/09            danner]
 * 
 * Revision 2.2  93/02/04  07:59:01  danner
 * 	Integrate PS2 code from IBM.
 * 	[93/01/18            prithvi]
 * 
 */

#ifndef	_I386PS2_POS_H_
#define	_I386PS2_POS_H_

#define MAX_POS_SLOTS	8	/* max number of slots */
#define MAX_POS_BYTES	8	/* max number of bytes */
#define MAX_POS_INFO	6	/* max number of info bytes */

#define POS_DISABLE_VGA	0x94
#define POS_PORT	0x96
#define POS_ENABLE(slot) (0x08+(slot))
#define POS_DISABLE	0x00
#define POS_GET_DATA(slot) inb(0x100+(slot))

#define POS_ID_NONE	0xffff	/* no card present */

struct pos_info {
	union {
	    unsigned short  un_pos_id;		/* the ID as a short */
	    unsigned char   un_data[2];		/* first two bytes of data */
	} un;
	unsigned char	pos_info[MAX_POS_INFO];	/* the bytes from hardware */
} slots[MAX_POS_SLOTS];

#define pos_data un.un_data
#define pos_id un.un_pos_id

extern void	pos_init(void);
extern int	pos_slot(
	unsigned short	card_id,
	int		slot);

#endif	/* _I386PS2_POS_H_ */

