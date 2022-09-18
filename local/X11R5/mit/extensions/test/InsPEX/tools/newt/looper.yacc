
/* $XConsortium: looper.yacc,v 5.4 91/11/26 14:42:32 hersh Exp $ */

/*****************************************************************
Copyright (c) 1989, 1990, 1991 by Sun Microsystems, Inc. and the X Consortium.

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
 * looper.grammar:
 *  Yacc grammar, with actions, for the looper end of Newt.
 * The lexical analyzer is specified in looper.lex.
 *
 * Also contains the functions for the building and execution of the
 * structures corresponding to looper functions.
 */

%{
#ifndef lint
	static char sccsid[] = "@(#)looper.yacc	5.2 2/13/91 Copyr. Sun Microsystems";
#endif
#include <stdio.h>
#include <fcntl.h>
#ifdef SYSV 
#define index strchr
#define rindex strrchr
#include <string.h>
#else
#include <string.h>
#include <strings.h>
#endif
#include "looper.h"
#include "debugger.h"
#include "var.h"
#include "interpret.h"

#define YYMAXDEPTH 500		/* stack size for parsing */
#define MAXLINELEN 1024		/* maximum size of predicate output line */

extern char *optarg;		/* for getopt */
extern int optind, opterr;

/* 
 *execution modes:
 */
static int interactive = 0;	/* nonzero value indicates interactive mode */
static int printonly = 0;	/* nonzero means just print looper output, */
				/* rather than interpret.		*/
static int trace = 0;		/* nonzero means print out interpreted */
				/* commands before passing on to interpreter*/
int N_translate = 0;		/* translate-to-C mode */

static MACROVARLIST *macro_vars = NULL; /* list of variables being used */
				/* for macro definition */
static char *macro_name = NULL;	/* name of macro currently being defined */
static FUNC *macro_list = NULL;	/* list of currently defined macros */
char *N_filepath;    /* path of directories in which to search for files */

static char *tmpstr1, *tmpstr2;	/* needed to workaround sun4 compiler prob */


/* we keep a stack of recursively-invoked source files.*/
#define MAXFILES 16		
static FILE *filestack[MAXFILES];
static char *filenamestack[MAXFILES];
static int filelinestack[MAXFILES] = {0};
static int fileindex = 0;

static char *filename = "standard input";  /* current file being parsed */
static int lineno = 1;			    /* line number in file being parsed */

static char *expand_arg(), *copy_string();

/* for debugging mode */
static int debug=0;		/* 1 if debug is ON, 0 otherwise */
static int syntaxerr=0;		/* 1 if syntax error occured, 0 otherwise */
FUNC *N_funchead;		/* pointer to start of function structure */
static FUNC *functail; 		/* pointer to end of function structure */
int N_2process;			/* 2 process debugging mode */
#define IFSTACK 0
#define FORSTACK 1
#define FOREACHSTACK 2
static char *curr_debug_file;  /* file currently being debugged */

/* for translation mode */
static int countervars = 0;	/* number of counter variables to declare */
static int prepend_underscore = 0; /* 1 means add "_" before predicates */
static char *headertext_file = NULL;  /* file to insert at head of C prog */

%}

/* union defining the possible value types */
%union {
	char *strval;
	FUNC *funval;
	ARGTYPE  *argval;
	
}

%token LEFT RIGHT SEMI COMMA EQUAL FOREACH FOR END IF THEN ELSE ENDIF 
%token MACRO ENDMACRO READFILE RESUME
%token <strval>  VAR ARG IDENT SHCOMMENT
%type <funval> fun foreachloop forloop ifstmnt funlist
%type <argval> varlist var macvarlist macvar looparglist arglist arg
%type <strval> ident optcomment
%%
immed_funlist : /* empty */
	|	immed_funlist immed_fun optsemi
	;

immed_fun :	fun
			{

			if (interactive) N_execute($1,EXECUTE_NORMAL);
			else {
			    functail->next = $1;
			    functail = functail->next;			    
			}
			 if (interactive && fileindex==0) fprintf(stderr,">");
			 fflush(stdout); }
	|	error
			{
				static char ln[256];


                                syntaxerr = 1;

				fgets(ln, 256, yyin);
				fprintf(stderr,
				"looper syntax error, line %d of %s, at or near '%s' -- continuing\n",
				lineno, filename, yytext);}

	;

fun:		foreachloop	
			{$$ = $1;}
	|	forloop	
			{$$ = $1;}
	|	ifstmnt	
			{$$ = $1;}
	|	ident LEFT arglist RIGHT
			{$$ = pred(NULL, $1, $3);}
	|	ident EQUAL ident LEFT arglist RIGHT
			{$$ = pred($1, $3, $5);}
	|	var EQUAL ident LEFT arglist RIGHT
			{$$ = pred($1->name, $3, $5);}
	|	MACRO ident 
			{ start_macro($2);}
		LEFT macvarlist RIGHT funlist ENDMACRO
			{$$ = end_macro($2, $5, $7, filename);}
	|	var EQUAL arg	
			{$$ = assign($1, $3);}
	|	READFILE arg
			{ if (fileindex==MAXFILES-1) fatal("Too many files");
			  filestack[fileindex]=yyin;
			  if ((yyin=N_fopen_from_path($2->name, "r", N_filepath))==NULL) {
				yyin=filestack[fileindex];
				fprintf(stderr,"looper error: could not open file %s -- continuing\n", $2->name);
				YYERROR;
			   } else {
				filenamestack[fileindex] = filename;
				filename = $2->name;
				filelinestack[fileindex++]=lineno;
				lineno=1;
			  	if (debug) N_debuguse($2->name);
			   }
			}
		funlist	RESUME
			{
			    /* note that stack popping occurs in looper.lex.*/
			    $$ = source($2, $4);
			}
	|	SHCOMMENT
			{ $$ = comment(yylval.strval); }
	;	

foreachloop:	FOREACH varlist LEFT looparglist RIGHT funlist  END
			{$$ = foreach($2, $4, $6);}
	;

forloop:	FOR LEFT var SEMI arg SEMI arg SEMI arg RIGHT funlist END
			{$$ = forloop($3, $5, $7, $9, $11);}
	|	FOR LEFT var SEMI arg SEMI arg  RIGHT funlist END
			{ /* increment left implicit */
			   $$ = forloop($3, $5, $7, NULL, $9);
			}
	|	FOR LEFT var SEMI arg  RIGHT funlist END
			{ /* start and increment left implicit */
			  $$ = forloop($3, NULL, $5, NULL, $7);
			}
	;

