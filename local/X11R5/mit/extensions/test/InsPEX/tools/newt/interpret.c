
/* $XConsortium: interpret.c,v 5.1 91/02/16 09:59:53 rws Exp $ */

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
 * interpreter.c:
 *
 * The interpreter module of NewT. This includes the scanner, parser
 * of the interpreter and other utilites.
 */

#include "ctype.h"
#include "stdio.h"
#include "malloc.h"
#include "looper.h"
#include "interpret.h"
#include "config.h"
#ifdef SYSV 
#define index strchr
#define rindex strrchr
#endif

#define MAXTOK 3		/* token stack size */
#define MAXLEN 512		/* maximum string length */
#define HASHSIZE 3097		/* hash table size */

typedef enum {
	E_PNAME, E_LEFTP, E_SYNTAX, E_UNDEF, E_XTRARG, E_MAXLEN,
	E_FEWARG, E_ASTERCONST, E_AMPCONST, E_AMPARG, E_VARARG, E_REFARG,
	E_ADJFLOAT, E_ADJINT, E_EOS, E_GETINT, E_MAXARG, E_ILLASM,
	E_MALLOC
	} ERROR;		/* error type */

typedef enum {	
	T_EOS, T_ID, T_LEFTP, T_RIGHTP, T_COMMA, T_STRING, T_INT,
	T_FLOAT, T_ERRCHR, T_ASTER, T_AMP, T_CHAR,
	T_VBAR
        } TOKEN;		/* token type */

typedef enum {
	S_START, S_LEFTP, S_INARG, S_NEXTARG, S_ASTER, S_AMP, S_INVBAR,
	S_ARGLST 
	} STATE;		/* state type */

static char *module_name = "Interpreter";	/* module name */
static int acount = 0;    	/* argument count */

static ADDR argv[MAXARG];	/* argument vector */
static int intk[MAXARG];	/* interger contant place holder */
static float floatk[MAXARG];	/* float contant place holder */
static double doublek[MAXARG];	/* double contant place holder */
static char chark[MAXARG];	/* character constant place holder */
static short shortk[MAXARG];	/* short constant place holder */
static ADDR ptr[MAXARG];	/* pointer place holder */
static long longk[MAXARG];	/* long contant place holder */

static char *predptr;		/* pointer to input predicate */

typedef struct {
	TOKEN token;
	char word[MAXLEN];
} TSTACK;			/* token stack type */

static TSTACK tokstack[MAXTOK];	/* token stack */
static int stackptr = 0;	/* token stack ptr */

typedef struct {
	int size;
	int size_ifnotptr;
	char *type;
} ARGV;				/* argument vector type */

struct flist {
	char *name;		/* predicate name */
	int  (*fcnptr)();	/* function ptr */
	int  argc;		/* arg count */
	ARGV *argv;		/* arg vector */
	int  vararg;		/* vararg flag */
	int  ret;		/* return flag */
	struct flist *next;
};

typedef struct flist FLIST;	/* fcn hash table content structure */
static FLIST *fhashtbl[HASHSIZE];/* pointer fcn hash table */
static FLIST *curpred;		/* current predicate name */
	
struct klist {
        char *name;		/* const name */
        long  value;		/* its integer value */
        struct klist *next;
};
 
typedef struct klist KLIST;     /* const hash table content structure */
static KLIST *khashtbl[HASHSIZE];/* pointer const hash table */

static VLIST *vhashtbl[HASHSIZE];/* pointer var hash table */ 

#define VALID_ID(x) 	isalnum(x) || x == '_'
#define FILLWORD(x)	*w++ = x; *w = '\0';
#define STRCAT(w,c)     *w++ = c;

static char* emalloc();

/* 
 * gettoken(word)
 * Returns the next token and assigns its string value to word.
 * If there is a token in the stack, returns that one instead.
 */
