(includef 'declar.l)
(comment Mapping)

;;;::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
;;;
;;;		          Mapping
;;;
;;;::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::


(macro MAPAPPEND (x)
   ;; similar to MAPCAN, except appending is non-destructive.
   (list 'apply (list 'quote 'append) (cons 'mapcar (cdr x))))

(macro NMAPCAR (s)
          ;; like MAPCAR, except reuses cells of the list.
           (sublis (list (cons 'fcall (cond ((and (not (atom (cadr s)))(eq (caadr s) 'quote))
                                             (list (cadadr s) '(car */#*/ l/ */#*)))
                                            (t (list 'funcall (cadr s) '(car */#*/ l/ */#*)))))
                         (cons 'arg (caddr s))
                         '(l . */#*/ l/ */#*)
                         '(ll . */#*/ ll/ */#*))
                   '((lambda (ll)
                             (do ((l ll (cdr l)))
                                 ((null l)ll)
                                 (rplaca l fcall)))
                     arg)))

(macro FOREACH (l)
      ;; (foreach x <list> F1 ... Fn)
      ;;   returns a list of (eval Fi) for each x in <list>.
       (prog (var set forms)
         (setq var (cadr l) set (caddr l) forms (cdddr l))
         (return (list 'do (list (list '*do* set (list 'cdr '*do*))
                                 (list var)
                                 '(*done*))
                       (list (list 'null '*do*) '(nreverse *done*))
                       (list 'setq var (list 'car '*do*))
                       (list 'setq '*done*
                                   (list 'cons (cond((> (length forms) 1)
                                                     (cons 'progn forms))
                                                    ;; there is only one form.
                                                    ((car forms)))
                                               '*done*))))))


(macro DO-FOREACH (l)
 ;; (do-foreach x <list> F1 ... Fn)
 ;;       is equivalent in effect to
 ;; (mapc '(lambda (x) F1 ... Fn) <list>)
	(prog (var)
		(setq var (cadr l))
		(return
                   (append
                        (list 'do (list (list '*do* (caddr l) (list 'cdr '*do*))
                                        (list var))
				  (list (list 'null '*do*))
				  (list 'setq var (list 'car '*do*)))
                        (cdddr l)))))


(comment Filtering)
;;;*****************************************************************
;;;                          FILTERS
;;;*****************************************************************

(macro FILTER (l)
       ;; (FILTER x <list> p1 ... pn) returns only those members of the <list>
       ;;   for which all the predicates evaluate to non-NIL.
	(prog (var forms)
		(setq var (cadr l) forms (cdddr l))
		(return (list 'do (list (list '*do (caddr l) (list 'cdr '*do))
                                        (list var)
                                        (list '*done))
				  (list (list 'null '*do) (list 'nreverse '*done))
				  (list 'setq var (list 'car '*do))
				  (list 'and (cond((> (length forms) 1)
                                                   (cons 'and forms))
                                                  ((car forms)))
                                             (list 'setq '*done (list 'cons var '*done)))))))


(macro FORALL (l)
   ;; (FORALL x <list> P1 ... Pn) returns T iff all predicates Pi
   ;;    evaluate to non-NIL for every x in <list>.
	(prog (var set forms)
		(setq var (cadr l) set (caddr l) forms (cdddr l))
		(return (list 'do (list (list '*do* set (list 'cdr '*do*)) (list var))
				  (list (list 'null '*do*) t)
				  (list 'setq var (list 'car '*do*))
				  (list 'or (cond((> (length forms) 1)
                                                  (cons 'and forms))
                                                 ((car forms)))
                                        '(return nil))))))


(macro EXISTS (l)
;;(EXISTS x <list> p1 ... pn) returns non-NIL iff predicates evaluate to non-NIL
;; for at least one x in <list>.
;; The value returned in this case is the first member of the <list> for which
;; all predicates were true.  *BUG* This value might be NIL!
	(prog (var set forms)
		(setq var (cadr l) set (caddr l) forms (cdddr l))
		(return (list 'do (list (list '*do* set (list 'cdr '*do*)) (list var))
				  (list (list 'null '*do*) nil)
				  (list 'setq var (list 'car '*do*))
				  (list 'and (cond((> (length forms) 1)
                                                   (cons 'and forms))
                                                  ((car forms)))
                                        (list 'return var))))))

(macro CLASSIFY (s)
       ;;
       ;; (CLASSIFY <func> <list>)
       ;;
       ;; classify given list according to values of given function
       ;; return A-LIST which associates each distinct (under EQUAL) functional
       ;; value with list of elements from given list which evaluate to that value
       ;; note: since values may be non-atomic, in general ASSOC should
       ;;       by used to retrieve from a-list
       ;; note: may be used sytnactically just like MAPC
      (sublis
       (list (cons 'fcall
                   ;; to improve compilation
                   (cond ((and (not (atom (cadr s))) (eq (caadr s) 'quote))
			  (list (cadadr s) '*/#*/ e/ */#*))
			 (t (list 'funcall (cadr s) '*/#*/ e/ */#*))))
             (cons 'arg (caddr s))
             '(alist . */#*/ l/ */#*)
             '(a . */#*/ a/ */#*)
             '(v . */#*/ v/ */#*)
             '(e . */#*/ e/ */#*))

	 '(prog (alist a v)
                (mapc '(lambda (e)
                               (setq v fcall
                                     a (assoc v alist))
                               (cond (a (rplacd a (cons e (cdr a))))
                                     (t (setq alist (cons (cons v (list e)) alist)))))
                      arg)
                (return alist))))

(macro SELECT1 (s)
      ;;
      ;; (SELECT1 <pred> <list>)
      ;;
      ;; return first element encountered in list that satisfies predicate,
      ;; otherwise NIL.  (Note case were nil is a member of the list.)
      ;; Note: syntactically just like MAPC.
    (list 'do (list (list '*/#*/ l/ */#* (caddr s) (list 'cdr '*/#*/ l/ */#*)))
              (list (list 'null '*/#*/ l/ */#*))
              (list 'and
                    ;; to improve compilation
                    (cond ((and (not (atom (cadr s)))
                                (eq (caadr s) 'quote))
                            (list (cadadr s) (list 'car '*/#*/ l/ */#*)))
                          (t (list 'funcall (cadr s) (list 'car '*/#*/ l/ */#*))))
                    (list 'return (list 'car '*/#*/ l/ */#*)))))

(macro SELECT (s)
       ;;
       ;; (SELECT <pred> <list>)
       ;;
       ;; return list of elements from given list that satisfy given predicate
       ;; note: may be used syntactically just like MAPC
       ;; note: if want elements in same order as original list, NREVERSE result
    (list 'prog (list '*/#*/ h/ */#*)
                (list 'mapc (list 'quote 
                              (list 'lambda (list '*/#*/ e/ */#*)
                                            (list 'and
                                                  ;; to improve compilation
                                                  (cond ((and (not (atom (cadr s)))
                                                              (eq (caadr s) 'quote))
                                                         (list (cadadr s) '*/#*/ e/ */#*))
                                                        (t (list 'funcall (cadr s) '*/#*/ e/ */#*)))
                                                  (list 'setq '*/#*/ h/ */#* 
                                                              (list 'cons '*/#*/ e/ */#* '*/#*/ h/ */#*)))))
                           (caddr s))
                (list 'return '*/#*/ h/ */#*)))

(macro NSELECT (s)
       ;; just like SELECT, except modifies list argument using RPLAC.
       ;; Therefore, the list is returned in the same order.
       (sublis
           (list  (cons 'predcall
                        ;; to improve compilation
                        (cond ((and (not (atom (cadr s)))
                                    (eq (caadr s) 'quote))
                               (list (cadadr s)(list 'car '*/#*/ l/ */#*)))
                              (t (list 'funcall (cadr s)(list 'car '*/#*/ l/ */#*)))))
                 (cons 'arg (caddr s))
                 '(l . */#*/ l/ */#*)
                 '(ll . */#*/ ll/ */#*)
                 '(lll . */#*/ lll/ */#*))

           '(do ((l arg (cdr l))
                 (ll)
                 (lll)) 
                ((null l) lll)
                (or lll (setq lll l))
                (cond (predcall (setq ll l))
                      (t (cond (ll (rplacd ll (cdr l))
                                   (setq l ll))
                               (t (setq lll (cdr l)))))))))
(comment Control Primitives)
;;;*****************************************************************
;;;
;;;	              Control Primitives
;;;
;;;*****************************************************************

;;; Alternate syntax for LAMBDA expressions.

(macro FOR (x)
  ;;  E.g.,  (FOR (A (+ 1 1) B (+ 2 2)) (- B A)) = 3.
  ;;  (FOR (<name1> <value1> ... <nameN> <valueN>) ...forms... )
  ;; returns output of last form.  The assignments are done in parallel
  ;;  (like LAMBDA, into which this expands).
      (do ((varbind (cadr x))(varlist)(bindlist))
          ((null varbind)
           (cons (list* 'lambda (nreverse varlist) (cddr x))
                 (nreverse bindlist)))
          (push (pop varbind) varlist)
          (push (pop varbind) bindlist)))


(macro PROGI (s)
       ;;
       ;; (progi (a x b y ...) b1 b2 ...)
       ;;      => (prog (a b ...) (setq a x b y ...) (return (progn b1 b2 ...)))
       ;;
          (list 'prog
                (do ((v (cadr s)(cddr v))
                     (args))
                    ((null v)(nreverse args))
                    (setq args (cons (car v) args)))
                (cons 'setq (cadr s))
                (list 'return (cons 'progn (cddr s)))))

(macro PROG1 (form)
       (list* 'prog2 'nil (cdr form)))

(macro IF (form)
   ;; (IF x a b c) => (AND x (PROGN a b c))
       (prog (then-clauses)
          (setq then-clauses (cddr form))
          (return (list 'AND
                        (cadr form)
                        (cond((cdr then-clauses)
                              (cons 'PROGN then-clauses))
                             ((car then-clauses)))))))

(macro IFNOT (form)
   ;; (IFNOT x a b c) => (OR x (PROGN a b c))
       (prog (then-clauses)
          (setq then-clauses (cddr form))
          (return (list 'OR
                        (cadr form)
                        (cond((cdr then-clauses)
                              (cons 'PROGN then-clauses))
                             ((car then-clauses)))))))
