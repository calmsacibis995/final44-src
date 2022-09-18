# include "stdio.h"
# define U(x) x
# define NLSTATE yyprevious=YYNEWLINE
# define BEGIN yybgin = yysvec + 1 +
# define INITIAL 0
# define YYLERR yysvec
# define YYSTATE (yyestate-yysvec-1)
# define YYOPTIM 1
# define YYLMAX 200
# define output(c) putc(c,yyout)
# define input() (((yytchar=yysptr>yysbuf?U(*--yysptr):getc(yyin))==10?(yylineno++,yytchar):yytchar)==EOF?0:yytchar)
# define unput(c) {yytchar= (c);if(yytchar=='\n')yylineno--;*yysptr++=yytchar;}
# define yymore() (yymorfg=1)
# define ECHO fprintf(yyout, "%s",yytext)
# define REJECT { nstr = yyreject(); goto yyfussy;}
int yyleng; extern char yytext[];
int yymorfg;
extern char *yysptr, yysbuf[];
int yytchar;
FILE *yyin ={stdin}, *yyout ={stdout};
extern int yylineno;
struct yysvf { 
	struct yywork *yystoff;
	struct yysvf *yyother;
	int *yystops;};
struct yysvf *yyestate;
extern struct yysvf yysvec[], *yybgin;
# define A 2
# define str 4
# define def 6
# define sc 8
# define br 10
# define thru 12
# define sh 14
#undef	input
#undef	unput
#include <stdio.h>
#include <ctype.h>
#include "pic.h"
#include "y.tab.h"

extern	float	atof();
extern	struct	symtab	symtab[];
extern	char	*filename, *copythru();

