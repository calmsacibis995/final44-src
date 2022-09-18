h00218
s 00001/00011/00071
d D 7.3 90/06/28 22:27:49 bostic 4 3
c new copyright notice
e
s 00015/00000/00067
d D 7.2 88/09/16 09:37:29 bostic 3 2
c add appropriate copyright notices
e
s 00003/00001/00064
d D 7.1 88/05/21 18:33:09 karels 2 1
c bring up to revision 7 for tahoe release
e
s 00065/00000/00000
d D 1.1 86/11/29 12:09:54 sam 1 0
c date and time created 86/11/29 12:09:54 by sam
e
u
U
t
T
I 1
D 2
/*	%M%	%I%	%E%	*/
E 2
I 2
/*
I 3
 * Copyright (c) 1986 The Regents of the University of California.
 * All rights reserved.
 *
D 4
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 4
I 4
 * %sccs.include.redist.c%
E 4
 *
E 3
 *	%W% (Berkeley) %G%
 */
E 2

/*
 * PS300-Host Handshake Protocol Definitions.
 */

/*
 * Commands sent from host->PS300.
 *
 * In the initial handshake carried out when requesting
 * one of these commands be performed, the PS300 always
 * returns the identical code to indicate success.
 */
#define PS_ABORT        0x1000  /* abort current command */
#define PS_RESET        0x3000  /* reset device */
#define PS_RDNET        0x5000  /* logical read */
#define PS_LOOKUP       0x8000  /* name lookup */
#define PS_RDPHY        0x9000  /* physical read */
#define PS_WRPHY_SYNC   0xa000  /* physical write w/ sync */
#define PS_WRPHY        0xb000  /* physical write */
#define PS_WRNET        0xc000  /* logical write */
#define PS_DETACH       0xd000  /* normal/diagnostic detach */
#define PS_ATTACH       0xe000  /* normal attach */
#define PS_DATTACH      0xf000  /* diagnostic attach */

#define PS_DIOREAD      0x4000  /* internal, wait for dioread attention */

/*
 * Command responses from PS300->host.
 */
#define PS_DMAOK(code)  ((code)|0x0a00) /* successful dma transfer */ 
#define PS_ADROK(code)  ((code)|0x0100) /* successful address tranfer */

#define PS_CODE(v)      ((v)&0xf000)    /* extract code from PS300 msg */
#define PS_LUNIT(v)     ((v)&0x000f)    /* extract PS300 unit from msg */

/*
 * Single unit PS300 address list.
 */
struct  psalist {
        u_short nblocks;                /* # of i/o vectors (we always use 1) */
        u_short addr[2];                /* PS300 address */
        u_short wc;                     /* transfer size */
};

/*
 * The max dma size is actually 64KB, but
 * we limit it to be just large enough for
 * the maximum vector list as this is sufficient
 * for our needs and we must allocate real
 * memory to the intermediate buffer.
 */
#define PS_MAXDMA       (1024+2048*12)

/*
 * Pseudo commands used internally by the driver.
 */
#define PS_DMAOUT       0x0100          /* dma buffer host->PS300 */
#define PS_DMAIN        0x0200          /* dma buffer PS300->host */

/*
 * Default timeouts.
 */
#define PS_TIMEOUT      30              /* dma/attention timeout (in hz) */
#define PS_DIOTIMO      1000            /* dio polling timeout */
E 1
