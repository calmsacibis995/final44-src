h00634
s 00001/00000/01950
d D 8.78 95/06/21 07:12:35 eric 204 203
c close passwd file before setuid() "just in case"
e
s 00010/00004/01940
d D 8.77 95/06/20 10:42:11 eric 203 202
c more hacks to make /usr/tmp/dead.letter work right
e
s 00003/00003/01941
d D 8.76 95/06/13 09:23:03 eric 202 201
c make a bunch of #defines into 0/1 instead of ifdef/ifndef
e
s 00001/00002/01943
d D 8.75 95/06/05 07:21:55 eric 201 200
c avoid infinite loops if malloc fails
e
s 00000/00001/01945
d D 8.74 95/05/30 19:24:16 eric 200 199
c change RealUserName from an array to a pointer; move defn to sendmail.h
e
s 00005/00001/01941
d D 8.73 95/05/30 07:08:41 eric 199 198
c don't shorten names that have a trailing dot (except for the dot itself)
e
s 00015/00005/01927
d D 8.72 95/05/28 11:49:48 eric 198 197
c lint
e
s 00003/00002/01929
d D 8.71 95/05/25 16:17:52 eric 197 196
c woops -- previous patch didn't null terminate in all cases
e
s 00002/00001/01929
d D 8.70 95/05/25 15:54:43 eric 196 195
c don't trash lines without trailing newlines
e
s 00001/00001/01929
d D 8.69 95/05/24 16:23:44 eric 195 194
c null delimiter can be newline as well as space or tab
e
s 00001/00016/01929
d D 8.68 95/05/15 15:02:05 eric 194 193
c add "E" line to config file to set or propogate environment
c variables to children
e
s 00134/00000/01811
d D 8.67 95/05/14 08:42:49 eric 193 192
c implement Fx|prog and "program" map class
e
s 00037/00000/01774
d D 8.66 95/05/13 15:06:06 eric 192 191
c put getcanonname into service switch
e
s 00027/00006/01747
d D 8.65 95/04/22 10:53:03 eric 191 190
c fixes to MIME code
e
s 00001/00001/01752
d D 8.64 95/04/21 09:57:26 eric 190 189
c update copyright notice
e
s 00002/00002/01751
d D 8.63 95/04/19 11:50:23 eric 189 188
c better messages if getsockname or getpeername fail
e
s 00017/00014/01736
d D 8.62 95/04/11 06:52:58 eric 188 187
c don't do a gethostbyaddr call on unix domain sockets during state dump
e
s 00004/00004/01746
d D 8.61 95/03/31 15:29:25 eric 187 186
c compile problem on some old platforms
e
s 00002/00002/01748
d D 8.60 95/03/31 15:22:58 eric 186 185
c change "bool" to be an int -- prototypes just don't grok it otherwise
e
s 00002/00003/01748
d D 8.59 95/03/31 10:52:06 eric 185 184
c pull getpwXXX and gethostbyXXX calls out into conf.c so they can
c be tweaked
e
s 00019/00000/01732
d D 8.58 95/03/11 13:42:42 eric 184 183
c fix several MIME boundary-condition problems
e
s 00016/00005/01716
d D 8.57 95/03/10 12:21:57 eric 183 182
c improved security when opening files
e
s 00002/00003/01719
d D 8.56 95/03/07 16:43:22 eric 182 181
c fix bug in xputs -- wasn't properly printing \n, \r, or \t
e
s 00139/00013/01583
d D 8.55 95/03/06 15:11:57 eric 181 180
c fix some race conditions for file opens
e
s 00000/00000/01596
d D 8.54 95/03/05 11:57:13 eric 180 178
i 179
c add "strict" parameter to denlstring to allow continuations
e
s 00009/00003/01523
d D 8.39.1.5 95/03/05 10:09:59 eric 179 177
c add concept of "strict adherence" to newline standard
e
s 00000/00000/01590
d D 8.53 95/02/28 15:42:09 eric 178 176
i 177
c incorporate fixes from 8.6.11
e
s 00001/00001/01525
d D 8.39.1.4 95/02/28 15:11:19 eric 177 175
c prototypes
e
s 00000/00000/01590
d D 8.52 95/02/28 14:43:14 eric 176 174
i 175
c incorporate fixes from 8.6.11
e
s 00010/00005/01516
d D 8.39.1.3 95/02/28 10:58:52 eric 175 171
c multiple glitches in 8.6.10 -- see ../RELEASE_NOTES for details
e
s 00002/00000/01583
d D 8.51 95/02/24 08:07:13 eric 174 173
c remove "POSSIBLE ATTACK" message -- it can be triggered in
e
s 00003/00002/01580
d D 8.50 95/02/23 15:50:51 eric 173 172
c cleanup to make gcc -Winitialized happier
e
s 00043/00036/01539
d D 8.49 95/02/11 06:43:38 eric 172 170
c avoid checking path directory modes if setreuid succeeded (for
c efficiency)
e
s 00000/00000/01521
d D 8.39.1.2 95/02/10 10:48:28 eric 171 169
i 170
c add logging on possible attacks
e
s 00012/00000/01563
d D 8.48 95/02/10 10:45:44 eric 170 168
c add syslog on possible attack
e
s 00000/00000/01509
d D 8.39.1.1 95/02/10 07:37:51 eric 169 160
i 168
c fix security problem allowing bogus lines to be written to qf file
c from command line or IDENT protocol by embedding newlines
e
s 00068/00000/01495
d D 8.47 95/02/10 07:16:42 eric 168 167
c fix security problem: avoid newlines in command line or IDENT input
e
s 00073/00000/01422
d D 8.46 94/10/24 18:32:31 eric 167 166
c first cut at service switch abstraction
e
s 00003/00002/01419
d D 8.45 94/10/08 09:25:20 eric 166 165
c avoid null pointer dereferences in some degenerate cases
e
s 00008/00001/01413
d D 8.44 94/09/08 17:56:52 eric 165 164
c prototype long macro name implementation
e
s 00003/00045/01411
d D 8.43 94/08/07 10:02:35 eric 164 163
c first cut at full 8-bit data capability
e
s 00014/00001/01442
d D 8.42 94/07/23 07:59:38 eric 163 162
c MIME 8 to 7 bit support
e
s 00002/00002/01441
d D 8.41 94/06/17 17:40:03 eric 162 161
c compatibility with BIND 4.9.3 (just cleanup)
e
s 00004/00002/01439
d D 8.40 94/06/17 11:12:59 eric 161 160
c Cray fixes from Eric Wassenaar
e
s 00001/00001/01440
d D 8.39 94/04/14 09:57:59 eric 160 159
c don't assume that long is 4 bytes
e
s 00047/00004/01394
d D 8.38 94/04/12 16:11:50 eric 159 158
c speed up reading of messages by reducing system call load
e
s 00002/00002/01396
d D 8.37 94/04/12 08:59:03 eric 158 157
c syntax bug (oops!)
e
s 00002/00000/01396
d D 8.36 94/04/12 08:38:32 eric 157 156
c updates for Intergraph CLIX
e
s 00010/00001/01386
d D 8.35 94/04/12 08:22:14 eric 156 155
c handle possible zero arg to xalloc and large file sizes
e
s 00006/00000/01381
d D 8.34 94/03/11 11:09:14 eric 155 154
c don't die in sfgets if a null pointer is passed
e
s 00001/00001/01380
d D 8.33 94/02/25 10:13:25 eric 154 153
c avoid problem where S_IFIFO == S_IFSOCK
e
s 00000/00003/01381
d D 8.32 94/02/07 08:35:04 eric 153 152
c fix reversed condition in last delta
e
s 00012/00001/01372
d D 8.31 94/02/06 19:29:03 eric 152 151
c changes from Eric Wassenaar: Apollo portability and improved network
c error handling
e
s 00010/00005/01363
d D 8.30 94/02/05 12:56:24 eric 151 150
c wrap headers and lines more intelligently (important for very
c short line lengths
e
s 00016/00017/01352
d D 8.29 94/01/24 08:01:38 eric 150 149
c move 7BIT information from per-mailer to per-connection so it can
c be tweaked based on the other end
e
s 00021/00000/01348
d D 8.28 94/01/04 06:40:36 eric 149 148
c expand dumpfd to tag FIFOs, directories, and symbolic links
e
s 00006/00000/01342
d D 8.27 93/12/30 05:55:03 eric 148 147
c security: fix a problem that allowed root to get into any directory
c instead of being treated as the "nobody" user
e
s 00003/00004/01339
d D 8.26 93/12/21 08:14:45 eric 147 146
c avoid infinite loops in sfgets due to wierd fgets implementations
e
s 00002/00000/01341
d D 8.25 93/12/20 10:52:27 eric 146 145
c avoid infinite loops on bad file sent to sfgets
e
s 00001/00001/01340
d D 8.24 93/12/14 14:22:06 eric 145 144
c hooks to allow access to files as root (on SFF_ROOTOK flag)
e
s 00001/00001/01340
d D 8.23 93/12/13 17:58:46 eric 144 143
c minor debugging glitch
e
s 00006/00006/01335
d D 8.22 93/12/10 16:40:15 eric 143 142
c cleanup of symbolic link checking -- make it less picky
e
s 00001/00001/01340
d D 8.21 93/12/10 12:42:19 eric 142 141
c up size of maximum short string
e
s 00049/00000/01292
d D 8.20 93/12/02 10:17:57 eric 141 140
c fix bogus implementation of name overflow limiting
e
s 00013/00008/01279
d D 8.19 93/12/02 07:28:40 eric 140 139
c make strcontainedin case insensitive
e
s 00001/00001/01286
d D 8.18 93/12/01 14:01:41 eric 139 137
c syslog debug info as LOG_DEBUG instead of LOG_INFO
e
s 00087/00027/01260
d D 8.17.1.1 93/11/27 11:51:13 eric 138 137
c sample implementation of buildfname that handles 8-bit characters
e
s 00024/00006/01263
d D 8.17 93/11/25 11:32:59 eric 137 136
c security patches to seal up symbolic link attacks
e
s 00001/00001/01268
d D 8.16 93/11/08 09:45:48 eric 136 135
c fix bug that permitted anyone to own /.forward
e
s 00002/00000/01267
d D 8.15 93/10/31 13:05:24 eric 135 134
c make S_IFSOCK conditional
e
s 00087/00054/01180
d D 8.14 93/10/23 12:45:33 eric 134 133
c open file debugging
e
s 00001/00001/01233
d D 8.13 93/10/21 07:20:33 eric 133 132
c handle pipes properly in checkfd012()
e
s 00087/00000/01147
d D 8.12 93/10/17 10:00:15 eric 132 131
c additional debugging information for too many open files problem
e
s 00011/00002/01136
d D 8.11 93/09/22 10:32:25 eric 131 130
c include hacks to allow old versions of wait that use "union wait"
e
s 00004/00000/01134
d D 8.10 93/09/04 11:50:53 eric 130 129
c more attempts to find the fd 1 closed error
e
s 00004/00004/01130
d D 8.9 93/08/26 11:21:20 eric 129 128
c more work on safefile -- it was STILL too pissy
e
s 00001/00001/01133
d D 8.8 93/08/23 08:32:31 eric 128 127
c add "ext" argument to lockfile so you can accurately tell what file
c is being locked in logging/error messages
e
s 00027/00002/01107
d D 8.7 93/07/28 15:30:07 eric 127 126
c finish group id set job
e
s 00048/00017/01061
d D 8.6 93/07/28 15:08:25 eric 126 125
c accept group permissions for :include: and .forward processing
e
s 00002/00002/01076
d D 8.5 93/07/19 20:50:16 eric 125 124
c SGI IRIX & ANSI C portability
e
s 00001/00001/01077
d D 8.4 93/07/16 10:23:05 eric 124 123
c avoid null pointer dereference
e
s 00004/00001/01074
d D 8.3 93/07/13 12:58:37 eric 123 122
c many fixes.  primarily fix for seteuid problem in 8.2; also,
c Solaris compatibility fixes; timed out messages problems; messages
c silently discarded if checkcompat returned EX_TEMPFAIL
e
s 00078/00005/00997
d D 8.2 93/07/11 06:52:42 eric 122 121
c huge number of changes for 8.2, including IRIX & Solaris portability;
c improved error checking; fix -m flag and add -O flag in maps; fix long
c DNS timeouts; relax safefile restrictions; add -X command line flag; etc.
e
s 00002/00002/01000
d D 8.1 93/06/27 18:26:25 bostic 121 120
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00041/00002/00961
d D 6.22 93/06/24 07:29:43 eric 120 118
c fix serious security bug allowing any user to read any file on
c the system regardless of permissions or ownership; fix problem causing
c subroutines returning $# triples to continue to evaluate (causes loops)
e
s 00002/00002/00961
d R 8.1 93/06/07 10:32:47 bostic 119 118
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00003/00961
d D 6.21 93/06/05 17:07:59 eric 118 117
c lint-style cleanup
e
s 00007/00004/00957
d D 6.20 93/06/03 17:01:35 eric 117 116
c print better diagnostic information on sfgets timeouts
e
s 00000/00001/00961
d D 6.19 93/05/27 11:37:36 eric 116 115
c prototype functions
e
s 00031/00009/00931
d D 6.18 93/05/05 08:11:27 eric 115 114
c create dead.letter with FileMode instead of 0666
e
s 00001/00001/00939
d D 6.17 93/05/03 19:12:06 eric 114 113
c change option 8 to option 7 (and invert semantics)
e
s 00000/00037/00940
d D 6.16 93/04/30 12:54:27 eric 113 112
c don't change alpha case on header field names
e
s 00002/00002/00975
d D 6.15 93/04/27 18:48:15 eric 112 111
c only flock regular files (specifically, not /dev/null)
e
s 00002/00002/00975
d D 6.14 93/03/23 19:50:53 eric 111 110
c improved debugging; pass convtime a default units; allow addition
c of Comments: and stripping of Return-Path:
e
s 00002/00003/00975
d D 6.13 93/03/17 09:55:18 eric 110 109
c clean up file locking (create a lockfile() routine in conf.c)
e
s 00023/00000/00955
d D 6.12 93/03/16 09:16:17 eric 109 108
c delete e_sender and e_returnpath; fix some bugs in envelope splitting
e
s 00000/00082/00955
d D 6.11 93/03/07 16:16:07 eric 108 107
c use transienterror() all places where we do this sort of mapping
e
s 00001/00004/01036
d D 6.10 93/03/01 06:53:38 eric 107 106
c header file cleanup; primarily #include <unistd.h> in sendmail.h
c and delete duplicate cruft
e
s 00030/00000/01010
d D 6.9 93/02/28 18:43:33 eric 106 105
c allow command line limitations to individual queue runs
e
s 00095/00008/00915
d D 6.8 93/02/26 08:19:37 eric 105 104
c better handling of transient errors
e
s 00039/00000/00884
d D 6.7 93/02/24 05:36:53 eric 104 103
c propagate alias owner information back to envelope sender
e
s 00020/00019/00864
d D 6.6 93/02/18 20:22:31 eric 103 102
c move the meta-characters from C0 into C1 space
e
s 00003/00003/00880
d D 6.5 93/02/16 18:30:03 eric 102 101
c clean up log levels; allow IDA-style split header/envelope rewriting;
c extend arpatounix with more zones (but is this even needed?)
e
s 00002/00002/00881
d D 6.4 93/01/21 15:18:46 eric 101 100
c more environment problems; limit resource exhaustion; fix incorrect
c name in Connection timed out message; ANSI C fixes; log message sender on
c returned mail during queue run; count recipients properly; fix YP code;
c diagnose "message timed out" properly
e
s 00035/00036/00848
d D 6.3 93/01/18 14:32:21 eric 100 99
c implement arpatounix; log more info; allow nested $?...$|...$.;
c POSIX compatibility; handle SMTP MAIL command errors properly;
c do early diagnosis of .cf errors; adjust checkpointing; misc bugs
e
s 00005/00003/00879
d D 6.2 93/01/01 13:08:25 eric 99 98
c pass read timeouts to sfgets
e
s 00000/00000/00882
d D 6.1 92/12/21 16:08:45 eric 98 97
c Release 6
e
s 00002/00002/00880
d D 5.35 92/12/20 11:14:22 eric 97 96
c change random constants to be #defines
e
s 00027/00009/00855
d D 5.34 92/12/15 12:34:51 eric 96 95
c dynamically allocate header fields (and more....); miscellaneous
c cleanup (mostly comments)
e
s 00001/00001/00863
d D 5.33 92/12/14 09:59:19 eric 95 94
c correct list of must-be-quoted characters
e
s 00005/00006/00859
d D 5.32 92/11/14 11:34:27 eric 94 93
c (partially) ANSI-fy it
e
s 00000/00010/00865
d D 5.31 92/11/13 16:04:22 eric 93 92
c *really* fix quoting in phrase part of addresses; eliminate #-style
c commenting in :include: and .forward files (parenthesized comments
c can be used instead)
e
s 00014/00001/00861
d D 5.30 92/09/22 16:40:27 eric 92 91
c a variety of bug minor bug fixes; add file locking when writing
c to a UNIX file; strip out dangerous envariables
e
s 00001/00001/00861
d D 5.29 92/07/19 14:26:07 eric 91 90
c finish uid_t/gid_t conversion; allow locally customized message for
c prepending to all error returns
e
s 00002/00003/00860
d D 5.28 92/07/14 12:58:46 eric 90 89
c fix small bug in buildfname
e
s 00028/00004/00835
d D 5.27 92/07/12 10:23:46 eric 89 88
c quote full names if they have special characters
e
s 00010/00043/00829
d D 5.26 92/07/12 10:14:12 eric 88 87
c make eight-bit clean; backslashes are carried through as-is
e
s 00014/00012/00858
d D 5.25 92/02/24 21:15:44 eric 87 86
c allow on-line comments; don't double-parse RCPT To: addresses;
c warn on truncated lines; do some sanity checks on .cf file descriptor
e
s 00004/00000/00866
d D 5.24 92/02/21 20:57:52 eric 86 85
c from Bryan Costales: several smallish changes, mostly to clean
c up debugging output.  The major change is that test mode (-bt)
c doesn't automatically run through ruleset three any more.
e
s 00013/00007/00853
d D 5.23 92/01/04 15:33:13 eric 85 84
c allow limited 8-bit support; allow [TCP] as an alias for [IPC], even
c though it's wrong; restore t option for System V support; add L=_N_
c mailer option for line lengths; implement R mailer flag to get
c restricted port; misc cleanup
e
s 00020/00002/00840
d D 5.22 91/12/21 10:35:03 eric 84 83
c print some control characters in xputs
e
s 00016/00000/00826
d D 5.21 91/11/20 18:23:28 eric 83 82
c from costales@icsi.Berkeley.EDU: print rulesets with symbolic name
c instead of control characters; allow # comments in :include: files
e
s 00007/00010/00819
d D 5.20 91/03/08 12:29:53 bostic 82 81
c ANSI, don't write into strings; bug report 4.3BSD-reno/usr.lib/0
e
s 00001/00001/00828
d D 5.19 91/03/02 17:15:36 bostic 81 80
c ANSI
e
s 00002/00010/00827
d D 5.18 90/06/01 19:07:05 bostic 80 79
c new copyright notice
e
s 00002/00001/00835
d D 5.17 90/04/19 17:06:37 bostic 79 78
c don't use toupper(*s++), paranoia; bug report 4.3BSD-tahoe/usr.sbin/16
e
s 00001/00001/00835
d D 5.16 90/04/19 17:05:10 bostic 78 77
c don't NULL deref RealHostName; bug report 4.3BSD-tahoe/usr.sbin/15
e
s 00001/00001/00835
d D 5.15 90/04/18 12:27:31 bostic 77 76
c mail bounces on transient errors; bug report 4.3BSD/usr.lib/135
e
s 00001/00001/00835
d D 5.14 88/12/05 20:04:18 bostic 76 75
c minor cleanups for cray
e
s 00002/00000/00834
d D 5.13 88/11/17 22:02:40 karels 75 74
c more cleanup, fix some inappropriate syserr's
e
s 00005/00006/00829
d D 5.12 88/11/17 10:32:18 karels 74 73
c expunge debugging/nonstandard/trojan horse commands from smtp,
c logging attempts to use them; log name/address of host from which mail received
c ("mail from" may not include it or may lie); don't allow debug to affect
c permissions locally; change some of the non-system syserrs to syslog at lower
c priority; still need to unifdef remaining debug code
e
s 00016/00010/00819
d D 5.11 88/03/13 19:53:37 bostic 73 72
c add Berkeley specific header
e
s 00002/00037/00827
d D 5.10 88/03/13 18:20:49 bostic 72 71
c use tolower macro where applicable; remove sameword, the routine 
c strcasecmp has been added to the C library.
e
s 00000/00001/00864
d D 5.9 86/12/17 16:05:39 eric 71 70
c delete unneeded #include <ctype.h>
e
s 00001/00001/00864
d D 5.8 85/12/17 23:54:13 eric 70 69
m 
c lint
e
s 00001/00005/00864
d D 5.7 85/09/30 21:34:27 eric 69 68
m 
c clean up some aspects of error message display
e
s 00005/00001/00864
d D 5.6 85/09/19 00:45:26 eric 68 67
m 
c SMI changes (somewhat)
e
s 00002/00001/00863
d D 5.5 85/06/08 10:30:11 eric 67 66
m 
c lint for 4.3 release
e
s 00012/00012/00852
d D 5.4 85/06/08 00:30:55 eric 66 65
m 
c lint
e
s 00000/00002/00864
d D 5.3 85/06/07 22:22:08 miriam 65 64
m 
c Resolve duplicate SccsId
e
s 00000/00000/00866
d D 5.2 85/06/07 15:21:54 dist 64 63
m 
c Add copyright
e
s 00014/00000/00852
d D 5.1 85/06/07 15:18:20 dist 63 62
m 
c Add copyright
e
s 00001/00004/00851
d D 4.11 85/04/28 10:42:36 eric 62 61
m 
c remove #ifdef DEBUG so we can compile without #define DEBUG
e
s 00000/00019/00855
d D 4.10 85/04/09 14:14:54 ralph 61 60
m 
c syslog() is in lint librrary now.
e
s 00036/00019/00838
d D 4.9 84/11/13 12:29:36 eric 60 59
m 
c optimize fgetfolded and sameword
e
s 00002/00002/00855
d D 4.8 84/08/11 17:49:03 eric 59 58
m 
c Assorted changes from Guy Harris <rlgvax!guy>: mostly lint & USG
e
s 00001/00022/00856
d D 4.7 84/08/11 16:51:51 eric 58 57
m 
c Changes from Greg Couch <ucsfcgl!gregc> for V7 compatibility and
c miscellaneous bug fixes; "clear" => "bzero" and "bmove" => "bcopy"
c throughout for consistency; bzero is now in bcopy.c (these are
c supplied by libc on 4.2bsd)
e
s 00006/00001/00872
d D 4.6 84/08/11 14:53:19 eric 57 56
m 
c strip 0200 bits on input to prevent loops
e
s 00006/00001/00867
d D 4.5 84/03/11 13:37:47 eric 56 55
m 
c fixes from Greg Satz <satz@sri-tsc.ARPA>, mostly for PDP's
e
s 00000/00020/00868
d D 4.4 83/12/27 22:52:29 eric 55 54
m 
c don't close files immediately before exec of mailer so that we can log;
c use FIOCLEX instead.  Suggested by Tom Ferrin, UCSF CGL.
e
s 00009/00003/00879
d D 4.3 83/11/13 18:08:07 eric 54 53
m 
c Fixes two nasty problems, both pointed out by Bill Nowicki at Stanford:
c I/O errors on input in collect would cause infinite loops, and a protocol
c error (or other error that would call smtpquit abnormally) would cause
c core dumps
e
s 00018/00007/00864
d D 4.2 83/08/31 17:42:23 eric 53 52
m 
c fix problem with timeouts caused by change in EINTR semantics in 4.2bsd;
c add a two minute timeout on the greeting message in user smtp to detect
c hung connections
e
s 00000/00000/00871
d D 4.1 83/07/25 19:45:24 eric 52 51
m 
c 4.2 release version
e
s 00002/00000/00869
d D 3.44 83/04/17 17:15:30 eric 51 50
m 221
c fix bogus errno problems
e
s 00009/00001/00860
d D 3.43 83/02/24 18:53:57 eric 50 49
m 192
c Truncate output text to seven bits
e
s 00056/00004/00805
d D 3.42 83/02/02 12:53:22 eric 49 48
m 165
c implement classes and mailer flags as a bit map; define new class 'w'
c as the set of all hosts we are known by
e
s 00004/00004/00805
d D 3.41 83/01/16 13:14:17 eric 48 47
m 152
c Change mailer spec to have labelled fields for future expansion.
c **** This delta invalidates previous configuration files ****
e
s 00002/00031/00807
d D 3.40 83/01/09 15:42:29 eric 47 46
m 
c fix CRLF problem when sending SMTP commands; make newstr() and crlf()
c into macros
e
s 00014/00013/00824
d D 3.39 83/01/06 10:46:54 eric 46 45
m 
c split up FULLSMTP flag -- now have "X" (M_XDOT, use hidden dot algorithm),
c "p" (M_FROMPATH, use reverse-path in MAIL FROM:<> command), and "L"
c (M_LIMITS, enforce SMTP line limits).  I would like to change the format
c of the mail defn one more time to make named fields so that it would
c be more extensible.
e
s 00009/00003/00828
d D 3.38 83/01/01 21:25:45 eric 45 44
m 123
c Put CRLF on all lines in user SMTP.  Pass this info down to
c innumerable routines.
e
s 00002/00001/00829
d D 3.37 82/12/30 17:30:37 eric 44 43
m 114
c don't bother timing out on *.cf and qf* file reads -- they are
c really very vanilla
e
s 00002/00000/00828
d D 3.36 82/12/09 11:14:25 eric 43 42
m 081
c log read timeouts as a syserr
e
s 00052/00093/00776
d D 3.35 82/11/28 00:22:29 eric 42 41
m 
c Many changes resulting from a complete code readthrough.  Most of these
c fix minor bugs or change the internal structure for clarity, etc.  There
c should be almost no externally visible changes (other than some cleaner
c error message printouts and the like).
e
s 00023/00000/00846
d D 3.34 82/11/03 10:29:24 eric 41 40
m 058
c Put temporary file mode on the F option
e
s 00027/00000/00819
d D 3.33 82/11/03 09:49:24 eric 40 39
m 049
c Arrange to strip quote bits in message header; move SPACESUB into
c conf.c; change SpaceSub to unquoted dot
e
s 00024/00000/00795
d D 3.32 82/09/26 14:46:01 eric 39 38
c completely instantiate queue files for all mail, even if not needed;
c fix a bug that would probably come up once every ten years in creating
c the queue id.  should merge argv flag processing with option processing.
e
s 00007/00002/00788
d D 3.31 82/09/05 18:03:35 eric 38 37
c tune debugging
e
s 00007/00001/00783
d D 3.30 82/09/05 11:45:22 eric 37 36
c add line numbering for some input files; improve debugging output
e
s 00012/00008/00772
d D 3.29 82/08/27 16:03:28 eric 36 35
c simplify timeout code; allow multiple simultaneous queue runs so that
c large messages don't freeze things up; fix EINTR problem in sfgets;
c clean up canonname to be really correct; lots of misc. cleanup
e
s 00021/00000/00759
d D 3.28 82/08/25 11:21:31 eric 35 34
c clean up time manipulation to always be current; assign job
c id's earlier to make sure there is always one with a message.
e
s 00001/00001/00758
d D 3.27 82/08/24 10:27:21 eric 34 33
c clean up event handling so that events that do longjmp's don't turn
c off all future events.
e
s 00091/00000/00668
d D 3.26 82/08/23 11:59:43 eric 33 32
c clean up queueing; log time in queue.
c **** This delta invalidates mqueue files ****
e
s 00001/00001/00667
d D 3.25 82/08/22 19:03:13 eric 32 31
c assign a unique id to each transaction that can be determined from
c the queue file name.
e
s 00042/00000/00626
d D 3.24 82/08/17 20:43:29 eric 31 30
c handle folded lines in queue file properly
e
s 00033/00026/00593
d D 3.23 82/08/15 11:51:38 eric 30 29
c know about continuation lines in queue files: necessary for headers
e
s 00041/00000/00578
d D 3.22 82/08/08 17:02:39 eric 29 28
c more general event mechanism
e
s 00029/00000/00549
d D 3.21 82/08/08 01:03:06 eric 28 27
c change debug level to a debug vector; add levels on logging (and the
c -L flag); change logging to be by message-id; elevate message-id;
c some lint-type cleanup
e
s 00000/00023/00549
d D 3.20 82/07/05 12:21:57 eric 27 26
c split off clock stuff from util.c so that vacation will compile
e
s 00023/00000/00549
d D 3.19 82/07/05 12:02:47 eric 26 25
c put timeouts on net reads
e
s 00001/00002/00548
d D 3.18 82/06/26 13:10:36 eric 25 24
c lint
e
s 00055/00000/00495
d D 3.17 82/06/07 23:55:47 eric 24 23
c call the routine putline to output lines to mailers.  this lets us
c implement line length limits, etc. for full SMTP compatibility.
e
s 00004/00004/00491
d D 3.16 82/05/31 18:49:42 eric 23 22
c pass lint.  notice that definitions in llib-lc have changed for
c alarm() and sleep() calls {arg was unsigned, is now int}.
e
s 00030/00001/00465
d D 3.15 82/05/20 17:45:57 eric 22 21
c add dfopen as a "determined fopen" -- it retries if it gets recoverable
c errors.  we use it for returning mail (to dead.letter) and creating the
c temp file.  the whole idea is to avoid dropping things on the floor on
c heavily loaded systems.  this is untested, since it seems impossible to
c fill up the inode or file tables on this VAX (but it works if the open
c succeeds).
e
s 00001/00001/00465
d D 3.14 82/03/20 18:12:53 eric 21 20
c take % as an acceptable name terminator in GECOS field
c ("in-care-of") -- for TEF%UCSFCGL
e
s 00001/00001/00465
d D 3.13 81/12/06 12:39:03 eric 20 18
c cleanup so it will go through lint without any fancy grep -v's;
c change the way SCCS Id's are handled.
e
s 00008/00011/00455
d D 3.12.1.1 81/11/21 15:47:50 eric 19 18
c links together aliases into proper trees.  This is in part an
c attempt to do the SMTP VRFY command properly, but there are a number
c of annoying problems that convince me that this is the wrong way to
c do it.  Sigh.
e
s 00001/00001/00465
d D 3.12 81/11/07 21:57:40 eric 18 17
c fix a bug in fixcrlf that made SMTP die
e
s 00034/00000/00432
d D 3.11 81/10/20 11:36:19 eric 17 16
c clean up the SMTP stuff some more
e
s 00031/00000/00401
d D 3.10 81/10/17 16:57:55 eric 16 15
c initial prep to put in Daemon mode
e
s 00002/00000/00399
d D 3.9 81/09/24 10:30:37 eric 15 13
c changes to work under a V6 system -- mostly compilation flags
e
s 00001/00000/00399
d D 3.8.1.1 81/09/23 18:23:11 eric 14 13
c break some configuration into conf.h -- simplifies makefile changes
c on different machines.  But there are still conditional libraries, so
c this may not be a good idea.....
e
s 00040/00000/00359
d D 3.8 81/09/12 17:34:01 eric 13 12
c match on full name for local users
e
s 00029/00002/00330
d D 3.7 81/08/10 16:56:46 eric 12 11
c totally rework aliasing scheme -- sucks when no DBM now,
c but works better for the usual case; fix some quoting problems
c (and how many did I add?); remove .mailer feature since .forward
c will simulate this happily
e
s 00022/00006/00310
d D 3.6 81/08/09 15:03:12 eric 11 10
c lint it
e
s 00029/00000/00287
d D 3.5 81/08/08 11:17:20 eric 10 9
c add "sameword" to do case-indistinct matching of names
e
s 00155/00000/00132
d D 3.4 81/03/09 13:22:41 eric 9 8
c first step at rewriting rules, etc.
e
s 00002/00001/00130
d D 3.3 81/03/07 15:33:41 eric 8 7
c lint fixes
e
s 00000/00030/00131
d D 3.2 81/03/07 14:27:15 eric 7 6
c ----- delivermail ==> postbox -----
e
s 00062/00003/00099
d D 3.1 81/03/04 09:34:38 eric 6 5
c install fancy header stuff
e
s 00000/00000/00102
d D 2.1 80/11/05 11:00:30 eric 5 4
c release 2
e
s 00001/00001/00101
d D 1.4 80/10/21 22:39:47 eric 4 3
c EX_UNAVAIL => EX_UNAVAILABLE
e
s 00000/00028/00102
d D 1.3 80/08/02 13:50:10 eric 3 2
c cleaned up comments
e
s 00002/00000/00128
d D 1.2 80/07/25 22:04:31 eric 2 1
c add ID keywords
e
s 00128/00000/00000
d D 1.1 80/06/23 08:24:52 eric 1 0
e
u
U
f b 
f i 
t
T
I 63
/*
I 80
D 190
 * Copyright (c) 1983 Eric P. Allman
E 190
I 190
 * Copyright (c) 1983, 1995 Eric P. Allman
E 190
E 80
D 73
**  Sendmail
**  Copyright (c) 1983  Eric P. Allman
**  Berkeley, California
**
**  Copyright (c) 1983 Regents of the University of California.
**  All rights reserved.  The Berkeley software License Agreement
**  specifies the terms and conditions for redistribution.
*/
E 73
I 73
D 121
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.
E 121
I 121
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 121
 *
D 80
 * Redistribution and use in source and binary forms are permitted
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
 *
 *  Sendmail
 *  Copyright (c) 1983  Eric P. Allman
 *  Berkeley, California
E 80
I 80
 * %sccs.include.redist.c%
E 80
 */
E 73

#ifndef lint
D 73
static char	SccsId[] = "%W% (Berkeley) %G%";
#endif not lint
E 73
I 73
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 73

E 63
I 9
D 107
# include <stdio.h>
I 19
# include <pwd.h>
E 19
I 16
# include <sys/types.h>
E 107
I 107
# include "sendmail.h"
E 107
D 112
# include <sys/stat.h>
E 112
E 16
E 9
I 1
# include <sysexits.h>
D 22
# include "useful.h"
E 22
I 22
D 107
# include <errno.h>
E 22
I 6
D 71
# include <ctype.h>
E 71
I 22
# include "sendmail.h"
E 107
E 22
I 14
# include "conf.h"
E 14
E 6
D 96

I 2
D 20
static char	SccsId[] = "%W%	%G%";
E 20
I 20
D 65
SCCSID(%W%	%Y%	%G%);
E 20

E 65
E 2
/*
E 96
I 96
/*
E 96
D 3
**  UTIL.C -- General Purpose Routines
**
**	Defines:
**		stripquotes
**		xalloc
**		any
*/
/*
E 3
**  STRIPQUOTES -- Strip quotes & quote bits from a string.
**
**	Runs through a string and strips off unquoted quote
**	characters and quote bits.  This is done in place.
**
**	Parameters:
**		s -- the string to strip.
I 12
D 88
**		qf -- if set, remove actual `` " '' characters
**			as well as the quote bits.
E 88
E 12
**
**	Returns:
**		none.
**
**	Side Effects:
**		none.
**
D 3
**	Requires:
**		none.
**
E 3
**	Called By:
**		deliver
D 3
**
**	History:
**		3/5/80 -- written.
E 3
*/

I 198
void
E 198
D 12
stripquotes(s)
E 12
I 12
D 88
stripquotes(s, qf)
E 88
I 88
stripquotes(s)
E 88
E 12
	char *s;
I 12
D 88
	bool qf;
E 88
E 12
{
	register char *p;
	register char *q;
	register char c;

I 12
	if (s == NULL)
		return;

E 12
D 88
	for (p = q = s; (c = *p++) != '\0'; )
E 88
I 88
	p = q = s;
	do
E 88
	{
D 12
		if (c != '"')
E 12
I 12
D 88
		if (c != '"' || !qf)
E 12
			*q++ = c & 0177;
	}
	*q = '\0';
E 88
I 88
		c = *p++;
		if (c == '\\')
			c = *p++;
		else if (c == '"')
			continue;
		*q++ = c;
	} while (c != '\0');
E 88
}
/*
I 40
D 88
**  QSTRLEN -- give me the string length assuming 0200 bits add a char
**
**	Parameters:
**		s -- the string to measure.
**
**	Reurns:
**		The length of s, including space for backslash escapes.
**
**	Side Effects:
**		none.
*/

