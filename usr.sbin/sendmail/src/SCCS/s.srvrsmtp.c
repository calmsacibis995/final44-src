h02611
s 00001/00002/01248
d D 8.83 95/06/21 11:36:43 eric 252 251
c *sigh*  don't disallow bare NL in incoming 8BITMIME messages
e
s 00001/00001/01249
d D 8.82 95/06/14 07:04:22 eric 251 250
c update for new DSN draft
e
s 00001/00001/01249
d D 8.81 95/06/11 06:47:08 eric 250 249
c updates for new DSN drafts
e
s 00001/00001/01249
d D 8.80 95/06/05 07:26:23 eric 249 248
c freespace=>freediskspace, enoughspace=>enoughdiskspace to avoid
c conflicts with some memory allocators (e.g., A/UX)
e
s 00009/00001/01241
d D 8.79 95/05/31 08:49:53 eric 248 247
c move SMTP startup logging to daemon.c so that $_ is set
e
s 00005/00005/01237
d D 8.78 95/05/31 08:31:27 eric 247 246
c log more info in several places
e
s 00000/00001/01242
d D 8.77 95/05/30 19:24:13 eric 246 245
c change RealUserName from an array to a pointer; move defn to sendmail.h
e
s 00001/00000/01242
d D 8.76 95/05/29 09:03:24 eric 245 244
c allow trusted users to use -bs without a warning
e
s 00011/00001/01231
d D 8.75 95/05/28 11:49:45 eric 244 243
c lint
e
s 00003/00003/01229
d D 8.74 95/05/27 07:46:19 eric 243 242
c make 451 error codes explicit
e
s 00001/00001/01231
d D 8.73 95/05/18 13:09:41 eric 242 241
c clean up version numbers on DSN drafts
e
s 00002/00000/01230
d D 8.72 95/05/15 19:00:23 eric 241 240
c put MIME 8->7 bit conversions on a compile flag (default on for now)
e
s 00006/00000/01224
d D 8.71 95/04/29 07:41:30 eric 240 239
c truncate first space of second and subsequent 220 greeting messages
e
s 00001/00001/01223
d D 8.70 95/04/26 09:05:51 eric 239 238
c add BROKEN_ANSI_LIBRARY define to get around strtoul problem
e
s 00001/00000/01223
d D 8.69 95/04/25 09:57:45 eric 238 237
c only insist on CRLF for SMTP 8BITMIME
e
s 00001/00001/01222
d D 8.68 95/04/22 11:06:12 eric 237 236
c default DSNs on
e
s 00001/00001/01222
d D 8.67 95/04/21 09:57:23 eric 236 235
c update copyright notice
e
s 00017/00019/01206
d D 8.66 95/04/10 11:05:09 eric 235 234
c eliminate BrokenSmtpPeers and two line SMTP greeting messages
e
s 00011/00003/01214
d D 8.65 95/04/08 16:18:01 eric 234 233
c have HELP report the version number
e
s 00003/00001/01214
d D 8.64 95/03/31 09:05:36 eric 233 232
c buffer error messages during collect phase (better implementation)
e
s 00001/00001/01214
d D 8.63 95/03/27 11:43:27 eric 232 231
c make DSN info match draft numbers
e
s 00006/00001/01209
d D 8.62 95/03/27 09:25:38 eric 231 230
c more cleanup for DSN drafts
e
s 00001/00000/01209
d D 8.61 95/03/25 07:39:37 eric 230 229
c don't pass through NOTIFY= unless it was given in the SMTP RCPT
e
s 00025/00000/01184
d D 8.60 95/03/22 18:09:25 eric 229 228
c more updates for DSN
e
s 00004/00001/01180
d D 8.59 95/03/22 17:23:56 eric 228 227
c avoid null messages if you get a tempfail on a recipient address
c and then lose the connection before data phase completes
e
s 00005/00006/01176
d D 8.58 95/03/21 09:52:30 eric 227 226
c fix some compile problems with message sizes
e
s 00086/00067/01096
d D 8.57 95/03/21 09:26:52 eric 226 225
c new DSN draft
e
s 00001/00001/01162
d D 8.56 95/03/14 09:11:05 eric 225 224
c change call to expand() to be more rational (and consistent!)
e
s 00001/00001/01162
d D 8.55 95/02/23 15:50:54 eric 224 222
c cleanup to make gcc -Winitialized happier
e
s 00000/00000/01007
d R 8.37.1.1 95/02/10 07:37:49 eric 223 205
i 222
c fix security problem allowing bogus lines to be written to qf file
c from command line or IDENT protocol by embedding newlines
e
s 00001/00001/01162
d D 8.54 95/02/10 07:16:40 eric 222 221
c fix security problem: avoid newlines in command line or IDENT input
e
s 00001/00010/01162
d D 8.53 95/02/05 08:03:55 eric 221 220
c cut at 20 January version of DSN document
e
s 00002/00000/01170
d D 8.52 94/12/05 10:05:10 eric 220 219
c fix a bug that caused lost messages in -odq mode
e
s 00002/00000/01168
d D 8.51 94/12/03 08:29:23 eric 219 218
c put DSNs on a compile flag
e
s 00001/00001/01167
d D 8.50 94/11/25 09:06:09 eric 218 217
c improve DSN handling somewhat + some bug fixes
e
s 00001/00001/01167
d D 8.49 94/11/22 22:24:59 eric 217 216
c clean up several small problems with file delivery, error detection,
c and return receipts
e
s 00005/00002/01163
d D 8.48 94/11/22 16:59:19 eric 216 215
c fix propogation of notification flags to alias values
e
s 00093/00054/01072
d D 8.47 94/11/21 21:07:40 eric 215 214
c convert to new DSN draft
e
s 00001/00001/01125
d D 8.46 94/11/05 10:43:56 eric 214 213
c announce DSN extension as X-DSN-0 instead of DSN until it is
c standardized
e
s 00102/00003/01024
d D 8.45 94/11/04 08:40:30 eric 213 212
c first cut at DSN implementation
e
s 00001/00001/01026
d D 8.44 94/08/07 16:53:53 eric 212 211
c fix unnecessary dereferences
e
s 00003/00003/01024
d D 8.43 94/07/23 07:59:36 eric 211 210
c MIME 8 to 7 bit support
e
s 00002/00002/01025
d D 8.42 94/07/03 11:48:24 eric 210 209
c break out special local mail processing (e.g., mapping to the
c "prog" mailer) onto separate mailer flags
e
s 00028/00000/00999
d D 8.41 94/06/24 12:50:16 eric 209 208
c diagnose bogus HELO commands
e
s 00005/00004/00994
d D 8.40 94/06/17 11:06:30 eric 208 207
c fixes for MIME body type support
e
s 00001/00001/00997
d D 8.39 94/05/17 08:12:22 eric 207 206
c make VRFY 252 response more polite
e
s 00019/00027/00979
d D 8.38 94/05/12 13:06:38 eric 206 205
c repairs to ensure that error messages in response to delivery time
c problems (such as "too many hops" always get delivered even in doublequeue
c mode; this also cleans up the CMDDATA code a lot
e
s 00006/00002/01000
d D 8.37 94/04/13 08:53:31 eric 205 204
c try to handle very large SIZE parameters (should be a quad)
e
s 00002/00002/01000
d D 8.36 94/04/12 15:43:13 eric 204 203
c fix need for double space between ESMTP args on MAIL command
e
s 00006/00006/00996
d D 8.35 94/04/12 14:54:23 eric 203 202
c fix botch in multi-line SMTP greeting code
e
s 00001/00001/01001
d D 8.34 94/04/12 14:38:14 eric 202 201
c make HELO and EHLO response consistent
e
s 00013/00001/00989
d D 8.33 94/04/12 08:21:15 eric 201 200
c handle multi-line greeting messages
e
s 00011/00000/00979
d D 8.32 94/03/08 10:32:17 eric 200 199
c avoid "warning: user foo owned process using -bs" if mail is sent
c from foo
e
s 00001/00001/00978
d D 8.31 94/03/04 08:46:40 eric 199 198
c fix uninitialized variable reference in ESMTP parameters without an "="
e
s 00011/00000/00968
d D 8.30 94/02/28 10:03:47 eric 198 197
c abort connection after 25 bad commands
e
s 00006/00002/00962
d D 8.29 94/02/06 19:29:01 eric 197 196
c changes from Eric Wassenaar: Apollo portability and improved network
c error handling
e
s 00015/00011/00949
d D 8.28 94/02/05 17:12:44 eric 196 195
c fix bug in last delta causing all MAIL commands to fail
e
s 00011/00009/00949
d D 8.27 94/02/05 12:29:48 eric 195 194
c allow $s to be set to NULL for locally generated mail
e
s 00002/00000/00956
d D 8.26 94/01/31 14:47:40 eric 194 193
c eliminate HELO checking -- almost noone does it right
e
s 00008/00008/00948
d D 8.25 94/01/22 09:01:35 eric 193 192
c fix problem that caused loss of "invalid HELO arg" authentication
c warnings
e
s 00008/00004/00948
d D 8.24 94/01/15 12:38:55 eric 192 191
c Unicos portability changes
e
s 00001/00001/00951
d D 8.23 93/12/21 14:41:43 eric 191 190
c make the "go away" message more polite
e
s 00001/00000/00951
d D 8.22 93/12/11 13:53:39 eric 190 189
c arrange to log sender in SMTP even if all RCPTs failed
e
s 00003/00003/00948
d D 8.21 93/12/10 12:43:48 eric 189 188
c limit size of input lines sent to setproctitle to avoid buffer overruns
e
s 00018/00011/00933
d D 8.20 93/12/02 15:58:00 eric 188 187
c log host info on expn/vrfy even when they are disabled
e
s 00003/00000/00941
d D 8.19 93/11/26 18:43:36 eric 187 186
c diagnose children that core dump in srvrsmtp
e
s 00003/00001/00938
d D 8.18 93/10/28 19:38:19 eric 186 185
c pass 451 out of space errors back
e
s 00004/00005/00935
d D 8.17 93/10/15 08:34:45 eric 185 184
c 8.6.2: improved error return messages; better error handling on
c hung connections or the name server is down; add "vendor code" on V line;
c fix some X-Authentication-Warning: problems; portability fixes
e
s 00006/00003/00934
d D 8.16 93/09/30 14:52:32 eric 184 183
c log attempts to use the "WIZ" command
e
s 00009/00002/00928
d D 8.15 93/09/18 22:08:16 eric 183 182
c hooks to handle broken SMTP peers that can't handle multi-line
c 220 greeting messages
e
s 00001/00000/00929
d D 8.14 93/08/26 08:24:20 eric 182 180
c remember to clear envelope on RSET
e
s 00027/00002/00927
d D 8.13.1.1 93/08/20 13:18:28 eric 181 180
c announce amount of actual free space in EHLO SIZE line
e
s 00003/00002/00926
d D 8.13 93/08/19 13:36:53 eric 180 179
c fix obscure lost mail problem if fcntl locking used (ugh)
e
s 00005/00004/00923
d D 8.12 93/08/17 09:51:59 eric 179 178
c put in beginnings of mod time checks on maps; generalize flags
c parameter to parseaddr/allocaddr to use RF_ hooks; relax HELO rules
c for Authentication-Warning:s
e
s 00001/00001/00926
d D 8.11 93/08/06 21:17:44 eric 178 177
c NOOP should return 250 response code, not 200
e
s 00000/00003/00927
d D 8.10 93/07/27 21:35:52 eric 177 176
c fix statistics gathering
e
s 00000/00003/00930
d D 8.9 93/07/26 09:20:20 eric 176 175
c fix problem causing errors during collect to supress 250 message
e
s 00004/00000/00929
d D 8.8 93/07/21 12:10:01 eric 175 174
c fix botch with EXPN continuation lines
e
s 00001/00002/00928
d D 8.7 93/07/20 19:24:42 eric 174 173
c RISCOS and SGI fixes; fix error handling (caused error messages to
c be discarded in some circumstances)
e
s 00002/00001/00928
d D 8.6 93/07/19 20:50:12 eric 173 172
c SGI IRIX & ANSI C portability
e
s 00001/00008/00928
d D 8.5 93/07/17 13:46:53 eric 172 171
c detect self-destructing alias loop more generally for better diagnostics
e
s 00006/00003/00930
d D 8.4 93/07/16 10:31:31 eric 171 170
c global error cleanup; log "lost connection" at level 20 if not
c in transaction
e
s 00018/00005/00915
d D 8.3 93/07/13 12:58:34 eric 170 169
c many fixes.  primarily fix for seteuid problem in 8.2; also,
c Solaris compatibility fixes; timed out messages problems; messages
c silently discarded if checkcompat returned EX_TEMPFAIL
e
s 00006/00006/00914
d D 8.2 93/07/11 06:52:40 eric 169 168
c huge number of changes for 8.2, including IRIX & Solaris portability;
c improved error checking; fix -m flag and add -O flag in maps; fix long
c DNS timeouts; relax safefile restrictions; add -X command line flag; etc.
e
s 00002/00002/00918
d D 8.1 93/06/07 10:32:13 bostic 168 167
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00020/00002/00900
d D 6.61 93/06/06 21:25:18 eric 167 166
c behave properly even with bogus input
e
s 00000/00001/00902
d D 6.60 93/06/05 17:07:57 eric 166 165
c lint-style cleanup
e
s 00011/00010/00892
d D 6.59 93/06/03 17:01:28 eric 165 164
c print better diagnostic information on sfgets timeouts
e
s 00004/00000/00898
d D 6.58 93/06/02 19:07:08 eric 164 163
c don't send 050 information after the 250 QUIT response
e
s 00001/00001/00897
d D 6.57 93/05/28 07:00:45 eric 163 162
c change alias initialization to general map initialization
e
s 00000/00004/00898
d D 6.56 93/05/27 11:37:34 eric 162 161
c prototype functions
e
s 00009/00004/00893
d D 6.55 93/05/23 07:32:56 eric 161 160
c message insists on a literal " " or "-" for continuation
e
s 00007/00003/00890
d D 6.54 93/05/21 18:59:54 eric 160 159
c avoid unexpected multiline replies to HELO packet -- it breaks
c Pony Express on VMS; instead use a two line 220 greeting with ESMTP as the
c first word of the second line
e
s 00008/00002/00885
d D 6.53 93/05/12 08:00:08 eric 159 158
c don't allow VERB if PRIV_NOEXPN set
e
s 00015/00003/00872
d D 6.52 93/05/05 12:06:32 eric 158 157
c fixes for problems causing mail to be both sent and rejected
e
s 00013/00008/00862
d D 6.51 93/05/05 08:40:37 eric 157 156
c fix VRFY and EXPN output to have fully qualified names
e
s 00013/00008/00857
d D 6.50 93/05/04 15:45:08 eric 156 155
c update for MIME encapsulated error messages
e
s 00002/00002/00863
d D 6.49 93/05/03 19:12:03 eric 155 154
c change option 8 to option 7 (and invert semantics)
e
s 00002/00001/00863
d D 6.48 93/05/03 17:22:15 eric 154 153
c if in SM_DELIVER mode, don't do optimizations on RCPT
e
s 00001/00001/00863
d D 6.47 93/05/03 12:26:21 eric 153 152
c first cut at updated alias implementation
e
s 00007/00000/00857
d D 6.46 93/04/26 14:42:52 eric 152 151
c reject messages exceeding maximum message size
e
s 00004/00001/00853
d D 6.45 93/04/26 12:45:40 eric 151 150
c give max message size in HELO/EHLO message if specified
e
s 00026/00001/00828
d D 6.44 93/04/15 07:41:17 eric 150 149
c add e_bodytype and B queue line and -B flag for body type information
e
s 00002/00003/00827
d D 6.43 93/04/13 17:36:37 eric 149 148
c simplify and generalize OutChannel => stdout code
e
s 00009/00006/00821
d D 6.42 93/04/13 14:44:54 eric 148 147
c improve setproctitle info
e
s 00008/00000/00819
d D 6.41 93/04/13 08:44:24 eric 147 146
c avoid multiple error messages on wierd syntax like "From: <a"
e
s 00007/00004/00812
d D 6.40 93/04/09 15:55:19 eric 146 145
c set $s after runinchild; runinchild calls newenvelope which clears
c the macros
e
s 00009/00028/00807
d D 6.39 93/04/04 16:03:22 eric 145 144
c IDENT cleanup; move loopback checking from srvr to user smtp
e
s 00008/00008/00827
d D 6.38 93/04/01 14:59:22 eric 144 143
c fixes to properly compute priority, nrcpts, etc. on requeued delivery
e
s 00001/00001/00834
d D 6.37 93/04/01 13:54:17 eric 143 142
c do immediate requeue if expanding aliases during queue run (from SMTP)
e
s 00017/00004/00818
d D 6.36 93/04/01 13:32:39 eric 142 140
c always respond "quickly" to RCPT commands; don't give error
c messages if there is an error in the alias
e
s 00009/00005/00817
d D 6.35.1.1 93/03/30 15:49:36 eric 141 140
c attempt to get better handling of recipients going
e
s 00000/00000/00822
d D 6.35 93/03/30 13:37:11 eric 140 139
x 139 138
c back out previous two changes
e
s 00001/00001/00822
d D 6.34 93/03/30 12:04:22 eric 139 138
c fix typo
e
s 00005/00004/00818
d D 6.33 93/03/30 12:01:30 eric 138 137
c move VRFYONLY flag up into MAIL command (it's global, not local)
e
s 00001/00001/00821
d D 6.32 93/03/29 17:23:46 eric 137 136
c give a nicer message on message acceptance
e
s 00005/00000/00817
d D 6.31 93/03/29 12:43:56 eric 136 135
c diagnose RCPT before MAIL
e
s 00005/00001/00812
d D 6.30 93/03/26 06:43:01 eric 135 134
c fix auth_warning problem that rejected all MAIL commands if no
c HELO was given
e
s 00009/00002/00804
d D 6.29 93/03/23 18:06:37 eric 134 133
c add X-Authentication-Warning: headers on possible attempts at forgery
e
s 00003/00003/00803
d D 6.28 93/03/19 16:24:30 eric 133 132
c initial hooks for ISO networking
e
s 00003/00003/00803
d D 6.27 93/03/19 08:50:54 eric 132 131
c move SendMode and ErrorMode into the envelope
e
s 00003/00001/00803
d D 6.26 93/03/18 14:18:11 eric 131 130
c print queue id on final 250 (after DATA)
e
s 00001/00001/00803
d D 6.25 93/03/18 10:56:27 eric 130 129
c restore e_sender as sending address sans decorations
e
s 00009/00006/00795
d D 6.24 93/03/06 09:32:10 eric 129 128
c log numeric IP addr in Received: lines per 1123 section 5.2.8
e
s 00004/00001/00797
d D 6.23 93/03/03 11:48:56 eric 128 127
c use 252 response to VRFY if PRIV_NOVRFY is set per RFC 1123
c section 5.2.3.
e
s 00001/00000/00797
d D 6.22 93/03/01 13:31:57 eric 127 126
c have HELO/EHLO announce SIZE option
e
s 00068/00007/00729
d D 6.21 93/03/01 12:43:57 eric 126 125
c changes for ESMTP; mostly better delimiter character pointer passing
e
s 00002/00001/00734
d D 6.20 93/03/01 06:42:41 eric 125 124
c fix null pointer reference problem
e
s 00024/00004/00711
d D 6.19 93/02/28 19:57:18 eric 124 123
c hooks for SMTP Service Extensions
e
s 00002/00004/00713
d D 6.18 93/02/28 11:03:14 eric 123 122
c changes for better logging of mail submitters
e
s 00002/00002/00715
d D 6.17 93/02/24 10:19:32 eric 122 121
c fix yet another problem with new owner-foo implementation
e
s 00066/00043/00651
d D 6.16 93/02/23 06:31:47 eric 121 120
c overhaul status of SMTP reply codes
e
s 00007/00007/00687
d D 6.15 93/02/22 17:03:30 eric 120 119
c fix problem with syntax error in MAIL command leaving old subprocess
c around
e
s 00018/00012/00676
d D 6.14 93/02/21 09:54:07 eric 119 118
c generalized timeouts; make RSET reset everything
e
s 00005/00000/00683
d D 6.13 93/02/20 14:54:54 eric 118 117
c optimization: don't expand aliases if you are in queue-only mode
e
s 00021/00011/00662
d D 6.12 93/02/20 14:49:02 eric 117 116
c make VRFY just verify; EXPN does full expansion
e
s 00025/00001/00648
d D 6.11 93/02/20 13:46:41 eric 116 115
c close cached MCI connections after a fork; add p (privacy) and b
c (min blocks free) options; fix selfref code; clean up $#error format
e
s 00003/00001/00646
d D 6.10 93/02/19 16:17:27 eric 115 114
c more bug fixes from Eric Wassenaar
e
s 00003/00002/00644
d D 6.9 93/02/19 10:35:45 eric 114 113
c put better information in Received: lines
e
s 00010/00008/00636
d D 6.8 93/02/18 20:22:30 eric 113 112
c move the meta-characters from C0 into C1 space
e
s 00003/00003/00641
d D 6.7 93/02/16 18:30:01 eric 112 111
c clean up log levels; allow IDA-style split header/envelope rewriting;
c extend arpatounix with more zones (but is this even needed?)
e
s 00003/00001/00641
d D 6.6 93/02/15 16:45:00 eric 111 110
c Allow saving in ~/dead.letter; clean up VRFY output; fix bogus
c error message in udbexpand; null terminate host buffers in buildaddr
c (broken in 6.21).
e
s 00002/00002/00640
d D 6.5 93/02/15 12:00:32 eric 110 109
c improve some error messages; fix quoted :include:s; check for some
c other buffer overflows; log SMTP protocol errors
e
s 00003/00000/00639
d D 6.4 93/02/14 14:41:38 eric 109 108
c HPUX and OSF/1 support; fix SMTP reply codes & multiple SMTP error
c problem; consider cache timeout non-permanent; be more graceful on OS
c failures; log forward, alias, and userdb expansions on log level 10
e
s 00004/00010/00635
d D 6.3 93/01/21 15:18:45 eric 108 107
c more environment problems; limit resource exhaustion; fix incorrect
c name in Connection timed out message; ANSI C fixes; log message sender on
c returned mail during queue run; count recipients properly; fix YP code;
c diagnose "message timed out" properly
e
s 00004/00007/00641
d D 6.2 93/01/01 13:15:59 eric 107 106
c pass timeouts to sfgets
e
s 00000/00000/00648
d D 6.1 92/12/21 16:08:43 eric 106 105
c Release 6
e
s 00003/00003/00645
d D 5.40 92/12/20 11:14:20 eric 105 104
c change random constants to be #defines
e
s 00002/00002/00646
d D 5.39 92/11/14 11:34:25 eric 104 103
c (partially) ANSI-fy it
e
s 00005/00000/00643
d D 5.38 92/07/20 21:02:37 eric 103 102
c log lost connections (for connection caching debugging)
e
s 00001/00001/00642
d D 5.37 92/07/19 10:20:03 eric 102 101
c fix bogus envelope problem in clock-driven queue runs; misc. fixes
e
s 00004/00000/00639
d D 5.36 92/07/13 16:27:45 eric 101 100
c miscellaneous changes to improve logging and messages
e
s 00040/00038/00599
d D 5.35 92/07/12 14:09:48 eric 100 99
c reduce number of instances of CurEnv by passing it as a parameter
e
s 00001/00001/00636
d D 5.34 92/04/16 18:40:16 eric 99 98
c try to eliminate some of the CurEnv globals
e
s 00003/00000/00634
d D 5.33 91/12/15 14:26:37 eric 98 97
c clear errno at top of loop to avoid bogus messages
e
s 00002/00000/00632
d D 5.32 91/12/15 13:59:44 eric 97 96
c separate support for header vs envelope sender; if users are in the
c database, map them to a canonical name (e.g., @CS.Berkeley.EDU) in header.
e
s 00005/00003/00627
d D 5.31 91/05/10 23:05:14 eric 96 95
c fix read-only string problem in help command
e
s 00002/00001/00628
d D 5.30 91/03/19 10:01:42 eric 95 94
c another cut at "I refuse to talk to myself" error message wording
e
s 00001/00001/00628
d D 5.29 91/03/02 17:15:33 bostic 94 93
c ANSI
e
s 00001/00011/00628
d D 5.28 90/06/01 19:04:12 bostic 93 92
c new copyright notice
e
s 00001/00000/00638
d D 5.27 89/01/18 14:39:18 bostic 92 91
c define protocol used for them as wants it
e
s 00000/00072/00638
d D 5.26 88/12/28 20:33:23 bostic 91 90
c WIZ vanishes
e
s 00003/00001/00707
d D 5.25 88/11/17 22:02:37 karels 90 89
c more cleanup, fix some inappropriate syserr's
e
s 00035/00020/00673
d D 5.24 88/11/17 10:32:14 karels 89 88
c expunge debugging/nonstandard/trojan horse commands from smtp,
c logging attempts to use them; log name/address of host from which mail received
c ("mail from" may not include it or may lie); don't allow debug to affect
c permissions locally; change some of the non-system syserrs to syslog at lower
c priority; still need to unifdef remaining debug code
e
s 00003/00001/00690
d D 5.23 88/11/03 18:29:50 bostic 88 87
c  comment out debug
e
s 00011/00009/00680
d D 5.22 88/06/30 14:59:49 bostic 87 86
c install approved copyright notice
e
s 00024/00018/00665
d D 5.21 88/03/13 19:53:16 bostic 86 85
c add Berkeley specific header
e
s 00004/00006/00679
d D 5.20 88/03/13 18:21:50 bostic 85 84
c replace sameword with strcasecmp
e
s 00006/00003/00679
d D 5.19 87/02/03 20:43:52 eric 84 83
c pass sending hostname correctly back via the $s macro (broken sometime
c earlier); hack around some name server changes
e
s 00004/00000/00678
d D 5.18 86/01/05 18:49:17 eric 83 82
m 
c rewrite reply-to and resent-reply-to; save errorqueueu in qf file;
c some performance hacking; some alias handling cleanup; delete leading
c spaces from SMTP lines
e
s 00001/00001/00677
d D 5.17 85/12/17 21:36:21 eric 82 81
m 
c patch to clearenvelope to avoid dereferencing garbage pointers
e
s 00021/00011/00657
d D 5.16 85/09/30 21:34:35 eric 81 80
m 
c clean up some aspects of error message display
e
s 00001/00000/00667
d D 5.15 85/09/23 21:19:01 eric 80 79
m 
c deliver directly in SMTP if VERB command has been issued; don't
c externalize name using ruleset 4 when defining $f macro: this turns "<>"
c into "", which confuses local mail
e
s 00009/00009/00658
d D 5.14 85/09/21 16:35:30 eric 79 78
m 
c yet more cleanup to the process title code
e
s 00001/00001/00666
d D 5.13 85/09/21 15:01:28 eric 78 77
m 
c fix silly botch in SMTP command decoding
e
s 00016/00017/00651
d D 5.12 85/09/21 14:44:30 eric 77 76
m 
c clean up priority handling, making several of the parameters configurable:
c y - WkRecipFact, z - WkClassFact, Z - WkTimeFact, Y - ForkQueueRuns; improve
c process title labelling; finish "errors to postmaster" option
e
s 00007/00000/00661
d D 5.11 85/09/20 09:43:17 eric 76 75
m 
c print cute labels on programs communicating with SMTP
e
s 00004/00000/00657
d D 5.10 85/09/19 23:16:20 eric 75 74
m 
c label child processes more effectively
e
s 00002/00004/00655
d D 5.9 85/09/19 13:35:58 eric 74 73
m 
c lint
e
s 00000/00000/00659
d D 5.8 85/09/19 01:25:35 eric 73 71
i 72
m 
c incorporate SMI changes -- still experimental
e
s 00019/00003/00633
d D 5.5.1.1 85/09/19 00:55:47 eric 72 69
m 
c SMI changes (somewhat)
e
s 00013/00004/00630
d D 5.7 85/09/03 19:50:02 eric 71 70
m 
c Wander WIZ from weariful DEBUG to wonderful WIZ woption
e
s 00001/00003/00633
d D 5.6 85/07/31 15:51:12 miriam 70 69
m 
c Correct the cleaning up of tmp queue files. - Kirk Smith @ Purdue
e
s 00003/00000/00633
d D 5.5 85/06/17 18:52:21 eric 69 68
m 
c From Bill Nowicki: fixes to the statistics
e
s 00004/00000/00629
d D 5.4 85/06/08 10:30:29 eric 68 67
m 
c lint for 4.3 release
e
s 00001/00001/00628
d D 5.3 85/06/08 00:34:15 eric 67 66
m 
c lint
e
s 00002/00005/00627
d D 5.2 85/06/07 22:18:08 miriam 66 65
m 
c Resolve duplicate SccsId
e
s 00014/00000/00618
d D 5.1 85/06/07 15:14:21 dist 65 64
m 
c Add copyright
e
s 00004/00027/00614
d D 4.11 85/04/28 10:43:10 eric 64 63
m 
c remove #ifdef DEBUG so we can compile without #define DEBUG;
c drop SHELL command
e
s 00000/00002/00641
d D 4.10 84/08/18 10:28:23 eric 63 62
m 
c take WizWord off of compilation flag to avoid undefined refs
e
s 00002/00001/00641
d D 4.9 84/08/11 16:54:29 eric 62 61
m 
c Changes from Greg Couch <ucsfcgl!gregc> for V7 compatibility and
c miscellaneous bug fixes; "clear" => "bzero" and "bmove" => "bcopy"
c throughout for consistency; bzero is now in bcopy.c (these are
c supplied by libc on 4.2bsd)
e
s 00030/00028/00612
d D 4.8 84/03/11 19:40:44 eric 61 60
m 
c Remember to open the alias file if the ONEX command is specified.
e
s 00001/00001/00639
d D 4.7 84/03/11 16:55:05 eric 60 59
m 
c change macro expansion character from $ to \001 so that $'s can be
c used in headers -- the .cf file is unchanged by mapping $ to \001.
c \001 is now a manifest constant.
e
s 00001/00001/00639
d D 4.6 84/03/11 13:38:14 eric 59 58
m 
c fixes from Greg Satz <satz@sri-tsc.ARPA>, mostly for PDP's
e
s 00005/00005/00635
d D 4.5 83/11/26 18:52:35 eric 58 57
m 
c fix SERIOUS bug allowing anyone to be "wiz" without a password
c if the configuration was frozen
e
s 00004/00000/00636
d D 4.4 83/10/16 16:07:52 eric 57 56
m 
c Postpone opening the alias DBM file until after the fork in srvrsmtp so
c that the alias database is as current as possible; thanks to dagobah!efo
c (Eben Ostby) for this one.
e
s 00008/00001/00628
d D 4.3 83/08/28 14:45:21 eric 56 55
m 
c Refuse to talk to yourself (i.e., reject HELO packets with your own name).
c Add two thresholds -- option 'x' is the load average at which messages are
c queued rather than delivered (default 12); option 'X' is the load average
c at which incoming TCP connections are refused (default 25).
e
s 00003/00001/00626
d D 4.2 83/08/21 15:13:19 eric 55 54
m 
c Don't send back a separate error message if we have diagnosed an RCPT.
e
s 00000/00000/00627
d D 4.1 83/07/25 19:45:54 eric 54 53
m 
c 4.2 release version
e
s 00027/00007/00600
d D 3.50 83/05/20 11:48:48 eric 53 52
m 238
m 239
c Don't stack processes when VRFY fails.
c Give an error message on multiple RCPT commands with a bad address.
e
s 00002/00000/00605
d D 3.49 83/04/17 17:12:25 eric 52 51
m 199
m 221
c put true current time on SMTP greeting message; fix bogus errno problems
e
s 00001/00000/00604
d D 3.48 83/03/26 14:27:30 eric 51 50
m 214
c changes from MRH for USG UNIX 5.0
e
s 00005/00000/00599
d D 3.47 83/02/18 14:10:56 eric 50 48
m 183
c improve hostname validation: force it even if no HELO command is given.
e
s 00004/00000/00599
d R 3.47 83/02/18 13:11:44 eric 49 48
m 183
c Improve host verification -- put something in even if no HELO command given
e
s 00011/00001/00588
d D 3.46 83/02/18 12:42:18 eric 48 47
m 183
c Add HELO hostname verification
e
s 00002/00002/00587
d D 3.45 83/02/03 10:29:26 eric 47 46
m 160
c $e macro is now SMTP entry message (so that configuration version can
c be included).
e
s 00004/00001/00585
d D 3.44 83/01/16 22:07:12 eric 46 45
m 
c fix SHELL command; CR's on end of lines are still a problem, but....
e
s 00005/00000/00581
d D 3.43 83/01/08 13:48:57 eric 45 44
m 
c be sure to open a new transcript on every queue run; when returning
c an SMTP transcript, only send the last half (i.e., that part which
c describes the sending half).
e
s 00002/00002/00579
d D 3.42 82/12/13 18:26:01 eric 44 43
m 085
c The routine "sendto" is now a system call (yeuch!); change our sendto
c to "sendtolist"
e
s 00003/00002/00578
d D 3.41 82/12/05 13:46:55 eric 43 42
m 092
c Clear the envelope in the child in server SMTP to insure that our oh so
c helpful parent doesn't delete our transcript; move the transcript and
c temporary file pointers into the envelope; pass the envelope to other
c routines in the holy war against global variables; split off envelope
c routines from main.c to envelope.c
e
s 00002/00003/00578
d D 3.40 82/11/28 16:01:13 eric 42 41
m 
c implement SMTP auto-shutdown on 421 codes; clean up some error processing
c items, particularly in SMTP; don't reinstantiate error message bodies after
c queueing; other minor changes.  This is all cleanup from 3.253.
e
s 00028/00013/00553
d D 3.39 82/11/28 00:22:56 eric 41 40
m 
c Many changes resulting from a complete code readthrough.  Most of these
c fix minor bugs or change the internal structure for clarity, etc.  There
c should be almost no externally visible changes (other than some cleaner
c error message printouts and the like).
e
s 00002/00004/00564
d D 3.38 82/11/24 18:44:50 eric 40 39
m 
c lint it
e
s 00115/00051/00453
d D 3.37 82/11/24 17:16:00 eric 39 38
m 026
c run SMTP jobs in a subprocess so that multiple jobs will work.  This
c delta also changes the envelope data structure so that flags are in
c a bit map, and adjusts some of the semantics.  The transcript is now
c local to an envelope.  A bunch of old code is deleted.  A serious bug
c was fixed in the "run in background" code.  Etc., etc.
e
s 00012/00000/00492
d D 3.36 82/11/21 17:19:16 eric 38 37
m 026
c preliminary hacks for multiple SMTP transactions per connection: make
c assignment of multiple queue id's more efficient, make prefixes two
c characters (e.g., qfAA99999), pass the file name to freeze and thaw,
c add a mailer flag saying we are talking to one of our own kind.
e
s 00002/00002/00490
d D 3.35 82/11/17 09:37:15 eric 37 36
m 060
c split operation mode ("-bx" flag) and delivery mode ("d" option)
c so that operation mode can apply to SMTP/daemon connections also.
e
s 00065/00015/00427
d D 3.34 82/10/16 14:43:55 eric 36 35
m 007
c Arrange for a wizards password (the W option).  The SMTP KILL command
c may only be issued if this option is set.  This delta adds the "WIZ"
c command, and changes _KILL => KILL, _DEBUG => DEBUG, _VERBOSE => VERB,
c and _SHOWQ => SHOWQ.
e
s 00001/00003/00441
d D 3.33 82/09/26 17:04:31 eric 35 34
c Put more configuration into setoption; merge some of the argv processing
c with this; move configuration information out of conf.c into the .cf
c file.  Since a lot of stuff will default to zero, a new .cf file is
c required.
e
s 00022/00006/00422
d D 3.32 82/09/21 10:12:57 eric 34 33
c avoid double error messages (one from each end)
e
s 00002/00002/00426
d D 3.31 82/09/06 16:25:07 eric 33 32
c install new state-driven scanner; make everyone use it, thus fixing
c problems of quoted commas, etc.
e
s 00001/00001/00427
d D 3.30 82/08/22 23:07:19 eric 32 31
c change $i to $j; $i is now queue id; put "Received:" format in .cf
c file; minor cleanup
e
s 00000/00006/00428
d D 3.29 82/08/21 17:54:46 eric 31 30
c move <> and forward path processing to .cf file; increase MAXATOMS
c since some "comment" information may now be part of the address.
c **** this installation requires a new sendmail.cf file ****
e
s 00002/00001/00432
d D 3.28 82/08/20 20:34:34 eric 30 29
c time stamp the greeting message
e
s 00006/00000/00427
d D 3.27 82/08/15 17:33:11 eric 29 28
c make VRFY and EXPN work more correctly (VRFY still gives an OK even
c if the target is a list); this adds the QuickAbort option
e
s 00000/00001/00427
d D 3.26 82/08/08 21:15:52 eric 28 27
c make "sleep" work correctly even in the face of other events; clean
c up the queue processing: child queue runs now go away when done.  more
c debugging logging is needed to verify that this works right though.
e
s 00004/00013/00424
d D 3.25 82/08/08 17:02:45 eric 27 26
c more general event mechanism
e
s 00003/00002/00434
d D 3.24 82/08/08 01:03:12 eric 26 25
c change debug level to a debug vector; add levels on logging (and the
c -L flag); change logging to be by message-id; elevate message-id;
c some lint-type cleanup
e
s 00001/00001/00435
d D 3.23 82/07/27 23:03:14 eric 25 24
c improve verbose information to make it more obvious what is going where
e
s 00006/00002/00430
d D 3.22 82/07/05 13:18:54 eric 24 23
c fix bug in interactive SMTP session (i.e., non-daemon)
e
s 00018/00001/00414
d D 3.21 82/07/05 12:02:58 eric 23 21
c put timeouts on net reads
e
s 00010/00000/00415
d D 3.20.1.1 82/07/04 10:28:28 eric 22 21
c do some stuff to add a "HOPS" command -- it seems like it would
c be easier and smarter to count Mail-From: lines.
e
s 00002/00002/00413
d D 3.20 82/06/26 13:10:47 eric 21 20
c lint
e
s 00009/00000/00406
d D 3.19 82/06/26 11:56:57 eric 20 19
c add _kill command to SMTP.  this is probably dangerous in the
c outside world.
e
s 00019/00002/00387
d D 3.18 82/06/25 19:38:29 eric 19 18
c add debugging information to server smtp code: _debug to set
c Debug, _verbose to set verbose, and _showq to show the send queue
c (already existant, just a name change)
e
s 00002/00001/00387
d D 3.17 82/06/07 23:55:51 eric 18 17
c call the routine putline to output lines to mailers.  this lets us
c implement line length limits, etc. for full SMTP compatibility.
e
s 00001/00001/00387
d D 3.16 82/06/06 23:05:44 eric 17 16
c implement alias owner feature.  this actually works for any user.
c basically, if the alias owner-xxx exists, errors sending to xxx will be
c sent to that alias rather than to the sender.
e
s 00005/00005/00383
d D 3.15 82/05/22 01:38:52 eric 16 15
c add "envelopes" to contain the basic information needed as control
c info for each message.  currently there is only one envelope -- this
c being the obvious stupid conversion.  later there will be separate
c envelopes for error messages, return receipts, etc.
e
s 00001/00001/00387
d D 3.14 82/03/06 14:51:39 eric 15 14
c tell what recipient is ok when you say it is ok.
e
s 00002/00003/00386
d D 3.13 81/12/06 12:39:44 eric 14 13
c cleanup so it will go through lint without any fancy grep -v's;
c change the way SCCS Id's are handled.
e
s 00001/00000/00388
d D 3.12 81/12/05 14:14:36 eric 13 12
c insert SMTP "Mail-From:" line.
e
s 00006/00000/00382
d D 3.11 81/12/05 11:54:05 eric 12 11
c put the SMTP and queueing code on compilation flags so that sendmail
c will fit on non-ID PDP-11's (ugh); put the ugly UUCP hack on a
c compilation flag also to emphasize that it sucks eggs; makefile
c cleanup.
e
s 00041/00004/00341
d D 3.10 81/11/21 18:43:21 eric 11 10
c change the send queue to be only one queue instead of one per mailer.
c this is slightly inefficient but simpler.  also, pass this queue
c around so we can have multiple send queues.  this makes VRFY work.
e
s 00003/00004/00342
d D 3.9 81/11/21 16:38:37 eric 10 8
c convert to SMTP draft 3 -- finishing touches.  Punt on the VRFY/
c EXPN commands for now; they aren't required anyhow.  Move the fullname
c into the address structure so it can be inherited.
e
s 00064/00006/00340
d D 3.8.1.1 81/11/21 15:49:43 eric 9 8
c links together aliases into proper trees.  This is in part an
c attempt to do the SMTP VRFY command properly, but there are a number
c of annoying problems that convince me that this is the wrong way to
c do it.  Sigh.
e
s 00035/00025/00311
d D 3.8 81/11/21 09:58:01 eric 8 7
c convert to SMTP draft 3
e
s 00014/00007/00322
d D 3.7 81/10/31 22:13:17 eric 7 6
c drop old NCP stuff for ARPANET handling; fix some bugs in error
c messages with multiple recipients in SMTP; clean up error handling
e
s 00003/00003/00326
d D 3.6 81/10/26 14:23:28 eric 6 5
c Install new experimental queueing facility -- one stage timeout,
c etc.  This version is still quite incomplete.  It needs to reorder
c the queue after some interval, do two-stage timeout, take option
c info from the queue file instead of the command line, read the
c sender's .mailcf file, etc.  Some of this is useful for SMTP also.
e
s 00002/00001/00327
d D 3.5 81/10/22 10:25:34 eric 5 4
c move stats file to /usr/lib; put location of sendmail.hf in conf.c
e
s 00090/00008/00238
d D 3.4 81/10/22 09:14:34 eric 4 3
c implement HELP and MRSQ -- MRSQ is a partial implementation
c of old MTP -- in particular, To: fields in MAIL commands are not yet
c implemented.  The "message" routine now takes first args of the form
c "999-" to specify continuation.
e
s 00014/00014/00232
d D 3.3 81/10/20 11:36:54 eric 3 2
c clean up the SMTP stuff some more
e
s 00002/00000/00244
d D 3.2 81/10/20 00:14:53 eric 2 1
c add id keywords
e
s 00244/00000/00000
d D 3.1 81/10/19 22:24:47 eric 1 0
c date and time created 81/10/19 22:24:47 by eric
e
u
U
f b 
f i 
t
T
I 65
/*
I 87
D 236
 * Copyright (c) 1983 Eric P. Allman
E 236
I 236
 * Copyright (c) 1983, 1995 Eric P. Allman
E 236
E 87
D 86
**  Sendmail
**  Copyright (c) 1983  Eric P. Allman
**  Berkeley, California
**
**  Copyright (c) 1983 Regents of the University of California.
**  All rights reserved.  The Berkeley software License Agreement
**  specifies the terms and conditions for redistribution.
*/
E 86
I 86
D 168
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.
E 168
I 168
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 168
 *
D 93
 * Redistribution and use in source and binary forms are permitted
D 87
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
 *
 *  Sendmail
 *  Copyright (c) 1983  Eric P. Allman
 *  Berkeley, California
E 87
I 87
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
E 93
I 93
 * %sccs.include.redist.c%
E 93
E 87
 */
E 86

I 86
# include "sendmail.h"
E 86
D 66
#ifndef lint
static char	SccsId[] = "%W% (Berkeley) %G%";
#endif not lint
E 66

I 86
#ifndef lint
#ifdef SMTP
static char sccsid[] = "%W% (Berkeley) %G% (with SMTP)";
#else
static char sccsid[] = "%W% (Berkeley) %G% (without SMTP)";
#endif
#endif /* not lint */

E 86
E 65
I 39
# include <errno.h>
E 39
I 1
D 86
# include "sendmail.h"
E 86
I 51
D 176
# include <signal.h>
E 176
E 51

I 12
D 86
# ifndef SMTP
I 68
# ifndef lint
E 68
D 14
static char	SccsId[] =	"%W%	%G%	(no SMTP)";
E 14
I 14
D 66
SCCSID(%W%	%Y%	%G%	(no SMTP));
E 66
I 66
static char	SccsId[] = "%W% (Berkeley) %G%	(no SMTP)";
I 68
# endif not lint
E 68
E 66
E 14
# else SMTP

I 68
# ifndef lint
E 68
E 12
I 2
D 14
static char	SccsId[] =	"%W%	%G%";
E 14
I 14
D 66
SCCSID(%W%	%Y%	%G%);
E 66
I 66
static char	SccsId[] = "%W% (Berkeley) %G%";
I 68
# endif not lint
E 86
I 86
# ifdef SMTP
E 86
E 68
E 66
E 14

E 2
/*
**  SMTP -- run the SMTP protocol.
**
**	Parameters:
**		none.
**
**	Returns:
**		never.
**
**	Side Effects:
**		Reads commands from the input channel and processes
**			them.
*/

struct cmd
{
	char	*cmdname;	/* command name */
	int	cmdcode;	/* internal code, see below */
};

/* values for cmdcode */
# define CMDERROR	0	/* bad command */
# define CMDMAIL	1	/* mail -- designate sender */
D 8
# define CMDMRCP	2	/* mrcp -- designate recipient */
E 8
I 8
# define CMDRCPT	2	/* rcpt -- designate recipient */
E 8
# define CMDDATA	3	/* data -- send message text */
I 22
# define CMDHOPS	4	/* hops -- specify hop count */
E 22
D 8
# define CMDDOIT	4	/* doit -- actually do delivery */
E 8
D 39
# define CMDRSET	5	/* rset -- reset state */
# define CMDVRFY	6	/* vrfy -- verify address */
# define CMDHELP	7	/* help -- give usage info */
# define CMDNOOP	8	/* noop -- do nothing */
# define CMDQUIT	9	/* quit -- close connection and die */
I 4
# define CMDMRSQ	10	/* mrsq -- for old mtp compat only */
I 8
# define CMDHELO	11	/* helo -- be polite */
I 11
D 19
# define CMDDBGSHOWQ	12	/* showq -- show send queue (DEBUG) */
E 19
I 19
D 36
# define CMDDBGSHOWQ	12	/* _showq -- show send queue (DEBUG) */
# define CMDDBGDEBUG	13	/* _debug -- set debug mode */
# define CMDDBGVERBOSE	14	/* _verbose -- go into verbose mode */
I 20
# define CMDDBGKILL	15	/* _kill -- kill sendmail */
E 36
I 36
# define CMDDBGSHOWQ	12	/* showq -- show send queue (DEBUG) */
# define CMDDBGDEBUG	13	/* debug -- set debug mode */
# define CMDVERB	14	/* verb -- go into verbose mode */
# define CMDDBGKILL	15	/* kill -- kill sendmail */
# define CMDDBGWIZ	16	/* wiz -- become a wizard */
I 38
# define CMDONEX	17	/* onex -- sending one transaction only */
E 39
I 39
# define CMDRSET	4	/* rset -- reset state */
# define CMDVRFY	5	/* vrfy -- verify address */
D 117
# define CMDHELP	6	/* help -- give usage info */
E 117
I 117
# define CMDEXPN	6	/* expn -- expand address */
E 117
# define CMDNOOP	7	/* noop -- do nothing */
# define CMDQUIT	8	/* quit -- close connection and die */
# define CMDHELO	9	/* helo -- be polite */
D 89
# define CMDDBGQSHOW	10	/* showq -- show send queue (DEBUG) */
# define CMDDBGDEBUG	11	/* debug -- set debug mode */
# define CMDVERB	12	/* verb -- go into verbose mode */
# define CMDDBGKILL	13	/* kill -- kill sendmail */
# define CMDDBGWIZ	14	/* wiz -- become a wizard */
# define CMDONEX	15	/* onex -- sending one transaction only */
E 89
I 89
D 117
# define CMDONEX	10	/* onex -- sending one transaction only */
# define CMDVERB	11	/* verb -- go into verbose mode */
E 117
I 117
# define CMDHELP	10	/* help -- give usage info */
I 124
# define CMDEHLO	11	/* ehlo -- extended helo (RFC 1425) */
E 124
/* non-standard commands */
# define CMDONEX	16	/* onex -- sending one transaction only */
# define CMDVERB	17	/* verb -- go into verbose mode */
I 184
/* use this to catch and log "door handle" attempts on your system */
# define CMDLOGBOGUS	23	/* bogus command that should be logged */
E 184
E 117
/* debugging-only commands, only enabled if SMTPDEBUG is defined */
D 117
# define CMDDBGQSHOW	12	/* showq -- show send queue */
# define CMDDBGDEBUG	13	/* debug -- set debug mode */
E 117
I 117
# define CMDDBGQSHOW	24	/* showq -- show send queue */
# define CMDDBGDEBUG	25	/* debug -- set debug mode */
E 117
D 91
# define CMDDBGKILL	14	/* kill -- kill sendmail */
# define CMDDBGWIZ	15	/* wiz -- become a wizard */
E 91
E 89
D 64
# define CMDDBGSHELL	16	/* shell -- give us a shell */
E 64
E 39
E 38
E 36
E 20
E 19
E 11
E 8
E 4

static struct cmd	CmdTab[] =
{
	"mail",		CMDMAIL,
D 8
	"mrcp",		CMDMRCP,
E 8
I 8
	"rcpt",		CMDRCPT,
D 39
	"mrcp",		CMDRCPT,	/* for old MTP compatability */
E 39
E 8
	"data",		CMDDATA,
D 8
	"doit",		CMDDOIT,
E 8
	"rset",		CMDRSET,
	"vrfy",		CMDVRFY,
I 29
D 117
	"expn",		CMDVRFY,
E 117
I 117
	"expn",		CMDEXPN,
E 117
E 29
I 9
	"expn",		CMDVRFY,
E 9
	"help",		CMDHELP,
	"noop",		CMDNOOP,
	"quit",		CMDQUIT,
I 4
D 39
	"mrsq",		CMDMRSQ,
E 39
I 8
	"helo",		CMDHELO,
I 124
	"ehlo",		CMDEHLO,
E 124
I 36
	"verb",		CMDVERB,
I 38
	"onex",		CMDONEX,
E 38
E 36
I 22
	"hops",		CMDHOPS,
E 22
I 11
D 89
# ifdef DEBUG
E 89
I 89
	/*
	 * remaining commands are here only
	 * to trap and log attempts to use them
	 */
E 89
D 19
	"showq",	CMDDBGSHOWQ,
E 19
I 19
D 36
	"_showq",	CMDDBGSHOWQ,
	"_debug",	CMDDBGDEBUG,
	"_verbose",	CMDDBGVERBOSE,
I 20
	"_kill",	CMDDBGKILL,
E 36
I 36
D 39
	"showq",	CMDDBGSHOWQ,
E 39
I 39
	"showq",	CMDDBGQSHOW,
E 39
D 88
	"debug",	CMDDBGDEBUG,
E 88
I 71
D 89
# endif DEBUG
I 88
# ifdef notdef
E 89
	"debug",	CMDDBGDEBUG,
I 184
	"wiz",		CMDLOGBOGUS,
E 184
D 89
# endif notdef
E 88
# ifdef WIZ
E 89
E 71
D 91
	"kill",		CMDDBGKILL,
I 71
D 89
# endif WIZ
E 89
E 71
	"wiz",		CMDDBGWIZ,
E 91
I 39
D 64
	"shell",	CMDDBGSHELL,
E 64
E 39
E 36
E 20
E 19
D 71
# endif DEBUG
E 71
E 11
E 8
E 4
	NULL,		CMDERROR,
};

I 74
D 91
# ifdef WIZ
E 74
I 36
D 63
# ifdef DEBUG
E 63
bool	IsWiz = FALSE;			/* set if we are a wizard */
I 74
D 89
# endif WIZ
E 89
E 74
D 58
char	*WizWord = NULL;		/* the wizard word to compare against */
E 58
I 58
char	*WizWord;			/* the wizard word to compare against */
I 89
# endif WIZ
E 91
E 89
E 58
D 63
# endif DEBUG
E 63
I 39
D 185
bool	InChild = FALSE;		/* true if running in a subprocess */
E 185
I 41
bool	OneXact = FALSE;		/* one xaction only this run */
I 188
char	*CurSmtpClient;			/* who's at the other end of channel */
E 188
I 48
D 72
char	*RealHostName = NULL;		/* verified hostname, set in daemon.c */
E 72

E 48
E 41
D 185
#define EX_QUIT		22		/* special code for QUIT command */
E 39

E 185
I 173
static char	*skipword();
I 200
D 246
extern char	RealUserName[];
E 246
E 200

I 200

E 200
I 198
#define MAXBADCOMMANDS	25		/* maximum number of bad commands */

I 244
void
E 244
E 198
I 195
D 196
#define REALHOSTNAME	(RealHostName == NULL ? "localhost" : RealHostName)

E 196
E 195
E 173
E 36
D 100
smtp()
E 100
I 100
smtp(e)
	register ENVELOPE *e;
E 100
{
D 36
	char inp[MAXLINE];
E 36
	register char *p;
D 36
	struct cmd *c;
E 36
I 36
	register struct cmd *c;
E 36
	char *cmd;
D 94
	extern char *skipword();
E 94
I 94
D 173
	static char *skipword();
E 173
E 94
D 85
	extern bool sameword();
E 85
D 117
	bool hasmail;			/* mail command received */
E 117
D 7
	bool hasmrcp;			/* has a recipient */
E 7
I 7
D 74
	int rcps;			/* number of recipients */
E 74
E 7
D 9
D 11
	bool hasdata;			/* has mail data */
E 11
I 11
	auto ADDRESS *vrfyqueue;
I 53
	ADDRESS *a;
I 84
D 145
	char *sendinghost;
E 145
I 116
D 117
	bool gothello;
E 117
I 117
D 119
	bool hasmail;			/* mail command received */
E 119
I 119
	bool gotmail;			/* mail command received */
E 119
	bool gothello;			/* helo command received */
	bool vrfy;			/* set if this is a vrfy command */
I 124
	char *protocol;			/* sending protocol */
I 146
	char *sendinghost;		/* sending hostname */
E 146
I 126
D 205
	long msize;			/* approximate maximum message size */
E 205
I 205
D 227
	unsigned long msize;		/* approximate maximum message size */
E 227
E 205
I 196
	char *peerhostname;		/* name of SMTP peer or "localhost" */
E 196
I 181
	long bfree, bsize;		/* queue fs free and block size */
E 181
	auto char *delimptr;
I 131
	char *id;
I 158
D 224
	int nrcpts;			/* number of RCPT commands */
E 224
I 224
	int nrcpts = 0;			/* number of RCPT commands */
E 224
I 170
	bool doublequeue;
I 198
	int badcommands = 0;		/* count of bad commands */
E 198
E 170
E 158
E 131
E 126
E 124
E 117
E 116
E 84
I 75
D 77
	char state[100];
E 77
E 75
E 53
I 38
D 41
	bool onexact = FALSE;		/* one transaction this connection */
E 41
D 40
	bool firsttime = TRUE;		/* this is the first transaction */
E 40
E 38
I 36
	char inp[MAXLINE];
I 77
D 105
	char cmdbuf[100];
E 105
I 105
	char cmdbuf[MAXLINE];
I 129
D 145
	char hostbuf[MAXNAME];
E 145
E 129
E 105
E 77
E 36
I 18
D 235
	extern char Version[];
E 235
I 23
D 91
	extern tick();
I 36
	extern bool iswiz();
I 40
	extern char *arpadate();
E 91
I 50
D 162
	extern char *macvalue();
I 53
	extern ADDRESS *recipient();
E 162
I 72
	extern ENVELOPE BlankEnvelope;
I 244
	extern void help __P((char *));
E 244
I 181
	extern long freespace();
E 181
D 162
	extern ENVELOPE *newenvelope();
I 129
D 133
	extern char *inet_ntoa();
E 133
I 133
	extern char *anynet_ntoa();
E 162
E 133
E 129
E 72
E 53
E 50
E 40
E 36
E 23
E 18
D 14
	ADDRESS *prev;
E 14
E 11
E 9
I 9
	extern ADDRESS *sendto();
	ADDRESS *a;
E 9
I 3
D 4
	int baseerrs;
E 4
E 3

D 3
	/*%%%*/	HostName = "XYZZY";
E 3
D 7
	hasmail = hasmrcp = hasdata = FALSE;
E 7
I 7
D 9
D 11
	hasmail = hasdata = FALSE;
E 11
I 11
D 119
	hasmail = FALSE;
E 119
I 119
D 125
	gotmail = FALSE;
E 125
E 119
E 11
E 9
I 9
	hasmail = FALSE;
E 9
D 74
	rcps = 0;
E 74
I 19
D 21
	close(1);
	dup(fileno(OutChannel));
E 21
I 21
D 24
	(void) close(1);
	(void) dup(fileno(OutChannel));
E 24
I 24
D 149
	if (OutChannel != stdout)
E 149
I 149
	if (fileno(OutChannel) != fileno(stdout))
E 149
	{
		/* arrange for debugging output to go to remote host */
D 149
		(void) close(1);
		(void) dup(fileno(OutChannel));
E 149
I 149
		(void) dup2(fileno(OutChannel), fileno(stdout));
E 149
	}
I 52
D 100
	settime();
E 100
I 100
	settime(e);
E 100
I 76
D 108
	if (RealHostName != NULL)
D 77
	{
		static char status[100];

		(void) sprintf(status, "talking to %s", RealHostName);
		setproctitle(status);
	}
E 77
I 77
D 79
		setproctitle("talking to %s", RealHostName);
E 79
I 79
D 81
		setproctitle("srvrsmtp %s", RealHostName);
E 81
I 81
	{
		CurHostName = RealHostName;
		setproctitle("srvrsmtp %s", CurHostName);
	}
	else
	{
		/* this must be us!! */
		CurHostName = MyHostName;
	}
E 108
I 108
D 123
	if (RealHostName == NULL)
		RealHostName = MyHostName;
E 123
D 195
	CurHostName = RealHostName;
E 195
I 195
D 196
	CurHostName = REALHOSTNAME;
E 196
I 196
	peerhostname = RealHostName;
	if (peerhostname == NULL)
		peerhostname = "localhost";
	CurHostName = peerhostname;
E 196
E 195
D 148
	setproctitle("srvrsmtp %s", CurHostName);
E 148
I 148
D 165
	setproctitle("srvrsmtp %s startup", CurHostName);
E 165
I 165
D 188
	setproctitle("server %s startup", CurHostName);
E 188
I 188
	CurSmtpClient = macvalue('_', e);
	if (CurSmtpClient == NULL)
D 195
		CurSmtpClient = RealHostName;
E 195
I 195
		CurSmtpClient = CurHostName;
E 195

	setproctitle("server %s startup", CurSmtpClient);
E 188
E 165
E 148
E 108
E 81
E 79
E 77
E 76
E 52
E 24
E 21
E 19
E 7
D 18
	message("220", "%s Sendmail at your service", HostName);
E 18
I 18
D 30
	message("220", "%s Sendmail version %s at your service", HostName, Version);
E 30
I 30
D 32
	message("220", "%s Sendmail v%s ready at %s", HostName,
E 32
I 32
D 47
	message("220", "%s Sendmail %s ready at %s", HostName,
E 32
D 40
			Version, arpadate(NULL));
E 40
I 40
			Version, arpadate((char *) NULL));
E 47
I 47
D 60
	expand("$e", inp, &inp[sizeof inp], CurEnv);
E 60
I 60
D 100
	expand("\001e", inp, &inp[sizeof inp], CurEnv);
E 100
I 100
D 113
	expand("\001e", inp, &inp[sizeof inp], e);
E 113
I 113
D 225
	expand("\201e", inp, &inp[sizeof inp], e);
E 225
I 225
D 248
	expand("\201e", inp, sizeof inp, e);
E 248
I 248
#ifdef LOG
	if (LogLevel > 11)
	{
		/* log connection information */
		syslog(LOG_INFO, "SMTP connect from %s (%s)",
			CurSmtpClient, anynet_ntoa(&RealHostAddr));
	}
#endif
E 248
E 225
I 201
D 203
	p = strchr(inp, '\n');
	if (p != NULL)
		*p++ = '\0';
E 203
E 201
E 113
E 100
E 60
D 102
	message("220", inp);
E 102
I 102
D 121
	message("220", "%s", inp);
E 121
I 121
D 160
	message("220 %s", inp);
E 160
I 160
D 183
	message("220-%s", inp);
	message("220 ESMTP spoken here");
E 183
I 183
D 235
	if (BrokenSmtpPeers)
E 235
I 235

	/* output the first line, inserting "ESMTP" as second word */
I 248
	expand("\201e", inp, sizeof inp, e);
E 248
	p = strchr(inp, '\n');
	if (p != NULL)
		*p++ = '\0';
	id = strchr(inp, ' ');
	if (id == NULL)
		id = &inp[strlen(inp)];
	cmd = p == NULL ? "220 %.*s ESMTP%s" : "220-%.*s ESMTP%s";
	message(cmd, id - inp, inp, id);

	/* output remaining lines */
	while ((id = p) != NULL && (p = strchr(id, '\n')) != NULL)
E 235
	{
I 203
D 235
		p = strchr(inp, '\n');
		if (p != NULL)
			*p = '\0';
E 203
		message("220 %s", inp);
E 235
I 235
		*p++ = '\0';
I 240
		if (isascii(*id) && isspace(*id))
			id++;
E 240
		message("220-%s", id);
E 235
	}
D 235
	else
	{
D 201
		message("220-%s", inp);
E 201
I 201
		char *q = inp;
E 235
I 235
	if (id != NULL)
I 240
	{
		if (isascii(*id) && isspace(*id))
			id++;
E 240
		message("220 %s", id);
I 240
	}
E 240
E 235

D 235
		while (q != NULL)
		{
D 203
			message("220-%s", q);
			q = p;
			p = strchr(p, '\n');
E 203
I 203
			p = strchr(q, '\n');
E 203
			if (p != NULL)
				*p++ = '\0';
I 203
			message("220-%s", q);
			q = p;
E 203
		}
E 201
		message("220 ESMTP spoken here");
	}
E 235
E 183
E 160
E 121
E 102
I 72
D 148
	SmtpPhase = "startup";
E 148
I 84
D 145
	sendinghost = NULL;
E 145
I 125
	protocol = NULL;
I 146
	sendinghost = macvalue('s', e);
E 146
E 125
I 116
	gothello = FALSE;
I 125
	gotmail = FALSE;
E 125
E 116
E 84
E 72
E 47
E 40
E 30
I 29
D 53
	(void) setjmp(TopFrame);
	QuickAbort = FALSE;
I 42
	HoldErrs = FALSE;
E 53
E 42
E 29
I 23
D 28
	(void) signal(SIGALRM, tick);
E 28
E 23
E 18
	for (;;)
	{
I 53
		/* arrange for backout */
D 192
		if (setjmp(TopFrame) > 0 && InChild)
E 192
I 192
		if (setjmp(TopFrame) > 0)
E 192
I 147
		{
D 192
			QuickAbort = FALSE;
			SuprErrs = TRUE;
E 147
			finis();
E 192
I 192
			/* if() nesting is necessary for Cray UNICOS */
			if (InChild)
			{
				QuickAbort = FALSE;
				SuprErrs = TRUE;
				finis();
			}
E 192
I 147
		}
E 147
		QuickAbort = FALSE;
		HoldErrs = FALSE;
I 97
		LogUsrErrs = FALSE;
I 117
D 171
		e->e_flags &= ~EF_VRFYONLY;
E 171
I 171
		e->e_flags &= ~(EF_VRFYONLY|EF_GLOBALERRS);
E 171
E 117
E 97

E 53
I 23
		/* setup for the read */
E 23
D 16
		To = NULL;
E 16
I 16
D 100
		CurEnv->e_to = NULL;
E 100
I 100
		e->e_to = NULL;
E 100
E 16
D 3
		Errors = 0;
E 3
I 3
D 4
		baseerrs = Errors;
E 4
I 4
		Errors = 0;
I 19
		(void) fflush(stdout);
E 19
E 4
E 3
D 23
		if (fgets(inp, sizeof inp, InChannel) == NULL)
E 23
I 23

D 27
		/* arrange a timeout */
		if (setjmp(TickFrame) != 0)
		{
			message("421", "%s timed out", HostName);
			finis();
		}
		(void) alarm(ReadTimeout);

E 27
		/* read the input line */
I 148
D 165
		SmtpPhase = "srvrsmtp cmd read";
		setproctitle("srvrsmtp %s cmd read", CurHostName);
E 148
D 27
		p = fgets(inp, sizeof inp, InChannel);
E 27
I 27
D 107
		p = sfgets(inp, sizeof inp, InChannel);
E 107
I 107
D 119
		p = sfgets(inp, sizeof inp, InChannel, ReadTimeout);
E 119
I 119
		p = sfgets(inp, sizeof inp, InChannel, TimeOuts.to_nextcommand);
E 165
I 165
		SmtpPhase = "server cmd read";
D 247
		setproctitle("server %s cmd read", CurHostName);
E 247
I 247
		setproctitle("server %s cmd read", CurSmtpClient);
E 247
		p = sfgets(inp, sizeof inp, InChannel, TimeOuts.to_nextcommand,
				SmtpPhase);
E 165
E 119
E 107
E 27

D 27
		/* clear the timeout and handle errors */
		(void) alarm(0);
E 27
I 27
		/* handle errors */
E 27
		if (p == NULL)
E 23
		{
			/* end of file, just die */
I 197
			disconnect(1, e);
E 197
D 3
			message("421", "Lost input channel");
E 3
I 3
D 81
			message("421", "%s Lost input channel", HostName);
E 81
I 81
D 89
			message("421", "%s Lost input channel to %s",
E 89
I 89
D 121
			message("421", "%s Lost input channel from %s",
E 121
I 121
			message("421 %s Lost input channel from %s",
E 121
E 89
D 188
				MyHostName, CurHostName);
E 188
I 188
				MyHostName, CurSmtpClient);
E 188
I 103
#ifdef LOG
D 112
			if (LogLevel >= 4)
E 112
I 112
D 171
			if (LogLevel > 1)
E 171
I 171
			if (LogLevel > (gotmail ? 1 : 19))
E 171
E 112
				syslog(LOG_NOTICE, "lost input channel from %s",
D 188
					CurHostName);
E 188
I 188
					CurSmtpClient);
E 188
#endif
I 115
			if (InChild)
				ExitStat = EX_QUIT;
E 115
E 103
E 81
E 3
			finis();
		}

		/* clean up end of line */
D 3
		p = index(inp, '\n');
		if (p != NULL)
			*p = '\0';
		p = index(inp, '\r');
		if (p != NULL)
			*p = '\0';
E 3
I 3
		fixcrlf(inp, TRUE);
E 3

I 7
		/* echo command to transcript */
D 25
		fprintf(Xscript, "*** %s\n", inp);
E 25
I 25
D 39
		fprintf(Xscript, "<<< %s\n", inp);
E 39
I 39
D 43
		if (Xscript != NULL)
			fprintf(Xscript, "<<< %s\n", inp);
E 43
I 43
D 100
		if (CurEnv->e_xfp != NULL)
			fprintf(CurEnv->e_xfp, "<<< %s\n", inp);
E 100
I 100
		if (e->e_xfp != NULL)
			fprintf(e->e_xfp, "<<< %s\n", inp);
E 100
E 43
E 39
E 25

I 148
		if (e->e_id == NULL)
D 188
			setproctitle("%s: %s", CurHostName, inp);
E 188
I 188
D 189
			setproctitle("%s: %s", CurSmtpClient, inp);
E 189
I 189
			setproctitle("%s: %.80s", CurSmtpClient, inp);
E 189
E 188
		else
D 188
			setproctitle("%s %s: %s", e->e_id, CurHostName, inp);
E 188
I 188
D 189
			setproctitle("%s %s: %s", e->e_id, CurSmtpClient, inp);
E 189
I 189
			setproctitle("%s %s: %.80s", e->e_id, CurSmtpClient, inp);
E 189
E 188

E 148
E 7
		/* break off command */
D 113
		for (p = inp; isspace(*p); p++)
E 113
I 113
		for (p = inp; isascii(*p) && isspace(*p); p++)
E 113
			continue;
D 105
		cmd = p;
D 77
		while (*++p != '\0' && !isspace(*p))
			continue;
		if (*p != '\0')
			*p++ = '\0';
E 77
I 77
		for (cmd = cmdbuf; *p != '\0' && !isspace(*p); )
E 105
I 105
		cmd = cmdbuf;
D 113
		while (*p != '\0' && !isspace(*p) && cmd < &cmdbuf[sizeof cmdbuf - 2])
E 113
I 113
		while (*p != '\0' &&
		       !(isascii(*p) && isspace(*p)) &&
		       cmd < &cmdbuf[sizeof cmdbuf - 2])
E 113
E 105
			*cmd++ = *p++;
		*cmd = '\0';
E 77

I 83
		/* throw away leading whitespace */
D 113
		while (isspace(*p))
E 113
I 113
		while (isascii(*p) && isspace(*p))
E 113
			p++;

E 83
		/* decode command */
		for (c = CmdTab; c->cmdname != NULL; c++)
		{
D 78
			if (sameword(c->cmdname, cmd))
E 78
I 78
D 85
			if (sameword(c->cmdname, cmdbuf))
E 85
I 85
			if (!strcasecmp(c->cmdname, cmdbuf))
E 85
E 78
				break;
		}

I 98
		/* reset errors */
		errno = 0;

E 98
		/* process command */
		switch (c->cmdcode)
		{
I 8
		  case CMDHELO:		/* hello -- introduce yourself */
I 72
D 124
			SmtpPhase = "HELO";
E 124
I 124
		  case CMDEHLO:		/* extended hello */
			if (c->cmdcode == CMDEHLO)
			{
				protocol = "ESMTP";
D 165
				SmtpPhase = "EHLO";
E 165
I 165
				SmtpPhase = "server EHLO";
E 165
			}
			else
			{
				protocol = "SMTP";
D 165
				SmtpPhase = "HELO";
E 165
I 165
				SmtpPhase = "server HELO";
E 165
			}
I 209

			/* check for valid domain name (re 1123 5.2.5) */
			if (*p == '\0')
			{
				message("501 %s requires domain address",
					cmdbuf);
				break;
			}
			else
			{
				register char *q;

				for (q = p; *q != '\0'; q++)
				{
					if (!isascii(*q))
						break;
					if (isalnum(*q))
						continue;
					if (strchr("[].-_#", *q) == NULL)
						break;
				}
				if (*q != '\0')
				{
					message("501 Invalid domain name");
					break;
				}
			}

E 209
E 124
I 77
D 79
			setproctitle("talking to %s (%s)", RealHostName, inp);
E 79
I 79
D 81
			setproctitle("%s: %s", RealHostName, inp);
E 79
E 77
E 72
I 56
			if (sameword(p, HostName))
E 81
I 81
D 148
			setproctitle("%s: %s", CurHostName, inp);
E 148
D 85
			if (sameword(p, MyHostName))
E 85
I 85
D 119
			if (!strcasecmp(p, MyHostName))
E 119
I 119
D 145
			if (strcasecmp(p, MyHostName) == 0)
E 119
E 85
E 81
			{
D 89
				/* connected to an echo server */
				message("553", "%s I refuse to talk to myself",
D 81
					HostName);
E 81
I 81
					MyHostName);
E 89
I 89
				/*
D 119
				 * didn't know about alias,
				 * or connected to an echo server
				 */
E 119
I 119
				**  Didn't know about alias or MX,
				**  or connected to an echo server
				*/

E 119
D 95
				message("553", "Local configuration error, hostname not recognized as local");
E 95
I 95
D 121
				message("553", "%s config error: mail loops back to myself",
E 121
I 121
				message("553 %s config error: mail loops back to myself",
E 121
					MyHostName);
E 95
E 89
E 81
				break;
			}
I 129
			(void) strcpy(hostbuf, p);
			(void) strcat(hostbuf, " (");
D 133
			(void) strcat(hostbuf, inet_ntoa(RealHostAddr.sin_addr));
E 133
I 133
			(void) strcat(hostbuf, anynet_ntoa(&RealHostAddr));
E 145
I 145
D 146
			define('s', newstr(p), e);
E 146
I 146
			sendinghost = newstr(p);
E 146
E 145
E 133
E 129
E 56
I 13
D 41
			define('s', newstr(p));
E 41
I 41
D 48
			define('s', newstr(p), CurEnv);
E 48
I 48
D 85
			if (RealHostName != NULL && !sameword(p, RealHostName))
E 85
I 85
D 119
			if (RealHostName != NULL && strcasecmp(p, RealHostName))
E 119
I 119
D 123
			if (RealHostName != NULL && strcasecmp(p, RealHostName) != 0)
E 123
I 123
D 179
			if (strcasecmp(p, RealHostName) != 0)
E 179
I 179
D 193
			if (strcasecmp(p, RealHostName) != 0 &&
			    (strcasecmp(RealHostName, "localhost") != 0 ||
			     strcasecmp(p, MyHostName) != 0))
E 179
E 123
E 119
E 85
			{
I 134
				auth_warning(e, "Host %s claimed to be %s",
					RealHostName, p);
E 134
D 77
				char buf[MAXNAME];
E 77
I 77
D 129
				char hostbuf[MAXNAME];
E 77

D 77
				(void) sprintf(buf, "%s (%s)", p, RealHostName);
				define('s', newstr(buf), CurEnv);
E 77
I 77
				(void) sprintf(hostbuf, "%s (%s)", p, RealHostName);
D 84
				define('s', newstr(hostbuf), CurEnv);
E 84
I 84
				sendinghost = newstr(hostbuf);
E 129
I 129
D 145
				(void) strcat(hostbuf, "; ");
				(void) strcat(hostbuf, RealHostName);
E 145
E 129
E 84
E 77
			}
D 129
			else
D 84
				define('s', newstr(p), CurEnv);
E 84
I 84
				sendinghost = newstr(p);
E 129
I 129
D 145
			(void) strcat(hostbuf, ")");
			sendinghost = newstr(hostbuf);
E 145
I 145
D 188
			p = macvalue('_', e);
			if (p == NULL)
D 146
				p = macvalue('s', e);
E 146
I 146
				p = RealHostName;
E 188
E 146
E 145
E 129
E 84
E 48
E 41
E 13
D 9
D 10
			message("250", "%s Pleased to meet you", HostName);
E 10
I 10
D 121
			message("250", "%s Hello %s, pleased to meet you",
E 121
I 121
D 124
			message("250 %s Hello %s, pleased to meet you",
E 124
I 124

E 193
D 161
			/* send ext. message -- old systems must ignore */
D 160
			message("250-%s Hello %s, pleased to meet you",
E 160
I 160
			message("250%c%s Hello %s, pleased to meet you",
				c->cmdcode == CMDEHLO ? '-' : ' ',
E 160
E 124
E 121
D 81
				HostName, p);
E 81
I 81
D 89
				MyHostName, p);
E 89
I 89
D 145
				MyHostName, sendinghost);
E 145
I 145
				MyHostName, p);
E 161
I 160
			gothello = TRUE;
			if (c->cmdcode != CMDEHLO)
I 161
			{
				/* print old message and be done with it */
				message("250 %s Hello %s, pleased to meet you",
D 188
					MyHostName, p);
E 188
I 188
					MyHostName, CurSmtpClient);
E 188
E 161
				break;
I 161
			}
			
			/* print extended message and brag */
			message("250-%s Hello %s, pleased to meet you",
D 202
				MyHostName, p);
E 202
I 202
				MyHostName, CurSmtpClient);
E 202
E 161
E 160
E 145
I 124
			if (!bitset(PRIV_NOEXPN, PrivacyFlags))
				message("250-EXPN");
I 241
#if MIME8TO7
E 241
I 208
D 213
#ifdef ADVERTISE_MIME
E 213
			message("250-8BITMIME");
I 241
#endif
E 241
D 213
#endif
E 213
E 208
I 127
D 151
			message("250-SIZE");
E 151
I 151
D 181
			if (MaxMessageSize > 0)
				message("250-SIZE %ld", MaxMessageSize);
E 181
I 181
			if ((bfree = freespace(QueueDir, &bsize)) >= 0)
			{
				long t;
				int log;

				log = 0;
				bfree -= MinBlocksFree;
				for (t = bfree; t != 0; t >>= 1)
					log++;
				for (t = bsize; t != 0; t >>= 1)
					log++;
				if (log <= 29)
					msize = bfree * bsize;
				else
				{
					/* possible overflow */
					msize = 0;
				}
				if (MaxMessageSize > 0 && MaxMessageSize < msize)
					msize = MaxMessageSize;
			}
			else
				msize = MaxMessageSize;
			if (msize > 0)
				message("250-SIZE %ld", msize);
E 181
			else
				message("250-SIZE");
I 219
D 237
#ifdef DSN
E 237
I 237
#if DSN
E 237
E 219
I 213
D 214
			message("250-DSN");
E 214
I 214
D 215
			message("250-X-DSN-0");
E 215
I 215
D 221
			message("250-X-DSN-1");
E 221
I 221
D 226
			message("250-X-DSN-2 (Unpublished draft as of Sat, 04 Feb 1995)");
E 226
I 226
D 232
			message("250-X-DSN-3 (Unpublished draft of 12 Mar 1995)");
E 232
I 232
D 242
			message("250-X-DSN-03 (Unpublished draft of 12 Mar 1995)");
E 242
I 242
D 250
			message("250-X-DSN-03 (Draft of 12 Mar 1995)");
E 250
I 250
			message("250-X-DSN-04 (Draft of May 29, 1995)");
E 250
E 242
E 232
E 226
E 221
I 219
#endif
E 219
E 215
E 214
E 213
E 151
E 127
			message("250 HELP");
E 124
I 116
D 160
			gothello = TRUE;
E 160
E 116
E 89
E 81
E 10
E 9
I 9
			message("250", "%s Hello %s, pleased to meet you", HostName, p);
E 9
			break;

E 8
		  case CMDMAIL:		/* mail -- designate sender */
I 72
D 165
			SmtpPhase = "MAIL";
E 165
I 165
			SmtpPhase = "server MAIL";
E 165

E 72
I 50
D 145
			/* force a sending host even if no HELO given */
D 100
			if (RealHostName != NULL && macvalue('s', CurEnv) == NULL)
E 100
I 100
D 114
			if (RealHostName != NULL && macvalue('s', e) == NULL)
E 114
I 114
			if (sendinghost == NULL && macvalue('s', e) == NULL)
E 114
E 100
D 84
				define('s', RealHostName, CurEnv);
E 84
I 84
				sendinghost = RealHostName;
E 84

E 145
E 50
I 38
D 40
			firsttime = FALSE;

E 40
			/* check for validity of this command */
I 116
D 134
			if (!gothello && bitset(PRIV_NEEDMAILHELO, PrivacyFlags))
E 134
I 134
			if (!gothello)
E 134
			{
I 145
				/* set sending host to our known value */
D 146
				if (macvalue('s', e) == NULL)
					define('s', RealHostName, e);
E 146
I 146
				if (sendinghost == NULL)
D 195
					sendinghost = RealHostName;
E 195
I 195
D 196
					sendinghost = REALHOSTNAME;
E 196
I 196
					sendinghost = peerhostname;
E 196
E 195
E 146

E 145
D 121
				message("503", "Polite people say HELO first");
E 121
I 121
D 134
				message("503 Polite people say HELO first");
E 134
I 134
				if (bitset(PRIV_NEEDMAILHELO, PrivacyFlags))
I 135
				{
E 135
					message("503 Polite people say HELO first");
I 135
					break;
				}
E 135
D 169
				else
I 135
				{
E 135
					auth_warning(e,
						"Host %s didn't use HELO protocol",
						RealHostName);
E 134
E 121
D 135
				break;
E 135
I 135
				}
E 169
E 135
			}
E 116
E 38
I 3
D 119
			if (hasmail)
E 119
I 119
			if (gotmail)
E 119
			{
D 121
				message("503", "Sender already specified");
E 121
I 121
				message("503 Sender already specified");
I 171
				if (InChild)
					finis();
E 171
E 121
				break;
			}
I 39
			if (InChild)
			{
I 89
				errno = 0;
E 89
D 110
				syserr("Nested MAIL command");
E 110
I 110
D 121
				syserr("Nested MAIL command: MAIL %s", p);
E 121
I 121
				syserr("503 Nested MAIL command: MAIL %s", p);
E 121
E 110
D 115
				exit(0);
E 115
I 115
				finis();
E 115
			}
I 116
D 126
			if (!enoughspace())
			{
D 121
				message("452", "Insufficient disk space; try again later");
E 121
I 121
				message("452 Insufficient disk space; try again later");
E 121
				break;
			}
E 126
E 116

			/* fork a subprocess to process this command */
D 100
			if (runinchild("SMTP-MAIL") > 0)
E 100
I 100
			if (runinchild("SMTP-MAIL", e) > 0)
E 100
				break;
I 195
D 196
			p = REALHOSTNAME;
E 196
E 195
I 169
			if (!gothello)
			{
				auth_warning(e,
D 195
					"Host %s didn't use HELO protocol",
					RealHostName);
E 195
I 195
D 196
					"Host %s didn't use HELO protocol", p);
E 196
I 196
					"Host %s didn't use HELO protocol",
D 247
					peerhostname);
E 247
I 247
					CurSmtpClient);
E 247
E 196
E 195
			}
