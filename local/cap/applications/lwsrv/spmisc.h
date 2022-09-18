/* " Author: cck    Date: 87/09/05 17:28:08  " */
/* " Header: spmisc.h,v 1.1 87/09/05 17:28:08 cck Rel  " */
/* " Revision: 1.1  " */

/*
 * spmisc - UNIX AppleTalk spooling program: act as a laserwriter
 *   some misc. functions useful for spooler
 *   (some should be put in abmisc)
 *
 * AppleTalk package for UNIX (4.2 BSD).
 *
 * Copyright (c) 1986,1987 by The Trustees of Columbia University in the
 * City of New York.
 *
 * Edit History:
 *
 *  Created sept 5, 1987 by cck from lwsrv
 *
*/

void stripspaces();		/* void stripspaces(char *) */
boolean push();			/* boolean push(int) */
int pop();
boolean isstackempty();
void clearstack();
void dumpstack();
char *strdup();			/* char *strdup(char *) */
