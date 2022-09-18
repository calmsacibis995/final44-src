h33305
s 00001/00001/02104
d D 8.73 95/06/19 07:38:44 eric 287 286
c fix bogus debug flag (apparently a typo)
e
s 00001/00000/02104
d D 8.72 95/06/10 07:37:19 eric 286 285
c need MF_KEEPQUOTES bit in dequote map, else it is double-dequoted
e
s 00001/00005/02103
d D 8.71 95/05/30 19:25:15 eric 285 284
c allow symbolic ruleset names on M lines (S= and R=)
e
s 00008/00005/02100
d D 8.70 95/05/28 11:49:26 eric 284 283
c lint
e
s 00003/00000/02102
d D 8.69 95/05/26 07:49:58 eric 283 282
c add -q map flag to avoid quote stripping; clean up domain addition
c in nis_getcanonname and nisplus_getcanonname
e
s 00001/00001/02101
d D 8.68 95/04/25 07:13:02 eric 282 281
c fix problem sending to user@domain where "domain" has an entry
c but no A or MX records; problem only occurs if it matches as the
c last entry in the resolver search list
e
s 00003/00002/02099
d D 8.67 95/04/23 14:02:36 eric 281 280
c updates for new DSN drafts
e
s 00067/00082/02034
d D 8.66 95/04/22 11:07:06 eric 280 279
c allow error mailer to take DSN status code
e
s 00001/00001/02115
d D 8.65 95/04/21 09:57:01 eric 279 277
c update copyright notice
e
s 00003/00001/02115
d R 8.65 95/04/09 17:41:31 eric 278 277
c clean up group handling for sender & envelope addresses
e
s 00099/00032/02017
d D 8.64 95/04/02 09:28:37 eric 277 276
c MIME cleanup to get header line parsing right
e
s 00001/00001/02048
d D 8.63 95/03/31 16:59:35 eric 276 275
c fix compile glitch
e
s 00015/00002/02034
d D 8.62 95/03/31 16:53:52 eric 275 274
c merge a bit with Sun version
e
s 00006/00002/02030
d D 8.61 95/03/27 09:25:29 eric 274 273
c more cleanup for DSN drafts
e
s 00001/00000/02031
d D 8.60 95/03/25 07:39:30 eric 273 272
c don't pass through NOTIFY= unless it was given in the SMTP RCPT
e
s 00000/00002/02031
d D 8.59 95/03/21 09:26:39 eric 272 270
c new DSN draft
e
s 00071/00034/01999
d D 8.58.1.1 95/03/14 18:38:04 eric 271 270
c hacks to make it more IDA-like -- they have other problems
e
s 00003/00003/02030
d D 8.58 95/03/14 09:10:48 eric 270 269
c change call to expand() to be more rational (and consistent!)
e
s 00005/00005/02028
d D 8.57 95/03/14 08:18:53 eric 269 268
c be more precise on MAXNAME checking
e
s 00002/00000/02031
d D 8.56 95/03/14 07:55:44 eric 268 267
c fix problem that can cause very long R lines in qf to core dump
e
s 00001/00001/02030
d D 8.55 95/02/24 07:49:05 eric 267 266
c minor ordering glitch, more pedantic than important
e
s 00002/00001/02029
d D 8.54 95/02/23 15:51:05 eric 266 265
c cleanup to make gcc -Winitialized happier
e
s 00001/00001/02029
d D 8.53 95/02/21 11:47:47 eric 265 264
c fix minor used-before-set problem
e
s 00009/00001/02021
d D 8.52 95/02/20 07:33:52 eric 264 263
c allow symbolic ruleset names
e
s 00001/00001/02021
d D 8.51 95/02/19 07:43:45 eric 263 262
c updated status codes for DSNs
e
s 00001/00001/02021
d D 8.50 95/02/19 06:46:07 eric 262 261
c fix prescan() function decl to match prototype
e
s 00001/00002/02021
d D 8.49 95/02/05 08:03:46 eric 261 260
c cut at 20 January version of DSN document
e
s 00002/00005/02021
d D 8.48 95/01/24 08:28:33 eric 260 259
c use wordinclass() abstraction for searching classes
e
s 00007/00007/02019
d D 8.47 94/12/28 07:08:48 eric 259 258
c allow $#local $: @ /filename
e
s 00001/00000/02025
d D 8.46 94/11/27 15:22:20 eric 258 257
c more DSN hacking
e
s 00051/00006/01974
d D 8.45 94/11/27 11:20:14 eric 257 256
c improved debugging
e
s 00003/00002/01977
d D 8.44 94/11/25 09:05:59 eric 256 255
c improve DSN handling somewhat + some bug fixes
e
s 00004/00000/01975
d D 8.43 94/11/23 15:21:07 eric 255 254
c get ORCPT= ESMTP DSN parameter working
e
s 00005/00002/01970
d D 8.42 94/11/22 22:24:50 eric 254 253
c clean up several small problems with file delivery, error detection,
c and return receipts
e
s 00001/00001/01971
d D 8.41 94/11/21 21:07:30 eric 253 252
c convert to new DSN draft
e
s 00017/00000/01955
d D 8.40 94/11/20 08:56:39 eric 252 251
c check for "<<>>" etc as equivalent to "<>"
e
s 00003/00000/01952
d D 8.39 94/11/04 08:40:21 eric 251 250
c first cut at DSN implementation
e
s 00013/00015/01939
d D 8.38 94/10/17 08:24:32 eric 250 249
c use -s flag on dequote map to indicate space substitution
e
s 00012/00000/01942
d D 8.37 94/10/07 12:20:15 eric 249 248
c 
e
s 00003/00000/01939
d D 8.36 94/09/08 11:30:58 eric 248 247
c use SpaceSub option value for space replacement in dequote map
e
s 00003/00003/01936
d D 8.35 94/08/17 08:09:01 eric 247 246
c make all flags be printed in hex rather than octal (except file modes)
e
s 00006/00005/01933
d D 8.34 94/07/03 11:47:57 eric 246 245
c break out special local mail processing (e.g., mapping to the
c "prog" mailer) onto separate mailer flags
e
s 00002/00002/01936
d D 8.33 94/05/29 07:33:28 eric 245 244
c move entry/exit debugging to 21.1
e
s 00002/00002/01936
d D 8.32 94/05/18 10:45:42 eric 244 243
c avoid null pointer dereference in debugging code
e
s 00001/00001/01937
d D 8.31 94/04/15 09:27:11 eric 243 242
c don't print size parameter in error messages during parsing
e
s 00001/00001/01937
d D 8.30 94/02/09 11:32:19 eric 242 241
c make default $#error number 553 instead of 501
e
s 00007/00001/01931
d D 8.29 94/01/05 09:20:07 eric 241 239
c try to make sure that path-addrs always have <angle brackets>
e
s 00007/00001/01931
d R 8.29 94/01/04 15:02:44 eric 240 239
c make sure route-addrs have <angle brackets> in envelope
e
s 00026/00014/01906
d D 8.28 94/01/04 06:41:26 eric 239 238
c avoid core dump on $> with no argument; fix sameaddr to avoid
c excessive FALSE values
e
s 00005/00001/01915
d D 8.27 93/12/14 14:05:17 eric 238 237
c parameterize maximum recursion depth (compile time only)
e
s 00002/00001/01914
d D 8.26 93/12/12 07:22:24 eric 237 236
c avoid core dump if getctladdr() returns null
e
s 00007/00002/01908
d D 8.25 93/12/11 17:14:39 eric 236 235
c fix uid-dependent non-equivalence of addresses
e
s 00040/00042/01870
d D 8.24 93/12/11 14:49:15 eric 235 234
c efficiency hacks for toktype
e
s 00021/00014/01891
d D 8.23 93/12/10 17:46:36 eric 234 233
c add a "recursion level" argument to rewrite() to detect loops politely
e
s 00008/00006/01897
d D 8.22 93/12/10 17:20:05 eric 233 232
c add bufsize parameter to prescan
e
s 00001/00001/01902
d D 8.21 93/12/10 12:42:42 eric 232 231
c avoid core dump on subroutines that return null addr lists
e
s 00007/00012/01896
d D 8.20 93/12/02 10:17:48 eric 231 230
c fix bogus implementation of name overflow limiting
e
s 00012/00000/01896
d D 8.19 93/11/28 14:28:24 eric 230 229
c avoid problems with very long addresses
e
s 00002/00000/01894
d D 8.18 93/11/20 07:35:38 eric 229 228
c make $#error exit stats work consistently whether or not they have
c a $@exitstat clause
e
s 00006/00000/01888
d D 8.17 93/10/31 10:17:57 eric 228 227
c debugging
e
s 00005/00005/01883
d D 8.16 93/10/28 19:38:40 eric 227 226
c it's not the case that unbalanced conditions are always fixed
e
s 00012/00005/01876
d D 8.15 93/10/28 18:08:01 eric 226 225
c fix core dump caused by writing to read-only memory
e
s 00004/00002/01877
d D 8.14 93/10/22 09:21:55 eric 225 224
c repair to infinite loop detection algorithm
e
s 00032/00014/01847
d D 8.13 93/10/17 12:00:29 eric 224 223
c fix handling of pre-parsing address errors
e
s 00015/00001/01846
d D 8.12 93/09/27 08:23:32 eric 223 222
c repair numeric codes on $#error lines (broken a few days ago)
e
s 00007/00000/01840
d D 8.11 93/09/04 18:02:23 eric 222 221
c allow null defaults in $( ... $) lookups
e
s 00001/00001/01839
d D 8.10 93/09/04 09:10:53 eric 221 220
c fix improper interpretation of % in addresses in $#error mailer
e
s 00023/00017/01817
d D 8.9 93/08/24 21:06:26 eric 220 219
c save paddr in parseaddr early to avoid having it get trashed
e
s 00020/00018/01814
d D 8.8 93/08/19 15:30:46 eric 219 218
c if buildaddr return an error, return a non-null pointer so we can
c keep track of what's really gotten lost
e
s 00028/00022/01804
d D 8.7 93/08/17 09:51:51 eric 218 217
c put in beginnings of mod time checks on maps; generalize flags
c parameter to parseaddr/allocaddr to use RF_ hooks; relax HELO rules
c for Authentication-Warning:s
e
s 00005/00005/01821
d D 8.6 93/07/17 14:33:17 eric 217 216
c have "Unbalanced" messages note that the problem was fixed
e
s 00005/00005/01821
d D 8.5 93/07/17 13:48:15 eric 216 215
c allow 6xx codes to mean "warnings sent to postmaster"
e
s 00004/00009/01822
d D 8.4 93/07/16 10:31:58 eric 215 214
c repair unbalanced ) and >
e
s 00004/00002/01827
d D 8.3 93/07/11 11:49:39 eric 214 213
c avoid deferencing null pointers -- breaks on Solaris (printf is dumb)
e
s 00001/00001/01828
d D 8.2 93/07/11 06:52:30 eric 213 212
c huge number of changes for 8.2, including IRIX & Solaris portability;
c improved error checking; fix -m flag and add -O flag in maps; fix long
c DNS timeouts; relax safefile restrictions; add -X command line flag; etc.
e
s 00002/00002/01827
d D 8.1 93/06/27 18:26:12 bostic 212 211
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00000/01827
d D 6.62 93/06/24 07:29:38 eric 211 209
c fix serious security bug allowing any user to read any file on
c the system regardless of permissions or ownership; fix problem causing
c subroutines returning $# triples to continue to evaluate (causes loops)
e
s 00002/00002/01825
d R 8.1 93/06/12 08:35:51 eric 210 209
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/01826
d D 6.61 93/06/12 08:35:11 eric 209 207
c fix bug causing class backups to jump two tokens instead of one
e
s 00002/00002/01825
d R 8.1 93/06/07 10:31:16 bostic 208 207
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00003/01827
d D 6.60 93/06/05 17:07:49 eric 207 206
c lint-style cleanup
e
s 00001/00001/01829
d D 6.59 93/05/28 07:12:29 eric 206 205
c defer map open as long as possible
e
s 00001/00001/01829
d D 6.58 93/05/27 13:01:57 eric 205 204
c Solaris portability changes
e
s 00000/00004/01830
d D 6.57 93/05/27 11:37:18 eric 204 203
c prototype functions
e
s 00001/00003/01833
d D 6.56 93/05/22 08:57:58 eric 203 202
c AIX compatibility changes; clean up map initialization functions
e
s 00002/00000/01834
d D 6.55 93/05/21 20:29:43 eric 202 201
c cleanup for NIS maps
e
s 00001/00001/01833
d D 6.54 93/05/21 18:59:00 eric 201 200
c changes to merge alias and map implementations
e
s 00008/00030/01826
d D 6.53 93/05/17 10:28:09 eric 200 199
c first cut at merged map/alias implementation
e
s 00001/00001/01855
d D 6.52 93/05/14 13:52:26 eric 199 198
c use newstr for e_message consistently
e
s 00011/00001/01845
d D 6.51 93/05/13 09:29:01 eric 198 197
c don't write arbitrarily off the end of a buffer (ugh!)
e
s 00011/00002/01835
d D 6.50 93/05/05 12:06:28 eric 197 196
c fixes for problems causing mail to be both sent and rejected
e
s 00005/00001/01832
d D 6.49 93/05/04 20:42:56 eric 196 195
c fix some bogus messages being printed in mailq command
e
s 00001/00001/01832
d D 6.48 93/05/03 17:23:59 eric 195 194
c ANSI fixes
e
s 00005/00002/01828
d D 6.47 93/04/30 15:15:40 eric 194 193
c clean up error message printing, especially for deferred messages
e
s 00006/00000/01824
d D 6.46 93/04/29 20:35:30 eric 193 192
c compile problem -- dangling else
e
s 00001/00001/01823
d D 6.45 93/04/26 13:33:19 eric 192 191
c quote need not be in DELIMCHARS either
e
s 00002/00004/01822
d D 6.44 93/04/26 13:30:04 eric 191 190
c fix some problems with backslash handling
e
s 00005/00004/01821
d D 6.43 93/04/26 12:44:22 eric 190 189
c print more fields in printaddr
e
s 00025/00024/01800
d D 6.42 93/04/19 09:19:34 eric 189 188
c change remotename to use flag bits instead of individual parameters;
c add a pstat parameter to return status information up
e
s 00009/00003/01815
d D 6.41 93/04/16 08:48:58 eric 188 187
c fix bug causing host\!user to be parsed as one token
e
s 00007/00001/01811
d D 6.40 93/04/14 16:46:56 eric 187 186
c don't dequote if there would be spaces left -- they will be
c replaced by the SpaceSub character
e
s 00051/00021/01761
d D 6.39 93/04/14 14:38:42 eric 186 185
c return status information from map lookups and from there from 
c rewrite; this allows higher level code to queue if the name server is down
e
s 00001/00001/01781
d D 6.38 93/04/12 08:02:55 eric 185 184
c properly diagnose ruleset zero returning null vector
e
s 00063/00013/01719
d D 6.37 93/04/10 09:28:28 eric 184 183
c implement $&x for deferred macro expansion; some POSIX compatibility
e
s 00007/00003/01725
d D 6.36 93/04/05 08:21:57 eric 183 182
c clean up error return messages
e
s 00013/00004/01715
d D 6.35 93/03/30 10:05:13 eric 182 181
c fix bogus "infinite loop" diagnostic; log better diagnostic info
e
s 00003/00003/01716
d D 6.34 93/03/26 08:06:27 eric 181 180
c fix excessive matching problem
e
s 00055/00026/01664
d D 6.33 93/03/26 07:32:08 eric 180 179
c fix a few problems pointed out by Neil Rickert; $~ matches only
c one token
e
s 00034/00017/01656
d D 6.32 93/03/25 14:16:30 eric 179 178
c implement multi-word classes
e
s 00022/00000/01651
d D 6.31 93/03/25 10:27:14 eric 178 177
c recognize -a flag in dequote map
e
s 00115/00000/01536
d D 6.30 93/03/25 09:12:23 eric 177 176
c add dequote pseudo-map
e
s 00005/00000/01531
d D 6.29 93/03/23 19:50:46 eric 176 175
c improved debugging; pass convtime a default units; allow addition
c of Comments: and stripping of Return-Path:
e
s 00003/00003/01528
d D 6.28 93/03/16 09:16:10 eric 175 174
c delete e_sender and e_returnpath; fix some bugs in envelope splitting
e
s 00004/00004/01527
d D 6.27 93/03/14 08:30:36 eric 174 173
c don't send all addresses through recipient rewriting in buildaddr;
e
s 00009/00029/01522
d D 6.26 93/03/14 07:36:33 eric 173 172
c change (simplify) user and host UPPER => lower case mapping
e
s 00002/00000/01549
d D 6.25 93/03/08 07:48:29 eric 172 171
c undo patch allowing prescan to return null vector; it breaks far
c too much
e
s 00020/00012/01529
d D 6.24 93/03/06 08:32:09 eric 171 170
c allow host on local addresses; don't do domain extension on
c return path, ever -- for <> addresses
e
s 00004/00000/01537
d D 6.23 93/03/04 08:03:56 eric 170 169
c consider addresses "different" if their uids differ
e
s 00002/00004/01535
d D 6.22 93/03/03 09:48:48 eric 169 168
c allow prescan to return a null vector; fix some duplicate prescan errs
e
s 00036/00026/01503
d D 6.21 93/03/01 12:43:50 eric 168 167
c changes for ESMTP; mostly better delimiter character pointer passing
e
s 00006/00001/01523
d D 6.20 93/02/24 09:12:34 eric 167 166
c allow $@ on LHS to indicate match zero tokens
e
s 00022/00022/01502
d D 6.19 93/02/23 06:31:35 eric 166 165
c overhaul status of SMTP reply codes
e
s 00002/00002/01522
d D 6.18 93/02/21 15:52:31 eric 165 164
c M_LOCAL => M_LOCALMAILER to avoid conflict with Ultrix <sys/mount.h>
e
s 00019/00036/01505
d D 6.17 93/02/20 13:46:33 eric 164 163
c close cached MCI connections after a fork; add p (privacy) and b
c (min blocks free) options; fix selfref code; clean up $#error format
e
s 00003/00001/01538
d D 6.16 93/02/19 09:21:30 eric 163 162
c fix a variety of bugs found by Eric Wassenaar <e07@nikhef.nl>
e
s 00038/00033/01501
d D 6.15 93/02/18 20:22:18 eric 162 161
c move the meta-characters from C0 into C1 space
e
s 00001/00001/01533
d D 6.14 93/02/18 10:37:30 eric 161 160
c add "c" mailer flag to suppress all comment info in addresses
e
s 00015/00012/01519
d D 6.13 93/02/16 18:29:48 eric 160 159
c clean up log levels; allow IDA-style split header/envelope rewriting;
c extend arpatounix with more zones (but is this even needed?)
e
s 00002/00000/01529
d D 6.12 93/02/15 16:44:47 eric 159 158
c Allow saving in ~/dead.letter; clean up VRFY output; fix bogus
c error message in udbexpand; null terminate host buffers in buildaddr
c (broken in 6.21).
e
s 00060/00019/01469
d D 6.11 93/02/15 12:00:27 eric 158 157
c improve some error messages; fix quoted :include:s; check for some
c other buffer overflows; log SMTP protocol errors
e
s 00018/00001/01470
d D 6.10 93/01/26 11:36:31 eric 157 156
c some (iffy) changes to prevent suppressing the actual sender
c during a queue run (interaction with C line in qf file)
e
s 00004/00002/01467
d D 6.9 93/01/20 13:21:55 eric 156 155
c fix problem with address delimitor inside quotes; define $k and $=k
c to be the name (from the uname call)
e
s 00002/00002/01467
d D 6.8 93/01/14 10:33:40 eric 155 154
c revert debugging to old values
e
s 00002/00002/01467
d D 6.7 93/01/14 08:50:20 eric 154 153
c fix minor debugging botch
e
s 00002/00001/01467
d D 6.6 93/01/13 18:38:11 eric 153 152
c environment handling simplification/bug fix; handle commas inside
c comments; properly limit large messages in -obq mode
e
s 00014/00006/01454
d D 6.5 93/01/10 12:56:42 eric 152 151
c MX piggybacking, based on code from John Myers@CMU; allow checkcompat
c to return -1 to mean tempfail; bug fix in m_mno computation
e
s 00021/00002/01439
d D 6.4 93/01/02 13:59:59 eric 151 150
c changes to recognize special mailer types (e.g., file) early
e
s 00002/00002/01439
d D 6.3 93/01/01 13:30:06 eric 150 149
c fix botch in invalidaddr() routine
e
s 00033/00000/01408
d D 6.2 93/01/01 13:09:52 eric 149 148
c check for invalid characters in addresses
e
s 00000/00000/01408
d D 6.1 92/12/21 16:08:21 eric 148 147
c Release 6
e
s 00032/00001/01376
d D 5.28 92/12/21 12:10:58 eric 147 145
c fix aliases to print error messages (rather than core dumping);
c allow words as error codes to $#error mailer
e
s 00008/00006/01371
d D 5.27.1.1 92/12/14 22:04:39 eric 146 145
c try to allow host on local mailers (for some reason)
e
s 00009/00001/01368
d D 5.27 92/11/15 19:24:38 eric 145 144
c allow specification of arbitrary string on successful db match
e
s 00047/00015/01322
d D 5.26 92/11/15 16:10:53 eric 144 143
c finish support for generalized maps
e
s 00001/00001/01336
d D 5.25 92/11/14 11:34:12 eric 143 142
c (partially) ANSI-fy it
e
s 00030/00010/01307
d D 5.24 92/11/13 18:09:02 eric 142 141
c try to do some syntax error corrections on errors in headers
e
s 00004/00000/01313
d D 5.23 92/11/13 11:02:42 eric 141 140
c add some debugging info
e
s 00010/00002/01303
d D 5.22 92/11/04 12:14:45 eric 140 137
c fix a variety of small bugs noticed by bcx
e
s 00024/00090/01698
d D 5.13.1.2 92/09/22 16:13:49 eric 139 138
c hacks so it will compile -- but I don't see making a lot of use
c of this version, because of the extent of the changes
e
s 00771/00144/01017
d D 5.13.1.1 92/09/22 14:48:33 eric 138 129
c version from Neil Rickert
e
s 00000/00001/01305
d D 5.21 92/07/12 14:39:02 eric 137 136
c lint
e
s 00015/00011/01291
d D 5.20 92/07/12 14:09:40 eric 136 135
c reduce number of instances of CurEnv by passing it as a parameter
e
s 00004/00003/01298
d D 5.19 92/07/12 10:14:07 eric 135 134
c make eight-bit clean; backslashes are carried through as-is
e
s 00068/00025/01233
d D 5.18 92/05/25 13:13:29 eric 134 133
c add generalized database mapping (using the K config line and
c $( ... $) syntaxes); $[ ... $] is now a special case
e
s 00009/00002/01249
d D 5.17 92/02/21 20:57:47 eric 133 132
c from Bryan Costales: several smallish changes, mostly to clean
c up debugging output.  The major change is that test mode (-bt)
c doesn't automatically run through ruleset three any more.
e
s 00001/00001/01250
d D 5.16 91/11/15 15:53:40 eric 132 131
c change leading "local mailer" indicator to avoid conflict with
c :include: lists
e
s 00002/00001/01249
d D 5.15 91/10/20 01:50:03 eric 131 130
c handle backslashes in addresses properly
e
s 00106/00017/01144
d D 5.14 91/10/05 10:09:07 eric 130 129
c allow catching of local names after aliasing but before local name
c resolution; have name server return indication that it matched.
e
s 00001/00011/01160
d D 5.13 90/06/01 19:02:34 bostic 129 128
c new copyright notice
e
s 00003/00003/01168
d D 5.12 90/04/18 13:54:09 bostic 128 127
c sendmail security problems; bug report 4.3BSD/usr.lib/153
c sendmail security problems; bug report 4.3BSD/usr.lib/133
c sendmail security problems; bug report 4.3BSD/usr.lib/136
e
s 00001/00001/01170
d D 5.11 89/01/25 09:32:46 bostic 127 126
c don't indirect through null, just because mc file messed up
e
s 00000/00033/01171
d D 5.10 89/01/01 17:17:31 bostic 126 125
c remove DEBUG
e
s 00011/00009/01193
d D 5.9 88/06/30 14:59:17 bostic 125 124
c install approved copyright notice
e
s 00016/00010/01186
d D 5.8 88/03/13 19:52:30 bostic 124 123
c add Berkeley specific header
e
s 00003/00005/01193
d D 5.7 88/03/13 18:21:42 bostic 123 122
c replace sameword with strcasecmp
e
s 00000/00005/01198
d D 5.6 86/04/02 16:00:55 eric 122 121
c don't run around clearing EF_FATALERRS -- this often applies to another
c address.  Drop uid/gid check in sameaddr -- it causes more problems
c than it fixes.
e
s 00002/00002/01201
d D 5.5 86/01/30 11:02:18 eric 121 120
c fix .forward files that include yourself; this was a bug in sameaddr
c that may have caused some other problems
e
s 00004/00000/01199
d D 5.4 85/11/22 08:26:44 eric 120 119
m 
c don't consider addresses with different q_uid's alike
e
s 00001/00001/01198
d D 5.3 85/10/24 10:36:36 eric 119 118
m 
c don't create a queue name in syserr; permit trailing blanks and quoted
c commas in aliases.
e
s 00000/00000/01199
d D 5.2 85/09/19 01:25:52 eric 118 116
i 117
m 
c incorporate SMI changes -- still experimental
e
s 00012/00007/01187
d D 5.1.1.1 85/09/19 00:56:11 eric 117 116
m 
c SMI changes (somewhat)
e
s 00000/00000/01194
d D 5.1 85/06/08 10:25:54 eric 116 115
m 
c bring to release 5 (like all the other files)
e
s 00003/00003/01191
d D 4.17 85/06/08 00:42:51 eric 115 114
m 
c lint
e
s 00016/00005/01178
d D 4.16 85/06/07 22:31:05 miriam 114 113
m 
c Resolve duplicate SccsId.  Remove unused variables.  Correct 
c return.
e
s 00008/00001/01175
d D 4.15 85/04/28 10:44:23 eric 113 112
m 
c use the recipient rewriting set for parsed addresses
e
s 00004/00000/01172
d D 4.14 84/12/05 23:15:41 eric 112 111
m 
c Try to use flock call (this doesn't work because we don't always have an
c open fd); security and performance fixes from Kirk Smith at Purdue; "a"
c option is now the number of minutes to wait for "@:@" alias; fix bug in
c $[ $] using -t; random cleanup
e
s 00001/00001/01171
d D 4.13 84/11/13 11:33:43 eric 111 110
m 
c bmove => bcopy
e
s 00001/00001/01171
d D 4.12 84/09/09 14:28:22 eric 110 109
m 
c fix absurd trivial botch in previous change
e
s 00007/00003/01165
d D 4.11 84/09/08 17:43:36 eric 109 108
m 
c fix hostname mapping to be repeatable (as required by some .cf files).
e
s 00006/00006/01162
d D 4.10 84/08/12 00:19:01 eric 108 107
m 
c clean up botch in $[ $] code
e
s 00103/00032/01065
d D 4.9 84/08/11 23:20:10 eric 107 106
m 
c Add $[ and $] as RHS operators to look up the contents and pass them
c to maphostname; maphostname currently looks them up in /etc/hosts and
c converts them to canonical form, but could be turned into a general
c name server.....   huzzah!!
e
s 00002/00002/01095
d D 4.8 84/08/11 17:52:58 eric 106 105
m 
c Assorted changes from Guy Harris <rlgvax!guy>: mostly lint & USG
e
s 00008/00003/01089
d D 4.7 84/08/11 16:55:38 eric 105 103
m 
c Changes from Greg Couch <ucsfcgl!gregc> for V7 compatibility and
c miscellaneous bug fixes; "clear" => "bzero" and "bmove" => "bcopy"
c throughout for consistency; bzero is now in bcopy.c (these are
c supplied by libc on 4.2bsd)
e
s 00057/00014/01078
d D 4.6.1.1 84/06/17 16:18:24 eric 104 103
m 
c abortive attempt to install a name server.... sigh.
e
s 00008/00002/01084
d D 4.6 84/03/17 16:27:30 eric 103 102
m 
c always fold case on host names; fold case on the LHS of aliases
e
s 00023/00009/01063
d D 4.5 84/03/11 19:58:44 eric 102 101
m 
c disable UPPER->lower case mapping in RHS's of aliases so that upper
c case letters can be used in file names and as args to programs.
e
s 00003/00010/01069
d D 4.4 84/03/11 16:55:38 eric 101 100
m 
c change macro expansion character from $ to \001 so that $'s can be
c used in headers -- the .cf file is unchanged by mapping $ to \001.
c \001 is now a manifest constant.
e
s 00014/00002/01065
d D 4.3 83/10/23 17:15:42 eric 100 99
m 
c handle dollar signs in headers properly
e
s 00004/00000/01063
d D 4.2 83/10/16 15:25:42 eric 99 98
m 
c reset errno in parseaddr so that syserr gives a permanent error code and
c no extraneous information about non-errors
e
s 00000/00000/01063
d D 4.1 83/07/25 19:46:46 eric 98 97
m 
c 4.2 release version
e
s 00001/00000/01062
d D 3.81 83/03/26 14:25:26 eric 97 96
m 215
c rewrite again with ruleset 3 after appending from domain so that we can
c add any punctuation, e.g., "<" "@" "domain" ">"
e
s 00005/00002/01057
d D 3.80 83/03/08 19:21:47 eric 96 95
m 205
c Pass the delimiter character to parseaddr so that we can correctly
c decide between comma and space
e
s 00003/00001/01056
d D 3.79 83/03/07 09:24:34 eric 95 94
m 202
c Handle OLDSTYLE addresses properly with the -t flag; notice that tabs also
c delimit addresses (as well as spaces)
e
s 00001/00001/01056
d D 3.78 83/03/05 17:37:54 eric 94 93
m 200
c Ignore delimiters (e.g., commas) inside quotes
e
s 00002/00001/01055
d D 3.77 83/02/24 20:02:44 eric 93 92
m 181
c arrange to cleanup addresses using ruleset 4 before storing in ADDR struct
e
s 00002/00002/01054
d D 3.76 83/02/19 14:41:40 eric 92 91
m 188
c Avoid core dumps on very long addresses in headers.
e
s 00005/00013/01051
d D 3.75 83/02/02 12:55:01 eric 91 90
m 165
c implement classes and mailer flags as a bit map; define new class 'w'
c as the set of all hosts we are known by
e
s 00008/00037/01056
d D 3.74 83/01/15 17:41:30 eric 90 89
m 149
c be sure everything gets appropriately externalized; canonname goes away,
c since everything is now done by remotename
e
s 00006/00001/01087
d D 3.73 83/01/06 18:21:30 eric 89 88
m 
c allow user-setable error codes in "error" mailer
e
s 00004/00000/01084
d D 3.72 83/01/06 10:49:48 eric 88 87
m 
c split up FULLSMTP flag -- now have "X" (M_XDOT, use hidden dot algorithm),
c "p" (M_FROMPATH, use reverse-path in MAIL FROM:<> command), and "L"
c (M_LIMITS, enforce SMTP line limits).  I would like to change the format
c of the mail defn one more time to make named fields so that it would
c be more extensible.
e
s 00001/00000/01083
d D 3.71 83/01/03 14:02:03 eric 87 86
m 
c have canonname pass the address through ruleset four also
e
s 00004/00004/01079
d D 3.70 82/12/24 08:15:34 eric 86 85
m 108
c Change parse to parseaddr for BB&N TCP/IP implementation; clean up
c comments in daemon.c to simplify the poor alternate protocol type.
e
s 00004/00002/01079
d D 3.69 82/12/09 19:18:11 eric 85 84
m 036
m 053
m 064
c Fix a bug triggered when we add the sender's "@domain" to an address
c in the message body that is missing a domain -- we forgot to null
c terminate the list.
e
s 00013/00006/01068
d D 3.68 82/12/09 11:17:43 eric 84 83
m 095
c be able to match the inverse of a class using the $~x syntax
e
s 00086/00092/00988
d D 3.67 82/11/28 00:21:33 eric 83 82
m 
c Many changes resulting from a complete code readthrough.  Most of these
c fix minor bugs or change the internal structure for clarity, etc.  There
c should be almost no externally visible changes (other than some cleaner
c error message printouts and the like).
e
s 00001/00002/01079
d D 3.66 82/11/24 18:44:00 eric 82 81
m 
c lint it
e
s 00002/00002/01079
d D 3.65 82/11/17 09:36:07 eric 81 80
m 060
c split operation mode ("-bx" flag) and delivery mode ("d" option)
c so that operation mode can apply to SMTP/daemon connections also.
e
s 00003/00003/01078
d D 3.64 82/11/03 11:17:32 eric 80 79
m 059
c don't strip quotes off of addresses during prescan
e
s 00001/00001/01080
d D 3.63 82/11/03 09:48:57 eric 79 78
m 049
c Arrange to strip quote bits in message header; move SPACESUB into
c conf.c; change SpaceSub to unquoted dot
e
s 00012/00003/01069
d D 3.62 82/10/31 13:46:39 eric 78 77
m 032,
m 051
c Call ruleset 4 after doing per-mailer translation to convert from
c internal to external form.
e
s 00004/00000/01068
d D 3.61 82/10/13 18:43:06 eric 77 76
m 022
c Don't interpret <, >, (, or ) while in QST (quote state) during prescan
e
s 00025/00002/01043
d D 3.60 82/10/09 09:05:11 eric 76 75
m 001
c implement an experimental forward-path algorithm by stripping off a
c leading "@..." component and dropping it on the end.
e
s 00004/00001/01041
d D 3.59 82/10/07 08:50:53 eric 75 74
c never use ruleset 3 alone -- perhaps the standard use of ruleset
c three should go now, since noone uses it alone.
e
s 00002/00006/01040
d D 3.58 82/10/06 11:44:40 eric 74 73
c add test mode (MD_TEST, -bt)
e
s 00016/00014/01030
d D 3.57 82/09/16 20:24:38 eric 73 72
x 72
c drop ":...;" stuff -- it screws it up aliases; pass parameters to
c subroutines (this also adds $@ and $: features to subr calls); check
c overflow of "tobuf" on smtp deliveries, which caused core dumps on
c large mailing lists
e
s 00011/00000/01044
d D 3.56 82/09/12 22:17:08 eric 72 71
c accept ": ... ;" syntax for groups if !oldstyle
e
s 00047/00016/00997
d D 3.55 82/09/12 16:43:39 eric 71 70
c change inheritance for macros in envelopes; be able to canonicalize
c non-domained names by appending domain from sender; call ruleset 3
c explicitly before doing other rulesets; some general cleanup.
e
s 00002/00002/01011
d D 3.54 82/09/06 17:58:21 eric 70 69
c fix bug in scanner state machine that never let you out of quote state.
e
s 00130/00113/00883
d D 3.53 82/09/06 16:24:18 eric 69 68
c install new state-driven scanner; make everyone use it, thus fixing
c problems of quoted commas, etc.
e
s 00054/00078/00942
d D 3.52 82/09/05 18:08:38 eric 68 67
c change $g processing from a macro substitution per mailer to two sets
c of rewriting rules per mailer -- one each for sender and recipient
c fields; convert to NBS standard on Return-Receipt-To: and Precedence:
c fields; clean up From: processing code and generalize it to all
c sender fields; tune debugging code; clean up canonname.
c **** This delta invalidates previous configuration files ****
e
s 00072/00025/00948
d D 3.51 82/09/05 11:48:09 eric 67 66
c add $* to match zero or more and $> to make a "subroutine" call; stick
c in initial hooks for per-mailer rewriting; improve diagnostics in readcf,
c including number lines; increase the number of rewriting sets.
e
s 00003/00001/00970
d D 3.50 82/09/01 10:23:14 eric 66 65
c allow CANONUSER ($:) to abort a rewriting set
e
s 00005/00004/00966
d D 3.49 82/08/27 16:00:29 eric 65 64
c simplify timeout code; allow multiple simultaneous queue runs so that
c large messages don't freeze things up; fix EINTR problem in sfgets;
c clean up canonname to be really correct; lots of misc. cleanup
e
s 00043/00038/00927
d D 3.48 82/08/25 16:18:39 eric 64 63
c apply ruleset 4 to rewrite addresses in the body of the message; fix
c a clock.c bug that caused it to lose events; more time cleanup.
e
s 00001/00038/00964
d D 3.47 82/08/21 17:54:19 eric 63 62
c move <> and forward path processing to .cf file; increase MAXATOMS
c since some "comment" information may now be part of the address.
c **** this installation requires a new sendmail.cf file ****
e
s 00012/00001/00990
d D 3.46 82/08/15 11:54:00 eric 62 61
c add debugging info
e
s 00124/00000/00867
d D 3.45 82/08/08 16:58:18 eric 61 60
c move remotename() from deliver.c to parse.c; initial implementation
c of canonname()
e
s 00008/00008/00859
d D 3.44 82/08/08 01:02:37 eric 60 59
c change debug level to a debug vector; add levels on logging (and the
c -L flag); change logging to be by message-id; elevate message-id;
c some lint-type cleanup
e
s 00004/00004/00863
d D 3.43 82/05/31 18:49:12 eric 59 58
c pass lint.  notice that definitions in llib-lc have changed for
c alarm() and sleep() calls {arg was unsigned, is now int}.
e
s 00000/00000/00867
d D 3.42 82/05/31 15:31:55 eric 58 56
i 57
c finish implementing envelopes.  it's not completely clear to me that
c this is really the way to go, but it seems clearly better than what
c i had before.  this delta includes many other minor changes, so it
c should probably not be blithely removed.
e
s 00001/00001/00866
d D 3.41.1.1 82/05/29 18:20:02 eric 57 56
c try to install envelopes.  is this really worth it???
e
s 00001/00001/00866
d D 3.41 82/05/22 01:37:38 eric 56 55
c add "envelopes" to contain the basic information needed as control
c info for each message.  currently there is only one envelope -- this
c being the obvious stupid conversion.  later there will be separate
c envelopes for error messages, return receipts, etc.
e
s 00001/00001/00866
d D 3.40 82/03/20 16:12:14 eric 55 54
c 16 bit changes -- should have no effect on VAX binaries to
c speak of.
e
s 00007/00064/00860
d D 3.39 82/03/06 14:14:58 eric 54 53
c collapse special character processing into macro processing for
c simplicity of code.
e
s 00005/00004/00919
d D 3.38 82/02/04 20:30:13 eric 53 52
c add host aliasing; add -p flag.  this version doesn't yet know about
c replacing the text of the host alias into the message however.  syntax
c is grotty: "/hostmatch:%s@newhost" or whatever.
e
s 00001/00001/00922
d D 3.37 81/12/06 12:38:35 eric 52 51
c cleanup so it will go through lint without any fancy grep -v's;
c change the way SCCS Id's are handled.
e
s 00002/00002/00921
d D 3.36 81/11/22 19:17:33 eric 51 50
c Edit queue control files when running queue (assuming there are still
c recipients left).  Also, modify the MsgPriority to be the absolute
c number (not the Priority: value); this allows us to include aging into
c the priority algorithm.
e
s 00006/00002/00917
d D 3.35 81/11/21 18:42:12 eric 50 49
c change the send queue to be only one queue instead of one per mailer.
c this is slightly inefficient but simpler.  also, pass this queue
c around so we can have multiple send queues.  this makes VRFY work.
e
s 00001/00002/00918
d D 3.34 81/11/21 16:37:57 eric 49 47
c convert to SMTP draft 3 -- finishing touches.  Punt on the VRFY/
c EXPN commands for now; they aren't required anyhow.  Move the fullname
c into the address structure so it can be inherited.
e
s 00018/00006/00914
d D 3.33.1.1 81/11/21 15:47:12 eric 48 47
c links together aliases into proper trees.  This is in part an
c attempt to do the SMTP VRFY command properly, but there are a number
c of annoying problems that convince me that this is the wrong way to
c do it.  Sigh.
e
s 00003/00002/00917
d D 3.33 81/10/27 11:13:14 eric 47 46
c ignore case in mailer name comparison
e
s 00001/00002/00918
d D 3.32 81/10/26 14:22:22 eric 46 45
c Install new experimental queueing facility -- one stage timeout,
c etc.  This version is still quite incomplete.  It needs to reorder
c the queue after some interval, do two-stage timeout, take option
c info from the queue file instead of the command line, read the
c sender's .mailcf file, etc.  Some of this is useful for SMTP also.
e
s 00005/00005/00915
d D 3.31 81/10/23 19:37:41 eric 45 44
c Eliminate magic MN_LOCAL and MN_PROG; change q_mailer item in ADDRESS
c to be pointer to mailer rather than index.
e
s 00043/00023/00877
d D 3.30 81/10/08 09:16:51 eric 44 42
c fix botch in backup code during rewriting
e
s 00043/00022/00878
d R 3.30 81/10/08 09:13:17 eric 43 42
c fix botch in backup code during rewriting
e
s 00048/00141/00852
d D 3.29 81/10/06 19:12:41 eric 42 41
c change rewriting rules to use $N on RHS to match LHS, and include
c $=X (class match) in the matching; this will allow us to match the
c proposed "user.host@domain" syntax as well as the old syntax, by
c putting the known domains into a class to disambiguate.
e
s 00007/00007/00986
d D 3.28 81/09/30 10:00:04 eric 41 40
c fix the <> syntax, convert "at" to "@" in from addresses also,
c plus some minorness to get the multi-machine case going nicely.
e
s 00008/00004/00985
d D 3.27 81/09/28 19:17:12 eric 40 39
c enable aliases to self-reference themselves correctly.
e
s 00019/00009/00970
d D 3.26 81/09/22 13:24:08 eric 39 38
c fix problem with using macros in rules; change configuration to send
c different flags when destined for arpanet vs. berknet hosts, etc.
e
s 00017/00000/00962
d D 3.25 81/09/14 12:41:14 eric 38 37
c check MAXATOM overflow; increase MAXATOM value
e
s 00000/00001/00962
d D 3.24 81/09/12 17:33:48 eric 37 36
c match on full name for local users
e
s 00004/00004/00959
d D 3.23 81/09/06 19:48:36 eric 36 35
c cleanup, commenting, linting, etc.
e
s 00030/00001/00933
d D 3.22 81/08/31 12:11:35 eric 35 34
c allow "error" as a net name to print error messages
e
s 00000/00000/00934
d D 3.21 81/08/25 16:05:53 eric 34 33
i 32
c remove special "at" processing (put it in .cf file)
e
s 00051/00019/00894
d D 3.20 81/08/25 16:01:42 eric 33 31
c change processing of <LWSP> in addresses
e
s 00000/00011/00902
d D 3.19.1.1 81/08/25 13:42:16 eric 32 31
c remove special "at" processing (experimental)
e
s 00002/00002/00911
d D 3.19 81/08/21 18:18:19 eric 31 30
c drop M_FINAL, change some other defined constant names
e
s 00000/00002/00913
d D 3.18 81/08/20 15:14:02 eric 30 29
c clean up some header information; don't reopen tempfile as
c stdin (to fix some problems with saving mail on interrupts)
e
s 00024/00015/00891
d D 3.17 81/08/10 16:56:30 eric 29 28
c totally rework aliasing scheme -- sucks when no DBM now,
c but works better for the usual case; fix some quoting problems
c (and how many did I add?); remove .mailer feature since .forward
c will simulate this happily
e
s 00007/00010/00899
d D 3.16 81/08/09 15:02:46 eric 28 27
c lint it
e
s 00001/00000/00908
d D 3.15 81/08/09 12:34:32 eric 27 26
c add private incoming mailers; add q_home field to ADDRESS struct;
c some general cleanup
e
s 00004/00003/00904
d D 3.14 81/08/08 17:47:33 eric 26 25
c add another set of rewrite rules to process From: address;
c this will allow generalized from address processing in an
c internet
e
s 00025/00006/00882
d D 3.13 81/08/08 11:17:49 eric 25 24
c add word classes
e
s 00003/00002/00885
d D 3.12 81/03/27 14:31:09 eric 24 23
c fix funny botch in $o exclusion
e
s 00010/00002/00877
d D 3.11 81/03/27 13:54:59 eric 23 22
c put word delimiters into cf file
e
s 00001/00001/00878
d D 3.10 81/03/20 09:45:16 eric 22 21
c change name (again); from postbox to sendmail
e
s 00032/00000/00847
d D 3.9 81/03/12 10:57:09 eric 21 20
c merge letters to the same host into one message
e
s 00065/00011/00782
d D 3.8 81/03/11 10:45:50 eric 20 19
c general cleanup, esp. macro processor
e
s 00002/00002/00791
d D 3.7 81/03/09 14:21:12 eric 19 18
c fix botch in string compares
e
s 00569/00295/00224
d D 3.6 81/03/09 13:22:02 eric 18 17
c first step at rewriting rules, etc.
e
s 00034/00001/00485
d D 3.5 81/03/08 13:05:00 eric 17 16
c do host equivalence
e
s 00002/00003/00484
d D 3.4 81/03/07 16:59:32 eric 16 15
c change q_mailer to be index, not pointer
e
s 00001/00000/00486
d D 3.3 81/03/07 15:32:33 eric 15 14
c lint fixes
e
s 00001/00000/00485
d D 3.2 81/03/07 14:58:19 eric 14 13
c save real mailer
e
s 00023/00034/00462
d D 3.1 81/03/07 14:26:50 eric 13 12
c ----- delivermail ==> postbox -----
e
s 00001/00001/00495
d D 2.5 81/01/08 23:57:36 eric 12 11
c fixed botch in at => @ translation
e
s 00001/00001/00495
d D 2.4 81/01/08 19:50:58 eric 11 10
c fix problem with "isspace" on non-ascii characters
e
s 00010/00002/00486
d D 2.3 81/01/08 19:36:42 eric 10 9
c disallowed multiple <> spec
e
s 00021/00005/00467
d D 2.2 81/01/08 19:27:29 eric 9 8
c turn <lwsp> (spaces) into quoted '.' instead of nothing (for CMU)
e
s 00000/00000/00472
d D 2.1 80/11/05 11:01:09 eric 8 7
c release 2
e
s 00002/00002/00470
d D 1.7 80/10/21 12:13:01 eric 7 6
c fix bug with bslashmode & don't strip quote bits in prescan
e
s 00001/00001/00471
d D 1.6 80/10/21 11:53:45 eric 6 5
c print result at all times
e
s 00038/00000/00434
d D 1.5 80/10/18 16:49:23 eric 5 4
c cleanup for dbm stuff: Error => Errors; move local host
c detection into parse; misc cleanup
e
s 00004/00003/00430
d D 1.4 80/10/11 12:57:13 eric 4 3
c cleaned up algorithm slightly
e
s 00000/00032/00433
d D 1.3 80/08/02 13:49:38 eric 3 2
c cleaned up comments
e
s 00002/00000/00463
d D 1.2 80/07/25 22:04:06 eric 2 1
c add ID keywords
e
s 00463/00000/00000
d D 1.1 80/06/23 08:24:29 eric 1 0
e
u
U
f b 
f i 
t
T
I 1
D 30
# include <stdio.h>
# include <ctype.h>
E 30
D 13
# include "dlvrmail.h"
E 13
I 13
D 22
# include "postbox.h"
E 22
I 22
D 114
# include "sendmail.h"
E 114
E 22
E 13
D 121

