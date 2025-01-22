/*
 * $Idx: $
 *
 * Public domain, from djbdns-1.05. 
 * As per http://cr.yp.to/djbdns/res-disaster.html 
 */

int
main()
{
	unsigned long   u;
	u = 1;
	u += u;
	u += u;
	u += u;
	u += u;
	u += u;
	u += u;
	u += u;
	u += u;
	u += u;
	u += u;
	u += u;
	u += u;
	u += u;
	u += u;
	u += u;
	u += u;
	u += u;
	u += u;
	u += u;
	u += u;
	u += u;
	u += u;
	u += u;
	u += u;
	u += u;
	u += u;
	u += u;
	u += u;
	u += u;
	u += u;
	u += u;
	u += u;
	if (!u)
		_exit(0);
	_exit(1);
}
/*
 * $Log: tryulong32.c,v $
 * Revision 1.1  2025-01-22 10:52:37+05:30  Cprogrammer
 * Fixes for gcc14
 *
 */