I 194
#ifdef PICKY_HELO_CHECK
E 194
I 193
D 195
			if (strcasecmp(sendinghost, RealHostName) != 0 &&
			    (strcasecmp(RealHostName, "localhost") != 0 ||
E 195
I 195
D 196
			if (strcasecmp(sendinghost, p) != 0 &&
			    (strcasecmp(p, "localhost") != 0 ||
E 196
I 196
			if (strcasecmp(sendinghost, peerhostname) != 0 &&
			    (strcasecmp(peerhostname, "localhost") != 0 ||
E 196
E 195
			     strcasecmp(sendinghost, MyHostName) != 0))
			{
				auth_warning(e, "Host %s claimed to be %s",
D 195
					RealHostName, sendinghost);
E 195
I 195
D 196
					p, sendinghost);
E 196
I 196
D 247
					peerhostname, sendinghost);
E 247
I 247
					CurSmtpClient, sendinghost);
E 247
E 196
E 195
			}
I 194
#endif
E 194

E 193
E 169
I 84
D 100
			define('s', sendinghost, CurEnv);
I 92
			define('r', "SMTP", CurEnv);
E 92
E 84
			initsys();
I 75
D 77
			(void) sprintf(state, "srvrsmtp %s", CurEnv->e_id);
			setproctitle(state);
E 77
I 77
D 79
			setproctitle("talking to %s (%s - %s)", RealHostName,
				CurEnv->e_id, inp);
E 79
I 79
			setproctitle("%s %s: %s", CurEnv->e_id,
E 100
I 100
D 114
			define('s', sendinghost, e);
E 114
I 114
D 145
			if (sendinghost != NULL)
				define('s', sendinghost, e);
E 145
E 114
D 124
			define('r', "SMTP", e);
E 124
I 124
			if (protocol == NULL)
				protocol = "SMTP";
			define('r', protocol, e);
I 146
			define('s', sendinghost, e);
E 146
E 124
			initsys(e);
I 158
			nrcpts = 0;
I 190
D 228
			e->e_flags |= EF_LOGSENDER;
E 228
I 228
			e->e_flags |= EF_LOGSENDER|EF_CLRQUEUE;
E 228
E 190
E 158
D 107
			setproctitle("%s %s: %s", e->e_id,
E 100
D 81
				RealHostName, inp);
E 81
I 81
				CurHostName, inp);
E 107
I 107
D 188
			setproctitle("%s %s: %s", e->e_id, CurHostName, inp);
E 188
I 188
D 189
			setproctitle("%s %s: %s", e->e_id, CurSmtpClient, inp);
E 189
I 189
			setproctitle("%s %s: %.80s", e->e_id, CurSmtpClient, inp);
E 189
E 188
E 107
E 81
E 79
E 77
E 75

			/* child -- go do the processing */
E 39
E 3
			p = skipword(p, "from");
			if (p == NULL)
				break;
I 109
			if (setjmp(TopFrame) > 0)
I 120
			{
				/* this failed -- undo work */
				if (InChild)
I 147
				{
					QuickAbort = FALSE;
					SuprErrs = TRUE;
I 170
					e->e_flags &= ~EF_FATALERRS;
E 170
E 147
					finis();
I 147
				}
E 147
E 120
				break;
I 120
			}
E 120
			QuickAbort = TRUE;
E 109
D 39
			if (index(p, ',') != NULL)
			{
				message("501", "Source routing not implemented");
				Errors++;
				break;
			}
E 39
D 99
			setsender(p);
E 99
I 99
D 100
			setsender(p, CurEnv);
E 100
I 100
D 126
			setsender(p, e);
E 126
I 126

			/* must parse sender first */
			delimptr = NULL;
D 130
			setsender(p, e, &delimptr);
E 130
I 130
			setsender(p, e, &delimptr, FALSE);
E 130
			p = delimptr;
			if (p != NULL && *p != '\0')
				*p++ = '\0';
I 200

			/* check for possible spoofing */
			if (RealUid != 0 && OpMode == MD_SMTP &&
I 245
			    !wordinclass(RealUserName, 't') &&
E 245
D 210
			    (e->e_from.q_mailer != LocalMailer &&
			     strcmp(e->e_from.q_user, RealUserName) != 0))
E 210
I 210
			    !bitnset(M_LOCALMAILER, e->e_from.q_mailer->m_flags) &&
			    strcmp(e->e_from.q_user, RealUserName) != 0)
