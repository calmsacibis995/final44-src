(File |frl/faccess.l|)
(fvalues-as-needed lambda list and if fneed for nreverse cdr atom cond car cons setq null quote fdata liszt-internal-do mapcar findicators1 fdata-only or)
(fvalue-as-needed lambda fneed nreverse cdr atom cond car cons setq null quote fdata liszt-internal-do mapcar findicators1 fdata-only inspect-datum fdatum-only or)
(restrict-data lambda cons cdr atom fcomment? fbucket intersect? and car setq nreverse do filter null cond)
(fneed lexpr cdr return atom findicator funcall car null restrict-data or do exists > and if fdata arg quote cond setq prog)
(fprocess-indic-by-key lambda caadr |2nd| quote apply append funcall cdr fbucket cadr eval eq and cons ncons car atom cond findicator for)
(fprocess-indics1 lambda fprocess-indic nconc cdr return caaar memq cond car findicator atom not and null do)
(fprocess-indics lambda car findicator cons eq return fprocess-indics1 cdr atom cond fbucket setq prog)
(fprocess-indic1 lambda nreverse setq null cdr |2nd| quote apply fbucket liszt-internal-do mapcar findicators cadr eval car eq cons ncons atom cond)
(fprocess-indic lambda caadr |2nd| quote apply append funcall cdr fbucket cadr eval eq cons ncons car atom cond findicator for)
(faccess lexpr atom cond fbucket cdr assoc fassoc |1+| declare fprocess-indics > null or arg frame do)
(fremove-msg lambda cdr atom cond fbucket delq rplacd)
(fput-msg lambda cons ncons nconc cdr atom cond fbucket memq or ifnot)
(fadd-comment lambda cdr fbucket append car atom cond findicator cons quote apply)
(freplace-datum-comment lexpr cons |1-| + cdr < do minusp eq cond let listify quote apply arg flistget flistclear fclear)
(fremove-datum-comment lexpr flistdelete fdelete fremove-msg car null cons |1-| + cdr < do minusp eq - let listify setq liszt-internal-do mapc arg flistget for > cond)
(fput-datum-comment lexpr fput-msg car null cons |1-| + cdr < do minusp eq cond - let listify setq liszt-internal-do mapc arg fbuild for)
(fcomment? lexpr cdr atom fbucket member > and eq = or cond arg flistget for)
(replace-value macro cadr quote list progn)
(remove-value macro cadr quote list progn)
(put-value macro cadr quote list progn)
(freplace-value macro cdddr nconc caddr |3rd| cadr |2nd| quote cons progn)
(fremove-value macro quote list cadddr caddr cadr)
(fput-value macro cdddr nconc caddr |3rd| cadr |2nd| quote cons progn)
(freplace-datum lexpr fadd fname quote list cadr frame+ fput-datum or run-if-added-methods fput-msg > and if flistclear run-if-removed-methods nreverse car cons null cdr atom fbucket mapcar findicators delete liszt-internal-do mapc eq cond flistget setq frame fbuild arg for)
(fremove-datum lambda run-if-removed-methods1 flistdelete get-if-removed-methods eq and if flistget setq return frame? or ifnot prog)
(fput-comment macro rplaca progn)
(fput-datum lexpr fname quote list cadr car frame+ fput-datum atom or run-if-added-methods fput-msg > if flistget not eq and cond setq frame fbuild arg for)
(fvalue macro list quote cons caddr cadr)
(fvalue-only macro list quote cons caddr cadr)
(fvalue? macro quote cons caddr cadr)
(fvalues-only macro quote cons caddr cadr)
(fvalues macro quote cons caddr cadr)
(*fvalue macro list quote cons caddr cadr)
(*fvalue-only macro list quote cons caddr cadr)
(*fvalue? macro quote cons caddr cadr)
(*fvalues-only macro quote cons caddr cadr)
(*fvalues macro quote cons caddr cadr)
(fvalue2 macro list quote cons caddr cadr)
(fvalue-only2 macro list quote cons caddr cadr)
(fvalue2? macro quote cons caddr cadr)
(fvalues-only2 macro quote list caddr cadr)
(fvalues2 lambda quote finherit2 fprocess-indics1)
(fvalue1 macro list quote cons caddr cadr)
(fvalue-only1 macro list quote cons caddr cadr)
(fvalue1? macro quote cons caddr cadr)
(fvalues-only1 macro quote list caddr cadr)
(fvalues1 lambda quote finherit1 fprocess-indics1)
(fdata1 lambda finherit1 fprocess-indics1)
(*fdatum macro list quote cons cadddr caddr cadr)
(*fdatum-only macro list quote cons cadddr caddr cadr)
(*fdatum? macro quote list cadddr caddr cadr)
(*fdata-only macro quote list cadddr caddr cadr)
(*fdata lambda cdr atom cond flistget fprocess-indics fbucket)
(fdatum macro list quote cons cadddr caddr cadr)
(fdatum-only macro list quote cons cadddr caddr cadr)
(fdatum? macro quote list cadddr caddr cadr)
(fdata-only macro quote list cadddr caddr cadr)
(fdata lambda finherit fprocess-indics1)
(fdatum-along macro list quote cons caddddr cadddr caddr cadr)
(fdatum-only-along macro list quote cons caddddr cadddr caddr cadr)
(fdatum-along? macro quote list caddddr cadddr caddr cadr)
(fdata-only-along macro quote list caddddr cadddr caddr cadr)
(fdata-along lambda finherit-along fprocess-indics1)
(match-keyword lambda car cond intersectq for)
(fget-using-keywords lambda return inspect-datum findicators1 and if nreverse fprocess-indic-by-key car cons null liszt-internal-do mapcar apply mapappend finherit2 finherit1 finherit flistget cdr atom fheritage fbucket eq cond caseq quote match-keyword setq prog)
(inspect-datum lambda and if last car for *break break terpri patom request2 list shout0 progn quote stringify error eq caseq cdr cond)
(fclear macro rplaca progn)
(fdelete macro rplaca progn)
(fbuild-frame lexpr cons |1-| + cdr < do minusp eq cond let listify quote apply arg frame+ setarg)
(freplace-facet lambda fremove-facet)
(freplace-slot lambda fremove-slot)
(fremove-facet lambda flistclear fremove-datum fremove-value nreverse cdr atom cond car cons setq null quote *fdata liszt-internal-do mapcar findicators1 *fdata-only *fvalues-only do do-foreach eq and if)
(fremove-slot lambda flistdelete fremove-datum fremove-value nreverse cdr atom cond car cons setq null quote *fdata liszt-internal-do mapcar findicators1 *fdata-only *fvalues-only do do-foreach)
(fput-structure macro cadr |2nd| list null cddr reverse last car do > quote error length cdr < cond progn)
(freplace macro rplaca eq = > quote error length cdr < cond progn)
(fremove macro rplaca eq = > quote error length cdr < cond progn)
(fput macro rplaca > quote error length cdr < cond progn)
(fget macro rplaca eq = quote error length cdr < cond progn)
