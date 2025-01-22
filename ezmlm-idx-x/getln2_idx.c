/*
 * $Id: getln2_idx.c,v 1.1 2025-01-22 10:52:38+05:30 Cprogrammer Exp mbhangui $
 */
#include "substdio.h"
#include "stralloc.h"
#include "byte.h"
#include "getln.h"

int
getln2_idx(struct substdio *ss, struct stralloc *sa, char **cont, unsigned int *clen, int sep)
{
	register char  *x;
	register unsigned int i;
	int             n;

	if (!stralloc_ready(sa, 0))
		return -1;
	for (;;) {
		if ((n = substdio_feed(ss)) < 0)
			return -1;
		else
		if (!n) {
			*clen = 0;
			return 0;
		}
		x = substdio_PEEK(ss);
		i = byte_chr(x, n, sep);
		if (i < (unsigned int) n) {
			substdio_SEEK(ss, *clen = i + 1);
			*cont = x;
			return 0;
		}
		if (!stralloc_readyplus(sa, n))
			return -1;
		i = sa->len;
		sa->len = i + substdio_get(ss, sa->s + i, n);
	}
}
/*
 * $Log: getln2_idx.c,v $
 * Revision 1.1  2025-01-22 10:52:38+05:30  Cprogrammer
 * Fixes for gcc14
 *
 */
