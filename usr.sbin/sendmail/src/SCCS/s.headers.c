h42305
s 00001/00001/01398
d D 8.70 95/06/19 07:39:10 eric 208 207
c sigh.....  wrong string routine
e
s 00014/00003/01385
d D 8.69 95/06/18 12:36:46 eric 207 206
c avoid MIMEing RFC1049 messages
e
s 00009/00002/01379
d D 8.68 95/06/01 06:19:19 eric 206 205
c improved debug output
e
s 00006/00002/01375
d D 8.67 95/05/28 11:49:09 eric 205 204
c lint
e
s 00008/00000/01369
d D 8.66 95/05/27 11:19:49 eric 204 203
c headers with H_ACHECK set would never be propogated, even if proper
c flags were set
e
s 00002/00002/01367
d D 8.65 95/05/27 07:44:48 eric 203 202
c make USERDB be a 0/1 option instead of #ifdef/#ifndef
e
s 00010/00008/01359
d D 8.64 95/05/25 11:37:23 eric 202 201
c fix problem that caused Message-Id:s to sometimes not be logged
e
s 00002/00000/01365
d D 8.63 95/05/15 19:00:18 eric 201 200
c put MIME 8->7 bit conversions on a compile flag (default on for now)
e
s 00002/00003/01363
d D 8.62 95/05/15 09:15:44 eric 200 199
c MIME glitches
e
s 00013/00009/01353
d D 8.61 95/05/05 08:21:04 eric 199 198
c fix MIME problem: did header munging on interior headers
e
s 00006/00001/01356
d D 8.60 95/04/29 07:41:25 eric 198 197
c better (more accurate) labelling of 8bit code
e
s 00005/00000/01352
d D 8.59 95/04/25 09:58:22 eric 197 196
c assume that anything with MIME-Version: is MIME, even if it
c didn't come with BODY=8BITMIME in the envelope
e
s 00001/00001/01351
d D 8.58 95/04/21 09:56:46 eric 196 195
c update copyright notice
e
s 00005/00001/01347
d D 8.57 95/04/20 06:35:14 eric 195 194
c use xputs to print chompheader intro debugging output
e
s 00045/00006/01303
d D 8.56 95/04/09 17:54:04 eric 194 192
c auto-quote group names; hack around :: address
e
s 00050/00009/01300
d R 8.56 95/04/09 17:41:24 eric 193 192
c clean up group handling for sender & envelope addresses
e
s 00042/00004/01267
d D 8.55 95/04/09 13:46:28 eric 192 191
c fix handling of group phrase: addr1, addr2, ... addrN; syntax
e
s 00024/00006/01247
d D 8.54 95/04/03 09:31:12 eric 191 190
c clean up problems with MIME 8 to 7 bit conversions
e
s 00001/00001/01252
d D 8.53 95/04/02 09:28:28 eric 190 189
c MIME cleanup to get header line parsing right
e
s 00010/00005/01243
d D 8.52 95/03/30 15:26:01 eric 189 188
c make lines beginning with : look like non-headers instead of
c syntax errors
e
s 00004/00005/01244
d D 8.51 95/03/21 06:46:13 eric 188 187
c back out E qf line
e
s 00003/00003/01246
d D 8.50 95/03/14 09:10:38 eric 187 186
c change call to expand() to be more rational (and consistent!)
e
s 00005/00005/01244
d D 8.49 95/03/14 08:18:47 eric 186 185
c be more precise on MAXNAME checking
e
s 00009/00000/01240
d D 8.48 95/03/12 17:04:26 eric 185 184
c add 'j' mailer flag to rewrite recipient addresses
e
s 00007/00001/01233
d D 8.47 95/02/24 10:00:57 eric 184 183
c add NoRecipientAction; make Bcc: field truncate instead of delete
e
s 00002/00014/01232
d D 8.46 95/02/05 08:03:42 eric 183 182
c cut at 20 January version of DSN document
e
s 00001/00001/01245
d D 8.45 94/12/05 10:05:25 eric 182 181
c do sender logging as early as possible
e
s 00002/00002/01244
d D 8.44 94/11/22 22:24:43 eric 181 180
c clean up several small problems with file delivery, error detection,
c and return receipts
e
s 00003/00002/01243
d D 8.43 94/11/19 17:13:05 eric 180 179
c change PF_NOBODYPART to be more descriptive of what the flag
c actually does
e
s 00013/00002/01232
d D 8.42 94/11/19 16:57:26 eric 179 178
c remove Content-Type: header from returned messages if and only if
c no body is to be returned -- this could confuse mail readers
e
s 00017/00002/01217
d D 8.41 94/11/11 08:09:35 eric 178 177
c translate newlines to space in logged message-id to avoid
c syslog truncations
e
s 00001/00002/01218
d D 8.40 94/11/08 11:48:53 eric 177 176
c allow per-mailer default character set (applies to INCOMING mailer)
e
s 00013/00004/01207
d D 8.39 94/11/06 13:09:34 eric 176 175
c create proper headers on MIME mail (not just MIME-Version:)
e
s 00014/00000/01197
d D 8.38 94/11/05 12:27:43 eric 175 174
c tweak EightBitMode and F=8 options to do something useful
e
s 00004/00003/01193
d D 8.37 94/10/08 09:25:18 eric 174 173
c avoid null pointer dereferences in some degenerate cases
e
s 00019/00000/01177
d D 8.36 94/08/21 15:25:39 eric 173 172
c multiple queue timeouts
e
s 00010/00001/01167
d D 8.35 94/08/17 08:10:00 eric 172 171
c add H_CTE for content-transfer-encoding; don't output it when you
c are going to be doing 8to7 bit MIME translation, which will add one
e
s 00018/00016/01150
d D 8.34 94/07/23 07:59:21 eric 171 170
c MIME 8 to 7 bit support
e
s 00001/00001/01165
d D 8.33 94/07/03 11:47:47 eric 170 169
c break out special local mail processing (e.g., mapping to the
c "prog" mailer) onto separate mailer flags
e
s 00009/00000/01157
d D 8.32 94/04/14 09:42:39 eric 169 168
c give return-receipt on delivery to mailing lists (instead of to the
c members of that list) and suppress Return-Receipt-To: in subsequent
c deliveries to avoid denial of service attacks and generally improve
c the semantics
e
s 00002/00000/01155
d D 8.31 94/04/12 08:38:23 eric 168 167
c updates for Intergraph CLIX
e
s 00002/00002/01153
d D 8.30 94/02/25 14:56:23 eric 167 166
c efficiency hacks
e
s 00003/00003/01152
d D 8.29 94/02/25 10:16:27 eric 166 165
c avoid wrapping header lines too eagerly
e
s 00004/00004/01151
d D 8.28 94/02/16 16:34:06 eric 165 164
c better patch of MAYBENEXTRELEASE problem
e
s 00010/00000/01145
d D 8.27 94/02/16 11:24:06 eric 164 163
c fix a bug in MAYBENEXTRELEASE code -- it's not really fixed though
e
s 00005/00001/01140
d D 8.26 94/02/05 12:56:22 eric 163 162
c wrap headers and lines more intelligently (important for very
c short line lengths
e
s 00002/00000/01139
d D 8.25 94/02/05 12:29:42 eric 162 161
c allow $s to be set to NULL for locally generated mail
e
s 00026/00000/01113
d D 8.24 94/02/03 08:07:46 eric 161 160
c restore -ba mode for UK Grey book
e
s 00016/00019/01097
d D 8.23 94/01/24 08:01:30 eric 160 159
c move 7BIT information from per-mailer to per-connection so it can
c be tweaked based on the other end
e
s 00001/00001/01115
d D 8.22 94/01/13 15:36:45 eric 159 158
c patch to protocol logging for short syslog buffer sizes
e
s 00012/00003/01104
d D 8.21 94/01/12 12:38:43 eric 158 157
c some cleanup for short syslog buffers
e
s 00001/00001/01106
d D 8.20 94/01/06 10:15:15 eric 157 156
c fix to avoid turning ``<foo)'' into ``<$>'' instead of ``<$g>''
e
s 00013/00004/01094
d D 8.19 93/12/15 09:21:34 eric 156 155
c improve debug output
e
s 00071/00049/01027
d D 8.18 93/12/11 13:53:36 eric 155 154
c arrange to log sender in SMTP even if all RCPTs failed
e
s 00002/00001/01074
d D 8.17 93/12/10 17:19:53 eric 154 153
c add bufsize parameter to prescan
e
s 00018/00000/01057
d D 8.16 93/12/10 12:51:15 eric 153 152
c deal with possibility of very short syslog buffers (for SVR4)
e
s 00005/00005/01052
d D 8.15 93/12/10 12:31:19 eric 152 151
c accept Full-Name: header on input
e
s 00001/00002/01056
d D 8.14 93/11/29 08:38:02 eric 151 150
c handle quotes inside comments properly
e
s 00003/00002/01055
d D 8.13 93/10/24 10:34:32 eric 150 149
c fix "<<a>>" syntax
e
s 00012/00001/01045
d D 8.12 93/09/26 08:16:53 eric 149 148
c comments
e
s 00025/00000/01021
d D 8.11 93/08/25 13:21:19 eric 148 147
c add untested mapping of local envelope From: line
e
s 00010/00002/01011
d D 8.10 93/08/17 09:51:15 eric 147 146
c improved debugging
e
s 00009/00003/01004
d D 8.9 93/08/08 15:21:44 eric 146 145
c avoid null pointer dereference on h->h_value
e
s 00001/00001/01006
d D 8.8 93/08/08 12:51:39 eric 145 144
c more syntax checking
e
s 00008/00006/00999
d D 8.7 93/08/08 11:35:51 eric 144 143
c do better syntax checking on H config lines
e
s 00016/00003/00989
d D 8.6 93/08/08 11:00:39 eric 143 142
c deal with pairs of angle braces in addresses
e
s 00001/00001/00991
d D 8.5 93/08/07 13:25:12 eric 142 141
c auto-quote addresses with <> in them
e
s 00001/00004/00991
d D 8.4 93/08/07 11:57:31 eric 141 140
c fix some random bad code
e
s 00006/00000/00989
d D 8.3 93/07/16 10:28:32 eric 140 139
c clean up error handling, including concept of local error handling
e
s 00007/00001/00982
d D 8.2 93/07/11 06:52:20 eric 139 138
c huge number of changes for 8.2, including IRIX & Solaris portability;
c improved error checking; fix -m flag and add -O flag in maps; fix long
c DNS timeouts; relax safefile restrictions; add -X command line flag; etc.
e
s 00002/00002/00981
d D 8.1 93/06/07 10:30:27 bostic 138 137
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00982
d D 6.37 93/06/03 19:12:11 eric 137 136
c only use Errors-To: header if 'l' option is set
e
s 00012/00001/00971
d D 6.36 93/05/28 21:52:27 eric 136 135
c log protocol and body type
e
s 00000/00005/00972
d D 6.35 93/05/27 11:37:04 eric 135 134
c prototype functions
e
s 00019/00000/00958
d D 6.34 93/05/11 08:17:14 eric 134 133
c debugging in putheader
e
s 00002/00000/00956
d D 6.33 93/05/10 07:55:34 eric 133 132
c strip spaces off of beginning of message-id (in case it was folded)
c before logging
e
s 00012/00017/00944
d D 6.32 93/04/30 12:53:57 eric 132 131
c don't change alpha case on header field names
e
s 00000/00005/00961
d D 6.31 93/04/26 13:29:47 eric 131 130
c delete duplicate 8th bit stripping
e
s 00007/00002/00959
d D 6.30 93/04/19 09:19:32 eric 130 129
c change remotename to use flag bits instead of individual parameters;
c add a pstat parameter to return status information up
e
s 00003/00000/00958
d D 6.29 93/04/04 13:56:49 eric 129 128
c RFC 1413 (IDENT) protocol support
e
s 00007/00004/00951
d D 6.28 93/04/01 14:59:09 eric 128 127
c fixes to properly compute priority, nrcpts, etc. on requeued delivery
e
s 00004/00000/00951
d D 6.27 93/03/31 08:10:12 eric 127 126
c arrange to quote backslash as well as other special characters
e
s 00007/00002/00944
d D 6.26 93/03/24 07:21:51 eric 126 125
c clean up logging of email received from localhost
e
s 00003/00002/00943
d D 6.25 93/03/23 18:06:23 eric 125 124
c add X-Authentication-Warning: headers on possible attempts at forgery
e
s 00002/00002/00943
d D 6.24 93/03/19 16:24:17 eric 124 123
c initial hooks for ISO networking
e
s 00000/00001/00945
d D 6.23 93/03/19 12:59:26 eric 123 122
c don't free header values -- they are still accessible from
c BlankEnvelope
e
s 00005/00007/00941
d D 6.22 93/03/19 11:46:28 eric 122 121
c include a warning timeout after some interval; get rid of QueueRun
c global and put it in the envelope; some other minor bug fixes
e
s 00002/00002/00946
d D 6.21 93/03/18 10:56:12 eric 121 120
c restore e_sender as sending address sans decorations
e
s 00020/00007/00928
d D 6.20 93/03/17 09:54:32 eric 120 119
c early bind default headers
e
s 00001/00001/00934
d D 6.19 93/03/16 18:17:47 eric 119 118
c changed "received from" to "relay=" for consistency
e
s 00003/00001/00932
d D 6.18 93/03/13 22:52:27 eric 118 117
c change "received from" logging on internal error response
e
s 00001/00002/00932
d D 6.17 93/03/08 18:02:05 eric 117 116
c undo RESPONSE hack -- is it worthwhile?
e
s 00002/00001/00932
d D 6.16 93/03/07 16:15:35 eric 116 115
c clean up from= logging on internally generated responses
e
s 00001/00001/00932
d D 6.15 93/03/06 08:32:07 eric 115 114
c allow host on local addresses; don't do domain extension on
c return path, ever -- for <> addresses
e
s 00003/00005/00930
d D 6.14 93/03/01 12:43:39 eric 114 113
c changes for ESMTP; mostly better delimiter character pointer passing
e
s 00001/00003/00934
d D 6.13 93/02/28 11:03:04 eric 113 112
c changes for better logging of mail submitters
e
s 00023/00014/00914
d D 6.12 93/02/24 05:36:48 eric 112 111
c propagate alias owner information back to envelope sender
e
s 00002/00002/00926
d D 6.11 93/02/23 06:31:30 eric 111 110
c overhaul status of SMTP reply codes
e
s 00004/00000/00924
d D 6.10 93/02/22 17:02:24 eric 110 109
c don't log from= info on sendmail -t -bv
e
s 00000/00006/00924
d D 6.9 93/02/21 13:45:33 eric 109 108
c change $d to be current date, not origination date
e
s 00004/00003/00926
d D 6.8 93/02/20 13:46:24 eric 108 107
c close cached MCI connections after a fork; add p (privacy) and b
c (min blocks free) options; fix selfref code; clean up $#error format
e
s 00011/00010/00918
d D 6.7 93/02/18 20:22:09 eric 107 106
c move the meta-characters from C0 into C1 space
e
s 00004/00003/00924
d D 6.6 93/02/16 18:29:39 eric 106 105
c clean up log levels; allow IDA-style split header/envelope rewriting;
c extend arpatounix with more zones (but is this even needed?)
e
s 00008/00006/00919
d D 6.5 93/01/21 15:18:23 eric 105 104
c more environment problems; limit resource exhaustion; fix incorrect
c name in Connection timed out message; ANSI C fixes; log message sender on
c returned mail during queue run; count recipients properly; fix YP code;
c diagnose "message timed out" properly
e
s 00014/00005/00911
d D 6.4 93/01/18 14:32:11 eric 104 103
c implement arpatounix; log more info; allow nested $?...$|...$.;
c POSIX compatibility; handle SMTP MAIL command errors properly;
c do early diagnosis of .cf errors; adjust checkpointing; misc bugs
e
s 00001/00001/00915
d D 6.3 93/01/03 12:08:20 eric 103 102
c fix botch causing queued headers to have ?XX? prefixes
e
s 00022/00016/00894
d D 6.2 92/12/30 11:00:50 eric 102 101
c put return-receipt-to on a conf.c flag (but don't set it);
c fix minor syslog problem
e
s 00000/00000/00910
d D 6.1 92/12/21 16:08:06 eric 101 100
c Release 6
e
s 00001/00002/00909
d D 5.30 92/12/20 11:14:15 eric 100 99
c change random constants to be #defines
e
s 00011/00012/00900
d D 5.29 92/12/18 12:03:13 eric 99 98
c add NIS map type; log message-id in same line as from logging
e
s 00001/00001/00911
d D 5.28 92/12/16 22:53:03 eric 98 97
c fix auto-quoting screwup
e
s 00002/00002/00910
d D 5.27 92/12/15 12:34:38 eric 97 96
c dynamically allocate header fields (and more....); miscellaneous
c cleanup (mostly comments)
e
s 00001/00001/00911
d D 5.26 92/12/14 09:59:14 eric 96 95
c correct list of must-be-quoted characters
e
s 00008/00008/00904
d D 5.25 92/11/14 11:34:00 eric 95 94
c (partially) ANSI-fy it
e
s 00096/00024/00816
d D 5.24 92/11/13 18:09:00 eric 94 93
c try to do some syntax error corrections on errors in headers
e
s 00042/00004/00798
d D 5.23 92/11/13 16:04:16 eric 93 92
c *really* fix quoting in phrase part of addresses; eliminate #-style
c commenting in :include: and .forward files (parenthesized comments
c can be used instead)
e
s 00001/00001/00801
d D 5.22 92/11/04 12:14:43 eric 92 91
c fix a variety of small bugs noticed by bcx
e
s 00003/00001/00799
d D 5.21 92/07/12 14:39:00 eric 91 90
c lint
e
s 00030/00023/00770
d D 5.20 92/07/12 14:09:25 eric 90 89
c reduce number of instances of CurEnv by passing it as a parameter
e
s 00001/00001/00792
d D 5.19 92/07/12 12:55:56 eric 89 88
c fix latent bug in received logging printing
e
s 00007/00006/00786
d D 5.18 92/07/12 10:14:03 eric 88 87
c make eight-bit clean; backslashes are carried through as-is
e
s 00000/00014/00792
d D 5.17 92/01/18 07:57:12 eric 87 86
c drop mode a (ARPA FTP) -- NCP is gone forever.....
e
s 00070/00102/00736
d D 5.16 91/10/20 00:55:46 eric 86 85
c handle a wider range of syntaxes -- notably, angle brackets
c appearing in quotes and comments.
e
s 00001/00011/00837
d D 5.15 90/06/01 19:01:54 bostic 85 84
c new copyright notice
e
s 00003/00002/00845
d D 5.14 90/04/18 12:03:34 bostic 84 83
c increase MAXFIELD to 4K; bug report 4.3BSD/usr.lib/153
e
s 00000/00014/00847
d D 5.13 89/01/01 17:17:17 bostic 83 82
c remove DEBUG
e
s 00001/00001/00860
d D 5.12 88/11/17 22:02:18 karels 82 81
c more cleanup, fix some inappropriate syserr's
e
s 00013/00003/00848
d D 5.11 88/11/17 10:32:06 karels 81 80
c expunge debugging/nonstandard/trojan horse commands from smtp,
c logging attempts to use them; log name/address of host from which mail received
c ("mail from" may not include it or may lie); don't allow debug to affect
c permissions locally; change some of the non-system syserrs to syslog at lower
c priority; still need to unifdef remaining debug code
e
s 00011/00009/00840
d D 5.10 88/06/30 14:59:01 bostic 80 79
c install approved copyright notice
e
s 00016/00010/00833
d D 5.9 88/03/13 19:52:09 bostic 79 78
c add Berkeley specific header
e
s 00001/00002/00842
d D 5.8 88/03/13 18:21:38 bostic 78 77
c replace sameword with strcasecmp
e
s 00001/00001/00843
d D 5.7 85/09/21 16:23:56 eric 77 76
m 
c don't include ctime as part of priority, since the value affects the results of
c shouldqueue; we go back to adding ctime into the workcmpf in queue.c
e
s 00002/00002/00842
d D 5.6 85/09/21 14:44:21 eric 76 75
m 
c clean up priority handling, making several of the parameters configurable:
c y - WkRecipFact, z - WkClassFact, Z - WkTimeFact, Y - ForkQueueRuns; improve
c process title labelling; finish "errors to postmaster" option
e
s 00005/00002/00839
d D 5.5 85/09/19 00:45:09 eric 75 73
m 
c SMI changes (somewhat)
e
s 00010/00000/00841
d D 5.4.1.1 85/09/04 09:40:34 eric 74 73
m 
c save code to throw out invalid Sender: fields for validated senders
e
s 00001/00001/00840
d D 5.4 85/06/08 10:27:07 eric 73 72
m 
c lint for 4.3 release
e
s 00005/00005/00836
d D 5.3 85/06/08 00:03:06 eric 72 71
m 
c lint
e
s 00000/00004/00841
d D 5.2 85/06/07 22:28:45 miriam 71 70
m 
c Resolve duplicate SccsId.  Remove unused variable.
e
s 00014/00000/00831
d D 5.1 85/06/07 15:06:13 dist 70 69
m 
c Add copyright
e
s 00001/00001/00830
d D 4.6 85/05/24 10:54:55 eric 69 68
m 
c Changes from Bill Nowicki <sun!rose!nowicki> and Jay Lepreau <lepreau@utah-cs>:
c Fix "bad file number" problem; improve error reporting; try to keep messages
c closer to their original order.  Also, drop "safe" mode in readcf since we
c never run setuid when -C is specified.
e
s 00002/00001/00829
d D 4.5 84/08/11 23:18:02 eric 68 66
m 
c Add $[ and $] as RHS operators to look up the contents and pass them
c to maphostname; maphostname currently looks them up in /etc/hosts and
c converts them to canonical form, but could be turned into a general
c name server.....   huzzah!!
e
s 00000/00000/00830
d R 4.4.1.1 84/06/17 16:17:05 eric 67 66
m 
c abortive attempt to install a name server.... sigh.
e
s 00001/00001/00829
d D 4.4 84/03/11 16:52:39 eric 66 65
m 
c change macro expansion character from $ to \001 so that $'s can be
c used in headers -- the .cf file is unchanged by mapping $ to \001.
c \001 is now a manifest constant.
e
s 00002/00003/00828
d D 4.3 83/08/21 15:39:52 eric 65 64
m 
c Drop "Sender:" hack, since it doesn't work properly when relaying messages.
e
s 00017/00015/00814
d D 4.2 83/08/21 15:12:30 eric 64 63
m 
c Insert Sender: line if a From: line is specified and is different from
c what we would otherwise put in.
e
s 00000/00000/00829
d D 4.1 83/07/25 19:43:48 eric 63 62
m 
c 4.2 release version
e
s 00001/00001/00828
d D 3.59 83/06/14 11:04:47 eric 62 61
m 
c log the message-id only if non-null
e
s 00012/00014/00817
d D 3.58 83/06/11 19:28:31 eric 61 60
m 045
m 240
c don't rearrange input header lines; force Received: lines to be at the
c beginning by always adding new header fields at the end of the header.
e
s 00001/00001/00830
d D 3.57 83/05/01 15:02:39 eric 60 59
m 234
c don't add an extra tab in the header (white space should already exist)
e
s 00013/00001/00818
d D 3.56 83/05/01 14:27:41 eric 59 58
m 234
c avoid core dumps on messages with very long header fields
e
s 00001/00001/00818
d D 3.55 83/04/17 17:11:36 eric 58 57
m 224
c fix *(0) problems
e
s 00001/00001/00818
d D 3.54 83/03/12 15:39:19 eric 57 56
m 207
c Don't artifically add a "from: $q" when running the queue -- this seems
c to cause the from line in the qf file to be ignored.
e
s 00029/00004/00790
d D 3.53 83/03/06 16:30:04 eric 56 55
m 201
c Handle messages with "Resent-xxx:" header lines properly (basically mark
c the message as being resent); ignore incoming From: lines if their text
c exactly matches our machine-readable address exactly -- this causes the
c full name to be added when called from (e.g.) MH.  Both of these mode are
c to improve interaction with MH.
e
s 00003/00002/00791
d D 3.52 83/02/26 15:30:58 eric 55 54
m 193
c Don't log message-id mapping and from person in a queue run
e
s 00027/00000/00766
d D 3.51 83/02/26 11:51:16 eric 54 53
m 193
c log queueid <=> message-id correspondence
e
s 00002/00002/00764
d D 3.50 83/02/19 14:42:00 eric 53 52
m 188
c Avoid core dumps on very long addresses in headers.
e
s 00008/00007/00758
d D 3.49 83/02/02 12:54:33 eric 52 51
m 165
c implement classes and mailer flags as a bit map; define new class 'w'
c as the set of all hosts we are known by
e
s 00001/00001/00764
d D 3.48 83/01/15 17:41:17 eric 51 50
m 149
c be sure everything gets appropriately externalized; canonname goes away,
c since everything is now done by remotename
e
s 00001/00001/00764
d D 3.47 83/01/06 12:05:36 eric 50 49
m 
c fix (one more time!) long line wrapping.....
e
s 00008/00021/00757
d D 3.46 83/01/06 10:49:20 eric 49 48
m 
c split up FULLSMTP flag -- now have "X" (M_XDOT, use hidden dot algorithm),
c "p" (M_FROMPATH, use reverse-path in MAIL FROM:<> command), and "L"
c (M_LIMITS, enforce SMTP line limits).  I would like to change the format
c of the mail defn one more time to make named fields so that it would
c be more extensible.
e
s 00005/00003/00773
d D 3.45 83/01/05 20:29:58 eric 48 47
m 
c fix folded line output
e
s 00005/00000/00771
d D 3.44 83/01/04 10:04:26 eric 47 46
m 
c Detect an internal error that seems to be occuring
e
s 00003/00003/00768
d D 3.43 83/01/03 13:00:30 eric 46 45
m 
c fix bug in commaize so that it won't core dump on every message (sigh)
e
s 00013/00007/00758
d D 3.42 83/01/01 21:26:16 eric 45 44
m 123
c Put CRLF on all lines in user SMTP.  Pass this info down to
c innumerable routines.
e
s 00002/00002/00763
d D 3.41 82/12/13 18:26:17 eric 44 43
m 085
c The routine "sendto" is now a system call (yeuch!); change our sendto
c to "sendtolist"
e
s 00274/00035/00491
d D 3.40 82/11/28 00:24:06 eric 43 42
m 
c Many changes resulting from a complete code readthrough.  Most of these
c fix minor bugs or change the internal structure for clarity, etc.  There
c should be almost no externally visible changes (other than some cleaner
c error message printouts and the like).
e
s 00001/00097/00525
d D 3.39 82/11/24 18:45:14 eric 42 41
m 
c lint it
e
s 00001/00001/00621
d D 3.38 82/11/24 17:16:51 eric 41 40
m 026
c run SMTP jobs in a subprocess so that multiple jobs will work.  This
c delta also changes the envelope data structure so that flags are in
c a bit map, and adjusts some of the semantics.  The transcript is now
c local to an envelope.  A bunch of old code is deleted.  A serious bug
c was fixed in the "run in background" code.  Etc., etc.
e
s 00001/00001/00621
d D 3.37 82/11/17 09:37:39 eric 40 39
m 060
c split operation mode ("-bx" flag) and delivery mode ("d" option)
c so that operation mode can apply to SMTP/daemon connections also.
e
s 00006/00004/00616
d D 3.36 82/11/04 13:27:38 eric 39 38
m 037
c put header conditionals into the .cf file
e
s 00012/00025/00608
d D 3.35 82/09/24 09:38:57 eric 38 37
c arrange to be able to define options; put precedences in .cf file;
c send errors to an Errors-To: field; fix a serious bug causing mail
c to not be delivered to anyone if there were any errors.
e
s 00001/00001/00632
d D 3.34 82/09/06 19:55:29 eric 37 36
c more hacking on oldstyle -- always assume sender fields are in new
c style so that locally generated fields are edited correctly.
e
s 00004/00002/00629
d D 3.33 82/09/06 18:24:29 eric 36 35
c fix botch in computing e_oldstyle
e
s 00011/00003/00620
d D 3.32 82/09/06 16:25:32 eric 35 34
c install new state-driven scanner; make everyone use it, thus fixing
c problems of quoted commas, etc.
e
s 00023/00094/00600
d D 3.31 82/09/05 18:05:05 eric 34 33
c convert Return-Receipt-To: and Precedence: to NBS standard; correctly
c process all sender fields
e
s 00009/00006/00685
d D 3.30 82/08/27 18:01:05 eric 33 32
c hack crackaddr to strip blanks off the end of a cracked address; this
c happens because "u at h" becomes "$g  " (with two spaces at the end).
c this doesn't solve the general case (e.g., "u at h (me)" comes out as
c "$g   (me)", with three spaces), but does handle the ugliest case.
c besides, the "at" syntax is supposed to go away.
e
s 00014/00014/00677
d D 3.29 82/08/25 16:19:32 eric 32 31
c apply ruleset 4 to rewrite addresses in the body of the message; fix
c a clock.c bug that caused it to lose events; more time cleanup.
e
s 00001/00012/00690
d D 3.28 82/08/23 09:24:17 eric 31 30
c allow continuation lines in .cf file (particularly in headers)
e
s 00000/00024/00702
d D 3.27 82/08/22 23:07:32 eric 30 29
c change $i to $j; $i is now queue id; put "Received:" format in .cf
c file; minor cleanup
e
s 00013/00005/00713
d D 3.26 82/08/22 19:03:25 eric 29 28
c assign a unique id to each transaction that can be determined from
c the queue file name.
e
s 00002/00002/00716
d D 3.25 82/08/17 20:45:03 eric 28 27
c Mail-From: ==> Received: for new SMTP spec (RFC821)
e
s 00379/00008/00339
d D 3.24 82/08/17 16:17:42 eric 27 26
c rework header processing: do special purpose header munging in a
c separate routine so that the queue run can do it also.  Also, parse
c From: lines in a fancy way, extracting the address part and turning
c it into a $g macro.
e
s 00001/00005/00346
d D 3.23 82/08/15 17:34:00 eric 26 25
c make headers work properly when a message is queued up; this involves
c expanding the header before it is written into the queue.  However, it
c also means that we don't have to store the macro definitions (?)
e
s 00034/00000/00317
d D 3.22 82/08/08 01:03:47 eric 25 24
c change debug level to a debug vector; add levels on logging (and the
c -L flag); change logging to be by message-id; elevate message-id;
c some lint-type cleanup
e
s 00001/00001/00316
d D 3.21 82/07/05 18:49:54 eric 24 23
c add "Apparently-To:" field if no recipients are in the header.
e
s 00004/00000/00313
d D 3.20 82/07/05 13:19:55 eric 23 22
c count Mail-From: lines to avoid loops (simulates hop counts)
e
s 00000/00000/00313
d D 3.19 82/05/31 15:32:56 eric 22 20
i 21
c finish implementing envelopes.  it's not completely clear to me that
c this is really the way to go, but it seems clearly better than what
c i had before.  this delta includes many other minor changes, so it
c should probably not be blithely removed.
e
s 00049/00000/00264
d D 3.18.1.1 82/05/29 18:21:10 eric 21 20
c try to install envelopes.  is this really worth it???
e
s 00005/00005/00259
d D 3.18 82/05/22 01:39:02 eric 20 19
c add "envelopes" to contain the basic information needed as control
c info for each message.  currently there is only one envelope -- this
c being the obvious stupid conversion.  later there will be separate
c envelopes for error messages, return receipts, etc.
e
s 00001/00001/00263
d D 3.17 82/03/06 12:09:40 eric 19 18
c clean up error handling in IPC case; fix a minor bug in headers in
c queueing code; make SMTP mail multi user per connect.
e
s 00006/00000/00258
d D 3.16 82/02/22 19:31:56 eric 18 17
c become NewStyle automatically based on heuristics
e
s 00067/00001/00191
d D 3.15 82/02/20 19:16:28 eric 17 15
c make rewriting of addresses in headers really work.  This adds the $q
c macro.  The rewriting of the From: address is still ad hoc and should
c be integrated into this format.
c Note:  old .cf files will not work with this version.
e
s 00020/00002/00190
d D 3.14.1.1 82/02/20 15:51:28 eric 16 15
c put the type address headers into a per-header send queue
e
s 00001/00001/00191
d D 3.14 81/12/06 12:40:07 eric 15 14
c cleanup so it will go through lint without any fancy grep -v's;
c change the way SCCS Id's are handled.
e
s 00009/00005/00183
d D 3.13 81/12/05 14:14:50 eric 14 13
c insert SMTP "Mail-From:" line.
e
s 00001/00001/00187
d D 3.12 81/11/22 19:18:08 eric 13 12
c Edit queue control files when running queue (assuming there are still
c recipients left).  Also, modify the MsgPriority to be the absolute
c number (not the Priority: value); this allows us to include aging into
c the priority algorithm.
e
s 00001/00001/00187
d D 3.11 81/11/21 18:43:47 eric 12 10
c change the send queue to be only one queue instead of one per mailer.
c this is slightly inefficient but simpler.  also, pass this queue
c around so we can have multiple send queues.  this makes VRFY work.
e
s 00002/00001/00187
d D 3.10.1.1 81/11/21 15:50:02 eric 11 10
c links together aliases into proper trees.  This is in part an
c attempt to do the SMTP VRFY command properly, but there are a number
c of annoying problems that convince me that this is the wrong way to
c do it.  Sigh.
e
s 00025/00005/00163
d D 3.10 81/10/26 14:23:07 eric 10 9
c Install new experimental queueing facility -- one stage timeout,
c etc.  This version is still quite incomplete.  It needs to reorder
c the queue after some interval, do two-stage timeout, take option
c info from the queue file instead of the command line, read the
c sender's .mailcf file, etc.  Some of this is useful for SMTP also.
e
s 00001/00001/00167
d D 3.9 81/09/16 16:24:22 eric 9 8
c last delta was too paranoid -- this increases the number of
c cases that work (but is still safe -- I hope)
e
s 00001/00001/00167
d D 3.8 81/09/16 16:08:21 eric 8 7
c run as the user forwarding mail after a .forward operation;
c fix a bug in .forwarding that caused recursive expansion;
c restrict mail to programs, files, and with :include: for security
c reasons.
e
s 00007/00004/00161
d D 3.7 81/09/12 15:49:17 eric 7 6
c change From: processing to reduce the number of Original-From:
c lines; change allocation of global variables.
e
s 00009/00000/00156
d D 3.6 81/09/06 19:49:24 eric 6 5
c cleanup, commenting, linting, etc.
e
s 00002/00000/00154
d D 3.5 81/08/24 14:06:17 eric 5 4
c Add "-t" option to read To:, Cc:, and Bcc: lines to get recipients
e
s 00004/00000/00150
d D 3.4 81/08/22 17:52:16 eric 4 3
c Arrange to pull full name out of From line if found; includes
c Original-From: hacking (oh so ugly).  There's got to be a better way
c to do this...
e
s 00000/00002/00150
d D 3.3 81/08/20 15:14:51 eric 3 2
c clean up some header information; don't reopen tempfile as
c stdin (to fix some problems with saving mail on interrupts)
e
s 00002/00001/00150
d D 3.2 81/08/17 09:37:58 eric 2 1
c add header fields from new BB&N proposal ICST/CBOS - 80-2,
c "Specification of a Draft Message Format Standard" for NBS.
e
s 00151/00000/00000
d D 3.1 81/08/09 16:40:48 eric 1 0
c date and time created 81/08/09 16:40:48 by eric
e
u
U
f b 
f i 
t
T
I 70
/*
I 80
D 196
 * Copyright (c) 1983 Eric P. Allman
E 196
I 196
 * Copyright (c) 1983, 1995 Eric P. Allman
E 196
E 80
D 79
**  Sendmail
**  Copyright (c) 1983  Eric P. Allman
**  Berkeley, California
**
**  Copyright (c) 1983 Regents of the University of California.
**  All rights reserved.  The Berkeley software License Agreement
**  specifies the terms and conditions for redistribution.
*/
E 79
I 79
D 138
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.
E 138
I 138
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 138
 *
