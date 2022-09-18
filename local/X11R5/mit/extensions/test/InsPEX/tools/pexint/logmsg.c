
/* $XConsortium: logmsg.c,v 5.1 91/02/16 10:00:17 rws Exp $ */

/*****************************************************************
Copyright (c) 1989,1990, 1991 by Sun Microsystems, Inc. and the X Consortium.

                        All Rights Reserved

Permission to use, copy, modify, and distribute this software and its 
documentation for any purpose and without fee is hereby granted, 
provided that the above copyright notice appear in all copies and that
both that copyright notice and this permission notice appear in 
supporting documentation, and that the names of Sun Microsystems,
the X Consortium, and MIT not be used in advertising or publicity 
pertaining to distribution of the software without specific, written 
prior permission.  

SUN MICROSYSTEMS DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, 
INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT 
SHALL SUN MICROSYSTEMS BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL 
DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
SOFTWARE.

******************************************************************/



/*
 * Message logging utilities
 */
#include "stdio.h"
#include "logmsg.h"
#include "varargs.h"

/*
 * global variables
 */
char    *testname = NULL;	/* current test name */
char    *testdesc = NULL;	/* test description */
int      maxfail = 5;    	/* max failures before abort */
int      numfail;    		/* current number of failures */
int      verbosity = 0;  	/* verbosity level */
int      pausebetweenframe = 0; /* pause flag */
int      clientside = 0;     	/* 1 for client side storage testing */
char    *inspexdest = NULL;     /* path for inspex destination directory */
char    *inspeximageref = NULL;	/* path for inspex image directory */
int      showpix = 0;        	/* 1 for showing where pixels are sampled */
int      nomonitor = 0;      	/* 1 for no monitor testing */
int      xtoolws = 0;        	/* 1 for x tool ws testing */
int      grid = 0;           	/* 1 for showing grid in some tests */
int      winxoffset = 0;     	/* x offset for putting window */
int      winyoffset = 0;     	/* y offset for putting window */



/*
 * external functions
 */
char *getenv();

/*
 * forward declaration
 */
/*
 * export routines */
void tbegintest();
void tfprintf();
void tvprintf();
void tendtest();
void tabort();


/*
 * tbegintest(name, desc) initializes testing environment
 */
void
tbegintest(name, desc)
    char           *name;       /* test name */
    char           *desc;       /* test description */
{
    char           *cp;

    /* initialize testing environment */
    testname = name;
    testdesc = desc;
    numfail = 0;
    if (cp = getenv("MAXFAIL"))
        maxfail = atoi(cp);
    if (cp = getenv("VERBOSITY"))
        verbosity = atoi(cp);
    if (cp = getenv("I_CLIENT_SIDE"))
        clientside = 1;
    if (cp = getenv("I_NO_MONITOR"))
        nomonitor = 1;
    if (cp = getenv("I_WIN_X_OFFSET"))
        winxoffset = atoi(cp);
    if (cp = getenv("I_WIN_Y_OFFSET"))
        winyoffset = atoi(cp);
    if (cp = getenv("I_X_TOOL_WS"))
        xtoolws = 1;
    if (cp = getenv("PAUSE"))
        pausebetweenframe = 1;
    if (cp = getenv("SHOWPIX"))
        showpix = 1;
    if (cp = getenv("GRID"))
        grid = 1;
    if (cp = getenv("INSPEXDEST"))
        inspexdest = cp;
    if (cp = getenv("INSPEXIMAGEREF"))
        inspeximageref = cp;
    tvprintf(2, "Beginning test...\n");
}

/*
 * tendtest() terminates test
 */
void
tendtest()
{
    if (numfail)
        printf("%s: FAILED: %s\n", testname, testdesc);
    else
        printf("%s: PASSED: %s\n", testname, testdesc);
    tvprintf(2, "Ending test.\n");
}


/*
 * tfprintf(fmt,va_alist) prints out msg, incs fail
 */
void
tfprintf(fmt, va_alist)
    char           *fmt;        /* message fmt */
    va_dcl                      /* variable data */
{
    va_list         ap;
    
    va_start(ap);
    printf("%s: ",testname);
    vprintf(fmt, ap);
    va_end(ap);

    if (++numfail >= maxfail) {
        printf("%s: Exiting, too many failures (%d).\n",testname,numfail);
	tendtest();
        exit(1); 
    }
}

/*
 * tvprintf(ver,fmt,va_alist) prints out message according to given verbosity
 */
void
tvprintf(ver, fmt, va_alist)
    int             ver;        /* current verbosity */
    char           *fmt;        /* message fmt */
    va_dcl                          /* variable data */
{
    va_list         ap;

    /* print out message if VERBOSITY >= this message's verbosity */
    if (ver <= verbosity) {
        va_start(ap);
        printf("%s: ",testname);
        vprintf(fmt, ap);
        va_end(ap);
    }
}

/*
 * tabort(fmt,va_alist)
 * prints out error message and abort program
 */
void
tabort(fmt,va_alist)

        char *fmt;              /* message fmt */
        va_dcl                  /* variable data */
{
        va_list ap;

        va_start(ap);
        printf("%s: ",testname);
        vprintf(fmt,ap);
        va_end(ap);
	++numfail;
	tendtest();
        exit(1);
}


