/*
 * $Id: dns_name.c,v 1.1 2025-01-22 10:52:38+05:30 Cprogrammer Exp mbhangui $
 *
 * Public domain, from djbdns-1.05. 
 */

#include "stralloc.h"
#include "uint16.h"
#include "byte.h"
#include "dns.h"

static char    *q = 0;

int
dns_name_packet(stralloc *out, const char *buf, unsigned int len)
{
	unsigned int    pos;
	char            header[12];
	uint16          numanswers;
	uint16          datalen;

	if (!stralloc_copys(out, ""))
		return -1;

	pos = dns_packet_copy(buf, len, 0, header, 12);
	if (!pos)
		return -1;
	uint16_unpack_big(header + 6, &numanswers);
	pos = dns_packet_skipname(buf, len, pos);
	if (!pos)
		return -1;
	pos += 4;

	while (numanswers--) {
		pos = dns_packet_skipname(buf, len, pos);
		if (!pos)
			return -1;
		pos = dns_packet_copy(buf, len, pos, header, 10);
		if (!pos)
			return -1;
		uint16_unpack_big(header + 8, &datalen);
		if (byte_equal(header, 2, DNS_T_PTR))
			if (byte_equal(header + 2, 2, DNS_C_IN)) {
				if (!dns_packet_getname(buf, len, pos, &q))
					return -1;
				if (!dns_domain_todot_cat(out, q))
					return -1;
				return 0;
			}
		pos += datalen;
	}

	return 0;
}

int
dns_name4(stralloc *out, const char ip[4])
{
	char            name[DNS_NAME4_DOMAIN];

	dns_name4_domain(name, ip);
	if (dns_resolve(name, DNS_T_PTR) == -1)
		return -1;
	if (dns_name_packet(out, dns_resolve_tx.packet, dns_resolve_tx.packetlen) == -1)
		return -1;
	dns_transmit_free(&dns_resolve_tx);
	dns_domain_free(&q);
	return 0;
}
/*
 * $Log: dns_name.c,v $
 * Revision 1.1  2025-01-22 10:52:38+05:30  Cprogrammer
 * Fixes for gcc14
 *
 */