D 85
 * Redistribution and use in source and binary forms are permitted
D 80
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
E 85
I 85
 * %sccs.include.redist.c%
E 85
E 80
 */
E 79

#ifndef lint
D 79
static char	SccsId[] = "%W% (Berkeley) %G%";
#endif not lint
E 79
I 79
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 79

I 84
D 100
# include <sys/param.h>
E 100
E 84
E 70
I 1
D 3
# include <stdio.h>
# include <ctype.h>
E 3
# include <errno.h>
# include "sendmail.h"

D 15
static char	SccsId[] = "%W%	%G%";
E 15
I 15
D 71
SCCSID(%W%	%Y%	%G%);
E 15

E 71
/*
**  CHOMPHEADER -- process and save a header line.
**
**	Called by collect and by readcf to deal with header lines.
**
**	Parameters:
**		line -- header as a text line.
**		def -- if set, this is a default value.
I 191
**		hdrp -- a pointer to the place to save the header.
E 191
I 90
**		e -- the envelope including this header.
E 90
**
**	Returns:
**		flags for this header.
**
**	Side Effects:
**		The header is saved on the header list.
I 6
**		Contents of 'line' are destroyed.
E 6
*/

I 205
int
E 205
D 90
chompheader(line, def)
E 90
I 90
D 191
chompheader(line, def, e)
E 191
I 191
chompheader(line, def, hdrp, e)
E 191
E 90
	char *line;
	bool def;
