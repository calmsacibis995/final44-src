h50015
s 00002/00002/00982
d D 8.1 93/06/11 15:13:41 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00395/00544/00589
d D 7.2 93/05/27 20:41:41 torek 2 1
c fully bracket those initializers (for gcc2 -W); make most symbols static
e
s 01133/00000/00000
d D 7.1 92/07/13 00:43:45 torek 1 0
c date and time created 92/07/13 00:43:45 by torek
e
u
U
t
T
I 1
/*
D 3
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * This code is derived from software contributed to the Computer Systems
 * Engineering Group at Lawrence Berkeley Laboratory and to the University
 * of California at Berkeley by Jef Poskanzer.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *
D 2
 * from: $Header: raster_text.c,v 1.15 92/06/17 08:14:45 torek Exp $
E 2
I 2
 * from: $Header: gallant19.h,v 1.3 93/05/28 03:40:36 torek Exp $
E 2
 */

D 2
u_long gallant19_32_pixels[] = {
E 2
I 2
static u_long gallant19_32_pixels[] = {
E 2
    0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x000018c0, 0x000003c0, 0x000030c0,
    0x000030c0, 0x00001ee0, 0x00000000, 0x00000000, 0x00002000, 0x0000e000,
    0x00006000, 0x00006fc0, 0x00006060, 0x00006060, 0x00007060, 0x00004f80,
    0x00000000, 0x00000000, 0x00000000
D 2
    };
struct raster gallant19_32 = { 12, 22, 1, 1, gallant19_32_pixels, 0 };
E 2
I 2
};
static struct raster gallant19_32 = { 12, 22, 1, 1, gallant19_32_pixels, 0 };
E 2

D 2
u_long gallant19_33_pixels[] = {
E 2
I 2
static u_long gallant19_33_pixels[] = {
E 2
    0x00000000,
    0x06000000, 0x06000000, 0x06000060, 0x06000060, 0x06000060, 0x060031e0,
    0x06006060, 0x06006060, 0x060070e0, 0x06001e70, 0x06000000, 0x00000000,
    0x00000000, 0x06000000, 0x06000000, 0x000030c0, 0x00006060, 0x00006000,
    0x00003000, 0x00000f80, 0x00000000
D 2
    };
struct raster gallant19_33 = { 12, 22, 1, 1, gallant19_33_pixels, 0 };
E 2
I 2
};
static struct raster gallant19_33 = { 12, 22, 1, 1, gallant19_33_pixels, 0 };
E 2

D 2
u_long gallant19_34_pixels[] = {
E 2
I 2
static u_long gallant19_34_pixels[] = {
E 2
    0x00000000,
    0x19800c00, 0x19801e00, 0x19800000, 0x19800000, 0x19800000, 0x19800000,
    0x00000000, 0x000031e0, 0x000060c0, 0x00003180, 0x00006000, 0x00003fe0,
    0x00004020, 0x00007fc0, 0x00001000, 0x00007000, 0x00003000, 0x000039c0,
    0x000030c0, 0x000030c0, 0x00000000
D 2
    };
struct raster gallant19_34 = { 12, 22, 1, 1, gallant19_34_pixels, 0 };
E 2
I 2
};
static struct raster gallant19_34 = { 12, 22, 1, 1, gallant19_34_pixels, 0 };
E 2

D 2
u_long gallant19_35_pixels[] = {
E 2
I 2
static u_long gallant19_35_pixels[] = {
E 2
    0x00000000,
    0x03300600, 0x03300600, 0x03300600, 0x06601f80, 0x1ff00000, 0x1ff00000,
    0x0cc00000, 0x0cc000c0, 0x19800000, 0x198000c0, 0x7fc000c0, 0x7fc000c0,
    0x330000c0, 0x660000c0, 0x660030c0, 0x00001f00, 0x00006000, 0x00006000,
    0x00006000, 0x00006300, 0x00000000
D 2
    };
struct raster gallant19_35 = { 12, 22, 1, 1, gallant19_35_pixels, 0 };
E 2
I 2
};
static struct raster gallant19_35 = { 12, 22, 1, 1, gallant19_35_pixels, 0 };
E 2

D 2
u_long gallant19_36_pixels[] = {
E 2
I 2
static u_long gallant19_36_pixels[] = {
E 2
    0x00000000,
    0x06000600, 0x1f800600, 0x3fc00600, 0x66e00600, 0x66600600, 0x66001f80,
    0x3e000000, 0x1f800000, 0x07c00000, 0x06600000, 0x06600000, 0x66606ee0,
    0x7fc06660, 0x3f806660, 0x06006660, 0x0000ef70, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000
D 2
    };
struct raster gallant19_36 = { 12, 22, 1, 1, gallant19_36_pixels, 0 };
E 2
I 2
};
static struct raster gallant19_36 = { 12, 22, 1, 1, gallant19_36_pixels, 0 };
E 2

D 2
u_long gallant19_37_pixels[] = {
E 2
I 2
static u_long gallant19_37_pixels[] = {
E 2
    0x00000000,
    0x38600000, 0x44c00000, 0x44c00000, 0x458011c0, 0x39806060, 0x03006060,
    0x03007040, 0x06001f00, 0x0c000000, 0x0c000000, 0x19c00000, 0x1a200000,
    0x32200000, 0x322071c0, 0x61c06060, 0x00006060, 0x00006040, 0x00007f00,
    0x00006000, 0x00006000, 0x00000000
D 2
    };
struct raster gallant19_37 = { 12, 22, 1, 1, gallant19_37_pixels, 0 };
E 2
I 2
};
static struct raster gallant19_37 = { 12, 22, 1, 1, gallant19_37_pixels, 0 };
E 2

D 2
u_long gallant19_38_pixels[] = {
E 2
I 2
static u_long gallant19_38_pixels[] = {
E 2
    0x00000000,
    0x07000060, 0x0f800060, 0x18c00000, 0x18c00000, 0x18c00000, 0x0f8034c0,
    0x1e003000, 0x3e003000, 0x77003000, 0x63607800, 0x61e00000, 0x61c00000,
    0x61800000, 0x3fe00000, 0x1e600000, 0x000030c0, 0x00003800, 0x00000780,
    0x000020c0, 0x00003f80, 0x00000000
D 2
    };
struct raster gallant19_38 = { 12, 22, 1, 1, gallant19_38_pixels, 0 };
E 2
I 2
};
static struct raster gallant19_38 = { 12, 22, 1, 1, gallant19_38_pixels, 0 };
E 2

D 2
u_long gallant19_39_pixels[] = {
E 2
I 2
static u_long gallant19_39_pixels[] = {
E 2
    0x00000000,
    0x0c000c20, 0x1e000780, 0x1e000000, 0x06000000, 0x06000000, 0x0c000000,
    0x18000000, 0x100030c0, 0x000030c0, 0x000030c0, 0x000030c0, 0x00001e60,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00006020,
    0x00003040, 0x00001880, 0x00000000
D 2
    };
struct raster gallant19_39 = { 12, 22, 1, 1, gallant19_39_pixels, 0 };
E 2
I 2
};
static struct raster gallant19_39 = { 12, 22, 1, 1, gallant19_39_pixels, 0 };
E 2

D 2
u_long gallant19_40_pixels[] = {
E 2
I 2
static u_long gallant19_40_pixels[] = {
E 2
    0x00000000,
    0x00c06620, 0x01803b40, 0x03801980, 0x03001980, 0x07000000, 0x06000000,
    0x06000000, 0x06000000, 0x06000000, 0x06007040, 0x07001d00, 0x03000700,
    0x038011c0, 0x0180f1f0, 0x00c00000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00006020, 0x00000000
D 2
    };
struct raster gallant19_40 = { 12, 22, 1, 1, gallant19_40_pixels, 0 };
E 2
I 2
};
static struct raster gallant19_40 = { 12, 22, 1, 1, gallant19_40_pixels, 0 };
E 2

D 2
u_long gallant19_41_pixels[] = {
E 2
I 2
static u_long gallant19_41_pixels[] = {
E 2
    0x00000000,
    0x30000000, 0x180060e0, 0x1c000380, 0x0c000e00, 0x0e003820, 0x06007fe0,
    0x06000000, 0x06000000, 0x060001c0, 0x06000300, 0x0e000180, 0x0c000300,
    0x1c000300, 0x18000180, 0x30000300, 0x000001c0, 0x00000000, 0x00000000,
    0x00000600, 0x00000600, 0x00000000
D 2
    };
struct raster gallant19_41 = { 12, 22, 1, 1, gallant19_41_pixels, 0 };
E 2
I 2
};
static struct raster gallant19_41 = { 12, 22, 1, 1, gallant19_41_pixels, 0 };
E 2

D 2
u_long gallant19_42_pixels[] = {
E 2
I 2
static u_long gallant19_42_pixels[] = {
E 2
    0x00000000,
    0x00003800, 0x00000c00, 0x00001800, 0x00000c00, 0x0f000c00, 0x06001800,
    0x66600c00, 0x76e03800, 0x19800000, 0x00000000, 0x19800000, 0x76e00000,
    0x66600000, 0x06000000, 0x0f001c20, 0x000036c0, 0x00004380, 0x00000000,
    0x00000000, 0x00000000, 0x00000000
D 2
    };
struct raster gallant19_42 = { 12, 22, 1, 1, gallant19_42_pixels, 0 };
E 2
I 2
};
static struct raster gallant19_42 = { 12, 22, 1, 1, gallant19_42_pixels, 0 };
E 2