ifstmnt:	IF LEFT arg RIGHT optthen funlist ELSE funlist ENDIF
			{$$ = ifstatement($3, NULL, NULL, $6, $8);}
	|	IF LEFT arg RIGHT optthen funlist ENDIF
			{$$ = ifstatement($3, NULL, NULL, $6, NULL);}
	|	IF LEFT arg arg arg RIGHT optthen funlist ELSE funlist ENDIF
			{if (!is_binary_oper($4->name)) {
			    fprintf(stderr,"looper error, line %d of %d: %s is not a valid operator for if-statement condition\n", lineno, filename, $4->name);
			    YYERROR;
			 } else {
			    $$ = ifstatement($3, $4, $5, $8, $10);
			 }
			}
	|	IF LEFT arg arg arg RIGHT optthen funlist ENDIF
			{if (!is_binary_oper($4->name)) {
			    fprintf(stderr,"looper error, line %d of %d: %s is not a valid operator for if-statement condition\n", lineno, filename, $4->name);
			    YYERROR;
			 } else {
			    $$ = ifstatement($3, $4, $5, $8, NULL);
			 }
			}
	;
funlist:	
	fun optsemi funlist
			{append_fun($1, $3); $$ = $1;}
	|
	fun optsemi
			{$$ = $1;}
	;

varlist:	var varlist
			{append_arg($1, $2); $$ = $1;} 
	|	var
			{$$ = $1;}
	;

macvarlist:	/* empty - macro may have no arguments */
			{$$ = NULL;}
	|	macvar COMMA macvarlist
			{append_arg($1, $3); $$ = $1;} 
	|	macvar
			{$$ = $1;}
	;

var:		VAR
			{$$ = arg(yylval.strval);}
	;

macvar:		VAR
			{
			$$ = new_macvar(yylval.strval);
			}
	;
looparglist:	/* empty */
			{$$ = NULL;}
	|	arg SEMI optcomment looparglist
			{$1->cmt=$3; append_arg($1, $4); $$ = $1;}
	|	arg optcomment
			{$1->cmt=$2; $$=$1;}
	;

arglist:	/* empty */
			{$$ = NULL;}
	|	arg COMMA arglist
			{append_arg($1, $3); $$ = $1;}
	|	arg
			{$$=$1;}
	;

arg:		ARG
			{$$ = arg(yylval.strval);}
	|	var
			{$$ = $1;}
	|	ident
			{$$ = arg($1);}
	;

ident:		IDENT
			{tmpstr1 = (char *) malloc(strlen(yylval.strval)+1); 
			 strcpy(tmpstr1, yylval.strval);
			 $$ = tmpstr1;}

optcomment:	/* empty */
			{$$ = NULL;}
	|
		SHCOMMENT
			{tmpstr1 = (char *) malloc(strlen(yylval.strval)+1); 
			 strcpy(tmpstr1, yylval.strval);
			 $$ = tmpstr1;}
	;
optsemi:	/* empty */
	|	SEMI
	;

optthen:    /* empty */
	|	THEN
	;

%%
#include "lex.yy.c"

