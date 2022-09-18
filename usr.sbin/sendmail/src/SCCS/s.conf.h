h46699
s 00000/00002/01697
d D 8.196 95/06/21 06:42:29 eric 276 275
c ping-ponging ISC_UNIX changes from J.J.Bailey <jjb@jagware.bcc.com>
e
s 00016/00000/01683
d D 8.195 95/06/20 12:20:29 eric 275 274
c add KSR support
e
s 00003/00000/01680
d D 8.194 95/06/20 10:44:20 eric 274 273
c declare h_errno in conf.h
e
s 00003/00001/01677
d D 8.193 95/06/20 06:14:41 eric 273 272
c woops -- generic vendor paths need to be ifdefed
e
s 00004/00000/01674
d D 8.192 95/06/20 06:08:05 eric 272 271
c DG/UX changes
e
s 00032/00072/01642
d D 8.191 95/06/19 18:12:22 eric 271 270
c default scanf on; always use /etc/sendmail.cf regardless of vendor
c preferences
e
s 00008/00001/01706
d D 8.190 95/06/15 08:22:30 eric 270 269
c updates for A/UX
e
s 00003/00003/01704
d D 8.189 95/06/13 09:31:05 eric 269 268
c compile glitch with NETLINK
e
s 00042/00027/01665
d D 8.188 95/06/13 09:22:51 eric 268 267
c make a bunch of #defines into 0/1 instead of ifdef/ifndef
e
s 00006/00005/01686
d D 8.187 95/06/13 06:27:49 eric 267 266
c udpates for NEWS-OS from Motonori Nakamura
e
s 00001/00001/01690
d D 8.186 95/06/11 09:25:54 eric 266 265
c fixes for BSDI
e
s 00002/00000/01689
d D 8.185 95/06/10 15:49:09 eric 265 264
c changes for ISC_UNIX
e
s 00001/00001/01688
d D 8.184 95/06/10 14:13:56 eric 264 262
c sys/mkdev.h seems to be specific to UnixWare
e
s 00003/00001/01688
d R 8.184 95/06/10 13:30:25 eric 263 262
c be a bit more gentle about including <sys/mkdev.h> on SVr4
e
s 00001/00000/01688
d D 8.183 95/06/10 11:20:30 eric 262 261
c updates for IRIX5 & IRIX6
e
s 00006/00006/01682
d D 8.182 95/06/10 10:27:05 eric 261 260
c cleanup for FreeBSD/NetBSD; drop 386BSD
e
s 00002/00000/01686
d D 8.181 95/06/05 08:15:26 eric 260 259
c AIX 3 fixes
e
s 00001/00000/01685
d D 8.180 95/06/05 08:13:51 eric 259 258
c SVr4 needs <sys/mkdev.h>
e
s 00001/00001/01684
d D 8.179 95/06/05 08:08:07 eric 258 257
c UnixWare can use sysconf() instead of getdtablesize
e
s 00001/00001/01684
d D 8.178 95/05/30 11:07:13 eric 257 256
c define BSD_COMP on all SVr4 systems
e
s 00001/00000/01684
d D 8.177 95/05/30 07:31:54 eric 256 255
c NCR3000 needs explicit include of sys/sockio.h
e
s 00003/00001/01681
d D 8.176 95/05/28 19:48:45 eric 255 254
c glitch that causes compile problems (sometimes) on HP-UX
e
s 00001/00003/01681
d D 8.175 95/05/28 11:49:23 eric 254 253
c lint
e
s 00000/00004/01684
d D 8.174 95/05/27 09:25:19 eric 253 252
c make the maximum number of jobs in one queue run an option
e
s 00003/00002/01685
d D 8.173 95/05/27 09:16:14 eric 252 251
c dynmically extend the queue size
e
s 00001/00001/01686
d D 8.172 95/05/27 07:47:05 eric 251 250
c include putenv() implementation that doesn't depend on setenv()
e
s 00001/00000/01686
d D 8.171 95/05/25 12:46:09 eric 250 249
c patch for NeXTstep
e
s 00004/00004/01682
d D 8.170 95/05/25 12:27:55 eric 249 247
c Linux doesn't support IP_OPTIONS
e
s 00004/00004/01682
d R 8.170 95/05/25 12:26:42 eric 248 247
c Linux doesn't have IP_OPTIONS support
e
s 00006/00004/01680
d D 8.169 95/05/25 11:38:11 eric 247 246
c cleanup for IRIX5
e
s 00015/00015/01669
d D 8.168 95/05/25 07:57:00 eric 246 245
c NCR3000 doesn't handle IP_SRCROUTE; explicitly state that it
c works on systems where we know it does so that we can change the default
c to off if necessary; misc cleanup
e
s 00002/00000/01682
d D 8.167 95/05/25 06:24:43 eric 245 244
c support for SunOS 4.0.3 and the LUNA
e
s 00001/00000/01681
d D 8.166 95/05/24 15:39:42 eric 244 243
c include BSD ioctl calls in Solaris
e
s 00005/00000/01676
d D 8.165 95/05/24 08:24:08 eric 243 242
c portability for Japanese workstations from Motonori Nakamura
e
s 00033/00023/01643
d D 8.164 95/05/23 16:44:32 eric 242 241
c allow use of seteuid() on systems that have new Posix semantics
e
s 00010/00000/01656
d D 8.163 95/05/22 08:29:58 eric 241 240
c add option to print IP source routing info
e
s 00006/00000/01650
d D 8.162 95/05/19 16:00:11 eric 240 239
c fix compile problems on various platforms
e
s 00003/00000/01647
d D 8.161 95/05/17 07:20:44 eric 239 238
c handle AF_LINK addresses on 4.4BSD networking
e
s 00008/00000/01639
d D 8.160 95/05/15 19:00:20 eric 238 237
c put MIME 8->7 bit conversions on a compile flag (default on for now)
e
s 00009/00005/01630
d D 8.159 95/05/15 07:37:31 eric 237 236
c cleanup of LA_READKSYM code from Motonori NAKAMURA <motonori@cs.ritsumei.ac.jp>
e
s 00007/00003/01628
d D 8.158 95/05/14 20:19:34 eric 236 235
c more cleanup from Motonori Nakamura
e
s 00006/00018/01625
d D 8.157 95/05/14 09:05:50 eric 235 234
c portability patches for Sony NEWS-OS 4.2.1R and 6.0.3,
c Omron LUNAs, and NEC EWS-UX/V 4.2
e
s 00003/00000/01640
d D 8.156 95/05/13 15:05:58 eric 234 233
c put getcanonname into service switch
e
s 00004/00002/01636
d D 8.155 95/05/05 08:18:32 eric 233 232
c allow command-line redefinitions of BROKEN_RES_SEARCH
e
s 00029/00009/01609
d D 8.154 95/04/25 17:08:06 eric 232 231
c HP-UX 10.0 portability changes
e
s 00001/00000/01617
d D 8.153 95/04/24 16:48:29 eric 231 230
c HP-UX uses SPT_PSTAT
e
s 00005/00001/01612
d D 8.152 95/04/22 11:06:16 eric 230 229
c default DSNs on
e
s 00001/00001/01612
d D 8.151 95/04/21 09:56:58 eric 229 228
c update copyright notice
e
s 00001/00001/01612
d D 8.150 95/04/20 06:37:19 eric 228 227
c solaris 2.3 cleanup
e
s 00001/00000/01612
d D 8.149 95/04/14 08:16:47 eric 227 226
c res_search(unknown.host) is broken (returns h_errno = 0) on AUX
e
s 00002/00002/01610
d D 8.148 95/04/12 07:46:56 eric 226 225
c define USERDB if either NEWDB or HESIOD are defined
e
s 00001/00001/01611
d D 8.147 95/04/09 11:57:36 eric 225 224
c minor cleanup from last set of changes
e
s 00133/00003/01479
d D 8.146 95/04/07 19:19:21 eric 224 223
c portability fixes for various Japanese workstations
e
s 00004/00004/01478
d D 8.145 95/03/31 16:53:50 eric 223 222
c merge a bit with Sun version
e
s 00010/00000/01472
d D 8.144 95/03/31 15:46:47 eric 222 221
c more type hacking for non-Posix/ANSI systems
e
s 00002/00000/01470
d D 8.143 95/03/31 10:51:52 eric 221 220
c pull getpwXXX and gethostbyXXX calls out into conf.c so they can
c be tweaked
e
s 00005/00003/01465
d D 8.142 95/03/30 15:20:41 eric 220 219
c IRIX 5.2/5.3 changes
e
s 00003/00000/01465
d D 8.141 95/03/12 09:02:04 eric 219 218
c flock(2) is broken in Linux
e
s 00002/00001/01463
d D 8.140 95/03/11 18:02:16 eric 218 217
c more MIME cleanup
e
s 00001/00000/01463
d D 8.139 95/03/11 14:27:49 eric 217 216
c add MAXMIMENESTING
e
s 00005/00002/01458
d D 8.138 95/03/06 15:11:46 eric 216 215
c fix some race conditions for file opens
e
s 00005/00003/01455
d D 8.137 95/03/05 12:39:12 eric 215 214
c Solaris 2.4 changes
e
s 00045/00005/01413
d D 8.136 95/02/24 07:04:05 eric 214 213
c ISC (SunSoft) Unix (never heard of this one)
e
s 00007/00000/01411
d D 8.135 95/02/24 06:48:21 eric 213 212
c change way statfs.f_bavail is handled to be more general
e
s 00001/00001/01410
d D 8.134 95/02/20 07:13:58 eric 212 211
c double number of rewriting sets (half numeric, half symbolic)
e
s 00021/00002/01390
d D 8.133 95/02/19 07:28:57 eric 211 210
c support for Cray Computer Corp's CSOS
e
s 00001/00001/01391
d D 8.132 95/02/14 08:11:38 eric 210 209
c use LA_SUBR for HP-UX load average (for pstat_getdynamic(2))
e
s 00001/00001/01391
d D 8.131 95/02/06 07:20:22 eric 209 208
c IRIX6.0 is actually IRIX64 -- get rid of a compile flag
e
s 00003/00001/01389
d D 8.130 95/02/04 08:06:35 eric 208 207
c first cut at IRIX 6.0 changes
e
s 00001/00000/01389
d D 8.129 95/01/07 11:18:43 eric 207 206
c enable load average for AIX3
e
s 00039/00000/01350
d D 8.128 94/12/28 07:32:00 eric 206 205
c portability fixes for Amdahl UTS System V 2.1.5
e
s 00009/00005/01341
d D 8.127 94/12/15 06:33:47 eric 205 204
c Linux updates
e
s 00002/00002/01344
d D 8.126 94/12/11 14:04:59 eric 204 203
c change Paragon e-mail address
e
s 00015/00000/01331
d D 8.125 94/12/10 09:20:43 eric 203 202
c add Intel Paragon support
e
s 00034/00004/01297
d D 8.124 94/12/05 14:06:35 eric 202 201
c patches for Altos System V
e
s 00013/00001/01288
d D 8.123 94/11/22 08:18:29 eric 201 200
c IRIX64 and DG-UX updates
e
s 00002/00000/01287
d D 8.122 94/11/05 10:31:51 eric 200 199
c Linux problem with getusershell(3)
e
s 00001/00001/01286
d D 8.121 94/10/15 08:55:20 eric 199 198
c SCO Unix updates
e
s 00008/00006/01279
d D 8.120 94/09/09 16:47:14 eric 198 197
c change setproctitle definitions to use SPT_TYPE variable a la
c SFS_TYPE and LA_TYPE; this allows for a cleaner integration of new types
e
s 00008/00006/01277
d D 8.119 94/08/29 08:51:57 eric 197 196
c UnixWare updates
e
s 00005/00001/01278
d D 8.118 94/08/27 09:22:50 eric 196 195
c System V release 4 has initgroups(3) and setrlimit(2)
e
s 00002/00000/01277
d D 8.117 94/08/21 15:25:29 eric 195 194
c new map classes in preparation for service abstraction; multiple
c queue timeouts
e
s 00006/00007/01271
d D 8.116 94/08/09 07:56:22 eric 194 193
c setproctitle updates for AIX
e
s 00003/00003/01275
d D 8.115 94/08/07 14:00:31 eric 193 192
c change name of TZ_TYPE values -- the USE_ was bogus
e
s 00007/00000/01271
d D 8.114 94/08/07 12:06:41 eric 192 191
c defaults for TZ_TYPE -- this will probably require some tuning
e
s 00040/00000/01231
d D 8.113 94/07/04 06:25:41 eric 191 190
c Portability fixes for Hitachi HI-UX/WE2
e
s 00001/00000/01230
d D 8.112 94/06/19 11:13:34 eric 190 189
c generalize nlist value masking
e
s 00017/00003/01213
d D 8.111 94/06/19 08:53:42 eric 189 188
c updates for SVR4 and NonStop-UX
e
s 00014/00000/01202
d D 8.110 94/06/19 07:34:15 eric 188 187
c avoid denial-of-service attacks caused by setting resource limits
c low before calling sendmail
e
s 00010/00002/01192
d D 8.109 94/06/19 06:37:07 eric 187 186
c portability fixes for DG/UX 5.4.3
e
s 00019/00001/01175
d D 8.108 94/06/17 17:39:55 eric 186 185
c compatibility with BIND 4.9.3 (just cleanup)
e
s 00008/00000/01168
d D 8.107 94/06/17 11:12:49 eric 185 184
c Cray fixes from Eric Wassenaar
e
s 00003/00000/01165
d D 8.106 94/05/17 08:10:50 eric 184 183
c portability for System V Release 4
e
s 00001/00001/01164
d D 8.105 94/05/12 07:00:16 eric 183 182
c portability fix for Solaris 2
e
s 00015/00005/01150
d D 8.104 94/04/17 07:05:45 eric 182 181
c make OLD_NEWDB a #if instead of #ifdef; autoconfigure it for old
c versions of BSD/386
e
s 00014/00000/01141
d D 8.103 94/04/13 10:34:06 eric 181 180
c NCR 3000 changes
e
s 00002/00001/01139
d D 8.102 94/04/12 15:42:15 eric 180 179
c IRIX cleanup
e
s 00001/00000/01139
d D 8.101 94/04/12 14:18:56 eric 179 178
c SCO support for fsync
e
s 00003/00000/01136
d D 8.100 94/04/12 09:31:47 eric 178 177
c NetBSD updates
e
s 00031/00000/01105
d D 8.99 94/04/12 09:01:04 eric 177 176
c UnixWare changes
e
s 00016/00000/01089
d D 8.98 94/04/12 08:38:30 eric 176 175
c updates for Intergraph CLIX
e
s 00006/00002/01083
d D 8.97 94/04/07 18:28:41 eric 175 174
c portability changes for SunOS and BSD/386
e
s 00010/00002/01075
d D 8.96 94/03/11 14:42:15 eric 174 173
c change NAMED_BIND to a 0/1 flag to allow Makefile override
e
s 00001/00000/01076
d D 8.95 94/03/06 09:06:04 eric 173 172
c apply workaround to broken res_search on Ultrix
e
s 00001/00001/01075
d D 8.94 94/03/03 08:35:09 eric 172 171
c Linux portability changes; add LA_PROCSTR
e
s 00015/00009/01061
d D 8.93 94/03/03 08:18:21 eric 171 170
c more Linux portability changes (geez, what a pain)
e
s 00013/00006/01057
d D 8.92 94/03/02 09:09:42 eric 170 169
c Linux changes -- are these any good?
e
s 00001/00000/01062
d D 8.91 94/02/22 15:24:03 eric 169 168
c Ultrix has uname(2) syscall
e
s 00003/00003/01059
d D 8.90 94/02/22 09:38:09 eric 168 167
c fix reversed conditions on HASFLOCK settings
e
s 00007/00000/01055
d D 8.89 94/02/17 09:24:46 eric 167 166
c don't use IDENTPROTO on Sequent
e
s 00001/00001/01054
d D 8.88 94/02/10 09:06:16 eric 166 165
c portabiltiy fix for DomainOS
e
s 00028/00000/01027
d D 8.87 94/02/09 10:38:19 eric 165 164
c Sequent DYNIX/ptx changes
e
s 00001/00000/01026
d D 8.86 94/02/09 07:39:55 eric 164 163
c DG/UX doesn't have getusershell(3)
e
s 00002/00003/01024
d D 8.85 94/02/08 08:53:29 eric 163 162
c fix some HASSTATFS defines that have snuck in
e
s 00003/00003/01024
d D 8.84 94/02/07 09:30:01 eric 162 161
c allow full size syslog buffer in all Solaris versions by default,
c since patches are available
e
s 00029/00003/00998
d D 8.83 94/02/03 08:07:11 eric 161 160
c portability fixes for BSD/386 and Solaris 2.3
e
s 00008/00000/00993
d D 8.82 94/01/31 19:56:58 eric 160 159
c default SCANF on if we are going to link it anyway
e
s 00017/00001/00976
d D 8.81 94/01/31 17:00:25 eric 159 158
c fixes for older BSDs and ConvexOS systems
e
s 00000/00003/00977
d D 8.80 94/01/26 17:35:32 eric 158 157
c the Linux flock() problem was only on one release
e
s 00029/00007/00951
d D 8.79 94/01/22 16:12:21 eric 157 156
c make HASFLOCK a 0/1 definition so Linux can turn it off
e
s 00032/00000/00926
d D 8.78 94/01/22 08:59:42 eric 156 155
c Apollo & NeXT portability fixes
e
s 00021/00020/00905
d D 8.77 94/01/15 12:37:00 eric 155 154
c change method of declaring statfs(2) functionality
e
s 00014/00000/00911
d D 8.76 94/01/15 09:34:32 eric 154 153
c UNICOS portability
e
s 00006/00000/00905
d D 8.75 94/01/08 17:53:10 eric 153 151
c HP-UX portability changes
e
s 00003/00000/00905
d R 8.75 94/01/08 17:26:53 eric 152 151
c HP-UX portability changes
e
s 00001/00001/00904
d D 8.74 94/01/07 14:57:22 eric 151 150
c change HOP-
e
s 00002/00001/00903
d D 8.73 94/01/05 10:20:10 eric 150 149
c syslog portability for HP-UX; fix typo for OSF/1 pid file
e
s 00004/00000/00900
d D 8.72 94/01/03 09:32:25 eric 149 148
c HP-UX portability
e
s 00003/00001/00897
d D 8.71 93/12/29 09:29:28 eric 148 147
c Solaris native cc doesn't predefine __svr4__ (sigh)
e
s 00001/00000/00897
d D 8.70 93/12/26 07:46:54 eric 147 146
c SCO UNIX doesn't have getusershell(3)
e
s 00009/00009/00888
d D 8.69 93/12/26 06:07:52 eric 146 145
c clean up implementation if you don't have getusershell(3) in libc
e
s 00012/00000/00885
d D 8.68 93/12/24 10:12:28 eric 145 144
c first cut at adding NEEDGETUSERSHELL
e
s 00027/00018/00858
d D 8.67 93/12/21 06:20:16 eric 144 143
c System V Release 4 changes
e
s 00001/00001/00875
d D 8.66 93/12/17 19:16:04 eric 143 142
c GIDSET_T is gid_t only on Solaris, not on SunOS
e
s 00001/00000/00875
d D 8.65 93/12/17 18:19:30 eric 142 141
c getgroups on Sun systems takes an array of gid_t, not of int
e
s 00033/00025/00842
d D 8.64 93/12/17 06:03:11 eric 141 140
c rearrange IDENTPROTO definitions to make it easier to turn on in Makefile
e
s 00006/00002/00861
d D 8.63 93/12/14 08:25:45 eric 140 139
c VAX Ultrix changes
e
s 00017/00001/00846
d D 8.62 93/12/12 06:46:24 eric 139 138
c updates for SunOS 4.0.3 and SVR4
e
s 00016/00000/00831
d D 8.61 93/12/11 13:15:30 eric 138 137
c add support for SCO Open Server 3.2v4
e
s 00010/00001/00821
d D 8.60 93/12/10 12:37:54 eric 137 136
c move SYSLOG_BUFSIZE in here
e
s 00002/00002/00820
d D 8.59 93/12/10 06:24:33 eric 136 135
c NetBSD changes
e
s 00001/00000/00821
d D 8.58 93/12/09 13:37:37 eric 135 134
c Linux portability
e
s 00007/00001/00814
d D 8.57 93/12/02 10:17:44 eric 134 133
c fix bogus implementation of name overflow limiting
e
s 00016/00002/00799
d D 8.56 93/12/01 10:52:58 eric 133 131
c RISC/os patches
e
s 00015/00002/00799
d R 8.56 93/12/01 09:22:42 eric 132 131
c RISC/os changes
e
s 00054/00006/00747
d D 8.55 93/11/27 14:17:20 eric 131 130
c add DYNIX support
e
s 00012/00002/00741
d D 8.54 93/11/25 11:32:58 eric 130 129
c security patches to seal up symbolic link attacks
e
s 00027/00000/00716
d D 8.53 93/11/25 08:17:38 eric 129 128
c add clause for Stardent Titan running TitanOS 4.2
e
s 00006/00000/00710
d D 8.52 93/11/20 07:36:03 eric 128 127
c change IDENTPROTO from a #ifdef to a #if
e
s 00006/00001/00704
d D 8.51 93/11/20 06:57:09 eric 127 126
c claim is that DELL 2.2 has seteuid that works fine
e
s 00004/00000/00701
d D 8.50 93/11/14 07:51:55 eric 126 125
c Solaris portability
e
s 00002/00000/00699
d D 8.49 93/11/13 08:16:39 eric 125 124
c AIX has statfs() and uname()
e
s 00004/00000/00695
d D 8.48 93/11/12 06:30:27 eric 124 122
c 4.3BSD changes
e
s 00002/00000/00695
d R 8.48 93/11/12 06:23:50 eric 123 122
c 4.3 BSD changes
e
s 00002/00002/00693
d D 8.47 93/11/11 16:52:27 eric 122 121
c Solaris portability changes
e
s 00007/00003/00688
d D 8.46 93/11/11 15:44:17 eric 121 120
c revert to using flock() whenever possible
e
s 00049/00004/00642
d D 8.45 93/11/07 15:59:29 eric 120 119
c DG/UX and MACH/386 changes; support for systems that don't have
c unix domain sockets at all
e
s 00001/00001/00645
d D 8.44 93/10/29 06:44:28 eric 119 118
c Linux portability changes
e
s 00001/00000/00645
d D 8.43 93/10/28 06:51:27 eric 118 117
c Linux portability patches
e
s 00018/00000/00627
d D 8.42 93/10/21 07:19:37 eric 117 116
c 386BSD/FreeBSD/NetBSD
e
s 00001/00000/00626
d D 8.41 93/10/17 19:57:13 eric 116 115
c portability for A/UX
e
s 00001/00000/00625
d D 8.40 93/10/17 19:29:14 eric 115 114
c portability
e
s 00003/00000/00622
d D 8.39 93/10/17 19:27:11 eric 114 113
c portability of minor() & major() macros
e
s 00027/00003/00595
d D 8.38 93/10/15 08:34:32 eric 113 112
c 8.6.2: improved error return messages; better error handling on
c hung connections or the name server is down; add "vendor code" on V line;
c fix some X-Authentication-Warning: problems; portability fixes
e
s 00025/00000/00573
d D 8.37 93/10/08 15:54:40 eric 112 111
c 8.6.1: A/UX and Encore UMAX V patches; fix to not toss error messages
c too early
e
s 00001/00000/00572
d D 8.36 93/09/22 10:45:28 eric 111 110
c NeXT also uses union wait
e
s 00001/00000/00571
d D 8.35 93/09/22 10:32:24 eric 110 109
c include hacks to allow old versions of wait that use "union wait"
e
s 00005/00000/00566
d D 8.34 93/09/22 10:03:01 eric 109 108
c compile cleanup on various systems (mostly AUX)
e
s 00002/00000/00564
d D 8.33 93/09/22 09:46:56 eric 108 107
c redefine WIFEXITED and WEXITSTATUS for AUX
e
s 00012/00000/00552
d D 8.32 93/09/19 19:23:25 eric 107 106
c NeXT portability changes; cleanup of <sys/wait.h> assumptions
e
s 00001/00000/00551
d D 8.31 93/09/18 17:15:17 eric 106 105
c #undef SETPROCTITLE on AIX -- it confuses things
e
s 00003/00002/00548
d D 8.30 93/09/05 12:31:56 eric 105 104
c comments only
e
s 00022/00004/00528
d D 8.29 93/09/02 09:44:57 eric 104 103
c AUX compatibility
e
s 00003/00002/00529
d D 8.28 93/08/26 08:24:06 eric 103 102
c #undef IDENTPROTO for 4.3 systems
e
s 00023/00000/00508
d D 8.27 93/08/24 14:44:39 eric 102 101
c add DELL_SVR4 support
e
s 00000/00001/00508
d D 8.26 93/08/23 10:17:30 eric 101 100
c instead of MyIpAddrs, put all [...] names in $=w
e
s 00017/00000/00492
d D 8.25 93/08/21 07:22:52 eric 100 99
c more NeXT portability changes; use initgroups when reading .forward files
e
s 00000/00009/00492
d D 8.24 93/08/20 11:52:00 eric 99 98
c more on elimination of frozen config files
e
s 00003/00001/00498
d D 8.23 93/08/19 07:01:11 eric 98 97
c NeXT load average
e
s 00005/00001/00494
d D 8.22 93/08/15 11:07:30 eric 97 96
c fix problem on Ultrix -- fcntl locking doesn't auto-release locks
c when the file is closed
e
s 00018/00001/00477
d D 8.21 93/08/08 15:08:10 eric 96 95
c POSIX and Linux changes
e
s 00003/00000/00475
d D 8.20 93/08/06 21:20:09 eric 95 94
c Solaris and NeXT portability
e
s 00001/00001/00474
d D 8.19 93/07/28 08:10:14 eric 94 93
c use NeXT as compile flag -- apparently NeXT cc auto-defines this
e
s 00021/00010/00454
d D 8.18 93/07/27 21:38:15 eric 93 92
c portability enhancements: NeXT and SCO
e
s 00033/00019/00431
d D 8.17 93/07/26 09:21:58 eric 92 91
c signal and file locking portability changes
e
s 00016/00014/00434
d D 8.16 93/07/24 08:06:27 eric 91 90
c move IDENTPROTO defines around to simplify turning it off on a
c per-OS basis
e
s 00013/00000/00435
d D 8.15 93/07/22 11:27:52 eric 90 89
c fix bogus error message with open timeout in :include: -- this also
c fixes a bug that caused resolver errnos to conflict with real errnos
e
s 00001/00000/00434
d D 8.14 93/07/22 08:42:46 eric 89 88
c SCO UNIX changes
e
s 00006/00005/00428
d D 8.13 93/07/21 18:20:12 eric 88 87
c Convex changes
e
s 00006/00000/00427
d D 8.12 93/07/21 11:50:14 eric 87 86
c more 4.3 changes
e
s 00021/00000/00406
d D 8.11 93/07/21 11:45:41 eric 86 85
c old 4.3BSD changes
e
s 00002/00000/00404
d D 8.10 93/07/20 19:51:42 eric 85 84
c updates for Convex, NEWS-OS 4.1C (Sony), and UNIOS-B 1.6 (Omron)
e
s 00003/00003/00401
d D 8.9 93/07/20 19:24:40 eric 84 83
c RISCOS and SGI fixes; fix error handling (caused error messages to
c be discarded in some circumstances)
e
s 00061/00016/00343
d D 8.8 93/07/20 15:35:44 eric 83 82
c more portability changes, including ConvexOS support
e
s 00021/00021/00338
d D 8.7 93/07/20 10:16:58 eric 82 81
c further compat changes for Solaris & other System-V derived systems
e
s 00012/00000/00347
d D 8.6 93/07/19 20:50:09 eric 81 80
c SGI IRIX & ANSI C portability
e
s 00054/00024/00293
d D 8.5 93/07/19 11:30:39 eric 80 79
c HASSETEUID => HASSETREUID and changes to avoid having to do
c setuid(getuid()) in main.
e
s 00011/00002/00306
d D 8.4 93/07/16 10:25:54 eric 79 78
c SCO unix changes; fix problem with defn of sys_errlist
e
s 00053/00017/00255
d D 8.3 93/07/13 12:58:23 eric 78 77
c many fixes.  primarily fix for seteuid problem in 8.2; also,
c Solaris compatibility fixes; timed out messages problems; messages
c silently discarded if checkcompat returned EX_TEMPFAIL
e
s 00021/00002/00251
d D 8.2 93/07/11 06:52:29 eric 77 76
c huge number of changes for 8.2, including IRIX & Solaris portability;
c improved error checking; fix -m flag and add -O flag in maps; fix long
c DNS timeouts; relax safefile restrictions; add -X command line flag; etc.
e
s 00002/00002/00251
d D 8.1 93/06/07 10:29:35 bostic 76 75
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00002/00247
d D 6.36 93/05/30 08:54:27 eric 75 74
c Solaris portability changes
e
s 00008/00001/00241
d D 6.35 93/05/28 16:43:15 eric 74 73
c tweak cdefs.h include
e
s 00014/00013/00228
d D 6.34 93/05/28 16:04:31 eric 73 72
c try to automate compile flag handling based on OS type
e
s 00001/00001/00240
d D 6.33 93/05/27 13:01:54 eric 72 71
c Solaris portability changes
e
s 00004/00003/00237
d D 6.32 93/05/22 10:15:21 eric 71 70
c IBM_AIX => _AIX3
e
s 00010/00004/00230
d D 6.31 93/05/22 08:57:57 eric 70 69
c AIX compatibility changes; clean up map initialization functions
e
s 00001/00001/00233
d D 6.30 93/05/20 15:40:14 eric 69 68
c compatibility for Sun BSD
e
s 00001/00000/00233
d D 6.29 93/05/17 10:28:07 eric 68 67
c first cut at merged map/alias implementation
e
s 00005/00000/00228
d D 6.28 93/05/04 12:24:55 eric 67 66
c make NIS set NIS_ALIASES and NIS_MAP
e
s 00001/00000/00227
d D 6.27 93/05/03 11:36:24 eric 66 65
c updates for new alias implementation
e
s 00001/00000/00226
d D 6.26 93/04/28 12:26:30 eric 65 64
c add hooks to allow unlocking
e
s 00001/00000/00225
d D 6.25 93/04/27 17:27:08 eric 64 63
c need sys/stat.h
e
s 00011/00000/00214
d D 6.24 93/04/27 17:24:31 eric 63 62
c move compatibility hooks for S_ISREG et al to conf.h
e
s 00002/00002/00212
d D 6.23 93/04/27 14:50:41 eric 62 61
c hpux => __hpux
e
s 00003/00003/00211
d D 6.22 93/04/26 19:59:41 eric 61 60
c up some of the values to be more generous
e
s 00004/00000/00210
d D 6.21 93/04/26 16:03:26 eric 60 59
c NeXT portability changes
e
s 00006/00001/00204
d D 6.20 93/04/26 15:57:50 eric 59 58
c add HASSETSID on #ifdef _POSIX_VERSION
e
s 00003/00005/00202
d D 6.19 93/04/16 09:46:34 eric 58 57
c don't double-#define SMTP and QUEUE
e
s 00008/00007/00199
d D 6.18 93/04/15 07:14:27 eric 57 56
c IDENT problem applies to HPUX as well as Ultrix
e
s 00014/00001/00192
d D 6.17 93/04/14 07:34:26 eric 56 55
c move IDENTPROTO #define into conf.h; default it off for ULTRIX
e
s 00001/00001/00192
d D 6.16 93/04/13 08:05:11 eric 55 54
c change comment on MAXUSERENVIRON to emphasize min value
e
s 00013/00005/00180
d D 6.15 93/04/10 09:25:47 eric 54 53
c clarify comments for the unwary
e
s 00012/00001/00173
d D 6.14 93/03/23 15:37:03 eric 53 52
c fix generalized socket code so that it doesn't screw up on older
c vendor's systems; put INET support on separate compilation flag
e
s 00010/00000/00164
d D 6.13 93/03/18 08:16:05 eric 52 51
c define TOBUFSIZE
e
s 00005/00000/00159
d D 6.12 93/03/17 10:46:20 eric 51 50
c flock requires sys/file.h
e
s 00007/00000/00152
d D 6.11 93/03/17 09:55:17 eric 50 49
c clean up file locking (create a lockfile() routine in conf.c)
e
s 00000/00001/00152
d D 6.10 93/02/23 14:45:22 eric 49 48
c delete trusted users code; it's too easy to circumvent
e
s 00016/00000/00137
d D 6.9 93/02/23 08:59:56 eric 48 47
c more System V compatibility changes (ugh)
e
s 00001/00000/00136
d D 6.8 93/02/21 07:42:42 eric 47 46
c add MAXIPADDR
e
s 00001/00000/00135
d D 6.7 93/02/15 10:24:21 eric 46 45
c increase size of prescan buffer
e
s 00004/00004/00131
d D 6.6 93/02/12 11:51:16 eric 45 44
c fix wildcard MX handling (option W no longer needed); fix
c process title when using cached connection; many minor fixes
e
s 00004/00000/00131
d D 6.5 93/01/28 09:41:07 eric 44 43
c System 5 compatibility
e
s 00005/00004/00126
d D 6.4 93/01/21 15:18:34 eric 43 42
c more environment problems; limit resource exhaustion; fix incorrect
c name in Connection timed out message; ANSI C fixes; log message sender on
c returned mail during queue run; count recipients properly; fix YP code;
c diagnose "message timed out" properly
e
s 00014/00000/00116
d D 6.3 93/01/20 13:21:52 eric 42 41
c fix problem with address delimitor inside quotes; define $k and $=k
c to be the name (from the uname call)
e
s 00000/00001/00116
d D 6.2 93/01/13 18:09:44 eric 41 40
c eliminate UserEnviron
e
s 00000/00000/00117
d D 6.1 92/12/21 16:08:20 eric 40 39
c Release 6
e
s 00004/00000/00113
d D 5.33 92/12/20 11:14:17 eric 39 38
c change random constants to be #defines
e
s 00008/00005/00105
d D 5.32 92/12/16 16:41:24 eric 38 37
c tweak some of the configurations to up some values
e
s 00000/00001/00110
d D 5.31 92/12/15 12:34:43 eric 37 36
c dynamically allocate header fields (and more....); miscellaneous
c cleanup (mostly comments)
e
s 00026/00000/00085
d D 5.30 92/11/16 17:52:15 eric 36 35
c make it use varargs/stdarg and vsprintf
e
s 00014/00007/00071
d D 5.29 92/11/15 16:10:52 eric 35 34
c finish support for generalized maps
e
s 00000/00000/00078
d D 5.28 92/11/14 11:34:12 eric 34 33
c (partially) ANSI-fy it
e
s 00004/00001/00074
d D 5.27 92/09/23 15:24:28 eric 33 32
c make USERDB dependent on NEWDB
e
s 00006/00003/00069
d D 5.26 92/07/20 08:02:58 eric 32 31
c portability changes
e
s 00001/00000/00071
d D 5.25 92/05/29 10:38:32 eric 31 30
c allow configuration of GECOS matching; do regular aliasing after
c a GECOS match
e
s 00003/00000/00068
d D 5.24 92/01/05 09:21:33 eric 30 29
c clean up #ifdef configuration to more cleanly match the modern age
e
s 00001/00000/00067
d D 5.23 92/01/04 15:33:00 eric 29 28
c allow limited 8-bit support; allow [TCP] as an alias for [IPC], even
c though it's wrong; restore t option for System V support; add L=_N_
c mailer option for line lengths; implement R mailer flag to get
c restricted port; misc cleanup
e
s 00008/00001/00059
d D 5.22 91/12/13 14:54:29 eric 28 27
c some System V hacks....
e
s 00001/00000/00059
d D 5.21 91/12/08 16:42:29 eric 27 26
c include LOCKF compilation variable
e
s 00003/00002/00056
d D 5.20 91/07/26 17:26:14 eric 26 25
c use new Berkeley DB routines for aliases
e
s 00001/00000/00057
d D 5.19 91/07/26 09:34:20 eric 25 24
c hooks for distributed user database system
e
s 00008/00009/00049
d D 5.18 91/07/25 11:12:05 eric 24 23
c some compatibility with SunOS for future work here at Berkeley;
c change NO_WILDCARD_MX compilation flag to configuration option "w".
e
s 00001/00011/00057
d D 5.17 90/06/01 19:00:50 bostic 23 22
c new copyright notice
e
s 00001/00001/00067
d D 5.16 90/04/18 12:03:32 bostic 22 21
c increase MAXFIELD to 4K; bug report 4.3BSD/usr.lib/153
e
s 00000/00001/00068
d D 5.15 89/01/01 17:16:57 bostic 21 20
c remove DEBUG
e
s 00000/00001/00069
d D 5.14 88/12/28 20:33:29 bostic 20 19
c WIZ vanishes
e
s 00010/00000/00060
d D 5.13 88/12/28 19:45:41 bostic 19 18
c add NO_WILDCARD_MX #define
e
s 00001/00000/00059
d D 5.12 88/09/20 22:15:36 eric 18 17
c add I option to insist on Internet domain server; add NAMED_BIND
c compile option to compile in named routines.
e
s 00011/00010/00048
d D 5.11 88/06/30 14:58:32 bostic 17 16
c install approved copyright notice
e
s 00000/00001/00058
d D 5.10 88/04/01 16:21:18 bostic 16 15
c always use flock when rebuilding alias file
e
s 00017/00012/00042
d D 5.9 88/03/13 19:51:42 bostic 15 14
c add Berkeley specific header
e
s 00001/00000/00053
d D 5.8 86/07/21 10:21:13 bloom 14 13
c add support for MX use of the name server
e
s 00001/00000/00052
d D 5.7 86/01/05 19:56:31 eric 13 12
m 
c cleanup for various compilation flags and reasonable organization
e
s 00012/00009/00040
d D 5.6 86/01/05 17:52:18 eric 12 11
m 
c add NDBM compilation flag
e
s 00001/00000/00048
d D 5.5 86/01/05 16:57:09 eric 11 10
m 
c define QUEUESIZE to be the maximum number of jobs considered during
c a single queue run
e
s 00001/00000/00047
d D 5.4 85/09/24 15:09:32 eric 10 9
m 
c don't step on user environment
e
s 00000/00000/00047
d D 5.3 85/09/19 01:25:13 eric 9 7
i 8
m 
c incorporate SMI changes -- still experimental
e
s 00003/00002/00044
d D 5.1.1.1 85/09/19 00:55:22 eric 8 6
m 
c SMI changes (somewhat)
e
s 00002/00002/00044
d D 5.2 85/09/03 20:08:50 eric 7 6
m 
c increase MAXNAME and MAXLINE, as requested by Rick Adams, via
c George Goble, via Kirk Smith, via Miriam Amos (why????)
e
s 00012/00002/00034
d D 5.1 85/06/07 16:10:52 dist 6 5
m 
c Add copyright
e
s 00001/00000/00035
d D 4.3 85/04/28 11:51:34 eric 5 4
m 
c add #define FLOCK 1
e
s 00001/00001/00034
d D 4.2 84/03/11 13:37:36 eric 4 3
m 
c fixes from Greg Satz <satz@sri-tsc.ARPA>, mostly for PDP's
e
s 00000/00000/00035
d D 4.1 83/07/25 19:43:26 eric 3 2
m 
c 4.2 release version
e
s 00001/00003/00034
d D 3.2 82/11/13 18:45:04 eric 2 1
m 070
c put OS info back into the Makefile; sendmail discretionary info goes into
c conf.h.
e
s 00037/00000/00000
d D 3.1 82/11/13 17:57:12 eric 1 0
m 021,
m 070
c date and time created 82/11/13 17:57:12 by eric
e
u
U
f b 
f i 
t
T
I 1
/*
I 17
D 229
 * Copyright (c) 1983 Eric P. Allman
E 229
I 229
 * Copyright (c) 1983, 1995 Eric P. Allman
E 229
E 17
D 2
**  CONF.H -- All user-configurable parameters
E 2
I 2
D 6
**  CONF.H -- All user-configurable parameters for sendmail
E 6
I 6
D 15
**  Sendmail
**  Copyright (c) 1983  Eric P. Allman
**  Berkeley, California
E 6
E 2
**
D 6
**	%W%	%Y%	%G%
E 6
I 6
**  Copyright (c) 1983 Regents of the University of California.
**  All rights reserved.  The Berkeley software License Agreement
**  specifies the terms and conditions for redistribution.
**
**	%W% (Berkeley) %G%
*/
E 15
I 15
D 76
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.
E 76
I 76
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 76
 *