E 210
			{
				auth_warning(e, "%s owned process doing -bs",
					RealUserName);
			}
E 200

			/* now parse ESMTP arguments */
D 227
			msize = 0;
E 227
I 227
			e->e_msgsize = 0;
E 227
D 204
			for (; p != NULL && *p != '\0'; p++)
E 204
I 204
			while (p != NULL && *p != '\0')
E 204
			{
				char *kp;
D 199
				char *vp;
E 199
I 199
				char *vp = NULL;
I 244
				extern void mail_esmtp_args __P((char *, char *, ENVELOPE *));
E 244
E 199

				/* locate the beginning of the keyword */
				while (isascii(*p) && isspace(*p))
					p++;
				if (*p == '\0')
					break;
				kp = p;

				/* skip to the value portion */
				while (isascii(*p) && isalnum(*p) || *p == '-')
					p++;
				if (*p == '=')
				{
					*p++ = '\0';
					vp = p;

					/* skip to the end of the value */
					while (*p != '\0' && *p != ' ' &&
					       !(isascii(*p) && iscntrl(*p)) &&
					       *p != '=')
						p++;
				}

				if (*p != '\0')
					*p++ = '\0';

				if (tTd(19, 1))
D 204
					printf("MAIL: got arg %s=%s\n", kp,
E 204
I 204
					printf("MAIL: got arg %s=\"%s\"\n", kp,
E 204
						vp == NULL ? "<null>" : vp);

D 226
				if (strcasecmp(kp, "size") == 0)
				{
D 150
					if (kp == NULL)
E 150
I 150
					if (vp == NULL)
E 150
					{
						usrerr("501 SIZE requires a value");
						/* NOTREACHED */
					}
D 205
					msize = atol(vp);
E 205
I 205
# ifdef __STDC__
					msize = strtoul(vp, (char **) NULL, 10);
# else
					msize = strtol(vp, (char **) NULL, 10);
# endif
E 205
I 150
				}
				else if (strcasecmp(kp, "body") == 0)
				{
					if (vp == NULL)
					{
						usrerr("501 BODY requires a value");
						/* NOTREACHED */
					}
D 208
# ifdef MIME
E 208
I 208
D 222
					e->e_bodytype = newstr(vp);
E 222
E 208
					if (strcasecmp(vp, "8bitmime") == 0)
					{
D 208
						e->e_bodytype = "8BITMIME";
E 208
D 155
						EightBit = TRUE;
E 155
I 155
D 211
						SevenBit = FALSE;
E 211
I 211
						SevenBitInput = FALSE;
E 211
E 155
					}
					else if (strcasecmp(vp, "7bit") == 0)
					{
D 208
						e->e_bodytype = "7BIT";
E 208
D 155
						EightBit = FALSE;
E 155
I 155
D 211
						SevenBit = TRUE;
E 211
I 211
						SevenBitInput = TRUE;
E 211
E 155
					}
					else
					{
						usrerr("501 Unknown BODY type %s",
							vp);
I 208
						/* NOTREACHED */
E 208
					}
I 222
					e->e_bodytype = newstr(vp);
E 222
D 208
# endif
E 208
E 150
				}
I 213
				else if (strcasecmp(kp, "envid") == 0)
				{
					if (vp == NULL)
					{
						usrerr("501 ENVID requires a value");
						/* NOTREACHED */
					}
					e->e_envid = newstr(vp);
D 221
				}
I 215
				else if (strcasecmp(kp, "omts") == 0)
				{
					if (vp == NULL)
					{
						usrerr("501 OMTS requires a value");
						/* NOTREACHED */
					}
					e->e_omts = newstr(vp);
E 221
				}
E 215
E 213
				else
				{
					usrerr("501 %s parameter unrecognized", kp);
					/* NOTREACHED */
				}
E 226
I 226
				mail_esmtp_args(kp, vp, e);
E 226
			}
I 152

D 227
			if (MaxMessageSize > 0 && msize > MaxMessageSize)
E 227
I 227
			if (MaxMessageSize > 0 && e->e_msgsize > MaxMessageSize)
E 227
			{
				usrerr("552 Message size exceeds fixed maximum message size (%ld)",
					MaxMessageSize);
				/* NOTREACHED */
			}
E 152
				
D 227
			if (!enoughspace(msize))
E 227
I 227
D 249
			if (!enoughspace(e->e_msgsize))
E 249
I 249
			if (!enoughdiskspace(e->e_msgsize))
E 249
E 227
			{
				message("452 Insufficient disk space; try again later");
				break;
			}
E 126
E 100
E 99
D 3
			if (Errors == 0)
E 3
I 3
D 4
			if (Errors == baseerrs)
E 4
I 4
D 120
			if (Errors == 0)
E 4
E 3
			{
				message("250", "Sender ok");
D 119
				hasmail = TRUE;
E 119
I 119
				gotmail = TRUE;
E 119
			}
I 39
			else if (InChild)
				finis();
E 120
I 120
D 121
			message("250", "Sender ok");
E 121
I 121
			message("250 Sender ok");
E 121
			gotmail = TRUE;
I 138

			/* optimize: non-interactive, don't expand aliases */
D 139
			if (e->e_sendmode != SM_INTERACTIVE)
E 139
I 139
			if (e->e_sendmode != SM_DELIVER)
E 139
				e->e_flags |= EF_VRFYONLY;

E 138
E 120
E 39
			break;

D 8
		  case CMDMRCP:		/* mrcp -- designate recipient */
E 8
I 8
		  case CMDRCPT:		/* rcpt -- designate recipient */
I 136
			if (!gotmail)
			{
				usrerr("503 Need MAIL before RCPT");
				break;
			}
E 136
I 72
D 165
			SmtpPhase = "RCPT";
E 165
I 165
			SmtpPhase = "server RCPT";
E 165
I 77
D 79
			setproctitle("talking to %s (%s - %s)", RealHostName,
				CurEnv->e_id, inp);
E 79
I 79
D 100
			setproctitle("%s %s: %s", CurEnv->e_id,
E 100
I 100
D 107
			setproctitle("%s %s: %s", e->e_id,
E 100
D 81
				RealHostName, inp);
E 81
I 81
				CurHostName, inp);
E 107
I 107
D 148
			setproctitle("%s %s: %s", e->e_id, CurHostName, inp);
E 148
E 107
E 81
E 79
E 77
E 72
I 53
			if (setjmp(TopFrame) > 0)
I 55
			{
D 100
				CurEnv->e_flags &= ~EF_FATALERRS;
E 100
I 100
				e->e_flags &= ~EF_FATALERRS;
E 100
E 55
				break;
I 55
			}
E 55
			QuickAbort = TRUE;
I 97
			LogUsrErrs = TRUE;
I 118
D 138

D 141
D 142
			/* optimization -- if queueing, don't expand aliases */
D 132
			if (SendMode == SM_QUEUE)
E 132
I 132
			if (e->e_sendmode == SM_QUEUE)
E 132
				e->e_flags |= EF_VRFYONLY;
E 142
I 142
D 154
			e->e_flags |= EF_VRFYONLY;
E 154
I 154
			if (e->e_sendmode != SM_DELIVER)
				e->e_flags |= EF_VRFYONLY;
E 154
E 142
E 138

E 141
E 118
E 97
E 53
E 8
			p = skipword(p, "to");
			if (p == NULL)
				break;
D 31
			if (index(p, ',') != NULL)
			{
				message("501", "Source routing not implemented");
				Errors++;
				break;
			}
E 31
D 6
			sendto(p, 1, NULL);
E 6
I 6
D 9
D 11
			sendto(p, 1, (ADDRESS *) NULL);
E 11
I 11
D 16
			sendto(p, 1, (ADDRESS *) NULL, &SendQueue);
E 16
I 16
D 33
			sendto(p, 1, (ADDRESS *) NULL, &CurEnv->e_sendqueue);
E 33
I 33
D 44
			sendto(p, (ADDRESS *) NULL, &CurEnv->e_sendqueue);
E 44
I 44
D 53
			sendtolist(p, (ADDRESS *) NULL, &CurEnv->e_sendqueue);
E 53
I 53
D 59
			a = parseaddr(p, (ADDRESS *) NULL, 1);
E 59
I 59
D 100
			a = parseaddr(p, (ADDRESS *) NULL, 1, '\0');
E 100
I 100
D 124
			a = parseaddr(p, (ADDRESS *) NULL, 1, '\0', e);
E 124
I 124
D 126
			a = parseaddr(p, (ADDRESS *) NULL, 1, ' ', e);
E 126
I 126
D 179
			a = parseaddr(p, (ADDRESS *) NULL, 1, ' ', NULL, e);
E 179
I 179
D 213
			a = parseaddr(p, NULLADDR, RF_COPYALL, ' ', NULL, e);
E 213
I 213
			a = parseaddr(p, NULLADDR, RF_COPYALL, ' ', &delimptr, e);
E 213
E 179
E 126
E 124
E 100
E 59
			if (a == NULL)
				break;
I 213
			p = delimptr;
E 213
I 62
D 216
			a->q_flags |= QPRIMARY;
I 141
			if (!Verbose)
				e->e_flags |= EF_VRFYONLY;
E 141
E 62
D 100
			a = recipient(a, &CurEnv->e_sendqueue);
E 100
I 100
			a = recipient(a, &e->e_sendqueue, e);
E 216
I 213

			/* now parse ESMTP arguments */
			while (p != NULL && *p != '\0')
			{
				char *kp;
				char *vp = NULL;
I 244
				extern void rcpt_esmtp_args __P((ADDRESS *, char *, char *, ENVELOPE *));
E 244

				/* locate the beginning of the keyword */
				while (isascii(*p) && isspace(*p))
					p++;
				if (*p == '\0')
					break;
				kp = p;

				/* skip to the value portion */
				while (isascii(*p) && isalnum(*p) || *p == '-')
					p++;
				if (*p == '=')
				{
					*p++ = '\0';
					vp = p;

					/* skip to the end of the value */
					while (*p != '\0' && *p != ' ' &&
					       !(isascii(*p) && iscntrl(*p)) &&
					       *p != '=')
						p++;
				}

				if (*p != '\0')
					*p++ = '\0';

				if (tTd(19, 1))
					printf("RCPT: got arg %s=\"%s\"\n", kp,
						vp == NULL ? "<null>" : vp);

D 215
				if (strcasecmp(kp, "notify") == 0)
				{
					if (vp == NULL)
					{
						usrerr("501 NOTIFY requires a value");
						/* NOTREACHED */
					}
					a->q_flags &= ~(QPINGONSUCCESS|QPINGONFAILURE);
					if (strcasecmp(vp, "success") == 0)
						a->q_flags |= QPINGONSUCCESS;
					else if (strcasecmp(vp, "failure") == 0)
						a->q_flags |= QPINGONFAILURE;
					else if (strcasecmp(vp, "always") == 0)
						a->q_flags |= QPINGONSUCCESS |
							      QPINGONFAILURE;
					else if (strcasecmp(vp, "never") != 0)
					{
						usrerr("501 Bad argument \"%s\"  to NOTIFY",
							vp);
						/* NOTREACHED */
					}
				}
				else if (strcasecmp(kp, "ret") == 0)
				{
					if (vp == NULL)
					{
						usrerr("501 RET requires a value");
						/* NOTREACHED */
					}
					a->q_flags |= QHASRETPARAM;
					if (strcasecmp(vp, "no") == 0)
						a->q_flags |= QNOBODYRETURN;
					else if (strcasecmp(vp, "yes") != 0)
					{
						usrerr("501 Bad argument \"%s\" to RET",
							vp);
						/* NOTREACHED */
					}
				}
				else if (strcasecmp(kp, "orcpt") == 0)
				{
					if (vp == NULL)
					{
						usrerr("501 ORCPT requires a value");
						/* NOTREACHED */
					}
					a->q_orcpt = newstr(vp);
				}
				else
				{
					usrerr("501 %s parameter unrecognized", kp);
					/* NOTREACHED */
				}
E 215
I 215
				rcpt_esmtp_args(a, kp, vp, e);
D 244

E 244
E 215
			}
I 216

			/* save in recipient list after ESMTP mods */
D 231
			a->q_flags |= QPRIMARY;
E 231
D 217
			a = recipient(a, &e->e_sendqueue, e);
E 217
I 217
			a = recipient(a, &e->e_sendqueue, 0, e);
E 217

E 216
E 213
E 100
E 53
E 44
I 42
D 55
			CurEnv->e_flags &= ~EF_FATALERRS;
E 55
E 42
E 33
E 16
E 11
E 9
I 9
			a = sendto(p, 1, (ADDRESS *) NULL, 0);
# ifdef DEBUG
			if (Debug > 1)
				printaddr(a, TRUE);
# endif DEBUG
E 9
E 6
D 3
			if (Errors == 0)
E 3
I 3
D 4
			if (Errors == baseerrs)
E 4
I 4
D 53
			if (Errors == 0)
E 53
I 53
			if (Errors != 0)
				break;

			/* no errors during parsing, but might be a duplicate */
D 100
			CurEnv->e_to = p;
E 100
I 100
			e->e_to = p;
E 100
			if (!bitset(QBADADDR, a->q_flags))
I 158
			{
E 158
D 121
				message("250", "Recipient ok");
E 121
I 121
D 185
				message("250 Recipient ok");
E 185
I 185
				message("250 Recipient ok%s",
					bitset(QQUEUEUP, a->q_flags) ?
						" (will queue)" : "");
E 185
I 158
				nrcpts++;
			}
E 158
E 121
			else
E 53
E 4
E 3
			{
D 15
				message("250", "Recipient ok");
E 15
I 15
D 53
				message("250", "%s... Recipient ok", p);
E 15
D 7
				hasmrcp = TRUE;
E 7
I 7
				rcps++;
E 53
I 53
				/* punt -- should keep message in ADDRESS.... */
D 121
				message("550", "Addressee unknown");
E 121
I 121
				message("550 Addressee unknown");
E 121
E 53
E 7
			}
I 53
D 100
			CurEnv->e_to = NULL;
E 100
I 100
			e->e_to = NULL;
E 100
D 74
			rcps++;
E 74
E 53
			break;

		  case CMDDATA:		/* data -- text of mail */
I 72
D 165
			SmtpPhase = "DATA";
E 165
I 165
			SmtpPhase = "server DATA";
E 165
E 72
D 7
			message("354", "Enter mail, end with dot");
			collect();
E 7
I 7
D 8
			collect(TRUE);
E 7
D 3
			if (Errors == 0)
E 3
I 3
D 4
			if (Errors == baseerrs)
E 4
I 4
			if (Errors == 0)
E 4
E 3
			{
				message("250", "Message stored");
				hasdata = TRUE;
			}
			break;

		  case CMDDOIT:		/* doit -- actually send everything */
E 8
D 119
			if (!hasmail)
E 119
I 119
			if (!gotmail)
E 119
I 8
			{
E 8
D 121
				message("503", "Need MAIL command");
E 121
I 121
				message("503 Need MAIL command");
E 121
I 8
				break;
			}
E 8
D 7
			else if (!hasmrcp)
E 7
I 7
D 72
			else if (rcps <= 0)
E 72
I 72
D 100
			else if (CurEnv->e_nrcpts <= 0)
E 100
I 100
D 185
			else if (e->e_nrcpts <= 0)
E 185
I 185
			else if (nrcpts <= 0)
E 185
E 100
E 72
E 7
D 8
				message("503", "Need MRCP (recipient)");
			else if (!hasdata)
				message("503", "No message, use DATA");
			else
E 8
			{
I 7
D 8
				if (rcps != 1)
					HoldErrs = MailBack = TRUE;
E 7
				sendall(FALSE);
D 3
				if (Errors == 0)
E 3
I 3
D 4
				if (Errors == baseerrs)
E 4
I 4
D 7
				if (Errors == 0)
E 7
I 7
				HoldErrs = FALSE;
				To = NULL;
				if (Errors == 0 || rcps != 1)
E 7
E 4
E 3
					message("250", "Sent");
E 8
I 8
D 121
				message("503", "Need RCPT (recipient)");
E 121
I 121
				message("503 Need RCPT (recipient)");
E 121
				break;
E 8
			}
I 8

I 144
			/* check to see if we need to re-expand aliases */
I 170
			/* also reset QBADADDR on already-diagnosted addrs */
			doublequeue = FALSE;
E 170
			for (a = e->e_sendqueue; a != NULL; a = a->q_next)
			{
				if (bitset(QVERIFIED, a->q_flags))
D 170
					break;
E 170
I 170
				{
					/* need to re-expand aliases */
					doublequeue = TRUE;
				}
				if (bitset(QBADADDR, a->q_flags))
				{
					/* make this "go away" */
					a->q_flags |= QDONTSEND;
					a->q_flags &= ~QBADADDR;
				}
E 170
			}

E 144
			/* collect the text of the message */
I 72
			SmtpPhase = "collect";
I 233
			buffer_errors();
E 233
I 171
D 174
			SuprErrs = TRUE;
E 174
I 174
D 186
			HoldErrs = TRUE;
E 186
E 174
E 171
I 77
D 79
			setproctitle("talking to %s (%s - %s)", RealHostName,
				CurEnv->e_id, inp);
E 79
I 79
D 100
			setproctitle("%s %s: %s", CurEnv->e_id,
E 100
I 100
D 107
			setproctitle("%s %s: %s", e->e_id,
E 100
D 81
				RealHostName, inp);
E 81
I 81
				CurHostName, inp);
E 107
I 107
D 148
			setproctitle("%s %s: %s", e->e_id, CurHostName, inp);
E 148
E 107
E 81
E 79
E 77
E 72
D 100
			collect(TRUE);
E 100
I 100
D 144
			collect(TRUE, e);
E 144
I 144
D 170
			collect(TRUE, a != NULL, e);
E 170
I 170
D 211
			collect(TRUE, doublequeue, e);
E 211
I 211
			collect(InChannel, TRUE, doublequeue, NULL, e);
I 233
			flush_errors(TRUE);
E 233
E 211
I 186
			if (Errors != 0)
				goto abortmessage;
I 228

			/* make sure we actually do delivery */
			e->e_flags &= ~EF_CLRQUEUE;
E 228
I 206

			/* from now on, we have to operate silently */
E 206
D 233
			HoldErrs = TRUE;
E 233
I 233
			buffer_errors();
E 233
I 206
			e->e_errormode = EM_MAIL;
E 206
E 186
E 170
I 156
D 171
			e->e_flags &= ~EF_FATALERRS;
E 171
E 156
E 144
E 100
D 176
			if (Errors != 0)
D 158
				break;
E 158
I 158
				goto abortmessage;
E 176
E 158

D 34
			/* if sending to multiple people, mail back errors */
E 34
I 34
			/*
			**  Arrange to send to everyone.
			**	If sending to multiple people, mail back
			**		errors rather than reporting directly.
			**	In any case, don't mail back errors for
			**		anything that has happened up to
			**		now (the other end will do this).
I 45
			**	Truncate our transcript -- the mail has gotten
			**		to us successfully, and if we have
			**		to mail this back, it will be easier
			**		on the reader.
E 45
			**	Then send to everyone.
			**	Finally give a reply code.  If an error has
			**		already been given, don't mail a
			**		message back.
D 39
			**	We goose error returns by clearing FatalErrors.
E 39
I 39
			**	We goose error returns by clearing error bit.
E 39
			*/

E 34
D 72
			if (rcps != 1)
E 72
I 72
			SmtpPhase = "delivery";
D 100
			if (CurEnv->e_nrcpts != 1)
E 100
I 100
D 158
			if (e->e_nrcpts != 1)
E 158
I 158
D 170
			if (nrcpts != 1 && a == NULL)
E 170
I 170
D 206
			if (nrcpts != 1 && !doublequeue)
E 170
E 158
E 100
E 72
D 41
				HoldErrs = MailBack = TRUE;
E 41
I 41
			{
				HoldErrs = TRUE;
D 62
				ErrorMode == EM_MAIL;
E 62
I 62
D 132
				ErrorMode = EM_MAIL;
E 132
I 132
				e->e_errormode = EM_MAIL;
E 132
E 62
			}
E 206
E 41
I 34
D 39
			FatalErrors = FALSE;
E 39
I 39
D 100
			CurEnv->e_flags &= ~EF_FATALERRS;
I 45
			CurEnv->e_xfp = freopen(queuename(CurEnv, 'x'), "w", CurEnv->e_xfp);
E 100
I 100
D 156
			e->e_flags &= ~EF_FATALERRS;
E 156
			e->e_xfp = freopen(queuename(e, 'x'), "w", e->e_xfp);
I 131
			id = e->e_id;
E 131
E 100
E 45
E 39
E 34
D 144

I 142
			/* check to see if we need to re-expand aliases */
			for (a = e->e_sendqueue; a != NULL; a = a->q_next)
			{
				if (bitset(QVERIFIED, a->q_flags))
					break;
			}
E 144

E 142
D 206
			/* send to all recipients */
D 17
			sendall(FALSE);
E 17
I 17
D 37
			sendall(CurEnv, FALSE);
E 37
I 37
D 56
			sendall(CurEnv, SendMode);
E 56
I 56
D 100
			sendall(CurEnv, SM_DEFAULT);
E 56
E 37
E 17
D 34

			/* reset strange modes */
			HoldErrs = FALSE;
E 34
D 16
			To = NULL;
E 16
I 16
			CurEnv->e_to = NULL;
E 100
I 100
D 141
D 142
			sendall(e, SM_DEFAULT);
E 142
I 142
D 170
			sendall(e, a == NULL ? SM_DEFAULT : SM_QUEUE);
E 170
I 170
			sendall(e, doublequeue ? SM_QUEUE : SM_DEFAULT);
E 170
E 142
E 141
I 141
			sendall(e, Verbose ? SM_DELIVER : SM_QUEUE);
E 141
			e->e_to = NULL;
I 171
D 174
			SuprErrs = FALSE;
E 174
E 171
E 100
E 16

I 69
D 177
			/* save statistics */
D 100
			markstats(CurEnv, (ADDRESS *) NULL);
E 100
I 100
			markstats(e, (ADDRESS *) NULL);
E 100

E 177
I 141
			unlockqueue(e);

E 141
E 69
D 34
			/* issue success if appropriate */
			if (Errors == 0 || rcps != 1)
E 34
I 34
			/* issue success if appropriate and reset */
			if (Errors == 0 || HoldErrs)
D 42
			{
				HoldErrs = FALSE;
E 42
E 34
D 37
				message("250", "Sent");
E 37
I 37
D 121
				message("250", "Ok");
E 121
I 121
D 131
				message("250 Ok");
E 131
I 131
D 137
				message("250 %s OK", id);
E 137
I 137
				message("250 %s Message accepted for delivery", id);
E 137
E 131
E 121
E 37
I 34
D 42
			}
E 42
D 156
			else
E 156
I 156
D 158
			if (bitset(EF_FATALERRS, e->e_flags))
E 158
I 158

			if (bitset(EF_FATALERRS, e->e_flags) && !HoldErrs)
E 206
I 206
			if (doublequeue)
E 206
E 158
			{
D 206
				/* avoid sending back an extra message */
E 156
D 39
				FatalErrors = FALSE;
E 39
I 39
D 100
				CurEnv->e_flags &= ~EF_FATALERRS;
E 100
I 100
				e->e_flags &= ~EF_FATALERRS;
I 158
				e->e_flags |= EF_CLRQUEUE;
E 206
I 206
				/* make sure it is in the queue */
				queueup(e, TRUE, FALSE);
I 220
				if (e->e_sendmode == SM_QUEUE)
					e->e_flags |= EF_KEEPQUEUE;
E 220
E 206
E 158
I 142
D 156

			/* if we just queued, poke it */
			if (a != NULL && e->e_sendmode != SM_QUEUE)
E 156
I 156
			}
			else
E 156
			{
I 158
D 206
				/* from now on, we have to operate silently */
				HoldErrs = TRUE;
				e->e_errormode = EM_MAIL;
E 206
I 206
				/* send to all recipients */
				sendall(e, SM_DEFAULT);
			}
			e->e_to = NULL;
E 206

E 158
D 156
				unlockqueue(e);
D 143
				dowork(id, TRUE, e);
E 143
I 143
				dowork(id, TRUE, TRUE, e);
E 143
				e->e_id = NULL;
E 156
I 156
D 206
				/* if we just queued, poke it */
D 170
				if (a != NULL && e->e_sendmode != SM_QUEUE)
E 170
I 170
				if (doublequeue && e->e_sendmode != SM_QUEUE)
E 170
				{
I 180
					extern pid_t dowork();
E 206
I 206
			/* issue success message */
			message("250 %s Message accepted for delivery", id);
E 206

E 180
D 206
					unlockqueue(e);
D 180
					dowork(id, TRUE, TRUE, e);
					e->e_id = NULL;
E 180
I 180
					(void) dowork(id, TRUE, TRUE, e);
E 180
				}
E 206
I 206
			/* if we just queued, poke it */
			if (doublequeue && e->e_sendmode != SM_QUEUE)
			{
				extern pid_t dowork();

				unlockqueue(e);
				(void) dowork(id, TRUE, TRUE, e);
E 206
E 156
			}
E 142
I 141

			/* now make it really happen */
			if (!Verbose && e->e_sendmode != SM_QUEUE)
				dowork(id, TRUE, e);
E 141
E 100

I 158
  abortmessage:
E 158
			/* if in a child, pop back to our parent */
			if (InChild)
				finis();
I 72

			/* clean up a bit */
D 110
			hasmail = 0;
E 110
I 110
D 119
			hasmail = FALSE;
E 119
I 119
			gotmail = FALSE;
E 119
E 110
D 74
			rcps = 0;
E 74
D 100
			dropenvelope(CurEnv);
			CurEnv = newenvelope(CurEnv);
			CurEnv->e_flags = BlankEnvelope.e_flags;
E 100
I 100
			dropenvelope(e);
D 122
			CurEnv = e = newenvelope(e);
E 122
I 122
			CurEnv = e = newenvelope(e, CurEnv);
E 122
			e->e_flags = BlankEnvelope.e_flags;
E 100
E 72
E 39
E 34
E 8
			break;

		  case CMDRSET:		/* rset -- reset state */
D 121
			message("250", "Reset state");
E 121
I 121
			message("250 Reset state");
I 231

			/* arrange to ignore any current send list */
			e->e_sendqueue = NULL;
E 231
I 182
			e->e_flags |= EF_CLRQUEUE;
E 182
E 121
D 39
			finis();
E 39
I 39
			if (InChild)
				finis();
I 119

			/* clean up a bit */
			gotmail = FALSE;
			dropenvelope(e);
D 122
			CurEnv = e = newenvelope(e);
E 122
I 122
			CurEnv = e = newenvelope(e, CurEnv);
E 122
E 119
			break;
E 39

		  case CMDVRFY:		/* vrfy -- verify address */
I 116
D 117
			if (bitset(PRIV_NOVRFY|PRIV_NOEXPN, PrivacyFlags))
E 117
I 117
		  case CMDEXPN:		/* expn -- expand address */
			vrfy = c->cmdcode == CMDVRFY;
			if (bitset(vrfy ? PRIV_NOVRFY : PRIV_NOEXPN,
						PrivacyFlags))
E 117
			{
D 121
				message("502", "That's none of your business");
E 121
I 121
D 128
				message("502 That's none of your business");
E 128
I 128
				if (vrfy)
D 207
					message("252 Who's to say?");
E 207
I 207
					message("252 Cannot VRFY user; try RCPT to attempt delivery (or try finger)");
E 207
				else
D 191
					message("502 That's none of your business");
E 191
I 191
					message("502 Sorry, we do not allow this operation");
E 191
I 188
#ifdef LOG
				if (LogLevel > 5)
					syslog(LOG_INFO, "%s: %s [rejected]",
						CurSmtpClient, inp);
#endif
E 188
E 128
E 121
				break;
			}
			else if (!gothello &&
D 117
				 bitset(PRIV_NEEDVRFYHELO|PRIV_NEEDEXPNHELO, PrivacyFlags))
E 117
I 117
				 bitset(vrfy ? PRIV_NEEDVRFYHELO : PRIV_NEEDEXPNHELO,
						PrivacyFlags))
