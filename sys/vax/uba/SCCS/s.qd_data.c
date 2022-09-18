h31140
s 00016/00016/00324
d D 1.4 90/12/16 16:59:41 bostic 4 3
c kernel reorg
e
s 00011/00012/00329
d D 1.3 90/02/17 11:03:59 mckusick 3 2
c get rid of dir.h
e
s 00005/00008/00336
d D 1.2 87/08/07 15:55:30 marc 2 1
c not needed anymore - merged into qd.c for 4.3
e
s 00344/00000/00000
d D 1.1 87/07/09 17:57:30 marc 1 0
c date and time created 87/07/09 17:57:30 by marc
e
u
U
t
T
I 1
/*
 *	@(#)qd_data.c	1.16	(ULTRIX)	7/2/86
 */

/************************************************************************
 *									*
 *			Copyright (c) 1985, 1986 by			*
 *		Digital Equipment Corporation, Maynard, MA		*
 *			All rights reserved.				*
 *									*
 *   This software is furnished under a license and may be used and	*
 *   copied  only  in accordance with the terms of such license and	*
 *   with the  inclusion  of  the  above  copyright  notice.   This	*
 *   software  or  any	other copies thereof may not be provided or	*
 *   otherwise made available to any other person.  No title to and	*
 *   ownership of the software is hereby transferred.			*
 *									*
 *   The information in this software is subject to change  without	*
 *   notice  and should not be construed as a commitment by Digital	*
 *   Equipment Corporation.						*
 *									*
 *   Digital assumes no responsibility for the use  or	reliability	*
 *   of its software on equipment which is not supplied by Digital.	*
 *									*
 ************************************************************************/

/*
 * qd_data.c
 *
 * Modification history
 *
 * QDSS data file
 *
 *  3-Jul-85 - longo
 *
 *	Created file.
 *
 * 15-Jul-85 - longo
 *
 *	Added "qdfont.h" include and moved "mouse_report" struct
 *	and definitions in from "qduser.h".
 *
 * 18-Aug-85 - longo
 *
 *	Added "duart_imask" entry to qdflags for shadowing.
 *
 *  4-Sep-85 - longo
 *
 *	Added storage "QBAreg[]" for DMA support.
 *
 * 11-Sep-85 - longo
 *
 *	Added constant for event buffer size (now 1k).
 *
 * 17-Sep-85 - longo
 *
 *	Changes for DMA support.
 *
 * 18-Sep-85 - longo
 *
 *	Changes for scroll interrupt support.
 *
 *  2-Oct-85 - longo
 *
 *	Added color map write buffer shared RAM stuff and adder
 *	interrupt enable register shadowing to qdflags.
 *
 *  4-Oct-85 - longo
 *
 *	Added kernel loop back state flag to qdflags.
 *
 * 16-Oct-85 - longo
 *
 *	Added "pntr_id" entry to qdflags struct.
 *
 * 22-Oct-85 - longo
 *
 *	Added buf structures for use by driver strategy routines.
 *
 * 23-Oct-85 - longo
 *
 *	Added "user_dma" entry to qdflag structure.
 *
 *  8-Nov-85 - longo
 *
 *	Added "selmask" entry to qdflags structure.
 *
 * 11-Nov-85 - longo
 *
 *	Changed "_vs_eventqueue" struct references to "qdinput".
 *
 * 25-Nov-85 - longo
 *
 *	Added "one_only" lock switch for single process access.
 *
 * 18-Mar-86 - jaw
 *
 *	Add routines to cpu switch for nexus/unibus addreses.
 *	Also got rid of some globals like nexnum.
 *	ka8800 cleanup.
 *
 * 19-Mar-86 - ricky palmer
 *
 *	Added "devio.h" to include list. V2.0
 *
 * 02-Jul-86 -  Brian Stevens
 *
 *	Added cursor structure for each display
 *
 */

#include "qd.h" 	/* # of QDSS's the system is configured for */

D 2
#include "../machine/pte.h"	/* page table values */
#include "../machine/mtpr.h"	/* VAX register access stuff */
E 2
I 2
D 4
#include "../vax/pte.h"	/* page table values */
#include "../vax/mtpr.h"	/* VAX register access stuff */
E 4
I 4
#include "../include/pte.h"	/* page table values */
#include "../include/mtpr.h"	/* VAX register access stuff */
E 4
E 2

