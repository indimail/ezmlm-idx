/*
 * $Id: getconfopt_ulong_flag.c,v 1.1 2025-01-22 10:52:38+05:30 Cprogrammer Exp mbhangui $
 */
#include "getconf.h"
#include "getconfopt.h"

static int
parse(struct option *o, const char *arg)
{
	*o->var.ulong = o->value.ulong;
	return 1;
	(void) arg;
}

static void
fetch(struct option *o)
{
	if (getconf_isset(o->filename))
		*o->var.ulong = o->value.ulong;
}

const struct option_type opt_ulong_flag = {
	0,
	parse,
	fetch
};
/*
 * $Log: getconfopt_ulong_flag.c,v $
 * Revision 1.1  2025-01-22 10:52:38+05:30  Cprogrammer
 * Fixes for gcc14
 *
 */