D 23
 * Redistribution and use in source and binary forms are permitted
D 17
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 17
I 17
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
E 23
I 23
 * %sccs.include.redist.c%
E 23
E 17
 *
 *	%W% (Berkeley) %G%
D 17
 *
 *  Sendmail
 *  Copyright (c) 1983  Eric P. Allman
 *  Berkeley, California
 *
E 17
 */
E 15

/*
**  CONF.H -- All user-configurable parameters for sendmail
I 246
**
**	Send updates to sendmail@CS.Berkeley.EDU so they will be
**	included in the next release.
E 246
E 6
*/
D 15


E 15

I 240
struct rusage;	/* forward declaration to get gcc to shut up in wait.h */

E 240
I 39
# include <sys/param.h>
I 112
# include <sys/types.h>
E 112
I 64
# include <sys/stat.h>
I 104
# include <sys/file.h>
I 107
# include <sys/wait.h>
E 107
E 104
E 64
I 50
# include <fcntl.h>
I 92
# include <signal.h>
I 221
# include <netdb.h>
# include <pwd.h>
E 221
E 92
I 68
D 74
# include "cdefs.h"
E 74
E 68
E 50

E 39
D 80
/*
E 80
I 80
/**********************************************************************
E 80
**  Table sizes, etc....
**	There shouldn't be much need to change these....
D 80
*/
E 80
I 80
**********************************************************************/
E 80

