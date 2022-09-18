;; benchmac
;; a macro for making a benchmark
;; Use it like this:
;;	(defun tak-bench (n) (benchmac (tak 18. 14. 4.)))
;; You must use the variable 'n'.  You may use other variables.
;; The function tak-bench takes one argument which is the number of
;; times to run the benchmark
;;
(declare (macros t))

(defmacro benchmac (callform)
   `(prog (count begin end gctime)
       (setq count nil)
       (do ((x n (1- x)))
	   ((zerop x))
	   (setq count (cons nil count)))
       (setq begin (ptime))
       (do ((y count (cdr y)))
	   ((null y))
	   ,callform)
       (setq end (ptime))
       (msg "begin " begin N
            "end "   end   N
            "runs "  n     N)
       (cond ((> (setq gctime (- (cadr end) (cadr begin))) 0)
	      (msg "avg cpu time "
		   (quotient (diff (car end) (car begin) gctime)
			     (times 60.0 n))
		   ", avg gc time " (quotient gctime (times 60.0 n))
		   N))
	     (t (msg "avg cpu time "
		     (quotient (diff (car end) (car begin))
			       (times 60.0 n))
		     N)))
       (terpr)))
