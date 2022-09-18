;	flavors:	an implementatioin of the MIT Lisp Machine
;			flavors package in Franz Lisp
;	(Copyright (c)	Richard J. Wood	May 1982)
;	initial release:	01/18/82		Rich Wood
;	01/19/82	added 	:documentation option to defflavor
;				describe-flavor, compile-file, compile functions
;	05/04/82	added	:default-init-plist to defflavor
;	06/11/82	changed execute flavor to use rplacad to avoid
;			generating a cons cell for each flavor call
;	10/14/82	added stripped flavors, modified describe, added
;			<< and >>, declared functions local.
;	10/22/82	Re-released by Randy Trigg and Liz Allen
(eval-when (compile) (load 'uommacs))
(declare
  (special
	*all-flavor-names*		; list of defined flavors
	*flavor-temp*			; global temp
	*flavor-temp1*			; another global temp
	*defflavor-option-keywords*	; defflavor options
	*flavor-message-error-break*	; switch for error loop on undefined 
					; messages
	*flavor-lispobj-hook*		; switch for lispobj default flavor
	*flavor-auto-compile*		; switch for auto compile on combine
	*flavor-recombine-immediate-flavor-only*
					; limit effect of recombine
	*flavor-expand-macros*		; expand macros at combine time switch
	*flavor-flavor-properties*	; list of properties on flavors
	*flavor-method-properties*	; list of properties on methods
	*print-on-combine*		; if t, get msg every combine
	*combining-flavors*		; t if within a combine
	*debugging-flavors*		; assigns values to tags on flavors
	*FLAVOR-CONS*			; a constant cons cell for execute
	*dump-command-keywords*
	prinlength prinlevel port poport $ldprint
	)
  (localf gen-getable-methods gen-setable-methods combine-components
	  find-components find-all-components find-all-instance-vars
	  build-default-plist combine-methods find-all-methods make-ghost
	  get-flavor get-method1 get-symbol-position flavor-error describe1
	  mark-for-combining1 combine-flavor1 combine-it reset-method-table
	  build-method build-method1 build-method2 prep-args
	  build-combined-methods build-combined-method check-required-methods
	  build-instance compile-here compile-file-here dump-commands
	  dump-flavors clean-df-marks check-dump dump-flavor-props
	  dump-method-table dump-method dump-method-props dump-functions
	  strip-flavors strip-flavor unstrip-flavors unstrip-flavor
	  )
  )

(setq *defflavor-option-keywords* 
	'(:gettable-instance-variables 	; auto generate <i-var> methods
	  :settable-instance-variables	; auto generate set-<i-var> methods
	  :no-vanilla-flavor 		; don't mixin vanilla method
	  :required-methods		; list of required methods at combine time
	  :included-flavors		; list of flavors to include (different from components)
	  :default-init-plist		; list of values for initialization
	  :documentation		; documentation about the flavor
	  :never-strip			; don't strip when compiling (RHT)
	  ))
	
(defmacro flavor-option-keywordp (wd) `(memq ,wd *defflavor-option-keywords*))


(setq *flavor-flavor-properties*
	'(method-table			; ptr to method table
	  instance-variables		; complete list of instance variables
	  component-flavors		; complete list of component flavors
	  immediate-component-flavors	; component flavors in defflavor form
	  immediate-instance-variables	; instance variables in defflavor form
	  included-flavors		; list of :include'd flavors
	  type				; the constant 'flavor
	  vanilla?			; switch for inclusion of vanilla flavor
	  required-methods		; list of methods needed for mixin
	  combined?			; whether the flavor has been combined
	  combined-processing?		; whether the flavor is being combined
	  which-operations		; list of messages handled by flavor
	  immediate-init-plist		; defaults for this flavor only
	  documentation			; documentation about the flavor
	  strippedp			; flag for whether flavor has its
					; symbolic's stripped off (added 9/29/82
					; RHT)
	  just-loaded			; this flavor is being loaded via
					; .o file - don't reset method-table
					; when combining (10/5/82 RHT)
	  ))

(setq *flavor-method-properties*
	'(type				; the constant 'method
	  method-type			; one of (primary :before :after)
	  method-args			; a list of lambda variables for method
	  method-body			; the symbolic form of the body
					; or 'stripped if to be omitted
	  referenced-i-vars		; a list of instance vars referenced in the method
	  defining-flavor		; the flavor for which this was defmethoded
	))

(setq *dump-command-keywords* 
	'(:declares		; include declare in file
	  :flavors		; dump each flavor that follows
	  :functions		; dump each function definition that follows
	  :inits		; dump each of the following forms
	  ))

(defmacro cmd-option-keywordp (cmd) `(memq ,cmd *dump-command-keywords*))

(or (boundp '*all-flavor-names*) (setq *all-flavor-names* nil))
(or (boundp '*flavor-message-error-break*) 
		(setq *flavor-message-error-break* t))			; on
(or (boundp '*flavor-lispobj-hook*) (setq *flavor-lispobj-hook* nil)) 	; off
(or (boundp '*flavor-auto-compile*) (setq *flavor-auto-compile* nil)) 	; off
(or (boundp '*flavor-recombine-immediate-flavor-only*)
		(setq *flavor-recombine-immediate-flavor-only* nil))	; off
(or (boundp '*flavor-expand-macros*) (setq *flavor-expand-macros* t))	; on
(or (boundp '*print-on-combine*) (setq *print-on-combine* nil))		; on
(or (boundp '*debugging-flavors*) (setq *debugging-flavors* nil))	; off
(or (boundp '*combining-flavors*) (setq *combining-flavors* nil))
(setq *FLAVOR-CONS* (ncons nil))

; fl-rplacx
;	version of rplacx that returns value instead of hunk
(defun fl-rplacx (index hunk value) (rplacx index hunk value) value]

; instancep
;	predicate for determining it an object is an instance of a flavor
(defun instancep (instance)
	(and (hunkp instance) (eq (get (cxr 0 instance) 'type) 'flavor))
	]

; flavorp
;	predicate for determining if argument given is the name of a flavor
(defun flavorp (x)
  (and (atom x) (eq (get x 'type) 'flavor)))

(defmacro put-immediate-components (fl cp)
	`(putprop ,fl ,cp 'immediate-component-flavors)]
(defmacro get-immediate-components (fl) 
	`(get ,fl 'immediate-component-flavors)]

; we want all the macros after this point compiled.  Macros above this point
; should not be compiled - liz 10/15/82
(declare (macros t))

; defflavor 
;	flavor defining macro
;	fl-name	:	name of flavor being defined
;	i-vars	:	list of immediate instance variables
;	c-flavors :	list of immediate component flavors
;	options :	rest of args as options to defflavor
(defmacro defflavor (fl-name i-vars c-flavors &rest options &aux i-varnames)
   (and (get fl-name 'strippedp) ; added (9/29/82 RHT) - strip before redefining
        (unstrip-flavor fl-name))
   (setq i-vars (for iv in i-vars
			collect (cond ((atom iv) `(,iv nil))
		 		      (t `(,(car iv) ,(cadr iv)))))) 
   (setq i-varnames (for iv in i-vars collect (car iv)))
  `(progn 'compile
	(putprop ',fl-name nil 'method-table)		; head of plist
	(putprop ',fl-name nil 'instance-variables)	; 	''
	(putprop ',fl-name nil 'component-flavors)
	(putprop ',fl-name ',c-flavors 'immediate-component-flavors)
	(putprop ',fl-name ',i-vars 'immediate-instance-variables)
	(putprop ',fl-name 'flavor 'type)
	(putprop ',fl-name t 'vanilla?)			; mixin vanilla switch
	(putprop ',fl-name nil 'required-methods)	; list of required methods
	(putprop ',fl-name nil 'combined?)		; switch for combined flag
	(putprop ',fl-name nil 'combined-processing?)		; switch for combined-processing flag
	(putprop ',fl-name nil 'which-operations)
	(putprop ',fl-name nil 'immediate-init-plist)
	,@(process-options fl-name options i-varnames)
	(or (memq ',fl-name *all-flavor-names*)
	    (setq *all-flavor-names* (cons ',fl-name *all-flavor-names*)))
	',fl-name]
	
(defun process-options (flavor opt-lst i-var-lst)
	(for while opt-lst join
		(selectq (car opt-lst)
		  (:gettable-instance-variables
			(for giv on (cdr opt-lst) 
			     until (flavor-option-keywordp (car giv))
			     collect (car giv)
			     finally (setq opt-lst giv)
				     (gen-getable-methods flavor
						$$val i-var-lst)))
		  (:settable-instance-variables
			(for siv on (cdr opt-lst) 
			     until (flavor-option-keywordp (car siv))
			     collect (car siv)
			     finally (setq opt-lst siv)
				     (gen-setable-methods flavor
						$$val i-var-lst)))
		  (:included-flavors
			(for if on (cdr opt-lst)
			     until (flavor-option-keywordp (car if))
			     collect (car if)
			     finally (setq opt-lst if)
				     `((putprop ',flavor ',$$val 'included-flavors))))
		  (:no-vanilla-flavor
			(setq opt-lst (cdr opt-lst))
			`((remprop ',flavor 'vanilla?)))
		  (:never-strip			     ; 10/5/82 RHT prevents
			(setq opt-lst (cdr opt-lst)) ; stripping at compile time
			`((putprop ',flavor t 'nostrip-when-compile)))
		  (:required-methods
			(for rm on (cdr opt-lst)
			     until (flavor-option-keywordp (car rm))
			     collect (car rm)
			     finally (setq opt-lst rm)
				     `((putprop ',flavor ',$$val 'required-methods))))
		  (:default-init-plist
			(for bind (init (cdr opt-lst) (cddr init))
			     until (or (not init) 
				       (flavor-option-keywordp (car init)))
			     collect (cons (car init) (cadr init))
			     finally (setq opt-lst init)
				     `((putprop ',flavor ',$$val 
						'immediate-init-plist))))
		  (:documentation
			(for doc on (cdr opt-lst)
			     until (flavor-option-keywordp (car doc))
			     collect (car doc)
			     finally (setq opt-lst doc)
				     `((putprop ',flavor ',$$val 'documentation))))
		  (progn (flavor-error
			  `("flavor option error: unrecognized keyword "
			    ,(car opt-lst)))
			 (setq opt-lst (cdr opt-lst))
			 nil)))
	]

(defun gen-getable-methods (flavor g-ivars all-var-lst)
	(cond ((null g-ivars) (setq g-ivars all-var-lst))
	      (t (setq g-ivars
		   (for giv in g-ivars join 
			(cond ((memq giv all-var-lst) (ncons giv))
			      (t (flavor-error
				  `(":gettable-instance-variables error: "
				    ,giv
				    " in not an immediate instance variable of "
				    ,flavor))))))))
	(for i-var in g-ivars
		collect `(defmethod (,flavor ,i-var) nil ,i-var))
	]

(defun gen-setable-methods (flavor s-ivars all-var-lst)
	(cond ((null s-ivars) (setq s-ivars all-var-lst))
	      (t (setq s-ivars
		   (for siv in s-ivars join 
			(cond ((memq siv all-var-lst) (ncons siv))
			      (t (flavor-error
				  `(":settable-instance-variables error: "
				    ,siv
				    " in not an immediate instance variable of "
				    ,flavor))))))))
	(for i-var in s-ivars
		collect `(defmethod (,flavor ,(concat '|set-| i-var))
				(newval)
				(setq ,i-var newval)))
	]

; combine-components
;	finds all the components for a flavor, that is, the component flavors,
;	the included flavors, and the vanilla flavor (if applicable)
(defun combine-components (flavor)
	(setq *flavor-temp*
		(nconc (setq *flavor-temp1*
				(find-components flavor))
		       (for if in *flavor-temp1*
			    join (find-all-components if)
			    finally (and (get flavor 'vanilla?)
					 (setq $$val 
					   (nconc $$val (ncons 'vanilla))))
				    $$val)))
	(for fl in *flavor-temp* 
	     do (remprop fl 'fc-mark)
		(remprop fl 'fi-mark))
	*flavor-temp*]

; find-components
;	finds all the components of a given flavor using a recursive
;	depth first tree walk 
(defun find-components (flavor)
	(cond ((get flavor 'fc-mark) nil)
	      ((null (setq *flavor-temp* (get-immediate-components flavor)))
			(putprop flavor t 'fc-mark)
			(ncons flavor))
	      (t (putprop flavor t 'fc-mark)
		 (for fl in *flavor-temp* 
			join (find-components fl)
			finally (cons flavor $$val))))
	]

; find-all-components
;	returns a list of both the component and included flavors of a
;	given flavor (if they haven't been traversed before)
(defun find-all-components (flavor)
	(cond ((get flavor 'fc-mark) 
			(cond ((get flavor 'fi-mark) nil)
			      (t (putprop flavor t 'fi-mark)
				 (for fl in (get flavor 'included-flavors)
				      join (find-all-components fl)))))
	      (t (nconc (find-components flavor)
			(find-all-components flavor))))
	]

; find-all-instance-vars 
;	returns a list of all the instance variables of the component-flavors
;	of the given flavor.  The list is in the reverse order of the component
;	flavors, but within each flavor the variables are contributed in the
;	same order that they were originally specified
(defun find-all-instance-vars (flavor)
	(for bind (var-temp) (val-lst)
	     cfl in (get flavor 'component-flavors)
	     collect 
		(prog1 
		  (for i-var in (get cfl 'immediate-instance-variables)
		       join (cond ((null (get (car i-var) 'faiv-mark))
				     (putprop (car i-var) t 'faiv-mark)
				     (ncons 
				       (cond ((setq *flavor-temp*
						(assq (car i-var) val-lst))
						(list (car i-var)
						      (cdr *flavor-temp*)))
					     (t i-var))))))
		   (for ipair in (get cfl 'immediate-init-plist)
		        do (cond ((get (car ipair) 'faiv-mark))
		  	         ((assq (car ipair) val-lst))
			         (t (setq val-lst (cons ipair val-lst))))))
	      finally (setq $$val (for i-set in (reverse $$val) join i-set))
	 	      (for bind (pos 1 (add1 pos)) 
			   i-var in $$val 
			   collect (remprop (car i-var) 'faiv-mark)
			 	   `(,(car i-var) ,pos ,(cadr i-var))))
	]

; build-default-plist
;	returns an assoc list of the form (<var> . <init-val>) in the
;	order of combination for all the variables in the component
;	list.  Note this only contains values explicitly stated in
;	the option :default-init-plist.  Instance variables can still
;	receive defaults from the defflavor form
(defun build-default-plist (flavor)
	(for cfl in (get flavor 'component-flavors)
	     join (for i-var in (get cfl 'immediate-init-plist)
		       join (cond ((null (get (car i-var) 'bdp-mark))
					(putprop (car i-var) t 'bdp-mark)
					(ncons i-var))))
	     finally (setq $$val (reverse $$val))
		     (for i-var in $$val 
			  do (remprop (car i-var) 'bdp-mark))
		     $$val)
	]

; combine-methods
;	returns a list of the intersection primary methods of a flavor
(defun combine-methods (flavor)
	(for initially (for m1 in (get flavor 'method-table)
			    do (and (caddr m1)		; must be primary
				    (putprop (car m1) 't 'cm-mark)))
	     cfl in (cdr (get flavor 'component-flavors))
	     join (for method in (get cfl 'method-table)
		       join (cond ((get (car method) 'cm-mark) nil)
				  ((and (caddr method)
					(eq (get (caddr method) 'type) 'method)
					(eq (get (caddr method) 
							'defining-flavor)
						cfl))
					(putprop (car method) t 'cm-mark)
					`((,(car method) ,(caddr method))))))
	     finally (for method in $$val do (remprop (car method) 'cm-mark))
		     (for m1 in (get flavor 'method-table)
			  do (remprop (car m1) 'cm-mark))
		     $$val)
	]


; find-all-methods
;	goes down the component-flavors list (actually only the cdr of
;	the component list and augments (or modifies each
;	entry in the method table to include an entry for the method
(defun find-all-methods (flavor)
  (let ((all-methods (combine-methods flavor))
	(inst-vars (get flavor 'instance-variables))
	ghost-name fl)
	(for method in all-methods 
	     do (cond ((variables-aligned inst-vars (get (cadr method)
							'referenced-i-vars))
	 		(add-method flavor (car method) (cadr method) 
				(get (cadr method) 'method-type)))

		      ; 10/5/82 RHT - assumes if just loaded .o file then
		      ; definition of ghost method must be around.
		      ((get flavor 'just-loaded)
		       (add-method flavor (car method) 
				   (concat '|ghost-| flavor '|-| (cadr method))
				   (get (cadr method) 'method-type)))

		      ; 9/29/82 RHT added to cut out if can't align and the
		      ; method came from a stripped flavor
		      ((get (setq fl (get (cadr method) 'defining-flavor)) 
			    'strippedp)
		       (msg '|Can't mix in for | flavor 
			    '| the compiled or stripped flavor | fl)
		       (error))

		      (t (add-method flavor (car method)
				     (make-ghost flavor (cadr method))
				     (get (cadr method) 'method-type)))))
	]

; make-ghost
;	create a ghost method - a copy of method but for a new flavor
;	was necessary because variables didn't align - returns the name
(defun make-ghost (flavor method)
  (let ((ghost-name (concat '|ghost-| flavor '|-| method))
	(inst-vars (get flavor 'instance-variables)))
   (funcall 'defun `(defun ,ghost-name
			   ,(prep-args (get method 'method-args))
			   ,@(build-method1 inst-vars 
					    (get method 'method-body))))
   ghost-name))

; variables-aligned
;	checks to see if two list of variables are aligned w.r.t. the
;	hunk that is being referenced.
(defun variables-aligned (ivar-lst ref-ivar-lst)
	(for rivar in ref-ivar-lst
		always (eq (cdr rivar) (cadr (assq (car rivar) ivar-lst))))
	]
			

; execute-flavor
;	entry point for execution of all flavors
(defun execute-flavor (instance message &rest message-args)
	(*catch 'execute-flavor-FRAME
	   (apply (get-method1 (get-flavor instance) message)
		  (rplacad *FLAVOR-CONS* instance message-args)))
	]

(putd '|<-| (getd 'execute-flavor))			; shorthand notation

; get-flavor
;	returns the name of the flavor for a given instance
;	if instance is not a flavor and lispobj hook is set then returns
;	'lispobj, other wise nil (which should then cause an error)
(defun get-flavor (instance)
	(cond ((and (hunkp instance) (eq (get (cxr 0 instance) 'type) 'flavor))
			(cxr 0 instance))
	      (*flavor-lispobj-hook* 'lispobj))
	]

; get-method1
;	returns the method for a given flavor and message
;	if none exists prints error message and traps (if flag set)
;	returns nil or value from error
;	liz 10/22/82
;	Modified to combine flavor and try to get the method again if the
;	flavor is uncombined
(defun get-method1 (flavor message)
	(or (cadr (assq message (get flavor 'method-table)))	; success
	    (if (null (get flavor 'combined?))
		(combine-flavor flavor)		; combine and try again
		(cadr (assq message (get flavor 'method-table))))
	    (*throw 'execute-flavor-FRAME	; otherwise, error
		    (flavor-error `(|undefined message: | ,message
				    | for flavor: | ,flavor))))
	]

; get-method
;	returns the method for a given flavor and message
;	if none exists prints message to that effect.
(defun get-method (flavor message)
	(or (cadr (assq message (get flavor 'method-table)))	; success
	    (if (null (get flavor 'combined?))
		(combine-flavor flavor)		; combine and try again
		(cadr (assq message (get flavor 'method-table))))
	    (msg "There is no method " message " for flavor " flavor))
	]

; get-handler-for
;	returns the name of the function for a given instance and message
;	returns nil if instance cannot handle message
(defun get-handler-for (instance message)
	(cadr (assq message (get (cxr 0 instance) 'method-table)))]

; symeval-in-instance
;	returns the value of the instance variable 'symbol' in 'instance'.
;	If symbol is not an instance variable returns nil if no-error-p
;	is non-nil.  Else signals an error (default)
(defun symeval-in-instance (instance symbol &optional no-error-p)
	(cond ((setq *flavor-temp* 
		 (get-symbol-position (cxr 0 instance) symbol))
		(cxr *flavor-temp* instance))
	      (no-error-p nil)
	      (t (flavor-error `(|symeval-in-instance: undefined symbol: |
				 ,symbol))))
	]

; set-in-instance
;	sets the instance symbol to the new value
;	signals error if symbol is not an instance variable
(defun set-in-instance (instance symbol value)
	(cond ((setq *flavor-temp*
		 (get-symbol-position (cxr 0 instance) symbol))
		 (fl-rplacx *flavor-temp* instance value))
	      (t (flavor-error `(|set-in-instance: undefined symbol: |
				 ,symbol))))
	]

; get-symbol-position
;	liz 10/22/82
;	added so that uncombined flavors may be combined
;	finds an instance symbol's position in a flavor
(defun get-symbol-position (flavor symbol)
  (or (cadr (assq symbol (get flavor 'instance-variables)))
      (if (null (get flavor 'combined?))
	  (combine-flavor flavor)
	  (cadr (assq symbol (get flavor 'instance-variables)))))
	]

; flavor-error
;	error loop for flavor errors, returns rest of line on macro ok
;	made flavor-error non-lexpr so it could be a local
;		10/14/82 - liz
(defun flavor-error (msgs)
	(and *flavor-message-error-break*
	  (progn
	     (for initially (msg '|flavor error:|)
		  x in msgs 
		  do (patom x) (patom '| |)
		  finally (terpri))
	     (lispbreak)))
	]

; describe-flavor
;	prints out some information about the flavor
;	liz - 10/25/82
;	do a combine before the describe-flavor if necessary
(defun describe-flavor (flavor)
	(cond ((flavorp flavor)
		 (or (get flavor 'combined?) (combine-flavor flavor))
		 (msg flavor '| is a flavor with:|)
		 (cond ((setq *flavor-temp* 
			      (get flavor 'instance-variables))
			  (msg '|   instance variables:|)
			  (for iv in *flavor-temp* 
			       bind (col 7 (mod (+ col 20) 60))
			       do (msg (C col) (car iv) -D)
			       finally (terpri)))
		       (t (msg '|   no instance variables|)))
	         (cond ((setq *flavor-temp*
			      (get flavor 'method-table))
			  (msg '|   methods for messages:|)
			  (for mthd in *flavor-temp*
			       bind (col 7 (mod (+ col 20) 60))
			       do (msg (C col) (car mthd) -D)
			       finally (terpri)))
		       (t (msg '|   no methods|)))
		 (cond ((setq *flavor-temp*
			      (get flavor 'documentation))
			  (msg '|   documentation:|)
			  (for doc in *flavor-temp*
			       bind (col 7 (mod (+ col 20) 60))
			       do (msg (C col) doc)))
		       (t (msg '|   no documentation|)))
	         (cond ((setq *flavor-temp*
			      (cdr (get flavor 'component-flavors)))
			  (msg '|and directly (or indirectly) depends on:|)
			  (for cfl in *flavor-temp*
			       bind (col 7 (mod (+ col 20) 60))
			       do (msg (C col) cfl -D)
			       finally (terpri)))
		       (t (msg '|and does not depend on any other flavors|))))
	      (t (msg flavor '| is not of type flavor|)))
	flavor]

; describe
;	prints out a description of whatever you give it
;	liz 10/23/82
;	combine flavor of instance if necessary
(defun describe (x)
	(cond ((instancep x)
			(or (get (cxr 0 x) 'combined?)
			    (combine-flavor (cxr 0 x)))
			(describe1 x)
			(msg '|, an object of flavor | 
				(cxr 0 x) N 
				'| has instance variable values: |)
			(for i in (get (cxr 0 x) 'instance-variables)
			     do (msg T (car i) '|:| (C 18) -D)
				(describe1 (cxr (cadr i) x))
				(terpri)))
	      ((flavorp x)
		 (describe-flavor x))
	      (t (describe1 x)
		 (terpri)))
	]

(defun describe1 (x)
	(cond ((instancep x) (msg '|<| (cxr 0 x) B (get-flavor-id x) '|>| -D))
	      ((atom x) (patom x))
	      ((and (cdr x) (not (dtpr (cdr x))))
			(patom '|(|)
			(describe1 (car x))
			(patom '| . |)
			(describe1 (cdr x))
			(patom '|)|))
	      (t (patom '|(|)
		 (describe1 (car x))
		 (for y in (cdr x) do (patom '| |) (describe1 y))
		 (patom '|)|))
	]

; get-flavor-id
;	10/9/82 liz
;	allows user to follow tags to find objects appearing as instance
;	variable values of other objects.  Only happens if debugging flag
;	is set.
(defun get-flavor-id (x)
  (let ((tag (concat 'f (maknum x))))
       (and *debugging-flavors* (set tag x))
       tag))

; defmethod
;	macro for defining a method for a flavor.  Defmethod simply
;	puts a bunch of properties on the method-symbol-name.  The
;	bulk of the work is done while combining the flavors
(defmacro defmethod (type-args method-args &rest method-body)
  (let ((flavor-name (car type-args))
	method-type message method-symbol-name)
        (and 				; (added 9/29/82 RHT) watch out for
         (get flavor-name 'strippedp)   ; defmethod for a stripped flavor
         (msg '|Warning: defining method for compiled or stripped flavor | 
	      flavor-name))
	(cond ((eq (length type-args) 2)
			(setq method-type 'primary
			      message (cadr type-args)))
	      (t (setq method-type (cadr type-args)
		       message (caddr type-args))))
	(setq method-symbol-name (concat flavor-name '|-| method-type '|-|
					 message '|-method|))
	`(progn 'compile
	   (mark-for-combining ',flavor-name)
	   (putprop ',method-symbol-name 'method 'type)
	   (putprop ',method-symbol-name ',flavor-name 'defining-flavor)
	   (putprop ',method-symbol-name ',method-type 'method-type)
	   (putprop ',method-symbol-name ',method-args 'method-args)
	   (putprop ',method-symbol-name ',method-body 'method-body)
	   (putprop ',method-symbol-name nil 'referenced-i-vars)
	   (add-method ',flavor-name ',message ',method-symbol-name 
			',method-type)
	   ',type-args))
	]

; mark-for-combining
;	this function is called each time defmethod is called and marks the
;	defining flavor as needing to be combined
; (defun mark-for-combining (flavor)
;   (and 			  	  ; (added 9/30/82 RHT) watch out for
;     (get flavor 'strippedp)       ; combines of stripped flavors
;     (msg '|Warning: will need to load symbolics for methods of flavor | flavor 
; 	 '| before combining|)) 
;   (putprop flavor nil 'combined?)
;   (putprop flavor nil 'combined-processing?)
;   (or *flavor-recombine-immediate-flavor-only*
;       (for fl in *all-flavor-names*
; 	   do (cond ((memq flavor (get fl 'component-flavors))
; 		     (putprop fl nil 'combined?)
; 		     (putprop fl nil 'combined-processing?)))))
; 	]
;
; mark-for-combining
;	liz 10/23/82
;	Function rewritten so that any flavor that has been marked for
;	combining will have its method table and its instance variables
;	list cleared; that way the flavor will always be recombined before
;	anything is done with it.
(defun mark-for-combining (flavor)
  (mark-for-combining1 flavor)
  (or *flavor-recombine-immediate-flavor-only*
      (for fl in *all-flavor-names*
	   when (memq flavor (get fl 'component-flavors))
	   do (mark-for-combining1 fl))))

; mark-for-combining1
;	this does the actual work
(defun mark-for-combining1 (flavor)
  (putprop flavor nil 'combined?)
  (putprop flavor nil 'combined-processing?)
  (putprop flavor nil 'instance-variables)
  (for meth in (get flavor 'method-table)
       do (rplaca (cdr meth) nil)))

; add-method
;	augments or updates the method table entry for a flavor message 
;	combination
(defun add-method (flavor message method method-type)
	(cond ((setq *flavor-temp* 
		  (assq message 
		     (setq *flavor-temp1* (get flavor 'method-table))))
			(selectq method-type
			  (primary	(rplaca (cddr *flavor-temp*) method))
			  (:before	(rplaca (cdddr *flavor-temp*) method))
			  (:after	(rplaca (cddddr *flavor-temp*) method))
			  nil))
	      (t (putprop flavor
		    (nconc *flavor-temp1*
		      (ncons
			(selectq method-type
			    (primary	(list message nil method nil nil))
			    (:before	(list message nil nil method nil))
			    (:after	(list message nil nil nil method))
			    nil)))
		      'method-table)))
	]

; combine-flavors
;	takes a list of flavors and combines each of the flavors in the list
(defun combine-flavors (lst-of-flavors)
	(for fl in *all-flavor-names* do (remprop fl 'combined-processing?))
	(for fl in lst-of-flavors do (combine-flavor1 fl))
	lst-of-flavors]

; combine-flavor 
;	9/29/82 RHT
; 	just here to make sure the 'combined-processing? flags get cleaned
;	up properly in case of an error - combine-flavor1 does all the work
(defun combine-flavor (flavor)
  (or *combining-flavors*
      (for fl in *all-flavor-names* do (remprop fl 'combined-processing?)))
  (combine-flavor1 flavor))

; combine-flavor1
;	does all the processing necessary to mix a flavor and calculate
;	all the instance-variables, methods, and gets the flavor in
;	a form ready to be used.  This function is called when a flavor
;	is created that is not combined, or when entered by combine-flavors
;	liz 10/22/82
;	Added clause to give user a chance to reload a stripped flavor
;	before trying to combine it.  Also added *combining-flavors* global
;	to prevent the 'combined-processing? properties from being removed
;	if there is a call to combine-favor while in the break.
(defun combine-flavor1 (flavor)
 (let ((*combining-flavors* t))
  (or (get flavor 'combined?)
      (get flavor 'combined-processing?)
      (if (and (get flavor 'strippedp) (not (get flavor 'just-loaded)))
	  (msg '|Flavor | flavor '| cannot be combined since it is stripped|
	       N '|Please reload the flavor and continue with "ok"|)
	  (lispbreak)
	  (combine-flavor1 flavor))
      (progn (putprop flavor t 'combined-processing?)
	     (combine-it flavor)
	     (putprop flavor t 'combined?)
	     flavor))))

; combine-it
;	performs the real work of combining the flavor
;	1) compute the list of flavors that influence this flavor
;	2) verify that each of them is combined (or cause it to be combined)
;	3) generate the list of all the instance variables for this flavor
;	4) generate the sparsely populated method table and process each
;		method (if necessary)
;	5) generate all the combined methods for each method of this flavor
;	6) check the required-methods for each component flavor 
;	7) constructs the property which-operations
;	8) if switch is set compile the flavor
(defun combine-it (flavor)
  (let ((components (combine-components flavor))		; (1)
	methods before-daemons after-daemons instance-vars)
	(putprop flavor components 'component-flavors)
	(for cfl in components do (combine-flavor1 cfl))		; (2)
	(and *print-on-combine*
	     (msg "Combining flavor " flavor))
	(putprop flavor (setq instance-vars (find-all-instance-vars flavor))
		 'instance-variables)				; (3)
	(or (get flavor 'just-loaded)    ; if compiled versions are lying around
	    (reset-method-table flavor)) ; don't redefine them  (10/5/82 RHT)
	(find-all-methods flavor)				; (4)
	(build-combined-methods flavor)				; (5)
	(check-required-methods flavor)				; (6)
	(putprop flavor (for mthd in (get flavor 'method-table)	; (7)
			     collect (car mthd))
		 'which-operations)
	(and *flavor-auto-compile* (compile-flavor flavor))	; (8)
	flavor]

; reset-method-table
;	sets the method table of a flavor to contain only the entries
;	that were explicitly defmethod'ed for the given flavor
;	This function is meant to be followed by a call to a set of 
;	functions that would then compute the union of all the
;	messages that should be handled by a given flavor
(defun reset-method-table (flavor)
  (for mthd in (get flavor 'method-table)
       join (for bind (flg nil)
		 fctn in (cddr mthd)
		 collect (cond ((eq (get fctn 'defining-flavor) flavor)

				; clause added to guard against stripping, 
				; unstripping, and then trying to combine a 
				; flavor.  10/3/82 RHT
				(and (eq (get fctn 'method-body) 'stripped)
				     (error (msg '|Can't combine flavor | flavor
						 N '|Def'n for message | 
						 (car mthd)
						 '| has been stripped.|)))
				(setq flg t)
				(build-method flavor fctn)))
		 finally (and flg `((,(car mthd) nil ,@$$val))))
       finally (putprop flavor $$val 'method-table))
	]

; build-method
;	function constructs a function to handle a message given the flavor
;	and the name of the function.  It replaces all references to i-vars
;	of the flavor to the corresponding cxr or rplacx calls.  References
;	to i-vars in quoted forms are left unchanged (so watch out for eval,
;	apply, and funcall forms)
;	note that build-method expects build-method1 to compute the
;	value in *flavor-temp* and nothing else should use the global
;	until the putprop is finished!
(defun build-method (flavor method-symbol)
  (let ((method-body (build-method1 (get flavor 'instance-variables)
				    (get method-symbol 'method-body)))
	method-args)
	(putprop method-symbol *flavor-temp* 'referenced-i-vars)
	(setq method-args (prep-args (get method-symbol 'method-args)))
	(funcall 'defun `(defun ,method-symbol ,method-args ,@method-body))
	]

; build-method1
;	initializes the global *flavor-temp and hangs i-vars 
(declare (special i-vars))

(defun build-method1 (i-vars forms)
	(setq *flavor-temp* nil)
	(cond (*flavor-expand-macros* (build-method2 (macroexpand forms)))
	      (t (build-method2 forms)))
	]

; build-method2
;	maps down the forms replacing each reference to an i-var with the
;	corresponding cxr (or rplacx call)
(defun build-method2 (forms)
	(cond ((atom forms)
			(cond ((setq *flavor-temp1* (assq forms i-vars))
					(or (assq forms *flavor-temp*)
					    (setq *flavor-temp*
						(cons (cons forms 
							(cadr *flavor-temp1*))
						      *flavor-temp*)))
					`(cxr ,(cadr *flavor-temp1*) self))
			      (t forms)))
	      ((eq (car forms) 'quote) forms)
	      ((eq (car forms) 'setq)
	       (cond ((greaterp (length (cdr forms)) 2)
			`(progn 
			  ,@(for bind (setq-forms (cdr forms) (cddr setq-forms))
				 while setq-forms
				 collect (cond ((setq *flavor-temp1* 
						      (assq (car setq-forms) i-vars))
						  (or (assq (car setq-forms) 
							    *flavor-temp*)
						      (setq *flavor-temp*
							    (cons (cons (car setq-forms)
							                (cadr *flavor-temp1*))
								  *flavor-temp*)))
						  `(fl-rplacx ,(cadr *flavor-temp1*)
							      self
							      ,(build-method2 
								    (cadr setq-forms))))
					       (t `(setq ,(car setq-forms)
							 ,(build-method2 
								(cadr setq-forms))))))))
		     (t (cond ((setq *flavor-temp1* (assq (cadr forms) i-vars))
					(or (assq (cadr forms) *flavor-temp*)
					    (setq *flavor-temp*
						(cons (cons (cadr forms)
							 (cadr *flavor-temp1*))
						      *flavor-temp*)))
					`(fl-rplacx ,(cadr *flavor-temp1*) self
						,@(build-method2 (cddr forms))))
			      (t `(setq ,(cadr forms)
					,@(build-method2 (cddr forms))))))))
	      (t (for frm in forms collect (build-method2 frm))))
	]

; prep-args
;	removes all references to the keywords &optional and &rest in the
;	arguments to a method and references only to variable name (not
;	any initialization that might be included
(defun prep-args (arg-lst)
	(for while arg-lst 
	     join (cond ((or (eq (car arg-lst) '|&optional|) 
			     (eq (car arg-lst) '|&rest|))
				(setq *flavor-temp* (cadr arg-lst))
				(setq arg-lst (cddr arg-lst))
				(cond ((atom *flavor-temp*) 
						(ncons *flavor-temp*))
				      (t (ncons (car *flavor-temp*)))))
			((eq (car arg-lst) '|&aux|)
				(setq *flavor-temp* arg-lst)
				(setq arg-lst nil)
				(cons (car *flavor-temp*) (cdr *flavor-temp*)))
			(t (setq *flavor-temp* (car arg-lst))
			   (setq arg-lst (cdr arg-lst))
			   (ncons *flavor-temp*)))
	     finally (cons 'self $$val))
	]

; build-combined-methods
;	maps down the flavors method table and builds combined methods
;	for any message supported by the flavor (by invoking the 
;	build-combined-method <message>)
(defun build-combined-methods (flavor)
	(for method-entry in (get flavor 'method-table)
	     do (build-combined-method flavor method-entry (car method-entry)))
	]

; build-combined-method
;	computes the set of :before and :after daemons for a flavor
;	and builds a combined form for the message. The args to the
;	combined form are the args to the primary method for the 
;	message (with the &aux args removed)
(defun build-combined-method (flavor method-entry message)
    (let ((before-daemons 
	      (for cflavor in (get flavor 'component-flavors)
		   join (cond ((setq *flavor-temp*
				     (cadddr (assq message 
						   (get cflavor 'method-table))))
			       (ncons *flavor-temp*)))))
	  (after-daemons
	      (for cflavor in (reverse (get flavor 'component-flavors))
		   join (cond ((setq *flavor-temp*
				     (caddddr (assq message
						    (get cflavor 'method-table))))
			       (ncons *flavor-temp*)))))
	  (inst-vars (get flavor 'instance-variables))
	  combined-name combined-method-args invoked-args ghost-name)
	 (setq combined-method-args 
	       (cons 'self
		     (for arg-name in (get (caddr method-entry) 'method-args)
			  until (eq arg-name '|&aux|)
			  collect arg-name))
	       invoked-args 
	       (cons 'self
		     (for arg-name in (get (caddr method-entry) 'method-args)
			  until (eq arg-name '|&aux|)
			  join (cond ((memq arg-name '(|&aux| |&optional| |&rest|))
				      nil)
				     ((atom arg-name) (ncons arg-name))
				     (t (ncons (car arg-name)))))))
	 (setq before-daemons
	       (for bdaemon in before-daemons
		    join (cond ((variables-aligned inst-vars 
				    (get bdaemon 'referenced-i-vars))
				(ncons bdaemon))

		      ; 10/5/82 RHT - assumes if just loaded .o file then
		      ; definition of ghost method must be around.
		      	       ((get flavor 'just-loaded)
			        (ncons (concat '|ghost-| flavor '|-| bdaemon)))

			       (t (ncons (make-ghost flavor bdaemon))))))
	 (setq after-daemons
	       (for adaemon in after-daemons
		    join (cond ((variables-aligned inst-vars 
				    (get adaemon 'referenced-i-vars))
				(ncons adaemon))

		      ; 10/5/82 RHT - assumes if just loaded .o file then
		      ; definition of ghost method must be around.
		      	       ((get flavor 'just-loaded)
			        (ncons (concat '|ghost-| flavor '|-| adaemon)))

			       (t (ncons (make-ghost flavor adaemon))))))
	 (cond ((or before-daemons after-daemons) ;  really need to combine
		(setq combined-name 
		      (concat flavor '|-combined-| message '|-method|))
		(or (get flavor 'just-loaded) ; defun if no compiled present
		    (funcall 'defun
			     `(defun ,combined-name 
				     ,combined-method-args
				     (let (flavor-combined-result)
					  ,@(for bdaemon in before-daemons
						 collect `(,bdaemon ,@invoked-args))
					  ,@(and (caddr method-entry)
						 `((setq flavor-combined-result
							 (,(caddr method-entry) ,@invoked-args))))
					  ,@(for adaemon in after-daemons
						 collect `(,adaemon ,@invoked-args))
					  flavor-combined-result)))))
	       ((not (equal combined-method-args invoked-args))
		(setq combined-name 
		      (concat flavor '|-combined-| message '|-method|))
		(or (get flavor 'just-loaded) ; defun if no compiled present
		    (funcall 'defun
			     `(defun ,combined-name ,combined-method-args
				     (,(caddr method-entry) ,@invoked-args)))))
	       (t (setq combined-name (caddr method-entry)))); same as primary
    (rplaca (cdr method-entry) combined-name)))

; check-required-methods
;	runs down all the combined flavors and verifies
;	that there is a method for each required method
;	errors if none exists
(defun check-required-methods (flavor)
  (let ((mthd-table (get flavor 'method-table)))
	(for cflavor in (cdr (get flavor 'component-flavors))
	     do (for rmthd in (get cflavor 'required-methods)
		     do (cond ((caddr (assq rmthd mthd-table)))
			      (t (flavor-error
				  `(|component flavor: | ,cflavor
				    | of flavor: | ,flavor
				    | requires method: | ,rmthd))))))
	]

; make-instance
;	function for creating an object of a given flavor
;	note that this is now a regular form that takes as
;	args the name of the flavor to be instantiated and
;	the rest of the args are init options to make-instance
(defun make-instance (flavor &rest init-options)
	(cond ((not (eq (get flavor 'type) 'flavor))
		    (flavor-error `(|make-instance: | ,flavor
				    | is not of type flavor|)))
	      (t (or (get flavor 'combined?) (combine-flavor flavor))
		 (build-instance flavor (get flavor 'instance-variables)
				 init-options)))
	]

; build-instance
;	processes the init options for the make-instance and supplies
;	default values for uninitialized instance variables and then
;	calls hunk to create the instance
(defun build-instance (flavor inst-vars init-options)
  (let ((default-vars (for i-var in inst-vars
			   collect (cons (car i-var) (caddr i-var)))))
	(for while init-options
	     do	(selectq (car init-options)
	     		; the initoption keywords go here
			(cond ((setq *flavor-temp* 
					(assq (car init-options)
						default-vars))
					(rplacd *flavor-temp*
						(list 'quote 
							(cadr init-options)))
					(setq init-options (cddr init-options)))
			      (t (flavor-error
				  `(|make-instance: can't handle option keyword: |
				    ,(car init-options)))
				 (setq init-options (cdr init-options))))))
	(funcall 'makhunk `(,flavor ,@(for dv in default-vars 
					   collect (eval (cdr dv)))))
	]

; recombine-flavors
;	marks each flavor for combining and then combines them
(defun recombine-flavors (lst-of-flavors)
	(for flavor in lst-of-flavors do (mark-for-combining flavor))
	(combine-flavors lst-of-flavors)
	]

; compile-cmds
;	invokes the compiler on the given cmdlst
;	filename: source file without suffix
;	xxfilename: gets compiler output (comes to screen if nil)
;	no-strip: don't strip off the symbolics from property lists
;	          (don't need them unless expect to recombine a compiled flavor)
;	no-wait: don't wait for forked compile to finish - it will print a 
;	  	  message when done.
(defun compile-cmds (cmdlst filename xxfilename fctn-only no-strip 
			    no-wait no-fork copts)
  (let (prinlength prinlevel liszt-error $ldprint)
   (msg '|Beginning to compile | filename)
   (cond ((and (not no-fork) (fork))
	  (or no-wait (and (plusp (cdr (wait)))
			   (setq liszt-error t))))
	 (t ; now we're either in the child or we didn't fork at all
	    (and xxfilename
		 (setq poport (outfile xxfilename)))
	    (if (not no-fork)
		(sstatus exit-on-error t)
		(sstatus ignoreeof nil))
	    (or (getd 'liszt) (load (get 'liszt 'autoload)))
	    (setq $ldprint t)
	    (if (onep (prog1 (compile-here cmdlst filename fctn-only no-strip copts)
			     (setq poport nil)))
		(setq liszt-error t)
		(msg '|Trouble compiling | filename)
		(or no-fork (exit 1))
	     else (msg '|Compile of | filename '| is finished|)
	          (or no-fork (exit)))))
   ; want to fasl if we didn't fork or we forked and waited; don't want
   ; to fasl if there was an error
   (setq $ldprint t)
   (and (or no-fork (not no-wait))
	(not liszt-error)
	(fasl (concat filename '|.o|)))
   cmdlst)
	]

; compile-here
;	helper function actually builds .ctmp file and calls liszt.
(defun compile-here (cmdlst filename fctn-only no-strip copts)
  (let ((port1 (outfile (concat filename '|.ctmp|))))
   (cond (port1 (dump-commands cmdlst port1 fctn-only no-strip)
		(close port1)
		(funcall 'liszt `(,(concat filename '|.ctmp|) 
				   |-o| ,(concat filename '|.o|) 
				   ,@copts)))
	 (t (msg '|unable to open temp file: | filename '|.ctmp|)))))

; compile-file
;	invokes the compiler of the given file in the current environment
;	filename: source file without suffix
;	xxfilename: gets compiler output (comes to screen if nil)
;	no-wait: don't wait for forked compiler to return - will print a message
;		 when done.
(defun compile-file (filename &optional xxfilename &optional no-wait 
			      &optional no-fork &optional copts)
   (let (liszt-error $ldprint)
        (msg '|Beginning to compile | filename)
	(cond ((and (not no-fork) (fork)) 
	       (or no-wait (and (plusp (cdr (wait)))
				(setq liszt-error t))))
	      (t (cond (xxfilename (setq poport (outfile xxfilename))))
	         (or (getd 'liszt) (load (get 'liszt 'autoload)))
		 (setq $ldprint t)
		 (if (not no-fork)
		     (sstatus exit-on-error t)
		     (sstatus ignoreeof nil))
		 (if (onep (prog1 (compile-file-here filename copts)
				  (setq poport nil)))
		     (setq liszt-error t)
		     (msg '|Trouble compiling | filename)
		     (or no-fork (exit 1))
		  else (msg '|Compile of | filename '| is finished|)
		       (or no-fork (exit)))))
	(setq $ldprint t)
	(and (or no-fork (not no-wait))
	     (not liszt-error)
	     (load filename))
	]

; compile-file-here
;	helper function actually calls liszt.
(defun compile-file-here (filename copts)
   (funcall 'liszt `(,filename ,@copts)))

; dump-commands
;	expects a list of file dump commands and prints (if possible)
;	the commands to the given port
(defun dump-commands (cmd-lst port fctn-only no-strip)
  (let (flavors-dumped result)
    (setq result
      (*catch 'dump-commands-frame
	(for bind tmp
	     while cmd-lst
	     do (selectq (car cmd-lst)
		  (:declares (for dcl on (cdr cmd-lst)
				 until (cmd-option-keywordp (car dcl))
				 join (car dcl)
				 finally (setq cmd-lst dcl)
					 (msg (P port) (L (cons 'declare $$val)))))
		  (:flavors (for fl on (cdr cmd-lst)
				 until (cmd-option-keywordp (car fl))
				 collect (push flavors-dumped (car fl))
					 (car fl)
				 finally (setq cmd-lst fl)
					 (dump-flavors $$val port 
						       fctn-only no-strip)))
		  (:functions (for fctn on (cdr cmd-lst)
				 until (cmd-option-keywordp (car fctn))
				 collect (car fctn)
				 finally (setq cmd-lst fctn)
					 (dump-functions $$val port)))
		  (:inits (for init on (cdr cmd-lst)
				 until (cmd-option-keywordp (car init))
				 collect (car init)
				 finally (setq cmd-lst init)
					 (msg (P port) 
					      (L `(progn 'compile ,@$$val)))))
		  (progn (msg '|undefined dump command: | (car cmd-lst))
			 (setq cmd-lst (cdr cmd-lst)))))))
    (clean-df-marks flavors-dumped)
    (and (eq result '$$fail) (error))
     cmd-lst]

; dump-flavors
;	dumps the flavors to a given port
;	10/1/82 RHT 
;	New version that avoids duplication of methods existing in two
;	flavor's method tables.  Also puts out helper function calls to
;	load-flavor-props and load-method-props rather than a mess of
;	putprops.  If meth-only is set than skips putting out props
;	altogether.
(defun dump-flavors (lst-of-flavors port meth-only no-strip)
  (cond (no-strip (combine-flavors lst-of-flavors)) ; just combine flavors
	(t (strip-flavors lst-of-flavors)))         ; strip and combine
  (for method in (for flavor in lst-of-flavors
		      join (if (not meth-only)
			       (msg (P port) 
				    '|; information concerning flavor: | 
				    (L flavor) N
				    '|(add-flavor '| (L flavor) '| )|)
			       (dump-flavor-props flavor port))
			   (for method-entry in (get flavor 'method-table)
				join (for fn in (cdr method-entry)
					  join (and fn 
						    (check-dump fn flavor)
						    (not (get fn 'df-mark))
						    (putprop fn t 'df-mark)
						    (ncons fn)))))
       do (dump-method method port meth-only))
  (and lst-of-flavors
       (cond (meth-only
	      (msg (P port) '|;do a funny combine of affected flavors| N
		   '|(just-loaded-combine '| (L lst-of-flavors) '|)|))
	     (t (msg (P port) 
		     '|;do a funny forced combine of affected flavors| N
		     '|(just-loaded-combine '| (L lst-of-flavors) 
		     '| t| '|)|)))))

; clean-df-marks
;	After dumping all flavors for a given file, clean up marks
;	indicating which methods have been dumped.
(defun clean-df-marks (flavors-dumped)
  (for flavor in flavors-dumped
       do (for method-entry in (get flavor 'method-table)
	       do (for fn in (cdr method-entry)
		       when fn
		       do (remprop fn 'df-mark)))))

; check-dump
; 	make sure that this method is uncompiled if it's an immediate method
; 	for flavor fl.
(defun check-dump (meth fl)
  (or (not (eq fl (get meth 'defining-flavor)))
      (dtpr (getd meth))
      (progn (msg '|method | meth '| is machine coded (bcd)|
		  N '|Compile aborted|)
	     (*throw 'dump-commands-frame '$$fail))))

; dump-flavor-props 
;	dumps the call to helper function which will later do putprops
; 	for flavor when loading .o file
(defun dump-flavor-props (flavor port)
  (msg (P port) '|;flavor properties:|)
  (msg (P port) '|(load-flavor-props '| (L flavor) -D)
  (for prop in *flavor-flavor-properties*
       do (msg (P port) '| '| (L (cond ((eq prop 'method-table)
					  (dump-method-table flavor))
				       (t (get flavor prop))))
	       -D))
  (msg (P port) '|)|))

;dump-method-table
;	returns a trimmed version of the method-table containing only immediate
;	methods for the given flavor
(defun dump-method-table (flavor)
  (for meth in (get flavor 'method-table)
       when (for meth-name in (cddr meth)
		 when meth-name
		 thereis (eq (get meth-name 'defining-flavor) flavor))
       collect `(,(car meth) nil ,@(cddr meth))))

; add-flavor
;	adds the flavor name to the *all-flavor-names* list if not
;	already there.  Used by compiled files
(defun add-flavor (flavor)
	(or (memq flavor *all-flavor-names*)
	    (setq *all-flavor-names* (cons flavor *all-flavor-names*)))
	]

; dump-method
;	prints out the methods definition. Also its properties unless meth-only
;	is set.
(defun dump-method (method-symbol port meth-only)
	(cond ((eq (type (getd method-symbol)) 'list)
			(msg (P port) '|;method definition:|)
			(msg (P port) '|(def | (L method-symbol) '| |
				       (L (getd method-symbol)) '|)|)
			(or meth-only (dump-method-props method-symbol port)))
	      (t (msg (P port) '|;method: | (L method-symbol)
		      '| is machine (bcd) coded|)))
	]

; dump-method-props 
;	dumps the call to helper function which will later do putprops
; 	for method-symbol when loading .o file
(defun dump-method-props (method-symbol port)
  (msg (P port) '|;method properties:|)
  (msg (P port) '|(load-method-props '| (L method-symbol) -D)
  (for prop in *flavor-method-properties*
       do (msg (P port) '| '| (L (get method-symbol prop)) -D))
  (msg (P port) '|)|))
	
; dump-functions
;	dumps the symbolic form of the function to the specified port
(defun dump-functions (lst-of-fctns port)
	(for bind (tmp)
	     fctn in lst-of-fctns 
	     do (cond ((eq (type (setq tmp (getd fctn))) 'list)
		       (msg (P port) '|(def | (L fctn) B (L tmp) '|)|))
		      ((null tmp) (msg (P port) '|; | fctn '| is undefined|))
		      (t (msg '|; | fctn '| is machine (bcd) coded|
			      N '|Compile aborted|)
			 (*throw 'dump-commands-frame '$$fail)))
	]


; compile-flavor
;	compiles a flavor with a tmp file
;	does nothing now	1/19/82
(defun compile-flavor (flavor)
	flavor]

; strip-flavors
; 	puts 'strippedp flags on property lists of the flavors and replaces
; 	the method-body property on all their methods with 'stripped.
; 	9/29/82 RHT
(defun strip-flavors (flavors)
  (combine-flavors flavors)
  (for x in flavors
       do (strip-flavor x))
  flavors)

(defun strip-flavor (fl)
  (cond ((get fl ':never-strip))
	(t (combine-flavor fl)
	   (putprop fl t 'strippedp)
	   (let ((m-table (get fl 'method-table)))
		(for m in m-table
		     do (for x in (cddr m)
			     when x
			     do (putprop x 'stripped 'method-body)))
		t))))

; unstrip-flavors
; 	takes the 'stripped flag off property lists of the flavors
(defun unstrip-flavors (flavors)
  (for x in flavors
       do (unstrip-flavor x))
  flavors)

(defun unstrip-flavor (fl)
  (and (remprop fl 'strippedp) t))

; load-flavor-props
;	10/1/82 RHT
;	used to perform the putprops to the flavor atom when loading .o file
(defun load-flavor-props (flavor &rest props)
  (for prop-name in *flavor-flavor-properties*
       prop in props
       do (putprop flavor prop prop-name)))

; load-method-props
;	10/1/82 RHT
;	used to perform the putprops to the method atom when loading .o file
(defun load-method-props (method &rest props)
  (for prop-name in *flavor-method-properties*
       prop in props
       do (putprop method prop prop-name)))

; just-loaded-combine
;	10/5/82 RHT
;	called from last line of .o file - sets just-loaded property and then
;	combines - that way compiled versions of the methods will be found
;	rather than creating brand new symbolics
(defun just-loaded-combine (flavors &optional force-combine)
  (for flavor in flavors
       do (and force-combine (putprop flavor nil 'combined?))
	  (putprop flavor nil 'combined-processing?)
	  (putprop flavor t 'just-loaded))
  (combine-flavors flavors)
  (for flavor in flavors
       do (remprop flavor 'just-loaded)))


; remmethod
; 	10/3/82 RHT
;	allows user to remove a defmethod without redoing the defflavor
;	as long as the flavor is not stripped.
(defun remmethod (flavor method &aux p1 p2)
	  (setq p1 (get flavor 'method-table))
	  (cond ((setq p2 (assq method p1))
		 (setq p1 (delq p2 p1))
		 (putprop flavor p1 'method-table)
		 (mark-for-combining flavor)
			)))

; handy macros for getting and setting values of symbols in flavor instances
; means you don't have to use :gettable-instance-variables and :settable ...

(defmacro << (inst sym) `(symeval-in-instance ,inst ,sym))
(defmacro >> (inst sym val) `(set-in-instance ,inst ,sym ,val))
(defmacro flavor (object) `(cxr 0 ,object))

; handy fcn to combine all that needs combining

(defun combine-all nil
  (combine-flavors
   (for f in *all-flavor-names*
	unless (get f 'combined?)
	collect f)))

; make new generalized type function

(eval-when (eval compile load)
  (or (getd 'old-type) (putd 'old-type (getd 'type))))

(defun type (x)
  (cond ((instancep x) (cxr 0 x))
	(t (old-type x))))