E 121
I 2
D 50
static char	SccsId[] = "%W%	%G%";
E 50
I 50
D 52
static char	SccsId[] =	"%W%	%G%";
E 52
I 52
D 114
SCCSID(%W%	%Y%	%G%);
E 114
I 114
/*
I 125
D 279
 * Copyright (c) 1983 Eric P. Allman
E 279
I 279
 * Copyright (c) 1983, 1995 Eric P. Allman
E 279
E 125
D 124
**  Sendmail
**  Copyright (c) 1983  Eric P. Allman
**  Berkeley, California
**
**  Copyright (c) 1983 Regents of the University of California.
**  All rights reserved.  The Berkeley software License Agreement
**  specifies the terms and conditions for redistribution.
*/
E 124
I 124
D 212
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.
E 212
I 212
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 212
 *
D 129
 * Redistribution and use in source and binary forms are permitted
D 125
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
 *
 *  Sendmail
 *  Copyright (c) 1983  Eric P. Allman
 *  Berkeley, California
E 125
I 125
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
E 129
I 129
 * %sccs.include.redist.c%
E 129
E 125
 */
E 124
E 114
E 52
E 50

I 114
#ifndef lint
D 124
static char	SccsId[] = "%W% (Berkeley) %G%";
#endif not lint
E 124
I 124
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 124

D 138
# include "sendmail.h"
E 138
I 138
#include "sendmail.h"
E 138

I 271
static int	callsubr __P((char **, int, ENVELOPE *));

E 271
I 138
#ifdef	CC_WONT_PROMOTE
static int toktype __P((char));
#else	/* !CC_WONT_PROMOTE */
static int toktype __P((int));				/* char -> int */
#endif	/* CC_WONT_PROMOTE */
static void _rewrite __P((char **, int));
static void callsubr __P((char **));
static ADDRESS * buildaddr __P((char **, ADDRESS *));
static void uurelativize __P((const char *, const char *, char **));

char	*DelimChar;		/* set to point to the delimiter */

E 138
E 114
E 2
/*
D 86
**  PARSE -- Parse an address
E 86
I 86
**  PARSEADDR -- Parse an address
E 86
**
**	Parses an address and breaks it up into three parts: a
**	net to transmit the message on, the host to transmit it
**	to, and a user on that host.  These are loaded into an
D 13
**	addrq header with the values squirreled away if necessary.
E 13
I 13
**	ADDRESS header with the values squirreled away if necessary.
E 13
**	The "user" part may not be a real user; the process may
**	just reoccur on that machine.  For example, on a machine
**	with an arpanet connection, the address
**		csvax.bill@berkeley
**	will break up to a "user" of 'csvax.bill' and a host
**	of 'berkeley' -- to be transmitted over the arpanet.
**
**	Parameters:
**		addr -- the address to parse.
**		a -- a pointer to the address descriptor buffer.
**			If NULL, a header will be created.
D 218
**		copyf -- determines what shall be copied:
**			-1 -- don't copy anything.  The printname
**				(q_paddr) is just addr, and the
**				user & host are allocated internally
**				to parse.
**			0 -- copy out the parsed user & host, but
**				don't copy the printname.
**			+1 -- copy everything.
E 218
I 218
**		flags -- describe detail for parsing.  See RF_ definitions
**			in sendmail.h.
E 218
I 96
**		delim -- the character to terminate the address, passed
**			to prescan.
I 168
**		delimptr -- if non-NULL, set to the location of the
**			delim character that was found.
E 168
I 136
**		e -- the envelope that will contain this address.
E 136
E 96
**
**	Returns:
**		A pointer to the address descriptor header (`a' if
**			`a' is non-NULL).
**		NULL on error.
**
**	Side Effects:
**		none
D 33
**
D 3
**	Defined Constants:
**		none
**
**	Requires:
**		usrerr
**		strcpy (sys)
**		isalpha (sys)
**		xalloc
**		prescan
**		flagset
**		makelower
**		printf (sys)
**		ParseTab -- the parse table.
**
E 3
**	Called By:
**		main
**		sendto
**		alias
**		savemail
E 33
D 3
**
**	History:
**		12/26/79 -- written.
E 3
*/

I 83
/* following delimiters are inherent to the internal algorithms */
E 83
I 9
D 12
# define DELIMCHARS	"()<>@!.,;:\\\""	/* word delimiters */
E 12
I 12
D 18
# define DELIMCHARS	"()<>@!.,;:\\\" \t\r\n"	/* word delimiters */
E 18
I 18
D 23
# define DELIMCHARS	"$()<>@!.,;:\\\" \t\r\n"	/* word delimiters */
E 23
I 23
D 101
# define DELIMCHARS	"$()<>,;\\\"\r\n"	/* word delimiters */
E 101
I 101
D 162
# define DELIMCHARS	"\001()<>,;\\\"\r\n"	/* word delimiters */
E 162
I 162
D 191
# define DELIMCHARS	"\201()<>,;\\\"\r\n"	/* word delimiters */
E 191
I 191
D 192
# define DELIMCHARS	"()<>,;\"\r\n"	/* default word delimiters */
E 192
I 192
# define DELIMCHARS	"()<>,;\r\n"	/* default word delimiters */
E 192
E 191
E 162
E 101
E 23
E 18
E 12
D 37
# define SPACESUB	('.'|0200)		/* substitution for <lwsp> */
E 37

E 9
D 13
addrq *
E 13
I 13
ADDRESS *
E 13
D 86
parse(addr, a, copyf)
E 86
I 86
D 96
parseaddr(addr, a, copyf)
E 96
I 96
D 136
parseaddr(addr, a, copyf, delim)
E 136
I 136
D 168
parseaddr(addr, a, copyf, delim, e)
E 168
I 168
D 218
parseaddr(addr, a, copyf, delim, delimptr, e)
E 218
I 218
parseaddr(addr, a, flags, delim, delimptr, e)
E 218
E 168
E 136
E 96
E 86
	char *addr;
D 13
	register addrq *a;
E 13
I 13
	register ADDRESS *a;
E 13
D 218
	int copyf;
E 218
I 218
	int flags;
E 218
I 96
D 195
	char delim;
E 195
I 195
	int delim;
E 195
I 168
	char **delimptr;
E 168
I 136
	register ENVELOPE *e;
