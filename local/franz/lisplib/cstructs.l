(setq rcs-c-structure-package
  "$Header: cstructs.l,v 1.2 84/01/05 17:35:55 sklower Exp $")
;
; Package for describing and using C structures from franz lisp
;

(defvar c-structure-indicator 'cs-ind)
(defvar cs-structs-in-progress nil)
(defvar cs-long-alignment #+(or vax mc500) 4 #-(or vax mc500) 2)
(declare
  (special cs-cur-size cs-cur-base cs-cur-alignment cs-cur-name)
  (macros nil)
  (localf cs-parse-struct cs-parse-dcl cs-array-size cs-peruse-dcl
	  cs-gen-member cs-gen*-member cs-gen-structs cs-do-one-struct)
  )

;; internal book-keeping macros
(defmacro cs-error (message &rest args)
  ;; print an error preceeded by 'c-structure-package'
  `(error ',(concat "c-structure-package: " message) ,@args))

(defrecord cs-type
	(name nil)
	(size nil)
	(alignment 1)
	(defflag t)
	(members nil)
	)

(defrecord cs-type-member
	(handle nil)
	(offset 0)
	(type nil)
	(init nil)
	)

(defmacro make*-cs-type (&rest x) `(list ,@ x))
(defmacro make*-cs-type-member (&rest x) `(list ,@ x))
(defmacro roundup (what howmuch)
  `(setq ,what (1+ (boole 7  (1- ,howmuch) (1- ,what)))))

(defmacro cs-car (x)
  `(let ((z ,x)) (if (dtpr z) then (car z) else
		     (cs-error "got an atom when expecting list "
			       z "while parsing struct" cs-cur-name))))

(defmacro cs-cadr (x)
  `(let ((z (cdr ,x))) (if (dtpr z) then (car z) else
		     (cs-error "got an atom when expecting list "
			       z "while parsing struct" cs-cur-name))))
(defmacro cs-cddr (x)
  `(let ((z (cdr ,x))) (if (dtpr z) then (cdr z) else
		     (cs-error "got an atom when expecting list "
			       z "while parsing struct" cs-cur-name))))
(defmacro cs-cdar (x)
  `(let ((z (car ,x))) (if (dtpr z) then (cdr z) else
		     (cs-error "got an atom when expecting list "
			       z "while parsing struct" cs-cur-name))))
(defmacro cs-caar (x)
  `(let ((z (car ,x))) (if (dtpr z) then (car z) else
		     (cs-error "got an atom when expecting list "
			       z "while parsing struct" cs-cur-name))))

;; cs-parse-struct, cs-parse-member, and cs-peruse-member are
;; internal functions used in traversing the description of structure
;; and building an internal database describing it.
;; other functions come along later and generate macros for
;; referencing the members of the strcucture.

(defun cs-parse-struct (arg handle)
  (let (
	(union-or-struct (cs-car arg))
	(name (cs-cadr arg))
	(cs-cur-name handle)
	(rest (cs-cddr arg))
	(mysize 0)
	(check))
       
       (setq check (get name c-structure-indicator))
       
       (if (and check (cs-type-defflag check)) then
	   (cs-error "Recursively Defining C-Structure"))
       
       (if (and (null rest) (null check))
	   then (cs-error "unknown size for structure element of structure"))
       
       (if (null rest) then
	   (progn
	    (roundup cs-cur-alignment (cs-type-alignment check))
	    (roundup cs-cur-base cs-cur-alignment)
	    (setq mysize (cs-type-size check)))
	   
	   else
	   (progn
	    (push name cs-structs-in-progress)
	    (putprop name (make-cs-type name name) c-structure-indicator)
	    (do ((cs-cur-base 0)
		 (cs-cur-alignment 1)
		 (cs-cur-size 0)
		 (member)
		 (decl)
		 (ll))
		
		((null rest)
		 (roundup mysize cs-cur-alignment)
		 (putprop
		  name
		  (make*-cs-type name mysize cs-cur-alignment nil ll)
		  c-structure-indicator))
		
		(setq member (cs-caar rest) decl (cs-cdar rest))
		(if (symbolp member) then (setq member `(,member)))
		(setq ll
		      (nconc
		       (mapcar
			#'(lambda (x)
				  (setq x (cs-parse-dcl decl x))
				  (caseq union-or-struct
					 (struct
					  (setq cs-cur-base
						(+ cs-cur-base cs-cur-size))
					  (setq mysize cs-cur-base))
					 (t
					  (setq mysize
						(max mysize cs-cur-size))))
				  x)
			member)
		       ll))
		(pop rest)
		)))
       (setq cs-cur-size mysize)
       (if handle then
	   (make*-cs-type-member
	    handle cs-cur-base `(,union-or-struct ,name) nil)
	   else nil
	   )))

(defun cs-parse-dcl (rest handle)
  (let (
	(unit)
	(type (cs-car rest))
	(size 0))
       (if
	(symbolp type) then 
	(progn
	 (caseq type
		((char unsigned-char u_char) 
		 (setq cs-cur-size 1))
		((short unsigned-short u_short)
		 (setq cs-cur-size 2)
		 (roundup cs-cur-base 2)
		 (roundup cs-cur-alignment 2))
		((long int * float unsigned-long unsigned-int u_long u_int)
		 (setq cs-cur-size 4)
		 (roundup cs-cur-base cs-long-alignment)
		 (roundup cs-cur-alignment cs-long-alignment)
		 (if (eq type '*) (cs-peruse-dcl (cdr rest))))
		(double
		 (setq cs-cur-size 8)
		 (roundup cs-cur-base cs-long-alignment)
		 (roundup cs-cur-alignment cs-long-alignment))
		(t
		 (cs-error "don't know how to handle this type")))
	 (make*-cs-type-member handle cs-cur-base type nil))
	elseif (symbolp (car type)) then
	(caseq (car type)
	       ((struct union)
		(cs-parse-struct type handle))
	       (array
		(setq size (apply '* (cdr type))
		      unit (cs-parse-dcl (cdr rest) handle)
		      cs-cur-size (* size cs-cur-size))
		(setf (cs-type-member-type unit)
		      `(array ,(cs-type-member-type unit) ,@(cdr type)))
		unit)
	       (t (cs-error "don't know how to handle this type"))))))