qstrlen(s)
	register char *s;
{
	register int l = 0;
	register char c;

	while ((c = *s++) != '\0')
	{
		if (bitset(0200, c))
			l++;
		l++;
	}
	return (l);
}
/*
E 88
E 40
I 6
D 113
**  CAPITALIZE -- return a copy of a string, properly capitalized.
**
**	Parameters:
**		s -- the string to capitalize.
**
**	Returns:
**		a pointer to a properly capitalized string.
**
**	Side Effects:
**		none.
*/

char *
capitalize(s)
	register char *s;
{
	static char buf[50];
	register char *p;

	p = buf;

	for (;;)
	{
D 103
		while (!isalpha(*s) && *s != '\0')
E 103
I 103
		while (!(isascii(*s) && isalpha(*s)) && *s != '\0')
E 103
			*p++ = *s++;
		if (*s == '\0')
			break;
D 79
		*p++ = toupper(*s++);
E 79
I 79
		*p++ = toupper(*s);
		s++;
E 79
D 103
		while (isalpha(*s))
E 103
I 103
		while (isascii(*s) && isalpha(*s))
E 103
			*p++ = *s++;
	}

	*p = '\0';
	return (buf);
}
/*
E 113
E 6
**  XALLOC -- Allocate memory and bitch wildly on failure.
**
**	THIS IS A CLUDGE.  This should be made to give a proper
**	error -- but after all, what can we do?
**
**	Parameters:
**		sz -- size of area to allocate.
**
**	Returns:
**		pointer to data region.
**
**	Side Effects:
**		Memory is allocated.
D 6
**
D 3
**	Requires:
**		malloc
**		syserr
**		exit
**
E 3
**	Called By:
**		lots of people.
E 6
D 3
**
**	History:
**		12/31/79 -- written.
E 3
*/

