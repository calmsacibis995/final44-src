h19925
s 00009/00011/01265
d D 8.97 95/06/20 10:42:14 eric 247 246
c more hacks to make /usr/tmp/dead.letter work right
e
s 00002/00001/01274
d D 8.96 95/06/15 19:06:41 eric 246 245
c don't alias \-quoted addresses
e
s 00001/00001/01274
d D 8.95 95/06/15 14:04:26 eric 245 244
c avoid bogus "aliasing/forwarding loop broken" messages
e
s 00002/00003/01273
d D 8.94 95/06/15 08:41:42 eric 244 243
c allow trusted users to have untrusted shells
e
s 00001/00001/01275
d D 8.93 95/06/13 09:22:43 eric 243 242
c make a bunch of #defines into 0/1 instead of ifdef/ifndef
e
s 00000/00002/01276
d D 8.92 95/05/30 19:23:56 eric 242 241
c change RealUserName from an array to a pointer; move defn to sendmail.h
e
s 00003/00002/01275
d D 8.91 95/05/28 11:49:12 eric 241 240
c lint
e
s 00002/00002/01275
d D 8.90 95/05/27 07:45:32 eric 240 239
c allow #@#\0 as a comment; make USERDB be a 0/1 option
e
s 00014/00002/01263
d D 8.89 95/05/23 16:44:29 eric 239 238
c allow use of seteuid() on systems that have new Posix semantics
e
s 00004/00001/01261
d D 8.88 95/05/23 10:20:27 eric 238 237
c avoid bogus "alias loop" messages
e
s 00006/00001/01256
d D 8.87 95/05/23 10:09:33 eric 237 236
c don't do .forward lookups at RCPT time -- can have large timeouts
c if NFS server is hung
e
s 00002/00002/01255
d D 8.86 95/05/19 17:55:13 eric 236 235
c tweak comments to match Andrew's original intent
e
s 00017/00002/01240
d D 8.85 95/05/19 15:59:29 eric 235 234
c fix simple self-references; more debugging
e
s 00105/00001/01137
d D 8.84 95/05/18 12:59:31 eric 234 233
c fix self-reference algorithm to use more intelligent choices
e
s 00001/00001/01137
d D 8.83 95/05/09 10:48:00 eric 233 232
c allow root .forward to work even if ~root not searchable or
c ~root/.forward is not readable by non-roots
e
s 00013/00003/01125
d D 8.82 95/04/23 14:02:24 eric 232 231
c updates for new DSN drafts
e
s 00001/00001/01127
d D 8.81 95/04/22 14:55:42 eric 231 230
c woops -- compile glitch
e
s 00012/00000/01116
d D 8.80 95/04/22 14:50:47 eric 230 229
c better use of extended DSN status codes
e
s 00001/00001/01115
d D 8.79 95/04/21 09:56:48 eric 229 228
c update copyright notice
e
s 00002/00005/01114
d D 8.78 95/04/13 17:36:07 eric 228 227
c fix postmaster notifications -- it was getting the body in
c some inappropriate cases, and sometimes no message at all; clean up
c dead.letter processing
e
s 00016/00000/01103
d D 8.77 95/04/12 08:20:13 eric 227 226
c allow <SP>#@#<SP> as an in-line comment introducer in :include: files
e
s 00002/00005/01101
d D 8.76 95/03/31 10:51:44 eric 226 225
c pull getpwXXX and gethostbyXXX calls out into conf.c so they can
c be tweaked
e
s 00058/00011/01048
d D 8.75 95/03/27 09:25:20 eric 225 224
c more cleanup for DSN drafts
e
s 00001/00001/01058
d D 8.74 95/03/25 07:39:27 eric 224 223
c don't pass through NOTIFY= unless it was given in the SMTP RCPT
e
s 00001/00001/01058
d D 8.73 95/03/21 09:26:34 eric 223 222
c new DSN draft
e
s 00004/00004/01055
d D 8.72 95/03/14 08:18:50 eric 222 221
c be more precise on MAXNAME checking
e
s 00004/00001/01055
d D 8.71 95/03/10 12:21:48 eric 221 220
c improved security when opening files
e
s 00006/00053/01050
d D 8.70 95/03/06 15:11:43 eric 220 219
c fix some race conditions for file opens
e
s 00000/00000/01103
d D 8.69 95/03/05 11:57:06 eric 219 217
i 218
c add "strict" parameter to denlstring to allow continuations
e
s 00001/00001/01045
d D 8.44.1.6 95/03/05 10:09:51 eric 218 216
c add concept of "strict adherence" to newline standard
e
s 00000/00000/01103
d D 8.68 95/02/28 14:43:08 eric 217 215
i 216
c incorporate fixes from 8.6.11
e
s 00001/00001/01045
d D 8.44.1.5 95/02/28 10:58:42 eric 216 212
c multiple glitches in 8.6.10 -- see ../RELEASE_NOTES for details
e
s 00003/00003/01100
d D 8.67 95/02/23 15:51:14 eric 215 214
c cleanup to make gcc -Winitialized happier
e
s 00000/00001/01103
d D 8.66 95/02/21 07:40:29 eric 214 213
c woops -- botched the last patch
e
s 00001/00003/01103
d D 8.65 95/02/20 17:32:35 eric 213 211
i 212
c fix sendtolist() buffer copying -- confusion of global v. local
e
s 00011/00016/01035
d D 8.44.1.4 95/02/20 17:31:36 eric 212 210
c fix sendtolist() buffer copying -- confusion of global v. local
e
s 00001/00001/01108
d D 8.64 95/02/14 06:11:29 eric 211 209
c fix bug -- should have been testing bufp == NULL instead of buf == NULL
e
s 00001/00001/01050
d D 8.44.1.3 95/02/14 06:10:33 eric 210 207
c fix error -- should hvae been testing bufp instead of buf
e
s 00013/00014/01096
d D 8.63 95/02/11 06:56:57 eric 209 208
c become the default uid when including files with HASSETREUID
e
s 00002/00000/01108
d D 8.62 95/02/11 06:43:32 eric 208 205
c avoid checking path directory modes if setreuid succeeded (for
c efficiency)
e
s 00000/00000/01051
d D 8.44.1.2 95/02/10 07:47:26 eric 207 206
i 196
c avoid conflicting buffer usage
e
s 00001/00003/01032
d D 8.44.1.1 95/02/10 07:37:38 eric 206 188
i 205
c fix security problem allowing bogus lines to be written to qf file
c from command line or IDENT protocol by embedding newlines
e
s 00002/00001/01106
d D 8.61 95/02/10 07:16:33 eric 205 204
c fix security problem: avoid newlines in command line or IDENT input
e
s 00001/00001/01106
d D 8.60 95/01/04 16:33:29 eric 204 203
c avoid error message on self-referencing alias
e
s 00004/00002/01103
d D 8.59 94/12/10 07:46:44 eric 203 202
c log transaction delay as well as queue delay (for ordering lists)
e
s 00003/00001/01102
d D 8.58 94/11/25 09:05:52 eric 202 201
c improve DSN handling somewhat + some bug fixes
e
s 00003/00000/01100
d D 8.57 94/11/23 15:21:05 eric 201 200
c get ORCPT= ESMTP DSN parameter working
e
s 00020/00014/01080
d D 8.56 94/11/22 22:24:46 eric 200 199
c clean up several small problems with file delivery, error detection,
c and return receipts
e
s 00016/00014/01078
d D 8.55 94/11/22 16:59:16 eric 199 198
c fix propogation of notification flags to alias values
e
s 00001/00001/01091
d D 8.54 94/11/21 21:07:26 eric 198 197
c convert to new DSN draft
e
s 00025/00011/01067
d D 8.53 94/11/20 13:50:17 eric 197 196
c allow files referenced in aliases to write files as the default uid
e
s 00019/00001/01059
d D 8.52 94/11/08 10:06:29 eric 196 195
c copy buffer in senttolist() to avoid conflict with maps
e
s 00015/00004/01045
d D 8.51 94/11/04 08:40:16 eric 195 194
c first cut at DSN implementation
e
s 00002/00000/01047
d D 8.50 94/10/20 14:17:00 eric 194 193
c don't object to all numeric user names unless HESIOD is defined; this
c is legal under Posix (bletch!)
e
s 00011/00002/01036
d D 8.49 94/10/17 10:56:49 eric 193 192
c improved diagnostics in setreuid code
e
s 00000/00003/01038
d D 8.48 94/08/21 15:25:41 eric 192 191
c multiple queue timeouts
e
s 00006/00002/01035
d D 8.47 94/08/20 07:01:22 eric 191 190
c Generalize ReadTimeout option and call it Timeouts; create
c queuereturn, queuewarn, and fileopen timeouts
e
s 00009/00016/01028
d D 8.46 94/07/03 11:47:49 eric 190 189
c break out special local mail processing (e.g., mapping to the
c "prog" mailer) onto separate mailer flags
e
s 00013/00002/01031
d D 8.45 94/05/29 07:56:09 eric 189 188
c avoid buffer overrun problems with very long user names
e
s 00006/00003/01027
d D 8.44 94/02/28 10:04:52 eric 188 187
c avoid null pointer dereferences to e->e_id when logging
e
s 00001/00001/01029
d D 8.43 94/02/22 14:55:09 eric 187 186
c fix typo in syslog call
e
s 00019/00008/01011
d D 8.42 94/01/31 16:59:50 eric 186 185
c cleanup of _POSIX_CHOWN_RESTRICTED stuff
e
s 00037/00002/00982
d D 8.41 94/01/26 17:35:56 eric 185 184
c fix security problem with systems that can give away files
e
s 00004/00001/00980
d D 8.40 94/01/22 09:00:59 eric 184 183
c Apollo/POSIX changes -- leading pathname of // can legally have
c different semantics; ensure that this never happens when building pathnames
e
s 00008/00006/00973
d D 8.39 94/01/10 08:57:22 eric 183 182
c avoid QuickAbort problems while uid is reset; repair duplicate
c suppression algorithm
e
s 00001/00001/00978
d D 8.38 94/01/08 17:28:13 eric 182 181
c fix improper diagnosis of "aliasing/forwarding loop broken"
e
s 00004/00002/00975
d D 8.37 94/01/06 10:13:11 eric 181 180
c if an address is a self-reference, inherit the new q_flags
e
s 00084/00025/00893
d D 8.36 94/01/05 09:22:39 eric 180 179
c improvements to local program access lockouts
e
s 00009/00007/00909
d D 8.35 93/12/30 05:55:01 eric 179 178
c security: fix a problem that allowed root to get into any directory
c instead of being treated as the "nobody" user
e
s 00001/00000/00915
d D 8.34 93/12/26 09:00:36 eric 178 177
c avoid "broken alias loop" messages when a :include: times out
e
s 00003/00010/00912
d D 8.33 93/12/26 06:07:50 eric 177 176
c clean up implementation if you don't have getusershell(3) in libc
e
s 00000/00002/00922
d D 8.32 93/12/24 07:57:01 eric 176 175
c go ahead and actually implement getusershell in compat mode; too many
c systems don't have it
e
s 00014/00000/00910
d D 8.31 93/12/24 06:29:23 eric 175 174
c fixes to restrict users who don't have a "regular" login shell (i.e.,
c not listed in /etc/shells) from forwarding to a program or file; they can
c write their .forward file from another machine and then get in.
e
s 00013/00009/00897
d D 8.30 93/12/14 14:07:15 eric 174 173
c add hooks to permit writes to setuid files (with no X bits)
c on the SUID_ROOT_FILES_OK compile flag.  Is this a good idea?
e
s 00022/00010/00884
d D 8.29 93/12/13 07:35:41 eric 173 172
c patches to fix checks when sending to a file
e
s 00008/00007/00886
d D 8.28 93/12/10 17:30:16 eric 172 171
c improve error messages -- avoid "Error 0" syndrome
e
s 00011/00008/00882
d D 8.27 93/12/10 16:40:09 eric 171 170
c cleanup of symbolic link checking -- make it less picky
e
s 00005/00000/00885
d D 8.26 93/12/04 08:06:49 eric 170 169
c fix bug in writable (directory writable wasn't enough); extra
c debug info
e
s 00001/00001/00884
d D 8.25 93/12/02 08:15:19 eric 169 168
c fix bug in new writable implementation -- can't return safefile directly
e
s 00053/00024/00832
d D 8.24 93/11/25 11:33:01 eric 168 167
c security patches to seal up symbolic link attacks
e
s 00003/00003/00853
d D 8.23 93/11/14 08:27:34 eric 167 166
c look at DefUid instead of zero if no ctladdr
e
s 00009/00003/00847
d D 8.22 93/11/08 09:46:34 eric 166 165
c additional debugging statements
e
s 00002/00002/00848
d D 8.21 93/10/29 19:24:38 eric 165 164
c improved logging (log ctladdr on recipients
e
s 00003/00004/00847
d D 8.20 93/10/27 08:36:35 eric 164 163
c security fix: avoid accepting inappropriate program/file mailers
e
s 00011/00000/00840
d D 8.19 93/09/29 10:55:14 eric 163 162
c reject all-numeric login names
e
s 00028/00027/00812
d D 8.18 93/09/22 18:02:54 eric 162 161
c fix bug that can cause recursive .forward files to fail
e
s 00010/00013/00829
d D 8.17 93/08/21 21:50:09 eric 161 160
c remember to always reset uid
e
s 00045/00010/00797
d D 8.16 93/08/21 16:36:12 eric 160 159
c move uid setting from forward() to include() so as to be more
c inclusive; this also adds proper group setting (previously it just set
c the user id)
e
s 00002/00002/00805
d D 8.15 93/08/17 09:51:48 eric 159 158
c put in beginnings of mod time checks on maps; generalize flags
c parameter to parseaddr/allocaddr to use RF_ hooks; relax HELO rules
c for Authentication-Warning:s
e
s 00009/00000/00798
d D 8.14 93/08/08 10:57:26 eric 158 157
c hooks to set $u to original recipient for "for" clause in Received: line
e
s 00006/00000/00792
d D 8.13 93/08/07 06:44:55 eric 157 156
c diagnose null list passed to sendtolist
e
s 00013/00002/00779
d D 8.12 93/07/28 15:08:23 eric 156 155
c accept group permissions for :include: and .forward processing
e
s 00003/00001/00778
d D 8.11 93/07/22 11:27:50 eric 155 154
c fix bogus error message with open timeout in :include: -- this also
c fixes a bug that caused resolver errnos to conflict with real errnos
e
s 00009/00003/00770
d D 8.10 93/07/21 18:20:33 eric 154 153
c don't improperly diagnose alias/forward loops (although this misses
c some)
e
s 00001/00001/00772
d D 8.9 93/07/20 19:24:38 eric 153 152
c RISCOS and SGI fixes; fix error handling (caused error messages to
c be discarded in some circumstances)
e
s 00002/00002/00771
d D 8.8 93/07/19 21:03:54 eric 152 151
c fix duplicate diagnosis of aliasing/forwarding loop broken
e
s 00001/00001/00772
d D 8.7 93/07/19 20:50:07 eric 151 150
c SGI IRIX & ANSI C portability
e
s 00007/00000/00766
d D 8.6 93/07/19 11:30:33 eric 150 149
c HASSETEUID => HASSETREUID and changes to avoid having to do
c setuid(getuid()) in main.
e
s 00003/00003/00763
d D 8.5 93/07/17 17:06:32 eric 149 148
c clean up semantics: QDONTSEND says don't ever send, and diables QQUEUEUP
c (previously, it meant don't send in this run)
e
s 00023/00007/00743
d D 8.4 93/07/17 13:46:51 eric 148 147
c detect self-destructing alias loop more generally for better diagnostics
e
s 00003/00003/00747
d D 8.3 93/07/13 12:58:16 eric 147 146
c many fixes.  primarily fix for seteuid problem in 8.2; also,
c Solaris compatibility fixes; timed out messages problems; messages
c silently discarded if checkcompat returned EX_TEMPFAIL
e
s 00002/00002/00748
d D 8.2 93/07/11 06:52:22 eric 146 145
c huge number of changes for 8.2, including IRIX & Solaris portability;
c improved error checking; fix -m flag and add -O flag in maps; fix long
c DNS timeouts; relax safefile restrictions; add -X command line flag; etc.
e
s 00002/00002/00748
d D 8.1 93/06/27 18:26:20 bostic 145 144
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00017/00004/00733
d D 6.42 93/06/24 07:29:36 eric 144 142
c fix serious security bug allowing any user to read any file on
c the system regardless of permissions or ownership; fix problem causing
c subroutines returning $# triples to continue to evaluate (causes loops)
e
s 00002/00002/00735
d R 8.1 93/06/07 10:31:50 bostic 143 142
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00003/00737
d D 6.41 93/05/27 11:37:06 eric 142 141
c prototype functions
e
s 00003/00003/00737
d D 6.40 93/05/01 15:18:14 eric 141 140
c don't use %e for syslog errors -- either %m or errstring
e
s 00005/00003/00735
d D 6.39 93/05/01 12:26:32 eric 140 139
c minor tweaking of syslog levels & compile fixes for SunOS & Ultrix
e
s 00018/00013/00720
d D 6.38 93/04/30 07:11:09 eric 139 138
c give reasonable error message on transienterror() of include
c or forward file
e
s 00000/00001/00733
d D 6.37 93/04/27 18:51:29 eric 138 137
c move #include <sys/stat.h> into conf.h
e
s 00001/00000/00733
d D 6.36 93/04/14 13:15:12 eric 137 136
c set q_ruser when you send to a true human user
e
s 00004/00001/00729
d D 6.35 93/04/09 14:24:20 eric 136 135
c clean up some debug messages if MATCHGECOS not compiled in
e
s 00001/00001/00729
d D 6.34 93/04/01 13:32:03 eric 135 134
c don't do extra userdb lookups in VRFYONLY mode
e
s 00001/00000/00729
d D 6.33 93/03/30 15:49:56 eric 134 132
c hooks for eventual better handling of SMTP recipients
e
s 00011/00002/00727
d D 6.32.1.1 93/03/30 13:28:41 eric 133 132
c attempt at quick RCPT response
e
s 00001/00000/00728
d D 6.32 93/03/30 12:00:59 eric 132 131
c mark include() address as verified for possible later expansion
e
s 00000/00006/00728
d D 6.31 93/03/19 12:20:03 eric 131 130
c don't force local names to lower case -- this was left over from
c the bogus alias mapping
e
s 00005/00004/00729
d D 6.30 93/03/19 11:46:30 eric 130 129
c include a warning timeout after some interval; get rid of QueueRun
c global and put it in the envelope; some other minor bug fixes
e
s 00010/00001/00723
d D 6.29 93/03/17 10:35:15 eric 129 128
c attempts to handle ENFILE conditions better
e
s 00000/00001/00724
d D 6.28 93/03/17 09:55:11 eric 128 127
c clean up file locking (create a lockfile() routine in conf.c)
e
s 00009/00009/00716
d D 6.27 93/03/16 09:16:06 eric 127 126
c delete e_sender and e_returnpath; fix some bugs in envelope splitting
e
s 00000/00015/00725
d D 6.26 93/03/14 08:30:10 eric 126 125
c delete handling for word "at" on command line
e
s 00000/00004/00740
d D 6.25 93/03/14 07:36:30 eric 125 124
c change (simplify) user and host UPPER => lower case mapping
e
s 00001/00001/00743
d D 6.24 93/03/06 10:52:56 eric 124 123
c don't automatically print errno in usrerr -- it can be too misleading
e
s 00004/00003/00740
d D 6.23 93/03/02 09:06:55 eric 123 122
c set QDONTSEND together with QBADADDR
e
s 00002/00002/00741
d D 6.22 93/03/01 13:15:27 eric 122 121
c yet more logging
e
s 00003/00003/00740
d D 6.21 93/03/01 12:43:43 eric 121 120
c changes for ESMTP; mostly better delimiter character pointer passing
e
s 00001/00002/00742
d D 6.20 93/03/01 06:53:28 eric 120 119
c header file cleanup; primarily #include <unistd.h> in sendmail.h
c and delete duplicate cruft
e
s 00001/00001/00743
d D 6.19 93/02/27 11:58:04 eric 119 118
c fix problem that caused looping in .forward files on queue runs only
e
s 00017/00009/00727
d D 6.18 93/02/26 08:19:40 eric 118 117
c better handling of transient errors
e
s 00002/00002/00734
d D 6.17 93/02/23 09:19:03 eric 117 116
c fix botch in SMTP VRFY code (assumed all users were local)
e
s 00012/00012/00724
d D 6.16 93/02/23 06:31:32 eric 116 115
c overhaul status of SMTP reply codes
e
s 00000/00034/00736
d D 6.15 93/02/22 16:59:03 eric 115 114
c delete -R flag (RcptLogFile handling)
e
s 00007/00000/00763
d D 6.14 93/02/20 14:49:00 eric 114 113
c make VRFY just verify; EXPN does full expansion
e
s 00011/00004/00752
d D 6.13 93/02/20 13:46:27 eric 113 112
c close cached MCI connections after a fork; add p (privacy) and b
c (min blocks free) options; fix selfref code; clean up $#error format
e
s 00013/00013/00743
d D 6.12 93/02/19 10:37:12 eric 112 111
c make duplicate deletion more global
e
s 00009/00004/00747
d D 6.11 93/02/19 09:21:24 eric 111 110
c fix a variety of bugs found by Eric Wassenaar <e07@nikhef.nl>
e
s 00001/00001/00750
d D 6.10 93/02/18 20:22:11 eric 110 109
c move the meta-characters from C0 into C1 space
e
s 00002/00002/00749
d D 6.9 93/02/16 18:29:41 eric 109 108
c clean up log levels; allow IDA-style split header/envelope rewriting;
c extend arpatounix with more zones (but is this even needed?)
e
s 00003/00003/00748
d D 6.8 93/02/15 12:00:24 eric 108 107
c improve some error messages; fix quoted :include:s; check for some
c other buffer overflows; log SMTP protocol errors
e
s 00006/00000/00745
d D 6.7 93/02/14 14:41:28 eric 107 106
c HPUX and OSF/1 support; fix SMTP reply codes & multiple SMTP error
c problem; consider cache timeout non-permanent; be more graceful on OS
c failures; log forward, alias, and userdb expansions on log level 10
e
s 00001/00002/00744
d D 6.6 93/01/28 17:04:46 eric 106 105
c fix the System 5 compatilibility to be compatible with the rest
c of the world.
e
s 00001/00000/00745
d D 6.5 93/01/28 10:15:39 eric 105 104
c System 5 compatibility, misc fixes
e
s 00012/00006/00733
d D 6.4 93/01/26 11:36:25 eric 104 103
c some (iffy) changes to prevent suppressing the actual sender
c during a queue run (interaction with C line in qf file)
e
s 00008/00005/00731
d D 6.3 93/01/21 15:18:28 eric 103 102
c more environment problems; limit resource exhaustion; fix incorrect
c name in Connection timed out message; ANSI C fixes; log message sender on
c returned mail during queue run; count recipients properly; fix YP code;
c diagnose "message timed out" properly
e
s 00049/00060/00687
d D 6.2 93/01/02 13:59:53 eric 102 101
c changes to recognize special mailer types (e.g., file) early
e
s 00000/00000/00747
d D 6.1 92/12/21 16:08:09 eric 101 100
c Release 6
e
s 00006/00001/00741
d D 5.40 92/12/17 09:09:33 eric 100 99
c fix bug in including (and forwarding) files; all lines looked
c like comments
e
s 00002/00000/00740
d D 5.39 92/12/15 17:17:25 eric 99 98
c restore # as comment symbol in .forward/:include:; extend -p flag;
c remove = option (use V instead)
e
s 00009/00005/00731
d D 5.38 92/12/15 13:24:01 eric 98 97
c J option sets "search path" for .forward
e
s 00005/00005/00731
d D 5.37 92/11/14 11:34:04 eric 97 96
c (partially) ANSI-fy it
e
s 00000/00002/00736
d D 5.36 92/11/13 16:04:18 eric 96 95
c *really* fix quoting in phrase part of addresses; eliminate #-style
c commenting in :include: and .forward files (parenthesized comments
c can be used instead)
e
s 00002/00001/00736
d D 5.35 92/07/19 14:26:02 eric 95 94
c finish uid_t/gid_t conversion; allow locally customized message for
c prepending to all error returns
e
s 00028/00003/00709
d D 5.34 92/07/18 18:33:48 eric 94 93
c fix confusion regarding quoting with fuzzy local name matching resulting
c from 8-bit clean conversion
e
s 00029/00025/00683
d D 5.33 92/07/12 14:09:29 eric 93 92
c reduce number of instances of CurEnv by passing it as a parameter
e
s 00001/00001/00707
d D 5.32 92/07/12 11:57:26 eric 92 91
c child pid not getting changed; \quoted names were still forwarded
e
s 00001/00001/00707
d D 5.31 92/07/12 10:14:05 eric 91 90
c make eight-bit clean; backslashes are carried through as-is
e
s 00002/00002/00706
d D 5.30 92/07/12 07:26:49 eric 90 89
c many fixes to controlling user code; fix Neil Rickert's hack using
c CNAME for someone else's host
e
s 00000/00001/00708
d D 5.29 92/07/12 07:01:29 eric 89 88
c clean up controlling user implementation; all those global variables
c weren't needed
e
s 00018/00000/00691
d D 5.28 92/05/29 10:38:29 eric 88 87
c allow configuration of GECOS matching; do regular aliasing after
c a GECOS match
e
s 00043/00006/00648
d D 5.27 92/03/20 22:32:57 eric 87 86
c reject connections more quickly if load average goes up;
c try to time out on opens of .forward files on hung filesystems
e
s 00002/00000/00652
d D 5.26 91/12/20 20:10:39 eric 86 85
c set close-on-exec flag for recipient log file
e
s 00033/00000/00619
d D 5.25 91/12/20 20:01:18 eric 85 84
c add -R flag to log incoming raw recipients for analysis
e
s 00018/00002/00601
d D 5.24 91/12/14 14:35:30 eric 84 83
c allow udbexpand to return temporary failure errors
e
s 00001/00001/00602
d D 5.23 91/11/20 18:23:32 eric 83 82
c from costales@icsi.Berkeley.EDU: print rulesets with symbolic name
c instead of control characters; allow # comments in :include: files
e
s 00001/00001/00602
d D 5.22 91/10/11 12:45:59 eric 82 81
c fixes for user database and new config files
e
s 00068/00042/00535
d D 5.21 91/10/05 10:09:06 eric 81 80
c allow catching of local names after aliasing but before local name
c resolution; have name server return indication that it matched.
e
s 00009/00000/00568
d D 5.20 91/07/26 09:34:15 eric 80 79
c hooks for distributed user database system
e
s 00002/00001/00566
d D 5.19 91/03/02 17:15:31 bostic 79 78
c ANSI
e
s 00001/00011/00566
d D 5.18 90/06/01 19:03:25 bostic 78 77
c new copyright notice
e
s 00001/00000/00576
d D 5.17 90/04/18 13:53:46 bostic 77 76
c sendmail security problems; bug report 4.3BSD/usr.lib/153
c sendmail security problems; bug report 4.3BSD/usr.lib/133
c sendmail security problems; bug report 4.3BSD/usr.lib/136
e
s 00001/00000/00575
d D 5.16 90/04/18 12:16:55 bostic 76 75
c `LineNumber' not incremented when reading :include: file
c bug report 4.3BSD/usr.lib/120
e
s 00002/00001/00573
d D 5.15 89/02/27 09:16:46 bostic 75 74
c add types.h for pwd.h
e
s 00000/00006/00574
d D 5.14 89/01/01 17:17:47 bostic 74 73
c remove DEBUG
e
s 00003/00003/00577
d D 5.13 88/11/17 10:39:18 bostic 73 72
c debug shouldn't change ability to mail to programs, pipes, etc.
e
s 00011/00009/00569
d D 5.12 88/06/30 14:59:33 bostic 72 71
c install approved copyright notice
e
s 00016/00010/00562
d D 5.11 88/03/13 19:52:58 bostic 71 70
c add Berkeley specific header
e
s 00002/00004/00570
d D 5.10 88/03/13 18:21:47 bostic 70 69
c replace sameword with strcasecmp
e
s 00005/00002/00569
d D 5.9 86/10/23 10:21:52 eric 69 68
c set QBADADDR on illegal cases -- such as sending directly to files
e
s 00002/00002/00569
d D 5.8 86/10/23 10:11:07 eric 68 67
c Fix security bug allowing writing to arbitrary files; from Bart Miller
c at U. Wisconsin.
e
s 00008/00010/00563
d D 5.7 86/01/09 14:36:59 eric 67 66
c allow underscores in login names
e
s 00001/00001/00572
d D 5.6 85/12/07 08:57:01 eric 66 65
m 
c ischar => isascii
e
s 00002/00000/00571
d D 5.5 85/12/07 08:17:29 eric 65 64
m 
c several small bugs: don't die if no environment, don't look in
c ESM_DEADLETTER state in savemail; lowercase before getpwnam to
c allow upper case regular names in alias file
e
s 00001/00000/00570
d D 5.4 85/09/19 12:17:45 eric 64 63
m 
c count recipients
e
s 00001/00001/00569
d D 5.3 85/06/08 00:37:08 eric 63 62
m 
c lint
e
s 00000/00002/00570
d D 5.2 85/06/07 22:17:17 miriam 62 61
m 
c Resolve duplicate SccsId
e
s 00014/00000/00558
d D 5.1 85/06/07 15:10:29 dist 61 59
m 
c Add copyright
e
s 00000/00000/00558
d R 4.3.1.1 84/06/17 16:18:01 eric 60 59
m 
c abortive attempt to install a name server.... sigh.
e
s 00006/00000/00552
d D 4.3 84/03/11 19:58:07 eric 59 58
m 
c disable UPPER->lower case mapping in RHS's of aliases so that upper
c case letters can be used in file names and as args to programs.
e
s 00002/00001/00550
d D 4.2 83/10/29 16:45:59 eric 58 57
m 
c declare getpwnam in recipient.c for earlier systems
e
s 00000/00000/00551
d D 4.1 83/07/25 19:46:05 eric 57 56
m 
c 4.2 release version
e
s 00005/00000/00546
d D 3.54 83/05/21 11:01:31 eric 56 55
m 
c Miscellaneous changes for PDP-11's.
c Always send to a login name before a full name.
e
s 00008/00004/00538
d D 3.53 83/05/20 11:49:30 eric 55 54
m 238
m 239
c Don't stack processes when VRFY fails.
c Give an error message on multiple RCPT commands with a bad address.
e
s 00005/00001/00537
d D 3.52 83/03/08 19:22:13 eric 54 53
m 205
c Pass the delimiter character to parseaddr so that we can correctly
c decide between comma and space
e
s 00002/00002/00536
d D 3.51 83/01/03 18:01:57 eric 53 52
m 
c give more useful error messages (including the errno that caused
c a temporary failure); reflect these messages out to mailq
e
s 00001/00001/00537
d D 3.50 82/12/24 08:15:22 eric 52 51
m 108
c Change parse to parseaddr for BB&N TCP/IP implementation; clean up
c comments in daemon.c to simplify the poor alternate protocol type.
e
s 00004/00004/00534
d D 3.49 82/12/13 18:26:59 eric 51 50
m 085
c The routine "sendto" is now a system call (yeuch!); change our sendto
c to "sendtolist"
e
s 00013/00006/00525
d D 3.48 82/11/28 00:23:16 eric 50 49
m 
c Many changes resulting from a complete code readthrough.  Most of these
c fix minor bugs or change the internal structure for clarity, etc.  There
c should be almost no externally visible changes (other than some cleaner
c error message printouts and the like).
e
s 00001/00001/00530
d D 3.47 82/11/24 17:16:15 eric 49 48
m 026
c run SMTP jobs in a subprocess so that multiple jobs will work.  This
c delta also changes the envelope data structure so that flags are in
c a bit map, and adjusts some of the semantics.  The transcript is now
c local to an envelope.  A bunch of old code is deleted.  A serious bug
c was fixed in the "run in background" code.  Etc., etc.
e
s 00003/00005/00528
d D 3.46 82/11/18 17:58:43 eric 48 47
m 079
c minor cleanup from previous delta
e
s 00003/00000/00530
d D 3.45 82/11/18 17:54:40 eric 47 46
m 079
c Fix bug causing loops in sendto if there are scanner errors in addresses
e
s 00019/00022/00511
d D 3.44 82/11/14 15:14:17 eric 46 45
m 074
c fix quote processing on program mailers
e
s 00002/00002/00531
d D 3.43 82/11/03 09:49:36 eric 45 44
m 049
c Arrange to strip quote bits in message header; move SPACESUB into
c conf.c; change SpaceSub to unquoted dot
e
s 00003/00002/00530
d D 3.42 82/09/18 20:37:54 eric 44 43
c fix botch where it believes that a list is !oldstyle just because
c it has an alias expansion in it.
e
s 00007/00001/00525
d D 3.41 82/09/12 22:17:38 eric 43 42
c accept ": ... ;" syntax for groups if !oldstyle
e
s 00012/00027/00514
d D 3.40 82/09/06 16:25:15 eric 42 41
c install new state-driven scanner; make everyone use it, thus fixing
c problems of quoted commas, etc.
e
s 00006/00006/00535
d D 3.39 82/08/08 01:03:19 eric 41 40
c change debug level to a debug vector; add levels on logging (and the
c -L flag); change logging to be by message-id; elevate message-id;
c some lint-type cleanup
e
s 00004/00008/00537
d D 3.38 82/06/07 07:55:01 eric 40 39
c make transcripts verbose always; misc. message cleanup, etc.
e
s 00000/00029/00545
d D 3.37 82/06/07 07:06:18 eric 39 38
c strip out xlate stuff -- this belongs at a different level
e
s 00002/00002/00572
d D 3.36 82/05/31 18:50:21 eric 38 37
c pass lint.  notice that definitions in llib-lc have changed for
c alarm() and sleep() calls {arg was unsigned, is now int}.
e
s 00005/00005/00569
d D 3.35 82/05/22 01:38:39 eric 37 36
c add "envelopes" to contain the basic information needed as control
c info for each message.  currently there is only one envelope -- this
c being the obvious stupid conversion.  later there will be separate
c envelopes for error messages, return receipts, etc.
e
s 00029/00000/00545
d D 3.34 82/02/04 20:31:08 eric 36 35
c add host aliasing; add -p flag.  this version doesn't yet know about
c replacing the text of the host alias into the message however.  syntax
c is grotty: "/hostmatch:%s@newhost" or whatever.
e
s 00002/00001/00543
d D 3.33 82/01/23 14:18:57 eric 35 34
c only catch filenames if the "/" is leading
e
s 00003/00003/00541
d D 3.32 82/01/01 18:27:28 eric 34 33
c send to dead.letter using sendto/recipient/deliver mechanism rather
c than mailfile; this fixes a bug with the "from" name and seems like
c a better abstraction.
e
s 00002/00001/00542
d D 3.31 81/12/06 12:40:20 eric 33 32
c cleanup so it will go through lint without any fancy grep -v's;
c change the way SCCS Id's are handled.
e
s 00021/00010/00522
d D 3.30 81/11/21 18:43:58 eric 32 31
c change the send queue to be only one queue instead of one per mailer.
c this is slightly inefficient but simpler.  also, pass this queue
c around so we can have multiple send queues.  this makes VRFY work.
e
s 00010/00001/00522
d D 3.29 81/11/21 16:38:54 eric 31 29
c convert to SMTP draft 3 -- finishing touches.  Punt on the VRFY/
c EXPN commands for now; they aren't required anyhow.  Move the fullname
c into the address structure so it can be inherited.
e
s 00094/00014/00509
d D 3.28.1.1 81/11/21 15:50:15 eric 30 29
c links together aliases into proper trees.  This is in part an
c attempt to do the SMTP VRFY command properly, but there are a number
c of annoying problems that convince me that this is the wrong way to
c do it.  Sigh.
e
s 00010/00007/00513
d D 3.28 81/10/26 14:23:15 eric 29 28
c Install new experimental queueing facility -- one stage timeout,
c etc.  This version is still quite incomplete.  It needs to reorder
c the queue after some interval, do two-stage timeout, take option
c info from the queue file instead of the command line, read the
c sender's .mailcf file, etc.  Some of this is useful for SMTP also.
e
s 00005/00006/00515
d D 3.27 81/10/23 19:38:33 eric 28 27
c Eliminate magic MN_LOCAL and MN_PROG; change q_mailer item in ADDRESS
c to be pointer to mailer rather than index.
e
s 00000/00000/00521
d D 3.26 81/10/19 22:27:46 eric 27 26
c implement SMTP mode -- doesn't support source routing or the
c HELP command, and doesn't give the correct code on VRFY or forwarding.
c Maybe someday....
e
s 00001/00001/00520
d D 3.25 81/10/17 16:58:24 eric 26 25
c initial prep to put in Daemon mode
e
s 00026/00006/00495
d D 3.24 81/09/28 19:17:32 eric 25 24
c enable aliases to self-reference themselves correctly.
e
s 00008/00001/00493
d D 3.23 81/09/22 11:33:20 eric 24 23
c finally make suppression of sender in mailing lists work -- this version
c also works correctly on simple aliases.
e
s 00007/00003/00487
d D 3.22 81/09/21 18:49:43 eric 23 22
c fix suppression of from address in mailing lists.
e
s 00014/00010/00476
d D 3.21 81/09/16 20:04:17 eric 22 21
c take underscore as well as space to separate parts of a person's
c full name.  Dot notation should be made to work someday also.
e
s 00013/00009/00473
d D 3.20 81/09/16 17:16:35 eric 21 20
c have .forward ownership stick harder than :include: ownership:
c this prevents cretins from using writable root files for nastiness.
c all this is pointless if /usr/lib/aliases is writable though....
e
s 00008/00001/00474
d D 3.19 81/09/16 16:39:58 eric 20 19
c be REALLY clever and inherit uid/gid from owner of :include:
c files also...   solves problem of alias to non-secure file
e
s 00004/00006/00471
d D 3.18 81/09/16 16:24:26 eric 19 18
c last delta was too paranoid -- this increases the number of
c cases that work (but is still safe -- I hope)
e
s 00061/00012/00416
d D 3.17 81/09/16 16:08:24 eric 18 17
c run as the user forwarding mail after a .forward operation;
c fix a bug in .forwarding that caused recursive expansion;
c restrict mail to programs, files, and with :include: for security
c reasons.
e
s 00008/00002/00420
d D 3.16 81/09/12 22:54:44 eric 17 16
c don't match on one-word gecos entries to avoid stealing mail
e
s 00004/00000/00418
d D 3.15 81/09/12 17:55:17 eric 16 15
c print message when sending to full name equivalent
e
s 00023/00002/00395
d D 3.14 81/09/12 17:34:21 eric 15 14
c match on full name for local users
e
s 00028/00002/00369
d D 3.13 81/09/12 16:37:14 eric 14 12
c preliminary work to take full names
e
s 00026/00002/00369
d R 3.13 81/09/12 16:33:17 eric 13 12
c preliminary work to take full names
e
s 00057/00002/00314
d D 3.12 81/09/07 14:13:07 eric 12 11
c fix up umask; allow setuid on files to take recipient owner;
c factor some configuration info into conf.c
e
s 00062/00002/00254
d D 3.11 81/09/07 12:33:55 eric 11 10
c add auto-rebuild on alias database; fix some aliasing bugs;
c add statistics to rebuild; slight code restructuring; change
c version handling one last (?) time
e
s 00017/00027/00239
d D 3.10 81/09/06 19:49:37 eric 10 9
c cleanup, commenting, linting, etc.
e
s 00002/00000/00264
d D 3.9 81/08/27 11:43:19 eric 9 8
c on -t, use argument list as a supress list
e
s 00007/00000/00257
d D 3.8 81/08/23 12:09:17 eric 8 7
c plug assorted security holes
e
s 00001/00000/00256
d D 3.7 81/08/22 19:36:41 eric 7 6
c only use a .forward file if owned by the receiver
e
s 00006/00002/00250
d D 3.6 81/08/22 14:31:21 eric 6 5
c fix mail to file problem (giving inappropriate diagnostic)
e
s 00005/00005/00247
d D 3.5 81/08/21 18:18:57 eric 5 4
c drop M_FINAL, change some other defined constant names
e
s 00000/00007/00252
d D 3.4 81/08/20 15:14:56 eric 4 3
c clean up some header information; don't reopen tempfile as
c stdin (to fix some problems with saving mail on interrupts)
e
s 00002/00001/00257
d D 3.3 81/08/20 14:50:19 eric 3 2
c pretty up message that include() prints
e
s 00009/00005/00249
d D 3.2 81/08/20 14:36:47 eric 2 1
c merge forwarding with :include:ing
e
s 00254/00000/00000
d D 3.1 81/08/20 14:33:05 eric 1 0
c split deliver.c and sendto.c
e
u
U
f b 
f i 
t
T
I 61
/*
I 72
D 229
 * Copyright (c) 1983 Eric P. Allman
E 229
I 229
 * Copyright (c) 1983, 1995 Eric P. Allman
E 229
E 72
D 71
**  Sendmail
**  Copyright (c) 1983  Eric P. Allman
**  Berkeley, California
**
**  Copyright (c) 1983 Regents of the University of California.
**  All rights reserved.  The Berkeley software License Agreement
**  specifies the terms and conditions for redistribution.
*/
E 71
I 71
D 145
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.
E 145
I 145
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 145
 *
D 78
 * Redistribution and use in source and binary forms are permitted
D 72
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
 *
 *  Sendmail
 *  Copyright (c) 1983  Eric P. Allman
 *  Berkeley, California
E 72
I 72
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
E 78
I 78
 * %sccs.include.redist.c%
E 78
E 72
 */
E 71

#ifndef lint
D 71
static char	SccsId[] = "%W% (Berkeley) %G%";
#endif not lint
E 71
I 71
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 71

I 75
D 120
# include <sys/types.h>
E 120
I 120
# include "sendmail.h"
E 120
D 138
# include <sys/stat.h>
E 138
I 85
D 106
# include <sys/file.h>
I 105
# include <sys/fcntl.h>
E 106
I 106
D 128
# include <fcntl.h>
E 128
E 106
E 105
E 85
E 75
E 61
I 1
D 4
# include <stdio.h>
E 4
D 226
# include <pwd.h>
E 226
I 12
D 29
# include <sys/types.h>
# include <sys/stat.h>
E 29
E 12
D 4
# include <signal.h>
# include <ctype.h>
# include <errno.h>
E 4
D 120
# include "sendmail.h"
E 120
I 29
D 75
# include <sys/stat.h>
E 75
E 29
D 4
# ifdef LOG
# include <syslog.h>
# endif LOG
E 4

D 33
static char SccsId[] = "%W%	%G%";
E 33
I 33
D 62
SCCSID(%W%	%Y%	%G%);
E 33

E 62
/*
D 51
**  SENDTO -- Designate a send list.
E 51
I 51
**  SENDTOLIST -- Designate a send list.
E 51
**
**	The parameter is a comma-separated list of people to send to.
**	This routine arranges to send to all of them.
**
I 30
**	The `ctladdr' is the address that expanded to be this one,
**	e.g., in an alias expansion.  This is used for a number of
**	purposed, most notably inheritance of uid/gid for protection
**	purposes.  It is also used to detect self-reference in group
**	expansions and the like.
**
E 30
**	Parameters:
**		list -- the send list.
D 42
**		copyf -- the copy flag; passed to parse.
E 42
I 18
**		ctladdr -- the address template for the person to
**			send to -- effective uid/gid are important.
I 32
**			This is typically the alias that caused this
**			expansion.
**		sendq -- a pointer to the head of a queue to put
**			these people into.
I 200
**		aliaslevel -- the current alias nesting depth -- to
**			diagnose loops.
E 200
I 118
**		e -- the envelope in which to add these recipients.
E 118
E 32
I 30
**		qflags -- special flags to set in the q_flags field.
E 30
E 18
**
**	Returns:
D 30
D 113
**		none
E 113
I 113
**		The number of addresses actually on the list.
E 113
E 30
I 30
**		pointer to chain of addresses.
E 30
**
**	Side Effects:
**		none.
*/

D 195
# define MAXRCRSN	10
E 195
I 195
#define MAXRCRSN	10	/* maximum levels of alias recursion */
E 195

I 195
/* q_flags bits inherited from ctladdr */
D 198
#define QINHERITEDBITS	(QPINGONSUCCESS|QPINGONFAILURE|QPINGONDELAY|QHASRETPARAM|QNOBODYRETURN)
E 198
I 198
D 223
#define QINHERITEDBITS	(QPINGONSUCCESS|QPINGONFAILURE|QPINGONDELAY|QHAS_RET_PARAM|QRET_HDRS)
E 223
I 223
D 224
#define QINHERITEDBITS	(QPINGONSUCCESS|QPINGONFAILURE|QPINGONDELAY)
E 224
I 224
#define QINHERITEDBITS	(QPINGONSUCCESS|QPINGONFAILURE|QPINGONDELAY|QHASNOTIFY)
E 224
E 223
E 198

I 202
int
E 202
E 195
D 18
sendto(list, copyf)
E 18
I 18
D 30
D 32
sendto(list, copyf, ctladdr)
E 32
I 32
D 42
sendto(list, copyf, ctladdr, sendq)
E 42
I 42
D 51
sendto(list, ctladdr, sendq)
E 51
I 51
D 93
sendtolist(list, ctladdr, sendq)
E 93
I 93
D 200
sendtolist(list, ctladdr, sendq, e)
E 200
I 200
sendtolist(list, ctladdr, sendq, aliaslevel, e)
E 200
E 93
E 51
E 42
E 32
E 30
I 30
ADDRESS *
sendto(list, copyf, ctladdr, qflags)
E 30
E 18
	char *list;
D 42
	int copyf;
E 42
I 18
	ADDRESS *ctladdr;
I 33
	ADDRESS **sendq;
I 200
	int aliaslevel;
E 200
I 93
	register ENVELOPE *e;
E 93
E 33
I 30
	u_short qflags;
E 30
E 18
{
	register char *p;
D 10
	register char *q;
	register char c;
	ADDRESS *a;
	bool more;
E 10
I 10
D 42
	bool more;		/* set if more addresses to send to */
I 11
	ADDRESS *al;		/* list of addresses to send to */
E 42
I 42
D 43
	register ADDRESS *al;		/* list of addresses to send to */
E 43
I 43
	register ADDRESS *al;	/* list of addresses to send to */
E 43
E 42
I 24
	bool firstone;		/* set on first address sent */
I 25
D 111
	bool selfref;		/* set if this list includes ctladdr */
E 111
I 54
	char delimiter;		/* the address delimiter */
I 113
	int naddrs;
I 212
	int i;
E 212
I 148
	char *oldto = e->e_to;
I 196
D 212
	static char *bufp = NULL;
	static int buflen;
E 212
I 212
	char *bufp;
E 212
	char buf[MAXNAME + 1];
E 196
E 148
E 113
E 54
I 30
	ADDRESS *sibl;		/* sibling pointer in tree */
	ADDRESS *prev;		/* previous sibling */
E 30
E 25
E 24
E 11
E 10

I 157
	if (list == NULL)
	{
		syserr("sendtolist: null list");
		return 0;
	}

E 157
I 11
D 74
# ifdef DEBUG
E 74
D 41
	if (Debug > 1)
E 41
I 41
	if (tTd(25, 1))
E 41
D 25
		printf("sendto: %s\n", list);
E 25
I 25
	{
		printf("sendto: %s\n   ctladdr=", list);
		printaddr(ctladdr, FALSE);
	}
E 25
D 74
# endif DEBUG
E 74

I 43
	/* heuristic to determine old versus new style addresses */
D 44
	if (index(list, ',') != NULL || index(list, ';') != NULL ||
	    index(list, '<') != NULL || index(list, '(') != NULL)
E 44
I 44
	if (ctladdr == NULL &&
D 97
	    (index(list, ',') != NULL || index(list, ';') != NULL ||
	     index(list, '<') != NULL || index(list, '(') != NULL))
E 97
I 97
	    (strchr(list, ',') != NULL || strchr(list, ';') != NULL ||
	     strchr(list, '<') != NULL || strchr(list, '(') != NULL))
E 97
E 44
D 49
		CurEnv->e_oldstyle = FALSE;
E 49
I 49
D 93
		CurEnv->e_flags &= ~EF_OLDSTYLE;
E 93
I 93
		e->e_flags &= ~EF_OLDSTYLE;
E 93
I 54
	delimiter = ' ';
D 93
	if (!bitset(EF_OLDSTYLE, CurEnv->e_flags) || ctladdr != NULL)
E 93
I 93
	if (!bitset(EF_OLDSTYLE, e->e_flags) || ctladdr != NULL)
E 93
		delimiter = ',';
E 54
E 49

E 43
E 11
D 10
	/* more keeps track of what the previous delimiter was */
E 10
D 42
	more = TRUE;
E 42
I 24
	firstone = TRUE;
I 25
D 111
	selfref = FALSE;
E 111
E 25
E 24
I 11
	al = NULL;
I 113
	naddrs = 0;
E 113
I 43

E 43
E 11
D 42
	for (p = list; more; )
E 42
I 42
D 196
	for (p = list; *p != '\0'; )
E 196
I 196
D 210
D 211
	if (buf == NULL)
E 211
I 211
D 214
	if (bufp == NULL)
E 214
E 211
E 210
I 210
D 212
	if (bufp == NULL)
E 210
	{
E 212
I 212
	/* make sure we have enough space to copy the string */
	i = strlen(list) + 1;
	if (i <= sizeof buf)
E 212
		bufp = buf;
D 212
		buflen = sizeof buf - 1;
	}
	if (strlen(list) > buflen)
	{
		/* allocate additional space */
		if (bufp != buf)
			free(bufp);
		buflen = strlen(list);
		bufp = malloc(buflen + 1);
	}
	strcpy(bufp, list);
E 212
I 212
	else
		bufp = xalloc(i);
D 216
	strcpy(bufp, denlstring(list));
E 216
I 216
D 218
	strcpy(bufp, denlstring(list, FALSE));
E 218
I 218
	strcpy(bufp, denlstring(list, FALSE, TRUE));
E 218
E 216
E 212

	for (p = bufp; *p != '\0'; )
E 196
E 42
	{
I 121
		auto char *delimptr;
E 121
I 10
D 42
		register char *q;
		register char c;
		ADDRESS *a;
E 42
I 42
		register ADDRESS *a;
D 121
		extern char *DelimChar;		/* defined in prescan */
E 121
E 42

E 10
D 42
		/* find the end of this address */
		while (*p == ' ' || *p == '\t')
E 42
I 42
		/* parse the address */
D 110
		while (isspace(*p) || *p == ',')
E 110
I 110
		while ((isascii(*p) && isspace(*p)) || *p == ',')
E 110
E 42
			p++;
D 42
		q = p;
		while ((c = *p++) != '\0' && c != ',' && c != '\n')
E 42
I 42
D 48
		if ((a = parse(p, (ADDRESS *) NULL, 1)) == NULL)
I 47
		{
			p = DelimChar;
E 47
E 42
			continue;
I 47
		}
E 48
I 48
D 52
		a = parse(p, (ADDRESS *) NULL, 1);
E 52
I 52
D 54
		a = parseaddr(p, (ADDRESS *) NULL, 1);
E 54
I 54
D 93
		a = parseaddr(p, (ADDRESS *) NULL, 1, delimiter);
E 93
I 93
D 121
		a = parseaddr(p, (ADDRESS *) NULL, 1, delimiter, e);
E 93
E 54
E 52
E 48
E 47
D 42
		more = c != '\0';
		*--p = '\0';
		if (more)
			p++;
I 11
		if (*q == '\0')
			continue;
E 11

		/* parse the address */
		if ((a = parse(q, (ADDRESS *) NULL, copyf)) == NULL)
			continue;
E 42
I 42
		p = DelimChar;
E 121
I 121
D 159
		a = parseaddr(p, (ADDRESS *) NULL, 1, delimiter, &delimptr, e);
E 159
I 159
		a = parseaddr(p, NULLADDR, RF_COPYALL, delimiter, &delimptr, e);
E 159
		p = delimptr;
E 121
I 48
		if (a == NULL)
			continue;
E 48
E 42
D 25

D 11
		/* arrange to send to this person */
E 11
I 11
		/* put it on the local send list */
E 25
		a->q_next = al;
I 18
		a->q_alias = ctladdr;
I 30
		if (ctladdr != NULL)
			a->q_flags |= ctladdr->q_flags & ~QPRIMARY;
		a->q_flags |= qflags;
E 30
I 25

I 36
D 39
		/*
		**  If this address should have a host alias, take care
		**  of it now.
		*/

		if (strcmp(a->q_mailer->m_name, "xlate") == 0)
		{
			register char *newaddr;
			extern char *hostalias();

			newaddr = hostalias(a);
			if (newaddr == NULL)
			{
				/* couldn't do anything with it */
				giveresponse(EX_NOUSER, TRUE, a->q_mailer);
				continue;
			}

			if (Verbose)
				printf("%s... translated to %s\n", a->q_paddr, newaddr);

			/* change the print address so the message looks good */
			a->q_paddr = newaddr;

			/* call ourselves recursively to send to our friends */
			sendto(newaddr, copyf > 0 ? 0 : copyf, ctladdr, sendq);
			continue;
		}

E 39
E 36
D 225
		/* see if this should be marked as a primary address */
E 25
I 24
		if (ctladdr == NULL ||
D 42
		    (firstone && !more && bitset(QPRIMARY, ctladdr->q_flags)))
E 42
I 42
		    (firstone && *p == '\0' && bitset(QPRIMARY, ctladdr->q_flags)))
E 42
			a->q_flags |= QPRIMARY;
E 24
E 18
D 25
		al = a;
E 25
I 25

E 225
D 104
		/* put on send queue or suppress self-reference */
E 104
D 50
		if (ctladdr != NULL && sameaddr(ctladdr, a, FALSE))
E 50
I 50
D 199
		if (ctladdr != NULL && sameaddr(ctladdr, a))
E 50
D 111
			selfref = TRUE;
E 111
I 111
			ctladdr->q_flags |= QSELFREF;
E 111
D 104
		else
			al = a;
E 104
I 104
		al = a;
E 104
E 25
I 24
		firstone = FALSE;
E 24
	}

I 25
D 112
	/* if this alias doesn't include itself, delete ctladdr */
D 111
	if (!selfref && ctladdr != NULL)
E 111
I 111
	if (ctladdr != NULL && !bitset(QSELFREF, ctladdr->q_flags))
E 111
I 104
	{
		if (tTd(25, 5))
		{
			printf("sendtolist: QDONTSEND ");
			printaddr(ctladdr, FALSE);
		}
E 104
		ctladdr->q_flags |= QDONTSEND;
I 104
	}
E 104

E 112
E 25
	/* arrange to send to everyone on the local send list */
I 30
	prev = sibl = NULL;
	if (ctladdr != NULL)
		prev = ctladdr->q_child;
E 30
	while (al != NULL)
	{
		register ADDRESS *a = al;
I 55
D 142
		extern ADDRESS *recipient();
E 142
E 55
I 30
		extern ADDRESS *recipient();
E 30

		al = a->q_next;
I 77
D 89
		setctladdr(a);
E 89
E 77
E 11
D 30
D 32
		recipient(a);
E 32
I 32
D 55
		recipient(a, sendq);
E 55
I 55
D 93
		a = recipient(a, sendq);
E 93
I 93
		a = recipient(a, sendq, e);
E 93
E 55
E 32
I 31

E 199
D 195
		/* arrange to inherit full name */
		if (a->q_fullname == NULL && ctladdr != NULL)
			a->q_fullname = ctladdr->q_fullname;
E 195
I 195
		/* arrange to inherit attributes from parent */
		if (ctladdr != NULL)
		{
I 234
			ADDRESS *b;
			extern ADDRESS *self_reference();

D 235
#if 0
E 235
E 234
I 199
			/* self reference test */
			if (sameaddr(ctladdr, a))
I 235
			{
				if (tTd(27, 5))
				{
					printf("sendtolist: QSELFREF ");
					printaddr(ctladdr, FALSE);
				}
E 235
				ctladdr->q_flags |= QSELFREF;
I 234
D 235
#endif
E 235
I 235
			}
E 235
E 234

I 234
			/* check for address loops */
			b = self_reference(a, e);
			if (b != NULL)
			{
				b->q_flags |= QSELFREF;
I 235
				if (tTd(27, 5))
				{
					printf("sendtolist: QSELFREF ");
					printaddr(b, FALSE);
				}
E 235
				if (a != b)
				{
I 235
					if (tTd(27, 5))
					{
						printf("sendtolist: QDONTSEND ");
						printaddr(a, FALSE);
					}
E 235
					a->q_flags |= QDONTSEND;
					continue;
				}
			}

E 234
E 199
			/* full name */
			if (a->q_fullname == NULL)
				a->q_fullname = ctladdr->q_fullname;

			/* various flag bits */
			a->q_flags &= ~QINHERITEDBITS;
			a->q_flags |= ctladdr->q_flags & QINHERITEDBITS;
I 201

			/* original recipient information */
			a->q_orcpt = ctladdr->q_orcpt;
E 201
		}
I 199

		al = a;
		firstone = FALSE;
	}

	/* arrange to send to everyone on the local send list */
	while (al != NULL)
	{
		register ADDRESS *a = al;

		al = a->q_next;
D 200
		a = recipient(a, sendq, e);
E 200
I 200
		a = recipient(a, sendq, aliaslevel, e);
E 200
E 199
E 195
I 113
		naddrs++;
E 113
E 31
E 30
I 30
		sibl = recipient(a);
		if (sibl != NULL)
		{
			extern ADDRESS *addrref();

			/* inherit full name */
			if (sibl->q_fullname == NULL && ctladdr != NULL)
				sibl->q_fullname = ctladdr->q_fullname;

			/* link tree together (but only if the node is new) */
			if (sibl == a)
			{
				sibl->q_sibling = prev;
				prev = sibl;
			}
		}
E 30
	}
I 11

E 11
D 37
	To = NULL;
E 37
I 37
D 93
	CurEnv->e_to = NULL;
E 93
I 93
D 148
	e->e_to = NULL;
E 148
I 148
	e->e_to = oldto;
I 212
	if (bufp != buf)
		free(bufp);
E 212
E 148
I 113
	return (naddrs);
E 113
E 93
E 37
I 30
	if (ctladdr != NULL)
		ctladdr->q_child = prev;
	return (prev);
E 30
}
/*
I 30
**  ADDRREF -- return pointer to address that references another address.
**
**	Parameters:
**		a -- address to check.
**		r -- reference to find.
**
**	Returns:
**		address of node in tree rooted at 'a' that references
**			'r'.
**		NULL if no such node exists.
**
**	Side Effects:
**		none.
*/

