(defun compare (message value1 value2)
  (cond ((not (eq value1 value2)) (msg "error found, test " message N
				       "value expected: " value1 N
				       "value got: " value2 N))
	(t (msg "OK: " message N D))))

; test file
(defun test nil
  (progdotest)
  (catchthrowtest))

(declare (special x xxx))
(defun progdotest nil
  ; test progs
  ;
  (setq x 4)
  (compare "prog not returning"
	    nil (prog (x y)
		      (setq x 3)
		      (setq y 4)
		      (compare "local binding in prog" 3 x)))
  (compare "variable being un shallow bound"
	    4 x)

  ; add numbers from 1 to 10, result is 10*11 / 2
  (compare "do loop  simple add"
	    55 (do ((x 1 (add1 x))
		    (sum 0 (add x sum)))
		   ((eq x 11) sum)))

  ; do loop with return
  (compare "do with return"
	  4 (do ((xx '(a b c d) (cdr xx))
		 (sum 0 (1+ sum)))
		(nil)
		(cond ((null xx) (return sum))))))



(defun catchthrowtest ()
  ; test catches, 
  ;
  (compare  "catch not being thrown"
	    4 (*catch 'tg (progn (setq x 4)
				 (add 5 4 2 1)
				 x)))

  (compare "catch being thrown"
	   'foobar (*catch 'tg2 (progn (setq x 4)
				       (add 5 4)
				       (*throw 'tg2 'foobar)
				       x)))

  ; test errsets
  (setq x '(a b c))
  (compare "errset not taken"
	   x (car (errset (progn (add 3 4 5) x))))

  (msg "expect add error message " N)
  (compare "errset being taken, with message"
	   nil (errset (prog nil
			   (setq xxx 234234)
			   (add 3 4 'a)
			   (return 2342340))))

  (compare "errset being taken, no message"
	   nil (errset (prog nil
			     (xxx 3 'yyy)	; undefined function
			     )
		       nil))
)

				 
