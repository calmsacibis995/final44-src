/*
 * Define constants and structures for the KSI/Odetics TPRO IRIG board.
 */
#ifndef EXT_CLOCK
#define EXT_CLOCK
#endif /* EXT_CLOCK */

/*
 * Note: The physical address adventure assumes the board must be in
 * slot 1. This should be fixed.
 */
#define	TPRO_ADDR	0xfa008000 	/* physical address of regs */
#define MAXDIFF		1000		/* max tpro - system time difference */
#define	DAY		86400		/* seconds in a day */
#define	DAY_YEAR	31536000	/* seconds in a normal year */
#define	DAY_CYCLE	126230400	/* seconds in a leap cycle */

/*
 * Status register decode (tprostat)
 */
#define	TPRO_READY	0x01		/* output not ready */
#define	TPRO_SIG	0x02		/* IRIG signal okay */
#define	TPRO_SYNC	0x04		/* IRIG sync okay */

/*
 * Error return codes
 */
#define	ENOSIG		-4		/* lost IRIG signal */
#define	ENOSYNC		-3		/* lost IRIG sync */
#define	EBADDATA	-2		/* invalid IRIG data */
#define EBADTIME	-1		/* invalid IRIG time */

/*
 * Data/status registers
 */
#ifndef	LOCORE
struct tproregs {
	u_long	tprolo;		/* low-order toy - read first */
	u_long	tprohi;		/* high-order toy - read last */
	u_char	tprocom;	/* command register */
	u_char	tproevt;	/* internal event */
	u_char	tprofifo;	/* fifo */
	u_char	tprostat;	/* status */
};
#endif	/* LOCORE */