ADDRESS *
addrref(a, r)
	register ADDRESS *a;
	register ADDRESS *r;
{
	register ADDRESS *q;

	while (a != NULL)
	{
		if (a->q_child == r || a->q_sibling == r)
			return (a);
		q = addrref(a->q_child, r);
		if (q != NULL)
			return (q);
		a = a->q_sibling;
	}
	return (NULL);
}
/*
E 30
**  RECIPIENT -- Designate a message recipient
**
**	Saves the named person for future mailing.
**
**	Parameters:
**		a -- the (preparsed) address header for the recipient.
I 32
**		sendq -- a pointer to the head of a queue to put the
**			recipient in.  Duplicate supression is done
**			in this queue.
I 200
**		aliaslevel -- the current alias nesting depth.
E 200
I 104
**		e -- the current envelope.
E 104
E 32
**
**	Returns:
D 30
D 55
**		none.
E 55
I 55
**		The actual address in the queue.  This will be "a" if
**		the address is not a duplicate, else the original address.
E 55
E 30
I 30
**		pointer to address actually inserted in send list.
E 30
**
**	Side Effects:
**		none.
*/
D 142

I 79
extern ADDRESS *getctladdr();
E 142
I 85
D 115
extern char	*RcptLogFile;
E 115
E 85

E 79
I 55
ADDRESS *
E 55
I 30
ADDRESS *
E 30
D 32
recipient(a)
E 32
I 32
D 93
recipient(a, sendq)
E 93
I 93
D 200
recipient(a, sendq, e)
E 200
I 200
recipient(a, sendq, aliaslevel, e)
E 200
E 93
E 32
	register ADDRESS *a;
