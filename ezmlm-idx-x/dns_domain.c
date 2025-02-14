/*
 * $Id: dns_domain.c,v 1.1 2025-01-22 10:52:37+05:30 Cprogrammer Exp mbhangui $
 *
 * Public domain, from djbdns-1.05. 
 */

#include "error.h"
#include "alloc.h"
#include "case.h"
#include "byte.h"
#include "dns.h"

unsigned int
dns_domain_length(const char *dn)
{
	const char     *x;
	unsigned char   c;

	x = dn;
	while ((c = *x++) != 0)
		x += (unsigned int) c;
	return x - dn;
}

void
dns_domain_free(char **out)
{
	if (*out) {
		alloc_free(*out);
		*out = 0;
	}
}

int
dns_domain_copy(char **out, const char *in)
{
	unsigned int    len;
	char           *x;

	len = dns_domain_length(in);
	x = alloc(len);
	if (!x)
		return 0;
	byte_copy(x, len, in);
	if (*out)
		alloc_free(*out);
	*out = x;
	return 1;
}

int
dns_domain_equal(const char *dn1, const char *dn2)
{
	unsigned int    len;

	len = dns_domain_length(dn1);
	if (len != dns_domain_length(dn2))
		return 0;

	if (case_diffb(dn1, len, dn2))
		return 0; /* safe since 63 < 'A' */
	return 1;
}

int
dns_domain_suffix(const char *big, const char *little)
{
	unsigned char   c;

	for (;;) {
		if (dns_domain_equal(big, little))
			return 1;
		c = *big++;
		if (!c)
			return 0;
		big += c;
	}
}

unsigned int
dns_domain_suffixpos(const char *big, const char *little)
{
	const char     *orig = big;
	unsigned char   c;

	for (;;) {
		if (dns_domain_equal(big, little))
			return big - orig;
		c = *big++;
		if (!c)
			return 0;
		big += c;
	}
}
/*
 * $Log: dns_domain.c,v $
 * Revision 1.1  2025-01-22 10:52:37+05:30  Cprogrammer
 * Fixes for gcc14
 *
 */
