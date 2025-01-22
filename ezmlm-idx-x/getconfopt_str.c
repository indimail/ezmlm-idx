/*
 * $Id: getconfopt_str.c,v 1.1 2025-01-22 10:52:38+05:30 Cprogrammer Exp mbhangui $
 */
#include "die.h"
#include "getconf.h"
#include "getconfopt.h"
#include "stralloc.h"

static int
parse(struct option *o, const char *arg)
{
	if (!stralloc_copys(o->var.str, arg))
		die_nomem();
	return 1;
}

static void
fetch(struct option *o)
{
	getconf_line(o->var.str, o->filename, 0);
}

const struct option_type opt_str = {
	1,
	parse,
	fetch
};
/*
 * $Log: getconfopt_str.c,v $
 * Revision 1.1  2025-01-22 10:52:38+05:30  Cprogrammer
 * Fixes for gcc14
 *
 */
