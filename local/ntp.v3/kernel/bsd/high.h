/*
 * Define constants and structures for the Highball board.
 */
#ifndef EXT_CLOCK
#define EXT_CLOCK
#endif /* EXT_CLOCK */

/*
 * Ominous note: the register address is valid only for slot 1.
 */
#define	HIGH_ADDR	0xfa800000 	/* physical address of regs */
#define MAXDIFF		1000		/* max system - hightime (s) */

/*
 * Control/status register decode
 */
#define DIV5		0		/* divide by 5 */
#define DIV4		2		/* divide by 4 */
#define DIV6		3		/* divide by 6 */

/*
 * Error return codes
 */
#define EBADTIME        -1              /* invalid highball time */

/*
 * Data/control/status registers
 */
#ifndef	LOCORE
struct highregs {
	u_long	csr;		/* control/status register */
	u_long	cnt_w0;		/* counter bits [0:15] latched */
	u_long	cnt_w1;		/* counter bits [16:17] */
	u_long	cnt_w2;		/* counter bits [32:47] */
	u_long	cnt_w3;		/* counter bits [48:63] */
	u_long	padding[2];	/* (barf, gag) */
	u_long	clock_strobe;	/* latch counter (write only) */
};
#endif	/* !LOCORE */
