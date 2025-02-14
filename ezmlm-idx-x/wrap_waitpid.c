/*
 * $Idx: $
 */
#include "wait.h"
#include "messages.h"
#include "strerr.h"
#include "wrap.h"
#include "die.h"
#include "idx.h"

int
wrap_waitpid(int pid)
{
	int             wstat;
	wait_pid(&wstat, pid);
	if (wait_crashed(wstat))
		strerr_die2x(111, FATAL, MSG(ERR_CHILD_CRASHED));
	return wait_exitcode(wstat);
}
/*
 * $Log: wrap_waitpid.c,v $
 * Revision 1.1  2025-01-22 10:52:37+05:30  Cprogrammer
 * Fixes for gcc14
 *
 */
