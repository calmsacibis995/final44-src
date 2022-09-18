h36830
s 00002/00002/00036
d D 8.3 94/04/17 09:17:14 bostic 14 13
c move zopen(3) out of the C library, to here; the interface
c is wrong for the C library, and I don't have time to fix it
e
s 00002/00002/00036
d D 8.2 94/01/02 14:05:07 bostic 13 12
c rename fgetline.{3,c} -> fgetln.{3,c}
e
s 00000/00000/00038
d D 8.1 93/06/04 13:03:57 bostic 12 11
c 4.4BSD snapshot (revision 8.1)
e
s 00004/00004/00034
d D 5.10 93/05/04 13:28:21 bostic 11 9
c mktemp is in stdio
e
s 00002/00002/00036
d R 5.10 93/04/27 18:37:09 bostic 10 9
c delete zopen(3) from the C library, moved to compress source tree
e
s 00002/00002/00036
d D 5.9 92/12/03 10:48:30 bostic 9 8
c add zopen
e
s 00002/00003/00036
d D 5.8 91/09/14 10:34:07 bostic 8 7
c move strerror to string
e
s 00001/00001/00038
d D 5.7 91/06/27 14:56:33 bostic 7 6
c no longer any machine-dependent stdio functions
e
s 00004/00002/00035
d D 5.6 91/04/15 11:49:08 donn 6 5
c Add vscanf.c and vsscanf.c (feeping creaturism...)
e
s 00001/00001/00036
d D 5.5 91/03/14 09:30:20 bostic 5 4
c somebody forgot a scanf.3 entry
e
s 00018/00013/00019
d D 5.4 91/03/12 09:39:30 bostic 4 3
c checkpoint
e
s 00008/00018/00024
d D 5.3 91/03/04 20:08:21 bostic 3 2
c VAX .s routines only work with the old stdio
e
s 00014/00008/00028
d D 5.2 91/02/24 13:18:32 bostic 2 1
c lots of minor changes
e
s 00036/00000/00000
d D 5.1 90/06/23 16:23:27 bostic 1 0
c date and time created 90/06/23 16:23:27 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

# stdio sources
D 7
.PATH: ${.CURDIR}/${MACHINE}/stdio ${.CURDIR}/stdio
E 7
I 7
.PATH: ${.CURDIR}/stdio
E 7

D 2
SRCS+=	clrerr.c doprnt.c doscan.c fdopen.c fgetc.c filbuf.c findiop.c \
	flsbuf.c fopen.c fprintf.c fputc.c fread.c freopen.c fseek.c \
	ftell.c fwrite.c getchar.c gets.c getw.c printf.c putchar.c \
	putw.c rew.c scanf.c setbuf.c setbuffer.c sprintf.c ungetc.c \
	vfprintf.c vprintf.c vsprintf.c
E 2
I 2
SRCS+=	clrerr.c fclose.c fdopen.c feof.c ferror.c fflush.c fgetc.c \
D 3
	fgetline.c fgetpos.c fileno.c findfp.c flags.c fopen.c fprintf.c \
	fpurge.c fputc.c fread.c freopen.c fscanf.c fseek.c fsetpos.c \
	ftell.c funopen.c fvwrite.c fwalk.c fwrite.c getc.c getchar.c \
	gets.c getw.c makebuf.c perror.c printf.c putc.c putchar.c putw.c \
	refill.c remove.c rewind.c rget.c scanf.c setbuf.c setbuffer.c \
	setvbuf.c snprintf.c sprintf.c sscanf.c stdio.c tempnam.c tmpfile.c \
	tmpnam.c ungetc.c vfprintf.c vfscanf.c vprintf.c vsnprintf.c \
	vsprintf.c wbuf.c wsetup.c
E 2

.if   (${MACHINE} == "hp300")
SRCS+=	fgets.c fputs.c puts.c
.elif (${MACHINE} == "i386")
SRCS+=	fgets.c fputs.c puts.c
.elif (${MACHINE} == "tahoe")
SRCS+=	fgets.c fputs.c puts.c
.elif (${MACHINE} == "vax")
SRCS+=	fgets.s fputs.s puts.s
.endif
E 3
I 3
D 13
	fgetline.c fgetpos.c fgets.c fileno.c findfp.c flags.c fopen.c \
E 13
I 13
	fgetln.c fgetpos.c fgets.c fileno.c findfp.c flags.c fopen.c \
E 13
	fprintf.c fpurge.c fputc.c fputs.c fread.c freopen.c fscanf.c \
	fseek.c fsetpos.c ftell.c funopen.c fvwrite.c fwalk.c fwrite.c \
D 11
	getc.c getchar.c gets.c getw.c makebuf.c perror.c printf.c putc.c \
	putchar.c puts.c putw.c refill.c remove.c rewind.c rget.c scanf.c \
	setbuf.c setbuffer.c setvbuf.c snprintf.c sprintf.c sscanf.c \
D 4
	stdio.c tempnam.c tmpfile.c tmpnam.c ungetc.c vfprintf.c vfscanf.c \
	vprintf.c vsnprintf.c vsprintf.c wbuf.c wsetup.c
E 4
I 4
D 8
	stdio.c strerror.c tempnam.c tmpfile.c tmpnam.c ungetc.c vfprintf.c \
E 8
I 8
	stdio.c tempnam.c tmpfile.c tmpnam.c ungetc.c vfprintf.c \
