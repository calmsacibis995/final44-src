/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/* 
 * HISTORY
 * $Log:	inline_machdep.c,v $
 * Revision 2.3  90/02/09  21:42:39  berman
 * 	Fix rewrite to write correct number with address register
 * 	and rewrite all logic for pea case.  The old version did
 * 	not work for most cases.
 * 	[90/02/06            rwd]
 * 
 * Revision 2.2  89/02/25  19:34:34  gm0w
 * 	Changes for cleanup.
 * 
 * 21-Jan-88  Robert Baron (rvb) at Carnegie-Mellon University
 *	In cleanup(), iff numargs > 0 and there is no pop fake a push
 *	and hope the code had moved the pop somewhere unobvious.
 *
 *  7-Jan-88  Robert Baron (rvb) at Carnegie-Mellon University
 *	Gcc pops stack after arg push with addql vs addqw -- handle both.
 *
 *  5-Jan-88  Robert Baron (rvb) at Carnegie-Mellon University
 *	Allow for jbsr<space> emitted by GNU vs jbsr\t emitted by PCC.
 *
 * 18-Dec-87  Robert Baron (rvb) at Carnegie-Mellon University
 *	Created
 *
 */

#include <stdio.h>
#include <ctype.h>

#include <inline/inline.h>

extern char *strcpy();
extern char *strcat();
extern char *index();

/*
 * The routines and tables in this file must be rewritten
 * for each new machine that this program is ported to.
 */
extern struct pats tst[];
extern struct pats mc68020_ptab[];
extern struct pats sun_ptab[];
extern struct pats unix_ptab[];
extern struct pats mach_schnell_ptab[];

struct pats *inittables[] = {
/*	tst,*/
	mc68020_ptab,
	sun_ptab,
	unix_ptab,
	mach_schnell_ptab,
	0
};

struct pats *subset_inittables[] = {
	mc68020_ptab,
	sun_ptab,
	unix_ptab,
	mach_schnell_ptab,
	0
};

/*
 * Instruction stop table.
 * All instructions that implicitly modify any of the temporary
 * registers, change control flow, or implicitly loop must be
 * listed in this table. It is used to find the end of a basic
 * block when scanning backwards through the instruction stream
 * trying to merge the inline expansion.
 */
struct inststoptbl inststoptable[] = {
		/*
		 * This table does not include the floating point ops, 
		 * since the kernel does not currently use them.
		 */
	{ "bra" }, { "bsr" }, 
	{ "bcc" }, { "bcs" }, { "beq" }, { "bne" }, { "bge" }, { "bgt" }, { "bhi" },
	{ "blr" }, { "bls" }, { "blt" }, { "bmi" }, { "bpl" }, { "bvc" }, { "bvs" },

	{ "bras" }, { "bsrs" },
	{ "bccs" }, { "bcss" }, { "beqs" }, { "bnes" }, { "bges" }, { "bgts" }, { "bhis" },
	{ "blrs" }, { "blss" }, { "blts" }, { "bmis" }, { "bpls" }, { "bvcs" }, { "bvss" },

	{ "bral" }, { "bsrl" },
	{ "bccl" }, { "bcsl" }, { "beql" }, { "bnel" }, { "bgel" }, { "bgtl" }, { "bhil" },
	{ "blrl" }, { "blsl" }, { "bltl" }, { "bmil" }, { "bpll" }, { "bvcl" }, { "bvsl" },

	{ "jmp" }, { "jsr" }, { "jra" }, { "jbsr" }, { "callm" },
	{ "rte" }, { "rtr" }, { "rtd" }, { "rts" }, { "rtm" },
	{ "jcc" }, { "jcs" }, { "jeq" }, { "jne" }, { "jge" }, { "jgt" }, { "jhi" },
	{ "jle" }, { "jls" }, { "jlt" }, { "jmi" }, { "jpl" }, { "jvc" }, { "jvs" },

	{ "dbra" }, { "dbf" }, { "dbt" },
	{ "dbcc" }, { "dbcs" }, { "dbeq" }, { "dbne" }, { "dbge" }, { "dbgt" }, { "dbhi" },
	{ "dble" }, { "dbls" }, { "dblt" }, { "dbmi" }, { "dbpl" }, { "dbvc" }, { "dbvs" },

