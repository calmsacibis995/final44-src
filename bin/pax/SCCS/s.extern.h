h36107
s 00001/00001/00258
d D 8.2 94/04/18 14:02:19 bostic 7 6
c new version from Keith Muller (muller@sdcc3.ucsd.edu)
e
s 00002/00002/00257
d D 8.1 93/05/31 14:52:38 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00258
d D 1.5 93/04/12 17:46:10 muller 5 4
c put the wrong prototype name in for ar_drain().
e
s 00001/00000/00258
d D 1.4 93/03/12 14:13:46 muller 4 3
c added routine to drain pipes. bug from donn seeley.
e
s 00000/00001/00258
d D 1.3 93/01/16 16:37:34 muller 3 2
c made copyright a static
e
s 00002/00000/00257
d D 1.2 93/01/14 15:13:57 muller 2 1
c added support for -D and -Y.
e
s 00257/00000/00000
d D 1.1 92/12/17 19:22:20 muller 1 0
c date and time created 92/12/17 19:22:20 by muller
e
u
U
t
T
I 1
/*-
 * Copyright (c) 1992 Keith Muller.
D 6
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * This code is derived from software contributed to Berkeley by
 * Keith Muller of the University of California, San Diego.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/*
 * External references from each source file
 */

#include <sys/cdefs.h>

/*
 * ar_io.c
 */
extern char *arcname;
int ar_open __P((char *));
void ar_close __P((void));
I 4
D 5
void ar_flush __P((void));
E 5
I 5
void ar_drain __P((void));
E 5
E 4
int ar_set_wr __P((void));
int ar_app_ok __P((void));
int ar_read __P((register char *, register int));
int ar_write __P((register char *, register int));
int ar_rdsync __P((void));
int ar_fow __P((off_t, off_t *));
int ar_rev __P((off_t ));
int ar_next __P((void));

/*
 * ar_subs.c
 */
extern u_long flcnt;
void list __P((void));
void extract __P((void));
void append __P((void));
void archive __P((void));
void copy __P((void));

/*
 * buf_subs.c
 */
extern int blksz;
extern int wrblksz;
extern int maxflt;
extern int rdblksz;
extern off_t wrlimit;
extern off_t rdcnt;
extern off_t wrcnt;
int wr_start __P((void));
int rd_start __P((void));
void cp_start __P((void));
int appnd_start __P((off_t));
int rd_sync __P((void));
void pback __P((char *, int));
int rd_skip __P((off_t));
void wr_fin __P((void));
int wr_rdbuf __P((register char *, register int));
int rd_wrbuf __P((register char *, register int));
int wr_skip __P((off_t));
int wr_rdfile __P((ARCHD *, int, off_t *));
int rd_wrfile __P((ARCHD *, int, off_t *));
void cp_file __P((ARCHD *, int, int));
int buf_fill __P((void));
int buf_flush __P((register int));

/*
 * cache.c
 */
int uidtb_start __P((void));
int gidtb_start __P((void));
int usrtb_start __P((void));
int grptb_start __P((void));
char * name_uid __P((uid_t, int));
char * name_gid __P((gid_t, int));
int uid_name __P((char *, uid_t *));
int gid_name __P((char *, gid_t *));

/*
 * cpio.c
 */
int cpio_strd __P((void));
int cpio_trail __P((register ARCHD *));
int cpio_endwr __P((void));
int cpio_id __P((char *, int));
int cpio_rd __P((register ARCHD *, register char *));
off_t cpio_endrd __P((void));
int cpio_stwr __P((void));
int cpio_wr __P((register ARCHD *));
int vcpio_id __P((char *, int));
int crc_id __P((char *, int));
int crc_strd __P((void));
int vcpio_rd __P((register ARCHD *, register char *));
off_t vcpio_endrd __P((void));
int crc_stwr __P((void));
int vcpio_wr __P((register ARCHD *));
int bcpio_id __P((char *, int));
int bcpio_rd __P((register ARCHD *, register char *));
off_t bcpio_endrd __P((void));
int bcpio_wr __P((register ARCHD *));

/*
 * file_subs.c
 */
