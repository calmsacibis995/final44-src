(declare (localf tak))
(sstatus translink on)

(defun tak (x y z)
   (cond ((>& x y)
	  (tak (tak (1- x) y z)
	       (tak (1- y) z x)
	       (tak (1- z) x y) ))
	 (t z) ))

(defun test ()
   (print (ptime))
   (tak 18 12 6)
   (print (ptime)))