static TOKEN
gettoken(word)
	char *word;
{
	TOKEN poptok(), gettok();

	if (stackptr)
		return(poptok(word));
	else
		return(gettok(word));
}


/*
 * gettok(word)
 * returns the next token and assigns its string value to word.
 */

static TOKEN 
gettok(word)
	char *word;
{
	int c,tmpc;
	char *w=word;
	enum {
		S_NEUTRAL, S_INID, S_INNUM, S_INSTRING, S_INHEX, S_INCHAR,
		S_INFLOAT } 
		state = S_NEUTRAL;

	while ( (c= *predptr++) != '\0') {
		switch(state) {
		case S_NEUTRAL:
			switch(c) {
			case '(':
				FILLWORD(c)
				return(T_LEFTP);
			case ')':
				FILLWORD(c)
				return(T_RIGHTP);
			case ',':
				FILLWORD(c)
				return(T_COMMA);
			case '|':
				FILLWORD(c)
				return(T_VBAR);
			case '&':
				FILLWORD(c)
				return(T_AMP);
			case '*':
				FILLWORD(c)
				return(T_ASTER);
			case '"':
				state = S_INSTRING;
				continue;
			case '.':
				*w++ = c;
				state = S_INFLOAT;
				continue;
			case '\n':
			case ' ':
			case '\t':
				continue;
			case '\'':
				if (*predptr == '\'') {
					return(T_ERRCHR);
				}
				state = S_INCHAR;
				continue;
			default:
				if (isalpha(c) || c == '_') {
					*w++ = c;
					state = S_INID;
				} else if (c == '0' && *predptr == 'x' && 
					    (isdigit(tmpc = *(predptr+1)) || 
					     (tmpc >='a' && tmpc <='f') )) {
							*w++ = c;
							*w++ = *predptr++;
							*w++ = *predptr++;
							state = S_INHEX;
				} else if (isdigit(c) || c == '-' || c == '+') {
					*w++ = c;
					state = S_INNUM;
				} else {
					FILLWORD(c)
					return(T_ERRCHR);
				}
				continue;
			}
		case S_INID:
			if (VALID_ID(c)) {
				STRCAT(w,c)
			} else {
				predptr--;
				*w = '\0';
				return(T_ID);
			}
			continue;
		case S_INNUM:
			if (isdigit(c)) {
				STRCAT(w,c)
			} else if (c == '.') {
				STRCAT(w,c)
				state = S_INFLOAT;
			} else {
				predptr--;
				*w = '\0';
				return(T_INT);
			}
			continue;
		case S_INFLOAT:
			if (isdigit(c)) {
				STRCAT(w,c)
			} else {
				predptr--;
				*w = '\0';
				return(T_FLOAT);
			}
			continue;
		case S_INCHAR:
			if (c != '\'') {
				STRCAT(w,c)
			} else {
				*w = '\0';
				return(T_CHAR);
			}
			continue;
		case S_INSTRING:
			if (c == '\\') {
				if ((c = *predptr++) == 'n')
					STRCAT(w,'\n')
				else if (c == 't')
					STRCAT(w,'\t')
				else
					STRCAT(w,c)
			} else if (c != '"') {
				STRCAT(w,c)
			} else {
				*w = '\0';
				return(T_STRING);
			}
			continue;
		case S_INHEX:
			if (isdigit(c) || (c >='a' && c <= 'f')) {
				STRCAT(w,c)
			} else {
				predptr--;
				*w = '\0';
				return(T_INT);
			}
			continue;
		}
	}
	return(T_EOS);
}


#define ERRORPROC(etype,estr,eflag) \
	eflag = 1; \
	error(etype,estr); \

/*
 * N_interpret(predicate,ret)
 * The interpreter interface, parser and command executor
 */
