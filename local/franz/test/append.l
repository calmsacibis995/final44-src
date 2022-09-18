(def append
  (lexpr (nargs)
	 (cond ((eq nargs 2) (append2args (arg 1) (arg 2)))
	       ((zerop nargs) nil)
	       (t (do ((i (1- nargs) (1- i))
		       (res (arg nargs)))
		      ((zerop i) res)
		      (setq res (append2args (arg i) res)))))))

;--- append2args : append just two args
; a version of append which only works on 2 arguments
;
(def append2args 
  (lambda (x y)
	  (prog (l l*)
		(cond ((null x) (return y))
		      ((atom x) (error "Non-list to append:" x)))
		(setq l* (setq l (cons (car x) nil)))
	loop	(cond ((atom x) (error "Non-list to append:" x))
		      ((setq x (cdr x))
		       (setq l* (cdr (rplacd l* (cons (car x) nil))))
		       (go loop)))
		(rplacd l* y)
		(return l))))
