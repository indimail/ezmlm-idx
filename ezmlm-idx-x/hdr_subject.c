/*
 * $Id: hdr_subject.c,v 1.1 2025-01-22 10:52:38+05:30 Cprogrammer Exp mbhangui $
 */
#include "hdr.h"
#include "qmail.h"

extern struct qmail qq;

void
hdr_subject(const char *subject)
{
	qmail_puts(&qq, "Subject: ");
	qmail_puts(&qq, subject);
	qmail_puts(&qq, "\n");
}
/*
 * $Log: hdr_subject.c,v $
 * Revision 1.1  2025-01-22 10:52:38+05:30  Cprogrammer
 * Fixes for gcc14
 *
 */