	{ "bkpt" }, { "trap" }, { "trapv" },
	{ "chk" }, { "chkw" }, { "chkl" }, { "chk2b" }, { "chk2w" }, { "chk2l" },

	{ "trapf" }, { "trapt" },
	{ "dbcc" }, { "dbcs" }, { "dbeq" }, { "dbne" }, { "dbge" }, { "dbgt" }, { "dbhi" },
	{ "dble" }, { "dbls" }, { "dblt" }, { "dbmi" }, { "dbpl" }, { "dbvc" }, { "dbvs" },

	{ "trapfw" }, { "traptw" },
	{ "trapccw" }, { "trapcsw" }, { "trapeqw" }, { "trapnew" }, { "trapgew" },
	{ "trapgtw" }, { "traphiw" }, { "traplew" }, { "traplsw" }, { "trapltw" },
	{ "trapmiw" }, { "trapplw" }, { "trapvcw" }, { "trapvsw" },

	{ "trapfl" }, { "traptl" },
	{ "trapccl" }, { "trapcsl" }, { "trapeql" }, { "trapnel" }, { "trapgel" },
	{ "trapgtl" }, { "traphil" }, { "traplel" }, { "traplsl" }, { "trapltl" },
	{ "trapmil" }, { "trappll" }, { "trapvcl" }, { "trapvsl" },


	{ "link" }, { "linkw" }, { "linkl" }, { "unlk" }, { "movemw" }, { "moveml" },

	{ "" }
};

/*
 * Check to see if a line is a candidate for replacement.
 * Return pointer to name to be looked up in pattern table.
 */
char *
doreplaceon(cp)
	char *cp;
{

	if (! bcmp(cp, "jbsr", 4) )
		return (cp + 5);	/* 5 is to skip \t (PCC) or space (GNU) */
	else if (! bcmp(cp, "bsr", 3) != 0)
		return (cp + 4);	/* 4 is to skip \t (PCC) or space (GNU) */
	else if (! bcmp(cp, "jsr", 3) != 0)
		return (cp + 4);	/* 4 is to skip \t (PCC) or space (GNU) */
	else
		return (0); 
}

/*
 * Find out how many arguments the function is being called with.
 * A return value of -1 indicates that the count can't be determined.
 */
int
countargs(cp)
	char *cp;
{
	return (-1);
}

/*
 * Find the next argument to the function being expanded.
 */
nextarg(argc, argv)
	int argc;
	char *argv[];
{
	register char *lastarg = argv[2];
#ifdef	DEBUG
	register int i;
	printf("nextarg: %d\n", argc);
	for (i=0; i< argc; printf("#%s# ", argv[i++]));
	printf("\n");
#endif	DEBUG
	if (argc == 3 &&
	    bcmp(argv[0], "movl", 4) == 0 &&
	    bcmp(argv[1], "sp@+", 4) == 0 &&
	    lastarg[0] == 'd' && isdigit(lastarg[1]) && lastarg[2] == '\0')
		return (lastarg[1] - '0');
	if (argc == 3 &&
	    bcmp(argv[0], "movl", 4) == 0 &&
	    bcmp(argv[1], "sp@+", 4) == 0 &&
	    lastarg[0] == 'a' && isdigit(lastarg[1]) && lastarg[2] == '\0')
		return (lastarg[1] - '0' + 8);
	return (-1);
}

/*
 * Determine whether the current line pushes an argument.
 */
ispusharg(argc, argv)
	int argc;
	char *argv[];
{
#ifdef	DEBUG
	register int i;
	printf("ispusharg: %d\n", argc);
	for (i=0; i< argc; printf("#%s# ", argv[i++]));
	printf("\n");
#endif	DEBUG
	if (argc < 2)
		return (0);
	if (bcmp(argv[argc - 1], "sp@-", 4) == 0)
		return (1);
	if (bcmp(argv[0], "pea", 3) == 0)
		return (1);
	return (0);
}

