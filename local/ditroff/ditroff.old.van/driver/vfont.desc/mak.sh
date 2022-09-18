#!/bin/csh -f
#		create width files for varian/versatec fonts
set path=(../../bin /bin)
# Produce troff width files from the raster font files via "makefont"
makevfont -nB -l B > B
makevfont -nI -l -f95 I > I
makevfont -nR -l -f95 R > R
makevfont -nS -s S > old.S
#	br should be zero width
sed -e "/^br/s/[0-9][0-9]*/0/" old.S > S
rm -f old.S
makevfont -nap -a apl > ap
makevfont -nbr -a -l '-xno,em:mo,:O+,Fl:!=,Fi:>=,ff:==,fi:or,fl:??,is' basker.r > br
makevfont -nbi -a -l '-xno,em:mo,:O+,Fl:!=,Fi:>=,ff:==,fi:or,fl:??,is' basker.i > bi
makevfont -nbb -a -l '-xno,em:mo,:O+,Fl:!=,Fi:>=,ff:==,fi:or,fl:??,is' basker.b > bb
makevfont -nbk -a bocklin.14 > bk
makevfont -nch -c chess > ch
makevfont -ncl -a '-x!=,is:ap,!=:&,:' '-y+,pl:-,mi' clarendon > cl
makevfont -ncr '-x^T,:^U,:^V,:^W,:^X,:^Y,:^Z,:^^,:^_,:^?,:??,*G:fi,*D:fl,*H:ff,*L:\-,*C:ru,*P:em,*S:bu,*U:sq,*F:Fi,*Q:Fl,*W:de,:dg,:^[,:^\,:^],:#,fm:$,:' '-yA,*A:B,*B:E,*E:Z,*Z:H,*Y:I,*I:K,*K:M,*M:N,*N:O,*O:P,*R:T,*T:X,*X' cm.r > cr
makevfont -ncb '-x^T,:^U,:^V,:^W,:^X,:^Y,:^Z,:^^,:^_,:^?,:??,*G:fi,*D:fl,*H:ff,*L:\-,*C:ru,*P:em,*S:bu,*U:sq,*F:Fi,*Q:Fl,*W:de,:dg,:^[,:^\,:^],:#,fm:$,:' '-yA,*A:B,*B:E,*E:Z,*Z:H,*Y:I,*I:K,*K:M,*M:N,*N:O,*O:P,*R:T,*T:X,*X' cm.b > cb
makevfont -nci '-x^T,:^U,:^V,:^W,:^X,:^Y,:^Z,:^^,:^_,:^?,:??,*G:fi,*D:fl,*H:ff,*L:\-,*C:ru,*P:em,*S:bu,*U:sq,*F:Fi,*Q:Fl,*W:de,:dg,:^[,:^\,:^],:#,fm:$,:' '-yA,*A:B,*B:E,*E:Z,*Z:H,*Y:I,*I:K,*K:M,*M:N,*N:O,*O:P,*R:T,*T:X,*X' cm.i > ci
makevfont -nco countdown > co
makevfont -ncy cyrillic > cy
makevfont -ndr -a -c delegate.r > dr
makevfont -ndi -a -c delegate.i > di
makevfont -ndb -a -c delegate.b > db
makevfont -nCW -a -c '-x??,is' fix.10 > CW
makevfont -ngr -c '-x^T,ct:^U,fm:^V,dg:^W,de:14,O+:12,co:34,rg:^X,34:^Y,12:^Z,14:^],sq:^^,:^_,:' '-y_,ru:_,ul:|,bv' gacham.r > gr
makevfont -ngi -c '-x^T,ct:^U,fm:^V,dg:^W,de:14,O+:12,co:34,rg:^X,34:^Y,12:^Z,14:^],sq:^^,:^_,:' '-y_,ru:_,ul:|,bv' gacham.i > gi
makevfont -ngb -c '-x^T,ct:^U,fm:^V,dg:^W,de:14,O+:12,co:34,rg:^X,34:^Y,12:^Z,14:^],sq:^^,:^_,:' '-y_,ru:_,ul:|,bv' gacham.b > gb
makevfont -ngk greek > gk
makevfont -ngf -a -c '-y-,:' graphics > gf
makevfont -nhb '-x^T,*t:^X,*x:^^,*z' hebrew.16 > hb
makevfont -nhn -c h19 > hn
makevfont -nm -a '-x*g,:*d,:+-,:O+,:' '-y_,\_:_,ul' ugramma > m
makevfont -nmn '-x%,ct' '-y-,\-' mona > mn
makevfont -nmr '-x^X,ul:^V,OX' meteor.r.10 > mr
makevfont -nmi '-x^X,ul' meteor.i > mi
makevfont -nmb '-x^X,ul' meteor.b > mb
makevfont -nnr -a '-y_,ru' nonie.r.10 > nr
makevfont -nni -a '-y_,ru' nonie.i.10 > ni
makevfont -nnb -a '-y_,ru' nonie.b.10 > nb
makevfont -noe oldenglish > oe
makevfont -nor -a '-y_,ru' bodoni.r > or
makevfont -noi -a '-y_,ru' bodoni.i > oi
makevfont -nob -a '-y_,ru' bodoni.b > ob
makevfont -npb -a playbill > pb
makevfont -npp pip > pp
makevfont -nsc script > sc
makevfont -nsl seal > sl
makevfont -nsg -a sign > sg
makevfont -nsh -a shadow > sh
makevfont -nsr -l stare.r > sr
makevfont -nsi -l stare.i > si
makevfont -nsb -l stare.b > sb
makevfont -ntr times.r > tr
makevfont -nti times.i > ti
makevfont -ntb times.b > tb
makevfont -nts -s '-xmi,ci:es,*f:*f,es' times.s > ts
makevfont -ntR -l '-xru,\-' '-y_,ru:A,*A:B,*B:E,*E:H,*Y:I,*I:K,*K:M,*M:N,*N:O,*O:P,*R:T,*T:X,*X:Z,*Z' otimes.r > tR
makevfont -ntI -l '-xru,\-' '-y_,ru:A,*A:B,*B:E,*E:H,*Y:I,*I:K,*K:M,*M:N,*N:O,*O:P,*R:T,*T:X,*X:Z,*Z' otimes.i > tI
makevfont -ntB -l '-xru,\-' '-y_,ru:A,*A:B,*B:E,*E:H,*Y:I,*I:K,*K:M,*M:N,*N:O,*O:P,*R:T,*T:X,*X:Z,*Z' otimes.b > tB
makevfont -ntS -o otimes.s > old.tS
#	br should be zero width
sed -e "/^br/s/[0-9][0-9]*/0/" old.tS > tS
rm -f old.tS
