(defun foo (x y)
   (do ((xx x (cdr xx))
	(num 0))
       ((null xx))
       (setq num (boole 7 num (car xx)))))
