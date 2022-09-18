/*
 *  Author: cck    Date: 86/07/04 15:45:55  
 *  Header: abqueue.h,v 1.1 86/07/04 15:45:55 cck Rel  
 *  Revision: 1.1  
*/

/*
 * abqueue.h - header file for abqueue and abqueue users 
 *
 * AppleTalk package for UNIX (4.2 BSD).
 *
 * Copyright (c) 1986 by The Trustees of Columbia University in the
 * City of New York.
 *
 * Edit History:
 *
 *  July  1, 1986    Schilit    Created
 *
 */

typedef struct qelem {
  struct qelem *q_forw;
  struct qelem *q_back;
} QElem, *QElemPtr, **QHead;

#define NILQ (QElemPtr) 0
#define NILQHEAD (QHead) 0

void q_head();
void q_tail();
QElemPtr dq_head(),dq_tail();
QElemPtr q_next(),q_prev();

