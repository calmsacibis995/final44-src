h58969
s 00001/00011/00898
d D 5.5 90/06/01 16:02:27 bostic 13 12
c new copyright notice
e
s 00015/00006/00894
d D 5.4 89/05/23 10:20:39 bostic 12 11
c add Berkeley specific copyright notice
e
s 00019/00018/00881
d D 5.3 88/01/12 00:33:04 donn 11 10
c merge in latest Linton version
e
s 00001/00001/00898
d D 5.2 87/04/06 12:02:35 bostic 10 9
c printf format/argument mismatch
e
s 00008/00002/00891
d D 5.1 85/05/31 09:58:49 dist 9 8
c Add copyright
e
s 00085/00176/00808
d D 1.7 85/03/01 20:22:36 linton 8 7
c update to version 3.0
e
s 00012/00001/00972
d D 1.6 84/08/18 19:52:29 sam 7 6
c add support for tracing register variables
e
s 00142/00041/00831
d D 1.5 84/08/18 13:40:15 sam 6 5
c put traceoff event back to being temporary (linton had changed 
c it, but it breaks everything); add loads of deubgging info; make bpact 
c a bit more paranoid about referencing bpt pointers since delevent might 
c conceivably delete the current one out from underneath it
e
s 00001/00003/00871
d D 1.4 84/06/23 11:40:29 sam 5 3
i 4
c merge linton branch delta trail
e
s 00062/00016/00812
d D 1.3.1.1 84/06/23 10:46:07 sam 4 3
c branch delta of linton changes from net.sources
e
s 00065/00029/00763
d D 1.3 83/04/08 01:24:26 linton 3 2
c added a routine to determine if any breakpoints lie within 
c a given routine
e
s 00001/00001/00791
d D 1.2 82/12/15 04:20:09 linton 2 1
c fixed @(#) stuff
e
s 00792/00000/00000
d D 1.1 82/12/15 04:07:28 linton 1 0
c date and time created 82/12/15 04:07:28 by linton
e
u
U
f b 
t
T
I 1
D 9
/* Copyright (c) 1982 Regents of the University of California */
E 9
I 9
/*
D 12
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 12
I 12
 * Copyright (c) 1983 The Regents of the University of California.
 * All rights reserved.
 *
D 13
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
E 13
I 13
 * %sccs.include.redist.c%
E 13
E 12
 */
E 9

D 2
static char sccsid[] = "@(#)%Z%%M% %I% %G%";
E 2
I 2
D 4
static char sccsid[] = "%Z%%M% %I% %G%";
E 4
I 4
D 5
static char sccsid[] = "@(#)events.c 1.3 4/8/83";
E 4
E 2

I 4
static char rcsid[] = "$Header: events.c,v 1.3 84/03/27 10:20:41 linton Exp $";
E 5
I 5
D 9
static	char sccsid[] = "%W% (Berkeley) %G%";
E 9
I 9
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 12
#endif not lint
E 9
E 5

I 8
D 11
static char rcsid[] = "$Header: events.c,v 1.5 84/12/26 10:39:26 linton Exp $";
E 11
I 11
static char rcsid[] = "$Header: events.c,v 1.3 87/07/08 18:46:02 donn Exp $";
E 12
I 12
#endif /* not lint */
E 12
E 11

E 8
E 4
/*
 * Event/breakpoint managment.
 */

#include "defs.h"
#include "events.h"
#include "main.h"
#include "symbols.h"
#include "tree.h"
#include "eval.h"
#include "source.h"
#include "mappings.h"
I 4
#include "runtime.h"
E 4
#include "process.h"
#include "machine.h"
#include "lists.h"

#ifndef public
I 11

E 11
typedef struct Event *Event;
typedef struct Breakpoint *Breakpoint;

D 8
Boolean inst_tracing;
Boolean single_stepping;
Boolean isstopped;
E 8
I 8
D 11
boolean inst_tracing;
boolean single_stepping;
boolean isstopped;
E 8

E 11
#include "symbols.h"

D 11
Symbol linesym;
Symbol procsym;
Symbol pcsym;
Symbol retaddrsym;

E 11
#define addevent(cond, cmdlist) event_alloc(false, cond, cmdlist)
#define event_once(cond, cmdlist) event_alloc(true, cond, cmdlist)

I 11
/*
 * When tracing variables we keep a copy of their most recent value
 * and compare it to the current one each time a breakpoint occurs.
 * MAXTRSIZE is the maximum size variable we allow.
 */

#define MAXTRSIZE 512

E 11
#endif

I 11
public boolean inst_tracing;
public boolean single_stepping;
public boolean isstopped;

public Symbol linesym;
public Symbol procsym;
public Symbol pcsym;
public Symbol retaddrsym;

E 11
struct Event {
    unsigned int id;
D 8
    Boolean temporary;
E 8
I 8
    boolean temporary;
E 8
    Node condition;
    Cmdlist actions;
};

struct Breakpoint {
    Event event;
    Address bpaddr;	
    Lineno bpline;
    Cmdlist actions;
I 8
    boolean temporary;
E 8
};

typedef List Eventlist;
typedef List Bplist;

#define eventlist_append(event, el) list_append(list_item(event), nil, el)
#define bplist_append(bp, bl) list_append(list_item(bp), nil, bl)

private Eventlist eventlist;		/* list of active events */
private Bplist bplist;			/* list of active breakpoints */
D 8
private Integer eventid;		/* id number of next allocated event */
private Integer trid;			/* id number of next allocated trace */
E 8
I 8
private Event curevent;			/* most recently created event */
private integer eventid;		/* id number of current event */
private integer trid;			/* id number of current trace */
E 8

typedef struct Trcmd {
    Integer trid;
    Event event;
    Cmdlist cmdlist;
} *Trcmd;

private List eachline;		/* commands to execute after each line */
private List eachinst;		/* commands to execute after each instruction */

private Breakpoint bp_alloc();

/*
 * Initialize breakpoint information.
 */

private Symbol builtinsym(str, class, type)
String str;
Symclass class;
Symbol type;
{
    Symbol s;

    s = insert(identname(str, true));
    s->language = findlanguage(".s");
    s->class = class;
    s->type = type;
    return s;
}

public bpinit()
{
    linesym = builtinsym("$line", VAR, t_int);
    procsym = builtinsym("$proc", PROC, nil);
    pcsym = lookup(identname("$pc", true));
    if (pcsym == nil) {
	panic("can't find $pc");
    }
    retaddrsym = builtinsym("$retaddr", VAR, t_int);
    eventlist = list_alloc();
    bplist = list_alloc();
    eachline = list_alloc();
    eachinst = list_alloc();
}

/*
 * Trap an event and do the associated commands when it occurs.
 */

public Event event_alloc(istmp, econd, cmdlist)
D 8
Boolean istmp;
E 8
I 8
boolean istmp;
E 8
Node econd;
Cmdlist cmdlist;
{
    register Event e;

    e = new(Event);
D 6
    ++eventid;
    e->id = eventid;
E 6
I 6
D 8
    e->id = ++eventid;
E 8
I 8
    ++eventid;
    e->id = eventid;
E 8
E 6
    e->temporary = istmp;
    e->condition = econd;
    e->actions = cmdlist;
I 6
D 8
    if (tracebpts) {
	debugevent("event_alloc: new", e);
	putchar('\n');
	fflush(stdout);
    }
E 8
E 6
    eventlist_append(e, eventlist);
I 8
    curevent = e;
E 8
    translate(e);
    return e;
}

/*
 * Delete the event with the given id.
I 4
 * Returns whether it's successful or not.
E 4
 */

D 4
public delevent(id)
E 4
I 4
public boolean delevent (id)
E 4
unsigned int id;
{
    Event e;
    Breakpoint bp;
    Trcmd t;
I 4
    boolean found;
E 4

I 4
    found = false;
E 4
    foreach (Event, e, eventlist)
	if (e->id == id) {
D 4
	    list_delete(list_curitem(eventlist), eventlist);
E 4
I 4
	    found = true;
E 4
	    foreach (Breakpoint, bp, bplist)
		if (bp->event == e) {
I 4
D 6
		    if (tracebpts) {
			printf("deleting breakpoint at 0x%x\n", bp->bpaddr);
			fflush(stdout);
		    }
E 6
I 6
D 8
		    if (tracebpts)
			debugbpt("delevent: deleting", bp);
E 8
I 8
		    if (tracebpts) {
			printf("deleting breakpoint at 0x%x\n", bp->bpaddr);
			fflush(stdout);
		    }
E 8
E 6
E 4
		    list_delete(list_curitem(bplist), bplist);
		}
	    endfor
I 4
	    list_delete(list_curitem(eventlist), eventlist);
E 4
	    break;
	}
    endfor
    foreach (Trcmd, t, eachline)
	if (t->event->id == id) {
I 4
	    found = true;
E 4
	    printrmtr(t);
	    list_delete(list_curitem(eachline), eachline);
	}
    endfor
    foreach (Trcmd, t, eachinst)
	if (t->event->id == id) {
I 4
	    found = true;
E 4
	    printrmtr(t);
	    list_delete(list_curitem(eachinst), eachinst);
	}
    endfor
    if (list_size(eachinst) == 0) {
	inst_tracing = false;
	if (list_size(eachline) == 0) {
	    single_stepping = false;
	}
    }
I 4
    return found;
E 4
}

/*
 * Translate an event into the appropriate breakpoints and actions.
 * While we're at it, turn on the breakpoints if the condition is true.
 */

private translate(e)
Event e;
{
    Breakpoint bp;
    Symbol s;
    Node place;
    Lineno line;
    Address addr;

    checkref(e->condition);
    switch (e->condition->op) {
	case O_EQ:
	    if (e->condition->value.arg[0]->op == O_SYM) {
		s = e->condition->value.arg[0]->value.sym;
		place = e->condition->value.arg[1];
		if (s == linesym) {
		    if (place->op == O_QLINE) {
			line = place->value.arg[1]->value.lcon;
D 4
			addr = objaddr(line,
			    place->value.arg[0]->value.scon);
E 4
I 4
			addr = objaddr(line, place->value.arg[0]->value.scon);
E 4
		    } else {
			eval(place);
			line = pop(long);
			addr = objaddr(line, cursource);
		    }
		    if (addr == NOADDR) {
D 4
			delevent(e->id);
E 4
I 4
			if (not delevent(e->id)) {
			    printf("!! dbx.translate: can't undo event %d?\n",
				e->id);
			}
E 4
			beginerrmsg();
			fprintf(stderr, "no executable code at line ");
			prtree(stderr, place);
			enderrmsg();
		    }
		    bp = bp_alloc(e, addr, line, e->actions);
		} else if (s == procsym) {
		    eval(place);
		    s = pop(Symbol);
		    bp = bp_alloc(e, codeloc(s), 0, e->actions);
		    if (isactive(s) and pc != codeloc(program)) {
			evalcmdlist(e->actions);
		    }
		} else if (s == pcsym) {
		    eval(place);
		    bp = bp_alloc(e, pop(Address), 0, e->actions);
		} else {
		    condbp(e);
		}
	    } else {
		condbp(e);
	    }
	    break;

	/*
	 * These should be handled specially.
	 * But for now I'm ignoring the problem.
	 */
	case O_AND:
	case O_OR:
	default:
	    condbp(e);
	    break;
    }
}

/*
 * Create a breakpoint for a condition that cannot be pinpointed
 * to happening at a particular address, but one for which we
 * must single step and check the condition after each statement.
 */

private condbp(e)
Event e;
{
    Symbol p;
    Breakpoint bp;
    Cmdlist actions;

    p = tcontainer(e->condition);
    if (p == nil) {
	p = program;
    }
    actions = buildcmdlist(build(O_IF, e->condition, e->actions));
    actions = buildcmdlist(build(O_TRACEON, false, actions));
    bp = bp_alloc(e, codeloc(p), 0, actions);
}

/*
 * Determine the deepest nested subprogram that still contains
 * all elements in the given expression.
 */

public Symbol tcontainer(exp)
Node exp;
{
    Integer i;
    Symbol s, t, u, v;

    checkref(exp);
    s = nil;
    if (exp->op == O_SYM) {
	s = container(exp->value.sym);
    } else if (not isleaf(exp->op)) {
	for (i = 0; i < nargs(exp->op); i++) {
	    t = tcontainer(exp->value.arg[i]);
	    if (t != nil) {
		if (s == nil) {
		    s = t;
		} else {
		    u = s;
		    v = t;
		    while (u != v and u != nil) {
			u = container(u);
			v = container(v);
		    }
		    if (u == nil) {
			panic("bad ancestry for \"%s\"", symname(s));
		    } else {
			s = u;
		    }
		}
	    }
	}
    }
    return s;
}

/*
I 3
 * Determine if the given function can be executed at full speed.
 * This can only be done if there are no breakpoints within the function.
 */

D 8
public Boolean canskip(f)
E 8
I 8
public boolean canskip(f)
E 8
Symbol f;
{
    Breakpoint p;
D 8
    Boolean ok;
E 8
I 8
    boolean ok;
E 8

    ok = true;
    foreach (Breakpoint, p, bplist)
	if (whatblock(p->bpaddr) == f) {
	    ok = false;
	    break;
	}
    endfor
    return ok;
}

/*
E 3
 * Print out what's currently being traced by looking at
 * the currently active events.
 *
 * Some convolution here to translate internal representation
 * of events back into something more palatable.
 */

public status()
{
    Event e;
D 3
    Command cmd;
E 3

    foreach (Event, e, eventlist)
	if (not e->temporary) {
D 3
	    if (not isredirected()) {
		printf("(%d) ", e->id);
	    }
	    cmd = list_element(Command, list_head(e->actions));
	    if (cmd->op == O_PRINTCALL) {
		printf("trace ");
		printname(stdout, cmd->value.sym);
	    } else {
		if (list_size(e->actions) > 1) {
		    printf("{ ");
		}
		foreach (Command, cmd, e->actions)
		    printcmd(stdout, cmd);
		    if (not list_islast()) {
			printf("; ");
		    }
		endfor
		if (list_size(e->actions) > 1) {
		    printf(" }");
		}
		printcond(e->condition);
	    }
	    printf("\n");
E 3
I 3
	    printevent(e);
E 3
	}
    endfor
}

I 3
public printevent(e)
Event e;
{
    Command cmd;

    if (not isredirected()) {
D 4
	printf("(%d) ", e->id);
E 4
I 4
	printeventid(e->id);
E 4
    }
    cmd = list_element(Command, list_head(e->actions));
    if (cmd->op == O_PRINTCALL) {
	printf("trace ");
	printname(stdout, cmd->value.sym);
    } else {
	if (list_size(e->actions) > 1) {
	    printf("{ ");
	}
	foreach (Command, cmd, e->actions)
	    printcmd(stdout, cmd);
	    if (not list_islast()) {
		printf("; ");
	    }
	endfor
	if (list_size(e->actions) > 1) {
	    printf(" }");
	}
	printcond(e->condition);
    }
    printf("\n");
}

I 4
private printeventid (id)
integer id;
{
    printf("[%d] ", id);
}

E 4
E 3
/*
 * Print out a condition.
 */

private printcond(cond)
Node cond;
{
    Symbol s;
    Node place;

    if (cond->op == O_EQ and cond->value.arg[0]->op == O_SYM) {
	s = cond->value.arg[0]->value.sym;
	place = cond->value.arg[1];
	if (s == procsym) {
	    if (place->value.sym != program) {
		printf(" in ");
		printname(stdout, place->value.sym);
	    }
	} else if (s == linesym) {
	    printf(" at ");
	    prtree(stdout, place);
	} else if (s == pcsym or s == retaddrsym) {
	    printf("i at ");
	    prtree(stdout, place);
	} else {
	    printf(" when ");
	    prtree(stdout, cond);
	}
    } else {
	printf(" when ");
	prtree(stdout, cond);
    }
}

/*
 * Add a breakpoint to the list and return it.
 */

private Breakpoint bp_alloc(e, addr, line, actions)
Event e;
Address addr;
Lineno line;
Cmdlist actions;
{
    register Breakpoint p;

    p = new(Breakpoint);
    p->event = e;
    p->bpaddr = addr;
    p->bpline = line;
    p->actions = actions;
D 6
    if (tracebpts) {
D 4
	printf("new bp at 0x%x\n", addr);
E 4
I 4
	if (e == nil) {
	    printf("new bp at 0x%x for event ??\n", addr, e->id);
	} else {
	    printf("new bp at 0x%x for event %d\n", addr, e->id);
	}
E 4
	fflush(stdout);
    }
E 6
I 6
D 8
    if (tracebpts)
	debugbpt("bp_alloc: new", p);
E 8
I 8
    p->temporary = false;
    if (tracebpts) {
	if (e == nil) {
D 10
	    printf("new bp at 0x%x for event ??\n", addr, e->id);
E 10
I 10
	    printf("new bp at 0x%x for event ??\n", addr);
E 10
	} else {
	    printf("new bp at 0x%x for event %d\n", addr, e->id);
	}
	fflush(stdout);
    }
E 8
E 6
    bplist_append(p, bplist);
    return p;
}

/*
 * Free all storage in the event and breakpoint tables.
 */

public bpfree()
{
    register Event e;

    fixbps();
    foreach (Event, e, eventlist)
D 4
	delevent(e->id);
E 4
I 4
	if (not delevent(e->id)) {
	    printf("!! dbx.bpfree: can't delete event %d\n", e->id);
	}
E 4
	list_delete(list_curitem(eventlist), eventlist);
    endfor
}

/*
 * Determine if the program stopped at a known breakpoint
 * and if so do the associated commands.
 */

D 8
public Boolean bpact()
E 8
I 8
public boolean bpact()
E 8
{
    register Breakpoint p;
D 8
    Boolean found;
E 8
I 8
    boolean found;
E 8
I 4
    integer eventId;
E 4

    found = false;
    foreach (Breakpoint, p, bplist)
	if (p->bpaddr == pc) {
D 6
	    if (tracebpts) {
D 4
		printf("breakpoint found at location 0x%x\n", pc);
E 4
I 4
		printf("breakpoint for event %d found at location 0x%x\n",
		    p->event->id, pc);
E 4
	    }
E 6
I 6
D 8
	    if (tracebpts)
		debugbpt("bpact: found", p);
E 8
I 8
	    if (tracebpts) {
		printf("breakpoint for event %d found at location 0x%x\n",
		    p->event->id, pc);
	    }
E 8
E 6
	    found = true;
I 8
	    if (p->event->temporary) {
		if (not delevent(p->event->id)) {
		    printf("!! dbx.bpact: can't find event %d\n",
			p->event->id);
		}
	    }
E 8
D 6
	    if (p->event->temporary) {
D 4
		delevent(p->event->id);
E 4
I 4
		if (not delevent(p->event->id)) {
		    printf("!! dbx.bpact: can't find event %d\n",
			p->event->id);
		}
E 4
	    }
E 6
	    evalcmdlist(p->actions);
I 4
D 6
	    if (isstopped) {
		eventId = p->event->id;
	    }
E 6
I 6
D 8
	    eventId = p->event->id;
	    if (p->event->temporary and not delevent(p->event->id))
		printf("!! dbx.bpact: can't find event %d\n", eventId);
E 8
I 8
	    if (isstopped) {
		eventId = p->event->id;
	    }
	    if (p->temporary) {
		list_delete(list_curitem(bplist), bplist);
	    }
E 8
E 6
E 4
	}
    endfor
    if (isstopped) {
I 4
	if (found) {
	    printeventid(eventId);
	}
E 4
	printstatus();
    }
    fflush(stdout);
    return found;
}

/*
 * Begin single stepping and executing the given commands after each step.
 * If the first argument is true step by instructions, otherwise
 * step by source lines.
 *
 * We automatically set a breakpoint at the end of the current procedure
 * to turn off the given tracing.
 */

public traceon(inst, event, cmdlist)
D 8
Boolean inst;
E 8
I 8
boolean inst;
E 8
Event event;
Cmdlist cmdlist;
{
    register Trcmd trcmd;
I 8
    Breakpoint bp;
E 8
D 6
    Breakpoint bp;
E 6
D 4
    Node until;
E 4
    Cmdlist actions;
I 3
    Address ret;
I 8
    Event e;
E 8
E 3

I 8
    if (event == nil) {
	e = curevent;
    } else {
	e = event;
    }
E 8
    trcmd = new(Trcmd);
D 6
    ++trid;
    trcmd->trid = trid;
E 6
I 6
D 8
    trcmd->trid = ++trid;
E 6
    trcmd->event = event;
E 8
I 8
    ++trid;
    trcmd->trid = trid;
    trcmd->event = e;
E 8
    trcmd->cmdlist = cmdlist;
I 6
D 8
    if (tracebpts)
	debugtrace("traceon: adding", trcmd);
E 8
E 6
    single_stepping = true;
    if (inst) {
	inst_tracing = true;
	list_append(list_item(trcmd), nil, eachinst);
    } else {
	list_append(list_item(trcmd), nil, eachline);
    }
D 3
    until = build(O_EQ, build(O_SYM, pcsym), build(O_LCON, return_addr()));
    actions = buildcmdlist(build(O_TRACEOFF, trcmd->trid));
    event_once(until, actions);
E 3
I 3
    ret = return_addr();
    if (ret != 0) {
D 4
	until = build(O_EQ, build(O_SYM, pcsym), build(O_LCON, ret));
E 4
D 6
	actions = buildcmdlist(build(O_TRACEOFF, trcmd->trid));
D 4
	event_once(until, actions);
E 4
I 4
	bp = bp_alloc(event, (Address) ret, 0, actions);
E 6
I 6
D 8
	/*
	 * Must create new temporary event for traceoff action;
	 * otherwise traceoff will take place but the breakpoint
	 * won't be deleted.  This results in a panic the next
	 * time we enter the region where tracing takes place since
	 * the associate trace id (of the traceoff command) no
	 * longer exists.
	 */
	event_once(build(O_EQ, build(O_SYM, pcsym), build(O_LCON, ret)),
	    buildcmdlist(build(O_TRACEOFF, trcmd->trid)));
E 8
I 8
	actions = buildcmdlist(build(O_TRACEOFF, trcmd->trid));
	bp = bp_alloc(e, (Address) ret, 0, actions);
	bp->temporary = true;
E 8
E 6
E 4
    }
I 8
    if (tracebpts) {
	printf("adding trace %d for event %d\n", trcmd->trid, e->id);
    }
E 8
E 3
D 6
    if (tracebpts) {
	printf("adding trace %d for event %d\n", trcmd->trid, event->id);
    }
E 6
}

/*
 * Turn off some kind of tracing.
 * Strictly an internal command, this cannot be invoked by the user.
 */

public traceoff(id)
Integer id;
{
    register Trcmd t;
D 8
    register Boolean found;
E 8
I 8
    register boolean found;
E 8

    found = false;
    foreach (Trcmd, t, eachline)
	if (t->trid == id) {
	    printrmtr(t);
	    list_delete(list_curitem(eachline), eachline);
	    found = true;
	    break;
	}
    endfor
    if (not found) {
	foreach (Trcmd, t, eachinst)
	    if (t->event->id == id) {
		printrmtr(t);
		list_delete(list_curitem(eachinst), eachinst);
		found = true;
		break;
	    }
	endfor
	if (not found) {
I 6
D 8
	    debugallevents("traceoff");
E 6
	    panic("missing trid %d", id);
E 8
I 8
	    beginerrmsg();
	    fprintf(stderr, "[internal error: trace id %d not found]\n", id);
E 8
	}
    }
    if (list_size(eachinst) == 0) {
	inst_tracing = false;
	if (list_size(eachline) == 0) {
	    single_stepping = false;
	}
    }
}

/*
 * If breakpoints are being traced, note that a Trcmd is being deleted.
 */

private printrmtr(t)
Trcmd t;
{
D 6
    if (tracebpts) {
D 3
	printf("removing trace %d for event %d\n", t->trid, t->event->id);
E 3
I 3
	printf("removing trace %d", t->trid);
	if (t->event != nil) {
	    printf(" for event %d", t->event->id);
	}
	printf("\n");
E 6
I 6
D 8
    if (tracebpts)
	debugtrace("removing", t);
}

/*
 * Debugging routines.
 */
debugallevents(s)
String s;
{
    register Trcmd t;
    register Event e;
    register Breakpoint bp;

    if (s)
	printf("%s:\n", s);
    if (eachline) {
	printf("Traces (eachline):\n");
	foreach (Trcmd, t, eachline)
	    debugtrace("\t", t);
	endfor
E 8
I 8
    if (tracebpts) {
	printf("removing trace %d", t->trid);
	if (t->event != nil) {
	    printf(" for event %d", t->event->id);
	}
	printf("\n");
E 8
E 6
E 3
    }
I 6
D 8
    if (eachinst) {
	printf("Trace (eachinst):\n");
	foreach (Trcmd, t, eachinst)
	    debugtrace("\t", t);
	endfor
    }
    if (bplist) {
	printf("Breakpoints:\n");
	foreach (Breakpoint, bp, bplist)
	    debugbpt("\t", bp);
	endfor
    }
    if (eventlist) {
	printf("Events:\n");
	foreach (Event, e, eventlist)
	    debugevent("\t", e);
	    putchar('\n');
	endfor
    }
    fflush(stdout);
E 8
}

D 8
private debugtrace(s, t)
String s;
Trcmd t;
{

    if (s)
	printf("%s ", s);
    printf("trace %d ", t->trid);
    debugevent("for", t->event);
    printf("\n");
    fflush(stdout);
}

private debugbpt(s, bp)
String s;
Breakpoint bp;
{

    if (s)
	printf("%s ", s);
    debugevent("breakpoint for", bp->event);
    printf("; loc 0x%x", bp->bpaddr);
    if (bp->actions)
	debugactions(" ", bp->actions, nil);
    putchar('\n');
    fflush(stdout);
}

private debugevent(s, e)
String s;
Event e;
{

    if (s)
	printf("%s ", s);
    if (e == nil) {
	printf("nil event");
	return;
    }
    if (e->temporary)
	printf("temporary ");
    printf("event %d", e->id);
}

debugactions(s, cl, condition)
String s;
Cmdlist cl;
Node condition;
{
    Command c;

    if (s)
	printf("%s ", s);
    c = list_element(Command, list_head(cl));
    if (c->op == O_PRINTCALL) {
	printf("trace ");
	printname(stdout, c->value.sym);
	return;
    }
    if (list_size(cl) > 1)
	printf("{ ");
    foreach (Command, c, cl)
	printcmd(stdout, c);
	if (not list_islast())
	    printf("; ");
    endfor
    if (list_size(cl) > 1)
	printf(" }");
    if (condition)
	printcond(condition);
E 6
}

E 8
/*
 * Print out news during single step tracing.
 */

public printnews()
{
    register Trcmd t;

    foreach (Trcmd, t, eachline)
	evalcmdlist(t->cmdlist);
    endfor
    foreach (Trcmd, t, eachinst)
	evalcmdlist(t->cmdlist);
    endfor
    bpact();
}

/*
 * A procedure call/return has occurred while single-stepping,
 * note it if we're tracing lines.
 */

D 8
private Boolean chklist();
E 8
I 8
private boolean chklist();
E 8

public callnews(iscall)
D 8
Boolean iscall;
E 8
I 8
boolean iscall;
E 8
{
    if (not chklist(eachline, iscall)) {
	chklist(eachinst, iscall);
    }
}

D 8
private Boolean chklist(list, iscall)
E 8
I 8
private boolean chklist(list, iscall)
E 8
List list;
D 8
Boolean iscall;
E 8
I 8
boolean iscall;
E 8
{
    register Trcmd t;
    register Command cmd;

I 3
D 4
    curfunc = whatblock(pc);
E 4
I 4
    setcurfunc(whatblock(pc));
E 4
E 3
    foreach (Trcmd, t, list)
	foreach (Command, cmd, t->cmdlist)
	    if (cmd->op == O_PRINTSRCPOS and
	      (cmd->value.arg[0] == nil or cmd->value.arg[0]->op == O_QLINE)) {
D 3
		curfunc = whatblock(pc);
E 3
		if (iscall) {
		    printentry(curfunc);
		} else {
		    printexit(curfunc);
		}
		return true;
	    }
	endfor
    endfor
    return false;
}
D 11

/*
 * When tracing variables we keep a copy of their most recent value
 * and compare it to the current one each time a breakpoint occurs.
 * MAXTRSIZE is the maximum size variable we allow.
 */

#define MAXTRSIZE 512
E 11

/*
 * List of variables being watched.
 */

typedef struct Trinfo *Trinfo;

struct Trinfo {
    Node variable;
    Address traddr;
    Symbol trblock;
    char *trvalue;
};

private List trinfolist;

/*
 * Find the trace information record associated with the given record.
 * If there isn't one then create it and add it to the list.
 */

private Trinfo findtrinfo(p)
Node p;
{
    register Trinfo tp;
D 8
    Boolean isnew;
E 8
I 8
    boolean isnew;
E 8

    isnew = true;
    if (trinfolist == nil) {
	trinfolist = list_alloc();
    } else {
	foreach (Trinfo, tp, trinfolist)
	    if (tp->variable == p) {
		isnew = false;
		break;
	    }
	endfor
    }
    if (isnew) {
	if (tracebpts) {
	    printf("adding trinfo for \"");
	    prtree(stdout, p);
	    printf("\"\n");
	}
	tp = new(Trinfo);
	tp->variable = p;
	tp->traddr = lval(p);
	tp->trvalue = nil;
	list_append(list_item(tp), nil, trinfolist);
    }
    return tp;
}

I 7
D 8
#define	cast(size, loc, val) \
    switch (size) { \
	case sizeof (char): *(char *)(loc) = (val); break; \
	case sizeof (short): *(short *)(loc) = (val); break; \
	default: *(int *)(loc) = (val); break; \
    }
E 8
E 7
/*
 * Print out the value of a variable if it has changed since the
 * last time we checked.
 */

public printifchanged(p)
Node p;
{
    register Trinfo tp;
    register int n;
    char buff[MAXTRSIZE];
I 8
    Filename curfile;
E 8
    static Lineno prevline;
I 8
    static Filename prevfile;
E 8

    tp = findtrinfo(p);
    n = size(p->nodetype);
D 7
    dread(buff, tp->traddr, n);
E 7
I 7
D 8
    if (p->op == O_SYM and isreg(p->value.sym)) {
	int regval = address(p->value.sym, nil);

	cast(n, buff, regval);
    } else
	dread(buff, tp->traddr, n);
E 8
I 8
    dread(buff, tp->traddr, n);
    curfile = srcfilename(pc);
E 8
E 7
    if (tp->trvalue == nil) {
	tp->trvalue = newarr(char, n);
	mov(buff, tp->trvalue, n);
	mov(buff, sp, n);
	sp += n;
D 8
	printf("initially (at line %d):\t", curline);
E 8
I 8
	printf("initially (at line %d in \"%s\"):\t", curline, curfile);
E 8
	prtree(stdout, p);
	printf(" = ");
	printval(p->nodetype);
	putchar('\n');
    } else if (cmp(tp->trvalue, buff, n) != 0) {
	mov(buff, tp->trvalue, n);
	mov(buff, sp, n);
	sp += n;
D 8
	printf("after line %d:\t", prevline);
E 8
I 8
	printf("after line %d in \"%s\":\t", prevline, prevfile);
E 8
	prtree(stdout, p);
	printf(" = ");
	printval(p->nodetype);
	putchar('\n');
    }
    prevline = curline;
I 8
    prevfile = curfile;
E 8
}

/*
 * Stop if the value of the given expression has changed.
 */

public stopifchanged(p)
Node p;
{
    register Trinfo tp;
    register int n;
    char buff[MAXTRSIZE];
    static Lineno prevline;

    tp = findtrinfo(p);
    n = size(p->nodetype);
    dread(buff, tp->traddr, n);
    if (tp->trvalue == nil) {
	tp->trvalue = newarr(char, n);
	mov(buff, tp->trvalue, n);
	isstopped = true;
    } else if (cmp(tp->trvalue, buff, n) != 0) {
	mov(buff, tp->trvalue, n);
I 4
	mov(buff, sp, n);
	sp += n;
	printf("after line %d:\t", prevline);
	prtree(stdout, p);
	printf(" = ");
	printval(p->nodetype);
	putchar('\n');
E 4
	isstopped = true;
    }
    prevline = curline;
}

/*
 * Free the tracing table.
 */

public trfree()
{
    register Trinfo tp;

    foreach (Trinfo, tp, trinfolist)
	dispose(tp->trvalue);
	dispose(tp);
	list_delete(list_curitem(trinfolist), trinfolist);
    endfor
}

/*
 * Fix up breakpoint information before continuing execution.
 *
 * It's necessary to destroy events and breakpoints that were created
 * temporarily and still exist because the program terminated abnormally.
 */

public fixbps()
{
    register Event e;
    register Trcmd t;

    single_stepping = false;
    inst_tracing = false;
    trfree();
    foreach (Event, e, eventlist)
	if (e->temporary) {
D 4
	    delevent(e->id);
E 4
I 4
	    if (not delevent(e->id)) {
		printf("!! dbx.fixbps: can't find event %d\n", e->id);
	    }
E 4
	}
    endfor
    foreach (Trcmd, t, eachline)
	printrmtr(t);
	list_delete(list_curitem(eachline), eachline);
    endfor
    foreach (Trcmd, t, eachinst)
	printrmtr(t);
	list_delete(list_curitem(eachinst), eachinst);
    endfor
}

/*
 * Set all breakpoints in object code.
 */

public setallbps()
{
    register Breakpoint p;

    foreach (Breakpoint, p, bplist)
	setbp(p->bpaddr);
    endfor
}

/*
 * Undo damage done by "setallbps".
 */

public unsetallbps()
{
    register Breakpoint p;

    foreach (Breakpoint, p, bplist)
	unsetbp(p->bpaddr);
    endfor
}
E 1
