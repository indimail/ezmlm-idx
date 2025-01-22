/*
 * $Id: getconfopt_ulong.c,v 1.1 2025-01-22 10:52:38+05:30 Cprogrammer Exp mbhangui $
 */
#include "die.h"
#include "getconf.h"
#include "getconfopt.h"
#include "scan.h"

static int
parse(struct option *o, const char *arg)
{
	if (arg[scan_ulong(arg, o->var.ulong)] != 0)
		return 0;
	return 1;
}

static void
fetch(struct option *o)
{
	getconf_ulong(o->var.ulong, o->filename, 0);
}

const struct option_type opt_ulong = {
	1,
	parse,
	fetch
};
/*
 * $Log: getconfopt_ulong.c,v $
 * Revision 1.1  2025-01-22 10:52:38+05:30  Cprogrammer
 * Fixes for gcc14
 *
 */
