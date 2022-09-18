#! /bin/csh -f
#
# DITROFF filter for the imagen
#

umask 0
set name=() host=()
top:
	if ($#argv > 0) then
		switch ($argv[1])
		case -n:
			shift argv
			if ($#argv > 0) then
				set name = $argv[1]
				shift argv
			endif
			goto top
		case -h:
			shift argv
			if ($#argv > 0) then
				set host = $argv[1]
				shift argv
			endif
			goto top
		default:
			shift argv
			goto top
		endsw
	endif
onintr cleanup
/usr/local/lib/dit-imagen > /tmp/imp$$
if ($status) exit $status
(echo -n \@document\(owner \"$name\", site \"$host\", spooldate \"`date`\", \
    language \"imPress\", jobheader on, jamresistance on\) ; \
    cat /tmp/imp$$ ) | /usr/local/lib/ips -s
/bin/rm -f /tmp/imp$$
exit 0

cleanup:
/bin/rm -f /tmp/imp$$
exit 1
