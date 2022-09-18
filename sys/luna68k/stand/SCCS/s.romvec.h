h35484
s 00002/00002/00090
d D 8.1 93/06/10 22:29:56 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00065/00070/00027
d D 7.2 93/01/20 09:16:10 akito 2 1
c added frame entry
e
s 00097/00000/00000
d D 7.1 92/12/13 03:50:23 akito 1 0
c date and time created 92/12/13 03:50:23 by akito
e
u
U
t
T
I 1
/*
 * Copyright (c) 1992 OMRON Corporation.
D 3
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * This code is derived from software contributed to Berkeley by
 * OMRON Corporation.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/* romvec.h Oct-22-1991 */


#define RVPtr	((struct romvec *) 0x41000000)

#define ROM_memsize	(*((int *) *RVPtr->vec03))
#define	ROM_getchar	(*RVPtr->vec06)
#define	ROM_putchar	(*RVPtr->vec07)
#define	ROM_abort	(*RVPtr->vec25)
I 2
#define ROM_plane	(*((int *) *RVPtr->vec46))
E 2

struct romvec {
D 2
    int     (*vec00)();    /* 00 - Cold Boot Entry */
    int     (*vec01)();    /* 01 */
    int     (*vec02)();    /* 02 */
    int     (*vec03)();    /* 03 - memsize : Memory Size */
    int     (*vec04)();    /* 04 */
    int     (*vec05)();    /* 05 */
    int     (*vec06)();    /* 06 - getchar : get 1 charactor from console	*/
    int     (*vec07)();    /* 07 - putchar : put 1 charactor to console		*/
    int     (*vec08)();    /* 08 */
    int     (*vec09)();    /* 09 */
    int     (*vec10)();    /* 10 */
    int     (*vec11)();    /* 11 */
    int     (*vec12)();    /* 12 */
    int     (*vec13)();    /* 13 */
    int     (*vec14)();    /* 14 */
    int     (*vec15)();    /* 15 */
    int     (*vec16)();    /* 16 */
    int     (*vec17)();    /* 17 */
    int     (*vec18)();    /* 18 */
    int     (*vec19)();    /* 19 */
    int     (*vec20)();    /* 20 */
    int     (*vec21)();    /* 21 */
    int     (*vec22)();    /* 22 */
    int     (*vec23)();    /* 23 */
    int     (*vec24)();    /* 24 */
    int     (*vec25)();    /* 25 - abort : back to ROM Monitor */
    int     (*vec26)();    /* 26 */
    int     (*vec27)();    /* 27 */
    int     (*vec28)();    /* 28 */
    int     (*vec29)();    /* 29 */
    int     (*vec30)();    /* 30 */
    int     (*vec31)();    /* 31 */
    int     (*vec32)();    /* 32 */
    int     (*vec33)();    /* 33 */
    int     (*vec34)();    /* 34 */
    int     (*vec35)();    /* 35 */
    int     (*vec36)();    /* 36 */
    int     (*vec37)();    /* 37 */
    int     (*vec38)();    /* 38 */
    int     (*vec39)();    /* 39 */
    int     (*vec40)();    /* 40 */
    int     (*vec41)();    /* 41 */
    int     (*vec42)();    /* 42 */
    int     (*vec43)();    /* 43 */
    int     (*vec44)();    /* 44 */
    int     (*vec45)();    /* 45 */
    int     (*vec46)();    /* 46 */
    int     (*vec47)();    /* 47 */
    int     (*vec48)();    /* 48 */
    int     (*vec49)();    /* 49 */
    int     (*vec50)();    /* 50 */
    int     (*vec51)();    /* 51 */
    int     (*vec52)();    /* 52 */
    int     (*vec53)();    /* 53 */
    int     (*vec54)();    /* 54 */
    int     (*vec55)();    /* 55 */
    int     (*vec56)();    /* 56 */
    int     (*vec57)();    /* 57 */
    int     (*vec58)();    /* 58 */
    int     (*vec59)();    /* 59 */
    int     (*vec60)();    /* 60 */
    int     (*vec61)();    /* 61 */
    int     (*vec62)();    /* 62 */
    int     (*vec63)();    /* 63 */
    int     (*vec64)();    /* 64 */
    int     (*vec65)();    /* 65 */
    int     (*vec66)();    /* 66 */
    int     (*vec67)();    /* 67 */
    int     (*vec68)();    /* 68 */
    int     (*vec69)();    /* 69 */
E 2
I 2
    int     (*vec00)();    /* 00 [00] - Cold Boot Entry */
    int     (*vec01)();    /* 01 [04] */
    int     (*vec02)();    /* 02 [08] */
    int     (*vec03)();    /* 03 [0C] - memsize : Memory Size */
    int     (*vec04)();    /* 04 [10] */
    int     (*vec05)();    /* 05 [14] */
    int     (*vec06)();    /* 06 [18] - getchar : get 1 charactor from console	*/
    int     (*vec07)();    /* 07 [1C] - putchar : put 1 charactor to console		*/
    int     (*vec08)();    /* 08 [20] */
    int     (*vec09)();    /* 09 [24] */
    int     (*vec10)();    /* 10 [28] */
    int     (*vec11)();    /* 11 [2C] */
    int     (*vec12)();    /* 12 [30] */
    int     (*vec13)();    /* 13 [34] */
    int     (*vec14)();    /* 14 [38] */
    int     (*vec15)();    /* 15 [3C] */
    int     (*vec16)();    /* 16 [40] */
    int     (*vec17)();    /* 17 [44] */
    int     (*vec18)();    /* 18 [48] */
    int     (*vec19)();    /* 19 [4C] */
    int     (*vec20)();    /* 20 [50] */
    int     (*vec21)();    /* 21 [54] */
    int     (*vec22)();    /* 22 [58] */
    int     (*vec23)();    /* 23 [5C] */
    int     (*vec24)();    /* 24 [60] */
    int     (*vec25)();    /* 25 [64] - abort : back to ROM Monitor */
    int     (*vec26)();    /* 26 [68] */
    int     (*vec27)();    /* 27 [6C] */
    int     (*vec28)();    /* 28 [70] */
    int     (*vec29)();    /* 29 [74] */
    int     (*vec30)();    /* 30 [78] */
    int     (*vec31)();    /* 31 [7C] */
    int     (*vec32)();    /* 32 [80] */
    int     (*vec33)();    /* 33 [84] */
    int     (*vec34)();    /* 34 [88] */
    int     (*vec35)();    /* 35 [8C] */
    int     (*vec36)();    /* 36 [90] */
    int     (*vec37)();    /* 37 [94] */
    int     (*vec38)();    /* 38 [98] */
    int     (*vec39)();    /* 39 [9C] */
    int     (*vec40)();    /* 40 [A0] */
    int     (*vec41)();    /* 41 [A4] */
    int     (*vec42)();    /* 42 [A8] */
    int     (*vec43)();    /* 43 [AC] */
    int     (*vec44)();    /* 44 [B0] */
    int     (*vec45)();    /* 45 [B4] */
    int     (*vec46)();    /* 46 [B8] -- number of plane */
    int     (*vec47)();    /* 47 [BC] */
    int     (*vec48)();    /* 48 [C0] */
    int     (*vec49)();    /* 49 [C4] */
    int     (*vec50)();    /* 50 [C8] */
    int     (*vec51)();    /* 51 [CC] */
    int     (*vec52)();    /* 52 [D0] */
    int     (*vec53)();    /* 53 [D4] */
    int     (*vec54)();    /* 54 [D8] */
    int     (*vec55)();    /* 55 [DC] */
    int     (*vec56)();    /* 56 [E0] */
    int     (*vec57)();    /* 57 [E4] */
    int     (*vec58)();    /* 58 [E8] */
    int     (*vec59)();    /* 59 [EC] */
    int     (*vec60)();    /* 60 [F0] */
    int     (*vec61)();    /* 61 [F4] */
    int     (*vec62)();    /* 62 [F8] */
    int     (*vec63)();    /* 63 [FC] */
E 2
};


E 1
