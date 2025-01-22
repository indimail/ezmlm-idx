/*
 * $Id: die_badformat.c,v 1.1 2025-01-22 10:52:39+05:30 Cprogrammer Exp mbhangui $
 */
#include "strerr.h"
#include "messages.h"
#include "die.h"

no_return void
die_badformat(void)
{
	strerr_die2x(100, FATAL, MSG(ERR_BAD_REQUEST));
}
/*
 * $Log: die_badformat.c,v $
 * Revision 1.1  2025-01-22 10:52:39+05:30  Cprogrammer
 * Fixes for gcc14
 *
 */