I 191
	HDR **hdrp;
E 191
I 90
	register ENVELOPE *e;
E 90
{
	register char *p;
	register HDR *h;
	HDR **hp;
D 31
	extern bool isheader();
E 31
	char *fname;
	char *fvalue;
	struct hdrinfo *hi;
I 39
	bool cond = FALSE;
I 191
	bool headeronly;
E 191
E 39
I 10
D 52
	u_long mopts;
	extern u_long mfencode();
E 52
I 52
	BITMAP mopts;
I 148
D 186
	char buf[MAXNAME];
E 186
I 186
	char buf[MAXNAME + 1];
E 186
E 148
E 52
I 27
D 32
	extern char *crackfrom();
E 32
I 32
D 93
	extern char *crackaddr();
E 93
E 32
E 27
I 11
	extern ADDRESS *sendto();
E 11
E 10

I 25
D 83
# ifdef DEBUG
E 83
	if (tTd(31, 6))
D 195
		printf("chompheader: %s\n", line);
E 195
I 195
	{
		printf("chompheader: ");
		xputs(line);
		printf("\n");
	}
E 195
D 83
# endif DEBUG
E 83

I 191
	headeronly = hdrp != NULL;
	if (!headeronly)
		hdrp = &e->e_header;

E 191
E 25
D 31
	/* strip off trailing newline */
	p = rindex(line, '\n');
	if (p != NULL)
		*p = '\0';

E 31
I 10
	/* strip off options */
D 52
	mopts = 0;
E 52
I 52
	clrbitmap(mopts);
E 52
	p = line;
D 92
	if (*p == '?')
E 92
I 92
D 103
	if (def && *p == '?')
E 103
I 103
	if (*p == '?')
E 103
E 92
	{
		/* have some */
D 95
		register char *q = index(p + 1, *p);
E 95
I 95
		register char *q = strchr(p + 1, *p);
E 95
		
		if (q != NULL)
		{
			*q++ = '\0';
D 52
			mopts = mfencode(p + 1);
E 52
I 52
			while (*++p != '\0')
				setbitn(*p, mopts);
E 52
			p = q;
		}
		else
D 82
			syserr("chompheader: syntax error, line \"%s\"", line);
E 82
I 82
D 111
			usrerr("chompheader: syntax error, line \"%s\"", line);
E 111
I 111
D 189
			usrerr("553 header syntax error, line \"%s\"", line);
E 189
I 189
			syserr("553 header syntax error, line \"%s\"", line);
E 189
E 111
E 82
I 39
		cond = TRUE;
E 39
	}

E 10
	/* find canonical name */
D 10
	fname = line;
	p = index(line, ':');
E 10
I 10
	fname = p;
D 95
	p = index(p, ':');
E 95
I 95
D 144
	p = strchr(p, ':');
E 95
I 47
	if (p == NULL)
E 144
I 144
	while (isascii(*p) && isgraph(*p) && *p != ':')
		p++;
	fvalue = p;
	while (isascii(*p) && isspace(*p))
		p++;
D 145
	if (*p++ != ':')
E 145
I 145
	if (*p++ != ':' || fname == fvalue)
E 145
E 144
	{
D 111
		syserr("chompheader: syntax error, line \"%s\"", line);
E 111
I 111
		syserr("553 header syntax error, line \"%s\"", line);
E 111
		return (0);
	}
E 47
E 10
D 144
	fvalue = &p[1];
D 107
	while (isspace(*--p))
E 107
I 107
	while (isascii(*--p) && isspace(*p))
E 107
		continue;
	*++p = '\0';
E 144
I 144
	*fvalue = '\0';
	fvalue = p;
E 144
D 132
	makelower(fname);
E 132

I 4
D 7
	/* hack, hack -- save the old From: address */
	if (!def && strcmp(fname, "from") == 0)
		fname = "original-from";

E 7
E 4
	/* strip field value on front */
	if (*fvalue == ' ')
		fvalue++;
I 7

D 27
	/* hack, hack -- save From: line specially */
D 19
	if (!def && strcmp(fname, "from") == 0)
E 19
I 19
D 26
	if (!def && !QueueRun && strcmp(fname, "from") == 0)
E 26
I 26
	if (!def && strcmp(fname, "from") == 0)
E 26
E 19
	{
D 20
		OrigFrom = newstr(fvalue);
E 20
I 20
		CurEnv->e_origfrom = newstr(fvalue);
E 20
		return (0);
	}
E 7

E 27
D 61
	/* search header list for this header */
E 61
I 61
D 64
	/* delete default value for this header */
E 61
D 20
	for (hp = &Header, h = Header; h != NULL; hp = &h->h_link, h = h->h_link)
E 20
I 20
D 43
	for (hp = &CurEnv->e_header, h = CurEnv->e_header; h != NULL; hp = &h->h_link, h = h->h_link)
E 43
I 43
	for (hp = &CurEnv->e_header, h = CurEnv->e_header; h != NULL;
		hp = &h->h_link, h = h->h_link)
E 43
E 20
	{
D 2
		if (strcmp(fname, h->h_field) == 0 && bitset(H_DEFAULT, h->h_flags))
E 2
I 2
D 14
		if (strcmp(fname, h->h_field) == 0 && bitset(H_DEFAULT, h->h_flags) &&
D 13
		    !bitset(H_FORCE, h->h_flags))
E 13
I 13
		    !(bitset(H_FORCE, h->h_flags) && !QueueRun))
E 14
I 14
D 61
		if (strcmp(fname, h->h_field) == 0 && bitset(H_DEFAULT, h->h_flags))
E 14
E 13
E 2
			break;
E 61
I 61
		if (strcmp(fname, h->h_field) == 0 &&
		    bitset(H_DEFAULT, h->h_flags) &&
		    !bitset(H_FORCE, h->h_flags))
			h->h_value = NULL;
E 61
	}

E 64
	/* see if it is a known type */
	for (hi = HdrInfo; hi->hi_field != NULL; hi++)
	{
D 132
		if (strcmp(hi->hi_field, fname) == 0)
E 132
I 132
		if (strcasecmp(hi->hi_field, fname) == 0)
E 132
			break;
	}

I 147
	if (tTd(31, 9))
	{
		if (hi->hi_field == NULL)
			printf("no header match\n");
		else
D 172
			printf("header match, hi_flags=%o\n", hi->hi_flags);
E 172
I 172
			printf("header match, hi_flags=%x\n", hi->hi_flags);
E 172
	}

E 147
I 56
	/* see if this is a resent message */
D 58
	if (!def && bitset(H_RESENT, h->h_flags))
E 58
I 58
D 191
	if (!def && bitset(H_RESENT, hi->hi_flags))
E 191
I 191
	if (!def && !headeronly && bitset(H_RESENT, hi->hi_flags))
E 191
E 58
D 90
		CurEnv->e_flags |= EF_RESENT;
E 90
I 90
		e->e_flags |= EF_RESENT;
E 90

I 188
	/* if this is an Errors-To: header keep track of it now */
D 191
	if (UseErrorsTo && !def && bitset(H_ERRORSTO, hi->hi_flags))
E 191
I 191
	if (UseErrorsTo && !def && !headeronly &&
	    bitset(H_ERRORSTO, hi->hi_flags))
E 191
		(void) sendtolist(fvalue, NULLADDR, &e->e_errorqueue, 0, e);

E 188
E 56
	/* if this means "end of header" quit now */
	if (bitset(H_EOH, hi->hi_flags))
		return (hi->hi_flags);
D 26

I 14
	/* don't put timestamps in every queue run */
	if (QueueRun && h != NULL && bitset(H_FORCE, h->h_flags))
		return (h->h_flags);
E 26

I 56
D 149
	/* drop explicit From: if same as what we would generate -- for MH */
E 149
I 149
	/*
	**  Drop explicit From: if same as what we would generate.
	**  This is to make MH (which doesn't always give a full name)
	**  insert the full name information in all circumstances.
	*/

E 149
D 57
	if (!def && strcmp(fvalue, CurEnv->e_from.q_paddr) == 0)
E 57
I 57
D 64
	if (!def && !QueueRun && strcmp(fvalue, CurEnv->e_from.q_paddr) == 0)
E 64
I 64
	p = "resent-from";
D 90
	if (!bitset(EF_RESENT, CurEnv->e_flags))
E 90
I 90
	if (!bitset(EF_RESENT, e->e_flags))
E 90
		p += 7;
D 122
	if (!def && !QueueRun && strcmp(fname, p) == 0)
E 122
I 122
D 132
	if (!def && !bitset(EF_QUEUERUN, e->e_flags) && strcmp(fname, p) == 0)
E 132
I 132
D 191
	if (!def && !bitset(EF_QUEUERUN, e->e_flags) && strcasecmp(fname, p) == 0)
E 191
I 191
	if (!def && !headeronly && !bitset(EF_QUEUERUN, e->e_flags) &&
	    strcasecmp(fname, p) == 0)
E 191
E 132
E 122
E 64
E 57
	{
I 139
		if (tTd(31, 2))
		{
			printf("comparing header from (%s) against default (%s or %s)\n",
				fvalue, e->e_from.q_paddr, e->e_from.q_user);
		}
E 139
I 65
D 71
		ADDRESS fromaddr;

E 71
E 65
D 64
		p = "resent-from";
		if (!bitset(EF_RESENT, CurEnv->e_flags))
			p += 7;
		if (strcmp(fname, p) == 0)
E 64
I 64
D 75
		if (strcmp(fvalue, CurEnv->e_from.q_paddr) == 0)
E 75
I 75
D 90
		if (CurEnv->e_from.q_paddr != NULL &&
		    strcmp(fvalue, CurEnv->e_from.q_paddr) == 0)
E 90
I 90
		if (e->e_from.q_paddr != NULL &&
D 139
		    strcmp(fvalue, e->e_from.q_paddr) == 0)
E 139
I 139
		    (strcmp(fvalue, e->e_from.q_paddr) == 0 ||
		     strcmp(fvalue, e->e_from.q_user) == 0))
E 139
E 90
E 75
E 64
			return (hi->hi_flags);
I 148
#ifdef MAYBENEXTRELEASE		/* XXX UNTESTED XXX UNTESTED XXX UNTESTED XXX */
D 203
#ifdef USERDB
E 203
I 203
#if USERDB
E 203
		else
		{
			auto ADDRESS a;
			char *fancy;
I 164
D 165
			bool oldHoldErrs = HoldErrs;
E 165
I 165
			bool oldSuprErrs = SuprErrs;
E 165
E 164
			extern char *crackaddr();
			extern char *udbsender();
I 149

			/*
			**  Try doing USERDB rewriting even on fully commented
			**  names; this saves the "comment" information (such
			**  as full name) and rewrites the electronic part.
I 164
			**
			** XXX	This code doesn't belong here -- parsing should
			** XXX	not be done during collect() phase because
			** XXX	error messages can confuse the SMTP phase.
D 165
			** XXX	Setting HoldErrs is a crude hack around this
E 165
I 165
			** XXX	Setting SuprErrs is a crude hack around this
E 165
			** XXX	problem.
E 164
			*/
E 149

I 164
			if (OpMode == MD_SMTP || OpMode == MD_ARPAFTP)
D 165
				HoldErrs = TRUE;
E 165
I 165
				SuprErrs = TRUE;
E 165
E 164
			fancy = crackaddr(fvalue);
			if (parseaddr(fvalue, &a, RF_COPYNONE, '\0', NULL, e) != NULL &&
D 170
			    a.q_mailer == LocalMailer &&
E 170
I 170
			    bitnset(M_CHECKUDB, a.q_mailer->m_flags) &&
E 170
			    (p = udbsender(a.q_user)) != NULL)
			{
				char *oldg = macvalue('g', e);

				define('g', p, e);
D 187
				expand(fancy, buf, &buf[sizeof buf], e);
E 187
I 187
				expand(fancy, buf, sizeof buf, e);
E 187
				define('g', oldg, e);
				fvalue = buf;
			}
I 164
D 165
			HoldErrs = oldHoldErrs;
E 165
I 165
			SuprErrs = oldSuprErrs;
E 165
E 164
		}
#endif
#endif
E 148
I 64
D 65

		/* different contents -- add a Sender: field */
		addheader("sender", "$q", CurEnv);
E 65
	}

I 74
	/* drop forged Sender: values */
	p = "resent-sender";
	if (!bitset(EF_RESENT, CurEnv->e_flags))
		p += 7;
	if (!def && !QueueRun && CurEnv->e_from.q_mailer == LocalMailer &&
	    bitset(H_VALID, hi->hi_flags))
	{
		return (hi->hi_flags);
	}

E 74
	/* delete default value for this header */
D 90
	for (hp = &CurEnv->e_header; (h = *hp) != NULL; hp = &h->h_link)
E 90
I 90
D 191
	for (hp = &e->e_header; (h = *hp) != NULL; hp = &h->h_link)
E 191
I 191
	for (hp = hdrp; (h = *hp) != NULL; hp = &h->h_link)