D 4
# define MAXLINE	256		/* max line length */
E 4
I 4
D 7
# define MAXLINE	512		/* max line length */
E 4
# define MAXNAME	128		/* max length of a name */
E 7
I 7
D 61
# define MAXLINE	1024		/* max line length */
E 61
I 61
# define MAXLINE	2048		/* max line length */
E 61
# define MAXNAME	256		/* max length of a name */
E 7
D 22
# define MAXFIELD	2500		/* max total length of a hdr field */
E 22
I 22
D 37
# define MAXFIELD	4096		/* max total length of a hdr field */
E 37
E 22
# define MAXPV		40		/* max # of parms to mailers */
D 8
# define MAXHOP		30		/* max value of HopCount */
E 8
I 8
D 38
# define MAXHOP		17		/* max value of HopCount */
E 38
E 8
D 61
# define MAXATOM	100		/* max atoms per address */
E 61
I 61
# define MAXATOM	200		/* max atoms per address */
E 61
# define MAXMAILERS	25		/* maximum mailers known to system */
D 38
# define MAXRWSETS	30		/* max # of sets of rewriting rules */
E 38
I 38
D 212
# define MAXRWSETS	100		/* max # of sets of rewriting rules */
E 212
I 212
# define MAXRWSETS	200		/* max # of sets of rewriting rules */
E 212
E 38
# define MAXPRIORITIES	25		/* max values for Precedence: field */
D 49
# define MAXTRUST	30		/* maximum number of trusted users */
E 49
I 10
D 41
# define MAXUSERENVIRON	40		/* max # of items in user environ */
E 41
I 11
D 38
# define QUEUESIZE	600		/* max # of jobs per queue run */
I 14
# define MAXMXHOSTS	10		/* max # of MX records */
E 38
I 38
# define MAXMXHOSTS	20		/* max # of MX records */
E 38
I 29
# define SMTPLINELIM	990		/* maximum SMTP line length */
I 39
# define MAXKEY		128		/* maximum size of a database key */
# define MEMCHUNKSIZE	1024		/* chunk size for memory allocation */
I 43
D 55
# define MAXUSERENVIRON	100		/* max envariables saved */
E 55
I 55
# define MAXUSERENVIRON	100		/* max envars saved, must be >= 3 */
E 55
I 47
D 101
# define MAXIPADDR	16		/* max # of IP addrs for this host */
E 101
I 66
# define MAXALIASDB	12		/* max # of alias databases */
I 195
# define MAXMAPSTACK	12		/* max # of stacked or sequenced maps */
# define MAXTOCLASS	8		/* max # of message timeout classes */
I 217
D 218
# define MAXMIMENESTING	20		/* max depth of MIME nesting */
E 218
I 218
# define MAXMIMEARGS	20		/* max args in Content-Type: */
# define MAXMIMENESTING	20		/* max MIME multipart nesting */
I 252
# define QUEUESEGSIZE	1000		/* increment for queue size */
E 252
E 218
E 217
E 195
E 66
E 47
I 46
D 61
# define PSBUFSIZE	(MAXNAME * 4)	/* size of prescan buffer */
E 61
I 61
D 134
# define PSBUFSIZE	(MAXLINE + MAXATOM)	/* size of prescan buffer */
E 134
E 61
E 46
E 43
E 39
I 38

D 252
# ifndef QUEUESIZE
D 242
# define QUEUESIZE	1000		/* max # of jobs per queue run */
E 242
I 242
#  define QUEUESIZE	3000		/* max # of jobs per queue run */
E 252
I 252
D 253
# ifndef MAXQUEUESIZE
#  define MAXQUEUESIZE	40000		/* max # of jobs we will run at once */
E 252
E 242
# endif

E 253
E 38
I 30
D 70
# ifndef FORK
# define FORK		vfork		/* function to call to fork mailer */
# endif
E 30
E 29
E 14
E 11
E 10

E 70
D 80
/*
E 80
I 80
/**********************************************************************
E 80
**  Compilation options.
I 12
D 268
**
**	#define these if they are available; comment them out otherwise.
E 12
D 80
*/
E 80
I 80
**********************************************************************/
E 80

I 28
D 35
# ifdef hpux
# define SYSTEM5	1
# endif

E 35
E 28
D 12
#define DBM		1	/* use DBM library (requires -ldbm) */
#define DEBUG		1	/* enable debugging */
#define LOG		1	/* enable logging */
#define SMTP		1	/* enable user and server SMTP */
#define QUEUE		1	/* enable queueing */
#define UGLYUUCP	1	/* output ugly UUCP From lines */
D 8
#define DAEMON		1	/* include the daemon (requires IPC) */
E 8
I 8
#define DAEMON		1	/* include the daemon (requires IPC & SMTP) */
E 8
I 5
#define FLOCK		1	/* use flock file locking */
I 8
#define SETPROCTITLE	1	/* munge argv to display current status */
E 12
I 12
D 26
# define DBM		1	/* use DBM library (requires -ldbm) */
# define NDBM		1	/* new DBM library available (requires DBM) */
E 26
I 26
D 32
/* # define DBM		1	/* use DBM library (requires -ldbm) */
/* # define NDBM	1	/* new DBM library available (requires DBM) */
# define NEWDB		1	/* use new 4.4bsd database package db(3) */
E 32
E 26
D 21
# define DEBUG		1	/* enable debugging */
E 21
# define LOG		1	/* enable logging */
D 58
# define SMTP		1	/* enable user and server SMTP */
# define QUEUE		1	/* enable queueing */
E 58
# define UGLYUUCP	1	/* output ugly UUCP From lines */
I 120
# define NETUNIX	1	/* include unix domain support */
E 120
D 53
# define DAEMON		1	/* include the daemon (requires IPC & SMTP) */
E 53
I 53
# define NETINET	1	/* include internet support */
E 53
D 16
# define FLOCK		1	/* use flock file locking */
E 16
D 198
# define SETPROCTITLE	1	/* munge argv to display current status */
E 198
I 13
D 20
/* # define WIZ		1	/* allow wizard mode */
E 20
I 18
D 174
# define NAMED_BIND	1	/* use Berkeley Internet Domain Server */
E 174
I 25
D 33
# define USERDB		1	/* look in user database */
E 33
I 31
# define MATCHGECOS	1	/* match user names from gecos field */
I 77
# define XDEBUG		1	/* enable extended debugging */
E 77
I 33
D 174

E 174
D 226
# ifdef NEWDB
# define USERDB		1	/* look in user database (requires NEWDB) */
E 226
I 226
# if (defined(NEWDB) || defined(HESIOD)) && !defined(USERDB)
D 230
# define USERDB		1	/* look in user database */
E 230
I 230
#  define USERDB	1	/* look in user database */
E 230
E 226
I 174
# endif

/**********************************************************************
**  0/1 Compilation options.
E 268
**	#define these to 1 if they are available;
**	#define them to 0 otherwise.
I 268
**  All can be overridden from Makefile.
E 268
**********************************************************************/

I 268
# ifndef NETINET
#  define NETINET	1	/* include internet support */
# endif

E 268
# ifndef NAMED_BIND
#  define NAMED_BIND	1	/* use Berkeley Internet Domain Server */
I 230
# endif

I 268
# ifndef XDEBUG
#  define XDEBUG	1	/* enable extended debugging */
# endif

# ifndef MATCHGECOS
#  define MATCHGECOS	1	/* match user names from gecos field */
# endif

E 268
# ifndef DSN
#  define DSN		1	/* include delivery status notification code */
E 230
E 174
I 35
D 73
# define BTREE_MAP	1	/* enable BTREE mapping type (requires NEWDB) */
D 38
/*# define HASH_MAP	1	/* enable HASH mapping type (requires NEWDB) */
E 38
I 38
# define HASH_MAP	1	/* enable HASH mapping type (requires NEWDB) */
E 73
E 38
E 35
# endif
E 33
E 31
I 27
D 28
/* # define LOCKF	1	/* use System V lockf instead of flock */
E 28
I 28

I 268
# if !defined(USERDB) && (defined(NEWDB) || defined(HESIOD))
#  define USERDB	1	/* look in user database */
# endif

E 268
I 238
# ifndef MIME8TO7
#  define MIME8TO7	1	/* 8->7 bit MIME conversions */
# endif

# ifndef MIME7TO8
#  define MIME7TO8	1	/* 7->8 bit MIME conversions */
# endif

E 238
I 91
D 268
/*
D 141
**  Due to a "feature" in some operating systems such as Ultrix 4.3 and
**  HPUX 8.0, if you receive a "No route to host" message (ICMP message
**  ICMP_UNREACH_HOST) on _any_ connection, all connections to that host
**  are closed.  Some firewalls return this error if you try to connect
**  to the IDENT port (113), so you can't receive email from these hosts
**  on these systems.  The firewall really should use a more specific
**  message such as ICMP_UNREACH_PROTOCOL or _PORT or _NET_PROHIB.  This
**  will get #undefed below as needed.
*/

I 128
#ifndef IDENTPROTO
E 128
# define IDENTPROTO	1	/* use IDENT proto (RFC 1413) */
I 128
#endif
E 128

I 130
/*
E 141
**  Most systems have symbolic links today, so default them on.  You
**  can turn them off by #undef'ing this below.
*/
E 268
I 268
/**********************************************************************
**  "Hard" compilation options.
**	#define these if they are available; comment them out otherwise.
**  These cannot be overridden from the Makefile, and should really not
**  be turned off unless absolutely necessary.
**********************************************************************/
E 268

D 268
# define HASLSTAT	1	/* has lstat(2) call */
E 268
I 268
# define LOG			/* enable logging -- don't turn off */
E 268

I 131
D 268
/*
E 268
I 268
/**********************************************************************
**  End of site-specific configuration.
**********************************************************************/
/*
E 268
**  General "standard C" defines.
**
**	These may be undone later, to cope with systems that claim to
**	be Standard C but aren't.  Gcc is the biggest offender -- it
**	doesn't realize that the library is part of the language.
**
**	Life would be much easier if we could get rid of this sort
**	of bozo problems.
*/

#ifdef __STDC__
# define HASSETVBUF	1	/* we have setvbuf(3) in libc */
#endif
I 268

/*
**  Assume you have standard calls; can be #undefed below if necessary.
*/

# define HASLSTAT	1	/* has lstat(2) call */
E 268
D 246

E 131
E 130
E 91
I 67
D 73
# ifdef NIS
# define NIS_ALIASES	1	/* include NIS support for aliases */
# define NIS_MAP	1	/* include NIS mapping type */
# endif

E 67
I 35
# ifdef NDBM
# define DBM_MAP	1	/* enable DBM mapping type (requires NDBM) */
# endif

E 73
D 80
/*
E 80
I 80
/**********************************************************************
E 246
I 246
/**********************************************************************
E 246
E 80
D 54
**  Some general configuration -- you shouldn't have to touch these
E 54
I 54
**  Operating system configuration.
**
**	Unless you are porting to a new OS, you shouldn't have to
**	change these.
E 54
D 80
*/
E 80
I 80
**********************************************************************/
E 80

I 78
D 82
/* general "standard C" defines */
E 78
I 77
#ifdef __STDC__
# define HASSETVBUF	1	/* yes, we have setvbuf in libc */
#endif

I 78
/* general POSIX defines */
#ifdef _POSIX_VERSION
# define HASSETSID	1	/* has setsid(2) call */
#endif

E 82
D 246
/*
**  Per-Operating System defines
*/
E 246
D 268

E 268
I 100
D 246

E 246
E 100
E 78
E 77
I 71
D 80
/* HP-UX -- tested for 8.07 */
E 80
I 80
/*
D 151
**  HP-UX -- tested for 8.07
E 151
I 151
**  HP-UX -- tested for 8.07, 9.00, and 9.01.
I 232
**
**	If V4FS is defined, compile for HP-UX 10.0.
E 232
E 151
*/

E 80
E 71
D 62
# ifdef hpux
E 62
I 62
D 194
# ifdef __hpux
E 194
I 194
#ifdef __hpux
E 194
I 114
D 232
/* avoid m_flags conflict between db.h & sys/sysmacros.h on HP 300 */
# undef m_flags
E 232
I 232
		/* common definitions for HP-UX 9.x and 10.x */
# undef m_flags		/* conflict between db.h & sys/sysmacros.h on HP 300 */
E 232
E 114
E 62
D 78
# define SYSTEM5	1
E 78
I 78
# define SYSTEM5	1	/* include all the System V defines */
E 78
I 73
D 83
# define UNSETENV	1	/* need unsetenv(3) support */
E 83
I 77
D 78
# define seteuid	setuid
# define HASSETVBUF		/* we have setvbuf in libc (but not __STDC__) */
E 78
I 78
D 80
# define HASSETEUID	1	/* we have seteuid call */
# define seteuid(uid)	setresuid(-1, uid, -1)	
E 80
I 80
D 92
# define HASSETREUID	1	/* have setreuid(2) call */
E 92
I 92
# define HASINITGROUPS	1	/* has initgroups(3) call */
I 100
D 155
# define HASSTATFS	1	/* has the statfs(2) syscall */
E 155
E 100
D 242
# define HASSETREUID	1	/* has setreuid(2) call */
E 92
D 161
# define setreuid(r, e)		setresuid(r, e, -1)	
E 161
I 161
# define setreuid(r, e)		setresuid(r, e, -1)
E 242
I 242
# define USESETEUID	1	/* has useable seteuid(2) call */
# define seteuid(e)	setresuid(-1, e, -1)
I 246
# define IP_SRCROUTE	1	/* can check IP source routing */
E 246
E 242
E 161
I 83
D 210
# define LA_TYPE	LA_FLOAT
E 210
I 210
D 236
# define LA_TYPE	LA_SUBR
E 236
I 236
# define LA_TYPE	LA_HPUX
E 236
I 231
# define SPT_TYPE	SPT_PSTAT
E 231
E 210
I 155
# define SFS_TYPE	SFS_VFS	/* use <sys/vfs.h> statfs() implementation */
E 155
I 149
# define GIDSET_T	gid_t
E 149
D 232
# define _PATH_UNIX	"/hp-ux"
I 149
# ifndef _PATH_SENDMAILCF
#  define _PATH_SENDMAILCF	"/usr/lib/sendmail.cf"
# endif
E 149
I 91
D 103
# undef IDENTPROTO
E 103
I 103
D 141
# undef IDENTPROTO		/* TCP/IP implementation is broken */
E 141
I 141
# ifndef IDENTPROTO
#  define IDENTPROTO	0	/* TCP/IP implementation is broken */
E 141
E 103
E 91
E 83
E 80
D 82
# ifndef __STDC__
#  define HASSETVBUF	1	/* we have setvbuf in libc (but not __STDC__) */
E 82
E 78
E 77
E 73
# endif
E 232
I 153
# ifndef HASGETUSERSHELL
#  define HASGETUSERSHELL 0	/* getusershell(3) causes core dumps */
# endif
E 153
I 150
# define syslog		hard_syslog
I 153
D 254
# ifdef __STDC__
extern int	syslog(int, char *, ...);
# endif
E 254
I 254
D 255
extern void	hard_syslog __P((int, char *, ...));
E 255
I 255
# ifdef __STDC__
extern void	hard_syslog(int, char *, ...);
# endif
E 255
E 254
I 232

# ifdef V4FS
		/* HP-UX 10.x */
D 271
#  define _PATH_UNIX	"/stand/vmunix"
#  ifndef _PATH_SENDMAILCF
#   define _PATH_SENDMAILCF	"/etc/mail/sendmail.cf"
#  endif
E 271
I 271
#  define _PATH_UNIX		"/stand/vmunix"
#  define _PATH_VENDOR_CF	"/etc/mail/sendmail.cf"
E 271
#  ifndef _PATH_SENDMAILPID
#   define _PATH_SENDMAILPID	"/etc/mail/sendmail.pid"
#  endif
#  ifndef IDENTPROTO
#   define IDENTPROTO	1	/* TCP/IP implementation fixed in 10.0 */
#  endif