N_interpret(predicate,ret)
	char *predicate,*ret;
{
	TOKEN token;
	static char word[MAXLEN]; 
	char *tmpstr, *tmpptr, *strsave(); 
	STATE state = S_START;
	VLIST *vp, *H_lookupvar(), *H_installvar();
	KLIST *kp, *H_lookupconst();
	FLIST *H_lookupfcn();
	int err=0;
	static int firsttime = 1;
	int i;
	ADDR tmpaddr;
	void N_makehashfcn();
	void N_makehashconst();

	if (firsttime) {
		firsttime = 0;
		N_makehashfcn();
		N_makehashconst();
	}
	if (strlen(predicate) >= MAXLEN) {
		error(E_MAXLEN,predicate);
		return;
	}
	predptr = predicate;
	while(!err && (token = gettoken(word)) != T_EOS) {
		if (token == T_ERRCHR) {
			ERRORPROC(E_SYNTAX,word,err)
			continue;
		}
		switch(state) {
		case S_START:
			if (token == T_ID) {
				if (curpred = H_lookupfcn(word)) {
					state = S_LEFTP;
					assignment_proc(word,ret,&err);
				} else {
					ERRORPROC(E_UNDEF,word,err)
				}
			} else {
				ERRORPROC(E_PNAME,word,err)
			}
			continue;
		case S_LEFTP:
			if (token == T_LEFTP)
				state = S_ARGLST;
			else {
				ERRORPROC(E_LEFTP,word,err)
			}
			continue;
		case S_INARG:
			if (token == T_RIGHTP) {
				execute ();
				cleanup();
				return;
			} else if (token == T_COMMA)
				state = S_NEXTARG;
			else {
				ERRORPROC(E_SYNTAX,word,err)
			}
			continue;
		case S_NEXTARG:
			evalarg(token,word,&state,&err);
			continue;
		case S_ARGLST:
			if (token == T_RIGHTP) {
				execute ();
				cleanup();
				return; 
			} else
				evalarg(token,word,&state,&err);
			continue;
		case S_ASTER:
                        if (token == T_ID) {
                                if (kp = H_lookupconst(word)) {
                                        ERRORPROC(E_ASTERCONST,word,err)
				}
                                else if (vp = H_lookupvar(word)) {
					argv[acount] = *((ADDR*)(vp->addr));
					acount++;
                                        state = S_INARG;
                                } else if (! (curpred->vararg && acount >= curpred->argc)) {
                                        tmpptr=curpred->argv[acount].type;
					tmpstr=emalloc(strlen(tmpptr)+3);
					sprintf(tmpstr,"%s *",tmpptr);
                                        vp = H_installvar(word,sizeof(ADDR),tmpstr);
/*
Eliminate type casting to LHS of operator:
					*((ADDR*)(vp->addr)) = 
					emalloc(curpred->argv[acount].size);
*/

					tmpaddr=
					  emalloc(curpred->argv[acount].size);
					memcpy((char*)vp->addr,(char*)&tmpaddr,
					  sizeof(ADDR));
                                        argv[acount] = *((ADDR*)(vp->addr));
					acount++;
                                        state = S_INARG;
				} else {
                                	ERRORPROC(E_VARARG,word,err)
				}
                        } else {
                                ERRORPROC(E_SYNTAX,word,err)
			}
                        continue;
		case S_AMP:
			if (token == T_ID) {
				if (kp = H_lookupconst(word)) {
					ERRORPROC(E_AMPCONST,word,err)
				}
				else if (vp = H_lookupvar(word)) {
					ptr[acount] = vp->addr;
					argv[acount] = (ADDR) &ptr[acount];
					acount++;
					state = S_INARG;
                                } else if (! (curpred->vararg && acount >= curpred->argc)) {
				       if (curpred->argv[acount].size_ifnotptr){
				        tmpstr=strsave(curpred->argv[acount].type);
					*((char*)rindex(tmpstr,'*')) = '\0';
                			vp = H_installvar(word,
					curpred->argv[acount].size_ifnotptr,
					tmpstr);
					ptr[acount] = vp->addr;
					argv[acount] = (ADDR) &ptr[acount];
					acount++;
					state = S_INARG;
					} else {
						ERRORPROC(E_AMPARG,word,err)
					}
				} else {
					ERRORPROC(E_VARARG,word,err)
				}
			} else {
				ERRORPROC(E_SYNTAX,word,err)
			}
			continue;
		case S_INVBAR:
			evalinvbar(token,word,&state,&err);
			continue;
		}
	}
	if (token == T_EOS)
		error(E_EOS);
	cleanup();
			
}

