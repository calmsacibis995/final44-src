;; VAX tests were run on a 780.

(defun tak (x y z)
  (if (not (< y x))
      z
      (tak (tak (1- x) y z)
	   (tak (1- y) z x)
	   (tak (1- z) x y))))

;; here it is with FUNCALL. An extra argument is passed, which also
;; costs some small amount. Note that the reference to the function-cell
;; by #'takfsub is "taken-out-of-the-loop." This may explain the Lispm result.
	
(defun takf (x y z)
  (takfsub #'takfsub x y z))

(defun takfsub (f x y z)
  (if (not (< y x))
      z
      (funcall f f (funcall f f (1- x) y z)
	       (funcall f f (1- y) z x)
	       (funcall f f (1- z) x y))))
 

