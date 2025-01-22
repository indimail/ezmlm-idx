/*
 * $Id: hdr_from.c,v 1.1 2025-01-22 10:52:38+05:30 Cprogrammer Exp mbhangui $
 */
#include "hdr.h"
#include "qmail.h"
#include "stralloc.h"
#include "quote.h"
#include "die.h"
#include "idx.h"

extern struct qmail qq;
extern stralloc outlocal;
extern stralloc outhost;
extern stralloc quoted;

void
hdr_from(const char *append)
{
	qmail_puts(&qq, "From: ");
	if (!quote(&quoted, &outlocal))
		die_nomem();
	qmail_put(&qq, quoted.s, quoted.len);
	if (append)
		qmail_puts(&qq, append);
	qmail_puts(&qq, "@");
	qmail_put(&qq, outhost.s, outhost.len);
	qmail_puts(&qq, "\n");
}
/*
 * $Log: hdr_from.c,v $
 * Revision 1.1  2025-01-22 10:52:38+05:30  Cprogrammer
 * Fixes for gcc14
 *
 */
