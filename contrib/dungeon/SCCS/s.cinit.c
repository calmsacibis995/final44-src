h13456
s 00065/00000/00000
d D 5.1 88/10/20 18:34:54 bostic 1 0
c from UUNET; applied patches 1-3
e
u
U
t
T
I 1
#include <stdio.h>


/*	read one integer from the open file */
intrd_(valptr)

int *valptr;
{
	scanf("%d",valptr);
	while((getchar() != '\n'));
	return;
}

/*	read an array from the open file */
aryrd_(cntptr,aryptr)

int *cntptr,*aryptr[];
{
	int i;

	for(i = *cntptr; i > 0;--i,++aryptr)
		scanf("%d",aryptr);
	while((getchar() != '\n'));
	return;
}

/* get a logical value */
logrd_(ptr)
int *ptr;
{
static char byte;

	*ptr = 0;
	while((byte = getchar()) != '\n'){
		if ((byte == 'T') || (byte == 't'))
			*ptr = 1;
	}
	return;
}


/* wait for end of init flag */
initnd_()
{
	static int chr;

	while ((chr = getchar()) != '?'){	/* wait for end flag */
		if (chr == 'R')		/* check for restore flag */
			rstrgm_();	/* call restore routine  */
	}
	return;
}

/*	write an array to the open pipe */
arywt_(cntptr,aryptr)

int *cntptr,*aryptr[];
{
	static int i;

	for(i = *cntptr; i > 0;--i,++aryptr)
		printf("%d\n",*aryptr);
	return;
}

E 1
