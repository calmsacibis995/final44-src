(File |frl/raccess.l|)
(rremove-datum lambda fput-datum fput flistget delete setq liszt-internal-do mapc run-if-removed-methods is-same car return caar eq do assq cdr *rdata assoc fremove-datum null cond get-restriced-values let)
(rdelete-datum lambda fput-datum fput flistget delete setq liszt-internal-do mapc is-same car return caar eq do assq cdr *rdata assoc flistdelete fdelete null cond get-restriced-values let)
(rdelete-facet lambda fput-datum fput flistget delete flistdelete fdelete return caar eq do assq mapc is-same *rdata fdelete-facet nreverse cdr atom cond car cons setq null quote *fdata liszt-internal-do mapcar findicators1 *fdata-only *fvalues-only get-restricted-values let)
(rremove-facet lambda fput-datum fput flistget delete run-if-removed-methods fremove-datum return caar eq do assq mapc is-same *rdata fremove-facet nreverse cdr atom cond car cons setq null quote *fdata liszt-internal-do mapcar findicators1 *fdata-only *fvalues-only get-restricted-values let)
(rdelete-slot lambda fput-datum fput mapc flistdelete fdelete is-same fdelete-slot nreverse cdr atom cond car cons setq null quote *fdata liszt-internal-do mapcar findicators1 *fdata-only *fvalues-only get-restricted-values let)
(rremove-slot lambda fput-datum fput fremove-datum run-if-removed-methods rdata rdata-only rvalues-only mapc fremove is-same fremove-slot nreverse cdr atom cond car cons setq null quote *fdata liszt-internal-do mapcar findicators1 *fdata-only *fvalues-only get-restricted-values let)
(is-same lambda delete car member return null and cond equal copy do)
(rreplace macro cdr append cons cadddr caddr cadr list > quote error < cond length let progn)
(rremove macro rplaca eq = > quote error < cond length let progn)
(rdelete macro rplaca eq = > quote error < cond length let progn)
(rsiblings lambda nreverse cdr car cons setq null rchildren liszt-internal-do mapcar quote apply mapappend setifyq fname delq)
(r-collect-family lambda rplacd |1-| r-collect-family car setq rchildren liszt-internal-do mapcan fname cons ncons bigp not cdr and zerop null cond)
(rfamily lambda rdescendants fname cons)
(rdescendants lambda rplacd cdr rdescendants car setq cond null liszt-internal-do mapcan append setifyq rchildren)
(rchildren lambda nreverse cdr atom cond car cons setq null quote *rdata liszt-internal-do mapcar findicators1 *rdata-only *rvalues-only)
(rfringe1 lambda rplacd rfringe1 setq liszt-internal-do mapcan car list cdr null cond)
(rfringe lambda rtree rfringe1)
(rtree lambda rtree nreverse cdr atom cond car setq null quote *rdata findicators1 *rdata-only *rvalues-only liszt-internal-do mapcar fname cons)
(rvalue macro list quote cons caddr cadr)
(rvalue-only macro list quote cons caddr cadr)
(rvalue? macro quote cons caddr cadr)
(rvalues-only macro quote cons caddr cadr)
(rvalues macro quote cons caddr cadr)
(rvalue2 macro list quote cons caddr cadr)
(rvalue-only2 macro list quote cons caddr cadr)
(rvalue2? macro quote cons caddr cadr)
(rvalues-only2 macro quote list caddr cadr)
(rvalues2 lambda quote rinherit2 fprocess-indics1)
(rvalue1 macro list quote cons caddr cadr)
(rvalue-only1 macro list quote cons caddr cadr)
(rvalue1? macro quote cons caddr cadr)
(rvalues-only1 macro quote list caddr cadr)
(rvalues1 lambda quote rinherit1 fprocess-indics1)
(rdata1 lambda rinherit1 fprocess-indics1)
(*rvalue macro list quote cons caddr cadr)
(*rvalue-only macro list quote cons caddr cadr)
(*rvalue? macro quote cons caddr cadr)
(*rvalues-only macro quote cons caddr cadr)
(*rvalues macro quote cons caddr cadr)
(*rdatum-only macro list quote cons cadddr caddr cadr)
(*rdatum? macro quote list cadddr caddr cadr)
(*rdata-only macro quote list cadddr caddr cadr)
(*rdata lambda cdr atom cond rlistget fprocess-indics fbucket)
(rdatum macro list quote cons cadddr caddr cadr)
(rdatum-only macro list quote cons cadddr caddr cadr)
(rdatum? macro quote list cadddr caddr cadr)
(rdata-only macro quote list cadddr caddr cadr)
(rdata lambda rinherit fprocess-indics1)
(rinherit2 lambda quote eq and rinherit or)
(rinherit1 lambda funcall rinherit1 apply nreverse cons *fdata liszt-internal-do mapcar findicators1 *fdata-only *fvalues-only return fcomment? car setq do exists null quote eq and cdr atom cond rlistget fbucket or for)
(rinherit lambda rinherit apply funcall nreverse cons *fdata liszt-internal-do mapcar findicators1 *fdata-only *fvalues-only return quote fcomment? and car setq do exists null or cdr atom cond rlistget fbucket for)
(rlistget lambda flistget rplacd visibledatum mapcan list visiblefacet delete copy includeall not memq intersection or and return caar eq fframe do assq onevisibleslot nreverse cdr atom cond car cons setq null quote *fdata liszt-internal-do mapcar findicators1 *fdata-only *fvalues-only get-restricted-values let)
(onevisibleslot macro cons quote list cadddr caddr cadr)
(rinstantiate lambda cadr cdr append list quote cons)
(role? macro quote list caddr cadr)
(restricted-value? macro quote list caddr cadr)
(rcopy lambda frame visibleframe rframe copy)
(rslots lambda rplacd list delete copy includeall not memq intersection or and return caar eq do assq frame mapcan nreverse cdr atom cond car cons setq null quote *fdata liszt-internal-do mapcar findicators1 *fdata-only *fvalues-only get-restricted-values let)
(rshowif macro quote list caddr cadr)
(rexec macro list quote cons cadddr caddr cadr)
(rshow lambda terpri frame visibleframe rframe $prpr)
(visibleframe lambda rplacd visibledatum visiblefacet list delete copy includeall not memq intersection or and return caar eq do assq let visibleslot mapcan nreverse cdr atom cons setq quote car *fdata liszt-internal-do mapcar findicators1 *fdata-only *fvalues-only get-restricted-values null cond)
(visibleslot macro cons quote list caddr cadr)
(visiblefacet macro quote list caddr cadr)
(visibledatum macro cons quote list caddr cadr)
(rframe? macro quote list cadr)
(rfframe macro quote list cadr)
(rframe macro quote list cadr)
(rput macro cadddr caddddr cdr append cons caddr cadr list eq = > quote error < cond length let)
(rget macro caddr cadr cdr append cons list eq = quote error < cond length let)
(restricted-work macro cons quote list cadddr caddr cadr)
(restrict-values macro cons quote list caddr cadr)
(intersection macro list quote cons caddr cadr)
(includeall macro list quote cons caddr cadr)
(changerole macro quote list cadddr caddr cadr)
(setrole macro quote list caddr cadr)
(addrole macro quote list caddr cadr)
(putrole macro quote list caddr cadr)
(getroles macro quote cons cadr)
(change-restricted-value macro quote list cadddr caddr cadr)
(set-restricted-value macro quote list caddr cadr)
(add-restricted-value macro quote list caddr cadr)
(put-restricted-value macro quote list caddr cadr)
(get-restricted-values macro quote cons cadr)
