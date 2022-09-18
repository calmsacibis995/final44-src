h28225
s 00002/00002/00321
d D 8.1 93/06/06 14:46:58 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00322
d D 1.5 90/06/01 16:04:45 bostic 5 4
c new copyright notice
e
s 00010/00005/00323
d D 1.4 88/06/29 19:23:25 bostic 4 3
c install approved copyright notice
e
s 00014/00002/00314
d D 1.3 88/05/05 17:50:26 bostic 3 2
c add Berkeley specific header; written by K. McKusick and P. Kessler
e
s 00005/00005/00311
d D 1.2 86/01/07 00:04:59 sam 2 1
c everyone wants to rename calls to callf (or similar), make it just findcall
e
s 00316/00000/00000
d D 1.1 86/01/07 00:01:12 sam 1 0
c date and time created 86/01/07 00:01:12 by sam
e
u
U
t
T
I 3
/*
D 6
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
D 5
 * Redistribution and use in source and binary forms are permitted
D 4
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 4
I 4
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
E 5
I 5
 * %sccs.include.redist.c%
E 5
E 4
 */

E 3
I 1
#ifndef lint
D 3
static	char *sccsid = "%W% (Berkeley) %G%";
#endif not lint
E 3
I 3
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 3

#include	"gprof.h"

    /*
     *	a namelist entry to be the child of indirect callf
     */
nltype	indirectchild = {
	"(*)" ,				/* the name */
	(unsigned long) 0 ,		/* the pc entry point */
	(unsigned long) 0 ,		/* entry point aligned to histogram */
	(double) 0.0 ,			/* ticks in this routine */
	(double) 0.0 ,			/* cumulative ticks in children */
	(long) 0 ,			/* how many times called */
	(long) 0 ,			/* how many calls to self */
	(double) 1.0 ,			/* propagation fraction */
	(double) 0.0 ,			/* self propagation time */
	(double) 0.0 ,			/* child propagation time */
	(bool) 0 ,			/* print flag */
	(int) 0 ,			/* index in the graph list */
	(int) 0 , 			/* graph call chain top-sort order */
	(int) 0 ,			/* internal number of cycle on */
	(struct nl *) &indirectchild ,	/* pointer to head of cycle */
	(struct nl *) 0 ,		/* pointer to next member of cycle */
	(arctype *) 0 ,			/* list of caller arcs */
	(arctype *) 0 			/* list of callee arcs */
    };

operandenum
operandmode( modep )
    unsigned char	*modep;
{
    long	usesreg = ((long)*modep) & 0xf;
    
    switch ( ((long)*modep) >> 4 ) {
	case 0:
	case 1:
	case 2:
	case 3:
	    return literal;
	case 4:
	    return indexed;
	case 5:
	    return reg;
	case 6:
	    return regdef;
	case 7:
	    return autodec;
	case 8:
	    return ( usesreg != 0xe ? autoinc : immediate );
	case 9:
	    return ( usesreg != PC ? autoincdef : absolute );
	case 10:
	    return ( usesreg != PC ? bytedisp : byterel );
	case 11:
	    return ( usesreg != PC ? bytedispdef : bytereldef );
	case 12:
	    return ( usesreg != PC ? worddisp : wordrel );
	case 13:
	    return ( usesreg != PC ? worddispdef : wordreldef );
	case 14:
	    return ( usesreg != PC ? longdisp : longrel );
	case 15:
	    return ( usesreg != PC ? longdispdef : longreldef );
    }
    /* NOTREACHED */
}

char *
operandname( mode )
    operandenum	mode;
{
    
    switch ( mode ) {
	case literal:
	    return "literal";
	case indexed:
	    return "indexed";
	case reg:
	    return "register";
	case regdef:
	    return "register deferred";
	case autodec:
	    return "autodecrement";
	case autoinc:
	    return "autoincrement";
	case autoincdef:
	    return "autoincrement deferred";
	case bytedisp:
	    return "byte displacement";
	case bytedispdef:
	    return "byte displacement deferred";
	case byterel:
	    return "byte relative";
	case bytereldef:
	    return "byte relative deferred";
	case worddisp:
	    return "word displacement";
	case worddispdef:
	    return "word displacement deferred";
	case wordrel:
	    return "word relative";
	case wordreldef:
	    return "word relative deferred";
	case immediate:
	    return "immediate";
	case absolute:
	    return "absolute";
	case longdisp:
	    return "long displacement";
	case longdispdef:
	    return "long displacement deferred";
	case longrel:
	    return "long relative";
	case longreldef:
	    return "long relative deferred";
    }
    /* NOTREACHED */
}

long
operandlength( modep )
    unsigned char	*modep;
{
    
    switch ( operandmode( modep ) ) {
	case literal:
	case reg:
	case regdef:
	case autodec:
	case autoinc:
	case autoincdef:
	    return 1;
	case bytedisp:
	case bytedispdef:
	case byterel:
	case bytereldef:
	    return 2;
	case worddisp:
	case worddispdef:
	case wordrel:
	case wordreldef:
	    return 3;
	case immediate:
	case absolute:
	case longdisp:
	case longdispdef:
	case longrel:
	case longreldef:
	    return 5;
	case indexed:
	    return 1+operandlength( modep + 1 );
    }
    /* NOTREACHED */
}