E 117
			{
D 121
				message("503", "I demand that you introduce yourself first");
E 121
I 121
				message("503 I demand that you introduce yourself first");
E 121
				break;
			}
E 116
I 39
D 100
			if (runinchild("SMTP-VRFY") > 0)
E 100
I 100
D 117
			if (runinchild("SMTP-VRFY", e) > 0)
E 117
I 117
			if (runinchild(vrfy ? "SMTP-VRFY" : "SMTP-EXPN", e) > 0)
E 117
E 100
				break;
I 75
D 77
			setproctitle("SMTP-VRFY");
E 77
I 77
D 79
			setproctitle("talking to %s (%s)", RealHostName, inp);
E 79
I 79
D 81
			setproctitle("%s: %s", RealHostName, inp);
E 81
I 81
D 148
			setproctitle("%s: %s", CurHostName, inp);
E 148
I 101
#ifdef LOG
D 112
			if (LogLevel >= 9)
E 112
I 112
			if (LogLevel > 5)
E 112
D 188
				syslog(LOG_INFO, "%s: %s", CurHostName, inp);
E 188
I 188
				syslog(LOG_INFO, "%s: %s", CurSmtpClient, inp);
E 188
#endif
E 101
E 81
E 79
E 77
E 75
E 39
D 6
			sendto(p, 1, NULL);
