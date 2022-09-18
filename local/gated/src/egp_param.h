/*
 * $Id: egp_param.h,v 1.11.2.1 1994/02/28 20:34:05 jch Exp $
 */

/* %(Copyright.header) */


/* egp_param.h
 *
 * Defines various egp parameters
 */

#define EGP_PKTSIZE	8192		/* Maximum EGP packet size we can send and receive */
#define	EGP_PKTSLOP	1024		/* Slop in packet size to make it easier to detect overflow */

/* RFC904 defined parameters */
#define EGP_P1		30		/* Minimum interval for sending and receiving hellos */
#define EGP_P2		120		/* Minimum interval for sending and receiving polls */

#define	EGP_P3		30		/* interval between Request or Cease command retransmissions */
#define	EGP_P4		3600		/* interval during which state variables are maintained in */
					/* the absence of commands or responses in the Down or Up states */
#define	EGP_P5		120		/* interval during which state variables are maintained in */
					/* the absence of responses in the Acquisition and Cease states */

/* Automatic restart timers */
#define	EGP_START_RETRY	EGP_P5		/* Retry if max neighbors already acquired */
#define	EGP_START_SHORT	EGP_P5		/* Retry neighbor in 2 minutes */
#define	EGP_START_LONG	EGP_P5		/* Retry neighbor in an hour */

/* Hello interval constants */

#define MAXHELLOINT	900		/* Maximum hello interval, sec. */
#define HELLOMARGIN	2		/* Margin in hello interval to allow for delay variation in */
					/* the network */
/* Poll interval constants */

#define MAXPOLLINT  	3600		/* Maximum poll interval, sec. */

/* repoll interval is set to the hello interval for the particular neighbor */

/* Reachability test constants */

#define REACH_RATIO	4		/* No. commands sent on which reachability is based */
#define MAXNOUPDATE	3		/* Maximum # successive polls (new id) for which no update */
					/* was received before cease  and try to acquire an alternative */

#define	RATE_WINDOW	4		/* Size of polling rate window */
#define	RATE_MAX	3		/* Number of violations before generating an error message */


/* Limits of gateways per update */
#define	EGP_GATEWAY_MAX		255

/* Limits of EGP distance */
#define	EGP_DISTANCE_MIN	0
#define	EGP_DISTANCE_MAX	255

/* Limits of EGP networks per distance */
#define	EGP_ROUTES_MAX		255


/*
 * %(Copyright)
 */
