h46743
s 00005/00000/01072
d D 5.8 91/07/30 16:32:05 mckusick 8 7
c implement $unsafecall (4.3BSD-reno/pgrm/3)
e
s 00002/00000/01070
d D 5.7 91/07/30 15:35:00 mckusick 7 6
c avoid trashing fp when doing "call" (4.3BSD-reno/pgrm/1)
e
s 00002/00002/01068
d D 5.6 91/01/27 12:16:25 torek 6 5
c stdio has changed; flushoutput must change correspondingly
e
s 00001/00011/01069
d D 5.5 90/06/01 16:05:59 bostic 5 4
c new copyright notice
e
s 00015/00006/01065
d D 5.4 89/05/23 10:21:38 bostic 4 3
c add Berkeley specific copyright notice
e
s 00038/00012/01033
d D 5.3 88/01/12 01:14:26 donn 3 2
c merge in latest Linton version
e
s 00000/00001/01045
d D 5.2 86/02/23 16:20:04 sam 2 1
c delete include file found in tahoe.c
e
s 01046/00000/00000
d D 5.1 86/02/22 23:39:27 sam 1 0
c date and time created 86/02/22 23:39:27 by sam
e
u
U
t
T
I 1
/*
D 4
 * Copyright (c) 1985 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 4
I 4
 * Copyright (c) 1985 The Regents of the University of California.
 * All rights reserved.
 *
D 5
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
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 5
I 5
 * %sccs.include.redist.c%
E 5
E 4
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 4
#endif not lint

D 3
static char rcsid[] = "$Header: runtime.c,v 1.5 84/12/26 10:41:52 linton Exp $";
E 3
I 3
static char rcsid[] = "$Header: runtime.tahoe.c,v 1.6 88/01/11 21:26:56 donn Exp $";
E 4
I 4
#endif /* not lint */
E 4
E 3

/*
 * Runtime organization dependent routines, mostly dealing with
 * activation records.
 */

#include "defs.h"
#include "runtime.h"
#include "process.h"
#include "machine.h"
#include "events.h"
#include "mappings.h"
#include "symbols.h"
#include "tree.h"
#include "eval.h"
#include "operators.h"
#include "object.h"
D 2
#include <sys/param.h>
E 2

#ifndef public
#include "machine.h"

typedef struct Frame {
    Address save_pc;		/* program counter */
    integer mask:16;		/* register save mask */
    integer removed:16;		/* 4*number of arguments + 4 */
    Address save_fp;		/* frame pointer */
#define NSAVEREG 13
    Word save_reg[NSAVEREG];	/* not necessarily there */
} *Frame;
#endif

private Frame curframe = nil;
private struct Frame curframerec;
private Boolean walkingstack = false;

#define frameeq(f1, f2) ((f1)->save_fp == (f2)->save_fp)

D 3
#define isstackaddr(addr) \
E 3
I 3
#define inSignalHandler(addr) \
E 3
    (((addr) < 0xc0000000) and ((addr) > 0xc0000000 - 0x400 * UPAGES))

typedef struct {
    Node callnode;
    Node cmdnode;
    boolean isfunc;
} CallEnv;

private CallEnv endproc;

/*
 * Set a frame to the current activation record.
 */

private getcurframe(frp)
Frame frp;
{
    register int i;
    long x;

    checkref(frp);
    frp->save_fp = reg(FRP);
    dread(&x, frp->save_fp-4, 4);
    frp->mask = x >> 16;
    frp->removed = x & 0xffff;
    frp->save_pc = reg(PROGCTR);
    for (i = 0; i < NSAVEREG; i++) {
	frp->save_reg[i] = reg(i);
    }
}

/*
 * Get the saved registers from one frame to another
 * given mask specifying which registers were actually saved.
 */

#define bis(b, n) ((b & (1 << (n))) != 0)

