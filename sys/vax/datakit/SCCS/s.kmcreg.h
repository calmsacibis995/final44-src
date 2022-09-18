h49371
s 00001/00001/00024
d D 1.2 89/08/15 18:43:36 karels 2 1
c current version from monet
e
s 00025/00000/00000
d D 1.1 89/08/15 18:32:13 karels 1 0
c kmcreg.h.old from monet
e
u
U
t
T
I 1
/*	@(#)kmc.h	1.1	*/
#define	KSTEP	1
#define	KMS	2
#define	KCSR	3
#define	KSTOP	4
#define	KMCLR	5
#define	KRUN	6
#define	KLU	7
#define	KWRCR	8
#define	KRESET	9

struct kmcntl {
	int	kmd;
	short	*kcsr;
	int	kval;
};

#include <sys/ioctl.h>

D 2
#define	KCSETA	_IOW(k, 1, struct kmcntl)
E 2
I 2
#define	KCSETA	_IOW('k', 1, struct kmcntl)
E 2

#define	lobyte(X)	(((unsigned char *)&X)[0])
#define	hibyte(X)	(((unsigned char *)&X)[1])
#define	loword(X)	(((ushort *)&X)[0])
#define	hiword(X)	(((ushort *)&X)[1])
E 1