D 2
u_long gallant19_43_pixels[] = {
E 2
I 2
static u_long gallant19_43_pixels[] = {
E 2
    0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x06000000,
    0x06000000, 0x06000000, 0x06000000, 0x7fe00000, 0x7fe00000, 0x06000000,
    0x06000000, 0x06000000, 0x06000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000
D 2
    };
struct raster gallant19_43 = { 12, 22, 1, 1, gallant19_43_pixels, 0 };
E 2
I 2
};
static struct raster gallant19_43 = { 12, 22, 1, 1, gallant19_43_pixels, 0 };
E 2

D 2
u_long gallant19_44_pixels[] = {
E 2
I 2
static u_long gallant19_44_pixels[] = {
E 2
    0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x0c000000, 0x1e000000, 0x1e000000, 0x06000000, 0x06000000, 0x0c000000,
    0x18000000, 0x10000000, 0x00000000
D 2
    };
struct raster gallant19_44 = { 12, 22, 1, 1, gallant19_44_pixels, 0 };
E 2
I 2
};
static struct raster gallant19_44 = { 12, 22, 1, 1, gallant19_44_pixels, 0 };
E 2

D 2
u_long gallant19_45_pixels[] = {
E 2
I 2
static u_long gallant19_45_pixels[] = {
E 2
    0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x7fe00000, 0x7fe00000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000
D 2
    };
struct raster gallant19_45 = { 12, 22, 1, 1, gallant19_45_pixels, 0 };
E 2
I 2
};
static struct raster gallant19_45 = { 12, 22, 1, 1, gallant19_45_pixels, 0 };
E 2

D 2
u_long gallant19_46_pixels[] = {
E 2
I 2
static u_long gallant19_46_pixels[] = {
E 2
    0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x0c000000,
    0x1e000000, 0x1e000000, 0x0c000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000
D 2
    };
struct raster gallant19_46 = { 12, 22, 1, 1, gallant19_46_pixels, 0 };
E 2
I 2
};
static struct raster gallant19_46 = { 12, 22, 1, 1, gallant19_46_pixels, 0 };
E 2

D 2
u_long gallant19_47_pixels[] = {
E 2
I 2
static u_long gallant19_47_pixels[] = {
E 2
    0x00000000,
    0x00600000, 0x00c00000, 0x00c00000, 0x01800000, 0x01800000, 0x03000000,
    0x03000000, 0x06000000, 0x0c000000, 0x0c000000, 0x18000000, 0x18000000,
    0x30000000, 0x30000000, 0x60000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000
D 2
    };
struct raster gallant19_47 = { 12, 22, 1, 1, gallant19_47_pixels, 0 };
E 2
I 2
};
static struct raster gallant19_47 = { 12, 22, 1, 1, gallant19_47_pixels, 0 };
E 2

D 2
u_long gallant19_48_pixels[] = {
E 2
I 2
static u_long gallant19_48_pixels[] = {
E 2
    0x00000000,
    0x07000000, 0x0f800000, 0x11800000, 0x10c00000, 0x30c00000, 0x30c00000,
    0x30c00000, 0x30c00000, 0x30c00000, 0x30c00000, 0x30c00000, 0x30800000,
    0x18800000, 0x1f000000, 0x0e000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000
D 2
    };
struct raster gallant19_48 = { 12, 22, 1, 1, gallant19_48_pixels, 0 };
E 2
I 2
};
static struct raster gallant19_48 = { 12, 22, 1, 1, gallant19_48_pixels, 0 };
E 2

D 2
u_long gallant19_49_pixels[] = {
E 2
I 2
static u_long gallant19_49_pixels[] = {
E 2
    0x00000000,
    0x02000000, 0x06000000, 0x0e000000, 0x1e000000, 0x36000000, 0x06000000,
    0x06000000, 0x06000000, 0x06000000, 0x06000000, 0x06000000, 0x06000000,
    0x06000000, 0x06000000, 0x3fc00000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000
D 2
    };
struct raster gallant19_49 = { 12, 22, 1, 1, gallant19_49_pixels, 0 };
E 2
I 2
};
static struct raster gallant19_49 = { 12, 22, 1, 1, gallant19_49_pixels, 0 };
E 2

D 2
u_long gallant19_50_pixels[] = {
E 2
I 2
static u_long gallant19_50_pixels[] = {
E 2
    0x00000000,
    0x1f000000, 0x3f800000, 0x61c00000, 0x40c00000, 0x00c00000, 0x00c00000,
    0x00c00000, 0x01800000, 0x03000000, 0x06000000, 0x0c000000, 0x18000000,
    0x30200000, 0x7fe00000, 0x7fe00000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000
D 2
    };
struct raster gallant19_50 = { 12, 22, 1, 1, gallant19_50_pixels, 0 };
E 2
I 2
};
static struct raster gallant19_50 = { 12, 22, 1, 1, gallant19_50_pixels, 0 };
E 2

D 2
u_long gallant19_51_pixels[] = {
E 2
I 2
static u_long gallant19_51_pixels[] = {
E 2
    0x00000000,
    0x0f800000, 0x1fc00000, 0x20e00000, 0x40600000, 0x00600000, 0x00e00000,
    0x07c00000, 0x0fc00000, 0x00e00000, 0x00600000, 0x00600000, 0x40600000,
    0x60400000, 0x3f800000, 0x1f000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000
D 2
    };
struct raster gallant19_51 = { 12, 22, 1, 1, gallant19_51_pixels, 0 };
E 2
I 2
};
static struct raster gallant19_51 = { 12, 22, 1, 1, gallant19_51_pixels, 0 };
E 2

D 2
u_long gallant19_52_pixels[] = {
E 2
I 2
static u_long gallant19_52_pixels[] = {
E 2
    0x00000000,
    0x01800000, 0x03800000, 0x03800000, 0x05800000, 0x05800000, 0x09800000,
    0x09800000, 0x11800000, 0x11800000, 0x21800000, 0x3fe00000, 0x7fe00000,
    0x01800000, 0x01800000, 0x01800000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000
D 2
    };
struct raster gallant19_52 = { 12, 22, 1, 1, gallant19_52_pixels, 0 };
E 2
I 2
};
static struct raster gallant19_52 = { 12, 22, 1, 1, gallant19_52_pixels, 0 };
E 2

D 2
u_long gallant19_53_pixels[] = {
E 2
I 2
static u_long gallant19_53_pixels[] = {
E 2
    0x00000000,
    0x0fc00000, 0x0fc00000, 0x10000000, 0x10000000, 0x20000000, 0x3f800000,
    0x31c00000, 0x00e00000, 0x00600000, 0x00600000, 0x00600000, 0x40600000,
    0x60600000, 0x30c00000, 0x1f800000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000
D 2
    };
struct raster gallant19_53 = { 12, 22, 1, 1, gallant19_53_pixels, 0 };
E 2
I 2
};
static struct raster gallant19_53 = { 12, 22, 1, 1, gallant19_53_pixels, 0 };
E 2

D 2
u_long gallant19_54_pixels[] = {
E 2
I 2
static u_long gallant19_54_pixels[] = {
E 2
    0x00000000,
    0x07000000, 0x0c000000, 0x18000000, 0x30000000, 0x30000000, 0x60000000,
    0x67800000, 0x6fc00000, 0x70e00000, 0x60600000, 0x60600000, 0x60600000,
    0x70400000, 0x3f800000, 0x1f000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000
D 2
    };
struct raster gallant19_54 = { 12, 22, 1, 1, gallant19_54_pixels, 0 };
E 2
I 2
};
static struct raster gallant19_54 = { 12, 22, 1, 1, gallant19_54_pixels, 0 };
E 2

D 2
u_long gallant19_55_pixels[] = {
E 2
I 2
static u_long gallant19_55_pixels[] = {
E 2
    0x00000000,
    0x1fe00000, 0x3fe00000, 0x60400000, 0x00400000, 0x00c00000, 0x00800000,
    0x00800000, 0x01800000, 0x01000000, 0x01000000, 0x03000000, 0x02000000,
    0x02000000, 0x06000000, 0x04000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000
D 2
    };
struct raster gallant19_55 = { 12, 22, 1, 1, gallant19_55_pixels, 0 };
E 2
I 2
};
static struct raster gallant19_55 = { 12, 22, 1, 1, gallant19_55_pixels, 0 };
E 2

D 2
u_long gallant19_56_pixels[] = {
E 2
I 2
static u_long gallant19_56_pixels[] = {
E 2
    0x00000000,
    0x0f000000, 0x11800000, 0x30c00000, 0x30c00000, 0x30c00000, 0x18800000,
    0x0d000000, 0x06000000, 0x0b000000, 0x11800000, 0x30c00000, 0x30c00000,
    0x30c00000, 0x18800000, 0x0f000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000
D 2
    };
struct raster gallant19_56 = { 12, 22, 1, 1, gallant19_56_pixels, 0 };
E 2
I 2
};
static struct raster gallant19_56 = { 12, 22, 1, 1, gallant19_56_pixels, 0 };
E 2

D 2
u_long gallant19_57_pixels[] = {
E 2
I 2
static u_long gallant19_57_pixels[] = {
E 2
    0x00000000,
    0x0f800000, 0x11c00000, 0x20e00000, 0x60600000, 0x60600000, 0x60600000,
    0x70e00000, 0x3f600000, 0x1e600000, 0x00600000, 0x00c00000, 0x00c00000,
    0x01800000, 0x07000000, 0x3c000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000
D 2
    };
struct raster gallant19_57 = { 12, 22, 1, 1, gallant19_57_pixels, 0 };
E 2
I 2
};
static struct raster gallant19_57 = { 12, 22, 1, 1, gallant19_57_pixels, 0 };
E 2

