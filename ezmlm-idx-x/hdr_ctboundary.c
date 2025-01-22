/*
 * $Id: hdr_ctboundary.c,v 1.1 2025-01-22 10:52:38+05:30 Cprogrammer Exp mbhangui $
 */
#include "hdr.h"
#include "qmail.h"

extern struct qmail qq;
extern char     flagcd;

void
hdr_ctboundary(void)
{
	if (flagcd) {
		hdr_boundary(0);
		hdr_ctype(CTYPE_TEXT);
		hdr_transferenc();
	} else
		qmail_puts(&qq, "\n");
}
/*
 * $Log: hdr_ctboundary.c,v $
 * Revision 1.1  2025-01-22 10:52:38+05:30  Cprogrammer
 * Fixes for gcc14
 *
 */