# else
		/* HP-UX 9.x */
D 271
#  define _PATH_UNIX	"/hp-ux"
#  ifndef _PATH_SENDMAILCF
#   define _PATH_SENDMAILCF	"/usr/lib/sendmail.cf"
#  endif
E 271
I 271
#  define _PATH_UNIX		"/hp-ux"
#  define _PATH_VENDOR_CF	"/usr/lib/sendmail.cf"
E 271
#  ifndef IDENTPROTO
#   define IDENTPROTO	0	/* TCP/IP implementation is broken */
#  endif
# endif

E 232
E 153
E 150
I 141
D 194
# endif
E 194
I 194
#endif
E 194
E 141
I 78
D 82
# endif
E 82
E 78

I 100

E 100
I 70
D 71
# ifdef IBM_AIX
E 71
I 71
D 80
/* IBM AIX 3.x -- actually tested for 3.2.3 */
E 80
I 80
/*
**  IBM AIX 3.x -- actually tested for 3.2.3
*/

E 80
D 194
# ifdef _AIX3
E 194
I 194
#ifdef _AIX3
I 260
# include <paths.h>
E 260
E 194
E 71
D 92
# define LOCKF		1	/* use System V lockf instead of flock */
E 92
I 92
# define HASINITGROUPS	1	/* has initgroups(3) call */
I 125
D 155
# define HASSTATFS	1	/* has the statfs(2) syscall */
E 155
# define HASUNAME	1	/* use System V uname(2) system call */
I 145
D 146
# define NEEDGETUSERSHELL 1	/* needs getusershell(3) implementation */
E 146
I 146
# define HASGETUSERSHELL 0	/* does not have getusershell(3) call */
I 241
D 246
# ifndef IP_SRCROUTE
#  define IP_SRCROUTE	0	/* Something is broken with getsockopt() */
# endif
E 246
I 246
# define IP_SRCROUTE	0	/* Something is broken with getsockopt() */
E 246
E 241
E 146
E 145
E 125
E 92
# define FORK		fork	/* no vfork primitive available */
I 240
# define GIDSET_T	gid_t
E 240
I 106
D 194
# undef  SETPROCTITLE		/* setproctitle confuses AIX */
E 194
I 155
# define SFS_TYPE	SFS_STATFS	/* use <sys/statfs.h> statfs() impl */
I 198
# define SPT_PADCHAR	'\0'	/* pad process title with nulls */
I 207
# define LA_TYPE	LA_INT
I 260
# define LA_AVENRUN	"avenrun"
E 260
E 207
E 198
E 155
E 106
I 73
D 83
# define UNSETENV	1	/* need unsetenv(3) support */
I 77
# define SYS5TZ		1	/* use System V style timezones */
E 83
E 77
E 73
D 194
# endif
E 194
I 194
#endif
E 194

I 100

E 100
I 77
D 80
/* Silicon Graphics IRIX */
E 80
I 80
/*
**  Silicon Graphics IRIX
**
D 84
**	I haven't tested this yet myself.
E 84
I 84
**	Compiles on 4.0.1.
I 201
**
D 220
**	Use IRIX64 instead of IRIX for 64-bit IRIX.
E 220
I 220
**	Use IRIX64 instead of IRIX for 64-bit IRIX (6.0).
**	Use IRIX5 instead of IRIX for IRIX 5.x.
E 220
**
**	IRIX64 changes from Mark R. Levinson <ml@cvdev.rochester.edu>.
I 220
**	IRIX5 changes from Kari E. Hurtta <Kari.Hurtta@fmi.fi>.
E 220
E 201
E 84
*/

I 201
D 220
#ifdef IRIX64
E 220
I 220
#if defined(IRIX64) || defined(IRIX5)
E 220
# define IRIX
#endif

E 201
E 80
D 194
# ifdef IRIX
E 194
I 194
#ifdef IRIX
E 194
I 114
D 180
# include <sys/sysmacros.h>
E 180
I 180
# define SYSTEM5	1	/* this is a System-V derived system */
E 180
E 114
I 84
D 92
# define HASSETREUID	1	/* have setreuid(2) call */
E 92
I 92
# define HASSETREUID	1	/* has setreuid(2) call */
# define HASINITGROUPS	1	/* has initgroups(3) call */
I 100
D 155
# define HASSTATFS	1	/* has the statfs(2) syscall */
E 155
I 145
D 146
# define NEEDGETUSERSHELL 1	/* needs getusershell(3) implementation */
E 146
I 146
# define HASGETUSERSHELL 0	/* does not have getusershell(3) call */
I 246
# define IP_SRCROUTE	1	/* can check IP source routing */
E 246
E 146
E 145
E 100
E 92
E 84
# define FORK		fork	/* no vfork primitive available */
I 110
D 208
# define WAITUNION	1	/* use "union wait" as wait argument type */
E 208
I 208
D 209
# ifndef IRIX6			/* IRIX 6.0 */
E 209
I 209
D 220
# ifndef IRIX64			/* IRIX 6.0 */
E 220
I 220
D 247
# if !defined(IRIX64) && !defined(IRIX5)
E 220
E 209
#  define WAITUNION	1	/* use "union wait" as wait argument type */
# endif
E 247
E 208
E 110
D 83
# define UNSETENV	1	/* need unsetenv(3) support */
E 83
D 96
# define setpgrp	BSDsetpgrp
E 96
I 96
# define setpgid	BSDsetpgrp
E 96
I 81
D 84
# define HASSETREUID	1	/* have setreuid(2) call */
E 84
# define GIDSET_T	gid_t
I 222
D 247
# define ARGV_T		const char **
E 247
E 222
I 155
# define SFS_TYPE	SFS_4ARGS	/* four argument statfs() call */
I 213
# define SFS_BAVAIL	f_bfree		/* alternate field name */
E 213
I 180
# define LA_TYPE	LA_INT
I 190
D 201
# define NAMELISTMASK	0x7fffffff	/* mask for nlist() values */
E 201
I 201
# ifdef IRIX64
#  define NAMELISTMASK	0x7fffffffffffffff	/* mask for nlist() values */
# else
#  define NAMELISTMASK	0x7fffffff		/* mask for nlist() values */
I 247
# endif
# if defined(IRIX64) || defined(IRIX5)
#  define ARGV_T	char *const *
I 262
#  define HASSETRLIMIT	1	/* has setrlimit(2) syscall */
E 262
# else
#  define ARGV_T	const char **
#  define WAITUNION	1	/* use "union wait" as wait argument type */
E 247
# endif
E 201
E 190
E 180
E 155
E 81
D 194
# endif
E 194
I 194
#endif
E 194

E 77
I 71
D 78
/* general System V defines */
E 71
E 70
E 35
# ifdef SYSTEM5
I 32
D 71

E 71
E 32
# define LOCKF		1	/* use System V lockf instead of flock */
I 32
# define SYS5TZ		1	/* use System V style timezones */
I 42
D 45
# define UNAME		1	/* use System V uname system call */
E 45
I 45
# define HASUNAME	1	/* use System V uname system call */
E 45
E 42
D 35

# define index		strchr
# define rindex		strrchr
E 35
D 71

E 71
I 56
# endif

E 78
I 78
D 80
/* various systems from Sun Microsystems */
E 80
I 80

/*
D 120
**  SunOS
E 120
I 120
**  SunOS and Solaris
**
**	Tested on SunOS 4.1.x (a.k.a. Solaris 1.1.x) and
D 242
**	Solaris 2.2 (a.k.a. SunOS 5.2).
E 242
I 242
**	Solaris 2.4 (a.k.a. SunOS 5.4).
E 242
E 120
*/

E 80
E 78
E 56
I 54
D 69
#ifdef sun
E 69
I 69
D 72
#if defined(sun) && !defined(BSD)
E 72
I 72
D 73
#if defined(sun) && !defined(BSD) && !defined(SOLARIS)
E 72
E 69
# include <vfork.h>
E 73
I 73
#if defined(sun) && !defined(BSD)
I 78

E 78
D 83
# define UNSETENV	1	/* need unsetenv(3) support */
E 83
I 83
D 155
# define LA_TYPE	LA_INT
E 155
I 88
D 92
# define HASSETREUID	1	/* have setreuid(2) call */
E 92
I 92
D 144
# define HASSETREUID	1	/* has setreuid(2) call */
E 144
# define HASINITGROUPS	1	/* has initgroups(3) call */
I 120
# define HASUNAME	1	/* use System V uname(2) system call */
I 145
D 146
# define NEEDGETUSERSHELL 0	/* libc has getusershell(3) */
E 146
I 146
# define HASGETUSERSHELL 1	/* DOES have getusershell(3) call in libc */
I 246
# define IP_SRCROUTE	1	/* can check IP source routing */
E 246
I 155
# define LA_TYPE	LA_INT
E 155
E 146
E 145
I 142
D 143
# define GIDSET_T	gid_t
E 143
E 142
E 120
E 92
E 88
E 83
D 75
# define HASSTATFS	1	/* has the statfs(2) syscall */
E 75

I 126
# ifdef SOLARIS_2_3
D 215
#  define SOLARIS
E 215
I 215
D 228
#  define SOLARIS		/* for back compat only -- use -DSOLARIS=203 */
E 228
I 228
#  define SOLARIS	203	/* for back compat only -- use -DSOLARIS=203 */
E 228
E 215
I 161
D 162
#  ifndef SYSLOG_BUFSIZE
#   define SYSLOG_BUFSIZE	1024	/* allow full size syslog buffer */
#  endif
E 162
E 161
# endif

E 126
D 75
# if !defined(SOLARIS)
E 75
I 75
# ifdef SOLARIS
I 78
D 80
			/* Solaris 2.x */
E 80
I 80
			/* Solaris 2.x (a.k.a. SunOS 5.x) */
E 80
E 78
D 82
#  define LOCKF		1	/* use System V lockf instead of flock */
D 78
#  define UNSETENV	1	/* need unsetenv(3) support */
E 78
#  define HASUSTAT	1	/* has the ustat(2) syscall */
I 78
#  define bcopy(s, d, l)	(memmove((d), (s), (l)))
#  define bzero(d, l)		(memset((d), '\0', (l)))
#  define bcmp(s, d, l)		(memcmp((s), (d), (l)))
E 82
I 82
D 144
#  define SYSTEM5	1	/* use System V definitions */
I 88
#  define setreuid(r, e)	seteuid(e)
E 144
I 144
D 148
			/* see also __svr4__ defines below */
E 148
I 148
#  ifndef __svr4__
#   define __svr4__		/* use all System V Releae 4 defines below */
#  endif
I 244
D 257
#  define BSD_COMP	1	/* get BSD ioctl calls */
E 257
E 244
E 148
E 144
I 115
D 120
#  include <sys/sysmacros.h>
E 120
E 115
E 88
E 82
#  include <sys/time.h>
I 95
D 122
#  define gethostbyname	__switch_gethostbyname	/* get working version */
#  define gethostbyaddr	__switch_gethostbyaddr	/* get working version */
E 122
I 122
D 215
#  define gethostbyname	solaris_gethostbyname	/* get working version */
#  define gethostbyaddr	solaris_gethostbyaddr	/* get working version */
E 215
I 143
#  define GIDSET_T	gid_t
E 143
E 122
E 95
I 83
D 144
#  define _PATH_UNIX	"/kernel/unix"
E 144
I 144
#  ifndef _PATH_UNIX
D 183
#   define _PATH_UNIX	"/kernel/unix"
E 183
I 183
D 271
#   define _PATH_UNIX	"/dev/ksyms"
E 271
I 271
#   define _PATH_UNIX		"/dev/ksyms"
E 271
E 183
#  endif
E 144
D 271
#  ifndef _PATH_SENDMAILCF
#   define _PATH_SENDMAILCF	"/etc/mail/sendmail.cf"
I 93
#  endif
E 271
I 271
#  define _PATH_VENDOR_CF	"/etc/mail/sendmail.cf"
E 271
D 99
#  ifndef _PATH_SENDMAILFC
#   define _PATH_SENDMAILFC	"/etc/mail/sendmail.fc"
#  endif
E 99
#  ifndef _PATH_SENDMAILPID
E 93
#   define _PATH_SENDMAILPID	"/etc/mail/sendmail.pid"
I 162
#  endif
I 234
#  ifndef _PATH_HOSTS
#   define _PATH_HOSTS		"/etc/inet/hosts"
#  endif
E 234
#  ifndef SYSLOG_BUFSIZE
#   define SYSLOG_BUFSIZE	1024	/* allow full size syslog buffer */
I 215
#  endif
D 223
#  if SOLARIS < 204
#   define gethostbyname	solaris_gethostbyname	/* get good version */
#   define gethostbyaddr	solaris_gethostbyaddr	/* get good version */
E 215
E 162
#  endif
E 223
E 83

E 78
# else
I 78
D 139
			/* SunOS 4.1.x */
E 139
I 139
			/* SunOS 4.0.3 or 4.1.x */
I 144
#  define HASSETREUID	1	/* has setreuid(2) call */
E 144
E 139
E 78
D 155
#  define HASSTATFS	1	/* has the statfs(2) syscall */
E 155
I 92
D 121
/* #  define HASFLOCK	1	/* has flock(2) call */
E 121
I 121
D 157
#  define HASFLOCK	1	/* has flock(2) call */
E 157
I 157
#  ifndef HASFLOCK
#   define HASFLOCK	1	/* has flock(2) call */
#  endif
E 157
I 155
#  define SFS_TYPE	SFS_VFS	/* use <sys/vfs.h> statfs() implementation */
E 155
E 121
E 92
I 78
D 80
#  define HASSETEUID	1	/* we have seteuid call */
E 80
I 80
D 88
#  define HASSETREUID	1	/* have setreuid(2) call */
E 88
E 80
E 78
E 75
#  include <vfork.h>
D 78
# endif
E 78

I 139
#  ifdef SUNOS403
			/* special tweaking for SunOS 4.0.3 */
#   include <malloc.h>
#   define SYS5SIGNALS	1	/* SysV signal semantics -- reset on each sig */
I 245
#   define NEEDSTRSTR	1	/* need emulation of strstr(3) routine */
E 245
#   define WAITUNION	1	/* use "union wait" as wait argument type */
#   undef WIFEXITED
#   undef WEXITSTATUS
#   undef HASUNAME
#   define setpgid	setpgrp
typedef int		pid_t;
extern char		*getenv();

I 175
#  else
			/* 4.1.x specifics */
#   define HASSETSID	1	/* has Posix setsid(2) call */
#   define HASSETVBUF	1	/* we have setvbuf(3) in libc */

E 175
#  endif
E 139
I 78
# endif
E 78
#endif

I 113
/*
D 120
** DG/UX 5.4.2
E 120
I 120
**  DG/UX
**
D 187
**	Tested on 5.4.2
E 187
I 187
**	Tested on 5.4.2 and 5.4.3.  Use DGUX_5_4_2 to get the
**	older support.
**	5.4.3 changes from Mark T. Robinson <mtr@ornl.gov>.
E 187
E 120
*/
E 113
I 100

I 187
#ifdef DGUX_5_4_2
# define DGUX		1
#endif

E 187
I 113
#ifdef	DGUX
# define SYSTEM5	1
D 236
# define LA_TYPE	LA_SUBR
E 236
I 236
# define LA_TYPE	LA_DGUX
E 236
D 155
# define HASSTATFS	1	/* has the statfs(2) syscall */
E 155
# define HASSETREUID	1	/* has setreuid(2) call */
# define HASUNAME	1	/* use System V uname(2) system call */
# define HASSETSID	1	/* has Posix setsid(2) call */
# define HASINITGROUPS	1	/* has initgroups(3) call */
I 272
# define IP_SRCROUTE	0	/* does not have <netinet/ip_var.h> */
E 272
I 164
# define HASGETUSERSHELL 0	/* does not have getusershell(3) */
E 164
D 131
# define HASSETVBUF	1	/* we have setvbuf(3) in libc */
E 131
D 141
# undef IDENTPROTO		/* TCP/IP implementation is broken */
E 141
I 141
# ifndef IDENTPROTO
#  define IDENTPROTO	0	/* TCP/IP implementation is broken */
# endif
E 141
D 198
# undef SETPROCTITLE
E 198
I 198
# define SPT_TYPE	SPT_NONE	/* don't use setproctitle */
E 198
I 155
# define SFS_TYPE	SFS_4ARGS	/* four argument statfs() call */
E 155
I 120

/* these include files must be included early on DG/UX */
# include <netinet/in.h>
# include <arpa/inet.h>
I 272

/* compiler doesn't understand const? */
# define const
E 272

E 120
D 187
# define inet_addr	dgux_inet_addr
E 187
I 187
# ifdef DGUX_5_4_2
#  define inet_addr	dgux_inet_addr
E 187
extern long	dgux_inet_addr();
I 187
# endif
E 187
#endif


E 113
E 100
I 78
D 80
/* Digital Ultrix 4.2A or 4.3 */
E 80
I 80
/*
**  Digital Ultrix 4.2A or 4.3
I 97
**
**	Apparently, fcntl locking is broken on 4.2A, in that locks are
**	not dropped when the process exits.  This causes major problems,
**	so flock is the only alternative.
E 97
*/

E 80
E 78
#ifdef ultrix
D 155
# define HASSTATFS	1	/* has the statfs(2) syscall */
E 155
I 78
D 80
# define HASSETEUID	1	/* we have seteuid call */
E 80
I 80
D 92
# define HASSETREUID	1	/* have setreuid(2) call */
E 92
I 92
# define HASSETREUID	1	/* has setreuid(2) call */
E 92
I 83
D 93
# define HASSETENV	1	/* has setenv(3) call */
E 93
# define HASUNSETENV	1	/* has unsetenv(3) call */
I 92
# define HASINITGROUPS	1	/* has initgroups(3) call */
I 169
# define HASUNAME	1	/* use System V uname(2) system call */
E 169
D 97
/* # define HASFLOCK	1	/* has flock(2) call */
E 97
I 97
D 157
# define HASFLOCK	1	/* has flock(2) call */
E 157
I 157
# ifndef HASFLOCK
#  define HASFLOCK	1	/* has flock(2) call */
# endif
E 157
I 145
D 146
# define NEEDGETUSERSHELL 1	/* needs getusershell(3) implementation */
E 146
I 146
# define HASGETUSERSHELL 0	/* does not have getusershell(3) call */
I 173
D 233
# define BROKEN_RES_SEARCH 1	/* res_search(unknown) returns h_errno=0 */
E 233
I 233
# ifndef BROKEN_RES_SEARCH
#  define BROKEN_RES_SEARCH 1	/* res_search(unknown) returns h_errno=0 */
# endif
E 233
E 173
E 146
E 145
E 97
E 92
D 140
# define LA_TYPE	LA_INT
# define LA_AVENRUN	"avenrun"
E 140
I 140
# ifdef vax
#  define LA_TYPE	LA_FLOAT
# else
#  define LA_TYPE	LA_INT
#  define LA_AVENRUN	"avenrun"
# endif
I 155
# define SFS_TYPE	SFS_MOUNT	/* use <sys/mount.h> statfs() impl */
E 155
E 140
I 91
D 103
# undef IDENTPROTO
E 103
I 103
D 141
# undef IDENTPROTO		/* TCP/IP implementation is broken */
E 141
I 141
# ifndef IDENTPROTO
D 233
#  define IDENTPROTO	0	/* TCP/IP implementation is broken */
E 233
I 233
#  define IDENTPROTO	0	/* pre-4.4 TCP/IP implementation is broken */
E 233
# endif
E 141
E 103
E 91
E 83
E 80
E 78
E 73
#endif