unsigned long
reladdr( modep )
    char	*modep;
{
    operandenum	mode = operandmode( modep );
    char	*cp;
    short	*sp;
    long	*lp;
    int		i;
    long	value = 0;

    cp = modep;
    cp += 1;			/* skip over the mode */
    switch ( mode ) {
	default:
	    fprintf( stderr , "[reladdr] not relative address\n" );
	    return (unsigned long) modep;
	case byterel:
	    return (unsigned long) ( cp + sizeof *cp + *cp );
	case wordrel:
	    for (i = 0; i < sizeof *sp; i++)
		value = (value << 8) + (cp[i] & 0xff);
	    return (unsigned long) ( cp + sizeof *sp + value );
	case longrel:
	    for (i = 0; i < sizeof *lp; i++)
		value = (value << 8) + (cp[i] & 0xff);
	    return (unsigned long) ( cp + sizeof *lp + value );
    }
}

D 2
findcallf( parentp , p_lowpc , p_highpc )
E 2
I 2
findcall( parentp , p_lowpc , p_highpc )
E 2
    nltype		*parentp;
    unsigned long	p_lowpc;
    unsigned long	p_highpc;
{
    unsigned char	*instructp;
    long		length;
    nltype		*childp;
    operandenum		mode;
    operandenum		firstmode;
    unsigned long	destpc;

    if ( textspace == 0 ) {
	return;
    }
    if ( p_lowpc < s_lowpc ) {
	p_lowpc = s_lowpc;
    }
    if ( p_highpc > s_highpc ) {
	p_highpc = s_highpc;
    }
#   ifdef DEBUG
	if ( debug & CALLDEBUG ) {
D 2
	    printf( "[findcallf] %s: 0x%x to 0x%x\n" ,
E 2
I 2
	    printf( "[findcall] %s: 0x%x to 0x%x\n" ,
E 2
		    parentp -> name , p_lowpc , p_highpc );
	}
#   endif DEBUG
    for (   instructp = textspace + p_lowpc ;
	    instructp < textspace + p_highpc ;
	    instructp += length ) {
	length = 1;
	if ( *instructp == CALLF ) {
		/*
		 *	maybe a callf, better check it out.
		 *	skip the count of the number of arguments.
		 */
#	    ifdef DEBUG
		if ( debug & CALLDEBUG ) {
D 2
		    printf( "[findcallf]\t0x%x:callf" , instructp - textspace );
E 2
I 2
		    printf( "[findcall]\t0x%x:callf" , instructp - textspace );
E 2
		}
#	    endif DEBUG
	    firstmode = operandmode( instructp+length );
	    switch ( firstmode ) {
		case literal:
		case immediate:
		    break;
		default:
		    goto botched;
	    }
	    length += operandlength( instructp+length );
	    mode = operandmode( instructp + length );
#	    ifdef DEBUG
		if ( debug & CALLDEBUG ) {
		    printf( "\tfirst operand is %s", operandname( firstmode ) );
		    printf( "\tsecond operand is %s\n" , operandname( mode ) );
		}
#	    endif DEBUG
	    switch ( mode ) {
		case regdef:
		case bytedispdef:
		case worddispdef:
		case longdispdef:
		case bytereldef:
		case wordreldef:
		case longreldef:
			/*
			 *	indirect call: call through pointer
			 *	either	*d(r)	as a parameter or local
			 *		(r)	as a return value
			 *		*f	as a global pointer
			 *	[are there others that we miss?,
			 *	 e.g. arrays of pointers to functions???]
			 */
		    addarc( parentp , &indirectchild , (long) 0 );
		    length += operandlength( instructp + length );
		    continue;
		case byterel:
		case wordrel:
		case longrel:
			/*
			 *	regular pc relative addressing
			 *	check that this is the address of 
			 *	a function.
			 */
		    destpc = reladdr( instructp+length )
				- (unsigned long) textspace;
		    if ( destpc >= s_lowpc && destpc <= s_highpc ) {
			childp = nllookup( destpc );
#			ifdef DEBUG
			    if ( debug & CALLDEBUG ) {
D 2
				printf( "[findcallf]\tdestpc 0x%x" , destpc );
E 2
I 2
				printf( "[findcall]\tdestpc 0x%x" , destpc );
E 2
				printf( " childp->name %s" , childp -> name );
				printf( " childp->value 0x%x\n" ,
					childp -> value );
			    }
#			endif DEBUG
			if ( childp -> value == destpc ) {
				/*
				 *	a hit
				 */
			    addarc( parentp , childp , (long) 0 );
			    length += operandlength( instructp + length );
			    continue;
			}
			goto botched;
		    }
			/*
			 *	else:
			 *	it looked like a callf,
			 *	but it wasn't to anywhere.
			 */
		    goto botched;
		default:
		botched:
			/*
			 *	something funny going on.
			 */
#		    ifdef DEBUG
			if ( debug & CALLDEBUG ) {
D 2
			    printf( "[findcallf]\tbut it's a botch\n" );
E 2
I 2
			    printf( "[findcall]\tbut it's a botch\n" );
E 2
			}
#		    endif DEBUG
		    length = 1;
		    continue;
	    }
	}
    }
}
E 1