E 11
I 11
	getc.c getchar.c gets.c getw.c makebuf.c mktemp.c perror.c \
	printf.c putc.c putchar.c puts.c putw.c refill.c remove.c rewind.c \
	rget.c scanf.c setbuf.c setbuffer.c setvbuf.c snprintf.c sprintf.c \
	sscanf.c stdio.c tempnam.c tmpfile.c tmpnam.c ungetc.c vfprintf.c \
E 11
E 8
D 6
	vfscanf.c vprintf.c vsnprintf.c vsprintf.c wbuf.c wsetup.c
E 6
I 6
	vfscanf.c vprintf.c vscanf.c vsnprintf.c vsprintf.c vsscanf.c \
D 9
	wbuf.c wsetup.c
E 9
I 9
D 14
	wbuf.c wsetup.c zopen.c
E 14
I 14
	wbuf.c wsetup.c
E 14
E 9
E 6
E 4
E 3

D 2
MAN3+=	fclose.0 ferror.0 fgets.0 fopen.0 fread.0 fseek.0 getc.0 \
	gets.0 printf.0 putc.0 puts.0 scanf.0 setbuf.0 stdio.0 ungetc.0 \
E 2
I 2
D 4
MAN3+=	fclose.0 ferror.0 fflush.0 fgets.0 fopen.0 fread.0 fseek.0 getc.0 \
	gets.0 perror.0 printf.0 putc.0 puts.0 scanf.0 setbuf.0 stdio.0 \
	tmpnam.0 ungetc.0 
E 4
I 4
D 13
MAN3+=	fclose.0 ferror.0 fflush.0 fgetline.0 fgets.0 fopen.0 fputs.0 \
E 13
I 13
MAN3+=	fclose.0 ferror.0 fflush.0 fgetln.0 fgets.0 fopen.0 fputs.0 \
E 13
	fread.0 fseek.0 funopen.0 getc.0 mktemp.0 printf.0 putc.0 remove.0 \
D 8
	scanf.0 setbuf.0 stdio.0 strerror.0 tmpnam.0 ungetc.0
E 8
I 8
D 9
	scanf.0 setbuf.0 stdio.0 tmpnam.0 ungetc.0
E 9
I 9
D 14
	scanf.0 setbuf.0 stdio.0 tmpnam.0 ungetc.0 zopen.0
E 14
I 14
	scanf.0 setbuf.0 stdio.0 tmpnam.0 ungetc.0
E 14
E 9
E 8
E 4
E 2

D 2
MLINKS+=fclose.3 fflush.3
E 2
MLINKS+=ferror.3 clearerr.3 ferror.3 feof.3 ferror.3 fileno.3
I 4
MLINKS+=fflush.3 fpurge.3
MLINKS+=fgets.3 gets.3
E 4
MLINKS+=fopen.3 fdopen.3 fopen.3 freopen.3
I 4
MLINKS+=fputs.3 puts.3
E 4
MLINKS+=fread.3 fwrite.3
D 4
MLINKS+=fseek.3 ftell.3 fseek.3 rewind.3
E 4
I 4
MLINKS+=fseek.3 fgetpos.3 fseek.3 fsetpos.3 fseek.3 ftell.3 fseek.3 rewind.3
MLINKS+=funopen.3 fropen.3 funopen.3 fwopen.3
E 4
MLINKS+=getc.3 fgetc.3 getc.3 getchar.3 getc.3 getw.3
I 2
D 4
MLINKS+=perror.3 strerror.3 perror.3 sys_errlist.3 perror.3 sys_nerr.3
E 2
MLINKS+=printf.3 fprintf.3 printf.3 sprintf.3 printf.3 vfprintf.3 \
	printf.3 vprintf.3 printf.3 vsprintf.3
E 4
I 4
MLINKS+=mktemp.3 mkstemp.3
MLINKS+=printf.3 fprintf.3 printf.3 snprintf.3 printf.3 sprintf.3 \
	printf.3 vfprintf.3 printf.3 vprintf.3 printf.3 vsnprintf.3 \
	printf.3 vsprintf.3 
E 4
MLINKS+=putc.3 fputc.3 putc.3 putchar.3 putc.3 putw.3
D 4
MLINKS+=puts.3 fputs.3
MLINKS+=scanf.3 fscanf.3 scanf.3 sscanf.3
MLINKS+=setbuf.3 setbuffer.3 setbuf.3 setlinebuf.3
I 2
MLINKS+=tmpnam.3 tmpfile.3 tmpnam.3 tempnam.3
E 4
I 4
D 5
MLINKS+=scanf.3 fscanf.3 scanf.3 sscanf.3 vfscanf.3
E 5
I 5
D 6
MLINKS+=scanf.3 fscanf.3 scanf.3 sscanf.3 scanf.3 vfscanf.3
E 6
I 6
MLINKS+=scanf.3 fscanf.3 scanf.3 sscanf.3 scanf.3 vfscanf.3 scanf.3 vscanf.3 \
	scanf.3 vsscanf.3
E 6
E 5
MLINKS+=setbuf.3 setbuffer.3 setbuf.3 setlinebuf.3 setbuf.3 setvbuf.3
D 8
MLINKS+=strerror.3 perror.3
E 8
MLINKS+=tmpnam.3 tempnam.3 tmpnam.3 tmpfile.3
E 4
E 2
E 1
