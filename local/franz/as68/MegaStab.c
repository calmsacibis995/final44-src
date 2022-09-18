		/*	MegaStab.c	1.2	82/09/15	*/
#include "inst.h"
#include "scan.h" 
#include "mical.h"

extern struct sym_bkt *sym_hash_tab[];
extern long Dot;                       /* current offset in csect (i.e. addr)*/

#define STABFLOATING     0
#define STABFIXED        1


struct stab_sym_bkt *stab_free = NULL;
#define STAB_INCR 50

#define SProg_Error Prog_Error
#define DEBUG( X ) printf(X);

struct stab_sym_bkt *
gstab()
{
    /* get a stab symbol bucket -- analogous with gsbkt()/sym.c */
    register struct stab_sym_bkt *sbp;
    register int i;

    if ((sbp = stab_free) != NULL) {
	stab_free = sbp->next_stab;
    } else {
	sbp = (struct stab_sym_bkt *) calloc( STAB_INCR, sizeof(struct stab_sym_bkt));
	if (sbp == NULL) Sys_Error("Stab storage exceeded\n", 0);
	for (i=STAB_INCR-1;i--;) {
	    sbp->next_stab = stab_free;
	    stab_free = sbp++;
	}
    }
    return sbp;
}

Stab( opcode )
    int opcode;
{
    /* 
      allocate a new stab bucket, and process the stabs/d/n
      arguments which have already been parsed for us.
    */
    struct stab_sym_bkt *s;
    register int opno;

    if (Pass != 2) return;
    s = gstab();
    if (opcode==i_stabs){
	/* have a string operand -- parse it a la Ascii(), and save it off */
	register char *cp;
	register nchars;
	char *sp;
	if (numops != 5 ){
	    SProg_Error( E_NUMOPS); return;
	}
	if (operands[0].type_o != t_string ) {
	    DEBUG("first stabs operand not a string\n");
	    SProg_Error( E_OPERAND); return;
	}
	nchars = 0;
	cp = (char *)operands[0].value_o;
	while (*cp++)++nchars;
	cp = (char *)operands[0].value_o;
	s->ch = sp = (char *) calloc( nchars +1, sizeof(char));
	if (sp==NULL) Sys_Error( "Out of string space\n", 0);
	/* nchars is only an approximate character count -- recount for real */
	nchars = 0;
	while (*cp){
	    nchars++;
	    if ((*sp = *cp++)!= '\\'){
		sp++;
	    } 
#ifdef notdef
	    else switch (*cp) {
		int i;
		int c;
		/* bet none of this is ever executed */
		case '\\':
		case '"':
		    *sp++ = *cp++;
		    break;
		default:
		    /* \ octal */
		    for(i=0,c=0; i<3; i++) {
			if((*cp >= '0') && (*cp <= '7'))
			    c = (c<<3) + *cp-- - '0';
			else 
			    break;
		    }
		    *sp++ = c;
	    }
#else
	   else
	       Sys_Error("Stabs choke\n",0);
#endif
	}
	s->id = nchars;
	opno = 1;
    } else if ( opcode == i_stabd ) {
	if (numops != 3 ) { 
	    DEBUG("stabd has the wrong number of operands\n");
	    SProg_Error(E_NUMOPS);
	    return;
	}
	opno = 0;
	s->id = 0;
    } else { /* opcode == i_stabn */
	if (numops != 4 ) {
	    DEBUG("stabn has the wrong number of operands\n");
	    SProg_Error(E_NUMOPS);
	    return;
	}
	opno = 0;
	s->id = 0;
    }
    /* stuff the next three numbers without too much thought */
    if (operands[opno].sym_o != NULL || operands[opno].type_o != t_normal){
	DEBUG("stab first numeric operand bad\n");
	SProg_Error( E_OPERAND); return;
    }
    s->type = operands[opno++].value_o;
    if (operands[opno].sym_o != NULL || operands[opno].type_o != t_normal){
	DEBUG("stab second numeric operand bad\n");
	SProg_Error( E_OPERAND); return;
    }
    s->other = operands[opno++].value_o;
    if (operands[opno].sym_o != NULL || operands[opno].type_o != t_normal){
	DEBUG("stab third numeric operand bad\n");
	SProg_Error( E_OPERAND); return;
    }
    s->desc = operands[opno++].value_o;

    if (opcode == i_stabd) {
	/* value is Dot */
	s->tag = STABFIXED;
	s->value = Dot; /* this looks like a bug if you consider sdi's */
    } else {
	/* value is either a label or its a number */
	if (operands[opno].type_o != t_normal){
	    DEBUG("stab last operand isn't `normal'\n");
	    SProg_Error(E_OPERAND); return;
	}
	switch (s->type) {
	case N_FUN:
	case N_STSYM:
	case N_LCSYM:
	case N_SLINE:
	case N_SO:
	case N_SOL:
	case N_ENTRY:
	case N_LBRAC:
	case N_RBRAC:
	case N_ECOML:
		/* it a label */
		if (!operands[opno].sym_o
		|| operands[opno].value_o != operands[opno].sym_o->value_s) {
		    DEBUG("stab last operand isn't just a label\n");
		    SProg_Error(E_OPERAND); return;
		}
		s->label = operands[opno].sym_o;
		s->tag = STABFLOATING;
		break;
	default:
		/* its a number */
		if ( operands[opno].sym_o) {
		    DEBUG("stab last operand isn't just a number\n");
		    SProg_Error(E_OPERAND); return;
		}
		s->value = operands[opno].value_o;
		s->tag = STABFIXED;;
		break;
	}
    }
    Link_Stab_Tab( s );
}
/* ************************************************************************* */

  /* Link the incoming stab bucket to the stab symbol table.       */
  /* The addition of the incoming stab is linked to the end of the */
  /* current linked list.                                          */


Link_Stab_Tab(s)
struct stab_sym_bkt *s;


{ if (stabkt_head == NULL)                 /* if no entry on linked list */
     { stabkt_head = s;                         /* let both head and tail     */
       stabkt_tail = s;                         /* pointing to this entry s   */
       stabkt_head->next_stab = NULL;      /* and make the next one null */
     }
     else { stabkt_tail->next_stab = s;          /* otherwise make this entry */
            stabkt_tail = stabkt_tail->next_stab; /* the next entry and move  */
            stabkt_tail->next_stab = NULL;  /* tail pointing to this one */
          }
} /* end Link_Stab_Tab */

/* ************************************************************************** */

/* This will go through the entire sdb symbol table before  the second pass   */
/* to look for all labels with unresolved address and try to resolve them.    */

Find_Label_Value()
{ struct stab_sym_bkt *t, *f;
  struct sym_bkt *sbp_lab;
  
  t = stabkt_head;

  while (t != NULL)            /* go through the entire sdb symbol table */
        { if (t->tag == STABFLOATING)            /* look for unresolved value */
	  {
	      sbp_lab = t->label; 
	      t->value = sbp_lab->value_s;
	  }
          t = t->next_stab;
         } /* end while */
} /* end Find_Label_Value */

/* ************************************************************************** */
