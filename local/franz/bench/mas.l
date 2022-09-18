
(defun listn (n)
    (cond
      ((= 0 n)
	nil)
      (t (cons n (listn (1- n))))))

(defun mas (x y z)
    (cond
      ((not (shorterp y x))
	z)
      (t (mas (mas (cdr x)
		   y z)
	      (mas (cdr y)
		   z x)
	      (mas (cdr z)
		   x y)))))

(defun shorterp (x y)
       (and y (or (null x)
		  (shorterp (cdr x)
			    (cdr y)))))

;benchmark is called

;(mas (listn 18) (listn 12) (listn 6))

Could you please check this against your recolllection? Thanks.
			-rpg-


