		/*	scan.c	1.4	82/09/23	*/
#include "inst.h"
#include "scan.h" 
#include "mical.h"

/* process lines from source file, returns when EOF detected */

#define LSIZE	200	/* max size of input line */

short cinfo[128] = {
	ERR,	ERR,	ERR,	ERR,	ERR,	ERR,	ERR,	ERR,
	ERR,	SPC,	EOL,	SPC,	SPC,	SPC,	ERR,	ERR,
	ERR,	ERR,	ERR,	ERR,	ERR,	ERR,	ERR,	ERR,
	ERR,	ERR,	ERR,	ERR,	ERR,	ERR,	ERR,	ERR,
	SPC,	ERR,	QUO,	IMM,	S+T,	ERR,	ERR,	ERR,
	LP,	RP,	MUL,	ADD,	COM,	SUB,	S+T,	DIV,
	D+T,	D+T,	D+T,	D+T,	D+T,	D+T,	D+T,	D+T,
	D+T,	D+T,	COL,	EOL,	ERR,	EQL,	ERR,	ERR,
	IND,	S+T,	S+T,	S+T,	S+T,	S+T,	S+T,	S+T,
	S+T,	S+T,	S+T,	S+T,	S+T,	S+T,	S+T,	S+T,
	S+T,	S+T,	S+T,	S+T,	S+T,	S+T,	S+T,	S+T,
	S+T,	S+T,	S+T,	ERR,	ERR,	ERR,	ERR,	S+T,
	ERR,	S+T,	S+T,	S+T,	S+T,	S+T,	S+T,	S+T,
	S+T,	S+T,	S+T,	S+T,	S+T,	S+T,	S+T,	S+T,
	S+T,	S+T,	S+T,	S+T,	S+T,	S+T,	S+T,	S+T,
	S+T,	S+T,	S+T,	ERR,	EOL,	ERR,	NOT,	S+T
};  



char *sassign(),*sdefer(),*exp(),*term();
int slabel();

char iline[LSIZE];	/* current input line resides */
int Line_no;		/* current input line number */
char Code[CODE_MAX];	/* where generated code is stored */
long Dot;		/* offset in current csect */
int BC;			/* size of code for current line */
int opshow = 0;


main(argc,argv)
char *argv[];
{ char *i;

  stabkt_head = stabkt_tail = NULL;      /* initialize stabs/d  symbol table */

  Init(argc,argv);                       /* Initialization */
  scan();                                /* 1st pass through .s file */
  End();                                 /* end of 1st pass          */

  /* Resolve the unresolved addresses in .stabs and .stabd directives.       */
  /* .stabs type 0x24 (N_Fun for procedure name), 0x26 (N_STSYM for static   */
  /* symbol), and 0x64 (N_SO for source file name) have a labeled-address    */
  /* tagged in the directive in the last field "value".  These addresses     */
  /* have to be resolved during or before the 2nd Pass (in this version,     */
  /* resolved before the second pass).                                       */

  scan();                                /* 2nd pass through .s file */
  Find_Label_Value();                    /* Resolve unresolved addresses */

  End();                                 /* end of 2nd pass          */

  exit(Errors? -1: 0);

} /* end main */

