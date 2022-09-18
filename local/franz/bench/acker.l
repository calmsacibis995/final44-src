;  ackermans function
;    a(0,y) = y+1
;    a(x+1,0) = a(x,1)
;    a(x+1,y+1) = a(x,a(x+1,y))
;

(declare (localf acker))


(defun acker (x y)
  (cond ((eq 0 x) (1+ y))
	((eq 0 y) (acker (1- x) 1))
	(t (acker (1- x) (acker x (1- y))))))


(defun timeit (x y)
  (setq start (ptime)
        result (acker x y)
  	end (ptime))
  (print "result is ") (print result) (terpr)
  (print "seconds taken ") 
  (print (quotient (difference (car end) (car start)) 60.0))
  (terpr))
