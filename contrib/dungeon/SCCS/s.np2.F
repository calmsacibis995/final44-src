h49864
s 00238/00000/00000
d D 5.1 88/10/20 18:36:00 bostic 1 0
c from UUNET; applied patches 1-3
e
u
U
t
T
I 1
C GETOBJ--	FIND OBJ DESCRIBED BY ADJ, NAME PAIR
C
C COPYRIGHT 1980, INFOCOM COMPUTERS AND COMMUNICATIONS, CAMBRIDGE MA. 02142
C ALL RIGHTS RESERVED, COMMERCIAL USAGE STRICTLY PROHIBITED
C WRITTEN BY R. M. SUPNIK
C
C DECLARATIONS
C
C THIS ROUTINE DETAILS ON BIT 3 OF PRSFLG
C
	INTEGER FUNCTION GETOBJ(OIDX,AIDX,SPCOBJ)
	IMPLICIT INTEGER(A-Z)
	LOGICAL THISIT,GHERE,LIT,CHOMP
#include "parser.h"
#include "gamestate.h"
C
C MISCELLANEOUS VARIABLES
C
	COMMON /STAR/ MBASE,STRBIT
#include "debug.h"
#include "objects.h"
#include "oflags.h"
#include "advers.h"
#include "vocab.h"
C GETOBJ, PAGE 2
C
#ifdef debug
	DFLAG=and(PRSFLG, 8).NE.0
#endif debug
	CHOMP=.FALSE.
	AV=AVEHIC(WINNER)
	OBJ=0
C						!ASSUME DARK.
	IF(.NOT.LIT(HERE)) GO TO 200
C						!LIT?
C
	OBJ=SCHLST(OIDX,AIDX,HERE,0,0,SPCOBJ)
C						!SEARCH ROOM.
#ifdef debug
	IF(DFLAG) PRINT 10,OBJ
#ifdef NOCC
10	FORMAT('SCHLST- ROOM SCH ',I6)
#else NOCC
10	FORMAT(' SCHLST- ROOM SCH ',I6)
#endif NOCC
#endif debug
	IF(OBJ) 1000,200,100
C						!TEST RESULT.
100	IF((AV.EQ.0).OR.(AV.EQ.OBJ).OR.
&		(and(OFLAG2(OBJ),FINDBT).NE.0)) GO TO 200
	IF(OCAN(OBJ).EQ.AV) GO TO 200
C						!TEST IF REACHABLE.
	CHOMP=.TRUE.
C						!PROBABLY NOT.
C
200	IF(AV.EQ.0) GO TO 400
C						!IN VEHICLE?
	NOBJ=SCHLST(OIDX,AIDX,0,AV,0,SPCOBJ)
C						!SEARCH VEHICLE.
#ifdef debug
	IF(DFLAG) PRINT 20,NOBJ
#ifdef NOCC
20	FORMAT('SCHLST- VEH SCH  ',I6)
#else NOCC
20	FORMAT(' SCHLST- VEH SCH  ',I6)
#endif NOCC
#endif debug
	IF(NOBJ) 1100,400,300
C						!TEST RESULT.
300	CHOMP=.FALSE.
C						!REACHABLE.
	IF(OBJ.EQ.NOBJ) GO TO 400
C						!SAME AS BEFORE?
	IF(OBJ.NE.0) NOBJ=-NOBJ
C						!AMB RESULT?
	OBJ=NOBJ
C
400	NOBJ=SCHLST(OIDX,AIDX,0,0,WINNER,SPCOBJ)
C						!SEARCH ADVENTURER.
#ifdef debug
	IF(DFLAG) PRINT 30,NOBJ
#ifdef NOCC
30	FORMAT('SCHLST- ADV SCH  ',I6)
#else NOCC
30	FORMAT(' SCHLST- ADV SCH  ',I6)
#endif NOCC
#endif debug
	IF(NOBJ) 1100,600,500
C						!TEST RESULT
500	IF(OBJ.NE.0) NOBJ=-NOBJ
C						!AMB RESULT?
1100	OBJ=NOBJ
C						!RETURN NEW OBJECT.
600	IF(CHOMP) OBJ=-10000
C						!UNREACHABLE.
1000	GETOBJ=OBJ
C
	IF(GETOBJ.NE.0) GO TO 1500
C						!GOT SOMETHING?
	DO 1200 I=STRBIT+1,OLNT
C						!NO, SEARCH GLOBALS.
	  IF(.NOT.THISIT(OIDX,AIDX,I,SPCOBJ)) GO TO 1200
	  IF(.NOT.GHERE(I,HERE)) GO TO 1200
C						!CAN IT BE HERE?
	  IF(GETOBJ.NE.0) GETOBJ=-I
C						!AMB MATCH?
	  IF(GETOBJ.EQ.0) GETOBJ=I
1200	CONTINUE
C
1500	CONTINUE
C						!END OF SEARCH.
#ifdef debug
	IF(DFLAG) PRINT 40,GETOBJ