E 136
E 96
{
D 18
	register char *p;
	register struct parsetab *t;
	extern struct parsetab ParseTab[];
	static char buf[MAXNAME];
	register char c;
	register char *q;
	bool got_one;
	extern char *prescan();
E 18
I 18
	register char **pvp;
I 168
	auto char *delimptrbuf;
I 186
	bool queueup;
E 186
E 168
D 137
	register struct mailer *m;
E 137
I 107
	char pvpbuf[PSBUFSIZE];
E 107
D 138
D 204
	extern char **prescan();
E 204
E 18
D 20
	extern char *xalloc();
E 20
I 13
D 28
	extern char *newstr();
E 13
I 5
D 18
	char **pvp;
I 17
	char ***hvp;
E 18
E 17
I 15
	extern char *strcpy();
E 28
I 18
	extern ADDRESS *buildaddr();
I 149
	extern bool invalidaddr();
I 284
	extern void allocaddr __P((ADDRESS *, int, char *));
E 284
E 149
E 138
I 64
D 82
	static char nbuf[MAXNAME];
E 82
E 64
E 18
E 15
E 5

	/*
	**  Initialize and prescan address.
	*/

D 56
	To = addr;
E 56
I 56
D 136
D 138
	CurEnv->e_to = addr;
E 138
I 138
	CurEnv->e_to = (char *)addr;
E 138
E 136
I 136
	e->e_to = addr;
E 136
E 56
I 20
D 126
# ifdef DEBUG
E 126
D 60
	if (Debug)
E 60
I 60
	if (tTd(20, 1))
E 60
D 86
		printf("\n--parse(%s)\n", addr);
E 86
I 86
		printf("\n--parseaddr(%s)\n", addr);
E 86
D 126
# endif DEBUG
E 126

I 149
D 224
	if (invalidaddr(addr))
	{
		if (tTd(20, 1))
			printf("parseaddr-->bad address\n");
		return NULL;
	}

E 224
E 149
I 138
	{
		extern char *DelimChar;		/* parseaddr.c */
		char savec;
		bool invalid;
I 139
		extern char *finddelim();
		extern bool invalidaddr();
E 139

		DelimChar = finddelim(addr, delim);
		savec = *DelimChar;
		*DelimChar = '\0';
		invalid = invalidaddr(addr);
		*DelimChar = savec;
		if (invalid)
			return (NULL);
	}

E 138
E 20
D 18
	if (prescan(addr, buf, &buf[sizeof buf], '\0') == NULL)
E 18
I 18
D 69
	pvp = prescan(addr, '\0');
E 69
I 69
D 95
	pvp = prescan(addr, ',');
E 95
I 95
D 96
	pvp = prescan(addr, bitset(EF_OLDSTYLE, CurEnv->e_flags) ? ' ' : ',');
E 96
I 96
D 107
	pvp = prescan(addr, delim);
E 107
I 107
D 168
	pvp = prescan(addr, delim, pvpbuf);
E 168
I 168
	if (delimptr == NULL)
		delimptr = &delimptrbuf;

I 230
D 231
	if (strlen(addr) >= MAXNAME)
	{
		usrerr("Name too long, %d characters max", MAXNAME - 1);
		if (tTd(20, 1))
			printf("parseaddr-->NULL\n");
		return NULL;
	}

E 231
E 230
D 233
	pvp = prescan(addr, delim, pvpbuf, delimptr);
E 233
I 233
D 277
	pvp = prescan(addr, delim, pvpbuf, sizeof pvpbuf, delimptr);
E 277
I 277
	pvp = prescan(addr, delim, pvpbuf, sizeof pvpbuf, delimptr, NULL);
E 277
E 233
E 168
E 107
E 96
E 95
E 69
	if (pvp == NULL)
I 141
	{
		if (tTd(20, 1))
			printf("parseaddr-->NULL\n");
E 141
E 18
		return (NULL);
I 141
	}
E 141

I 224
	if (invalidaddr(addr, delim == '\0' ? NULL : *delimptr))
	{
		if (tTd(20, 1))
			printf("parseaddr-->bad address\n");
		return NULL;
	}

E 224
	/*
I 220
	**  Save addr if we are going to have to.
	**
	**	We have to do this early because there is a chance that
	**	the map lookups in the rewriting rules could clobber
	**	static memory somewhere.
	*/

	if (bitset(RF_COPYPADDR, flags) && addr != NULL)
	{
		char savec = **delimptr;

		if (savec != '\0')
			**delimptr = '\0';
D 243
		addr = newstr(addr);
E 243
I 243
		e->e_to = addr = newstr(addr);
E 243
		if (savec != '\0')
			**delimptr = savec;
	}

	/*
E 220
D 18
	**  Scan parse table.
	**	Look for the first entry designating a character
	**		that is contained in the address.
	**	Arrange for q to point to that character.
	**	Check to see that there is only one of the char
	**		if it must be unique.
	**	Find the last one if the host is on the RHS.
	**	Insist that the host name is atomic.
	**	If just doing a map, do the map and then start all
	**		over.
E 18
I 18
	**  Apply rewriting rules.
I 64
D 68
	**	Ruleset 4 rewrites the address into a form that will
	**		be reflected in the outgoing message.  It must
	**		not resolve.
E 68
	**	Ruleset 0 does basic parsing.  It must resolve.
E 64
E 18
	*/

I 71
D 184
	rewrite(pvp, 3);
E 71
I 64
D 68
	rewrite(pvp, 4);
E 68
E 64
D 18
 rescan:
	got_one = FALSE;
	for (t = ParseTab; t->p_char != '\0'; t++)
	{
		q = NULL;
		for (p = buf; (c = *p) != '\0'; p++)
		{
			/* find the end of this token */
			while (isalnum(c) || c == '-' || c == '_')
				c = *++p;
			if (c == '\0')
				break;
E 18
I 18
D 26
	rewrite(pvp);
E 26
I 26
	rewrite(pvp, 0);
E 184
I 184
D 186
	rewrite(pvp, 3, e);
	rewrite(pvp, 0, e);
E 186
I 186
	queueup = FALSE;
D 234
	if (rewrite(pvp, 3, e) == EX_TEMPFAIL)
E 234
I 234
	if (rewrite(pvp, 3, 0, e) == EX_TEMPFAIL)
E 234
		queueup = TRUE;
D 234
	if (rewrite(pvp, 0, e) == EX_TEMPFAIL)
E 234
I 234
	if (rewrite(pvp, 0, 0, e) == EX_TEMPFAIL)
E 234
		queueup = TRUE;
E 186
E 184
E 26
E 18

D 18
			if (c == t->p_char)
			{
				got_one = TRUE;
E 18
I 18
D 219
	/*
	**  See if we resolved to a real mailer.
	*/
E 219
E 18

D 18
				/* do mapping as appropriate */
D 13
				if (flagset(P_MAP, t->p_flags))
E 13
I 13
				if (bitset(P_MAP, t->p_flags))
E 13
				{
					*p = t->p_arg[0];
D 13
					if (flagset(P_ONE, t->p_flags))
E 13
I 13
					if (bitset(P_ONE, t->p_flags))
E 13
						goto rescan;
					else
						continue;
				}

				/* arrange for q to point to it */
D 13
				if (q != NULL && flagset(P_ONE, t->p_flags))
E 13
I 13
				if (q != NULL && bitset(P_ONE, t->p_flags))
E 13
				{
					usrerr("multichar error");
					ExitStat = EX_USAGE;
					return (NULL);
				}
D 13
				if (q == NULL || flagset(P_HLAST, t->p_flags))
E 13
I 13
				if (q == NULL || bitset(P_HLAST, t->p_flags))
E 13
					q = p;
			}
			else
			{
				/* insist that host name is atomic */
D 13
				if (flagset(P_HLAST, t->p_flags))
E 13
I 13
				if (bitset(P_HLAST, t->p_flags))
E 13
					q = NULL;
				else
					break;
			}
		}

		if (q != NULL)
			break;
E 18
I 18
D 162
	if (pvp[0][0] != CANONNET)
E 162
I 162
D 185
	if ((pvp[0][0] & 0377) != CANONNET)
E 185
I 185
D 219
	if (pvp[0] == NULL || (pvp[0][0] & 0377) != CANONNET)
E 185
E 162
	{
		setstat(EX_USAGE);
D 166
		usrerr("cannot resolve name");
E 166
I 166
D 213
		syserr("554 cannot resolve name");
E 213
I 213
		syserr("554 cannot resolve name %s", addr);
E 213
E 166
		return (NULL);
E 18
	}

E 219
	/*
D 18
	**  If we matched nothing cleanly, but we did match something
	**  somewhere in the process of scanning, then we have a
	**  syntax error.  This can happen on things like a@b:c where
	**  @ has a right host and : has a left host.
	**
	**  We also set `q' to the null string, in case someone forgets
	**  to put the P_MOVE bit in the local mailer entry of the
	**  configuration table.
E 18
I 18
	**  Build canonical address from pvp.
E 18
	*/

D 18
	if (q == NULL)
	{
		q = "";
		if (got_one)
		{
			usrerr("syntax error");
			ExitStat = EX_USAGE;
			return (NULL);
		}
	}
E 18
I 18
D 183
	a = buildaddr(pvp, a);
E 183
I 183
D 218
	a = buildaddr(pvp, a, e);
E 218
I 218
	a = buildaddr(pvp, a, flags, e);
E 218
E 183
I 35
D 219
	if (a == NULL)
		return (NULL);
E 219
E 35
D 45
	m = Mailer[a->q_mailer];
E 45
I 45
D 130
	m = a->q_mailer;
E 130
E 45
E 18

	/*
D 18
	**  Interpret entry.
	**	t points to the entry for the mailer we will use.
	**	q points to the significant character.
E 18
I 18
	**  Make local copies of the host & user and then
	**  transport them out.
E 18
	*/

D 18
	if (a == NULL)
D 13
		a = (addrq *) xalloc(sizeof *a);
E 13
I 13
		a = (ADDRESS *) xalloc(sizeof *a);
E 18
E 13
D 130
	if (copyf > 0)
E 130
I 130
D 168
	allocaddr(a, copyf, addr);
E 168
I 168
D 218
	allocaddr(a, copyf, addr, *delimptr);
E 218
I 218
D 220
	allocaddr(a, flags, addr, *delimptr);
E 220
I 220
	allocaddr(a, flags, addr);
E 220
I 219
	if (bitset(QBADADDR, a->q_flags))
		return a;
E 219
E 218
E 168

	/*
I 186
	**  If there was a parsing failure, mark it for queueing.
	*/

	if (queueup)
I 194
	{
I 196
		char *msg = "Transient parse error -- message queued for future delivery";

E 196
		if (tTd(20, 1))
			printf("parseaddr: queuing message\n");
D 196
		message("Transient parse error -- message queued for future delivery");
E 196
I 196
		message(msg);
		if (e->e_message == NULL)
D 199
			e->e_message = msg;
E 199
I 199
			e->e_message = newstr(msg);
E 199
E 196
E 194
		a->q_flags |= QQUEUEUP;
I 258
D 263
		a->q_status = "466";
E 263
I 263
		a->q_status = "4.4.3";
E 263
E 258
I 194
	}
E 194

	/*
E 186
	**  Compute return value.
	*/

	if (tTd(20, 1))
E 130
I 69
	{
I 130
		printf("parseaddr-->");
		printaddr(a, FALSE);
	}

	return (a);
I 149
}
/*
**  INVALIDADDR -- check for address containing meta-characters
**
**	Parameters:
**		addr -- the address to check.
**
**	Returns:
**		TRUE -- if the address has any "wierd" characters
**		FALSE -- otherwise.
*/

bool
D 224
invalidaddr(addr)
E 224
I 224
invalidaddr(addr, delimptr)
E 224
	register char *addr;
I 224
	char *delimptr;
E 224
{
D 224
	for (; *addr != '\0'; addr++)
E 224
I 224
D 266
	char savedelim;
E 266
I 266
	char savedelim = '\0';
E 266

	if (delimptr != NULL)
I 226
	{
E 226
		savedelim = *delimptr;
I 226
		if (savedelim != '\0')
			*delimptr = '\0';
	}
E 226
#if 0
	/* for testing.... */
	if (strcmp(addr, "INvalidADDR") == 0)
E 224
	{
D 150
		if (((int) *addr & 0377) >= '\040')
E 150
I 150
D 152
		if ((((int) *addr) & 0377) >= '\040' || isspace(*addr))
E 152
I 152
D 162
		if (!isascii((int) *addr & 0377) ||
		    !iscntrl(*addr) || isspace(*addr))
E 162
I 162
D 224
		if ((*addr & 0340) != 0200)
E 162
E 152
E 150
			continue;
		setstat(EX_USAGE);
D 150
		usrerr("address contained invalid control characters");
E 150
I 150
D 166
		usrerr("Address contained invalid control characters");
E 166
I 166
		usrerr("553 Address contained invalid control characters");
E 224
I 224
		usrerr("553 INvalid ADDRess");
D 226
		if (delimptr != NULL)
			*delimptr = savedelim;
E 224
E 166
E 150
		return TRUE;
E 226
I 226
		goto addrfailure;
E 226
	}
D 224
	return FALSE;
E 224
I 224
#endif
	for (; *addr != '\0'; addr++)
	{
		if ((*addr & 0340) == 0200)
			break;
	}
D 226
	if (delimptr != NULL)
		*delimptr = savedelim;
E 226
	if (*addr == '\0')
I 226
	{
D 265
		if (savedelim != '\0' && delimptr != NULL)
E 265
I 265
		if (delimptr != NULL && savedelim != '\0')
E 265
			*delimptr = savedelim;
E 226
		return FALSE;
I 226
	}
E 226
	setstat(EX_USAGE);
	usrerr("553 Address contained invalid control characters");
I 226
  addrfailure:
D 267
	if (savedelim != '\0' && delimptr != NULL)
E 267
I 267
	if (delimptr != NULL && savedelim != '\0')
E 267
		*delimptr = savedelim;
E 226
	return TRUE;
E 224
E 149
}
/*
**  ALLOCADDR -- do local allocations of address on demand.
**
**	Also lowercases the host name if requested.
**
**	Parameters:
**		a -- the address to reallocate.
D 218
**		copyf -- the copy flag (see parseaddr for description).
E 218
I 218
**		flags -- the copy flag (see RF_ definitions in sendmail.h
**			for a description).
E 218
**		paddr -- the printname of the address.
I 168
D 220
**		delimptr -- a pointer to the address delimiter.  Must be set.
E 220
E 168
**
**	Returns:
**		none.
**
**	Side Effects:
**		Copies portions of a into local buffers as requested.
*/

I 284
void
E 284
D 168
allocaddr(a, copyf, paddr)
E 168
I 168
D 218
allocaddr(a, copyf, paddr, delimptr)
E 218
I 218
D 220
allocaddr(a, flags, paddr, delimptr)
E 220
I 220
allocaddr(a, flags, paddr)
E 220
E 218
E 168
	register ADDRESS *a;
D 218
	int copyf;
E 218
I 218
	int flags;
E 218
	char *paddr;
I 168
D 220
	char *delimptr;
E 220
E 168
{
D 207
	register MAILER *m = a->q_mailer;

E 207
I 174
	if (tTd(24, 4))
D 218
		printf("allocaddr(copyf=%d, paddr=%s)\n", copyf, paddr);
E 218
I 218
D 247
		printf("allocaddr(flags=%o, paddr=%s)\n", flags, paddr);
E 247
I 247
		printf("allocaddr(flags=%x, paddr=%s)\n", flags, paddr);
E 247
E 218

E 174
D 218
	if (copyf > 0 && paddr != NULL)
E 218
I 218
D 220
	if (bitset(RF_COPYPADDR, flags) && paddr != NULL)
E 218
	{
E 130
D 138
D 168
		extern char *DelimChar;
E 138
		char savec = *DelimChar;
E 168
I 168
		char savec = *delimptr;
E 220
I 220
	a->q_paddr = paddr;
E 220
E 168

D 168
		*DelimChar = '\0';
E 168
I 168
D 197
		*delimptr = '\0';
E 197
I 197
D 220
		if (savec != '\0')
			*delimptr = '\0';
E 197
E 168
E 69
D 13
	{
		p = xalloc((unsigned) strlen(addr) + 1);
		strcpy(p, addr);
		a->q_paddr = p;
	}
E 13
I 13
D 130
		a->q_paddr = newstr(addr);
E 130
I 130
		a->q_paddr = newstr(paddr);
E 130
I 69
D 168
		*DelimChar = savec;
E 168
I 168
D 197
		*delimptr = savec;
E 197
I 197
		if (savec != '\0')
			*delimptr = savec;
E 197
E 168
	}
E 69
E 13
	else
D 130
		a->q_paddr = addr;
E 130
I 130
		a->q_paddr = paddr;
E 130
I 117

E 220
	if (a->q_user == NULL)
		a->q_user = "";
	if (a->q_host == NULL)
		a->q_host = "";

E 117
I 14
D 16
	a->q_rmailer = t->p_mailer;
E 14
	a->q_mailer = &Mailer[t->p_mailer];
E 16
I 16
D 18
	a->q_mailer = a->q_rmailer = t->p_mailer;
E 18
E 16
D 64

E 64
D 13
	if (flagset(P_MOVE, t->p_flags))
E 13
I 13
D 18
	if (bitset(P_MOVE, t->p_flags))
E 18
I 18
D 218
	if (copyf >= 0)
E 218
I 218
	if (bitset(RF_COPYPARSE, flags))
E 218
E 18
E 13
	{
D 18
		/* send the message to another host & retry */
		a->q_host = t->p_arg;
		if (copyf >= 0)
D 13
		{
			p = xalloc((unsigned) strlen(buf) + 1);
			strcpy(p, buf);
			a->q_user = p;
		}
E 13
I 13
			a->q_user = newstr(buf);
E 18
I 18
D 117
		if (a->q_host != NULL)
			a->q_host = newstr(a->q_host);
E 18
E 13
		else
D 18
			a->q_user = buf;
E 18
I 18
			a->q_host = "";
E 117
I 117
		a->q_host = newstr(a->q_host);
E 117
		if (a->q_user != a->q_paddr)
			a->q_user = newstr(a->q_user);
E 18
	}
D 18
	else
	{
		/*
		**  Make local copies of the host & user and then
		**  transport them out.
		*/
E 18

I 130
	if (a->q_paddr == NULL)
		a->q_paddr = a->q_user;
D 173

E 130
D 18
		*q++ = '\0';
D 13
		if (flagset(P_HLAST, t->p_flags))
E 13
I 13
		if (bitset(P_HLAST, t->p_flags))
E 13
		{
			a->q_host = q;
			a->q_user = buf;
		}
		else
		{
			a->q_host = buf;
			a->q_user = q;
		}
I 5

		/*
		**  Don't go to the net if already on the target host.
		**	This is important on the berkeley network, since
		**	it get confused if we ask to send to ourselves.
		**	For nets like the ARPANET, we probably will have
		**	the local list set to NULL to simplify testing.
		**	The canonical representation of the name is also set
		**	to be just the local name so the duplicate letter
		**	suppression algorithm will work.
		*/

D 16
		if ((pvp = a->q_mailer->m_local) != NULL)
E 16
I 16
		if ((pvp = Mailer[a->q_mailer]->m_local) != NULL)
E 16
		{
			while (*pvp != NULL)
			{
				auto char buf2[MAXNAME];

				strcpy(buf2, a->q_host);
D 13
				if (!flagset(P_HST_UPPER, t->p_flags))
E 13
I 13
				if (!bitset(P_HST_UPPER, t->p_flags))
E 13
					makelower(buf2);
				if (strcmp(*pvp++, buf2) == 0)
				{
					strcpy(buf2, a->q_user);
					p = a->q_paddr;
					if (parse(buf2, a, -1) == NULL)
					{
						To = addr;
						return (NULL);
					}
					To = a->q_paddr = p;
					break;
				}
			}
		}

I 17
		/*
		**  Do host equivalence.
		**	This allows us to map together messages that
		**	would otherwise have several copies going
		**	through the same net link.
		*/

		for (hvp = Mailer[a->q_mailer]->m_hmap; *hvp != NULL; hvp++)
		{
			register bool doremap;

			doremap = FALSE;
			for (pvp = *hvp; *pvp != NULL; pvp++)
			{
				p = *pvp;
				if (*p == '\0')
				{
					/* null string: match everything */
					doremap = TRUE;
				}
				else if (strcmp(p, a->q_host) == 0)
					doremap = TRUE;
			}

			if (doremap)
			{
				a->q_host = pvp[-1];
				a->q_user = a->q_paddr;
			}
		}

E 17
		/* make copies if specified */
E 5
		if (copyf >= 0)
		{
D 13
			p = xalloc((unsigned) strlen(a->q_host) + 1);
			strcpy(p, a->q_host);
			a->q_host = p;
			p = xalloc((unsigned) strlen(a->q_user) + 1);
			strcpy(p, a->q_user);
			a->q_user = p;
E 13
I 13
			a->q_host = newstr(a->q_host);
D 17
			a->q_user = newstr(a->q_user);
E 17
I 17
			if (a->q_user != a->q_paddr)
				a->q_user = newstr(a->q_user);
E 17
E 13
		}
	}

E 18
	/*
I 103
	**  Convert host name to lower case if requested.
	**	User name will be done later.
	*/

	if (!bitnset(M_HST_UPPER, m->m_flags))
		makelower(a->q_host);
E 173
D 130

	/*
E 103
D 102
	**  Do UPPER->lower case mapping unless inhibited.
	*/

D 13
	if (!flagset(P_HST_UPPER, t->p_flags))
E 13
I 13
D 18
	if (!bitset(P_HST_UPPER, t->p_flags))
E 18
I 18
D 91
	if (!bitset(M_HST_UPPER, m->m_flags))
E 91
I 91
	if (!bitnset(M_HST_UPPER, m->m_flags))
E 91
E 18
E 13
		makelower(a->q_host);
D 13
	if (!flagset(P_USR_UPPER, t->p_flags))
E 13
I 13
D 18
	if (!bitset(P_USR_UPPER, t->p_flags))
E 18
I 18
D 91
	if (!bitset(M_USR_UPPER, m->m_flags))
E 91
I 91
	if (!bitnset(M_USR_UPPER, m->m_flags))
E 91
E 18
E 13
		makelower(a->q_user);

	/*
E 102
	**  Compute return value.
	*/

D 126
# ifdef DEBUG
E 126
D 6
	if (Debug && copyf >= 0)
E 6
I 6
D 60
	if (Debug)
E 60
I 60
	if (tTd(20, 1))
E 60
E 6
D 40
		printf("parse(\"%s\"): host \"%s\" user \"%s\" mailer %d\n",
D 18
		    addr, a->q_host, a->q_user, t->p_mailer);
E 18
I 18
		    addr, a->q_host, a->q_user, a->q_mailer);
E 40
I 40
	{
D 86
		printf("parse-->");
E 86
I 86
		printf("parseaddr-->");
E 86
		printaddr(a, FALSE);
	}
E 40
E 18
D 126
# endif DEBUG
E 126

	return (a);
E 130
I 102
}
/*
D 173
**  LOWERADDR -- map UPPER->lower case on addresses as requested.
**
**	Parameters:
**		a -- address to be mapped.
**
**	Returns:
**		none.
**
**	Side Effects:
**		none.
*/

I 138
void
E 138
loweraddr(a)
	register ADDRESS *a;
{
	register MAILER *m = a->q_mailer;

D 103
	if (!bitnset(M_HST_UPPER, m->m_flags))
		makelower(a->q_host);
E 103
	if (!bitnset(M_USR_UPPER, m->m_flags))
		makelower(a->q_user);
E 102
}
/*
E 173
I 138
**  INVALIDADDR -- check an address string for invalid control characters.
**
**	Parameters:
**		addr -- address string to be checked.
**
**	Returns:
**		TRUE if address string could cause problems, FALSE o/w.
**
**	Side Effects:
**		ExitStat may be changed and an error message generated.
*/

bool
invalidaddr(addr)
	const char *addr;
{
	register const char *cp;

	/* make sure error messages don't have garbage on them */
	errno = 0;

	/*
	** Sendmail reserves characters 020 - 036 for rewriting rules
	** which can cause havoc (e.g. infinite rewriting loops) if
	** one shows up at the wrong time.  If any of these characters
	** appear in an address, the address is deemed "invalid" and
	** an error message is generated.
	*/

	for (cp = addr; *cp; cp++)
		if ((*cp >= MATCHZANY && *cp <= HOSTEND) || *cp == '\001')
		{
			setstat(EX_USAGE);
			usrerr("address contained invalid control char(s)");
			return (TRUE);
		}
	return (FALSE);
}
/*
E 138
D 18
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
D 3
**	Requires:
**		isupper (sys)
**
E 3
**	Called By:
**		parse
D 3
**
**	History:
**		12/26/79 -- written.
E 3
*/

makelower(p)
	register char *p;
{
	register char c;

	if (p == NULL)
		return;
	for (; (c = *p) != '\0'; p++)
		if ((c & 0200) == 0 && isupper(c))
			*p = c - 'A' + 'a';
}
/*
E 18
**  PRESCAN -- Prescan name and make it canonical
**
D 83
**	Scans a name and turns it into canonical form.  This involves
**	deleting blanks, comments (in parentheses), and turning the
**	word "at" into an at-sign ("@").  The name is copied as this
**	is done; it is legal to copy a name onto itself, since this
**	process can only make things smaller.
E 83
I 83
**	Scans a name and turns it into a set of tokens.  This process
**	deletes blanks and comments (in parentheses).
E 83
**
**	This routine knows about quoted strings and angle brackets.
**
**	There are certain subtleties to this routine.  The one that
**	comes to mind now is that backslashes on the ends of names
**	are silently stripped off; this is intentional.  The problem
**	is that some versions of sndmsg (like at LBL) set the kill
**	character to something other than @ when reading addresses;
**	so people type "csvax.eric\@berkeley" -- which screws up the
**	berknet mailer.
**
**	Parameters:
**		addr -- the name to chomp.
D 18
**		buf -- the buffer to copy it into.
**		buflim -- the last usable address in the buffer
**			(which will old a null byte).  Normally
**			&buf[sizeof buf - 1].
E 18
**		delim -- the delimiter for the address, normally
**			'\0' or ','; \0 is accepted in any case.
I 100
**			If '\t' then we are reading the .cf file.
I 107
**		pvpbuf -- place to put the saved text -- note that
**			the pointers are static.
I 233
**		pvpbsize -- size of pvpbuf.
E 233
I 168
**		delimptr -- if non-NULL, set to the location of the
**			terminating delimiter.
I 277
**		toktab -- if set, a token table to use for parsing.
**			If NULL, use the default table.
E 277
E 168
E 107
E 100
D 69
**			are moving in place; set buflim to high core.
E 69
**
**	Returns:
D 18
**		A pointer to the terminator of buf.
E 18
I 18
**		A pointer to a vector of tokens.
E 18
**		NULL on error.
D 168
**
**	Side Effects:
D 18
**		buf gets clobbered.
**
D 3
**	Requires:
**		isspace (sys)
**		any
**		usrerr
**
E 3
**	Called By:
**		parse
**		maketemp
E 18
I 18
D 119
**		none.
E 119
I 119
**		sets DelimChar to point to the character matching 'delim'.
E 168
E 119
E 18
D 3
**
**	History:
**		12/30/79 -- broken from parse; comment processing
**			added.
E 3
*/

D 18
char *
prescan(addr, buf, buflim, delim)
E 18
I 18
D 69
# define OPER		1
# define ATOM		2
# define EOTOK		3
# define QSTRING	4
# define SPACE		5
D 54
# define DOLLAR		6
E 54
I 54
# define ONEMORE	6
E 54
# define GETONE		7
I 39
# define MACRO		8
E 69
I 69
/* states and character types */
# define OPR		0	/* operator */
# define ATM		1	/* atom */
# define QST		2	/* in quoted string */
# define SPC		3	/* chewing up spaces */
# define ONE		4	/* pick up one character */
I 277
# define ILL		5	/* illegal character */
E 277
E 69
E 39

I 69
D 277
# define NSTATES	5	/* number of states */
E 277
I 277
# define NSTATES	6	/* number of states */
E 277
# define TYPE		017	/* mask to select state type */

/* meta bits for table */
# define M		020	/* meta character; don't pass through */
# define B		040	/* cause a break */
# define MB		M|B	/* meta-break */

static short StateTab[NSTATES][NSTATES] =
{
D 70
   /*	oldst	newst>	OPR	ATM	QST	SPC	ONE	*/
E 70
I 70
D 277
   /*	oldst	chtype>	OPR	ATM	QST	SPC	ONE	*/
E 70
D 80
	/*OPR*/		OPR|B,	ATM|B,	QST|MB,	SPC|MB,	ONE|B,
	/*ATM*/		OPR|B,	ATM,	QST|MB,	SPC|MB,	ONE|B,
D 70
	/*QST*/		QST,	QST,	QST|MB,	QST,	QST,
E 70
I 70
	/*QST*/		QST,	QST,	OPR|MB,	QST,	QST,
E 80
I 80
	/*OPR*/		OPR|B,	ATM|B,	QST|B,	SPC|MB,	ONE|B,
	/*ATM*/		OPR|B,	ATM,	QST|B,	SPC|MB,	ONE|B,
	/*QST*/		QST,	QST,	OPR,	QST,	QST,
E 80
E 70
	/*SPC*/		OPR,	ATM,	QST,	SPC|M,	ONE,
	/*ONE*/		OPR,	OPR,	OPR,	OPR,	OPR,
E 277
I 277
   /*	oldst	chtype>	OPR	ATM	QST	SPC	ONE	ILL	*/
	/*OPR*/		OPR|B,	ATM|B,	QST|B,	SPC|MB,	ONE|B,	ILL|MB,
	/*ATM*/		OPR|B,	ATM,	QST|B,	SPC|MB,	ONE|B,	ILL|MB,
	/*QST*/		QST,	QST,	OPR,	QST,	QST,	QST,
	/*SPC*/		OPR,	ATM,	QST,	SPC|M,	ONE,	ILL|MB,
	/*ONE*/		OPR,	OPR,	OPR,	OPR,	OPR,	ILL|MB,
	/*ILL*/		OPR|B,	ATM|B,	QST|B,	SPC|MB,	ONE|B,	ILL|M,
E 277
};

I 235
/* token type table -- it gets modified with $o characters */
D 277
static TokTypeTab[256] =
E 277
I 277
D 284
static char TokTypeTab[256] =
E 284
I 284
static u_char	TokTypeTab[256] =
E 284
E 277
{
D 277
	ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,SPC,SPC,SPC,SPC,SPC,ATM,ATM,
	ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,
	SPC,ATM,QST,ATM,ATM,ATM,ATM,ATM,ATM,SPC,ATM,ATM,ATM,ATM,ATM,ATM,
	ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,
	ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,
	ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,
	ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,
	ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,
	OPR,OPR,ONE,OPR,OPR,OPR,OPR,OPR,OPR,OPR,OPR,OPR,OPR,OPR,OPR,OPR,
	OPR,OPR,OPR,ONE,ONE,ONE,OPR,OPR,OPR,OPR,OPR,OPR,OPR,OPR,OPR,OPR,
	ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,
	ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,
	ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,
	ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,
	ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,
	ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,
E 277
I 277
    /*	nul soh stx etx eot enq ack bel  bs  ht  nl  vt  np  cr  so  si   */
	ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM, ATM,SPC,SPC,SPC,SPC,SPC,ATM,ATM,
    /*	dle dc1 dc2 dc3 dc4 nak syn etb  can em  sub esc fs  gs  rs  us   */
	ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM, ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,
    /*  sp  !   "   #   $   %   &   '    (   )   *   +   ,   -   .   /    */
	SPC,ATM,QST,ATM,ATM,ATM,ATM,ATM, ATM,SPC,ATM,ATM,ATM,ATM,ATM,ATM,
    /*	0   1   2   3   4   5   6   7    8   9   :   ;   <   =   >   ?    */
	ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM, ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,
    /*	@   A   B   C   D   E   F   G    H   I   J   K   L   M   N   O    */
	ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM, ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,
    /*  P   Q   R   S   T   U   V   W    X   Y   Z   [   \   ]   ^   _    */
	ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM, ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,
    /*	`   a   b   c   d   e   f   g    h   i   j   k   l   m   n   o    */
	ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM, ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,
    /*  p   q   r   s   t   u   v   w    x   y   z   {   |   }   ~   del  */
	ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM, ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,

    /*	nul soh stx etx eot enq ack bel  bs  ht  nl  vt  np  cr  so  si   */
	OPR,OPR,ONE,OPR,OPR,OPR,OPR,OPR, OPR,OPR,OPR,OPR,OPR,OPR,OPR,OPR,
    /*	dle dc1 dc2 dc3 dc4 nak syn etb  can em  sub esc fs  gs  rs  us   */
	OPR,OPR,OPR,ONE,ONE,ONE,OPR,OPR, OPR,OPR,OPR,OPR,OPR,OPR,OPR,OPR,
    /*  sp  !   "   #   $   %   &   '    (   )   *   +   ,   -   .   /    */
	ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM, ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,
    /*	0   1   2   3   4   5   6   7    8   9   :   ;   <   =   >   ?    */
	ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM, ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,
    /*	@   A   B   C   D   E   F   G    H   I   J   K   L   M   N   O    */
	ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM, ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,
    /*  P   Q   R   S   T   U   V   W    X   Y   Z   [   \   ]   ^   _    */
	ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM, ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,
    /*	`   a   b   c   d   e   f   g    h   i   j   k   l   m   n   o    */
	ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM, ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,
    /*  p   q   r   s   t   u   v   w    x   y   z   {   |   }   ~   del  */
	ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM, ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,
E 277
};

D 277
#define toktype(c)	((int) TokTypeTab[(c) & 0xff])
E 277
I 277
/* token type table for MIME parsing */
D 284
char MimeTokenTab[256] =
E 284
I 284
u_char	MimeTokenTab[256] =
E 284
{
    /*	nul soh stx etx eot enq ack bel  bs  ht  nl  vt  np  cr  so  si   */
	ILL,ILL,ILL,ILL,ILL,ILL,ILL,ILL, ILL,SPC,SPC,SPC,SPC,SPC,ILL,ILL,
    /*	dle dc1 dc2 dc3 dc4 nak syn etb  can em  sub esc fs  gs  rs  us   */
	ILL,ILL,ILL,ILL,ILL,ILL,ILL,ILL, ILL,ILL,ILL,ILL,ILL,ILL,ILL,ILL,
    /*  sp  !   "   #   $   %   &   '    (   )   *   +   ,   -   .   /    */
	SPC,ATM,QST,ATM,ATM,ATM,ATM,ATM, ATM,SPC,ATM,ATM,OPR,ATM,ATM,OPR,
    /*	0   1   2   3   4   5   6   7    8   9   :   ;   <   =   >   ?    */
	ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM, ATM,ATM,OPR,OPR,OPR,OPR,OPR,OPR,
    /*	@   A   B   C   D   E   F   G    H   I   J   K   L   M   N   O    */
	OPR,ATM,ATM,ATM,ATM,ATM,ATM,ATM, ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,
    /*  P   Q   R   S   T   U   V   W    X   Y   Z   [   \   ]   ^   _    */
	ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM, ATM,ATM,ATM,OPR,OPR,OPR,ATM,ATM,
    /*	`   a   b   c   d   e   f   g    h   i   j   k   l   m   n   o    */
	ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM, ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,
    /*  p   q   r   s   t   u   v   w    x   y   z   {   |   }   ~   del  */
	ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM, ATM,ATM,ATM,ATM,ATM,ATM,ATM,ATM,
E 277

I 277
    /*	nul soh stx etx eot enq ack bel  bs  ht  nl  vt  np  cr  so  si   */
	ILL,ILL,ILL,ILL,ILL,ILL,ILL,ILL, ILL,ILL,ILL,ILL,ILL,ILL,ILL,ILL,
    /*	dle dc1 dc2 dc3 dc4 nak syn etb  can em  sub esc fs  gs  rs  us   */
	ILL,ILL,ILL,ILL,ILL,ILL,ILL,ILL, ILL,ILL,ILL,ILL,ILL,ILL,ILL,ILL,
    /*  sp  !   "   #   $   %   &   '    (   )   *   +   ,   -   .   /    */
	ILL,ILL,ILL,ILL,ILL,ILL,ILL,ILL, ILL,ILL,ILL,ILL,ILL,ILL,ILL,ILL,
    /*	0   1   2   3   4   5   6   7    8   9   :   ;   <   =   >   ?    */
	ILL,ILL,ILL,ILL,ILL,ILL,ILL,ILL, ILL,ILL,ILL,ILL,ILL,ILL,ILL,ILL,
    /*	@   A   B   C   D   E   F   G    H   I   J   K   L   M   N   O    */
	ILL,ILL,ILL,ILL,ILL,ILL,ILL,ILL, ILL,ILL,ILL,ILL,ILL,ILL,ILL,ILL,
    /*  P   Q   R   S   T   U   V   W    X   Y   Z   [   \   ]   ^   _    */
	ILL,ILL,ILL,ILL,ILL,ILL,ILL,ILL, ILL,ILL,ILL,ILL,ILL,ILL,ILL,ILL,
    /*	`   a   b   c   d   e   f   g    h   i   j   k   l   m   n   o    */
	ILL,ILL,ILL,ILL,ILL,ILL,ILL,ILL, ILL,ILL,ILL,ILL,ILL,ILL,ILL,ILL,
    /*  p   q   r   s   t   u   v   w    x   y   z   {   |   }   ~   del  */
	ILL,ILL,ILL,ILL,ILL,ILL,ILL,ILL, ILL,ILL,ILL,ILL,ILL,ILL,ILL,ILL,
};
E 277

I 277

E 277
E 235
# define NOCHAR		-1	/* signal nothing in lookahead token */

D 138
D 168
char	*DelimChar;		/* set to point to the delimiter */

E 168
E 138
E 69
char **
D 107
prescan(addr, delim)
E 107
I 107
D 168
prescan(addr, delim, pvpbuf)
E 168
I 168
D 233
prescan(addr, delim, pvpbuf, delimptr)
E 233
I 233
D 277
prescan(addr, delim, pvpbuf, pvpbsize, delimptr)
E 277
I 277
prescan(addr, delim, pvpbuf, pvpbsize, delimptr, toktab)
E 277
E 233
E 168
E 107
E 18
	char *addr;
D 18
	char *buf;
	char *buflim;
E 18
D 262
	char delim;
E 262
I 262
	int delim;
E 262
I 107
	char pvpbuf[];
I 168
	char **delimptr;
I 277
D 284
	char *toktab;
E 284
I 284
	u_char *toktab;
