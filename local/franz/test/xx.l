(defun xx (x)
   (cons 'a (rplaca x (cons 'b 'c))))

(If (not (equal (copy '(a . ((b . c) 2 3)))
		(xx '(1 2 3))))
    then (break "xx"))

(defun xx2 (x)
   (rplaca x 'junk))

(If (not (equal (copy '(junk 2 3 4 5))
		(xx2 '(xx2 2 3 4 5))))
    then (break "xx2"))

(defun xx3 (x)
   (rplaca x (cons 'junk 'too)))

(If (not (equal (copy '((junk . too) 2 3 4 5))
		(xx3 '(xx2 2 3 4 5))))
    then (break "xx3"))