#define	CADD	cbuf[clen++]=yytext[0]; if(clen>=CBUFLEN-1) {yyerror("string too long", cbuf); BEGIN A;}
#define	CBUFLEN	500
char	cbuf[CBUFLEN];
int	c, clen, cflag, delim;
int	ifsw	= 0;	/* 1 if if statement in progress */
# define YYNEWLINE 10
yylex(){
int nstr; extern int yyprevious;
switch (yybgin-yysvec-1) {	/* witchcraft */
	case 0:
		BEGIN A;
		break;
	case sc:
		BEGIN A;
		return('}');
	case br:
		BEGIN A;
		return(']');
	}
while((nstr = yylook()) >= 0)
yyfussy: switch(nstr){
case 0:
if(yywrap()) return(0); break;
case 1:
	;
break;
case 2:
;
break;
case 3:
	{ return(ST); }
break;
case 4:
	{ return(ST); }
break;
case 5:
	{ BEGIN sc; return(ST); }
break;
case 6:
	{ BEGIN br; return(ST); }
break;
case 7:
{ if (curfile == infile) yyerror(".PS found inside .PS/.PE"); }
break;
case 8:
{ if (curfile == infile) {
			yylval.i = yytext[2];
			return(EOF);
		  }
		}
break;
case 9:
{ yylval.p = tostring(yytext); return(TROFF); }
break;
case 10:
return(yylval.i = PRINT);
break;
case 11:
	return(yylval.i = BOX);
break;
case 12:
return(yylval.i = CIRCLE);
break;
case 13:
	return(yylval.i = ARC);
break;
case 14:
return(yylval.i = ELLIPSE);
break;
case 15:
return(yylval.i = ARROW);
break;
case 16:
return(yylval.i = SPLINE);
break;
case 17:
	return(yylval.i = LINE);
break;
case 18:
	return(yylval.i = MOVE);
break;
case 19:
	return(yylval.i = BLOCK);
break;
case 20:
return(RESET);
break;
case 21:
return(SPRINTF);
break;
case 22:
	return(SAME);
break;
case 23:
return(BETWEEN);
break;
case 24:
	return(AND);
break;
case 25:
	;
break;
case 26:
	;
break;
case 27:
	;
break;
case 28:
	{ yylval.i = EAST; return(CORNER); }
break;
case 29:
	{ yylval.i = EAST; return(CORNER); }
break;
case 30:
	{ yylval.i = WEST; return(CORNER); }
break;
case 31:
	{ yylval.i = WEST; return(CORNER); }
break;
case 32:
	{ yylval.i = NORTH; return(CORNER); }
break;
case 33:
	{ yylval.i = NORTH; return(CORNER); }
break;
case 34:
	{ yylval.i = SOUTH; return(CORNER); }
break;
case 35:
{ yylval.i = SOUTH; return(CORNER); }
break;
case 36:
{ yylval.i = CENTER; return(CORNER); }
break;
case 37:
	{ yylval.i = START; return(CORNER); }
break;
case 38:
	{ yylval.i = END; return(CORNER); }
break;
case 39:
	{ yylval.i = NE; return(CORNER); }
break;
case 40:
	{ yylval.i = SE; return(CORNER); }
break;
case 41:
	{ yylval.i = NW; return(CORNER); }
break;
case 42:
	{ yylval.i = SW; return(CORNER); }
break;
case 43:
	{ yylval.i = NORTH; return(CORNER); }
break;
case 44:
	{ yylval.i = NORTH; return(CORNER); }
break;
case 45:
	{ yylval.i = SOUTH; return(CORNER); }
break;
case 46:
	{ yylval.i = SOUTH; return(CORNER); }
break;
case 47:
	{ yylval.i = WEST; return(CORNER); }
break;
case 48:
	{ yylval.i = WEST; return(CORNER); }
break;
case 49:
	{ yylval.i = EAST; return(CORNER); }
break;
case 50:
	{ yylval.i = EAST; return(CORNER); }
break;
case 51:
	{ yylval.i = CENTER; return(CORNER); }
break;
case 52:
	{ yylval.i = START; return(CORNER); }
break;
case 53:
	{ yylval.i = END; return(CORNER); }
break;
case 54:
{ yylval.i = HEIGHT; return(ATTR); }
break;
case 55:
{ yylval.i = WIDTH; return(ATTR); }
break;
case 56:
{ yylval.i = RADIUS; return(ATTR); }
break;
case 57:
{ yylval.i = DIAMETER; return(ATTR); }
break;
case 58:
	{ yylval.i = SIZE; return(ATTR); }
break;
case 59:
	{ yylval.i = LEFT; return(DIR); }
break;
case 60:
{ yylval.i = RIGHT; return(DIR); }
break;
case 61:
	{ yylval.i = UP; return(DIR); }
break;
case 62:
	{ yylval.i = DOWN; return(DIR); }
break;
case 63:
	{ yylval.i = CW; return(ATTR); }
break;
case 64:
{ yylval.i = CW; return(ATTR); }
break;
case 65:
	{ yylval.i = CCW; return(ATTR); }
break;
case 66:
{ yylval.i = INVIS; return(ATTR); }
break;
case 67:
return(yylval.i = DOT);
break;
case 68:
return(yylval.i = DASH);
break;
case 69:
	return(yylval.i = CHOP);
break;
case 70:
{ yylval.i = SPREAD; return TEXTATTR; }
break;
case 71:
	{ yylval.i = FILL; return TEXTATTR; }
break;
case 72:
{ yylval.i = LJUST; return TEXTATTR; }
break;
case 73:
{ yylval.i = RJUST; return TEXTATTR; }
break;
case 74:
{ yylval.i = ABOVE; return TEXTATTR; }
break;
case 75:
{ yylval.i = BELOW; return TEXTATTR; }
break;
case 76:
{ yylval.i = CENTER; return TEXTATTR; }
break;
case 77:
	{ yylval.i = HEAD1; return(HEAD); }
break;
case 78:
	{ yylval.i = HEAD2; return(HEAD); }
break;
case 79:
{ yylval.i = HEAD12; return(HEAD); }
break;
case 80:
		return(yylval.i = DOTX);
break;
case 81:
		return(yylval.i = DOTY);
break;
case 82:
return(yylval.i = DOTHT);
break;
case 83:
return(yylval.i = DOTWID);
break;
case 84:
return(yylval.i = DOTRAD);
break;
case 85:
	return(yylval.i = FROM);
break;
case 86:
	return(yylval.i = TO);
break;
case 87:
	return(yylval.i = AT);
break;
case 88:
	return(yylval.i = BY);
break;
case 89:
	return(yylval.i = WITH);
break;
case 90:
	return(yylval.i = LAST);
break;
case 91:
	return(LOG);
break;
case 92:
	return(EXP);
break;
case 93:
	return(SIN);
break;
case 94:
	return(COS);
break;
case 95:
return(ATAN2);
break;
case 96:
	return(SQRT);
break;
case 97:
	return(RAND);
break;
case 98:
	return(MAX);
break;
case 99:
	return(MIN);
break;
case 100:
	return(INT);
break;
case 101:
	return(EQ);
break;
case 102:
	return(GE);
break;
case 103:
	return(LE);
break;
case 104:
	return(NEQ);
break;
case 105:
	return(GT);
break;
case 106:
	return(LT);
break;
case 107:
	return(ANDAND);
break;
case 108:
	return(OROR);
break;
case 109:
	return(NOT);
break;
case 110:
	return(yylval.i = HERE);
break;
case 111:
	return(FOR);
break;
case 112:
{ endfor(); }
break;
case 113:
	{ yylval.p = delimstr("loop body"); return(DOSTR); }
break;
case 114:
	return(COPY);
break;
case 115:
{ BEGIN thru; return(THRU); }
break;
case 116:
	{ yylval.p = copythru(yytext); BEGIN A; return(DEFNAME); }
break;
case 117:
	return(UNTIL);
break;
case 118:
	{ ifsw = 1; return(IF); }
break;
case 119:
	{ if (!ifsw) { yylval.i = THEN; return(ATTR); }
		  yylval.p = delimstr("then part"); ifsw = 0;
		  return(THENSTR); }
break;
case 120:
	{ yylval.p = delimstr("else part"); return(ELSESTR); }
break;
case 121:
{ BEGIN sh;
		  if ((delim = input()) == '{') delim = '}';	/* no nested {} */
		  shell_init(); }
break;
case 122:
{ struct symtab *p;
		  if (yytext[0] == delim) {
			shell_exec();
			BEGIN A;
		  } else {
			p = lookup(yytext, 0);
			if (p != NULL && p->s_type == DEFNAME) {
				c = input();
				unput(c);
				if (c == '(')
					dodef(p);
				else
					pbstr(p->s_val.p);
			} else
				shell_text(yytext);
		  }
		}
break;
case 123:
{ if (yytext[0] == delim) {
			shell_exec();
			BEGIN A;
		  } else
			shell_text(yytext);
		}
break;
case 124:
	{ BEGIN def; }
break;
case 125:
	{ definition(yytext); BEGIN A; }
break;
case 126:
{ undefine(yytext); }
break;
case 127:
	{ yylval.i = 1; return(NTH); }
break;
case 128:
{ yylval.i = atoi(yytext); return(NTH); }
break;
case 129:
{
		  	yylval.f = atof(yytext); return(NUMBER); }
break;
case 130:
{	struct symtab *p;
		p = lookup(yytext);
		if (p != NULL && p->s_type == DEFNAME) {
			c = input();
			unput(c);
			if (c == '(')	/* it's name(...) */
				dodef(p);
			else {	/* no argument list */
				pbstr(p->s_val);
				dprintf("pushing back `%s'\n", p->s_val);
			}
		} else if (islower(yytext[0])) {
			yylval.p = tostring(yytext);
			return(VARNAME);
		} else {
			yylval.p = tostring(yytext);
			return(PLACENAME);
		}
	}
break;
case 131:
	{ BEGIN str; clen=0; }
break;
case 132:
	{ cbuf[clen]=0; yylval.p = tostring(cbuf); BEGIN A; return(TEXT); }
break;
case 133:
	{ yyerror("newline in string"); BEGIN A; return(ST); }
break;
case 134:
{ cbuf[clen++]='"'; }
break;
case 135:
{ cbuf[clen++]='\t'; }
break;
case 136:
{ cbuf[clen++]='\\'; }
break;
case 137:
	{ CADD; }
break;
case 138:
	;
break;
case 139:
	return(yylval.i = yytext[0]);
break;
case -1:
break;
default:
fprintf(yyout,"bad switch yylook %d",nstr);
} return(0); }
/* end of yylex */
int yyvstop[] ={
0,

139,
0,

1,
139,
0,

3,
0,

109,
139,
0,

131,
139,
0,

138,
139,
0,

139,
0,

139,
0,

139,
0,

129,
139,
0,

4,
139,
0,

106,
139,
0,

139,
0,

105,
139,
0,

130,
139,
0,

130,
139,
0,

139,
0,

139,
0,

6,
139,
0,

130,
139,
0,

130,
139,
0,

130,
139,
0,

130,
139,
0,

130,
139,
0,

130,
139,
0,

130,
139,
0,

130,
139,
0,

130,
139,
0,

130,
139,
0,

130,
139,
0,

130,
139,
0,

130,
139,
0,

130,
139,
0,

130,
139,
0,

130,
139,
0,

130,
139,
0,

130,
139,
0,

139,
0,

5,
139,
0,

9,
139,
0,

130,
139,
0,

137,
0,

133,
0,

132,
137,
0,

137,
0,

125,
0,

116,
0,

116,
0,

123,
0,

122,
123,
0,

104,
0,

138,
0,

107,
0,

78,
0,

129,
0,

35,
0,

36,
0,

28,
0,

31,
0,

32,
0,

29,
0,

34,
0,

33,
0,

30,
0,

80,
0,

81,
0,

129,
0,

129,
0,

129,
0,

77,
0,

103,
0,

101,
0,

102,
0,

130,
0,

130,
0,

19,
0,

2,
0,

130,
0,

130,
0,

130,
0,

87,
130,
0,

130,
0,

130,
0,

88,
130,
0,

130,
0,

130,
0,

130,
0,

130,
0,

130,
0,

130,
0,

63,
130,
0,

130,
0,

130,
0,

130,
0,

113,
130,
0,

130,
0,

130,
0,

130,
0,

130,
0,

130,
0,

130,
0,

130,
0,

130,
0,

54,
130,
0,

118,
130,
0,

130,
0,

130,
0,

130,
0,

130,
0,

130,
0,

130,
0,

130,
0,

130,
0,

130,
0,

130,
0,

25,
130,
0,

130,
0,

130,
0,

130,
0,

130,
0,

130,
0,

130,
0,

130,
0,

130,
0,

130,
0,

130,
0,

130,
0,

130,
0,

130,
0,

86,
130,
0,

130,
0,

61,
130,
0,

130,
0,

130,
0,

130,
0,

108,
0,

9,
0,

9,
129,
0,

9,
0,

9,
35,
0,

9,
36,
0,

9,
28,
0,

9,
0,

9,
31,
0,

9,
32,
0,

9,
29,
0,

9,
34,
0,

9,
33,
0,

9,
30,
0,

9,
80,
0,

9,
81,
0,

130,
0,

134,
0,

136,
0,

135,
0,

122,
0,

82,
0,

39,
0,

41,
0,

40,
0,

42,
0,

129,
0,

128,
0,

79,
0,

130,
0,

130,
0,

24,
130,
0,

13,
130,
0,

130,
0,

130,
0,

130,
0,

130,
0,

130,
0,

11,
130,
0,

65,
130,
0,

130,
0,

130,
0,

130,
0,

130,
0,

130,
0,

94,
130,
0,

130,
0,

130,
0,

130,
0,

67,
130,
0,

130,
0,

130,
0,

130,
0,

130,
0,

130,
0,

92,
130,
0,

130,
0,

130,
0,

111,
130,
0,

130,
0,

130,
0,

130,
0,

100,
130,
0,

130,
0,

130,
0,

130,
0,

130,
0,

130,
0,

91,
130,
0,

98,
130,
0,

99,
130,
0,

130,
0,

130,
0,

130,
0,

56,
130,
0,

130,
0,

130,
0,

130,
0,

130,
0,

130,
0,

121,
0,

93,
130,
0,

130,
0,

130,
0,

130,
0,

130,
0,

130,
0,

130,
0,

26,
130,
0,

130,
0,

130,
0,

130,
0,

130,
0,

27,
130,
0,

130,
0,

55,
130,
0,

130,
0,

9,
0,

9,
129,
0,

8,
9,
0,

7,
9,
0,

9,
0,

9,
0,

9,
0,

9,
0,

9,
0,

9,
82,
0,

9,
0,

9,
39,
0,

9,
0,

9,
41,
0,

9,
0,

9,
0,

9,
40,
0,

9,
0,

9,
0,

9,
42,
0,

9,
0,

9,
0,

9,
0,

130,
0,

35,
0,

38,
0,

84,
0,

33,
0,

83,
0,

110,
130,
0,

130,
0,

130,
0,

130,
0,

130,
0,

130,
0,

130,
0,

130,
0,

69,
130,
0,

130,
0,

130,
0,

114,
130,
0,

68,
130,
0,

130,
0,

57,
130,
0,

130,
0,

62,
130,
0,

130,
0,

130,
0,

120,
130,
0,

71,
130,
0,

130,
0,

85,
130,
0,

130,
0,

130,
0,

130,
0,

90,
130,
0,

59,
130,
0,

17,
130,
0,

130,
0,

18,
130,
0,

130,
0,

130,
0,

130,
0,

97,
130,
0,

130,
0,

130,
0,

130,
0,

22,
130,
0,

58,
130,
0,

130,
0,

130,
0,

130,
0,

130,
0,

96,
130,
0,

130,
0,

119,
130,
0,

130,
0,

130,
0,

130,
0,

130,
0,

130,
0,

130,
0,

89,
130,
0,

9,
0,

9,
129,
0,

9,
35,
0,

9,
0,

9,
0,

9,
38,
0,

9,
0,

9,
0,

9,
0,

9,
84,
0,

9,
0,

9,
0,

9,
0,

9,
33,
0,

9,
0,

9,
83,
0,

130,
0,

28,
0,

31,
0,

30,
0,

74,
130,
0,

15,
130,
0,

95,
130,
0,

75,
130,
0,

130,
0,

130,
0,

130,
0,

130,
0,

130,
0,

130,
0,

130,
0,

130,
0,

130,
0,

130,
0,

127,
130,
0,

130,
0,

130,
0,

66,
130,
0,

72,
130,
0,

130,
0,

10,
130,
0,

130,
0,

20,
130,
0,

60,
130,
0,

73,
130,
0,

130,
0,

130,
0,

130,
0,

130,
0,

130,
0,

130,
0,

115,
0,

130,
0,

117,
130,
0,

55,
130,
0,

9,
0,

9,
0,

9,
28,
0,

9,
0,

9,
31,
0,

9,
0,

9,
0,

9,
0,

9,
0,

9,
0,

9,
30,
0,

9,
0,

130,
0,

32,
0,

29,
0,

34,
0,

37,
0,

83,
0,

130,
0,

130,
0,

76,
130,
0,

12,
130,
0,

130,
0,

68,
130,
0,

130,
0,

130,
0,

67,
130,
0,

130,
0,

53,
0,

130,
0,

130,
0,

56,
130,
0,

16,
130,
0,

70,
130,
0,

130,
0,

130,
0,

43,
0,

130,
0,

9,
0,

9,
0,

9,
0,

9,
32,
0,

9,
0,

9,
29,
0,

9,
34,
0,

9,
37,
0,

9,
83,
0,

130,
0,

35,
0,

36,
0,

84,
0,

23,
130,
0,

130,
0,

124,
0,

130,
0,

50,
0,

14,
130,
0,

130,
0,

47,
0,

21,
130,
0,

126,
0,

130,
0,

48,
0,

9,
35,
0,

9,
36,
0,

9,
84,
0,

112,
0,

130,
0,

57,
130,
0,

130,
0,

44,
0,

49,
0,

46,
0,

52,
0,

130,
0,

45,
0,

51,
0,

64,
130,
0,

66,
130,
0,
0};
# define YYTYPE int
struct yywork { YYTYPE verify, advance; } yycrank[] ={
0,0,	0,0,	3,17,	0,0,	
5,58,	0,0,	0,0,	13,63,	
0,0,	0,0,	3,18,	3,19,	
5,58,	5,59,	14,0,	13,63,	
13,0,	15,65,	34,99,	0,0,	
22,68,	0,0,	0,0,	0,0,	
0,0,	15,65,	15,65,	0,0,	
22,68,	22,0,	68,0,	0,0,	
0,0,	0,0,	3,20,	3,21,	
3,22,	5,60,	6,60,	3,23,	
23,69,	0,0,	0,0,	0,0,	
0,0,	0,0,	3,24,	3,25,	
0,0,	3,26,	0,0,	5,58,	
0,0,	0,0,	13,63,	0,0,	
0,0,	0,0,	28,92,	0,0,	
3,27,	3,28,	3,29,	3,30,	
15,65,	20,67,	3,31,	22,68,	
5,58,	24,70,	3,31,	13,64,	
5,58,	3,32,	28,93,	13,64,	
29,94,	30,95,	0,0,	0,0,	
0,0,	15,66,	0,0,	0,0,	
22,68,	15,66,	0,0,	0,0,	
22,68,	0,0,	0,0,	0,0,	
3,33,	3,34,	3,35,	5,61,	
6,61,	33,98,	3,36,	3,37,	
3,38,	3,39,	3,40,	3,41,	
32,97,	3,42,	3,43,	47,138,	
0,0,	3,44,	3,45,	3,46,	
3,47,	3,48,	42,125,	3,49,	
3,50,	3,51,	3,52,	46,137,	
3,53,	36,100,	4,20,	4,21,	
4,22,	3,54,	3,55,	4,23,	
43,127,	42,126,	40,118,	48,139,	
37,104,	36,101,	4,24,	4,56,	
43,128,	36,102,	41,122,	36,103,	
54,158,	40,119,	37,105,	40,120,	
41,123,	57,174,	72,179,	41,124,	
4,27,	4,28,	4,29,	4,30,	
37,106,	40,121,	73,180,	51,151,	
39,114,	76,185,	4,57,	4,31,	
39,115,	4,32,	51,152,	38,107,	
39,116,	38,108,	80,195,	88,200,	
38,109,	38,110,	39,117,	45,134,	
38,111,	90,200,	52,153,	38,112,	
52,154,	75,183,	91,200,	45,135,	
4,33,	4,34,	4,35,	38,113,	
92,201,	45,136,	4,36,	4,37,	
4,38,	4,39,	4,40,	4,41,	
75,184,	4,42,	4,43,	97,202,	
74,181,	4,44,	4,45,	4,46,	
4,47,	4,48,	78,189,	4,49,	
4,50,	4,51,	4,52,	81,196,	
4,53,	74,182,	78,190,	81,197,	
100,203,	4,54,	4,55,	7,62,	
7,62,	7,62,	7,62,	7,62,	
7,62,	7,62,	7,62,	7,62,	
7,62,	7,62,	7,62,	7,62,	
7,62,	7,62,	7,62,	7,62,	
7,62,	7,62,	7,62,	7,62,	
7,62,	7,62,	7,62,	7,62,	
7,62,	101,204,	103,207,	107,212,	
108,213,	7,62,	109,214,	7,62,	
7,62,	7,62,	7,62,	7,62,	
7,62,	7,62,	7,62,	7,62,	
7,62,	7,62,	7,62,	7,62,	
7,62,	7,62,	7,62,	7,62,	
7,62,	7,62,	7,62,	7,62,	
7,62,	7,62,	7,62,	7,62,	
7,62,	25,71,	25,71,	25,71,	
25,71,	25,71,	25,71,	25,71,	
25,71,	25,71,	25,71,	26,84,	
110,215,	26,85,	26,85,	26,85,	
26,85,	26,85,	26,85,	26,85,	
26,85,	26,85,	26,85,	44,129,	
111,216,	53,155,	102,205,	44,130,	
77,186,	53,156,	79,191,	44,131,	
44,132,	53,157,	26,86,	49,140,	
114,219,	44,133,	77,187,	49,141,	
79,192,	102,206,	104,208,	49,142,	
49,143,	79,193,	77,188,	115,220,	
79,194,	105,210,	104,209,	25,72,	
25,73,	105,211,	25,74,	112,217,	
116,221,	25,75,	112,218,	117,222,	
118,224,	25,76,	117,223,	25,77,	
119,225,	120,227,	26,86,	25,78,	
25,79,	25,80,	26,87,	119,226,	
25,81,	25,82,	25,83,	26,88,	
121,228,	123,231,	124,232,	26,89,	
26,90,	26,91,	31,96,	31,96,	
31,96,	31,96,	31,96,	31,96,	
31,96,	31,96,	31,96,	31,96,	
122,229,	125,233,	129,237,	130,238,	
131,239,	132,240,	122,230,	31,96,	
31,96,	31,96,	31,96,	31,96,	
31,96,	31,96,	31,96,	31,96,	
31,96,	31,96,	31,96,	31,96,	
31,96,	31,96,	31,96,	31,96,	
31,96,	31,96,	31,96,	31,96,	
31,96,	31,96,	31,96,	31,96,	
31,96,	61,175,	133,241,	134,242,	
135,243,	31,96,	136,244,	31,96,	
31,96,	31,96,	31,96,	31,96,	
31,96,	31,96,	31,96,	31,96,	
31,96,	31,96,	31,96,	31,96,	
31,96,	31,96,	31,96,	31,96,	
31,96,	31,96,	31,96,	31,96,	
31,96,	31,96,	31,96,	31,96,	
31,96,	50,144,	56,159,	137,245,	
128,234,	139,246,	141,249,	142,250,	
50,145,	50,146,	56,159,	56,0,	
140,247,	143,251,	144,252,	50,147,	
50,148,	50,149,	147,256,	149,259,	
50,150,	128,235,	140,248,	128,236,	
150,260,	145,253,	152,263,	61,176,	
62,62,	62,62,	62,62,	62,62,	
62,62,	62,62,	62,62,	62,62,	
62,62,	62,62,	71,71,	71,71,	
71,71,	71,71,	71,71,	71,71,	
71,71,	71,71,	71,71,	71,71,	
145,253,	56,160,	146,254,	61,177,	
148,257,	153,264,	151,261,	155,266,	
156,267,	172,0,	148,258,	71,86,	
161,0,	173,0,	146,255,	174,293,	
179,294,	162,0,	56,159,	151,262,	
157,268,	153,265,	56,159,	84,84,	
84,84,	84,84,	84,84,	84,84,	
84,84,	84,84,	84,84,	84,84,	
84,84,	56,161,	180,295,	181,296,	
157,269,	182,297,	183,298,	185,299,	
187,300,	189,301,	190,302,	71,86,	
192,303,	193,304,	195,305,	71,87,	
196,306,	197,307,	199,87,	56,162,	
56,163,	202,308,	56,164,	203,309,	
206,310,	56,165,	207,311,	208,312,	
209,313,	56,166,	210,314,	56,167,	
213,315,	170,0,	214,316,	56,168,	
56,169,	56,170,	163,0,	161,272,	
56,171,	56,172,	56,173,	64,64,	
64,64,	64,64,	64,64,	64,64,	
64,64,	64,64,	64,64,	64,64,	
64,64,	161,273,	215,317,	216,318,	
217,319,	219,320,	220,321,	221,322,	
64,64,	64,64,	64,64,	64,64,	
64,64,	64,64,	64,64,	64,64,	
64,64,	64,64,	64,64,	64,64,	
64,64,	64,64,	64,64,	64,64,	
64,64,	64,64,	64,64,	64,64,	
64,64,	64,64,	64,64,	64,64,	
64,64,	64,64,	162,274,	222,323,	
223,324,	224,325,	64,64,	225,326,	
64,64,	64,64,	64,64,	64,64,	
64,64,	64,64,	64,64,	64,64,	
64,64,	64,64,	64,64,	64,64,	
64,64,	64,64,	64,64,	64,64,	
64,64,	64,64,	64,64,	64,64,	
64,64,	64,64,	64,64,	64,64,	
64,64,	64,64,	66,178,	66,178,	
66,178,	66,178,	66,178,	66,178,	
66,178,	66,178,	66,178,	66,178,	
164,0,	163,275,	165,0,	166,0,	
167,0,	169,0,	170,290,	66,178,	
66,178,	66,178,	66,178,	66,178,	
66,178,	66,178,	66,178,	66,178,	
66,178,	66,178,	66,178,	66,178,	
66,178,	66,178,	66,178,	66,178,	
66,178,	66,178,	66,178,	66,178,	
66,178,	66,178,	66,178,	66,178,	
66,178,	168,0,	226,327,	171,0,	
227,328,	66,178,	229,329,	66,178,	
66,178,	66,178,	66,178,	66,178,	
66,178,	66,178,	66,178,	66,178,	
66,178,	66,178,	66,178,	66,178,	
66,178,	66,178,	66,178,	66,178,	
66,178,	66,178,	66,178,	66,178,	
66,178,	66,178,	66,178,	66,178,	
66,178,	86,198,	230,330,	86,198,	
232,331,	233,332,	86,199,	86,199,	
86,199,	86,199,	86,199,	86,199,	
86,199,	86,199,	86,199,	86,199,	
159,159,	234,333,	160,159,	236,334,	
237,335,	238,336,	239,337,	164,276,	
159,159,	159,0,	160,159,	160,0,	
240,338,	165,278,	166,280,	167,281,	
169,286,	244,339,	245,340,	246,341,	
164,277,	247,342,	248,343,	249,344,	
250,345,	167,282,	169,287,	251,346,	
165,279,	252,347,	255,348,	169,288,	
256,349,	167,283,	169,289,	257,350,	
259,353,	258,351,	253,253,	260,354,	
168,284,	258,352,	261,355,	263,358,	
264,359,	265,360,	171,291,	159,159,	
168,285,	160,160,	171,292,	198,199,	
198,199,	198,199,	198,199,	198,199,	
198,199,	198,199,	198,199,	198,199,	
198,199,	253,253,	267,361,	262,356,	
159,159,	268,362,	160,159,	269,363,	
159,159,	262,357,	160,270,	160,159,	
270,0,	271,0,	272,272,	274,0,	
273,273,	275,0,	276,0,	277,0,	
278,0,	279,0,	272,272,	272,0,	
273,273,	273,0,	280,0,	281,0,	
282,0,	283,0,	284,0,	285,0,	
286,0,	287,0,	289,0,	288,0,	
290,0,	291,0,	292,0,	293,380,	
294,381,	295,382,	160,270,	296,383,	
298,384,	270,364,	160,271,	270,364,	
299,385,	300,386,	270,365,	301,387,	
302,388,	303,389,	304,390,	306,391,	
307,392,	309,393,	310,394,	311,395,	
312,396,	272,272,	313,397,	273,273,	
314,398,	315,399,	317,400,	318,401,	
320,402,	321,403,	322,404,	323,405,	
325,406,	326,407,	328,328,	330,409,	
332,410,	333,411,	272,272,	334,412,	
273,273,	336,413,	272,272,	338,414,	
273,273,	340,415,	341,416,	342,417,	
344,418,	345,419,	346,420,	349,421,	
350,422,	351,423,	352,424,	354,425,	
356,426,	358,358,	359,429,	360,430,	
361,431,	362,432,	357,427,	364,0,	
366,0,	365,0,	367,0,	368,0,	
369,0,	277,369,	370,0,	371,0,	
372,0,	373,0,	377,0,	278,370,	
375,0,	275,367,	280,371,	376,0,	
284,373,	274,366,	288,376,	276,368,	
285,374,	357,427,	374,0,	378,0,	
292,379,	379,0,	380,445,	381,446,	
282,372,	382,447,	384,448,	386,449,	
387,450,	388,451,	290,377,	389,452,	
287,375,	364,365,	291,378,	365,365,	
390,453,	392,454,	397,455,	398,456,	
399,457,	400,458,	401,459,	402,460,	
403,461,	328,408,	404,462,	405,463,	
407,465,	406,406,	408,466,	410,126,	
411,467,	412,468,	413,413,	415,470,	
417,471,	419,472,	421,473,	422,474,	
423,475,	424,476,	425,477,	426,478,	
427,427,	428,479,	429,480,	431,431,	
358,428,	433,0,	434,0,	435,0,	
436,0,	437,0,	438,0,	439,0,	
443,0,	440,0,	441,0,	442,0,	
444,0,	445,492,	446,493,	447,494,	
448,184,	450,495,	455,496,	427,427,	
456,497,	429,480,	457,498,	459,499,	
365,271,	461,500,	462,501,	370,436,	
464,502,	465,503,	467,319,	468,504,	
373,439,	469,505,	366,433,	476,509,	
367,434,	368,435,	478,357,	470,470,	
472,472,	371,437,	372,438,	473,473,	
374,440,	477,477,	375,441,	376,442,	
461,500,	481,512,	482,513,	486,0,	
483,0,	488,0,	489,0,	490,0,	
491,0,	378,443,	492,517,	379,444,	
406,464,	499,520,	500,500,	501,521,	
504,522,	413,469,	506,523,	507,524,	
508,525,	480,480,	510,526,	512,527,	
514,0,	497,497,	498,498,	515,0,	
516,0,	518,528,	431,482,	484,0,	
485,0,	519,529,	487,0,	520,530,	
522,531,	500,500,	527,480,	0,0,	
0,0,	0,0,	0,0,	0,0,	
480,480,	434,484,	429,481,	0,0,	
0,0,	0,0,	436,485,	0,0,	
438,486,	0,0,	433,483,	0,0,	
441,489,	0,0,	444,491,	0,0,	
0,0,	527,480,	0,0,	0,0,	
0,0,	0,0,	439,487,	440,488,	
0,0,	442,490,	470,506,	472,507,	
0,0,	0,0,	473,508,	0,0,	
477,510,	480,511,	480,511,	480,511,	
480,511,	480,511,	480,511,	480,511,	
480,511,	480,511,	480,511,	480,511,	
480,511,	480,511,	480,511,	480,511,	
480,511,	480,511,	480,511,	480,511,	
480,511,	480,511,	480,511,	480,511,	
480,511,	480,511,	480,511,	483,514,	
497,518,	498,519,	0,0,	480,511,	
0,0,	480,511,	480,511,	480,511,	
480,511,	480,511,	480,511,	480,511,	
480,511,	480,511,	480,511,	480,511,	
480,511,	480,511,	480,511,	480,511,	
480,511,	480,511,	480,511,	480,511,	
480,511,	480,511,	480,511,	480,511,	
480,511,	480,511,	480,511,	484,515,	
0,0,	0,0,	485,279,	487,516,	
511,511,	511,511,	511,511,	511,511,	
511,511,	511,511,	511,511,	511,511,	
511,511,	511,511,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	511,511,	511,511,	511,511,	
511,511,	511,511,	511,511,	511,511,	
511,511,	511,511,	511,511,	511,511,	
511,511,	511,511,	511,511,	511,511,	
511,511,	511,511,	511,511,	511,511,	
511,511,	511,511,	511,511,	511,511,	
511,511,	511,511,	511,511,	0,0,	
0,0,	0,0,	0,0,	511,511,	
0,0,	511,511,	511,511,	511,511,	
511,511,	511,511,	511,511,	511,511,	
511,511,	511,511,	511,511,	511,511,	
511,511,	511,511,	511,511,	511,511,	
511,511,	511,511,	511,511,	511,511,	
511,511,	511,511,	511,511,	511,511,	
511,511,	511,511,	511,511,	0,0,	
0,0};
struct yysvf yysvec[] ={
0,	0,	0,
yycrank+0,	0,		0,	
yycrank+0,	0,		0,	
yycrank+-1,	0,		0,	
yycrank+-89,	yysvec+3,	0,	
yycrank+-3,	0,		0,	
yycrank+-4,	yysvec+5,	0,	
yycrank+150,	0,		0,	
yycrank+0,	yysvec+7,	0,	
yycrank+0,	0,		0,	
yycrank+0,	0,		0,	
yycrank+0,	0,		0,	
yycrank+0,	0,		0,	
yycrank+-6,	0,		0,	
yycrank+-4,	yysvec+13,	0,	
yycrank+-16,	0,		0,	
yycrank+0,	yysvec+15,	0,	
yycrank+0,	0,		yyvstop+1,
yycrank+0,	0,		yyvstop+3,
yycrank+0,	0,		yyvstop+6,
yycrank+4,	0,		yyvstop+8,
yycrank+0,	0,		yyvstop+11,
yycrank+-19,	0,		yyvstop+14,
yycrank+2,	0,		yyvstop+17,
yycrank+7,	0,		yyvstop+19,
yycrank+225,	0,		yyvstop+21,
yycrank+237,	0,		yyvstop+23,
yycrank+0,	0,		yyvstop+26,
yycrank+13,	0,		yyvstop+29,
yycrank+15,	0,		yyvstop+32,
yycrank+16,	0,		yyvstop+34,
yycrank+306,	0,		yyvstop+37,
yycrank+3,	yysvec+31,	yyvstop+40,
yycrank+4,	0,		yyvstop+43,
yycrank+8,	0,		yyvstop+45,
yycrank+0,	0,		yyvstop+47,
yycrank+23,	yysvec+31,	yyvstop+50,
yycrank+31,	yysvec+31,	yyvstop+53,
yycrank+64,	yysvec+31,	yyvstop+56,
yycrank+59,	yysvec+31,	yyvstop+59,
yycrank+33,	yysvec+31,	yyvstop+62,
yycrank+33,	yysvec+31,	yyvstop+65,
yycrank+13,	yysvec+31,	yyvstop+68,
yycrank+26,	yysvec+31,	yyvstop+71,
yycrank+198,	yysvec+31,	yyvstop+74,
yycrank+74,	yysvec+31,	yyvstop+77,
yycrank+8,	yysvec+31,	yyvstop+80,
yycrank+5,	yysvec+31,	yyvstop+83,
yycrank+17,	yysvec+31,	yyvstop+86,
yycrank+210,	yysvec+31,	yyvstop+89,
yycrank+332,	yysvec+31,	yyvstop+92,
yycrank+51,	yysvec+31,	yyvstop+95,
yycrank+64,	yysvec+31,	yyvstop+98,
yycrank+200,	yysvec+31,	yyvstop+101,
yycrank+16,	0,		yyvstop+104,
yycrank+0,	0,		yyvstop+106,
yycrank+-429,	0,		yyvstop+109,
yycrank+35,	yysvec+31,	yyvstop+112,
yycrank+0,	0,		yyvstop+115,
yycrank+0,	0,		yyvstop+117,
yycrank+0,	0,		yyvstop+119,
yycrank+363,	0,		yyvstop+122,
yycrank+408,	yysvec+7,	yyvstop+124,
yycrank+0,	0,		yyvstop+126,
yycrank+503,	0,		yyvstop+128,
yycrank+0,	0,		yyvstop+130,
yycrank+578,	0,		yyvstop+132,
yycrank+0,	0,		yyvstop+135,
yycrank+-20,	yysvec+22,	yyvstop+137,
yycrank+0,	0,		yyvstop+139,
yycrank+0,	0,		yyvstop+141,
yycrank+418,	0,		yyvstop+143,
yycrank+35,	0,		yyvstop+145,
yycrank+53,	0,		yyvstop+147,
yycrank+99,	0,		yyvstop+149,
yycrank+76,	0,		0,	
yycrank+56,	0,		yyvstop+151,
yycrank+199,	0,		yyvstop+153,
yycrank+105,	0,		yyvstop+155,
yycrank+201,	0,		yyvstop+157,
yycrank+55,	0,		yyvstop+159,
yycrank+106,	0,		yyvstop+161,
yycrank+0,	0,		yyvstop+163,
yycrank+0,	0,		yyvstop+165,
yycrank+451,	yysvec+71,	yyvstop+167,
yycrank+0,	yysvec+26,	yyvstop+169,
yycrank+658,	0,		0,	
yycrank+0,	0,		yyvstop+171,
yycrank+67,	0,		0,	
yycrank+0,	yysvec+88,	0,	
yycrank+57,	0,		0,	
yycrank+74,	0,		0,	
yycrank+122,	0,		yyvstop+173,
yycrank+0,	0,		yyvstop+175,
yycrank+0,	0,		yyvstop+177,
yycrank+0,	0,		yyvstop+179,
yycrank+0,	yysvec+31,	yyvstop+181,
yycrank+81,	yysvec+31,	yyvstop+183,
yycrank+0,	0,		yyvstop+185,
yycrank+0,	0,		yyvstop+187,
yycrank+101,	yysvec+31,	yyvstop+189,
yycrank+141,	yysvec+31,	yyvstop+191,
yycrank+199,	yysvec+31,	yyvstop+193,
yycrank+145,	yysvec+31,	yyvstop+195,
yycrank+206,	yysvec+31,	yyvstop+198,
yycrank+205,	yysvec+31,	yyvstop+200,
yycrank+0,	yysvec+31,	yyvstop+202,
yycrank+124,	yysvec+31,	yyvstop+205,
yycrank+134,	yysvec+31,	yyvstop+207,
yycrank+135,	yysvec+31,	yyvstop+209,
yycrank+170,	yysvec+31,	yyvstop+211,
yycrank+185,	yysvec+31,	yyvstop+213,
yycrank+215,	yysvec+31,	yyvstop+215,
yycrank+0,	yysvec+31,	yyvstop+217,
yycrank+193,	yysvec+31,	yyvstop+220,
yycrank+217,	yysvec+31,	yyvstop+222,
yycrank+231,	yysvec+31,	yyvstop+224,
yycrank+215,	yysvec+31,	yyvstop+226,
yycrank+217,	yysvec+31,	yyvstop+229,
yycrank+228,	yysvec+31,	yyvstop+231,
yycrank+237,	yysvec+31,	yyvstop+233,
yycrank+236,	yysvec+31,	yyvstop+235,
yycrank+256,	yysvec+31,	yyvstop+237,
yycrank+235,	yysvec+31,	yyvstop+239,
yycrank+239,	yysvec+31,	yyvstop+241,
yycrank+260,	yysvec+31,	yyvstop+243,
yycrank+0,	yysvec+31,	yyvstop+245,
yycrank+0,	yysvec+31,	yyvstop+248,
yycrank+333,	yysvec+31,	yyvstop+251,
yycrank+251,	yysvec+31,	yyvstop+253,
yycrank+265,	yysvec+31,	yyvstop+255,
yycrank+258,	yysvec+31,	yyvstop+257,
yycrank+252,	yysvec+31,	yyvstop+259,
yycrank+295,	yysvec+31,	yyvstop+261,
yycrank+279,	yysvec+31,	yyvstop+263,
yycrank+290,	yysvec+31,	yyvstop+265,
yycrank+284,	yysvec+31,	yyvstop+267,
yycrank+317,	yysvec+31,	yyvstop+269,
yycrank+0,	yysvec+31,	yyvstop+271,
yycrank+328,	yysvec+31,	yyvstop+274,
yycrank+340,	yysvec+31,	yyvstop+276,
yycrank+319,	yysvec+31,	yyvstop+278,
yycrank+332,	yysvec+31,	yyvstop+280,
yycrank+324,	yysvec+31,	yyvstop+282,
yycrank+333,	yysvec+31,	yyvstop+284,
yycrank+444,	yysvec+31,	yyvstop+286,
yycrank+368,	yysvec+31,	yyvstop+288,
yycrank+329,	yysvec+31,	yyvstop+290,
yycrank+372,	yysvec+31,	yyvstop+292,
yycrank+333,	yysvec+31,	yyvstop+294,
yycrank+355,	yysvec+31,	yyvstop+296,
yycrank+381,	yysvec+31,	yyvstop+298,
yycrank+342,	yysvec+31,	yyvstop+300,
yycrank+381,	yysvec+31,	yyvstop+303,
yycrank+0,	yysvec+31,	yyvstop+305,
yycrank+362,	yysvec+31,	yyvstop+308,
yycrank+369,	yysvec+31,	yyvstop+310,
yycrank+396,	yysvec+31,	yyvstop+312,
yycrank+0,	0,		yyvstop+314,
yycrank+-715,	0,		yyvstop+316,
yycrank+-717,	0,		yyvstop+318,
yycrank+-478,	yysvec+159,	yyvstop+321,
yycrank+-483,	yysvec+159,	yyvstop+323,
yycrank+-536,	yysvec+159,	yyvstop+326,
yycrank+-626,	yysvec+159,	yyvstop+329,
yycrank+-628,	yysvec+159,	yyvstop+332,
yycrank+-629,	yysvec+159,	yyvstop+334,
yycrank+-630,	yysvec+159,	yyvstop+337,
yycrank+-659,	yysvec+159,	yyvstop+340,
yycrank+-631,	yysvec+159,	yyvstop+343,
yycrank+-531,	yysvec+159,	yyvstop+346,
yycrank+-661,	yysvec+159,	yyvstop+349,
yycrank+-475,	yysvec+159,	yyvstop+352,
yycrank+-479,	yysvec+159,	yyvstop+355,
yycrank+391,	yysvec+31,	yyvstop+358,
yycrank+0,	0,		yyvstop+360,
yycrank+0,	0,		yyvstop+362,
yycrank+0,	0,		yyvstop+364,
yycrank+0,	yysvec+66,	yyvstop+366,
yycrank+376,	0,		0,	
yycrank+400,	0,		0,	
yycrank+396,	0,		0,	
yycrank+413,	0,		0,	
yycrank+409,	0,		0,	
yycrank+0,	0,		yyvstop+368,
yycrank+413,	0,		0,	
yycrank+0,	0,		yyvstop+370,
yycrank+402,	0,		0,	
yycrank+0,	0,		yyvstop+372,
yycrank+417,	0,		0,	
yycrank+415,	0,		0,	
yycrank+0,	0,		yyvstop+374,
yycrank+403,	0,		0,	
yycrank+424,	0,		0,	
yycrank+0,	0,		yyvstop+376,
yycrank+410,	0,		0,	
yycrank+409,	0,		0,	
yycrank+425,	0,		0,	
yycrank+719,	0,		0,	
yycrank+421,	yysvec+198,	yyvstop+378,
yycrank+0,	0,		yyvstop+380,
yycrank+0,	0,		yyvstop+382,
yycrank+428,	yysvec+31,	yyvstop+384,
yycrank+413,	yysvec+31,	yyvstop+386,
yycrank+0,	yysvec+31,	yyvstop+388,
yycrank+0,	yysvec+31,	yyvstop+391,
yycrank+421,	yysvec+31,	yyvstop+394,
yycrank+424,	yysvec+31,	yyvstop+396,
yycrank+424,	yysvec+31,	yyvstop+398,
yycrank+417,	yysvec+31,	yyvstop+400,
yycrank+422,	yysvec+31,	yyvstop+402,
yycrank+0,	yysvec+31,	yyvstop+404,
yycrank+0,	yysvec+31,	yyvstop+407,
yycrank+424,	yysvec+31,	yyvstop+410,
yycrank+430,	yysvec+31,	yyvstop+412,
yycrank+463,	yysvec+31,	yyvstop+414,
yycrank+464,	yysvec+31,	yyvstop+416,
yycrank+443,	yysvec+31,	yyvstop+418,
yycrank+0,	yysvec+31,	yyvstop+420,
yycrank+461,	yysvec+31,	yyvstop+423,
yycrank+461,	yysvec+31,	yyvstop+425,
yycrank+458,	yysvec+31,	yyvstop+427,
yycrank+479,	yysvec+31,	yyvstop+429,
yycrank+486,	yysvec+31,	yyvstop+432,
yycrank+481,	yysvec+31,	yyvstop+434,
yycrank+494,	yysvec+31,	yyvstop+436,
yycrank+569,	yysvec+31,	yyvstop+438,
yycrank+640,	yysvec+31,	yyvstop+440,
yycrank+0,	yysvec+31,	yyvstop+442,
yycrank+566,	yysvec+31,	yyvstop+445,
yycrank+587,	yysvec+31,	yyvstop+447,
yycrank+0,	yysvec+31,	yyvstop+449,
yycrank+595,	yysvec+31,	yyvstop+452,
yycrank+602,	yysvec+31,	yyvstop+454,
yycrank+609,	yysvec+31,	yyvstop+456,
yycrank+0,	yysvec+31,	yyvstop+458,
yycrank+614,	yysvec+31,	yyvstop+461,
yycrank+604,	yysvec+31,	yyvstop+463,
yycrank+605,	yysvec+31,	yyvstop+465,
yycrank+621,	yysvec+31,	yyvstop+467,
yycrank+613,	yysvec+31,	yyvstop+469,
yycrank+0,	yysvec+31,	yyvstop+471,
yycrank+0,	yysvec+31,	yyvstop+474,
yycrank+0,	yysvec+31,	yyvstop+477,
yycrank+632,	yysvec+31,	yyvstop+480,
yycrank+618,	yysvec+31,	yyvstop+482,
yycrank+625,	yysvec+31,	yyvstop+484,
yycrank+632,	yysvec+31,	yyvstop+486,
yycrank+638,	yysvec+31,	yyvstop+489,
yycrank+638,	yysvec+31,	yyvstop+491,
yycrank+636,	yysvec+31,	yyvstop+493,
yycrank+628,	yysvec+31,	yyvstop+495,
yycrank+644,	yysvec+31,	yyvstop+497,
yycrank+745,	0,		yyvstop+499,
yycrank+0,	yysvec+31,	yyvstop+501,
yycrank+645,	yysvec+31,	yyvstop+504,
yycrank+632,	yysvec+31,	yyvstop+506,
yycrank+646,	yysvec+31,	yyvstop+508,
yycrank+652,	yysvec+31,	yyvstop+510,
yycrank+636,	yysvec+31,	yyvstop+512,
yycrank+641,	yysvec+31,	yyvstop+514,
yycrank+648,	yysvec+31,	yyvstop+516,
yycrank+668,	yysvec+31,	yyvstop+519,
yycrank+727,	yysvec+31,	yyvstop+521,
yycrank+659,	yysvec+31,	yyvstop+523,
yycrank+656,	yysvec+31,	yyvstop+525,
yycrank+0,	yysvec+31,	yyvstop+527,
yycrank+662,	yysvec+31,	yyvstop+530,
yycrank+665,	yysvec+31,	yyvstop+532,
yycrank+679,	yysvec+31,	yyvstop+535,
yycrank+-778,	yysvec+159,	yyvstop+537,
yycrank+-779,	yysvec+159,	yyvstop+539,
yycrank+-789,	0,		yyvstop+542,
yycrank+-791,	0,		yyvstop+545,
yycrank+-781,	yysvec+159,	yyvstop+548,
yycrank+-783,	yysvec+159,	yyvstop+550,
yycrank+-784,	yysvec+159,	yyvstop+552,
yycrank+-785,	yysvec+159,	yyvstop+554,
yycrank+-786,	yysvec+159,	yyvstop+556,
yycrank+-787,	yysvec+159,	yyvstop+558,
yycrank+-792,	yysvec+159,	yyvstop+561,
yycrank+-793,	yysvec+159,	yyvstop+563,
yycrank+-794,	yysvec+159,	yyvstop+566,
yycrank+-795,	yysvec+159,	yyvstop+568,
yycrank+-796,	yysvec+159,	yyvstop+571,
yycrank+-797,	yysvec+159,	yyvstop+573,
yycrank+-798,	yysvec+159,	yyvstop+575,
yycrank+-799,	yysvec+159,	yyvstop+578,
yycrank+-801,	yysvec+159,	yyvstop+580,
yycrank+-800,	yysvec+159,	yyvstop+582,
yycrank+-802,	yysvec+159,	yyvstop+585,
yycrank+-803,	yysvec+159,	yyvstop+587,
yycrank+-804,	yysvec+159,	yyvstop+589,
yycrank+713,	yysvec+31,	yyvstop+591,
yycrank+700,	0,		yyvstop+593,
yycrank+701,	0,		0,	
yycrank+703,	0,		0,	
yycrank+0,	0,		yyvstop+595,
yycrank+717,	0,		0,	
yycrank+708,	0,		0,	
yycrank+709,	0,		0,	
yycrank+722,	0,		yyvstop+597,
yycrank+724,	0,		0,	
yycrank+713,	0,		0,	
yycrank+716,	0,		0,	
yycrank+0,	0,		yyvstop+599,
yycrank+715,	0,		0,	
yycrank+716,	0,		yyvstop+601,
yycrank+0,	yysvec+31,	yyvstop+603,
yycrank+732,	yysvec+31,	yyvstop+606,
yycrank+715,	yysvec+31,	yyvstop+608,
yycrank+785,	yysvec+31,	yyvstop+610,
yycrank+717,	yysvec+31,	yyvstop+612,
yycrank+737,	yysvec+31,	yyvstop+614,
yycrank+729,	yysvec+31,	yyvstop+616,
yycrank+740,	yysvec+31,	yyvstop+618,
yycrank+0,	yysvec+31,	yyvstop+620,
yycrank+734,	yysvec+31,	yyvstop+623,
yycrank+736,	yysvec+31,	yyvstop+625,
yycrank+0,	yysvec+31,	yyvstop+627,
yycrank+743,	yysvec+31,	yyvstop+630,
yycrank+735,	yysvec+31,	yyvstop+633,
yycrank+745,	yysvec+31,	yyvstop+635,
yycrank+746,	yysvec+31,	yyvstop+638,
yycrank+0,	yysvec+31,	yyvstop+640,
yycrank+816,	yysvec+31,	yyvstop+643,
yycrank+737,	yysvec+31,	yyvstop+645,
yycrank+0,	yysvec+31,	yyvstop+647,
yycrank+818,	0,		0,	
yycrank+0,	yysvec+31,	yyvstop+650,
yycrank+735,	yysvec+31,	yyvstop+653,
yycrank+0,	yysvec+31,	yyvstop+655,
yycrank+748,	yysvec+31,	yyvstop+658,
yycrank+736,	yysvec+31,	yyvstop+660,
yycrank+740,	yysvec+31,	yyvstop+662,
yycrank+0,	yysvec+31,	yyvstop+664,
yycrank+825,	yysvec+31,	yyvstop+667,
yycrank+0,	yysvec+31,	yyvstop+670,
yycrank+743,	yysvec+31,	yyvstop+673,
yycrank+0,	yysvec+31,	yyvstop+675,
yycrank+757,	yysvec+31,	yyvstop+678,
yycrank+746,	yysvec+31,	yyvstop+680,
yycrank+746,	yysvec+31,	yyvstop+682,
yycrank+0,	yysvec+31,	yyvstop+684,
yycrank+748,	yysvec+31,	yyvstop+687,
yycrank+749,	yysvec+31,	yyvstop+689,
yycrank+750,	yysvec+31,	yyvstop+691,
yycrank+0,	yysvec+31,	yyvstop+693,
yycrank+0,	yysvec+31,	yyvstop+696,
yycrank+763,	yysvec+31,	yyvstop+699,
yycrank+758,	yysvec+31,	yyvstop+701,
yycrank+772,	yysvec+31,	yyvstop+703,
yycrank+760,	yysvec+31,	yyvstop+705,
yycrank+0,	yysvec+31,	yyvstop+707,
yycrank+755,	yysvec+31,	yyvstop+710,
yycrank+0,	yysvec+31,	yyvstop+712,
yycrank+755,	yysvec+31,	yyvstop+715,
yycrank+869,	yysvec+31,	yyvstop+717,
yycrank+841,	0,		0,	
yycrank+772,	yysvec+31,	yyvstop+719,
yycrank+767,	yysvec+31,	yyvstop+721,
yycrank+844,	yysvec+31,	yyvstop+723,
yycrank+773,	yysvec+31,	yyvstop+725,
yycrank+0,	yysvec+31,	yyvstop+727,
yycrank+-869,	yysvec+159,	yyvstop+730,
yycrank+-871,	yysvec+159,	yyvstop+732,
yycrank+-870,	yysvec+159,	yyvstop+735,
yycrank+-872,	yysvec+159,	yyvstop+738,
yycrank+-873,	yysvec+159,	yyvstop+740,
yycrank+-874,	yysvec+159,	yyvstop+742,
yycrank+-876,	yysvec+159,	yyvstop+745,
yycrank+-877,	yysvec+159,	yyvstop+747,
yycrank+-878,	yysvec+159,	yyvstop+749,
yycrank+-879,	yysvec+159,	yyvstop+751,
yycrank+-892,	yysvec+159,	yyvstop+754,
yycrank+-882,	yysvec+159,	yyvstop+756,
yycrank+-885,	yysvec+159,	yyvstop+758,
yycrank+-880,	yysvec+159,	yyvstop+760,
yycrank+-893,	yysvec+159,	yyvstop+763,
yycrank+-895,	yysvec+159,	yyvstop+765,
yycrank+795,	yysvec+31,	yyvstop+768,
yycrank+796,	0,		0,	
yycrank+808,	0,		0,	
yycrank+0,	0,		yyvstop+770,
yycrank+806,	0,		0,	
yycrank+0,	0,		yyvstop+772,
yycrank+807,	0,		0,	
yycrank+795,	0,		0,	
yycrank+797,	0,		0,	
yycrank+811,	0,		0,	
yycrank+804,	0,		0,	
yycrank+0,	0,		yyvstop+774,
yycrank+817,	0,		0,	
yycrank+0,	yysvec+31,	yyvstop+776,
yycrank+0,	yysvec+31,	yyvstop+779,
yycrank+0,	yysvec+31,	yyvstop+782,
yycrank+0,	yysvec+31,	yyvstop+785,
yycrank+821,	yysvec+31,	yyvstop+788,
yycrank+814,	yysvec+31,	yyvstop+790,
yycrank+810,	yysvec+31,	yyvstop+792,
yycrank+824,	yysvec+31,	yyvstop+794,
yycrank+807,	yysvec+31,	yyvstop+796,
yycrank+827,	yysvec+31,	yyvstop+798,
yycrank+827,	yysvec+31,	yyvstop+800,
yycrank+814,	yysvec+31,	yyvstop+802,
yycrank+831,	yysvec+31,	yyvstop+804,
yycrank+901,	0,		0,	
yycrank+817,	yysvec+31,	yyvstop+806,
yycrank+832,	0,		0,	
yycrank+0,	yysvec+31,	yyvstop+808,
yycrank+819,	yysvec+31,	yyvstop+811,
yycrank+836,	yysvec+31,	yyvstop+813,
yycrank+832,	yysvec+31,	yyvstop+815,
yycrank+906,	0,		0,	
yycrank+0,	yysvec+31,	yyvstop+818,
yycrank+907,	yysvec+31,	yyvstop+821,
yycrank+0,	yysvec+31,	yyvstop+823,
yycrank+825,	yysvec+31,	yyvstop+826,
yycrank+0,	yysvec+31,	yyvstop+828,
yycrank+909,	yysvec+31,	yyvstop+831,
yycrank+0,	yysvec+31,	yyvstop+834,
yycrank+910,	yysvec+31,	yyvstop+837,
yycrank+842,	yysvec+31,	yyvstop+839,
yycrank+844,	yysvec+31,	yyvstop+841,
yycrank+829,	yysvec+31,	yyvstop+843,
yycrank+914,	yysvec+31,	yyvstop+845,
yycrank+844,	yysvec+31,	yyvstop+847,
yycrank+939,	0,		yyvstop+849,
yycrank+847,	0,		0,	
yycrank+941,	yysvec+31,	yyvstop+851,
yycrank+0,	yysvec+31,	yyvstop+853,
yycrank+919,	0,		0,	
yycrank+0,	yysvec+31,	yyvstop+856,
yycrank+-943,	yysvec+159,	yyvstop+859,
yycrank+-944,	yysvec+159,	yyvstop+861,
yycrank+-945,	yysvec+159,	yyvstop+863,
yycrank+-946,	yysvec+159,	yyvstop+866,
yycrank+-947,	yysvec+159,	yyvstop+868,
yycrank+-948,	yysvec+159,	yyvstop+871,
yycrank+-949,	yysvec+159,	yyvstop+873,
yycrank+-951,	yysvec+159,	yyvstop+875,
yycrank+-952,	yysvec+159,	yyvstop+877,
yycrank+-953,	yysvec+159,	yyvstop+879,
yycrank+-950,	yysvec+159,	yyvstop+881,
yycrank+-954,	yysvec+159,	yyvstop+884,
yycrank+851,	yysvec+31,	yyvstop+886,
yycrank+857,	0,		0,	
yycrank+853,	0,		0,	
yycrank+852,	0,		0,	
yycrank+0,	0,		yyvstop+888,
yycrank+854,	0,		0,	
yycrank+0,	0,		yyvstop+890,
yycrank+0,	0,		yyvstop+892,
yycrank+0,	0,		yyvstop+894,
yycrank+0,	0,		yyvstop+896,
yycrank+860,	yysvec+31,	yyvstop+898,
yycrank+940,	yysvec+31,	yyvstop+900,
yycrank+942,	yysvec+31,	yyvstop+902,
yycrank+0,	yysvec+31,	yyvstop+905,
yycrank+870,	yysvec+31,	yyvstop+908,
yycrank+0,	yysvec+31,	yyvstop+910,
yycrank+968,	yysvec+31,	yyvstop+913,
yycrank+877,	yysvec+31,	yyvstop+915,
yycrank+0,	yysvec+31,	yyvstop+917,
yycrank+878,	0,		0,	
yycrank+880,	yysvec+31,	yyvstop+920,
yycrank+0,	0,		yyvstop+922,
yycrank+881,	yysvec+31,	yyvstop+924,
yycrank+885,	yysvec+31,	yyvstop+926,
yycrank+883,	0,		0,	
yycrank+959,	0,		0,	
yycrank+0,	yysvec+31,	yyvstop+928,
yycrank+960,	0,		0,	
yycrank+963,	0,		0,	
yycrank+0,	yysvec+31,	yyvstop+931,
yycrank+0,	yysvec+31,	yyvstop+934,
yycrank+885,	yysvec+31,	yyvstop+937,
yycrank+965,	0,		0,	
yycrank+886,	yysvec+31,	yyvstop+939,
yycrank+0,	0,		yyvstop+941,
yycrank+1012,	0,		0,	
yycrank+891,	yysvec+31,	yyvstop+943,
yycrank+900,	0,		0,	
yycrank+-994,	yysvec+159,	yyvstop+945,
yycrank+-1021,	yysvec+159,	yyvstop+947,
yycrank+-1022,	yysvec+159,	yyvstop+949,
yycrank+-993,	yysvec+159,	yyvstop+951,
yycrank+-1024,	yysvec+159,	yyvstop+954,
yycrank+-995,	yysvec+159,	yyvstop+956,
yycrank+-996,	yysvec+159,	yyvstop+959,
yycrank+-997,	yysvec+159,	yyvstop+962,
yycrank+-998,	yysvec+159,	yyvstop+965,
yycrank+1000,	yysvec+31,	yyvstop+968,
yycrank+0,	0,		yyvstop+970,
yycrank+0,	0,		yyvstop+972,
yycrank+0,	0,		yyvstop+974,
yycrank+0,	yysvec+31,	yyvstop+976,
yycrank+993,	0,		0,	
yycrank+994,	0,		0,	
yycrank+898,	yysvec+31,	yyvstop+979,
yycrank+1005,	0,		yyvstop+981,
yycrank+901,	yysvec+31,	yyvstop+983,
yycrank+0,	0,		yyvstop+985,
yycrank+0,	yysvec+31,	yyvstop+987,
yycrank+908,	yysvec+31,	yyvstop+990,
yycrank+0,	0,		yyvstop+992,
yycrank+916,	0,		0,	
yycrank+917,	0,		0,	
yycrank+918,	0,		0,	
yycrank+0,	yysvec+31,	yyvstop+994,
yycrank+920,	0,		0,	
yycrank+1092,	0,		yyvstop+997,
yycrank+922,	yysvec+31,	yyvstop+999,
yycrank+0,	0,		yyvstop+1001,
yycrank+-1014,	yysvec+159,	yyvstop+1003,
yycrank+-1017,	yysvec+159,	yyvstop+1006,
yycrank+-1018,	yysvec+159,	yyvstop+1009,
yycrank+0,	0,		yyvstop+1012,
yycrank+927,	0,		0,	
yycrank+931,	0,		0,	
yycrank+934,	yysvec+31,	yyvstop+1014,
yycrank+0,	yysvec+31,	yyvstop+1016,
yycrank+935,	yysvec+31,	yyvstop+1019,
yycrank+0,	0,		yyvstop+1021,
yycrank+0,	0,		yyvstop+1023,
yycrank+0,	0,		yyvstop+1025,
yycrank+0,	0,		yyvstop+1027,
yycrank+1029,	yysvec+31,	yyvstop+1029,
yycrank+0,	0,		yyvstop+1031,
yycrank+0,	0,		yyvstop+1033,
yycrank+0,	yysvec+31,	yyvstop+1035,
yycrank+0,	yysvec+31,	yyvstop+1038,
0,	0,	0};
struct yywork *yytop = yycrank+1214;
struct yysvf *yybgin = yysvec+1;
char yymatch[] ={
00  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,011 ,012 ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
011 ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
'0' ,'0' ,'0' ,'0' ,'0' ,'0' ,'0' ,'0' ,
'0' ,'0' ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,'A' ,'A' ,'A' ,'A' ,'E' ,'E' ,'A' ,
'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,
'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,
'A' ,'A' ,'A' ,01  ,01  ,01  ,01  ,'A' ,
01  ,'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,
'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,
'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,
'A' ,'A' ,'A' ,01  ,01  ,01  ,01  ,01  ,
0};
char yyextra[] ={
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0};
/*	ncform	4.1	83/08/11	*/