E 284
E 277
E 168
E 107
{
	register char *p;
I 18
D 69
	static char buf[MAXNAME+MAXATOM];
	static char *av[MAXATOM+1];
E 69
I 69
	register char *q;
D 82
	register char c;
E 82
I 82
	register int c;
E 82
E 69
	char **avp;
E 18
D 36
	bool space;
E 36
D 18
	bool quotemode;
E 18
	bool bslashmode;
I 9
D 18
	bool delimmode;
E 18
E 9
	int cmntcnt;
I 76
	int anglecnt;
E 76
D 63
	int brccnt;
E 63
D 69
	register char c;
E 69
I 18
	char *tok;
E 18
D 69
	register char *q;
D 13
	extern bool any();
E 13
I 13
D 28
	extern char *index();
E 28
I 18
	register int state;
	int nstate;
I 28
	extern char lower();
E 69
I 69
	int state;
	int newstate;
I 197
	char *saveto = CurEnv->e_to;
E 197
D 107
	static char buf[MAXNAME+MAXATOM];
E 107
	static char *av[MAXATOM+1];
I 235
	static char firsttime = TRUE;
E 235
I 99
D 138
	extern int errno;
E 138

I 235
	if (firsttime)
	{
		/* initialize the token type table */
		char obuf[50];

		firsttime = FALSE;
D 270
		expand("\201o", obuf, &obuf[sizeof obuf - sizeof DELIMCHARS], CurEnv);
E 270
I 270
		expand("\201o", obuf, sizeof obuf - sizeof DELIMCHARS, CurEnv);
E 270
		strcat(obuf, DELIMCHARS);
		for (p = obuf; *p != '\0'; p++)
		{
			if (TokTypeTab[*p & 0xff] == ATM)
				TokTypeTab[*p & 0xff] = OPR;
		}
	}
I 277
	if (toktab == NULL)
		toktab = TokTypeTab;
E 277

E 235
	/* make sure error messages don't have garbage on them */
	errno = 0;
E 99
E 69
E 28
E 18
E 13

D 9
	space = TRUE;
E 9
I 9
D 36
	space = FALSE;
E 36
D 18
	delimmode = TRUE;
E 18
E 9
D 107
	q = buf;
E 107
I 107
	q = pvpbuf;
E 107
D 18
	bslashmode = quotemode = FALSE;
E 18
I 18
	bslashmode = FALSE;
E 18
D 63
	cmntcnt = brccnt = 0;
E 63
I 63
	cmntcnt = 0;
I 76
	anglecnt = 0;
E 76
E 63
D 7
	for (p = addr; (c = *p++ & 0177) != '\0'; )
E 7
I 7
D 18
	for (p = addr; (c = *p++) != '\0'; )
E 18
I 18
	avp = av;
D 69
	state = OPER;
	for (p = addr; *p != '\0' && *p != delim; )
E 69
I 69
D 135
	state = OPR;
E 135
I 135
	state = ATM;
E 135
	c = NOCHAR;
	p = addr;
I 197
	CurEnv->e_to = p;
E 197
D 126
# ifdef DEBUG
E 126
D 142
	if (tTd(22, 45))
E 142
I 142
	if (tTd(22, 11))
E 142
E 69
E 18
E 7
	{
I 69
		printf("prescan: ");
		xputs(p);
D 115
		putchar('\n');
E 115
I 115
		(void) putchar('\n');
E 115
	}
D 126
# endif DEBUG
E 126

	do
	{
E 69
D 18
		/* chew up special characters */
		*q = '\0';
		if (bslashmode)
E 18
I 18
		/* read a token */
		tok = q;
D 69
		while ((c = *p++) != '\0' && c != delim)
E 69
I 69
		for (;;)
E 69
E 18
		{
I 69
			/* store away any old lookahead character */
D 191
			if (c != NOCHAR)
E 191
I 191
			if (c != NOCHAR && !bslashmode)
E 191
			{
D 100
				/* squirrel it away */
E 100
I 100
				/* see if there is room */
E 100
D 107
				if (q >= &buf[sizeof buf - 5])
E 107
I 107
D 233
				if (q >= &pvpbuf[PSBUFSIZE - 5])
E 233
I 233
				if (q >= &pvpbuf[pvpbsize - 5])
E 233
E 107
				{
D 166
					usrerr("Address too long");
E 166
I 166
					usrerr("553 Address too long");
I 268
					if (strlen(addr) > MAXNAME)
						addr[MAXNAME] = '\0';
E 268
I 231
	returnnull:
E 231
E 166
D 168
					DelimChar = p;
E 168
I 168
					if (delimptr != NULL)
						*delimptr = p;
I 197
					CurEnv->e_to = saveto;
E 197
E 168
					return (NULL);
				}
I 100

				/* squirrel it away */
E 100
				*q++ = c;
			}

			/* read a new input character */
			c = *p++;
D 142
			if (c == '\0')
				break;
E 142
I 142
D 153
			if (c == '\0' || (c == delim && anglecnt <= 0))
E 153
I 153
D 156
			if (c == '\0' ||
			    (c == delim && anglecnt <= 0 && cmntcnt <= 0))
E 156
I 156
			if (c == '\0')
E 156
E 153
			{
				/* diagnose and patch up bad syntax */
				if (state == QST)
				{
D 166
					usrerr("Unbalanced '\"'");
E 166
I 166
D 216
					usrerr("553 Unbalanced '\"'");
E 216
I 216
D 217
					usrerr("653 Unbalanced '\"'");
E 217
I 217
D 227
					usrerr("653 Unbalanced '\"' (fixed)");
E 227
I 227
					usrerr("653 Unbalanced '\"'");
E 227
E 217
E 216
E 166
					c = '"';
				}
				else if (cmntcnt > 0)
				{
D 166
					usrerr("Unbalanced '('");
E 166
I 166
D 216
					usrerr("553 Unbalanced '('");
E 216
I 216
D 217
					usrerr("653 Unbalanced '('");
E 217
I 217
D 227
					usrerr("653 Unbalanced '(' (fixed)");
E 227
I 227
					usrerr("653 Unbalanced '('");
E 227
E 217
E 216
E 166
					c = ')';
				}
				else if (anglecnt > 0)
				{
					c = '>';
D 166
					usrerr("Unbalanced '<'");
E 166
I 166
D 216
					usrerr("553 Unbalanced '<'");
E 216
I 216
D 217
					usrerr("653 Unbalanced '<'");
E 217
I 217
D 227
					usrerr("653 Unbalanced '<' (fixed)");
E 227
I 227
					usrerr("653 Unbalanced '<'");
E 227
E 217
E 216
E 166
				}
				else
					break;
E 142
I 100
D 135
D 138
			c &= ~0200;
E 138
I 138
			c &= 0177;
E 138
E 135

I 142
				p--;
			}
I 156
			else if (c == delim && anglecnt <= 0 &&
					cmntcnt <= 0 && state != QST)
				break;
E 156

E 142
E 100
D 126
# ifdef DEBUG
E 126
			if (tTd(22, 101))
				printf("c=%c, s=%d; ", c, state);
D 126
# endif DEBUG
E 126

E 69
D 18
			c |= 0200;
D 7
			bslashmode == FALSE;
E 7
I 7
			bslashmode = FALSE;
E 18
I 18
			/* chew up special characters */
I 29
D 100
			c &= ~0200;
E 100
E 29
			*q = '\0';
			if (bslashmode)
			{
I 188
				bslashmode = FALSE;

E 188
D 117
				c |= 0200;
E 117
I 117
				/* kludge \! for naive users */
D 163
				if (c != '!')
E 163
I 163
				if (cmntcnt > 0)
I 188
				{
E 188
					c = NOCHAR;
D 188
				else if (c != '!')
E 188
I 188
					continue;
				}
				else if (c != '!' || state == QST)
				{
E 188
E 163
D 135
					c |= 0200;
E 135
I 135
					*q++ = '\\';
E 135
E 117
D 188
				bslashmode = FALSE;
I 138
				if (cmntcnt > 0)
					c = NOCHAR;
E 138
I 135
				continue;
E 188
I 188
					continue;
				}
E 188
E 135
			}
D 131
			else if (c == '\\')
E 131
I 131

			if (c == '\\')
E 131
			{
				bslashmode = TRUE;
D 69
				continue;
E 69
I 69
D 191
				c = NOCHAR;
I 135
				continue;
E 191
E 135
E 69
			}
I 77
D 138
			else if (state == QST)
E 138
I 138
			if (state == QST)
E 138
			{
				/* do nothing, just avoid next clauses */
			}
E 77
I 29
D 69
			else if (c == '"')
E 69
I 69
			else if (c == '(')
E 69
			{
D 69
				if (state == QSTRING)
					state = OPER;
				else
					state = QSTRING;
				break;
E 69
I 69
				cmntcnt++;
				c = NOCHAR;
E 69
			}
E 29
D 69

D 39
			nstate = toktype(c);
E 39
I 39
D 54
			if (c == '$' && delim == '\t')
				nstate = DOLLAR;
			else
				nstate = toktype(c);
E 54
I 54
			nstate = toktype(c);
E 54
E 39
			switch (state)
E 69
I 69
			else if (c == ')')
E 69
			{
D 69
			  case QSTRING:		/* in quoted string */
D 29
				if (c == '"')
					state = OPER;
E 29
				break;

			  case ATOM:		/* regular atom */
D 33
				state = nstate;
				if (state != ATOM)
E 33
I 33
D 39
				/* state = nstate; */
E 39
				if (nstate != ATOM)
E 69
I 69
				if (cmntcnt <= 0)
E 69
E 33
				{
D 69
					state = EOTOK;
					p--;
E 69
I 69
D 166
					usrerr("Unbalanced ')'");
E 166
I 166
D 216
					usrerr("553 Unbalanced ')'");
E 216
I 216
D 217
					usrerr("653 Unbalanced ')'");
E 217
I 217
D 227
					usrerr("653 Unbalanced ')' (fixed)");
E 227
I 227
					usrerr("653 Unbalanced ')'");
E 227
E 217
E 216
E 166
D 168
					DelimChar = p;
E 168
I 168
D 215
					if (delimptr != NULL)
						*delimptr = p;
I 197
					CurEnv->e_to = saveto;
E 197
E 168
					return (NULL);
E 215
I 215
					c = NOCHAR;
E 215
E 69
				}
D 69
				break;
E 69
I 69
				else
					cmntcnt--;
			}
			else if (cmntcnt > 0)
				c = NOCHAR;
I 76
			else if (c == '<')
				anglecnt++;
			else if (c == '>')
			{
				if (anglecnt <= 0)
				{
D 166
					usrerr("Unbalanced '>'");
E 166
I 166
D 216
					usrerr("553 Unbalanced '>'");
E 216
I 216
D 217
					usrerr("653 Unbalanced '>'");
E 217
I 217
D 227
					usrerr("653 Unbalanced '>' (fixed)");
E 227
I 227
					usrerr("653 Unbalanced '>'");
E 227
E 217
E 216
E 166
D 168
					DelimChar = p;
E 168
I 168
D 215
					if (delimptr != NULL)
						*delimptr = p;
I 197
					CurEnv->e_to = saveto;
E 197
E 168
					return (NULL);
E 215
I 215
					c = NOCHAR;
E 215
				}
D 215
				anglecnt--;
E 215
I 215
				else
					anglecnt--;
E 215
			}
I 95
D 162
			else if (delim == ' ' && isspace(c))
E 162
I 162
			else if (delim == ' ' && isascii(c) && isspace(c))
E 162
				c = ' ';
E 95
E 76
I 72
			else if (c == ':' && !CurEnv->e_oldstyle)
			{
				/* consume characters until a semicolon */
				while (*p != '\0' && *p != ';')
					p++;
				if (*p == '\0')
					usrerr("Unbalanced ':...;' group spec");
				else
					p++;
				c = ' ';
			}
E 72
E 69

I 138
			else if (c == ';') /* semicolons are not tokens */
				c = NOCHAR;

E 138
D 69
			  case GETONE:		/* grab one character */
				state = OPER;
				break;
E 69
I 69
			if (c == NOCHAR)
				continue;
E 69

D 69
			  case EOTOK:		/* after atom or q-string */
				state = nstate;
				if (state == SPACE)
					continue;
E 69
I 69
			/* see if this is end of input */
D 76
			if (c == delim)
E 76
I 76
D 94
			if (c == delim && anglecnt <= 0)
E 94
I 94
			if (c == delim && anglecnt <= 0 && state != QST)
E 94
E 76
E 69
				break;

D 69
			  case SPACE:		/* linear white space */
				state = nstate;
E 69
I 69
D 277
			newstate = StateTab[state][toktype(c)];
E 277
I 277
			newstate = StateTab[state][toktab[c & 0xff]];
E 277
D 126
# ifdef DEBUG
E 126
			if (tTd(22, 101))
				printf("ns=%02o\n", newstate);
D 126
# endif DEBUG
E 126
			state = newstate & TYPE;
I 277
			if (state == ILL)
			{
				if (isascii(c) && isprint(c))
					usrerr("653 Illegal character %c", c);
				else
					usrerr("653 Illegal character 0x%02x", c);
			}
E 277
			if (bitset(M, newstate))
				c = NOCHAR;
			if (bitset(B, newstate))
E 69
D 36
				space = TRUE;
E 36
D 33
				continue;
E 33
I 33
				break;
E 33
D 69

			  case OPER:		/* operator */
				if (nstate == SPACE)
					continue;
				state = nstate;
				break;

D 54
			  case DOLLAR:		/* $- etc. */
				state = OPER;
I 42
				if (isascii(c) && isdigit(c))
				{
					/* replacement */
					c = MATCHREPL;
					state = GETONE;
					p--;
					break;
				}
E 42
				switch (c)
				{
				  case '$':		/* literal $ */
					break;

				  case '+':		/* match anything */
					c = MATCHANY;
D 42
					state = GETONE;
E 42
					break;

				  case '-':		/* match one token */
					c = MATCHONE;
D 42
					state = GETONE;
E 42
					break;

I 25
				  case '=':		/* match one token of class */
					c = MATCHCLASS;
					state = GETONE;
					break;

E 25
				  case '#':		/* canonical net name */
					c = CANONNET;
					break;

				  case '@':		/* canonical host name */
					c = CANONHOST;
					break;

				  case ':':		/* canonical user name */
					c = CANONUSER;
					break;

				  default:
D 39
					c = '$';
					state = OPER;
					p--;
E 39
I 39
					state = MACRO;
E 39
					break;
				}
E 54
I 54
			  case ONEMORE:		/* $- etc. */
				state = GETONE;
E 54
				break;

			  default:
				syserr("prescan: unknown state %d", state);
			}

D 33
			if (state == OPER)
				space = FALSE;
			else if (state == EOTOK)
E 33
I 33
			if (state == EOTOK || state == SPACE)
E 33
				break;
D 39
			if (c == '$' && delim == '\t')
			{
				state = DOLLAR;
E 39
I 39
D 54
			if (state == DOLLAR)
E 39
				continue;
E 54
D 39
			}
E 39

			/* squirrel it away */
			if (q >= &buf[sizeof buf - 5])
			{
				usrerr("Address too long");
				return (NULL);
I 39
			}
D 54
			if (state == MACRO)
			{
				char mbuf[3];

				mbuf[0] = '$';
				mbuf[1] = c;
				mbuf[2] = '\0';
				(void) expand(mbuf, q, &buf[sizeof buf - 5]);
				q += strlen(q);
				state = EOTOK;
				break;
E 39
			}
E 54
D 33
			if (space)
				*q++ = SPACESUB;
E 33
			*q++ = c;

			/* decide whether this represents end of token */
D 54
			if (state == OPER)
E 54
I 54
			if (state == OPER || state == GETONE)
E 54
				break;
E 69
E 18
E 7
		}
D 18
		else if (c == '"')
			quotemode = !quotemode;
		else if (c == '\\')
		{
			bslashmode++;
E 18
I 18
D 69
		if (c == '\0' || c == delim)
			p--;
E 69

		/* new token */
D 69
		if (tok == q)
E 18
			continue;
D 18
		}
		else if (quotemode)
			c |= 0200;
		else if (c == delim)
			break;
		else if (c == '(')
E 18
I 18
		*q++ = '\0';

		c = tok[0];
		if (c == '(')
E 69
I 69
		if (tok != q)
E 69
E 18
I 4
		{
E 4
D 69
			cmntcnt++;
I 4
			continue;
		}
E 4
		else if (c == ')')
		{
			if (cmntcnt <= 0)
E 69
I 69
			*q++ = '\0';
D 126
# ifdef DEBUG
E 126
			if (tTd(22, 36))
E 69
			{
D 69
				usrerr("Unbalanced ')'");
				return (NULL);
E 69
I 69
				printf("tok=");
				xputs(tok);
D 115
				putchar('\n');
E 115
I 115
				(void) putchar('\n');
E 115
E 69
			}
D 69
			else
E 69
I 69
D 126
# endif DEBUG
E 126
			if (avp >= &av[MAXATOM])
E 69
			{
D 69
				cmntcnt--;
				continue;
E 69
I 69
D 166
				syserr("prescan: too many tokens");
E 166
I 166
				syserr("553 prescan: too many tokens");
E 166
D 168
				DelimChar = p;
E 168
I 168
D 231
				if (delimptr != NULL)
					*delimptr = p;
I 197
				CurEnv->e_to = saveto;
E 197
E 168
				return (NULL);
E 231
I 231
				goto returnnull;
			}
			if (q - tok > MAXNAME)
			{
				syserr("553 prescan: token too long");
				goto returnnull;
E 231
E 69
			}
I 69
			*avp++ = tok;
E 69
		}
I 9
D 18
		if (cmntcnt > 0)
E 18
I 18
D 69
		else if (cmntcnt > 0)
E 18
			continue;
D 18
		else if (isascii(c) && isspace(c) && (space || delimmode))
			continue;
E 9
D 4
		if (cmntcnt > 0)
			continue;
E 4
		else if (c == '<')
E 18
I 18

I 38
D 41
		if (avp >= &av[MAXATOM])
		{
			syserr("prescan: too many tokens");
			return (NULL);
		}
E 38
		*avp++ = tok;

E 41
D 63
		/* we prefer <> specs */
		if (c == '<')
E 18
		{
I 10
			if (brccnt < 0)
			{
				usrerr("multiple < spec");
				return (NULL);
			}
E 10
			brccnt++;
I 9
D 18
			delimmode = TRUE;
E 18
D 36
			space = FALSE;
E 36
E 9
			if (brccnt == 1)
			{
				/* we prefer using machine readable name */
				q = buf;
				*q = '\0';
I 18
				avp = av;
E 18
				continue;
			}
		}
		else if (c == '>')
		{
			if (brccnt <= 0)
			{
				usrerr("Unbalanced `>'");
				return (NULL);
			}
			else
				brccnt--;
			if (brccnt <= 0)
I 10
			{
				brccnt = -1;
E 10
				continue;
I 10
			}
E 10
		}
I 41

E 63
		if (avp >= &av[MAXATOM])
		{
			syserr("prescan: too many tokens");
			return (NULL);
		}
		*avp++ = tok;
E 41
D 32

		/*
		**  Turn "at" into "@",
D 4
		**	but only if "at" is a word in and to itself.
E 4
I 4
		**	but only if "at" is a word.
E 4
D 18
		**	By the way, I violate the ARPANET RFC-733
		**	standard here, by assuming that 'space' delimits
		**	atoms.  I assume that is just a mistake, since
		**	it violates the spirit of the semantics
		**	of the document.....
E 18
		*/

D 9
		if (space && (c == 'a' || c == 'A') &&
E 9
I 9
D 18
		if (delimmode && (c == 'a' || c == 'A') &&
E 9
		    (p[0] == 't' || p[0] == 'T') &&
D 9
		    (any(p[1], "()<>@,;:\\\"") || p[1] <= 040))
E 9
I 9
D 13
		    (any(p[1], DELIMCHARS) || p[1] <= 040))
E 13
I 13
		    (index(DELIMCHARS, p[1]) != NULL || p[1] <= 040))
E 18
I 18
		if (lower(tok[0]) == 'a' && lower(tok[1]) == 't' && tok[2] == '\0')
E 18
E 13
E 9
		{
D 18
			c = '@';
			p++;
E 18
I 18
			tok[0] = '@';
			tok[1] = '\0';
E 18
		}
E 32
I 18
	}
E 69
I 69
D 76
	} while (c != '\0' && c != delim);
E 76
I 76
	} while (c != '\0' && (c != delim || anglecnt > 0));
E 76
E 69
	*avp = NULL;
I 69
D 168
	DelimChar = --p;
E 168
I 168
	p--;
	if (delimptr != NULL)
		*delimptr = p;
E 168
E 69
D 142
	if (cmntcnt > 0)
		usrerr("Unbalanced '('");
I 76
	else if (anglecnt > 0)
		usrerr("Unbalanced '<'");
E 76
D 63
	else if (brccnt > 0)
		usrerr("Unbalanced '<'");
E 63
D 69
	else if (state == QSTRING)
E 69
I 69
	else if (state == QST)
E 69
		usrerr("Unbalanced '\"'");
	else if (av[0] != NULL)
E 142
I 142
	if (tTd(22, 12))
	{
		printf("prescan==>");
		printav(av);
	}
I 197
	CurEnv->e_to = saveto;
E 197
I 172
	if (av[0] == NULL)
I 230
	{
		if (tTd(22, 1))
			printf("prescan: null leading token\n");
E 230
		return (NULL);
I 230
	}
E 230
E 172
D 169
	if (av[0] != NULL)
E 142
		return (av);
	return (NULL);
E 169
I 169
	return (av);
E 169
D 235
}
/*
**  TOKTYPE -- return token type
**
**	Parameters:
**		c -- the character in question.
**
**	Returns:
**		Its type.
**
**	Side Effects:
**		none.
*/
E 18

I 138
static int
E 138
I 9
D 13
		if (delimmode = any(c, DELIMCHARS))
E 13
I 13
D 18
		if (delimmode = (index(DELIMCHARS, c) != NULL))
E 13
			space = FALSE;
E 18
I 18
toktype(c)
D 162
	register char c;
E 162
I 162
	register int c;
E 162
{
I 23
	static char buf[50];
D 24
	static char firstime;
E 24
I 24
	static bool firstime = TRUE;
E 24

D 24
	if (firstime++ == 0)
E 24
I 24
	if (firstime)
E 24
	{
I 24
		firstime = FALSE;
E 24
D 28
		expand("$o", buf, &buf[sizeof buf - 1]);
E 28
I 28
D 57
		(void) expand("$o", buf, &buf[sizeof buf - 1]);
E 57
I 57
D 101
		expand("$o", buf, &buf[sizeof buf - 1], CurEnv);
E 101
I 101
D 162
		expand("\001o", buf, &buf[sizeof buf - 1], CurEnv);
E 162
I 162
		expand("\201o", buf, &buf[sizeof buf - 1], CurEnv);
E 162
E 101
E 57
E 28
D 59
		strcat(buf, DELIMCHARS);
E 59
I 59
		(void) strcat(buf, DELIMCHARS);
E 59
	}
I 162
	c &= 0377;
E 162
I 54
D 84
	if (c == MATCHCLASS || c == MATCHREPL)
E 84
I 84
D 138
	if (c == MATCHCLASS || c == MATCHREPL || c == MATCHNCLASS)
E 138
I 138
D 139
	if (c == MATCHCLASS || c == MATCHREPL || c == MATCHNCLASS ||
	    c == MATCHMAP   || c == MATCHNMAP)
E 139
I 139
	if (c == MATCHCLASS || c == MATCHREPL || c == MATCHNCLASS)
E 139
E 138
E 84
D 69
		return (ONEMORE);
E 69
I 69
		return (ONE);
I 184
	if (c == MACRODEXPAND)
		return (ONE);
E 184
I 138
#ifdef MACVALUE
	if (c == MACVALUE)
		return (ONE);
#endif /* MACVALUE */
E 138
	if (c == '"')
		return (QST);
I 162
	if ((c & 0340) == 0200)
		return (OPR);
E 162
E 69
E 54
I 29
	if (!isascii(c))
D 69
		return (ATOM);
E 29
E 23
	if (isspace(c))
		return (SPACE);
E 69
I 69
		return (ATM);
	if (isspace(c) || c == ')')
		return (SPC);
E 69
D 23
	if (index(DELIMCHARS, c) != NULL || iscntrl(c))
E 23
I 23
D 143
	if (iscntrl(c) || index(buf, c) != NULL)
E 143
I 143
D 162
	if (iscntrl(c) || strchr(buf, c) != NULL)
E 162
I 162
	if (strchr(buf, c) != NULL)
E 162
E 143
E 23
D 69
		return (OPER);
	return (ATOM);
E 69
I 69
		return (OPR);
	return (ATM);
E 235
E 69
}
/*
**  REWRITE -- apply rewrite rules to token vector.
**
I 44
**	This routine is an ordered production system.  Each rewrite
**	rule has a LHS (called the pattern) and a RHS (called the
**	rewrite); 'rwr' points the the current rewrite rule.
**
**	For each rewrite rule, 'avp' points the address vector we
**	are trying to match against, and 'pvp' points to the pattern.
D 67
**	If pvp points to a special match value (MATCHANY, MATCHONE,
**	MATCHCLASS) then the address in avp matched is saved away
**	in the match vector (pointed to by 'mvp').
E 67
I 67
**	If pvp points to a special match value (MATCHZANY, MATCHANY,
D 84
**	MATCHONE, MATCHCLASS) then the address in avp matched is
**	saved away in the match vector (pointed to by 'mvp').
E 84
I 84
**	MATCHONE, MATCHCLASS, MATCHNCLASS) then the address in avp
**	matched is saved away in the match vector (pointed to by 'mvp').
E 84
E 67
**
**	When a match between avp & pvp does not match, we try to
D 84
**	back out.  If we back up over a MATCHONE or a MATCHCLASS
E 84
I 84
**	back out.  If we back up over MATCHONE, MATCHCLASS, or MATCHNCLASS
E 84
**	we must also back out the match in mvp.  If we reach a
D 67
**	MATCHANY we just extend the match and start over again.
E 67
I 67
**	MATCHANY or MATCHZANY we just extend the match and start
**	over again.
E 67
**
**	When we finally match, we rewrite the address vector
**	and try over again.
**
E 44
**	Parameters:
**		pvp -- pointer to token vector.
I 184
**		ruleset -- the ruleset to use for rewriting.
I 234
**		reclevel -- recursion level (to catch loops).
E 234
**		e -- the current envelope.
E 184
**
**	Returns:
D 186
**		none.
E 186
I 186
**		A status code.  If EX_TEMPFAIL, higher level code should
**			attempt recovery.
E 186
**
**	Side Effects:
**		pvp is modified.
*/
E 18

I 138
# define OP_NONZLEN	00001
# define OP_VARLEN	00002
# define OP_CLASS	00004
# define OP_EXACT	00010

E 138
E 9
D 10
		/* skip blanks */
D 9
		if (((c & 0200) != 0 || !isspace(c)) && cmntcnt <= 0)
E 9
I 9
		if (!isascii(c) || !isspace(c))
E 10
I 10
D 18
		/* if not a space, squirrel it away */
		if ((!isascii(c) || !isspace(c)) && brccnt >= 0)
E 18
I 18
struct match
{
D 42
	char	**firsttok;	/* first token matched */
	char	**lasttok;	/* last token matched */
	char	name;		/* name of parameter */
E 42
I 42
	char	**first;	/* first token matched */
	char	**last;		/* last token matched */
I 180
	char	**pattern;	/* pointer to pattern */
E 180
I 138
	char	**source;	/* left hand source operand */
	char	flags;		/* attributes of this operator */
E 138
E 42
};

D 42
# define MAXMATCH	8	/* max params per rewrite */
E 42
I 42
# define MAXMATCH	9	/* max params per rewrite */
I 138
# define MAX_CONTROL ' '
E 138
E 42

I 238
# ifndef MAXRULERECURSION
#  define MAXRULERECURSION	50	/* max recursion depth */
# endif
E 238
I 138
static char control_opts[MAX_CONTROL];
E 138

I 238

E 238
I 186
int
E 186
I 138
static char control_init_data[] = { 
	MATCHZANY,	OP_VARLEN,
	MATCHONE,	OP_NONZLEN,
	MATCHANY,	OP_VARLEN|OP_NONZLEN,
#ifdef MACVALUE
	MACVALUE,	OP_EXACT,
#endif /* MACVALUE */
	MATCHNCLASS,	OP_NONZLEN,
	MATCHCLASS,	OP_NONZLEN|OP_VARLEN|OP_CLASS,
D 139
	MATCHNMAP,	OP_NONZLEN,
	MATCHMAP,	OP_NONZLEN|OP_VARLEN|OP_CLASS
E 139
};

static int nrw;

void
E 138
D 26
rewrite(pvp)
E 26
I 26
D 184
rewrite(pvp, ruleset)
E 184
I 184
D 234
rewrite(pvp, ruleset, e)
E 234
I 234
rewrite(pvp, ruleset, reclevel, e)
E 234
E 184
E 26
	char **pvp;
I 26
	int ruleset;
I 234
	int reclevel;
E 234
I 184
	register ENVELOPE *e;
E 184
E 26
{
I 138
	nrw = 0;
	_rewrite(pvp, ruleset);
}