E 191
E 90
	{
D 132
		if (strcmp(fname, h->h_field) == 0 &&
E 132
I 132
		if (strcasecmp(fname, h->h_field) == 0 &&
E 132
		    bitset(H_DEFAULT, h->h_flags) &&
		    !bitset(H_FORCE, h->h_flags))
I 204
		{
E 204
			h->h_value = NULL;
I 204
			if (!cond)
			{
				/* copy conditions from default case */
				bcopy((char *)h->h_mflags, (char *)mopts,
						sizeof mopts);
			}
		}
E 204
E 64
	}

E 56
I 23
D 28
	/* count Mail-From: lines to avoid loops (simulate hop counts) */
	if (strcmp(fname, "mail-from") == 0)
E 28
I 28
D 43
	/* count Received: lines to avoid loops (simulate hop counts) */
D 34
	if (strcmp(fname, "received") == 0)
E 34
I 34
	if (bitset(H_TRACE, hi->hi_flags))
E 34
E 28
		HopCount++;

E 43
E 23
E 14
D 61
	/* create/fill in a new node */
D 14
	if (h == NULL)
E 14
I 14
	if (h == NULL || bitset(H_FORCE, h->h_flags))
E 14
	{
		/* create a new node */
D 14
		*hp = h = (HDR *) xalloc(sizeof *h);
E 14
I 14
		h = (HDR *) xalloc(sizeof *h);
E 14
		h->h_field = newstr(fname);
		h->h_value = NULL;
D 14
		h->h_link = NULL;
E 14
I 14
		h->h_link = *hp;
E 14
D 34
		h->h_flags = hi->hi_flags;
E 34
D 10
		h->h_mflags = hi->hi_mflags;
E 10
I 10
D 39
		h->h_mflags = mopts | hi->hi_mflags;
E 39
I 39
D 52
		h->h_mflags = mopts;
E 52
I 52
		bcopy(mopts, h->h_mflags, sizeof mopts);
E 52
E 39
I 14
		*hp = h;
E 14
E 10
	}
E 61
I 61
	/* create a new node */
	h = (HDR *) xalloc(sizeof *h);
	h->h_field = newstr(fname);
D 141
	h->h_value = NULL;
E 141
I 141
	h->h_value = newstr(fvalue);
E 141
	h->h_link = NULL;
D 73
	bcopy(mopts, h->h_mflags, sizeof mopts);
E 73
I 73
	bcopy((char *) mopts, (char *) h->h_mflags, sizeof mopts);
E 73
	*hp = h;
E 61
I 34
	h->h_flags = hi->hi_flags;
E 34
	if (def)
		h->h_flags |= H_DEFAULT;
D 10
	else
E 10
I 10
D 39
	else if (mopts == 0)
E 10
		h->h_flags &= ~H_CHECK;
E 39
I 39
	if (cond)
		h->h_flags |= H_CHECK;
E 39
D 141
	if (h->h_value != NULL)
D 42
		free(h->h_value);
E 42
I 42
		free((char *) h->h_value);
E 42
D 27
	h->h_value = newstr(fvalue);
E 27
I 27
D 34
	if (!def && strcmp(fname, "from") == 0)
	{
		/* turn it into a macro -- will be expanded later */
D 32
		h->h_value = newstr(crackfrom(fvalue));
E 32
I 32
		h->h_value = newstr(crackaddr(fvalue));
E 32
		h->h_flags |= H_DEFAULT;
	}
	else
		h->h_value = newstr(fvalue);
E 27
I 5
D 16
D 17
	if (!def && GrabTo && bitset(H_ADDR, h->h_flags))
E 17
I 17
	if (!def && GrabTo && bitset(H_RCPT, h->h_flags))
E 17
D 8
		sendto(h->h_value, 0);
E 8
I 8
D 9
		sendto(h->h_value, 0, &From);
E 9
I 9
D 10
		sendto(h->h_value, 0, NULL);
E 10
I 10
D 11
D 12
		sendto(h->h_value, 0, (ADDRESS *) NULL);
E 12
I 12
D 20
		sendto(h->h_value, 0, (ADDRESS *) NULL, &SendQueue);
E 20
I 20
		sendto(h->h_value, 0, (ADDRESS *) NULL, &CurEnv->e_sendqueue);
E 34
I 34
	h->h_value = newstr(fvalue);
E 141
E 34
E 20
E 16
I 16
	if (!def && bitset(H_ADDR, h->h_flags))
	{
		if (GrabTo)
			sendto(h->h_value, 0, (ADDRESS *) NULL, &SendQueue);
		if (!OldStyle)
			sendto(h->h_value, 0, (ADDRESS *) NULL, &h->h_addrq);
		else
		{
			p = fvalue;
			while (*p != '\0')
			{
				fvalue = p;
				while (*p != '\0' && !isspace(*p))
					p++;
				while (isspace(*p))
					*p++ = '\0';
				sendto(fvalue, 1, (ADDRESS *) NULL, &h->h_addrq);
			}
		}
	}
E 16
E 12
E 11
I 11
		(void) sendto(h->h_value, 0, (ADDRESS *) NULL, 0);
E 11
E 10
E 9
E 8
E 5

I 18
	/* hack to see if this is a new format message */
D 36
	if (bitset(H_RCPT, h->h_flags) &&
E 36
I 36
D 37
	if (!def && bitset(H_RCPT, h->h_flags) &&
E 37
I 37
D 191
	if (!def && bitset(H_RCPT|H_FROM, h->h_flags) &&
E 191
I 191
	if (!def && !headeronly && bitset(H_RCPT|H_FROM, h->h_flags) &&
E 191
E 37
E 36
D 95
	    (index(fvalue, ',') != NULL || index(fvalue, '(') != NULL ||
D 34
	     index(fvalue, '<') != NULL))
E 34
I 34
D 36
	     index(fvalue, '<') != NULL) || index(fvalue, ';') != NULL)
E 36
I 36
	     index(fvalue, '<') != NULL || index(fvalue, ';') != NULL))
E 95
I 95
	    (strchr(fvalue, ',') != NULL || strchr(fvalue, '(') != NULL ||
	     strchr(fvalue, '<') != NULL || strchr(fvalue, ';') != NULL))
E 95
	{
E 36
E 34
D 20
		OldStyle = FALSE;
E 20
I 20
D 41
		CurEnv->e_oldstyle = FALSE;
E 41
I 41
D 90
		CurEnv->e_flags &= ~EF_OLDSTYLE;
E 90
I 90
		e->e_flags &= ~EF_OLDSTYLE;
E 90
E 41
I 36
	}
E 36
E 20

I 34
D 56
	/* send to this person if we so desire */
	if (!def && GrabTo && bitset(H_RCPT, h->h_flags))
D 35
		sendto(h->h_value, 0, (ADDRESS *) NULL, &CurEnv->e_sendqueue);
E 35
I 35
D 44
		sendto(h->h_value, (ADDRESS *) NULL, &CurEnv->e_sendqueue);
E 44
I 44
		sendtolist(h->h_value, (ADDRESS *) NULL, &CurEnv->e_sendqueue);
E 44
E 35

E 56
E 34
E 18
	return (h->h_flags);
}
/*
I 21
**  ADDHEADER -- add a header entry to the end of the queue.
**
**	This bypasses the special checking of chompheader.
**
**	Parameters:
D 125
**		field -- the name of the header field.
**		value -- the value of the field.  It must be lower-cased.
E 125
I 125
D 132
**		field -- the name of the header field.  It must be
**			lower-cased.
E 132
I 132
**		field -- the name of the header field.
E 132
**		value -- the value of the field.
E 125
D 171
**		e -- the envelope to add them to.
E 171
I 171
**		hp -- an indirect pointer to the header structure list.
E 171
**
**	Returns:
**		none.
**
**	Side Effects:
**		adds the field on the list of headers for this envelope.
*/

I 205
void
E 205
D 171
addheader(field, value, e)
E 171
I 171
addheader(field, value, hdrlist)
E 171
	char *field;
	char *value;
D 171
	ENVELOPE *e;
E 171
I 171
	HDR **hdrlist;
E 171
{
	register HDR *h;
	register struct hdrinfo *hi;
	HDR **hp;

	/* find info struct */
	for (hi = HdrInfo; hi->hi_field != NULL; hi++)
	{
D 132
		if (strcmp(field, hi->hi_field) == 0)
E 132
I 132
		if (strcasecmp(field, hi->hi_field) == 0)
E 132
			break;
	}

	/* find current place in list -- keep back pointer? */
D 171
	for (hp = &e->e_header; (h = *hp) != NULL; hp = &h->h_link)
E 171
I 171
	for (hp = hdrlist; (h = *hp) != NULL; hp = &h->h_link)
E 171
	{
D 132
		if (strcmp(field, h->h_field) == 0)
E 132
I 132
		if (strcasecmp(field, h->h_field) == 0)
E 132
			break;
	}

	/* allocate space for new header */
	h = (HDR *) xalloc(sizeof *h);
	h->h_field = field;
	h->h_value = newstr(value);
D 24
	h->h_link = NULL;
E 24
I 24
	h->h_link = *hp;
E 24
	h->h_flags = hi->hi_flags | H_DEFAULT;
D 39
	h->h_mflags = hi->hi_mflags;
E 39
I 39
D 52
	h->h_mflags = 0;
E 52
I 52
	clrbitmap(h->h_mflags);
E 52
E 39
	*hp = h;
}
/*
E 21
**  HVALUE -- return value of a header.
**
**	Only "real" fields (i.e., ones that have not been supplied
**	as a default) are used.
**
**	Parameters:
**		field -- the field name.
I 90
D 171
**		e -- the envelope containing the header.
E 171
I 171
**		header -- the header list.
E 171
E 90
**
**	Returns:
**		pointer to the value part.
**		NULL if not found.
**
**	Side Effects:
D 43
**		sets the H_USED bit in the header if found.
E 43
I 43
**		none.
E 43
*/

char *
D 90
hvalue(field)
E 90
I 90
D 171
hvalue(field, e)
E 171
I 171
hvalue(field, header)
E 171
E 90
	char *field;
I 90
D 171
	register ENVELOPE *e;
E 171
I 171
	HDR *header;
E 171
E 90
{
	register HDR *h;

D 20
	for (h = Header; h != NULL; h = h->h_link)
E 20
I 20
D 90
	for (h = CurEnv->e_header; h != NULL; h = h->h_link)
E 90
I 90
D 171
	for (h = e->e_header; h != NULL; h = h->h_link)
E 171
I 171
	for (h = header; h != NULL; h = h->h_link)
E 171
E 90
E 20
	{
D 132
		if (!bitset(H_DEFAULT, h->h_flags) && strcmp(h->h_field, field) == 0)
E 132
I 132
		if (!bitset(H_DEFAULT, h->h_flags) &&
		    strcasecmp(h->h_field, field) == 0)
E 132
D 43
		{
			h->h_flags |= H_USED;
E 43
			return (h->h_value);
D 43
		}
E 43
I 25
	}
	return (NULL);
}
/*
D 42
**  HRVALUE -- return pointer to header descriptor.
**
**	Like hvalue except returns header descriptor block and isn't
**	picky about "real" headers.
**
**	Parameters:
**		field -- name of field we are interested in.
**
**	Returns:
**		pointer to header descriptor.
**
**	Side Effects:
**		none.
*/

HDR *
hrvalue(field)
	char *field;
{
	register HDR *h;

	for (h = CurEnv->e_header; h != NULL; h = h->h_link)
	{
		if (strcmp(h->h_field, field) == 0)
			return (h);
E 25
	}
	return (NULL);
}
/*
E 42
**  ISHEADER -- predicate telling if argument is a header.
**
I 6
**	A line is a header if it has a single word followed by
**	optional white space followed by a colon.
**
I 191
**	Header fields beginning with two dashes, although technically
**	permitted by RFC822, are automatically rejected in order
**	to make MIME work out.  Without this we could have a technically
**	legal header such as ``--"foo:bar"'' that would also be a legal
**	MIME separator.
**
E 191
E 6
**	Parameters:
D 189
**		s -- string to check for possible headerness.
E 189
I 189
**		h -- string to check for possible headerness.
E 189
**
**	Returns:
D 189
**		TRUE if s is a header.
E 189
I 189
**		TRUE if h is a header.
E 189
**		FALSE otherwise.
**
**	Side Effects:
**		none.
I 6
D 31
**
**	Bugs:
**		According to RFC733, there should be a newline
**		permitted after the word but before the colon.
**		We don't seem to support that.....
E 31
E 6
*/

bool
D 189
isheader(s)
	register char *s;
E 189
I 189
isheader(h)
	char *h;
E 189
{
I 189
	register char *s = h;
I 191

	if (s[0] == '-' && s[1] == '-')
		return FALSE;
E 191

E 189
D 43
	if (!isalnum(*s))
		return (FALSE);
D 31
	while (!isspace(*s) && *s != ':')
E 31
I 31
	while (!isspace(*s) && *s != ':' && *s != '\0')
E 43
I 43
	while (*s > ' ' && *s != ':' && *s != '\0')
E 43
E 31
		s++;
I 189

	if (h == s)
		return FALSE;
E 189
I 43

	/* following technically violates RFC822 */
E 43
D 107
	while (isspace(*s))
E 107
I 107
	while (isascii(*s) && isspace(*s))
E 107
		s++;
I 43

E 43
	return (*s == ':');
I 17
}
/*
D 42
**  GETXPART -- extract the "signature" part of an address line.
**
**	Try to extract the full name from a general address
**	field.  We take anything which is a comment as a
**	first choice.  Failing in that, we see if there is
**	a "machine readable" name (in <angle brackets>); if
**	so we take anything preceeding that clause.
**
**	If we blow it here it's not all that serious.
**
**	Parameters:
**		p -- line to crack.
**
**	Returns:
**		signature part.
**		NULL if no signature part.
**
**	Side Effects:
**		none.
*/

char *
getxpart(p)
	register char *p;
{
	register char *q;
	register char *rval = NULL;

	q = index(p, '(');
	if (q != NULL)
	{
		int parenlev = 0;

		for (p = q; *p != '\0'; p++)
		{
			if (*p == '(')
				parenlev++;
			else if (*p == ')' && --parenlev <= 0)
				break;
		}
		if (*p == ')')
		{
			*p = '\0';
			if (*++q != '\0')
				rval = newstr(q);
			*p = ')';
		}
	}
	else if ((q = index(p, '<')) != NULL)
	{
		char savec;

		while (*--q == ' ')
			continue;
		while (isspace(*p))
			p++;
		savec = *++q;
		*q = '\0';
		if (*p != '\0')
			rval = newstr(p);
		*q = savec;
	}

	return (rval);
I 27
}
/*
E 42
**  EATHEADER -- run through the stored header and extract info.
**
**	Parameters:
D 43
**		none.
E 43
I 43
**		e -- the envelope to process.
I 128
**		full -- if set, do full processing (e.g., compute
D 202
**			message priority).
E 202
I 202
**			message priority).  This should not be set
**			when reading a queue file because some info
**			needed to compute the priority is wrong.
E 202
E 128
I 105
D 122
**		queuejob -- set if running a queued job.
E 122
E 105
E 43
**
**	Returns:
**		none.
**
**	Side Effects:
**		Sets a bunch of global variables from information
D 43
**		in the collected header.
E 43
I 43
**			in the collected header.
**		Aborts the message if the hop count is exceeded.
E 43
*/

I 205
void
E 205
D 43
eatheader()
E 43
I 43
D 105
eatheader(e)
E 105
I 105
D 122
eatheader(e, queuejob)
E 122
I 122
D 128
eatheader(e)
E 128
I 128
eatheader(e, full)
E 128
E 122
E 105
	register ENVELOPE *e;
I 128
	bool full;
E 128
I 105
D 122
	bool queuejob;
