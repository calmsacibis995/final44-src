h19177
s 00049/00000/00000
d D 7.1 90/04/24 19:57:04 william 1 0
c date and time created 90/04/24 19:57:04 by william
e
u
U
t
T
I 1
/*-
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * William Jolitz.
 *
 * %sccs.include.noredist.c%
 *
 *	%W% (Berkeley) %G%
 */

/*
 * Scan physical memory and talley, bypassing AT devices/roms
 */
#define	CHK	4096
main() {
	long base;
	register long val;

	base = 0;
	do {
		printf("0x%X - ", base);
		for ( ;; base+= CHK) {
			if (base >= 0xa0000 && base <= 0xe0000) break;
			if (base >= 0xfffff000) break;
			val = *((long *) base);
			*((long *) base) = base*4 + 0x55555555;
			if (*((long *) base) != base*4 + 0x55555555) {
				*((long *) base) = val ;
				break;
			}
			*((long *) base) = val ;
		}
		printf("0x%X\n", base-CHK) ;
		for ( ;; base+= CHK) {
			if (base >= 0xa0000 && base <= 0xe0000) continue ;
			if (base >= 0xfffff000) break;
			val = *((long *) base);
			*((long *) base) = base*4 + 0x55555555;
			if (*((long *) base) == base*4 + 0x55555555) {
				*((long *) base) = val ;
				break;
			}
		}
	} while (base < 0xfffff000); 
	printf("finished\n");
	getchar();
}
E 1