D 2
u_long gallant19_58_pixels[] = {
E 2
I 2
static u_long gallant19_58_pixels[] = {
E 2
    0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x0c000000,
    0x1e000000, 0x1e000000, 0x0c000000, 0x00000000, 0x00000000, 0x0c000000,
    0x1e000000, 0x1e000000, 0x0c000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000
D 2
    };
struct raster gallant19_58 = { 12, 22, 1, 1, gallant19_58_pixels, 0 };
E 2
I 2
};
static struct raster gallant19_58 = { 12, 22, 1, 1, gallant19_58_pixels, 0 };
E 2

D 2
u_long gallant19_59_pixels[] = {
E 2
I 2
static u_long gallant19_59_pixels[] = {
E 2
    0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x0c000000, 0x1e000000, 0x1e000000, 0x0c000000, 0x00000000, 0x00000000,
    0x0c000000, 0x1e000000, 0x1e000000, 0x06000000, 0x06000000, 0x0c000000,
    0x18000000, 0x10000000, 0x00000000
D 2
    };
struct raster gallant19_59 = { 12, 22, 1, 1, gallant19_59_pixels, 0 };
E 2
I 2
};
static struct raster gallant19_59 = { 12, 22, 1, 1, gallant19_59_pixels, 0 };
E 2

D 2
u_long gallant19_60_pixels[] = {
E 2
I 2
static u_long gallant19_60_pixels[] = {
E 2
    0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00600000,
    0x01c00000, 0x07000000, 0x1e000000, 0x78000000, 0x78000000, 0x1e000000,
    0x07000000, 0x01c00000, 0x00600000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000
D 2
    };
struct raster gallant19_60 = { 12, 22, 1, 1, gallant19_60_pixels, 0 };
E 2
I 2
};
static struct raster gallant19_60 = { 12, 22, 1, 1, gallant19_60_pixels, 0 };
E 2

D 2
u_long gallant19_61_pixels[] = {
E 2
I 2
static u_long gallant19_61_pixels[] = {
E 2
    0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x7fc00000, 0x7fc00000, 0x00000000, 0x00000000, 0x7fc00000,
    0x7fc00000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000
D 2
    };
struct raster gallant19_61 = { 12, 22, 1, 1, gallant19_61_pixels, 0 };
E 2
I 2
};
static struct raster gallant19_61 = { 12, 22, 1, 1, gallant19_61_pixels, 0 };
E 2

D 2
u_long gallant19_62_pixels[] = {
E 2
I 2
static u_long gallant19_62_pixels[] = {
E 2
    0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x60000000,
    0x38000000, 0x1e000000, 0x07800000, 0x01e00000, 0x01e00000, 0x07800000,
    0x1e000000, 0x38000000, 0x60000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000
D 2
    };
struct raster gallant19_62 = { 12, 22, 1, 1, gallant19_62_pixels, 0 };
E 2
I 2
};
static struct raster gallant19_62 = { 12, 22, 1, 1, gallant19_62_pixels, 0 };
E 2

D 2
u_long gallant19_63_pixels[] = {
E 2
I 2
static u_long gallant19_63_pixels[] = {
E 2
    0x00000000,
    0x0f000000, 0x1f800000, 0x39c00000, 0x20c00000, 0x00c00000, 0x00c00000,
    0x01800000, 0x03000000, 0x06000000, 0x0c000000, 0x0c000000, 0x00000000,
    0x00000000, 0x0c000000, 0x0c000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000
D 2
    };
struct raster gallant19_63 = { 12, 22, 1, 1, gallant19_63_pixels, 0 };
E 2
I 2
};
static struct raster gallant19_63 = { 12, 22, 1, 1, gallant19_63_pixels, 0 };
E 2

D 2
u_long gallant19_64_pixels[] = {
E 2
I 2
static u_long gallant19_64_pixels[] = {
E 2
    0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x0f800000, 0x3fc00000, 0x30600000,
    0x60600000, 0x67200000, 0x6fa00000, 0x6ca00000, 0x6ca00000, 0x67e00000,
    0x60000000, 0x30000000, 0x3fe00000, 0x0fe00000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000
D 2
    };
struct raster gallant19_64 = { 12, 22, 1, 1, gallant19_64_pixels, 0 };
E 2
I 2
};
static struct raster gallant19_64 = { 12, 22, 1, 1, gallant19_64_pixels, 0 };
E 2

D 2
u_long gallant19_65_pixels[] = {
E 2
I 2
static u_long gallant19_65_pixels[] = {
E 2
    0x00000000,
    0x00000000, 0x06000000, 0x06000000, 0x0b000000, 0x0b000000, 0x09000000,
    0x11800000, 0x11800000, 0x10800000, 0x3fc00000, 0x20c00000, 0x20400000,
    0x40600000, 0x40600000, 0xe0f00000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000
D 2
    };
struct raster gallant19_65 = { 12, 22, 1, 1, gallant19_65_pixels, 0 };
E 2
I 2
};
static struct raster gallant19_65 = { 12, 22, 1, 1, gallant19_65_pixels, 0 };
E 2

D 2
u_long gallant19_66_pixels[] = {
E 2
I 2
static u_long gallant19_66_pixels[] = {
E 2
    0x00000000,
    0x00000000, 0xff000000, 0x60800000, 0x60c00000, 0x60c00000, 0x60c00000,
    0x61800000, 0x7f800000, 0x60c00000, 0x60600000, 0x60600000, 0x60600000,
    0x60600000, 0x60c00000, 0xff800000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000
D 2
    };
struct raster gallant19_66 = { 12, 22, 1, 1, gallant19_66_pixels, 0 };
E 2
I 2
};
static struct raster gallant19_66 = { 12, 22, 1, 1, gallant19_66_pixels, 0 };
E 2

D 2
u_long gallant19_67_pixels[] = {
E 2
I 2
static u_long gallant19_67_pixels[] = {
E 2
    0x00000000,
    0x00000000, 0x0fc00000, 0x10600000, 0x20200000, 0x20000000, 0x60000000,
    0x60000000, 0x60000000, 0x60000000, 0x60000000, 0x60000000, 0x20000000,
    0x30200000, 0x18400000, 0x0f800000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000
D 2
    };
struct raster gallant19_67 = { 12, 22, 1, 1, gallant19_67_pixels, 0 };
E 2
I 2
};
static struct raster gallant19_67 = { 12, 22, 1, 1, gallant19_67_pixels, 0 };
E 2

D 2
u_long gallant19_68_pixels[] = {
E 2
I 2
static u_long gallant19_68_pixels[] = {
E 2
    0x00000000,
    0x00000000, 0xff000000, 0x61c00000, 0x60c00000, 0x60600000, 0x60600000,
    0x60600000, 0x60600000, 0x60600000, 0x60600000, 0x60600000, 0x60600000,
    0x60400000, 0x61800000, 0xfe000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000
D 2
    };
struct raster gallant19_68 = { 12, 22, 1, 1, gallant19_68_pixels, 0 };
E 2
I 2
};
static struct raster gallant19_68 = { 12, 22, 1, 1, gallant19_68_pixels, 0 };
E 2

D 2
u_long gallant19_69_pixels[] = {
E 2
I 2
static u_long gallant19_69_pixels[] = {
E 2
    0x00000000,
    0x00000000, 0x7fc00000, 0x30400000, 0x30400000, 0x30000000, 0x30000000,
    0x30800000, 0x3f800000, 0x30800000, 0x30000000, 0x30000000, 0x30000000,
    0x30200000, 0x30200000, 0x7fe00000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000
D 2
    };
struct raster gallant19_69 = { 12, 22, 1, 1, gallant19_69_pixels, 0 };
E 2
I 2
};
static struct raster gallant19_69 = { 12, 22, 1, 1, gallant19_69_pixels, 0 };
E 2

D 2
u_long gallant19_70_pixels[] = {
E 2
I 2
static u_long gallant19_70_pixels[] = {
E 2
    0x00000000,
    0x00000000, 0x7fc00000, 0x30400000, 0x30400000, 0x30000000, 0x30000000,
    0x30800000, 0x3f800000, 0x30800000, 0x30000000, 0x30000000, 0x30000000,
    0x30000000, 0x30000000, 0x78000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000
D 2
    };
struct raster gallant19_70 = { 12, 22, 1, 1, gallant19_70_pixels, 0 };
E 2
I 2
};
static struct raster gallant19_70 = { 12, 22, 1, 1, gallant19_70_pixels, 0 };
E 2

D 2
u_long gallant19_71_pixels[] = {
E 2
I 2
static u_long gallant19_71_pixels[] = {
E 2
    0x00000000,
    0x00000000, 0x0fc00000, 0x10600000, 0x20200000, 0x20000000, 0x60000000,
    0x60000000, 0x60000000, 0x60000000, 0x61f00000, 0x60600000, 0x20600000,
    0x30600000, 0x18600000, 0x0f800000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000
D 2
    };
struct raster gallant19_71 = { 12, 22, 1, 1, gallant19_71_pixels, 0 };
E 2
I 2
};
static struct raster gallant19_71 = { 12, 22, 1, 1, gallant19_71_pixels, 0 };
E 2

