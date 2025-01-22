/*
 * $Id: die_sender.c,v 1.1 2025-01-22 10:52:38+05:30 Cprogrammer Exp mbhangui $
 */
#include "strerr.h"
#include "messages.h"
#include "die.h"

no_return void
die_sender(void)
{
	strerr_die2x(100, FATAL, MSG(ERR_NOSENDER));
}
/*
 * $Log: die_sender.c,v $
 * Revision 1.1  2025-01-22 10:52:38+05:30  Cprogrammer
 * Fixes for gcc14
 *
 */