E 122
E 105
E 43
{
	register HDR *h;
	register char *p;
I 43
	int hopcnt = 0;
I 99
	char *msgid;
D 120
	char msgidbuf[MAXNAME];
E 120
I 120
	char buf[MAXLINE];
E 120
E 99
E 43
D 42
	char buf[MAXLINE];
E 42
I 29
D 30
	char *msgid;
E 30
E 29

I 120
	/*
	**  Set up macros for possible expansion in headers.
	*/

D 121
	define('f', e->e_from.q_paddr, e);
	define('g', e->e_from.q_paddr, e);
E 121
I 121
	define('f', e->e_sender, e);
	define('g', e->e_sender, e);
I 143
	if (e->e_origrcpt != NULL && *e->e_origrcpt != '\0')
		define('u', e->e_origrcpt, e);
	else
		define('u', NULL, e);
E 143
E 121

I 152
	/* full name of from person */
D 171
	p = hvalue("full-name", e);
E 171
I 171
	p = hvalue("full-name", e->e_header);
E 171
	if (p != NULL)
		define('x', p, e);

E 152
E 120
D 43
# ifdef DEBUG
	if (tTd(32, 2))
E 43
I 43
D 83
#ifdef DEBUG
E 83
	if (tTd(32, 1))
		printf("----- collected header -----\n");
I 99
D 202
	msgid = "<none>";
E 202
I 202
	msgid = NULL;
E 202
E 99
D 83
#endif DEBUG
E 83
	for (h = e->e_header; h != NULL; h = h->h_link)
E 43
	{
I 206
		if (tTd(32, 1))
			printf("%s: ", h->h_field);
E 206
I 146
		if (h->h_value == NULL)
		{
			if (tTd(32, 1))
D 206
				printf("%s: <NULL>\n", h->h_field);
E 206
I 206
				printf("<NULL>\n");
E 206
			continue;
		}

E 146
I 43
D 83
#ifdef DEBUG
E 83
E 43
D 132
		extern char *capitalize();

E 132
I 120
		/* do early binding */
D 146
		if (bitset(H_DEFAULT, h->h_flags) && h->h_value != NULL)
E 146
I 146
		if (bitset(H_DEFAULT, h->h_flags))
E 146
		{
I 206
			if (tTd(32, 1))
			{
				printf("(");
				xputs(h->h_value);
				printf(") ");
			}
E 206
D 187
			expand(h->h_value, buf, &buf[sizeof buf], e);
E 187
I 187
			expand(h->h_value, buf, sizeof buf, e);
E 187
			if (buf[0] != '\0')
			{
D 123
				free(h->h_value);
E 123
				h->h_value = newstr(buf);
				h->h_flags &= ~H_DEFAULT;
			}
		}

E 120
D 43
		printf("----- collected header -----\n");
		for (h = CurEnv->e_header; h != NULL; h = h->h_link)
E 43
I 43
		if (tTd(32, 1))
E 43
D 132
			printf("%s: %s\n", capitalize(h->h_field), h->h_value);
E 132
I 132
D 156
			printf("%s: %s\n", h->h_field, h->h_value);
E 156
I 156
		{
D 206
			printf("%s: ", h->h_field);
E 206
			xputs(h->h_value);
			printf("\n");
		}
E 156
E 132
I 102

E 102
D 43
		printf("----------------------------\n");
E 43
I 43
D 83
#endif DEBUG
E 83
I 56
		/* count the number of times it has been processed */
E 56
		if (bitset(H_TRACE, h->h_flags))
			hopcnt++;
I 56

		/* send to this person if we so desire */
		if (GrabTo && bitset(H_RCPT, h->h_flags) &&
		    !bitset(H_DEFAULT, h->h_flags) &&
D 90
		    (!bitset(EF_RESENT, CurEnv->e_flags) || bitset(H_RESENT, h->h_flags)))
E 90
I 90
		    (!bitset(EF_RESENT, e->e_flags) || bitset(H_RESENT, h->h_flags)))
E 90
		{
I 140
			int saveflags = e->e_flags;

E 140
D 90
			sendtolist(h->h_value, (ADDRESS *) NULL, &CurEnv->e_sendqueue);
E 90
I 90
D 108
			sendtolist(h->h_value, (ADDRESS *) NULL,
				   &e->e_sendqueue, e);
E 108
I 108
D 147
			(void) sendtolist(h->h_value, (ADDRESS *) NULL,
E 147
I 147
			(void) sendtolist(h->h_value, NULLADDR,
E 147
D 181
					  &e->e_sendqueue, e);
E 181
I 181
					  &e->e_sendqueue, 0, e);
E 181
I 140

			/* delete fatal errors generated by this address */
D 143
			if (!bitset(EF_FATALERRS, saveflags))
E 143
I 143
			if (!GrabTo && !bitset(EF_FATALERRS, saveflags))
E 143
				e->e_flags &= ~EF_FATALERRS;
E 140
E 108
E 90
		}

D 99
		/* log the message-id */
E 56
I 54
#ifdef LOG
D 55
		if (strcmp(h->h_field, "message-id") == 0 && LogLevel > 8)
E 55
I 55
D 62
		if (!QueueRun && LogLevel > 8 &&
E 62
I 62
		if (!QueueRun && LogLevel > 8 && h->h_value != NULL &&
E 99
I 99
		/* save the message-id for logging */
D 105
		if (!QueueRun && h->h_value != NULL &&
E 105
I 105
D 122
		if (!queuejob && h->h_value != NULL &&
E 122
I 122
D 128
		if (!bitset(EF_QUEUERUN, e->e_flags) && h->h_value != NULL &&
E 128
I 128
D 146
		if (full && h->h_value != NULL &&
E 128
E 122
E 105
E 99
E 62
D 132
		    strcmp(h->h_field, "message-id") == 0)
E 132
I 132
		    strcasecmp(h->h_field, "message-id") == 0)
E 146
I 146
D 202
		if (full && strcasecmp(h->h_field, "message-id") == 0)
E 202
I 202
		if (strcasecmp(h->h_field, "message-id") == 0)
E 202
E 146
E 132
E 55
		{
D 99
			char buf[MAXNAME];

			p = h->h_value;
E 99
I 99
			msgid = h->h_value;
I 133
			while (isascii(*msgid) && isspace(*msgid))
				msgid++;
E 133
E 99
D 120
			if (bitset(H_DEFAULT, h->h_flags))
			{
D 99
				expand(p, buf, &buf[sizeof buf], e);
				p = buf;
E 99
I 99
				expand(msgid, msgidbuf,
					&msgidbuf[sizeof msgidbuf], e);
				msgid = msgidbuf;
E 99
			}
E 120
D 99
			syslog(LOG_INFO, "%s: message-id=%s", e->e_id, p);
E 99
		}
I 102

		/* see if this is a return-receipt header */
		if (bitset(H_RECEIPTTO, h->h_flags))
			e->e_receiptto = h->h_value;
D 188

		/* see if this is an errors-to header */
D 137
		if (bitset(H_ERRORSTO, h->h_flags))
E 137
I 137
		if (UseErrorsTo && bitset(H_ERRORSTO, h->h_flags))
E 137
D 108
			sendtolist(h->h_value, (ADDRESS *) NULL, &e->e_errorqueue, e);
E 108
I 108
D 147
			(void) sendtolist(h->h_value, (ADDRESS *) NULL,
E 147
I 147
			(void) sendtolist(h->h_value, NULLADDR,
E 147
D 181
					  &e->e_errorqueue, e);
E 181
I 181
					  &e->e_errorqueue, 0, e);
E 188
E 181
E 108
E 102
D 95
#endif LOG
E 95
I 95
D 99
#endif /* LOG */
E 99
E 95
E 54
E 43
	}
D 43
# endif DEBUG
E 43
I 43
D 83
#ifdef DEBUG
E 83
	if (tTd(32, 1))
		printf("----------------------------\n");
D 83
#endif DEBUG
E 83
E 43
D 30

	/* message id */
	h = hrvalue("message-id");
	if (h == NULL)
D 29
		syserr("No Message-Id spec");
E 29
I 29
		msgid = NULL;
E 29
	else if (bitset(H_DEFAULT, h->h_flags))
	{
		(void) expand(h->h_value, buf, &buf[sizeof buf - 1], CurEnv);
D 29
		MsgId = newstr(buf);
E 29
I 29
		msgid = buf;
E 29
	}
	else
D 29
		MsgId = h->h_value;
E 29
I 29
		msgid = h->h_value;
	if (msgid != NULL)
	{
E 29
# ifdef DEBUG
D 29
	if (tTd(32, 1))
		printf("Message-Id: %s\n", MsgId);
E 29
I 29
		if (tTd(32, 1))
			printf("Message-Id: %s\n", msgid);
E 29
# endif DEBUG
I 29
# ifdef LOG
		if (LogLevel > 1)
			syslog(LOG_INFO, "%s: messageid=%s", CurEnv->e_id, msgid);
# endif LOG
	}
E 30
E 29

I 110
	/* if we are just verifying (that is, sendmail -t -bv), drop out now */
	if (OpMode == MD_VERIFY)
		return;

E 110
I 43
	/* store hop count */
	if (hopcnt > e->e_hopcount)
		e->e_hopcount = hopcnt;

E 43
	/* message priority */
I 43
D 90
	p = hvalue("precedence");
E 90
I 90
D 171
	p = hvalue("precedence", e);
E 171
I 171
	p = hvalue("precedence", e->e_header);
E 171
E 90
	if (p != NULL)
		e->e_class = priencode(p);
I 202
	if (e->e_class < 0)
		e->e_timeoutclass = TOC_NONURGENT;
	else if (e->e_class > 0)
		e->e_timeoutclass = TOC_URGENT;
E 202
E 43
D 105
	if (!QueueRun)
E 105
I 105
D 122
	if (!queuejob)
E 122
I 122
D 128
	if (!bitset(EF_QUEUERUN, e->e_flags))
E 128
I 128
	if (full)
I 173
	{
E 173
E 128
E 122
E 105
D 43
	{
		/* adjust total priority by message priority */
		CurEnv->e_msgpriority = CurEnv->e_msgsize;
D 34
		p = hvalue("priority");
E 34
I 34
		p = hvalue("precedence");
E 34
		if (p != NULL)
			CurEnv->e_class = priencode(p);
D 38
		else
			CurEnv->e_class = PRI_NORMAL;
E 38
		CurEnv->e_msgpriority -= CurEnv->e_class * WKPRIFACT;
	}
E 43
I 43
D 69
		e->e_msgpriority = e->e_msgsize - e->e_class * WKPRIFACT;
E 69
I 69
D 75
		e->e_msgpriority = e->e_msgsize + e->e_ctime - e->e_class * WKPRIFACT;
E 75
I 75
D 77
		e->e_msgpriority = e->e_msgsize + e->e_ctime
E 77
I 77
		e->e_msgpriority = e->e_msgsize
E 77
D 76
				 - e->e_class * WKPRIFACT
				 + e->e_nrcpts * WKRECIPFACT;
E 76
I 76
				 - e->e_class * WkClassFact
				 + e->e_nrcpts * WkRecipFact;
I 173
D 202
		if (e->e_class < 0)
			e->e_timeoutclass = TOC_NONURGENT;
		else if (e->e_class > 0)
			e->e_timeoutclass = TOC_URGENT;
E 202
	}

	/* message timeout priority */
	p = hvalue("priority", e->e_header);
D 202
	if (full && p != NULL)
E 202
I 202
	if (p != NULL)
E 202
	{
		/* (this should be in the configuration file) */
		if (strcasecmp(p, "urgent"))
			e->e_timeoutclass = TOC_URGENT;
		else if (strcasecmp(p, "normal"))
			e->e_timeoutclass = TOC_NORMAL;
		else if (strcasecmp(p, "non-urgent"))
			e->e_timeoutclass = TOC_NONURGENT;
	}
E 173
E 76
E 75
E 69
E 43
D 152

D 34
	/* special handling */
	p = hvalue("special-handling");
E 34
I 34
D 102
	/* return receipt to */
D 90
	p = hvalue("return-receipt-to");
E 90
I 90
	p = hvalue("return-receipt-to", e);
E 90
E 34
	if (p != NULL)
D 34
		spechandling(p);
E 34
I 34
D 43
		CurEnv->e_receiptto = p;
E 43
I 43
		e->e_receiptto = p;
E 43
E 34

I 38
	/* errors to */
D 90
	p = hvalue("errors-to");
E 90
I 90
	p = hvalue("errors-to", e);
E 90
	if (p != NULL)
D 43
		sendto(p, (ADDRESS *) NULL, &CurEnv->e_errorqueue);
E 43
I 43
D 44
		sendto(p, (ADDRESS *) NULL, &e->e_errorqueue);
E 44
I 44
D 90
		sendtolist(p, (ADDRESS *) NULL, &e->e_errorqueue);
E 90
I 90
		sendtolist(p, (ADDRESS *) NULL, &e->e_errorqueue, e);
E 90
E 44
E 43

E 102
E 38
D 87
	/* from person */
D 34
	p = hvalue("sender");
	if (p == NULL)
		p = CurEnv->e_origfrom;
E 34
D 40
	if (ArpaMode)
E 40
I 40
	if (OpMode == MD_ARPAFTP)
E 40
D 34
		setfrom(p, (char *) NULL);
E 34
I 34
	{
		register struct hdrinfo *hi = HdrInfo;
E 34

I 34
		for (p = NULL; p == NULL && hi->hi_field != NULL; hi++)
		{
			if (bitset(H_FROM, hi->hi_flags))
				p = hvalue(hi->hi_field);
		}
		if (p != NULL)
D 43
			setfrom(p, (char *) NULL);
E 43
I 43
			setsender(p);
E 43
	}

E 87
E 34
	/* full name of from person */
D 90
	p = hvalue("full-name");
E 90
I 90
	p = hvalue("full-name", e);
E 90
	if (p != NULL)
D 43
		define('x', p);
E 43
I 43
		define('x', p, e);
E 152
E 43

	/* date message originated */
D 90
	p = hvalue("posted-date");
E 90
I 90
D 171
	p = hvalue("posted-date", e);
E 171
I 171
	p = hvalue("posted-date", e->e_header);
E 171
E 90
	if (p == NULL)
D 90
		p = hvalue("date");
E 90
I 90
D 171
		p = hvalue("date", e);
E 171
I 171
		p = hvalue("date", e->e_header);
E 171
E 90
	if (p != NULL)
D 109
	{
I 104
		extern char *arpatounix();

E 109
E 104
D 43
		define('a', p);
E 43
I 43
		define('a', p, e);
E 43
D 104
		/* we don't have a good way to do canonical conversion ....
D 43
		define('d', newstr(arpatounix(p)));
E 43
I 43
		define('d', newstr(arpatounix(p)), e);
E 43
		.... so we will ignore the problem for the time being */
E 104
I 104
D 109
		if ((p = arpatounix(p, e)) != NULL)
			define('d', newstr(p), e);
E 104
	}
E 109
I 54

I 197
	/* check to see if this is a MIME message */
D 198
	if ((e->e_bodytype != NULL && strcasecmp(e->e_bodytype, "8BITMIME") == 0) ||
E 198
I 198
D 207
	if ((e->e_bodytype != NULL &&
	     strcasecmp(e->e_bodytype, "8BITMIME") == 0) ||
E 198
	    hvalue("MIME-Version", e->e_header) != NULL)
E 207
I 207
	else if ((e->e_bodytype != NULL &&
		  strcasecmp(e->e_bodytype, "8BITMIME") == 0) ||
		 hvalue("MIME-Version", e->e_header) != NULL)
E 207
I 198
	{
E 198
		e->e_flags |= EF_IS_MIME;
I 198
		if (HasEightBits)
			e->e_bodytype = "8BITMIME";
	}
I 207
	else if ((p = hvalue("Content-Type", e->e_header)) != NULL)
	{
		/* this may be an RFC 1049 message */
D 208
		p = strtok(p, ";/");
E 208
I 208
		p = strpbrk(p, ";/");
E 208
		if (p == NULL || *p == ';')
		{
			/* yep, it is */
			e->e_flags |= EF_DONT_MIME;
		}
	}
E 207
E 198

E 197
	/*
I 161
	**  From person in antiquated ARPANET mode
	**	required by UK Grey Book e-mail gateways (sigh)
	*/

	if (OpMode == MD_ARPAFTP)
	{
		register struct hdrinfo *hi;

		for (hi = HdrInfo; hi->hi_field != NULL; hi++)
		{
			if (bitset(H_FROM, hi->hi_flags) &&
			    (!bitset(H_RESENT, hi->hi_flags) ||
			     bitset(EF_RESENT, e->e_flags)) &&
D 171
			    (p = hvalue(hi->hi_field, e)) != NULL)
E 171
I 171
			    (p = hvalue(hi->hi_field, e->e_header)) != NULL)
E 171
				break;
		}
		if (hi->hi_field != NULL)
		{
			if (tTd(32, 2))
				printf("eatheader: setsender(*%s == %s)\n",
					hi->hi_field, p);
			setsender(p, e, NULL, TRUE);
		}
	}

	/*
E 161
	**  Log collection information.
	*/

# ifdef LOG
D 55
	if (LogLevel > 1)
E 55
I 55
D 105
	if (!QueueRun && LogLevel > 1)
E 105
I 105
D 106
	if (!queuejob && LogLevel > 1)
E 106
I 106
D 122
	if (!queuejob && LogLevel > 4)
E 122
I 122
D 128
	if (!bitset(EF_QUEUERUN, e->e_flags) && LogLevel > 4)
E 128
I 128
D 182
	if (full && LogLevel > 4)
E 182
I 182
	if (bitset(EF_LOGSENDER, e->e_flags) && LogLevel > 4)
E 182
E 128
E 122
E 106
E 105
E 55
D 155
	{
I 102
		char *name;
I 136
		register char *sbp;
E 136
E 102
D 81
		syslog(LOG_INFO, "%s: from=%s, size=%ld, class=%d\n",
		       CurEnv->e_id, CurEnv->e_from.q_paddr, CurEnv->e_msgsize,
		       CurEnv->e_class);
E 81
I 81
D 91
		char hbuf[100], *name = hbuf;
E 91
I 91
D 100
		char hbuf[100];
E 100
I 100
		char hbuf[MAXNAME];
E 100
D 102
		char *name = hbuf;
		extern char *inet_ntoa();
E 102
I 102
		char sbuf[MAXLINE];
E 155
I 155
		logsender(e, msgid);
# endif /* LOG */
	e->e_flags &= ~EF_LOGSENDER;
}
/*
**  LOGSENDER -- log sender information
**
**	Parameters:
**		e -- the envelope to log
**		msgid -- the message id
**
**	Returns:
**		none
*/
E 155
I 129
D 135
		extern char *macvalue();
E 135
E 129
E 102
E 91

I 205
void
E 205
D 113
		if (RealHostName == NULL)
			name = "local";
		else if (RealHostName[0] == '[')
E 113
I 113
D 118
		if (RealHostName[0] == '[')
E 118
I 118
D 155
		if (bitset(EF_RESPONSE, e->e_flags))
			name = "[RESPONSE]";
I 129
		else if ((name = macvalue('_', e)) != NULL)
			;
E 129
		else if (RealHostName[0] == '[')
E 118
E 113
			name = RealHostName;
		else
E 155
I 155
logsender(e, msgid)
	register ENVELOPE *e;
	char *msgid;
{
I 168
# ifdef LOG
E 168
	char *name;
	register char *sbp;
	register char *p;
I 178
	int l;
E 178
D 186
	char hbuf[MAXNAME];
	char sbuf[MAXLINE];
I 178
	char mbuf[MAXNAME];
E 186
I 186
	char hbuf[MAXNAME + 1];
	char sbuf[MAXLINE + 1];
	char mbuf[MAXNAME + 1];
E 186
E 178

I 178
	/* don't allow newlines in the message-id */
	if (msgid != NULL)
	{
		l = strlen(msgid);
		if (l > sizeof mbuf - 1)
			l = sizeof mbuf - 1;
		bcopy(msgid, mbuf, l);
		mbuf[l] = '\0';
		p = mbuf;
		while ((p = strchr(p, '\n')) != NULL)
			*p++ = ' ';
	}

E 178
	if (bitset(EF_RESPONSE, e->e_flags))
		name = "[RESPONSE]";
	else if ((name = macvalue('_', e)) != NULL)
		;
I 162
	else if (RealHostName == NULL)
		name = "localhost";
E 162
	else if (RealHostName[0] == '[')
		name = RealHostName;
	else
	{
		name = hbuf;
		(void) sprintf(hbuf, "%.80s", RealHostName);
		if (RealHostAddr.sa.sa_family != 0)
E 155
I 102
		{
D 124
			extern char *inet_ntoa();
E 124
I 124
D 135
			extern char *anynet_ntoa();
E 124

E 135
D 155
			name = hbuf;
E 102
D 89
			(void)sprintf(hbuf, "%.90s (%s)", 
E 89
I 89
D 126
			(void)sprintf(hbuf, "%.80s (%s)", 
E 89
D 124
			    RealHostName, inet_ntoa(RealHostAddr.sin_addr));
E 124
I 124
			    RealHostName, anynet_ntoa(&RealHostAddr));
E 126
I 126
			(void) sprintf(hbuf, "%.80s", RealHostName);
			if (RealHostAddr.sa.sa_family != 0)
			{
				p = &hbuf[strlen(hbuf)];
				(void) sprintf(p, " (%s)",
					anynet_ntoa(&RealHostAddr));
			}
E 155
I 155
			p = &hbuf[strlen(hbuf)];
			(void) sprintf(p, " (%s)",
				anynet_ntoa(&RealHostAddr));
E 155
E 126
E 124
D 102
		syslog(LOG_INFO,
D 99
		    "%s: from=%s, size=%ld, class=%d, received from %s\n",
E 99
I 99
		    "%s: from=%s, size=%ld, class=%d, msgid=%s, received from %s\n",
E 99
D 90
		    CurEnv->e_id, CurEnv->e_from.q_paddr, CurEnv->e_msgsize,
		    CurEnv->e_class, name);
E 90
I 90
		    e->e_id, e->e_from.q_paddr, e->e_msgsize,
D 99
		    e->e_class, name);
E 99
I 99
		    e->e_class, msgid, name);
E 102
I 102
		}
I 155
	}
E 155

D 155
		/* some versions of syslog only take 5 printf args */
E 155
I 155
	/* some versions of syslog only take 5 printf args */
E 155
I 153
#  if (SYSLOG_BUFSIZE) >= 256
E 153
D 104
		sprintf(sbuf, "from=%.200s, size=%ld, class=%d, msgid=%.100s",
		    e->e_from.q_paddr, e->e_msgsize, e->e_class, msgid);
E 104
I 104
D 136
		sprintf(sbuf, "from=%.200s, size=%ld, class=%d, pri=%ld, nrcpts=%d, msgid=%.100s",
E 136
I 136
D 155
		sbp = sbuf;
		sprintf(sbp, "from=%.200s, size=%ld, class=%d, pri=%ld, nrcpts=%d, msgid=%.100s",
E 136
D 116
		    e->e_from.q_paddr, e->e_msgsize, e->e_class,
E 116
I 116
D 117
		    bitset(EF_RESPONSE, e->e_flags) ? "[RESPONSE]" : e->e_from.q_paddr,
		    e->e_msgsize, e->e_class,
E 117
I 117
		    e->e_from.q_paddr, e->e_msgsize, e->e_class,
E 117
E 116
		    e->e_msgpriority, e->e_nrcpts, msgid);
E 155
I 155
	sbp = sbuf;
	sprintf(sbp, "from=%.200s, size=%ld, class=%d, pri=%ld, nrcpts=%d",
D 174
	    e->e_from.q_paddr, e->e_msgsize, e->e_class,
	    e->e_msgpriority, e->e_nrcpts);
E 174
I 174
	    e->e_from.q_paddr == NULL ? "<NONE>" : e->e_from.q_paddr,
	    e->e_msgsize, e->e_class, e->e_msgpriority, e->e_nrcpts);
E 174
	sbp += strlen(sbp);
	if (msgid != NULL)
	{
D 178
		sprintf(sbp, ", msgid=%.100s", msgid);
E 178
I 178
		sprintf(sbp, ", msgid=%.100s", mbuf);
E 178
E 155
I 136
		sbp += strlen(sbp);
D 155
		if (e->e_bodytype != NULL)
		{
			(void) sprintf(sbp, ", bodytype=%.20s", e->e_bodytype);
			sbp += strlen(sbp);
		}
		p = macvalue('r', e);
		if (p != NULL)
			(void) sprintf(sbp, ", proto=%.20s", p);
E 136
E 104
D 106
		syslog(LOG_INFO, "%s: %s, received from %s\n",
E 106
I 106
D 119
		syslog(LOG_INFO, "%s: %s, received from %s",
E 119
I 119
		syslog(LOG_INFO, "%s: %s, relay=%s",
E 119
E 106
		    e->e_id, sbuf, name);
E 155
I 155
	}
	if (e->e_bodytype != NULL)
	{
		(void) sprintf(sbp, ", bodytype=%.20s", e->e_bodytype);
		sbp += strlen(sbp);
	}
	p = macvalue('r', e);
	if (p != NULL)
		(void) sprintf(sbp, ", proto=%.20s", p);
	syslog(LOG_INFO, "%s: %s, relay=%s",
	    e->e_id, sbuf, name);
E 155
I 153

#  else			/* short syslog buffer */

D 155
		syslog(LOG_INFO, "%s: from=%s",
			e->e_id, shortenstring(e->e_from.q_paddr, 83));
		syslog(LOG_INFO, "%s: size=%ld, class=%ld, pri=%ld, nrcpts=%d",
			e->e_id, e->e_msgsize, e->e_class,
			e->e_msgpriority, e->e_nrcpts);
E 155
I 155
	syslog(LOG_INFO, "%s: from=%s",
D 174
		e->e_id, shortenstring(e->e_from.q_paddr, 83));
E 174
I 174
		e->e_id, e->e_from.q_paddr == NULL ? "<NONE>" :
				shortenstring(e->e_from.q_paddr, 83));
E 174
	syslog(LOG_INFO, "%s: size=%ld, class=%ld, pri=%ld, nrcpts=%d",
		e->e_id, e->e_msgsize, e->e_class,
		e->e_msgpriority, e->e_nrcpts);
	if (msgid != NULL)
E 155
D 178
		syslog(LOG_INFO, "%s: msgid=%s", e->e_id, msgid);
E 178
I 178
		syslog(LOG_INFO, "%s: msgid=%s", e->e_id, mbuf);
E 178
I 158
	sbp = sbuf;
	sprintf(sbp, "%s:", e->e_id);
	sbp += strlen(sbp);
E 158
D 155
		if (e->e_bodytype != NULL)
			syslog(LOG_INFO, "%s: bodytype=%s",
				e->e_id, e->e_bodytype);
		p = macvalue('r', e);
		if (p != NULL)
			syslog(LOG_INFO, "%s: proto=%s", e->e_id, p);
		syslog(LOG_INFO, "%s: relay=%s", e->e_id, name);
E 155
I 155
	if (e->e_bodytype != NULL)
D 158
		syslog(LOG_INFO, "%s: bodytype=%s", e->e_id, e->e_bodytype);
E 158
I 158
	{
		sprintf(sbp, " bodytype=%s,", e->e_bodytype);
		sbp += strlen(sbp);
	}
E 158
	p = macvalue('r', e);
	if (p != NULL)
D 158
		syslog(LOG_INFO, "%s: proto=%s", e->e_id, p);
	syslog(LOG_INFO, "%s: relay=%s", e->e_id, name);
E 158
I 158
	{
D 159
		sprintf(sbp, " proto=%s,", e->e_id, p);
E 159
I 159
		sprintf(sbp, " proto=%s,", p);
E 159
		sbp += strlen(sbp);
	}
	syslog(LOG_INFO, "%s relay=%s", sbuf, name);
E 158
E 155
#  endif
I 168
# endif
E 168
E 153
E 102
E 99
E 90
E 81
D 155
	}
D 95
# endif LOG
E 95
I 95
# endif /* LOG */
E 155
E 95
E 54
}
/*
**  PRIENCODE -- encode external priority names into internal values.
**
**	Parameters:
**		p -- priority in ascii.
**
**	Returns:
**		priority as a numeric level.
**
**	Side Effects:
**		none.
*/

I 205
int
E 205
D 38
struct prio
{
	char	*pri_name;	/* external name of priority */
	int	pri_val;	/* internal value for same */
};

static struct prio	Prio[] =
{
	"alert",		PRI_ALERT,
	"quick",		PRI_QUICK,
	"first-class",		PRI_FIRSTCL,
	"normal",		PRI_NORMAL,
	"second-class",		PRI_SECONDCL,
	"third-class",		PRI_THIRDCL,
	"junk",			PRI_JUNK,
	NULL,			PRI_NORMAL,
};

E 38
priencode(p)
	char *p;
{
D 38
	register struct prio *pl;
E 38
I 38
	register int i;
E 38
D 78
	extern bool sameword();
E 78

D 38
	for (pl = Prio; pl->pri_name != NULL; pl++)
E 38
I 38
	for (i = 0; i < NumPriorities; i++)
E 38
	{
D 38
		if (sameword(p, pl->pri_name))
			break;
E 38
I 38
D 78
		if (sameword(p, Priorities[i].pri_name))
E 78
I 78
		if (!strcasecmp(p, Priorities[i].pri_name))
E 78
			return (Priorities[i].pri_val);
E 38
	}
D 38
	return (pl->pri_val);
E 38
I 38

	/* unknown priority */
	return (0);
E 38
D 34
}
/*
**  SPECHANDLE -- do special handling
**
**	Parameters:
**		p -- pointer to list of special handling words.
**
**	Returns:
**		none.
**
**	Side Effects:
**		Sets flags as indicated by p.
*/

struct handling
{
	char	*han_name;		/* word to get this magic */
	int	han_what;		/* what to do, see below */
};

/* modes for han_what */
# define	HAN_NONE	0	/* nothing special */
# define	HAN_RRECEIPT	1	/* give return receipt */

struct handling	Handling[] =
{
	"return-receipt-requested",	HAN_RRECEIPT,
	NULL,				HAN_NONE
};

spechandling(p)
	register char *p;
{
	register char *w;
	register struct handling *h;
	extern bool sameword();

	while (*p != '\0')
	{
		/* collect a word to compare to */
		while (*p != '\0' && (*p == ',' || isspace(*p)))
			p++;
		if (*p == '\0')
			break;
		w = p;
		while (*p != '\0' && *p != ',' && !isspace(*p))
			p++;
		if (*p != '\0')
			*p++ = '\0';

		/* scan the special handling table */
		for (h = Handling; h->han_name != NULL; h++)
			if (sameword(h->han_name, w))
				break;

		/* see if we can do anything interesting */
		switch (h->han_what)
		{
		  case HAN_NONE:	/* nothing to be done */
			break;

		  case HAN_RRECEIPT:	/* give return receipt */
			CurEnv->e_retreceipt = TRUE;
# ifdef DEBUG
			if (tTd(30, 3))
				printf(">>> Return receipt requested\n");
# endif DEBUG
			break;

		  default:
			syserr("spechandling: handling %d (%s)", h->han_what, w);
		}
	}
E 34
}
/*
D 32
**  CRACKFROM -- parse the from line and turn it into a macro
E 32
I 32
**  CRACKADDR -- parse an address and turn it into a macro
E 32
**
**	This doesn't actually parse the address -- it just extracts
**	it and replaces it with "$g".  The parse is totally ad hoc
**	and isn't even guaranteed to leave something syntactically
**	identical to what it started with.  However, it does leave
**	something semantically identical.
**
D 86
**	The process is kind of strange.  There are a number of
**	interesting cases:
**		1.  comment <address> comment	==> comment <$g> comment
**		2.  address			==> address
**		3.  address (comment)		==> $g (comment)
**		4.  (comment) address		==> (comment) $g
**	And then there are the hard cases....
**		5.  add (comment) ress		==> $g (comment)
**		6.  comment <address (comment)>	==> comment <$g (comment)>
**		7.    .... etc ....
E 86
I 86
**	This algorithm has been cleaned up to handle a wider range
**	of cases -- notably quoted and backslash escaped strings.
**	This modification makes it substantially better at preserving
**	the original syntax.
E 86
**
**	Parameters:
D 32
**		from -- the value part of the from line.
E 32
I 32
**		addr -- the address to be cracked.
E 32
**
**	Returns:
**		a pointer to the new version.
**
**	Side Effects:
D 32
**		The $f and $x macros may be defined.
E 32
I 32
**		none.
E 32
**
**	Warning:
**		The return value is saved in local storage and should
**		be copied if it is to be reused.
*/

char *
D 32
crackfrom(from)
	register char *from;
E 32
I 32
crackaddr(addr)
	register char *addr;
E 32
{
	register char *p;
D 86
	register int i;
	static char buf[MAXNAME];
	char *rhs;
	bool gotaddr;
E 86
I 86
	register char c;
	int cmtlev;
I 94
	int realcmtlev;
	int anglelev, realanglelev;
E 94
	int copylev;
	bool qmode;
I 94
	bool realqmode;
	bool skipping;
E 94
	bool putgmac = FALSE;
I 93
	bool quoteit = FALSE;
I 143
	bool gotangle = FALSE;
I 192
	bool gotcolon = FALSE;
E 192
E 143
E 93
E 86
	register char *bp;
I 94
	char *buflim;
I 192
	char *bufhead;
	char *addrhead;
E 192
E 94
I 86
D 186
	static char buf[MAXNAME];
E 186
I 186
	static char buf[MAXNAME + 1];
E 186
E 86

D 83
# ifdef DEBUG
E 83
	if (tTd(33, 1))
D 32
		printf("crackfrom(%s)\n", from);
E 32
I 32
		printf("crackaddr(%s)\n", addr);
E 32
D 83
# endif DEBUG
E 83

D 72
	strcpy(buf, "");
E 72
I 72
D 86
	(void) strcpy(buf, "");
E 72
	rhs = NULL;

E 86
I 35
	/* strip leading spaces */
D 107
	while (*addr != '\0' && isspace(*addr))
E 107
I 107
	while (*addr != '\0' && isascii(*addr) && isspace(*addr))
E 107
		addr++;

E 35
	/*
D 86
	**  See if we have anything in angle brackets.  If so, that is
	**  the address part, and the rest is the comment.
E 86
I 86
	**  Start by assuming we have no angle brackets.  This will be
	**  adjusted later if we find them.
E 86
	*/

D 32
	p = index(from, '<');
E 32
I 32
D 86
	p = index(addr, '<');
E 32
	if (p != NULL)
E 86
I 86
D 192
	bp = buf;
E 192
I 192
	bp = bufhead = buf;
E 192
I 94
	buflim = &buf[sizeof buf - 5];
E 94
D 192
	p = addr;
E 192
I 192
	p = addrhead = addr;
E 192
D 94
	copylev = cmtlev = 0;
	qmode = FALSE;
E 94
I 94
	copylev = anglelev = realanglelev = cmtlev = realcmtlev = 0;
	qmode = realqmode = FALSE;
E 94

	while ((c = *p++) != '\0')
E 86
	{
D 32
		/* copy the beginning of the from field to the buffer */
E 32
I 32
D 86
		/* copy the beginning of the addr field to the buffer */
E 32
		*p = '\0';
D 32
		strcpy(buf, from);
E 32
I 32
D 72
		strcpy(buf, addr);
E 32
		strcat(buf, "<");
E 72
I 72
		(void) strcpy(buf, addr);
		(void) strcat(buf, "<");
E 72
D 35
		*p = '<';
E 35
I 35
		*p++ = '<';
E 86
I 86
D 94
		if (copylev > 0 || c == ' ')
			*bp++ = c;
E 94
I 94
		/*
		**  If the buffer is overful, go into a special "skipping"
		**  mode that tries to keep legal syntax but doesn't actually
		**  output things.
		*/
E 94
E 86
E 35

I 93
D 94
		/* check for characters that may have to be quoted */
		if (index(".'@,;:[]", c) != NULL)
		{
			/*
			**  If these occur as the phrase part of a <>
			**  construct, but are not inside of () or already
			**  quoted, they will have to be quoted.  Note that
			**  now (but don't actually do the quoting).
			*/
E 94
I 94
		skipping = bp >= buflim;
E 94

D 94
			if (cmtlev <= 0 && !qmode)
				quoteit = TRUE;
		}
E 94
I 94
		if (copylev > 0 && !skipping)
			*bp++ = c;
E 94

E 93
I 35
D 86
		/* skip spaces */
		while (isspace(*p))
			p++;

E 35
		/* find the matching right angle bracket */
D 32
		from = ++p;
E 32
I 32
D 35
		addr = ++p;
E 35
I 35
		addr = p;
E 35
E 32
		for (i = 0; *p != '\0'; p++)
E 86
I 86
		/* check for backslash escapes */
		if (c == '\\')
E 86
		{
I 127
			/* arrange to quote the address */
			if (cmtlev <= 0 && !qmode)
				quoteit = TRUE;

E 127
D 86
			switch (*p)
E 86
I 86
			if ((c = *p++) == '\0')
E 86
			{
D 86
			  case '<':
				i++;
				break;

			  case '>':
				i--;
				break;
E 86
I 86
				/* too far */
				p--;
				goto putg;
E 86
			}
D 86
			if (i < 0)
				break;
E 86
I 86
D 94
			if (copylev > 0)
E 94
I 94
			if (copylev > 0 && !skipping)
E 94
				*bp++ = c;
			goto putg;
E 86
		}

D 86
		/* p now points to the closing quote (or a null byte) */
		if (*p != '\0')
E 86
I 86
		/* check for quoted strings */
D 151
		if (c == '"')
E 151
I 151
		if (c == '"' && cmtlev <= 0)
E 151
E 86
		{
D 86
			/* make rhs point to the extra stuff at the end */
			rhs = p;
			*p++ = '\0';
E 86
I 86
			qmode = !qmode;
I 94
			if (copylev > 0 && !skipping)
				realqmode = !realqmode;
E 94
			continue;
E 86
		}
D 86
	}
E 86
I 86
		if (qmode)
			goto putg;
E 86

D 86
	/*
D 33
	**  Now parse the real address part.  from points to the (null
E 33
I 33
	**  Now parse the real address part.  "addr" points to the (null
E 33
	**  terminated) version of what we are inerested in; rhs points
	**  to the extra stuff at the end of the line, if any.
	*/

D 32
	p = from;
E 32
I 32
	p = addr;
E 32

	/* now strip out comments */
	bp = &buf[strlen(buf)];
	gotaddr = FALSE;
	for (; *p != '\0'; p++)
	{
		if (*p == '(')
E 86
I 86
		/* check for comments */
		if (c == '(')
E 86
		{
D 86
			/* copy to matching close paren */
			*bp++ = *p++;
			for (i = 0; *p != '\0'; p++)
E 86
I 86
			cmtlev++;
D 94
			if (copylev++ <= 0)
				*bp++ = c;
E 94
I 94

			/* allow space for closing paren */
			if (!skipping)
			{
				buflim--;
				realcmtlev++;
				if (copylev++ <= 0)
				{
					*bp++ = ' ';
					*bp++ = c;
				}
			}
E 94
		}
		if (cmtlev > 0)
		{
			if (c == ')')
E 86
			{
D 86
				*bp++ = *p;
				switch (*p)
				{
				  case '(':
					i++;
					break;

				  case ')':
					i--;
					break;
				}
				if (i < 0)
					break;
E 86
I 86
				cmtlev--;
				copylev--;
I 94
				if (!skipping)
				{
					realcmtlev--;
					buflim++;
				}
E 94
E 86
			}
			continue;
		}
I 94
		else if (c == ')')
		{
			/* syntax error: unmatched ) */
D 157
			if (!skipping)
E 157
I 157
			if (copylev > 0 && !skipping)
E 157
				bp--;
		}
E 94
D 151

E 151
I 94

I 192
		/* check for group: list; syntax */
D 194
		if (c == ':' && anglelev <= 0 && !gotcolon && *p != ':' &&
		    !ColonOkInAddr)
E 194
I 194
		if (c == ':' && anglelev <= 0 && !gotcolon && !ColonOkInAddr)
E 194
		{
			register char *q;

I 194
			if (*p == ':')
			{
				/* special case -- :: syntax */
				if (cmtlev <= 0 && !qmode)
					quoteit = TRUE;
				if (copylev > 0 && !skipping)
				{
					*bp++ = c;
					*bp++ = c;
				}
				p++;
				goto putg;
			}

E 194
			gotcolon = TRUE;

D 194
			/* consider white space part of the group: part */
			while (isascii(*p) && isspace(*p))
				p++;
E 194
			bp = bufhead;
I 194
			if (quoteit)
			{
				*bp++ = '"';

				/* back up over the ':' and any spaces */
				--p;
				while (isascii(*--p) && isspace(*p))
					continue;
				p++;
			}
E 194
			for (q = addrhead; q < p; )
			{
				c = *q++;
				if (bp < buflim)
				{
I 194
					if (quoteit && c == '"')
						*bp++ = '\\';
E 194
					*bp++ = c;
				}
			}
I 194
			if (quoteit)
			{
				if (bp == &bufhead[1])
					bp--;
				else
					*bp++ = '"';
				while ((c = *p++) != ':')
				{
					if (bp < buflim)
						*bp++ = c;
				}
				*bp++ = c;
			}

			/* any trailing white space is part of group: */
			while (isascii(*p) && isspace(*p) && bp < buflim)
				*bp++ = *p++;
E 194
			copylev = 0;
D 194
			putgmac = FALSE;
E 194
I 194
			putgmac = quoteit = FALSE;
E 194
			bufhead = bp;
			addrhead = p;
			continue;
		}

		if (c == ';' && copylev <= 0 && !ColonOkInAddr)
		{
D 205
			register char *q = p;

E 205
			if (bp < buflim)
				*bp++ = c;
		}

E 192
		/* check for characters that may have to be quoted */
D 95
		if (index(".'@,;:[]", c) != NULL)
E 95
I 95
D 96
		if (strchr(".'@,;:[]", c) != NULL)
E 96
I 96
D 98
		if (strchr(".'@,;:\\[]<>()", c) != NULL)
E 98
I 98
D 142
		if (strchr(".'@,;:\\()", c) != NULL)
E 142
I 142
D 143
		if (strchr(".'@,;:\\()<>", c) != NULL)
E 143
I 143
		if (strchr(".'@,;:\\()[]", c) != NULL)
E 143
E 142
E 98
E 96
E 95
		{
			/*
			**  If these occur as the phrase part of a <>
			**  construct, but are not inside of () or already
			**  quoted, they will have to be quoted.  Note that
			**  now (but don't actually do the quoting).
			*/

			if (cmtlev <= 0 && !qmode)
				quoteit = TRUE;
		}

E 94
D 86
		/*
		**  If this is the first "real" character we have seen,
		**  then we put the "$g" in the buffer now.
		*/
E 86
I 86
		/* check for angle brackets */
		if (c == '<')
		{
I 93
			register char *q;

I 143
			/* assume first of two angles is bogus */
			if (gotangle)
				quoteit = TRUE;
			gotangle = TRUE;

E 143
E 93
			/* oops -- have to change our mind */
I 94
D 150
			anglelev++;
E 150
I 150
			anglelev = 1;
E 150
			if (!skipping)
D 150
				realanglelev++;
E 150
I 150
				realanglelev = 1;
E 150

E 94
D 93
			bcopy(addr, buf, p - addr);
			bp = &buf[p - addr];
E 93
I 93
D 192
			bp = buf;
E 192
I 192
			bp = bufhead;
E 192
			if (quoteit)
			{
				*bp++ = '"';

				/* back up over the '<' and any spaces */
				--p;
D 107
				while (isspace(*--p))
E 107
I 107
				while (isascii(*--p) && isspace(*p))
E 107
					continue;
				p++;
			}
D 192
			for (q = addr; q < p; )
E 192
I 192
			for (q = addrhead; q < p; )
E 192
			{
				c = *q++;
D 94
				if (quoteit && c == '"')
					*bp++ = '\\';
				*bp++ = c;
E 94
I 94
				if (bp < buflim)
				{
					if (quoteit && c == '"')
						*bp++ = '\\';
					*bp++ = c;
				}
E 94
			}
			if (quoteit)
			{
D 143
				*bp++ = '"';
E 143
I 143
				if (bp == &buf[1])
					bp--;
				else
					*bp++ = '"';
E 143
D 94
				while ((*bp++ = *p++) != '<')
					continue;
E 94
I 94
				while ((c = *p++) != '<')
				{
					if (bp < buflim)
						*bp++ = c;
				}
				*bp++ = c;
E 94
			}
E 93
			copylev = 0;
D 93
			putgmac = FALSE;
E 93
I 93
			putgmac = quoteit = FALSE;
E 93
			continue;
		}
E 86

D 86
		if (isspace(*p))
			*bp++ = *p;
		else if (!gotaddr)
E 86
I 86
		if (c == '>')
E 86
		{
I 94
			if (anglelev > 0)
			{
				anglelev--;
				if (!skipping)
				{
					realanglelev--;
					buflim++;
				}
			}
			else if (!skipping)
			{
				/* syntax error: unmatched > */
				if (copylev > 0)
					bp--;
I 150
				quoteit = TRUE;
E 150
				continue;
			}
E 94
D 66
			strcpy(bp, "$g");
E 66
I 66
D 72
			strcpy(bp, "\001g");
E 72
I 72
D 86
			(void) strcpy(bp, "\001g");
E 72
E 66
			bp += 2;
			gotaddr = TRUE;
E 86
I 86
			if (copylev++ <= 0)
				*bp++ = c;
			continue;
E 86
		}
D 86
	}
E 86

D 33
	/*
	**  If there is a tag at the end, insert it.
	*/
E 33
I 33
D 86
	/* hack, hack.... strip trailing blanks */
	do
	{
		*bp-- = '\0';
	} while (isspace(*bp));
	bp++;
E 33

D 33
	*bp = '\0';
E 33
I 33
	/* put any right hand side back on */
E 33
	if (rhs != NULL)
	{
		*rhs = '>';
D 72
		strcpy(bp, rhs);
E 72
I 72
		(void) strcpy(bp, rhs);
E 86
I 86
		/* must be a real address character */
	putg:
		if (copylev <= 0 && !putgmac)
		{
D 107
			*bp++ = '\001';
E 107
I 107
			*bp++ = MACROEXPAND;
E 107
			*bp++ = 'g';
			putgmac = TRUE;
		}
E 86
E 72
	}
I 86

I 94
	/* repair any syntactic damage */
	if (realqmode)
		*bp++ = '"';
	while (realcmtlev-- > 0)
		*bp++ = ')';
	while (realanglelev-- > 0)
		*bp++ = '>';
E 94
	*bp++ = '\0';
E 86

D 83
# ifdef DEBUG
E 83
	if (tTd(33, 1))
D 32
		printf("crackfrom=>%s\n", buf);
E 32
I 32
D 33
		printf("crackaddr=>%s\n", buf);
E 33
I 33
		printf("crackaddr=>`%s'\n", buf);
E 33
E 32
D 83
# endif DEBUG
E 83

	return (buf);
I 43
}
/*
**  PUTHEADER -- put the header part of a message from the in-core copy
**
**	Parameters:
D 160
**		fp -- file to put it on.
**		m -- mailer to use.
E 160
I 160
**		mci -- the connection information.
I 171
**		h -- the header to put.
E 171
E 160
**		e -- envelope to use.
I 179
D 183
**		flags -- to modify the behaviour.
E 183
E 179
I 45
D 49
**		crlf -- if set, output CRLF on the end of lines.
E 49
E 45
**
**	Returns:
**		none.
**
**	Side Effects:
**		none.
*/
I 104

/*
 * Macro for fast max (not available in e.g. DG/UX, 386/ix).
 */
#ifndef MAX
# define MAX(a,b) (((a)>(b))?(a):(b))
#endif
E 104

I 205
void
E 205
D 45
putheader(fp, m, e)
E 45
I 45
D 49
putheader(fp, m, e, crlf)
E 49
I 49
D 160
putheader(fp, m, e)
E 49
E 45
	register FILE *fp;
	register MAILER *m;
E 160
I 160
D 171
putheader(mci, e)
E 171
I 171
D 179
putheader(mci, h, e)
E 179
I 179
D 183
putheader(mci, h, e, flags)
E 183
I 183
putheader(mci, h, e)
E 183
E 179
E 171
	register MCI *mci;
I 171
	register HDR *h;
E 171
E 160
	register ENVELOPE *e;
I 179
D 183
	int flags;
E 183
E 179
{
D 84
	char buf[BUFSIZ];
E 84
I 84
D 97
	char buf[MAX(MAXFIELD,BUFSIZ)];
E 97
I 97
	char buf[MAX(MAXLINE,BUFSIZ)];
E 97
E 84
D 171
	register HDR *h;
E 171
D 105
	extern char *arpadate();
	extern char *capitalize();
E 105
D 84
	char obuf[MAXLINE];
E 84
I 84
D 97
	char obuf[MAX(MAXFIELD,MAXLINE)];
E 97
I 97
	char obuf[MAXLINE];
E 97
E 84
D 49
	bool fullsmtp = bitset(M_FULLSMTP, m->m_flags);
E 49

I 134
	if (tTd(34, 1))
D 160
		printf("--- putheader, mailer = %s ---\n", m->m_name);
E 160
I 160
		printf("--- putheader, mailer = %s ---\n",
			mci->mci_mailer->m_name);
E 160

E 134
D 171
	for (h = e->e_header; h != NULL; h = h->h_link)
E 171
I 171
	mci->mci_flags |= MCIF_INHEADER;
	for (; h != NULL; h = h->h_link)
E 171
	{
D 200
		register char *p;
E 200
I 200
		register char *p = h->h_value;
E 200
I 52
		extern bool bitintersect();
E 52

I 134
		if (tTd(34, 11))
		{
			printf("  %s: ", h->h_field);
D 200
			xputs(h->h_value);
E 200
I 200
			xputs(p);
E 200
		}

I 199
		/* suppress Content-Transfer-Encoding: if we are MIMEing */
		if (bitset(H_CTE, h->h_flags) &&
		    bitset(MCIF_CVT8TO7|MCIF_INMIME, mci->mci_flags))
		{
			if (tTd(34, 11))
				printf(" (skipped (content-transfer-encoding))\n");
			continue;
		}

		if (bitset(MCIF_INMIME, mci->mci_flags))
			goto vanilla;

E 199
E 134
		if (bitset(H_CHECK|H_ACHECK, h->h_flags) &&
D 52
		    !bitset(h->h_mflags, m->m_flags))
E 52
I 52
D 160
		    !bitintersect(h->h_mflags, m->m_flags))
E 160
I 160
		    !bitintersect(h->h_mflags, mci->mci_mailer->m_flags))
E 160
I 134
		{
			if (tTd(34, 11))
				printf(" (skipped)\n");
E 134
I 56
			continue;
I 134
		}
E 134

		/* handle Resent-... headers specially */
		if (bitset(H_RESENT, h->h_flags) && !bitset(EF_RESENT, e->e_flags))
I 134
		{
			if (tTd(34, 11))
				printf(" (skipped (resent))\n");
E 134
E 56
E 52
			continue;
I 134
		}
D 156
		if (tTd(34, 11))
			printf("\n");
E 156
E 134

I 169
		/* suppress return receipts if requested */
		if (bitset(H_RECEIPTTO, h->h_flags) &&
		    bitset(EF_NORECEIPT, e->e_flags))
		{
			if (tTd(34, 11))
				printf(" (skipped (receipt))\n");
I 172
			continue;
		}

I 179
D 183
		/* suppress Content-Type: if we are not including the body */
D 180
		if (bitset(PF_NOBODYPART, flags) && bitset(H_CTYPE, h->h_flags))
E 180
I 180
		if (bitset(PF_DELETEMIMEHDRS, flags) &&
		    bitset(H_CTYPE, h->h_flags))
E 180
		{
			if (tTd(34, 11))
				printf(" (skipped (content-type))\n");
			continue;
		}

E 183
E 179
D 199
		/* suppress Content-Transfer-Encoding: if we are MIMEing */
		if (bitset(H_CTE, h->h_flags) &&
D 179
		    bitset(MCIF_CVT8TO7, mci->mci_flags))
E 179
I 179
D 183
		    (bitset(MCIF_CVT8TO7, mci->mci_flags) ||
D 180
		     bitset(PF_NOBODYPART, flags)))
E 180
I 180
		     bitset(PF_DELETEMIMEHDRS, flags)))