E 6
I 6
D 9
D 10
			sendto(p, 1, (ADDRESS *) NULL);
E 9
I 9
			a = sendto(p, 1, (ADDRESS *) NULL, QPSEUDO);
E 9
E 6
D 3
			if (Errors == 0)
E 3
I 3
D 4
			if (Errors == baseerrs)
E 4
I 4
			if (Errors == 0)
E 4
E 3
D 9
				message("250", "user ok");
E 10
I 10
D 11
			message("502", "Command not implemented");
E 11
I 11
			vrfyqueue = NULL;
I 29
			QuickAbort = TRUE;
I 117
			if (vrfy)
				e->e_flags |= EF_VRFYONLY;
E 117
E 29
D 33
			sendto(p, 1, (ADDRESS *) NULL, &vrfyqueue);
E 33
I 33
D 44
			sendto(p, (ADDRESS *) NULL, &vrfyqueue);
E 44
I 44
D 100
			sendtolist(p, (ADDRESS *) NULL, &vrfyqueue);
E 100
I 100
D 116
			sendtolist(p, (ADDRESS *) NULL, &vrfyqueue, e);
E 116
I 116
D 167
			(void) sendtolist(p, (ADDRESS *) NULL, &vrfyqueue, e);
E 167
I 167
			while (*p != '\0' && isascii(*p) && isspace(*p))
