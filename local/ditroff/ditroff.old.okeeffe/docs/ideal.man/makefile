PRINTER=-Pimagen
BODY=intro vague elements namebox pens opaque draw libfiles

out:	penult
	ditroff -msd -t $(PRINTER) penult > out

try:	$(BODY)
	ideal_p -n $(BODY) > try1.out
	ideal_p -n examples acknow > try2.out
	cat header try1.out try2.out refs > try

penult:	try biblio.ref
	ideal_f $(PRINTER) try | refer -sL -p biblio.ref | deqn $(PRINTER) > penult