/*
 * N_execute() - the main execution routine.
 * Execute the function structure list pointed to by func, in the manner 
 * appropriate to its type.  The execution of the first function is
 * carried out, and then N_execute is called recursively on the rest of 
 * the list.
*/
void
N_execute(func,exeflag)
	FUNC *func;
	int exeflag;
{
	ARGTYPE *arg, *val, *macvar;
	char *valstring, *varstring, *tmpstr;
	char outstring[MAXLINELEN], *outptr;
	FUNC *mac;
	int curflag=exeflag;
	int bool;

        if (debug) {
            if (!N_isskip 
		    || (N_isskip && func->lineno >= N_resumeat)) {
                if (N_isskip) N_isskip = 0;
		if (func->lineno) {	/* is this line breakable? */
                    if ((N_getflag(N_fstr->userbreakpt,func->lineno) && exeflag == EXECUTE_NORMAL)
				|| N_isstep 
				|| (N_isnext && exeflag == EXECUTE_NORMAL) ) {
			if (N_isstep && N_stepcount >1) {
				N_stepcount--;
			} else if (N_isnext && N_nextcount >1) {
				N_nextcount--;
			} else {
                            printf("Debugger: stopped at line %d in file %s\n", func->lineno,N_fstr->name);
                            printf("\t%d %s", func->lineno,N_fstr->fileimage[func->lineno-1]);
                            N_debugger(func->lineno+1);
	    		    if (N_isskip && func->lineno >= N_resumeat) N_isskip = 0;
			    if (N_isnext) curflag = EXECUTE_BYPASS;
		        }
                    }
                }
            }
        }
    if (!N_isskip)
	switch (func->ftype) {
	    case FOREACHLOOP:
		val = func->fun.fl.values;
		/* loop runs until we're out of loop variable values */
		while(val != NULL) { 
			/* set a value for each loop variable */
			for (arg=func->fun.fl.loopvars; arg!=NULL; 
					arg=arg->next) {
				if (val==NULL) {
				    fatal("wrong number of loopvars\n");
				}
				set_val(arg->name, val->name);
				val = val->next;
			}
                        N_execute(func->fun.fl.body,curflag);
		}
		break;
	    case FORLOOP: 
		{
		    int i, end, increment;
		    char numstring[12];

		    /* get start value */
		    if (func->fun.forl.start==NULL) {i = 1;} 
		    else {
			if((valstring=value(func->fun.forl.start->name))==NULL){
			    fprintf(stderr, "Looper error: forloop start, %s, has no value\n", 
				    func->fun.forl.start->name);
			    exit(1);
			}
			i = atoi(valstring);
		    }

		    /* get end value */
		    if((valstring=value(func->fun.forl.end->name))==NULL){
			fprintf(stderr, "Looper error: forloop end, %s, has no value\n", 
				func->fun.forl.start->name);
			exit(1);
		    }
		    end = atoi(valstring);

		    /* get increment value */
		    if (func->fun.forl.incr==NULL) {increment = 1;} 
		    else {
			if((valstring=value(func->fun.forl.incr->name))==NULL){
			    fprintf(stderr, "Looper error: forloop increment, %s, has no value\n", 
				    func->fun.forl.start->name);
			    exit(1);
			}
			increment = atoi(valstring);
		    }

		    /* iterate over the loop */
		    for ( ; i <= end; i+=increment) {
			sprintf(numstring, "%d", i);
			set_val(func->fun.forl.loopvar->name,numstring);
                        N_execute(func->fun.forl.body,curflag);
		    }
		}
		break;
	    case IFSTMNT:
		if (func->fun.ifstr.oper==NULL)
		    /* the if statement has a unary condition */
		    bool = eval_condition(func->fun.ifstr.cond);
		else
		    /* the if statement has a binary operator condition */
		    bool = eval_binary_oper(func->fun.ifstr.oper->name, 
			func->fun.ifstr.cond,
			func->fun.ifstr.cond2);
		if (bool) {
		    if (func->fun.ifstr.thenbody==NULL) 
			fatal("empty if-then body\n");
		    N_execute(func->fun.ifstr.thenbody, curflag);
		} else if (func->fun.ifstr.elsebody!=NULL) {
		    N_execute(func->fun.ifstr.elsebody, curflag);
		}
		break;
	    case PRED:
		if (func->fun.pred.dest!=NULL) {
		    /* function assignment can't be a macro */
		    mac=NULL;
		} else { 
		    /* see whether predicate is a macro invocation */ 
		    for(mac=macro_list;
			mac!=NULL && 
			    strcmp(mac->fun.macro.name,func->fun.pred.name)!=0;
			mac=mac->fun.macro.next_macro);
		}
		if (mac!=NULL) {
			/* is a macro -- must first set vars */
			for (arg=func->fun.pred.args, 
					 macvar=mac->fun.macro.macvars;
			     (arg != NULL) && (macvar!=NULL); 
			     arg=arg->next, macvar=macvar->next) {
				set_val(macvar->name, arg->name);
			}
			if (arg==NULL && macvar!=NULL) {
				fprintf(stderr, "macro %s: not enough args\n",
					func->fun.pred.name);
				exit(1);
			}
			if (arg!=NULL && macvar==NULL) {
			      fprintf(stderr, "macro %s: extra args ignored\n",
					func->fun.pred.name);
			}
			/* I think I'm safe using != instead of strcmp...*/
			if (debug && curr_debug_file!=mac->fun.macro.fname) { 
			    tmpstr = curr_debug_file;
			    N_debuguse(curr_debug_file = mac->fun.macro.fname);
			    N_execute(mac->fun.macro.body,curflag);
			    N_debuguse(curr_debug_file = tmpstr);
			} else {
			    N_execute(mac->fun.macro.body,curflag);
			}
		} else { 
			/* is not a macro invocation -- assemble output line */
			outptr = copy_string(outstring, func->fun.pred.name);
			outptr = copy_string(outptr, "(");
			for (arg=func->fun.pred.args; 
				arg != NULL; arg=arg->next) { 
				valstring = value(arg->name);
				if (valstring == NULL) {
				      fprintf(stderr, "Looper error: unknown variable, %s\n", arg->name);
				      exit(1);
				}
				if (index(valstring,'@')==NULL) { 
					outptr = copy_string(outptr, valstring);
				} else {
					/* must expand variables in arg */
					outptr = expand_arg(outptr, valstring);
				}
				if (arg->next != NULL) {
					outptr = copy_string(outptr,", ");
				}
			}
			outptr = copy_string(outptr,")");
			if (trace || printonly) {
			    if (func->fun.pred.dest!=NULL) 
				printf("%s = %s\n", value(func->fun.pred.dest), outstring);
			    else printf("%s\n", outstring);
			} 
			if(!printonly) N_interpret(outstring,
			    value(func->fun.pred.dest));
		}
		break;
	    case MACRODEF:
		/* put macro at head of macro list */
		if (macro_list!=func) { 
		    /* Isn't the first macro in list. */
		    /* Remove from curr. place in macro list if already there*/
		    if (func->fun.macro.prev_macro!=NULL)
			func->fun.macro.prev_macro->fun.macro.next_macro=
			    func->fun.macro.next_macro;
		    if (func->fun.macro.next_macro!=NULL)
			func->fun.macro.next_macro->fun.macro.prev_macro=
			    func->fun.macro.prev_macro;
		    /* insert at head of list of defined macros */
		    func->fun.macro.next_macro = macro_list;
		    func->fun.macro.prev_macro = NULL;
		    if (macro_list!=NULL) macro_list->fun.macro.prev_macro=func;
		    macro_list = func;
		}
		break;
	    case ASSIGN:
		varstring = func->fun.assign.var->name;
		valstring = func->fun.assign.val->name;
		set_val(varstring, valstring);
		break;
	    case SOURCE:
		if (debug) {
		    tmpstr = curr_debug_file;
		    N_debuguse(curr_debug_file = func->fun.source.fname);
		}
		N_execute(func->fun.source.body, curflag);
		if (debug) N_debuguse(curr_debug_file = tmpstr);
		break;
	    case COMMENT:
		/* do nothing */
		break;
	    default:
		fatal("(internal) -- unknown function type\n");
		break;
	}
	if (func->next != NULL) {
		N_execute(func->next,exeflag);
	}
}


/* generate_C_file:
 * generate the C code from the parsed structure supplied,
 * and output the result into a file whose name is derived from the supplied
 * filename (or to stdout if filename is null).
 * two passes are made through the data structure -- the first
 * passes information to the interpreter in order to derive 
 * variable declaration information, and the second outputs the
 * actual code.
 */
static
int
generate_C_file(func, filename)
    FUNC *func;
    char *filename;
{
    FILE *outfile, *hfile;
    char Cfilename[64], *period;
    int i, character;

   if (filename==NULL) outfile=stdout;
    else {
	strcpy(Cfilename,filename);
	if ((period=rindex(Cfilename,'.'))==NULL) strcat(Cfilename,".c");
	else strcpy(period,".c");
	outfile = fdopen(creat(Cfilename, 0666),"w+");
	if (outfile==NULL) {
	    fprintf(stderr, "ERROR - could not create file %s\n",Cfilename);
	    exit(1);
	}
    }
    fprintf(outfile, "/* Automatically-generated translation of %s */\n\n",filename);

    if (headertext_file) {
	/* include the file's text in the translation */
	if ((hfile=fopen(headertext_file,"r"))==NULL) {
	    fprintf(stderr,"ERROR - could not open header file %s\n",
		headertext_file);
	    exit(1);
	}
	while ((character=getc(hfile))!=EOF) putc((char)character,outfile);
	fclose(hfile);
	fflush(outfile);
    }

    fprintf(outfile, "\nmain()\n{\n");

    /* first pass through the data structure just passes information
     * to the interpreter in order to get variable declaration info.
     */
    execute_for_trans(func);
    /*
     * insert interpreter's declarations, and declaration of loop
     * counters.
     */
    N_generate_C_declaration(outfile);
    if (countervars) {
	fprintf(outfile, "int ctr1");
	if (countervars>1)
	    for(i=2; i<=countervars; i++)
		fprintf(outfile, ", ctr%i", i);
	fprintf(outfile, ";\n\n");
    }
    /*
     * generate the program body and closing brace
     */
    countervars=0;
    translate_func(func, outfile);
    fprintf(outfile, "}\n"); 
    fclose(outfile);
}


