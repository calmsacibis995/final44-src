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
# define comment 6
# define def 8
# define sc 10
# define br 12
#undef	input
#undef	unput
#include <stdio.h>
#include <ctype.h>
#include "pic.h"
#include "y.tab.h"

extern	float	atof();
extern	struct	symtab	symtab[];
extern	char	*filename;
extern	int	synerr;

#define	CADD	cbuf[clen++]=yytext[0]; if(clen>=CBUFLEN-1) {yyerror("string too long", cbuf); BEGIN A;}
#define	CBUFLEN	150
char	cbuf[CBUFLEN];
int	clen, cflag;
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
{ if (yytext[1] == 'P' && (yytext[2] == 'E' || yytext[2] == 'F')) {
			yylval.i = yytext[2];
			return(EOF);
		  } else {
			yylval.p = tostring(yytext);
			return(TROFF);
		  }
		}
break;
case 8:
return(yylval.i = PRINT);
break;
case 9:
	return(yylval.i = BOX);
break;
case 10:
return(yylval.i = CIRCLE);
break;
case 11:
	return(yylval.i = ARC);
break;
case 12:
return(yylval.i = ELLIPSE);
break;
case 13:
return(yylval.i = ARROW);
break;
case 14:
return(yylval.i = SPLINE);
break;
case 15:
	return(yylval.i = LINE);
break;
case 16:
	return(yylval.i = MOVE);
break;
case 17:
	return(yylval.i = BLOCK);
break;
case 18:
	return(SAME);
break;
case 19:
return(BETWEEN);
break;
case 20:
	return(AND);
break;
case 21:
	;
break;
case 22:
	;
break;
case 23:
	;
break;
case 24:
	{ yylval.i = EAST; return(CORNER); }
break;
case 25:
{ yylval.i = EAST; return(CORNER); }
break;
case 26:
	{ yylval.i = EAST; return(CORNER); }
break;
case 27:
{ yylval.i = EAST; return(CORNER); }
break;
case 28:
	{ yylval.i = WEST; return(CORNER); }
break;
case 29:
{ yylval.i = WEST; return(CORNER); }
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
	{ yylval.i = NORTH; return(CORNER); }
break;
case 35:
{ yylval.i = NORTH; return(CORNER); }
break;
case 36:
	{ yylval.i = SOUTH; return(CORNER); }
break;
case 37:
{ yylval.i = SOUTH; return(CORNER); }
break;
case 38:
	{ yylval.i = SOUTH; return(CORNER); }
break;
case 39:
{ yylval.i = SOUTH; return(CORNER); }
break;
case 40:
{ yylval.i = SOUTH; return(CORNER); }
break;
case 41:
	{ yylval.i = CENTER; return(CORNER); }
break;
case 42:
{ yylval.i = CENTER; return(CORNER); }
break;
case 43:
{ yylval.i = START; return(CORNER); }
break;
case 44:
{ yylval.i = END; return(CORNER); }
break;
case 45:
	{ yylval.i = NE; return(CORNER); }
break;
case 46:
{ yylval.i = NE; return(CORNER); }
break;
case 47:
	{ yylval.i = SE; return(CORNER); }
break;
case 48:
{ yylval.i = SE; return(CORNER); }
break;
case 49:
	{ yylval.i = NW; return(CORNER); }
break;
case 50:
{ yylval.i = NW; return(CORNER); }
break;
case 51:
	{ yylval.i = SW; return(CORNER); }
break;
case 52:
{ yylval.i = SW; return(CORNER); }
break;
case 53:
	{ yylval.i = NORTH; return(CORNER); }
break;
case 54:
	{ yylval.i = NORTH; return(CORNER); }
break;
case 55:
	{ yylval.i = SOUTH; return(CORNER); }
break;
case 56:
	{ yylval.i = SOUTH; return(CORNER); }
break;
case 57:
	{ yylval.i = WEST; return(CORNER); }
break;
case 58:
	{ yylval.i = WEST; return(CORNER); }
break;
case 59:
	{ yylval.i = EAST; return(CORNER); }
break;
case 60:
	{ yylval.i = EAST; return(CORNER); }
break;
case 61:
	{ yylval.i = CENTER; return(CORNER); }
break;
case 62:
	{ yylval.i = START; return(CORNER); }
break;
case 63:
	{ yylval.i = END; return(CORNER); }
break;
case 64:
{ yylval.i = NE; return(CORNER); }
break;
case 65:
{ yylval.i = NW; return(CORNER); }
break;
case 66:
{ yylval.i = SE; return(CORNER); }
break;
case 67:
{ yylval.i = SW; return(CORNER); }
break;
case 68:
{ yylval.i = HEIGHT; return(ATTR); }
break;
case 69:
	{ yylval.i = HEIGHT; return(ATTR); }
break;
case 70:
	{ yylval.i = WIDTH; return(ATTR); }
break;
case 71:
{ yylval.i = WIDTH; return(ATTR); }
break;
case 72:
	{ yylval.i = RADIUS; return(ATTR); }
break;
case 73:
{ yylval.i = RADIUS; return(ATTR); }
break;
case 74:
	{ yylval.i = DIAMETER; return(ATTR); }
break;
case 75:
{ yylval.i = DIAMETER; return(ATTR); }
break;
case 76:
	{ yylval.i = SIZE; return(ATTR); }
break;
case 77:
	{ yylval.i = LEFT; return(DIR); }
break;
case 78:
{ yylval.i = RIGHT; return(DIR); }
break;
case 79:
	{ yylval.i = UP; return(DIR); }
break;
case 80:
	{ yylval.i = DOWN; return(DIR); }
break;
case 81:
	{ yylval.i = CW; return(ATTR); }
break;
case 82:
{ yylval.i = CW; return(ATTR); }
break;
case 83:
	{ yylval.i = CCW; return(ATTR); }
break;
case 84:
	{ yylval.i = THEN; return(ATTR); }
break;
case 85:
{ yylval.i = INVIS; return(ATTR); }
break;
case 86:
{ yylval.i = INVIS; return(ATTR); }
break;
case 87:
	return(yylval.i = DOT);
break;
case 88:
return(yylval.i = DOT);
break;
case 89:
	return(yylval.i = DASH);
break;
case 90:
return(yylval.i = DASH);
break;
case 91:
	return(yylval.i = CHOP);
break;
case 92:
return(yylval.i = SPREAD);
break;
case 93:
	return(yylval.i = FILL);
break;
case 94:
return(yylval.i = LJUST);
break;
case 95:
return(yylval.i = RJUST);
break;
case 96:
return(yylval.i = ABOVE);
break;
case 97:
return(yylval.i = BELOW);
break;
case 98:
	{ yylval.i = HEAD1; return(HEAD); }
break;
case 99:
	{ yylval.i = HEAD2; return(HEAD); }
break;
case 100:
{ yylval.i = HEAD12; return(HEAD); }
break;
case 101:
	return(yylval.i = DOTX);
break;
case 102:
	return(yylval.i = DOTY);
break;
case 103:
return(yylval.i = DOTHT);
break;
case 104:
return(yylval.i = DOTHT);
break;
case 105:
return(yylval.i = DOTWID);
break;
case 106:
return(yylval.i = DOTWID);
break;
case 107:
return(yylval.i = DOTRAD);
break;
case 108:
return(yylval.i = DOTRAD);
break;
case 109:
	return(yylval.i = FROM);