scan()
  {	register int i;
	register char *p;	/* pointer into input line */
	char *token;		/* pointer to beginning of last token */
	int opindex;		/* index of opcode on current line */

	while (fgets(iline,LSIZE,stdin) == iline) {

	  Line_no++;
	  p = iline;
	  BC = 0;
	  Code_length = 0;

	  /* see what's the first thing on the line. if newline or comment
	   * char just ignore line all together.  if start of symbol see
	   * what follows.  otherwise error.
	   */
 restart: skipb(p);
	  i = cinfo[*p];	/* see what we know about next char */
	  /* hack to make # in col 1 a comment -- for cpp leavings */
	  if (i == EOL || i == IMM) {
	      /* further hack to make ; in line act as seperator. */
	      if (*p == ';'){ p++; goto restart;}
	      continue;
	  }
	  if (!(i & (S|D))) { Prog_Error(E_BADCHAR); continue; }

	  /* what follows is either label or opcode, gobble it up */
	  token = p;
	  skips(p);
	  skipb(p);
	  i = cinfo[*p];

	  /* if next char is ":", this is label definition */
	  if (i == COL) { p++; slabel(token); goto restart; }

	  /* if next char is "=", this is label assignment */
	  if (i == EQL) {
	    p = sassign(++p,token);
	    if (cinfo[*p] != EOL) Prog_Error(E_BADCHAR);
	    /* hack to make ; in line act as seperator. */
	    if (*p == ';'){ p++; goto restart;}
	    continue;
	  }

	  /* otherwise this must be opcode, find its index */
	  if ((opindex = sopcode(token)) == 0) {
	    Prog_Error(E_OPCODE);
	    continue;
	  }

	  if (i == EOL) { numops = 0; goto doins; }

	  /* keep reading operands until we run out of room or hit EOL */
	  for (numops = 1; numops <= OPERANDS_MAX; numops++)
	      { p = soperand(p,&operands[numops-1]);
	        if (opshow) printop(&operands[numops-1]);
	        skipb(p);
	        i = cinfo[*p];
	        if (i == COM) { p++; skipb(p); continue; }
	        if (i == EOL) goto doins;
	        Prog_Error(E_OPERAND);
	        goto next;
	      }
	  Prog_Error(E_NUMOPS);
  next:	  continue;

  doins:  Instruction(opindex);
 n_doins: Dot += BC;
	  Cur_csect->dot_cs = Dot_bkt->value_s = Dot;
	  if (Dot > Cur_csect->len_cs) Cur_csect->len_cs = Dot;
	  
	  /* hack to make ; in line act as seperator. */
	  if (*p == ';'){ p++; goto restart;}
	}
} /* end Scan */

/* lookup token in opcode hash table, return 0 if not found */
int sopcode(token)
register char *token;
{ register char *p;
  register struct ins_bkt *ibp;
  char mnem[50];

  /* make asciz version of mnemonic */
  p = mnem;
  while (cinfo[*token] & T) *p++ = *token++;
  *p = 0;

  /* look through appropriate hash bucket */
  ibp = ins_hash_tab[Hash(mnem)];
  while (ibp) 
        { if (strcmp(ibp->text_i,mnem) == 0) return(ibp->code_i);
	  ibp = ibp->next_i;
	}

  return(0);
} /* end sopcode */

/* handle definition of label */
slabel(token)
register char *token;
{ register char *p;
  struct sym_bkt *sbp;
  char nextc;

  /* make asciz version of label */
  p = token;
  while (cinfo[*p] & T) p++;
  nextc = *p; /* may be a , a + a \n ... */
  *p = '\0';

  /* find/enter symbol in the symbol table */
  sbp = Lookup(token);

  /* on pass 1 look for multiply defined symbols.  if ok, label
     value is dot in current csect
  */
  if (Pass==1) 
     { if (sbp->attr_s & (S_LABEL|S_REG)) 
          Prog_Error(E_MULTSYM);
       sbp->attr_s |= S_LABEL | S_DEC | S_DEF;
       sbp->csect_s = Cur_csect;
       sbp->value_s = Dot;
       /* printf("\n\n***** Label sbp->name_s %s ", sbp->name_s);
        * printf("\n              address = 0%o", Dot);
        */
     } 
  else if (sbp->csect_s!=Cur_csect || sbp->value_s!=Dot)
	  Prog_Error(E_MULTSYM);

  if (!(cinfo[token[0]] & D)) 
     Last_symbol = sbp;

/* fprintf(stderr,"slabel(%s) = %ld\n",token,Dot); */

  *p = nextc; /* replace next character before proceeding */
} /* end slabel */