D 3
#include "../h/param.h" 	/* general system params & macros */
#include "../h/conf.h"		/* "linesw" tty driver dispatch */
#include "../h/dir.h"		/* for directory handling */
#include "../h/user.h"		/* user structure (what else?) */
E 3
I 3
D 4
#include "../sys/param.h" 	/* general system params & macros */
#include "../sys/conf.h"	/* "linesw" tty driver dispatch */
#include "../sys/user.h"	/* user structure (what else?) */
E 4
I 4
#include "sys/param.h" 		/* general system params & macros */
#include "sys/conf.h"		/* "linesw" tty driver dispatch */
#include "sys/user.h"		/* user structure (what else?) */
E 4
E 3
D 2
#include "../vaxuba/qdioctl.h"	/* ioctl call values */
E 2
I 2
#include "qdioctl.h" 		/* ioctl call values */
E 2
D 3
#include "../h/tty.h"
#include "../h/map.h"		/* resource allocation map struct */
#include "../h/buf.h"		/* buf structs */
#include "../h/vm.h"		/* includes 'vm' header files */
D 2
#include "../h/bk.h"		/* BKINPUT macro for line stuff */
E 2
#include "../h/clist.h" 	/* char list handling structs */
#include "../h/file.h"		/* file I/O definitions */
#include "../h/uio.h"		/* write/read call structs */
#include "../h/kernel.h"	/* clock handling structs */
E 3
I 3
D 4
#include "../sys/tty.h"
#include "../sys/map.h"		/* resource allocation map struct */
#include "../sys/buf.h"		/* buf structs */
#include "../sys/vm.h"		/* includes 'vm' header files */
#include "../sys/clist.h" 	/* char list handling structs */
#include "../sys/file.h"	/* file I/O definitions */
#include "../sys/uio.h"		/* write/read call structs */
#include "../sys/kernel.h"	/* clock handling structs */
E 3
D 2
#include "../h/cpuconf.h"
#include "../h/devio.h"
E 2
#include "../vax/cpu.h" 	/* per cpu (pcpu) struct */
E 4
I 4
#include "sys/tty.h"
#include "sys/map.h"		/* resource allocation map struct */
#include "sys/buf.h"		/* buf structs */
#include "sys/vm.h"		/* includes 'vm' header files */
#include "sys/clist.h" 		/* char list handling structs */
#include "sys/file.h"		/* file I/O definitions */
#include "sys/uio.h"		/* write/read call structs */
#include "sys/kernel.h"		/* clock handling structs */
#include "../include/cpu.h" 	/* per cpu (pcpu) struct */
E 4

D 4
#include "../vaxuba/ubareg.h"	/* uba & 'qba' register structs */
#include "../vaxuba/ubavar.h"	/* uba structs & uba map externs */
E 4
I 4
#include "../uba/ubareg.h"	/* uba & 'qba' register structs */
#include "../uba/ubavar.h"	/* uba structs & uba map externs */
E 4

D 2
#include "../vaxuba/qduser.h"	/* definitions shared with my client */
#include "../vaxuba/qdreg.h"	/* QDSS device register structures */
E 2
I 2
#include "qduser.h"	/* definitions shared with my client */
#include "qdreg.h"	/* QDSS device register structures */
E 2

/*-----------------------------------------------------------
* QDSS driver status flags for tracking operational state */

	struct qdflags {

	    u_int inuse;	    /* which minor dev's are in use now */
	    u_int config;	    /* I/O page register content */
	    u_int mapped;	    /* user mapping status word */
	    u_int kernel_loop;	    /* if kernel console is redirected */
	    u_int user_dma;	    /* DMA from user space in progress */
	    u_short pntr_id;	    /* type code of pointing device */
	    u_short duart_imask;    /* shadowing for duart intrpt mask reg */
	    u_short adder_ie;	    /* shadowing for adder intrpt enbl reg */
	    u_short curs_acc;	    /* cursor acceleration factor */
	    u_short curs_thr;	    /* cursor acceleration threshold level */
	    u_short tab_res;	    /* tablet resolution factor */
	    u_short selmask;	    /* mask for active qd select entries */
	};

	/* bit definitions for "inuse" entry  */

#define CONS_DEV	0x01
#define ALTCONS_DEV	0x02
#define GRAPHIC_DEV	0x04

	/* bit definitions for 'mapped' member of flag structure */

#define MAPDEV		0x01		/* hardware is mapped */
#define MAPDMA		0x02		/* DMA buffer mapped */
#define MAPEQ		0x04		/* event queue buffer mapped */
#define MAPSCR		0x08		/* scroll param area mapped */
#define MAPCOLOR	0x10		/* color map writing buffer mapped */

	/* bit definitions for 'selmask' member of qdflag structure */

#define SEL_READ	0x01		/* read select is active */
#define SEL_WRITE	0x02		/* write select is active */

/*----------------------------------------------
* constants used in shared memory operations */

#define EVENT_BUFSIZE  1024	/* # of bytes per device's event buffer */

#define MAXEVENTS  ( (EVENT_BUFSIZE - sizeof(struct qdinput))	 \
		     / sizeof(struct _vs_event) )

#define DMA_BUFSIZ	(1024 * 3)

#define COLOR_BUFSIZ  ((sizeof(struct color_buf) + 512) & ~0x01FF)

/*******************************************************************/

#ifdef BINARY

	extern struct uba_device *qdinfo[];  /* array of pntrs to each QDSS */
					     /* uba structure  */
	extern struct tty qd_tty[];

	extern struct qd_softc qd_softc[];