(defun cs-peruse-dcl (tail)
  (if (null tail) then nil
      elseif (symbolp (cs-car tail)) then
      (caseq (car tail)
	     ((function *) (cs-peruse-dcl (cdr tail)))
	     (t nil))
      elseif (and (dtpr (car tail)) (symbolp (caar tail))) then
      (caseq (caar tail)
	     (array (cs-peruse-dcl (cdr tail)))
	     ((struct union)
	      (if (cddar tail) then
		  (let ((cs-cur-size 0)(cs-cur-aligment 1)(cs-cur-base 1))
		       (cs-parse-struct (car tail) nil)))))))

;; cs-gen*-member and cs-gen-member are called to generate a
;; macro (or several macros) for each member of a structure.
;; they are not invoked by users.  cs-gen-dims does get invoked
;; while somebody is compiling (foo->subarray struct index1 [indexn ..])
;;
;; the * forms are for pursuing pointers to structures.

(defun cs-gen*-member (member)
  (let (
	(handle (cs-type-member-handle member))
	(offset (cs-type-member-offset member))
	(type (cs-type-member-type member))
	(code)
	)
       (if (dtpr type) then
	   (caseq
	    (car type)
	    (array
	     `(defmacro
	       ,(concat '* cs-cur-name '-> handle) (x &rest y)
	       (cs-gen*-dims ',(cadr type) ',(cddr type) ,offset x y)))
	    ((struct union)
	     (let ((cs-cur-name (concat '* cs-cur-name '-> handle))
		   (structsize
		    (cs-type-size (get (cadr type) c-structure-indicator)))
		   (cs-cur-base offset))
		  (append
		   `(progn 'compile
			   (defmacro ,cs-cur-name (x)
				     `(cs-get-out-struct
						x ,,offset ,,structsize)))
		   (mapcar
		    'cs-gen-member
		    (cs-type-members (get (cadr type) 'cs-ind))))))
	    (t (cs-error "internal botch in generating macros" cs-cur-handle)))
	   else
	   `(defmacro
	     ,(concat '* cs-cur-name '-> handle) (x)
	     ,(caseq type
		     (char ``(crefi-byte ,x ,,offset))
		     ((unsigned-char u_char)
		      ``(crefi-ubyte ,x ,,offset))
		     (short ``(crefi-word ,x ,,offset))
		     ((unsigned-short u_short)
		      ``(crefi-uword ,x ,,offset))
		     ((int long *)
		      ``(crefi-long ,x ,,offset))
		     ((float double)
		      (setq handle (concat 'crefi- type))
		      ``(,',handle ,x ,,offset))
		     (t
		      ``(+ (maknum ,x) ,,offset)))))))

(defun cs-gen*-dims (type dims offset parent indices)
  (prog (num calc coef)
	(if (null (eq (length dims) (length indices))) then
	    (cs-error "improper array reference in substructure"))
	(setq num (cs-array-size type)
	      coef (append dims (ncons (car num)))
	      calc `(+ ,offset
		       ,@(mapcar
				 '(lambda (x) (pop coef)
					  `(* ,(apply '* coef) ,x))
			 indices))
	      )
	(return 
	 (caseq (cdr num)
		((long char word float double uchar uword)
		 `(,(concat 'crefi- (cdr num)) ,parent ,calc))
		(t
		 `(+ ,parent ,@(cdr calc))))
	 )))

(defun cs-array-size (x)
  (if (symbolp x) then
      (caseq x
	     ((* long int unsigned-int u_int) (cons 4 'long))
	     (float (cons 4 x))
	     (double (cons 8 x))
	     (char (cons 1 x))
	     ((unsigned-char u_char) (cons 1 'uchar))
	     ((unsigned-short u_short) (cons 2 'uword))
	     (short (cons 2 'word)))
      else
      (caseq (car x)
	     ((struct union)
	      (cons
	       (cs-type-size (get (cadr x) c-structure-indicator))
	       'struct))
	     (array
	      (let (xx (cs-array-size (cadr x)))
		   (setf (car xx) (apply '* (cons (car xx) (cddr x)))))))))

(defun cs-gen-member (member)
  (let (
	(handle (cs-type-member-handle member))
	(offset (+ cs-cur-base (cs-type-member-offset member)))
	(type (cs-type-member-type member))
	(myname cs-cur-name)
	)
       (if (symbolp type) then
	   `(defmacro
	     ,(concat myname '-> handle) (x)
	     ,(caseq type
		     (char ``(vrefi-byte ,x ,,offset))
		     ((unsigned-char u_char)
		      ``(crefi-ubyte (maknum ,x) ,,offset))
		     (short ``(vrefi-word ,x ,,(/ offset 2)))
		     ((unsigned-short u_short)
		      ``(crefi-uword (maknum ,x) ,,offset))
		     ((int long *)
		      ``(vrefi-long ,x ,,(/ offset 4)))
		     ((float double)
		      (setq handle (concat 'crefi- type))
		      ``(,',handle (maknum ,x) ,,offset))
		     (t ``(+ (maknum ,x) ,,offset))))
	   else
	   (caseq (car type)
		  (array
		   `(defmacro
		     ,(concat cs-cur-name '-> handle) (x &rest y)
		     (cs-gen-dims
		      ',(cadr type) ',(cddr type) ,offset x y)))
		  ((struct union)
		   (let ((cs-cur-name (concat myname '-> handle))
			 (structsize
			  (cs-type-size
			   (get (cadr type) c-structure-indicator)))
			 (cs-cur-base offset))
			(append
			 `(progn 'compile
				 (defmacro
				  ,cs-cur-name (x)
				  `(cs-get-out-struct (maknum x)
						      ,,offset ,,structsize)))
			 (mapcar
			  'cs-gen-member
			  (cs-type-members (get (cadr type) 'cs-ind))))))
		  ))))


(defun cs-gen-dims (type dims offset parent indices)
  (prog (num calc coefs)
	(if (null (eq (length dims) (length indices))) then
	    (cs-error "improper array reference in substructure"))
	(setq num (cs-array-size type)
	      coefs dims
	      calc (mapcar
		    '(lambda (x) (pop coefs)
			     (if (null coefs) then x
				 else `(* ,(apply '* coefs) ,x)))
		    indices))
	(return 
	 (caseq (cdr num)
		((long char word)
		 `(,(concat 'vrefi- (cdr num))
		    ,parent (+ ,(/ offset (car num)) ,@calc)))
		(t
		 (cs-gen*-dims
		  type dims offset `(maknum ,parent) indices))
		))))

;; cs-gen-structs does the overall creation of the macros
;; once the entire declaration has been parsed.  It is not
;; user visible either.

(defun cs-gen-structs nil
  (let (
	(todo cs-structs-in-progress))
       (setq cs-structs-in-progress nil)
       (mapcan 'cs-do-one-struct todo)))

(defun cs-do-one-struct (cs-cur-name)
  (let (
	(cs-cur-base 0)
	(ll (cs-type-members (get cs-cur-name c-structure-indicator))))
       (nconc
	`((defmacro ,(concat 'make- cs-cur-name) (&rest args)
		    (cs-make-instance-of ',cs-cur-name args)))
	(mapcar 'cs-gen-member ll)
	(mapcar 'cs-gen*-member ll))))

(defun cs-make-instance-of (recname args)
   ;; called to expand a make- form.
   ;; recname is the name of a structure
   ; convert to an assq list, verifing field names
   (let* ((cs-record (get recname c-structure-indicator))
	  (fields (cs-type-members cs-record))
	  (given))
      (do ((xx args (cddr xx)))
	  ((null xx))
	  (if (assq (car xx) fields)
	     then (push (cons (car xx) (cadr xx)) given)
	     else (cs-error " for record " recname
			   ", this field doesn't exist " (car xx))))
      ;; now build a list of values.
      (do ((xx fields (cdr xx))
	   (got)
	   (res
	    `(((x (new-vectori-byte ,(cs-type-size cs-record)))) let))
	   )
	  ((null xx)
	   ;; now we have a list of values to compute to build this
	   ;; form.
	   (push 'x res)
	   (reverse res))
	  (let (
		(handle (cs-type-member-handle (car xx))))
	       (setq got (assq handle given))
	       (if (null got) then
		   (setq got (cs-type-member-init (car xx)))
		   else (setq got (cdr got)))
	       (if got then
		   (push
		    `(setf (,(concat recname '-> handle) x) ,got)
		    res
		    )))
	  )))

;--- cref
; refernces an element of a C-structure given base address as a boxed int.
;   (vref 'vect 'index)
;
(defmacro cref-macro (base offset class)
  `(cond ((not (fixp ,base))
	  (cs-error "cref: base address not passed as boxed integer" ,base))
	 ((not (fixp ,offset))
	  (cs-error "cref: non fixnum offset " ,offset))
	 (t (int:vref ,base ,offset ,class))))

(defun crefi-byte (vect ind)
   (cref-macro vect ind 4))

(defun crefi-ubyte (vect ind)
   (boole 1 (cref-macro vect ind 4) 255)) 

(defun crefi-word (vect ind)
   (cref-macro vect ind 5))

(defun crefi-uword (vect ind)
   (boole 1 (cref-macro vect ind 5) 65535))

(defun crefi-long (vect ind)
   (cref-macro vect ind 6))

(defun crefi-float (vect ind)
   (cref-macro vect ind 7))

(defun crefi-double (vect ind)
   (cref-macro vect ind 8))


;--- cseti
; use:
;	(cseti-<size> 'base 'offset 'value)
;
(defmacro cset-macro (base offset value class)
  `(cond ((not (fixp ,base))
	  (cs-error "cref: base address not passed as boxed integer" ,base))
	 ((not (fixp ,offset))
	  (cs-error "cref: non fixnum offset " ,offset))
	 (t (int:vset ,base ,offset ,value ,class))))

(defun cseti-byte (vect ind value)
   (cset-macro vect ind value 4))

(defun cseti-word (vect ind value)
   (cset-macro vect ind value 5))

(defun cseti-long (vect ind value)
   (cset-macro vect ind value 6))

(defun cseti-float (vect ind value)
   (cset-macro vect ind value 7))

(defun cseti-double (vect ind value)
   (cset-macro vect ind value 8))

(eval-when (load eval)
  (if (null (getd 'cs-blcopy)) then
      (getaddress "_strncpy" 'cs-blcopy "c-function")))

(defun cs-get-out-struct (vector* offset size)
  (let ((x (new-vectori-byte size)))
       (cs-blcopy x (+ vector* offset) size)
       x))

(defun cs-put-back-struct (vector* offset size smaller)
  (cs-blcopy (+ vector* offset) (maknum smaller) size))

(defsetf crefi-byte (e v) `(cseti-byte ,(cadr e) ,(caddr e) ,v))
(defsetf crefi-ubyte (e v) `(cseti-byte ,(cadr e) ,(caddr e) ,v))
(defsetf crefi-word (e v) `(cseti-word ,(cadr e) ,(caddr e) ,v))
(defsetf crefi-uword (e v) `(cseti-word ,(cadr e) ,(caddr e) ,v))
(defsetf crefi-long (e v) `(cseti-long ,(cadr e) ,(caddr e) ,v))
(defsetf crefi-float (e v) `(cseti-float ,(cadr e) ,(caddr e) ,v))
(defsetf crefi-double (e v) `(cseti-double ,(cadr e) ,(caddr e) ,v))
(defsetf cs-get-out-struct (e v)
  `(cs-put-back-structs ,(cadr e) ,(caddr e) ,(cadddr e) ,v))

(declare (macros t))

(defmacro test-c-declare (&rest stuff)
  (do ((cs-cur-size 0)
	(cs-cur-base 0)
	(cs-cur-alignment 0)
	(cs-cur-decl)
	)
      ((null stuff)
       `(setq l ,@(cs-gen-structs)))
      (setq cs-cur-decl (car stuff) stuff (cdr stuff))
      (cs-parse-struct cs-cur-decl nil)))

(defmacro c-declare (&rest stuff)
  (do ((cs-cur-size 0)
	(cs-cur-base 0)
	(cs-cur-alignment 0)
	(cs-cur-decl)
	)
      ((null stuff)
       `(progn 'compile ,@(cs-gen-structs)))
      (setq cs-cur-decl (car stuff) stuff (cdr stuff))
      (cs-parse-struct cs-cur-decl nil)))