private getsaveregs (newfrp, frp, mask)
Frame newfrp, frp;
integer mask;
{
    integer i, j;

    j = 0;
    for (i = 0; i < NSAVEREG; i++) {
	if (bis(mask, i)) {
	    newfrp->save_reg[i] = frp->save_reg[j];
	    ++j;
	}
    }
}

/*
 * Return a pointer to the next activation record up the stack.
 * Return nil if there is none.
 * Writes over space pointed to by given argument.
 */

private Frame nextframe(frp)
Frame frp;
{
    Frame newfrp;
    struct Frame frame;
    long x;
D 3
    Address prev_frame, callpc; 
E 3
I 3
    Address prev_frame, callpc;
E 3
    static integer ntramp = 0;

    newfrp = frp;
    prev_frame = frp->save_fp;

/*
 *  The check for interrupt generated frames is taken from adb with only
 *  partial understanding.  If you're in "sub" and on a sigxxx "sigsub"
 *  gets control, then the stack does NOT look like <main, sub, sigsub>.
 *
 *  As best I can make out it looks like:
 *
 *     <main, (machine check exception block + sub), sysframe, sigsub>.
 *
 *  When the signal occurs an exception block and a frame for the routine
 *  in which it occured are pushed on the user stack.  Then another frame
 *  is pushed corresponding to a call from the kernel to sigsub.
 *
 *  The addr in sub at which the exception occured is not in sub.save_pc
 *  but in the machine check exception block.  It is at the magic address
 *  fp + 84.
 *
 *  The current approach ignores the sys_frame (what adb reports as sigtramp)
 *  and takes the pc for sub from the exception block.  This allows the
 *  "where" command to report <main, sub, sigsub>, which seems reasonable.
 */

nextf:
    dread(&frame, prev_frame-8, sizeof(struct Frame));
    if (ntramp == 1) {
	dread(&callpc, prev_frame+44, sizeof(callpc));
    } else {
	callpc = frame.save_pc;
    }
    if (frame.save_fp == nil or frame.save_pc == (Address) -1) {
	newfrp = nil;
D 3
    } else if (isstackaddr(callpc)) {
E 3
I 3
    } else if (inSignalHandler(callpc)) {
E 3
	ntramp++;
	prev_frame = frame.save_fp;
	goto nextf;
    } else {
        ntramp = 0;
	getsaveregs(newfrp, &frame, frame.mask);
	dread(&x, frame.save_fp-4, sizeof (x));
	newfrp->mask = x >> 16;
	newfrp->removed = x & 0xffff;
	newfrp->save_fp = frame.save_fp;
	newfrp->save_pc = callpc;
    }
    return newfrp;
}

/*
 * Get the current frame information in the given Frame and store the
 * associated function in the given value-result parameter.
 */

private getcurfunc (frp, fp)
Frame frp;
Symbol *fp;
{
    getcurframe(frp);
    *fp = whatblock(frp->save_pc);
}

/*
 * Return the frame associated with the next function up the call stack, or
 * nil if there is none.  The function is returned in a value-result parameter.
 * For "inline" functions the statically outer function and same frame
 * are returned.
 */

public Frame nextfunc (frp, fp)
Frame frp;
Symbol *fp;
{
    Symbol t;
    Frame nfrp;

    t = *fp;
    checkref(t);
    if (isinline(t)) {
	t = container(t);
	nfrp = frp;
    } else {
	nfrp = nextframe(frp);
	if (nfrp == nil) {
	    t = nil;
	} else {
	    t = whatblock(nfrp->save_pc);
	}
    }
    *fp = t;
    return nfrp;
}

/*
 * Return the frame associated with the given function.
 * If the function is nil, return the most recently activated frame.
 *
 * Static allocation for the frame.
 */

public Frame findframe(f)
Symbol f;
{
    Frame frp;
    static struct Frame frame;
    Symbol p;
    Boolean done;

    frp = &frame;
    getcurframe(frp);
    if (f != nil) {
	if (f == curfunc and curframe != nil) {
	    *frp = *curframe;
	} else {
	    done = false;
	    p = whatblock(frp->save_pc);
	    do {
		if (p == f) {
		    done = true;
		} else if (p == program) {
		    done = true;
		    frp = nil;
		} else {
		    frp = nextfunc(frp, &p);
		    if (frp == nil) {
			done = true;
		    }
		}
	    } while (not done);
	}
    }
    return frp;
}