char *
xalloc(sz)
D 23
	register unsigned int sz;
E 23
I 23
	register int sz;
E 23
{
	register char *p;
I 67
D 94
	extern char *malloc();
E 94
E 67
D 11
	extern char *malloc();
E 11

I 156
	/* some systems can't handle size zero mallocs */
	if (sz <= 0)
		sz = 1;

E 156
D 67
	p = malloc(sz);
E 67
I 67
	p = malloc((unsigned) sz);
E 67
	if (p == NULL)
	{
D 201
		syserr("Out of memory!!");
D 4
		exit(EX_UNAVAIL);
E 4
I 4
D 49
		exit(EX_UNAVAILABLE);
E 49
I 49
		abort();
E 201
I 201
		syserr("!Out of memory!!");
E 201
		/* exit(EX_UNAVAILABLE); */
E 49
E 4
	}
I 6
	return (p);
}
/*
D 47
**  NEWSTR -- make copy of string.
**
**	Space is allocated for it using xalloc.
**
**	Parameters:
**		string to copy.
**
**	Returns:
**		pointer to new string.
**
**	Side Effects:
**		none.
*/

char *
newstr(s)
	register char *s;
{
	register char *p;
I 8
D 11
	extern char *strcpy();
E 11
E 8

D 8
	p = xalloc(strlen(s) + 1);
E 8
I 8
D 23
	p = xalloc((unsigned) (strlen(s) + 1));
E 8
	strcpy(p, s);
E 23
I 23
	p = xalloc(strlen(s) + 1);
	(void) strcpy(p, s);
E 23
E 6
	return (p);
I 9
}
/*
E 47
**  COPYPLIST -- copy list of pointers.
**
**	This routine is the equivalent of newstr for lists of
**	pointers.
**
**	Parameters:
**		list -- list of pointers to copy.
**			Must be NULL terminated.
**		copycont -- if TRUE, copy the contents of the vector
**			(which must be a string) also.
**
**	Returns:
**		a copy of 'list'.
**
**	Side Effects:
**		none.
*/

char **
copyplist(list, copycont)
	char **list;
	bool copycont;
{
	register char **vp;
	register char **newvp;
D 11
	extern char *xalloc();
E 11

	for (vp = list; *vp != NULL; vp++)
		continue;

	vp++;

D 11
	newvp = (char **) xalloc((vp - list) * sizeof *vp);
	bmove(list, newvp, (vp - list) * sizeof *vp);
E 11
I 11
D 23
	newvp = (char **) xalloc((unsigned) (vp - list) * sizeof *vp);
E 23
I 23
D 59
	newvp = (char **) xalloc((vp - list) * sizeof *vp);
E 23
D 58
	bmove((char *) list, (char *) newvp, (vp - list) * sizeof *vp);
E 58
I 58
	bcopy((char *) list, (char *) newvp, (vp - list) * sizeof *vp);
E 59
I 59
	newvp = (char **) xalloc((int) (vp - list) * sizeof *vp);
	bcopy((char *) list, (char *) newvp, (int) (vp - list) * sizeof *vp);
E 59
E 58
E 11

	if (copycont)
	{
		for (vp = newvp; *vp != NULL; vp++)
			*vp = newstr(*vp);
	}

	return (newvp);
}
/*
I 104
**  COPYQUEUE -- copy address queue.
**
**	This routine is the equivalent of newstr for address queues
**	addresses marked with QDONTSEND aren't copied
**
**	Parameters:
**		addr -- list of address structures to copy.
**
**	Returns:
**		a copy of 'addr'.
**
**	Side Effects:
**		none.
*/

ADDRESS *
copyqueue(addr)
	ADDRESS *addr;
{
	register ADDRESS *newaddr;
	ADDRESS *ret;
	register ADDRESS **tail = &ret;

	while (addr != NULL)
	{
		if (!bitset(QDONTSEND, addr->q_flags))
		{
			newaddr = (ADDRESS *) xalloc(sizeof(ADDRESS));
			STRUCTCOPY(*addr, *newaddr);
			*tail = newaddr;
			tail = &newaddr->q_next;
		}
		addr = addr->q_next;
	}
	*tail = NULL;
	
	return ret;
}
/*
E 104
**  PRINTAV -- print argument vector.
**
**	Parameters:
**		av -- argument vector.
**
**	Returns:
**		none.
**
**	Side Effects:
**		prints av.
*/

I 198
void
E 198
D 62
# ifdef DEBUG
E 62
printav(av)
	register char **av;
{
	while (*av != NULL)
	{
D 38
		printf("\t%08x=", *av);
E 38
I 38
		if (tTd(0, 44))
			printf("\n\t%08x=", *av);
		else
D 66
			putchar(' ');
E 66
I 66
			(void) putchar(' ');
E 66
E 38
		xputs(*av++);
D 38
		putchar('\n');
E 38
	}
I 38
D 66
	putchar('\n');
E 66
I 66
	(void) putchar('\n');
E 66
E 38
}
D 62
# endif DEBUG
E 62
/*
**  LOWER -- turn letter into lower case.
**
**	Parameters:
**		c -- character to turn into lower case.
**
**	Returns:
**		c, in lower case.
**
**	Side Effects:
**		none.
*/

char
lower(c)
	register char c;
{
D 72
	if (isascii(c) && isupper(c))
		c = c - 'A' + 'a';
	return (c);
E 72
I 72
D 103
	return(isascii(c) && isupper(c) ? tolower(c) : c);
E 103
I 103
	return((isascii(c) && isupper(c)) ? tolower(c) : c);
E 103
E 72
}
/*
**  XPUTS -- put string doing control escapes.
**
**	Parameters:
**		s -- string to put.
**
**	Returns:
**		none.
**
**	Side Effects:
**		output to stdout
*/

I 198
void
E 198
D 62
# ifdef DEBUG
E 62
xputs(s)
D 198
	register char *s;
E 198
I 198
	register const char *s;
E 198
{
D 103
	register char c;
E 103
I 103
	register int c;
E 103
I 83
	register struct metamac *mp;
	extern struct metamac MetaMacros[];
E 83

I 37
	if (s == NULL)
	{
		printf("<null>");
		return;
I 83
	}
D 100
	c = *s;
	if (c == MATCHREPL && isdigit(s[1]) && s[2] == '\0')
	{
		printf("$%c", s[1]);
		return;
	}
	for (mp = MetaMacros; mp->metaname != NULL; mp++)
	{
		if (mp->metaval == c)
		{
			printf("$%c%s", mp->metaname, ++s);
			return;
		}
E 83
	}
I 38
D 66
	putchar('"');
E 66
I 66
	(void) putchar('"');
E 100
E 66
E 38
E 37
D 103
	while ((c = *s++) != '\0')
E 103
I 103
	while ((c = (*s++ & 0377)) != '\0')
E 103
	{
		if (!isascii(c))
		{
I 103
D 165
			if (c == MATCHREPL || c == MACROEXPAND)
E 165
I 165
			if (c == MATCHREPL)
E 165
			{
				putchar('$');
I 165
				continue;
			}
			if (c == MACROEXPAND)
			{
				putchar('$');
				if (bitset(0200, *s))
					printf("{%s}", macname(*s++ & 0377));
E 165
				continue;
			}
			for (mp = MetaMacros; mp->metaname != '\0'; mp++)
			{
				if ((mp->metaval & 0377) == c)
				{
					printf("$%c", mp->metaname);
					break;
				}
			}
			if (mp->metaname != '\0')
				continue;
E 103
D 66
			putchar('\\');
E 66
I 66
			(void) putchar('\\');
E 66
			c &= 0177;
		}
D 48
		if (iscntrl(c))
E 48
I 48
D 100
		if (c < 040 || c >= 0177)
E 100
I 100
		if (isprint(c))
E 100
E 48
		{
D 66
			putchar('^');
E 66
I 66
D 84
			(void) putchar('^');
E 66
D 48
			c |= 0100;
E 48
I 48
			c ^= 0100;
E 84
I 84
D 100
			switch (c)
E 100
I 100
			putchar(c);
			continue;
D 103
		}
		if (c == MATCHREPL || c == '\001')
		{
			putchar('$');
			continue;
		}
D 101
		for (mp = MetaMacros; mp->metaname != NULL; mp++)
E 101
I 101
		for (mp = MetaMacros; mp->metaname != '\0'; mp++)
E 101
		{
			if (mp->metaval == c)
E 100
			{
D 100
			  case '\n':
				c = 'n';
E 100
I 100
				printf("$%c", mp->metaname);
				c = '\0';
E 100
				break;
I 100
			}
E 103
		}
E 100

D 100
			  case '\r':
				c = 'r';
				break;
E 100
I 100
		/* wasn't a meta-macro -- find another way to print it */
		switch (c)
		{
D 182
		  case '\0':
			continue;
E 100

E 182
D 100
			  case '\t':
				c = 't';
				break;
E 100
I 100
		  case '\n':
			c = 'n';
			break;
E 100

I 86
D 100
			  case '\001':
				(void) putchar('$');
				continue;
E 100
I 100
		  case '\r':
			c = 'r';
			break;
E 100

E 86
D 100
			  default:
				(void) putchar('^');
				(void) putchar(c ^ 0100);
				continue;
			}
			(void) putchar('\\');
E 100
I 100
		  case '\t':
			c = 't';
			break;

		  default:
			(void) putchar('^');
			(void) putchar(c ^ 0100);
			continue;
E 100
E 84
E 48
		}
I 182
		(void) putchar('\\');
		(void) putchar(c);
E 182
D 66
		putchar(c);
E 66
I 66
D 100
		(void) putchar(c);
E 100
E 66
	}
I 38
D 66
	putchar('"');
E 66
I 66
D 100
	(void) putchar('"');
E 100
E 66
E 38
D 11
	fflush(stdout);
E 11
I 11
	(void) fflush(stdout);
E 11
}
D 62
# endif DEBUG
E 62
/*
**  MAKELOWER -- Translate a line into lower case
**
**	Parameters:
**		p -- the string to translate.  If NULL, return is
**			immediate.
**
**	Returns:
**		none.
**
**	Side Effects:
**		String pointed to by p is translated to lower case.
**
**	Called By:
**		parse
*/

I 173
void
E 173
makelower(p)
	register char *p;
{
	register char c;

	if (p == NULL)
		return;
	for (; (c = *p) != '\0'; p++)
		if (isascii(c) && isupper(c))
D 72
			*p = c - 'A' + 'a';
E 9
}
I 10
/*
**  SAMEWORD -- return TRUE if the words are the same
**
**	Ignores case.
**
**	Parameters:
**		a, b -- the words to compare.
**
**	Returns:
**		TRUE if a & b match exactly (modulo case)
**		FALSE otherwise.
**
**	Side Effects:
**		none.
*/

bool
sameword(a, b)
	register char *a, *b;
{
D 60
	while (lower(*a) == lower(*b))
E 60
I 60
	char ca, cb;

	do
E 60
	{
D 60
		if (*a == '\0')
			return (TRUE);
		a++;
		b++;
	}
	return (FALSE);
E 60
I 60
		ca = *a++;
		cb = *b++;
		if (isascii(ca) && isupper(ca))
			ca = ca - 'A' + 'a';
		if (isascii(cb) && isupper(cb))
			cb = cb - 'A' + 'a';
	} while (ca != '\0' && ca == cb);
	return (ca == cb);
E 72
I 72
			*p = tolower(c);
E 72
E 60
I 12
D 58
}
/*
**  CLEAR -- clear a block of memory
**
**	Parameters:
**		p -- location to clear.
**		l -- number of bytes to clear.
**
**	Returns:
**		none.
**
**	Side Effects:
**		none.
*/

clear(p, l)
	register char *p;
	register int l;
{
	while (l-- > 0)
		*p++ = 0;
E 58
E 12
}
I 11
/*
I 13
D 19
**  BUILDFNAME -- build full name from gecos style entry.
E 19
I 19
**  FULLNAME -- extract full name from a passwd file entry.
E 19
**
D 19
**	This routine interprets the strange entry that would appear
**	in the GECOS field of the password file.
**
E 19
**	Parameters:
D 19
**		p -- name to build.
**		login -- the login name of this user (for &).
**		buf -- place to put the result.
E 19
I 19
**		pw -- password entry to start from.
**		buf -- buffer to store result in.
E 19
**
**	Returns:
D 138
**		none.
E 138
I 138
**		TRUE -- if the resulting message should be a MIME format.
**		FALSE -- if MIME is not necessary.
E 138
**
**	Side Effects:
**		none.
*/

