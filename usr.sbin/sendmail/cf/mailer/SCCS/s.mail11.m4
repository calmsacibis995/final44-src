h51614
s 00050/00000/00000
d D 8.1 95/05/23 12:05:02 eric 1 0
c date and time created 95/05/23 12:05:02 by eric
e
u
U
t
T
I 1
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
ifdef(`MAIL11_MAILER_PATH',, `define(`MAIL11_MAILER_PATH', /usr/etc/mail11)')
ifdef(`MAIL11_MAILER_FLAGS',, `define(`MAIL11_MAILER_FLAGS', nsFx)')
ifdef(`MAIL11_MAILER_ARGS',, `define(`MAIL11_MAILER_ARGS', mail11 $g $x $h $u)')
define(`_USE_DECNET_SYNTAX_')

POPDIVERT

PUSHDIVERT(3)
# DECNET delivery
R$* < @ $=w .DECNET. >		$#local $: $1			local DECnet
R$+ < @ $+ .DECNET. >		$#mail11 $@ $2 $: $1		DECnet user
POPDIVERT

PUSHDIVERT(6)
CPDECNET
POPDIVERT

###########################################
###   UTK-MAIL11 Mailer specification   ###
###########################################

VERSIONID(`%W% (Berkeley) %G%')

Mmail11, P=MAIL11_MAILER_PATH, F=MAIL11_MAILER_FLAGS, S=15, R=25,
	A=MAIL11_MAILER_ARGS

S15
R$+			$: $>25 $1		preprocess
R$w :: $+		$@ $w :: $1		ready to go

S25
R$+ < @ $- .UUCP >	$: $2 ! $1		back to old style
R$+ < @ $- .DECNET >	$: $2 :: $1		convert to DECnet style
R$+ < @ $- .LOCAL >	$: $2 :: $1		convert to DECnet style
R$+ < @ $=w. >		$: $2 :: $1		convert to DECnet style
R$=w :: $+		$2			strip local names
R$+ :: $+		$@ $1 :: $2		already qualified
E 1
