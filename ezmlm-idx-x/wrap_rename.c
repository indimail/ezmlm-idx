/*
 * $Idx: $
 */
#include "die.h"
#include "messages.h"
#include "strerr.h"
#include "wrap.h"

int             rename(const char *old, const char *new);

void
wrap_rename(const char *oldpath, const char *newpath)
{
	if (rename(oldpath, newpath) == -1)
		strerr_die2sys(111, FATAL, MSG2(ERR_MOVE, oldpath, newpath));
}
/*
 * $Log: wrap_rename.c,v $
 * Revision 1.1  2025-01-22 10:52:37+05:30  Cprogrammer
 * Fixes for gcc14
 *
 */