/*
 * Set the registers according to the given frame pointer.
 */

public getnewregs (addr)
Address addr;
{
    struct Frame frame;
    integer i, j, mask;

    dread(&frame, addr-8, sizeof(frame));
    setreg(FRP, frame.save_fp);
    setreg(PROGCTR, frame.save_pc);
    mask = frame.mask;
    j = 0;
    for (i = 0; i < NSAVEREG; i++) {
	if (bis(mask, i)) {
	    setreg(i, frame.save_reg[j]);
	    ++j;
	}
    }
    pc = frame.save_pc;
    setcurfunc(whatblock(pc));
}

/*
 * Find the return address of the current procedure/function.
 */

public Address return_addr()
{
    Frame frp;
    Address addr;
    struct Frame frame;

    frp = &frame;
    getcurframe(frp);
    frp = nextframe(frp);
    if (frp == nil) {
	addr = 0;
    } else {
	addr = frp->save_pc;
    }
    return addr;
}

/*
 * Push the value associated with the current function.
 */

public pushretval(len, isindirect)
integer len;
boolean isindirect;
{
    Word r0;

    r0 = reg(0);
    if (isindirect) {
	rpush((Address) r0, len);
    } else {
	switch (len) {
	    case sizeof(char):
		push(char, r0);
		break;

	    case sizeof(short):
		push(short, r0);
		break;

	    default:
		if (len == sizeof(Word)) {
		    push(Word, r0);
		} else if (len == 2*sizeof(Word)) {
		    push(Word, r0);
		    push(Word, reg(1));
		} else {
		    error("[internal error: bad size %d in pushretval]", len);
		}
		break;
	}
    }
}

/*
 * Return the base address for locals in the given frame.
 */

public Address locals_base(frp)
Frame frp;
{
    return (frp == nil ? reg(FRP) : frp->save_fp);
}

/*
 * Return the base address for arguments in the given frame.
 */

public Address args_base(frp)
Frame frp;
{
    return (frp == nil ? reg(FRP) : frp->save_fp);
}

/*
 * Return saved register n from the given frame.
 */

public Word savereg(n, frp)
integer n;
Frame frp;
{
    Word w;

    if (frp == nil) {
	w = reg(n);
    } else {
	switch (n) {

	    case FRP:
		w = frp->save_fp;
		break;

	    case STKP:
		w = reg(STKP);
		break;

	    case PROGCTR:
		w = frp->save_pc;
		break;

	    default:
		assert(n >= 0 and n < NSAVEREG);
		w = frp->save_reg[n];
		break;
	}
    }
    return w;
}

/*
 * Return the nth argument to the current procedure.
 */

public Word argn(n, frp)
integer n;
Frame frp;
{
I 3
    Address argaddr;
E 3
    Word w;

D 3
    dread(&w, args_base(frp) + (n * sizeof(Word)), sizeof(w));
E 3
I 3
    argaddr = args_base(frp) + (n * sizeof(Word));
    dread(&w, argaddr, sizeof(w));
E 3
    return w;
}

/*
 * Print a list of currently active blocks starting with most recent.
 */

public wherecmd()
{
    walkstack(false);
}

/*
 * Print the variables in the given frame or the current one if nil.
 */

public dump (func)
Symbol func;
{
    Symbol f;
    Frame frp;

    if (func == nil) {
	f = curfunc;
	if (curframe != nil) {
	    frp = curframe;
	} else {
	    frp = findframe(f);
	}
    } else {
	f = func;
	frp = findframe(f);
    }
    showaggrs = true;
    printcallinfo(f, frp);
    dumpvars(f, frp);
}