/*
 * execute_for_trans:
 * traverse the function structure to allow the interpreter
 * to generate a list of the variables that will have to
 * be declared in order to generate the C translation.
 */
static
int
execute_for_trans(func)
	FUNC *func;
{
	ARGTYPE *arg, *val, *macvar;
	char *valstring, *varstring, *tmpstr;
	char outstring[MAXLINELEN], *outptr;
	FUNC *mac;
	int i;

	switch (func->ftype) {
	    case FOREACHLOOP:
		val = func->fun.fl.values;
		countervars++;
		/* 
		 * execute with values from value list, to
		 * get declarations for any vars named there.
		 */
		for (i=0; val != NULL; i++) { 
			/* set a value for each loop variable */
			for (arg=func->fun.fl.loopvars; arg!=NULL; 
					arg=arg->next,val=val->next) {
				if (val==NULL) {
				    fatal("wrong number of loopvars\n");
				}
				set_val(arg->name, val->name);
			}
                        N_execute(func->fun.fl.body,EXECUTE_NORMAL);
		}
		/*
		 * assign C variable names to looper variables,
		 * traverse the body
		 */
		for (arg=func->fun.fl.loopvars; arg!=NULL; arg=arg->next) {
		    set_val(arg->name, arg->name+1);
		}
		execute_for_trans(func->fun.fl.body);
		break;

	    case FORLOOP: 
		{
		    set_val(func->fun.forl.loopvar->name,
			func->fun.forl.loopvar->name + 1);
                    execute_for_trans(func->fun.forl.body);
		}
		break;
	    case IFSTMNT:
		execute_for_trans(func->fun.ifstr.thenbody);
		if (func->fun.ifstr.elsebody!=NULL) {
		    execute_for_trans(func->fun.ifstr.elsebody);
		}
		break;
	    case PRED:
		if (func->fun.pred.dest!=NULL) {
		    /* function assignment can't be a macro */
		    mac=NULL;
		} else { 
		    /* see whether predicate is a macro invocation */ 
		    for(mac=macro_list;
			mac!=NULL && 
			    strcmp(mac->fun.macro.name,func->fun.pred.name)!=0;
			mac=mac->fun.macro.next_macro);
		}
		if (mac!=NULL) {
			/* is a macro -- must first set vars */
			for (arg=func->fun.pred.args, 
					 macvar=mac->fun.macro.macvars;
			     (arg != NULL) && (macvar!=NULL); 
			     arg=arg->next, macvar=macvar->next) {
				set_val(macvar->name, arg->name);
			}
			if (arg==NULL && macvar!=NULL) {
				fprintf(stderr, "macro %s: not enough args\n",
					func->fun.pred.name);
				exit(1);
			}
			if (arg!=NULL && macvar==NULL) {
			      fprintf(stderr, "macro %s: extra args ignored\n",
					func->fun.pred.name);
			}
			execute_for_trans(mac->fun.macro.body);

		} else { 
			/* is not a macro invocation -- assemble output line */
			outptr = copy_string(outstring, func->fun.pred.name);
			outptr = copy_string(outptr, "(");
			for (arg=func->fun.pred.args; 
				arg != NULL; arg=arg->next) { 
				valstring = value(arg->name);
				if (valstring == NULL) {
				      fprintf(stderr, "Looper error: unknown variable, %s\n", arg->name);
				      exit(1);
				}
				if (index(valstring,'@')==NULL) { 
					outptr = copy_string(outptr, valstring);
				} else {
					/* must expand variables in arg */
					outptr = expand_arg(outptr, valstring);
				}
				if (arg->next != NULL) {
					outptr = copy_string(outptr,", ");
				}
			}
			outptr = copy_string(outptr,")");
			/* interpret to get variable declaration */
			N_interpret(outstring,value(func->fun.pred.dest));
		}
		break;
	    case MACRODEF:
		/* put macro at head of macro list */
		if (macro_list!=func) { 
		    /* Isn't the first macro in list. */
		    /* Remove from curr. place in macro list if already there*/
		    if (func->fun.macro.prev_macro!=NULL)
			func->fun.macro.prev_macro->fun.macro.next_macro=
			    func->fun.macro.next_macro;
		    if (func->fun.macro.next_macro!=NULL)
			func->fun.macro.next_macro->fun.macro.prev_macro=
			    func->fun.macro.prev_macro;
		    /* insert at head of list of defined macros */
		    func->fun.macro.next_macro = macro_list;
		    func->fun.macro.prev_macro = NULL;
		    if (macro_list!=NULL) macro_list->fun.macro.prev_macro=func;
		    macro_list = func;
		}
		break;
	    case ASSIGN:
		varstring = func->fun.assign.var->name;
		valstring = func->fun.assign.val->name;
		set_val(varstring, valstring);
		break;
	    case SOURCE:
		execute_for_trans(func->fun.source.body);
		break;
	    case COMMENT:   /* do nothing */
		break;
	    default:
		fatal("(internal) -- unknown function type\n");
		break;
	}
	if (func->next != NULL) {
		execute_for_trans(func->next);
	}
}

/* translate_func:
 * generate the C code for the given function, writing it into
 * the supplied file.
 */
