#! /bin/csh -f
# Produce troff width files from the raster font files via "makefont"
set path=( ../../bin /bin )
#
makeifont -r300 -d/usr/imagen/fonts/raster/300 -p36 -nR -l '-y/,sl:+,pl:=,eq' cmr10 > R
makeifont -r300 -d/usr/imagen/fonts/raster/300 -p36 -nI -l cmti10 > I
makeifont -r300 -d/usr/imagen/fonts/raster/300 -p36 -nB -l cmb10 > B
makeifont -r300 -d/usr/imagen/fonts/raster/300 -p36 -nS -s '-xci,:lf,:rf,:lc,:rc,:' cmsy10 > old.S
#	ul width = 95, not 132;  br is zero-width
sed -e "/^ul/s/132/ 95/" -e "/^br/s/[0-9][0-9]*/0/" old.S > S
rm -f old.S
makeifont -r300 -d/usr/imagen/fonts/raster/300 -p36 -nCW -a -c cmasc10 > CW
makeifont -r300 -d/usr/imagen/fonts/raster/300 -p36 -nBS -s '-xci,:lf,:rf,:lc,:rc,:' cmbsy > old.BS
#	ul width = 110, not 152;  / is 133 wide, not 0;  br is zero-width
sed -e "/^ul/s/152/110/" -e "/^\//s/  0/133/" -e "/^br/s/[0-9][0-9]*/0/" old.BS > BS
rm -f old.BS
makeifont -r300 -d/usr/imagen/fonts/raster/300 -p36 -nBT -l cmbti > BT
makeifont -r300 -d/usr/imagen/fonts/raster/300 -p36 -nCS -l cmcsc > CS
makeifont -r300 -d/usr/imagen/fonts/raster/300 -p36 -ns -l cms10 > s
makeifont -r300 -d/usr/imagen/fonts/raster/300 -p36 -np -l cmss10 > p
makeifont -r300 -d/usr/imagen/fonts/raster/300 -p36 -nBp -l cmssb > Bp
makeifont -r300 -d/usr/imagen/fonts/raster/300 -p36 -nsp -l cmsss > sp
makeifont -r300 -d/usr/imagen/fonts/raster/300 -p36 -nT -i '-ys,ts' cmi10 > T
