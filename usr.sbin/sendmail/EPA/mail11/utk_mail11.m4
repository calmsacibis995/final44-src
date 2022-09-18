PUSHDIVERT(-1)
#
# Not exciting enough to bother with copyrights and most of the
# rulesets are based from those provided by DEC.
# Barb Dijker, Labyrinth Computer Services, barb@labyrinth.com
#
# This mailer is only useful if you have DECNET and the
# mail11 program - gatekeeper.dec.com:/pub/DEC/gwtools.
# 
# For local delivery of DECNET style addresses to the local
# DECNET node, you will need feature(use_cw_file) and put
# your DECNET nodename in in the cw file.
#
ifdef(`MAIL11_PATH',,
        `define(`MAIL11_PATH', /usr/etc/mail11)')

POPDIVERT

PUSHDIVERT(3)
# DECNET delivery
R$*<@$=w.DNET.>		$#local $: $1			local decnet
R$+<@$+.DNET.>		$#mail11 $@$2$:$1		dnet user
POPDIVERT

PUSHDIVERT(6)
CPDNET
POPDIVERT

###########################################
###   UTK-MAIL11 Mailer specification   ###
###########################################

VERSIONID(`utk_mail11.m4 lcs1.0')

Mmail11, P=/usr/etc/mail11, F=nsFx, S=17, R=18, A=mail11 $g $x $h $u

S17
R$+			$:$>18$1			preprocess
R$w::$+			$@$w::$1			ready to go

S18
R$+<@$-.UUCP>		$:$2!$1				back to old style
R$+<@$-.DNET>		$:$2::$1			convert to dnet style
R$+<@$-.LOCAL>		$:$2::$1			convert to dnet style
R$+<@$=w.>		$:$2::$1			convert to dnet style
R$=w::$+		$2				strip local names
R$+::$+			$@$1::$2			already qualified
