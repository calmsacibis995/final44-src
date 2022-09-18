; benchmarks from BYTE, July 1984 p. 288-9
;
;
; REV/APP benchmark
;
(defun rev (x)
       (cond ((null x) nil)
	     (t (app (rev (cdr x)) (list (car x))))))

(defun app (x y)
       (cond ((null x) y)
	     (t (app (rev (cdr x)) (cons (car (rev x)) y)))))
