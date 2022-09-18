# I made a little program to make two column output since I couldn't figure
# out any other way to do it.  The app.me is what we used for the 4.3
# Schedule A, but it came out to be 56 pages instead of 50.  --sellgren

AttachmentA:
	rm -f twocol
	cc -O -o twocol format.c twocol.c
	twocol network.2.list
	enscript -2r -pAttachmentA.p -b"BSD Networking Software, Release 2--Attachment A    8 July 1991" network.2.list.tc
	# lpr AttachmentA.p
	rm network.2.list.tc



