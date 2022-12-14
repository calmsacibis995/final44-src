(int:setsyntax '\; 'splicing 'zapline)
;; buildlisp.l				-[Tue Apr 13 13:43:55 1982 by jkf]-
;; build the lisp system from the C kernel
;; the order of these files is very important.
;; @(#)buildlisp.l	1.4	4/13/82

;
; To load U of M along with Opus 38 things, use this file changing only
; the values of the directories.  If you want to load the U of M objects
; on top of another lisp, modify the directory names, and take out the
; calls to build:load which load the original franz lisp objects.
;

; variables to modify the way buildlisp works:
;   build:dir -- directory containing the object files to load
;	default: /usr/lib/lisp
;   build:map -- map file to write the fasl map into.
;	default: no map is written
;   build:load -- if t then only loading will be done, no fasl'ing
;   lisp-library-directory -- directory which will contain lisp library
;	this directory will be part of the default search path
;   lisp-object-directory -- directory which contains the lisp object file
;
(or (boundp 'build:dir) (setq build:dir '/g/liz/uomlisp/lib))
(or (boundp 'build:map) (setq build:map nil))
(or (boundp 'build:load) (setq build:load nil))
(or (boundp 'lisp-library-directory)
   (setq lisp-library-directory '/g/liz/uomlisp/lib))
(or (boundp 'lisp-object-directory)
   (setq lisp-object-directory '/usr/liz/bin/lisp))


(def build:load
   (lambda (x)
      (prog (name)
	 (setq name (concat build:dir "/" x))
	 (cond (build:map
		  (fasl-or-load name t build:map)
		  ; concatentate to map after first file loaded
		  (cond ((null (status appendmap))
			 (sstatus appendmap t))))
	       (t (fasl-or-load name nil nil))))))

(def fasl-or-load
   (lambda (name provide-map map-name)
     (prog  (tempname)
      (cond ((and (null build:load)
		  (probef (setq tempname (concat name ".o"))))
	       (cond (provide-map (fasl tempname map-name))
		     (t (fasl name))))
	    ((probef (setq tempname (concat name ".l")))
	       (load tempname))
	    (t (patom "fasl-or-load: Can't find file: ")
	       (patom name)
	       (terpr)
	       (exit 1)  ; just go away fast so user will realize problem
	    )))))
	       
; Load franz lisp code.
(build:load 'common0)
(build:load 'syntax)
(build:load 'charmac)
(build:load 'macros)
(build:load 'common1)
(build:load 'common2)
(build:load 'vector)
(build:load 'array)
(build:load 'pp)
(build:load 'version)
; (build:load 'toplevel)
; (putd 'sysout (getd 'dumplisp))

; Load Maryland lisp objects
(build:load 'uommacs)
(build:load 'uomfuncs)
(build:load 'tlev-uom)	; this is a modified version of the top level.
			; If you already have the original in the lisp,
			; you don't have to load this again, but do:
			; (setq user-top-level 'userexec)
(build:load 'nlispx)
(build:load 'lispbreak)
(build:load 'flavors)
(build:load 'vanilla)
(build:load 'new-load)

; make sure all fast links are done
(sstatus translink nil)
(sstatus translink on)
(sstatus translink t)

; want to ignore eof's
(sstatus ignoreeof t)

; autoload liszt for compiling flavors
(putprop 'liszt 'load-liszt 'autoload)

; kill definitions
(putd 'fasl-or-load  nil)
(putd 'build:load nil)

; clean up
(allocate 'symbol 25)
(gc)
(gc symbol)
