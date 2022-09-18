h33924
s 00001/00001/00172
d D 5.9 91/11/14 09:19:11 bostic 10 9
c make it compile again
e
s 00002/00005/00171
d D 5.8 91/02/01 11:56:46 bostic 9 8
c move dbx to src/old
e
s 00001/00011/00175
d D 5.7 90/06/01 16:04:55 bostic 8 7
c new copyright notice
e
s 00015/00004/00171
d D 5.6 89/05/23 10:21:19 bostic 7 6
c add Berkeley specific copyright notice
e
s 00001/00001/00174
d D 5.5 89/03/06 12:52:40 bostic 6 5
c instrs -> instrs.adb
e
s 00005/00001/00170
d D 5.4 88/01/22 00:33:21 donn 5 4
c Permit the instrs file to be in an arbitrary place, using the ADBINSTRS
c macro.
e
s 00001/00001/00170
d D 5.3 86/10/14 21:41:16 mckusick 4 3
c moved include file
e
s 00001/00001/00170
d D 5.2 86/02/23 16:17:14 sam 3 2
c make pathname of instrs not depende on -I
e
s 00000/00000/00171
d D 5.1 86/02/22 22:24:32 sam 2 1
c update sccsid
e
s 00171/00000/00000
d D 1.1 86/02/22 22:23:35 sam 1 0
c date and time created 86/02/22 22:23:35 by sam
e
u
U
t
T
I 1
/*
D 7
 * Copyright (c) 1985 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 7
I 7
 * Copyright (c) 1985 The Regents of the University of California.
 * All rights reserved.
 *
D 8
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 8
I 8
 * %sccs.include.redist.c%
E 8
E 7
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 7
#endif not lint
E 7
I 7
#endif /* not lint */
E 7

/*
 * Machine operators.
 */

#include "defs.h"
#include "ops.h"
I 9
#include "pathnames.h"
E 9

#ifndef public
typedef unsigned char Opcode;

/*
 * Opcode definitions.
 */

/*
 * Argument access types
 */
#define ACCA	(8<<3)	/* address only */
#define ACCR	(1<<3)	/* read */
#define ACCW	(2<<3)	/* write */
#define ACCM	(3<<3)	/* modify */
#define ACCB	(4<<3)	/* branch displacement */
#define ACCI	(5<<3)	/* XFC code */

/*
 * Argument data types
 */
#define TYPB	0	/* byte */
#define TYPW	1	/* word */
#define TYPL	2	/* long */
#define TYPQ	3	/* quad */
#define	TYPF	4	/* float */
#define	TYPD	5	/* double */

/*
 * Addressing modes.
 */
#define LITSHORT    0x0	/* short literals */
#define LITUPTO31   0x1
#define LITUPTO47   0x2
#define LITUPTO63   0x3
#define INDEX       0x4 /* i[r] */
#define REG	    0x5 /* r */
#define REGDEF      0x6 /* (r) */
#define AUTODEC     0x7 /* -(r) */
#define AUTOINC     0x8 /* (r)+ */
#define AUTOINCDEF  0x9 /* *(r)+ */
#define BYTEDISP    0xA /* BD(r) */
#define BYTEDISPDEF 0xB /* *BD(r) */
#define WORDDISP    0xC /* WD(r) */
#define WORDDISPDEF 0xD /* *WD(r) */
#define LONGDISP    0xE /* LD(r) */
#define LONGDISPDEF 0xF /* *LD(r) */

#define is_branch_disp(arg) ((arg & ACCB) != 0)
#define typelen(arg)        (arg & 07)
#define regnm(mode)	    (mode & 0xF)
#define addrmode(mode)      (mode >> 4)

/*
 * Certain opcodes values are used either in calculating
 * the next address a process will go to, or for other
 * random reasons -- these are defined here.
 */
