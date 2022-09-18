
(declare (localf fib))		;comment out to stop local functions

(defun If macro  (lis) 
       (prog (majlis minlis revl)
	     (do ((revl (reverse lis) (cdr revl)))
		 ((null revl))
		 (cond ((eq (car revl) 'else)
			(setq majlis `((t ,@minlis) ,@majlis)
			      minlis nil))
		       ((or (eq (car revl) 'then) (eq (car revl) 'thenret))
			(setq revl (cdr revl)
			      majlis `((,(car revl) ,@minlis) ,@majlis)
			      minlis nil))
		       ((eq (car revl) 'elseif))
		       ((eq (car revl) 'If)
			(setq majlis `(cond ,@majlis)))
		       (t (setq minlis `( ,(car revl) ,@minlis)))))
	     ; we displace the previous macro, that is we actually replace
	     ; the if list structure with the corresponding cond, meaning
	     ; that the expansion is done only once
	     (rplaca  lis (car majlis))
	     (rplacd lis (cdr majlis))
	     (return majlis)))
; useful printing macro (from jkfmacs)
;
(defmacro msg (&rest msglist)
  (do ((ll msglist (cdr ll))
       (result)
       (cur nil nil)
       (curport nil)
       (current))
      ((null ll) `(progn ,@(nreverse result)))
      (setq current (car ll))
      (If (dtpr current)
	  then (If (eq (car current) 'N)
		   then (setq cur `(msg-tyo-char 10 ,(cadr current)))
		elseif (eq (car current) 'B)
		   then (setq cur `(msg-tyo-char 32 ,(cadr current)))
		elseif (eq (car current) 'P)
		   then (setq curport (cadr current))
		else (setq cur `(princ ,current)))
       elseif (eq current 'N)
	  then (setq cur (list 'terpr))		; (can't use backquote
       elseif (eq current 'B)			; since must have new
      	  then (setq cur (list 'tyo 32))	; dtpr cell at end)
       elseif (eq current 'D)
	  then (setq cur '(drain))
       else (setq cur `(princ ,current)))
      (If cur 
	  then (setq result (cons (If curport then (nconc cur (ncons curport))
			                      else cur)
				  result)))))


;---- fib benchmark program
;
(defun fibtest ()
   (prog (vec fibnum)
	 (setq vec nil)
	 (do ((testlist '((15 . 100) (20 . 10)) (cdr testlist)))
	     ((null testlist))

	     (do ((xx (cdar testlist) (1- xx)))
		 ((zerop xx))
		 (setq vec (cons nil vec)))
	     (setq fibnum (caar testlist))
	     (setq starttime (ptime))
	     (do ((xx vec (cdr xx)))
		 ((null xx))
		 (fib 15))
	     (setq endtime (ptime))
	     (setq float-format "%.4f")
	     (msg "fib # " fibnum N
		  " start, end: " (norm starttime) " " (norm endtime) N
		  " total cpu time/ calc " (quotient
					      (norm (- (car endtime)
						       ( car starttime)))
					      (cdar testlist)) N

		  " cpu time - gc / calc "
		  (quotient
		     (norm (- (car endtime)
			      (car starttime)
			      (cadr endtime)
			      (-(cadr starttime))))
			(cdar testlist)) N
		  ))))
					  

(defun fib (x)
   (cond ((< x 2)  1)
	 (t (+ (fib (- x 1)) (fib (- x 2))))))

(defun norm (x) (cond ((dtpr x)(mapcar 'norm x))
		      (t (quotient x 60.0))))

;; end of benchmark file