D 212
				*p++;
E 212
I 212
				p++;
E 212
			if (*p == '\0')
			{
				message("501 Argument required");
				Errors++;
			}
			else
			{
D 179
				(void) sendtolist(p, (ADDRESS *) NULL,
						  &vrfyqueue, e);
E 179
I 179
D 218
				(void) sendtolist(p, NULLADDR, &vrfyqueue, e);
E 218
I 218
				(void) sendtolist(p, NULLADDR, &vrfyqueue, 0, e);
E 218
E 179
			}
E 167
E 116
E 100
E 44
E 33
I 29
			if (Errors != 0)
I 39
			{
				if (InChild)
					finis();
E 39
				break;
I 39
			}
I 167
			if (vrfyqueue == NULL)
			{
				message("554 Nothing to %s", vrfy ? "VRFY" : "EXPN");
			}
E 167
E 39
E 29
			while (vrfyqueue != NULL)
			{
I 244
				extern void printvrfyaddr __P((ADDRESS *, bool));

E 244
I 175
				a = vrfyqueue;
				while ((a = a->q_next) != NULL &&
				       bitset(QDONTSEND|QBADADDR, a->q_flags))
					continue;
E 175
D 172
				register ADDRESS *a = vrfyqueue->q_next;
D 166
				char *code;
E 166

D 27
				while (a != NULL && bitset(QDONTSEND, a->q_flags))
E 27
I 27
				while (a != NULL && bitset(QDONTSEND|QBADADDR, a->q_flags))
E 27
					a = a->q_next;

E 172
D 27
				if (!bitset(QDONTSEND, vrfyqueue->q_flags))
E 27
I 27
				if (!bitset(QDONTSEND|QBADADDR, vrfyqueue->q_flags))
E 27
D 121
				{
					if (a != NULL)
						code = "250-";
					else
						code = "250";
D 111
					if (vrfyqueue->q_fullname == NULL)
E 111
I 111
					if (strchr(vrfyqueue->q_paddr, '<') != NULL)
						message(code, "%s", vrfyqueue->q_paddr);
					else if (vrfyqueue->q_fullname == NULL)
E 111
						message(code, "<%s>", vrfyqueue->q_paddr);
					else
						message(code, "%s <%s>",
						    vrfyqueue->q_fullname, vrfyqueue->q_paddr);
				}
E 121
I 121
					printvrfyaddr(vrfyqueue, a == NULL);
E 121
D 172
				else if (a == NULL)
D 121
					message("554", "Self destructive alias loop");
E 121
I 121
					message("554 Self destructive alias loop");
E 121
				vrfyqueue = a;
E 172
I 172
				vrfyqueue = vrfyqueue->q_next;
E 172
			}