static void
_rewrite(pvp, ruleset)
	char **pvp;
	int ruleset;
{
E 138
	register char *ap;		/* address pointer */
	register char *rp;		/* rewrite pointer */
	register char **avp;		/* address vector pointer */
I 42
D 44
	char **avfp;			/* first word in current match */
E 44
E 42
	register char **rvp;		/* rewrite vector pointer */
D 42
	struct rewrite *rwr;
	struct match mlist[MAXMATCH];
E 42
I 42
D 67
	struct rewrite *rwr;		/* pointer to current rewrite rule */
E 67
I 67
	register struct match *mlp;	/* cur ptr into mlist */
	register struct rewrite *rwr;	/* pointer to current rewrite rule */
I 182
	int ruleno;			/* current rule number */
I 186
	int rstat = EX_OK;		/* return status */
I 225
	int loopcount;
E 225
E 186
E 182
I 104
	int subr;			/* subroutine number if >= 0 */
	bool dolookup;			/* do host aliasing */
E 104
E 67
D 138
	struct match mlist[MAXMATCH];	/* stores match on LHS */
E 138
D 67
	struct match *mlp;		/* cur ptr into mlist */
E 67
E 42
	char *npvp[MAXATOM+1];		/* temporary space for rebuild */
I 184
D 204
	extern char *macvalue();
E 204
E 184
I 138
	char tokbuf[MAXNAME+1];		/* for concatenated class tokens */
 	int nloops, nmatches = 0;	/* for looping rule checks */
	struct rewrite *prev_rwr;	/* pointer to previous rewrite rule */
	struct match mlist[MAXMATCH+1];	/* stores match on LHS */
	struct match *old_mlp;		/* to save our place */
	bool extend_match;	/* extend existing match during backup */
E 138
I 25
D 123
	extern bool sameword();
E 123
E 25

I 138
D 139
	/* test entry which should be nonzero */
	if (control_opts[MATCHMAP] == 0)
	{
		/* First time through, initialize table */
		int	c, i;

		for (i = 0; i < sizeof control_init_data; )
		{
			c = control_init_data[i++];
			control_opts[c] = control_init_data[i++];
		}
	}

E 139
E 138
D 20
# ifdef DEBUG
E 20
I 20
D 29
# ifdef DEBUGX
E 20
	if (Debug)
E 29
I 29
D 74
# ifdef DEBUG
D 33
	if (Debug > 10)
E 33
I 33
D 60
	if (Debug > 9)
E 60
I 60
D 68
	if (tTd(21, 9))
E 68
I 68
	if (tTd(21, 2))
E 74
I 74
D 81
	if (Mode == MD_TEST || tTd(21, 2))
E 81
I 81
D 245
	if (OpMode == MD_TEST || tTd(21, 2))
E 245
I 245
	if (OpMode == MD_TEST || tTd(21, 1))
E 245
E 81
E 74
E 68
E 60
E 33
E 29
	{
D 67
		printf("rewrite: original pvp:\n");
E 67
I 67
D 68
		printf("rewrite: ruleset %d, original pvp:\n", ruleset);
E 68
I 68
D 78
		printf("rewrite: ruleset %d, original pvp:", ruleset);
E 78
I 78
		printf("rewrite: ruleset %2d   input:", ruleset);
E 78
E 68
E 67
D 138
		printav(pvp);
E 138
I 138
		printcav(pvp);
E 138
	}
I 140
	if (ruleset < 0 || ruleset >= MAXRWSETS)
	{
D 166
		syserr("rewrite: illegal ruleset number %d", ruleset);
E 166
I 166
		syserr("554 rewrite: illegal ruleset number %d", ruleset);
E 166
D 186
		return;
E 186
I 186
		return EX_CONFIG;
E 186
	}
I 234
D 238
	if (reclevel++ > 50)
E 238
I 238
	if (reclevel++ > MAXRULERECURSION)
E 238
	{
		syserr("rewrite: infinite recursion, ruleset %d", ruleset);
		return EX_CONFIG;
	}
E 234
E 140
I 76
	if (pvp == NULL)
D 186
		return;
E 186
I 186
		return EX_USAGE;
E 186
E 76
D 20
# endif DEBUG
E 20
I 20
D 29
# endif DEBUGX
E 29
I 29
D 74
# endif DEBUG
E 74
E 29
E 20

I 138
	if (++nrw > 100)
	{
		char buf[MAXLINE];

		buf[0] = buf[MAXLINE-1] = 0;
		while (*pvp)
			(void) strncat(buf, *pvp++, sizeof buf);
		syserr("address causes rewrite loop: <%s>", buf);
		return;
	}

	/* Be sure to recognize first rule as new */
	prev_rwr = NULL;

E 138
	/*
D 138
	**  Run through the list of rewrite rules, applying
	**	any that match.
E 138
I 138
	**  Run through the list of rewrite rules, applying any that match.
E 138
	*/

I 182
	ruleno = 1;
I 225
	loopcount = 0;
E 225
E 182
D 26
	for (rwr = RewriteRules; rwr != NULL; )
E 26
I 26
	for (rwr = RewriteRules[ruleset]; rwr != NULL; )
E 26
	{
I 133
D 225
		int loopcount = 0;

E 225
E 133
D 20
# ifdef DEBUG
E 20
I 20
D 29
# ifdef DEBUGX
E 20
		if (Debug)
E 29
I 29
D 126
# ifdef DEBUG
E 126
D 60
		if (Debug > 10)
E 60
I 60
		if (tTd(21, 12))
E 60
E 29
E 18
E 10
E 9
		{
D 9
			if (q >= buflim)
E 9
I 9
D 18
			if (q >= buflim-1)
E 18
I 18
D 68
			printf("-----trying rule:\n");
E 68
I 68
			printf("-----trying rule:");
E 68
D 138
			printav(rwr->r_lhs);
E 138
I 138
			printcav(rwr->r_lhs);
E 138
		}
D 20
# endif DEBUG
E 20
I 20
D 29
# endif DEBUGX
E 29
I 29
D 126
# endif DEBUG
E 126
E 29
E 20

I 138
		/*
		**  Set up the match list.  This is done once for each
		**  rule.  If a rule is used repeatedly, the list need not
		**  be set up the next time.
		*/

		if (rwr != prev_rwr)
		{
			prev_rwr = rwr;
			for (rvp = rwr->r_lhs, mlp = mlist;
				 *rvp && (mlp < &mlist[MAXMATCH]); rvp++)
			{
				mlp->flags = ((unsigned char) **rvp >= MAX_CONTROL) ?
								0 : control_opts[**rvp] ;
				if (mlp->flags)
				{
					mlp->source = rvp;
					mlp++;
				}
			}
			if (*rvp)
			{
				syserr("Too many variables on LHS in ruleset %d", ruleset);
				return;
			}
			mlp->source = rvp;

			/* Make sure end marker is initialized */
			mlp->flags = 0;
		}

E 138
		/* try to match on this rule */
D 42
		clrmatch(mlist);
		for (rvp = rwr->r_lhs, avp = pvp; *avp != NULL; )
E 42
I 42
		mlp = mlist;
I 138

E 138
D 44
		for (rvp = rwr->r_lhs, avfp = avp = pvp; *avp != NULL; )
E 44
I 44
D 67
		for (rvp = rwr->r_lhs, avp = pvp; *avp != NULL; )
E 67
I 67
		rvp = rwr->r_lhs;
		avp = pvp;
I 138
		nloops = 0;
		extend_match = FALSE;

E 138
D 182
		while ((ap = *avp) != NULL || *rvp != NULL)
E 182
I 182
		if (++loopcount > 100)
E 182
E 67
E 44
E 42
		{
I 138
			if (nloops++ > 400)
			{
				syserr("Looping on ruleset %d, rule %d",
					ruleset, rwr-RewriteRules[ruleset]);
				mlp = mlist - 1; /* force rule failure */
				break;
			}
E 138
I 133
D 182
			if (++loopcount > 100)
E 182
I 182
			syserr("554 Infinite loop in ruleset %d, rule %d",
				ruleset, ruleno);
			if (tTd(21, 1))
E 182
			{
D 166
				syserr("Infinite loop in ruleset %d", ruleset);
E 166
I 166
D 182
				syserr("554 Infinite loop in ruleset %d", ruleset);
E 182
E 166
I 140
				printf("workspace: ");
				printav(pvp);
E 140
D 182
				break;
E 182
			}
I 182
			break;
		}

		while ((ap = *avp) != NULL || *rvp != NULL)
		{
E 182
E 133
D 67
			ap = *avp;
E 67
			rp = *rvp;
I 138

E 138
D 67

E 67
I 67
D 126
# ifdef DEBUG
E 126
			if (tTd(21, 35))
			{
D 68
				printf("ap=\"");
E 68
I 68
D 133
				printf("ap=");
E 133
I 133
D 155
				printf("operator=");
E 155
I 155
D 180
				printf("rp=");
E 180
I 180
				printf("ADVANCE rp=");
E 180
E 155
E 133
E 68
D 154
				xputs(ap);
D 68
				printf("\", rp=\"");
E 68
I 68
D 133
				printf(", rp=");
E 133
I 133
				printf(", token=");
E 154
E 133
E 68
				xputs(rp);
I 154
D 155
				printf(", token=");
E 155
I 155
				printf(", ap=");
E 155
				xputs(ap);
E 154
D 68
				printf("\"\n");
E 68
I 68
				printf("\n");
E 68
			}
D 126
# endif DEBUG
E 126
E 67
D 138
			if (rp == NULL)
E 138
I 138

			if (extend_match)
				extend_match = FALSE;
			else
E 138
E 18
E 9
			{
I 138
				mlp->first = avp;
				mlp->last = mlp->flags == 0 || (mlp->flags & OP_NONZLEN) ?
							avp + 1 : avp;
			}

			if (rp == NULL)
E 138
D 18
				usrerr("Address too long");
				return (NULL);
E 18
I 18
				/* end-of-pattern before end-of-address */
D 67
				goto fail;
E 67
I 67
				goto backup;
E 67
E 18
D 138
			}
I 67
D 162
			if (ap == NULL && *rp != MATCHZANY)
E 162
I 162
D 167
			if (ap == NULL && (*rp & 0377) != MATCHZANY)
E 167
I 167
			if (ap == NULL && (*rp & 0377) != MATCHZANY &&
D 181
			    (*rp & 0377) != CANONHOST)
E 181
I 181
			    (*rp & 0377) != MATCHZERO)
E 181
E 167
E 162
E 138
I 138

			/* Premature end of address */
			if (ap == NULL && avp != mlp->last)
				goto backup;

			/*
			**  Simplest case - exact token comparison between
			**  pattern and address.  Such a match is not saved
			**  in mlp.
			*/

			if (rvp < mlp->source)
E 138
			{
D 138
D 180
				/* end-of-input */
				break;
E 180
I 180
				/* end-of-input with patterns left */
				goto backup;
E 180
E 138
I 138
				if (ap == NULL || strcasecmp(ap, rp))
					goto backup;
				rvp++;
				avp++;
				continue;
E 138
			}
E 67
I 9
D 18
			if (space)
				*q++ = SPACESUB;
E 9
			*q++ = c;
E 18
I 18

D 138
D 162
			switch (*rp)
E 162
I 162
			switch (*rp & 0377)
E 162
E 138
I 138
#ifdef MACVALUE
			/*
			**  This is special case handled.  The match is exact,
			**  but might span zero or more address tokens.  The
			**  result is saved in mlp.
			*/

			if (*rp == MACVALUE)
E 138
			{
I 25
D 138
D 260
				register STAB *s;
E 260
I 179
				char buf[MAXLINE];
E 179
E 138
I 138
				int len;
				rp = macvalue(rp[1], CurEnv);
E 138
D 91
				register int class;
E 91

E 25
D 44
			  case MATCHONE:
				/* match exactly one token */
D 42
				setmatch(mlist, rp[1], avp, avp);
E 42
I 42
				mlp->first = mlp->last = avp++;
				mlp++;
				avfp = avp;
E 42
				break;

			  case MATCHANY:
				/* match any number of tokens */
D 28
				setmatch(mlist, rp[1], NULL, avp);
E 28
I 28
D 42
				setmatch(mlist, rp[1], (char **) NULL, avp);
E 42
I 42
				mlp->first = avfp;
				mlp->last = avp++;
				mlp++;
E 42
E 28
				break;

E 44
I 25
D 138
			  case MATCHCLASS:
D 84
				/* match any token in a class */
E 84
I 84
D 180
			  case MATCHNCLASS:
				/* match any token in (not in) a class */
E 180
I 180
				/* match any phrase in a class */
				mlp->pattern = rvp;
E 180
E 84
D 91
				class = rp[1];
				if (!isalpha(class))
D 67
					goto fail;
E 67
I 67
					goto backup;
E 67
				if (isupper(class))
					class -= 'A';
				else
					class -= 'a';
E 91
D 29
				s = stab(ap, ST_FIND);
E 29
I 29
D 179
				s = stab(ap, ST_CLASS, ST_FIND);
E 179
I 179
				mlp->first = avp;
	extendclass:
D 180
				if (*avp == NULL)
E 180
I 180
				ap = *avp;
				if (ap == NULL)
E 180
					goto backup;
				mlp->last = avp++;
				cataddr(mlp->first, mlp->last, buf, sizeof buf, '\0');
D 260
				s = stab(buf, ST_CLASS, ST_FIND);
E 179
E 29
D 55
				if (s == NULL || (s->s_class & (1 << class)) == 0)
E 55
I 55
D 91
				if (s == NULL || (s->s_class & (1L << class)) == 0)
E 91
I 91
				if (s == NULL || !bitnset(rp[1], s->s_class))
E 260
I 260
				if (!wordinclass(buf, rp[1]))
E 260
E 138
I 138
				if (rp)
					while (*rp)
					{
						if (*avp == NULL || strncasecmp(rp,*avp,len = strlen(*avp)))
							goto backup;
						rp += len;
						avp++;
					}
				mlp->last = avp;
				rvp++;
				mlp++;
				continue;
			}
#endif /* MACVALUE */

			/*
			**  All other matches are saved in mlp.  Initially
			**  assume they match at the shortest possible length
			**  for this pattern.  Variable patterns will be
			**  extended later as needed.
			*/

			/* Fixed length first */
			if (!(mlp->flags & OP_VARLEN))
			{
				switch (*rp)
E 138
E 91
I 84
				{
D 138
D 162
					if (*rp == MATCHCLASS)
E 162
I 162
D 180
					if ((*rp & 0377) == MATCHCLASS)
E 162
E 138
I 138
					register STAB *s;

				    case MATCHNCLASS:
					/* match any single token not in a class */
					s = stab(ap, ST_CLASS, ST_FIND);
					if (s != NULL && bitnset(rp[1], s->s_class))
E 138
D 179
						goto backup;
E 179
I 179
						goto extendclass;
E 179
D 138
				}
D 162
				else if (*rp == MATCHNCLASS)
E 162
I 162
				else if ((*rp & 0377) == MATCHNCLASS)
E 180
I 180
					if (tTd(21, 36))
					{
						printf("EXTEND  rp=");
						xputs(rp);
						printf(", ap=");
						xputs(ap);
						printf("\n");
					}
E 180
E 162
E 84
E 55
D 67
					goto fail;
E 67
I 67
D 179
					goto backup;
E 179
I 179
					goto extendclass;
I 180
				}
				if (tTd(21, 36))
					printf("CLMATCH\n");
E 180
				mlp++;
				break;
E 179
E 138
I 138
					break;
E 138
E 67
I 42
D 139

I 180
			  case MATCHNCLASS:
				/* match any token not in a class */
D 260
				s = stab(ap, ST_CLASS, ST_FIND);
				if (s != NULL && bitnset(rp[1], s->s_class))
E 260
I 260
				if (wordinclass(ap, rp[1]))
E 260
					goto backup;

				/* fall through */

E 180
D 44
				/* mark match */
E 44
I 44
D 138
D 179
				/* explicit fall-through */
E 138
I 138
				    case MATCHNMAP:
					/* match any token not in a DBM map */
					if ((rp = mapkey(rp[1], ap, 0, NULL)) != NULL)
					{
						free(rp);
						goto backup;
					}
					break;
E 138

E 179
E 139
D 138
			  case MATCHONE:
			  case MATCHANY:
				/* match exactly one token */
I 180
				mlp->pattern = rvp;
E 180
E 44
D 67
				mlp->first = mlp->last = avp++;
E 67
I 67
				mlp->first = avp;
				mlp->last = avp++;
E 67
				mlp++;
D 44
				avfp = avp;
E 44
E 42
				break;
E 138
I 138
				}
E 138

I 67
D 138
			  case MATCHZANY:
				/* match zero or more tokens */
I 180
				mlp->pattern = rvp;
E 180
				mlp->first = avp;
				mlp->last = avp - 1;
E 138
I 138
				avp = mlp->last;
				rvp++;
E 138
				mlp++;
I 167
				break;

D 181
			  case CANONHOST:
E 181
I 181
			  case MATCHZERO:
E 181
				/* match zero tokens */
E 167
D 138
				break;
E 138
I 138
				continue;
			}
E 138

I 184
			  case MACRODEXPAND:
				/*
				**  Match against run-time macro.
				**  This algorithm is broken for the
				**  general case (no recursive macros,
				**  improper tokenization) but should
				**  work for the usual cases.
				*/

				ap = macvalue(rp[1], e);
				mlp->first = avp;
				if (tTd(21, 2))
					printf("rewrite: LHS $&%c => \"%s\"\n",
						rp[1],
						ap == NULL ? "(NULL)" : ap);

				if (ap == NULL)
					break;
D 205
				while (*ap != NULL)
E 205
I 205
				while (*ap != '\0')
E 205
				{
					if (*avp == NULL ||
					    strncasecmp(ap, *avp, strlen(*avp)) != 0)
					{
						/* no match */
						avp = mlp->first;
						goto backup;
					}
					ap += strlen(*avp++);
				}

				/* match */
				break;

E 184
E 67
E 25
D 138
			  default:
				/* must have exact match */
D 25
				/* can scribble rp & ap here safely */
D 19
				while (*rp != '\0' && *ap != '\0')
E 19
I 19
				while (*rp != '\0' || *ap != '\0')
E 19
				{
					if (*rp++ != lower(*ap++))
						goto fail;
				}
E 25
I 25
D 123
				if (!sameword(rp, ap))
E 123
I 123
				if (strcasecmp(rp, ap))
E 138
I 138
			/*
			**  We now have a variable length item.  It could
			**  be $+ or $* in which case no special checking
			**  is needed.  But a class match such as $=x must
			**  be verified.
			**
			**  As a speedup, if a variable length item is
			**  followed by a plain character token, we initially
			**  extend the match to the first such token we find.
			**  If the required character token cannot be found,
			**  we fail the match at this point.
			*/

			avp = mlp->last;

			/* If next token is char token */
			if (&rvp[1] < mlp[1].source)
			{
				while (*avp && strcasecmp(*avp, rvp[1]))
					avp++;

				/*
				**  If we can't find the proper ending token,
				**  leave avp point to NULL.  This indicates
				**  we have run out of address tokens.  It is
				**  pointless to advance the beginning of this
				**  match and retry.
				*/

				if (*avp == NULL)
E 138
E 123
D 67
					goto fail;
E 67
I 67
					goto backup;
I 138
				mlp->last = avp;
			}
			else if (rvp[1] == NULL)
			/* next token is end of address */
			{
				while (*avp)
					avp++;
				mlp->last = avp;
			}

			if (mlp->flags & OP_CLASS)
			{
				register char *cp = tokbuf;

				avp = mlp->first;
				strcpy(cp, *avp);
E 138
E 67
I 42
				avp++;
D 44
				avfp = avp;
E 44
E 42
E 25
D 138
				break;
E 138
I 138
				for (;;)
				{
					while (avp < mlp->last)
					{
						while (*cp)
							cp++;
						strcpy(cp, *avp);
						avp++;
					}
					switch (*rp)
					{
						register STAB *s;

					    case MATCHCLASS:
						s = stab(tokbuf, ST_CLASS, ST_FIND);
						if (s != NULL && bitnset(rp[1], s->s_class))
							goto have_match;
						break;
D 139

					    case MATCHMAP:
						if (mapkey(rp[1], tokbuf, sizeof(tokbuf)-1, NULL))
							goto have_match;
						break;
E 139
					}

					/*
					**  Class match initially failed.
					**  Extend the tentative match.
					**  Again, if followed by a character
					**  token, extend all the way to that
					**  token before checking.
					*/

					if (*avp)
					{
						(mlp->last)++;
						if (&rvp[1] < mlp[1].source)
						{
							while (*(mlp->last) && strcasecmp(*(mlp->last), rvp[1]))
								(mlp->last)++;
							if (*(mlp->last) == NULL)
								avp = mlp->last;
						}
					}
					if (*avp == NULL)
					{
						/*
						**  We could not find the
						**  ending token.  But we had
						**  found ending tokens before.
						**  A match is still plausible
						**  if the start of the
						**  tentative match is advanced.
						**  Hence we must not leave avp
						**  pointing to NULL.
						*/
						avp = mlp->first;
						goto backup;
					}
				}
E 138
			}

D 138
			/* successful match on this token */
E 138
I 138
 have_match:
E 138
D 42
			avp++;
E 42
			rvp++;
I 138
			mlp++;
E 138
			continue;

D 67
		  fail:
E 67
I 67
D 138
D 180
		  backup:
E 180
I 180
	  backup:
E 180
E 67
			/* match failed -- back up */
D 180
			while (--rvp >= rwr->r_lhs)
E 180
I 180
			while (--mlp >= mlist)
E 180
E 138
I 138
backup:
			/* We failed to match.  mlp marks point of failure */

			/*
			**  There is a special case when we have exhausted
			**  the address, but have not exhausted the pattern.
			**  Under normal circumstances we could consider the
			**  failure permanent, since extending the number of
			**  address tokens matched by a '$+' or a '$*' will
			**  only worsen the situation.
			**
			**  There is an exception, however.  It is possible
			**  that we have matched a class token, say '$=x',
			**  with three or more tokens.  Extending a '$+' say,
			**  which precedes the '$=x' will move the beginning
			**  of the '$=x' match to the right, but it might match
			**  a smaller number of tokens then, possibly
			**  correcting the mismatch.
			**
			**  Thus in this case we initially back up to the
			**  $=x which matches three or more tokens.
			*/

			if (*avp == NULL)
E 138
			{
I 180
				rvp = mlp->pattern;
E 180
D 138
				rp = *rvp;
I 180
				avp = mlp->last + 1;
				ap = *avp;

				if (tTd(21, 36))
				{
					printf("BACKUP  rp=");
					xputs(rp);
					printf(", ap=");
					xputs(ap);
					printf("\n");
				}

				if (ap == NULL)
				{
					/* run off the end -- back up again */
					continue;
				}
E 180
D 67
				if (*rp == MATCHANY)
E 67
I 67
D 162
				if (*rp == MATCHANY || *rp == MATCHZANY)
E 162
I 162
				if ((*rp & 0377) == MATCHANY ||
				    (*rp & 0377) == MATCHZANY)
E 162
E 138
I 138
				while (--mlp > mlist)
E 138
E 67
I 42
				{
D 44
					avfp = mlp->first;
E 44
I 44
D 138
					/* extend binding and continue */
D 67
					mlp[-1].last = avp++;
E 67
I 67
D 180
					avp = ++mlp[-1].last;
					avp++;
E 180
I 180
					mlp->last = avp++;
E 180
E 67
					rvp++;
I 180
					mlp++;
E 180
E 44
E 42
					break;
E 138
I 138
					if ((mlp->flags & OP_CLASS) &&
					    mlp->last > 2 + mlp->first)
						break;
E 138
D 42

				/* can't extend match: back up everything */
				avp--;

				if (*rp == MATCHONE)
E 42
I 42
				}
D 44
				else if (*rp == MATCHONE || *rp == MATCHCLASS)
E 44
I 44
D 138
D 179
				avp--;
D 84
				if (*rp == MATCHONE || *rp == MATCHCLASS)
E 84
I 84
D 162
				if (*rp == MATCHONE || *rp == MATCHCLASS ||
				    *rp == MATCHNCLASS)
E 162
I 162
				if ((*rp & 0377) == MATCHONE ||
				    (*rp & 0377) == MATCHCLASS ||
E 179
I 179
D 180
				if ((*rp & 0377) == MATCHCLASS ||
E 179
				    (*rp & 0377) == MATCHNCLASS)
E 180
I 180
				if ((*rp & 0377) == MATCHCLASS)
E 180
E 162
E 84
E 44
E 42
				{
I 179
					/* extend binding and try again */
D 180
					mlp--;
					avp = ++mlp->last;
E 180
I 180
D 209
					mlp->last = avp++;
E 209
I 209
					mlp->last = avp;
E 209
E 180
					goto extendclass;
				}
D 180
				avp--;
				if ((*rp & 0377) == MATCHONE)
				{
E 179
D 42
					/* undo binding */
D 28
					setmatch(mlist, rp[1], NULL, NULL);
E 28
I 28
					setmatch(mlist, rp[1], (char **) NULL, (char **) NULL);
E 42
I 42
					/* back out binding */
D 44
					avp--;
					avfp = avp;
E 44
					mlp--;
E 42
E 28
				}
E 180
E 138
			}

D 138
D 180
			if (rvp < rwr->r_lhs)
E 180
I 180
			if (mlp < mlist)
E 180
			{
				/* total failure to match */
E 138
I 138
			/*
			**  Now backup till we find a match with a pattern
			**  whose length is extendable, and extend that.
			*/

			mlp--;
			while (mlp >= mlist && !(mlp->flags & OP_VARLEN))
				mlp--;

			/* Total failure to match */
			if (mlp < mlist)
E 138
				break;
I 138

			avp = ++(mlp->last);
			rvp = mlp->source;

			/*
			**  We have found a backup point.  Normally we would
			**  increase the matched amount by one token, and
			**  continue from the next item in the pattern.  But
			**  there are two special cases.  If this is a
			**  class-type match (OP_CLASS), we must test the
			**  validity of the extended match.  If this pattern
			**  item is directly followed by a character token, it
			**  is worth going back and locating the next such
			**  character token before we continue on.
			*/
			if ((mlp->flags & OP_CLASS) || (&rvp[1] < mlp[1].source))
			{
				avp = mlp->first;
				extend_match = TRUE;
E 138
			}
I 138
			else
			{
				mlp++;
				rvp++;
			}
E 138
E 18
		}
D 11
		space = isspace(c);
E 11
I 11
D 18
		space = isascii(c) && isspace(c);
E 18
I 18

		/*
D 138
		**  See if we successfully matched
E 138
I 138
		**  See if we successfully matched.
E 138
		*/

D 83
		if (rvp >= rwr->r_lhs && *rvp == NULL)
E 83
I 83
D 138
D 181
		if (rvp < rwr->r_lhs || *rvp != NULL)
E 181
I 181
		if (mlp < mlist || *rvp != NULL)
E 181
E 138
I 138
		if (mlp < mlist)
E 138
E 83
		{
I 67
D 83
			rvp = rwr->r_rhs;
E 83
E 67
D 20
# ifdef DEBUG
E 20
I 20
D 29
# ifdef DEBUGX
E 20
			if (Debug)
E 29
I 29
D 126
# ifdef DEBUG
E 126
D 60
			if (Debug > 10)
E 60
I 60
D 83
			if (tTd(21, 12))
E 60
E 29
			{
D 68
				printf("-----rule matches:\n");
E 68
I 68
				printf("-----rule matches:");
E 68
D 67
				printav(rwr->r_rhs);
E 67
I 67
				printav(rvp);
E 67
			}
E 83
I 83
			if (tTd(21, 10))
				printf("----- rule fails\n");
E 83
D 20
# endif DEBUG
E 20
I 20
D 29
# endif DEBUGX
E 29
I 29
D 126
# endif DEBUG
E 126
I 83
			rwr = rwr->r_next;
I 182
			ruleno++;
I 225
			loopcount = 0;
E 225
E 182
I 138
			nmatches = 0;
E 138
			continue;
		}
E 83
E 29
E 20

I 138
		if (nmatches++ > 200)
		{
			syserr("Loop in ruleset %d, rule %d (too many matches)",
				ruleset, rwr - RewriteRules[ruleset]);
			rwr = rwr->r_next;
			nmatches = 0;
			continue;
		}

E 138
I 83
		rvp = rwr->r_rhs;
D 126
# ifdef DEBUG
E 126
		if (tTd(21, 12))
		{
			printf("-----rule matches:");
D 138
			printav(rvp);
E 138
I 138
			printcav(rvp);
E 138
		}
D 126
# endif DEBUG
E 126

		rp = *rvp;
D 162
		if (*rp == CANONUSER)
E 162
I 162
		if ((*rp & 0377) == CANONUSER)
E 162
		{
			rvp++;
			rwr = rwr->r_next;
I 182
			ruleno++;
I 225
			loopcount = 0;
E 225
E 182
I 138
			nmatches = 0;
E 138
		}
D 162
		else if (*rp == CANONHOST)
E 162
I 162
		else if ((*rp & 0377) == CANONHOST)
E 162
		{
			rvp++;
			rwr = NULL;
		}
D 162
		else if (*rp == CANONNET)
E 162
I 162
		else if ((*rp & 0377) == CANONNET)
E 162
			rwr = NULL;

		/* substitute */
I 104
		dolookup = FALSE;
E 104
		for (avp = npvp; *rvp != NULL; rvp++)
		{
			register struct match *m;
			register char **pp;

E 83
I 67
D 73
			/* see if this is a "subroutine" call */
E 73
			rp = *rvp;
I 104

			/* check to see if we should do a lookup */
			if (*rp == MATCHLOOKUP)
				dolookup = TRUE;

			/* see if there is substitution here */
E 104
D 73
			if (*rp == CALLSUBR)
E 73
I 73
D 83
			if (*rp == CANONUSER)
E 83
I 83
D 107
			if (*rp != MATCHREPL)
E 107
I 107
D 138
D 162
			if (*rp == MATCHREPL)
E 162
I 162
			if ((*rp & 0377) == MATCHREPL)
E 162
E 138
I 138
			if (*rp == MATCHREPL && rp[1] >= '1' && rp[1] <= '9')
E 138
E 107
E 83
E 73
			{
D 73
				rp = *++rvp;
# ifdef DEBUG
D 68
				if (tTd(21, 2))
E 68
I 68
				if (tTd(21, 3))
E 68
					printf("-----callsubr %s\n", rp);
# endif DEBUG
				rewrite(pvp, atoi(rp));
				rwr = rwr->r_next;
				continue;
			}
I 68
			else if (*rp == CANONUSER)
			{
E 73
D 83
				rvp++;
				rwr = rwr->r_next;
E 83
I 83
D 107
				if (avp >= &npvp[MAXATOM])
E 107
I 107
				/* substitute from LHS */
				m = &mlist[rp[1] - '1'];
D 140
				if (m >= mlp)
E 140
I 140
				if (m < mlist || m >= mlp)
E 140
E 107
				{
I 104
				  toolong:
E 104
D 107
					syserr("rewrite: expansion too long");
E 107
I 107
D 138
D 140
					syserr("rewrite: ruleset %d: replacement out of bounds", ruleset);
E 140
I 140
D 166
					syserr("rewrite: ruleset %d: replacement $%c out of bounds",
E 166
I 166
					syserr("554 rewrite: ruleset %d: replacement $%c out of bounds",
E 166
						ruleset, rp[1]);
E 140
E 138
I 138
					syserr("rewrite: ruleset %d: replacement #%c out of bounds",
						ruleset, rp[1]);
E 138
E 107
D 186
					return;
E 186
I 186
					return EX_CONFIG;
E 186
				}
D 107
				*avp++ = rp;
				continue;
E 83
			}
D 83
			else if (*rp == CANONHOST)
			{
				rvp++;
				rwr = NULL;
			}
			else if (*rp == CANONNET)
				rwr = NULL;
E 83
E 68

E 67
D 83
			/* substitute */
D 68
			for (rvp = rwr->r_rhs, avp = npvp; *rvp != NULL; rvp++)
E 68
I 68
			for (avp = npvp; *rvp != NULL; rvp++)
E 83
I 83
			/* substitute from LHS */
			m = &mlist[rp[1] - '1'];
I 105
			if (m >= mlp)
			{
				syserr("rewrite: ruleset %d: replacement out of bounds", ruleset);
				return;
			}
E 107
E 105
D 126
# ifdef DEBUG
E 126
D 107
			if (tTd(21, 15))
E 83
E 68
			{
D 83
				rp = *rvp;
D 42
				if (*rp == MATCHANY)
E 42
I 42
				if (*rp == MATCHREPL)
E 83
I 83
				printf("$%c:", rp[1]);
E 107
I 107
				if (tTd(21, 15))
				{
					printf("$%c:", rp[1]);
					pp = m->first;
D 138
					while (pp <= m->last)
E 138
I 138
					while (pp < m->last)
E 138
					{
						printf(" %x=\"", *pp);
						(void) fflush(stdout);
						printf("%s\"", *pp++);
					}
					printf("\n");
				}
D 126
# endif DEBUG
E 126
E 107
				pp = m->first;
D 138
				while (pp <= m->last)
E 138
I 138
				while (pp < m->last)
E 138
E 83
E 42
				{
D 83
					register struct match *m;
					register char **pp;
D 42
					extern struct match *findmatch();
E 42

D 42
					m = findmatch(mlist, rp[1]);
					if (m != NULL)
E 42
I 42
					m = &mlist[rp[1] - '1'];
I 44
# ifdef DEBUG
D 60
					if (Debug > 13)
E 60
I 60
					if (tTd(21, 15))
E 60
					{
						printf("$%c:", rp[1]);
						pp = m->first;
D 67
						do
E 67
I 67
						while (pp <= m->last)
E 67
						{
							printf(" %x=\"", *pp);
D 46
							fflush(stdout);
E 46
I 46
							(void) fflush(stdout);
E 46
D 67
							printf("%s\"", *pp);
						} while (pp++ != m->last);
E 67
I 67
							printf("%s\"", *pp++);
						}
E 67
						printf("\n");
					}
# endif DEBUG
E 44
					pp = m->first;
D 67
					do
E 67
I 67
					while (pp <= m->last)
E 67
E 42
					{
D 42
						pp = m->firsttok;
						do
E 42
I 42
						if (avp >= &npvp[MAXATOM])
E 42
						{
I 38
D 42
							if (avp >= &npvp[MAXATOM])
							{
								syserr("rewrite: expansion too long");
								return;
							}
E 38
							*avp++ = *pp;
						} while (pp++ != m->lasttok);
					}
E 42
I 42
							syserr("rewrite: expansion too long");
							return;
						}
D 67
						*avp++ = *pp;
					} while (pp++ != m->last);
E 67
I 67
						*avp++ = *pp++;
					}
E 83
I 83
D 107
					printf(" %x=\"", *pp);
					(void) fflush(stdout);
					printf("%s\"", *pp++);
E 107
I 107
					if (avp >= &npvp[MAXATOM])
D 138
					{
D 166
						syserr("rewrite: expansion too long");
E 166
I 166
						syserr("554 rewrite: expansion too long");
E 166
D 186
						return;
E 186
I 186
						return EX_DATAERR;
E 186
					}
E 138
I 138
						goto toolong;
E 138
					*avp++ = *pp++;
E 107
E 83
E 67
E 42
				}
D 83
				else
I 38
				{
					if (avp >= &npvp[MAXATOM])
					{
						syserr("rewrite: expansion too long");
						return;
					}
E 38
					*avp++ = rp;
I 38
				}
E 83
I 83
D 107
				printf("\n");
E 107
E 83
E 38
			}
D 83
			*avp++ = NULL;
D 28
			bmove(npvp, pvp, (avp - npvp) * sizeof *avp);
E 28
I 28
D 73
			bmove((char *) npvp, (char *) pvp, (avp - npvp) * sizeof *avp);
E 73
I 73
			if (**npvp == CALLSUBR)
			{
				bmove((char *) &npvp[2], (char *) pvp,
					(avp - npvp - 2) * sizeof *avp);
# ifdef DEBUG
				if (tTd(21, 3))
					printf("-----callsubr %s\n", npvp[1]);
E 83
D 107
# endif DEBUG
D 83
				rewrite(pvp, atoi(npvp[1]));
			}
			else
E 83
I 83
			pp = m->first;
			while (pp <= m->last)
E 107
I 107
			else
E 107
E 83
			{
I 107
				/* vanilla replacement */
E 107
D 83
				bmove((char *) npvp, (char *) pvp,
					(avp - npvp) * sizeof *avp);
E 83
I 83
				if (avp >= &npvp[MAXATOM])
D 104
				{
I 107
D 138
	toolong:
E 138
I 138
toolong:
E 138
E 107
D 166
					syserr("rewrite: expansion too long");
E 166
I 166
					syserr("554 rewrite: expansion too long");
E 166
D 186
					return;
E 186
I 186
					return EX_DATAERR;
E 186
				}
E 104
I 104
					goto toolong;
E 104
D 107
				*avp++ = *pp++;
E 107
I 107
D 138
D 184
				*avp++ = rp;
E 184
I 184
				if ((*rp & 0377) != MACRODEXPAND)
					*avp++ = rp;
				else
				{
					*avp = macvalue(rp[1], e);
					if (tTd(21, 2))
						printf("rewrite: RHS $&%c => \"%s\"\n",
							rp[1],
							*avp == NULL ? "(NULL)" : *avp);
					if (*avp != NULL)
						avp++;
				}
E 184
E 138
I 138
#ifdef MACVALUE
				if (*rp == MACVALUE)
				{
					char *p = macvalue(rp[1], CurEnv);

					if (tTd(21, 2))
						printf("expanding runtime macro '%c' to \"%s\"\n",
						    rp[1], p ? p : "(null)");
					if (p)
						*avp++ = p;
				}
				else
#endif /* MACVALUE */
					*avp++ = rp;
E 138
E 107
E 83
			}