I 32
	register ADDRESS **sendq;
I 200
	int aliaslevel;
E 200
I 93
	register ENVELOPE *e;
E 93
E 32
{
	register ADDRESS *q;
I 10
	ADDRESS **pq;
E 10
	register struct mailer *m;
I 46
	register char *p;
	bool quoted = FALSE;		/* set if the addr has a quote bit */
I 88
	int findusercount = 0;
I 225
	bool initialdontsend = bitset(QDONTSEND, a->q_flags);
E 225
E 88
D 189
	char buf[MAXNAME];		/* unquoted image of the user name */
E 189
I 189
	int i;
	char *buf;
D 222
	char buf0[MAXNAME];		/* unquoted image of the user name */
E 222
I 222
	char buf0[MAXNAME + 1];		/* unquoted image of the user name */
E 222
E 189
E 46
I 18
D 79
	extern ADDRESS *getctladdr();
E 79
I 29
D 118
	extern bool safefile();
E 118
I 118
	extern int safefile();
E 118
E 29
E 18
D 10
	char buf[MAXNAME];
E 10

D 37
	To = a->q_paddr;
E 37
I 37
D 93
	CurEnv->e_to = a->q_paddr;
E 93
I 93
	e->e_to = a->q_paddr;
E 93
E 37
D 28
	m = Mailer[a->q_mailer];
E 28
I 28
	m = a->q_mailer;
E 28
	errno = 0;
I 225
	if (aliaslevel == 0)
		a->q_flags |= QPRIMARY;
E 225
D 74
# ifdef DEBUG
E 74
D 41
	if (Debug)
E 41
I 41
	if (tTd(26, 1))
E 41
D 25
		printf("recipient(%s)\n", To);
E 25
I 25
	{
D 225
		printf("\nrecipient: ");
E 225
I 225
		printf("\nrecipient (%d): ", aliaslevel);
E 225
		printaddr(a, FALSE);
	}
E 25
D 74
# endif DEBUG
E 74

I 158
	/* if this is primary, add it to the original recipient list */
	if (a->q_alias == NULL)
	{
		if (e->e_origrcpt == NULL)
			e->e_origrcpt = a->q_paddr;
		else if (e->e_origrcpt != a->q_paddr)
			e->e_origrcpt = "";
	}

E 158
	/* break aliasing loops */
D 200
	if (AliasLevel > MAXRCRSN)
E 200
I 200
	if (aliaslevel > MAXRCRSN)
E 200
	{
I 230
		a->q_status = "5.4.6";
E 230
D 116
		usrerr("aliasing/forwarding loop broken");
E 116
I 116
D 202
		usrerr("554 aliasing/forwarding loop broken");
E 202
I 202
		usrerr("554 aliasing/forwarding loop broken (%d aliases deep; %d max",
			aliaslevel, MAXRCRSN);
E 202
E 116
D 30
D 55
		return;
E 55
I 55
		return (a);
E 55
E 30
I 30
		return (NULL);
E 30
	}

	/*
D 29
	**  Do sickly crude mapping for program mailing, etc.
E 29
I 29
	**  Finish setting up address structure.
E 29
	*/

I 59
D 192
	/* set the queue timeout */
E 59
I 29
D 130
	a->q_timeout = TimeOut;
E 130
I 130
	a->q_timeout = TimeOuts.to_q_return;
E 130

E 192
I 59
D 125
	/* map user & host to lower case if requested on non-aliases */
	if (a->q_alias == NULL)
		loweraddr(a);

E 125
	/* get unquoted user for file, program or user.name check */
I 189
	i = strlen(a->q_user);
D 222
	if (i >= sizeof buf)
E 222
I 222
	if (i >= sizeof buf0)
E 222
		buf = xalloc(i + 1);
	else
		buf = buf0;
E 189
E 59
I 46
	(void) strcpy(buf, a->q_user);
	for (p = buf; *p != '\0' && !quoted; p++)
	{
D 92
		if (!isascii(*p) && (*p & 0377) != (SpaceSub & 0377))
E 92
I 92
		if (*p == '\\')
E 92
			quoted = TRUE;
	}
D 91
	stripquotes(buf, TRUE);
E 91
I 91
	stripquotes(buf);
E 91

E 46
D 102
	/* do sickly crude mapping for program mailing, etc. */
E 29
D 5
	if (a->q_mailer == M_LOCAL)
E 5
I 5
D 28
	if (a->q_mailer == MN_LOCAL)
E 28
I 28
D 46
	if (a->q_mailer == LocalMailer)
E 46
I 46
	if (m == LocalMailer && buf[0] == '|')
E 102
I 102
	/* check for direct mailing to restricted mailers */
D 104
	if (a->q_alias == NULL && m == ProgMailer && !ForceMail)
E 104
I 104
D 130
	if (a->q_alias == NULL && m == ProgMailer)
E 130
I 130
D 164
	if (a->q_alias == NULL && m == ProgMailer &&
	    !bitset(EF_QUEUERUN, e->e_flags))
E 164
I 164
D 180
	if (a->q_alias == NULL && m == ProgMailer)
E 180
I 180
	if (m == ProgMailer)
E 180
E 164
E 130
E 104
E 102
E 46
E 28
E 5
	{
D 46
		if (a->q_user[0] == '|')
E 46
I 46
D 102
		a->q_mailer = m = ProgMailer;
		a->q_user++;
D 73
		if (a->q_alias == NULL && !tTd(0, 1) && !QueueRun && !ForceMail)
E 73
I 73
D 90
		if (a->q_alias == NULL && !QueueRun && !ForceMail)
E 90
I 90
		if (a->q_alias == NULL && !ForceMail)
E 90
E 73
E 46
		{
D 5
			a->q_mailer = M_PROG;
			m = Mailer[M_PROG];
E 5
I 5
D 28
			a->q_mailer = MN_PROG;
			m = Mailer[MN_PROG];
E 28
I 28
D 46
			a->q_mailer = m = ProgMailer;
E 28
E 5
			a->q_user++;
I 8
D 18
# ifdef PARANOID
			if (AliasLevel <= 0)
E 18
I 18
D 19
			if (getctladdr(a) == &From && Debug == 0)
E 19
I 19
D 21
			if (getctladdr(a) == NULL && Debug == 0)
E 21
I 21
D 29
			if (a->q_alias == NULL && Debug == 0)
E 29
I 29
D 34
			if (a->q_alias == NULL && Debug == 0 && !QueueRun)
E 34
I 34
D 41
			if (a->q_alias == NULL && Debug == 0 && !QueueRun && !ForceMail)
E 41
I 41
			if (a->q_alias == NULL && !tTd(0, 1) && !QueueRun && !ForceMail)
E 41
E 34
E 29
E 21
E 19
E 18
			{
				usrerr("Cannot mail directly to programs");
				a->q_flags |= QDONTSEND;
			}
E 46
I 46
D 68
			usrerr("Cannot mail directly to programs");
E 68
D 69
			a->q_flags |= QDONTSEND;
E 69
I 69
			a->q_flags |= QDONTSEND|QBADADDR;
E 69
I 68
			usrerr("Cannot mail directly to programs");
E 68
E 46
D 18
# endif PARANOID
E 18
E 8
		}
E 102
I 102
D 127
		a->q_flags |= QDONTSEND|QBADADDR;
E 127
I 127
D 180
		a->q_flags |= QBADADDR;
E 127
D 116
		usrerr("Cannot mail directly to programs", m->m_name);
E 116
I 116
D 148
		usrerr("550 Cannot mail directly to programs", m->m_name);
E 148
I 148
		usrerr("550 Cannot mail directly to programs");
E 180
I 180
		if (a->q_alias == NULL)
		{
			a->q_flags |= QBADADDR;
I 230
			a->q_status = "5.7.1";
E 230
			usrerr("550 Cannot mail directly to programs");
		}
		else if (bitset(QBOGUSSHELL, a->q_alias->q_flags))
		{
			a->q_flags |= QBADADDR;
I 230
			a->q_status = "5.7.1";
E 230
			usrerr("550 User %s@%s doesn't have a valid shell for mailing to programs",
				a->q_alias->q_ruser, MyHostName);
		}
		else if (bitset(QUNSAFEADDR, a->q_alias->q_flags))
		{
			a->q_flags |= QBADADDR;
I 230
			a->q_status = "5.7.1";
E 230
			usrerr("550 Address %s is unsafe for mailing to programs",
				a->q_alias->q_paddr);
		}
E 180
E 148
E 116
E 102
	}

	/*
D 23
	**  Look up this person in the recipient list.  If they
	**  are there already, return, otherwise continue.
	**  If the list is empty, just add it.
E 23
I 23
	**  Look up this person in the recipient list.
	**	If they are there already, return, otherwise continue.
	**	If the list is empty, just add it.  Notice the cute
	**	hack to make from addresses suppress things correctly:
	**	the QDONTSEND bit will be set in the send list.
	**	[Please note: the emphasis is on "hack."]
E 23
	*/

D 10
	if (m->m_sendq == NULL)
E 10
I 10
D 32
	for (pq = &m->m_sendq; (q = *pq) != NULL; pq = &q->q_next)
E 32
I 32
	for (pq = sendq; (q = *pq) != NULL; pq = &q->q_next)
E 32
E 10
	{
D 10
		m->m_sendq = a;
	}
	else
	{
		ADDRESS *pq;

		for (q = m->m_sendq; q != NULL; pq = q, q = q->q_next)
E 10
I 10
D 50
		if (!ForceMail && sameaddr(q, a, FALSE))
E 50
I 50
D 119
		if (!ForceMail && sameaddr(q, a))
E 119
I 119
		if (sameaddr(q, a))
E 119
E 50
E 10
		{
I 133
			/* if this is a reinsertion, just go ahead */
			if (bitset(QVERIFIED, q->q_flags))
				break;

E 133
D 10
			if (!ForceMail && sameaddr(q, a, FALSE))
			{
E 10
D 74
# ifdef DEBUG
E 74
D 10
				if (Debug)
					printf("(%s in sendq)\n", a->q_paddr);
E 10
I 10
D 41
			if (Debug)
E 41
I 41
			if (tTd(26, 1))
E 41
D 25
				printf("(%s in sendq)\n", a->q_paddr);
E 25
I 25
			{
				printf("%s in sendq: ", a->q_paddr);
				printaddr(q, FALSE);
			}
E 25
E 10
D 74
# endif DEBUG
E 74
D 10
				if (Verbose && !bitset(QDONTSEND, a->q_flags))
					message(Arpa_Info, "duplicate supressed");
				return;
			}
E 10
I 10
D 30
D 40
			if (Verbose && !bitset(QDONTSEND, a->q_flags))
E 40
I 40
D 112
			if (!bitset(QDONTSEND, a->q_flags))
E 40
E 30
I 30
			if (Verbose && !bitset(QDONTSEND|QPSEUDO, a->q_flags))
E 30
D 11
				message(Arpa_Info, "duplicate supressed");
E 11
I 11
				message(Arpa_Info, "duplicate suppressed");
E 112
I 23
D 24
			q->q_flags |= a->q_flags;
E 24
I 24
D 181
			if (!bitset(QPRIMARY, q->q_flags))
E 181
I 181
D 183
			if (!bitset(QPRIMARY, q->q_flags) ||
			    bitset(QSELFREF, q->q_flags))
E 183
I 183
			if (!bitset(QPRIMARY, q->q_flags))
E 183
E 181
I 112
			{
D 181
				if (!bitset(QDONTSEND, a->q_flags))
E 181
I 181
D 183
				if (!bitset(QDONTSEND, a->q_flags) &&
				    !bitset(QSELFREF, q->q_flags))
E 183
I 183
				if (!bitset(QDONTSEND, a->q_flags))
E 183
E 181
D 116
					message(Arpa_Info, "duplicate suppressed");
E 116
I 116
					message("duplicate suppressed");
E 116
E 112
D 182
				q->q_flags |= a->q_flags;
E 182
I 182
D 183
				q->q_flags |= a->q_flags & ~QDONTSEND;
E 183
I 183
				q->q_flags |= a->q_flags;
E 183
E 182
I 112
			}
I 183
			else if (bitset(QSELFREF, q->q_flags))
				q->q_flags |= a->q_flags & ~QDONTSEND;
E 183
E 112
E 24
E 23
E 11
D 30
D 55
			return;
E 55
I 55
D 148
			return (q);
E 148
I 148
			a = q;
D 204
			goto testselfdestruct;
E 204
I 204
			goto done;
E 204
E 148
E 55
E 30
I 30
			if (!bitset(QPSEUDO, a->q_flags))
				q->q_flags &= ~QPSEUDO;
			return (q);
E 30
E 10
		}
D 10

		/* add address on list */
		q = pq;
		q->q_next = a;
E 10
	}
I 10

	/* add address on list */
D 133
	*pq = a;
E 10
	a->q_next = NULL;
E 133
I 133
	if (*pq != a)
	{
		*pq = a;
		a->q_next = NULL;
	}

	a->q_flags &= ~QVERIFIED;
E 133
I 64
D 93
	CurEnv->e_nrcpts++;
E 93
I 93
D 103
	e->e_nrcpts++;
E 103
E 93
I 85
D 115

	if (a->q_alias == NULL && RcptLogFile != NULL &&
	    !bitset(QDONTSEND, a->q_flags))
	{
		static int RcptLogFd = -1;

		/*
		**  Log the incoming recipient name before aliasing,
		**  expanding, forwarding, rewriting, and all that jazz.
		**  We'll use this to track down out-of-date aliases,
		**  host names, and so forth.
		*/

		if (RcptLogFd < 0)
		{
			/* try to open the log file */
			RcptLogFd = open(RcptLogFile, O_WRONLY|O_APPEND|O_CREAT, 0666);
I 86
			if (RcptLogFd >= 0)
				(void) fcntl(RcptLogFd, F_SETFD, 1);
E 86
		}
		if (RcptLogFd >= 0)
		{
			int l = strlen(a->q_paddr);

			a->q_paddr[l] = '\n';
			if (write(RcptLogFd, a->q_paddr, l + 1) < 0)
			{
				(void) close(RcptLogFd);
				RcptLogFd = -1;
			}
			a->q_paddr[l] = '\0';
		}
	}
E 115
E 85
E 64
I 9
D 50
	if (DontSend)
		a->q_flags |= QDONTSEND;
E 50
E 9

	/*
D 102
	**  Alias the name and handle :include: specs.
E 102
I 102
	**  Alias the name and handle special mailer types.
E 102
	*/

I 88
  trylocaluser:
I 94
	if (tTd(29, 7))
		printf("at trylocaluser %s\n", a->q_user);

E 94
E 88
D 5
	if (a->q_mailer == M_LOCAL)
E 5
I 5
D 28
	if (a->q_mailer == MN_LOCAL)
E 28
I 28
D 46
	if (a->q_mailer == LocalMailer)
E 46
I 46
D 102
	if (m == LocalMailer && !bitset(QDONTSEND, a->q_flags))
E 102
I 102
D 117
	if (bitset(QDONTSEND, a->q_flags))
E 117
I 117
D 127
	if (bitset(QDONTSEND|QVERIFIED, a->q_flags))
E 127
I 127
	if (bitset(QDONTSEND|QBADADDR|QVERIFIED, a->q_flags))
E 127
E 117
D 148
		return (a);
E 148
I 148
		goto testselfdestruct;
E 148

	if (m == InclMailer)
E 102
E 46
E 28
E 5
	{
D 102
		if (strncmp(a->q_user, ":include:", 9) == 0)
E 102
I 102
		a->q_flags |= QDONTSEND;
D 104
		if (a->q_alias == NULL && !ForceMail)
E 104
I 104
D 130
		if (a->q_alias == NULL)
E 130
I 130
D 164
		if (a->q_alias == NULL && !bitset(EF_QUEUERUN, e->e_flags))
E 164
I 164
		if (a->q_alias == NULL)
E 164
E 130
E 104
E 102
		{
D 102
			a->q_flags |= QDONTSEND;
D 2
			include(&a->q_user[9]);
E 2
I 2
D 18
			if (Verbose)
				message(Arpa_Info, "including file %s", &a->q_user[9]);
			include(&a->q_user[9], " sending");
E 18
I 18
D 19
			if (getctladdr(a) == &From && Debug == 0)
E 19
I 19
D 21
			if (getctladdr(a) == NULL && Debug == 0)
E 21
I 21
D 29
			if (a->q_alias == NULL && Debug == 0)
E 29
I 29
D 34
			if (a->q_alias == NULL && Debug == 0 && !QueueRun)
E 34
I 34
D 41
			if (a->q_alias == NULL && Debug == 0 && !QueueRun && !ForceMail)
E 41
I 41
D 73
			if (a->q_alias == NULL && !tTd(0, 1) && !QueueRun && !ForceMail)
E 73
I 73
D 90
			if (a->q_alias == NULL && !QueueRun && !ForceMail)
E 90
I 90
			if (a->q_alias == NULL && !ForceMail)
E 90
E 73
I 69
			{
				a->q_flags |= QBADADDR;
E 69
E 41
E 34
E 29
E 21
E 19
				usrerr("Cannot mail directly to :include:s");
I 69
			}
E 69
			else
			{
D 40
				if (Verbose)
					message(Arpa_Info, "including file %s", &a->q_user[9]);
E 40
I 40
				message(Arpa_Info, "including file %s", &a->q_user[9]);
E 40
D 32
				include(&a->q_user[9], " sending", a);
E 32
I 32
D 87
				include(&a->q_user[9], " sending", a, sendq);
E 87
I 87
D 93
				include(&a->q_user[9], FALSE, a, sendq);
E 93
I 93
D 98
				include(&a->q_user[9], FALSE, a, sendq, e);
E 98
I 98
				(void) include(&a->q_user[9], FALSE, a, sendq, e);
E 98
E 93
E 87
E 32
			}
E 102
I 102
D 123
			a->q_flags |= QBADADDR;
E 123
I 123
D 127
			a->q_flags |= QDONTSEND|QBADADDR;
E 127
I 127
			a->q_flags |= QBADADDR;
I 230
			a->q_status = "5.7.1";
E 230
E 127
E 123
D 116
			usrerr("Cannot mail directly to :include:s");
E 116
I 116
			usrerr("550 Cannot mail directly to :include:s");
E 116
E 102
E 18
E 2
		}
		else
I 80
		{
I 118
D 139
			int err;
E 139
I 139
			int ret;
E 139

E 118
D 102
			/* try aliasing */
E 80
D 32
			alias(a);
E 32
I 32
D 93
			alias(a, sendq);
E 93
I 93
			alias(a, sendq, e);
E 93
I 80

# ifdef USERDB
D 84
			/* if not  aliased, look it up in the user database */
E 84
I 84
			/* if not aliased, look it up in the user database */
E 84
D 82
			if (!bitset(QDONTSEND, a->q_flags))
E 82
I 82
			if (!bitset(QDONTSEND|QNOTREMOTE, a->q_flags))
E 82
D 84
				udbexpand(a, sendq);
E 84
I 84
			{
				extern int udbexpand();

D 93
				if (udbexpand(a, sendq) == EX_TEMPFAIL)
E 93
I 93
				if (udbexpand(a, sendq, e) == EX_TEMPFAIL)
E 93
				{
					a->q_flags |= QQUEUEUP;
D 93
					if (CurEnv->e_message == NULL)
						CurEnv->e_message = newstr("Deferred: user database error");
E 93
I 93
					if (e->e_message == NULL)
						e->e_message = newstr("Deferred: user database error");
E 93
# ifdef LOG
					if (LogLevel > 3)
						syslog(LOG_INFO, "%s: deferred: udbexpand",
D 93
							CurEnv->e_id);
E 93
I 93
							e->e_id);
E 93
# endif
					message(Arpa_Info, "queued (user database error)");
					return (a);
				}
			}
E 84
# endif
E 102
I 102
D 108
			message(Arpa_Info, "including file %s", &a->q_user[9]);
			(void) include(&a->q_user[9], FALSE, a, sendq, e);
E 108
I 108
D 116
			message(Arpa_Info, "including file %s", a->q_user);
E 116
I 116
			message("including file %s", a->q_user);
E 116
D 118
			(void) include(a->q_user, FALSE, a, sendq, e);
E 118
I 118
D 139
			err = include(a->q_user, FALSE, a, sendq, e);
			if (transienterror(err))
E 139
I 139
D 200
			ret = include(a->q_user, FALSE, a, sendq, e);
E 200
I 200
			ret = include(a->q_user, FALSE, a, sendq, aliaslevel, e);
E 200
			if (transienterror(ret))
			{
#ifdef LOG
				if (LogLevel > 2)
D 140
					syslog(LOG_NOTICE, "%s: include %s: transient error: %e",
E 140
I 140
D 187
					syslog(LOG_ERR, "%s: include %s: transient error: %e",
E 187
I 187
					syslog(LOG_ERR, "%s: include %s: transient error: %s",
E 187
E 140
D 141
						e->e_id, a->q_user);
E 141
I 141
D 188
						e->e_id, a->q_user, errstring(ret));
E 188
I 188
						e->e_id == NULL ? "NOQUEUE" : e->e_id,
						a->q_user, errstring(ret));
E 188
E 141
#endif
E 139
D 149
				a->q_flags |= QQUEUEUP|QDONTSEND;
E 149
I 149
				a->q_flags |= QQUEUEUP;
I 178
				a->q_flags &= ~QDONTSEND;
E 178
E 149
I 139
				usrerr("451 Cannot open %s: %s",
					a->q_user, errstring(ret));
			}
			else if (ret != 0)
			{
I 152
				a->q_flags |= QBADADDR;
I 230
				a->q_status = "5.2.4";
E 230
E 152
				usrerr("550 Cannot open %s: %s",
					a->q_user, errstring(ret));
D 152
				a->q_flags |= QBADADDR;
E 152
			}
E 139
E 118
E 108
E 102
		}
I 102
D 103
		return (a);
E 103
E 102
E 80
E 32
	}
