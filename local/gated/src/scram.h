/*
 * $Id: scram.h,v 1.10 1994/01/17 18:49:12 jch Exp $
 */

/* %(Copyright.header) */


/* Scram */

#define	SCRAM_NAME	"/tmp/gated_route_to_scram"

#define	SCRAM_T_OPEN		(time_t) 15

PROTOTYPE(scram_init,
	  extern void,
	  (void));
PROTOTYPE(scram_reinit,
	  extern void,
	  (task *));
PROTOTYPE(scram_request,
	  extern void,
	  (int,
	   rt_entry *));

/*
 * %(Copyright)
 */