I 100

E 100
I 59
D 78
#ifdef _POSIX_VERSION
# define HASSETSID	1	/* has setsid(2) call */
E 78
I 78
D 80
/* OSF/1 (tested on Alpha) */
E 80
I 80
/*
I 275
**  OSF/1 for KSR.
**
**      Contributed by Todd C. Miller <Todd.Miller@cs.colorado.edu>
*/

#ifdef __ksr__
# define __osf__	1       /* get OSF/1 defines below */
# define FORK		fork    /* no vfork primitive available */
# define _PATH_VENDOR_CF	"/var/adm/sendmail/sendmail.cf"
# ifndef TZ_TYPE
#  define TZ_TYPE	TZ_TZNAME	/* use tzname[] vector */
# endif
#endif


/*
E 275
I 203
**  OSF/1 for Intel Paragon.
**
D 204
**	Contributed by Jeff A. Earickson <jeff@ithaca.ccs.ornl.gov>
**	of Oak Ridge National Lab.
E 204
I 204
**	Contributed by Jeff A. Earickson <jeff@ssd.intel.com>
**	of Intel Scalable Systems Divison.
E 204
*/

#ifdef __PARAGON__
# define __osf__	1	/* get OSF/1 defines below */
D 271
# ifndef _PATH_SENDMAILCF
#  define _PATH_SENDMAILCF	"/var/adm/sendmail/sendmail.cf"
# endif
E 271
I 271
# define _PATH_VENDOR_CF	"/var/adm/sendmail/sendmail.cf"
E 271
#endif


/*
E 203
**  OSF/1 (tested on Alpha)
*/

E 80
#ifdef __osf__
I 100
D 155
# define HASSTATFS	1	/* has the statfs(2) syscall */
E 155
E 100
I 83
D 93
# define HASSETENV	1	/* has setenv(3) call */
E 93
# define HASUNSETENV	1	/* has unsetenv(3) call */
E 83
D 80
# define HASSETEUID	1	/* we have seteuid call */
E 80
I 80
D 92
# define HASSETREUID	1	/* have setreuid(2) call */
E 92
I 92
D 242
# define HASSETREUID	1	/* has setreuid(2) call */
E 242
I 242
# define USESETEUID	1	/* has useable seteuid(2) call */
E 242
# define HASINITGROUPS	1	/* has initgroups(3) call */
I 246
# define IP_SRCROUTE	1	/* can check IP source routing */
E 246
D 121
/* # define HASFLOCK	1	/* has flock(2) call */
E 121
I 121
D 157
# define HASFLOCK	1	/* has flock(2) call */
E 157
I 157
D 168
# ifdef HASFLOCK
E 168
I 168
# ifndef HASFLOCK
E 168
#  define HASFLOCK	1	/* has flock(2) call */
# endif
E 157
E 121
E 92
E 80
D 83
# define seteuid(uid)	setreuid(-1, uid)
E 83
I 83
# define LA_TYPE	LA_INT
I 155
# define SFS_TYPE	SFS_MOUNT	/* use <sys/mount.h> statfs() impl */
E 155
I 120
# ifndef _PATH_SENDMAILPID
D 150
#  define _PATH_SENDMAILPID	"/var/run/sendmial.pid"
E 150
I 150
#  define _PATH_SENDMAILPID	"/var/run/sendmail.pid"
E 150
# endif
E 120
D 93
# define LA_AVENRUN	"avenrun"
E 93
E 83
E 78
#endif

I 100

E 100
I 78
D 80
/* NeXTstep */
E 80
I 80
/*
**  NeXTstep
*/

E 80
E 78
I 60
D 77
#ifdef NeXT
# define	sleep	sleepX
E 77
I 77
D 94
#ifdef __NeXT__
E 94
I 94
#ifdef NeXT
E 94
I 92
# define HASINITGROUPS	1	/* has initgroups(3) call */
I 250
D 251
# define NEEDPUTENV	1	/* need putenv(3) call */
E 251
I 251
# define NEEDPUTENV	2	/* need putenv(3) call; no setenv(3) call */
E 251
E 250
D 157
# define HASFLOCK	1	/* has flock(2) call */
E 157
I 157
# ifndef HASFLOCK
#  define HASFLOCK	1	/* has flock(2) call */
# endif
E 157
I 95
# define NEEDGETOPT	1	/* need a replacement for getopt(3) */
I 100
D 155
# define HASSTATFS	1	/* has the statfs(2) syscall */
E 155
I 111
# define WAITUNION	1	/* use "union wait" as wait argument type */
I 222
# define UID_T		int	/* compiler gripes on uid_t */
E 222
E 111
E 100
E 95
E 92
# define sleep		sleepX
I 96
# define setpgid	setpgrp
E 96
D 83
# define UNSETENV	1	/* need unsetenv(3) support */
E 83
I 83
D 98
# define LA_TYPE	LA_ZERO
E 98
I 98
# ifndef LA_TYPE
#  define LA_TYPE	LA_MACH
# endif
I 155
# define SFS_TYPE	SFS_VFS	/* use <sys/vfs.h> statfs() implementation */
E 155
I 107
# ifndef _POSIX_SOURCE
E 107
E 98
I 92
typedef int		pid_t;
I 107
#  undef WEXITSTATUS
#  undef WIFEXITED
# endif
E 107
I 93
D 271
# ifndef _PATH_SENDMAILCF
#  define _PATH_SENDMAILCF	"/etc/sendmail/sendmail.cf"
# endif
E 271
I 271
# define _PATH_VENDOR_CF	"/etc/sendmail/sendmail.cf"
E 271
D 99
# ifndef _PATH_SENDMAILFC
#  define _PATH_SENDMAILFC	"/etc/sendmail/sendmail.fc"
# endif
E 99
# ifndef _PATH_SENDMAILPID
#  define _PATH_SENDMAILPID	"/etc/sendmail/sendmail.pid"
# endif
E 93
E 92
E 83
E 77
#endif

I 100

E 100
I 78
D 80
/* various flavors of BSD */
E 80
I 80
/*
D 83
**  BSD
E 83
I 83
**  4.4 BSD
I 121
**
**	See also BSD defines.
E 121
E 83
*/

E 80
D 83
#ifdef BSD
# define HASGETDTABLESIZE 1	/* we have getdtablesize(2) call */
#endif

/* 4.4BSD */
E 83
E 78
I 74
D 266
#ifdef BSD4_4
E 266
I 266
#if defined(BSD4_4) && !defined(__bsdi__)
E 266
I 93
# define HASUNSETENV	1	/* has unsetenv(3) call */
I 242
# define USESETEUID	1	/* has useable seteuid(2) call */
E 242
I 100
D 155
# define HASSTATFS	1	/* has the statfs(2) syscall */
E 155
E 100
E 93
# include <sys/cdefs.h>
I 77
D 78
# ifndef _POSIX_SAVED_IDS
#  define _POSIX_SAVED_IDS	/* safe because we actually use seteuid */
# endif
E 78
I 78
D 80
# define HASSETEUID	1	/* we have seteuid(2) call */
E 80
I 80
D 83
# define HASSETREUID	1	/* have setreuid(2) call */
E 83
E 80
I 79
# define ERRLIST_PREDEFINED	/* don't declare sys_errlist */
I 239
# define BSD4_4_SOCKADDR	/* has sa_len */
I 240
D 269
# define NETLINK		/* supports AF_LINK */
E 269
I 269
# define NETLINK	1	/* supports AF_LINK */
E 269
E 240
E 239
I 93
# ifndef LA_TYPE
#  define LA_TYPE	LA_SUBR
# endif
I 155
# define SFS_TYPE	SFS_MOUNT	/* use <sys/mount.h> statfs() impl */
I 198
# define SPT_TYPE	SPT_PSSTRINGS	/* use PS_STRINGS pointer */
E 198
E 155
E 93
E 79
E 78
E 77
#endif
I 78

I 100

E 100
I 79
D 80
/* SCO Unix */
E 80
I 80
/*
I 161
**  BSD/386 (all versions)
**	From Tony Sanders, BSDI
*/

#ifdef __bsdi__
# define HASUNSETENV	1	/* has the unsetenv(3) call */
# define HASSETSID	1	/* has the setsid(2) POSIX syscall */
I 242
# define USESETEUID	1	/* has useable seteuid(2) call */
E 242
D 163
# define HASSTATFS	1	/* has the statfs(2) syscall */
E 163
I 163
D 182
# define SFS_TYPE	SFS_MOUNT	/* use <sys/mount.h> statfs() impl */
E 163
# if defined(_BSDI_VERSION) && _BSDI_VERSION >= 199312
#  define HASSETPROCTITLE 1	/* setproctitle is in libc */
D 175
# else
#  define SETPROCTITLE	1
E 175
I 175
#  undef SETPROCTITLE		/* so don't redefine it in conf.c */
E 175
# endif
E 182
# include <sys/cdefs.h>
# define ERRLIST_PREDEFINED	/* don't declare sys_errlist */
I 239
# define BSD4_4_SOCKADDR	/* has sa_len */
I 240
D 269
# define NETLINK		/* supports AF_LINK */
E 269
I 269
# define NETLINK	1	/* supports AF_LINK */
E 269
E 240
E 239
I 182
# define SFS_TYPE	SFS_MOUNT	/* use <sys/mount.h> statfs() impl */
E 182
# ifndef LA_TYPE
#  define LA_TYPE	LA_SUBR
# endif
I 225
# define GIDSET_T	gid_t
E 225
I 182
# if defined(_BSDI_VERSION) && _BSDI_VERSION >= 199312
			/* version 1.1 or later */
D 198
#  define HASSETPROCTITLE 1	/* setproctitle is in libc */
#  undef SETPROCTITLE		/* so don't redefine it in conf.c */
E 198
I 198
#  undef SPT_TYPE
#  define SPT_TYPE	SPT_BUILTIN	/* setproctitle is in libc */
E 198
# else
			/* version 1.0 or earlier */
#  ifndef OLD_NEWDB
#   define OLD_NEWDB	1	/* old version of newdb library */
#  endif
I 198
#  define SPT_PADCHAR	'\0'	/* pad process title with nulls */
E 198
# endif
E 182
#endif



/*
E 161
I 117
D 136
**  386BSD / FreeBSD 1.0E (works) / NetBSD (not tested)
E 136
I 136
D 261
**  386BSD / FreeBSD 1.0E / NetBSD (all architectures, all versions)
E 261
I 261
**  FreeBSD / NetBSD (all architectures, all versions)
E 261
E 136
**
D 261
**  4.3BSD clone, closer to 4.4BSD
E 261
I 261
**  4.3BSD clone, closer to 4.4BSD	for FreeBSD 1.x and NetBSD 0.9x
**  4.4BSD-Lite based			for FreeBSD 2.x and NetBSD 1.x
E 261
I 121
**
**	See also BSD defines.
E 121
*/

D 136
#ifdef __386BSD__
E 136
I 136
D 261
#if defined(__386BSD__) || defined(__FreeBSD__) || defined(__NetBSD__)
E 261
I 261
#if defined(__FreeBSD__) || defined(__NetBSD__)
E 261
E 136
# define HASUNSETENV	1	/* has unsetenv(3) call */
# define HASSETSID	1	/* has the setsid(2) POSIX syscall */
I 242
# define USESETEUID	1	/* has useable seteuid(2) call */
E 242
I 178
D 261
# ifdef __NetBSD__
#  define HASUNAME	1	/* has uname(2) syscall */
# endif
E 261
I 261
# define HASUNAME	1	/* has uname(2) syscall */
E 261
E 178
D 155
# define HASSTATFS	1	/* has the statfs(2) syscall */
E 155
# include <sys/cdefs.h>
# define ERRLIST_PREDEFINED	/* don't declare sys_errlist */
I 239
# define BSD4_4_SOCKADDR	/* has sa_len */
I 240
D 269
# define NETLINK		/* supports AF_LINK */
E 269
I 269
# define NETLINK	1	/* supports AF_LINK */
E 269
I 261
# define GIDSET_T	gid_t
E 261
E 240
E 239
# ifndef LA_TYPE
#  define LA_TYPE	LA_SUBR
# endif
I 155
# define SFS_TYPE	SFS_MOUNT	/* use <sys/mount.h> statfs() impl */
E 155
#endif


/*
I 120
**  Mach386
**
**	For mt Xinu's Mach386 system.
*/

#if defined(MACH) && defined(i386)
# define MACH386	1
# define HASUNSETENV	1	/* has unsetenv(3) call */
# define HASINITGROUPS	1	/* has initgroups(3) call */
D 157
# define HASFLOCK	1	/* has flock(2) call */
E 157
I 157
D 168
# ifdef HASFLOCK
E 168
I 168
# ifndef HASFLOCK
E 168
#  define HASFLOCK	1	/* has flock(2) call */
# endif
E 157
D 155
# define HASSTATFS	1	/* has the statfs(2) syscall */
E 155
# define NEEDGETOPT	1	/* need a replacement for getopt(3) */
# define NEEDSTRTOL	1	/* need the strtol() function */
# define setpgid	setpgrp
# ifndef LA_TYPE
#  define LA_TYPE	LA_FLOAT
# endif
I 155
# define SFS_TYPE	SFS_VFS	/* use <sys/vfs.h> statfs() implementation */
E 155
I 131
# undef HASSETVBUF		/* don't actually have setvbuf(3) */
E 131
# undef WEXITSTATUS
# undef WIFEXITED
D 271
# ifndef _PATH_SENDMAILCF
#  define _PATH_SENDMAILCF	"/usr/lib/sendmail.cf"
# endif
E 271
I 271
# define _PATH_VENDOR_CF	"/usr/lib/sendmail.cf"
E 271
# ifndef _PATH_SENDMAILPID
#  define _PATH_SENDMAILPID	"/etc/sendmail.pid"
# endif
#endif


/*
E 120
E 117
I 86
**  4.3 BSD -- this is for very old systems
**
I 159
**	Should work for mt Xinu MORE/BSD and Mips UMIPS-BSD 2.1.
**
E 159
**	You'll also have to install a new resolver library.
**	I don't guarantee that support for this environment is complete.
*/

D 159
#ifdef oldBSD43
E 159
I 159
#if defined(oldBSD43) || defined(MORE_BSD) || defined(umipsbsd)
E 159
# define NEEDVPRINTF	1	/* need a replacement for vprintf(3) */
# define NEEDGETOPT	1	/* need a replacement for getopt(3) */
I 87
# define ARBPTR_T	char *
I 96
# define setpgid	setpgrp
E 96
E 87
# ifndef LA_TYPE
#  define LA_TYPE	LA_FLOAT
# endif
D 271
# ifndef _PATH_SENDMAILCF
#  define _PATH_SENDMAILCF	"/usr/lib/sendmail.cf"
D 99
# endif
# ifndef _PATH_SENDMAILFC
#  define _PATH_SENDMAILFC	"/usr/lib/sendmail.fc"
E 99
# endif
E 271
I 271
# define _PATH_VENDOR_CF	"/usr/lib/sendmail.cf"
E 271
I 103
D 141
# undef IDENTPROTO		/* TCP/IP implementation is broken */
E 141
I 141
# ifndef IDENTPROTO
#  define IDENTPROTO	0	/* TCP/IP implementation is broken */
# endif
E 141
I 124
# undef WEXITSTATUS
# undef WIFEXITED
typedef short		pid_t;
extern int		errno;
E 124
E 103
#endif

I 100

E 100
/*
E 86
**  SCO Unix
I 138
**
**	This includes two parts -- the first is for SCO Open Server 3.2v4
**	(contributed by Philippe Brand <phb@colombo.telesys-innov.fr>).
**	The second is, I believe, for an older version.
E 138
*/
I 138

#ifdef _SCO_unix_4_2
# define _SCO_unix_
# define HASSETREUID	1	/* has setreuid(2) call */
I 179
# define NEEDFSYNC	1	/* needs the fsync(2) call stub */
E 179
D 271
# define _PATH_UNIX	"/unix"
# ifndef _PATH_SENDMAILCF
#  define _PATH_SENDMAILCF	"/usr/lib/sendmail.cf"
# endif
E 271
I 271
# define _PATH_UNIX		"/unix"
# define _PATH_VENDOR_CF	"/usr/lib/sendmail.cf"
E 271
# ifndef _PATH_SENDMAILPID
#  define _PATH_SENDMAILPID	"/etc/sendmail.pid"
# endif
#endif
E 138

E 80
#ifdef _SCO_unix_
# define SYSTEM5	1	/* include all the System V defines */
I 92
# define SYS5SIGNALS	1	/* SysV signal semantics -- reset on each sig */
E 92
I 89
D 155
# define HASSTATFS	1	/* has the statfs(2) syscall */
E 155
I 147
# define HASGETUSERSHELL 0	/* does not have getusershell(3) call */
E 147
E 89
D 83
# define UNSETENV	1	/* need unsetenv(3) support */
E 83
# define FORK		fork
# define MAXPATHLEN	PATHSIZE
I 83
D 113
# define LA_TYPE	LA_ZERO
E 113
I 113
# define LA_TYPE	LA_SHORT
I 155
D 199
# define SFS_TYPE	SFS_STATFS	/* use <sys/statfs.h> statfs() impl */
E 199
I 199
# define SFS_TYPE	SFS_4ARGS	/* use <sys/statfs.h> 4-arg impl */
I 213
# define SFS_BAVAIL	f_bfree		/* alternate field name */
E 213
E 199
I 192
D 193
# define TZ_TYPE	TZ_USE_TM_NAME	/* use tm->tm_name */
E 193
I 193
# define TZ_TYPE	TZ_TM_NAME	/* use tm->tm_name */
E 193
E 192
E 155
I 120
D 268
# undef NETUNIX			/* no unix domain socket support */
E 268
I 268
# define NETUNIX	0	/* no unix domain socket support */
E 268
E 120
E 113
E 83
#endif

I 100

E 100
I 83
/*
I 214
**  ISC (SunSoft) Unix.
**
**	Contributed by J.J. Bailey <jjb@jagware.bcc.com>
*/

#ifdef ISC_UNIX
# include <net/errno.h>
I 265
# include <sys/stream.h>	/* needed for IP_SRCROUTE */
# include <sys/bsdtypes.h>
E 265
# define SYSTEM5	1	/* include all the System V defines */
# define SYS5SIGNALS	1	/* SysV signal semantics -- reset on each sig */
# define HASGETUSERSHELL 0	/* does not have getusershell(3) call */
# define HASSETREUID	1	/* has setreuid(2) call */
# define NEEDFSYNC	1	/* needs the fsync(2) call stub */
D 268
# undef NETUNIX			/* no unix domain socket support */
E 268
I 268
# define NETUNIX	0	/* no unix domain socket support */
E 268
# define FORK		fork
# define MAXPATHLEN	1024
# define LA_TYPE	LA_SHORT
# define SFS_TYPE	SFS_STATFS	/* use <sys/statfs.h> statfs() impl */
# define SFS_BAVAIL	f_bfree		/* alternate field name */
D 271
# define _PATH_UNIX	"/unix"
# ifndef _PATH_SENDMAILCF
#  define _PATH_SENDMAILCF	"/usr/lib/sendmail.cf"
# endif
E 271
I 271
# define _PATH_UNIX		"/unix"
# define _PATH_VENDOR_CF	"/usr/lib/sendmail.cf"
E 271
# ifndef _PATH_SENDMAILPID
#  define _PATH_SENDMAILPID	"/etc/sendmail.pid"
# endif