D 103

D 102
	/*
	**  If the user is local and still being sent, verify that
	**  the address is good.  If it is, try to forward.
	**  If the address is already good, we have a forwarding
	**  loop.  This can be broken by just sending directly to
	**  the user (which is probably correct anyway).
	*/

D 5
	if (!bitset(QDONTSEND, a->q_flags) && a->q_mailer == M_LOCAL)
E 5
I 5
D 28
	if (!bitset(QDONTSEND, a->q_flags) && a->q_mailer == MN_LOCAL)
E 28
I 28
D 46
	if (!bitset(QDONTSEND, a->q_flags) && a->q_mailer == LocalMailer)
E 46
I 46
D 81
	if (!bitset(QDONTSEND, a->q_flags) && m == LocalMailer)
E 81
I 81
	if (bitset(QDONTSEND, a->q_flags) || m != LocalMailer)
		return (a);

	/* see if this is to a file */
	if (buf[0] == '/')
E 102
I 102
	if (m == FileMailer)
E 103
I 103
	else if (m == FileMailer)
E 103
E 102
E 81
E 46
E 28
E 5
	{
D 46
		char buf[MAXNAME];
I 6
		register char *p;
E 46
I 12
D 168
		struct stat stb;
E 168
		extern bool writable();
I 18
D 46
		bool quoted = FALSE;
E 18
E 12
E 6

D 38
		strcpy(buf, a->q_user);
E 38
I 38
		(void) strcpy(buf, a->q_user);
E 38
I 18
		for (p = buf; *p != '\0' && !quoted; p++)
		{
D 30
D 31
			if (!isascii(*p))
E 31
I 31
D 45
			if (!isascii(*p) && (*p & 0377) != (SPACESUB & 0377))
E 45
I 45
			if (!isascii(*p) && (*p & 0377) != (SpaceSub & 0377))
E 45
E 31
E 30
I 30
			if (!isascii(*p) && (*p & 0377) != (SPACESUB) & 0377)
E 30
				quoted = TRUE;
		}
E 18
		stripquotes(buf, TRUE);
E 46

D 81
		/* see if this is to a file */
D 6
		if (index(buf, '/') != NULL)
E 6
I 6
D 35
		if ((p = rindex(buf, '/')) != NULL)
E 35
I 35
		if (buf[0] == '/')
E 81
I 81
D 97
		p = rindex(buf, '/');
E 97
I 97
D 168
		p = strrchr(buf, '/');
E 168
E 97
		/* check if writable or creatable */
D 104
		if (a->q_alias == NULL && !QueueRun && !ForceMail)
E 104
I 104
D 130
		if (a->q_alias == NULL && !QueueRun)
E 130
I 130
D 164
		if (a->q_alias == NULL && !bitset(EF_QUEUERUN, e->e_flags))
E 164
I 164
		if (a->q_alias == NULL)
E 164
E 130
E 104
E 81
E 35
E 6
		{
I 35
D 81
			p = rindex(buf, '/');
E 35
D 6
			if (access(buf, 2) < 0)
E 6
I 6
			/* check if writable or creatable */
D 12
			if ((access(buf, 0) >= 0) ?
			    (access(buf, 2) < 0) :
E 12
I 12
D 18
			if ((stat(buf, &stb) >= 0) ? (!writable(&stb)) :
E 18
I 18
D 19
			if (getctladdr(a) == &From && Debug == 0)
E 19
I 19
D 21
			if (getctladdr(a) == NULL && Debug == 0)
E 21
I 21
D 29
			if (a->q_alias == NULL && Debug == 0)
E 29
I 29
D 34
			if (a->q_alias == NULL && Debug == 0 && !QueueRun)
E 34
I 34
D 41
			if (a->q_alias == NULL && Debug == 0 && !QueueRun && !ForceMail)
E 41
I 41
D 73
			if (a->q_alias == NULL && !tTd(0, 1) && !QueueRun && !ForceMail)
E 73
I 73
			if (a->q_alias == NULL && !QueueRun && !ForceMail)
E 73
E 41
E 34
E 29
E 21
E 19
			{
D 68
				usrerr("Cannot mail directly to files");
E 68
D 69
				a->q_flags |= QDONTSEND;
E 69
I 69
				a->q_flags |= QDONTSEND|QBADADDR;
E 69
I 68
				usrerr("Cannot mail directly to files");
E 68
			}
			else if ((stat(buf, &stb) >= 0) ? (!writable(&stb)) :
E 18
E 12
D 26
			    (*p = '\0', access(buf, 3) < 0))
E 26
I 26
			    (*p = '\0', !safefile(buf, getruid(), S_IWRITE|S_IEXEC)))
E 26
E 6
			{
				a->q_flags |= QBADADDR;
D 50
				giveresponse(EX_CANTCREAT, TRUE, m);
E 50
I 50
D 53
				giveresponse(EX_CANTCREAT, m);
E 53
I 53
				giveresponse(EX_CANTCREAT, m, CurEnv);
E 53
E 50
			}
E 81
I 81
D 127
			a->q_flags |= QDONTSEND|QBADADDR;
E 127
I 127
			a->q_flags |= QBADADDR;
I 230
			a->q_status = "5.7.1";
E 230
E 127
D 116
			usrerr("Cannot mail directly to files");
E 116
I 116
			usrerr("550 Cannot mail directly to files");
E 116
E 81
		}
I 180
		else if (bitset(QBOGUSSHELL, a->q_alias->q_flags))
		{
			a->q_flags |= QBADADDR;
I 230
			a->q_status = "5.7.1";
E 230
			usrerr("550 User %s@%s doesn't have a valid shell for mailing to files",
				a->q_alias->q_ruser, MyHostName);
		}
		else if (bitset(QUNSAFEADDR, a->q_alias->q_flags))
		{
			a->q_flags |= QBADADDR;
I 230
			a->q_status = "5.7.1";
E 230
			usrerr("550 Address %s is unsafe for mailing to files",
				a->q_alias->q_paddr);
		}
E 180
I 81
D 166
		else if ((stat(buf, &stb) >= 0) ? (!writable(&stb)) :
E 166
I 166
D 168
		else if ((stat(buf, &stb) >= 0) ? (!writable(buf, &stb)) :
E 166
D 118
		    (*p = '\0', !safefile(buf, getruid(), S_IWRITE|S_IEXEC)))
E 118
I 118
D 146
		    (*p = '\0', safefile(buf, getruid(), S_IWRITE|S_IEXEC) != 0))
E 146
I 146
D 147
		    (*p = '\0', safefile(buf, getruid(), TRUE, S_IWRITE|S_IEXEC) != 0))
E 147
I 147
D 156
		    (*p = '\0', safefile(buf, RealUid, TRUE, S_IWRITE|S_IEXEC) != 0))
