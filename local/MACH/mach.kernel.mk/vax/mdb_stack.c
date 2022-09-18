/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	mdb_stack.c,v $
 * Revision 2.2  89/02/25  20:25:31  gm0w
 * 	Changes for cleanup.
 * 
 */
/*
 *	File:	vax/mdb_stack.c	--	stack trace
 *	Author:	Robert V. Baron
 *
 *	Copyright (C) 1987, Robert V. Baron
 *
 *	Kernel debugger.
 */

#include <mdb/mdb.h>

struct frame {
	ulongp	f_handler;
	struct	f_fm {
		unsigned int : 5;
		unsigned int fm_psw : 11;
		unsigned int fm_mask : 12;
		unsigned int : 1;
		unsigned int fm_s : 1;
		unsigned int fm_spa : 2;
	} f_msk ;
	ulongp	f_ap ;
	struct	frame *f_fp ;
	unsigned char *f_pc ;
	int	f_r0[12] ;
} ;

#define f_psw f_msk.f_fmask
#define f_mask f_msk.fm_mask
#define f_s f_msk.fm_s
#define f_spa f_msk.fm_spa

#define R_0_5  "    R0        R1        R2        R3        R4        R5\n"
#define R_6_11 "    R6        R7        R8        R9        R10       R11\n"
#define R_INDENT "                   "
#define T_INDENT "           "
#define OVERLOAD 128

#define SYS 0x80000000
#define EOF(fp) (!(int)fp || ((int) fp == SYS) || \
	(VALulong( (ulongp) &(((struct frame *)fp)->f_pc), dp ) & SYS) != SYS)

struct frame *mdb_stack_numeric();

mdb_stack_print(fp, dp)
ulongp fp;
register struct dbg_state *dp;
{
ulongp ap = (ulongp) -1;

	do {
		mdb_stack_frame(&fp, &ap, dp);
		if (EOF(fp))
			break;
	} while (fp);
}

mdb_rawstack_print(fp, dp)
register struct frame *fp;
register struct dbg_state *dp;
{
	do {
		fp = mdb_stack_numeric(fp, dp);
		if (EOF(fp))
			break;
	} while (fp);

}

mdb_stack_frame(fpp, app, dp)
struct frame *(*fpp);
ulongp *app;
struct dbg_state *dp;
{
register struct frame *fp = *fpp;
register ulongp ap = *app;
register ulongp sp;
register int cnt;

/* call  */
	{register ucharp rpc;
	 register ucharp cpc;
	 ucharp spc;
	 int scnt = -1;

	 rpc = (ucharp)(VALulong(&fp->f_pc, dp));
	 cpc = rpc - 8;

	 while (cpc < rpc)
	 	if ((cnt = VALuchar(cpc++, dp)) == 0xfb || cnt == 0xfa)
			scnt = cnt, spc = cpc;

	 if (scnt != -1)
		 switch (scnt) {
		 case 0:
			mpr_address(rpc, dp);
			printf("calls $%D,", (VALulong(ap, dp)));
			if (VALuchar(spc++, dp) == (VALulong(ap, dp)) )	/* calls $#, ... */
				 switch (cnt = VALuchar(spc++, dp)) {
				 case 0xef:	/* word rel */
					printf("%s(", rpc+(VALulong((ulongp)spc, dp)));
					break;
				 case 0x60:
				 	printf("(r0)(");
					break;
				 default:
					printf("??%x??%x??(", cnt, cnt);
				 }
			else
				printf("calls #!=(");
			break;
	/*calls*/case 0xfa:
	/*calls*/case 0xfb:		
			mdb_dis(--spc, 0, dp);
			printf("(");
			break;
		default:
			printf("not a call(");
			*app = 0;
			*fpp = 0;
			return;
		 }
	else {
		mpr_address(rpc, dp);
		printf("call??(");
	}

/* args */
	if ((int) ap > 0)
		for (cnt = (VALulong(ap++, dp)) ; cnt-- > 0 ;)
			printf("%x%s", (VALulong(ap++, dp)), cnt ? ", " : "");
	}
	printf(")\n");

/* regs */
	{register ulongp rp = (ulongp) fp->f_r0;
	 int mskword;
	 register msk;

		mskword = (VALulong(&fp->f_msk, dp));
		msk = ((struct f_fm *) &mskword)->fm_mask;

		if (msk & 0x3f) {	/* first 6 saved */
			printf(R_INDENT) ; printf(R_0_5);
			printf(R_INDENT);
			for (cnt = 0 ; cnt < 6; cnt++ ) {
				if (msk & (1<<cnt))
					printf(" %08X ", (VALulong(rp++, dp)));
				else
					printf("   ????   ");
			}
			printf("\n");
		}

		printf(R_INDENT) ; printf(R_6_11);
		printf(R_INDENT);
		for (cnt = 6 ; cnt < 12; cnt++ ) {
			if (msk & (1<<cnt))
				printf(" %08X ", (VALulong(rp++, dp)));
			else
				printf("   ????   ");
		}
		printf("\n\n");
	  }

/* autos */
	if ((int) ap > 0) {register ulongp nfp = (ulongp) (VALulong(&fp->f_fp, dp));
			   register int cnt;
			   int save_cnt;
			   int locals;

		locals = nfp - ap;
		printf("%s LOCAL (%d LONGS)", T_INDENT, locals);
		if ((locals) > OVERLOAD) {
			printf(" WILL PRINT FIRST %d\n", OVERLOAD);
			locals = OVERLOAD;
		} else {
			printf("\n");
			locals <<= 2;
		}
		for (cnt = 0; cnt < locals;) {
			printf(R_INDENT);
			save_cnt = cnt;
			do {
				printf(" -%02x(fp)  ", cnt+4);
				cnt += 4;
			} while(cnt < locals && cnt & 0xf);
			printf("\n") ; printf(R_INDENT);
			cnt = save_cnt;
			do {
				printf(" %08x ", VALulong(--nfp, dp));
				cnt += 4;
			} while(cnt < locals && cnt & 0xf);
			printf("\n");
		}
		printf("\n");
	}