break;
case 110:
	return(yylval.i = TO);
break;
case 111:
	return(yylval.i = AT);
break;
case 112:
	return(yylval.i = BY);
break;
case 113:
	return(yylval.i = WITH);
break;
case 114:
	return(yylval.i = LAST);
break;
case 115:
	return(yylval.i = HERE);
break;
case 116:
{ BEGIN def; }
break;
case 117:
{ definition(yytext); BEGIN A; }
break;
case 118:
	{ yylval.i = 1; return(NTH); }
break;
case 119:
{ yylval.i = atoi(yytext); return(NTH); }
break;
case 120:
{ yylval.f = atof(yytext); return(NUMBER); }
break;
case 121:
{
		int c;
		struct symtab *p;
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
case 122:
	{ BEGIN str; clen=0; }
break;
case 123:
	{ BEGIN comment; }
break;
case 124:
{ BEGIN A; return(ST); }
break;
case 125:
;
break;
case 126:
	{ yylval.i = yytext[0]; return(yytext[0]); }
break;
case 127:
	{ BEGIN A; cbuf[clen]=0; yylval.p = tostring(cbuf); return(TEXT); }
break;
case 128:
	{ yyerror("newline in string"); BEGIN A; return(ST); }
break;
case 129:
{ cbuf[clen++]='"'; }
break;
case 130:
{ cbuf[clen++]='\t'; }
break;
case 131:
{ cbuf[clen++]='\\'; }
break;
case 132:
	{ CADD; }
break;
case -1:
break;
default:
fprintf(yyout,"bad switch yylook %d",nstr);
} return(0); }
/* end of yylex */
int yyvstop[] ={
0,

126,
0,

1,
126,
0,

3,
0,

122,
126,
0,

123,
126,
0,

126,
0,

126,
0,

120,
126,
0,

4,
126,
0,

126,
0,

121,
126,
0,

121,
126,
0,

126,
0,

126,
0,

6,
126,
0,

121,
126,
0,

121,
126,
0,

121,
126,
0,

121,
126,
0,

121,
126,
0,

121,
126,
0,

121,
126,
0,

121,
126,
0,

121,
126,
0,

121,
126,
0,

121,
126,
0,

121,
126,
0,

121,
126,
0,

121,
126,
0,

121,
126,
0,

121,
126,
0,

121,
126,
0,

121,
126,
0,

5,
126,
0,

7,
126,
0,

132,
0,

128,
0,

127,
132,
0,

132,
0,

125,
0,

124,
0,

117,
0,

99,
0,

120,
0,

38,
0,

41,
0,

24,
0,

30,
0,

32,
0,

26,
0,

36,
0,

34,
0,

28,
0,

101,
0,

102,
0,

120,
0,

120,
0,

120,
0,

98,
0,

121,
0,

121,
0,

17,
0,

2,
0,

121,
0,

121,
0,

121,
0,

111,
121,
0,

121,
0,

121,
0,

112,
121,
0,

121,
0,

121,
0,

121,
0,

121,
0,

121,
0,

81,
121,
0,

121,
0,

121,
0,

121,
0,

121,
0,

121,
0,

121,
0,

121,
0,

121,
0,

121,
0,

121,
0,

69,
121,
0,

121,
0,

121,
0,

121,
0,

121,
0,

121,
0,

121,
0,

121,
0,

121,
0,

21,
121,
0,

121,
0,

121,
0,

121,
0,

121,
0,

121,
0,

121,
0,

121,
0,

121,
0,

121,
0,

121,
0,

110,
121,
0,

79,
121,
0,

121,
0,

121,
0,

121,
0,

7,
0,

7,
120,
0,

7,
38,
0,

7,
41,
0,

7,
24,
0,

7,
0,

7,
30,
0,

7,
32,
0,

7,
26,
0,

7,
36,
0,

7,
34,
0,

7,
0,

7,
28,
0,

7,
101,
0,

7,
102,
0,

129,
0,

131,
0,

130,
0,

103,
0,

45,
0,

49,
0,

47,
0,

51,
0,

119,
0,

100,
0,

121,
0,

121,
0,

20,
121,
0,

11,
121,
0,

121,
0,

121,
0,

121,
0,

121,
0,

9,
121,
0,

83,
121,
0,

121,
0,

121,
0,

121,
0,

121,
0,

121,
0,

121,
0,

121,
0,

87,
121,
0,

121,
0,

121,
0,

121,
0,

121,
0,

121,
0,

121,
0,

121,
0,

121,
0,

121,
0,

121,
0,

121,
0,

121,
0,

121,
0,

121,
0,

121,
0,

121,
0,

121,
0,

72,
121,
0,

121,
0,

121,
0,

121,
0,

121,
0,

121,
0,

121,
0,

121,
0,

121,
0,

22,
121,
0,

121,
0,

121,
0,

23,
121,
0,

121,
0,

70,
121,
0,

121,
0,

7,
120,
0,

7,
0,

7,
0,

7,
0,

7,
0,

7,
0,

7,
103,
0,

7,
0,

7,
0,

7,
45,
0,

7,
0,

7,
49,
0,

7,
0,

7,
0,

7,
47,
0,

7,
0,

7,
0,

7,
51,
0,

7,
0,

7,
0,

7,
0,

7,
0,

39,
0,

44,
0,

107,
0,

35,
0,

105,
0,

115,
121,
0,

121,
0,

121,
0,

121,
0,

121,
0,

121,
0,

121,
0,

91,
121,
0,

121,
0,

121,
0,

89,
121,
0,

121,
0,

74,
121,
0,

121,
0,

80,
121,
0,

121,
0,

121,
0,

93,
121,
0,

121,
0,

109,
121,
0,

121,
0,

121,
0,

114,
121,
0,

77,
121,
0,

15,
121,
0,

121,
0,

121,
0,

16,
121,
0,

121,
0,

121,
0,

121,
0,

121,
0,

121,
0,

18,
121,
0,

76,
121,
0,

121,
0,

121,
0,

121,
0,

121,
0,

84,
121,
0,

121,
0,

121,
0,

121,
0,

113,
121,
0,

7,
39,
0,

7,
0,

7,
0,

7,
44,
0,

7,
0,

7,
0,

7,
0,

7,
0,

7,
107,
0,

7,
0,

7,
0,

7,
0,

7,
35,
0,

7,
0,

7,
0,

7,
105,
0,

25,
0,

31,
0,

29,
0,

96,
121,
0,

13,
121,
0,

97,
121,
0,

121,
0,

121,
0,

121,
0,

121,
0,

121,
0,

121,
0,

121,
0,

121,
0,

121,
0,

121,
0,

118,
121,
0,

121,
0,

85,
121,
0,

94,
121,
0,

121,
0,

121,
0,

8,
121,
0,

121,
0,

78,
121,
0,

95,
121,
0,

121,
0,

121,
0,

121,
0,

121,
0,

121,
0,

71,
121,
0,

7,
0,

7,
0,

7,
25,
0,

7,
0,

7,
31,
0,

7,
0,

7,
0,

7,
0,

7,
0,

7,
0,

7,
0,

7,
0,

7,
29,
0,

7,
0,

33,
0,

27,
0,

37,
0,

43,
0,

106,
0,

121,
0,

121,
0,

121,
0,

10,
121,
0,

121,
0,

90,
121,
0,

121,
0,

121,
0,

88,
121,
0,

121,
0,

63,
0,

68,
121,
0,

121,
0,

73,
121,
0,

14,
121,
0,

92,
121,
0,

53,
0,

7,
0,

7,
0,

7,
0,

7,
0,

7,
33,
0,

7,
0,

7,
27,
0,

7,
37,
0,

7,
43,
0,

7,
0,

7,
106,
0,

40,
0,

42,
0,

104,
0,

108,
0,

19,
121,
0,

121,
0,

116,
0,

121,
0,

60,
0,

12,
121,
0,

121,
0,

57,
0,

58,
0,

7,
40,
0,

7,
42,
0,

7,
104,
0,

7,
0,

7,
0,

7,
108,
0,

7,
0,

7,
0,

121,
0,

75,
121,
0,

121,
0,

54,
0,

59,
0,

56,
0,

62,
0,

7,
0,

7,
0,

7,
0,

7,
0,

55,
0,

61,
0,

82,
121,
0,

86,
121,
0,

7,
0,

7,
0,

7,
0,

7,
0,

52,
0,

50,
0,

7,
52,
0,

7,
0,

7,
50,
0,

7,
0,

48,
0,

46,
0,

7,
48,
0,

7,
46,
0,

67,
0,

65,
0,

66,
0,

64,
0,
0};
# define YYTYPE int
struct yywork { YYTYPE verify, advance; } yycrank[] ={
0,0,	0,0,	3,15,	0,0,	
7,54,	0,0,	0,0,	0,0,	
0,0,	0,0,	3,16,	3,17,	
7,54,	7,55,	28,83,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	3,18,	
3,19,	0,0,	0,0,	6,52,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	3,20,	3,21,	
24,79,	3,22,	0,0,	7,54,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
3,23,	3,24,	0,0,	0,0,	
0,0,	20,57,	3,25,	0,0,	
7,54,	0,0,	4,18,	4,19,	
0,0,	3,26,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	4,20,	4,49,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
3,27,	3,28,	3,29,	4,23,	
4,24,	6,53,	3,30,	3,31,	
3,32,	3,33,	3,34,	3,35,	
26,81,	3,36,	3,37,	27,82,	
4,26,	3,38,	3,39,	3,40,	
3,41,	3,42,	0,0,	3,43,	
3,44,	3,45,	3,46,	0,0,	
3,47,	35,104,	0,0,	5,50,	
0,0,	0,0,	3,48,	4,27,	
4,28,	4,29,	35,105,	5,50,	
5,51,	4,30,	4,31,	4,32,	
4,33,	4,34,	4,35,	31,88,	
4,36,	4,37,	30,84,	37,108,	
4,38,	4,39,	4,40,	4,41,	
4,42,	31,89,	4,43,	4,44,	
4,45,	4,46,	30,85,	4,47,	
5,52,	36,106,	30,86,	31,90,	
30,87,	4,48,	32,91,	34,101,	
32,92,	33,97,	39,114,	32,93,	
32,94,	33,98,	5,50,	32,95,	
36,107,	33,99,	34,102,	40,115,	
34,103,	41,116,	42,117,	33,100,	
46,128,	59,150,	32,96,	60,151,	
67,167,	68,168,	75,171,	5,50,	
9,56,	9,56,	9,56,	9,56,	
9,56,	9,56,	9,56,	9,56,	
9,56,	9,56,	9,56,	9,56,	
9,56,	9,56,	9,56,	9,56,	
9,56,	9,56,	9,56,	9,56,	
9,56,	9,56,	9,56,	9,56,	
9,56,	9,56,	5,53,	69,169,	
77,171,	78,171,	9,56,	69,170,	
9,56,	9,56,	9,56,	9,56,	
9,56,	9,56,	9,56,	9,56,	
9,56,	9,56,	9,56,	9,56,	
9,56,	9,56,	9,56,	9,56,	
9,56,	9,56,	9,56,	9,56,	
9,56,	9,56,	9,56,	9,56,	
9,56,	9,56,	21,58,	21,58,	
21,58,	21,58,	21,58,	21,58,	
21,58,	21,58,	21,58,	21,58,	
79,172,	22,72,	81,173,	22,73,	
22,73,	22,73,	22,73,	22,73,	
22,73,	22,73,	22,73,	22,73,	
22,73,	38,109,	84,174,	43,118,	
61,152,	38,110,	44,121,	85,175,	
91,182,	38,111,	38,112,	43,119,	
43,120,	92,183,	44,122,	38,113,	
45,126,	61,153,	47,129,	93,184,	
44,123,	44,124,	47,130,	45,127,	
62,154,	44,125,	47,131,	63,156,	
21,59,	21,60,	94,185,	21,61,	
89,180,	65,161,	21,62,	88,178,	
89,181,	63,157,	21,63,	62,155,	
21,64,	65,162,	95,186,	88,179,	
21,65,	21,66,	21,67,	21,68,	
22,74,	21,69,	21,70,	21,71,	
97,187,	22,75,	98,188,	86,176,	
99,189,	22,76,	22,77,	22,78,	
25,80,	25,80,	25,80,	25,80,	
25,80,	25,80,	25,80,	25,80,	
25,80,	25,80,	86,177,	100,190,	
101,192,	102,193,	100,191,	103,194,	
105,197,	25,80,	25,80,	25,80,	
25,80,	25,80,	25,80,	25,80,	
25,80,	25,80,	25,80,	25,80,	
25,80,	25,80,	25,80,	25,80,	
25,80,	25,80,	25,80,	25,80,	
25,80,	25,80,	25,80,	25,80,	
25,80,	25,80,	25,80,	53,147,	
106,198,	108,199,	109,200,	25,80,	
110,201,	25,80,	25,80,	25,80,	
25,80,	25,80,	25,80,	25,80,	
25,80,	25,80,	25,80,	25,80,	
25,80,	25,80,	25,80,	25,80,	
25,80,	25,80,	25,80,	25,80,	
25,80,	25,80,	25,80,	25,80,	
25,80,	25,80,	25,80,	49,132,	
104,195,	111,202,	112,203,	113,204,	
114,205,	115,206,	104,196,	49,132,	
49,0,	56,56,	56,56,	56,56,	
56,56,	56,56,	56,56,	56,56,	
56,56,	56,56,	56,56,	117,207,	
118,208,	119,209,	120,210,	121,211,	
122,212,	53,148,	58,58,	58,58,	
58,58,	58,58,	58,58,	58,58,	
58,58,	58,58,	58,58,	58,58,	
123,213,	64,158,	66,163,	124,214,	
125,216,	126,217,	127,218,	128,219,	
129,220,	124,215,	49,133,	64,159,	
66,164,	53,149,	130,221,	133,0,	
134,0,	66,165,	135,0,	64,160,	
66,166,	136,0,	131,222,	137,0,	
138,0,	139,0,	142,0,	49,132,	
72,72,	72,72,	72,72,	72,72,	
72,72,	72,72,	72,72,	72,72,	
72,72,	72,72,	131,223,	143,0,	
132,132,	140,0,	141,132,	145,0,	
144,0,	146,0,	150,246,	58,74,	
132,132,	132,0,	141,132,	141,0,	
151,247,	133,133,	152,248,	153,249,	
154,250,	156,251,	157,252,	159,253,	
49,134,	49,135,	161,254,	49,136,	
162,255,	164,256,	49,137,	165,257,	
167,258,	168,259,	49,138,	169,260,	
49,139,	170,261,	173,262,	174,263,	
49,140,	49,141,	49,142,	49,143,	
177,264,	49,144,	49,145,	49,146,	
178,265,	179,266,	180,267,	132,132,	
183,268,	141,132,	184,269,	185,270,	
186,271,	187,272,	188,273,	189,274,	
190,275,	191,276,	192,277,	193,278,	
194,279,	195,280,	196,281,	197,282,	
132,132,	198,283,	141,132,	199,284,	
136,227,	135,226,	133,224,	200,285,	
201,286,	202,287,	137,229,	138,231,	
139,233,	134,225,	203,288,	204,289,	
205,290,	136,228,	206,291,	207,292,	
208,293,	138,232,	139,234,	142,242,	
140,236,	137,230,	209,294,	210,295,	
211,296,	212,297,	139,235,	144,244,	
140,237,	213,298,	214,299,	144,245,	
215,300,	143,243,	141,238,	216,301,	
217,302,	218,303,	219,304,	221,305,	
222,306,	223,307,	224,0,	225,0,	
141,239,	226,0,	227,0,	228,0,	
229,0,	141,240,	230,0,	232,0,	
141,241,	233,0,	231,0,	234,0,	
235,0,	236,0,	238,0,	237,0,	
239,0,	240,0,	241,0,	242,0,	
243,0,	244,0,	245,0,	246,324,	
247,325,	248,326,	250,327,	251,328,	
252,329,	253,330,	254,331,	255,332,	
256,333,	257,334,	259,335,	260,336,	
261,337,	263,338,	264,339,	265,340,	
266,341,	267,342,	268,343,	270,344,	
271,345,	272,346,	273,347,	274,348,	
275,349,	277,350,	278,351,	279,279,	
281,353,	283,354,	284,355,	286,356,	
288,357,	289,358,	291,359,	292,360,	
293,361,	294,362,	295,363,	298,364,	
299,365,	300,366,	301,367,	303,303,	
304,369,	305,370,	306,371,	308,0,	
309,0,	310,0,	311,0,	312,0,	
313,0,	315,0,	314,0,	316,0,	
318,0,	317,0,	320,0,	319,0,	
322,0,	321,0,	323,0,	324,386,	
325,387,	327,388,	329,389,	330,390,	
331,391,	228,311,	332,392,	333,393,	
334,394,	335,395,	337,396,	229,312,	
341,397,	226,309,	231,313,	236,316,	
240,319,	225,308,	342,398,	227,310,	
237,317,	343,399,	344,400,	345,401,	
245,323,	346,402,	347,403,	234,315,	
232,314,	348,404,	349,405,	350,350,	
351,407,	242,320,	243,321,	239,318,	
352,408,	354,409,	244,322,	355,410,	
356,356,	358,412,	279,352,	359,413,	
361,414,	362,415,	364,416,	365,417,	
366,418,	367,419,	368,420,	369,421,	
370,370,	372,0,	373,0,	374,0,	
375,0,	376,0,	303,368,	377,0,	
379,0,	378,0,	380,0,	381,0,	
382,0,	383,0,	384,0,	385,0,	
386,434,	387,435,	388,436,	389,389,	
391,439,	397,442,	398,443,	399,444,	
395,395,	401,445,	403,446,	404,447,	
312,375,	314,377,	406,448,	407,449,	
410,450,	411,451,	316,379,	317,380,	
321,383,	308,372,	309,373,	310,374,	
413,413,	422,460,	313,376,	315,378,	
412,412,	415,415,	318,381,	319,382,	
416,416,	403,446,	322,384,	419,419,	
323,385,	421,421,	423,0,	424,0,	
425,0,	427,0,	350,406,	426,0,	
428,0,	429,0,	430,0,	431,0,	
433,0,	437,469,	432,0,	356,411,	
438,470,	440,471,	441,472,	443,443,	
444,444,	445,475,	446,446,	447,476,	
450,477,	452,478,	453,479,	370,422,	
454,480,	426,426,	455,481,	456,482,	
457,483,	458,484,	459,485,	461,0,	
432,432,	462,0,	463,0,	464,0,	
465,0,	373,424,	466,0,	389,437,	
468,0,	446,446,	375,425,	467,0,	
395,440,	389,438,	372,423,	378,427,	
469,490,	381,430,	395,441,	470,491,	
471,492,	385,433,	472,493,	377,426,	
473,494,	474,495,	475,496,	379,428,	
380,429,	383,432,	382,431,	413,454,	
412,452,	477,497,	478,498,	479,499,	
415,455,	484,500,	412,453,	416,456,	
485,501,	421,458,	419,457,	486,0,	
487,0,	490,506,	488,0,	421,459,	
489,0,	491,507,	492,508,	493,509,	
498,510,	499,511,	500,512,	501,513,	
502,0,	503,0,	504,0,	505,0,	
507,518,	509,519,	443,473,	444,474,	
510,520,	423,461,	511,521,	512,522,	
513,523,	426,464,	514,0,	424,462,	
515,0,	516,0,	425,463,	426,465,	
432,467,	428,466,	517,0,	520,520,	
521,527,	522,522,	432,468,	523,529,	
524,0,	525,0,	526,530,	527,527,	
528,532,	529,529,	531,534,	533,535,	
0,0,	0,0,	464,486,	0,0,	
0,0,	0,0,	0,0,	465,487,	
0,0,	0,0,	467,488,	468,489,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	486,502,	
0,0,	487,503,	488,504,	0,0,	
0,0,	489,505,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	503,515,	
0,0,	505,517,	0,0,	0,0,	
0,0,	0,0,	520,526,	0,0,	
522,528,	0,0,	502,514,	0,0,	
504,516,	0,0,	527,531,	0,0,	
529,533,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	515,524,	0,0,	
0,0,	0,0,	0,0,	0,0,	
517,525,	0,0,	0,0,	0,0,	
0,0};
struct yysvf yysvec[] ={
0,	0,	0,
yycrank+0,	0,		0,	
yycrank+0,	0,		0,	
yycrank+-1,	0,		0,	
yycrank+-36,	yysvec+3,	0,	
yycrank+-122,	0,		0,	
yycrank+-5,	yysvec+5,	0,	
yycrank+-3,	0,		0,	
yycrank+0,	yysvec+7,	0,	
yycrank+123,	0,		0,	
yycrank+0,	yysvec+9,	0,	
yycrank+0,	0,		0,	
yycrank+0,	0,		0,	
yycrank+0,	0,		0,	
yycrank+0,	0,		0,	
yycrank+0,	0,		yyvstop+1,
yycrank+0,	0,		yyvstop+3,
yycrank+0,	0,		yyvstop+6,
yycrank+0,	0,		yyvstop+8,
yycrank+0,	0,		yyvstop+11,
yycrank+3,	0,		yyvstop+14,
yycrank+198,	0,		yyvstop+16,
yycrank+211,	0,		yyvstop+18,
yycrank+0,	0,		yyvstop+21,
yycrank+3,	0,		yyvstop+24,
yycrank+280,	0,		yyvstop+26,
yycrank+3,	yysvec+25,	yyvstop+29,
yycrank+14,	0,		yyvstop+32,
yycrank+4,	0,		yyvstop+34,
yycrank+0,	0,		yyvstop+36,
yycrank+44,	yysvec+25,	yyvstop+39,
yycrank+38,	yysvec+25,	yyvstop+42,
yycrank+63,	yysvec+25,	yyvstop+45,
yycrank+68,	yysvec+25,	yyvstop+48,
yycrank+66,	yysvec+25,	yyvstop+51,
yycrank+16,	yysvec+25,	yyvstop+54,
yycrank+56,	yysvec+25,	yyvstop+57,
yycrank+33,	yysvec+25,	yyvstop+60,
yycrank+172,	yysvec+25,	yyvstop+63,
yycrank+55,	yysvec+25,	yyvstop+66,
yycrank+64,	yysvec+25,	yyvstop+69,
yycrank+75,	yysvec+25,	yyvstop+72,
yycrank+64,	yysvec+25,	yyvstop+75,
yycrank+174,	yysvec+25,	yyvstop+78,
yycrank+177,	yysvec+25,	yyvstop+81,
yycrank+180,	yysvec+25,	yyvstop+84,
yycrank+68,	yysvec+25,	yyvstop+87,
yycrank+189,	yysvec+25,	yyvstop+90,
yycrank+0,	0,		yyvstop+93,
yycrank+-402,	0,		yyvstop+96,
yycrank+0,	0,		yyvstop+99,
yycrank+0,	0,		yyvstop+101,
yycrank+0,	0,		yyvstop+103,
yycrank+337,	0,		yyvstop+106,
yycrank+0,	0,		yyvstop+108,
yycrank+0,	0,		yyvstop+110,
yycrank+365,	yysvec+9,	yyvstop+112,
yycrank+0,	0,		yyvstop+114,
yycrank+382,	0,		yyvstop+116,
yycrank+70,	0,		yyvstop+118,
yycrank+82,	0,		yyvstop+120,
yycrank+175,	0,		yyvstop+122,
yycrank+191,	0,		0,	
yycrank+194,	0,		yyvstop+124,
yycrank+340,	0,		yyvstop+126,
yycrank+204,	0,		yyvstop+128,
yycrank+341,	0,		yyvstop+130,
yycrank+73,	0,		yyvstop+132,
yycrank+73,	0,		0,	
yycrank+114,	0,		yyvstop+134,
yycrank+0,	0,		yyvstop+136,
yycrank+0,	0,		yyvstop+138,
yycrank+420,	yysvec+58,	yyvstop+140,
yycrank+0,	yysvec+22,	yyvstop+142,
yycrank+0,	0,		yyvstop+144,
yycrank+86,	0,		0,	
yycrank+0,	yysvec+75,	0,	
yycrank+100,	0,		0,	
yycrank+113,	0,		0,	
yycrank+194,	0,		yyvstop+146,
yycrank+0,	yysvec+25,	yyvstop+148,
yycrank+144,	yysvec+25,	yyvstop+150,
yycrank+0,	0,		yyvstop+152,
yycrank+0,	0,		yyvstop+154,
yycrank+159,	yysvec+25,	yyvstop+156,
yycrank+175,	yysvec+25,	yyvstop+158,
yycrank+224,	yysvec+25,	yyvstop+160,
yycrank+0,	yysvec+25,	yyvstop+162,
yycrank+195,	yysvec+25,	yyvstop+165,
yycrank+184,	yysvec+25,	yyvstop+167,
yycrank+0,	yysvec+25,	yyvstop+169,
yycrank+157,	yysvec+25,	yyvstop+172,
yycrank+171,	yysvec+25,	yyvstop+174,
yycrank+176,	yysvec+25,	yyvstop+176,
yycrank+184,	yysvec+25,	yyvstop+178,
yycrank+199,	yysvec+25,	yyvstop+180,
yycrank+0,	yysvec+25,	yyvstop+182,
yycrank+205,	yysvec+25,	yyvstop+185,
yycrank+220,	yysvec+25,	yyvstop+187,
yycrank+227,	yysvec+25,	yyvstop+189,
yycrank+223,	yysvec+25,	yyvstop+191,
yycrank+225,	yysvec+25,	yyvstop+193,
yycrank+233,	yysvec+25,	yyvstop+195,
yycrank+243,	yysvec+25,	yyvstop+197,
yycrank+296,	yysvec+25,	yyvstop+199,
yycrank+233,	yysvec+25,	yyvstop+201,
yycrank+267,	yysvec+25,	yyvstop+203,
yycrank+0,	yysvec+25,	yyvstop+205,
yycrank+255,	yysvec+25,	yyvstop+208,
yycrank+259,	yysvec+25,	yyvstop+210,
yycrank+274,	yysvec+25,	yyvstop+212,
yycrank+295,	yysvec+25,	yyvstop+214,
yycrank+289,	yysvec+25,	yyvstop+216,
yycrank+288,	yysvec+25,	yyvstop+218,
yycrank+290,	yysvec+25,	yyvstop+220,
yycrank+295,	yysvec+25,	yyvstop+222,
yycrank+0,	yysvec+25,	yyvstop+224,
yycrank+318,	yysvec+25,	yyvstop+227,
yycrank+324,	yysvec+25,	yyvstop+229,
yycrank+322,	yysvec+25,	yyvstop+231,
yycrank+309,	yysvec+25,	yyvstop+233,
yycrank+318,	yysvec+25,	yyvstop+235,
yycrank+306,	yysvec+25,	yyvstop+237,
yycrank+323,	yysvec+25,	yyvstop+239,
yycrank+335,	yysvec+25,	yyvstop+241,
yycrank+347,	yysvec+25,	yyvstop+243,
yycrank+344,	yysvec+25,	yyvstop+245,
yycrank+334,	yysvec+25,	yyvstop+247,
yycrank+335,	yysvec+25,	yyvstop+250,
yycrank+327,	yysvec+25,	yyvstop+253,
yycrank+339,	yysvec+25,	yyvstop+255,
yycrank+362,	yysvec+25,	yyvstop+257,
yycrank+-479,	0,		yyvstop+259,
yycrank+-445,	yysvec+132,	yyvstop+261,
yycrank+-446,	yysvec+132,	yyvstop+264,
yycrank+-448,	yysvec+132,	yyvstop+267,
yycrank+-451,	yysvec+132,	yyvstop+270,
yycrank+-453,	yysvec+132,	yyvstop+273,
yycrank+-454,	yysvec+132,	yyvstop+275,
yycrank+-455,	yysvec+132,	yyvstop+278,
yycrank+-471,	yysvec+132,	yyvstop+281,
yycrank+-481,	0,		yyvstop+284,
yycrank+-456,	yysvec+132,	yyvstop+287,
yycrank+-469,	yysvec+132,	yyvstop+290,
yycrank+-474,	yysvec+132,	yyvstop+292,
yycrank+-473,	yysvec+132,	yyvstop+295,
yycrank+-475,	yysvec+132,	yyvstop+298,
yycrank+0,	0,		yyvstop+301,
yycrank+0,	0,		yyvstop+303,
yycrank+0,	0,		yyvstop+305,
yycrank+370,	0,		0,	
yycrank+382,	0,		0,	
yycrank+379,	0,		0,	
yycrank+395,	0,		0,	
yycrank+391,	0,		0,	
yycrank+0,	0,		yyvstop+307,
yycrank+395,	0,		0,	
yycrank+379,	0,		0,	
yycrank+0,	0,		yyvstop+309,
yycrank+385,	0,		0,	
yycrank+0,	0,		yyvstop+311,
yycrank+402,	0,		0,	
yycrank+401,	0,		0,	
yycrank+0,	0,		yyvstop+313,
yycrank+388,	0,		0,	
yycrank+410,	0,		0,	
yycrank+0,	0,		yyvstop+315,
yycrank+396,	0,		0,	
yycrank+397,	0,		0,	
yycrank+396,	0,		0,	
yycrank+413,	0,		0,	
yycrank+0,	0,		yyvstop+317,
yycrank+0,	0,		yyvstop+319,
yycrank+413,	yysvec+25,	yyvstop+321,
yycrank+397,	yysvec+25,	yyvstop+323,
yycrank+0,	yysvec+25,	yyvstop+325,
yycrank+0,	yysvec+25,	yyvstop+328,
yycrank+409,	yysvec+25,	yyvstop+331,
yycrank+413,	yysvec+25,	yyvstop+333,
yycrank+406,	yysvec+25,	yyvstop+335,
yycrank+410,	yysvec+25,	yyvstop+337,
yycrank+0,	yysvec+25,	yyvstop+339,
yycrank+0,	yysvec+25,	yyvstop+342,
yycrank+412,	yysvec+25,	yyvstop+345,
yycrank+418,	yysvec+25,	yyvstop+347,
yycrank+432,	yysvec+25,	yyvstop+349,
yycrank+433,	yysvec+25,	yyvstop+351,
yycrank+429,	yysvec+25,	yyvstop+353,
yycrank+429,	yysvec+25,	yyvstop+355,
yycrank+426,	yysvec+25,	yyvstop+357,
yycrank+420,	yysvec+25,	yyvstop+359,
yycrank+427,	yysvec+25,	yyvstop+362,
yycrank+422,	yysvec+25,	yyvstop+364,
yycrank+434,	yysvec+25,	yyvstop+366,
yycrank+508,	yysvec+25,	yyvstop+368,
yycrank+433,	yysvec+25,	yyvstop+370,
yycrank+427,	yysvec+25,	yyvstop+372,
yycrank+434,	yysvec+25,	yyvstop+374,
yycrank+442,	yysvec+25,	yyvstop+376,
yycrank+442,	yysvec+25,	yyvstop+378,
yycrank+435,	yysvec+25,	yyvstop+380,
yycrank+436,	yysvec+25,	yyvstop+382,
yycrank+452,	yysvec+25,	yyvstop+384,
yycrank+443,	yysvec+25,	yyvstop+386,
yycrank+458,	yysvec+25,	yyvstop+388,
yycrank+459,	yysvec+25,	yyvstop+390,
yycrank+446,	yysvec+25,	yyvstop+392,
yycrank+453,	yysvec+25,	yyvstop+394,
yycrank+459,	yysvec+25,	yyvstop+396,
yycrank+466,	yysvec+25,	yyvstop+399,
yycrank+456,	yysvec+25,	yyvstop+401,
yycrank+471,	yysvec+25,	yyvstop+403,
yycrank+472,	yysvec+25,	yyvstop+405,
yycrank+461,	yysvec+25,	yyvstop+407,
yycrank+473,	yysvec+25,	yyvstop+409,
yycrank+479,	yysvec+25,	yyvstop+411,
yycrank+469,	yysvec+25,	yyvstop+413,
yycrank+474,	yysvec+25,	yyvstop+415,
yycrank+553,	yysvec+25,	yyvstop+418,
yycrank+485,	yysvec+25,	yyvstop+420,
yycrank+0,	yysvec+25,	yyvstop+422,
yycrank+471,	yysvec+25,	yyvstop+425,
yycrank+472,	yysvec+25,	yyvstop+427,
yycrank+485,	yysvec+25,	yyvstop+430,
yycrank+-580,	yysvec+132,	yyvstop+432,
yycrank+-581,	yysvec+132,	yyvstop+435,
yycrank+-583,	yysvec+132,	yyvstop+437,
yycrank+-584,	yysvec+132,	yyvstop+439,
yycrank+-585,	yysvec+132,	yyvstop+441,
yycrank+-586,	yysvec+132,	yyvstop+443,
yycrank+-588,	yysvec+132,	yyvstop+445,
yycrank+-592,	yysvec+132,	yyvstop+448,
yycrank+-589,	yysvec+132,	yyvstop+450,
yycrank+-591,	yysvec+132,	yyvstop+452,
yycrank+-593,	yysvec+132,	yyvstop+455,
yycrank+-594,	yysvec+132,	yyvstop+457,
yycrank+-595,	yysvec+132,	yyvstop+460,
yycrank+-597,	yysvec+132,	yyvstop+462,
yycrank+-596,	yysvec+132,	yyvstop+464,
yycrank+-598,	yysvec+132,	yyvstop+467,
yycrank+-599,	yysvec+132,	yyvstop+469,
yycrank+-600,	yysvec+132,	yyvstop+471,
yycrank+-601,	yysvec+132,	yyvstop+474,
yycrank+-602,	yysvec+132,	yyvstop+476,
yycrank+-603,	yysvec+132,	yyvstop+478,
yycrank+-604,	yysvec+132,	yyvstop+480,
yycrank+499,	0,		yyvstop+482,
yycrank+500,	0,		0,	
yycrank+501,	0,		0,	
yycrank+0,	0,		yyvstop+484,
yycrank+515,	0,		0,	
yycrank+503,	0,		0,	
yycrank+519,	0,		0,	
yycrank+505,	0,		0,	
yycrank+517,	0,		yyvstop+486,
yycrank+519,	0,		0,	
yycrank+508,	0,		0,	
yycrank+511,	0,		0,	
yycrank+0,	0,		yyvstop+488,
yycrank+525,	0,		0,	
yycrank+511,	0,		0,	
yycrank+512,	0,		yyvstop+490,
yycrank+0,	yysvec+25,	yyvstop+492,
yycrank+528,	yysvec+25,	yyvstop+495,
yycrank+511,	yysvec+25,	yyvstop+497,
yycrank+512,	yysvec+25,	yyvstop+499,
yycrank+531,	yysvec+25,	yyvstop+501,
yycrank+522,	yysvec+25,	yyvstop+503,
yycrank+533,	yysvec+25,	yyvstop+505,
yycrank+0,	yysvec+25,	yyvstop+507,
yycrank+527,	yysvec+25,	yyvstop+510,
yycrank+529,	yysvec+25,	yyvstop+512,
yycrank+536,	yysvec+25,	yyvstop+514,
yycrank+528,	yysvec+25,	yyvstop+517,
yycrank+538,	yysvec+25,	yyvstop+519,
yycrank+539,	yysvec+25,	yyvstop+522,
yycrank+0,	yysvec+25,	yyvstop+524,
yycrank+609,	yysvec+25,	yyvstop+527,
yycrank+530,	yysvec+25,	yyvstop+529,
yycrank+611,	0,		0,	
yycrank+0,	yysvec+25,	yyvstop+531,
yycrank+528,	yysvec+25,	yyvstop+534,
yycrank+0,	yysvec+25,	yyvstop+536,
yycrank+541,	yysvec+25,	yyvstop+539,
yycrank+531,	yysvec+25,	yyvstop+541,
yycrank+0,	yysvec+25,	yyvstop+543,
yycrank+615,	yysvec+25,	yyvstop+546,
yycrank+0,	yysvec+25,	yyvstop+549,
yycrank+532,	yysvec+25,	yyvstop+552,
yycrank+535,	yysvec+25,	yyvstop+554,
yycrank+0,	yysvec+25,	yyvstop+556,
yycrank+546,	yysvec+25,	yyvstop+559,
yycrank+535,	yysvec+25,	yyvstop+561,
yycrank+535,	yysvec+25,	yyvstop+563,
yycrank+537,	yysvec+25,	yyvstop+565,
yycrank+538,	yysvec+25,	yyvstop+567,
yycrank+0,	yysvec+25,	yyvstop+569,
yycrank+0,	yysvec+25,	yyvstop+572,
yycrank+551,	yysvec+25,	yyvstop+575,
yycrank+546,	yysvec+25,	yyvstop+577,
yycrank+560,	yysvec+25,	yyvstop+579,
yycrank+542,	yysvec+25,	yyvstop+581,
yycrank+0,	yysvec+25,	yyvstop+583,
yycrank+627,	0,		0,	
yycrank+546,	yysvec+25,	yyvstop+586,
yycrank+629,	yysvec+25,	yyvstop+588,
yycrank+558,	yysvec+25,	yyvstop+590,
yycrank+0,	yysvec+25,	yyvstop+592,
yycrank+-653,	yysvec+132,	yyvstop+595,
yycrank+-654,	yysvec+132,	yyvstop+598,
yycrank+-655,	yysvec+132,	yyvstop+600,
yycrank+-656,	yysvec+132,	yyvstop+602,
yycrank+-657,	yysvec+132,	yyvstop+605,
yycrank+-658,	yysvec+132,	yyvstop+607,
yycrank+-660,	yysvec+132,	yyvstop+609,
yycrank+-659,	yysvec+132,	yyvstop+611,
yycrank+-661,	yysvec+132,	yyvstop+613,
yycrank+-663,	yysvec+132,	yyvstop+616,
yycrank+-662,	yysvec+132,	yyvstop+618,
yycrank+-665,	yysvec+132,	yyvstop+620,
yycrank+-664,	yysvec+132,	yyvstop+622,
yycrank+-667,	yysvec+132,	yyvstop+625,
yycrank+-666,	yysvec+132,	yyvstop+627,
yycrank+-668,	yysvec+132,	yyvstop+629,
yycrank+568,	0,		0,	
yycrank+579,	0,		0,	
yycrank+0,	0,		yyvstop+632,
yycrank+577,	0,		0,	
yycrank+0,	0,		yyvstop+634,
yycrank+568,	0,		0,	
yycrank+579,	0,		0,	
yycrank+567,	0,		0,	
yycrank+570,	0,		0,	
yycrank+583,	0,		0,	
yycrank+572,	0,		0,	
yycrank+575,	0,		0,	
yycrank+0,	0,		yyvstop+636,
yycrank+586,	0,		0,	
yycrank+0,	yysvec+25,	yyvstop+638,
yycrank+0,	yysvec+25,	yyvstop+641,
yycrank+0,	yysvec+25,	yyvstop+644,
yycrank+591,	yysvec+25,	yyvstop+647,
yycrank+589,	yysvec+25,	yyvstop+649,
yycrank+587,	yysvec+25,	yyvstop+651,
yycrank+601,	yysvec+25,	yyvstop+653,
yycrank+584,	yysvec+25,	yyvstop+655,
yycrank+605,	yysvec+25,	yyvstop+657,
yycrank+605,	yysvec+25,	yyvstop+659,
yycrank+593,	yysvec+25,	yyvstop+661,
yycrank+610,	yysvec+25,	yyvstop+663,
yycrank+679,	0,		0,	
yycrank+597,	yysvec+25,	yyvstop+665,
yycrank+614,	0,		0,	
yycrank+0,	yysvec+25,	yyvstop+667,
yycrank+601,	yysvec+25,	yyvstop+670,
yycrank+614,	yysvec+25,	yyvstop+672,
yycrank+688,	0,		0,	
yycrank+0,	yysvec+25,	yyvstop+675,
yycrank+689,	yysvec+25,	yyvstop+678,
yycrank+691,	yysvec+25,	yyvstop+680,
yycrank+0,	yysvec+25,	yyvstop+682,
yycrank+609,	yysvec+25,	yyvstop+685,
yycrank+693,	yysvec+25,	yyvstop+687,
yycrank+0,	yysvec+25,	yyvstop+690,
yycrank+694,	yysvec+25,	yyvstop+693,
yycrank+626,	yysvec+25,	yyvstop+695,
yycrank+628,	yysvec+25,	yyvstop+697,
yycrank+697,	yysvec+25,	yyvstop+699,
yycrank+628,	0,		0,	
yycrank+699,	yysvec+25,	yyvstop+701,
yycrank+700,	0,		0,	
yycrank+0,	yysvec+25,	yyvstop+703,
yycrank+-723,	yysvec+132,	yyvstop+706,
yycrank+-724,	yysvec+132,	yyvstop+708,
yycrank+-725,	yysvec+132,	yyvstop+710,
yycrank+-726,	yysvec+132,	yyvstop+713,
yycrank+-727,	yysvec+132,	yyvstop+715,
yycrank+-729,	yysvec+132,	yyvstop+718,
yycrank+-731,	yysvec+132,	yyvstop+720,
yycrank+-730,	yysvec+132,	yyvstop+722,
yycrank+-732,	yysvec+132,	yyvstop+724,
yycrank+-733,	yysvec+132,	yyvstop+726,
yycrank+-734,	yysvec+132,	yyvstop+728,
yycrank+-735,	yysvec+132,	yyvstop+730,
yycrank+-736,	yysvec+132,	yyvstop+732,
yycrank+-737,	yysvec+132,	yyvstop+735,
yycrank+639,	0,		0,	
yycrank+635,	0,		0,	
yycrank+634,	0,		0,	
yycrank+719,	0,		0,	
yycrank+0,	0,		yyvstop+737,
yycrank+637,	0,		0,	
yycrank+0,	0,		yyvstop+739,
yycrank+0,	0,		yyvstop+741,
yycrank+0,	0,		yyvstop+743,
yycrank+724,	0,		0,	
yycrank+0,	0,		yyvstop+745,
yycrank+643,	yysvec+25,	yyvstop+747,
yycrank+722,	yysvec+25,	yyvstop+749,
yycrank+723,	yysvec+25,	yyvstop+751,
yycrank+0,	yysvec+25,	yyvstop+753,
yycrank+652,	yysvec+25,	yyvstop+756,
yycrank+0,	yysvec+25,	yyvstop+758,
yycrank+749,	yysvec+25,	yyvstop+761,
yycrank+658,	yysvec+25,	yyvstop+763,
yycrank+0,	yysvec+25,	yyvstop+765,
yycrank+660,	0,		0,	
yycrank+662,	yysvec+25,	yyvstop+768,
yycrank+0,	0,		yyvstop+770,
yycrank+0,	yysvec+25,	yyvstop+772,
yycrank+666,	yysvec+25,	yyvstop+775,
yycrank+663,	0,		0,	
yycrank+744,	0,		0,	
yycrank+740,	0,		0,	
yycrank+0,	yysvec+25,	yyvstop+777,
yycrank+745,	0,		0,	
yycrank+748,	0,		0,	
yycrank+0,	yysvec+25,	yyvstop+780,
yycrank+0,	yysvec+25,	yyvstop+783,
yycrank+751,	0,		0,	
yycrank+0,	0,		yyvstop+786,
yycrank+753,	0,		0,	
yycrank+671,	0,		0,	
yycrank+-776,	yysvec+132,	yyvstop+788,
yycrank+-777,	yysvec+132,	yyvstop+790,
yycrank+-778,	yysvec+132,	yyvstop+792,
yycrank+-781,	yysvec+132,	yyvstop+794,
yycrank+-779,	yysvec+132,	yyvstop+796,
yycrank+-782,	yysvec+132,	yyvstop+799,
yycrank+-783,	yysvec+132,	yyvstop+801,
yycrank+-784,	yysvec+132,	yyvstop+804,
yycrank+-785,	yysvec+132,	yyvstop+807,
yycrank+-788,	yysvec+132,	yyvstop+810,
yycrank+-786,	yysvec+132,	yyvstop+812,
yycrank+0,	0,		yyvstop+815,
yycrank+0,	0,		yyvstop+817,
yycrank+0,	0,		yyvstop+819,
yycrank+696,	0,		0,	
yycrank+695,	0,		0,	
yycrank+0,	0,		yyvstop+821,
yycrank+700,	0,		0,	
yycrank+697,	0,		0,	
yycrank+0,	yysvec+25,	yyvstop+823,
yycrank+771,	0,		0,	
yycrank+772,	0,		0,	
yycrank+690,	yysvec+25,	yyvstop+826,
yycrank+797,	0,		yyvstop+828,
yycrank+693,	yysvec+25,	yyvstop+830,
yycrank+0,	0,		yyvstop+832,
yycrank+0,	yysvec+25,	yyvstop+834,
yycrank+700,	yysvec+25,	yyvstop+837,
yycrank+0,	0,		yyvstop+839,
yycrank+708,	0,		0,	
yycrank+705,	0,		0,	
yycrank+710,	0,		0,	
yycrank+712,	0,		0,	
yycrank+713,	0,		0,	
yycrank+714,	0,		0,	
yycrank+716,	0,		0,	
yycrank+713,	0,		0,	
yycrank+0,	0,		yyvstop+841,
yycrank+-809,	yysvec+132,	yyvstop+843,
yycrank+-811,	yysvec+132,	yyvstop+846,
yycrank+-812,	yysvec+132,	yyvstop+849,
yycrank+-813,	yysvec+132,	yyvstop+852,
yycrank+-814,	yysvec+132,	yyvstop+854,
yycrank+-816,	yysvec+132,	yyvstop+856,
yycrank+-821,	yysvec+132,	yyvstop+859,
yycrank+-818,	yysvec+132,	yyvstop+861,
yycrank+734,	0,		0,	
yycrank+736,	0,		0,	
yycrank+738,	0,		0,	
yycrank+739,	0,		0,	
yycrank+742,	0,		0,	
yycrank+743,	0,		0,	
yycrank+745,	yysvec+25,	yyvstop+863,
yycrank+0,	yysvec+25,	yyvstop+865,
yycrank+752,	yysvec+25,	yyvstop+868,
yycrank+752,	0,		0,	
yycrank+752,	0,		0,	
yycrank+0,	0,		yyvstop+870,
yycrank+0,	0,		yyvstop+872,
yycrank+0,	0,		yyvstop+874,
yycrank+0,	0,		yyvstop+876,
yycrank+755,	0,		0,	
yycrank+757,	0,		0,	
yycrank+-853,	yysvec+132,	yyvstop+878,
yycrank+-854,	yysvec+132,	yyvstop+880,
yycrank+-856,	yysvec+132,	yyvstop+882,
yycrank+-858,	yysvec+132,	yyvstop+884,
yycrank+749,	0,		0,	
yycrank+765,	0,		0,	
yycrank+754,	0,		0,	
yycrank+767,	0,		0,	
yycrank+0,	0,		yyvstop+886,
yycrank+0,	0,		yyvstop+888,
yycrank+0,	yysvec+25,	yyvstop+890,
yycrank+0,	yysvec+25,	yyvstop+893,
yycrank+756,	0,		0,	
yycrank+769,	0,		0,	
yycrank+758,	0,		0,	
yycrank+771,	0,		0,	
yycrank+-866,	yysvec+132,	yyvstop+896,
yycrank+-867,	yysvec+132,	yyvstop+898,
yycrank+-868,	yysvec+132,	yyvstop+900,
yycrank+-869,	yysvec+132,	yyvstop+902,
yycrank+0,	0,		yyvstop+904,
yycrank+764,	0,		0,	
yycrank+0,	0,		yyvstop+906,
yycrank+765,	0,		0,	
yycrank+852,	0,		0,	
yycrank+770,	0,		0,	
yycrank+855,	0,		0,	
yycrank+772,	0,		0,	
yycrank+-880,	yysvec+132,	yyvstop+908,
yycrank+-882,	yysvec+132,	yyvstop+911,
yycrank+-883,	yysvec+132,	yyvstop+913,
yycrank+-888,	yysvec+132,	yyvstop+916,
yycrank+0,	0,		yyvstop+918,
yycrank+0,	0,		yyvstop+920,
yycrank+867,	0,		0,	
yycrank+868,	0,		0,	
yycrank+869,	0,		0,	
yycrank+871,	0,		0,	
yycrank+-894,	yysvec+132,	yyvstop+922,
yycrank+-895,	yysvec+132,	yyvstop+925,
yycrank+804,	0,		0,	
yycrank+875,	0,		0,	
yycrank+806,	0,		0,	
yycrank+877,	0,		0,	
yycrank+0,	0,		yyvstop+928,
yycrank+808,	0,		0,	
yycrank+0,	0,		yyvstop+930,
yycrank+809,	0,		0,	
yycrank+0,	0,		yyvstop+932,
yycrank+0,	0,		yyvstop+934,
0,	0,	0};
struct yywork *yytop = yycrank+1004;
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
01  ,'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,
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
