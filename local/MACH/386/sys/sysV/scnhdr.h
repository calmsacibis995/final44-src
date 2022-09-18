/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	scnhdr.h,v $
 * Revision 2.5  89/05/30  13:28:57  rvb
 * 	Additions for i386.
 * 	[89/04/20            af]
 * 
 * Revision 2.4  89/03/09  22:11:41  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  20:09:50  gm0w
 * 	Changes for cleanup.
 * 
 */
/*	5.2 SID scnhdr.h	2.2 12/15/82	*/

struct scnhdr {
	char		s_name[8];	/* section name */
	long		s_paddr;	/* physical address */
	long		s_vaddr;	/* virtual address */
	long		s_size;		/* section size */
	long		s_scnptr;	/* file ptr to raw data for section */
	long		s_relptr;	/* file ptr to relocation */
	long		s_lnnoptr;	/* file ptr to line numbers */
	unsigned short	s_nreloc;	/* number of relocation entries */
	unsigned short	s_nlnno;	/* number of line number entries */
	long		s_flags;	/* flags */
#ifdef	ns32000
	long		s_symptr;	/* file pointer to symbol entries */
	unsigned short	s_modno;	/* Module number of module associated */
					/*   with this section */
	short		s_pad;		/* padding to 4 byte multiple */
#endif
	};

#define SCNHDR	struct scnhdr
#define SCNHSZ	sizeof(SCNHDR)


#ifdef	i386
/*
 * The number of shared libraries in a .lib section in an absolute output file
 * is put in the s_paddr field of the .lib section header, the following
 * definition allows it to be referenced as s_nlib
 */
#define s_nlib	s_paddr
#endif	i386


/*
 * Define constants for names of "special" sections
 */

#define _TEXT ".text"
#define _DATA ".data"
#define _BSS  ".bss"
#define _TV  ".tv"
#ifdef	i386
#define _INIT ".init"
#define _FINI ".fini"
#endif	i386


/*
 * The low 4 bits of s_flags is used as a section "type"
 */

#define STYP_REG	0x00		/* "regular" section:
						allocated, relocated, loaded */
#define STYP_DSECT	0x01		/* "dummy" section:
						not allocated, relocated,
						not loaded */
#define STYP_NOLOAD	0x02		/* "noload" section:
						allocated, relocated,
						 not loaded */
#define STYP_GROUP	0x04		/* "grouped" section:
						formed of input sections */
#define STYP_PAD	0x08		/* "padding" section:
						not allocated, not relocated,
						 loaded */
#define STYP_COPY	0x10		/* "copy" section:
						for decision function used
						by field update;  not
						allocated, not relocated,
						loaded;  reloc & lineno
						entries processed normally */
#define STYP_TEXT	0x20		/* section contains text only */
#define STYP_DATA	0x40		/* section contains data only */
#define STYP_BSS	0x80		/* section contains bss only */
#ifdef	i386
#define STYP_INFO	0x200		/* comment section : not allocated
						not relocated, not loaded */
#define STYP_LIB	0x800		/* for .lib section : same as INFO */
#define STYP_OVER	0x400		/* overlay section : relocated
						not allocated or loaded */
#endif	i386

/*
 *  In a minimal file or an update file, a new function
 *  (as compared with a replaced function) is indicated by S_NEWFCN
 */

#ifdef	i386
#define S_NEWFCN  0x100
#else	i386
#define S_NEWFCN  0x10
#endif	i386

/*
 * In 3b Update Files (output of ogen), sections which appear in SHARED
 * segments of the Pfile will have the S_SHRSEG flag set by ogen, to inform
 * dufr that updating 1 copy of the proc. will update all process invocations.
 */

#define S_SHRSEG	0x20