I 198
void
E 198
I 138
/* values for should_quote */
#define NO_QUOTE	0
#define SHOULD_QUOTE	1
#define SHOULD_MIME	2

int
E 138
D 19
D 89
buildfname(p, login, buf)
	register char *p;
E 89
I 89
buildfname(gecos, login, buf)
D 138
	register char *gecos;
E 89
	char *login;
E 19
I 19
fullname(pw, buf)
	register struct passwd *pw;
E 19
	char *buf;
E 138
I 138
	register unsigned char *gecos;
	const unsigned char *login;
	unsigned char *buf;
E 138
{
I 89
D 138
	register char *p;
E 89
	register char *bp = buf;
I 89
	int l;
E 138
I 138
	register unsigned char *bp = buf;
	unsigned char *p;
	int should_quote = NO_QUOTE;
E 138
D 93
	bool quoteit;
E 93
E 89
I 19
	register char *p = pw->pw_gecos;
E 19

I 15
D 89
	if (*p == '*')
		p++;
E 89
I 89
D 138
	if (*gecos == '*')
		gecos++;

D 95
	/* see if the full name needs to be quoted */
E 95
I 95
	/* find length of final string */
E 95
	l = 0;
D 93
	quoteit = FALSE;
E 93
	for (p = gecos; *p != '\0' && *p != ',' && *p != ';' && *p != '%'; p++)
E 138
I 138
	/* make sure specials, SPACE and CTLs are quoted within " " */
	for (p = gecos; *p && *p != ',' && *p != ';' && *p != '%'; p++)
E 138
	{
D 93
		if (index("<>()'.", *p) != NULL)
			quoteit = TRUE;
E 93
D 138
		if (*p == '&')
			l += strlen(login);
		else
			l++;
E 138
I 138
		if (*p >= 0200)
		{
			should_quote = SHOULD_MIME;
			break;
		}
		switch (*p)
		{
		  case '(':
		  case ')':
		  case '<':
		  case '>':
		  case '@':
		  case ':':
		  case '\\':
		  case '"':
		  case '.':
		  case '[':
		  case ']':
			should_quote = SHOULD_QUOTE;
			break;
		}	
E 138
	}
D 93
	if (quoteit)
		l += 2;
E 93
D 138

	/* now fill in buf */
D 93
	if (quoteit)
		*bp++ = '"';
E 93
E 89
E 15
D 21
	while (*p != '\0' && *p != ',' && *p != ';')
E 21
I 21
D 90
	while (*p != '\0' && *p != ',' && *p != ';' && *p != '%')
E 90
I 90
	for (p = gecos; *p != '\0' && *p != ',' && *p != ';' && *p != '%'; p++)
E 138
I 138
	if (should_quote == SHOULD_MIME)
E 138
E 90
E 21
	{
D 138
		if (*p == '&')
E 138
I 138
		strcpy (bp, "=?iso-8859-1?Q?");
		bp += 15;
		for (p = gecos; *p && *p != ',' && *p != ';' && *p != '%'; p++)
E 138
		{
D 19
D 138
			(void) strcpy(bp, login);
E 19
I 19
			(void) strcpy(bp, pw->pw_name);
E 19
			*bp = toupper(*bp);
			while (*bp != '\0')
				bp++;
E 138
I 138
			if (*p == ' ')
				*bp++ = '_';
                        else if (*p == '&')
                        {
				(void) strcpy(bp, login);
				*bp = toupper(*bp);
				bp += strlen (bp);
			}
			else if (*p < 040 || *p >= 200 || 
				 strchr("_?()<>@:\\\".[]", *p) != NULL)
			{
				*bp++ = '=';
				*bp++ = "0123456789ABCDEF"[(*p >> 4) & 0xf];
				*bp++ = "0123456789ABCDEF"[*p & 0xf];
			}
			else
				*bp++ = *p;
E 138
D 90
			p++;
E 90
		}
D 138
		else
D 90
			*bp++ = *p++;
E 90
I 90
			*bp++ = *p;
E 138
I 138
		strcpy (bp, "?= ");
		bp += 3;
E 138
E 90
	}
I 138
	else
	{
		if (should_quote)
			*bp++ = '"';
		for (p = gecos; *p && *p != ',' && *p != ';' && *p != '%'; p++)
		{
			if (*p == '&')
			{
				(void) strcpy(bp, login);
				*bp = toupper(*bp);
				while (*bp != '\0')
					bp++;
			}
			else
			{
				if (*p == '"')
					*bp++ = '\\';
				*bp++ = *p;
			}
		}
		if (bp[-1] == '\\')
			*bp++ = '\\';
		if (should_quote)
			*bp++ = '"';
	}

E 138
I 89
D 93
	if (quoteit)
		*bp++ = '"';
E 93
E 89
	*bp = '\0';
I 138
	return should_quote == SHOULD_MIME;
E 138
I 16
}
/*
**  SAFEFILE -- return true if a file exists and is safe for a user.
**
**	Parameters:
**		fn -- filename to check.
D 126
**		uid -- uid to compare against.
E 126
I 126
**		uid -- user id to compare against.
**		gid -- group id to compare against.
**		uname -- user name to compare against (used for group
**			sets).
E 126
I 122
D 137
**		mustown -- to be safe, this uid must own the file.
E 137
I 137
**		flags -- modifiers:
D 143
**			SF_MUSTOWN -- "uid" must own this file.
**			SF_NOSLINK -- file cannot be a symbolic link.
E 143
I 143
**			SFF_MUSTOWN -- "uid" must own this file.
**			SFF_NOSLINK -- file cannot be a symbolic link.
E 143
E 137
E 122
**		mode -- mode bits that must match.
I 181
**		st -- if set, points to a stat structure that will
**			get the stat info for the file.
E 181
**
**	Returns:
D 105
**		TRUE if fn exists, is owned by uid, and matches mode.
**		FALSE otherwise.
E 105
I 105
**		0 if fn exists, is owned by uid, and matches mode.
**		An errno otherwise.  The actual errno is cleared.
E 105
**
**	Side Effects:
**		none.
*/

I 126
#include <grp.h>

E 126
I 120
#ifndef S_IXOTH
# define S_IXOTH	(S_IEXEC >> 6)
#endif

I 126
#ifndef S_IXGRP
# define S_IXGRP	(S_IEXEC >> 3)
#endif

E 126
I 122
#ifndef S_IXUSR
# define S_IXUSR	(S_IEXEC)
#endif

I 181
#define ST_MODE_NOFILE	0171147		/* unlikely to occur */

E 181
E 122
E 120
D 105
bool
E 105
I 105
int
E 105
D 122
safefile(fn, uid, mode)
E 122
I 122
D 126
safefile(fn, uid, mustown, mode)
E 126
I 126
D 137
safefile(fn, uid, gid, uname, mustown, mode)
E 137
I 137
D 181
safefile(fn, uid, gid, uname, flags, mode)
E 181
I 181
safefile(fn, uid, gid, uname, flags, mode, st)
E 181
E 137
E 126
E 122
	char *fn;
D 91
	int uid;
E 91
I 91
	uid_t uid;
I 126
	gid_t gid;
	char *uname;
E 126
I 122
D 137
	bool mustown;
E 137
I 137
	int flags;
E 137
E 122
E 91
	int mode;
I 181
	struct stat *st;
E 181
{
I 120
	register char *p;
I 126
	register struct group *gr = NULL;
E 126
E 120
	struct stat stbuf;

I 120
	if (tTd(54, 4))
D 122
		printf("safefile(%s, %d, %o): ", fn, uid, mode);
E 122
I 122
D 126
		printf("safefile(%s, %d, %d, %o): ", fn, uid, mustown, mode);
E 126
I 126
D 137
		printf("safefile(%s, uid=%d, gid=%d, mustown=%d, mode=%o):\n",
			fn, uid, gid, mustown, mode);
E 137
I 137
		printf("safefile(%s, uid=%d, gid=%d, flags=%x, mode=%o):\n",
			fn, uid, gid, flags, mode);
E 137
E 126
E 122
	errno = 0;
I 181
	if (st == NULL)
		st = &stbuf;
E 181

D 172
	for (p = fn; (p = strchr(++p, '/')) != NULL; *p = '/')
E 172
I 172
	if (!bitset(SFF_NOPATHCHECK, flags) ||
	    (uid == 0 && !bitset(SFF_ROOTOK, flags)))
E 172
	{
D 172
		*p = '\0';
D 122
		if (stat(fn, &stbuf) < 0 || !bitset(S_IXOTH, stbuf.st_mode))
E 122
I 122
D 126
		if (stat(fn, &stbuf) < 0 ||
		    !bitset(stbuf.st_uid == uid ? S_IXUSR : S_IXOTH,
			    stbuf.st_mode))
E 126
I 126
		if (stat(fn, &stbuf) < 0)
			break;
I 148
		if (uid == 0 && !bitset(SFF_ROOTOK, flags))
E 172
I 172
		/* check the path to the file for acceptability */
		for (p = fn; (p = strchr(++p, '/')) != NULL; *p = '/')
E 172
		{
D 172
			if (bitset(S_IXOTH, stbuf.st_mode))
E 172
I 172
			*p = '\0';
			if (stat(fn, &stbuf) < 0)
				break;
I 183
			if (uid == 0 && bitset(S_IWGRP|S_IWOTH, stbuf.st_mode))
				message("051 WARNING: writable directory %s",
					fn);
E 183
			if (uid == 0 && !bitset(SFF_ROOTOK, flags))
			{
				if (bitset(S_IXOTH, stbuf.st_mode))
					continue;
				break;
			}
			if (stbuf.st_uid == uid &&
			    bitset(S_IXUSR, stbuf.st_mode))
E 172
				continue;
D 172
			break;
		}
E 148
D 129
		if (stbuf.st_uid == uid && !bitset(S_IXUSR, stbuf.st_mode))
			break;
E 129
I 129
		if (stbuf.st_uid == uid && bitset(S_IXUSR, stbuf.st_mode))
			continue;
E 129
		if (stbuf.st_gid == gid && bitset(S_IXGRP, stbuf.st_mode))
			continue;
I 127
#ifndef NO_GROUP_SET
E 127
		if (uname != NULL &&
		    ((gr != NULL && gr->gr_gid == stbuf.st_gid) ||
		     (gr = getgrgid(stbuf.st_gid)) != NULL))
E 126
E 122
		{
D 126
			int ret = errno;
E 126
I 126
			register char **gp;
E 126

D 126
			if (ret == 0)
				ret = EACCES;
			if (tTd(54, 4))
				printf("[dir %s] %s\n", fn, errstring(ret));
			*p = '/';
			return ret;
E 126
I 126
D 166
			for (gp = gr->gr_mem; *gp != NULL; gp++)
E 166
I 166
			for (gp = gr->gr_mem; gp != NULL && *gp != NULL; gp++)
E 166
				if (strcmp(*gp, uname) == 0)
					break;
D 129
			if (*gp != NULL && !bitset(S_IXGRP, stbuf.st_mode))
				break;
E 129
I 129
D 166
			if (*gp != NULL && bitset(S_IXGRP, stbuf.st_mode))
E 166
I 166
			if (gp != NULL && *gp != NULL &&
E 172
I 172
			if (stbuf.st_gid == gid &&
E 172
			    bitset(S_IXGRP, stbuf.st_mode))
E 166
				continue;
E 129
E 126
D 172
		}
E 172
I 172
#ifndef NO_GROUP_SET
			if (uname != NULL &&
			    ((gr != NULL && gr->gr_gid == stbuf.st_gid) ||
			     (gr = getgrgid(stbuf.st_gid)) != NULL))
			{
				register char **gp;

				for (gp = gr->gr_mem; gp != NULL && *gp != NULL; gp++)
					if (strcmp(*gp, uname) == 0)
						break;
				if (gp != NULL && *gp != NULL &&
				    bitset(S_IXGRP, stbuf.st_mode))
					continue;
			}
E 172
I 127
#endif
E 127
I 126
D 172
		if (!bitset(S_IXOTH, stbuf.st_mode))
			break;
E 126
	}
I 126
	if (p != NULL)
	{
		int ret = errno;
E 172
I 172
			if (!bitset(S_IXOTH, stbuf.st_mode))
				break;
		}
		if (p != NULL)
		{
			int ret = errno;
E 172
E 126

I 126
D 172
		if (ret == 0)
			ret = EACCES;
		if (tTd(54, 4))
			printf("\t[dir %s] %s\n", fn, errstring(ret));
		*p = '/';
		return ret;
E 172
I 172
			if (ret == 0)
				ret = EACCES;
			if (tTd(54, 4))
				printf("\t[dir %s] %s\n", fn, errstring(ret));
			*p = '/';
			return ret;
		}
E 172
	}

I 137
#ifdef HASLSTAT
D 143
	if ((bitset(SF_NOSLINK, flags) ? lstat(fn, &stbuf)
				       : stat(fn, &stbuf)) < 0)
E 143
I 143
D 181
	if ((bitset(SFF_NOSLINK, flags) ? lstat(fn, &stbuf)
					: stat(fn, &stbuf)) < 0)
E 181
I 181
	if ((bitset(SFF_NOSLINK, flags) ? lstat(fn, st)
					: stat(fn, st)) < 0)
E 181
E 143
#else
E 137
E 126
E 120
D 105
	if (stat(fn, &stbuf) >= 0 && stbuf.st_uid == uid &&
	    (stbuf.st_mode & mode) == mode)
		return (TRUE);
I 51
	errno = 0;
E 51
	return (FALSE);
E 105
I 105
D 181
	if (stat(fn, &stbuf) < 0)
E 181
I 181
	if (stat(fn, st) < 0)
E 181
I 137
#endif
E 137
	{
		int ret = errno;

I 120
		if (tTd(54, 4))
D 126
			printf("%s\n", errstring(ret));
E 126
I 126
			printf("\t%s\n", errstring(ret));
E 126

E 120
		errno = 0;
I 181
		if (!bitset(SFF_CREAT, flags))
			return ret;

		/* check to see if legal to create the file */
		p = strrchr(fn, '/');
		if (p == NULL)
			return ENOTDIR;
		*p = '\0';
		if (stat(fn, &stbuf) >= 0)
		{
			int md = S_IWRITE|S_IEXEC;
			if (stbuf.st_uid != uid)
				md >>= 6;
			if ((stbuf.st_mode & md) != md)
				errno = EACCES;
		}
		ret = errno;
		if (tTd(54, 4))
			printf("\t[final dir %s uid %d mode %o] %s\n",
				fn, stbuf.st_uid, stbuf.st_mode,
				errstring(ret));
		*p = '/';
		st->st_mode = ST_MODE_NOFILE;
E 181
		return ret;
	}
I 137

#ifdef S_ISLNK
D 143
	if (bitset(SF_NOSLINK, flags) && S_ISLNK(stbuf.st_mode))
E 143
I 143
D 181
	if (bitset(SFF_NOSLINK, flags) && S_ISLNK(stbuf.st_mode))
E 181
I 181
	if (bitset(SFF_NOSLINK, flags) && S_ISLNK(st->st_mode))
E 181
E 143
	{
		if (tTd(54, 4))
D 144
			printf("\t[mode %o]\tEPERM\n");
E 144
I 144
D 181
			printf("\t[slink mode %o]\tEPERM\n", stbuf.st_mode);
E 181
I 181
			printf("\t[slink mode %o]\tEPERM\n", st->st_mode);
E 181
E 144
		return EPERM;
	}
#endif
D 183

E 183
I 183
	if (bitset(SFF_REGONLY, flags) && !S_ISREG(st->st_mode))
	{
		if (tTd(54, 4))
			printf("\t[non-reg mode %o]\tEPERM\n", st->st_mode);
		return EPERM;
	}
E 183
I 181
	if (bitset(S_IWUSR|S_IWGRP|S_IWOTH, mode) && bitset(0111, st->st_mode))
	{
		if (tTd(29, 5))
			printf("failed (mode %o: x bits)\n", st->st_mode);
D 183
		errno = EPERM;
		return FALSE;
E 183
I 183
		return EPERM;
E 183
	}

	if (bitset(SFF_SETUIDOK, flags))
	{
D 203
		if (bitset(S_ISUID, st->st_mode) &&
		    (st->st_uid != 0 || bitset(SFF_ROOTOK, flags)))
E 203
I 203
#ifdef SUID_ROOT_FILES_OK
		if (bitset(S_ISUID, st->st_mode))
#else
		if (bitset(S_ISUID, st->st_mode) && st->st_uid != 0)
#endif
E 203
		{
			uid = st->st_uid;
			uname = NULL;
		}
D 203
		if (bitset(S_ISGID, st->st_mode) &&
		    (st->st_gid != 0 || bitset(SFF_ROOTOK, flags)))
E 203
I 203
#ifdef SUID_ROOT_FILES_OK
		if (bitset(S_ISGID, st->st_mode))
#else
		if (bitset(S_ISGID, st->st_mode) && st->st_gid != 0)
#endif
E 203
			gid = st->st_gid;
	}

E 181
E 137
D 120
	if (stbuf.st_uid == uid && (stbuf.st_mode & mode) == mode)
E 120
I 120
D 122
	if (stbuf.st_uid != uid && uid == 0)
E 122
I 122
D 127
	if (stbuf.st_uid != uid || uid == 0 || !mustown)
E 127
I 127
D 145
	if (uid == 0)
E 145
I 145
	if (uid == 0 && !bitset(SFF_ROOTOK, flags))
E 145
E 127
E 122
		mode >>= 6;
I 127
D 181
	else if (stbuf.st_uid != uid)
E 181
I 181
	else if (st->st_uid != uid)
E 181
	{
		mode >>= 3;
D 181
		if (stbuf.st_gid == gid)
E 181
I 181
		if (st->st_gid == gid)
E 181
			;
#ifndef NO_GROUP_SET
		else if (uname != NULL &&
D 181
			 ((gr != NULL && gr->gr_gid == stbuf.st_gid) ||
			  (gr = getgrgid(stbuf.st_gid)) != NULL))
E 181
I 181
			 ((gr != NULL && gr->gr_gid == st->st_gid) ||
			  (gr = getgrgid(st->st_gid)) != NULL))
E 181
		{
			register char **gp;

			for (gp = gr->gr_mem; *gp != NULL; gp++)
				if (strcmp(*gp, uname) == 0)
					break;
			if (*gp == NULL)
				mode >>= 3;
		}
#endif
		else
			mode >>= 3;
	}