/*
 * Dump all values.
 */

public dumpall ()
{
    walkstack(true);
}

/*
 * Walk the stack of active procedures printing information
 * about each active procedure.
 */

private walkstack(dumpvariables)
Boolean dumpvariables;
{
    Frame frp;
    boolean save;
    Symbol f;
    struct Frame frame;

    if (notstarted(process) or isfinished(process)) {
	error("program is not active");
    } else {
	save = walkingstack;
	walkingstack = true;
	showaggrs = dumpvariables;
	frp = &frame;
	getcurfunc(frp, &f);
	for (;;) {
	    printcallinfo(f, frp);
	    if (dumpvariables) {
		dumpvars(f, frp);
		putchar('\n');
	    }
	    frp = nextfunc(frp, &f);
	    if (frp == nil or f == program) {
		break;
	    }
	}
	if (dumpvariables) {
	    printf("in \"%s\":\n", symname(program));
	    dumpvars(program, nil);
	    putchar('\n');
	}
	walkingstack = save;
    }
}

/*
 * Print out the information about a call, i.e.,
 * routine name, parameter values, and source location.
 */

private printcallinfo (f, frp)
Symbol f;
Frame frp;
{
    Lineno line;
    Address savepc;

    savepc = frp->save_pc;
    if (frp->save_fp != reg(FRP)) {
	savepc -= 1;
    }
    printname(stdout, f);
    if (not isinline(f)) {
	printparams(f, frp);
    }
    line = srcline(savepc);
    if (line != 0) {
	printf(", line %d", line);
	printf(" in \"%s\"\n", srcfilename(savepc));
    } else {
	printf(" at 0x%x\n", savepc);
    }
}

/*
 * Set the current function to the given symbol.
 * We must adjust "curframe" so that subsequent operations are
 * not confused; for simplicity we simply clear it.
 */

public setcurfunc (f)
Symbol f;
{
    curfunc = f;
    curframe = nil;
}

/*
 * Return the frame for the current function.
 * The space for the frame is allocated statically.
 */

public Frame curfuncframe ()
{
    static struct Frame frame;
    Frame frp;

    if (curframe == nil) {
	frp = findframe(curfunc);
	curframe = &curframerec;
	*curframe = *frp;
    } else {
	frp = &frame;
	*frp = *curframe;
    }
    return frp;
}

/*
 * Set curfunc to be N up/down the stack from its current value.
 */

public up (n)
integer n;
{
    integer i;
    Symbol f;
    Frame frp;
    boolean done;

    if (not isactive(program)) {
	error("program is not active");
    } else if (curfunc == nil) {
	error("no current function");
    } else {
	i = 0;
	f = curfunc;
	frp = curfuncframe();
	done = false;
	do {
	    if (frp == nil) {
		done = true;
		error("not that many levels");
	    } else if (i >= n) {
		done = true;
		curfunc = f;
		curframe = &curframerec;
		*curframe = *frp;
		showaggrs = false;
		printcallinfo(curfunc, curframe);
	    } else if (f == program) {
		done = true;
		error("not that many levels");
	    } else {
		frp = nextfunc(frp, &f);
	    }
	    ++i;
	} while (not done);
    }
}

public down (n)
integer n;
{
    integer i, depth;
    Frame frp, curfrp;
    Symbol f;
    struct Frame frame;

    if (not isactive(program)) {
	error("program is not active");
    } else if (curfunc == nil) {
	error("no current function");
    } else {
	depth = 0;
	frp = &frame;
	getcurfunc(frp, &f);
	if (curframe == nil) {
	    curfrp = findframe(curfunc);
	    curframe = &curframerec;
	    *curframe = *curfrp;
	}
	while ((f != curfunc or !frameeq(frp, curframe)) and f != nil) {
	    frp = nextfunc(frp, &f);
	    ++depth;
	}
	if (f == nil or n > depth) {
	    error("not that many levels");
	} else {
	    depth -= n;
	    frp = &frame;
	    getcurfunc(frp, &f);
	    for (i = 0; i < depth; i++) {
		frp = nextfunc(frp, &f);
		assert(frp != nil);
	    }
	    curfunc = f;
	    *curframe = *frp;
	    showaggrs = false;
	    printcallinfo(curfunc, curframe);
	}
    }
}

