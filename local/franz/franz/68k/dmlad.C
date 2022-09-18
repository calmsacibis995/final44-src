/* Copyright (c) 1982, Regents, University of California */
struct sdot	{ long I; struct sdot *CDR; };
struct vl	{ long high; long low; };

struct sdot *dmlad(obn,mul,add)
struct sdot *obn;
register long mul, add;
{
	register struct sdot *bn = obn;
	struct vl work;

	for(;;) {
		emul(bn->I,mul,add,&work);
		add = work.high;
		add <<= 2;
		if(work.low < 0) add += 2;
		if((work.low << 1) < 0) add += 1;
		bn->I = work.low & 0x3fffffff;
		if (bn->CDR==0) break;
		bn = bn->CDR;
	}
	if (add) {
		struct sdot *newdot();

		if(add==-1) {
			bn->I |= 0xc0000000;
		} else {
			bn = bn->CDR = newdot();
			bn->I = add;
			bn->CDR = 0;
		}
	}
	return obn;
}
