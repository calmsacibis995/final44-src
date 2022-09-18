h57528
s 00002/00001/01899
d D 8.13 95/01/09 18:22:12 cgd 168 167
c return types, 64-bit changes: ioctl cmd -> u_long, casts, etc.
e
s 00002/00002/01898
d D 8.12 94/08/22 10:19:53 mckusick 167 166
c use new queue.h data structures
e
s 00002/00002/01898
d D 8.11 94/08/15 11:57:50 mckusick 166 165
c uucp dies if it cannot repeatedly set the same controlling tty
e
s 00002/00002/01898
d D 8.10 94/08/14 21:56:41 mckusick 165 164
c cannot get new controlling tty when you already have one
e
s 00007/00004/01893
d D 8.9 94/05/09 21:39:42 mckusick 164 163
c cope with partial outputting of tabs when output list is full (from cgd)
e
s 00005/00001/01892
d D 8.8 94/01/21 17:17:58 bostic 163 162
c add USL's copyright notice
e
s 00006/00001/01887
d D 8.7 94/01/06 16:42:03 mckusick 162 161
c update to approximate process resident set size (from hibler and cgd)
e
s 00002/00001/01886
d D 8.6 94/01/02 13:41:01 bostic 161 160
c clear PENDIN if ICANON is cleared
c retain the PENDIN flag if set when ICANON is set
c From: karels@BSDI.COM (Mike Karels)
e
s 00002/00001/01885
d D 8.5 93/11/15 20:57:00 mckusick 160 159
c move initialization of `cc' above loop: as it used to be
e
s 00102/00098/01784
d D 8.4 93/09/23 15:28:18 bostic 159 158
c changes for 4.4BSD-Lite requested by USL
e
s 00012/00012/01870
d D 8.3 93/09/21 07:32:03 bostic 158 157
c changes for 4.4BSD-Lite requested by USL
e
s 00954/00964/00928
d D 8.2 93/09/05 09:39:53 bostic 157 156
c Cleanups for 4.4BSD-Lite
e
s 00002/00002/01890
d D 8.1 93/06/10 21:59:01 bostic 156 155
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/01891
d D 7.56 92/12/15 16:28:01 torek 155 154
c TIOCSTI fails for 8-bit chars (from comp.unix.bsd)
e
s 00013/00013/01879
d D 7.55 92/10/11 10:38:33 bostic 154 153
c make kernel includes standard
e
s 00001/00001/01891
d D 7.54 92/08/24 17:29:57 marc 153 152
c echo quoted ^? correctly
e
s 00001/00001/01891
d D 7.53 92/08/24 17:08:01 marc 152 151
c some flags got moved around and code wasen't consistent
e
s 00001/00001/01891
d D 7.52 92/07/12 17:20:15 pendry 151 150
c MIN -> min, MAX -> max
e
s 00009/00015/01883
d D 7.51 92/07/08 00:48:52 torek 150 149
c lint; fix FIONREAD; new rusage calculations
e
s 00001/00001/01897
d D 7.50 92/02/25 17:14:49 mckusick 149 148
c averunnable now a structure
e
s 00007/00020/01891
d D 7.49 92/02/15 21:08:41 mckusick 148 147
c convert to use new select interface, selrecord/selwakeup
e
s 00051/00012/01860
d D 7.48 92/02/14 13:59:32 torek 147 146
c misc nits, additions for sun4c
e
s 00002/00001/01870
d D 7.47 91/09/09 16:27:25 marc 146 145
c only send SIGINFO on ^T if ISIG is set
e
s 00004/00000/01867
d D 7.46 91/09/05 16:36:51 bostic 145 144
c 'a b c^W' erases 'b c' instead of just 'c'
e
s 00002/00001/01865
d D 7.45 91/08/02 12:18:53 karels 144 143
c curproc is null if no one is running, but ignore curproc unless wait is true
e
s 00039/00063/01827
d D 7.44 91/05/28 15:54:01 bostic 143 142
c use the printf routines in subr_prf instead of rolling out own
e
s 00008/00004/01882
d D 7.43 91/05/16 17:49:33 marc 142 141
c pass flags to l_close, dont ttywait if IO_NDELAY (revoke)
e
s 00006/00004/01880
d D 7.42 91/05/09 21:21:30 bostic 141 140
c new copyright; att/bsd/shared
e
s 00123/00099/01761
d D 7.41 91/05/07 20:07:13 karels 140 139
c redo partab using #defines; meta chars are normal; simpler flushes;
c fix up comments
e
s 00000/00011/01860
d D 7.40 91/05/05 14:28:16 bostic 139 138
c move ttyprintf to subr_prf.c
e
s 00023/00003/01848
d D 7.39 91/04/20 16:11:39 karels 138 137
c rm user.h, reg.h; move ttspeedtab back for drivers;
c change "running" to "iowait" for sleeping procs without wmesg;
c (marc) add TIOCDRAIN ioctl
e
s 00080/00183/01771
d D 7.38 91/03/17 15:42:13 karels 137 136
c more-or-less working with new proc & user structs
e
s 00001/00001/01953
d D 7.37 90/12/05 17:37:47 mckusick 136 135
c update for new VM
e
s 00022/00017/01932
d D 7.36 90/12/05 16:27:01 mckusick 135 134
c checked in for Marc to create checkpoint for VM merge
e
s 00003/00002/01946
d D 7.35 90/07/27 22:43:02 marc 134 133
c (by karels) typo in TIOCSETAF, was always flushing; can't use 0 for no pgrp;
c ttyrub newline could maybe happen???
e
s 00167/00185/01781
d D 7.34 90/06/28 18:50:10 marc 133 132
c reformat EXTPROC code
e
s 00046/00032/01920
d D 7.33 90/06/21 17:56:58 marc 132 131
c ttysleep - to catch revoked terminal
e
s 00001/00001/01951
d D 7.32 90/06/20 18:05:39 marc 131 130
c VINFO -> VSTATUS
e
s 00001/00000/01951
d D 7.31 90/06/20 18:04:07 hibler 130 129
c add OTIOCCONS
e
s 00001/00001/01950
d D 7.30 90/06/14 13:22:26 marc 129 128
c VFLUSHO -> VDISCARD
e
s 00026/00015/01925
d D 7.29 90/06/14 13:20:42 marc 128 127
c check for revoked line
e
s 00030/00012/01910
d D 7.28 90/06/05 10:50:43 marc 127 126
c pgsignal takes extra arg.  telnet linemode changes (dab@cray).
e
s 00003/00003/01919
d D 7.27 90/05/25 15:17:44 mckusick 126 125
c update from Mike Hibler at Utah
e
s 00012/00011/01910
d D 7.26 90/05/17 15:51:12 marc 125 124
c abolish NOHANG flag.  signal session leader on lost carrier (not fgpgrp), put CLOCAL check on carrier transitions
e
s 00009/00007/01912
d D 7.25 90/05/16 15:50:34 mckusick 124 123
c vinfo under control of ICANON, extra checks in TIOCCONS
e
s 00002/00001/01917
d D 7.24 90/05/04 15:00:36 marc 123 122
c lflag can change while we sleep in ttread.  
e
s 00002/00002/01916
d D 7.23 90/05/04 10:57:50 marc 122 121
c change wchan messages to consistant format
e
s 00141/00014/01777
d D 7.22 90/05/01 11:19:27 marc 121 120
c  ^T
e
s 00132/00117/01659
d D 7.21 90/04/03 21:49:00 karels 120 119
c tsleep; unwind on interrupt; don't back up uio then copyin again
c after blocking; KNF; strings for sleep messages; SIGINFO; NOKERNINFO lflag
c allow input to be read from queue after carrier drops
e
s 00011/00001/01765
d D 7.20 90/02/07 15:42:11 marc 119 118
c check for compat ioctls. pgrp can now be null.
e
s 00061/00045/01705
d D 7.19 89/11/20 18:15:14 marc 118 117
c controlling terminal is a vnode
e
s 00084/00025/01666
d D 7.18 89/10/27 01:14:28 marc 117 116
c cleanups, add ^T prototype, CIGNORE instead of separate ioctls
e
s 00007/00010/01684
d D 7.17 89/05/09 17:02:43 mckusick 116 115
c merge in vnodes
e
s 00086/00038/01608
d D 7.16 89/05/01 23:00:44 marc 115 114
c clocal, nonblock, other carrier related stuff
e
s 00003/00003/01643
d D 7.15 89/04/26 19:50:29 mckusick 114 113
c use new form of suser()
e
s 00002/00002/01644
d D 7.14 89/04/25 14:50:02 mckusick 113 112
c ../machine => machine
e
s 00497/00532/01149
d D 7.13 88/10/18 15:16:44 marc 112 111
x 110
c new terminal driver
e
s 00002/00002/01679
d D 7.12 88/05/26 09:01:32 karels 111 110
x 110
c lint
e
s 00384/00299/01382
d D 7.11 88/04/08 20:37:51 marc 110 109
c minor fix in ^X where rocount != rawq.c_cc
e
s 00001/00001/01680
d D 7.10 88/01/28 09:41:17 karels 109 108
c typo
e
s 00002/00002/01679
d D 7.9 88/01/05 16:36:54 bostic 108 107
c fix CTRL macro; for ANSI C
e
s 00001/00001/01680
d D 7.8 87/10/05 09:57:46 mckusick 107 106
c avoid call through zero (t_oproc) when certain flags are set on a pty
e
s 00009/00011/01672
d D 7.7 87/08/23 18:23:44 karels 106 105
c call ttystart before checking for queue overflow,
c instead of afterward (if it's synchronous, we hang); call driver oproc
c at normal priority, and let it check for timeout,etc (they all do anyway).
e
s 00000/00002/01683
d D 7.6 87/07/21 18:23:53 mckusick 105 103
c delete unneeded header files
e
s 00003/00000/01685
d R 7.6 87/07/07 16:58:24 sklower 104 103
c temporary change to count cooked char processing.
e
s 00007/00003/01678
d D 7.5 87/03/29 20:43:35 karels 103 102
c don't let uprintf be interrupted (callers hold locked inodes, etc)
e
s 00018/00000/01663
d D 7.4 87/02/19 17:30:02 karels 102 101
c TIOCCONS
e
s 00011/00025/01652
d D 7.3 86/11/03 12:00:20 karels 101 100
c merge in tahoe support
e
s 00014/00000/01663
d D 7.2 86/08/09 18:02:32 karels 100 99
c add substitutable cnputc, user console
e
s 00001/00001/01662
d D 7.1 86/06/05 00:08:59 mckusick 99 98
c 4.3BSD release version
e
s 00005/00003/01658
d D 6.26 86/02/23 23:10:31 karels 98 97
c lint
e
s 00010/00008/01651
d D 6.25 85/12/10 18:36:04 karels 97 96
c don't flush when not changing line disciplines
e
s 00002/00001/01657
d D 6.24 85/11/06 19:18:01 karels 96 95
c let's get it all
e
s 00015/00000/01643
d D 6.23 85/11/06 10:10:41 karels 95 94
c move nullmodem to tty.c, maintain TS_CARR_ON
e
s 00088/00013/01555
d D 6.22 85/11/04 18:11:05 karels 94 93
c use modem entry in linesw to signal carrier change; split line-disc close
c from tty close
e
s 00006/00012/01562
d D 6.21 85/08/22 14:41:07 karels 93 92
c use sigmask() instead of private definitions
e
s 00002/00002/01572
d D 6.20 85/08/13 05:24:34 lepreau 92 91
c add PASS8: pass all 8 bits of input
e
s 00007/00001/01567
d D 6.19 85/06/08 14:45:13 mckusick 91 90
c Add copyright
e
s 00018/00024/01550
d D 6.18 85/06/08 12:29:54 bloom 90 89
c fix carrier drop handling in ttread & try improving LCASE mode
e
s 00036/00022/01538
d D 6.17 85/06/03 08:41:19 bloom 89 88
c optimization and handle closure during sleeps correctly
e
s 00000/00014/01560
d D 6.16 85/05/27 15:06:16 mckusick 88 87
c C definition of scanc moves to ufs_subr.c
e
s 00005/00010/01569
d D 6.15 85/04/17 17:14:27 bloom 87 86
c cleanup and get rid of race
e
s 00001/00003/01578
d D 6.14 85/02/08 10:12:21 karels 86 85
c was too restrictive on SPGRP (it's all a crock anyway)
e
s 00021/00000/01560
d D 6.13 84/12/31 12:39:41 bloom 85 84
c Added ioctls for window size changes, process group checking
e
s 00037/00024/01523
d D 6.12 84/12/20 15:00:22 karels 84 83
c don't flush when opening open terminal; missing splx; a few more
c sensiblity tests; rename spl's to spltty
e
s 00002/00000/01545
d D 6.11 84/09/10 18:16:33 mckusick 83 82
c security fix from George Goble
e
s 00014/00014/01531
d D 6.10 84/08/29 20:22:27 bloom 82 81
c Change to includes.  no more ../h
e
s 00002/00002/01543
d D 6.9 84/02/15 20:50:41 karels 81 80
c t_delct unused; use t_canq.c_cc instead
e
s 00001/00001/01544
d D 6.8 83/12/16 14:35:04 karels 80 79
c don't sign extend local flags when shifting for TIOCLGET
e
s 00008/00004/01537
d D 6.7 83/10/01 17:55:27 karels 79 77
c fix the rest of the signal value checks
e
s 00008/00004/01537
d R 6.7 83/10/01 14:34:29 karels 78 77
c fix the rest of the signal value checking
e
s 00009/00003/01532
d D 6.6 83/09/28 10:47:15 karels 77 76
c in cooked tandem mode, no stopc until at least 1 delim
e
s 00001/00001/01534
d D 6.5 83/09/25 19:40:37 karels 76 75
c scanc returns count remaining, not pointer
e
s 00001/00001/01534
d D 6.4 83/09/25 16:24:21 karels 75 74
c return EWOULDBLOCK on read w/ no carrier or NBIO in raw mode
e
s 00005/00003/01530
d D 6.3 83/09/25 12:44:03 karels 74 73
c new signal code for SIGTTOU;
c check for negative ldisc
e
s 00004/00004/01529
d D 6.2 83/09/09 17:26:18 mckusick 73 72
c get rid of passuc as it is equivalent to ureadc (shannon)
e
s 00000/00000/01533
d D 6.1 83/07/29 06:38:02 sam 72 71
c 4.2 distribution
e
s 00002/00001/01531
d D 4.47 83/07/09 00:44:32 sam 71 70
c parenthesis problem; wait a long time past col 127
e
s 00010/00003/01522
d D 4.46 83/07/06 23:38:45 sam 70 68
c correct terminal delays (kre)
e
s 00006/00003/01522
d R 4.46 83/07/06 23:13:26 sam 69 68
c proper calculation of tty delays
e
s 00002/00002/01523
d D 4.45 83/07/06 19:25:40 sam 68 66
c wait for silo's to drain on output (from kre)
e
s 00002/00002/01523
d R 4.45 83/07/06 18:55:50 sam 67 66
c hang while device is waiting for silo to flush
e
s 00001/00000/01524
d D 4.44 83/07/06 16:22:21 sam 66 65
c fix from edward for flushing type ahead on switch to CBREAK
e
s 00001/00001/01523
d D 4.43 83/07/01 02:19:45 sam 65 64
c purge #if sun's
e
s 00012/00027/01512
d D 4.42 83/06/13 02:58:11 sam 64 63
c let's not confuse the issue anymore than necessary
e
s 00138/00077/01401
d D 4.41 83/05/27 12:47:59 sam 63 62
c merge of bill's code plus lint (plus, of course, cleanup of bill's bugs)
e
s 00008/00005/01470
d D 4.40 83/02/10 16:03:32 sam 62 61
c bogus return value; try to reopen old ldisp one TIOCSETD failure
e
s 00005/00005/01470
d D 4.39 83/01/17 16:25:48 sam 61 60
c beep lots more; don't give the sun scanc
e
s 00018/00022/01457
d D 4.38 82/12/19 19:05:38 sam 60 58
c tandem mode bug fix from Mike Karels; purge spl0's and t_char
e
s 00018/00022/01457
d R 4.38 82/12/19 17:35:48 sam 59 58
c tandem mode bug fix from Mike Karels; cleanup spl0's; purge t_char
e
s 00002/00001/01477
d D 4.37 82/12/17 11:46:52 sam 58 57
c sun merge
e
s 00054/00082/01424
d D 4.36 82/12/13 20:54:21 sam 57 56
c strip old ioctl's out and put them tty_xxx.c
e
s 00530/00381/00976
d D 4.35 82/12/07 16:44:28 sam 56 54
c major reorganization; t_lstate & t_lflags purged
e
s 00499/00368/00989
d R 4.35 82/12/05 21:58:32 sam 55 54
c reorganized; t_lstate and t_lflags no more; rewrite of ttyinput 
c and ttyoutput, among others
e
s 00011/00000/01346
d D 4.34 82/11/22 17:16:55 sam 54 53
c put back TIOCSTI
e
s 00001/00001/01345
d D 4.33 82/10/31 00:58:12 root 53 52
c very high watermarks for 19.2 and 38.4k baud
e
s 00004/00008/01342
d D 4.32 82/10/17 14:05:13 root 52 51
c fix lint
e
s 00025/00062/01325
d D 4.31 82/10/17 11:29:29 root 51 50
c ioctl and open routines return value
e
s 00019/00030/01368
d D 4.30 82/10/13 22:08:27 root 50 49
c return errors from ioctl routines and internal ldisc routines
e
s 00001/00000/01397
d D 4.29 82/09/12 02:58:20 root 49 48
c kernel.h include for lbolt
e
s 00020/00009/01377
d D 4.28 82/08/22 20:41:22 root 48 47
c uio'd
e
s 00012/00004/01374
d D 4.27 82/08/13 00:04:30 wnj 47 46
c fixes to get uio'd readi for char devs
e
s 00001/00001/01377
d D 4.26 82/08/04 21:43:25 sam 46 45
c ^Y being recognized in old line discipline
e
s 00108/00165/01270
d D 4.25 82/08/01 19:21:27 sam 45 44
c new ioctl's
e
s 00818/00000/00617
d D 4.24 82/07/24 18:11:46 root 44 43
c merge with calder
e
s 00050/00001/00567
d D 4.23 82/07/15 20:45:06 kre 43 42
c put partab[] def'n here
e
s 00013/00000/00555
d D 4.22 82/03/15 04:50:03 wnj 42 41
c fix to mode resetting
e
s 00005/00001/00550
d D 4.21 82/01/30 19:09:49 wnj 41 40
c avoid SDETACH botch
e
s 00004/00002/00547
d D 4.20 82/01/25 18:39:43 wnj 40 39
c bug fixes (kludge round 1)
e
s 00011/00000/00538
d D 4.19 82/01/24 18:44:44 wnj 39 38
c restore XCLUDE
e
s 00020/00000/00518
d D 4.18 82/01/19 01:58:21 wnj 38 37
c TIOCSTOP TIOCSTART
e
s 00002/00002/00516
d D 4.17 82/01/17 04:00:08 wnj 37 36
c pass rw flags to d_stop indicating which queues were flushed
e
s 00000/00001/00518
d D 4.16 82/01/15 16:41:37 wnj 36 35
c remove printf
e
s 00045/00019/00474
d D 4.15 82/01/14 17:05:45 wnj 35 34
c early non-blocking stuff
e
s 00001/00001/00492
d D 4.14 81/11/18 15:50:52 wnj 34 33
c lint
e
s 00052/00071/00441
d D 4.13 81/10/11 11:48:17 wnj 33 32
c first boot with select()
e
s 00000/00000/00512
d D 4.12 81/07/22 00:35:25 wnj 32 31
c implement LNOFLSH
e
s 00001/00001/00511
d D 4.11 81/07/09 04:07:10 root 31 30
c return(1)!
e
s 00002/00000/00510
d D 4.10 81/07/08 11:59:14 wnj 30 29
c fix FIONREAD in NTTYDISC to do ntypend(tp);
e
s 00001/00000/00509
d D 4.9 81/07/06 15:57:50 bugs 29 28
c mismatched braces
e
s 00009/00002/00500
d D 4.8 81/07/05 23:33:29 bugs 28 27
c TIOCFLUSH third arg, if non-zero, points to FREAD|FWRITE flags
e
s 00004/00000/00498
d D 4.7 81/07/05 23:24:03 bugs 27 26
c clear TTSTOP entering raw mode
e
s 00004/00000/00494
d D 4.6 81/03/22 20:59:35 wnj 26 25
c ttrstrt arg 0 prints and returns
e
s 00001/00001/00493
d D 4.5 81/03/09 01:54:58 wnj 25 24
c %G% -> %E%
e
s 00000/00012/00494
d D 4.4 81/03/09 00:34:55 wnj 24 23
c lint
e
s 00003/00010/00503
d D 4.3 80/12/17 10:47:42 wnj 23 22
c rearrange ioctl arguments; elim DIOC[SG]ETP per greg
e
s 00001/00000/00512
d D 4.2 80/11/09 22:55:05 bill 22 21
c minor lint
e
s 00000/00000/00512
d D 4.1 80/11/09 16:53:30 bill 21 20
c stamp for 4bsd
e
s 00005/00000/00507
d D 3.20 80/10/01 02:06:10 bill 20 19
c dont sdata to try to fixup mx
e
s 00005/00003/00502
d D 3.19 80/09/27 18:05:05 bill 19 18
c tthiwat/lowat based on speed; kill local erase+intr+kill
e
s 00014/00001/00491
d D 3.18 80/09/25 21:50:55 bill 18 17
c EBADF for ioctl when no carrier; fix list of forbidden bkgd ioctls
e
s 00132/00633/00360
d D 3.17 80/09/20 20:40:11 bill 17 16
c ttioctl
e
s 00011/00003/00982
d D 3.16 80/09/20 18:32:18 bill 16 15
c prevent ioctl after vhangup... FIONREAD in old tty driver
e
s 00009/00000/00976
d D 3.15 80/09/16 17:35:15 bill 15 14
c add TIOCSTI
e
s 00026/00019/00950
d D 3.14 80/09/14 13:16:24 bill 14 13
c flushtty flags
e
s 00015/00004/00954
d D 3.13 80/08/27 08:37:41 bill 13 12
c buffers allocated in sysmap, ioctls all take addresses
e
s 00003/00002/00955
d D 3.12 80/08/24 21:25:31 bill 12 11
c fix bug with c100 when *colp < 0
e
s 00002/00004/00955
d D 3.11 80/07/19 19:55:39 bill 11 10
c can OKI crap
e
s 00004/00002/00955
d D 3.10 80/07/12 20:01:17 bill 10 9
c dont reset oki line discipline
e
s 00020/00003/00937
d D 3.9 80/07/01 09:48:18 bill 9 8
c minor fixups
e
s 00001/00001/00939
d D 3.8 80/06/07 02:48:29 bill 8 7
c %H%->%G%
e
s 00005/00000/00935
d D 3.7 80/06/02 12:39:56 bill 7 6
c 
e
s 00005/00004/00930
d D 3.6 80/05/24 19:45:44 bill 6 5
c new signal stuff
e
s 00003/00005/00931
d D 3.5 80/05/18 11:38:08 bill 5 4
c first stab
e
s 00129/00027/00807
d D 3.4 80/05/15 17:10:52 bill 4 3
c hooks for new tty
e
s 00011/00000/00823
d D 3.3 80/05/09 20:55:40 bill 3 2
c run spl6 for dz SAE
e
s 00047/00028/00776
d D 3.2 80/05/08 10:13:56 bill 2 1
c modified to support TIOCSETD reasonably
e
s 00804/00000/00000
d D 3.1 80/04/09 16:04:43 bill 1 0
c date and time created 80/04/09 16:04:43 by bill
e
u
U
t
T
I 1
D 8
/*	%M%	%I%	%H%	*/
E 8
I 8
D 25
/*	%M%	%I%	%G%	*/
E 25
I 25
D 91
/*	%M%	%I%	%E%	*/
E 91
I 91
D 141
/*
D 99
 * Copyright (c) 1982 Regents of the University of California.
E 99
I 99
D 120
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 120
I 120
 * Copyright (c) 1982, 1986, 1990 Regents of the University of California.
E 120
E 99
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 141
I 141
/*-
D 156
 * Copyright (c) 1982, 1986, 1990 The Regents of the University of California.
 * Copyright (c) 1991 The Regents of the University of California.
E 156
I 156
 * Copyright (c) 1982, 1986, 1990, 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 156
D 163
 * All rights reserved.
E 163
I 163
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
E 163
 *
 * %sccs.include.redist.c%
E 141
 *
 *	%W% (Berkeley) %G%
 */
E 91
E 25
E 8

I 58
D 113
#include "../machine/reg.h"

E 113
E 58
D 56
/*
D 17
 * general TTY subroutines
E 17
I 17
 * TTY subroutines common to more than one line discipline
E 17
 */
E 56
D 82
#include "../h/param.h"
#include "../h/systm.h"
#include "../h/dir.h"
#include "../h/user.h"
I 56
#include "../h/ioctl.h"
E 56
#include "../h/tty.h"
#include "../h/proc.h"
D 33
#include "../h/mx.h"
E 33
#include "../h/inode.h"
#include "../h/file.h"
D 58
#include "../h/reg.h"
E 58
#include "../h/conf.h"
#include "../h/buf.h"
I 9
#include "../h/dk.h"
I 47
#include "../h/uio.h"
I 49
#include "../h/kernel.h"
E 82
I 82
D 154
#include "param.h"
#include "systm.h"
D 116
#include "dir.h"
E 116
D 138
#include "user.h"
E 138
#include "ioctl.h"
I 148
#include "proc.h"
E 154
I 154
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/ioctl.h>
#include <sys/proc.h>
E 154
E 148
D 117
#include "tty.h"
E 117
I 112
D 157
#define TTYDEFCHARS
E 157
I 157
#define	TTYDEFCHARS
E 157
D 117
#include "ttydefaults.h"
E 117
I 117
D 154
#include "tty.h"
E 154
I 154
#include <sys/tty.h>
E 154
E 117
D 157
#undef TTYDEFCHARS
E 157
I 157
#undef	TTYDEFCHARS
E 157
D 117
#include "termios.h"
E 117
E 112
I 110
#define TTYDEFCHARS
#include "ttydefaults.h"
#undef TTYDEFCHARS
#include "termios.h"
E 110
D 148
#include "proc.h"
E 148
D 105
#include "inode.h"
E 105
D 154
#include "file.h"
#include "conf.h"
D 105
#include "buf.h"
E 105
D 101
#include "dk.h"
E 101
I 101
#include "dkstat.h"
E 101
#include "uio.h"
#include "kernel.h"
I 116
#include "vnode.h"
E 116
I 112
#include "syslog.h"
E 154
I 154
#include <sys/file.h>
#include <sys/conf.h>
#include <sys/dkstat.h>
#include <sys/uio.h>
#include <sys/kernel.h>
#include <sys/vnode.h>
#include <sys/syslog.h>
E 154
I 113

D 138
#include "machine/reg.h"
E 138
I 138
D 154
#include "vm/vm.h"
E 154
I 154
#include <vm/vm.h>
E 154
E 138
E 113
E 112
I 110
#include "syslog.h"
E 110
E 82
E 49
E 47
E 9

I 143
D 157
static int proc_compare __P((struct proc *p1, struct proc *p2));
E 157
I 157
static int	proc_compare __P((struct proc *p1, struct proc *p2));
static int	ttnread __P((struct tty *));
static void	ttyblock __P((struct tty *tp));
static void	ttyecho __P((int, struct tty *tp));
static void	ttyrubo __P((struct tty *, int));
E 157

E 143
I 120
D 157
/* symbolic sleep message strings */
char ttyin[] = "ttyin";
char ttyout[] = "ttyout";
D 122
char ttopen[] = "ttopen";
char ttclos[] = "ttclos";
E 122
I 122
char ttopen[] = "ttyopn";
char ttclos[] = "ttycls";
E 122
char ttybg[] = "ttybg";
char ttybuf[] = "ttybuf";
E 157
I 157
/* Symbolic sleep message strings. */
char ttclos[]	= "ttycls";
char ttopen[]	= "ttyopn";
char ttybg[]	= "ttybg";
char ttybuf[]	= "ttybuf";
char ttyin[]	= "ttyin";
char ttyout[]	= "ttyout";
E 157

E 120
D 43
char	partab[];
E 43
I 43
/*
D 157
 * Table giving parity for characters and indicating
D 112
 * character classes to tty driver.  In particular,
 * if the low 6 bits are 0, then the character needs
 * no special processing on output.
E 112
I 112
 * character classes to tty driver. The 8th bit
 * indicates parity, the 7th bit indicates the character
 * is an alphameric or underscore (for ALTWERASE), and the 
 * low 6 bits indicate delay type.  If the low 6 bits are 0
D 140
 * then the character needs no special processing on output.
E 140
I 140
 * then the character needs no special processing on output;
 * classes other than 0 might be translated or (not currently)
 * require delays.
E 157
I 157
 * Table with character classes and parity. The 8th bit indicates parity,
 * the 7th bit indicates the character is an alphameric or underscore (for
 * ALTWERASE), and the low 6 bits indicate delay type.  If the low 6 bits
 * are 0 then the character needs no special processing on output; classes
 * other than 0 might be translated or (not currently) require delays.
E 157
E 140
E 112
 */
I 140
D 157
#define	PARITY(c)	(partab[c] & 0x80)
#define	ISALPHA(c)	(partab[(c)&TTY_CHARMASK] & 0x40)
#define	CCLASSMASK	0x3f
#define	CCLASS(c)	(partab[c] & CCLASSMASK)
E 157
I 157
#define	E	0x00	/* Even parity. */
#define	O	0x80	/* Odd parity. */
#define	PARITY(c)	(char_type[c] & O)
E 157
E 140
E 43

I 140
D 157
#define	E	0x00	/* even parity */
#define	O	0x80	/* odd parity */
#define	ALPHA	0x40	/* alpha or underscore */
E 157
I 157
#define	ALPHA	0x40	/* Alpha or underscore. */
#define	ISALPHA(c)	(char_type[(c) & TTY_CHARMASK] & ALPHA)
E 157

D 157
#define	NO	ORDINARY
#define	NA	ORDINARY|ALPHA
#define	CC	CONTROL
E 157
I 157
#define	CCLASSMASK	0x3f
#define	CCLASS(c)	(char_type[c] & CCLASSMASK)

E 157
#define	BS	BACKSPACE
I 157
#define	CC	CONTROL
#define	CR	RETURN
#define	NA	ORDINARY | ALPHA
E 157
#define	NL	NEWLINE
I 157
#define	NO	ORDINARY
E 157
#define	TB	TAB
#define	VT	VTAB
D 157
#define	CR	RETURN
E 157

E 140
I 43
D 157
char partab[] = {
E 157
I 157
char const char_type[] = {
E 157
D 112
	0001,0201,0201,0001,0201,0001,0001,0201,
	0202,0004,0003,0201,0005,0206,0201,0001,
	0201,0001,0001,0201,0001,0201,0201,0001,
	0001,0201,0201,0001,0201,0001,0001,0201,
	0200,0000,0000,0200,0000,0200,0200,0000,
	0000,0200,0200,0000,0200,0000,0000,0200,
	0000,0200,0200,0000,0200,0000,0000,0200,
	0200,0000,0000,0200,0000,0200,0200,0000,
	0200,0000,0000,0200,0000,0200,0200,0000,
	0000,0200,0200,0000,0200,0000,0000,0200,
	0000,0200,0200,0000,0200,0000,0000,0200,
	0200,0000,0000,0200,0000,0200,0200,0000,
	0000,0200,0200,0000,0200,0000,0000,0200,
	0200,0000,0000,0200,0000,0200,0200,0000,
	0200,0000,0000,0200,0000,0200,0200,0000,
	0000,0200,0200,0000,0200,0000,0000,0201,

E 112
I 112
D 140
	0001,0201,0201,0001,0201,0001,0001,0201,	/* nul - bel */
	0202,0004,0003,0201,0005,0206,0201,0001,	/* bs - si */
	0201,0001,0001,0201,0001,0201,0201,0001,	/* dle - etb */
	0001,0201,0201,0001,0201,0001,0001,0201,	/* can - us */
	0200,0000,0000,0200,0000,0200,0200,0000,	/* sp - ' */
	0000,0200,0200,0000,0200,0000,0000,0200,	/* ( - / */
	0100,0300,0300,0100,0300,0100,0100,0300,	/* 0 - 7 */
	0300,0100,0000,0200,0000,0200,0200,0000,	/* 8 - ? */
	0200,0100,0100,0300,0100,0300,0300,0100,	/* @ - G */
	0100,0300,0300,0100,0300,0100,0100,0300,	/* H - O */
	0100,0300,0300,0100,0300,0100,0100,0300,	/* P - W */
	0300,0100,0100,0200,0000,0200,0200,0300,	/* X - _ */
	0000,0300,0300,0100,0300,0100,0100,0300,	/* ` - g */
	0300,0100,0100,0300,0100,0300,0300,0100,	/* h - o */
	0300,0100,0100,0300,0100,0300,0300,0100,	/* p - w */
	0100,0300,0300,0000,0200,0000,0000,0201,	/* x - del */
E 140
I 140
	E|CC, O|CC, O|CC, E|CC, O|CC, E|CC, E|CC, O|CC,	/* nul - bel */
	O|BS, E|TB, E|NL, O|CC, E|VT, O|CR, O|CC, E|CC, /* bs - si */
	O|CC, E|CC, E|CC, O|CC, E|CC, O|CC, O|CC, E|CC, /* dle - etb */
	E|CC, O|CC, O|CC, E|CC, O|CC, E|CC, E|CC, O|CC, /* can - us */
	O|NO, E|NO, E|NO, O|NO, E|NO, O|NO, O|NO, E|NO, /* sp - ' */
	E|NO, O|NO, O|NO, E|NO, O|NO, E|NO, E|NO, O|NO, /* ( - / */
	E|NA, O|NA, O|NA, E|NA, O|NA, E|NA, E|NA, O|NA, /* 0 - 7 */
	O|NA, E|NA, E|NO, O|NO, E|NO, O|NO, O|NO, E|NO, /* 8 - ? */
	O|NO, E|NA, E|NA, O|NA, E|NA, O|NA, O|NA, E|NA, /* @ - G */
	E|NA, O|NA, O|NA, E|NA, O|NA, E|NA, E|NA, O|NA, /* H - O */
	E|NA, O|NA, O|NA, E|NA, O|NA, E|NA, E|NA, O|NA, /* P - W */
	O|NA, E|NA, E|NA, O|NO, E|NO, O|NO, O|NO, O|NA, /* X - _ */
	E|NO, O|NA, O|NA, E|NA, O|NA, E|NA, E|NA, O|NA, /* ` - g */
	O|NA, E|NA, E|NA, O|NA, E|NA, O|NA, O|NA, E|NA, /* h - o */
	O|NA, E|NA, E|NA, O|NA, E|NA, O|NA, O|NA, E|NA, /* p - w */
	E|NA, O|NA, O|NA, E|NO, O|NO, E|NO, E|NO, O|CC, /* x - del */
E 140
E 112
	/*
D 112
	 * 7 bit ascii ends with the last character above,
	 * but we contine through all 256 codes for the sake
	 * of the tty output routines which use special vax
	 * instructions which need a 256 character trt table.
E 112
I 112
D 140
	 * meta chars
E 140
I 140
D 157
	 * "meta" chars; should be settable per charset.
	 * For now, treat all as normal characters.
E 157
I 157
	 * Meta chars; should be settable per character set;
	 * for now, treat them all as normal characters.
E 157
E 140
E 112
	 */
D 112

	0007,0007,0007,0007,0007,0007,0007,0007,
	0007,0007,0007,0007,0007,0007,0007,0007,
	0007,0007,0007,0007,0007,0007,0007,0007,
	0007,0007,0007,0007,0007,0007,0007,0007,
	0007,0007,0007,0007,0007,0007,0007,0007,
	0007,0007,0007,0007,0007,0007,0007,0007,
	0007,0007,0007,0007,0007,0007,0007,0007,
	0007,0007,0007,0007,0007,0007,0007,0007,
	0007,0007,0007,0007,0007,0007,0007,0007,
	0007,0007,0007,0007,0007,0007,0007,0007,
	0007,0007,0007,0007,0007,0007,0007,0007,
	0007,0007,0007,0007,0007,0007,0007,0007,
	0007,0007,0007,0007,0007,0007,0007,0007,
	0007,0007,0007,0007,0007,0007,0007,0007,
	0007,0007,0007,0007,0007,0007,0007,0007,
	0007,0007,0007,0007,0007,0007,0007,0007
E 112
I 112
D 140
	0001,0201,0201,0001,0201,0001,0001,0201,	/* nul - bel */
	0202,0004,0003,0201,0005,0206,0201,0001,	/* bs - si */
	0201,0001,0001,0201,0001,0201,0201,0001,	/* dle - etb */
	0001,0201,0201,0001,0201,0001,0001,0201,	/* can - us */
	0200,0000,0000,0200,0000,0200,0200,0000,	/* sp - ' */
	0000,0200,0200,0000,0200,0000,0000,0200,	/* ( - / */
	0100,0300,0300,0100,0300,0100,0100,0300,	/* 0 - 7 */
	0300,0100,0000,0200,0000,0200,0200,0000,	/* 8 - ? */
	0200,0100,0100,0300,0100,0300,0300,0100,	/* @ - G */
	0100,0300,0300,0100,0300,0100,0100,0300,	/* H - O */
	0100,0300,0300,0100,0300,0100,0100,0300,	/* P - W */
	0300,0100,0100,0200,0000,0200,0200,0300,	/* X - _ */
	0000,0300,0300,0100,0300,0100,0100,0300,	/* ` - g */
	0300,0100,0100,0300,0100,0300,0300,0100,	/* h - o */
	0300,0100,0100,0300,0100,0300,0300,0100,	/* p - w */
	0100,0300,0300,0000,0200,0000,0000,0201,	/* x - del */
E 140
I 140
	NA,   NA,   NA,   NA,   NA,   NA,   NA,   NA,
	NA,   NA,   NA,   NA,   NA,   NA,   NA,   NA,
	NA,   NA,   NA,   NA,   NA,   NA,   NA,   NA,
	NA,   NA,   NA,   NA,   NA,   NA,   NA,   NA,
	NA,   NA,   NA,   NA,   NA,   NA,   NA,   NA,
	NA,   NA,   NA,   NA,   NA,   NA,   NA,   NA,
	NA,   NA,   NA,   NA,   NA,   NA,   NA,   NA,
	NA,   NA,   NA,   NA,   NA,   NA,   NA,   NA,
	NA,   NA,   NA,   NA,   NA,   NA,   NA,   NA,
	NA,   NA,   NA,   NA,   NA,   NA,   NA,   NA,
	NA,   NA,   NA,   NA,   NA,   NA,   NA,   NA,
	NA,   NA,   NA,   NA,   NA,   NA,   NA,   NA,
	NA,   NA,   NA,   NA,   NA,   NA,   NA,   NA,
	NA,   NA,   NA,   NA,   NA,   NA,   NA,   NA,
	NA,   NA,   NA,   NA,   NA,   NA,   NA,   NA,
	NA,   NA,   NA,   NA,   NA,   NA,   NA,   NA,
E 140
E 112
};
I 140
D 157
#undef	NO
#undef	NA
#undef	CC
E 157
#undef	BS
I 157
#undef	CC
#undef	CR
#undef	NA
E 157
#undef	NL
I 157
#undef	NO
E 157
#undef	TB
#undef	VT
D 157
#undef	CR
E 157
E 140

I 112
D 157
extern struct tty *constty;		/* temporary virtual console */
E 157
I 157
/* Macros to clear/set/test flags. */
#define	SET(t, f)	(t) |= (f)
#define	CLR(t, f)	(t) &= ~(f)
#define	ISSET(t, f)	((t) & (f))
E 157
D 137
extern char partab[], maptab[];
E 137

E 112
E 43
I 3
/*
D 24
 * When running dz's using only SAE (silo alarm) on input
 * it is necessary to call dzrint() at clock interrupt time.
 * This is unsafe unless spl5()s in tty code are changed to
 * spl6()s to block clock interrupts.  Note that the dh driver
 * currently in use works the same way as the dz, even though
 * we could try to more intelligently manage its silo.
 * Thus don't take this out if you have no dz's unless you
 * change clock.c and dhtimer().
 */
#define	spl5	spl6
E 3

/*
E 24
D 112
 * Input mapping table-- if an entry is non-zero, when the
 * corresponding character is typed preceded by "\" the escape
 * sequence is replaced by the table value.  Mostly used for
 * upper-case only terminals.
E 112
I 112
D 157
 * Is 'c' a line delimiter ("break" character)?
E 157
I 157
 * Initial open of tty, or (re)entry to standard tty line discipline.
E 157
E 112
 */
D 56

E 56
D 112
char	maptab[] ={
	000,000,000,000,000,000,000,000,
	000,000,000,000,000,000,000,000,
	000,000,000,000,000,000,000,000,
	000,000,000,000,000,000,000,000,
	000,'|',000,000,000,000,000,'`',
	'{','}',000,000,000,000,000,000,
	000,000,000,000,000,000,000,000,
	000,000,000,000,000,000,000,000,
	000,000,000,000,000,000,000,000,
	000,000,000,000,000,000,000,000,
	000,000,000,000,000,000,000,000,
	000,000,000,000,000,000,'~',000,
	000,'A','B','C','D','E','F','G',
	'H','I','J','K','L','M','N','O',
	'P','Q','R','S','T','U','V','W',
	'X','Y','Z',000,000,000,000,000,
};
E 112
I 112
D 120
#define ttbreakc(c) (c == '\n' || CCEQ(cc[VEOF], c) || \
		CCEQ(cc[VEOL], c) || CCEQ(cc[VEOL2], c))
E 120
I 120
D 157
#define ttbreakc(c) ((c) == '\n' || ((c) == cc[VEOF] || \
	(c) == cc[VEOL] || (c) == cc[VEOL2]) && (c) != _POSIX_VDISABLE)
E 120
E 112

I 19
D 112
short	tthiwat[16] =
D 53
   { 100,100,100,100,100,100,100,200,200,400,400,400,650,650,650,650 };
E 53
I 53
   { 100,100,100,100,100,100,100,200,200,400,400,400,650,650,1300,2000 };
E 53
short	ttlowat[16] =
   {  30, 30, 30, 30, 30, 30, 30, 50, 50,120,120,120,125,125,125,125 };

E 19
D 17

/*
 * shorthand
 */
#define	q1	tp->t_rawq
#define	q2	tp->t_canq
#define	q3	tp->t_outq
#define	q4	tp->t_un.t_ctlq

E 17
D 56
#define	OBUFSIZ	100
E 56
I 56
D 110
struct	ttychars ttydefaults = {
	CERASE,	CKILL,	CINTR,	CQUIT,	CSTART,	CSTOP,	CEOF,
	CBRK,	CSUSP,	CDSUSP, CRPRNT, CFLUSH, CWERASE,CLNEXT
};
E 56

E 110
I 102
extern struct tty *constty;		/* temporary virtual console */
I 110
extern char partab[], maptab[];
E 110

E 112
I 110
/*
 * Debugging aids
 */
#define dprintf 	if (tp->t_trace & TTRACE_IO)printf

/*
 * Is 'c' a line delimiter ("break" character)?
 */
#define ttbreakc(c) (c == '\n' || CCEQ(cc[VEOF], c) || \
		CCEQ(cc[VEOL], c) || CCEQ(cc[VEOL2], c))

E 110
E 102
D 56
/*
D 17
 * routine called on first teletype open.
 * establishes a process group for distribution
 * of quits and interrupts from the tty.
 */
ttyopen(dev, tp)
dev_t dev;
register struct tty *tp;
{
	register struct proc *pp;

	pp = u.u_procp;
	tp->t_dev = dev;
	if(pp->p_pgrp == 0) {
		u.u_ttyp = tp;
		u.u_ttyd = dev;
D 4
		if (tp->t_pgrp==0)
			tp->t_pgrp = pp->p_pid;
E 4
I 4
D 6
		tp->t_pgrp = pp->p_pid;
E 6
I 6
		if (tp->t_pgrp == 0)
			tp->t_pgrp = pp->p_pid;
E 6
E 4
		pp->p_pgrp = tp->t_pgrp;
	}
	tp->t_state &= ~WOPEN;
	tp->t_state |= ISOPEN;
I 4
D 10
	tp->t_line = 0;		/* conservative */
E 10
I 10
D 11
	if (tp->t_line != OKILDISC)
		tp->t_line = 0;		/* conservative */
E 11
I 11
	tp->t_line = 0;		/* conservative */
E 11
E 10
E 4
}

D 4

E 4
/*
E 17
 * set default control characters.
 */
E 56
ttychars(tp)
D 45
register struct tty *tp;
E 45
I 45
D 56
	register struct tty *tp;
E 56
I 56
	struct tty *tp;
E 56
E 45
{
I 137

E 137
I 4
D 110
D 112

E 4
D 56
	tun.t_intrc = CINTR;
	tun.t_quitc = CQUIT;
	tun.t_startc = CSTART;
	tun.t_stopc = CSTOP;
	tun.t_eofc = CEOT;
	tun.t_brkc = CBRK;
	tp->t_erase = CERASE;
	tp->t_kill = CKILL;
I 4
/* begin local */
D 6
	tlun.t_suspc = 0377;
	tlun.t_dstopc = 0377;
E 6
I 6
	tlun.t_suspc = CTRL(z);
	tlun.t_dsuspc = CTRL(y);
E 6
	tlun.t_rprntc = CTRL(r);
	tlun.t_flushc = CTRL(o);
	tlun.t_werasc = CTRL(w);
	tlun.t_lnextc = CTRL(v);
D 19
	tlun.t_lintr = CTRL(c);
	tlun.t_lerase = CTRL(h);
	tlun.t_lkill = CTRL(u);
E 19
	tp->t_local = 0;
	tp->t_lstate = 0;
/* end local */
E 56
I 56
	tp->t_chars = ttydefaults;
E 112
I 112
	bcopy(ttydefchars, tp->t_cc, sizeof(ttydefchars));
E 112
E 110
I 110
	bcopy(ttydefchars, tp->t_cc, sizeof(ttydefchars));
E 110
E 56
E 4
}

/*
I 110
 *
E 110
D 17
 * clean tp on last close
E 17
I 17
D 140
 * Wait for output to drain, then flush input waiting.
E 140
I 140
 * Flush tty after output has drained.
E 140
E 17
 */
D 17
ttyclose(tp)
E 17
I 17
D 63
wflushtty(tp)
E 63
I 63
ttywflush(tp)
E 63
E 17
D 35
register struct tty *tp;
E 35
I 35
D 115
	register struct tty *tp;
E 115
I 115
	struct tty *tp;
E 115
E 35
{
I 120
	int error;
E 120
I 60
D 63
	int s;
E 63
E 60

D 17
	tp->t_pgrp = 0;
	wflushtty(tp);
	tp->t_state = 0;
I 4
D 10
	tp->t_line = 0;
E 10
I 10
D 11
	if (tp->t_line != OKILDISC)
		tp->t_line = 0;
E 11
I 11
	tp->t_line = 0;
E 17
I 17
D 60
	(void) spl5();
E 60
I 60
D 63
	s = spl5();
E 63
I 63
D 120
	ttywait(tp);
	ttyflush(tp, FREAD);
E 120
I 120
	if ((error = ttywait(tp)) == 0)
		ttyflush(tp, FREAD);
	return (error);
E 120
}

I 112
/*
 * Wait for output to drain.
 */
E 112
I 110
/*
 * Wait for output to drain.
 */
E 110
ttywait(tp)
E 157
I 157
int
ttyopen(device, tp)
	dev_t device;
E 157
	register struct tty *tp;
{
D 84
	register int s = spl5();
E 84
I 84
D 115
	register int s = spltty();
E 115
I 115
D 120
	int s = spltty();
E 120
I 120
D 157
	int error = 0, s = spltty();
E 120
E 115
E 84

E 63
E 60
D 35
	while (tp->t_outq.c_cc && tp->t_state&CARR_ON) {
E 35
I 35
D 40
	while (tp->t_outq.c_cc && tp->t_state&TS_CARR_ON) {
E 40
I 40
D 68
	while (tp->t_outq.c_cc && tp->t_state&TS_CARR_ON
	    && tp->t_oproc) {		/* kludge for pty */
E 68
I 68
	while ((tp->t_outq.c_cc || tp->t_state&TS_BUSY) &&
D 94
	    tp->t_state&TS_CARR_ON && tp->t_oproc) {	/* kludge for pty */
E 94
I 94
D 107
	    tp->t_state&TS_CARR_ON) {
E 107
I 107
D 115
	    tp->t_state&TS_CARR_ON && tp->t_oproc) {
E 115
I 115
	    (tp->t_state&TS_CARR_ON || tp->t_cflag&CLOCAL) && 
	    tp->t_oproc) {
E 115
E 107
E 94
E 68
E 40
E 35
		(*tp->t_oproc)(tp);
D 35
		tp->t_state |= ASLEEP;
E 35
I 35
		tp->t_state |= TS_ASLEEP;
E 35
D 120
		sleep((caddr_t)&tp->t_outq, TTOPRI);
E 120
I 120
D 128
		if (error = tsleep((caddr_t)&tp->t_outq, TTOPRI | PCATCH,
		    ttyout, 0))
E 128
I 128
D 132
		if ((error = tsleep((caddr_t)&tp->t_outq, TTOPRI | PCATCH,
				    ttyout, 0)) ||
		    (error = ttclosed(tp)))
E 132
I 132
		if (error = ttysleep(tp, (caddr_t)&tp->t_outq, 
		    TTOPRI | PCATCH, ttyout, 0))
E 132
E 128
			break;
E 120
	}
D 37
	flushtty(tp, FREAD|FWRITE);
E 37
I 37
D 63
	flushtty(tp, FREAD);
E 63
E 37
D 60
	(void) spl0();
E 60
I 60
	splx(s);
I 120
	return (error);
E 120
E 60
E 17
E 11
E 10
E 4
}

I 140
D 147
#define	flushq(qq) { \
	register struct clist *q = qq; \
	if (q->c_cc) \
		ndflush(q, q->c_cc); \
E 147
I 147
#define	flushq(q) { \
	if ((q)->c_cc) \
		ndflush(q, (q)->c_cc); \
E 147
}

E 140
/*
D 17
 * stty/gtty writearound
E 17
I 17
D 56
 * flush all TTY queues
E 56
I 56
D 140
 * Flush all TTY queues
E 140
I 140
 * Flush TTY read and/or write queues,
 * notifying anyone waiting.
E 140
E 56
E 17
 */
D 17
stty()
E 17
I 17
D 63
flushtty(tp, rw)
E 63
I 63
ttyflush(tp, rw)
E 63
D 45
register struct tty *tp;
E 45
I 45
	register struct tty *tp;
I 147
	int rw;
E 147
E 45
E 17
{
D 17
	u.u_arg[2] = u.u_arg[1];
	u.u_arg[1] = TIOCSETP;
	ioctl();
E 17
I 17
D 147
	register s;
E 147
I 147
	register int s;
E 147

D 33
	if (tp->t_line == NETLDISC)
		return;
E 33
D 84
	s = spl6();
E 84
I 84
	s = spltty();
E 84
	if (rw & FREAD) {
D 140
		while (getc(&tp->t_canq) >= 0)
			;
E 140
I 140
		flushq(&tp->t_canq);
		flushq(&tp->t_rawq);
		tp->t_rocount = 0;
		tp->t_rocol = 0;
		tp->t_state &= ~TS_LOCAL;
E 140
D 115
		wakeup((caddr_t)&tp->t_rawq);
E 115
I 115
		ttwakeup(tp);
E 115
	}
	if (rw & FWRITE) {
D 115
		wakeup((caddr_t)&tp->t_outq);
E 115
I 115
D 140
		wakeup((caddr_t)&tp->t_outq); /* XXX? what about selwakeup? */
E 140
E 115
D 35
		tp->t_state &= ~TTSTOP;
E 35
I 35
		tp->t_state &= ~TS_TTSTOP;
I 147
#ifdef sun4c						/* XXX */
		(*tp->t_stop)(tp, rw);
#else
E 147
E 35
D 37
		(*cdevsw[major(tp->t_dev)].d_stop)(tp);
E 37
I 37
		(*cdevsw[major(tp->t_dev)].d_stop)(tp, rw);
I 147
#endif
E 147
E 37
D 140
		while (getc(&tp->t_outq) >= 0)
			;
E 140
I 140
		flushq(&tp->t_outq);
		wakeup((caddr_t)&tp->t_outq);
D 148
		if (tp->t_wsel) {
			selwakeup(tp->t_wsel, tp->t_state & TS_WCOLL);
			tp->t_wsel = 0;
			tp->t_state &= ~TS_WCOLL;
		}
E 148
I 148
		selwakeup(&tp->t_wsel);
E 148
E 140
	}
D 140
	if (rw & FREAD) {
		while (getc(&tp->t_rawq) >= 0)
			;
D 81
		tp->t_delct = 0;
E 81
D 56
		tp->t_rocount = 0;		/* local */
E 56
I 56
		tp->t_rocount = 0;
E 56
		tp->t_rocol = 0;
D 56
		tp->t_lstate = 0;
E 56
I 56
		tp->t_state &= ~TS_LOCAL;
E 56
	}
E 140
	splx(s);
E 17
}

D 17
gtty()
E 17
I 17
/*
 * Send stop character on input overflow.
 */
ttyblock(tp)
D 45
register struct tty *tp;
E 45
I 45
	register struct tty *tp;
E 45
E 17
{
D 17
	u.u_arg[2] = u.u_arg[1];
	u.u_arg[1] = TIOCGETP;
	ioctl();
E 17
I 17
	register x;
I 56

E 56
	x = tp->t_rawq.c_cc + tp->t_canq.c_cc;
	if (tp->t_rawq.c_cc > TTYHOG) {
D 63
		flushtty(tp, FREAD|FWRITE);
E 63
I 63
		ttyflush(tp, FREAD|FWRITE);
E 63
D 35
		tp->t_state &= ~TBLOCK;
E 35
I 35
		tp->t_state &= ~TS_TBLOCK;
E 35
	}
D 56
	if (x >= TTYHOG/2) {
		if (putc(tun.t_stopc, &tp->t_outq)==0) {
D 35
			tp->t_state |= TBLOCK;
E 35
I 35
			tp->t_state |= TS_TBLOCK;
E 35
			tp->t_char++;
			ttstart(tp);
		}
E 56
I 56
D 77
	if (x >= TTYHOG/2 && putc(tp->t_stopc, &tp->t_outq) == 0) {
		tp->t_state |= TS_TBLOCK;
D 60
		tp->t_char++;
E 60
		ttstart(tp);
E 77
I 77
	/*
	 * Block further input iff:
	 * Current input > threshold AND input is available to user program
	 */
D 81
	if (x >= TTYHOG/2 && (tp->t_delct>0 || (tp->t_flags&(RAW|CBREAK)))) {
E 81
I 81
D 126
	if (x >= TTYHOG/2 && 
E 126
I 126
	if (x >= TTYHOG/2 && (tp->t_state & TS_TBLOCK) == 0 &&
E 126
D 110
D 112
	    ((tp->t_flags & (RAW|CBREAK)) || (tp->t_canq.c_cc > 0))) {
E 81
		if (putc(tp->t_stopc, &tp->t_outq)==0) {
E 112
I 112
D 120
	    (!(tp->t_lflag&ICANON)) || (tp->t_canq.c_cc > 0) &&
E 120
I 120
	    ((tp->t_lflag&ICANON) == 0) || (tp->t_canq.c_cc > 0) &&
E 120
	    tp->t_cc[VSTOP] != _POSIX_VDISABLE) {
D 126
		if (putc(tp->t_cc[VSTOP], &tp->t_outq)==0) {
E 126
I 126
		if (putc(tp->t_cc[VSTOP], &tp->t_outq) == 0) {
E 126
E 112
E 110
I 110
	    (!(tp->t_lflag&ICANON)) || (tp->t_canq.c_cc > 0) &&
	    tp->t_cc[VSTOP] != POSIX_V_DISABLE) {
		if (putc(tp->t_cc[VSTOP], &tp->t_outq)==0) {
E 110
			tp->t_state |= TS_TBLOCK;
			ttstart(tp);
		}
E 77
E 56
	}
E 17
}

D 140
/*
I 2
D 17
 * Do nothing specific version of line
 * discipline specific ioctl command.
E 17
I 17
D 137
 * Restart typewriter output following a delay
 * timeout.
 * The name of the routine is passed to the timeout
 * subroutine and it is called during a clock interrupt.
E 137
I 137
 * Start output on the typewriter. It is used from the top half
 * after some characters have been put on the output queue,
 * from the interrupt routine to transmit the next
 * character.
E 137
E 17
 */
E 140
I 5
D 17
/*ARGSUSED*/
E 5
nullioctl(tp, cmd, addr)
E 17
I 17
D 137
ttrstrt(tp)
E 137
I 137
ttstart(tp)
E 137
E 17
D 45
register struct tty *tp;
E 45
I 45
D 115
	register struct tty *tp;
E 115
I 115
	struct tty *tp;
E 115
E 45
D 17
caddr_t addr;
E 17
{

I 137
	if (tp->t_oproc)		/* kludge for pty */
		(*tp->t_oproc)(tp);
}

D 150
ttrstrt(tp)				/* XXX */
	struct tty *tp;
E 150
I 150
void
ttrstrt(tp0)
	void *tp0;
E 150
{
I 150
	struct tty *tp;
E 157
E 150
I 147
	int s;
E 147

I 150
D 157
	tp = (struct tty *)tp0;
E 150
E 137
I 120
#ifdef DIAGNOSTIC
E 120
I 26
D 56
	if (tp == 0) {
		printf("ttrstrt: arg was 0!\n");
		return;
	}
E 56
I 56
	if (tp == 0)
		panic("ttrstrt");
I 120
#endif
E 157
I 147
	s = spltty();
E 147
E 120
E 56
E 26
D 17
	return (cmd);
E 17
I 17
D 35
	tp->t_state &= ~TIMEOUT;
E 35
I 35
D 157
	tp->t_state &= ~TS_TIMEOUT;
E 35
	ttstart(tp);
I 147
	splx(s);
E 147
E 17
}

D 137
/*
E 2
D 17
 * ioctl system call
 * Check legality, execute common code, and switch out to individual
 * device routine.
E 17
I 17
 * Start output on the typewriter. It is used from the top half
 * after some characters have been put on the output queue,
 * from the interrupt routine to transmit the next
 * character, and after a timeout has finished.
E 17
 */
D 17
ioctl()
E 17
I 17
ttstart(tp)
D 45
register struct tty *tp;
E 45
I 45
D 115
	register struct tty *tp;
E 115
I 115
	struct tty *tp;
E 115
E 45
E 17
{
E 137
D 17
	register struct file *fp;
	register struct inode *ip;
	register struct a {
		int	fdes;
		int	cmd;
		caddr_t	cmarg;
	} *uap;
	register dev_t dev;
	register fmt;
E 17
I 17
D 106
	register s;
E 106
E 17

D 17
	uap = (struct a *)u.u_ap;
	if ((fp = getf(uap->fdes)) == NULL)
		return;
I 16
	if ((fp->f_flag & (FREAD|FWRITE)) == 0) {
		u.u_error = EBADF;
		return;
	}
E 16
	if (uap->cmd==FIOCLEX) {
		u.u_pofile[uap->fdes] |= EXCLOSE;
		return;
	}
	if (uap->cmd==FIONCLEX) {
		u.u_pofile[uap->fdes] &= ~EXCLOSE;
		return;
	}
	ip = fp->f_inode;
	fmt = ip->i_mode & IFMT;
	if (fmt != IFCHR && fmt != IFMPC) {
D 4
		u.u_error = ENOTTY;
E 4
I 4
/* begin local */
		if (uap->cmd==FIONREAD && (fmt == IFREG || fmt == IFDIR)) {
			off_t nread = ip->i_size - fp->f_un.f_offset;

			if (copyout((caddr_t)&nread, uap->cmarg, sizeof(off_t)))
				u.u_error = EFAULT;
		} else
/* end local */
			u.u_error = ENOTTY;
E 4
		return;
	}
	dev = ip->i_un.i_rdev;
	u.u_r.r_val1 = 0;
	(*cdevsw[major(dev)].d_ioctl)(dev, uap->cmd, uap->cmarg, fp->f_flag);
E 17
I 17
D 84
	s = spl5();
E 84
I 84
D 106
	s = spltty();
E 84
D 35
	if((tp->t_state&(TIMEOUT|TTSTOP|BUSY)) == 0)
E 35
I 35
D 40
	if((tp->t_state&(TS_TIMEOUT|TS_TTSTOP|TS_BUSY)) == 0)
E 40
I 40
D 45
	if((tp->t_state&(TS_TIMEOUT|TS_TTSTOP|TS_BUSY)) == 0 &&
E 45
I 45
D 56
	if ((tp->t_state&(TS_TIMEOUT|TS_TTSTOP|TS_BUSY)) == 0 &&
E 56
I 56
	if ((tp->t_state & (TS_TIMEOUT|TS_TTSTOP|TS_BUSY)) == 0 &&
E 56
E 45
	    tp->t_oproc)		/* kludge for pty */
E 106
I 106
D 137
	if (tp->t_oproc)		/* kludge for pty */
E 106
E 40
E 35
		(*tp->t_oproc)(tp);
D 106
	splx(s);
E 106
E 17
}

E 137
/*
D 17
 * Common code for several tty ioctl commands
E 17
I 17
D 140
 * Common code for tty ioctls.
E 140
I 140
 * Common code for ioctls on tty devices.
 * Called after line-discipline-specific ioctl
 * has been called to do discipline-specific functions
 * and/or reject any of these ioctl commands.
E 140
E 17
 */
I 22
/*ARGSUSED*/
E 22
D 17
ttioccomm(com, tp, addr, dev)
E 17
I 17
D 23
ttioctl(com, tp, addr, dev, flag)
E 23
I 23
D 45
ttioctl(tp, com, addr, flag)
E 23
E 17
register struct tty *tp;
caddr_t addr;
E 45
I 45
ttioctl(tp, com, data, flag)
	register struct tty *tp;
I 147
	int com;
E 147
	caddr_t data;
I 147
	int flag;
E 147
E 45
{
I 137
	register struct proc *p = curproc;		/* XXX */
E 137
I 23
D 50
	int dev;
E 50
I 50
D 110
D 112
	int dev = tp->t_dev;
E 112
E 110
E 50
E 23
D 45
	unsigned t;
D 4
	struct ttiocb iocb;
E 4
I 4
	struct sgttyb iocb;
I 5
	struct clist tq;
E 45
E 5
E 4
	extern int nldisp;
I 112
D 117
	int softset = 0;
E 117
E 112
I 110
	int soft;
E 110
I 51
D 114
	int s;
E 114
I 114
	int s, error;
E 114
I 63
D 110
D 112
	register int newflags;
E 112
E 110
E 63
E 51
I 15
D 45
	register c;
E 15
I 13
	int temp;
E 45
E 13
I 2
D 4
	register s;
E 4
E 2

I 102
D 117

E 117
E 102
I 17
	/*
I 18
D 50
	 * This is especially so that isatty() will
	 * fail when carrier is gone.
	 */
D 35
	if ((tp->t_state&CARR_ON) == 0) {
E 35
I 35
	if ((tp->t_state&TS_CARR_ON) == 0) {
E 35
		u.u_error = EBADF;
		return (1);
	}

I 23
	dev = tp->t_dev;
E 23
	/*
E 50
E 18
	 * If the ioctl involves modification,
D 84
	 * insist on being able to write the device,
	 * and hang if in the background.
E 84
I 84
	 * hang if in the background.
E 84
	 */
E 17
D 45
	switch(com) {
E 45
I 45
	switch (com) {
E 45

I 17
D 18
	case TIOCHPCL:
E 18
I 18
D 110
D 112
	case TIOCSETD:
	case TIOCSETP:
	case TIOCSETN:
E 112
I 112
	case TIOCSETD: 
E 112
E 110
I 110
	case TIOCSETD: 
E 110
E 18
	case TIOCFLUSH:
D 110
D 112
	case TIOCSETC:
	case TIOCSLTC:
E 110
	case TIOCSPGRP:
D 110
	case TIOCLBIS:
	case TIOCLBIC:
	case TIOCLSET:
E 112
I 112
	/*case TIOCSPGRP:*/
E 112
E 110
I 57
D 64
	case TIOCBIS:
	case TIOCBIC:
	case TIOCSET:
E 64
E 57
I 54
	case TIOCSTI:
I 85
	case TIOCSWINSZ:
E 85
I 74
D 93
#define bit(a) (1<<(a-1))
E 93
E 74
E 54
D 45
	case TIOCSTI:
E 45
I 18
D 51
/* this is reasonable, but impractical... 
E 18
		if ((flag & FWRITE) == 0) {
			u.u_error = EBADF;
			return (1);
		}
I 18
 */
E 51
E 18
D 110
D 112
		while (tp->t_line == NTTYDISC &&
E 110
I 110
	case TIOCSETA:
	case TIOCSETAW:
	case TIOCSETAF:
	case TIOCSETAS:
	case TIOCSETAWS:
	case TIOCSETAFS:
		while (tp->t_line == POSXDISC &&
E 110
		   u.u_procp->p_pgrp != tp->t_pgrp && tp == u.u_ttyp &&
E 112
I 112
	case TIOCSETA:
	case TIOCSETAW:
	case TIOCSETAF:
I 117
D 133
/**** these get removed ****
E 117
	case TIOCSETAS:
	case TIOCSETAWS:
	case TIOCSETAFS:
I 117
/***************************/
E 133
I 119
D 147
#ifdef COMPAT_43
E 147
I 147
#if defined(COMPAT_43) || defined(COMPAT_SUNOS)
E 147
	case TIOCSETP:
	case TIOCSETN:
	case TIOCSETC:
	case TIOCSLTC:
	case TIOCLBIS:
	case TIOCLBIC:
	case TIOCLSET:
	case OTIOCSETD:
I 130
D 132
	case OTIOCCONS:
E 132
E 130
#endif
E 119
E 117
D 118
		while (u.u_procp->p_pgid != tp->t_pgid &&
		   tp == u.u_ttyp &&
E 118
I 118
D 137
		while (isbackground(u.u_procp, tp) && 
E 118
		   u.u_procp->p_pgrp->pg_jobc &&
E 112
		   (u.u_procp->p_flag&SVFORK) == 0 &&
D 74
		   u.u_signal[SIGTTOU] != SIG_IGN &&
D 41
		   u.u_signal[SIGTTOU] != SIG_HOLD &&
E 41
I 41
D 51
		   u.u_signal[SIGTTOU] != SIG_HOLD
/*
						   &&
E 41
		   (u.u_procp->p_flag&SDETACH)==0) {
I 41
*/
		   ) {
E 51
I 51
		   u.u_signal[SIGTTOU] != SIG_HOLD) {
E 74
I 74
D 93
		   !(u.u_procp->p_sigignore & bit(SIGTTOU)) &&
		   !(u.u_procp->p_sigmask & bit(SIGTTOU))) {
E 93
I 93
D 120
		   !(u.u_procp->p_sigignore & sigmask(SIGTTOU)) &&
		   !(u.u_procp->p_sigmask & sigmask(SIGTTOU))) {
E 120
I 120
		   (u.u_procp->p_sigignore & sigmask(SIGTTOU)) == 0 &&
		   (u.u_procp->p_sigmask & sigmask(SIGTTOU)) == 0) {
E 120
E 93
E 74
E 51
E 41
D 112
			gsignal(u.u_procp->p_pgrp, SIGTTOU);
E 112
I 112
D 127
			pgsignal(u.u_procp->p_pgrp, SIGTTOU);
E 127
I 127
			pgsignal(u.u_procp->p_pgrp, SIGTTOU, 1);
E 137
I 137
		while (isbackground(curproc, tp) && 
		   p->p_pgrp->pg_jobc && (p->p_flag&SPPWAIT) == 0 &&
		   (p->p_sigignore & sigmask(SIGTTOU)) == 0 &&
		   (p->p_sigmask & sigmask(SIGTTOU)) == 0) {
			pgsignal(p->p_pgrp, SIGTTOU, 1);
E 137
E 127
E 112
D 120
			sleep((caddr_t)&lbolt, TTOPRI);
E 120
I 120
D 128
			if (error = tsleep((caddr_t)&lbolt, TTOPRI | PCATCH,
			    ttybg, 0))
E 128
I 128
D 132
			if ((error = tsleep((caddr_t)&lbolt, TTOPRI | PCATCH,
					    ttybg, 0)) ||
			    (error = ttclosed(tp)))
E 132
I 132
			if (error = ttysleep(tp, (caddr_t)&lbolt, 
			    TTOPRI | PCATCH, ttybg, 0)) 
E 132
E 128
				return (error);
E 120
		}
		break;
E 157
I 157
	tp->t_dev = device;
	if (!ISSET(tp->t_state, TS_ISOPEN)) {
		SET(tp->t_state, TS_ISOPEN);
		bzero(&tp->t_winsize, sizeof(tp->t_winsize));
E 157
	}
I 74
D 93
#undef	bit
E 93
E 74
D 157

I 56
	/*
	 * Process the ioctl.
	 */
E 56
E 17
D 51
	/*
D 17
	 * get discipline number
E 17
I 17
	 * Process the ioctl.
E 17
	 */
E 51
I 17
D 45
	switch(com) {
E 45
I 45
	switch (com) {
E 45

D 51
	/*
	 * Get discipline number
	 */
E 51
I 51
	/* get discipline number */
E 51
E 17
	case TIOCGETD:
D 45
		t = tp->t_line;
		if (copyout((caddr_t)&t, addr, sizeof(t)))
			u.u_error = EFAULT;
E 45
I 45
		*(int *)data = tp->t_line;
E 45
		break;

D 51
	/*
D 17
	 * set line discipline
E 17
I 17
	 * Set line discipline
E 17
	 */
E 51
I 51
	/* set line discipline */
E 51
D 45
	case TIOCSETD:
		if (copyin(addr, (caddr_t)&t, sizeof(t))) {
			u.u_error = EFAULT;
			break;
		}
E 45
I 45
	case TIOCSETD: {
		register int t = *(int *)data;
I 112
		dev_t dev = tp->t_dev;
E 112
I 110
		dev_t dev = tp->t_dev;
E 110
I 51
D 56
		int error;
E 56
I 56
D 120
		int error = 0;
E 120
E 56
E 51

E 45
D 51
		if (t >= nldisp) {
			u.u_error = ENXIO;
			break;
		}
I 2
D 4
		s = spl5();
E 4
I 4
		(void) spl5();
E 51
I 51
D 56
		if (t >= nldisp)
			return (ENXIO);
E 56
I 56
D 62
		if (t >= nldisp) {
			u.u_error = ENXIO;
			break;
		}
E 62
I 62
D 74
		if (t >= nldisp)
E 74
I 74
D 112
		if ((unsigned) t >= nldisp)
E 112
I 112
		if ((unsigned)t >= nldisp)
E 112
E 74
			return (ENXIO);
E 62
E 56
D 84
		s = spl5();
E 84
I 84
D 97
		s = spltty();
E 84
E 51
E 4
E 2
D 94
		if (tp->t_line)
			(*linesw[tp->t_line].l_close)(tp);
		if (t)
D 45
			(*linesw[t].l_open)(dev, tp, addr);
E 45
I 45
D 51
			(*linesw[t].l_open)(dev, tp);
E 45
		if (u.u_error==0)
			tp->t_line = t;
I 2
D 4
		splx(s);
E 4
I 4
		(void) spl0();
E 51
I 51
			error = (*linesw[t].l_open)(dev, tp);
E 94
I 94
		(*linesw[tp->t_line].l_close)(tp);
		error = (*linesw[t].l_open)(dev, tp);
E 94
D 87
		splx(s);
E 87
D 62
		if (error)
E 62
I 62
		if (error) {
D 84
			s = spl5();
E 84
I 84
D 87
			s = spltty();
E 87
E 84
D 94
			if (tp->t_line)
				(void) (*linesw[tp->t_line].l_open)(dev, tp);
E 94
I 94
			(void) (*linesw[tp->t_line].l_open)(dev, tp);
E 97
I 97
		if (t != tp->t_line) {
			s = spltty();
D 142
			(*linesw[tp->t_line].l_close)(tp);
E 142
I 142
			(*linesw[tp->t_line].l_close)(tp, flag);
E 142
			error = (*linesw[t].l_open)(dev, tp);
			if (error) {
D 110
D 112
				(void) (*linesw[tp->t_line].l_open)(dev, tp);
E 112
I 112
				(void)(*linesw[tp->t_line].l_open)(dev, tp);
E 112
E 110
I 110
				(void)(*linesw[tp->t_line].l_open)(dev, tp);
E 110
				splx(s);
				return (error);
			}
			tp->t_line = t;
E 97
E 94
			splx(s);
E 62
D 97
			return (error);
E 97
I 62
		}
I 110
		if (tp->t_trace & TTRACE_STATE)
			ttytrace(com, tp);
E 110
E 62
D 97
		tp->t_line = t;
I 87
		splx(s);
E 97
E 87
E 51
E 4
E 2
		break;
I 45
	}
E 45

D 51
	/*
I 39
	 * Prevent more opens on channel
	 */
E 51
I 51
	/* prevent more opens on channel */
E 51
	case TIOCEXCL:
I 147
		s = spltty();
E 147
		tp->t_state |= TS_XCLUDE;
I 147
		splx(s);
E 147
		break;

	case TIOCNXCL:
I 147
		s = spltty();
E 147
		tp->t_state &= ~TS_XCLUDE;
I 147
		splx(s);
E 147
		break;

I 147
#ifdef TIOCHPCL
E 147
D 51
	/*
E 39
D 17
	 * prevent more opens on channel
E 17
I 17
D 33
	 * Prevent more opens on channel
E 17
	 */
	case TIOCEXCL:
		tp->t_state |= XCLUDE;
		break;

	case TIOCNXCL:
		tp->t_state &= ~XCLUDE;
		break;

	/*
E 33
	 * Set new parameters
	 */
E 51
I 51
D 57
	/* set new parameters */
E 51
	case TIOCSETP:
D 4
		wflushtty(tp);
	case TIOCSETN:
E 4
I 4
D 5
	case TIOCSETN: {
		struct clist tq;
		register c;

E 5
I 5
D 45
	case TIOCSETN:
E 5
E 4
		if (copyin(addr, (caddr_t)&iocb, sizeof(iocb))) {
			u.u_error = EFAULT;
			return(1);
		}
E 45
I 45
	case TIOCSETN: {
		register struct sgttyb *sg = (struct sgttyb *)data;
		struct clist tq;
E 57
I 57
D 63
	case TIOCSET:
	case TIOCBIS: {
		u_long newflags = *(u_long *)data;
E 63
E 57
D 64

E 45
D 2
		VOID spl5();
E 2
I 2
D 57
		(void) spl5();
E 2
D 4
		while (canon(tp)>=0) 
			;
E 4
I 4
D 33
		if (tp->t_line == 0) {
			if (com == TIOCSETP)
				wflushtty(tp);
			while (canon(tp)>=0) 
				;
I 20
#ifdef notdef
			wakeup((caddr_t)&tp->t_rawq);
#endif
E 20
		} else if (tp->t_line == NTTYDISC) {
			if (tp->t_flags&RAW || iocb.sg_flags&RAW ||
			    com == TIOCSETP)
				wflushtty(tp);
			else if ((tp->t_flags&CBREAK) != (iocb.sg_flags&CBREAK)) {
				if (iocb.sg_flags & CBREAK) {
					catq(&tp->t_rawq, &tp->t_canq);
					tq = tp->t_rawq;
					tp->t_rawq = tp->t_canq;
					tp->t_canq = tq;
				} else {
					tp->t_local |= LPENDIN;
					if (tp->t_canq.c_cc)
						panic("ioccom canq");
I 20
#ifdef notdef
E 20
					if (tp->t_chan)
						(void) sdata(tp->t_chan);
					else
I 20
#endif
E 20
						wakeup((caddr_t)&tp->t_rawq);
				}
E 33
I 33
D 45
		if (tp->t_flags&RAW || iocb.sg_flags&RAW ||
		    com == TIOCSETP)
E 45
I 45
		if (tp->t_flags&RAW || sg->sg_flags&RAW || com == TIOCSETP)
E 57
I 57
D 63
		s = spl5();
		if (tp->t_flags&RAW || newflags&RAW)
E 57
E 45
			wflushtty(tp);
D 45
		else if ((tp->t_flags&CBREAK) != (iocb.sg_flags&CBREAK)) {
			if (iocb.sg_flags & CBREAK) {
E 45
I 45
D 57
		else if ((tp->t_flags&CBREAK) != (sg->sg_flags&CBREAK)) {
D 56
			if (sg->sg_flags & CBREAK) {
E 56
I 56
			if (sg->sg_flags&CBREAK) {
E 57
I 57
		else if ((tp->t_flags&CBREAK) != (newflags&CBREAK))
			if (newflags&CBREAK) {
				struct clist tq;

E 57
E 56
E 45
				catq(&tp->t_rawq, &tp->t_canq);
				tq = tp->t_rawq;
				tp->t_rawq = tp->t_canq;
				tp->t_canq = tq;
			} else {
D 56
				tp->t_local |= LPENDIN;
E 56
I 56
				tp->t_flags |= PENDIN;
E 56
				ttwakeup(tp);
E 33
			}
D 57
		}
E 4
D 33
		if ((tp->t_state&SPEEDS)==0) {
D 4
			tp->t_ispeed = iocb.ioc_ispeed;
			tp->t_ospeed = iocb.ioc_ospeed;
E 4
I 4
			tp->t_ispeed = iocb.sg_ispeed;
			tp->t_ospeed = iocb.sg_ospeed;
E 4
		}
E 33
I 33
D 45
		tp->t_ispeed = iocb.sg_ispeed;
		tp->t_ospeed = iocb.sg_ospeed;
E 33
D 4
		tp->t_erase = iocb.ioc_erase;
		tp->t_kill = iocb.ioc_kill;
		tp->t_flags = iocb.ioc_flags;
E 4
I 4
		tp->t_erase = iocb.sg_erase;
		tp->t_kill = iocb.sg_kill;
		tp->t_flags = iocb.sg_flags;
E 45
I 45
		tp->t_ispeed = sg->sg_ispeed;
		tp->t_ospeed = sg->sg_ospeed;
		tp->t_erase = sg->sg_erase;
		tp->t_kill = sg->sg_kill;
D 56
		tp->t_flags = sg->sg_flags;
E 45
I 27
		if (tp->t_flags & RAW) {
E 56
I 56
		tp->t_flags &= ~0xffff;
		tp->t_flags |= sg->sg_flags;
E 57
I 57
		if (com == TIOCSET)
			tp->t_flags = newflags;
		else
			tp->t_flags |= newflags;
E 57
		if (tp->t_flags&RAW) {
E 56
D 35
			tp->t_state &= ~TTSTOP;
E 35
I 35
			tp->t_state &= ~TS_TTSTOP;
E 35
			ttstart(tp);
		}
E 27
E 4
D 2
		VOID spl0();
E 2
I 2
D 57
		(void) spl0();
E 57
I 57
		splx(s);
E 57
E 2
		break;
I 45
	}
E 45
I 4
D 5
		}
E 5
E 4

D 51
	/*
D 17
	 * send current parameters to user
E 17
I 17
	 * Send current parameters to user
E 17
	 */
E 51
I 51
D 57
	/* send current parameters to user */
E 51
D 45
	case TIOCGETP:
D 4
		iocb.ioc_ispeed = tp->t_ispeed;
		iocb.ioc_ospeed = tp->t_ospeed;
		iocb.ioc_erase = tp->t_erase;
		iocb.ioc_kill = tp->t_kill;
		iocb.ioc_flags = tp->t_flags;
E 4
I 4
		iocb.sg_ispeed = tp->t_ispeed;
		iocb.sg_ospeed = tp->t_ospeed;
		iocb.sg_erase = tp->t_erase;
		iocb.sg_kill = tp->t_kill;
		iocb.sg_flags = tp->t_flags;
E 4
		if (copyout((caddr_t)&iocb, addr, sizeof(iocb)))
			u.u_error = EFAULT;
E 45
I 45
	case TIOCGETP: {
		register struct sgttyb *sg = (struct sgttyb *)data;
E 57
I 57
	case TIOCBIC: {
		u_long newflags = *(long *)data;
E 57

D 57
		sg->sg_ispeed = tp->t_ispeed;
		sg->sg_ospeed = tp->t_ospeed;
		sg->sg_erase = tp->t_erase;
		sg->sg_kill = tp->t_kill;
		sg->sg_flags = tp->t_flags;
E 57
I 57
		if (tp->t_flags&RAW)
			wflushtty(tp);
		else if ((tp->t_flags&CBREAK) != (CBREAK&~newflags))
			if (newflags&CBREAK) {
				tp->t_flags |= PENDIN;
				ttwakeup(tp);
			} else {
				struct clist tq;

				catq(&tp->t_rawq, &tp->t_canq);
				tq = tp->t_rawq;
				tp->t_rawq = tp->t_canq;
				tp->t_canq = tq;
			}
		if (tp->t_flags&RAW) {
			tp->t_state &= ~TS_TTSTOP;
			ttstart(tp);
		}
		splx(s);
E 57
E 45
		break;
I 45
	}
E 45

E 63
I 57
	case TIOCGET:
D 63
		*(long *)data = tp->t_flags;
E 63
I 63
		*(int *)data = tp->t_flags;
E 63
		break;

	case TIOCCGET:
		bcopy((caddr_t)&tp->t_chars, data, sizeof (struct ttychars));
		break;

	case TIOCCSET:
		bcopy(data, (caddr_t)&tp->t_chars, sizeof (struct ttychars));
		break;

E 64
E 57
D 51
	/*
	 * Hang up line on last close
	 */
E 51
I 51
D 110
D 112
	/* hang up line on last close */
E 112
E 110
E 51
D 17

E 17
	case TIOCHPCL:
I 147
		s = spltty();
E 147
D 35
		tp->t_state |= HUPCLS;
E 35
I 35
D 110
D 112
		tp->t_state |= TS_HUPCLS;
E 112
I 112
		tp->t_cflag |= HUPCL;
I 147
		splx(s);
E 147
E 112
E 110
I 110
		tp->t_cflag |= HUPCL;
E 110
E 35
		break;
I 147
#endif
E 147

D 28
	case TIOCFLUSH:
D 14
		flushtty(tp);
E 14
I 14
		flushtty(tp, FREAD|FWRITE);
E 28
I 28
	case TIOCFLUSH: {
D 45
		int flags;
		if (addr == 0)
E 45
I 45
		register int flags = *(int *)data;

		if (flags == 0)
E 45
			flags = FREAD|FWRITE;
D 45
		else if (copyin(addr, (caddr_t)&flags, sizeof (flags))) {
			u.u_error = EFAULT;
D 31
			return;
E 31
I 31
			return(1);
E 31
		}
E 45
I 45
		else
			flags &= FREAD|FWRITE;
E 45
D 63
		flushtty(tp, flags);
E 63
I 63
		ttyflush(tp, flags);
E 63
E 28
E 14
D 23
		break;

	/*
D 17
	 * ioctl entries to line discipline
E 17
I 17
	 * Ioctl entries to line discipline
E 17
	 */
	case DIOCSETP:
	case DIOCGETP:
D 2
		(*linesw[tp->t_line].l_ioctl)(com, tp, addr);
E 2
I 2
		if ((*linesw[tp->t_line].l_ioctl)(com, tp, addr))
			u.u_error = ENOTTY;
E 23
E 2
		break;
I 29
	}
E 29

I 115
	case FIOASYNC:
I 147
		s = spltty();
E 147
		if (*(int *)data)
			tp->t_state |= TS_ASYNC;
		else
			tp->t_state &= ~TS_ASYNC;
I 147
		splx(s);
E 147
		break;

	case FIONBIO:
		break;	/* XXX remove */

E 115
I 56
D 57
	/* set and fetch special characters */
	/* THIS SHOULD USE struct ttychars */
	case TIOCSETC:
		bcopy(data, (caddr_t)&tp->t_intrc, sizeof (struct tchars));
		break;

	case TIOCGETC:
		bcopy((caddr_t)&tp->t_intrc, data, sizeof (struct tchars));
		break;

/* BEGIN DEFUNCT */
E 56
I 35
D 45
	case FIONBIO: {
		int nbio;
		if (copyin(addr, (caddr_t)&nbio, sizeof (nbio))) {
			u.u_error = EFAULT;
			return(1);
		}
		if (nbio)
E 45
I 45
	case FIONBIO:
		if (*(int *)data)
E 45
			tp->t_state |= TS_NBIO;
		else
			tp->t_state &= ~TS_NBIO;
		break;
D 45
	}
E 45

I 42
D 45
	case FIOASYNC: {
		int async;
		if (copyin(addr, (caddr_t)&async, sizeof (async))) {
			u.u_error = EFAULT;
			return(1);
		}
		if (async)
E 45
I 45
D 56
	case FIOASYNC:
		if (*(int *)data)
E 45
			tp->t_state |= TS_ASYNC;
		else
			tp->t_state &= ~TS_ASYNC;
E 56
I 56
	/* set/get local special characters */
	case TIOCSLTC:
		bcopy(data, (caddr_t)&tp->t_suspc, sizeof (struct ltchars));
E 56
		break;
D 45
	}
E 45

E 42
E 35
D 51
	/*
D 17
	 * set and fetch special characters
E 17
I 17
	 * Set and fetch special characters
E 17
	 */
E 51
I 51
D 56
	/* set and fetch special characters */
E 51
	case TIOCSETC:
D 4
		if (copyin(addr, (caddr_t)&tun, sizeof(struct tc)))
E 4
I 4
D 45
		if (copyin(addr, (caddr_t)&tun, sizeof(struct tchars)))
E 4
			u.u_error = EFAULT;
E 45
I 45
		bcopy(data, (caddr_t)&tun, sizeof (struct tchars));
E 56
I 56
	case TIOCGLTC:
		bcopy((caddr_t)&tp->t_suspc, data, sizeof (struct ltchars));
E 56
E 45
		break;

D 56
	case TIOCGETC:
D 4
		if (copyout((caddr_t)&tun, addr, sizeof(struct tc)))
E 4
I 4
D 45
		if (copyout((caddr_t)&tun, addr, sizeof(struct tchars)))
E 4
			u.u_error = EFAULT;
E 45
I 45
		bcopy((caddr_t)&tun, data, sizeof (struct tchars));
E 56
I 56
	/*
	 * Modify local mode word.
	 */
	case TIOCLBIS:
		tp->t_flags |= *(int *)data << 16;
E 56
E 45
		break;

I 4
D 51
/* local ioctls */
I 17
	/*
	 * Set/get local special characters.
	 */
E 51
I 51
D 56
	/* set/get local special characters */
E 51
E 17
	case TIOCSLTC:
D 45
		if (copyin(addr, (caddr_t)&tlun, sizeof (struct ltchars)))
			u.u_error = EFAULT;
E 45
I 45
		bcopy(data, (caddr_t)&tlun, sizeof (struct ltchars));
E 56
I 56
	case TIOCLBIC:
		tp->t_flags &= ~(*(int *)data << 16);
E 56
E 45
		break;

D 56
	case TIOCGLTC:
D 45
		if (copyout((caddr_t)&tlun, addr, sizeof (struct ltchars)))
			u.u_error = EFAULT;
E 45
I 45
		bcopy((caddr_t)&tlun, data, sizeof (struct ltchars));
E 56
I 56
	case TIOCLSET:
		tp->t_flags &= 0xffff;
		tp->t_flags |= *(int *)data << 16;
E 56
E 45
		break;

I 56
	case TIOCLGET:
		*(int *)data = tp->t_flags >> 16;
		break;
/* END DEFUNCT */

E 57
E 56
I 17
D 51
	/*
	 * Return number of characters immediately available.
	 */
E 51
I 51
	/* return number of characters immediately available */
E 51
E 17
D 45
	case FIONREAD: {
D 9
		off_t nread = tp->t_canq.c_cc;
E 9
I 9
D 33
		off_t nread;
E 9

D 9
		if (tp->t_flags & (RAW|CBREAK))
			nread += tp->t_rawq.c_cc;
E 9
I 9
		switch (tp->t_line) {

		case NETLDISC:
			nread = tp->t_rec ? tp->t_inbuf : 0;
			break;

I 16
		case 0:
			(void) spl5();
			while (canon(tp)>=0)
				;
			(void) spl0();
			/* fall into ... */

E 16
		case NTTYDISC:
I 30
			if (tp->t_local & LPENDIN)
				ntypend(tp);
E 30
			nread = tp->t_canq.c_cc;
			if (tp->t_flags & (RAW|CBREAK))
				nread += tp->t_rawq.c_cc;
			break;

D 16
		case 0:
			/* do something here ... */
			;
E 16
		}
E 33
I 33
		off_t nread = ttnread(tp);
E 33
E 9
		if (copyout((caddr_t)&nread, addr, sizeof (off_t)))
			u.u_error = EFAULT;
E 45
I 45
	case FIONREAD:
D 150
		*(off_t *)data = ttnread(tp);
E 150
I 150
		*(int *)data = ttnread(tp);
E 150
E 45
		break;
D 45
		}
E 45

I 64
	case TIOCOUTQ:
		*(int *)data = tp->t_outq.c_cc;
		break;

E 64
D 51
	/*
	 * Should allow SPGRP and GPGRP only if tty open for reading.
	 */
E 51
I 51
D 57
	/* should allow SPGRP and GPGRP only if tty open for reading */
E 51
	case TIOCSPGRP:
D 13
		tp->t_pgrp = (int)addr;
E 13
I 13
D 45
		if (copyin(addr, (caddr_t)&tp->t_pgrp, sizeof (tp->t_pgrp)))
			u.u_error = EFAULT;
E 45
I 45
		tp->t_pgrp = *(int *)data;
E 45
E 13
		break;

	case TIOCGPGRP:
D 45
		if (copyout((caddr_t)&tp->t_pgrp, addr, sizeof(tp->t_pgrp)))
			u.u_error = EFAULT;
E 45
I 45
		*(int *)data = tp->t_pgrp;
E 45
		break;

E 57
D 51
	/*
	 * Modify local mode word.
	 */
E 51
I 51
D 56
	/* Modify local mode word */
E 51
	case TIOCLBIS:
D 13
		tp->t_local |= (int)addr;
E 13
I 13
D 45
		if (copyin(addr, (caddr_t)&temp, sizeof (tp->t_local)))
			u.u_error = EFAULT;
		else
			tp->t_local |= temp;
E 45
I 45
		tp->t_local |= *(int *)data;
E 45
E 13
		break;

	case TIOCLBIC:
D 13
		tp->t_local &= ~(int)addr;
E 13
I 13
D 45
		if (copyin(addr, (caddr_t)&temp, sizeof (tp->t_local)))
			u.u_error = EFAULT;
		else
			tp->t_local &= ~temp;
E 45
I 45
		tp->t_local &= ~(*(int *)data);
E 45
E 13
		break;

	case TIOCLSET:
D 13
		tp->t_local = (int)addr;
E 13
I 13
D 45
		if (copyin(addr, (caddr_t)&temp, sizeof (tp->t_local)))
			u.u_error = EFAULT;
		else
			tp->t_local = temp;
E 45
I 45
		tp->t_local = *(int *)data;
E 45
E 13
		break;

	case TIOCLGET:
D 45
		if (copyout((caddr_t)&tp->t_local, addr, sizeof(tp->t_local)))
			u.u_error = EFAULT;
E 45
I 45
		*(int *)data = tp->t_local;
E 45
		break;

E 56
I 17
D 45
	/*
	 * Return number of characters in
	 * the output.
	 */
E 17
I 7
	case TIOCOUTQ:
		if (copyout((caddr_t)&tp->t_outq.c_cc, addr, sizeof(tp->t_outq.c_cc)))
			u.u_error = EFAULT;
		break;
E 45
I 45
D 52
	case TIOCSTOP: {
		int s = spl5();
E 45

E 52
I 52
	case TIOCSTOP:
D 84
		s = spl5();
E 84
I 84
		s = spltty();
E 84
E 52
I 17
D 45
	/*
	 * Simulate typing of a character at the terminal.
	 */
E 17
I 15
	case TIOCSTI:
		c = fubyte(addr);
		if (u.u_uid && u.u_ttyp != tp || c < 0)
			u.u_error = EFAULT;
		else
			(*linesw[tp->t_line].l_rint)(c, tp);
		break;
I 38

	case TIOCSTOP:
		c = spl5();
E 45
D 56
		if ((tp->t_state & TS_TTSTOP) == 0) {
E 56
I 56
		if ((tp->t_state&TS_TTSTOP) == 0) {
E 56
			tp->t_state |= TS_TTSTOP;
I 147
#ifdef sun4c						/* XXX */
			(*tp->t_stop)(tp, 0);
#else
E 147
			(*cdevsw[major(tp->t_dev)].d_stop)(tp, 0);
I 147
#endif
E 147
		}
D 45
		splx(c);
E 45
I 45
		splx(s);
E 45
		break;
I 45
D 52
	}
E 52
E 45

D 45
	case TIOCSTART:
		c = spl5();
E 45
I 45
D 52
	case TIOCSTART: {
		int s = spl5();

E 52
I 52
	case TIOCSTART:
D 84
		s = spl5();
E 84
I 84
		s = spltty();
E 84
E 52
E 45
D 56
		if ((tp->t_state & TS_TTSTOP) || (tp->t_local & LFLUSHO)) {
E 56
I 56
D 110
D 112
		if ((tp->t_state&TS_TTSTOP) || (tp->t_flags&FLUSHO)) {
E 112
I 112
		if ((tp->t_state&TS_TTSTOP) || (tp->t_lflag&FLUSHO)) {
E 112
E 110
I 110
		if ((tp->t_state&TS_TTSTOP) || (tp->t_lflag&FLUSHO)) {
E 110
E 56
			tp->t_state &= ~TS_TTSTOP;
D 56
			tp->t_local &= ~LFLUSHO;
E 56
I 56
D 110
D 112
			tp->t_flags &= ~FLUSHO;
E 112
I 112
			tp->t_lflag &= ~FLUSHO;
E 112
E 110
I 110
			tp->t_lflag &= ~FLUSHO;
E 110
E 56
			ttstart(tp);
		}
D 45
		splx(c);
E 45
I 45
		splx(s);
I 54
		break;

	/*
	 * Simulate typing of a character at the terminal.
	 */
	case TIOCSTI:
I 83
D 137
		if (u.u_uid && (flag & FREAD) == 0)
E 137
I 137
		if (p->p_ucred->cr_uid && (flag & FREAD) == 0)
E 137
			return (EPERM);
E 83
D 118
		if (u.u_uid && u.u_ttyp != tp)
E 118
I 118
D 137
		if (u.u_uid && !isctty(u.u_procp, tp))
E 137
I 137
		if (p->p_ucred->cr_uid && !isctty(p, tp))
E 137
E 118
			return (EACCES);
D 56
		else
			(*linesw[tp->t_line].l_rint)(*(char *)data, tp);
E 56
I 56
D 155
		(*linesw[tp->t_line].l_rint)(*(char *)data, tp);
E 155
I 155
		(*linesw[tp->t_line].l_rint)(*(u_char *)data, tp);
E 155
E 56
E 54
E 45
		break;
I 45
D 52
	}
E 52
E 45

I 63
D 64
	case TIOCSET:
	case TIOCBIS:
	case TIOCBIC:
		newflags = *(int *)data;
		if (com == TIOCBIS)
			newflags |= tp->t_flags;
		else if (com == TIOCBIC)
			newflags = tp->t_flags &~ newflags;
		goto setin;

E 64
D 110
D 112
	case TIOCSETP:
	case TIOCSETN: {
		register struct sgttyb *sg = (struct sgttyb *)data;
E 112
I 112
	case TIOCGETA: {
		struct termios *t = (struct termios *)data;
E 112
E 110
I 110
	case TIOCGETA: {
		struct termios *t = (struct termios *)data;
		bcopy(&tp->t_termio, t, sizeof(struct termios));
		if (tp->t_trace & TTRACE_STATE)
			ttytrace(com, tp);
		break;
	}
E 110

D 110
D 112
		tp->t_erase = sg->sg_erase;
		tp->t_kill = sg->sg_kill;
		tp->t_ispeed = sg->sg_ispeed;
		tp->t_ospeed = sg->sg_ospeed;
		newflags = (tp->t_flags&0xffff0000) | (sg->sg_flags&0xffff);
E 110
I 110
	case TIOCSETAS:
	case TIOCSETAWS:
	case TIOCSETAFS:
		soft = 1;
		goto set;
	case TIOCSETA:
	case TIOCSETAW:
	case TIOCSETAF:
		soft = 0;
set:
		{
		register struct termios *t = (struct termios *)data;

E 110
D 64
setin:
E 64
D 84
		s = spl5();
E 84
I 84
		s = spltty();
E 84
D 110
		if (tp->t_flags&RAW || newflags&RAW || com == TIOCSETP) {
			ttywait(tp);
			ttyflush(tp, FREAD);
		} else if ((tp->t_flags&CBREAK) != (newflags&CBREAK)) {
			if (newflags&CBREAK) {
				struct clist tq;
E 112
I 112
		bcopy(&tp->t_termios, t, sizeof(struct termios));
		break;
	}
E 112
E 110
I 110
		if (com == TIOCSETAF || com == TIOCSETAFS) 
			ttywflush(tp);
		else {
			if (com == TIOCSETAW || com == TIOCSETAWS)
				ttywait(tp);
			if ((t->c_lflag&ICANON) != (tp->t_lflag&ICANON))
				if (t->c_lflag&ICANON) {	
					tp->t_lflag |= PENDIN;
					ttwakeup(tp);
				}
				else {
					struct clist tq;
E 110

D 110
D 112
				catq(&tp->t_rawq, &tp->t_canq);
				tq = tp->t_rawq;
				tp->t_rawq = tp->t_canq;
				tp->t_canq = tq;
			} else {
				tp->t_flags |= PENDIN;
I 66
				newflags |= PENDIN;
E 66
				ttwakeup(tp);
E 112
I 112
D 117
	case TIOCSETAS:
	case TIOCSETAWS:
	case TIOCSETAFS:
		softset = 1;
		/*FALLTHROUGH*/
E 117
I 117
D 133
	/*** THIS ALL GETS REMOVED ***/
	case JUNK_TIOCSETAS:
	case JUNK_TIOCSETAWS:
	case JUNK_TIOCSETAFS:
		((struct termios *)data)->c_cflag |= CIGNORE;
		switch(com) {
		case JUNK_TIOCSETAS:
			com = TIOCSETA;
			break;
		case JUNK_TIOCSETAWS:
			com = TIOCSETAW;
			break;
		case JUNK_TIOCSETAFS:
			com = TIOCSETAF;
			break;
		}
	/*******************************/
		/*FALLTHROGH*/
E 133
E 117
	case TIOCSETA:
	case TIOCSETAW:
D 115
	case TIOCSETAF:
		{
E 115
I 115
	case TIOCSETAF: {
E 115
		register struct termios *t = (struct termios *)data;
I 120

E 120
D 117
		int error;

E 117
		s = spltty();
D 117
		if (!softset) {
E 117
I 117
		if (com == TIOCSETAW || com == TIOCSETAF) {
D 120
			ttywait(tp);
E 120
I 120
			if (error = ttywait(tp)) {
				splx(s);
				return (error);
			}
E 120
D 134
			if (com == TIOCSETAF);
E 134
I 134
			if (com == TIOCSETAF)
E 134
				ttyflush(tp, FREAD);
		}
D 120
		if (!(t->c_cflag&CIGNORE)) {
E 120
I 120
		if ((t->c_cflag&CIGNORE) == 0) {
E 120
E 117
			/*
			 * set device hardware
			 */
D 115
			if (tp->t_param && (error = (*tp->t_param)(tp, t)))
E 115
I 115
			if (tp->t_param && (error = (*tp->t_param)(tp, t))) {
				splx(s);
E 115
				return (error);
D 115
			else {
E 115
I 115
			} else {
D 120
				if (!(tp->t_state&TS_CARR_ON) &&
E 120
I 120
				if ((tp->t_state&TS_CARR_ON) == 0 &&
E 120
				    (tp->t_cflag&CLOCAL) &&
D 120
				    !(t->c_cflag&CLOCAL)) {
E 120
I 120
				    (t->c_cflag&CLOCAL) == 0) {
E 120
					tp->t_state &= ~TS_ISOPEN;
					tp->t_state |= TS_WOPEN;
					ttwakeup(tp);
				}
E 115
				tp->t_cflag = t->c_cflag;
				tp->t_ispeed = t->c_ispeed;
				tp->t_ospeed = t->c_ospeed;
E 112
			}
I 112
			ttsetwater(tp);
E 112
E 110
I 110
					catq(&tp->t_rawq, &tp->t_canq);
					tq = tp->t_rawq;
					tp->t_rawq = tp->t_canq;
					tp->t_canq = tq;
				}
E 110
		}
D 110
D 112
		tp->t_flags = newflags;
		if (tp->t_flags&RAW) {
			tp->t_state &= ~TS_TTSTOP;
			ttstart(tp);
E 112
I 112
D 117
		if (com == TIOCSETAF || com == TIOCSETAFS) 
			ttywflush(tp);
		else {
			if (com == TIOCSETAW || com == TIOCSETAWS)
				ttywait(tp);
E 117
I 117
		if (com != TIOCSETAF) {
E 117
			if ((t->c_lflag&ICANON) != (tp->t_lflag&ICANON))
				if (t->c_lflag&ICANON) {	
					tp->t_lflag |= PENDIN;
					ttwakeup(tp);
				}
				else {
					struct clist tq;

					catq(&tp->t_rawq, &tp->t_canq);
					tq = tp->t_rawq;
					tp->t_rawq = tp->t_canq;
					tp->t_canq = tq;
				}
E 112
E 110
I 110
		tp->t_iflag = t->c_iflag;
		tp->t_oflag = t->c_oflag;
		tp->t_lflag = t->c_lflag;
		bcopy(t->c_cc, tp->t_cc, sizeof(t->c_cc));
		if (!soft) {
			tp->t_cflag = t->c_cflag;
			tp->t_ispeed = t->c_ispeed;
			tp->t_ospeed = t->c_ospeed;
E 110
		}
I 112
		tp->t_iflag = t->c_iflag;
		tp->t_oflag = t->c_oflag;
I 127
		/*
		 * Make the EXTPROC bit read only.
		 */
		if (tp->t_lflag&EXTPROC)
			t->c_lflag |= EXTPROC;
		else
			t->c_lflag &= ~EXTPROC;
E 127
		tp->t_lflag = t->c_lflag;
		bcopy(t->c_cc, tp->t_cc, sizeof(t->c_cc));
E 112
		splx(s);
I 110
		if (tp->t_trace & TTRACE_STATE)
			ttytrace(com, tp);
E 110
		break;
	}

D 110
D 112
	/* send current parameters to user */
	case TIOCGETP: {
		register struct sgttyb *sg = (struct sgttyb *)data;

		sg->sg_ispeed = tp->t_ispeed;
		sg->sg_ospeed = tp->t_ospeed;
		sg->sg_erase = tp->t_erase;
		sg->sg_kill = tp->t_kill;
		sg->sg_flags = tp->t_flags;
E 110
I 110
	case TIOCTRACE:
		tp->t_trace = *(int *)data;
E 110
		break;
D 110
	}
E 110

E 112
D 115
	case FIONBIO:
		if (*(int *)data)
			tp->t_state |= TS_NBIO;
		else
			tp->t_state &= ~TS_NBIO;
		break;

	case FIOASYNC:
		if (*(int *)data)
			tp->t_state |= TS_ASYNC;
		else
			tp->t_state &= ~TS_ASYNC;
I 64
		break;

E 115
D 110
D 112
	case TIOCGETC:
		bcopy((caddr_t)&tp->t_intrc, data, sizeof (struct tchars));
		break;
E 110

D 110
	case TIOCSETC:
		bcopy(data, (caddr_t)&tp->t_intrc, sizeof (struct tchars));
E 64
		break;

	/* set/get local special characters */
	case TIOCSLTC:
		bcopy(data, (caddr_t)&tp->t_suspc, sizeof (struct ltchars));
		break;

	case TIOCGLTC:
		bcopy((caddr_t)&tp->t_suspc, data, sizeof (struct ltchars));
		break;

E 112
E 110
	/*
D 110
D 112
	 * Modify local mode word.
E 112
I 112
D 118
	 * Acquire controlling terminal.
E 118
I 118
	 * Set controlling terminal.
	 * Session ctty vnode pointer set in vnode layer.
E 118
E 112
	 */
D 112
	case TIOCLBIS:
		tp->t_flags |= *(int *)data << 16;
		break;
E 112
I 112
D 137
	case TIOCSCTTY: {
		register struct proc *p = u.u_procp;
E 112

E 137
I 137
	case TIOCSCTTY:
E 137
D 112
	case TIOCLBIC:
		tp->t_flags &= ~(*(int *)data << 16);
E 112
I 112
D 118
		/* RETHINK - whether non-session leader
		 * can allocate a new ctty for a session.
		 */
		if (u.u_ttyp || 
		    (tp->t_session && tp->t_session != p->p_session) ||
		    (!tp->t_session && !SESS_LEADER(p)))
E 118
I 118
		if (!SESS_LEADER(p) || 
		   (p->p_session->s_ttyvp || tp->t_session) &&
		   (tp->t_session != p->p_session))
E 118
D 117
			return(EPERM);
E 117
I 117
			return (EPERM);
E 117
D 118
		u.u_ttyp = tp;
		u.u_ttyd = tp->t_dev;
		if (tp->t_pgid == 0)
			tp->t_pgid = p->p_pgrp->pg_id;
E 118
		tp->t_session = p->p_session;
I 118
		tp->t_pgrp = p->p_pgrp;
		p->p_session->s_ttyp = tp;
		p->p_flag |= SCTTY;
E 118
E 112
		break;
I 112
D 137
	}
E 137
E 112
D 118

E 118
I 118
		
E 118
D 112
	case TIOCLSET:
		tp->t_flags &= 0xffff;
		tp->t_flags |= *(int *)data << 16;
		break;

	case TIOCLGET:
D 80
		*(int *)data = tp->t_flags >> 16;
E 80
I 80
D 101
		*(int *)data = ((unsigned) tp->t_flags) >> 16;
E 101
I 101
		*(int *)data = ((unsigned)tp->t_flags) >> 16;
E 101
E 80
		break;

E 112
D 84
	/* should allow SPGRP and GPGRP only if tty open for reading */
E 84
I 84
	/*
E 110
D 86
	 * Allow SPGRP only if tty is ours and is open for reading.
E 86
I 86
D 112
	 * Allow SPGRP only if tty is open for reading.
E 86
I 85
	 * Quick check: if we can find a process in the new pgrp,
	 * this user must own that process.
	 * SHOULD VERIFY THAT PGRP IS IN USE AND IS THIS USER'S.
E 112
I 112
	 * Set terminal process group.
E 112
E 85
	 */
E 84
D 87
	case TIOCSPGRP:
D 84
		tp->t_pgrp = *(int *)data;
E 84
I 84
		{
E 87
I 87
	case TIOCSPGRP: {
E 87
D 112
		struct proc *p;
		int pgrp = *(int *)data;
E 112
I 112
D 137
		register struct proc *p = u.u_procp;
E 137
		register struct pgrp *pgrp = pgfind(*(int *)data);
E 112

D 112
		if (u.u_uid && (flag & FREAD) == 0)
			return (EPERM);
D 86
		if (u.u_uid && u.u_ttyp != tp)
			return (EACCES);
E 86
I 85
		p = pfind(pgrp);
		if (p && p->p_pgrp == pgrp &&
		    p->p_uid != u.u_uid && u.u_uid && !inferior(p))
			return (EPERM);
E 85
		tp->t_pgrp = pgrp;
E 112
I 112
D 118
		if (u.u_uid && 
		    (tp != u.u_ttyp ||
		    (pgrp && pgrp->pg_session != p->p_session))) {
			if (u.u_ttyp == NULL)
				return (ENOTTY);
			else
				return (EPERM);
		}
		tp->t_pgid = *(int *)data;
E 118
I 118
		if (!isctty(p, tp))
			return (ENOTTY);
D 119
		else if (pgrp->pg_session != p->p_session)
E 119
I 119
		else if (pgrp == NULL || pgrp->pg_session != p->p_session)
E 119
			return (EPERM);
		tp->t_pgrp = pgrp;
E 118
E 112
E 84
		break;
I 84
D 87
		}
E 87
I 87
	}
E 87
E 84

	case TIOCGPGRP:
D 112
		*(int *)data = tp->t_pgrp;
E 112
I 112
D 118
		*(int *)data = tp->t_pgid;
E 118
I 118
D 137
		if (!isctty(u.u_procp, tp))
E 137
I 137
		if (!isctty(p, tp))
E 137
			return (ENOTTY);
D 134
		*(int *)data = tp->t_pgrp ? tp->t_pgrp->pg_id : 0;
E 134
I 134
		*(int *)data = tp->t_pgrp ? tp->t_pgrp->pg_id : NO_PID;
E 134
E 118
E 112
		break;

I 85
	case TIOCSWINSZ:
D 87
		if (bcmp((caddr_t)&tp->t_winsize, data, 
				sizeof(struct winsize))) {
E 87
I 87
		if (bcmp((caddr_t)&tp->t_winsize, data,
		    sizeof (struct winsize))) {
E 87
			tp->t_winsize = *(struct winsize *)data;
D 112
			gsignal(tp->t_pgrp, SIGWINCH);
E 112
I 112
D 118
			gsignal(tp->t_pgid, SIGWINCH);
E 118
I 118
D 127
			pgsignal(tp->t_pgrp, SIGWINCH);
E 127
I 127
			pgsignal(tp->t_pgrp, SIGWINCH, 1);
E 127
E 118
E 112
		}
		break;

	case TIOCGWINSZ:
		*(struct winsize *)data = tp->t_winsize;
		break;

I 102
	case TIOCCONS:
		if (*(int *)data) {
D 124
			if (constty != NULL)
E 124
I 124
			if (constty && constty != tp &&
			    (constty->t_state & (TS_CARR_ON|TS_ISOPEN)) ==
			    (TS_CARR_ON|TS_ISOPEN))
E 124
				return (EBUSY);
#ifndef	UCONSOLE
D 114
			if (!suser())
				return (EPERM);
E 114
I 114
D 137
			if (error = suser(u.u_cred, &u.u_acflag))
E 137
I 137
			if (error = suser(p->p_ucred, &p->p_acflag))
E 137
				return (error);
E 114
#endif
			constty = tp;
		} else if (tp == constty)
D 109
			constty == NULL;
E 109
I 109
			constty = NULL;
E 109
		break;

I 138
	case TIOCDRAIN:
		if (error = ttywait(tp))
			return (error);
		break;

E 138
I 112
D 137
#ifdef COMPAT_43
	case TIOCGETP:
	case TIOCSETP:
	case TIOCSETN:
	case TIOCGETC:
	case TIOCSETC:
	case TIOCSLTC:
	case TIOCGLTC:
	case TIOCLBIS:
	case TIOCLBIC:
	case TIOCLSET:
	case TIOCLGET:
D 117
	case TIOCGETDCOMPAT:
	case TIOCSETDCOMPAT:
E 117
I 117
	case OTIOCGETD:
	case OTIOCSETD:
I 132
	case OTIOCCONS:
E 132
E 117
		return(ttcompat(tp, com, data, flag));
#endif

E 137
E 112
I 110
	/* allow old ioctls for now */
	case TIOCGETP:
	case TIOCSETP:
	case TIOCSETN:
	case TIOCGETC:
	case TIOCSETC:
	case TIOCSLTC:
	case TIOCGLTC:
	case TIOCLBIS:
	case TIOCLBIC:
	case TIOCLSET:
	case TIOCLGET:
		return(ottioctl(tp, com, data, flag));

E 110
E 102
I 100
D 101
	case TIOCCONS:
	    {
		extern struct tty *constty;

		if (constty != NULL)
			return (EBUSY);
#ifndef	UCONSOLE
		if (!suser())
			return (EPERM);
#endif
		constty = tp;
		break;
	    }

E 101
E 100
E 85
E 63
E 38
E 15
E 7
D 51
/* end of locals */
I 15

E 51
E 15
E 4
	default:
I 137
D 147
#ifdef COMPAT_43
E 147
I 147
#if defined(COMPAT_43) || defined(COMPAT_SUNOS)
E 147
		return (ttcompat(tp, com, data, flag));
#else
E 137
I 57
D 63
#ifndef NOCOMPAT
		return (ottioctl(tp, com, data, flag));
#else
E 63
E 57
D 45
		return(0);
E 45
I 45
D 51
		return (0);
E 51
I 51
		return (-1);
I 137
#endif
E 137
I 57
D 63
#endif
E 63
E 57
E 51
E 45
	}
D 45
	return(1);
E 45
I 45
D 51
	return (1);
E 51
I 51
	return (0);
E 51
E 45
I 33
}

I 110
/*
 * DEBUG - to be removed
 */
ttytrace(ioc, tp)
	struct tty *tp;
{
	register u_char *cc = tp->t_cc;
	char comm[MAXCOMLEN+1];
	static int seq = 0;
	
	bcopy(u.u_comm, comm, MAXCOMLEN+1);
	comm[MAXCOMLEN] = '\0';

	/* trace changes to line disciplines */
	if (ioc == TIOCSETD) {
		log(LOG_LOCAL4|LOG_DEBUG, "%s:%x:%x:%x:%x\n",
		    comm, ioc, u.u_procp->p_pid, tp->t_dev, tp->t_line);
		return;
	}

	/*
	 * format for the trace record is:
	 *
	 * u_comm:ioctl:pid:dev_t:ldisc:iflag:oflag:lflag:cflag:ispeed:
	 *    ospeed:cc's...:seq
	 *
	 * u_comm is a string and all other values are hex. "cc's..."
	 * stands for control chars 0 through NCC-1.  seq is a sequence #
	 * to force syslogd to log every entry (rather than hold them to
	 * print "last message repeated...".
	 */
	log(LOG_LOCAL4|LOG_DEBUG, "%s:%x:%x:%x:%x:%x:%x:%x:%x:%x:%x:%x:%x:%x:%x:%x:%x:%x:%x:%x:%x:%x:%x:%x:%x:%x:%x:%x:%x:%x:%x:%x\n",
		comm, ioc, u.u_procp->p_pid, tp->t_dev, tp->t_line,
		tp->t_iflag, tp->t_oflag, tp->t_lflag, tp->t_cflag,
		tp->t_ispeed, tp->t_ospeed, cc[0], cc[1], cc[2], cc[3],
		cc[4], cc[5], cc[6], cc[7], cc[8], cc[9], cc[10], cc[11],
		cc[12], cc[13], cc[14], cc[15], cc[16], cc[17], cc[18], 
		cc[19], seq++);
}

E 110
ttnread(tp)
	struct tty *tp;
{
	int nread = 0;

D 56
	if (tp->t_local & LPENDIN)
E 56
I 56
D 110
D 112
	if (tp->t_flags & PENDIN)
E 112
I 112
	if (tp->t_lflag & PENDIN)
E 112
E 110
I 110
	if (tp->t_lflag & PENDIN)
E 110
E 56
		ttypend(tp);
	nread = tp->t_canq.c_cc;
D 110
D 112
	if (tp->t_flags & (RAW|CBREAK))
E 112
I 112
	if ((tp->t_lflag & ICANON) == 0)
E 112
E 110
I 110
	if (tp->t_lflag & ICANON == 0)
E 110
		nread += tp->t_rawq.c_cc;
	return (nread);
}

D 35
ttselect(dev, flag)
E 35
I 35
D 148
ttselect(dev, rw)
E 148
I 148
ttselect(dev, rw, p)
E 148
E 35
	dev_t dev;
D 35
	int flag;
E 35
I 35
	int rw;
I 148
	struct proc *p;
E 148
E 35
{
	register struct tty *tp = &cdevsw[major(dev)].d_ttys[minor(dev)];
	int nread;
I 35
D 84
	int s = spl5();
E 84
I 84
	int s = spltty();
E 84
E 35

D 35
	switch (flag) {
E 35
I 35
	switch (rw) {
E 35

	case FREAD:
		nread = ttnread(tp);
D 89
		if (nread > 0)
E 89
I 89
D 101
		if ((nread > 0) || ((tp->t_state & TS_CARR_ON) == 0))
E 101
I 101
D 115
		if (nread > 0 || (tp->t_state & TS_CARR_ON) == 0)
E 115
I 115
		if (nread > 0 || 
D 120
		   (!(tp->t_cflag&CLOCAL) && !(tp->t_state&TS_CARR_ON)))
E 120
I 120
		   ((tp->t_cflag&CLOCAL) == 0 && (tp->t_state&TS_CARR_ON) == 0))
E 120
E 115
E 101
E 89
D 35
			return (1);
E 35
I 35
			goto win;
E 35
D 34
		if (tp->t_rsel && tp->t_rsel->p_wchan == (caddr_t)select)
E 34
I 34
D 148
		if (tp->t_rsel && tp->t_rsel->p_wchan == (caddr_t)&selwait)
E 34
D 35
			tp->t_state |= RCOLL;
E 35
I 35
			tp->t_state |= TS_RCOLL;
E 35
		else
D 137
			tp->t_rsel = u.u_procp;
E 137
I 137
			tp->t_rsel = curproc;
E 148
I 148
		selrecord(p, &tp->t_rsel);
E 148
E 137
D 35
		return (0);
E 35
I 35
		break;
E 35

D 35
	default:
		return (1);
E 35
I 35
	case FWRITE:
D 112
		if (tp->t_outq.c_cc <= TTLOWAT(tp))
E 112
I 112
		if (tp->t_outq.c_cc <= tp->t_lowat)
E 112
			goto win;
D 36
printf("wsel block\n");
E 36
D 148
		if (tp->t_wsel && tp->t_wsel->p_wchan == (caddr_t)&selwait)
			tp->t_state |= TS_WCOLL;
		else
D 137
			tp->t_wsel = u.u_procp;
E 137
I 137
			tp->t_wsel = curproc;
E 148
I 148
		selrecord(p, &tp->t_wsel);
E 148
E 137
		break;
E 35
	}
E 157
I 157
	CLR(tp->t_state, TS_WOPEN);
E 157
I 35
	splx(s);
	return (0);
D 157
win:
	splx(s);
	return (1);
E 157
E 35
E 33
D 17
}

/*
 * Wait for output to drain, then flush input waiting.
 */
wflushtty(tp)
register struct tty *tp;
{

D 2
	VOID spl5();
E 2
I 2
	(void) spl5();
E 2
	while (tp->t_outq.c_cc && tp->t_state&CARR_ON) {
		(*tp->t_oproc)(tp);
		tp->t_state |= ASLEEP;
		sleep((caddr_t)&tp->t_outq, TTOPRI);
	}
D 14
	flushtty(tp);
E 14
I 14
	flushtty(tp, FREAD|FWRITE);
E 14
D 2
	VOID spl0();
E 2
I 2
	(void) spl0();
E 2
}

/*
 * flush all TTY queues
 */
D 14
flushtty(tp)
E 14
I 14
flushtty(tp, rw)
E 14
register struct tty *tp;
{
	register s;

I 9
	if (tp->t_line == NETLDISC)
		return;
E 9
I 2
	s = spl6();
E 2
D 14
	while (getc(&tp->t_canq) >= 0)
		;
	wakeup((caddr_t)&tp->t_rawq);
	wakeup((caddr_t)&tp->t_outq);
D 2
	s = spl6();
E 2
	tp->t_state &= ~TTSTOP;
	(*cdevsw[major(tp->t_dev)].d_stop)(tp);
	while (getc(&tp->t_outq) >= 0)
		;
	while (getc(&tp->t_rawq) >= 0)
		;
	tp->t_delct = 0;
I 4
	tp->t_rocount = 0;		/* local */
D 6
	tp->t_lstate = 0;	/* reset */
E 6
I 6
	tp->t_lstate = 0;
E 14
I 14
	if (rw & FREAD) {
		while (getc(&tp->t_canq) >= 0)
			;
		wakeup((caddr_t)&tp->t_rawq);
	}
	if (rw & FWRITE) {
		wakeup((caddr_t)&tp->t_outq);
		tp->t_state &= ~TTSTOP;
		(*cdevsw[major(tp->t_dev)].d_stop)(tp);
		while (getc(&tp->t_outq) >= 0)
			;
	}
	if (rw & FREAD) {
		while (getc(&tp->t_rawq) >= 0)
			;
		tp->t_delct = 0;
		tp->t_rocount = 0;		/* local */
		tp->t_rocol = 0;
		tp->t_lstate = 0;
	}
E 14
E 6
E 4
	splx(s);
}



/*
 * transfer raw input list to canonical list,
 * doing erase-kill processing and handling escapes.
 * It waits until a full line has been typed in cooked mode,
 * or until any character has been typed in raw mode.
 */
canon(tp)
register struct tty *tp;
{
	register char *bp;
	char *bp1;
	register int c;
	int mc;
	int s;

	if ((tp->t_flags&(RAW|CBREAK))==0 && tp->t_delct==0
	    || (tp->t_flags&(RAW|CBREAK))!=0 && tp->t_rawq.c_cc==0) {
		return(-1);
	}
	s = spl0();
loop:
	bp = &canonb[2];
	while ((c=getc(&tp->t_rawq)) >= 0) {
		if ((tp->t_flags&(RAW|CBREAK))==0) {
			if (c==0377) {
				tp->t_delct--;
				break;
			}
			if (bp[-1]!='\\') {
				if (c==tp->t_erase) {
					if (bp > &canonb[2])
						bp--;
					continue;
				}
				if (c==tp->t_kill)
					goto loop;
				if (c==tun.t_eofc)
					continue;
			} else {
				mc = maptab[c];
				if (c==tp->t_erase || c==tp->t_kill)
					mc = c;
				if (mc && (mc==c || (tp->t_flags&LCASE))) {
					if (bp[-2] != '\\')
						c = mc;
					bp--;
				}
			}
		}
		*bp++ = c;
		if (bp>=canonb+CANBSIZ)
			break;
	}
	bp1 = &canonb[2];
D 2
	VOID b_to_q(bp1, bp-bp1, &tp->t_canq);
E 2
I 2
	(void) b_to_q(bp1, bp-bp1, &tp->t_canq);
E 2

	if (tp->t_state&TBLOCK && tp->t_rawq.c_cc < TTYHOG/5) {
		if (putc(tun.t_startc, &tp->t_outq)==0) {
			tp->t_state &= ~TBLOCK;
			ttstart(tp);
		}
		tp->t_char = 0;
	}

	splx(s);
	return(0);
}


/*
 * block transfer input handler.
 */
ttyrend(tp, pb, pe)
register struct tty *tp;
register char *pb, *pe;
{
	int	tandem;

	tandem = tp->t_flags&TANDEM;
	if (tp->t_flags&RAW) {
D 2
		VOID b_to_q(pb, pe-pb, &tp->t_rawq);
E 2
I 2
		(void) b_to_q(pb, pe-pb, &tp->t_rawq);
E 2
		if (tp->t_chan)
D 2
			VOID sdata(tp->t_chan); else
E 2
I 2
			(void) sdata(tp->t_chan); else
E 2
			wakeup((caddr_t)&tp->t_rawq);
	} else {
		tp->t_flags &= ~TANDEM;
		while (pb < pe)
			ttyinput(*pb++, tp);
		tp->t_flags |= tandem;
	}
	if (tandem)
		ttyblock(tp);
}

/*
 * Place a character on raw TTY input queue, putting in delimiters
 * and waking up top half as needed.
 * Also echo if required.
 * The arguments are the character and the appropriate
 * tty structure.
 */
ttyinput(c, tp)
register c;
register struct tty *tp;
{
	register int t_flags;
	register struct chan *cp;

	tk_nin += 1;
	c &= 0377;
	t_flags = tp->t_flags;
	if (t_flags&TANDEM)
		ttyblock(tp);
	if ((t_flags&RAW)==0) {
		c &= 0177;
		if (tp->t_state&TTSTOP) {
			if (c==tun.t_startc) {
				tp->t_state &= ~TTSTOP;
				ttstart(tp);
				return;
			}
			if (c==tun.t_stopc)
				return;
			tp->t_state &= ~TTSTOP;
			ttstart(tp);
		} else {
			if (c==tun.t_stopc) {
				tp->t_state |= TTSTOP;
				(*cdevsw[major(tp->t_dev)].d_stop)(tp);
				return;
			}
			if (c==tun.t_startc)
				return;
		}
		if (c==tun.t_quitc || c==tun.t_intrc) {
D 14
			flushtty(tp);
E 14
I 14
			flushtty(tp, FREAD|FWRITE);
E 14
			c = (c==tun.t_intrc) ? SIGINT:SIGQUIT;
			if (tp->t_chan)
				scontrol(tp->t_chan, M_SIG, c);
			else
D 4
				signal(tp->t_pgrp, c);
E 4
I 4
				gsignal(tp->t_pgrp, c);
E 4
			return;
		}
		if (c=='\r' && t_flags&CRMOD)
			c = '\n';
	}
	if (tp->t_rawq.c_cc>TTYHOG) {
D 14
		flushtty(tp);
E 14
I 14
		flushtty(tp, FREAD|FWRITE);
E 14
		return;
	}
	if (t_flags&LCASE && c>='A' && c<='Z')
		c += 'a'-'A';
D 2
	VOID putc(c, &tp->t_rawq);
E 2
I 2
	(void) putc(c, &tp->t_rawq);
E 2
	if (t_flags&(RAW|CBREAK)||(c=='\n'||c==tun.t_eofc||c==tun.t_brkc)) {
		if ((t_flags&(RAW|CBREAK))==0 && putc(0377, &tp->t_rawq)==0)
			tp->t_delct++;
		if ((cp=tp->t_chan)!=NULL)
D 2
			VOID sdata(cp); else
E 2
I 2
			(void) sdata(cp); else
E 2
			wakeup((caddr_t)&tp->t_rawq);
	}
	if (t_flags&ECHO) {
		ttyoutput(c, tp);
		if (c==tp->t_kill && (t_flags&(RAW|CBREAK))==0)
			ttyoutput('\n', tp);
		ttstart(tp);
	}
}


/*
 * Send stop character on input overflow.
 */
ttyblock(tp)
register struct tty *tp;
{
	register x;
	x = q1.c_cc + q2.c_cc;
	if (q1.c_cc > TTYHOG) {
D 14
		flushtty(tp);
E 14
I 14
		flushtty(tp, FREAD|FWRITE);
E 14
		tp->t_state &= ~TBLOCK;
	}
	if (x >= TTYHOG/2) {
		if (putc(tun.t_stopc, &tp->t_outq)==0) {
			tp->t_state |= TBLOCK;
			tp->t_char++;
			ttstart(tp);
		}
	}
}

/*
 * put character on TTY output queue, adding delays,
 * expanding tabs, and handling the CR/NL bit.
 * It is called both from the top half for output, and from
 * interrupt level for echoing.
 * The arguments are the character and the tty structure.
 */
ttyoutput(c, tp)
register c;
register struct tty *tp;
{
	register char *colp;
	register ctype;

D 2
	tk_nout++;
E 2
	/*
	 * Ignore EOT in normal mode to avoid hanging up
	 * certain terminals.
	 * In raw mode dump the char unchanged.
	 */
D 2

E 2
	if ((tp->t_flags&RAW)==0) {
		c &= 0177;
		if ((tp->t_flags&CBREAK)==0 && c==CEOT)
			return;
	} else {
D 2
		VOID putc(c, &tp->t_outq);
E 2
I 2
		tk_nout++;
		(void) putc(c, &tp->t_outq);
E 2
		return;
	}

	/*
	 * Turn tabs to spaces as required
	 */
	if (c=='\t' && (tp->t_flags&TBDELAY)==XTABS) {
D 2
		c = 8;
		do
			ttyoutput(' ', tp);
		while (--c >= 0 && tp->t_col&07);
E 2
I 2
		c = 8 - (tp->t_col & 7);
		(void) b_to_q("        ", c, &tp->t_outq);
		tp->t_col += c;
		tk_nout += c;
E 2
		return;
	}
I 2
	tk_nout++;
E 2
	/*
	 * for upper-case-only terminals,
	 * generate escapes.
	 */
	if (tp->t_flags&LCASE) {
		colp = "({)}!|^~'`";
		while(*colp++)
			if(c == *colp++) {
				ttyoutput('\\', tp);
				c = colp[-2];
				break;
			}
		if ('a'<=c && c<='z')
			c += 'A' - 'a';
	}
	/*
	 * turn <nl> to <cr><lf> if desired.
	 */
	if (c=='\n' && tp->t_flags&CRMOD)
		ttyoutput('\r', tp);
D 2
	VOID putc(c, &tp->t_outq);
E 2
I 2
	(void) putc(c, &tp->t_outq);
E 2
	/*
	 * Calculate delays.
	 * The numbers here represent clock ticks
	 * and are not necessarily optimal for all terminals.
	 * The delays are indicated by characters above 0200.
	 * In raw mode there are no delays and the
	 * transmission path is 8 bits wide.
	 */
	colp = &tp->t_col;
	ctype = partab[c];
	c = 0;
	switch (ctype&077) {

	/* ordinary */
	case 0:
		(*colp)++;

	/* non-printing */
	case 1:
		break;

	/* backspace */
	case 2:
		if (*colp)
			(*colp)--;
		break;

	/* newline */
	case 3:
		ctype = (tp->t_flags >> 8) & 03;
		if(ctype == 1) { /* tty 37 */
			if (*colp)
				c = max(((unsigned)*colp>>4) + 3, (unsigned)6);
		} else
		if(ctype == 2) { /* vt05 */
			c = 6;
		}
		*colp = 0;
		break;

	/* tab */
	case 4:
		ctype = (tp->t_flags >> 10) & 03;
		if(ctype == 1) { /* tty 37 */
			c = 1 - (*colp | ~07);
			if(c < 5)
				c = 0;
		}
		*colp |= 07;
		(*colp)++;
		break;

	/* vertical motion */
	case 5:
		if(tp->t_flags & VTDELAY) /* tty 37 */
			c = 0177;
		break;

	/* carriage return */
	case 6:
		ctype = (tp->t_flags >> 12) & 03;
		if(ctype == 1) { /* tn 300 */
			c = 5;
		} else if(ctype == 2) { /* ti 700 */
			c = 10;
		} else if(ctype == 3) { /* concept 100 */
			int i;
D 12
			for (i= *colp; i<9; i++)
D 2
				VOID putc(0177, &tp->t_outq);
E 2
I 2
				(void) putc(0177, &tp->t_outq);
E 12
I 12
			if ((i = *colp) >= 0)
				for (; i<9; i++)
					(void) putc(0177, &tp->t_outq);
E 12
E 2
		}
		*colp = 0;
	}
	if(c)
D 2
		VOID putc(c|0200, &tp->t_outq);
E 2
I 2
		(void) putc(c|0200, &tp->t_outq);
E 2
}

/*
 * Restart typewriter output following a delay
 * timeout.
 * The name of the routine is passed to the timeout
 * subroutine and it is called during a clock interrupt.
 */
ttrstrt(tp)
register struct tty *tp;
{

	tp->t_state &= ~TIMEOUT;
	ttstart(tp);
}

/*
 * Start output on the typewriter. It is used from the top half
 * after some characters have been put on the output queue,
 * from the interrupt routine to transmit the next
 * character, and after a timeout has finished.
 */
ttstart(tp)
register struct tty *tp;
{
	register s;

	s = spl5();
	if((tp->t_state&(TIMEOUT|TTSTOP|BUSY)) == 0)
		(*tp->t_oproc)(tp);
	splx(s);
}

/*
 * Called from device's read routine after it has
 * calculated the tty-structure given as argument.
 */
ttread(tp)
register struct tty *tp;
{
register s;

	if ((tp->t_state&CARR_ON)==0)
		return(-1);
	s = spl5();
	if (tp->t_canq.c_cc==0)
		while (canon(tp)<0)
			if (tp->t_chan==NULL) {
				sleep((caddr_t)&tp->t_rawq, TTIPRI); 
			} else {
				splx(s);
				return(0);
			}
	splx(s);
	while (tp->t_canq.c_cc && passc(getc(&tp->t_canq))>=0)
			;
	return(tp->t_rawq.c_cc+tp->t_canq.c_cc);
}

/*
 * Called from the device's write routine after it has
 * calculated the tty-structure given as argument.
 */
caddr_t
ttwrite(tp)
register struct tty *tp;
{
	/*
	 * THE POSITIONING OF CP, CC, AND CE ARE CRITICAL
	 * AND MUST NOT BE CHANGED WITHOUT PATCHING
	 * THE 'ASM' INLINES BELOW.  WATCH OUT.
	 */
	register char *cp;
	register int cc, ce;
	register i;
	char obuf[OBUFSIZ];

	if ((tp->t_state&CARR_ON)==0)
		return(NULL);
	while (u.u_count) {
		cc = MIN(u.u_count, OBUFSIZ);
		cp = obuf;
		iomove(cp, (unsigned)cc, B_WRITE);
		if (u.u_error)
			break;
D 2
		VOID spl5();
E 2
I 2
		(void) spl5();
E 2
		while (tp->t_outq.c_cc > TTHIWAT) {
			ttstart(tp);
			tp->t_state |= ASLEEP;
			if (tp->t_chan) {
				u.u_base -= cc;
				u.u_offset -= cc;
				u.u_count += cc;
D 2
				VOID spl0();
E 2
I 2
				(void) spl0();
E 2
				return((caddr_t)&tp->t_outq);
			}
			sleep((caddr_t)&tp->t_outq, TTOPRI);
		}
D 2
		VOID spl0();
E 2
I 2
		(void) spl0();
E 2
		if (tp->t_flags&LCASE) {
			while (cc--)
				ttyoutput(*cp++,tp);
			continue;
		}
		while (cc) {
			if (tp->t_flags&RAW)
				ce=cc;
			else {
#ifdef VAX
				asm("	scanc	r9,(r10),_partab,$077");
				asm("	subl3	r0,r9,r8");
#else
				ce=0;
				while(((partab[*(cp+ce)]&077)==0)&&(ce<cc))
					ce++;
#endif
				if (ce==0) {
					ttyoutput(*cp++,tp);
					cc--;
D 2
					continue;
E 2
I 2
					goto check;
E 2
				}
			}
			i=b_to_q(cp,ce,&tp->t_outq);
			ce-=i;
			tk_nout+=ce;
			tp->t_col+=ce;
			cp+=ce;
			cc-=ce;
D 2
			if (i) {
				VOID spl5();
E 2
I 2
D 4
			if (i == 0)
				continue;
E 4
check:
			if (tp->t_outq.c_cc > TTHIWAT) {
				(void) spl5();
E 2
				while (tp->t_outq.c_cc > TTHIWAT) {
					ttstart(tp);
					tp->t_state |= ASLEEP;
					sleep((caddr_t)&tp->t_outq, TTOPRI);
				}
D 2
				VOID spl0();
E 2
I 2
				(void) spl0();
E 2
			}
		}
	}
	ttstart(tp);
	return(NULL);
E 17
}
I 43

I 44
D 56
#define	OBUFSIZ	100

E 56
/*
I 94
D 140
 * Initial open of tty, or (re)entry to line discipline.
E 140
I 140
D 157
 * Initial open of tty, or (re)entry to standard tty line discipline.
E 140
E 94
D 56
 * routine called on opens while tp->t_line == NTTYDISC
 * establishes a process group for distribution of
E 56
I 56
D 112
 * Establish a process group for distribution of
E 56
 * quits and interrupts from the tty.
E 112
D 56
 * (actually, pp->p_pgrp can't be 0 when this routine
 * is called since NTTYDISC is not the default discipline)
E 56
 */
ttyopen(dev, tp)
D 45
dev_t dev;
register struct tty *tp;
E 45
I 45
	dev_t dev;
	register struct tty *tp;
E 45
{
I 147
	int s = spltty();
E 147
D 116
	register struct proc *pp;
E 116

D 112
	pp = u.u_procp;
E 112
	tp->t_dev = dev;
D 45
	if(pp->p_pgrp == 0) {
E 45
I 45
D 110
D 112
	if (pp->p_pgrp == 0) {
E 110
I 110
	if (pp->p_pgrp == 0) {	/* XXX - this has got to change */
E 110
E 45
		u.u_ttyp = tp;
		u.u_ttyd = dev;
		if (tp->t_pgrp == 0)
			tp->t_pgrp = pp->p_pid;
		pp->p_pgrp = tp->t_pgrp;
	}
E 112
I 112

I 128
D 132
	if (ttclosed(tp))	/* XXX is this still needed? (drivers do it) */
		return (ERESTART);
E 132
E 128
E 112
	tp->t_state &= ~TS_WOPEN;
D 84
	tp->t_state |= TS_ISOPEN;
	if (tp->t_line != NTTYDISC)
D 63
		wflushtty(tp);
E 63
I 63
		ttywflush(tp);
E 84
I 84
	if ((tp->t_state & TS_ISOPEN) == 0) {
		tp->t_state |= TS_ISOPEN;
I 85
		bzero((caddr_t)&tp->t_winsize, sizeof(tp->t_winsize));
E 85
D 110
D 112
		if (tp->t_line != NTTYDISC)
			ttywflush(tp);
E 112
E 110
I 110
		/*
		 * CHANGE: used to do a ttywflush() if it was the
		 *  old (old) line discipline.
		 */
E 110
	}
I 147
	splx(s);
E 147
E 84
E 63
I 51
	return (0);
E 51
}

/*
I 94
 * "close" a line discipline
 */
D 142
ttylclose(tp)
	register struct tty *tp;
E 142
I 142
ttylclose(tp, flag)
	struct tty *tp;
	int flag;
E 142
{

D 142
	ttywflush(tp);
E 142
I 142
	if (flag&IO_NDELAY)
		ttyflush(tp, FREAD|FWRITE);
	else
		ttywflush(tp);
E 142
D 110
D 112
	tp->t_line = 0;
E 112
E 110
}

/*
E 157
E 94
D 140
 * clean tp on last close
E 140
I 140
 * Handle close() on a tty line: flush and set to initial state,
 * bumping generation number so that pending read/write calls
 * can detect recycling of the tty.
E 140
 */
I 157
int
E 157
ttyclose(tp)
D 45
register struct tty *tp;
E 45
I 45
	register struct tty *tp;
E 45
{
I 157
	extern struct tty *constty;	/* Temporary virtual console. */

E 157
D 112

E 112
I 102
	if (constty == tp)
		constty = NULL;
E 102
D 94
	if (tp->t_line) {
D 63
		wflushtty(tp);
E 63
I 63
		ttywflush(tp);
E 63
		tp->t_line = 0;
		return;
	}
E 94
I 94
D 157
	ttyflush(tp, FREAD|FWRITE);
E 94
D 112
	tp->t_pgrp = 0;
E 112
I 112
D 118
	tp->t_pgid = 0;
E 118
I 118
	tp->t_session = NULL;
E 157
I 157

	ttyflush(tp, FREAD | FWRITE);

	tp->t_gen++;
E 157
	tp->t_pgrp = NULL;
I 157
	tp->t_session = NULL;
E 157
E 118
E 112
D 63
	wflushtty(tp);
E 63
I 63
D 94
	ttywflush(tp);
E 94
E 63
	tp->t_state = 0;
I 132
D 157
	tp->t_gen++;
E 157
E 132
I 120
	return (0);
E 120
}

D 157
/*
I 94
 * Handle modem control transition on a tty.
 * Flag indicates new state of carrier.
 * Returns 0 if the line should be turned off, otherwise 1.
 */
ttymodem(tp, flag)
	register struct tty *tp;
I 147
	int flag;
E 147
{

D 110
D 112
	if ((tp->t_state&TS_WOPEN) == 0 && (tp->t_flags & MDMBUF)) {
E 112
I 112
D 125
	if ((tp->t_state&TS_WOPEN) == 0 && (tp->t_lflag & MDMBUF)) {
E 125
I 125
D 152
	if ((tp->t_state&TS_WOPEN) == 0 && (tp->t_lflag&MDMBUF)) {
E 152
I 152
	if ((tp->t_state&TS_WOPEN) == 0 && (tp->t_cflag&MDMBUF)) {
E 152
E 125
E 112
E 110
I 110
	if ((tp->t_state&TS_WOPEN) == 0 && (tp->t_lflag & MDMBUF)) {
E 110
		/*
		 * MDMBUF: do flow control according to carrier flag
		 */
		if (flag) {
			tp->t_state &= ~TS_TTSTOP;
			ttstart(tp);
		} else if ((tp->t_state&TS_TTSTOP) == 0) {
			tp->t_state |= TS_TTSTOP;
I 147
#ifdef sun4c						/* XXX */
			(*tp->t_stop)(tp, 0);
#else
E 147
			(*cdevsw[major(tp->t_dev)].d_stop)(tp, 0);
I 147
#endif
E 147
		}
	} else if (flag == 0) {
		/*
		 * Lost carrier.
		 */
		tp->t_state &= ~TS_CARR_ON;
D 125
		if (tp->t_state & TS_ISOPEN) {
D 110
D 112
			if ((tp->t_flags & NOHANG) == 0) {
E 110
I 110
			if ((tp->t_lflag & NOHANG) == 0) {
E 110
				gsignal(tp->t_pgrp, SIGHUP);
				gsignal(tp->t_pgrp, SIGCONT);
E 112
I 112
			if ((tp->t_lflag & NOHANG) == 0) {
D 118
				gsignal(tp->t_pgid, SIGHUP);
				gsignal(tp->t_pgid, SIGCONT);
E 118
I 118
				pgsignal(tp->t_pgrp, SIGHUP);
				pgsignal(tp->t_pgrp, SIGCONT);
E 118
E 112
				ttyflush(tp, FREAD|FWRITE);
				return (0);
			}
E 125
I 125
		if (tp->t_state&TS_ISOPEN && (tp->t_cflag&CLOCAL) == 0) {
			if (tp->t_session && tp->t_session->s_leader)
				psignal(tp->t_session->s_leader, SIGHUP);
			ttyflush(tp, FREAD|FWRITE);
			return (0);
E 125
		}
	} else {
		/*
		 * Carrier now on.
		 */
		tp->t_state |= TS_CARR_ON;
D 115
		wakeup((caddr_t)&tp->t_rawq);
E 115
I 115
		ttwakeup(tp);
E 115
	}
	return (1);
E 157
I 157
#define	FLUSHQ(q) {							\
	if ((q)->c_cc)							\
		ndflush(q, (q)->c_cc);					\
E 157
}

D 157
/*
I 95
 * Default modem control routine (for other line disciplines).
 * Return argument flag, to turn off device on carrier drop.
 */
D 96
nullmodem(flag)
E 96
I 96
nullmodem(tp, flag)
	register struct tty *tp;
E 96
	int flag;
{
	
	if (flag)
		tp->t_state |= TS_CARR_ON;
D 117
	else
E 117
I 117
	else {
E 117
		tp->t_state &= ~TS_CARR_ON;
I 117
D 125
		if ((tp->t_lflag & NOHANG) == 0)
D 118
			gsignal(tp->t_pgid, SIGHUP);
E 118
I 118
			pgsignal(tp->t_pgrp, SIGHUP);
E 125
I 125
		if ((tp->t_cflag&CLOCAL) == 0) {
			if (tp->t_session && tp->t_session->s_leader)
				psignal(tp->t_session->s_leader, SIGHUP);
			return (0);
		}
E 125
E 118
	}
E 117
D 125
	return (flag);
E 125
I 125
	return (1);
E 125
}
E 157
I 157
/* Is 'c' a line delimiter ("break" character)? */
#define	TTBREAKC(c)							\
	((c) == '\n' || ((c) == cc[VEOF] ||				\
	(c) == cc[VEOL] || (c) == cc[VEOL2]) && (c) != _POSIX_VDISABLE)
E 157

D 157
/*
E 95
E 94
 * reinput pending characters after state switch
D 84
 * call at spl5().
E 84
I 84
 * call at spltty().
E 84
 */
ttypend(tp)
D 45
register struct tty *tp;
E 45
I 45
	register struct tty *tp;
E 45
{
	struct clist tq;
	register c;
E 157

D 56
	tp->t_local &= ~LPENDIN;
	tp->t_lstate |= LSTYPEN;
E 56
I 56
D 110
D 112
	tp->t_flags &= ~PENDIN;
E 112
I 112
D 157
	tp->t_lflag &= ~PENDIN;
E 112
E 110
I 110
	tp->t_lflag &= ~PENDIN;
E 110
	tp->t_state |= TS_TYPEN;
E 56
	tq = tp->t_rawq;
	tp->t_rawq.c_cc = 0;
	tp->t_rawq.c_cf = tp->t_rawq.c_cl = 0;
	while ((c = getc(&tq)) >= 0)
		ttyinput(c, tp);
D 56
	tp->t_lstate &= ~LSTYPEN;
E 56
I 56
	tp->t_state &= ~TS_TYPEN;
E 56
}

E 157
/*
I 112
D 140
 *
E 112
I 110
 *
E 110
D 56
 * Place a character on raw TTY input queue, putting in delimiters
 * and waking up top half as needed.
 * Also echo if required.
 * The arguments are the character and the appropriate
 * tty structure.
E 56
I 56
 * Place a character on raw TTY input queue,
 * putting in delimiters and waking up top
 * half as needed.  Also echo if required.
 * The arguments are the character and the
 * appropriate tty structure.
E 140
I 140
 * Process input of a single character received on a tty.
E 140
E 56
 */
I 157
int
E 157
ttyinput(c, tp)
D 45
register c;
register struct tty *tp;
E 45
I 45
D 157
	register c;
E 157
I 157
	register int c;
E 157
	register struct tty *tp;
E 45
{
D 56
	register int t_flags;
E 56
I 56
D 110
D 112
	register int t_flags = tp->t_flags;
E 56
	int i;
E 112
I 112
D 157
	register int iflag = tp->t_iflag;
	register int lflag = tp->t_lflag;
	register u_char *cc = tp->t_cc;
E 157
I 157
	register int iflag, lflag;
	register u_char *cc;
E 157
	int i, err;
E 112
E 110
I 110
	register int iflag = tp->t_iflag;
	register int lflag = tp->t_lflag;
	register u_char *cc = tp->t_cc;
	int i, err;
E 110

D 56
	if (tp->t_local&LPENDIN)
E 56
I 56
	/*
	 * If input is pending take it first.
	 */
D 110
D 112
	if (t_flags&PENDIN)
E 112
I 112
D 157
	if (lflag&PENDIN)
E 157
I 157
	lflag = tp->t_lflag;
	if (ISSET(lflag, PENDIN))
E 157
E 112
E 110
I 110
	if (lflag&PENDIN)
E 110
E 56
		ttypend(tp);
I 112
	/*
	 * Gather stats.
	 */
E 112
I 110

E 110
D 157
	tk_nin++;
D 110
D 112
	c &= 0377;
E 110
D 56
	t_flags = tp->t_flags;
E 56
I 56

E 112
I 112
	if (lflag&ICANON) {
		tk_cancc++;
		tp->t_cancc++;
E 157
I 157
	if (ISSET(lflag, ICANON)) {
		++tk_cancc;
		++tp->t_cancc;
E 157
	} else {
D 157
		tk_rawcc++;
		tp->t_rawcc++;
E 157
I 157
		++tk_rawcc;
		++tp->t_rawcc;
E 157
	}
E 112
D 157
	/*
D 110
D 112
	 * In tandem mode, check high water mark.
E 112
I 112
	 * Handle exceptional conditions (break, parity, framing).
E 112
E 110
I 110
	 * Handle exceptional conditions (break, parity, framing).
E 110
	 */
E 56
D 110
D 112
	if (t_flags&TANDEM)
		ttyblock(tp);
D 56
	if ((t_flags&RAW)==0) {
		if ((tp->t_lstate&LSTYPEN) == 0)
			c &= 0177;
	/* check for literal nexting very first */
		if (tp->t_lstate&LSLNCH) {
			c |= 0200;
			tp->t_lstate &= ~LSLNCH;
E 56
I 56

	if (t_flags&RAW) {
		/*
		 * Raw mode, just put character
		 * in input q w/o interpretation.
		 */
		if (tp->t_rawq.c_cc > TTYHOG) 
D 63
			flushtty(tp, FREAD|FWRITE);
E 63
I 63
			ttyflush(tp, FREAD|FWRITE);
E 63
		else {
			if (putc(c, &tp->t_rawq) >= 0)
				ttwakeup(tp);
			ttyecho(c, tp);
E 112
I 112
	if (err = (c&TTY_ERRORMASK)) {
E 157
I 157
	++tk_nin;

	/* Handle exceptional conditions (break, parity, framing). */
	cc = tp->t_cc;
	iflag = tp->t_iflag;
D 159
	if (err = (c & TTY_ERRORMASK)) {
E 157
		c &= ~TTY_ERRORMASK;
D 157
		if (err&TTY_FE && !c) {		/* break */
			if (iflag&IGNBRK)
E 157
I 157
		if (err & TTY_FE && !c) {	/* Break. */
E 159
I 159
	if (err = (ISSET(c, TTY_ERRORMASK))) {
		CLR(c, TTY_ERRORMASK);
		if (ISSET(err, TTY_FE) && !c) {	/* Break. */
E 159
			if (ISSET(iflag, IGNBRK))
E 157
				goto endcase;
D 157
			else if (iflag&BRKINT && lflag&ISIG && 
				(cc[VINTR] != _POSIX_VDISABLE))
E 157
I 157
			else if (ISSET(iflag, BRKINT) &&
			    ISSET(lflag, ISIG) &&
			    (cc[VINTR] != _POSIX_VDISABLE))
E 157
				c = cc[VINTR];
D 137
			else {
				c = 0;
				if (iflag&PARMRK)
					goto parmrk;
			}
E 137
I 137
D 157
			else if (iflag&PARMRK)
E 157
I 157
			else if (ISSET(iflag, PARMRK))
E 157
				goto parmrk;
E 137
D 157
		} else if ((err&TTY_PE && iflag&INPCK) || err&TTY_FE) {
			if (iflag&IGNPAR)
E 157
I 157
D 159
		} else if (err & TTY_PE &&
		    ISSET(iflag, INPCK) || err & TTY_FE) {
E 159
I 159
		} else if (ISSET(err, TTY_PE) &&
		    ISSET(iflag, INPCK) || ISSET(err, TTY_FE)) {
E 159
			if (ISSET(iflag, IGNPAR))
E 157
				goto endcase;
D 157
			else if (iflag&PARMRK) {
parmrk:
				putc(0377|TTY_QUOTE, &tp->t_rawq);
				putc(0|TTY_QUOTE, &tp->t_rawq);
				putc(c|TTY_QUOTE, &tp->t_rawq);
E 157
I 157
			else if (ISSET(iflag, PARMRK)) {
D 159
parmrk:				putc(0377 | TTY_QUOTE, &tp->t_rawq);
				putc(0 | TTY_QUOTE, &tp->t_rawq);
				putc(c | TTY_QUOTE, &tp->t_rawq);
E 159
I 159
parmrk:				(void)putc(0377 | TTY_QUOTE, &tp->t_rawq);
				(void)putc(0 | TTY_QUOTE, &tp->t_rawq);
				(void)putc(c | TTY_QUOTE, &tp->t_rawq);
E 159
E 157
				goto endcase;
			} else
				c = 0;
E 112
E 110
I 110
	if (err = (c&TTY_ERRORMASK)) {
		c &= TTY_CHARMASK;
		if (err&TTY_FE && !c) {		/* break */
			if (iflag&IGNBRK)
				goto endcase;
			else if (iflag&BRKINT && lflag&ISIG && 
				(cc[VINTR] != POSIX_V_DISABLE))
				c = cc[VINTR];
			else
				c = 0;
		} else if ((err&TTY_PE && iflag&INPCK) || err&TTY_FE) {
			if (iflag&IGNPAR)
				goto endcase;
			else if (iflag&PARMRK) {
				ttyinput(0377, tp);
				ttyinput(0, tp);
			} else
				c = 0;
E 110
E 56
		}
D 56
		if (tp->t_line == NTTYDISC && c==tlun.t_lnextc) {
E 56
I 56
D 110
D 112
		goto endcase;
E 112
E 110
	}
D 112

E 112
I 110
	dprintf("<%o>\n", c);

E 110
	/*
I 110
	 * In tandem mode, check high water mark.
	 */
	if (iflag&IXOFF)
		ttyblock(tp);

	/*
E 110
D 112
	 * Ignore any high bit added during
	 * previous ttyinput processing.
E 112
I 112
	 * In tandem mode, check high water mark.
E 112
	 */
D 92
	if ((tp->t_state&TS_TYPEN) == 0)
E 92
I 92
D 110
D 112
	if ((tp->t_state&TS_TYPEN) == 0 && (t_flags&PASS8) == 0)
E 112
I 112
D 157
	if (iflag&IXOFF)
E 157
I 157
	if (ISSET(iflag, IXOFF))
E 157
		ttyblock(tp);
D 157
	if ((tp->t_state&TS_TYPEN) == 0 && (iflag&ISTRIP))
E 157
I 157
	if (!ISSET(tp->t_state, TS_TYPEN) && ISSET(iflag, ISTRIP))
E 157
E 112
E 110
I 110
	if ((tp->t_state&TS_TYPEN) == 0 && (iflag&ISTRIP))
E 110
E 92
D 140
		c &= 0177;
E 140
I 140
D 159
		c &= ~0x80;
E 159
I 159
		CLR(c, 0x80);
E 159
E 140
I 127
D 133
    if ((tp->t_lflag&EXTPROC) == 0) {
E 127
	/*
	 * Check for literal nexting very first
	 */
	if (tp->t_state&TS_LNCH) {
D 112
		c |= 0200;
E 112
I 112
		c |= TTY_QUOTE;
E 112
		tp->t_state &= ~TS_LNCH;
	}
D 112

E 112
	/*
	 * Scan for special characters.  This code
	 * is really just a big case statement with
	 * non-constant cases.  The bottom of the
	 * case statement is labeled ``endcase'', so goto
	 * it after a case match, or similar.
	 */
D 110
D 112
	if (tp->t_line == NTTYDISC) {
		if (c == tp->t_lnextc) {
E 56
D 89
			if (tp->t_flags&ECHO)
E 89
I 89
			if (t_flags&ECHO)
E 89
				ttyout("^\b", tp);
E 112
I 112
	/*
	 * Control chars which aren't controlled
	 * by ICANON, ISIG, or IXON.
	 */
D 117
	if (iflag&IEXTEN) {
E 117
I 117
	if (lflag&IEXTEN) {
E 117
D 120
		if (CCEQ(cc[VLNEXT],c)) {
E 120
I 120
		if (CCEQ(cc[VLNEXT], c)) {
E 120
			if (lflag&ECHO) {
				if (lflag&ECHOE)
D 120
					ttyout("^\b", tp);
E 120
I 120
					ttyoutstr("^\b", tp);
E 120
				else
E 133
I 133
D 157
	if ((tp->t_lflag&EXTPROC) == 0) {
E 157
I 157
	if (!ISSET(lflag, EXTPROC)) {
E 157
		/*
		 * Check for literal nexting very first
		 */
D 157
		if (tp->t_state&TS_LNCH) {
E 157
I 157
		if (ISSET(tp->t_state, TS_LNCH)) {
E 157
D 159
			c |= TTY_QUOTE;
E 159
I 159
			SET(c, TTY_QUOTE);
E 159
D 157
			tp->t_state &= ~TS_LNCH;
E 157
I 157
			CLR(tp->t_state, TS_LNCH);
E 157
		}
		/*
		 * Scan for special characters.  This code
		 * is really just a big case statement with
		 * non-constant cases.  The bottom of the
		 * case statement is labeled ``endcase'', so goto
		 * it after a case match, or similar.
		 */

		/*
		 * Control chars which aren't controlled
		 * by ICANON, ISIG, or IXON.
		 */
D 157
		if (lflag&IEXTEN) {
E 157
I 157
		if (ISSET(lflag, IEXTEN)) {
E 157
			if (CCEQ(cc[VLNEXT], c)) {
D 157
				if (lflag&ECHO) {
					if (lflag&ECHOE)
						ttyoutstr("^\b", tp);
					else
E 157
I 157
				if (ISSET(lflag, ECHO)) {
					if (ISSET(lflag, ECHOE)) {
						(void)ttyoutput('^', tp);
						(void)ttyoutput('\b', tp);
					} else
E 157
						ttyecho(c, tp);
				}
D 157
				tp->t_state |= TS_LNCH;
E 157
I 157
				SET(tp->t_state, TS_LNCH);
E 157
				goto endcase;
			}
			if (CCEQ(cc[VDISCARD], c)) {
D 157
				if (lflag&FLUSHO)
					tp->t_lflag &= ~FLUSHO;
E 157
I 157
				if (ISSET(lflag, FLUSHO))
					CLR(tp->t_lflag, FLUSHO);
E 157
				else {
					ttyflush(tp, FWRITE);
E 133
					ttyecho(c, tp);
I 133
					if (tp->t_rawq.c_cc + tp->t_canq.c_cc)
						ttyretype(tp);
D 157
					tp->t_lflag |= FLUSHO;
E 157
I 157
					SET(tp->t_lflag, FLUSHO);
E 157
				}
				goto startoutput;
E 133
			}
E 112
E 110
I 110

	/*
	 * Extensions to POSIX input modes which aren't controlled
	 * by ICANON, ISIG, or IXON.
	 */
	if (iflag&IEXTEN) {
		if (CCEQ(cc[VLNEXT],c) && (iflag&ISTRIP)) {
			if (lflag&ECHO)
				ttyout("^\b", tp); /*XXX - presumes too much */
E 110
D 56
			tp->t_lstate |= LSLNCH;
	/* check for output control functions */
		} else if (c==tun.t_stopc) {
			if ((tp->t_state&TS_TTSTOP)==0) {
				tp->t_state |= TS_TTSTOP;
				(*cdevsw[major(tp->t_dev)].d_stop)(tp, 0);
				return;
			}
			if (c!=tun.t_startc)
				return;
		} else if (c==tun.t_startc) {
			tp->t_state &= ~TS_TTSTOP;
			tp->t_local &= ~LFLUSHO;
			ttstart(tp);
			return;
		} else if (tp->t_line == NTTYDISC && c==tlun.t_flushc) {
			if (tp->t_local & LFLUSHO)
				tp->t_local &= ~LFLUSHO;
E 56
I 56
D 133
			tp->t_state |= TS_LNCH;
			goto endcase;
E 133
		}
D 110
D 112
		if (c == tp->t_flushc) {
D 89
			if (tp->t_flags&FLUSHO)
E 89
I 89
			if (t_flags&FLUSHO)
E 89
				tp->t_flags &= ~FLUSHO;
E 112
I 112
D 120
		if (CCEQ(cc[VFLUSHO],c)) {
E 120
I 120
D 129
		if (CCEQ(cc[VFLUSHO], c)) {
E 129
I 129
D 133
		if (CCEQ(cc[VDISCARD], c)) {
E 129
E 120
			if (lflag&FLUSHO)
				tp->t_lflag &= ~FLUSHO;
E 112
E 110
I 110
		if (CCEQ(cc[VFLUSHO],c)) {
			if (lflag&FLUSHO)
				tp->t_lflag &= ~FLUSHO;
E 110
E 56
			else {
D 63
				flushtty(tp, FWRITE);
E 63
I 63
				ttyflush(tp, FWRITE);
E 133
I 133
		/*
		 * Signals.
		 */
D 157
		if (lflag&ISIG) {
E 157
I 157
		if (ISSET(lflag, ISIG)) {
E 157
			if (CCEQ(cc[VINTR], c) || CCEQ(cc[VQUIT], c)) {
D 157
				if ((lflag&NOFLSH) == 0)
					ttyflush(tp, FREAD|FWRITE);
E 157
I 157
				if (!ISSET(lflag, NOFLSH))
					ttyflush(tp, FREAD | FWRITE);
E 157
E 133
E 63
				ttyecho(c, tp);
D 56
				if (tp->t_rawq.c_cc+tp->t_canq.c_cc)
E 56
I 56
D 133
				if (tp->t_rawq.c_cc + tp->t_canq.c_cc)
E 56
					ttyretype(tp);
D 56
				tp->t_local |= LFLUSHO;
E 56
I 56
D 110
D 112
				tp->t_flags |= FLUSHO;
E 112
I 112
				tp->t_lflag |= FLUSHO;
E 133
I 133
				pgsignal(tp->t_pgrp,
				    CCEQ(cc[VINTR], c) ? SIGINT : SIGQUIT, 1);
				goto endcase;
E 133
E 112
E 110
I 110
				tp->t_lflag |= FLUSHO;
E 110
E 56
			}
D 56
			ttstart(tp);
			return;
		} else if (c==tun.t_intrc || c==tun.t_quitc ||
		    (tp->t_line == NTTYDISC && c==tlun.t_suspc)) {
			if ((tp->t_local & LNOFLSH) == 0)
				flushtty(tp,
				    c==tlun.t_suspc ? FREAD : FREAD|FWRITE);
E 56
I 56
D 133
			goto startoutput;
E 133
I 133
			if (CCEQ(cc[VSUSP], c)) {
D 157
				if ((lflag&NOFLSH) == 0)
E 157
I 157
				if (!ISSET(lflag, NOFLSH))
E 157
					ttyflush(tp, FREAD);
				ttyecho(c, tp);
				pgsignal(tp->t_pgrp, SIGTSTP, 1);
				goto endcase;
			}
E 133
		}
D 110
D 112
		if (c == tp->t_suspc) {
D 89
			if ((tp->t_flags&NOFLSH) == 0)
E 89
I 89
			if ((t_flags&NOFLSH) == 0)
E 112
I 112
D 133
	}
	/*
	 * Signals.
	 */
	if (lflag&ISIG) {
		if (CCEQ(cc[VINTR], c) || CCEQ(cc[VQUIT], c)) {
			if ((lflag&NOFLSH) == 0)
				ttyflush(tp, FREAD|FWRITE);
			ttyecho(c, tp);
D 118
			gsignal(tp->t_pgid, CCEQ(cc[VINTR],c) ? 
				SIGINT : SIGQUIT);
E 118
I 118
			pgsignal(tp->t_pgrp,
D 120
					CCEQ(cc[VINTR],c) ? SIGINT : SIGQUIT);
E 120
I 120
D 127
			    CCEQ(cc[VINTR], c) ? SIGINT : SIGQUIT);
E 127
I 127
			    CCEQ(cc[VINTR], c) ? SIGINT : SIGQUIT, 1);
E 127
E 120
E 118
			goto endcase;
		}
D 120
		if (CCEQ(cc[VSUSP],c)) {
E 120
I 120
		if (CCEQ(cc[VSUSP], c)) {
E 120
			if ((lflag&NOFLSH) == 0)
E 112
E 110
I 110
	}

	/*
	 * Signals.
	 */
	if (lflag&ISIG) {
		if (CCEQ(cc[VINTR], c) || CCEQ(cc[VQUIT], c)) {
			if ((lflag&NOFLSH) == 0)
				ttyflush(tp, FREAD|FWRITE);
			ttyecho(c, tp);
			gsignal(tp->t_pgrp, CCEQ(cc[VINTR],c) ? 
				SIGINT : SIGQUIT);
			goto endcase;
		}
		if (CCEQ(cc[VSUSP],c)) {
			if ((lflag&NOFLSH) == 0)
E 110
E 89
D 63
				flushtty(tp, FREAD);
E 63
I 63
				ttyflush(tp, FREAD);
E 63
E 56
			ttyecho(c, tp);
D 56
			c = c==tun.t_intrc ? SIGINT :
				((c==tun.t_quitc) ? SIGQUIT : SIGTSTP);
			ttsignal(tp, c);
	/* check for buffer editing functions - cooked mode */
		} else if ((t_flags&CBREAK) == 0) {
			if ((tp->t_lstate&LSQUOT) &&
			    (c==tp->t_erase||c==tp->t_kill)) {
				ttyrub(unputc(&tp->t_rawq), tp);
				c |= 0200;
			}
			if (c==tp->t_erase) {
				if (tp->t_rawq.c_cc)
					ttyrub(unputc(&tp->t_rawq), tp);
			} else if (c==tp->t_kill) {
				if (tp->t_local&LCRTKIL &&
				    tp->t_rawq.c_cc == tp->t_rocount) {
					while (tp->t_rawq.c_cc)
						ttyrub(unputc(&tp->t_rawq), tp);
				} else {
					ttyecho(c, tp);
					ttyecho('\n', tp);
					while (getc(&tp->t_rawq) > 0)
						;
					tp->t_rocount = 0;
				}
				tp->t_lstate = 0;
			} else if (tp->t_line == NTTYDISC && c==tlun.t_werasc) {
				if (tp->t_rawq.c_cc == 0)
					goto out;
				do {
					c = unputc(&tp->t_rawq);
					if (c != ' ' && c != '\t')
						goto erasenb;
					ttyrub(c, tp);
				} while (tp->t_rawq.c_cc);
				goto out;
			    erasenb:
				do {
					ttyrub(c, tp);
					if (tp->t_rawq.c_cc == 0)
						goto out;
					c = unputc(&tp->t_rawq);
				} while (c != ' ' && c != '\t');
				(void) putc(c, &tp->t_rawq);
			} else if (tp->t_line == NTTYDISC && c==tlun.t_rprntc) {
				ttyretype(tp);
	/* check for cooked mode input buffer overflow */
			} else if (tp->t_rawq.c_cc+tp->t_canq.c_cc >= TTYHOG) {
				;
	/* put data char in q for user and wakeup if a break char */
			} else if (putc(c, &tp->t_rawq) >= 0) {
				if (tp->t_rawq.c_cc+tp->t_canq.c_cc==TTYHOG
				    && tp->t_line == NTTYDISC)
					(void) ttyoutput(CTRL(g), tp);
				if (!ttbreakc(c, tp)) {
					if (tp->t_rocount++ == 0)
						tp->t_rocol = tp->t_col;
				} else {
					tp->t_rocount = 0;
					catq(&tp->t_rawq, &tp->t_canq);
					/* IF (TP->T_CHAN) (VOID) SDATA(TP->T_CHAN); */
					ttwakeup(tp);
				}
				tp->t_lstate &= ~LSQUOT;
				if (c == '\\')
					tp->t_lstate |= LSQUOT;
				if (tp->t_lstate&LSERASE) {
					tp->t_lstate &= ~LSERASE;
					(void) ttyoutput('/', tp);
				}
				i = tp->t_col;
				ttyecho(c, tp);
				if (c==tun.t_eofc && tp->t_flags&ECHO) {
					i = MIN(2, tp->t_col - i);
					while (i > 0) {
						(void) ttyoutput('\b', tp);
						i--;
					}
				}
			}
	/* CBREAK mode */
		} else if (tp->t_rawq.c_cc > TTYHOG) {
E 56
I 56
D 112
			gsignal(tp->t_pgrp, SIGTSTP);
E 112
I 112
D 118
			gsignal(tp->t_pgid, SIGTSTP);
E 118
I 118
D 127
			pgsignal(tp->t_pgrp, SIGTSTP);
E 127
I 127
			pgsignal(tp->t_pgrp, SIGTSTP, 1);
E 127
E 118
E 112
			goto endcase;
		}
I 117
D 120
		if (CCEQ(cc[VINFO],c)) {
			ttyinfo(tp);
E 120
I 120
D 124
		if (CCEQ(cc[VINFO], c)) {
			pgsignal(tp->t_pgrp, SIGINFO);
			if ((lflag&NOKERNINFO) == 0)
				ttyinfo(tp);
E 120
			goto endcase;
		}
E 124
E 117
	}
D 112

E 112
	/*
	 * Handle start/stop characters.
	 */
D 110
D 112
	if (c == tp->t_stopc) {
		if ((tp->t_state&TS_TTSTOP) == 0) {
			tp->t_state |= TS_TTSTOP;
			(*cdevsw[major(tp->t_dev)].d_stop)(tp, 0);
			return;
E 112
I 112
	if (iflag&IXON) {
D 120
		if (CCEQ(cc[VSTOP],c)) {
E 120
I 120
		if (CCEQ(cc[VSTOP], c)) {
E 120
			if ((tp->t_state&TS_TTSTOP) == 0) {
				tp->t_state |= TS_TTSTOP;
				(*cdevsw[major(tp->t_dev)].d_stop)(tp, 0);
				return;
E 133
I 133
		/*
		 * Handle start/stop characters.
		 */
D 157
		if (iflag&IXON) {
E 157
I 157
		if (ISSET(iflag, IXON)) {
E 157
			if (CCEQ(cc[VSTOP], c)) {
D 157
				if ((tp->t_state&TS_TTSTOP) == 0) {
					tp->t_state |= TS_TTSTOP;
E 157
I 157
				if (!ISSET(tp->t_state, TS_TTSTOP)) {
					SET(tp->t_state, TS_TTSTOP);
E 157
I 147
#ifdef sun4c						/* XXX */
					(*tp->t_stop)(tp, 0);
#else
E 147
					(*cdevsw[major(tp->t_dev)].d_stop)(tp,
					   0);
I 147
#endif
E 147
D 157
					return;
E 157
I 157
					return (0);
E 157
				}
				if (!CCEQ(cc[VSTART], c))
D 157
					return;
				/* 
				 * if VSTART == VSTOP then toggle 
E 157
I 157
					return (0);
				/*
				 * if VSTART == VSTOP then toggle
E 157
				 */
				goto endcase;
E 133
			}
D 133
			if (!CCEQ(cc[VSTART], c))
				return;
			/* 
			 * if VSTART == VSTOP then toggle 
			 */
			goto endcase;
E 133
I 133
			if (CCEQ(cc[VSTART], c))
				goto restartoutput;
E 133
E 112
E 110
I 110
	if (iflag&IXON) {
		if (CCEQ(cc[VSTOP],c)) {
			if ((tp->t_state&TS_TTSTOP) == 0) {
				tp->t_state |= TS_TTSTOP;
				(*cdevsw[major(tp->t_dev)].d_stop)(tp, 0);
				return;
			}
			if (!CCEQ(cc[VSTART], c))
				return;
			/* 
			 * if VSTART == VSTOP we toggle 
			 */
			goto endcase;
E 110
		}
D 110
D 112
		if (c != tp->t_startc)
			return;
		goto endcase;
E 112
I 112
D 133
		if (CCEQ(cc[VSTART], c))
			goto restartoutput;
E 133
I 133
		/*
		 * IGNCR, ICRNL, & INLCR
		 */
		if (c == '\r') {
D 157
			if (iflag&IGNCR)
E 157
I 157
			if (ISSET(iflag, IGNCR))
E 157
				goto endcase;
D 157
			else if (iflag&ICRNL)
E 157
I 157
			else if (ISSET(iflag, ICRNL))
E 157
				c = '\n';
D 157
		} else if (c == '\n' && iflag&INLCR)
E 157
I 157
		} else if (c == '\n' && ISSET(iflag, INLCR))
E 157
			c = '\r';
E 133
E 112
E 110
I 110
		if (CCEQ(cc[VSTART], c))
			goto restartoutput;
E 110
	}
D 110
D 112
	if (c == tp->t_startc)
		goto restartoutput;
E 110

E 112
D 137
	/*
D 110
D 112
	 * Look for interrupt/quit chars.
E 112
I 112
D 133
	 * IGNCR, ICRNL, & INLCR
E 112
E 110
I 110
	 * IGNCR, ICRNL, & INLCR
E 110
	 */
D 110
D 112
	if (c == tp->t_intrc || c == tp->t_quitc) {
D 89
		if ((tp->t_flags&NOFLSH) == 0)
E 89
I 89
		if ((t_flags&NOFLSH) == 0)
E 89
D 63
			flushtty(tp, FREAD|FWRITE);
E 63
I 63
			ttyflush(tp, FREAD|FWRITE);
E 63
		ttyecho(c, tp);
		gsignal(tp->t_pgrp, c == tp->t_intrc ? SIGINT : SIGQUIT);
		goto endcase;
E 112
I 112
	if (c == '\r') {
		if (iflag&IGNCR)
			goto endcase;
		else if (iflag&ICRNL)
			c = '\n';
E 112
E 110
I 110
	if (c == '\r') {
		if (iflag&IGNCR)
			goto endcase;
		else if (iflag&ICRNL)
			c = '\n';
E 110
	}
I 110
	else if (c == '\n' && iflag&INLCR)
		c = '\r';
E 110
D 112

I 110
#ifdef notdef
	/*
	 * We'd like to completely remove it.
	 */
E 110
I 90
	if (tp->t_flags & LCASE && c <= 0177) {
		if (tp->t_state&TS_BKSL) {
			ttyrub(unputc(&tp->t_rawq), tp);
			if (maptab[c])
				c = maptab[c];
			c |= 0200;
			tp->t_state &= ~(TS_BKSL|TS_QUOT);
		} else if (c >= 'A' && c <= 'Z')
			c += 'a' - 'A';
		else if (c == '\\')
			tp->t_state |= TS_BKSL;
	}
I 110
#endif /*notdef*/
E 110

E 112
I 112
	else if (c == '\n' && iflag&INLCR)
		c = '\r';
I 127
    }
E 127
E 112
E 90
	/*
E 133
D 110
D 112
	 * Cbreak mode, don't process line editing
E 112
I 112
	 * Non canonical mode; don't process line editing
E 112
E 110
I 110
	 * Non canonical mode, don't process line editing
E 110
	 * characters; check high water mark for wakeup.
I 112
	 * 
E 112
I 110
	 * 
E 110
	 */
D 110
D 112
	if (t_flags&CBREAK) {
E 112
I 112
D 120
	if (!(lflag&ICANON)) {
E 120
I 120
	if ((lflag&ICANON) == 0) {
E 120
E 112
E 110
I 110
	if (!(lflag&ICANON)) {
E 110
		if (tp->t_rawq.c_cc > TTYHOG) {
E 56
D 110
D 112
			if (tp->t_outq.c_cc < TTHIWAT(tp) &&
			    tp->t_line == NTTYDISC)
D 108
				(void) ttyoutput(CTRL(g), tp);
E 108
I 108
				(void) ttyoutput(CTRL('g'), tp);
E 110
I 110
			if (iflag&IMAXBEL) {
				if (tp->t_outq.c_cc < TTHIWAT(tp))
					(void) ttyoutput(CTRL('g'), tp);
			} else
				ttyflush(tp, FREAD | FWRITE);
E 110
E 108
		} else if (putc(c, &tp->t_rawq) >= 0) {
			ttwakeup(tp);
			ttyecho(c, tp);
E 112
I 112
			if (iflag&IMAXBEL) {
				if (tp->t_outq.c_cc < tp->t_hiwat)
					(void) ttyoutput(CTRL('g'), tp);
			} else
				ttyflush(tp, FREAD | FWRITE);
		} else {
			if (putc(c, &tp->t_rawq) >= 0) {
				ttwakeup(tp);
				ttyecho(c, tp);
			}
E 112
		}
D 56
	/* RAW mode */
	} else if (tp->t_rawq.c_cc > TTYHOG) 
		flushtty(tp, FREAD|FWRITE);
	else {
		if (putc(c, &tp->t_rawq) >= 0)
E 56
I 56
		goto endcase;
	}
I 127
D 133
    if ((tp->t_lflag&EXTPROC) == 0) {
E 127
D 112

E 112
	/*
D 110
D 112
	 * From here on down cooked mode character
E 112
I 112
	 * From here on down canonical mode character
E 112
E 110
I 110
	 * From here on down canonical mode character
E 110
	 * processing takes place.
	 */
I 110

	/* 
	 * Oldstyle quoting of erase, kill, and eof chars.
	 *
	 * Historically is '\' , but can be changed (read: disabled)
	 * with the VQUOTE subscript.
	 */
E 110
D 112
	if ((tp->t_state&TS_QUOT) &&
D 110
	    (c == tp->t_erase || c == tp->t_kill)) {
E 110
I 110
	    (CCEQ(cc[VERASE], c) || CCEQ(cc[VKILL], c) || CCEQ(cc[VEOF], c))) {
E 110
		ttyrub(unputc(&tp->t_rawq), tp);
		c |= 0200;
	}
D 110
	if (c == tp->t_erase) {
E 112
I 112
	/*
	 * erase (^H / ^?)
	 */
D 117
	if (CCEQ(cc[VERASE], c) || CCEQ(cc[VERASE2], c)) {
E 117
I 117
D 132
	if (CCEQ(cc[VERASE], c)) {
E 132
I 132
	if ((c == cc[VERASE] || c == cc[VERASE2]) && c != _POSIX_VDISABLE &&
	     cc[VERASE] != _POSIX_VDISABLE) {
E 132
E 117
E 112
E 110
I 110

	/*
	 * erase (^H / ^?)
	 */
	if (CCEQ(cc[VERASE], c)) {
E 110
		if (tp->t_rawq.c_cc)
			ttyrub(unputc(&tp->t_rawq), tp);
		goto endcase;
	}
D 110
D 112
	if (c == tp->t_kill) {
D 89
		if (tp->t_flags&CRTKIL &&
E 89
I 89
		if (t_flags&CRTKIL &&
E 112
I 112
	/*
	 * kill (^U)
	 */
	if (CCEQ(cc[VKILL], c)) {
D 115
		if (lflag&ECHOKE &&
E 112
E 110
I 110
	/*
	 * kill (^X / ^U)
	 */
	if (CCEQ(cc[VKILL], c)) {
		if (lflag&ECHOKE &&
E 110
E 89
		    tp->t_rawq.c_cc == tp->t_rocount) {
E 115
I 115
		if (lflag&ECHOKE && tp->t_rawq.c_cc == tp->t_rocount &&
D 120
		    !(lflag&ECHOPRT)) {
E 120
I 120
		    (lflag&ECHOPRT) == 0) {
E 120
E 115
			while (tp->t_rawq.c_cc)
				ttyrub(unputc(&tp->t_rawq), tp);
		} else {
			ttyecho(c, tp);
D 110
D 112
			ttyecho('\n', tp);
E 112
I 112
			if (lflag&ECHOK || lflag&ECHOKE)
				ttyecho('\n', tp);
E 112
E 110
I 110
			if (lflag&ECHOK || lflag&ECHOKE)
				ttyecho('\n', tp);
E 110
			while (getc(&tp->t_rawq) > 0)
				;
			tp->t_rocount = 0;
		}
		tp->t_state &= ~TS_LOCAL;
		goto endcase;
	}
D 112

E 112
	/*
D 110
D 112
	 * New line discipline,
	 * check word erase/reprint line.
E 112
I 112
	 * word erase (^W)
E 112
E 110
I 110
	 * word erase (^W)
E 110
	 */
D 110
D 112
	if (tp->t_line == NTTYDISC) {
		if (c == tp->t_werasc) {
E 110
I 110
	if (CCEQ(cc[VWERASE], c)) {	
		if (tp->t_rawq.c_cc == 0)
			goto endcase;
		do {
			c = unputc(&tp->t_rawq);
			if (c != ' ' && c != '\t')
				goto erasenb;
			ttyrub(c, tp);
		} while (tp->t_rawq.c_cc);
		goto endcase;
erasenb:
		do {
			ttyrub(c, tp);
E 110
			if (tp->t_rawq.c_cc == 0)
				goto endcase;
D 110
			do {
				c = unputc(&tp->t_rawq);
				if (c != ' ' && c != '\t')
					goto erasenb;
				ttyrub(c, tp);
			} while (tp->t_rawq.c_cc);
E 112
I 112
	if (CCEQ(cc[VWERASE], c)) {	
		int ctype;

#define CTYPE(c) ((lflag&ALTWERASE) ? (partab[(c)&TTY_CHARMASK]&0100) : 0)
		/* 
		 * erase whitespace 
E 133
I 133
	if ((tp->t_lflag&EXTPROC) == 0) {
E 137
I 137
D 157
	if ((tp->t_lflag&EXTPROC) == 0 && lflag&ICANON) {
E 157
I 157
	if (!ISSET(tp->t_lflag, EXTPROC) && ISSET(lflag, ICANON)) {
E 157
E 137
		/*
		 * From here on down canonical mode character
		 * processing takes place.
E 133
		 */
D 133
		while ((c = unputc(&tp->t_rawq)) == ' ' || c == '\t')
			ttyrub(c, tp);
		if (c == -1)
E 133
I 133
		/*
		 * erase (^H / ^?)
		 */
		if (CCEQ(cc[VERASE], c)) {
			if (tp->t_rawq.c_cc)
				ttyrub(unputc(&tp->t_rawq), tp);
E 133
E 112
			goto endcase;
I 133
		}
E 133
D 112
	erasenb:
			do {
				ttyrub(c, tp);
				if (tp->t_rawq.c_cc == 0)
					goto endcase;
				c = unputc(&tp->t_rawq);
			} while (c != ' ' && c != '\t');
			(void) putc(c, &tp->t_rawq);
E 112
I 112
		/*
D 133
		 * special case last char of token
E 133
I 133
		 * kill (^U)
E 133
		 */
D 133
		ttyrub(c, tp);
		c = unputc(&tp->t_rawq);
		if (c == -1 || c == ' ' || c == '\t') {
			if (c != -1)
				(void) putc(c, &tp->t_rawq);
E 133
I 133
		if (CCEQ(cc[VKILL], c)) {
D 157
			if (lflag&ECHOKE && tp->t_rawq.c_cc == tp->t_rocount &&
			    (lflag&ECHOPRT) == 0) {
E 157
I 157
			if (ISSET(lflag, ECHOKE) &&
			    tp->t_rawq.c_cc == tp->t_rocount &&
			    !ISSET(lflag, ECHOPRT))
E 157
				while (tp->t_rawq.c_cc)
					ttyrub(unputc(&tp->t_rawq), tp);
D 157
			} else {
E 157
I 157
			else {
E 157
				ttyecho(c, tp);
D 157
				if (lflag&ECHOK || lflag&ECHOKE)
E 157
I 157
				if (ISSET(lflag, ECHOK) ||
				    ISSET(lflag, ECHOKE))
E 157
					ttyecho('\n', tp);
D 147
				while (getc(&tp->t_rawq) > 0)
					;
E 147
I 147
D 157
				flushq(&tp->t_rawq);
E 157
I 157
				FLUSHQ(&tp->t_rawq);
E 157
E 147
				tp->t_rocount = 0;
			}
D 157
			tp->t_state &= ~TS_LOCAL;
E 157
I 157
			CLR(tp->t_state, TS_LOCAL);
E 157
E 133
E 112
			goto endcase;
		}
D 112
		if (c == tp->t_rprntc) {
			ttyretype(tp);
			goto endcase;
		}
E 112
I 112
		/*
D 133
		 * erase rest of token
E 133
I 133
		 * word erase (^W)
E 133
		 */
D 133
		ctype = CTYPE(c);
		do {
E 133
I 133
D 157
		if (CCEQ(cc[VWERASE], c)) {	
E 157
I 157
		if (CCEQ(cc[VWERASE], c)) {
			int alt = ISSET(lflag, ALTWERASE);
E 157
			int ctype;
I 137
D 157
			int alt = lflag&ALTWERASE;
E 157
E 137

D 137
#define CTYPE(c) ((lflag&ALTWERASE) ? (partab[(c)&TTY_CHARMASK]&0100) : 0)
E 137
I 137
D 140
#define CTYPE(c) (partab[(c)&TTY_CHARMASK]&0100)
E 140
E 137
D 157
			/* 
			 * erase whitespace 
E 157
I 157
			/*
			 * erase whitespace
E 157
			 */
			while ((c = unputc(&tp->t_rawq)) == ' ' || c == '\t')
				ttyrub(c, tp);
			if (c == -1)
				goto endcase;
			/*
D 137
			 * special case last char of token
E 137
I 137
			 * erase last char of word and remember the
			 * next chars type (for ALTWERASE)
E 137
			 */
E 133
			ttyrub(c, tp);
			c = unputc(&tp->t_rawq);
D 133
			if (c == -1)
E 133
I 133
D 137
			if (c == -1 || c == ' ' || c == '\t') {
				if (c != -1)
					(void) putc(c, &tp->t_rawq);
E 137
I 137
			if (c == -1)
E 137
E 133
				goto endcase;
I 145
			if (c == ' ' || c == '\t') {
D 159
				putc(c, &tp->t_rawq);
E 159
I 159
				(void)putc(c, &tp->t_rawq);
E 159
				goto endcase;
			}
E 145
D 133
		} while (c != ' ' && c != '\t' && CTYPE(c) == ctype);
		(void) putc(c, &tp->t_rawq);
		goto endcase;
E 133
I 133
D 137
			}
E 137
I 137
D 140
			ctype = CTYPE(c);
E 140
I 140
			ctype = ISALPHA(c);
E 140
E 137
			/*
D 137
			 * erase rest of token
E 137
I 137
			 * erase rest of word
E 137
			 */
D 137
			ctype = CTYPE(c);
E 137
			do {
				ttyrub(c, tp);
				c = unputc(&tp->t_rawq);
				if (c == -1)
					goto endcase;
D 137
			} while (c != ' ' && c != '\t' && CTYPE(c) == ctype);
E 137
I 137
D 157
			} while (c != ' ' && c != '\t' && 
D 140
				(alt == 0 || CTYPE(c) == ctype));
E 140
I 140
				(alt == 0 || ISALPHA(c) == ctype));
E 140
E 137
			(void) putc(c, &tp->t_rawq);
E 157
I 157
			} while (c != ' ' && c != '\t' &&
			    (alt == 0 || ISALPHA(c) == ctype));
			(void)putc(c, &tp->t_rawq);
E 157
			goto endcase;
E 133
D 140
#undef CTYPE
E 140
I 133
		}
		/*
		 * reprint line (^R)
		 */
		if (CCEQ(cc[VREPRINT], c)) {
			ttyretype(tp);
			goto endcase;
		}
		/*
		 * ^T - kernel info and generate SIGINFO
		 */
		if (CCEQ(cc[VSTATUS], c)) {
D 146
			pgsignal(tp->t_pgrp, SIGINFO, 1);
E 146
I 146
D 157
			if (lflag&ISIG)
E 157
I 157
			if (ISSET(lflag, ISIG))
E 157
				pgsignal(tp->t_pgrp, SIGINFO, 1);
E 146
D 157
			if ((lflag&NOKERNINFO) == 0)
E 157
I 157
			if (!ISSET(lflag, NOKERNINFO))
E 157
				ttyinfo(tp);
			goto endcase;
		}
E 133
E 112
E 110
I 110
			c = unputc(&tp->t_rawq);
		} while (c != ' ' && c != '\t');
		(void) putc(c, &tp->t_rawq);
		goto endcase;
E 110
	}
I 110
	/*
	 * reprint line (^R)
	 */
	if (CCEQ(cc[VREPRINT], c)) {
		ttyretype(tp);
		goto endcase;
	}
E 110
D 112

E 112
	/*
I 112
D 133
	 * reprint line (^R)
	 */
	if (CCEQ(cc[VREPRINT], c)) {
		ttyretype(tp);
I 124
		goto endcase;
	}
I 132
	/*
	 * ^T - kernel info and generate SIGINFO
	 */
E 132
D 131
	if (CCEQ(cc[VINFO], c)) {
E 131
I 131
	if (CCEQ(cc[VSTATUS], c)) {
E 131
D 127
		pgsignal(tp->t_pgrp, SIGINFO);
E 127
I 127
		pgsignal(tp->t_pgrp, SIGINFO, 1);
E 127
		if ((lflag&NOKERNINFO) == 0)
			ttyinfo(tp);
E 124
		goto endcase;
	}
I 127
    }
E 127
	/*
E 133
E 112
	 * Check for input buffer overflow
	 */
D 61
	if (tp->t_rawq.c_cc+tp->t_canq.c_cc >= TTYHOG)
E 61
I 61
D 137
	if (tp->t_rawq.c_cc+tp->t_canq.c_cc >= TTYHOG) {
E 137
I 137
	if (tp->t_rawq.c_cc + tp->t_canq.c_cc >= TTYHOG) {
E 137
D 110
D 112
		if (tp->t_line == NTTYDISC)
D 108
			(void) ttyoutput(CTRL(g), tp);
E 108
I 108
			(void) ttyoutput(CTRL('g'), tp);
E 112
I 112
D 157
		if (iflag&IMAXBEL) {
E 157
I 157
		if (ISSET(iflag, IMAXBEL)) {
E 157
			if (tp->t_outq.c_cc < tp->t_hiwat)
D 157
				(void) ttyoutput(CTRL('g'), tp);
E 157
I 157
				(void)ttyoutput(CTRL('g'), tp);
E 157
		} else
			ttyflush(tp, FREAD | FWRITE);
E 112
E 110
I 110
		if (iflag&IMAXBEL) {
			if (tp->t_outq.c_cc < TTHIWAT(tp))
				(void) ttyoutput(CTRL('g'), tp);
		} else
			ttyflush(tp, FREAD | FWRITE);
E 110
E 108
E 61
		goto endcase;
I 61
	}
E 61
D 112

E 112
	/*
	 * Put data char in q for user and
	 * wakeup on seeing a line delimiter.
	 */
	if (putc(c, &tp->t_rawq) >= 0) {
I 137
D 157
		if ((lflag&ICANON) == 0) {
E 157
I 157
		if (!ISSET(lflag, ICANON)) {
E 157
			ttwakeup(tp);
			ttyecho(c, tp);
			goto endcase;
		}
E 137
D 61
		if (tp->t_rawq.c_cc + tp->t_canq.c_cc == TTYHOG
		    && tp->t_line == NTTYDISC)
			(void) ttyoutput(CTRL(g), tp);
E 61
D 110
D 112
		if (ttbreakc(c, tp)) {
E 112
I 112
D 157
		if (ttbreakc(c)) {
E 157
I 157
		if (TTBREAKC(c)) {
E 157
E 112
E 110
I 110
		if (ttbreakc(c)) {
E 110
			tp->t_rocount = 0;
			catq(&tp->t_rawq, &tp->t_canq);
E 56
			ttwakeup(tp);
I 56
		} else if (tp->t_rocount++ == 0)
D 158
			tp->t_rocol = tp->t_col;
E 158
I 158
			tp->t_rocol = tp->t_column;
E 158
D 112
		tp->t_state &= ~TS_QUOT;
D 110
		if (c == '\\')
			tp->t_state |= TS_QUOT;
E 112
E 110
I 110
		if (CCEQ(cc[VQUOTE], c) && (iflag&ISTRIP))
			tp->t_state |= TS_QUOT;	/* '\' escape */
E 110
D 157
		if (tp->t_state&TS_ERASE) {
E 157
I 157
		if (ISSET(tp->t_state, TS_ERASE)) {
E 157
I 112
			/*
			 * end of prterase \.../
			 */
E 112
I 110
			/*
			 * end of prterase \.../
			 */
E 110
D 157
			tp->t_state &= ~TS_ERASE;
			(void) ttyoutput('/', tp);
E 157
I 157
			CLR(tp->t_state, TS_ERASE);
			(void)ttyoutput('/', tp);
E 157
		}
D 158
		i = tp->t_col;
E 158
I 158
		i = tp->t_column;
E 158
E 56
		ttyecho(c, tp);
I 56
D 89
		if (c == tp->t_eofc && tp->t_flags&ECHO) {
E 89
I 89
D 110
D 112
		if (c == tp->t_eofc && t_flags&ECHO) {
E 112
I 112
D 157
		if (CCEQ(cc[VEOF], c) && lflag&ECHO) {
E 157
I 157
		if (CCEQ(cc[VEOF], c) && ISSET(lflag, ECHO)) {
E 157
			/*
			 * Place the cursor over the '^' of the ^D.
			 */
E 112
E 110
I 110
		if (CCEQ(cc[VEOF], c) && lflag&ECHO) {
			/*
			 * Place the cursor over the '^' of the ^D.
			 */
E 110
E 89
D 151
			i = MIN(2, tp->t_col - i);
E 151
I 151
D 158
			i = min(2, tp->t_col - i);
E 158
I 158
			i = min(2, tp->t_column - i);
E 158
E 151
			while (i > 0) {
D 157
				(void) ttyoutput('\b', tp);
E 157
I 157
				(void)ttyoutput('\b', tp);
E 157
				i--;
			}
		}
E 56
	}
D 56
out:
	if (tp->t_local & LDECCTQ && tp->t_state & TS_TTSTOP &&
	    tun.t_startc != tun.t_stopc)
E 56
I 56
D 87

E 87
endcase:
	/*
D 110
D 112
	 * If DEC-style start/stop is enabled don't restart
	 * output until seeing the start character.
E 112
I 112
	 * IXANY means allow any character to restart output.
E 112
E 110
I 110
	 * IXANY means allow any character to restart output.
E 110
	 */
D 89
	if (tp->t_flags&DECCTQ && tp->t_state&TS_TTSTOP &&
E 89
I 89
D 110
D 112
	if (t_flags&DECCTQ && tp->t_state&TS_TTSTOP &&
E 89
	    tp->t_startc != tp->t_stopc)
E 112
I 112
D 120
	if ((tp->t_state&TS_TTSTOP) && !(iflag&IXANY) 
	    && cc[VSTART] != cc[VSTOP])
E 120
I 120
D 157
	if ((tp->t_state&TS_TTSTOP) && (iflag&IXANY) == 0 && 
	    cc[VSTART] != cc[VSTOP])
E 120
E 112
E 110
I 110
	if (tp->t_state&TS_TTSTOP && (iflag&IXANY == 0) 
	    && cc[VSTART] != cc[VSTOP])
E 110
E 56
		return;
E 157
I 157
	if (ISSET(tp->t_state, TS_TTSTOP) &&
	    !ISSET(iflag, IXANY) && cc[VSTART] != cc[VSTOP])
		return (0);
E 157
I 110
	
E 110
I 56
D 87

E 87
restartoutput:
E 56
D 157
	tp->t_state &= ~TS_TTSTOP;
D 56
	tp->t_local &= ~LFLUSHO;
E 56
I 56
D 110
D 112
	tp->t_flags &= ~FLUSHO;
E 112
I 112
	tp->t_lflag &= ~FLUSHO;
E 157
I 157
	CLR(tp->t_lflag, FLUSHO);
	CLR(tp->t_state, TS_TTSTOP);
E 157
E 112
E 110
I 110
	tp->t_lflag &= ~FLUSHO;
E 110
D 87

E 87
startoutput:
E 56
D 157
	ttstart(tp);
E 157
I 157
	return (ttstart(tp));
E 157
}

/*
D 56
 * put character on TTY output queue, adding delays,
E 56
I 56
D 140
 * Put character on TTY output queue, adding delays,
E 56
 * expanding tabs, and handling the CR/NL bit.
D 56
 * It is called both from the top half for output, and from
 * interrupt level for echoing.
E 56
I 56
 * This is called both from the top half for output,
 * and from interrupt level for echoing.
E 56
 * The arguments are the character and the tty structure.
 * Returns < 0 if putc succeeds, otherwise returns char to resend
E 140
I 140
 * Output a single character on a tty, doing output processing
 * as needed (expanding tabs, newline processing, etc.).
D 157
 * Returns < 0 if putc succeeds, otherwise returns char to resend.
E 157
I 157
 * Returns < 0 if succeeds, otherwise returns char to resend.
E 157
E 140
 * Must be recursive.
 */
I 157
int
E 157
ttyoutput(c, tp)
D 157
	register c;
E 157
I 157
	register int c;
E 157
	register struct tty *tp;
{
D 133
	register char *colp;
E 133
I 133
D 140
	register short *colp;
E 133
	register ctype;
E 140
I 140
D 157
	register int col;
E 140
D 112

D 56
	if (tp->t_flags&RAW || tp->t_local&LLITOUT) {
		if (tp->t_local&LFLUSHO)
E 56
I 56
D 110
	if (tp->t_flags & (RAW|LITOUT)) {
		if (tp->t_flags&FLUSHO)
E 112
I 112
	register long oflag = tp->t_oflag;
	
D 120
	if (!(oflag&OPOST)) {
E 120
I 120
	if ((oflag&OPOST) == 0) {
E 120
		if (tp->t_lflag&FLUSHO) 
E 157
I 157
	register long oflag;
D 164
	register int col, s;
E 164
I 164
	register int notout, col, s;
E 164

	oflag = tp->t_oflag;
	if (!ISSET(oflag, OPOST)) {
		if (ISSET(tp->t_lflag, FLUSHO))
E 157
E 112
E 110
I 110
	if (!(tp->t_oflag&OPOST)) {
		if (tp->t_lflag&FLUSHO) 
E 110
E 56
			return (-1);
		if (putc(c, &tp->t_outq))
D 45
			return(c);
E 45
I 45
			return (c);
E 45
		tk_nout++;
I 112
		tp->t_outcc++;
E 112
		return (-1);
	}
I 56
D 110
D 112

E 112
I 112
D 157
	c &= TTY_CHARMASK;
E 157
E 112
E 110
I 110
	c &= 0377;
E 110
E 56
	/*
D 56
	 * Ignore EOT in normal mode to avoid hanging up
	 * certain terminals.
E 56
I 56
D 110
D 112
	 * Ignore EOT in normal mode to avoid
	 * hanging up certain terminals.
E 56
	 */
	c &= 0177;
D 56
	if (c==CEOT && (tp->t_flags&CBREAK)==0)
E 56
I 56
	if (c == CEOT && (tp->t_flags&CBREAK) == 0)
E 56
		return (-1);
	/*
E 112
E 110
D 140
	 * Turn tabs to spaces as required
I 127
	 *
E 140
I 140
D 157
	 * Do tab expansion if OXTABS is set.
E 140
	 * Special case if we have external processing, we don't
	 * do the tab expansion because we'll probably get it
	 * wrong.  If tab expansion needs to be done, let it
	 * happen externally.
E 157
I 157
	 * Do tab expansion if OXTABS is set.  Special case if we external
	 * processing, we don't do the tab expansion because we'll probably
	 * get it wrong.  If tab expansion needs to be done, let it happen
	 * externally.
E 157
E 127
	 */
D 56
	if (c=='\t' && (tp->t_flags&TBDELAY)==XTABS) {
E 56
I 56
D 110
D 112
	if (c == '\t' && (tp->t_flags&TBDELAY) == XTABS) {
E 112
I 112
D 127
	if (c == '\t' && oflag&OXTABS ) {
E 127
I 127
D 137
	if ((tp->t_lflag&EXTPROC) == 0 &&
	    c == '\t' && oflag&OXTABS ) {
E 137
I 137
D 157
	if (c == '\t' && oflag&OXTABS && (tp->t_lflag&EXTPROC) == 0) {
E 137
E 127
E 112
E 110
I 110
	if (c == '\t' && tp->t_oflag&OXTABS ) {
E 110
E 56
		register int s;

		c = 8 - (tp->t_col&7);
D 56
		if ((tp->t_local&LFLUSHO) == 0) {
E 56
I 56
D 110
D 112
		if ((tp->t_flags&FLUSHO) == 0) {
E 112
I 112
		if ((tp->t_lflag&FLUSHO) == 0) {
E 112
E 110
I 110
		if ((tp->t_lflag&FLUSHO) == 0) {
E 110
E 56
D 84
			s = spl5();		/* don't interrupt tabs */
E 84
I 84
			s = spltty();		/* don't interrupt tabs */
E 157
I 157
D 159
	c &= TTY_CHARMASK;
E 159
I 159
	CLR(c, ~TTY_CHARMASK);
E 159
	if (c == '\t' &&
	    ISSET(oflag, OXTABS) && !ISSET(tp->t_lflag, EXTPROC)) {
D 158
		c = 8 - (tp->t_col & 7);
E 158
I 158
		c = 8 - (tp->t_column & 7);
E 158
D 164
		if (!ISSET(tp->t_lflag, FLUSHO)) {
E 164
I 164
		if (ISSET(tp->t_lflag, FLUSHO)) {
			notout = 0;
		} else {
E 164
			s = spltty();		/* Don't interrupt tabs. */
E 157
E 84
D 164
			c -= b_to_q("        ", c, &tp->t_outq);
E 164
I 164
			notout = b_to_q("        ", c, &tp->t_outq);
			c -= notout;
E 164
			tk_nout += c;
I 112
			tp->t_outcc += c;
E 112
			splx(s);
		}
D 158
		tp->t_col += c;
E 158
I 158
		tp->t_column += c;
E 158
D 164
		return (c ? -1 : '\t');
E 164
I 164
		return (notout ? '\t' : -1);
E 164
	}
I 112
D 157
	if (c == CEOT && oflag&ONOEOT)
E 157
I 157
	if (c == CEOT && ISSET(oflag, ONOEOT))
E 157
D 137
		return(-1);
E 137
I 137
		return (-1);
E 137
E 112
D 159
	tk_nout++;
I 112
	tp->t_outcc++;
E 159
I 159

E 159
E 112
I 110
#ifdef notdef
E 110
	/*
D 112
	 * for upper-case-only terminals,
	 * generate escapes.
	 */
	if (tp->t_flags&LCASE) {
		colp = "({)}!|^~'`";
D 45
		while(*colp++)
			if(c == *colp++) {
E 45
I 45
		while (*colp++)
			if (c == *colp++) {
E 45
				if (ttyoutput('\\', tp) >= 0)
					return (c);
				c = colp[-2];
				break;
			}
D 56
		if ('A'<=c && c<='Z') {
E 56
I 56
		if ('A' <= c && c <= 'Z') {
E 56
			if (ttyoutput('\\', tp) >= 0)
				return (c);
D 56
		} else if ('a'<=c && c<='z')
E 56
I 56
		} else if ('a' <= c && c <= 'z')
E 56
			c += 'A' - 'a';
	}
I 110
#endif
E 110
I 56

E 56
	/*
E 112
D 140
	 * turn <nl> to <cr><lf> if desired.
E 140
I 140
	 * Newline translation: if ONLCR is set,
	 * translate newline into "\r\n".
E 140
	 */
D 56
	if (c=='\n' && tp->t_flags&CRMOD)
E 56
I 56
D 110
D 112
	if (c == '\n' && tp->t_flags&CRMOD)
E 56
		if (ttyoutput('\r', tp) >= 0)
E 110
I 110
	if (c == '\n' && (tp->t_oflag&ONLCR) && ttyoutput('\r', tp) >= 0)
E 110
			return (c);
I 110
#ifdef notdef
E 110
D 56
	if (c=='~' && tp->t_local&LTILDE)
E 56
I 56
	if (c == '~' && tp->t_flags&TILDE)
E 56
		c = '`';
D 56
	if ((tp->t_local&LFLUSHO) == 0 && putc(c, &tp->t_outq))
E 56
I 56
D 110
	if ((tp->t_flags&FLUSHO) == 0 && putc(c, &tp->t_outq))
E 112
I 112
D 157
	if (c == '\n' && (tp->t_oflag&ONLCR) && ttyoutput('\r', tp) >= 0)
E 157
I 157
D 159
	if (c == '\n' &&
	    ISSET(tp->t_oflag, ONLCR) && ttyoutput('\r', tp) >= 0)
E 157
E 112
E 110
I 110
#endif
	if ((tp->t_lflag&FLUSHO) == 0 && putc(c, &tp->t_outq))
E 110
E 56
		return (c);
E 159
I 159
	if (c == '\n' && ISSET(tp->t_oflag, ONLCR)) {
		tk_nout++;
		tp->t_outcc++;
		if (putc('\r', &tp->t_outq))
			return (c);
	}
	tk_nout++;
	tp->t_outcc++;
E 159
I 112
D 157
	if ((tp->t_lflag&FLUSHO) == 0 && putc(c, &tp->t_outq))
E 157
I 157
	if (!ISSET(tp->t_lflag, FLUSHO) && putc(c, &tp->t_outq))
E 157
		return (c);
E 112
D 137
	/*
	 * Calculate delays.
	 * The numbers here represent clock ticks
	 * and are not necessarily optimal for all terminals.
D 112
	 * The delays are indicated by characters above 0200.
	 * In raw mode there are no delays and the
	 * transmission path is 8 bits wide.
E 112
I 56
	 *
	 * SHOULD JUST ALLOW USER TO SPECIFY DELAYS
I 112
	 *
	 * (actually, should THROW AWAY terminals which need delays)
E 112
E 56
	 */
E 137
I 137

E 137
D 140
	colp = &tp->t_col;
	ctype = partab[c];
D 137
	c = 0;
E 137
	switch (ctype&077) {
E 140
I 140
D 158
	col = tp->t_col;
E 158
I 158
	col = tp->t_column;
E 158
	switch (CCLASS(c)) {
E 140
D 157

	case ORDINARY:
D 140
		(*colp)++;
E 140
I 140
		col++;
E 140

	case CONTROL:
		break;

E 157
	case BACKSPACE:
D 140
		if (*colp)
			(*colp)--;
E 140
I 140
		if (col > 0)
D 157
			col--;
E 157
I 157
			--col;
E 157
E 140
		break;
D 157

E 157
I 157
	case CONTROL:
		break;
E 157
I 70
D 137
	/*
	 * This macro is close enough to the correct thing;
	 * it should be replaced by real user settable delays
	 * in any event...
	 */
#define	mstohz(ms)	(((ms) * hz) >> 10)
E 137
E 70
	case NEWLINE:
I 157
	case RETURN:
E 157
D 137
		ctype = (tp->t_flags >> 8) & 03;
D 45
		if(ctype == 1) { /* tty 37 */
E 45
I 45
		if (ctype == 1) { /* tty 37 */
E 45
D 63
			if (*colp)
E 63
I 63
D 98
			if (*colp > 0)
E 63
D 71
				c = max(((unsigned)*colp>>4) + 3, (unsigned)6);
E 71
I 71
				c = max((((unsigned)*colp) >> 4) + 3,
				    (unsigned)6);
E 98
I 98
			if (*colp > 0) {
				c = (((unsigned)*colp) >> 4) + 3;
				if ((unsigned)c > 6)
					c = 6;
			}
E 98
E 71
D 56
		} else
D 45
		if(ctype == 2) { /* vt05 */
E 45
I 45
		if (ctype == 2) { /* vt05 */
E 56
I 56
		} else if (ctype == 2) /* vt05 */
E 56
E 45
D 70
			c = 6;
E 70
I 70
			c = mstohz(100);
E 137
E 70
D 56
		}
E 56
D 140
		*colp = 0;
E 140
I 140
		col = 0;
E 140
		break;
D 157

E 157
I 157
	case ORDINARY:
		++col;
		break;
E 157
	case TAB:
D 137
		ctype = (tp->t_flags >> 10) & 03;
D 45
		if(ctype == 1) { /* tty 37 */
E 45
I 45
		if (ctype == 1) { /* tty 37 */
E 45
			c = 1 - (*colp | ~07);
D 45
			if(c < 5)
E 45
I 45
			if (c < 5)
E 45
				c = 0;
		}
E 137
D 140
		*colp |= 07;
		(*colp)++;
E 140
I 140
D 157
		col = (col + 8) &~ 0x7;
E 157
I 157
		col = (col + 8) & ~7;
E 157
E 140
		break;
D 157

D 137
	case VTAB:
D 45
		if(tp->t_flags & VTDELAY) /* tty 37 */
E 45
I 45
D 56
		if (tp->t_flags & VTDELAY) /* tty 37 */
E 56
I 56
		if (tp->t_flags&VTDELAY) /* tty 37 */
E 56
E 45
			c = 0177;
		break;

E 137
	case RETURN:
D 137
		ctype = (tp->t_flags >> 12) & 03;
D 45
		if(ctype == 1) { /* tn 300 */
E 45
I 45
D 56
		if (ctype == 1) { /* tn 300 */
E 56
I 56
		if (ctype == 1) /* tn 300 */
E 56
E 45
D 70
			c = 5;
E 70
I 70
			c = mstohz(83);
E 70
D 45
		} else if(ctype == 2) { /* ti 700 */
E 45
I 45
D 56
		} else if (ctype == 2) { /* ti 700 */
E 56
I 56
		else if (ctype == 2) /* ti 700 */
E 56
E 45
D 70
			c = 10;
E 70
I 70
			c = mstohz(166);
E 70
D 45
		} else if(ctype == 3) { /* concept 100 */
E 45
I 45
D 56
		} else if (ctype == 3) { /* concept 100 */
E 56
I 56
		else if (ctype == 3) { /* concept 100 */
E 56
E 45
			int i;
I 56

E 56
			if ((i = *colp) >= 0)
D 56
				for (; i<9; i++)
E 56
I 56
				for (; i < 9; i++)
E 56
					(void) putc(0177, &tp->t_outq);
		}
E 137
D 140
		*colp = 0;
E 140
I 140
		col = 0;
E 157
E 140
	}
I 140
D 158
	tp->t_col = col;
E 158
I 158
	tp->t_column = col;
E 158
E 140
D 45
	if(c && (tp->t_local&LFLUSHO) == 0)
E 45
I 45
D 56
	if (c && (tp->t_local&LFLUSHO) == 0)
E 56
I 56
D 110
D 112
	if (c && (tp->t_flags&FLUSHO) == 0)
E 110
I 110
	if (c && (tp->t_lflag&FLUSHO) == 0)
E 110
E 56
E 45
		(void) putc(c|0200, &tp->t_outq);
E 112
I 112
D 137
	if (c && (tp->t_lflag&FLUSHO) == 0)
		(void) putc(c|TTY_QUOTE, &tp->t_outq);
E 137
E 112
	return (-1);
}
I 70
D 137
#undef mstohz
E 137
E 70

/*
I 157
D 159
 * Common code for ioctls on all tty devices.  Called after line-discipline
 * specific ioctl has been called to do discipline-specific functions and/or
 * reject any of these ioctl commands.
E 159
I 159
 * Ioctls for all tty devices.  Called after line-discipline specific ioctl
 * has been called to do discipline-specific functions and/or reject any
 * of these ioctl commands.
E 159
 */
/* ARGSUSED */
int
D 159
ttioctl(tp, com, data, flag)
E 159
I 159
ttioctl(tp, cmd, data, flag)
E 159
	register struct tty *tp;
D 159
	int com, flag;
E 159
I 159
D 168
	int cmd, flag;
E 168
I 168
	u_long cmd;
E 168
E 159
	void *data;
I 168
	int flag;
E 168
{
	extern struct tty *constty;	/* Temporary virtual console. */
D 159
	extern int nldisp;
E 159
I 159
	extern int nlinesw;
E 159
	register struct proc *p;
	int s, error;

	p = curproc;			/* XXX */

	/* If the ioctl involves modification, hang if in the background. */
D 159
	switch (com) {
E 159
I 159
	switch (cmd) {
E 159
	case  TIOCFLUSH:
	case  TIOCSETA:
	case  TIOCSETD:
	case  TIOCSETAF:
	case  TIOCSETAW:
#ifdef notdef
	case  TIOCSPGRP:
#endif
	case  TIOCSTI:
	case  TIOCSWINSZ:
#if defined(COMPAT_43) || defined(COMPAT_SUNOS)
	case  TIOCLBIC:
	case  TIOCLBIS:
	case  TIOCLSET:
	case  TIOCSETC:
	case OTIOCSETD:
	case  TIOCSETN:
	case  TIOCSETP:
	case  TIOCSLTC:
#endif
		while (isbackground(curproc, tp) &&
D 159
		    p->p_pgrp->pg_jobc && (p->p_flag & SPPWAIT) == 0 &&
E 159
I 159
		    p->p_pgrp->pg_jobc && (p->p_flag & P_PPWAIT) == 0 &&
E 159
		    (p->p_sigignore & sigmask(SIGTTOU)) == 0 &&
		    (p->p_sigmask & sigmask(SIGTTOU)) == 0) {
			pgsignal(p->p_pgrp, SIGTTOU, 1);
			if (error = ttysleep(tp,
			    &lbolt, TTOPRI | PCATCH, ttybg, 0))
				return (error);
		}
		break;
	}

D 159
	switch (com) {			/* Process the ioctl. */
E 159
I 159
	switch (cmd) {			/* Process the ioctl. */
E 159
	case FIOASYNC:			/* set/clear async i/o */
		s = spltty();
		if (*(int *)data)
			SET(tp->t_state, TS_ASYNC);
		else
			CLR(tp->t_state, TS_ASYNC);
		splx(s);
		break;
	case FIONBIO:			/* set/clear non-blocking i/o */
		break;			/* XXX: delete. */
	case FIONREAD:			/* get # bytes to read */
		*(int *)data = ttnread(tp);
		break;
	case TIOCEXCL:			/* set exclusive use of tty */
		s = spltty();
		SET(tp->t_state, TS_XCLUDE);
		splx(s);
		break;
	case TIOCFLUSH: {		/* flush buffers */
		register int flags = *(int *)data;

		if (flags == 0)
			flags = FREAD | FWRITE;
		else
			flags &= FREAD | FWRITE;
		ttyflush(tp, flags);
		break;
	}
	case TIOCCONS:			/* become virtual console */
		if (*(int *)data) {
			if (constty && constty != tp &&
			    ISSET(constty->t_state, TS_CARR_ON | TS_ISOPEN) ==
			    (TS_CARR_ON | TS_ISOPEN))
				return (EBUSY);
#ifndef	UCONSOLE
			if (error = suser(p->p_ucred, &p->p_acflag))
				return (error);
#endif
			constty = tp;
		} else if (tp == constty)
			constty = NULL;
		break;
	case TIOCDRAIN:			/* wait till output drained */
		if (error = ttywait(tp))
			return (error);
		break;
	case TIOCGETA: {		/* get termios struct */
		struct termios *t = (struct termios *)data;

		bcopy(&tp->t_termios, t, sizeof(struct termios));
		break;
	}
	case TIOCGETD:			/* get line discipline */
		*(int *)data = tp->t_line;
		break;
	case TIOCGWINSZ:		/* get window size */
		*(struct winsize *)data = tp->t_winsize;
		break;
	case TIOCGPGRP:			/* get pgrp of tty */
		if (!isctty(p, tp))
			return (ENOTTY);
		*(int *)data = tp->t_pgrp ? tp->t_pgrp->pg_id : NO_PID;
		break;
#ifdef TIOCHPCL
	case TIOCHPCL:			/* hang up on last close */
		s = spltty();
D 159
		tp->t_cflag |= HUPCL;
E 159
I 159
		SET(tp->t_cflag, HUPCL);
E 159
		splx(s);
		break;
#endif
	case TIOCNXCL:			/* reset exclusive use of tty */
		s = spltty();
		CLR(tp->t_state, TS_XCLUDE);
		splx(s);
		break;
	case TIOCOUTQ:			/* output queue size */
		*(int *)data = tp->t_outq.c_cc;
		break;
	case TIOCSETA:			/* set termios struct */
	case TIOCSETAW:			/* drain output, set */
	case TIOCSETAF: {		/* drn out, fls in, set */
		register struct termios *t = (struct termios *)data;

		s = spltty();
D 159
		if (com == TIOCSETAW || com == TIOCSETAF) {
E 159
I 159
		if (cmd == TIOCSETAW || cmd == TIOCSETAF) {
E 159
			if (error = ttywait(tp)) {
				splx(s);
				return (error);
			}
D 159
			if (com == TIOCSETAF)
E 159
I 159
			if (cmd == TIOCSETAF)
E 159
				ttyflush(tp, FREAD);
		}
		if (!ISSET(t->c_cflag, CIGNORE)) {
			/*
			 * Set device hardware.
			 */
			if (tp->t_param && (error = (*tp->t_param)(tp, t))) {
				splx(s);
				return (error);
			} else {
				if (!ISSET(tp->t_state, TS_CARR_ON) &&
				    ISSET(tp->t_cflag, CLOCAL) &&
				    !ISSET(t->c_cflag, CLOCAL)) {
					CLR(tp->t_state, TS_ISOPEN);
					SET(tp->t_state, TS_WOPEN);
					ttwakeup(tp);
				}
				tp->t_cflag = t->c_cflag;
				tp->t_ispeed = t->c_ispeed;
				tp->t_ospeed = t->c_ospeed;
			}
			ttsetwater(tp);
		}
D 159
		if (com != TIOCSETAF) {
E 159
I 159
		if (cmd != TIOCSETAF) {
E 159
			if (ISSET(t->c_lflag, ICANON) !=
			    ISSET(tp->t_lflag, ICANON))
				if (ISSET(t->c_lflag, ICANON)) {
D 159
					tp->t_lflag |= PENDIN;
E 159
I 159
					SET(tp->t_lflag, PENDIN);
E 159
					ttwakeup(tp);
				} else {
					struct clist tq;

					catq(&tp->t_rawq, &tp->t_canq);
					tq = tp->t_rawq;
					tp->t_rawq = tp->t_canq;
					tp->t_canq = tq;
I 161
					CLR(tp->t_lflag, PENDIN);
E 161
				}
		}
		tp->t_iflag = t->c_iflag;
		tp->t_oflag = t->c_oflag;
		/*
		 * Make the EXTPROC bit read only.
		 */
		if (ISSET(tp->t_lflag, EXTPROC))
			SET(t->c_lflag, EXTPROC);
		else
			CLR(t->c_lflag, EXTPROC);
D 161
		tp->t_lflag = t->c_lflag;
E 161
I 161
		tp->t_lflag = t->c_lflag | ISSET(tp->t_lflag, PENDIN);
E 161
		bcopy(t->c_cc, tp->t_cc, sizeof(t->c_cc));
		splx(s);
		break;
	}
	case TIOCSETD: {		/* set line discipline */
		register int t = *(int *)data;
		dev_t device = tp->t_dev;

D 159
		if ((u_int)t >= nldisp)
E 159
I 159
		if ((u_int)t >= nlinesw)
E 159
			return (ENXIO);
		if (t != tp->t_line) {
			s = spltty();
			(*linesw[tp->t_line].l_close)(tp, flag);
			error = (*linesw[t].l_open)(device, tp);
			if (error) {
				(void)(*linesw[tp->t_line].l_open)(device, tp);
				splx(s);
				return (error);
			}
			tp->t_line = t;
			splx(s);
		}
		break;
	}
	case TIOCSTART:			/* start output, like ^Q */
		s = spltty();
		if (ISSET(tp->t_state, TS_TTSTOP) ||
		    ISSET(tp->t_lflag, FLUSHO)) {
			CLR(tp->t_lflag, FLUSHO);
			CLR(tp->t_state, TS_TTSTOP);
			ttstart(tp);
		}
		splx(s);
		break;
	case TIOCSTI:			/* simulate terminal input */
		if (p->p_ucred->cr_uid && (flag & FREAD) == 0)
			return (EPERM);
		if (p->p_ucred->cr_uid && !isctty(p, tp))
			return (EACCES);
		(*linesw[tp->t_line].l_rint)(*(u_char *)data, tp);
		break;
	case TIOCSTOP:			/* stop output, like ^S */
		s = spltty();
		if (!ISSET(tp->t_state, TS_TTSTOP)) {
			SET(tp->t_state, TS_TTSTOP);
#ifdef sun4c				/* XXX */
			(*tp->t_stop)(tp, 0);
#else
			(*cdevsw[major(tp->t_dev)].d_stop)(tp, 0);
#endif
		}
		splx(s);
		break;
	case TIOCSCTTY:			/* become controlling tty */
		/* Session ctty vnode pointer set in vnode layer. */
		if (!SESS_LEADER(p) ||
D 165
		    (p->p_session->s_ttyvp || tp->t_session) &&
		    (tp->t_session != p->p_session))
E 165
I 165
D 166
		    p->p_session->s_ttyvp ||
		    (tp->t_session && tp->t_session != p->p_session))
E 166
I 166
		    (p->p_session->s_ttyvp || tp->t_session) &&
		    (tp->t_session != p->p_session))
E 166
E 165
			return (EPERM);
		tp->t_session = p->p_session;
		tp->t_pgrp = p->p_pgrp;
		p->p_session->s_ttyp = tp;
D 159
		p->p_flag |= SCTTY;
E 159
I 159
		p->p_flag |= P_CONTROLT;
E 159
		break;
	case TIOCSPGRP: {		/* set pgrp of tty */
		register struct pgrp *pgrp = pgfind(*(int *)data);

		if (!isctty(p, tp))
			return (ENOTTY);
		else if (pgrp == NULL || pgrp->pg_session != p->p_session)
			return (EPERM);
		tp->t_pgrp = pgrp;
		break;
	}
	case TIOCSWINSZ:		/* set window size */
		if (bcmp((caddr_t)&tp->t_winsize, data,
		    sizeof (struct winsize))) {
			tp->t_winsize = *(struct winsize *)data;
			pgsignal(tp->t_pgrp, SIGWINCH, 1);
		}
		break;
	default:
#if defined(COMPAT_43) || defined(COMPAT_SUNOS)
D 159
		return (ttcompat(tp, com, data, flag));
E 159
I 159
		return (ttcompat(tp, cmd, data, flag));
E 159
#else
		return (-1);
#endif
	}
	return (0);
}

int
ttselect(device, rw, p)
	dev_t device;
	int rw;
	struct proc *p;
{
	register struct tty *tp;
	int nread, s;

	tp = &cdevsw[major(device)].d_ttys[minor(device)];

	s = spltty();
	switch (rw) {
	case FREAD:
		nread = ttnread(tp);
		if (nread > 0 || !ISSET(tp->t_cflag, CLOCAL) &&
		    !ISSET(tp->t_state, TS_CARR_ON))
			goto win;
		selrecord(p, &tp->t_rsel);
		break;
	case FWRITE:
		if (tp->t_outq.c_cc <= tp->t_lowat) {
win:			splx(s);
			return (1);
		}
		selrecord(p, &tp->t_wsel);
		break;
	}
	splx(s);
	return (0);
}

static int
ttnread(tp)
	struct tty *tp;
{
	int nread;

	if (ISSET(tp->t_lflag, PENDIN))
		ttypend(tp);
	nread = tp->t_canq.c_cc;
	if (!ISSET(tp->t_lflag, ICANON))
		nread += tp->t_rawq.c_cc;
	return (nread);
}

/*
 * Wait for output to drain.
 */
int
ttywait(tp)
	register struct tty *tp;
{
	int error, s;

	error = 0;
	s = spltty();
	while ((tp->t_outq.c_cc || ISSET(tp->t_state, TS_BUSY)) &&
	    (ISSET(tp->t_state, TS_CARR_ON) || ISSET(tp->t_cflag, CLOCAL))
	    && tp->t_oproc) {
		(*tp->t_oproc)(tp);
		SET(tp->t_state, TS_ASLEEP);
		if (error = ttysleep(tp,
		    &tp->t_outq, TTOPRI | PCATCH, ttyout, 0))
			break;
	}
	splx(s);
	return (error);
}

/*
 * Flush if successfully wait.
 */
int
ttywflush(tp)
	struct tty *tp;
{
	int error;

	if ((error = ttywait(tp)) == 0)
		ttyflush(tp, FREAD);
	return (error);
}

/*
 * Flush tty read and/or write queues, notifying anyone waiting.
 */
void
ttyflush(tp, rw)
	register struct tty *tp;
	int rw;
{
	register int s;

	s = spltty();
	if (rw & FREAD) {
		FLUSHQ(&tp->t_canq);
		FLUSHQ(&tp->t_rawq);
		tp->t_rocount = 0;
		tp->t_rocol = 0;
		CLR(tp->t_state, TS_LOCAL);
		ttwakeup(tp);
	}
	if (rw & FWRITE) {
		CLR(tp->t_state, TS_TTSTOP);
#ifdef sun4c						/* XXX */
		(*tp->t_stop)(tp, rw);
#else
		(*cdevsw[major(tp->t_dev)].d_stop)(tp, rw);
#endif
		FLUSHQ(&tp->t_outq);
		wakeup((caddr_t)&tp->t_outq);
		selwakeup(&tp->t_wsel);
	}
	splx(s);
}

/*
 * Copy in the default termios characters.
 */
void
ttychars(tp)
	struct tty *tp;
{

	bcopy(ttydefchars, tp->t_cc, sizeof(ttydefchars));
}

/*
 * Send stop character on input overflow.
 */
static void
ttyblock(tp)
	register struct tty *tp;
{
	register int total;

	total = tp->t_rawq.c_cc + tp->t_canq.c_cc;
	if (tp->t_rawq.c_cc > TTYHOG) {
		ttyflush(tp, FREAD | FWRITE);
		CLR(tp->t_state, TS_TBLOCK);
	}
	/*
	 * Block further input iff: current input > threshold
	 * AND input is available to user program.
	 */
	if (total >= TTYHOG / 2 &&
	    !ISSET(tp->t_state, TS_TBLOCK) &&
	    !ISSET(tp->t_lflag, ICANON) || tp->t_canq.c_cc > 0 &&
	    tp->t_cc[VSTOP] != _POSIX_VDISABLE) {
		if (putc(tp->t_cc[VSTOP], &tp->t_outq) == 0) {
			SET(tp->t_state, TS_TBLOCK);
			ttstart(tp);
		}
	}
}

void
ttrstrt(tp_arg)
	void *tp_arg;
{
	struct tty *tp;
	int s;

#ifdef DIAGNOSTIC
	if (tp_arg == NULL)
		panic("ttrstrt");
#endif
	tp = tp_arg;
	s = spltty();

	CLR(tp->t_state, TS_TIMEOUT);
	ttstart(tp);

	splx(s);
}

int
ttstart(tp)
	struct tty *tp;
{

	if (tp->t_oproc != NULL)	/* XXX: Kludge for pty. */
		(*tp->t_oproc)(tp);
	return (0);
}

/*
 * "close" a line discipline
 */
int
ttylclose(tp, flag)
	struct tty *tp;
	int flag;
{

	if (flag & IO_NDELAY)
		ttyflush(tp, FREAD | FWRITE);
	else
		ttywflush(tp);
	return (0);
}

/*
 * Handle modem control transition on a tty.
 * Flag indicates new state of carrier.
 * Returns 0 if the line should be turned off, otherwise 1.
 */
int
ttymodem(tp, flag)
	register struct tty *tp;
	int flag;
{

	if (!ISSET(tp->t_state, TS_WOPEN) && ISSET(tp->t_cflag, MDMBUF)) {
		/*
		 * MDMBUF: do flow control according to carrier flag
		 */
		if (flag) {
			CLR(tp->t_state, TS_TTSTOP);
			ttstart(tp);
		} else if (!ISSET(tp->t_state, TS_TTSTOP)) {
			SET(tp->t_state, TS_TTSTOP);
#ifdef sun4c						/* XXX */
			(*tp->t_stop)(tp, 0);
#else
			(*cdevsw[major(tp->t_dev)].d_stop)(tp, 0);
#endif
		}
	} else if (flag == 0) {
		/*
		 * Lost carrier.
		 */
		CLR(tp->t_state, TS_CARR_ON);
		if (ISSET(tp->t_state, TS_ISOPEN) &&
		    !ISSET(tp->t_cflag, CLOCAL)) {
			if (tp->t_session && tp->t_session->s_leader)
				psignal(tp->t_session->s_leader, SIGHUP);
			ttyflush(tp, FREAD | FWRITE);
			return (0);
		}
	} else {
		/*
		 * Carrier now on.
		 */
		SET(tp->t_state, TS_CARR_ON);
		ttwakeup(tp);
	}
	return (1);
}

/*
 * Default modem control routine (for other line disciplines).
 * Return argument flag, to turn off device on carrier drop.
 */
int
nullmodem(tp, flag)
	register struct tty *tp;
	int flag;
{

	if (flag)
		SET(tp->t_state, TS_CARR_ON);
	else {
		CLR(tp->t_state, TS_CARR_ON);
		if (!ISSET(tp->t_cflag, CLOCAL)) {
			if (tp->t_session && tp->t_session->s_leader)
				psignal(tp->t_session->s_leader, SIGHUP);
			return (0);
		}
	}
	return (1);
}

/*
 * Reinput pending characters after state switch
 * call at spltty().
 */
void
ttypend(tp)
	register struct tty *tp;
{
	struct clist tq;
	register c;

	CLR(tp->t_lflag, PENDIN);
	SET(tp->t_state, TS_TYPEN);
	tq = tp->t_rawq;
	tp->t_rawq.c_cc = 0;
	tp->t_rawq.c_cf = tp->t_rawq.c_cl = 0;
	while ((c = getc(&tq)) >= 0)
		ttyinput(c, tp);
	CLR(tp->t_state, TS_TYPEN);
}

/*
E 157
D 140
 * Called from device's read routine after it has
 * calculated the tty-structure given as argument.
E 140
I 140
 * Process a read call on a tty device.
E 140
 */
I 157
int
E 157
D 47
ttread(tp)
E 47
I 47
D 115
ttread(tp, uio)
E 115
I 115
ttread(tp, uio, flag)
E 115
E 47
D 45
register struct tty *tp;
E 45
I 45
	register struct tty *tp;
I 47
	struct uio *uio;
I 147
	int flag;
E 147
E 47
E 45
{
	register struct clist *qp;
D 56
	register c, first;
I 50
	int error = 0;
E 56
I 56
D 110
D 112
	register c, t_flags;
E 112
I 112
	register int c;
D 123
	register long lflag = tp->t_lflag;
E 123
I 123
	register long lflag;
E 123
D 116
	register long iflag = tp->t_iflag;
E 116
	register u_char *cc = tp->t_cc;
I 137
	register struct proc *p = curproc;
E 137
E 112
E 110
I 110
	register int c, t_flags;
	register long lflag = tp->t_lflag;
	register long iflag = tp->t_iflag;
	register u_char *cc = tp->t_cc;
E 110
D 60
	int first, error = 0;
E 60
I 60
	int s, first, error = 0;
E 60
E 56
E 50

I 110

E 110
D 90
	if ((tp->t_state&TS_CARR_ON)==0)
D 45
		return(0);
E 45
I 45
D 50
		return (0);
E 50
I 50
		return (EIO);
E 90
E 50
E 45
D 157
loop:
I 123
	lflag = tp->t_lflag;
E 157
I 157
loop:	lflag = tp->t_lflag;
E 157
E 123
I 115
	s = spltty();
E 115
I 56
	/*
D 115
	 * Take any pending input first.
E 115
I 115
D 157
	 * take pending input first 
E 157
I 157
	 * take pending input first
E 157
E 115
	 */
E 56
D 60
	(void) spl5();
E 60
I 60
D 84
	s = spl5();
E 84
I 84
D 115
	s = spltty();
E 115
E 84
E 60
D 56
	if (tp->t_local&LPENDIN)
E 56
I 56
D 110
D 112
	if (tp->t_flags&PENDIN)
E 112
I 112
D 157
	if (lflag&PENDIN)
E 157
I 157
	if (ISSET(lflag, PENDIN))
E 157
E 112
E 110
I 110
	if (tp->t_lflag&PENDIN)
E 110
E 56
		ttypend(tp);
I 115
D 120
	/*
	 * Handle carrier.
	 */
	if (!(tp->t_state&TS_CARR_ON) && !(tp->t_cflag&CLOCAL)) {
		if (tp->t_state&TS_ISOPEN) {
			splx(s);
			return (0);	/* EOF */
D 116
		} else if (flag&FNDELAY) {
E 116
I 116
		} else if (flag & IO_NDELAY) {
E 116
			splx(s);
			return (EWOULDBLOCK);
		} else {
			/*
			 * sleep awaiting carrier
			 */
			sleep((caddr_t)&tp->t_rawq, TTIPRI);
			splx(s);
			goto loop;
		}
	}
E 120
E 115
D 60
	(void) spl0();
E 60
I 60
	splx(s);
I 120

E 120
E 60
I 56
D 112

E 112
I 90
D 115
	if ((tp->t_state&TS_CARR_ON)==0)
		return (EIO);
E 115
D 112

E 112
E 90
	/*
	 * Hang process if it's in the background.
	 */
I 79
D 93
#define bit(a) (1<<(a-1))
E 93
E 79
E 56
D 90
	while (tp == u.u_ttyp && u.u_procp->p_pgrp != tp->t_pgrp) {
E 90
I 90
D 112
	if (tp == u.u_ttyp && u.u_procp->p_pgrp != tp->t_pgrp) {
E 112
I 112
D 118
	if (u.u_ttyp == tp && u.u_procp->p_pgid != tp->t_pgid) {
E 118
I 118
D 137
	if (isbackground(u.u_procp, tp)) {
E 118
E 112
E 90
D 79
		if (u.u_signal[SIGTTIN] == SIG_IGN ||
		    u.u_signal[SIGTTIN] == SIG_HOLD ||
E 79
I 79
D 93
		if ((u.u_procp->p_sigignore & bit(SIGTTIN)) ||
		   (u.u_procp->p_sigmask & bit(SIGTTIN)) ||
E 93
I 93
		if ((u.u_procp->p_sigignore & sigmask(SIGTTIN)) ||
		   (u.u_procp->p_sigmask & sigmask(SIGTTIN)) ||
E 93
E 79
D 90
/*
		    (u.u_procp->p_flag&SDETACH) ||
*/
E 90
D 112
		    u.u_procp->p_flag&SVFORK)
E 112
I 112
		    u.u_procp->p_flag&SVFORK || u.u_procp->p_pgrp->pg_jobc == 0)
E 137
I 137
	if (isbackground(p, tp)) {
		if ((p->p_sigignore & sigmask(SIGTTIN)) ||
		   (p->p_sigmask & sigmask(SIGTTIN)) ||
D 157
		    p->p_flag&SPPWAIT || p->p_pgrp->pg_jobc == 0)
E 157
I 157
D 159
		    p->p_flag & SPPWAIT || p->p_pgrp->pg_jobc == 0)
E 159
I 159
		    p->p_flag & P_PPWAIT || p->p_pgrp->pg_jobc == 0)
E 159
E 157
E 137
E 112
D 50
			return (0);
E 50
I 50
			return (EIO);
E 50
D 112
		gsignal(u.u_procp->p_pgrp, SIGTTIN);
E 112
I 112
D 127
		pgsignal(u.u_procp->p_pgrp, SIGTTIN);
E 127
I 127
D 137
		pgsignal(u.u_procp->p_pgrp, SIGTTIN, 1);
E 137
I 137
		pgsignal(p->p_pgrp, SIGTTIN, 1);
E 137
E 127
E 112
D 120
		sleep((caddr_t)&lbolt, TTIPRI);
E 120
I 120
D 128
		if (error = tsleep((caddr_t)&lbolt, TTIPRI | PCATCH, ttybg, 0))
E 128
I 128
D 132
		if ((error = tsleep((caddr_t)&lbolt, TTIPRI | PCATCH, 
				    ttybg, 0)) ||
		    (error = ttclosed(tp)))
E 132
I 132
D 157
		if (error = ttysleep(tp, (caddr_t)&lbolt, TTIPRI | PCATCH, 
		    ttybg, 0)) 
E 157
I 157
		if (error = ttysleep(tp, &lbolt, TTIPRI | PCATCH, ttybg, 0))
E 157
E 132
E 128
			return (error);
E 120
I 90
		goto loop;
E 90
	}
I 120

E 120
D 56
	if (tp->t_flags&RAW) {
E 56
I 56
D 112
	t_flags = tp->t_flags;
I 79
D 93
#undef	bit
E 93
E 79

E 112
	/*
D 110
D 112
	 * In raw mode take characters directly from the
	 * raw queue w/o processing.  Interlock against
	 * device interrupts when interrogating rawq.
E 112
I 112
	 * If canonical, use the canonical queue,
	 * else use the raw queue.
I 115
	 *
D 137
	 * XXX - should get rid of canonical queue.
	 * (actually, should get rid of clists...)
E 137
I 137
	 * (should get rid of clists...)
E 137
E 115
E 112
E 110
I 110
	 * If canonical, use the canonical queue,
	 * else use the raw queue.
E 110
	 */
D 110
D 112
	if (t_flags&RAW) {
E 56
D 60
		(void) spl5();
E 60
I 60
D 84
		s = spl5();
E 84
I 84
		s = spltty();
E 84
E 60
		if (tp->t_rawq.c_cc <= 0) {
D 56
			if ((tp->t_state&TS_CARR_ON)==0 ||
E 56
I 56
			if ((tp->t_state&TS_CARR_ON) == 0 ||
E 56
			    (tp->t_state&TS_NBIO)) {
D 60
				(void) spl0();
E 60
I 60
				splx(s);
E 60
D 50
				return (0);
E 50
I 50
D 56
				return (EWOULDBLOCK);
E 56
I 56
D 75
				return (0);
E 75
I 75
				return (EWOULDBLOCK);
E 75
E 56
E 50
			}
			sleep((caddr_t)&tp->t_rawq, TTIPRI);
D 60
			(void) spl0();
E 60
I 60
			splx(s);
E 60
			goto loop;
		}
D 60
		(void) spl0();
D 47
		while (tp->t_rawq.c_cc && passc(getc(&tp->t_rawq))>=0)
			;
E 47
I 47
		while (tp->t_rawq.c_cc && uio->uio_iovcnt) {
E 60
I 60
		splx(s);
D 73
		while (!error && tp->t_rawq.c_cc && uio->uio_iovcnt)
E 60
D 50
			u.u_error = passuc(getc(&tp->t_rawq), uio);
			if (u.u_error)
E 50
I 50
			error = passuc(getc(&tp->t_rawq), uio);
E 73
I 73
 		while (!error && tp->t_rawq.c_cc && uio->uio_resid)
 			error = ureadc(getc(&tp->t_rawq), uio);
E 73
D 60
			if (error)
E 50
				break;
		}
E 47
D 50
		return (0);
E 50
I 50
		return (error);
E 60
I 60
		goto checktandem;
E 60
E 50
D 56
	} else {
		qp = tp->t_flags & CBREAK ? &tp->t_rawq : &tp->t_canq;
		(void) spl5();
		if (qp->c_cc <= 0) {
			if ((tp->t_state&TS_CARR_ON)==0 ||
			    (tp->t_state&TS_NBIO)) {
				(void) spl0();
D 50
				return (0);
E 50
I 50
				return (EWOULDBLOCK);
E 50
			}
			sleep((caddr_t)&tp->t_rawq, TTIPRI);
E 56
I 56
	}
E 110
I 110
	qp = lflag&ICANON ? &tp->t_canq : &tp->t_rawq;
E 110

E 112
I 112
D 157
	qp = lflag&ICANON ? &tp->t_canq : &tp->t_rawq;
E 157
I 157
	qp = ISSET(lflag, ICANON) ? &tp->t_canq : &tp->t_rawq;
E 157
I 120

E 120
E 112
	/*
D 110
D 112
	 * In cbreak mode use the rawq, otherwise
	 * take characters from the canonicalized q.
	 */
	qp = t_flags&CBREAK ? &tp->t_rawq : &tp->t_canq;

	/*
E 112
E 110
D 120
	 * No input, sleep on rawq awaiting hardware
	 * receipt and notification.
E 120
I 120
	 * If there is no input, sleep on rawq
	 * awaiting hardware receipt and notification.
	 * If we have data, we don't need to check for carrier.
E 120
	 */
D 60
	(void) spl5();
E 60
I 60
D 84
	s = spl5();
E 84
I 84
	s = spltty();
E 84
E 60
	if (qp->c_cc <= 0) {
I 115
D 120
		/** XXX ??? ask mike why TS_CARR_ON was (once) necessary here
E 115
		if ((tp->t_state&TS_CARR_ON) == 0 ||
		    (tp->t_state&TS_NBIO)) {
E 120
I 120
		int carrier;

D 157
		carrier = (tp->t_state&TS_CARR_ON) || (tp->t_cflag&CLOCAL);
		if (!carrier && tp->t_state&TS_ISOPEN) {
E 157
I 157
		carrier = ISSET(tp->t_state, TS_CARR_ON) ||
		    ISSET(tp->t_cflag, CLOCAL);
		if (!carrier && ISSET(tp->t_state, TS_ISOPEN)) {
E 157
E 120
E 56
D 60
			(void) spl0();
E 60
I 60
			splx(s);
E 60
D 56
			goto loop;
E 56
I 56
D 120
			return (EWOULDBLOCK);
E 120
I 120
			return (0);	/* EOF */
E 120
E 56
		}
I 115
D 120
		**/
E 120
D 116
		if (flag&FNDELAY) {
E 116
I 116
		if (flag & IO_NDELAY) {
E 116
			splx(s);
			return (EWOULDBLOCK);
		}
E 115
I 56
D 120
		sleep((caddr_t)&tp->t_rawq, TTIPRI);
E 120
I 120
D 132
		error = tsleep((caddr_t)&tp->t_rawq, TTIPRI | PCATCH,
E 132
I 132
D 157
		error = ttysleep(tp, (caddr_t)&tp->t_rawq, TTIPRI | PCATCH,
E 157
I 157
		error = ttysleep(tp, &tp->t_rawq, TTIPRI | PCATCH,
E 157
E 132
		    carrier ? ttyin : ttopen, 0);
E 120
E 56
D 60
		(void) spl0();
E 60
I 60
		splx(s);
I 120
D 128
		if (error)
E 128
I 128
D 132
		if (error || (error = ttclosed(tp)))
E 132
I 132
		if (error)
E 132
E 128
			return (error);
E 120
E 60
D 56
		first = 1;
		while ((c = getc(qp)) >= 0) {
			if (tp->t_flags&CRMOD && c == '\r')
				c = '\n';
			if (tp->t_flags&LCASE && c <= 0177)
				if (tp->t_lstate&LSBKSL) {
					if (maptab[c])
						c = maptab[c];
					tp->t_lstate &= ~LSBKSL;
				} else if (c >= 'A' && c <= 'Z')
					c += 'a' - 'A';
				else if (c == '\\') {
					tp->t_lstate |= LSBKSL;
					continue;
				}
D 46
			if (c == tlun.t_dsuspc) {
E 46
I 46
			if (tp->t_line == NTTYDISC && c == tlun.t_dsuspc) {
E 46
				ttsignal(tp, SIGTSTP);
				if (first) {
					sleep((caddr_t)&lbolt, TTIPRI);
					goto loop;
				}
				break;
E 56
I 56
		goto loop;
	}
D 60
	(void) spl0();
E 60
I 60
	splx(s);
I 120

E 120
E 60
D 112

E 112
	/*
D 110
D 112
	 * Input present, perform input mapping
	 * and processing (we're not in raw mode).
E 112
I 112
	 * Input present, check for input mapping and processing.
E 112
E 110
I 110
	 * Input present, check for input mapping and processing.
E 110
	 */
	first = 1;
	while ((c = getc(qp)) >= 0) {
D 110
D 112
		if (t_flags&CRMOD && c == '\r')
			c = '\n';
E 112
E 110
		/*
D 90
		 * Hack lower case simulation on
		 * upper case only terminals.
		 */
		if (t_flags&LCASE && c <= 0177)
			if (tp->t_state&TS_BKSL) {
				if (maptab[c])
					c = maptab[c];
				tp->t_state &= ~TS_BKSL;
			} else if (c >= 'A' && c <= 'Z')
				c += 'a' - 'A';
			else if (c == '\\') {
				tp->t_state |= TS_BKSL;
				continue;
E 56
			}
D 56
			if (c == tun.t_eofc && (tp->t_flags&CBREAK)==0)
				break;
D 47
			if (passc(c & 0177) < 0)
E 47
I 47
D 50
			u.u_error = passuc(c & 0177, uio);
			if (u.u_error)
E 50
I 50
			error = passuc(c & 0177, uio);
			if (error)
E 50
				break;
			if (uio->uio_iovcnt == 0)
E 47
				break;
			if ((tp->t_flags&CBREAK)==0 && ttbreakc(c, tp))
				break;
			first = 0;
E 56
I 56
		/*
E 90
D 110
D 112
		 * Check for delayed suspend character.
E 112
I 112
		 * delayed suspend (^Y)
E 112
E 110
I 110
		 * delayed suspend (^Y)
E 110
		 */
D 110
D 112
		if (tp->t_line == NTTYDISC && c == tp->t_dsuspc) {
E 110
I 110
		if (CCEQ(cc[VDSUSP], c) && lflag&ISIG) {
E 110
			gsignal(tp->t_pgrp, SIGTSTP);
E 112
I 112
D 157
		if (CCEQ(cc[VDSUSP], c) && lflag&ISIG) {
E 157
I 157
		if (CCEQ(cc[VDSUSP], c) && ISSET(lflag, ISIG)) {
E 157
D 118
			gsignal(tp->t_pgid, SIGTSTP);
E 118
I 118
D 127
			pgsignal(tp->t_pgrp, SIGTSTP);
E 127
I 127
			pgsignal(tp->t_pgrp, SIGTSTP, 1);
E 127
E 118
E 112
			if (first) {
D 120
				sleep((caddr_t)&lbolt, TTIPRI);
E 120
I 120
D 128
				if (error = tsleep((caddr_t)&lbolt,
				    TTIPRI | PCATCH, ttybg, 0))
E 128
I 128
D 132
				if ((error = tsleep((caddr_t)&lbolt,
					    TTIPRI | PCATCH, ttybg, 0)) ||
				    (error = ttclosed(tp)))
E 132
I 132
D 157
				if (error = ttysleep(tp, (caddr_t)&lbolt,
				    TTIPRI | PCATCH, ttybg, 0))
E 157
I 157
				if (error = ttysleep(tp,
				    &lbolt, TTIPRI | PCATCH, ttybg, 0))
E 157
E 132
E 128
					break;
E 120
				goto loop;
			}
			break;
E 56
		}
D 56
		tp->t_lstate &= ~LSBKSL;
E 56
I 56
		/*
D 110
D 112
		 * Interpret EOF only in cooked mode.
E 112
I 112
		 * Interpret EOF only in canonical mode.
E 112
E 110
I 110
		 * Interpret EOF only in canonical mode.
E 110
		 */
D 110
D 112
		if (c == tp->t_eofc && (t_flags&CBREAK) == 0)
E 112
I 112
D 157
		if (CCEQ(cc[VEOF], c) && lflag&ICANON)
E 157
I 157
		if (CCEQ(cc[VEOF], c) && ISSET(lflag, ICANON))
E 157
E 112
E 110
I 110
		if (CCEQ(cc[VEOF], c) && lflag&ICANON)
E 110
			break;
		/*
		 * Give user character.
		 */
D 73
		error = passuc(c & 0177, uio);
E 73
I 73
D 92
 		error = ureadc(c & 0177, uio);
E 92
I 92
D 110
D 112
 		error = ureadc(t_flags&PASS8 ? c : c & 0177, uio);
E 112
I 112
D 120
 		error = ureadc(c , uio);
E 120
I 120
 		error = ureadc(c, uio);
E 120
E 112
E 110
I 110
 		error = ureadc(iflag&ISTRIP ? c & 0177 : c , uio);
E 110
E 92
E 73
		if (error)
			break;
D 73
		if (uio->uio_iovcnt == 0)
E 73
I 73
 		if (uio->uio_resid == 0)
E 73
			break;
		/*
D 110
D 112
		 * In cooked mode check for a "break character"
E 112
I 112
		 * In canonical mode check for a "break character"
E 112
E 110
I 110
		 * In canonical mode check for a "break character"
E 110
		 * marking the end of a "line of input".
		 */
D 110
D 112
		if ((t_flags&CBREAK) == 0 && ttbreakc(c, tp))
E 112
I 112
D 120
		if (lflag&ICANON && ttbreakc(c)) {
E 120
I 120
D 157
		if (lflag&ICANON && ttbreakc(c))
E 157
I 157
		if (ISSET(lflag, ICANON) && TTBREAKC(c))
E 157
E 120
E 112
E 110
I 110
		if (lflag&ICANON && ttbreakc(c)) {
E 110
			break;
I 112
D 120
		}
E 120
E 112
I 110
		}
E 110
		first = 0;
E 56
	}
I 56
D 90
	tp->t_state &= ~TS_BKSL;
E 90
D 112

E 112
I 60
D 116
checktandem:
E 116
E 60
	/*
	 * Look to unblock output now that (presumably)
	 * the input queue has gone down.
	 */
I 147
	s = spltty();
E 147
E 56
D 50

E 50
D 60
	if (tp->t_state&TS_TBLOCK && tp->t_rawq.c_cc < TTYHOG/5) {
E 60
I 60
D 110
D 112
	if (tp->t_state&TS_TBLOCK && tp->t_rawq.c_cc < TTYHOG/5)
E 60
D 56
		if (putc(tun.t_startc, &tp->t_outq)==0) {
E 56
I 56
		if (putc(tp->t_startc, &tp->t_outq) == 0) {
E 112
I 112
D 157
	if (tp->t_state&TS_TBLOCK && tp->t_rawq.c_cc < TTYHOG/5) {
E 157
I 157
	if (ISSET(tp->t_state, TS_TBLOCK) && tp->t_rawq.c_cc < TTYHOG/5) {
E 157
D 137
		if (cc[VSTART] != _POSIX_VDISABLE 
		   && putc(cc[VSTART], &tp->t_outq) == 0) {
E 137
I 137
		if (cc[VSTART] != _POSIX_VDISABLE &&
		    putc(cc[VSTART], &tp->t_outq) == 0) {
E 137
E 112
E 110
I 110
	if (tp->t_state&TS_TBLOCK && tp->t_rawq.c_cc < TTYHOG/5) {
		if (cc[VSTART] != POSIX_V_DISABLE 
		   && putc(cc[VSTART], &tp->t_outq) == 0) {
E 110
E 56
D 157
			tp->t_state &= ~TS_TBLOCK;
E 157
I 157
			CLR(tp->t_state, TS_TBLOCK);
E 157
			ttstart(tp);
		}
I 112
	}
I 147
	splx(s);
E 147
E 112
I 110
	}
E 110
D 60
		tp->t_char = 0;
	}
E 60
D 50

	return (tp->t_rawq.c_cc + tp->t_canq.c_cc);
E 50
I 50
	return (error);
I 94
}

/*
D 157
 * Check the output queue on tp for space for a kernel message
 * (from uprintf/tprintf).  Allow some space over the normal
 * hiwater mark so we don't lose messages due to normal flow
 * control, but don't let the tty run amok.
I 103
 * Sleeps here are not interruptible, but we return prematurely
 * if new signals come in.
E 157
I 157
 * Check the output queue on tp for space for a kernel message (from uprintf
 * or tprintf).  Allow some space over the normal hiwater mark so we don't
 * lose messages due to normal flow control, but don't let the tty run amok.
 * Sleeps here are not interruptible, but we return prematurely if new signals
 * arrive.
E 157
E 103
 */
I 157
int
E 157
ttycheckoutq(tp, wait)
	register struct tty *tp;
	int wait;
{
D 103
	int hiwat, s;
E 103
I 103
	int hiwat, s, oldsig;
I 138
D 150
	extern int wakeup();
E 150
E 138
E 103

D 112
	hiwat = TTHIWAT(tp);
E 112
I 112
	hiwat = tp->t_hiwat;
E 112
	s = spltty();
I 103
D 137
	oldsig = u.u_procp->p_sig;
E 137
I 137
D 144
	oldsig = curproc->p_sig;
E 144
I 144
D 147
	if (wait)
		oldsig = curproc->p_sig;
E 147
I 147
D 159
	oldsig = wait ? curproc->p_sig : 0;
E 159
I 159
	oldsig = wait ? curproc->p_siglist : 0;
E 159
E 147
E 144
E 137
E 103
	if (tp->t_outq.c_cc > hiwat + 200)
D 101
	    while (tp->t_outq.c_cc > hiwat) {
		ttstart(tp);
		if (wait == 0) {
			splx(s);
			return (0);
E 101
I 101
		while (tp->t_outq.c_cc > hiwat) {
			ttstart(tp);
D 103
			if (wait == 0) {
E 103
I 103
D 137
			if (wait == 0 || u.u_procp->p_sig != oldsig) {
E 137
I 137
D 159
			if (wait == 0 || curproc->p_sig != oldsig) {
E 159
I 159
			if (wait == 0 || curproc->p_siglist != oldsig) {
E 159
E 137
E 103
				splx(s);
				return (0);
			}
I 103
D 150
			timeout(wakeup, (caddr_t)&tp->t_outq, hz);
E 150
I 150
			timeout((void (*)__P((void *)))wakeup,
			    (void *)&tp->t_outq, hz);
E 150
E 103
D 157
			tp->t_state |= TS_ASLEEP;
E 157
I 157
			SET(tp->t_state, TS_ASLEEP);
E 157
D 103
			sleep((caddr_t)&tp->t_outq, TTOPRI);
E 103
I 103
			sleep((caddr_t)&tp->t_outq, PZERO - 1);
E 103
E 101
		}
D 101
		tp->t_state |= TS_ASLEEP;
		sleep((caddr_t)&tp->t_outq, TTOPRI);
	}
E 101
	splx(s);
	return (1);
E 94
E 50
}

/*
D 140
 * Called from the device's write routine after it has
 * calculated the tty-structure given as argument.
E 140
I 140
 * Process a write call on a tty device.
E 140
 */
I 157
int
E 157
D 50
caddr_t
E 50
D 48
ttwrite(tp)
E 48
I 48
D 115
ttwrite(tp, uio)
E 115
I 115
ttwrite(tp, uio, flag)
E 115
E 48
D 45
register struct tty *tp;
E 45
I 45
	register struct tty *tp;
I 48
D 56
	struct uio *uio;
E 56
I 56
	register struct uio *uio;
I 147
	int flag;
E 147
E 56
E 48
E 45
{
D 56
#ifdef vax
	/*
	 * THE POSITIONING OF CP, CC, AND CE ARE CRITICAL
	 * AND MUST NOT BE CHANGED WITHOUT PATCHING
	 * THE 'ASM' INLINES BELOW.  WATCH OUT.
	 */
#endif
E 56
	register char *cp;
D 56
	register int cc, ce;
	register i;
E 56
I 56
D 116
	register int cc, ce, c;
E 116
I 116
D 120
	register int cc, ce;
E 120
I 120
D 157
	register int cc = 0, ce;
I 137
	register struct proc *p = curproc;
E 157
I 157
	register int cc, ce;
	register struct proc *p;
E 157
E 137
E 120
E 116
	int i, hiwat, cnt, error, s;
E 56
	char obuf[OBUFSIZ];
D 56
	register c;
	int hiwat = TTHIWAT(tp);
D 48
	int cnt = u.u_count;
E 48
I 48
	int cnt = uio->uio_resid;
I 50
	int error = 0;
E 56
E 50
E 48

D 56
	if ((tp->t_state&TS_CARR_ON)==0)
E 56
I 56
D 89
	if ((tp->t_state&TS_CARR_ON) == 0)
E 56
D 50
		return (NULL);
E 50
I 50
		return (EIO);
E 89
I 56
D 112
	hiwat = TTHIWAT(tp);
E 112
I 112
	hiwat = tp->t_hiwat;
E 112
	cnt = uio->uio_resid;
	error = 0;
I 160
	cc = 0;
E 160
E 56
E 50
loop:
I 89
D 115
	if ((tp->t_state&TS_CARR_ON) == 0)
		return (EIO);
E 115
I 115
	s = spltty();
D 120
	if (!(tp->t_state&TS_CARR_ON) && !(tp->t_cflag&CLOCAL)) {
E 120
I 120
D 157
	if ((tp->t_state&TS_CARR_ON) == 0 && (tp->t_cflag&CLOCAL) == 0) {
E 120
		if (tp->t_state&TS_ISOPEN) {
E 157
I 157
	if (!ISSET(tp->t_state, TS_CARR_ON) &&
	    !ISSET(tp->t_cflag, CLOCAL)) {
		if (ISSET(tp->t_state, TS_ISOPEN)) {
E 157
			splx(s);
			return (EIO);
D 116
		} else if (flag&FNDELAY) {
E 116
I 116
		} else if (flag & IO_NDELAY) {
E 116
			splx(s);
D 120
			return (EWOULDBLOCK);
E 120
I 120
			error = EWOULDBLOCK;
			goto out;
E 120
		} else {
D 157
			/*
			 * sleep awaiting carrier
			 */
D 120
			sleep((caddr_t)&tp->t_rawq, TTIPRI);
E 120
I 120
D 132
			error = tsleep((caddr_t)&tp->t_rawq, TTIPRI | PCATCH,
			    ttopen, 0);
E 132
I 132
			error = ttysleep(tp, (caddr_t)&tp->t_rawq, 
					TTIPRI | PCATCH,ttopen, 0);
E 157
I 157
			/* Sleep awaiting carrier. */
			error = ttysleep(tp,
			    &tp->t_rawq, TTIPRI | PCATCH,ttopen, 0);
E 157
E 132
E 120
			splx(s);
I 120
D 128
			if (error)
E 128
I 128
D 132
			if (error || (error = ttclosed(tp)))
E 132
I 132
			if (error)
E 132
E 128
				goto out;
E 120
			goto loop;
		}
	}
	splx(s);
E 115
E 89
I 56
	/*
	 * Hang the process if it's in the background.
	 */
I 79
D 93
#define bit(a) (1<<(a-1))
E 93
E 79
E 56
D 89
	while (u.u_procp->p_pgrp != tp->t_pgrp && tp == u.u_ttyp &&
E 89
I 89
D 112
	if (u.u_procp->p_pgrp != tp->t_pgrp && tp == u.u_ttyp &&
E 89
D 56
	    (tp->t_local&LTOSTOP) && (u.u_procp->p_flag&SVFORK)==0 &&
E 56
I 56
D 110
	    (tp->t_flags&TOSTOP) && (u.u_procp->p_flag&SVFORK)==0 &&
E 112
I 112
D 118
	if (u.u_ttyp == tp &&
	    u.u_procp->p_pgid != tp->t_pgid && 
E 118
I 118
D 137
	if (isbackground(u.u_procp, tp) && 
E 118
	    (tp->t_lflag&TOSTOP) && (u.u_procp->p_flag&SVFORK)==0 &&
E 112
E 110
I 110
	    (tp->t_lflag&TOSTOP) && (u.u_procp->p_flag&SVFORK)==0 &&
E 110
E 56
D 79
	    u.u_signal[SIGTTOU] != SIG_IGN &&
	    u.u_signal[SIGTTOU] != SIG_HOLD
E 79
I 79
D 93
	    !(u.u_procp->p_sigignore & bit(SIGTTOU)) &&
D 89
	    !(u.u_procp->p_sigmask & bit(SIGTTOU))
E 79
/*
					     &&
	    (u.u_procp->p_flag&SDETACH)==0) {
*/
	    ) {
E 89
I 89
	    !(u.u_procp->p_sigmask & bit(SIGTTOU))) {
E 93
I 93
D 120
	    !(u.u_procp->p_sigignore & sigmask(SIGTTOU)) &&
D 112
	    !(u.u_procp->p_sigmask & sigmask(SIGTTOU))) {
E 93
E 89
		gsignal(u.u_procp->p_pgrp, SIGTTOU);
E 112
I 112
	    !(u.u_procp->p_sigmask & sigmask(SIGTTOU)) &&
E 120
I 120
	    (u.u_procp->p_sigignore & sigmask(SIGTTOU)) == 0 &&
	    (u.u_procp->p_sigmask & sigmask(SIGTTOU)) == 0 &&
E 120
	     u.u_procp->p_pgrp->pg_jobc) {
D 127
		pgsignal(u.u_procp->p_pgrp, SIGTTOU);
E 127
I 127
		pgsignal(u.u_procp->p_pgrp, SIGTTOU, 1);
E 137
I 137
D 157
	if (isbackground(p, tp) && 
	    tp->t_lflag&TOSTOP && (p->p_flag&SPPWAIT) == 0 &&
E 157
I 157
	p = curproc;
	if (isbackground(p, tp) &&
D 159
	    ISSET(tp->t_lflag, TOSTOP) && (p->p_flag & SPPWAIT) == 0 &&
E 159
I 159
	    ISSET(tp->t_lflag, TOSTOP) && (p->p_flag & P_PPWAIT) == 0 &&
E 159
E 157
	    (p->p_sigignore & sigmask(SIGTTOU)) == 0 &&
	    (p->p_sigmask & sigmask(SIGTTOU)) == 0 &&
	     p->p_pgrp->pg_jobc) {
		pgsignal(p->p_pgrp, SIGTTOU, 1);
E 137
E 127
E 112
D 120
		sleep((caddr_t)&lbolt, TTIPRI);
E 120
I 120
D 128
		if (error = tsleep((caddr_t)&lbolt, TTIPRI | PCATCH, ttybg, 0))
E 128
I 128
D 132
		if ((error = tsleep((caddr_t)&lbolt, TTIPRI | PCATCH, 
				     ttybg, 0)) ||
		    (error = ttclosed(tp)))
E 132
I 132
D 157
		if (error = ttysleep(tp, (caddr_t)&lbolt, TTIPRI | PCATCH, 
		    ttybg, 0))
E 157
I 157
		if (error = ttysleep(tp, &lbolt, TTIPRI | PCATCH, ttybg, 0))
E 157
E 132
E 128
			goto out;
E 120
I 89
		goto loop;
E 89
	}
I 79
D 93
#undef	bit
E 93
E 79
I 56
D 112

E 112
	/*
D 157
	 * Process the user's data in at most OBUFSIZ
D 120
	 * chunks.  Perform lower case simulation and
	 * similar hacks.  Keep track of high water
	 * mark, sleep on overflow awaiting device aid
	 * in acquiring new space.
E 120
I 120
	 * chunks.  Perform any output translation.
	 * Keep track of high water mark, sleep on overflow
	 * awaiting device aid in acquiring new space.
E 157
I 157
	 * Process the user's data in at most OBUFSIZ chunks.  Perform any
	 * output translation.  Keep track of high water mark, sleep on
	 * overflow awaiting device aid in acquiring new space.
E 157
E 120
	 */
E 56
D 48
	while (u.u_count) {
		cc = MIN(u.u_count, OBUFSIZ);
E 48
I 48
D 120
	while (uio->uio_resid > 0) {
I 106
		if (tp->t_outq.c_cc > hiwat) {
			cc = 0;
			goto ovhiwat;
E 120
I 120
D 157
	while (uio->uio_resid > 0 || cc > 0) {
		if (tp->t_lflag&FLUSHO) {
E 157
I 157
D 160
	for (cc = 0; uio->uio_resid > 0 || cc > 0;) {
E 160
I 160
	while (uio->uio_resid > 0 || cc > 0) {
E 160
		if (ISSET(tp->t_lflag, FLUSHO)) {
E 157
			uio->uio_resid = 0;
			return (0);
E 120
		}
I 120
		if (tp->t_outq.c_cc > hiwat)
			goto ovhiwat;
E 120
E 106
I 56
		/*
D 120
		 * Grab a hunk of data from the user.
E 120
I 120
D 157
		 * Grab a hunk of data from the user,
		 * unless we have some leftover from last time.
E 157
I 157
		 * Grab a hunk of data from the user, unless we have some
		 * leftover from last time.
E 157
E 120
		 */
E 56
D 120
		cc = uio->uio_iov->iov_len;
E 120
		if (cc == 0) {
D 120
			uio->uio_iovcnt--;
			uio->uio_iov++;
D 89
			if (uio->uio_iovcnt < 0)
E 89
I 89
			if (uio->uio_iovcnt <= 0)
E 89
				panic("ttwrite");
			continue;
E 120
I 120
			cc = min(uio->uio_resid, OBUFSIZ);
			cp = obuf;
			error = uiomove(cp, cc, uio);
			if (error) {
				cc = 0;
				break;
			}
E 120
		}
D 120
		if (cc > OBUFSIZ)
			cc = OBUFSIZ;
E 48
		cp = obuf;
D 48
		iomove(cp, (unsigned)cc, B_WRITE);
E 48
I 48
D 50
		u.u_error = uiomove(cp, cc, UIO_WRITE, uio);
E 48
		if (u.u_error)
E 50
I 50
D 56
		error = uiomove(cp, cc, UIO_WRITE, uio);
E 56
I 56
D 63
		error = uiomove(cp, (unsigned)cc, UIO_WRITE, uio);
E 63
I 63
D 116
		error = uiomove(cp, cc, UIO_WRITE, uio);
E 116
I 116
		error = uiomove(cp, cc, uio);
E 116
E 63
E 56
		if (error)
E 50
			break;
D 106
		if (tp->t_outq.c_cc > hiwat)
			goto ovhiwat;
E 106
D 56
		if (tp->t_local&LFLUSHO)
E 56
I 56
D 110
D 112
		if (tp->t_flags&FLUSHO)
E 112
I 112
		if (tp->t_lflag&FLUSHO)
E 112
E 110
I 110
		if (tp->t_lflag&FLUSHO)
E 110
E 56
			continue;
E 120
I 110
#ifdef notdef
E 110
D 56
		if (tp->t_flags&LCASE || tp->t_local&LTILDE) {
			while (cc) {
E 56
I 56
		/*
D 112
		 * If we're mapping lower case or kludging tildes,
		 * then we've got to look at each character, so
		 * just feed the stuff to ttyoutput...
		 */
		if (tp->t_flags & (LCASE|TILDE)) {
			while (cc > 0) {
E 56
				c = *cp++;
				tp->t_rocount = 0;
D 45
				while((c = ttyoutput(c, tp)) >= 0) {
E 45
I 45
				while ((c = ttyoutput(c, tp)) >= 0) {
E 45
					/* out of clists, wait a bit */
					ttstart(tp);
					sleep((caddr_t)&lbolt, TTOPRI);
					tp->t_rocount = 0;
I 89
					if (cc != 0) {
						uio->uio_iov->iov_base -= cc;
						uio->uio_iov->iov_len += cc;
						uio->uio_resid += cc;
						uio->uio_offset -= cc;
					}
					goto loop;
E 89
				}
				--cc;
				if (tp->t_outq.c_cc > hiwat)
					goto ovhiwat;
			}
			continue;
		}
I 110
#endif
E 110
D 56
		while (cc) {
			if (tp->t_flags&RAW || tp->t_local&LLITOUT)
E 56
I 56
		/*
E 112
		 * If nothing fancy need be done, grab those characters we
		 * can handle without any of ttyoutput's processing and
		 * just transfer them to the output q.  For those chars
		 * which require special processing (as indicated by the
D 157
		 * bits in partab), call ttyoutput.  After processing
E 157
I 157
		 * bits in char_type), call ttyoutput.  After processing
E 157
		 * a hunk of data, look for FLUSHO so ^O's will take effect
		 * immediately.
		 */
		while (cc > 0) {
D 110
D 112
			if (tp->t_flags & (RAW|LITOUT))
E 112
I 112
D 120
			if (!(tp->t_oflag&OPOST))
E 120
I 120
D 157
			if ((tp->t_oflag&OPOST) == 0)
E 157
I 157
			if (!ISSET(tp->t_oflag, OPOST))
E 157
E 120
E 112
E 110
I 110
			if (!(tp->t_oflag&OPOST))
E 110
E 56
				ce = cc;
			else {
D 56
#ifdef vax
				asm("	scanc	r9,(r10),_partab,$077");
				asm("	subl3	r0,r9,r8");
#else
				ce=0;
D 45
				while(((partab[*(unsigned char *)(cp+ce)]&077)==0)&&(ce<cc))
E 45
I 45
				while (((partab[*(unsigned char *)(cp+ce)]&077)==0)&&(ce<cc))
E 45
					ce++;
#endif
				if (ce==0) {
E 56
I 56
D 63
				ce = cc - scanc(cc, cp, partab, 077);
E 63
I 63
D 111
				ce = cc - scanc((unsigned)cc, (caddr_t)cp,
				   (caddr_t)partab, 077);
E 111
I 111
D 157
				ce = cc - scanc((unsigned)cc, (u_char *)cp,
D 140
				   (u_char *)partab, 077);
E 140
I 140
				   (u_char *)partab, CCLASSMASK);
E 157
I 157
				ce = cc - scanc((u_int)cc, (u_char *)cp,
				   (u_char *)char_type, CCLASSMASK);
E 157
E 140
E 111
E 63
				/*
				 * If ce is zero, then we're processing
				 * a special character through ttyoutput.
				 */
				if (ce == 0) {
E 56
					tp->t_rocount = 0;
					if (ttyoutput(*cp, tp) >= 0) {
I 56
D 89
						/* no c-lists, wait a bit */
E 56
						ttstart(tp);
						sleep((caddr_t)&lbolt, TTOPRI);
						continue;
E 89
I 89
D 157
					    /* no c-lists, wait a bit */
					    ttstart(tp);
D 120
					    sleep((caddr_t)&lbolt, TTOPRI);
					    if (cc != 0) {
					        uio->uio_iov->iov_base -= cc;
					        uio->uio_iov->iov_len += cc;
					        uio->uio_resid += cc;
						uio->uio_offset -= cc;
					    }
E 120
I 120
D 128
					    if (error = tsleep((caddr_t)&lbolt,
						TTOPRI | PCATCH, ttybuf, 0))
E 128
I 128
D 132
					    if ((error = tsleep((caddr_t)&lbolt,
						TTOPRI | PCATCH, ttybuf, 0)) ||
						(error = ttclosed(tp)))
E 132
I 132
					    if (error = ttysleep(tp, 
						(caddr_t)&lbolt,
						 TTOPRI | PCATCH, ttybuf, 0))
E 132
E 128
						    break;
E 120
					    goto loop;
E 157
I 157
						/* No Clists, wait a bit. */
						ttstart(tp);
						if (error = ttysleep(tp, &lbolt,
						    TTOPRI | PCATCH, ttybuf, 0))
							break;
						goto loop;
E 157
E 89
					}
D 56
					cp++;
					cc--;
					if (tp->t_outq.c_cc > hiwat)
E 56
I 56
D 157
					cp++, cc--;
D 110
D 112
					if (tp->t_flags&FLUSHO ||
E 112
I 112
					if ((tp->t_lflag&FLUSHO) ||
E 157
I 157
					cp++;
					cc--;
					if (ISSET(tp->t_lflag, FLUSHO) ||
E 157
E 112
E 110
I 110
					if (tp->t_lflag&FLUSHO ||
E 110
					    tp->t_outq.c_cc > hiwat)
E 56
						goto ovhiwat;
I 56
					continue;
E 56
				}
			}
I 56
			/*
D 157
			 * A bunch of normal characters have been found,
			 * transfer them en masse to the output queue and
E 157
I 157
			 * A bunch of normal characters have been found.
			 * Transfer them en masse to the output queue and
E 157
			 * continue processing at the top of the loop.
			 * If there are any further characters in this
			 * <= OBUFSIZ chunk, the first should be a character
			 * requiring special handling by ttyoutput.
			 */
E 56
			tp->t_rocount = 0;
D 56
			i=b_to_q(cp,ce,&tp->t_outq);
			ce-=i;
			tk_nout+=ce;
			tp->t_col+=ce;
			cp+=ce;
			cc-=ce;
			if (i) {
E 56
I 56
			i = b_to_q(cp, ce, &tp->t_outq);
			ce -= i;
D 158
			tp->t_col += ce;
E 158
I 158
			tp->t_column += ce;
E 158
			cp += ce, cc -= ce, tk_nout += ce;
I 112
			tp->t_outcc += ce;
E 112
			if (i > 0) {
D 157
				/* out of c-lists, wait a bit */
E 157
I 157
				/* No Clists, wait a bit. */
E 157
E 56
				ttstart(tp);
D 120
				sleep((caddr_t)&lbolt, TTOPRI);
I 89
				uio->uio_iov->iov_base -= cc;
				uio->uio_iov->iov_len += cc;
				uio->uio_resid += cc;
				uio->uio_offset -= cc;
E 120
I 120
D 128
				if (error = tsleep((caddr_t)&lbolt,
				    TTOPRI | PCATCH, ttybuf, 0))
E 128
I 128
D 132
				if ((error = tsleep((caddr_t)&lbolt,
					    TTOPRI | PCATCH, ttybuf, 0)) ||
				    (error = ttclosed(tp)))
E 132
I 132
D 157
				if (error = ttysleep(tp, (caddr_t)&lbolt,
					    TTOPRI | PCATCH, ttybuf, 0))
E 157
I 157
				if (error = ttysleep(tp,
				    &lbolt, TTOPRI | PCATCH, ttybuf, 0))
E 157
E 132
E 128
					break;
E 120
				goto loop;
E 89
			}
D 56
			if (ce || tp->t_outq.c_cc > hiwat)
E 56
I 56
D 110
D 112
			if (tp->t_flags&FLUSHO || tp->t_outq.c_cc > hiwat)
E 112
I 112
D 157
			if (tp->t_lflag&FLUSHO || tp->t_outq.c_cc > hiwat)
E 157
I 157
			if (ISSET(tp->t_lflag, FLUSHO) ||
			    tp->t_outq.c_cc > hiwat)
E 157
E 112
E 110
I 110
			if (tp->t_lflag&FLUSHO || tp->t_outq.c_cc > hiwat)
E 110
E 56
D 120
				goto ovhiwat;
E 120
I 120
				break;
E 120
		}
I 112
		ttstart(tp);
E 112
I 110
		ttstart(tp);
E 110
	}
I 120
out:
	/*
D 157
	 * If cc is nonzero, we leave the uio structure inconsistent,
	 * as the offset and iov pointers have moved forward,
	 * but it doesn't matter (the call will either return short
	 * or restart with a new uio).
E 157
I 157
	 * If cc is nonzero, we leave the uio structure inconsistent, as the
	 * offset and iov pointers have moved forward, but it doesn't matter
	 * (the call will either return short or restart with a new uio).
E 157
	 */
	uio->uio_resid += cc;
E 120
D 110
D 112
	ttstart(tp);
E 112
E 110
D 45
	return(NULL);
E 45
I 45
D 50
	return (NULL);
E 50
I 50
	return (error);
I 120

E 120
E 50
E 45
D 112

E 112
ovhiwat:
D 56
	(void) spl5();
D 48
	u.u_base -= cc;
	u.u_offset -= cc;
	u.u_count += cc;
E 48
I 48
	uio->uio_iov->iov_base -= cc;
	uio->uio_iov->iov_len += cc;
	uio->uio_resid += cc;
	uio->uio_offset -= cc;
E 56
I 56
D 84
	s = spl5();
E 84
I 84
D 106
	s = spltty();
E 106
E 84
D 120
	if (cc != 0) {
		uio->uio_iov->iov_base -= cc;
		uio->uio_iov->iov_len += cc;
		uio->uio_resid += cc;
		uio->uio_offset -= cc;
	}
E 120
I 106
	ttstart(tp);
	s = spltty();
E 106
	/*
D 106
	 * This can only occur if FLUSHO
	 * is also set in t_flags.
E 106
I 106
D 110
D 112
	 * This can only occur if FLUSHO is set in t_flags,
E 112
I 112
	 * This can only occur if FLUSHO is set in t_lflag,
E 112
E 110
I 110
	 * This can only occur if FLUSHO is set in t_lflag,
E 110
	 * or if ttstart/oproc is synchronous (or very fast).
E 106
	 */
E 56
E 48
	if (tp->t_outq.c_cc <= hiwat) {
D 56
		(void) spl0();
E 56
I 56
		splx(s);
E 56
		goto loop;
	}
D 106
	ttstart(tp);
E 106
D 56
	if (tp->t_state & TS_NBIO) {
E 56
I 56
D 115
	if (tp->t_state&TS_NBIO) {
E 115
I 115
D 116
	if (flag&FNDELAY) {
E 116
I 116
	if (flag & IO_NDELAY) {
E 116
E 115
I 84
		splx(s);
I 120
		uio->uio_resid += cc;
E 120
E 84
E 56
D 48
		if (u.u_count == cnt)
E 48
I 48
D 157
		if (uio->uio_resid == cnt)
E 48
D 50
			u.u_error = EWOULDBLOCK;
		return (NULL);
E 50
I 50
			return (EWOULDBLOCK);
		return (0);
E 157
I 157
		return (uio->uio_resid == cnt ? EWOULDBLOCK : 0);
E 157
E 50
	}
D 157
	tp->t_state |= TS_ASLEEP;
D 120
	sleep((caddr_t)&tp->t_outq, TTOPRI);
E 120
I 120
D 132
	error = tsleep((caddr_t)&tp->t_outq, TTOPRI | PCATCH, ttyout, 0);
E 132
I 132
	error = ttysleep(tp, (caddr_t)&tp->t_outq, TTOPRI | PCATCH, ttyout, 0);
E 157
I 157
	SET(tp->t_state, TS_ASLEEP);
	error = ttysleep(tp, &tp->t_outq, TTOPRI | PCATCH, ttyout, 0);
E 157
E 132
E 120
D 56
	(void) spl0();
E 56
I 56
	splx(s);
I 120
D 128
	if (error)
E 128
I 128
D 132
	if (error || (error = ttclosed(tp)))
E 132
I 132
	if (error)
E 132
E 128
		goto out;
E 120
E 56
	goto loop;
}

/*
 * Rubout one character from the rawq of tp
 * as cleanly as possible.
 */
I 157
void
E 157
ttyrub(c, tp)
D 45
register c;
register struct tty *tp;
E 45
I 45
D 157
	register c;
E 157
I 157
	register int c;
E 157
	register struct tty *tp;
E 45
{
	register char *cp;
	register int savecol;
D 157
	int s;
	char *nextc();
E 157
I 157
	int tabc, s;
E 157

D 56
	if ((tp->t_flags&ECHO)==0)
E 56
I 56
D 110
D 112
	if ((tp->t_flags&ECHO) == 0)
E 112
I 112
D 127
	if ((tp->t_lflag&ECHO) == 0)
E 127
I 127
D 157
	if ((tp->t_lflag&ECHO) == 0 || (tp->t_lflag&EXTPROC))
E 157
I 157
	if (!ISSET(tp->t_lflag, ECHO) || ISSET(tp->t_lflag, EXTPROC))
E 157
E 127
E 112
E 110
I 110
	if ((tp->t_lflag&ECHO) == 0)
E 110
E 56
		return;
D 56
	tp->t_local &= ~LFLUSHO;
E 56
I 56
D 110
D 112
	tp->t_flags &= ~FLUSHO;
E 110
I 110
	tp->t_lflag &= ~FLUSHO;	
E 110
E 56
	c &= 0377;
D 56
	if (tp->t_local&LCRTBS) {
E 56
I 56
D 110
	if (tp->t_flags&CRTBS) {
E 112
I 112
D 157
	tp->t_lflag &= ~FLUSHO;	
	if (tp->t_lflag&ECHOE) {
E 157
I 157
	CLR(tp->t_lflag, FLUSHO);
	if (ISSET(tp->t_lflag, ECHOE)) {
E 157
E 112
E 110
I 110
	if (tp->t_lflag&ECHOE) {
E 110
E 56
		if (tp->t_rocount == 0) {
			/*
			 * Screwed by ttwrite; retype
			 */
			ttyretype(tp);
			return;
		}
I 110
		/* if tab or newline was escaped  - XXX - not 8bit */
E 110
D 56
		if (c==('\t'|0200) || c==('\n'|0200))
E 56
I 56
D 112
		if (c == ('\t'|0200) || c == ('\n'|0200))
E 112
I 112
D 157
		if (c == ('\t'|TTY_QUOTE) || c == ('\n'|TTY_QUOTE))
E 157
I 157
		if (c == ('\t' | TTY_QUOTE) || c == ('\n' | TTY_QUOTE))
E 157
E 112
E 56
			ttyrubo(tp, 2);
D 45
		else switch(partab[c&=0177] & 0177) {
E 45
I 45
D 56
		else switch (partab[c&=0177] & 0177) {
E 56
I 56
D 112
		else switch (partab[c&=0177]&0177) {
E 112
I 112
D 140
		else switch (partab[c&=0377]&077) {
E 140
I 140
D 159
		else switch (CCLASS(c &= TTY_CHARMASK)) {
E 140
E 112
E 56
E 45
D 157

E 157
		case ORDINARY:
I 110
#ifdef notdef
E 110
D 112
			if (tp->t_flags&LCASE && c >= 'A' && c <= 'Z')
				ttyrubo(tp, 2);
			else
I 110
#endif
E 110
				ttyrubo(tp, 1);
E 112
I 112
			ttyrubo(tp, 1);
E 112
			break;
D 157

		case VTAB:
E 157
		case BACKSPACE:
		case CONTROL:
D 157
		case RETURN:
E 157
I 134
D 137
		case NEWLINE:	/* XXX can't happen ? */
E 137
I 137
		case NEWLINE:
E 137
E 134
D 56
			if (tp->t_local & LCTLECH)
E 56
I 56
D 110
D 112
			if (tp->t_flags&CTLECH)
E 112
I 112
D 157
			if (tp->t_lflag&ECHOCTL)
E 157
I 157
		case RETURN:
		case VTAB:
			if (ISSET(tp->t_lflag, ECHOCTL))
E 157
E 112
E 110
I 110
			if (tp->t_lflag&ECHOCTL)
E 110
E 56
				ttyrubo(tp, 2);
			break;
D 157

D 112
		case TAB:
E 112
I 112
		case TAB: {
			int c;

E 157
I 157
		case TAB:
E 157
E 112
			if (tp->t_rocount < tp->t_rawq.c_cc) {
				ttyretype(tp);
				return;
			}
D 84
			s = spl5();
E 84
I 84
			s = spltty();
E 84
D 158
			savecol = tp->t_col;
E 158
I 158
			savecol = tp->t_column;
E 158
D 56
			tp->t_lstate |= LSCNTTB;
			tp->t_local |= LFLUSHO;
E 56
I 56
D 157
			tp->t_state |= TS_CNTTB;
D 110
D 112
			tp->t_flags |= FLUSHO;
E 112
I 112
			tp->t_lflag |= FLUSHO;
E 157
I 157
			SET(tp->t_state, TS_CNTTB);
			SET(tp->t_lflag, FLUSHO);
E 157
E 112
E 110
I 110
			tp->t_lflag |= FLUSHO;
E 110
E 56
D 158
			tp->t_col = tp->t_rocol;
E 158
I 158
			tp->t_column = tp->t_rocol;
E 158
D 56
			for (cp = tp->t_rawq.c_cf; cp; cp = nextc(&tp->t_rawq, cp))
E 56
I 56
			cp = tp->t_rawq.c_cf;
D 112
			for (; cp; cp = nextc(&tp->t_rawq, cp))
E 56
				ttyecho(*cp, tp);
D 56
			tp->t_local &= ~LFLUSHO;
			tp->t_lstate &= ~LSCNTTB;
E 56
I 56
D 110
			tp->t_flags &= ~FLUSHO;
E 112
I 112
D 117
			c = *cp;	/* XXX FIX NEXTC */
E 117
I 117
			if (cp)
D 157
				c = *cp;	/* XXX FIX NEXTC */
E 117
			for (; cp; cp = nextc(&tp->t_rawq, cp, &c))
				ttyecho(c, tp);
			tp->t_lflag &= ~FLUSHO;
E 112
E 110
I 110
			tp->t_lflag &= ~FLUSHO;
E 110
			tp->t_state &= ~TS_CNTTB;
E 157
I 157
				tabc = *cp;	/* XXX FIX NEXTC */
			for (; cp; cp = nextc(&tp->t_rawq, cp, &tabc))
				ttyecho(tabc, tp);
			CLR(tp->t_lflag, FLUSHO);
			CLR(tp->t_state, TS_CNTTB);
E 157
E 56
			splx(s);
E 159
I 159
		else {
			CLR(c, ~TTY_CHARMASK);
			switch (CCLASS(c)) {
			case ORDINARY:
				ttyrubo(tp, 1);
				break;
			case BACKSPACE:
			case CONTROL:
			case NEWLINE:
			case RETURN:
			case VTAB:
				if (ISSET(tp->t_lflag, ECHOCTL))
					ttyrubo(tp, 2);
				break;
			case TAB:
				if (tp->t_rocount < tp->t_rawq.c_cc) {
					ttyretype(tp);
					return;
				}
				s = spltty();
				savecol = tp->t_column;
				SET(tp->t_state, TS_CNTTB);
				SET(tp->t_lflag, FLUSHO);
				tp->t_column = tp->t_rocol;
				cp = tp->t_rawq.c_cf;
				if (cp)
					tabc = *cp;	/* XXX FIX NEXTC */
				for (; cp; cp = nextc(&tp->t_rawq, cp, &tabc))
					ttyecho(tabc, tp);
				CLR(tp->t_lflag, FLUSHO);
				CLR(tp->t_state, TS_CNTTB);
				splx(s);
E 159
D 157
			/*
			 * savecol will now be length of the tab
			 */
E 157
I 157

D 159
			/* savecol will now be length of the tab. */
E 157
D 158
			savecol -= tp->t_col;
			tp->t_col += savecol;
E 158
I 158
			savecol -= tp->t_column;
			tp->t_column += savecol;
E 158
			if (savecol > 8)
				savecol = 8;		/* overflow screw */
			while (--savecol >= 0)
D 157
				(void) ttyoutput('\b', tp);
E 157
I 157
				(void)ttyoutput('\b', tp);
E 157
			break;
I 157
		default:			/* XXX */
E 159
I 159
				/* savecol will now be length of the tab. */
				savecol -= tp->t_column;
				tp->t_column += savecol;
				if (savecol > 8)
					savecol = 8;	/* overflow screw */
				while (--savecol >= 0)
					(void)ttyoutput('\b', tp);
				break;
			default:			/* XXX */
E 159
#define	PANICSTR	"ttyrub: would panic c = %d, val = %d\n"
D 159
			(void)printf(PANICSTR, c, CCLASS(c));
E 159
I 159
				(void)printf(PANICSTR, c, CCLASS(c));
E 159
#ifdef notdef
D 159
			panic(PANICSTR, c, CCLASS(c));
E 159
I 159
				panic(PANICSTR, c, CCLASS(c));
E 159
#endif
I 159
			}
E 159
E 157
I 112
		}
E 112
D 157

		default:
I 115
			/* XXX */
E 115
D 112
			panic("ttyrub");
E 112
I 112
			printf("ttyrub: would panic c = %d, val = %d\n",
D 140
				c, partab[c&=0377]&077);
E 140
I 140
				c, CCLASS(c));
E 140
			/*panic("ttyrub");*/
E 157
I 157
	} else if (ISSET(tp->t_lflag, ECHOPRT)) {
		if (!ISSET(tp->t_state, TS_ERASE)) {
			SET(tp->t_state, TS_ERASE);
			(void)ttyoutput('\\', tp);
E 157
E 112
		}
D 56
	} else if (tp->t_local&LPRTERA) {
		if ((tp->t_lstate&LSERASE) == 0) {
E 56
I 56
D 110
D 112
	} else if (tp->t_flags&PRTERA) {
E 112
I 112
D 157
	} else if (tp->t_lflag&ECHOPRT) {
E 112
E 110
I 110
	} else if (tp->t_lflag&ECHOPRT) {
E 110
		if ((tp->t_state&TS_ERASE) == 0) {
E 56
			(void) ttyoutput('\\', tp);
D 56
			tp->t_lstate |= LSERASE;
E 56
I 56
			tp->t_state |= TS_ERASE;
E 56
		}
E 157
		ttyecho(c, tp);
	} else
D 110
D 112
		ttyecho(tp->t_erase, tp);
E 112
I 112
		ttyecho(tp->t_cc[VERASE], tp);
E 112
E 110
I 110
		ttyecho(tp->t_cc[VERASE], tp);
E 110
D 157
	tp->t_rocount--;
E 157
I 157
	--tp->t_rocount;
E 157
}

/*
D 157
 * Crt back over cnt chars perhaps
 * erasing them.
E 157
I 157
 * Back over cnt characters, erasing them.
E 157
 */
I 157
static void
E 157
ttyrubo(tp, cnt)
D 45
register struct tty *tp;
int cnt;
E 45
I 45
	register struct tty *tp;
	int cnt;
E 45
{
I 56
D 110
D 112
	register char *rubostring = tp->t_flags&CRTERA ? "\b \b" : "\b";
E 112
E 110
I 110
	register char *rubostring = tp->t_lflag&ECHOE ? "\b \b" : "\b";
E 110
E 56

D 157
	while (--cnt >= 0)
D 56
		ttyout(tp->t_local&LCRTERA ? "\b \b" : "\b", tp);
E 56
I 56
D 112
		ttyout(rubostring, tp);
E 112
I 112
D 120
		ttyout("\b \b", tp);
E 120
I 120
		ttyoutstr("\b \b", tp);
E 157
I 157
	while (cnt-- > 0) {
		(void)ttyoutput('\b', tp);
		(void)ttyoutput(' ', tp);
		(void)ttyoutput('\b', tp);
	}
E 157
E 120
E 112
E 56
}

/*
D 157
 * Reprint the rawq line.
 * We assume c_cc has already been checked.
E 157
I 157
 * ttyretype --
 *	Reprint the rawq line.  Note, it is assumed that c_cc has already
 *	been checked.
E 157
 */
I 157
void
E 157
ttyretype(tp)
D 45
register struct tty *tp;
E 45
I 45
	register struct tty *tp;
E 45
{
	register char *cp;
D 157
	char *nextc();
E 157
D 112
	int s;
E 112
I 112
	int s, c;
E 112

I 157
	/* Echo the reprint character. */
E 157
D 56
	if (tlun.t_rprntc != 0377)
		ttyecho(tlun.t_rprntc, tp);
E 56
I 56
D 110
D 112
	if (tp->t_rprntc != 0377)
		ttyecho(tp->t_rprntc, tp);
E 112
I 112
	if (tp->t_cc[VREPRINT] != _POSIX_VDISABLE)
		ttyecho(tp->t_cc[VREPRINT], tp);
E 112
E 110
I 110
	if (tp->t_cc[VREPRINT] != POSIX_V_DISABLE)
		ttyecho(tp->t_cc[VREPRINT], tp);
E 110
E 56
D 157
	(void) ttyoutput('\n', tp);
E 157
I 157

	(void)ttyoutput('\n', tp);

	/*
	 * XXX
	 * FIX: NEXTC IS BROKEN - DOESN'T CHECK QUOTE
	 * BIT OF FIRST CHAR.
	 */
E 157
D 84
	s = spl5();
E 84
I 84
	s = spltty();
E 84
D 112
	for (cp = tp->t_canq.c_cf; cp; cp = nextc(&tp->t_canq, cp))
		ttyecho(*cp, tp);
	for (cp = tp->t_rawq.c_cf; cp; cp = nextc(&tp->t_rawq, cp))
		ttyecho(*cp, tp);
E 112
I 112
D 157
	/*** XXX *** FIX *** NEXTC IS BROKEN - DOESN'T CHECK QUOTE
	  BIT OF FIRST CHAR ****/
	for (cp = tp->t_canq.c_cf, c=(cp?*cp:0); cp; cp = nextc(&tp->t_canq, cp, &c)) {
E 157
I 157
	for (cp = tp->t_canq.c_cf, c = (cp != NULL ? *cp : 0);
	    cp != NULL; cp = nextc(&tp->t_canq, cp, &c))
E 157
		ttyecho(c, tp);
D 157
	}
	for (cp = tp->t_rawq.c_cf, c=(cp?*cp:0); cp; cp = nextc(&tp->t_rawq, cp, &c)) {
E 157
I 157
	for (cp = tp->t_rawq.c_cf, c = (cp != NULL ? *cp : 0);
	    cp != NULL; cp = nextc(&tp->t_rawq, cp, &c))
E 157
		ttyecho(c, tp);
D 157
	}
E 112
D 56
	tp->t_lstate &= ~LSERASE;
E 56
I 56
	tp->t_state &= ~TS_ERASE;
E 157
I 157
	CLR(tp->t_state, TS_ERASE);
E 157
E 56
	splx(s);
I 157

E 157
	tp->t_rocount = tp->t_rawq.c_cc;
	tp->t_rocol = 0;
}

/*
D 110
D 112
 * Echo a typed character to the terminal
E 112
I 112
 * Echo a typed character to the terminal.
E 112
E 110
I 110
 * Echo a typed character to the terminal.
E 110
 */
I 157
static void
E 157
ttyecho(c, tp)
D 45
register c;
register struct tty *tp;
E 45
I 45
D 157
	register c;
E 157
I 157
	register int c;
E 157
	register struct tty *tp;
E 45
{
D 112

E 112
I 110
	c &= 0377;
E 110
D 56
	if ((tp->t_lstate & LSCNTTB) == 0)
		tp->t_local &= ~LFLUSHO;
E 56
I 56
D 157
	if ((tp->t_state&TS_CNTTB) == 0)
D 110
D 112
		tp->t_flags &= ~FLUSHO;
E 56
	if ((tp->t_flags&ECHO) == 0)
E 112
I 112
		tp->t_lflag &= ~FLUSHO;
D 120
	if ((tp->t_lflag&ECHO) == 0 && !(tp->t_lflag&ECHONL && c == '\n'))
E 120
I 120
D 127
	if ((tp->t_lflag&ECHO) == 0 && ((tp->t_lflag&ECHONL) == 0 || c == '\n'))
E 127
I 127
D 137
	if (((tp->t_lflag&ECHO) == 0 && ((tp->t_lflag&ECHONL) == 0 ||
					  c == '\n')) || (tp->t_lflag&EXTPROC))
E 137
I 137
	if (((tp->t_lflag&ECHO) == 0 &&
	    ((tp->t_lflag&ECHONL) == 0 || c == '\n')) || (tp->t_lflag&EXTPROC))
E 157
I 157

	if (!ISSET(tp->t_state, TS_CNTTB))
		CLR(tp->t_lflag, FLUSHO);
	if ((!ISSET(tp->t_lflag, ECHO) &&
	    (!ISSET(tp->t_lflag, ECHONL) || c == '\n')) ||
	    ISSET(tp->t_lflag, EXTPROC))
E 157
E 137
E 127
E 120
E 112
E 110
I 110
		tp->t_lflag &= ~FLUSHO;
	if ((tp->t_lflag&ECHO) == 0 && !(tp->t_lflag&ECHONL && c == '\n'))
E 110
		return;
D 110
D 112
	c &= 0377;
	if (tp->t_flags&RAW) {
		(void) ttyoutput(c, tp);
		return;
	}
	if (c == '\r' && tp->t_flags&CRMOD)
		c = '\n';
D 56
	if (tp->t_local&LCTLECH) {
E 56
I 56
	if (tp->t_flags&CTLECH) {
E 110
I 110
	if (tp->t_lflag&ECHOCTL) {
E 110
E 56
		if ((c&0177) <= 037 && c!='\t' && c!='\n' || (c&0177)==0177) {
E 112
I 112
D 157
	if (tp->t_lflag&ECHOCTL) {
D 120
		if ((c&TTY_CHARMASK)<=037 && c!='\t' && c!='\n' || c==0177) {
E 120
I 120
		if ((c&TTY_CHARMASK) <= 037 && c != '\t' && c != '\n' ||
D 153
		    c == 0177) {
E 153
I 153
		    (c&TTY_CHARMASK) == 0177) {
E 153
E 120
E 112
			(void) ttyoutput('^', tp);
D 112
			c &= 0177;
E 112
I 112
			c &= TTY_CHARMASK;
E 112
			if (c == 0177)
				c = '?';
I 110
#ifdef notdef
E 110
D 112
			else if (tp->t_flags&LCASE)
				c += 'a' - 1;
E 112
I 110
#endif
E 110
			else
				c += 'A' - 1;
		}
E 157
I 157
	if (ISSET(tp->t_lflag, ECHOCTL) &&
D 159
	    ((c & TTY_CHARMASK) <= 037 && c != '\t' && c != '\n' ||
	    (c & TTY_CHARMASK) == 0177)) {
E 159
I 159
	    (ISSET(c, TTY_CHARMASK) <= 037 && c != '\t' && c != '\n' ||
	    ISSET(c, TTY_CHARMASK) == 0177)) {
E 159
		(void)ttyoutput('^', tp);
D 159
		c &= TTY_CHARMASK;
E 159
I 159
		CLR(c, ~TTY_CHARMASK);
E 159
		if (c == 0177)
			c = '?';
		else
			c += 'A' - 1;
E 157
	}
D 90
	if ((tp->t_flags&LCASE) && (c >= 'A' && c <= 'Z'))
		c += 'a' - 'A';
E 90
D 56
	(void) ttyoutput(c & 0177, tp);
E 56
I 56
D 112
	(void) ttyoutput(c&0177, tp);
E 112
I 112
D 157
	(void) ttyoutput(c, tp);
E 157
I 157
	(void)ttyoutput(c, tp);
E 157
E 112
E 56
D 110
}

/*
D 112
 * Is c a break char for tp?
 */
ttbreakc(c, tp)
D 45
register c;
register struct tty *tp;
E 45
I 45
	register c;
	register struct tty *tp;
E 45
{
D 56
	return (c == '\n' || c == tun.t_eofc || c == tun.t_brkc ||
E 56
I 56
	return (c == '\n' || c == tp->t_eofc || c == tp->t_brkc ||
E 56
		c == '\r' && (tp->t_flags&CRMOD));
E 110
}

/*
E 112
D 157
 * send string cp to tp
 */
D 120
ttyout(cp, tp)
E 120
I 120
ttyoutstr(cp, tp)
E 120
D 45
register char *cp;
register struct tty *tp;
E 45
I 45
	register char *cp;
	register struct tty *tp;
E 45
{
	register char c;

	while (c = *cp++)
		(void) ttyoutput(c, tp);
}

I 140
/*
E 157
 * Wake up any readers on a tty.
 */
I 157
void
E 157
E 140
ttwakeup(tp)
D 137
	struct tty *tp;
E 137
I 137
	register struct tty *tp;
E 137
{

D 148
	if (tp->t_rsel) {
		selwakeup(tp->t_rsel, tp->t_state&TS_RCOLL);
		tp->t_state &= ~TS_RCOLL;
		tp->t_rsel = 0;
	}
E 148
I 148
	selwakeup(&tp->t_rsel);
E 148
I 63
D 157
	if (tp->t_state & TS_ASYNC)
D 112
		gsignal(tp->t_pgrp, SIGIO); 
E 112
I 112
D 118
		gsignal(tp->t_pgid, SIGIO); 
E 118
I 118
D 127
		pgsignal(tp->t_pgrp, SIGIO); 
E 127
I 127
		pgsignal(tp->t_pgrp, SIGIO, 1); 
E 157
I 157
	if (ISSET(tp->t_state, TS_ASYNC))
		pgsignal(tp->t_pgrp, SIGIO, 1);
E 157
E 127
E 118
E 112
E 63
	wakeup((caddr_t)&tp->t_rawq);
I 112
}

/*
I 138
 * Look up a code for a specified speed in a conversion table;
 * used by drivers to map software speed values to hardware parameters.
 */
I 157
int
E 157
ttspeedtab(speed, table)
I 147
	int speed;
E 147
	register struct speedtab *table;
{

	for ( ; table->sp_speed != -1; table++)
		if (table->sp_speed == speed)
			return (table->sp_code);
	return (-1);
}

/*
E 138
D 157
 * set tty hi and low water marks
E 157
I 157
 * Set tty hi and low water marks.
E 157
 *
 * Try to arrange the dynamics so there's about one second
 * from hi to low water.
D 157
 * 
E 157
I 157
 *
E 157
 */
I 157
void
E 157
ttsetwater(tp)
	struct tty *tp;
{
D 157
	register cps = tp->t_ospeed / 10;
	register x;
E 157
I 157
	register int cps, x;
E 157

D 157
#define clamp(x, h, l) ((x)>h ? h : ((x)<l) ? l : (x))
	tp->t_lowat = x = clamp(cps/2, TTMAXLOWAT, TTMINLOWAT);
E 157
I 157
#define CLAMP(x, h, l)	((x) > h ? h : ((x) < l) ? l : (x))

	cps = tp->t_ospeed / 10;
	tp->t_lowat = x = CLAMP(cps / 2, TTMAXLOWAT, TTMINLOWAT);
E 157
	x += cps;
D 157
	x = clamp(x, TTMAXHIWAT, TTMINHIWAT);
E 157
I 157
	x = CLAMP(x, TTMAXHIWAT, TTMINHIWAT);
E 157
	tp->t_hiwat = roundup(x, CBSIZE);
D 157
#undef clamp
E 157
I 157
#undef	CLAMP
E 157
}

D 137
ttspeedtab(speed, table)
	struct speedtab table[];
{
	register int i;

	for (i = 0; table[i].sp_speed != -1; i++)
		if (table[i].sp_speed == speed)
			return(table[i].sp_code);
	return(-1);
I 117
}

I 121
int ttyhostname = 0;
E 137
E 121
/*
D 143
 * (^T)
E 143
 * Report on state of foreground process group.
 */
I 157
void
E 157
ttyinfo(tp)
D 143
	struct tty *tp;
E 143
I 143
	register struct tty *tp;
E 143
{
D 121
	register struct proc *p;
E 121
I 121
D 143
	register struct proc *p, *pick = NULL;
D 135
	register char *cp = hostname;
E 135
	int x, s;
E 143
I 143
	register struct proc *p, *pick;
E 143
	struct timeval utime, stime;
D 126
#define	pgtok(a)	((a)/(1024/NBPG))
E 126
I 126
D 143
#define	pgtok(a)	(((a)*NBPG)/1024)
E 143
I 143
	int tmp;
E 143
E 126
E 121
D 118
	struct pgrp *pg = pgfind(tp->t_pgid);
E 118

D 157
	if (ttycheckoutq(tp,0) == 0) 
E 157
I 157
	if (ttycheckoutq(tp,0) == 0)
E 157
		return;
I 121
D 143
	/* 
D 135
	 * hostname 
	 */
	if (ttyhostname) {
		if (*cp == '\0')
			ttyprintf(tp, "amnesia");
		else
			while (*cp && *cp != '.')
				tputchar(*cp++, tp);
		tputchar(' ');
	}
	/* 
E 135
	 * load average 
	 */
	x = (averunnable[0] * 100 + FSCALE/2) >> FSHIFT;
	ttyprintf(tp, "load: %d.", x/100);
	ttyoutint(x%100, 10, 2, tp);
E 143
I 143

	/* Print load average. */
D 149
	tmp = (averunnable[0] * 100 + FSCALE / 2) >> FSHIFT;
E 149
I 149
	tmp = (averunnable.ldavg[0] * 100 + FSCALE / 2) >> FSHIFT;
E 149
	ttyprintf(tp, "load: %d.%02d ", tmp / 100, tmp % 100);

E 143
E 121
D 118
	if (pg == NULL)
E 118
I 118
	if (tp->t_session == NULL)
D 121
		ttyprintf(tp, "kernel: not a controlling terminal\n");
	else if (tp->t_pgrp == NULL || 
		(p = tp->t_pgrp->pg_mem) == NULL)
E 118
		ttyprintf(tp, "kernel: no foreground process group\n");
E 121
I 121
D 143
		ttyprintf(tp, " not a controlling terminal\n");
E 143
I 143
		ttyprintf(tp, "not a controlling terminal\n");
E 143
	else if (tp->t_pgrp == NULL)
D 143
		ttyprintf(tp, " no foreground process group\n");
E 143
I 143
		ttyprintf(tp, "no foreground process group\n");
E 143
D 167
	else if ((p = tp->t_pgrp->pg_mem) == NULL)
E 167
I 167
	else if ((p = tp->t_pgrp->pg_members.lh_first) == 0)
E 167
D 143
		ttyprintf(tp, " empty foreground process group\n");
E 143
I 143
		ttyprintf(tp, "empty foreground process group\n");
E 143
E 121
D 118
	else if ((p = pg->pg_mem) == NULL)
		ttyprintf(tp, "kernel: empty process group: %d\n", 
			tp->t_pgid);
E 118
	else {
D 121
		int i = 0;
I 118

E 121
I 121
D 143
		/* pick interesting process */
E 121
E 118
		for (; p != NULL; p = p->p_pgrpnxt) {
E 143
I 143
		/* Pick interesting process. */
D 167
		for (pick = NULL; p != NULL; p = p->p_pgrpnxt)
E 167
I 167
		for (pick = NULL; p != 0; p = p->p_pglist.le_next)
E 167
E 143
D 121
			ttyprintf(tp, 
			 "kernel: pid: %d state: %x wchan: %x ticks: %d\n",
				p->p_pid, p->p_stat, p->p_wchan, p->p_cpticks);
			if (++i > 6) {
				ttyprintf(tp, "kernel: more...\n");
				break;
			}
E 121
I 121
			if (proc_compare(pick, p))
				pick = p;
E 121
D 143
		}
I 121
		ttyprintf(tp, "  cmd: %s %d [%s] ",
			pick->p_comm, pick->p_pid,
D 138
			pick->p_wmesg ? pick->p_wmesg : "running");
E 138
I 138
			pick->p_stat == SRUN ? "running" :
			pick->p_wmesg ? pick->p_wmesg : "iowait");
E 138
		/* 
		 * cpu time 
E 143
I 143

		ttyprintf(tp, " cmd: %s %d [%s] ", pick->p_comm, pick->p_pid,
		    pick->p_stat == SRUN ? "running" :
		    pick->p_wmesg ? pick->p_wmesg : "iowait");

D 150
		/*
		 * Lock out clock if process is running; get user/system
		 * cpu time.
E 143
		 */
D 137
		if (u.u_procp == pick)
E 137
I 137
		if (curproc == pick)
E 137
D 143
			s = splclock();
E 143
I 143
			tmp = splclock();
E 143
		utime = pick->p_utime;
		stime = pick->p_stime;
D 137
		if (u.u_procp == pick)
E 137
I 137
		if (curproc == pick)
E 137
D 143
			splx(s);
		/* user time */
		x = (utime.tv_usec + 5000) / 10000; /* scale to 100's */
		ttyoutint(utime.tv_sec, 10, 1, tp);
		tputchar('.', tp);
		ttyoutint(x, 10, 2, tp);
		tputchar('u', tp);
		tputchar(' ', tp);
		/* system time */
		x = (stime.tv_usec + 5000) / 10000; /* scale to 100's */
		ttyoutint(stime.tv_sec, 10, 1, tp);
		tputchar('.', tp);
		ttyoutint(x, 10, 2, tp);
		tputchar('s', tp);
		tputchar(' ', tp);
		/* 
		 * pctcpu 
		 */
		x = pick->p_pctcpu * 10000 + FSCALE/2 >> FSHIFT;
		ttyoutint(x/100, 10, 1, tp);
#ifdef notdef	/* do we really want this ??? */
		tputchar('.', tp);
		ttyoutint(x%100, 10, 2, tp);
#endif
D 136
		ttyprintf(tp, "%% %dk\n", pgtok(pick->p_ssize + pick->p_dsize));
E 136
I 136
D 137
		ttyprintf(tp, "%% %dk\n", pgtok(pick->p_rssize));
E 137
I 137
		ttyprintf(tp, "%% %dk\n", pgtok(pick->p_vmspace->vm_rssize));
E 137
E 136
E 121
	}
I 121
	tp->t_rocount = 0;	/* so pending input will be retyped if BS */
E 121
}
E 143
I 143
			splx(tmp);
E 150
I 150
		calcru(pick, &utime, &stime, NULL);
E 150
E 143

I 121
D 143
ttyoutint(n, base, min, tp)
	register int n, base, min;
	register struct tty *tp;
{
	char info[16];
	register char *p = info;
E 143
I 143
		/* Print user time. */
		ttyprintf(tp, "%d.%02du ",
		    utime.tv_sec, (utime.tv_usec + 5000) / 10000);
E 143

D 143
	while (--min >= 0 || n) {
		*p++ = "0123456789abcdef"[n%base];
		n /= base;
E 143
I 143
		/* Print system time. */
		ttyprintf(tp, "%d.%02ds ",
		    stime.tv_sec, (stime.tv_usec + 5000) / 10000);

#define	pgtok(a)	(((a) * NBPG) / 1024)
		/* Print percentage cpu, resident set size. */
		tmp = pick->p_pctcpu * 10000 + FSCALE / 2 >> FSHIFT;
		ttyprintf(tp, "%d%% %dk\n",
D 147
		   tmp / 100, pgtok(pick->p_vmspace->vm_rssize));
E 147
I 147
		    tmp / 100,
		    pick->p_stat == SIDL || pick->p_stat == SZOMB ? 0 :
D 162
			pgtok(pick->p_vmspace->vm_rssize));
E 162
I 162
#ifdef pmap_resident_count
			pgtok(pmap_resident_count(&pick->p_vmspace->vm_pmap))
#else
			pgtok(pick->p_vmspace->vm_rssize)
#endif
			);
E 162
E 147
E 143
	}
D 143
	while (p > info)
		ttyoutput(*--p, tp);
E 143
I 143
	tp->t_rocount = 0;	/* so pending input will be retyped if BS */
E 143
}

/*
 * Returns 1 if p2 is "better" than p1
 *
 * The algorithm for picking the "interesting" process is thus:
 *
D 159
 *	1) (Only foreground processes are eligable - implied)
 *	2) Runnable processes are favored over anything
 *	   else.  The runner with the highest cpu
 *	   utilization is picked (p_cpu).  Ties are
E 159
I 159
 *	1) Only foreground processes are eligible - implied.
 *	2) Runnable processes are favored over anything else.  The runner
 *	   with the highest cpu utilization is picked (p_estcpu).  Ties are
E 159
 *	   broken by picking the highest pid.
D 159
 *	3  Next, the sleeper with the shortest sleep
 *	   time is favored.  With ties, we pick out
 *	   just "short-term" sleepers (SSINTR == 0).
 *	   Further ties are broken by picking the highest
 *	   pid.
 *
E 159
I 159
 *	3) The sleeper with the shortest sleep time is next.  With ties,
 *	   we pick out just "short-term" sleepers (P_SINTR == 0).
 *	4) Further ties are broken by picking the highest pid.
E 159
 */
D 159
#define isrun(p)	(((p)->p_stat == SRUN) || ((p)->p_stat == SIDL))
E 159
I 159
#define ISRUN(p)	(((p)->p_stat == SRUN) || ((p)->p_stat == SIDL))
E 159
I 135
#define TESTAB(a, b)    ((a)<<1 | (b))
#define ONLYA   2
#define ONLYB   1
#define BOTH    3
I 159

E 159
D 157

E 157
I 143
static int
E 143
E 135
proc_compare(p1, p2)
	register struct proc *p1, *p2;
{

	if (p1 == NULL)
		return (1);
	/*
	 * see if at least one of them is runnable
	 */
D 135
	switch (isrun(p1)<<1 | isrun(p2)) {
	case 0x01:
		return (1);
	case 0x10:
E 135
I 135
D 159
	switch (TESTAB(isrun(p1), isrun(p2))) {
E 159
I 159
	switch (TESTAB(ISRUN(p1), ISRUN(p2))) {
E 159
	case ONLYA:
E 135
		return (0);
D 135
	case 0x11:
E 135
I 135
	case ONLYB:
		return (1);
	case BOTH:
E 135
		/*
		 * tie - favor one with highest recent cpu utilization
		 */
D 159
		if (p2->p_cpu > p1->p_cpu)
E 159
I 159
		if (p2->p_estcpu > p1->p_estcpu)
E 159
			return (1);
D 159
		if (p1->p_cpu > p2->p_cpu)
E 159
I 159
		if (p1->p_estcpu > p2->p_estcpu)
E 159
			return (0);
		return (p2->p_pid > p1->p_pid);	/* tie - return highest pid */
	}
I 135
	/*
 	 * weed out zombies
	 */
	switch (TESTAB(p1->p_stat == SZOMB, p2->p_stat == SZOMB)) {
	case ONLYA:
		return (1);
	case ONLYB:
		return (0);
	case BOTH:
		return (p2->p_pid > p1->p_pid); /* tie - return highest pid */
	}
E 135
D 157
	/* 
E 157
I 157
	/*
E 157
	 * pick the one with the smallest sleep time
	 */
	if (p2->p_slptime > p1->p_slptime)
		return (0);
	if (p1->p_slptime > p2->p_slptime)
		return (1);
	/*
	 * favor one sleeping in a non-interruptible sleep
	 */
D 157
	if (p1->p_flag&SSINTR && (p2->p_flag&SSINTR) == 0)
E 157
I 157
D 159
	if (p1->p_flag & SSINTR && (p2->p_flag & SSINTR) == 0)
E 159
I 159
	if (p1->p_flag & P_SINTR && (p2->p_flag & P_SINTR) == 0)
E 159
E 157
		return (1);
D 157
	if (p2->p_flag&SSINTR && (p1->p_flag&SSINTR) == 0)
E 157
I 157
D 159
	if (p2->p_flag & SSINTR && (p1->p_flag & SSINTR) == 0)
E 159
I 159
	if (p2->p_flag & P_SINTR && (p1->p_flag & P_SINTR) == 0)
E 159
E 157
		return (0);
D 137
	return(p2->p_pid > p1->p_pid);		/* tie - return highest pid */
E 137
I 137
	return (p2->p_pid > p1->p_pid);		/* tie - return highest pid */
E 137
}
I 135

I 137
D 139
/* XXX move to subr_prf.c */
E 137
E 135
E 121
#define TOTTY	0x2	/* XXX should be in header */
/*VARARGS2*/
ttyprintf(tp, fmt, x1)
D 118
	register struct tty *tp;
E 118
I 118
	struct tty *tp;
E 118
	char *fmt;
	unsigned x1;
{
D 118
	prf(fmt, &x1, TOTTY, tp);
E 118
I 118
	prf(fmt, &x1, TOTTY, (caddr_t)tp);
}

E 139
/*
 * Output char to tty; console putchar style.
 */
I 157
int
E 157
tputchar(c, tp)
	int c;
	struct tty *tp;
{
D 157
	register s = spltty();
E 157
I 157
	register int s;
E 157

D 137
	if ((tp->t_state & (TS_CARR_ON | TS_ISOPEN)) 
	    == (TS_CARR_ON | TS_ISOPEN)) {
E 137
I 137
D 157
	if ((tp->t_state & (TS_CARR_ON|TS_ISOPEN)) == (TS_CARR_ON|TS_ISOPEN)) {
E 137
		if (c == '\n')
			(void) ttyoutput('\r', tp);
		(void) ttyoutput(c, tp);
		ttstart(tp);
E 157
I 157
	s = spltty();
	if (ISSET(tp->t_state,
	    TS_CARR_ON | TS_ISOPEN) != (TS_CARR_ON | TS_ISOPEN)) {
E 157
		splx(s);
D 157
		return (0);
E 157
I 157
		return (-1);
E 157
	}
I 157
	if (c == '\n')
		(void)ttyoutput('\r', tp);
	(void)ttyoutput(c, tp);
	ttstart(tp);
E 157
	splx(s);
D 157
	return (-1);
E 157
I 157
	return (0);
E 157
I 132
}

I 133
/*
D 140
 * Sleep on chan.
 *
 * Return ERESTART if tty changed while we napped.
E 140
I 140
D 157
 * Sleep on chan, returning ERESTART if tty changed
 * while we napped and returning any errors (e.g. EINTR/ETIMEDOUT)
 * reported by tsleep.  If the tty is revoked, restarting a pending
 * call will redo validation done at the start of the call.
E 157
I 157
 * Sleep on chan, returning ERESTART if tty changed while we napped and
 * returning any errors (e.g. EINTR/ETIMEDOUT) reported by tsleep.  If
 * the tty is revoked, restarting a pending call will redo validation done
 * at the start of the call.
E 157
E 140
 */
I 157
int
E 157
E 133
ttysleep(tp, chan, pri, wmesg, timo)
	struct tty *tp;
D 157
	caddr_t chan;
	int pri;
E 157
I 157
	void *chan;
	int pri, timo;
E 157
	char *wmesg;
D 157
	int timo;
E 157
{
	int error;
D 157
	short gen = tp->t_gen;
E 157
I 157
	short gen;
E 157

I 157
	gen = tp->t_gen;
E 157
	if (error = tsleep(chan, pri, wmesg, timo))
		return (error);
D 157
	if (tp->t_gen != gen)
		return (ERESTART);
	return (0);
E 157
I 157
	return (tp->t_gen == gen ? 0 : ERESTART);
E 157
E 132
E 118
E 117
E 112
}
D 88

D 56
ttsignal(tp, signo)
	struct tty *tp;
	int signo;
E 56
I 56
D 61
#ifndef vax
E 61
I 61
D 65
#if !defined(vax) && !defined(sun)
E 65
I 65
#if !defined(vax)
E 65
E 61
scanc(size, cp, table, mask)
	register int size;
	register char *cp, table[];
	register int mask;
E 56
{
I 56
	register int i = 0;
E 56

D 56
	gsignal(tp->t_pgrp, signo);
E 56
I 56
	while ((table[*(u_char *)(cp + i)]&mask) == 0 && i < size)
		i++;
D 76
	return (i);
E 76
I 76
	return (size - i);
E 76
E 56
}
I 56
#endif
E 88
E 56
E 44
E 43
E 1
