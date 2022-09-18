h38835
s 00027/00035/00778
d D 8.49 95/05/30 07:31:08 eric 220 219
c change OA semantics so that all .cf entries are mapped into the
c "files" or "local" alias service type
e
s 00002/00002/00811
d D 8.48 95/05/29 18:17:21 eric 219 218
c implementation of aliases that puts first unqualified A option
c as local; rest of A options after switched lookup
e
s 00000/00002/00813
d D 8.47 95/05/28 11:50:15 eric 218 217
c lint
e
s 00001/00001/00814
d D 8.46 95/04/24 20:31:14 eric 217 216
c efficiency improvements
e
s 00001/00001/00814
d D 8.45 95/04/23 14:03:17 eric 216 215
c updates for new DSN drafts
e
s 00001/00001/00814
d D 8.44 95/04/21 09:57:47 eric 215 214
c update copyright notice
e
s 00007/00000/00808
d D 8.43 95/04/13 14:25:23 eric 214 213
c make sure the the MF_OPEN and MF_WRITABLE bits are cleared after the
c maps are closed
e
s 00020/00005/00788
d D 8.42 95/03/31 16:54:09 eric 213 212
c merge a bit with Sun version
e
s 00000/00001/00793
d D 8.41 95/03/31 10:52:28 eric 212 211
c pull getpwXXX and gethostbyXXX calls out into conf.c so they can
c be tweaked
e
s 00001/00001/00793
d D 8.40 95/03/27 09:25:52 eric 211 210
c more cleanup for DSN drafts
e
s 00001/00001/00793
d D 8.39 95/03/14 09:11:22 eric 210 209
c change call to expand() to be more rational (and consistent!)
e
s 00001/00001/00793
d D 8.38 95/03/14 08:19:12 eric 209 208
c be more precise on MAXNAME checking
e
s 00001/00001/00793
d D 8.37 95/02/23 19:00:37 eric 208 207
c allow optional alias files (where the source file doesn't exist)
e
s 00006/00000/00788
d D 8.36 95/02/23 15:50:32 eric 207 206
c cleanup to make gcc -Winitialized happier
e
s 00005/00000/00783
d D 8.35 94/12/28 07:33:08 eric 206 205
c prevent errors during alias auto-rebuilds from stopping VRFY
e
s 00003/00001/00780
d D 8.34 94/12/27 14:44:34 eric 205 204
c allow multiple OA/file/name lines
e
s 00002/00003/00779
d D 8.33 94/11/28 09:16:04 eric 204 203
c fix DSN return receipts to mailing lists
e
s 00015/00013/00767
d D 8.32 94/11/22 22:25:12 eric 203 202
c clean up several small problems with file delivery, error detection,
c and return receipts
e
s 00001/00000/00779
d D 8.31 94/11/22 13:33:56 eric 202 201
c make alias maps have a name
e
s 00028/00010/00751
d D 8.30 94/10/24 18:32:40 eric 201 200
c first cut at service switch abstraction
e
s 00003/00002/00758
d D 8.29 94/07/03 11:48:37 eric 200 199
c break out special local mail processing (e.g., mapping to the
c "prog" mailer) onto separate mailer flags
e
s 00015/00002/00745
d D 8.28 94/06/19 07:34:21 eric 199 198
c avoid denial-of-service attacks caused by setting resource limits
c low before calling sendmail
e
s 00001/00001/00746
d D 8.27 94/06/19 06:35:52 eric 198 197
c print the true database key when entering the alias routine
e
s 00009/00006/00738
d D 8.26 94/05/29 07:34:50 eric 197 196
c avoid logging alias stats if you have no db code defined
e
s 00013/00004/00731
d D 8.25 94/04/14 09:42:47 eric 196 195
c give return-receipt on delivery to mailing lists (instead of to the
c members of that list) and suppress Return-Receipt-To: in subsequent
c deliveries to avoid denial of service attacks and generally improve
c the semantics
e
s 00002/00001/00733
d D 8.24 94/02/28 10:04:54 eric 195 194
c avoid null pointer dereferences to e->e_id when logging
e
s 00003/00001/00731
d D 8.23 94/02/27 11:05:03 eric 194 193
c avoid null pointer reference during logging of EXPN commands
e
s 00001/00001/00731
d D 8.22 94/01/31 17:34:37 eric 193 192
c allow alias builds from alias text files on read only file systems
e
s 00001/00001/00731
d D 8.21 93/12/11 14:21:32 eric 192 191
c be more conservative about reflecting contents of owner- list
c into envelope -- avoid doing it for :include: and /dev/null type situations
e
s 00001/00001/00731
d D 8.20 93/11/13 07:56:55 eric 191 190
c fix core dump on null LHS of alias
e
s 00020/00008/00712
d D 8.19 93/10/31 11:07:14 eric 190 189
c clean up aliaswait backoff algorithm
e
s 00002/00002/00718
d D 8.18 93/10/29 19:25:01 eric 189 188
c use xfclose instead of fclose to catch closes of fd=1
e
s 00023/00005/00697
d D 8.17 93/10/15 08:35:02 eric 188 187
c 8.6.2: improved error return messages; better error handling on
c hung connections or the name server is down; add "vendor code" on V line;
c fix some X-Authentication-Warning: problems; portability fixes
e
s 00006/00000/00696
d D 8.16 93/09/25 07:25:25 eric 187 186
c add MF_ALIASWAIT flag to avoid infinite recursion in aliaswait
e
s 00001/00001/00695
d D 8.15 93/09/22 10:45:41 eric 186 185
c fix signal return value
e
s 00019/00010/00677
d D 8.14 93/09/02 17:19:11 eric 185 184
c improvements to alias file locking code
e
s 00014/00009/00673
d D 8.13 93/09/02 09:45:40 eric 184 183
c don't announce alias file rebuild if it fails
e
s 00002/00002/00680
d D 8.12 93/08/23 08:32:38 eric 183 182
c add "ext" argument to lockfile so you can accurately tell what file
c is being locked in logging/error messages
e
s 00001/00055/00681
d D 8.11 93/08/21 16:36:10 eric 182 181
c move uid setting from forward() to include() so as to be more
c inclusive; this also adds proper group setting (previously it just set
c the user id)
e
s 00025/00006/00711
d D 8.10 93/08/21 07:23:00 eric 181 180
c more NeXT portability changes; use initgroups when reading .forward files
e
s 00001/00001/00716
d D 8.9 93/08/19 14:53:26 eric 180 179
c catch "disappearing" aliases -- they aren't allowed to resolve to nothing
e
s 00003/00002/00714
d D 8.8 93/08/17 09:52:01 eric 179 178
c put in beginnings of mod time checks on maps; generalize flags
c parameter to parseaddr/allocaddr to use RF_ hooks; relax HELO rules
c for Authentication-Warning:s
e
s 00003/00002/00713
d D 8.7 93/08/16 15:24:05 eric 178 177
c do better identification of errors during alias rebuild
e
s 00002/00003/00713
d D 8.6 93/07/26 09:22:15 eric 177 176
c signal and file locking portability changes
e
s 00008/00008/00708
d D 8.5 93/07/19 11:30:40 eric 176 175
c HASSETEUID => HASSETREUID and changes to avoid having to do
c setuid(getuid()) in main.
e
s 00001/00001/00715
d D 8.4 93/07/17 17:06:38 eric 175 174
c clean up semantics: QDONTSEND says don't ever send, and diables QQUEUEUP
c (previously, it meant don't send in this run)
e
s 00016/00005/00700
d D 8.3 93/07/13 12:58:50 eric 174 173
c many fixes.  primarily fix for seteuid problem in 8.2; also,
c Solaris compatibility fixes; timed out messages problems; messages
c silently discarded if checkcompat returned EX_TEMPFAIL
e
s 00025/00000/00680
d D 8.2 93/07/11 06:52:54 eric 173 172
c huge number of changes for 8.2, including IRIX & Solaris portability;
c improved error checking; fix -m flag and add -O flag in maps; fix long
c DNS timeouts; relax safefile restrictions; add -X command line flag; etc.
e
s 00002/00002/00678
d D 8.1 93/06/07 10:29:02 bostic 172 171
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00001/00680
d D 6.52 93/06/05 17:08:14 eric 171 170
c lint-style cleanup
e
s 00008/00069/00673
d D 6.51 93/05/28 07:00:54 eric 170 169
c change alias initialization to general map initialization
e
s 00001/00001/00741
d D 6.50 93/05/27 13:02:02 eric 169 168
c Solaris portability changes
e
s 00000/00002/00742
d D 6.49 93/05/27 11:37:49 eric 168 167
c prototype functions
e
s 00001/00001/00743
d D 6.48 93/05/22 11:52:45 eric 167 166
c alias maps include null byte; don't add .db if it already exits
e
s 00062/00037/00682
d D 6.47 93/05/21 18:57:59 eric 166 165
c changes to merge alias and map implementations
e
s 00075/00915/00644
d D 6.46 93/05/17 10:28:27 eric 165 164
c first cut at merged map/alias implementation
e
s 00044/00034/01515
d D 6.45 93/05/06 12:58:12 eric 164 163
c allow comma separated A option(s)
e
s 00046/00013/01503
d D 6.44 93/05/06 11:28:20 eric 163 162
c cleanup for NIS and general usability
e
s 00032/00016/01484
d D 6.43 93/05/04 20:42:24 eric 162 161
c avoid gratuitous warning messages
e
s 00005/00005/01495
d D 6.42 93/05/04 12:25:16 eric 161 160
c NIS => NIS_ALIASES (set by NIS in conf.h)
e
s 00010/00009/01490
d D 6.41 93/05/03 17:41:01 eric 160 159
c more tweaking to handle error conditions properly
e
s 00092/00024/01407
d D 6.40 93/05/03 17:21:28 eric 159 158
c debugging (printfs and code changes)
e
s 00949/00446/00482
d D 6.39 93/05/03 12:26:38 eric 158 157
c first cut at updated alias implementation
e
s 00002/00002/00926
d D 6.38 93/05/01 15:18:26 eric 157 156
c don't use %e for syslog errors -- either %m or errstring
e
s 00000/00001/00928
d D 6.37 93/05/01 12:47:39 eric 156 155
c oops...  can't #undef __P on vangogh
e
s 00002/00001/00927
d D 6.36 93/05/01 12:26:38 eric 155 154
c minor tweaking of syslog levels & compile fixes for SunOS & Ultrix
e
s 00001/00001/00927
d D 6.35 93/05/01 09:22:35 eric 154 153
c strerror => errstring
e
s 00008/00000/00920
d D 6.34 93/04/30 07:11:07 eric 153 152
c give reasonable error message on transienterror() of include
c or forward file
e
s 00000/00001/00920
d D 6.33 93/04/27 18:52:04 eric 152 151
c move #include <sys/stat.h> into conf.h
e
s 00001/00001/00920
d D 6.32 93/04/18 09:35:29 eric 151 150
c use UCB standard prototype string
e
s 00005/00005/00916
d D 6.31 93/04/10 09:27:04 eric 150 149
c clarify error messages
e
s 00002/00000/00919
d D 6.30 93/04/01 13:29:34 eric 149 148
c strip leading spaces off of aliases
e
s 00001/00000/00918
d D 6.29 93/03/30 15:50:01 eric 148 147
c hooks for eventual better handling of SMTP recipients
e
s 00003/00001/00915
d D 6.28 93/03/29 12:41:45 eric 147 146
c fix typo bugs
e
s 00000/00001/00916
d D 6.27 93/03/17 10:46:23 eric 146 145
c flock requires sys/file.h
e
s 00003/00016/00914
d D 6.26 93/03/17 09:55:29 eric 145 144
c clean up file locking (create a lockfile() routine in conf.c)
e
s 00001/00001/00929
d D 6.25 93/03/16 09:16:27 eric 144 143
c delete e_sender and e_returnpath; fix some bugs in envelope splitting
e
s 00000/00001/00930
d D 6.24 93/03/14 07:36:40 eric 143 142
c change (simplify) user and host UPPER => lower case mapping
e
s 00006/00003/00925
d D 6.23 93/03/13 22:48:00 eric 142 141
c delete trailing newline from aliases when option n set to avoid
c bogus output from EXPN command
e
s 00000/00001/00928
d D 6.22 93/03/07 16:16:16 eric 141 140
c use transienterror() all places where we do this sort of mapping
e
s 00004/00004/00925
d D 6.21 93/03/01 12:44:08 eric 140 139
c changes for ESMTP; mostly better delimiter character pointer passing
e
s 00001/00002/00928
d D 6.20 93/03/01 06:53:46 eric 139 138
c header file cleanup; primarily #include <unistd.h> in sendmail.h
c and delete duplicate cruft
e
s 00010/00002/00920
d D 6.19 93/02/26 08:19:30 eric 138 137
c better handling of transient errors
e
s 00021/00000/00901
d D 6.18 93/02/24 05:37:00 eric 137 136
c propagate alias owner information back to envelope sender
e
s 00005/00002/00896
d D 6.17 93/02/23 09:19:07 eric 136 135
c fix botch in SMTP VRFY code (assumed all users were local)
e
s 00014/00014/00884
d D 6.16 93/02/23 06:32:01 eric 135 134
c overhaul status of SMTP reply codes
e
s 00003/00000/00895
d D 6.15 93/02/20 14:49:04 eric 134 133
c make VRFY just verify; EXPN does full expansion
e
s 00004/00002/00891
d D 6.14 93/02/20 13:46:53 eric 133 132
c close cached MCI connections after a fork; add p (privacy) and b
c (min blocks free) options; fix selfref code; clean up $#error format
e
s 00009/00000/00884
d D 6.13 93/02/19 10:37:14 eric 132 131
c make duplicate deletion more global
e
s 00052/00000/00832
d D 6.12 93/02/19 08:11:43 eric 131 130
c add YP_LAST_MODIFIED and YP_MASTER_NAME to DBM version of alias
c database if YPCOMPAT is #defined (from Takahiro Kanbe).
e
s 00003/00002/00829
d D 6.11 93/02/18 20:22:43 eric 130 129
c move the meta-characters from C0 into C1 space
e
s 00005/00005/00826
d D 6.10 93/02/16 18:30:14 eric 129 128
c clean up log levels; allow IDA-style split header/envelope rewriting;
c extend arpatounix with more zones (but is this even needed?)
e
s 00002/00001/00829
d D 6.9 93/02/15 12:00:35 eric 128 127
c improve some error messages; fix quoted :include:s; check for some
c other buffer overflows; log SMTP protocol errors
e
s 00008/00003/00822
d D 6.8 93/02/14 14:41:50 eric 127 126
c HPUX and OSF/1 support; fix SMTP reply codes & multiple SMTP error
c problem; consider cache timeout non-permanent; be more graceful on OS
c failures; log forward, alias, and userdb expansions on log level 10
e
s 00001/00000/00824
d D 6.7 93/02/12 14:36:36 eric 126 125
c fix System V compatibility -- again
e
s 00001/00004/00823
d D 6.6 93/01/28 17:04:56 eric 125 124
c fix the System 5 compatilibility to be compatible with the rest
c of the world.
e
s 00006/00002/00821
d D 6.5 93/01/28 10:16:00 eric 124 123
c System 5 compatibility, misc fixes
e
s 00002/00001/00821
d D 6.4 93/01/14 08:49:47 eric 123 122
c fix compilation problem with -DNDBM only
e
s 00000/00002/00822
d D 6.3 93/01/09 14:45:45 eric 122 121
c tuning of queueing functions as recommended by John Gardiner Myers
c <jgm+@CMU.EDU>; return mail headers (no body) on messages with negative
c precedence; minor other bug fixes
e
s 00049/00007/00775
d D 6.2 93/01/01 13:07:29 eric 121 120
c report duplicated aliases; handle upper case aliases properly
e
s 00000/00000/00782
d D 6.1 92/12/21 16:08:54 eric 120 119
c Release 6
e
s 00022/00002/00760
d D 5.44 92/12/21 12:11:02 eric 119 118
c fix aliases to print error messages (rather than core dumping);
c allow words as error codes to $#error mailer
e
s 00001/00001/00761
d D 5.43 92/12/20 11:14:28 eric 118 117
c change random constants to be #defines
e
s 00022/00003/00740
d D 5.42 92/12/15 13:24:11 eric 117 116
c J option sets "search path" for .forward
e
s 00007/00000/00736
d D 5.41 92/12/15 12:34:57 eric 116 115
c dynamically allocate header fields (and more....); miscellaneous
c cleanup (mostly comments)
e
s 00001/00001/00735
d D 5.40 92/11/16 11:44:13 eric 115 114
c #error breaks most old compilers, even if it is being ignored
e
s 00093/00079/00643
d D 5.39 92/11/16 11:29:20 eric 114 113
c eliminate old DBM support; improve NDBM support
e
s 00010/00010/00712
d D 5.38 92/11/14 11:34:39 eric 113 112
c (partially) ANSI-fy it
e
s 00002/00001/00720
d D 5.37 92/11/14 09:01:55 eric 112 111
c fix botch in YPCOMPAT mode
e
s 00001/00001/00720
d D 5.36 92/11/14 01:18:12 eric 111 110
c fix error with IF_MAKEDBMFILES ifdef
e
s 00006/00000/00715
d D 5.35 92/11/13 18:36:45 eric 110 109
c -DNDBM implies -DDBM
e
s 00018/00014/00697
d D 5.34 92/07/12 14:10:10 eric 109 108
c reduce number of instances of CurEnv by passing it as a parameter
e
s 00045/00021/00666
d D 5.33 92/05/29 13:49:14 eric 108 107
c YP back compatibility for NEWDB -- DBM files needed
e
s 00001/00005/00686
d D 5.32 92/03/20 22:33:10 eric 107 106
c reject connections more quickly if load average goes up;
c try to time out on opens of .forward files on hung filesystems
e
s 00011/00013/00680
d D 5.31 91/12/14 19:39:50 eric 106 105
c convert lockf implementation to use fcntl directly
e
s 00007/00001/00686
d D 5.30 91/12/13 12:09:41 eric 105 104
c fix lockf code; have getcanonname recognize canonical names
e
s 00001/00001/00686
d D 5.29 91/12/08 14:48:06 eric 104 103
c F_TEST => F_TLOCK
e
s 00012/00000/00675
d D 5.28 91/12/05 17:50:21 eric 103 102
c hacks for systems with lockf, not flock
e
s 00050/00035/00625
d D 5.27 91/11/19 17:35:25 eric 102 101
c allow both NEWDB and DBM compilation so that old alias files will
c be accepted
e
s 00007/00005/00653
d D 5.26 91/09/23 15:09:11 bostic 101 100
c hash_open -> dbopen, R_PUT no longer necessary
e
s 00013/00013/00645
d D 5.25 91/07/26 17:46:17 eric 100 99
c ugh...  fixes for older C compiler
e
s 00023/00005/00635
d D 5.24 91/07/26 17:36:48 eric 99 98
c check some return values
e
s 00094/00025/00546
d D 5.23 91/07/26 17:26:17 eric 98 97
c use new Berkeley DB routines for aliases
e
s 00001/00000/00570
d D 5.22 91/03/02 17:15:11 bostic 97 96
c ANSI
e
s 00001/00011/00569
d D 5.21 90/06/01 19:00:11 bostic 96 95
c new copyright notice
e
s 00001/00001/00579
d D 5.20 90/04/18 13:39:25 bostic 95 94
c signals return void pointers
e
s 00004/00007/00576
d D 5.19 90/03/21 18:26:15 bostic 94 93
c both the alias and alias ndbm files have to be protected
e
s 00001/00001/00582
d D 5.18 89/02/27 09:16:35 bostic 93 92
c add types.h for pwd.h
e
s 00000/00010/00583
d D 5.17 89/01/01 17:16:47 bostic 92 91
c remove DEBUG
e
s 00011/00009/00582
d D 5.16 88/07/14 17:32:43 bostic 91 89
c add approved copyright
e
s 00014/00009/00582
d R 5.16 88/06/30 14:58:15 bostic 90 89
c install approved copyright notice
e
s 00000/00004/00591
d D 5.15 88/04/01 16:22:10 bostic 89 88
c always use flock when rebuilding alias file
e
s 00022/00017/00573
d D 5.14 88/03/13 19:51:26 bostic 88 87
c add Berkeley specific header
e
s 00005/00000/00585
d D 5.13 86/04/17 20:17:54 eric 87 86
c don't ignore aliasing during queue runs in conjunction with -bd
e
s 00001/00001/00584
d D 5.12 86/03/08 09:27:59 eric 86 85
c do dbminit in a reasonable place
e
s 00008/00008/00577
d D 5.11 86/03/02 14:06:46 eric 85 84
c always ignore SIGCHLD in openmailer; get SccsId correct in alias.c
e
s 00001/00001/00584
d D 5.10 86/01/11 00:18:15 eric 84 83
c only check the RHS of aliases during newalias if the "n" option is set;
c this option should probably be set if you are not running the nameserver
e
s 00018/00001/00567
d D 5.9 86/01/05 18:48:46 eric 83 82
m 
c rewrite reply-to and resent-reply-to; save errorqueueu in qf file;
c some performance hacking; some alias handling cleanup; delete leading
c spaces from SMTP lines
e
s 00000/00001/00568
d D 5.8 85/12/17 23:54:27 eric 82 81
m 
c lint
e
s 00014/00001/00555
d D 5.7 85/11/22 08:26:00 eric 81 80
m 
c give error if alias file cannot be opened; log message when rebuilt
e
s 00012/00018/00544
d D 5.6 85/10/24 10:35:58 eric 80 79
m 
c don't create a queue name in syserr; permit trailing blanks and quoted
c commas in aliases.
e
s 00002/00000/00560
d D 5.5 85/10/19 09:53:53 eric 79 78
m 
c strip off spaces again so that blanks at end of line work
e
s 00000/00000/00560
d D 5.4 85/09/19 01:25:42 eric 78 76
i 77
m 
c incorporate SMI changes -- still experimental
e
s 00020/00006/00540
d D 5.3.1.1 85/09/19 00:56:04 eric 77 76
m 
c SMI changes (somewhat)
e
s 00001/00001/00545
d D 5.3 85/06/08 00:39:10 eric 76 75
m 
c lint
e
s 00005/00006/00541
d D 5.2 85/06/07 22:00:06 miriam 75 74
m 
c Resolve duplicate SccsId
e
s 00014/00000/00533
d D 5.1 85/06/07 14:27:12 dist 74 73
m 
c Add copyright
e
s 00066/00035/00467
d D 4.10 85/04/29 22:48:20 eric 73 72
m 
c lock alias file while rebuilding if flock system call available
e
s 00004/00005/00498
d D 4.9 85/04/28 10:43:58 eric 72 71
m 
c arrange tests to recover from trashed DBM files; avoid sending
c nonstandard 050 messages in SMTP transaction
e
s 00001/00001/00502
d D 4.8 85/02/15 09:27:39 eric 71 70
m 
c fix some bugs with -C flag; one with queuing from Teus
e
s 00008/00003/00495
d D 4.7 84/12/05 23:15:10 eric 70 69
m 
c Try to use flock call (this doesn't work because we don't always have an
c open fd); security and performance fixes from Kirk Smith at Purdue; "a"
c option is now the number of minutes to wait for "@:@" alias; fix bug in
c $[ $] using -t; random cleanup
e
s 00005/00010/00493
d D 4.6 84/09/18 19:52:52 eric 69 68
m 
c fix multiline aliases
e
s 00003/00003/00500
d D 4.5 84/08/11 17:49:17 eric 68 66
m 
c Assorted changes from Guy Harris <rlgvax!guy>: mostly lint & USG
e
s 00113/00015/00488
d D 4.4.1.1 84/06/17 16:18:10 eric 67 66
m 
c abortive attempt to install a name server.... sigh.
e
s 00001/00000/00502
d D 4.4 84/03/17 16:26:38 eric 66 65
m 
c always fold case on host names; fold case on the LHS of aliases
e
s 00001/00001/00501
d D 4.3 84/03/11 16:55:19 eric 65 64
m 
c change macro expansion character from $ to \001 so that $'s can be
c used in headers -- the .cf file is unchanged by mapping $ to \001.
c \001 is now a manifest constant.
e
s 00004/00001/00498
d D 4.2 83/12/27 21:19:54 eric 64 63
m 
c fix bug with un-DBM'ed alias files that adds a newline on the end of
c the last entry in the alias; found by John Gilmore, SMI
e
s 00000/00000/00499
d D 4.1 83/07/25 19:46:14 eric 63 62
m 
c 4.2 release version
e
s 00002/00000/00497
d D 3.47 83/04/17 17:15:50 eric 62 61
m 221
c fix bogus errno problems
e
s 00001/00001/00496
d D 3.46 83/03/10 00:47:49 eric 61 60
m 206
c Delete colon on front of aliases
e
s 00002/00004/00495
d D 3.45 83/03/08 19:21:35 eric 60 59
m 205
c Pass the delimiter character to parseaddr so that we can correctly
c decide between comma and space
e
s 00002/00002/00497
d D 3.44 82/12/24 08:14:05 eric 59 58
m 108
c Change parse to parseaddr for BB&N TCP/IP implementation; clean up
c comments in daemon.c to simplify the poor alternate protocol type.
e
s 00001/00001/00498
d D 3.43 82/12/13 18:23:22 eric 58 57
m 085
c The routine "sendto" is now a system call (yeuch!); change our sendto
c to "sendtolist"
e
s 00023/00030/00476
d D 3.42 82/11/28 00:18:06 eric 57 56
m 
c Many changes resulting from a complete code readthrough.  Most of these
c fix minor bugs or change the internal structure for clarity, etc.  There
c should be almost no externally visible changes (other than some cleaner
c error message printouts and the like).
e
s 00000/00027/00506
d D 3.41 82/11/24 18:43:11 eric 56 55
m 
c lint it
e
s 00002/00003/00531
d D 3.40 82/11/13 18:00:50 eric 55 54
m 066
c don't default to rebuilding alias file if needed; now requires the "D"
c option.  This "feature" causes big problems on loaded machines.
e
s 00003/00002/00531
d D 3.39 82/10/28 17:40:04 eric 54 53
m 039,
m 027
c Put the "@:@" trick on the "a" option.  Also, move TrustedUsers into
c sendmail.h (it should have gone here in the first place!)
e
s 00060/00008/00473
d D 3.38 82/10/09 20:27:30 eric 53 52
m 003
c Lock out interrupts during alias rebuild; add an alias "@:@" after
c rebuild that we can check for to insure that the alias file is up to
c date.  Times out after five minutes (is this reasonable on ucbvax?)
c and forces a rebuild.  It shouldn't matter in the long run if two
c people rebuild, so I think this is the right thing to do.
e
s 00001/00001/00480
d D 3.37 82/09/06 16:23:42 eric 52 51
c install new state-driven scanner; make everyone use it, thus fixing
c problems of quoted commas, etc.
e
s 00004/00004/00477
d D 3.36 82/08/08 01:01:01 eric 51 50
c change debug level to a debug vector; add levels on logging (and the
c -L flag); change logging to be by message-id; elevate message-id;
c some lint-type cleanup
e
s 00007/00006/00474
d D 3.35 82/06/07 07:53:44 eric 50 49
c make transcripts verbose always; misc. message cleanup, etc.
e
s 00000/00034/00480
d D 3.34 82/06/07 07:05:44 eric 49 47
c strip out xlate stuff -- this belongs at a different level
e
s 00028/00001/00513
d D 3.33.1.1 82/06/06 20:12:42 eric 48 47
c first cut at putting mailing list maintainers in -- there is a
c much better way though.
e
s 00002/00002/00512
d D 3.33 82/05/31 18:47:51 eric 47 46
c pass lint.  notice that definitions in llib-lc have changed for
c alarm() and sleep() calls {arg was unsigned, is now int}.
e
s 00000/00000/00514
d D 3.32 82/05/31 15:30:41 eric 46 44
i 45
c finish implementing envelopes.  it's not completely clear to me that
c this is really the way to go, but it seems clearly better than what
c i had before.  this delta includes many other minor changes, so it
c should probably not be blithely removed.
e
s 00001/00001/00513
d D 3.31.1.1 82/05/29 18:18:43 eric 45 44
c try to install envelopes.  is this really worth it???
e
s 00002/00002/00512
d D 3.31 82/05/22 01:35:52 eric 44 43
c add "envelopes" to contain the basic information needed as control
c info for each message.  currently there is only one envelope -- this
c being the obvious stupid conversion.  later there will be separate
c envelopes for error messages, return receipts, etc.
e
s 00001/00001/00513
d D 3.30 82/02/15 09:39:09 eric 43 42
c pass lint
e
s 00074/00018/00440
d D 3.29 82/02/04 20:29:09 eric 42 41
c add host aliasing; add -p flag.  this version doesn't yet know about
c replacing the text of the host alias into the message however.  syntax
c is grotty: "/hostmatch:%s@newhost" or whatever.
e
s 00002/00002/00456
d D 3.28 81/12/06 12:37:02 eric 41 40
c cleanup so it will go through lint without any fancy grep -v's;
c change the way SCCS Id's are handled.
e
s 00010/00004/00448
d D 3.27 81/11/21 18:41:07 eric 40 38
c change the send queue to be only one queue instead of one per mailer.
c this is slightly inefficient but simpler.  also, pass this queue
c around so we can have multiple send queues.  this makes VRFY work.
e
s 00002/00001/00451
d D 3.26.1.1 81/11/21 15:44:47 eric 39 38
c links together aliases into proper trees.  This is in part an
c attempt to do the SMTP VRFY command properly, but there are a number
c of annoying problems that convince me that this is the wrong way to
c do it.  Sigh.
e
s 00002/00002/00450
d D 3.26 81/10/23 19:36:40 eric 38 37
c Eliminate magic MN_LOCAL and MN_PROG; change q_mailer item in ADDRESS
c to be pointer to mailer rather than index.
e
s 00002/00003/00450
d D 3.25 81/10/17 16:57:21 eric 37 36
c initial prep to put in Daemon mode
e
s 00001/00004/00452
d D 3.24 81/09/28 19:17:02 eric 36 35
c enable aliases to self-reference themselves correctly.
e
s 00001/00001/00455
d D 3.23 81/09/16 16:23:57 eric 35 34
c last delta was too paranoid -- this increases the number of
c cases that work (but is still safe -- I hope)
e
s 00002/00002/00454
d D 3.22 81/09/16 16:07:21 eric 34 33
c run as the user forwarding mail after a .forward operation;
c fix a bug in .forwarding that caused recursive expansion;
c restrict mail to programs, files, and with :include: for security
c reasons.
e
s 00002/00002/00454
d D 3.21 81/09/07 12:39:58 eric 33 32
c take mode 666 instead of 777 for database autorebuild
e
s 00070/00004/00386
d D 3.20 81/09/07 12:33:14 eric 32 31
c add auto-rebuild on alias database; fix some aliasing bugs;
c add statistics to rebuild; slight code restructuring; change
c version handling one last (?) time
e
s 00040/00008/00350
d D 3.19 81/09/06 19:47:25 eric 31 30
c cleanup, commenting, linting, etc.
e
s 00005/00001/00353
d D 3.18 81/08/22 19:36:21 eric 30 29
c only use a .forward file if owned by the receiver
e
s 00002/00002/00352
d D 3.17 81/08/21 18:17:36 eric 29 28
c drop M_FINAL, change some other defined constant names
e
s 00000/00002/00354
d D 3.16 81/08/20 15:12:57 eric 28 27
c clean up some header information; don't reopen tempfile as
c stdin (to fix some problems with saving mail on interrupts)
e
s 00002/00014/00354
d D 3.15 81/08/20 14:47:26 eric 27 25
c merge forwarding with :include:ing
e
s 00002/00014/00354
d R 3.15 81/08/20 14:36:40 eric 26 25
c merge forwarding with :include:ing
e
s 00002/00002/00366
d D 3.14 81/08/18 17:12:09 eric 25 24
c factor out ARPANET FTP reply codes into conf.c
e
s 00091/00025/00277
d D 3.13 81/08/18 10:38:59 eric 24 23
c put alias.{dir,pag} initialization into sendmail rather than
c a different program (on -I flag).
e
s 00019/00011/00283
d D 3.12 81/08/10 18:48:49 eric 23 22
c make the non-DBM case work
e
s 00001/00000/00293
d D 3.11 81/08/10 18:14:28 eric 22 21
c fix botch with $z macro that confused forwarding
e
s 00173/00065/00120
d D 3.10 81/08/10 16:55:45 eric 21 20
c totally rework aliasing scheme -- sucks when no DBM now,
c but works better for the usual case; fix some quoting problems
c (and how many did I add?); remove .mailer feature since .forward
c will simulate this happily
e
s 00046/00153/00139
d D 3.9 81/08/10 12:26:47 eric 20 19
c intermediate version -- NOT RUNNABLE
e
s 00008/00010/00284
d D 3.8 81/08/09 15:01:43 eric 19 18
c lint it
e
s 00004/00016/00290
d D 3.7 81/08/09 12:33:56 eric 18 17
c add private incoming mailers; add q_home field to ADDRESS struct;
c some general cleanup
e
s 00037/00001/00269
d D 3.6 81/08/08 16:09:04 eric 17 16
c install forwarding using .forward technique
e
s 00006/00000/00264
d D 3.5 81/08/08 15:04:40 eric 16 15
c implement blow-by-blow verbose mode
e
s 00001/00001/00263
d D 3.4 81/03/20 09:44:17 eric 15 14
c change name (again); from postbox to sendmail
e
s 00054/00090/00210
d D 3.3 81/03/11 10:44:52 eric 14 13
c general cleanup, esp. macro processor
e
s 00001/00001/00299
d D 3.2 81/03/07 16:58:24 eric 13 11
c change q_mailer to be index, not pointer
e
s 00003/00001/00299
d R 3.2 81/03/07 15:31:10 eric 12 11
c lint fixes
e
s 00011/00007/00289
d D 3.1 81/03/07 14:25:04 eric 11 10
c ----- delivermail ==> postbox -----
e
s 00031/00004/00265
d D 2.2 80/12/06 17:24:30 eric 10 9
c allow aliases of the form "eric:eric,i.eric"
e
s 00000/00000/00269
d D 2.1 80/11/05 11:00:43 eric 9 8
c release 2
e
s 00004/00000/00265
d D 1.8 80/10/28 23:52:32 eric 8 7
c fixed ANOTHER bug in aliasing (this is getting dull....)
e
s 00005/00001/00260
d D 1.7 80/10/27 19:09:44 eric 7 6
c fix botch with multiple aliases
e
s 00000/00001/00261
d D 1.6 80/10/21 12:12:20 eric 6 5
c fix bug in alias key
e
s 00043/00027/00219
d D 1.5 80/10/18 16:49:04 eric 5 4
c cleanup for dbm stuff: Error => Errors; move local host
c detection into parse; misc cleanup
e
s 00041/00009/00205
d D 1.4 80/10/17 13:41:46 mark 4 3
c uses dbm package for alias file to make it faster
e
s 00006/00028/00208
d D 1.3 80/08/02 13:47:37 eric 3 2
c cleaned up comments
e
s 00002/00000/00234
d D 1.2 80/07/25 22:02:01 eric 2 1
c add ID keywords
e
s 00234/00000/00000
d D 1.1 80/06/23 08:23:07 eric 1 0
e
u
U
f b 
f i 
t
T
I 74
/*
I 91
D 215
 * Copyright (c) 1983 Eric P. Allman
E 215
I 215
 * Copyright (c) 1983, 1995 Eric P. Allman
E 215
E 91
D 88
**  Sendmail
**  Copyright (c) 1983  Eric P. Allman
**  Berkeley, California
**
**  Copyright (c) 1983 Regents of the University of California.
**  All rights reserved.  The Berkeley software License Agreement
**  specifies the terms and conditions for redistribution.
*/
E 88
I 88
D 172
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.
E 172
I 172
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 172
 *
D 96
 * Redistribution and use in source and binary forms are permitted
D 91
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
 *
 *  Sendmail
 *  Copyright (c) 1983  Eric P. Allman
 *  Berkeley, California
E 91
I 91
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
E 96
I 96
 * %sccs.include.redist.c%
E 96
E 91
 */
E 88

I 100
D 139
# include <sys/types.h>
E 139
I 139
# include "sendmail.h"
E 139
D 152
# include <sys/stat.h>
E 152
I 126
D 146
# include <sys/file.h>
E 146
E 126
D 177
# include <signal.h>
E 177
D 114
# include <errno.h>
E 114
D 139
# include "sendmail.h"
E 139
D 125
# include <sys/file.h>
# include <pwd.h>
I 106
# ifdef LOCKF
E 125
D 145
# include <fcntl.h>
E 145
D 125
# endif
E 125
I 125
D 212
# include <pwd.h>
E 212
E 125
E 106
D 158

E 158
I 114
D 165
# ifdef DBM
D 115
# error DBM is no longer supported -- use NDBM instead.
E 115
I 115
ERROR: DBM is no longer supported -- use NDBM instead.
E 115
# endif
D 158

E 158
E 114
# ifdef NEWDB
I 155
D 156
# undef __P
E 156
E 155
# include <db.h>
# endif
D 158

E 158
I 110
# ifdef NDBM
D 114
# ifndef DBM
# define DBM
E 114
I 114
# include <ndbm.h>
E 114
# endif
I 158
D 161
# ifdef NIS
E 161
I 161
# ifdef NIS_ALIASES
E 161
# include <rpcsvc/ypclnt.h>
# endif
E 165
E 158
D 114
# endif
E 114

E 110
I 103
D 106
# ifdef LOCKF
# include <unistd.h>
# endif

E 106
E 103
E 100
I 88
#ifndef lint
D 102
#ifdef DBM
static char sccsid[] = "%W% (Berkeley) %G% (with DBM)";
#else
E 102
I 98
D 165
#ifdef NEWDB
I 124
#ifdef NDBM
static char sccsid[] = "%W% (Berkeley) %G% (with NEWDB and NDBM)";
#else
E 124
static char sccsid[] = "%W% (Berkeley) %G% (with NEWDB)";
I 124
#endif
E 124
#else
I 102
D 114
#ifdef DBM
static char sccsid[] = "%W% (Berkeley) %G% (with DBM)";
E 114
I 114
#ifdef NDBM
static char sccsid[] = "%W% (Berkeley) %G% (with NDBM)";
E 114
#else
E 102
E 98
D 114
static char sccsid[] = "%W% (Berkeley) %G% (without DBM)";
E 114
I 114
D 124
static char sccsid[] = "%W% (Berkeley) %G% (without NDBM)";
E 124
I 124
static char sccsid[] = "%W% (Berkeley) %G% (without NEWDB or NDBM)";
E 124
E 114
#endif
I 98
#endif
E 165
I 165
static char sccsid[] = "%W% (Berkeley) %G%";
E 165
E 98
#endif /* not lint */
D 102

I 98
# ifdef DBM
# ifdef NEWDB
D 100
#   ERROR: must choose one of DBM or NEWDB compilation flags
E 100
I 100
  ERROR ERROR ERROR: must choose one of DBM or NEWDB compilation flags
E 100
# endif
D 100
# endif

E 98
E 88
D 85
#ifndef lint
D 75
static char	SccsId[] = "%W% (Berkeley) %G%";
E 75
I 75
# ifdef DBM
static char	SccsId[] = "%W% (Berkeley) %G%	(with DBM)";
# else DBM
static char	SccsId[] = "%W% (Berkeley) %G%	(without DBM)";
# endif DBM
E 75
#endif not lint

E 85
E 74
I 1
D 28
# include <stdio.h>
# include <ctype.h>
E 28
D 93
# include <pwd.h>
E 93
I 30
# include <sys/types.h>
# include <sys/stat.h>
I 53
# include <signal.h>
I 73
# include <errno.h>
E 73
E 53
E 30
D 11
# include "dlvrmail.h"
E 11
I 11
D 15
# include "postbox.h"
E 15
I 15
# include "sendmail.h"
I 73
D 89
# ifdef FLOCK
E 89
# include <sys/file.h>
I 93
# include <pwd.h>
E 93
D 89
# endif FLOCK
E 89
I 85
D 88

#ifndef lint
# ifdef DBM
static char	SccsId[] = "%W% (Berkeley) %G%	(with DBM)";
# else DBM
static char	SccsId[] = "%W% (Berkeley) %G%	(without DBM)";
# endif DBM
#endif not lint
E 85
E 73
E 15
E 11

E 88
I 2
D 23
static char SccsId[] = "%W%	%G%";
E 23
I 23
D 75
# ifdef DBM
D 41
static char SccsId[] = "%W%	%G%	(with DBM)";
E 41
I 41
SCCSID(%W%	%Y%	%G%	(with DBM));
E 41
# else DBM
D 41
static char SccsId[] = "%W%	%G%	(without DBM)";
E 41
I 41
SCCSID(%W%	%Y%	%G%	(without DBM));
E 41
# endif DBM
E 75
E 23

I 98
# ifdef NEWDB
# include <db.h>
E 100
# endif

E 98
E 2
/*
E 102
I 102
D 165
/*
I 158
**  Alias data structures
*/
#define ALIASDB		struct _aliasdb
E 165


D 165
ALIASDB
{
	ALIASCLASS	*ad_class;	/* class of this database */
	char		*ad_name;	/* name of alias file */
	char		*ad_domain;	/* name of (NIS) domain */
	void		*ad_dbp;	/* ndbm/nis database pointer */
#ifdef NEWDB
	DB		*ad_ndbp;	/* newdb database pointer */
#endif
	short		ad_flags;	/* flag bits */
};

/* bits for ad_flags */
#define ADF_VALID	0x0001		/* database initialized */
#define ADF_WRITABLE	0x0002		/* open for write */
#define ADF_IMPLHASH	0x0004		/* IMPL: underlying hash database */
#define ADF_IMPLNDBM	0x0008		/* IMPL: underlying NDBM database */


ALIASCLASS
{
	char	*ac_name;		/* name of alias class */
	char	*(*ac_lookup)__P((ALIASDB *, char *, ENVELOPE *));
					/* lookup func */
	void	(*ac_store)__P((ALIASDB *, char *, char *, ENVELOPE *));
					/* database store func */
	bool	(*ac_init)__P((ALIASDB *, ENVELOPE *));
					/* initialization func */
D 162
	void	(*ac_rebuild)__P((ALIASDB *, FILE *, ENVELOPE *));
E 162
I 162
	void	(*ac_rebuild)__P((ALIASDB *, FILE *, int, ENVELOPE *));
E 162
					/* initialization func */
	void	(*ac_close)__P((ALIASDB *, ENVELOPE *));
					/* close function */
	short	ac_flags;		/* flag bits */
};

/* bits for ac_flags */
#define ACF_BUILDABLE	0x0001		/* can build a cached version */


ALIASDB	AliasDB[MAXALIASDB + 1];	/* actual database list */
E 165
I 165
D 170
MAP	AliasDB[MAXALIASDB + 1];	/* actual database list */
E 170
I 170
D 220
MAP	*AliasDB[MAXALIASDB + 1];	/* actual database list */
E 170
E 165
D 219
int	NAliasDBs;			/* number of alias databases */
E 219
I 219
int	NAliasDBs = 1;			/* number of alias databases */
E 220
I 220
MAP	*AliasFileMap = NULL;	/* the actual aliases.files map */
int	NAliasFileMaps;		/* the number of entries in AliasFileMap */
E 220
E 219
/*
E 158
E 102
**  ALIAS -- Compute aliases.
**
D 4
**	Scans the file /usr/lib/mailaliases for a set of aliases.
E 4
I 4
D 20
**	Scans the file ALIASFILE for a set of aliases.
E 20
I 20
D 21
**	Scans the file AliasFile for a set of aliases.
E 21
I 21
D 57
**	Scans the file /usr/lib/aliases for a set of aliases.
E 21
E 20
E 4
D 14
**	If found, it arranges to deliver to them by inserting the
D 4
**	new names onto the SendQ queue.
E 4
I 4
**	new names onto the SendQ queue.  Uses libdbm database if -DDBM.
E 14
I 14
**	If found, it arranges to deliver to them.  Uses libdbm
**	database if -DDBM.
E 57
I 57
**	Scans the alias file for an alias for the given address.
**	If found, it arranges to deliver to the alias list instead.
**	Uses libdbm database if -DDBM.
E 57
E 14
E 4
**
**	Parameters:
D 20
**		none
E 20
I 20
**		a -- address to alias.
I 40
**		sendq -- a pointer to the head of the send queue
**			to put the aliases in.
I 203
**		aliaslevel -- the current alias nesting depth.
E 203
I 134
**		e -- the current envelope.
E 134
E 40
E 20
**
**	Returns:
**		none
**
**	Side Effects:
D 14
**		Aliases found on SendQ are removed and put onto
**		AliasQ; replacements are added to SendQ.  This is
**		done until no such replacement occurs.
E 14
I 14
**		Aliases found are expanded.
E 14
**
D 21
**	Defined Constants:
**		MAXRCRSN -- the maximum recursion depth.
D 5
**		ALIASFILE -- the pathname of the alias file.
E 5
**
E 21
D 3
**	Requires:
**		fopen (stdio)
**		fgets (stdio)
**		rewind (stdio)
**		isspace (sys)
**		printf (sys)
**		sendto
**		syserr
**		parse
**		nxtinq
**		sameaddr
**		tkoffq
**		putonq
**		fclose (sys)
**
E 3
D 14
**	Called By:
**		main
**
E 14
D 57
**	Files:
D 3
**		/usr/lib/mailaliases -- the mail aliases.
E 3
I 3
D 20
**		ALIASFILE -- the mail aliases.  The format is
E 20
I 20
D 21
**		AliasFile -- the mail aliases.  The format is
E 21
I 21
**		/usr/lib/aliases -- the mail aliases.  The format is
E 21
E 20
**			a series of lines of the form:
**				alias:name1,name2,name3,...
**			where 'alias' expands to all of
**			'name[i]'.  Continuations begin with
**			space or tab.
I 4
D 20
**		ALIASFILE.pag, ALIASFILE.dir: libdbm version
E 20
I 20
D 21
**		AliasFile.pag, AliasFile.dir: libdbm version
E 21
I 21
**		/usr/lib/aliases.pag, /usr/lib/aliases.dir: libdbm version
E 21
E 20
**			of alias file.  Keys are aliases, datums
**			(data?) are name1,name2, ...
E 4
E 3
**
E 57
D 158
**	Notes:
**		If NoAlias (the "-n" flag) is set, no aliasing is
**			done.
**
E 158
**	Deficiencies:
**		It should complain about names that are aliased to
**			nothing.
D 57
**		It is unsophisticated about line overflows.
E 57
D 3
**
**	History:
**		3/5/80 -- extensive mods to change internal address
**			format.
**		12/27/79 -- written.
E 3
*/

I 207
void
E 207
D 158

I 108
/*
**  Sun YP servers read the dbm files directly, so we have to build them
**  even if NEWDB
*/

E 108
D 5
# define ALIASFILE	"/usr/lib/mailaliases"
E 5
D 21
# define MAXRCRSN	10

E 21
I 4
D 114
#ifdef DBM
E 114
I 114
#ifdef NDBM
E 114
I 108
# ifndef NEWDB
#  define IF_MAKEDBMFILES
# else
#  ifdef YPCOMPAT
#   define IF_MAKEDBMFILES		if (makedbmfiles)
#  endif
# endif
#endif

D 114
#ifdef DBM
E 108
I 102
#ifndef NEWDB
E 102
D 11
typedef struct {char *dptr; int dsize;} datum;
E 11
I 11
typedef struct
E 114
I 114
typedef union
E 114
{
D 98
	char	*dptr;
D 24
	int dsize;
} datum;
E 11
datum lhs, rhs;
D 5
datum fetch();
E 5
I 5
extern datum fetch();
E 24
I 24
	int	dsize;
} DATUM;
D 42
DATUM lhs, rhs;
E 42
extern DATUM fetch();
E 24
E 5
#endif DBM
E 98
I 98
D 114
	char	*data;
	int	size;
} DBT;
E 114
I 114
#ifdef NDBM
	datum	dbm;