E 127
	if (tTd(54, 4))
D 126
		printf("[uid %d, stat %o] ", stbuf.st_uid, stbuf.st_mode);
E 126
I 126
D 127
		printf("\t[uid %d, stat %o] ", stbuf.st_uid, stbuf.st_mode);
E 127
I 127
		printf("\t[uid %d, stat %o, mode %o] ",
D 181
			stbuf.st_uid, stbuf.st_mode, mode);
E 127
E 126
D 122
	if ((stbuf.st_uid == uid || uid == 0) &&
E 122
I 122
D 136
	if ((stbuf.st_uid == uid || uid == 0 || !mustown) &&
E 136
I 136
D 137
	if ((stbuf.st_uid == uid || stbuf.st_uid == 0 || !mustown) &&
E 137
I 137
	if ((stbuf.st_uid == uid || stbuf.st_uid == 0 ||
E 181
I 181
			st->st_uid, st->st_mode, mode);
	if ((st->st_uid == uid || st->st_uid == 0 ||
E 181
D 143
	     !bitset(SF_MUSTOWN, flags)) &&
E 143
I 143
	     !bitset(SFF_MUSTOWN, flags)) &&
E 143
E 137
E 136
E 122
D 181
	    (stbuf.st_mode & mode) == mode)
E 181
I 181
	    (st->st_mode & mode) == mode)
E 181
	{
		if (tTd(54, 4))
D 126
			printf("OK\n");
E 126
I 126
			printf("\tOK\n");
E 126
E 120
		return 0;
D 120
	return EPERM;
E 120
I 120
	}
	if (tTd(54, 4))
D 126
		printf("EACCES\n");
E 126
I 126
		printf("\tEACCES\n");
E 126
	return EACCES;
I 181
}
/*
**  SAFEFOPEN -- do a file open with extra checking
**
**	Parameters:
**		fn -- the file name to open.
**		omode -- the open-style mode flags.
**		cmode -- the create-style mode flags.
**		sff -- safefile flags.
**
**	Returns:
**		Same as fopen.
*/

I 187
#ifndef O_ACCMODE
# define O_ACCMODE	(O_RDONLY|O_WRONLY|O_RDWR)
#endif

E 187
FILE *
safefopen(fn, omode, cmode, sff)
	char *fn;
	int omode;
	int cmode;
	int sff;
{
	int rval;
	FILE *fp;
	int smode;
	struct stat stb, sta;
D 200
	extern char RealUserName[];
E 200

	if (bitset(O_CREAT, omode))
		sff |= SFF_CREAT;
	smode = 0;
	switch (omode & O_ACCMODE)
	{
	  case O_RDONLY:
		smode = S_IREAD;
		break;

	  case O_WRONLY:
		smode = S_IWRITE;
		break;

	  case O_RDWR:
		smode = S_IREAD|S_IWRITE;
		break;

	  default:
		smode = 0;
		break;
	}
D 183
	rval = safefile(fn, RealUid, RealGid, RealUserName, sff, smode, &stb);
E 183
I 183
	if (bitset(SFF_OPENASROOT, sff))
		rval = safefile(fn, 0, 0, NULL, sff, smode, &stb);
	else
		rval = safefile(fn, RealUid, RealGid, RealUserName,
				sff, smode, &stb);
E 183
	if (rval != 0)
	{
		errno = rval;
		return NULL;
	}
	if (stb.st_mode == ST_MODE_NOFILE)
		omode |= O_EXCL;

	fp = dfopen(fn, omode, cmode);
	if (fp == NULL)
		return NULL;
	if (bitset(O_EXCL, omode))
		return fp;
	if (fstat(fileno(fp), &sta) < 0 ||
	    sta.st_nlink != stb.st_nlink ||
	    sta.st_dev != stb.st_dev ||
	    sta.st_ino != stb.st_ino ||
	    sta.st_uid != stb.st_uid ||
	    sta.st_gid != stb.st_gid)
	{
		syserr("554 cannot open: file %s changed after open", fn);
D 183
		errno = EPERM;
E 183
		fclose(fp);
I 183
		errno = EPERM;
E 183
		return NULL;
	}
	return fp;
E 181
E 120
E 105
E 16
}
/*
I 17
**  FIXCRLF -- fix <CR><LF> in line.
**
**	Looks for the <CR><LF> combination and turns it into the
**	UNIX canonical <NL> character.  It only takes one line,
**	i.e., it is assumed that the first <NL> found is the end
**	of the line.
**
**	Parameters:
**		line -- the line to fix.
**		stripnl -- if true, strip the newline also.
**
**	Returns:
**		none.
**
**	Side Effects:
**		line is changed in place.
*/

I 198
void
E 198
fixcrlf(line, stripnl)
	char *line;
	bool stripnl;
{
	register char *p;

D 94
	p = index(line, '\n');
E 94
I 94
	p = strchr(line, '\n');
E 94
	if (p == NULL)
		return;
D 18
	if (*p == '\r')
E 18
I 18
D 76
	if (p[-1] == '\r')
E 76
I 76
	if (p > line && p[-1] == '\r')
E 76
E 18
		p--;
	if (!stripnl)
		*p++ = '\n';
	*p = '\0';
}
/*
E 17
E 13
D 61
**  SYSLOG -- fake entry to fool lint
*/

# ifdef LOG
# ifdef lint

/*VARARGS2*/
syslog(pri, fmt, args)
	int pri;
	char *fmt;
{
	pri = *fmt;
	args = pri;
	pri = args;
}

# endif lint
# endif LOG
I 22
/*
E 61
**  DFOPEN -- determined file open
**
**	This routine has the semantics of fopen, except that it will
**	keep trying a few times to make this happen.  The idea is that
**	on very loaded systems, we may run out of resources (inodes,
**	whatever), so this tries to get around it.
*/
D 187

I 122
#ifndef O_ACCMODE
# define O_ACCMODE	(O_RDONLY|O_WRONLY|O_RDWR)
#endif
E 187

E 122
I 115
struct omodes
{
	int	mask;
	int	mode;
	char	*farg;
} OpenModes[] =
{
	O_ACCMODE,		O_RDONLY,		"r",
	O_ACCMODE|O_APPEND,	O_WRONLY,		"w",
	O_ACCMODE|O_APPEND,	O_WRONLY|O_APPEND,	"a",
	O_TRUNC,		0,			"w+",
	O_APPEND,		O_APPEND,		"a+",
	0,			0,			"r+",
};

E 115
FILE *
D 115
dfopen(filename, mode)
E 115
I 115
dfopen(filename, omode, cmode)
E 115
	char *filename;
D 115
	char *mode;
E 115
I 115
	int omode;
	int cmode;
E 115
{
	register int tries;
D 115
	register FILE *fp;
E 115
I 115
D 118
	FILE *fp;
E 118
	int fd;
	register struct omodes *om;
E 115
I 112
	struct stat st;
E 112
D 42
	extern int errno;
E 42

I 115
	for (om = OpenModes; om->mask != 0; om++)
		if ((omode & om->mask) == om->mode)
			break;

E 115
	for (tries = 0; tries < 10; tries++)
	{
D 70
		sleep(10 * tries);
E 70
I 70
		sleep((unsigned) (10 * tries));
E 70
		errno = 0;
D 115
		fp = fopen(filename, mode);
D 42
		if (fp != NULL || errno != ENFILE)
E 42
I 42
		if (fp != NULL)
E 115
I 115
		fd = open(filename, omode, cmode);
		if (fd >= 0)
E 115
E 42
			break;
I 42
D 152
		if (errno != ENFILE && errno != EINTR)
E 152
I 152
		switch (errno)
		{
		  case ENFILE:		/* system file table full */
		  case EINTR:		/* interrupted syscall */
#ifdef ETXTBSY
		  case ETXTBSY:		/* Apollo: net file locked */
#endif
E 152
D 153
			break;
I 152

		  default:
E 153
			continue;
		}
		break;
E 152
E 42
	}
I 51
D 92
	errno = 0;
E 92
I 92
D 112
	if (fp != NULL)
E 112
I 112
D 115
	if (fp != NULL && fstat(fileno(fp), &st) >= 0 && S_ISREG(st.st_mode))
E 115
I 115
	if (fd >= 0 && fstat(fd, &st) >= 0 && S_ISREG(st.st_mode))
E 115
E 112
	{
D 110
#ifdef FLOCK
E 110
		int locktype;
I 110
D 116
		extern bool lockfile();
E 116
E 110

		/* lock the file to avoid accidental conflicts */
D 115
		if (*mode == 'w' || *mode == 'a')
E 115
I 115
		if ((omode & O_ACCMODE) != O_RDONLY)
E 115
			locktype = LOCK_EX;
		else
			locktype = LOCK_SH;
D 110
		(void) flock(fileno(fp), locktype);
#endif
E 110
I 110
D 115
		(void) lockfile(fileno(fp), filename, locktype);
E 115
I 115
D 128
		(void) lockfile(fd, filename, locktype);
E 128
I 128
		(void) lockfile(fd, filename, NULL, locktype);
E 128
E 115
E 110
		errno = 0;
	}
E 92
E 51
D 115
	return (fp);
E 115
I 115
D 123
	return fdopen(fd, om->farg);
E 123
I 123
	if (fd < 0)
		return NULL;
	else
		return fdopen(fd, om->farg);
E 123
E 115
}
I 24
/*
**  PUTLINE -- put a line like fputs obeying SMTP conventions
**
I 30
**	This routine always guarantees outputing a newline (or CRLF,
**	as appropriate) at the end of the string.
**
E 30
**	Parameters:
**		l -- line to put.
D 150
**		fp -- file to put it onto.
I 45
D 46
**		crlf -- if set, output Carriage Return/Line Feed on lines
**			instead of newline.
E 45
**		fullsmtp -- if set, obey strictest SMTP conventions.
E 46
I 46
**		m -- the mailer used to control output.
E 150
I 150
**		mci -- the mailer connection information.
E 150
E 46
**
**	Returns:
**		none
**
**	Side Effects:
**		output of l to fp.
*/

I 198
void
E 198
D 30
# define SMTPLINELIM	120	/* maximum line length */
E 30
I 30
D 85
# define SMTPLINELIM	990	/* maximum line length */
E 30

E 85
D 45
putline(l, fp, fullsmtp)
E 45
I 45
D 46
putline(l, fp, crlf, fullsmtp)
E 46
I 46
D 150
putline(l, fp, m)
E 150
I 150
putline(l, mci)
E 150
E 46
E 45
D 30
	char *l;
E 30
I 30
	register char *l;
E 30
D 150
	FILE *fp;
I 45
D 46
	bool crlf;
E 45
	bool fullsmtp;
E 46
I 46
	MAILER *m;
E 150
I 150
	register MCI *mci;
E 150
E 46
{
I 184
D 198
	extern void putxline();

E 198
D 191
	putxline(l, mci, TRUE);
E 191
I 191
	putxline(l, mci, PXLF_MAPFROM);
E 191
}
I 191
/*
**  PUTXLINE -- putline with flags bits.
**
**	This routine always guarantees outputing a newline (or CRLF,
**	as appropriate) at the end of the string.
**
**	Parameters:
**		l -- line to put.
**		mci -- the mailer connection information.
**		pxflags -- flag bits:
**		    PXLF_MAPFROM -- map From_ to >From_.
**		    PXLF_STRIP8BIT -- strip 8th bit.
**
**	Returns:
**		none
**
**	Side Effects:
**		output of l to fp.
*/
E 191

void
D 191
putxline(l, mci, mapfrom)
E 191
I 191
putxline(l, mci, pxflags)
E 191
	register char *l;
	register MCI *mci;
D 191
	bool mapfrom;
E 191
I 191
	int pxflags;
E 191
{
E 184
	register char *p;
I 30
D 82
	char svchar;
E 82
I 82
	register char svchar;
I 151
	int slop = 0;
E 151
E 82
I 46
D 47
	char *crlfstring = "\r\n";
E 47
E 46
E 30
D 25
	char s1, s2;
E 25

I 50
	/* strip out 0200 bits -- these can look like TELNET protocol */
D 85
	if (bitnset(M_LIMITS, m->m_flags))
E 85
I 85
D 150
	if (bitnset(M_7BITS, m->m_flags))
E 150
I 150
D 191
	if (bitset(MCIF_7BIT, mci->mci_flags))
E 191
I 191
	if (bitset(MCIF_7BIT, mci->mci_flags) ||
	    bitset(PXLF_STRIP8BIT, pxflags))
E 191
E 150
E 85
	{
D 82
		p = l;
		while ((*p++ &= ~0200) != 0)
			continue;
E 82
I 82
D 118
		for (p = l; svchar = *p; ++p)
			if (svchar & 0200)
E 118
I 118
		for (p = l; (svchar = *p) != '\0'; ++p)
			if (bitset(0200, svchar))
E 118
				*p = svchar &~ 0200;
E 82
	}

E 50
I 46
D 47
	if (!bitset(M_CRLF, m->m_flags))
		crlfstring++;

E 47
E 46
D 30
	if (!fullsmtp)
E 30
I 30
	do
E 30
	{
D 30
		fputs(l, fp);
		return;
	}
E 30
I 30
		/* find the end of the line */
D 94
		p = index(l, '\n');
E 94
I 94
		p = strchr(l, '\n');
E 94
		if (p == NULL)
			p = &l[strlen(l)];
E 30

I 122
		if (TrafficLogFile != NULL)
			fprintf(TrafficLogFile, "%05d >>> ", getpid());

E 122
D 30
	/* find the end of the line */
D 25
	p = index('\n', l);
E 25
I 25
	p = index(l, '\n');
E 25
	if (p == NULL)
		p = &l[strlen(l)];
E 30
I 30
		/* check for line overflow */
D 46
		while (fullsmtp && (p - l) > SMTPLINELIM)
E 46
I 46
D 49
		while (bitset(M_LIMITS, m->m_flags) && (p - l) > SMTPLINELIM)
E 49
I 49
D 50
		while (bitnset(M_LIMITS, m->m_flags) && (p - l) > SMTPLINELIM)
E 50
I 50
D 85
		while ((p - l) > SMTPLINELIM && bitnset(M_LIMITS, m->m_flags))
E 85
I 85
D 150
		while (m->m_linelimit > 0 && (p - l) > m->m_linelimit)
E 150
I 150
		while (mci->mci_mailer->m_linelimit > 0 &&
D 151
		       (p - l) > mci->mci_mailer->m_linelimit)
E 151
I 151
		       (p - l + slop) > mci->mci_mailer->m_linelimit)
E 151
E 150
E 85
E 50
E 49
E 46
		{
D 85
			register char *q = &l[SMTPLINELIM - 1];
E 85
I 85
D 150
			register char *q = &l[m->m_linelimit - 1];
E 150
I 150
D 151
			register char *q = &l[mci->mci_mailer->m_linelimit - 1];
E 151
I 151
			register char *q = &l[mci->mci_mailer->m_linelimit - slop - 1];
E 151
E 150
E 85
E 30

D 30
	/* check for line overflow */
	while (p - l > SMTPLINELIM)
	{
		register char *q = &l[SMTPLINELIM - 1];
		char svchar = *q;
E 30
I 30
			svchar = *q;
			*q = '\0';
I 46
D 49
			if (l[0] == '.' && bitset(M_XDOT, m->m_flags))
E 49
I 49
D 150
			if (l[0] == '.' && bitnset(M_XDOT, m->m_flags))
E 150
I 150
D 151
			if (l[0] == '.' && bitnset(M_XDOT, mci->mci_mailer->m_flags))
E 151
I 151
			if (l[0] == '.' && slop == 0 &&
			    bitnset(M_XDOT, mci->mci_mailer->m_flags))
E 151
E 150
I 122
			{
E 122
E 49
D 66
				fputc('.', fp);
E 66
I 66
D 150
				(void) putc('.', fp);
E 150
I 150
				(void) putc('.', mci->mci_out);
E 150
I 122
				if (TrafficLogFile != NULL)
					(void) putc('.', TrafficLogFile);
I 184
			}
D 191
			else if (l[0] == 'F' && slop == 0 && mapfrom &&
				 strncmp(l, "From ", 5) == 0 &
E 191
I 191
			else if (l[0] == 'F' && slop == 0 &&
				 bitset(PXLF_MAPFROM, pxflags) &&
				 strncmp(l, "From ", 5) == 0 &&
E 191
				 bitnset(M_ESCFROM, mci->mci_mailer->m_flags))
			{
				(void) putc('>', mci->mci_out);
				if (TrafficLogFile != NULL)
					(void) putc('>', TrafficLogFile);
E 184
			}
E 122
E 66
E 46
D 150
			fputs(l, fp);
D 45
			fputs("!\r\n", fp);
E 45
I 45
D 66
			fputc('!', fp);
E 66
I 66
			(void) putc('!', fp);
E 66
D 46
			if (crlf)
				fputc('\r', fp);
			fputc('\n', fp);
E 46
I 46
D 47
			fputs(crlfstring, fp);
E 47
I 47
D 48
			fputs(crlf(m), fp);
E 48
I 48
			fputs(m->m_eol, fp);
E 150
I 150
			fputs(l, mci->mci_out);
			(void) putc('!', mci->mci_out);
			fputs(mci->mci_mailer->m_eol, mci->mci_out);
I 151
			(void) putc(' ', mci->mci_out);
E 151
E 150
I 122
			if (TrafficLogFile != NULL)
D 151
				fprintf(TrafficLogFile, "%s!\n%05d >>> ",
E 151
I 151
				fprintf(TrafficLogFile, "%s!\n%05d >>>  ",
E 151
					l, getpid());
E 122
E 48
E 47
E 46
E 45
			*q = svchar;
			l = q;
I 151
			slop = 1;
E 151
		}
E 30

D 30
		*q = '\0';
E 30
I 30
		/* output last part */
D 82
		svchar = *p;
		*p = '\0';
E 82
I 46
D 49
		if (l[0] == '.' && bitset(M_XDOT, m->m_flags))
E 49
I 49
D 150
		if (l[0] == '.' && bitnset(M_XDOT, m->m_flags))
E 150
I 150
D 151
		if (l[0] == '.' && bitnset(M_XDOT, mci->mci_mailer->m_flags))
E 151
I 151
		if (l[0] == '.' && slop == 0 &&
		    bitnset(M_XDOT, mci->mci_mailer->m_flags))
E 151
E 150
I 122
		{
E 122
E 49
D 66
			fputc('.', fp);
E 66
I 66
D 150
			(void) putc('.', fp);
E 150
I 150
			(void) putc('.', mci->mci_out);
E 150
I 122
			if (TrafficLogFile != NULL)
				(void) putc('.', TrafficLogFile);
		}
		if (TrafficLogFile != NULL)
			fprintf(TrafficLogFile, "%.*s\n", p - l, l);
E 122
E 66
E 46
E 30
D 82
		fputs(l, fp);
E 82
I 82
		for ( ; l < p; ++l)
D 150
			(void) putc(*l, fp);
E 82
D 30
		fputs("!\r\n", fp);
		*q = svchar;
		l = q;
	}

	/* output last part */
	*p = '\0';
	fputs(l, fp);
	fputs("\r\n", fp);
	*p = '\n';
E 30
I 30
D 45
		if (fullsmtp)
E 45
I 45
D 46
		if (crlf)
E 45
			fputc('\r', fp);
		fputc('\n', fp);
E 46
I 46
D 47
		fputs(crlfstring, fp);
E 47
I 47
D 48
		fputs(crlf(m), fp);
E 48
I 48
		fputs(m->m_eol, fp);
E 150
I 150
			(void) putc(*l, mci->mci_out);
		fputs(mci->mci_mailer->m_eol, mci->mci_out);
E 150
E 48
E 47
E 46
D 82
		*p = svchar;
		l = p;
E 82
		if (*l == '\n')
D 82
			l++;
E 82
I 82
			++l;
E 82
	} while (l[0] != '\0');
E 30
}
I 28
/*
**  XUNLINK -- unlink a file, doing logging as appropriate.
**
**	Parameters:
**		f -- name of file to unlink.
**
**	Returns:
**		none.
**
**	Side Effects:
**		f is unlinked.
*/

I 198
void
E 198
xunlink(f)
	char *f;
{
	register int i;

# ifdef LOG
D 102
	if (LogLevel > 20)
D 32
		syslog(LOG_DEBUG, "%s: unlink %s\n", MsgId, f);
E 32
I 32
		syslog(LOG_DEBUG, "%s: unlink %s\n", CurEnv->e_id, f);
E 102
I 102
	if (LogLevel > 98)
		syslog(LOG_DEBUG, "%s: unlink %s", CurEnv->e_id, f);
E 102
E 32
D 94
# endif LOG
E 94
I 94
# endif /* LOG */
E 94

	i = unlink(f);
# ifdef LOG
D 102
	if (i < 0 && LogLevel > 21)
E 102
I 102
	if (i < 0 && LogLevel > 97)
E 102
D 36
		syslog(LOG_DEBUG, "%s: unlink-fail %e");
E 36
I 36
		syslog(LOG_DEBUG, "%s: unlink-fail %d", f, errno);
E 36
D 94
# endif LOG
E 94
I 94
# endif /* LOG */
E 94
}
I 29
/*
I 109
**  XFCLOSE -- close a file, doing logging as appropriate.
**
**	Parameters:
**		fp -- file pointer for the file to close
**		a, b -- miscellaneous crud to print for debugging
**
**	Returns:
**		none.
**
**	Side Effects:
**		fp is closed.
*/

I 198
void
E 198
xfclose(fp, a, b)
	FILE *fp;
	char *a, *b;
{
D 111
	if (tTd(9, 99))
E 111
I 111
	if (tTd(53, 99))
E 111
		printf("xfclose(%x) %s %s\n", fp, a, b);
I 130
D 202
#ifdef XDEBUG
E 202
I 202
#if XDEBUG
E 202
	if (fileno(fp) == 1)
		syserr("xfclose(%s %s): fd = 1", a, b);
#endif
E 130
D 111
	if (fclose(fp) < 0 && tTd(9, 99))
E 111
I 111
	if (fclose(fp) < 0 && tTd(53, 99))
E 111
		printf("xfclose FAILURE: %s\n", errstring(errno));
}
/*
E 109
D 53
**  SFGETS -- "safe" fgets -- times out.
E 53
I 53
**  SFGETS -- "safe" fgets -- times out and ignores random interrupts.
E 53
**
**	Parameters:
**		buf -- place to put the input line.
**		siz -- size of buf.
**		fp -- file to read from.
I 99
**		timeout -- the timeout before error occurs.
I 117
**		during -- what we are trying to read (for error messages).
E 117
E 99
**
**	Returns:
D 54
**		NULL on error (including timeout).
E 54
I 54
**		NULL on error (including timeout).  This will also leave
**			buf containing a null string.
E 54
**		buf otherwise.
**
**	Side Effects:
**		none.
*/

D 36
jmp_buf	TimeoFrame;
E 36
I 36
D 53
static bool	TimeoutFlag;
E 53
I 53
static jmp_buf	CtxReadTimeout;
I 125
D 173
static int	readtimeout();
E 173
I 173
static void	readtimeout();
E 173
I 159
D 164
static EVENT	*GlobalTimeout = NULL;
static bool	EnableTimeout = FALSE;
static int	ReadProgress;
E 164
E 159
E 125
E 53
E 36

I 56
D 74
#ifndef ETIMEDOUT
#define ETIMEDOUT	EINTR
#endif

E 74
E 56
char *
D 99
sfgets(buf, siz, fp)
E 99
I 99
D 117
sfgets(buf, siz, fp, timeout)
E 117
I 117
sfgets(buf, siz, fp, timeout, during)
E 117
E 99
	char *buf;
	int siz;
	FILE *fp;
I 99
	time_t timeout;
I 117
	char *during;
E 117
E 99
{
D 36
	register EVENT *ev;
E 36
I 36
	register EVENT *ev = NULL;
E 36
	register char *p;
D 81
	extern readtimeout();
E 81
I 81
D 125
	static int readtimeout();
E 125
E 81

I 155
	if (fp == NULL)
	{
		buf[0] = '\0';
		return NULL;
	}

E 155
I 53
	/* set the timeout */
E 53
D 34
	ev = setevent(ReadTimeout, readtimeout, 0);
E 34
D 36
	if (setjmp(TimeoFrame) != 0)
		return (NULL);
I 34
	ev = setevent(ReadTimeout, readtimeout, 0);
E 34
	p = fgets(buf, siz, fp);
E 36
I 36
D 99
	if (ReadTimeout != 0)
E 99
I 99
	if (timeout != 0)
E 99
I 53
	{
		if (setjmp(CtxReadTimeout) != 0)
		{
I 75
# ifdef LOG
E 75
I 56
D 74
			errno = ETIMEDOUT;
E 56
D 68
			syserr("sfgets: timeout on read (mailer may be hung)");
E 68
I 68
D 69
			if (RealHostName == NULL)
				syserr("timeout on read");
			else
				syserr("net timeout reading from %s", RealHostName);
			errno = ETIMEDOUT;
E 69
I 69
			syserr("net timeout");
E 74
I 74
			syslog(LOG_NOTICE,
D 117
			    "timeout waiting for input from %s\n",
D 78
			    RealHostName);
E 78
I 78
D 101
			    RealHostName? RealHostName: "local");
E 101
I 101
			    CurHostName? CurHostName: "local");
E 117
I 117
			    "timeout waiting for input from %s during %s\n",
			    CurHostName? CurHostName: "local", during);
E 117
E 101
E 78
I 75
# endif
E 75
			errno = 0;
D 77
			usrerr("timeout waiting for input");
E 77
I 77
D 117
			usrerr("451 timeout waiting for input");
E 117
I 117
			usrerr("451 timeout waiting for input during %s",
				during);
E 117
E 77
E 74
E 69
E 68
I 62
			buf[0] = '\0';
I 122
D 202
#ifdef XDEBUG
E 202
I 202
#if XDEBUG
E 202
			checkfd012(during);
#endif
E 122
E 62
			return (NULL);
		}
