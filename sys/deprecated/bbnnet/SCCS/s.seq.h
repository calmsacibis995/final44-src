h33277
s 00011/00000/00000
d D 1.1 85/10/14 18:14:45 karels 1 0
c from BBN
e
u
U
t
T
I 1

/* macros for sequence number comparison (32 bit modular arithmetic) */
#define SEQ_LT(a,b)	((long)((a)-(b)) < 0)
#define SEQ_LEQ(a,b)	((long)((a)-(b)) <= 0)
#define SEQ_GT(a,b)	((long)((a)-(b)) > 0)
#define SEQ_GEQ(a,b)	((long)((a)-(b)) >= 0)
#define SEQ_EQ(a,b)	((a) == (b))
#define SEQ_NEQ(a,b)	((a) != (b))
#define SEQ_MIN(a,b)	(SEQ_LT((a),(b)) ? (a) : (b))
#define SEQ_MAX(a,b)	(SEQ_GT((a),(b)) ? (a) : (b))

E 1
