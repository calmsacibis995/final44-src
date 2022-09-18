#define	CNIL	((lispval) -4)
#define nil	((lispval) 0)
#define eofa	((lispval) 20)
#define NOTNIL(a)	((int)a)
#define ISNIL(a)	(!(int)a)
#define STRBLEN 512

#define	NULL_CHAR	0


/* type flags and the macros to get them ********************************/

#define	UNBO	-1
#define	STRNG	0
#define	ATOM	1
#define	INT	2
#define	DTPR	3
#define DOUB	4
#define	BCD	5
#define	PORT	6
#define	ARRAY	7
#define SDOT	9
#define VALUE	10

#define HUNK2	11		/* The hunks */
#define HUNK4	12
#define HUNK8	13
#define HUNK16	14
#define HUNK32	15
#define HUNK64	16
#define HUNK128	17

extern char typetable[];  /*  the table with types for each page  */

#define	TYPE(a1)	((typetable+1)[(int)(a1) >> 9])
#define	HUNKSIZE(a1)	((TYPE(a1)+5) & 15)
#define VALID(a)	(a >= CNIL && a < datalim)
#define PN(p)		((int) ((p)-_iob))

typedef union lispobj *lispval ;

struct dtpr {
	lispval	cdr, car;
};

struct sdot {
	int 	I;
	lispval	CDR;
};


struct	atom	{
	lispval		clb;		/* current level binding*/
	lispval 	plist;		/* pointer to prop list	*/
	lispval		fnbnd;		/* function binding	*/
	struct	atom	*hshlnk;	/* hash link to next	*/
	char		*pname;		/* print name	*/
	};

struct array {
	lispval accfun,		/*  access function--may be anything  */
		aux;		/*  slot for dimensions or auxilliary data  */
	char *data;		/*  pointer to first byte of array    */
	lispval length, delta;	/* length in items and length of one item */
};

struct bfun {
	lispval (*entry)();	/*  entry point to routine  */
	lispval	discipline,	/*  argument-passing discipline  */
		language,	/*  language coded in	*/
		params,		/*  parameter list if relevant  */
		loctab;		/*  local table  */
};

struct Hunk {
	lispval hunk[1];
};

union lispobj {
	struct atom a;
	FILE *p;
	struct dtpr d;
	long int i;
	long int *j;
	double r;
	lispval (*f)();
	struct array ar;
	struct sdot s;
	char c;
	lispval l;
	struct bfun bcd;
	struct Hunk h;
};

struct argent {
	lispval	val;
};
extern lispval datalim;
#define SIGNIF 119
extern lispval lispsys[SIGNIF];
#define tatom (lispsys[1])
#define lambda (lispsys[2])
#define nlambda (lispsys[3])
#define perda (lispsys[4])
#define lpara (lispsys[5])
#define rpara (lispsys[6])
#define lbkta (lispsys[7])
#define rbkta (lispsys[8])
#define Eofa (lispsys[9])
#define snqta (lispsys[10])
#define exclpa (lispsys[11])
#define quota (lispsys[12])
#define xatom (lispsys[13])
#define cara (lispsys[14])
#define cdra (lispsys[15])
#define gcafter (lispsys[16])
#define noptop (lispsys[17])
#define gcthresh (lispsys[18])
#define int_name (lispsys[19])
#define str_name (lispsys[20])
#define atom_name (lispsys[21])
#define doub_name (lispsys[22])
#define dtpr_name (lispsys[23])
#define int_items (lispsys[24])
#define int_pages (lispsys[25])
#define str_items (lispsys[26])
#define str_pages (lispsys[27])
#define dtpr_items (lispsys[28])
#define dtpr_pages (lispsys[29])
#define doub_items (lispsys[30])
#define doub_pages (lispsys[31])
#define atom_items (lispsys[32])
#define atom_pages (lispsys[33])
#define gccall1 (lispsys[34])
#define gccall2 (lispsys[35])
#define sysa (lispsys[36])
#define plima (lispsys[37])
#define macro (lispsys[38])
#define startup (lispsys[39])
#define rcomms (lispsys[40])
#define commta (lispsys[41])
#define plimit (lispsys[44])
#define array_items (lispsys[45])
#define array_pages (lispsys[46])
#define array_name  (lispsys[47])
#define sdot_items (lispsys[48])
#define sdot_pages (lispsys[49])
#define sdot_name (lispsys[50])
#define val_items (lispsys[51])
#define val_pages (lispsys[52])
#define val_name  (lispsys[53])
#define splice	(lispsys[54])
#define rdrsdot (lispsys[55])
#define funct_items (lispsys[56])
#define funct_pages (lispsys[57])
#define funct_name (lispsys[58])
#define nstack (lispsys[59])
#define rdrint (lispsys[63])
#define nilplist (lispsys[64])
#define badst (lispsys[65])
#define gccheck (lispsys[66])
#define gcport (lispsys[67])
#define gcdis (lispsys[68])
#define gcload (lispsys[69])
#define loading (lispsys[70])
#define noautot (lispsys[71])
#define lcode (lispsys[72])
#define ccode (lispsys[73])
#define odform (lispsys[74])
#define bcdst (lispsys[75])
#define listst (lispsys[76])
#define macrost (lispsys[77])
#define protst (lispsys[78])
#define argst (lispsys[79])
#define arrayst (lispsys[80])
#define proga (lispsys[81])
#define progma (lispsys[82])
#define bstack (lispsys[83])
#define lexpr_atom (lispsys[84])
#define lexpr (lispsys[85])
#define ibase (lispsys[86])
#define Vpiport (lispsys[87])
#define Vpoport (lispsys[88])
#define Veval (lispsys[89])
#define Vererr (lispsys[90])
#define Vertpl (lispsys[91])
#define Verall (lispsys[92])
#define Vermisc (lispsys[93])
#define Vlerall (lispsys[94])
#define stlist (lispsys[95])
#define Vreadtable (lispsys[96])
#define strtab (lispsys[97])
#define Verbrk (lispsys[98])
#define Vnogbar (lispsys[99])
#define rdrsdot2 (lispsys[100])
#define Veruwpt (lispsys[101])

#define hunkfree (lispsys[102])
#define port_name (lispsys[103])
#define reseta (lispsys[104])
#define rsetatom (lispsys[105])
#define bptr_atom (lispsys[106])
#define evalhatom (lispsys[107])
#define funhatom (lispsys[108])
#define Vptport (lispsys[109])
#define Vcntlw  (lispsys[110])
#define Verrset (lispsys[111])
#define Verundef (lispsys[112])
#define Vsubrou (lispsys[113])
#define Vprinlevel (lispsys[114])
#define Vprinlength (lispsys[115])
#define Vfloatformat (lispsys[116])
#define Vldprt  (lispsys[117])
#define Verdepth  (lispsys[118])

/* various status switches */

#ifndef CONTORT
extern lispval stattab[16] ;
#define Schainp (stattab[0])
#define Sautor (stattab[1])
#define Strans (stattab[2])
#define evalhsw (stattab[3])
#endif