E 53
D 56
		ev = setevent(ReadTimeout, readtimeout, 0);
E 56
I 56
D 99
		ev = setevent((time_t) ReadTimeout, readtimeout, 0);
E 99
I 99
D 159
		ev = setevent(timeout, readtimeout, 0);
E 159
I 159
D 164
		if (GlobalTimeout == NULL)
			ev = setevent(timeout, readtimeout, 0);
		else
			EnableTimeout = TRUE;
E 164
I 164
		ev = setevent(timeout, readtimeout, 0);
E 164
E 159
E 99
E 56
D 53
	TimeoutFlag = FALSE;
E 53
I 53
	}

	/* try to read */
E 53
D 54
	do
E 54
I 54
	p = NULL;
D 147
	while (p == NULL && !feof(fp) && !ferror(fp))
E 147
I 147
	while (!feof(fp) && !ferror(fp))
E 147
E 54
	{
		errno = 0;
		p = fgets(buf, siz, fp);
D 53
	} while (!(p != NULL || TimeoutFlag || errno != EINTR));
E 53
I 53
D 54
	} while (p == NULL && errno == EINTR);
E 54
I 54
D 147
		if (errno == EINTR)
			clearerr(fp);
I 146
		else if (errno == EBADF)
E 147
I 147
		if (p != NULL || errno != EINTR)
E 147
			break;
I 147
		clearerr(fp);
E 147
E 146
	}
E 54

	/* clear the event if it has not sprung */
E 53
E 36
D 159
	clrevent(ev);
E 159
I 159
D 164
	if (GlobalTimeout == NULL)
		clrevent(ev);
	else
		EnableTimeout = FALSE;
E 164
I 164
	clrevent(ev);
E 164
E 159
I 53

	/* clean up the books and exit */
E 53
I 37
	LineNumber++;
I 54
	if (p == NULL)
I 57
	{
E 57
		buf[0] = '\0';
I 122
		if (TrafficLogFile != NULL)
			fprintf(TrafficLogFile, "%05d <<< [EOF]\n", getpid());
E 122
E 54
I 43
D 53
	if (TimeoutFlag)
		syserr("sfgets: timeout on read (mailer may be hung)");
E 53
E 43
E 37
D 57
	return (p);
E 57
I 57
		return (NULL);
	}
I 122
	if (TrafficLogFile != NULL)
		fprintf(TrafficLogFile, "%05d <<< %s", getpid(), buf);
E 122
D 85
	for (p = buf; *p != '\0'; p++)
		*p &= ~0200;
E 85
I 85
D 114
	if (!EightBit)
E 114
I 114
D 163
	if (SevenBit)
E 163
I 163
	if (SevenBitInput)
	{
E 163
E 114
		for (p = buf; *p != '\0'; p++)
			*p &= ~0200;
I 163
	}
	else if (!HasEightBits)
	{
		for (p = buf; *p != '\0'; p++)
		{
			if (bitset(0200, *p))
			{
				HasEightBits = TRUE;
				break;
			}
		}
	}
E 163
E 85
	return (buf);
E 57
}

I 159
D 164
void
sfgetset(timeout)
	time_t timeout;
{
	/* cancel pending timer */
	if (GlobalTimeout != NULL)
	{
		clrevent(GlobalTimeout);
		GlobalTimeout = NULL;
	}

	/* schedule fresh one if so requested */
	if (timeout != 0)
	{
		ReadProgress = LineNumber;
		GlobalTimeout = setevent(timeout, readtimeout, timeout);
	}
}

E 164
E 159
D 173
static
E 173
I 173
static void
E 173
D 159
readtimeout()
E 159
I 159
readtimeout(timeout)
	time_t timeout;
E 159
{
D 36
	longjmp(TimeoFrame, 1);
E 36
I 36
D 53
	TimeoutFlag = TRUE;
E 53
I 53
D 159
	longjmp(CtxReadTimeout, 1);
E 159
I 159
D 164
	/* terminate if ordinary timeout */
	if (GlobalTimeout == NULL)
		longjmp(CtxReadTimeout, 1);

	/* terminate if no progress was made -- reset state */
	if (EnableTimeout && (LineNumber <= ReadProgress))
	{
		EnableTimeout = FALSE;
		GlobalTimeout = NULL;
		longjmp(CtxReadTimeout, 2);
	}

	/* schedule a new timeout */
	GlobalTimeout = NULL;
	sfgetset(timeout);
E 164
I 164
	longjmp(CtxReadTimeout, 1);
E 164
E 159
E 53
E 36
}
I 31
/*
**  FGETFOLDED -- like fgets, but know about folded lines.
**
**	Parameters:
**		buf -- place to put result.
**		n -- bytes available.
**		f -- file to read from.
**
**	Returns:
D 96
**		buf on success, NULL on error or EOF.
E 96
I 96
**		input line(s) on success, NULL on error or EOF.
**		This will normally be buf -- unless the line is too
**			long, when it will be xalloc()ed.
E 96
**
**	Side Effects:
**		buf gets lines from f, with continuation lines (lines
**		with leading white space) appended.  CRLF's are mapped
**		into single newlines.  Any trailing NL is stripped.
*/

