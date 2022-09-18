h41437
s 00002/00002/00097
d D 8.1 93/06/10 21:23:19 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00000/00097
d D 7.4 92/06/05 15:23:15 hibler 4 3
c merge latest Utah hp300 code including 68040 support
e
s 00040/00034/00057
d D 7.3 91/05/07 09:52:06 hibler 3 2
c 
e
s 00009/00006/00082
d D 7.2 90/05/25 15:43:35 mckusick 2 1
c "update from Mike Hibler at Utah"
e
s 00088/00000/00000
d D 7.1 90/05/08 22:06:34 mckusick 1 0
c merge in hp300 support from Utah
e
u
U
t
T
I 1
/*
D 5
 * Copyright (c) 1982, 1990 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1982, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

struct driver {
	int	(*d_init)();
	char	*d_name;
	int	(*d_start)();
	int	(*d_go)();
	int	(*d_intr)();
	int	(*d_done)();
};

struct hp_ctlr {
	struct driver	*hp_driver;
	int		hp_unit;
	int		hp_alive;
	char		*hp_addr;
	int		hp_flags;
	int		hp_ipl;
};

struct hp_device {
	struct driver	*hp_driver;
	struct driver	*hp_cdriver;
	int		hp_unit;
	int		hp_ctlr;
	int		hp_slave;
	char		*hp_addr;
	int		hp_dk;
	int		hp_flags;
	int		hp_alive;
	int		hp_ipl;
};

struct	devqueue {
	struct	devqueue *dq_forw;
	struct	devqueue *dq_back;
	int	dq_ctlr;
	int	dq_unit;
	int	dq_slave;
	struct	driver *dq_driver;
};

I 3
#define	MAXCTLRS	16	/* Size of HW table (arbitrary) */
#define	MAXSLAVES	8	/* Slaves per controller (HPIB/SCSI limit) */

E 3
struct hp_hw {
D 3
	char	*hw_addr;	/* physical address of registers */
	short	hw_sc;		/* select code (if applicable) */
	short	hw_type;	/* type (defined below) */
E 3
I 3
	caddr_t	hw_pa;		/* physical address of control space */
	int	hw_size;	/* size of control space */
	caddr_t	hw_kva;		/* kernel virtual address of control space */
E 3
	short	hw_id;		/* HW returned id */
D 3
	short	hw_id2;		/* secondary HW id (displays) */
	char	*hw_name;	/* HP product name */
E 3
I 3
	short	hw_secid;	/* secondary HW id (displays) */
	short	hw_type;	/* type (defined below) */
	short	hw_sc;		/* select code (if applicable) */
E 3
};

D 3
#define	MAX_CTLR	16	/* Totally arbitrary */
#define	MAXSLAVES	8	/* Currently the HPIB limit */
E 3
I 3
/* bus types */
#define	B_MASK		0xE000
#define	B_DIO		0x2000
#define B_DIOII		0x4000
#define B_VME		0x6000
/* controller types */
#define	C_MASK		0x8F
#define C_FLAG		0x80
#define	C_HPIB		0x81
#define C_SCSI		0x82
#define C_VME		0x83
/* device types (controllers with no slaves) */
#define D_MASK		0x8F
#define	D_BITMAP	0x01
#define	D_LAN		0x02
#define	D_FPA		0x03
#define	D_KEYBOARD	0x04
#define	D_COMMDCA	0x05
#define	D_COMMDCM	0x06
#define	D_COMMDCL	0x07
#define	D_PPORT		0x08
#define	D_MISC		0x7F
E 3

D 3
#define	WILD_CARD_CTLR	0
E 3
I 3
#define HW_ISCTLR(hw)	((hw)->hw_type & C_FLAG)
#define HW_ISDIOII(hw)	((hw)->hw_type & B_DIOII)
#define HW_ISHPIB(hw)	(((hw)->hw_type & C_MASK) == C_HPIB)
#define HW_ISSCSI(hw)	(((hw)->hw_type & C_MASK) == C_SCSI)
#define HW_ISDEV(hw,d)	(((hw)->hw_type & D_MASK) == (d))
E 3

D 3
/* A controller is a card which can have one or more slaves attached */
#define	CONTROLLER	0x10
#define	HPIB		0x16
#define	SCSI		0x17
#define	VME		0x18
#define	FLINK		0x19

/* Slaves are devices which attach to controllers, e.g. disks, tapes */
#define	RD		0x2a
#define	PPI		0x2b
#define	CT		0x2c

/* These are not controllers, but may have their own HPIB address */
D 2
#define	BITMAP		0x01
#define	NET		0x02
#define	COMM		0x03
#define	FPA		0x04
#define	MISC		0x05
#define KEYBOARD	0x06
E 2
I 2
#define	BITMAP		1
#define	NET		2
#define	FPA		4
#define	MISC		5
#define	KEYBOARD	6
#define	COMMDCA		7
#define	COMMDCM		8
#define	COMMDCL		9
#define	PPORT		10
E 2

E 3
#ifdef KERNEL
I 4
#ifdef hp300
E 4
D 3
extern struct hp_ctlr	hp_cinit[];
extern struct hp_device	hp_dinit[];
extern struct hp_hw	sc_table[];
E 3
I 3
extern struct hp_hw sc_table[];
extern struct hp_ctlr hp_cinit[];
extern struct hp_device hp_dinit[];
extern caddr_t sctova(), sctopa(), iomap();
I 4
#endif
E 4
E 3
#endif
E 1
