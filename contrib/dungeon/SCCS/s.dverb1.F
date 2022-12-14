h20217
s 00339/00000/00000
d D 5.1 88/10/20 18:35:35 bostic 1 0
c from UUNET; applied patches 1-3
e
u
U
t
T
I 1
C TAKE-- BASIC TAKE SEQUENCE
C
C COPYRIGHT 1980, INFOCOM COMPUTERS AND COMMUNICATIONS, CAMBRIDGE MA. 02142
C ALL RIGHTS RESERVED, COMMERCIAL USAGE STRICTLY PROHIBITED
C WRITTEN BY R. M. SUPNIK
C
C TAKE AN OBJECT (FOR VERBS TAKE, PUT, DROP, READ, ETC.)
C
	LOGICAL FUNCTION TAKE(FLG)
C
C DECLARATIONS
C
	IMPLICIT INTEGER (A-Z)
	LOGICAL FLG,OBJACT,OAPPLI,QOPEN,QHERE
#include "parser.h"
#include "gamestate.h"
#include "state.h"
	COMMON /STAR/ MBASE,STRBIT
#include "objects.h"
#include "oflags.h"
C
#include "advers.h"
C
C FUNCTIONS AND DATA
C
	QOPEN(O)=(and(OFLAG2(O),OPENBT).NE.0)
C TAKE, PAGE 2
C
	TAKE=.FALSE.
C						!ASSUME LOSES.
	OA=OACTIO(PRSO)
C						!GET OBJECT ACTION.
	IF(PRSO.LE.STRBIT) GO TO 100
C						!STAR?
	TAKE=OBJACT(X)
C						!YES, LET IT HANDLE.
	RETURN
C
100	X=OCAN(PRSO)
C						!INSIDE?
	IF(PRSO.NE.AVEHIC(WINNER)) GO TO 400
C						!HIS VEHICLE?
	CALL RSPEAK(672)
C						!DUMMY.
	RETURN
C
400	IF(and(OFLAG1(PRSO),TAKEBT).NE.0) GO TO 500
	IF(.NOT.OAPPLI(OA,0)) CALL RSPEAK(552+RND(5))
	RETURN
C
C OBJECT IS TAKEABLE AND IN POSITION TO BE TAKEN.
C
500	IF((X.NE.0).OR. QHERE(PRSO,HERE)) GO TO 600
	IF(OADV(PRSO).EQ.WINNER) CALL RSPEAK(557)
C						!ALREADY GOT IT?
	RETURN
C
600	IF(((X.NE.0).AND.(OADV(X).EQ.WINNER)).OR.
&		((WEIGHT(0,PRSO,WINNER)+OSIZE(PRSO)).LE.MXLOAD))
&		GO TO 700
	CALL RSPEAK(558)
C						!TOO MUCH WEIGHT.
	RETURN
C
700	TAKE=.TRUE.
C						!AT LAST.
	IF(OAPPLI(OA,0)) RETURN
C						!DID IT HANDLE?
	CALL NEWSTA(PRSO,0,0,0,WINNER)
C						!TAKE OBJECT FOR WINNER.
	OFLAG2(PRSO)=or(OFLAG2(PRSO),TCHBT)
	CALL SCRUPD(OFVAL(PRSO))
C						!UPDATE SCORE.
	OFVAL(PRSO)=0
C						!CANT BE SCORED AGAIN.
	IF(FLG) CALL RSPEAK(559)
C						!TELL TAKEN.
	RETURN
C
	END
C DROP- DROP VERB PROCESSOR
C
C DECLARATIONS
C
	LOGICAL FUNCTION DROP(Z)
	IMPLICIT INTEGER (A-Z)
	LOGICAL F,PUT,OBJACT
#include "parser.h"
#include "gamestate.h"
C
C ROOMS
#include "rindex.h"
#include "objects.h"
#include "oflags.h"
C
#include "advers.h"
#include "verbs.h"
C DROP, PAGE 2
C
	DROP=.TRUE.
C						!ASSUME WINS.
	X=OCAN(PRSO)
C						!GET CONTAINER.
	IF(X.EQ.0) GO TO 200
C						!IS IT INSIDE?
	IF(OADV(X).NE.WINNER) GO TO 1000
C						!IS HE CARRYING CON?
	IF(and(OFLAG2(X),OPENBT).NE.0) GO TO 300
	CALL RSPSUB(525,ODESC2(X))
C						!CANT REACH.
	RETURN
