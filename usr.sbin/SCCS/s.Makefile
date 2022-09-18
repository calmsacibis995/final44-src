h06865
s 00003/00003/00023
d D 5.20 93/06/12 15:22:05 bostic 23 21
c move nvi.recover to contrib
e
s 00000/00000/00026
d R 8.1 93/06/06 14:13:03 bostic 22 21
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00025
d D 5.19 93/06/04 11:19:48 bostic 21 20
c go to named 4.9
e
s 00002/00000/00024
d D 5.18 93/05/28 22:26:24 ralph 20 19
c added mips specific files
e
s 00003/00003/00021
d D 5.17 93/05/16 13:55:32 bostic 19 18
c add nvi.recover(8)
e
s 00002/00002/00022
d D 5.16 93/04/27 18:39:40 torek 18 17
c add sparc eeprom utility
e
s 00001/00001/00023
d D 5.15 93/04/27 10:14:09 bostic 17 16
c add sysctl
e
s 00003/00004/00021
d D 5.14 93/04/04 21:02:32 bostic 16 15
c Kirk made pstat work again
e
s 00005/00005/00020
d D 5.13 93/02/25 15:15:19 torek 15 14
c config is not used everywhere; make clean should clean config.new
e
s 00003/00004/00022
d D 5.12 93/02/24 18:19:39 bostic 14 13
c move implog, implogd, htable, gettable to /usr/src/old
e
s 00002/00002/00024
d D 5.11 93/02/24 18:17:41 bostic 13 12
c move dlmpcc to /usr/src/old
e
s 00002/00002/00024
d D 5.10 93/02/24 18:15:34 bostic 12 11
c move arff, rxformat, flcopy to old
e
s 00010/00008/00016
d D 5.9 93/02/24 18:14:56 torek 11 10
c checked in for Chris Torek by TK
e
s 00002/00000/00022
d D 5.8 92/09/02 11:58:57 bostic 10 9
c add luna68k
e
s 00006/00005/00016
d D 5.7 92/07/20 14:38:59 bostic 9 6
c update
e
s 00002/00002/00018
d D 5.6.1.2 91/05/08 18:23:25 bostic 8 7
c branch for the 2nd network distribution
e
s 00003/00004/00017
d D 5.6.1.1 91/05/07 23:10:47 bostic 7 6
c branch for the 2nd network distribution
e
s 00010/00007/00011
d D 5.6 91/05/06 18:16:23 bostic 6 5
c checkpoint
e
s 00002/00000/00016
d D 5.5 91/01/15 13:50:14 william 5 4
c 386 uses bad144
e
s 00000/00001/00016
d D 5.4 90/08/07 20:05:44 karels 4 3
c mv gated to sbin
e
s 00004/00004/00013
d D 5.3 90/06/25 10:29:29 bostic 3 2
c arp_iso is gone now
e
s 00010/00011/00007
d D 5.2 90/06/25 00:53:12 bostic 2 1
c checkpoint for June tape
e
s 00018/00000/00000
d D 5.1 90/05/11 16:06:00 bostic 1 0
c first pass for new make
e
u
U
f b 
t
T
I 1
#	%W% (Berkeley) %G%

D 2
# not ours?: gated
# not converted: gated
E 2
I 2
D 4
# not working:	gated
E 4
E 2
D 3
SUBDIR=	ac accton arp arp_iso chown chroot config cron diskpart edquota \
D 2
	gettable htable implog implogd inetd iostat kgmon kvm_mkdb lpr \
	mkhosts mkpasswd mkproto mtree quot quotaon rmt rwhod sa sendmail \
	sliplogin syslogd timed timedc traceroute trpt trsp update
E 2
I 2
	gettable htable implog implogd inetd kgmon kvm_mkdb lpr mkhosts \
	mkpasswd mkproto mtree named pstat quot quotaon repquota rmt \
	rwhod sa sendmail sliplogin syslogd timed traceroute trpt trsp update
E 3
I 3
D 6
SUBDIR=	ac accton arp chown chroot config cron diskpart edquota gettable \
	htable implog implogd inetd kgmon kvm_mkdb lpr mkhosts mkpasswd \
	mkproto mtree named pstat quot quotaon repquota rmt rwhod sa \
	sendmail sliplogin syslogd timed traceroute trpt trsp update
E 6
I 6
D 7
D 9
# pstat
SUBDIR=	ac accton arp chown chroot config cron dev_mkdb diskpart edquota \
E 7
I 7
D 8
SUBDIR=	ac accton arp chown chroot config dev_mkdb diskpart edquota \
E 8
I 8
SUBDIR=	accton arp chown chroot config dev_mkdb diskpart edquota \
E 8
E 7
	gettable htable implog implogd inetd iostat kgmon kvm_mkdb lpr \
D 7
	mkproto mtree named pwd_mkdb quot quotaon repquota rmt rwhod sa \
E 7
I 7
	mtree named pwd_mkdb quotaon repquota rmt rwhod \
E 7
	sendmail sliplogin syslogd traceroute trpt trsp update vipw