D 276
typedef short		pid_t;

E 276
#endif


/*
E 214
I 202
**  Altos System V.
**	Contributed by Tim Rice <timr@crl.com>.
*/

#ifdef ALTOS_SYS_V
# include <limits.h>
# define SYSTEM5	1	/* include all the System V defines */
# define SYS5SIGNALS	1	/* SysV signal semantics -- reset on each sig */
# define HASGETUSERSHELL 0	/* does not have getusershell(3) call */
# define WAITUNION	1	/* use "union wait" as wait argument type */
# define NEEDFSYNC	1	/* no fsync(2) in system library */
# define FORK		fork
# define MAXPATHLEN	PATHSIZE
# define LA_TYPE	LA_SHORT
# define SFS_TYPE	SFS_STATFS	/* use <sys/statfs.h> statfs() impl */
I 213
# define SFS_BAVAIL	f_bfree		/* alternate field name */
E 213
# define TZ_TYPE	TZ_TM_NAME	/* use tm->tm_name */
D 268
# undef NETUNIX			/* no unix domain socket support */
E 268
I 268
# define NETUNIX	0	/* no unix domain socket support */
E 268
# undef WIFEXITED
# undef WEXITSTATUS
# define strtoul	strtol	/* gcc library bogosity */

typedef unsigned short	uid_t;
typedef unsigned short	gid_t;
typedef short		pid_t;
#endif


/*
E 202
**  ConvexOS 11.0 and later
I 159
**
**	"Todd C. Miller" <millert@mroe.cs.colorado.edu> claims this
**	works on 9.1 as well.
E 159
*/

#ifdef _CONVEX_SOURCE
D 88
# define SYSTEM5	1	/* include all the System V defines */
E 88
I 88
# define BSD		1	/* include all the BSD defines */
# define HASUNAME	1	/* use System V uname(2) system call */
D 92
# define LOCKF		1	/* use System V locking instead of flock */
E 92
E 88
D 155
# define HASSTATFS	1	/* has the statfs(2) syscall */
E 155
# define HASSETSID	1	/* has POSIX setsid(2) call */
D 92
# define HASINITGROUPS	1	/* has initgroups(2) call */
E 92
D 88
# define HASGETDTABLESIZE 1	/* we have getdtablesize(2) call */
# define HASSETREUID	1	/* have setreuid(2) call */
I 85
# define HASSETENV	1	/* has setenv(3) call */
E 88
I 88
# define NEEDGETOPT	1	/* need replacement for getopt(3) */
I 246
# define IP_SRCROUTE	0	/* Something is broken with getsockopt() */
E 246
E 88
E 85
# define LA_TYPE	LA_FLOAT
I 155
# define SFS_TYPE	SFS_VFS	/* use <sys/vfs.h> statfs() implementation */
I 159
D 271
# ifndef _PATH_SENDMAILCF
#  define _PATH_SENDMAILCF	"/usr/lib/sendmail.cf"
# endif
E 271
I 271
# define _PATH_VENDOR_CF	"/usr/lib/sendmail.cf"
E 271
# ifndef S_IREAD
#  define S_IREAD	_S_IREAD
#  define S_IWRITE	_S_IWRITE
#  define S_IEXEC	_S_IEXEC
#  define S_IFMT	_S_IFMT
#  define S_IFCHR	_S_IFCHR
#  define S_IFBLK	_S_IFBLK
# endif
E 159
E 155
I 91
D 141
# undef IDENTPROTO
E 141
I 141
# ifndef IDENTPROTO
#  define IDENTPROTO	0	/* TCP/IP implementation is broken */
# endif
I 241
D 246
# ifndef IP_SRCROUTE
#  define IP_SRCROUTE	0	/* Something is broken with getsockopt() */
# endif
E 246
E 241
E 141
E 91
#endif

I 100

E 100
/*
D 133
**  RISC/os 4.51
E 133
I 133
**  RISC/os 4.52
E 133
**
D 133
**	Untested...
E 133
I 133
**	Gives a ton of warning messages, but otherwise compiles.
E 133
*/

D 84
#if defined(mips) && !defined(ultrix)
E 84
I 84
#ifdef RISCOS
I 133

E 133
E 84
D 93
# define HASSETENV	1	/* has setenv(3) call */
E 93
# define HASUNSETENV	1	/* has unsetenv(3) call */
I 92
D 121
/* # define HASFLOCK	1	/* has flock(2) call */
E 121
I 121
D 157
# define HASFLOCK	1	/* has flock(2) call */
E 157
I 157
D 168
# ifdef HASFLOCK
E 168
I 168
# ifndef HASFLOCK
E 168
#  define HASFLOCK	1	/* has flock(2) call */
# endif
E 157
I 133
# define WAITUNION	1	/* use "union wait" as wait argument type */
# define NEEDGETOPT	1	/* need a replacement for getopt(3) */
E 133
E 121
E 92
# define LA_TYPE	LA_INT
# define LA_AVENRUN	"avenrun"
# define _PATH_UNIX	"/unix"
I 133
# undef WIFEXITED

# define setpgid	setpgrp

extern int		errno;
typedef int		pid_t;
#define			SIGFUNC_DEFINED
typedef int		(*sigfunc_t)();
extern char		*getenv();
extern void		*malloc();

E 133
#endif
I 100

E 100
I 96

/*
**  Linux 0.99pl10 and above...
D 170
**	From Karl London <karl@borg.demon.co.uk>.
E 170
I 170
D 171
**	From Karl London <karl@borg.demon.co.uk> and John Kennedy
**	<warlock@csuchico.edu>.  Conversion for "native (non-BSD)
**	mode" from Florian La Roche <rzsfl@rzluxt.rz.uni-sb.de>.
E 171
I 171
**
**  Thanks to, in reverse order of contact:
**
I 200
D 205
**	Andrew Pam <avatar@aus.xanadu.com>
E 205
E 200
**	John Kennedy <warlock@csuchico.edu>
I 205
**	Andrew Pam <avatar@aus.xanadu.com>
E 205
**	Florian La Roche <rzsfl@rz.uni-sb.de>
**	Karl London <karl@borg.demon.co.uk>
**
D 205
**  Last compiled against:	[03/02/94 @ 05:34 PM (Wednesday)]
**	sendmail 8.6.6.b9	named 4.9.2-931205-p1	db-1.73
**	gcc 2.5.8		libc.so.4.5.19
**	slackware 1.1.2		linux 0.99.15
E 205
I 205
D 249
**  Last compiled against:	[12/14/94 @ 11:38:41 PM (Wednesday)]
**	sendmail 8.7.a.5	named 4.9.3-beta12-p1	db-1.85
**	gcc 2.6.2		libc.so.4.6.20
**	slackware 2.1.0		linux 1.1.70
E 249
I 249
**  Last compiled against:	[05/25/95 @ 11:39:31 AM (Thursday)]
**	sendmail 8.7.b.0	named 4.9.3-beta17	db-1.85
**	gcc 2.6.4-950518	libc-5.0.9		linux 1.2.8
E 249
E 205
E 171
E 170
*/

D 119
#ifdef linux
E 119
I 119
#ifdef __linux__
E 119
D 170
# define BSD		1	/* pretend to be BSD based today */
I 157
D 158
# ifndef HASFLOCK
#  define HASFLOCK	0	/* don't have a functioning flock(2) */
# endif
E 158
E 157
# undef  NEEDVPRINTF	1	/* need a replacement for vprintf(3) */
E 170
I 170
# define BSD		1	/* include BSD defines */
E 170
# define NEEDGETOPT	1	/* need a replacement for getopt(3) */
I 170
# define HASUNAME	1	/* use System V uname(2) system call */
E 170
I 104
# define HASUNSETENV	1	/* has unsetenv(3) call */
I 170
# define ERRLIST_PREDEFINED	/* don't declare sys_errlist */
D 171
# define GIDSET_T	gid_t
# define sleep		sleepXX
E 171
I 171
# define GIDSET_T	gid_t	/* from <linux/types.h> */
I 200
# define HASGETUSERSHELL 0	/* getusershell(3) broken in Slackware 2.0 */
I 249
# define IP_SRCROUTE	0	/* linux <= 1.2.8 doesn't support IP_OPTIONS */
E 249
I 219
# ifndef HASFLOCK
#  define HASFLOCK	0	/* flock(2) is broken after 0.99.13 */
# endif
E 219
E 200
E 171
E 170
E 104
# ifndef LA_TYPE
D 171
#  define LA_TYPE	LA_FLOAT
E 171
I 171
D 172
#  define LA_TYPE	LA_PROC
E 172
I 172
#  define LA_TYPE	LA_PROCSTR
E 172
E 171
# endif
I 170
D 171
# define SFS_TYPE	SFS_MOUNT	/* use <sys/mount.h> statfs() impl */
# include <linux/fs.h>
E 171
I 171
# define SFS_TYPE	SFS_VFS		/* use <sys/vfs.h> statfs() impl */
I 205
# ifndef _PATH_SENDMAILPID
#  define _PATH_SENDMAILPID	"/var/run/sendmail.pid"
# endif
# define TZ_TYPE	TZ_TNAME
E 205
E 171
E 170
I 118
# include <sys/sysmacros.h>
I 135
D 170
# define GIDSET_T	gid_t
E 170
I 170
D 171
# undef atol
E 171
I 171
# undef atol			/* wounded in <stdlib.h> */
E 171
E 170
E 135
E 118
#endif

E 96

I 102
/*
**  DELL SVR4 Issue 2.2, and others
**	From Kimmo Suominen <kim@grendel.lut.fi>
**
**	It's on #ifdef DELL_SVR4 because Solaris also gets __svr4__
**	defined, and the definitions conflict.
I 127
**
**	Peter Wemm <peter@perth.DIALix.oz.au> claims that the setreuid
**	trick works on DELL 2.2 (SVR4.0/386 version 4.0) and ESIX 4.0.3A
**	(SVR4.0/386 version 3.0).
E 127
*/

#ifdef DELL_SVR4
D 144
# define SYSTEM5	1
D 127
/* # define setreuid(r, e)	seteuid(e) */
E 127
I 127
# define HASSETREUID	1	/* has seteuid(2) call & working saved uids */
# define setreuid(r, e)	seteuid(e)
E 127
/* # include <sys/time.h> */
# define _PATH_UNIX	"/unix"
# ifndef _PATH_SENDMAILCF
#  define _PATH_SENDMAILCF	"/usr/ucblib/sendmail.cf"
# endif
# ifndef _PATH_SENDMAILPID
#  define _PATH_SENDMAILPID	"/usr/ucblib/sendmail.pid"
I 139
# endif
# ifndef SYSLOG_BUFSIZE
#  define SYSLOG_BUFSIZE	128
E 139
# endif
E 144
I 144
				/* no changes necessary */
				/* see general __svr4__ defines below */
E 144
#endif


I 104
/*
**  Apple A/UX 3.0
*/
E 104

I 104
#ifdef _AUX_SOURCE
I 116
# include <sys/sysmacros.h>
E 116
# define BSD			/* has BSD routines */
I 270
# define HASSETRLIMIT	0	/* ... but not setrlimit(2) */
E 270
I 227
# define BROKEN_RES_SEARCH 1	/* res_search(unknown) returns h_errno=0 */
E 227
D 155
# define HASSTATFS	1	/* has the statfs(2) syscall */
E 155
# define HASUNAME	1	/* use System V uname(2) system call */
D 155
# define HASUSTAT	1	/* use System V ustat(2) syscall */
E 155
# define HASSETVBUF	1	/* we have setvbuf(3) in libc */
I 109
# define SIGFUNC_DEFINED	/* sigfunc_t already defined */
I 113
D 141
# undef IDENTPROTO		/* TCP/IP implementation is broken */
E 141
I 141
# ifndef IDENTPROTO
#  define IDENTPROTO	0	/* TCP/IP implementation is broken */
# endif
E 141
E 113
E 109
# define FORK		fork
D 271
# ifndef _PATH_SENDMAILCF
#  define _PATH_SENDMAILCF	"/usr/lib/sendmail.cf"
# endif
E 271
# ifndef LA_TYPE
D 270
#  define LA_TYPE	LA_ZERO
E 270
I 270
#  define LA_TYPE	LA_INT
#  define FSHIFT	16
E 270
# endif
I 270
# define LA_AVENRUN	"avenrun"
E 270
I 155
# define SFS_TYPE	SFS_VFS	/* use <sys/vfs.h> statfs() implementation */
I 270
# define TZ_TYPE	TZ_TZNAME
# ifndef _PATH_UNIX
D 271
#  define _PATH_UNIX	"/unix"		/* should be in <paths.h> */
E 271
I 271
#  define _PATH_UNIX		"/unix"		/* should be in <paths.h> */
E 271
# endif
I 271
# define _PATH_VENDOR_CF	"/usr/lib/sendmail.cf"
E 271
E 270
E 155
I 108
# undef WIFEXITED
# undef WEXITSTATUS
E 108
#endif


I 112
/*
**  Encore UMAX V
**
**	Not extensively tested.
*/
E 112

I 112
#ifdef UMAXV
# include <limits.h>
# define HASUNAME	1	/* use System V uname(2) system call */
D 155
# define HASSTATFS	1	/* has the statfs(2) syscall */
E 155
# define HASSETVBUF	1	/* we have setvbuf(3) in libc */
# define HASINITGROUPS	1	/* has initgroups(3) call */
I 145
D 146
# define NEEDGETUSERSHELL 1	/* needs getusershell(3) implementation ??? */
E 146
I 146
# define HASGETUSERSHELL 0	/* does not have getusershell(3) call */
E 146
E 145
# define SYS5SIGNALS	1	/* SysV signal semantics -- reset on each sig */
# define SYS5SETPGRP	1	/* use System V setpgrp(2) syscall */
# define FORK		fork	/* no vfork(2) primitive available */
I 155
# define SFS_TYPE	SFS_4ARGS	/* four argument statfs() call */
E 155
# define MAXPATHLEN	PATH_MAX
extern struct passwd	*getpwent(), *getpwnam(), *getpwuid();
extern struct group	*getgrent(), *getgrnam(), *getgrgid();
# undef WIFEXITED
# undef WEXITSTATUS
#endif


I 129
/*
**  Stardent Titan 3000 running TitanOS 4.2.
**
**	Must be compiled in "cc -43" mode.
**
D 130
**	From Kate HedStrom <kate@ahab.rutgers.edu>.
E 130
I 130
**	From Kate Hedstrom <kate@ahab.rutgers.edu>.
E 130
**
**	Note the tweaking below after the BSD defines are set.
*/
E 129

I 129
#ifdef titan
# define setpgid	setpgrp
typedef int		pid_t;
# undef WIFEXITED
# undef WEXITSTATUS
#endif


I 131
/*
**  Sequent DYNIX 3.2.0
**
**	From Jim Davis <jdavis@cs.arizona.edu>.
*/
E 131

I 131
#ifdef sequent
I 165

E 165
# define BSD		1
# define HASUNSETENV	1
# define BSD4_3		1	/* to get signal() in conf.c */
# define WAITUNION	1
# define LA_TYPE	LA_FLOAT
# ifdef	_POSIX_VERSION
#  undef _POSIX_VERSION		/* set in <unistd.h> */
# endif
# undef HASSETVBUF		/* don't actually have setvbuf(3) */
# define setpgid	setpgrp

/* Have to redefine WIFEXITED to take an int, to work with waitfor() */
# undef	WIFEXITED
# define WIFEXITED(s)	(((union wait*)&(s))->w_stopval != WSTOPPED && \
			 ((union wait*)&(s))->w_termsig == 0)
# define WEXITSTATUS(s)	(((union wait*)&(s))->w_retcode)
typedef int		pid_t;
# define isgraph(c)	(isprint(c) && (c != ' '))

I 167
# ifndef IDENTPROTO
#  define IDENTPROTO	0	/* TCP/IP implementation is broken */
# endif

E 167
# ifndef _PATH_UNIX
D 271
#  define _PATH_UNIX	"/dynix"
E 271
I 271
#  define _PATH_UNIX		"/dynix"
E 271
# endif
D 271
# ifndef _PATH_SENDMAILCF
#  define _PATH_SENDMAILCF	"/usr/lib/sendmail.cf"
# endif
E 271
I 271
# define _PATH_VENDOR_CF	"/usr/lib/sendmail.cf"
E 271

I 165
#endif


/*
**  Sequent DYNIX/ptx v2.0 (and higher)
**
**	For DYNIX/ptx v1.x, undefine HASSETREUID.
**
**	From Tim Wright <timw@sequent.com>.
*/

#ifdef _SEQUENT_
# define SYSTEM5	1	/* include all the System V defines */
# define HASSETSID	1	/* has POSIX setsid(2) call */
# define HASINITGROUPS	1	/* has initgroups(3) call */
# define HASSETREUID	1	/* has setreuid(2) call */
# define HASGETUSERSHELL 0	/* does not have getusershell(3) call */
# define GIDSET_T	gid_t
# define LA_TYPE	LA_INT
# define SFS_TYPE	SFS_STATFS	/* use <sys/statfs.h> statfs() impl */
D 198
# undef SETPROCTITLE
E 198
I 198
# define SPT_TYPE	SPT_NONE	/* don't use setproctitle */
E 198
I 167
# ifndef IDENTPROTO
#  define IDENTPROTO	0	/* TCP/IP implementation is broken */
# endif
E 167
D 271
# ifndef _PATH_SENDMAILCF
#  define _PATH_SENDMAILCF	"/usr/lib/sendmail.cf"
# endif
E 271
I 271
# define _PATH_VENDOR_CF	"/usr/lib/sendmail.cf"
E 271
# ifndef _PATH_SENDMAILPID
#  define _PATH_SENDMAILPID	"/etc/sendmail.pid"
# endif
E 165
#endif


I 154
/*
**  Cray Unicos
**
**	Ported by David L. Kensiski, Sterling Sofware <kensiski@nas.nasa.gov>
*/

#ifdef UNICOS
# define SYSTEM5	1	/* include all the System V defines */
# define SYS5SIGNALS	1	/* SysV signal semantics -- reset on each sig */
D 155
# define HASSTATFS	1	/* has the statfs(2) syscall */
E 155
# define MAXPATHLEN	PATHSIZE
# define LA_TYPE	LA_ZERO
I 155
# define SFS_TYPE	SFS_4ARGS	/* four argument statfs() call */
I 213
# define SFS_BAVAIL	f_bfree		/* alternate field name */
E 213
E 155
#endif

E 154

I 156
/*
**  Apollo DomainOS
**
**  From Todd Martin <tmartint@tus.ssi1.com> & Don Lewis <gdonl@gv.ssi1.com>
D 161
** 
E 161
I 161
**
E 161
**  15 Jan 1994
**
*/

