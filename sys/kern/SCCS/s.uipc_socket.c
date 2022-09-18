h41869
s 00001/00001/01013
d D 8.6 95/05/02 11:28:58 mckusick 160 159
c fix bug pointed out by Stevens in his vol II book
e
s 00002/00002/01012
d D 8.5 95/05/01 16:37:12 mckusick 159 158
c limit process to 327.67 rather than 227 seconds timeout;
c return correct timeout from getsockopt (from rstevens@noao.edu)
e
s 00024/00008/00990
d D 8.4 95/02/14 10:49:20 cgd 158 157
c return types, light clean.
e
s 00009/00000/00989
d D 8.3 94/04/15 17:25:46 mckusick 157 156
c avoid hang when given a negative write count (from polk@bsdi.com)
e
s 00003/00002/00986
d D 8.2 94/01/03 17:40:08 bostic 156 155
c For a setsockopt at the socket level, if the protocol has no ctloutput
c function, an mbuf is lost.  From: Mike Karels <karels@BSDI.COM>
e
s 00002/00002/00986
d D 8.1 93/06/10 21:59:46 bostic 155 154
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00987
d D 7.41 93/06/02 10:45:57 karels 154 153
c deliver data to non-atomic protocols in regular-sized chunks even on machines
c without MAPPED_MBUFS, or TCP will send 968-byte packets
e
s 00001/00001/00987
d D 7.40 93/05/12 16:26:35 sklower 153 152
c If an internal-use protocol entry doesn't have a usrreq routine
c bail out very early before creating a socket.  (from thomas@lkg.dec.com)
e
s 00004/00001/00984
d D 7.39 93/03/06 23:42:02 torek 152 151
c stop if we reach out of band mark while peeking; otherwise
c we will go into an infinite loop copying 0 bytes each time.  (From
c Tom Truscott <trt@cs.duke.edu>)
e
s 00020/00007/00965
d D 7.38 93/02/27 23:16:32 mckusick 151 150
c fix bugs in sending messages through sockets (4.4BSD-alpha/sys/6)
e
s 00012/00012/00960
d D 7.37 92/10/11 10:38:52 bostic 150 149
c make kernel includes standard
e
s 00002/00000/00970
d D 7.36 92/07/18 17:01:51 sklower 149 148
c multicast bugfix from arc@sgi.com
e
s 00001/00000/00969
d D 7.35 92/07/12 17:31:26 pendry 148 147
c need to include systm.h
e
s 00002/00002/00967
d D 7.34 92/03/13 17:08:37 mckusick 147 146
c use proc pointer from uio rather than (sometimes unset curproc)
e
s 00001/00005/00968
d D 7.33 92/02/15 21:14:15 mckusick 146 145
c convert to use new select interface, selrecord/selwakeup
e
s 00001/00000/00972
d D 7.32 92/02/13 18:13:03 torek 145 144
c lint
e
s 00012/00009/00960
d D 7.31 91/11/19 15:59:36 mckusick 144 143
c upcall facilities for sorwakeup, non-blocking sblock for NFS (from Macklem)
e
s 00004/00003/00965
d D 7.30 91/09/06 17:03:32 sklower 143 142
c last line of while not reached; shut up mips compiler (from Ralph Campbell);
c make sosetopt inform protocols of SOL_SOCKET options being changed.
e
s 00003/00000/00965
d D 7.29 91/08/30 16:25:54 sklower 142 140
c notify lower levels of some socket setopt changes, esp. buffering
e
s 00012/00013/00955
d D 7.27.1.1 91/05/09 19:05:04 sklower 141 139
c possibly change conventions about where M_EOR lies (never tested)
e
s 00007/00010/00958
d D 7.28 91/05/04 16:32:59 karels 140 139
c need proc parameter; for now use curproc.  u. is gone
e
s 00002/00001/00966
d D 7.27 91/05/03 19:22:16 sklower 139 138
c minor fix to allow sendmsg with purely control data while confirming
e
s 00021/00008/00946
d D 7.26 91/02/19 17:06:04 karels 138 137
c Try not to initiate copyouts that are going to block
c for MSG_WAITALL or watermark conditions, unless there are exceptional conditionsa
c (by sklower for history purposes before changes sockbuf storage conventions)/
e
s 00010/00004/00944
d D 7.25 91/02/18 17:13:20 sklower 137 136
c (checked in by karels) treat MT_HEADER as MT_DATA in soreceive;
c need to init len when MAPPED_MBUFS not defined
e
s 00005/00006/00943
d D 7.24 90/11/05 10:11:56 karels 136 135
c lint, rm unneeded assignment (from torek)
e
s 00036/00008/00913
d D 7.23 90/06/29 23:13:19 karels 135 134
c set/get timeouts using timevals
e
s 00001/00011/00920
d D 7.22 90/06/28 21:23:59 bostic 134 133
c new copyright notice
e
s 00015/00009/00916
d D 7.21 90/06/28 15:13:05 karels 133 132
c collect tests in soreceive (and add comments); minor fix to avoid setting
c m_nextpkt in middle of chain if peeking
e
s 00029/00046/00896
d D 7.20 90/06/22 10:26:05 karels 132 131
c fixes from macklem
e
s 00003/00003/00939
d D 7.19 90/06/14 18:19:50 sklower 131 129
c must test for existence of externalization before peeking into supposed cmsghdr
c since it may not be aligned properly if the protocol is managing it differently.
e
s 00003/00003/00939
d R 7.19 90/06/14 18:15:29 sklower 130 129
c must test for existence of externalization before peeking into supposed cmsghdr
c since it may not be aligned properly if the protocol is managing it differently.
e
s 00202/00144/00740
d D 7.18 90/05/14 13:24:28 karels 129 128
c first cut at merged sosend, soreceive for NFS and sockets
e
s 00048/00032/00836
d D 7.17 90/04/03 21:31:44 karels 128 127
c tsleep; sblock/sbwait catch/return interrupts; implement lowat,
c timeout; move SIGPIPE up to syscall layer; strings for sleep messages
e
s 00017/00013/00851
d D 7.16 90/03/25 16:45:14 karels 127 126
c as currently running: control replaces rights entirely,
c tsleep round one, something sklower was doing with end-of-record
e
s 00005/00014/00859
d D 7.15 89/08/11 13:03:29 karels 126 125
c checkpoint before playing around with EOR conventions (by sklower)
e
s 00003/00006/00870
d D 7.14 89/05/09 17:03:00 mckusick 125 124
c merge in vnodes
e
s 00025/00024/00851
d D 7.13 89/04/22 12:26:53 sklower 124 123
c checkpoint for version to be handed to NIST, simple tp4 connection
e
s 00001/00001/00874
d D 7.12 88/08/25 11:50:27 karels 123 122
c can only use MH_ALIGN on first mbuf, and don't want it on others
e
s 00125/00055/00750
d D 7.11 88/08/21 21:53:37 karels 122 121
c working with new mbufs, control (from sklower)
e
s 00010/00005/00795
d D 7.10 88/06/29 17:21:24 bostic 121 120
c install approved copyright notice
e
s 00003/00002/00797
d D 7.9 88/05/26 09:01:38 karels 120 118
c lint
e
s 00003/00002/00797
d R 7.9 88/05/25 18:06:26 karels 119 118
c in sonewconn, set buffer limits of new socket to those of head
e
s 00001/00001/00798
d D 7.8 88/01/20 15:29:00 bostic 118 117
c soclose had uninitialized return value
e
s 00008/00002/00791
d D 7.7 87/12/30 12:01:15 bostic 117 116
c add Berkeley header
e
s 00009/00009/00784
d D 7.6 87/10/30 17:04:43 bostic 116 115
c release does an splx(s); don't bother doing it earlier
e
s 00013/00015/00780
d D 7.5 87/09/01 15:15:37 karels 115 114
c avoid reading past mark if oob data arrives during uiomove
e
s 00000/00010/00795
d D 7.4 87/07/27 18:07:53 mckusick 114 113
c delete unneeded header files
e
s 00002/00002/00803
d D 7.3 87/07/10 09:08:50 karels 113 112
c don't remove socket from q's if not freeing
c (it confuses sonewconn, which removes it from q itself)
e
s 00004/00001/00801
d D 7.2 87/01/18 22:11:02 karels 112 111
c avoid knots
e
s 00001/00001/00801
d D 7.1 86/06/05 00:16:31 mckusick 111 110
c 4.3BSD release version
e
s 00002/00000/00800
d D 6.26 86/04/19 20:44:30 karels 110 109
c option for receiving OOB data in-line
e
s 00023/00032/00777
d D 6.25 86/03/28 15:00:34 karels 109 108
c re-fix consistency problems with input during uiomove,
c let uiomove update the vectors (and we can pack things tighter)
e
s 00007/00004/00802
d D 6.24 86/03/07 19:23:51 karels 108 107
c clean up ordering; don't lose stuff that arrives during uiomove
e
s 00001/00001/00805
d D 6.23 86/02/23 23:12:22 karels 107 106
c lint
e
s 00003/00004/00803
d D 6.22 86/02/19 16:50:14 karels 106 105
c remove unused (and sometimes missing) second arg to sodisconnect
e
s 00002/00004/00805
d D 6.21 86/02/18 16:25:19 karels 105 104
c clean up cluster allocation
e
s 00004/00002/00805
d D 6.20 86/01/09 18:35:05 karels 104 103
c oops, don't want to remove mbufs while peeking!
e
s 00060/00032/00747
d D 6.19 85/12/19 14:51:25 karels 103 102
c change datagram queuing, full packet on one chain; allow rights
c in streams
e
s 00006/00001/00773
d D 6.18 85/11/19 19:42:12 karels 102 101
c add SO_TYPE option (get only!), correct mbuf lengths
e
s 00023/00007/00751
d D 6.17 85/09/16 20:52:39 karels 101 100
c allow select on exceptional conditions to notify of urgent data pending;
c connect on connected datagram socket does disconnect first; error status
c socket option
e
s 00001/00001/00757
d D 6.16 85/09/04 08:50:20 karels 100 99
c use the macro
e
s 00007/00001/00751
d D 6.15 85/06/08 15:00:13 mckusick 99 98
c Add copyright
e
s 00005/00010/00747
d D 6.14 85/06/08 13:10:11 karels 98 97
c reverse sense of pid/pgrp for fcntl, SIOCSPGRP (pgrp is negative)
e
s 00001/00001/00756
d D 6.13 85/06/03 08:48:49 karels 97 96
c oops, forgot one
e
s 00011/00011/00746
d D 6.12 85/06/02 23:33:58 karels 96 95
c allow raw sockets of any protocol if a wildcard raw entry is found;
c pass protocol number to PRU_ATTACH for above;
c use mbuf clusters for sends of >= NBPG;
c send access rights once only if more than 1 mbuf of ordinary data;
c fix PEEK moff code in soreceive
e
s 00021/00032/00736
d D 6.11 85/05/27 20:01:55 karels 95 94
c allow zero-length sends; fix race when blocking in uiomove
c by getting EPIPE from usrreq if disconnected; M_WAIT is here
e
s 00004/00003/00764
d D 6.10 85/04/02 09:24:59 karels 94 92
c last arg of pr_ctloutput(PRCO_SETOPT... is **mbuf for consistency
e
s 00003/00002/00765
d R 6.10 85/04/01 17:55:06 karels 93 92
c last arg of pr_ctloutput(PRCO_SETOPT... is **mbuf for consistency
e
s 00126/00058/00641
d D 6.9 85/03/18 15:24:54 karels 92 90
c ctloutput calls to protocol
e
s 00060/00000/00699
d R 6.9 84/11/14 09:58:28 karels 91 90
c add sockopts for buffer sizes, etc.
e
s 00049/00028/00650
d D 6.8 84/09/04 21:45:44 sam 90 89
c revise socket option interface so options at SOL_SOCKET take value 
c parameter indicating if option is on/off
e
s 00017/00017/00661
d D 6.7 84/08/29 20:28:02 bloom 89 88
c Change to includes.  no more ../h
e
s 00055/00073/00623
d D 6.6 84/08/21 10:42:11 karels 88 87
c change datagram queuing to use m_act properly; type mbufs with rights;
c change protocol family number in protosw to pointer to domain (for sam)
e
s 00015/00010/00681
d D 6.5 84/08/21 10:38:46 karels 87 86
c try to remain page-aligned in sosend, even if that means waiting
e
s 00002/00000/00689
d D 6.4 84/04/30 13:39:07 karels 86 85
c seem to need to call usrreq at splnet...
e
s 00080/00094/00609
d D 6.3 84/04/24 17:26:59 karels 85 84
c rework sosend: no EWOULDBLOCK after partial write; allow zero-length
c datagrams; eliminate goto's and untwist loop; simplify space calculation
c (still wrong, but won't send partial datagrams!)
e
s 00011/00002/00692
d D 6.2 83/09/29 11:23:09 karels 84 82
c prevent inner loop in sosend from queuing more than "space" bytes;
c temporary fix to prevent 64K writes from crashing us.
e
s 00006/00002/00692
d R 6.2 83/09/28 11:52:09 karels 83 82
c inner loop in sosend limited to "space" bytes to fix
c 64K pipe problem
e
s 00000/00000/00694
d D 6.1 83/08/23 12:59:45 sam 82 81
c 4.2 distribution
e
s 00002/00000/00692
d D 4.78 83/08/23 12:58:09 sam 81 79
c panic too punitive?  we'll see ...
e
s 00000/00000/00692
d R 6.1 83/08/20 15:32:23 sam 80 79
c 4.2 distribution
e
s 00003/00001/00689
d D 4.77 83/08/20 15:31:51 sam 79 77
c ignoring error return is a no no
e
s 00000/00000/00690
d R 6.1 83/07/29 06:47:24 sam 78 77
c 4.2 distribution
e
s 00002/00005/00688
d D 4.76 83/06/14 20:40:17 sam 77 76
c socketpair
e
s 00153/00169/00540
d D 4.75 83/05/27 12:50:31 sam 76 75
c merge of bill's code plus lint (plus, of course, cleanup of bill's bugs)
e
s 00001/00000/00708
d D 4.74 83/05/18 02:00:17 sam 75 74
c not needed, but shannon's a perfectionist
e
s 00002/00000/00706
d D 4.73 83/03/19 18:20:02 sam 74 73
c add two ioctl's
e
s 00015/00000/00691
d D 4.72 83/03/15 18:15:29 sam 73 72
c socket ioctls
e
s 00005/00012/00686
d D 4.71 83/01/22 23:41:29 sam 72 70
c hack to allow FTP to rebind local addresses
e
s 00005/00012/00686
d R 4.71 83/01/22 22:50:47 sam 71 70
c hack for FTP and the rest of the Internet gang
e
s 00019/00002/00679
d D 4.70 83/01/17 18:08:38 sam 70 69
c fix for race condition in soclose
e
s 00008/00007/00673
d D 4.69 83/01/13 19:02:20 sam 69 68
c allow nil pointers for option values
e
s 00115/00062/00565
d D 4.68 83/01/13 18:38:44 sam 68 67
c reorganize socket options; move shutdown from ioctl to 
c system call; purge some ioctl's which are superseded by socket 
c options sys calls; 
c invert SO_DONTLINGER to SO_LINGER; add SOF_DONTROUTE for sendto
e
s 00016/00015/00611
d D 4.67 83/01/04 20:48:59 sam 67 66
c from reading the code -- boy is there a lot of work to be done
e
s 00003/00003/00623
d D 4.66 82/12/14 17:10:38 sam 66 65
c typed mbufs
e
s 00000/00025/00626
d D 4.65 82/12/05 21:57:16 sam 65 64
c delete obsolete ioctl's (now use SOF_OOB)
e
s 00005/00005/00646
d D 4.64 82/11/13 22:54:06 sam 64 63
c merge of 4.1b and 4.1c
e
s 00004/00003/00647
d D 4.63 82/11/02 23:39:29 root 63 62
c typos
e
s 00001/00000/00649
d D 4.62 82/10/31 14:09:29 root 62 61
c fix from 68k
e
s 00001/00001/00648
d D 4.61 82/10/23 16:36:19 root 61 60
c race in soreceive consistency checking
e
s 00002/00002/00647
d D 4.60 82/10/21 23:53:59 root 60 59
c lint
e
s 00004/00004/00645
d D 4.59 82/10/21 20:59:41 root 59 58
c lint
e
s 00001/00001/00648
d D 4.58 82/10/20 03:17:22 root 58 57
c lint
e
s 00015/00016/00634
d D 4.57 82/10/20 02:40:19 root 57 56
c lint
e
s 00030/00029/00620
d D 4.56 82/10/17 14:06:47 root 56 55
c fix lint
e
s 00019/00021/00630
d D 4.55 82/10/17 11:33:10 root 55 54
c soioctl returns errno's
e
s 00001/00001/00650
d D 4.54 82/10/16 22:54:23 root 54 53
c typo
e
s 00009/00002/00642
d D 4.53 82/10/16 17:40:24 root 53 52
c add code looking for panic:receive problem
e
s 00001/00003/00643
d D 4.52 82/10/09 05:39:25 wnj 52 51
c fix up header file dependencies 
e
s 00090/00044/00556
d D 4.51 82/10/05 21:58:09 root 51 50
c send(... SOF_OOB) and receive(... SOF_PREVIEW)
e
s 00093/00083/00507
d D 4.50 82/10/03 23:39:25 root 50 49
c overhaul
e
s 00002/00000/00588
d D 4.49 82/09/04 09:22:24 root 49 48
c count messages
e
s 00022/00015/00566
d D 4.48 82/08/22 21:13:32 root 48 47
c uio'd
e
s 00024/00015/00557
d D 4.47 82/08/14 18:01:40 root 47 46
c read() now goes through readip()
e
s 00001/00001/00571
d D 4.46 82/08/01 19:23:45 sam 46 45
c lost SCCS keywords
e
s 00033/00093/00539
d D 4.45 82/08/01 19:22:17 sam 45 44
c new ioctl's
e
s 00023/00020/00609
d D 4.44 82/07/24 18:12:47 root 44 43
c merge with calder
e
s 00002/00002/00627
d D 4.43 82/07/22 18:23:41 sam 43 42
c inverted logic (crotf@sri-tsc)
e
s 00000/00010/00629
d D 4.42 82/06/20 12:22:00 sam 42 41
c purge COUNT crap now that we have gprof
e
s 00004/00001/00635
d D 4.41 82/06/14 22:17:17 wnj 41 40
c get rid of m_release stuff
e
s 00007/00001/00629
d D 4.40 82/05/20 15:04:35 sam 40 39
c don't DETACH if protocol control block already gone
e
s 00000/00002/00630
d D 4.39 82/04/10 23:44:02 sam 39 38
c make routing entry installation priviledged
e
s 00015/00011/00617
d D 4.38 82/04/01 07:54:56 root 38 37
c bug fixes (with kirk) obscure races
e
s 00019/00000/00609
d D 4.37 82/03/29 11:36:09 sam 37 36
c add routing ioctl's
e
s 00000/00016/00609
d D 4.36 82/03/19 14:22:11 sam 36 35
c purge extraneous stuff
e
s 00002/00000/00623
d D 4.35 82/03/19 00:25:06 root 35 34
c set SO_KEEPALIVE when start exiting to force dead circuits to die
e
s 00014/00011/00609
d D 4.34 82/03/15 04:47:31 wnj 34 33
c shutdown; clear suid; get/set hostname; nbio in state not options fixes
e
s 00001/00000/00619
d D 4.33 82/03/12 15:59:33 sam 33 32
c lint picked this one up
e
s 00003/00005/00616
d D 4.32 82/03/09 20:32:25 root 32 31
c 
e
s 00003/00001/00618
d D 4.31 82/02/25 12:49:58 wnj 31 30
c send SIGPIPE
e
s 00001/00001/00618
d D 4.30 82/01/24 18:33:15 wnj 30 29
c space <= 0 check avoids unsigned comparison botch
e
s 00000/00000/00619
d D 4.29 82/01/19 06:39:29 wnj 29 28
c closef parameter indicating whether error return
c to complete non-blc
e
s 00010/00003/00609
d D 4.28 82/01/19 05:16:48 root 28 27
c dont lose memory when closing non-blocking socket; this is blocking operation; set linger to 0 to not block then
e
s 00002/00014/00610
d D 4.27 82/01/17 21:51:24 wnj 27 26
c EOPNOTSUPP when unknown ioctl
e
s 00006/00002/00618
d D 4.26 82/01/17 04:04:14 wnj 26 25
c fix psignal to have struct proc argument
e
s 00085/00003/00535
d D 4.25 82/01/17 01:06:28 wnj 25 24
c out of band and related facilities
e
s 00001/00001/00537
d D 4.24 82/01/14 17:00:51 wnj 24 23
c before move async to file table
e
s 00075/00006/00463
d D 4.23 82/01/13 10:30:48 root 23 22
c add ioctls
e
s 00003/00003/00466
d D 4.22 82/01/07 22:13:35 root 22 21
c minor bug fixes
e
s 00002/00001/00467
d D 4.21 81/12/22 23:45:05 root 21 20
c fstat on socket gives 0
e
s 00026/00008/00442
d D 4.20 81/12/21 11:53:53 root 20 19
c LETDATADRAIN; SIOCDONE
e
s 00005/00004/00445
d D 4.19 81/12/19 12:50:21 wnj 19 18
c fix soaccept
e
s 00000/00004/00449
d D 4.18 81/12/12 18:07:46 root 18 17
c delete prints
e
s 00006/00001/00447
d D 4.17 81/12/12 17:49:45 root 17 16
c almost works
e
s 00015/00005/00433
d D 4.16 81/12/02 17:26:45 wnj 16 15
c more cleanup
e
s 00005/00005/00433
d D 4.15 81/11/26 11:58:56 wnj 15 14
c before carry to arpavax
e
s 00000/00060/00438
d D 4.14 81/11/22 23:55:21 wnj 14 13
c fix to PR_ADDR code
e
s 00066/00006/00432
d D 4.13 81/11/22 23:49:53 wnj 13 12
c working with dg's but a lot of crud
e
s 00006/00004/00432
d D 4.12 81/11/22 10:51:04 wnj 12 11
c fix to way send looks at space: sleep when none!
e
s 00003/00003/00433
d D 4.11 81/11/21 22:13:32 root 11 10
c fix mbuf accounting
e
s 00002/00000/00434
d D 4.10 81/11/21 21:32:58 wnj 10 9
c missing splx(s) and so->so_rcv.sb_mb = n in
e
s 00006/00003/00428
d D 4.9 81/11/21 15:15:15 wnj 9 8
c error value from ATTACH; u.u_count==0 break in send
e
s 00003/00003/00428
d D 4.8 81/11/20 14:43:41 wnj 8 7
c more lint
e
s 00006/00002/00425
d D 4.7 81/11/20 00:46:09 wnj 7 6
c linted
e
s 00074/00046/00353
d D 4.6 81/11/18 15:45:22 wnj 6 5
c more cleanup
e
s 00023/00014/00376
d D 4.5 81/11/16 14:21:06 wnj 5 4
c lint
e
s 00001/00005/00389
d D 4.4 81/11/15 13:02:11 wnj 4 3
c listing
e
s 00217/00341/00177
d D 4.3 81/11/14 16:43:56 wnj 3 2
c before header overlay
e
s 00161/00059/00357
d D 4.2 81/11/08 17:11:48 wnj 2 1
c first listing
e
s 00416/00000/00000
d D 4.1 81/11/07 17:59:21 wnj 1 0
c date and time created 81/11/07 17:59:21 by wnj
e
u
U
f b 
t
T
I 1
D 44
/*	%M%	%I%	%E%	*/
E 44
I 44
D 46
/*	socket.c	4.43	82/07/21	*/
E 46
I 46
D 99
/*	%M%	%I%	%E%	*/
E 99
I 99
/*
D 111
 * Copyright (c) 1982 Regents of the University of California.
E 111
I 111
D 122
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 122
I 122
D 129
 * Copyright (c) 1982, 1986, 1988 Regents of the University of California.
E 129
I 129
D 155
 * Copyright (c) 1982, 1986, 1988, 1990 Regents of the University of California.
E 129
E 122
E 111
D 117
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 117
I 117
 * All rights reserved.
E 155
I 155
 * Copyright (c) 1982, 1986, 1988, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 155
 *
D 134
 * Redistribution and use in source and binary forms are permitted
D 121
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 121
I 121
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 134
I 134
 * %sccs.include.redist.c%
E 134
E 121
E 117
 *
 *	%W% (Berkeley) %G%
 */
E 99
E 46
E 44

D 89
#include "../h/param.h"
I 2
#include "../h/systm.h"
E 2
#include "../h/dir.h"
#include "../h/user.h"
D 2
#include "file.h"
E 2
I 2
#include "../h/proc.h"
#include "../h/file.h"
E 2
#include "../h/inode.h"
I 2
#include "../h/buf.h"
E 2
#include "../h/mbuf.h"
I 76
#include "../h/un.h"
I 88
#include "../h/domain.h"
E 88
E 76
D 2
#include "protocol.h"
#include "protocolsw.h"
#include "socket.h"
#include "socketvar.h"
E 2
I 2
D 6
#include "../h/protocol.h"
E 6
#include "../h/protosw.h"
#include "../h/socket.h"
#include "../h/socketvar.h"
D 6
#include "../h/inaddr.h"
E 6
I 5
#include "../h/stat.h"
I 20
#include "../h/ioctl.h"
E 20
E 5
D 15
#include "../net/inet.h"
#include "../net/inet_systm.h"
E 15
I 15
D 52
#include "../net/in.h"
#include "../net/in_systm.h"
I 37
#include "../net/route.h"
E 52
I 47
#include "../h/uio.h"
E 89
I 89
D 150
#include "param.h"
I 148
#include "systm.h"
E 148
D 114
#include "systm.h"
E 114
D 125
#include "dir.h"
E 125
D 140
#include "user.h"
E 140
#include "proc.h"
#include "file.h"
I 122
#include "malloc.h"
E 122
D 114
#include "inode.h"
#include "buf.h"
E 114
#include "mbuf.h"
D 114
#include "un.h"
E 114
#include "domain.h"
I 135
#include "kernel.h"
E 135
#include "protosw.h"
#include "socket.h"
#include "socketvar.h"
I 135
D 140
#include "time.h"
E 140
I 140
#include "resourcevar.h"
E 150
I 150
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/proc.h>
#include <sys/file.h>
#include <sys/malloc.h>
#include <sys/mbuf.h>
#include <sys/domain.h>
#include <sys/kernel.h>
#include <sys/protosw.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
#include <sys/resourcevar.h>
E 150
E 140
E 135
I 127
D 128
#include "tsleep.h"
E 128
E 127
D 114
#include "stat.h"
#include "ioctl.h"
#include "uio.h"
E 89
I 52
#include "../net/route.h"
I 76
#include "../netinet/in.h"
E 76
I 73
#include "../net/if.h"
E 114
E 73
E 52
E 47
E 37
E 15
E 2

D 3
struct	socket zerosocket;
struct	in_addr zeroin_addr;

E 3
/*
D 3
 * Socket system call interface.  Copy in arguments
 * set up file descriptor and call internal socket
 * creation routine.
E 3
I 3
D 50
 * Socket support routines.
 *
 * DEAL WITH INTERRUPT NOTIFICATION.
E 50
I 50
 * Socket operation routines.
 * These routines are called by the routines in
 * sys_socket.c or from a system process, and
 * implement the semantics of socket operations by
 * switching out to the protocol specific routines.
I 76
D 140
 *
 * TODO:
D 96
 *	sostat
E 96
 *	test socketpair
D 96
 *	PR_RIGHTS
 *	clean up select, async
E 96
I 96
 *	clean up async
E 96
 *	out-of-band is a kludge
E 140
E 76
E 50
D 6
 * DO NEWFD STUFF
E 6
E 3
 */
D 3
ssocket()
{
	register struct a {
D 2
		int type;
		in_addr *ain;
		int flags;
E 2
I 2
		int	type;
		struct	in_addr *ain;
		int	options;
E 2
	} *uap = (struct a *)u.u_ap;
D 2
	in_addr in;
E 2
I 2
	struct in_addr in;
E 2
	struct socket *so0;
	register struct socket *so;
	register struct file *fp;
E 3
D 76

E 76
I 56
/*ARGSUSED*/
I 158
int
E 158
E 56
D 3
	if ((fp = falloc()) == NULL)
		return;
	fp->f_flag = FSOCKET|FREAD|FWRITE;
	if (copyin((caddr_t)uap->ain, &in, sizeof (in))) {
		u.u_error = EFAULT;
		return;
	}
D 2
	u.u_error = socket(&so0, a->type, &in, a->flags);
E 2
I 2
	u.u_error = socket(&so0, uap->type, &in, uap->options);
E 2
	if (u.u_error)
		goto bad;
	fp->f_socket = so;
	return;
bad:
	u.u_ofile[u.u_r.r_val1] = 0;
	fp->f_count = 0;
}

E 3
D 50
/*
 * Create a socket.
 */
D 2
socket(aso, type, iap, flags)
E 2
I 2
D 6
socket(aso, type, iap, options)
E 6
I 6
socreate(aso, type, asp, asa, options)
E 50
I 50
D 68
socreate(dom, aso, type, proto, opt)
E 68
I 68
socreate(dom, aso, type, proto)
I 145
	int dom;
E 145
E 68
E 50
E 6
E 2
	struct socket **aso;
D 50
	int type;
D 6
	register struct in_addr *iap;
E 6
I 6
	struct sockproto *asp;
	struct sockaddr *asa;
E 6
D 2
	int flags;
E 2
I 2
	int options;
E 50
I 50
D 76
	int type, proto;
E 76
I 76
	register int type;
	int proto;
E 76
D 68
	struct socketopt *opt;
E 68
E 50
E 2
{
I 140
	struct proc *p = curproc;		/* XXX */
E 140
	register struct protosw *prp;
	register struct socket *so;
D 76
	struct mbuf *m;
D 3
	int pf, proto;
E 3
I 3
D 50
	int pf, proto, error;
E 50
I 50
D 64
	int pf, error;
E 64
I 64
	int error;
E 76
I 76
D 124
	register struct mbuf *m;
E 124
	register int error;
E 76
E 64
E 50
I 6
D 42
COUNT(SOCREATE);
E 42
E 6
E 3

D 50
	/*
D 3
	 * Pin down protocol if possible.
	 * If no address specified, use a generic protocol.
E 3
I 3
	 * Use process standard protocol/protocol family if none
	 * specified by address argument.
E 3
	 */
D 6
	if (iap == 0) {
E 6
I 6
	if (asp == 0) {
E 6
D 3
		pf = PF_GENERIC;
E 3
I 3
		pf = PF_INET;		/* should be u.u_protof */
E 3
		proto = 0;
	} else {
D 6
		pf = iap->ia_pf;
		proto = iap->ia_proto;
E 6
I 6
		pf = asp->sp_family;
		proto = asp->sp_protocol;
E 6
	}
D 3
	if (proto) {
		/*
		 * A specific protocol was requested.  Look
		 * for the protocol.  If not found, then we
		 * don't support it.
		 */
		prp = pf_findproto(pf, proto);
		if (prp == 0)
D 2
			return (EPROTONOTSUPP);
E 2
I 2
			return (EPROTONOSUPPORT);
E 2
	} else {
		/*
		 * No specific protocol was requested.  Look
		 * in the specified (or generic) protocol set
		 * for a protocol of this type.
		 */
		prp = pf_findtype(pf, type);
		if (prp == 0)
D 2
			return (ESOCKTYPENOTSUPP);
E 2
I 2
			return (pf == PF_GENERIC ?
			    ESOCKTNOSUPPORT : EPROTONOSUPPORT);
E 2
	}
E 3

	/*
I 3
	 * If protocol specified, look for it, otherwise
	 * for a protocol of the correct type in the right family.
	 */
E 50
I 50
D 64
	pf = dom ? PF_UNIX : PF_INET;		/* should be u.u_protof */
E 64
E 50
	if (proto)
D 64
		prp = pffindproto(pf, proto);
E 64
I 64
D 96
		prp = pffindproto(dom, proto);
E 96
I 96
		prp = pffindproto(dom, proto, type);
E 96
E 64
	else
D 64
		prp = pffindtype(pf, type);
E 64
I 64
		prp = pffindtype(dom, type);
E 64
D 153
	if (prp == 0)
E 153
I 153
	if (prp == 0 || prp->pr_usrreq == 0)
E 153
		return (EPROTONOSUPPORT);
D 50

	/*
E 3
	 * Get a socket structure.
	 */
E 50
I 50
	if (prp->pr_type != type)
		return (EPROTOTYPE);
E 50
D 3
	m = m_get(M_WAIT);
E 3
I 3
D 66
	m = m_getclr(M_WAIT);
E 66
I 66
D 124
	m = m_getclr(M_WAIT, MT_SOCKET);
E 66
E 3
D 95
	if (m == 0)
		return (ENOBUFS);
E 95
D 3
	m->m_off = MMINOFF;
E 3
	so = mtod(m, struct socket *);
D 3
	*so = zerosocket;
E 3
D 2
	so->so_flags = flags;
E 2
I 2
D 50
	so->so_options = options;
I 44
	if (options & SO_ACCEPTCONN) {
		so->so_q = so;
		so->so_q0 = so;
		so->so_qlimit = (so->so_options & SO_NEWFDONCONN) ? 5 : 1;
	}
E 50
I 50
D 68
	so->so_options = 0;
E 68
I 68
D 76
	so->so_options = SO_LINGER;
E 76
I 76
	so->so_options = 0;
E 76
E 68
E 50
E 44
I 34
	so->so_state = 0;
E 124
I 124
	MALLOC(so, struct socket *, sizeof(*so), M_SOCKET, M_WAIT);
	bzero((caddr_t)so, sizeof(*so));
E 124
I 64
	so->so_type = type;
E 64
D 140
	if (u.u_uid == 0)
E 140
I 140
	if (p->p_ucred->cr_uid == 0)
E 140
		so->so_state = SS_PRIV;
E 34
E 2
D 50

	/*
D 3
	 * An early call to protocol initialization.  If protocol
	 * actually hasn't been decided on yet (till we know
	 * peer), then the generic protocol allocated so far can
	 * just make sure a reasonable amount of resources will
	 * be available to it (say by allocating liberally now
	 * and returning some of the resources later).
E 3
I 3
	 * Attach protocol to socket, initializing
	 * and reserving resources.
E 3
	 */
E 50
	so->so_proto = prp;
D 6
	(*prp->pr_usrreq)(so, PRU_ATTACH, 0, 0);
E 6
I 6
D 9
	(*prp->pr_usrreq)(so, PRU_ATTACH, 0, asa);
E 6
	if (so->so_error) {
I 3
D 4
/*###80 [cc] operands of = have incompatible types %%%*/
/*###80 [cc] zerosocket undefined %%%*/
E 4
		error = so->so_error;
E 9
I 9
D 50
	error = (*prp->pr_usrreq)(so, PRU_ATTACH, 0, asa);
E 50
I 50
D 76
	error = (*prp->pr_usrreq)(so, PRU_ATTACH,
D 67
	    (struct mbuf *)0, (struct mbuf *)0, (struct socketopt *)0);
E 67
I 67
D 68
	    (struct mbuf *)0, (struct mbuf *)0, opt);
E 68
I 68
	    (struct mbuf *)0, (struct mbuf *)0);
E 76
I 76
D 158
	error =
	    (*prp->pr_usrreq)(so, PRU_ATTACH,
D 96
		(struct mbuf *)0, (struct mbuf *)0, (struct mbuf *)0);
E 96
I 96
		(struct mbuf *)0, (struct mbuf *)proto, (struct mbuf *)0);
E 158
I 158
	error = (*prp->pr_usrreq)(so, PRU_ATTACH, (struct mbuf *)0,
	    (struct mbuf *)(long)proto, (struct mbuf *)0);
E 158
E 96
E 76
E 68
E 67
E 50
	if (error) {
E 9
E 3
D 8
		m_free(dtom(so));
E 8
I 8
D 41
		(void) m_free(dtom(so));
E 41
I 41
D 44
		if (so->so_snd.sb_mbmax || so->so_rcv.sb_mbmax)
			panic("socreate");
		so->so_state |= SS_USERGONE;
E 44
I 44
		so->so_state |= SS_NOFDREF;
E 44
		sofree(so);
E 41
E 8
D 3
		return (u.u_error);
E 3
I 3
		return (error);
E 3
	}
	*aso = so;
	return (0);
}

I 158
int
E 158
I 50
D 68
sobind(so, nam, opt)
E 68
I 68
sobind(so, nam)
E 68
	struct socket *so;
	struct mbuf *nam;
D 68
	struct socketopt *opt;
E 68
{
	int s = splnet();
	int error;

D 128
	error =
D 68
	    (*so->so_proto->pr_usrreq)(so, PRU_BIND,
		(struct mbuf *)0, nam, opt);
E 68
I 68
D 76
	    (*so->so_proto->pr_usrreq)(so, PRU_BIND, (struct mbuf *)0, nam);
E 76
I 76
	    (*so->so_proto->pr_usrreq)(so, PRU_BIND,
E 128
I 128
D 129
	error = (*so->so_proto->pr_usrreq)(so, PRU_BIND,
E 129
I 129
	error =
	    (*so->so_proto->pr_usrreq)(so, PRU_BIND,
E 129
E 128
		(struct mbuf *)0, nam, (struct mbuf *)0);
E 76
E 68
	splx(s);
	return (error);
}

I 158
int
E 158
solisten(so, backlog)
D 76
	struct socket *so;
E 76
I 76
	register struct socket *so;
E 76
	int backlog;
{
D 76
	int s = splnet();
	int error;
E 76
I 76
	int s = splnet(), error;
E 76

D 76
	error = (*so->so_proto->pr_usrreq)(so, PRU_LISTEN,
D 68
	    (struct mbuf *)0, (struct mbuf *)0, (struct socketopt *)0);
E 68
I 68
	    (struct mbuf *)0, (struct mbuf *)0);
E 76
I 76
	error =
	    (*so->so_proto->pr_usrreq)(so, PRU_LISTEN,
		(struct mbuf *)0, (struct mbuf *)0, (struct mbuf *)0);
E 76
E 68
	if (error) {
		splx(s);
		return (error);
	}
D 126
	if (so->so_q == 0) {
		so->so_q = so;
		so->so_q0 = so;
E 126
I 126
	if (so->so_q == 0)
E 126
		so->so_options |= SO_ACCEPTCONN;
D 126
	}
E 126
	if (backlog < 0)
		backlog = 0;
D 67
	so->so_qlimit = backlog < 5 ? backlog : 5;
E 67
I 67
D 76
#define	SOMAXCONN	5
E 76
D 122
	so->so_qlimit = MIN(backlog, SOMAXCONN);
E 122
I 122
	so->so_qlimit = min(backlog, SOMAXCONN);
E 122
E 67
D 76
	so->so_options |= SO_NEWFDONCONN;
E 76
I 75
	splx(s);
E 75
	return (0);
}

I 158
int
E 158
E 50
I 5
sofree(so)
D 76
	struct socket *so;
E 76
I 76
	register struct socket *so;
E 76
{

I 113
	if (so->so_pcb || (so->so_state & SS_NOFDREF) == 0)
		return;
E 113
I 6
D 42
COUNT(SOFREE);
E 42
I 7
D 44
	if (so->so_pcb || (so->so_state & SS_USERGONE) == 0)
E 44
I 44
	if (so->so_head) {
		if (!soqremque(so, 0) && !soqremque(so, 1))
			panic("sofree dq");
		so->so_head = 0;
	}
D 113
	if (so->so_pcb || (so->so_state & SS_NOFDREF) == 0)
E 44
		return;
E 113
	sbrelease(&so->so_snd);
D 76
	sbrelease(&so->so_rcv);
E 76
I 76
	sorflush(so);
E 76
E 7
E 6
D 8
	m_free(dtom(so));
E 8
I 8
D 124
	(void) m_free(dtom(so));
E 124
I 124
	FREE(so, M_SOCKET);
E 124
E 8
}

E 5
I 2
D 3
spipe()
{

}

skclose(so)
	register struct socket *so;
{

	if (so->so_pcb)
		(*so->so_proto->pr_usrreq)(so, PRU_DETACH, 0, 0);
}

E 3
E 2
/*
I 2
D 3
 * Select a socket.
E 3
I 3
 * Close a socket on last file table reference removal.
 * Initiate disconnect if connected.
 * Free socket when disconnect complete.
I 28
D 44
 *
 * THIS IS REALLY A UNIX INTERFACE ROUTINE
E 44
E 28
E 3
 */
I 158
int
E 158
D 3
soselect(so, flag)
E 3
I 3
D 28
soclose(so)
E 28
I 28
D 76
soclose(so, exiting)
E 76
I 76
soclose(so)
E 76
E 28
E 3
	register struct socket *so;
I 28
D 76
	int exiting;
E 76
E 28
D 3
	int flag;
E 3
{
D 3
	register struct proc *p;
E 3
I 3
	int s = splnet();		/* conservative */
I 57
D 118
	int error;
E 118
I 118
	int error = 0;
E 118
E 57
I 44
D 48
	register struct socket *so2;
E 48
E 44
E 3

I 44
	if (so->so_options & SO_ACCEPTCONN) {
D 126
		while (so->so_q0 != so)
E 126
I 126
		while (so->so_q0)
E 126
D 57
			soclose(so->so_q0, 1);
E 57
I 57
D 70
			(void) soclose(so->so_q0, 1);
E 70
I 70
			(void) soabort(so->so_q0);
E 70
E 57
D 126
		while (so->so_q != so)
E 126
I 126
		while (so->so_q)
E 126
D 57
			soclose(so->so_q, 1);
E 57
I 57
D 70
			(void) soclose(so->so_q, 1);
E 70
I 70
			(void) soabort(so->so_q);
E 70
E 57
	}
E 44
I 6
D 42
COUNT(SOCLOSE);
E 42
E 6
D 3
	if (so->so_rcv.sb_cc)
		return (1);
	if ((p = so->so_rcv.sb_sel) && p->p_wchan == (caddr_t)select)
		so->so_rcv.sb_flags |= SB_COLL;
	else
		so->so_rcv.sb_sel = u.u_procp;
	return (0);
E 3
I 3
	if (so->so_pcb == 0)
		goto discard;
I 35
D 76
	if (exiting)
		so->so_options |= SO_KEEPALIVE;
E 76
E 35
I 17
D 18
printf("soclose %x state %x\n", so, so->so_state);
E 18
E 17
	if (so->so_state & SS_ISCONNECTED) {
		if ((so->so_state & SS_ISDISCONNECTING) == 0) {
D 5
			u.u_error = disconnect(so, 0);
E 5
I 5
D 6
			u.u_error = disconnect(so, (struct in_addr *)0);
E 6
I 6
D 57
			u.u_error = sodisconnect(so, (struct sockaddr *)0);
E 6
E 5
			if (u.u_error) {
E 57
I 57
D 58
			error = sodisconnect(so, (struct sockaddr *)0);
E 58
I 58
D 106
			error = sodisconnect(so, (struct mbuf *)0);
E 106
I 106
			error = sodisconnect(so);
E 106
E 58
D 76
			if (error) {
E 57
I 28
				if (exiting)
					goto drop;
E 28
I 17
D 18
printf("soclose disconnect error %d\n", u.u_error);
E 18
E 17
				splx(s);
D 57
				return;
E 57
I 57
				return (error);
E 57
			}
E 76
I 76
			if (error)
				goto drop;
E 76
		}
D 20
		if ((so->so_state & SS_ISDISCONNECTING) &&
		    (so->so_options & SO_NBIO)) {
			u.u_error = EINPROGRESS;
			splx(s);
			return;
E 20
I 20
D 23
		if (so->so_options & SO_LETDATADRAIN) {
E 23
I 23
D 68
		if ((so->so_options & SO_DONTLINGER) == 0) {
E 68
I 68
		if (so->so_options & SO_LINGER) {
E 68
E 23
			if ((so->so_state & SS_ISDISCONNECTING) &&
D 23
			    (so->so_options & SO_NBIO)) {
E 23
I 23
D 28
			    (so->so_options & SO_NONBLOCKING)) {
E 28
I 28
D 34
			    (so->so_options & SO_NONBLOCKING) &&
E 34
I 34
D 76
			    (so->so_state & SS_NBIO) &&
E 34
D 57
			    exiting == 0) {
E 28
E 23
				u.u_error = EINPROGRESS;
				splx(s);
				return;
			}
E 57
I 57
			    exiting == 0)
				return (EINPROGRESS);
E 57
I 23
D 28
			/* should use tsleep here */
E 28
I 28
			/* should use tsleep here, for at most linger */
E 76
I 76
			    (so->so_state & SS_NBIO))
				goto drop;
E 76
E 28
E 23
			while (so->so_state & SS_ISCONNECTED)
D 127
				sleep((caddr_t)&so->so_timeo, PZERO+1);
E 127
I 127
D 128
				tsleep((caddr_t)&so->so_timeo, PZERO+1,
					SLP_SO_LINGER, 0);
E 128
I 128
				if (error = tsleep((caddr_t)&so->so_timeo,
D 160
				    PSOCK | PCATCH, netcls, so->so_linger))
E 160
I 160
				    PSOCK | PCATCH, netcls, so->so_linger * hz))
E 160
					break;
E 128
E 127
E 20
		}
D 17
		while (so->so_state & SS_ISCONNECTED)
E 17
I 17
D 20
		while (so->so_state & SS_ISCONNECTED) {
D 18
printf("sleeping until not connected\n");
E 18
E 17
			sleep((caddr_t)&so->so_timeo, PZERO+1);
I 17
		}
E 20
E 17
	}
I 128
D 129
	/*
	 * If there is an error on the socket, disregard any
	 * error from tsleep and return the socket error.
	 */
	if (so->so_error)
		error = so->so_error;
E 129
E 128
I 28
drop:
E 28
D 40
	u.u_error = (*so->so_proto->pr_usrreq)(so, PRU_DETACH, 0, 0);
E 40
I 40
	if (so->so_pcb) {
D 50
		u.u_error = (*so->so_proto->pr_usrreq)(so, PRU_DETACH, 0, 0);
E 50
I 50
D 57
		u.u_error = (*so->so_proto->pr_usrreq)(so, PRU_DETACH,
E 57
I 57
D 76
		error = (*so->so_proto->pr_usrreq)(so, PRU_DETACH,
E 57
D 68
		    (struct mbuf *)0, (struct mbuf *)0, (struct socketopt *)0);
E 68
I 68
		    (struct mbuf *)0, (struct mbuf *)0);
E 68
E 50
D 57
		if (exiting == 0 && u.u_error) {
E 57
I 57
		if (exiting == 0 && error) {
E 57
			splx(s);
D 57
			return;
E 57
I 57
			return (error);
E 57
		}
E 76
I 76
		int error2 =
		    (*so->so_proto->pr_usrreq)(so, PRU_DETACH,
			(struct mbuf *)0, (struct mbuf *)0, (struct mbuf *)0);
		if (error == 0)
			error = error2;
E 76
	}
E 40
discard:
I 70
	if (so->so_state & SS_NOFDREF)
		panic("soclose: NOFDREF");
E 70
D 7
	if (so->so_pcb == 0)
		sofree(so);
E 7
I 7
D 44
	so->so_state |= SS_USERGONE;
E 44
I 44
	so->so_state |= SS_NOFDREF;
E 44
	sofree(so);
E 7
	splx(s);
I 57
D 76
	return (0);
E 76
I 76
	return (error);
E 76
E 57
E 3
}

I 70
/*
 * Must be called at splnet...
 */
I 158
int
E 158
soabort(so)
	struct socket *so;
{
D 76
	int error;
E 76

D 76
	error = (*so->so_proto->pr_usrreq)(so, PRU_ABORT,
	   (struct mbuf *)0, (struct mbuf *)0);
	return (error);
E 76
I 76
	return (
	    (*so->so_proto->pr_usrreq)(so, PRU_ABORT,
		(struct mbuf *)0, (struct mbuf *)0, (struct mbuf *)0));
E 76
}

I 158
int
E 158
E 70
I 6
D 36
sosplice(pso, so)
	struct socket *pso, *so;
{

COUNT(SOSPLICE);
D 16
	if (pso->so_proto->pr_family != PF_LOCAL) {
E 16
I 16
	if (pso->so_proto->pr_family != PF_UNIX) {
E 16
		struct socket *tso;
		tso = pso; pso = so; so = tso;
	}
D 16
	if (pso->so_proto->pr_family != PF_LOCAL)
E 16
I 16
	if (pso->so_proto->pr_family != PF_UNIX)
E 16
		return (EOPNOTSUPP);
	/* check types and buffer space */
	/* merge buffers */
	return (0);
}

E 36
E 6
I 5
D 76
/*ARGSUSED*/
E 5
D 3
/*
 * Wakeup read sleep/select'ers.
 */
sowakeup(so)
E 3
I 3
D 63
sostat(so, sb)
E 63
I 63
sostat(so, ub)
E 63
E 3
	struct socket *so;
I 3
D 63
	struct stat *sb;
E 63
I 63
	struct stat *ub;
E 63
E 3
{
I 63
	struct stat sb;
E 63

I 6
D 42
COUNT(SOSTAT);
E 42
E 6
D 3
	if (so->so_rcv.sb_cc && so->so_rcv.sb_sel) {
		selwakeup(so->so_rcv.sb_sel, so->so_rcv.sb_flags & SB_COLL);
		so->so_rcv.sb_sel = 0;
		so->so_rcv.sb_flags &= ~SB_COLL;
	}
	if (so->so_rcv.sb_flags & SB_WAIT) {
		so->so_rcv.sb_flags &= ~SB_WAIT;
		wakeup((caddr_t)&so->so_rcv.sb_cc);
	}
E 3
I 3
D 21
	return (EOPNOTSUPP);
E 21
I 21
D 63
	bzero((caddr_t)sb, sizeof (*sb));		/* XXX */
E 63
I 63
	bzero((caddr_t)&sb, sizeof (sb));		/* XXX */
E 63
I 62
D 64
	copyout((caddr_t)&sb, (caddr_t)ub, sizeof (sb));/* XXX */
E 64
I 64
	(void) copyout((caddr_t)&sb, (caddr_t)ub, sizeof (sb));/* XXX */
E 64
E 62
	return (0);					/* XXX */
E 21
E 3
}

E 76
D 50
/*
I 6
 * Accept connection on a socket.
 */
soaccept(so, asa)
E 50
I 50
D 68
soaccept(so, nam, opt)
E 68
I 68
soaccept(so, nam)
E 68
E 50
D 76
	struct socket *so;
E 76
I 76
	register struct socket *so;
E 76
D 50
	struct sockaddr *asa;
E 50
I 50
	struct mbuf *nam;
D 68
	struct socketopt *opt;
E 68
E 50
{
	int s = splnet();
	int error;

I 70
	if ((so->so_state & SS_NOFDREF) == 0)
		panic("soaccept: !NOFDREF");
E 70
I 68
	so->so_state &= ~SS_NOFDREF;
E 68
D 42
COUNT(SOACCEPT);
E 42
D 19
	if (so->so_state & (SS_ISCONNECTED|SS_ISCONNECTING)) {
		error = EISCONN;
		goto bad;
	}
E 19
D 44
	if ((so->so_options & SO_ACCEPTCONN) == 0) {
		error = EINVAL;			/* XXX */
		goto bad;
	}
I 19
	if ((so->so_state & SS_CONNAWAITING) == 0) {
		error = ENOTCONN;
		goto bad;
	}
	so->so_state &= ~SS_CONNAWAITING;
E 44
E 19
D 50
	error = (*so->so_proto->pr_usrreq)(so, PRU_ACCEPT, 0, (caddr_t)asa);
E 50
I 50
	error = (*so->so_proto->pr_usrreq)(so, PRU_ACCEPT,
D 68
	    (struct mbuf *)0, nam, opt);
E 68
I 68
D 76
	    (struct mbuf *)0, nam);
E 76
I 76
	    (struct mbuf *)0, nam, (struct mbuf *)0);
E 76
E 68
E 50
I 17
D 18
printf("PRU_ACCEPT returns error %d\n", error);
E 18
E 17
D 44
bad:
E 44
	splx(s);
	return (error);
}

I 158
int
E 158
D 50
/*
E 6
E 2
D 3
 * Connect socket to foreign peer; system call
 * interface.  Copy in arguments and call internal routine.
E 3
I 3
 * Connect socket to a specified address.
 * If already connected or connecting, then avoid
 * the protocol entry, to keep its job simpler.
E 3
 */
D 3
sconnect()
{
	register struct a {
		int fdes;
D 2
		in_addr *a;
E 2
I 2
		struct in_addr *a;
E 2
	} *uap = (struct a *)u.u_ap;
	in_addr in;
I 2
	register struct file *fp;
	register struct socket *so;
	int s;
E 2

D 2
	if (copyin((caddr_t)uap->aaddr, &in, sizeof (in))) {
E 2
I 2
	if (copyin((caddr_t)uap->a, &in, sizeof (in))) {
E 2
		u.u_error = EFAULT;
		return;
	}
	fp = getf(uap->fdes);
	if (fp == 0)
		return;
	if ((fp->f_flag & FSOCKET) == 0) {
		u.u_error = ENOTSOCK;
		return;
	}
D 2
	u.u_error = connect(fp->f_socket, &in);
E 2
I 2
	so = fp->f_socket;
	u.u_error = connect(so, &in);
E 2
	if (u.u_error)
		return;
	s = splnet();
	for (;;) {
		/* should use tsleep here */
		if ((*so->so_proto->pr_usrreq)(so, PRU_ISCONN, 0, &in) == 0)
			break;
		sleep((caddr_t)&so->so_timeo, PZERO+1);
	}
	splx(s);
}

E 3
D 6
connect(so, iap)
E 6
I 6
soconnect(so, asa)
E 50
I 50
D 68
soconnect(so, nam, opt)
E 68
I 68
soconnect(so, nam)
E 68
E 50
E 6
D 76
	struct socket *so;
E 76
I 76
	register struct socket *so;
E 76
D 6
	struct in_addr *iap;
E 6
I 6
D 50
	struct sockaddr *asa;
E 50
I 50
	struct mbuf *nam;
D 68
	struct socketopt *opt;
E 68
E 50
E 6
{
I 3
D 112
	int s = splnet();
E 112
I 112
	int s;
E 112
	int error;
E 3

I 112
	if (so->so_options & SO_ACCEPTCONN)
		return (EOPNOTSUPP);
	s = splnet();
E 112
I 6
D 42
COUNT(SOCONNECT);
E 42
E 6
D 2
	return ((*so->so_proto->pr_usrreq)(so, PRU_CONNECT, 0, &in));
E 2
I 2
D 3
	return ((*so->so_proto->pr_usrreq)(so, PRU_CONNECT, 0, iap));
E 3
I 3
D 101
	if (so->so_state & (SS_ISCONNECTED|SS_ISCONNECTING)) {
E 101
I 101
	/*
	 * If protocol is connection-based, can only connect once.
	 * Otherwise, if connected, try to disconnect first.
	 * This allows user to disconnect by connecting to, e.g.,
	 * a null address.
	 */
	if (so->so_state & (SS_ISCONNECTED|SS_ISCONNECTING) &&
	    ((so->so_proto->pr_flags & PR_CONNREQUIRED) ||
	    (error = sodisconnect(so))))
E 101
		error = EISCONN;
D 101
		goto bad;
	}
D 6
	error = (*so->so_proto->pr_usrreq)(so, PRU_CONNECT, 0, (caddr_t)iap);
E 6
I 6
D 50
	error = (*so->so_proto->pr_usrreq)(so, PRU_CONNECT, 0, (caddr_t)asa);
E 50
I 50
	error = (*so->so_proto->pr_usrreq)(so, PRU_CONNECT,
D 68
	    (struct mbuf *)0, nam, opt);
E 68
I 68
D 76
	    (struct mbuf *)0, nam);
E 76
I 76
	    (struct mbuf *)0, nam, (struct mbuf *)0);
E 76
E 68
E 50
E 6
bad:
E 101
I 101
	else
		error = (*so->so_proto->pr_usrreq)(so, PRU_CONNECT,
		    (struct mbuf *)0, nam, (struct mbuf *)0);
E 101
	splx(s);
	return (error);
E 3
E 2
}

I 158
int
E 158
I 76
D 77
#ifdef notdef
E 77
soconnect2(so1, so2)
	register struct socket *so1;
	struct socket *so2;
{
	int s = splnet();
	int error;

D 77
	error =
	    (*so1->so_proto->pr_usrreq)(so, PRU_CONNECT2,
		(struct mbuf *)0, (struct mbuf *)so2, (struct mbuf *)0);
E 77
I 77
	error = (*so1->so_proto->pr_usrreq)(so1, PRU_CONNECT2,
	    (struct mbuf *)0, (struct mbuf *)so2, (struct mbuf *)0);
E 77
	splx(s);
	return (error);
}
D 77
#endif
E 77

I 158
int
E 158
E 76
D 50
/*
D 3
 * Disconnect socket from foreign peer; system call
 * interface.  Copy in arguments and call internal routine.
E 3
I 3
 * Disconnect from a socket.
 * Address parameter is from system call for later multicast
 * protocols.  Check to make sure that connected and no disconnect
 * in progress (for protocol's sake), and then invoke protocol.
E 3
 */
I 5
D 6
/*ARGSUSED*/
E 5
D 3
sdisconnect()
{
	register struct a {
D 2
		int fdes;
		in_addr *a;
E 2
I 2
		int	fdes;
		in_addr	 *addr;
E 2
	} *uap = (struct a *)u.u_ap;
	in_addr in;
I 2
	register struct file *fp;
E 2

D 2
	if (uap->a && copyin((caddr_t)uap->aaddr, &in, sizeof (in))) {
E 2
I 2
	if (uap->addr &&
	    copyin((caddr_t)uap->addr, (caddr_t)&in, sizeof (in))) {
E 2
		u.u_error = EFAULT;
		return;
	}
	fp = getf(uap->fdes);
	if (fp == 0)
		return;
	if ((fp->f_flag & FSOCKET) == 0) {
		u.u_error = ENOTSOCK;
		return;
	}
D 2
	disconnect(fp->f_socket, uap->a ? &in : 0);
E 2
I 2
	disconnect(fp->f_socket, uap->addr ? &in : 0);
E 2
}

E 3
disconnect(so, iap)
E 6
I 6
sodisconnect(so, asa)
E 50
I 50
D 106
sodisconnect(so, nam)
E 106
I 106
sodisconnect(so)
E 106
E 50
E 6
D 76
	struct socket *so;
E 76
I 76
	register struct socket *so;
E 76
D 6
	struct in_addr *iap;
E 6
I 6
D 50
	struct sockaddr *asa;
E 50
I 50
D 106
	struct mbuf *nam;
E 106
E 50
E 6
{
I 3
	int s = splnet();
	int error;
E 3

I 6
D 42
COUNT(SODISCONNECT);
E 42
E 6
D 2
	u.u_error = (*so->so_proto->pr_usrreq)(so, PRU_DISCONNECT, 0, &in);
E 2
I 2
D 3
	u.u_error = (*so->so_proto->pr_usrreq)(so, PRU_DISCONNECT, 0, iap);
E 2
}

/*
 * Send data on socket.
 */
ssend()
{
	register struct a {
D 2
		int fdes;
		in_addr *ain;
		caddr_t cbuf;
		int count;
E 2
I 2
		int	fdes;
		in_addr	*ain;
		caddr_t	cbuf;
		int	count;
E 2
	} *uap = (struct a *)u.u_ap;
I 2
	register struct file *fp;
	struct in_addr in;
E 2

	fp = getf(uap->fdes);
	if (fp == 0)
		return;
	if ((fp->f_flag & FSOCKET) == 0) {
		u.u_error = ENOTSOCK;
		return;
E 3
I 3
	if ((so->so_state & SS_ISCONNECTED) == 0) {
		error = ENOTCONN;
		goto bad;
E 3
	}
D 3
	if (uap->count < 0) {
		u.u_error = EINVAL;
		return;
E 3
I 3
	if (so->so_state & SS_ISDISCONNECTING) {
		error = EALREADY;
		goto bad;
E 3
	}
D 2
	u.u_base = uap->buf;
	u.u_count = uap->len;
E 2
I 2
D 3
	u.u_base = uap->cbuf;
	u.u_count = uap->count;
E 2
	u.u_segflg = 0;
	if (useracc(u.u_base, u.u_count, B_READ) == 0 ||
	    uap->ain && copyin((caddr_t)uap->ain, (caddr_t)&in, sizeof (in))) {
		u.u_error = EFAULT;
		return;
	}
	u.u_error = send(fp->f_socket, uap->ain ? &in : 0);
E 3
I 3
D 6
	error = (*so->so_proto->pr_usrreq)(so, PRU_DISCONNECT, 0, 0);
E 6
I 6
D 50
	error = (*so->so_proto->pr_usrreq)(so, PRU_DISCONNECT, 0, asa);
E 50
I 50
	error = (*so->so_proto->pr_usrreq)(so, PRU_DISCONNECT,
D 68
	    (struct mbuf *)0, nam, (struct socketopt *)0);
E 68
I 68
D 76
	    (struct mbuf *)0, nam);
E 76
I 76
D 106
	    (struct mbuf *)0, nam, (struct mbuf *)0);
E 106
I 106
	    (struct mbuf *)0, (struct mbuf *)0, (struct mbuf *)0);
E 106
E 76
E 68
E 50
E 6
bad:
	splx(s);
	return (error);
E 3
}

I 144
#define	SBLOCKWAIT(f)	(((f) & MSG_DONTWAIT) ? M_NOWAIT : M_WAITOK)
E 144
I 3
/*
 * Send on a socket.
 * If send must go all at once and message is larger than
 * send buffering, then hard error.
 * Lock against other senders.
 * If must go all at once and not enough room now, then
 * inform user that this would block and do nothing.
I 85
 * Otherwise, if nonblocking, send as much as possible.
I 129
 * The data to be sent is described by "uio" if nonzero,
 * otherwise by the mbuf chain "top" (which must be null
 * if uio is not).  Data provided in mbuf chain must be small
 * enough to send all at once.
 *
 * Returns nonzero on error, timeout or signal; callers
 * must check for short counts if EINTR/ERESTART are returned.
 * Data and control buffers are freed on return.
E 129
E 85
 */
I 158
int
E 158
E 3
D 6
send(so, iap)
E 6
I 6
D 48
sosend(so, asa)
E 48
I 48
D 50
sosend(so, asa, uio)
E 50
I 50
D 51
sosend(so, nam, uio)
E 51
I 51
D 76
sosend(so, nam, uio, flags)
E 76
I 76
D 122
sosend(so, nam, uio, flags, rights)
E 122
I 122
D 127
sosend(so, nam, uio, flags, rights, control)
E 127
I 127
D 129
sosend(so, nam, uio, flags, control)
E 129
I 129
D 132
sosend(so, addr, uio, top, control, flags/*, sbwait_func, sbwait_arg*/)
E 132
I 132
sosend(so, addr, uio, top, control, flags)
E 132
E 129
E 127
E 122
E 76
E 51
E 50
E 48
E 6
	register struct socket *so;
D 5
	struct in_addr *iap;
E 5
I 5
D 6
	struct inaddr *iap;
E 6
I 6
D 50
	struct sockaddr *asa;
E 50
I 50
D 129
	struct mbuf *nam;
E 50
I 48
D 76
	struct uio *uio;
E 76
I 76
	register struct uio *uio;
E 76
I 51
	int flags;
E 129
I 129
	struct mbuf *addr;
	struct uio *uio;
	struct mbuf *top;
E 129
I 76
D 122
	struct mbuf *rights;
E 122
I 122
D 127
	struct mbuf *rights, *control;
E 127
I 127
	struct mbuf *control;
I 129
	int flags;
D 132
/*
	int (*sbwait_func)();
	caddr_t sbwait_arg;
*/
E 132
E 129
E 127
E 122
E 76
E 51
E 48
E 6
E 5
{
I 140
	struct proc *p = curproc;		/* XXX */
E 140
D 3
	register struct mbuf *m, **mp;
	struct mbuf *top;
E 3
I 3
D 122
	struct mbuf *top = 0;
D 85
	register struct mbuf *m, **mp = &top;
E 85
I 85
	register struct mbuf *m, **mp;
E 85
D 5
	register int bufs;
	register int len;
E 3
	int error = 0;
I 3
	int s;
E 5
I 5
D 57
	register u_int len;
E 57
I 57
D 76
	register int len;
E 57
D 68
	int error = 0, space, s;
E 68
I 68
	int error = 0, space, s, dontroute;
E 76
I 76
	register int space;
D 85
	int len, error = 0, s, dontroute;
I 84
	struct sockbuf sendtempbuf;
E 85
I 85
D 103
	int len, error = 0, s, dontroute, first = 1;
E 103
I 103
	int len, rlen = 0, error = 0, s, dontroute, first = 1;
E 122
I 122
D 129
	struct mbuf *top = 0, **mp;
E 129
I 129
	struct mbuf **mp;
E 129
	register struct mbuf *m;
D 129
	register int space, len;
D 128
	int rlen = 0, error = 0, s, dontroute, first = 1, mlen;
E 128
I 128
	int rlen = 0, error, s, dontroute, mlen;
E 128
	int atomic = sosendallatonce(so);
E 129
I 129
	register long space, len, resid;
	int clen = 0, error, s, dontroute, mlen;
	int atomic = sosendallatonce(so) || top;
E 129
E 122
E 103
E 85
E 84
E 76
E 68
E 5
E 3

I 6
D 42
COUNT(SOSEND);
E 42
E 6
D 3
	if (so->so_proto->pr_flags & PR_ATOMIC) {
		if (u.u_count > so->so_snd.sb_hiwat) {
			error = EMSGSIZE;
E 3
I 3
D 31
	if (so->so_state & SS_CANTSENDMORE)
E 31
I 31
D 38
	if (so->so_state & SS_CANTSENDMORE) {
		psignal(u.u_procp, SIGPIPE);
E 31
		return (EPIPE);
I 31
	}
E 38
E 31
D 48
	if (sosendallatonce(so) && u.u_count > so->so_snd.sb_hiwat)
E 48
I 48
D 122
	if (sosendallatonce(so) && uio->uio_resid > so->so_snd.sb_hiwat)
E 122
I 122
D 129
	if (atomic && uio->uio_resid > so->so_snd.sb_hiwat)
E 122
E 48
		return (EMSGSIZE);
E 129
I 129
	if (uio)
		resid = uio->uio_resid;
	else
		resid = top->m_pkthdr.len;
I 157
	/*
	 * In theory resid should be unsigned.
	 * However, space must be signed, as it might be less than 0
	 * if we over-committed, and we must use a signed comparison
	 * of space and resid.  On the other hand, a negative resid
	 * causes us to loop sending 0-length segments to the protocol.
	 */
	if (resid < 0)
		return (EINVAL);
E 157
E 129
I 68
D 76
	dontroute = (flags & SOF_DONTROUTE) &&
		(so->so_options & SO_DONTROUTE) == 0 &&
		(so->so_proto->pr_flags & PR_ATOMIC);
E 76
I 76
	dontroute =
	    (flags & MSG_DONTROUTE) && (so->so_options & SO_DONTROUTE) == 0 &&
	    (so->so_proto->pr_flags & PR_ATOMIC);
E 76
E 68
I 38
D 51
#ifdef notdef
	/* NEED TO PREVENT BUSY WAITING IN SELECT FOR WRITING */
E 38
D 23
	if ((so->so_snd.sb_flags & SB_LOCK) && (so->so_options & SO_NBIO))
E 23
I 23
D 34
	if ((so->so_snd.sb_flags & SB_LOCK) && (so->so_options & SO_NONBLOCKING))
E 34
I 34
	if ((so->so_snd.sb_flags & SB_LOCK) && (so->so_state & SS_NBIO))
E 34
E 23
		return (EWOULDBLOCK);
I 38
#endif
E 51
D 85
restart:
E 38
	sblock(&so->so_snd);
E 85
I 85
D 140
	u.u_ru.ru_msgsnd++;
E 140
I 140
	p->p_stats->p_ru.ru_msgsnd++;
E 140
I 103
D 127
	if (rights)
		rlen = rights->m_len;
E 127
I 127
	if (control)
D 129
		rlen = control->m_len;
E 129
I 129
		clen = control->m_len;
E 129
E 127
E 103
E 85
#define	snderr(errno)	{ error = errno; splx(s); goto release; }

I 49
D 85
	u.u_ru.ru_msgsnd++;
E 49
D 38
	s = splnet();
E 38
I 13
D 14
	nullchk("sosend in", so->so_snd.sb_mb);
E 14
E 13
again:
I 38
	s = splnet();
	if (so->so_state & SS_CANTSENDMORE) {
		psignal(u.u_procp, SIGPIPE);
		snderr(EPIPE);
	}
E 38
I 16
	if (so->so_error) {
		error = so->so_error;
D 38
		so->so_error = 0;
E 38
I 38
		so->so_error = 0;				/* ??? */
E 85
I 85
restart:
D 128
	sblock(&so->so_snd);
E 128
I 128
D 144
	if (error = sblock(&so->so_snd))
E 144
I 144
	if (error = sblock(&so->so_snd, SBLOCKWAIT(flags)))
E 144
D 129
		return (error);
E 129
I 129
		goto out;
E 129
E 128
	do {
		s = splnet();
D 95
		if (so->so_state & SS_CANTSENDMORE) {
			psignal(u.u_procp, SIGPIPE);
E 95
I 95
		if (so->so_state & SS_CANTSENDMORE)
E 95
			snderr(EPIPE);
D 95
		}
E 95
D 124
		if (so->so_error) {
			error = so->so_error;
			so->so_error = 0;			/* ??? */
			splx(s);
			goto release;
		}
E 124
I 124
		if (so->so_error)
			snderr(so->so_error);
E 124
		if ((so->so_state & SS_ISCONNECTED) == 0) {
D 124
			if (so->so_proto->pr_flags & PR_CONNREQUIRED)
				snderr(ENOTCONN);
			if (nam == 0)
E 124
I 124
			if (so->so_proto->pr_flags & PR_CONNREQUIRED) {
D 126
				if (!uio->uio_resid && !rights && control) {
					snderr((*so->so_proto->pr_usrreq)(so,
				    (flags & MSG_OOB) ? PRU_SENDOOB : PRU_SEND,
					    top, (caddr_t)0, rights, control));
				} else if (so->so_state & SS_ISCONFIRMING)
					/* is ok */;
				else
E 126
I 126
D 139
				if ((so->so_state & SS_ISCONFIRMING) == 0)
E 139
I 139
				if ((so->so_state & SS_ISCONFIRMING) == 0 &&
				    !(resid == 0 && clen != 0))
E 139
E 126
					snderr(ENOTCONN);
D 129
			} else if (nam == 0)
E 129
I 129
			} else if (addr == 0)
E 129
E 124
				snderr(EDESTADDRREQ);
		}
I 129
		space = sbspace(&so->so_snd);
E 129
		if (flags & MSG_OOB)
D 129
			space = 1024;
		else {
			space = sbspace(&so->so_snd);
D 103
			if (space <= 0 ||
D 87
			    sosendallatonce(so) && space < uio->uio_resid) {
E 87
I 87
			   (sosendallatonce(so) && space < uio->uio_resid) ||
E 103
I 103
			if (space <= rlen ||
D 122
			   (sosendallatonce(so) &&
				space < uio->uio_resid + rlen) ||
E 103
			   (uio->uio_resid >= CLBYTES && space < CLBYTES &&
			   so->so_snd.sb_cc >= CLBYTES &&
E 122
I 122
			   (atomic && space < uio->uio_resid + rlen) ||
			   (uio->uio_resid >= MCLBYTES && space < MCLBYTES &&
			   so->so_snd.sb_cc >= MCLBYTES &&
E 122
			   (so->so_state & SS_NBIO) == 0)) {
E 87
D 128
				if (so->so_state & SS_NBIO) {
					if (first)
						error = EWOULDBLOCK;
					splx(s);
					goto release;
				}
E 128
I 128
				if (so->so_state & SS_NBIO)
					snderr(EWOULDBLOCK);
E 128
				sbunlock(&so->so_snd);
D 128
				sbwait(&so->so_snd);
E 128
I 128
				if (error = sbwait(&so->so_snd))
					snderr(error);
E 128
				splx(s);
				goto restart;
			}
E 129
I 129
			space += 1024;
D 144
		if (space < resid + clen &&
E 144
I 144
		if (atomic && resid > so->so_snd.sb_hiwat ||
		    clen > so->so_snd.sb_hiwat)
			snderr(EMSGSIZE);
		if (space < resid + clen && uio &&
E 144
		    (atomic || space < so->so_snd.sb_lowat || space < clen)) {
D 144
			if (atomic && resid > so->so_snd.sb_hiwat ||
			    clen > so->so_snd.sb_hiwat)
				snderr(EMSGSIZE);
E 144
			if (so->so_state & SS_NBIO)
				snderr(EWOULDBLOCK);
			sbunlock(&so->so_snd);
D 132
/*
			if (sbwait_func)
				error = (*sbwait_func)(&so->so_snd, sbwait_arg);
			else
*/
				error = sbwait(&so->so_snd);
E 132
I 132
			error = sbwait(&so->so_snd);
E 132
			splx(s);
			if (error)
				goto out;
			goto restart;
E 129
		}
E 85
E 38
		splx(s);
D 85
		goto release;
	}
E 16
	if ((so->so_state & SS_ISCONNECTED) == 0) {
		if (so->so_proto->pr_flags & PR_CONNREQUIRED)
			snderr(ENOTCONN);
D 6
		if (iap == 0)
E 6
I 6
D 50
		if (asa == 0)
E 50
I 50
		if (nam == 0)
E 50
E 6
			snderr(EDESTADDRREQ);
	}
D 16
	if (so->so_error)
		snderr(so->so_error);
E 16
	if (top) {
E 85
I 85
		mp = &top;
I 103
D 129
		space -= rlen;
E 103
D 95
		while (uio->uio_resid > 0 && space > 0) {
E 95
I 95
D 122
		while (space > 0) {
E 95
D 109
			register struct iovec *iov = uio->uio_iov;

E 109
D 95
			if (iov->iov_len == 0) {
				uio->uio_iov++;
				uio->uio_iovcnt--;
				if (uio->uio_iovcnt < 0)
					panic("sosend");
				continue;
			}
E 95
			MGET(m, M_WAIT, MT_DATA);
D 92
			if (m == NULL) {
				error = ENOBUFS;		/* SIGPIPE? */
				goto release;
			}
E 92
I 92
D 95
if (m == NULL) {
	error = ENOBUFS;		/* SIGPIPE? */
	goto release;
}
E 95
E 92
D 96
			if (iov->iov_len >= CLBYTES && space >= CLBYTES) {
E 96
I 96
D 109
			if (iov->iov_len >= NBPG && space >= CLBYTES) {
E 109
I 109
			if (uio->uio_resid >= CLBYTES / 2 && space >= CLBYTES) {
E 109
E 96
D 105
				register struct mbuf *p;
				MCLGET(p, 1);
				if (p == 0)
E 105
I 105
				MCLGET(m);
				if (m->m_len != CLBYTES)
E 122
I 122
		do {
E 129
I 129
		space -= clen;
D 132
		if (uio == NULL) {
E 132
I 132
		do {
		    if (uio == NULL) {
E 132
			/*
			 * Data is prepackaged in "top".
			 */
			resid = 0;
			if (flags & MSG_EOR)
				top->m_flags |= M_EOR;
D 132
		} else do {
E 129
		   do {
E 132
I 132
		    } else do {
E 132
			if (top == 0) {
				MGETHDR(m, M_WAIT, MT_DATA);
				mlen = MHLEN;
				m->m_pkthdr.len = 0;
				m->m_pkthdr.rcvif = (struct ifnet *)0;
			} else {
				MGET(m, M_WAIT, MT_DATA);
				mlen = MLEN;
			}
D 129
			if (uio->uio_resid >= MINCLSIZE && space >= MCLBYTES) {
E 129
I 129
			if (resid >= MINCLSIZE && space >= MCLBYTES) {
E 129
				MCLGET(m, M_WAIT);
				if ((m->m_flags & M_EXT) == 0)
E 122
E 105
					goto nopages;
D 105
				m->m_off = (int)p - (int)m;
E 105
D 96
				len = CLBYTES;
E 96
I 96
D 100
				len = min(CLBYTES, iov->iov_len);
E 100
I 100
D 109
				len = MIN(CLBYTES, iov->iov_len);
E 109
I 109
D 122
				len = MIN(CLBYTES, uio->uio_resid);
E 109
E 100
				space -= CLBYTES;
E 122
I 122
				mlen = MCLBYTES;
#ifdef	MAPPED_MBUFS
D 129
				len = min(MCLBYTES, uio->uio_resid);
				if (len < mlen - max_hdr)
					m->m_data += max_hdr;
E 129
I 129
				len = min(MCLBYTES, resid);
E 129
#else
D 129
				len = min(MCLBYTES - max_hdr, uio->uio_resid);
				m->m_data += max_hdr;
E 129
I 129
D 154
				if (top == 0) {
E 154
I 154
				if (atomic && top == 0) {
E 154
					len = min(MCLBYTES - max_hdr, resid);
					m->m_data += max_hdr;
D 137
				}
E 137
I 137
				} else
					len = min(MCLBYTES, resid);
E 137
E 129
#endif
				space -= MCLBYTES;
E 122
E 96
			} else {
nopages:
D 103
				len = MIN(MLEN, iov->iov_len);
E 103
I 103
D 109
				len = MIN(MIN(MLEN, iov->iov_len), space);
E 109
I 109
D 122
				len = MIN(MIN(MLEN, uio->uio_resid), space);
E 122
I 122
D 129
				len = min(min(mlen, uio->uio_resid), space);
E 129
I 129
				len = min(min(mlen, resid), space);
E 129
E 122
E 109
E 103
I 96
				space -= len;
I 122
				/*
				 * For datagram protocols, leave room
				 * for protocol headers in first mbuf.
				 */
D 123
				if (atomic && len < mlen)
E 123
I 123
				if (atomic && top == 0 && len < mlen)
E 123
					MH_ALIGN(m, len);
E 122
E 96
			}
D 125
			error = uiomove(mtod(m, caddr_t), len, UIO_WRITE, uio);
E 125
I 125
D 136
			error = uiomove(mtod(m, caddr_t), len, uio);
E 136
I 136
			error = uiomove(mtod(m, caddr_t), (int)len, uio);
E 136
I 129
			resid = uio->uio_resid;
E 129
E 125
			m->m_len = len;
			*mp = m;
I 122
			top->m_pkthdr.len += len;
E 122
			if (error)
				goto release;
			mp = &m->m_next;
D 96
			space -= len;
E 96
I 95
D 122
			if (uio->uio_resid <= 0)
E 122
I 122
D 129
			if (uio->uio_resid <= 0) {
				if ((flags & MSG_EOR) && top)
E 129
I 129
			if (resid <= 0) {
				if (flags & MSG_EOR)
E 129
					top->m_flags |= M_EOR;
E 122
				break;
D 109
			while (uio->uio_iov->iov_len == 0) {
				uio->uio_iov++;
				uio->uio_iovcnt--;
				if (uio->uio_iovcnt <= 0)
					panic("sosend");
			}
E 109
E 95
D 122
		}
E 85
I 68
D 87
		if (dontroute)
			so->so_options |= SO_DONTROUTE;
I 86
		s = splnet();
E 86
E 68
D 6
		error = (*so->so_proto->pr_usrreq)(so, PRU_SEND, top, iap);
E 6
I 6
D 50
		error = (*so->so_proto->pr_usrreq)(so, PRU_SEND, top, asa);
E 50
I 50
D 51
		error = (*so->so_proto->pr_usrreq)(so, PRU_SEND,
E 51
I 51
		error = (*so->so_proto->pr_usrreq)(so,
D 76
		    (flags & SOF_OOB) ? PRU_SENDOOB : PRU_SEND,
E 51
D 68
		    top, (caddr_t)nam, (struct socketopt *)0);
E 68
I 68
		    top, (caddr_t)nam);
E 76
I 76
		    (flags & MSG_OOB) ? PRU_SENDOOB : PRU_SEND,
		    top, (caddr_t)nam, rights);
I 86
		splx(s);
E 86
E 76
		if (dontroute)
			so->so_options &= ~SO_DONTROUTE;
E 87
I 87
D 95
		if (top) {
			if (dontroute)
				so->so_options |= SO_DONTROUTE;
			s = splnet();
			error = (*so->so_proto->pr_usrreq)(so,
			    (flags & MSG_OOB) ? PRU_SENDOOB : PRU_SEND,
			    top, (caddr_t)nam, rights);
			splx(s);
			if (dontroute)
				so->so_options &= ~SO_DONTROUTE;
		}
E 95
I 95
		if (dontroute)
			so->so_options |= SO_DONTROUTE;
		s = splnet();					/* XXX */
		error = (*so->so_proto->pr_usrreq)(so,
		    (flags & MSG_OOB) ? PRU_SENDOOB : PRU_SEND,
		    top, (caddr_t)nam, rights);
		splx(s);
		if (dontroute)
			so->so_options &= ~SO_DONTROUTE;
I 96
		rights = 0;
I 103
		rlen = 0;
E 103
E 96
E 95
E 87
E 68
E 50
I 38
		top = 0;
E 38
I 13
D 14
		nullchk("sosend after PRU_SEND", so->so_snd.sb_mb);
E 14
E 13
E 6
D 85
		if (error) {
			splx(s);
E 3
			goto release;
		}
I 3
D 38
		top = 0;
E 38
		mp = &top;
I 9
	}
D 48
	if (u.u_count == 0) {
E 48
I 48
	if (uio->uio_resid == 0) {
E 48
		splx(s);
		goto release;
E 9
E 3
	}
D 3
again:
	while (so->so_snd.sb_flags & SB_LOCK) {
		so->so_snd.sb_flags |= SB_WANT;
		sleep((caddr_t)&so->so_snd.sb_flags, PZERO+1);
	}
	if (so->so_snd.sb_hiwat - so->so_snd.sb_cc < u.u_count) {
		so->so_snd.sb_flags |= SB_WAIT;
		sleep((caddr_t)&so->so_snd.sb_cc, PZERO+1);
E 3
I 3
D 12
	if (sosendallatonce(so) && sbspace(&so->so_snd) < u.u_count) {
E 12
I 12
D 51
	space = sbspace(&so->so_snd);
D 30
	if (space == 0 || sosendallatonce(so) && space < u.u_count) {
E 30
I 30
D 48
	if (space <= 0 || sosendallatonce(so) && space < u.u_count) {
E 48
I 48
	if (space <= 0 || sosendallatonce(so) && space < uio->uio_resid) {
E 48
E 30
E 12
D 23
		if (so->so_options & SO_NBIO)
E 23
I 23
D 34
		if (so->so_options & SO_NONBLOCKING)
E 34
I 34
		if (so->so_state & SS_NBIO)
E 34
E 23
			snderr(EWOULDBLOCK);
		sbunlock(&so->so_snd);
		sbwait(&so->so_snd);
		splx(s);
E 3
D 38
		goto again;
E 38
I 38
		goto restart;
E 51
I 51
D 76
	if (flags & SOF_OOB)
E 76
I 76
	if (flags & MSG_OOB)
E 76
		space = 1024;
	else {
		space = sbspace(&so->so_snd);
		if (space <= 0 ||
		    sosendallatonce(so) && space < uio->uio_resid) {
			if (so->so_state & SS_NBIO)
				snderr(EWOULDBLOCK);
			sbunlock(&so->so_snd);
			sbwait(&so->so_snd);
			splx(s);
			goto restart;
		}
E 51
E 38
	}
D 3
	so->so_snd.sb_flags |= SB_LOCK;
	while (u.u_count > 0) {
D 2
		bufs = so->so_snd.sb_mbmax - so->so_snd.sb_mbcnt;
E 2
I 2
		register int bufs = so->so_snd.sb_mbmax - so->so_snd.sb_mbcnt;
E 2
		while (bufs == 0) {
			so->so_snd.sb_flags |= SB_WAIT;
			sleep((caddr_t)&so->so_snd.sb_cc, PZERO+1);
E 3
I 3
	splx(s);
I 84
	/*
	 * Temporary kludge-- don't want to update so_snd in this loop
	 * (will be done when sent), but need to recalculate
	 * space on each iteration.  For now, copy so_snd into a tmp.
	 */
	sendtempbuf = so->so_snd;
E 84
D 5
	while (u.u_count > 0 && sbspace(&so->so_snd) > 0) {
E 5
I 5
D 12
	while (u.u_count && (space = sbspace(&so->so_snd)) > 0) {
E 12
I 12
D 48
	while (u.u_count && space > 0) {
E 48
I 48
	while (uio->uio_resid > 0 && space > 0) {
		register struct iovec *iov = uio->uio_iov;

		if (iov->iov_len == 0) {
			uio->uio_iov++;
			uio->uio_iovcnt--;
			if (uio->uio_iovcnt < 0)
				panic("sosend");
			continue;
		}
E 48
E 12
E 5
D 66
		MGET(m, 1);
E 66
I 66
		MGET(m, M_WAIT, MT_DATA);
E 66
		if (m == NULL) {
D 38
			error = ENOBUFS;
			m_freem(top);
E 38
I 38
			error = ENOBUFS;			/* SIGPIPE? */
E 38
			goto release;
E 3
		}
D 3
		mp = &top;
		top = 0;
		while (--bufs >= 0 && u.u_count > 0) {
I 2
			register int len;
E 2
			MGET(m, 1);
			if (m == NULL) {
				error = ENOBUFS;
				m_freem(top);
				goto release;
			}
			if (u.u_count >= PGSIZE && bufs >= NMBPG) {
I 2
				register struct mbuf *p;
E 2
				MPGET(p, 1);
				if (p == 0)
D 2
					goto nopage;
E 2
I 2
					goto nopages;
E 2
				m->m_off = (int)p - (int)m;
				len = PGSIZE;
			} else {
E 3
I 3
D 5
		if (u.u_count >= PGSIZE && bufs >= NMBPG) {
E 5
I 5
D 15
		if (u.u_count >= PGSIZE && space >= NMBPG) {
E 15
I 15
D 48
		if (u.u_count >= CLBYTES && space >= CLBYTES) {
E 48
I 48
		if (iov->iov_len >= CLBYTES && space >= CLBYTES) {
E 48
E 15
E 5
			register struct mbuf *p;
D 15
			MPGET(p, 1);
E 15
I 15
			MCLGET(p, 1);
E 15
			if (p == 0)
				goto nopages;
			m->m_off = (int)p - (int)m;
D 15
			len = PGSIZE;
E 15
I 15
			len = CLBYTES;
E 15
		} else {
E 3
nopages:
D 3
				m->m_off = MMINOFF;
				len = MIN(MLEN, u.u_count);
			}
			iomove(mtod(m, caddr_t), len, B_WRITE);
			m->m_len = len;
			*mp = m;
			mp = &m->m_next;
E 3
I 3
D 51
			m->m_off = MMINOFF;
E 51
D 48
			len = MIN(MLEN, u.u_count);
E 48
I 48
			len = MIN(MLEN, iov->iov_len);
E 48
E 3
		}
D 2
		s = splnet();
		error = (*so->so_proto->pr_usrreq)(so, PRU_SEND, top, iap);
		splx(s);
E 2
I 2
D 3
		{ register int s = splnet();
		  error = (*so->so_proto->pr_usrreq)(so, PRU_SEND, top, iap);
		  splx(s); }
E 2
		if (error)
			break;
E 3
I 3
D 48
		iomove(mtod(m, caddr_t), len, B_WRITE);
E 48
I 48
D 59
		uiomove(mtod(m, caddr_t), len, UIO_WRITE, uio);
E 59
I 59
D 79
		(void) uiomove(mtod(m, caddr_t), len, UIO_WRITE, uio);
E 79
I 79
		error = uiomove(mtod(m, caddr_t), len, UIO_WRITE, uio);
E 79
E 59
E 48
I 13
D 14
		nullblk("sosend", m, len);
E 14
E 13
		m->m_len = len;
		*mp = m;
E 85
I 85
		first = 0;
E 85
I 79
		if (error)
D 85
			goto release;
E 79
		mp = &m->m_next;
I 12
D 51
		space = sbspace(&so->so_snd);
E 51
I 51
D 76
		if (flags & SOF_OOB)
E 76
I 76
		if (flags & MSG_OOB)
E 76
			space -= len;
D 84
		else
			space = sbspace(&so->so_snd);
E 84
I 84
		else {
			sballoc(&sendtempbuf, m);
			space = sbspace(&sendtempbuf);
		}
E 84
E 51
E 12
E 3
	}
I 13
D 14
	nullchk("sosend top", top);
E 14
E 13
I 3
D 38
	s = splnet();
E 38
	goto again;
E 85
I 85
			break;
E 122
I 122
			}
		    } while (space > 0 && atomic);
		    if (dontroute)
			    so->so_options |= SO_DONTROUTE;
		    s = splnet();				/* XXX */
		    error = (*so->so_proto->pr_usrreq)(so,
			(flags & MSG_OOB) ? PRU_SENDOOB : PRU_SEND,
D 127
			top, (caddr_t)nam, rights, control);
E 127
I 127
D 129
			top, (caddr_t)nam, control);
E 129
I 129
			top, addr, control);
E 129
E 127
		    splx(s);
		    if (dontroute)
			    so->so_options &= ~SO_DONTROUTE;
D 127
		    rights = 0;
E 127
D 129
		    rlen = 0;
E 129
I 129
		    clen = 0;
		    control = 0;
E 129
		    top = 0;
		    mp = &top;
D 128
		    first = 0;
E 128
		    if (error)
			goto release;
D 129
		} while (uio->uio_resid && space > 0);
E 122
	} while (uio->uio_resid);
E 129
I 129
		} while (resid && space > 0);
	} while (resid);
E 129
E 85

E 3
release:
D 3
	so->so_snd.sb_flags &= ~SB_LOCK;
	if (so->so_snd.sb_flags & SB_WANT)
D 2
		wakeup((caddr_t)&so->so_sb.sb_flags);
E 2
I 2
		wakeup((caddr_t)&so->so_snd.sb_flags);
E 3
I 3
	sbunlock(&so->so_snd);
I 129
out:
E 129
I 38
	if (top)
		m_freem(top);
I 129
	if (control)
		m_freem(control);
E 129
I 95
D 128
	if (error == EPIPE)
		psignal(u.u_procp, SIGPIPE);
E 128
E 95
E 38
E 3
E 2
	return (error);
}

I 103
/*
 * Implement receive operations on a socket.
 * We depend on the way that records are added to the sockbuf
 * by sbappend*.  In particular, each record (mbufs linked through m_next)
 * must begin with an address if the protocol so specifies,
D 129
 * followed by an optional mbuf containing access rights if supported
 * by the protocol, and then zero or more mbufs of data.
E 129
I 129
 * followed by an optional mbuf or mbufs containing ancillary data,
 * and then zero or more mbufs of data.
E 129
 * In order to avoid blocking network interrupts for the entire time here,
 * we splx() while doing the actual copy to user space.
 * Although the sockbuf is locked, new data may still be appended,
 * and thus we must maintain consistency of the sockbuf during that time.
I 129
D 136
 * 
E 136
I 136
 *
E 136
 * The caller may receive the data as a single mbuf chain by supplying
D 132
 * an mbuf **mp for use in returning the chain.  The uio is then used
E 132
I 132
 * an mbuf **mp0 for use in returning the chain.  The uio is then used
E 132
 * only for the count in uio_resid.
E 129
 */
I 158
int
E 158
E 103
D 3
/*
 * Receive data on socket.
 */
sreceive()
{
	register struct a {
D 2
		int fdes;
		in_addr *ain;
		caddr_t cbuf;
		int count;
E 2
I 2
		int	fdes;
		in_addr	*ain;
		caddr_t	cbuf;
		int	count;
E 2
	} *uap = (struct a *)u.u_ap;
I 2
	register struct file *fp;
	struct in_addr *in;
E 2

	fp = getf(uap->fdes);
	if (fp == 0)
		return;
	if ((fp->f_flag & FSOCKET) == 0) {
		u.u_error = ENOTSOCK;
		return;
	}
	if (uap->count < 0) {
		u.u_error = EINVAL;
		return;
	}
D 2
	u.u_base = uap->buf;
	u.u_count = uap->len;
E 2
I 2
	u.u_base = uap->cbuf;
	u.u_count = uap->count;
E 2
	u.u_segflg = 0;
	if (useracc(u.u_base, u.u_count, B_WRITE) == 0 ||
	    uap->ain && copyin((caddr_t)uap->ain, (caddr_t)&in, sizeof (in))) {
		u.u_error = EFAULT;
		return;
	}
	receive(fp->f_socket, uap->ain ? &in : 0);
}

E 3
D 6
receive(so, iap)
E 6
I 6
D 47
soreceive(so, asa)
E 47
I 47
D 50
soreceive(so, asa, uio)
E 50
I 50
D 51
soreceive(so, aname, uio)
E 51
I 51
D 76
soreceive(so, aname, uio, flags)
E 76
I 76
D 122
soreceive(so, aname, uio, flags, rightsp)
E 122
I 122
D 129
soreceive(so, aname, uio, flagsp, rightsp, controlp)
E 129
I 129
D 132
soreceive(so, paddr, uio, mp, controlp, flagsp/*, sbwait_func, sbwait_arg*/)
E 132
I 132
soreceive(so, paddr, uio, mp0, controlp, flagsp)
E 132
E 129
E 122
E 76
E 51
E 50
E 47
E 6
	register struct socket *so;
D 5
	struct in_addr *iap;
E 5
I 5
D 6
	struct inaddr *iap;
E 6
I 6
D 50
	struct sockaddr *asa;
E 50
I 50
D 129
	struct mbuf **aname;
E 50
I 47
D 76
	struct uio *uio;
E 76
I 76
	register struct uio *uio;
E 129
I 129
	struct mbuf **paddr;
	struct uio *uio;
D 132
	struct mbuf **mp;
E 132
I 132
	struct mbuf **mp0;
E 132
	struct mbuf **controlp;
E 129
E 76
I 51
D 122
	int flags;
I 76
	struct mbuf **rightsp;
E 122
I 122
	int *flagsp;
D 129
	struct mbuf **rightsp, **controlp;
E 129
I 129
D 132
/*
	int (*sbwait_func)();
	caddr_t sbwait_arg;
*/
E 132
E 129
E 122
E 76
E 51
E 47
E 6
E 5
{
I 140
D 147
	struct proc *p = curproc;		/* XXX */
E 147
E 140
I 47
D 56
	register struct iovec *iov;
E 56
E 47
D 109
	register struct mbuf *m, *n;
E 109
I 109
D 132
	register struct mbuf *m;
E 109
D 3
	register int eor, len, s;
E 3
I 3
D 5
	register int len;
E 5
I 5
D 57
	u_int len;
E 57
I 57
D 76
	int len;
E 57
E 5
D 25
	int eor, s, error = 0;
E 25
I 25
D 47
	int eor, s, error = 0, cnt = u.u_count;
	caddr_t base = u.u_base;
E 47
I 47
D 48
	int eor, s, error = 0, resid = uio->uio_resid;
	int cnt;
E 48
I 48
D 51
	int eor, s, error = 0;
E 51
I 51
	int eor, s, error = 0, moff, tomark;
E 76
I 76
D 88
	register int len, error = 0, s, eor, tomark;
E 88
I 88
D 115
	register int len, error = 0, s, tomark;
E 115
I 115
D 122
	register int len, error = 0, s, offset;
E 122
I 122
D 128
	register int flags, len, error = 0, s, offset;
E 128
I 128
D 129
	register int flags, len, error, s, offset;
E 129
I 129
	register int resid, flags, len, error, s, offset;
E 132
I 132
	register struct mbuf *m, **mp;
	register int flags, len, error, s, offset;
E 132
E 129
E 128
E 122
E 115
E 88
	struct protosw *pr = so->so_proto;
I 88
D 127
	struct mbuf *nextrecord;
E 127
I 127
D 129
	struct mbuf *nextrecord, *m_with_eor;
E 127
E 88
	int moff;
E 129
I 129
	struct mbuf *nextrecord;
	int moff, type;
I 151
	int orig_resid = uio->uio_resid;
E 151
E 129
E 76
E 51
E 48
E 47
E 25
E 3

I 132
	mp = mp0;
E 132
I 51
D 76
	if (flags & SOF_OOB) {
E 76
I 76
D 129
	if (rightsp)
		*rightsp = 0;
	if (aname)
		*aname = 0;
E 129
I 129
	if (paddr)
		*paddr = 0;
E 129
I 122
	if (controlp)
		*controlp = 0;
	if (flagsp)
		flags = *flagsp &~ MSG_EOR;
D 136
	else 
E 136
I 136
	else
E 136
		flags = 0;
E 122
	if (flags & MSG_OOB) {
E 76
D 56
		struct mbuf *m = m_get(M_WAIT);

		(*so->so_proto->pr_usrreq)(so, PRU_RCVOOB,
E 56
I 56
D 66
		m = m_get(M_WAIT);
E 66
I 66
		m = m_get(M_WAIT, MT_DATA);
I 67
D 76
		if (m == NULL)
E 76
I 76
D 95
		if (m == 0)
E 76
			return (ENOBUFS);
E 95
E 67
E 66
D 76
		error = (*so->so_proto->pr_usrreq)(so, PRU_RCVOOB,
E 56
D 68
		    m, (struct mbuf *)0, (struct socketopt *)0);
E 68
I 68
		    m, (struct mbuf *)0);
E 76
I 76
D 158
		error = (*pr->pr_usrreq)(so, PRU_RCVOOB,
D 101
		    m, (struct mbuf *)0, (struct mbuf *)0);
E 101
I 101
		    m, (struct mbuf *)(flags & MSG_PEEK), (struct mbuf *)0);
E 158
I 158
		error = (*pr->pr_usrreq)(so, PRU_RCVOOB, m,
		    (struct mbuf *)(long)(flags & MSG_PEEK), (struct mbuf *)0);
E 158
E 101
E 76
E 68
I 56
		if (error)
D 57
			return;
E 57
I 57
D 67
			return (error);
E 57
E 56
		len = uio->uio_resid;
E 67
I 67
			goto bad;
E 67
		do {
I 67
D 129
			len = uio->uio_resid;
E 67
			if (len > m->m_len)
				len = m->m_len;
D 56
			uiomove(mtod(m, caddr_t), (int)len, UIO_READ, uio);
E 56
I 56
D 125
			error =
D 59
			    uiomove(mtod(m, caddr_t), (int)len, UIO_READ, uio);
E 59
I 59
D 60
			    (void) uiomove(mtod(m, caddr_t), (int)len, UIO_READ, uio);
E 60
I 60
			    uiomove(mtod(m, caddr_t), (int)len, UIO_READ, uio);
E 125
I 125
			error = uiomove(mtod(m, caddr_t), (int)len, uio);
E 129
I 129
			error = uiomove(mtod(m, caddr_t),
			    (int) min(uio->uio_resid, m->m_len), uio);
E 129
E 125
E 60
E 59
E 56
			m = m_free(m);
D 56
		} while (uio->uio_resid && u.u_error == 0 && m);
E 56
I 56
		} while (uio->uio_resid && error == 0 && m);
I 67
bad:
E 67
E 56
		if (m)
D 59
			(void) m_freem(m);
E 59
I 59
			m_freem(m);
E 59
D 56
		return;
E 56
I 56
		return (error);
E 56
	}
I 122
D 124
	if (so->so_state & SS_ISCONFIRMING)
E 124
I 124
D 129
	if (so->so_state & SS_ISCONFIRMING && uio->uio_resid)
E 129
I 129
	if (mp)
		*mp = (struct mbuf *)0;
D 132
	resid = uio->uio_resid;
	if (so->so_state & SS_ISCONFIRMING && resid)
E 132
I 132
	if (so->so_state & SS_ISCONFIRMING && uio->uio_resid)
E 132
E 129
E 124
		(*pr->pr_usrreq)(so, PRU_RCVD, (struct mbuf *)0,
		    (struct mbuf *)0, (struct mbuf *)0);
E 122

E 51
I 6
D 42
COUNT(SORECEIVE);
E 42
E 6
D 3
again:
	while (so->so_rcv.sb_flags & SB_LOCK) {
		so->so_rcv.sb_flags |= SB_WANT;
		sleep((caddr_t)&so->so_rcv.sb_flags, PZERO+1);
	}
E 3
I 3
restart:
I 13
D 14
	nullchk("soreceive restart", so->so_rcv.sb_mb);
	for (m = so->so_rcv.sb_mb; m; m = m->m_next)
		printf("%d ", m->m_len);
	printf("\n");
E 14
E 13
D 128
	sblock(&so->so_rcv);
E 128
I 128
D 144
	if (error = sblock(&so->so_rcv))
E 144
I 144
	if (error = sblock(&so->so_rcv, SBLOCKWAIT(flags)))
E 144
		return (error);
E 128
I 53
D 54
SBCHECK(&so->so_snd, "soreceive restart");
E 54
I 54
D 61
SBCHECK(&so->so_rcv, "soreceive restart");
E 61
E 54
E 53
	s = splnet();
I 61
D 67
SBCHECK(&so->so_rcv, "soreceive restart");
E 67
E 61

D 116
#define	rcverr(errno)	{ error = errno; splx(s); goto release; }
E 116
E 3
D 124
	if (so->so_rcv.sb_cc == 0) {
E 124
I 124
	m = so->so_rcv.sb_mb;
D 129
	if (m == 0) {
		if (so->so_rcv.sb_cc)
E 129
I 129
D 132
	if (m == 0 || (so->so_rcv.sb_cc < resid && 
	    so->so_rcv.sb_cc < so->so_rcv.sb_lowat)) {
E 132
I 132
D 133
	if (m == 0 || (so->so_rcv.sb_cc < uio->uio_resid && 
	    so->so_rcv.sb_cc < so->so_rcv.sb_lowat) ||
	    ((flags & MSG_WAITALL) && so->so_rcv.sb_cc < uio->uio_resid &&
	    so->so_rcv.sb_hiwat >= uio->uio_resid && !sosendallatonce(so))) {
E 133
I 133
	/*
	 * If we have less data than requested, block awaiting more
	 * (subject to any timeout) if:
	 *   1. the current count is less than the low water mark, or
	 *   2. MSG_WAITALL is set, and it is possible to do the entire
D 158
	 *	receive operation at once if we block (resid <= hiwat).
I 144
	 *   3. MSG_DONTWAIT is not set
E 158
I 158
	 *	receive operation at once if we block (resid <= hiwat), or
	 *   3. MSG_DONTWAIT is not set.
E 158
E 144
	 * If MSG_WAITALL is set but resid is larger than the receive buffer,
	 * we have to do the receive in sections, and thus risk returning
	 * a short count if a timeout or signal occurs after we start.
	 */
D 136
	if (m == 0 || so->so_rcv.sb_cc < uio->uio_resid && 
E 136
I 136
D 138
	if (m == 0 || so->so_rcv.sb_cc < uio->uio_resid &&
E 138
I 138
D 143
	while (m == 0 || so->so_rcv.sb_cc < uio->uio_resid &&
E 143
I 143
D 144
	if (m == 0 || so->so_rcv.sb_cc < uio->uio_resid &&
E 144
I 144
	if (m == 0 || ((flags & MSG_DONTWAIT) == 0 &&
	    so->so_rcv.sb_cc < uio->uio_resid) &&
E 144
E 143
E 138
E 136
	    (so->so_rcv.sb_cc < so->so_rcv.sb_lowat ||
D 138
	    ((flags & MSG_WAITALL) && uio->uio_resid <= so->so_rcv.sb_hiwat))) {
E 138
I 138
D 141
	    ((flags & MSG_WAITALL) && uio->uio_resid <= so->so_rcv.sb_hiwat)) &&
D 151
	    m->m_nextpkt == 0) {
E 151
I 151
	    m->m_nextpkt == 0 && (pr->pr_flags & PR_ATOMIC) == 0) {
E 151
E 141
I 141
	    ((flags & MSG_WAITALL) && uio->uio_resid <= so->so_rcv.sb_hiwat)))
		if (m && (m->m_nextpkt || (m->m_flags & M_EOR) ||
		          m->m_type == MT_OOBDATA || m->m_type == MT_CONTROL))
			break;
E 141
E 138
E 133
E 132
#ifdef DIAGNOSTIC
		if (m == 0 && so->so_rcv.sb_cc)
E 129
			panic("receive 1");
I 129
#endif
E 129
E 124
I 16
		if (so->so_error) {
I 138
			if (m)
D 143
				break;
E 143
I 143
				goto dontblock;
E 143
E 138
			error = so->so_error;
D 138
			so->so_error = 0;
E 138
I 138
			if ((flags & MSG_PEEK) == 0)
				so->so_error = 0;
E 138
D 116
			splx(s);
E 116
			goto release;
		}
E 16
D 2
		if ((so->so_proto->pr_usrreq)(so, PR_ISDISCONN, 0, 0) == 0)
E 2
I 2
D 3
		if ((so->so_proto->pr_usrreq)(so, PRU_ISDISCONN, 0, 0) == 0)
E 2
			return;
		so->so_rcv.sb_flags |= SB_WAIT;
E 3
I 3
D 11
		if ((so->so_state & SS_ISCONNECTED) == 0 &&
		    (so->so_proto->pr_flags & PR_CONNREQUIRED))
			rcverr(ENOTCONN);
E 11
D 116
		if (so->so_state & SS_CANTRCVMORE) {
			splx(s);
E 116
I 116
D 138
		if (so->so_state & SS_CANTRCVMORE)
E 116
			goto release;
E 138
I 138
		if (so->so_state & SS_CANTRCVMORE) {
			if (m)
D 143
				break;
E 143
I 143
				goto dontblock;
E 143
			else
				goto release;
		}
D 141
		for (; m; m = m->m_next)
			if (m->m_type == MT_OOBDATA  || (m->m_flags & M_EOR)) {
				m = so->so_rcv.sb_mb;
				goto dontblock;
			}
E 141
E 138
D 116
		}
E 116
I 11
D 126
		if ((so->so_state & SS_ISCONNECTED) == 0 &&
E 126
I 126
		if ((so->so_state & (SS_ISCONNECTED|SS_ISCONNECTING)) == 0 &&
E 126
D 116
		    (so->so_proto->pr_flags & PR_CONNREQUIRED))
			rcverr(ENOTCONN);
E 116
I 116
		    (so->so_proto->pr_flags & PR_CONNREQUIRED)) {
			error = ENOTCONN;
			goto release;
		}
E 116
I 103
D 129
		if (uio->uio_resid == 0)
E 129
I 129
D 132
		if (resid == 0)
E 132
I 132
		if (uio->uio_resid == 0)
E 132
E 129
			goto release;
E 103
E 11
D 23
		if (so->so_options & SO_NBIO)
E 23
I 23
D 34
		if (so->so_options & SO_NONBLOCKING)
E 34
I 34
D 116
		if (so->so_state & SS_NBIO)
E 34
E 23
D 5
			rcverr(EWOULDBLOCK);
E 5
I 5
D 16
			rcverr (EWOULDBLOCK);
E 16
I 16
			rcverr(EWOULDBLOCK);
E 116
I 116
D 144
		if (so->so_state & SS_NBIO) {
E 144
I 144
		if ((so->so_state & SS_NBIO) || (flags & MSG_DONTWAIT)) {
E 144
			error = EWOULDBLOCK;
			goto release;
		}
E 116
E 16
E 5
		sbunlock(&so->so_rcv);
E 3
D 8
		sleep((caddr_t)&so->so_rcv.sb_cc, PZERO+1);
E 8
I 8
D 128
		sbwait(&so->so_rcv);
E 128
I 128
D 129
		if (error = sbwait(&so->so_rcv))
			goto release;
E 129
I 129
D 132
/*
		if (sbwait_func)
			error = (*sbwait_func)(&so->so_rcv, sbwait_arg);
		else
*/
			error = sbwait(&so->so_rcv);
E 132
I 132
		error = sbwait(&so->so_rcv);
E 132
E 129
E 128
I 10
		splx(s);
I 129
		if (error)
			return (error);
E 129
E 10
E 8
D 3
		goto again;
E 3
I 3
		goto restart;
E 3
	}
I 138
D 141
dontblock:
E 141
E 138
I 49
D 140
	u.u_ru.ru_msgrcv++;
E 140
I 140
D 147
	p->p_stats->p_ru.ru_msgrcv++;
E 147
I 147
	if (uio->uio_procp)
		uio->uio_procp->p_stats->p_ru.ru_msgrcv++;
E 147
E 140
I 129
D 133
#ifdef DIAGNOSTIC
E 129
E 49
I 13
D 14
	printf("soreceive about to\n");
	psndrcv(&so->so_snd, &so->so_rcv);
E 14
E 13
D 3
	so->so_rcv.sb_flags |= SB_LOCK;
E 3
D 2
	m = up->uc_rcv.sb_mb;
E 2
I 2
D 124
	m = so->so_rcv.sb_mb;
I 103
	if (m == 0)
		panic("receive 1");
E 124
D 122
	nextrecord = m->m_act;
E 122
I 122
if (m->m_type == 0)
panic("receive 3a");
I 129
#endif
E 133
E 129
	nextrecord = m->m_nextpkt;
I 141
	record_eor = m->m_flags & M_EOR;
E 141
E 122
E 103
E 2
D 88
	if (m == 0)
		panic("receive");
E 88
I 53
D 67
SBCHECK(&so->so_snd, "soreceive havecc");
E 67
E 53
I 3
D 5
	
E 5
D 6
	/*
	 * Pull address off receive chain, if protocol
	 * put one there.
	 */
E 6
D 13
	if ((so->so_proto->pr_flags & PR_ADDR)) {
D 12
		so->so_rcv.sb_mb = m->m_next;
E 12
D 6
		if (iap) {
E 6
I 6
		if (asa) {
E 6
			so->so_rcv.sb_cc -= m->m_len;
D 6
			len = MIN(m->m_len, sizeof (struct in_addr));
			bcopy(mtod(m, caddr_t), (caddr_t)iap, len);
E 6
I 6
			len = MIN(m->m_len, sizeof (struct sockaddr));
			bcopy(mtod(m, caddr_t), (caddr_t)asa, len);
E 6
		} else
E 13
I 13
D 76
	if (so->so_proto->pr_flags & PR_ADDR) {
D 14
		printf("m_len %d\n", m->m_len);
E 14
D 50
		if (m->m_len != sizeof (struct sockaddr))
			panic("soreceive addr");
		if (asa)
			bcopy(mtod(m, caddr_t), (caddr_t)asa, sizeof (*asa));
E 50
D 14
		else
E 13
D 4
			*iap = zeroin_addr;
E 4
I 4
D 6
			bzero((caddr_t)iap, sizeof (*iap));
E 6
I 6
			bzero((caddr_t)asa, sizeof (*asa));
E 14
I 13
D 51
		so->so_rcv.sb_cc -= m->m_len;
		so->so_rcv.sb_mbcnt -= MSIZE;
E 51
I 51
		if ((flags & SOF_PREVIEW) == 0) {
E 76
I 76
	if (pr->pr_flags & PR_ADDR) {
I 129
#ifdef DIAGNOSTIC
E 129
D 88
		if ((flags & MSG_PEEK) == 0) {
E 76
			so->so_rcv.sb_cc -= m->m_len;
			so->so_rcv.sb_mbcnt -= MSIZE;
		}
E 51
E 13
E 6
E 4
D 12
		m = so->so_rcv.sb_mb;
E 12
I 12
D 50
		m = m_free(m);
E 50
I 50
		if (aname) {
D 51
			*aname = m;
E 51
I 51
D 67
			if (flags & SOF_PREVIEW)
E 67
I 67
D 76
			if (flags & SOF_PREVIEW) {
E 76
I 76
			if (flags & MSG_PEEK) {
E 88
I 88
D 103
		if (m == 0 || m->m_type != MT_SONAME)
E 103
I 103
		if (m->m_type != MT_SONAME)
E 103
			panic("receive 1a");
I 129
#endif
I 151
		orig_resid = 0;
E 151
E 129
		if (flags & MSG_PEEK) {
D 129
			if (aname)
E 88
E 76
E 67
				*aname = m_copy(m, 0, m->m_len);
E 129
I 129
			if (paddr)
				*paddr = m_copy(m, 0, m->m_len);
E 129
D 67
			else
E 67
I 67
D 88
				if (*aname == NULL)
					panic("receive 2");
			} else
E 67
				*aname = m;
E 51
			m = m->m_next;
			(*aname)->m_next = 0;
		} else
D 51
			m = m_free(m);
E 51
I 51
D 76
			if (flags & SOF_PREVIEW)
E 76
I 76
			if (flags & MSG_PEEK)
E 76
				m = m->m_next;
E 88
D 103
			else
D 88
				m = m_free(m);
E 51
E 50
E 12
		if (m == 0)
E 88
I 88
				m = m->m_act;
E 103
I 103
			m = m->m_next;
E 103
		} else {
I 103
			sbfree(&so->so_rcv, m);
E 103
D 129
			if (aname) {
				*aname = m;
E 129
I 129
			if (paddr) {
				*paddr = m;
E 129
D 103
				sbfree(&so->so_rcv, m);
if(m->m_next) panic("receive 1b");
				so->so_rcv.sb_mb = m = m->m_act;
			} else
				m = sbdroprecord(&so->so_rcv);
E 103
I 103
D 122
				m = m->m_next;
				(*aname)->m_next = 0;
I 109
				so->so_rcv.sb_mb = m;
E 122
I 122
				so->so_rcv.sb_mb = m->m_next;
				m->m_next = 0;
				m = so->so_rcv.sb_mb;
E 122
E 109
			} else {
D 108
				MFREE(m, n);
E 108
D 109
				nextrecord = m->m_act;
I 108
				MFREE(m, n);
E 108
				m = n;
E 109
I 109
				MFREE(m, so->so_rcv.sb_mb);
				m = so->so_rcv.sb_mb;
E 109
			}
I 109
D 122
			if (m)
				m->m_act = nextrecord;
E 122
E 109
E 103
		}
	}
D 129
	if (m && m->m_type == MT_RIGHTS) {
		if ((pr->pr_flags & PR_RIGHTS) == 0)
E 88
I 76
D 109
			panic("receive 2a");
E 109
I 109
			panic("receive 2");
E 129
I 129
	while (m && m->m_type == MT_CONTROL && error == 0) {
E 129
E 109
D 88
		if (rightsp) {
			if (m->m_len)
E 88
I 88
		if (flags & MSG_PEEK) {
D 129
			if (rightsp)
E 88
				*rightsp = m_copy(m, 0, m->m_len);
D 88
			else {
				*rightsp = m_get(M_DONTWAIT, MT_SONAME);
				if (*rightsp)
					(*rightsp)->m_len = 0;
			}
I 81
#ifdef notdef
E 81
			if (*rightsp == NULL)
				panic("receive 2b");
I 81
#endif
E 88
I 88
D 103
			else
				m = m->m_act;
E 103
I 103
			m = m->m_next;
E 103
		} else {
I 103
			sbfree(&so->so_rcv, m);
E 103
			if (rightsp) {
				*rightsp = m;
D 103
				sbfree(&so->so_rcv, m);
if(m->m_next) panic("receive 2b");
				so->so_rcv.sb_mb = m = m->m_act;
			} else
				m = sbdroprecord(&so->so_rcv);
E 103
I 103
D 109
				n = m->m_next;
E 109
I 109
				so->so_rcv.sb_mb = m->m_next;
E 109
				m->m_next = 0;
D 109
				m = n;
E 109
I 109
				m = so->so_rcv.sb_mb;
E 109
			} else {
D 109
				MFREE(m, n);
				m = n;
E 109
I 109
				MFREE(m, so->so_rcv.sb_mb);
				m = so->so_rcv.sb_mb;
E 109
			}
I 109
D 122
			if (m)
				m->m_act = nextrecord;
E 122
E 109
E 103
E 88
E 81
		}
D 88
		if (flags & MSG_PEEK)
			m = m->m_next;
		else {
			so->so_rcv.sb_cc -= m->m_len;
			so->so_rcv.sb_mbcnt -= MSIZE;
			m = m_free(m);
		}
		if (m == 0)
E 76
D 67
			panic("receive 2");
E 67
I 67
			panic("receive 3");
E 67
I 53
D 76
		if ((flags & SOF_PREVIEW) == 0)
E 76
I 76
		if ((flags & MSG_PEEK) == 0)
E 76
			so->so_rcv.sb_mb = m;
E 88
D 67
SBCHECK(&so->so_snd, "soreceive afteraddr");
E 67
E 53
I 12
D 51
		so->so_rcv.sb_mb = m;
E 51
E 12
	}
I 122
	if (m && m->m_type == MT_CONTROL) {
		if (flags & MSG_PEEK) {
E 129
			if (controlp)
				*controlp = m_copy(m, 0, m->m_len);
			m = m->m_next;
		} else {
			sbfree(&so->so_rcv, m);
			if (controlp) {
I 129
D 131
				if (mtod(m, struct cmsghdr *)->cmsg_type ==
				    SCM_RIGHTS &&
				    pr->pr_domain->dom_externalize)
E 131
I 131
				if (pr->pr_domain->dom_externalize &&
				    mtod(m, struct cmsghdr *)->cmsg_type ==
				    SCM_RIGHTS)
E 131
				   error = (*pr->pr_domain->dom_externalize)(m);
E 129
				*controlp = m;
				so->so_rcv.sb_mb = m->m_next;
				m->m_next = 0;
				m = so->so_rcv.sb_mb;
			} else {
				MFREE(m, so->so_rcv.sb_mb);
				m = so->so_rcv.sb_mb;
			}
		}
I 129
D 151
		if (controlp)
E 151
I 151
		if (controlp) {
			orig_resid = 0;
E 151
			controlp = &(*controlp)->m_next;
I 151
		}
E 151
E 129
	}
D 129
	if (m)
E 129
I 129
	if (m) {
E 129
D 133
		m->m_nextpkt = nextrecord;
E 133
I 133
		if ((flags & MSG_PEEK) == 0)
			m->m_nextpkt = nextrecord;
E 133
I 129
		type = m->m_type;
I 137
		if (type == MT_OOBDATA)
			flags |= MSG_OOB;
E 137
	}
E 129
E 122
I 25
D 47
	so->so_state &= ~SS_RCVATMARK;
	if (so->so_oobmark && cnt > so->so_oobmark)
		cnt = so->so_oobmark;
E 47
E 25
D 6

	/*
	 * Next pull data off the chain.
	 * Stop at eor or when run out of space in user buffer.
	 */
E 6
E 3
D 88
	eor = 0;
E 88
I 88
D 96
	if (m == 0)
E 96
I 96
D 97
	if (m == 0 || m->m_type != MT_DATA)
E 97
I 97
D 103
	if (m == 0 || (m->m_type != MT_DATA && m->m_type != MT_HEADER))
E 97
E 96
		panic("receive 3");
E 103
E 88
I 51
	moff = 0;
D 115
	tomark = so->so_oobmark;
E 115
I 115
	offset = 0;
I 127
D 129
	m_with_eor = 0;
E 127
E 115
E 51
I 13
D 14
	printf("soreceive before receive loop\n");
	psndrcv(&so->so_snd, &so->so_rcv);
E 14
E 13
D 88
	do {
D 25
		len = MIN(m->m_len, u.u_count);
E 25
I 25
D 47
		len = MIN(m->m_len, cnt);
E 47
I 47
D 48
		if (uio->uio_iovcnt == 0)
E 48
I 48
		if (uio->uio_resid <= 0)
E 48
			break;
E 88
I 88
	while (m && uio->uio_resid > 0 && error == 0) {
E 129
I 129
D 132
	while (m && m->m_type == type && resid > 0 && error == 0) {
E 132
I 132
D 137
	while (m && m->m_type == type && uio->uio_resid > 0 && error == 0) {
E 132
E 129
I 103
D 122
		if (m->m_type != MT_DATA && m->m_type != MT_HEADER)
E 122
I 122
		if (m->m_type == MT_OOBDATA)
			flags |= MSG_OOB;
E 137
I 137
	while (m && uio->uio_resid > 0 && error == 0) {
		if (m->m_type == MT_OOBDATA) {
			if (type != MT_OOBDATA)
				break;
		} else if (type == MT_OOBDATA)
			break;
E 137
I 129
#ifdef DIAGNOSTIC
E 129
		else if (m->m_type != MT_DATA && m->m_type != MT_HEADER)
E 122
			panic("receive 3");
I 122
D 129
		if (m->m_flags & M_EOR)
D 127
			flags |= MSG_EOR;
E 127
I 127
			m_with_eor = m;
E 127
E 122
E 103
E 88
D 48
		iov = uio->uio_iov;
		len = iov->iov_len;
E 48
I 48
		len = uio->uio_resid;
E 129
I 129
#endif
D 136
		type = m->m_type;
E 136
E 129
E 48
		so->so_state &= ~SS_RCVATMARK;
I 129
D 132
		len = resid;
E 132
I 132
		len = uio->uio_resid;
E 132
E 129
D 51
		if (so->so_oobmark && len > so->so_oobmark)
			len = so->so_oobmark;
		if (len > m->m_len)
			len = m->m_len;
E 51
I 51
D 115
		if (tomark && len > tomark)
			len = tomark;
E 115
I 115
		if (so->so_oobmark && len > so->so_oobmark - offset)
			len = so->so_oobmark - offset;
E 115
D 53
		if (len > m->m_len - moff)
E 53
I 53
D 96
		if (moff+len > m->m_len - moff)
E 96
I 96
		if (len > m->m_len - moff)
E 96
E 53
			len = m->m_len - moff;
I 103
D 104
		so->so_rcv.sb_mb = m;
		m->m_act = nextrecord;
E 104
I 104
D 109
		if ((flags & MSG_PEEK) == 0) {
			so->so_rcv.sb_mb = m;
			m->m_act = nextrecord;
		}
E 109
E 104
E 103
E 51
E 47
E 25
D 32
		if (len == m->m_len) {
			eor = (int)m->m_act;
D 2
			up->uc_rcv.sb_mb = m->m_next;
			up->uc_rcv.sb_cc -= len;
			if (up->uc_rcv.sb_cc < 0)
E 2
I 2
D 3
			so->so_rcv.sb_mb = m->m_next;
			so->so_rcv.sb_cc -= len;
			if (so->so_rcv.sb_cc < 0)
E 2
				panic("receive 2");
E 3
I 3
			sbfree(&so->so_rcv, m);
I 22
			so->so_rcv.sb_mb = m->m_next;
E 22
E 3
		}
E 32
D 129
		splx(s);
I 13
D 14
		nullblk("soreceive", m, len);
		if (len)
		printf("%o\n", *mtod(m, caddr_t));
E 14
E 13
D 47
		iomove(mtod(m, caddr_t), len, B_READ);
I 25
		cnt -= len;
E 47
I 47
D 48
		uiomove(mtod(m, caddr_t), len, UIO_WRITETO, uio);
E 48
I 48
D 51
		uiomove(mtod(m, caddr_t), (int)len, UIO_READ, uio);
E 51
I 51
D 56
		uiomove(mtod(m, caddr_t) + moff, (int)len, UIO_READ, uio);
E 56
I 56
D 125
		error =
D 59
		    uiomove(mtod(m, caddr_t) + moff, (int)len, UIO_READ, uio);
E 59
I 59
D 60
		    (void) uiomove(mtod(m, caddr_t) + moff, (int)len, UIO_READ, uio);
E 60
I 60
		    uiomove(mtod(m, caddr_t) + moff, (int)len, UIO_READ, uio);
E 125
I 125
		error = uiomove(mtod(m, caddr_t) + moff, (int)len, uio);
E 125
E 60
E 59
E 56
E 51
E 48
E 47
E 25
		s = splnet();
E 129
I 129
		/*
		 * If mp is set, just pass back the mbufs.
		 * Otherwise copy them out via the uio, then free.
		 * Sockbuf must be consistent here (points to current mbuf,
		 * it points to next record) when we drop priority;
		 * we must note any additions to the sockbuf when we
		 * block interrupts again.
		 */
		if (mp == 0) {
			splx(s);
			error = uiomove(mtod(m, caddr_t) + moff, (int)len, uio);
D 132
			resid = uio->uio_resid;
E 132
			s = splnet();
D 132
		}
E 132
I 132
		} else
			uio->uio_resid -= len;
E 132
E 129
D 96
		if (len == m->m_len) {
E 96
I 96
		if (len == m->m_len - moff) {
I 129
D 141
			if (m->m_flags & M_EOR)
				flags |= MSG_EOR;
E 141
E 129
E 96
I 32
D 88
			eor = (int)m->m_act;
D 51
			sbfree(&so->so_rcv, m);
			so->so_rcv.sb_mb = m->m_next;
E 32
			MFREE(m, n);
I 10
D 22
			so->so_rcv.sb_mb = n;
E 22
E 10
		} else {
			m->m_off += len;
			m->m_len -= len;
D 2
			up->uc_rcv.sb_cc -= len;
			if (up->uc_rcv.sb_cc < 0)
E 2
I 2
			so->so_rcv.sb_cc -= len;
E 51
I 51
D 76
			if (flags & SOF_PREVIEW)
E 76
I 76
			if (flags & MSG_PEEK)
E 76
				m = m->m_next;
			else {
E 88
I 88
D 103
			if ((flags & MSG_PEEK) == 0) {
				nextrecord = m->m_act;
E 103
I 103
			if (flags & MSG_PEEK) {
				m = m->m_next;
				moff = 0;
			} else {
E 103
E 88
D 109
				sbfree(&so->so_rcv, m);
E 109
I 103
D 122
				nextrecord = m->m_act;
E 122
I 122
				nextrecord = m->m_nextpkt;
E 122
E 103
D 109
				MFREE(m, n);
D 88
				m = n;
E 88
I 88
D 103
				if (m = n)
					m->m_act = nextrecord;
E 88
I 53
				so->so_rcv.sb_mb = m;
E 53
D 88
			}
E 88
I 88
			} else
				m = m->m_next;
E 88
			moff = 0;
E 103
I 103
				so->so_rcv.sb_mb = m = n;
E 109
I 109
				sbfree(&so->so_rcv, m);
D 129
				MFREE(m, so->so_rcv.sb_mb);
				m = so->so_rcv.sb_mb;
E 129
I 129
				if (mp) {
					*mp = m;
					mp = &m->m_next;
D 132
					m = m->m_next;
E 132
I 132
					so->so_rcv.sb_mb = m = m->m_next;
					*mp = (struct mbuf *)0;
E 132
				} else {
					MFREE(m, so->so_rcv.sb_mb);
					m = so->so_rcv.sb_mb;
				}
E 129
				if (m)
D 122
					m->m_act = nextrecord;
E 122
I 122
					m->m_nextpkt = nextrecord;
E 122
E 109
			}
E 103
		} else {
D 76
			if (flags & SOF_PREVIEW)
E 76
I 76
			if (flags & MSG_PEEK)
E 76
				moff += len;
			else {
I 132
				if (mp)
					*mp = m_copym(m, 0, len, M_WAIT);
E 132
D 122
				m->m_off += len;
E 122
I 122
				m->m_data += len;
E 122
				m->m_len -= len;
				so->so_rcv.sb_cc -= len;
			}
E 51
D 3
			if (so->so_rcv.sb_cc < 0)
E 2
				panic("receive 3");
E 3
		}
D 2
	} while ((m = up->uc_rcv.sb_mb) && u.u_count && !eor);
E 2
I 2
D 25
	} while ((m = so->so_rcv.sb_mb) && u.u_count && !eor);
E 25
I 25
D 47
	} while ((m = so->so_rcv.sb_mb) && cnt && !eor);
E 47
I 47
D 51
		if (so->so_oobmark) {
E 51
I 51
D 76
		if ((flags & SOF_PREVIEW) == 0 && so->so_oobmark) {
E 76
I 76
D 115
		if ((flags & MSG_PEEK) == 0 && so->so_oobmark) {
E 76
E 51
			so->so_oobmark -= len;
			if (so->so_oobmark == 0) {
				so->so_state |= SS_RCVATMARK;
				break;
			}
		}
D 51
	} while ((m = so->so_rcv.sb_mb) && !eor);
E 51
I 51
		if (tomark) {
			tomark -= len;
			if (tomark == 0)
				break;
E 115
I 115
		if (so->so_oobmark) {
			if ((flags & MSG_PEEK) == 0) {
				so->so_oobmark -= len;
				if (so->so_oobmark == 0) {
					so->so_state |= SS_RCVATMARK;
					break;
				}
D 152
			} else
E 152
I 152
			} else {
E 152
				offset += len;
I 152
				if (offset == so->so_oobmark)
					break;
			}
E 152
E 115
		}
I 127
D 129
		if (m_with_eor)
E 129
I 129
D 141
		if (flags & MSG_EOR)
E 141
I 141
		if (m == 0 && record_eor) {
			flags |= record_eor;
E 141
E 129
			break;
I 141
		}
E 141
I 129
		/*
		 * If the MSG_WAITALL flag is set (for non-atomic socket),
D 132
		 * we must not quit until "resid == 0" or an error
E 132
I 132
		 * we must not quit until "uio->uio_resid == 0" or an error
E 132
		 * termination.  If a signal/timeout occurs, return
D 132
		 * prematurely but without error.
E 132
I 132
		 * with a short count but without error.
E 132
		 * Keep sockbuf locked against other readers.
		 */
D 132
		while (flags & MSG_WAITALL && m == 0 && resid > 0 &&
E 132
I 132
		while (flags & MSG_WAITALL && m == 0 && uio->uio_resid > 0 &&
E 132
D 141
D 151
		    !sosendallatonce(so)) {
E 151
I 151
		    !sosendallatonce(so) && !nextrecord) {
E 151
E 141
I 141
		   !(flags & MSG_OOB) && !sosendallatonce(so)) {
E 141
I 138
			if (so->so_error || so->so_state & SS_CANTRCVMORE)
				break;
E 138
			error = sbwait(&so->so_rcv);
			if (error) {
				sbunlock(&so->so_rcv);
				splx(s);
D 132
				if (mp)
					*mp = (struct mbuf *)0;
E 132
				return (0);
			}
D 141
			if (m = so->so_rcv.sb_mb)
E 141
I 141
			if (m = so->so_rcv.sb_mb) {
E 141
				nextrecord = m->m_nextpkt;
I 141
				record_eor |= m->m_flags & M_EOR;
			}
E 141
D 138
			if (so->so_error || so->so_state & SS_CANTRCVMORE)
				break;
			continue;
E 138
		}
E 129
E 127
I 53
D 67
SBCHECK(&so->so_snd, "soreceive rcvloop");
E 67
E 53
D 56
	} while (m && !eor);
E 56
I 56
D 88
	} while (m && error == 0 && !eor);
E 56
D 76
	if (flags & SOF_PREVIEW)
E 76
I 76
	if (flags & MSG_PEEK)
E 76
		goto release;
D 53
	so->so_rcv.sb_mb = m;
E 53
E 51
E 47
E 25
I 13
D 14
	printf("after receive loop\n");
	psndrcv(&so->so_snd, &so->so_rcv);
E 14
E 13
I 3
D 6

	/*
	 * If atomic protocol discard rest of record.
	 */
E 6
E 3
E 2
	if ((so->so_proto->pr_flags & PR_ATOMIC) && eor == 0)
		do {
D 3
			m = so->so_rcv.sb_mb;
E 3
			if (m == 0)
D 3
				panic("receive 4");
D 2
			up->uc_rcv.sb_cc -= m->m_len;
			if (up->uc_rcv.sb_cc < 0)
E 2
I 2
			so->so_rcv.sb_cc -= m->m_len;
			if (so->so_rcv.sb_cc < 0)
E 2
				panic("receive 5");
E 3
I 3
D 67
				panic("receive 3");
E 67
I 67
				panic("receive 4");
E 67
			sbfree(&so->so_rcv, m);
E 3
			eor = (int)m->m_act;
			so->so_rcv.sb_mb = m->m_next;
			MFREE(m, n);
I 3
			m = n;
I 53
D 67
SBCHECK(&so->so_snd, "soreceive atomicloop");
E 67
E 53
E 3
		} while (eor == 0);
I 13
D 14
	printf("soreceive after drop remnants\n");
	psndrcv(&so->so_snd, &so->so_rcv);
E 14
E 13
D 3
	if (iap)
D 2
		if ((so->so_proto->pr_flags & PR_PROVIDEADDR)) {
			m = up->uc_rcv.sb_mb;
E 2
I 2
		if ((so->so_proto->pr_flags & PR_ADDR)) {
			m = so->so_rcv.sb_mb;
E 2
			if (m == 0)
				panic("receive 6");
D 2
			up->uc_rcv.sb_mb = m->m_next;
			up->uc_rcv.sb_cc -= m->m_len;
E 2
I 2
			so->so_rcv.sb_mb = m->m_next;
			so->so_rcv.sb_cc -= m->m_len;
E 2
			len = MIN(m->m_len, sizeof (struct in_addr));
			bcopy(mtod(m, caddr_t), (caddr_t)iap, len);
		} else
			*iap = zeroin_addr;
D 2
	(*so->so_proto->pr_usrreq)(up, PRU_RCVD, m, 0);
E 2
I 2
	(*so->so_proto->pr_usrreq)(so, PRU_RCVD, m, 0);
E 3
I 3
D 6

	/*
	 * If protocol cares, inform it that
	 * there is more space in the receive buffer.
	 */
E 6
	if ((so->so_proto->pr_flags & PR_WANTRCVD) && so->so_pcb)
D 50
		(*so->so_proto->pr_usrreq)(so, PRU_RCVD, 0, 0);
E 50
I 50
		(*so->so_proto->pr_usrreq)(so, PRU_RCVD,
D 68
		    (struct mbuf *)0, (struct mbuf *)0, (struct socketopt *)0);
E 68
I 68
D 76
		    (struct mbuf *)0, (struct mbuf *)0);
E 76
I 76
		    (struct mbuf *)0, (struct mbuf *)0, (struct mbuf *)0);
E 88
I 88
	}
I 151

	if (m && pr->pr_flags & PR_ATOMIC) {
		flags |= MSG_TRUNC;
		if ((flags & MSG_PEEK) == 0)
			(void) sbdroprecord(&so->so_rcv);
	}
E 151
I 122
D 127
	if (m && (flags & MSG_EOR)) {
		flags &= ~MSG_EOR;
		if ((flags & MSG_PEEK) == 0)
			m->m_flags |= M_EOR;
E 127
I 127
D 129
	if (m_with_eor) {
		if (m != m_with_eor)
			flags |= MSG_EOR;
		/* else data not consumed from mbuf */
E 127
	}
E 129
I 129
D 132
	if (mp)
		*mp = (struct mbuf *)0;
E 132
E 129
E 122
	if ((flags & MSG_PEEK) == 0) {
D 103
		if (m == 0)
E 103
I 103
D 108
		if (so->so_rcv.sb_mb == 0)
E 108
I 108
		if (m == 0)
E 108
E 103
			so->so_rcv.sb_mb = nextrecord;
D 108
		else if (pr->pr_flags & PR_ATOMIC)
			(void) sbdroprecord(&so->so_rcv);
E 108
I 108
D 109
		else {
			m->m_act = nextrecord;
			if (pr->pr_flags & PR_ATOMIC)
				(void) sbdroprecord(&so->so_rcv);
		}
E 109
I 109
D 122
		else if (pr->pr_flags & PR_ATOMIC)
E 122
I 122
D 151
		else if (pr->pr_flags & PR_ATOMIC) {
			flags |= MSG_TRUNC;
E 122
			(void) sbdroprecord(&so->so_rcv);
I 122
		}
E 151
E 122
E 109
E 108
		if (pr->pr_flags & PR_WANTRCVD && so->so_pcb)
			(*pr->pr_usrreq)(so, PRU_RCVD, (struct mbuf *)0,
D 124
			    (struct mbuf *)0, (struct mbuf *)0);
E 124
I 124
D 158
			    (struct mbuf *)flags, (struct mbuf *)0,
E 158
I 158
			    (struct mbuf *)(long)flags, (struct mbuf *)0,
E 158
			    (struct mbuf *)0);
E 124
I 103
D 129
		if (error == 0 && rightsp && *rightsp &&
		    pr->pr_domain->dom_externalize)
			error = (*pr->pr_domain->dom_externalize)(*rightsp);
E 129
E 103
	}
I 151
	if (orig_resid == uio->uio_resid && orig_resid &&
	    (flags & MSG_EOR) == 0 && (so->so_state & SS_CANTRCVMORE) == 0) {
		sbunlock(&so->so_rcv);
		splx(s);
		goto restart;
	}
		
E 151
I 122
	if (flagsp)
		*flagsp |= flags;
E 122
E 88
E 76
E 68
E 50
I 25
D 47
	if (so->so_oobmark) {
		so->so_oobmark -= u.u_base - base;
		if (so->so_oobmark == 0)
			so->so_state |= SS_RCVATMARK;
	}
E 47
E 25
I 13
D 14
	nullchk("receive after PRU_RCVD", so->so_rcv.sb_mb);
E 14
E 13
D 6

E 6
release:
D 5
	sounlock(&so->so_rcv);
E 5
I 5
	sbunlock(&so->so_rcv);
I 76
D 88
	if (error == 0 && rightsp &&
	    *rightsp && so->so_proto->pr_family == AF_UNIX)
		error = unp_externalize(*rightsp);
E 88
I 88
D 103
	if (error == 0 && rightsp && *rightsp && pr->pr_domain->dom_externalize)
		error = (*pr->pr_domain->dom_externalize)(*rightsp);
E 103
E 88
E 76
E 5
	splx(s);
I 5
	return (error);
E 5
E 3
E 2
}

I 158
int
E 158
I 68
soshutdown(so, how)
D 76
	struct socket *so;
	int how;
E 76
I 76
	register struct socket *so;
	register int how;
E 76
{
I 76
	register struct protosw *pr = so->so_proto;
E 76

	how++;
D 76
	if (how & FREAD) {
		int s = splimp();
		socantrcvmore(so);
		sbflush(&so->so_rcv);
		splx(s);
	}
E 76
I 76
	if (how & FREAD)
		sorflush(so);
E 76
	if (how & FWRITE)
D 76
		return ((*so->so_proto->pr_usrreq)(so, PRU_SHUTDOWN,
		    (struct mbuf *)0, (struct mbuf *)0));
E 76
I 76
		return ((*pr->pr_usrreq)(so, PRU_SHUTDOWN,
		    (struct mbuf *)0, (struct mbuf *)0, (struct mbuf *)0));
E 76
	return (0);
}

I 158
void
E 158
I 76
sorflush(so)
	register struct socket *so;
{
	register struct sockbuf *sb = &so->so_rcv;
	register struct protosw *pr = so->so_proto;
	register int s;
	struct sockbuf asb;

D 128
	sblock(sb);
E 128
I 128
	sb->sb_flags |= SB_NOINTR;
D 144
	(void) sblock(sb);
E 144
I 144
	(void) sblock(sb, M_WAITOK);
E 144
E 128
	s = splimp();
	socantrcvmore(so);
	sbunlock(sb);
	asb = *sb;
	bzero((caddr_t)sb, sizeof (*sb));
	splx(s);
D 88
	if (pr->pr_family == AF_UNIX && (pr->pr_flags & PR_RIGHTS))
		unp_scan(asb.sb_mb, unp_discard);
E 88
I 88
	if (pr->pr_flags & PR_RIGHTS && pr->pr_domain->dom_dispose)
		(*pr->pr_domain->dom_dispose)(asb.sb_mb);
E 88
	sbrelease(&asb);
}

I 158
int
E 158
E 76
D 94
sosetopt(so, level, optname, m)
E 94
I 94
sosetopt(so, level, optname, m0)
E 94
D 76
	struct socket *so;
E 76
I 76
	register struct socket *so;
E 76
	int level, optname;
D 76
	struct mbuf *m;
E 76
I 76
D 94
	register struct mbuf *m;
E 94
I 94
	struct mbuf *m0;
E 94
E 76
{
I 90
	int error = 0;
I 128
D 129
	u_long val;
E 129
E 128
I 94
	register struct mbuf *m = m0;
I 128
D 129
	register struct sockbuf *sb;
E 129
E 128
E 94
E 90
D 69
	int optval;
E 69

D 90
	if (level != SOL_SOCKET)
		return (EINVAL);	/* XXX */
E 90
I 90
	if (level != SOL_SOCKET) {
D 92
		error = EINVAL;
		goto bad;
	}
E 90
D 69
	if (m->m_len != sizeof (int))
		return (EINVAL);
	optval = *mtod(m, int *);
E 69
	switch (optname) {
E 92
I 92
		if (so->so_proto && so->so_proto->pr_ctloutput)
			return ((*so->so_proto->pr_ctloutput)
D 94
				  (PRCO_SETOPT, so, level, optname, m));
E 94
I 94
				  (PRCO_SETOPT, so, level, optname, &m0));
E 94
		error = ENOPROTOOPT;
	} else {
		switch (optname) {
E 92

I 90
D 92
	case SO_LINGER:
		if (m == NULL || m->m_len != sizeof (struct linger)) {
			error = EINVAL;
			goto bad;
		}
		so->so_linger = mtod(m, struct linger *)->l_linger;
		/* fall thru... */
E 92
I 92
		case SO_LINGER:
			if (m == NULL || m->m_len != sizeof (struct linger)) {
				error = EINVAL;
				goto bad;
			}
			so->so_linger = mtod(m, struct linger *)->l_linger;
			/* fall thru... */
E 92

E 90
D 92
	case SO_DEBUG:
D 72
		so->so_options |= SO_DEBUG;
		break;

E 72
I 69
	case SO_KEEPALIVE:
D 72
		so->so_options |= SO_KEEPALIVE;
E 72
I 72
	case SO_DONTROUTE:
	case SO_USELOOPBACK:
I 90
	case SO_BROADCAST:
E 90
	case SO_REUSEADDR:
D 90
		so->so_options |= optname;
E 90
I 90
		if (m == NULL || m->m_len < sizeof (int)) {
			error = EINVAL;
			goto bad;
		}
		if (*mtod(m, int *))
			so->so_options |= optname;
		else
			so->so_options &= ~optname;
E 90
E 72
		break;
E 92
I 92
		case SO_DEBUG:
		case SO_KEEPALIVE:
		case SO_DONTROUTE:
		case SO_USELOOPBACK:
		case SO_BROADCAST:
		case SO_REUSEADDR:
I 149
		case SO_REUSEPORT:
E 149
I 110
		case SO_OOBINLINE:
E 110
			if (m == NULL || m->m_len < sizeof (int)) {
				error = EINVAL;
				goto bad;
			}
			if (*mtod(m, int *))
				so->so_options |= optname;
			else
				so->so_options &= ~optname;
			break;
E 92

E 69
D 90
	case SO_LINGER:
I 69
		if (m == NULL || m->m_len != sizeof (int))
			return (EINVAL);
E 69
		so->so_options |= SO_LINGER;
D 69
		so->so_linger = optval;
E 69
I 69
		so->so_linger = *mtod(m, int *);
E 69
		break;

	case SO_DONTLINGER:
		so->so_options &= ~SO_LINGER;
		so->so_linger = 0;
		break;

E 90
D 72
	case SO_DONTROUTE:
		so->so_options |= SO_DONTROUTE;
		break;

	case SO_USELOOPBACK:
		so->so_options |= SO_USELOOPBACK;
		break;

E 72
D 92
	default:
D 90
		return (EINVAL);
E 90
I 90
		error = ENOPROTOOPT;
		break;
E 92
I 92
		case SO_SNDBUF:
D 128
		case SO_RCVBUF:
E 128
D 129
		case SO_SNDLOWAT:
D 128
		case SO_RCVLOWAT:
E 128
		case SO_SNDTIMEO:
I 128
			sb = &so->so_snd;
			goto bufopts;

E 129
		case SO_RCVBUF:
I 129
		case SO_SNDLOWAT:
E 129
		case SO_RCVLOWAT:
I 129
D 135
		case SO_SNDTIMEO:
E 129
E 128
		case SO_RCVTIMEO:
E 135
I 128
D 129
			sb = &so->so_rcv;
		bufopts:
E 129
E 128
			if (m == NULL || m->m_len < sizeof (int)) {
				error = EINVAL;
				goto bad;
			}
			switch (optname) {

			case SO_SNDBUF:
			case SO_RCVBUF:
D 120
				if (sbreserve(optname == SO_SNDBUF ? &so->so_snd :
				    &so->so_rcv, *mtod(m, int *)) == 0) {
E 120
I 120
D 128
				if (sbreserve(optname == SO_SNDBUF ?
				    &so->so_snd : &so->so_rcv,
				    (u_long) *mtod(m, int *)) == 0) {
E 128
I 128
D 129
				if ((val = (u_long) *mtod(m, int *)) == 0) {
					error = EINVAL;
					goto bad;
				}
				if (sbreserve(sb, val) == 0) {
E 129
I 129
				if (sbreserve(optname == SO_SNDBUF ?
				    &so->so_snd : &so->so_rcv,
				    (u_long) *mtod(m, int *)) == 0) {
E 129
E 128
E 120
					error = ENOBUFS;
					goto bad;
				}
I 128
D 129
				if (sb->sb_lowat > sb->sb_hiwat)
					sb->sb_lowat = sb->sb_hiwat;
E 129
E 128
				break;

			case SO_SNDLOWAT:
I 129
				so->so_snd.sb_lowat = *mtod(m, int *);
				break;
E 129
D 128
				so->so_snd.sb_lowat = *mtod(m, int *);
				break;
E 128
			case SO_RCVLOWAT:
D 128
				so->so_rcv.sb_lowat = *mtod(m, int *);
E 128
I 128
D 129
				if ((val = (u_long) *mtod(m, int *)) == 0 ||
				    val > sb->sb_hiwat) {
					error = EINVAL;
					goto bad;
				}
				sb->sb_lowat = val;
E 129
I 129
				so->so_rcv.sb_lowat = *mtod(m, int *);
E 129
E 128
				break;
I 135
			}
			break;

		case SO_SNDTIMEO:
		case SO_RCVTIMEO:
		    {
			struct timeval *tv;
			short val;

			if (m == NULL || m->m_len < sizeof (*tv)) {
				error = EINVAL;
				goto bad;
			}
			tv = mtod(m, struct timeval *);
D 159
			if (tv->tv_sec > SHRT_MAX / hz - hz) {
E 159
I 159
			if (tv->tv_sec * hz + tv->tv_usec / tick > SHRT_MAX) {
E 159
				error = EDOM;
				goto bad;
			}
			val = tv->tv_sec * hz + tv->tv_usec / tick;

			switch (optname) {

E 135
I 128
D 129

E 129
E 128
			case SO_SNDTIMEO:
I 129
D 135
				so->so_snd.sb_timeo = *mtod(m, int *);
E 135
I 135
				so->so_snd.sb_timeo = val;
E 135
				break;
E 129
D 128
				so->so_snd.sb_timeo = *mtod(m, int *);
				break;
E 128
			case SO_RCVTIMEO:
D 128
				so->so_rcv.sb_timeo = *mtod(m, int *);
E 128
I 128
D 129
				sb->sb_timeo = *mtod(m, int *);
E 129
I 129
D 135
				so->so_rcv.sb_timeo = *mtod(m, int *);
E 135
I 135
				so->so_rcv.sb_timeo = val;
E 135
E 129
E 128
				break;
			}
			break;
I 135
		    }
E 135

		default:
			error = ENOPROTOOPT;
			break;
		}
I 143
D 156
		m = 0;
E 143
I 142
		if (error == 0 && so->so_proto && so->so_proto->pr_ctloutput)
E 156
I 156
		if (error == 0 && so->so_proto && so->so_proto->pr_ctloutput) {
E 156
			(void) ((*so->so_proto->pr_ctloutput)
				  (PRCO_SETOPT, so, level, optname, &m0));
I 156
			m = NULL;	/* freed by protocol */
		}
E 156
E 142
E 92
E 90
	}
D 90
	return (0);
E 90
I 90
bad:
	if (m)
		(void) m_free(m);
	return (error);
E 90
}

I 158
int
E 158
D 90
sogetopt(so, level, optname, m)
E 90
I 90
sogetopt(so, level, optname, mp)
E 90
D 76
	struct socket *so;
E 76
I 76
	register struct socket *so;
E 76
	int level, optname;
D 76
	struct mbuf *m;
E 76
I 76
D 90
	register struct mbuf *m;
E 90
I 90
	struct mbuf **mp;
E 90
E 76
{
I 90
	register struct mbuf *m;
E 90
D 69
	int *optval;
E 69

D 92
	if (level != SOL_SOCKET)
D 90
		return (EINVAL);	/* XXX */
E 90
I 90
		return (EINVAL);		/* XXX */
E 90
	switch (optname) {

I 90
	case SO_LINGER:
E 92
I 92
	if (level != SOL_SOCKET) {
		if (so->so_proto && so->so_proto->pr_ctloutput) {
			return ((*so->so_proto->pr_ctloutput)
				  (PRCO_GETOPT, so, level, optname, mp));
D 136
		} else 
E 136
I 136
		} else
E 136
			return (ENOPROTOOPT);
	} else {
E 92
		m = m_get(M_WAIT, MT_SOOPTS);
I 102
		m->m_len = sizeof (int);

E 102
D 95
		if (m == NULL)
			return (ENOBUFS);
E 95
D 92
		m->m_len = sizeof (struct linger);
		mtod(m, struct linger *)->l_onoff = so->so_options & SO_LINGER;
		mtod(m, struct linger *)->l_linger = so->so_linger;
		break;
E 92
I 92
		switch (optname) {
E 92

E 90
D 92
	case SO_USELOOPBACK:
	case SO_DONTROUTE:
	case SO_DEBUG:
	case SO_KEEPALIVE:
D 90
	case SO_LINGER:
E 90
I 72
	case SO_REUSEADDR:
E 72
D 90
		if ((so->so_options & optname) == 0)
			return (ENOPROTOOPT);
D 69
		if (optname == SO_LINGER) {
E 69
I 69
		if (optname == SO_LINGER && m != NULL) {
E 69
			*mtod(m, int *) = so->so_linger;
			m->m_len = sizeof (so->so_linger);
		}
E 90
I 90
	case SO_BROADCAST:
		m = m_get(M_WAIT, MT_SOOPTS);
		if (m == NULL)
			return (ENOBUFS);
		m->m_len = sizeof (int);
		*mtod(m, int *) = so->so_options & optname;
E 90
		break;
E 92
I 92
		case SO_LINGER:
			m->m_len = sizeof (struct linger);
			mtod(m, struct linger *)->l_onoff =
				so->so_options & SO_LINGER;
			mtod(m, struct linger *)->l_linger = so->so_linger;
			break;
E 92

D 92
	default:
D 90
		return (EINVAL);
E 90
I 90
		return (ENOPROTOOPT);
E 92
I 92
		case SO_USELOOPBACK:
		case SO_DONTROUTE:
		case SO_DEBUG:
		case SO_KEEPALIVE:
		case SO_REUSEADDR:
I 149
		case SO_REUSEPORT:
E 149
		case SO_BROADCAST:
I 110
		case SO_OOBINLINE:
E 110
D 102
			m->m_len = sizeof (int);
E 102
			*mtod(m, int *) = so->so_options & optname;
I 102
			break;

		case SO_TYPE:
			*mtod(m, int *) = so->so_type;
E 102
			break;

I 101
		case SO_ERROR:
			*mtod(m, int *) = so->so_error;
			so->so_error = 0;
			break;

E 101
		case SO_SNDBUF:
			*mtod(m, int *) = so->so_snd.sb_hiwat;
			break;

		case SO_RCVBUF:
			*mtod(m, int *) = so->so_rcv.sb_hiwat;
			break;

		case SO_SNDLOWAT:
			*mtod(m, int *) = so->so_snd.sb_lowat;
			break;

		case SO_RCVLOWAT:
			*mtod(m, int *) = so->so_rcv.sb_lowat;
			break;

		case SO_SNDTIMEO:
D 135
			*mtod(m, int *) = so->so_snd.sb_timeo;
			break;

E 135
		case SO_RCVTIMEO:
D 135
			*mtod(m, int *) = so->so_rcv.sb_timeo;
E 135
I 135
		    {
			int val = (optname == SO_SNDTIMEO ?
			     so->so_snd.sb_timeo : so->so_rcv.sb_timeo);

			m->m_len = sizeof(struct timeval);
			mtod(m, struct timeval *)->tv_sec = val / hz;
			mtod(m, struct timeval *)->tv_usec =
D 159
			    (val % hz) / tick;
E 159
I 159
			    (val % hz) * tick;
E 159
E 135
			break;
I 135
		    }
E 135

		default:
D 107
			m_free(m);
E 107
I 107
			(void)m_free(m);
E 107
			return (ENOPROTOOPT);
		}
		*mp = m;
		return (0);
E 92
E 90
	}
I 90
D 92
	*mp = m;
E 90
	return (0);
E 92
}

I 158
void
E 158
E 68
I 25
sohasoutofband(so)
D 76
	struct socket *so;
E 76
I 76
	register struct socket *so;
E 76
{
I 98
	struct proc *p;
E 98

D 98
	if (so->so_pgrp == 0)
		return;
	if (so->so_pgrp > 0)
		gsignal(so->so_pgrp, SIGURG);
D 26
	else 
		psignal(-so->so_pgrp, SIGURG);
E 26
I 26
	else {
		struct proc *p = pfind(-so->so_pgrp);

		if (p)
			psignal(p, SIGURG);
	}
E 98
I 98
D 124
	if (so->so_pgrp < 0)
		gsignal(-so->so_pgrp, SIGURG);
	else if (so->so_pgrp > 0 && (p = pfind(so->so_pgrp)) != 0)
E 124
I 124
	if (so->so_pgid < 0)
		gsignal(-so->so_pgid, SIGURG);
	else if (so->so_pgid > 0 && (p = pfind(so->so_pgid)) != 0)
E 124
		psignal(p, SIGURG);
I 101
D 146
	if (so->so_rcv.sb_sel) {
		selwakeup(so->so_rcv.sb_sel, so->so_rcv.sb_flags & SB_COLL);
		so->so_rcv.sb_sel = 0;
		so->so_rcv.sb_flags &= ~SB_COLL;
	}
E 146
I 146
	selwakeup(&so->so_rcv.sb_sel);
E 146
E 101
E 98
E 26
D 76
}

E 25
D 2
skioctl()
E 2
I 2
D 5
skioctl(so, cmd, cmdp)
E 5
I 5
/*ARGSUSED*/
D 45
soioctl(so, cmd, cmdp)
E 45
I 45
soioctl(so, cmd, data)
E 45
E 5
	register struct socket *so;
	int cmd;
D 45
	register caddr_t cmdp;
E 45
I 45
	register char *data;
E 45
E 2
{

I 6
D 42
COUNT(SOIOCTL);
E 42
E 6
D 2
	/* switch out based on socket type */
E 2
I 2
D 22
	switch (cmdp) {
E 22
I 22
	switch (cmd) {
E 22
I 20

I 23
D 45
	case FIONBIO: {
		int nbio;
		if (copyin(cmdp, (caddr_t)&nbio, sizeof (nbio))) {
			u.u_error = EFAULT;
			return;
		}
		if (nbio)
E 45
I 45
	case FIONBIO:
		if (*(int *)data)
E 45
D 34
			so->so_options |= SO_NONBLOCKING;
E 34
I 34
			so->so_state |= SS_NBIO;
E 34
		else
D 34
			so->so_options &= ~SO_NONBLOCKING;
E 34
I 34
			so->so_state &= ~SS_NBIO;
E 34
D 55
		return;
E 55
I 55
D 56
		return (0);
E 56
I 56
		break;
E 56
E 55
D 45
	}
E 45

D 45
	case FIOASYNC: {
		int async;
		if (copyin(cmdp, (caddr_t)&async, sizeof (async))) {
			u.u_error = EFAULT;
			return;
		}
		if (async)
E 45
I 45
	case FIOASYNC:
		if (*(int *)data)
E 45
D 34
			;
E 34
I 34
			so->so_state |= SS_ASYNC;
E 34
		else
D 34
			;
E 34
I 34
			so->so_state &= ~SS_ASYNC;
E 34
D 55
		return;
E 55
I 55
D 56
		return (0);
E 56
I 56
		break;
E 56
E 55
D 45
	}
E 45

D 45
	case SIOCSKEEP: {
		int keep;
		if (copyin(cmdp, (caddr_t)&keep, sizeof (keep))) {
			u.u_error = EFAULT;
			return;
		}
		if (keep)
E 45
I 45
D 68
	case SIOCSKEEP:
		if (*(int *)data)
E 45
D 34
			so->so_options &= ~SO_NOKEEPALIVE;
E 34
I 34
D 43
			so->so_options &= ~SO_KEEPALIVE;
E 34
		else
E 43
D 34
			so->so_options |= SO_NOKEEPALIVE;
E 34
I 34
D 44
			so->so_options |= SO_KEEPALIVE;
I 43
		else
E 44
			so->so_options &= ~SO_KEEPALIVE;
I 44
		else
			so->so_options |= SO_KEEPALIVE;
E 44
E 43
E 34
D 55
		return;
E 55
I 55
D 56
		return (0);
E 56
I 56
		break;
E 56
E 55
D 45
	}
E 45

D 45
	case SIOCGKEEP: {
D 34
		int keep = (so->so_options & SO_NOKEEPALIVE) == 0;
E 34
I 34
		int keep = (so->so_options & SO_KEEPALIVE) != 0;
E 34
		if (copyout((caddr_t)&keep, cmdp, sizeof (keep)))
			u.u_error = EFAULT;
E 45
I 45
	case SIOCGKEEP:
		*(int *)data = (so->so_options & SO_KEEPALIVE) != 0;
E 45
D 55
		return;
E 55
I 55
D 56
		return (0);
E 56
I 56
		break;
E 56
E 55
D 45
	}
E 45

D 45
	case SIOCSLINGER: {
		int linger;
		if (copyin(cmdp, (caddr_t)&linger, sizeof (linger))) {
			u.u_error = EFAULT;
			return;
		}
		so->so_linger = linger;
E 45
I 45
	case SIOCSLINGER:
		so->so_linger = *(int *)data;
E 45
		if (so->so_linger)
			so->so_options &= ~SO_DONTLINGER;
		else
			so->so_options |= SO_DONTLINGER;
D 55
		return;
E 55
I 55
D 56
		return (0);
E 56
I 56
		break;
E 56
E 55
D 45
	}
E 45

D 45
	case SIOCGLINGER: {
		int linger = so->so_linger;
		if (copyout((caddr_t)&linger, cmdp, sizeof (linger))) {
			u.u_error = EFAULT;
			return;
		}
	}
I 25
	case SIOCSPGRP: {
		int pgrp;
		if (copyin(cmdp, (caddr_t)&pgrp, sizeof (pgrp))) {
			u.u_error = EFAULT;
			return;
		}
		so->so_pgrp = pgrp;
E 45
I 45
	case SIOCGLINGER:
		*(int *)data = so->so_linger;
E 45
D 55
		return;
E 55
I 55
D 56
		return (0);
E 56
I 56
		break;
E 56
E 55
D 45
	}
E 45
E 25

E 68
I 25
D 45
	case SIOCGPGRP: {
		int pgrp = so->so_pgrp;
		if (copyout((caddr_t)&pgrp, cmdp, sizeof (pgrp))) {
			u.u_error = EFAULT;
			return;
		}
	}
E 45
I 45
	case SIOCSPGRP:
		so->so_pgrp = *(int *)data;
D 55
		return;
E 55
I 55
D 56
		return (0);
E 56
I 56
		break;
E 56
E 55
E 45

I 45
	case SIOCGPGRP:
		*(int *)data = so->so_pgrp;
D 55
		return;
E 55
I 55
D 56
		return (0);
E 56
I 56
		break;
E 56
E 55
D 68

E 45
E 25
E 23
	case SIOCDONE: {
D 45
		int flags;
		if (copyin(cmdp, (caddr_t)&flags, sizeof (flags))) {
			u.u_error = EFAULT;
			return;
		}
E 45
I 45
		int flags = *(int *)data;

E 45
I 23
		flags++;
E 23
		if (flags & FREAD) {
			int s = splimp();
			socantrcvmore(so);
			sbflush(&so->so_rcv);
I 33
			splx(s);
E 33
		}
		if (flags & FWRITE)
D 22
			(*so->so_proto->pr_usrreq)(so, PRU_DISCONNECT, (struct mbuf *)0, 0);
E 22
I 22
D 24
			u.u_error = (*so->so_proto->pr_usrreq)(so, PRU_DISCONNECT, (struct mbuf *)0, 0);
E 24
I 24
D 50
			u.u_error = (*so->so_proto->pr_usrreq)(so, PRU_SHUTDOWN, (struct mbuf *)0, 0);
E 50
I 50
D 55
			u.u_error = (*so->so_proto->pr_usrreq)(so, PRU_SHUTDOWN,
E 55
I 55
			return ((*so->so_proto->pr_usrreq)(so, PRU_SHUTDOWN,
E 55
			    (struct mbuf *)0, (struct mbuf *)0,
D 55
			    (struct socketopt *)0);
E 50
E 24
E 22
		return;
E 55
I 55
			    (struct socketopt *)0));
D 56
		return (0);
E 56
I 56
		break;
E 56
E 55
	}
E 68
E 20

I 25
D 65
	case SIOCSENDOOB: {
D 45
		char oob;
E 45
I 45
		char oob = *(char *)data;
E 45
D 51
		struct mbuf *m;
E 51
I 51
		struct mbuf *m = m_get(M_DONTWAIT);
E 51
D 45
		if (copyin(cmdp, (caddr_t)&oob, sizeof (oob))) {
			u.u_error = EFAULT;
			return;
		}
E 45
I 45

E 45
D 51
		m = m_get(M_DONTWAIT);
E 51
D 56
		if (m == 0) {
			u.u_error = ENOBUFS;
			return;
		}
E 56
I 56
		if (m == 0)
			return (ENOBUFS);
E 56
D 51
		m->m_off = MMINOFF;
D 45
		m->m_len = 1;
		*mtod(m, caddr_t) = oob;
E 45
I 45
		m->m_len = sizeof (char);
E 51
I 51
		m->m_len = 1;
E 51
		*mtod(m, char *) = oob;
E 45
D 50
		(*so->so_proto->pr_usrreq)(so, PRU_SENDOOB, m, 0);
E 50
I 50
D 55
		(*so->so_proto->pr_usrreq)(so, PRU_SENDOOB,
		    m, (struct mbuf *)0, (struct socketopt *)0);
E 50
		return;
E 55
I 55
		return ((*so->so_proto->pr_usrreq)(so, PRU_SENDOOB,
		    m, (struct mbuf *)0, (struct socketopt *)0));
E 55
	}

	case SIOCRCVOOB: {
D 51
		struct mbuf *m = m_get(M_DONTWAIT);
E 51
I 51
		struct mbuf *m = m_get(M_WAIT);
E 51
I 45

E 45
D 56
		if (m == 0) {
			u.u_error = ENOBUFS;
D 55
			return;
E 55
I 55
			return (0);
E 55
		}
E 56
I 56
		if (m == 0)
			return (ENOBUFS);
E 56
D 51
		m->m_off = MMINOFF; *mtod(m, caddr_t) = 0;
E 51
I 51
		*mtod(m, caddr_t) = 0;
E 51
D 50
		(*so->so_proto->pr_usrreq)(so, PRU_RCVOOB, m, 0);
E 50
I 50
		(*so->so_proto->pr_usrreq)(so, PRU_RCVOOB,
		    m, (struct mbuf *)0, (struct socketopt *)0);
E 50
D 45
		if (copyout(mtod(m, caddr_t), cmdp, sizeof (char))) {
			u.u_error = EFAULT;
			return;
		}
		m_free(m);
E 45
I 45
		*(char *)data = *mtod(m, char *);
		(void) m_free(m);
E 45
D 55
		return;
E 55
I 55
D 56
		return (0);
E 56
I 56
		break;
E 56
E 55
	}

E 65
D 45
	case SIOCATMARK: {
		int atmark = (so->so_state&SS_RCVATMARK) != 0;
		if (copyout((caddr_t)&atmark, cmdp, sizeof (atmark))) {
			u.u_error = EFAULT;
			return;
		}
E 45
I 45
	case SIOCATMARK:
		*(int *)data = (so->so_state&SS_RCVATMARK) != 0;
E 45
D 55
		return;
E 55
I 55
D 56
		return (0);
E 56
I 56
		break;
E 56
E 55
D 45
	}
E 45
I 37

	/* routing table update calls */
	case SIOCADDRT:
	case SIOCDELRT:
D 45
	case SIOCCHGRT: {
		struct rtentry route;
E 45
D 39
#ifdef notdef
E 39
		if (!suser())
D 55
			return;
D 39
#endif
E 39
D 45
		if (copyin(cmdp, (caddr_t)&route, sizeof (route))) {
			u.u_error = EFAULT;
			return;
		}
		u.u_error = rtrequest(cmd, &route);
E 45
I 45
		u.u_error = rtrequest(cmd, (struct rtentry *)data);
E 45
		return;
E 55
I 55
D 67
			return (u.u_error);		/* XXX */
E 67
I 67
			return (u.u_error);
E 67
		return (rtrequest(cmd, (struct rtentry *)data));
I 73

	/* interface parameter requests */
	case SIOCSIFADDR:
	case SIOCSIFFLAGS:
I 74
	case SIOCSIFDSTADDR:
E 74
		if (!suser())
			return (u.u_error);
		return (ifrequest(cmd, data));

	case SIOCGIFADDR:
	case SIOCGIFFLAGS:
I 74
	case SIOCGIFDSTADDR:
E 74
		return (ifrequest(cmd, data));

	case SIOCGIFCONF:
		return (ifconf(cmd, data));
E 73
E 55
D 45
	}
E 45

E 37
I 27
	/* type/protocol specific ioctls */
I 56
	default:
D 67
		return (ENOTTY);
E 67
I 67
		return (ENOTTY);		/* XXX */
E 67
E 56
E 27
E 25
	}
D 27
	switch (so->so_type) {

	case SOCK_STREAM:
		break;

	case SOCK_DGRAM:
		break;

	case SOCK_RDM:
		break;

	case SOCK_RAW:
		break;
D 23

E 23
	}
E 27
I 27
D 55
	u.u_error = EOPNOTSUPP;
E 55
I 55
D 56
	return (EOPNOTSUPP);
E 56
I 56
	return (0);
E 76
E 56
E 55
E 27
I 13
D 14
}

nullchk(where, m0)
	char *where;
	struct mbuf *m0;
{
	register struct mbuf *m;

	for (m = m0; m; m = m->m_next)
		if (nullany(mtod(m, caddr_t), m->m_len))
			goto bad;
	return;
bad:
	printf("nullchk: %s\n", where);
	for (m = m0; m; m = m->m_next)
		printf("\t%x len %d: %s\n", m, m->m_len,
		    nullany(mtod(m, caddr_t), m->m_len) ? "BAD" : "OK");
}

nullblk(where, m, len)
	char *where;
	struct mbuf *m;
	int len;
{

	if (nullany(mtod(m, caddr_t), len))
		printf("nullblk: %s m=%x len=%d\n", where, m, len);
}

nullany(cp, len)
	char *cp;
	int len;
{
	for (; len > 0; len--)
		if (*cp++ == 0)
			return (0);		/* XXX */
	return (0);
E 14
E 13
}
D 3

sostat(so)
	struct socket *so;
{

}

/*
 * Generic protocol handler.
 */
gen_usrreq()
{

E 2
}
E 3
I 3
D 4
/*###417 [cc] operands of = have incompatible types %%%*/
/*###417 [cc] zeroin_addr undefined %%%*/
E 4
E 3
E 1
