;                    The New Loader Package
;
; This package defines the following new functions:
;
; (load1 <filename>)
;	   
;       This behaves like load for object files and almost like load
;       for symbolics.  In the latter case, $$load-file is set
;       to the FULL name of the file being loaded (with .l) and 
;       $$load-file's property list is modified as follows:
;	The :forms property contains a list of the names of functions,
;	macros, def's, and flavors defined in the file separated by 
; 	appropriate keywords (e.g. :functions, :flavors, etc.).  
;	(Any other forms are included as is with the :inits property.) 
;	In addition, the property lists of each of those names is 
;	modified to contain $$load-file's value under the appropriate 
;	property (e.g. the $$defun-file property for functions).  
;	This allows the same name to be used for different types.  
;	(Things are a bit more complicated in the case of methods 
;	since the flavor must also be stored.)
;
; compile (<fname> [-x [<xfname>]] [-ns] [-nw] [-m] [<other opts>]) 
;       This function accepts the name of a symbolic file (without suffix).
;	If it contains method and/or flavor defn's and was loaded with load1
;	then builds a call suitable for the compile-cmds function using 
;	fname's property list and calls compile-cmds. Otherwise, it calls
;	compile-file.  <fname>.o will contain the object.
;	<fname> can optionally be a list of files 
;	(without suffixes) all of which have been loaded using load1 
;	in which case (car <fname>).o contains object. If -x option is 
;	present then compiler output goes into <xfname> or defaults to 
;	<fname>.X (if <xfname> wasn't given) - the way to have output 
;	come to the screen is by leaving out the -x option altogether.
;	The -ns option causes no stripping of method
;	symbolics from property lists - default is to strip.  The -nw
;	option causes lisp not to wait until forked compile is finished,
;	a message will be printed out when it's done.  Default is to wait.
;	-m causes only method definitions to be compiled.  This means that
;	.l will have to be loaded before .o, but .o will be smaller.
;	Any other options are passed directly to liszt (notably -o and -q)
;
; quick-compile ( ... )
; 	This function calls compile forcing the -nw flag to true - to force
;	compile to be in background, i.e. we won't wait for forked compile
;	to finish.  Otherwise just like compile.
;
; (vi <name> [<flname>])
;       If a function, macro, flavor, or method having the name <name>
;       has been load1'ed, vi will be called on the file containing
;       its definition placing the cursor at the line containing that
;       definition.  If <name> is instead a file name then vi will be
;       called on that file.
;           In the case where <name> has been used for two or
;       more different types, the order of checking is governed by the
;       global variable $$vi-type-order which defaults to 
;                   '(def defun defmacro defflavor defmethod).
;       To override this ordering one can either change the value of
;       $$vi-type-order or in specific cases, call one of the functions 
;       videf, videfun, videfmac, videffl, or videfme instead of vi. 
;	These expect the <name> to be of a specific type.
;           The case when <name> is a method is slightly different.  
;       If <name> has been defined for more than one flavor, vi will
;       print the names of those flavors and direct the user to call vi
;       using the second optional argument <flname> which should
;       contain the name of a flavor for which the <name> method has
;       been defined. (videfme also allows this second optional argument.)
;           When vi returns one of three things can happen depending on the
;       value of $$vi-load.
;
;    $$vi-load = nil     In this case the file is not loaded (0 is returned).
;    $$vi-load = t       In this case the file is loaded (name is returned).
;    $$vi-load = 'ask    In this case the user is queried as to whether or 
;                        not to load.
;
;       Note that 'ask is the default case.

(eval-when (compile) (load 'uommacs))

; We don't want this compiled!!  For some reason this doesn't work
; if it's compiled...  - liz 10/11/82
(progn
  (defun gwd nil (concat (Gwd)))
  (if (null (getd 'Gwd))
      (setq gwdfile (concat (if (boundp 'lisp-library-directory)
				 lisp-library-directory
			     else '/g/liz/uomlisp/lib)
				  ; the above should be changed
			    '/gwd.o))
      (cfasl gwdfile '_gwd 'Gwd "function")))
 
(declare (macros t))

(declare
  (special gcdisable $$noattach-cwd poport $ldprint
	   $$load-file $$vi-load $$vi-type-order $$directives)
  (localf  load-a-file1 check-form check-filename vi1 vi2 vi3 vi-load)
  )

(or (boundp '$$noattach-cwd) (setq $$noattach-cwd nil))
(or (boundp '$$load-file) (setq $$load-file nil))

; initialize two globals for vi stuff
(or (boundp '$$vi-type-order) 
    (setq $$vi-type-order '(def defun defmacro defflavor defmethod)))
(or (boundp '$$vi-load)
    (setq $$vi-load 'ask))

; essentially the old load code modified to build ENTIRE file name
; using the gwd function
(defun load1 (filename &rest fasl-args)
  (cond ((not (or (symbolp filename) (stringp filename))) 
	 (error "load1: illegal filename " filename)))
  (let (load-only fasl-only no-ext len search-path name pred shortname explf)
       
       ; determine the length of the filename, ignoring the possible
       ; list of directories.  set explf to the reversed exploded filename

       (setq len (do ((xx (setq explf (nreverse (explode filename))) (cdr xx))
		      (i 0 (1+ i)))
		     ((null xx) i)
		     (cond ((eq '/ (car xx)) (return i)))))

       (cond ((> len 2)
	      (cond ((memq (cadr explf) '(|.| $$IGNORE))
		     (cond ((eq (car explf) 'o)
			    (setq fasl-only t))
			   ((eq (car explf) 'l)
			    (setq load-only t))
			   (t (setq no-ext t))))
		    (t (setq no-ext t))))
	     (t (setq no-ext t)))

       ; a short name is less or equal 12 characters.  If a name is not
       ; short, then load will not try to append .l or .o

       (cond ((< len 12) (setq shortname t)))

       (cond ((and (> len 0) (eq (getchar filename 1) '/))
	      (setq search-path '(||)))
	     (t (setq search-path (status load-search-path))))
       (do ((xx search-path (cdr xx)))
	   ((null xx) (error "load1: file not found " filename))
	   (setq pred (cond ((memq (car xx) '(|.| $$IGNORE))
			     (if $$noattach-cwd
			      then '||
			      else (concat (gwd) "/")))
			    ((eq (car xx) '||) '||)
			    (t (concat (car xx) "/"))))
	   (cond (no-ext
		  (cond ((and shortname
			      (probef (setq name (concat pred filename ".o"))))
			 (return (fasl name (car fasl-args)
				       (cadr fasl-args))))
			((and shortname
			      (probef (setq name (concat pred filename ".l"))))
			 (return (load-a-file1 name)))
			((probef (setq name (concat pred filename)))
			 (cond (fasl-args (return (fasl name (car fasl-args)
							(cadr fasl-args))))
			       (t (return (load-a-file1 name)))))))
		 (fasl-only
		  (cond ((probef (setq name (concat  pred  filename)))
			 (return (fasl name (car fasl-args)
				       (cadr fasl-args))))))
		 (load-only
		  (cond ((probef (setq name (concat pred filename)))
			 (return (load-a-file1 name)))))))))

; essentially the old load-a-file code with the addition of redefining 
; several functions before the load and putting them back the way we found
; them afterwards.  Also sets the $$load-file global and clears some of its
; properties.
(defun load-a-file1 (name)
  (and $ldprint (msg '|[load1 | name '|]|))
  (putprop name nil ':contains-flavs)
  (if (not $$noattach-cwd) 
      (putprop name nil ':forms))
  (setq $$load-file name)
  (let ((infileport (infile name))
        (gcdisable t)	; don't gc when loading, it slows things down
	(eof (list nil))
	forms)
   (for being (form (read infileport eof))
	bind val last-type
	until (eq eof form)
	join (eval form)
	     (setq val (check-form form))
	     (cond ((eq last-type (car val))
		      (cdr val))
		   (t (and val (setq last-type (car val)))
		      val))
	finally (putprop name (append (get name ':forms) $$val) ':forms))
   (close infileport)
    t))

; returns a list of two elements - the type of the form (expr, macro, etc.)
; and the name of the form (or the entire form if type is not known, say, setq)
; Returns nil if form is a defmethod.
(defun check-form (form)
  (selectq (car form)
     (def (putprop (cadr form) $$load-file '$$def-file)
	  (list ':functions (cadr form)))
     (defun (putprop (cadr form) $$load-file '$$defun-file)
	    (list ':functions (cadr form)))
     (defmacro (putprop (cadr form) $$load-file '$$defmacro-file)
	       (list ':functions (cadr form)))
     (declare (list ':declares (cdr form)))
     (defflavor (putprop (cadr form) $$load-file '$$defflavor-file)
		(putprop $$load-file t ':contains-flavs)
		(list ':flavors (cadr form)))
     (defmethod (let ((pair (cadr form))
		      (name (cadadr form)) pairs fl-file-pair)
		 (setq fl-file-pair (list (car pair) $$load-file) 
		       pairs (get name '$$method-fl-files))
		 (or (member fl-file-pair pairs)
		     (putprop name (cons fl-file-pair pairs) '$$method-fl-files))
		 (putprop $$load-file t ':contains-flavs)
		 nil))
     (list ':inits form)))
  
; builds a call to Rich's compile function allowing multiple source files
; (if filenames is a list) or one (if filenames is an atom).

(defun compile (filenames &rest opts)
  (let (filename xxfilename fctn-only no-strip no-wait no-fork copts)
   (if  (setq filenames (for x in (mklist filenames)
			    collect (or (check-filename x) (return))))
	(setq filename (car filenames))
	(setq copts
	      (for opt on opts
		   join (selectq (car opt)
			 (|-x| (cond ((and (cdr opt) 
					   (neq (getchar (cadr opt) 1) '|-|))
				      (setq xxfilename (cadr opt))
				      (setq opt (cdr opt)))
				     (t (setq xxfilename 
					      (concat filename '|.X|))))
			       nil)
			 (|-m| (setq fctn-only t) nil)
			 (|-ns| (setq no-strip t) nil)
			 (|-nw| (setq no-wait t) nil)
			 (|-nf| (setq no-fork t) nil)
			 (list (car opt)))))
	(cond ((for x in filenames          	   ; do any of the files contain
		    thereis (get (concat x '|.l|)  ; flavors or methods?
				 ':contains-flavs))
	       (setq $$directives (for x in filenames
				       join (copy (get (concat x '|.l|) 
						       ':forms))))
	       (for bind (x (cdr (memq ':flavors $$directives))
			    (cdr (memq ':flavors x)))
		    while x
		    do (for y in x
			    until (eq (getchar y 1) ':)
			    do (combine-flavor y)))
	       (compile-cmds $$directives filename xxfilename fctn-only
			     no-strip no-wait no-fork copts))
	      ((onep (length filenames))
	       (compile-file filename xxfilename no-wait no-fork copts))
	      (t (msg '|Warning: will only compile the first file in list|)
	         (compile-file filename xxfilename no-wait no-fork copts))))
    nil))

; does a compile without waiting to come back - will echo a message when done
(defun quick-compile (fname &rest args)
  (apply 'compile `(,fname ,@args |-nw|)))

; another installment of the old load code - this time just to build
; the expanded file name

(defun check-filename (filename)
  (cond ((not (or (symbolp filename) (stringp filename))) 
	 (error "compile: illegal filename " filename)))
  (let (load-only fasl-only no-ext len search-path name pred shortname explf)
       
       ; determine the length of the filename, ignoring the possible
       ; list of directories.  set explf to the reversed exploded filename

       (setq len (do ((xx (setq explf (nreverse (explode filename))) (cdr xx))
		      (i 0 (1+ i)))
		     ((null xx) i)
		     (cond ((eq '/ (car xx)) (return i)))))

       (cond ((> len 2)
	      (cond ((memq (cadr explf) '(|.| $$IGNORE))
		     (cond ((eq (car explf) 'o)
			    (error "Cannot compile the .o file " filename))
			   ((eq (car explf) 'l)
			    (setq filename (concatl (nreverse (cddr explf))))
			    (setq len (- len 2))))))))

       (and (> len 12) (error "compile: filename too long " filename))

       (cond ((and (> len 0) (eq (getchar filename 1) '/))
	      (setq search-path '(||)))
	     (t (setq search-path (status load-search-path))))
       (do ((xx search-path (cdr xx)))
	   ((null xx) (error "compile: file not found " filename))
	   (setq pred (cond ((memq (car xx) '(|.| $$IGNORE))
			     (if $$noattach-cwd
				 then '||
				 else (concat (gwd) "/")))
			    ((eq (car xx) '||) '||)
			    (t (concat (car xx) "/"))))
	   (cond ((probef (concat (setq name (concat pred filename)) 
				  '|.l|))
		  (return name))
		 ((probef (setq name (concat pred filename)))
		  (error '|compile: file does not have .l suffix: |
			 name))))))

; the new improved vi function - depending on type of name it calls one
; of videfun, videfmac, etc.

(defun vi (name &optional fl)
  (for x in $$vi-type-order
       bind file
       do (and fl (return (videfme name fl)))
	  (selectq x
	   (def (and (setq file (get name '$$def-file))
		     (return (videf name file))))
           (defun (and (setq file (get name '$$defun-file))
		       (return (videfun name file))))
           (defmacro (and (setq file (get name '$$defmacro-file))
			  (return (videfmac name file))))
           (defflavor (and (setq file (get name '$$defflavor-file))
			   (return (videffl name file))))
           (defmethod (and (setq file (get name '$$method-fl-files))
			   (return (videfme name fl file))))
           nil)
       finally (vi1 name)))

; calls vi2 on a def

(defun videf (name &optional file)
   (or file (setq file (get name '$$def-file)))
   (cond (file (vi2 name file 'def))
	 (t (msg "no 'def' defn for that name"))))

; calls vi2 on a defun

(defun videfun (name &optional file)
   (or file (setq file (get name '$$defun-file)))
   (cond (file (vi2 name file 'defun))
	 (t (msg "no function defn for that name"))))

; calls vi2 on a macro

(defun videfmac (name &optional file)
   (or file (setq file (get name '$$defmacro-file)))
   (cond (file (vi2 name file 'defmacro))
	 (t (msg "no macro defn for that name"))))

; calls vi2 on a flavor

(defun videffl (name &optional file)
   (or file (setq file (get name '$$defflavor-file)))
   (cond (file (vi2 name file 'defflavor))
	 (t (msg "no defflavor defn for that name"))))

; calls vi2 on a method - if there's more than one flavor for this method
; it prints all names of such flavors and directs user to call with extra
; argument.

(defun videfme (meth &optional fl &optional fl-files)
  (let (fl-file-pair)
   (or fl-files (setq fl-files (get meth '$$method-fl-files)))
   (cond (fl (setq fl-file-pair (for x in fl-files
				     when (eq fl (car x))
				     do (return x)))
	     (if (not fl-file-pair)
		 (setq fl-file-pair nil)
		 (msg "no such method defn for that flavor")))
	 ((onep (length fl-files))
	  (setq fl-file-pair (car fl-files)))
	 (t (msg "flavors for this method:")
	    (for x in fl-files
		 do (msg (car x) '| | -N))
	    (msg N "should call via (vi <method> <flavor>)")))
   (if fl-file-pair 
       (vi3 (car fl-file-pair) meth (cadr fl-file-pair) 'defmethod))))

; a simple call to vi for a filename

(defun vi1 (file)
    (apply 'exec (list (concat '|vi | file)))
    (vi-load file))

; a trickier call to vi that positions cursor at line of definition

(defun vi2 (name file definer)
    (apply 'exec (list (concat '|vi '+?|
		       definer
		       '| | name '| ' | file)))
    (vi-load file))

; trickiest of all that positions cursor at line of method definition

(defun vi3 (fl meth file definer)
    (apply 'exec (list (concat '|vi '+?|
		       definer
		       '| (| fl '| | meth '|)' | file)))
    (vi-load file))

; after vi has run this loads file or not (or asks) depending on value
; of $$vi-load

(defun vi-load (file)
   (selectq $$vi-load
      (nil	0)
      (t	(load1 file))
      (ask	(if (query "load1 " file "? ")
		    then (load1 file)
		    else 0))
      (msg "unknown value of $$vi-load")))