D 2
u_long gallant19_72_pixels[] = {
E 2
I 2
static u_long gallant19_72_pixels[] = {
E 2
    0x00000000,
    0x00000000, 0xf0f00000, 0x60600000, 0x60600000, 0x60600000, 0x60600000,
    0x60600000, 0x7fe00000, 0x60600000, 0x60600000, 0x60600000, 0x60600000,
    0x60600000, 0x60600000, 0xf0f00000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000
D 2
    };
struct raster gallant19_72 = { 12, 22, 1, 1, gallant19_72_pixels, 0 };
E 2
I 2
};
static struct raster gallant19_72 = { 12, 22, 1, 1, gallant19_72_pixels, 0 };
E 2

D 2
u_long gallant19_73_pixels[] = {
E 2
I 2
static u_long gallant19_73_pixels[] = {
E 2
    0x00000000,
    0x00000000, 0x1f800000, 0x06000000, 0x06000000, 0x06000000, 0x06000000,
    0x06000000, 0x06000000, 0x06000000, 0x06000000, 0x06000000, 0x06000000,
    0x06000000, 0x06000000, 0x1f800000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000
D 2
    };
struct raster gallant19_73 = { 12, 22, 1, 1, gallant19_73_pixels, 0 };
E 2
I 2
};
static struct raster gallant19_73 = { 12, 22, 1, 1, gallant19_73_pixels, 0 };
E 2

D 2
u_long gallant19_74_pixels[] = {
E 2
I 2
static u_long gallant19_74_pixels[] = {
E 2
    0x00000000,
    0x00000000, 0x1f800000, 0x06000000, 0x06000000, 0x06000000, 0x06000000,
    0x06000000, 0x06000000, 0x06000000, 0x06000000, 0x06000000, 0x06000000,
    0x06000000, 0x06000000, 0x06000000, 0x06000000, 0x06000000, 0x04000000,
    0x38000000, 0x30000000, 0x00000000
D 2
    };
struct raster gallant19_74 = { 12, 22, 1, 1, gallant19_74_pixels, 0 };
E 2
I 2
};
static struct raster gallant19_74 = { 12, 22, 1, 1, gallant19_74_pixels, 0 };
E 2

D 2
u_long gallant19_75_pixels[] = {
E 2
I 2
static u_long gallant19_75_pixels[] = {
E 2
    0x00000000,
    0x00000000, 0xf0e00000, 0x61800000, 0x63000000, 0x66000000, 0x6c000000,
    0x78000000, 0x78000000, 0x7c000000, 0x6e000000, 0x67000000, 0x63800000,
    0x61c00000, 0x60e00000, 0xf0700000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000
D 2
    };
struct raster gallant19_75 = { 12, 22, 1, 1, gallant19_75_pixels, 0 };
E 2
I 2
};
static struct raster gallant19_75 = { 12, 22, 1, 1, gallant19_75_pixels, 0 };
E 2

D 2
u_long gallant19_76_pixels[] = {
E 2
I 2
static u_long gallant19_76_pixels[] = {
E 2
    0x00000000,
    0x00000000, 0x78000000, 0x30000000, 0x30000000, 0x30000000, 0x30000000,
    0x30000000, 0x30000000, 0x30000000, 0x30000000, 0x30000000, 0x30000000,
    0x30200000, 0x30200000, 0x7fe00000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000
D 2
    };
struct raster gallant19_76 = { 12, 22, 1, 1, gallant19_76_pixels, 0 };
E 2
I 2
};
static struct raster gallant19_76 = { 12, 22, 1, 1, gallant19_76_pixels, 0 };
E 2

D 2
u_long gallant19_77_pixels[] = {
E 2
I 2
static u_long gallant19_77_pixels[] = {
E 2
    0x00000000,
    0x00000000, 0xe0700000, 0x60e00000, 0x70e00000, 0x70e00000, 0x70e00000,
    0x59600000, 0x59600000, 0x59600000, 0x4d600000, 0x4e600000, 0x4e600000,
    0x44600000, 0x44600000, 0xe4f00000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000
D 2
    };
struct raster gallant19_77 = { 12, 22, 1, 1, gallant19_77_pixels, 0 };
E 2
I 2
};
static struct raster gallant19_77 = { 12, 22, 1, 1, gallant19_77_pixels, 0 };
E 2

D 2
u_long gallant19_78_pixels[] = {
E 2
I 2
static u_long gallant19_78_pixels[] = {
E 2
    0x00000000,
    0x00000000, 0xc0700000, 0x60200000, 0x70200000, 0x78200000, 0x58200000,
    0x4c200000, 0x46200000, 0x47200000, 0x43200000, 0x41a00000, 0x40e00000,
    0x40e00000, 0x40600000, 0xe0300000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000
D 2
    };
struct raster gallant19_78 = { 12, 22, 1, 1, gallant19_78_pixels, 0 };
E 2
I 2
};
static struct raster gallant19_78 = { 12, 22, 1, 1, gallant19_78_pixels, 0 };
E 2

D 2
u_long gallant19_79_pixels[] = {
E 2
I 2
static u_long gallant19_79_pixels[] = {
E 2
    0x00000000,
    0x00000000, 0x0f000000, 0x11c00000, 0x20c00000, 0x20600000, 0x60600000,
    0x60600000, 0x60600000, 0x60600000, 0x60600000, 0x60600000, 0x20400000,
    0x30400000, 0x18800000, 0x0f000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000
D 2
    };
struct raster gallant19_79 = { 12, 22, 1, 1, gallant19_79_pixels, 0 };
E 2
I 2
};
static struct raster gallant19_79 = { 12, 22, 1, 1, gallant19_79_pixels, 0 };
E 2

D 2
u_long gallant19_80_pixels[] = {
E 2
I 2
static u_long gallant19_80_pixels[] = {
E 2
    0x00000000,
    0x00000000, 0x7f800000, 0x30c00000, 0x30600000, 0x30600000, 0x30600000,
    0x30c00000, 0x37800000, 0x30000000, 0x30000000, 0x30000000, 0x30000000,
    0x30000000, 0x30000000, 0x78000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000
D 2
    };
struct raster gallant19_80 = { 12, 22, 1, 1, gallant19_80_pixels, 0 };
E 2
I 2
};
static struct raster gallant19_80 = { 12, 22, 1, 1, gallant19_80_pixels, 0 };
E 2

D 2
u_long gallant19_81_pixels[] = {
E 2
I 2
static u_long gallant19_81_pixels[] = {
E 2
    0x00000000,
    0x00000000, 0x0f000000, 0x11c00000, 0x20c00000, 0x20600000, 0x60600000,
    0x60600000, 0x60600000, 0x60600000, 0x60600000, 0x60600000, 0x30400000,
    0x38400000, 0x1f800000, 0x0e000000, 0x1f000000, 0x23900000, 0x01e00000,
    0x00000000, 0x00000000, 0x00000000
D 2
    };
struct raster gallant19_81 = { 12, 22, 1, 1, gallant19_81_pixels, 0 };
E 2
I 2
};
static struct raster gallant19_81 = { 12, 22, 1, 1, gallant19_81_pixels, 0 };
E 2

D 2
u_long gallant19_82_pixels[] = {
E 2
I 2
static u_long gallant19_82_pixels[] = {
E 2
    0x00000000,
    0x00000000, 0xff000000, 0x61800000, 0x60c00000, 0x60c00000, 0x60c00000,
    0x60800000, 0x7f000000, 0x7c000000, 0x6e000000, 0x67000000, 0x63800000,
    0x61c00000, 0x60e00000, 0xf0700000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000
D 2
    };
struct raster gallant19_82 = { 12, 22, 1, 1, gallant19_82_pixels, 0 };
E 2
I 2
};
static struct raster gallant19_82 = { 12, 22, 1, 1, gallant19_82_pixels, 0 };
E 2

D 2
u_long gallant19_83_pixels[] = {
E 2
I 2
static u_long gallant19_83_pixels[] = {
E 2
    0x00000000,
    0x00000000, 0x1fe00000, 0x30600000, 0x60200000, 0x60200000, 0x70000000,
    0x3c000000, 0x1e000000, 0x07800000, 0x01c00000, 0x00e00000, 0x40600000,
    0x40600000, 0x60c00000, 0x7f800000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000
D 2
    };
struct raster gallant19_83 = { 12, 22, 1, 1, gallant19_83_pixels, 0 };
E 2
I 2
};
static struct raster gallant19_83 = { 12, 22, 1, 1, gallant19_83_pixels, 0 };
E 2

D 2
u_long gallant19_84_pixels[] = {
E 2
I 2
static u_long gallant19_84_pixels[] = {
E 2
    0x00000000,
    0x00000000, 0x7fe00000, 0x46200000, 0x06000000, 0x06000000, 0x06000000,
    0x06000000, 0x06000000, 0x06000000, 0x06000000, 0x06000000, 0x06000000,
    0x06000000, 0x06000000, 0x1f800000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000
D 2
    };
struct raster gallant19_84 = { 12, 22, 1, 1, gallant19_84_pixels, 0 };
E 2
I 2
};
static struct raster gallant19_84 = { 12, 22, 1, 1, gallant19_84_pixels, 0 };
E 2

D 2
u_long gallant19_85_pixels[] = {
E 2
I 2
static u_long gallant19_85_pixels[] = {
E 2
    0x00000000,
    0x00000000, 0xf0700000, 0x60200000, 0x60200000, 0x60200000, 0x60200000,
    0x60200000, 0x60200000, 0x60200000, 0x60200000, 0x60200000, 0x60200000,
    0x70400000, 0x3fc00000, 0x1f800000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000
D 2
    };
struct raster gallant19_85 = { 12, 22, 1, 1, gallant19_85_pixels, 0 };
E 2
I 2
};
static struct raster gallant19_85 = { 12, 22, 1, 1, gallant19_85_pixels, 0 };
E 2

