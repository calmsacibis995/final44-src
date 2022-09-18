h43975
s 00018/00000/00000
d D 5.1 88/10/20 18:35:50 bostic 1 0
c from UUNET; applied patches 1-3
e
u
U
t
T
I 1
:
: make dtext.dat from individual parts
:
if test -s dtext.dat
 then exit 0
fi
for fname in dtext.aa dtext.ab dtext.ac dtext.ad dtext.ae dtext.af
do
 if test -f $fname
  then continue
  else echo "maketxt.sh: missing file: $fname"; exit 1
 fi
done
cat dtext.aa dtext.ab dtext.ac dtext.ad dtext.ae dtext.af >dtext.dat.uu
rm dtext.aa dtext.ab dtext.ac dtext.ad dtext.ae dtext.af
uudecode dtext.dat.uu
rm dtext.dat.uu
exit 0
E 1