static
int
translate_func(func,outfile)
	FUNC *func;
	FILE *outfile;
{
	ARGTYPE *arg, *val, *macvar;
	char *valstring, *varstring, *tmpstr;
	char outstring[MAXLINELEN], *outptr;
	FUNC *mac;
	int i;

	switch (func->ftype) {
	    case FOREACHLOOP:
		/* translate into a forloop & switch combination */

		/* 
		 * first, generate header 
		*/
		val = func->fun.fl.values;
		countervars++;
		fprintf(outfile, "for (ctr%d=0; ctr%d<%d; ctr%d++) {\n",
		    countervars, countervars, 
		    arglist_length(val)/arglist_length(func->fun.fl.loopvars),
		    countervars);
		fprintf(outfile, "    switch (ctr%d) {\n", countervars);
		/*
		 * go through the value list, generating switch cases
		 */
		for (i=0; val != NULL; i++) { 
			fprintf(outfile, "\tcase %d:\n",i);
			for (arg=func->fun.fl.loopvars; arg!=NULL; 
					arg=arg->next,val=val->next) {
				if (val==NULL) {
				    fatal("wrong number of loopvars\n");
				}
				if (val->cmt != NULL) fprintf(outfile, "\t    %s = %s;  /* %s */\n",
				    arg->name+1,value(val->name), val->cmt+1);
				else fprintf(outfile, "\t    %s = %s;\n",
				    arg->name+1,value(val->name));
			}
			fprintf(outfile, "\tbreak;\n");
		}
		fprintf(outfile, "    } \n");
		/*
		 * assign C variable names to looper variables,
		 * translate body, close for loop.
		 */
		for (arg=func->fun.fl.loopvars; arg!=NULL; arg=arg->next) {
		    set_val(arg->name, arg->name+1);
		}
		translate_func(func->fun.fl.body, outfile);
		fprintf(outfile, "} \n");
		break;

	    case FORLOOP: 
		{
		    char *loopvar, *start, *end, *increment;
		    char numstring[12];

		    /* get start value */
		    if (func->fun.forl.start==NULL) start = "1"; 
		    else {
			if((start=value(func->fun.forl.start->name))==NULL){
			    fprintf(stderr, "Looper error: forloop start, %s, has no value\n", 
				    func->fun.forl.start->name);
			    exit(1);
			}
		    }

		    /* get end value */
		    if((end=value(func->fun.forl.end->name))==NULL){
			fprintf(stderr, "Looper error: forloop end, %s, has no value\n", 
				func->fun.forl.start->name);
			exit(1);
		    }

		    /* get increment value */
		    if (func->fun.forl.incr==NULL) {increment = "1";} 
		    else {
			if((increment=value(func->fun.forl.incr->name))==NULL){
			    fprintf(stderr, "Looper error: forloop increment, %s, has no value\n", 
				    func->fun.forl.start->name);
			    exit(1);
			}
		    }

		    /* Generate a for-loop with these values */
		    loopvar = func->fun.forl.loopvar->name + 1;
		    fprintf(outfile, "for(%s=%s; %s<=%s; %s+=%s) {\n",
			loopvar,start,loopvar,end,loopvar,increment);
		    set_val(func->fun.forl.loopvar->name,loopvar);
                    translate_func(func->fun.forl.body,outfile);
		    fprintf(outfile, "}\n");
		}
		break;
	    case IFSTMNT:
		fprintf(outfile, "if (%s",
		    value(func->fun.ifstr.cond->name));
		if (func->fun.ifstr.oper != NULL) {
		    fprintf(outfile, " %s %s",
			func->fun.ifstr.oper->name,
			value(func->fun.ifstr.cond2->name));
		}
		fprintf(outfile, ") {\n");
		translate_func(func->fun.ifstr.thenbody, outfile);
		if (func->fun.ifstr.elsebody!=NULL) {
		    fprintf(outfile, "} else {\n"); 
		    translate_func(func->fun.ifstr.elsebody, outfile);
		}
		fprintf(outfile, "}\n");
		break;
	    case PRED:
		if (func->fun.pred.dest!=NULL) {
		    /* function assignment can't be a macro */
		    mac=NULL;
		} else { 
		    /* see whether predicate is a macro invocation */ 
		    for(mac=macro_list;
			mac!=NULL && 
			    strcmp(mac->fun.macro.name,func->fun.pred.name)!=0;
			mac=mac->fun.macro.next_macro);
		}
		if (mac!=NULL) {
			/* is a macro -- must first set vars */
			for (arg=func->fun.pred.args, 
					 macvar=mac->fun.macro.macvars;
			     (arg != NULL) && (macvar!=NULL); 
			     arg=arg->next, macvar=macvar->next) {
				set_val(macvar->name, arg->name);
			}
			if (arg==NULL && macvar!=NULL) {
				fprintf(stderr, "macro %s: not enough args\n",
					func->fun.pred.name);
				exit(1);
			}
			if (arg!=NULL && macvar==NULL) {
			      fprintf(stderr, "macro %s: extra args ignored\n",
					func->fun.pred.name);
			}
			translate_func(mac->fun.macro.body,outfile);

		} else { 
			/* is not a macro invocation -- assemble output line */
			outptr = outstring;
			if (prepend_underscore)
			    outptr = copy_string(outptr, "_");
			outptr = copy_string(outptr, func->fun.pred.name);
			outptr = copy_string(outptr, "(");
			for (arg=func->fun.pred.args; 
				arg != NULL; arg=arg->next) { 
				valstring = value(arg->name);
				if (valstring == NULL) {
				      fprintf(stderr, "Looper error: unknown variable, %s\n", arg->name);
				      exit(1);
				}
				if (index(valstring,'@')==NULL) { 
					outptr = copy_string(outptr, valstring);
				} else {
					/* must expand variables in arg */
					outptr = expand_arg(outptr, valstring);
				}
				if (arg->next != NULL) {
					outptr = copy_string(outptr,", ");
				}
			}
			outptr = copy_string(outptr,")");
			if (func->fun.pred.dest!=NULL)
			    fprintf(outfile, "    %s = %s;\n",
				value(func->fun.pred.dest), outstring);
			else fprintf(outfile, "    %s;\n",outstring);
		}
		break;
	    case MACRODEF:
		/* put macro at head of macro list */
		if (macro_list!=func) { 
		    /* Isn't the first macro in list. */
		    /* Remove from curr. place in macro list if already there*/
		    if (func->fun.macro.prev_macro!=NULL)
			func->fun.macro.prev_macro->fun.macro.next_macro=
			    func->fun.macro.next_macro;
		    if (func->fun.macro.next_macro!=NULL)
			func->fun.macro.next_macro->fun.macro.prev_macro=
			    func->fun.macro.prev_macro;
		    /* insert at head of list of defined macros */
		    func->fun.macro.next_macro = macro_list;
		    func->fun.macro.prev_macro = NULL;
		    if (macro_list!=NULL) macro_list->fun.macro.prev_macro=func;
		    macro_list = func;
		}
		break;
	    case ASSIGN:
		varstring = func->fun.assign.var->name;
		valstring = func->fun.assign.val->name;
		set_val(varstring, valstring);
		break;
	    case SOURCE:
		translate_func(func->fun.source.body, outfile);
		break;
	    case COMMENT:   /* do nothing */
		fprintf(outfile, "/* %s */\n", func->fun.cmt.text+1);
		break;
	    default:
		fatal("(internal) -- unknown function type\n");
		break;
	}
	if (func->next != NULL) {
		translate_func(func->next,outfile);
	}
}


