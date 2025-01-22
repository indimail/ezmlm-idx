/*
 * $Idx: $
 */
#include <unistd.h>
#include "stralloc.h"
#include "slurpclose.h"
#include "error.h"

int
slurpclose(int fd, stralloc *sa, int bufsize)
{
	int             r;
	for (;;) {
		if (!stralloc_readyplus(sa, bufsize)) {
			close(fd);
			return -1;
		}
		r = read(fd, sa->s + sa->len, bufsize);
		if (r == -1)
			if (errno == error_intr)
				continue;
		if (r <= 0) {
			close(fd);
			return r;
		}
		sa->len += r;
	}
}
/*
 * $Log: slurpclose.c,v $
 * Revision 1.1  2025-01-22 10:52:38+05:30  Cprogrammer
 * Fixes for gcc14
 *
 */