/* handle assignment to a label, return updated line pointer */
char *
sassign(lptr,token)
  register char *token;
  register char *lptr;
{
  register char *p;
  register struct sym_bkt *sbp;
  struct oper value;
  char nextc;

  /* make asciz version of label */
  p = token;
  while (cinfo[*p] & T) p++;
  nextc = *p;
  *p = '\0';

  /* find/enter symbol in the symbol table, and get its new value */
  sbp = Lookup(token);
  lptr = exp(lptr,&value);

  /* if assignment is to dot, we'll treat it specially */
  if (sbp == Dot_bkt) {
	int deltadot;
	static char zed[512];
	if (value.sym_o && value.sym_o->csect_s!=Cur_csect)
	  Prog_Error(E_OPERAND);
	deltadot = value.value_o - Dot;
	while (deltadot > sizeof zed){
	  Put_Text(zed,sizeof zed); /* if not in bss segment, put zeros */
	  deltadot -= sizeof zed;
	}
	while (deltadot-- > 0)
	  Put_Text(zed,1); /* if not in bss segment, put zeros */
	Dot = value.value_o;
	Cur_csect->dot_cs = Dot_bkt->value_s = Dot;
	if (Dot > Cur_csect->len_cs) Cur_csect->len_cs = Dot;
  } else {
	sbp->value_s = value.value_o;
	sbp->csect_s = (value.sym_o!=NULL) ? value.sym_o->csect_s : NULL;
	if (sbp->attr_s & S_LABEL) 
            Prog_Error(E_EQUALS);
	else if (value.type_o == t_reg)
	    sbp->attr_s = (sbp->attr_s&S_EXT) | S_REG | S_DEC | S_DEF;
	else
	    sbp->attr_s = (sbp->attr_s&S_EXT)  |
		((value.sym_o!=NULL) ?
	         (value.sym_o->attr_s & ~(S_LABEL|S_PERM)): (S_DEC | S_DEF));
   }

 if (opshow) fprintf(stderr,"sassign(%s) = %ld, %ld\n",
	token, value.value_o, sbp->attr_s);

  *p = nextc;

  /* return update line pointer */
  skipb(lptr);
  return(lptr);
} /* end sassign */

/* Hashing routine for Symbol and Instruction hash tables */
Hash(s)
register char *s;
{ register int i = 0;

  while (*s) i = i*10 + *s++ - ' ';
  i = i % HASH_MAX;
  return(i<0 ? i+HASH_MAX : i);
} /* end Hash */

/* 
 * Fetches operand value and register subfields and loads them into
 * the operand structure. This routine will fetch only one set of value
 * and register subfields. It will move line pointer to first untouched char.
 */
char *
soperand(lptr,opnd)
  register char *lptr;
  struct oper *opnd;
{ char c;

  opnd->type_o = opnd->flags_o = opnd->reg_o = 0;
  opnd->value_o = opnd->disp_o = 0;
  opnd->sym_o = NULL;

  if (cinfo[*lptr] == IMM) 
     { lptr = exp(++lptr,opnd);
       if (opnd->type_o == t_reg) 
          Prog_Error(E_REG);
       opnd->type_o = t_immed;
     } 
  else { lptr = exp(lptr,opnd);
	 skipb(lptr);
	 while (1) switch (cinfo[*lptr]) {
	    default:	return(lptr);

	    case COL:	switch (*++lptr)
			{ case 'W':
			  case 'w': opnd->type_o = t_abss;
				    lptr++;
				    continue;
			  case 'L':
			  case 'l': opnd->type_o = t_absl;
				    lptr++;
				    continue;
			  default:  return(lptr);
			}

	    case IND:	if (opnd->type_o != t_reg) 
                           return(lptr);
			opnd->type_o = t_defer;
			lptr++;
			continue;

	    case ADD:	if (opnd->type_o != t_defer) 
                           return(lptr);
			opnd->type_o = t_postinc;
			lptr++;
			continue;

	    case SUB:	if (opnd->type_o != t_defer) 
                           return(lptr);
			opnd->type_o = t_predec;
			lptr++;
			continue;

	    case LP:	lptr = sdefer(lptr,opnd);
			continue;
	  }
	}
	return(lptr);
} /* end soperand */

