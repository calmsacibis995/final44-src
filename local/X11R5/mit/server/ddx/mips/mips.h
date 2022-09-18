/*
 * $XConsortium: mips.h,v 1.4 91/07/18 22:57:52 keith Exp $
 *
 * Copyright 1991 MIPS Computer Systems, Inc.
 *
 * Permission to use, copy, modify, distribute, and sell this software and its
 * documentation for any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that
 * copyright notice and this permission notice appear in supporting
 * documentation, and that the name of MIPS not be used in advertising or
 * publicity pertaining to distribution of the software without specific,
 * written prior permission.  MIPS makes no representations about the
 * suitability of this software for any purpose.  It is provided "as is"
 * without express or implied warranty.
 *
 * MIPS DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING ALL
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL MIPS
 * BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
 * OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN 
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */
/* $Header: mips.h,v 1.4 91/07/18 22:57:52 keith Exp $ */
#ifndef __DDX_MIPS_H
#define	__DDX_MIPS_H

#ifndef PIXIE
#define PIXIE   	0	/* Define to allow Pause/Break key to exit */
				/* must be defined for pixie analysis */
				/* Also must provide -DPIXIE in os/4.2bsd */
#endif

#ifndef NETWORK_KEYBD
#define NETWORK_KEYBD	0	/* Connect across TCP socket to remote keyboard client */
#endif

/* System types */
#define RS2030		0
#define RS3230		1

extern int mipsSysType;

#endif /* __DDX_MIPS_H */