#define	O_AOBLEQ	0x3f
#define	O_AOBLSS	0x2f
#define	O_BBC		0x1e
#define	O_BBS		0x0e
#define	O_BBSSI		0x5f
#define	O_BCC		0xf1
#define	O_BCS		0xe1
#define	O_BEQL		0x31
#define	O_BGEQ		0x81
#define	O_BGEQU		0xe1
#define	O_BGTR		0x41
#define	O_BGTRU		0xa1
#define	O_BLEQ		0x51
#define	O_BLEQU		0xb1
#define	O_BLSS		0x91
#define	O_BLSSU		0xf1
#define	O_BNEQ		0x21
#define	O_BPT		0x30
#define	O_BRB		0x11
#define	O_BRW		0x13
#define	O_BTCS		0xce
#define	O_BVC		0xc1
#define	O_BVS		0xd1
#define	O_CALLF		0xfe
#define	O_CALLS		0xbf
#define	O_CASEL		0xfc
#define	O_JMP		0x71
#define	O_KCALL		0xcf
#define	O_RET		0x40

/*
 * Operator information structure.
 */
typedef struct {
    char *iname;
    char val;
    char numargs;
    char argtype[6];
} Optab;

#define	SYSSIZE	151		/* # of system calls */
#endif

I 5
D 9
#ifndef ADBINSTRS
D 6
#define ADBINSTRS "../../bin/adb/adb.tahoe/instrs"
E 6
I 6
#define ADBINSTRS "../../bin/adb/adb.tahoe/instrs.adb"
E 6
#endif

E 9
E 5
public Optab optab[] = {
#define OP(a,b,c,d,e,f,g,h,i) {a,b,c,d,e,f,g,h,i}
D 3
#include "instrs"
E 3
I 3
D 4
#include "../../bin/adb.tahoe/instrs"
E 4
I 4
D 5
#include "../../bin/adb/adb.tahoe/instrs"
E 5
I 5
D 9
#include ADBINSTRS
E 9
I 9
D 10
#include _PATH_ADBINSTR
E 10
I 10
#include "instrs.adb"
E 10
E 9
E 5
E 4
E 3
0};

/*
 * Register names.
 */

public String regname[] = {
    "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7",
    "r8", "r9", "r10","r11","r12", "fp", "sp", "pc"
};

public String systab[SYSSIZE] = {
	"indir",	"exit",		"fork",		"read",
	"write",	"open",		"close",	"owait",
	"creat",	"link",		"unlink",	"execv",
	"chdir",	"otime",	"mknod",	"chmod",
	"chown",	"obreak",	"ostat",	"lseek",
	"getpid",	"mount",	"umount",	"osetuid",
	"getuid",	"ostime",	"ptrace",	"oalarm",
	"ofstat",	"opause",	"outime",	"ostty",
	"ogtty",	"access",	"onice",	"oftime",
	"sync",		"kill",		"stat",		"osetpgrp",
	"lstat",	"dup",		"pipe",		"otimes",
	"profil",	0,		"osetgid",	"getgid",
	"osig",		0,		0,		"acct",
	"ophys",	"olock",	"ioctl",	"reboot",
	"ompxchan",	"symlink",	"readlink",	"execve",
	"umask",	"chroot",	"fstat",	0,
	"getpagesize",	"mremap",	"vfork",	"ovread",
	"ovwrite",	"sbrk",		"sstk",		"mmap",
	"ovadvise",	"munmap",	"mprotect",	"madvise",
	"vhangup",	"ovlimit",	"mincore",	"getgroups",
	"setgroups",	"getpgrp",	"setpgrp",	"setitimer",
	"wait",		"swapon",	"getitimer",	"gethostname",
	"sethostname",	"getdtablesize","dup2",		"getdopt",
	"fcntl",	"select",	"setdopt",	"fsync",
	"setpriority",	"socket",	"connect",	"accept",
	"getpriority",	"send",		"recv",		"osocketaddr",
	"bind",		"setsockopt",	"listen",	"ovtimes",
	"sigvec",	"sigblock",	"sigsetmask",	"sigpause",
	"sigstack",	"recvmsg",	"sendmsg",	"vtrace",
	"gettimeofday",	"getrusage",	"getsockopt",	"resuba",
	"readv",	"writev",	"settimeofday",	"fchown",
	"fchmod",	"recvfrom",	"setreuid",	"setregid",
	"rename",	"truncate",	"ftruncate",	"flock",
	0,		"sendto",	"shutdown",	"socketpair",
	"mkdir",	"rmdir",	"utimes",	0,
	0,		"getpeername",	"gethostid",	"sethostid",
	"getrlimit",	"setrlimit",	"killpg",	0,
	"quota",	"qquota",	"getsockname",
};
E 1