D 2
u_long gallant19_86_pixels[] = {
E 2
I 2
static u_long gallant19_86_pixels[] = {
E 2
    0x00000000,
    0x00000000, 0xe0e00000, 0x60400000, 0x30800000, 0x30800000, 0x30800000,
    0x19000000, 0x19000000, 0x19000000, 0x0c000000, 0x0e000000, 0x0e000000,
    0x04000000, 0x04000000, 0x04000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000
D 2
    };
struct raster gallant19_86 = { 12, 22, 1, 1, gallant19_86_pixels, 0 };
E 2
I 2
};
static struct raster gallant19_86 = { 12, 22, 1, 1, gallant19_86_pixels, 0 };
E 2

D 2
u_long gallant19_87_pixels[] = {
E 2
I 2
static u_long gallant19_87_pixels[] = {
E 2
    0x00000000,
    0x00000000, 0xfef00000, 0x66200000, 0x66200000, 0x66200000, 0x76200000,
    0x77400000, 0x33400000, 0x37400000, 0x3bc00000, 0x3b800000, 0x19800000,
    0x19800000, 0x19800000, 0x19800000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000
D 2
    };
struct raster gallant19_87 = { 12, 22, 1, 1, gallant19_87_pixels, 0 };
E 2
I 2
};
static struct raster gallant19_87 = { 12, 22, 1, 1, gallant19_87_pixels, 0 };
E 2

D 2
u_long gallant19_88_pixels[] = {
E 2
I 2
static u_long gallant19_88_pixels[] = {
E 2
    0x00000000,
    0x00000000, 0xf0700000, 0x60200000, 0x30400000, 0x38800000, 0x18800000,
    0x0d000000, 0x06000000, 0x06000000, 0x0b000000, 0x11800000, 0x11c00000,
    0x20c00000, 0x40600000, 0xe0f00000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000
D 2
    };
struct raster gallant19_88 = { 12, 22, 1, 1, gallant19_88_pixels, 0 };
E 2
I 2
};
static struct raster gallant19_88 = { 12, 22, 1, 1, gallant19_88_pixels, 0 };
E 2

D 2
u_long gallant19_89_pixels[] = {
E 2
I 2
static u_long gallant19_89_pixels[] = {
E 2
    0x00000000,
    0x00000000, 0xf0700000, 0x60200000, 0x30400000, 0x18800000, 0x18800000,
    0x0d000000, 0x06000000, 0x06000000, 0x06000000, 0x06000000, 0x06000000,
    0x06000000, 0x06000000, 0x0f000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000
D 2
    };
struct raster gallant19_89 = { 12, 22, 1, 1, gallant19_89_pixels, 0 };
E 2
I 2
};
static struct raster gallant19_89 = { 12, 22, 1, 1, gallant19_89_pixels, 0 };
E 2

D 2
u_long gallant19_90_pixels[] = {
E 2
I 2
static u_long gallant19_90_pixels[] = {
E 2
    0x00000000,
    0x00000000, 0x3fe00000, 0x20c00000, 0x00c00000, 0x01800000, 0x01800000,
    0x03000000, 0x03000000, 0x06000000, 0x06000000, 0x0c000000, 0x0c000000,
    0x18000000, 0x18200000, 0x3fe00000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000
D 2
    };
struct raster gallant19_90 = { 12, 22, 1, 1, gallant19_90_pixels, 0 };
E 2
I 2
};
static struct raster gallant19_90 = { 12, 22, 1, 1, gallant19_90_pixels, 0 };
E 2

D 2
u_long gallant19_91_pixels[] = {
E 2
I 2
static u_long gallant19_91_pixels[] = {
E 2
    0x00000000,
    0x07c00000, 0x07c00000, 0x06000000, 0x06000000, 0x06000000, 0x06000000,
    0x06000000, 0x06000000, 0x06000000, 0x06000000, 0x06000000, 0x06000000,
    0x06000000, 0x07c00000, 0x07c00000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000
D 2
    };
struct raster gallant19_91 = { 12, 22, 1, 1, gallant19_91_pixels, 0 };
E 2
I 2
};
static struct raster gallant19_91 = { 12, 22, 1, 1, gallant19_91_pixels, 0 };
E 2

D 2
u_long gallant19_92_pixels[] = {
E 2
I 2
static u_long gallant19_92_pixels[] = {
E 2
    0x00000000,
    0x60000000, 0x60000000, 0x30000000, 0x30000000, 0x18000000, 0x18000000,
    0x0c000000, 0x0c000000, 0x06000000, 0x03000000, 0x03000000, 0x01800000,
    0x01800000, 0x00c00000, 0x00c00000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000
D 2
    };
struct raster gallant19_92 = { 12, 22, 1, 1, gallant19_92_pixels, 0 };
E 2
I 2
};
static struct raster gallant19_92 = { 12, 22, 1, 1, gallant19_92_pixels, 0 };
E 2

D 2
u_long gallant19_93_pixels[] = {
E 2
I 2
static u_long gallant19_93_pixels[] = {
E 2
    0x00000000,
    0x7c000000, 0x7c000000, 0x0c000000, 0x0c000000, 0x0c000000, 0x0c000000,
    0x0c000000, 0x0c000000, 0x0c000000, 0x0c000000, 0x0c000000, 0x0c000000,
    0x0c000000, 0x7c000000, 0x7c000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000
D 2
    };
struct raster gallant19_93 = { 12, 22, 1, 1, gallant19_93_pixels, 0 };
E 2
I 2
};
static struct raster gallant19_93 = { 12, 22, 1, 1, gallant19_93_pixels, 0 };
E 2

D 2
u_long gallant19_94_pixels[] = {
E 2
I 2
static u_long gallant19_94_pixels[] = {
E 2
    0x00000000,
    0x04000000, 0x0e000000, 0x1b000000, 0x31800000, 0x60c00000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000
D 2
    };
struct raster gallant19_94 = { 12, 22, 1, 1, gallant19_94_pixels, 0 };
E 2
I 2
};
static struct raster gallant19_94 = { 12, 22, 1, 1, gallant19_94_pixels, 0 };
E 2

D 2
u_long gallant19_95_pixels[] = {
E 2
I 2
static u_long gallant19_95_pixels[] = {
E 2
    0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xfff00000, 0xfff00000,
    0x00000000, 0x00000000, 0x00000000
D 2
    };
struct raster gallant19_95 = { 12, 22, 1, 1, gallant19_95_pixels, 0 };
E 2
I 2
};
static struct raster gallant19_95 = { 12, 22, 1, 1, gallant19_95_pixels, 0 };
E 2

D 2
u_long gallant19_96_pixels[] = {
E 2
I 2
static u_long gallant19_96_pixels[] = {
E 2
    0x00000000,
    0x01000000, 0x03000000, 0x06000000, 0x06000000, 0x07800000, 0x07800000,
    0x03000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000
D 2
    };
struct raster gallant19_96 = { 12, 22, 1, 1, gallant19_96_pixels, 0 };
E 2
I 2
};
static struct raster gallant19_96 = { 12, 22, 1, 1, gallant19_96_pixels, 0 };
E 2

D 2
u_long gallant19_97_pixels[] = {
E 2
I 2
static u_long gallant19_97_pixels[] = {
E 2
    0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x0f800000,
    0x18c00000, 0x10c00000, 0x03c00000, 0x1cc00000, 0x30c00000, 0x30c00000,
    0x30c00000, 0x39c00000, 0x1ee00000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000
D 2
    };
struct raster gallant19_97 = { 12, 22, 1, 1, gallant19_97_pixels, 0 };
E 2
I 2
};
static struct raster gallant19_97 = { 12, 22, 1, 1, gallant19_97_pixels, 0 };
E 2

D 2
u_long gallant19_98_pixels[] = {
E 2
I 2
static u_long gallant19_98_pixels[] = {
E 2
    0x00000000,
    0x20000000, 0x60000000, 0xe0000000, 0x60000000, 0x60000000, 0x67800000,
    0x6fc00000, 0x70e00000, 0x60600000, 0x60600000, 0x60600000, 0x60600000,
    0x70600000, 0x78c00000, 0x4f800000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000
D 2
    };
struct raster gallant19_98 = { 12, 22, 1, 1, gallant19_98_pixels, 0 };
E 2
I 2
};
static struct raster gallant19_98 = { 12, 22, 1, 1, gallant19_98_pixels, 0 };
E 2

D 2
u_long gallant19_99_pixels[] = {
E 2
I 2
static u_long gallant19_99_pixels[] = {
E 2
    0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x1f800000,
    0x31c00000, 0x20c00000, 0x60000000, 0x60000000, 0x60000000, 0x60000000,
    0x70400000, 0x30c00000, 0x1f800000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000
D 2
    };
struct raster gallant19_99 = { 12, 22, 1, 1, gallant19_99_pixels, 0 };
E 2
I 2
};
static struct raster gallant19_99 = { 12, 22, 1, 1, gallant19_99_pixels, 0 };
E 2

D 2
u_long gallant19_100_pixels[] = {
E 2
I 2
static u_long gallant19_100_pixels[] = {
E 2
    0x00000000,
    0x00600000, 0x00e00000, 0x00600000, 0x00600000, 0x00600000, 0x0f600000,
    0x31e00000, 0x20e00000, 0x60600000, 0x60600000, 0x60600000, 0x60600000,
    0x70e00000, 0x39600000, 0x1e700000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000
D 2
    };
struct raster gallant19_100 = { 12, 22, 1, 1, gallant19_100_pixels, 0 };
E 2
I 2
};
static struct raster gallant19_100 = { 12, 22, 1, 1, gallant19_100_pixels, 0 };
E 2

