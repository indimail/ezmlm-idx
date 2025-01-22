/*
 * $Idx: $
 */
#include "wrap.h"

void
wrap_execsh(const char *command)
{
	const char     *args[4];
	args[0] = "/bin/sh";
	args[1] = "-c";
	args[2] = command;
	args[3] = 0;
	wrap_execv(args);
}
/*
 * $Log: wrap_execsh.c,v $
 * Revision 1.1  2025-01-22 10:52:37+05:30  Cprogrammer
 * Fixes for gcc14
 *
 */
