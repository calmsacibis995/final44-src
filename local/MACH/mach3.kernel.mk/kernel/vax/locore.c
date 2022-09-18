/*
 * Low core for VAX.
 */

/*
 * This C module is really assembler code.  It includes the various
 * pieces of assembler code in the proper sequence.
 */

#include <bi.h>

#include "assym.s"

#include <vax/rpb.s>
#include <vax/scb.s>
#if	NBI > 0
#include <vax/biscb.s>
#endif

#include "ubvec.s"

#include <vax/locore.s>		/* split this up more */
#if	NBI > 0
#include <vax/biglue.s>
#endif

#include "ubglue.s"