char *
fgetfolded(buf, n, f)
	char *buf;
	register int n;
	FILE *f;
{
	register char *p = buf;
I 96
	char *bp = buf;
E 96
	register int i;

	n--;
D 37
	while (fgets(p, n, f) != NULL)
E 37
I 37
D 44
	while (sfgets(p, n, f) != NULL)
E 44
I 44
D 60
	while (fgets(p, n, f) != NULL)
E 60
I 60
	while ((i = getc(f)) != EOF)
E 60
E 44
E 37
	{
I 44
D 60
		LineNumber++;
E 44
		fixcrlf(p, TRUE);
		i = fgetc(f);
		if (i != EOF)
			ungetc(i, f);
		if (i != ' ' && i != '\t')
			return (buf);
		i = strlen(p);
		p += i;
		*p++ = '\n';
		n -= i + 1;
E 60
I 60
		if (i == '\r')
		{
			i = getc(f);
			if (i != '\n')
			{
				if (i != EOF)
D 66
					ungetc(i, f);
E 66
I 66
					(void) ungetc(i, f);
E 66
				i = '\r';
			}
		}
D 96
		if (--n > 0)
			*p++ = i;
I 87
		else if (n == 0)
			nmessage(Arpa_Info, "warning: line truncated");
E 96
I 96
		if (--n <= 0)
		{
			/* allocate new space */
			char *nbp;
			int nn;

			nn = (p - bp);
D 97
			if (nn < 1024)
E 97
I 97
			if (nn < MEMCHUNKSIZE)
E 97
				nn *= 2;
			else
D 97
				nn += 1024;
E 97
I 97
				nn += MEMCHUNKSIZE;
E 97
			nbp = xalloc(nn);
			bcopy(bp, nbp, p - bp);
			p = &nbp[p - bp];
			if (bp != buf)
				free(bp);
			bp = nbp;
			n = nn - (p - bp);
		}
		*p++ = i;
E 96
E 87
		if (i == '\n')
		{
			LineNumber++;
			i = getc(f);
			if (i != EOF)
D 66
				ungetc(i, f);
E 66
I 66
				(void) ungetc(i, f);
E 66
			if (i != ' ' && i != '\t')
D 87
			{
				*--p = '\0';
I 85
				if (!EightBit)
				{
					/* headers always have to be 7-bit */
					for (p = buf; (i = *p) != '\0'; *p++)
						if (bitset(0200, i))
							*p = i & ~0200;
				}
E 85
				return (buf);
			}
E 87
I 87
				break;
E 87
		}
E 60
	}
D 87
	return (NULL);
E 87
I 87
D 96
	if (p == buf)
E 96
I 96
	if (p == bp)
E 96
		return (NULL);
D 196
	*--p = '\0';
E 196
I 196
D 197
	if (*--p == '\n')
		*p = '\0';
E 197
I 197
	if (p[-1] == '\n')
		p--;
	*p = '\0';
E 197
E 196
D 88
	if (!EightBit)
	{
		/* headers always have to be 7-bit */
		for (p = buf; (i = *p) != '\0'; *p++)
			if (bitset(0200, i))
				*p = i & ~0200;
	}
E 88
D 96
	return (buf);
E 96
I 96
	return (bp);
E 96
E 87
}
I 33
/*
D 42
**  PINTVL -- produce printable version of a time interval
**
**	Parameters:
**		intvl -- the interval to be converted
**		brief -- if TRUE, print this in an extremely compact form
**			(basically used for logging).
**
**	Returns:
**		A pointer to a string version of intvl suitable for
**			printing or framing.
**
**	Side Effects:
**		none.
**
**	Warning:
**		The string returned is in a static buffer.
*/

# define PLURAL(n)	((n) == 1 ? "" : "s")

char *
pintvl(intvl, brief)
	time_t intvl;
	bool brief;
{
	static char buf[MAXNAME];
	register char *p;
	int wk, dy, hr, mi, se;

	if (intvl == 0 && !brief)
		return ("zero seconds");

	/* decode the interval into weeks, days, hours, minutes, seconds */
	se = intvl % 60;
	intvl /= 60;
	mi = intvl % 60;
	intvl /= 60;
	hr = intvl % 24;
	intvl /= 24;
	if (brief)
		dy = intvl;
	else
	{
		dy = intvl % 7;
		intvl /= 7;
		wk = intvl;
	}

	/* now turn it into a sexy form */
	p = buf;
	if (brief)
	{
		if (dy > 0)
		{
			(void) sprintf(p, "%d+", dy);
			p += strlen(p);
		}
		(void) sprintf(p, "%02d:%02d:%02d", hr, mi, se);
		return (buf);
	}

	/* use the verbose form */
	if (wk > 0)
	{
		(void) sprintf(p, ", %d week%s", wk, PLURAL(wk));
		p += strlen(p);
	}
	if (dy > 0)
	{
		(void) sprintf(p, ", %d day%s", dy, PLURAL(dy));
		p += strlen(p);
	}
	if (hr > 0)
	{
		(void) sprintf(p, ", %d hour%s", hr, PLURAL(hr));
		p += strlen(p);
	}
	if (mi > 0)
	{
		(void) sprintf(p, ", %d minute%s", mi, PLURAL(mi));
		p += strlen(p);
	}
	if (se > 0)
	{
		(void) sprintf(p, ", %d second%s", se, PLURAL(se));
		p += strlen(p);
	}

	return (buf + 2);
}
I 35
/*
E 42
**  CURTIME -- return current time.
**
**	Parameters:
**		none.
**
**	Returns:
**		the current time.
**
**	Side Effects:
**		none.
*/

time_t
curtime()
{
	auto time_t t;

	(void) time(&t);
	return (t);
}
I 39
/*
**  ATOBOOL -- convert a string representation to boolean.
**
**	Defaults to "TRUE"
**
**	Parameters:
**		s -- string to convert.  Takes "tTyY" as true,
**			others as false.
**
**	Returns:
**		A boolean representation of the string.
**
**	Side Effects:
**		none.
*/

bool
atobool(s)
	register char *s;
{
D 94
	if (*s == '\0' || index("tTyY", *s) != NULL)
E 94
I 94
D 124
	if (*s == '\0' || strchr("tTyY", *s) != NULL)
E 124
I 124
	if (s == NULL || *s == '\0' || strchr("tTyY", *s) != NULL)
E 124
E 94
		return (TRUE);
	return (FALSE);
}
I 41
/*
**  ATOOCT -- convert a string representation to octal.
**
**	Parameters:
**		s -- string to convert.
**
**	Returns:
**		An integer representing the string interpreted as an
**		octal number.
**
**	Side Effects:
**		none.
*/

I 198
int
E 198
atooct(s)
	register char *s;
{
	register int i = 0;

	while (*s >= '0' && *s <= '7')
		i = (i << 3) | (*s++ - '0');
	return (i);
I 42
}
/*
**  WAITFOR -- wait for a particular process id.
**
**	Parameters:
**		pid -- process id to wait for.
**
**	Returns:
**		status of pid.
**		-1 if pid never shows up.
**
**	Side Effects:
**		none.
*/

I 131
int
E 131
waitfor(pid)
	int pid;
{
I 131
#ifdef WAITUNION
	union wait st;
#else
E 131
	auto int st;
I 131
#endif
E 131
	int i;

	do
	{
		errno = 0;
		i = wait(&st);
	} while ((i >= 0 || errno == EINTR) && i != pid);
	if (i < 0)
D 131
		st = -1;
	return (st);
E 131
I 131
		return -1;
#ifdef WAITUNION
	return st.w_status;
#else
	return st;
#endif
E 131
}
/*
D 55
**  CLOSEALL -- close all extraneous file descriptors
**
**	Parameters:
**		none.
**
**	Returns:
**		none.
**
**	Side Effects:
**		Closes all file descriptors except zero, one, and two.
*/

closeall()
{
	int i;

	for (i = 3; i < 50; i++)
		(void) close(i);
I 49
}
/*
E 55
**  BITINTERSECT -- tell if two bitmaps intersect
**
**	Parameters:
**		a, b -- the bitmaps in question
**
**	Returns:
**		TRUE if they have a non-null intersection
**		FALSE otherwise
**
**	Side Effects:
**		none.
*/

bool
bitintersect(a, b)
	BITMAP a;
	BITMAP b;
{
	int i;

	for (i = BITMAPBYTES / sizeof (int); --i >= 0; )
		if ((a[i] & b[i]) != 0)
			return (TRUE);
	return (FALSE);
}
/*
**  BITZEROP -- tell if a bitmap is all zero
**
**	Parameters:
**		map -- the bit map to check
**
**	Returns:
**		TRUE if map is all zero.
**		FALSE if there are any bits set in map.
**
**	Side Effects:
**		none.
*/

bool
bitzerop(map)
	BITMAP map;
{
	int i;

	for (i = BITMAPBYTES / sizeof (int); --i >= 0; )
		if (map[i] != 0)
			return (FALSE);
	return (TRUE);
I 105
}
/*
I 106
**  STRCONTAINEDIN -- tell if one string is contained in another
**
**	Parameters:
**		a -- possible substring.
**		b -- possible superstring.
**
**	Returns:
**		TRUE if a is contained in b.
**		FALSE otherwise.
*/

bool
strcontainedin(a, b)
	register char *a;
	register char *b;
{
D 140
	int l;
E 140
I 140
	int la;
	int lb;
	int c;
E 140

D 140
	l = strlen(a);
	for (;;)
E 140
I 140
	la = strlen(a);
	lb = strlen(b);
	c = *a;
	if (isascii(c) && isupper(c))
		c = tolower(c);
	for (; lb-- >= la; b++)
E 140
	{
D 140
		b = strchr(b, a[0]);
		if (b == NULL)
			return FALSE;
		if (strncmp(a, b, l) == 0)
E 140
I 140
		if (*b != c && isascii(*b) && isupper(*b) && tolower(*b) != c)
			continue;
		if (strncasecmp(a, b, la) == 0)
E 140
			return TRUE;
D 140
		b++;
E 140
	}
I 140
	return FALSE;
E 140
I 122
}
/*
**  CHECKFD012 -- check low numbered file descriptors
**
**	File descriptors 0, 1, and 2 should be open at all times.
**	This routine verifies that, and fixes it if not true.
**
**	Parameters:
**		where -- a tag printed if the assertion failed
**
**	Returns:
**		none
*/

I 198
void
E 198
checkfd012(where)
	char *where;
{
D 202
#ifdef XDEBUG
E 202
I 202
#if XDEBUG
E 202
	register int i;
	struct stat stbuf;

	for (i = 0; i < 3; i++)
	{
D 133
		if (fstat(i, &stbuf) < 0)
E 133
I 133
		if (fstat(i, &stbuf) < 0 && errno != EOPNOTSUPP)
E 133
		{
			/* oops.... */
			int fd;

			syserr("%s: fd %d not open", where, i);
			fd = open("/dev/null", i == 0 ? O_RDONLY : O_WRONLY, 0666);
			if (fd != i)
			{
				(void) dup2(fd, i);
				(void) close(fd);
			}
		}
	}
D 125
#endif XDEBUG
E 125
I 125
#endif /* XDEBUG */
E 125
E 122
}
I 132
/*
**  PRINTOPENFDS -- print the open file descriptors (for debugging)
**
**	Parameters:
**		logit -- if set, send output to syslog; otherwise
**			print for debugging.
**
**	Returns:
**		none.
*/

D 185
#include <netdb.h>
E 185
#include <arpa/inet.h>

I 198
void
E 198
printopenfds(logit)
	bool logit;
{
	register int fd;
D 134
	struct stat st;
E 134
I 134
	extern int DtableSize;

	for (fd = 0; fd < DtableSize; fd++)
		dumpfd(fd, FALSE, logit);
}
/*
**  DUMPFD -- dump a file descriptor
**
**	Parameters:
**		fd -- the file descriptor to dump.
**		printclosed -- if set, print a notification even if
**			it is closed; otherwise print nothing.
**		logit -- if set, send output to syslog instead of stdout.
*/

I 198
void
E 198
dumpfd(fd, printclosed, logit)
	int fd;
	bool printclosed;
	bool logit;
{
E 134
D 188
	register struct hostent *hp;
E 188
	register char *p;
I 188
	char *hp;
E 188
I 156
	char *fmtstr;
E 156
I 134
D 188
	struct sockaddr_in sin;
E 188
I 188
	SOCKADDR sa;
E 188
	auto int slen;
	struct stat st;
E 134
	char buf[200];
I 188
	extern char *hostnamebyanyaddr();
E 188
D 134
	extern int DtableSize;
E 134

D 134
	for (fd = 0; fd < DtableSize; fd++)
E 134
I 134
	p = buf;
	sprintf(p, "%3d: ", fd);
	p += strlen(p);

	if (fstat(fd, &st) < 0)
E 134
	{
D 134
		struct sockaddr_in sin;
		auto int slen;
E 134
I 134
		if (printclosed || errno != EBADF)
		{
			sprintf(p, "CANNOT STAT (%s)", errstring(errno));
			goto printit;
		}
		return;
	}
E 134

D 134
		if (fstat(fd, &st) < 0)
			continue;
E 134
I 134
	slen = fcntl(fd, F_GETFL, NULL);
	if (slen != -1)
	{
		sprintf(p, "fl=0x%x, ", slen);
		p += strlen(p);
	}
E 134

D 134
		p = buf;
		sprintf(p, "%3d: mode=%o: ", fd, st.st_mode);
E 134
I 134
	sprintf(p, "mode=%o: ", st.st_mode);
	p += strlen(p);
	switch (st.st_mode & S_IFMT)
	{
I 135
#ifdef S_IFSOCK
E 135
	  case S_IFSOCK:
		sprintf(p, "SOCK ");
E 134
		p += strlen(p);
D 134
		switch (st.st_mode & S_IFMT)
E 134
I 134
D 188
		slen = sizeof sin;
		if (getsockname(fd, (struct sockaddr *) &sin, &slen) < 0)
E 188
I 188
		slen = sizeof sa;
		if (getsockname(fd, &sa.sa, &slen) < 0)
E 188
D 189
			sprintf(p, "(badsock)");
E 189
I 189
			sprintf(p, "(%s)", errstring(errno));
E 189
		else
E 134
		{
D 134
		  case S_IFSOCK:
			sprintf(p, "SOCK ");
			p += strlen(p);
			slen = sizeof sin;
			if (getsockname(fd, (struct sockaddr *) &sin, &slen) < 0)
				sprintf(p, "(badsock)");
			else
			{
				hp = gethostbyaddr((char *) &sin.sin_addr, slen, AF_INET);
				sprintf(p, "%s/%d", hp == NULL ? inet_ntoa(sin.sin_addr)
							   : hp->h_name, ntohs(sin.sin_port));
			}
			p += strlen(p);
			sprintf(p, "->");
			p += strlen(p);
			slen = sizeof sin;
			if (getpeername(fd, (struct sockaddr *) &sin, &slen) < 0)
				sprintf(p, "(badsock)");
			else
			{
				hp = gethostbyaddr((char *) &sin.sin_addr, slen, AF_INET);
				sprintf(p, "%s/%d", hp == NULL ? inet_ntoa(sin.sin_addr)
							   : hp->h_name, ntohs(sin.sin_port));
			}
			break;
E 134
I 134
D 161
			hp = gethostbyaddr((char *) &sin.sin_addr, slen, AF_INET);
E 161
I 161
D 185
			hp = gethostbyaddr((char *) &sin.sin_addr,
E 185
I 185
D 188
			hp = sm_gethostbyaddr((char *) &sin.sin_addr,
E 185
D 162
					   IPADDRSIZE, AF_INET);
E 162
I 162
					   INADDRSZ, AF_INET);
E 162
E 161
			sprintf(p, "%s/%d", hp == NULL ? inet_ntoa(sin.sin_addr)
						   : hp->h_name, ntohs(sin.sin_port));
E 188
I 188
			hp = hostnamebyanyaddr(&sa);
			if (sa.sa.sa_family == AF_INET)
				sprintf(p, "%s/%d", hp, ntohs(sa.sin.sin_port));
			else
				sprintf(p, "%s", hp);
E 188
		}
		p += strlen(p);
		sprintf(p, "->");
		p += strlen(p);
D 188
		slen = sizeof sin;
		if (getpeername(fd, (struct sockaddr *) &sin, &slen) < 0)
E 188
I 188
		slen = sizeof sa;
		if (getpeername(fd, &sa.sa, &slen) < 0)
E 188
D 189
			sprintf(p, "(badsock)");
E 189
I 189
			sprintf(p, "(%s)", errstring(errno));
E 189
		else
		{
D 161
			hp = gethostbyaddr((char *) &sin.sin_addr, slen, AF_INET);
E 161
I 161
D 185
			hp = gethostbyaddr((char *) &sin.sin_addr,
E 185
I 185
D 188
			hp = sm_gethostbyaddr((char *) &sin.sin_addr,
E 185
D 162
					   IPADDRSIZE, AF_INET);
E 162
I 162
					   INADDRSZ, AF_INET);
E 162
E 161
			sprintf(p, "%s/%d", hp == NULL ? inet_ntoa(sin.sin_addr)
						   : hp->h_name, ntohs(sin.sin_port));
E 188
I 188
			hp = hostnamebyanyaddr(&sa);
			if (sa.sa.sa_family == AF_INET)
				sprintf(p, "%s/%d", hp, ntohs(sa.sin.sin_port));
			else
				sprintf(p, "%s", hp);
E 188
		}
		break;
I 135
#endif
E 135
E 134

D 134
		  case S_IFCHR:
			sprintf(p, "CHR: ");
			p += strlen(p);
			goto defprint;
E 134
I 134
	  case S_IFCHR:
		sprintf(p, "CHR: ");
		p += strlen(p);
		goto defprint;
E 134

D 134
		  case S_IFBLK:
			sprintf(p, "BLK: ");
			p += strlen(p);
			goto defprint;
E 134
I 134
	  case S_IFBLK:
		sprintf(p, "BLK: ");
		p += strlen(p);
		goto defprint;
E 134

I 149
D 154
#ifdef S_IFIFO
E 154
I 154
#if defined(S_IFIFO) && (!defined(S_IFSOCK) || S_IFIFO != S_IFSOCK)
E 154
	  case S_IFIFO:
		sprintf(p, "FIFO: ");
		p += strlen(p);
		goto defprint;
#endif

#ifdef S_IFDIR
	  case S_IFDIR:
		sprintf(p, "DIR: ");
		p += strlen(p);
		goto defprint;
#endif

#ifdef S_IFLNK
	  case S_IFLNK:
		sprintf(p, "LNK: ");
		p += strlen(p);
		goto defprint;
#endif

E 149
D 134
		  default:
E 134
I 134
	  default:
E 134
defprint:
D 134
			sprintf(p, "rdev=%d/%d, ino=%d, nlink=%d, u/gid=%d/%d, size=%ld",
				major(st.st_rdev), minor(st.st_rdev), st.st_ino,
				st.st_nlink, st.st_uid, st.st_gid, st.st_size);
			break;
		}

		if (logit)
			syslog(LOG_INFO, "%s", buf);
		else
			printf("%s\n", buf);
E 134
I 134
D 156
		sprintf(p, "dev=%d/%d, ino=%d, nlink=%d, u/gid=%d/%d, size=%ld",
E 156
I 156
D 160
		if (sizeof st.st_size > 4)
E 160
I 160
		if (sizeof st.st_size > sizeof (long))
E 160
D 158
			fmtstr = "dev=%d/%d, ino=%d, nlink=%d, u/gid=%d/%d, size=%qd",
E 158
I 158
			fmtstr = "dev=%d/%d, ino=%d, nlink=%d, u/gid=%d/%d, size=%qd";
E 158
		else
D 158
			fmtstr = "dev=%d/%d, ino=%d, nlink=%d, u/gid=%d/%d, size=%ld",
E 158
I 158
			fmtstr = "dev=%d/%d, ino=%d, nlink=%d, u/gid=%d/%d, size=%ld";
E 158
		sprintf(p, fmtstr,
E 156
			major(st.st_dev), minor(st.st_dev), st.st_ino,
			st.st_nlink, st.st_uid, st.st_gid, st.st_size);
		break;
E 134
	}
I 134

printit:
I 157
#ifdef LOG
E 157
	if (logit)
D 139
		syslog(LOG_INFO, "%s", buf);
E 139
I 139
		syslog(LOG_DEBUG, "%s", buf);
E 139
	else
I 157
#endif
E 157
		printf("%s\n", buf);
E 134
}
I 141
/*
**  SHORTENSTRING -- return short version of a string
**
**	If the string is already short, just return it.  If it is too
**	long, return the head and tail of the string.
**
**	Parameters:
**		s -- the string to shorten.
**		m -- the max length of the string.
**
**	Returns:
**		Either s or a short version of s.
*/