/*
 * assignment_proc(name,ret,err)
 * process complicated function assignment, if any
 */
static assignment_proc(name,ret,err)
	char *name,*ret;
	int *err;
{
	VLIST *vp;

	static char dummy[MAXLEN];
	static ADDR dummyptr = dummy;
	static int maxsize=MAXLEN;
#ifdef SYSV 
#define PREALLOC(ptr,size) \
	( ((size) <=0) ? realloc((ptr),1) : realloc((ptr),(size)) )
#else
#define PREALLOC(ptr,size) \
	(realloc(ptr,size))
#endif

	if (ret) {  /* return argument supplied */
		if (curpred->ret) { /* this is a function */
			if (H_lookupconst(ret)) { /* this is a constant */
				ERRORPROC(E_ILLASM,ret,*err)
			} else if (vp=H_lookupvar(ret)) { /* var already defined */
				argv[acount] = vp->addr;
				acount++;
			} else { /* var not defined, create one */
				vp = H_installvar(ret,curpred->argv[0].size, curpred->argv[0].type);
				argv[acount] = vp->addr;
				acount++;
			}
		} else{	/* this is procedure */
			ERRORPROC(E_ILLASM,name,*err)
		}
	} else { /* no return argument supplied */
		if (curpred->ret) { /* this is a function */
			if (curpred->argv[0].size > maxsize) {
				if( !(dummyptr = PREALLOC(dummyptr,curpred->argv[0].size)));
					error(E_MALLOC);
				maxsize = curpred->argv[0].size;
			}
			argv[acount] = dummyptr; /* use dummy variable */
			acount++;
		}
	}
}

/*
 * evalarg(token,word,err)
 * Evaluates an argument token, this may results in different
 * state changes depending on whether the argument is an expression
 * or not.
 */
static
evalarg(token,word,statep,err)	
	TOKEN token;
	char *word;
	STATE *statep;
	int *err;
{
	static char lword[MAXARG];
	TOKEN lookahead;
	ADDR H_getidaddr(), adjust_int_type(), adjust_float_type();
	long intval;
	char **strp;

	if (acount >= curpred->argc && !curpred->vararg &&
	    (token == T_ASTER  || token == T_AMP ||
	     token == T_FLOAT  || token == T_INT ||
	     token == T_STRING || token == T_ID )) {
		ERRORPROC(E_XTRARG,curpred->name,*err)
	} else if (acount >= MAXARG) {
		ERRORPROC(E_MAXARG,curpred->name,*err)
	} else 
		switch(token) {
		case T_ASTER:
			*statep = S_ASTER;
			break;
		case T_AMP:
			*statep = S_AMP;
			break;
		case T_FLOAT: 
			sscanf(word,"%lf",&doublek[acount]);
			argv[acount] = adjust_float_type(&doublek[acount]);
			acount++;
			*statep = S_INARG;
			break;
		case T_STRING: 
			strp = (char**)emalloc(sizeof(char*));
			*strp = emalloc(strlen(word)+1);
			strcpy(*strp,word);
			argv[acount] = (ADDR) strp;
			acount++;
			*statep = S_INARG;
			break;
		case T_CHAR: 
			if (word[0] == '\\') {
				if (word[1] == 'n')
					chark[acount] = '\n';
				else if (word[1] == 't')
					chark[acount] = '\t';
			} else
				sscanf(word,"%c",&chark[acount]);
			argv[acount] = (ADDR) &chark[acount];
			acount++;
			*statep = S_INARG;
			break;
		case T_INT: 
			lookahead = gettok(lword);
			if (word[0] == '0') {
				if (word[1] == 'x')
					sscanf(word+2,"%lx",&longk[acount]);
				else
					sscanf(word,"%lo",&longk[acount]);
			} else
				sscanf(word,"%ld",&longk[acount]);
			if (lookahead == T_VBAR) {
				*statep = S_INVBAR;
			} else {
				pushtok(lookahead,lword);
				argv[acount] = adjust_int_type(&longk[acount]);
				acount++;
				*statep = S_INARG;
			}
			break;
		case T_ID: 
			lookahead = gettok(lword);
			if (lookahead == T_VBAR) {
				if (H_getidintval(word,&intval)) {
					longk[acount] = intval;
					*statep = S_INVBAR;
				} else {
					ERRORPROC(E_REFARG,word,*err)
				}
			} else {
				pushtok(lookahead,lword);
				if (argv[acount] = H_getidaddr(word))
					*statep = S_INARG;
				else {
					ERRORPROC(E_VARARG,word,*err)
				}
				acount++;
			}
			break;
		default:
			ERRORPROC(E_SYNTAX,word,*err)
			break;
		}
}