C
200	IF(OADV(PRSO).NE.WINNER) GO TO 1000
C						!IS HE CARRYING OBJ?
300	IF(AVEHIC(WINNER).EQ.0) GO TO 400
C						!IS HE IN VEHICLE?
	PRSI=AVEHIC(WINNER)
C						!YES,
	F=PUT(.TRUE.)
C						!DROP INTO VEHICLE.
	PRSI=0
C						!DISARM PARSER.
	RETURN
C						!DONE.
C
400	CALL NEWSTA(PRSO,0,HERE,0,0)
C						!DROP INTO ROOM.
	IF(HERE.EQ.MTREE) CALL NEWSTA(PRSO,0,FORE3,0,0)
	CALL SCRUPD(OFVAL(PRSO))
C						!SCORE OBJECT.
	OFVAL(PRSO)=0
C						!CANT BE SCORED AGAIN.
	OFLAG2(PRSO)=or(OFLAG2(PRSO),TCHBT)
C
	IF(OBJACT(X)) RETURN
C						!DID IT HANDLE?
	I=0
C						!ASSUME NOTHING TO SAY.
	IF(PRSA.EQ.DROPW) I=528
	IF(PRSA.EQ.THROWW) I=529
	IF((I.NE.0).AND.(HERE.EQ.MTREE)) I=659
	CALL RSPSUB(I,ODESC2(PRSO))
	RETURN
C
1000	CALL RSPEAK(527)
C						!DONT HAVE IT.
	RETURN
C
	END
C PUT- PUT VERB PROCESSOR
C
C DECLARATIONS
C
	LOGICAL FUNCTION PUT(FLG)
	IMPLICIT INTEGER (A-Z)
	LOGICAL TAKE,QOPEN,QHERE,OBJACT,FLG
#include "parser.h"
#include "gamestate.h"
C
C MISCELLANEOUS VARIABLES
C
	COMMON /STAR/ MBASE,STRBIT
#include "objects.h"
#include "oflags.h"
#include "advers.h"
#include "verbs.h"
C
C FUNCTIONS AND DATA
C
	QOPEN(R)=((and(OFLAG2(R),OPENBT)).NE.0)
C PUT, PAGE 2
C
	PUT=.FALSE.
	IF((PRSO.LE.STRBIT).AND.(PRSI.LE.STRBIT)) GO TO 200
	IF(.NOT.OBJACT(X)) CALL RSPEAK(560)
C						!STAR
	PUT=.TRUE.
	RETURN
C
200	IF((QOPEN(PRSI))
&		.OR.(and(OFLAG1(PRSI),(DOORBT+CONTBT)).NE.0)
&		.OR.(and(OFLAG2(PRSI),VEHBT).NE.0)) GO TO 300
	CALL RSPEAK(561)
C						!CANT PUT IN THAT.
	RETURN
C
300	IF(QOPEN(PRSI)) GO TO 400
C						!IS IT OPEN?
	CALL RSPEAK(562)
C						!NO, JOKE
	RETURN
C
400	IF(PRSO.NE.PRSI) GO TO 500
C						!INTO ITSELF?
	CALL RSPEAK(563)
C						!YES, JOKE.
	RETURN
C
500	IF(OCAN(PRSO).NE.PRSI) GO TO 600
C						!ALREADY INSIDE.
	CALL RSPSB2(564,ODESC2(PRSO),ODESC2(PRSI))
	PUT=.TRUE.
	RETURN
C
600	IF((WEIGHT(0,PRSO,0)+WEIGHT(0,PRSI,0)+OSIZE(PRSO))
&		.LE.OCAPAC(PRSI)) GO TO 700
	CALL RSPEAK(565)
C						!THEN CANT DO IT.
	RETURN
C
C NOW SEE IF OBJECT (OR ITS CONTAINER) IS IN ROOM
C
700	J=PRSO
C						!START SEARCH.
725	IF(QHERE(J,HERE)) GO TO 750
C						!IS IT HERE?
	J=OCAN(J)
	IF(J.NE.0) GO TO 725
C						!MORE TO DO?
	GO TO 800
C						!NO, SCH FAILS.
C
750	SVO=PRSO
C						!SAVE PARSER.
	SVI=PRSI
	PRSA=TAKEW
	PRSI=0
	IF(.NOT.TAKE(.FALSE.)) RETURN
C						!TAKE OBJECT.
	PRSA=PUTW
	PRSO=SVO
	PRSI=SVI
	GO TO 1000