E 156
I 156
		    (*p = '\0', safefile(buf, RealUid, RealGid, NULL, TRUE, S_IWRITE|S_IEXEC) != 0))
E 168
I 168
D 171
		else if (!writable(buf))
E 171
I 171
D 173
		else if (!writable(buf, SFF_ANYFILE))
E 173
I 173
D 220
		else if (!writable(buf, getctladdr(a), SFF_ANYFILE))
E 220
I 220
		else if (!writable(buf, getctladdr(a), SFF_CREAT))
E 220
E 173
E 171
E 168
E 156
E 147
E 146
E 118
		{
D 123
			a->q_flags |= QBADADDR;
E 123
I 123
D 127
			a->q_flags |= QDONTSEND|QBADADDR;
E 127
I 127
			a->q_flags |= QBADADDR;
E 127
E 123
D 93
			giveresponse(EX_CANTCREAT, m, CurEnv);
E 93
I 93
D 122
			giveresponse(EX_CANTCREAT, m, e);
E 122
I 122
D 165
			giveresponse(EX_CANTCREAT, m, NULL, e);
E 165
I 165
D 203
			giveresponse(EX_CANTCREAT, m, NULL, a->q_alias, e);
E 203
I 203
			giveresponse(EX_CANTCREAT, m, NULL, a->q_alias,
				     (time_t) 0, e);
E 203
E 165
E 122
E 93
		}
D 103
		return (a);
E 103
	}
I 102

D 190
	if (m != LocalMailer)
I 103
	{
		if (!bitset(QDONTSEND, a->q_flags))
			e->e_nrcpts++;
E 103
D 148
		return (a);
E 148
I 148
		goto testselfdestruct;
E 148
I 103
	}
E 103

E 190
	/* try aliasing */
D 190
	alias(a, sendq, e);
E 190
I 190
D 246
	if (!bitset(QDONTSEND, a->q_flags) && bitnset(M_ALIASABLE, m->m_flags))
E 246
I 246
	if (!quoted && !bitset(QDONTSEND, a->q_flags) &&
	    bitnset(M_ALIASABLE, m->m_flags))
E 246
D 200
		alias(a, sendq, e);
E 200
I 200
		alias(a, sendq, aliaslevel, e);
E 200
E 190

D 240
# ifdef USERDB
E 240
I 240
# if USERDB
E 240
	/* if not aliased, look it up in the user database */
D 135
	if (!bitset(QDONTSEND|QNOTREMOTE, a->q_flags))
E 135
I 135
D 190
	if (!bitset(QDONTSEND|QNOTREMOTE|QVERIFIED, a->q_flags))
E 190
I 190
	if (!bitset(QDONTSEND|QNOTREMOTE|QVERIFIED, a->q_flags) &&
	    bitnset(M_CHECKUDB, m->m_flags))
E 190
E 135
	{
		extern int udbexpand();
I 140
D 166
		extern int errno;
E 166
E 140

D 200
		if (udbexpand(a, sendq, e) == EX_TEMPFAIL)
E 200
I 200
		if (udbexpand(a, sendq, aliaslevel, e) == EX_TEMPFAIL)
E 200
		{
D 118
			a->q_flags |= QQUEUEUP;
E 118
I 118
D 149
			a->q_flags |= QQUEUEUP|QDONTSEND;
E 149
I 149
			a->q_flags |= QQUEUEUP;
E 149
E 118
			if (e->e_message == NULL)
				e->e_message = newstr("Deferred: user database error");
# ifdef LOG
D 109
			if (LogLevel > 3)
E 109
I 109
			if (LogLevel > 8)
E 109
D 140
				syslog(LOG_INFO, "%s: deferred: udbexpand",
E 140
I 140
D 141
				syslog(LOG_INFO, "%s: deferred: udbexpand: %e",
E 140
					e->e_id);
E 141
I 141
				syslog(LOG_INFO, "%s: deferred: udbexpand: %s",
D 188
					e->e_id, errstring(errno));
E 188
I 188
					e->e_id == NULL ? "NOQUEUE" : e->e_id,
					errstring(errno));
E 188
E 141
# endif
D 116
			message(Arpa_Info, "queued (user database error)");
E 116
I 116
D 140
			message("queued (user database error)");
E 140
I 140
			message("queued (user database error): %s",
				errstring(errno));
E 140
E 116
I 103
			e->e_nrcpts++;
E 103
D 148
			return (a);
E 148
I 148
			goto testselfdestruct;
E 148
		}
	}