I 83
		}
		*avp++ = NULL;
I 107

		/*
D 134
		**  Check for any hostname lookups.
E 134
I 134
		**  Check for any hostname/keyword lookups.
E 134
		*/

		for (rvp = npvp; *rvp != NULL; rvp++)
		{
D 138
			char **hbrvp;
E 138
I 138
			char **hbrvp, **ubrvp;
E 138
			char **xpvp;
			int trsize;
D 114
			int i;
E 114
I 112
D 207
			char *olddelimchar;
E 207
I 134
			char *replac;
			int endtoken;
			STAB *map;
			char *mapname;
			char **key_rvp;
			char **arg_rvp;
			char **default_rvp;
E 134
E 112
D 108
			char buf[MAXATOM + 1];
E 108
I 108
D 138
			char buf[MAXNAME + 1];
E 138
I 138
			char hbuf[MAXNAME + 1], ubuf[MAXNAME + 1];
E 138
E 108
			char *pvpb1[MAXATOM + 1];
I 144
			char *argvect[10];
E 144
D 109
			static char pvpbuf[PSBUFSIZE];
E 109
I 109
			char pvpbuf[PSBUFSIZE];
I 222
			char *nullpvp[1];
E 222
I 112
D 138
D 168
			extern char *DelimChar;
E 168
E 138
I 138
			bool match, defaultpart;
			char begintype;
			char db = '\0';
E 138
E 112
E 109

D 134
D 138
			if (**rvp != HOSTBEGIN)
E 138
I 138
D 139
			if (**rvp != HOSTBEGIN && **rvp != KEYBEGIN)
E 139
I 139
			if (**rvp != HOSTBEGIN)
E 139
E 138
E 134
I 134
D 162
			if (**rvp != HOSTBEGIN && **rvp != LOOKUPBEGIN)
E 162
I 162
			if ((**rvp & 0377) != HOSTBEGIN &&
			    (**rvp & 0377) != LOOKUPBEGIN)
E 162
E 134
				continue;

			/*
D 134
D 138
			**  Got a hostname lookup.
E 138
I 138
			**  Got a hostname or database lookup.
E 138
E 134
I 134
			**  Got a hostname/keyword lookup.
E 134
			**
			**	This could be optimized fairly easily.
			*/

I 138
			begintype = **rvp;
E 138
			hbrvp = rvp;
I 138
			ubrvp = NULL;
E 138
I 134
D 144
			arg_rvp = default_rvp = NULL;
E 144
D 162
			if (**rvp == HOSTBEGIN)
E 162
I 162
			if ((**rvp & 0377) == HOSTBEGIN)
E 162
			{
				endtoken = HOSTEND;
				mapname = "host";
			}
			else
			{
				endtoken = LOOKUPEND;
				mapname = *++rvp;
			}
			map = stab(mapname, ST_MAP, ST_FIND);
			if (map == NULL)
D 166
				syserr("rewrite: map %s not found", mapname);
E 166
I 166
				syserr("554 rewrite: map %s not found", mapname);
E 166
E 134

I 138
D 139
			/* read database name if that's what we're up for */
			if (begintype == KEYBEGIN)
			{
				if (*++rvp != NULL)
					db = **rvp;
			}

E 139
E 138
			/* extract the match part */
D 134
D 138
			while (*++rvp != NULL && **rvp != HOSTEND)
E 138
I 138
			if (begintype == HOSTBEGIN)
I 139
			{
E 139
				while (*++rvp != NULL && **rvp != HOSTEND &&
D 139
				   **rvp != CANONUSER)
E 138
				continue;
E 139
I 139
				    **rvp != CANONUSER)
					continue;
			}
E 139
I 138
			else
D 139
				while (*++rvp != NULL && **rvp != KEYEND &&
				   **rvp != CANONHOST && **rvp != CANONUSER)
E 139
I 139
			{
				while (*++rvp != NULL && **rvp != CANONHOST &&
				    **rvp != CANONUSER)
E 139
					continue;
I 139
			}
E 139
			/* got a sprintf argument? */
			if (**rvp == CANONHOST)
			{
				*rvp = NULL;
				ubrvp = rvp+1;
D 139
				while (*++rvp != NULL && **rvp != KEYEND &&
				    **rvp != CANONUSER)
E 139
I 139
				while (*++rvp != NULL && **rvp != CANONUSER)
E 139
					continue;
			}
			defaultpart = **rvp == CANONUSER;
E 138
E 134
I 134
			key_rvp = ++rvp;
I 144
			default_rvp = NULL;
			arg_rvp = argvect;
			xpvp = NULL;
			replac = pvpbuf;
E 144
D 162
			while (*rvp != NULL && **rvp != endtoken)
E 162
I 162
			while (*rvp != NULL && (**rvp & 0377) != endtoken)
E 162
			{
D 144
				switch (**rvp)
E 144
I 144
D 162
				int nodetype = **rvp;
E 162
I 162
				int nodetype = **rvp & 0377;
E 162

				if (nodetype != CANONHOST && nodetype != CANONUSER)
E 144
				{
I 144
					rvp++;
					continue;
				}

				*rvp++ = NULL;

				if (xpvp != NULL)
				{
D 179
					cataddr(xpvp, replac,
E 179
I 179
					cataddr(xpvp, NULL, replac,
E 179
D 164
						&pvpbuf[sizeof pvpbuf] - replac);
E 164
I 164
						&pvpbuf[sizeof pvpbuf] - replac,
						'\0');
E 164
					*++arg_rvp = replac;
					replac += strlen(replac) + 1;
					xpvp = NULL;
				}
				switch (nodetype)
				{
E 144
				  case CANONHOST:
D 144
					*rvp++ = NULL;
					arg_rvp = rvp;
E 144
I 144
					xpvp = rvp;
E 144
					break;

				  case CANONUSER:
D 144
					*rvp++ = NULL;
E 144
					default_rvp = rvp;
					break;
D 144

				  default:
					rvp++;
					break;
E 144
				}
			}
E 134
			if (*rvp != NULL)
				*rvp++ = NULL;
I 144
			if (xpvp != NULL)
			{
D 179
				cataddr(xpvp, replac,
E 179
I 179
				cataddr(xpvp, NULL, replac,
E 179
D 164
					&pvpbuf[sizeof pvpbuf] - replac);
E 164
I 164
					&pvpbuf[sizeof pvpbuf] - replac, 
					'\0');
E 164
				*++arg_rvp = replac;
			}
			*++arg_rvp = NULL;
E 144

			/* save the remainder of the input string */
			trsize = (int) (avp - rvp + 1) * sizeof *rvp;
			bcopy((char *) rvp, (char *) pvpb1, trsize);

D 138
			/* look it up */
D 134
			cataddr(++hbrvp, buf, sizeof buf);
D 130
			maphostname(buf, sizeof buf);
E 130
I 130
			if (maphostname(buf, sizeof buf - 1) && ConfigLevel >= 2)
			{
				register int i;
E 134
I 134
D 164
			cataddr(key_rvp, buf, sizeof buf);
E 164
I 164
D 179
			cataddr(key_rvp, buf, sizeof buf, '\0');
E 179
I 179
			cataddr(key_rvp, NULL, buf, sizeof buf, '\0');
E 179
E 164
I 144
			argvect[0] = buf;
E 144
D 201
			if (map != NULL && bitset(MF_VALID, map->s_map.map_flags))
E 201
I 201
D 206
			if (map != NULL && bitset(MF_VALID, map->s_map.map_mflags))
E 206
I 206
			if (map != NULL && bitset(MF_OPEN, map->s_map.map_mflags))
E 206
E 201
D 144
				replac = (*map->s_map.map_class->map_lookup)(buf,
						sizeof buf - 1, arg_rvp);
E 144
I 144
D 145
				replac = (*map->s_map.map_class->map_lookup)(map,
E 145
I 145
			{
D 200
				int bsize = sizeof buf - 1;
E 200
I 186
				auto int stat = EX_OK;
E 186

I 283
				if (!bitset(MF_KEEPQUOTES, map->s_map.map_mflags))
					stripquotes(buf);

E 283
I 202
				/* XXX should try to auto-open the map here */

E 202
D 200
				if (map->s_map.map_app != NULL)
					bsize -= strlen(map->s_map.map_app);
E 200
I 176
				if (tTd(60, 1))
					printf("map_lookup(%s, %s) => ",
						mapname, buf);
E 176
				replac = (*map->s_map.map_class->map_lookup)(&map->s_map,
E 145
D 186
						buf, sizeof buf - 1, argvect);
E 186
I 186
D 198
						buf, sizeof buf - 1, argvect,
E 198
I 198
D 200
						buf, bsize, argvect,
E 198
						&stat);
E 186
I 145
				if (replac != NULL && map->s_map.map_app != NULL)
I 198
				{
					if (replac != buf)
					{
						if (strlen(replac) > bsize)
							strncpy(buf, replac, bsize);
						else
							strcpy(buf, replac);
						replac = buf;
					}
E 198
					strcat(replac, map->s_map.map_app);
I 198
				}
E 200
I 200
						buf, argvect, &stat);
E 200
E 198
I 176
				if (tTd(60, 1))
D 186
					printf("%s\n", replac ? replac : "NOT FOUND");
E 186
I 186
					printf("%s (%d)\n",
						replac ? replac : "NOT FOUND",
						stat);

				/* should recover if stat == EX_TEMPFAIL */
D 275
				if (stat == EX_TEMPFAIL)
					rstat = stat;
E 275
I 275
D 282
				if (stat == EX_TEMPFAIL || stat == EX_UNAVAILABLE)
E 282
I 282
				if (stat == EX_TEMPFAIL)
E 282
				{
					rstat = EX_TEMPFAIL;
D 276
					if (tTd(50, 1)
E 276
I 276
D 287
					if (tTd(50, 1))
E 287
I 287
					if (tTd(60, 1))
E 287
E 276
						printf("map_lookup(%s, %s) failed (stat = %d)\n",
							mapname, buf, stat);
					if (e->e_message == NULL)
					{
						char mbuf[300];

						sprintf(mbuf, "map %s: lookup (%s) failed",
							mapname, buf);
						e->e_message = newstr(mbuf);
					}
				}
E 275
E 186
E 176
			}
E 145
E 144
			else
				replac = NULL;
E 134
E 130

I 130
D 134
				/* it mapped -- mark it with a trailing dot */
				i = strlen(buf);
				if (i > 0 && buf[i - 1] != '.')
E 134
I 134
			/* if no replacement, use default */
I 144
			if (replac == NULL && default_rvp != NULL)
			{
D 200
				char buf2[sizeof buf];

				/* rewrite the default with % translations */
D 164
				cataddr(default_rvp, buf2, sizeof buf2);
E 164
I 164
D 179
				cataddr(default_rvp, buf2, sizeof buf2, '\0');
E 179
I 179
				cataddr(default_rvp, NULL, buf2, sizeof buf2, '\0');
E 179
E 164
				map_rewrite(buf2, sizeof buf2, buf, sizeof buf,
					argvect);
E 200
I 200
				/* create the default */
				cataddr(default_rvp, NULL, buf, sizeof buf, '\0');
E 200
				replac = buf;
			}

E 144
			if (replac == NULL)
			{
D 144
				if (default_rvp != NULL)
					xpvp = default_rvp;
				else
					xpvp = key_rvp;
E 144
I 144
				xpvp = key_rvp;
I 222
			}
			else if (*replac == '\0')
			{
				/* null replacement */
				nullpvp[0] = NULL;
				xpvp = nullpvp;
E 222
E 144
			}
			else
			{
				/* scan the new replacement */
D 168
				olddelimchar = DelimChar;
				xpvp = prescan(replac, '\0', pvpbuf);
				DelimChar = olddelimchar;
E 168
I 168
D 233
				xpvp = prescan(replac, '\0', pvpbuf, NULL);
E 233
I 233
				xpvp = prescan(replac, '\0', pvpbuf,
D 277
					       sizeof pvpbuf, NULL);
E 277
I 277
					       sizeof pvpbuf, NULL, NULL);
E 277
E 233
E 168
				if (xpvp == NULL)
E 134
				{
D 134
					buf[i++] = '.';
					buf[i] = '\0';
E 134
I 134
D 166
					syserr("rewrite: cannot prescan map value: %s", replac);
E 166
I 166
D 169
					syserr("553 rewrite: cannot prescan map value: %s", replac);
E 169
I 169
					/* prescan already printed error */
E 169
E 166
D 186
					return;
E 186
I 186
					return EX_DATAERR;
E 186
E 134
				}
			}

E 130
D 134
			/* scan the new host name */
E 138
I 138
			/* Look it up (lowercase version) */
			cataddr(hbrvp + (begintype == HOSTBEGIN ? 1 : 2),
			    hbuf, sizeof hbuf);
			if (begintype == HOSTBEGIN)
#ifdef VMUNIX
				match = maphostname(hbuf, sizeof hbuf);
#else /* !VMUNIX */
				match = FALSE;