C
C NOW SEE IF OBJECT IS ON PERSON.
C
800	IF(OCAN(PRSO).EQ.0) GO TO 1000
C						!INSIDE?
	IF(QOPEN(OCAN(PRSO))) GO TO 900
C						!OPEN?
	CALL RSPSUB(566,ODESC2(PRSO))
C						!LOSE.
	RETURN
C
900	CALL SCRUPD(OFVAL(PRSO))
C						!SCORE OBJECT.
	OFVAL(PRSO)=0
	OFLAG2(PRSO)=or(OFLAG2(PRSO),TCHBT)
	CALL NEWSTA(PRSO,0,0,0,WINNER)
C						!TEMPORARILY ON WINNER.
C
1000	IF(OBJACT(X)) RETURN
C						!NO, GIVE OBJECT A SHOT.
	CALL NEWSTA(PRSO,2,0,PRSI,0)
C						!CONTAINED INSIDE.
	PUT=.TRUE.
	RETURN
C
	END
C VALUAC- HANDLES VALUABLES/EVERYTHING
C
C DECLARATIONS
C
	SUBROUTINE VALUAC(V)
	IMPLICIT INTEGER (A-Z)
	LOGICAL LIT,F,F1,TAKE,PUT,DROP,NOTVAL,QHERE
#include "parser.h"
#include "gamestate.h"
#include "objects.h"
#include "oflags.h"
#include "verbs.h"
C
C FUNCTIONS AND DATA
C
	NOTVAL(R)=(SAVEP.EQ.V).AND.(OTVAL(R).LE.0)
C VALUAC, PAGE 2
C
	F=.TRUE.
C						!ASSUME NO ACTIONS.
	I=579
C						!ASSUME NOT LIT.
	IF(.NOT.LIT(HERE)) GO TO 4000
C						!IF NOT LIT, PUNT.
	I=677
C						!ASSUME WRONG VERB.
	SAVEP=PRSO
C						!SAVE PRSO.
	SAVEH=HERE
C						!SAVE HERE.
C
100	IF(PRSA.NE.TAKEW) GO TO 1000
C						!TAKE EVERY/VALUA?
	DO 500 PRSO=1,OLNT
C						!LOOP THRU OBJECTS.
	  IF(.NOT.QHERE(PRSO,HERE).OR.
&		(and(OFLAG1(PRSO),VISIBT).EQ.0).OR.
&		(and(OFLAG2(PRSO),ACTRBT).NE.0).OR.
&		NOTVAL(PRSO)) GO TO 500
	  IF((and(OFLAG1(PRSO),TAKEBT).EQ.0).AND.
&		(and(OFLAG2(PRSO),TRYBT).EQ.0)) GO TO 500
	  F=.FALSE.
	  CALL RSPSUB(580,ODESC2(PRSO))
	  F1=TAKE(.TRUE.)
	  IF(SAVEH.NE.HERE) RETURN
500	CONTINUE
	GO TO 3000
C
1000	IF(PRSA.NE.DROPW) GO TO 2000
C						!DROP EVERY/VALUA?
	DO 1500 PRSO=1,OLNT
	  IF((OADV(PRSO).NE.WINNER).OR.NOTVAL(PRSO))
&		GO TO 1500
	  F=.FALSE.
	  CALL RSPSUB(580,ODESC2(PRSO))
	  F1=DROP(.TRUE.)
	  IF(SAVEH.NE.HERE) RETURN
1500	CONTINUE
	GO TO 3000
C
2000	IF(PRSA.NE.PUTW) GO TO 3000
C						!PUT EVERY/VALUA?
	DO 2500 PRSO=1,OLNT
C						!LOOP THRU OBJECTS.
	  IF((OADV(PRSO).NE.WINNER)
&		.OR.(PRSO.EQ.PRSI).OR.NOTVAL(PRSO).OR.
&		(and(OFLAG1(PRSO),VISIBT).EQ.0)) GO TO 2500
	  F=.FALSE.
	  CALL RSPSUB(580,ODESC2(PRSO))
	  F1=PUT(.TRUE.)
	  IF(SAVEH.NE.HERE) RETURN
2500	CONTINUE
C
3000	I=581
	IF(SAVEP.EQ.V) I=582
C						!CHOOSE MESSAGE.
4000	IF(F) CALL RSPEAK(I)
C						!IF NOTHING, REPORT.
	RETURN
	END
E 1
