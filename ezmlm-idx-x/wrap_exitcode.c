/*
 * $Idx: $
 */
#include "messages.h"
#include "strerr.h"
#include "wrap.h"
#include "die.h"
#include "idx.h"

void
wrap_exitcode(int pid)
{
	switch (wrap_waitpid(pid)) {
	case 100:
		strerr_die2x(100, FATAL, MSG(ERR_CHILD_FATAL));
	case 111:
		strerr_die2x(111, FATAL, MSG(ERR_CHILD_TEMP));
	case 0:
		break;
	default:
		strerr_die2x(111, FATAL, MSG(ERR_CHILD_UNKNOWN));
	}
}
/*
 * $Log: wrap_exitcode.c,v $
 * Revision 1.1  2025-01-22 10:52:37+05:30  Cprogrammer
 * Fixes for gcc14
 *
 */