E 183
I 183
		    bitset(MCIF_CVT8TO7, mci->mci_flags))
E 183
E 180
E 179
		{
			if (tTd(34, 11))
				printf(" (skipped (content-transfer-encoding))\n");
E 172
			continue;
		}

E 199
E 169
I 156
		/* macro expand value if generated internally */
E 156
D 200
		p = h->h_value;
E 200
		if (bitset(H_DEFAULT, h->h_flags))
		{
D 156
			/* macro expand value if generated internally */
E 156
D 187
			expand(p, buf, &buf[sizeof buf], e);
E 187
I 187
			expand(p, buf, sizeof buf, e);
E 187
			p = buf;
			if (p == NULL || *p == '\0')
I 156
			{
				if (tTd(34, 11))
					printf(" (skipped -- null value)\n");
E 156
				continue;
I 156
			}
E 156
		}
I 156

		if (tTd(34, 11))
			printf("\n");
E 156

D 184
		if (bitset(H_FROM|H_RCPT, h->h_flags))
E 184
I 184
		if (bitset(H_STRIPVAL, h->h_flags))
		{
			/* empty field */
			(void) sprintf(obuf, "%s:", h->h_field);
			putline(obuf, mci);
		}
		else if (bitset(H_FROM|H_RCPT, h->h_flags))
