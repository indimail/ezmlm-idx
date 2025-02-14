/*
 * $Id: getconfopt_copy.c,v 1.1 2025-01-22 10:52:38+05:30 Cprogrammer Exp mbhangui $
 */
#include "die.h"
#include "getconfopt.h"
#include "stralloc.h"

static int
copy_flag(struct option *o, const char *arg)
{
	if (!stralloc_append(o->var.str, &o->ch))
		die_nomem();
	return 1;
	(void) arg;
}

const struct option_type opt_copy_flag = {
	0,
	copy_flag,
	0
};
/*
 * $Log: getconfopt_copy.c,v $
 * Revision 1.1  2025-01-22 10:52:38+05:30  Cprogrammer
 * Fixes for gcc14
 *
 */
