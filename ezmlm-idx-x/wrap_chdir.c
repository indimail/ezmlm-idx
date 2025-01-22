/*
 * $Idx: $
 */
#include <unistd.h>
#include "messages.h"
#include "strerr.h"
#include "wrap.h"
#include "die.h"

void
wrap_chdir(const char *dir)
{
	if (chdir(dir) == -1)
		strerr_die2sys(111, FATAL, MSG1(ERR_CHDIR, dir));
}
/*
 * $Log: wrap_chdir.c,v $
 * Revision 1.1  2025-01-22 10:52:37+05:30  Cprogrammer
 * Fixes for gcc14
 *
 */