/* Process Displacement or Index Deferred Suboperands */
char 
*sdefer(lptr,opnd)
  register struct oper *opnd;
  register char *lptr;
{ if (opnd->type_o != t_defer)
     { Prog_Error(E_OPERAND); 
       /* we didn't see a @ .. pretend we did */
       opnd->type_o = t_defer;
     }
  opnd->reg_o = opnd->value_o;
  lptr = exp(++lptr,opnd);

  skipb(lptr);
  switch (cinfo[*lptr]) {
	  case RP:	opnd->type_o = t_displ;
			lptr++;
			break;

	  case COM:	opnd->disp_o = opnd->value_o;
			lptr = exp(++lptr,opnd);
			if (opnd->type_o!=t_reg || cinfo[*lptr]!=COL) 
                           { Prog_Error(E_OPERAND); return(lptr);
			   }
			lptr++;
			switch (*lptr++)
			{ case 'W':
			  case 'w':	opnd->flags_o |= O_WINDEX;
					break;
			  case 'L':
			  case 'l':	opnd->flags_o |= O_LINDEX;
					break;
			  default:	Prog_Error(E_OPERAND);
					return(lptr);
			}
			skipb(lptr);
			if (cinfo[*lptr] != RP)
			   { Prog_Error(E_OPERAND); 
                             return(lptr);
			   }
			opnd->type_o = t_index;
			lptr++;
			break;

	default:	return(lptr);
	}						
	return(lptr);
} /* end sdefer */

/* read expression */
char *
exp(lptr,Arg1)
  register char *lptr;
  register struct oper *Arg1;
{ struct oper Arg2;	       	/* holds value of right hand term */
  register char Op;	        /* operator character */
  register int i;

  skipb(lptr);			/* Find the operator */
  i = cinfo[*lptr];
  if (i==EOL || i==COM)         /* nil operand is zero */
     { Arg1->sym_o = NULL;
       Arg1->value_o = 0;
       return(lptr);
     }
  lptr = term(lptr,Arg1);

  while (1) {
	  skipb(lptr);
	  switch (cinfo[*lptr]) {
	    case ADD:	lptr = term(++lptr,&Arg2);
			if (Arg1->type_o==t_reg || Arg2.type_o==t_reg) 
                           break;
			if (Arg1->sym_o && Arg2.sym_o) 
                           break;
			if (Arg2.sym_o) 
                           Arg1->sym_o = Arg2.sym_o;
			Arg1->value_o += Arg2.value_o;
			Arg1->flags_o |= Arg2.flags_o&O_COMPLEX;
			continue;

	    case MUL:	lptr = term(++lptr,&Arg2);
			if (Arg1->type_o==t_reg || Arg2.type_o==t_reg) 
                           break;
			if (Arg1->sym_o || Arg2.sym_o) 
                           break;
			Arg1->value_o *= Arg2.value_o;
			Arg1->flags_o |= Arg2.flags_o&O_COMPLEX;
			continue;

	    case DIV:	lptr = term(++lptr,&Arg2);
			if (Arg1->type_o==t_reg || Arg2.type_o==t_reg) 
                           break;
			if (Arg1->sym_o || Arg2.sym_o) 
                           break;
			Arg1->value_o /= Arg2.value_o;
			Arg1->flags_o |= Arg2.flags_o&O_COMPLEX;
			continue;

	    case SUB:	lptr = term(++lptr,&Arg2);
			if (Arg1->type_o==t_reg || Arg2.type_o==t_reg) 
                           break;
			if (Arg2.sym_o)		/* if B is relocatable, */
			   if (Arg1->sym_o)  	/* and A is relocatable, */
			      { if (Arg2.sym_o->csect_s != Arg1->sym_o->csect_s)
                                   break;       /* break into error */
			        else  /* result is absolute (no offset) */
                                      { Arg1->sym_o = NULL;	
                                        /* but not a simple address for sdi's */
			                Arg1->flags_o |= O_COMPLEX;	
			              }
			       } 
                           else break;    /* if B rel., and A is not, */
                                          /* then break into relocation error */
			Arg1->value_o -= Arg2.value_o;
			continue;

	    default:	return(lptr);
	  }
	Prog_Error(E_RELOCATE);
	return(lptr);
	}
} /* end exp <read expression> */