int yylineno =1;
# define YYU(x) x
# define NLSTATE yyprevious=YYNEWLINE
char yytext[YYLMAX];
struct yysvf *yylstate [YYLMAX], **yylsp, **yyolsp;
char yysbuf[YYLMAX];
char *yysptr = yysbuf;
int *yyfnd;
extern struct yysvf *yyestate;
int yyprevious = YYNEWLINE;
yylook(){
	register struct yysvf *yystate, **lsp;
	register struct yywork *yyt;
	struct yysvf *yyz;
	int yych;
	struct yywork *yyr;
# ifdef LEXDEBUG
	int debug;
# endif
	char *yylastch;
	/* start off machines */
# ifdef LEXDEBUG
	debug = 0;
# endif
	if (!yymorfg)
		yylastch = yytext;
	else {
		yymorfg=0;
		yylastch = yytext+yyleng;
		}
	for(;;){
		lsp = yylstate;
		yyestate = yystate = yybgin;
		if (yyprevious==YYNEWLINE) yystate++;
		for (;;){
# ifdef LEXDEBUG
			if(debug)fprintf(yyout,"state %d\n",yystate-yysvec-1);
# endif
			yyt = yystate->yystoff;
			if(yyt == yycrank){		/* may not be any transitions */
				yyz = yystate->yyother;
				if(yyz == 0)break;
				if(yyz->yystoff == yycrank)break;
				}
			*yylastch++ = yych = input();
		tryagain:
# ifdef LEXDEBUG
			if(debug){
				fprintf(yyout,"char ");
				allprint(yych);
				putchar('\n');
				}
# endif
			yyr = yyt;
			if ( (int)yyt > (int)yycrank){
				yyt = yyr + yych;
				if (yyt <= yytop && yyt->verify+yysvec == yystate){
					if(yyt->advance+yysvec == YYLERR)	/* error transitions */
						{unput(*--yylastch);break;}
					*lsp++ = yystate = yyt->advance+yysvec;
					goto contin;
					}
				}
# ifdef YYOPTIM
			else if((int)yyt < (int)yycrank) {		/* r < yycrank */
				yyt = yyr = yycrank+(yycrank-yyt);
# ifdef LEXDEBUG
				if(debug)fprintf(yyout,"compressed state\n");
# endif
				yyt = yyt + yych;
				if(yyt <= yytop && yyt->verify+yysvec == yystate){
					if(yyt->advance+yysvec == YYLERR)	/* error transitions */
						{unput(*--yylastch);break;}
					*lsp++ = yystate = yyt->advance+yysvec;
					goto contin;
					}
				yyt = yyr + YYU(yymatch[yych]);
# ifdef LEXDEBUG
				if(debug){
					fprintf(yyout,"try fall back character ");
					allprint(YYU(yymatch[yych]));
					putchar('\n');
					}
# endif
				if(yyt <= yytop && yyt->verify+yysvec == yystate){
					if(yyt->advance+yysvec == YYLERR)	/* error transition */
						{unput(*--yylastch);break;}
					*lsp++ = yystate = yyt->advance+yysvec;
					goto contin;
					}
				}
			if ((yystate = yystate->yyother) && (yyt= yystate->yystoff) != yycrank){
# ifdef LEXDEBUG
				if(debug)fprintf(yyout,"fall back to state %d\n",yystate-yysvec-1);
# endif
				goto tryagain;
				}
# endif
			else
				{unput(*--yylastch);break;}
		contin:
# ifdef LEXDEBUG
			if(debug){
				fprintf(yyout,"state %d char ",yystate-yysvec-1);
				allprint(yych);
				putchar('\n');
				}
# endif
			;
			}
# ifdef LEXDEBUG
		if(debug){
			fprintf(yyout,"stopped at %d with ",*(lsp-1)-yysvec-1);
			allprint(yych);
			putchar('\n');
			}
# endif
		while (lsp-- > yylstate){
			*yylastch-- = 0;
			if (*lsp != 0 && (yyfnd= (*lsp)->yystops) && *yyfnd > 0){
				yyolsp = lsp;
				if(yyextra[*yyfnd]){		/* must backup */
					while(yyback((*lsp)->yystops,-*yyfnd) != 1 && lsp > yylstate){
						lsp--;
						unput(*yylastch--);
						}
					}
				yyprevious = YYU(*yylastch);
				yylsp = lsp;
				yyleng = yylastch-yytext+1;
				yytext[yyleng] = 0;
# ifdef LEXDEBUG
				if(debug){
					fprintf(yyout,"\nmatch ");
					sprint(yytext);
					fprintf(yyout," action %d\n",*yyfnd);
					}
# endif
				return(*yyfnd++);
				}
			unput(*yylastch);
			}
		if (yytext[0] == 0  /* && feof(yyin) */)
			{
			yysptr=yysbuf;
			return(0);
			}
		yyprevious = yytext[0] = input();
		if (yyprevious>0)
			output(yyprevious);
		yylastch=yytext;
# ifdef LEXDEBUG
		if(debug)putchar('\n');
# endif
		}
	}
yyback(p, m)
	int *p;
{
if (p==0) return(0);
while (*p)
	{
	if (*p++ == m)
		return(1);
	}
return(0);
}
	/* the following are only used in the lex library */
yyinput(){
	return(input());
	}
yyoutput(c)
  int c; {
	output(c);
	}
yyunput(c)
   int c; {
	unput(c);
	}
