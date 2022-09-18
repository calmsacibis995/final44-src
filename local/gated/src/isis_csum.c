/*
 *  isis_csum.c,v 1.9 1993/01/07 22:39:08 jch Exp
 */

/* %(Copyright.header) */


#include "include.h"
#include "isis_globals.h"

/*
 * written by michael g. mcmenemy
 * tcheck.c
 */

#define MOD_VAL 255
#define MAX_CHECK_ITER 4104

/*
 * variable naming match tp4 spec...
 */

void
  tcompute_checksum(pdu_ptr, n, L)
unsigned char *pdu_ptr; /* pointer to start of pdu */
int n; /* index into pdu of checksum - Assumes starting at 1 */
int L; /* length of pdu */
{		  
	int C0 = 0;
	int C1 = 0;
  int i;
  int X; /* first checksum octet */
  int Y; /* second */
  int cnt = 0; /* keeps track of iterations */
  
  for (i = 0; i<L; i++) {
    cnt++;
    C0 += pdu_ptr[i];
    C1 += C0;
    
    if (cnt == MAX_CHECK_ITER) {
      cnt = 0;
      C0 = (C0 % MOD_VAL);
      C1 = (C1 % MOD_VAL);
    }
  }
  
  X = (( -C1 + (L-n)*C0) % MOD_VAL);
  Y = (( C1 - (L-n+1)*C0) % MOD_VAL);
  
  if (X < 0) X += MOD_VAL;
  if (Y < 0) Y += MOD_VAL;
  
  pdu_ptr[--n] = X;
  pdu_ptr[++n] = Y;
  
}

int
tcheck_checksum(pdu_ptr, len)
unsigned char *pdu_ptr;
int len;
{
  int C0 = 0;
  int C1 = 0;
  int i;
  int cnt = 0; 
  
  for (i = 0; i < len; i++) {
    cnt++; 
    C0 += pdu_ptr[i];
    C1 += C0;
    if (cnt == MAX_CHECK_ITER)
      {
	C0 = (C0 % MOD_VAL);
	C1 = (C1 % MOD_VAL);
	cnt = 0;
      }
  }
  
  C0 = (C0 % MOD_VAL);
  C1 = (C1 % MOD_VAL);
  
  if ( (C0 != 0) || (C1 != 0))
    return (1);
  else
    return (0);
  
}


/*
 * %(Copyright)
 * %(Copyright.ISIS)
 */
