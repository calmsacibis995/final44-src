h09136
s 00002/00002/00106
d D 8.1 93/06/11 15:11:39 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00028/00024/00080
d D 7.3 93/04/20 06:35:20 torek 3 2
c update from van: add backlog, renumber ioctls for mixing with SunOS
e
s 00005/00000/00099
d D 7.2 92/07/21 16:41:26 bostic 2 1
c update the contribution notice; LBL requires acknowledgement
e
s 00099/00000/00000
d D 7.1 92/07/13 00:42:59 torek 1 0
c date and time created 92/07/13 00:42:59 by torek
e
u
U
t
T
I 1
/*
D 4
 * Copyright (c) 1991, 1992 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1991, 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley.
 *
I 2
 * All advertising materials mentioning features or use of this software
 * must display the following acknowledgement:
 *	This product includes software developed by the University of
D 3
 *	California, Lawrence Berkeley Laboratories.
E 3
I 3
 *	California, Lawrence Berkeley Laboratory.
E 3
 *
E 2
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *
D 3
 * from: $Header: bsd_audioio.h,v 1.4 92/07/13 00:31:22 torek Exp $ (LBL)
E 3
I 3
 * from: $Header: bsd_audioio.h,v 1.5 92/11/21 20:46:46 van Exp $ (LBL)
E 3
 */

#ifndef _BSD_AUDIOIO_H_
#define _BSD_AUDIOIO_H_

/*
 * /dev/audio ioctls.  needs comments!
 */
D 3
#define AUDIO_MIN_GAIN 0
#define AUDIO_MAX_GAIN 255
E 3
I 3
#define AUDIO_MIN_GAIN (0)
#define AUDIO_MAX_GAIN (255)
E 3

D 3
#define AUDIO_ENCODING_ULAW 1
#define AUDIO_ENCODING_ALAW 2
E 3
I 3
#define AUDIO_ENCODING_ULAW (1)
#define AUDIO_ENCODING_ALAW (2)
E 3

struct audio_prinfo {
	u_int	sample_rate;
	u_int	channels;
	u_int	precision;
	u_int	encoding;
	u_int	gain;
	u_int	port;
I 3
	u_long	seek;		/* BSD extension */
	u_int	ispare[3];
E 3
	u_int	samples;
I 3
	u_int	eof;
E 3

	u_char	pause;
	u_char	error;
	u_char	waiting;
I 3
	u_char	cspare[3];
E 3
	u_char	open;
I 3
	u_char	active;
E 3

D 3
	/* BSD extensions */
	u_long	seek;
E 3
};

struct audio_info {
	struct	audio_prinfo play;
	struct	audio_prinfo record;
	u_int	monitor_gain;
	/* BSD extensions */
	u_int	blocksize;	/* input blocking threshold */
	u_int	hiwat;		/* output high water mark */
	u_int	lowat;		/* output low water mark */
I 3
	u_int	backlog;	/* samples of output backlog to gen. */
E 3
};
typedef struct audio_info audio_info_t;

#define AUDIO_INITINFO(p)\
	(void)memset((void *)(p), 0xff, sizeof(struct audio_info))

#if (defined(sun) || defined(ibm032)) && !defined(__GNUC__)
D 3
#define AUDIO_GETINFO	_IOR(A, 1, struct audio_info)
#define AUDIO_SETINFO	_IOWR(A, 2, struct audio_info)
#define AUDIO_DRAIN	_IO(A, 3)
#define AUDIO_FLUSH	_IO(A, 4)
#define AUDIO_WSEEK	_IOR(A, 5, u_long)
#define AUDIO_RERROR	_IOR(A, 6, int)
#define AUDIO_GETMAP	_IOR(A, 20, struct mapreg)
#define	AUDIO_SETMAP	_IOW(A, 21, struct mapreg)
E 3
I 3
#define AUDIO_GETINFO	_IOR(A, 21, struct audio_info)
#define AUDIO_SETINFO	_IOWR(A, 22, struct audio_info)
#define AUDIO_DRAIN	_IO(A, 23)
#define AUDIO_FLUSH	_IO(A, 24)
#define AUDIO_WSEEK	_IOR(A, 25, u_long)
#define AUDIO_RERROR	_IOR(A, 26, int)
#define AUDIO_GETMAP	_IOR(A, 27, struct mapreg)
#define	AUDIO_SETMAP	_IOW(A, 28, struct mapreg)
E 3
#else
D 3
#define AUDIO_GETINFO	_IOR('A', 1, struct audio_info)
#define AUDIO_SETINFO	_IOWR('A', 2, struct audio_info)
#define AUDIO_DRAIN	_IO('A', 3)
#define AUDIO_FLUSH	_IO('A', 4)
#define AUDIO_WSEEK	_IOR('A', 5, u_long)
#define AUDIO_RERROR	_IOR('A', 6, int)
#define AUDIO_GETMAP	_IOR('A', 20, struct mapreg)
#define	AUDIO_SETMAP	_IOW('A', 21, struct mapreg)
E 3
I 3
#define AUDIO_GETINFO	_IOR('A', 21, struct audio_info)
#define AUDIO_SETINFO	_IOWR('A', 22, struct audio_info)
#define AUDIO_DRAIN	_IO('A', 23)
#define AUDIO_FLUSH	_IO('A', 24)
#define AUDIO_WSEEK	_IOR('A', 25, u_long)
#define AUDIO_RERROR	_IOR('A', 26, int)
#define AUDIO_GETMAP	_IOR('A', 27, struct mapreg)
#define	AUDIO_SETMAP	_IOW('A', 28, struct mapreg)
E 3
#endif

#define AUDIO_SPEAKER   	1
#define AUDIO_HEADPHONE		2

/*
 * Low level interface.
 */
struct mapreg {
	u_short	mr_x[8];
	u_short	mr_r[8];
	u_short	mr_gx;
	u_short	mr_gr;
	u_short	mr_ger;
	u_short	mr_stgr;
	u_short	mr_ftgr;
	u_short	mr_atgr;
	u_char	mr_mmr1;
	u_char	mr_mmr2;
};

#endif /* _BSD_AUDIOIO_H_ */
E 1
