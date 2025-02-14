/*
 * $Id: getconfopt_flag.c,v 1.1 2025-01-22 10:52:38+05:30 Cprogrammer Exp mbhangui $
 */
#include "getconf.h"
#include "getconfopt.h"

static int
parse(struct option *o, const char *arg)
{
	*o->var.flag = o->value.flag;
	return 1;
	(void) arg;
}

static int
counter(struct option *o, const char *arg)
{
	*o->var.flag += o->value.flag;
	return 1;
	(void) arg;
}

static void
fetch(struct option *o)
{
	*o->var.flag = !!getconf_isset(o->filename) ^ !o->value.flag;
}

const struct option_type opt_flag = {
	0,
	parse,
	fetch
};

const struct option_type opt_counter = {
	0,
	counter,
	fetch
};
/*
 * $Log: getconfopt_flag.c,v $
 * Revision 1.1  2025-01-22 10:52:38+05:30  Cprogrammer
 * Fixes for gcc14
 *
 */