/* 
 * evalinvbar(token,word,statep)
 * Evaluates token in the state S_INVBAR, and changes state accordingly.
 */
static
evalinvbar(token,word,statep,err)
	TOKEN token;
	char *word;
	STATE *statep;
	int *err;
{
	TOKEN lookahead;
	static char lword[MAXLEN];
	ADDR H_getidaddr(), adjust_int_type();
	long intval;

	if (token == T_INT) {
 		lookahead = gettok(lword);
		if (word[0] == '0') {
			if (word[1] == 'x')
				sscanf(word+2,"%lx",&intval);
			else
				sscanf(word,"%lo",&intval);
		} else
			sscanf(word,"%ld",&intval);
		longk[acount] |= intval;
		if (lookahead == T_VBAR) {
			*statep = S_INVBAR;
		} else {
			pushtok(lookahead,lword);
			argv[acount] = adjust_int_type(&longk[acount]);
			acount++;
			*statep = S_INARG;
		}
	} else if (token == T_ID) {
		lookahead = gettok(lword);
		if (H_getidintval(word,&intval)) {
			longk[acount] |= intval;
			if (lookahead == T_VBAR) {
				*statep = S_INVBAR;
			} else {
				pushtok(lookahead,lword);
				argv[acount] = adjust_int_type(&longk[acount]);
				acount++;
				*statep = S_INARG;
			}
		} else {
			ERRORPROC(E_REFARG,word,*err)
		}
	} else {
		ERRORPROC(E_SYNTAX,word,*err)
	}
}

/*
 * cleanup()
 * Cleanup state
 */
static
cleanup()
{
	/* reset counters */
	acount = 0;
	/* reset look ahead token stack */
	stackptr = 0;
}

/*
 * execute (statep)
 * executes a predicate command, cleanup and re-set state to S_START.
 */
static
execute ()
{
	if ((!curpred->vararg && acount == curpred->argc) ||
	    ( curpred->vararg && acount >= curpred->argc) ) {    
		/* execute the function */
		if (!N_translate)
			(*curpred->fcnptr) (argv);
	} else {
		error(E_FEWARG, curpred->name);
	}
}
	
/*
 * strsave(s)
 * Copy and save a string.
 */
static char *
strsave(s)
        char *s;
{
        char *p;
        
        p = emalloc(strlen(s)+1);
        strcpy(p,s);
        return(p);
}
 
/*
 * emalloc(size)
 * Allocate memory.
 */
