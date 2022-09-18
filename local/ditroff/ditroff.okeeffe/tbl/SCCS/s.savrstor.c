h55288
s 00000/00000/00129
d D 1.5 93/07/27 09:16:27 bostic 5 4
c checkpoint; Mike Karels left this checked out.
e
s 00013/00015/00116
d D 1.4 87/12/01 00:38:55 jaap 4 3
c Andries fixed the linedrawing, at least he says so
e
s 00001/00000/00130
d D 1.3 86/11/10 15:36:51 jaap 3 2
c Just updating
e
s 00001/00004/00129
d D 1.2 85/10/02 14:39:03 jaap 2 1
c Removed a lot of commented out debug code, takes now -d argument
c for debug output. some tidy up.
e
s 00133/00000/00000
d D 1.1 85/10/01 18:09:19 jaap 1 0
c date and time created 85/10/01 18:09:19 by jaap
e
u
U
t
T
I 1
#ifndef lint
D 4
static char sccsid[] = "%W% (CWI) %E%";
E 4
I 4
static char sccsid[] = "@(#)savrstor.c	1.3 (CWI) 86/11/10";
E 4
#endif lint

D 2

 /* tf.c: save and restore fill mode around table */

E 2
#include "defs.h"
#include "ext.h"

/*
 * remembers various things: fill mode, vs, ps in mac 35(SF)
 */
savefill()
{
	printf(".de %d\n", SF);
	printf(".ps \\n(.s\n");
	printf(".vs \\n(.vu\n");
	printf(".in \\n(.iu\n");
	printf(".if \\n(.u .fi\n");
	printf(".if \\n(.j .ad\n");
	printf(".if \\n(.j=0 .na\n");
	printf("..\n");
	printf(".nf\n");
D 4
	/*
	 * set obx offset if useful
	 * 
	printf(".nr #~ 0\n");
	 *
	 * JNA, the offset is used to set the vertical line to the left
	 *
	 * I'll introduce register #| to offset the horizontal lines
	 * a bit up
	 */
E 4
I 4

	/* #| and #~ give the offsets for hor. and vert. lines
	   (in hundredths of an n) */
E 4
	switch(device){
	case HARRIS:
D 4
		printf(".nr #~ 0.24n\n");
		printf(".nr #| 0.1n\n");
E 4
I 4
		printf(".nr #~ 24\n");
		printf(".nr #| 46\n");
E 4
		printf(".nr Tw 22.5c\n");
		break;
	case CAT:
	case DEVVER:
I 3
D 4
	case DEVPSC:
E 4
I 4
	default:
E 4
E 3
		printf(".nr #~ 0\n");
		printf(".nr #| 0\n");
		printf(".nr Tw 7.65i\n");
		break;
I 4
	case DEVPSC:
		printf(".nr #~ 0-5\n");
		printf(".nr #| 8\n");
		printf(".nr Tw 7.65i\n");
		break;
E 4
	}
	
	/*
	 * This is the offset for the T450 boxes see drawvert()
	 */
D 4
	printf(".if \\n(.T .if n .nr #~ 0.6n\n");
E 4
I 4
	printf(".if \\n(.T .if n .nr #~ 60\n");
E 4
}

/*
 * Call the macro SF (35) to restore collected data
 */
rstofill()
{
	printf(".%d\n", SF);
}

/*
 * Clean up at end of file?
 */
endoff()
{
D 2
	int i;
E 2
I 2
	register int i;
E 2
	/*
	 * make some registers to be 0 ...
	 */
	for(i = 0; i < MAXHEAD; i++)
		if(linestop[i])
			printf(".nr #%c 0\n", 'a' + i);
	/*
	 * and remove used macros, strings (and diversions?)
	 */
	for(i = 0; i < texct; i++)
		printf(".rm %c+\n", texstr[i]);
	printf("%s\n", last);
}

/*
 * Let's check wether we are in a diversion
 */
ifdivert()
{
	/*
	 * #d hold current vertical place if in a diversion
	 */
	printf(".ds #d .d\n");
	/*
	 * if diversion doesn't exist, rememenber current vertical
	 * place (nl) in #d
	 */
	printf(".if \\(ts\\n(.z\\(ts\\(ts .ds #d nl\n");
}

/*
 * save current input line number (of troff), since we are going to add a lot of
 * lines
 *
 * Note that register b. is never set to be auto incremeted, so this
 * garanteed to fail!!! (jna)
 *
 * (should be replaced with a request for new troff)
 */
saveline()
{
	printf(".if \\n+(b.=1 .nr d. \\n(.c-\\n(c.-1\n");
	linstart = iline;
}

/*
 * rstore line count of troff
 */
restline()
{
	printf(".if \\n-(b.=0 .nr c. \\n(.c-\\n(d.-%d\n", iline - linstart);
	linstart = 0;
	/*
	 * support for .lf request of troff (jna)
	 */
	printf(".lf %d\n", iline);
}

/*
 * Turn the field mechanism off
 */
cleanfc()
{
	printf(".fc\n");
}
E 1
