;;;
;;; This file mainly tests the lisp code portion of the interp.
;;;
;;;			-[Mon Nov 22 23:04:55 1982 by layer]-
;;;
;;;

(eval-when (eval compile) (load 'tmacs.l))

(defun test ()
   (prog ()
       (start-exer "rplac[ad]")
       (done-exer
	   (If (and (equal (copy '(replaced-element 2 3 4 5 6 7 8))
			   (rplaca '(1 2 3 4 5 6 7 8) 'replaced-element))
		    (equal (copy '(1 replaced-element))
			   (rplacd '(1 2 3 4 5 6 7 8) '(replaced-element))))
	       then (quote t)
	       else (quote nil)))
       (start-exer "loops and go")
       (done-exer
	   (If (eq 100 (tloop 100))
	       then (quote t)
	       else (quote nil)))))

(defun tloop (high)
   (prog (counter)
       (setq counter 1)
top    (If (eq counter high)
	   then (return counter)
	   else (setq counter (add1 counter))
		(go top))))