E 184
		{
			/* address field */
			bool oldstyle = bitset(EF_OLDSTYLE, e->e_flags);

			if (bitset(H_FROM, h->h_flags))
				oldstyle = FALSE;
D 45
			commaize(h, p, fp, oldstyle, m);
E 45
I 45
D 49
			commaize(h, p, fp, oldstyle, m, crlf);
E 49
I 49
D 90
			commaize(h, p, fp, oldstyle, m);
E 90
I 90
D 160
			commaize(h, p, fp, oldstyle, m, e);
E 160
I 160
			commaize(h, p, oldstyle, mci, e);
E 160
E 90
E 49
E 45
		}
		else
		{
			/* vanilla header line */
D 59
			(void) sprintf(obuf, "%s: %s\n", capitalize(h->h_field), p);
E 59
I 59
			register char *nlp;
I 105
D 132
			extern char *capitalize();
E 132
E 105

I 199
vanilla:
E 199
D 132
			(void) sprintf(obuf, "%s: ", capitalize(h->h_field));
E 132
I 132
			(void) sprintf(obuf, "%s: ", h->h_field);
E 132
D 95
			while ((nlp = index(p, '\n')) != NULL)
E 95
I 95
			while ((nlp = strchr(p, '\n')) != NULL)
E 95
			{
				*nlp = '\0';
				(void) strcat(obuf, p);
				*nlp = '\n';
D 160
				putline(obuf, fp, m);
E 160
I 160
				putline(obuf, mci);
E 160
				p = ++nlp;
D 60
				(void) strcpy(obuf, "\t");
E 60
I 60
				obuf[0] = '\0';
E 60
			}
			(void) strcat(obuf, p);
E 59
D 45
			putline(obuf, fp, fullsmtp);
E 45
I 45
D 49
			putline(obuf, fp, crlf, fullsmtp);
E 49
I 49
D 160
			putline(obuf, fp, m);
E 160
I 160
			putline(obuf, mci);
E 160
E 49
E 45
		}
	}