static char *
emalloc(size)
        int size;
{
        char *p, *calloc();
#ifdef SYSV 
#define PCALLOC(n,size) \
	( ((size) <=0) ? calloc((n),1) : calloc((n),(size)) )
#else
#define PCALLOC(n,size) \
	(calloc(n,size))
#endif
 
        if (! (p=PCALLOC(size,sizeof(char))))
                error(E_MALLOC);
        return(p);
}

/*
 * pushtok(token,word)
 * Push a token and its string value into the stack
 */
static
pushtok(token,word)
	TOKEN token;
	char *word;
{
	tokstack[stackptr].token = token;
	strcpy(tokstack[stackptr].word,word);
	stackptr++;
}

/*
 * poptok(word)
 * Retrieve a token and its string value from the stack
 */
static TOKEN
poptok(word)
	char *word;
{
	--stackptr;
	strcpy(word,tokstack[stackptr].word);
	return(tokstack[stackptr].token);
}

/*
 * H_hash(s)
 * Retrieve hash value
 */
static
H_hash(s)
	char *s;
{
	int hashval;

	for (hashval = 0; *s != '\0'; )
		hashval += *s++;
	return(hashval % HASHSIZE);
}

/*
 * N_installfcn(name,fcnptr,argc,argv,vararg,ret)
 * Install a new entry to the fcn hash tbl.
 */
void
N_installfcn(name,fcnptr,argc,argv,vararg,ret)
	char *name; 
	int (*fcnptr)(), argc, vararg, ret;
	ARGV *argv;
{
	FLIST *fp; 
	int hashval, i;
	
	fp = (FLIST *) emalloc(sizeof(FLIST));
	fp->argv = (ARGV*) emalloc( argc * sizeof (ARGV));
	fp->name = name;
	fp->fcnptr = fcnptr;
	fp->argc = argc;
	fp->vararg = vararg;
	for (i=0; i<argc; ++i) 
		fp->argv[i] = argv[i];
	hashval = H_hash(name);
	fp->ret = ret;
	fp->next = fhashtbl[hashval];
	fhashtbl[hashval] = fp;
}
		
/*
 * N_installconst(name,value)
 * Install a new entry to the const hash tbl.
 */
void
N_installconst(name,value)
	char *name; 
	long value;
{
	KLIST *kp, *H_lookupconst();
	int hashval;
	
	if (!H_lookupconst(name))   { /* not found */ 
		kp = (KLIST *) emalloc(sizeof(KLIST));
		kp->name = name;
		kp->value = value;
		hashval = H_hash(name);
		kp->next = khashtbl[hashval];
		khashtbl[hashval] = kp;
	} 
}
		
/*
 * H_installvar(name,size,type)
 * Install a new entry to the var hash tbl.
 */
static VLIST *
H_installvar(name,size,type)
	char *name, *type; 
	int size;
{
	VLIST *vp, *H_lookupvar();
	char *strsave();
	int hashval;
	ADDR addr;
	
	vp = (VLIST *) emalloc(sizeof(VLIST));
	addr = (ADDR) emalloc(size);
	vp->name = strsave(name);
	vp->addr = addr;
	vp->type = type;
	vp->size = size;
	hashval = H_hash(name);
	vp->next = vhashtbl[hashval];
	vhashtbl[hashval] = vp;
	return(vp);
}
		
/*
 * H_lookupfcn(name)
 * Retrieve an entry from the fcn hash tbl.
 */
static FLIST *
H_lookupfcn(name)
	char *name;
{
	FLIST *fp;

	for (fp = fhashtbl[ H_hash(name) ]; fp != NULL; fp = fp->next)
		if (! strcmp(name, fp->name) )
			return(fp); /* found it */
	return(NULL); /* not found */
}

/*
 * H_lookupconst(name)
 * Retrieve an entry from the const hash tbl.
 */
static KLIST *
H_lookupconst(name)
        char *name;
{
        KLIST *kp;
 
        for (kp = khashtbl[ H_hash(name) ]; kp != NULL; kp = kp->next)
                if (! strcmp(name, kp->name) )
                        return(kp); /* found it */
        return(NULL); /* not found */
}

