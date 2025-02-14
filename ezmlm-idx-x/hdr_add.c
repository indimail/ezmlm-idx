/*
 * $Id: hdr_add.c,v 1.1 2025-01-22 10:52:38+05:30 Cprogrammer Exp mbhangui $
 */
#include "hdr.h"
#include "qmail.h"

extern struct qmail qq;

void
hdr_add(const char *line, unsigned int len)
{
	qmail_put(&qq, line, len);
	qmail_puts(&qq, "\n");
}

void
hdr_adds(const char *line)
{
	qmail_puts(&qq, line);
	qmail_puts(&qq, "\n");
}

void
hdr_add2(const char *start, const char *value, unsigned int len)
{
	qmail_puts(&qq, start);
	qmail_put(&qq, value, len);
	qmail_puts(&qq, "\n");
}

void
hdr_add2s(const char *start, const char *value)
{
	qmail_puts(&qq, start);
	qmail_puts(&qq, value);
	qmail_puts(&qq, "\n");
}
/*
 * $Log: hdr_add.c,v $
 * Revision 1.1  2025-01-22 10:52:38+05:30  Cprogrammer
 * Fixes for gcc14
 *
 */
