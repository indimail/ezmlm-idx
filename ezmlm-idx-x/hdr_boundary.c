/*
 * $Id: hdr_boundary.c,v 1.1 2025-01-22 10:52:38+05:30 Cprogrammer Exp mbhangui $
 */
#include "hdr.h"
#include "qmail.h"
#include "makehash.h"

extern struct qmail qq;
extern char     boundary[HASHLEN];

void
hdr_boundary(int last)
{
	qmail_puts(&qq, "\n\n--");
	qmail_put(&qq, boundary, HASHLEN);
	qmail_puts(&qq, last ? "--\n" : "\n");
}
/*
 * $Log: hdr_boundary.c,v $
 * Revision 1.1  2025-01-22 10:52:38+05:30  Cprogrammer
 * Fixes for gcc14
 *
 */
