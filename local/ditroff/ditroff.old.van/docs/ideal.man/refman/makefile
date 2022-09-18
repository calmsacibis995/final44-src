PRINTER=-Pimagen
BODY=intro lang line comm post obs

out	:
	deqn $(PRINTER) header $(BODY) | ditroff $(PRINTER) -t -msd > out

try	:
	neqn header $(BODY) | nroff -msd > out