#ifdef NOCC
40	FORMAT('SCHLST- RESULT   ',I6)
#else NOCC
40	FORMAT(' SCHLST- RESULT   ',I6)
#endif NOCC
#endif debug
	RETURN
	END
C SCHLST--	SEARCH FOR OBJECT
C
C DECLARATIONS
C
	INTEGER FUNCTION SCHLST(OIDX,AIDX,RM,CN,AD,SPCOBJ)
	IMPLICIT INTEGER(A-Z)
	LOGICAL THISIT,QHERE,NOTRAN,NOVIS
C
	COMMON /STAR/ MBASE,STRBIT
#include "objects.h"
#include "oflags.h"
C
C FUNCTIONS AND DATA
C
	NOTRAN(O)=(and(OFLAG1(O),TRANBT).EQ.0).AND.
&		(and(OFLAG2(O),OPENBT).EQ.0)
	NOVIS(O)=(and(OFLAG1(O),VISIBT).EQ.0)
C
	SCHLST=0
C						!NO RESULT.
	DO 1000 I=1,OLNT
C						!SEARCH OBJECTS.
	  IF(NOVIS(I).OR.
&		(((RM.EQ.0).OR.(.NOT.QHERE(I,RM))).AND.
&		 ((CN.EQ.0).OR.(OCAN(I).NE.CN)).AND.
&		 ((AD.EQ.0).OR.(OADV(I).NE.AD)))) GO TO 1000
	  IF(.NOT.THISIT(OIDX,AIDX,I,SPCOBJ)) GO TO 200
	  IF(SCHLST.NE.0) GO TO 2000
C						!GOT ONE ALREADY?
	  SCHLST=I
C						!NO.
C
C IF OPEN OR TRANSPARENT, SEARCH THE OBJECT ITSELF.
C
200	  IF(NOTRAN(I)) GO TO 1000
C
C SEARCH IS CONDUCTED IN REVERSE.  ALL OBJECTS ARE CHECKED TO
C SEE IF THEY ARE AT SOME LEVEL OF CONTAINMENT INSIDE OBJECT 'I'.
C IF THEY ARE AT LEVEL 1, OR IF ALL LINKS IN THE CONTAINMENT
C CHAIN ARE OPEN, VISIBLE, AND HAVE SEARCHME SET, THEY CAN QUALIFY
C AS A POTENTIAL MATCH.
C
	  DO 500 J=1,OLNT
C						!SEARCH OBJECTS.
	    IF(NOVIS(J).OR. (.NOT.THISIT(OIDX,AIDX,J,SPCOBJ)))
&		GO TO 500
	    X=OCAN(J)
C						!GET CONTAINER.
300	    IF(X.EQ.I) GO TO 400
C						!INSIDE TARGET?
	    IF(X.EQ.0) GO TO 500
C						!INSIDE ANYTHING?
	    IF(NOVIS(X).OR.NOTRAN(X).OR.
&		(and(OFLAG2(X),SCHBT).EQ.0)) GO TO 500
	    X=OCAN(X)
C						!GO ANOTHER LEVEL.
	    GO TO 300
C
400	    IF(SCHLST.NE.0) GO TO 2000
C						!ALREADY GOT ONE?
	    SCHLST=J
C						!NO.
500	  CONTINUE
C
1000	CONTINUE
	RETURN
C
2000	SCHLST=-SCHLST
C						!AMB RETURN.
	RETURN
C
	END
C
C THISIT--	VALIDATE OBJECT VS DESCRIPTION
C
C DECLARATIONS
C
	LOGICAL  FUNCTION  THISIT(OIDX,AIDX,OBJ,SPCOBJ)
	IMPLICIT INTEGER(A-Z)
	LOGICAL  NOTEST
#include "vocab.h"
C
C FUNCTIONS AND DATA
C
	NOTEST(O)=(O.LE.0).OR.(O.GE.R50MIN)
C
C    THE FOLLOWING DATA STATEMENT USED RADIX-50 NOTATION (R50MIN/1RA/)
C       IN RADIX-50 NOTATION, AN "A" IN THE FIRST POSITION IS
C       ENCODED AS 1*40*40 = 1600.
C
	DATA R50MIN/1600/
C
	THISIT=.FALSE.
C						!ASSUME NO MATCH.
	IF((SPCOBJ.NE.0).AND.(OBJ.EQ.SPCOBJ)) GO TO 500
C
C CHECK FOR OBJECT NAMES
C
	I=OIDX+1
100	I=I+1
	IF(NOTEST(OVOC(I))) RETURN
C						!IF DONE, LOSE.
	IF(OVOC(I).NE.OBJ) GO TO 100
C						!IF FAIL, CONT.
C
	IF(AIDX.EQ.0) GO TO 500
C						!ANY ADJ?
	I=AIDX+1
200	I=I+1
	IF(NOTEST(AVOC(I))) RETURN
C						!IF DONE, LOSE.
	IF(AVOC(I).NE.OBJ) GO TO 200
C						!IF FAIL, CONT.
C
500	THISIT=.TRUE.
	RETURN
	END
E 1