E 114
I 102
#endif
E 102
D 114
extern DBT fetch();
#endif /* DBM */
E 114
I 114
#ifdef NEWDB
	DBT	dbt;
#endif
	struct
	{
		char	*data;
		int	size;
	} xx;
} DBdatum;
E 114
E 98
E 4

I 98
#ifdef NEWDB
static DB	*AliasDBptr;
#endif
I 114
#ifdef NDBM
static DBM	*AliasDBMptr;
#endif
E 114

E 158
E 98
D 20
alias()
E 20
I 20
D 40
alias(a)
E 40
I 40
D 109
alias(a, sendq)
E 109
I 109
D 203
alias(a, sendq, e)
E 203
I 203
alias(a, sendq, aliaslevel, e)
E 203
E 109
E 40
	register ADDRESS *a;
I 40
	ADDRESS **sendq;
I 203
	int aliaslevel;
E 203
I 109
	register ENVELOPE *e;
E 109
E 40
E 20
{
D 11
	register addrq *q;
I 7
	addrq *q2;
E 11
I 11
D 21
	register ADDRESS *q;
E 21
D 19
	ADDRESS *q2;
E 19
I 19
	register char *p;
I 133
	int naliases;
I 137
	char *owner;
I 213
	auto int stat = EX_OK;
E 213
	char obuf[MAXNAME + 6];
E 137
E 133
I 39
	extern ADDRESS *sendto();
E 39
I 20
D 21
	extern char *AliasFile;
E 21
E 20
D 42
# ifndef DBM
E 19
E 11
E 7
D 21
	FILE *af;
	char line[MAXLINE+1];
D 19
	register char *p;
	extern int errno;
E 19
	bool didalias;
	bool gotmatch;
D 11
	auto addrq al;
E 11
I 11
	auto ADDRESS al;
E 21
I 21
	register STAB *s;
E 21
E 11
D 19
	extern bool sameaddr();
D 11
	extern addrq *parse();
E 11
I 11
	extern ADDRESS *parse();
E 19
I 19
D 20
# else
E 19
I 14
	int mno;
E 20
I 19
# endif DBM
E 42
I 42
	extern char *aliaslookup();
E 42
E 19
E 14
E 11

D 77
	if (NoAlias)
		return;
E 77
D 92
# ifdef DEBUG
E 92
D 51
	if (Debug)
E 51
I 51
	if (tTd(27, 1))
E 51
D 21
		printf("--- alias ---\n");
E 21
I 21
D 198
		printf("alias(%s)\n", a->q_paddr);
E 198
I 198
		printf("alias(%s)\n", a->q_user);
E 198
E 21
D 92
# endif
E 92

I 21
	/* don't realias already aliased names */
D 136
	if (bitset(QDONTSEND, a->q_flags))
E 136
I 136
D 144
	if (bitset(QDONTSEND|QVERIFIED, a->q_flags))
E 144
I 144
	if (bitset(QDONTSEND|QBADADDR|QVERIFIED, a->q_flags))
E 144
E 136
		return;

I 158
	if (NoAlias)
		return;

E 158
D 44
	To = a->q_paddr;
E 44
I 44
D 109
	CurEnv->e_to = a->q_paddr;
E 109
I 109
	e->e_to = a->q_paddr;
E 109
E 44

I 31
	/*
D 213
	**  Look up this name
E 213
I 213
	**  Look up this name.
	**
	**	If the map was unavailable, we will queue this message
	**	until the map becomes available; otherwise, we could
	**	bounce messages inappropriately.
E 213
	*/

E 31
E 21
D 20
	/* open alias file if not already open */
I 4
#ifndef DBM
E 4
# ifdef DEBUG
	if (Debug && (af = fopen("mailaliases", "r")) != NULL)
		printf(" [using local alias file]\n");
	else
# endif
	if ((af = fopen(ALIASFILE, "r")) == NULL)
	{
# ifdef DEBUG
		if (Debug)
			printf("Can't open %s\n", ALIASFILE);
# endif
		errno = 0;
		return;
	}
I 4
#else DBM
	dbminit(ALIASFILE);
#endif DBM
E 20
I 20
D 42
# ifdef DBM
D 21
	dbminit(AliasFile);
E 21
I 21
	/* create a key for fetch */
	lhs.dptr = a->q_user;
	lhs.dsize = strlen(a->q_user) + 1;
	rhs = fetch(lhs);

	/* find this alias? */
	p = rhs.dptr;
E 42
I 42
D 77
	p = aliaslookup(a->q_user);
E 77
I 77
D 158
	if (NoAlias)
		p = NULL;
	else
		p = aliaslookup(a->q_user);
E 158
I 158
D 213
	p = aliaslookup(a->q_user, e);
E 213
I 213
	p = aliaslookup(a->q_user, &stat, e);
	if (stat == EX_TEMPFAIL || stat == EX_UNAVAILABLE)
	{
		a->q_flags |= QQUEUEUP;
		if (e->e_message == NULL)
			e->e_message = "alias database unavailable";
		return;
	}
E 213
E 158
E 77
E 42
	if (p == NULL)
		return;
D 42
# else DBM
	s = stab(a->q_user, ST_ALIAS, ST_FIND);
	if (s == NULL)
		return;
	p = s->s_alias;
E 21
# endif DBM
E 42
E 20
E 4

I 4
D 20
#ifndef DBM
E 20
E 4
	/*
D 20
	**  Scan alias file.
	**	If we find any user that any line matches any user, we
	**	will send to the line rather than to the user.
	**
	**	We pass through the file several times.  Didalias tells
	**	us if we took some alias on this pass through the file;
	**	when it goes false at the top of the loop we don't have
	**	to scan any more.  Gotmatch tells the same thing, but
	**	on a line-by-line basis; it is used for processing
	**	continuation lines.
	*/

D 4
	didalias = TRUE;
	while (didalias)
E 4
I 4
	do
E 4
	{
		didalias = FALSE;
		gotmatch = FALSE;
		rewind(af);
		while (fgets(line, sizeof line, af) != NULL)
		{
			/* comments begin with `#' */
			if (line[0] == '#')
				continue;

			/* check for continuation lines */
			if (isspace(line[0]))
			{
				if (gotmatch)
				{
D 4
# ifdef DEBUG
					if (Debug)
						printf("   ... also aliased to %s", line);
# endif
E 4
					sendto(line, 1);
				}
				continue;
			}
			gotmatch = FALSE;

			/*
D 14
			**  Check to see if this pseudonym exists in SendQ.
E 14
I 14
			**  Check to see if this pseudonym exists.
E 14
			**	Turn the alias into canonical form.
D 14
			**	Then scan SendQ until you do (or do not)
			**	find that address.
E 14
I 14
			**	Then scan the send queue until you
			**	do (or do not) find that address.
E 14
			*/

			/*  Get a canonical form for the alias. */
			for (p = line; *p != '\0' && *p != ':' && *p != '\n'; p++)
				continue;
			if (*p == '\0' || *p == '\n')
			{
			 syntaxerr:
				syserr("Bad alias line `%s'", line);
				continue;
			}
			*p++ = '\0';
			if (parse(line, &al, -1) == NULL)
			{
				*--p = ':';
				goto syntaxerr;
			}

I 10
D 14
			/* if already in AliasQ don't realias */
			for (q = &AliasQ; (q = nxtinq(q)) != NULL; )
E 14
I 14
			/* if already queued up, don't realias */
			for (q = Mailer[al.q_mailer]->m_sendq; q != NULL; q = q->q_next)
E 14
			{
				if (sameaddr(&al, q, TRUE))
					break;
			}
D 14
			if (q != NULL)
E 14
I 14
			if (q == NULL || bitset(QDONTSEND, q->q_flags))
E 14
				continue;

E 10
D 14
			/*  Scan SendQ for that canonical form. */
			for (q = &SendQ; (q = nxtinq(q)) != NULL; )
			{
				if (sameaddr(&al, q, TRUE))
					break;
			}
			if (q != NULL)
			{
I 4
D 5
#else DBM
	/*
	**  Scan SendQ
	**	We pass through the queue several times.  Didalias tells
	**	us if we took some alias on this pass through the queue;
	**	when it goes false at the top of the loop we don't have
	**	to scan any more.
	*/

	do
	{
		didalias = FALSE;
		/*  Scan SendQ for that canonical form. */
		for (q = &SendQ; (q = nxtinq(q)) != NULL; )
		{
			lhs.dptr = q -> q_paddr;
			lhs.dsize = strlen(lhs.dptr)+1;
			rhs = fetch(lhs);
			p = rhs.dptr;
			if (p != NULL)
			{
#endif
E 5
E 4
				/*
				**  Match on Alias.
				**	Deliver to the target list.
				**	Remove the alias from the send queue
				**	  and put it on the Alias queue.
				*/
E 14
I 14
			/*
			**  Match on Alias.
			**	Deliver to the target list.
			**	Remove the alias from the send queue
			**	  and put it on the Alias queue.
			*/
E 14

# ifdef DEBUG
D 14
				if (Debug)
					printf("%s (%s, %s) aliased to %s (%s,%s,%s)\n",
					    q->q_paddr, q->q_host, q->q_user,
					    p, al.q_paddr, al.q_host, al.q_user);
E 14
I 14
			if (Debug)
				printf("%s (%s, %s) aliased to %s (%s,%s,%s)\n",
				    q->q_paddr, q->q_host, q->q_user,
				    p, al.q_paddr, al.q_host, al.q_user);
E 14
# endif
I 16
			if (Verbose)
				message("050", "aliased to %s", p);
E 16
D 14
				tkoffq(q, &SendQ);
D 10
				putonq(q, &AliasQ);
E 10
				didalias++;
				gotmatch++;
				sendto(p, 1);
I 10
				putonq(q, &AliasQ);
E 10
			}
E 14
I 14
			q->q_flags |= QDONTSEND;
			didalias++;
			gotmatch++;
			sendto(p, 1);
E 14
		}
D 4
	}
E 4
I 4
	} while (didalias);
D 5
#ifndef DBM
E 5
E 4
D 19
	fclose(af);
E 19
I 19
	(void) fclose(af);
E 19
I 4
D 5
#endif
E 5
I 5
#else DBM
	/*
D 14
	**  Scan SendQ
E 14
I 14
	**  Scan send queues
E 20
I 20
D 21
	**  Scan send queue for local mailer.
E 20
E 14
	**	We only have to do this once, since anything we alias
D 10
	**	two is being put at the end of the queue we are
E 10
I 10
	**	to is being put at the end of the queue we are
E 10
D 20
	**	scanning.
E 20
I 20
	**	scanning or another queue.  This is because we only
	**	scan the local mailer queue.
E 21
I 21
	**  Match on Alias.
	**	Deliver to the target list.
E 21
E 20
I 10
D 14
	**	If the alias on SendQ is also (already) on AliasQ, we
	**	have an alias such as:
	**		eric:eric,i:eric
	**	In this case we have already done this alias once, and
	**	we don't want to do it again (for obvious reasons!).
E 14
E 10
	*/

D 7
	for (q = &SendQ; (q = nxtinq(q)) != NULL; )
E 7
I 7
D 10
	for (q2 = nxtinq(&SendQ); (q = q2) != NULL; )
E 10
I 10
D 14
	for (q2 = nxtinq(&SendQ); q2 != NULL; )
E 14
I 14
D 20
	for (mno = 0; Mailer[mno] != NULL; mno++)
E 20
I 20
D 21
	for (q = Mailer[M_LOCAL]->m_sendq; q != NULL; q = q->q_next)
E 21
I 21
D 92
# ifdef DEBUG
E 92
D 51
	if (Debug)
E 51
I 51
	if (tTd(27, 1))
E 51
		printf("%s (%s, %s) aliased to %s\n",
		    a->q_paddr, a->q_host, a->q_user, p);
D 92
# endif
E 92
D 50
	if (Verbose)
D 25
		message("050", "aliased to %s", p);
E 25
I 25
		message(Arpa_Info, "aliased to %s", p);
E 50
I 50
D 135
	message(Arpa_Info, "aliased to %s", p);
E 135
I 135
D 136
	message("aliased to %s", p);
E 136
E 135
I 134
	if (bitset(EF_VRFYONLY, e->e_flags))
I 136
	{
		a->q_flags |= QVERIFIED;
I 148
		e->e_nrcpts++;
E 148
E 136
		return;
I 136
	}
	message("aliased to %s", p);
E 136
E 134
I 127
#ifdef LOG
D 129
	if (LogLevel >= 10)
E 129
I 129
	if (LogLevel > 9)
E 129
D 194
		syslog(LOG_INFO, "%s: alias %s => %s", e->e_id, a->q_paddr, p);
E 194
I 194
		syslog(LOG_INFO, "%s: alias %s => %s",
			e->e_id == NULL ? "NOQUEUE" : e->e_id,
			a->q_paddr, p);
E 194
#endif
I 133
	a->q_flags &= ~QSELFREF;
E 133
E 127
E 50
E 25
D 36
	a->q_flags |= QDONTSEND;
E 36
D 203
	AliasLevel++;
D 34
	sendto(p, 1);
E 34
I 34
D 35
	sendto(p, 1, a);
E 35
I 35
D 36
	sendto(p, 1, (a->q_alias == NULL) ? &From : a);
E 36
I 36
D 39
D 40
	sendto(p, 1, a);
E 40
I 40
D 52
	sendto(p, 1, a, sendq);
E 52
I 52
D 58
	sendto(p, a, sendq);
E 58
I 58
D 109
	sendtolist(p, a, sendq);
E 109
I 109
D 133
	sendtolist(p, a, sendq, e);
E 133
I 133
	naliases = sendtolist(p, a, sendq, e);
E 133
E 109
E 58
E 52
E 40
E 39
I 39
	a->q_child = sendto(p, 1, a, 0);
E 39
E 36
E 35
E 34
	AliasLevel--;
I 132
D 133
	if (!bitset(QSELFREF, a->q_flags))
E 133
I 133
D 180
	if (naliases > 0 && !bitset(QSELFREF, a->q_flags))
E 180
I 180
	if (!bitset(QSELFREF, a->q_flags))
E 203
I 203
	if (tTd(27, 5))
E 203
E 180
E 133
	{
D 203
		if (tTd(27, 5))
		{
			printf("alias: QDONTSEND ");
			printaddr(a, FALSE);
		}
		a->q_flags |= QDONTSEND;
E 203
I 203
		printf("alias: QDONTSEND ");
		printaddr(a, FALSE);
E 203
I 137
	}
I 203
	a->q_flags |= QDONTSEND;
	naliases = sendtolist(p, a, sendq, aliaslevel + 1, e);
	if (bitset(QSELFREF, a->q_flags))
		a->q_flags &= ~QDONTSEND;
E 203

	/*
	**  Look for owner of alias
	*/

	(void) strcpy(obuf, "owner-");
	if (strncmp(a->q_user, "owner-", 6) == 0)
		(void) strcat(obuf, "owner");
	else
		(void) strcat(obuf, a->q_user);
	if (!bitnset(M_USR_UPPER, a->q_mailer->m_flags))
		makelower(obuf);
D 158
	owner = aliaslookup(obuf);
E 158
I 158
D 213
	owner = aliaslookup(obuf, e);
E 213
I 213
	owner = aliaslookup(obuf, &stat, e);
E 213
E 158
D 196
	if (owner != NULL)
E 196
I 196
	if (owner == NULL)
		return;

	/* reflect owner into envelope sender */
	if (strpbrk(owner, ",:/|\"") != NULL)
		owner = obuf;
	a->q_owner = newstr(owner);

	/* announce delivery to this alias; NORECEIPT bit set later */
	if (e->e_xfp != NULL)
E 196
D 204
	{
E 204
D 192
		if (strchr(owner, ',') != NULL)
E 192
I 192
D 196
		if (strpbrk(owner, ",:/|\"") != NULL)
E 192
			owner = obuf;
		a->q_owner = newstr(owner);
E 196
I 196
		fprintf(e->e_xfp, "Message delivered to mailing list %s\n",
			a->q_paddr);
D 204
		e->e_flags |= EF_SENDRECEIPT;
E 196
E 137
	}
E 204
I 204
	e->e_flags |= EF_SENDRECEIPT;
D 211
	a->q_flags |= QREPORT;
E 211
I 211
D 216
	a->q_flags |= QREPORT|QEXPLODED;
E 216
I 216
	a->q_flags |= QDELIVERED|QEXPANDED;
E 216
E 211
E 204
E 132
}
/*
I 42
**  ALIASLOOKUP -- look up a name in the alias file.
**
**	Parameters:
**		name -- the name to look up.
I 213
**		pstat -- a pointer to a place to put the status.
**		e -- the current envelope.
E 213
**
**	Returns:
**		the value of name.
**		NULL if unknown.
**
**	Side Effects:
**		none.
**
**	Warnings:
**		The return value will be trashed across calls.
*/

char *
D 158
aliaslookup(name)
E 158
I 158
D 213
aliaslookup(name, e)
E 213
I 213
aliaslookup(name, pstat, e)
E 213
E 158
	char *name;
I 213
	int *pstat;
E 213
I 158
	ENVELOPE *e;
E 158
{
I 121
D 158
	int i;
	char keybuf[MAXNAME + 1];
E 121
D 98
# ifdef DBM
	DATUM rhs, lhs;
E 98
I 98
D 114
# if defined(NEWDB) || defined(DBM)
	DBT rhs, lhs;
E 114
I 114
# if defined(NEWDB) || defined(NDBM)
	DBdatum rhs, lhs;
E 114
	int s;
I 121
# else /* neither NEWDB nor NDBM */
	register STAB *s;
# endif
E 158
I 158
D 220
	register int dbno;
D 165
	register ALIASDB *ad;
E 165
I 165
	register MAP *map;
E 165
	register char *p;
E 220
I 220
	static MAP *map = NULL;
E 220
I 165
D 166
	char *nullargv[1];
E 166
E 165
E 158
E 121
E 98

I 165
D 166
	nullargv[0] = NULL;
E 166
E 165
D 158
	/* create a key for fetch */
D 98
	lhs.dptr = name;
	lhs.dsize = strlen(name) + 1;
E 98
I 98
D 114
	lhs.data = name;
	lhs.size = strlen(name) + 1;
E 114
I 114
D 121
	lhs.xx.data = name;
	lhs.xx.size = strlen(name) + 1;
E 121
I 121
	i = strlen(name) + 1;
	if (i > sizeof keybuf)
		i = sizeof keybuf;
	bcopy(name, keybuf, i);
	if (!bitnset(M_USR_UPPER, LocalMailer->m_flags))
		makelower(keybuf);
E 158
I 158
D 220
	for (dbno = 0; dbno < NAliasDBs; dbno++)
E 220
I 220
	if (map == NULL)
E 220
	{
D 165
		ad = &AliasDB[dbno];
		if (!bitset(ADF_VALID, ad->ad_flags))
E 165
I 165
D 218
		auto int stat;

E 218
D 170
		map = &AliasDB[dbno];
E 170
I 170
D 220
		map = AliasDB[dbno];
E 170
D 166
		if (!bitset(MF_VALID, map->map_flags))
E 166
I 166
D 219
		if (!bitset(MF_OPEN, map->map_mflags))
E 219
I 219
		if (map == NULL || !bitset(MF_OPEN, map->map_mflags))
E 219
E 166
E 165
			continue;
D 165
		p = (*ad->ad_class->ac_lookup)(ad, name, e);
E 165
I 165
D 166
		p = (*map->map_class->map_lookup)(map, name, nullargv, &stat);
E 166
I 166
D 213
		p = (*map->map_class->map_lookup)(map, name, NULL, &stat);
E 213
I 213
		p = (*map->map_class->map_lookup)(map, name, NULL, pstat);
E 213
E 166
E 165
		if (p != NULL)
			return p;
E 220
I 220
		STAB *s = stab("aliases", ST_MAP, ST_FIND);

		if (s == NULL)
			return NULL;
		map = &s->s_map;
E 220
	}
D 220
	return NULL;
E 220
I 220
	if (!bitset(MF_OPEN, map->map_mflags))
		return NULL;
	return (*map->map_class->map_lookup)(map, name, NULL, pstat);
E 220
}
/*
**  SETALIAS -- set up an alias map
**
**	Called when reading configuration file.
**
**	Parameters:
**		spec -- the alias specification
**
**	Returns:
**		none.
*/
E 158

I 207
void
E 207
D 158
# if defined(NEWDB) || defined(NDBM)
	lhs.xx.size = i;
	lhs.xx.data = keybuf;
E 121
E 114
# ifdef NEWDB
D 102
	s = AliasDBptr->get(AliasDBptr, &lhs, &rhs, 0);
	if (s != 0)
		return (NULL);
E 102
I 102
	if (AliasDBptr != NULL)
E 158
I 158
setalias(spec)
	char *spec;
{
	register char *p;
D 165
	register ALIASDB *ad;
E 165
I 165
	register MAP *map;
E 165
	char *class;
	STAB *s;
I 205
D 220
	static bool first_unqual = TRUE;
E 220
E 205

I 159
	if (tTd(27, 8))
		printf("setalias(%s)\n", spec);

E 159
D 164
	if (NAliasDBs >= MAXALIASDB)
E 164
I 164
	for (p = spec; p != NULL; )
E 164
E 158
	{
I 220
		char buf[50];

E 220
I 170
D 201
		char aname[50];

E 201
E 170
D 114
		s = AliasDBptr->get(AliasDBptr, &lhs, &rhs, 0);
E 114
I 114
D 121
		s = AliasDBptr->get(AliasDBptr, &lhs.dbt, &rhs.dbt, 0);
E 114
		if (s == 0)
E 121
I 121
D 158
		i = AliasDBptr->get(AliasDBptr, &lhs.dbt, &rhs.dbt, 0);
		if (i == 0)
E 121
D 114
			return (rhs.data);
E 114
I 114
			return (rhs.dbt.data);
E 158
I 158
D 164
		syserr("Too many alias databases defined, %d max", MAXALIASDB);
		return;
E 158
E 114
	}
D 114
# ifdef DBM
E 114
I 114
D 158
# ifdef NDBM
E 114
D 119
	else
E 119
I 119
	else if (AliasDBMptr != NULL)
E 158
I 158
	ad = &AliasDB[NAliasDBs];

	for (p = spec; *p != '\0'; p++)
E 158
E 119
	{
D 114
		rhs = fetch(lhs);
		return (rhs.data);
E 114
I 114
D 158
		rhs.dbm = dbm_fetch(AliasDBMptr, lhs.dbm);
		return (rhs.dbm.dptr);
E 158
I 158
		if (strchr(" /:", *p) != NULL)
E 164
I 164
		while (isspace(*p))
			p++;
D 169
		if (*p == NULL)
E 169
I 169
		if (*p == '\0')
E 169
E 164
			break;
E 158
E 114
D 164
	}
D 114
# endif
E 102
# else
E 98
	rhs = fetch(lhs);
D 98
	return (rhs.dptr);
E 98
I 98
D 102
# endif
E 102
	return (rhs.data);
E 98
D 102
# else DBM
E 102
I 102
# endif
# else /* neither NEWDB nor DBM */
E 114
I 114
D 158
# endif /* NDBM */
I 123
	return (NULL);
E 123
# else /* not NEWDB */
	rhs.dbm = dbm_fetch(AliasDBMptr, lhs.dbm);
	return (rhs.dbm.dptr);
# endif /* NEWDB */
# else /* neither NEWDB nor NDBM */
E 114
E 102
D 122
	register STAB *s;

E 122
D 121
	s = stab(name, ST_ALIAS, ST_FIND);
E 121
I 121
	s = stab(keybuf, ST_ALIAS, ST_FIND);
E 121
D 102
	if (s == NULL)
		return (NULL);
	return (s->s_alias);
# endif DBM
E 102
I 102
	if (s != NULL)
		return (s->s_alias);
D 123
# endif
E 123
	return (NULL);
I 123
# endif
E 158
I 158

	if (*p == ':')
	{
		/* explicit class listed */
		*p++ = '\0';
		class = spec;
E 164
		spec = p;
D 164
	}
	else
	{
		/* implicit class */
		class = "implicit";
	}
E 164

D 164
	/* look up class */
	s = stab(class, ST_ALIASCLASS, ST_FIND);
	if (s == NULL)
D 163
		syserr("Unknown alias class %s", class);
E 163
I 163
	{
		if (tTd(27, 1))
			printf("Unknown alias class %s\n", class);
	}
E 163
	else
	{
		ad->ad_class = s->s_aliasclass;
		ad->ad_name = newstr(spec);
		NAliasDBs++;
E 164
I 164
D 201
		if (NAliasDBs >= MAXALIASDB)
E 201
I 201
D 220
		/*
		**  Treat simple filename specially -- this is the file name
		**  for the files implementation, not necessarily in order.
		*/

D 205
		if (spec[0] == '/')
E 205
I 205
		if (spec[0] == '/' && first_unqual)
E 220
I 220
		if (NAliasFileMaps >= MAXMAPSTACK)
E 220
E 205
E 201
		{
D 201
			syserr("Too many alias databases defined, %d max", MAXALIASDB);
			return;
E 201
I 201
D 220
			s = stab("aliases.files", ST_MAP, ST_ENTER);
			map = &s->s_map;
I 205
			first_unqual = FALSE;
E 220
I 220
			syserr("Too many alias databases defined, %d max",
				MAXMAPSTACK);
			return;
E 220
E 205
E 201
		}
D 165
		ad = &AliasDB[NAliasDBs];
E 165
I 165
D 170
		map = &AliasDB[NAliasDBs];
E 170
I 170
D 201
		(void) sprintf(aname, "Alias%d", NAliasDBs);
		s = stab(aname, ST_MAP, ST_ENTER);
		map = &s->s_map;
		AliasDB[NAliasDBs] = map;
E 201
I 201
D 220
		else
E 220
I 220
		if (AliasFileMap == NULL)
E 220
		{
D 220
			char aname[50];

			if (NAliasDBs >= MAXALIASDB)
E 220
I 220
			strcpy(buf, "aliases.files sequence");
			AliasFileMap = makemapentry(buf);
			if (AliasFileMap == NULL)
E 220
			{
D 220
				syserr("Too many alias databases defined, %d max",
					MAXALIASDB);
E 220
I 220
				syserr("setalias: cannot create aliases.files map");
E 220
				return;
			}
D 220
			(void) sprintf(aname, "Alias%d", NAliasDBs);
			s = stab(aname, ST_MAP, ST_ENTER);
			map = &s->s_map;
			AliasDB[NAliasDBs] = map;
E 220
		}
I 220
		(void) sprintf(buf, "Alias%d", NAliasFileMaps);
		s = stab(buf, ST_MAP, ST_ENTER);
		map = &s->s_map;
E 220
E 201
E 170
		bzero(map, sizeof *map);
I 202
		map->map_mname = s->s_name;
E 202
E 165

		p = strpbrk(p, " ,/:");
		if (p != NULL && *p == ':')
		{
D 165
			/* explicit class listed */
E 165
I 165
			/* map name */
E 165
			*p++ = '\0';
			class = spec;
			spec = p;
		}
		else
		{
D 165
			/* implicit class */
E 165
			class = "implicit";
I 165
D 166
			map->map_flags = MF_OPTIONAL;
E 166
I 166
D 167
			map->map_mflags = MF_OPTIONAL;
E 167
I 167
			map->map_mflags = MF_OPTIONAL|MF_INCLNULL;
E 167
E 166
E 165
		}

		/* find end of spec */
		if (p != NULL)
			p = strchr(p, ',');
		if (p != NULL)
			*p++ = '\0';

I 201
		if (tTd(27, 20))
			printf("  map %s:%s %s\n", class, s->s_name, spec);

E 201
		/* look up class */
D 165
		s = stab(class, ST_ALIASCLASS, ST_FIND);
E 165
I 165
		s = stab(class, ST_MAPCLASS, ST_FIND);
E 165
		if (s == NULL)
		{
			if (tTd(27, 1))
				printf("Unknown alias class %s\n", class);
		}
I 166
		else if (!bitset(MCF_ALIASOK, s->s_mapclass.map_cflags))
		{
			syserr("setalias: map class %s can't handle aliases",
				class);
		}
E 166
		else
		{
D 165
			ad->ad_class = s->s_aliasclass;
			ad->ad_name = newstr(spec);
			NAliasDBs++;
E 165
I 165
D 166
			map->map_class = s->s_mapclass;
E 166
I 166
			map->map_class = &s->s_mapclass;
E 166
			if (map->map_class->map_parse(map, spec))
			{
D 166
				map->map_flags |= MF_VALID;
E 166
I 166
				map->map_mflags |= MF_VALID|MF_ALIAS;
E 166
D 201
				NAliasDBs++;
E 201
I 201
D 220
				if (AliasDB[NAliasDBs] == map)
					NAliasDBs++;
E 220
I 220
				AliasFileMap->map_stack[NAliasFileMaps++] = map;
E 220
E 201
			}
E 165
D 170
		}
E 164
	}
E 158
E 123
E 102
}
/*
E 42
**  INITALIASES -- initialize for aliasing
**
D 114
**	Very different depending on whether we are running DBM or not.
E 114
I 114
**	Very different depending on whether we are running NDBM or not.
E 114
**
**	Parameters:
D 158
**		aliasfile -- location of aliases.
I 24
D 114
**		init -- if set and if DBM, initialize the DBM files.
E 114
I 114
**		init -- if set and if NDBM, initialize the NDBM files.
E 158
I 158
**		rebuild -- if TRUE, this rebuilds the cached versions.
**		e -- current envelope.
E 158
E 114
E 24
**
**	Returns:
**		none.
**
**	Side Effects:
**		initializes aliases:
D 114
**		if DBM:  opens the database.
**		if ~DBM: reads the aliases into the symbol table.
E 114
I 114
**		if NDBM:  opens the database.
**		if ~NDBM: reads the aliases into the symbol table.
E 114
*/

D 24
initaliases(aliasfile)
E 24
I 24
D 94
# define DBMMODE	0666
E 94
I 94
D 166
# define DBMMODE	0644
E 94

E 166
D 109
initaliases(aliasfile, init)
E 109
I 109
D 158
initaliases(aliasfile, init, e)
E 109
E 24
	char *aliasfile;
I 24
	bool init;
E 158
I 158
initaliases(rebuild, e)
	bool rebuild;
E 158
I 109
	register ENVELOPE *e;
E 109
E 24
{
I 57
D 98
#ifdef DBM
E 98
I 98
D 114
#if defined(DBM) || defined(NEWDB)
E 114
I 114
D 158
#if defined(NDBM) || defined(NEWDB)
E 114
E 98
E 57
I 53
	int atcnt;
E 53
I 32
D 81
	char buf[MAXNAME];
E 81
D 57
	struct stat stb;
E 57
	time_t modtime;
I 81
	bool automatic = FALSE;
	char buf[MAXNAME];
E 81
I 53
D 73
	int (*oldsigint)();
E 73
I 57
D 98
#endif DBM
E 98
I 98
#endif
E 98
	struct stat stb;
I 87
	static bool initialized = FALSE;
I 97
	static int readaliases();
E 158
I 158
	int dbno;
D 165
	register ALIASDB *ad;
E 165
I 165
	register MAP *map;
E 165
E 158
E 97

I 166
	CurEnv = e;
E 166
D 158
	if (initialized)
		return;
	initialized = TRUE;
E 87
E 57
E 53

I 53
D 71
	if (stat(aliasfile, &stb) < 0)
E 71
I 71
	if (aliasfile == NULL || stat(aliasfile, &stb) < 0)
E 158
I 158
	for (dbno = 0; dbno < NAliasDBs; dbno++)
E 158
E 71
	{
I 81
D 158
		if (aliasfile != NULL && init)
D 135
			syserr("Cannot open %s", aliasfile);
E 135
I 135
			syserr("554 Cannot open %s", aliasfile);
E 135
E 81
		NoAlias = TRUE;
I 62
		errno = 0;
E 62
		return;
	}

I 54
D 98
# ifdef DBM
E 98
I 98
D 114
# if defined(DBM) || defined(NEWDB)
E 114
I 114
# if defined(NDBM) || defined(NEWDB)
E 114
E 98
E 54
E 53
	/*
I 53
	**  Check to see that the alias file is complete.
	**	If not, we will assume that someone died, and it is up
	**	to us to rebuild it.
	*/

D 83
	dbminit(aliasfile);
E 83
I 83
	if (!init)
I 98
	{
# ifdef NEWDB
		(void) strcpy(buf, aliasfile);
		(void) strcat(buf, ".db");
D 101
		AliasDBptr = hash_open(buf, O_RDONLY, DBMMODE, NULL);
E 101
I 101
		AliasDBptr = dbopen(buf, O_RDONLY, DBMMODE, DB_HASH, NULL);
E 101
I 99
		if (AliasDBptr == NULL)
E 158
I 158
D 165
		ad = &AliasDB[dbno];
E 165
I 165
		map = &AliasDB[dbno];
I 166
		if (!bitset(MF_VALID, map->map_mflags))
			continue;
E 166
E 165
I 159

		if (tTd(27, 2))
			printf("initaliases(%s:%s)\n",
D 165
				ad->ad_class->ac_name, ad->ad_name);
E 165
I 165
				map->map_class->map_cname, map->map_file);
E 165

I 166
		/* if already open, close it (for nested open) */
		if (bitset(MF_OPEN, map->map_mflags))
		{
			map->map_class->map_close(map);
			map->map_mflags &= ~(MF_OPEN|MF_WRITABLE);
		}

E 166
E 159
		if (rebuild)
E 158
		{
I 102
D 114
# ifdef DBM
			dbminit(aliasfile);
E 114
I 114
D 158
# ifdef NDBM
			AliasDBMptr = dbm_open(aliasfile, O_RDONLY, DBMMODE);
I 119
			if (AliasDBMptr == NULL)
			{
D 150
				syserr("initaliases: cannot open %s", buf);
E 150
I 150
				syserr("WARNING: initaliases: cannot open %s", buf);
E 150
				NoAlias = TRUE;
				return;
			}
E 119
E 114
# else
E 102
D 150
			syserr("initaliases: cannot open %s", buf);
E 150
I 150
			syserr("WARNING: initaliases: cannot open %s", buf);
E 150
			NoAlias = TRUE;
			return;
I 102
# endif
E 158
I 158
D 165
			rebuildaliases(ad, FALSE, e);
E 165
I 165
D 166
			rebuildaliases(map, FALSE, e);
E 166
I 166
			if (bitset(MCF_REBUILDABLE, map->map_class->map_cflags))
				rebuildaliases(map, FALSE);
E 166
E 165
E 158
E 102
		}
E 99
D 158
# else
E 98
D 114
		dbminit(aliasfile);
E 114
I 114
		AliasDBMptr = dbm_open(aliasfile, O_RDONLY, DBMMODE);
I 119
		if (AliasDBMptr == NULL)
E 158
I 158
		else
E 158
		{
D 127
			syserr("initaliases: cannot open %s", buf);
E 127
I 127
D 150
			syserr("initaliases: cannot open DBM database %s.{pag,dir}",
E 150
I 150
D 158
			syserr("WARNING: initaliases: cannot open DBM database %s.{pag,dir}",
E 150
				aliasfile);
E 127
			NoAlias = TRUE;
			return;
E 158
I 158
D 159
			ad->ad_class->ac_init(ad, e);
E 159
I 159
D 165
			if (ad->ad_class->ac_init(ad, e))
E 165
I 165
			if (map->map_class->map_open(map, O_RDONLY))
E 165
I 163
			{
				if (tTd(27, 4))
					printf("%s:%s: valid\n",
D 165
						ad->ad_class->ac_name,
						ad->ad_name);
E 163
				ad->ad_flags |= ADF_VALID;
E 165
I 165
						map->map_class->map_cname,
						map->map_file);
D 166
				map->map_flags |= MF_VALID;
				aliaswait(map, e);
E 166
I 166
				map->map_mflags |= MF_OPEN;
E 166
E 165
I 163
			}
			else if (tTd(27, 4))
				printf("%s:%s: invalid: %s\n",
D 165
					ad->ad_class->ac_name, ad->ad_name,
E 165
I 165
D 166
					map->map_class->map_cname, map->map_file,
E 166
I 166
					map->map_class->map_cname,
					map->map_file,
E 166
E 165
					errstring(errno));
E 170
E 163
E 159
E 158
		}
E 119
E 114
I 98
D 158
# endif
E 158
	}
I 158
}
/*
**  ALIASWAIT -- wait for distinguished @:@ token to appear.
**
**	This can decide to reopen or rebuild the alias file
I 188
**
**	Parameters:
**		map -- a pointer to the map descriptor for this alias file.
**		ext -- the filename extension (e.g., ".db") for the
**			database file.
**		isopen -- if set, the database is already open, and we
**			should check for validity; otherwise, we are
**			just checking to see if it should be created.
**
**	Returns:
**		TRUE -- if the database is open when we return.
**		FALSE -- if the database is closed when we return.
E 188
*/

D 165
aliaswait(ad, ext, e)
	ALIASDB *ad;
	char *ext;
E 165
I 165
D 166
aliaswait(map, e)
E 166
I 166
D 188
aliaswait(map, ext)
E 188
I 188
bool
aliaswait(map, ext, isopen)
E 188
E 166
	MAP *map;
E 165
D 166
	ENVELOPE *e;
E 166
I 166
	char *ext;
I 188
	int isopen;
E 188
E 166
{
D 190
	int atcnt;
E 190
I 190
	bool attimeout = FALSE;
E 190
	time_t mtime;
	struct stat stb;
D 209
	char buf[MAXNAME];
E 209
I 209
	char buf[MAXNAME + 1];
E 209

I 159
	if (tTd(27, 3))
D 166
		printf("aliaswait\n");
E 166
I 166
		printf("aliaswait(%s:%s)\n",
			map->map_class->map_cname, map->map_file);
I 187
	if (bitset(MF_ALIASWAIT, map->map_mflags))
D 190
		return;
E 190
I 190
		return isopen;
E 190
	map->map_mflags |= MF_ALIASWAIT;
E 187
E 166

E 159
E 158
E 98
E 83
D 54
	for (atcnt = 10; !init && atcnt-- >= 0 && aliaslookup("@") == NULL; )
E 54
I 54
D 70
	atcnt = 10;
	while (SafeAlias && !init && atcnt-- >= 0 && aliaslookup("@") == NULL)
E 54
		sleep(30);
E 70
I 70
D 190
	atcnt = SafeAlias * 2;
	if (atcnt > 0)
E 190
I 190
	if (SafeAlias > 0)
E 190
	{
I 165
		auto int st;
I 190
		time_t toolong = curtime() + SafeAlias;
		unsigned int sleeptime = 2;
E 190

E 165
D 158
		while (!init && atcnt-- >= 0 && aliaslookup("@") == NULL)
E 158
I 158
D 188
		while (atcnt-- >= 0 &&
E 188
I 188
D 190
		while (isopen && atcnt-- >= 0 &&
E 190
I 190
		while (isopen &&
E 190
E 188
D 165
		       ad->ad_class->ac_lookup(ad, "@", e) == NULL)
E 165
I 165
		       map->map_class->map_lookup(map, "@", NULL, &st) == NULL)
E 165
E 158
I 83
		{
I 190
			if (curtime() > toolong)
			{
				/* we timed out */
				attimeout = TRUE;
				break;
			}

E 190
			/*
D 158
			**  Reinitialize alias file in case the new
			**  one is mv'ed in instead of cp'ed in.
			**
			**	Only works with new DBM -- old one will
			**	just consume file descriptors forever.
			**	If you have a dbmclose() it can be
			**	added before the sleep(30).
E 158
I 158
			**  Close and re-open the alias database in case
			**  the one is mv'ed instead of cp'ed in.
E 158
			*/

I 159
			if (tTd(27, 2))
D 190
				printf("aliaswait: sleeping\n");
E 190
I 190
				printf("aliaswait: sleeping for %d seconds\n",
					sleeptime);
E 190

E 159
I 98
D 158
# ifdef NEWDB
D 102
			AliasDBptr->close(AliasDBptr);
E 102
I 102
			if (AliasDBptr != NULL)
				AliasDBptr->close(AliasDBptr);
E 102
# endif
I 114
# ifdef NDBM
			if (AliasDBMptr != NULL)
				dbm_close(AliasDBMptr);
# endif
E 114

E 158
I 158
D 165
			ad->ad_class->ac_close(ad, e);
E 165
I 165
			map->map_class->map_close(map);
I 214
			map->map_mflags &= ~(MF_OPEN|MF_WRITABLE);
E 214
E 165
E 158
E 98
E 83
D 190
			sleep(30);
E 190
I 190
			sleep(sleeptime);
			sleeptime *= 2;
			if (sleeptime > 60)
				sleeptime = 60;
E 190
I 98
D 158
# ifdef NEWDB
			(void) strcpy(buf, aliasfile);
			(void) strcat(buf, ".db");
D 101
			AliasDBptr = hash_open(buf, O_RDONLY, DBMMODE, NULL);
E 101
I 101
			AliasDBptr =
			    dbopen(buf, O_RDONLY, DBMMODE, DB_HASH, NULL);
E 101
I 99
			if (AliasDBptr == NULL)
			{
I 102
# ifdef NDBM
D 114
				dbminit(aliasfile);
E 114
I 114
				AliasDBMptr = dbm_open(aliasfile, O_RDONLY, DBMMODE);
E 114
# else
E 102
D 150
				syserr("initaliases: cannot open %s", buf);
E 150
I 150
				syserr("WARNING: initaliases: cannot open %s", buf);
E 150
				NoAlias = TRUE;
				return;
I 102
# endif
E 102
			}
E 99
# else
E 98
I 83
# ifdef NDBM
D 114
			dbminit(aliasfile);
E 114
I 114
			AliasDBMptr = dbm_open(aliasfile, O_RDONLY, DBMMODE);
I 119
			if (AliasDBMptr == NULL)
			{
D 128
				syserr("initaliases: cannot open %s", buf);
E 128
I 128
D 150
				syserr("initaliases: cannot open DBM database %s.{pag,dir}",
E 150
I 150
				syserr("WARNING: initaliases: cannot open DBM database %s.{pag,dir}",
E 150
					aliasfile);
E 128
				NoAlias = TRUE;
				return;
			}
E 119
E 114
D 98
# endif NDBM
E 98
I 98
# endif
# endif
E 158
I 158
D 165
			ad->ad_class->ac_init(ad, e);
E 165
I 165
D 188
			map->map_class->map_open(map, O_RDONLY);
E 188
I 188
			isopen = map->map_class->map_open(map, O_RDONLY);
E 188
E 165
E 158
E 98
		}
E 83
	}
D 158
	else
		atcnt = 1;
E 158
E 70

D 54
# ifdef DBM
E 54
D 158
	/*
E 53
D 114
	**  See if the DBM version of the file is out of date with
E 114
I 114
	**  See if the NDBM version of the file is out of date with
E 114
	**  the text version.  If so, go into 'init' mode automatically.
D 94
	**	This only happens if our effective userid owns the DBM
D 33
	**	version or if the mode of the database is 777 -- this
E 33
I 33
	**	version or if the mode of the database is 666 -- this
E 33
	**	is an attempt to avoid protection problems.  Note the
	**	unpalatable hack to see if the stat succeeded.
E 94
I 94
	**	This only happens if our effective userid owns the DBM.
	**	Note the unpalatable hack to see if the stat succeeded.
E 94
	*/

D 53
	if (stat(aliasfile, &stb) < 0)
		return;
E 32
# ifdef DBM
E 53
I 24
D 32
	if (init)
E 32
I 32
	modtime = stb.st_mtime;
	(void) strcpy(buf, aliasfile);
I 98
# ifdef NEWDB
	(void) strcat(buf, ".db");
# else
E 98
	(void) strcat(buf, ".pag");
I 98
# endif
E 98
	stb.st_ino = 0;
D 53
	if ((stat(buf, &stb) < 0 || stb.st_mtime < modtime) && !init)
E 53
I 53
D 55
	if ((stat(buf, &stb) < 0 || stb.st_mtime < modtime || atcnt < 0) &&
	    !init)
E 55
I 55
D 72
	if (!init && (atcnt < 0 || stat(buf, &stb) < 0 || stb.st_mtime < modtime))
E 72
I 72
	if (!init && (stat(buf, &stb) < 0 || stb.st_mtime < modtime || atcnt < 0))
E 158
I 158
	/* see if we need to go into auto-rebuild mode */
D 165
	if (stat(ad->ad_name, &stb) < 0)
E 165
I 165
D 166
	if (map->map_class->map_rebuild == NULL ||
	    stat(map->map_file, &stb) < 0)
E 166
I 166
	if (!bitset(MCF_REBUILDABLE, map->map_class->map_cflags))
	{
		if (tTd(27, 3))
			printf("aliaswait: not rebuildable\n");
I 187
		map->map_mflags &= ~MF_ALIASWAIT;
E 187
E 166
E 165
D 188
		return;
E 188
I 188
		return isopen;
E 188
I 166
	}
	if (stat(map->map_file, &stb) < 0)
	{
		if (tTd(27, 3))
			printf("aliaswait: no source file\n");
I 187
		map->map_mflags &= ~MF_ALIASWAIT;
E 187
D 188
		return;
E 188
I 188
		return isopen;
E 188
	}
E 166
	mtime = stb.st_mtime;
D 165
	(void) strcpy(buf, ad->ad_name);
	(void) strcat(buf, ext);
E 165
I 165
	(void) strcpy(buf, map->map_file);
D 166
	if (map->map_class->map_ext != NULL)
		(void) strcat(buf, map->map_class->map_ext);
E 166
I 166
	if (ext != NULL)
		(void) strcat(buf, ext);
E 166
E 165
D 190
	if (stat(buf, &stb) < 0 || stb.st_mtime < mtime || atcnt < 0)
E 190
I 190
	if (stat(buf, &stb) < 0 || stb.st_mtime < mtime || attimeout)
E 190
E 158
E 72
E 55
E 53
E 32
	{
I 62
D 158
		errno = 0;
E 158
I 158
		/* database is out of date */
E 158
E 62
D 32
		char buf[MAXNAME];
E 32
I 32
D 55
		if (stb.st_ino != 0 &&
E 55
I 55
D 94
		if (AutoRebuild && stb.st_ino != 0 &&
E 55
D 33
		    ((stb.st_mode & 0777) == 0777 || stb.st_uid == geteuid()))
E 33
I 33
D 57
		    ((stb.st_mode & 0666) == 0666 || stb.st_uid == geteuid()))
E 57
I 57
		    ((stb.st_mode & 0777) == 0666 || stb.st_uid == geteuid()))
E 94
I 94
		if (AutoRebuild && stb.st_ino != 0 && stb.st_uid == geteuid())
E 94
E 57
E 33
		{
I 206
			bool oldSuprErrs;

E 206
D 158
			init = TRUE;
I 81
			automatic = TRUE;
E 81
D 50
			if (Verbose)
				message(Arpa_Info, "rebuilding alias database");
E 50
I 50
D 135
			message(Arpa_Info, "rebuilding alias database");
E 135
I 135
			message("rebuilding alias database");
E 135
I 77
#ifdef LOG
D 129
			if (LogLevel >= 7)
E 129
I 129
			if (LogLevel > 14)
E 129
				syslog(LOG_INFO, "rebuilding alias database");
D 113
#endif LOG
E 113
I 113
#endif /* LOG */
E 158
I 158
D 165
			message("auto-rebuilding alias database %s",
				ad->ad_name);
			rebuildaliases(ad, TRUE, e);
E 165
I 165
			message("auto-rebuilding alias database %s", buf);
I 206
			oldSuprErrs = SuprErrs;
			SuprErrs = TRUE;
E 206
I 188
			if (isopen)
I 214
			{
E 214
				map->map_class->map_close(map);
I 214
				map->map_mflags &= ~(MF_OPEN|MF_WRITABLE);
			}
E 214
E 188
D 166
			rebuildaliases(map, TRUE, e);
E 166
I 166
			rebuildaliases(map, TRUE);
I 188
			isopen = map->map_class->map_open(map, O_RDONLY);
I 206
			SuprErrs = oldSuprErrs;
E 206
E 188
E 166
E 165
E 158
E 113
E 77
E 50
		}
		else
		{
I 50
D 72
			bool oldverb = Verbose;

			Verbose = TRUE;
E 72
I 72
#ifdef LOG
D 77
			syslog(LOG_INFO, "alias database out of date");
E 77
I 77
D 129
			if (LogLevel >= 7)
E 129
I 129
			if (LogLevel > 3)
E 129
D 158
				syslog(LOG_INFO, "alias database out of date");
E 158
I 158
				syslog(LOG_INFO, "alias database %s out of date",
D 165
					ad->ad_name);
E 165
I 165
					buf);
E 165
E 158
E 77
D 113
#endif LOG
E 113
I 113
#endif /* LOG */
E 113
E 72
E 50
D 135
			message(Arpa_Info, "Warning: alias database out of date");
E 135
I 135
D 158
			message("Warning: alias database out of date");
E 158
I 158
D 165
			message("Warning: alias database %s out of date",
				ad->ad_name);
E 165
I 165
			message("Warning: alias database %s out of date", buf);
E 165
E 158
E 135
I 50
D 72
			Verbose = oldverb;
E 72
E 50
		}
	}
I 187
	map->map_mflags &= ~MF_ALIASWAIT;
I 188
	return isopen;
E 188
E 187
I 158
}
/*
**  REBUILDALIASES -- rebuild the alias database.
**
**	Parameters:
D 165
**		ad -- the database to rebuild.
E 165
I 165
**		map -- the database to rebuild.
E 165
**		automatic -- set if this was automatically generated.
D 166
**		e -- current envelope.
E 166
**
**	Returns:
**		none.
**
**	Side Effects:
**		Reads the text version of the database, builds the
**		DBM or DB version.
*/
E 158
D 53
# endif DBM
E 53
E 32

I 207
void
E 207
I 158
D 165
rebuildaliases(ad, automatic, e)
	register ALIASDB *ad;
E 165
I 165
D 166
rebuildaliases(map, automatic, e)
E 166
I 166
rebuildaliases(map, automatic)
E 166
	register MAP *map;
E 165
	bool automatic;
D 166
	register ENVELOPE *e;
E 166
{
	FILE *af;
I 185
	bool nolock = FALSE;
E 185
D 186
	void (*oldsigint)();
E 186
I 186
D 199
	sigfunc_t oldsigint;
E 199
I 199
	sigfunc_t oldsigint, oldsigquit;
#ifdef SIGTSTP
	sigfunc_t oldsigtstp;
#endif
E 199
E 186
E 158
I 32
D 73
	/*
	**  If initializing, create the new files.
	**	We should lock the alias file here to prevent other
	**	instantiations of sendmail from reading an incomplete
	**	file -- or worse yet, doing a concurrent initialize.
	*/
E 73

D 53
# ifdef DBM
E 53
D 73
	if (init)
	{
I 53
		oldsigint = signal(SIGINT, SIG_IGN);
E 53
E 32
		(void) strcpy(buf, aliasfile);
		(void) strcat(buf, ".dir");
		if (close(creat(buf, DBMMODE)) < 0)
		{
			syserr("cannot make %s", buf);
I 57
			(void) signal(SIGINT, oldsigint);
E 57
			return;
		}
		(void) strcpy(buf, aliasfile);
		(void) strcat(buf, ".pag");
		if (close(creat(buf, DBMMODE)) < 0)
		{
			syserr("cannot make %s", buf);
I 57
			(void) signal(SIGINT, oldsigint);
E 57
			return;
		}
	}
I 32

E 73
D 158
	/*
D 53
	**  Open and, if necessary, load the DBM file.
E 53
I 53
D 114
	**  If necessary, load the DBM file.
E 53
	**	If running without DBM, load the symbol table.
E 114
I 114
	**  If necessary, load the NDBM file.
	**	If running without NDBM, load the symbol table.
E 114
I 53
D 73
	**	After loading the DBM file, add the distinquished alias "@".
E 73
E 53
	*/
E 158
I 158
D 165
	if (!bitset(ACF_BUILDABLE, ad->ad_class->ac_flags))
E 165
I 165
D 166
	if (map->map_class->map_rebuild == NULL)
E 166
I 166
	if (!bitset(MCF_REBUILDABLE, map->map_class->map_cflags))
E 166
E 165
		return;
E 158

E 32
E 24
D 53
	dbminit(aliasfile);
E 53
I 24
D 158
	if (init)
I 53
	{
E 158
I 81
D 184
#ifdef LOG
D 129
		if (LogLevel >= 6)
E 129
I 129
D 158
		if (LogLevel > 7)
E 129
		{
			extern char *username();
E 158
I 158
	if (LogLevel > 7)
	{
D 168
		extern char *username();
E 158

E 168
D 158
			syslog(LOG_NOTICE, "alias database %srebuilt by %s",
				automatic ? "auto" : "", username());
		}
E 158
I 158
		syslog(LOG_NOTICE, "alias database %s %srebuilt by %s",
D 165
			ad->ad_name, automatic ? "auto" : "", username());
E 165
I 165
			map->map_file, automatic ? "auto" : "", username());
E 165
	}
E 158
D 113
#endif LOG
E 113
I 113
#endif /* LOG */
E 113
E 81
D 73
		DATUM key;

E 73
E 53
D 109
		readaliases(aliasfile, TRUE);
E 109
I 109
D 158
		readaliases(aliasfile, TRUE, e);
E 158
I 158

E 184
	/* try to lock the source file */
D 165
	if ((af = fopen(ad->ad_name, "r+")) == NULL)
E 165
I 165
	if ((af = fopen(map->map_file, "r+")) == NULL)
E 165
	{
I 184
D 185
		int saveerr = errno;
E 185
I 185
D 193
		if (errno != EACCES || automatic ||
E 193
I 193
		if ((errno != EACCES && errno != EROFS) || automatic ||
E 193
		    (af = fopen(map->map_file, "r")) == NULL)
		{
			int saveerr = errno;
E 185

E 184
D 163
		syserr("554 Can't open %s", ad->ad_name);
E 163
I 163
D 185
		if (tTd(27, 1))
			printf("Can't open %s: %s\n",
D 165
				ad->ad_name, errstring(errno));
		ad->ad_flags &= ~ADF_VALID;
E 165
I 165
D 184
				map->map_file, errstring(errno));
E 184
I 184
				map->map_file, errstring(saveerr));
		if (!automatic)
			message("newaliases: cannot open %s: %s",
				map->map_file, errstring(saveerr));
E 184
D 166
		map->map_flags &= ~MF_VALID;
E 166
E 165
E 163
D 162
		printf("Can't open %s\n", ad->ad_name);
E 162
		errno = 0;
		return;
E 185
I 185
			if (tTd(27, 1))
				printf("Can't open %s: %s\n",
					map->map_file, errstring(saveerr));
D 208
			if (!automatic)
E 208
I 208
			if (!automatic && !bitset(MF_OPTIONAL, map->map_mflags))
E 208
				message("newaliases: cannot open %s: %s",
					map->map_file, errstring(saveerr));
			errno = 0;
			return;
		}
		nolock = TRUE;
		message("warning: cannot lock %s: %s",
			map->map_file, errstring(errno));
E 185
E 158
E 109
I 53
D 73
		key.dsize = 2;
		key.dptr = "@";
		store(key, key);
		(void) signal(SIGINT, oldsigint);
E 73
	}
E 53
E 24
D 113
# else DBM
E 113
I 113
D 114
# else /* DBM */
E 114
I 114
D 158
# else /* NDBM */
E 114
E 113
I 24
D 109
	readaliases(aliasfile, init);
E 109
I 109
	readaliases(aliasfile, init, e);
E 109
D 113
# endif DBM
E 113
I 113
D 114
# endif /* DBM */
E 114
I 114
# endif /* NDBM */
E 158
I 158

	/* see if someone else is rebuilding the alias file */
D 165
	if (!lockfile(fileno(af), ad->ad_name, LOCK_EX|LOCK_NB))
E 165
I 165
D 183
	if (!lockfile(fileno(af), map->map_file, LOCK_EX|LOCK_NB))
E 183
I 183
D 185
	if (!lockfile(fileno(af), map->map_file, NULL, LOCK_EX|LOCK_NB))
E 185
I 185
	if (!nolock &&
	    !lockfile(fileno(af), map->map_file, NULL, LOCK_EX|LOCK_NB))
E 185
E 183
E 165
	{
		/* yes, they are -- wait until done */
		message("Alias file %s is already being rebuilt",
D 165
			ad->ad_name);
E 165
I 165
			map->map_file);
E 165
		if (OpMode != MD_INITALIAS)
		{
			/* wait for other rebuild to complete */
D 165
			(void) lockfile(fileno(af), ad->ad_name,
E 165
I 165
D 183
			(void) lockfile(fileno(af), map->map_file,
E 183
I 183
			(void) lockfile(fileno(af), map->map_file, NULL,
E 183
E 165
					LOCK_EX);
		}
D 189
		(void) fclose(af);
E 189
I 189
		(void) xfclose(af, "rebuildaliases1", map->map_file);
E 189
		errno = 0;
		return;
	}

I 199
	/* avoid denial-of-service attacks */
	resetlimits();
E 199
D 177
	oldsigint = signal(SIGINT, SIG_IGN);
E 177
I 177
	oldsigint = setsignal(SIGINT, SIG_IGN);
I 199
	oldsigquit = setsignal(SIGQUIT, SIG_IGN);
#ifdef SIGTSTP
	oldsigtstp = setsignal(SIGTSTP, SIG_IGN);
#endif
E 199
E 177

D 162
	ad->ad_class->ac_rebuild(ad, af, e);
E 162
I 162
D 165
	ad->ad_class->ac_rebuild(ad, af, automatic, e);
E 165
I 165
D 166
	map->map_class->map_open(map, O_RDWR);
	if (bitset(MF_VALID, map->map_flags))
E 166
I 166
	if (map->map_class->map_open(map, O_RDWR))
E 166
	{
I 184
#ifdef LOG
		if (LogLevel > 7)
		{
			syslog(LOG_NOTICE, "alias database %s %srebuilt by %s",
				map->map_file, automatic ? "auto" : "",
				username());
		}
#endif /* LOG */
E 184
D 166
		map->map_class->map_rebuild(map, af, automatic);
		readaliases(map, af, automatic, e);
E 166
I 166
		map->map_mflags |= MF_OPEN|MF_WRITABLE;
D 197
		readaliases(map, af, automatic);
E 197
I 197
		readaliases(map, af, !automatic, TRUE);
E 197
E 166
	}
I 166
	else
	{
		if (tTd(27, 1))
			printf("Can't create database for %s: %s\n",
				map->map_file, errstring(errno));
		if (!automatic)
			syserr("Cannot create database for alias file %s",
				map->map_file);
	}
E 166
E 165
E 162

	/* close the file, thus releasing locks */
D 189
	fclose(af);
E 189
I 189
	xfclose(af, "rebuildaliases2", map->map_file);
E 189

	/* add distinguished entries and close the database */
D 160
	ad->ad_class->ac_close(ad, e);
E 160
I 160
D 165
	if (bitset(ADF_VALID, ad->ad_flags))
		ad->ad_class->ac_close(ad, e);
E 165
I 165
D 166
	if (bitset(MF_VALID, map->map_flags))
E 166
I 166
	if (bitset(MF_OPEN, map->map_mflags))
I 214
	{
E 214
E 166
		map->map_class->map_close(map);
I 214
		map->map_mflags &= ~(MF_OPEN|MF_WRITABLE);
	}
E 214
E 165
E 160

D 199
	/* restore the old signal */
E 199
I 199
	/* restore the old signals */
E 199
D 177
	(void) signal(SIGINT, oldsigint);
E 177
I 177
	(void) setsignal(SIGINT, oldsigint);
I 199
	(void) setsignal(SIGQUIT, oldsigquit);
#ifdef SIGTSTP
	(void) setsignal(SIGTSTP, oldsigtstp);
#endif
E 199
E 177
E 158
E 114
E 113
I 53
}
/*
D 56
**  DBMCLOSE -- close the dbm file.
**
**	This is highly implementation dependent.  It should be in the
**	DBM library rather than here.  So why isn't it?
**
**	This is really only needed to save file descriptors.  It can be
**	safely (??) replaced by the null routine.
**
**	Parameters:
**		none.
**
**	Returns:
**		none.
**
**	Side Effects:
**		Closes the DBM file.
*/

dbmclose()
{
	/* hack attack!! -- see comment above */
	extern int pagf, dirf;

	(void) close(pagf);
	(void) close(dirf);
E 53
}
/*
E 56
**  READALIASES -- read and process the alias file.
**
**	This routine implements the part of initaliases that occurs
**	when we are not going to use the DBM stuff.
**
**	Parameters:
D 158
**		aliasfile -- the pathname of the alias file master.
D 114
**		init -- if set, initialize the DBM stuff.
E 114
I 114
**		init -- if set, initialize the NDBM stuff.
E 158
I 158
D 165
**		ad -- the alias database descriptor.
E 165
I 165
**		map -- the alias database descriptor.
E 165
**		af -- file to read the aliases from.
I 162
D 197
**		automatic -- set if this was an automatic rebuild.
E 197
I 197
**		announcestats -- anounce statistics regarding number of
**			aliases, longest alias, etc.
**		logstats -- lot the same info.
E 197
E 162
D 165
**		e -- the current alias file.
E 165
I 165
D 166
**		e -- the current envelope.
E 166
E 165
E 158
E 114
**
**	Returns:
**		none.
**
**	Side Effects:
**		Reads aliasfile into the symbol table.
**		Optionally, builds the .dir & .pag files.
*/

I 207
void
E 207
I 105
D 106
# ifdef LOCKF
# define RDLK_MODE	"r+"
# else
# define RDLK_MODE	"r"
# endif

E 106
E 105
D 165
static
D 109
readaliases(aliasfile, init)
E 109
I 109
D 158
readaliases(aliasfile, init, e)
E 109
	char *aliasfile;
	bool init;
E 158
I 158
D 162
readaliases(ad, af, e)
E 162
I 162
readaliases(ad, af, automatic, e)
E 162
	register ALIASDB *ad;
E 165
I 165
D 166
readaliases(map, af, automatic, e)
E 166
I 166
D 197
readaliases(map, af, automatic)
E 197
I 197
readaliases(map, af, announcestats, logstats)
E 197
E 166
	register MAP *map;
E 165
	FILE *af;
I 162
D 197
	int automatic;
E 197
I 197
	bool announcestats;
	bool logstats;
E 197
E 162
E 158
I 109
D 166
	register ENVELOPE *e;
E 166
E 109
{
E 24
D 57
	char line[BUFSIZ];
E 57
	register char *p;
D 82
	char *p2;
E 82
I 67
	char *lhs;
E 67
	char *rhs;
	bool skipping;
D 57
	ADDRESS al, bl;
E 57
I 57
D 158
	int naliases, bytes, longest;
E 57
D 23
	extern char *prescan();
	bool contin;
E 23
I 23
	FILE *af;
I 108
	bool makedbmfiles;
E 108
I 73
D 95
	int (*oldsigint)();
E 95
I 95
	void (*oldsigint)();
E 158
I 158
	long naliases, bytes, longest;
E 158
E 95
E 73
D 57
	int lineno;
E 57
I 57
	ADDRESS al, bl;
E 57
D 171
	register STAB *s;
E 171
I 98
D 158
# ifdef NEWDB
	DB *dbp;
# endif
I 114
# ifdef NDBM
	DBM *dbmp;
# endif
E 158
E 114
I 106
D 145
# ifdef LOCKF
	struct flock fld;
# endif
E 145
E 106
E 98
I 32
D 57
	int naliases, bytes, longest;
E 57
I 57
	char line[BUFSIZ];
I 145
D 158
	extern bool lockfile();
E 158
E 145
E 57
E 32
E 23

D 105
	if ((af = fopen(aliasfile, "r")) == NULL)
E 105
I 105
D 106
	if ((af = fopen(aliasfile, RDLK_MODE)) == NULL)
E 106
I 106
D 158
	if ((af = fopen(aliasfile, "r+")) == NULL)
E 106
E 105
E 21
E 20
E 14
E 10
E 7
	{
I 10
D 14
		/* if already in AliasQ, don't realias */
		for (q = &AliasQ; (q = nxtinq(q)) != NULL; )
E 14
I 14
D 20
		for (q = Mailer[mno]->m_sendq; q != NULL; q = q->q_next)
E 14
		{
I 16
			To = q->q_paddr;
E 20
I 20
D 21
		To = q->q_paddr;
E 21
I 21
D 92
# ifdef DEBUG
E 92
D 51
		if (Debug)
E 51
I 51
D 119
		if (tTd(27, 1))
E 119
I 119
		if (init)
D 135
			syserr("Can't open %s", aliasfile);
E 135
I 135
			syserr("554 Can't open %s", aliasfile);
E 135
		else if (tTd(27, 1))
E 119
E 51
D 23
			printf("Can't open %s\n", AliasFile);
E 23
I 23
			printf("Can't open %s\n", aliasfile);
E 23
D 92
# endif
E 92
		errno = 0;
		NoAlias++;
		return;
	}
D 31
	/* read and interpret lines */
E 31
I 31

I 73
D 98
# ifdef DBM
E 98
I 98
D 114
# if defined(DBM) || defined(NEWDB)
E 114
I 114
# if defined(NDBM) || defined(NEWDB)
E 114
E 98
D 89
# ifdef FLOCK
E 89
	/* see if someone else is rebuilding the alias file already */
I 103
D 145
# ifdef LOCKF
D 104
	if (lockf(fileno(af), F_TEST, 0) < 0 && errno == EACCES)
E 104
I 104
D 106
	if (lockf(fileno(af), F_TLOCK, 0) < 0)
E 106
I 106
	fld.l_type = F_WRLCK;
	fld.l_whence = fld.l_start = fld.l_len = 0;
	if (fcntl(fileno(af), F_SETLK, &fld) < 0)
E 106
E 104
# else
E 103
	if (flock(fileno(af), LOCK_EX | LOCK_NB) < 0 && errno == EWOULDBLOCK)
I 103
# endif
E 145
I 145
	if (!lockfile(fileno(af), aliasfile, LOCK_EX|LOCK_NB))
E 145
E 103
	{
		/* yes, they are -- wait until done and then return */
D 135
		message(Arpa_Info, "Alias file is already being rebuilt");
E 135
I 135
		message("Alias file is already being rebuilt");
E 135
		if (OpMode != MD_INITALIAS)
		{
			/* wait for other rebuild to complete */
I 103
D 145
# ifdef LOCKF
D 106
			(void) lockf(fileno(af), F_LOCK, 0);
E 106
I 106
			(void) fcntl(fileno(af), F_SETLKW, &fld);
E 106
# else
E 103
			(void) flock(fileno(af), LOCK_EX);
I 103
# endif
E 145
I 145
			(void) lockfile(fileno(af), aliasfile, LOCK_EX);
E 145
E 103
		}
D 76
		fclose(af);
E 76
I 76
		(void) fclose(af);
E 76
		errno = 0;
		return;
	}
D 89
# endif FLOCK
E 89
D 113
# endif DBM
E 113
I 113
D 114
# endif /* DBM */
E 114
I 114
# endif /* NDBM */
E 114
E 113

E 158
E 73
	/*
I 73
D 158
	**  If initializing, create the new DBM files.
	*/

	if (init)
	{
		oldsigint = signal(SIGINT, SIG_IGN);
I 102
# ifdef NEWDB
		(void) strcpy(line, aliasfile);
		(void) strcat(line, ".db");
		dbp = dbopen(line,
		    O_RDWR|O_CREAT|O_TRUNC, DBMMODE, DB_HASH, NULL);
		if (dbp == NULL)
		{
			syserr("readaliases: cannot create %s", line);
			(void) signal(SIGINT, oldsigint);
			return;
		}
D 108
# else
E 102
I 98
# ifdef DBM
E 98
		(void) strcpy(line, aliasfile);
		(void) strcat(line, ".dir");
		if (close(creat(line, DBMMODE)) < 0)
E 108
I 108
# endif
# ifdef IF_MAKEDBMFILES
# ifdef NEWDB
		makedbmfiles = access("/var/yp/Makefile", R_OK) == 0;
# endif
		IF_MAKEDBMFILES
E 108
		{
D 108
			syserr("cannot make %s", line);
			(void) signal(SIGINT, oldsigint);
			return;
E 108
I 108
D 114
			(void) strcpy(line, aliasfile);
			(void) strcat(line, ".dir");
			if (close(creat(line, DBMMODE)) < 0)
E 114
I 114
			dbmp = dbm_open(aliasfile,
					       O_RDWR|O_CREAT|O_TRUNC, DBMMODE);
			if (dbmp == NULL)
E 114
			{
D 114
				syserr("cannot make %s", line);
E 114
I 114
				syserr("readaliases: cannot create %s.{dir,pag}",
					aliasfile);
E 114
				(void) signal(SIGINT, oldsigint);
				return;
			}
D 114
			(void) strcpy(line, aliasfile);
			(void) strcat(line, ".pag");
			if (close(creat(line, DBMMODE)) < 0)
			{
				syserr("cannot make %s", line);
				(void) signal(SIGINT, oldsigint);
				return;
			}
			dbminit(aliasfile);
E 114
E 108
		}
I 83
D 86
		dbminit(aliasfile);
E 86
E 83
D 108
		(void) strcpy(line, aliasfile);
		(void) strcat(line, ".pag");
		if (close(creat(line, DBMMODE)) < 0)
		{
			syserr("cannot make %s", line);
			(void) signal(SIGINT, oldsigint);
			return;
		}
I 86
		dbminit(aliasfile);
E 108
I 98
# endif
D 102
# ifdef NEWDB
		(void) strcpy(line, aliasfile);
		(void) strcat(line, ".db");
D 101
		dbp = hash_open(line, O_RDWR|O_CREAT|O_TRUNC, DBMMODE, NULL);
E 101
I 101
		dbp = dbopen(line,
		    O_RDWR|O_CREAT|O_TRUNC, DBMMODE, DB_HASH, NULL);
E 101
I 99
		if (dbp == NULL)
		{
			syserr("readaliases: cannot create %s", line);
			(void) signal(SIGINT, oldsigint);
			return;
		}
E 102
E 99
D 108
# endif
E 108
E 98
E 86
	}

	/*
E 158
E 73
	**  Read and interpret lines
	*/

E 31
D 57
	lineno = 0;
E 57
I 57
D 158
	FileName = aliasfile;
E 158
I 158
D 165
	FileName = ad->ad_name;
E 165
I 165
	FileName = map->map_file;
E 165
E 158
	LineNumber = 0;
E 57
I 32
	naliases = bytes = longest = 0;
E 32
	skipping = FALSE;
	while (fgets(line, sizeof (line), af) != NULL)
	{
I 32
		int lhssize, rhssize;

E 32
D 57
		lineno++;
E 57
I 57
		LineNumber++;
I 80
D 113
		p = index(line, '\n');
E 113
I 113
		p = strchr(line, '\n');
E 113
		if (p != NULL)
			*p = '\0';
E 80
E 57
		switch (line[0])
		{
		  case '#':
D 80
		  case '\n':
E 80
		  case '\0':
			skipping = FALSE;
			continue;
E 21
E 20

E 16
D 14
			if (sameaddr(q, q2, TRUE))
				break;
		}
		if (q != NULL)
		{
			q2 = nxtinq(q2);
			continue;
		}
E 14
I 14
D 20
			/* don't realias already aliased names */
			if (bitset(QDONTSEND, q->q_flags))
				continue;
E 20
I 20
D 21
		/* don't realias already aliased names */
		if (bitset(QDONTSEND, q->q_flags))
E 21
I 21
		  case ' ':
		  case '\t':
			if (!skipping)
D 57
				syserr("aliases: %d: Non-continuation line starts with space", lineno);
E 57
I 57
D 135
				syserr("Non-continuation line starts with space");
E 135
I 135
				syserr("554 Non-continuation line starts with space");
E 135
E 57
			skipping = TRUE;
E 21
			continue;
I 21
		}
		skipping = FALSE;
E 21
E 20
E 14

E 10
I 7
D 14
		/* save ptr to next address */
I 10
		q = q2;
E 10
		q2 = nxtinq(q);
E 14
I 14
D 20
			/* only alias local users */
D 18
			if (q->q_mailer != 0)
E 18
I 18
			if (q->q_mailer != M_LOCAL)
E 18
				continue;
E 20
I 20
D 21
# ifdef DBM
		/* create a key for fetch */
		lhs.dptr = q->q_user;
		lhs.dsize = strlen(q->q_user) + 1;
		rhs = fetch(lhs);
E 20
E 14

E 7
D 14
		/* only alias local users */
D 13
		if (q->q_mailer != &Mailer[0])
E 13
I 13
		if (q->q_mailer != 0)
E 13
			continue;
E 14
I 14
D 20
			/* create a key for fetch */
			lhs.dptr = q->q_user;
			lhs.dsize = strlen(q->q_user) + 1;
			rhs = fetch(lhs);
E 20
I 20
		/* find this alias? */
		p = rhs.dptr;
		if (p == NULL)
E 21
I 21
D 31
		/* process the LHS */
E 31
I 31
		/*
		**  Process the LHS
I 67
		**
E 67
D 124
		**	Find the final colon, and parse the address.
E 124
I 124
		**	Find the colon separator, and parse the address.
E 124
D 67
		**	It should resolve to a local name -- this will
		**	be checked later (we want to optionally do
		**	parsing of the RHS first to maximize error
		**	detection).
E 67
I 67
		**	It should resolve to a local name.
		**
		**	Alternatively, it can be "@hostname" for host
		**	aliases -- all we do here is map case.  Hostname
		**	need not be a single token.
E 67
		*/

E 31
		for (p = line; *p != '\0' && *p != ':' && *p != '\n'; p++)
E 21
			continue;
D 21
# else DBM
		s = stab(q->q_user, ST_ALIAS, ST_FIND);
		if (s == NULL)
E 21
I 21
D 61
		if (*p == '\0' || *p == '\n')
E 61
I 61
D 67
		if (*p++ != ':')
E 67
I 67
		if (*p != ':')
E 67
E 61
		{
D 57
		 syntaxerr:
D 48
			syserr("aliases: %d: missing colon", lineno);
E 57
I 57
D 135
			syserr("missing colon");
E 135
I 135
			syserr("554 missing colon");
E 135
E 57
E 48
I 48
			syserr("%s, line %d: syntax error", aliasfile, lineno);
E 48
E 21
			continue;
D 21
		p = s->s_alias;
# endif DBM
E 21
I 21
		}
D 60
		*p++ = '\0';
D 59
		if (parse(line, &al, 1) == NULL)
E 59
I 59
		if (parseaddr(line, &al, 1) == NULL)
E 60
I 60
D 67
D 109
		if (parseaddr(line, &al, 1, ':') == NULL)
E 109
I 109
D 140
		if (parseaddr(line, &al, 1, ':', e) == NULL)
E 140
I 140
D 166
		if (parseaddr(line, &al, 1, ':', NULL, e) == NULL)
E 166
I 166
D 179
		if (parseaddr(line, &al, 1, ':', NULL, CurEnv) == NULL)
E 179
I 179
		if (parseaddr(line, &al, RF_COPYALL, ':', NULL, CurEnv) == NULL)
E 179
E 166
E 140
E 109
E 67
I 67
		*p++ = '\0';
		if (line[0] == '@')
E 67
E 60
E 59
		{
D 60
			*--p = ':';
E 60
D 57
			goto syntaxerr;
E 57
I 57
D 67
D 135
			syserr("illegal alias name");
E 135
I 135
D 178
			syserr("554 illegal alias name");
E 178
I 178
D 191
			syserr("554 %s... illegal alias name", al.q_paddr);
E 191
I 191
			syserr("554 %.40s... illegal alias name", line);
E 191
E 178
E 135
			continue;
E 67
I 67
			/* a host alias */
			makelower(line);
			lhs = line;
E 67
E 57
		}
I 66
D 67
D 143
		loweraddr(&al);
E 143
E 67
I 67
		else
		{
			/* a user alias */
			if (parseaddr(line, &al, 1, ':') == NULL)
			{
				syserr("illegal alias name");
				continue;
			}
			loweraddr(&al);
			if (al.q_mailer != LocalMailer)
			{
				syserr("cannot alias non-local names");
				continue;
			}
			lhs = al.q_user;
		}
E 67
E 66
I 31

		/*
		**  Process the RHS.
		**	'al' is the internal form of the LHS address.
		**	'p' points to the text of the RHS.
I 48
		**		'p' may begin with a colon (i.e., the
		**		separator was "::") which will use the
		**		first address as the person to send
		**		errors to -- i.e., designates the
		**		list maintainer.
E 48
		*/

I 149
		while (isascii(*p) && isspace(*p))
			p++;
E 149
I 48
		if (*p == ':')
		{
			ADDRESS *maint;

			while (isspace(*++p))
				continue;
			rhs = p;
			while (*p != '\0' && *p != ',')
				p++;
			if (*p != ',')
				goto syntaxerr;
			*p++ = '\0';
			maint = parse(p, (ADDRESS *) NULL, 1);
			if (maint == NULL)
				syserr("Illegal list maintainer for list %s", al.q_user);
			else if (CurEnv->e_returnto == &CurEnv->e_from)
			{
				CurEnv->e_returnto = maint;
				MailBack++;
			}
		}
			
E 48
E 31
		rhs = p;
D 23
		contin = FALSE;
E 23
		for (;;)
		{
			register char c;
I 142
			register char *nlp;
E 142
E 21
E 20
E 14

I 142
			nlp = &p[strlen(p)];
			if (nlp[-1] == '\n')
				*--nlp = '\0';

E 142
I 23
D 24
# ifdef SECURE
E 23
D 14
		/* create a key for fetch */
		lhs.dptr = q->q_user;
		lhs.dsize = strlen(q->q_user) + 1;
D 6
		lhs.dptr = line;
E 6
		rhs = fetch(lhs);
E 14
I 14
D 20
			/* find this alias? */
			p = rhs.dptr;
			if (p == NULL)
				continue;
E 20
I 20
D 21
		/*
		**  Match on Alias.
		**	Deliver to the target list.
		**	Remove the alias from the send queue
		**	  and put it on the Alias queue.
		*/
E 21
I 21
			/* do parsing & compression of addresses */
			c = *p;
			while (c != '\0')
E 24
I 24
D 84
			if (init)
E 84
I 84
D 158
			if (init && CheckAliases)
E 158
I 158
			if (CheckAliases)
E 158
E 84
E 24
			{
D 24
				p2 = p;
				while (*p != '\n' && *p != ',' && *p != '\0')
					p++;
E 24
I 24
				/* do parsing & compression of addresses */
E 24
D 80
				c = *p;
D 24
				*p++ = '\0';
				if (*p2 == '\0')
E 24
I 24
				while (c != '\0')
E 80
I 80
				while (*p != '\0')
E 80
E 24
				{
I 24
D 80
					p2 = p;
					while (*p != '\n' && *p != ',' && *p != '\0')
E 80
I 80
D 140
					extern char *DelimChar;
E 140
I 140
					auto char *delimptr;
E 140

D 130
					while (isspace(*p) || *p == ',')
E 130
I 130
					while ((isascii(*p) && isspace(*p)) ||
								*p == ',')
E 130
E 80
						p++;
D 80
					c = *p;
D 69
					*p++ = '\0';
E 69
I 32
					if (c == '\n')
						c = '\0';
E 32
D 69
					if (*p2 == '\0')
					{
						p[-1] = c;
						continue;
					}
D 31
					parse(p2, &bl, -1);
E 31
I 31
D 59
					(void) parse(p2, &bl, -1);
E 59
I 59
D 60
					(void) parseaddr(p2, &bl, -1);
E 60
I 60
					(void) parseaddr(p2, &bl, -1, ',');
E 60
E 59
E 31
E 24
					p[-1] = c;
D 24
					continue;
E 24
I 24
					while (isspace(*p))
						p++;
E 69
I 69
					*p = '\0';
D 77
					if (*p2 != '\0')
						(void) parseaddr(p2, &bl, -1, ',');
E 77
I 77
					if (*p2 != '\0' &&
					    parseaddr(p2, &bl, -1, ',') == NULL)
					{
						usrerr("%s... bad address");
					}
E 77
					if (c != '\0')
						*p++ = c;
I 79
					while (isspace(*p))
						p++;
E 80
I 80
					if (*p == '\0')
						break;
D 109
					if (parseaddr(p, &bl, -1, ',') == NULL)
E 109
I 109
D 140
					if (parseaddr(p, &bl, -1, ',', e) == NULL)
E 140
I 140
D 166
					if (parseaddr(p, &bl, -1, ',', &delimptr, e) == NULL)
E 166
I 166
D 179
					if (parseaddr(p, &bl, -1, ',', &delimptr, CurEnv) == NULL)
E 179
I 179
					if (parseaddr(p, &bl, RF_COPYNONE, ',',
						      &delimptr, CurEnv) == NULL)
E 179
E 166
E 140
E 109
D 135
						usrerr("%s... bad address", p);
E 135
I 135
						usrerr("553 %s... bad address", p);
E 135
D 140
					p = DelimChar;
E 140
I 140
					p = delimptr;
E 140
E 80
E 79
E 69
E 24
				}
D 24
				parse(p2, &bl, -1);
D 23
				contin = (c == ',');
E 23
				p[-1] = c;
				while (isspace(*p))
					p++;
E 24
			}
I 23
D 24
# else SECURE
			p = &p[strlen(p)];
# endif SECURE
E 24
I 24
			else
D 64
				p = &p[strlen(p)];
E 64
I 64
			{
D 68
				p = &p[strlen(p) - 1];
				*p = '\0';
E 68
I 68
D 142
				p = &p[strlen(p)];
				if (p[-1] == '\n')
					*--p = '\0';
E 142
I 142
				p = nlp;
E 142
E 68
			}
E 64
E 24
E 23
E 21
E 20
E 14

D 14
		/* find this alias? */
		p = rhs.dptr;
		if (p == NULL)
			continue;
E 14
I 14
D 20
			/*
			**  Match on Alias.
			**	Deliver to the target list.
			**	Remove the alias from the send queue
			**	  and put it on the Alias queue.
			*/
E 14

E 20
D 14
		/*
		**  Match on Alias.
		**	Deliver to the target list.
		**	Remove the alias from the send queue
		**	  and put it on the Alias queue.
		*/

E 14
D 21
# ifdef DEBUG
D 14
		if (Debug)
			printf("%s (%s, %s) aliased to %s\n",
			    q->q_paddr, q->q_host, q->q_user, p);
E 14
I 14
D 20
			if (Debug)
				printf("%s (%s, %s) aliased to %s\n",
				    q->q_paddr, q->q_host, q->q_user, p);
E 20
I 20
		if (Debug)
			printf("%s (%s, %s) aliased to %s\n",
			    q->q_paddr, q->q_host, q->q_user, p);
E 20
E 14
# endif
I 16
D 20
			if (Verbose)
				message("050", "aliased to %s", p);
E 16
D 14
		tkoffq(q, &SendQ);
D 10
		putonq(q, &AliasQ);
E 10
		sendto(p, 1);
I 10
		putonq(q, &AliasQ);
E 10
I 8

		/* if our last entry had an alias, process them */
		if (q2 == NULL)
			q2 = nxtinq(&SendQ);
E 14
I 14
			q->q_flags |= QDONTSEND;
			sendto(p, 1);
		}
E 20
I 20
		if (Verbose)
			message("050", "aliased to %s", p);
		q->q_flags |= QDONTSEND;
		sendto(p, 1);
E 21
I 21
			/* see if there should be a continuation line */
D 23
			if (!contin)
E 23
I 23
D 217
			c = fgetc(af);
E 217
I 217
			c = getc(af);
E 217
			if (!feof(af))
D 31
				ungetc(c, af);
E 31
I 31
				(void) ungetc(c, af);
E 31
			if (c != ' ' && c != '\t')
E 23
				break;

			/* read continuation line */
D 68
			p--;
E 68
			if (fgets(p, sizeof line - (p - line), af) == NULL)
				break;
D 57
			lineno++;
E 57
I 57
			LineNumber++;
I 116

			/* check for line overflow */
			if (strchr(p, '\n') == NULL)
			{
D 135
				usrerr("alias too long");
E 135
I 135
				usrerr("554 alias too long");
E 135
				break;
			}
E 116
E 57
D 23

			if (!isspace(*p))
				syserr("aliases: %d: continuation line missing", lineno);
E 23
		}
D 29
		if (al.q_mailer != M_LOCAL)
E 29
I 29
D 38
		if (al.q_mailer != MN_LOCAL)
E 38
I 38
D 67
D 200
		if (al.q_mailer != LocalMailer)
E 200
I 200
		if (!bitnset(M_ALIASABLE, al.q_mailer->m_flags))
E 200
E 38
E 29
		{
D 57
			syserr("aliases: %d: cannot alias non-local names", lineno);
E 57
I 57
D 135
			syserr("cannot alias non-local names");
E 135
I 135
D 178
			syserr("554 cannot alias non-local names");
E 178
I 178
			syserr("554 %s... cannot alias non-local names",
				al.q_paddr);
E 178
E 135
E 57
			continue;
		}
E 67
I 31

		/*
		**  Insert alias into symbol table or DBM file
		*/

I 32
D 67
D 158
		lhssize = strlen(al.q_user) + 1;
E 158
I 121
		if (!bitnset(M_USR_UPPER, al.q_mailer->m_flags))
			makelower(al.q_user);
E 121
E 67
I 67
		lhssize = strlen(lhs) + 1;
E 67
D 158
		rhssize = strlen(rhs) + 1;
E 158

E 32
E 31
D 23
		s = stab(al.q_user, ST_ALIAS, rhs);
E 23
I 23
D 24
		s = stab(al.q_user, ST_ALIAS, ST_ENTER);
		s->s_alias = newstr(rhs);
E 24
I 24
D 98
# ifdef DBM
E 98
I 98
D 114
# if defined(DBM) || defined(NEWDB)
E 114
I 114
D 158
# if defined(NDBM) || defined(NEWDB)
E 114
E 98
		if (init)
		{
D 98
			DATUM key, content;
E 98
I 98
D 114
			DBT key, content;
E 114
I 114
			DBdatum key, content;
I 121
			int putstat;
E 158
I 158
		lhssize = strlen(al.q_user);
		rhssize = strlen(rhs);
D 165
		ad->ad_class->ac_store(ad, al.q_user, rhs, e);
E 165
I 165
		map->map_class->map_store(map, al.q_user, rhs);
E 165
E 158
E 121
E 114
E 98

D 32
			key.dsize = strlen(al.q_user) + 1;
E 32
I 32
D 98
			key.dsize = lhssize;
E 32
			key.dptr = al.q_user;
D 32
			content.dsize = strlen(rhs) + 1;
E 32
I 32
			content.dsize = rhssize;
E 32
			content.dptr = rhs;
E 98
I 98
D 114
			key.size = lhssize;
			key.data = al.q_user;
			content.size = rhssize;
			content.data = rhs;
E 114
I 114
D 158
			key.xx.size = lhssize;
			key.xx.data = al.q_user;
			content.xx.size = rhssize;
			content.xx.data = rhs;
E 114
D 102
# ifdef DBM
E 98
			store(key, content);
I 98
# else
E 102
I 102
# ifdef NEWDB
E 102
D 101
			if (dbp->put(dbp, &key, &content, R_PUT) != 0)
E 101
I 101
D 114
			if (dbp->put(dbp, &key, &content, 0) != 0)
E 114
I 114
D 121
			if (dbp->put(dbp, &key.dbt, &content.dbt, 0) != 0)
E 121
I 121
			putstat = dbp->put(dbp, &key.dbt, &content.dbt,
					   R_NOOVERWRITE);
			if (putstat > 0)
			{
D 127
				usrerr("Warning: duplicate alias name %s",
E 127
I 127
				usrerr("050 Warning: duplicate alias name %s",
E 127
					al.q_user);
				putstat = dbp->put(dbp, &key.dbt,
						   &content.dbt, 0);
			}
			if (putstat != 0)
E 121
E 114
E 101
D 99
			{
				syserr("cannot put alias %s", al.q_user);
			}
E 99
I 99
				syserr("readaliases: db put (%s)", al.q_user);
I 102
D 108
# else
			store(key, content);
E 108
E 102
E 99
# endif
I 108
# ifdef IF_MAKEDBMFILES
			IF_MAKEDBMFILES
D 114
				store(key, content);
E 114
I 114
D 121
				if (dbm_store(dbmp, key.dbm, content.dbm, DBM_REPLACE) != 0)
E 121
I 121
			{
				putstat = dbm_store(dbmp, key.dbm, content.dbm,
						    DBM_INSERT);
				if (putstat > 0)
				{
D 127
					usrerr("Warning: duplicate alias name %s",
E 127
I 127
					usrerr("050 Warning: duplicate alias name %s",
E 127
						al.q_user);
					putstat = dbm_store(dbmp, key.dbm,
							content.dbm, DBM_REPLACE);
				}
				if (putstat != 0)
E 121
					syserr("readaliases: dbm store (%s)",
						al.q_user);
I 121
			}
E 121
E 114
# endif
I 121
			if (al.q_paddr != NULL)
				free(al.q_paddr);
			if (al.q_host != NULL)
				free(al.q_host);
			if (al.q_user != NULL)
				free(al.q_user);
E 121
E 108
E 98
		}
		else
D 113
# endif DBM
E 113
I 113
D 114
# endif /* DBM */
E 114
I 114
# endif /* NDBM */
E 114
E 113
		{
			s = stab(al.q_user, ST_ALIAS, ST_ENTER);
			s->s_alias = newstr(rhs);
		}
E 158
I 158
		if (al.q_paddr != NULL)
			free(al.q_paddr);
		if (al.q_host != NULL)
			free(al.q_host);
		if (al.q_user != NULL)
			free(al.q_user);
E 158
I 32

		/* statistics */
		naliases++;
		bytes += lhssize + rhssize;
		if (rhssize > longest)
			longest = rhssize;
E 32
E 24
E 23
E 21
E 20
E 14
E 8
	}
I 73

D 98
# ifdef DBM
E 98
I 98
D 114
# if defined(DBM) || defined(NEWDB)
E 114
I 114
D 158
# if defined(NDBM) || defined(NEWDB)
E 114
E 98
	if (init)
E 158
I 158
D 166
	e->e_to = NULL;
E 166
I 166
	CurEnv->e_to = NULL;
E 166
	FileName = NULL;
D 162
	message("%s: %d aliases, longest %d bytes, %d bytes total",
E 162
I 162
D 197
	if (Verbose || !automatic)
E 197
I 197
	if (Verbose || announcestats)
E 197
		message("%s: %d aliases, longest %d bytes, %d bytes total",
E 162
D 165
			ad->ad_name, naliases, longest, bytes);
E 165
I 165
			map->map_file, naliases, longest, bytes);
E 165
# ifdef LOG
D 197
	if (LogLevel > 7)
E 197
I 197
	if (LogLevel > 7 && logstats)
E 197
		syslog(LOG_INFO, "%s: %d aliases, longest %d bytes, %d bytes total",
D 165
			ad->ad_name, naliases, longest, bytes);
E 165
I 165
			map->map_file, naliases, longest, bytes);
E 165
# endif /* LOG */
D 165
}
/*
**  NDBM modules
*/

#ifdef NDBM

/*
**  NDBM_ALOOKUP -- look up alias in ndbm file
*/

char *
ndbm_alookup(ad, name, e)
	register ALIASDB *ad;
	char *name;
	ENVELOPE *e;
{
	int i;
	datum rhs, lhs;
	char keybuf[MAXNAME + 1];

I 159
	if (tTd(27, 20))
		printf("ndbm_lookup(%s)\n", name);

E 159
	/* create a key for fetch */
	i = strlen(name) + 1;
	if (i > sizeof keybuf)
		i = sizeof keybuf;
	bcopy(name, keybuf, i);
	if (!bitnset(M_USR_UPPER, LocalMailer->m_flags))
		makelower(keybuf);

	lhs.dsize = i;
	lhs.dptr = keybuf;
	rhs = dbm_fetch((DBM *) ad->ad_dbp, lhs);
	return (rhs.dptr);
}


/*
**  NDBM_ASTORE -- store a datum in the database
*/

void
ndbm_astore(ad, lhs, rhs, e)
	register ALIASDB *ad;
	char *lhs;
	char *rhs;
	ENVELOPE *e;
{
	datum key;
	datum data;
	int stat;

D 159
	key.dsize = strlen(lhs);
E 159
I 159
	key.dsize = strlen(lhs) + 1;
E 159
	key.dptr = lhs;

D 159
	data.dsize = strlen(rhs);
E 159
I 159
	data.dsize = strlen(rhs) + 1;
E 159
	data.dptr = rhs;

	stat = dbm_store((DBM *) ad->ad_dbp, key, data, DBM_INSERT);
	if (stat > 0)
E 158
	{
D 158
		/* add the distinquished alias "@" */
D 98
		DATUM key;
E 98
I 98
D 114
		DBT key;
E 114
I 114
		DBdatum key;
E 158
I 158
		usrerr("050 Warning: duplicate alias name %s", lhs);
		stat = dbm_store((DBM *) ad->ad_dbp, key, data, DBM_REPLACE);
	}
	if (stat != 0)
		syserr("readaliases: dbm put (%s)", lhs);
}
E 158
E 114
E 98

D 98
		key.dsize = 2;
		key.dptr = "@";
E 98
I 98
D 114
		key.size = 2;
		key.data = "@";
E 114
I 114
D 158
		key.xx.size = 2;
		key.xx.data = "@";
E 114
# ifdef NEWDB
D 99
		dbp->put(dbp, &key, &key, R_PUT);
		dbp->close(dbp);
E 99
I 99
		if (dbp->sync(dbp) != 0 ||
D 101
		    dbp->put(dbp, &key, &key, R_PUT) != 0 ||
E 101
I 101
D 114
		    dbp->put(dbp, &key, &key, 0) != 0 ||
E 114
I 114
		    dbp->put(dbp, &key.dbt, &key.dbt, 0) != 0 ||
E 114
E 101
		    dbp->close(dbp) != 0)
			syserr("readaliases: db close failure");
E 99
D 108
# else
E 108
I 108
# endif
D 111
# ifdef MAKEDBMFILES
E 111
I 111
# ifdef IF_MAKEDBMFILES
E 111
E 108
E 98
D 112
		store(key, key);
E 112
I 112
		IF_MAKEDBMFILES
D 114
			store(key, key);
E 114
I 114
		{
E 158
I 158

/*
**  NDBM_AINIT -- initialize DBM database
*/

bool
ndbm_ainit(ad, e)
	register ALIASDB *ad;
	ENVELOPE *e;
{
	char buf[MAXNAME];

I 159
	if (tTd(27, 2))
		printf("ndbm_ainit(%s)\n", ad->ad_name);

E 159
	/* open the database */
	ad->ad_dbp = (void *) dbm_open(ad->ad_name, O_RDONLY, DBMMODE);
	if (ad->ad_dbp == NULL)
		return FALSE;
D 159
	ad->ad_flags |= ADF_VALID;
E 159

	/* wait for @:@ to appear */
	aliaswait(ad, ".pag", e);

	return TRUE;
}


/*
**  NDBM_AREBUILD -- rebuild hash database
*/

void
D 162
ndbm_arebuild(ad, fp, e)
E 162
I 162
ndbm_arebuild(ad, fp, automatic, e)
E 162
	register ALIASDB *ad;
	FILE *fp;
I 162
	int automatic;
E 162
	ENVELOPE *e;
{
	register DBM *db;
	int i;
	char buf[MAXNAME];

I 159
	if (tTd(27, 2))
		printf("ndbm_arebuild(%s)\n", ad->ad_name);

E 159
	db = dbm_open(ad->ad_name, O_RDWR|O_CREAT|O_TRUNC, DBMMODE);
	if (db == NULL)
	{
D 160
		syserr("readaliases: cannot create %s", buf);
E 160
I 160
		syserr("ndbm_arebuild: cannot create %s", buf);
E 160
		return;
	}
	ad->ad_dbp = (void *) db;
D 159
	ad->ad_flags |= ADF_VALID|ADF_WRITABLE;
E 159
I 159
D 160
	ad->ad_flags |= ADF_WRITABLE;
E 160
I 160
	ad->ad_flags |= ADF_WRITABLE|ADF_VALID;
E 160
E 159

	/* read and store the aliases */
D 162
	readaliases(ad, fp, e);
E 162
I 162
	readaliases(ad, fp, automatic, e);
E 162
}

/*
**  NDBM_ACLOSE -- close the database
*/

void
ndbm_aclose(ad, e)
	register ALIASDB  *ad;
	ENVELOPE *e;
{
	if (bitset(ADF_WRITABLE, ad->ad_flags))
	{
E 158
I 131
#ifdef YPCOMPAT
I 147
D 151
			static void nis_magic P((DBM *dbmp));
E 151
I 151
D 158
			static void nis_magic __P((DBM *dbmp));
E 158
I 158
		char buf[200];
E 158
E 151

E 147
D 158
			nis_magic(dbmp);
E 158
I 158
		(void) sprintf(buf, "%010ld", curtime());
		ndbm_astore(ad, "YP_LAST_MODIFIED", buf, e);

		(void) myhostname(buf, sizeof buf);
		ndbm_astore(ad, "YP_MASTER_NAME", buf, e);
E 158
#endif
E 131
D 158
			if (dbm_store(dbmp, key.dbm, key.dbm, DBM_REPLACE) != 0 ||
			    dbm_error(dbmp))
				syserr("readaliases: dbm close failure");
			dbm_close(dbmp);
		}
E 114
E 112
I 98
# endif
E 158
E 98

D 158
		/* restore the old signal */
		(void) signal(SIGINT, oldsigint);
E 158
I 158
		/* write out the distinguished alias */
		ndbm_astore(ad, "@", "@", e);
E 158
	}
D 113
# endif DBM
E 113
I 113
D 114
# endif /* DBM */
E 114
I 114
D 158
# endif /* NDBM */
E 158
I 158
	dbm_close((DBM *) ad->ad_dbp);
}
E 158
E 114
E 113

D 158
	/* closing the alias file drops the lock */
E 73
I 21
	(void) fclose(af);
I 32
D 44
	To = NULL;
E 44
I 44
D 109
	CurEnv->e_to = NULL;
E 109
I 109
	e->e_to = NULL;
E 109
I 57
	FileName = NULL;
E 57
E 44
D 50
	if (Verbose)
		message(Arpa_Info, "%d aliases, longest %d bytes, %d bytes total",
E 50
I 50
D 135
	message(Arpa_Info, "%d aliases, longest %d bytes, %d bytes total",
E 135
I 135
	message("%d aliases, longest %d bytes, %d bytes total",
E 135
E 50
			naliases, longest, bytes);
I 77
# ifdef LOG
D 129
	if (LogLevel >= 8)
E 129
I 129
	if (LogLevel > 7)
E 129
		syslog(LOG_INFO, "%d aliases, longest %d bytes, %d bytes total",
			naliases, longest, bytes);
D 113
# endif LOG
E 113
I 113
# endif /* LOG */
E 158
I 158
#endif
/*
**  HASH (NEWDB) Modules
*/

#ifdef NEWDB

/*
**  HASH_ALOOKUP -- look up alias in hash file
*/

char *
hash_alookup(ad, name, e)
	register ALIASDB *ad;
	char *name;
	ENVELOPE *e;
{
	int i;
	DBT rhs, lhs;
	int s;
	char keybuf[MAXNAME + 1];

I 159
	if (tTd(27, 20))
		printf("hash_alookup(%s)\n", name);

E 159
	/* create a key for fetch */
	i = strlen(name) + 1;
	if (i > sizeof keybuf)
		i = sizeof keybuf;
	bcopy(name, keybuf, i);
	if (!bitnset(M_USR_UPPER, LocalMailer->m_flags))
		makelower(keybuf);

	lhs.size = i;
	lhs.data = keybuf;
	i = ad->ad_ndbp->get(ad->ad_ndbp, &lhs, &rhs, 0);
	if (i == 0)
		return (rhs.data);
	return (NULL);
E 158
E 113
E 77
E 32
D 24
# endif DBM
E 24
E 21
D 20
#endif DBM
E 20
E 5
E 4
}
I 158


/*
**  HASH_ASTORE -- store a datum in the database
*/

void
hash_astore(ad, lhs, rhs, e)
	register ALIASDB *ad;
	char *lhs;
	char *rhs;
	ENVELOPE *e;
{
	int stat;
	DBT key;
	DBT data;

D 159
	key.size = strlen(lhs);
E 159
I 159
	if (tTd(27, 20))
		printf("hash_astore(%s, %s)\n", lhs, rhs);

	key.size = strlen(lhs) + 1;
E 159
	key.data = lhs;

D 159
	data.size = strlen(rhs);
E 159
I 159
	data.size = strlen(rhs) + 1;
E 159
	data.data = rhs;

	stat = ad->ad_ndbp->put(ad->ad_ndbp, &key, &data, R_NOOVERWRITE);
	if (stat > 0)
	{
		usrerr("050 Warning: duplicate alias name %s", lhs);
		stat = ad->ad_ndbp->put(ad->ad_ndbp, &key, &data, 0);
	}
	if (stat != 0)
		syserr("readaliases: db put (%s)", lhs);
}


/*
**  HASH_AINIT -- initialize hash database
*/

bool
hash_ainit(ad, e)
	register ALIASDB *ad;
	ENVELOPE *e;
{
	char buf[MAXNAME];

I 159
	if (tTd(27, 2))
		printf("hash_ainit(%s)\n", ad->ad_name);

E 159
	/* open the database */
	(void) strcpy(buf, ad->ad_name);
	(void) strcat(buf, ".db");
	ad->ad_ndbp = dbopen(buf, O_RDONLY, DBMMODE, DB_HASH, NULL);
	if (ad->ad_ndbp == NULL)
		return FALSE;
D 159
	ad->ad_flags |= ADF_VALID;
E 159

	/* wait for @:@ to appear */
	aliaswait(ad, ".db", e);
	return TRUE;
}


/*
**  HASH_AREBUILD -- rebuild hash database
*/

void
D 162
hash_arebuild(ad, fp, e)
E 162
I 162
hash_arebuild(ad, fp, automatic, e)
E 162
	register ALIASDB *ad;
	FILE *fp;
I 162
	int automatic;
E 162
	ENVELOPE *e;
{
	register DB *db;
	char buf[MAXNAME];

I 159
	if (tTd(27, 2))
		printf("hash_arebuild(%s)\n", ad->ad_name);

I 160
	(void) strcpy(buf, ad->ad_name);
	(void) strcat(buf, ".db");
E 160
E 159
	db = dbopen(buf, O_RDWR|O_CREAT|O_TRUNC, DBMMODE, DB_HASH, NULL);
	if (db == NULL)
	{
D 160
		syserr("readaliases: cannot create %s", buf);
E 160
I 160
		syserr("hash_arebuild: cannot create %s", buf);
E 160
		return;
	}
	ad->ad_ndbp = db;
D 159
	ad->ad_flags |= ADF_VALID|ADF_WRITABLE;
E 159
I 159
D 160
	ad->ad_flags |= ADF_WRITABLE;
E 160
I 160
	ad->ad_flags |= ADF_WRITABLE|ADF_VALID;
E 160
E 159

	/* read and store the aliases */
D 162
	readaliases(ad, fp, e);
E 162
I 162
	readaliases(ad, fp, automatic, e);
E 162
}


/*
**  HASH_ACLOSE -- add distinguished entries and close the database
*/

void
hash_aclose(ad, e)
	ALIASDB *ad;
	ENVELOPE *e;
{
I 159
	if (tTd(27, 9))
		printf("hash_aclose(%x)\n", ad->ad_flags);

E 159
	if (bitset(ADF_WRITABLE, ad->ad_flags))
	{
		/* write out the distinguished alias */
		hash_astore(ad, "@", "@", e);
	}

	if (ad->ad_ndbp->close(ad->ad_ndbp) != 0)
		syserr("readaliases: db close failure");
}

#endif
E 158
/*
I 131
D 158
**  NIS_MAGIC -- Add NIS magic dbm data
E 158
I 158
**  STAB (Symbol Table) Modules
*/


/*
**  STAB_ALOOKUP -- look up alias in symbol table
*/

char *
stab_alookup(ad, name, e)
	register ALIASDB *ad;
	char *name;
	ENVELOPE *e;
{
	register STAB *s;

I 159
	if (tTd(27, 20))
		printf("stab_lookup(%s)\n", name);

E 159
	s = stab(name, ST_ALIAS, ST_FIND);
	if (s != NULL)
		return (s->s_alias);
	return (NULL);
}


/*
**  STAB_ASTORE -- store in symtab (actually using during init, not rebuild)
*/

void
stab_astore(ad, lhs, rhs, e)
	register ALIASDB *ad;
	char *lhs;
	char *rhs;
	ENVELOPE *e;
{
	register STAB *s;

	s = stab(lhs, ST_ALIAS, ST_ENTER);
	s->s_alias = newstr(rhs);
}


/*
**  STAB_AINIT -- initialize (reads data file)
*/

bool
stab_ainit(ad, e)
	register ALIASDB *ad;
	ENVELOPE *e;
{
	FILE *af;

I 159
	if (tTd(27, 2))
		printf("stab_ainit(%s)\n", ad->ad_name);

E 159
	af = fopen(ad->ad_name, "r");
	if (af == NULL)
D 163
	{
		syserr("554 Can't open %s", ad->ad_name);
		errno = 0;
E 163
		return FALSE;
D 163
	}
E 163
D 159
	ad->ad_flags |= ADF_VALID;
E 159

D 162
	readaliases(ad, af, e);
E 162
I 162
	readaliases(ad, af, TRUE, e);
E 162
}


/*
**  STAB_AREBUILD -- rebuild alias file
*/

void
D 162
stab_arebuild(ad, fp, e)
E 162
I 162
stab_arebuild(ad, fp, automatic, e)
E 162
	ALIASDB *ad;
	FILE *fp;
I 162
	int automatic;
E 162
	ENVELOPE *e;
{
D 159
	ad->ad_flags |= ADF_VALID|ADF_WRITABLE;
E 159
I 159
	if (tTd(27, 2))
		printf("stab_arebuild(%s)\n", ad->ad_name);

D 160
	ad->ad_flags |= ADF_WRITABLE;
E 160
I 160
	ad->ad_flags |= ADF_WRITABLE|ADF_VALID;
E 160
E 159
}


/*
**  STAB_ACLOSE -- close symbol table (???)
*/

void
stab_aclose(ad, e)
	ALIASDB *ad;
	ENVELOPE *e;
{
	/* ignore it */
}
/*
**  NIS Modules
*/

D 161
#ifdef NIS
E 161
I 161
#ifdef NIS_ALIASES
E 161

/*
**  NIS_ALOOKUP
*/

char *
nis_alookup(ad, name, e)
	ALIASDB *ad;
	char *name;
	ENVELOPE *e;
{
	auto char *vp;
	auto int vsize;
I 163
	int yperr;
	int keylen;
E 163

I 159
	if (tTd(27, 20))
		printf("nis_lookup(%s)\n", name);

E 159
D 163
	if (ypmatch(ad->ad_domain, ad->ad_name, name, strlen(name),
			&vp, &vsize) != 0)
		return NULL;
	return vp;
E 163
I 163
	keylen = strlen(name);
	yperr = yp_match(ad->ad_domain, ad->ad_name, name, keylen,
			&vp, &vsize);
	if (yperr == YPERR_KEY)
		yperr = yp_match(ad->ad_domain, ad->ad_name, name, ++keylen,
				&vp, &vsize);
	if (yperr == 0)
		return vp;

	if (tTd(27, 10))
		printf("nis_alookup: yp_match(%s, %s, %s) => %s\n",
			ad->ad_domain, ad->ad_name, name, yperr_string(yperr));
	if (yperr != YPERR_KEY && yperr != YPERR_BUSY)
		ad->ad_flags &= ~ADF_VALID;
	return NULL;
E 163
}

/*
**  NIS_ASTORE
*/

void
nis_astore(ad, lhs, rhs, e)
	ALIASDB *ad;
	char *lhs;
	char *rhs;
	ENVELOPE *e;
{
	/* nothing */
}

/*
**  NIS_AINIT
*/

bool
nis_ainit(ad, e)
	ALIASDB *ad;
	ENVELOPE *e;
{
	register char *p;
D 163
	auto char *ypmaster;
E 163
I 163
	int yperr;
	auto char *vp;
	auto int vsize;
E 163

I 159
	if (tTd(27, 2))
		printf("nis_ainit(%s)\n", ad->ad_name);

E 159
	p = strchr(ad->ad_name, '@');
	if (p != NULL)
	{
		*p++ = '\0';
		if (*p != '\0')
			ad->ad_domain = p;
	}
	if (ad->ad_domain == NULL)
		yp_get_default_domain(&ad->ad_domain);

	if (*ad->ad_name == '\0')
		ad->ad_name = "mail.aliases";

D 163
	yperr = yp_master(ad->ad_domain, ad->ad_name, &ypmaster);
	return (yperr == 0);
E 163
I 163
	yperr = yp_match(ad->ad_domain, ad->ad_name, "@", 1,
			&vp, &vsize);
	if (tTd(27, 10))
		printf("nis_ainit: yp_match(%s, %s) => %s\n",
			ad->ad_domain, ad->ad_name, yperr_string(yperr));
	if (yperr == 0 || yperr == YPERR_KEY || yperr == YPERR_BUSY)
		return TRUE;
	return FALSE;
E 163
}

/*
**  NIS_AREBUILD
*/

void
D 162
nis_arebuild(ad, fp, e)
E 162
I 162
nis_arebuild(ad, fp, automatic, e)
E 162
	ALIASDB *ad;
	FILE *fp;
I 162
	int automatic;
E 162
	ENVELOPE *e;
{
I 159
	if (tTd(27, 2))
		printf("nis_arebuild(%s)\n", ad->ad_name);
D 160

E 159
	/* nothing */
E 160
}


/*
**  NIS_ACLOSE
*/

void
nis_aclose(ad, e)
	ALIASDB *ad;
	ENVELOPE *e;
{
	/* nothing */
}

D 161
#endif /* NIS */
E 161
I 161
#endif /* NIS_ALIASES */
E 161
/*
**  Implicit Modules
E 158
**
D 158
**	This adds the magic entries needed by SunOS to make this a valid
**	NIS map.
**
**	Parameters:
**		dbmp -- a pointer to the DBM structure.
**
**	Returns:
**		none.
E 158
I 158
**	Tries several types.  For back compatibility.
E 158
*/

D 158
# ifdef YPCOMPAT
E 158
I 158
/*
**  IMPL_ALOOKUP -- lookup in best open database
*/
E 158

D 158
static void
nis_magic(dbmp)
	DBM *dbmp;
E 158
I 158
char *
impl_alookup(ad, name, e)
	ALIASDB *ad;
	char *name;
	ENVELOPE *e;
E 158
{
I 159
	if (tTd(27, 20))
		printf("impl_lookup(%s)\n", name);

E 159
D 158
	int i;
	static datum key[2] =
E 158
I 158
#ifdef NEWDB
	if (bitset(ADF_IMPLHASH, ad->ad_flags))
		return hash_alookup(ad, name, e);
#endif
#ifdef NDBM
	if (bitset(ADF_IMPLNDBM, ad->ad_flags))
		return ndbm_alookup(ad, name, e);
#endif
	return stab_alookup(ad, name, e);
}

/*
**  IMPL_ASTORE -- store in open databases
*/

void
impl_astore(ad, lhs, rhs, e)
	ALIASDB *ad;
	char *lhs;
	char *rhs;
	ENVELOPE *e;
{
#ifdef NEWDB
	if (bitset(ADF_IMPLHASH, ad->ad_flags))
		hash_astore(ad, lhs, rhs, e);
#endif
#ifdef NDBM
	if (bitset(ADF_IMPLNDBM, ad->ad_flags))
		ndbm_astore(ad, lhs, rhs, e);
#endif
	stab_astore(ad, lhs, rhs, e);
}

/*
**  IMPL_AINIT -- implicit database lookup
*/

bool
impl_ainit(ad, e)
	ALIASDB *ad;
	ENVELOPE *e;
{
I 162
	struct stat stb;

E 162
I 159
	if (tTd(27, 2))
		printf("impl_ainit(%s)\n", ad->ad_name);

E 159
D 162
	/* implicit class */
E 162
I 162
	if (stat(ad->ad_name, &stb) < 0)
	{
		/* no alias file at all */
		return FALSE;
	}

E 162
#ifdef NEWDB
I 159
	ad->ad_flags |= ADF_IMPLHASH;
E 159
	if (hash_ainit(ad, e))
E 158
	{
D 158
		{ "YP_LAST_MODIFIED",	sizeof "YP_LAST_MODIFIED" - 1 },
		{ "YP_MASTER_NAME",	sizeof "YP_MASTER_NAME" - 1 },
	};
	datum contents[2];
	char tbuf[12];
	char hbuf[MAXHOSTNAMELEN];
E 158
I 158
D 159
		ad->ad_flags |= ADF_VALID|ADF_IMPLHASH;
		NAliasDBs++;
		return;
E 159
I 159
		return TRUE;
E 159
	}
I 159
	ad->ad_flags &= ~ADF_IMPLHASH;
E 159
#endif
#ifdef NDBM
I 159
	ad->ad_flags |= ADF_IMPLNDBM;
E 159
	if (ndbm_ainit(ad, e))
	{
D 159
		ad->ad_flags |= ADF_VALID|ADF_IMPLNDBM;
		NAliasDBs++;
		return;
E 159
I 159
		return TRUE;
E 159
	}
I 159
	ad->ad_flags &= ~ADF_IMPLNDBM;
E 159
#endif
D 162
	syserr("WARNING: cannot open alias database %s", ad->ad_name);
E 162
E 158

I 162
	if (Verbose)
		message("WARNING: cannot open alias database %s", ad->ad_name);

E 162
D 158
	(void) sprintf(tbuf, "%010ld", curtime());
	contents[0].dptr = tbuf;
	contents[0].dsize = strlen(tbuf);
E 158
I 158
	if (stab_ainit(ad, e))
	{
D 159
		ad->ad_flags |= ADF_VALID;
		NAliasDBs++;
		return;
E 159
I 159
		return TRUE;
E 159
	}
I 159

	return FALSE;
E 159
}
E 158

D 158
	(void) myhostname(hbuf, sizeof hbuf);
	contents[1].dptr = hbuf;
D 147
	contents[1].dptr = strlen(hbuf);
E 147
I 147
	contents[1].dsize = strlen(hbuf);
E 158
I 158
/*
**  IMPL_AREBUILD -- rebuild alias database
*/
E 158
E 147

D 158
	for (i = 0; i < sizeof key / sizeof *key; i++)
E 158
I 158
void
D 162
impl_arebuild(ad, fp, e)
E 162
I 162
impl_arebuild(ad, fp, automatic, e)
E 162
	ALIASDB *ad;
	FILE *fp;
I 162
	int automatic;
E 162
	ENVELOPE *e;
{
#ifdef NEWDB
	DB *ndb;
	char buf[MAXNAME];
I 159
#endif
E 159

I 159
	if (tTd(27, 2))
		printf("impl_arebuild(%s)\n", ad->ad_name);

#ifdef NEWDB
E 159
	(void) strcpy(buf, ad->ad_name);
	(void) strcat(buf, ".db");
	ndb = dbopen(buf, O_RDWR|O_CREAT|O_TRUNC, DBMMODE, DB_HASH, NULL);
	if (ndb == NULL)
E 158
	{
D 158
		if (dbm_store(dbmp, key[i], contents[i], DBM_REPLACE) != 0 ||
		    dbm_error(dbmp))
			syserr("nis_magic: dbm_store failure");
E 158
I 158
		syserr("rebuildaliases: cannot create %s", buf);
E 158
	}
I 158
	else
	{
		ad->ad_ndbp = ndb;
		ad->ad_flags |= ADF_IMPLHASH;
#if defined(NDBM) && defined(YPCOMPAT)
		if (access("/var/yp/Makefile", R_OK) != 0)
D 159
			return;
E 159
#endif
I 159
			goto readem;
E 159
	}
#endif

#ifdef NDBM
	ad->ad_dbp = (void *) dbm_open(ad->ad_name, O_RDWR|O_CREAT|O_TRUNC, DBMMODE);
	if (ad->ad_dbp == NULL)
	{
		syserr("rebuildaliases: cannot create %s.{pag,dir}",
			ad->ad_name);
	}
	else
	{
		ad->ad_flags |= ADF_IMPLNDBM;
	}
#endif

	if (!bitset(ADF_IMPLHASH|ADF_IMPLNDBM, ad->ad_flags))
		return;

D 159
	ad->ad_flags |= ADF_VALID|ADF_WRITABLE;
E 159
I 159
  readem:
D 160
	ad->ad_flags |= ADF_WRITABLE;
E 160
I 160
	ad->ad_flags |= ADF_WRITABLE|ADF_VALID;
E 160
E 159

	/* read and store aliases */
D 162
	readaliases(ad, fp, e);
E 162
I 162
	readaliases(ad, fp, automatic, e);
E 162
E 158
}

D 158
# endif
E 158
I 158

/*
**  IMPL_ACLOSE -- close any open database(s)
*/

void
impl_aclose(ad, e)
	ALIASDB *ad;
	ENVELOPE *e;
{
#ifdef NEWDB
D 159
	hash_aclose(ad, e);
E 159
I 159
	if (bitset(ADF_IMPLHASH, ad->ad_flags))
		hash_aclose(ad, e);
E 159
#endif

#ifdef NDBM
D 159
	ndbm_aclose(ad, e);
E 159
I 159
	if (bitset(ADF_IMPLNDBM, ad->ad_flags))
		ndbm_aclose(ad, e);
E 159
#endif
}
/*
**  SETUPALIASES -- set up aliases classes
*/

#ifdef NEWDB
ALIASCLASS	HashAClass =
{
	"hash",		hash_alookup,	hash_astore,
	hash_ainit,	hash_arebuild,	hash_aclose,
	ACF_BUILDABLE
};
#endif

#ifdef NDBM
ALIASCLASS	DbmAClass =
{
	"dbm",		ndbm_alookup,	ndbm_astore,
	ndbm_ainit,	ndbm_arebuild,	ndbm_aclose,
	ACF_BUILDABLE
};
#endif

D 161
#ifdef NIS
E 161
I 161
#ifdef NIS_ALIASES
E 161
ALIASCLASS	NisAClass =
{
	"nis",		nis_alookup,	nis_astore,
	nis_ainit,	nis_arebuild,	nis_aclose,
	0
};
#endif

ALIASCLASS	StabAClass =
{
	"stab",		stab_alookup,	stab_astore,
	stab_ainit,	stab_arebuild,	stab_aclose,
	0
};

ALIASCLASS	ImplAClass =
{
	"implicit",	impl_alookup,	impl_astore,
	impl_ainit,	impl_arebuild,	impl_aclose,
	ACF_BUILDABLE
};

setupaliases()
{
	register STAB *s;

#ifdef NEWDB
	s = stab("hash", ST_ALIASCLASS, ST_ENTER);
	s->s_aliasclass = &HashAClass;
#endif

#ifdef NDBM
	s = stab("dbm", ST_ALIASCLASS, ST_ENTER);
	s->s_aliasclass = &DbmAClass;
#endif

D 161
#ifdef NIS
E 161
I 161
#ifdef NIS_ALIASES
E 161
	s = stab("nis", ST_ALIASCLASS, ST_ENTER);
	s->s_aliasclass = &NisAClass;
#endif

#if !defined(NEWDB) && !defined(NDBM)
	s = stab("stab", ST_ALIASCLASS, ST_ENTER);
	s->s_aliasclass = &StabAClass;
#endif

	s = stab("implicit", ST_ALIASCLASS, ST_ENTER);
	s->s_aliasclass = &ImplAClass;
E 165
}
E 158
/*
E 131
**  FORWARD -- Try to forward mail
**
**	This is similar but not identical to aliasing.
**
D 21
**	Currently it is undefined, until the protocol for userinfo
**	databases is finalized.
**
E 21
**	Parameters:
D 31
**		user -- the name of the user who's mail we
**			would like to forward to.
E 31
I 31
**		user -- the name of the user who's mail we would like
**			to forward to.  It must have been verified --
**			i.e., the q_home field must have been filled
**			in.
I 40
**		sendq -- a pointer to the head of the send queue to
**			put this user's aliases in.
I 203
**		aliaslevel -- the current alias nesting depth.
**		e -- the current envelope.
E 203
E 40
E 31
**
**	Returns:
D 21
**		TRUE -- we have forwarded it somewhere.
**		FALSE -- not forwarded; go ahead & deliver.
E 21
I 21
**		none.
E 21
**
**	Side Effects:
D 14
**		New names are added to SendQ.
**
D 3
**	Requires:
**		none
**
E 3
**	Called By:
**		recipient
E 14
I 14
**		New names are added to send queues.
I 21
D 36
**		Sets the QDONTSEND bit in addresses that are forwarded.
E 36
E 21
E 14
D 3
**
**	History:
**		3/5/80 -- return value changed.
**		1/23/80 -- null version written.
E 3
*/

I 207
void
E 207
D 21
bool
E 21
D 40
forward(user)
E 40
I 40
D 109
forward(user, sendq)
E 109
I 109
D 203
forward(user, sendq, e)
E 203
I 203
forward(user, sendq, aliaslevel, e)
E 203
E 109
E 40
D 11
	addrq *user;
E 11
I 11
	ADDRESS *user;
I 40
	ADDRESS **sendq;
I 203
	int aliaslevel;
E 203
I 109
	register ENVELOPE *e;
E 109
E 40
E 11
{
D 17
	return (FALSE);
E 17
I 17
D 18
	register struct passwd *pw;
	char buf[50];
E 18
I 18
D 117
	char buf[60];
E 117
I 117
	char *pp;
	char *ep;
I 173
D 174
#ifdef _POSIX_SAVED_IDS
E 174
I 174
D 176
#ifdef HASSETEUID
E 176
I 176
D 182
#ifdef HASSETREUID
E 176
E 174
	register ADDRESS *ca;
	uid_t saveduid, uid;
I 181
	gid_t savedgid, gid;
E 181
#endif
E 182
E 173
E 117
E 18
D 31
	register FILE *fp;
	register char *p;
E 31
I 30
D 37
	struct stat stbuf;
E 37
I 37
D 138
	extern bool safefile();
E 138
E 37
E 30
D 18
	extern struct passwd *getpwnam();
E 18
D 19
	extern char *index();
E 19

I 21
D 92
# ifdef DEBUG
E 92
D 51
	if (Debug)
E 51
I 51
	if (tTd(27, 1))
E 51
		printf("forward(%s)\n", user->q_paddr);
D 92
# endif DEBUG
E 92

E 21
D 18
	if (user->q_mailer != 0)
E 18
I 18
D 29
	if (user->q_mailer != M_LOCAL || bitset(QBADADDR, user->q_flags))
E 29
I 29
D 38
	if (user->q_mailer != MN_LOCAL || bitset(QBADADDR, user->q_flags))
E 38
I 38
D 200
	if (user->q_mailer != LocalMailer || bitset(QBADADDR, user->q_flags))
E 200
I 200
	if (!bitnset(M_HASPWENT, user->q_mailer->m_flags) ||
	    bitset(QBADADDR, user->q_flags))
E 200
E 38
E 29
E 18
D 21
		return (FALSE);
E 21
I 21
		return;
I 31
D 92
# ifdef DEBUG
E 92
	if (user->q_home == NULL)
I 131
	{
E 131
D 135
		syserr("forward: no home");
E 135
I 135
		syserr("554 forward: no home");
E 135
I 131
		user->q_home = "/nosuchdirectory";
	}
E 131
D 92
# endif DEBUG
E 92
E 31
E 21

D 18
	/* find the user's home directory */
	pw = getpwnam(user->q_user);
	if (pw == NULL)
	{
		/* bad address -- mark it */
		user->q_flags |= QBADADDR;
		return (FALSE);
	}

E 18
	/* good address -- look for .forward file in home */
I 22
D 57
	define('z', user->q_home);
E 57
I 57
D 109
	define('z', user->q_home, CurEnv);
E 57
E 22
D 18
	user->q_flags |= QGOODADDR;
	sprintf(buf, "%s/.forward", pw->pw_dir);
E 18
I 18
D 19
	expand("$z/.forward", buf, &buf[sizeof buf - 1]);
E 19
I 19
D 45
	(void) expand("$z/.forward", buf, &buf[sizeof buf - 1]);
E 45
I 45
D 65
	expand("$z/.forward", buf, &buf[sizeof buf - 1], CurEnv);
E 65
I 65
	expand("\001z/.forward", buf, &buf[sizeof buf - 1], CurEnv);
E 65
E 45
E 19
E 18
D 27
	fp = fopen(buf, "r");
	if (fp == NULL)
E 27
I 27
D 30
	if (access(buf, 4) < 0)
E 30
I 30
D 37
	if (stat(buf, &stbuf) < 0 || stbuf.st_uid != user->q_uid ||
	    !bitset(S_IREAD, stbuf.st_mode))
E 37
I 37
D 107
	if (!safefile(buf, user->q_uid, S_IREAD))
E 37
E 30
E 27
D 21
		return (FALSE);
E 21
I 21
		return;
E 21

	/* we do have an address to forward to -- do it */
I 21
D 36
	user->q_flags |= QDONTSEND;
E 36
E 21
D 19
	fgets(buf, sizeof buf, fp);
E 19
I 19
D 27
	(void) fgets(buf, sizeof buf, fp);
E 19
	if ((p = index(buf, '\n')) != NULL)
		*p = '\0';
D 19
	fclose(fp);
E 19
I 19
	(void) fclose(fp);
E 19
	if (buf[0] == '\0')
D 21
		return (FALSE);
E 21
I 21
		return;
E 21
	if (Verbose)
D 25
		message("050", "forwarded to %s", buf);
E 25
I 25
		message(Arpa_Info, "forwarded to %s", buf);
E 25
I 21
	AliasLevel++;
E 21
	sendto(buf, 1);
D 21
	return (TRUE);
E 21
I 21
	AliasLevel--;
	return;
E 27
I 27
D 34
	include(buf, "forwarding");
E 34
I 34
D 40
	include(buf, "forwarding", user);
E 40
I 40
	include(buf, "forwarding", user, sendq);
E 107
I 107
	include(buf, TRUE, user, sendq);
E 109
I 109
	define('z', user->q_home, e);
D 117
	expand("\001z/.forward", buf, &buf[sizeof buf - 1], e);
	include(buf, TRUE, user, sendq, e);
E 117
I 117
	define('u', user->q_user, e);
	define('h', user->q_host, e);
	if (ForwardPath == NULL)
D 130
		ForwardPath = newstr("\001z/.forward");
E 130
I 130
		ForwardPath = newstr("\201z/.forward");
E 130

I 173
D 174
#ifdef _POSIX_SAVED_IDS
E 174
I 174
D 176
#ifdef HASSETEUID
E 176
I 176
D 182
#ifdef HASSETREUID
E 176
E 174
	ca = getctladdr(user);
	if (ca != NULL)
I 181
	{
E 181
		uid = ca->q_uid;
I 181
		gid = ca->q_gid;
	}
E 181
	else
I 181
	{
E 181
		uid = DefUid;
I 181
		gid = DefGid;
	}
E 181
#endif

E 182
E 173
	for (pp = ForwardPath; pp != NULL; pp = ep)
	{
I 138
		int err;
E 138
D 118
		char buf[256];
E 118
I 118
		char buf[MAXPATHLEN+1];
I 207
		extern int include();
E 207
I 138
D 141
		extern bool transienterror();
E 141
E 138
E 118

		ep = strchr(pp, ':');
		if (ep != NULL)
			*ep = '\0';
D 210
		expand(pp, buf, &buf[sizeof buf - 1], e);
E 210
I 210
		expand(pp, buf, sizeof buf, e);
E 210
		if (ep != NULL)
			*ep++ = ':';
		if (tTd(27, 3))
			printf("forward: trying %s\n", buf);
I 173

D 174
#ifdef _POSIX_SAVED_IDS
E 174
I 174
D 182
		if (tTd(27, 9))
			printf("forward: old uid = %d/%d\n", getuid(), geteuid());

D 176
#ifdef HASSETEUID
E 176
I 176
#ifdef HASSETREUID
E 176
E 174
		saveduid = geteuid();
D 181
		if (saveduid == 0 && uid != 0)
D 176
			(void) seteuid(uid);
E 176
I 176
			(void) setreuid(0, uid);
E 181
I 181
		savedgid = getegid();
		if (saveduid == 0)
		{
			if (ca != NULL)
				initgroups(ca->ca_user, gid);
			else if (gid != 0)
				setgid(gid);
			if (uid != 0)
				(void) setreuid(0, uid);
		}
E 181
E 176
#endif                   

I 174
		if (tTd(27, 9))
			printf("forward: new uid = %d/%d\n", getuid(), geteuid());

E 182
E 174
E 173
D 138
		if (include(buf, TRUE, user, sendq, e) == 0)
E 138
I 138
D 203
		err = include(buf, TRUE, user, sendq, e);
E 203
I 203
		err = include(buf, TRUE, user, sendq, aliaslevel, e);
E 203
I 173
D 182

D 174
#ifdef _POSIX_SAVED_IDS
E 174
I 174
D 176
#ifdef HASSETEUID
E 176
I 176
#ifdef HASSETREUID
E 176
E 174
D 181
		if (saveduid == 0 && uid != 0)
D 174
			(void) seteuid(saveduid);
E 174
I 174
D 176
			if (seteuid(saveduid) < 0)
				syserr("seteuid(%d) failure (real=%d, eff=%d)",
					saveduid, getuid(), geteuid());
E 176
I 176
			if (setreuid(-1, 0) < 0 || setreuid(RealUid, 0) < 0)
				syserr("setreuid(%d, 0) failure (real=%d, eff=%d)",
					RealUid, getuid(), geteuid());
E 181
I 181
		if (saveduid == 0)
		{
			if (uid != 0)
				if (setreuid(-1, 0) < 0 || setreuid(RealUid, 0) < 0)
					syserr("setreuid(%d, 0) failure (real=%d, eff=%d)",
						RealUid, getuid(), geteuid());
			setgid(savedgid);
		}
E 181
E 176
E 174
#endif
I 174

		if (tTd(27, 9))
			printf("forward: reset uid = %d/%d\n", getuid(), geteuid());
E 174

E 182
E 173
		if (err == 0)
E 138
			break;
I 138
D 182
		if (transienterror(err))
E 182
I 182
		else if (transienterror(err))
E 182
		{
			/* we have to suspend this message */
I 153
			if (tTd(27, 2))
				printf("forward: transient error on %s\n", buf);
#ifdef LOG
			if (LogLevel > 2)
D 155
				syslog(LOG_NOTICE, "%s: forward %s: transient error: %e",
E 155
I 155
D 157
				syslog(LOG_ERR, "%s: forward %s: transient error: %e",
E 155
					e->e_id, buf);
E 157
I 157
				syslog(LOG_ERR, "%s: forward %s: transient error: %s",
D 195
					e->e_id, buf, errstring(err));
E 195
I 195
					e->e_id == NULL ? "NOQUEUE" : e->e_id,
					buf, errstring(err));
E 195
E 157
#endif
D 154
			message("%s: %s: message queued", buf, strerror(err));
E 154
I 154
			message("%s: %s: message queued", buf, errstring(err));
E 154
E 153
D 175
			user->q_flags |= QQUEUEUP|QDONTSEND;
E 175
I 175
			user->q_flags |= QQUEUEUP;
E 175
			return;
		}
E 138
	}
E 117
E 109
E 107
I 67
}
/*
**  MAPHOST -- given a host description, produce a mapping.
**
**	This is done by looking up the name in the alias file,
**	preceeded by an "@".  This can be used for UUCP mapping.
**	For example, a call with {blia, ., UUCP} as arguments
**	might return {ucsfcgl, !, blia, ., UUCP} as the result.
**
**	We first break the input into three parts -- before the
**	lookup, the lookup itself, and after the lookup.  We
**	then do the lookup, concatenate them together, and rescan
**	the result.
**
**	Parameters:
**		pvp -- the parameter vector to map.
**
**	Returns:
**		The result of the mapping.  If nothing found, it
**		should just concatenate the three parts together and
**		return that.
**
**	Side Effects:
**		none.
*/

char **
maphost(pvp)
	char **pvp;
{
	register char **avp;
	register char **bvp;
	char *p;
	char buf1[MAXNAME];
	char buf2[MAXNAME];
	char buf3[MAXNAME];
	extern char **prescan();

	/*
	**  Extract the three parts of the input as strings.
	*/

	/* find the part before the lookup */
	for (bvp = pvp; *bvp != NULL && **bvp != MATCHLOOKUP; bvp++)
		continue;
	if (*bvp == NULL)
		return (pvp);
	p = *bvp;
	*bvp = NULL;
	cataddr(pvp, buf1, sizeof buf1);
	*bvp++ = p;

	/* find the rest of the lookup */
	for (avp = bvp; *pvp != NULL && **bvp != MATCHELOOKUP; bvp++)
		continue;
	if (*bvp == NULL)
		return (pvp);
	p = *bvp;
	*bvp = NULL;
	cataddr(avp, buf2, sizeof buf2);
	*bvp++ = p;

	/* save the part after the lookup */
	cataddr(bvp, buf3, sizeof buf3);

	/*
	**  Now look up the middle part.
	*/

	p = aliaslookup(buf2);
	if (p != NULL)
		strcpy(buf2, p);

	/*
	**  Put the three parts back together and break into tokens.
	*/

	strcat(buf1, buf2);
	strcat(buf1, buf3);
	avp = prescan(buf1, '\0');

	/* return this mapping */
	return (avp);
E 67
I 42
}
D 49
/*
**  HOSTALIAS -- alias a host name
**
**	Given a host name, look it up in the host alias table
**	and return it's value.  If nothing, return NULL.
**
**	Parameters:
**		a -- address to alias.
**
**	Returns:
**		text result of aliasing.
**		NULL if none.
**
**	Side Effects:
**		none.
*/

char *
hostalias(a)
	register ADDRESS *a;
{
	char buf[MAXNAME+2];
	register char *p;

D 47
	strcpy(buf, "/");
	strcat(buf, a->q_host);
E 47
I 47
	(void) strcpy(buf, "/");
	(void) strcat(buf, a->q_host);
E 47
	makelower(buf);

	p = aliaslookup(buf);
	if (p == NULL)
		return (NULL);
D 43
	sprintf(buf, p, a->q_user);
E 43
I 43
	(void) sprintf(buf, p, a->q_user);
E 43
	return (newstr(buf));
E 42
E 40
E 34
E 27
E 21
E 17
}
E 49
E 1