E 9
I 9
D 16
# BROKEN pstat
E 16
D 15
SUBDIR=	ac accton amd arp chown chroot config cron dev_mkdb diskpart \
D 11
	edquota gettable htable implog implogd inetd iostat kgmon kvm_mkdb \
E 11
I 11
D 14
	edquota gettable htable implog implogd inetd kgmon kvm_mkdb \
E 11
	lpr mkproto mtree named portmap pwd_mkdb quot quotaon repquota \
	rmt rwhod sa sendmail sliplogin syslogd traceroute trpt trsp \
	update vipw
E 14
I 14
	edquota inetd kgmon kvm_mkdb lpr mkproto mtree named portmap \
	pwd_mkdb quot quotaon repquota rmt rwhod sa sendmail sliplogin \
	syslogd traceroute trpt trsp update vipw
E 15
I 15
SUBDIR=	ac accton amd arp chown chroot cron dev_mkdb diskpart edquota \
D 16
	inetd kgmon kvm_mkdb lpr mkproto mtree named portmap pwd_mkdb \
	quot quotaon repquota rmt rwhod sa sendmail sliplogin syslogd \
	traceroute trpt trsp update vipw
E 16
I 16
D 19
	inetd kgmon kvm_mkdb lpr mkproto mtree named portmap pstat \
	pwd_mkdb quot quotaon repquota rmt rwhod sa sendmail sliplogin \
D 17
	syslogd traceroute trpt trsp update vipw
E 17
I 17
	sysctl syslogd traceroute trpt trsp update vipw
E 19
I 19
D 21
	inetd kgmon kvm_mkdb lpr mkproto mtree named nvi.recover portmap \
E 21
I 21
D 23
	inetd kgmon kvm_mkdb lpr mkproto mtree nvi.recover portmap \
E 21
	pstat pwd_mkdb quot quotaon repquota rmt rwhod sa sendmail \
	sliplogin sysctl syslogd traceroute trpt trsp update vipw
E 23
I 23
	inetd kgmon kvm_mkdb lpr mkproto mtree portmap pstat pwd_mkdb \
	quot quotaon repquota rmt rwhod sa sendmail sliplogin sysctl \
	syslogd traceroute trpt trsp update vipw
E 23
E 19
E 17
E 16
E 15
E 14
E 9
E 6
E 3
E 2

D 2
.if ${MACHINE} == "tahoe" || make(clean) || make(cleandir)
SUBDIR+=dlmpcc
.endif

.if ${MACHINE} == "vax" || make(clean) || make(cleandir)
SUBDIR+=arff bad144 flcopy rxformat
E 2
I 2
.if   make(clean) || make(cleandir)
D 6
SUBDIR+=arff bad144 dlmpcc flcopy iostat rxformat
E 6
I 6
D 7
D 11
SUBDIR+=arff bad144 dlmpcc flcopy rxformat timed
E 11
I 11
D 12
SUBDIR+=arff bad144 config dlmpcc flcopy iostat rxformat timed
E 12
I 12
D 13
SUBDIR+=bad144 config dlmpcc iostat timed
E 13
I 13
D 15
SUBDIR+=bad144 config iostat timed
E 15
I 15
D 18
SUBDIR+=bad144 config config.new iostat timed
E 18
I 18
SUBDIR+=bad144 config config.new eeprom iostat timed
E 18
E 15
E 13
E 12
E 11
E 7
I 7
SUBDIR+=bad144 dlmpcc flcopy rxformat timed
E 7
.elif ${MACHINE} == "hp300"
D 11
SUBDIR+=timed
E 11
I 11
SUBDIR+=config iostat timed
.elif ${MACHINE} == "i386"
SUBDIR+=bad144 config iostat
E 11
I 10
.elif ${MACHINE} == "luna68k"
D 11
SUBDIR+=timed
E 11
I 11
SUBDIR+=config iostat timed
I 20
.elif ${MACHINE} == "mips"
SUBDIR+=config iostat timed
E 20
.elif ${MACHINE} == "sparc"
D 18
SUBDIR+=config.new timed
E 18
I 18
SUBDIR+=config.new eeprom timed
E 18
E 11
E 10
E 6
.elif ${MACHINE} == "tahoe"
D 6
SUBDIR+=dlmpcc iostat
E 6
I 6
D 11
SUBDIR+=dlmpcc timed
E 11
I 11
D 13
SUBDIR+=config dlmpcc iostat timed
E 13
I 13
SUBDIR+=config iostat timed
E 13
E 11
E 6
.elif ${MACHINE} == "vax"
D 6
SUBDIR+=arff bad144 flcopy iostat rxformat
E 6
I 6
D 8
D 11
SUBDIR+=arff bad144 flcopy rxformat timed
E 8
I 8
SUBDIR+=bad144 flcopy rxformat timed
E 8
E 6
I 5
.elif ${MACHINE} == "i386"
SUBDIR+=bad144 
E 11
I 11
D 12
SUBDIR+=arff bad144 config flcopy iostat rxformat timed
E 12
I 12
SUBDIR+=bad144 config iostat timed
E 12
E 11
E 5
E 2
.endif

.include <bsd.subdir.mk>
E 1
