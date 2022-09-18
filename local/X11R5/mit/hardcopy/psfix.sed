# sed script to fix PostScript files to print higher on the page,
# you may lose page numbers on some printers without this
/^clippath pathbbox pop pop exch pop 0 exch translate$/i\
clippath pathbbox exch pop exch add /pgtop exch def pop
/^clippath pathbbox \/pgtop exch def pop pop pop$/d