/* create a function structure for a predicate with the given destination, name 
 * and argument list, return a pointer to it 
 */
static
FUNC *
pred(dest, name, args)
	char *dest, *name;
	ARGTYPE *args;
{
	FUNC *func;

	func = (FUNC *) malloc(sizeof(FUNC));
	func->ftype = PRED;
	if (debug) {
		func->lineno = lineno;
		N_setflag(N_fstr->breakablept,lineno);
	}
	func->next = NULL;
	func->fun.pred.dest = dest;
	func->fun.pred.name = name;
	func->fun.pred.args = args;
	return(func);
}

/* create a function structure for a comment 
 */
static 
FUNC *
comment(text)
	char *text;
{
	FUNC *func;

	func = (FUNC *) malloc(sizeof(FUNC));
	func->ftype = COMMENT;
	if (debug) {
		func->lineno = 0; /*zero means non stoppable for the debugger*/
	}
	func->next = NULL;
	func->fun.cmt.text = (char *)malloc(strlen(text)+1);
	strcpy(func->fun.cmt.text, text);
	return(func);
}

/* initialize an argument structure, with a copy of the given name and a 
 * null next field (substituting long name if arg is a macro variable)
*/
static
ARGTYPE *
arg(argname)
	char *argname;
{
	ARGTYPE *argstruct;
	MACROVARLIST *mv;

	argstruct = (ARGTYPE *) malloc(sizeof(ARGTYPE));
	argstruct->next = NULL;
	argstruct->cmt = NULL;

	if (macro_vars != NULL && is_var(argname)) {
		/* must see whether argname should be turned into long var */
		for(mv=macro_vars; mv!=NULL; mv=mv->next) {
			if (strcmp(argname+1,mv->shortname)==0) {
				argstruct->name = (mv->longname);
				return(argstruct);
			}
		}
	}
	/* if we got this far, is not a macro variable */
	argstruct->name = (char *) malloc(strlen(argname)+1);
	strcpy(argstruct->name, argname);
	return(argstruct);
}


/* append an argument list after arg1 */
static int
append_arg(arg1, arglist)
	ARGTYPE *arg1, *arglist;
{
	arg1->next = arglist;
}

static
int
arglist_length(list)
    ARGTYPE *list;
{
    ARGTYPE *p;
    int i;

    for(p=list,i=0; p!=NULL; p=p->next,i++);
    return(i);
}

/* append a function list after fun1 */
static int
append_fun(fun1, funlist)
	FUNC *fun1, *funlist;
{
	fun1->next = funlist;
}


/* allocate and initialize a foreach-loop function structure with the given
 * arguments 
*/
static
FUNC *
foreach(vars, vals, funlist)
	ARGTYPE *vars, *vals;
	FUNC *funlist;
{
	FUNC *forstruct;

	forstruct = (FUNC *) malloc(sizeof(FUNC));
	forstruct->ftype = FOREACHLOOP;
	if (debug) {
		forstruct->lineno = pop(FOREACHSTACK);
		N_setflag(N_fstr->breakablept,forstruct->lineno);
	}
	forstruct->next = NULL;
	forstruct->fun.fl.loopvars = vars;
	forstruct->fun.fl.values = vals;
	forstruct->fun.fl.body = funlist;
	return(forstruct);
}

/* allocate and initialize a for-loop function structure with the given
 * arguments 
*/
static
FUNC *
forloop(var, start, end, incr, funlist)
	ARGTYPE *var, *start, *end, *incr;
	FUNC *funlist;
{
	FUNC *forstruct;

	forstruct = (FUNC *) malloc(sizeof(FUNC));
	forstruct->ftype = FORLOOP;
	if (debug) {
		forstruct->lineno = pop(FORSTACK);
		N_setflag(N_fstr->breakablept,forstruct->lineno);
	}
	forstruct->next = NULL;
	forstruct->fun.forl.loopvar = var;
	forstruct->fun.forl.start = start;
	forstruct->fun.forl.end = end;
	forstruct->fun.forl.incr = incr;
	forstruct->fun.forl.body = funlist;
	return(forstruct);
}

/* allocate and initialize an if-statement structure */
static
FUNC *
ifstatement(cond,oper,cond2,thenbody,elsebody)
	ARGTYPE *cond, *oper, *cond2;
	FUNC *thenbody, *elsebody;
{
	FUNC *ifstruct;

	ifstruct = (FUNC *) malloc(sizeof(FUNC));
	ifstruct->ftype = IFSTMNT;
	if (debug) {
		ifstruct->lineno = pop(IFSTACK);
		N_setflag(N_fstr->breakablept,ifstruct->lineno);
	}
	ifstruct->next = NULL;
	ifstruct->fun.ifstr.cond = cond;
	ifstruct->fun.ifstr.oper = oper;
	ifstruct->fun.ifstr.cond2 = cond2;
	ifstruct->fun.ifstr.thenbody = thenbody;
	ifstruct->fun.ifstr.elsebody = elsebody;
	return(ifstruct);
}

/* build an assigment structure, consisting of variable and value arg */
static
FUNC *
assign(var, val)
    ARGTYPE *var, *val;
{
	FUNC *func;

	func = (FUNC *) malloc(sizeof(FUNC));
	func->ftype = ASSIGN;
        if (debug) {
		func->lineno = lineno;
		N_setflag(N_fstr->breakablept,lineno);
	}
	func->next = NULL;
	func->fun.assign.var = var;
	func->fun.assign.val = val;
	return(func);
}

static
FUNC *
source(file, body)
    ARGTYPE *file;
    FUNC *body;
{
	FUNC *func;

	func = (FUNC *) malloc(sizeof(FUNC));
	func->ftype = SOURCE;
        if (debug) {
		func->lineno = lineno;
		N_setflag(N_fstr->breakablept,lineno);
	}
	func->next = NULL;
	func->fun.source.fname = file->name;
	func->fun.source.body = body;
	return(func);
}


/* initiate definition of a macro.
*/
static
start_macro(name)
	char *name;
{

	/* set global variable indicating name of current macro */
	/* (this name will be prepended to variable names) */
	macro_name = name;
	macro_vars = NULL;

}


