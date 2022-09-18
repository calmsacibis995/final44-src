;; This file contains the differences between the standard version of franz
;; that is distributed by Berkeley, and the version that is in /usr/ucb/lisp.
;; The main differences are the availability of format and loop, and 
;; miscellaneous macros and functions that are present in zetalisp.

;; This file is loaded when a zlisp is created and is also loaded by the
;; compiler when the -m switch is given.  Notice that the compiler runs in
;; a vanilla franz.

;; When this file is changed, a new /usr/ucb/lisp must be created but, not
;;  a new liszt.  liszt loads this file when necessary.

;; These four files and the syntax differences are what differentiate
;; ``lisp'' from the standard released Franz.

(load (concat lisp-library-directory "//machacks"))
(load (concat lisp-library-directory "//struct"))
(load (concat lisp-library-directory "//loop"))
(load (concat lisp-library-directory "//hash"))
(load (concat lisp-library-directory "//lmhacks"))
(cvttomaclisp)

(putprop 'defflavor1 (concat lisp-library-directory "//flavors") 'autoload)
(putprop 'describe (concat lisp-library-directory "//describe") 'autoload)
(putprop 'apropos (concat lisp-library-directory "//describe") 'autoload)
(putprop 'mapatoms (concat lisp-library-directory "//describe") 'autoload)

(setq franz-minor-version-number
      (concat franz-minor-version-number "a"))