/*
 * H_lookupvar(name)
 * Retrieve an entry from the var hash tbl.
 */
static VLIST *
H_lookupvar(name)
        char *name;
{
        VLIST *vp;
 
        for (vp = vhashtbl[ H_hash(name) ]; vp != NULL; vp = vp->next)
                if (! strcmp(name, vp->name) )
                        return(vp); /* found it */
        return(NULL); /* not found */
}

/*
 * N_get_interpreter_const(name)
 * Retrieve an entry from the const hash tbl
 * return 1 if is const, 0 otherwise
 */
int
N_get_interpreter_const(name,val)
        char *name;
	long *val;
{
        KLIST *k;
 
        if (k = H_lookupconst(name)) {
		*val = k->value;
                return(1);
	} else {
                return(0);
	}
}


/*
 * N_get_interpreter_var(name,vstr)
 * Retrieve an entry from the var hash tbl
 * return 1 if is variable, 0 otherwise
 * If a variable, assign to *vstr a pointer to the table entry
 */
int
N_get_interpreter_var(name,vstr)
	char *name;
	VLIST **vstr;
{
        if (*vstr = H_lookupvar(name)) {
                return(1);
	} else {
                return(0);
	}
}

/*
 * adjust_int_type(ip)
 * Return the adjusted object's address, the interger may be converted
 * to a short or a character object according to the size of the actual
 * argument. 
 */
static ADDR
adjust_int_type(ip)
	long *ip;
{
	int size;

	size = curpred->argv[acount].size;
	if (curpred->vararg && acount >= curpred->argc) 
		/* don't adjust if this belongs to vararg */
		return((ADDR) ip);
	else {
		if (size == sizeof(long)) {
			return ((ADDR) ip);
		} else if (size == sizeof(int)) {
			intk[acount] = *ip;
			return ((ADDR) &intk[acount]);
		} else if (size == sizeof(short)) {
			shortk[acount] = *ip;
			return ((ADDR) &shortk[acount]);
		} else if (size == sizeof(char)) {
			chark[acount] = *ip;
			return ((ADDR) &chark[acount]);
		} else {
			error(E_ADJINT,curpred->name);
		}
	}
}


/*
 * adjust_float_type(dp)
 * Return the adjusted object's address, the double may be converted
 * to a float object according to the size of the actual argument.
 */
static ADDR
adjust_float_type(dp)
        double *dp;
{
	int size;

        size = curpred->argv[acount].size;
	if (curpred->vararg && acount >= curpred->argc) 
		/* don't adjust if this belongs to vararg */
		return((ADDR) dp);
	else {
		if (size == sizeof(double)) {
                	return ((ADDR) dp);
		} else if (size == sizeof(float)) {
                	floatk[acount] = *dp;
                	return ((ADDR) &floatk[acount]);
        	} else {
			error(E_ADJFLOAT,curpred->name);
        	}
	}
}

/*
 * H_getidaddr(name)
 * Retrieve the addr of the id, may have to create this var if not
 * already existed.
 */
static ADDR
H_getidaddr(name)
	char *name;
{
	KLIST *kp;
	VLIST *vp; 

	if (kp = H_lookupconst(name))
		return(adjust_int_type(&kp->value));
	else if (vp = H_lookupvar(name))
		return(vp->addr);
	else if (curpred->vararg && acount >= curpred->argc)
		return(NULL);
	else {
		vp = H_installvar(name,curpred->argv[acount].size,curpred->argv[acount].type);
		return(vp->addr);
	}
}

/*
 * H_getidintval(name,val)
 * Retrieve the int value of the id 
 */
