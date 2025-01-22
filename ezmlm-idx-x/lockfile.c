/*
 * $Idx: $
 */
#include "lock.h"
#include "messages.h"
#include "strerr.h"
#include "die.h"
#include "idx.h"
#include "open.h"

int
lockfile(const char *path)
{
	int             fd;
	fd = open_append(path);
	if (fd == -1)
		strerr_die2sys(111, FATAL, MSG1(ERR_OPEN, path));
	if (lock_ex(fd) == -1)
		strerr_die2sys(111, FATAL, MSG1(ERR_OBTAIN_LOCK, path));
	return fd;
}
/*
 * $Log: lockfile.c,v $
 * Revision 1.1  2025-01-22 10:52:38+05:30  Cprogrammer
 * Fixes for gcc14
 *
 */