I 39
			if (InChild)
				finis();
E 39
E 11
E 10
E 9
I 9
				paddrtree(a);
E 9
			break;

		  case CMDHELP:		/* help -- give user info */
D 4
			message("502", "HELP not implemented");
E 4
I 4
D 96
			if (*p == '\0')
				p = "SMTP";
E 96
			help(p);
E 4
			break;

		  case CMDNOOP:		/* noop -- do nothing */
D 121
			message("200", "OK");
E 121
I 121
D 178
			message("200 OK");
E 178
I 178
			message("250 OK");
E 178
E 121
			break;

		  case CMDQUIT:		/* quit -- leave mail */
D 81
			message("221", "%s closing connection", HostName);
E 81
I 81
D 121
			message("221", "%s closing connection", MyHostName);
E 121
I 121
			message("221 %s closing connection", MyHostName);
I 164

I 198
doquit:
I 231
			/* arrange to ignore any current send list */
			e->e_sendqueue = NULL;

E 231
E 198
			/* avoid future 050 messages */
D 197
			Verbose = FALSE;
E 197
I 197
			disconnect(1, e);
E 197

E 164
E 121
E 81
I 39
			if (InChild)
				ExitStat = EX_QUIT;
E 39
			finis();

I 4
D 39
		  case CMDMRSQ:		/* mrsq -- negotiate protocol */
			if (*p == 'R' || *p == 'T')
			{
				/* recipients first or text first */
				message("200", "%c ok, please continue", *p);
			}
			else if (*p == '?')
			{
				/* what do I prefer?  anything, anytime */
				message("215", "R Recipients first is my choice");
			}
			else if (*p == '\0')
			{
				/* no meaningful scheme */
				message("200", "okey dokie boobie");
			}
			else
			{
				/* bad argument */
				message("504", "Scheme unknown");
			}
I 22
			break;

		  case CMDHOPS:		/* specify hop count */
			HopCount = atoi(p);
			if (++HopCount > MAXHOP)
				message("501", "Hop count exceeded");
			else
				message("200", "Hop count ok");
E 22
			break;
I 11

E 39
I 36
		  case CMDVERB:		/* set verbose mode */
I 159
			if (bitset(PRIV_NOEXPN, PrivacyFlags))
			{
				/* this would give out the same info */
				message("502 Verbose unavailable");
				break;
			}
E 159
			Verbose = TRUE;
I 80
D 132
			SendMode = SM_DELIVER;
E 132
I 132
			e->e_sendmode = SM_DELIVER;
E 132
E 80
D 121
			message("200", "Verbose mode");
E 121
I 121
D 159
			message("200 Verbose mode");
E 159
I 159
			message("250 Verbose mode");
E 159
E 121
I 38
			break;

		  case CMDONEX:		/* doing one transaction only */
D 41
			onexact = TRUE;
E 41
I 41
			OneXact = TRUE;
E 41
D 121
			message("200", "Only one transaction");
E 121
I 121
D 159
			message("200 Only one transaction");
E 159
I 159
			message("250 Only one transaction");
E 159
E 121
E 38
			break;

E 36
D 89
# ifdef DEBUG
E 89
I 89
# ifdef SMTPDEBUG
E 89
D 39
		  case CMDDBGSHOWQ:	/* show queues */
E 39
I 39
		  case CMDDBGQSHOW:	/* show queues */
E 39
D 16
			printf("SendQueue=");
			printaddr(SendQueue, TRUE);
E 16
I 16
			printf("Send Queue=");
D 100
			printaddr(CurEnv->e_sendqueue, TRUE);
E 100
I 100
			printaddr(e->e_sendqueue, TRUE);
E 100
I 19
			break;

		  case CMDDBGDEBUG:	/* set debug mode */
D 26
			Debug = atoi(p);
			message("200", "Debug = %d", Debug);
E 26
I 26
			tTsetup(tTdvect, sizeof tTdvect, "0-99.1");
			tTflag(p);
D 121
			message("200", "Debug set");
E 121
I 121
			message("200 Debug set");
E 121
E 26
			break;
I 71
D 89
# endif DEBUG
E 89
E 71

I 71
D 91
# ifdef WIZ
E 71
D 36
		  case CMDDBGVERBOSE:	/* set verbose mode */
			Verbose = TRUE;
			message("200", "Verbose mode");
I 20
			break;

E 36
		  case CMDDBGKILL:	/* kill the parent */
I 36
			if (!iswiz())
				break;
E 36
			if (kill(MotherPid, SIGTERM) >= 0)
				message("200", "Mother is dead");
			else
				message("500", "Can't kill Mom");
E 20
E 19
E 16
			break;
I 36

I 39
D 64
		  case CMDDBGSHELL:	/* give us an interactive shell */
			if (!iswiz())
				break;
I 41
			if (fileno(InChannel) != 0)
			{
				(void) close(0);
				(void) dup(fileno(InChannel));
D 46
				(void) fclose(InChannel);
E 46
I 46
				if (fileno(InChannel) != fileno(OutChannel))
					(void) fclose(InChannel);
E 46
				InChannel = stdin;
			}
			if (fileno(OutChannel) != 1)
			{
				(void) close(1);
				(void) dup(fileno(OutChannel));
				(void) fclose(OutChannel);
				OutChannel = stdout;
			}
I 46
			(void) close(2);
			(void) dup(1);
E 46
E 41
			execl("/bin/csh", "sendmail", 0);
			execl("/bin/sh", "sendmail", 0);
			message("500", "Can't");
D 41
			break;
E 41
I 41
			exit(EX_UNAVAILABLE);
E 41

E 64
E 39
		  case CMDDBGWIZ:	/* become a wizard */
			if (WizWord != NULL)
			{
				char seed[3];
				extern char *crypt();

D 67
				strncpy(seed, WizWord, 2);
E 67
I 67
				(void) strncpy(seed, WizWord, 2);
E 67
D 58
				if (strcmp(WizWord, crypt(p, seed)) != 0)
E 58
I 58
				if (strcmp(WizWord, crypt(p, seed)) == 0)
E 58
				{
D 58
					message("500", "You are no wizard!");
E 58
I 58
					IsWiz = TRUE;
					message("200", "Please pass, oh mighty wizard");
E 58
					break;
				}
			}
D 58
			IsWiz = TRUE;
			message("200", "Please pass, oh mighty wizard");
E 58
I 58
			message("500", "You are no wizard!");
E 58
			break;
E 36
D 71
# endif DEBUG
E 71
E 11

I 71
# else WIZ
		  case CMDDBGWIZ:	/* try to become a wizard */
			message("500", "You wascal wabbit!  Wandering wizards won't win!");
			break;
# endif WIZ
E 91
I 89
# else /* not SMTPDEBUG */
E 89
D 184

E 184
I 89
		  case CMDDBGQSHOW:	/* show queues */
		  case CMDDBGDEBUG:	/* set debug mode */
I 184
# endif /* SMTPDEBUG */
		  case CMDLOGBOGUS:	/* bogus command */
E 184
D 91
		  case CMDDBGKILL:	/* kill the parent */
		  case CMDDBGWIZ:	/* become a wizard */
E 91
D 90
			if (RealHostName)
E 90
I 90
# ifdef LOG
D 123
			if (RealHostName != NULL && LogLevel > 0)
E 123
I 123
			if (LogLevel > 0)
E 123
E 90
D 184
				syslog(LOG_NOTICE,
E 184
I 184
				syslog(LOG_CRIT,
E 184
D 112
				    "\"%s\" command from %s (%s)\n",
E 112
I 112
				    "\"%s\" command from %s (%s)",
E 112
D 195
				    c->cmdname, RealHostName,
E 195
I 195
D 196
				    c->cmdname, REALHOSTNAME,
E 196
I 196
D 247
				    c->cmdname, peerhostname,
E 247
I 247
				    c->cmdname, CurSmtpClient,
E 247
E 196
E 195
D 133
				    inet_ntoa(RealHostAddr.sin_addr));
E 133
I 133
				    anynet_ntoa(&RealHostAddr));