#ifdef apollo
D 163
# define HASSTATFS	1	/* has the statfs(2) syscall */
E 163
# define HASSETREUID	1	/* has setreuid(2) call */
# define HASINITGROUPS	1	/* has initgroups(2) call */
D 198
# undef  SETPROCTITLE
E 198
I 198
# define SPT_TYPE	SPT_NONE	/* don't use setproctitle */
E 198
# define LA_TYPE	LA_SUBR		/* use getloadavg.c */
D 163
# define SFS_TYPE	SFS_MOUNT
E 163
I 163
D 166
# define SFS_TYPE	SFS_MOUNT	/* use <sys/mount.h> statfs() impl */
E 166
I 166
# define SFS_TYPE	SFS_4ARGS	/* four argument statfs() call */
I 213
# define SFS_BAVAIL	f_bfree		/* alternate field name */
E 213
E 166
E 163
D 271
# ifndef _PATH_SENDMAILCF
#  define _PATH_SENDMAILCF	"/usr/lib/sendmail.cf"
# endif
E 271
I 271
# define _PATH_VENDOR_CF	"/usr/lib/sendmail.cf"
E 271
# ifndef _PATH_SENDMAILPID
#  define _PATH_SENDMAILPID	"/etc/sendmail.pid"
# endif
# undef  S_IFSOCK		/* S_IFSOCK and S_IFIFO are the same */
# undef  S_IFIFO
# define S_IFIFO	0010000
# ifndef IDENTPROTO
#  define IDENTPROTO	0	/* TCP/IP implementation is broken */
# endif
D 161
#endif 
E 161
I 161
#endif
E 161


I 176
/*
I 177
D 197
**  UnixWare
E 197
I 197
**  UnixWare 1.1.2.
E 197
**
I 258
**	Updated by Petr Lampa <lampa@fee.vutbr.cz>.
E 258
**	From Evan Champion <evanc@spatial.synapse.org>.
*/

#ifdef UNIXWARE
I 264
# include <sys/mkdev.h>
E 264
# define SYSTEM5		1
D 197
# ifndef HASGETUSERSHELL
#  define HASGETUSERSHELL 0	/* does not have getusershell(3) call */
# endif
# define GIDSET_T		int
# define SLEEP_T		int
E 197
I 197
# define HASGETUSERSHELL	0	/* does not have getusershell(3) call */
D 258
# define HASGETDTABLESIZE	1
E 258
# define HASSETREUID		1
# define HASSETSID		1
# define HASINITGROUPS		1
# define GIDSET_T		gid_t
# define SLEEP_T		unsigned
E 197
# define SFS_TYPE		SFS_STATVFS
# define LA_TYPE		LA_ZERO
# undef WIFEXITED
# undef WEXITSTATUS
# define _PATH_UNIX		"/unix"
D 271
# ifndef _PATH_SENDMAILCF
#  define _PATH_SENDMAILCF	"/usr/ucblib/sendmail.cf"
# endif
E 271
I 271
# define _PATH_VENDOR_CF	"/usr/ucblib/sendmail.cf"
E 271
# ifndef _PATH_SENDMAILPID
#  define _PATH_SENDMAILPID	"/usr/ucblib/sendmail.pid"
# endif
# define SYSLOG_BUFSIZE	128
#endif


/*
E 177
**  Intergraph CLIX 3.1
**
**	From Paul Southworth <pauls@locust.cic.net>
*/

#ifdef CLIX
# define SYSTEM5	1	/* looks like System V */
I 177
# ifndef HASGETUSERSHELL
#  define HASGETUSERSHELL 0	/* does not have getusershell(3) call */
# endif
E 177
# define DEV_BSIZE	512	/* device block size not defined */
# define GIDSET_T	gid_t
# undef LOG			/* syslog not available */
# define NEEDFSYNC	1	/* no fsync in system library */
# define GETSHORT	_getshort
#endif


I 181
/*
**  NCR 3000 Series (SysVr4)
**
D 189
**	From From: Kevin Darcy <kevin@tech.mis.cfc.com>.
E 189
I 189
**	From Kevin Darcy <kevin@tech.mis.cfc.com>.
E 189
*/

#ifdef NCR3000
I 256
# include <sys/sockio.h>
E 256
# define __svr4__
I 246
# define IP_SRCROUTE	0	/* Something is broken with getsockopt() */
E 246
# undef BSD
# define LA_AVENRUN	"avenrun"
#endif
D 189
 
E 189


I 189
/*
**  Tandem NonStop-UX SVR4
**
**	From Rick McCarty <mccarty@mpd.tandem.com>.
*/
E 189
E 181
E 176

I 189
#ifdef NonStop_UX_BXX
# define __svr4__
#endif
E 189
E 156

I 189

I 191
/*
**  Hitachi 3050R & 3050RX Workstations running HI-UX/WE2.
**
**	Tested for 1.04 and 1.03
**	From Akihiro Hashimoto ("Hash") <hash@dominic.ipc.chiba-u.ac.jp>.
*/

#ifdef __H3050R
# define SYSTEM5	1	/* include all the System V defines */
# define HASINITGROUPS	1	/* has initgroups(3) call */
# define setreuid(r, e)	setresuid(r, e, -1)
# define LA_TYPE	LA_FLOAT
# define SFS_TYPE	SFS_VFS	/* use <sys/vfs.h> statfs() implementation */
# define HASSETVBUF	/* HI-UX has no setlinebuf */
# ifndef GIDSET_T
#  define GIDSET_T	gid_t
# endif
# ifndef _PATH_UNIX
D 271
#  define _PATH_UNIX	"/HI-UX"
E 271
I 271
#  define _PATH_UNIX		"/HI-UX"
E 271
# endif
D 271
# ifndef _PATH_SENDMAILCF
#  define _PATH_SENDMAILCF	"/usr/lib/sendmail.cf"
# endif
E 271
I 271
# define _PATH_VENDOR_CF	"/usr/lib/sendmail.cf"
E 271
# ifndef IDENTPROTO
#  define IDENTPROTO	0	/* TCP/IP implementation is broken */
# endif
# ifndef HASGETUSERSHELL
#  define HASGETUSERSHELL 0	/* getusershell(3) causes core dumps */
# endif

/* avoid m_flags conflict between db.h & sys/sysmacros.h on HIUX 3050 */
# undef m_flags

# ifdef __STDC__
extern int	syslog(int, char *, ...);
# endif

#endif


I 206
/*
**  Amdahl UTS System V 2.1.5 (SVr3-based)
**
**    From: Janet Jackson <janet@dialix.oz.au>.
*/
E 206
E 191

I 206
#ifdef _UTS
# include <sys/sysmacros.h>
D 268
# undef HASLSTAT	/* has symlinks, but they cause problems */
E 268
I 268
# undef HASLSTAT		/* has symlinks, but they cause problems */
E 268
# define NEEDFSYNC	1	/* system fsync(2) fails on non-EFS filesys */
# define SYS5SIGNALS	1	/* System V signal semantics */
# define SYS5SETPGRP	1	/* use System V setpgrp(2) syscall */
# define HASUNAME	1	/* use System V uname(2) system call */
# define HASINITGROUPS	1	/* has initgroups(3) function */
# define HASSETVBUF	1	/* has setvbuf(3) function */
# define HASSIGSETMASK	0	/* does not have sigsetmask(2) function */
# ifndef HASGETUSERSHELL
#  define HASGETUSERSHELL 0	/* does not have getusershell(3) function */
# endif
# define GIDSET_T	gid_t	/* type of 2nd arg to getgroups(2) isn't int */
# define LA_TYPE	LA_ZERO		/* doesn't have load average */
# define SFS_TYPE	SFS_4ARGS	/* use 4-arg statfs() */
I 213
# define SFS_BAVAIL	f_bfree		/* alternate field name */
E 213
D 271
# define _PATH_UNIX	"/unix"
# ifndef _PATH_SENDMAILCF
#  define _PATH_SENDMAILCF	"/usr/lib/sendmail.cf"
# endif
E 271
I 271
# define _PATH_UNIX		"/unix"
# define _PATH_VENDOR_CF	"/usr/lib/sendmail.cf"
E 271
#endif

I 211
/*
**  Cray Computer Corporation's CSOS
**
D 237
**	Contributed by Scott Bolte <scott@craycos.com>.
E 237
I 237
**	From Scott Bolte <scott@craycos.com>.
E 237
*/
E 211

I 211
#ifdef _CRAYCOM
# define SYSTEM5	1	/* include all the System V defines */
# define SYS5SIGNALS	1	/* SysV signal semantics -- reset on each sig */
# define NEEDFSYNC	1	/* no fsync in system library */
# define MAXPATHLEN	PATHSIZE
# define LA_TYPE	LA_ZERO
# define SFS_TYPE	SFS_4ARGS	/* four argument statfs() call */
I 213
# define SFS_BAVAIL	f_bfree		/* alternate field name */
E 213
# define _POSIX_CHOWN_RESTRICTED	-1
extern struct group	*getgrent(), *getgrnam(), *getgrgid();
#endif
E 211


I 224
/*
**  Sony NEWS-OS 4.2.1R and 6.0.3
I 237
**
**	From Motonori NAKAMURA <motonori@cs.ritsumei.ac.jp>.
E 237
*/

#ifdef sony_news
# ifndef __svr4
			/* NEWS-OS 4.2.1R */
#  ifndef BSD
#   define BSD			/* has BSD routines */
#  endif
#  define HASUNSETENV	1	/* has unsetenv(2) call */
#  undef HASSETVBUF		/* don't actually have setvbuf(3) */
#  define WAITUNION	1	/* use "union wait" as wait argument type */
#  define LA_TYPE	LA_INT
#  define SFS_TYPE	SFS_VFS /* use <sys/vfs.h> statfs() implementation */
#  ifndef HASFLOCK
#   define HASFLOCK	1	/* has flock(2) call */
#  endif
#  define setpgid	setpgrp
#  undef WIFEXITED
#  undef WEXITSTATUS
typedef int		pid_t;
typedef int		(*sigfunc_t)();
#  define SIGFUNC_DEFINED

# else
			/* NEWS-OS 6.0.3 with /bin/cc */
D 267
#  define SYSTEM5	1	/* include all the System V defines */
#  define SYS5SIGNALS	1	/* SysV signal semantics -- reset on each sig */
#  define HASINITGROUPS	1	/* has initgroups(3) call */
D 242
#  define HASSETREUID	1	/* has setreuid(2) call */
E 242
I 242
#  define USESETEUID	1	/* has useable seteuid(2) call */
E 267
I 267
#  ifndef __svr4__
#   define __svr4__		/* use all System V Releae 4 defines below */
#  endif
E 267
E 242
#  define HASSETSID	1	/* has Posix setsid(2) call */
#  define HASGETUSERSHELL 1	/* DOES have getusershell(3) call in libc */
D 237
#  define LA_TYPE	LA_INT
E 237
I 237
#  define LA_TYPE	LA_READKSYM	/* use MIOC_READKSYM ioctl */
E 237
D 267
#  define SFS_TYPE	SFS_STATVFS	/* use <sys/statvfs.h> statvfs() impl */
E 267
I 243
#  ifndef SPT_TYPE
#   define SPT_TYPE	SPT_SYSMIPS	/* use sysmips() (OS 6.0.2 or later) */
#  endif
E 243
#  define GIDSET_T	gid_t
D 242
#  define setreuid(r, e)	seteuid(e)
E 242
#  undef WIFEXITED
#  undef WEXITSTATUS
I 267
#  ifndef SYSLOG_BUFSIZE
#   define SYSLOG_BUFSIZE	1024
#  endif
E 267
D 271
#  define _PATH_UNIX  "/stand/unix"
#  ifndef _PATH_SENDMAILCF
#   define _PATH_SENDMAILCF	"/etc/mail/sendmail.cf"
#  endif
E 271
I 271
#  define _PATH_UNIX		"/stand/unix"
#  define _PATH_VENDOR_CF	"/etc/mail/sendmail.cf"
E 271
#  ifndef _PATH_SENDMAILPID
#   define _PATH_SENDMAILPID	"/etc/mail/sendmail.pid"
#  endif

# endif
#endif


/*
**  Omron LUNA/UNIOS-B 3.0, LUNA2/Mach and LUNA88K Mach
I 237
**
**	From Motonori NAKAMURA <motonori@cs.ritsumei.ac.jp>.
E 237
*/

#ifdef luna
# ifndef IDENTPROTO
#  define IDENTPROTO	0	/* TCP/IP implementation is broken */
# endif
# ifdef uniosb
I 235
#  include <sys/time.h>
E 235
D 225
#  define SYS_TIME	1	/* use <sys/time.h> instead of <time.h> */
E 225
#  define NEEDVPRINTF	1	/* need a replacement for vprintf(3) */
# endif
I 243
# define HASUNSETENV	1	/* has unsetenv(2) call */
# define NEEDPUTENV	1	/* need putenv(3) call */
E 243
# define NEEDGETOPT	1	/* need a replacement for getopt(3) */
I 245
# define NEEDSTRSTR	1	/* need emulation of the strstr(3) call */
E 245
# define WAITUNION	1	/* use "union wait" as wait argument type */
# ifdef uniosb
#  define LA_TYPE	LA_INT
# endif
# ifdef luna2m
#  define LA_TYPE	LA_SUBR
# endif
# ifdef luna88k
#  define LA_TYPE	LA_INT
# endif
# define SFS_TYPE	SFS_VFS /* use <sys/vfs.h> statfs() implementation */
# define setpgid	setpgrp
# undef WIFEXITED
# undef WEXITSTATUS
typedef int		pid_t;
typedef int		(*sigfunc_t)();
# define SIGFUNC_DEFINED
extern char	*getenv();
extern int	errno;
D 271
# ifndef _PATH_SENDMAILCF
#  define _PATH_SENDMAILCF	"/usr/lib/sendmail.cf"
# endif
E 271
I 271
# define _PATH_VENDOR_CF	"/usr/lib/sendmail.cf"
E 271
#endif

  
/*
D 237
**  NEC EWS-UX/V 4.2
E 237
I 237
**  NEC EWS-UX/V 4.2 (with /usr/ucb/cc)
E 237
**
D 237
**  with /usr/ucb/cc
E 237
I 237
**	From Motonori NAKAMURA <motonori@cs.ritsumei.ac.jp>.
E 237
*/

#ifdef nec_ews_svr4
D 235
# define SYSTEM5	1	/* include all the System V defines */
E 235
I 235
# ifndef __svr4__
#  define __svr4__		/* use all System V Releae 4 defines below */
# endif
E 235
# define SYS5SIGNALS	1	/* SysV signal semantics -- reset on each sig */
D 235
# define HASINITGROUPS	1	/* has initgroups(3) call */
# define HASSETREUID	1	/* has setreuid(2) call */
# define setreuid(r, e)	seteuid(e)
E 235
# define HASSETSID	1	/* has Posix setsid(2) call */
I 237
# define LA_TYPE	LA_READKSYM	/* use MIOC_READSYM ioctl */
E 237
D 235
# define LA_TYPE	LA_INT
E 235
# define SFS_TYPE	SFS_USTAT	/* use System V ustat(2) syscall */
# define GIDSET_T	gid_t
D 235
# ifndef HASGETUSERSHELL
#  define HASGETUSERSHELL	0	/* does not have getusershell(3) call */
# endif
E 235
# undef WIFEXITED
# undef WEXITSTATUS
D 235
# ifndef _PATH_UNIX
#  define _PATH_UNIX		"/unix"
# endif
# ifndef _PATH_SENDMAILCF
#  define _PATH_SENDMAILCF	"/var/ucblib/sendmail.cf"
# endif
# ifndef _PATH_SENDMAILPID
#  define _PATH_SENDMAILPID	"/var/ucblib/sendmail.pid"
# endif
# define NAMELISTMASK	0x7fffffff		/* mask for nlist() values */
E 235
I 235
# define NAMELISTMASK	0x7fffffff	/* mask for nlist() values */
D 237
# include <sys/ksym.h>		/* for MIOC_READKSYM */
E 237
E 235
#endif



E 224
E 206
E 189
E 131
E 129
E 112
E 104
E 102
E 83
E 79
D 80
/*
E 80
I 80
/**********************************************************************
E 80
**  End of Per-Operating System defines
D 80
*/
E 80
I 80
**********************************************************************/
E 80
D 242

I 82
/**********************************************************************
E 242
I 242
/**********************************************************************
E 242
**  More general defines
**********************************************************************/

I 83
/* general BSD defines */
#ifdef BSD
D 93
# define HASSETENV	1	/* has setenv(3) call */
# define HASUNSETENV	1	/* has unsetenv(3) call */
E 93
D 92
# define HASGETDTABLESIZE 1	/* we have getdtablesize(2) call */
# define HASSETREUID	1	/* have setreuid(2) call */
E 92
I 92
# define HASGETDTABLESIZE 1	/* has getdtablesize(2) call */
# define HASSETREUID	1	/* has setreuid(2) call */
D 196
# define HASINITGROUPS	1	/* has initgroups(2) call */
E 196
I 196
# define HASINITGROUPS	1	/* has initgroups(3) call */
I 246
# ifndef IP_SRCROUTE
#  define IP_SRCROUTE	1	/* can check IP source routing */
# endif
E 246
E 196
I 188
# ifndef HASSETRLIMIT
#  define HASSETRLIMIT	1	/* has setrlimit(2) call */
# endif
E 188
D 157
# define HASFLOCK	1	/* has flock(2) call */
E 157
I 157
# ifndef HASFLOCK
#  define HASFLOCK	1	/* has flock(2) call */
# endif
I 192
# ifndef TZ_TYPE
D 193
#  define TZ_TYPE	TZ_USE_TM_ZONE	/* use tm->tm_zone variable */
E 193
I 193
#  define TZ_TYPE	TZ_TM_ZONE	/* use tm->tm_zone variable */
E 193
# endif
E 192
E 157
I 144
#endif

/* general System V Release 4 defines */
#ifdef __svr4__
I 259
D 264
# include <sys/mkdev.h>
E 264
E 259
# define SYSTEM5	1
D 242
# define HASSETREUID	1	/* has seteuid(2) call & working saved uids */
E 242
I 242
# define USESETEUID	1	/* has useable seteuid(2) call */
E 242
I 196
# define HASINITGROUPS	1	/* has initgroups(3) call */
I 257
#  define BSD_COMP	1	/* get BSD ioctl calls */
E 257
# ifndef HASSETRLIMIT
#  define HASSETRLIMIT	1	/* has setrlimit(2) call */
# endif
E 196
I 145
D 146
# ifndef NEEDGETUSERSHELL
#  define NEEDGETUSERSHELL 1	/* needs getusershell(3) implementation ??? */
E 146
I 146
# ifndef HASGETUSERSHELL
#  define HASGETUSERSHELL 0	/* does not have getusershell(3) call */
E 146
# endif
E 145
D 242
# define setreuid(r, e)	seteuid(e)
E 242

# ifndef _PATH_UNIX
#  define _PATH_UNIX		"/unix"
# endif
D 271
# ifndef _PATH_SENDMAILCF
#  define _PATH_SENDMAILCF	"/usr/ucblib/sendmail.cf"
# endif
E 271
I 271
D 273
# define _PATH_VENDOR_CF	"/usr/ucblib/sendmail.cf"
E 273
I 273
# ifndef _PATH_VENDOR_CF
#  define _PATH_VENDOR_CF	"/usr/ucblib/sendmail.cf"
# endif
E 273
E 271
# ifndef _PATH_SENDMAILPID
#  define _PATH_SENDMAILPID	"/usr/ucblib/sendmail.pid"
# endif
# ifndef SYSLOG_BUFSIZE
#  define SYSLOG_BUFSIZE	128
# endif
I 184
# ifndef SFS_TYPE
#  define SFS_TYPE		SFS_STATVFS
# endif
E 184
E 144
E 92
D 93
# ifndef LA_TYPE
#  define LA_TYPE	LA_SUBR
# endif
E 93
#endif

