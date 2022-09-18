;;;
;;;		compiler/interpreter exerciser (validation)
;;;
;;;			-[Thu Aug 11 14:22:20 1983 by layer]-

(eval-when (eval compile) (load 'tmacs.l))

(defun nlist (n)
   (do ((i 1 (1+ i))
	(x nil (cons i x)))
       ((greaterp i n) x)))

(defun tfact (n)
  (cond ((greaterp 3 n) n)
	(t (times n (tfact (difference n 1))))))

(defun tget (prop key)
   (get prop key))

(defun tmemq (n m)
  (memq n m))

(defun ttype (n)
  (typep n))

(defmacro args-to-list ()
   '(cond ((greaterp (arg) 0)
	   (do ((i N (1- i)) (arglis))
	       ((lessp i 1)
		(return arglis))
	       (setq arglis (cons (arg i) arglis))))
	  (t nil)))

(defun lexpr-argtest N
   (args-to-list))

(defun lexpr-setargtest N
   (setarg 3 'three)
   (setarg N 'last-arg)
   (setarg 1 'first-arg)
   (args-to-list))

(defun lexpr-tail-merge N		;count up to (arg 2) and return it
   (if (=& (arg 1) (arg 2))
       then (arg 2)
       else (lexpr-tail-merge (1+ (arg 1)) (arg 2))))

(defun lexpr-cc nargs
  (cond ((eq nargs '2) 
	 (cond ((null (arg 1)) (arg 2))
	       (t (arg 1))))
	(t nargs)))

(defun tail-merge (l)		;return last arg
   (if (eq 1 (length l))
       then (car l)
       else (tail-merge (cdr l))))

(defun tail-merge2 (a b c)
  (if (<& a 0)
      then (list a b c)
      else (tail-merge2 (1- c) (1- a) (1- b))))

;;;--- test :: main testing routine
; to add a test, write the function and add it above.  Then add the
; verification/validation part below.

(defun test ()
   (prog (x y z)
       (start-exer "misc functions")
       (if (equal 3000 (length (nlist 3000)))
	   then (done-exer t)
	   else (done-exer nil))

       (start-exer "factorial")
       (if (equal (tfact 200) 788657867364790503552363213932185062295135977687173263294742533244359449963403342920304284011984623904177212138919638830257642790242637105061926624952829931113462857270763317237396988943922445621451664240254033291864131227428294853277524242407573903240321257405579568660226031904170324062351700858796178922222789623703897374720000000000000000000000000000000000000000000000000)
	   then (done-exer t)
	   else (done-exer nil))

       (start-exer "get")
       (setq x 1 y 2 z 3)
       (putprop 'x 1 'number)
       (putprop 'y 2 'number)
       (putprop 'z 3 'number)
       (if (and (eq 1 (tget 'x 'number))
		(null (tget 'x 'junk))
		(putprop 'nil 45 'number)
		(eq 45 (tget nil 'number)))
	   then (done-exer t)
	   else (done-exer nil))

       (start-exer "memq")
       (if (and (null (tmemq 'a '(b c d e f g h i j k l)))
		(equal '(c d e f) (tmemq 'c '(a b c d e f))))
	   then (done-exer t)
	   else (done-exer nil))

       (start-exer "type")
       (if (and (atom 'sdfsdfds)
		(bigp 9999999999999999999999999999999)
		(dtpr '(a b c d))
		(list '(a d s a))
		(symbolp 'asdasdas)
		(stringp "1212323213")
		(eq 'string (ttype "asdasdas"))
		(eq 'bignum (ttype 99999999999999999999999999999))
		(eq 'fixnum (ttype 1))
		(eq 'symbol (ttype 'asdasdasdas))
		(eq 'flonum (ttype 123.123))
		(eq 'list (ttype '(asd asd asd asd asd asd asd))))
	   then (done-exer t)
	   else (done-exer nil))

       (start-exer "arg")
       (if (equal '(a b c d e f) (lexpr-argtest 'a 'b 'c 'd 'e 'f))
	   then (done-exer t)
	   else (done-exer nil))
       
       (start-exer "setarg")
       (if (equal '(first-arg 2 three 4 5 6 7 8 last-arg)
		  (lexpr-setargtest 1 2 3 4 5 6 7 8 9))
	   then (done-exer t)
	   else (done-exer nil))

       (start-exer "lexpr tail merge")
       (if (eq 10 (lexpr-tail-merge 0 10))
	   then (done-exer t)
	   else (done-exer nil))
       
       (start-exer "lexpr/cc")
       (if (and (eq 5 (lexpr-cc 1 2 3 4 5))
		(eq 2 (lexpr-cc nil 2))
		(eq 1 (lexpr-cc 1 2)))
	   then (done-exer t)
	   else (done-exer nil))
       
       (start-exer "tail merge1")
       (if (eq 'last (tail-merge '(1 2 3 4 5 6 7 8 7 6 5 6 67 last)))
	   then (done-exer t)
	   else (done-exer nil))

       (start-exer "tail merge2")
       (if (and (equal '(-1 -1 -1) (tail-merge2 65535 65535 65535))
		(equal '(-1 0 -2) (tail-merge2 12 13 14))
		(equal '(-3 7 17) (tail-merge2 40 20 30)))
	   then (done-exer t)
	   else (done-exer nil))
       
       (msg "All tests completed successfully!" N)))
