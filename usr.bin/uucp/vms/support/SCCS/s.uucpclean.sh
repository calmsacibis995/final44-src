h47136
s 00000/00000/00017
d D 8.1 93/06/06 22:16:01 bostic 2 1
c 4.4BSD snapshot (revision 8.1)
e
s 00017/00000/00000
d D 5.1 91/04/24 17:51:36 bostic 1 0
c date and time created 91/04/24 17:51:36 by bostic
e
u
U
t
T
I 1
SPOOL=/usr/spool/uucp

cd /usr/lib/uucp
uuclean -pLTMP. -n24
uuclean -d/usr/spool/uucp/TM. -pTM.
uuclean -d/usr/spool/uucp/X. -pX.
uuclean -d/usr/spool/uucp/C. -pC.
uuclean -d/usr/spool/uucp/D. -pD.
uuclean -d/usr/spool/uucp/D.`uuname -l` -pD.
uuclean -d/usr/spool/uucp/D.`uuname -l`X -pD.

cd $SPOOL
mv LOGFILE o.LOGFILE
mv SYSLOG o.SYSLOG
cp /dev/null LOGFILE
cp /dev/null SYSLOG
chmod 666 LOGFILE SYSLOG
E 1