E 133
I 90
# endif
E 90
			/* FALL THROUGH */
D 184
# endif /* SMTPDEBUG */
E 184

E 89
E 71
E 4
		  case CMDERROR:	/* unknown command */
I 198
			if (++badcommands > MAXBADCOMMANDS)
			{
				message("421 %s Too many bad commands; closing connection",
					MyHostName);
				goto doquit;
			}

E 198
D 121
			message("500", "Command unrecognized");
E 121
I 121
			message("500 Command unrecognized");
E 121
			break;

		  default:
I 89
			errno = 0;
E 89
D 121
			syserr("smtp: unknown code %d", c->cmdcode);
E 121
I 121
			syserr("500 smtp: unknown code %d", c->cmdcode);
E 121
			break;
		}
	}
}
/*
**  SKIPWORD -- skip a fixed word.
**
**	Parameters:
**		p -- place to start looking.
**		w -- word to skip.
**
**	Returns:
**		p following w.
**		NULL on error.
**
**	Side Effects:
**		clobbers the p data area.
*/

static char *
skipword(p, w)
	register char *p;
	char *w;
{
	register char *q;
I 196
	char *firstp = p;
E 196
D 85
	extern bool sameword();
E 85

	/* find beginning of word */
D 113
	while (isspace(*p))
E 113
I 113
	while (isascii(*p) && isspace(*p))
E 113
		p++;
	q = p;

	/* find end of word */
D 113
	while (*p != '\0' && *p != ':' && !isspace(*p))
E 113
I 113
	while (*p != '\0' && *p != ':' && !(isascii(*p) && isspace(*p)))
E 113
		p++;
D 113
	while (isspace(*p))
E 113
I 113
	while (isascii(*p) && isspace(*p))
E 113
		*p++ = '\0';
	if (*p != ':')
	{
	  syntax:
D 121
		message("501", "Syntax error");
E 121
I 121
D 167
		message("501 Syntax error");
E 167
I 167
D 196
		message("501 Syntax error in parameters");
E 196
I 196
		message("501 Syntax error in parameters scanning \"%s\"",
			firstp);
E 196
E 167
E 121
		Errors++;
		return (NULL);
	}
	*p++ = '\0';
D 113
	while (isspace(*p))
E 113
I 113
	while (isascii(*p) && isspace(*p))
E 113
		p++;
I 167

	if (*p == '\0')
		goto syntax;
E 167

	/* see if the input word matches desired word */
D 85
	if (!sameword(q, w))
E 85
I 85
	if (strcasecmp(q, w))
E 85
		goto syntax;

	return (p);
I 215
}
/*
I 226
**  MAIL_ESMTP_ARGS -- process ESMTP arguments from MAIL line
**
**	Parameters:
**		kp -- the parameter key.
**		vp -- the value of that parameter.
**		e -- the envelope.
**
**	Returns:
**		none.
*/

I 244
void
E 244
mail_esmtp_args(kp, vp, e)
	char *kp;
	char *vp;
	ENVELOPE *e;
{
	if (strcasecmp(kp, "size") == 0)
	{
		if (vp == NULL)
		{
			usrerr("501 SIZE requires a value");
			/* NOTREACHED */
		}
D 239
# ifdef __STDC__
E 239
I 239
# if defined(__STDC__) && !defined(BROKEN_ANSI_LIBRARY)
E 239
D 227
		msize = strtoul(vp, (char **) NULL, 10);
E 227
I 227
		e->e_msgsize = strtoul(vp, (char **) NULL, 10);
E 227
# else
D 227
		msize = strtol(vp, (char **) NULL, 10);
E 227
I 227
		e->e_msgsize = strtol(vp, (char **) NULL, 10);
E 227
# endif
	}
	else if (strcasecmp(kp, "body") == 0)
	{
		if (vp == NULL)
		{
			usrerr("501 BODY requires a value");
			/* NOTREACHED */
		}
D 252
		if (strcasecmp(vp, "8bitmime") == 0)
E 252
I 252
		else if (strcasecmp(vp, "8bitmime") == 0)
E 252
		{
			SevenBitInput = FALSE;
I 238
D 252
			e->e_flags |= EF_NL_NOT_EOL;
E 252
E 238
		}
		else if (strcasecmp(vp, "7bit") == 0)
		{
			SevenBitInput = TRUE;
		}
		else
		{
			usrerr("501 Unknown BODY type %s",
				vp);
			/* NOTREACHED */
		}
		e->e_bodytype = newstr(vp);
	}
	else if (strcasecmp(kp, "envid") == 0)
	{
		if (vp == NULL)
		{
			usrerr("501 ENVID requires a value");
			/* NOTREACHED */
		}
I 229
		if (!xtextok(vp))
		{
			usrerr("501 Syntax error in ENVID parameter value");
			/* NOTREACHED */
		}
		if (e->e_envid != NULL)
		{
			usrerr("501 Duplicate ENVID parameter");
			/* NOTREACHED */
		}
E 229
		e->e_envid = newstr(vp);
	}
	else if (strcasecmp(kp, "ret") == 0)
	{
		if (vp == NULL)
		{
			usrerr("501 RET requires a value");
			/* NOTREACHED */
		}
I 229
		if (bitset(EF_RET_PARAM, e->e_flags))
		{
			usrerr("501 Duplicate RET parameter");
			/* NOTREACHED */
		}
E 229
		e->e_flags |= EF_RET_PARAM;
		if (strcasecmp(vp, "hdrs") == 0)
			e->e_flags |= EF_NO_BODY_RETN;
		else if (strcasecmp(vp, "full") != 0)
		{
			usrerr("501 Bad argument \"%s\" to RET", vp);
			/* NOTREACHED */
		}
	}
	else
	{
		usrerr("501 %s parameter unrecognized", kp);
		/* NOTREACHED */
	}
}
/*
E 226
**  RCPT_ESMTP_ARGS -- process ESMTP arguments from RCPT line
**
**	Parameters:
**		a -- the address corresponding to the To: parameter.
**		kp -- the parameter key.
**		vp -- the value of that parameter.
**		e -- the envelope.
**
**	Returns:
**		none.
*/

I 244
void
E 244
rcpt_esmtp_args(a, kp, vp, e)
	ADDRESS *a;
	char *kp;
	char *vp;
	ENVELOPE *e;
{
	if (strcasecmp(kp, "notify") == 0)
	{
		char *p;

		if (vp == NULL)
		{
			usrerr("501 NOTIFY requires a value");
			/* NOTREACHED */
		}
		a->q_flags &= ~(QPINGONSUCCESS|QPINGONFAILURE|QPINGONDELAY);
I 230
		a->q_flags |= QHASNOTIFY;
E 230
		if (strcasecmp(vp, "never") == 0)
			return;
		for (p = vp; p != NULL; vp = p)
		{
			p = strchr(p, ',');
			if (p != NULL)
				*p++ = '\0';
			if (strcasecmp(vp, "success") == 0)
				a->q_flags |= QPINGONSUCCESS;
			else if (strcasecmp(vp, "failure") == 0)
				a->q_flags |= QPINGONFAILURE;
			else if (strcasecmp(vp, "delay") == 0)
				a->q_flags |= QPINGONDELAY;
			else
			{
				usrerr("501 Bad argument \"%s\"  to NOTIFY",
					vp);
				/* NOTREACHED */
			}
D 226
		}
	}
	else if (strcasecmp(kp, "ret") == 0)
	{
		if (vp == NULL)
		{
			usrerr("501 RET requires a value");
			/* NOTREACHED */
		}
		a->q_flags |= QHAS_RET_PARAM;
		if (strcasecmp(vp, "hdrs") == 0)
			a->q_flags |= QRET_HDRS;
		else if (strcasecmp(vp, "full") != 0)
		{
			usrerr("501 Bad argument \"%s\" to RET", vp);
			/* NOTREACHED */
E 226
		}
	}
	else if (strcasecmp(kp, "orcpt") == 0)
	{
		if (vp == NULL)
		{
			usrerr("501 ORCPT requires a value");
I 229
			/* NOTREACHED */
		}
D 251
		if (!xtextok(vp))
E 251
I 251
		if (strchr(vp, ';') == NULL || !xtextok(vp))
E 251
		{
			usrerr("501 Syntax error in ORCPT parameter value");
			/* NOTREACHED */
		}
		if (a->q_orcpt != NULL)
		{
			usrerr("501 Duplicate ORCPT parameter");
E 229
			/* NOTREACHED */
		}
		a->q_orcpt = newstr(vp);
	}
	else
	{
		usrerr("501 %s parameter unrecognized", kp);
		/* NOTREACHED */
	}
E 215
I 4
}
/*
I 121
**  PRINTVRFYADDR -- print an entry in the verify queue
**
**	Parameters:
**		a -- the address to print
**		last -- set if this is the last one.
**
**	Returns:
**		none.
**
**	Side Effects:
**		Prints the appropriate 250 codes.
*/

I 244
void
E 244
printvrfyaddr(a, last)
	register ADDRESS *a;
	bool last;
{
	char fmtbuf[20];

	strcpy(fmtbuf, "250");
	fmtbuf[3] = last ? ' ' : '-';

D 157
	if (strchr(a->q_paddr, '<') != NULL)
		strcpy(&fmtbuf[4], "%s");
	else if (a->q_fullname == NULL)
		strcpy(&fmtbuf[4], "<%s>");
E 157
I 157
	if (a->q_fullname == NULL)
	{
		if (strchr(a->q_user, '@') == NULL)
			strcpy(&fmtbuf[4], "<%s@%s>");
		else
			strcpy(&fmtbuf[4], "<%s>");
		message(fmtbuf, a->q_user, MyHostName);
	}
E 157
	else
	{
D 157
		strcpy(&fmtbuf[4], "%s <%s>");
		message(fmtbuf, a->q_fullname, a->q_paddr);
		return;
E 157
I 157
		if (strchr(a->q_user, '@') == NULL)
			strcpy(&fmtbuf[4], "%s <%s@%s>");
		else
			strcpy(&fmtbuf[4], "%s <%s>");
		message(fmtbuf, a->q_fullname, a->q_user, MyHostName);
E 157
	}
D 157
	message(fmtbuf, a->q_paddr);
E 157
}
/*
E 121
**  HELP -- implement the HELP command.
**
**	Parameters:
**		topic -- the topic we want help for.
**
**	Returns:
**		none.
**
**	Side Effects:
**		outputs the help file to message output.
*/

I 244
void
E 244
help(topic)
	char *topic;
{
	register FILE *hf;
	int len;
D 234
	char buf[MAXLINE];
E 234
	bool noinfo;
I 234
	char buf[MAXLINE];
	extern char Version[];
E 234
I 5
D 35
	extern char *HelpFile;
E 35
E 5

I 234

E 234
D 5
	hf = fopen("/usr/lib/sendmail.hf", "r");
E 5
I 5
D 35
	hf = fopen(HelpFile, "r");
E 5
	if (hf == NULL)
E 35
I 35
	if (HelpFile == NULL || (hf = fopen(HelpFile, "r")) == NULL)
E 35
	{
		/* no help */
I 52
		errno = 0;
E 52
D 121
		message("502", "HELP not implemented");
E 121
I 121
D 234
		message("502 HELP not implemented");
E 234
I 234
		message("502 Sendmail %s -- HELP not implemented", Version);
E 234
E 121
		return;
	}

I 96
	if (topic == NULL || *topic == '\0')
I 234
	{
E 234
		topic = "smtp";
I 234
		message("214-This is Sendmail version %s", Version);
		noinfo = FALSE;
	}
E 234
	else
I 234
	{
E 234
		makelower(topic);
I 234
		noinfo = TRUE;
	}
E 234

E 96
	len = strlen(topic);
D 96
	makelower(topic);
E 96
D 234
	noinfo = TRUE;
E 234

	while (fgets(buf, sizeof buf, hf) != NULL)
	{
		if (strncmp(buf, topic, len) == 0)
		{
			register char *p;

D 104
			p = index(buf, '\t');
E 104
I 104
			p = strchr(buf, '\t');
E 104
			if (p == NULL)
				p = buf;
			else
				p++;
			fixcrlf(p, TRUE);
D 121
			message("214-", p);
E 121
I 121
			message("214-%s", p);
E 121
			noinfo = FALSE;
		}
	}

	if (noinfo)
D 121
		message("504", "HELP topic unknown");
E 121
I 121
		message("504 HELP topic unknown");
E 121
	else
D 121
		message("214", "End of HELP info");
E 121
I 121
		message("214 End of HELP info");
E 121
D 6
	fclose(hf);
E 6
I 6
	(void) fclose(hf);
I 36
}
D 91
/*
**  ISWIZ -- tell us if we are a wizard
**
**	If not, print a nasty message.
**
**	Parameters:
**		none.
**
**	Returns:
**		TRUE if we are a wizard.
**		FALSE if we are not a wizard.
**
**	Side Effects:
**		Prints a 500 exit stat if we are not a wizard.
*/

I 64
D 71
#ifdef DEBUG
E 71
I 71
#ifdef WIZ
E 71

E 64
bool
iswiz()
{
	if (!IsWiz)
		message("500", "Mere mortals musn't mutter that mantra");
	return (IsWiz);
I 39
}
I 64

D 71
#endif DEBUG
E 71
I 71
#endif WIZ
E 91
E 71
E 64
/*
**  RUNINCHILD -- return twice -- once in the child, then in the parent again
**
**	Parameters:
**		label -- a string used in error messages
**
**	Returns:
**		zero in the child
**		one in the parent
**
**	Side Effects:
**		none.
*/

I 244
int
E 244
D 100
runinchild(label)
E 100
I 100
runinchild(label, e)
E 100
	char *label;
I 100
	register ENVELOPE *e;
E 100
{
	int childpid;

I 41
D 61
	if (OneXact)
		return (0);

E 41
	childpid = dofork();
	if (childpid < 0)
E 61
I 61
	if (!OneXact)
E 61
	{
D 61
		syserr("%s: cannot fork", label);
		return (1);
	}
	if (childpid > 0)
	{
D 41
		/* parent -- wait for child to complete */
E 41
		auto int st;
E 61
I 61
		childpid = dofork();
		if (childpid < 0)
		{
D 243
			syserr("%s: cannot fork", label);
E 243
I 243
			syserr("451 %s: cannot fork", label);
E 243
			return (1);
		}
		if (childpid > 0)
		{
			auto int st;
E 61
D 41
		int i;
E 41

D 41
		while ((i = wait(&st)) != childpid)
		{
			if (i < 0 && errno != EINTR)
				break;
		}
		if (i < 0)
E 41
I 41
D 61
		/* parent -- wait for child to complete */
		st = waitfor(childpid);
		if (st == -1)
E 41
			syserr("%s: lost child", label);
E 61
I 61
			/* parent -- wait for child to complete */
I 148
D 165
			setproctitle("srvrsmtp %s child wait", CurHostName);
E 165
I 165
D 247
			setproctitle("server %s child wait", CurHostName);
E 247
I 247
			setproctitle("server %s child wait", CurSmtpClient);
E 247
E 165
E 148
			st = waitfor(childpid);
			if (st == -1)
D 243
				syserr("%s: lost child", label);
E 243
I 243
				syserr("451 %s: lost child", label);
E 243
I 187
			else if (!WIFEXITED(st))
D 243
				syserr("%s: died on signal %d",
E 243
I 243
				syserr("451 %s: died on signal %d",
E 243
					label, st & 0177);
E 187
E 61

D 61
		/* if we exited on a QUIT command, complete the process */
		if (st == (EX_QUIT << 8))
			finis();
E 61
I 61
			/* if we exited on a QUIT command, complete the process */
D 197
			if (st == (EX_QUIT << 8))
E 197
I 197
			if (WEXITSTATUS(st) == EX_QUIT)
			{
				disconnect(1, e);
E 197
				finis();
I 197
			}
E 197
E 61

D 61
		return (1);
E 61
I 61
			return (1);
		}
		else
		{
			/* child */
			InChild = TRUE;
I 81
			QuickAbort = FALSE;
E 81
I 70
D 82
			clearenvelope(CurEnv);
E 82
I 82
D 100
			clearenvelope(CurEnv, FALSE);
E 100
I 100
			clearenvelope(e, FALSE);
E 100
E 82
E 70
		}
E 61
	}
D 61
	else
	{
		/* child */
		InChild = TRUE;
I 43
		clearenvelope(CurEnv);
E 61
I 57
D 70

D 61
		/* open alias database */
		initaliases(AliasFile, FALSE);
E 61
I 61
	/* child (or ONEX command specified) */
	clearenvelope(CurEnv);
E 70
E 61

E 57
E 43
D 61
		return (0);
	}
E 61
I 61
	/* open alias database */
D 100
	initaliases(AliasFile, FALSE);
E 100
I 100
D 153
	initaliases(AliasFile, FALSE, e);
E 153
I 153
D 163
	initaliases(FALSE, e);
E 163
I 163
	initmaps(FALSE, e);
E 163
E 153
E 100

	return (0);
E 61
E 39
E 36
I 9
}
/*
**  PADDRTREE -- print address tree
**
**	Used by VRFY and EXPD to dump the tree of addresses produced.
**
**	Parameters:
**		a -- address of root.
**
**	Returns:
**		none.
**
**	Side Effects:
**		prints the tree in a nice order.
*/

paddrtree(a)
	register ADDRESS *a;
{
	static ADDRESS *prev;
	static int lev;

	if (a == NULL)
		return;
	lev++;
	if (!bitset(QDONTSEND, a->q_flags))
	{
		if (prev != NULL)
		{
			if (prev->q_fullname != NULL)
				message("250-", "%s <%s>", prev->q_fullname, prev->q_paddr);
			else
				message("250-", "<%s>", prev->q_paddr);
		}
		prev = a;
	}
	paddrtree(a->q_child);
	paddrtree(a->q_sibling);
	if (--lev <= 0)
	{
		if (prev != NULL)
		{
			/* last one */
			if (prev->q_fullname != NULL)
				message("250", "%s <%s>", prev->q_fullname, prev->q_paddr);
			else
				message("250", "<%s>", prev->q_paddr);
			prev = NULL;
		}
		else
			message("550", "User unknown");
	}
E 9
E 6
E 4
}
I 12

D 104
# endif SMTP
E 104
I 104
# endif /* SMTP */
E 104
E 12
E 1
