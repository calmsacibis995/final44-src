;;
;;	this file if served as input into lisp will create
;;		a new FRL. (the dumplisp or savelisp is
;;		done by the user or the makefile).
;;
;;	set interpret-mode to t here if you wish to load an
;;		interpretive version of frl.
;;
;;	see file ftoplevel.l to set the main frl directory 
;;		of sources and objects (variable frl-main-dir).
;;

(includef 'init.l)
(sstatus ignoreeof nil)	;; to undo something in ~douglas/.lisprc
			;; since I usually create FRL - douglas
(setq $gcprint nil)
(gc)			;; garbage collect before dumping lisp