D 2
u_long gallant19_101_pixels[] = {
E 2
I 2
static u_long gallant19_101_pixels[] = {
E 2
    0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x0f000000,
    0x30c00000, 0x60600000, 0x60600000, 0x7fe00000, 0x60000000, 0x60000000,
    0x30000000, 0x18600000, 0x0f800000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000
D 2
    };
struct raster gallant19_101 = { 12, 22, 1, 1, gallant19_101_pixels, 0 };
E 2
I 2
};
static struct raster gallant19_101 = { 12, 22, 1, 1, gallant19_101_pixels, 0 };
E 2

D 2
u_long gallant19_102_pixels[] = {
E 2
I 2
static u_long gallant19_102_pixels[] = {
E 2
    0x00000000,
    0x03800000, 0x04c00000, 0x04c00000, 0x0c000000, 0x0c000000, 0x0c000000,
    0x0c000000, 0x1f800000, 0x0c000000, 0x0c000000, 0x0c000000, 0x0c000000,
    0x0c000000, 0x0c000000, 0x1e000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000
D 2
    };
struct raster gallant19_102 = { 12, 22, 1, 1, gallant19_102_pixels, 0 };
E 2
I 2
};
static struct raster gallant19_102 = { 12, 22, 1, 1, gallant19_102_pixels, 0 };
E 2

D 2
u_long gallant19_103_pixels[] = {
E 2
I 2
static u_long gallant19_103_pixels[] = {
E 2
    0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x1f200000,
    0x31e00000, 0x60c00000, 0x60c00000, 0x60c00000, 0x31800000, 0x3f000000,
    0x60000000, 0x7fc00000, 0x3fe00000, 0x20600000, 0x40200000, 0x40200000,
    0x7fc00000, 0x3f800000, 0x00000000
D 2
    };
struct raster gallant19_103 = { 12, 22, 1, 1, gallant19_103_pixels, 0 };
E 2
I 2
};
static struct raster gallant19_103 = { 12, 22, 1, 1, gallant19_103_pixels, 0 };
E 2

D 2
u_long gallant19_104_pixels[] = {
E 2
I 2
static u_long gallant19_104_pixels[] = {
E 2
    0x00000000,
    0x10000000, 0x30000000, 0x70000000, 0x30000000, 0x30000000, 0x37800000,
    0x39c00000, 0x30c00000, 0x30c00000, 0x30c00000, 0x30c00000, 0x30c00000,
    0x30c00000, 0x30c00000, 0x79e00000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000
D 2
    };
struct raster gallant19_104 = { 12, 22, 1, 1, gallant19_104_pixels, 0 };
E 2
I 2
};
static struct raster gallant19_104 = { 12, 22, 1, 1, gallant19_104_pixels, 0 };
E 2

D 2
u_long gallant19_105_pixels[] = {
E 2
I 2
static u_long gallant19_105_pixels[] = {
E 2
    0x00000000,
    0x00000000, 0x06000000, 0x06000000, 0x00000000, 0x00000000, 0x1e000000,
    0x06000000, 0x06000000, 0x06000000, 0x06000000, 0x06000000, 0x06000000,
    0x06000000, 0x06000000, 0x1f800000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000
D 2
    };
struct raster gallant19_105 = { 12, 22, 1, 1, gallant19_105_pixels, 0 };
E 2
I 2
};
static struct raster gallant19_105 = { 12, 22, 1, 1, gallant19_105_pixels, 0 };
E 2

D 2
u_long gallant19_106_pixels[] = {
E 2
I 2
static u_long gallant19_106_pixels[] = {
E 2
    0x00000000,
    0x00000000, 0x00c00000, 0x00c00000, 0x00000000, 0x00000000, 0x03c00000,
    0x00c00000, 0x00c00000, 0x00c00000, 0x00c00000, 0x00c00000, 0x00c00000,
    0x00c00000, 0x00c00000, 0x00c00000, 0x20c00000, 0x30c00000, 0x38800000,
    0x1f000000, 0x0e000000, 0x00000000
D 2
    };
struct raster gallant19_106 = { 12, 22, 1, 1, gallant19_106_pixels, 0 };
E 2
I 2
};
static struct raster gallant19_106 = { 12, 22, 1, 1, gallant19_106_pixels, 0 };
E 2

D 2
u_long gallant19_107_pixels[] = {
E 2
I 2
static u_long gallant19_107_pixels[] = {
E 2
    0x00000000,
    0x60000000, 0xe0000000, 0x60000000, 0x60000000, 0x60000000, 0x61c00000,
    0x63000000, 0x66000000, 0x7c000000, 0x78000000, 0x7c000000, 0x6e000000,
    0x67000000, 0x63800000, 0xf1e00000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000
D 2
    };
struct raster gallant19_107 = { 12, 22, 1, 1, gallant19_107_pixels, 0 };
E 2
I 2
};
static struct raster gallant19_107 = { 12, 22, 1, 1, gallant19_107_pixels, 0 };
E 2

D 2
u_long gallant19_108_pixels[] = {
E 2
I 2
static u_long gallant19_108_pixels[] = {
E 2
    0x00000000,
    0x1e000000, 0x06000000, 0x06000000, 0x06000000, 0x06000000, 0x06000000,
    0x06000000, 0x06000000, 0x06000000, 0x06000000, 0x06000000, 0x06000000,
    0x06000000, 0x06000000, 0x1f800000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000
D 2
    };
struct raster gallant19_108 = { 12, 22, 1, 1, gallant19_108_pixels, 0 };
E 2
I 2
};
static struct raster gallant19_108 = { 12, 22, 1, 1, gallant19_108_pixels, 0 };
E 2

D 2
u_long gallant19_109_pixels[] = {
E 2
I 2
static u_long gallant19_109_pixels[] = {
E 2
    0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xddc00000,
    0x6ee00000, 0x66600000, 0x66600000, 0x66600000, 0x66600000, 0x66600000,
    0x66600000, 0x66600000, 0xef700000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000
D 2
    };
struct raster gallant19_109 = { 12, 22, 1, 1, gallant19_109_pixels, 0 };
E 2
I 2
};
static struct raster gallant19_109 = { 12, 22, 1, 1, gallant19_109_pixels, 0 };
E 2

D 2
u_long gallant19_110_pixels[] = {
E 2
I 2
static u_long gallant19_110_pixels[] = {
E 2
    0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x27800000,
    0x79c00000, 0x30c00000, 0x30c00000, 0x30c00000, 0x30c00000, 0x30c00000,
    0x30c00000, 0x30c00000, 0x79e00000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000
D 2
    };
struct raster gallant19_110 = { 12, 22, 1, 1, gallant19_110_pixels, 0 };
E 2
I 2
};
static struct raster gallant19_110 = { 12, 22, 1, 1, gallant19_110_pixels, 0 };
E 2

D 2
u_long gallant19_111_pixels[] = {
E 2
I 2
static u_long gallant19_111_pixels[] = {
E 2
    0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x0f800000,
    0x11c00000, 0x20e00000, 0x60600000, 0x60600000, 0x60600000, 0x60600000,
    0x70400000, 0x38800000, 0x1f000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000
D 2
    };
struct raster gallant19_111 = { 12, 22, 1, 1, gallant19_111_pixels, 0 };
E 2
I 2
};
static struct raster gallant19_111 = { 12, 22, 1, 1, gallant19_111_pixels, 0 };
E 2

D 2
u_long gallant19_112_pixels[] = {
E 2
I 2
static u_long gallant19_112_pixels[] = {
E 2
    0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xef800000,
    0x71c00000, 0x60e00000, 0x60600000, 0x60600000, 0x60600000, 0x60600000,
    0x60400000, 0x70800000, 0x7f000000, 0x60000000, 0x60000000, 0x60000000,
    0x60000000, 0xf0000000, 0x00000000
D 2
    };
struct raster gallant19_112 = { 12, 22, 1, 1, gallant19_112_pixels, 0 };
E 2
I 2
};
static struct raster gallant19_112 = { 12, 22, 1, 1, gallant19_112_pixels, 0 };
E 2

D 2
u_long gallant19_113_pixels[] = {
E 2
I 2
static u_long gallant19_113_pixels[] = {
E 2
    0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x0f200000,
    0x11e00000, 0x20e00000, 0x60600000, 0x60600000, 0x60600000, 0x60600000,
    0x70600000, 0x38e00000, 0x1fe00000, 0x00600000, 0x00600000, 0x00600000,
    0x00600000, 0x00f00000, 0x00000000
D 2
    };
struct raster gallant19_113 = { 12, 22, 1, 1, gallant19_113_pixels, 0 };
E 2
I 2
};
static struct raster gallant19_113 = { 12, 22, 1, 1, gallant19_113_pixels, 0 };
E 2

D 2
u_long gallant19_114_pixels[] = {
E 2
I 2
static u_long gallant19_114_pixels[] = {
E 2
    0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x73800000,
    0x34c00000, 0x38c00000, 0x30000000, 0x30000000, 0x30000000, 0x30000000,
    0x30000000, 0x30000000, 0x78000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000
D 2
    };
struct raster gallant19_114 = { 12, 22, 1, 1, gallant19_114_pixels, 0 };
E 2
I 2
};
static struct raster gallant19_114 = { 12, 22, 1, 1, gallant19_114_pixels, 0 };
E 2