/*
 * Determine which (if any) registers are modified
 * Return register number that is modified, -1 if none are modified.
 */
modifies(argc, argv)
	int argc;
	char *argv[];
{
	/*
	 * For the Sequent Balance all we care about are r0 to r2
	 */
	register char *lastarg = argv[argc - 1];
#ifdef	DEBUG
	register int i;
	printf("modifies: %d\n", argc);
	for (i=0; i< argc; printf("#%s# ", argv[i++]));
	printf("\n");
#endif	DEBUG
	if (lastarg[0] == 'd' && isdigit(lastarg[1]) && lastarg[2] == '\0')
		return (lastarg[1] - '0');
	if (lastarg[0] == 'a' && isdigit(lastarg[1]) && lastarg[2] == '\0')
		return (lastarg[1] - '0' + 8);
	return (-1);
}

/*
 * Rewrite the instruction in (argc, argv) to store its
 * contents into arg instead of onto the stack. The new
 * instruction is placed in the buffer that is provided.
 */
rewrite(instbuf, argc, argv, target)
	char *instbuf;
	int argc;
	char *argv[];
	int target;
{
register int r = (target < 8) ? 'd' : 'a';

	if (target > 7) target -= 8;

	switch (argc) {
	case 0:
		instbuf[0] = '\0';
		fprintf(stderr, "blank line to rewrite?\n");
		return;
	case 1:
		sprintf(instbuf, "\t%s\n", argv[0]);
		fprintf(stderr, "rewrite?-> %s", instbuf);
		return;
	case 2:
	    if (bcmp(argv[0], "pea", 3) == 0) {
		register int l = strlen(argv[1]) - 1;
		if (argv[1][l] == '@') {
		  argv[1][l] = 0;
		  sprintf(instbuf,"\tmovl\t%s, %c%d\n",argv[1],r,target);
		} else {
		  if (r == 'a') {
		    sprintf(instbuf,"\tlea\t%s, %c%d\n", argv[1], r, target);
		  } else {
		    sprintf(instbuf, "\tpea\t%s\n", argv[1]);
		    sprintf(instbuf, "\tmovl\tsp,%c%d\n", r, target);
		  }
		}
	    } else {
		  sprintf(instbuf, "\t%s\t%c%d\n", argv[0], r, target);
	    }
	    return;
	case 3:
		sprintf(instbuf, "\t%s\t%s, %c%d\n", argv[0], argv[1], r, target);
		return;
	case 4:
		sprintf(instbuf, "\t%s\t%s, %s, %c%d\n",
			argv[0], argv[1], argv[2], r, target);
		return;
	case 5:
		sprintf(instbuf, "\t%s\t%s, %s, %s, %c%d\n",
			argv[0], argv[1], argv[2], argv[3], r, target);
		return;
	default:
		sprintf(instbuf, "\t%s\t%s", argv[0], argv[1]);
		argc -= 2, argv += 2;
		while (argc-- > 0) {
			(void) strcat(instbuf, ", ");
			(void) strcat(instbuf, *argv++);
		}
		(void) strcat(instbuf, "\n");
		fprintf(stderr, "rewrite?-> %s", instbuf);
		return;
	}
}

/*
 * Do any necessary post expansion cleanup.
 */
/*ARGSUSED*/
cleanup(numargs)
	int numargs;
{
	register char *cp = line[bufhead], *lp;

	pre_read = 0;

	if (!numargs)
		return;

	fgets(line[bufhead], MAXLINELEN, stdin);

	if (lp = index(cp, LABELCHAR))
		cp = lp + 1;
	for (; isspace(*cp); cp++) ;
	
	if (! bcmp(cp, "addqw", 5) )
		return;
	else if (! bcmp(cp, "addql", 5) )
		return;
	else if (! bcmp(cp, "addw", 5) )
		return;
	else if (! bcmp(cp, "addl", 5) )
		return;
	else {
		pre_read = 1;
		if (numargs < 3)
			printf("	subql	#%d, sp\n", 4*numargs);
		else
			printf("	subw	#%d, sp\n", 4*numargs);
	}
	return;
}