	*app = (ulongp) VALulong(&fp->f_ap, dp);
	*fpp = (struct frame *) VALulong(&fp->f_fp, dp);
	return;
}

mdb_stack(fp, dp)
register struct frame *fp;
struct dbg_state *dp;
{
register ulongp ap = (ulongp) -1;
register ulongp sp;
register int cnt;

   while (fp) {
/* call  */
	{register ucharp rpc;
	 register ucharp cpc;
	 ucharp spc;
	 int scnt = -1;

	 rpc = (ucharp)(VALulong(&fp->f_pc, dp));
	 cpc = rpc - 8;

	 while (cpc < rpc)
	 	if ((cnt = VALuchar(cpc++, dp)) == 0xfb || cnt == 0xfa)
			scnt = cnt, spc = cpc;

	 if (scnt != -1)
		 switch (scnt) {
		 case 0:
			mpr_address(rpc, dp);
			printf("calls $%D,", (VALulong(ap, dp)));
			if (VALuchar(spc++, dp) == (VALulong(ap, dp)) )	/* calls $#, ... */
				 switch (cnt = VALuchar(spc++, dp)) {
				 case 0xef:	/* word rel */
					printf("%s(", rpc+(VALulong((ulongp)cpc, dp)));
					break;
				 case 0x60:
				 	printf("(r0)(");
					break;
				 default:
					printf("??%x??%x??(", cnt, cnt);
				 }
			else
				printf("calls #!=(");
			break;
	/*calls*/case 0xfa:
	/*calls*/case 0xfb:		
			mdb_dis(--spc, 0, dp);
			printf("(");
			break;
		default:
			printf("not a call(");
			return;
	}
	else {
		mpr_address(rpc, dp);
		printf("call??(");
	}

/* args */
	if ((int) ap > 0)
		for (cnt = (VALulong(ap++, dp)) ; cnt-- > 0 ;)
			printf("%x%s", (VALulong(ap++, dp)), cnt ? ", " : "");
	}
	printf(")\n");

	ap = (ulongp) VALulong(&fp->f_ap, dp);
	fp = (struct frame *) VALulong(&fp->f_fp, dp);
	if (EOF(fp))
		break;
   }
}

mdb_stack_brief(fp, dp)
register struct frame *fp;
struct dbg_state *dp;
{
register int len = 0;
register int size;

	printf("\t");
	do {register ulongp rpc = (ulongp)(VALulong(&fp->f_pc, dp));


		size = mpr_address_string(rpc, dp);
		printf("%s -> ", dp->address_string);
		if ((len += 4 + size) > 60) {
			printf("\n\t");
			len = 0;
		}
		fp = (struct frame *)VALulong(&fp->f_fp, dp);
		if (EOF(fp))
			break;
	} while (fp);

	printf("\n");
}

struct frame *
mdb_stack_numeric(fp, dp)
register ulongp fp;
struct dbg_state *dp;
{
register ulongp nfp = (ulongp) (VALulong((ulongp)&((struct frame *)fp)->f_fp, dp));
register int locals = (ulongp) nfp - (ulongp) fp;
register int cnt;
int save_cnt;
struct frame *snfp = (struct frame *)nfp;

	printf("        \t<@%x-@%x>", fp, nfp);
	if (locals > OVERLOAD >> 2) {
		printf(" WILL PRINT FIRST %d\n", OVERLOAD);
		locals = OVERLOAD;
	} else {
		printf("\n");
		locals <<= 2;
	}
	for (cnt = 0; cnt < locals;) {
		printf("%08x:\t", fp);
		do {
			printf(" %08x ", VALulong(fp++, dp));
			cnt += 4;
		} while(cnt < locals && cnt & 0xf);
		printf("\n");
	}
	printf("\n");

	return snfp;
}

mdb_upstack(sp, limit, dp)
register ulongp sp;
int limit;
register struct dbg_state *dp;
{
	register ulongp target;
	register ulongp spl;

	if ( ((int) sp) & 0x3ff)	/* low address specified */
		target = sp;
	else
		target = (ulongp) sp - 20;

	if (!limit)
		limit = 4*1024;
	spl = sp - (limit>>2);

	while (sp > spl) {
		while (VALulong(--sp, dp) != (ulong) target && sp > spl) /**/;
		if (sp > spl) {
			target = sp;
		}
	}
	return (int) target;
}
