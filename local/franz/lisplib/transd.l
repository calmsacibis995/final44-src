;;; interlisp to franzlisp file transducer utilities
;;; pass1. balance parentheses:

(defun pass1 (in out)(prog (inport )
			   (setq inport(infile in))
			   (setq $outport$ (outfile out)) ; close this later?
			   loop ($prpr (read inport))
			   (go loop) ;;; how do you detect eof?
			   ))