# endif

D 190
	/* if it was an alias or a UDB expansion, just return now */
D 117
	if (bitset(QDONTSEND, a->q_flags))
E 117
I 117
D 118
	if (bitset(QDONTSEND|QVERIFIED, a->q_flags))
E 118
I 118
	if (bitset(QDONTSEND|QQUEUEUP|QVERIFIED, a->q_flags))
E 118
E 117
D 148
		return (a);
E 148
I 148
		goto testselfdestruct;
E 148
E 102

E 190
	/*
	**  If we have a level two config file, then pass the name through
	**  Ruleset 5 before sending it off.  Ruleset 5 has the right
	**  to send rewrite it to another mailer.  This gives us a hook
	**  after local aliasing has been done.
	*/

	if (tTd(29, 5))
	{
		printf("recipient: testing local?  cl=%d, rr5=%x\n\t",
			ConfigLevel, RewriteRules[5]);
		printaddr(a, FALSE);
	}
D 190
	if (!bitset(QNOTREMOTE, a->q_flags) && ConfigLevel >= 2 &&
	    RewriteRules[5] != NULL)
E 190
I 190
	if (!bitset(QNOTREMOTE|QDONTSEND|QQUEUEUP|QVERIFIED, a->q_flags) &&
	    ConfigLevel >= 2 && RewriteRules[5] != NULL &&
	    bitnset(M_TRYRULESET5, m->m_flags))
E 190
	{
D 93
		maplocaluser(a, sendq);
E 93
I 93
D 200
		maplocaluser(a, sendq, e);
E 200
I 200
D 225
		maplocaluser(a, sendq, aliaslevel, e);
E 225
I 225
		maplocaluser(a, sendq, aliaslevel + 1, e);
E 225
E 200
E 93
	}

	/*
	**  If it didn't get rewritten to another mailer, go ahead
	**  and deliver it.
	*/

D 118
	if (!bitset(QDONTSEND, a->q_flags))
E 118
I 118
D 190
	if (!bitset(QDONTSEND|QQUEUEUP, a->q_flags))
E 190
I 190
	if (!bitset(QDONTSEND|QQUEUEUP|QVERIFIED, a->q_flags) &&
	    bitnset(M_HASPWENT, m->m_flags))
E 190
E 118
	{
I 94
		auto bool fuzzy;
E 94
		register struct passwd *pw;
		extern struct passwd *finduser();

		/* warning -- finduser may trash buf */
D 94
		pw = finduser(buf);
E 94
I 94
		pw = finduser(buf, &fuzzy);
E 94
		if (pw == NULL)
		{
D 123
			a->q_flags |= QBADADDR;
E 123
I 123
D 127
			a->q_flags |= QDONTSEND|QBADADDR;
E 127
I 127
			a->q_flags |= QBADADDR;
I 230
			a->q_status = "5.1.1";
E 230
E 127
E 123
D 93
			giveresponse(EX_NOUSER, m, CurEnv);
E 93
I 93
D 122
			giveresponse(EX_NOUSER, m, e);
E 122
I 122
D 165
			giveresponse(EX_NOUSER, m, NULL, e);
E 165
I 165
D 203
			giveresponse(EX_NOUSER, m, NULL, a->q_alias, e);
E 203
I 203
			giveresponse(EX_NOUSER, m, NULL, a->q_alias,
				     (time_t) 0, e);
E 203
E 165
E 122
E 93
		}
E 81
		else
		{
D 81
			register struct passwd *pw;
D 14
			extern struct passwd *getpwnam();
			pw = getpwnam(buf);
E 14
I 14
			extern struct passwd *finduser();
E 81
I 81
D 222
			char nbuf[MAXNAME];
E 222
I 222
			char nbuf[MAXNAME + 1];
E 222
E 81

I 22
D 81
			/* warning -- finduser may trash buf */
E 22
			pw = finduser(buf);
E 14
			if (pw == NULL)
E 81
I 81
D 94
			if (strcmp(a->q_user, pw->pw_name) != 0)
E 94
I 94
			if (fuzzy)
E 94
E 81
			{
I 88
				/* name was a fuzzy match */
E 88
D 81
				a->q_flags |= QBADADDR;
D 50
				giveresponse(EX_NOUSER, TRUE, m);
E 50
I 50
D 53
				giveresponse(EX_NOUSER, m);
E 53
I 53
				giveresponse(EX_NOUSER, m, CurEnv);
E 81
I 81
				a->q_user = newstr(pw->pw_name);
I 88
				if (findusercount++ > 3)
				{
I 123
D 127
					a->q_flags |= QDONTSEND|QBADADDR;
E 127
I 127
					a->q_flags |= QBADADDR;
I 230
					a->q_status = "5.4.6";
E 230
E 127
E 123
D 116
					usrerr("aliasing/forwarding loop for %s broken",
E 116
I 116
					usrerr("554 aliasing/forwarding loop for %s broken",
E 116
						pw->pw_name);
D 189
					return (a);
E 189
I 189
					goto done;
E 189
				}

				/* see if it aliases */
E 88
				(void) strcpy(buf, pw->pw_name);
I 88
				goto trylocaluser;
E 88
E 81
E 53
E 50
			}
D 81
			else
			{
I 31
				char nbuf[MAXNAME];

E 31
I 30
				char nbuf[MAXNAME];

E 30
I 15
				if (strcmp(a->q_user, pw->pw_name) != 0)
				{
					a->q_user = newstr(pw->pw_name);
D 38
					strcpy(buf, pw->pw_name);
E 38
I 38
					(void) strcpy(buf, pw->pw_name);
E 38
				}
E 15
				a->q_home = newstr(pw->pw_dir);
I 7
				a->q_uid = pw->pw_uid;
E 7
D 18
				if (strcmp(buf, a->q_user) == 0)
E 18
I 18
				a->q_gid = pw->pw_gid;
I 20
				a->q_flags |= QGOODUID;
I 31
				buildfname(pw->pw_gecos, pw->pw_name, nbuf);
				if (nbuf[0] != '\0')
					a->q_fullname = newstr(nbuf);
E 31
I 30
				fullname(pw, nbuf);
				if (nbuf[0] != '\0')
					a->q_fullname = newstr(nbuf);
E 30
E 20
				if (!quoted)
E 18
D 32
					forward(a);
E 32
I 32
					forward(a, sendq);
E 32
			}
E 81
I 81
D 184
			a->q_home = newstr(pw->pw_dir);
E 184
I 184
			if (strcmp(pw->pw_dir, "/") == 0)
				a->q_home = "";
			else
				a->q_home = newstr(pw->pw_dir);
E 184
			a->q_uid = pw->pw_uid;
			a->q_gid = pw->pw_gid;
I 137
			a->q_ruser = newstr(pw->pw_name);
E 137
			a->q_flags |= QGOODUID;
			buildfname(pw->pw_gecos, pw->pw_name, nbuf);
			if (nbuf[0] != '\0')
				a->q_fullname = newstr(nbuf);
I 175
D 176
#ifndef NEEDGETUSERSHELL
E 176
D 177
			if (pw->pw_shell != NULL && pw->pw_shell[0] != '\0')
E 177
I 177
D 244
			if (pw->pw_shell != NULL && pw->pw_shell[0] != '\0' &&
			    !usershellok(pw->pw_shell))
E 244
I 244
			if (!usershellok(pw->pw_name, pw->pw_shell))
E 244
E 177
			{
D 177
				extern char *getusershell();

				setusershell();
				while ((p = getusershell()) != NULL)
					if (strcmp(p, pw->pw_shell) == 0)
						break;
				endusershell();
				if (p == NULL)
					a->q_flags |= QBOGUSSHELL;
E 177
I 177
				a->q_flags |= QBOGUSSHELL;
E 177
			}
D 176
#endif
E 176
E 175
D 237
			if (!quoted)
E 237
I 237
			if (bitset(EF_VRFYONLY, e->e_flags))
			{
				/* don't do any more now */
				a->q_flags |= QVERIFIED;
			}
			else if (!quoted)
E 237
D 93
				forward(a, sendq);
E 93
I 93
D 200
				forward(a, sendq, e);
E 200
I 200
				forward(a, sendq, aliaslevel, e);
E 200
E 93
E 81
		}
	}
I 103
	if (!bitset(QDONTSEND, a->q_flags))
		e->e_nrcpts++;
I 148

  testselfdestruct:
I 225
	a->q_flags |= QTHISPASS;
E 225
D 154
	if (a->q_alias == NULL && a != &e->e_from)
E 154
I 154
	if (tTd(26, 8))
E 154
	{
D 154
		q = a->q_next;
E 154
I 154
		printf("testselfdestruct: ");
D 225
		printaddr(a, TRUE);
E 225
I 225
		printaddr(a, FALSE);
		if (tTd(26, 10))
		{
			printf("SENDQ:\n");
			printaddr(*sendq, TRUE);
			printf("----\n");
		}
E 225
	}
	if (a->q_alias == NULL && a != &e->e_from &&
	    bitset(QDONTSEND, a->q_flags))
	{
D 225
		q = *sendq;
E 154
D 153
		while (q != NULL && bitset(QDONTSEND|QBADADDR, q->q_flags))
E 153
I 153
		while (q != NULL && bitset(QDONTSEND, q->q_flags))
E 153
			q = q->q_next;
E 225
I 225
		for (q = *sendq; q != NULL; q = q->q_next)
		{
D 245
			if (!bitset(QDONTSEND|QBADADDR, q->q_flags) &&
E 245
I 245
			if (!bitset(QDONTSEND, q->q_flags) &&
E 245
			    bitset(QTHISPASS, q->q_flags))
				break;
		}
E 225
D 152
		if (bitset(QDONTSEND|QBADADDR, a->q_flags) && q == NULL)
E 152
I 152
D 154
		if (bitset(QDONTSEND, a->q_flags) && q == NULL)
E 154
I 154
		if (q == NULL)
E 154
E 152
		{
			a->q_flags |= QBADADDR;
I 230
D 231
			a->q_flags = "5.4.6";
E 231
I 231
			a->q_status = "5.4.6";
E 231
E 230
			usrerr("554 aliasing/forwarding loop broken");
		}
	}
I 189

  done:
I 225
	a->q_flags |= QTHISPASS;
E 225
	if (buf != buf0)
		free(buf);
I 225

	/*
	**  If we are at the top level, check to see if this has
	**  expanded to exactly one address.  If so, it can inherit
	**  the primaryness of the address.
	**
	**  While we're at it, clear the QTHISPASS bits.
	*/

	if (aliaslevel == 0)
	{
		int nrcpts = 0;
		ADDRESS *only;

		for (q = *sendq; q != NULL; q = q->q_next)
		{
			if (bitset(QTHISPASS, q->q_flags) &&
			    !bitset(QDONTSEND|QBADADDR, q->q_flags))
			{
				nrcpts++;
				only = q;
			}
			q->q_flags &= ~QTHISPASS;
		}
		if (nrcpts == 1)
D 232
			only->q_flags |= QPRIMARY;
		else if (!initialdontsend)
E 232
		{
I 232
			/* check to see if this actually got a new owner */
			q = only;
			while ((q = q->q_alias) != NULL)
			{
				if (q->q_owner != NULL)
					break;
			}
			if (q == NULL)
				only->q_flags |= QPRIMARY;
		}
		else if (!initialdontsend && nrcpts > 0)
		{
E 232
			/* arrange for return receipt */
			e->e_flags |= EF_SENDRECEIPT;
D 232
			a->q_flags |= QEXPLODED;
E 232
I 232
			a->q_flags |= QEXPANDED;
E 232
			if (e->e_xfp != NULL)
				fprintf(e->e_xfp,
					"%s... expanded to multiple addresses\n",
					a->q_paddr);
		}
	}

E 225
E 189
E 148
E 103
I 55
	return (a);
E 55
I 30

	return (a);
E 30
I 14
}
/*
**  FINDUSER -- find the password entry for a user.
**
**	This looks a lot like getpwnam, except that it may want to
**	do some fancier pattern matching in /etc/passwd.
**
I 50
**	This routine contains most of the time of many sendmail runs.
**	It deserves to be optimized.
**
E 50
**	Parameters:
**		name -- the name to match against.
I 94
**		fuzzyp -- an outarg that is set to TRUE if this entry
**			was found using the fuzzy matching algorithm;
**			set to FALSE otherwise.
E 94
**
**	Returns:
**		A pointer to a pw struct.
**		NULL if name is unknown or ambiguous.
**
**	Side Effects:
D 22
**		none.
E 22
I 22
**		may modify name.
E 22
*/

struct passwd *
D 94
finduser(name)
E 94
I 94
finduser(name, fuzzyp)
E 94
	char *name;
I 94
	bool *fuzzyp;
E 94
{
D 15
	extern struct passwd *getpwnam();
E 15
I 15
D 58
	extern struct passwd *getpwent();
E 58
	register struct passwd *pw;
I 22
	register char *p;
I 58
D 226
	extern struct passwd *getpwent();
	extern struct passwd *getpwnam();
E 226
E 58
E 22
E 15

I 94
	if (tTd(29, 4))
		printf("finduser(%s): ", name);

E 94
I 22
D 67
	/*
	**  Make name canonical.
	*/

E 67
I 67
D 131
	/* map upper => lower case */
E 67
	for (p = name; *p != '\0'; p++)
	{
D 45
		if (*p == (SPACESUB & 0177) || *p == '_')
E 45
I 45
D 67
		if (*p == (SpaceSub & 0177) || *p == '_')
E 45
			*p = ' ';
I 65
D 66
		else if (ischar(*p) && isupper(*p))
E 66
I 66
		else if (isascii(*p) && isupper(*p))
E 67
I 67
		if (isascii(*p) && isupper(*p))
E 67
E 66
			*p = tolower(*p);
E 65
	}
E 131
I 94
	*fuzzyp = FALSE;
E 94

I 194
#ifdef HESIOD
E 194
I 163
	/* DEC Hesiod getpwnam accepts numeric strings -- short circuit it */
	for (p = name; *p != '\0'; p++)
		if (!isascii(*p) || !isdigit(*p))
			break;
	if (*p == '\0')
	{
		if (tTd(29, 4))
			printf("failed (numeric input)\n");
		return NULL;
	}
I 194
#endif
E 194

E 163
I 56
D 67
	/* look up this login name */
E 67
I 67
	/* look up this login name using fast path */
E 67
D 226
	if ((pw = getpwnam(name)) != NULL)
E 226
I 226
	if ((pw = sm_getpwnam(name)) != NULL)
E 226
I 94
	{
		if (tTd(29, 4))
			printf("found (non-fuzzy)\n");
E 94
		return (pw);
I 94
	}
E 94

I 88
D 243
#ifdef MATCHGECOS
E 243
I 243
#if MATCHGECOS
E 243
	/* see if fuzzy matching allowed */
	if (!MatchGecos)
I 94
	{
		if (tTd(29, 4))
			printf("not found (fuzzy disabled)\n");
E 94
		return NULL;
I 94
	}
E 94

E 88
	/* search for a matching full name instead */
I 67
	for (p = name; *p != '\0'; p++)
	{
		if (*p == (SpaceSub & 0177) || *p == '_')
			*p = ' ';
	}
E 67
E 56
E 22
D 15
	return (getpwnam(name));
E 15
I 15
D 63
	setpwent();
E 63
I 63
	(void) setpwent();
E 63
	while ((pw = getpwent()) != NULL)
	{
D 30
D 222
		char buf[MAXNAME];
E 222
I 222
		char buf[MAXNAME + 1];
E 222
E 30
D 22
		register char *p;
E 22
D 70
		extern bool sameword();
E 70
I 30
		char buf[MAXNAME];
E 30
I 17
D 22
		bool gotaspace;
E 22
E 17

D 67
		if (strcmp(pw->pw_name, name) == 0)
			return (pw);
E 67
D 30
		buildfname(pw->pw_gecos, pw->pw_name, buf);
E 30
I 30
		fullname(pw, buf);
E 30
I 17
D 22
		gotaspace = FALSE;
E 17
		for (p = buf; (p = index(p, ' ')) != NULL; )
I 17
		{
E 17
			*p++ = SPACESUB & 0177;
D 17
		if (sameword(buf, name))
E 17
I 17
			gotaspace = TRUE;
		}
		if (gotaspace && sameword(buf, name))
E 22
I 22
D 70
		if (index(buf, ' ') != NULL && sameword(buf, name))
E 70
I 70
D 97
		if (index(buf, ' ') != NULL && !strcasecmp(buf, name))
E 97
I 97
		if (strchr(buf, ' ') != NULL && !strcasecmp(buf, name))
E 97
E 70
E 22
E 17
I 16
		{
I 94
			if (tTd(29, 4))
				printf("fuzzy matches %s\n", pw->pw_name);
E 94
D 40
			if (Verbose)
D 17
				message(Arpa_Info, "sending to login name %s", pw->pw_name);
E 17
I 17
D 30
				message(Arpa_Info, "sending to login name %s",
				    pw->pw_name);
E 40
I 40
D 116
			message(Arpa_Info, "sending to login name %s", pw->pw_name);
E 116
I 116
			message("sending to login name %s", pw->pw_name);
E 116
I 94
			*fuzzyp = TRUE;
E 94
E 40
E 30
I 30
				message(Arpa_Info, "sending to %s <%s>",
				    buf, pw->pw_name);
E 30
E 17
E 16
			return (pw);
I 16
		}
E 16
	}
I 88
D 136
#endif
E 136
I 94
	if (tTd(29, 4))
		printf("no fuzzy match found\n");
I 136
#else
	if (tTd(29, 4))
		printf("not found (fuzzy disabled)\n");
#endif
E 136
E 94
E 88
	return (NULL);
E 15
E 14
I 12
}
/*
**  WRITABLE -- predicate returning if the file is writable.
**
**	This routine must duplicate the algorithm in sys/fio.c.
**	Unfortunately, we cannot use the access call since we
**	won't necessarily be the real uid when we try to
**	actually open the file.
**
**	Notice that ANY file with ANY execute bit is automatically
**	not writable.  This is also enforced by mailfile.
**
**	Parameters:
D 171
**		s -- pointer to a stat struct for the file.
E 171
I 171
**		filename -- the file name to check.
I 173
**		ctladdr -- the controlling address for this file.
E 173
**		flags -- SFF_* flags to control the function.
E 171
**
**	Returns:
**		TRUE -- if we will be able to write this file.
**		FALSE -- if we cannot write this file.
**
**	Side Effects:
**		none.
*/

bool
D 166
writable(s)
E 166
I 166
D 168
writable(filename, s)
E 168
I 168
D 171
writable(filename)
E 171
I 171
D 173
writable(filename, flags)
E 173
I 173
writable(filename, ctladdr, flags)
E 173
E 171
E 168
	char *filename;
I 173
	ADDRESS *ctladdr;
E 173
I 171
	int flags;
E 171
E 166
D 168
	register struct stat *s;
E 168
{
D 95
	int euid, egid;
E 95
I 95
	uid_t euid;
	gid_t egid;
E 95
D 241
	int bits;
I 168
	register char *p;
E 241
	char *uname;
D 220
	struct stat stb;
	extern char RealUserName[];
E 220
E 168

I 166
	if (tTd(29, 5))
D 168
		printf("writable(%s) mode=%o\n", filename, s->st_mode);
E 166
	if (bitset(0111, s->st_mode))
E 168
I 168
D 171
		printf("writable(%s)\n", filename);
E 171
I 171
D 228
		printf("writable(%s, %x)\n", filename, flags);
E 228
I 228
		printf("writable(%s, 0x%x)\n", filename, flags);
E 228
E 171

D 220
#ifdef HASLSTAT
D 171
	if (lstat(filename, &stb) < 0)
E 171
I 171
	if ((bitset(SFF_NOSLINK, flags) ? lstat(filename, &stb)
					: stat(filename, &stb)) < 0)
E 171
#else
	if (stat(filename, &stb) < 0)
#endif
	{
		/* file does not exist -- see if directory is safe */
		p = strrchr(filename, '/');
		if (p == NULL)
D 172
			return FALSE;
		*p = '\0';
		if (safefile(filename, RealUid, RealGid, RealUserName,
D 171
			     SF_MUSTOWN, S_IWRITE|S_IEXEC) != 0)
E 171
I 171
			     SFF_MUSTOWN, S_IWRITE|S_IEXEC) != 0)
E 172
E 171
		{
D 172
			*p = '/';
E 172
I 172
			errno = ENOTDIR;
E 172
			return FALSE;
		}
I 172
		*p = '\0';
		errno = safefile(filename, RealUid, RealGid, RealUserName,
				 SFF_MUSTOWN, S_IWRITE|S_IEXEC);
E 172
		*p = '/';
I 170
D 172
		return TRUE;
E 172
I 172
		return errno == 0;
E 172
E 170
	}