I 175

	/*
	**  If we are converting this to a MIME message, add the
D 176
	**  MIME-Version: header.
E 176
I 176
	**  MIME headers.
E 176
	*/

I 201
#if MIME8TO7
E 201
	if (bitset(MM_MIME8BIT, MimeMode) &&
	    bitset(EF_HAS8BIT, e->e_flags) &&
I 207
	    !bitset(EF_DONT_MIME, e->e_flags) &&
E 207
	    !bitnset(M_8BITS, mci->mci_mailer->m_flags) &&
D 176
	    !bitset(MCIF_CVT8TO7, mci->mci_flags) &&
	    hvalue("MIME-Version", e->e_header) == NULL)
E 176
I 176
	    !bitset(MCIF_CVT8TO7, mci->mci_flags))
E 176
	{
D 176
		putline("MIME-Version: 1.0", mci);
E 176
I 176
		if (hvalue("MIME-Version", e->e_header) == NULL)
			putline("MIME-Version: 1.0", mci);
		if (hvalue("Content-Type", e->e_header) == NULL)
		{
			sprintf(obuf, "Content-Type: text/plain; charset=%s",
D 177
				DefaultCharSet != NULL ? DefaultCharSet
						       : "unknown-8bit");
E 177
I 177
				defcharset(e));
E 177
			putline(obuf, mci);
		}
		if (hvalue("Content-Transfer-Encoding", e->e_header) == NULL)
			putline("Content-Transfer-Encoding: 8bit", mci);
E 176
	}
I 201
#endif
E 201
E 175
}
/*
**  COMMAIZE -- output a header field, making a comma-translated list.
**
**	Parameters:
**		h -- the header field to output.
**		p -- the value to put in it.
D 160
**		fp -- file to put it to.
E 160
**		oldstyle -- TRUE if this is an old style header.
D 160
**		m -- a pointer to the mailer descriptor.  If NULL,
**			don't transform the name at all.
E 160
I 160
**		mci -- the connection information.
E 160
I 90
**		e -- the envelope containing the message.
E 90
I 45
D 49
**		crlf -- set if we want CRLF's on the end of lines.
E 49
E 45
**
**	Returns:
**		none.
**
**	Side Effects:
**		outputs "p" to file "fp".
*/

D 45
commaize(h, p, fp, oldstyle, m)
E 45
I 45
D 49
commaize(h, p, fp, oldstyle, m, crlf)
E 49
I 49
D 90
commaize(h, p, fp, oldstyle, m)
E 90
I 90
D 160
commaize(h, p, fp, oldstyle, m, e)
E 160
I 160
void
commaize(h, p, oldstyle, mci, e)
E 160
E 90
E 49
E 45
	register HDR *h;
	register char *p;
D 160
	FILE *fp;
E 160
	bool oldstyle;
D 160
	register MAILER *m;
E 160
I 160
	register MCI *mci;
E 160
I 90
	register ENVELOPE *e;
E 90
I 45
D 49
	bool crlf;
E 49
E 45
{
	register char *obp;
	int opos;
I 163
	int omax;
E 163
D 49
	bool fullsmtp = FALSE;
E 49
	bool firstone = TRUE;
D 53
	char obuf[MAXLINE];
E 53
I 53
	char obuf[MAXLINE + 3];
I 105
D 132
	extern char *capitalize();
E 132
E 105
E 53

	/*
	**  Output the address list translated by the
	**  mailer and with commas.
	*/

D 83
# ifdef DEBUG
E 83
	if (tTd(14, 2))
		printf("commaize(%s: %s)\n", h->h_field, p);
D 83
# endif DEBUG
E 83

D 49
	if (m != NULL && bitset(M_FULLSMTP, m->m_flags))
		fullsmtp = TRUE;

E 49
	obp = obuf;
D 132
	(void) sprintf(obp, "%s: ", capitalize(h->h_field));
E 132
I 132
	(void) sprintf(obp, "%s: ", h->h_field);
E 132
	opos = strlen(h->h_field) + 2;
	obp += opos;
I 163
D 166
	omax = 78;
	if (mci->mci_mailer->m_linelimit - 2 < omax)
		omax = mci->mci_mailer->m_linelimit - 2;
E 166
I 166
	omax = mci->mci_mailer->m_linelimit - 2;
	if (omax < 0 || omax > 78)
		omax = 78;
E 166
E 163

	/*
	**  Run through the list of values.
	*/

	while (*p != '\0')
	{
		register char *name;
I 88
		register int c;
E 88
		char savechar;
I 130
		int flags;
		auto int stat;
E 130
D 135
		extern char *remotename();
E 135
D 114
		extern char *DelimChar;		/* defined in prescan */
E 114

		/*
		**  Find the end of the name.  New style names
		**  end with a comma, old style names end with
		**  a space character.  However, spaces do not
		**  necessarily delimit an old-style name -- at
		**  signs mean keep going.
		*/

		/* find end of name */
D 107
		while (isspace(*p) || *p == ',')
E 107
I 107
		while ((isascii(*p) && isspace(*p)) || *p == ',')
E 107
			p++;
		name = p;
		for (;;)
		{
D 114
			char *oldp;
E 114
I 114
			auto char *oldp;
E 114
I 68
			char pvpbuf[PSBUFSIZE];
E 68
D 112
			extern bool isatword();
E 112
D 135
			extern char **prescan();
E 135

D 68
			(void) prescan(p, oldstyle ? ' ' : ',');
E 68
I 68
D 114
			(void) prescan(p, oldstyle ? ' ' : ',', pvpbuf);
E 68
			p = DelimChar;
E 114
I 114
D 154
			(void) prescan(p, oldstyle ? ' ' : ',', pvpbuf, &oldp);
E 154
I 154
			(void) prescan(p, oldstyle ? ' ' : ',', pvpbuf,
D 190
				       sizeof pvpbuf, &oldp);
E 190
I 190
				       sizeof pvpbuf, &oldp, NULL);
E 190
E 154
			p = oldp;
E 114

			/* look to see if we have an at sign */
D 114
			oldp = p;
E 114
D 107
			while (*p != '\0' && isspace(*p))
E 107
I 107
			while (*p != '\0' && isascii(*p) && isspace(*p))
E 107
				p++;

D 112
			if (*p != '@' && !isatword(p))
E 112
I 112
			if (*p != '@')
E 112
			{
				p = oldp;
				break;
			}
			p += *p == '@' ? 1 : 2;
D 107
			while (*p != '\0' && isspace(*p))
E 107
I 107
			while (*p != '\0' && isascii(*p) && isspace(*p))
E 107
				p++;
		}
		/* at the end of one complete name */

		/* strip off trailing white space */
D 107
		while (p >= name && (isspace(*p) || *p == ',' || *p == '\0'))
E 107
I 107
		while (p >= name &&
		       ((isascii(*p) && isspace(*p)) || *p == ',' || *p == '\0'))
E 107
			p--;
		if (++p == name)
			continue;
		savechar = *p;
		*p = '\0';

		/* translate the name to be relative */
D 49
		if (m != NULL)
			name = remotename(name, m, bitset(H_FROM, h->h_flags));
E 49
I 49
D 51
		name = remotename(name, m, bitset(H_FROM, h->h_flags));
E 51
I 51
D 90
		name = remotename(name, m, bitset(H_FROM, h->h_flags), FALSE);
E 90
I 90
D 106
		name = remotename(name, m, bitset(H_FROM, h->h_flags), FALSE, e);
E 106
I 106
D 130
		name = remotename(name, m, bitset(H_FROM, h->h_flags),
D 115
				  TRUE, FALSE, e);
E 115
I 115
				  TRUE, FALSE, TRUE, e);
E 130
I 130
		flags = RF_HEADERADDR|RF_ADDDOMAIN;
		if (bitset(H_FROM, h->h_flags))
			flags |= RF_SENDERADDR;
I 185
D 203
#ifdef USERDB
E 203
I 203
#if USERDB
E 203
		else if (e->e_from.q_mailer != NULL &&
			 bitnset(M_UDBRECIPIENT, e->e_from.q_mailer->m_flags))
		{
			extern char *udbsender();

			name = udbsender(name);
		}
#endif
E 185
		stat = EX_OK;
D 160
		name = remotename(name, m, flags, &stat, e);
E 160
I 160
		name = remotename(name, mci->mci_mailer, flags, &stat, e);
E 160
E 130
E 115
E 106
E 90
E 51
E 49
		if (*name == '\0')
		{
			*p = savechar;
			continue;
		}

		/* output the name with nice formatting */
D 88
		opos += qstrlen(name);
E 88
I 88
		opos += strlen(name);
E 88
		if (!firstone)
			opos += 2;
D 163
		if (opos > 78 && !firstone)
E 163
I 163
		if (opos > omax && !firstone)
E 163
		{
I 48
D 49
			*obp = '\0';
			putline(obuf, fp, crlf, fullsmtp);
E 48
D 45
			(void) sprintf(obp, ",\n");
			putline(obuf, fp, fullsmtp);
E 45
I 45
D 46
			fputc(',', obp);
E 46
I 46
			fputc(',', fp);
E 46
			if (crlf)
D 46
				fputc('\r', obp);
			fputc('\n', obp);
E 46
I 46
				fputc('\r', fp);
			fputc('\n', fp);
E 49
I 49
D 50
			(void) strcat(obp, ",\n");
E 50
I 50
			(void) strcpy(obp, ",\n");
E 50
D 160
			putline(obuf, fp, m);
E 160
I 160
			putline(obuf, mci);
E 160
E 49
E 46
D 48
			putline(obuf, fp, crlf, fullsmtp);
E 48
E 45
			obp = obuf;
D 167
			(void) sprintf(obp, "        ");
E 167
I 167
			(void) strcpy(obp, "        ");
E 167
D 48
			obp += strlen(obp);
			opos = 8 + strlen(name);
E 48
I 48
			opos = strlen(obp);
			obp += opos;
D 88
			opos += qstrlen(name);
E 88
I 88
			opos += strlen(name);
E 88
E 48
		}
		else if (!firstone)
		{
D 167
			(void) sprintf(obp, ", ");
E 167
I 167
			(void) strcpy(obp, ", ");
E 167
			obp += 2;
		}

D 131
		/* strip off quote bits as we output */
E 131
D 53
		while (*name != '\0')
E 53
I 53
D 88
		while (*name != '\0' && obp < &obuf[MAXLINE])
E 88
I 88
		while ((c = *name++) != '\0' && obp < &obuf[MAXLINE])
E 88
E 53
D 131
		{
D 88
			if (bitset(0200, *name))
				*obp++ = '\\';
			*obp++ = *name++ & ~0200;
E 88
I 88
			if (bitnset(M_7BITS, m->m_flags))
				c &= 0177;
E 131
			*obp++ = c;
E 88
D 131
		}
E 131
		firstone = FALSE;
		*p = savechar;
	}
	(void) strcpy(obp, "\n");
D 45
	putline(obuf, fp, fullsmtp);
E 45
I 45
D 49
	putline(obuf, fp, crlf, fullsmtp);
E 49
I 49
D 160
	putline(obuf, fp, m);
E 160
I 160
	putline(obuf, mci);
E 160
E 49
E 45
}
/*
D 112
**  ISATWORD -- tell if the word we are pointing to is "at".
E 112
I 112
**  COPYHEADER -- copy header list
E 112
**
I 112
**	This routine is the equivalent of newstr for header lists
**
E 112
**	Parameters:
D 112
**		p -- word to check.
E 112
I 112
**		header -- list of header structures to copy.
E 112
**
**	Returns:
D 112
**		TRUE -- if p is the word at.
**		FALSE -- otherwise.
E 112
I 112
**		a copy of 'header'.
E 112
**
**	Side Effects:
**		none.
*/

D 112
bool
isatword(p)
	register char *p;
E 112
I 112
HDR *
copyheader(header)
	register HDR *header;
E 112
{
D 112
	extern char lower();
E 112
I 112
	register HDR *newhdr;
	HDR *ret;
	register HDR **tail = &ret;
E 112

D 112
	if (lower(p[0]) == 'a' && lower(p[1]) == 't' &&
D 107
	    p[2] != '\0' && isspace(p[2]))
E 107
I 107
	    p[2] != '\0' && isascii(p[2]) && isspace(p[2]))
E 107
		return (TRUE);
	return (FALSE);
E 112
I 112
	while (header != NULL)
	{
		newhdr = (HDR *) xalloc(sizeof(HDR));
		STRUCTCOPY(*header, *newhdr);
		*tail = newhdr;
		tail = &newhdr->h_link;
		header = header->h_link;
	}
	*tail = NULL;
	
	return ret;
E 112
E 43
E 27
E 17
}
E 1