D 2
u_long gallant19_115_pixels[] = {
E 2
I 2
static u_long gallant19_115_pixels[] = {
E 2
    0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x1fc00000,
    0x30c00000, 0x30400000, 0x38000000, 0x1e000000, 0x07800000, 0x01c00000,
    0x20c00000, 0x30c00000, 0x3f800000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000
D 2
    };
struct raster gallant19_115 = { 12, 22, 1, 1, gallant19_115_pixels, 0 };
E 2
I 2
};
static struct raster gallant19_115 = { 12, 22, 1, 1, gallant19_115_pixels, 0 };
E 2

D 2
u_long gallant19_116_pixels[] = {
E 2
I 2
static u_long gallant19_116_pixels[] = {
E 2
    0x00000000,
    0x00000000, 0x00000000, 0x04000000, 0x04000000, 0x0c000000, 0x7fc00000,
    0x0c000000, 0x0c000000, 0x0c000000, 0x0c000000, 0x0c000000, 0x0c000000,
    0x0c200000, 0x0e400000, 0x07800000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000
D 2
    };
struct raster gallant19_116 = { 12, 22, 1, 1, gallant19_116_pixels, 0 };
E 2
I 2
};
static struct raster gallant19_116 = { 12, 22, 1, 1, gallant19_116_pixels, 0 };
E 2

D 2
u_long gallant19_117_pixels[] = {
E 2
I 2
static u_long gallant19_117_pixels[] = {
E 2
    0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x79e00000,
    0x30c00000, 0x30c00000, 0x30c00000, 0x30c00000, 0x30c00000, 0x30c00000,
    0x30c00000, 0x39c00000, 0x1e600000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000
D 2
    };
struct raster gallant19_117 = { 12, 22, 1, 1, gallant19_117_pixels, 0 };
E 2
I 2
};
static struct raster gallant19_117 = { 12, 22, 1, 1, gallant19_117_pixels, 0 };
E 2

D 2
u_long gallant19_118_pixels[] = {
E 2
I 2
static u_long gallant19_118_pixels[] = {
E 2
    0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xf0700000,
    0x60200000, 0x30400000, 0x30400000, 0x18800000, 0x18800000, 0x0d000000,
    0x0d000000, 0x06000000, 0x06000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000
D 2
    };
struct raster gallant19_118 = { 12, 22, 1, 1, gallant19_118_pixels, 0 };
E 2
I 2
};
static struct raster gallant19_118 = { 12, 22, 1, 1, gallant19_118_pixels, 0 };
E 2

D 2
u_long gallant19_119_pixels[] = {
E 2
I 2
static u_long gallant19_119_pixels[] = {
E 2
    0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff700000,
    0x66200000, 0x66200000, 0x66200000, 0x37400000, 0x3b400000, 0x3b400000,
    0x19800000, 0x19800000, 0x19800000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000
D 2
    };
struct raster gallant19_119 = { 12, 22, 1, 1, gallant19_119_pixels, 0 };
E 2
I 2
};
static struct raster gallant19_119 = { 12, 22, 1, 1, gallant19_119_pixels, 0 };
E 2

D 2
u_long gallant19_120_pixels[] = {
E 2
I 2
static u_long gallant19_120_pixels[] = {
E 2
    0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xf8f00000,
    0x70400000, 0x38800000, 0x1d000000, 0x0e000000, 0x07000000, 0x0b800000,
    0x11c00000, 0x20e00000, 0xf1f00000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000
D 2
    };
struct raster gallant19_120 = { 12, 22, 1, 1, gallant19_120_pixels, 0 };
E 2
I 2
};
static struct raster gallant19_120 = { 12, 22, 1, 1, gallant19_120_pixels, 0 };
E 2

D 2
u_long gallant19_121_pixels[] = {
E 2
I 2
static u_long gallant19_121_pixels[] = {
E 2
    0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xf0f00000,
    0x60200000, 0x30400000, 0x30400000, 0x18800000, 0x18800000, 0x0d000000,
    0x0d000000, 0x06000000, 0x06000000, 0x04000000, 0x0c000000, 0x08000000,
    0x78000000, 0x70000000, 0x00000000
D 2
    };
struct raster gallant19_121 = { 12, 22, 1, 1, gallant19_121_pixels, 0 };
E 2
I 2
};
static struct raster gallant19_121 = { 12, 22, 1, 1, gallant19_121_pixels, 0 };
E 2

D 2
u_long gallant19_122_pixels[] = {
E 2
I 2
static u_long gallant19_122_pixels[] = {
E 2
    0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x7fe00000,
    0x60e00000, 0x41c00000, 0x03800000, 0x07000000, 0x0e000000, 0x1c000000,
    0x38200000, 0x70600000, 0x7fe00000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000
D 2
    };
struct raster gallant19_122 = { 12, 22, 1, 1, gallant19_122_pixels, 0 };
E 2
I 2
};
static struct raster gallant19_122 = { 12, 22, 1, 1, gallant19_122_pixels, 0 };
E 2

D 2
u_long gallant19_123_pixels[] = {
E 2
I 2
static u_long gallant19_123_pixels[] = {
E 2
    0x00000000,
    0x01c00000, 0x03000000, 0x03000000, 0x01800000, 0x01800000, 0x01800000,
    0x03000000, 0x07000000, 0x03000000, 0x01800000, 0x01800000, 0x01800000,
    0x03000000, 0x03000000, 0x01c00000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000
D 2
    };
struct raster gallant19_123 = { 12, 22, 1, 1, gallant19_123_pixels, 0 };
E 2
I 2
};
static struct raster gallant19_123 = { 12, 22, 1, 1, gallant19_123_pixels, 0 };
E 2

D 2
u_long gallant19_124_pixels[] = {
E 2
I 2
static u_long gallant19_124_pixels[] = {
E 2
    0x00000000,
    0x06000000, 0x06000000, 0x06000000, 0x06000000, 0x06000000, 0x06000000,
    0x06000000, 0x06000000, 0x06000000, 0x06000000, 0x06000000, 0x06000000,
    0x06000000, 0x06000000, 0x06000000, 0x06000000, 0x06000000, 0x06000000,
    0x06000000, 0x06000000, 0x00000000
D 2
    };
struct raster gallant19_124 = { 12, 22, 1, 1, gallant19_124_pixels, 0 };
E 2
I 2
};
static struct raster gallant19_124 = { 12, 22, 1, 1, gallant19_124_pixels, 0 };
E 2

D 2
u_long gallant19_125_pixels[] = {
E 2
I 2
static u_long gallant19_125_pixels[] = {
E 2
    0x00000000,
    0x38000000, 0x0c000000, 0x0c000000, 0x18000000, 0x18000000, 0x18000000,
    0x0c000000, 0x0e000000, 0x0c000000, 0x18000000, 0x18000000, 0x18000000,
    0x0c000000, 0x0c000000, 0x38000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000
D 2
    };
struct raster gallant19_125 = { 12, 22, 1, 1, gallant19_125_pixels, 0 };
E 2
I 2
};
static struct raster gallant19_125 = { 12, 22, 1, 1, gallant19_125_pixels, 0 };
E 2

D 2
u_long gallant19_126_pixels[] = {
E 2
I 2
static u_long gallant19_126_pixels[] = {
E 2
    0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x1c200000, 0x3e600000, 0x36c00000, 0x67c00000,
    0x43800000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000
D 2
    };
struct raster gallant19_126 = { 12, 22, 1, 1, gallant19_126_pixels, 0 };
E 2
I 2
};
static struct raster gallant19_126 = { 12, 22, 1, 1, gallant19_126_pixels, 0 };
E 2

I 2
#define	null2 {0}, {0}
#define	null4 null2, null2
#define	null8 null4, null4
#define	null16 null8, null8
#define	null32 null16, null16
#define	null64 null32, null32
#define	null128 null64, null64