static
H_getidintval(name,val)
        char *name;
	int *val;
{
        KLIST *kp;
        VLIST *vp;

        if (kp = H_lookupconst(name))
                *val = kp->value;
        else if (vp = H_lookupvar(name)) {
		if (vp->size == sizeof(long)) {
			*val = *(long*)vp->addr;
		} else if (vp->size == sizeof(int)) {
			*val = *(int*)vp->addr;
		} else if (vp->size == sizeof(short)) {
			*val = *(short*)vp->addr;
		} else if (vp->size == sizeof(char)) {
			*val = *(char*)vp->addr;
		} else {
			error(E_GETINT,name);
		}
        } else {
                return(0);
	} 
	return(1);
}


/*
 * dumpvar()
 * System built-in dumpvar function
 */
dumpvar()
{
	int i;
	VLIST *vp;

	printf("       variable name  variable type\n\n");
	for (i=0; i<HASHSIZE; ++i)
	  for (vp = vhashtbl[i]; vp != NULL; vp = vp->next)
		printf("%20s  %s\n", vp->name, vp->type);
	return(1);
}

/*
 * N_generate_C_declaration(fp)
 * Print C declaration informations into the given file.
 */
N_generate_C_declaration(fp)
	FILE *fp;
{
        int i;
        VLIST *vp;

        for (i=0; i<HASHSIZE; ++i)
          for (vp = vhashtbl[i]; vp != NULL; vp = vp->next)
                fprintf(fp,"%s %s;\n", vp->type, vp->name);
}

/*
 * error(type, arg1)
 * Process errors according to the given error type.
 */
static
error(type,arg1)
	ERROR type;
	char *arg1;
{
	fprintf(stderr,"%s: ",module_name);
        switch(type) {
        case E_MAXLEN:
                fprintf(stderr,"input predicate too long \"%s\"\n",arg1);    
		break;
        case E_EOS:
                fprintf(stderr,"incomplete predicate\n");    
		break;
        case E_PNAME:
                fprintf(stderr,"expecting a predicate name at or near \"%s\"\n",arg1);    
		break;
        case E_LEFTP:
                fprintf(stderr,"expecting '(' at or near \"%s\"\n",arg1);    
		break;
        case E_SYNTAX:
                fprintf(stderr,"syntax error at or near \"%s\"\n",arg1);    
		break;
        case E_UNDEF:
                fprintf(stderr,"undefined predicate\"%s\"\n",arg1);    
		break;
        case E_XTRARG:
                fprintf(stderr,"too many arguments for this predicate \"%s\"\n",arg1);    
		break;
        case E_MAXARG:
                fprintf(stderr,"exceeding maximum number of arguments for this predicate \"%s\"\n",arg1);    
		break;
        case E_FEWARG:
                fprintf(stderr,"too few arguments for this predicate \"%s\"\n",arg1);    
		break;
        case E_ASTERCONST:
                fprintf(stderr,"invalid addressing mode for the constant \"%s\"\n",arg1);    
		break;
        case E_AMPCONST:
                fprintf(stderr,"invalid addressing mode for the constant \"%s\"\n",arg1);    
		break;
        case E_AMPARG:
                fprintf(stderr,"cannot create invalid data type for \"%s\"\n",arg1);    
		break;
        case E_REFARG:
                fprintf(stderr,"invalid reference to non-exist variable \"%s\"\n",arg1);    
		break;
        case E_VARARG:
                fprintf(stderr,"invalid attempt to create a VARARG variable \"%s\"\n",arg1);    
		break;
        case E_ADJFLOAT:
                fprintf(stderr,"float type adjustment failure for this predicate \"%s\"\n",arg1);
		break;
        case E_ADJINT:
                fprintf(stderr,"int type adjustment failure for this predicate \"%s\"\n",arg1);
		break;
        case E_GETINT:
                fprintf(stderr,"int type adjustment failure for this variable \"%s\"\n",arg1);
		break;
        case E_ILLASM:
                fprintf(stderr,"illegal assignment for \"%s\"\n",arg1);
		break;
	case E_MALLOC:
                fprintf(stderr,"FATAL: memory allocation failed\n");    
		exit(1);
        }
}
