/*
 * $Idx: $
 */
#include "die.h"
#include "stralloc.h"
#include "sub_std.h"

void
makepath(stralloc *fn, const char *subdir, const char *append, char ch)
{
	if (!stralloc_copys(fn, (subdir != 0 && subdir[0] != 0 && (subdir[0] != '.' || subdir[1] != 0))
						? subdir : "."))
		die_nomem();
	if (!stralloc_cats(fn, append))
		die_nomem();
	if (ch > 0)
		if (!stralloc_catb(fn, &ch, 1))
			die_nomem();
	if (!stralloc_0(fn))
		die_nomem();
}
/*
 * $Log: makepath.c,v $
 * Revision 1.1  2025-01-22 10:52:38+05:30  Cprogrammer
 * Fixes for gcc14
 *
 */
