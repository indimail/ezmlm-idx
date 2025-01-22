/*
 * $Id: getconfopt_version.c,v 1.1 2025-01-22 10:52:38+05:30 Cprogrammer Exp mbhangui $
 */
#include "auto_version.h"
#include "getconfopt.h"
#include "strerr.h"

static int
parse(struct option *o, const char *arg)
{
	strerr_die2x(0, "ezmlm version: ", auto_version);
	(void) o;
	(void) arg;
}

const struct option_type opt_version = {
	0,
	parse,
	0
};
/*
 * $Log: getconfopt_version.c,v $
 * Revision 1.1  2025-01-22 10:52:38+05:30  Cprogrammer
 * Fixes for gcc14
 *
 */
