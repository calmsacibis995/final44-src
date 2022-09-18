#! /bin/csh -f
# Produce troff width files from the raster font files via "makefont"
set path=( ../../bin /bin )
#
makeifont -nR -l '-y/,sl:+,pl:=,eq' cmr10 > R
makeifont -nI -i -l '-ys,ts' cmi10 > I
makeifont -nB -l cmb10 > B
makeifont -nS -s '-xci,:lf,:rf,:lc,:rc,:' cmsy10 > old.S
#	ul width = 95, not 132;  br is zero-width
sed -e "/^ul/s/132/ 95/" -e "/^br/s/[0-9][0-9]*/0/" old.S > S
rm -f old.S
makeifont -nCW -c '-xim,OX:tl,->:ar,ru:\-,ua:b",\:ve,if:em,<-:o/,ux:ft,$:fi,|:fl,}:ff,{:Fi,da:fm,#:Fl,fm:es,@' '-y-,em:-,\-:",b"' cmtt10 > old.CW
#	ru should have 47 width not 69
sed -e '/^ru/s/69/47/' old.CW > CW
rm -f old.CW
makeifont -nCI -c '-xim,OX:tl,->:ar,_:\-,ua:b",\:ve,if:em,<-:o/,ux:ft,$:fi,|:fl,}:ff,{:Fi,da:fm,#:Fl,fm:es,@' '-y_,\_:-,em:-,\-:",b"' cmit > CI
makeifont -nas -a -c cmasc10 > as
makeifont -nMS -o brack > MS
makeifont -nBI -i cmbi10 > BI
makeifont -nBs -l cmbs10 > Bs
makeifont -nBS -s '-xci,:lf,:rf,:lc,:rc,:' cmbsy > old.BS
#	ul width = 110, not 152;  / is 133 wide, not 0;  br is zero-width
sed -e "/^ul/s/152/110/" -e "/^\//s/  0/133/" -e "/^br/s/[0-9][0-9]*/0/" old.BS > BS
rm -f old.BS
makeifont -nBT -l cmbti > BT
makeifont -nCS -l cmcsc > CS
makeifont -nd -l cmdunh > d
makeifont -nF -l cmfib > F
makeifont -nf -l cmff > f
makeifont -nn -l cmnew > n
makeifont -nni -l cmnews > ni
makeifont -ns -l cms10 > s
makeifont -nsl seal > sl
makeifont -np -l cmss10 > p
makeifont -nBp -l cmssb > Bp
makeifont -nsp -l cmsss > sp
makeifont -nT -l cmti10 > T
makeifont -nti -l cmtitl > ti
makeifont -nu -l cmu10 > u