E 83
E 82
/* general System V defines */
D 170
# ifdef SYSTEM5
E 170
I 170
#ifdef SYSTEM5
E 170
I 120
# include <sys/sysmacros.h>
E 120
D 82
# define LOCKF		1	/* use System V lockf instead of flock */
E 82
I 82
D 92
# define LOCKF		1	/* use System V locking instead of flock */
E 92
E 82
D 83
# define SYS5TZ		1	/* use System V style timezones */
E 83
D 82
# define HASUNAME	1	/* use System V uname system call */
# define NEEDGETDTABLESIZE 1	/* needs a replacement getdtablesize */
E 82
I 82
# define HASUNAME	1	/* use System V uname(2) system call */
D 155
# define HASUSTAT	1	/* use System V ustat(2) syscall */
E 155
I 112
# define SYS5SETPGRP	1	/* use System V setpgrp(2) syscall */
I 131
# define HASSETVBUF	1	/* we have setvbuf(3) in libc */
I 188
# ifndef HASULIMIT
#  define HASULIMIT	1	/* has the ulimit(2) syscall */
# endif
E 188
E 131
E 112
I 83
# ifndef LA_TYPE
D 155
#  define LA_TYPE	LA_INT
E 155
I 155
D 236
#  define LA_TYPE	LA_INT		/* assume integer load average */
E 236
I 236
#  ifdef MIOC_READKSYM
#   define LA_TYPE	LA_READKSYM	/* use MIOC_READKSYM ioctl */
#  else
#   define LA_TYPE	LA_INT		/* assume integer load average */
#  endif
E 236
# endif
# ifndef SFS_TYPE
#  define SFS_TYPE	SFS_USTAT	/* use System V ustat(2) syscall */
I 192
# endif
# ifndef TZ_TYPE
D 193
#  define TZ_TYPE	TZ_USE_TZNAME	/* use tzname[] vector */
E 193
I 193
#  define TZ_TYPE	TZ_TZNAME	/* use tzname[] vector */
E 193
E 192
E 155
# endif
E 83
D 202
# define bcopy(s, d, l)		(memmove((d), (s), (l)))
# define bzero(d, l)		(memset((d), '\0', (l)))
# define bcmp(s, d, l)		(memcmp((s), (d), (l)))
E 202
I 202
D 214
# ifndef ALTOS_SYS_V
#  define bcopy(s, d, l)	(memmove((d), (s), (l)))
#  define bzero(d, l)		(memset((d), '\0', (l)))
#  define bcmp(s, d, l)		(memcmp((s), (d), (l)))
# endif
E 214
I 214
# define bcopy(s, d, l)		(memmove((d), (s), (l)))
# define bzero(d, l)		(memset((d), '\0', (l)))
# define bcmp(s, d, l)		(memcmp((s), (d), (l)))
E 214
E 202
E 82
D 170
# endif
E 170
I 170
#endif
E 170
I 82
D 131

/* general "standard C" defines */
D 120
#if defined(__STDC__) || defined(SYSTEM5)
E 120
I 120
#if (defined(__STDC__) && !defined(MACH386)) || defined(SYSTEM5)
E 120
# define HASSETVBUF	1	/* we have setvbuf(3) in libc */
#endif
E 131

/* general POSIX defines */
#ifdef _POSIX_VERSION
D 113
# define HASSETSID	1	/* has setsid(2) call */
I 85
# define HASWAITPID	1	/* has waitpid(2) call */
E 113
I 113
# define HASSETSID	1	/* has Posix setsid(2) call */
# define HASWAITPID	1	/* has Posix waitpid(2) call */
I 242
# if _POSIX_VERSION >= 199500 && !defined(USESETEUID)
#  define USESETEUID	1	/* has useable seteuid(2) call */
# endif
E 242
E 113
E 85
D 91
#endif
E 82
E 78

E 74
E 60
E 59
E 54
E 32
D 56
# endif
E 56
I 56
/*
D 57
**  Due to a "feature" in Ultrix, if you receive an ICMP_UNREACH_HOST
**  on _any_ connection, all connections to that host are closed.  Some
**  firewalls return this error if you try to connect to the IDENT port
**  (113), so you can't receive email from these hosts on Ultrix.  The
**  firewall really should use ICMP_UNREACH_PROTOCOL or _PORT or
**  _NET_PROHIB instead.
E 57
I 57
**  Due to a "feature" in some operating systems such as Ultrix 4.3 and
**  HPUX 8.0, if you receive a "No route to host" message (ICMP message
**  ICMP_UNREACH_HOST) on _any_ connection, all connections to that host
**  are closed.  Some firewalls return this error if you try to connect
**  to the IDENT port (113), so you can't receive email from these hosts
**  on these systems.  The firewall really should use a more specific
**  message such as ICMP_UNREACH_PROTOCOL or _PORT or _NET_PROHIB.
E 57
*/

D 57
#ifndef ultrix
E 57
I 57
D 62
#if !defined(ultrix) && !defined(hpux)
E 62
I 62
#if !defined(ultrix) && !defined(__hpux)
E 62
E 57
# define IDENTPROTO	1	/* use IDENT proto (RFC 1413) */
E 91
I 81
#endif
D 242

/*
**  If no type for argument two of getgroups call is defined, assume
**  it's an integer -- unfortunately, there seem to be several choices
**  here.
*/

#ifndef GIDSET_T
# define GIDSET_T	int
I 129
#endif

/*
E 242
I 242
/*
E 242
D 211
**  Tweaking for systems that (for example) claim to be BSD but
**  don't have all the standard BSD routines (boo hiss).
E 211
I 211
**  Tweaking for systems that (for example) claim to be BSD or POSIX
**  but don't have all the standard BSD or POSIX routines (boo hiss).
E 211
*/

#ifdef titan
# undef HASINITGROUPS		/* doesn't have initgroups(3) call */
I 211
#endif

#ifdef _CRAYCOM
# undef HASSETSID		/* despite POSIX claim, doesn't have setsid */
I 214
#endif

#ifdef ISC_UNIX
# undef bcopy			/* despite SystemV claim, uses BSD bcopy */
#endif

#ifdef ALTOS_SYS_V
# undef bcopy			/* despite SystemV claim, uses BSD bcopy */
# undef bzero			/* despite SystemV claim, uses BSD bzero */
# undef bcmp			/* despite SystemV claim, uses BSD bcmp */
E 214
E 211
E 129
E 81
#endif
E 56
E 28
E 27
E 25
I 19

I 157

E 157
I 141
/*
**  Due to a "feature" in some operating systems such as Ultrix 4.3 and
**  HPUX 8.0, if you receive a "No route to host" message (ICMP message
**  ICMP_UNREACH_HOST) on _any_ connection, all connections to that host
**  are closed.  Some firewalls return this error if you try to connect
**  to the IDENT port (113), so you can't receive email from these hosts
**  on these systems.  The firewall really should use a more specific
**  message such as ICMP_UNREACH_PROTOCOL or _PORT or _NET_PROHIB.  If
**  not explicitly set to zero above, default it on.
*/
E 141
D 24
	/*
	 * Use query type of ANY if possible (NO_WILDCARD_MX), which will
	 * find types CNAME, A, and MX, and will cause all existing records
	 * to be cached by our local server.  If there is (might be) a
	 * wildcard MX record in the local domain or its parents that are
	 * searched, we can't use ANY; it would cause fully-qualified names
	 * to match as names in a local domain.
	 */
# define NO_WILDCARD_MX	1
E 24
I 24
D 105
/*
E 105
I 105

I 141
#ifndef IDENTPROTO
# define IDENTPROTO	1	/* use IDENT proto (RFC 1413) */
I 241
#endif

#ifndef IP_SRCROUTE
# define IP_SRCROUTE	1	/* Detect IP source routing */
E 241
I 145
#endif

D 146
#ifndef NEEDGETUSERSHELL
# define NEEDGETUSERSHELL 0	/* libc has getusershell(3) */
E 146
I 146
#ifndef HASGETUSERSHELL
# define HASGETUSERSHELL 1	/* libc has getusershell(3) call */
I 268
#endif

#ifndef NETUNIX
# define NETUNIX	1	/* include unix domain support */
E 268
I 157
#endif

#ifndef HASFLOCK
# define HASFLOCK	0	/* assume no flock(2) support */
I 188
#endif

I 242
#ifndef HASSETREUID
# define HASSETREUID	0	/* assume no setreuid(2) call */
#endif

#ifndef USESETEUID
# define USESETEUID	0	/* assume no seteuid(2) call or no saved ids */
#endif

E 242
#ifndef HASSETRLIMIT
# define HASSETRLIMIT	0	/* assume no setrlimit(2) support */
#endif

#ifndef HASULIMIT
# define HASULIMIT	0	/* assume no ulimit(2) support */
E 188
I 182
#endif

#ifndef OLD_NEWDB
# define OLD_NEWDB	0	/* assume newer version of newdb */
I 206
#endif

/* heuristic setting of HASSETSIGMASK; can override above */
#ifndef HASSIGSETMASK
# ifdef SIGVTALRM
#  define HASSETSIGMASK	1
# else
#  define HASSETSIGMASK	0
# endif
I 242
#endif

/*
**  If no type for argument two of getgroups call is defined, assume
**  it's an integer -- unfortunately, there seem to be several choices
**  here.
*/

#ifndef GIDSET_T
# define GIDSET_T	int
E 242
I 222
#endif

#ifndef UID_T
# define UID_T		uid_t
I 223
#endif

#ifndef SIZE_T
# define SIZE_T		size_t
E 223
#endif

#ifndef ARGV_T
# define ARGV_T		char **
E 222
E 206
E 182
E 157
E 146
E 145
#endif
D 246


E 141
/**********************************************************************
E 246
I 246
/**********************************************************************
E 246
E 105
I 54
**  Remaining definitions should never have to be changed.  They are
**  primarily to provide back compatibility for older systems -- for
D 59
**  example, it includes some POSIX compatibility definitions */
E 59
I 59
**  example, it includes some POSIX compatibility definitions
D 105
*/
E 105
I 105
**********************************************************************/
E 105
E 59

I 63
/* System 5 compatibility */
#ifndef S_ISREG
D 130
#define S_ISREG(foo)	((foo & S_IFREG) == S_IFREG)
E 130
I 130
# define S_ISREG(foo)	((foo & S_IFMT) == S_IFREG)
#endif
#if !defined(S_ISLNK) && defined(S_IFLNK)
# define S_ISLNK(foo)	((foo & S_IFMT) == S_IFLNK)
E 130
#endif
I 216
#ifndef S_IWUSR
# define S_IWUSR		0200
#endif
E 216
#ifndef S_IWGRP
D 216
#define S_IWGRP		020
E 216
I 216
# define S_IWGRP		0020
E 216
#endif
#ifndef S_IWOTH
D 216
#define S_IWOTH		002
E 216
I 216
# define S_IWOTH		0002
E 216
#endif

E 63
/*
E 54
**  Older systems don't have this error code -- it should be in
**  /usr/include/sysexits.h.
*/

# ifndef EX_CONFIG
# define EX_CONFIG	78	/* configuration error */
# endif
I 113

/* pseudo-code used in server SMTP */
# define EX_QUIT	22	/* drop out of server immediately */

E 113
I 87

I 90
/*
**  These are used in a few cases where we need some special
**  error codes, but where the system doesn't provide something
**  reasonable.  They are printed in errstring.
*/

#ifndef E_PSEUDOBASE
# define E_PSEUDOBASE	256
#endif

#define EOPENTIMEOUT	(E_PSEUDOBASE + 0)	/* timeout on open */
#define E_DNSBASE	(E_PSEUDOBASE + 20)	/* base for DNS h_errno */

E 90
/* type of arbitrary pointer */
#ifndef ARBPTR_T
# define ARBPTR_T	void *
#endif
E 87
I 74

#ifndef __P
# include "cdefs.h"
#endif
E 74
I 53

I 186
#if NAMED_BIND
# include <arpa/nameser.h>
I 189
# ifdef __svr4__
#  ifdef NOERROR
#   undef NOERROR		/* avoid compiler conflict with stream.h */
#  endif
# endif
I 274
# ifndef __ksr__
extern int h_errno;
# endif
E 274
E 189
#endif

E 186
/*
I 185
**  The size of an IP address -- can't use sizeof because of problems
**  on Crays, where everything is 64 bits.  This will break if/when
**  IP addresses are expanded to eight bytes.
*/

D 186
#define IPADDRSIZE	4
E 186
I 186
#ifndef INADDRSZ
# define INADDRSZ	4
#endif

/*
**  The size of various known types -- for reading network protocols.
**  Again, we can't use sizeof because of compiler randomness.
*/

#ifndef INT16SZ
# define INT16SZ	2
#endif
#ifndef INT32SZ
# define INT32SZ	4
#endif
E 186

/*
E 185
**  Do some required dependencies
*/

#if defined(NETINET) || defined(NETISO)
D 58
# define DAEMON		1
# define SMTP		1
# define QUEUE		1
E 58
I 58
# define SMTP		1	/* enable user and server SMTP */
# define QUEUE		1	/* enable queueing */
# define DAEMON		1	/* include the daemon (requires IPC & SMTP) */
E 58
#endif

E 53
I 36

/*
**  Arrange to use either varargs or stdargs
*/

# ifdef __STDC__

# include <stdarg.h>

D 43
# define VA_ARG_FORMAL
# define VA_ARG_DECL
E 43
# define VA_LOCAL_DECL	va_list ap;
# define VA_START(f)	va_start(ap, f)
# define VA_END		va_end(ap)

# else

# include <varargs.h>

D 43
# define VA_ARG_FORMAL	,va_alist
# define VA_ARG_DECL	va_dcl
E 43
# define VA_LOCAL_DECL	va_list ap;
# define VA_START(f)	va_start(ap)
# define VA_END		va_end(ap)

# endif
I 42

D 45
#ifdef UNAME
E 45
I 45
#ifdef HASUNAME
E 45
# include <sys/utsname.h>
# ifdef newstr
#  undef newstr
# endif
D 45
#else /* ! UNAME */
E 45
I 45
#else /* ! HASUNAME */
E 45
# define NODE_LENGTH 32
struct utsname
{
	char nodename[NODE_LENGTH+1];
};
D 45
#endif /* UNAME */
E 45
I 45
#endif /* HASUNAME */
E 45
I 43
D 54

#ifdef sun
# include <vfork.h>
#endif
E 54
I 44

D 79
#ifndef MAXHOSTNAMELEN
#define MAXHOSTNAMELEN	256
E 79
I 79
D 189
#if !defined(MAXHOSTNAMELEN) && !defined(_SCO_unix_)
E 189
I 189
D 202
#if !defined(MAXHOSTNAMELEN) && !defined(_SCO_unix_) && !defined(NonStop_UX_BXX)
E 202
I 202
#if !defined(MAXHOSTNAMELEN) && !defined(_SCO_unix_) && !defined(NonStop_UX_BXX) && !defined(ALTOS_SYS_V)
E 202
E 189
# define MAXHOSTNAMELEN	256
E 79
#endif
I 48

#if !defined(SIGCHLD) && defined(SIGCLD)
# define SIGCHLD	SIGCLD
#endif

#ifndef STDIN_FILENO
D 224
#define STDIN_FILENO	0
E 224
I 224
# define STDIN_FILENO	0
E 224
#endif

#ifndef STDOUT_FILENO
D 224
#define STDOUT_FILENO	1
E 224
I 224
# define STDOUT_FILENO	1
E 224
#endif

#ifndef STDERR_FILENO
D 224
#define STDERR_FILENO	2
E 224
I 224
# define STDERR_FILENO	2
E 224
I 50
D 104
#endif

D 92
#ifdef LOCKF
#define LOCK_SH		0x01	/* shared lock */
#define LOCK_EX		0x02	/* exclusive lock */
#define LOCK_NB		0x04	/* non-blocking lock */
I 65
#define LOCK_UN		0x08	/* unlock */
E 65
I 51

E 92
I 92
#ifdef HASFLOCK
# include <sys/file.h>
E 104
E 92
D 93
#else
E 93
I 93
#endif

#ifndef LOCK_SH
E 93
I 92
# define LOCK_SH	0x01	/* shared lock */
# define LOCK_EX	0x02	/* exclusive lock */
# define LOCK_NB	0x04	/* non-blocking lock */
# define LOCK_UN	0x08	/* unlock */
I 224
#endif

#ifndef SEEK_SET
# define SEEK_SET	0
# define SEEK_CUR	1
# define SEEK_END	2
E 224
#endif
E 92

D 92
# include <sys/file.h>

E 92
I 92
#ifndef SIG_ERR
# define SIG_ERR	((void (*)()) -1)
I 107
#endif

#ifndef WEXITSTATUS
# define WEXITSTATUS(st)	(((st) >> 8) & 0377)
#endif
#ifndef WIFEXITED
# define WIFEXITED(st)		(((st) & 0377) == 0)
I 109
#endif

#ifndef SIGFUNC_DEFINED
typedef void		(*sigfunc_t) __P((int));
E 109
E 107
E 92
E 51
E 50
#endif
I 52

I 137
/* size of syslog buffer */
#ifndef SYSLOG_BUFSIZE
# define SYSLOG_BUFSIZE	1024
#endif

E 137
/*
**  Size of tobuf (deliver.c)
**	Tweak this to match your syslog implementation.  It will have to
**	allow for the extra information printed.
*/

#ifndef TOBUFSIZE
D 137
# define TOBUFSIZE (1024 - 256)
E 137
I 137
# if (SYSLOG_BUFSIZE) > 512
#  define TOBUFSIZE	(SYSLOG_BUFSIZE - 256)
# else
#  define TOBUFSIZE	256
# endif
E 137
#endif
I 70

I 134
/*
**  Size of prescan buffer.
**	Despite comments in the _sendmail_ book, this probably should
**	not be changed; there are some hard-to-define dependencies.
*/

# define PSBUFSIZE	(MAXNAME + MAXATOM)	/* size of prescan buffer */
E 134
/* fork routine -- set above using #ifdef _osname_ or in Makefile */
# ifndef FORK
# define FORK		vfork		/* function to call to fork mailer */
# endif
I 160

/*
D 271
**  If we are going to link scanf anyway, use it in readcf
E 271
I 271
**  Default to using scanf in readcf.
E 271
*/

D 271
#if !defined(HASUNAME) && !defined(SCANF)
E 271
I 271
#ifndef SCANF
E 271
# define SCANF		1
#endif
E 160
I 128
D 141

#ifndef IDENTPROTO
# define IDENTPROTO	0		/* don't use RFC 1413 */
#endif
E 141
E 128
E 70
E 52
E 48
E 44
E 43
E 42
E 36
E 24
E 19
E 18
E 13
E 12
E 8
E 5
D 2
#define VMUNIX		1	/* VMUNIX options (4.1bsd) */
/* #define NVMUNIX	1	/* new VMUNIX options (4.2bsd, requires VMUNIX) */
E 2
E 1
