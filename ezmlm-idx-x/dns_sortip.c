/*
 * $Id: dns_sortip.c,v 1.1 2025-01-22 10:52:38+05:30 Cprogrammer Exp mbhangui $
 *
 * Public domain, from djbdns-1.05. 
 */

#include "byte.h"
#include "dns.h"

/*
 * XXX: sort servers by configurable notion of closeness? 
 * XXX: pay attention to competence of each server? 
 */

void
dns_sortip(char *s, unsigned int n)
{
	unsigned int    i;
	char            tmp[4];

	n >>= 2;
	while (n > 1) {
		i = dns_random(n);
		--n;
		byte_copy(tmp, 4, s + (i << 2));
		byte_copy(s + (i << 2), 4, s + (n << 2));
		byte_copy(s + (n << 2), 4, tmp);
	}
}
/*
 * $Log: dns_sortip.c,v $
 * Revision 1.1  2025-01-22 10:52:38+05:30  Cprogrammer
 * Fixes for gcc14
 *
 */
