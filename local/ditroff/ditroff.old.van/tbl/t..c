/* t..c : external declarations */

# include "stdio.h"
# include "ctype.h"

# define MAXLIN 250
# define MAXHEAD 44
# define MAXCOL 30
 /* Do NOT make MAXCOL bigger with adjusting nregs[] in tr.c */
# define MAXCHS 2000
# define MAXRPT 100
# define CLLEN 10
# define SHORTLINE 4
extern int nlin, ncol, iline, nclin, nslin;

extern int (*style)[MAXHEAD];
extern char (*font)[MAXHEAD][2];
extern char (*csize)[MAXHEAD][4];
extern char (*vsize)[MAXHEAD][4];
extern char (*cll)[CLLEN];
extern int (*flags)[MAXHEAD];
# define ZEROW 001
# define HALFUP 002
# define CTOP 004
# define CDOWN 010
extern int stynum[];
extern int qcol;
extern int *doubled, *acase, *topat;
extern int F1, F2;
extern int (*lefline)[MAXHEAD];
extern int fullbot[];
extern char *instead[];
extern int expflg;
extern int ctrflg;
extern int evenflg;
extern int *evenup;
extern int boxflg;
extern int dboxflg;
extern int linsize;
extern int tab;
extern int pr1403;
extern int linsize, delim1, delim2;
extern int allflg;
extern int textflg;
extern int left1flg;
extern int rightl;
struct colstr {char *col, *rcol;};
extern struct colstr *table[];
extern char *cspace, *cstore;
extern char *exstore, *exlim, *exspace;
extern int *sep;
extern int *used, *lused, *rused;
extern int linestop[];
extern int leftover;
extern char *last, *ifile;
extern int texname;
extern int texct, texmax;
extern char texstr[];
extern int linstart;


extern FILE *tabin, *tabout;
# define CRIGHT 2
# define CLEFT 0
# define CMID 1

# define S1 "3b"
# define S2 "3c"
# define S3 "3a"
# define TMP "3i"
# define SF "3f"
# define SL "3e"
# define LSIZE "3d"
# define SIND "3h"
# define SVS "3g"

/* this refers to the relative position of lines */
# define LEFT 1
# define RIGHT 2
# define THRU 3
# define TOP 1
# define BOT 2