int file_creat __P((register ARCHD *));
void file_close __P((register ARCHD *, int));
int lnk_creat __P((register ARCHD *));
int cross_lnk __P((register ARCHD *));
int chk_same __P((register ARCHD *));
int node_creat __P((register ARCHD *));
int unlnk_exist __P((register char *, register int));
int chk_path __P((register char *, uid_t, gid_t));
void set_ftime __P((char *fnm, time_t mtime, time_t atime, int frc));
int set_ids __P((char *, uid_t, gid_t));
void set_pmode __P((char *, mode_t));
int file_write __P((int, char *, register int, int *, int *, int, char *));
void file_flush __P((int, char *, int));
void rdfile_close __P((register ARCHD *, register int *));
int set_crc __P((register ARCHD *, register int));

/*
 * ftree.c
 */
int ftree_start __P((void));
int ftree_add __P((register char *));
void ftree_sel __P((register ARCHD *));
void ftree_chk __P((void));
int next_file __P((register ARCHD *));

/*
 * gen_subs.c
 */
void ls_list __P((register ARCHD *, time_t));
void ls_tty __P((register ARCHD *));
void zf_strncpy __P((register char *, register char *, int));
int l_strncpy __P((register char *, register char *, int));
u_long asc_ul __P((register char *, int, register int));
int ul_asc __P((u_long, register char *, register int, register int));
#ifndef NET2_STAT
u_quad_t asc_uqd __P((register char *, int, register int));
int uqd_asc __P((u_quad_t, register char *, register int, register int));
#endif

/*
 * options.c
 */
extern FSUB fsub[];
extern int ford[];
void options __P((register int, register char **));
OPLIST * opt_next __P((void));
int opt_add __P((register char *));
int bad_opt __P((void));

/*
 * pat_rep.c
 */
int rep_add __P((register char *));
int pat_add __P((char *));
void pat_chk __P((void));
int pat_sel __P((register ARCHD *));
int pat_match __P((register ARCHD *));
int mod_name __P((register ARCHD *));
int set_dest __P((register ARCHD *, char *, int));

/*
 * pax.c
 */
D 3
extern char copyright[];
E 3
extern int act;
extern FSUB *frmt;
extern int cflag;
extern int dflag;
extern int iflag;
extern int kflag;
extern int lflag;
extern int nflag;
extern int tflag;
extern int uflag;
extern int vflag;
I 2
extern int Dflag;
E 2
extern int Hflag;
extern int Lflag;
extern int Xflag;
I 2
extern int Yflag;
E 2
extern int Zflag;
extern int vfpart;
extern int patime;
extern int pmtime;
extern int pmode;
extern int pids;
extern int exit_val;
extern int docrc;
extern char *dirptr;
extern char *ltmfrmt;
I 7
extern char *argv0;
E 7
int main __P((int, char **));
D 7
void usage __P((void));
E 7
void sig_cleanup __P((int));

/*
 * sel_subs.c
 */
int sel_chk __P((register ARCHD *));
int grp_add __P((register char *));
int usr_add __P((register char *));
int trng_add __P((register char *));

/*
 * tables.c
 */
int lnk_start __P((void));
int chk_lnk __P((register ARCHD *));
void purg_lnk __P((register ARCHD *));
void lnk_end __P((void));
int ftime_start __P((void));
int chk_ftime __P((register ARCHD *));
int name_start __P((void));
int add_name __P((register char *, int, char *));
void sub_name __P((register char *, int *));
int dev_start __P((void));
int add_dev __P((register ARCHD *));
int map_dev __P((register ARCHD *, u_long, u_long));
int atdir_start __P((void));
void atdir_end __P((void));
void add_atdir __P((char *, dev_t, ino_t, time_t, time_t));
int get_atdir __P((dev_t, ino_t, time_t *, time_t *));
int dir_start __P((void));
void add_dir __P((char *, int, struct stat *, int));
void proc_dir __P((void));
u_int st_hash __P((char *, int, int));

/*
 * tar.c
 */
int tar_endwr __P((void));
off_t tar_endrd __P((void));
int tar_trail __P((register char *, register int, register int *));
int tar_id __P((register char *, int));
int tar_opt __P((void));
int tar_rd __P((register ARCHD *, register char *));
int tar_wr __P((register ARCHD *));
int ustar_strd __P((void));
int ustar_stwr __P((void));
int ustar_id __P((char *, int));
int ustar_rd __P((register ARCHD *, register char *));
int ustar_wr __P((register ARCHD *));

/*
 * tty_subs.c
 */
int tty_init __P((void));
void tty_prnt __P((char *, ...));
int tty_read __P((char *, int));
void warn __P((int, char *, ...));
void syswarn __P((int, int, char *, ...));
E 1