/*
 * new_macvar(): create from a macro variable an expanded variable
 * name, of the form @MACRO_foo_x, where "foo" is the current macro's
 * name and x is the original variable name (minus the "@").  This
 * expanded name, and a pointer to where the original name is within the
 * expanded string, are stored in a list so that occurrences of the
 * short name within the macro body are replaced with the long 
 * variable name.
*/
static
ARGTYPE *
new_macvar(varname)
	char *varname;
{
	ARGTYPE *argptr;
	char *longname;
	MACROVARLIST *newvar;
			
	longname = (char *) malloc(strlen(macro_name)+strlen(varname)+8);
	strcpy(longname,"@MACRO_");
	strcat(longname,macro_name);
	strcat(longname,"_");
	strcat(longname,varname+1);	/* leave off leading "@" */

	/* add to macro variable list */
	newvar = (MACROVARLIST *) malloc(sizeof(MACROVARLIST));
	newvar->longname = longname;
	/* shortname is at end of variable's longname! */
	newvar->shortname = longname + strlen(macro_name) + 8;
	/* put new variable at head of macro variable list */
	newvar->next = macro_vars;
	macro_vars = newvar;

	/* create and fill argument structure */
	argptr = (ARGTYPE *) malloc(sizeof(ARGTYPE));
	argptr->name = longname;
	argptr->next = NULL;
	return(argptr);
}

/* Create macro FUNC struct for macro just defined */
static
FUNC *
end_macro(name, varlist, body, fname)
	char *name;
	ARGTYPE *varlist;
	FUNC *body;
	char *fname;
{
	FUNC *func;

	func = (FUNC *) malloc(sizeof(FUNC));
	func->ftype = MACRODEF;
	if (debug) func->lineno = 0;
	func->next = NULL;
	func->fun.macro.name = name;
	func->fun.macro.fname = fname;
	func->fun.macro.macvars = varlist;
	func->fun.macro.body = body;
	func->fun.macro.next_macro = NULL;
	func->fun.macro.prev_macro = NULL;
    
	macro_name = NULL;	/* no longer defining a macro */
	macro_vars = NULL;	/* (could reclaim this storage?) */

	return(func);
}


/*
 * copy into deststr the expanded form of an argument containing variables,
 * and return a pointer to the end of the resulting string (the null
 * terminator).
 * A variable may be placed first in extended argument if the 
 * "@" is escaped with a preceding "\".
 */
static
char *
expand_arg(deststr, orig)
	char *deststr, *orig;
{
	char tempstr[MAXLINELEN], 
	    *curr,	    /* current position in original string */
	    *val;	    /* return value from variable lookup */
	int n;

	/* handle escaped "@" in extended argument */
	if (orig[0]=='\\' && orig[1]=='@') {
		curr = orig+1;
	} else {
		curr = orig;
	}

	while (*curr != '\0') {
		if (*curr == '@') {
			/* extract variable name, look up value, output */
			n =strspn(curr+1,
			    "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_");
			strncpy(tempstr,curr,n+1);
			tempstr[n+1]='\0';
			if((val=value(tempstr))==NULL) {
				fprintf(stderr, "looper error: unknown variable %s in argument %s\n", 
					tempstr, orig);
				exit(1);
			} else {
				if (index(val,'@')==NULL) { 
					deststr = copy_string(deststr,val);
				} else { 
					/* variable has embedded variables*/
					deststr = expand_arg(deststr, val);
				}
			}
			curr += n+1;
		} else {
			/* output contents up to '@' or end */
			n=strcspn(curr,"@");
			strncpy(deststr,curr,n);
			deststr[n]='\0';
			deststr += n;
			curr += n;
		}
	}

	return (deststr);
}

/* 
 * return a value of the supplied argument appropriate for
 * true/false evaluation
 */
static
int
eval_condition(arg)
    struct ARG_STRUCT *arg;
{
    int n, i;
    float f;
    char *val;
    long l;
    VLIST *vstr;

    /* instantiate any variables in arg */
    if ((val = value(arg->name))==NULL) 
	fatal("if-condition has unknown value\n");
    
    /* figure out what it is */
    if (n=sscanf(val, "%i", &i)==1) {
	/* successfully read an integer */
	return(i);
    } else if (n=sscanf(arg->name, "%f", &f)==1) {
	/* successfully read a float */
	return(f);
    } else if (printonly) {
	printf("looper: if-cond unknown due to printonly option; assuming true, continuing\n");
	return(1);
    } else if (N_get_interpreter_const(val, &l)) {
	return(l);
    } else if (N_get_interpreter_var(val, &vstr)) {
	switch(vstr->size) {
	    case 1:
		return(*((char*)(vstr->addr)));
		break;
	    case 2:
		return(*((short*)(vstr->addr)));
		break;
	    case 4:
		return(*((long*)(vstr->addr)));
		break;
	    default:
		fatal("if-statement condition variable is bad type\n");
	}
    } else fatal("if-statement condition is unknown\n");
}

/*
 * return true iff the string specified is a supported binary operator
 * for if statements.
 */
static
int
is_binary_oper(string)
    char *string;
{
    return (strcmp(string,"==")==0 ||
	    strcmp(string,"!=")==0 ||
	    strcmp(string,"<")==0  ||
	    strcmp(string,">")==0  ||
	    strcmp(string,"||")==0 ||
	    strcmp(string,"&&")==0 ||
	    strcmp(string,"|")==0  ||
	    strcmp(string,"&")==0);
}

/*
 * evaluate the binary operator applied to the two supplied arguments
 * and return the boolean result
 */
static
int
eval_binary_oper(oper, arg1, arg2)
    char *oper;
    struct ARG_STRUCT *arg1, *arg2;
{
    int val1, val2;

    val1 = eval_condition(arg1);
    val2 = eval_condition(arg2);
    
    if (strcmp(oper,"==") == 0) return (val1 == val2);
    else if (strcmp(oper,"!=") == 0) return (val1 != val2);
    else if (strcmp(oper,"<") == 0) return (val1 < val2);
    else if (strcmp(oper,">") == 0) return (val1 > val2);
    else if (strcmp(oper,"||") == 0) return (val1 || val2);
    else if (strcmp(oper,"&&") == 0) return (val1 && val2);
    else if (strcmp(oper,"|") == 0) return (val1 | val2);
    else if (strcmp(oper,"&") == 0) return (val1 & val2);
    else fatal("invalid binary operator in if-statement\n");
}

