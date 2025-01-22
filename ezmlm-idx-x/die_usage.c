/*
 * $Id: die_usage.c,v 1.1 2025-01-22 10:52:38+05:30 Cprogrammer Exp mbhangui $
 */
#include "strerr.h"
#include "messages.h"
#include "die.h"

no_return void
die_usage(void)
{
	strerr_die1x(100, USAGE);
}
/*
 * $Log: die_usage.c,v $
 * Revision 1.1  2025-01-22 10:52:38+05:30  Cprogrammer
 * Fixes for gcc14
 *
 */