E 220
I 179
D 247
#ifdef SUID_ROOT_FILES_OK
	/* really ought to be passed down -- and not a good idea */
	flags |= SFF_ROOTOK;
#endif

E 247
E 179
	/*
	**  File does exist -- check that it is writable.
	*/

D 220
	if (bitset(0111, stb.st_mode))
I 170
	{
		if (tTd(29, 5))
			printf("failed (mode %o: x bits)\n", stb.st_mode);
I 172
		errno = EPERM;
E 172
E 170
E 168
		return (FALSE);
I 170
	}
E 170
I 168

E 220
E 168
D 147
	euid = getruid();
	egid = getrgid();
E 147
I 147
D 173
	euid = RealUid;
I 168
	uname = RealUserName;
	if (euid == 0)
E 173
I 173
	if (ctladdr != NULL && geteuid() == 0)
E 173
	{
D 173
		euid = DefUid;
		uname = DefUser;
E 173
I 173
		euid = ctladdr->q_uid;
		egid = ctladdr->q_gid;
		uname = ctladdr->q_user;
E 173
	}
I 197
D 228
#ifdef RUN_AS_REAL_UID
E 197
E 168
D 173
	egid = RealGid;
I 168
	if (egid == 0)
		egid = DefGid;
E 173
I 173
	else
E 228
I 228
	else if (bitset(SFF_RUNASREALUID, flags))
E 228
	{
I 220
D 242
		extern char RealUserName[];

E 242
E 220
		euid = RealUid;
		egid = RealGid;
		uname = RealUserName;
	}
I 197
D 228
#else
E 228
D 247
	else if (FileMailer != NULL)
E 247
I 247
	else if (FileMailer != NULL && !bitset(SFF_ROOTOK, flags))
E 247
	{
		euid = FileMailer->m_uid;
		egid = FileMailer->m_gid;
I 241
		uname = NULL;
E 241
	}
	else
	{
		euid = egid = 0;
I 241
		uname = NULL;
E 241
	}
D 228
#endif
E 228
E 197
I 174
D 247
	if (euid == 0)
E 247
I 247
	if (!bitset(SFF_ROOTOK, flags))
E 247
	{
D 247
		euid = DefUid;
		uname = DefUser;
E 247
I 247
		if (euid == 0)
		{
			euid = DefUid;
			uname = DefUser;
		}
		if (egid == 0)
			egid = DefGid;
E 247
	}
D 247
	if (egid == 0)
		egid = DefGid;
E 247
E 174
E 173
E 168
E 147
	if (geteuid() == 0)
D 220
	{
I 174
D 179
#ifdef SUID_ROOT_FILES_OK
E 174
D 168
		if (bitset(S_ISUID, s->st_mode))
			euid = s->st_uid;
		if (bitset(S_ISGID, s->st_mode))
			egid = s->st_gid;
E 168
I 168
		if (bitset(S_ISUID, stb.st_mode))
I 174
#else
		if (bitset(S_ISUID, stb.st_mode) && stb.st_uid != 0)
#endif
E 179
I 179
		if (bitset(S_ISUID, stb.st_mode) &&
		    (stb.st_uid != 0 || bitset(SFF_ROOTOK, flags)))
E 179
E 174
		{
I 174
D 179
			flags |= SFF_ROOTOK;
E 179
E 174
			euid = stb.st_uid;
			uname = NULL;
		}
D 174
		if (bitset(S_ISGID, stb.st_mode))
E 174
I 174
D 179
		if (bitset(S_ISGID, stb.st_mode) && stb.st_gid != 0)
E 179
I 179
		if (bitset(S_ISGID, stb.st_mode) &&
		    (stb.st_gid != 0 || bitset(SFF_ROOTOK, flags)))
E 179
E 174
			egid = stb.st_gid;
E 168
	}
E 220
I 220
		flags |= SFF_SETUIDOK;
E 220
I 173
D 174
	if (euid == 0)
	{
		euid = DefUid;
		uname = DefUser;
	}
	if (egid == 0)
		egid = DefGid;
	
E 174
E 173
I 166

D 220
	if (tTd(29, 5))
		printf("\teu/gid=%d/%d, st_u/gid=%d/%d\n",
D 168
			euid, egid, s->st_uid, s->st_gid);
E 168
I 168
			euid, egid, stb.st_uid, stb.st_gid);
E 168
E 166

D 168
	if (euid == 0)
		return (TRUE);
	bits = S_IWRITE;
	if (euid != s->st_uid)
	{
		bits >>= 3;
		if (egid != s->st_gid)
			bits >>= 3;
	}
	return ((s->st_mode & bits) != 0);
E 168
I 168
D 169
	return safefile(filename, euid, egid, uname, SF_NOSLINK, S_IWRITE);
E 169
I 169
D 171
	return safefile(filename, euid, egid, uname, SF_NOSLINK, S_IWRITE) == 0;
E 171
I 171
D 172
	return safefile(filename, euid, egid, uname, flags, S_IWRITE) == 0;
E 172
I 172
	errno = safefile(filename, euid, egid, uname, flags, S_IWRITE);
E 220
I 220
	errno = safefile(filename, euid, egid, uname, flags, S_IWRITE, NULL);
E 220
	return errno == 0;
E 172
E 171
E 169
E 168
E 12
}
/*
**  INCLUDE -- handle :include: specification.
**
**	Parameters:
**		fname -- filename to include.
I 2
D 87
**		msg -- message to print in verbose mode.
E 87
I 87
**		forwarding -- if TRUE, we are reading a .forward file.
**			if FALSE, it's a :include: file.
E 87
I 18
**		ctladdr -- address template to use to fill in these
**			addresses -- effective user/group id are
**			the important things.
I 32
**		sendq -- a pointer to the head of the send queue
**			to put these addresses in.
I 200
**		aliaslevel -- the alias nesting depth.
**		e -- the current envelope.
E 200
E 32
E 18
E 2
**
**	Returns:
D 98
**		none.
E 98
I 98
**		open error status
E 98
**
**	Side Effects:
**		reads the :include: file and sends to everyone
**		listed in that file.
I 185
**
**	Security Note:
**		If you have restricted chown (that is, you can't
**		give a file away), it is reasonable to allow programs
**		and files called from this :include: file to be to be
**		run as the owner of the :include: file.  This is bogus
**		if there is any chance of someone giving away a file.
**		We assume that pre-POSIX systems can give away files.
**
**		There is an additional restriction that if you
**		forward to a :include: file, it will not take on
**		the ownership of the :include: file.  This may not
**		be necessary, but shouldn't hurt.
E 185
*/

D 2
include(fname)
E 2
I 2
D 18
include(fname, msg)
E 18
I 18
D 32
include(fname, msg, ctladdr)
E 32
I 32
D 87
include(fname, msg, ctladdr, sendq)
E 87
I 87
static jmp_buf	CtxIncludeTimeout;
I 151
D 215
static int	includetimeout();
E 215
I 215
static void	includetimeout();
E 215
E 151

I 180
D 220
#ifndef S_IWOTH
# define S_IWOTH	(S_IWRITE >> 6)
#endif

E 220
E 180
I 98
int
E 98
D 93
include(fname, forwarding, ctladdr, sendq)
E 93
I 93
D 200
include(fname, forwarding, ctladdr, sendq, e)
E 200
I 200
include(fname, forwarding, ctladdr, sendq, aliaslevel, e)
E 200
E 93
E 87
E 32
E 18
E 2
	char *fname;
I 2
D 87
	char *msg;
E 87
I 87
	bool forwarding;
E 87
I 18
	ADDRESS *ctladdr;
I 32
	ADDRESS **sendq;
I 200
	int aliaslevel;
E 200
I 93
	ENVELOPE *e;
E 93
E 32
E 18
E 2
{
D 87
	char buf[MAXLINE];
E 87
D 162
	register FILE *fp;
E 162
I 162
D 215
	register FILE *fp = NULL;
E 215
I 215
	FILE *fp = NULL;
E 215
E 162
I 3
D 37
	char *oldto = To;
E 37
I 37
D 93
	char *oldto = CurEnv->e_to;
E 93
I 93
	char *oldto = e->e_to;
E 93
I 50
	char *oldfilename = FileName;
	int oldlinenumber = LineNumber;
I 87
	register EVENT *ev = NULL;
I 113
	int nincludes;
I 118
D 161
	int ret;
E 161
I 144
D 160
	ADDRESS *ca;
	uid_t uid;
I 156
	gid_t gid;
E 160
I 160
	register ADDRESS *ca;
	uid_t saveduid, uid;
	gid_t savedgid, gid;
E 160
	char *uname;
I 160
	int rval = 0;
I 168
D 171
	int sfflags = forwarding ? SF_MUSTOWN : 0;
E 171
I 171
D 221
	int sfflags = forwarding ? SFF_MUSTOWN : SFF_ANYFILE;
E 221
I 221
	int sfflags = SFF_REGONLY;
E 221
I 180
	struct stat st;
I 186
	char buf[MAXLINE];
E 186
I 185
#ifdef _POSIX_CHOWN_RESTRICTED
I 186
# if _POSIX_CHOWN_RESTRICTED == -1
#  define safechown	FALSE
# else
#  define safechown	TRUE
# endif
#else
# ifdef _PC_CHOWN_RESTRICTED
E 186
	bool safechown;
I 186
# else
#  ifdef BSD
#   define safechown	TRUE
#  else
#   define safechown	FALSE
#  endif
# endif
E 186
#endif
E 185
E 180
E 171
E 168
E 160
E 156
E 144
E 118
E 113
D 186
	char buf[MAXLINE];
E 186
I 186
	extern bool chownsafe();
E 186
D 151
	static int includetimeout();
E 151
E 87
E 50
E 37
I 20
D 21
	struct stat st;
E 21
E 20
E 3

I 100
	if (tTd(27, 2))
		printf("include(%s)\n", fname);
I 150
	if (tTd(27, 4))
		printf("   ruid=%d euid=%d\n", getuid(), geteuid());
E 150
I 144
	if (tTd(27, 14))
	{
		printf("ctladdr ");
		printaddr(ctladdr, FALSE);
	}
E 144

E 100
I 87
D 160
	/*
	**  If home directory is remote mounted but server is down,
	**  this can hang or give errors; use a timeout to avoid this
	*/
E 160
I 160
	if (tTd(27, 9))
		printf("include: old uid = %d/%d\n", getuid(), geteuid());
I 221

	if (forwarding)
D 233
		sfflags |= SFF_MUSTOWN;
E 233
I 233
		sfflags |= SFF_MUSTOWN|SFF_ROOTOK|SFF_NOSLINK;
E 233
E 221
E 160

I 144
	ca = getctladdr(ctladdr);
	if (ca == NULL)
I 156
	{
E 156
D 167
		uid = 0;
I 156
		gid = 0;
		uname = NULL;
E 167
I 167
		uid = DefUid;
		gid = DefGid;
		uname = DefUser;
E 167
I 160
D 209
		saveduid = -1;
E 209
E 160
	}
E 156
	else
I 156
	{
E 156
		uid = ca->q_uid;
I 156
		gid = ca->q_gid;
		uname = ca->q_user;
I 209
	}
E 209
I 160
D 239
#ifdef HASSETREUID
E 239
I 239
#if HASSETREUID || USESETEUID
E 239
D 209
		saveduid = geteuid();
		savedgid = getegid();
		if (saveduid == 0)
E 209
I 209
	saveduid = geteuid();
	savedgid = getegid();
	if (saveduid == 0)
	{
		initgroups(uname, gid);
		if (uid != 0)
E 209
		{
I 239
# if USESETEUID
			if (seteuid(uid) < 0)
				syserr("seteuid(%d) failure (real=%d, eff=%d)",
					uid, getuid(), geteuid());
# else
E 239
D 209
			initgroups(uname, gid);
			if (uid != 0)
D 193
				(void) setreuid(0, uid);
E 193
I 193
			{
				if (setreuid(0, uid) < 0)
					syserr("setreuid(0, %d) failure (real=%d, eff=%d)",
						uid, getuid(), geteuid());
I 208
				else
					sfflags |= SFF_NOPATHCHECK;
E 208
			}
E 209
I 209
			if (setreuid(0, uid) < 0)
				syserr("setreuid(0, %d) failure (real=%d, eff=%d)",
					uid, getuid(), geteuid());
I 239
# endif
E 239
			else
				sfflags |= SFF_NOPATHCHECK;
E 209
E 193
		}
D 209
#endif                   
E 209
E 160
	}
I 209
D 234
#endif                   
E 234
I 234
#endif
E 234
E 209
E 156

I 160
	if (tTd(27, 9))
		printf("include: new uid = %d/%d\n", getuid(), geteuid());

	/*
	**  If home directory is remote mounted but server is down,
	**  this can hang or give errors; use a timeout to avoid this
	*/

E 160
E 144
	if (setjmp(CtxIncludeTimeout) != 0)
	{
D 149
		ctladdr->q_flags |= QQUEUEUP|QDONTSEND;
E 149
I 149
		ctladdr->q_flags |= QQUEUEUP;
E 149
		errno = 0;
D 183
		usrerr("451 open timeout on %s", fname);
E 183
D 98
		return;
E 98
I 98
D 155
		return ETIMEDOUT;
E 155
I 155

		/* return pseudo-error code */
D 160
		return EOPENTIMEOUT;
E 160
I 160
		rval = EOPENTIMEOUT;
		goto resetuid;
E 160
E 155
E 98
	}
D 191
	ev = setevent((time_t) 60, includetimeout, 0);
E 191
I 191
	if (TimeOuts.to_fileopen > 0)
		ev = setevent(TimeOuts.to_fileopen, includetimeout, 0);
	else
		ev = NULL;
E 191

D 144
	/* if forwarding, the input file must be marked safe */
D 118
	if (forwarding && !safefile(fname, ctladdr->q_uid, S_IREAD))
E 118
I 118
	if (forwarding && (ret = safefile(fname, ctladdr->q_uid, S_IREAD)) != 0)
E 144
I 144
	/* the input file must be marked safe */
D 146
	if ((ret = safefile(fname, uid, S_IREAD)) != 0)
E 146
I 146
D 156
	if ((ret = safefile(fname, uid, forwarding, S_IREAD)) != 0)
E 156
I 156
D 161
	ret = safefile(fname, uid, gid, uname, forwarding, S_IREAD);
	if (ret != 0)
E 161
I 161
D 168
	rval = safefile(fname, uid, gid, uname, forwarding, S_IREAD);
E 168
I 168
D 220
	rval = safefile(fname, uid, gid, uname, sfflags, S_IREAD);
E 220
I 220
	rval = safefile(fname, uid, gid, uname, sfflags, S_IREAD, NULL);
E 220
E 168
	if (rval != 0)
E 161
E 156
E 146
E 144
E 118
	{
D 160
		/* don't use this .forward file */
E 160
I 160
		/* don't use this :include: file */
E 160
D 180
		clrevent(ev);
E 180
I 100
		if (tTd(27, 4))
D 118
			printf("include: not safe (uid=%d)\n", ctladdr->q_uid);
E 100
D 98
		return;
E 98
I 98
		return EPERM;
E 118
I 118
			printf("include: not safe (uid=%d): %s\n",
D 144
				ctladdr->q_uid, errstring(ret));
E 144
I 144
D 161
				uid, errstring(ret));
E 144
		return ret;
E 161
I 161
				uid, errstring(rval));
D 180
		goto resetuid;
E 180
E 161
E 118
E 98
	}
D 180

E 87
D 2
	if (Verbose)
		message(Arpa_Info, "Including file %s", fname);
E 2
	fp = fopen(fname, "r");
	if (fp == NULL)
E 180
I 180
	else
E 180
	{
I 98
D 161
		int ret = errno;

E 161
I 161
D 180
		rval = errno;
E 161
I 111
D 162
		clrevent(ev);
E 162
I 150
		if (tTd(27, 4))
D 161
			printf("include: open: %s\n", errstring(ret));
E 150
E 111
E 98
D 116
		usrerr("Cannot open %s", fname);
E 116
I 116
D 124
		usrerr("550 Cannot open %s", fname);
E 124
I 124
D 129
		usrerr("550 Cannot open %s: %s", fname, errstring(ret));
E 129
I 129
D 139
		if (transienterror(ret))
		{
			ctladdr->q_flags |= QQUEUEUP|QDONTSEND;
			errno = 0;
			usrerr("451 Cannot open %s: %s", fname, errstring(ret));
		}
		else
		{
			usrerr("550 Cannot open %s: %s", fname, errstring(ret));
		}
E 139
E 129
E 124
E 116
D 98
		return;
E 98
I 98
		return ret;
E 161
I 161
			printf("include: open: %s\n", errstring(rval));
D 162
		goto resetuid;
E 162
E 161
E 98
	}