/*
 * Find the entry point of a procedure or function.
 */

public findbeginning (f)
Symbol f;
{
    if (isinternal(f)) {
	f->symvalue.funcv.beginaddr += 15;
    } else {
D 3
	f->symvalue.funcv.beginaddr += 2;
E 3
I 3
	f->symvalue.funcv.beginaddr += FUNCOFFSET;
E 3
    }
}

/*
 * Return the address corresponding to the first line in a function.
 */

public Address firstline(f)
Symbol f;
{
    Address addr;

    addr = codeloc(f);
    while (linelookup(addr) == 0 and addr < objsize) {
	++addr;
    }
    if (addr == objsize) {
	addr = -1;
    }
    return addr;
}

/*
 * Catcher drops strike three ...
 */

public runtofirst()
{
D 3
    Address addr;
E 3
I 3
    Address addr, endaddr;
E 3

    addr = pc;
D 3
    while (linelookup(addr) == 0 and addr < objsize) {
E 3
I 3
    endaddr = objsize + CODESTART;
    while (linelookup(addr) == 0 and addr < endaddr) {
E 3
	++addr;
    }
D 3
    if (addr < objsize) {
E 3
I 3
    if (addr < endaddr) {
E 3
	stepto(addr);
    }
}

/*
 * Return the address corresponding to the end of the program.
 *
 * We look for the entry to "exit".
 */

public Address lastaddr()
{
    Symbol s;

    s = lookup(identname("exit", true));
    if (s == nil) {
	panic("can't find exit");
    }
    return codeloc(s);
}

/*
 * Decide if the given function is currently active.
 *
 * We avoid calls to "findframe" during a stack trace for efficiency.
 * Presumably information evaluated while walking the stack is active.
 */

D 3
public Boolean isactive(f)
E 3
I 3
public Boolean isactive (f)
E 3
Symbol f;
{
    Boolean b;

    if (isfinished(process)) {
	b = false;
    } else {
D 3
	if (walkingstack or f == program or
E 3
I 3
	if (walkingstack or f == program or f == nil or
E 3
	  (ismodule(f) and isactive(container(f)))) {
	    b = true;
	} else {
	    b = (Boolean) (findframe(f) != nil);
	}
    }
    return b;
}

/*
 * Evaluate a call to a procedure.
 */

public callproc(exprnode, isfunc)
Node exprnode;
boolean isfunc;
{
    Node procnode, arglist;
    Symbol proc;
    integer argc;

    procnode = exprnode->value.arg[0];
    arglist = exprnode->value.arg[1];
    if (procnode->op != O_SYM) {
	beginerrmsg();
	fprintf(stderr, "can't call \"");
	prtree(stderr, procnode);
	fprintf(stderr, "\"");
	enderrmsg();
    }
    assert(procnode->op == O_SYM);
    proc = procnode->value.sym;
    if (not isblock(proc)) {
	error("\"%s\" is not a procedure or function", symname(proc));
    }
    endproc.isfunc = isfunc;
    endproc.callnode = exprnode;
    endproc.cmdnode = topnode;
    pushenv();
    pc = codeloc(proc);
    argc = pushargs(proc, arglist);
I 3
    setreg(FRP, 1);	/* have to ensure it's non-zero for return_addr() */
E 3
    beginproc(proc, argc);
    event_once(
	build(O_EQ, build(O_SYM, pcsym), build(O_SYM, retaddrsym)),
	buildcmdlist(build(O_PROCRTN, proc))
    );
    isstopped = false;
    if (not bpact()) {
	isstopped = true;
	cont(0);
    }
    /*
     * bpact() won't return true, it will call printstatus() and go back
     * to command input if a breakpoint is found.
     */
    /* NOTREACHED */
}

/*
 * Push the arguments on the process' stack.  We do this by first
 * evaluating them on the "eval" stack, then copying into the process'
 * space.
 */

private integer pushargs(proc, arglist)
Symbol proc;
Node arglist;
{
    Stack *savesp;
    int argc, args_size;

    savesp = sp;
I 8
    if (varIsSet("$unsafecall")) {
	argc = unsafe_evalargs(proc, arglist);
    } else {
	argc = evalargs(proc, arglist);
    }
E 8
    argc = evalargs(proc, arglist);
    args_size = sp - savesp;
    setreg(STKP, reg(STKP) - args_size);
    dwrite(savesp, reg(STKP), args_size);
    sp = savesp;
    return argc;
}

/*
 * Check to see if an expression is correct for a given parameter.
 * If the given parameter is false, don't worry about type inconsistencies.
 *
 * Return whether or not it is ok.
 */

private boolean chkparam (actual, formal, chk)
Node actual;
Symbol formal;
boolean chk;
{
    boolean b;

    b = true;
    if (chk) {
	if (formal == nil) {
	    beginerrmsg();
	    fprintf(stderr, "too many parameters");
	    b = false;
	} else if (not compatible(formal->type, actual->nodetype)) {
	    beginerrmsg();
	    fprintf(stderr, "type mismatch for %s", symname(formal));
	    b = false;
	}
    }
    if (b and formal != nil and
	isvarparam(formal) and not isopenarray(formal->type) and
	not (
	    actual->op == O_RVAL or actual->nodetype == t_addr or
	    (
		actual->op == O_TYPERENAME and
		(
		    actual->value.arg[0]->op == O_RVAL or
		    actual->value.arg[0]->nodetype == t_addr
		)
	    )
	)
    ) {
	beginerrmsg();
	fprintf(stderr, "expected variable, found \"");
	prtree(stderr, actual);
	fprintf(stderr, "\"");
	b = false;
    }
    return b;
}

/*
 * Pass an expression to a particular parameter.
 *
 * Normally we pass either the address or value, but in some cases
 * (such as C strings) we want to copy the value onto the stack and
 * pass its address.
 *
 * Another special case raised by strings is the possibility that
 * the actual parameter will be larger than the formal, even with
 * appropriate type-checking.  This occurs because we assume during
 * evaluation that strings are null-terminated, whereas some languages,
 * notably Pascal, do not work under that assumption.
 */

private passparam (actual, formal)
Node actual;
Symbol formal;
{
    boolean b;
    Address addr;
    Stack *savesp;
    integer actsize, formsize;

    if (formal != nil and isvarparam(formal) and
	(not isopenarray(formal->type))
    ) {
	addr = lval(actual->value.arg[0]);
	push(Address, addr);
    } else if (passaddr(formal, actual->nodetype)) {
	savesp = sp;
	eval(actual);
	actsize = sp - savesp;
	setreg(STKP, reg(STKP) - roundup(actsize, sizeof (Word)));
	dwrite(savesp, reg(STKP), actsize);
	sp = savesp;
	push(Address, reg(STKP));
	if (formal != nil and isopenarray(formal->type)) {
	    push(integer, actsize div size(formal->type->type));
	}
    } else if (formal != nil) {
	formsize = size(formal);
	savesp = sp;
	eval(actual);
	actsize = sp - savesp;
	if (actsize > formsize) {
	    sp -= (actsize - formsize);
	}
    } else {
	eval(actual);
    }
}

/*
 * Evaluate an argument list left-to-right.
 */

private integer evalargs(proc, arglist)
Symbol proc;
Node arglist;
{
    Node p, actual;
    Symbol formal;
    Stack *savesp;
    integer count;
    boolean chk;

    savesp = sp;
    count = 0;
    formal = proc->chain;
    chk = (boolean) (not nosource(proc));
    for (p = arglist; p != nil; p = p->value.arg[1]) {
	assert(p->op == O_COMMA);
	actual = p->value.arg[0];
	if (not chkparam(actual, formal, chk)) {
	    fprintf(stderr, " in call to %s", symname(proc));
	    sp = savesp;
	    enderrmsg();
	}
	passparam(actual, formal);
	if (formal != nil) {
	    formal = formal->chain;
	}
	++count;
    }
    if (chk) {
	if (formal != nil) {
	    sp = savesp;
	    error("not enough parameters to %s", symname(proc));
	}
    }
    return count;
}

I 3
/*
 * Evaluate an argument list without any type checking.
 * This is only useful for procedures with a varying number of
 * arguments that are compiled -g.
 */

private integer unsafe_evalargs (proc, arglist)
Symbol proc;
Node arglist;
{
    Node p;
    integer count;

    count = 0;
    for (p = arglist; p != nil; p = p->value.arg[1]) {
	assert(p->op == O_COMMA);
	eval(p->value.arg[0]);
	++count;
    }
    return count;
}

E 3
public procreturn(f)
Symbol f;
{
    integer retvalsize;
    Node tmp;
    char *copy;

    flushoutput();
    popenv();
    if (endproc.isfunc) {
	retvalsize = size(f->type);
	if (retvalsize > sizeof(long)) {
	    pushretval(retvalsize, true);
	    copy = newarr(char, retvalsize);
	    popn(retvalsize, copy);
	    tmp = build(O_SCON, copy);
	} else {
	    tmp = build(O_LCON, (long) (reg(0)));
	}
	tmp->nodetype = f->type;
	tfree(endproc.callnode);
	*(endproc.callnode) = *(tmp);
	dispose(tmp);
	eval(endproc.cmdnode);
    } else {
	putchar('\n');
	printname(stdout, f);
D 3
	printf(" returns successfully\n", symname(f));
E 3
I 3
	printf(" returns successfully\n");
E 3
    }
    erecover();
}

/*
 * Push the current environment.
 */

private pushenv()
{
    push(Address, pc);
    push(Lineno, curline);
    push(String, cursource);
    push(Boolean, isstopped);
    push(Symbol, curfunc);
    push(Frame, curframe);
    push(struct Frame, curframerec);
    push(CallEnv, endproc);
    push(Word, reg(PROGCTR));
    push(Word, reg(STKP));
I 7
    push(Word, reg(FRP));
E 7
}

/*
 * Pop back to the real world.
 */

public popenv()
{
    String filename;

I 7
    setreg(FRP, pop(Word));
E 7
    setreg(STKP, pop(Word));
    setreg(PROGCTR, pop(Word));
    endproc = pop(CallEnv);
    curframerec = pop(struct Frame);
    curframe = pop(Frame);
    curfunc = pop(Symbol);
    isstopped = pop(Boolean);
    filename = pop(String);
    curline = pop(Lineno);
    pc = pop(Address);
    setsource(filename);
}

/*
 * Flush the debuggee's standard output.
 *
 * This is VERY dependent on the use of stdio.
 */

public flushoutput()
{
    Symbol p, iob;
    Stack *savesp;

    p = lookup(identname("fflush", true));
    while (p != nil and not isblock(p)) {
	p = p->next_sym;
    }
    if (p != nil) {
D 6
	iob = lookup(identname("_iob", true));
E 6
I 6
	iob = lookup(identname("__sF", true));
E 6
	if (iob != nil) {
	    pushenv();
	    pc = codeloc(p);
	    savesp = sp;
D 6
	    push(long, address(iob, nil) + sizeof(struct _iobuf));
E 6
I 6
	    push(long, address(iob, nil) + sizeof(*stdout));
E 6
	    setreg(STKP, reg(STKP) - sizeof(long));
	    dwrite(savesp, reg(STKP), sizeof(long));
	    sp = savesp;
	    beginproc(p, 1);
	    stepto(return_addr());
	    popenv();
	}
    }
}
E 1