/*----------------------------------------------------------
* static storage used by multiple functions in this code  */

	extern int Qbus_unmap[];	  /* Qbus mapper release key */
	extern struct qdflags qdflags[];  /* QDSS device status flags */
	extern struct qdmap qdmap[];	  /* QDSS register map structure */
	extern caddr_t qdbase[];	  /* base address of each QDSS unit */
	extern struct buf qdbuf[];	  /* buf structs used by strategy */
	extern char one_only[]; 	  /* lock for single process access */

/*-----------------------------
* shared memory allocation  */

	extern char event_shared[];		 /* reserve event buf space */
	extern struct qdinput *eq_header[];	 /* event buf header ptrs */

	extern char DMA_shared[];		  /* reserve DMA buf space */
	extern struct DMAreq_header *DMAheader[]; /* DMA buf header ptrs */

	extern char scroll_shared[];	/* reserve space for scroll structs */
	extern struct scroll *scroll[]; /* pointers to scroll structures */

	extern char color_shared[];	      /* reserve space: color bufs */
	extern struct color_buf *color_buf[]; /* pointers to color bufs */

/*--------------------------------
* mouse input event structures */

	extern struct mouse_report last_rep[];
	extern struct mouse_report current_rep[];

/*----------------------------
* input event "select" use */

	extern struct proc *rsel[];	/* process waiting for select */

	extern int DMAbuf_size;

/*----------------------------
* console cursor structure */

	struct _vs_cursor cursor[];


/*********************************************************************/

#else

/*--------------------------------------------------------------------------
* reference to an array of "uba_device" structures built by the auto
* configuration program.  The uba_device structure decribes the device
* sufficiently for the driver to talk to it.  The auto configuration code
* fills in the uba_device structures (located in ioconf.c) from user
* maintained info.  */

	struct uba_device *qdinfo[NQD];  /* array of pntrs to each QDSS's */
					 /* uba structures  */
	struct tty qd_tty[NQD*4];	/* teletype structures for each.. */
					/* ..possible minor device */

	struct qd_softc qd_softc[NQD];

/*----------------------------------------------------------
* static storage used by multiple functions in this code  */

	int Qbus_unmap[NQD];		/* Qbus mapper release code */
	struct qdflags qdflags[NQD];	/* QDSS device status flags */
	struct qdmap qdmap[NQD];	/* QDSS register map structure */
	caddr_t qdbase[NQD];		/* base address of each QDSS unit */
	struct buf qdbuf[NQD];		/* buf structs used by strategy */
	char one_only[NQD];		/* lock for single process access */

/*------------------------------------------------------------------------
* the array "event_shared[]" is made up of a number of event queue buffers
* equal to the number of QDSS's configured into the running kernel (NQD).
* Each event queue buffer begins with an event queue header (struct qdinput)
* followed by a group of event queue entries (struct _vs_event).  The array
* "*eq_header[]" is an array of pointers to the start of each event queue
* buffer in "event_shared[]".  */

#define EQSIZE ((EVENT_BUFSIZE * NQD) + 512)

	char event_shared[EQSIZE];	    /* reserve space for event bufs */
	struct qdinput *eq_header[NQD];     /* event queue header pntrs */

/*--------------------------------------------------------------------------
* This allocation method reserves enough memory pages for NQD shared DMA I/O
* buffers.  Each buffer must consume an integral number of memory pages to
* guarantee that a following buffer will begin on a page boundary.  Also,
* enough space is allocated so that the FIRST I/O buffer can start at the
* 1st page boundary after "&DMA_shared".  Page boundaries are used so that
* memory protections can be turned on/off for individual buffers. */

#define IOBUFSIZE  ((DMA_BUFSIZ * NQD) + 512)

	char DMA_shared[IOBUFSIZE];	    /* reserve I/O buffer space */
	struct DMAreq_header *DMAheader[NQD];  /* DMA buffer header pntrs */

/*-------------------------------------------------------------------------
* The driver assists a client in scroll operations by loading dragon
* registers from an interrupt service routine.	The loading is done using
* parameters found in memory shrade between the driver and it's client.
* The scroll parameter structures are ALL loacted in the same memory page
* for reasons of memory economy.  */

	char scroll_shared[2 * 512];	/* reserve space for scroll structs */
	struct scroll *scroll[NQD];	/* pointers to scroll structures */

/*-----------------------------------------------------------------------
* the driver is programmable to provide the user with color map write
* services at VSYNC interrupt time.  At interrupt time the driver loads
* the color map with any user-requested load data found in shared memory */

#define COLOR_SHARED  ((COLOR_BUFSIZ * NQD) + 512)

	char color_shared[COLOR_SHARED];      /* reserve space: color bufs */
	struct color_buf *color_buf[NQD];     /* pointers to color bufs */

/*--------------------------------
* mouse input event structures */

	struct mouse_report last_rep[NQD];
	struct mouse_report current_rep[NQD];

/*----------------------------
* input event "select" use */

	struct proc *rsel[NQD]; 	/* process waiting for select */

/*----------------------------
* console cursor structure */

	struct _vs_cursor cursor[NQD];


/************************************************************************/

	int nNQD = NQD;

	int DMAbuf_size = DMA_BUFSIZ;

#endif


E 1