#ifndef MAXSHORTSTR
D 142
# define MAXSHORTSTR	83
E 142
I 142
# define MAXSHORTSTR	203
E 142
#endif

char *
shortenstring(s, m)
D 198
	register char *s;
E 198
I 198
	register const char *s;
E 198
	int m;
{
	int l;
	static char buf[MAXSHORTSTR + 1];

	l = strlen(s);
	if (l < m)
D 198
		return s;
E 198
I 198
		return (char *) s;
E 198
	if (m > MAXSHORTSTR)
		m = MAXSHORTSTR;
	else if (m < 10)
	{
		if (m < 5)
		{
			strncpy(buf, s, m);
			buf[m] = '\0';
			return buf;
		}
		strncpy(buf, s, m - 3);
		strcpy(buf + m - 3, "...");
		return buf;
	}
	m = (m - 3) / 2;
	strncpy(buf, s, m);
	strcpy(buf + m, "...");
	strcpy(buf + m + 3, s + l - m);
	return buf;
}
I 167
/*
I 192
**  SHORTEN_HOSTNAME -- strip local domain information off of hostname.
**
**	Parameters:
**		host -- the host to shorten (stripped in place).
**
**	Returns:
**		none.
*/

void
shorten_hostname(host)
	char host[];
{
	register char *p;
	char *mydom;
	int i;
I 199
	bool canon = FALSE;
E 199

	/* strip off final dot */
	p = &host[strlen(host) - 1];
	if (*p == '.')
I 199
	{
E 199
		*p = '\0';
I 199
		canon = TRUE;
	}
E 199

	/* see if there is any domain at all -- if not, we are done */
	p = strchr(host, '.');
	if (p == NULL)
		return;

	/* yes, we have a domain -- see if it looks like us */
	mydom = macvalue('m', CurEnv);
	if (mydom == NULL)
		mydom = "";
	i = strlen(++p);
D 199
	if (strncasecmp(p, mydom, i) == 0 &&
E 199
I 199
	if ((canon ? strcasecmp(p, mydom) : strncasecmp(p, mydom, i)) == 0 &&
E 199
	    (mydom[i] == '.' || mydom[i] == '\0'))
		*--p = '\0';
}
/*
I 193
**  PROG_OPEN -- open a program for reading
**
**	Parameters:
**		argv -- the argument list.
**		pfd -- pointer to a place to store the file descriptor.
**		e -- the current envelope.
**
**	Returns:
**		pid of the process -- -1 if it failed.
*/

int
prog_open(argv, pfd, e)
	char **argv;
	int *pfd;
	ENVELOPE *e;
{
	int pid;
	int i;
	int saveerrno;
D 194
	char **ep;
E 194
	int fdv[2];
	char *p, *q;
	char buf[MAXLINE + 1];
D 194
	char *env[MAXUSERENVIRON];
	extern char **environ;
E 194
	extern int DtableSize;

	if (pipe(fdv) < 0)
	{
		syserr("%s: cannot create pipe for stdout", argv[0]);
		return -1;
	}
	pid = fork();
	if (pid < 0)
	{
		syserr("%s: cannot fork", argv[0]);
		close(fdv[0]);
		close(fdv[1]);
		return -1;
	}
	if (pid > 0)
	{
		/* parent */
		close(fdv[1]);
		*pfd = fdv[0];
		return pid;
	}

	/* child -- close stdin */
	close(0);

	/* stdout goes back to parent */
	close(fdv[0]);
	if (dup2(fdv[1], 1) < 0)
	{
		syserr("%s: cannot dup2 for stdout", argv[0]);
		_exit(EX_OSERR);
	}
	close(fdv[1]);

	/* stderr goes to transcript if available */
	if (e->e_xfp != NULL)
	{
		if (dup2(fileno(e->e_xfp), 2) < 0)
		{
			syserr("%s: cannot dup2 for stderr", argv[0]);
			_exit(EX_OSERR);
		}
	}

	/* this process has no right to the queue file */
	if (e->e_lockfp != NULL)
		close(fileno(e->e_lockfp));

	/* run as default user */
I 204
	endpwent();
E 204
	setgid(DefGid);
	setuid(DefUid);

	/* run in some directory */
	if (ProgMailer != NULL)
		p = ProgMailer->m_execdir;
	else
		p = NULL;
	for (; p != NULL; p = q)
	{
		q = strchr(p, ':');
		if (q != NULL)
			*q = '\0';
		expand(p, buf, sizeof buf, e);
		if (q != NULL)
			*q++ = ':';
		if (buf[0] != '\0' && chdir(buf) >= 0)
			break;
	}
	if (p == NULL)
	{
		/* backup directories */
		if (chdir("/tmp") < 0)
			(void) chdir("/");
	}

	/* arrange for all the files to be closed */
	for (i = 3; i < DtableSize; i++)
	{
		register int j;

		if ((j = fcntl(i, F_GETFD, 0)) != -1)
			(void) fcntl(i, F_SETFD, j | 1);
	}

D 194
	/* set up the environment */
	i = 0;
	env[i++] = "AGENT=sendmail";
	for (ep = environ; *ep != NULL; ep++)
	{
		if (strncmp(*ep, "TZ=", 3) == 0 ||
		    strncmp(*ep, "ISP=", 4) == 0 ||
		    strncmp(*ep, "SYSTYPE=", 8) == 0)
			env[i++] = *ep;
	}
	env[i] = NULL;

E 194
	/* now exec the process */
D 194
	execve(argv[0], (ARGV_T) argv, (ARGV_T) env);
E 194
I 194
	execve(argv[0], (ARGV_T) argv, (ARGV_T) UserEnviron);
E 194

	/* woops!  failed */
	saveerrno = errno;
	syserr("%s: cannot exec", argv[0]);
	if (transienterror(saveerrno))
		_exit(EX_OSERR);
	_exit(EX_CONFIG);
}
/*
E 193
E 192
**  GET_COLUMN  -- look up a Column in a line buffer
**
**	Parameters:
**		line -- the raw text line to search.
**		col -- the column number to fetch.
**		delim -- the delimiter between columns.  If null,
**			use white space.
**		buf -- the output buffer.
**
**	Returns:
**		buf if successful.
**		NULL otherwise.
*/

char *
get_column(line, col, delim, buf)
	char line[];
	int col;
	char delim;
	char buf[];
{
	char *p;
	char *begin, *end;
	int i;
	char delimbuf[3];
	
	if (delim == '\0')
D 195
		strcpy(delimbuf, "\t ");
E 195
I 195
		strcpy(delimbuf, "\n\t ");
E 195
	else
	{
		delimbuf[0] = delim;
		delimbuf[1] = '\0';
	}

	p = line;
	if (*p == '\0')
		return NULL;			/* line empty */
	if (*p == delim && col == 0)
		return NULL;			/* first column empty */

	begin = line;

	if (col == 0 && delim == '\0')
	{
		while (*begin && isspace(*begin))
			begin++;
	}

	for (i = 0; i < col; i++)
	{
		if ((begin = strpbrk(begin, delimbuf)) == NULL)
			return NULL;		/* no such column */
		begin++;
		if (delim == '\0')
		{
			while (*begin && isspace(*begin))
				begin++;
		}
	}
	
	end = strpbrk(begin, delimbuf);
	if (end == NULL)
	{
		strcpy(buf, begin);
	}
	else
	{
		strncpy(buf, begin, end - begin);
		buf[end - begin] = '\0';
	}
	return buf;
}
I 168
/*
**  CLEANSTRCPY -- copy string keeping out bogus characters
**
**	Parameters:
**		t -- "to" string.
**		f -- "from" string.
**		l -- length of space available in "to" string.
**
**	Returns:
**		none.
*/

void
cleanstrcpy(t, f, l)
	register char *t;
	register char *f;
	int l;
{
I 170
#ifdef LOG
	/* check for newlines and log if necessary */
D 175
	(void) denlstring(f);
E 175
I 175
D 179
	(void) denlstring(f, TRUE);
E 179
I 179
	(void) denlstring(f, TRUE, TRUE);
E 179
E 175
#endif

E 170
	l--;
	while (l > 0 && *f != '\0')
	{
		if (isascii(*f) &&
		    (isalnum(*f) || strchr("!#$%&'*+-./^_`{|}~", *f) != NULL))
		{
			l--;
			*t++ = *f;
		}
		f++;
	}
	*t = '\0';
}
/*
**  DENLSTRING -- convert newlines in a string to spaces
**
**	Parameters:
**		s -- the input string
I 179
**		strict -- if set, don't permit continuation lines.
E 179
I 175
**		logattacks -- if set, log attempted attacks.
E 175
**
**	Returns:
**		A pointer to a version of the string with newlines
**		mapped to spaces.  This should be copied.
*/

char *
D 175
denlstring(s)
E 175
I 175
D 179
denlstring(s, logattacks)
E 179
I 179
denlstring(s, strict, logattacks)
E 179
E 175
	char *s;
I 179
D 186
	int strict;
E 179
I 175
D 177
	bool logattacks;
E 177
I 177
	int logattacks;
E 186
I 186
	bool strict;
	bool logattacks;
E 186
E 177
E 175
{
	register char *p;
	int l;
	static char *bp = NULL;
	static int bl = 0;

D 179
	if (strchr(s, '\n') == NULL)
E 179
I 179
	p = s;
	while ((p = strchr(p, '\n')) != NULL)
		if (strict || (*++p != ' ' && *p != '\t'))
			break;
	if (p == NULL)
E 179
		return s;

	l = strlen(s) + 1;
	if (bl < l)
	{
		/* allocate more space */
		if (bp != NULL)
			free(bp);
		bp = xalloc(l);
		bl = l;
	}
	strcpy(bp, s);
	for (p = bp; (p = strchr(p, '\n')) != NULL; )
		*p++ = ' ';
I 170

I 174
/*
E 174
#ifdef LOG
D 175
	p = macvalue('_', CurEnv);
	syslog(LOG_ALERT, "POSSIBLE ATTACK from %s: newline in string \"%s\"",
		p == NULL ? "[UNKNOWN]" : p, bp);
E 175
I 175
	if (logattacks)
	{
		syslog(LOG_NOTICE, "POSSIBLE ATTACK from %s: newline in string \"%s\"",
			RealHostName == NULL ? "[UNKNOWN]" : RealHostName,
			shortenstring(bp, 80));
	}
E 175
#endif
I 174
*/
E 174

E 170
	return bp;
}
E 168
E 167
E 141
E 132
D 108
/*
E 106
**  TRANSIENTERROR -- tell if an error code indicates a transient failure
**
**	This looks at an errno value and tells if this is likely to
**	go away if retried later.
**
**	Parameters:
**		err -- the errno code to classify.
**
**	Returns:
**		TRUE if this is probably transient.
**		FALSE otherwise.
*/

bool
transienterror(err)
	int err;
{
	switch (err)
	{
	  case EIO:			/* I/O error */
	  case ENXIO:			/* Device not configured */
	  case EAGAIN:			/* Resource temporarily unavailable */
	  case ENOMEM:			/* Cannot allocate memory */
	  case ENODEV:			/* Operation not supported by device */
	  case ENFILE:			/* Too many open files in system */
	  case EMFILE:			/* Too many open files */
	  case ENOSPC:			/* No space left on device */
#ifdef ETIMEDOUT
	  case ETIMEDOUT:		/* Connection timed out */
#endif
#ifdef ESTALE
	  case ESTALE:			/* Stale NFS file handle */
#endif
#ifdef ENETDOWN
	  case ENETDOWN:		/* Network is down */
#endif
#ifdef ENETUNREACH
	  case ENETUNREACH:		/* Network is unreachable */
#endif
#ifdef ENETRESET
	  case ENETRESET:		/* Network dropped connection on reset */
#endif
#ifdef ECONNABORTED
	  case ECONNABORTED:		/* Software caused connection abort */
#endif
#ifdef ECONNRESET
	  case ECONNRESET:		/* Connection reset by peer */
#endif
#ifdef ENOBUFS
	  case ENOBUFS:			/* No buffer space available */
#endif
#ifdef ESHUTDOWN
	  case ESHUTDOWN:		/* Can't send after socket shutdown */
#endif
#ifdef ECONNREFUSED
	  case ECONNREFUSED:		/* Connection refused */
#endif
#ifdef EHOSTDOWN
	  case EHOSTDOWN:		/* Host is down */
#endif
#ifdef EHOSTUNREACH
	  case EHOSTUNREACH:		/* No route to host */
#endif
#ifdef EDQUOT
	  case EDQUOT:			/* Disc quota exceeded */
#endif
#ifdef EPROCLIM
	  case EPROCLIM:		/* Too many processes */
#endif
#ifdef EUSERS
	  case EUSERS:			/* Too many users */
#endif
#ifdef EDEADLK
	  case EDEADLK:			/* Resource deadlock avoided */
#endif
		return TRUE;
	}

	/* nope, must be permanent */
	return FALSE;
E 105
E 49
E 42
}
E 108
E 41
E 39
E 35
E 33
E 31
E 29
E 28
I 26
D 27
/*
**  TICK -- take a clock tick
**
**	Someday this will have to do more complex event scheduling.
**
**	Parameters:
**		none.
**
**	Returns:
**		non-local through TickFrame.
**
**	Side Effects:
**		none.
*/

tick()
{
# ifdef DEBUG
	if (Debug > 0)
		printf("tick\n");
# endif DEBUG
	longjmp(TickFrame, 1);
}
E 27
E 26
E 24
E 22
E 11
E 10
D 7
/*
**  ANY -- Return TRUE if the character exists in the string.
**
**	Parameters:
**		c -- the character.
**		s -- the string
**			(sounds like an avant garde script)
**
**	Returns:
**		TRUE -- if c could be found in s.
**		FALSE -- otherwise.
**
**	Side Effects:
**		none.
**
D 3
**	Requires:
**		none.
**
E 3
**	Called By:
**		prescan
D 3
**
**	History:
**		3/5/80 -- written.
E 3
*/

any(c, s)
	register char c;
	register char *s;
{
	register char c2;

	while ((c2 = *s++) != '\0')
		if (c2 == c)
			return (TRUE);
	return (FALSE);
}
E 7
E 1