#endif /* VMUNIX */
			else
			{
				if (ubrvp == NULL)
				{
					/* no sprintf argument part */
					match = (mapkey(db, hbuf, sizeof hbuf, NULL) != NULL);
				}
				else
				{
					cataddr(ubrvp, ubuf, sizeof ubuf);
					match = (mapkey(db, hbuf, sizeof hbuf, ubuf) != NULL);
				}
			}
			if (match || !defaultpart)
			{
				/* scan the new route/host name */
E 138
I 112
			olddelimchar = DelimChar;
E 112
D 138
			xpvp = prescan(buf, '\0', pvpbuf);
E 138
I 138
				xpvp = prescan(hbuf, '\0', pvpbuf);
E 138
I 112
			DelimChar = olddelimchar;
E 112
D 138
			if (xpvp == NULL)
			{
				syserr("rewrite: cannot prescan canonical hostname: %s", buf);
E 138
I 138
				if (xpvp == NULL)
				{
					syserr("rewrite: cannot prescan %s: %s", 
					    begintype == HOSTBEGIN ?
					    "new hostname" :
					    "dbm lookup result",
					    hbuf);
E 138
D 114
				return (NULL);
E 114
I 114
				return;
E 114
			}

E 134
			/* append it to the token list */
D 108
			rvp = --hbrvp;
			while ((*rvp++ = *xpvp++) != NULL)
				if (rvp >= &npvp[MAXATOM])
E 108
I 108
D 109
			avp = --hbrvp;
			while ((*avp++ = *xpvp++) != NULL)
E 109
I 109
D 134
D 138
			for (avp = --hbrvp; *xpvp != NULL; xpvp++)
E 134
I 134
			for (avp = hbrvp; *xpvp != NULL; xpvp++)
E 134
			{
E 138
I 138
				for (avp = hbrvp; *xpvp != NULL; xpvp++)
				{
E 138
				*avp++ = newstr(*xpvp);
E 109
				if (avp >= &npvp[MAXATOM])
E 108
					goto toolong;
I 138
				}
E 138
I 109
			}
I 138
			else
				avp = hbrvp;
E 138
E 109

			/* restore the old trailing information */
D 108
			for (xpvp = pvpb1, rvp--; (*rvp++ = *xpvp++) != NULL; )
				if (rvp >= &npvp[MAXATOM])
E 108
I 108
D 110
			for (xpvp = pvpb1, avp--; (*avp++ = *xpvp++) != NULL; )
E 110
I 110
D 138
			for (xpvp = pvpb1; (*avp++ = *xpvp++) != NULL; )
E 138
I 138
			rvp = avp - 1;
			for (xpvp = pvpb1; *xpvp != NULL; xpvp++)
			{
D 139
				if (defaultpart && (begintype == HOSTBEGIN ?
				    **xpvp == HOSTEND :
				    **xpvp == KEYEND))
E 139
I 139
				if (defaultpart && **xpvp == HOSTEND)
E 139
				{
					defaultpart = FALSE;
					rvp = avp - 1;
				}
				else if (!defaultpart || !match)
					*avp++ = *xpvp;
E 138
E 110
				if (avp >= &npvp[MAXATOM])
E 108
					goto toolong;
I 138
			}
			*avp++ = NULL;
E 138
I 109

D 138
			break;
E 138
I 138
			/*break;*/
E 138
E 109
		}

		/*
		**  Check for subroutine calls.
I 138
		**  Then copy vector back into original space.
E 138
		*/

E 107
D 104
D 117
		if (**npvp == CALLSUBR)
E 117
I 117
D 138
D 162
		if (*npvp != NULL && **npvp == CALLSUBR)
E 162
I 162
D 271
		if (*npvp != NULL && (**npvp & 0377) == CALLSUBR)
E 162
E 117
E 104
I 104

		/*
		**  Do hostname lookup if requested.
		*/

		if (dolookup)
E 104
		{
I 186
			int stat;
E 271
I 271
		rstat = callsubr(npvp, reclevel, e);
E 271

E 186
D 104
D 105
			bmove((char *) &npvp[2], (char *) pvp,
E 105
I 105
D 239
			bcopy((char *) &npvp[2], (char *) pvp,
E 105
D 106
				(avp - npvp - 2) * sizeof *avp);
E 106
I 106
				(int) (avp - npvp - 2) * sizeof *avp);
E 106
E 83
E 73
E 28
D 126
# ifdef DEBUG
E 126
D 33
			if (Debug)
E 33
I 33
D 60
			if (Debug > 3)
E 60
I 60
D 83
			if (tTd(21, 4))
E 60
E 33
			{
D 20
				printf("rewritten as:\n");
				printav(pvp);
E 20
I 20
D 68
				char **vp;

				printf("rewritten as `");
				for (vp = pvp; *vp != NULL; vp++)
I 33
				{
					if (vp != pvp)
						printf("_");
E 33
					xputs(*vp);
I 33
				}
E 33
				printf("'\n");
E 68
I 68
				printf("rewritten as:");
				printav(pvp);
E 68
E 20
			}
E 83
I 83
			if (tTd(21, 3))
				printf("-----callsubr %s\n", npvp[1]);
E 83
D 126
# endif DEBUG
E 126
I 83
D 184
			rewrite(pvp, atoi(npvp[1]));
E 184
I 184
D 186
			rewrite(pvp, atoi(npvp[1]), e);
E 186
I 186
D 234
			stat = rewrite(pvp, atoi(npvp[1]), e);
E 234
I 234
			stat = rewrite(pvp, atoi(npvp[1]), reclevel, e);
E 234
			if (rstat == EX_OK || stat == EX_TEMPFAIL)
				rstat = stat;
I 211
D 232
			if ((**pvp & 0377) == CANONNET)
E 232
I 232
			if (*pvp != NULL && (**pvp & 0377) == CANONNET)
E 239
I 239
D 271
			if (npvp[1] == NULL)
			{
				syserr("parseaddr: NULL subroutine call in ruleset %d, rule %d",
					ruleset, ruleno);
				*pvp = NULL;
			}
			else
			{
I 264
				int ruleset;
				STAB *s;
E 271
I 271
		/* copy vector back into original space */
		for (avp = npvp; *avp++ != NULL; )
			continue;
		bcopy(npvp, pvp, (avp - npvp) * sizeof *avp);
E 271

E 264
D 271
				bcopy((char *) &npvp[2], (char *) pvp,
					(int) (avp - npvp - 2) * sizeof *avp);
				if (tTd(21, 3))
					printf("-----callsubr %s\n", npvp[1]);
D 264
				stat = rewrite(pvp, atoi(npvp[1]), reclevel, e);
E 264
I 264
D 285
				s = stab(npvp[1], ST_RULESET, ST_FIND);
				if (s == NULL)
					ruleset = atoi(npvp[1]);
				else
					ruleset = s->s_ruleset;
E 285
I 285
				ruleset = strtorwset(npvp[1], NULL, ST_FIND);
E 285
				stat = rewrite(pvp, ruleset, reclevel, e);
E 264
				if (rstat == EX_OK || stat == EX_TEMPFAIL)
					rstat = stat;
				if (*pvp != NULL && (**pvp & 0377) == CANONNET)
E 239
E 232
				rwr = NULL;
I 239
			}
E 239
E 211
E 186
E 184
E 104
I 104
			extern char **maphost();

			rvp = maphost(npvp);
E 104
E 83
D 66
			if (pvp[0][0] == CANONNET)
E 66
I 66
D 68
			if (**pvp == CANONNET || **pvp == CANONUSER)
E 66
				break;
E 68
		}
		else
I 104
			rvp = npvp;

		/*
		**  See if this is a subroutine call.
		*/

		if (**rvp == CALLSUBR)
E 104
		{
E 138
I 138
		callsubr(npvp);

		for (avp = npvp; *avp++ != NULL;);
E 138
I 83
D 104
D 105
			bmove((char *) npvp, (char *) pvp,
E 105
I 105
D 107
			bcopy((char *) npvp, (char *) pvp,
E 107
I 107
D 111
			bmove((char *) npvp, (char *) pvp,
E 111
I 111
			bcopy((char *) npvp, (char *) pvp,
E 111
E 107
E 105
D 106
				(avp - npvp) * sizeof *avp);
E 106
I 106
				(int) (avp - npvp) * sizeof *avp);
E 106
E 104
I 104
			subr = atoi(*++rvp);
			rvp++;
E 104
D 138
		}
E 271
E 138
I 138

E 138
I 104
		else
			subr = -1;

		/*
		**  Copy result back to original string.
		*/

		for (avp = pvp; *rvp != NULL; rvp++)
			*avp++ = *rvp;
		*avp = NULL;

		/*
		**  If this specified a subroutine, call it.
		*/

		if (subr >= 0)
		{
# ifdef DEBUG
			if (tTd(21, 3))
				printf("-----callsubr %s\n", subr);
# endif DEBUG
			rewrite(pvp, subr);
		}

		/*
		**  Done with rewriting this pass.
		*/

E 104
E 83
D 20
# ifdef DEBUG
E 20
I 20
D 29
# ifdef DEBUGX
E 20
			if (Debug)
E 29
I 29
D 126
# ifdef DEBUG
E 126
D 60
			if (Debug > 10)
E 60
I 60
D 83
			if (tTd(21, 10))
E 60
E 29
				printf("----- rule fails\n");
D 20
# endif DEBUG
E 20
I 20
D 29
# endif DEBUGX
E 29
I 29
# endif DEBUG
E 29
E 20
			rwr = rwr->r_next;
E 83
I 83
		if (tTd(21, 4))
		{
			printf("rewritten as:");
D 138
			printav(pvp);
E 138
I 138
			printcav(pvp);
E 138
E 83
		}
I 83
D 126
# endif DEBUG
E 126
E 83
E 18
E 11
	}
I 68

D 74
# ifdef DEBUG
	if (tTd(21, 2))
E 74
I 74
D 81
	if (Mode == MD_TEST || tTd(21, 2))
E 81
I 81
D 245
	if (OpMode == MD_TEST || tTd(21, 2))
E 245
I 245
	if (OpMode == MD_TEST || tTd(21, 1))
E 245
E 81
E 74
	{
D 78
		printf("rewrite: ruleset %d returns:", ruleset);
E 78
I 78
		printf("rewrite: ruleset %2d returns:", ruleset);
E 78
D 138
		printav(pvp);
E 138
I 138
		printcav(pvp);
E 138
	}
I 186

	return rstat;
I 271
}
/*
**  CALLSUBR -- call subroutines in rewrite vector
**
**	Parameters:
**		pvp -- pointer to token vector.
**
**	Returns:
**		none.
**
**	Side Effects:
**		pvp is modified.
*/

static int
callsubr(pvp, reclevel, e)
	char **pvp;
	int reclevel;
	ENVELOPE *e;
{
	char **rvp;
	int subr;
	int stat;
	STAB *s;

	for (; *pvp != NULL; pvp++)
	{
		if ((**pvp & 0377) == CALLSUBR && pvp[1] != NULL)
			break;
	}
	if (*pvp == NULL)
		return EX_OK;

	if (tTd(21, 3))
		printf("-----callsubr %s\n", pvp[1]);

	s = stab(pvp[1], ST_RULESET, ST_FIND);
	if (s == NULL)
		subr = atoi(pvp[1]);
	else
		subr = s->s_ruleset;

	/*
	**  Take care of possible inner calls.
	*/

	stat = callsubr(&pvp[2], reclevel, e);
	if (stat != EX_OK)
		return stat;

	/*
	**  Move vector up over calling opcode.
	*/

	for (rvp = &pvp[2]; *rvp != NULL; rvp++)
		rvp[-2] = rvp[0];
	rvp[-2] = NULL;

	/*
	**  Call inferior ruleset.
	*/

	stat = rewrite(pvp, subr, reclevel, e);
	return stat;
E 271
E 186
D 74
# endif DEBUG
E 74
E 68
D 18
	*q = '\0';
	if (c == '\0')
		p--;
	if (cmntcnt > 0)
		usrerr("Unbalanced '('");
	else if (quotemode)
		usrerr("Unbalanced '\"'");
	else if (brccnt > 0)
		usrerr("Unbalanced '<'");
	else if (buf[0] != '\0')
		return (p);
E 18
I 18
D 42
}
/*
**  SETMATCH -- set parameter value in match vector
**
**	Parameters:
**		mlist -- list of match values.
**		name -- the character name of this parameter.
**		first -- the first location of the replacement.
**		last -- the last location of the replacement.
**
**		If last == NULL, delete this entry.
**		If first == NULL, extend this entry (or add it if
**			it does not exist).
**
**	Returns:
**		nothing.
**
**	Side Effects:
**		munges with mlist.
*/

setmatch(mlist, name, first, last)
	struct match *mlist;
	char name;
	char **first;
	char **last;
{
	register struct match *m;
	struct match *nullm = NULL;

	for (m = mlist; m < &mlist[MAXMATCH]; m++)
	{
		if (m->name == name)
			break;
		if (m->name == '\0')
			nullm = m;
	}

	if (m >= &mlist[MAXMATCH])
		m = nullm;

	if (last == NULL)
	{
		m->name = '\0';
		return;
	}

	if (m->name == '\0')
	{
		if (first == NULL)
			m->firsttok = last;
		else
			m->firsttok = first;
	}
	m->name = name;
	m->lasttok = last;
}
/*
**  FINDMATCH -- find match in mlist
**
**	Parameters:
**		mlist -- list to search.
**		name -- name to find.
**
**	Returns:
**		pointer to match structure.
**		NULL if no match.
**
**	Side Effects:
**		none.
*/

struct match *
findmatch(mlist, name)
	struct match *mlist;
	char name;
{
	register struct match *m;

	for (m = mlist; m < &mlist[MAXMATCH]; m++)
	{
		if (m->name == name)
			return (m);
	}

E 18
	return (NULL);
I 18
}
/*
**  CLRMATCH -- clear match list
**
**	Parameters:
**		mlist -- list to clear.
**
**	Returns:
**		none.
**
**	Side Effects:
**		mlist is cleared.
*/

clrmatch(mlist)
	struct match *mlist;
{
	register struct match *m;

	for (m = mlist; m < &mlist[MAXMATCH]; m++)
		m->name = '\0';
E 42
}
/*
I 138
**  CALLSUBR -- call subroutines in rewrite vector
**
**	Parameters:
**		pvp -- pointer to token vector.
**
**	Returns:
**		none.
**
**	Side Effects:
**		pvp is modified.
*/

static void
callsubr(pvp)
	char **pvp;
{
	char **rvp;
	int subr;

	for (; *pvp != NULL; pvp++)
		if (**pvp == CALLSUBR && pvp[1] != NULL && isdigit(pvp[1][0]))
		{
			subr = atoi(pvp[1]);

			if (tTd(21, 3))
				printf("-----callsubr %d\n", subr);

			/*
			**  Take care of possible inner calls.
			*/
			callsubr(pvp+2);

			/*
			**  Move vector up over calling opcode.
			*/
			for (rvp = pvp+2; *rvp != NULL; rvp++)
				rvp[-2] = rvp[0];
			rvp[-2] = NULL;

			/*
			**  Call inferior ruleset.
			*/
			_rewrite(pvp, subr);

			break;
		}
}
/*
E 138
**  BUILDADDR -- build address from token vector.
**
**	Parameters:
**		tv -- token vector.
**		a -- pointer to address descriptor to fill.
**			If NULL, one will be allocated.
I 218
**		flags -- info regarding whether this is a sender or
**			a recipient.
E 218
I 183
**		e -- the current envelope.
E 183
**
**	Returns:
D 35
**		'a'
E 35
I 35
**		NULL if there was an error.
**		'a' otherwise.
E 35
**
**	Side Effects:
**		fills in 'a'
*/

I 147
struct errcodes
{
	char	*ec_name;		/* name of error code */
	int	ec_code;		/* numeric code */
} ErrorCodes[] =
{
	"usage",	EX_USAGE,
	"nouser",	EX_NOUSER,
	"nohost",	EX_NOHOST,
	"unavailable",	EX_UNAVAILABLE,
	"software",	EX_SOFTWARE,
	"tempfail",	EX_TEMPFAIL,
	"protocol",	EX_PROTOCOL,
#ifdef EX_CONFIG
	"config",	EX_CONFIG,
#endif
	NULL,		EX_UNAVAILABLE,
};

E 147
D 138
ADDRESS *
E 138
I 138
static ADDRESS *
E 138
D 183
buildaddr(tv, a)
E 183
I 183
D 218
buildaddr(tv, a, e)
E 218
I 218
buildaddr(tv, a, flags, e)
E 218
E 183
	register char **tv;
	register ADDRESS *a;
I 218
	int flags;
E 218
I 183
	register ENVELOPE *e;
E 183
{
D 46
	register int i;
E 46
D 151
	static char buf[MAXNAME];
E 151
	struct mailer **mp;
	register struct mailer *m;
I 280
	register char *p;
E 280
I 158
D 284
	char *bp;
E 284
D 280
	int spaceleft;
E 280
I 280
	char *mname;
	char **hostp;
	char hbuf[MAXNAME + 1];
E 280
I 219
	static MAILER errormailer;
	static char *errorargv[] = { "ERROR", NULL };
E 219
E 158
I 151
D 269
	static char buf[MAXNAME];
E 269
I 269
D 280
	static char buf[MAXNAME + 1];
E 280
I 280
	static char ubuf[MAXNAME + 1];
E 280
E 269
E 151
I 47
D 123
	extern bool sameword();
E 123
E 47
D 28
	extern char *xalloc();
E 28

I 228
	if (tTd(24, 5))
	{
D 247
		printf("buildaddr, flags=%o, tv=", flags);
E 247
I 247
		printf("buildaddr, flags=%x, tv=", flags);
E 247
		printav(tv);
	}

E 228
	if (a == NULL)
		a = (ADDRESS *) xalloc(sizeof *a);
I 20
D 48
D 49
	a->q_flags = 0;
I 27
	a->q_home = NULL;
E 49
I 49
D 105
	clear((char *) a, sizeof *a);
E 105
I 105
	bzero((char *) a, sizeof *a);
E 105
E 49
E 48
I 48
	clear((char *) a, sizeof *a);
E 48
E 27
E 20

I 251
	/* set up default error return flags */
D 253
	a->q_flags |= QPINGONFAILURE;
E 253
I 253
	a->q_flags |= QPINGONFAILURE|QPINGONDELAY;
E 253

E 251
	/* figure out what net/mailer to use */
D 138
D 162
	if (**tv != CANONNET)
E 162
I 162
D 219
	if ((**tv & 0377) != CANONNET)
E 219
I 219
	if (*tv == NULL || (**tv & 0377) != CANONNET)
E 219
E 162
E 138
I 138
	if (*tv == NULL || **tv != CANONNET)
E 138
I 35
	{
E 35
D 166
		syserr("buildaddr: no net");
E 166
I 166
		syserr("554 buildaddr: no net");
E 166
I 35
D 219
		return (NULL);
E 219
I 219
badaddr:
		a->q_flags |= QBADADDR;
		a->q_mailer = &errormailer;
		if (errormailer.m_name == NULL)
		{
			/* initialize the bogus mailer */
			errormailer.m_name = "*error*";
			errormailer.m_mailer = "ERROR";
			errormailer.m_argv = errorargv;
		}
		return a;
E 219
	}
E 35
D 280
	tv++;
I 35
D 47
	if (strcmp(*tv, "error") == 0)
E 47
I 47
D 123
	if (sameword(*tv, "error"))
E 123
I 123
D 175
	if (!strcasecmp(*tv, "error"))
E 175
I 175
	if (strcasecmp(*tv, "error") == 0)
E 280
I 280
	mname = *++tv;

	/* extract host and user portions */
	if ((**++tv & 0377) == CANONHOST)
		hostp = ++tv;
	else
		hostp = NULL;
	while (*tv != NULL && (**tv & 0377) != CANONUSER)
		tv++;
	if (*tv == NULL)
E 280
E 175
E 123
E 47
	{
D 89
		if (**++tv != CANONUSER)
E 89
I 89
D 162
		if (**++tv == CANONHOST)
E 162
I 162
D 280
		if ((**++tv & 0377) == CANONHOST)
E 280
I 280
		syserr("554 buildaddr: no user");
		goto badaddr;
	}
	if (hostp != NULL)
		cataddr(hostp, tv - 1, hbuf, sizeof hbuf, '\0');
	cataddr(++tv, NULL, ubuf, sizeof ubuf, '\0');

	/* save away the host name */
	if (strcasecmp(mname, "error") == 0)
	{
		if (hostp != NULL)
E 280
E 162
		{
D 147
			setstat(atoi(*++tv));
E 147
I 147
			register struct errcodes *ep;

D 162
			if (isdigit(**++tv))
E 162
I 162
D 280
			if (isascii(**++tv) && isdigit(**tv))
E 280
I 280
			if (strchr(hbuf, '.') != NULL)
E 280
E 162
			{
D 280
				setstat(atoi(*tv));
E 280
I 280
				a->q_status = newstr(hbuf);
				setstat(dsntoexitstat(hbuf));
E 280
			}
I 280
			else if (isascii(hbuf[0]) && isdigit(hbuf[0]))
			{
				setstat(atoi(hbuf));
			}
E 280
			else
			{
				for (ep = ErrorCodes; ep->ec_name != NULL; ep++)
D 280
					if (strcasecmp(ep->ec_name, *tv) == 0)
E 280
I 280
					if (strcasecmp(ep->ec_name, hbuf) == 0)
E 280
						break;
				setstat(ep->ec_code);
			}
E 147
D 280
			tv++;
E 280
		}
I 229
		else
			setstat(EX_UNAVAILABLE);
E 229
I 138
		buf[0] = '\0';
		for (; (*tv != NULL) && (**tv != CANONUSER); tv++)
		{
			if (buf[0] != '\0')
				(void) strcat(buf, " ");
			(void) strcat(buf, *tv);
		}
E 138
D 162
		if (**tv != CANONUSER)
E 162
I 162
D 280
		if ((**tv & 0377) != CANONUSER)
E 162
E 89
D 166
			syserr("buildaddr: error: no user");
E 166
I 166
			syserr("554 buildaddr: error: no user");
E 166
D 138
D 158
		buf[0] = '\0';
E 158
I 158
D 164
		bp = buf;
		spaceleft = sizeof buf - 2;
E 158
E 138
		while (*++tv != NULL)
		{
D 158
			if (buf[0] != '\0')
D 59
				strcat(buf, " ");
			strcat(buf, *tv);
E 59
I 59
				(void) strcat(buf, " ");
			(void) strcat(buf, *tv);
E 158
I 158
			int i = strlen(*tv);

			if (i > spaceleft)
			{
				/* out of space for this address */
				if (spaceleft >= 0)
					syserr("buildaddr: error message too long (%.40s...)",
						buf);
				i = spaceleft;
				spaceleft = 0;
			}
			if (i <= 0)
				continue;
			if (bp != buf)
			{
				*bp++ = ' ';
				spaceleft--;
			}
			bcopy(*tv, bp, i);
			bp += i;
			spaceleft -= i;
E 158
E 59
		}
I 159
		*bp = '\0';
E 164
I 164
D 179
		cataddr(++tv, buf, sizeof buf, ' ');
E 179
I 179
		cataddr(++tv, NULL, buf, sizeof buf, ' ');
E 179
		stripquotes(buf);
E 164
E 159
I 138
#ifdef LOG
		if (LogLevel > 8)
			syslog (LOG_DEBUG, "%s: Trace: $#ERROR $: %s",
				CurEnv->e_id, buf);
#endif /* LOG */
E 138
D 221
		usrerr(buf);
E 221
I 221
D 223
		usrerr("%s", buf);
E 223
I 223
		if (isascii(buf[0]) && isdigit(buf[0]) &&
		    isascii(buf[1]) && isdigit(buf[1]) &&
		    isascii(buf[2]) && isdigit(buf[2]) &&
		    buf[3] == ' ')
E 280
I 280
		stripquotes(ubuf);
		if (isascii(ubuf[0]) && isdigit(ubuf[0]) &&
		    isascii(ubuf[1]) && isdigit(ubuf[1]) &&
		    isascii(ubuf[2]) && isdigit(ubuf[2]) &&
		    ubuf[3] == ' ')
E 280
		{
			char fmt[10];

D 280
			strncpy(fmt, buf, 3);
E 280
I 280
			strncpy(fmt, ubuf, 3);
E 280
			strcpy(&fmt[3], " %s");
D 280
			usrerr(fmt, buf + 4);
E 280
I 280
			usrerr(fmt, ubuf + 4);
E 280
I 249

			/*
			**  If this is a 4xx code and we aren't running
			**  SMTP on our input, bounce this message;
			**  otherwise it disappears without a trace.
			*/

			if (fmt[0] == '4' && OpMode != MD_SMTP &&
			    OpMode != MD_DAEMON)
			{
				e->e_flags |= EF_FATALERRS;
			}
E 249
		}
		else
		{
D 242
			usrerr("%s", buf);
E 242
I 242
D 280
			usrerr("553 %s", buf);
E 280
I 280
			usrerr("553 %s", ubuf);
E 280
E 242
		}
E 223
E 221
I 183
D 194
		if (e->e_message == NULL)
			e->e_message = newstr(buf);
E 194
E 183
D 219
		return (NULL);
E 219
I 219
		goto badaddr;
E 219
	}
I 151

E 151
E 35
D 19
	for (mp = Mailer, i = 0; (m = *mp) != NULL; m++, i++)
E 19
I 19
D 45
	for (mp = Mailer, i = 0; (m = *mp++) != NULL; i++)
E 45
I 45
	for (mp = Mailer; (m = *mp++) != NULL; )
E 45
E 19
	{
D 47
		if (strcmp(m->m_name, *tv) == 0)
E 47
I 47
D 123
		if (sameword(m->m_name, *tv))
E 123
I 123
D 175
		if (!strcasecmp(m->m_name, *tv))
E 175
I 175
D 280
		if (strcasecmp(m->m_name, *tv) == 0)
E 280
I 280
		if (strcasecmp(m->m_name, mname) == 0)
E 280
E 175
E 123
E 47
			break;
	}
	if (m == NULL)
I 35
	{
E 35
D 117
		syserr("buildaddr: unknown net %s", *tv);
E 117
I 117
D 166
		syserr("buildaddr: unknown mailer %s", *tv);
E 166
I 166
D 280
		syserr("554 buildaddr: unknown mailer %s", *tv);
E 280
I 280
		syserr("554 buildaddr: unknown mailer %s", mname);
E 280
E 166
E 117
I 35
D 219
		return (NULL);
E 219
I 219
		goto badaddr;
E 219
	}
E 35
D 45
	a->q_mailer = i;
E 45
I 45
	a->q_mailer = m;
E 45

	/* figure out what host (if any) */
D 138
D 280
	tv++;
D 31
	if (!bitset(M_NOHOST, m->m_flags))
E 31
I 31
D 91
	if (!bitset(M_LOCAL, m->m_flags))
E 91
I 91
D 146
D 165
	if (!bitnset(M_LOCAL, m->m_flags))
E 165
I 165
D 171
	if (!bitnset(M_LOCALMAILER, m->m_flags))
E 171
I 171
	if ((**tv & 0377) == CANONHOST)
E 280
I 280
	if (hostp == NULL)
E 280
E 171
E 165
E 146
I 146
	if (**tv != CANONHOST)
E 146
E 138
I 138
	if (**++tv != CANONHOST)
E 138
E 91
E 31
	{
D 53
		if (**tv != CANONHOST)
E 53
I 53
D 138
D 146
D 158
		if (**tv++ != CANONHOST)
E 158
I 158
D 162
		if (**tv != CANONHOST)
E 162
I 162
D 171
		if ((**tv & 0377) != CANONHOST)
E 162
E 158
E 146
I 146
		if (!bitnset(M_LOCAL, m->m_flags))
E 146
E 138
I 138
		if (!bitnset(M_LOCAL, m->m_flags))
E 138
E 53
I 35
		{
E 35
D 166
			syserr("buildaddr: no host");
E 166
I 166
			syserr("554 buildaddr: no host");
E 166
I 35
			return (NULL);
		}
E 171
I 146
		a->q_host = NULL;
	}
	else
	{
E 146
I 138
		else
			a->q_host = NULL;
	}
	else
	{
E 138
E 35
D 53
		tv++;
		a->q_host = *tv;
		tv++;
E 53
I 53
D 158
		buf[0] = '\0';
D 138
D 146
		while (*tv != NULL && **tv != CANONUSER)
D 59
			strcat(buf, *tv++);
E 59
I 59
			(void) strcat(buf, *tv++);
E 158
I 158
D 280
		bp = buf;
		spaceleft = sizeof buf - 1;
D 162
		while (*++tv != NULL && **tv != CANONUSER)
E 162
I 162
		while (*++tv != NULL && (**tv & 0377) != CANONUSER)
E 162
		{
			int i = strlen(*tv);

			if (i > spaceleft)
			{
				/* out of space for this address */
				if (spaceleft >= 0)
D 166
					syserr("buildaddr: host too long (%.40s...)",
E 166
I 166
					syserr("554 buildaddr: host too long (%.40s...)",
E 166
						buf);
				i = spaceleft;
				spaceleft = 0;
			}
			if (i <= 0)
				continue;
			bcopy(*tv, bp, i);
			bp += i;
			spaceleft -= i;
		}
I 159
		*bp = '\0';
E 159
E 158
E 146
I 146
		while (*++tv != NULL && **tv != CANONUSER)
			(void) strcat(buf, *tv);
E 146
E 138
I 138
		while (*++tv != NULL && **tv != CANONUSER)
			(void) strcat(buf, *tv);
E 138
E 59
		a->q_host = newstr(buf);
E 53
	}
D 138
D 146
	else
I 171
	{
E 280
		if (!bitnset(M_LOCALMAILER, m->m_flags))
		{
			syserr("554 buildaddr: no host");
D 219
			return (NULL);
E 219
I 219
			goto badaddr;
E 219
		}
E 171
		a->q_host = NULL;
I 171
	}
I 280
	else
		a->q_host = newstr(hbuf);
E 280
E 171
E 146
E 138

	/* figure out the user */
D 127
	if (**tv != CANONUSER)
E 127
I 127
D 162
	if (*tv == NULL || **tv != CANONUSER)
E 162
I 162
D 280
	if (*tv == NULL || (**tv & 0377) != CANONUSER)
E 280
I 280
	p = ubuf;
	if (bitnset(M_CHECKUDB, m->m_flags) && *p == '@')
E 280
E 162
E 127
I 35
	{
E 35
D 166
		syserr("buildaddr: no user");
E 166
I 166
D 280
		syserr("554 buildaddr: no user");
E 166
I 35
D 219
		return (NULL);
E 219
I 219
		goto badaddr;
E 219
	}
E 35
D 33
	buf[0] = '\0';
	while (**++tv != NULL)
D 28
		strcat(buf, *tv);
E 28
I 28
		(void) strcat(buf, *tv);
E 33
I 33
D 93
	cataddr(++tv, buf, sizeof buf);
E 93
I 93
D 113
	rewrite(++tv, 4);
E 113
I 113
D 158

I 138
	/* define tohost before running mailer rulesets */
	define('h', a->q_host, CurEnv);

E 138
I 130
D 132
	if (m == LocalMailer && tv[1] != NULL && strcmp(tv[1], ":") == 0)
E 132
I 132
	if (m == LocalMailer && tv[1] != NULL && strcmp(tv[1], "@") == 0)
E 132
	{
		tv++;
		a->q_flags |= QNOTREMOTE;
	}
E 158
I 151
	tv++;
E 151

I 259
	if (bitnset(M_CHECKUDB, m->m_flags) && *tv != NULL &&
	    strcmp(*tv, "@") == 0)
	{
E 280
I 280
		p++;
E 280
		tv++;
		a->q_flags |= QNOTREMOTE;
	}

E 259
I 151
	/* do special mapping for local mailer */
D 246
	if (m == LocalMailer && *tv != NULL)
E 246
I 246
D 280
	if (*tv != NULL)
E 280
I 280
	if (*p == '"')
		p++;
	if (*p == '|' && bitnset(M_CHECKPROG, m->m_flags))
		a->q_mailer = m = ProgMailer;
	else if (*p == '/' && bitnset(M_CHECKFILE, m->m_flags))
		a->q_mailer = m = FileMailer;
	else if (*p == ':' && bitnset(M_CHECKINCLUDE, m->m_flags))
E 280
E 246
	{
D 152
		if (**tv == '|')
E 152
I 152
D 280
		register char *p = *tv;

		if (*p == '"')
			p++;
D 246
		if (*p == '|')
E 246
I 246
		if (*p == '|' && bitnset(M_CHECKPROG, m->m_flags))
E 246
E 152
			a->q_mailer = m = ProgMailer;
D 152
		else if (**tv == '/')
E 152
I 152
D 246
		else if (*p == '/')
E 246
I 246
		else if (*p == '/' && bitnset(M_CHECKFILE, m->m_flags))
E 246
E 152
			a->q_mailer = m = FileMailer;
D 152
		else if (**tv == ':')
E 152
I 152
D 246
		else if (*p == ':')
E 246
I 246
		else if (*p == ':' && bitnset(M_CHECKINCLUDE, m->m_flags))
E 280
I 280
		/* may be :include: */
		stripquotes(ubuf);
		if (strncasecmp(ubuf, ":include:", 9) == 0)
E 280
E 246
E 152
		{
D 280
			/* may be :include: */
D 164
			cataddr(tv, buf, sizeof buf);
E 164
I 164
D 179
			cataddr(tv, buf, sizeof buf, '\0');
E 179
I 179
			cataddr(tv, NULL, buf, sizeof buf, '\0');
E 179
E 164
D 152
			buf[9] = '\0';
			if (strcasecmp(buf, ":include:") == 0)
E 152
I 152
D 158
			p = buf;
			if (*p == '"')
				p++;
			p[9] = '\0';
			if (strcasecmp(p, ":include:") == 0)
E 158
I 158
			stripquotes(buf);
			if (strncasecmp(buf, ":include:", 9) == 0)
			{
				/* if :include:, don't need further rewriting */
E 158
E 152
				a->q_mailer = m = InclMailer;
I 158
				a->q_user = &buf[9];
				return (a);
			}
E 280
I 280
			/* if :include:, don't need further rewriting */
			a->q_mailer = m = InclMailer;
			a->q_user = newstr(&ubuf[9]);
			return a;
E 280
E 158
		}
I 158
D 259
	}

D 246
	if (m == LocalMailer && *tv != NULL && strcmp(*tv, "@") == 0)
E 246
I 246
	if (bitnset(M_CHECKUDB, m->m_flags) && *tv != NULL &&
	    strcmp(*tv, "@") == 0)
E 246
	{
		tv++;
		a->q_flags |= QNOTREMOTE;
E 259
E 158
	}

E 151
E 130
D 174
	/* rewrite according recipient mailer rewriting rules */
D 151
	rewrite(++tv, 2);
E 151
I 151
	rewrite(tv, 2);
E 151
D 138
D 160
	if (m->m_r_rwset > 0)
		rewrite(tv, m->m_r_rwset);
E 160
I 160
	if (m->m_re_rwset > 0)
		rewrite(tv, m->m_re_rwset);
E 174
I 174
D 218
	/* do cleanup of final address */
E 218
I 218
	/* rewrite according recipient mailer rewriting rules */
	define('h', a->q_host, e);
	if (!bitset(RF_SENDERADDR|RF_HEADERADDR, flags))
	{
		/* sender addresses done later */
D 234
		(void) rewrite(tv, 2, e);
E 234
I 234
		(void) rewrite(tv, 2, 0, e);
E 234
		if (m->m_re_rwset > 0)
D 234
		       (void) rewrite(tv, m->m_re_rwset, e);
E 234
I 234
		       (void) rewrite(tv, m->m_re_rwset, 0, e);
E 234
	}
E 218
E 174
E 160
E 138
I 138
D 139
	if (m->m_re_rwset > 0)
		rewrite(tv, m->m_re_rwset);
E 139
I 139
	if (m->m_r_rwset > 0)
		rewrite(tv, m->m_r_rwset);
E 139
E 138
D 184
	rewrite(tv, 4);
E 184
I 184
D 186
	rewrite(tv, 4, e);
E 186
I 186
D 234
	(void) rewrite(tv, 4, e);
E 234
I 234
	(void) rewrite(tv, 4, 0, e);
E 234
E 186
E 184

	/* save the result for the command line/RCPT argument */
E 113
D 164
	cataddr(tv, buf, sizeof buf);
E 164
I 164
D 179
	cataddr(tv, buf, sizeof buf, '\0');
E 179
I 179
D 280
	cataddr(tv, NULL, buf, sizeof buf, '\0');
E 179
E 164
E 93
E 33
E 28
	a->q_user = buf;
E 280
I 280
	cataddr(tv, NULL, ubuf, sizeof ubuf, '\0');
	a->q_user = ubuf;
E 280
I 173

	/*
	**  Do mapping to lower case as requested by mailer
	*/

	if (a->q_host != NULL && !bitnset(M_HST_UPPER, m->m_flags))
		makelower(a->q_host);
	if (!bitnset(M_USR_UPPER, m->m_flags))
		makelower(a->q_user);
E 173

D 280
	return (a);
E 280
I 280
	return a;
E 280
I 33
}
/*
**  CATADDR -- concatenate pieces of addresses (putting in <LWSP> subs)
**
**	Parameters:
**		pvp -- parameter vector to rebuild.
I 179
**		evp -- last parameter to include.  Can be NULL to
**			use entire pvp.
E 179
**		buf -- buffer to build the string into.
**		sz -- size of buf.
I 164
**		spacesub -- the space separator character; if null,
**			use SpaceSub.
E 164
**
**	Returns:
**		none.
**
**	Side Effects:
**		Destroys buf.
*/

I 284
void
E 284
I 138
void
E 138
D 164
cataddr(pvp, buf, sz)
E 164
I 164
D 179
cataddr(pvp, buf, sz, spacesub)
E 179
I 179
cataddr(pvp, evp, buf, sz, spacesub)
E 179
E 164
	char **pvp;
I 179
	char **evp;
E 179
	char *buf;
	register int sz;
I 164
D 284
	char spacesub;
E 284
I 284
	int spacesub;
E 284
E 164
{
	bool oatomtok = FALSE;
D 138
	bool natomtok = FALSE;
E 138
I 138
	bool natomtok;
E 138
	register int i;
	register char *p;

I 164
	if (spacesub == '\0')
		spacesub = SpaceSub;

E 164
I 76
	if (pvp == NULL)
	{
D 115
		strcpy(buf, "");
E 115
I 115
		(void) strcpy(buf, "");
E 115
		return;
	}
E 76
	p = buf;
D 92
	sz--;
E 92
I 92
	sz -= 2;
E 92
I 66
D 68
	if (*pvp != NULL && **pvp == CANONUSER)
		pvp++;
E 68
E 66
	while (*pvp != NULL && (i = strlen(*pvp)) < sz)
	{
D 69
		natomtok = (toktype(**pvp) == ATOM);
E 69
I 69
D 277
		natomtok = (toktype(**pvp) == ATM);
E 277
I 277
		natomtok = (TokTypeTab[**pvp & 0xff] == ATM);
E 277
E 69
		if (oatomtok && natomtok)
D 79
			*p++ = SPACESUB;
E 79
I 79
D 164
			*p++ = SpaceSub;
E 164
I 164
			*p++ = spacesub;
E 164
E 79
		(void) strcpy(p, *pvp);
		oatomtok = natomtok;
		p += i;
D 92
		sz -= i;
E 92
I 92
		sz -= i + 1;
E 92
D 179
		pvp++;
E 179
I 179
		if (pvp++ == evp)
			break;
E 179
	}
	*p = '\0';
E 33
I 20
}
/*
**  SAMEADDR -- Determine if two addresses are the same
**
**	This is not just a straight comparison -- if the mailer doesn't
**	care about the host we just ignore it, etc.
**
**	Parameters:
**		a, b -- pointers to the internal forms to compare.
D 83
**		wildflg -- if TRUE, 'a' may have no user specified,
**			in which case it is to match anything.
E 83
**
**	Returns:
**		TRUE -- they represent the same mailbox.
**		FALSE -- they don't.
**
**	Side Effects:
**		none.
*/

bool
D 83
sameaddr(a, b, wildflg)
E 83
I 83
sameaddr(a, b)
E 83
	register ADDRESS *a;
	register ADDRESS *b;
D 83
	bool wildflg;
E 83
{
I 236
	register ADDRESS *ca, *cb;

E 236
	/* if they don't have the same mailer, forget it */
	if (a->q_mailer != b->q_mailer)
		return (FALSE);

	/* if the user isn't the same, we can drop out */
D 83
	if ((!wildflg || a->q_user[0] != '\0') && strcmp(a->q_user, b->q_user) != 0)
E 83
I 83
D 138
	if (strcmp(a->q_user, b->q_user) != 0)
E 138
I 138
	if (strcasecmp(a->q_user, b->q_user))
E 138
E 83
		return (FALSE);

I 170
D 236
	/* if we have good uids for both but the differ, these are different */
	if (bitset(QGOODUID, a->q_flags & b->q_flags) && a->q_uid != b->q_uid)
E 236
I 236
	/* if we have good uids for both but they differ, these are different */
D 239
	ca = getctladdr(a);
	cb = getctladdr(b);
D 237
	if (bitset(QGOODUID, ca->q_flags & cb->q_flags) &&
E 237
I 237
	if (ca != NULL && cb != NULL &&
	    bitset(QGOODUID, ca->q_flags & cb->q_flags) &&
E 237
	    ca->q_uid != cb->q_uid)
E 236
		return (FALSE);
E 239
I 239
	if (a->q_mailer == ProgMailer)
	{
		ca = getctladdr(a);
		cb = getctladdr(b);
		if (ca != NULL && cb != NULL &&
		    bitset(QGOODUID, ca->q_flags & cb->q_flags) &&
		    ca->q_uid != cb->q_uid)
			return (FALSE);
	}
E 239

E 170
I 120
D 122
	/* if receiving uid's don't match, these are "different" */
D 121
	if (a->q_uid != b->q_uid || a->q_gid != b->q_gid)
E 121
I 121
	if (bitset(QGOODUID, a->q_flags) && bitset(QGOODUID, b->q_flags) &&
	    (a->q_uid != b->q_uid || a->q_gid != b->q_gid))
E 121
		return (FALSE);

E 122
E 120
D 171
	/* if the mailer ignores hosts, we have succeeded! */
D 31
	if (bitset(M_NOHOST, Mailer[a->q_mailer]->m_flags))
E 31
I 31
D 45
	if (bitset(M_LOCAL, Mailer[a->q_mailer]->m_flags))
E 45
I 45
D 91
	if (bitset(M_LOCAL, a->q_mailer->m_flags))
E 91
I 91
D 165
	if (bitnset(M_LOCAL, a->q_mailer->m_flags))
E 165
I 165
	if (bitnset(M_LOCALMAILER, a->q_mailer->m_flags))
E 165
E 91
E 45
E 31
		return (TRUE);

E 171
	/* otherwise compare hosts (but be careful for NULL ptrs) */
I 171
	if (a->q_host == b->q_host)
	{
		/* probably both null pointers */
		return (TRUE);
	}
E 171
	if (a->q_host == NULL || b->q_host == NULL)
I 171
	{
		/* only one is a null pointer */
E 171
		return (FALSE);
I 171
	}
E 171
D 138
	if (strcmp(a->q_host, b->q_host) != 0)
E 138
I 138
	if (strcasecmp(a->q_host, b->q_host))
E 138
		return (FALSE);

	return (TRUE);
E 20
E 18
}
I 21
/*
**  PRINTADDR -- print address (for debugging)
**
**	Parameters:
**		a -- the address to print
**		follow -- follow the q_next chain.
**
**	Returns:
**		none.
**
**	Side Effects:
**		none.
*/

I 257
struct qflags
{
	char	*qf_name;
	u_long	qf_bit;
};

struct qflags	AddressFlags[] =
{
	"QDONTSEND",		QDONTSEND,
	"QBADADDR",		QBADADDR,
	"QGOODUID",		QGOODUID,
	"QPRIMARY",		QPRIMARY,
	"QQUEUEUP",		QQUEUEUP,
	"QSENT",		QSENT,
	"QNOTREMOTE",		QNOTREMOTE,
	"QSELFREF",		QSELFREF,
	"QVERIFIED",		QVERIFIED,
D 281
	"QREPORT",		QREPORT,
E 281
	"QBOGUSSHELL",		QBOGUSSHELL,
	"QUNSAFEADDR",		QUNSAFEADDR,
	"QPINGONSUCCESS",	QPINGONSUCCESS,
	"QPINGONFAILURE",	QPINGONFAILURE,
	"QPINGONDELAY",		QPINGONDELAY,
I 273
	"QHASNOTIFY",		QHASNOTIFY,
E 273
D 272
	"QHAS_RET_PARAM",	QHAS_RET_PARAM,
	"QRET_HDRS",		QRET_HDRS,
E 272
	"QRELAYED",		QRELAYED,
I 274
D 281
	"QEXPLODED",		QEXPLODED,
E 281
I 281
	"QEXPANDED",		QEXPANDED,
	"QDELIVERED",		QDELIVERED,
	"QDELAYED",		QDELAYED,
E 281
	"QTHISPASS",		QTHISPASS,
E 274
	NULL
};

I 266
void
E 266
E 257
I 138
void
E 138
I 36
D 126
# ifdef DEBUG

E 126
E 36
printaddr(a, follow)
	register ADDRESS *a;
	bool follow;
{
I 50
D 257
	bool first = TRUE;
E 257
I 157
	register MAILER *m;
	MAILER pseudomailer;
I 257
	register struct qflags *qfp;
	bool firstone;
E 257
E 157

I 257
	if (a == NULL)
	{
		printf("[NULL]\n");
		return;
	}

E 257
E 50
I 48
	static int indent;
	register int i;

E 48
	while (a != NULL)
	{
I 50
D 257
		first = FALSE;
E 257
E 50
I 48
		for (i = indent; i > 0; i--)
			printf("\t");
E 48
D 40
		printf("addr@%x: ", a);
E 40
I 40
		printf("%x=", a);
E 40
D 28
		fflush(stdout);
E 28
I 28
		(void) fflush(stdout);
I 157

		/* find the mailer -- carefully */
		m = a->q_mailer;
		if (m == NULL)
		{
			m = &pseudomailer;
			m->m_mno = -1;
			m->m_name = "NULL";
		}

E 157
E 28
D 128
		printf("%s: mailer %d (%s), host `%s', user `%s'\n", a->q_paddr,
D 45
		       a->q_mailer, Mailer[a->q_mailer]->m_name, a->q_host, a->q_user);
E 45
I 45
D 71
		       a->q_mailer->m_mno, a->q_mailer->m_name, a->q_host, a->q_user);
E 45
D 40
		printf("\tnext=%x flags=%o, rmailer %d\n", a->q_next,
E 40
I 40
D 48
D 51
		printf("\tnext=%x, flags=%o, rmailer %d\n", a->q_next,
E 40
		       a->q_flags, a->q_rmailer);
E 51
I 51
		printf("\tnext=%x, flags=%o, rmailer %d, alias %x\n", a->q_next,
		       a->q_flags, a->q_rmailer, a->q_alias);
E 51
I 50
		printf("\thome=\"%s\", fullname=\"%s\"\n", a->q_home, a->q_fullname);
E 71
I 71
		       a->q_mailer->m_mno, a->q_mailer->m_name, a->q_host,
		       a->q_user);
E 128
I 128
D 175
		printf("%s: mailer %d (%s), host `%s', user `%s', ruser `%s'\n",
E 175
I 175
D 274
		printf("%s:\n\tmailer %d (%s), host `%s', user `%s', ruser `%s'\n",
E 274
I 274
		printf("%s:\n\tmailer %d (%s), host `%s'\n",
E 274
E 175
D 157
		       a->q_paddr, a->q_mailer->m_mno, a->q_mailer->m_name,
E 157
I 157
		       a->q_paddr, m->m_mno, m->m_name,
E 157
D 214
		       a->q_host, a->q_user, a->q_ruser? a->q_ruser: "<null>");
E 214
I 214
D 244
		       a->q_host, a->q_user,
		       a->q_ruser ? a->q_ruser : "<null>");
E 244
I 244
D 274
		       a->q_host == NULL ? "<null>" : a->q_host, a->q_user,
E 274
I 274
		       a->q_host == NULL ? "<null>" : a->q_host);
		printf("\tuser `%s', ruser `%s'\n",
		       a->q_user,
E 274
		       a->q_ruser == NULL ? "<null>" : a->q_ruser);
E 244
E 214
E 128
D 190
		printf("\tnext=%x, flags=%o, alias %x\n", a->q_next, a->q_flags,
		       a->q_alias);
		printf("\thome=\"%s\", fullname=\"%s\"\n", a->q_home,
		       a->q_fullname);
E 190
I 190
D 247
		printf("\tnext=%x, flags=%o, alias %x, uid %d, gid %d\n",
E 247
I 247
D 257
		printf("\tnext=%x, flags=%x, alias %x, uid %d, gid %d\n",
E 247
		       a->q_next, a->q_flags, a->q_alias, a->q_uid, a->q_gid);
E 257
I 257
		printf("\tnext=%x, alias %x, uid %d, gid %d\n",
		       a->q_next, a->q_alias, a->q_uid, a->q_gid);
		printf("\tflags=%lx<", a->q_flags);
		firstone = TRUE;
		for (qfp = AddressFlags; qfp->qf_name != NULL; qfp++)
		{
			if (!bitset(qfp->qf_bit, a->q_flags))
				continue;
			if (!firstone)
				printf(",");
			firstone = FALSE;
			printf("%s", qfp->qf_name);
		}
		printf(">\n");
E 257
		printf("\towner=%s, home=\"%s\", fullname=\"%s\"\n",
		       a->q_owner == NULL ? "(none)" : a->q_owner,
D 214
		       a->q_home, a->q_fullname);
E 214
I 214
		       a->q_home == NULL ? "(none)" : a->q_home,
		       a->q_fullname == NULL ? "(none)" : a->q_fullname);
I 255
D 256
		printf("\torcpt=\"%s\", statmta=%s, status=%s\n",
E 256
I 256
D 261
		printf("\torcpt=\"%s\", statmta=%s, fstatus=%s, rstatus=%s\n",
E 261
I 261
		printf("\torcpt=\"%s\", statmta=%s, rstatus=%s\n",
E 261
E 256
		       a->q_orcpt == NULL ? "(none)" : a->q_orcpt,
		       a->q_statmta == NULL ? "(none)" : a->q_statmta,
D 256
		       a->q_status == NULL ? "(none)" : a->q_status);
E 256
I 256
D 261
		       a->q_fstatus == NULL ? "(none)" : a->q_fstatus,
E 261
		       a->q_rstatus == NULL ? "(none)" : a->q_rstatus);
E 256
E 255
E 214
E 190
E 71
E 50

E 48
I 48
		for (i = indent; i > 0; i--)
			printf("\t");
		printf("\tnext=%x, flags=%o, rmailer %d, alias=%x, sibling=%x, child=%x\n",
		       a->q_next, a->q_flags, a->q_rmailer, a->q_alias,
		       a->q_sibling, a->q_child);
		
		/* follow the chain if appropriate */
E 48
		if (!follow)
			return;
D 48
		a = a->q_next;
E 48
I 48
		
		indent++;
		printaddr(a->q_child, TRUE);
		indent--;
		a = a->q_sibling;
E 48
	}
I 40
D 50
	if (!follow)
E 50
I 50
D 257
	if (first)
E 50
		printf("[NULL]\n");
E 257
E 40
}
I 252
/*
**  EMPTYADDR -- return TRUE if this address is empty (``<>'')
**
**	Parameters:
**		a -- pointer to the address
**
**	Returns:
**		TRUE -- if this address is "empty" (i.e., no one should
**			ever generate replies to it.
**		FALSE -- if it is a "regular" (read: replyable) address.
*/
E 252
I 36

I 252
bool
emptyaddr(a)
	register ADDRESS *a;
{
	return strcmp(a->q_paddr, "<>") == 0 || strcmp(a->q_user, "<>") == 0;
}
E 252
D 126
# endif DEBUG
E 126
I 61
/*
**  REMOTENAME -- return the name relative to the current mailer
**
**	Parameters:
**		name -- the name to translate.
D 68
**		force -- if set, forces rewriting even if the mailer
**			does not request it.  Used for rewriting
**			sender addresses.
E 68
I 68
**		m -- the mailer that we want to do rewriting relative
**			to.
D 189
**		senderaddress -- if set, uses the sender rewriting rules
**			rather than the recipient rewriting rules.
I 160
**		header -- set if this address is in the header, rather
**			than an envelope header.
E 160
I 90
**		canonical -- if set, strip out any comment information,
**			etc.
I 171
**		adddomain -- if set, OK to do domain extension.
E 189
I 189
**		flags -- fine tune operations.
**		pstat -- pointer to status word.
E 189
E 171
I 160
**		e -- the current envelope.
E 160
I 138
D 139
**		headeraddress -- if set, use header specific rewriting
**			rulesets and uurelativize if M_RELATIVIZE is set.
E 139
E 138
E 90
E 68
**
**	Returns:
**		the text string representing this address relative to
**			the receiving mailer.
**
**	Side Effects:
**		none.
**
**	Warnings:
**		The text string returned is tucked away locally;
**			copy it if you intend to save it.
*/

char *
D 68
remotename(name, m, force)
E 68
I 68
D 90
remotename(name, m, senderaddress)
E 90
I 90
D 136
D 138
remotename(name, m, senderaddress, canonical)
E 138
I 138
D 139
remotename(name, m, senderaddress, canonical, headeraddress)
E 139
I 139
remotename(name, m, senderaddress, canonical)
E 139
E 138
E 136
I 136
D 160
remotename(name, m, senderaddress, canonical, e)
E 160
I 160
D 171
remotename(name, m, senderaddress, header, canonical, e)
E 171
I 171
D 189
remotename(name, m, senderaddress, header, canonical, adddomain, e)
E 189
I 189
remotename(name, m, flags, pstat, e)
E 189
E 171
E 160
E 136
E 90
E 68
	char *name;
D 138
	struct mailer *m;
E 138
I 138
	MAILER *m;
E 138
D 68
	bool force;
E 68
I 68
D 189
	bool senderaddress;
I 160
	bool header;
E 160
I 90
	bool canonical;
I 171
	bool adddomain;
E 189
I 189
	int flags;
	int *pstat;
E 189
E 171
I 138
D 139
	bool headeraddress;
E 139
E 138
I 136
	register ENVELOPE *e;
E 136
E 90
E 68
{
D 68
	static char buf[MAXNAME];
	char lbuf[MAXNAME];
E 68
I 68
	register char **pvp;
	char *fancy;
I 100
D 114
	register char *p;
E 114
E 100
E 68
D 138
D 204
	extern char *macvalue();
E 204
E 138
D 68
	char *oldf = macvalue('f');
E 68
D 64
	char *oldx = macvalue('x');
E 64
D 71
	char *oldg = macvalue('g');
E 71
I 71
D 136
	char *oldg = macvalue('g', CurEnv);
E 136
I 136
	char *oldg = macvalue('g', e);
I 160
	int rwset;
E 160
E 136
E 71
I 68
D 269
	static char buf[MAXNAME];
	char lbuf[MAXNAME];
E 269
I 269
	static char buf[MAXNAME + 1];
	char lbuf[MAXNAME + 1];
E 269
I 107
	char pvpbuf[PSBUFSIZE];
E 107
E 68
D 138
D 204
	extern char **prescan();
E 204
D 68
	register char **pvp;
D 64
	extern char *getxpart();
E 64
	extern ADDRESS *buildaddr();
E 68
I 64
	extern char *crackaddr();
E 138
D 68
	char *fancy;
E 68
E 64

I 62
D 126
# ifdef DEBUG
E 126
	if (tTd(12, 1))
		printf("remotename(%s)\n", name);
D 126
# endif DEBUG
E 126

I 88
	/* don't do anything if we are tagging it as special */
D 138
D 160
	if ((senderaddress ? m->m_s_rwset : m->m_r_rwset) < 0)
E 160
I 160
D 189
	if (senderaddress)
		rwset = header ? m->m_sh_rwset : m->m_se_rwset;
E 189
I 189
	if (bitset(RF_SENDERADDR, flags))
		rwset = bitset(RF_HEADERADDR, flags) ? m->m_sh_rwset
						     : m->m_se_rwset;
E 189
	else
D 189
		rwset = header ? m->m_rh_rwset : m->m_re_rwset;
E 189
I 189
		rwset = bitset(RF_HEADERADDR, flags) ? m->m_rh_rwset
						     : m->m_re_rwset;
E 189
	if (rwset < 0)
E 160
E 138
I 138
D 139
	if ((senderaddress ?
	     (headeraddress ? m->m_sh_rwset : m->m_se_rwset) :
	     (headeraddress ? m->m_rh_rwset : m->m_re_rwset)) < 0)
E 139
I 139
	if ((senderaddress ? m->m_s_rwset : m->m_r_rwset) < 0)
E 139
E 138
		return (name);

E 88
E 62
	/*
D 64
	**  See if this mailer wants the name to be rewritten.  There are
	**  many problems here, owing to the standards for doing replies.
	**  In general, these names should only be rewritten if we are
	**  sending to another host that runs sendmail.
E 64
I 64
D 71
	**  First put this address into canonical form.
	**	First turn it into a macro.
D 68
	**	Then run it through ruleset 4.
E 68
I 68
	**	Then run it through ruleset 1 or 2, depending on whether
	**		it is a sender or a recipient address.
E 68
I 67
	**	If the mailer defines a rewriting set, run it through
	**		there next.
E 71
I 71
	**  Do a heuristic crack of this name to extract any comment info.
	**	This will leave the name as a comment and a $g macro.
E 71
D 68
	**	The intent is that ruleset 4 puts the name into a
	**		canonical form; the mailer's ruleset then
	**		does any customization.
E 68
E 67
E 64
	*/

D 64
	if (!bitset(M_RELRCPT, m->m_flags) && !force)
I 62
	{
# ifdef DEBUG
		if (tTd(12, 1))
			printf("remotename [ditto]\n");
# endif DEBUG
E 64
I 64
D 71
	/* save away the extraneous pretty stuff */
E 71
D 90
	fancy = crackaddr(name);
E 90
I 90
D 161
	if (canonical)
E 161
I 161
D 189
	if (canonical || bitnset(M_NOCOMMENT, m->m_flags))
E 189
I 189
	if (bitset(RF_CANONICAL, flags) || bitnset(M_NOCOMMENT, m->m_flags))
E 189
E 161
D 101
		fancy = "$g";
E 101
I 101
D 162
		fancy = "\001g";
E 162
I 162
		fancy = "\201g";
E 162
E 101
	else
		fancy = crackaddr(name);
E 90

D 71
	/* now run through ruleset four */
E 71
I 71
	/*
	**  Turn the name into canonical form.
	**	Normally this will be RFC 822 style, i.e., "user@domain".
	**	If this only resolves to "user", and the "C" flag is
	**	specified in the sending mailer, then the sender's
	**	domain will be appended.
	*/

E 71
D 107
	pvp = prescan(name, '\0');
E 107
I 107
D 168
	pvp = prescan(name, '\0', pvpbuf);
E 168
I 168
D 233
	pvp = prescan(name, '\0', pvpbuf, NULL);
E 233
I 233
D 277
	pvp = prescan(name, '\0', pvpbuf, sizeof pvpbuf, NULL);
E 277
I 277
	pvp = prescan(name, '\0', pvpbuf, sizeof pvpbuf, NULL, NULL);
E 277
E 233
E 168
E 107
	if (pvp == NULL)
E 64
E 62
		return (name);
I 71
D 184
	rewrite(pvp, 3);
E 184
I 184
D 186
	rewrite(pvp, 3, e);
E 186
I 186
D 189
	(void) rewrite(pvp, 3, e);
E 186
E 184
D 136
	if (CurEnv->e_fromdomain != NULL)
E 136
I 136
D 171
	if (e->e_fromdomain != NULL)
E 171
I 171
	if (adddomain && e->e_fromdomain != NULL)
E 189
I 189
D 234
	if (rewrite(pvp, 3, e) == EX_TEMPFAIL)
E 234
I 234
	if (rewrite(pvp, 3, 0, e) == EX_TEMPFAIL)
E 234
		*pstat = EX_TEMPFAIL;
	if (bitset(RF_ADDDOMAIN, flags) && e->e_fromdomain != NULL)
E 189
E 171
E 136
	{
		/* append from domain to this address */
		register char **pxp = pvp;

I 85
		/* see if there is an "@domain" in the current name */
E 85
		while (*pxp != NULL && strcmp(*pxp, "@") != 0)
			pxp++;
		if (*pxp == NULL)
		{
I 85
			/* no.... append the "@domain" from the sender */
E 85
D 136
			register char **qxq = CurEnv->e_fromdomain;
E 136
I 136
			register char **qxq = e->e_fromdomain;
E 136

D 85
			while (*qxq != NULL)
				*pxp++ = *qxq++;
E 85
I 85
			while ((*pxp++ = *qxq++) != NULL)
				continue;
I 97
D 184
			rewrite(pvp, 3);
E 184
I 184
D 186
			rewrite(pvp, 3, e);
E 186
I 186
D 189
			(void) rewrite(pvp, 3, e);
E 189
I 189
D 234
			if (rewrite(pvp, 3, e) == EX_TEMPFAIL)
E 234
I 234
			if (rewrite(pvp, 3, 0, e) == EX_TEMPFAIL)
E 234
				*pstat = EX_TEMPFAIL;
E 189
E 186
E 184
E 97
E 85
		}
	}

	/*
D 78
	**  Now do more specific rewriting.
E 78
I 78
	**  Do more specific rewriting.
E 78
D 138
	**	Rewrite using ruleset 1 or 2 depending on whether this is
	**		a sender address or not.
E 138
I 138
	**	Rewrite using ruleset 1 or 2 for envelope addresses and
	**	5 or 6 for header addresses depending on whether this
	**	is a sender address or not.
E 138
	**	Then run it through any receiving-mailer-specific rulesets.
	*/

E 71
I 62
D 64
	}
E 64
I 64
D 68
	rewrite(pvp, 4);
I 67
	if (m->m_rwset > 0)
		rewrite(pvp, m->m_rwset);
E 67
E 64
E 62

	/*
D 64
	**  Do general rewriting of name.
	**	This will also take care of doing global name translation.
E 64
I 64
	**  See if this mailer wants the name to be rewritten.  There are
	**  many problems here, owing to the standards for doing replies.
	**  In general, these names should only be rewritten if we are
	**  sending to another host that runs sendmail.
E 64
	*/

D 64
	define('x', getxpart(name));
	pvp = prescan(name, '\0');
	if (pvp == NULL)
		return (name);
	rewrite(pvp, 1);
	rewrite(pvp, 3);
	if (**pvp == CANONNET)
E 64
I 64
	if (bitset(M_RELRCPT, m->m_flags) && !force)
E 68
I 68
D 189
	if (senderaddress)
E 68
E 64
D 160
	{
E 160
D 64
		/* oops... resolved to something */
		return (name);
	}
	cataddr(pvp, lbuf, sizeof lbuf);
E 64
I 64
D 68
		/*
		**  Do general rewriting of name.
		**	This will also take care of doing global name
		**	translation.
		*/
E 64

E 68
D 64
	/* make the name relative to the receiving mailer */
	define('f', lbuf);
	expand(m->m_from, buf, &buf[sizeof buf - 1], CurEnv);
E 64
I 64
D 138
D 184
		rewrite(pvp, 1);
E 184
I 184
D 186
		rewrite(pvp, 1, e);
E 186
I 186
		(void) rewrite(pvp, 1, e);
E 189
I 189
	if (bitset(RF_SENDERADDR, flags))
I 193
	{
E 193
D 234
		if (rewrite(pvp, 1, e) == EX_TEMPFAIL)
E 234
I 234
		if (rewrite(pvp, 1, 0, e) == EX_TEMPFAIL)
E 234
			*pstat = EX_TEMPFAIL;
I 193
	}
E 193
E 189
E 186
E 184
D 68
		rewrite(pvp, 3);
E 64

D 64
	/* rewrite to get rid of garbage we added in the expand above */
	pvp = prescan(buf, '\0');
	if (pvp == NULL)
		return (name);
	rewrite(pvp, 2);
	cataddr(pvp, lbuf, sizeof lbuf);
E 64
I 64
		/* make the name relative to the receiving mailer */
		cataddr(pvp, lbuf, sizeof lbuf);
		define('f', lbuf);
		expand(m->m_from, buf, &buf[sizeof buf - 1], CurEnv);
E 64

I 64
		/* rewrite to get rid of garbage we added in the expand above */
		pvp = prescan(buf, '\0');
		if (pvp == NULL)
			return (name);
E 68
I 68
D 160
		if (m->m_s_rwset > 0)
			rewrite(pvp, m->m_s_rwset);
E 138
I 138
D 139
		if (headeraddress)
		{
			rewrite(pvp, SplitRewriting ? 5 : 1);
			if (m->m_sh_rwset > 0)
				rewrite(pvp, m->m_sh_rwset);
		}
		else
		{
			rewrite(pvp, 1);
			if (m->m_se_rwset > 0)
				rewrite(pvp, m->m_se_rwset);
		}
E 139
I 139
		rewrite(pvp, 1);
		if (m->m_s_rwset > 0)
			rewrite(pvp, m->m_s_rwset);
E 139
E 138
	}
E 160
	else
I 193
	{
E 193
D 160
	{
E 160
E 68
D 138
D 184
		rewrite(pvp, 2);
E 184
I 184
D 186
		rewrite(pvp, 2, e);
E 186
I 186
D 189
		(void) rewrite(pvp, 2, e);
E 189
I 189
D 234
		if (rewrite(pvp, 2, e) == EX_TEMPFAIL)
E 234
I 234
		if (rewrite(pvp, 2, 0, e) == EX_TEMPFAIL)
E 234
			*pstat = EX_TEMPFAIL;
I 193
	}
E 193
E 189
E 186
E 184
I 68
D 160
		if (m->m_r_rwset > 0)
			rewrite(pvp, m->m_r_rwset);
E 138
I 138
D 139
		if (headeraddress)
		{
			rewrite(pvp, SplitRewriting ? 6 : 2);
			if (m->m_rh_rwset > 0)
				rewrite(pvp, m->m_rh_rwset);
		}
		else
		{
			rewrite(pvp, 2);
			if (m->m_re_rwset > 0)
				rewrite(pvp, m->m_re_rwset);
		}
E 139
I 139
		rewrite(pvp, 2);
		if (m->m_r_rwset > 0)
			rewrite(pvp, m->m_r_rwset);
E 139
E 138
E 68
	}
E 160
I 160
	if (rwset > 0)
I 193
	{
E 193
D 184
		rewrite(pvp, rwset);
E 184
I 184
D 186
		rewrite(pvp, rwset, e);
E 186
I 186
D 189
		(void) rewrite(pvp, rwset, e);
E 189
I 189
D 234
		if (rewrite(pvp, rwset, e) == EX_TEMPFAIL)
E 234
I 234
		if (rewrite(pvp, rwset, 0, e) == EX_TEMPFAIL)
E 234
			*pstat = EX_TEMPFAIL;
I 193
	}
E 193
E 189
E 186
E 184
E 160
I 78

	/*
	**  Do any final sanitation the address may require.
	**	This will normally be used to turn internal forms
	**	(e.g., user@host.LOCAL) into external form.  This
	**	may be used as a default to the above rules.
	*/

D 184
	rewrite(pvp, 4);
E 184
I 184
D 186
	rewrite(pvp, 4, e);
E 186
I 186
D 189
	(void) rewrite(pvp, 4, e);
E 189
I 189
D 234
	if (rewrite(pvp, 4, e) == EX_TEMPFAIL)
E 234
I 234
	if (rewrite(pvp, 4, 0, e) == EX_TEMPFAIL)
E 234
		*pstat = EX_TEMPFAIL;
E 189
E 186
E 184
E 78
D 139

E 64
D 71
	/* now add any comment info we had before back */
E 71
I 71
	/*
I 138
	**  Check if we're supposed to do make the address
	**  UUCP !-relative to the rcpt host vs ourselves.
	*/

	if (headeraddress && bitnset(M_RELATIVIZE, m->m_flags))
		uurelativize("\001k", "\001h", pvp);
E 139

	/*
E 138
	**  Now restore the comment information we had at the beginning.
I 100
D 101
	**	Make sure that any real '$' characters in the input are
	**	not accidently interpreted as macro expansions by quoting
	**	them before expansion.
E 101
E 100
	*/

E 71
I 64
D 164
	cataddr(pvp, lbuf, sizeof lbuf);
E 164
I 164
D 180
	cataddr(pvp, lbuf, sizeof lbuf, '\0');
E 180
I 180
	cataddr(pvp, NULL, lbuf, sizeof lbuf, '\0');
E 180
E 164
I 100
D 101
	for (p = lbuf; *p != '\0'; p++)
		if (*p == '$')
			*p |= 0200;
E 101
E 100
E 64
D 83
	define('g', lbuf);
E 83
I 83
D 136
	define('g', lbuf, CurEnv);
E 83
D 64
	expand("$q", buf, &buf[sizeof buf - 1], CurEnv);
E 64
I 64
	expand(fancy, buf, &buf[sizeof buf - 1], CurEnv);
E 64
D 68

	define('f', oldf);
E 68
D 83
	define('g', oldg);
E 83
I 83
	define('g', oldg, CurEnv);
E 136
I 136
	define('g', lbuf, e);
D 241
	expand(fancy, buf, &buf[sizeof buf - 1], e);
E 241
I 241

	/* need to make sure route-addrs have <angle brackets> */
	if (bitset(RF_CANONICAL, flags) && lbuf[0] == '@')
D 269
		expand("<\201g>", buf, &buf[sizeof buf - 1], e);
E 269
I 269
D 270
		expand("<\201g>", buf, &buf[sizeof buf], e);
E 270
I 270
		expand("<\201g>", buf, sizeof buf, e);
E 270
E 269
	else
D 269
		expand(fancy, buf, &buf[sizeof buf - 1], e);
E 269
I 269
D 270
		expand(fancy, buf, &buf[sizeof buf], e);
E 270
I 270
		expand(fancy, buf, sizeof buf, e);
E 270
E 269

E 241
	define('g', oldg, e);
E 136
I 100
D 101
	stripquotes(buf, FALSE);
E 101
E 100
E 83
D 64
	define('x', oldx);
E 64

D 126
# ifdef DEBUG
E 126
	if (tTd(12, 1))
D 62
		printf("remotename(%s) => `%s'\n", name, buf);
E 62
I 62
		printf("remotename => `%s'\n", buf);
E 62
D 126
# endif DEBUG
E 126
	return (buf);
I 138
}
/*
**  UURELATIVIZE -- Make an address !-relative to recipient/sender nodes
**
**	Parameters:
**		from -- the sending node (usually "$k" or "$w")
**		to -- the receiving node (usually "$h")
**		pvp -- address vector
**
**	Returns:
**		none.
**
**	Side Effects:
**		The pvp is rewritten to be relative the "to" node
**		wrt the "from" node.  In other words, if the pvp
**		is headed by "to!" that part is stripped; otherwise
**		"from!" is prepended.  Exception: "to!user" addresses
**		with no '!'s in the user part are sent as is.
**
**	Bugs:
**		The pvp may overflow, but we don't catch it.
*/

static void
uurelativize(from, to, pvp)
	const char *from, *to;
	char **pvp;
{
	register char **pxp = pvp;
	char expfrom[MAXNAME], expto[MAXNAME];

	expand(from, expfrom, &expfrom[sizeof expfrom - 1], CurEnv);
	expand(to, expto, &expto[sizeof expto - 1], CurEnv);

	/*
	 * supposing that we've got something, should
	 * we add "from!" or remove "to!"?
	 */
	if (pvp[0] != NULL)
		if (pvp[1] == NULL || strcmp(pvp[1], "!") != 0 ||
		    /*strcasecmp?*/ strcmp(pvp[0], expto) != 0)
		{
			/* either local name, no UUCP address, */
			/* or not to "to!" ==> prepend address with "from!" */

			/* already there? */
			if (pvp[1] == NULL || strcmp(pvp[1], "!") != 0 ||
			    /*strcasecmp?*/ strcmp(pvp[0], expfrom) != 0)
			{

				/* no, put it there */
				while (*pxp != NULL)
					pxp++;
				do
					pxp[2] = *pxp;
				while (pxp-- != pvp);
				pvp[0] = newstr(expfrom);
				pvp[1] = "!";
			}
		}
		else
		{
			/* address is to "to!" -- remove if not "to!user" */
			for (pxp = &pvp[2];
			     *pxp != NULL && strcmp(*pxp, "!") != 0; pxp++)
				;
			if (*pxp != NULL)
				for (pxp = pvp; *pxp != NULL; pxp++)
					*pxp = pxp[2];
		}
E 138
I 130
}
/*
**  MAPLOCALUSER -- run local username through ruleset 5 for final redirection
**
**	Parameters:
**		a -- the address to map (but just the user name part).
**		sendq -- the sendq in which to install any replacement
**			addresses.
I 254
**		aliaslevel -- the alias nesting depth.
**		e -- the envelope.
E 254
**
**	Returns:
**		none.
*/

I 284
void
E 284
D 136
maplocaluser(a, sendq)
E 136
I 136
D 254
maplocaluser(a, sendq, e)
E 254
I 254
maplocaluser(a, sendq, aliaslevel, e)
E 254
E 136
	register ADDRESS *a;
	ADDRESS **sendq;
I 254
	int aliaslevel;
E 254
I 136
	ENVELOPE *e;
E 136
{
	register char **pvp;
	register ADDRESS *a1 = NULL;
I 168
	auto char *delimptr;
E 168
	char pvpbuf[PSBUFSIZE];

	if (tTd(29, 1))
	{
		printf("maplocaluser: ");
		printaddr(a, FALSE);
	}
D 168
	pvp = prescan(a->q_user, '\0', pvpbuf);
E 168
I 168
D 233
	pvp = prescan(a->q_user, '\0', pvpbuf, &delimptr);
E 233
I 233
D 277
	pvp = prescan(a->q_user, '\0', pvpbuf, sizeof pvpbuf, &delimptr);
E 277
I 277
	pvp = prescan(a->q_user, '\0', pvpbuf, sizeof pvpbuf, &delimptr, NULL);
E 277
E 233
E 168
	if (pvp == NULL)
		return;

D 184
	rewrite(pvp, 5);
E 184
I 184
D 186
	rewrite(pvp, 5, e);
E 186
I 186
D 234
	(void) rewrite(pvp, 5, e);
E 234
I 234
	(void) rewrite(pvp, 5, 0, e);
E 234
E 186
E 184
D 162
	if (pvp[0] == NULL || pvp[0][0] != CANONNET)
E 162
I 162
	if (pvp[0] == NULL || (pvp[0][0] & 0377) != CANONNET)
E 162
		return;

	/* if non-null, mailer destination specified -- has it changed? */
D 183
	a1 = buildaddr(pvp, NULL);
E 183
I 183
D 218
	a1 = buildaddr(pvp, NULL, e);
E 218
I 218
	a1 = buildaddr(pvp, NULL, 0, e);
E 218
E 183
	if (a1 == NULL || sameaddr(a, a1))
		return;

	/* mark old address as dead; insert new address */
	a->q_flags |= QDONTSEND;
I 157
	if (tTd(29, 5))
	{
		printf("maplocaluser: QDONTSEND ");
		printaddr(a, FALSE);
	}
E 157
	a1->q_alias = a;
D 168
	allocaddr(a1, 1, NULL);
E 168
I 168
D 218
	allocaddr(a1, 1, NULL, delimptr);
E 218
I 218
D 220
	allocaddr(a1, RF_COPYALL, NULL, delimptr);
E 220
I 220
	allocaddr(a1, RF_COPYALL, NULL);
E 220
E 218
E 168
D 136
	(void) recipient(a1, sendq);
E 136
I 136
D 254
	(void) recipient(a1, sendq, e);
E 254
I 254
	(void) recipient(a1, sendq, aliaslevel, e);
E 254
E 136
E 130
D 90
}
/*
**  CANONNAME -- make name canonical
**
**	This is used for SMTP and misc. printing.  Given a print
D 71
**	address, it strips out comments, etc., and puts on exactly
**	one set of brackets.
E 71
I 71
**	address, it strips out comments, etc.
E 71
**
**	Parameters:
**		name -- the name to make canonical.
I 75
**		ruleset -- the canonicalizing ruleset.
E 75
**
**	Returns:
**		pointer to canonical name.
**
**	Side Effects:
**		none.
**
**	Warning:
**		result is saved in static buf; future calls will trash it.
*/

char *
D 75
canonname(name)
E 75
I 75
canonname(name, ruleset)
E 75
	char *name;
I 75
	int ruleset;
E 75
{
D 68
	static char nbuf[MAXNAME + 2];
E 68
I 68
	static char nbuf[MAXNAME];
E 68
I 65
	register char **pvp;
E 65

D 65
	if (name[0] == '<')
		return (name);
	strcpy(nbuf, "<");
	strcat(nbuf, name);
E 65
I 65
	pvp = prescan(name, '\0');
D 68
	rewrite(pvp, 4);
	cataddr(pvp, nbuf + 1, MAXNAME);
	nbuf[0] = '<';
E 65
	strcat(nbuf, ">");
E 68
I 68
	rewrite(pvp, 3);
I 75
	rewrite(pvp, ruleset);
I 87
	rewrite(pvp, 4);
E 87
E 75
	cataddr(pvp, nbuf, sizeof nbuf);
E 68
	return (nbuf);
E 90
}
I 177
/*
**  DEQUOTE_INIT -- initialize dequote map
**
**	This is a no-op.
**
**	Parameters:
**		map -- the internal map structure.
D 203
**		mapname -- the name of the mapl.
E 203
**		args -- arguments.
**
**	Returns:
**		TRUE.
*/

bool
D 203
dequote_init(map, mapname, args)
E 203
I 203
dequote_init(map, args)
E 203
	MAP *map;
D 203
	char *mapname;
E 203
	char *args;
{
I 178
	register char *p = args;

I 286
	map->map_mflags |= MF_KEEPQUOTES;
E 286
	for (;;)
	{
		while (isascii(*p) && isspace(*p))
			p++;
		if (*p != '-')
			break;
		switch (*++p)
		{
		  case 'a':
			map->map_app = ++p;
			break;
I 250

		  case 's':
			map->map_coldelim = *++p;
			break;
E 250
		}
		while (*p != '\0' && !(isascii(*p) && isspace(*p)))
			p++;
		if (*p != '\0')
			*p = '\0';
	}
	if (map->map_app != NULL)
		map->map_app = newstr(map->map_app);

E 178
	return TRUE;
}
/*
**  DEQUOTE_MAP -- unquote an address
**
**	Parameters:
**		map -- the internal map structure (ignored).
D 200
**		buf -- the buffer to dequote.
**		bufsiz -- the size of that buffer.
E 200
I 200
**		name -- the name to dequote.
E 200
**		av -- arguments (ignored).
I 186
**		statp -- pointer to status out-parameter.
E 186
**
**	Returns:
**		NULL -- if there were no quotes, or if the resulting
**			unquoted buffer would not be acceptable to prescan.
**		else -- The dequoted buffer.
*/

char *
D 186
dequote_map(map, buf, bufsiz, av)
E 186
I 186
D 200
dequote_map(map, buf, bufsiz, av, statp)
E 200
I 200
dequote_map(map, name, av, statp)
E 200
E 186
	MAP *map;
D 200
	char buf[];
	int bufsiz;
E 200
I 200
	char *name;
E 200
	char **av;
I 186
	int *statp;
E 186
{
	register char *p;
	register char *q;
	register char c;
D 250
	int anglecnt;
	int cmntcnt;
	int quotecnt;
I 187
	int spacecnt;
E 187
	bool quotemode;
	bool bslashmode;
E 250
I 250
	int anglecnt = 0;
	int cmntcnt = 0;
	int quotecnt = 0;
	int spacecnt = 0;
	bool quotemode = FALSE;
	bool bslashmode = FALSE;
	char spacesub = map->map_coldelim;
E 250

D 250
	anglecnt = 0;
	cmntcnt = 0;
	quotecnt = 0;
I 187
	spacecnt = 0;
E 187
	quotemode = FALSE;
	bslashmode = FALSE;

E 250
D 200
	for (p = q = buf; (c = *p++) != '\0'; )
E 200
I 200
	for (p = q = name; (c = *p++) != '\0'; )
E 200
	{
		if (bslashmode)
		{
			bslashmode = FALSE;
			*q++ = c;
			continue;
		}

I 248
D 250
		if (c == ' ' && SpaceSub != '\0')
			c = SpaceSub;
E 250
I 250
		if (c == ' ' && spacesub != '\0')
			c = spacesub;
E 250

E 248
		switch (c)
		{
		  case '\\':
			bslashmode = TRUE;
			break;

		  case '(':
			cmntcnt++;
			break;

		  case ')':
			if (cmntcnt-- <= 0)
				return NULL;
			break;
I 187

		  case ' ':
			spacecnt++;
			break;
E 187
		}

		if (cmntcnt > 0)
		{
			*q++ = c;
			continue;
		}

		switch (c)
		{
		  case '"':
			quotemode = !quotemode;
			quotecnt++;
			continue;

		  case '<':
			anglecnt++;
			break;

		  case '>':
			if (anglecnt-- <= 0)
				return NULL;
			break;
		}
		*q++ = c;
	}

	if (anglecnt != 0 || cmntcnt != 0 || bslashmode ||
D 187
	    quotemode || quotecnt <= 0)
E 187
I 187
	    quotemode || quotecnt <= 0 || spacecnt != 0)
E 187
		return NULL;
	*q++ = '\0';
D 200
	return buf;
E 200
I 200
	return name;
E 200
}
E 177
E 61
E 36
E 21
E 1
