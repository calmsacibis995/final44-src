/* psspool.h
 *
 * Copyright (c) 1985 Adobe Systems Incorporated
 *
 * nice constants for printcap spooler filters
 *
 * RCSID: $Header: psspool.h,v 2.1 85/11/24 11:51:12 shore Rel $
 *
 * RCSLOG:
 * $Log:	psspool.h,v $
 * Revision 2.1  85/11/24  11:51:12  shore
 * Product Release 2.0
 * 
 * Revision 1.2  85/05/14  11:26:54  shore
 * 
 * 
 *
 */

#define PS_INT	'\003'
#define PS_EOF	'\004'
#define PS_STATUS '\024'

/* error exit codes for lpd-invoked processes */
#define TRY_AGAIN 1
#define THROW_AWAY 2