I 87
D 162

E 87
I 20
D 21
	if (fstat(fileno(fp), &st) < 0)
		syserr("Cannot fstat %s!", fname);
	ctladdr->q_uid = st.st_uid;
	ctladdr->q_gid = st.st_gid;
	ctladdr->q_flags |= QGOODUID;
E 21
I 21
D 144
	if (getctladdr(ctladdr) == NULL)
E 144
I 144
	if (ca == NULL)
E 162
I 162
	else if (ca == NULL)
E 162
E 144
	{
		struct stat st;

		if (fstat(fileno(fp), &st) < 0)
E 180
I 180
		fp = fopen(fname, "r");
		if (fp == NULL)
E 180
I 111
		{
D 161
			int ret = errno;

E 161
I 161
			rval = errno;
E 161
D 162
			clrevent(ev);
E 162
E 111
D 180
			syserr("Cannot fstat %s!", fname);
E 180
I 180
			if (tTd(27, 4))
				printf("include: open: %s\n", errstring(rval));
E 180
I 111
D 161
			return ret;
E 161
I 161
D 162
			goto resetuid;
E 162
E 161
		}
E 111
D 162
		ctladdr->q_uid = st.st_uid;
		ctladdr->q_gid = st.st_gid;
		ctladdr->q_flags |= QGOODUID;
E 162
I 162
D 180
		else
		{
			ctladdr->q_uid = st.st_uid;
			ctladdr->q_gid = st.st_gid;
			ctladdr->q_flags |= QGOODUID;
		}
E 180
E 162
	}
E 21
E 20
D 180

E 180
I 87
D 191
	clrevent(ev);
E 191
I 191
	if (ev != NULL)
		clrevent(ev);
E 191

I 162
resetuid:

D 239
#ifdef HASSETREUID
E 239
I 239
#if HASSETREUID || USESETEUID
E 239
	if (saveduid == 0)
	{
		if (uid != 0)
D 193
			if (setreuid(-1, 0) < 0 || setreuid(RealUid, 0) < 0)
E 193
I 193
		{
I 239
# if USESETEUID
			if (seteuid(0) < 0)
				syserr("seteuid(0) failure (real=%d, eff=%d)",
					getuid(), geteuid());
# else
E 239
			if (setreuid(-1, 0) < 0)
				syserr("setreuid(-1, 0) failure (real=%d, eff=%d)",
					getuid(), geteuid());
			if (setreuid(RealUid, 0) < 0)
E 193
				syserr("setreuid(%d, 0) failure (real=%d, eff=%d)",
					RealUid, getuid(), geteuid());
I 239
# endif
E 239
I 193
		}
E 193
		setgid(savedgid);
	}
#endif

	if (tTd(27, 9))
		printf("include: reset uid = %d/%d\n", getuid(), geteuid());
I 183

	if (rval == EOPENTIMEOUT)
		usrerr("451 open timeout on %s", fname);
E 183

	if (fp == NULL)
		return rval;

I 180
	if (fstat(fileno(fp), &st) < 0)
	{
		rval = errno;
		syserr("Cannot fstat %s!", fname);
		return rval;
	}

D 185
	if (ca == NULL)
E 185
I 185
D 186
#ifdef _POSIX_CHOWN_RESTRICTED
	safechown = fpathconf(fileno(fp), _PC_CHOWN_RESTRICTED) != -1;
E 186
I 186
#ifndef safechown
	safechown = chownsafe(fileno(fp));
#endif
E 186
	if (ca == NULL && safechown)
E 185
	{
		ctladdr->q_uid = st.st_uid;
		ctladdr->q_gid = st.st_gid;
		ctladdr->q_flags |= QGOODUID;
	}
I 185
D 186
#endif
E 186
E 185
	if (ca != NULL && ca->q_uid == st.st_uid)
	{
		/* optimization -- avoid getpwuid if we already have info */
		ctladdr->q_flags |= ca->q_flags & QBOGUSSHELL;
		ctladdr->q_ruser = ca->q_ruser;
	}
	else
	{
I 185
D 197
		char *sh;
E 197
E 185
		register struct passwd *pw;

I 185
D 197
		sh = "/SENDMAIL/ANY/SHELL/";
E 197
E 185
D 226
		pw = getpwuid(st.st_uid);
E 226
I 226
		pw = sm_getpwuid(st.st_uid);
E 226
D 185
		if (pw == NULL || !usershellok(pw->pw_shell))
E 185
I 185
D 197
		if (pw != NULL)
E 185
		{
			ctladdr->q_ruser = newstr(pw->pw_name);
I 185
D 186
#ifdef _POSIX_CHOWN_RESTRICTED
E 186
			if (safechown)
				sh = pw->pw_shell;
D 186
#endif
E 186
		}
E 197
		if (pw == NULL)
E 185
			ctladdr->q_flags |= QBOGUSSHELL;
I 185
D 197
		else if(!usershellok(sh))
E 197
I 197
		else
E 197
		{
I 197
			char *sh;

			ctladdr->q_ruser = newstr(pw->pw_name);
E 197
D 186
#ifdef _POSIX_CHOWN_RESTRICTED
E 186
			if (safechown)
D 197
				ctladdr->q_flags |= QBOGUSSHELL;
E 197
I 197
				sh = pw->pw_shell;
E 197
			else
D 186
#endif
E 186
D 197
				ctladdr->q_flags |= QUNSAFEADDR;
E 197
I 197
				sh = "/SENDMAIL/ANY/SHELL/";
D 244
			if (!usershellok(sh))
E 244
I 244
			if (!usershellok(pw->pw_name, sh))
E 244
			{
				if (safechown)
					ctladdr->q_flags |= QBOGUSSHELL;
				else
					ctladdr->q_flags |= QUNSAFEADDR;
			}
E 197
E 185
		}
	}

E 180
E 162
I 114
	if (bitset(EF_VRFYONLY, e->e_flags))
	{
		/* don't do any more now */
I 132
		ctladdr->q_flags |= QVERIFIED;
I 134
		e->e_nrcpts++;
E 134
E 132
D 127
		fclose(fp);
E 127
I 127
		xfclose(fp, "include", fname);
E 127
D 161
		return 0;
E 161
I 161
D 162
		goto resetuid;
E 162
I 162
		return rval;
E 162
E 161
	}
I 180

	/*
	** Check to see if some bad guy can write this file
	**
	**	This should really do something clever with group
	**	permissions; currently we just view world writable
	**	as unsafe.  Also, we don't check for writable
	**	directories in the path.  We've got to leave
	**	something for the local sysad to do.
	*/

	if (bitset(S_IWOTH, st.st_mode))
		ctladdr->q_flags |= QUNSAFEADDR;
E 180

E 114
E 87
	/* read the file -- each line is a comma-separated list. */
I 50
	FileName = fname;
	LineNumber = 0;
I 113
	ctladdr->q_flags &= ~QSELFREF;
	nincludes = 0;
E 113
E 50
	while (fgets(buf, sizeof buf, fp) != NULL)
	{
D 97
		register char *p = index(buf, '\n');
E 97
I 97
		register char *p = strchr(buf, '\n');
E 97

I 76
		LineNumber++;
E 76
		if (p != NULL)
			*p = '\0';
I 99
D 100
		if (*p == '#' || *p == '\0')
E 100
I 100
		if (buf[0] == '#' || buf[0] == '\0')
E 100
			continue;
I 227

		/* <sp>#@# introduces a comment anywhere */
		/* for Japanese character sets */
		for (p = buf; (p = strchr(++p, '#')) != NULL; )
		{
			if (p[1] == '@' && p[2] == '#' &&
			    isascii(p[-1]) && isspace(p[-1]) &&
D 240
			    isascii(p[3]) && isspace(p[3]))
E 240
I 240
			    (p[3] == '\0' || (isascii(p[3]) && isspace(p[3]))))
E 240
			{
				p[-1] = '\0';
				break;
			}
		}
		if (buf[0] == '\0')
			continue;

E 227
E 99
D 83
		if (buf[0] == '\0')
E 83
I 83
D 96
		if (buf[0] == '\0' || buf[0] == '#')
E 83
			continue;
E 96
D 3
		To = fname;
E 3
I 3
D 37
		To = oldto;
E 37
I 37
D 93
		CurEnv->e_to = oldto;
E 93
I 93
D 108
		e->e_to = oldto;
E 108
I 108
		e->e_to = NULL;
E 108
E 93
E 37
E 3
D 40
		if (Verbose)
D 2
			message(Arpa_Info, " >> %s", buf);
E 2
I 2
			message(Arpa_Info, "%s to %s", msg, buf);
E 40
I 40
D 87
		message(Arpa_Info, "%s to %s", msg, buf);
E 87
I 87
D 116
		message(Arpa_Info, "%s to %s",
E 116
I 116
		message("%s to %s",
E 116
			forwarding ? "forwarding" : "sending", buf);
I 107
#ifdef LOG
D 109
		if (forwarding && LogLevel >= 10)
E 109
I 109
		if (forwarding && LogLevel > 9)
E 109
			syslog(LOG_INFO, "%s: forward %s => %s",
D 188
				e->e_id, oldto, buf);
E 188
I 188
				e->e_id == NULL ? "NOQUEUE" : e->e_id,
				oldto, buf);
E 188
#endif

E 107
E 87
E 40
D 200
		AliasLevel++;
E 2
D 18
		sendto(buf, 1);
E 18
I 18
D 30
D 32
		sendto(buf, 1, ctladdr);
E 32
I 32
D 42
		sendto(buf, 1, ctladdr, sendq);
E 42
I 42
D 51
		sendto(buf, ctladdr, sendq);
E 51
I 51
D 93
		sendtolist(buf, ctladdr, sendq);
E 93
I 93
D 113
		sendtolist(buf, ctladdr, sendq, e);
E 113
I 113
		nincludes += sendtolist(buf, ctladdr, sendq, e);
E 113
E 93
E 51
E 42
E 32
E 30
I 30
		sendto(buf, 1, ctladdr, 0);
E 30
E 18
I 2
		AliasLevel--;
E 200
I 200
		nincludes += sendtolist(buf, ctladdr, sendq, aliaslevel + 1, e);
E 200
I 112
	}
I 150

	if (ferror(fp) && tTd(27, 3))
		printf("include: read error: %s\n", errstring(errno));
E 150
D 113
	if (!bitset(QSELFREF, ctladdr->q_flags))
E 113
I 113
	if (nincludes > 0 && !bitset(QSELFREF, ctladdr->q_flags))
E 113
	{
		if (tTd(27, 5))
		{
			printf("include: QDONTSEND ");
			printaddr(ctladdr, FALSE);
		}
		ctladdr->q_flags |= QDONTSEND;
E 112
E 2
	}

D 10
	fclose(fp);
E 10
I 10
D 127
	(void) fclose(fp);
E 127
I 127
	(void) xfclose(fp, "include", fname);
E 127
I 50
	FileName = oldfilename;
	LineNumber = oldlinenumber;
I 148
	e->e_to = oldto;
E 148
I 98
D 160
	return 0;
E 160
I 160
D 162

resetuid:

#ifdef HASSETREUID
	if (saveduid == 0)
	{
		if (uid != 0)
			if (setreuid(-1, 0) < 0 || setreuid(RealUid, 0) < 0)
				syserr("setreuid(%d, 0) failure (real=%d, eff=%d)",
					RealUid, getuid(), geteuid());
		setgid(savedgid);
	}
#endif

	if (tTd(27, 9))
		printf("include: reset uid = %d/%d\n", getuid(), geteuid());
E 162
	return rval;
E 160
E 98
I 87
}

D 215
static
E 215
I 215
static void
E 215
includetimeout()
{
	longjmp(CtxIncludeTimeout, 1);
E 87
E 50
I 11
}
/*
**  SENDTOARGV -- send to an argument vector.
**
**	Parameters:
**		argv -- argument vector to send to.
I 118
**		e -- the current envelope.
E 118
**
**	Returns:
**		none.
**
**	Side Effects:
**		puts all addresses on the argument vector onto the
**			send queue.
*/

I 241
void
E 241
D 93
sendtoargv(argv)
E 93
I 93
sendtoargv(argv, e)
E 93
	register char **argv;
I 93
	register ENVELOPE *e;
E 93
{
	register char *p;
D 70
	extern bool sameword();
E 70

	while ((p = *argv++) != NULL)
	{
D 70
		if (argv[0] != NULL && argv[1] != NULL && sameword(argv[0], "at"))
E 70
I 70
D 126
		if (argv[0] != NULL && argv[1] != NULL && !strcasecmp(argv[0], "at"))
E 70
		{
			char nbuf[MAXNAME];

			if (strlen(p) + strlen(argv[1]) + 2 > sizeof nbuf)
D 116
				usrerr("address overflow");
E 116
I 116
				usrerr("554 address overflow");
E 116
			else
			{
				(void) strcpy(nbuf, p);
				(void) strcat(nbuf, "@");
				(void) strcat(nbuf, argv[1]);
				p = newstr(nbuf);
				argv += 2;
			}
		}
E 126
D 18
		sendto(p, 0);
E 18
I 18
D 19
		sendto(p, 0, &From);
E 19
I 19
D 29
		sendto(p, 0, NULL);
E 29
I 29
D 30
D 32
		sendto(p, 0, (ADDRESS *) NULL);
E 32
I 32
D 37
		sendto(p, 0, (ADDRESS *) NULL, &SendQueue);
E 37
I 37
D 42
		sendto(p, 0, (ADDRESS *) NULL, &CurEnv->e_sendqueue);
E 42
I 42
D 51
		sendto(p, (ADDRESS *) NULL, &CurEnv->e_sendqueue);
E 51
I 51
D 93
		sendtolist(p, (ADDRESS *) NULL, &CurEnv->e_sendqueue);
E 93
I 93
D 113
		sendtolist(p, (ADDRESS *) NULL, &e->e_sendqueue, e);
E 113
I 113
D 159
		(void) sendtolist(p, (ADDRESS *) NULL, &e->e_sendqueue, e);
E 159
I 159
D 200
D 206
		(void) sendtolist(p, NULLADDR, &e->e_sendqueue, e);
E 200
I 200
D 205
		(void) sendtolist(p, NULLADDR, &e->e_sendqueue, 0, e);
E 205
I 205
D 213
		(void) sendtolist(denlstring(p), NULLADDR,
				  &e->e_sendqueue, 0, e);
E 206
I 206
D 212
		(void) sendtolist(denlstring(p), NULLADDR, &e->e_sendqueue, e);
E 212
I 212
		(void) sendtolist(p, NULLADDR, &e->e_sendqueue, e);
E 213
I 213
		(void) sendtolist(p, NULLADDR, &e->e_sendqueue, 0, e);
E 213
E 212
E 206
E 205
E 200
E 159
E 113
E 93
E 51
E 42
E 37
E 32
E 30
I 30
		sendto(p, 0, (ADDRESS *) NULL, 0);
E 30
E 29
E 19
E 18
	}
I 18
}
/*
**  GETCTLADDR -- get controlling address from an address header.
**
**	If none, get one corresponding to the effective userid.
**
**	Parameters:
**		a -- the address to find the controller of.
**
**	Returns:
**		the controlling address.
**
**	Side Effects:
**		none.
*/

ADDRESS *
getctladdr(a)
	register ADDRESS *a;
{
D 20
	while (a != NULL && a->q_home == NULL)
E 20
I 20
	while (a != NULL && !bitset(QGOODUID, a->q_flags))
E 20
		a = a->q_alias;
D 19
	if (a == NULL)
		return (&From);
E 19
	return (a);
I 234
}
/*
**  SELF_REFERENCE -- check to see if an address references itself
**
**	The check is done through a chain of aliases.  If it is part of
**	a loop, break the loop at the "best" address, that is, the one
**	that exists as a real user.
**
**	This is to handle the case of:
D 236
**		Andrew.Chang:	awc
**		awc:		Andrew.Chang@mail.server.
E 236
I 236
**		awc:		Andrew.Chang
**		Andrew.Chang:	awc@mail.server
E 236
**	which is a problem only on mail.server.
**
**	Parameters:
**		a -- the address to check.
**		e -- the current envelope.
**
**	Returns:
**		The address that should be retained.
*/

ADDRESS *
self_reference(a, e)
	ADDRESS *a;
	ENVELOPE *e;
{
	ADDRESS *b;		/* top entry in self ref loop */
	ADDRESS *c;		/* entry that point to a real mail box */

	if (tTd(27, 1))
		printf("self_reference(%s)\n", a->q_paddr);

	for (b = a->q_alias; b != NULL; b = b->q_alias)
	{
		if (sameaddr(a, b))
			break;
	}

	if (b == NULL)
	{
		if (tTd(27, 1))
			printf("\t... no self ref\n");
		return NULL;
	}

	/*
	**  Pick the first address that resolved to a real mail box
	**  i.e has a pw entry.  The returned value will be marked
	**  QSELFREF in recipient(), which in turn will disable alias()
	**  from marking it QDONTSEND, which mean it will be used
	**  as a deliverable address.
	**
	**  The 2 key thing to note here are:
	**	1) we are in a recursive call sequence:
	**		alias->sentolist->recipient->alias
	**	2) normally, when we return back to alias(), the address
	**	   will be marked QDONTSEND, since alias() assumes the
	**	   expanded form will be used instead of the current address.
	**	   This behaviour is turned off if the address is marked
	**	   QSELFREF We set QSELFREF when we return to recipient().
	*/

	c = a;
	while (c != NULL)
	{
		if (bitnset(M_HASPWENT, c->q_mailer->m_flags))
		{
			if (tTd(27, 2))
				printf("\t... getpwnam(%s)... ", c->q_user);
			if (sm_getpwnam(c->q_user) != NULL)
			{
				if (tTd(27, 2))
					printf("found\n");

				/* ought to cache results here */
D 238
				return c;
E 238
I 238
				if (sameaddr(b, c))
					return b;
				else
					return c;
E 238
			}
			if (tTd(27, 2))
				printf("failed\n");
		}
		c = c->q_alias;
	}

	if (tTd(27, 1))
		printf("\t... cannot break loop for \"%s\"\n", a->q_paddr);

	return NULL;
E 234
E 18
E 11
E 10
}
E 1