E 2
struct raster_font gallant19 = {
    12, 22, RASFONT_FIXEDWIDTH|RASFONT_NOVERTICALMOVEMENT,
D 2
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    &gallant19_32, 0, -15, 12, 0,
    &gallant19_33, 0, -15, 12, 0,
    &gallant19_34, 0, -15, 12, 0,
    &gallant19_35, 0, -15, 12, 0,
    &gallant19_36, 0, -15, 12, 0,
    &gallant19_37, 0, -15, 12, 0,
    &gallant19_38, 0, -15, 12, 0,
    &gallant19_39, 0, -15, 12, 0,
    &gallant19_40, 0, -15, 12, 0,
    &gallant19_41, 0, -15, 12, 0,
    &gallant19_42, 0, -15, 12, 0,
    &gallant19_43, 0, -15, 12, 0,
    &gallant19_44, 0, -15, 12, 0,
    &gallant19_45, 0, -15, 12, 0,
    &gallant19_46, 0, -15, 12, 0,
    &gallant19_47, 0, -15, 12, 0,
    &gallant19_48, 0, -15, 12, 0,
    &gallant19_49, 0, -15, 12, 0,
    &gallant19_50, 0, -15, 12, 0,
    &gallant19_51, 0, -15, 12, 0,
    &gallant19_52, 0, -15, 12, 0,
    &gallant19_53, 0, -15, 12, 0,
    &gallant19_54, 0, -15, 12, 0,
    &gallant19_55, 0, -15, 12, 0,
    &gallant19_56, 0, -15, 12, 0,
    &gallant19_57, 0, -15, 12, 0,
    &gallant19_58, 0, -15, 12, 0,
    &gallant19_59, 0, -15, 12, 0,
    &gallant19_60, 0, -15, 12, 0,
    &gallant19_61, 0, -15, 12, 0,
    &gallant19_62, 0, -15, 12, 0,
    &gallant19_63, 0, -15, 12, 0,
    &gallant19_64, 0, -15, 12, 0,
    &gallant19_65, 0, -15, 12, 0,
    &gallant19_66, 0, -15, 12, 0,
    &gallant19_67, 0, -15, 12, 0,
    &gallant19_68, 0, -15, 12, 0,
    &gallant19_69, 0, -15, 12, 0,
    &gallant19_70, 0, -15, 12, 0,
    &gallant19_71, 0, -15, 12, 0,
    &gallant19_72, 0, -15, 12, 0,
    &gallant19_73, 0, -15, 12, 0,
    &gallant19_74, 0, -15, 12, 0,
    &gallant19_75, 0, -15, 12, 0,
    &gallant19_76, 0, -15, 12, 0,
    &gallant19_77, 0, -15, 12, 0,
    &gallant19_78, 0, -15, 12, 0,
    &gallant19_79, 0, -15, 12, 0,
    &gallant19_80, 0, -15, 12, 0,
    &gallant19_81, 0, -15, 12, 0,
    &gallant19_82, 0, -15, 12, 0,
    &gallant19_83, 0, -15, 12, 0,
    &gallant19_84, 0, -15, 12, 0,
    &gallant19_85, 0, -15, 12, 0,
    &gallant19_86, 0, -15, 12, 0,
    &gallant19_87, 0, -15, 12, 0,
    &gallant19_88, 0, -15, 12, 0,
    &gallant19_89, 0, -15, 12, 0,
    &gallant19_90, 0, -15, 12, 0,
    &gallant19_91, 0, -15, 12, 0,
    &gallant19_92, 0, -15, 12, 0,
    &gallant19_93, 0, -15, 12, 0,
    &gallant19_94, 0, -15, 12, 0,
    &gallant19_95, 0, -15, 12, 0,
    &gallant19_96, 0, -15, 12, 0,
    &gallant19_97, 0, -15, 12, 0,
    &gallant19_98, 0, -15, 12, 0,
    &gallant19_99, 0, -15, 12, 0,
    &gallant19_100, 0, -15, 12, 0,
    &gallant19_101, 0, -15, 12, 0,
    &gallant19_102, 0, -15, 12, 0,
    &gallant19_103, 0, -15, 12, 0,
    &gallant19_104, 0, -15, 12, 0,
    &gallant19_105, 0, -15, 12, 0,
    &gallant19_106, 0, -15, 12, 0,
    &gallant19_107, 0, -15, 12, 0,
    &gallant19_108, 0, -15, 12, 0,
    &gallant19_109, 0, -15, 12, 0,
    &gallant19_110, 0, -15, 12, 0,
    &gallant19_111, 0, -15, 12, 0,
    &gallant19_112, 0, -15, 12, 0,
    &gallant19_113, 0, -15, 12, 0,
    &gallant19_114, 0, -15, 12, 0,
    &gallant19_115, 0, -15, 12, 0,
    &gallant19_116, 0, -15, 12, 0,
    &gallant19_117, 0, -15, 12, 0,
    &gallant19_118, 0, -15, 12, 0,
    &gallant19_119, 0, -15, 12, 0,
    &gallant19_120, 0, -15, 12, 0,
    &gallant19_121, 0, -15, 12, 0,
    &gallant19_122, 0, -15, 12, 0,
    &gallant19_123, 0, -15, 12, 0,
    &gallant19_124, 0, -15, 12, 0,
    &gallant19_125, 0, -15, 12, 0,
    &gallant19_126, 0, -15, 12, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
E 2
I 2
    {
	null32,
	{ &gallant19_32, 0, -15, 12, 0 },
	{ &gallant19_33, 0, -15, 12, 0 },
	{ &gallant19_34, 0, -15, 12, 0 },
	{ &gallant19_35, 0, -15, 12, 0 },
	{ &gallant19_36, 0, -15, 12, 0 },
	{ &gallant19_37, 0, -15, 12, 0 },
	{ &gallant19_38, 0, -15, 12, 0 },
	{ &gallant19_39, 0, -15, 12, 0 },
	{ &gallant19_40, 0, -15, 12, 0 },
	{ &gallant19_41, 0, -15, 12, 0 },
	{ &gallant19_42, 0, -15, 12, 0 },
	{ &gallant19_43, 0, -15, 12, 0 },
	{ &gallant19_44, 0, -15, 12, 0 },
	{ &gallant19_45, 0, -15, 12, 0 },
	{ &gallant19_46, 0, -15, 12, 0 },
	{ &gallant19_47, 0, -15, 12, 0 },
	{ &gallant19_48, 0, -15, 12, 0 },
	{ &gallant19_49, 0, -15, 12, 0 },
	{ &gallant19_50, 0, -15, 12, 0 },
	{ &gallant19_51, 0, -15, 12, 0 },
	{ &gallant19_52, 0, -15, 12, 0 },
	{ &gallant19_53, 0, -15, 12, 0 },
	{ &gallant19_54, 0, -15, 12, 0 },
	{ &gallant19_55, 0, -15, 12, 0 },
	{ &gallant19_56, 0, -15, 12, 0 },
	{ &gallant19_57, 0, -15, 12, 0 },
	{ &gallant19_58, 0, -15, 12, 0 },
	{ &gallant19_59, 0, -15, 12, 0 },
	{ &gallant19_60, 0, -15, 12, 0 },
	{ &gallant19_61, 0, -15, 12, 0 },
	{ &gallant19_62, 0, -15, 12, 0 },
	{ &gallant19_63, 0, -15, 12, 0 },
	{ &gallant19_64, 0, -15, 12, 0 },
	{ &gallant19_65, 0, -15, 12, 0 },
	{ &gallant19_66, 0, -15, 12, 0 },
	{ &gallant19_67, 0, -15, 12, 0 },
	{ &gallant19_68, 0, -15, 12, 0 },
	{ &gallant19_69, 0, -15, 12, 0 },
	{ &gallant19_70, 0, -15, 12, 0 },
	{ &gallant19_71, 0, -15, 12, 0 },
	{ &gallant19_72, 0, -15, 12, 0 },
	{ &gallant19_73, 0, -15, 12, 0 },
	{ &gallant19_74, 0, -15, 12, 0 },
	{ &gallant19_75, 0, -15, 12, 0 },
	{ &gallant19_76, 0, -15, 12, 0 },
	{ &gallant19_77, 0, -15, 12, 0 },
	{ &gallant19_78, 0, -15, 12, 0 },
	{ &gallant19_79, 0, -15, 12, 0 },
	{ &gallant19_80, 0, -15, 12, 0 },
	{ &gallant19_81, 0, -15, 12, 0 },
	{ &gallant19_82, 0, -15, 12, 0 },
	{ &gallant19_83, 0, -15, 12, 0 },
	{ &gallant19_84, 0, -15, 12, 0 },
	{ &gallant19_85, 0, -15, 12, 0 },
	{ &gallant19_86, 0, -15, 12, 0 },
	{ &gallant19_87, 0, -15, 12, 0 },
	{ &gallant19_88, 0, -15, 12, 0 },
	{ &gallant19_89, 0, -15, 12, 0 },
	{ &gallant19_90, 0, -15, 12, 0 },
	{ &gallant19_91, 0, -15, 12, 0 },
	{ &gallant19_92, 0, -15, 12, 0 },
	{ &gallant19_93, 0, -15, 12, 0 },
	{ &gallant19_94, 0, -15, 12, 0 },
	{ &gallant19_95, 0, -15, 12, 0 },
	{ &gallant19_96, 0, -15, 12, 0 },
	{ &gallant19_97, 0, -15, 12, 0 },
	{ &gallant19_98, 0, -15, 12, 0 },
	{ &gallant19_99, 0, -15, 12, 0 },
	{ &gallant19_100, 0, -15, 12, 0 },
	{ &gallant19_101, 0, -15, 12, 0 },
	{ &gallant19_102, 0, -15, 12, 0 },
	{ &gallant19_103, 0, -15, 12, 0 },
	{ &gallant19_104, 0, -15, 12, 0 },
	{ &gallant19_105, 0, -15, 12, 0 },
	{ &gallant19_106, 0, -15, 12, 0 },
	{ &gallant19_107, 0, -15, 12, 0 },
	{ &gallant19_108, 0, -15, 12, 0 },
	{ &gallant19_109, 0, -15, 12, 0 },
	{ &gallant19_110, 0, -15, 12, 0 },
	{ &gallant19_111, 0, -15, 12, 0 },
	{ &gallant19_112, 0, -15, 12, 0 },
	{ &gallant19_113, 0, -15, 12, 0 },
	{ &gallant19_114, 0, -15, 12, 0 },
	{ &gallant19_115, 0, -15, 12, 0 },
	{ &gallant19_116, 0, -15, 12, 0 },
	{ &gallant19_117, 0, -15, 12, 0 },
	{ &gallant19_118, 0, -15, 12, 0 },
	{ &gallant19_119, 0, -15, 12, 0 },
	{ &gallant19_120, 0, -15, 12, 0 },
	{ &gallant19_121, 0, -15, 12, 0 },
	{ &gallant19_122, 0, -15, 12, 0 },
	{ &gallant19_123, 0, -15, 12, 0 },
	{ &gallant19_124, 0, -15, 12, 0 },
	{ &gallant19_125, 0, -15, 12, 0 },
	{ &gallant19_126, 0, -15, 12, 0 },
	{ 0 },
	null128
    },
E 2
#ifdef COLORFONT_CACHE
    (struct raster_fontcache*) -1
#endif /*COLORFONT_CACHE*/
D 2
    };

E 2
I 2
};
E 2
E 1