/* read term: either symbol, constant, or unary minus */
char *
term(lptr,Vp)
  register char *lptr;
  register struct oper *Vp;
{ register struct sym_bkt *sbp;
  register int base = 10;
  register long val;
  register char *p;
  register int i;
  char token[50];

  skipb(lptr);
  i = cinfo[*lptr];

  /* here for number */
  if (i & D)  
     { p = lptr;
       if (*lptr == '0') 
	  { lptr++;
	    if (*lptr=='x' || *lptr=='X') 
               { lptr++; 
                 base = 16; 
               }
	    else base = 8;
	  }
       val = 0;
       if (base == 16) while (1)
	  { if (cinfo[*lptr] & D) val = val*16 + *lptr++ - '0';
	    else if (*lptr>='A' && *lptr<='F')
	      val = val*16 + *lptr++ - 'A' + 10;
	    else if (*lptr>='a' && *lptr<='f')
	      val = val*16 + *lptr++ - 'a' + 10;
	    else break;
	  } else while (cinfo[*lptr] & D) val = val*base + *lptr++ - '0';

       if (*lptr == '$') { lptr = p; goto sym; }

       Vp->value_o = val;
       Vp->sym_o = NULL;
       Vp->type_o = t_normal;
       return(lptr);
      }

	/* here for symbol name */
	if (i & S) {
    sym:  p = token;
	  while (cinfo[*lptr] & T) *p++ = *lptr++;
	  *p = 0;	  
	  sbp = Lookup(token);		/* find its symbol bucket */

	  if (sbp->attr_s & S_DEF)	/* if it's defined, use its value */
	    Vp->value_o = sbp->value_s;
	  else Vp->value_o = 0;

	  if (sbp->attr_s & S_REG) Vp->type_o = t_reg;
	  else {
	    Vp->sym_o = (sbp->attr_s & S_DEF) &&
			 (sbp->csect_s == 0 || (sbp->csect_s->attr_cs & R_ABS))
				    ? 0 : sbp;
	    Vp->type_o = t_normal;
	  }
	  return(lptr);
	}

	/* check for unary minus */
	if (i == SUB) {
	  lptr = term(++lptr,Vp);
	  if (Vp->sym_o) Prog_Error(E_RELOCATE);
	  Vp->value_o = -(Vp->value_o);	/* and finally do it */
	  return(lptr);
	}

	/* check for complement */
	if (i == NOT) {
	  lptr = term(++lptr,Vp);
	  if (Vp->sym_o) Prog_Error(E_RELOCATE);
	  Vp->value_o = ~(Vp->value_o);	/* and finally do it */
	  return(lptr);
	}

	/* here for string */
	if (i == QUO) {
	  Vp->value_o = (long)(lptr+1);
	  /* scan over the quoted string, being careful of \-stuff */
	  do{
	      i = *++lptr;
	      if (i=='\\')
		switch (i = *++lptr){
		case '"': i = '\\'; /* fake-out loop test by covering up \"*/
	      }
	  }while (i!='\n' && i!='"');
	  *lptr++ = 0;
	  Vp->sym_o = NULL;
	  Vp->type_o = t_string;
	  return(lptr);
	}

	/* new, improved kluge -- parens !! */
	if (i==LP) {
	  lptr = exp(++lptr, Vp);
	  skipb(lptr);
	  if ((i=cinfo[*lptr]) == RP) {
		lptr++;
	  } else {
		Prog_Error( E_PAREN );
	  }
	  return( lptr );
	}

	Prog_Error(E_TERM);
	return(lptr);
} /* end term */

char *tnames[] = {
  "?", "reg", "defer", "postinc", "predec", "displ",
  "index", "abss", "absl", "immed", "normal", "string"
};

printop(o)
  register struct oper *o;
  {	fprintf(stderr,"operand %d: type=%s ",numops,tnames[o->type_o]);
	if (o->sym_o) {
	  if(o->sym_o->csect_s)
	  fprintf(stderr,"csect=%s ",
		  o->sym_o->csect_s->name_cs);
	  fprintf(stderr,"sym=%s ",
		  o->sym_o->name_s);
	}
	fprintf(stderr,"value=%ld reg=%d displ=%ld\n",
		o->value_o,o->reg_o,o->disp_o);
} /* end printop */