/* N_fopen_from_path(name, type, path) - search through the
 * directories in colon-separated path "path" for a file of
 * name "name", open it with fopen, and return the stream
 * pointer.  If path is null, look for it in current directory.
 */
FILE *
N_fopen_from_path(name, type, path)
    char *name, *type, *path;
{
    char *path_copy;	/* copy of path (strtok munges it) */
    char *dir;
    char full_filename[256];
    FILE *stream;
    
    if (path==NULL) {
	/* look for it in current dir */
	return fopen(name, type);
    } else {
	/* go through dirs in path */
	path_copy = strcpy (malloc (strlen (path) + 1), path);
	for (dir=strtok(path_copy, ":"), stream = NULL; 
	     dir != NULL && stream==NULL;
	     dir=strtok(NULL, ":")) {
	    sprintf(full_filename, "%s/%s", dir, name);
	    stream=fopen(full_filename, type);
	}
	/* either we ran out of dirs, or found the file */
	free(path_copy);
	return stream;
    }
}
/*	
 * Copy the source string into the destination string, returning
 * a pointer to the end (null terminator) of destination string.
 */
static
char *
copy_string(dest,src)
    char *dest, *src;
{
    while (*dest = *src++) dest++;
    return dest;
}


/* for a fatal error: print message, exit */
static
fatal(msg)
   char *msg;
{
	fprintf(stderr, "looper error: %s", msg);
	exit(1);
}

main(argc, argv)
    int	argc;
    char *argv[];
{
	int c;
        int status;

	/* 
	 * MACROPATH can contain a list of directories in which
	 * to search for directories.
	 */
	N_filepath = (char*) getenv("MACROPATH");

	/* process command line options */
        while ((c = getopt(argc,argv,"iptDdCuh:")) != EOF) {
                switch(c) {
                case 'i':
                        interactive = 1;
                        break;
		case 'p':
			printonly = 1;
			break;
		case 't':
			trace = 1;
			break;
                case 'd':
                        debug = 1;
			N_2process = 1;
                        filename=optarg;
                        break;
                case 'D':
                        debug = 1;
			N_2process = 0;
                        filename=optarg;
                        break;
		case 'C':
			N_translate = 1;
			break;
		case 'u':
			prepend_underscore = 1;
			break;
		case 'h':
			headertext_file = optarg;
			break;
                case '?':
			printf("Legal interpreter options:\n");
			printf("-i       interactive mode\n");
			printf("-p       printonly mode\n");
			printf("-t       trace mode - prints commands before executing\n");
			printf("-d       two process debug mode (file required)\n");
			printf("-D       single process debug mode (file required)\n");
			printf("<fname>  file to read from\n");
			printf("-C       translation to C mode\n");
			printf("    -u   prepend underscore when translating\n");
			printf("    -h <fname> insert file at head of translated program\n");
                        exit(1);
                }
        }

	if (N_translate && (trace||debug||interactive))
	    fatal("C translation option not allowed with trace, debug, or interactive options\n");
        if (debug) {
            if (interactive) 
	      fatal("invalid combination of options, debug and interactive\n");
	    if (optind == argc) 
		fatal("filename required for debug option.\n");
	    filename = argv[optind];
            yyin = fopen(filename, "r");
            if (yyin == NULL) {
                fprintf(stderr, "looper error - could not open file %s\n",
                            filename);
            exit(1);
            }
	    functail = N_funchead = (FUNC*) malloc(sizeof(FUNC));
            N_debuguse(filename);
	    status = yyparse();
            N_debuguse(filename);
	    curr_debug_file = filename;
	    if (!syntaxerr) N_debugger(1);
	    return(status);
        } else if (interactive) {
	    if (optind<argc) fatal("Can't take input from file in interactive mode\n");
	    fprintf(stderr,">> ");
	    return( yyparse() );
	} else if (optind == argc) {
	    /* take input from stdin */
            functail = N_funchead = (FUNC*) malloc(sizeof(FUNC));
	    status = yyparse();
	    if (!syntaxerr) {
		if (N_translate) generate_C_file(N_funchead->next, NULL);
		else N_execute(N_funchead->next,EXECUTE_NORMAL);
	    }
	    return(status);
	} else {
	    /* separately execute each named file */
	    for (; optind < argc && !syntaxerr; optind++) {
		yyin = fopen(argv[optind], "r");
		if (yyin == NULL) {
		    fprintf(stderr, "looper error - could not open file %s\n",
				argv[optind]);
		    exit(1);
		}
		filename=argv[optind];
		functail = N_funchead = (FUNC*) malloc(sizeof(FUNC));
		status = yyparse();
		if (!syntaxerr) {
		    if (N_translate) generate_C_file(N_funchead->next,filename);
		    else N_execute(N_funchead->next,EXECUTE_NORMAL);
		}
	    }
	    return(status);
        }

}



/* required by yacc */
yyerror(s) char *s; {
	fprintf(stderr, " %s\n",s);
}


/* 
 * maintain the stack of starting lines for the "if", "for" and "foreach"
 */
#define MAXSTACK 64
static int ifstack[MAXSTACK];
static int forstack[MAXSTACK];
static int foreachstack[MAXSTACK];
static int ifstackp=0;
static int forstackp=0;
static int foreachstackp=0;

static
push(type,val)
	int type,val;
{
	switch (type) {
	case IFSTACK:
		ifstack[ifstackp] = val;
		if (ifstackp++ >= MAXSTACK)
			puts("looper error: push() stack overflow");
		break;
	case FORSTACK:
		forstack[forstackp] = val;
		if (forstackp++ >= MAXSTACK)
			puts("looper error: push() stack overflow");
		break;
	case FOREACHSTACK:
		foreachstack[foreachstackp] = val;
		if (foreachstackp++ >= MAXSTACK)
			puts("looper error: push() stack overflow");
		break;
	default:
		puts("looper error: push() invalid type");
	}
}

static
pop(type)
	int type;
{
        switch (type) { 
        case IFSTACK: 
                if (--ifstackp < 0) 
                        puts("looper error: pop() stack underflow");
                return (ifstack[ifstackp]); 
                break; 
        case FORSTACK:
                if (--forstackp < 0) 
                        puts("looper error: pop() stack underflow");
                return (forstack[forstackp]); 
                break; 
        case FOREACHSTACK:
                if (--foreachstackp < 0) 
                        puts("looper error: pop() stack underflow");
                return (foreachstack[foreachstackp]); 
                break;
        default:
                puts("looper error: pop() invalid type");
        }
}
