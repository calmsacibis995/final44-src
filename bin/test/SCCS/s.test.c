h01789
s 00002/00002/00532
d D 8.3 94/04/02 10:03:02 pendry 15 14
c add 1994 copyright
e
s 00008/00005/00526
d D 8.2 94/04/01 03:51:04 pendry 14 13
c prettyness police
e
s 00005/00005/00526
d D 8.1 93/05/31 15:49:54 bostic 13 12
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00000/00527
d D 5.8 93/05/29 17:07:32 bostic 12 11
c add -h for symbolic links
e
s 00001/00001/00526
d D 5.7 93/05/29 10:56:13 bostic 11 10
c the "!" operator of test was working backwards; from Mike Hibler
c if test ! "foo" ; then echo not set; fi
c if test ! "" ; then echo not set; fi
e
s 00002/00000/00525
d D 5.6 93/04/30 11:43:51 bostic 10 9
c lint
e
s 00039/00057/00486
d D 5.5 93/04/30 11:33:43 bostic 9 8
c strip leading spaces from "integers" (bug report 4.4BSD-alpha/bin/1)
c check for underflow, overflow, trailing garbage, use strtol(3)
c use err/warn from the C library, some minor lint/cleanups
e
s 00002/00001/00541
d D 5.4 93/02/12 15:43:18 elan 8 7
c MIPS machine returns NULL if used '[ ]'. So added fix so it doesn't
c dump core.
e
s 00004/00004/00538
d D 5.3 93/02/10 22:04:44 torek 7 6
c [ ] used *(char *)NULL (net2/bin/16).  also, /bin/[ should work
c just like [
e
s 00000/00001/00542
d D 5.2 92/08/29 15:58:42 bostic 6 5
c atol is in stdlib.h
e
s 00164/00146/00379
d D 5.1 92/06/08 17:17:08 bostic 5 4
c lots of minor cleanup, whitespace changes
e
s 00004/00000/00521
d D 1.4 92/06/05 12:39:41 elan 4 3
c Fixed bug in posix_binary_op() that did not initialize the value 
c structs in the case of a string operation.
e
s 00001/00001/00520
d D 1.3 92/06/03 16:47:07 elan 3 2
c fixed copyright.
e
s 00369/00409/00152
d D 1.2 92/06/03 16:28:19 elan 2 1
c Added BSD Copyright.  Indented correctly and made whitespace 
c cleanup.
e
s 00561/00000/00000
d D 1.1 92/06/03 13:16:30 elan 1 0
c date and time created 92/06/03 13:16:30 by elan
e
u
U
t
T
I 1
D 5
/*
D 2
 * The expr and test commands.
E 2
I 2
 * Copyright (c) 1988 The Regents of the University of California.
E 5
I 5
/*-
D 13
 * Copyright (c) 1992 The Regents of the University of California.
E 5
 * All rights reserved.
E 13
I 13
D 15
 * Copyright (c) 1992, 1993
E 15
I 15
 * Copyright (c) 1992, 1993, 1994
E 15
 *	The Regents of the University of California.  All rights reserved.
E 13
E 2
 *
D 2
 * Copyright (C) 1989 by Kenneth Almquist.  All rights reserved.
 * This file is part of ash, which is distributed under the terms specified
 * by the Ash General Public License.  See the file named LICENSE.
E 2
I 2
 * This code is derived from software contributed to Berkeley by
 * Kenneth Almquist.
 *
 * %sccs.include.redist.c%
E 2
 */

D 2
#define PRINT
E 2
I 2
#ifndef lint
D 3
char    copyright[] =
E 3
I 3
D 5
static char copyright[] =
E 3
"%Z% Copyright (c) 1988 The Regents of the University of California.\n\
E 5
I 5
D 13
char copyright[] =
"%Z% Copyright (c) 1992 The Regents of the University of California.\n\
E 5
 All rights reserved.\n";
E 13
I 13
static char copyright[] =
D 15
"%Z% Copyright (c) 1992, 1993\n\
E 15
I 15
"%Z% Copyright (c) 1992, 1993, 1994\n\
E 15
	The Regents of the University of California.  All rights reserved.\n";
E 13
D 5
#endif				/* not lint */
E 5
I 5
#endif /* not lint */
E 5
E 2

I 2
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 5
#endif				/* not lint */
E 5
I 5
#endif /* not lint */
E 5
E 2

D 5
#include <stdio.h>
#include <errno.h>
E 5
#include <sys/types.h>
#include <sys/stat.h>
I 9

I 10
#include <ctype.h>
E 10
#include <err.h>
E 9
I 5
#include <errno.h>
I 9
#include <limits.h>
#include <stdio.h>
E 9
#include <stdlib.h>
E 5
I 4
#include <string.h>
I 10
#include <unistd.h>
E 10
I 5
D 9
#include <stdio.h>
E 9

E 5
E 4
#include "operators.h"
D 5
#include "extern.h"
E 5

D 5
#define STACKSIZE 12
#define NESTINCR 16
E 5
I 5
#define	STACKSIZE	12
#define	NESTINCR	16
E 5

/* data types */
D 5
#define STRING 0
#define INTEGER 1
#define BOOLEAN 2
E 5
I 5
#define	STRING	0
#define	INTEGER	1
#define	BOOLEAN	2
E 5

D 5
#define INITARGS(argv)	if (argv[0] == NULL) {fputs("Argc is zero\n", stderr); exit(2);} else
E 5
I 5
#define	IS_BANG(s) (s[0] == '!' && s[1] == '\0')
E 5

D 5
#define IS_BANG(s) (s[0] == '!' && s[1] == '\0')
D 2

E 2
#define equal(s1, s2)   (strcmp(s1, s2) == 0)

E 5
D 2

E 2
/*
 * This structure hold a value.  The type keyword specifies the type of
 * the value, and the union u holds the value.  The value of a boolean
 * is stored in u.num (1 = TRUE, 0 = FALSE).
 */
D 5

E 5
struct value {
D 2
      int type;
      union {
	    char *string;
	    long num;
      } u;
E 2
I 2
D 5
	int     type;
E 5
I 5
	int type;
E 5
	union {
D 5
		char   *string;
		long    num;
	}       u;
E 5
I 5
		char *string;
		long num;
	} u;
E 5
E 2
};

struct operator {
D 2
      short op;			/* which operator */
      short pri;		/* priority of operator */
E 2
I 2
D 5
	short   op;		/* which operator */
	short   pri;		/* priority of operator */
E 5
I 5
	short op;		/* Which operator. */
	short pri;		/* Priority of operator. */
E 5
E 2
};

D 2

E 2
struct filestat {
D 2
      char *name;		/* name of file */
      int rcode;		/* return code from stat */
      struct stat stat;		/* status info on file */
E 2
I 2
D 5
	char   *name;		/* name of file */
	int     rcode;		/* return code from stat */
	struct stat stat;	/* status info on file */
E 5
I 5
	char *name;		/* Name of file. */
	int rcode;		/* Return code from stat. */
	struct stat stat;	/* Status info on file. */
E 5
E 2
};

D 5
static int expr_is_false __P((struct value *));
static void expr_operator __P((int, struct value *, struct filestat *));
D 2
static int lookup_op __P((char *, char *const*));
E 2
I 2
static int lookup_op __P((char *, char *const *));
E 2
static long atol __P((const char *));
static int posix_binary_op __P((char **));
static int posix_unary_op __P((char **));
static int int_tcheck __P((char *));
E 5
I 5
D 6
static long	atol __P((const char *));
E 6
D 9
static void	err __P((const char *, ...));
E 9
static int	expr_is_false __P((struct value *));
static void	expr_operator __P((int, struct value *, struct filestat *));
D 9
static int	int_tcheck __P((char *));
E 9
I 9
static void	get_int __P((char *, long *));
E 9
D 14
static int	lookup_op __P((char *, char *const *));
E 14
I 14
static int	lookup_op __P((char *, const char *const *));
E 14
static void	overflow __P((void));
static int	posix_binary_op __P((char **));
static int	posix_unary_op __P((char **));
static void	syntax __P((void));
E 5

int
D 2
main(argc, argv)  
	int argc;
	char **argv; 
E 2
I 2
main(argc, argv)
D 5
	int     argc;
	char  **argv;
E 5
I 5
	int argc;
	char *argv[];
E 5
E 2
{
D 2
      char **ap;
      char *opname;
      char c;
      char *p;
      int nest;		/* parenthises nesting */
      int op;
      int pri;
      int skipping;
      int binary;
      struct operator opstack[STACKSIZE];
      struct operator *opsp;
      struct value valstack[STACKSIZE + 1];
      struct value *valsp;
      struct filestat fs;
      int ret_val;
E 2
I 2
D 5
	char  **ap;
	char   *opname;
	char    c;
	char   *p;
	int     nest;		/* parentheses nesting */
	int     op;
	int     pri;
	int     skipping;
	int     binary;
E 5
	struct operator opstack[STACKSIZE];
	struct operator *opsp;
	struct value valstack[STACKSIZE + 1];
	struct value *valsp;
	struct filestat fs;
D 5
	int     ret_val;
E 5
I 5
	char  c, **ap, *opname, *p;
	int binary, nest, op, pri, ret_val, skipping;
E 5
E 2

D 2
      INITARGS(argv);
      if (**argv == '[') {
	    if (! equal(argv[argc - 1], "]"))
		  error("missing ]");
	    argv[argc - 1] = NULL;
      }
      ap = argv + 1;
      fs.name = NULL;
E 2
I 2
D 5
	INITARGS(argv);
E 5
I 5
D 7
	if (argv[0] == NULL) {
E 7
I 7
D 9
	if ((p = argv[0]) == NULL) {
E 7
		err("test: argc is zero.\n");
		exit(2);
	}
E 9
I 9
	if ((p = argv[0]) == NULL)
		errx(2, "test: argc is zero");
E 9

E 5
D 7
	if (**argv == '[') {
D 5
		if (!equal(argv[argc - 1], "]"))
			error("missing ]");
E 5
I 5
		if (strcmp(argv[argc - 1], "]"))
E 7
I 7
	if (*p != '\0' && p[strlen(p) - 1] == '[') {
		if (strcmp(argv[--argc], "]"))
E 7
D 9
			err("missing ]");
E 9
I 9
			errx(2, "missing ]");
E 9
E 5
D 7
		argv[argc - 1] = NULL;
E 7
I 7
		argv[argc] = NULL;
E 7
	}
	ap = argv + 1;
	fs.name = NULL;
E 2

D 2
      /*
       * Test(1) implements an inherently ambiguous grammer.  In order to 
       * assure some degree of consistency, we special case the POSIX 
       * requirements to assure correct evaluation for POSIX following 
       * scripts.  The following special cases comply with POSIX 
       * P1003.2/D11.2 Section 4.62.4.
       */
      switch(argc - 1) {
      case 0:          /* % test */
#ifdef PRINT
	      printf("1\n");
#endif
	      return 1;
	      break;
      case 1:          /* % test arg */
#ifdef PRINT
	      printf("%d\n", (*argv[1] == '\0')? 1 : 0);
#endif
	      return (*argv[1] == '\0')? 1 : 0;
	      break;
      case 2:          /* % test op arg */
	      opname = argv[1];
	      if (IS_BANG(opname)) {
#ifdef PRINT
		      printf("%d\n", (*argv[2] == '\0')? 1 : 0);
#endif
		      return (*argv[2] == '\0')? 1 : 0;
	      } else {
		      ret_val = posix_unary_op(&argv[1]);
		      if (ret_val >= 0) {
#ifdef PRINT
			      printf("%d\n", ret_val);
#endif
			      return ret_val;
		      }
	      }
	      break;      
      case 3:         /* % test arg1 op arg2 */
	      if (IS_BANG(argv[1])) {
		      ret_val = posix_unary_op(&argv[1]);
		      if (ret_val >= 0) {
#ifdef PRINT
			      printf("%d\n", !ret_val);
#endif
			      return !ret_val;
		      }
	      } else {
		      ret_val = posix_binary_op(&argv[1]);
		      if (ret_val >= 0) {
#ifdef PRINT
			      printf("%d\n", ret_val);
#endif
 			      return ret_val;
		      }
	      }
	      break;
      case 4:         /* % test ! arg1 op arg2 */
	      if (IS_BANG(argv[1])) {
		      ret_val = posix_binary_op(&argv[2]);
		      if (ret_val >= 0) {
#ifdef PRINT
			      printf("%d\n", !ret_val);
#endif
 			      return !ret_val;
		      }
	      }
	      break;
      default:
	      break;
      }
E 2
I 2
D 5
	/* Test(1) implements an inherently ambiguous grammer.  In order to
	 * assure some degree of consistency, we special case the POSIX
	 * requirements to assure correct evaluation for POSIX following
	 * scripts.  The following special cases comply with POSIX
	 * P1003.2/D11.2 Section 4.62.4. */
	switch (argc - 1) {
	case 0:		/* % test */
		return 1;
E 5
I 5
	/*
	 * Test(1) implements an inherently ambiguous grammer.  In order to
	 * assure some degree of consistency, we special case the POSIX 1003.2
	 * requirements to assure correct evaluation for POSIX scripts.  The
	 * following special cases comply with POSIX P1003.2/D11.2 Section
	 * 4.62.4.
	 */
	switch(argc - 1) {
	case 0:				/* % test */
		return (1);
E 5
		break;
D 5
	case 1:		/* % test arg */
E 5
I 5
	case 1:				/* % test arg */
E 5
D 8
		return (*argv[1] == '\0') ? 1 : 0;
E 8
I 8
D 9
		/* MIPS machine returns NULL of '[ ]' is called. */
		return (argv[1] == 0 || *argv[1] == '\0') ? 1 : 0;
E 9
I 9
		return (argv[1] == NULL || *argv[1] == '\0') ? 1 : 0;
E 9
E 8
		break;
D 5
	case 2:		/* % test op arg */
E 5
I 5
	case 2:				/* % test op arg */
E 5
		opname = argv[1];
		if (IS_BANG(opname))
D 11
			return (*argv[2] == '\0') ? 1 : 0;
E 11
I 11
			return (*argv[2] == '\0') ? 0 : 1;
E 11
		else {
			ret_val = posix_unary_op(&argv[1]);
			if (ret_val >= 0)
D 5
				return ret_val;
E 5
I 5
				return (ret_val);
E 5
		}
		break;
D 5
	case 3:		/* % test arg1 op arg2 */
E 5
I 5
	case 3:				/* % test arg1 op arg2 */
E 5
		if (IS_BANG(argv[1])) {
			ret_val = posix_unary_op(&argv[1]);
			if (ret_val >= 0)
D 5
				return !ret_val;
E 5
I 5
				return (!ret_val);
E 5
		} else {
			ret_val = posix_binary_op(&argv[1]);
			if (ret_val >= 0)
D 5
				return ret_val;
E 5
I 5
				return (ret_val);
E 5
		}
		break;
D 5
	case 4:		/* % test ! arg1 op arg2 */
E 5
I 5
	case 4:				/* % test ! arg1 op arg2 */
E 5
		if (IS_BANG(argv[1])) {
			ret_val = posix_binary_op(&argv[2]);
			if (ret_val >= 0)
D 5
				return !ret_val;
E 5
I 5
				return (!ret_val);
E 5
		}
		break;
	default:
		break;
	}
E 2

D 2
      /*
       * We use operator precedence parsing, evaluating the expression
       * as we parse it.  Parentheses are handled by bumping up the
       * priority of operators using the variable "nest."  We use the
       * variable "skipping" to turn off evaluation temporarily for the
       * short circuit boolean operators.  (It is important do the short
       * circuit evaluation because under NFS a stat operation can take
       * infinitely long.)
       */
E 2
I 2
D 5
	/* We use operator precedence parsing, evaluating the expression as
E 5
I 5
	/*
	 * We use operator precedence parsing, evaluating the expression as
E 5
	 * we parse it.  Parentheses are handled by bumping up the priority
	 * of operators using the variable "nest."  We use the variable
	 * "skipping" to turn off evaluation temporarily for the short
	 * circuit boolean operators.  (It is important do the short circuit
	 * evaluation because under NFS a stat operation can take infinitely
D 5
	 * long.) */
E 2

E 5
I 5
	 * long.)
	 */
E 5
D 2
      opsp = opstack + STACKSIZE;
      valsp = valstack;
      nest = 0;
      skipping = 0;
      if (*ap == NULL) {
	    valstack[0].type = BOOLEAN;
	    valstack[0].u.num = 0;
	    goto done;
      }
      for (;;) {
	    opname = *ap++;
	    if (opname == NULL)
		  goto syntax;
	    if (opname[0] == '(' && opname[1] == '\0') {
		  nest += NESTINCR;
		  continue;
	    } else if (*ap && (op = lookup_op(opname, unary_op)) >= 0) {
		  if (opsp == &opstack[0])
			  goto overflow;
		  --opsp;
		  opsp->op = op;
		  opsp->pri = op_priority[op] + nest;
		  continue;

	    } else {
		  valsp->type = STRING;
		  valsp->u.string = opname;
		  valsp++;
	    }
	    for (;;) {
		  opname = *ap++;
		  if (opname == NULL) {
			if (nest != 0)
			      goto syntax;
			pri = 0;
			break;
		  }
		  if (opname[0] != ')' || opname[1] != '\0') {
			if ((op = lookup_op(opname, binary_op)) < 0)
			      goto syntax;
			op += FIRST_BINARY_OP;
			pri = op_priority[op] + nest;
			break;
		  }
		  if ((nest -= NESTINCR) < 0)
E 2
I 2
	opsp = opstack + STACKSIZE;
	valsp = valstack;
D 5
	nest = 0;
	skipping = 0;
E 5
I 5
	nest = skipping = 0;
E 5
	if (*ap == NULL) {
		valstack[0].type = BOOLEAN;
		valstack[0].u.num = 0;
		goto done;
	}
	for (;;) {
		opname = *ap++;
		if (opname == NULL)
E 2
D 5
			goto syntax;
E 5
I 5
			syntax();
E 5
D 2
	    }
	    while (opsp < &opstack[STACKSIZE] && opsp->pri >= pri) {
		  binary = opsp->op;
		  for (;;) {
			valsp--;
			c = op_argflag[opsp->op];
			if (c == OP_INT) {
			      if (valsp->type == STRING &&
				  int_tcheck(valsp->u.string))
					      valsp->u.num = 
					          atol(valsp->u.string);
			      valsp->type = INTEGER;
			} else if (c >= OP_STRING) { /* OP_STRING or OP_FILE */
			      if (valsp->type == INTEGER) {
				    p = stalloc(32);
E 2
I 2
		if (opname[0] == '(' && opname[1] == '\0') {
			nest += NESTINCR;
			continue;
		} else if (*ap && (op = lookup_op(opname, unary_op)) >= 0) {
			if (opsp == &opstack[0])
D 5
				goto overflow;
E 5
I 5
				overflow();
E 5
			--opsp;
			opsp->op = op;
			opsp->pri = op_priority[op] + nest;
			continue;
D 5

E 5
		} else {
			valsp->type = STRING;
			valsp->u.string = opname;
			valsp++;
		}
		for (;;) {
			opname = *ap++;
			if (opname == NULL) {
				if (nest != 0)
D 5
					goto syntax;
E 5
I 5
					syntax();
E 5
				pri = 0;
				break;
			}
			if (opname[0] != ')' || opname[1] != '\0') {
				if ((op = lookup_op(opname, binary_op)) < 0)
D 5
					goto syntax;
E 5
I 5
					syntax();
E 5
				op += FIRST_BINARY_OP;
				pri = op_priority[op] + nest;
				break;
			}
			if ((nest -= NESTINCR) < 0)
D 5
				goto syntax;
E 5
I 5
				syntax();
E 5
		}
		while (opsp < &opstack[STACKSIZE] && opsp->pri >= pri) {
			binary = opsp->op;
			for (;;) {
				valsp--;
				c = op_argflag[opsp->op];
				if (c == OP_INT) {
D 9
					if (valsp->type == STRING &&
					    int_tcheck(valsp->u.string))
						valsp->u.num =
						    atol(valsp->u.string);
E 9
I 9
					if (valsp->type == STRING)
						get_int(valsp->u.string,
						    &valsp->u.num);
E 9
					valsp->type = INTEGER;
				} else if (c >= OP_STRING) {	
					            /* OP_STRING or OP_FILE */
					if (valsp->type == INTEGER) {
D 5
						p = stalloc(32);
E 5
I 5
						if ((p = malloc(32)) == NULL)
D 9
							err("%s",
							    strerror(errno));
E 9
I 9
							err(2, NULL);
E 9
E 5
E 2
#ifdef SHELL
D 2
				    fmtstr(p, 32, "%d", valsp->u.num);
E 2
I 2
						fmtstr(p, 32, "%d", 
						    valsp->u.num);
E 2
#else
D 2
				    sprintf(p, "%d", valsp->u.num);
E 2
I 2
D 5
						sprintf(p, "%d", valsp->u.num);
E 5
I 5
						(void)sprintf(p,
						    "%d", valsp->u.num);
E 5
E 2
#endif
D 2
				    valsp->u.string = p;
			      } else if (valsp->type == BOOLEAN) {
				    if (valsp->u.num)
					  valsp->u.string = "true";
				    else
					  valsp->u.string = "";
			      }
			      valsp->type = STRING;
			      if (c == OP_FILE
			       && (fs.name == NULL
			           || ! equal(fs.name, valsp->u.string))) {
				    fs.name = valsp->u.string;
				    fs.rcode = stat(valsp->u.string, &fs.stat);
			      }
E 2
I 2
						valsp->u.string = p;
					} else if (valsp->type == BOOLEAN) {
						if (valsp->u.num)
							valsp->u.string = 
						            "true";
						else
							valsp->u.string = "";
					}
					valsp->type = STRING;
D 5
					if (c == OP_FILE
					    && (fs.name == NULL 
						|| !equal(fs.name, 
                                                    valsp->u.string))) {
E 5
I 5
					if (c == OP_FILE && (fs.name == NULL ||
					    strcmp(fs.name, valsp->u.string))) {
E 5
						fs.name = valsp->u.string;
						fs.rcode = 
						    stat(valsp->u.string, 
                                                    &fs.stat);
					}
				}
				if (binary < FIRST_BINARY_OP)
					break;
				binary = 0;
E 2
			}
D 2
			if (binary < FIRST_BINARY_OP)
			      break;
			binary = 0;
		  }
		  if (! skipping)
			expr_operator(opsp->op, valsp, &fs);
		  else if (opsp->op == AND1 || opsp->op == OR1)
			skipping--;
		  valsp++;		/* push value */
		  opsp++;		/* pop operator */
	    }
	    if (opname == NULL)
		  break;
	    if (opsp == &opstack[0])
		  goto overflow;
	    if (op == AND1 || op == AND2) {
		  op = AND1;
		  if (skipping || expr_is_false(valsp - 1))
			skipping++;
	    }
	    if (op == OR1 || op == OR2) {
		  op = OR1;
		  if (skipping || ! expr_is_false(valsp - 1))
			skipping++;
	    }
	    opsp--;
	    opsp->op = op;
	    opsp->pri = pri;
      }
E 2
I 2
			if (!skipping)
				expr_operator(opsp->op, valsp, &fs);
			else if (opsp->op == AND1 || opsp->op == OR1)
				skipping--;
D 5
			valsp++;/* push value */
			opsp++;	/* pop operator */
E 5
I 5
			valsp++;		/* push value */
			opsp++;			/* pop operator */
E 5
		}
		if (opname == NULL)
			break;
		if (opsp == &opstack[0])
D 5
			goto overflow;
E 5
I 5
			overflow();
E 5
		if (op == AND1 || op == AND2) {
			op = AND1;
			if (skipping || expr_is_false(valsp - 1))
				skipping++;
		}
		if (op == OR1 || op == OR2) {
			op = OR1;
			if (skipping || !expr_is_false(valsp - 1))
				skipping++;
		}
		opsp--;
		opsp->op = op;
		opsp->pri = pri;
	}
E 2
D 5
done:
D 2
#ifdef PRINT
	    if (valstack[0].type == STRING)
		  printf("%s\n", valstack[0].u.string);
	    else if (valstack[0].type == INTEGER)
		  printf("%ld\n", valstack[0].u.num);
E 2
I 2
	return expr_is_false(&valstack[0]);
E 2

D 2
	    else if (valstack[0].u.num != 0)
		  printf("true\n");
#endif
E 2
I 2
syntax:   error("syntax error");
overflow: error("Expression too complex");
E 2

E 5
I 5
done:	return (expr_is_false(&valstack[0]));
E 5
D 2
      return expr_is_false(&valstack[0]);

 syntax:   error("syntax error");
 overflow: error("Expression too complex");

E 2
}

D 5

E 5
static int
expr_is_false(val)
D 2
      struct value *val;
E 2
I 2
	struct value *val;
E 2
{
I 14

E 14
D 2
      if (val->type == STRING) {
	    if (val->u.string[0] == '\0')
		  return 1;
      } else {	/* INTEGER or BOOLEAN */
	    if (val->u.num == 0)
		  return 1;
      }
      return 0;
E 2
I 2
	if (val->type == STRING) {
		if (val->u.string[0] == '\0')
D 5
			return 1;
E 5
I 5
			return (1);
E 5
	} else {		/* INTEGER or BOOLEAN */
		if (val->u.num == 0)
D 5
			return 1;
E 5
I 5
			return (1);
E 5
	}
D 5
	return 0;
E 5
I 5
	return (0);
E 5
E 2
}


/*
 * Execute an operator.  Op is the operator.  Sp is the stack pointer;
 * sp[0] refers to the first operand, sp[1] refers to the second operand
 * (if any), and the result is placed in sp[0].  The operands are converted
 * to the type expected by the operator before expr_operator is called.
 * Fs is a pointer to a structure which holds the value of the last call
 * to stat, to avoid repeated stat calls on the same file.
 */
D 5

E 5
static void
expr_operator(op, sp, fs)
D 2
	int op;
E 2
I 2
D 5
	int     op;
E 5
I 5
	int op;
E 5
E 2
	struct value *sp;
	struct filestat *fs;
{
D 2
	int i;
E 2
I 2
D 5
	int     i;
E 5
I 5
	int i;
E 5
E 2

	switch (op) {
	case NOT:
D 2
	    sp->u.num = expr_is_false(sp);
	    sp->type = BOOLEAN;
	    break;
    case ISEXIST:
	    if (fs == NULL || (fs->rcode == -1 && errno == ENOENT))
		    goto false;
	    else
		    goto true;
    case ISREAD:
	    i = 04;
	    goto permission;
    case ISWRITE:
	    i = 02;
	    goto permission;
    case ISEXEC:
	    i = 01;
E 2
I 2
		sp->u.num = expr_is_false(sp);
		sp->type = BOOLEAN;
		break;
	case ISEXIST:
		if (fs == NULL || fs->rcode == -1)
			goto false;
		else
			goto true;
	case ISREAD:
D 5
		i = 04;
E 5
I 5
		i = S_IROTH;
E 5
		goto permission;
	case ISWRITE:
D 5
		i = 02;
E 5
I 5
		i = S_IWOTH;
E 5
		goto permission;
	case ISEXEC:
D 5
		i = 01;
E 2
permission:
D 2
	    if (fs->stat.st_uid == geteuid())
		  i <<= 6;
	    else if (fs->stat.st_gid == getegid())
		  i <<= 3;
	    goto filebit;	/* true if (stat.st_mode & i) != 0 */
    case ISFILE:
	    i = S_IFREG;
	    goto filetype;
    case ISDIR:
	    i = S_IFDIR;
	    goto filetype;
    case ISCHAR:
	    i = S_IFCHR;
	    goto filetype;
    case ISBLOCK:
	    i = S_IFBLK;
	    goto filetype;
    case ISFIFO:
E 2
I 2
		if (fs->stat.st_uid == geteuid())
E 5
I 5
		i = S_IXOTH;
permission:	if (fs->stat.st_uid == geteuid())
E 5
			i <<= 6;
		else if (fs->stat.st_gid == getegid())
			i <<= 3;
		goto filebit;	/* true if (stat.st_mode & i) != 0 */
	case ISFILE:
		i = S_IFREG;
		goto filetype;
	case ISDIR:
		i = S_IFDIR;
		goto filetype;
	case ISCHAR:
		i = S_IFCHR;
		goto filetype;
	case ISBLOCK:
		i = S_IFBLK;
		goto filetype;
I 12
	case ISSYMLINK:
		i = S_IFLNK;
		(void)lstat(sp->u.string, &fs->stat);
		goto filetype;
E 12
	case ISFIFO:
E 2
D 5
#ifdef S_IFIFO
E 5
D 2
	    i = S_IFIFO;
	    goto filetype;
E 2
I 2
		i = S_IFIFO;
		goto filetype;
E 2
D 5
#else
D 2
	    goto false;
E 2
I 2
		goto false;
E 2
#endif
filetype:
D 2
	    if ((fs->stat.st_mode & S_IFMT) == i && fs->rcode >= 0) {
true:
		  sp->u.num = 1;
	    } else {
false:
		  sp->u.num = 0;
	    }
	    sp->type = BOOLEAN;
	    break;
    case ISSETUID:
	    i = S_ISUID;
	    goto filebit;
    case ISSETGID:
	    i = S_ISGID;
	    goto filebit;
    case ISSTICKY:
	    i = S_ISVTX;
E 2
I 2
		if ((fs->stat.st_mode & S_IFMT) == i && fs->rcode >= 0) {
	true:
			sp->u.num = 1;
		} else {
	false:
			sp->u.num = 0;
		}
E 5
I 5
filetype:	if ((fs->stat.st_mode & S_IFMT) == i && fs->rcode >= 0)
true:			sp->u.num = 1;
		else
false:			sp->u.num = 0;
E 5
		sp->type = BOOLEAN;
		break;
	case ISSETUID:
		i = S_ISUID;
		goto filebit;
	case ISSETGID:
		i = S_ISGID;
		goto filebit;
	case ISSTICKY:
		i = S_ISVTX;
E 2
D 5
filebit:
D 2
	    if (fs->stat.st_mode & i && fs->rcode >= 0)
		  goto true;
	    goto false;
    case ISSIZE:
	    sp->u.num = fs->rcode >= 0? fs->stat.st_size : 0L;
	    sp->type = INTEGER;
	    break;
    case ISTTY:
	    sp->u.num = isatty(sp->u.num);
	    sp->type = BOOLEAN;
	    break;
    case NULSTR:
	    if (sp->u.string[0] == '\0')
		  goto true;
	    goto false;
    case STRLEN:
	    sp->u.num = strlen(sp->u.string);
	    sp->type = INTEGER;
	    break;
    case OR1:
    case AND1:
	    /*
	     * These operators are mostly handled by the parser.  If we
	     * get here it means that both operands were evaluated, so
	     * the value is the value of the second operand.
	     */
	    *sp = *(sp + 1);
	    break;
    case STREQ:
    case STRNE:
	    i = 0;
	    if (equal(sp->u.string, (sp + 1)->u.string))
		  i++;
	    if (op == STRNE)
		  i = 1 - i;
	    sp->u.num = i;
	    sp->type = BOOLEAN;
	    break;
    case EQ:
	    if (sp->u.num == (sp + 1)->u.num)
		  goto true;
	    goto false;
    case NE:
	    if (sp->u.num != (sp + 1)->u.num)
		  goto true;
	    goto false;
    case GT:
	    if (sp->u.num > (sp + 1)->u.num)
		  goto true;
	    goto false;
    case LT:
	    if (sp->u.num < (sp + 1)->u.num)
		  goto true;
	    goto false;
    case LE:
	    if (sp->u.num <= (sp + 1)->u.num)
		  goto true;
	    goto false;
    case GE:
	    if (sp->u.num >= (sp + 1)->u.num)
		  goto true;
	    goto false;
E 2
I 2
		if (fs->stat.st_mode & i && fs->rcode >= 0)
E 5
I 5
filebit:	if (fs->stat.st_mode & i && fs->rcode >= 0)
E 5
			goto true;
		goto false;
	case ISSIZE:
		sp->u.num = fs->rcode >= 0 ? fs->stat.st_size : 0L;
		sp->type = INTEGER;
		break;
	case ISTTY:
		sp->u.num = isatty(sp->u.num);
		sp->type = BOOLEAN;
		break;
	case NULSTR:
		if (sp->u.string[0] == '\0')
			goto true;
		goto false;
	case STRLEN:
		sp->u.num = strlen(sp->u.string);
		sp->type = INTEGER;
		break;
	case OR1:
	case AND1:
D 5
		/* These operators are mostly handled by the parser.  If we
E 5
I 5
		/*
		 * These operators are mostly handled by the parser.  If we
E 5
		 * get here it means that both operands were evaluated, so
D 5
		 * the value is the value of the second operand. */
E 5
I 5
		 * the value is the value of the second operand.
		 */
E 5
		*sp = *(sp + 1);
		break;
	case STREQ:
	case STRNE:
		i = 0;
D 5
		if (equal(sp->u.string, (sp + 1)->u.string))
E 5
I 5
		if (!strcmp(sp->u.string, (sp + 1)->u.string))
E 5
			i++;
		if (op == STRNE)
			i = 1 - i;
		sp->u.num = i;
		sp->type = BOOLEAN;
		break;
	case EQ:
		if (sp->u.num == (sp + 1)->u.num)
			goto true;
		goto false;
	case NE:
		if (sp->u.num != (sp + 1)->u.num)
			goto true;
		goto false;
	case GT:
		if (sp->u.num > (sp + 1)->u.num)
			goto true;
		goto false;
	case LT:
		if (sp->u.num < (sp + 1)->u.num)
			goto true;
		goto false;
	case LE:
		if (sp->u.num <= (sp + 1)->u.num)
			goto true;
		goto false;
	case GE:
		if (sp->u.num >= (sp + 1)->u.num)
			goto true;
		goto false;
E 2

D 2
      }
E 2
I 2
	}
E 2
}

D 5

E 5
static int
lookup_op(name, table)
D 2
      char *name;
      char *const*table;
E 2
I 2
D 14
	char   *name;
	char   *const * table;
E 14
I 14
	char *name;
	const char *const * table;
E 14
E 2
{
D 2
      register char *const*tp;
      register char const *p;
      char c = name[1];
E 2
I 2
D 14
	register char *const * tp;
	register char const *p;
E 14
I 14
	const char *const * tp;
	const char *p;
E 14
D 5
	char    c = name[1];
E 5
I 5
	char c;
E 5
E 2

D 2
      for (tp = table ; (p = *tp) != NULL ; tp++) {
	    if (p[1] == c && equal(p, name))
		  return tp - table;
      }
      return -1;
E 2
I 2
D 5
	for (tp = table; (p = *tp) != NULL; tp++) {
		if (p[1] == c && equal(p, name))
			return tp - table;
	}
	return -1;
E 5
I 5
	c = name[1];
	for (tp = table; (p = *tp) != NULL; tp++)
		if (p[1] == c && !strcmp(p, name))
			return (tp - table);
	return (-1);
E 5
E 2
}

static int
posix_unary_op(argv)
D 2
	char **argv;
E 2
I 2
D 5
	char  **argv;
E 5
I 5
	char **argv;
E 5
E 2
{
D 2
	int op, c;
	char *opname;
E 2
I 2
D 5
	int     op, c;
	char   *opname;
E 5
E 2
	struct filestat fs;
	struct value valp;
I 5
	int op, c;
	char *opname;
E 5

	opname = *argv;
D 2
        if ((op = lookup_op(opname, unary_op)) < 0)
E 2
I 2
	if ((op = lookup_op(opname, unary_op)) < 0)
E 2
D 5
		return -1;
E 5
I 5
		return (-1);
E 5
D 2
        c = op_argflag[op];
        opname = argv[1];
        valp.u.string = opname;
        if (c == OP_FILE) {
E 2
I 2
	c = op_argflag[op];
	opname = argv[1];
	valp.u.string = opname;
	if (c == OP_FILE) {
E 2
		fs.name = opname;
		fs.rcode = stat(opname, &fs.stat);
	} else if (c != OP_STRING)
D 5
		return -1;
E 5
I 5
		return (-1);
E 5

	expr_operator(op, &valp, &fs);
	return (valp.u.num == 0);
}

D 5

E 5
static int
posix_binary_op(argv)
D 2
	char **argv;
E 2
I 2
	char  **argv;
E 2
{
D 2
	int op, c;
	char *opname;
E 2
I 2
D 5
	int     op, c;
	char   *opname;
E 5
E 2
	struct value v[2];
I 5
	int op, c;
	char *opname;
E 5
D 2
	
E 2
I 2

E 2
	opname = argv[1];
	if ((op = lookup_op(opname, binary_op)) < 0)
D 5
		return -1;
E 5
I 5
		return (-1);
E 5
	op += FIRST_BINARY_OP;
	c = op_argflag[op];

D 9
	if (c == OP_INT && int_tcheck(argv[0]) && int_tcheck(argv[2])) {
		v[0].u.num = atol(argv[0]);
		v[1].u.num = atol(argv[2]);
E 9
I 9
	if (c == OP_INT) {
		get_int(argv[0], &v[0].u.num);
		get_int(argv[2], &v[1].u.num);
E 9
I 4
	} else {
		v[0].u.string = argv[0];
		v[1].u.string = argv[2];
E 4
	}
	expr_operator(op, v, NULL);
	return (v[0].u.num == 0);
}

/*
 * Integer type checking.
 */
D 9
static int
int_tcheck(v)
E 9
I 9
static void
get_int(v, lp)
E 9
D 2
	char *v;
E 2
I 2
D 5
	char   *v;
E 5
I 5
	char *v;
I 9
	long *lp;
E 9
E 5
E 2
{
D 2
	char *p;
	char outbuf[512];
E 2
I 2
D 5
	char   *p;
	char    outbuf[512];
E 5
I 5
D 9
	char *p;
E 9
I 9
	long val;
	char *ep;
E 9
E 5
E 2

D 9
	for (p = v; *p != '\0'; p++)
D 5
		if (*p < '0' || *p > '9') {
D 2
			snprintf(outbuf, sizeof(outbuf), 
			    "Illegal operand \"%s\" -- expected integer.", v);
			     
			error(outbuf);	
E 2
I 2
			snprintf(outbuf, sizeof(outbuf),
			  "Illegal operand \"%s\" -- expected integer.", v);
			error(outbuf);
E 2
		}
	return 1;
E 5
I 5
		if (!isdigit(*p))
			err("illegal operand \"%s\" -- expected integer.", v);
	return (1);
E 9
I 9
	for (; *v && isspace(*v); ++v);
	if (isdigit(*v)) {
		errno = 0;
		val = strtol(v, &ep, 10);
		if (*ep != '\0')
			errx(2, "%s: trailing non-numeric characters", v);
		if (errno == ERANGE) {
			if (val == LONG_MIN)
				errx(2, "%s: underflow", v);
			if (val == LONG_MAX)
				errx(2, "%s: overflow", v);
		}
		*lp = val;
		return;
	}
	errx(2, "%s: expected integer", v);
E 9
}

static void
syntax()
{
I 14

E 14
D 9
	err("syntax error");
E 9
I 9
	err(2, "syntax error");
E 9
}

static void
overflow()
{
I 14

E 14
D 9
	err("expression is too complex");
}

#if __STDC__
#include <stdarg.h>
#else
#include <varargs.h>
#endif

void
#if __STDC__
err(const char *fmt, ...)
#else
err(fmt, va_alist)
	char *fmt;
        va_dcl
#endif
{
	va_list ap;
#if __STDC__
	va_start(ap, fmt);
#else
	va_start(ap);
#endif
	(void)fprintf(stderr, "test: ");
	(void)vfprintf(stderr, fmt, ap);
	va_end(ap);
	(void)fprintf(stderr, "\n");
	exit(2);
	/* NOTREACHED */
E 9
I 9
	err(2, "expression is too complex");
E 9
E 5
}
D 2










E 2
E 1
