/*
 * $Id: gethdrln.c,v 1.1 2025-01-22 10:52:38+05:30 Cprogrammer Exp mbhangui $
 */
#include "substdio.h"
#include "byte.h"
#include "stralloc.h"
#include "getln.h"
#include "gethdrln.h"

int
gethdrln(substdio *ss, stralloc *sa, int *match, int sep)
{
	char           *cont;
	unsigned int    clen;
	char           *x;

	if (!stralloc_ready(sa, 0))
		return -1;
	sa->len = 0;

	do {
		if (getln2_idx(ss, sa, &cont, &clen, sep))
			return -1;
		if (!clen) {
			*match = 0;
			return 0;
		}
		if (!stralloc_catb(sa, cont, clen))
			return -1;
	} while (sa->len > 1 && (x = substdio_PEEK(ss)) != 0 && (*x == ' ' || *x == '\t'));
	*match = 1;
	return 0;
}
/*
 * $Log: gethdrln.c,v $
 * Revision 1.1  2025-01-22 10:52:38+05:30  Cprogrammer
 * Fixes for gcc14
 *
 */
